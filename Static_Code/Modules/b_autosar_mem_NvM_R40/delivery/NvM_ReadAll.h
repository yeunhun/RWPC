/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_ReadAll.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Provision of NVRAM Manager ReadAll functions.                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date           By          Description                         **
********************************************************************************
** 1.3.2       10-Oct-2016   Song CY      Redmine #6215                       **
** 1.1.6       03-Mar-2015  Song CY       As per RedMine 2216, Remove version **
**                                        Information                         **
** 1.1.4       02-Dec-2014  Song CY       RedMine 1719, Update for PolySpace  **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/
/*
polyspace-begin MISRA-C3:1.1:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard-NvM SWS Chap 5.1.2)
polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/

#ifndef NVM_READALL_H
#define NVM_READALL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

#if(NVM_TOTAL_NUM_OF_READALL_BLOCKS > 0)
extern FUNC(void, NVM_CODE) NvM_ProcessReadAllBlocks(void);
#endif

extern FUNC(void, NVM_CODE) NvM_CheckConfigId(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* NVM_READALL_H */

/*
polyspace-end MISRA-C3:1.1:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard-NvM SWS Chap 5.1.2)
polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
