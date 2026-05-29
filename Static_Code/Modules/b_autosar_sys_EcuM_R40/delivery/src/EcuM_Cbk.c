/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : EcuM_Cbk.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Call Backs implementation for EcuM module                     **
**              EcuM_SetWakeupEvent                                           **
**              EcuM_ValidateWakeupEvent                                      **
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
** 3.0.5      17-Aug-2021   Junho Cho     Redmine #31552                      **
** 3.0.3      25-Nov-2020   Manje Woo     Redmine #18654                      **
** 2.9.0      17-Apr-2018   Sanghoon Bae  Redmine #12242                      **
** 2.5.3      12-Jan-2016   Daejun Park   Redmine #3856                       **
**                                        -Update precompile option           **
** 2.5.1      12-Oct-2015   Sanghoon Bae  Redmine #3035                       **
** 2.5.0      20-Aug-2015   Sanghoon Bae  Redmine #2571                       **
**                                        -Update EcuM_SetWakeupEvent         **
** 2.4.1      27-May-2015   Jihoon Jung   Redmine #2550                       **
** 2.3.2      29-Mar-2015   Daejun Park   Redmine #2376 #2388                 **
**                                        -Add ECUM_PM_ENABLED macro          **
**                                        -Update SetWakeupEvent function     **
** 2.3.1      19-Mar-2014   Daejun Park   Redmine #2345                       **
**                                        -Clear alarm when known wakeup event**
** 2.3.0      12-Mar-2014   Daejun Park   Redmine #2321                       **
**                                        -Update sleep/wakeup flags          **
** 2.2.1      26-Dec-2014   Daejun Park   Redmine #1879                       **
**                                        -Update to AUTRON template          **
** 2.2.0      26-Nov-2014   Daejun Park   Redmine #1536                       **
**                                        Modify alarm wakeup process         **
** 2.0.0      24-Apr-2014   Daejun Park   Update major version                **
** 1.1.0      07-Mar-2014   Daejun Park   Remove binary search APIs           **
** 1.0.0      04-Mar-2013   Daejun Park   Initial version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "EcuM_Ram.h"
#include "EcuM_Internal.h"
#include "EcuM_Config.h"

#include "SchM_EcuM.h"
#include "ComM_EcuMBswM.h"
#include "BswM_EcuM.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define ECUM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : EcuM_SetWakeupEvent                                 **
**                                                                            **
** Service ID           : 0x0C                                                **
**                                                                            **
** Description          : This routine is responsible for setting up off      **
**                        wakeup event. It takes the value and stores in the  **
**                        internal variable. This function must start the     **
**                        wakeup validation timeout timer.                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : sources                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)    :                             **
**                        EcuM_GaaWakeupStatus, EcuM_GaaWakeupCounter,        **
**                        EcuM_GaaWakeSource, EcuM_GblInitStatus,             **
**                        EcuM_GddPendingWakeupEvents,                        **
**                        EcuM_GddValidatedWakeupEvents                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, ComM_EcuM_WakeUpIndication,    **
**                        BswM_EcuM_CurrentWakeup,                            **
**                        EcuM_SearchWakeupSource                             **
*******************************************************************************/

FUNC(void, ECUM_CODE) EcuM_SetWakeupEvent(EcuM_WakeupSourceType sources)
{
  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  boolean LblAlarmExpired;
  #endif
  uint8 LucIndex;
  boolean LblSearchResult;

  LucIndex = (uint8)ECUM_ZERO;
  #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
  LblAlarmExpired = ECUM_FALSE;
  #endif
  #if (ECUM_DEV_ERROR_DETECT == STD_ON)

  /* Is module not initialized */
  if (EcuM_GblInitStatus == ECUM_UNINITIALIZED)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SETWAKEUPEVENT_SID, ECUM_E_UNINIT);
  }

  /* Module is initialized */
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    LblSearchResult = EcuM_SearchSleepModeWakeupSource(&LucIndex, sources);

    /* Is the reported event is an unknown event */
    if (LblSearchResult == ECUM_FALSE)
    {
      SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
      EcuM_GddWakeupType = ECUM_WK_UNKNOWN;
      SchM_Exit_EcuM_ALARM_TIME_PROTECTION();

      #if (ECUM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SETWAKEUPEVENT_SID,
        ECUM_E_UNKNOWN_WAKEUP_SOURCE);
      #endif
    }

    /* For Valid Wakeup event */
    else
    {
      #if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
      /* When alarm is present and
       * the source is a alarm source or normal source */
      if (sources == EcuM_GddAlarmWakeupSourceId)
      {
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        EcuM_GddWakeupType = ECUM_WK_KNOWN_ALARM;
        EcuM_GblAlarmCycle = ECUM_TRUE;
        EcuM_GulRunningTimer += EcuM_GulNextTick;

        if (EcuM_GulRunningTimer >= EcuM_GulMasterAlarm)
        {
          LblAlarmExpired = ECUM_TRUE;
          EcuM_GulRunningTimer = (uint32)ECUM_ZERO;
          EcuM_GulMasterAlarm = (uint32)ECUM_ZERO;
        }
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
      }
      else
      {
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        EcuM_GddWakeupType = ECUM_WK_KNOWN;
        EcuM_GblSleepCycle = ECUM_FALSE;
        EcuM_GblAlarmExpired = ECUM_TRUE;
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();

        LblAlarmExpired = ECUM_TRUE;
      }

      if (LblAlarmExpired == ECUM_TRUE)
      #endif /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
      {
        /* Is validation required */
        /* polyspace-begin RTE:UNR [Justified:Medium] "AUTOEVER_RTE_UNR" */
        /* polyspace<RTE: OBAI : Not a defect : No Action Planned > LucIndex has been checked */
        if (EcuM_GaaWakeSource[LucIndex].usWakeupValidationTimeOut
            != (uint16)ECUM_ZERO)
        {
          /* Is validation count zero */
          if (EcuM_GaaWakeupCounter[LucIndex] == (uint16)ECUM_ZERO)
          {
            /* Redmine #1536 */
            if (EcuM_GaaWakeupStatus[LucIndex] != ECUM_WKSTATUS_PENDING)
            {
              /* To enable data protection */
              SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

              /* Update WakeupCounter with configured WakeupValidationCount */
              EcuM_GaaWakeupCounter[LucIndex] =
                EcuM_GaaWakeSource[LucIndex].usWakeupValidationTimeOut;

              /* Update Status of wakeup source as PENDING */
              EcuM_GaaWakeupStatus[LucIndex] = ECUM_WKSTATUS_PENDING;

              /* Update the pending wakeup events variable */
              EcuM_GddPendingWakeupEvents |= sources;

              /* To disable data protection */
              SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

              /* Indicate current status of Wakeup source to BswM */
              BswM_EcuM_CurrentWakeup
                (EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId,
                ECUM_WKSTATUS_PENDING);
            }
          } /* End of if (EcuM_GaaWakeupCounter[LucIndex] == ECUM_ZERO) */
        } /* End of if (EcuM_GaaWakeSource[LucIndex].usWakeupValidationTimeOut
           *!= ECUM_ZERO) */
        /* polyspace-end RTE:UNR */

        /* Validation Not Required */
        else
        {
          /* Redmine #1536 */
          /* polyspace<RTE: OBAI : Not a defect : No Action Planned > LucIndex has been checked */
          if (EcuM_GaaWakeupStatus[LucIndex] != ECUM_WKSTATUS_VALIDATED)
          {
            /* To enable data protection */
            SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

            /* Update Status of wakeup source as VALIDATED */
            EcuM_GaaWakeupStatus[LucIndex] = ECUM_WKSTATUS_VALIDATED;

            /* Update the Validated event variable with sources */
            EcuM_GddValidatedWakeupEvents |= sources;

            /* To disable data protection */
            SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

            /* Indicate current status of Wakeup source to BswM */
            BswM_EcuM_CurrentWakeup(EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId,
              ECUM_WKSTATUS_VALIDATED);

            if (EcuM_GaaWakeSource[LucIndex].usComMChannel !=
                ECUM_COMM_INVALID_CHANNEL)
            {
              /* Indicate the wakeup event to ComM */
              ComM_EcuM_WakeUpIndication
                ((NetworkHandleType)(EcuM_GaaWakeSource[LucIndex].usComMChannel));
            }
          }
        } /* End of else */
      }
    }
  }
} /* End of EcuM_SetWakeupEvent */



/*******************************************************************************
** Function Name        : EcuM_ValidateWakeupEvent                            **
**                                                                            **
** Service ID           : 0x14                                                **
**                                                                            **
** Description          : EcuM_ValidateWakeupEvent() routine is responsible   **
**                        for validating all the WAKEUP events The validation **
**                        shall be valid when ANDing the parameter events with**
**                        the internal variable of pending wakeup events      **
**                        results in a value other than null.The service shall**
**                        invoke ComM_EcuM_WakeUpIndication of the            **
**                        Communication Manager for each event in the         **
**                        parameter, which is listed in the                   **
**                        ECUM_WKSOURCE_COMIF_XREF_LIST                       **
**                        configuration parameter.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : sources                                             **
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
**                        EcuM_GblInitStatus, EcuM_GddValidatedWakeupEvents   **
**                        EcuM_GddPendingWakeupEvents, EcuM_GaaWakeupStatus,  **
**                        EcuM_GaaWakeupCounter, EcuM_GaaWakeSource,          **
**                        EcuM_GddState                                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, EcuM_SearchWakeupSource,       **
**                        ComM_EcuM_WakeUpIndication,                         **
**                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION,           **
**                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION,            **
**                        BswM_EcuM_CurrentWakeup                             **
*******************************************************************************/
FUNC(void, ECUM_CODE) EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType sources)
{
  /* The variable LucIndex is used as index for WakeupSource structure array */
  uint8 LucIndex;

  #if (ECUM_DEV_ERROR_DETECT == STD_ON)
  /* The boolean variable checks whether the search result is TRUE or FALSE */
  boolean LblSearchResult;

  /* Is module uninitialized */
  if (EcuM_GblInitStatus == ECUM_UNINITIALIZED)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_VALIDATEWAKEUPEVENT_SID, ECUM_E_UNINIT);
  }

  /* Module is initialized */
  else
  #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ECUM_DEV_ERROR_DETECT == STD_OFF)
    (void)EcuM_SearchWakeupSource(&LucIndex, sources);
    #else
    LblSearchResult = EcuM_SearchWakeupSource(&LucIndex, sources);

    /* Is Wakeup Source unknown */
    if (LblSearchResult == ECUM_FALSE)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_VALIDATEWAKEUPEVENT_SID,
        ECUM_E_UNKNOWN_WAKEUP_SOURCE);
    }

    /* Known wakeup source */
    else
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_OFF) */
    {
      /* Is WakeupStatus of wakeup source(s) PENDING */
      if ((EcuM_GddPendingWakeupEvents & sources) != (EcuM_WakeupSourceType)ECUM_ZERO)
      {
        /* Is wakeup source a communication channel OR
         *   LblValidateFlag set */
        if ((EcuM_GddState != ECUM_STATE_STARTUP_TWO) ||
            (EcuM_GaaWakeSource[LucIndex].usComMChannel !=
             ECUM_COMM_INVALID_CHANNEL))
        {
          /* Redmine #1536 */
          if (EcuM_GaaWakeupStatus[LucIndex] != ECUM_WKSTATUS_VALIDATED)
          {
            /* To enable data protection */
            SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

            /* Update Status of wakeup source as VALIDATED */
            EcuM_GaaWakeupStatus[LucIndex] = ECUM_WKSTATUS_VALIDATED;

            /* Clear Validation Timeout Counter */
            EcuM_GaaWakeupCounter[LucIndex] = (uint16)ECUM_ZERO;

            /* Update the Validated event variable with sources */
            EcuM_GddValidatedWakeupEvents |= sources;

            /* Clear wakeup event from pending list */
            EcuM_GddPendingWakeupEvents &= (EcuM_WakeupSourceType)(~sources);

            /* To disable data protection */
            SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

            /* Indicate current status of Wakeup source to BswM */
            BswM_EcuM_CurrentWakeup(EcuM_GaaWakeSource[LucIndex].ddWakeupSourceId,
              ECUM_WKSTATUS_VALIDATED);

            if (EcuM_GaaWakeSource[LucIndex].usComMChannel !=
                ECUM_COMM_INVALID_CHANNEL)
            {
              /* Indicate the wakeup event to ComM */
              ComM_EcuM_WakeUpIndication
                ((NetworkHandleType)(EcuM_GaaWakeSource[LucIndex].usComMChannel));
            }
          }
        } /* End of if ((EcuM_GddState != ECUM_STATE_STARTUP_TWO) ||
           *(EcuM_GaaWakeSource[LucIndex].usComMChannel
           *!= ECUM_COMM_INVALID_CHANNEL))*/
      } /* End of if ((EcuM_GddPendingWakeupEvents & sources) != ECUM_ZERO) */
    }
  }
} /* End of EcuM_ValidateWakeupEvent */

/*******************************************************************************
** Function Name        : EcuM_SetRunState                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For Set EcuM Run Request State in RUN Mode          **
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

FUNC(void, ECUM_CODE) EcuM_SetRunState(void)
{
  SchM_Enter_EcuM_STATE_PROTECTION();

  EcuM_GucRunRequestStatus = ECUM_RUN_RUNNING;

  SchM_Exit_EcuM_STATE_PROTECTION();
}

#define ECUM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

