/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_DigOut.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_DigOutInit                                             **
**              IoHwAb_DigOutDeInit                                           **
**              IoHwAb_DigOutWrite                                            **
**              IoHwAb_DigOutWriteDirect                                      **
**              IoHwAb_DigOutRead                                             **
**              IoHwAb_DigOutReadDirect                                       **
**              IoHwAb_DigOutWriteOutputsToHW                                 **
**              IoHwAb_DigOutGetFailure                                       **
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
** 1.13.1    27-Jan-2021   Yangjin    #27954                                  **
** 1.10.1    04-Aug-2020   Yangjin    #24902                                  **
** 1.0.9     22-JUL-2016   Jongyoung  #5211                                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_DigOut.h"
#include "IoHwAb_Config.h"
#if (IOHWAB_USE_L9826 == STD_ON)
#include "IoHwAb_DigOutL9826.h"
#endif /* (IOHWAB_USE_L9826 == STD_ON) */
#if (IOHWAB_USE_L99MC6 == STD_ON)
#include "IoHwAb_DigOutL99MC6.h"
#endif /* (IOHWAB_USE_L99MC6 == STD_ON) */
#if (IOHWAB_USE_TLE7240SL == STD_ON)
#include "IoHwAb_DigOutTLE7240SL.h"
#endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */


#include "Rte_IoHwAb.h"
#include "SchM_IoHwAb.h"
/* polyspace-begin RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-begin MISRA-C3:2.7 MISRA-C3:17.8 [Justified:Unset] "Not a defect" */
/* polyspace-begin MISRA-C3:11.5 [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "validated by test cases. It works as intended." */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_DIG_OUT == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigOutInit                                   **
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
**                          IoHwAb_GaaDigOutResultBuffer,                     **
**                          IoHwAb_GaaDigOutDefVal,                           **
**                          IoHwAb_GaaDigOutL9826Infos                        **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigOutL9826SwitchOn                        **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutInit(void)
{
  uint8 LucIdx;

  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigOutMcuBuffer; LucIdx++)
  {
    IoHwAb_GaaDigOutResultBuffer[LucIdx].ucResult
      = IoHwAb_GaaDigOutDefVal[LucIdx];
  }

  /* update buffered outputs except demultiplexed outputs  */
  IoHwAb_DigOutWriteOutputsToHW();

  #if (IOHWAB_USE_L9826 == STD_ON)
  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigOutL9826; LucIdx++)
  {
    IoHwAb_GaaDigOutResultBuffer[LucIdx + IoHwAb_GucNumDigOutL9826StartIdx].ucResult
      = IoHwAb_GaaDigOutL9826Infos[LucIdx].ucDefVal;
  }

  IoHwAb_DigOutL9826SwitchOn();

  /* update the L9826 demultiplexed outputs */
  (void)IoHwAb_DigOutL9826();
  #endif /* (IOHWAB_USE_L9826 == STD_ON) */

  #if (IOHWAB_USE_L99MC6 == STD_ON)
  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigOutL99MC6; LucIdx++)
  {
    IoHwAb_GaaDigOutResultBuffer[LucIdx + IoHwAb_GucNumDigOutL99MC6StartIdx].ucResult
      = IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ucDefVal;
  }

  (void)IoHwAb_DigOutL99MC6SwitchOn();

  /* update the L99MC6 demultiplexed outputs */
  (void)IoHwAb_DigOutL99MC6();
  #endif /* (IOHWAB_USE_L99MC6 == STD_ON) */

  #if (IOHWAB_USE_TLE7240SL == STD_ON)
  for (LucIdx = 0U; LucIdx < IoHwAb_GucNumDigOutTLE7240SL; LucIdx++)
  {
    IoHwAb_GaaDigOutResultBuffer[LucIdx + IoHwAb_GucNumDigOutTLE7240SLStartIdx].ucResult
      = IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ucDefVal;
  }

  (void)IoHwAb_DigOutTLE7240SLSwitchOn();

  /* update the TLE7240SL demultiplexed outputs */
  IoHwAb_DigOutTLE7240SL();
  #endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */

}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutDeInit                                 **
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
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigOutL9826SwitchOff,                      **
**                          IoHwAb_DigOutL99MC6SwitchOff                      **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutDeInit(void)
{
  #if (IOHWAB_USE_L9826 == STD_ON)
  (void)IoHwAb_DigOutL9826SwitchOff();
  #endif /* (IOHWAB_USE_L9826 == STD_ON) */

  #if (IOHWAB_USE_L99MC6 == STD_ON)
  (void)IoHwAb_DigOutL99MC6SwitchOff();
  #endif /* (IOHWAB_USE_L99MC6 == STD_ON) */

  #if (IOHWAB_USE_TLE7240SL == STD_ON)
  (void)IoHwAb_DigOutTLE7240SLSwitchOff();
  #endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutWrite                                  **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutResultBuffer                      **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutWrite(IoHwAb_IndexType ChIdx,
  IoHwAb_LevelType Level)
{
  uint8 LucShiftBit =  (uint8)(ChIdx % 8U);
  uint8 LucResBufIdx = (uint8)(ChIdx / 8U);
  IoHwAb_LevelType LddLevel = Level;

  if (LddLevel != IOHWAB_LOW)
  {
    LddLevel = IOHWAB_HIGH;
  }

  if (LucResBufIdx < IoHwAb_GucNumDigOutResultBuffer)
  {
     SchM_Enter_IoHwAb_IoHwAbProtection();
     IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult
       &= (uint8)(~((uint8)(1U << LucShiftBit)));
     IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult
       |= (uint8)(LddLevel << LucShiftBit);
     SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutWriteDirect                            **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutResultBuffer,                     **
**                          IoHwAb_GaaGenInfos,                               **
**                          IoHwAb_GaaDigOutChIdx,                            **
**                          bodigdir_DirectWrite                              **
**                        Function(s) invoked    :                            **
**                          Dio_ReadChannel,                                  **
**                          Dio_WriteChannel,                                 **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutWriteDirect(IoHwAb_IndexType ChIdx,
  IoHwAb_LevelType Level)
{
  Dio_LevelType LddDioChValue;
  uint8 LucShiftBit  = (uint8)(ChIdx % 8U);
  uint8 LucResBufIdx = (uint8)(ChIdx / 8U);
  IoHwAb_LevelType LddLevel = Level;

  if (LddLevel != IOHWAB_LOW)
  {
    LddLevel = IOHWAB_HIGH;
  }
  if ((LucResBufIdx < IoHwAb_GucNumDigOutResultBuffer) &&
      (ChIdx < IoHwAb_GucNumDigOutMcuLgc))
  {
     SchM_Enter_IoHwAb_IoHwAbProtection();
     IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult
       &= (uint8)(~((uint8)(1U << LucShiftBit)));
     IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult
       |= (uint8)(LddLevel << LucShiftBit);
     if (IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[ChIdx]].ucPolar == IOHWAB_POL_LOW)
     {
        if (LddLevel == IOHWAB_LOW)
        {  
           LddLevel = IOHWAB_HIGH;
        }
        else
        {
           LddLevel = IOHWAB_LOW;
        }
     }
  
     LddDioChValue = Dio_ReadChannel(
       IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[ChIdx]].ddDioChType);

     if (LddDioChValue != LddLevel)
     {
       IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucTempResult
         &= (uint8)(~((uint8)(1U << LucShiftBit)));
       IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucTempResult
         |= (uint8)(LddLevel << LucShiftBit);

       Dio_WriteChannel(
       IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[ChIdx]].ddDioChType,
          LddLevel);
     }
     SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutRead                                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Level                                               **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutResultBuffer                      **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutRead(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  uint8 LucShiftBit = (uint8)(ChIdx % 8U);
  uint8 LucResBufIdx = (uint8)(ChIdx / 8U);
  
  if ((Level != NULL_PTR )&&(LucResBufIdx < IoHwAb_GucNumDigOutResultBuffer)) 
  {
    SchM_Enter_IoHwAb_IoHwAbProtection();
    *Level = ((IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult)
    & ((uint8)(1U << LucShiftBit))) >> LucShiftBit;
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutReadDirect                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Level                                               **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaGenInfos,                               **
**                          IoHwAb_GaaDigOutChIdx                             **
**                        Function(s) invoked    :                            **
**                          Dio_ReadChannel                                   **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutReadDirect(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  Dio_LevelType LddDioChValue;
  if ( (ChIdx < IoHwAb_GucNumDigOutMcuLgc) && (Level != NULL_PTR) )
  {
    LddDioChValue = Dio_ReadChannel(
    IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[ChIdx]].ddDioChType);

    if (IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[ChIdx]].ucPolar == IOHWAB_POL_LOW)
    {
      if (LddDioChValue == STD_LOW)
      {
        *Level = IOHWAB_HIGH;
      }
      else
      {
        *Level = IOHWAB_LOW;
      }
    }
    else
    {
      if (LddDioChValue == STD_LOW)
      {
        *Level = IOHWAB_LOW;
      }
      else
      {
        *Level = IOHWAB_HIGH;
      }
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutWriteOutputsToHW                       **
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
**                          IoHwAb_GaaDigOutResultBuffer,                     **
**                          IoHwAb_GaaGenInfos,                               **
**                          IoHwAb_GaaDigOutChIdx                             **
**                        Function(s) invoked    :                            **
**                          Dio_ReadChannel,                                  **
**                          Dio_WriteChannel                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutWriteOutputsToHW(void)
{
  IoHwAb_IndexType LucIdx;
  uint8 LucShiftBit;
  uint8 LucResBufIdx;
  uint8 LucPolarByte;
  uint8 LucPolarValue;
  Dio_LevelType LddDioChValue;

  for (LucIdx = 0; LucIdx < IoHwAb_GucNumDigOutMcuLgc; LucIdx++)
  {
    LucShiftBit  = (uint8)(LucIdx % 8U);
    LucResBufIdx = (uint8)(LucIdx / 8U);

    SchM_Enter_IoHwAb_IoHwAbProtection();

    if (IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[LucIdx]].ucPolar == IOHWAB_POL_LOW)
    {
      LucPolarByte = IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult
        ^ ((uint8)(0x01U << LucShiftBit));
    }
    else
    {
      LucPolarByte = IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult;
    }
    LucPolarValue = (LucPolarByte & ((uint8)(0x01U << LucShiftBit))) >> LucShiftBit;

    LddDioChValue = Dio_ReadChannel(
      IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[LucIdx]].ddDioChType);

    if (LddDioChValue != LucPolarValue)
    {
      IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucTempResult = LucPolarByte;
      Dio_WriteChannel(
        IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[LucIdx]].ddDioChType,
        LucPolarValue);
    }

    SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutGetFailure                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
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
**                          IoHwAb_GaaDigOutL9826Infos,                       **
**                          IoHwAb_GaaParallelConfigInL9826                   **
**                          IoHwAb_GaaDiagInL9826                             **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutGetFailure(
  IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  #if (IOHWAB_USE_L9826_DIAG == STD_ON)
  uint8 LucShiftBit = ChIdx % 8U;
  uint8 LucBufIdx = ( ChIdx / 8U ) - IoHwAb_GucNumDigOutMcuBuffer;

  if (IoHwAb_GaaDigOutL9826ResultBuffer[LucBufIdx].blStartDiag == IOHWAB_FALSE)
  {
    LddError = E_OK;
  }
  else
  {
    if ((LucShiftBit == IOHWAB_THREE)
      && ((IoHwAb_GaaDigOutL9826Infos[LucBufIdx].ucDefVal & 0x08U) == 0U))
    {
      /* Pin 0 in parallel mode */
      LddError
        = (IoHwAb_GaaDigOutL9826ResultBuffer[LucBufIdx].ucDiagSCGResult
        & ((uint8)(0x01U << LucShiftBit)))
        ? (RTE_E_IoHwAb_If_DigOut_E_PARALLEL) : (E_OK);
    }
    else if ((LucShiftBit == IOHWAB_SEVEN)
      && ((IoHwAb_GaaDigOutL9826Infos[LucBufIdx].ucDefVal & 0x80U) == 0U))
    {
      /* Pin 1 in parallel mode */
      LddError
        = (IoHwAb_GaaDigOutL9826ResultBuffer[LucBufIdx].ucDiagSCGResult
        & ((uint8)(0x01U << LucShiftBit)))
        ? (RTE_E_IoHwAb_If_DigOut_E_PARALLEL) : (E_OK);
    }
    else
    {
      LddError
        = (IoHwAb_GaaDigOutL9826ResultBuffer[LucBufIdx].ucDiagSCGResult
        & ((uint8)(0x01U << LucShiftBit)))
        ? (RTE_E_IoHwAb_If_DigOut_E_OL_SCG)
        : ((IoHwAb_GaaDigOutL9826ResultBuffer[LucBufIdx].ucDiagSCBResult
        & ((uint8)(0x01U << LucShiftBit)))
        ? (RTE_E_IoHwAb_If_DigOut_E_SCB) : (E_OK));
    }
  }
  #endif /* (IOHWAB_USE_L9826_DIAG  == STD_ON) */

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */
/* polyspace-end RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-end MISRA-C3:2.7 MISRA-C3:17.8 [Justified:Unset] "Not a defect" */
/* polyspace-end MISRA-C3:11.5 [Justified:Low] "Validated by test cases. It works as intended." */
/* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "validated by test cases. It works as intended." */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "It is checked by an if statement above." */
/* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "It depends on the configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

