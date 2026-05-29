/* *************************************************************************
 *                                                                       *
 *                      HYUNDAI MOTOR GROUP                              *
 *                                                                       *
 *                      All rights reserved                              *
 *                                                                       *
 *************************************************************************  
 *
 ****************************************************************************

 * Name : 

 * Description:

 * Version : 1.0

 *****************************************************************************

 * Project : e_rtu2_cyt4bbxx-21.08.1

 *****************************************************************************
 * Tool  : mobilgene
 * Author: 
 * Date  : 2021.08.01
 ****************************************************************************/
#include "Slpwup_LPTM_Def.h"
#include "Slpwup_Callouts.h"
#include "Mcu.h"
#include "Dio.h"
#include "Wdg.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/
#define COMP_ACTIVE     0
#define COMP_DEEPSLEEP    1
#define DEF_SLPWUP_SYSTEMMINIMUM_OFFSET_TIME 200UL
#define EVTGEN_COMP_STRUCT_NR           16u
#define Slpwup_LPTaskEntry 1
#define Slpwup_LPTaskExit  0

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/
cy_stc_evtgen_struct_context_t evtgenStruct0Context;
cy_stc_evtgen_struct_config_t evtgenTestStructureConfig;
cy_stc_evtgen_config_t evtgenTestConfig;
static cy_stc_evtgen_struct_context_t *evtgenContext[EVTGEN_COMP_STRUCT_NR];
uint64 lul_LPstart_EVTGENCNT = 0UL;
uint64 lul_LPend_EVTGENCNT = 0UL;
uint32 lul_ThresholdTime = 0UL;
uint32 lul_TaskExecutionTime = 0UL;
uint64 lul_SetEVTGENCNT = 0UL;
uint8 Slpwup_Guc_LPTaskExecution = 0;
uint32 mapUsed;

/*****************************************************************************/
/* Global variable definitions                                               */
/*****************************************************************************/
uint8 wakeUpSource = 0;

/*****************************************************************************/
/* Global function definitions                                    */
/*****************************************************************************/
extern void Cy_Evtgen_DeinitializeCompStruct(volatile stc_EVTGEN_t *base, uint8_t structNum);
extern void Cy_Evtgen_Deinitialize(volatile stc_EVTGEN_t *base);
extern cy_en_evtgendrv_status_t Cy_Evtgen_Initialize(volatile stc_EVTGEN_t *base, const cy_stc_evtgen_config_t* config);
extern cy_en_evtgendrv_status_t Cy_Evtgen_InitializeCompStruct(volatile stc_EVTGEN_t *base, uint8_t structNum,const cy_stc_evtgen_struct_config_t* configStruct,cy_stc_evtgen_struct_context_t* context);


/*******************************************************************************
* Function Name: Cy_Evtgen_SetInterruptDeepSleepMask
********************************************************************************/
void Cy_Evtgen_SetInterruptDeepSleepMask(volatile stc_EVTGEN_t *base, uint8_t structNumber)
{
    base->unINTR_DPSLP_MASK.u32Register |= ((uint32)1 << structNumber);
}

/*******************************************************************************
* Function Name: Cy_Evtgen_SetInterruptMask
*******************************************************************************/
void Cy_Evtgen_SetInterruptMask(volatile stc_EVTGEN_t *base, uint8_t structNumber)
{
    base->unINTR_MASK.u32Register |= ((uint32)1 << structNumber);
}

/*******************************************************************************
* Function Name: Cy_Evtgen_Enable
*******************************************************************************/
void Cy_Evtgen_Enable(volatile stc_EVTGEN_t *base)
{
    base->unCTL.stcField.u1ENABLED = 1u; /* Set ENABLED bit */
}


/*******************************************************************************
* Function Name: Cy_Evtgen_GetCounterValue
******************************************************************************/
uint32 Cy_Evtgen_GetCounterValue(volatile stc_EVTGEN_t *base)
{
    return base->unCOUNTER.u32Register;
}

/*******************************************************************************
* Function Name: Cy_Evtgen_DeinitializeCompStruct
******************************************************************************/
void Cy_Evtgen_DeinitializeCompStruct(volatile stc_EVTGEN_t *base, uint8_t structNum)
{
    base->COMP_STRUCT[structNum].unCOMP_CTL.u32Register = 0;
    base->COMP_STRUCT[structNum].unCOMP0.stcField.u32INT32 = 0;// Active
    base->COMP_STRUCT[structNum].unCOMP1.stcField.u32INT32 = 0;// Deep Sleep
    evtgenContext[structNum] = NULL;
}

/*******************************************************************************
* Function Name: Cy_Evtgen_Deinitialize
*******************************************************************************/
void Cy_Evtgen_Deinitialize(volatile stc_EVTGEN_t *base)
{
    base->unCTL.u32Register = 0;
    base->unREF_CLOCK_CTL.u32Register = 0; //Event Generator Clock divider register
    base->unRATIO.u32Register = 0;
    base->unRATIO_CTL.u32Register = 0;
    base->unINTR_MASK.u32Register = 0;
    base->unINTR_DPSLP_MASK.u32Register = 0;
}

/*******************************************************************************
* Function Name: Cy_Evtgen_Initialize
********************************************************************************/
cy_en_evtgendrv_status_t Cy_Evtgen_Initialize(volatile stc_EVTGEN_t *base, const cy_stc_evtgen_config_t* config)
{
    uint16_t refDiv;

    un_EVTGEN_RATIO_CTL_t ratioCtl;

    /* 1. Checking input parameter valid */
    if(config == NULL)
    {
        return CY_EVTGEN_ERR;
    }

    /* 2. Initialize internal variable */
    for(uint32 i = 0; i < EVTGEN_COMP_STRUCT_NR; i++)
    {
        evtgenContext[i] = NULL;
    }
    mapUsed = 0;

    Cy_Evtgen_Enable(base);

    /* 2. Setting divider value of clk_ref */
    refDiv = config->frequencyRef / config->frequencyTick;
    if(config->frequencyRef % config->frequencyTick != 0)
    {
        return CY_EVTGEN_ERR;
    }
    else if(refDiv > 256 || refDiv  < 1)
    {
        return CY_EVTGEN_ERR;
    }
    else
    {
        base->unREF_CLOCK_CTL.stcField.u8INT_DIV = refDiv - 1u;
    }

    /* 3. Setting ratio operation */
    if(config->ratioControlMode == CY_EVTGEN_RATIO_CONTROL_SW)
    {
        /* SW controll: setting value for ratio value should be ratio between tick_ref_div and clk_lf. */
        uint64 temp = (uint64)(config->frequencyRef / refDiv) << EVTGEN_RATIO_INT16_Pos;
        temp = temp / (uint64)(config->frequencyLf);
        base->unRATIO.u32Register = ((uint32)temp) & (EVTGEN_RATIO_INT16_Msk | EVTGEN_RATIO_FRAC8_Msk);

        base->unRATIO_CTL.stcField.u1DYNAMIC = 0u;

        /* SW controll: valid bit should be set manually. */
        base->unRATIO_CTL.stcField.u1VALID = 1u; /* Set VALID bit */
    }
    else
    {
        /* HW controll: */
        ratioCtl.u32Register = base->unRATIO_CTL.u32Register;
        ratioCtl.stcField.u1DYNAMIC = 1u; /* Set Dynamic bit */
        ratioCtl.stcField.u3DYNAMIC_MODE = config->ratioValueDynamicMode; /* Set Dynamic bit */
        base->unRATIO_CTL.u32Register = ratioCtl.u32Register;

        /* Waiting until valid bit is set. */
        while(base->unRATIO_CTL.stcField.u1VALID == 0u);
    }

    /* Waiting until counter become ready. */
    while(base->unCOUNTER_STATUS.stcField.u1VALID == 0u);

    return CY_EVTGEN_OK;
}

/*******************************************************************************
* Function Name: Cy_Evtgen_InitializeCompStruct
********************************************************************************/
cy_en_evtgendrv_status_t Cy_Evtgen_InitializeCompStruct(volatile stc_EVTGEN_t *base,
                                                        uint8_t structNum,
                                                        const cy_stc_evtgen_struct_config_t* configStruct,
                                                        cy_stc_evtgen_struct_context_t* context)
{
    un_EVTGEN_COMP_STRUCT_COMP_CTL_t compCtr;
    uint64 tempCounterValue;


    /* Checking input parameter valid */
    if(configStruct == NULL)
    {
        return CY_EVTGEN_ERR;
    }

    if(structNum >= EVTGEN_COMP_STRUCT_NR)
    {
        return CY_EVTGEN_ERR;
    }

    if(configStruct->functionalitySelection != CY_EVTGEN_DEEPSLEEP_FUNCTIONALITY)
    {
        if(context == NULL)
        {
            return CY_EVTGEN_ERR;
        }
        evtgenContext[structNum] = context;
        evtgenContext[structNum]->addValueForCOMP0 = configStruct->valueActiveComparator;
        evtgenContext[structNum]->userIsr = configStruct->userIsr;
        mapUsed |= 1 << structNum;
    }

    compCtr.u32Register = base->COMP_STRUCT[structNum].unCOMP_CTL.u32Register;

    if(configStruct->functionalitySelection == CY_EVTGEN_DEEPSLEEP_FUNCTIONALITY)
    {
        compCtr.stcField.u1COMP1_EN = 1u;
    }

    compCtr.stcField.u1COMP0_EN = 1u;

    compCtr.stcField.u1TR_OUT_EDGE = configStruct->triggerOutEdge;

    compCtr.stcField.u1ENABLED = 1u;


    tempCounterValue = (uint64)Cy_Evtgen_GetCounterValue(base);

    /* Setting active comparator value */
    base->COMP_STRUCT[structNum].unCOMP0.stcField.u32INT32 = (uint32)(tempCounterValue + (uint64)configStruct->valueActiveComparator);

    /* Setting deep sleep comparator value */
    if(configStruct->functionalitySelection == CY_EVTGEN_DEEPSLEEP_FUNCTIONALITY)
    {
        base->COMP_STRUCT[structNum].unCOMP1.stcField.u32INT32 = (uint32)(tempCounterValue + (uint64)configStruct->valueDeepSleepComparator);
    }



    /* Setting comparator struct controll parameter */
    base->COMP_STRUCT[structNum].unCOMP_CTL.u32Register = compCtr.u32Register;

    Cy_Evtgen_SetInterruptMask(base, structNum);
    if(configStruct->functionalitySelection == CY_EVTGEN_DEEPSLEEP_FUNCTIONALITY)
    {
        Cy_Evtgen_SetInterruptDeepSleepMask(base, structNum);
    }

    return CY_EVTGEN_OK;
}


/*******************************************************************************
* Function Name: Cy_Evtgen_ClearStructInterruptDeepSleep
*******************************************************************************/
void Cy_Evtgen_ClearStructInterruptDeepSleep(volatile stc_EVTGEN_t *base, uint8_t structNumber)
{
    base->unINTR_DPSLP.u32Register = ((uint32)1 << structNumber);

    // Dummy read. This is to wait for reflection above write operation.
    base->unINTR_DPSLP;
}

/*******************************************************************************
* Function Name: Cy_Evtgen_SetValueComp
****************************************************************************/
void Cy_Evtgen_SetValueComp(volatile stc_EVTGEN_t *base, uint8 kind, uint8 structNumber, uint32 countValue)
{
  if(kind == COMP_ACTIVE)
  {
    base->COMP_STRUCT[structNumber].unCOMP_CTL.stcField.u1COMP0_EN = 0u;
    base->COMP_STRUCT[structNumber].unCOMP0.stcField.u32INT32 = countValue;
    base->COMP_STRUCT[structNumber].unCOMP_CTL.stcField.u1COMP0_EN = 1u;
  }
  else
  {
    base->COMP_STRUCT[structNumber].unCOMP_CTL.stcField.u1COMP1_EN = 0u;
    base->COMP_STRUCT[structNumber].unCOMP1.stcField.u32INT32 = countValue;
    base->COMP_STRUCT[structNumber].unCOMP_CTL.stcField.u1COMP1_EN = 1u;
  }
}

/***************************************************************************
* Function Name: Cy_Evtgen_GetCounterStatus
****************************************************************************/
cy_en_evtgen_counter_status_t Cy_Evtgen_GetCounterStatus(volatile stc_EVTGEN_t *base)
{
     return (cy_en_evtgen_counter_status_t)base->unCOUNTER_STATUS.stcField.u1VALID;
}

/*********************************************************************
*  Function Name: CyclicWakeup_EventGenerator_Init
*  This function set EVTGEN Register.
*********************************************************************/
void CyclicWakeup_EventGenerator_Init(void)
{

    Cy_Evtgen_DeinitializeCompStruct(EVTGEN0,0);
    Cy_Evtgen_Deinitialize(EVTGEN0);

    /*******************************************/
    /*  Initialize event generator  0          */
    /*******************************************/
    evtgenTestConfig.frequencyRef = 8000000; //  clk_ref = clk_hf1 = CLK_PATH2 (IMO) -> 8,000,000 for silicon
    evtgenTestConfig.frequencyLf = 32768; //32000;     // clk_lf = 32,000 for silicon

    evtgenTestConfig.frequencyTick = 1000000; // Setting 1,000,000 Hz for event generator clock (clk_ref_div)
    evtgenTestConfig.ratioControlMode = CY_EVTGEN_RATIO_CONTROL_SW;
    evtgenTestConfig.ratioValueDynamicMode = CY_EVTGEN_RATIO_DYNAMIC_MODE0;
    Cy_Evtgen_Initialize(EVTGEN0,&evtgenTestConfig);

    /*******************************************/
    /*  Initialize comparator structure 0      */
    /*******************************************/
    evtgenTestStructureConfig.functionalitySelection = CY_EVTGEN_DEEPSLEEP_FUNCTIONALITY;
    evtgenTestStructureConfig.triggerOutEdge = CY_EVTGEN_EDGE_SENSITIVE;

    evtgenTestStructureConfig.valueDeepSleepComparator = SLPWUP_LPTASK_START_OFFSET_TICK; // 3ms
//  evtgenTestStructureConfig.valueDeepSleepComparator = 10000; // 10ms, In active functionality, this value is used for making period of interrupts/triggers
                                                                  // 100,000 / 1,000,000 (clk_ref_div) = 0.1[s]
    evtgenTestStructureConfig.valueActiveComparator    = 1000000; // In active functionality, this value is used for making period of interrupts/triggers
                                                                  // 1,000,000 / 1,000,000 (clk_ref_div) = 1[s]
    Cy_Evtgen_InitializeCompStruct(EVTGEN0,0, &evtgenTestStructureConfig, &evtgenStruct0Context);

}

/*********************************************************************
* Function Name: Slpwup_PreLPMode_Configuration
* This function is called before sleep mode process.
* User should configure HW Configuration for sleep mode.
*********************************************************************/

void Slpwup_PreLPMode_Configuration(void)
{

  /* set Lower Power Active Mode */
  //Mcu_InitClock(McuConf_McuClockSettingConfig_McuClockSettingConfig_LPA);
#if 0
  if(SRSS0->unPWR_CTL.stcField.u1DEBUG_SESSION == 0)
  {
    /*Disable External Power*/
    SRSS0->unPWR_REGHC_CTL2.stcField.u1REGHC_EN = 0u;

    while(SRSS0->unPWR_REGHC_STATUS.stcField.u1REGHC_SEQ_BUSY != 0);
    while(SRSS0->unPWR_REGHC_STATUS.stcField.u1REGHC_ENABLED != 0);
  }
#endif

  CyclicWakeup_EventGenerator_Init();
  wakeUpSource = UNKNOWN_WAKE_UP;

  /* Set next event generator wake up time */
  evtgenTestStructureConfig.valueDeepSleepComparator = SLPWUP_LPTASK_PERIOD_TICK;  // 50ms : 50000 -> 1,000,000.... 1,000,000 / 1,000,000 (clk_ref_div) = 1[s]

}

/*********************************************************************
* Function Name: Slpwup_PostLPMode_Configuration
* This function is called After sleep mode process.
* User should configure HW Configuration for sleep mode.
*********************************************************************/
void Slpwup_PostLPMode_Configuration(void)
{

  /*Enable External Power*/
  //SRSS0->unPWR_REGHC_CTL2.stcField.u1REGHC_EN = 1u;

  //while(SRSS0->unPWR_REGHC_STATUS.stcField.u1REGHC_SEQ_BUSY != 0);
  //while(SRSS0->unPWR_REGHC_STATUS.stcField.u1REGHC_ENABLED == 0);

  /* set Active Mode */
#if 0
  Mcu_InitClock(McuConf_McuClockSettingConfig_McuClockSettingConfig_0);

  while(Mcu_GetPllStatus() != MCU_PLL_LOCKED)
  {

  }
  Mcu_DistributePllClock();
#endif
  /* Disable Event Generator */
  Cy_Evtgen_DeinitializeCompStruct(EVTGEN0,0);
  Cy_Evtgen_Deinitialize(EVTGEN0);

}
/*********************************************************************
* Function Name : LowPowerActiveTask
* 1. It is a main function for Low Power Task execution.
* 2. This function is called when the first cyclic wake-up is executed.
* 3. Basic Watchdog sets 'OFF'.
* 4. This function calls ASW_LP_TASK().
*********************************************************************/
void LowPowerActiveTask(void)
{
  Wdg_SetMode(WDGIF_OFF_MODE);
  do
  {
      Slpwup_Guc_LPTaskExecution = Slpwup_LPTaskEntry;

      ASW_LP_TASK();

      /*******************EVTGEN Counter Compensation***************************/
      /*1. the Start moment of LPTask execution */
      /*it should be in evtgen_0_interrupt_dpslp_IRQn_Cat2*/

      /*2. threshold time : minimum LPTask execution Time*/
      lul_ThresholdTime = (uint32)(SLPWUP_LPTASK_PERIOD_TICK - DEF_SLPWUP_SYSTEMMINIMUM_OFFSET_TIME);

      /*waiting until counter become ready before set new compoare value.
        This wating may take up to 1 clk_lf cycle frome wakeup.
      */
      while(Cy_Evtgen_GetCounterStatus(EVTGEN0) == CY_EVTGEN_COUNTER_STATUS_INVALID);

      /*3. the End moment of LPTask execution */
      lul_LPend_EVTGENCNT = (uint64)Cy_Evtgen_GetCounterValue(EVTGEN0);

      /*4. calculation LPTask Execution*/
      lul_TaskExecutionTime = (uint32)(lul_LPend_EVTGENCNT - lul_LPstart_EVTGENCNT);

      if (lul_TaskExecutionTime > lul_ThresholdTime)
      {
        lul_SetEVTGENCNT = lul_LPend_EVTGENCNT + (uint64)DEF_SLPWUP_SYSTEMMINIMUM_OFFSET_TIME;
      }
      else
      {
        lul_SetEVTGENCNT = lul_LPstart_EVTGENCNT + (uint64)SLPWUP_LPTASK_PERIOD_TICK;
      }

      /* set next compare value of event generator */
      Cy_Evtgen_SetValueComp(EVTGEN0,COMP_DEEPSLEEP, 0,(uint32)lul_SetEVTGENCNT);

      /*******************EVTGEN Counter Compensation***************************/

      Slpwup_Guc_LPTaskExecution = Slpwup_LPTaskExit;

      /* To make sure SRAM write buffer is empty */
      while(CPUSS->unRAM0_STATUS.stcField.u1WB_EMPTY == 0);

      #if defined (CPUSS_RAMC1_PRESENT) && (CPUSS_RAMC1_PRESENT == 1UL) // depend on device
      while(CPUSS->unRAM1_STATUS.stcField.u1WB_EMPTY == 0);
      #endif /* defined (CPUSS_RAMC1_PRESENT) && (CPUSS_RAMC1_PRESENT == 1UL) */

      #if defined (CPUSS_RAMC2_PRESENT) && (CPUSS_RAMC2_PRESENT == 1UL) // depend on device
      while(CPUSS->unRAM2_STATUS.stcField.u1WB_EMPTY == 0);
        #endif /* defined (CPUSS_RAMC2_PRESENT) && (CPUSS_RAMC2_PRESENT == 1UL) */

      Cy_Evtgen_InitializeCompStruct(EVTGEN0,0, &evtgenTestStructureConfig, &evtgenStruct0Context);

      /* Enter Deep Sleep again */
      SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

      __WFI();

  /* wakeup from other than event generator, go to active mode.*/
  }while(wakeUpSource == EVENT_GENERATOR_WAKE_UP);

}

ISR(evtgen_0_interrupt_dpslp_IRQn_Cat2)
{
  Cy_Evtgen_ClearStructInterruptDeepSleep(EVTGEN0,0);

  /*waiting until counter become ready before set new compoare value.
    This wating may take up to 1 clk_lf cycle frome wakeup.
  */
  while(Cy_Evtgen_GetCounterStatus(EVTGEN0) == CY_EVTGEN_COUNTER_STATUS_INVALID);

  if((EVENT_GENERATOR_WAKE_UP == wakeUpSource) ||(UNKNOWN_WAKE_UP == wakeUpSource))
  {
    wakeUpSource = EVENT_GENERATOR_WAKE_UP;
  }
  if(Slpwup_LPTaskEntry != Slpwup_Guc_LPTaskExecution)
  {
    /*1. the Start moment of LPTask execution */
    lul_LPstart_EVTGENCNT = Cy_Evtgen_GetCounterValue(EVTGEN0);
  }
}
