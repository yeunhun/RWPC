/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_PCTypes.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR RamTst                                                **
**                                                                            **
**  PURPOSE   : Provision of pre-compile time parameters                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By     Description                                 **
********************************************************************************
** 1.2.5     16-May-2016   CY Song          RedMine #4902                     **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/

#ifndef RAMTST_PCTYPES_H
#define RAMTST_PCTYPES_H
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.4 [Justified:Low] "Not a defect" */
/*
  polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations> No Impact of this rule violation
*/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComStack_Types.h"
#include "RamTst_Types.h"

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] "Not a defect" */

/* Structure for configuring an algorithm */
typedef struct STag_RamTst_AlgParams
{

  /* Coverage of the defined RamTstAlgParams set */
  RamTst_AlgorithmType  ddRamTstAlgCoverage;

  /* Absolute maximum value for the number of cells that
   * NUMBER_OF_TESTED_CELLS and MAX_NUMBER_OF_TESTED_CELLS can be.
   */
  uint32 ulRamTstExtNumberOfTestedCells;

  /* maximum value for the number of cells that can be tested in one
   * cycle of a background test.
   */
  uint32 ulRamTstMaxNumberOfTestedCells;

  /* Initial value for a RAM variable, which can be changed by the function
   * "RamTst_ChangeNumberOfTestedCells"
   */
  uint32 ulRamTstNumberOfTestedCells;

  /* Number of RAM blocks configured */
  /* calculationFormula = Count of RamTstBlockParams contained in this
   * RamTstAlgParams container
   */
  uint16 usRamTstNumberOfBlocks;

  /* Index to the start of RamTest Blocks */
  uint16 usRamTstBlkIndex;

  /* Test Algorithm Parameter ID */
  uint8 ucRamTstAlgParamsId;

}RamTst_AlgParams;

/* Structure for block of RAM */
typedef struct STag_RamTst_BlockParams
{
  /* Pointer to Ram block status variable */
  P2VAR(RamTst_TestResultType, AUTOMATIC, RAMTST_CONFIG_DATA) pTestBlockStatus;

  /* Policy regarding destruction or non-destruction of memory content */
  RamTstTestPolicy ddRamTstPolicy;

  /* Block Start Address */
  uint32 ulRamTstStartAddress;

  /* Block End Address */
  uint32 ulRamTstEndAddress;

  /* Size of the Block  */
  /* (ulRamTstEndAddress - ulRamTstStartAddress)/Ram Cell Size */
  uint32 ulRamBlockSize;

  /* Pattern to be filled into each memory cell after
   * destructive test of this block
   */
  /* Applicable only if destructive Mode is ON */
  uint32 ulRamTstFillPattern;

  /* ID of the RAM block */
  uint16 usRamTstBlockId;

}RamTst_BlockParams;

/* Structure for configuring an algorithm */
typedef struct STag_RamTst_BckGrdCrcRamVar
{
  /* Current BlockID */
  RamTst_NumberOfBlocksType ddRunningBlockID;

  /* Pending Number of Cells to be tested */
  RamTst_NumberOfTestedCellsType ddBalNumOfCells;

  /* Address Location from which the testing should continued */
  uint32 ulBckGrdAddress;

  /* Error Flag */
  boolean blBlkBckGrdTstError;

  /* Error Flag */
  boolean blGblBckGrdTstError;

  #if(RAMTST_HIGH_COVERAGE_TEST_SELECTED == STD_ON)

  #if((RAMTST_CRC_8_SUPPORT == STD_ON) || (RAMTST_CRC_8H2F_SUPPORT == STD_ON))
  uint8 ucCrcInitialVal;
  #endif

  #if(RAMTST_CRC_16_SUPPORT == STD_ON)
  uint16 usCrcInitialVal;
  #endif

  #if(RAMTST_CRC_32_SUPPORT == STD_ON)
  uint32 ulCrcInitialVal;
  #endif

  #endif

}RamTst_BckGrdCrcRamVar;

#define RAMTST_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array for Blocks */
extern CONST(RamTst_BlockParams, RAMTST_CONST)
                                        RamTst_GaaBlkParam[];
#define RAMTST_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define RAMTST_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array for Algorithm Parameter */
extern CONST(RamTst_AlgParams, RAMTST_CONST)
                            RamTst_GaaAlgParam[];
#define RAMTST_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/*
  polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> No Impact of this rule violation
*/
/* polyspace-end MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.4 [Justified:Low] "Not a defect" */

#endif /* RAMTST_PCTYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
