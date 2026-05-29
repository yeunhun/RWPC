/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_ScanQueue.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Provision of NVRAM Manager queue functions.                   **
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
** 1.3.0       25-Jul-2016   Song CY      Redmine #5383                       **
** 1.1.6       03-Mar-2015  Song CY       As per RedMine 2216, Remove version **
**                                        Information                         **
** 1.1.4       02-Dec-2014  Song CY       RedMine 1719, Update for PolySpace  **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/

#ifndef NVM_SCANQUEUE_H
#define NVM_SCANQUEUE_H
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                     Function Prototypes                                    **
*******************************************************************************/
#if (NVM_API_CONFIG_CLASS  !=  NVM_API_CONFIG_CLASS_1)

extern FUNC(boolean, NVM_CODE) NvM_ScanQueue(void);

extern FUNC(Std_ReturnType, NVM_CODE) NvM_StdQueueWrite(
  CONSTP2CONST(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) LpDataPtr);

extern FUNC(Std_ReturnType, NVM_CODE) NvM_StdQueueCancel(NvM_BlockIdType
  BlockId);

extern FUNC(void, NVM_CODE) NvM_StdQueuePosClear(NvM_BlockIdType
  BlockId);

#endif

#if((NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) && \
 (NVM_JOB_PRIORITIZATION == STD_ON) && (NVM_IMM_JOB_PRIORITY == STD_ON))

extern FUNC(Std_ReturnType, NVM_CODE) NvM_ImmQueueCancel(NvM_BlockIdType
  BlockId);

extern FUNC(NvM_JobQueuePtrType, NVM_CODE)
  NvM_ImmQueueRead(void);

extern FUNC(Std_ReturnType, NVM_CODE) NvM_ImmQueueWrite(
  CONSTP2CONST(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) LpDataPtr);

extern FUNC(void, NVM_CODE) NvM_ImmQueuePosClear(NvM_BlockIdType
  BlockId);

#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */
#endif /* NVM_SCANQUEUE_H */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
