/*******************************************************************************
**                                                                            **
**  (C) 2013-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Multicore.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_Multicore.c file containing the declaration**
**              of Multicore functionality related functions.                 **
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
** 2.6.3     04-Jun-2020    MJ.Woo        Redmine #21784                      **
** 2.6.1     06-Mar-2020    MJ.Woo        Redmine #22246                      **
** 2.4.3     22-Mar-2018    SH.Yoo        Redmine #12025                      **
** 2.4.2     13-Mar-2018    MJ.Woo        Redmine #10875(Fix MISRA rule)      **
** 2.0.13    30-Jun-2016    MJ.Woo        Redmine #5368                       **
** 2.0.4     23-Oct-2013    DG.Lee        CR: xar~179, TASK: xar~736          **
** 2.0.0     22-Jul-2013    JH.Son,SH.Yoo CR: xar~107, TASK: xar~543          **
**                          DG.Lee,MJ.Woo                                     **
** 1.0.0     26-Mar-2013    Son           Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> see MEMMAP003 of AUTOSAR */

#ifndef OS_MULTICORE_H_
#define OS_MULTICORE_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*
 * @def OS_CORE_ID
 *
 * This is a ID of a Core
 */
#if (OS_MULTICORE == STD_ON)
/* polyspace<MISRA-C:19.4:Not a defect:Justify with annotations> Definition for function redirection does not use parenthesised expression */
/* polyspace<MISRA-C3:5.4:Not a defect:Justify with annotations> Definition for function redirection does not use parenthesised expression */
#define OS_CORE_ID                     LddCoreId
#else
#define OS_CORE_ID                     (OS_CORE_ID_MASTER)
#endif

#define OS_SPIN_LOCK_ZERO              (SpinlockIdType)0u

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define OS_START_SEC_CODE
#include "MemMap.h"

#if (OS_MULTICORE == STD_ON)
extern FUNC(void, OS_CODE) Os_TryToGetSpinlock
       (SpinlockIdType SpinlockId, boolean* Success);

extern FUNC(void, OS_CODE) Os_GetSpinlock(SpinlockIdType SpinlockId);

extern FUNC(void, OS_CODE) Os_ReleaseSpinlock(SpinlockIdType SpinlockId);

extern FUNC(void, OS_CODE) Os_StartCore(CoreIdType CoreID);

extern FUNC(void, OS_CODE) Os_SetSyncFirst(void);

extern FUNC(void, OS_CODE) Os_SetSyncSecond(void);

extern FUNC(void, OS_CODE) Os_SetSyncCountShutDown(void);

extern FUNC(void, OS_CODE) Os_WaitSyncShutDown(void);

extern FUNC(CoreIdType, OS_CODE) Os_KernGetCoreID(void);
#else
/* polyspace-begin MISRA-C3:11.1 [Justified:Medium] "To meet system call interface" */
#define Os_KernGetCoreID    Os_KernUnknownSyscall
#endif /* End of if (OS_MULTICORE == STD_ON) */

#define OS_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C3:20.1> */

#endif /* OS_MULTICORE_H_ */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
