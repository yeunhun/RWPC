/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_Gpt.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_GptStartTimer                                          **
**              IoHwAb_GptStopTimer                                           **
**              IoHwAb_GptGetTimeElapsed                                      **
**              IoHwAb_GptGetTimeRemaining                                    **
**              IoHwAb_GptDisableNotification                                 **
**              IoHwAb_GptEnableNotification                                 **
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
** 1.0.5     16-SEP-2015   Jongyoung  #4514                                   **
** 1.0.4     28-May-2015   Jongyoung  1.Bolero Errata e7953 resolved          **
**                                      IoHwAb_Pre(Post)ModeChange Api        **
** 1.0.3     25-Mar-2015   Jongyoung  1.Manage the single module version      **
** 1.0.2     27-Sep-2014   Jongyoung  1. Polyspace result Adaption            **
** 1.0.1     19-Aug-2014   Sinil      1. Change null types                    **
** 1.0.0     07-Mar-2014   Sinil      Initial version                         **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Gpt.h"
#include "Rte_IoHwAb.h"
#include "IoHwAb_Config.h"
#if (IOHWAB_USE_GPT == STD_ON)
#include "Gpt.h"
#endif /* (IOHWAB_USE_GPT == STD_ON) */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* polyspace-begin RTE:UNR [Justified:Low] "This if statement is needed for the validation." */
/* polyspace-begin RTE:IDP RTE:NIV [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-begin MISRA-C3:D4.5 MISRA-C3:18.1 [Justified:Unset] "Not a defect" */
/* polyspace-begin MISRA-C3:11.5 [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_GPT == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_GptStartTimer                                **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service starts the timer of the corresponding  **
**                        GPT channel.                                        **
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
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptStartTimer                            **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptStartTimer(IoHwAb_IndexType ChIdx,
  IoHwAb_GptValueType Value)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptStartTimer != IOHWAB_NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumGptLgc))
  {
    IoHwAb_GpGptStartTimer(IoHwAb_GaaGptChIdx[ChIdx], (Gpt_ValueType)Value);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_GptStopTimer                                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service stops the timer of the corresponding   **
**                        GPT channel.                                        **
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
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptStopTimer                             **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptStopTimer(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptStopTimer != IOHWAB_NULL_PTR)&&
      (ChIdx < IoHwAb_GucNumGptLgc))
  {
    IoHwAb_GpGptStopTimer(IoHwAb_GaaGptChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_GptGetTimeElapsed                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the elapsed time value of the    **
**                        corresponding GPT channel.                          **
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
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptGetTimeElapsed                        **
*******************************************************************************/
#if (IOHWAB_GPT_TIME_ELAPSED_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptGetTimeElapsed(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_GptValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptGetTimeElapsed != IOHWAB_NULL_PTR) && (Value != NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumGptLgc))
  {
    *Value = (IoHwAb_GptValueType)IoHwAb_GpGptGetTimeElapsed(IoHwAb_GaaGptChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(IOHWAB_GPT_TIME_ELAPSED_API == STD_ON)*/

/*******************************************************************************
** Function Name        : IoHwAb_GptGetTimeRemaining                          **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the remaining time value of the  **
**                        corresponding GPT channel.                          **
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
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptGetTimeRemaining                      **
*******************************************************************************/
#if (IOHWAB_GPT_TIME_REMAINING_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptGetTimeRemaining(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_GptValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptGetTimeRemaining != IOHWAB_NULL_PTR) && (Value != NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumGptLgc))
  {
    *Value = (IoHwAb_GptValueType)IoHwAb_GpGptGetTimeRemaining(IoHwAb_GaaGptChIdx[ChIdx]);
  }
  else
  { 
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(IOHWAB_GPT_TIME_REMAINING_API == STD_ON)*/

/*******************************************************************************
** Function Name        : IoHwAb_GptDisableNotification                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables notification feature of the   **
**                        corresponding GPT channel.                          **
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
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptDisableNotification                   **
*******************************************************************************/
#if (IOHWAB_GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptDisableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptDisableNotification != IOHWAB_NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumGptLgc))
  {
    IoHwAb_GpGptDisableNotification(IoHwAb_GaaGptChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(IOHWAB_GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)*/

/*******************************************************************************
** Function Name        : IoHwAb_GptEnableNotification                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables notification feature of the    **
**                        corresponding GPT channel.                          **
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
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptEnableNotification                    **
*******************************************************************************/
#if (IOHWAB_GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptEnableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptEnableNotification != IOHWAB_NULL_PTR) &&
      (ChIdx < IoHwAb_GucNumGptLgc))
  {
    IoHwAb_GpGptEnableNotification(IoHwAb_GaaGptChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(IOHWAB_GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)*/
#endif /* (IOHWAB_USE_GPT == STD_ON) */


/*polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*******************************************************************************
** Function Name        : IoHwAb_PreModeChange (Bolero Only)                  **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service covers Bolero errat #e7953             **
**                        This Api should be called before the Mcu_InitClock. **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : PIT_TIE_STATUS                                      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_GptPreModeChange(
  P2VAR(IoHwAb_IndexType, AUTOMATIC, IOHWAB_APPL_DATA) PIT_TIE_STATUS)
{
  uint16  LusPitChIdx;
  uint16  LusPitTieStatus = 0U;
  
  for( LusPitChIdx = 0U; LusPitChIdx < GPT_PIT_CHAN_NUM; LusPitChIdx++)
  {
    if((( REG_READ32(PIT_TCTRL(LusPitChIdx)))&((uint32)PIT_TCTRL_TIE)) == (uint32)PIT_TCTRL_TIE )
    {
      PIT_INTERRUPT_DISABLE(LusPitChIdx);
      LusPitTieStatus |= (uint16)((uint16)1 << (uint16)LusPitChIdx);      
    }
  }
  if (PIT_TIE_STATUS != NULL_PTR)
  {
     *PIT_TIE_STATUS = LusPitTieStatus;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : IoHwAb_PostModeChange (Bolero Only)                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service covers Bolero errat #e7953             **
**                        This Api should be called after the Mcu_InitClock.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : PIT_TIE_STATUS                                      **
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
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_GptPostModeChange(
  P2VAR(IoHwAb_IndexType, AUTOMATIC, IOHWAB_APPL_DATA) PIT_TIE_STATUS)
{
  uint16 LusPitChIdx = 0U;
  uint16 LusPitTieStatus = 0U;
  if (PIT_TIE_STATUS != NULL_PTR)
  { 
    LusPitTieStatus = *PIT_TIE_STATUS;
    for( LusPitChIdx = 0U; LusPitChIdx < GPT_PIT_CHAN_NUM; LusPitChIdx++)
    {
      if( (LusPitTieStatus & (uint16)((uint16)1 << (uint16)LusPitChIdx)) != 0U )
      {
        PIT_INTERRUPT_ENABLE(LusPitChIdx);
      }
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* polyspace-end RTE:UNR [Justified:Low] "This if statement is needed for the validation." */
/*polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/* polyspace-end RTE:IDP RTE:NIV [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-end MISRA-C3:D4.5 MISRA-C3:18.1 [Justified:Unset] "Not a defect" */
/* polyspace-end MISRA-C3:11.5 [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
