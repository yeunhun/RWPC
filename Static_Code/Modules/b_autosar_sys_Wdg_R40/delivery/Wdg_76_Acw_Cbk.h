/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Wdg_76_Acw_Cbk.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTRON CUSTOM WDG                                     **
**                                                                            **
**  PURPOSE   : Autron Custom Watchdog GPT callback function declaration      **
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
** 1.8.2.0   18-Oct-2021   YH.Han       Redmine #32698                        **
** 1.0.1     28-Apr-2016   Sinil        Redmine #4744                         **
** 1.0.0     02-Feb-2015   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a Defect] "see MEMMAP003 of AUTOSAR" */

#ifndef WDG_76_ACW_CBK_H
#define WDG_76_ACW_CBK_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw.h"

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_CODE) WDG_76_ACW_GPT_CBK(void);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */

#endif /* WDG_76_ACW_CBK_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
