/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : EcuM_Internal.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Internal Functionality implementation of EcuM                 **
**              EcuM_SearchMode                                               **
**              EcuM_SearchShutdownCause                                      **
**              EcuM_SearchWakeupSource                                       **
**              EcuM_SearchGoDownUser                                         **
**              EcuM_SearchAlarmClockUser                                     **
**              EcuM_ValidationProtocol                                       **
**              EcuM_OsWaitEvent                                              **
**              EcuM_OsSetEvent                                               **
**              EcuM_GoSleepSeq                                               **
**              EcuM_ClearAlarm                                               **
**              EcuM_WakeupRestartSeq                                         **
**              EcuM_CheckResetReason                                         **
**              EcuM_WakeUpReactSeq                                           **
**              EcuM_CheckSlaveSleep                                          **
**              EcuM_PollSeq                                                  **
**              EcuM_GetGptTicks                                              **
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
** 3.0.5      17-Aug-2021   Junho Cho     Redmine #31552                      **
** 3.0.4      06-Jan-2021   Manje Woo     Redmine #27140                      **
** 3.0.3      25-Nov-2020   Manje Woo     Redmine #18654                      **
** 3.0.0      28-Jun-2019   Manje Woo     Redmine #16766, #17850, #16271      **
** 2.7.3      16-May-2017   Sanghoon Bae  Redmine #8550 #8552                 **
** 2.7.2      23-Mar-2017   Sanghoon Bae  Redmine #7886 #7067                 **
** 2.6.0      04-Jul-2016   Sanghoon Bae  Redmine #5226                       **
** 2.5.5      04-Jul-2016   Sanghoon Bae  Redmine #5257                       **
** 2.5.3      12-Jan-2016   Daejun Park   Redmine #3856                       **
**                                        -Update precompile option           **
** 2.5.1      12-Oct-2015   Sanghoon Bae  Redmine #3035                       **
** 2.5.0      20-Aug-2015   Sanghoon Bae  Redmine #2571                       **
**                                        -Add function                       **
**                                         EcuM_SearchSleepModeWakeupSource   **
** 2.4.2      10-Jun-2015   Jihoon Jung   Redmine #2704                       **
**                                        - EcuM_SlaveShutDownOrSleep bug fix **
** 2.4.1      28-May-2015   Jihoon Jung   Redmine #2550                       **
** 2.3.2      27-Mar-2015   Daejun Park   Redmine #2376                       **
**                                        -Add ECUM_PM_ENABLED macro          **
** 2.2.1      26-Dec-2014   Daejun Park   Redmine #1879, #2094                **
**                                        -Update to AUTRON template          **
**                                        -EcuM_GetGptTicks bug fix           **
** 2.2.0      26-Nov-2014   Daejun Park   Modify alarm wakeup process         **
** 2.1.0      24-Sep-2014   Daejun Park   Redmine #1367                       **
** 2.0.4      12-Jun-2014   Daejun Park   Add feature MCU_NORMAL_MODE         **
** 2.0.0      24-Apr-2014   Daejun Park   Update major version                **
** 1.1.0      07-Mar-2014   Daejun Park   Remove binary search APIs           **
** 1.0.12     13-Dec-2013   Daejun Park   CR~208, XAR~779                     **
**                                        -Move pre-compile condition         **
**                                         to EcuM_Callout.c                  **
** 1.0.10     04-Jul-2013   Daejun Park   CR~129, XAR~581 : EcuM library      **
**                                        -Add new constant variable          **
**                                         EcuM_GulOsNumOfTasks to replace    **
**                                         macro in static code               **
**                                        -Change array variables in          **
**                                         EcuM_GaaOsTaskEventMask to pointer **
**                                         variables for library              **
** 1.0.9      11-Jun-2013   Daejun Park   CR~108, XAR~545 : Multicore support **
**                                        -Add inclusion of header file       **
**                                         Os_PortTypes.h                     **
** 1.0.8      07-Jun-2013   Daejun Park   CR~119, XAR~558 : EcuM library      **
**                                        -Add inclusion of header file       **
**                                         EcuM_Config.h                      **
**                                        -Convert macro to constant variables**
**                                         EcuM_GucNoOfSleepModes,            **
**                                         EcuM_GucNoOfResetModes,            **
**                                         EcuM_GucNoOfShutdownCause,         **
**                                         EcuM_GucNoOfWakeupSources,         **
**                                         EcuM_GucOsNumberOfCores,           **
**                                         EcuM_GucNoOfOsResources,           **
**                                         EcuM_GulMcuNormalMode              **
**                                        -Convert local variable             **
**                                         LaaSetEventInv to global variable  **
**                                         EcuM_GaaSetEventInv                **
** 1.0.0      04-Mar-2013   Daejun Park   Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin RTE:UNR [Justified:Medium] "AUTOEVER_RTE_UNR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "EcuM_Internal.h"
#include "EcuM_Config.h"
#include "EcuM_Ram.h"

#include "Rte_EcuM.h"
#include "SchM_EcuM.h"
#include "BswM_EcuM.h"
#include "Mcu.h"
#include "Os.h"
#include "Rte_Main.h"

#include "HwResource.h"
#if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
#include "Reg_Macros.h"
#include "Reg_eSys_Rtc.h"
#endif

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
#include "Os_PortTypes.h"
#endif

#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
#include "Gpt.h"
#endif

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if (ECUM_DEMERROR_REPORT == STD_ON)
#include "EcuM_Dem_Cfg.h"
#endif

/*******************************************************************************
**                        Global Data                                         **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define ECUM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : EcuM_SearchMode                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific mode**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : sleepResetMode                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpModeIdx                                           **
**                                                                            **
** Return parameter     : LblSearchResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_SearchMode
 (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpModeIdx, uint8 sleepResetMode)
{
  uint8 LucIndex;

  /* variable to break the FOR loop */
  boolean LblSearchResult;

  /* Set the search result flag to ECUM_FALSE */
  LblSearchResult = ECUM_FALSE;

  /* Check the mode by linear search */
  if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget == ECUM_STATE_SLEEP)
  {
    /* Set the initial value */
    *LpModeIdx = EcuM_GucNoOfSleepModes;

    for (LucIndex = (uint8)ECUM_ZERO; ((LucIndex < EcuM_GucNoOfSleepModes) &&
                              (LblSearchResult == ECUM_FALSE)); LucIndex++)
    {
      /* Is 'sleepResetMode' matches with the configured SleepMode */
      if (EcuM_GaaSleepModes[LucIndex].ucSleepModeId == sleepResetMode)
      {
        /* Set the search result flag to TRUE */
        LblSearchResult = ECUM_TRUE;

        /* Update index for Request Array Index */
        *LpModeIdx = LucIndex;
      }
    }
  }
  else if (EcuM_GstShutdownCauseTarget.ucSelectShutdownTarget == ECUM_STATE_RESET)
  {
    /* Set the initial value */
    *LpModeIdx = EcuM_GucNoOfResetModes;

    for (LucIndex = (uint8)ECUM_ZERO; ((LucIndex < EcuM_GucNoOfResetModes) &&
                              (LblSearchResult == ECUM_FALSE)); LucIndex++)
    {
      /* Is 'sleepResetMode' matches with the configured ResetMode */
      if (EcuM_GaaResetModeId[LucIndex] == sleepResetMode)
      {
        /* Set the search result flag to TRUE */
        LblSearchResult = ECUM_TRUE;

        /* Update index for Request Array Index */
        *LpModeIdx = LucIndex;
      }
    }
  }
  else
  {
    /* do nothing  */
  }

  /* Return ECUM_TRUE if found else ECUM_FALSE */
  return (LblSearchResult);
}/* End of function body */


/*******************************************************************************
** Function Name        : EcuM_SearchShutdownCause                            **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific     **
**                         ShutdownCause                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : target                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpCauseIdx                                          **
**                                                                            **
** Return parameter     : LblSearchResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_SearchShutdownCause
 (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpCauseIdx,
  EcuM_ShutdownCauseType target)
{
  uint8 LucIndex;

  /* variable to break the FOR loop */
  boolean LblSearchResult;

  /* Set the search result flag to ECUM_FALSE */
  LblSearchResult = ECUM_FALSE;

  /* Set the initial value */
  *LpCauseIdx = EcuM_GucNoOfShutdownCause;

  /* Check the ShutdownCause by linear search */
  for (LucIndex = (uint8)ECUM_ZERO; ((LucIndex < EcuM_GucNoOfShutdownCause) &&
                              (LblSearchResult == ECUM_FALSE)); LucIndex++)
  {
    /* Is 'ShutdownCause' matches with the configured ShutdownCause */
    if (EcuM_GaaShutdownCauseId[LucIndex] == target)
    {
      /* Set the search result flag to TRUE */
      LblSearchResult = ECUM_TRUE;

      /* Update index for Request Array Index */
      *LpCauseIdx = LucIndex;
    }
  }

  /* Return ECUM_TRUE if found else ECUM_FALSE */
  return (LblSearchResult);
} /* End of function body */

/*******************************************************************************
** Function Name        : EcuM_SearchWakeupSource                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific user**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : WakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpSourceIdx                                         **
**                                                                            **
** Return parameter     : LblSearchResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_SearchWakeupSource
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpSourceIdx,
  EcuM_WakeupSourceType wakeupSource)
{
  uint8 LucIndex;

  /* variable to break the FOR loop */
  boolean LblSearchResult;

  /* Set the search result flag to ECUM_FALSE */
  LblSearchResult = ECUM_FALSE;

  /* Set the initial value */
  *LpSourceIdx = EcuM_GucNoOfWakeupSources;

  /* Check the WakeupSource by linear search */
  for (LucIndex = (uint8)ECUM_ZERO; ((LucIndex < EcuM_GucNoOfWakeupSources) &&
                              (LblSearchResult == ECUM_FALSE)); LucIndex++)
  {
    /* Is 'wakeupSource' matches with the configured WakeupSource */
    if ((wakeupSource & EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId) ==
        EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId)
    {
      /* Set the search result flag to TRUE */
      LblSearchResult = ECUM_TRUE;

      /* Update index for Request Array Index */
      *LpSourceIdx = LucIndex;
    }
  }

  /* Return ECUM_TRUE if found else ECUM_FALSE */
  return (LblSearchResult);
} /* End of function body */


/*******************************************************************************
** Function Name        : EcuM_SearchGoDownUser                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific user**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpGoDownUserIdx                                     **
**                                                                            **
** Return parameter     : LblSearchResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_SearchGoDownUser
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpGoDownUserIdx, EcuM_UserType user)
{
  uint8 LucIndex;

  /* variable to break the FOR loop */
  boolean LblSearchResult;

  /* Set the search result flag to ECUM_FALSE */
  LblSearchResult = ECUM_FALSE;

  if(LpGoDownUserIdx != NULL_PTR)
  {
    /* Set the initial value */
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Medium] "Not from external sources" */
    *LpGoDownUserIdx = EcuM_GucNoOfGoDownUsers;

    /* Check the user by linear search */
    for (LucIndex = (uint8)ECUM_ZERO; ((LucIndex < EcuM_GucNoOfGoDownUsers) &&
                                (LblSearchResult == ECUM_FALSE)); LucIndex++)
    {
      /* Is 'user' matches with the configured users */
      if (EcuM_GaaGoDownAllowedUser[LucIndex] == user)
      {
        /* Set the search result flag to TRUE */
        LblSearchResult = ECUM_TRUE;

        /* Update index for Request Array Index */
        *LpGoDownUserIdx = LucIndex;
      }
    }
  }

  /* Return ECUM_TRUE if found else ECUM_FALSE */
  return (LblSearchResult);
}                                 /* End of function body */


/*******************************************************************************
** Function Name        : EcuM_SearchAlarmClockUser                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific user**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpAlarmUserIdx                                      **
**                                                                            **
** Return parameter     : LblSearchResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
FUNC(boolean, ECUM_CODE) EcuM_SearchAlarmClockUser
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpAlarmUserIdx, EcuM_UserType user)
{
  uint8 LucIndex;

  /* variable to break the FOR loop */
  boolean LblSearchResult;

  /* Set the search result flag to ECUM_FALSE */
  LblSearchResult = ECUM_FALSE;

  /* Set the initial value */
  *LpAlarmUserIdx = EcuM_GucNoOfAlarms;

  /* Check the user by linear search */
  for (LucIndex = (uint8)ECUM_ZERO; ((LucIndex < EcuM_GucNoOfAlarms) &&
                              (LblSearchResult == ECUM_FALSE)); LucIndex++)
  {
    /* Is 'user' matches with the configured users */
    if (EcuM_GaaAlarmClock[LucIndex].ddUser == user)
    {
      /* Set the search result flag to TRUE */
      LblSearchResult = ECUM_TRUE;

      /* Update index for Request Array Index */
      *LpAlarmUserIdx = LucIndex;
    }
  }

  /* Return ECUM_TRUE if found else ECUM_FALSE */
  return (LblSearchResult);
}                                 /* End of function body */

#endif /* (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

/*******************************************************************************
** Function Name        : EcuM_ValidationProtocol                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching a validated Wakeup Source             **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GddPendingWakeupEvents, EcuM_GddState          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_CheckValidation, BswM_EcuM_CurrentState        **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_ValidationProtocol(void)
{
  /* Local variable for wakeup sources */
  EcuM_WakeupSourceType LddWakeupSources;
  uint8 LucIndex;

  EcuM_GddState = ECUM_STATE_WAKEUP_VALIDATION;
  BswM_EcuM_CurrentState(EcuM_GddState);

  /* Loop FOR all configured wakeup sources */
  for (LucIndex = (uint8)ECUM_ZERO; LucIndex < EcuM_GucNoOfWakeupSources;
       LucIndex++)
  {
    LddWakeupSources = EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId;

    /* Is wakeup source pending */
    if (((EcuM_GddPendingWakeupEvents & LddWakeupSources) ==
         LddWakeupSources))
    {
      /* Invoke callout for wakeup validation */
      EcuM_CheckValidation(LddWakeupSources);
    }
  }
} /* End of EcuM_ValidationProtocol */


/*******************************************************************************
** Function Name        : EcuM_OsWaitEvent                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It is invoked by master core for all slave core     **
**                        for the synchronized shutdown.                      **
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
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GaaOsTask,                                     **
**                        EcuM_GucNoOfEventMasks, EcuM_GaaEventMask           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        GetTaskID(), WaitEvent(), GetEvent(), ClearEvent()  **
*******************************************************************************/
#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
FUNC(void, ECUM_CODE) EcuM_OsWaitEvent(void)
{
  volatile uint32 loopCount;
  #if ((ECUM_NO_OF_EVENT_MASKS > ECUM_ZERO) && (ECUM_NO_OF_OS_TASKS > ECUM_ZERO))
  /* Master/Slave Core Synchronization: AUTOSAR 4.4.0 example implementation */
  uint8 eventIdx;
  EventMaskType eventMask;
  EventMaskType waitEventMask;
  TaskType taskId;
  StatusType status;
  Std_ReturnType retVal;
  EcuM_StateType shutdownTarget;
  uint8 shutdownMode;

  eventMask = (EventMaskType)ECUM_ZERO;
  waitEventMask = (EventMaskType)ECUM_ZERO;

  retVal = EcuM_GetShutdownTarget(&shutdownTarget, &shutdownMode);
  status = GetTaskID(&taskId);

  if ((retVal == (Std_ReturnType)E_OK) &&
      (status == (StatusType)E_OK) &&
      (taskId == EcuM_GaaOsTask[ECUM_ZERO]))
  {
    /* Loop for number of events configured to get eventmask  */
    for (eventIdx = (uint8)ECUM_ZERO; eventIdx < EcuM_GucNoOfEventMasks;
         eventIdx++)
    {
      /* Get the event mask for the configured events
         by bitwise OR operation */
      waitEventMask |= EcuM_GaaEventMask[eventIdx];
    }

    loopCount = 0u;
    /* Wait until slave core ready */
    while (waitEventMask != (EventMaskType)ECUM_ZERO)
    {
      /* If OsResource not used, using WaitEvent and GetEvent loop */
      if ((shutdownTarget == ECUM_STATE_RESET) ||
          (shutdownTarget == ECUM_STATE_OFF))
      {
        status = WaitEvent(waitEventMask);
      }
      /* If OsResource used(ECUM_STATE_SLEEP), using GetEvent loop */
      if (status == (StatusType)E_OK)
      {
        status = GetEvent(taskId, &eventMask);
      }

      if (status != (StatusType)E_OK)
      {
        break;
      }
      else if (eventMask == 0u)
      {
        /* Continue loop */
      }
      else
      {
        (void)ClearEvent(eventMask);
        waitEventMask &= (~eventMask);
      } /* End of if (status == (StatusType)E_OK) */

      /* Failsafe for infinite loop */
      if (loopCount >= ECUM_LOOP_COUNT_MAX)
      {
        break;
      }
      loopCount++;
    } /* End of while (waitEventMask != (EventMaskType)ECUM_ZERO) */
  } /* End of if (retVal == (Std_ReturnType)E_OK && ...) */
  #else
  /* Master/Slave Core Synchronization: AUTOEVER specific implementation */
  loopCount = 0u;
  /* Wait until slave core ready */
  while ((EcuM_GucShutdownMask != 0u) ||
         (EcuM_GucHaltMask != 0u) ||
         (EcuM_GucPollMask != 0u))
  {
    /* Failsafe for infinite loop */
    if (loopCount >= ECUM_LOOP_COUNT_MAX)
    {
      break;
    }
    loopCount++;
  }
  #endif /* End of #if ((ECUM_NO_OF_EVENT_MASKS > ECUM_ZERO) && ... */
} /* End of EcuM_OsWaitEvent */

/*******************************************************************************
** Function Name        : EcuM_OsSetEvent                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It is invoked by slave core                         **
**                        for the synchronized shutdown.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : CoreId                                              **
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
**                        EcuM_GucNoOfCores, EcuM_GaaCoreID, EcuM_GucSpinlock,**
**                        EcuM_GucShutdownMask, EcuM_GucHaltMask,             **
**                        EcuM_GucPollMask, EcuM_GaaEventMask,                **
**                        EcuM_GaaOsTask                                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        GetSpinlock(), ReleaseSpinlock(), SetEvent()        **
*******************************************************************************/
static FUNC(void, ECUM_CODE) EcuM_OsSetEvent(CoreIdType LddCoreId)
{
  uint8 LucCoreIdx;
  #if ((ECUM_NO_OF_EVENT_MASKS > ECUM_ZERO) && (ECUM_NO_OF_OS_TASKS > ECUM_ZERO))
  uint8 LucEventIdx;
  #endif
  uint8 LucCoreMask;

  for (LucCoreIdx = (uint8)ECUM_ONE; LucCoreIdx < EcuM_GucNoOfCores;
       LucCoreIdx++)
  {
    if (LddCoreId == EcuM_GaaCoreID[LucCoreIdx])
    {
      LucCoreMask = ((uint8)ECUM_ONE << LddCoreId);

      (void)GetSpinlock(EcuM_GucSpinlock);

      EcuM_GucShutdownMask &= (~LucCoreMask);
      EcuM_GucHaltMask &= (~LucCoreMask);
      EcuM_GucPollMask &= (~LucCoreMask);

      (void)ReleaseSpinlock(EcuM_GucSpinlock);

      #if ((ECUM_NO_OF_EVENT_MASKS > ECUM_ZERO) && (ECUM_NO_OF_OS_TASKS > ECUM_ZERO))
      LucEventIdx = LucCoreIdx - (uint8)ECUM_ONE;

      /* Call Os API SetEvent to come out of wait state for each event mask */
      (void)SetEvent(EcuM_GaaOsTask[ECUM_ZERO], EcuM_GaaEventMask[LucEventIdx]);
      #endif

      break;
    }
  }
} /* End of EcuM_OsSetEvent */

#endif /* End of if (ECUM_MULTI_CORE_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : EcuM_GoSleepSeq                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : In the GoSleepseq the ECU Manager module configures **
**                        hardware for the upcoming sleep phase and sets the  **
**                        ECU up for the next wakeup event.                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucSleepModeIndex                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblGoSleepResult                                    **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GaaSleepModes, EcuM_GddState                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_IsMasterCore(), BswM_EcuM_CurrentWakeup(),     **
**                        SchM_Enter_EcuM_STATE_PROTECTION(),                 **
**                        SchM_Exit_EcuM_STATE_PROTECTION(),                  **
**                        BswM_EcuM_CurrentState(),                           **
**                        EcuM_EnableWakeupSources(), EcuM_GetOSResource()    **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_GoSleepSeq(uint8 LucSleepModeIndex)
{
  boolean isMasterCore;
  EcuM_WakeupSourceType wakeupSources;

  /* polyspace +2 RTE:OBAI [Justified:Medium] "Pointer not access out of array" */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "ptr points to a valid value and code is verified manually" */
  wakeupSources = EcuM_GaaSleepModes[LucSleepModeIndex].ddWakeupSourceMask;

  isMasterCore = EcuM_IsMasterCore();
  /* polyspace:begin<DEFECT : USELESS_IF : Not a defect : Justify with annotations > Value of isMasterCore depends on User-Configuration */
  /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Value of isMasterCore depends on User-Configuration" */
  /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "AUTOEVER_MISRA_14_3" */
  if (isMasterCore == TRUE)
  {
    BswM_EcuM_CurrentWakeup(wakeupSources, ECUM_WKSTATUS_NONE);
    /* Enable data protection  */
    SchM_Enter_EcuM_STATE_PROTECTION();
    /* Update the state to sleep */
    EcuM_GddState = ECUM_STATE_GO_SLEEP;
    /* Disable data protection */
    SchM_Exit_EcuM_STATE_PROTECTION();
    /* Indicate current sate to BswM */
    BswM_EcuM_CurrentState(EcuM_GddState);
  }
  /* polyspace:end<DEFECT : USELESS_IF : Not a defect : Justify with annotations > Value of isMasterCore depends on User-Configuration */
  /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Value of isMasterCore depends on User-Configuration" */

  #if (ECUM_PM_ENABLED == STD_OFF)
  /* Set the wakeup sources up for the next sleep mode */
  EcuM_EnableWakeupSources(wakeupSources);
  #endif

  /* Get OS Resource */
  /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL1 */
  /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "AUTOEVER_MISRA_2_2" */
  EcuM_GetOSResource();
} /* End of EcuM_GoSleepSeq */


/*******************************************************************************
** Function Name        : EcuM_ClearAlarm                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It is used to clearing the Alarms corresponding     **
**                        to Master Alarm.                                    **
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
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GaaAlarmTime, EcuM_GulMasterAlarm              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_EcuM_ALARM_TIME_PROTECTION,              **
**                        SchM_Exit_EcuM_ALARM_TIME_PROTECTION                **
*******************************************************************************/
#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
FUNC(void, ECUM_CODE) EcuM_ClearAlarm(void)
{
  uint8 LucAlarmIndx;
  /* Enable data protection */
  SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
  /* Clear the master alarm */
  EcuM_GulMasterAlarm = (uint32)ECUM_ZERO;
  /* Disable data protection  */
  SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
  LucAlarmIndx = (uint8)ECUM_ZERO;
  while (LucAlarmIndx < EcuM_GucNoOfAlarms)
  {
    /* Enable data protection  */
    SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
    /* Clear the validation timeout array */
    EcuM_GaaAlarmTime[LucAlarmIndx] = (uint32)ECUM_ZERO;
    /* Disable data protection */
    SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
    LucAlarmIndx++;
  }
}

#endif /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

/*******************************************************************************
** Function Name        : EcuM_WakeupRestartSeq                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It gives the Wakeup Restart sequence used by EcuM   **
**                        to make the EcuM Up for any wake up event.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : SleepIndex                                          **
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
**                        EcuM_GaaSleepModes, EcuM_GpEcuMConfigPtr,           **
**                        EcuM_GddState                                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_IsMasterCore(), BswM_EcuM_CurrentState(),      **
**                        EcuM_AL_DriverRestart(), BswM_EcuM_CurrentWakeup(), **
**                        EcuM_DisableWakeupSources(), EnableAllInterrupts(), **
**                        Mcu_SetMode(), DisableAllInterrupts(),              **
**                        EcuM_GetPendingWakeupEvents(),                      **
**                        SchM_Enter_EcuM_STATE_PROTECTION(),                 **
**                        SchM_Exit_EcuM_STATE_PROTECTION(),                  **
**                        EcuM_ClearWakeupEvent(), EcuM_ReleaseOSResource()   **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_WakeupRestartSeq(uint8 SleepIndex)
{
  #if (ECUM_PM_ENABLED == STD_OFF)
  EcuM_WakeupSourceType pendingWakeupEvents;
  #endif
  boolean isMasterCore;

  isMasterCore = EcuM_IsMasterCore();
  #if (ECUM_MCU_NORMAL_MODE_SUPPORT == STD_ON)
  /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "AUTOEVER_MISRA_14_3" */
  if (isMasterCore == TRUE)
  {
    /* Disable all interrupts */
    DisableAllInterrupts();

    /* Set MCU mode as NORMAL */
    Mcu_SetMode(EcuM_GulMcuNormalMode);

    /* Enable all interrupts */
    EnableAllInterrupts();
  }
  #endif

  #if (ECUM_PM_ENABLED == STD_OFF)
  pendingWakeupEvents = EcuM_GetPendingWakeupEvents();
  EcuM_DisableWakeupSources(pendingWakeupEvents);
  #endif

  /* polyspace:begin<DEFECT : USELESS_IF : Not a defect : Justify with annotations > Value of isMasterCore depends on User-Configuration */
  /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Value of isMasterCore depends on User-Configuration" */
  /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "AUTOEVER_MISRA_14_3" */
  if (isMasterCore == TRUE)
  {
    /* Redmine #1355 */
    BswM_EcuM_CurrentWakeup(EcuM_GaaSleepModes[SleepIndex].ddWakeupSourceMask,
                            ECUM_WKSTATUS_DISABLED);

    EcuM_AL_DriverRestart(EcuM_GpEcuMConfigPtr);

    /* Enable data protection */
    SchM_Enter_EcuM_STATE_PROTECTION();
    /* Update the current state to start up one */
    EcuM_GddState = ECUM_STATE_STARTUP_ONE;
    /* Disable the data protection */
    SchM_Exit_EcuM_STATE_PROTECTION();
    /* Indicate state change to BswM */
    BswM_EcuM_CurrentState(EcuM_GddState);
  }
  /* polyspace:end<DEFECT : USELESS_IF : Not a defect : Justify with annotations > Value of isMasterCore depends on User-Configuration */
  /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Value of isMasterCore depends on User-Configuration" */

  /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "AUTOEVER_MISRA_2_2" */
  EcuM_ReleaseOSResource();
} /* End of EcuM_WakeupRestartSeq(uint8 SleepIndex) */


/*******************************************************************************
** Function Name        : EcuM_CheckResetReason                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This service checks the reset reason.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : resetReason                                         **
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
**                        EcuM_GddPendingWakeupEvents, EcuM_GaaWakeSource,    **
**                        EcuM_GddValidatedWakeupEvents                       **
**                        Function(s) invoked    :                            **
**                                                                            **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_CheckResetReason(Mcu_ResetType resetReason)
{
  uint8 LucIndex;
  boolean LblWakeupSourceFlag;

  LblWakeupSourceFlag = ECUM_FALSE;

  /* Loop for wakeup source */
  for (LucIndex = (uint8)ECUM_ZERO; LucIndex < EcuM_GucNoOfWakeupSources;
       LucIndex++)
  {
    /* Map reset reason obtained from Mcu to wakeup source */
    /* polyspace +1 MISRA-C3:10.5 [Justified:Low] "AUTOEVER_MISRA_10_5" */
    if (EcuM_GaaWakeSource[LucIndex].ucResetReason
        == (uint8)resetReason)
    {
      LblWakeupSourceFlag = ECUM_TRUE;

      /* Is validation required for the wakeup source */
      if (EcuM_GaaWakeSource[LucIndex].usWakeupValidationTimeOut
          != (uint16)ECUM_ZERO)
      {
        /* Update EcuM_GddPendingWakeupEvents to remember the wakeup source
         *   resulting from the reset reason translation */
        EcuM_GddPendingWakeupEvents |=
          EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId;
      }
      else
      {
        /* Update EcuM_GddValidatedWakeupEvents to remember the wakeup source
         *   resulting from the reset reason translation */
        EcuM_GddValidatedWakeupEvents |=
          EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId;
      }
    } /* End of if ((Mcu_ResetType)EcuM_GaaWakeSource[LucIndex].ucResetReason ==
       *resetReason) */
  }

  if (LblWakeupSourceFlag != ECUM_TRUE)
  {
  /* Update EcuM_GddValidatedWakeupEvents to remember the wakeup source
   * resulting from the reset reason translation */
    EcuM_GddValidatedWakeupEvents |= ECUM_WKSOURCE_RESET;
  }
} /* End of EcuM_CheckResetReason */

/*******************************************************************************
** Function Name        : EcuM_HaltSeq                                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : The ECU Manager module shall execute the Halt       **
**                        Sequence in sleep modes that halt the               **
**                        microcontroller. In these sleep modes the ECU       **
**                        Manager module does not execute any code.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucSleepModeIndex                                   **
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
**                        EcuM_GucSpinlock, EcuM_GucHaltMask,                 **
**                        EcuM_GucSlaveCoreMask, EcuM_GblSleepCycle,          **
**                        EcuM_GblAlarmCycle, EcuM_GucGptChannelId,           **
**                        EcuM_GblAlarmExpired, EcuM_GulNextTick,             **
**                        EcuM_GddValidatedWakeupEvents,                      **
**                        EcuM_GddPendingWakeupEvents,                        **
**                        EcuM_GucRunRequestStatus, EcuM_GaaSleepModes,       **
**                        EcuM_GusERamCheckFailed, EcuM_GddWakeupType         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        GetSpinlock(), ReleaseSpinlock(), EcuM_OsWaitEvent()**
**                        EcuM_DetReportError(), Gpt_EnableWakeup(),          **
**                        SchM_Enter_EcuM_ALARM_TIME_PROTECTION(),            **
**                        SchM_Exit_EcuM_ALARM_TIME_PROTECTION(),             **
**                        EcuM_GetGptTicks(), Gpt_EnableNotification(),       **
**                        Gpt_StartTimer(), Gpt_SetMode(),                    **
**                        DisableAllInterrupts(), EnableAllInterrupts(),      **
**                        EcuM_GenerateRamHash(), EcuM_SetMode(),             **
**                        EcuM_EnableInterrupts(), EcuM_CheckRamHash(),       **
**                        EcuM_ErrorHook(), EcuM_ClearAlarm(), Gpt_StopTimer()**
**                        Gpt_DisableWakeup(), Gpt_DisableNotification()      **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_HaltSeq(uint8 LucSleepModeIndex)
{
  Std_ReturnType LddStdRetVal;
  uint8 LucRetVal;
  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  uint16 LusCounter;
  #endif

  LddStdRetVal = (Std_ReturnType)E_OK;

  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  (void)GetSpinlock(EcuM_GucSpinlock);
  /* Set a sleep flag to be read by slave core */
  EcuM_GucHaltMask = EcuM_GucSlaveCoreMask;
  (void)ReleaseSpinlock(EcuM_GucSpinlock);
  /* Wait for all slaves to complete their sleep sequence */
  EcuM_OsWaitEvent();

  /* polyspace:begin<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > EcuM_GucHaltMask can be changeble by other core */
  /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "EcuM_GucHaltMask can be changeble by other core" */
  /* polyspace-begin MISRA-C3:2.1 [Justified:Medium] "Reachable code by configuration change" */
  /* polyspace +2 MISRA2012:14.3 [Not a defect:Low] "Variable is changed by other core" */
  if (EcuM_GucHaltMask != (uint8)ECUM_ZERO)
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GOHALT_SID, ECUM_E_SHUTDOWN_FAILED);
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
    #endif
  }
  /* polyspace-end MISRA-C3:2.1 [Justified:Medium] "Reachable code by configuration change" */
  /* polyspace:end<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > EcuM_GucHaltMask can be changeble by other core */
  /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "EcuM_GucHaltMask can be changeble by other core" */
  else
  #endif
  {
    EcuM_GblSleepCycle = ECUM_TRUE;

    #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
    if (EcuM_GblAlarmCycle == ECUM_TRUE)
    {
      /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL2 */
      Gpt_EnableWakeup(EcuM_GucGptChannelId);
    }

    /* Enable data protection */
    SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
    EcuM_GblAlarmExpired = ECUM_FALSE;
    /* Disable data protection */
    SchM_Exit_EcuM_ALARM_TIME_PROTECTION();

    /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL3 */
    LusCounter = (uint16)ECUM_ZERO;
    while ((EcuM_GblAlarmExpired == ECUM_FALSE) &&
           (LusCounter < ECUM_ALRAM_LOOP_MAX))
    #endif
    {
      #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
      LusCounter++;
      SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
      /* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
      if (EcuM_GblAlarmCycle == ECUM_TRUE)
      {
        EcuM_GetGptTicks(&EcuM_GulNextTick);


        if (EcuM_GulNextTick > (uint32)ECUM_ZERO)
        {
          Gpt_EnableNotification(EcuM_GucGptChannelId);
          Gpt_StartTimer(EcuM_GucGptChannelId, EcuM_GulNextTick);
          Gpt_SetMode(GPT_MODE_SLEEP);
        }
        else
        {
          EcuM_GblAlarmExpired = ECUM_TRUE;
          EcuM_GblSleepCycle = ECUM_FALSE;
        }

        EcuM_GblAlarmCycle = ECUM_FALSE;
      }
      SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
      #endif

      /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL4 */
      DisableAllInterrupts();

      if ((EcuM_GblSleepCycle == ECUM_TRUE) &&
          ((EcuM_GddValidatedWakeupEvents == ECUM_NO_EVENTS) &&
           (EcuM_GddPendingWakeupEvents == ECUM_NO_EVENTS))
          && (EcuM_GucRunRequestStatus == ECUM_RUN_RELEASED))
      {
        /* Invoke before putting ECU to sleep */
        /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "AUTOEVER_MISRA_2_2" */
        EcuM_GenerateRamHash();

        /* Set Mcu mode */
        /* Set Breakpoint Here for MODE_TEST_ECUM_LOWPOWER_MANUAL1~4 */
        EcuM_SetMode(EcuM_GaaSleepModes[LucSleepModeIndex].ddMcuSleepModeType);
      }
      #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
      else
      {
        EcuM_GblAlarmExpired = ECUM_TRUE;
      }
      #endif
      EnableAllInterrupts();

      /* EI Fail Safe Redmine #8552 */
      /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "AUTOEVER_MISRA_2_2" */
      EcuM_EnableInterrupts();
    }
    /* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

    /* Invoke after ECU is woken up from sleep */
    LucRetVal = EcuM_CheckRamHash();

    /* Is RAM Integrity test failed */
    /* polyspace:begin<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Checking of NULL_PTR is for fail-safety */
    /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Checking of NULL_PTR is for fail-safety" */
    /* polyspace +2 MISRA-C3:2.1 [Justified:Medium] "Defensive programming" */
    /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "Defensive programming" */
    if (LucRetVal == (uint8)ECUM_ZERO)
    {
      #if (ECUM_DEMERROR_REPORT == STD_ON)
      /* Report to DEM */
      Dem_ReportErrorStatus(EcuM_GusERamCheckFailed,
          DEM_EVENT_STATUS_FAILED);
      #endif
      /* Invoke Callout error hook */
      EcuM_ErrorHook((Std_ReturnType)ECUM_E_RAM_CHECK_FAILED);
    }
    /* polyspace:end<DEFECT : DEAD_CODE : Not a defect : Justify with annotations > Checking of NULL_PTR is for fail-safety */
    /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Checking of NULL_PTR is for fail-safety" */
  } /* End of if (EcuM_GucHaltMask == (uint8)ECUM_ZERO) */

  /* polyspace +3 MISRA2012:14.3 [Not a defect:Low] "Variable can be changed by interrupt" */
  if ((EcuM_GddValidatedWakeupEvents != ECUM_NO_EVENTS) ||
      (EcuM_GddPendingWakeupEvents != ECUM_NO_EVENTS))
  {
    /* Start wakeup restart sequence if any validated or pending
     * wakeup events */
    #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
    if (EcuM_GddWakeupType == ECUM_WK_KNOWN_ALARM)
    {
      /* Clear alarm */
      EcuM_ClearAlarm();
      /* Stop timer  */
      Gpt_StopTimer(EcuM_GucGptChannelId);
      Gpt_DisableWakeup(EcuM_GucGptChannelId);
      Gpt_DisableNotification(EcuM_GucGptChannelId);
      #if (ECUM_PM_ENABLED == STD_OFF)
      Gpt_SetMode(GPT_MODE_NORMAL);
      #endif
    }
    #endif
  }
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GOHALT_SID,
        ECUM_E_UNKNOWN_WAKEUP_SOURCE);
    LddStdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  #endif

  return LddStdRetVal;
}

/*******************************************************************************
** Function Name        : EcuM_PollSeq                                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It gives the poll sequence used by the EcuM to      **
**                        check for any pending wakeup event.                 **
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
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GblAlarmExpired, EcuM_GucNoOfWakeupSources,    **
**                        EcuM_GaaWakeSource, EcuM_GddValidatedWakeupEvents,  **
**                        EcuM_GddPendingWakeupEvents                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_ClearAlarm(),                                  **
**                        EcuM_CheckWakeup(), EcuM_SleepActivity()            **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_PollSeq(void)
{
  /* Local variable for looping */
  uint8 LucLoop;
  uint8 LucIndex;

  /* Initialize loop variable */
  LucLoop = (uint8)ECUM_ONE;
  while ((LucLoop != (uint8)ECUM_ZERO)
         #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
         || (EcuM_GblAlarmExpired != ECUM_TRUE)
         #endif
         )
  {
    /* Invoke to poll wakeup source */
    /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "AUTOEVER_MISRA_2_2" */
    EcuM_SleepActivity();
    LucIndex = (uint8)ECUM_ZERO;
    /* For all wakeup sources */
    while (LucIndex < EcuM_GucNoOfWakeupSources)
    {
      /* Check whether polling is set for specific wakeup source */
      if (EcuM_GaaWakeSource[LucIndex].blWakeupSourcePolling ==
          (boolean)ECUM_ONE)
      {
        /* Invoke to poll wakeup source */
        EcuM_CheckWakeup(EcuM_GaaWakeSource[LucIndex].
          ddWakeupSourceId);

        if ((EcuM_GddValidatedWakeupEvents != ECUM_NO_EVENTS) ||
            (EcuM_GddPendingWakeupEvents != ECUM_NO_EVENTS))
        {
          #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
          /* Clear the alarm */
          EcuM_ClearAlarm();
          #endif

          /* update with zero to come out of loop */
          LucLoop = (uint8)ECUM_ZERO;
          LucIndex = EcuM_GucNoOfWakeupSources;
        }
      } /* End of if (EcuM_GaaWakeSource[LucIndex].blWakeupSourcePolling ==
         *ECUM_ONE)*/
      else
      {
        LucLoop = (uint8)ECUM_ZERO;
      }
      LucIndex++;
    }
  }
} /* End of EcuM_PollSeq */


#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
/*******************************************************************************
** Function Name        : EcuM_SlaveShutDownOrSleep                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : If Multicore support is ON,It gives the poll        **
**                        sequence used by the EcuM to check for any pending  **
**                        wakeup events for slave.                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LddCoreId                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GucHaltMask,          **
**                        EcuM_GucShutdownMask, EcuM_GucPollMask,             **
**                        EcuM_GstShutdownCauseTarget, EcuM_GusSleepModeId,   **
**                        EcuM_GaaSleepModes                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_OnGoOffOne(), SchM_Deinit(), EcuM_OsSetEvent(),**
**                        EcuM_SearchMode(), EcuM_DetReportError(),           **
**                        EcuM_GoSleepSeq(), DisableAllInterrupts(),          **
**                        EcuM_SetMode(), EnableAllInterrupts(),              **
**                        EcuM_WakeupRestartSeq()                             **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_SlaveShutDownOrSleep(CoreIdType LddCoreId)
{
  uint8 LucSlaveSleepModeIndex;
  uint8 LucCoreMask;
  boolean LblSleepModeValid;

  /* polyspace +2 RTE:OVFL [Not a defect:No action planned> It is defined from statically defined value */
  /* polyspace +1 RTE:SHF [Justified:Medium] "Pointer not access out of array" */
  LucCoreMask = ((uint8)ECUM_ONE << LddCoreId);

  /* Perform slave shutdown sequence */
  if ((EcuM_GucShutdownMask & LucCoreMask) == LucCoreMask)
  {
    EcuM_OnGoOffOne();
    /* Deinitialize the schedule manager */
    SchM_Deinit();
    /* Set the event to signal the master about slave shutdown */
    EcuM_OsSetEvent(LddCoreId);
  }
  else if (((EcuM_GucHaltMask & LucCoreMask) == LucCoreMask) ||
           ((EcuM_GucPollMask & LucCoreMask) == LucCoreMask))
  {
    /* Perform slave sleep sequence */
    /* To get the index of the structure array EcuM_GaaSleepModes for
     *   current sleep mode */
    LblSleepModeValid = EcuM_SearchMode(&LucSlaveSleepModeIndex,
                                       EcuM_GstShutdownCauseTarget.ucSleepMode);
    if (LblSleepModeValid == FALSE)
    {
      EcuM_GusSleepModeId = ECUM_INVALID_SLEEPMODEID;
      #if (ECUM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GOHALT_SID, ECUM_E_UNKNOWN_SLEEP_MODE);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
      EcuM_GoSleepSeq(LucSlaveSleepModeIndex);

      /* Slave Core Halt/Poll sequence */
      /* Set the event to signal the master about slave sleep */
      EcuM_OsSetEvent(LddCoreId);
      /* Disable all the interrupts  */
      DisableAllInterrupts();
      /* Set MCU mode */
      EcuM_SetMode(EcuM_GaaSleepModes[LucSlaveSleepModeIndex].
          ddMcuSleepModeType);
      /* Enable all the interrupts */
      EnableAllInterrupts();

      EcuM_WakeupRestartSeq(LucSlaveSleepModeIndex);
    }/* End of if (LblSleepModeValid == FALSE) */
  }
  else
  {
    /* do nothing  */
  }
}
#endif

#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
/*******************************************************************************
** Function Name        : EcuM_GetGptTicks                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It gives the next GPT ticks.                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTickValue                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        EcuM_GulMasterAlarm, EcuM_GulRunningTimer           **
**                        Function(s) invoked : None                          **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_GetGptTicks
  (P2VAR(uint32, AUTOMATIC, ECUM_DATA) LpTickValue)
{
  if (EcuM_GulMasterAlarm > EcuM_GulRunningTimer)
  {
    *LpTickValue = ((EcuM_GulMasterAlarm - EcuM_GulRunningTimer - (uint32)ECUM_ONE)
                    % EcuM_GulGptChannelTickMax) + (uint32)ECUM_ONE;
  }
  else
  {
    *LpTickValue = (uint32)ECUM_ZERO;
  }
}
#endif /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Function Name        : EcuM_DetReportError                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : If Dev Error Detection is enabled,                  **
**                        it stores last error status and reports to Det.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucApiId, LucErrorId                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : Dev Error Detection should be enabled.              **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_GstLastDetError                                **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
*******************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_DetReportError(uint8 LucApiId,
  uint8 LucErrorId)
{
  /* Local variable for return value */
  Std_ReturnType LddStdRetVal;

  EcuM_GstLastDetError.ucInstanceId = ECUM_INSTANCE_ID;
  EcuM_GstLastDetError.ucApiId = LucApiId;
  EcuM_GstLastDetError.ucErrorId = LucErrorId;

  /*Report to DET */
  LddStdRetVal = Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID,
      LucApiId, LucErrorId);

  return LddStdRetVal;
}
#endif

/*******************************************************************************
** Function Name        : EcuM_SearchSleepModeWakeupSource                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Searching index corresponding to a specific user**
**                        ONLY IN current Sleep Mode Wakeup source            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : WakeupSource                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpSourceIdx                                         **
**                                                                            **
** Return parameter     : LblSearchResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GusSleepModeIndex     **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_SearchSleepModeWakeupSource
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) LpSourceIdx,
  EcuM_WakeupSourceType wakeupSource)
{
  uint8 LucIndex;

  /* variable to break the FOR loop */
  boolean LblSearchResult;

  /* Set the search result flag to ECUM_FALSE */
  LblSearchResult = ECUM_FALSE;

  /* Set the initial value */
  *LpSourceIdx = EcuM_GucNoOfWakeupSources;

  /* For Redmine #5257 */
  if (EcuM_GusSleepModeId != ECUM_INVALID_SLEEPMODEID)
  {
    /* Check the WakeupSource by linear search */
    for (LucIndex = (uint8)ECUM_ZERO; ((LucIndex < EcuM_GucNoOfWakeupSources) &&
                                (LblSearchResult == ECUM_FALSE)); LucIndex++)
    {
      if(EcuM_GusSleepModeId < EcuM_GucNoOfSleepModes)
      {
        /* Is 'wakeupSource' matches with the configured WakeupSource with Sleepmode MASK */
        if ( ((wakeupSource & EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId) & (EcuM_GaaSleepModes[EcuM_GusSleepModeId].ddWakeupSourceMask)) ==
            EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId)
        {
          /* Set the search result flag to TRUE */
          LblSearchResult = ECUM_TRUE;

          /* Update index for Request Array Index */
          *LpSourceIdx = LucIndex;
        }
      }
    }
  }

  /* Return ECUM_TRUE if found else ECUM_FALSE */
  return (LblSearchResult);
} /* End of function body */


/*******************************************************************************
** Function Name        : EcuM_GetOSResource                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Getting OS Resource in sleep sequence           **
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
** Preconditions        : EcuM_GaaOsResources[] should be ordered by CoreID   **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GucNoOfOsResources    **
**                                                                            **
**                        Function(s) invoked    : GetCoreID(), GetResource() **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_GetOSResource (void)
{
  #if (ECUM_NO_OF_OSRESOURCES > ECUM_ZERO)
  uint8 osResInd;

  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  osResInd = (uint8)GetCoreID();
  if (osResInd < EcuM_GucNoOfOsResources)
  {
    (void)GetResource(EcuM_GaaOsResources[osResInd]);
  }
  #else
  osResInd = 0u;
  (void)GetResource(EcuM_GaaOsResources[osResInd]);
  #endif
  #endif /* #if (ECUM_NO_OF_OSRESOURCES > ECUM_ZERO) */
} /* End of function body */

/*******************************************************************************
** Function Name        : EcuM_ReleaseOSResource                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Releasing OS Resource in wakeup sequence        **
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
** Preconditions        : EcuM_GaaOsResources[] should be ordered by CoreID   **
**                                                                            **
** Remarks              : Global Variable(s)     : EcuM_GucNoOfOsResources    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        GetCoreID(), ReleaseResource()                      **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_ReleaseOSResource (void)
{
  #if (ECUM_NO_OF_OSRESOURCES > ECUM_ZERO)
  uint8 osResInd;

  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  osResInd = (uint8)GetCoreID();
  if (osResInd < EcuM_GucNoOfOsResources)
  {
    (void)ReleaseResource(EcuM_GaaOsResources[osResInd]);
  }
  #else
  osResInd = 0u;
  (void)ReleaseResource(EcuM_GaaOsResources[osResInd]);
  #endif
  #endif /* #if (ECUM_NO_OF_OSRESOURCES > ECUM_ZERO) */
} /* End of function body */


/*******************************************************************************
** Function Name        : EcuM_McuPostInit                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Post init step for Mcu                          **
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
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_McuPostInit (void)
{
  /*  For Redmine #5213  */
  #if HWRESOURCE_VENDOR(HWRESOURCE_FREESCALE)
/* polyspace<MISRA-C:11.3:Not a defect:Justify with annotations> Not a defect */
  REG_WRITE32(RTC_CR, (uint32)0x00000000UL);
/* polyspace<MISRA-C:11.3:Not a defect:Justify with annotations> Not a defect */
  RTC_CLEAR_ALL_INTERRUPT();
  #endif

  /*  For Redmine #4945  */
  #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
  #ifdef MCU_CLR_COLD_RESET_STAT_API
  Mcu_ClearColdResetStatus();
  #endif
  #endif
} /* End of function body */

/*******************************************************************************
** Function Name        : EcuM_EnableInterrupts                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Enable Interrupt Fail Safe                      **
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
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_EnableInterrupts (void)
{
  /*  For Tricore Compiler  */
  #ifdef __TASKING__
  /* polyspace<MISRA-C:8.1:Not a defect:Justify with annotations> Not a defect */
  (void) __enable();
  #endif

  /*  For GreenHills Compiler  */
  #ifdef __ghs__
  /* polyspace<MISRA-C:8.1:Not a defect:Justify with annotations> Not a defect */
  (void) __EI();
  #endif

} /* End of function body */

#define ECUM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end RTE:UNR */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

