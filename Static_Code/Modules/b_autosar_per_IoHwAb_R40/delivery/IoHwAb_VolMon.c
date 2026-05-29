/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_VolMon.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for VolMon module                         **
**              IoHwAb_VolMonInit                                             **
**              IoHwAb_VolMon                                                 **
**              IoHwAb_VolMonRead                                             **
**              IoHwAb_VolMonGetStatus                                        **
**              IoHwAb_VolMonIsThresholdOver                                  **
**              IoHwAb_VolMonIsThresholdUnder                                 **
**              IoHwAb_VolMonNotification                                     **
**                                                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.15.0.2  09-Sep-2021   Yangjin    #31974                                  **
** 1.10.1    04-Aug-2020   Yangjin    #24902                                  **
** 1.0.4     16-SEP-2015   Jongyoung  1.MISRA-C Rule violation fix            **
** 1.0.3     25-Mar-2015   Jongyoung  1.Manage the single module version      **
** 1.0.2     27-Sep-2014   Jongyoung  1. Polyspace result Adaption            **
** 1.0.1     18-Aug-2014   Sinil      1. Update Det error code                **
**                                    2. Add Dem event report                 **
** 1.0.0     07-Mar-2014   Sinil      Initial version                         **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 MISRA-C3:8.7 [Justified:Unset] "Not a defect" */
/* polyspace-begin MISRA-C3:11.5 [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/* polyspace-begin DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_VolMon.h"
#include "IoHwAb_Config.h"
#include "IoHwAb_AnaIn.h"
#include "Rte_IoHwAb.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (IOHWAB_USE_VOL_MON == STD_ON)
#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
VAR(uint8, IOHWAB_VAR) IoHwAb_GucVolMonIdx;
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
VAR(uint8, IOHWAB_VAR) IoHwAb_GucVolMonStatus;
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define IOHWAB_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, IOHWAB_VAR) IoHwAb_GusVolMonFiltValue;
#define IOHWAB_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif /* (IOHWAB_USE_VOL_MON == STD_ON) */
/* polyspace-begin RTE:UNR [Not a defect:Unset] "Reachable code" */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_VOL_MON == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_VolMonInit                                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service initilize VolMon module.               **
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
**                          IoHwAb_GucVolMonIdx,                              **
**                          IoHwAb_GusVolMonFiltValue,                        **
**                          IoHwAb_GaaVolMonIncr,                             **
**                          IoHwAb_GaaVolMonMask,                             **
**                          IoHwAb_GucVolMonStatus                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonInit(void)
{
  IoHwAb_GucVolMonIdx = 0;

  /* copy the default battery voltage */
  IoHwAb_GusVolMonFiltValue = IoHwAb_GusVolMonDefaultValue;

  /* loop until the correct threshold to set the global index */
  while((IoHwAb_GucVolMonIdx < IoHwAb_GucNumVolMonLevel)
    && (IoHwAb_GusVolMonFiltValue > IoHwAb_GaaVolMonIncr[IoHwAb_GucVolMonIdx]))
  {
    /* increment the index */
    IoHwAb_GucVolMonIdx++;
  }

  /* set the flags corresponding to the index */
  IoHwAb_GucVolMonStatus = IoHwAb_GaaVolMonMask[IoHwAb_GucVolMonIdx];
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_VolMon                                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
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
**                          IoHwAb_GusVolMonFiltValue,                        **
**                          IoHwAb_GucVolMonIdx,                              **
**                          IoHwAb_GaaVolMonIncr,                             **
**                          IoHwAb_GucVolMonStatus,                           **
**                          IoHwAb_GaaVolMonMask,                             **
**                          IoHwAb_GaaVolMonDecr                              **
**                        Function(s) invoked    :                            **
**                          IoHwAb_AnaInDirReadDirect,                        **
**                          IoHwAb_AnaInFirstOrderFiltering,                  **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMon(void)
{
  /* local index */
  uint8 LucIdx;
  /* local variable to hold the current battery level */
  IoHwAb_ValueType LddCurLevel = 0U;
  Std_ReturnType LddError = E_OK;

  /* first read directly the battery voltage */
  /* it could happend that Read direct is made during 10ms acquisition of     */
  /* analog inputs depending on CPU load and design of ConvertAllChannels, if */
  /* so log and error with no reste and skip the sample                       */
  LddError = IoHwAb_AnaInDirReadDirect(IoHwAb_GddVolMonAdcChIdx, &LddCurLevel, 1);
  if (LddError == E_OK)
  {
    /* now filter the battery level */
    LddCurLevel = IoHwAb_AnaInFirstOrderFiltering(IoHwAb_GusVolMonFiltValue,
      LddCurLevel, IoHwAb_GucVolMonFilter);

    /* if the new battery level is higher, the level is increasing, else decreasing */
    if (LddCurLevel > IoHwAb_GusVolMonFiltValue)
    {
      /*************************** level is increasing ************************/
      /* check if the global index is equal to the nb of thresholds */
      if (IoHwAb_GucVolMonIdx != IoHwAb_GucNumVolMonLevel)
      {/* the global index is smaller than the nb of thresholds */

        /* set the local index to the global index */
        LucIdx = IoHwAb_GucVolMonIdx;

        /* loop to reach the current threshold in the table */
        while ((LucIdx < IoHwAb_GucNumVolMonLevel)
          && (LddCurLevel >= IoHwAb_GaaVolMonIncr[LucIdx]))
        {
          /* increment the local index */
          LucIdx++;
        }

        /* test if the local index has changed */
        if (LucIdx != IoHwAb_GucVolMonIdx)
        {/* has changed */

          /* set the flags to mask[loc index] */
          IoHwAb_GucVolMonStatus = IoHwAb_GaaVolMonMask[LucIdx];

          /* set global index to local index */
          IoHwAb_GucVolMonIdx = LucIdx;

          IoHwAb_VolMonNotification();
        }
        else
        {/* not changed */
          /* do nothing, exit function */
        }
      }
      else
      {/* the global index is equal to the number of thresholds and VBAT is increasing */
        /* do nothing, exit function */
      }

    }
    else if (LddCurLevel < IoHwAb_GusVolMonFiltValue)
    {
      /*************************** level is decreasing *************************************/

      /* check if the global index is 0 */
      if ((IoHwAb_GucVolMonIdx != 0) && (IoHwAb_GucVolMonIdx <= IoHwAb_GucNumVolMonLevel))
      {/* the index is not 0 */

        /* set the local index to the global index */
        LucIdx = IoHwAb_GucVolMonIdx;

        /* loop to reach the current threshold in the table */
        while ((LucIdx > 0) && (LddCurLevel <= IoHwAb_GaaVolMonDecr[LucIdx]))
        {
          /* decrement the local index */
          LucIdx--;
        }

        /* test if the local index has changed */
        if (LucIdx != IoHwAb_GucVolMonIdx)
        {/* has changed */

          /* set the flags to mask[loc index] */
          IoHwAb_GucVolMonStatus = IoHwAb_GaaVolMonMask[LucIdx];

          /* set global index to local index */
          IoHwAb_GucVolMonIdx = LucIdx;

          IoHwAb_VolMonNotification();
        }
        else
        {/* not changed */
          /* do nothing, exit function */
        }
      }
      else
      {/* global index is 0 */
        /* do nothing, exit the function */
      }
    }
    else
    {
      /*************************** level is the same, do nothing  *************/
    }

    /* write the new value of the battery level */
    IoHwAb_GusVolMonFiltValue = LddCurLevel;
  }
  else
  {
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_VOLMON_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
    #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_VolMonRead                                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Value                                               **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GusVolMonFiltValue                         **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonRead(
  P2VAR(IoHwAb_ValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value)
{
  if (Value != NULL_PTR)
  {
    *Value = IoHwAb_GusVolMonFiltValue;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : IoHwAb_VolMonGetStatus                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Status                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucVolMonStatus                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonGetStatus(
  P2VAR(IoHwAb_StatusType, AUTOMATIC, IOHWAB_APPL_DATA) VolMonStatus)
{
  if (VolMonStatus != NULL_PTR)
  {
    *VolMonStatus = IoHwAb_GucVolMonStatus;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_VolMonIsThresholdOver                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Threshold                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Result                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucVolMonStatus                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonIsThresholdOver(
  IoHwAb_ThresholdType Threshold,
  P2VAR(IoHwAb_BoolType, AUTOMATIC, IOHWAB_APPL_DATA) VolMonResult)
{
  if ((VolMonResult != NULL_PTR) && ( Threshold < 8U))
  {
    if ( (IoHwAb_GucVolMonStatus & (uint8)(((IoHwAb_ThresholdType)1 << (IoHwAb_ThresholdType)Threshold) )) != 0U )
    {
      *VolMonResult = IOHWAB_TRUE;
    }
    else
    {
      *VolMonResult = IOHWAB_FALSE;
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_VolMonIsThresholdUnder                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Threshold                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Result                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GucVolMonStatus                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonIsThresholdUnder(
  IoHwAb_ThresholdType Threshold,
  P2VAR(IoHwAb_BoolType, AUTOMATIC, IOHWAB_APPL_DATA) VolMonResult)
{
  if ((VolMonResult != NULL_PTR) && ( Threshold < 8U))
  {
    if ( (IoHwAb_GucVolMonStatus & (uint8)(((IoHwAb_ThresholdType)1 << (IoHwAb_ThresholdType)Threshold))) != 0U )
    {
      *VolMonResult = IOHWAB_FALSE;
    }
    else
    {
      *VolMonResult = IOHWAB_TRUE;
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_VolMonNotification                           **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function notifies the transition of battery    **
**                        level to application                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          Rte_Call_R_VolMon_Cbk_Notification                **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_VolMonNotification(void)
{
  (void)Rte_Call_IoHwAb_R_VolMon_Cbk_Notification();
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_USE_VOL_MON == STD_ON) */
/* polyspace-end RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-end MISRA-C3:D4.5 MISRA-C3:8.7 [Justified:Unset] "Not a defect" */
/* polyspace-end MISRA-C3:11.5 [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/* polyspace-end DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
