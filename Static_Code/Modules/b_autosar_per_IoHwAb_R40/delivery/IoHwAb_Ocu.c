/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_Ocu.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_Ocu_StartChannel                                       **
**              IoHwAb_Ocu_StopChannel                                        **
**              IoHwAb_Ocu_SetPinState                                        **
**              IoHwAb_Ocu_SetPinAction                                       **
**              IoHwAb_Ocu_GetCounter                                         **
**              IoHwAb_Ocu_SetAbsoluteThreshold                               **
**              IoHwAb_Ocu_SetRelativeThreshold                               **
**              IoHwAb_Ocu_EnableNotification                                 **
**              IoHwAb_Ocu_DisableNotification                                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By         Description                             **
********************************************************************************
** 1.15.0.2  09-Sep-2021   Yangjin    #31974                                  **
** 1.10.1    04-Aug-2020   Yangjin    #24902                                  **
** 1.0.1     16-SEP-2015   Jongyoung  1.MISRA-C Rule violation fix            **
** 1.0.0     07-Jul-2015   Jongyoung  Initial version                         **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 MISRA-C3:10.5 [Justified:Unset] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_IoHwAb.h"
#include "IoHwAb_Ocu.h"
#include "IoHwAb_Config.h"

#if (IOHWAB_USE_OCU == STD_ON)
#include "Ocu.h"
#include "Ocu_Cfg.h"
#endif /* (IOHWAB_USE_OCU == STD_ON) */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_OCU == STD_ON)

#if (IOHWAB_OCU_START_CHANNEL_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuStartChannel                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service starts the timer of the corresponding  **
**                        OCU channel.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Value                                        **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuStartTimer                            **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuStartChannel(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuStartChannel != IOHWAB_NULL_PTR)&&
     (ChIdx < IoHwAb_GucNumOcuLgc))
  {
    IoHwAb_GpOcuStartChannel(IoHwAb_GaaOcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_START_CHANNEL_API == STD_ON) */


#if (IOHWAB_OCU_STOP_CHANNEL_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuStopTimer                                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service stops the timer of the corresponding   **
**                        OCU channel.                                        **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuStopTimer                             **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuStopChannel(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuStopChannel != IOHWAB_NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumOcuLgc))
  {
    IoHwAb_GpOcuStopChannel(IoHwAb_GaaOcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_STOP_CHANNEL_API == STD_ON) */


#if (IOHWAB_OCU_GET_COUNTER_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuGetCounter                                **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service get the counter values from            **
                          the corresponding OCU channel                       **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuGetCounter                            **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuGetCounter(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_OcuValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuGetCounter != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumOcuLgc)&&
      (Value != IOHWAB_NULL_PTR))
  {
    *Value = (IoHwAb_OcuValueType)IoHwAb_GpOcuGetCounter(IoHwAb_GaaOcuChIdx[ChIdx]);
  }
  else
  { 
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_GET_COUNTER_API == STD_ON) */


#if (IOHWAB_OCU_SET_PIN_STATE_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuSetPinState                               **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service Set the Output Pin State of            **
                          the corresponding OCU channel                       **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuSetState                              **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuSetPinState(IoHwAb_IndexType ChIdx, IoHwAb_OcuPinStateType PinState)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuSetPinState != IOHWAB_NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumOcuLgc))
  {
    IoHwAb_GpOcuSetPinState(IoHwAb_GaaOcuChIdx[ChIdx], (Ocu_PinStateType)PinState);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_SET_PIN_STATE_API == STD_ON) */


#if (IOHWAB_OCU_SET_PIN_ACTION_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuSetPinAction                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service Set the Output Pin Action of           **
                          the corresponding OCU channel                       **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuSetPinAction                          **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuSetPinAction(IoHwAb_IndexType ChIdx, IoHwAb_OcuPinActionType PinAction)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuSetPinAction != IOHWAB_NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumOcuLgc))
  {
    IoHwAb_GpOcuSetPinAction(IoHwAb_GaaOcuChIdx[ChIdx], (Ocu_PinActionType)PinAction);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }
  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_SET_PIN_ACTION_API == STD_ON) */

#if (IOHWAB_OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuSetAbsoluteThreshold                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the elapsed time value of the    **
**                        corresponding OCU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Value                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuSetAbsoluteThreshold                  **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuSetAbsoluteThreshold(IoHwAb_IndexType ChIdx,
    IoHwAb_OcuValueType ReferenceValue,
    IoHwAb_OcuValueType AbsoluteValue, 
    P2VAR(IoHwAb_OcuReturnType, AUTOMATIC, IOHWAB_APPL_DATA) ThresholdResult)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuSetAbsoluteThreshold != IOHWAB_NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumOcuLgc) &&
      (ThresholdResult != IOHWAB_NULL_PTR))
  {
    *ThresholdResult = (IoHwAb_OcuReturnType)IoHwAb_GpOcuSetAbsoluteThreshold(
    IoHwAb_GaaOcuChIdx[ChIdx], ReferenceValue, AbsoluteValue );
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) */

#if (IOHWAB_OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuSetRelativeThreshold                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the elapsed time value of the    **
**                        corresponding OCU channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Value                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuSetRelativeThreshold                  **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuSetRelativeThreshold(IoHwAb_IndexType ChIdx,
    IoHwAb_OcuValueType RelativeValue,
    P2VAR(IoHwAb_OcuReturnType, AUTOMATIC, IOHWAB_APPL_DATA) ThresholdResult)    
{
  Std_ReturnType LddError = E_OK;
  
  if ((IoHwAb_GpOcuSetRelativeThreshold != IOHWAB_NULL_PTR)&&
      (ThresholdResult != IOHWAB_NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumOcuLgc ))
  {
    *ThresholdResult = (IoHwAb_OcuReturnType)IoHwAb_GpOcuSetRelativeThreshold(
    IoHwAb_GaaOcuChIdx[ChIdx], RelativeValue);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_SET_RELATIVE_THRESHOLD_API == STD_ON) */

#if (IOHWAB_OCU_NOTIFICATION_SUPPORTED == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuDisableNotification                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables notification feature of the   **
**                        corresponding OCU channel.                          **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuDisableNotification                   **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuDisableNotification(IoHwAb_IndexType ChIdx)                                 
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuDisableNotification != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumOcuLgc))
  {
    IoHwAb_GpOcuDisableNotification(IoHwAb_GaaOcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(IOHWAB_OCU_NOTIFICATION_SUPPORTED == STD_ON)*/

#if (IOHWAB_OCU_NOTIFICATION_SUPPORTED == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_OcuEnableNotification                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables notification feature of the    **
**                        corresponding OCU channel.                          **
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
**                          IoHwAb_GaaOcuChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpOcuEnableNotification                    **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_OcuEnableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpOcuEnableNotification != IOHWAB_NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumOcuLgc))
  {
    IoHwAb_GpOcuEnableNotification(IoHwAb_GaaOcuChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Ocu_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_OCU_NOTIFICATION_SUPPORTED == STD_ON) */

#endif /* (IOHWAB_USE_OCU == STD_ON) */
/* polyspace-end MISRA-C3:D4.5 MISRA-C3:10.5 [Justified:Unset] "Not a defect" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
