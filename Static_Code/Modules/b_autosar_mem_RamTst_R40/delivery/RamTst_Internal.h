/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_Internal.h                                             **
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
** 1.3.2     30-Dec-2020   CY Song          RedMine #27378                    **
** 1.2.5     16-May-2016   CY Song    RedMine #4902                           **
** 1.2.4     05-Oct-2013   CY Song    Correct Misra Rule Error                **
** 1.0.4     17-Oct-2014   CY Song    Rd#1452 Correct PolySpace               **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/
#ifndef RAMTST_INTERNAL_H
#define RAMTST_INTERNAL_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if(RAMTST_LOW_COVERAGE_TEST_SELECTED == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, RAMTST_CODE)
                RamTst_RunParityBitTst(RamTst_NumberOfBlocksType RamTstBlockId);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_HIGH_COVERAGE_TEST_SELECTED == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, RAMTST_CODE)
                      RamTst_RunCrcTst(RamTst_NumberOfBlocksType RamTstBlockId);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_MEDIUM_COVERAGE_TEST_SELECTED == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, RAMTST_CODE)
                  RamTst_RunPatternChk(RamTst_NumberOfBlocksType RamTstBlockId);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_LOW_COVERAGE_TEST_SELECTED == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, RAMTST_CODE)
                             RamTst_ParityBitBckGrdTst(uint32 RamTstStrtAddress,
                               RamTst_NumberOfTestedCellsType RamTstNumOfCells);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_MEDIUM_COVERAGE_TEST_SELECTED == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, RAMTST_CODE)
                            RamTst_PatternChkBckGrdTst(uint32 RamTstStrtAddress,
                               RamTst_NumberOfTestedCellsType RamTstNumOfCells);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif


#if(RAMTST_HIGH_COVERAGE_TEST_SELECTED == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, RAMTST_CODE) RamTst_CrcBckGrdTst(uint32 RamTstStrtAddress,
                              RamTst_NumberOfTestedCellsType RamTstNumOfCells);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, RAMTST_CODE) RamTst_SetBlockResult(void);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"

#define RAMTST_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, RAMTST_CODE)
                     RamTst_SetOverAllResult(RamTst_NumberOfBlocksType BlockId);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */

#endif /* RAMTST_INTERNAL_H */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
