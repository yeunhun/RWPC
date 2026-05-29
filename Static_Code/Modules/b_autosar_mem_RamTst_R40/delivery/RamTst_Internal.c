/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_Internal.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR RAMTST                                                **
**                                                                            **
**  PURPOSE   : Ram Test API Functionality                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By       Description                               **
********************************************************************************
** 1.3.2     30-Dec-2020   CY Song    RedMine #27378                          **
** 1.2.7     22-Jun-2017   YJ Yun     Redmine #6835                           **
** 1.2.7     15-Nov-2015   CY Song    Redmine #6608                           **
** 1.2.5     16-May-2016   CY Song    RedMine #4902                           **
** 1.2.3     05-Oct-2015   CY Song    Correct Misra Rule Error                **
** 1.0.4     17-Oct-2014   CY Song    Rd#1452 Correct PolySpace               **
** 1.0.3     06-Dec-2013   CY Song  Add SchM_Enter_RamTst_RAM_PROTECTION,     **
**                                  SchM_Exit_RamTst_RAM_PROTECTION and Library*
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation (uint8 data needs to be extracted from a uint32 address. the code is verified manually)
polyspace:begin<RTE: NIV : Not a defect : Justify with annotations > Cannot initialize because of Application variable
polyspace:begin<RTE: IDP : Not a defect : Justify with annotations > configured memory access index
*/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst_Internal.h"       /* Ram Test Module Internal Header File */
#include "RamTst_PCTypes.h"       /* Ram Test Module Internal Header File */
#include "RamTst.h"               /* Ram Test Module Internal Header File */
#include "RamTst_Config.h"
#include "RamTst_Crc.h"
#include "RamTst_Ram.h"
#include "SchM_RamTst.h"          /* SchM header file for data protection API*/

#if(RAMTST_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                 /* Ram Test Module Header File */
#endif
#if(RAMTST_DEMERROR_REPORT == STD_ON)
#include "RamTst_Dem_Cfg.h"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define RAMTST_START_SEC_CODE
#include "MemMap.h"

#if(RAMTST_LOW_COVERAGE_TEST_SELECTED == STD_ON)
static FUNC(boolean, RAMTST_CODE) RamTst_ParityBit(RamTst_CellType Ramcell);
#endif

#if(RAMTST_MEDIUM_COVERAGE_TEST_SELECTED == STD_ON)
static FUNC(boolean, RAMTST_CODE)
                              RamTst_PatternChk(RamTst_CellType* RamCellAddress,
                  RamTstTestPolicy RamBlockTstPolicy, uint32 RamTstFillPattern);
#endif

/*******************************************************************************
** Function Name        : RamTst_ParityBit                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Function to get parity of number Ramcell.           **
**                        It returns 1 if Ramcell has odd parity, and         **
**                        It returns 0 if Ramcell has even parity             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy           : Non-Reentrant, Non-Interruptible                   **
**                                                                            **
** Input Parameters     : RamTst_CellType                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : The Ram Test module must be initialized             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if(RAMTST_LOW_COVERAGE_TEST_SELECTED == STD_ON)
static FUNC(boolean, RAMTST_CODE) RamTst_ParityBit(RamTst_CellType Ramcell)
{
  boolean paritybit = (boolean)RAMTST_FALSE;
  RamTst_CellType CellVal = Ramcell;

  SchM_Enter_RamTst_RAM_PROTECTION();

  while (CellVal > RAMTST_ZERO)
  {
    if (paritybit != RAMTST_ZERO)
    {
      paritybit = (boolean)RAMTST_FALSE;
    }
    else
    {
      paritybit = (boolean)RAMTST_TRUE;
    }
    CellVal = CellVal & (CellVal - RAMTST_ONE);
  }

  SchM_Exit_RamTst_RAM_PROTECTION();

  return paritybit;
}
#endif
/*******************************************************************************
** Function Name        : RamTst_ParityBitBckGrdTst                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Function to get parity of number Ramcell.           **
**                        It returns RAMTST_PASSED if parity is correct       **
**                        It returns RAMTST_FAILED if parity is wrong         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy           : Non-Reentrant, Non-Interruptible                   **
**                                                                            **
** Input Parameters     : uint16                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : The Ram Test module must be initialized             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                RamTst_GddBckGrdTstRamVar   **
**                                                RamTst_GaaBlkParam          **
**                        Function(s) invoked    :                            **
**                                                 Dem_ReportErrorStatus      **
*******************************************************************************/
#if(RAMTST_LOW_COVERAGE_TEST_SELECTED == STD_ON)
FUNC(boolean, RAMTST_CODE) RamTst_ParityBitBckGrdTst(uint32 RamTstStrtAddress,
                                RamTst_NumberOfTestedCellsType RamTstNumOfCells)
{
 boolean LblRamCellTstResult;
 RamTst_CellType* LpAddress;
 RamTst_NumberOfBlocksType LddBlockIdx;
 RamTst_NumberOfTestedCellsType NumOfCells = RamTstNumOfCells;
 
 /* Pointer Initialized with Address of type RamTst_CellType */
 LpAddress = (RamTst_CellType*)RamTstStrtAddress;
 LddBlockIdx = RamTst_GddBckGrdTstRamVar.ddRunningBlockID - RAMTST_ONE;
 do
 {
    /* Invoke ParityBit Check API */
    /* polyspace<MISRA-C:21.1:Not a defect:No action planned> Configured memory address  */    
    LblRamCellTstResult = RamTst_ParityBit(*LpAddress);
    #if(RAMTST_PARITY_BIT == EVEN_PARITY)
    if(LblRamCellTstResult != RAMTST_ZERO)
    #endif
    #if(RAMTST_PARITY_BIT == ODD_PARITY)
    if(LblRamCellTstResult != RAMTST_ONE)
    #endif
    {
      /* Global Test Status is Failed */
      RamTst_GddBckGrdTstRamVar.blGblBckGrdTstError = RAMTST_FAILED;
      /* Block Test Status is Failed */
      RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_FAILED;

      if (RamTst_GulNumberOfBlocks > LddBlockIdx)
      {
        /* If atleast one Cell fails the Block status changed to NOT_OK */
        *(RamTst_GaaBlkParam[LddBlockIdx].pTestBlockStatus) =
                                                      RAMTST_RESULT_NOT_OK;
      }
      #if(RAMTST_DEMERROR_REPORT == STD_ON)
      /* Raise DEM Error and set the RamTst_GddTestStatus to Failed */
      Dem_ReportErrorStatus(RamTst_GusRamFailure, DEM_EVENT_STATUS_FAILED);
      #endif

      #if(RAMTST_TEST_ERROR_NOTIFICATION_SUPPORT == STD_ON)
      /* CallErrorNotification API */
      RAMTST_TEST_ERROR_NOTIFICATION();
      #endif
    }
    else
    {
      /* Block Test Status is Passed */
      RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_PASSED;
    }

    /* Point to next data byte */
    LpAddress=&LpAddress[RAMTST_ONE];
    /* Decrement Cell Count */
    NumOfCells--;

 }while (NumOfCells != RAMTST_ZERO);

 /* Save the Next Address */
 RamTst_GddBckGrdTstRamVar.ulBckGrdAddress = (uint32)LpAddress;

 return LblRamCellTstResult;
}
#endif
/*******************************************************************************
** Function Name        : RamTst_RunParityBitTst                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Function to get parity of number Ramcell.           **
**                        It returns RAMTST_PASSED if parity is correct       **
**                        It returns RAMTST_FAILED if parity is wrong         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy           : Non-Reentrant, Non-Interruptible                   **
**                                                                            **
** Input Parameters     : uint16                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : The Ram Test module must be initialized             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                 RamTst_GaaBlkParam         **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(RAMTST_LOW_COVERAGE_TEST_SELECTED == STD_ON)
FUNC(boolean, RAMTST_CODE) RamTst_RunParityBitTst
                                       (RamTst_NumberOfBlocksType RamTstBlockId)
{
  uint8 LucParaId;
  uint32 LulStrtAddr;
  uint32 LulEndAddr;

  boolean LblRamCellTstResult;
  RamTst_CellType* LpAddress;
  RamTst_CellType* LpEndAddress;

  LblRamCellTstResult = RAMTST_FAILED;
  LucParaId = (uint8)RamTstBlockId - RAMTST_ONE;
  if (LucParaId < RamTst_GulNumberOfBlocks)
  {
    LulStrtAddr =
            RamTst_GaaBlkParam[LucParaId].ulRamTstStartAddress;
    LulEndAddr = RamTst_GaaBlkParam[LucParaId].ulRamTstEndAddress;
    /* Pointer Initialized with Address of type RamTst_CellType */
    LpAddress = (RamTst_CellType*)LulStrtAddr;
    LpEndAddress = (RamTst_CellType*)LulEndAddr;
    do
    {
      /* Invoke ParityBit Check API */
      /* polyspace<MISRA-C:21.1:Not a defect:No action planned> Configured memory address  */
      LblRamCellTstResult = RamTst_ParityBit(*LpAddress);
      #if(RAMTST_PARITY_BIT == EVEN_PARITY)
      if(LblRamCellTstResult == RAMTST_ZERO)
      #endif
      #if(RAMTST_PARITY_BIT == ODD_PARITY)
      if(LblRamCellTstResult == RAMTST_ONE)
      #endif
      {
        LblRamCellTstResult = RAMTST_PASSED;
      }
      else
      {
        LblRamCellTstResult = RAMTST_FAILED;
      }

      /* If at least one cell fails return Error */
      if(LblRamCellTstResult == RAMTST_FAILED)
      {
        /* End the Loop */
        LpAddress = LpEndAddress;
      }
      else
      {
        /* Point to next data byte */
        LpAddress=&LpAddress[RAMTST_ONE];
      }

    }while (LpAddress < LpEndAddress);
  }
  else
  {
    #if(RAMTST_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID,
    RAMTST_RUNPARITYBITTST_SID, RAMTST_E_STATUS_FAILURE);
    #endif
  }

  return LblRamCellTstResult;
}
#endif
/*******************************************************************************
** Function Name        : RamTst_PatternChk                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Function to check the ram pattern test              **
**                        It returns 1 if Ramcell pattern check passed        **
**                        It returns 0 if Ramcell pattern check failed        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy           : Non-Reentrant, Non-Interruptible                   **
**                                                                            **
** Input Parameters     : RamTst_CellType, RamBlockTstPolicy, uint32          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : The Ram Test module must be initialized             **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if(RAMTST_MEDIUM_COVERAGE_TEST_SELECTED == STD_ON)
static FUNC(boolean, RAMTST_CODE) RamTst_PatternChk(RamTst_CellType* RamCellAddress,
                   RamTstTestPolicy RamBlockTstPolicy, uint32 RamTstFillPattern)
{
  volatile RamTst_CellType LddRamcellBckup;
  boolean LblRamCellTstResult;
  volatile RamTst_CellType* CellAddress;
  volatile RamTst_CellType*  CellAddress2;
  LblRamCellTstResult = RAMTST_FAILED;
  
  if (RamCellAddress != NULL_PTR)
  {
    SchM_Enter_RamTst_RAM_PROTECTION();
    /* Restore the CELL content if block test policy is non destructive */
    if(RamBlockTstPolicy == RAMTEST_NON_DESTRUCTIVE)
    {
      /* polyspace<MISRA-C:21.1:Not a defect:No action planned> Configured memory address  */
      LddRamcellBckup = *RamCellAddress;
    }
    else
    {
      /* fill RamTst_FillPattern in the cell content */
      LddRamcellBckup = RamTstFillPattern;
    }

    if ((uint32)&CellAddress != (uint32)RamCellAddress)
    {
      CellAddress = RamCellAddress;
      /* WRITE RAM PATTERN 0 */
      /* polyspace<MISRA-C:21.1:Not a defect:No action planned> Configured memory address  */
      *CellAddress = RAMTST_PATTERN_TYPE_1;

      RAMTST_NOP();
      
      /* VERIFY WRITTEN RAM PATTERN */
      if (*CellAddress == RAMTST_PATTERN_TYPE_1)
      {
        /* WRITE RAM PATTERN 1 */
        *CellAddress = RAMTST_PATTERN_TYPE_2;
        
        RAMTST_NOP();
        
        /* VERIFY WRITTEN RAM PATTERN */
        if(*CellAddress == RAMTST_PATTERN_TYPE_2)
        {
          #if(RAMTST_CHK_TRANS_ONETOZERO == STD_ON)
          /* WRITE RAM PATTERN 0 */
          *CellAddress = RAMTST_PATTERN_ZERO;
          
          RAMTST_NOP();
          
          /* VERIFY WRITTEN RAM PATTERN */
          if(*CellAddress == RAMTST_PATTERN_ZERO)
          {
            LblRamCellTstResult = RAMTST_PASSED;
          }
          #else
          LblRamCellTstResult = RAMTST_PASSED;
          #endif
        }
      }
      /* Restore the cell content */
      *CellAddress = LddRamcellBckup;
    }
    else
    {
      CellAddress2 = RamCellAddress;
      /* WRITE RAM PATTERN 0 */
      /* polyspace<MISRA-C:21.1:Not a defect:No action planned> Configured memory address  */
      *CellAddress2 = RAMTST_PATTERN_TYPE_1;
      
      RAMTST_NOP();
      
      /* VERIFY WRITTEN RAM PATTERN */
      if(RAMTST_PATTERN_TYPE_1 == *CellAddress2)
      {
        /* WRITE RAM PATTERN 1 */
        *CellAddress2 = RAMTST_PATTERN_TYPE_2;
        
        RAMTST_NOP();        
        
        /* VERIFY WRITTEN RAM PATTERN */
        if(RAMTST_PATTERN_TYPE_2 == *CellAddress2)
        {
          #if(RAMTST_CHK_TRANS_ONETOZERO == STD_ON)
          /* WRITE RAM PATTERN 0 */
          *CellAddress2 = RAMTST_PATTERN_ZERO;
          
          RAMTST_NOP();         
          
          /* VERIFY WRITTEN RAM PATTERN */
          if(RAMTST_PATTERN_ZERO == *CellAddress2)
          {
            LblRamCellTstResult = RAMTST_PASSED;
          }
          #else
          LblRamCellTstResult = RAMTST_PASSED;
          #endif
        }
      }
      /* Restore the cell content */
      *CellAddress2 = LddRamcellBckup;
    }
    SchM_Exit_RamTst_RAM_PROTECTION();
  }
  return(LblRamCellTstResult);
}
#endif
/*******************************************************************************
** Function Name        : RamTst_PatternChkBckGrdTst                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Function to get parity of number Ramcell.           **
**                        It returns RAMTST_PASSED if test is correct         **
**                        It returns RAMTST_FAILED if test is wrong           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy           : Non-Reentrant, Non-Interruptible                   **
**                                                                            **
** Input Parameters     : RamTst_NumberOfBlocksType                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : The Ram Test module must be initialized             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                 RamTst_GddBckGrdTstRamVar  **
**                                                 RamTst_GaaBlkParam         **
**                        Function(s) invoked    :                            **
**                                                 Dem_ReportErrorStatus      **
*******************************************************************************/
#if(RAMTST_MEDIUM_COVERAGE_TEST_SELECTED == STD_ON)
FUNC(boolean, RAMTST_CODE) RamTst_PatternChkBckGrdTst(uint32 RamTstStrtAddress,
                                RamTst_NumberOfTestedCellsType RamTstNumOfCells)
{
  boolean LblRamCellTstResult;
  RamTst_CellType* LpAddress;
  RamTst_NumberOfBlocksType LddBlockIdx;
  RamTst_NumberOfTestedCellsType NumOfCells = RamTstNumOfCells;
  

 /* Pointer Initialized with Address of type RamTst_CellType */
  LblRamCellTstResult = RAMTST_FAILED; 
  /* polyspace +2 MISRA-C3:11.5 [Justified:Low] "Not a defect" */
  LpAddress = (RamTst_CellType*)(void*)RamTstStrtAddress;
  LddBlockIdx = RamTst_GddBckGrdTstRamVar.ddRunningBlockID - RAMTST_ONE;
  do
  {
    if (LddBlockIdx < RamTst_GulNumberOfBlocks)
    {
      SchM_Enter_RamTst_PATTERN_CHECK_PROTECT();
      /* Invoke Pattern check API */
      LblRamCellTstResult = RamTst_PatternChk(LpAddress,
              RamTst_GaaBlkParam[LddBlockIdx].ddRamTstPolicy,
              RamTst_GaaBlkParam[LddBlockIdx].ulRamTstFillPattern);
      SchM_Exit_RamTst_PATTERN_CHECK_PROTECT();
      if(LblRamCellTstResult != RAMTST_ONE)
      {
        /* Block Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_FAILED;

        /* Global Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blGblBckGrdTstError = RAMTST_FAILED;

        /* If atleast one Cell fails the Block status changed to NOT_OK */
        *(RamTst_GaaBlkParam[LddBlockIdx].pTestBlockStatus) =
                                                      RAMTST_RESULT_NOT_OK;

        #if(RAMTST_DEMERROR_REPORT == STD_ON)
        /* Raise DEM Error and set the RamTst_GddTestStatus to Failed */
        Dem_ReportErrorStatus(RamTst_GusRamFailure, DEM_EVENT_STATUS_FAILED);
        #endif

        #if(RAMTST_TEST_ERROR_NOTIFICATION_SUPPORT == STD_ON)
        /* CallErrorNotification API */
        RAMTST_TEST_ERROR_NOTIFICATION();
        #endif
      }
      else
      {
        /* Block Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_PASSED;
      }

      /* Move to Next Cell */
      /* Point to next data byte */
      LpAddress=&LpAddress[RAMTST_ONE];
      /* Decrement Cell Count */
      NumOfCells--;
    }
    else
    {
      #if(RAMTST_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID,
      RAMTST_PATTERNCHKBCKGRDTST_SID, RAMTST_E_STATUS_FAILURE);
      #endif
      NumOfCells = RAMTST_ZERO;
    }        
  }while (NumOfCells != RAMTST_ZERO);

  /* Save the Next Address */

  RamTst_GddBckGrdTstRamVar.ulBckGrdAddress = (uint32)LpAddress;

  return LblRamCellTstResult;
}
#endif
/*******************************************************************************
** Function Name        : RamTst_RunPatternChk                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Function to get parity of number Ramcell.           **
**                        It returns RAMTST_PASSED if test is correct         **
**                        It returns RAMTST_FAILED if test is wrong           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy           : Non-Reentrant, Non-Interruptible                   **
**                                                                            **
** Input Parameters     : RamTst_NumberOfBlocksType                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : The Ram Test module must be initialized             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                 RamTst_GaaBlkParam         **
**                        Function(s) invoked    : None                       **
**                                                                            **
*******************************************************************************/
#if(RAMTST_MEDIUM_COVERAGE_TEST_SELECTED == STD_ON)
FUNC(boolean, RAMTST_CODE) RamTst_RunPatternChk(
                                       RamTst_NumberOfBlocksType RamTstBlockId)
{
  uint8 LucParaId;
  uint32 LulStrtAddr;
  uint32 LulEndAddr;
  boolean LblRamCellTstResult;
  RamTst_CellType* LpAddress;
  RamTst_CellType* LpEndAddress;

  LucParaId = (uint8)RamTstBlockId - RAMTST_ONE;
  LblRamCellTstResult = RAMTST_FAILED;
  
  if (LucParaId < RamTst_GulNumberOfBlocks)
  {
    LulStrtAddr =
            RamTst_GaaBlkParam[LucParaId].ulRamTstStartAddress;
    LulEndAddr = RamTst_GaaBlkParam[LucParaId].ulRamTstEndAddress;

    /* Pointer Initialized with Address of type RamTst_CellType */
    /* polyspace +2 MISRA-C3:11.5 [Justified:Low] "Not a defect" */
    LpAddress = (RamTst_CellType*)((void*)LulStrtAddr);
    /* polyspace +2 MISRA-C3:11.5 [Justified:Low] "Not a defect" */
    LpEndAddress = (RamTst_CellType*)((void*)LulEndAddr);
    do
    {
      /* Invoke Pattern check API */
      LblRamCellTstResult = RamTst_PatternChk(LpAddress,
         RamTst_GaaBlkParam[LucParaId].ddRamTstPolicy,
         RamTst_GaaBlkParam[LucParaId].ulRamTstFillPattern);
      if(LblRamCellTstResult == RAMTST_ONE)
      {
        LblRamCellTstResult = RAMTST_PASSED;
        /* Point to next data byte */
        LpAddress=&LpAddress[RAMTST_ONE];
      }
      else
      {
        LblRamCellTstResult = RAMTST_FAILED;
        /* End the Loop */
        LpAddress = LpEndAddress;
      }   

    }while (LpAddress < LpEndAddress);
  }
  else
  {
    #if(RAMTST_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID,
    RAMTST_RUNPATTERNCHK_SID, RAMTST_E_STATUS_FAILURE);
    #endif
  }
  return LblRamCellTstResult;
}
#endif
/*******************************************************************************
** Function Name        : RamTst_RunCrcTst                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Function to get CRC of Block.                       **
**                        It returns RAMTST_PASSED if parity is correct       **
**                        It returns RAMTST_FAILED if parity is wrong         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy           : Non-Reentrant, Non-Interruptible                   **
**                                                                            **
** Input Parameters     : uint16                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : The Ram Test module must be initialized             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                 RamTst_GaaBlkParam         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                                                 RamTst_CalculateCRC8       **
**                                                 RamTst_CalculateCRC8H2F    **
**                                                 RamTst_CalculateCRC16      **
**                                                 RamTst_CalculateCRC32      **
*******************************************************************************/
#if(RAMTST_HIGH_COVERAGE_TEST_SELECTED == STD_ON)
FUNC(boolean, RAMTST_CODE) RamTst_RunCrcTst
                                       (RamTst_NumberOfBlocksType RamTstBlockId)
{
  uint8 LucParaId;
  uint32 LulStrtAddr;
  uint32 LulEndAddr;
  boolean LblRamCellTstResult;
  uint8* LpAddress;
  uint32 LulRamBlockSize;

  #if(RAMTST_CRC_8_SUPPORT == STD_ON)
  uint8* LpEndAddress;
  uint8 LucRamBlockCalCrc;
  uint8 LucRamBlockCrc;
  #endif

  #if(RAMTST_CRC_8H2F_SUPPORT == STD_ON)
  uint8* LpEndAddress;
  uint8 LucRamBlockCalCrc;
  uint8 LucRamBlockCrc;
  #endif

  #if(RAMTST_CRC_16_SUPPORT == STD_ON)
  uint16* LpEndAddress;
  uint16 LusRamBlockCalCrc;
  uint16 LusRamBlockCrc;
  #endif

  #if(RAMTST_CRC_32_SUPPORT == STD_ON)
  uint32* LpEndAddress;
  uint32 LulRamBlockCalCrc;
  uint32 LulRamBlockCrc;
  #endif

  LblRamCellTstResult = RAMTST_FAILED;
  LucParaId = (uint8)RamTstBlockId - RAMTST_ONE;
  if (LucParaId < RamTst_GulNumberOfBlocks)
  {
    LulStrtAddr =
            RamTst_GaaBlkParam[LucParaId].ulRamTstStartAddress;
    LulEndAddr = RamTst_GaaBlkParam[LucParaId].ulRamTstEndAddress;

    if (0U != LulStrtAddr)
    {
      /* Pointer Initialized with Address of type RamTst_CellType */
      LpAddress = (uint8*)LulStrtAddr;

      LulRamBlockSize = (LulEndAddr - LulStrtAddr);

      #if(RAMTST_CRC_8_SUPPORT == STD_ON)
      LucRamBlockCalCrc = RamTst_CalculateCRC8(LpAddress, LulRamBlockSize,
                                          RAMTST_CRC_INITIAL_VALUE8, (boolean)RAMTST_TRUE);
      /* fetch the CRC Calculated from the End of Block */
      LpEndAddress = (uint8*)LulEndAddr;
      /* polyspace<MISRA-C:21.1:Not a defect:No action planned> Configured memory address  */
      LucRamBlockCrc = *LpEndAddress;
      if(LucRamBlockCalCrc == LucRamBlockCrc)
      {
        LblRamCellTstResult = RAMTST_PASSED;
      }
      else
      {
        LblRamCellTstResult = RAMTST_FAILED;
      }

      #endif

      #if(RAMTST_CRC_8H2F_SUPPORT == STD_ON)
      LucRamBlockCalCrc = RamTst_CalculateCRC8H2F(LpAddress, LulRamBlockSize,
                                       RAMTST_CRC_INITIAL_VALUE8H2F, RAMTST_TRUE);
      /* fetch the CRC Calculated from the End of Block */
      LpEndAddress = (uint8*)LulEndAddr;

      LucRamBlockCrc = *LpEndAddress;
      if(LucRamBlockCalCrc == LucRamBlockCrc)
      {
        LblRamCellTstResult = RAMTST_PASSED;
      }
      else
      {
        LblRamCellTstResult = RAMTST_FAILED;
      }
      #endif

      #if(RAMTST_CRC_16_SUPPORT == STD_ON)
      LusRamBlockCalCrc = RamTst_CalculateCRC16(LpAddress, LulRamBlockSize,
      RAMTST_CRC_INITIAL_VALUE16, RAMTST_TRUE);
      /* fetch the CRC Calculated from the End of Block */
      LpEndAddress = (uint16*)LulEndAddr;

      LusRamBlockCrc = *LpEndAddress;
      if(LusRamBlockCalCrc == LusRamBlockCrc)
      {
        LblRamCellTstResult = RAMTST_PASSED;
      }
      else
      {
        LblRamCellTstResult = RAMTST_FAILED;
      }
      #endif

      #if(RAMTST_CRC_32_SUPPORT == STD_ON)
      LulRamBlockCalCrc = RamTst_CalculateCRC32(LpAddress, LulRamBlockSize,
      RAMTST_CRC_INITIAL_VALUE32, RAMTST_TRUE);

      /* fetch the CRC Calculated from the End of Block */
      LpEndAddress = (uint32*)LulEndAddr;

      LulRamBlockCrc = *LpEndAddress;
      if(LulRamBlockCalCrc == LulRamBlockCrc)
      {
        LblRamCellTstResult = RAMTST_PASSED;
      }
      else
      {
        LblRamCellTstResult = RAMTST_FAILED;
      }
      #endif
    }
    else
    {
      RAMTST_REPORT_ERROR(RAMTST_RUNCRCTST_SID, RAMTST_E_STATUS_FAILURE);
    }      
  }
  else
  {
    RAMTST_REPORT_ERROR(RAMTST_RUNCRCTST_SID, RAMTST_E_STATUS_FAILURE);
  }

  return LblRamCellTstResult;
}
#endif
/*******************************************************************************
** Function Name        : RamTst_CrcBckGrdTst                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Function to get CRC of Block.                       **
**                        It returns RAMTST_PASSED if parity is correct       **
**                        It returns RAMTST_FAILED if parity is wrong         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy           : Non-Reentrant, Non-Interruptible                   **
**                                                                            **
** Input Parameters     : uint16                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : The Ram Test module must be initialized             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                RamTst_GddBckGrdTstRamVar   **
**                                                RamTst_GaaBlkParam          **
**                        Function(s) invoked    :                            **
**                                                 RamTst_CalculateCRC8       **
**                                                 Dem_ReportErrorStatus      **
**                                                 RamTst_CalculateCRC8H2F    **
**                                                 RamTst_CalculateCRC16      **
**                                                 RamTst_CalculateCRC32      **
*******************************************************************************/
#if(RAMTST_HIGH_COVERAGE_TEST_SELECTED == STD_ON)
FUNC(boolean, RAMTST_CODE) RamTst_CrcBckGrdTst(uint32 RamTstStrtAddress,
                                RamTst_NumberOfTestedCellsType RamTstNumOfCells)
{
  boolean LblRamCellTstResult;
  uint8* LpAddress;
  uint32 LulRamBlockSize;
  boolean LblCrcIsFirstCall;
  RamTst_NumberOfTestedCellsType LddBlockIdx;

  #if(RAMTST_CRC_8_SUPPORT == STD_ON)
  uint8* LpEndAddress;
  uint8 LucRamBlockCalCrc;
  uint8 LucRamBlockCrc;
  #endif

  #if(RAMTST_CRC_8H2F_SUPPORT == STD_ON)
  uint8* LpEndAddress;
  uint8 LucRamBlockCalCrc;
  uint8 LucRamBlockCrc;
  #endif

  #if(RAMTST_CRC_16_SUPPORT == STD_ON)
  uint16* LpEndAddress;
  uint16 LusRamBlockCalCrc;
  uint16 LusRamBlockCrc;
  #endif

  #if(RAMTST_CRC_32_SUPPORT == STD_ON)
  uint32* LpEndAddress;
  uint32 LulRamBlockCalCrc;
  uint32 LulRamBlockCrc;
  #endif

  LpAddress = (uint8*)RamTstStrtAddress;

  LblRamCellTstResult = RAMTST_FAILED;
  LulRamBlockSize = RamTstNumOfCells;
  LddBlockIdx = (uint32)RamTst_GddBckGrdTstRamVar.ddRunningBlockID -  RAMTST_ONE;
  if ((NULL_PTR != LpAddress) && (LddBlockIdx < RamTst_GulNumberOfBlocks))
  {
    if(RamTstStrtAddress !=
                         (RamTst_GaaBlkParam[LddBlockIdx].ulRamTstStartAddress))
    {
      LblCrcIsFirstCall = (boolean)RAMTST_FALSE;
    }
    else
    {
      LblCrcIsFirstCall = (boolean)RAMTST_TRUE;
    }
    #if(RAMTST_CRC_8_SUPPORT == STD_ON)
    LucRamBlockCalCrc = RamTst_CalculateCRC8(LpAddress, LulRamBlockSize,
                  RamTst_GddBckGrdTstRamVar.ucCrcInitialVal, LblCrcIsFirstCall);
    RamTst_GddBckGrdTstRamVar.ucCrcInitialVal = LucRamBlockCalCrc;
    /* CRC calculated till this address */
    LpAddress = &LpAddress[LulRamBlockSize];

    /* Save the Next Address */
    RamTst_GddBckGrdTstRamVar.ulBckGrdAddress = (uint32)LpAddress;

    /* Block Finished Condition */
    if((uint32)LpAddress == RamTst_GaaBlkParam[LddBlockIdx].ulRamTstEndAddress)
    {
      /* fetch the CRC Calculated from the End of Block */
      LpEndAddress = (uint8*)RamTst_GaaBlkParam[LddBlockIdx].ulRamTstEndAddress;
      /* polyspace<MISRA-C:21.1:Not a defect:No action planned> Configured memory address  */
      LucRamBlockCrc = *LpEndAddress;
      if(LucRamBlockCalCrc == LucRamBlockCrc)
      {
        LblRamCellTstResult = RAMTST_PASSED;
        /* Block Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_PASSED;
      }
      else
      {
        LblRamCellTstResult = RAMTST_FAILED;
        /* Block Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_FAILED;

        /* Global Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blGblBckGrdTstError = RAMTST_FAILED;

        /* If atleast one Cell fails the Block status changed to NOT_OK */
        *(RamTst_GaaBlkParam[LddBlockIdx].pTestBlockStatus) =
                                                      RAMTST_RESULT_NOT_OK;

        #if(RAMTST_DEMERROR_REPORT == STD_ON)
        /* Raise DEM Error and set the RamTst_GddTestStatus to Failed */
        Dem_ReportErrorStatus(RamTst_GusRamFailure, DEM_EVENT_STATUS_FAILED);
        #endif

        #if(RAMTST_TEST_ERROR_NOTIFICATION_SUPPORT == STD_ON)
        /* CallErrorNotification API */
        RAMTST_TEST_ERROR_NOTIFICATION();
        #endif
      }
    }

    #endif

    #if(RAMTST_CRC_8H2F_SUPPORT == STD_ON)
    LucRamBlockCalCrc = RamTst_CalculateCRC8H2F(LpAddress, LulRamBlockSize,
                  RamTst_GddBckGrdTstRamVar.ucCrcInitialVal, LblCrcIsFirstCall);

    RamTst_GddBckGrdTstRamVar.ucCrcInitialVal = LucRamBlockCalCrc;
    /* CRC calculated till this address */
    LpAddress = &LpAddress[LulRamBlockSize];

    /* Save the Next Address */
    RamTst_GddBckGrdTstRamVar.ulBckGrdAddress = (uint32)LpAddress;

    /* Block Finished Condition */
    if((uint32)LpAddress == RamTst_GaaBlkParam[LddBlockIdx].ulRamTstEndAddress)
    {
      /* fetch the CRC Calculated from the End of Block */
      LpEndAddress = (uint8*)RamTst_GaaBlkParam[LddBlockIdx].ulRamTstEndAddress;

      LucRamBlockCrc = *LpEndAddress;
      if(LucRamBlockCalCrc == LucRamBlockCrc)
      {
        LblRamCellTstResult = RAMTST_PASSED;
        /* Block Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_PASSED;
      }
      else
      {
        LblRamCellTstResult = RAMTST_FAILED;
        /* Block Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_FAILED;

        /* Global Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blGblBckGrdTstError = RAMTST_FAILED;

        /* If atleast one Cell fails the Block status changed to NOT_OK */
        *(RamTst_GaaBlkParam[LddBlockIdx].pTestBlockStatus) =
                                                      RAMTST_RESULT_NOT_OK;

        #if(RAMTST_DEMERROR_REPORT == STD_ON)
        /* Raise DEM Error and set the RamTst_GddTestStatus to Failed */
        Dem_ReportErrorStatus(RamTst_GusRamFailure, DEM_EVENT_STATUS_FAILED);
        #endif

        #if(RAMTST_TEST_ERROR_NOTIFICATION_SUPPORT == STD_ON)
        /* CallErrorNotification API */
        RAMTST_TEST_ERROR_NOTIFICATION();
        #endif
      }
    }

    #endif

    #if(RAMTST_CRC_16_SUPPORT == STD_ON)
    LusRamBlockCalCrc = RamTst_CalculateCRC16(LpAddress, LulRamBlockSize,
    RamTst_GddBckGrdTstRamVar.usCrcInitialVal, LblCrcIsFirstCall);
    RamTst_GddBckGrdTstRamVar.usCrcInitialVal = LusRamBlockCalCrc;
    /* CRC calculated till this address */
    LpAddress = &LpAddress[LulRamBlockSize];

    /* Save the Next Address */
    RamTst_GddBckGrdTstRamVar.ulBckGrdAddress = (uint32)LpAddress;
      /* Block Finished Condition */
    if((uint32)LpAddress == RamTst_GaaBlkParam[LddBlockIdx].ulRamTstEndAddress)
    {
      /* fetch the CRC Calculated from the End of Block */
      LpEndAddress = (uint16*)RamTst_GaaBlkParam[LddBlockIdx].ulRamTstEndAddress;

      LusRamBlockCrc = *LpEndAddress;
      if(LusRamBlockCalCrc == LusRamBlockCrc)
      {
        LblRamCellTstResult = RAMTST_PASSED;

        /* Block Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_PASSED;

      }
      else
      {
        LblRamCellTstResult = RAMTST_FAILED;
        /* Block Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_FAILED;

        /* Global Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blGblBckGrdTstError = RAMTST_FAILED;

        /* If atleast one Cell fails the Block status changed to NOT_OK */
        *(RamTst_GaaBlkParam[LddBlockIdx].pTestBlockStatus) =
                                                      RAMTST_RESULT_NOT_OK;

        #if(RAMTST_DEMERROR_REPORT == STD_ON)
        /* Raise DEM Error and set the RamTst_GddTestStatus to Failed */
        Dem_ReportErrorStatus(RamTst_GusRamFailure, DEM_EVENT_STATUS_FAILED);
        #endif

        #if(RAMTST_TEST_ERROR_NOTIFICATION_SUPPORT == STD_ON)
        /* CallErrorNotification API */
        RAMTST_TEST_ERROR_NOTIFICATION();
        #endif
      }
    }

    #endif

    #if(RAMTST_CRC_32_SUPPORT == STD_ON)
    LulRamBlockCalCrc = RamTst_CalculateCRC32(LpAddress, LulRamBlockSize,
    RamTst_GddBckGrdTstRamVar.ulCrcInitialVal, LblCrcIsFirstCall);
    RamTst_GddBckGrdTstRamVar.ulCrcInitialVal = LulRamBlockCalCrc;
    /* CRC calculated till this address */
    LpAddress = &LpAddress[LulRamBlockSize];

    /* Save the Next Address */
    RamTst_GddBckGrdTstRamVar.ulBckGrdAddress = (uint32)LpAddress;
      /* Block Finished Condition */
    if((uint32)LpAddress == RamTst_GaaBlkParam[LddBlockIdx].ulRamTstEndAddress)
    {
      /* fetch the CRC Calculated from the End of Block */
      LpEndAddress = (uint32*)RamTst_GaaBlkParam[LddBlockIdx].ulRamTstEndAddress;

      LulRamBlockCrc = *LpEndAddress;
      if(LulRamBlockCalCrc == LulRamBlockCrc)
      {
        LblRamCellTstResult = RAMTST_PASSED;
        /* Block Test Status is Passed */
        RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_PASSED;
      }
      else
      {
        LblRamCellTstResult = RAMTST_FAILED;

        /* Global Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blGblBckGrdTstError = RAMTST_FAILED;

        /* If atleast one Cell fails the Block status changed to NOT_OK */
        *(RamTst_GaaBlkParam[LddBlockIdx].pTestBlockStatus) =
                                                      RAMTST_RESULT_NOT_OK;
        /* Block Test Status is Failed */
        RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError = RAMTST_FAILED;
        #if(RAMTST_DEMERROR_REPORT == STD_ON)
        /* Raise DEM Error and set the RamTst_GddTestStatus to Failed */
        Dem_ReportErrorStatus(RamTst_GusRamFailure, DEM_EVENT_STATUS_FAILED);
        #endif

        #if(RAMTST_TEST_ERROR_NOTIFICATION_SUPPORT == STD_ON)
        /* CallErrorNotification API */
        RAMTST_TEST_ERROR_NOTIFICATION();
        #endif
      }
    }

    #endif
  }
  else
  {
    #if(RAMTST_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID,
    RAMTST_CRCBCKGRDTST_SID, RAMTST_E_STATUS_FAILURE);
    #endif
  } 

  return LblRamCellTstResult;
}
#endif

/*******************************************************************************
** Function Name        : RamTst_SetBlockResult                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal Function to set the block test status      **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy           : Non-Reentrant, Non-Interruptible                   **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The Ram Test module must be initialized             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                 RamTst_GddBckGrdTstRamVar  **
**                                                 RamTst_GaaBlkParam         **
**                        Function(s) invoked    :                            **
**                                                                            **
*******************************************************************************/
FUNC(void, RAMTST_CODE) RamTst_SetBlockResult(void)
{
  RamTst_NumberOfBlocksType LddBlkID;

  LddBlkID = RamTst_GddBckGrdTstRamVar.ddRunningBlockID - RAMTST_ONE;
  if (LddBlkID < RamTst_GulNumberOfBlocks)
  {
    if((RamTst_GddBckGrdTstRamVar.blBlkBckGrdTstError != RAMTST_FAILED) &&
    (*(RamTst_GaaBlkParam[LddBlkID].pTestBlockStatus) != RAMTST_RESULT_NOT_OK))
    {
      /* Set the Block Status to OK */
      *(RamTst_GaaBlkParam[LddBlkID].pTestBlockStatus) = RAMTST_RESULT_OK;
    }
    else
    {
      /* Set the Block Status to OK */
      *(RamTst_GaaBlkParam[LddBlkID].pTestBlockStatus) = RAMTST_RESULT_NOT_OK;
    }
  }
  else
  {
    #if(RAMTST_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID,
    RAMTST_SETBLOCKRESULT_SID, RAMTST_E_STATUS_FAILURE);
    #endif
  } 
}

/*******************************************************************************
** Function Name        : RamTst_SetOverAllResult                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal Function to set the over all test status   **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy           : Non-Reentrant, Non-Interruptible                   **
**                                                                            **
** Input Parameters     : RamTst_NumberOfBlocksType                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The Ram Test module must be initialized             **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                 RamTst_GddBckGrdTstRamVar  **
**                                                 RamTst_GaaBlkParam         **
**                                                 RamTst_GddTestStatus       **
**                        Function(s) invoked    : None                       **
**                                                                            **
*******************************************************************************/
FUNC(void, RAMTST_CODE) RamTst_SetOverAllResult
                                             (RamTst_NumberOfBlocksType BlockId)
{
  /* Restart from Starting of Block */
  RamTst_GddBckGrdTstRamVar.ddRunningBlockID = BlockId;

  /* Starting Block Size */
  RamTst_GddBckGrdTstRamVar.ddBalNumOfCells =
                      RamTst_GaaBlkParam[BlockId - RAMTST_ONE].ulRamBlockSize;
  RamTst_GddBckGrdTstRamVar.ulBckGrdAddress =
  RamTst_GaaBlkParam[BlockId - RAMTST_ONE].ulRamTstStartAddress;

  if(RamTst_GddBckGrdTstRamVar.blGblBckGrdTstError != RAMTST_FAILED)
  {
    #if(RAMTST_TEST_COMPLETED_NOTIFICATION_SUPPORT == STD_ON)
    /* If No error Indicated then Call Test Completed Notification */
    RAMTST_TEST_COMPLETED_NOTIFICATION();
    #endif
    RamTst_GddTestStatus = RAMTST_RESULT_OK;
  }
  else
  {
    /* If atleast one cell fails the overall result set to NOT_OK */
    RamTst_GddTestStatus = RAMTST_RESULT_NOT_OK;
  }
}

#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/*
polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation (uint8 data needs to be extracted from a uint32 address. the code is verified manually)
polyspace:end<RTE: NIV : Not a defect : Justify with annotations > Cannot initialize because of Application variable
polyspace:end<RTE: IDP : Not a defect : Justify with annotations > configured memory access index
*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
