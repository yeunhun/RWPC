/*******************************************************************************
**                                                                            **
**  (C) 2020-2021 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CDD_DataLog.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : DataLog CDD                                                   **
**                                                                            **
**  PURPOSE   : Provision of functions for DataLog                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0     07-Jun-2021    MJ.Woo        Redmine #29944                      **
** 1.0.1     09-Dec-2020    MJ.Woo        Redmine #26970                      **
** 1.0.0     17-Nov-2020    MJ.Woo        Redmine #25497                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CDD_DataLog.h"
#include "Dem.h"
#include "EcuM_Ram.h"
#include "BswM_Ram.h"
#if (SWP_USE_RAMTST == STD_ON)
#include "RamTst.h"
#endif
#if (SWP_USE_ROMTST == STD_ON)
#include "RomTst.h"
#endif
#if (SWP_USE_IOHWAB == STD_ON)
#include "IoHwAb.h"
#endif
#include "SchM_DataLog.h"
#include "string.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/**
* @addtogroup DATALOG_ESDD_008
* @{ */
#if (SWP_USE_DATALOG == STD_ON)

#define DATALOG_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"
/** Current Log Data */
DataLog_DataType DataLog_Data;
/** Saved Log Data in Dem */
DataLog_DataType DataLog_SavedData;
#define DATALOG_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"

#endif

#define DATALOG_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/** Current Sleep and Wakeup sequence */
static DataLog_SleepSeqType DataLog_SleepSequence;
#define DATALOG_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if (SWP_USE_DATALOG == STD_ON)

#if (DATALOG_CUSTOM_DATA_BYTE_SIZE > 0)
#define DATALOG_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/** CustomData update buffer */
static uint8 DataLog_PreStoredCustomData[DATALOG_CUSTOM_DATA_BYTE_SIZE];
#define DATALOG_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define DATALOG_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/** This indicates that PreStoredCustomData is valid(update required) */
static boolean DataLog_PreStoredCustomDataValid[DATALOG_CUSTOM_DATA_BYTE_SIZE];
#define DATALOG_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#define DATALOG_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/** DataLog_SleepDelayCount is used to check how long SLEEP has been delayed.
 * Overflow can occur after about 4971 days(MainFunction period: 100ms) */
static DataLog_DelayCountType DataLog_SleepDelayCount;
/** DataLog_WakeupDelayCount is used to check how long RUN has been delayed
 * after wakeup.
 * Overflow can occur after about 4971 days(MainFunction period: 100ms) */
static DataLog_DelayCountType DataLog_WakeupDelayCount;
#define DATALOG_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#endif /* End of #if (SWP_USE_DATALOG == STD_ON) */
/** @}  */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DATALOG_START_SEC_CODE
#include "MemMap.h"

/**
* @addtogroup DATALOG_ESDD_003
* @{ */
#if (SWP_USE_DATALOG == STD_ON)
/***************************************************************************//**
 * Function Name        : DataLog_DemReport
 *
 * Service ID           : NA
 *
 * Description          : Dem Event Status of DataLog is changed and the current
 *                        log data is reported to Dem.
 *                        When Dem Event Status becomes FAILED, Dem calls
 *                        ReadData callback and read the data(DataLog_SavedData)
 *                        to be stored in Dem.
 *                        Dem Event Memory is not updated immediately in the
 *                        Dem_ReportErrorStatus() because the callback is called
 *                        at Dem_MainFunction().
 *                        For the next Dem report, the event status is
 *                        immediately restored to its original status.
 *                        If the previous log data and the current log data are
 *                        the same, do nothing
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : DataLog_Init() should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        DataLog_SavedData, DataLog_Data
 *
 *                        Function(s) invoked    :
 *                        memcpy(), Dem_ReportErrorStatus()
 ******************************************************************************/
static FUNC(void, DATALOG_CODE) DataLog_DemReport(void)
{
  if ((DataLog_SavedData.ResetReason      == DataLog_Data.ResetReason) &&
      (DataLog_SavedData.WakeupEvent      == DataLog_Data.WakeupEvent) &&
      (DataLog_SavedData.WakeupEventMulti == DataLog_Data.WakeupEventMulti) &&
      (DataLog_SavedData.LpAllowNvM       == DataLog_Data.LpAllowNvM) &&
      (DataLog_SavedData.LpAllowRamTst    == DataLog_Data.LpAllowRamTst) &&
      (DataLog_SavedData.LpAllowRomTst    == DataLog_Data.LpAllowRomTst) &&
      (DataLog_SavedData.LpAllowIoHwAb    == DataLog_Data.LpAllowIoHwAb) &&
      (DataLog_SavedData.RunOK            == DataLog_Data.RunOK) &&
      (DataLog_SavedData.SleepOK          == DataLog_Data.SleepOK) &&
      (DataLog_SavedData.ComModeErr0      == DataLog_Data.ComModeErr0) &&
      (DataLog_SavedData.ComModeErr1      == DataLog_Data.ComModeErr1))
  {
    /* If Log Data were not changed, do nothing */
  }
  else /* Log Data were changed */
  {
    memcpy(&DataLog_SavedData, &DataLog_Data, DATALOG_DATA_BYTE_SIZE);
    Dem_ReportErrorStatus(DemConf_DemEventParameter_DATALOG_E_EVENT, DEM_EVENT_STATUS_FAILED);
    Dem_ReportErrorStatus(DemConf_DemEventParameter_DATALOG_E_EVENT, DEM_EVENT_STATUS_PASSED);
  }
}

#if (DATALOG_CUSTOM_DATA_BYTE_SIZE > 0)
/***************************************************************************//**
 * Function Name        : DataLog_DemReportCustomData
 *
 * Service ID           : NA
 *
 * Description          : Dem Event Status of DataLog is changed and the current
 *                        CustomData in log is reported to Dem.
 *                        When Dem Event Status becomes FAILED, Dem calls
 *                        ReadData callback and read the data(DataLog_SavedData)
 *                        to be stored in Dem.
 *                        Dem Event Memory is not updated immediately in the
 *                        Dem_ReportErrorStatus() because the callback is called
 *                        at Dem_MainFunction().
 *                        For the next Dem report, the event status is
 *                        immediately restored to its original status.
 *                        If the previous log data and the current log data are
 *                        the same, do nothing
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : DataLog_Init() should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        DataLog_SavedData, DataLog_Data
 *
 *                        Function(s) invoked    :
 *                        memcmp(), memcpy(), Dem_ReportErrorStatus()
 ******************************************************************************/
static FUNC(void, DATALOG_CODE) DataLog_DemReportCustomData(void)
{
  sint32 cmpResult;

  cmpResult = memcmp(&DataLog_SavedData.CustomData, &DataLog_Data.CustomData,
                                                 DATALOG_CUSTOM_DATA_BYTE_SIZE);

  /* Custom Log Data were changed */
  if (cmpResult != 0)
  {
    memcpy(&DataLog_SavedData.CustomData, &DataLog_Data.CustomData, DATALOG_CUSTOM_DATA_BYTE_SIZE);
    Dem_ReportErrorStatus(DemConf_DemEventParameter_DATALOG_E_EVENT, DEM_EVENT_STATUS_FAILED);
    Dem_ReportErrorStatus(DemConf_DemEventParameter_DATALOG_E_EVENT, DEM_EVENT_STATUS_PASSED);
  }
}
#endif
#endif /* End of #if (SWP_USE_DATALOG == STD_ON) */
/** @}  */

/**
* @addtogroup DATALOG_ESDD_008
* @{ */
/***************************************************************************//**
 * Function Name        : DataLog_GetSleepSequence
 *
 * Service ID           : NA
 *
 * Description          : This function provides Sleep and Wakeup sequence
 *                        information
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : DataLog_SleepSeqType
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        DataLog_SleepSequence
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(DataLog_SleepSeqType, DATALOG_CODE) DataLog_GetSleepSequence(void)
{
  return DataLog_SleepSequence;
}

/***************************************************************************//**
 * Function Name        : DataLog_SetSleepSequence
 *
 * Service ID           : NA
 *
 * Description          : This function sets Sleep and Wakeup sequence
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            seq    Sleep/Wakeup sequence to be set
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        DataLog_SleepSequence
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, DATALOG_CODE) DataLog_SetSleepSequence(DataLog_SleepSeqType seq)
{
  DataLog_SleepSequence = seq;
}

#if (SWP_USE_DATALOG == STD_ON)
/***************************************************************************//**
 * Function Name        : DataLog_DataSizeAssert
 *
 * Service ID           : NA
 *
 * Description          : This is an assert function that allows you to check
 *                        the satisfaction of the following conditions at
 *                        compile time:
 *                        - Size of DataArrayType_DE_DataLog
 *                        (Dem/DemGeneral0/Data Element Class/DE_DataLog
 *                        /DemExternalCSDataElementClass_DataLog
 *                        /DemDataElementDataSize) should be same with
 *                        DATALOG_DATA_BYTE_SIZE(Bswmd_DataLog.arxml
 *                        CDD_DataLog/ENUM_DataLogDataSize)
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
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
static void DataLog_DataSizeAssert(void)
{
  typedef uint8 BUILD_ASSERT[(!!(sizeof(DataArrayType_DE_DataLog)
                                               == DATALOG_DATA_BYTE_SIZE))*2-1];
}
#endif
/** @}  */

/**
* @addtogroup DATALOG_ESDD_002
* @{ */
#if (SWP_USE_DATALOG == STD_ON)
/***************************************************************************//**
 * Function Name        : DataLog_Init
 *
 * Service ID           : NA
 *
 * Description          : This function initializes the DataLog
 *                        1. Loads Dem log information saved
 *                        2. Initialize current log when destructive reset
 *                        3. Save reset reason to current log
 *                        4. Starts Dem Operation Cycle
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : Dem_Init() should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        DataLog_SavedData, DataLog_Data, EcuM_GddResetReason,
 *                        DataLog_SleepSequence, Dem_Event
 *
 *                        Function(s) invoked    :
 *                        DataLog_DataSizeAssert(), Dem_GetEventStatus(),
 *                        Dem_GetEventFreezeFrameData(), memcpy(),
 *                        Dem_SetOperationCycleState()
 ******************************************************************************/
static FUNC(void, DATALOG_CODE) DataLog_Init(void)
{
  uint8 demOperationCycleId;
  Dem_EventIdType demEventId;
  Dem_EventStatusExtendedType demEventStatusExtended;

  DataLog_DataSizeAssert();

  demEventId = DemConf_DemEventParameter_DATALOG_E_EVENT;
  demEventStatusExtended = 0u;
  (void)Dem_GetEventStatus(demEventId, &demEventStatusExtended);
  /* If TestFailedSinceLastClear, load FF from Dem */
  if ((demEventStatusExtended & DEM_UDS_STATUS_TFSLC) == DEM_UDS_STATUS_TFSLC)
  {
    (void)Dem_GetEventFreezeFrameData(DemConf_DemEventParameter_DATALOG_E_EVENT,
                                  0xFFu, TRUE, 0u, (uint8 *)&DataLog_SavedData);
  }

  /* If DataLog_SleepSequence is not DATALOG_SEQ_INIT,
   * the saved log before reset is maintained(except for ResetReason) */
  DataLog_Data.ResetReason = (uint8)EcuM_GddResetReason;
  if (DataLog_SleepSequence == DATALOG_SEQ_INIT)
  {
    DataLog_Data.WakeupEvent = 0u;
    DataLog_Data.WakeupEventMulti = FALSE;
    DataLog_Data.LpAllowNvM = FALSE;
    DataLog_Data.LpAllowRamTst = FALSE;
    DataLog_Data.LpAllowRomTst = FALSE;
    DataLog_Data.LpAllowIoHwAb = FALSE;
    DataLog_Data.ComModeErr0 = 0u;
    DataLog_Data.ComModeErr1 = 0u;
    DataLog_Data.RunOK = FALSE;
    DataLog_Data.SleepOK = FALSE;
    #if (DATALOG_CUSTOM_DATA_BYTE_SIZE > 0)
    memcpy(&DataLog_Data.CustomData, &DataLog_SavedData.CustomData, DATALOG_CUSTOM_DATA_BYTE_SIZE);
    #endif
  }

  /* polyspace +2 RTE:OBAI [Not a defect:Medium] "AUTRON_RTE_OBAI" */
  /* polyspace +2 MISRA-C3:18.1 [Not a defect:Medium] "AUTRON_MISRA_18_1" */
  demOperationCycleId = Dem_Event[demEventId - 1u].e_OperationCycleId;
  /* If E_NOT_OK is returned, DataLog doesn't work */
  (void)Dem_SetOperationCycleState(demOperationCycleId, DEM_CYCLE_STATE_START);
}
#endif /* End of #if (SWP_USE_DATALOG == STD_ON) */
/** @}  */

/**
* @addtogroup DATALOG_ESDD_004
* @{ */
#if (SWP_USE_DATALOG == STD_ON)
/***************************************************************************//**
 * Function Name        : DataLog_UpdateLowPowerAllowed
 *
 * Service ID           : NA
 *
 * Description          : It updates Low Power Allowed condition in DataLog_Data
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
 *                        DataLog_Data, BswM_GaaGenericRequestProperty,
 *                        BswM_GaaGenericCurrentState
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
static FUNC(void, DATALOG_CODE) DataLog_UpdateLowPowerAllowed(void)
{
  uint32 i;

  DataLog_Data.LpAllowNvM = TRUE;
  DataLog_Data.LpAllowRamTst = TRUE;
  DataLog_Data.LpAllowRomTst = TRUE;
  DataLog_Data.LpAllowIoHwAb = TRUE;

  for (i = 0u; i < BSWM_TOTAL_PORTS_OF_GENERIC_REQUEST; i++)
  {
    switch (BswM_GaaGenericRequestProperty[i].usModeRequesterId)
    {
      #if (SWP_USE_NVM == STD_ON)
      case NVM_MODULE_ID:     /* 20 */
        if (BswM_GaaGenericCurrentState[i].ddRequestedState == NVM_LOWPOWER_PREVENT)
        {
          DataLog_Data.LpAllowNvM = FALSE;
        }
        break;
      #endif
      #if (SWP_USE_RAMTST == STD_ON)
      case RAMTST_MODULE_ID:  /* 93 */
        if (BswM_GaaGenericCurrentState[i].ddRequestedState == RAMTST_LOWPOWER_PREVENT)
        {
          DataLog_Data.LpAllowRamTst = FALSE;
        }
        break;
      #endif
      #if (SWP_USE_ROMTST == STD_ON)
      case ROMTST_MODULE_ID:  /* 104 */
        if (BswM_GaaGenericCurrentState[i].ddRequestedState == ROMTST_LOWPOWER_PREVENT)
        {
          DataLog_Data.LpAllowRomTst = FALSE;
        }
        break;
      #endif
      #if (SWP_USE_IOHWAB == STD_ON)
      case IOHWAB_MODULE_ID:  /* 254 */
        if (BswM_GaaGenericCurrentState[i].ddRequestedState == IOHWAB_LOWPOWER_PREVENT)
        {
          DataLog_Data.LpAllowIoHwAb = FALSE;
        }
        break;
      #endif
      default:
        /* Do nothing */
        break;
    }
  }
}

/***************************************************************************//**
 * Function Name        : DataLog_UpdateCurrentComMode
 *
 * Service ID           : NA
 *
 * Description          : It updates ComM Mode condition in DataLog_Data
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
 *                        DataLog_Data, BswM_GaaComMCurrentMode
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
static FUNC(void, DATALOG_CODE) DataLog_UpdateCurrentComMode(void)
{
  uint8 i;

  for (i = 0u; i < BSWM_TOTAL_PORTS_OF_COMM_INDICATION; i++)
  {
    if (BswM_GaaComMCurrentMode[i].ddCurrentMode != COMM_NO_COMMUNICATION)
    {
      #if (BSWM_TOTAL_PORTS_OF_COMM_INDICATION > 8)
      /* Consider the bit position as the ComM Channel */
      if (i >= 8u)
      {
        DataLog_Data.ComModeErr1 |= (uint8)1u << (i - 8u);
      }
      #if (BSWM_TOTAL_PORTS_OF_COMM_INDICATION > 14)
      else if (i >= 14u)
      {
        /* Discard. Because maximum channel count is 14 */
      }
      #endif
      else
      #endif
      {
        DataLog_Data.ComModeErr0 |= (uint8)1u << i;
      }
    }
  }
}
#endif /* End of #if (SWP_USE_DATALOG == STD_ON) */

/***************************************************************************//**
 * Function Name        : DataLog_SetSleepConditionLog
 *
 * Service ID           : NA
 *
 * Description          : It clear previous SLEEP related data and
 *                        updates SLEEP condition in DataLog_Data
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
 *                        DataLog_SleepSequence, DataLog_Data,
 *                        DataLog_SleepDelayCount, DataLog_WakeupDelayCount
 *
 *                        Function(s) invoked    :
 *                        SchM_Enter_DataLog_DATA_PROTECTION(),
 *                        SchM_Exit_DataLog_DATA_PROTECTION(),
 *                        DataLog_UpdateLowPowerAllowed(),
 *                        DataLog_UpdateCurrentComMode()
 ******************************************************************************/
FUNC(void, DATALOG_CODE) DataLog_SetSleepConditionLog(void)
{
  #if (SWP_USE_DATALOG == STD_ON)
  /* To prevent clearing DataLog_SleepDelayCount when multiple sleep request */
  if (DataLog_SleepSequence != DATALOG_SEQ_SLEEP_REQ)
  {
    SchM_Enter_DataLog_DATA_PROTECTION();
    DataLog_SleepSequence = DATALOG_SEQ_SLEEP_REQ;
    /* Clear WakeupEvent bit before new sleep */
    DataLog_Data.WakeupEvent = 0u;
    DataLog_Data.WakeupEventMulti = FALSE;
    /* Clear SleepOK bit before new sleep */
    DataLog_Data.SleepOK = FALSE;
    /* Clear ComModeErr bit before new sleep */
    DataLog_Data.ComModeErr0 = 0u;
    DataLog_Data.ComModeErr1 = 0u;

    DataLog_SleepDelayCount = DATALOG_DELAY_ZERO;
    DataLog_WakeupDelayCount = DATALOG_DELAY_ZERO;

    DataLog_UpdateLowPowerAllowed();
    DataLog_UpdateCurrentComMode();
    SchM_Exit_DataLog_DATA_PROTECTION();
  }
  #endif
}
/** @}  */

/**
* @addtogroup DATALOG_ESDD_005
* @{ */
/***************************************************************************//**
 * Function Name        : DataLog_SetSleepOKLog
 *
 * Service ID           : NA
 *
 * Description          : It sets SleepOK to DataLog_Data.
 *                        It means that all BswM SLEEP related Rule conditions
 *                        have been passed
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
 *                        DataLog_SleepSequence, DataLog_Data
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, DATALOG_CODE) DataLog_SetSleepOKLog(void)
{
  #if (SWP_USE_DATALOG == STD_ON)
  DataLog_SleepSequence = DATALOG_SEQ_H2L;
  DataLog_Data.SleepOK = TRUE;
  #endif
}
/** @}  */

/**
* @addtogroup DATALOG_ESDD_006
* @{ */
/***************************************************************************//**
 * Function Name        : DataLog_SetWakeupEventLog
 *
 * Service ID           : NA
 *
 * Description          : It updates Wakeup event in DataLog_Data
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
 *                        DataLog_SleepSequence, DataLog_Data
 *
 *                        Function(s) invoked    :
 *                        EcuM_GetValidatedWakeupEvents()
 ******************************************************************************/
FUNC(void, DATALOG_CODE) DataLog_SetWakeupEventLog(void)
{
  #if (SWP_USE_DATALOG == STD_ON)
  EcuM_WakeupSourceType validatedWakeupEvent;
  uint8 bitPosition;
  uint32 wakeupEventCount;

  DataLog_SleepSequence = DATALOG_SEQ_L2H;
  wakeupEventCount = 0u;
  validatedWakeupEvent = EcuM_GetValidatedWakeupEvents();

  /* Consider the bit position as the Wakeup Event Id */
  for (bitPosition = 0u; bitPosition < 32u; bitPosition++)
  {
    if ((validatedWakeupEvent & ((uint32)1u << bitPosition)) != 0u)
    {
      /* Only one Wakeup Event(higher number) can save */
      DataLog_Data.WakeupEvent = bitPosition;
      wakeupEventCount++;
    }
  }
  /* Check if multiple wakeup event exists */
  if (wakeupEventCount > 1u)
  {
    DataLog_Data.WakeupEventMulti = TRUE;
  }
  #endif
}
/** @}  */

/**
* @addtogroup DATALOG_ESDD_001
* @{ */
/***************************************************************************//**
 * Function Name        : DataLog_MainFunction
 *
 * Service ID           : NA
 *
 * Description          : It works periodically to check for errors in
 *                        Sleep/Wakeup related logs and changes in CustomData
 *                        and report them to Dem.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : Dem_Init() should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        DataLog_InitStatus, DataLog_PreStoredCustomDataValid,
 *                        DataLog_PreStoredCustomData, EcuM_GucRunRequestStatus,
 *                        DataLog_SleepSequence, DataLog_Data,
 *                        DataLog_SleepDelayCount, DataLog_WakeupDelayCount
 *
 *                        Function(s) invoked    :
 *                        SchM_Enter_DataLog_DATA_PROTECTION(),
 *                        SchM_Exit_DataLog_DATA_PROTECTION(), DataLog_Init(),
 *                        DataLog_DemReportCustomData(), DataLog_DemReport(),
 ******************************************************************************/
FUNC(void, DATALOG_CODE) DataLog_MainFunction(void)
{
  #if (SWP_USE_DATALOG == STD_ON)
  #if (DATALOG_CUSTOM_DATA_BYTE_SIZE > 0)
  uint32 i;
  boolean updateCustomData;
  #endif
  static DataLog_InitStatusType DataLog_InitStatus = DATALOG_INIT_NONE;

  /* Initialize DataLog */
  if (DataLog_InitStatus == DATALOG_INIT_NONE)
  {
    SchM_Enter_DataLog_DATA_PROTECTION();
    DataLog_Init();
    SchM_Exit_DataLog_DATA_PROTECTION();
    DataLog_InitStatus = DATALOG_INIT_COMPLETED;
  }

  #if (DATALOG_CUSTOM_DATA_BYTE_SIZE > 0)
  /* Check and Update CustomData */
  SchM_Enter_DataLog_DATA_PROTECTION();
  updateCustomData = (boolean)FALSE;
  for (i = 0u; i < DATALOG_CUSTOM_DATA_BYTE_SIZE; i++)
  {
    if (DataLog_PreStoredCustomDataValid[i] == TRUE)
    {
      DataLog_Data.CustomData[i] = DataLog_PreStoredCustomData[i];
      DataLog_PreStoredCustomDataValid[i] = (boolean)FALSE;
      updateCustomData = (boolean)TRUE;
    }
  }
  SchM_Exit_DataLog_DATA_PROTECTION();
  if (updateCustomData == TRUE)
  {
    DataLog_DemReportCustomData();
  }
  #endif

  /* Note: EcuM_GucRunRequestStatus
   * - ECUM_RUN_RUNNING -> ECUM_RUN_RELEASED: Sleep Request(EcuM_ReleaseRUN)
   * - ECUM_RUN_RELEASED -> ECUM_RUN_REQUESTED: Wakeup(EcuM_RequestRUN)
   * - ECUM_RUN_REQUESTED -> ECUM_RUN_RUNNING: RUN(EcuM_SetRunState) */
  if (EcuM_GucRunRequestStatus == ECUM_RUN_RUNNING)
  {
    SchM_Enter_DataLog_DATA_PROTECTION();
    DataLog_Data.RunOK = TRUE;
    SchM_Exit_DataLog_DATA_PROTECTION();
  }

  /* Check and Update Sleep/Wakeup log */
  SchM_Enter_DataLog_DATA_PROTECTION();
  switch (DataLog_SleepSequence)
  {
    /* Enter Sleep delayed */
    case DATALOG_SEQ_SLEEP_REQ:
      DataLog_SleepDelayCount++;
      if (DataLog_SleepDelayCount == DATALOG_DELAY_SLEEP_LIMIT)
      {
        DataLog_DemReport();
        DataLog_SleepSequence = DATALOG_SEQ_SLEEP_DELAYED;
      }
      break;

    /* Enter Sleep delay exceeds the limit */
    case DATALOG_SEQ_SLEEP_DELAYED:
      DataLog_SleepDelayCount++;
      if (EcuM_GucRunRequestStatus == ECUM_RUN_RUNNING)
      {
        DataLog_SleepSequence = DATALOG_SEQ_RUN;
      }
      break;

    /* Wakeup Reset */
    case DATALOG_SEQ_H2L:
    /* No Wakeup Reset(Normal Wakeup) */
    case DATALOG_SEQ_L2H:
    /* Incomplete wakeup */
    case DATALOG_SEQ_RUN_DELAYED:
      /* Wakeup and RUN OK */
      if (EcuM_GucRunRequestStatus == ECUM_RUN_RUNNING)
      {
        /* Sleep Condition Failed when requestSleep */
        if ((DataLog_Data.LpAllowNvM == FALSE) ||
            (DataLog_Data.LpAllowRamTst == FALSE) ||
            (DataLog_Data.LpAllowRomTst == FALSE) ||
            (DataLog_Data.LpAllowIoHwAb == FALSE) ||
            (DataLog_Data.ComModeErr0 != 0u) ||
            (DataLog_Data.ComModeErr1 != 0u))
        {
          DataLog_DemReport();
        }
        DataLog_SleepSequence = DATALOG_SEQ_RUN;
      }
      /* Wakeup but RUN NOT OK */
      else
      {
        DataLog_WakeupDelayCount++;
        if (DataLog_WakeupDelayCount == DATALOG_DELAY_WAKEUP_LIMIT)
        {
          DataLog_Data.RunOK = FALSE;
          DataLog_DemReport();
          DataLog_SleepSequence = DATALOG_SEQ_RUN_DELAYED;
        }
      }
      break;
    default:
      /* Do nothing */
      break;
  }
  SchM_Exit_DataLog_DATA_PROTECTION();
  #endif /* End of #if (SWP_USE_DATALOG == STD_ON) */
}
/** @}  */

/**
* @addtogroup DATALOG_ESDD_008
* @{ */
#if (DATALOG_CUSTOM_DATA_BYTE_SIZE > 0)
/***************************************************************************//**
 * Function Name        : DataLog_SetCustomData
 *
 * Service ID           : NA
 *
 * Description          : This function sets CustomData to buffer
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            customData         Data to be saved
 * @param [in]            customDataIndex    Index of CustomData array
 *
 * @return              : Std_ReturnType
 *                        - E_NOT_OK: customDataIndex is out of range
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        DataLog_PreStoredCustomData,
 *                        DataLog_PreStoredCustomDataValid
 *
 *                        Function(s) invoked    :
 *                        SchM_Enter_DataLog_DATA_PROTECTION(),
 *                        SchM_Exit_DataLog_DATA_PROTECTION()
 ******************************************************************************/
FUNC(Std_ReturnType, DATALOG_CODE) DataLog_SetCustomData(uint8 customData, uint32 customDataIndex)
{
  Std_ReturnType ret;

  if (customDataIndex >= DATALOG_CUSTOM_DATA_BYTE_SIZE)
  {
    ret = E_NOT_OK;
  }
  else
  {
    #if (SWP_USE_DATALOG == STD_ON)
    SchM_Enter_DataLog_DATA_PROTECTION();
    DataLog_PreStoredCustomData[customDataIndex] = customData;
    DataLog_PreStoredCustomDataValid[customDataIndex] = (boolean)TRUE;
    SchM_Exit_DataLog_DATA_PROTECTION();
    #endif
    ret = E_OK;
  }

  return ret;
}
#endif
/** @}  */

#define DATALOG_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
