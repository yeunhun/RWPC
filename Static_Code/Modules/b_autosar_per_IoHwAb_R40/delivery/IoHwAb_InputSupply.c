/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_InputSupply.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for Input Supply module                   **
**              IoHwAb_InputSupplyInit                                        **
**              IoHwAb_InputSupplyDigitalControl                              **
**              IoHwAb_InputSupplySwControl                                   **
**              IoHwAb_InputSupplyAnalogControl                               **
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
** 1.0.4     04-NOV-2015   Jongyoung  1.Support DigInput function removable   **
** 1.0.3     16-SEP-2015   Jongyoung  1.MISRA-C Rule violation fix            **
** 1.0.2     25-Mar-2015   Jongyoung  1.Manage the single module version      **
** 1.0.1     27-Sep-2014   Jongyoung  1. Polyspace result Adaption            **
** 1.0.0     07-Mar-2014   Sinil      Initial version                         **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.7 MISRA-C3:2.7 [Justified:Unset] "Not a defect" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_InputSupply.h"
#include "IoHwAb_Config.h"
#include "Rte_IoHwAb.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (IOHWAB_USE_IN_SUP_SWT == STD_ON)
#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
VAR(boolean, IOHWAB_VAR) IoHwAb_GblInputSupplySwBusy;
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (IOHWAB_USE_IN_SUP_SWT == STD_ON) */
/* polyspace-begin RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-begin DEFECT:USELESS_IF [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#if (IOHWAB_USE_IN_SUP_SWT == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_InputSupplyInit                              **
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
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_InputSupplyInit(void)
{
  IoHwAb_IndexType LucIdx;

  for (LucIdx = 0; LucIdx < IoHwAb_GddNumISupply; LucIdx++)
  {
    /* Set the initial value for Input supply switch (raub_ISSwitchControl) */
    IoHwAb_GblInputSupplySwControl[LucIdx]
      = IoHwAb_GaaInputSupplyInfos[LucIdx].ucInitMode;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#if (IOHWAB_USE_DIG_IN == STD_ON) 
#if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_InputSupplyDigitalControl                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : blHp, blOn                                          **
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
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_InputSupplyDigitalControl(
  boolean blHp, boolean blOn)
{
  IoHwAb_IndexType LucIdx;
  IoHwAb_IndexType LucEndIdx;
  IoHwAb_IndexType LucChRefIdx;
  boolean LblDoCtrl = TRUE;
  Dio_LevelType LddLevel;

  #if (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON)
  if (blHp == 0U)
  {
    LucEndIdx = IoHwAb_GddNumISupplyDigInLp;
  }
  else
  #endif /* (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON) */
  {
    LucEndIdx = IoHwAb_GddNumISupplyDig;
  }

  if (blOn != 0U)
  {
    IoHwAb_GblInputSupplySwBusy = TRUE;
  }
  else
  {
    IoHwAb_GblInputSupplySwBusy = FALSE;
  }

  for (LucIdx = 0U; LucIdx < LucEndIdx; LucIdx++)
  {
    LucChRefIdx = IoHwAb_GaaInputSupplyInfos[LucIdx].ddRefChIdx;
    if ((IoHwAb_GaaInputSupplyInfos[LucIdx].blUseInApp == TRUE)
      && (IoHwAb_GblInputSupplySwControl[LucIdx] == IOHWAB_IS_SW_OFF))
    {
      LblDoCtrl = FALSE;
    }

    if (LblDoCtrl != 0U)
    {
      if (blOn != 0U)
      {
        LddLevel = ( (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
          ? (Dio_LevelType)STD_LOW : (Dio_LevelType)STD_HIGH );
      }
      else
      {
        LddLevel = ( (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
          ? (Dio_LevelType)STD_HIGH : (Dio_LevelType)STD_LOW );
      }

      Dio_WriteChannel(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType, LddLevel);
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_InputSupplySwControl                         **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Level                                        **
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
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_InputSupplySwControl(
  IoHwAb_IndexType ChIdx, IoHwAb_LevelType Level)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GblInputSupplySwBusy != 0U) || (ChIdx >= IoHwAb_GddNumISupply))
  {
    LddError = RTE_E_IoHwAb_If_InputSupply_E_BUSY;
  }
  else 
  {
    if (IoHwAb_GaaInputSupplyInfos[ChIdx].blUseInApp == TRUE)
    {
      if (Level != 0U)
      {
        IoHwAb_GblInputSupplySwControl[ChIdx] = IOHWAB_IS_SW_ON;
      }
      else
      {
        IoHwAb_GblInputSupplySwControl[ChIdx] = IOHWAB_IS_SW_OFF;
      }
    }
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */
#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

#if (IOHWAB_USE_ANA_IN == STD_ON)
#if (IOHWAB_USE_ANA_SUP_SWT == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_InputSupplyAnalogControl                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : blHp, blOn                                          **
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
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_InputSupplyAnalogControl(boolean blOn)
{
  IoHwAb_IndexType LucIdx;
  IoHwAb_IndexType LucChRefIdx;
  boolean LblDoCtrl = TRUE;
  Dio_LevelType LddLevel;

  for (LucIdx = IoHwAb_GddNumISupplyDig; LucIdx < IoHwAb_GddNumISupply; LucIdx++)
  {
    LucChRefIdx = IoHwAb_GaaInputSupplyInfos[LucIdx].ddRefChIdx;

    if ((IoHwAb_GaaInputSupplyInfos[LucIdx].blUseInApp == TRUE)
      && (IoHwAb_GblInputSupplySwControl[LucIdx] == IOHWAB_IS_SW_OFF))
    {
      LblDoCtrl = FALSE;
    }

    if (LblDoCtrl != 0U)
    {
      if (blOn != 0U)
      {
        LddLevel = ( (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
          ? (Dio_LevelType)STD_LOW : (Dio_LevelType)STD_HIGH );
      }
      else
      {
        LddLevel = ( (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
          ? (Dio_LevelType)STD_HIGH : (Dio_LevelType)STD_LOW );
      }

      Dio_WriteChannel(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType, LddLevel);
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_USE_ANA_SUP_SWT == STD_ON) */
#endif /* (IOHWAB_USE_ANA_IN == STD_ON) */

#endif /* (IOHWAB_USE_IN_SUP_SWT == STD_ON) */
/* polyspace-end RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-end MISRA-C3:8.7 MISRA-C3:2.7 [Justified:Unset] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-end DEFECT:USELESS_IF [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
