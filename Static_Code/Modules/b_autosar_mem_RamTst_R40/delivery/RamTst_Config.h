/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_Config.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR RAMTST                                                **
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
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/
#ifndef RAMTST_CONFIG_H_
#define RAMTST_CONFIG_H_
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst_Cfg.h"
#if(RAMTST_DEMERROR_REPORT == STD_ON)
#include "RamTst_Dem_Cfg.h"
#endif

/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define RAMTST_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


extern const uint8  RamTst_GucNumberOfAlgParaSets;
extern const uint8  RamTst_GucDefaultAlgParaID;
extern const uint8  RamTst_GucCellSize;
extern const uint32 RamTst_GulNumberOfBlocks;
extern const uint32 RamTst_GulMinNumberOfTestedCells;
extern const uint16 RamTst_GusMaxBlockId;

#if(RAMTST_DEMERROR_REPORT == STD_ON)
extern const uint16 RamTst_GusRamFailure;
#endif

#define RAMTST_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] "It is implemented according to autosar specification" */

#endif /* ECUM_CONFIG_H_ */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
