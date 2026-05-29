/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_Config.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR RamTst                                                **
**                                                                            **
**  PURPOSE   : Provides Variable for upper layers                            **
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
** 1.2.5     16-May-2016   CY Song          RedMine #4902                     **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst_Cfg.h"
#include "RamTst_Config.h"

/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/* polyspace-begin RTE:UNR [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:IDP [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:NIV [Not a defect:Low] "Not a defect" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "Not a defect" */
/* polyspace-begin VARIABLE:ALL [Not a defect:Low] "Not a defect" */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define RAMTST_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

const uint8  RamTst_GucNumberOfAlgParaSets     = RAMTST_NUMBER_OF_ALG_PARAM_SETS;
const uint8  RamTst_GucDefaultAlgParaID        = RAMTST_DEFAULT_ALG_PARAMS_ID;
const uint8  RamTst_GucCellSize                = RAMTST_CELL_SIZE;
const uint16 RamTst_GusMaxBlockId              = RAMTST_MAX_BLOCKID;
#if(RAMTST_DEMERROR_REPORT == STD_ON)
const uint16 RamTst_GusRamFailure              = RAMTST_E_RAM_FAILURE;
#endif
const uint32 RamTst_GulNumberOfBlocks          = RAMTST_NUMBER_OF_BLOCKS;
const uint32 RamTst_GulMinNumberOfTestedCells  = RAMTST_MIN_NUMBER_OF_TESTED_CELLS;

#define RAMTST_STOP_SEC_CONST_UNSPECIFIED
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
