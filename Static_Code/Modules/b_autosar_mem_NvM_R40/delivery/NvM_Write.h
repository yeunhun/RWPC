/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_Write.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Provision of NVRAM Manager Write functions.                   **
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
** 1.3.0       25-Jul-2016   Song CY      Redmine #3883                       **
** 1.1.7       09-Jul-2015   Song CY      Correct MISRA-Rule Violation        **
** 1.1.6       03-Mar-2015  Song CY       As per RedMine 2216, Remove version **
**                                        Information                         **
** 1.1.4       02-Dec-2014  Song CY       RedMine 1719, Update for PolySpace  **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/
/*
polyspace-begin MISRA-C3:1.1:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard-NvM SWS Chap 5.1.2)
polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/

#ifndef NVM_WRITE_H
#define NVM_WRITE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, NVM_CODE) NvM_ProcessWriteBlock(void);
#if(NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS > 0)
extern FUNC(void, NVM_CODE) NvM_ProcessWriteAllBlocks(void);
#endif

#if((NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1) && \
    (NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))
extern FUNC(void, NVM_CODE) NvM_ProcessImmdWrite(void);
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* NVM_WRITE_H */

/*
polyspace-end MISRA-C3:1.1:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard-NvM SWS Chap 5.1.2)
polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification"
*/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
