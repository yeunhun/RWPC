/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_Icu.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_IcuSetActivationCondition                              **
**              IoHwAb_IcuDisableNotification                                 **
**              IoHwAb_IcuEnableNotification                                  **
**              IoHwAb_IcuGetInputState                                       **
**              IoHwAb_IcuStartTimestamp                                      **
**              IoHwAb_IcuStopTimestamp                                       **
**              IoHwAb_IcuGetTimestampIndex                                   **
**              IoHwAb_IcuResetEdgeCount                                      **
**              IoHwAb_IcuEnableEdgeCount                                     **
**              IoHwAb_IcuDisableEdgeCount                                    **
**              IoHwAb_IcuGetEdgeNumbers                                      **
**              IoHwAb_IcuEnableEdgeDetection                                 **
**              IoHwAb_IcuDisableEdgeDetection                                **
**              IoHwAb_IcuStartSignalMeasurement                              **
**              IoHwAb_IcuStopSignalMeasurement                               **
**              IoHwAb_IcuGetTimeElapsed                                      **
**              IoHwAb_IcuGetDutyCycleValues                                  **
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
** 1.3.1     30-Apr-2019   Yangjin    #16954                                  **
** 1.0.5     16-SEP-2015   Jongyoung  1.MISRA-C Rule violation fix            **
** 1.0.4     25-Mar-2015   Jongyoung  1.Manage the single module version      **
** 1.0.3     27-Sep-2014   Jongyoung  1. Polyspace result Adaption            **
** 1.0.2     05-Sep-2014   Sinil      1. Update activation condition          **
** 1.0.1     19-Aug-2014   Sinil      1. Change null types                    **
** 1.0.0     07-Mar-2014   Sinil      Initial version                         **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 MISRA-C3:8.13 [Justified:Unset] "Not a defect" */
/* polyspace-begin MISRA-C3:11.5 DEFECT:PTR_CAST [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Icu.h"
#include "Rte_IoHwAb.h"
#include "IoHwAb_Config.h"
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (defined(IOHWAB_MCAL_INFINEON_TC38X)) || (defined(IOHWAB_MCAL_INFINEON_TC39X))
#define ICU_RISING_EDGE ICU_17_TIMERIP_RISING_EDGE
#define ICU_FALLING_EDGE ICU_17_TIMERIP_FALLING_EDGE
#define ICU_BOTH_EDGES ICU_17_TIMERIP_BOTH_EDGES
#define ICU_IDLE ICU_17_TIMERIP_IDLE
#endif
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_ICU == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_IcuSetActivationCondition                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service changes the activation condition of    **
**                        the corresponding ICU channel.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Activation                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuSetActivationCondition                **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuSetActivationCondition(IoHwAb_IndexType ChIdx,
  IoHwAb_IcuActivationType Activation)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuSetActivationCondition != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    if (Activation == IOHWAB_RISING_EDGE)
    {
      IoHwAb_GpIcuSetActivationCondition(IoHwAb_GaaIcuChIdx[ChIdx],
        (Icu_ActivationType)ICU_RISING_EDGE);
    }
    else if (Activation == IOHWAB_FALLING_EDGE)
    {
      IoHwAb_GpIcuSetActivationCondition(IoHwAb_GaaIcuChIdx[ChIdx],
        (Icu_ActivationType)ICU_FALLING_EDGE);
    }
    else if (Activation == IOHWAB_BOTH_EDGES)
    {
      IoHwAb_GpIcuSetActivationCondition(IoHwAb_GaaIcuChIdx[ChIdx],
        (Icu_ActivationType)ICU_BOTH_EDGES);
    }
    else
    {
      LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
    }
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_IcuDisableNotification                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables notification feature of the   **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuDisableNotification                   **
*******************************************************************************/
#if ((IOHWAB_ICU_EDGE_DETECT_API == STD_ON) || (IOHWAB_ICU_TIMESTAMP_API == STD_ON))
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuDisableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuDisableNotification != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    IoHwAb_GpIcuDisableNotification(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* ((IOHWAB_ICU_EDGE_DETECT_API == STD_ON) || (IOHWAB_ICU_TIMESTAMP_API == STD_ON)) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuEnableNotification                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables notification feature of the    **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuEnableNotification                    **
*******************************************************************************/
#if ((IOHWAB_ICU_EDGE_DETECT_API == STD_ON) || (IOHWAB_ICU_TIMESTAMP_API == STD_ON))
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuEnableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuEnableNotification != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    IoHwAb_GpIcuEnableNotification(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* ((IOHWAB_ICU_EDGE_DETECT_API == STD_ON) || (IOHWAB_ICU_TIMESTAMP_API == STD_ON)) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuGetInputState                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the input pin state of the       **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : State                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuGetInputState                         **
*******************************************************************************/
#if (IOHWAB_ICU_GET_INPUT_STATE_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuGetInputState(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuStateType, AUTOMATIC, IOHWAB_APPL_DATA) State)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuGetInputState != IOHWAB_NULL_PTR) && (State != NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    if (ICU_IDLE == IoHwAb_GpIcuGetInputState(IoHwAb_GaaIcuChIdx[ChIdx]))
    {
      *State = IOHWAB_IDLE;
    }
    else
    {
      *State = IOHWAB_ACTIVE;
    }
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif  /* (IOHWAB_ICU_GET_INPUT_STATE_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuStartTimestamp                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service starts timestamp feature of the        **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, BufSize, NotiItv                             **
**                                                                            **
** InOut parameter      : BufPtr                                              **
**                                                                            **
** Output Parameters    : State                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuStartTimestamp                        **
*******************************************************************************/
#if (IOHWAB_ICU_TIMESTAMP_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuStartTimestamp(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuValueType, AUTOMATIC, IOHWAB_APPL_DATA) BufPtr,
  uint16 BufSize, uint16 NotiItv)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuStartTimestamp != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
/* polyspace-begin MISRA-C3:11.3 [Justified:Low] "It is validated by test cases. It works as intended." */
    IoHwAb_GpIcuStartTimestamp(IoHwAb_GaaIcuChIdx[ChIdx], BufPtr, (uint16)BufSize,
      (uint16)NotiItv);
/* polyspace-end MISRA-C3:11.3 [Justified:Low] "It is validated by test cases. It works as intended." */
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_TIMESTAMP_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuStopTimestamp                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service stops timestamp feature of the         **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuStopTimestamp                         **
*******************************************************************************/
#if (IOHWAB_ICU_TIMESTAMP_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuStopTimestamp(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuStopTimestamp != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    IoHwAb_GpIcuStopTimestamp(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_TIMESTAMP_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuGetTimestampIndex                         **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service returns the array index number of      **
**                        timestamp buffer of the corresponding ICU channel.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : TimestampIdx                                        **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuGetTimestampIndex                     **
*******************************************************************************/
#if (IOHWAB_ICU_TIMESTAMP_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuGetTimestampIndex(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuIndexType, AUTOMATIC, IOHWAB_APPL_DATA) TimestampIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuGetTimestampIndex != IOHWAB_NULL_PTR) && 
      (TimestampIdx != NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    *TimestampIdx = (IoHwAb_IndexType)IoHwAb_GpIcuGetTimestampIndex
      (IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  { 
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_TIMESTAMP_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuResetEdgeCount                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service resets edge counter value of the       **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuResetEdgeCount                        **
*******************************************************************************/
#if (IOHWAB_ICU_EDGE_COUNT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuResetEdgeCount(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuResetEdgeCount != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    IoHwAb_GpIcuResetEdgeCount(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_COUNT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuEnableEdgeCount                           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables edge count feature of the      **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuEnableEdgeCount                       **
*******************************************************************************/
#if (IOHWAB_ICU_EDGE_COUNT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuEnableEdgeCount(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuEnableEdgeCount != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    IoHwAb_GpIcuEnableEdgeCount(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_COUNT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuDisableEdgeCount                          **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables edge count feature of the     **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuDisableEdgeCount                      **
*******************************************************************************/
#if (IOHWAB_ICU_EDGE_COUNT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuDisableEdgeCount(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuDisableEdgeCount != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    IoHwAb_GpIcuDisableEdgeCount(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_COUNT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuGetEdgeNumbers                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the edge counter value of the    **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Num                                                 **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuGetEdgeNumbers                        **
*******************************************************************************/
#if (IOHWAB_ICU_EDGE_COUNT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuGetEdgeNumbers(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuEdgeNumberType, AUTOMATIC, IOHWAB_APPL_DATA) Num)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuGetEdgeNumbers != IOHWAB_NULL_PTR) &&
      (Num != NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    *Num = (IoHwAb_ValueType)IoHwAb_GpIcuGetEdgeNumbers(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_COUNT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuEnableEdgeDetection                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables edge detect feature of the     **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuEnableEdgeDetection                   **
*******************************************************************************/
#if (IOHWAB_ICU_EDGE_DETECT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuEnableEdgeDetection(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuEnableEdgeDetection != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    IoHwAb_GpIcuEnableEdgeDetection(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_DETECT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuDisableEdgeDetection                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables edge detect feature of the    **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuDisableEdgeDetection                  **
*******************************************************************************/
#if (IOHWAB_ICU_EDGE_DETECT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuDisableEdgeDetection(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuDisableEdgeDetection != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    IoHwAb_GpIcuDisableEdgeDetection(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_EDGE_DETECT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuStartSignalMeasurement                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service starts signal measurement feature of   **
**                        the corresponding ICU channel.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuStartSignalMeasurement                **
*******************************************************************************/
#if (IOHWAB_ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuStartSignalMeasurement(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuStartSignalMeasurement != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    IoHwAb_GpIcuStartSignalMeasurement(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_SIGNAL_MEASUREMENT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuStopSignalMeasurement                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service stops signal measurement feature of    **
**                        the corresponding ICU channel.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuStopSignalMeasurement                 **
*******************************************************************************/
#if (IOHWAB_ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuStopSignalMeasurement(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuStopSignalMeasurement != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    IoHwAb_GpIcuStopSignalMeasurement(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_SIGNAL_MEASUREMENT_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuGetTimeElapsed                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the elapsed time value of the    **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Time                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuGetTimeElapsed                        **
*******************************************************************************/
#if (IOHWAB_ICU_GET_TIME_ELAPSED_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuGetTimeElapsed(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuValueType, AUTOMATIC, IOHWAB_APPL_DATA) Time)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpIcuGetTimeElapsed != IOHWAB_NULL_PTR)&&
      (Time != NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    *Time = (IoHwAb_IcuValueType)IoHwAb_GpIcuGetTimeElapsed(IoHwAb_GaaIcuChIdx[ChIdx]);
  }
  else
  { 
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_GET_TIME_ELAPSED_API == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IcuGetDutyCycleValues                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the duty cycle value of the      **
**                        corresponding ICU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DutyCycle                                           **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaIcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpIcuGetDutyCycleValues                    **
*******************************************************************************/
#if (IOHWAB_ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_IcuGetDutyCycleValues(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_IcuDutyCycleType, AUTOMATIC, IOHWAB_APPL_DATA) DutyCycle)
{
  Std_ReturnType LddError = E_OK;
  /* polyspace-begin MISRA-C3:9.3 [Justified:Low] "The third element of the structure type is not specified in AUTOSAR, it is only used in AURIX MCAL. The platform doesn't support it." */
  Icu_DutyCycleType DutyCycleResult = {0U,0U};
  /* polyspace-end MISRA-C3:9.3 [Justified:Low] "The third element of the structure type is not specified in AUTOSAR, it is only used in AURIX MCAL. The platform doesn't support it." */
  if ((IoHwAb_GpIcuGetDutyCycleValues != IOHWAB_NULL_PTR) &&
      (DutyCycle != NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumIcuLgc))
  {
    IoHwAb_GpIcuGetDutyCycleValues(IoHwAb_GaaIcuChIdx[ChIdx], &DutyCycleResult);
    DutyCycle->ActiveTime = (IoHwAb_IcuValueType)DutyCycleResult.ActiveTime;
    DutyCycle->PeriodTime = (IoHwAb_IcuValueType)DutyCycleResult.PeriodTime;
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Icu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON) */

#endif /* (IOHWAB_USE_ICU == STD_ON) */
/* polyspace-end MISRA-C3:D4.5 MISRA-C3:8.13 [Justified:Unset] "Not a defect" */
/* polyspace-end MISRA-C3:11.5 DEFECT:PTR_CAST [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
