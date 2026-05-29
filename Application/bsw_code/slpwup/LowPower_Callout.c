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

#include "LowPower_Callout.h"

#include "Slpwup_Callouts.h"
#include "Slpwup_LPTM_Def.h"
#include "Slpwup_LPTM_Interface.h"
#include "SlpWup.h"

#include "WPCLogicControl.h"

#include "Rte_IoHwAb.h"
#include "IoHwAb_IOManager.h"
#include "WdgStack_Callout.h"
#include "WdgM.h"
#include "Gpt.h"
#include "Os_Debug.h"

//#if (CRYPTOLIB_SUPORT_HSM_HAE_HSM_2_X == STD_ON)
#include "Hsm_HostAPI.h"
#include "Os.h"
//#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
extern uint8 wakeUpSource;

#define ECUM_SYST_CSR_ENABLE_MASK 0x00000001u
#define ECUM_SCR_SLEEPDEEP_MASK 0x00000004u

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
/* IPC STURCT2 INTR Register Information */
#define ECUM_IPC_STRUCUT2_INTR_SET_REG       (*(volatile uint32*)0x40221044u)
#define ECUM_IPC_STRUCUT2_INTR_MASK_REG      (*(volatile uint32*)0x40221048u)
#endif

CONSTP2VAR(volatile Mcu_Cm4ScsRegType, AUTOMATIC, REGSPACE) EcuM_Cm4ScsRegBaseAddr =
                                    (volatile Mcu_Cm4ScsRegType *)MCU_SYSTEM_CM4_SCS_REG_BASE_ADDR;

uint16 cnt_wakeupwait = 0;

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
void User_H2L_Callout(void);
void User_L2H_Callout(void);


#define ECUM_START_SEC_CALLOUT_CODE
#include "MemMap.h"

/*******************************************************************************
 * Function Name        : EcuM_H2LTransition_Callout_Swp
 *
 * Service ID           : NA
 *
 * Description          : Callout for SWP in Sleep Sequence
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        WdgStack_TransitHighToLow()
 *                        IoHwAb_IOMH2L(), Os_DebugH2L(), Gpt_SetMode()
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_H2LTransition_Callout_Swp(void)
{
  Slpwup_GulSleepProcessState = SLPWUP_H2L_TRANSITION_SWP;

  SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

  /* Stop OS Counter for Main Core */
  EcuM_Cm4ScsRegBaseAddr->SYST_CSR &= ~ECUM_SYST_CSR_ENABLE_MASK;

  SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

  #if (IOHWAB_USE_IO_MAN == STD_ON)
  IoHwAb_IOMH2L();
  #endif
  Os_DebugH2L();

  WdgStack_TransitHighToLow();
  /* All Gpt channels that are not enabled for wakeup and
   * all enabled GPT Predef Timers are stopped. */
  Gpt_SetMode(GPT_MODE_SLEEP);
}

/*******************************************************************************
 * Function Name        : EcuM_H2LTransition_Callout_App
 *
 * Service ID           : NA
 *
 * Description          : User Callout for Sleep Sequence
 *                        The application should take the necessary action here
 *                        before switching to Low Power Mode
 *                        - Disable unnecessary peripherals in Low Power Mode
 *                        - Enable Wakeup sources(ex: Icu channel, Gpt channel)
 *                        - Check early wakeup
 *                        - Apply workaround for MCU Errata
 *                        - etc
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Icu_EnableEdgeDetection(), Icu_EnableNotification(),
 *                        Icu_DisableEdgeDetection(), Icu_DisableNotification(),
 *                        IoHwAb_DigDirReadDirect(), EcuM_SetWakeupEvent(),
 *                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION()
 ******************************************************************************/
#include "st_errno.h"
#include "st25r3916.h"
uint8 ign_on_callout_is_on = 0u;

void Set_IGN_ON_Callout_tmp(void);
void Set_IGN_ON_Callout_tmp(void)
{
  ign_on_callout_is_on = 1u;
}
#include "app_input_type.h"
#include "app_input.h"
#include "define.h"
extern ReturnCode rfalDeinitialize(void);
extern void st25r3916Deinitialize(void);
extern void DigDir_VBATSW_EN_tmp(uint8 data);
FUNC(void, ECUM_CALLOUT_CODE) EcuM_H2LTransition_Callout_App(void)
{
  IoHwAb_LevelType LddLevel;
  EcuM_WakeupSourceType LddWakeupMask;

  Slpwup_GulSleepProcessState = SLPWUP_H2L_TRANSITION_APP;

  UINT16 irqList[2];
  Std_ReturnType ret = E_NOT_OK;

  SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();
  LddWakeupMask = ECUM_WKSOURCE_NONE;

  Icu_EnableEdgeDetection(IcuConf_IcuChannel_IcuChannel_BCAN_WakeUp);
  Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_BCAN_WakeUp);

  if(GetX(kb_NFC_OPTION)==On)
  {
    Icu_EnableEdgeDetection(IcuConf_IcuChannel_IcuChannel_LCAN_WakeUp);
    Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_LCAN_WakeUp);
  }

  /*****************************************************************************
   * Check that the pin level has already changed before ICU Edge Detection is
   * enabled
   ****************************************************************************/
  IoHwAb_DigDirReadDirect((uint16)IoHwAbDigitalDirectLogical_BCAN_RX, &LddLevel);
  if (LddLevel == (IoHwAb_LevelType)IOHWAB_LOW)
  {
    LddWakeupMask |= ECUM_WKSOURCE_BCAN_RX_POLL;  // 0x80
  }

  if(GetX(kb_NFC_OPTION)==On)
  {
    IoHwAb_DigDirReadDirect((uint16)IoHwAbDigitalDirectLogical_LOCALCAN_RX, &LddLevel);
    if (LddLevel == (IoHwAb_LevelType)IOHWAB_LOW)
    {
      LddWakeupMask |= ECUM_WKSOURCE_LOCALCAN_RX_POLL;
    }
  }

  IoHwAb_DigDirReadDirect((uint16)DigDir_BCAN_WakeUp_INT, &LddLevel);
  if (LddLevel == (IoHwAb_LevelType)IOHWAB_LOW)
  {
    LddWakeupMask |= ECUM_WKSOURCE_BCAN_RX;
  }

  if(GetX(kb_NFC_OPTION)==On)
  {
    IoHwAb_DigDirReadDirect((uint16)DigDir_LCAN_WakeUp_INT, &LddLevel);
    if (LddLevel == (IoHwAb_LevelType)IOHWAB_LOW)
    {
      LddWakeupMask |= ECUM_WKSOURCE_LOCALCAN_RX;
    }
  }
#if 0
  if(ign_on_callout_is_on==1u)
  {
    ign_on_callout_is_on = 0u;
    LddWakeupMask |= ECUM_WKSOURCE_IGN_WakeUP;
  }
#endif

  if(GetX(kb_NFC_OPTION)==On)
  {
    //rfalDeinitialize();
    st25r3916Deinitialize();
    st25r3916IsOscOff();
    nfc_ticktimer_stop(); /* 20230527 : GPT Timer Stop */
  }
  else
  {
    nfc_ticktimer_stop(); /* 20230527 : GPT Timer Stop */
  }
  IoHwAb_PwmSetOutputToIdle(Pwm_AMBER_IND_OUT);
  IoHwAb_PwmSetOutputToIdle(Pwm_FAN_OUT);
  IoHwAb_PwmSetOutputToIdle(Pwm_GREEN_IND_OUT1);
  IoHwAb_PwmSetOutputToIdle(Pwm_GREEN_IND_OUT2);
  IoHwAb_PwmSetOutputToIdle(Pwm_GREEN_IND_OUT3);

  //Pwm_DeInit();
  if(GetX(kb_NFC_OPTION)==On)
  {
    IoHwAb_DigDirWriteDirect(DigDir_SPI_CS, 1);
  }

  IoHwAb_DigDirWriteDirect(DigDir_VBATSW_EN, 0);


  if (LddWakeupMask != ECUM_WKSOURCE_NONE)
  {
      /* Disable all Wakeup Signals */
      Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_BCAN_WakeUp);
      Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_BCAN_WakeUp);
      if(GetX(kb_NFC_OPTION)==On)
      {
        Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_LCAN_WakeUp);
        Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_LCAN_WakeUp);
      }
  }

  SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

  if ((LddWakeupMask & ECUM_WKSOURCE_BCAN_RX_POLL) == ECUM_WKSOURCE_BCAN_RX_POLL)
  {
    Slpwup_GulSleepProcessState = SLPWUP_EARLY_WAKEUP_DETECTED;
    /* Do not execute in interrupt disabled region */
    EcuM_SetWakeupEvent(ECUM_WKSOURCE_BCAN_RX_POLL);
  }
  else if ((LddWakeupMask & ECUM_WKSOURCE_LOCALCAN_RX_POLL) == ECUM_WKSOURCE_LOCALCAN_RX_POLL)
  {
    if(GetX(kb_NFC_OPTION)==On)
    {
      Slpwup_GulSleepProcessState = SLPWUP_EARLY_WAKEUP_DETECTED;
      /* Do not execute in interrupt disabled region */
      EcuM_SetWakeupEvent(ECUM_WKSOURCE_LOCALCAN_RX_POLL);
    }
  }
  else if ((LddWakeupMask & ECUM_WKSOURCE_BCAN_RX) == ECUM_WKSOURCE_BCAN_RX)
  {
    Slpwup_GulSleepProcessState = SLPWUP_EARLY_WAKEUP_DETECTED;
    /* Do not execute in interrupt disabled region */
    EcuM_SetWakeupEvent(ECUM_WKSOURCE_BCAN_RX);
  }
  else if ((LddWakeupMask & ECUM_WKSOURCE_LOCALCAN_RX) == ECUM_WKSOURCE_LOCALCAN_RX)
  {
    if(GetX(kb_NFC_OPTION)==On)
    {
      Slpwup_GulSleepProcessState = SLPWUP_EARLY_WAKEUP_DETECTED;
      /* Do not execute in interrupt disabled region */
      EcuM_SetWakeupEvent(ECUM_WKSOURCE_LOCALCAN_RX);
    }
  }
#if 0
  else if ((LddWakeupMask & ECUM_WKSOURCE_IGN_WakeUP) == ECUM_WKSOURCE_IGN_WakeUP)
  {
    Slpwup_GulSleepProcessState = SLPWUP_EARLY_WAKEUP_DETECTED;
    /* Do not execute in interrupt disabled region */
    EcuM_SetWakeupEvent(ECUM_WKSOURCE_IGN_WakeUP);
  }
#endif
  else
  {
    Slpwup_GulSleepProcessState = SLPWUP_GOTO_MCU_SLEEP;
  }




//#if (CRYPTOLIB_SUPORT_HSM_HAE_HSM_2_X == STD_ON)
  /* BCAN_RX */
  irqList[0] = 59;
  /* LCAN_RX */
  //irqList[1] = 59;



  /* set ECAN_RX, ICAN_RX to wakeup source of HSM core */
  ret = HSM_SetWakeupTrigger(irqList, 1);
  if (ret == E_OK)
  {
    /* Do not execute in interrupt disabled region */
      ret = HSM_Sleep();
      if (ret == E_OK)
      {
        /* HSM_Sleep succeeded */
      }

      if (ret != E_OK)
      {
        /* HSM_Sleep failed */
      }
  }

  if (ret != E_OK)
  {
      /* HSM_SetWakeupTrigger failed */
  }
//#endif

  if(Slpwup_GulSleepProcessState == SLPWUP_GOTO_MCU_SLEEP)
   {
       Slpwup_PreLPMode_Configuration();
   }

  User_H2L_Callout();

  //Port_Init(&PortConf_PortConfigSet_PortConfigSet_DeepSleep);
}

/*******************************************************************************
 * ISR Name             : EcuMIsr_Wakeup_CM7_1
 *
 * Service ID           : NA
 *
 * Description          : ISR to wakeup M7_1 Core
 *                        (It is generated in M7_1 Core)
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : None
 *
 * @pre                 : None
 *
 * @remarks             : None
 *
 ******************************************************************************/
#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
ISR(EcuMIsr_Wakeup_CM7_1)
{
  ECUM_IPC_STRUCUT2_INTR_MASK_REG = 0u;
  ECUM_IPC_STRUCUT2_INTR_SET_REG = 0u;
}
#endif
/*******************************************************************************
 * Function Name        : EcuM_L2HTransition_Callout_Swp
 *
 * Service ID           : NA
 *
 * Description          : Callout for SWP in Wakeup Sequence
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        WdgStack_TransitLowToHigh(), WdgM_PmModeChange(),
 *                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        IoHwAb_IOML2H(), Gpt_SetMode()
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_L2HTransition_Callout_Swp(void)
{
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  /* Wakeup for M0+ should be considered */
  
  /* Wakeup M7_1 Core */
  ECUM_IPC_STRUCUT2_INTR_SET_REG = 1u;
  ECUM_IPC_STRUCUT2_INTR_MASK_REG = 1u;
  #endif

  Slpwup_GulSleepProcessState = SLPWUP_L2H_TRANSITION_SWP;

  Slpwup_PostLPMode_Configuration();

  /* All channels and all enabled GPT Predef Timers are permitted to run.
   * Restart all enabled GPT Predef Timers
   * but does not restart any timer channels that were stopped */
  Gpt_SetMode(GPT_MODE_NORMAL);

  #if (IOHWAB_USE_IO_MAN == STD_ON)
  IoHwAb_IOML2H();
  #endif

  WdgStack_TransitLowToHigh();

  SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

  /* Resume OS Counter for Main Core */
  EcuM_Cm4ScsRegBaseAddr->SYST_CSR |= ECUM_SYST_CSR_ENABLE_MASK;
  /* Clear SLEEPDEEP bit from System Control Register in Core */
  EcuM_Cm4ScsRegBaseAddr->SCR &= ~ECUM_SCR_SLEEPDEEP_MASK;

  SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();
}

/*******************************************************************************
 * Function Name        : EcuM_L2HTransition_Callout_App
 *
 * Service ID           : NA
 *
 * Description          : User Callout for Wakeup Sequence
 *                        The application should take the necessary action here
 *                        before switching to RUN Mode
 *                        - Enable necessary peripherals in High Power Mode
 *                        - Disable Wakeup sources(ex: Icu channel, Gpt channel)
 *                        - Apply workaround for MCU Errata
 *                        - etc
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Lp_GaaAdcStatus, Lp_GulPitStatus, Lp_GaaStm0Status,
 *                        Lp_GaaStm2Status
 *
 *                        Function(s) invoked    :
 *                        Icu_DisableEdgeDetection(), Icu_DisableNotification(),
 *                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION()
 ******************************************************************************/
#include "WPCSleepControl.h"
#include "WPCTimer.h"
extern e_NFCState stateNFC;
extern Std_ReturnType HSM_Wakeup(void);
FUNC(void, ECUM_CALLOUT_CODE) EcuM_L2HTransition_Callout_App(void)
{
  Std_ReturnType ret = E_NOT_OK;

  cnt_wakeupwait = 0u;
  ADC_cnt = 0u;
  Slpwup_GulSleepProcessState = SLPWUP_L2H_TRANSITION_APP;

  ret = HSM_Wakeup();

  if (ret == E_OK)
  {
    /* HSM_Wakeup succeeded */
  }

  if (ret != E_OK)
  {
    /* HSM_Wakeup failed */
  }

  SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

  /* Disable all Wakeup Signals */
  Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_BCAN_WakeUp);
  Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_BCAN_WakeUp);

  if(GetX(kb_NFC_OPTION)==On)
  {
    Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_LCAN_WakeUp);
    Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_LCAN_WakeUp);
  }

  //Pwm_Init(&Pwm_GstConfiguration[0]);
  if(GetX(kb_NFC_OPTION)==On)
  {
    stateNFC = stsNFC_Init;
  }
  StartTimer(Timer_SleepWait);

  SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

  User_L2H_Callout();
}

FUNC(void, ECUM_CALLOUT_CODE) EcuM_Enable_Dma(void)
{
  uint32* dmactl = 0x402A0000;
  *dmactl |= 0x80000000;
}

/*******************************************************************************
 * Function Name        : EcuM_Boot_Callout
 *
 * Service ID           : NA
 *
 * Description          : User Callout for Before SWP Start
 *                        If MCU wakes up in Low Power Mode and operates as a
 *                        reset sequence. This callout can be used to identify
 *                        the wakeup and implement the required behavior.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : Interrupt cannot be used because it is before StartOS
 *                        Can not use SWP and MCAL API
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_Boot_Callout(void)
{
  /* Example: Check Wakeup Factor and action
   * If <Wakeup Factor == External Wakeup>
   * {
   *   <Necessary Functionality Initialize>
   *   <User Action>
   *   <Enter LP Again or Proceed to SWP Init>
   * }
   */
/* enable Dma for Fls */ 
EcuM_Enable_Dma();
}

/***************************************************************************//**
 * Function Name        : EcuM_Enable_Dma
 *
 * Service ID           : NA
 *
 * Description          : Enable Dma for Fls
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/

/*******************************************************************************
 * Function Name        : EcuM_PostInitUser
 *
 * Service ID           : NA
 *
 * Description          : User Callout called after DriverInitOne
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Icu_DisableEdgeDetection()
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_PostInitUser(void)
{
}

/***************************************************************************//**
 * Function Name        : CheckWakeup_BCAN_WakeUp
 *
 * Service ID           : NA
 *
 * Description          : Notification for IcuChannel_BCAN_WakeUp
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : The function name shall be set in the Signal
 *                        Notification field of the corresponding ICU Channel
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Icu_DisableEdgeDetection(), Icu_DisableNotification(),
 *                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        EcuM_SetWakeupEvent()
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) CheckWakeup_BCAN_WakeUp(void)
{
  cnt_wakeupwait++;

  if(cnt_wakeupwait >= 20u)
  {
  	cnt_wakeupwait = 0u;
  	
	SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

	Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_BCAN_WakeUp);
	Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_BCAN_WakeUp);

	wakeUpSource = CAN_WAKE_UP;

	/* Wakeup Sequence */
	EcuM_SetWakeupEvent(ECUM_WKSOURCE_BCAN_RX);

	StartTimer(Timer_SleepWait);
	Slpwup_GulSleepProcessingCount_Flag = 0u;
	f_BCAN_WakeupEvtOn = Off;

	Slpwup_modeRequestPort_ComMMode_FULL_COM();

	SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();
  }
}

/***************************************************************************//**
 * Function Name        : CheckWakeup_LCAN_WakeUp
 *
 * Service ID           : NA
 *
 * Description          : Notification for IcuChannel_LCAN_WakeUp
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : The function name shall be set in the Signal
 *                        Notification field of the corresponding ICU Channel
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Icu_DisableEdgeDetection(), Icu_DisableNotification(),
 *                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        EcuM_SetWakeupEvent()
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) CheckWakeup_LCAN_WakeUp(void)
{
  if(GetX(kb_NFC_OPTION)==On)
  {
    wakeUpSource = CAN_WAKE_UP;

    SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

    Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_LCAN_WakeUp);
    Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_LCAN_WakeUp);

    wakeUpSource = CAN_WAKE_UP;

    /* Wakeup Sequence */
    EcuM_SetWakeupEvent(ECUM_WKSOURCE_LOCALCAN_RX);

    SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();
  }
}

void User_H2L_Callout(void)
{
  /* user of App in Low Power Active Task set in the function */
  if(Slpwup_GulSleepProcessState == SLPWUP_GOTO_MCU_SLEEP)
  {
    #ifdef REQUIRED_RECONFIG_ADC
      /* Reconfigure ADC. firmware is used at LP Active mode to minimize code execution time */
      CyclicWakeup_Adc_Init();
    #endif
  }
}

void User_L2H_Callout(void)
{
  /*user of App in Low Power Active Task set in the function*/

  #ifdef REQUIRED_RECONFIG_ADC
    /* Disable ADC monitoring channel */
    Cy_Adc_Channel_DeInit(LP_ADC_CH_NO);
    Cy_Adc_DeInit(LP_ADC_HW_UNIT);
  #endif
}

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
