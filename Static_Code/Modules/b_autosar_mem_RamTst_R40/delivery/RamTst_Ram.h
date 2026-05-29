/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_Ram.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR RAMTST                                                **
**                                                                            **
**  PURPOSE   : Header file of RamTst_Ram.c                                   **
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
** 1.2.7     15-Nov-2015   CY Song          Redmine #6608                     **
** 1.2.5     16-May-2016   CY Song          RedMine #4902                     **
** 1.2.3     05-Oct-2015   CY Song          Correct Misra Rule Error          **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/
#ifndef RAMTST_RAM_H
#define RAMTST_RAM_H
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
  polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations> No Impact of this rule violation
*/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst_PCTypes.h"  /* Ram Test Module Pre-compile Types Header File */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define RAMTST_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if ((RAMTST_SUSPEND_API == STD_ON) || (RAMTST_STOP_API == STD_ON))
extern VAR(RamTst_TriggerStopOrSuspendType, RAMTST_VAR) RamTst_TriggerStopOrSuspend;
#endif

/* Global variable to store Initialization status of RAMTST */
extern VAR(RamTst_ExecutionStatusType, RAMTST_VAR)
                                                          RamTst_GddExecuStatus;

/* Global variable to store Initialization status of RAMTST */
extern VAR(RamTst_TestResultType, RAMTST_VAR)
                                                          RamTst_GddTestStatus;

/* Global variable to store Initialization status of RAMTST */
extern VAR(RamTst_TestResultType, RAMTST_VAR)
                                RamTst_GaaBlockStatus[];

/* Global variable to store latest  */
extern VAR(RamTst_AlgParamsIdType, RAMTST_VAR)
                                                       RamTst_GddNewAlgParamsId;
/* Global variable to store latest  */
extern VAR(RamTst_AlgorithmType, RAMTST_VAR) RamTst_GddNewAlgType;

/* Global variable to store latest  */
extern VAR(RamTst_NumberOfTestedCellsType, RAMTST_VAR)
                                                        RamTst_GddNumOfTstCells;

/* Global variable to store Initialization status of RAMTST */
extern VAR(RamTst_BckGrdCrcRamVar, RAMTST_VAR)
                                                      RamTst_GddBckGrdTstRamVar;
#define RAMTST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define RAMTST_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global variable to calculate CRC */
extern VAR(uint8, RAMTST_VAR) RamTst_GucMsb;
extern VAR(uint8, RAMTST_VAR) RamTst_GucMidHi;
extern VAR(uint8, RAMTST_VAR) RamTst_GucMidLow;
extern VAR(uint8, RAMTST_VAR) RamTst_GucLsb;
extern VAR(uint8, RAMTST_VAR) RamTst_GucPM_Count;
#define RAMTST_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/*
  polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> No Impact of this rule violation
*/

#endif /* RAMTST_RAM_H */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
