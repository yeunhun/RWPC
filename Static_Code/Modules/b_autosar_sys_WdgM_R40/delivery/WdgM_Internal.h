/*******************************************************************************
**                                                                            **
**  (C) 2015 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: WdgM_Internal.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : Provision of Prototypes of WdgM module internal functions     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.2.13    04-Dec-2018   YH.Han       Redmine #14965                        **
** 1.0.9     02-Sep-2015   Sinil        1. Fix Misra-c rule violations 16.4   **
** 1.0.8     20-Aug-2015   Sinil        1. Follow function prototype argument **
**                                      naming rule                           **
** 1.0.7     21-Oct-2014   Sinil        1. Add WdgM_PerformAliveIndication and**
**                                      WdgM_EvaluateLocalStatus              **
**                                      2. Change including                   **
**                                      3. Rearrange items and change naming  **
** 1.0.3     07-Oct-2014   Sinil        1. Change WdgM_TriggerWdgIf argument  **
** 1.0.2     30-Sep-2014   Sinil        1. Remove Wdgm_PerformTimeStamping    **
** 1.0.1     28-May-2013   Sinil        The second argument of                **
**                                        WdgM_SEIndexBinarySearch func is    **
**                                        changed from                        **
**                                        WdgM_SupervisedEntityIdType to      **
**                                        WdgM_SupervisedEntityIndexType      **
**                                      WdgM_TriggerWdgIf func is revised     **
**                                        to use triggers of delivered        **
**                                        LpMode and to separate cases for    **
**                                        normal mode and timeout mode        **
**                                        DL_ID:119                           **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a Defect] "see MEMMAP003 of AUTOSAR" */

#ifndef WDGM_INTERNAL_H
#define WDGM_INTERNAL_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM_Cfg.h"
#include "WdgM_PCTypes.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define WDGM_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Not a Defect] "below macro does not affect the result" */
extern FUNC(P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST), WDGM_CODE)
  WdgM_SEIDBinarySearch(WdgM_SupervisedEntityIdType ddSEID);
/* polyspace-end MISRA-C3:20.7 */
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

#define WDGM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, WDGM_CODE) WdgM_SEIndexBinarySearch(
  WdgM_SupervisedEntityIdType ddSEID,
  P2VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC, WDGM_DATA) pSEIndex);
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

#define WDGM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, WDGM_CODE) WdgM_InternalSetMode(WdgM_ModeType ddMode);
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

#define WDGM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_TriggerWdgIf(
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) pMode,
  WdgM_TriggerModeType ddTriggerMode);
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

#define WDGM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_ClearActivityFlag(
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) pCurrentMode);
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

#if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
#define WDGM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_PerformAliveIndication(
  WdgM_SupervisedEntityIdType ddSEID, WdgM_CheckpointIdType ddCheckpointID);
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

#define WDGM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_PerformAliveSupervision(void);
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
#define WDGM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_PerformDeadlineSupervision(
  WdgM_SupervisedEntityIdType ddSEID, WdgM_CheckpointIdType ddCheckpointID,
  WdgM_SupervisedEntityIndexType ddSEArrayIndex);
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_PerformIntLogicalSupervision(
  WdgM_CheckpointIdType ddCheckpointID,
  WdgM_SupervisedEntityIndexType ddSEArrayIndex);
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_PerformExtLogicalSupervision(
  WdgM_SupervisedEntityIdType ddSEID, WdgM_CheckpointIdType ddCheckpointID,
  WdgM_SupervisedEntityIndexType ddSEArrayIndex);
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define WDGM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_EvaluateLocalStatus(
  P2VAR(boolean, AUTOMATIC, WDGM_DATA) pSEFailedFlag,
  P2VAR(boolean, AUTOMATIC, WDGM_DATA) pSEExpiredFlag);
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

#define WDGM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDGM_CODE) WdgM_EvaluateGlobalStatus(
  boolean blSEFailedFlag, boolean blSEExpiredFlag);
#define WDGM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* WDGM_INTERNAL_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
