/***************************************************************************//**
* \file cy_scb_i2c.c
*
* Provides I2C API implementation of the SCB driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cy_scb_i2c.h"
#include "WPCVehicleOption.h"

/***************************************
*        Function Prototypes
***************************************/

static cy_en_scb_i2c_status_t HandleStatus(volatile stc_SCB_t *base, uint32_t status,
                                           cy_stc_scb_i2c_context_t *context);
static uint32_t WaitOneUnit(uint32_t *timeout);


/*******************************************************************************
* Function Name: Cy_SCB_I2C_Init
****************************************************************************//**
*
* Initializes the SCB for the I2C operation.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param config
* The pointer to the configuration structure \ref cy_stc_scb_i2c_config_t.
*
* \param context
* The pointer to the context structure \ref cy_stc_scb_i2c_context_t allocated
* by the user. The structure is used during the I2C operation for internal
* configuration and data keeping. The user must not modify anything
* in this structure.
*
* \return
* \ref cy_en_scb_i2c_status_t
*
* \note
* Ensure that the SCB block is disabled before calling this function.
*
*******************************************************************************/
cy_en_scb_i2c_status_t Cy_SCB_I2C_Init(volatile stc_SCB_t *base, cy_stc_scb_i2c_config_t const *config, cy_stc_scb_i2c_context_t *context)
{
    cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_BAD_PARAM;
    un_SCB_CTRL_t         temp_CTRL         = {0ul};
    un_SCB_I2C_CTRL_t     temp_I2C_CTRL     = {0ul};
    un_SCB_RX_CTRL_t      temp_RX_CTRL      = {0ul};
    un_SCB_RX_MATCH_t     temp_RX_MATCH     = {0ul};
    un_SCB_TX_CTRL_t      temp_TX_CTRL      = {0ul};

    if ((NULL != base) && (NULL != config) && (NULL != context))
    {
        /* Configure the I2C interface */
        temp_CTRL.stcField.u1ADDR_ACCEPT = (config->acceptAddrInFifo ? 1ul : 0ul);
        temp_CTRL.stcField.u1EC_AM_MODE  = (config->enableWakeFromSleep ? 1ul : 0ul);
        temp_CTRL.stcField.u2MEM_WIDTH   = 0ul;
        temp_CTRL.stcField.u2MODE        = CY_SCB_CTRL_MODE_I2C;
        base->unCTRL.u32Register         = temp_CTRL.u32Register;

        temp_I2C_CTRL.stcField.u1S_GENERAL_IGNORE = (config->ackGeneralAddr ? 0ul : 1ul);
        temp_I2C_CTRL.stcField.u1SLAVE_MODE       = (config->i2cMode & 0x00000001ul);
        temp_I2C_CTRL.stcField.u1MASTER_MODE      = (config->i2cMode & 0x00000002ul) >> 1ul;
        base->unI2C_CTRL.u32Register              = temp_I2C_CTRL.u32Register;

        /* Configure the RX direction */
        temp_RX_CTRL.stcField.u5DATA_WIDTH = CY_SCB_I2C_DATA_WIDTH;
        temp_RX_CTRL.stcField.u1MSB_FIRST  = 1ul;
        base->unRX_CTRL.u32Register        = temp_RX_CTRL.u32Register;
        base->unRX_FIFO_CTRL.u32Register   = (config->useRxFifo ? (CY_SCB_I2C_FIFO_SIZE - 1ul) : 0ul);

        /* Set the default address and mask */
        temp_RX_MATCH.stcField.u8ADDR = ((uint32_t) config->slaveAddress << 1ul);
        temp_RX_MATCH.stcField.u8MASK = ((uint32_t) config->slaveAddressMask << 1ul);
        base->unRX_MATCH.u32Register  = temp_RX_MATCH.u32Register;

        /* Configure the TX direction */
        temp_TX_CTRL.stcField.u5DATA_WIDTH = CY_SCB_I2C_DATA_WIDTH;
        temp_TX_CTRL.stcField.u1MSB_FIRST  = 1ul;
        temp_TX_CTRL.stcField.u1OPEN_DRAIN = 1ul;
        base->unTX_CTRL.u32Register        = temp_TX_CTRL.u32Register;
        base->unTX_FIFO_CTRL.u32Register   = (config->useTxFifo ? CY_SCB_I2C_HALF_FIFO_SIZE : 1ul);

        /* Configure interrupt sources */
        base->unINTR_SPI_EC_MASK.u32Register = 0ul;
        base->unINTR_I2C_EC_MASK.u32Register = 0ul;
        base->unINTR_RX_MASK.u32Register     = 0ul;
        base->unINTR_TX_MASK.u32Register     = 0ul;
        base->unINTR_M_MASK.u32Register      = 0ul;

        base->unINTR_S_MASK.u32Register      = ((0ul != (CY_SCB_I2C_SLAVE & config->i2cMode)) ? CY_SCB_I2C_SLAVE_INTR : 0ul);

        /* Initialize the context */
        context->useRxFifo = config->useRxFifo;
        context->useTxFifo = config->useTxFifo;

        context->state = CY_SCB_I2C_IDLE;

        /* Master-specific */
        context->masterStatus     = 0ul;
        context->masterBufferIdx  = 0ul;

        /* Slave-specific */
        context->slaveStatus       = 0ul;

        context->slaveRxBufferIdx  = 0ul;
        context->slaveRxBufferSize = 0ul;

        context->slaveTxBufferIdx  = 0ul;
        context->slaveTxBufferSize = 0ul;

        /* Un-register callbacks */
        context->cbEvents = NULL;
        context->cbAddr   = NULL;

        retStatus = CY_SCB_I2C_SUCCESS;
    }

    return (retStatus);
}


/*******************************************************************************
*  Function Name: Cy_SCB_I2C_DeInit
****************************************************************************//**
*
* De-initializes the SCB block, returns register values to default.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \note
* Ensure that the SCB block is disabled before calling this function.
*
*******************************************************************************/
void Cy_SCB_I2C_DeInit(volatile stc_SCB_t *base)
{
    /* Returns block registers into the default state */
    base->unCTRL.u32Register             = CY_SCB_CTRL_DEF_VAL;
    base->unI2C_CTRL.u32Register         = CY_SCB_I2C_CTRL_DEF_VAL;
    base->unI2C_CFG.u32Register          = CY_SCB_I2C_CFG_DEF_VAL;

    base->unRX_CTRL.u32Register          = CY_SCB_RX_CTRL_DEF_VAL;
    base->unRX_FIFO_CTRL.u32Register     = 0ul;
    base->unRX_MATCH.u32Register         = 0ul;

    base->unTX_CTRL.u32Register          = CY_SCB_TX_CTRL_DEF_VAL;
    base->unTX_FIFO_CTRL.u32Register     = 0ul;

    base->unINTR_SPI_EC_MASK.u32Register = 0ul;
    base->unINTR_I2C_EC_MASK.u32Register = 0ul;
    base->unINTR_RX_MASK.u32Register     = 0ul;
    base->unINTR_TX_MASK.u32Register     = 0ul;
    base->unINTR_M_MASK.u32Register      = 0ul;
    base->unINTR_S_MASK.u32Register      = 0ul;
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_Disable
****************************************************************************//**
*
* Disables the SCB block and clears context statuses.
* Note that after the block is disabled, the TX and RX FIFOs and hardware
* statuses are cleared. Also, the hardware stops driving the output and
* ignores the input.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_scb_i2c_context_t allocated
* by the user. The structure is used during the I2C operation for internal
* configuration and data keeping. The user must not modify anything
* in this structure.
*
* \note
* Calling this function when I2C is busy (master performs transaction or slave
* was address and communicates with master) may cause transaction corruption
* because the hardware stops driving the outputs and ignores the inputs.
* It is recommended to ensure that I2C is not busy before calling this function.
*
*******************************************************************************/
void Cy_SCB_I2C_Disable(volatile stc_SCB_t *base, cy_stc_scb_i2c_context_t *context)
{
    base->unCTRL.stcField.u1ENABLED = 0ul;

    /* Set the state to default and clear statuses */
    context->state        = CY_SCB_I2C_IDLE;
    context->masterStatus = 0ul;
    context->slaveStatus  = 0ul;
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_SetDataRate
****************************************************************************//**
*
* Configures the SCB to work at the desired data rate.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param dataRateHz
* The desired data Rate in Hz.
*
* \param scbClockHz
* The frequency of the clock connected to the SCB in Hz.
*
* \return
* The achieved data rate in Hz.
*
* \note
* This function does not change the values of the clock divider connected
* to the SCB, it only changes the SCB clock oversample registers. If this
* function is not able to achieve the desired data rate, then the clock
* divider has to be adjusted. Call this function only while the SCB is
* disabled. For the slave, this function only checks that the attached clock is
* fast enough to meet the desired data rate, it does not change any registers.
*
*******************************************************************************/
uint32_t Cy_SCB_I2C_SetDataRate(volatile stc_SCB_t *base, uint32_t dataRateHz, uint32_t scbClockHz)
{
    uint32_t actualDataRate = 0ul;

    if ((base->unI2C_CTRL.stcField.u1SLAVE_MODE == 1ul) && (base->unI2C_CTRL.stcField.u1MASTER_MODE == 0ul))
    {
        actualDataRate = Cy_SCB_I2C_GetDataRate(base, scbClockHz);

        /* Use an analog filter for the slave */
        base->unRX_CTRL.stcField.u1MEDIAN = 0ul;
        base->unI2C_CFG.u32Register       = CY_SCB_I2C_ENABLE_ANALOG_FITLER;
    }
    else
    {
        if ((scbClockHz > 0u) && (dataRateHz > 0u))
        {
            uint32_t sclLow;
            uint32_t sclHigh;
            uint32_t lowPhase;
            uint32_t highPhase;

            /* Convert scb clock and data rate in kHz */
            uint32_t scbClockKHz = scbClockHz / 1000ul;
            uint32_t dataRateKHz = dataRateHz / 1000ul;

            /* Get period of the scb clock in ns */
            uint32_t period = 1000000000ul / scbClockHz;

            /* Get duration of SCL low and high for the selected data rate */
            if (dataRateHz <= CY_SCB_I2C_STD_DATA_RATE)
            {
                sclLow  = CY_SCB_I2C_MASTER_STD_SCL_LOW;
                sclHigh = CY_SCB_I2C_MASTER_STD_SCL_HIGH;
            }
            else if (dataRateHz <= CY_SCB_I2C_FST_DATA_RATE)
            {
                sclLow  = CY_SCB_I2C_MASTER_FST_SCL_LOW;
                sclHigh = CY_SCB_I2C_MASTER_FST_SCL_HIGH;
            }
            else
            {
                sclLow  = CY_SCB_I2C_MASTER_FSTP_SCL_LOW;
                sclHigh = CY_SCB_I2C_MASTER_FSTP_SCL_HIGH;
            }

            /* Get low phase minimum value in scb clocks */
            lowPhase = sclLow / period;
            while (((period * lowPhase) < sclLow) && (lowPhase < CY_SCB_I2C_LOW_PHASE_MAX))
            {
                ++lowPhase;
            }

            /* Get high phase minimum value in scb clocks */
            highPhase = sclHigh / period;
            while (((period * highPhase) < sclHigh) && (highPhase < CY_SCB_I2C_HIGH_PHASE_MAX))
            {
                ++highPhase;
            }

            /* Get actual data rate */
            actualDataRate = scbClockKHz / (lowPhase + highPhase);

            uint32_t idx = 0ul;
            while ((actualDataRate > dataRateKHz) &&
                   ((lowPhase + highPhase) < CY_SCB_I2C_DUTY_CYCLE_MAX))
            {
                /* Increase low and high phase to reach desired data rate */
                if (0ul != (idx & 0x1ul))
                {
                    if (highPhase < CY_SCB_I2C_HIGH_PHASE_MAX)
                    {
                        highPhase++;
                    }
                }
                else
                {
                    if (lowPhase < CY_SCB_I2C_LOW_PHASE_MAX)
                    {
                        lowPhase++;
                    }
                }

                idx++;

                /* Update actual data rate */
                actualDataRate = scbClockKHz / (lowPhase + highPhase);
            }

            /* Set filter configuration based on actual data rate */
            if (actualDataRate > CY_SCB_I2C_FST_DATA_RATE)
            {
                /* Use a digital filter */
                base->unRX_CTRL.stcField.u1MEDIAN = 1ul;
                base->unI2C_CFG.u32Register       = CY_SCB_I2C_DISABLE_ANALOG_FITLER;
            }
            else
            {
                /* Use an analog filter */
                base->unRX_CTRL.stcField.u1MEDIAN = 0ul;
                base->unI2C_CFG.u32Register       = CY_SCB_I2C_ENABLE_ANALOG_FITLER;
            }

            /* Set phase low and high */
            Cy_SCB_I2C_MasterSetLowPhaseDutyCycle (base, lowPhase);
            Cy_SCB_I2C_MasterSetHighPhaseDutyCycle(base, highPhase);

            /* Convert actual data rate in Hz */
            actualDataRate = scbClockHz / (lowPhase + highPhase);
        }
    }

    return (actualDataRate);
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_GetDataRate
****************************************************************************//**
*
* Returns the data rate for the selected SCB block.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param scbClockHz
* The frequency of the clock connected to the SCB in Hz.
*
* \return
* The data rate in Hz.
*
*******************************************************************************/
uint32_t Cy_SCB_I2C_GetDataRate(volatile stc_SCB_t const *base, uint32_t scbClockHz)
{
    uint32_t actualDataRate;

    if ( (base->unI2C_CTRL.stcField.u1SLAVE_MODE == 1ul) && 
         (base->unI2C_CTRL.stcField.u1MASTER_MODE == 0ul) )
    {
        /* Check the clock frequency range to get maximum supported data rate */
        if ((scbClockHz >= CY_SCB_I2C_SLAVE_FST_CLK_MIN) && (scbClockHz <= CY_SCB_I2C_SLAVE_FST_CLK_MAX))
        {
            actualDataRate = CY_SCB_I2C_FST_DATA_RATE;
        }
        else if ((scbClockHz >= CY_SCB_I2C_SLAVE_STD_CLK_MIN) && (scbClockHz <= CY_SCB_I2C_SLAVE_STD_CLK_MAX))
        {
            actualDataRate = CY_SCB_I2C_STD_DATA_RATE;
        }
        else if ((scbClockHz >= CY_SCB_I2C_SLAVE_FSTP_CLK_MIN) && (scbClockHz <= CY_SCB_I2C_SLAVE_FSTP_CLK_MAX))
        {
            actualDataRate = CY_SCB_I2C_FSTP_DATA_RATE;
        }
        else
        {
            /* The clock frequency is too low or it gets to the gap between
            * Fast and Fast Plus data rates.
            */
            actualDataRate = 0ul;
        }
    }
    else
    {
        uint32_t dutyCycle;

        /* Get number of clocks in one SCL period */
        dutyCycle = base->unI2C_CTRL.stcField.u4LOW_PHASE_OVS  +
                    base->unI2C_CTRL.stcField.u4HIGH_PHASE_OVS +
                    2ul;

        /* Calculate the actual data rate */
        actualDataRate = (scbClockHz / dutyCycle);
    }

    return (actualDataRate);
}


/*******************************************************************************
*                         I2C Master API: Low level
*******************************************************************************/


/*******************************************************************************
* Function Name: Cy_SCB_I2C_MasterSendStart
****************************************************************************//**
*
* Generates a Start condition and sends a slave address with the Read/Write bit.
* This function is blocking and it does not return until the Start condition
* and address byte are sent and a ACK/NAK is received, an error or timeout
* occurred.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param address
* 7 bit right justified slave address.
*
* \param bitRnW
* This sets the value of the Read/Write bit in the address, thus defining
* the direction of the following transfer.
* See \ref group_scb_i2c_macro_direction for the set of constants.
*
* \param timeoutMs
* Defines in milliseconds the time that this function can block for.
* If that time expires, the function returns. If a zero is passed,
* the function waits forever for the action to complete. If a timeout occurs,
* the SCB block is reset. Note The maximum value is sizeof(uint32_t)/1000.
*
* \param context
* The pointer to the context structure \ref cy_stc_scb_i2c_context_t allocated
* by the user. The structure is used during the I2C operation for internal
* configuration and data keeping. The user must not modify anything
* in this structure.
*
* \return
* \ref cy_en_scb_i2c_status_t
*
* \note
* After a Read transaction is initiated and the slave ACKs the address, at
* least one byte must be read before completing the transaction or changing
* its direction.
*
*******************************************************************************/
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterSendStart(volatile stc_SCB_t *base, uint32_t address,
                                    uint32_t bitRnW, uint32_t timeoutMs,
                                    cy_stc_scb_i2c_context_t *context)
{
    cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_MASTER_NOT_READY;
    un_SCB_I2C_M_CMD_t temp_I2C_M_CMD;

    /* Disable the I2C slave interrupt sources to protect the state */
    Cy_SCB_SetSlaveInterruptMask(base, CY_SCB_CLEAR_ALL_INTR_SRC);

    if (CY_SCB_I2C_IDLE == context->state)
    {
        uint32_t locStatus;

        /* Convert the timeout to microseconds */
        uint32_t timeout = (timeoutMs * 1000ul);

        /* Set the read or write direction */
        context->state = CY_SCB_I2C_MASTER_ADDR;
        context->masterRdDir = (CY_SCB_I2C_READ_XFER == bitRnW);

        /* Clean up the hardware before a transfer. Note RX FIFO is empty at here */
        Cy_SCB_ClearMasterInterrupt(base, CY_SCB_I2C_MASTER_INTR_ALL);
        Cy_SCB_ClearRxInterrupt(base, CY_SCB_RX_INTR_NOT_EMPTY);
        Cy_SCB_ClearTxFifo(base);
        Cy_SCB_ClearRxFifo(base);

        /* Generate a Start and send address byte */
        //Cy_SCB_WriteTxFifo(base, (_VAL2FLD(CY_SCB_I2C_ADDRESS, address) | bitRnW));
        Cy_SCB_WriteTxFifo(base,((((uint32_t)(address) << 1ul) & CY_SCB_I2C_ADDRESS_Msk) | bitRnW));

        temp_I2C_M_CMD.u32Register                = 0ul;
        temp_I2C_M_CMD.stcField.u1M_START_ON_IDLE = 1ul;
        base->unI2C_M_CMD.u32Register             = temp_I2C_M_CMD.u32Register;

        /* Wait for a completion event from the master or slave */
        do
        {
            locStatus = ((CY_SCB_I2C_MASTER_TX_BYTE_DONE & Cy_SCB_GetMasterInterruptStatus(base)) |
                         (CY_SCB_I2C_SLAVE_ADDR_DONE & Cy_SCB_GetSlaveInterruptStatus(base)));

            locStatus |= WaitOneUnit(&timeout);

        } while (0ul == locStatus);

        retStatus = HandleStatus(base, locStatus, context);
    }

    /* Enable I2C slave interrupt sources */
    Cy_SCB_SetSlaveInterruptMask(base, CY_SCB_I2C_SLAVE_INTR);

    return (retStatus);
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_MasterSendReStart
****************************************************************************//**
*
* Generates a ReStart condition and sends a slave address with the Read/Write
* bit.
* This function is blocking and it does not return until the ReStart condition
* and address byte are sent and an ACK/NAK is received, an error or timeout
* occurred.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param address
* A 7-bit right-justified slave address.
*
* \param bitRnW
* This sets the value of the Read/Write bit in the address, thus defining
* the direction of the following transfer.
* See \ref group_scb_i2c_macro_direction for the set of constants.
*
* \param timeoutMs
* Defines in milliseconds the time that this function can block for.
* If that time expires, the function returns. If a zero is passed,
* the function waits forever for the action to complete. If a timeout occurs,
* the SCB block is reset. Note The maximum value is sizeof(uint32_t)/1000.
*
* \param context
* The pointer to the context structure \ref cy_stc_scb_i2c_context_t allocated
* by the user. The structure is used during the I2C operation for internal
* configuration and data keeping. The user must not modify anything
* in this structure.
*
* \return
* \ref cy_en_scb_i2c_status_t
*
* \note
* * A successful transaction must be initiated by \ref Cy_SCB_I2C_MasterSendStart
*   before calling this function. If this condition is not met, this function
*   does nothing and returns \ref CY_SCB_I2C_MASTER_NOT_READY.
* * After a Read transaction is initiated and the slave ACKs the address,
*   at least one byte must be read before completing the transaction or
*   changing its direction.
*
*******************************************************************************/
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterSendReStart(volatile stc_SCB_t *base, uint32_t address,
                                    uint32_t bitRnW, uint32_t timeoutMs,
                                    cy_stc_scb_i2c_context_t *context)
{
    cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_MASTER_NOT_READY;
    un_SCB_I2C_M_CMD_t temp_I2C_M_CMD;

    if (0ul != (CY_SCB_I2C_MASTER_ACTIVE & context->state))
    {
        uint32_t locStatus;

        /* Convert the timeout to microseconds */
        uint32_t timeout = (timeoutMs * 1000ul);

        /* Set the read or write direction */
        context->state = CY_SCB_I2C_MASTER_ADDR;
        context->masterRdDir = (CY_SCB_I2C_READ_XFER == bitRnW);

        /* Generate a restart (for write direction) and NACK plus restart for the Read direction */
        temp_I2C_M_CMD.u32Register        = 0ul;
        temp_I2C_M_CMD.stcField.u1M_START = 1ul;
        temp_I2C_M_CMD.stcField.u1M_NACK  = ((base->unI2C_STATUS.stcField.u1M_READ) ? 1ul : 0ul);
        base->unI2C_M_CMD.u32Register     = temp_I2C_M_CMD.u32Register;

        /* Send the address byte */
        //Cy_SCB_WriteTxFifo(base, (_VAL2FLD(CY_SCB_I2C_ADDRESS, address) | bitRnW));
        Cy_SCB_WriteTxFifo(base,((((uint32_t)(address) << 1ul) & CY_SCB_I2C_ADDRESS_Msk) | bitRnW));

        /* Wait for a completion event from the or slave */
        do
        {
            locStatus = ((CY_SCB_I2C_MASTER_TX_BYTE_DONE & Cy_SCB_GetMasterInterruptStatus(base)) |
                         (CY_SCB_I2C_SLAVE_ADDR_DONE & Cy_SCB_GetSlaveInterruptStatus(base)));

            locStatus |= WaitOneUnit(&timeout);

        } while (0ul == locStatus);

        /* Convert the status from register plus timeout to the API status */
        retStatus = HandleStatus(base, locStatus, context);
    }

    return (retStatus);
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_MasterSendStop
****************************************************************************//**
*
* Generates a Stop condition to complete the current transaction.
* This function is blocking and it does not return until the Stop condition
* is generated, an error occurred or timeout occurred.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param timeoutMs
* Defines in milliseconds the time that this function can block for.
* If that time expires, the function returns. If a zero is passed,
* the function waits forever for the action to complete. If a timeout occurs,
* the SCB block is reset. Note The maximum value is sizeof(uint32_t)/1000.
*
* \param context
* The pointer to the context structure \ref cy_stc_scb_i2c_context_t allocated
* by the user. The structure is used during the I2C operation for internal
* configuration and data keeping. The user must not modify anything
* in this structure.
*
* \return
* \ref cy_en_scb_i2c_status_t
*
* \note
* * A successful transaction must be initiated by
*   \ref Cy_SCB_I2C_MasterSendStart or \ref Cy_SCB_I2C_MasterSendReStart
*   before calling this function. If this condition is not met, this function
*   does nothing and returns.
*   \ref CY_SCB_I2C_MASTER_NOT_READY.
* * Even after the slave NAKs the address, this function has to be called
*   to complete the transaction.
*
*******************************************************************************/
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterSendStop(volatile stc_SCB_t *base,uint32_t timeoutMs,
                                cy_stc_scb_i2c_context_t *context)
{
    cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_MASTER_NOT_READY;
    un_SCB_I2C_M_CMD_t temp_I2C_M_CMD;

    if (0ul != (CY_SCB_I2C_MASTER_ACTIVE & context->state))
    {
        uint32_t locStatus;

        /* Convert the timeout to microseconds */
        uint32_t timeout = (timeoutMs * 1000ul);

        /* Generate a stop (for Write direction) and NACK plus stop for the Read direction */
        temp_I2C_M_CMD.u32Register       = 0ul;
        temp_I2C_M_CMD.stcField.u1M_STOP = 1ul;
        temp_I2C_M_CMD.stcField.u1M_NACK = 1ul;
        base->unI2C_M_CMD.u32Register    = temp_I2C_M_CMD.u32Register;

        /* Wait for a completion event from the master or slave */
        do
        {
            locStatus = (CY_SCB_I2C_MASTER_STOP_DONE & Cy_SCB_GetMasterInterruptStatus(base));

            locStatus |= WaitOneUnit(&timeout);

        } while (0ul == locStatus);

        /* Convert the status from register plus timeout to the API status */
        retStatus = HandleStatus(base, locStatus, context);
    }

    return (retStatus);
}

cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterSendWriteStop(volatile stc_SCB_t *base,uint32_t timeoutMs,
                                cy_stc_scb_i2c_context_t *context)
{
    cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_MASTER_NOT_READY;

    if (0ul != (CY_SCB_I2C_MASTER_ACTIVE & context->state))
    {
        uint32_t locStatus;

        /* Convert the timeout to microseconds */
        uint32_t timeout = (timeoutMs * 1000ul);

        /* Generate a stop for Write direction */
        base->unI2C_M_CMD.stcField.u1M_STOP = 1ul;

        /* Wait for a completion event from the master or slave */
        do
        {
            locStatus = (CY_SCB_I2C_MASTER_STOP_DONE & Cy_SCB_GetMasterInterruptStatus(base));

            locStatus |= WaitOneUnit(&timeout);

        } while (0ul == locStatus);

        /* Convert the status from register plus timeout to the API status */
        retStatus = HandleStatus(base, locStatus, context);
    }

    return (retStatus);
}

cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterSendReadStop(volatile stc_SCB_t *base,uint32_t timeoutMs,
                                cy_stc_scb_i2c_context_t *context)
{
    cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_MASTER_NOT_READY;

    if (0ul != (CY_SCB_I2C_MASTER_ACTIVE & context->state))
    {
        uint32_t locStatus;

        /* Convert the timeout to microseconds */
        uint32_t timeout = (timeoutMs * 1000ul);

        /* Generate a NACK plus for the Read direction */
        base->unI2C_M_CMD.stcField.u1M_NACK = 1ul;

        /* Wait for a completion event from the master or slave */
        do
        {
            locStatus = (CY_SCB_I2C_MASTER_STOP_DONE & Cy_SCB_GetMasterInterruptStatus(base));

            locStatus |= WaitOneUnit(&timeout);

        } while (0ul == locStatus);

        /* Convert the status from register plus timeout to the API status */
        retStatus = HandleStatus(base, locStatus, context);
    }

    return (retStatus);
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_MasterReadByte
****************************************************************************//**
*
* Reads one byte from a slave and generates an ACK or prepares to generate
* a NAK. The NAK will be generated before a Stop or ReStart condition by
* \ref Cy_SCB_I2C_MasterSendStop or \ref Cy_SCB_I2C_MasterSendReStart function
* appropriately.
* This function is blocking and it does not return until a byte is
* received, an error occurred or timeout occurred.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param ackNack
* A response to a received byte.
* See \ref group_scb_i2c_macro_ack_nack for the set of constants.
*
* \param byte
* The pointer to the location to store the Read byte.
*
* \param timeoutMs
* Defines in milliseconds the time that this function can block for.
* If that time expires, the function returns. If a zero is passed,
* the function waits forever for the action to complete. If a timeout occurs,
* the SCB block is reset. Note The maximum value is sizeof(uint32_t)/1000.
*
* \param context
* The pointer to the context structure \ref cy_stc_scb_i2c_context_t allocated
* by the user. The structure is used during the I2C operation for internal
* configuration and data keeping. The user must not modify anything
* in this structure.
*
* \return
* \ref cy_en_scb_i2c_status_t
*
* \note
* A successful transaction must be initiated by \ref Cy_SCB_I2C_MasterSendStart
* or \ref Cy_SCB_I2C_MasterSendReStart before calling this function. If this
* condition is not met, this function does nothing and returns
* \ref CY_SCB_I2C_MASTER_NOT_READY.
*
*******************************************************************************/
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterReadByte(volatile stc_SCB_t *base, uint32_t ackNack,
                                uint8_t *byte, uint32_t timeoutMs,
                                cy_stc_scb_i2c_context_t *context)
{
    cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_MASTER_NOT_READY;
    un_SCB_I2C_M_CMD_t temp_I2C_M_CMD;

    if (CY_SCB_I2C_MASTER_RX0 == context->state)
    {
        bool rxEmpty;

        uint32_t locStatus;

        /* Convert the timeout to microseconds */
        uint32_t timeout = (timeoutMs * 1000ul);

        /* Wait for ACK/NAK transmission and data byte reception */
        do
        {
            locStatus = (CY_SCB_I2C_MASTER_RX_BYTE_DONE & Cy_SCB_GetMasterInterruptStatus(base));
            rxEmpty   = (0ul == (CY_SCB_RX_INTR_NOT_EMPTY & Cy_SCB_GetRxInterruptStatus(base)));

            locStatus |= WaitOneUnit(&timeout);

        } while ((rxEmpty) && (0ul == locStatus));

        /* The Read byte if available */
        if (!rxEmpty)
        {
            /* Get the received data byte */
            *byte = (uint8_t) Cy_SCB_ReadRxFifo(base);

            Cy_SCB_ClearRxInterrupt(base, CY_SCB_RX_INTR_NOT_EMPTY | CY_SCB_RX_INTR_LEVEL);
        }

        /* Convert the status from register plus timeout to the API status */
        retStatus = HandleStatus(base, locStatus, context);

        if (CY_SCB_I2C_SUCCESS == retStatus)
        {
            /* Generate ACK or wait for NAK generation */
            if (CY_SCB_I2C_ACK == ackNack)
            {
                temp_I2C_M_CMD.u32Register      = 0ul;
                temp_I2C_M_CMD.stcField.u1M_ACK = 1ul;
                base->unI2C_M_CMD.u32Register   = temp_I2C_M_CMD.u32Register;
            }
        }
    }

    return (retStatus);
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_MasterWriteByte
****************************************************************************//**
*
* Sends one byte to a slave.
* This function is blocking and it does not return until a byte is
* transmitted, an error occurred or timeout occurred.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param theByte
* The byte to write to a slave.
*
* \param timeoutMs
* Defines in milliseconds the time that this function can block for.
* If that time expires, the function returns. If a zero is passed,
* the function waits forever for the action to complete. If a timeout occurs,
* the SCB block is reset. Note The maximum value is sizeof(uint32_t)/1000.
*
* \param context
* The pointer to the context structure \ref cy_stc_scb_i2c_context_t allocated
* by the user. The structure is used during the I2C operation for internal
* configuration and data keeping. The user must not modify anything
* in this structure.
*
* \return
* \ref cy_en_scb_i2c_status_t
*
* \note
* A successful transaction must be initiated by \ref Cy_SCB_I2C_MasterSendStart
* or \ref Cy_SCB_I2C_MasterSendReStart before calling this function. If this
* condition is not met, this function does nothing and returns
* \ref CY_SCB_I2C_MASTER_NOT_READY.
*
*******************************************************************************/
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterWriteByte(volatile stc_SCB_t *base, uint8_t theByte,
                                    uint32_t timeoutMs,
                                    cy_stc_scb_i2c_context_t *context)
{
    cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_MASTER_NOT_READY;

    if (CY_SCB_I2C_MASTER_TX == context->state)
    {
        uint32_t locStatus;

        /* Convert the timeout to microseconds */
        uint32_t timeout = (timeoutMs * 1000ul);

        /* Send the data byte */
        Cy_SCB_WriteTxFifo(base, (uint32_t) theByte);

        /* Wait for a completion event from the master or slave */
        do
        {
            locStatus  = (CY_SCB_I2C_MASTER_TX_BYTE_DONE & Cy_SCB_GetMasterInterruptStatus(base));
            locStatus |= WaitOneUnit(&timeout);

        } while (0ul == locStatus);

        /* Convert the status from register plus timeout to the API status */
        retStatus = HandleStatus(base, locStatus, context);
    }

    return (retStatus);
}

									
/*******************************************************************************
* Function Name: Cy_SysLib_DelayUs
****************************************************************************//**
*
* The function delays by the specified number of microseconds.
* By default, the number of cycles to delay is calculated based on the
* \ref SystemCoreClock.
*
* \param microseconds  The number of microseconds to delay.
*
* \note If the CPU frequency is a small non-integer number, the actual delay
*       can be up to twice as long as the nominal value. The actual delay
*       cannot be shorter than the nominal one.
*
*******************************************************************************/
void Cy_DelayUs(uint16_t microseconds)
{
    uint32_t cy_delayFreqMhz  = 160UL;

    Cy_DelayCycles((uint32_t) microseconds * cy_delayFreqMhz);
}


/******************************************************************************
* Function Name: WaitOneUnit
****************************************************************************//**
*
* Waits for one unit before unblock code execution.
* Note If a timeout value is 0, this function does nothing and returns 0.
*
* \param timeout
* The pointer to a timeout value.
*
* \return
* Returns 0 if a timeout does not expire or the timeout mask.
*
*******************************************************************************/
static uint32_t WaitOneUnit(uint32_t *timeout)
{
    uint32_t status = 0ul;

    /* If the timeout equal to 0. Ignore the timeout */
    if (*timeout > 0ul)
    {
        Cy_DelayUs(CY_SCB_WAIT_1_UNIT);
        --(*timeout);

        if (0ul == *timeout)
        {
            status = CY_SCB_I2C_MASTER_TIMEOUT_DONE;
        }
    }

    return (status);
}


/******************************************************************************
* Function Name: HandleStatus
****************************************************************************//**
*
* Converts passed status into the cy_en_scb_i2c_status_t.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param status
* The status to covert.
*
* \return
* \ref cy_en_scb_i2c_status_t
*
*******************************************************************************/
static cy_en_scb_i2c_status_t HandleStatus(volatile stc_SCB_t *base, uint32_t status, cy_stc_scb_i2c_context_t *context)
{
    bool resetBlock = false;
    cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_MASTER_MANUAL_TIMEOUT;

    /* Convert the master status to the API status */
    if (0ul != (CY_SCB_I2C_MASTER_TIMEOUT_DONE & status))
    {
        resetBlock = true;
    }
    else if (0ul != (CY_SCB_I2C_SLAVE_ADDR_DONE & status))
    {
        if (0ul != base->unI2C_M_CMD.u32Register)
        {
            /* Abort the master operation, the slave was addressed first */
            retStatus = CY_SCB_I2C_MASTER_MANUAL_ABORT_START;

            base->unI2C_M_CMD.u32Register = 0ul;
            context->state = CY_SCB_I2C_IDLE;
        }
    }
    else if (0ul != (CY_SCB_MASTER_INTR_I2C_BUS_ERROR & status))
    {
        retStatus = CY_SCB_I2C_MASTER_MANUAL_BUS_ERR;
        resetBlock = true;
    }
    else if (0ul != (CY_SCB_MASTER_INTR_I2C_ARB_LOST & status))
    {
        retStatus = CY_SCB_I2C_MASTER_MANUAL_ARB_LOST;

        if (CY_SCB_I2C_MASTER_ADDR == context->state)
        {
            /* This is the address phase:
            *  1. Master mode: Reset IP when "arbitration lost" occurred.
            *  2. Master-Slave mode: If "lost arbitration" occurred, the slave
            *  can be addressed to let the slave accept the address; do not
            *  reset IP.
            */
            resetBlock = !(base->unI2C_CTRL.stcField.u1SLAVE_MODE);

            context->state = CY_SCB_I2C_IDLE;
        }
        else
        {
            resetBlock = true;
        }
    }
    else if (0ul != (CY_SCB_MASTER_INTR_I2C_NACK & status))
    {
        /* An address or data was NAKed */
        retStatus = (CY_SCB_I2C_MASTER_ADDR == context->state) ?
                     CY_SCB_I2C_MASTER_MANUAL_ADDR_NAK : CY_SCB_I2C_MASTER_MANUAL_NAK;
    }
    else if (0ul != (CY_SCB_MASTER_INTR_I2C_STOP & status))
    {
        /* No errors - end of transaction detected */
        retStatus = CY_SCB_I2C_SUCCESS;

        context->state = CY_SCB_I2C_IDLE;
    }
    else /* No errors - continue transaction */
    {
        retStatus = CY_SCB_I2C_SUCCESS;

        /* The change state */
        if (CY_SCB_I2C_MASTER_ADDR == context->state)
        {
            context->state = (context->masterRdDir) ?
                                CY_SCB_I2C_MASTER_RX0 : CY_SCB_I2C_MASTER_TX;
        }
    }

    if (resetBlock)
    {
        /* A block reset clears all interrupt sources */
        Cy_SCB_FwBlockReset(base);

        context->state = CY_SCB_I2C_IDLE;
    }
    else
    {
        Cy_SCB_ClearMasterInterrupt(base, CY_SCB_I2C_MASTER_INTR_ALL);
    }

    return (retStatus);
}



/* [] END OF FILE */

