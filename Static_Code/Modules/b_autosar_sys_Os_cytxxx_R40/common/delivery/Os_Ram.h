/*******************************************************************************
**                                                                            **
**  (C) 2013-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Ram.h                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_Ram.c                                      **
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
** 2.5.0     26-Jun-2018    SH.Yoo        Redmine #12780                      **
** 2.3.1     22-May-2017    MJ.Woo        Redmine #5362                       **
** 2.3.0     28-Mar-2017    SH.Yoo        Redmine #5967                       **
** 2.1.1     10-Jan-2017    MJ.Woo        Redmine #7216                       **
** 2.0.13    30-Jun-2016    MJ.Woo        Redmine #5368                       **
** 2.0.10    09-Dec-2015    SH.Yoo        Redmine #1661                       **
** 2.0.9     15-Dec-2014    SH.Yoo        Redmine #1806                       **
**           10-Dec-2014    MJ.Woo        Redmine #1502                       **
**           26-Mar-2015    MJ.Woo        Redmine #2381                       **
** 2.0.8     22-Apr-2014    MJ.Woo        TASK: xar~842, Redmine #626         **
** 2.0.4     11-Nov-2013    SH.Yoo,MJ.Woo CR: xar~179, TASK: xar~736          **
** 2.0.0     22-Jul-2013    JH.Son,SH.Yoo CR: xar~107, TASK: xar~543          **
**                          DG.Lee,MJ.Woo                                     **
** 1.0.0     10-Jan-2013    JH.Son,SH.Yoo Initial version                     **
**                          DG.Lee,MJ.Woo                                     **
*******************************************************************************/
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations> External linkage with array size makes error because of compiler optimization  */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> see MEMMAP003 of AUTOSAR */

#ifndef OS_RAM_H
#define OS_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Arch_Ram.h"          /* Os Port-specific Data header file */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
extern VAR(boolean, OS_VAR) Os_GblOsInitialized[];
extern VAR(boolean, OS_VAR) Os_GblISRLock[];
extern VAR(boolean, OS_VAR) Os_GblStartOs[];
extern VAR(boolean, OS_VAR) Os_GblInterCoreInt[];
extern VAR(boolean, OS_VAR) Os_GblCoreShutdown[];
#if (OS_MULTICORE == STD_ON)
extern VAR(boolean, OS_VAR) Os_GblAppModeCheck;
extern VAR(boolean, OS_VAR) Os_GblShutdownFlag[];
#endif
#if (OS_TIMING_PROTECTION == STD_ON)
extern VAR(boolean, OS_VAR) Os_GblTPSFlag[];
#endif
#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"


#define OS_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(Os_IsrLockType, OS_VAR) Os_GddISRLock[];
extern VAR(Os_IsrLockType, OS_VAR) Os_GddISR2Lock[];
extern VAR(AppModeType, OS_VAR) Os_GddAppMode;
#if (OS_MULTICORE == STD_ON)
extern volatile VAR(uint8, OS_VAR) Os_GucSync1;
extern VAR(uint8, OS_VAR) Os_GucActivateCore;
#endif
#if(OS_APPLICATION == STD_ON)
extern VAR(ApplicationType, OS_VAR) Os_GddAppId[];
#endif
#if (OS_TIMING_PROTECTION == STD_ON)
extern VAR(uint8, OS_VAR) Os_GucExecFail[];
extern VAR(TaskType, OS_VAR) Os_GddFaultyTask[];
#if (OS_TRUSTED_FUNC_COUNT != OS_PRE_ZERO)
extern VAR(uint8, OS_VAR) Os_GucDelayBudget[];
#endif
#endif /* OS_TIMING_PROTECTION == STD_ON */
#define OS_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"


#define OS_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
extern VAR(uint16, OS_VAR) Os_GusCallevelCheck[];
#define OS_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"


#define OS_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
#if (OS_TIMING_PROTECTION == STD_ON)
extern VAR(uint32, OS_VAR) Os_GulBudgetTimerCount[];
extern VAR(uint32, OS_VAR) Os_GulTFTimerCount[];
#endif
#define OS_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"


#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) Os_GpStaticTask[];
extern VAR(TaskType, OS_VAR) Os_GaaLinkIndex[];
extern P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) Os_GpLinkTask[];
extern VAR(Os_OldLevel_T, OS_VAR) Os_GddOldSuspendOs[];
extern VAR(Os_OldLevel_T, OS_VAR) Os_GddOldSuspendAll[];
extern VAR(Os_StackType, OS_VAR) Os_GaaRamTaskStackSize[];
#if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
extern VAR(Os_StackType, OS_VAR) Os_GaaRamISRStackSize[];
#endif /* End of if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO) */
#if (OS_ERROR_HOOK == STD_ON)
extern VAR(Tdd_Os_ServiceCall, OS_VAR) Os_GddServiceCall[];
#endif /* End of if (OS_ERROR_HOOK == STD_ON) */
#if (OS_APPLICATION == STD_ON)
extern VAR(Tdd_Os_ApplicationData, OS_VAR) Os_GaaApplication[];
#endif
#if (OS_TIMING_PROTECTION == STD_ON)
extern P2VAR(Tdd_Os_ScheduleWatchdog, AUTOMATIC, OS_VAR) Os_GpSchedWatchdog[];
extern VAR(Tdd_Os_TPWatchdog, OS_VAR) Os_GaaRunningWdg[];
/** Variable to hold Timing Protection Values */
extern VAR(TickType, OS_VAR) Os_GaaTimingProtValue[];
#endif
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* OS_RAM_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> External linkage with array size makes error because of compiler optimization  */
/* polyspace:end<MISRA-C3:20.1> */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
