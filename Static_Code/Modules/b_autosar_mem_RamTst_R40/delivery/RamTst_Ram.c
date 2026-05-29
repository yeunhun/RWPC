/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_Ram.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR RAMTST                                                **
**                                                                            **
**  PURPOSE   : Ram Test Global Variables declaration                         **
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
** 1.2.3     05-Oct-2013   CY Song          Correct Misra Rule Error          **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst_Ram.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/* polyspace-begin RTE:UNR [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:IDP [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:NIV [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "Not a defect" */
/* polyspace-begin VARIABLE:ALL [Not a defect:Low] "Not a defect" */

#define RAMTST_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if ((RAMTST_SUSPEND_API == STD_ON) || (RAMTST_STOP_API == STD_ON))
VAR(RamTst_TriggerStopOrSuspendType, RAMTST_VAR) RamTst_TriggerStopOrSuspend;
#endif

/* Global variable to store Initialization status of RAMTST */
VAR(RamTst_ExecutionStatusType, RAMTST_VAR) RamTst_GddExecuStatus;
/* Global variable to store Initialization status of RAMTST */
VAR(RamTst_TestResultType, RAMTST_VAR) RamTst_GddTestStatus;

/* Global variable to store Initialization status of RAMTST */
VAR(RamTst_TestResultType, RAMTST_VAR)
                                RamTst_GaaBlockStatus[RAMTST_MAX_BLOCKID];

/* Global variable to store latest  */
VAR(RamTst_AlgParamsIdType, RAMTST_VAR) RamTst_GddNewAlgParamsId;

/* Global variable to store latest  */
VAR(RamTst_AlgorithmType, RAMTST_VAR) RamTst_GddNewAlgType;

/* Global variable to store latest  */
VAR(RamTst_NumberOfTestedCellsType, RAMTST_VAR)
                                                       RamTst_GddNumOfTstCells;

/* Global variable to store Initialization status of RAMTST */
VAR(RamTst_BckGrdCrcRamVar, RAMTST_VAR)
                                                      RamTst_GddBckGrdTstRamVar;
#define RAMTST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define RAMTST_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global variable to calculate CRC */
VAR(uint8, RAMTST_VAR) RamTst_GucMsb;
VAR(uint8, RAMTST_VAR) RamTst_GucMidHi;
VAR(uint8, RAMTST_VAR) RamTst_GucMidLow;
VAR(uint8, RAMTST_VAR) RamTst_GucLsb;
VAR(uint8, RAMTST_VAR) RamTst_GucPM_Count;
#define RAMTST_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* polyspace-end RTE:UNR [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:IDP [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:NIV [Not a defect:Low] "Not a defect" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "Not a defect" */
/* polyspace-end VARIABLE:ALL [Not a defect:Low] "Not a defect" */
/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
