/*******************************************************************************
**                                                                            **
**  (C) 2013-2016 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Task.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_Task.c file containing the declaration     **
**              of Task functionality related functions.                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 2.6.7     04-Nov-2020    JH.Cho        Redmine #25772                      **
** 2.6.6     14-Aug-2020    JH.Cho        Redmine #25095                      **
** 2.0.13    30-Jun-2016    MJ.Woo        Redmine #5368                       **
** 2.0.11    16-Feb-2016    JH.Lee,MJ.Woo Redmine #3963                       **
** 2.0.9     10-Dec-2014    MJ.Woo        Redmine #1189                       **
** 2.0.4     23-Oct-2013    DG.Lee        CR: xar~179, TASK: xar~736          **
** 2.0.2     19-Aug-2013    SH.Yoo        CR: xar~168, TASK: xar~675          **
** 2.0.0     22-Jul-2013    JH.Son,SH.Yoo CR: xar~107, TASK: xar~543          **
**                          DG.Lee,MJ.Woo                                     **
** 1.0.0     10-Jan-2013    JH.Son,SH.Yoo Initial version                     **
**                          DG.Lee,MJ.Woo                                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> see MEMMAP003 of AUTOSAR */

#ifndef OS_TASK_H
#define OS_TASK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Types.h"             /* Type definition of OS */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (OS_TASK == STD_ON)

#define OS_START_SEC_CODE
#include "MemMap.h"
extern StatusType Os_DoActivateTask(TaskType TaskID, boolean LblRemoteCall);

extern FUNC(StatusType, OS_CODE) Os_ActivateTaskService(P2CONST
                         (Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask);
#define OS_STOP_SEC_CODE
#include "MemMap.h"

#define OS_USERIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, OS_CODE) Os_ErrorTerminateTask(void);
#define OS_USERIF_STOP_SEC_CODE
#include "MemMap.h"

/* Macro for getting the TaskID */
/* polyspace<MISRA-C:19.7:Not a defect:Justify with annotations> Function like macro is used to improve performance */
#define OS_PROCURE_TASK_ID(TaskID)     (Os_GetTaskID(TaskID))
#endif /* #if(OS_TASK == STD_ON) */

#endif /* OS_TASK_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C3:20.1> */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
