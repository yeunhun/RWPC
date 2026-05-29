/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/
/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WPCVehicleOption.h"
#include "Slpwup_LPT_Callout.h"
#include "SlpWup.h"
#include "Rte_Type.h"
#include "data.h"
#include "define.h"
#include "EcuM_Cbk.h"

#define ECUM_START_SEC_CALLOUT_CODE
#include "MemMap.h"

/*****************************************************************************/
/* function definitions                                 */
/*****************************************************************************/
void CyclicWakeup_Adc_Init(void);
void Start_WdgService_CyclicWakeUp(void);
void Stop_WdgService_CyclicWakeUp(void);
/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/
#define WDG_TYPE_BASIC    0
#define WDG_TYPE_MCWDT    1
#define WDG_TYPE      WDG_TYPE_MCWDT

/**********MCWDT****************/
#define CY_MCWDT_LOCK_CLR0      (1ul)
#define CY_MCWDT_LOCK_CLR1      (2ul)
#define CY_MCWDT_LOCK_SET01     (3ul)

#define CY_MCWDT_CTR0_Pos (0ul)
#define CY_MCWDT_CTR1_Pos (1ul)
#define CY_MCWDT_CTR2_Pos (2ul)

#define CY_MCWDT_CTR0     (1ul << CY_MCWDT_CTR0_Pos)                /**< The sub-counter#0 mask. This macro is used with functions
                                                                   that handle multiple counters, including Cy_MCWDT_Enable(),
                                                                   Cy_MCWDT_Disable(), Cy_MCWDT_ClearInterrupt() and Cy_MCWDT_ResetCounters(). */
#define CY_MCWDT_CTR1     (1ul << CY_MCWDT_CTR1_Pos)                /**< The sub-counter#1 mask. This macro is used with functions
                                                                   that handle multiple counters, including Cy_MCWDT_Enable(),
                                                                   Cy_MCWDT_Disable(), Cy_MCWDT_ClearInterrupt() and Cy_MCWDT_ResetCounters(). */
#define CY_MCWDT_CTR2     (1ul << CY_MCWDT_CTR2_Pos)                /**< The sub-counter#2 mask. This macro is used with functions
                                                                   that handle multiple counters, including Cy_MCWDT_Enable(),
                                                                   Cy_MCWDT_Disable(), Cy_MCWDT_ClearInterrupt() and Cy_MCWDT_ResetCounters(). */

#define CY_MCWDT_NUM_OF_SUBCOUNTER      (2ul)

#define TIMEOUT_VALUE   3277UL// 100ms = 3277, 50ms = 1638, 1 sec = 32768 when clk_lf = 32.768KHz
#define TestOFF  0
#define TestON   1
#define Test_ADC TestON
#define Test_ExecutionCTR     TestON
#define Test_WDGSET    TestON

/*****************************************************************************/
/* local variable definitions                                 */
/*****************************************************************************/
//uint8 P009_3Level=0; //Toggle for Cyclic wakeup checkup

/*****************************************************************************/
/* Global variable definitions                                 */
/*****************************************************************************/
extern uint8 wakeUpSource;


/*******************************************************************************
* Function Name: Cy_Adc_Channel_SoftwareTrigger
****************************************************************************//**
*
* \brief  Issue software start trigger.
*
* \param  base: Pointer to the hardware SAR channel block.
*
* \return None
*
*******************************************************************************/
void Cy_Adc_Channel_SoftwareTrigger(volatile stc_PASS_SAR_CH_t * base)
{
    base->unTR_CMD.stcField.u1START = 1u;
}

/*******************************************************************************
* Function Name: Cy_Adc_Channel_GetInterruptStatus
****************************************************************************/
cy_en_adc_status_t Cy_Adc_Channel_GetInterruptStatus(const volatile stc_PASS_SAR_CH_t * base, cy_stc_adc_interrupt_source_t * status)
{
    cy_en_adc_status_t ret = CY_ADC_SUCCESS;
    un_PASS_SAR_CH_INTR_t unStat;

    if (NULL != status)
    {
        unStat.u32Register = base->unINTR.u32Register;
        status->chOverflow = (unStat.stcField.u1CH_OVERFLOW != 0) ? true : false;
        status->chPulse = (unStat.stcField.u1CH_PULSE != 0) ? true : false;
        status->chRange = (unStat.stcField.u1CH_RANGE != 0) ? true : false;
        status->grpCancelled = (unStat.stcField.u1GRP_CANCELLED != 0) ? true : false;
        status->grpDone = (unStat.stcField.u1GRP_DONE != 0) ? true : false;
        status->grpOverflow = (unStat.stcField.u1GRP_OVERFLOW != 0) ? true : false;
    }
    else
    {
        ret = CY_ADC_BAD_PARAM;
    }
    return ret;
}


/*******************************************************************************
* Function Name: Cy_Adc_Channel_GetResult
****************************************************************************/
cy_en_adc_status_t Cy_Adc_Channel_GetResult(const volatile stc_PASS_SAR_CH_t * base, uint16_t * result, cy_stc_adc_ch_status_t * status)
{
    cy_en_adc_status_t ret = CY_ADC_SUCCESS;
    un_PASS_SAR_CH_RESULT_t value;

    if ((NULL != result) && (NULL != status))
    {
        value.u32Register = base->unRESULT.u32Register;
        *result = value.stcField.u16RESULT;
        status->aboveHi = (value.stcField.u1ABOVE_HI_MIR != 0) ? true : false;
        status->pulseIntr = (value.stcField.u1PULSE_INTR_MIR != 0) ? true : false;
        status->rangeIntr = (value.stcField.u1RANGE_INTR_MIR != 0) ? true : false;
        status->valid = (value.stcField.u1VALID_MIR != 0) ? true : false;
    }
    else
    {
        ret = CY_ADC_BAD_PARAM;
    }
    return ret;
}

/*******************************************************************************
* Function Name: Cy_Adc_Channel_ClearInterruptStatus
*******************************************************************************/
cy_en_adc_status_t Cy_Adc_Channel_ClearInterruptStatus(volatile stc_PASS_SAR_CH_t * base, const cy_stc_adc_interrupt_source_t * source)
{
    cy_en_adc_status_t ret = CY_ADC_SUCCESS;
    un_PASS_SAR_CH_INTR_t unIntr = { 0 };
    if (NULL != source)
    {
        unIntr.stcField.u1CH_OVERFLOW = source->chOverflow ? 1u : 0u;
        unIntr.stcField.u1CH_PULSE = source->chPulse ? 1u : 0u;
        unIntr.stcField.u1CH_RANGE = source->chRange ? 1u : 0u;
        unIntr.stcField.u1GRP_CANCELLED = source->grpCancelled ? 1u : 0u;
        unIntr.stcField.u1GRP_DONE = source->grpDone ? 1u : 0u;
        unIntr.stcField.u1GRP_OVERFLOW = source->grpOverflow ? 1u : 0u;
        base->unINTR.u32Register = unIntr.u32Register;
    }
    else
    {
        ret = CY_ADC_BAD_PARAM;
    }
    return ret;
}


/*******************************************************************************
* Function Name: Cy_Adc_Init
******************************************************************************/
cy_en_adc_status_t Cy_Adc_Init(volatile stc_PASS_SAR_t * base, const cy_stc_adc_config_t * config)
{
    cy_en_adc_status_t ret = CY_ADC_SUCCESS;
    un_PASS_SAR_CTL_t unSarCtl = { 0 };
    if (NULL != config)
    {
        /* CTL register setting */
        base->unPRECOND_CTL.stcField.u4PRECOND_TIME = config->preconditionTime;

        /* CTL register setting */
        unSarCtl.stcField.u8PWRUP_TIME = config->powerupTime;
        unSarCtl.stcField.u1IDLE_PWRDWN = config->enableIdlePowerDown ? 1u : 0;
        unSarCtl.stcField.u1MSB_STRETCH = config->msbStretchMode;
        unSarCtl.stcField.u1HALF_LSB = config->enableHalfLsbConv ? 1u : 0;
        unSarCtl.stcField.u1SARMUX_EN = config->sarMuxEnable ? 1u : 0;
        unSarCtl.stcField.u1ADC_EN = config->adcEnable ? 1u : 0;
        unSarCtl.stcField.u1ENABLED = config->sarIpEnable ? 1u : 0;
        base->unCTL.u32Register = unSarCtl.u32Register;
    }
    else
    {
        ret = CY_ADC_BAD_PARAM;
    }

    return ret;
}

/*******************************************************************************
* Function Name: Cy_Adc_Channel_Init
*******************************************************************************/
cy_en_adc_status_t Cy_Adc_Channel_Init(volatile stc_PASS_SAR_CH_t * base, const cy_stc_adc_channel_config_t * config)
{
    cy_en_adc_status_t ret = CY_ADC_SUCCESS;
    un_PASS_SAR_CH_TR_CTL_t unTrCtl = { 0 };
    un_PASS_SAR_CH_SAMPLE_CTL_t unSampleCtl = { 0 };
    un_PASS_SAR_CH_POST_CTL_t unPostCtl = { 0 };
    un_PASS_SAR_CH_RANGE_CTL_t unRangeCtl = { 0 };
    un_PASS_SAR_CH_INTR_t unIntr = { 0 };

    if (NULL != config)
    {
        /* At first disable the channel */
        Cy_Adc_Channel_Disable(base);
        /* Clear whole interrupt flags */
        unIntr.stcField.u1CH_OVERFLOW = 1u;
        unIntr.stcField.u1CH_PULSE = 1u;
        unIntr.stcField.u1CH_RANGE = 1u;
        unIntr.stcField.u1GRP_CANCELLED = 1u;
        unIntr.stcField.u1GRP_DONE = 1u;
        unIntr.stcField.u1GRP_OVERFLOW = 1u;
        base->unINTR.u32Register = unIntr.u32Register;

        unTrCtl.stcField.u3SEL = config->triggerSelection;
        unTrCtl.stcField.u3PRIO = config->channelPriority;
        unTrCtl.stcField.u2PREEMPT_TYPE = config->preenptionType;
        unTrCtl.stcField.u1GROUP_END = config->isGroupEnd ? 1u : 0u;
        unTrCtl.stcField.u1DONE_LEVEL = config->doneLevel ? 1u : 0u;
        base->unTR_CTL.u32Register = unTrCtl.u32Register;

        unSampleCtl.stcField.u6PIN_ADDR = config->pinAddress;
        unSampleCtl.stcField.u2PORT_ADDR = config->portAddress;
        unSampleCtl.stcField.u3EXT_MUX_SEL = config->extMuxSelect;
        unSampleCtl.stcField.u1EXT_MUX_EN = config->extMuxEnable ? 1u : 0u;
        unSampleCtl.stcField.u2PRECOND_MODE = config->preconditionMode;
        unSampleCtl.stcField.u2OVERLAP_DIAG = config->overlapDiagMode;
        unSampleCtl.stcField.u12SAMPLE_TIME = config->sampleTime;
        unSampleCtl.stcField.u1ALT_CAL = config->calibrationValueSelect;
        base->unSAMPLE_CTL.u32Register = unSampleCtl.u32Register;

        unPostCtl.stcField.u3POST_PROC = config->postProcessingMode;
        unPostCtl.stcField.u1LEFT_ALIGN = config->resultAlignment;
        unPostCtl.stcField.u1SIGN_EXT = config->signExtention;
        unPostCtl.stcField.u8AVG_CNT = config->averageCount;
        unPostCtl.stcField.u5SHIFT_R = config->rightShift;
        unPostCtl.stcField.u2RANGE_MODE = config->rangeDetectionMode;
        base->unPOST_CTL.u32Register = unPostCtl.u32Register;

        unRangeCtl.stcField.u16RANGE_LO = config->rangeDetectionLoThreshold;
        unRangeCtl.stcField.u16RANGE_HI = config->rangeDetectionHiThreshold;
        base->unRANGE_CTL.u32Register = unRangeCtl.u32Register;

        Cy_Adc_Channel_SetInterruptMask(base, &config->mask);
    }
    else
    {
        ret = CY_ADC_BAD_PARAM;
    }
    return ret;
}

/*******************************************************************************
* Function Name: Cy_Adc_Channel_DeInit
****************************************************************************//**
*
* \brief Stop and de-initialize ADC channel register.
*
* \param base
* The pointer to an SAR channel instance.
*
*******************************************************************************/
void Cy_Adc_Channel_DeInit(volatile stc_PASS_SAR_CH_t * base)
{
    un_PASS_SAR_CH_INTR_t unIntr = { 0 };

    base->unTR_CTL.u32Register = 0x00000800uL;
    base->unENABLE.u32Register = 0x00000000uL;
    /* Clear whole interrupt flag */
    unIntr.stcField.u1CH_OVERFLOW = 1u;
    unIntr.stcField.u1CH_PULSE = 1u;
    unIntr.stcField.u1CH_RANGE = 1u;
    unIntr.stcField.u1GRP_CANCELLED = 1u;
    unIntr.stcField.u1GRP_DONE = 1u;
    unIntr.stcField.u1GRP_OVERFLOW = 1u;
    base->unINTR.u32Register = unIntr.u32Register;
}

/*******************************************************************************
* Function Name: Cy_Adc_DeInit
****************************************************************************//**
*
* \breif  De-initializes the SAR block, returns register values to default.
*
* \param base : The pointer to a SAR block.
*
* \return None
*
*******************************************************************************/
void Cy_Adc_DeInit(volatile stc_PASS_SAR_t * base)
{
    base->unCTL.u32Register = 0u;
    base->unPRECOND_CTL.u32Register = 0u;
}

/*******************************************************************************
* Function Name: Cy_Adc_Channel_Enable
*******************************************************************************/
void Cy_Adc_Channel_Enable(volatile stc_PASS_SAR_CH_t * base)
{
    base->unENABLE.stcField.u1CHAN_EN = 1u;
}

/*******************************************************************************
* Function Name: Cy_Adc_Channel_Disable
*******************************************************************************/
void Cy_Adc_Channel_Disable(volatile stc_PASS_SAR_CH_t * base)
{
    base->unENABLE.stcField.u1CHAN_EN = 0u;
}

/*******************************************************************************
* Function Name: Cy_Adc_Channel_SetInterruptMask
*******************************************************************************/
cy_en_adc_status_t Cy_Adc_Channel_SetInterruptMask(volatile stc_PASS_SAR_CH_t * base, const cy_stc_adc_interrupt_source_t * mask)
{
    cy_en_adc_status_t ret = CY_ADC_SUCCESS;
    un_PASS_SAR_CH_INTR_MASK_t unMask = { 0 };
    if (NULL != mask)
    {
        unMask.stcField.u1CH_OVERFLOW_MASK = mask->chOverflow ? 1u : 0u;
        unMask.stcField.u1CH_PULSE_MASK = mask->chPulse ? 1u : 0u;
        unMask.stcField.u1CH_RANGE_MASK = mask->chRange ? 1u : 0u;
        unMask.stcField.u1GRP_CANCELLED_MASK = mask->grpCancelled ? 1u : 0u;
        unMask.stcField.u1GRP_DONE_MASK = mask->grpDone ? 1u : 0u;
        unMask.stcField.u1GRP_OVERFLOW_MASK = mask->grpOverflow ? 1u : 0u;
        base->unINTR_MASK.u32Register = unMask.u32Register;
    }
    else
    {
        ret = CY_ADC_BAD_PARAM;
    }
    return ret;
}

/*******************************************************************************
* Function Name: Cy_WDT_Lock
****************************************************************************//**
*
* Locks out configuration changes to the Watchdog Timer register.
*
* After this function is called, the WDT configuration cannot be changed until
* Cy_WDT_Unlock() is called.
*
*******************************************************************************/
void Cy_WDT_Lock(volatile stc_WDT_t *base)
{
    base->unLOCK.stcField.u2WDT_LOCK = 3ul;
}


/*******************************************************************************
* Function Name: Cy_WDT_Unlock
****************************************************************************//**
*
* Unlocks the Watchdog Timer configuration register.
*
*******************************************************************************/
void Cy_WDT_Unlock(volatile stc_WDT_t *base)
{
    /* The WDT lock is to be removed by two writes */
    base->unLOCK.stcField.u2WDT_LOCK = 1ul;
    base->unLOCK.stcField.u2WDT_LOCK = 2ul;
}

/*******************************************************************************
* Function Name: Cy_WDT_SetService
****************************************************************************//**
*
* Set service of the watchdog. This resets the count value to zero.
*
*******************************************************************************/
 void Cy_WDT_SetService(volatile stc_WDT_t *base)
{
   base->unSERVICE.stcField.u1SERVICE = 1ul;
}


/*******************************************************************************
* Function Name: Cy_WDT_ClearWatchdog
****************************************************************************//**
*
* Clears ("feeds") the watchdog, to prevent a XRES device reset.
* This function simply call Cy_WDT_ClearInterrupt() function.
*
*******************************************************************************/
void Cy_WDT_ClearWatchdog(void)
{
    Cy_WDT_Unlock(BASICWDT);
    Cy_WDT_SetService(BASICWDT);
    Cy_WDT_Lock(BASICWDT);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_Lock
****************************************************************************//**
*
*  Locks out configuration changes to all MCWDT registers.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*******************************************************************************/
void Cy_MCWDT_Lock(volatile stc_MCWDT_t *base)
{
    base->unLOCK.stcField.u2MCWDT_LOCK  =  CY_MCWDT_LOCK_SET01;
}

/*******************************************************************************
* Function Name: Cy_MCWDT_Unlock
****************************************************************************//**
*
*  Unlocks the MCWDT configuration registers.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*******************************************************************************/
 void Cy_MCWDT_Unlock(volatile stc_MCWDT_t *base)
{
    base->unLOCK.stcField.u2MCWDT_LOCK  =  CY_MCWDT_LOCK_CLR0;
    base->unLOCK.stcField.u2MCWDT_LOCK  =  CY_MCWDT_LOCK_CLR1;
}


/*******************************************************************************
* Function Name: Cy_MCWDT_ResetCounters
****************************************************************************//**
*
*  Resets all specified counters.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counters
*  OR of all counters to reset. See the \ref CY_MCWDT_CTR0, CY_MCWDT_CTR1, and
*  CY_MCWDT_CTR2  macros.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning, because
*  a reset occurs after one lf_clk cycle passes. The recommended value is 62 us.
*  \note
*  Setting this parameter to a zero means No wait. In this case, it is the
*  user's responsibility to check whether the selected counters were reset
*  immediately after the function call. This can be done by the
*  Cy_MCWDT_GetCount() API.
*
*******************************************************************************/
void Cy_MCWDT_ResetCounters(volatile stc_MCWDT_t *base, uint32_t counters, uint16_t waitUs)
{
    if (counters & CY_MCWDT_CTR0)
    {
        base->unSERVICE.stcField.u1CTR0_SERVICE = 1;
    }
    if (counters & CY_MCWDT_CTR1)
    {
        base->unSERVICE.stcField.u1CTR1_SERVICE = 1;
    }
    if (counters & CY_MCWDT_CTR2)
    {
        // No reset functionality for CNT2
    }
}


/*******************************************************************************
* Function Name: Cy_MCWDT_ClearWatchdog
****************************************************************************//**
*
* Clears the MC watchdog counter, to prevent a XRES device reset or fault.
*
*  \param base
*  The base pointer to a structure that describes the registers.
*
*  \param counter
*  The number of the MCWDT counter. The valid range is [0-1].
*
*******************************************************************************/
void Cy_MCWDT_ClearWatchdog(volatile stc_MCWDT_t *base, cy_en_mcwdtctr_t counter)
{
   Cy_MCWDT_Unlock(base);
   Cy_MCWDT_ResetCounters(base, (1u << (uint8_t)counter), 0u);
   Cy_MCWDT_Lock(base);
}


void Trigger_WdgService_CyclicWakeUp(uint32_t kind)
{
  if(kind == WDG_TYPE_BASIC)
  {
    Cy_WDT_ClearWatchdog();
  }
  else  // in case MCWDT COUNTER 0 (16bit)
 {
   Cy_MCWDT_ClearWatchdog(MCWDT0, CY_MCWDT_COUNTER0);
/* To ensure a pending SERVICE write is reflected, firmware should wait until this bit reads low before attempting to write SERVICE=1 */
//    Cy_MCWDT_WaitForCounterReset(MCWDT0, CY_MCWDT_COUNTER0);
 }
}

void CyclicWakeup_Adc_Init(void)
{
  /* ADC clock must be initialized before ADC init */
  /* Make sure ADC clock must be lower than 26.7MHz */


    /* Initialize ADC */
    {
        cy_stc_adc_config_t adcConfig =
        {
            .preconditionTime = 0u,
            .powerupTime = 0u,
            .enableIdlePowerDown = false,
            .msbStretchMode = CY_ADC_MSB_STRETCH_MODE_1CYCLE,
            .enableHalfLsbConv = 0u,
            .sarMuxEnable = true,
            .adcEnable = true,
            .sarIpEnable = true,
        };
        cy_stc_adc_channel_config_t adcChannelConfig =
        {
            .triggerSelection = CY_ADC_TRIGGER_OFF,
            .channelPriority = 0,
            .preenptionType = CY_ADC_PREEMPTION_FINISH_RESUME,
            .isGroupEnd = true,
            .doneLevel = CY_ADC_DONE_LEVEL_PULSE,
            .pinAddress = ((cy_en_adc_pin_address_t)LP_ADC_PHY_NO),
            .portAddress = CY_ADC_PORT_ADDRESS_SARMUX0,
            .extMuxSelect = 0,
            .extMuxEnable = true,
            .preconditionMode = CY_ADC_PRECONDITION_MODE_OFF,
            .overlapDiagMode = CY_ADC_OVERLAP_DIAG_MODE_OFF,
            .sampleTime = 20,                     // ==> Need to adjust
            .calibrationValueSelect = CY_ADC_CALIBRATION_VALUE_REGULAR,
            .postProcessingMode = CY_ADC_POST_PROCESSING_MODE_NONE,
            .resultAlignment = CY_ADC_RESULT_ALIGNMENT_RIGHT,
            .signExtention = CY_ADC_SIGN_EXTENTION_UNSIGNED,
            .averageCount = 0,
            .rightShift = 0,
            .rangeDetectionMode = CY_ADC_RANGE_DETECTION_MODE_INSIDE_RANGE,
            .rangeDetectionLoThreshold = 0x0000,
            .rangeDetectionHiThreshold = 0x0FFF,
            .mask.grpDone = false,
            .mask.grpCancelled = false,
            .mask.grpOverflow = false,
            .mask.chRange = false,
            .mask.chPulse = false,
            .mask.chOverflow = false,
        };

        Cy_Adc_Channel_Init(LP_ADC_CH_NO, &adcChannelConfig);
    }

    /* Enable ADC ch. */
    Cy_Adc_Channel_Enable(LP_ADC_CH_NO);

}


void Cy_MCWDT_DeInit(volatile stc_MCWDT_t *base)
{
    Cy_MCWDT_Unlock(base);

    // disable all counter
    for(uint32_t loop = 0ul; loop < CY_MCWDT_NUM_OF_SUBCOUNTER; loop++)
    {
        base->CTR[loop].unCTL.u32Register = 0ul;
    }
    base->unCTR2_CTL.u32Register    = 0ul;

    for(uint32_t loop = 0ul; loop < CY_MCWDT_NUM_OF_SUBCOUNTER; loop++)
    {
        while(base->CTR[loop].unCTL.u32Register != 0x0ul); // wait until enabled bit become 1
        base->CTR[loop].unLOWER_LIMIT.u32Register = 0x0ul;
        base->CTR[loop].unUPPER_LIMIT.u32Register = 0x0ul;
        base->CTR[loop].unWARN_LIMIT.u32Register  = 0x0ul;
        base->CTR[loop].unCONFIG.u32Register      = 0x0ul;
        base->CTR[loop].unCNT.u32Register         = 0x0ul;
    }

    while(base->unCTR2_CNT.u32Register != 0ul); // wait until enabled bit become 1
    base->unCPU_SELECT.u32Register  = 0ul;
    base->unCTR2_CONFIG.u32Register = 0ul;
    base->unSERVICE.u32Register     = 0x00000003ul;
    base->unINTR.u32Register        = 0xFFFFFFFFul;
    base->unINTR_MASK.u32Register   = 0ul;

    Cy_MCWDT_Lock(base);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_CpuSelectForDpSlpPauseAction
****************************************************************************//**
*
*  Select deep sleep of which core for pausing this counter
*
*  \param core
*  The selected core. Deep sleep of the core pause this counter.
*
*******************************************************************************/
void Cy_MCWDT_CpuSelectForDpSlpPauseAction(volatile stc_MCWDT_t *base, cy_en_mcwdt_select_core_t core)
{
        base->unCPU_SELECT.u32Register  = core;
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetLowerAction
****************************************************************************//**
*
*  Sets the lower limit action of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \param action
*  The action of operation for the counter. See enum typedef cy_en_mcwdt_lower_upper_action_t.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
*******************************************************************************/
void Cy_MCWDT_SetLowerAction(volatile stc_MCWDT_t *base, cy_en_mcwdtctr_t counter, cy_en_mcwdt_lower_upper_action_t action)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        base->CTR[0].unCONFIG.stcField.u2LOWER_ACTION = action;
        break;
    case CY_MCWDT_COUNTER1:
        base->CTR[1].unCONFIG.stcField.u2LOWER_ACTION = action;
        break;
    default:
        //CY_ASSERT(0u != 0u);
        break;
    }
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetUpperAction
****************************************************************************//**
*
*  Sets the upper limit action of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \param action
*  The action of operation for the counter. See enum typedef cy_en_mcwdt_lower_upper_action_t.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
*******************************************************************************/
void Cy_MCWDT_SetUpperAction(volatile stc_MCWDT_t *base, cy_en_mcwdtctr_t counter, cy_en_mcwdt_lower_upper_action_t action)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        base->CTR[0].unCONFIG.stcField.u2UPPER_ACTION = action;
        break;
    case CY_MCWDT_COUNTER1:
        base->CTR[1].unCONFIG.stcField.u2UPPER_ACTION = action;
        break;
    default:
       // CY_ASSERT(0u != 0u);
        break;
    }
}

void Cy_MCWDT_SetWarnAction(volatile stc_MCWDT_t *base, cy_en_mcwdtctr_t counter, cy_en_mcwdt_warn_action_t action)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        base->CTR[0].unCONFIG.stcField.u1WARN_ACTION = action;
        break;
    case CY_MCWDT_COUNTER1:
        base->CTR[1].unCONFIG.stcField.u1WARN_ACTION = action;
        break;
    default:
        //CY_ASSERT(0u != 0u);
        break;
    }
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetLowerLimit
****************************************************************************//**
*
*  Sets the lower limit value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \param match
*  The value to lower limit against the counter.
*  The valid range is [0-65535] when Auto service is disabled and [1-65535] when
*  Auto service enabled.
*
*  \note
*  The lower limit value is not supported by Counter 2.
*
*  \note
*  Action on lower limit is taken on the next increment after the counter value
*  equal to lower limit value.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning,
*  because the match affects after two lf_clk cycles pass. The recommended
*  value is 93 us.
*  \note
*  Setting this parameter to a zero means No wait. This must be taken
*  into account when changing the match values on the running counters.
*
*******************************************************************************/
void Cy_MCWDT_SetLowerLimit(volatile stc_MCWDT_t *base, cy_en_mcwdtctr_t counter, uint16_t limit, uint16_t waitUs)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        base->CTR[0].unLOWER_LIMIT.stcField.u16LOWER_LIMIT = limit;
        break;
    case CY_MCWDT_COUNTER1:
        base->CTR[1].unLOWER_LIMIT.stcField.u16LOWER_LIMIT = limit;
        break;
    default:
        //CY_ASSERT(0u != 0u);
    }

}
/*******************************************************************************
* Function Name: Cy_MCWDT_SetWarnLimit
****************************************************************************//**
*
*  Sets the warn limit value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \param match
*  The value to warn limit against the counter.
*  The valid range is [0-65535] when Auto service is disabled and [1-65535] when
*  Auto service enabled.
*
*  \note
*  The warn limit value is not supported by Counter 2.
*
*  \note
*  Action on warn limit is taken on the next increment after the counter value
*  equal to warn limit value.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning,
*  because the match affects after two lf_clk cycles pass. The recommended
*  value is 93 us.
*  \note
*  Setting this parameter to a zero means No wait. This must be taken
*  into account when changing the match values on the running counters.
*
*******************************************************************************/
void Cy_MCWDT_SetWarnLimit(volatile stc_MCWDT_t *base, cy_en_mcwdtctr_t counter, uint16_t limit, uint16_t waitUs)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        base->CTR[0].unWARN_LIMIT.stcField.u16WARN_LIMIT = limit;
        break;
    case CY_MCWDT_COUNTER1:
        base->CTR[1].unWARN_LIMIT.stcField.u16WARN_LIMIT = limit;
        break;
    default:
       // CY_ASSERT(0u != 0u);
    }
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetUpperLimit
****************************************************************************//**
*
*  Sets the upper limit value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \param match
*  The value to upper limit against the counter.
*  The valid range is [0-65535] when Auto service is disabled and [1-65535] when
*  Auto service enabled.
*
*  \note
*  The upper limit value is not supported by Counter 2.
*
*  \note
*  Action on upper limit is taken on the next increment after the counter value
*  equal to upper limit value.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning,
*  because the match affects after two lf_clk cycles pass. The recommended
*  value is 93 us.
*  \note
*  Setting this parameter to a zero means No wait. This must be taken
*  into account when changing the match values on the running counters.
*
*******************************************************************************/
void Cy_MCWDT_SetUpperLimit(volatile stc_MCWDT_t *base, cy_en_mcwdtctr_t counter, uint16_t limit, uint16_t waitUs)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        base->CTR[0].unUPPER_LIMIT.stcField.u16UPPER_LIMIT = limit;
        break;
    case CY_MCWDT_COUNTER1:
        base->CTR[1].unUPPER_LIMIT.stcField.u16UPPER_LIMIT = limit;
        break;
    default:
        //CY_ASSERT(0u != 0u);
    }

}
/*******************************************************************************
* Function Name: Cy_MCWDT_SetAutoService
****************************************************************************//**
*
*  Sets the Auto service option for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \note
*  The auto service option is not supported by Counter 2.
*
*  \param enable
*  Set 0 to disable; 1 to enable.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
*******************************************************************************/
void Cy_MCWDT_SetAutoService(volatile stc_MCWDT_t *base, cy_en_mcwdtctr_t counter, uint32_t enable)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        base->CTR[0].unCONFIG.stcField.u1AUTO_SERVICE = enable;
        break;
    case CY_MCWDT_COUNTER1:
        base->CTR[1].unCONFIG.stcField.u1AUTO_SERVICE = enable;
        break;
    default:
        //CY_ASSERT(0u != 0u);
    }
}
/*******************************************************************************
* Function Name: Cy_MCWDT_SetSleepDeepPause
****************************************************************************//**
*
*  Sets the Sleep deep pause option for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-2].
*
*  \param enable
*  Set 0 to disable; 1 to enable.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
*******************************************************************************/
void Cy_MCWDT_SetSleepDeepPause(volatile stc_MCWDT_t *base, cy_en_mcwdtctr_t counter, uint32_t enable)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        base->CTR[0].unCONFIG.stcField.u1SLEEPDEEP_PAUSE = enable;
        break;
    case CY_MCWDT_COUNTER1:
        base->CTR[1].unCONFIG.stcField.u1SLEEPDEEP_PAUSE = enable;
        break;
    case CY_MCWDT_COUNTER2:
        base->unCTR2_CONFIG.stcField.u1SLEEPDEEP_PAUSE = enable;
        break;
    default:
        //CY_ASSERT(0u != 0u);
    }
}
/*******************************************************************************
* Function Name: Cy_MCWDT_SetDebugRun
****************************************************************************//**
*
*  Sets the Debug run option for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-2].
*
*  \param enable
*  Set 0 to disable; 1 to enable.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
*******************************************************************************/
void Cy_MCWDT_SetDebugRun(volatile stc_MCWDT_t *base, cy_en_mcwdtctr_t counter, uint32_t enable)
{
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        base->CTR[0].unCONFIG.stcField.u1DEBUG_RUN = enable;
        break;
    case CY_MCWDT_COUNTER1:
        base->CTR[1].unCONFIG.stcField.u1DEBUG_RUN = enable;
        break;
    case CY_MCWDT_COUNTER2:
        base->unCTR2_CONFIG.stcField.u1DEBUG_RUN = enable;
        break;
    default:
        //CY_ASSERT(0u != 0u);
    }
}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetEnabledStatus
****************************************************************************//**
*
*  Reports the enabled status of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the MCWDT counter. The valid range is [0-2].
*
*  \return
*  The status of the MCWDT counter: 0 = disabled, 1 = enabled.
*
*******************************************************************************/
uint32_t Cy_MCWDT_GetEnabledStatus(volatile stc_MCWDT_t const *base, cy_en_mcwdtctr_t counter)
{
    uint32_t status = 0u;
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        status = base->CTR[0].unCTL.stcField.u1ENABLED;
        break;
    case CY_MCWDT_COUNTER1:
        status = base->CTR[1].unCTL.stcField.u1ENABLED;
        break;
    case CY_MCWDT_COUNTER2:
        status = base->unCTR2_CTL.stcField.u1ENABLED;
        break;
    default:
        //CY_ASSERT(0u != 0u);
    break;
    }
    return (status);
}


void Cy_MCWDT_Enable(volatile stc_MCWDT_t *base, uint32_t counters, uint16_t waitUs)
{

    if (counters & CY_MCWDT_CTR0)
    {
        base->CTR[0].unCTL.stcField.u1ENABLE = 1;
    }
    if (counters & CY_MCWDT_CTR1)
    {
        base->CTR[1].unCTL.stcField.u1ENABLE = 1;
    }
    if (counters & CY_MCWDT_CTR2)
    {
        base->unCTR2_CTL.stcField.u1ENABLE = 1;
    }

}



void Start_WdgService_CyclicWakeUp()
{


    Cy_MCWDT_DeInit(MCWDT0);

    Cy_MCWDT_Unlock(MCWDT0);

    Cy_MCWDT_CpuSelectForDpSlpPauseAction(MCWDT0, CY_MCWDT_PAUSED_BY_DPSLP_CM4_CM7_0);

    /*********************************************************************/
    /*****              Set actions            *****/
    /*********************************************************************/
    Cy_MCWDT_SetLowerAction(MCWDT0, CY_MCWDT_COUNTER0, CY_MCWDT_ACTION_NONE);
    Cy_MCWDT_SetWarnAction(MCWDT0, CY_MCWDT_COUNTER0, CY_MCWDT_WARN_ACTION_NONE);
    Cy_MCWDT_SetUpperAction(MCWDT0, CY_MCWDT_COUNTER0, CY_MCWDT_ACTION_FAULT_THEN_RESET); // reset if timeout
    /*********************************************************************/
    /*****            Set limit values           *****/
    /*********************************************************************/
    Cy_MCWDT_SetLowerLimit(MCWDT0, CY_MCWDT_COUNTER0, 0u, 0u);
    Cy_MCWDT_SetWarnLimit(MCWDT0, CY_MCWDT_COUNTER0, 0u, 0u);
    Cy_MCWDT_SetUpperLimit(MCWDT0, CY_MCWDT_COUNTER0, TIMEOUT_VALUE, 0u);

    /*********************************************************************/
    /*****              Set options            *****/
    /*********************************************************************/
    Cy_MCWDT_SetAutoService(MCWDT0, CY_MCWDT_COUNTER0, 0ul);  // disable
    Cy_MCWDT_SetSleepDeepPause(MCWDT0, CY_MCWDT_COUNTER0, 0ul); // enable : 1, disable : 0
//    Cy_MCWDT_SetDebugRun(MCWDT0, CY_MCWDT_COUNTER0, 1ul);     // enable

    /* For WDT CNT debugging */
      Cy_MCWDT_SetDebugRun(MCWDT0, CY_MCWDT_COUNTER0, 0ul);     // disable...T32 해제시 EVTGEN toggle이 안됬어요.
      MCWDT0->CTR[0].unCONFIG.stcField.u1DEBUG_TRIGGER_EN = 1;  // to pause CNT by core halt

    Cy_MCWDT_Enable(MCWDT0, CY_MCWDT_CTR0 , 0u);  // enable only counter 0

    while(Cy_MCWDT_GetEnabledStatus(MCWDT0, CY_MCWDT_COUNTER0) != 1ul);

    Cy_MCWDT_Lock(MCWDT0);

}

void Stop_WdgService_CyclicWakeUp()
{

    Cy_MCWDT_DeInit(MCWDT0);

}

/***************************************************************************//**
 * Function Name        : ASW_LP_TASK
 * Service ID           : NA
 * Description          : Callout for Wakeup Check
 * Sync/Async           : Synchronous
 * Re-entrancy          : Non Re-entrant
 * Parameters           : None
 * @return              : void
 * @pre                 : None
 * @remarks             : Global Variable(s)     :
 *                        None
 ******************************************************************************/
uint16 adcResult = 0u;
uint32 adcResult_converse = 0u;
extern void WdgStack_TriggerWatchdog(void);
extern FUNC(void, CDD_WPCIC_CODE) wpcic_enable(void);
extern FUNC(void, CDD_WPCIC_CODE) wpcic_disable(void);
extern void DigDir_VBATSW_EN_tmp(uint8 data);
extern IoHwAb_ValueType Battery_Real_ReadDirect(void);
extern IoHwAb_ValueType ACC_ReadDirect(void);
extern void Input_IGNVoltage(void);
extern uint16 GetIGNADValue(void);
extern void Set_Slp_Step(void);
extern void Set_IGN_ON_Callout_tmp(void);
volatile uint8 test_tog = 0u;
extern uint8 IGN_stab_reset_flg;
extern uint8 Slpwup_GulSleepProcessState;
uint8 ADC_cnt = 0;
void ASW_LP_TASK(void)
{
  uint16 adcRawValue_Batt;
  uint16 adcRawValue_Ign;

  uint8 i = 0u;

#if 0
  if(test_tog==0u)
  {
    test_tog = 1u;
    DigDir_VBATSW_EN_tmp(0);
  }
  else if(test_tog==1u)
  {
    test_tog = 0u;
    DigDir_VBATSW_EN_tmp(1);
  }
#endif
  
  adcRawValue_Batt = Battery_Real_ReadDirect();
  adcRawValue_Ign = ACC_ReadDirect();

  if((adcRawValue_Ign > kIGN_ON_Voltage) && (adcRawValue_Batt > kCriticalBatteryUnder))
  {
  	if(ADC_cnt == 0)
  	{
    	IGN_stab_reset_flg = On;
    }

    do{
      Input_IGNVoltage();
      ADC_cnt++;
    }while(ADC_cnt < 2u);

	if(ADC_cnt >= 5u)		/* 150ms Wake-up -> 1sec Wake-up */
	{
		ADC_cnt = 0u;
	    adcRawValue_Ign = GetIGNADValue();

	    if(adcRawValue_Ign > kIGN_ON_Voltage)
	    {

			Slpwup_GulSleepProcessState = SLPWUP_IGN_L_H;

		 	wakeUpSource = ADC_WAKE_UP;

			EcuM_SetWakeupEvent(ECUM_WKSOURCE_IGN_WakeUP);
		    Set_IGN_ON_Callout_tmp();
		}
	    else
	    {
	      Slpwup_GulSleepProcessState = SLPWUP_GOTO_MCU_SLEEP;
	    }
    }
    else
    {
    	//POWER_SYS_SetMode(STOP);  /* Set Enter DeepSleep */
		Slpwup_GulSleepProcessState = SLPWUP_GOTO_MCU_SLEEP;
    }
  }
  else
  {
  	ADC_cnt = 0u;
    //PINS_DRV_WritePin(IPS_IN_PORT, IPS_IN, 1);
    //PINS_DRV_WritePin(IPS_SEN_PORT, IPS_SEN, 0);
    //POWER_SYS_SetMode(STOP);    /* Set Enter DeepSleep */
    Slpwup_GulSleepProcessState = SLPWUP_GOTO_MCU_SLEEP;
  }
}

#define ECUM_STOP_SEC_CALLOUT_CODE
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
