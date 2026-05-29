/***************************************************************************//**
* \file cy_scb_common.h
*
* Provides common API declarations of the SCB driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

/**
* \defgroup group_scb Serial Communication Block (SCB)
* \{
* \defgroup group_scb_common Common
* \defgroup group_scb_ezi2c  EZI2C (SCB)
* \defgroup group_scb_i2c    I2C (SCB)
* \defgroup group_scb_spi    SPI (SCB)
* \defgroup group_scb_uart   UART (SCB)
* \} */

/**
* \addtogroup group_scb_common
* \{
*
* Common API for the Serial Communication Block.
*
* This is the common API that provides an interface to the SCB hardware.
* The I2C, SPI, and UART drivers use this common API.
* Most users will use individual drivers and do not need to use the common
* API for the SCB. However, you can use the common SCB API to implement
* a custom driver based on the SCB hardware.
*
* \section group_scb_common_configuration Configuration Considerations
*
* This is not a driver and it does not require configuration.
*
* \section group_scb_common_more_information More Information
*
* Refer to the SCB chapter of the technical reference manual (TRM).
*
* \section group_scb_common_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_scb_common_macro Macro
* \defgroup group_scb_common_functions Functions
* \defgroup group_scb_common_data_structures Data Structures
*
*/

#if !defined(CY_SCB_COMMON_H)
#define CY_SCB_COMMON_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "cyip_scb_v2.h"

#include "WPCVehicleOption.h"

/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_scb_common_functions
* \{
*/
static inline uint32_t Cy_SCB_ReadRxFifo    (volatile stc_SCB_t const *base);
static inline uint32_t Cy_SCB_GetNumInRxFifo(volatile stc_SCB_t const *base);

static inline void     Cy_SCB_WriteTxFifo   (volatile stc_SCB_t *base, uint32_t data);
static inline uint32_t Cy_SCB_GetNumInTxFifo(volatile stc_SCB_t const *base);
static inline void     Cy_SCB_ClearTxFifo   (volatile stc_SCB_t *base);

static inline uint32_t Cy_SCB_GetRxInterruptStatus(volatile stc_SCB_t const *base);
static inline void     Cy_SCB_ClearRxInterrupt    (volatile stc_SCB_t *base, uint32_t interruptMask);
static inline void     Cy_SCB_ClearRxFifo   (volatile stc_SCB_t *base);

static inline uint32_t Cy_SCB_GetMasterInterruptStatus(volatile stc_SCB_t const *base);
static inline void     Cy_SCB_ClearMasterInterrupt    (volatile stc_SCB_t *base, uint32_t interruptMask);

static inline uint32_t Cy_SCB_GetSlaveInterruptStatus(volatile stc_SCB_t const *base);
static inline void     Cy_SCB_SetSlaveInterruptMask  (volatile stc_SCB_t *base, uint32_t interruptMask);

/***************************************
*     Internal Function Prototypes
***************************************/

/** \cond INTERNAL */
static inline void     Cy_SCB_FwBlockReset(volatile stc_SCB_t *base);
/** \endcond */

/** \} group_scb_common_functions */

/***************************************
*            API Constants
***************************************/

/**
* \addtogroup group_scb_common_macro
* \{
*/

/** Driver major version */
#define CY_SCB_DRV_VERSION_MAJOR    (1)

/** Driver minor version */
#define CY_SCB_DRV_VERSION_MINOR    (0)

#define CY_PDL_STATUS_TYPE_Pos  (16u)       /**< The status type position in the status code */
#define CY_PDL_MODULE_ID_Pos    (18u)       /**< The software module ID position in the status code */
#define CY_PDL_STATUS_ERROR     (2UL << CY_PDL_STATUS_TYPE_Pos)    /**< Error status type */
#define CY_PDL_MODULE_ID_Msk    (0x3FFFu)   /**< The software module ID mask */
#define CY_PDL_DRV_ID(id)       ((uint32_t)((uint32_t)((id) & CY_PDL_MODULE_ID_Msk) << CY_PDL_MODULE_ID_Pos))

/** SCB driver identifier */
#define CY_SCB_ID   CY_PDL_DRV_ID(0x2Au)

/** Position for SCB driver sub mode */
#define CY_SCB_SUB_MODE_Pos (13ul)

/** I2C mode identifier */
#define CY_SCB_I2C_ID       (0x1ul << CY_SCB_SUB_MODE_Pos)

/**
* \defgroup group_scb_common_macro_intr_cause SCB Interrupt Causes
* \{
*/
/** \} group_scb_common_macro_intr_cause */

/**
* \defgroup group_scb_common_macro_tx_intr TX Interrupt Statuses
* \{
*/
/** \} group_scb_common_macro_tx_intr */

/**
* \defgroup group_scb_common_macro_rx_intr RX Interrupt Statuses
* \{
*/
/**
* The number of data elements in the RX FIFO is greater than the value of the
* RX FIFO level
*/
#define CY_SCB_RX_INTR_LEVEL             SCB_INTR_RX_TRIGGER_Msk

/** The RX FIFO is not empty */
#define CY_SCB_RX_INTR_NOT_EMPTY         SCB_INTR_RX_NOT_EMPTY_Msk
/** \} group_scb_common_macro_rx_intr */

/**
* \defgroup group_scb_common_macro_slave_intr Slave Interrupt Statuses
* \{
*/
/**
* I2C slave lost arbitration: the value driven on the SDA line is not the same
* as the value observed on the SDA line
*/
#define CY_SCB_SLAVE_INTR_I2C_ARB_LOST      SCB_INTR_S_I2C_ARB_LOST_Msk

/** A Stop or Repeated Start event intended for this slave was detected */
#define CY_SCB_SLAVE_INTR_I2C_STOP          SCB_INTR_S_I2C_STOP_Msk

/** The I2C slave received the matching address */
#define CY_SCB_SLAVE_INTR_I2C_ADDR_MATCH    SCB_INTR_S_I2C_ADDR_MATCH_Msk

/** The I2C Slave received the general call address */
#define CY_SCB_SLAVE_INTR_I2C_GENERAL_ADDR  SCB_INTR_S_I2C_GENERAL_Msk

/** The I2C slave bus error (detection of unexpected Start or Stop condition) */
#define CY_SCB_SLAVE_INTR_I2C_BUS_ERROR     SCB_INTR_S_I2C_BUS_ERROR_Msk

/** \} group_scb_common_macro_slave_intr */

/**
* \defgroup group_scb_common_macro_master_intr Master Interrupt Statuses
* \{
*/
/** The I2C master's lost arbitration */
#define CY_SCB_MASTER_INTR_I2C_ARB_LOST    SCB_INTR_M_I2C_ARB_LOST_Msk

/** The I2C master received a NACK */
#define CY_SCB_MASTER_INTR_I2C_NACK        SCB_INTR_M_I2C_NACK_Msk

/** The I2C master received an ACK */
#define CY_SCB_MASTER_INTR_I2C_ACK         SCB_INTR_M_I2C_ACK_Msk

/** The I2C master generated a Stop */
#define CY_SCB_MASTER_INTR_I2C_STOP        SCB_INTR_M_I2C_STOP_Msk

/** The I2C master bus error (detection of unexpected START or STOP condition)
*/
#define CY_SCB_MASTER_INTR_I2C_BUS_ERROR   SCB_INTR_M_I2C_BUS_ERROR_Msk
/** \} group_scb_common_macro_master_intr */

/**
* \defgroup group_scb_common_macro_i2c_intr I2C Interrupt Statuses
* \{
*/
/** \} group_scb_common_macro_i2c_intr */

/**
* \defgroup group_scb_common_macro_SpiIntrStatuses SPI Interrupt Statuses
* \{
*/
/** \} group_scb_common_macro_SpiIntrStatuses */


/***************************************
*         Internal Constants
***************************************/

/** \cond INTERNAL */

/* Default registers values */
#define CY_SCB_CTRL_DEF_VAL         (0x0300000Ful)
#define CY_SCB_I2C_CTRL_DEF_VAL     (0x00003F88ul)
#define CY_SCB_I2C_CFG_DEF_VAL      (0x002A1013ul)
#define CY_SCB_RX_CTRL_DEF_VAL      (0x00000107ul)
#define CY_SCB_TX_CTRL_DEF_VAL      (0x00000107ul)

/* SCB CTRL modes */
#define CY_SCB_CTRL_MODE_I2C   (0ul)

/* I2C has fixed data width */
#define CY_SCB_I2C_DATA_WIDTH   (7ul)

/* RX and TX control register values */

/* The position and mask to make an address byte */
#define CY_SCB_I2C_ADDRESS_Pos  (1ul)
#define CY_SCB_I2C_ADDRESS_Msk  (0xFEul)

/* Max number of bits for byte mode */

/* Single unit to wait */
#define CY_SCB_WAIT_1_UNIT  (1u)

/* Clear interrupt sources */
#define CY_SCB_CLEAR_ALL_INTR_SRC   (0ul)

/* Hardware FIFO size */
#define CY_SCB_FIFO_SIZE    (128ul)
/** \endcond */

/** \} group_scb_common_macro */
/**
  \brief   Mask and shift a bit field value for use in a register bit range.
  \param[in] field  Name of the register bit field.
  \param[in] value  Value of the bit field. This parameter is interpreted as an uint32_t type.
  \return           Masked and shifted value.
*/
//#define _VAL2FLD(field, value)    (((uint32_t)(value) << field ## _Pos) & field ## _Msk)


/***************************************
* Inline Function Implementation
***************************************/

/**
* \addtogroup group_scb_common_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_SCB_ReadRxFifo
****************************************************************************//**
*
* Reads a data element directly out of the RX FIFO.
* This function does not check if the RX FIFO has data before reading it.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* Data from RX FIFO.
*
*******************************************************************************/
static inline uint32_t Cy_SCB_ReadRxFifo(volatile stc_SCB_t const *base)
{
    return (base->unRX_FIFO_RD.u32Register);
}


/*******************************************************************************
* Function Name: Cy_SCB_GetNumInRxFifo
****************************************************************************//**
*
* Returns the number of data elements currently in the RX FIFO.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The number or data elements in RX FIFO.
*
*******************************************************************************/
static inline uint32_t Cy_SCB_GetNumInRxFifo(volatile stc_SCB_t const *base)
{
    return (base->unRX_FIFO_STATUS.stcField.u9USED);
}


/*******************************************************************************
* Function Name: Cy_SCB_WriteTxFifo
****************************************************************************//**
*
* Writes data directly into the TX FIFO.
* This function does not check if the TX FIFO is not full before writing
* into it.
*
* \param base
* The pointer to the SCB instance.
*
* \param data
* Data to write to the TX FIFO.
*
*******************************************************************************/
static inline void Cy_SCB_WriteTxFifo(volatile stc_SCB_t* base, uint32_t data)
{
    base->unTX_FIFO_WR.u32Register = data;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetNumInTxFifo
****************************************************************************//**
*
* Returns the number of data elements currently in the TX FIFO.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The number or data elements in the TX FIFO.
*
*******************************************************************************/
static inline uint32_t Cy_SCB_GetNumInTxFifo(volatile stc_SCB_t const *base)
{
    return (base->unTX_FIFO_STATUS.stcField.u9USED);
}


/*******************************************************************************
* Function Name: Cy_SCB_ClearTxFifo
****************************************************************************//**
*
* Clears the TX FIFO.
*
* \param base
* The pointer to the SCB instance.
*
* \note
* The TX FIFO clear operation also clears the shift register, thus the shifter
* could be cleared in the middle of a data element transfer; resulting in
* "ones" being sent on the bus for the remainder of the transfer.
*
*******************************************************************************/
static inline void Cy_SCB_ClearTxFifo(volatile stc_SCB_t *base)
{
    base->unTX_FIFO_CTRL.stcField.u1CLEAR = 1ul;
    base->unTX_FIFO_CTRL.stcField.u1CLEAR = 0ul;
    (void) base->unTX_FIFO_CTRL.u32Register;
}

/*******************************************************************************
* Function Name: Cy_SCB_ClearRxFifo
****************************************************************************//**
*
* Clears the RX FIFO.
*
* \param base
* The pointer to the SCB instance.
*
*******************************************************************************/
static inline void Cy_SCB_ClearRxFifo(volatile stc_SCB_t *base)
{
    base->unRX_FIFO_CTRL.stcField.u1CLEAR = 1ul;
    base->unRX_FIFO_CTRL.stcField.u1CLEAR = 0ul;
    (void) base->unRX_FIFO_CTRL.u32Register;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetRxInterruptStatus
****************************************************************************//**
*
* Returns the RX interrupt request register. This register contains the current
* status of the RX interrupt sources.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of the RX interrupt sources. Each constant is a bit field
* value. The value returned may have multiple bits set to indicate the
* current status.
* See \ref group_scb_common_macro_rx_intr for the set of constants.
*
*******************************************************************************/
static inline uint32_t Cy_SCB_GetRxInterruptStatus(volatile stc_SCB_t const *base)
{
    return (base->unINTR_RX.u32Register);
}


/*******************************************************************************
* Function Name: Cy_SCB_ClearRxInterrupt
****************************************************************************//**
*
* Clears the RX interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The RX interrupt sources to be cleared.
* See \ref group_scb_common_macro_rx_intr for the set of constants.
*
* \note
*  - CY_SCB_INTR_RX_FIFO_LEVEL interrupt source is not cleared when
*    the RX FIFO has more entries than the level.
*  - CY_SCB_INTR_RX_NOT_EMPTY interrupt source is not cleared when the
*    RX FIFO is not empty.
*  - CY_SCB_INTR_RX_FULL interrupt source is not cleared when the
*    RX FIFO is full.
*
*******************************************************************************/
static inline void Cy_SCB_ClearRxInterrupt(volatile stc_SCB_t *base, uint32_t interruptMask)
{
    base->unINTR_RX.u32Register = interruptMask;
    (void) base->unINTR_RX.u32Register;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetMasterInterruptStatus
****************************************************************************//**
*
* Returns the master interrupt request register. This register contains the current
* status of the master interrupt sources.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of the master interrupt sources.
* Each constant is a bit field value. The value returned may have multiple
* bits set to indicate the current status.
* See \ref group_scb_common_macro_master_intr for the set of constants.
*
*******************************************************************************/
static inline uint32_t Cy_SCB_GetMasterInterruptStatus (volatile stc_SCB_t const *base)
{
    return (base->unINTR_M.u32Register);
}


/*******************************************************************************
* Function Name: Cy_SCB_ClearMasterInterrupt
****************************************************************************//**
*
* Clears master interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The master interrupt sources to be cleared.
* See \ref group_scb_common_macro_master_intr for the set of constants.
*
*******************************************************************************/
static inline void Cy_SCB_ClearMasterInterrupt(volatile stc_SCB_t *base, uint32_t interruptMask)
{
    base->unINTR_M.u32Register = interruptMask;
    (void) base->unINTR_M.u32Register;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetSlaveInterruptStatus
****************************************************************************//**
*
* Returns the slave interrupt request register. This register contains the current
* status of the slave interrupt sources.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of the slave interrupt sources.
* Each constant is a bit field value. The value returned may have multiple
* bits set to indicate the current status.
* See \ref group_scb_common_macro_slave_intr for the set of constants.
*
*******************************************************************************/
static inline uint32_t Cy_SCB_GetSlaveInterruptStatus(volatile stc_SCB_t const *base)
{
    return (base->unINTR_S.u32Register);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetSlaveInterruptMask
****************************************************************************//**
*
* Writes slave interrupt mask register.
* This register specifies which bits from the slave interrupt request register
* can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* Enabled slave interrupt sources.
* See \ref group_scb_common_macro_slave_intr for the set of constants.
*
*******************************************************************************/
static inline void Cy_SCB_SetSlaveInterruptMask(volatile stc_SCB_t *base, uint32_t interruptMask)
{
    base->unINTR_S_MASK.u32Register = interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SCB_FwBlockReset
****************************************************************************//**
*
* Disables and enables the block to return it into the known state (default):
* FIFOs and interrupt statuses are cleared.
*
* \param base
* The pointer to the SCB instance.
*
*******************************************************************************/
static inline void Cy_SCB_FwBlockReset(volatile stc_SCB_t *base)
{
    base->unCTRL.stcField.u1ENABLED = 0ul;

    /* Clean-up command registers */
    base->unI2C_M_CMD.u32Register = 0ul;
    base->unI2C_S_CMD.u32Register = 0ul;

    base->unCTRL.stcField.u1ENABLED = 1ul;

    (void) base->unCTRL.u32Register;
}

/** \} group_scb_common_functions */
/** \} group_scb_common */

#endif /* (CY_SCB_COMMON_H) */


/* [] END OF FILE */

