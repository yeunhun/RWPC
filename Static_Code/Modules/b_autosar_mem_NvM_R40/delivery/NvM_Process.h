/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_Process.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Provision of NVRAM Manager common functions.                  **
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
** 1.3.6       11-Sep-2017   Yun YJ       Redmine #9669                       **
** 1.1.7       09-Jul-2015  Song CY       As per RedMine 2265, Change         **
**                                        CRC & SID Logic                     **
** 1.1.6       03-Mar-2015  Song CY       As per RedMine 2216, Remove version **
**                                        Information                         **
** 1.1.4       02-Dec-2014  Song CY       RedMine 1719, Update for PolySpace  **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/

#ifndef NVM_PROCESS_H
#define NVM_PROCESS_H

/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM_Ram.h"
#include "NvM_Write.h"
#include "SchM_NvM.h" 
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"
/* NvM_CalcBlkNumber Prototype Declarations */
extern FUNC(uint16, NVM_CODE) NvM_CalcBlkNumber(void);
/* NvM_EndProcessBlock Prototype Declarations */
extern FUNC(void, NVM_CODE) NvM_EndProcessBlock
  (NvM_RequestResultType RequestResult);
/* NvM_UpdateGlobalVars Prototype Declarations */
extern FUNC(void, NVM_CODE) NvM_UpdateGlobalVars(void);

#if((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && \
  (NVM_RAM_BLOCK_DATA_ADDRESS == STD_ON))
/* NvM_UpdateRamStateStatus Prototype Declarations */
extern FUNC(void, NVM_CODE) NvM_UpdateRamStateStatus(uint8 Status);
#endif

#if(NVM_BLOCK_USE_SYNC_MECHANISM == STD_ON)
extern FUNC(uint8, NVM_CODE) NvM_QueueSwap
(uint8 QueStartPos, uint8 QueEnDis,
  P2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA)LpQueueBuffer);
#endif
 
#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */

#endif /* NVM_PROCESS_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
