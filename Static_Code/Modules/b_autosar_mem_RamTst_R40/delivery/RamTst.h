/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst.h                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR RAMTST                                                **
**                                                                            **
**  PURPOSE   : This file provides declarations of APIs and SIDs              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.2     30-Dec-2020   CY Song          RedMine #27378                    **
** 1.2.7     15-Nov-2015   CY Song          Redmine #6608                     **
** 1.2.3     05-Oct-2015   CY Song          Add Service ID                    **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/

#ifndef RAMTST_H
#define RAMTST_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Std_Types.h"
#include "RamTst_Types.h"
#include "RamTst_Cfg.h"
#include "RamTst_PCTypes.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/* Instance ID */
#define RAMTST_INSTANCE_ID                      0x00
/* Service ID for RamTst_Init */
#define RAMTST_INIT_SID                         0x00
/* Service ID for RamTst_DeInit */
#define RAMTST_DEINIT_SID                       0x0C
/* Service ID for RamTst_Stop */
#define RAMTST_STOP_SID                         0x02
/* Service ID for RamTst_Allow */
#define RAMTST_ALLOW_SID                        0x03
/* Service ID for RamTst_Suspend */
#define RAMTST_SUSPEND_SID                      0x0D
/* Service ID for RamTst_Resume */
#define RAMTST_RESUME_SID                       0x0E
/* Service ID for RamTst_GetExecutionStatus */
#define RAMTST_GETEXECUTIONSTATUS_SID           0x04
/* Service ID for RamTst_GetTestResult */
#define RAMTST_GETTESTRESULT_SID                0x05
/* Service ID for RamTst_GetTestResultPerBlock */
#define RAMTST_GETTESTRESULTPERBLOCK_SID        0x06
/* Service ID for RamTst_GetVersionInfo */
#define RAMTST_GETVERSIONINFO_SID               0x0A
/* Service ID for RamTst_GetAlgParams */
#define RAMTST_GETALGPARAMS_SID                 0x12
/* Service ID for RamTst_GetTestAlgorithm */
#define RAMTST_GETTESTALGORITHM_SID             0x07
/* Service ID for RamTst_GetNumberOfTestedCells */
#define RAMTST_GETNUMBEROFTESTEDCELLS_SID       0x09
/* Service ID for RamTst_SelectAlgParams */
#define RAMTST_SELECTALGPARAMS_SID              0x0B
/* Service ID for RamTst_ChangeNumberOfTestedCells */
#define RAMTST_CHANGENUMBEROFTESTEDCELLS_SID    0x08
/* Service ID for RamTst_RunFullTest */
#define RAMTST_RUNFULLTEST_SID                  0x10
/* Service ID for RamTst_RunPartialTest */
#define RAMTST_RUNPARTIALTEST_SID               0x11
/* Service ID for RamTst_MainFunction */
#define RAMTST_MAINFUNCTION_SID                 0x01

/* Service ID for RamTst_RunParityBitTst */
#define RAMTST_RUNPARITYBITTST_SID              0xF0U
/* Service ID for RamTst_PatternChkBckGrdTst */
#define RAMTST_PATTERNCHKBCKGRDTST_SID          0xF1U
/* Service ID for RamTst_RunPatternChk */
#define RAMTST_RUNPATTERNCHK_SID                0xF2U
/* Service ID for RamTst_RunCrcTst */
#define RAMTST_RUNCRCTST_SID                    0xF3U
/* Service ID for RamTst_CrcBckGrdTst */
#define RAMTST_CRCBCKGRDTST_SID                 0xF4U
/* Service ID for RamTst_SetBlockResult */
#define RAMTST_SETBLOCKRESULT_SID               0xF5U

/* Prevent to enter lowPower Mode */
#define RAMTST_LOWPOWER_PREVENT                 (0x00U)
/* Allow to enter lowPower Mode */
#define RAMTST_LOWPOWER_ALLOW                   (0x01U)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#if(RAMTST_GET_VERSION_INFO_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_GetVersionInfo API */
extern FUNC(void, RAMTST_CODE) RamTst_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, RAMTST_APPL_DATA)versioninfo);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define RAMTST_START_SEC_CODE
#include "MemMap.h"

/* Extern for RamTst_Init API */
extern FUNC(void, RAMTST_CODE) RamTst_Init(void);

/* Extern for RamTst_DeInit API */
extern FUNC(void, RAMTST_CODE) RamTst_DeInit(void);

#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"

#if(RAMTST_STOP_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_Stop API */
extern FUNC(void, RAMTST_CODE) RamTst_Stop(void);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_GET_NUMBER_OF_TESTED_CELLS_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_Stop API */
extern FUNC(RamTst_NumberOfTestedCellsType, RAMTST_CODE)
                                            RamTst_GetNumberOfTestedCells(void);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_ALLOW_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_Allow API */
extern FUNC(void, RAMTST_CODE) RamTst_Allow(void);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_SUSPEND_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_Suspend API */
extern FUNC(void, RAMTST_CODE) RamTst_Suspend(void);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_RESUME_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_Resume API */
extern FUNC(void, RAMTST_CODE) RamTst_Resume(void);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_GET_EXECUTION_STATUS_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_GetExecutionStatus API */
extern FUNC(RamTst_ExecutionStatusType, RAMTST_CODE)
                                                RamTst_GetExecutionStatus(void);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_GET_TEST_RESULT_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_GetTestResult API */
extern FUNC(RamTst_TestResultType, RAMTST_CODE) RamTst_GetTestResult(void);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_GET_TEST_RESULT_PER_BLOCK_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_GetTestResultPerBlock API */
extern FUNC(RamTst_TestResultType, RAMTST_CODE) RamTst_GetTestResultPerBlock(
                                             RamTst_NumberOfBlocksType BlockId);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_GET_ALG_PARAMS_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_GetAlgParams API */
extern FUNC(RamTst_AlgParamsIdType, RAMTST_CODE) RamTst_GetAlgParams(void);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_GET_TEST_ALGORITHM_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_GetTestAlgorithm API */
extern FUNC(RamTst_AlgorithmType, RAMTST_CODE) RamTst_GetTestAlgorithm(void);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_SELECT_ALG_PARAMS_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_SelectAlgParams API */
extern FUNC(void, RAMTST_CODE) RamTst_SelectAlgParams(
                                        RamTst_AlgParamsIdType NewAlgParamsId);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_CHANGE_NUMBER_OF_TESTED_CELLS_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_ChangeNumberOfTestedCells API */
extern FUNC(void, RAMTST_CODE) RamTst_ChangeNumberOfTestedCells(
                  RamTst_NumberOfTestedCellsType NewNumberOfTestedCells);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_RUN_FULL_TEST_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_RunFullTest API */
extern FUNC(void, RAMTST_CODE) RamTst_RunFullTest(void);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(RAMTST_RUN_PARTIAL_TEST_API == STD_ON)
#define RAMTST_START_SEC_CODE
#include "MemMap.h"
/* Extern for RamTst_RunPartialTest API */
extern FUNC(void, RAMTST_CODE) RamTst_RunPartialTest(
                                          RamTst_NumberOfBlocksType BlockId);
#define RAMTST_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* polyspace-end MISRA-C3:2.5 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */

#endif /* RAMTST_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
