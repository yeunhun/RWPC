/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : EcuM.c                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : APIs implementation for EcuM module                           **
**              EcuM_GetVersionInfo                                           **
**              EcuM_Init                                                     **
**              EcuM_GoDown                                                   **
**              EcuM_Shutdown                                                 **
**              EcuM_SelectShutdownTarget                                     **
**              EcuM_GetShutdownTarget                                        **
**              EcuM_GetLastShutdownTarget                                    **
**              EcuM_SelectShutdownCause                                      **
**              EcuM_GetShutdownCause                                         **
**              EcuM_GetMostRecentShutdown                                    **
**              EcuM_GetNextRecentShutdown                                    **
**              EcuM_GetPendingWakeupEvents                                   **
**              EcuM_ClearWakeupEvent                                         **
**              EcuM_GetValidatedWakeupEvents                                 **
**              EcuM_GetExpiredWakeupEvents                                   **
**              EcuM_SelectBootTarget                                         **
**              EcuM_GetBootTarget                                            **
**              EcuM_StartupTwo                                               **
**              EcuM_GoHalt                                                   **
**              EcuM_GoPoll                                                   **
**              EcuM_MainFunction                                             **
**              EcuM_SetRelWakeupAlarm                                        **
**              EcuM_SetAbsWakeupAlarm                                        **
**              EcuM_AbortWakeupAlarm                                         **
**              EcuM_GetCurrentTime                                           **
**              EcuM_GetWakeupTime                                            **
**              EcuM_SetClock                                                 **
**              EcuM_GetResetReason                                           **
**              EcuM_IsMasterCore                                             **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
** 3.1.1      17-Dec-2021   Junho Cho     Redmine #33385                      **
** 3.1.0      24-Nov-2021   Junho Cho     Redmine #33037                      **
** 3.0.5      17-Aug-2021   Junho Cho     Redmine #30595, #31552              **
** 3.0.4      06-Jan-2021   Manje Woo     Redmine #27327, #27140              **
** 3.0.3      25-Nov-2020   Manje Woo     Redmine #18654                      **
** 3.0.0      27-Jun-2019   Manje Woo     Redmine #17238, #16766, #17850,     **
**                                                #16798, #16618, #16271,     **
**                                                #14440                      **
** 2.10.0     19-Jun-2018   Sanghoon Bae  Redmine #13076                      **
** 2.9.0      17-Apr-2018   Sanghoon Bae  Redmine #12242 #12323               **
** 2.8.0      17-Oct-2017   Sanghoon Bae  Redmine #10090                      **
** 2.7.3      16-May-2017   Sanghoon Bae  Redmine #8550 #8552                 **
** 2.7.2      23-Mar-2017   Sanghoon Bae  Redmine #7886 #7887                 **
** 2.7.0      21-Oct-2016   Sanghoon Bae  Redmine #6350 #6639                 **
** 2.6.3      06-Oct-2016   Sanghoon Bae  Redmine #6144                       **
** 2.6.2      29-Aug-2016   Sanghoon Bae  Redmine #5876                       **
** 2.5.5      08-Jul-2016   Sanghoon Bae  Redmine #5257                       **
** 2.5.3      12-Jan-2016   Daejun Park   Redmine #3856                       **
**                                        -Update precompile option           **
** 2.5.2      04-Dec-2015   Daejun Park   Redmine #3599                       **
**                                        -Change ResetReason type            **
** 2.5.1      12-Oct-2015   Sanghoon Bae  Redmine #3035                       **
** 2.5.0      20-Aug-2015   Sanghoon Bae  Redmine #2571, #2583                **
**                                        -Add EcuM_GetResetReason function   **
**                                        -Update EcuM_GoHalt, EcuM_GoPoll    **
** 2.4.2      10-Jun-2015   Jihoon Jung   Redmine #2702                       **
**                                        -Update EcuM_Init function          **
** 2.4.1      27-May-2015   Jihoon Jung   Redmine #2550                       **
** 2.4.0      06-May-2015   Jihoon Jung   Redmine #2547                       **
**                                        -Update EcuM_GoHalt function        **
**            06-May-2015   Jihoon Jung   Redmine #2546                       **
**                                        -Update EcuM_AbortWakeupAlarm       **
**                                         function                           **
**            04-May-2015   Jihoon Jung   Redmine #2544                       **
**                                        -Runtime Error Fix in EcuM_Init     **
** 2.3.2      24-Apr-2015   Jihoon Jung   Redmine #2510                       **
**                                        -EcuM_ClearWakeupEvent don't report **
**                                         ECUM_E_UNKNOWN_WAKEUP_SOURCE to    **
**                                         DET when called with               **
**                                         ECUM_WKSOURCE_ALL_SOURCES          **
**            20-Apr-2015   Jihoon Jung   Redmine #2506                       **
**                                        -Set return value of                **
**                                         EcuM_SetRelWakeupAlarm,            **
**                                         EcuM_SetAbsWakeupAlarm             **
**                                         to E_NOT_OK if                     **
**                                         ECUM_ALARM_CLOCK_PRESENT==STD_OFF  **
**            29-Mar-2015   Daejun Park   Redmine #2376 #2388                 **
**                                        -Add ECUM_PM_ENABLED macro          **
**                                        -Update GoHalt and                  **
**                                         AbortWakeupAlarm function          **
** 2.3.0      12-Mar-2015   Daejun Park   Redmine #2321                       **
**                                        -Update sleep/wakeup flags          **
** 2.2.1      12-Mar-2015   Daejun Park   Redmine #1879                       **
**                                        -Update to AUTRON template          **
** 2.2.0      26-Nov-2014   Daejun Park   Modify alarm wakeup process         **
** 2.1.0      24-Sep-2014   Daejun Park   Redmine #1367                       **
** 2.0.0      24-Apr-2014   Daejun Park   Update major version                **
** 1.2.0      10-Apr-2014   Daejun Park   Update Gpt_StartTimer caller        **
** 1.1.0      07-Mar-2014   Daejun Park   Remove binary search APIs           **
** 1.0.12     13-Dec-2013   Daejun Park   CR~208, XAR~779                     **
**                                        -Include Gpt.h                      **
**                                        -Move pre-compile condition         **
**                                         to EcuM_Callout.c                  **
** 1.0.10     04-Jul-2013   Daejun Park   CR~129, XAR~581 : Dem event         **
**                                        -pre-compile condition has been     **
**                                         added for EcuM_Dem_Cfg.h file and  **
**                                         Dem_ReportErrorStatus() function   **
** 1.0.9      11-Jun-2013   Daejun Park   CR~108, XAR~545 : Multicore support **
**                                        -Add inclusion of header file       **
**                                         Os_PortTypes.h                     **
** 1.0.8      07-Jun-2013   Daejun Park   CR~119, XAR~558 : EcuM library      **
**                                        -Add inclusion of header file       **
**                                         EcuM_Config.h                      **
**                                        -Convert macro to constant variables**
**                                         EcuM_GucOsNumberOfCores,           **
**                                         EcuM_GucNoOfGoDownUsers,           **
**                                         EcuM_GucNoOfSleepModes,            **
**                                         EcuM_GucNoOfShutdownCause,         **
**                                         EcuM_GucNoOfWakeupSources,         **
**                                         EcuM_GucNoOfClockUsers             **
** 1.0.0      04-Mar-2013   Daejun Park   Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin RTE:UNR [Justified:Medium] "AUTOEVER_RTE_UNR" */
/* polyspace-begin MISRA-C3:D4.14 [Not a defect:Medium] "Not from external sources" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "EcuM_Ram.h"
#include "EcuM_Internal.h"
#include "EcuM_Config.h"

#include "Rte_EcuM.h"
#include "SchM_EcuM.h"
#include "BswM.h"
#include "BswM_EcuM.h"
#include "Rte_Main.h"
#if (ECUM_DEMERROR_REPORT == STD_ON)
#include "EcuM_Dem_Cfg.h"
#endif
#include "Os.h"
#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
#include "Os_PortTypes.h"
#endif
#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
#include "Gpt.h"
#endif
#if (ECUM_PM_ENABLED == STD_ON)
#include "Pm.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define ECUM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : EcuM_GetVersionInfo                                 **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This Service returns the version information of ECU **
**                        State Manager Module.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
#if (ECUM_VERSION_INFO_API == STD_ON)
FUNC(void, ECUM_CODE) EcuM_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, ECUM_APPL_DATA) versioninfo)
{
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)

  /* check NULL pointer */
  if (versioninfo == NULL_PTR)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETVERSIONINFO_SID, ECUM_E_NULL_POINTER);
  }
  else
  #endif
  {
    /* Load the vendor Id */
    versioninfo->vendorID = ECUM_VENDOR_ID;

    /* Load the module Id */
    versioninfo->moduleID = ECUM_MODULE_ID;

    /* Load Software Major Version */
    versioninfo->sw_major_version = ECUM_SW_MAJOR_VERSION;

    /* Load Software Minor Version */
    versioninfo->sw_minor_version = ECUM_SW_MINOR_VERSION;

    /* Load Software Patch Version */
    versioninfo->sw_patch_version = ECUM_SW_PATCH_VERSION;
  }
} /* End of EcuM_GetVersionInfo */


#endif /* (ECUM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : EcuM_Init                                           **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This Service initializes the ECU State Manager and  **
**                        carries out the startup-1 procedure.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        EcuM_GblInitStatus, EcuM_GpEcuMConfigPtr,           **
**                        EcuM_GaaLcfgHashValue, EcuM_GaaAlarmTime            **
**                        EcuM_GaaAlarmClock                                  **
**                        Function(s) invoked    :                            **
**                        GetCoreID, EcuM_AL_SetProgrammableInterrupts,       **
**                        EcuM_AL_DriverInitZero, Dem_ReportErrorStatus,      **
**                        EcuM_DeterminePbConfiguration, EcuM_ErrorHook,      **
**                        EcuM_AL_DriverInitOne, StartOS, StartCore,          **
**                        EcuM_LoopDetection, EcuM_SelectShutdownTarget,      **
**                        Mcu_GetResetReason, EcuM_CheckResetReason           **
**                        EcuM_PostInit                                       **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_Init(void)
{
  /* Local pointer for the Hash array EcuM_GaaLcfgHashValue[] */
  P2CONST(uint32, ECUM_CONST, ECUM_CONST) LpLcfgHashValue;
  uint32 LulIndex;
  uint8 LucSleepModeIndex;
  boolean LblResult;
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  CoreIdType LddCoreId;
  StatusType LddStatus;
  /* FOR loop index variable */
  uint8 LucCoreIdx;
  #endif

  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  uint8 LucAlarmIndx;
  #endif

  /* Variable for Hash array index */
  uint8 LucHashIndex;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /*  TO BE FIXED: Must be out of STD_ON Flag -BSH 20150828  */
  /* Set the variable EcuM_GblInitStatus to indicate EcuM is initialized */
  EcuM_GblInitStatus = ECUM_INITIALIZED;
  #endif

  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  /* Get the core id of currently running core */
  LddCoreId = GetCoreID();
  if (LddCoreId == EcuM_GaaCoreID[ECUM_ZERO])
  #endif
  {
    #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)

    for (LucAlarmIndx = (uint8)ECUM_ZERO; LucAlarmIndx < EcuM_GucNoOfAlarms;
         LucAlarmIndx++)
    {
      /* Initialize the run time AlarmTime array with configured value */
      EcuM_GaaAlarmTime[LucAlarmIndx] =
        EcuM_GaaAlarmClock[LucAlarmIndx].usAlarmClockTimeOut;
    }

    #endif

    /*  EcuM_AL_SetProgrammableInterrupts shall set the interrupts on
     *  ECUs with programmable interrupts. */
    /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "AUTOEVER_MISRA_2_2" */
    EcuM_AL_SetProgrammableInterrupts();

    /*
     * Driver initialization and hardware related startup activity for
     * loading postbuild configuration data
     */
    EcuM_AL_DriverInitZero();

    /* Get the configuration pointer into the global variable */
    EcuM_GpEcuMConfigPtr = EcuM_DeterminePbConfiguration();

    /* polyspace:begin<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Checking of NULL_PTR is for fail-safety */
    /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Checking of NULL_PTR is for fail-safety" */
    /* polyspace +2 MISRA-C3:2.1 [Justified:Medium] "Defensive programming" */
    /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "Defensive programming" */
    if (EcuM_GpEcuMConfigPtr == NULL_PTR)
    {
      #if (ECUM_DEV_ERROR_DETECT == STD_ON)
      (void)EcuM_DetReportError(ECUM_INIT_SID, ECUM_E_NULL_POINTER);
      #endif
    }
    /* polyspace:end<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Checking of NULL_PTR is for fail-safety */
    /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Checking of NULL_PTR is for fail-safety" */
    else
    {
      /* Get the index of Hash array from PB configuration structure */
      /*  Fix for Run time error orange -150910 BSH  */
      LucHashIndex = (uint8)ECUM_ZERO;

      /* polyspace +3 RTE:IDP [Justified:Medium] "AUTOEVER_RTE_IDP" */
      /* polyspace +2 RTE:NIP [Justified:Medium] "AUTOEVER_RTE_NIP" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Medium] "AUTRON_MISRA_18_1" */
      if( EcuM_GpEcuMConfigPtr->pEcuMConfigConsistencyHash != NULL_PTR )
      {
        /* Update the pointer with Hash array */
        LpLcfgHashValue = &EcuM_GaaLcfgHashValue[LucHashIndex];

        LulIndex = (uint32)ECUM_ZERO;
        /* Check Consistency of Configuration Data */
        while (LulIndex < (uint32)ECUM_TWO)
        {
          /* polyspace +4 RTE:IDP [Justified:Medium] "AUTOEVER_RTE_IDP" */
          /* polyspace +3 RTE:NIV [Justified:Medium] "AUTOEVER_RTE_NIV" */
          /* polyspace +2 MISRA-C3:18.1 [Justified:Medium] "AUTOEVER_MISRA_18_1" */
          if (LpLcfgHashValue[LulIndex]!=
              EcuM_GpEcuMConfigPtr->pEcuMConfigConsistencyHash[LulIndex])
          {
            #if (ECUM_DEMERROR_REPORT == STD_ON)
            Dem_ReportErrorStatus(EcuM_GusEConfigurationDataInconsistent,
              DEM_EVENT_STATUS_FAILED);
            # endif
            EcuM_ErrorHook((Std_ReturnType)E_OK);

            /* To come out of FOR loop */
            LulIndex = (uint32)ECUM_TWO;
          }
          LulIndex++;
        }

        /* Driver initialization and hardware related startup activity for
         *   loading postbuild configuration data */
        EcuM_AL_DriverInitOne(EcuM_GpEcuMConfigPtr);

        /* Init Callout For After Mcal Init */
        /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "AUTOEVER_MISRA_2_2" */
        EcuM_PostInit();

        /* Driver initialization and other hardware-related startup activities
         *   in case of a power on reset */
        /* Update Reset reason */
        EcuM_GddResetReason = Mcu_GetResetReason();
        EcuM_CheckResetReason(EcuM_GddResetReason);

        EcuM_GusSleepModeId = ECUM_INVALID_SLEEPMODEID;

        /* polyspace +1 RTE:NIV [Justified:Medium] "AUTOEVER_RTE_NIV" */
        if (EcuM_GpEcuMConfigPtr->ddEcuMDefaultState == ECUM_STATE_SLEEP)
        {
          /* Select Default shutdown target and Index to Sleep mode */
          /* polyspace +2 RTE:NIV [Justified:Medium] "AUTOEVER_RTE_NIV" */
          (void)EcuM_SelectShutdownTarget(EcuM_GpEcuMConfigPtr->ddEcuMDefaultState,
            EcuM_GpEcuMConfigPtr->ucEcuMDefaultSleepMode);

          LblResult = EcuM_SearchMode(&LucSleepModeIndex, EcuM_GpEcuMConfigPtr->ucEcuMDefaultSleepMode);
          if (LblResult == ECUM_TRUE)
          {
            EcuM_GusSleepModeId = (uint16)LucSleepModeIndex;
          }
        }
        else if (EcuM_GpEcuMConfigPtr->ddEcuMDefaultState == ECUM_STATE_RESET)
        {
          /* Select Default shutdown target and Index to Reset mode */
          /* polyspace +2 RTE:NIV [Justified:Medium] "AUTOEVER_RTE_NIV" */
          (void)EcuM_SelectShutdownTarget(EcuM_GpEcuMConfigPtr->ddEcuMDefaultState,
            EcuM_GpEcuMConfigPtr->ucEcuMDefaultResetMode);
        }
        else
        {
          /* Select Default shutdown target and Index to zero */
          (void)EcuM_SelectShutdownTarget(EcuM_GpEcuMConfigPtr->ddEcuMDefaultState,
            (uint8)ECUM_ZERO);
        }

        #if (ECUM_RESET_LOOP_DETECTION == STD_ON)
        EcuM_LoopDetection();
        #endif
      }
    }

  }
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  else
  {
    /* Get the configuration pointer into the global variable */
    EcuM_GpEcuMConfigPtr = EcuM_DeterminePbConfiguration();
  }
  #endif

  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  if (LddCoreId == OS_CORE_ID_MASTER)
  {
    /* StartCore exclude master core */
    for (LucCoreIdx = (uint8)ECUM_ZERO; LucCoreIdx < EcuM_GucNoOfCores; LucCoreIdx++)
    {
      if (EcuM_GaaCoreID[LucCoreIdx] != OS_CORE_ID_MASTER)
      {
        StartCore(EcuM_GaaCoreID[LucCoreIdx], &LddStatus);
        /* polyspace +2 RTE:NIVL [Not a defect:Low] "value LddStatus is assigned by StartCore function" */
        /* polyspace +1 MISRA-C3:9.1 [Justified:Low] "value LddStatus is assigned by StartCore function" */
        if(LddStatus != E_OK)
        {
          #if (ECUM_DEV_ERROR_DETECT == STD_ON)
          (void)EcuM_DetReportError(ECUM_INIT_SID, ECUM_E_START_CORE_FAILED);
          #endif
        }
      }
    }
  }
  #endif /* End of if (ECUM_MULTI_CORE_SUPPORT == STD_ON) */

  /* Start the OS with default application mode */
  /* polyspace<RTE: NTC : Not a defect : No Action Planned > Due to idle loop in StartOS */
  StartOS(EcuM_GddDefaultAppMode);
} /* End of EcuM_Init */

/*******************************************************************************
** Function Name        : EcuM_GoDown                                         **
**                                                                            **
** Service ID           : 0x1f                                                **
**                                                                            **
** Description          : This Service instructs the ECU State Manager module **
**                        to perform a power off or a reset depending on the  **
**                        selected shutdown target.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : caller                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : (E_OK or E_NOT_OK)                                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GaaGoDownAllowedUser,      **
**                        EcuM_GucSelectShutdownTarget, EcuM_GpEcuMConfigPtr  **
**                        EcuM_GddPendingWakeupEvents, EcuM_GucShutdownMask   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, Dem_ReportErrorStatus,         **
**                        GetCoreID, EcuM_OnGoOffOne, BswM_Deinit,            **
**                        SchM_Deinit, EcuM_SelectShutdownTarget,  ShutdownOS,**
**                        SetEvent, ShutdownAllCores,                         **
**                        SchM_Enter_EcuM_SHUTDOWN_FLAG_PROTECTION(),         **
**                        SchM_Exit_EcuM_SHUTDOWN_FLAG_PROTECTION()           **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoDown(uint16 caller)
{
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  CoreIdType LddCoreId;
  #endif

  #if (ECUM_DEF_BEHAVIOUR_ENABLED == STD_ON)
  boolean LblCallerFlag;
  /* Variable to store the array index where the user is present */
  uint8 LucGoDownUserInd;
  #endif

  Std_ReturnType LddStdRetVal;
  LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)

  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GODOWN_SID, ECUM_E_UNINIT);
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  /* Module is initialized */
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEF_BEHAVIOUR_ENABLED == STD_OFF)
    ECUM_UNUSED(caller);
    #else
    /* polyspace +1 MISRA-C3:10.3 [Justified:Medium] "caller is limited by EcuMFlexUserConfig" */
    LblCallerFlag = EcuM_SearchGoDownUser(&LucGoDownUserInd, caller);

    ECUM_UNUSED(LucGoDownUserInd);

    if (LblCallerFlag != ECUM_TRUE)
    {
      Dem_ReportErrorStatus(EcuM_GusEImproperCaller, DEM_EVENT_STATUS_FAILED);

      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif /* End of if (ECUM_DEF_BEHAVIOUR_ENABLED == STD_OFF) */
    {
      #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
      LddCoreId = GetCoreID();
      if (LddCoreId == EcuM_GaaCoreID[ECUM_ZERO])
      #endif
      {
        if ((EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
             == ECUM_STATE_OFF) ||
            (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
             == ECUM_STATE_RESET))
        {
          /* Enable data protection */
          SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION();

          /* Update Next recent shutdown Target state */
          EcuM_GstLastShutdown.ddNextRecentTarget =
                       EcuM_GstLastShutdown.ddMostRecentTarget;

          /* Update Last/Most Recent shutdown Target state */
          EcuM_GstLastShutdown.ddMostRecentTarget =
                       EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget;
          EcuM_GstLastShutdown.ddNextRecentShutDownCause =
                       EcuM_GstLastShutdown.ddMostRecentShutDownCause;
          EcuM_GstLastShutdown.ddMostRecentShutDownCause =
                       EcuM_GstShutdownCauseTarget.ddShutdownCause;
          /* Update Next recent reset mode id */
          EcuM_GstLastShutdown.ucNextRecentRstModeId =
                       EcuM_GstLastShutdown.ucMostRecentRstModeId;
          /* Update Last/Most Recent reset mode id */
          EcuM_GstLastShutdown.ucMostRecentRstModeId =
                                  EcuM_GstShutdownCauseTarget.ucResetMode;

          /* Disable data protection */
          SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION();
          /* call to allow the system designer to notify that the GO OFF I state
          * is about to be entered. */
          EcuM_OnGoOffOne();

          #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
          (void)GetSpinlock(EcuM_GucSpinlock);
          /* Set a shutdown flag to be read by slave core */
          EcuM_GucShutdownMask = EcuM_GucSlaveCoreMask;
          (void)ReleaseSpinlock(EcuM_GucSpinlock);
          #endif
          #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
          EcuM_ClearAlarm();
          #endif
          /* Deinitializes the BSW Mode Manager */
          BswM_Deinit();
          /* Deinitializes the schedule Manager */
          SchM_Deinit();

          if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
                                                              == ECUM_STATE_OFF)
          {
            /* Check for any Pending Wakeup Events, if present update the
             *   shutdownTarget as ECUM_STATE_RESET */
            if ((EcuM_GddPendingWakeupEvents != ECUM_NO_EVENTS) &&
                (EcuM_GpEcuMConfigPtr != NULL_PTR))
            {
              /* polyspace +2 RTE:NIV [Justified:Medium] "AUTOEVER_RTE_NIV" */
              (void)EcuM_SelectShutdownTarget(ECUM_STATE_RESET,
              EcuM_GpEcuMConfigPtr->ucEcuMDefaultResetMode);
            }
          }
          #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
          /* Wait for all slaves to complete their shutdown */
          EcuM_OsWaitEvent();
          #endif

          #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
          /* Call Shutdown for all cores if slave core has signalled ready */
          /* polyspace:begin<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > EcuM_GucShutdownMask can be changeble by other core */
          /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "EcuM_GucShutdownMask can be changeble by other core" */
          /* polyspace +3 MISRA-C3:2.1 [Justified:Medium] "Reachable code by configuration change" */
          /* polyspace +2 MISRA2012:14.3 [Not a defect:Low] "Variable is changed by other core" */
          if (EcuM_GucShutdownMask == (uint8)ECUM_ZERO)
          {
            ShutdownAllCores((StatusType)E_OK);
          }
          /* polyspace:end<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > EcuM_GucShutdownMask can be changeble by other core */
          /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "EcuM_GucShutdownMask can be changeble by other core" */
          else
          {
            #if (ECUM_DEV_ERROR_DETECT == STD_ON)
            /* Report to DET */
            (void)EcuM_DetReportError(ECUM_GODOWN_SID, ECUM_E_SHUTDOWN_FAILED);
            LddStdRetVal = (Std_ReturnType)E_NOT_OK;
            #endif
            /* If there is no response from the slave core, call ShutdownOS. */
            ShutdownOS((StatusType)E_OK);
          }
          #else
          ShutdownOS((StatusType)E_OK);
          #endif
        } /* End of if ((EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
         * == ECUM_STATE_OFF) ||
         *(EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
         * == ECUM_STATE_RESET)) */
      } /* End of if (LddCoreId == EcuM_GaaCoreID[ECUM_ZERO])*/
    } /* End of if (LblCallerFlag != ECUM_TRUE) */
  } /* End of if (ECUM_UNINITIALIZED == EcuM_GblInitStatus) */

  return LddStdRetVal;
} /* End of EcuM_GoDown */


/*******************************************************************************
** Function Name        : EcuM_Shutdown                                       **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service will carry out GO OFF II Activities    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GucSelectShutdownTarget,   **
**                        EcuM_GucResetMode                                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, EcuM_OnGoOffTwo,               **
**                        EcuM_AL_SwitchOff, EcuM_AL_Reset, EcuM_IsMasterCore **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_Shutdown(void)
{
  boolean isMasterCore;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SHUTDOWN_SID, ECUM_E_UNINIT);
  }
  /* Module is initialized */
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    isMasterCore = EcuM_IsMasterCore();

    /* Indicate entry of shutdown state */
    EcuM_OnGoOffTwo();

    /* polyspace:begin<DEFECT : USELESS_IF : Not a defect : Justify with annotations > Value of isMasterCore depends on User-Configuration */
    /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Value of isMasterCore depends on User-Configuration" */
    /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "AUTOEVER_MISRA_14_3" */
    if (isMasterCore == TRUE)
    {
      /* Is the shutdown target RESET */
      if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
                                                            == ECUM_STATE_RESET)
      {
        /* The shutdown target RESET is implemented by EcuM_AL_Reset callout */
        EcuM_AL_Reset(EcuM_GstShutdownCauseTarget.ucResetMode);
      }
      /* shutdown target OFF*/
      else if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
                                                            == ECUM_STATE_OFF)
      {
       /* The shutdown target OFF is implemented by EcuM_AL_Switchoff callout*/
        EcuM_AL_SwitchOff();
      }
      else
      {
        #if (ECUM_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)EcuM_DetReportError(ECUM_SHUTDOWN_SID, ECUM_E_INVALID_SHUTDOWNTARGET);
        #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */

        /* Force Sw Reset */
        EcuM_AL_Reset((uint8) ECUM_INVALID_SHUTDOWN);
      }
    }
    /* polyspace:end<DEFECT : USELESS_IF : Not a defect : Justify with annotations > Value of isMasterCore depends on User-Configuration */
    /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Value of isMasterCore depends on User-Configuration" */
  }
} /* End of EcuM_Shutdown */

/*******************************************************************************
** Function Name        : EcuM_SelectShutdownTarget                           **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This service stores the value for later use in the  **
**                      : shutdown state.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : shutdownTarget, shutdownMode                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GucSelectShutdownTarget    **
**                        EcuM_GstLastShutdown, EcuM_GddShutdownCause         **
**                        EcuM_GucSleepMode, EcuM_GucResetMode                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError,                                **
**                        SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION,         **
**                        SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION,          **
**                        EcuM_SearchMode                                     **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectShutdownTarget
  (EcuM_StateType shutdownTarget, uint8 shutdownMode)
{
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Status flag to check if the search was successful */
  boolean Lblstatus;
  uint8 LucIndex;
  #endif

  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;
  /* Set the Return Value to E_OK */
  LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNTARGET_SID, ECUM_E_UNINIT);

    /* Update Return Value */
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  /* Module is initialized */
  else
  #endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)

    /* Is the shutdownTarget other than SLEEP/RESET/OFF */
    if ((shutdownTarget != ECUM_STATE_SLEEP) &&
        (shutdownTarget != ECUM_STATE_RESET) &&
        (shutdownTarget != ECUM_STATE_OFF))
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNTARGET_SID,
        ECUM_E_STATE_PAR_OUT_OF_RANGE);

      /* Update Return Value */
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
    {
      /* Enable data protection */
      SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION();

      /* Update EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
       * with shutdownTarget */
      EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget = shutdownTarget;

      /* Disable data protection */
      SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION();

      if (shutdownTarget == ECUM_STATE_SLEEP)
      {
        #if (ECUM_DEV_ERROR_DETECT == STD_ON)
        Lblstatus = EcuM_SearchMode(&LucIndex, shutdownMode);

        /* Is 'shutdownMode' invalid */
        if (Lblstatus == ECUM_FALSE)
        {
          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNTARGET_SID,
            ECUM_E_INVALID_PAR);
          /* Set LddStdRetVal to E_NOT_OK */
          LddStdRetVal = (Std_ReturnType)E_NOT_OK;
        } /* End of if (Lblstatus == ECUM_FALSE) */
        else
        #endif
        {
          /* Enable data protection */
          SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION();

          /* Update the SLEEP / RESET shutdownMode */
          EcuM_GstShutdownCauseTarget.ucSleepMode = shutdownMode;

          /* Disable data protection */
          SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION();
        } /* End of if (LddStdRetVal != (Std_ReturnType)E_NOT_OK) */
      } /* End of if (shutdownTarget == ECUM_STATE_SLEEP) */
      else if (shutdownTarget == ECUM_STATE_RESET)
      {
        /* Report to DET */
        #if (ECUM_DEV_ERROR_DETECT == STD_ON)
        Lblstatus = EcuM_SearchMode(&LucIndex, shutdownMode);

        /* Is 'shutdownMode' invalid */
        if (Lblstatus == ECUM_FALSE)
        {

          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNTARGET_SID,
            ECUM_E_INVALID_PAR);
          /* Set LddStdRetVal to E_NOT_OK */
          LddStdRetVal = (Std_ReturnType)E_NOT_OK;
        } /* End of if (Lblstatus == ECUM_FALSE) */
        else
        #endif
        {
          /* Enable data protection */
          SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION();

          /* Update the SLEEP / RESET shutdownMode */
          EcuM_GstShutdownCauseTarget.ucResetMode = shutdownMode;

          /* Disable data protection */
          SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION();
        } /* End of if (LddStdRetVal != (Std_ReturnType)E_NOT_OK) */
      } /* End of if (shutdownTarget == ECUM_STATE_RESET) */
      else
      {
        /* To avoid MISRA warning */
      }
    }
  }
  /* Return E_OK or E_NOT_OK */
  return LddStdRetVal;
} /* End of EcuM_SelectShutdownTarget */

/*******************************************************************************
** Function Name        : EcuM_GetShutdownTarget                              **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This function returns always the selected shutdown  **
**                      : target as set by EcuM_SelectShutdownTarget          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : shutdownTarget, shutdownMode                        **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GucSelectShutdownTarget, EcuM_GblInitStatus,   **
**                        EcuM_GucSleepMode, EcuM_GucResetMode                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetShutdownTarget
  (P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
   P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA) shutdownMode)
{
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;
  /* Initialize LddStdRetVal to E_OK */
  LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /*Report to DET */
    (void)EcuM_DetReportError(ECUM_GETSHUTDOWNTARGET_SID, ECUM_E_UNINIT);

    /* Update Return Value */
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)

    /* Is shutdownTarget null pointer */
    if (shutdownTarget == NULL_PTR)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETSHUTDOWNTARGET_SID,
        ECUM_E_NULL_POINTER);

      /* Update Return Value */
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    /* Is return value E_OK */
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    {
     /* Update the shutdownTarget */
     *shutdownTarget = EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget;

      /* Is the selected shutdown shutdownTarget SLEEP */
      if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
                                                            == ECUM_STATE_SLEEP)
      {
        /* Is shutdownMode null pointer */
        #if (ECUM_DEV_ERROR_DETECT == STD_ON)

        if (shutdownMode == NULL_PTR)
        {
          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_GETSHUTDOWNTARGET_SID,
            ECUM_E_NULL_POINTER);

          /* Update Return Value */
          LddStdRetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
        {
          /* Update with current shutdownMode index */
          *shutdownMode = EcuM_GstShutdownCauseTarget.ucSleepMode;
        }
      } /* End of if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
         * == ECUM_STATE_SLEEP) */
      else if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
                                                            == ECUM_STATE_RESET)
      {
        #if (ECUM_DEV_ERROR_DETECT == STD_ON)

        /* Is shutdownMode null pointer */
        if (shutdownMode == NULL_PTR)
        {
          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_GETSHUTDOWNTARGET_SID,
            ECUM_E_NULL_POINTER);

          /* Update Return Value */
          LddStdRetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
        {
          /* Update with current shutdownMode index */
          *shutdownMode = EcuM_GstShutdownCauseTarget.ucResetMode;
        }
      } /* End of if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
         * == ECUM_STATE_RESET) */
      else
      {
        /* As per coding guidelines */
      }
    }
  }
  /* Return LddStdRetVal */
  return LddStdRetVal;
} /* End of EcuM_GetShutdownTarget */

/*******************************************************************************
** Function Name        : EcuM_GetLastShutdownTarget                          **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This routine is intended for primary use in STARTUP **
**                      : or RUN state. The return value describes the ECU    **
**                      : state from which the last wakeup or power up        **
**                      : occurred. This function shall return always the same**
**                      : value until the next shutdown                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : shutdownTarget, shutdownMode                        **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GstLastShutdown, EcuM_GblInitStatus            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetLastShutdownTarget
  (P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
   P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA) shutdownMode)
{
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;
  /* Initialize LddStdRetVal to E_OK */
  LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /*Report to DET */
    (void)EcuM_DetReportError(ECUM_GETLASTSHUTDOWNTARGET_SID, ECUM_E_UNINIT);

    /* Update Return Value */
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)

    /* Is shutdownTarget null pointer */
    if (shutdownTarget == NULL_PTR)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETLASTSHUTDOWNTARGET_SID,
        ECUM_E_NULL_POINTER);

      /* Update Return Value */
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    /* Is return value E_OK */
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    {
      /* Update the shutdownTarget with last shutdown shutdownTarget */
      *shutdownTarget = EcuM_GstLastShutdown.ddMostRecentTarget;

      /* Is shutdown shutdownTarget SLEEP */
      if (EcuM_GstLastShutdown.ddMostRecentTarget == ECUM_STATE_SLEEP)
      {
        #if (ECUM_DEV_ERROR_DETECT == STD_ON)

        /* Is shutdownMode null pointer */
        if (shutdownMode == NULL_PTR)
        {
          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_GETLASTSHUTDOWNTARGET_SID,
            ECUM_E_NULL_POINTER);

          /* Update Return Value */
          LddStdRetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
        {
          /* Update with last shutdownMode index */
          *shutdownMode = EcuM_GstLastShutdown.ucMostRecentSlpModeId;
        }
      } /* End of if (EcuM_GstLastShutdown.ddMostRecentTarget ==
       * ECUM_STATE_SLEEP) */
      else if (EcuM_GstLastShutdown.ddMostRecentTarget == ECUM_STATE_RESET)
      {
        #if (ECUM_DEV_ERROR_DETECT == STD_ON)

        /* Is shutdownMode null pointer */
        if (shutdownMode == NULL_PTR)
        {
          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_GETLASTSHUTDOWNTARGET_SID,
            ECUM_E_NULL_POINTER);

          /* Update Return Value */
          LddStdRetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
        {
          /* Update with last shutdownMode index */
          *shutdownMode = EcuM_GstLastShutdown.ucMostRecentRstModeId;
        }
      } /* End of if (EcuM_GstLastShutdown.ddMostRecentTarget ==
         * ECUM_STATE_RESET) */
      else
      {
        /* To avoid MISRA warning */
      }
    }
  }
  /* Return LddStdRetVal */
  return LddStdRetVal;
} /* End of EcuM_GetLastShutdownTarget */

/*******************************************************************************
** Function Name        : EcuM_SelectShutdownCause                            **
**                                                                            **
** Service ID           : 0x1b                                                **
**                                                                            **
** Description          : This routine is intended for primary use in STARTUP **
**                      : or RUN state. The return value describes the ECU    **
**                      : state from which the last wakeup or power up        **
**                      : occurred. This function shall return always the same**
**                      : value until the next shutdown                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : shutdownCause                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GddShutdownCause, EcuM_GblInitStatus           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, EcuM_SearchShutdownCause,      **
**                        SchM_Enter_EcuM_SHUTDOWN_CAUSE,                     **
**                        SchM_Exit_EcuM_SHUTDOWN_CAUSE                       **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectShutdownCause
  (EcuM_ShutdownCauseType shutdownCause)
{
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  boolean Lblstatus;
  uint8 LucIndex;
  #endif

  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;
  /* Initialize LddStdRetVal to E_OK */
  LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /*Report to DET */
    (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNCAUSE_SID, ECUM_E_UNINIT);

    /* Update Return Value */
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)
    Lblstatus = EcuM_SearchShutdownCause(&LucIndex, shutdownCause);

    if (Lblstatus == ECUM_FALSE)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNCAUSE_SID,
        ECUM_E_INVALID_PAR);
      /* Set LddStdRetVal to E_NOT_OK */
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    } /* End of if (Lblstatus == ECUM_FALSE) */
    else
    #endif
    {
     /* Enable data protection */
      SchM_Enter_EcuM_SHUTDOWN_CAUSE();
      /* Update the shutdown cause */
      EcuM_GstShutdownCauseTarget.ddShutdownCause = shutdownCause;
      /* Disable data protection  */
      SchM_Exit_EcuM_SHUTDOWN_CAUSE();
    }
  }
  return LddStdRetVal;
} /* End of EcuM_SelectShutdownCause */

/*******************************************************************************
** Function Name        : EcuM_GetShutdownCause                               **
**                                                                            **
** Service ID           : 0x1c                                                **
**                                                                            **
** Description          : This routine is intended for primary use in STARTUP **
**                      : or RUN state. The return value describes the ECU    **
**                      : state from which the last wakeup or power up        **
**                      : occurred. This function shall return always the same**
**                      : value until the next shutdown                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : shutdownCause                                       **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GddShutdownCause, EcuM_GblInitStatus           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetShutdownCause
  (P2VAR(EcuM_ShutdownCauseType, AUTOMATIC, ECUM_APPL_DATA) shutdownCause)
{
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;
  /* Initialize LddStdRetVal to E_OK */
  LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /*Report to DET */
    (void)EcuM_DetReportError(ECUM_GETSHUTDOWNCAUSE_SID, ECUM_E_UNINIT);

    /* Update Return Value */
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)

    /* Is shutdownCause null pointer */
    if (shutdownCause == NULL_PTR)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETSHUTDOWNCAUSE_SID, ECUM_E_NULL_POINTER);

      /* Update Return Value */
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    {
     /* Update the current shutdown cause */
      *shutdownCause = EcuM_GstShutdownCauseTarget.ddShutdownCause;
    }
  }
  return LddStdRetVal;
} /* End of EcuM_GetShutdownCause */

/*******************************************************************************
** Function Name        : EcuM_GetMostRecentShutdown                          **
**                                                                            **
** Service ID           : 0x1d                                                **
**                                                                            **
** Description          : This routine is intended for primary use in STARTUP **
**                      : or RUN state. The return value describes the ECU    **
**                      : state from which the last wakeup or power up        **
**                      : occurred. This function shall return always the same**
**                      : value until the next shutdown                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : shutdownTarget, shutdownMode, shutdownCause,        **
**                        shutdownTime                                        **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GstLastShutdown, EcuM_GblInitStatus            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/

FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetMostRecentShutdown
  (P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
   P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA) shutdownMode,
   P2VAR(EcuM_ShutdownCauseType, AUTOMATIC, ECUM_APPL_DATA) shutdownCause,
   P2VAR(uint32, AUTOMATIC, ECUM_APPL_DATA) shutdownTime)
{
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;
  /* Initialize LddStdRetVal to E_OK */
  LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /*Report to DET */
    (void)EcuM_DetReportError(ECUM_GETMOSTRECENTSHUTDOWN_SID, ECUM_E_UNINIT);

    /* Update Return Value */
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)

    if ((shutdownTarget == NULL_PTR) || (shutdownMode == NULL_PTR) ||
        (shutdownCause == NULL_PTR) || (shutdownTime == NULL_PTR))
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETMOSTRECENTSHUTDOWN_SID,
        ECUM_E_NULL_POINTER);

      /* Update Return Value */
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    {
      /* Update the most recent shutdownTarget */
      *shutdownTarget = EcuM_GstLastShutdown.ddMostRecentTarget;

      if (EcuM_GstLastShutdown.ddMostRecentTarget == ECUM_STATE_SLEEP)
      {
      /* Update the most recent sleep shutdownMode id */
        *shutdownMode = EcuM_GstLastShutdown.ucMostRecentSlpModeId;
      }
      else if (EcuM_GstLastShutdown.ddMostRecentTarget == ECUM_STATE_RESET)
      {
      /* Update the most recent reset shutdownMode id */
        *shutdownMode = EcuM_GstLastShutdown.ucMostRecentRstModeId;
      }
      else
      {
        /* To avoid QAC warning */
      }
      /* Update the nost recent shutdown cause */
      *shutdownCause = EcuM_GstLastShutdown.ddMostRecentShutDownCause;
      /* As per a bug, if not supported by hardware, return 0 */
      *shutdownTime = (uint32)ECUM_ZERO;
    }
  }
  return LddStdRetVal;
} /* End of EcuM_GetMostRecentShutdown */

/*******************************************************************************
** Function Name        : EcuM_GetNextRecentShutdown                          **
**                                                                            **
** Service ID           : 0x1e                                                **
**                                                                            **
** Description          : This routine is intended for primary use in STARTUP **
**                      : or RUN state. The return value describes the ECU    **
**                      : state from which the last wakeup or power up        **
**                      : occurred. This function shall return always the same**
**                      : value until the next shutdown                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : shutdownTarget, shutdownMode, shutdownCause,        **
**                        shutdownTime                                        **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GstLastShutdown, EcuM_GblInitStatus            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetNextRecentShutdown
  (P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
   P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA) shutdownMode,
   P2VAR(EcuM_ShutdownCauseType, AUTOMATIC, ECUM_APPL_DATA) shutdownCause,
   P2VAR(uint32, AUTOMATIC, ECUM_APPL_DATA) shutdownTime)
{
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;
  /* Initialize LddStdRetVal to E_OK */
  LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /*Report to DET */
    (void)EcuM_DetReportError(ECUM_GETNEXTRECENTSHUTDOWN_SID, ECUM_E_UNINIT);
    /* Update Return Value */
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)

    if ((shutdownTarget == NULL_PTR) || (shutdownMode == NULL_PTR) ||
        (shutdownCause == NULL_PTR) || (shutdownTime == NULL_PTR))
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETNEXTRECENTSHUTDOWN_SID,
        ECUM_E_NULL_POINTER);

      /* Update Return Value */
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    {
      /* Update the next recent shutdown shutdownTarget */
      *shutdownTarget = EcuM_GstLastShutdown.ddNextRecentTarget;

      if (EcuM_GstLastShutdown.ddNextRecentTarget == ECUM_STATE_SLEEP)
      {
      /* Update the next recent sleep shutdownMode id */
        *shutdownMode = EcuM_GstLastShutdown.ucNextRecentSlpModeId;
      }
      else if (EcuM_GstLastShutdown.ddNextRecentTarget == ECUM_STATE_RESET)
      {
      /* Update the next recent reset shutdownMode id */
        *shutdownMode = EcuM_GstLastShutdown.ucNextRecentRstModeId;
      }
      else
      {
        /* To avoid MISRA warning */
      }
      /* Update the next recent shutdown cause */
      *shutdownCause = EcuM_GstLastShutdown.ddNextRecentShutDownCause;

      /* As per a bug, if not supported by hardware, return 0 */
      *shutdownTime = (uint32)ECUM_ZERO;
    }
  }
  return LddStdRetVal;
} /* End of EcuM_GetNextRecentShutdown */

/*******************************************************************************
** Function Name        : EcuM_GetPendingWakeupEvents                         **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : This routine is responsible for returning the       **
**                        wakeup events, which have been set but not yet      **
**                        validated                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : EcuM_GddPendingWakeupEvents                         **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GddPendingWakeupEvents     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
FUNC(EcuM_WakeupSourceType, ECUM_CODE) EcuM_GetPendingWakeupEvents(void)
{
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)

  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETPENDINGWAKEUPEVENTS_SID, ECUM_E_UNINIT);
  }
  #endif

  /* Return pending wakeup events */
  return (EcuM_GddPendingWakeupEvents);
} /* End of EcuM_GetPendingWakeupEvents */

/*******************************************************************************
** Function Name        : EcuM_ClearWakeupEvent                               **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : This routine is responsible for clearing all wake up**
**                        events like pending, validated and expired events.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : wakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GddValidatedWakeupEvents,  **
**                        EcuM_GddPendingWakeupEvents, EcuM_GaaWakeupStatus,  **
**                        EcuM_GddExpiredWakeupEvents, EcuM_GaaWakeupCounter  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_ClearWakeupEvent(EcuM_WakeupSourceType wakeupSource)
{
  /* Variable used as index for wakeupSource structure array */
  uint8 LucIndex;
  EcuM_WakeupSourceType LddWkSrcMask;
  boolean LblSearchResult;

  LddWkSrcMask = wakeupSource;
  LblSearchResult = ECUM_FALSE;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_CLEARWAKEUPEVENT_SID, ECUM_E_UNINIT);
  }/* Module is initialized */
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* To enable data protection */
    SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

    /* clear validated event */
    EcuM_GddValidatedWakeupEvents &= (EcuM_WakeupSourceType)(~wakeupSource);

    /* clear pending event */
    EcuM_GddPendingWakeupEvents &= (EcuM_WakeupSourceType)(~wakeupSource);

    /* clear Expired event */
    EcuM_GddExpiredWakeupEvents &= (EcuM_WakeupSourceType)(~wakeupSource);

    LucIndex = ECUM_ZERO;

    while(LucIndex < EcuM_GucNoOfWakeupSources)
    {
      if ((wakeupSource & EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId) ==
      EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId)
      {
        /* Clear Counter */
        /* polyspace<RTE: OBAI : Not a defect : No Action Planned > LucIndex has been checked */
        /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations> LucIndex has been checked */
        EcuM_GaaWakeupCounter[LucIndex] = (uint16)ECUM_ZERO;

        /* Updating Status as None */
        /* polyspace<RTE: OBAI : Not a defect : No Action Planned > LucIndex has been checked */
        /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations> LucIndex has been checked */
        EcuM_GaaWakeupStatus[LucIndex] = ECUM_WKSTATUS_NONE;

        if(LblSearchResult == ECUM_FALSE)
        {
          LblSearchResult = ECUM_TRUE;
        }

        LddWkSrcMask &= (~(EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId));

      }

      LucIndex++;

      if(LddWkSrcMask == ECUM_ZERO)
      {
        LucIndex = EcuM_GucNoOfWakeupSources;
      }
    }

    #if (ECUM_DEV_ERROR_DETECT == STD_ON)
    if(LblSearchResult == ECUM_FALSE)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_CLEARWAKEUPEVENT_SID,
        ECUM_E_UNKNOWN_WAKEUP_SOURCE);
    }
    #endif

    /* To disable data protection */
    SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

    /* Indicate current status of Wakeup source */
    BswM_EcuM_CurrentWakeup(wakeupSource, ECUM_WKSTATUS_NONE);
  }
} /* End of EcuM_ClearWakeupEvent */

/*******************************************************************************
** Function Name        : EcuM_GetValidatedWakeupEvents                       **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : This routine is responsible for returning all the   **
**                        wakeup events that have passed the validation.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : EcuM_GddValidatedWakeupEvents                       **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GddValidatedWakeupEvents   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
FUNC(EcuM_WakeupSourceType, ECUM_CODE) EcuM_GetValidatedWakeupEvents(void)
{
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)

  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETVALIDATEDWAKEUPEVENTS_SID, ECUM_E_UNINIT);
  }
  #endif

  /* Return validated wakeup events */
  return (EcuM_GddValidatedWakeupEvents);
} /* End of EcuM_GetValidatedWakeupEvents */

/*******************************************************************************
** Function Name        : EcuM_GetExpiredWakeupEvents                         **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : This routine is responsible for returning all the   **
**                        wakeup events that have been set but failed the     **
**                        validation. Events that do not need validation must **
**                        never be reported by this function.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : EcuM_GddExpiredWakeupEvents                         **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GddExpiredWakeupEvents     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
FUNC(EcuM_WakeupSourceType, ECUM_CODE) EcuM_GetExpiredWakeupEvents(void)
{
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)

  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETEXPIREDWAKEUPEVENTS_SID, ECUM_E_UNINIT);
  }
  #endif

  /* Return expired wakeup events */
  return (EcuM_GddExpiredWakeupEvents);
} /* End of EcuM_GetExpiredWakeupEvents */

/*******************************************************************************
** Function Name      : EcuM_SelectBootTarget                                 **
**                                                                            **
** Service ID         : 0x12                                                  **
**                                                                            **
** Description        : EcuM_SelectBootTarget selects a boot target.          **
**                      EcuM_SelectBootTarget is part of the ECU Manager      **
**                      Module port interface.                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Reentrant                                             **
**                                                                            **
** Input Parameters   : target                                                **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType (E_OK or E_NOT_OK)                     **
**                                                                            **
** Preconditions      : The ECU state manager must be initialized.            **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      EcuM_GblInitStatus, EcuM_GddBootTarget                **
**                                                                            **
**                    : Function(s) invoked:                                  **
**                      EcuM_DetReportError,                                  **
**                      SchM_Enter_EcuM_BOOT_TARGET_PROTECTION,               **
**                      SchM_Exit_EcuM_BOOT_TARGET_PROTECTION                 **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectBootTarget
  (EcuM_BootTargetType target)
{
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;
  /* Initialize LddStdRetVal with E_OK */
  LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SELECTBOOTTARGET_SID, ECUM_E_UNINIT);

    /* Set LddStdRetVal to E_NOT_OK */
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  /* Module is initialized */
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)

    if ((target != ECUM_BOOT_TARGET_APP) &&
        (target != ECUM_BOOT_TARGET_OEM_BOOTLOADER) &&
        (target != ECUM_BOOT_TARGET_SYS_BOOTLOADER))
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SELECTBOOTTARGET_SID,
        ECUM_E_STATE_PAR_OUT_OF_RANGE);

      /* Set LddStdRetVal to E_NOT_OK */
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    {
      /* Enable data protection */
      SchM_Enter_EcuM_BOOT_TARGET_PROTECTION();

      /* Update the boot target */
      EcuM_GstShutdownCauseTarget.ddBootTarget = target;

      /* Disable data protection */
      SchM_Exit_EcuM_BOOT_TARGET_PROTECTION();
    }
  }
  /* Return E_OK or E_NOT_OK */
  return LddStdRetVal;
} /* End of EcuM_SelectBootTarget */

/*******************************************************************************
** Function Name      : EcuM_GetBootTarget                                    **
**                                                                            **
** Service ID         : 0x13                                                  **
**                                                                            **
** Description        : EcuM_GetBootTarget returns the current boot target.   **
**                      EcuM_GetBootTarget is part of the ECU Manager Module  **
**                      port interface.                                       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Reentrant                                             **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : target                                                **
**                                                                            **
** Return parameter   : Std_ReturnType (E_OK or E_NOT_OK)                     **
**                                                                            **
** Preconditions      : The ECU state manager must be initialized.            **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      EcuM_GddBootTarget, EcuM_GblInitStatus                **
**                                                                            **
**                    : Function(s) invoked:                                  **
**                      EcuM_DetReportError                                   **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetBootTarget
  (P2VAR(EcuM_BootTargetType, AUTOMATIC, ECUM_APPL_DATA) target)
{
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;
  /* Initialize LddStdRetVal with E_OK */
  LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETBOOTTARGET_SID, ECUM_E_UNINIT);

    /* Update return value */
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)

    /* Is target null pointer */
    if (target == NULL_PTR)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETBOOTTARGET_SID, ECUM_E_NULL_POINTER);

      /* Update return value */
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    {
      /* Update target with current boot target */
      *target = EcuM_GstShutdownCauseTarget.ddBootTarget;
    }
  }
  /* Return E_OK or E_NOT_OK */
  return LddStdRetVal;
} /* End of EcuM_GetBootTarget */

/*******************************************************************************
** Function Name        : EcuM_StartupTwo                                     **
**                                                                            **
** Service ID           : 0x1a                                                **
**                                                                            **
** Description          : In this state, the initialization of BSW modules    **
**                        which needs OS support is carried out               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GddState, EcuM_GpEcuMConfigPtr                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        GetCoreID, SchM_Init, BswM_Init,                    **
**                        BswM_EcuM_CurrentState                              **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_StartupTwo(void)
{
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  CoreIdType LddCoreId;
  /* Get the core id of currently running core */
  LddCoreId = GetCoreID();
  #endif

  /* SchM Initialization */
  #if (ECUM_SCHM_PRECOMPILE == STD_ON)
  #if ((RTE_AR_RELEASE_MAJOR_VERSION == 4)&&(RTE_AR_RELEASE_MINOR_VERSION >= 3))
  SchM_Init(NULL_PTR);
  #else
  SchM_Init();
  #endif
  #else

  SchM_Init((P2CONST(SchM_ConfigType, AUTOMATIC, ECUM_APPL_CONST))
      (EcuM_GpEcuMConfigPtr->pRtePostBuildVariantConfiguration));
  #endif

  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  if ((LddCoreId == EcuM_GaaCoreID[ECUM_ZERO]) && (EcuM_GpEcuMConfigPtr != NULL_PTR))
  #endif
  {
    /* BswM Initialization */
    /* polyspace +3 RTE:IDP [Justified:Medium] "AUTOEVER_RTE_IDP" */
    /* polyspace +2 RTE:NIP [Justified:Medium] "AUTOEVER_RTE_NIP" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Medium] "AUTOEVER_MISRA_18_1" */
    BswM_Init(EcuM_GpEcuMConfigPtr->pBswMConfig);
    EcuM_GddState = ECUM_STATE_STARTUP_TWO;

    /* Indicate state change to BswM */
    BswM_EcuM_CurrentState(EcuM_GddState);
  }
} /* End of EcuM_StartupTwo */

/*******************************************************************************
** Function Name        : EcuM_GoHalt                                         **
**                                                                            **
** Service ID           : 0x20                                                **
**                                                                            **
** Description          : Instructs the ECU State Manager module to go into a **
**                        sleep mode where the microcontroller is halted,     **
**                        depending on the selected shutdown target           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GstShutdownCauseTarget,    **
**                        EcuM_GstLastShutdown, EcuM_GusSleepModeId,          **
**                        EcuM_GaaSleepModes                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_IsMasterCore(), EcuM_DetReportError(),         **
**                        SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION(),       **
**                        SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION(),        **
**                        EcuM_SearchMode(), EcuM_GoSleepSeq(),               **
**                        EcuM_HaltSeq(), EcuM_WakeupRestartSeq()             **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoHalt(void)
{
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  boolean isMasterCore;
  #endif
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;
  uint8 LucSleepModeIndex;
  boolean LblSleepModeValid;

  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  isMasterCore = EcuM_IsMasterCore();
  #endif

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GOHALT_SID, ECUM_E_UNINIT);
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget != ECUM_STATE_SLEEP)
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GOHALT_SID, ECUM_E_INVALID_SHUTDOWNTARGET);
    #endif
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  else if (isMasterCore == FALSE)
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GOHALT_SID, ECUM_E_INVALID_API_CALL);
    #endif
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  #endif
  else
  {
    /* Enable data protection */
    SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION();

    /* Update Next recent shutdown Target state */
    EcuM_GstLastShutdown.ddNextRecentTarget =
      EcuM_GstLastShutdown.ddMostRecentTarget;

    /* Update Last/Most Recent shutdown Target state */
    EcuM_GstLastShutdown.ddMostRecentTarget =
      EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget;
    EcuM_GstLastShutdown.ddNextRecentShutDownCause =
      EcuM_GstLastShutdown.ddMostRecentShutDownCause;
    EcuM_GstLastShutdown.ddMostRecentShutDownCause =
      EcuM_GstShutdownCauseTarget.ddShutdownCause;

    /* Update Next recent sleep mode id */
    EcuM_GstLastShutdown.ucNextRecentSlpModeId =
      EcuM_GstLastShutdown.ucMostRecentSlpModeId;
    EcuM_GstLastShutdown.ucMostRecentSlpModeId =
      EcuM_GstShutdownCauseTarget.ucSleepMode;

    /* Disable data protection */
    SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION();

    /* To get the index of the structure array EcuM_GaaSleepModes for
     *   current sleep mode */
    LblSleepModeValid = EcuM_SearchMode(&LucSleepModeIndex,
                                       EcuM_GstShutdownCauseTarget.ucSleepMode);
    if (LblSleepModeValid == FALSE)
    {
      EcuM_GusSleepModeId = ECUM_INVALID_SLEEPMODEID;
      #if (ECUM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GOHALT_SID, ECUM_E_UNKNOWN_SLEEP_MODE);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    /* polyspace:begin<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Reachable code by configuration change */
    /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Reachable code by configuration change" */
    /* polyspace +2 MISRA-C3:2.1 [Justified:Medium] "Reachable code by configuration change" */
    /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "AUTOEVER_MISRA_14_3" */
    else if (EcuM_GaaSleepModes[LucSleepModeIndex].blSleepModeSuspnd == FALSE)
    {
      EcuM_GusSleepModeId = LucSleepModeIndex;
      /* Not Suspend in Go Halt */
      #if (ECUM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GOHALT_SID, ECUM_E_INVALID_API_CALL);
      #endif
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    /* polyspace:end<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Reachable code by configuration change */
    /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Reachable code by configuration change" */
    else
    {
      EcuM_GusSleepModeId = LucSleepModeIndex;
      LddStdRetVal = E_OK;
    }
  }

  if (LddStdRetVal == E_OK)
  {
    EcuM_GoSleepSeq(LucSleepModeIndex);

    LddStdRetVal = EcuM_HaltSeq(LucSleepModeIndex);

    EcuM_WakeupRestartSeq(LucSleepModeIndex);
  }

  /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL1~4 */
  return LddStdRetVal;
} /* End of EcuM_GoHalt */

/*******************************************************************************
** Function Name        : EcuM_GoPoll                                         **
**                                                                            **
** Service ID           : 0x21                                                **
**                                                                            **
** Description          : Instructs the ECU State Manager module to go into a **
**                        polling mode depending on the selected shutdown     **
**                        target                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GstShutdownCauseTarget,    **
**                        EcuM_GstLastShutdown, EcuM_GusSleepModeId,          **
**                        EcuM_GaaSleepModes, EcuM_GucSpinlock,               **
**                        EcuM_GucPollMask, EcuM_GucSlaveCoreMask             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_IsMasterCore(), EcuM_DetReportError(),         **
**                        SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION(),       **
**                        SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION(),        **
**                        EcuM_SearchMode(), EcuM_GoSleepSeq(),               **
**                        DisableAllInterrupts(), EcuM_SetMode(),             **
**                        EnableAllInterrupts(), GetSpinlock(),               **
**                        ReleaseSpinlock(), EcuM_OsWaitEvent(),              **
**                        EcuM_PollSeq(), EcuM_WakeupRestartSeq()             **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoPoll(void)
{
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  boolean isMasterCore;
  #endif
  uint8 LucSleepModeIndex;
  boolean LblSleepModeValid;

  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;
  LucSleepModeIndex = (uint8) ECUM_ZERO;
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  isMasterCore = EcuM_IsMasterCore();
  #endif

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GOPOLL_SID, ECUM_E_UNINIT);
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget != ECUM_STATE_SLEEP)
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GOPOLL_SID, ECUM_E_INVALID_SHUTDOWNTARGET);
    #endif
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  else if (isMasterCore == FALSE)
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GOPOLL_SID, ECUM_E_INVALID_API_CALL);
    #endif
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  #endif
  else
  {
    /* Enable data protection */
    SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION();

    /* Update Next recent shutdown Target state */
    EcuM_GstLastShutdown.ddNextRecentTarget =
      EcuM_GstLastShutdown.ddMostRecentTarget;

    /* Update Last/Most Recent shutdown Target state */
    EcuM_GstLastShutdown.ddMostRecentTarget =
      EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget;
    EcuM_GstLastShutdown.ddNextRecentShutDownCause =
      EcuM_GstLastShutdown.ddMostRecentShutDownCause;
    EcuM_GstLastShutdown.ddMostRecentShutDownCause =
      EcuM_GstShutdownCauseTarget.ddShutdownCause;

    /* Update Next recent sleep mode id */
    EcuM_GstLastShutdown.ucNextRecentSlpModeId =
      EcuM_GstLastShutdown.ucMostRecentSlpModeId;
    EcuM_GstLastShutdown.ucMostRecentSlpModeId =
      EcuM_GstShutdownCauseTarget.ucSleepMode;

    /* Disable data protection */
    SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION();

    /* To get the index of the structure array EcuM_GaaSleepModes for
     *   current sleep mode */
    LblSleepModeValid = EcuM_SearchMode(&LucSleepModeIndex,
                                       EcuM_GstShutdownCauseTarget.ucSleepMode);
    if (LblSleepModeValid == FALSE)
    {
      EcuM_GusSleepModeId = ECUM_INVALID_SLEEPMODEID;
      #if (ECUM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GOPOLL_SID, ECUM_E_UNKNOWN_SLEEP_MODE);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    /* polyspace:begin<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Reachable code by configuration change */
    /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Reachable code by configuration change" */
    /* polyspace-begin MISRA-C3:2.1 [Justified:Medium] "Reachable code by configuration change" */
    /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "AUTOEVER_MISRA_14_3" */
    else if (EcuM_GaaSleepModes[LucSleepModeIndex].blSleepModeSuspnd == TRUE)
    {
      EcuM_GusSleepModeId = LucSleepModeIndex;
      /* Suspend in Go Poll */
      #if (ECUM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GOPOLL_SID, ECUM_E_INVALID_API_CALL);
      #endif
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    /* polyspace-end MISRA-C3:2.1 */
    /* polyspace:end<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Reachable code by configuration change */
    /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Reachable code by configuration change" */
    else
    {
      EcuM_GusSleepModeId = LucSleepModeIndex;
      LddStdRetVal = E_OK;
    }
  }

  /* polyspace:begin<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Reachable code by configuration change */
  /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Reachable code by configuration change" */
  /* polyspace +2 MISRA-C3:2.1 [Justified:Medium] "Reachable code by configuration change" */
  /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "AUTOEVER_MISRA_14_3" */
  if (LddStdRetVal == E_OK)
  {
    EcuM_GoSleepSeq(LucSleepModeIndex);

    /* Disable all interrupts */
    DisableAllInterrupts();
    /* Set MCU mode */
    EcuM_SetMode(EcuM_GaaSleepModes[LucSleepModeIndex].ddMcuSleepModeType);
    /* Enable all interrupts */
    EnableAllInterrupts();

    #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
    (void)GetSpinlock(EcuM_GucSpinlock);
    /* Set a shutdown flag to be read by slave core */
    EcuM_GucPollMask = EcuM_GucSlaveCoreMask;
    (void)ReleaseSpinlock(EcuM_GucSpinlock);
    /* Wait for all slaves to complete their sleep sequence */
    EcuM_OsWaitEvent();

    if (EcuM_GucPollMask != (uint8)ECUM_ZERO)
    {
      #if (ECUM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GOPOLL_SID, ECUM_E_SHUTDOWN_FAILED);
      #endif
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif
    {
      /* Master Poll Sequence */
      EcuM_PollSeq();
    }

    EcuM_WakeupRestartSeq(LucSleepModeIndex);
  }
  /* polyspace:end<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Reachable code by configuration change */
  /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Reachable code by configuration change" */

  return LddStdRetVal;
} /* End of EcuM_GoPoll */

/*******************************************************************************
** Function Name        : EcuM_MainFunction                                   **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : This Service is to implement all activities of ECU  **
**                        State manager while the OS is up and running.       **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Reentrancy           : None                                                **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GddPendingWakeupEvents,    **
**                        EcuM_GddExpiredWakeupEvents, EcuM_GddState,         **
**                        EcuM_GaaWakeupCounter, EcuM_GaaWakeupStatus,        **
**                        EcuM_GaaWakeSource                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, GetCoreID,                     **
**                        EcuM_StartWakeupSources, BswM_EcuM_CurrentWakeup,   **
**                        EcuM_ValidationProtocol, SchM_Deinit,               **
**                        EcuM_OsSetEvent                                     **
**                                                                            **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_MainFunction(void)
{
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  CoreIdType LddCoreId;
  #endif

  /* Local variable for index */
  uint8 LucWakeUpIndex;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)

  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_MAINFUNCTION_SID, ECUM_E_UNINIT);
  }
  else
  #endif
  {
    #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
    /* Get the core id of currently running core  */
    LddCoreId = GetCoreID();

    if (LddCoreId == EcuM_GaaCoreID[ECUM_ZERO])
    #endif
    {
      /* Processing Pending wakeups in all states. if any pending events */
      if (EcuM_GddPendingWakeupEvents != ECUM_NO_EVENTS)
      {
        EcuM_StartWakeupSources(EcuM_GddPendingWakeupEvents);

        /* To process timeout of all active wakeup sources */
        for (LucWakeUpIndex = (uint8)ECUM_ZERO; LucWakeUpIndex <
             EcuM_GucNoOfWakeupSources; LucWakeUpIndex++)
        {
          /* Is wakeup event pending */
          if (EcuM_GaaWakeupStatus[LucWakeUpIndex] == ECUM_WKSTATUS_PENDING)
          {
            /* To enable data protection */
        	SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

        	/* If Expired */
            if (EcuM_GaaWakeupCounter[LucWakeUpIndex] == (uint16)ECUM_ZERO)
            {
              /* Update Status as Expired */
              EcuM_GaaWakeupStatus[LucWakeUpIndex] = ECUM_WKSTATUS_EXPIRED;

              /* Clear corresponding Pending wakeup event */
              EcuM_GddPendingWakeupEvents &=
                (EcuM_WakeupSourceType)
                (~EcuM_GaaWakeSource[LucWakeUpIndex].ddWakeupSourceId);

              /* Update corresponding Expired wakeup event */
              EcuM_GddExpiredWakeupEvents |=
              (EcuM_GaaWakeSource[LucWakeUpIndex].ddWakeupSourceId);

              /* To disable data protection */
              SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

              /* Indicate current status of Wakeup source */
              BswM_EcuM_CurrentWakeup(
                EcuM_GaaWakeSource[LucWakeUpIndex].ddWakeupSourceId,
                ECUM_WKSTATUS_EXPIRED);
              /*  Invoke callout to stop the given wakeup source after
               *  unsuccessful wakeup validation */
              EcuM_StopWakeupSources
                (EcuM_GaaWakeSource[LucWakeUpIndex].ddWakeupSourceId);
            } /* End of if (EcuM_GaaWakeupCounter[LucWakeUpIndex] ==
               * ECUM_ZERO) */
            else
            {
              EcuM_ValidationProtocol();

              /* Update validation timeout counter */
              EcuM_GaaWakeupCounter[LucWakeUpIndex]--;

              /* To disable data protection */
              SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();
            }
          } /* End of if (EcuM_GaaWakeupStatus[LucWakeUpIndex] ==
             * ECUM_WKSTATUS_PENDING) */
        }
      } /* End of if (EcuM_GddPendingWakeupEvents != ECUM_NO_EVENTS) */
    }
    #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
    else
    {
      (void)EcuM_SlaveShutDownOrSleep(LddCoreId);
    }
    #endif
  }
} /* End of EcuM_MainFunction */

/*******************************************************************************
** Function Name        : EcuM_SetRelWakeupAlarm                              **
**                                                                            **
** Service ID           : 0x22                                                **
**                                                                            **
** Description          : This Service sets a user's wakeup alarm relative    **
**                        to the current point in times.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user, wakeupTime                                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_NOT_OK or LddStdRetVal)           **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GulMasterAlarm,            **
**                        EcuM_GaaAlarmTime, EcuM_GulRunningTimer             **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError,                                **
**                        SchM_Enter_EcuM_ALARM_TIME_PROTECTION,              **
**                        SchM_Exit_EcuM_ALARM_TIME_PROTECTION,               **
**                        EcuM_SearchAlarmClockUser                           **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_SetRelWakeupAlarm(EcuM_UserType user,
  uint32 wakeupTime)
{
  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  /* Variable to store the array index where the user is present */
  uint8 LucAlarmUserInd;
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  boolean LblSearchResult;
  #endif
  #endif

  /* Local variable for return value */
  Std_ReturnType LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)

  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SETRELWAKEUPALARM_SID, ECUM_E_UNINIT);
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_OFF)
    /* To search index of a wakeup source */
    (void)EcuM_SearchAlarmClockUser(&LucAlarmUserInd, user);
    #else
    /* To search index of a wakeup source */
    LblSearchResult = EcuM_SearchAlarmClockUser(&LucAlarmUserInd, user);

    /* Is reported wakeup event unknown */
    if (LblSearchResult == ECUM_FALSE)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SETRELWAKEUPALARM_SID, ECUM_E_INVALID_PAR);
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_OFF) */
    {
      SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
      if (EcuM_GulMasterAlarm == (uint32)ECUM_ZERO)
      {
        EcuM_GaaAlarmTime[LucAlarmUserInd] = EcuM_GulRunningTimer + wakeupTime;
        EcuM_GulMasterAlarm = EcuM_GaaAlarmTime[LucAlarmUserInd];
        EcuM_GblAlarmCycle = ECUM_TRUE;
      }
      else if ((EcuM_GulRunningTimer + wakeupTime) < EcuM_GulMasterAlarm)
      {
        /* If the relative time from now is earlier than the current wakeup time,
         * shall update the wakeup time */
        EcuM_GaaAlarmTime[LucAlarmUserInd] = EcuM_GulRunningTimer + wakeupTime;
        EcuM_GulMasterAlarm = EcuM_GaaAlarmTime[LucAlarmUserInd];
        EcuM_GblAlarmCycle = ECUM_TRUE;
      }
      else
      {
        /* If the relative time from now is later than the current wakeup time,
         * shall not update the wakeup time and shall return E_EARLIER_ACTIVE */
        LddStdRetVal = (Std_ReturnType)ECUM_E_EARLIER_ACTIVE;
      }
      SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
    }
  }
  #else /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)

  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_SETRELWAKEUPALARM_SID,
    ECUM_E_SERVICE_DISABLED);
  LddStdRetVal = (Std_ReturnType)E_NOT_OK;

  ECUM_UNUSED(user);
  ECUM_UNUSED(wakeupTime);
  #endif /* #if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  #endif /* #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

  return LddStdRetVal;
} /* End of EcuM_SetRelWakeupAlarm */

/*******************************************************************************
** Function Name        : EcuM_SetAbsWakeupAlarm                              **
**                                                                            **
** Service ID           : 0x23                                                **
**                                                                            **
** Description          : EcuM_SetAbsWakeupAlarm sets the user's wakeup alarm **
**                        to an absolute point in time.                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user, wakeupTime                                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_NOT_OK or LddStdRetVal)           **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GulMasterAlarm,            **
**                        EcuM_GaaAlarmTime, EcuM_GulRunningTimer             **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError,                                **
**                        SchM_Enter_EcuM_ALARM_TIME_PROTECTION,              **
**                        SchM_Exit_EcuM_ALARM_TIME_PROTECTION,               **
**                        EcuM_SearchAlarmClockUser                           **
*******************************************************************************/

FUNC(Std_ReturnType, ECUM_CODE) EcuM_SetAbsWakeupAlarm(EcuM_UserType user,
  uint32 wakeupTime)
{
  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  /*
   * Local variable for return value
   * Variable to store the array index where the user is present
   */
  uint8 LucAlarmUserInd;
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  boolean LblSearchResult;
  #endif
  #endif

  /* Initialize LddStdRetVal with E_OK */
  Std_ReturnType LddStdRetVal = (Std_ReturnType)E_OK;


  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)

  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SETABSWAKEUPALARM_SID, ECUM_E_UNINIT);
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_OFF)
    (void)EcuM_SearchAlarmClockUser(&LucAlarmUserInd, user);
    #else
    LblSearchResult = EcuM_SearchAlarmClockUser(&LucAlarmUserInd, user);

    /* Is reported wakeup event unknown */
    if (LblSearchResult == ECUM_FALSE)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SETABSWAKEUPALARM_SID, ECUM_E_INVALID_PAR);
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_OFF) */
    {
      SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
      if (EcuM_GulMasterAlarm == (uint32)ECUM_ZERO)
      {
        EcuM_GaaAlarmTime[LucAlarmUserInd] = wakeupTime;
        EcuM_GulMasterAlarm = EcuM_GaaAlarmTime[LucAlarmUserInd];
        EcuM_GblAlarmCycle = ECUM_TRUE;
      }
      else if (wakeupTime <= EcuM_GulRunningTimer)
      {
        /* If the time is earlier than now ,shall not update the
         * wakeup time and shall return E_PAST */
        LddStdRetVal = (Std_ReturnType)ECUM_E_PAST;
      }
      else if (wakeupTime < EcuM_GulMasterAlarm)
      {
        /* If the time earlier than the current wakeup time ,
         * update the wakeup time */
        EcuM_GaaAlarmTime[LucAlarmUserInd] = wakeupTime;
        EcuM_GulMasterAlarm = EcuM_GaaAlarmTime[LucAlarmUserInd];
        EcuM_GblAlarmCycle = ECUM_TRUE;
      }
      else
      {
        /* If the time is later than the current wakeup time, shall not
         * update the wakeup time and shall return E_EARLIER_ACTIVE */
        LddStdRetVal = (Std_ReturnType)ECUM_E_EARLIER_ACTIVE;
      }
      SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
    }
  }
  #else /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  (void)EcuM_DetReportError(ECUM_SETABSWAKEUPALARM_SID,
    ECUM_E_SERVICE_DISABLED);
  LddStdRetVal = (Std_ReturnType)E_NOT_OK;

  ECUM_UNUSED(user);
  ECUM_UNUSED(wakeupTime);
  #endif /* #if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  #endif /* #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

  return LddStdRetVal;
} /* End of EcuM_SetAbsWakeupAlarm */

/*******************************************************************************
** Function Name        : EcuM_AbortWakeupAlarm                               **
**                                                                            **
** Service ID           : 0x24                                                **
**                                                                            **
** Description          : EcuM_AbortWakeupAlarm aborts the wakeup alarm       **
**                        previously set by this user.                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_NOT_OK or LddStdRetVal)           **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GulMasterAlarm,            **
**                        EcuM_GaaAlarmTime                                   **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError,                                **
**                        EcuM_SearchAlarmClockUser,                          **
**                        SchM_Enter_EcuM_ALARM_TIME_PROTECTION,              **
**                        SchM_Exit_EcuM_ALARM_TIME_PROTECTION                **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_AbortWakeupAlarm(EcuM_UserType user)
{
  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  /* Index to loop the number of alarms configured */
  uint8 LucAlarmIndx;
  /* Variable to store the array index where the user is present */
  uint8 LucAlarmUserInd;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  boolean LblSearchResult;
  #endif
  #endif

  /* Local variable for return value */
  Std_ReturnType LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_ABORTWAKEUPALARM_SID, ECUM_E_UNINIT);
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_OFF)
    (void)EcuM_SearchAlarmClockUser(&LucAlarmUserInd, user);
    #else
    /* To search index of a wakeup source */
    LblSearchResult = EcuM_SearchAlarmClockUser(&LucAlarmUserInd, user);

    /* Is reported wakeup event unknown */
    if (LblSearchResult == ECUM_FALSE)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_ABORTWAKEUPALARM_SID, ECUM_E_INVALID_PAR);
      LddStdRetVal = (Std_ReturnType)ECUM_E_NOT_ACTIVE;
    }
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_OFF) */
    {
      if (EcuM_GulMasterAlarm == EcuM_GaaAlarmTime[LucAlarmUserInd])
      {
        LucAlarmIndx = (uint8)ECUM_ZERO;

        /* Enter data protection  */
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        /* Set the master alarm to max value to get the minimum alarm */
        EcuM_GulMasterAlarm = ECUM_NO_ACTIVE_ALARM;
        /* Clear the validation timeout of corresponding user */
        EcuM_GaaAlarmTime[LucAlarmUserInd] = (uint32)ECUM_ZERO;
        /* Disable data protection */
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();

        while (LucAlarmIndx < EcuM_GucNoOfAlarms)
        {
          if (LucAlarmIndx != LucAlarmUserInd)
          {
            if ((EcuM_GaaAlarmTime[LucAlarmIndx] != (uint32)ECUM_ZERO) &&
                (EcuM_GaaAlarmTime[LucAlarmIndx] < EcuM_GulMasterAlarm))
            {
              /* Enter data protection  */
              SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
              /* Update the master alarm */
              EcuM_GulMasterAlarm = EcuM_GaaAlarmTime[LucAlarmIndx];
              /* Disable data protection */
              SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
            }
          }
          LucAlarmIndx++;
        }
      } /* End of if (EcuM_GulMasterAlarm == EcuM_GaaAlarmTime
         * [LucAlarmUserInd]) */

      if (EcuM_GulMasterAlarm == ECUM_NO_ACTIVE_ALARM)
      {
        /* Enter data protection  */
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        /* Clear the master alarm */
        EcuM_GulMasterAlarm = (uint32)ECUM_ZERO;
        /* Disable data protection */
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
      }
    }
  }
  #else /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  (void)EcuM_DetReportError(ECUM_ABORTWAKEUPALARM_SID, ECUM_E_SERVICE_DISABLED);
  LddStdRetVal = (Std_ReturnType)E_NOT_OK;

  ECUM_UNUSED(user);
  #endif /* #if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  #endif /* #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

  return LddStdRetVal;
} /* End of EcuM_AbortWakeupAlarm */


/*******************************************************************************
** Function Name        : EcuM_GetCurrentTime                                 **
**                                                                            **
** Service ID           : 0x25                                                **
**                                                                            **
** Description          : EcuM_GetCurrentTime returns the current value of    **
**                        the EcuM clock                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : *currentTime                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_NOT_OK or LddStdRetVal)           **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GulRunningTimer            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Not a defect:Low] "Configuration dependent" */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetCurrentTime
  (P2VAR(uint32, AUTOMATIC, ECUM_APPL_DATA) currentTime)
{
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETCURRENTTIME_SID, ECUM_E_UNINIT);
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)

    if (currentTime == NULL_PTR)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETCURRENTTIME_SID, ECUM_E_NULL_POINTER);
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif
    {
      /* Update the current running clock time */
      *currentTime = EcuM_GulRunningTimer;
    }
  }
  #else /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_GETCURRENTTIME_SID, ECUM_E_SERVICE_DISABLED);
  LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  #endif /* #if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  ECUM_UNUSED_PTR(currentTime);
  #endif /* #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

  return LddStdRetVal;
} /* End of EcuM_GetCurrentTime */


/*******************************************************************************
** Function Name        : EcuM_GetWakeupTime                                  **
**                                                                            **
** Service ID           : 0x26                                                **
**                                                                            **
** Description          : EcuM_GetWakeupTime returns the current value of the **
**                        master alarm clock (the minimum absolute time of    **
**                        all user alarm clocks).                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : wakeupTime                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_NOT_OK or LddStdRetVal)           **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GulMasterAlarm             **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Not a defect:Low] "Configuration dependent" */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetWakeupTime
  (P2VAR(uint32, AUTOMATIC, ECUM_APPL_DATA) wakeupTime)
{
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETWAKEUPTIME_SID, ECUM_E_UNINIT);
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)

    if (wakeupTime == NULL_PTR)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETWAKEUPTIME_SID, ECUM_E_NULL_POINTER);
      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif
    {
      if (EcuM_GulMasterAlarm != (uint32)ECUM_ZERO)
      {
        /* Update the alarm which is set */
        *wakeupTime = EcuM_GulMasterAlarm;
      }
      else
      {
        /* No alarm is active or set */
        *wakeupTime = ECUM_NO_ACTIVE_ALARM;
      }
    }
  }
  #else /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_GETWAKEUPTIME_SID, ECUM_E_SERVICE_DISABLED);
  LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  #endif /* #if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  ECUM_UNUSED_PTR(wakeupTime);
  #endif /* #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

  return LddStdRetVal;
} /* End of EcuM_GetWakeupTime */


/*******************************************************************************
** Function Name        : EcuM_SetClock                                       **
**                                                                            **
** Service ID           : 0x27                                                **
**                                                                            **
** Description          : EcuM_SetClock sets the EcuM clock time to the       **
**                        provided value. This API is useful for testing the  **
**                        alarm services; Alarms that take days to expire     **
**                        can be tested.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user, setTime                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_NOT_OK or LddStdRetVal)           **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblInitStatus, EcuM_GaaSetClockAllowedUser     **
**                        EcuM_GulRunningTimer                                **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/

FUNC(Std_ReturnType, ECUM_CODE) EcuM_SetClock(EcuM_UserType user,
  uint32 setTime)
{
  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  uint8 LucIndex;
  boolean LblSetClockUserFlag;
  #endif
  #endif

  /* Local variable for return value */
  Std_ReturnType LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  LblSetClockUserFlag = ECUM_FALSE;
  LucIndex = (uint8)ECUM_ZERO;

  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SETCLOCK_SID, ECUM_E_UNINIT);
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_OFF)
    ECUM_UNUSED(user);
    #else
    while (LucIndex < EcuM_GucNoOfClockUsers)
    {
      if (user == EcuM_GaaSetClockAllowedUser[LucIndex])
      {
        LblSetClockUserFlag = ECUM_TRUE;
        LucIndex = EcuM_GucNoOfClockUsers;
      }
      LucIndex++;
    }

    if (LblSetClockUserFlag != ECUM_TRUE)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SETCLOCK_SID, ECUM_E_INVALID_PAR);
      LddStdRetVal = (Std_ReturnType)ECUM_E_NOT_ALLOWED;
    }
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_OFF) */
    {
      /* Enable data protection */
      SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
      /* Update the running timer  */
      EcuM_GulRunningTimer = setTime;
      /* Disable data protection  */
      SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
    }
  }
  #else /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

  /* Initialize LddStdRetVal with E_OK */
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_SETCLOCK_SID, ECUM_E_SERVICE_DISABLED);
  LddStdRetVal = (Std_ReturnType)E_NOT_OK;

  ECUM_UNUSED(user);
  ECUM_UNUSED(setTime);
  #endif /* #if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  #endif /* #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

  return LddStdRetVal;
} /* End of EcuM_SetClock */


/*******************************************************************************
** Function Name        : EcuM_GetResetReason                                 **
**                                                                            **
** Service ID           : 0x28                                                **
**                                                                            **
** Description          : EcuM_GetResetReason returns the current value of    **
**                        the EcuM ResetReason                                **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : *resetReason                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GddResetReason, EcuM_GblInitStatus             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/

FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetResetReason
  (P2VAR(Mcu_ResetType, AUTOMATIC, ECUM_APPL_DATA) resetReason)
{
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal = E_NOT_OK;

  if(resetReason != NULL_PTR)
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)
    /* Is module not initialized */
    if (ECUM_UNINITIALIZED == EcuM_GblInitStatus)
    {

      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETRESETREASON_SID, ECUM_E_UNINIT);


      LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    #endif

    {
      *resetReason = EcuM_GddResetReason;

      LddStdRetVal = (Std_ReturnType)E_OK;
    }

  }

  return LddStdRetVal;
}  /* End of EcuM_GetResetReason */


/*******************************************************************************
** Function Name        : EcuM_RequestRUN                                     **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : Places a request for the RUN state. Requests can be **
**                        placed by every user made known to the state        **
**                        manager at configuration time.                      **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GucRunRequestStatus                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, BswM_RequestMode               **
*******************************************************************************/

FUNC(Std_ReturnType, ECUM_CODE) EcuM_RequestRUN(EcuM_UserType user)
{
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  CoreIdType LddCoreId;
  #endif
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal = E_NOT_OK;
  if(EcuM_GucRunRequestStatus != ECUM_RUN_RELEASED)
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_REQUESTRUN_SID, ECUM_E_MULTIPLE_RUN_REQUESTS);
    #endif

    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
    LddCoreId = GetCoreID();

    if (LddCoreId == EcuM_GaaCoreID[ECUM_ZERO])
    #endif
    {
      SchM_Enter_EcuM_STATE_PROTECTION();

      EcuM_GucRunRequestStatus = ECUM_RUN_REQUESTED;

      SchM_Exit_EcuM_STATE_PROTECTION();

      BswM_RequestMode((BswM_UserType)ECUM_STATEREQ_ID, ECUM_REQUEST_RUN);

      LddStdRetVal = (Std_ReturnType)E_OK;
    }
  }
  ECUM_UNUSED(user);

  return LddStdRetVal;
}


/*******************************************************************************
** Function Name        : EcuM_ReleaseRUN                                     **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : Releases a RUN request previously done with a call  **
**                        to EcuM_RequestRUN. The service is intended for     **
**                        implementing AUTOSAR ports.                         **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GucRunRequestStatus,                           **
**                        EcuM_GstShutdownCauseTarget                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, BswM_RequestMode               **
*******************************************************************************/

FUNC(Std_ReturnType, ECUM_CODE) EcuM_ReleaseRUN(EcuM_UserType user)
{
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  CoreIdType LddCoreId;
  #endif
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal = E_NOT_OK;

  SchM_Enter_EcuM_STATE_PROTECTION();

  if(EcuM_GucRunRequestStatus == ECUM_RUN_RUNNING)
  {
    #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
    LddCoreId = GetCoreID();
    if (LddCoreId == EcuM_GaaCoreID[ECUM_ZERO])
    #endif
    {
      EcuM_GucRunRequestStatus = ECUM_RUN_RELEASED;

      SchM_Exit_EcuM_STATE_PROTECTION();

      /* Is the shutdown target RESET */
      if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
          == ECUM_STATE_RESET)
      {
        BswM_RequestMode((BswM_UserType)ECUM_STATEREQ_ID, ECUM_REQUEST_RESET);

        LddStdRetVal = (Std_ReturnType)E_OK;
      }
      else if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
          == ECUM_STATE_OFF)
      {
        BswM_RequestMode((BswM_UserType)ECUM_STATEREQ_ID, ECUM_REQUEST_OFF);

        LddStdRetVal = (Std_ReturnType)E_OK;
      }
      else if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget
          == ECUM_STATE_SLEEP)
      {
        BswM_RequestMode((BswM_UserType)ECUM_STATEREQ_ID, ECUM_REQUEST_SLEEP);

        LddStdRetVal = (Std_ReturnType)E_OK;
      }
      else
      {
        LddStdRetVal = (Std_ReturnType)E_NOT_OK;
      }

    }
    #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
    else
    {
      SchM_Exit_EcuM_STATE_PROTECTION();
    }
    #endif
  }
  else
  {
    SchM_Exit_EcuM_STATE_PROTECTION();

    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  ECUM_UNUSED(user);

  return LddStdRetVal;
}

/*******************************************************************************
** Function Name        : EcuM_IsMasterCore                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Returns whether the current core is Master or not   **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : TRUE - Master Core, FALSE - Slave Core              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GaaCoreID                                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        GetCoreID()                                         **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_IsMasterCore(void)
{
  boolean isMasterCore;
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  CoreIdType coreId;

  coreId = GetCoreID();

  /* Array for Core ID
   * Master Core : EcuM_GaaCoreID[0]
   * Slave Cores : EcuM_GaaCoreID[1] ~ */
  if (coreId == EcuM_GaaCoreID[0])
  {
    isMasterCore = TRUE;
  }
  else
  {
    isMasterCore = FALSE;
  }
  #else
  isMasterCore = TRUE;
  #endif

  return isMasterCore;
}
#define ECUM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end RTE:UNR */
/* polyspace-end MISRA-C3:D4.14 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
