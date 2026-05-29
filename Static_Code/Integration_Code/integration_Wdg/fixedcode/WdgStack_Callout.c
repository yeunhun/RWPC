/*******************************************************************************
**                                                                            **
**  (C) 2016 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: WdgStack_Callout.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTRON WDG STACK CALLOUT                              **
**                                                                            **
**  PURPOSE   : Autron Watchdog stack Functionality                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.4.2     01-Jun-2021   YongHyun     Update #30107                         **
** 1.4.1     18-Mar-2021   YongHyun     Update #24041, #28846                 **
** 1.4.0     25-May-2020   YongHyun     Update #23683                         **
** 1.3.0     21-Apr-2020   YongHyun     Update #21787, #22236                 **
** 1.2.0     14-Aug-2019   YongHyun     Update #16891                         **
**                                      Update #18828                         **
** 1.1.4     21-Feb-2019   YongHyun     Update #15978                         **
** 1.1.3     05-Sep-2018   YongHyun     Update #13836                         **
**                                      Update #13917                         **
** 1.1.2     27-Mar-2018   YongHyun     Update #12135                         **
** 1.0.4     12-Jul-2016   Kuksun       Update #5513                          **
** 1.0.0     29-Apr-2016   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a Defect] "only comments or preprocessor directives above #include" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgStack_Callout.h"

#if ((WDGSTACK_ENABLE_INTERNAL_WDG == STD_ON) \
  || (WDGSTACK_ENABLE_EXTERNAL_WDG == STD_ON) \
  || (WDGSTACK_ENABLE == STD_ON))
#include "HwResource.h"
#endif

#if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
#include "Wdg.h"
#include "Reg_Macros.h"
#include "Reg_eSys_Swt.h"
#endif

#if (WDGSTACK_ENABLE_INTERNAL_WDG == STD_ON)
#if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
#include "Wdg_Swt_LLD.h"
#include "Gpt.h"
#elif HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
#include "Wdg_17_Scu.h"
#elif HWRESOURCE_VENDOR(HWRESOURCE_RENESAS)
#include "Wdg_59_DriverA.h"
#include "Wdg_59_DriverA_Private.h"
#if HWRESOURCE_MCU(HWRESOURCE_RH850F1K)
#include "Wdg_59_DriverA_Irq.h"
#include "Wdg_59_DriverA_Cfg.h"
#elif HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
#include "Wdg_59_DriverA_PBTypes.h"
#endif
#elif HWRESOURCE_VENDOR(HWRESOURCE_CYPRESS)
#include "Wdg_66_IA_Controller.h"
#elif HWRESOURCE_VENDOR(HWRESOURCE_ST)
#include "Wdg_27_INT.h"
#include "Wdg_Swt_LLD.h"
#include "Wdg_27_INTCfg.h"
#elif HWRESOURCE_VENDOR(HWRESOURCE_NXP)
#include "Gpt.h"
#include "Wdg_Cfg.h"
#if HWRESOURCE_FAMILY(HWRESOURCE_S32K14X)
#include "Wdg_IPW_Types.h"
#include "Wdg.h"
#include "Wdg_Wdog.h"
#elif HWRESOURCE_FAMILY(HWRESOURCE_S32G2X)
#include "Wdg_IPW_Types.h"
#include "Wdg_ChannelTypes.h"
#if (WDG_INSTANCE0 == STD_ON)
#include "Wdg_43_Instance0.h"
#endif
#if (WDG_INSTANCE1 == STD_ON)
#include "Wdg_43_Instance1.h"
#endif
#if (WDG_INSTANCE2 == STD_ON)
#include "Wdg_43_Instance2.h"
#endif
#if (WDG_INSTANCE3 == STD_ON)
#include "Wdg_43_Instance3.h"
#endif
#if (WDG_INSTANCE4 == STD_ON)
#include "Wdg_43_Instance4.h"
#endif
#if (WDG_INSTANCE5 == STD_ON)
#include "Wdg_43_Instance5.h"
#endif
#if (WDG_INSTANCE6 == STD_ON)
#include "Wdg_43_Instance6.h"
#endif
#endif
#endif
#endif /* (WDGSTACK_ENABLE_INTERNAL_WDG == STD_ON) */

#if (WDGSTACK_ENABLE_EXTERNAL_WDG == STD_ON)
#include "Wdg_76_Acw.h"
#include "Wdg_76_Acw_Config.h"
#endif /* (WDGSTACK_ENABLE_EXTERNAL_WDG == STD_ON) */

#if (WDGSTACK_ENABLE == STD_ON)
#include "WdgM.h"
#endif /* (WDGSTACK_ENABLE == STD_ON) */

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/

/*******************************************************************************
** Function Name      : WdgStack_DisableIntWdg                                **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : Disable internal watchdog while booting               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) : None                             **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
void WdgStack_DisableIntWdg(void)
{
  /* Bolero is need to clear soft lock of Internal Watchdog on initial sequence 
  Because internal Watchdog automatically set to soft lock as 100ms time out 
  period after reset */
  #if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
  {
    /* polyspace-begin RTE:IDP [Not a Defect] "pointer have to be used for setting register" */
    /* polyspace-begin MISRA-C3:D4.1 [Not a Defect] "pointer have to be used for setting register" */
    /* polyspace-begin MISRA-C3:18.1 [Not a Defect] "pointer operation is inside with pre-defined range" */
    REG_WRITE32(SWT_SR(0), SWT_UNLOCK_SEQ1);
    REG_WRITE32(SWT_SR(0), SWT_UNLOCK_SEQ2);

    /* polyspace-begin RTE:NIV [Not a Defect] "use MCAL macro for setting register" */
    /* Prevent to hard lock by clear bit for Disable watchdog */
    REG_BIT_CLEAR32(SWT_CR(0), SWT_WDG_ENABLED);
    /* polyspace-end RTE:NIV */
    /* polyspace-end MISRA-C3:18.1 */
    /* polyspace-end MISRA-C3:D4.1 */
    /* polyspace-end RTE:IDP */
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
  {
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_RENESAS)
  {
  }
  #endif
}

#if (WDGSTACK_INIT_USING_ECUM == STD_OFF)
/*******************************************************************************
** Function Name      : WdgStack_Init                                         **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : Initialize watchdog stack modules                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) : None                             **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
void WdgStack_Init(void)
{
  #if (WDGSTACK_ENABLE_INTERNAL_WDG == STD_ON)
  #if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
  {
    Wdg_Init(NULL_PTR);
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
  {
    Wdg_17_Scu_Init(&Wdg_ConfigRoot[0]);
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_RENESAS)
  {
    Wdg_59_DriverA_Init(&Wdg_59_DriverA_GstConfiguration); 
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_ST)
  {
    Wdg_27_INT_Init(NULL_PTR);
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_NXP)
  {
    #if HWRESOURCE_FAMILY(HWRESOURCE_S32K14X)
    Wdg_Init(&WdgSettingsConfig);
    #endif
  }
  #endif
  #endif /* (WDGSTACK_ENABLE_INTERNAL_WDG == STD_ON) */

  #if (WDGSTACK_ENABLE_EXTERNAL_WDG == STD_ON)
  {
    Wdg_76_Acw_Init(NULL_PTR);
  }
  #endif /* (WDGSTACK_ENABLE_EXTERNAL_WDG == STD_ON) */

  #if (WDGSTACK_ENABLE == STD_ON)
  {
    WdgM_Init(NULL_PTR);
  }
  #endif /* (WDGSTACK_ENABLE == STD_ON) */
}
#endif/* (WDGSTACK_INIT_USING_ECUM == STD_OFF) */


/*******************************************************************************
** Function Name      : WdgStack_TransitHighToLow                             **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : Control watchdog stack modules while high to low      **
**                      transition occurs                                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) : None                             **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
void WdgStack_TransitHighToLow(void)
{
  /* Internal Watchdog */
  #if (WDGSTACK_ENABLE_INTERNAL_WDG == STD_ON)
  #if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
  {
    uint32 LddSwtCR = 0x00000000UL;

    /* polyspace-begin RTE:IDP [Not a Defect] "pointer have to be used for setting register" */
    /* polyspace-begin MISRA-C3:D4.1 [Not a Defect] "pointer have to be used for setting register" */
    /* polyspace-begin MISRA-C3:18.1 [Not a Defect] "pointer operation is inside with pre-defined range" */
    /* polyspace-begin RTE:NIV [Not a Defect] "use MCAL macro for setting register" */
    LddSwtCR = REG_READ32(SWT_CR(0));

    /* Disable watchdog */
    /* polyspace<RTE:NIV:Not a defect:Justify with annotations> use MCAL macro for setting register */
    REG_BIT_CLEAR32(SWT_CR(0), SWT_WDG_ENABLED);
    /* polyspace-end RTE:NIV */

    /* Set Timer-out register */
    REG_WRITE32(SWT_TO(0), 0x00003200UL);

    /* Set window register */
    REG_WRITE32(SWT_WN(0), 0x00003200UL);

    /* Set the Control Register */
    REG_WRITE32(SWT_CR(0), LddSwtCR);

    /* Stop timer for watchdog trigger */
    Gpt_StopTimer(Wdg_ConfigPtr[0]->Gpt_Channel);
    /* polyspace-end MISRA-C3:18.1 */
    /* polyspace-end MISRA-C3:D4.1 */
    /* polyspace-end RTE:IDP */

  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
  {
    /* Not supported */
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_RENESAS)
  {
    /* It's not possible to change the configuration of the internal wdg after
      it has started */
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_NXP)
  {
    /* Stop timer for watchdog trigger */
    #if HWRESOURCE_FAMILY(HWRESOURCE_S32K14X)
    Gpt_StopTimer(WdgSettingsConfig.Wdg_TimerChannel);
    #elif HWRESOURCE_FAMILY(HWRESOURCE_S32G2X)
    {
      #if (WDG_INSTANCE0 == STD_ON)
      Gpt_StopTimer(Wdg_Config_0.Wdg_TimerChannel);
      #endif
      #if (WDG_INSTANCE1 == STD_ON)
      Gpt_StopTimer(Wdg_Config_1.Wdg_TimerChannel);
      #endif
      #if (WDG_INSTANCE2 == STD_ON)
      Gpt_StopTimer(Wdg_Config_2.Wdg_TimerChannel);
      #endif
      #if (WDG_INSTANCE3 == STD_ON)
      Gpt_StopTimer(Wdg_Config_3.Wdg_TimerChannel);
      #endif
      #if (WDG_INSTANCE4 == STD_ON)
      Gpt_StopTimer(Wdg_Config_4.Wdg_TimerChannel);
      #endif
      #if (WDG_INSTANCE5 == STD_ON)
      Gpt_StopTimer(Wdg_Config_5.Wdg_TimerChannel);
      #endif
      #if (WDG_INSTANCE6 == STD_ON)
      Gpt_StopTimer(Wdg_Config_6.Wdg_TimerChannel);
      #endif
    }
    #endif
  }
  #endif
  #endif /* (WDGSTACK_ENABLE_INTERNAL_WDG == STD_ON) */

  /* External Watchdog */
  #if (WDGSTACK_ENABLE_EXTERNAL_WDG == STD_ON)
  /* Stop timer for watchdog trigger */
  Gpt_StopTimer(Wdg_76_Acw_GptChannel);
  #endif /* (WDGSTACK_ENABLE_EXTERNAL_WDG == STD_ON) */

  WdgStack_TriggerWatchdog();
}

/*******************************************************************************
** Function Name      : WdgStack_TransitLowToHigh                             **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : Control watchdog stack modules while low to high      **
**                      transition occurs                                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) : None                             **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
void WdgStack_TransitLowToHigh(void)
{
  WdgStack_TriggerWatchdog();

  #if (WDGSTACK_ENABLE == STD_ON)
  #if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
  {
    (void) WdgM_PmModeChange(WDGM_PM_MODE_HP_REQ);
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
  {
    /* Not supported */
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_RENESAS)
  {
    (void) WdgM_PmModeChange(WDGM_PM_MODE_HP_REQ);
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_CYPRESS)
  {
    #if ( HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX) || HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX) || HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX) )
    (void) WdgM_PmModeChange(WDGM_PM_MODE_HP_REQ);
    #endif
  }
  #endif
  #endif /* (WDGSTACK_ENABLE == STD_ON) */
}

/*******************************************************************************
** Function Name      : WdgStack_TriggerWatchdog                              **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : Trigger watchdog stack modules                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) : None                             **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:8.7:Not a defect:Justify with annotations> below function could be used externally */
void WdgStack_TriggerWatchdog(void)
/* polyspace:end<MISRA-C3:8.7> */
{
  /* Internal Watchdog */
  #if (WDGSTACK_ENABLE_INTERNAL_WDG == STD_ON)
  #if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
  {
    Wdg_SWT_Trigger((Wdg_IPW_InstanceType) WDG_IPW_INSTANCE0);
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
  {
    /* Not supported */
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_RENESAS)
  {
    /* The window period of the internal wdg should be 100% */
    
    #if HWRESOURCE_MCU(HWRESOURCE_RH850F1K)
    Wdg_59_DriverA_TriggerFunc(WDG_59_DRIVERA_TRIGGER_FUNCTION_ISR_SID);   
   
    #elif HWRESOURCE_MCU(HWRESOURCE_RH850F1L)
    Wdg_59_DriverA_TriggerFunc(WDG_59_DRIVERA_INCLUDE_CRITICAL_SECTION);

    #elif HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
    Wdg_59_DriverA_TriggerFunc(WDG_59_DRIVERA_INCLUDE_CRITICAL_SECTION);
    
    #else
   
    #error "Not supported MCU Package, Contact to the Module Manager"
    
    #endif
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_CYPRESS)
  {
    #if HWRESOURCE_FAMILY(HWRESOURCE_S6J32XX)
    {
      Wdg_66_IA_Internal_ActivateTrigger();
    }
    #elif HWRESOURCE_FAMILY(HWRESOURCE_S6J33XX)
    {
      Wdg_66_IA_Internal_ActivateTrigger();
    }
    #elif HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)
    {
      /* Not supported */
    }
    #endif
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_ST)
  {
    Wdg_SWT_Trigger(Wdg_27_INT_ConfigPtr->Wdg_CfgServiceMode, Wdg_27_INT_ConfigPtr->Wdg_SwtBaseAddress);
  }
  #elif HWRESOURCE_VENDOR(HWRESOURCE_NXP)  
  {
    #if HWRESOURCE_FAMILY(HWRESOURCE_S32K14X)
    {
      #ifdef WDG_INSTANCE0
      #if (WDG_INSTANCE0 == STD_ON)
      Wdg_Wdog_Trigger(WDG_IPW_INSTANCE0);
      #endif
      #endif

      #ifdef WDG_INSTANCE1
      #if (WDG_INSTANCE1 == STD_ON)
      Wdg_Wdog_Trigger(WDG_IPW_INSTANCE1);
      #endif
      #endif

      #ifdef WDG_INSTANCE2
      #if (WDG_INSTANCE2 == STD_ON)
      Wdg_Wdog_Trigger(WDG_IPW_INSTANCE2);
      #endif
      #endif

      #ifdef WDG_INSTANCE3
      #if (WDG_INSTANCE3 == STD_ON)
      Wdg_Wdog_Trigger(WDG_IPW_INSTANCE3);
      #endif
      #endif

      #ifdef WDG_INSTANCE4
      #if (WDG_INSTANCE4 == STD_ON)
      Wdg_Wdog_Trigger(WDG_IPW_INSTANCE4);
      #endif
      #endif
    }
    #elif HWRESOURCE_FAMILY(HWRESOURCE_S32G2X)
    {
      #if (WDG_DIRECT_SERVICE_INSTANCE0 == STD_ON)
      Wdg_43_Instance0_Service();
      #endif
      #if (WDG_DIRECT_SERVICE_INSTANCE1 == STD_ON)
      Wdg_43_Instance1_Service();
      #endif
      #if (WDG_DIRECT_SERVICE_INSTANCE2 == STD_ON)
      Wdg_43_Instance2_Service();
      #endif
      #if (WDG_DIRECT_SERVICE_INSTANCE3 == STD_ON)
      Wdg_43_Instance3_Service();
      #endif
      #if (WDG_DIRECT_SERVICE_INSTANCE4 == STD_ON)
      Wdg_43_Instance4_Service();
      #endif
      #if (WDG_DIRECT_SERVICE_INSTANCE5 == STD_ON)
      Wdg_43_Instance5_Service();
      #endif
      #if (WDG_DIRECT_SERVICE_INSTANCE6 == STD_ON)
      Wdg_43_Instance6_Service();
      #endif
    }
    #endif
  }
  #endif
  #endif /* (WDGSTACK_ENABLE_INTERNAL_WDG == STD_ON) */

  /* External Watchdog */
  #if (WDGSTACK_ENABLE_EXTERNAL_WDG == STD_ON)
  Wdg_76_Acw_Trigger();
  #endif /* (WDGSTACK_ENABLE_EXTERNAL_WDG == STD_ON) */
}

#if HWRESOURCE_VENDOR(HWRESOURCE_TI)
Std_ReturnType Wdg_SetMode(uint32 Mode)
{
  Std_ReturnType ret = E_OK;
  return ret;
}
#endif

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
