/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Syst_Cfg.h                                                    **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Configuration file for Syst.c                                 **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision    Date          By           Description                         **
********************************************************************************
** 1.1.0.0     23-Feb-2021   JHLim        Redmine #23964                      **
** 1.0.0       10-April-2020 JaeHyun      Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:8.6 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef SYST_CFG_H
#define SYST_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Btl_LinkerSymbols.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define SYST_BUFF_SIZE_ONE                                                    1U

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
/* Do not add memory placement tags here, these symbols are
 * referred from[and allocated by] linker, Placement is taken care
 * by linker
 */
extern uint32 Syst_Gau32_BTLResetSaveData[SYST_BUFF_SIZE_ONE];
extern uint32 *Syst_Gpu32_BTLResetSaveDataSize;
extern uint32 Syst_Gau32_BTL_APPLResetSaveData[SYST_BUFF_SIZE_ONE];
extern uint32 *Syst_Gpu32_BTL_APPLResetSaveDataSize;

#endif /* SYST_CFG_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:8.6 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
