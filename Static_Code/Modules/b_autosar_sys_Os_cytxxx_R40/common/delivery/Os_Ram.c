/*******************************************************************************
**                                                                            **
**  (C) 2013-2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Ram.c                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Declaration of the global variables.                          **
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
** 2.6.0     23-Dec-2019    SH.Yoo        Redmine #13546                      **
** 2.3.1     22-May-2017    MJ.Woo        Redmine #5362                       **
** 2.3.0     28-Mar-2017    SH.Yoo        Redmine #5967                       **
** 2.1.1     10-Jan-2017    MJ.Woo        Redmine #7216                       **
** 2.0.13    30-Jun-2016    MJ.Woo        Redmine #5368                       **
** 2.0.10    09-Dec-2015    SH.Yoo        Redmine #1661                       **
** 2.0.9     15-Dec-2014    SH.Yoo        Redmine #1806                       **
**           10-Dec-2014    MJ.Woo        Redmine #1189                       **
**           26-Mar-2015    MJ.Woo        Redmine #2381                       **
** 2.0.8     22-Apr-2014    MJ.Woo        TASK: xar~842, Redmine #626         **
** 2.0.4     11-Nov-2013    SH.Yoo        CR: xar~179, TASK: xar~736          **
**                          DG.Lee                                            **
**                          MJ.Woo                                            **
** 2.0.0     22-Jul-2013    JH.Son,SH.Yoo CR: xar~107, TASK: xar~543          **
**                          DG.Lee,MJ.Woo                                     **
** 1.0.0     10-Jan-2013    JH.Son,SH.Yoo Initial version                     **
**                          DG.Lee,MJ.Woo                                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> see MEMMAP003 of AUTOSAR */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Ram.h"               /* Os Ram header file */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define OS_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/** Variable for OS Global Initialization */
VAR(boolean, OS_VAR) Os_GblOsInitialized[OS_CORE_COUNT];
/** Boolean Variable for Interrupt Lock */
VAR(boolean, OS_VAR) Os_GblISRLock[OS_CORE_COUNT];
/** Variable for OS Global Initialization for Multi Core */
VAR(boolean, OS_VAR) Os_GblStartOs[OS_CORE_COUNT];
VAR(boolean, OS_VAR) Os_GblInterCoreInt[OS_CORE_COUNT];
VAR(boolean, OS_VAR) Os_GblCoreShutdown[OS_CORE_COUNT];
#if (OS_MULTICORE == STD_ON)
/** Flag for Application Mode */
VAR(boolean, OS_VAR) Os_GblAppModeCheck;
/* polyspace<VARIABLE:ALL:Not a defect:No Action Planned> can be used for applications */
/** Variable to hold Global Shutdown */
VAR(boolean, OS_VAR) Os_GblShutdownFlag[OS_CORE_COUNT];
#endif /*OS_MULTICORE == STD_ON */
#if (OS_TIMING_PROTECTION == STD_ON)
VAR(boolean, OS_VAR) Os_GblTPSFlag[OS_CORE_COUNT];
#endif
#define OS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"


#define OS_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/** Nesting Variable for Interrupt Lock */
VAR(Os_IsrLockType, OS_VAR) Os_GddISRLock[OS_CORE_COUNT];
/** Nesting Variable for CAT2 interrupt Lock */
VAR(Os_IsrLockType, OS_VAR) Os_GddISR2Lock[OS_CORE_COUNT];
/** Variable to hold running Mode */
VAR(AppModeType, OS_VAR) Os_GddAppMode;
#if (OS_MULTICORE == STD_ON)
/** Variable for synchronization between cores */
volatile VAR(uint8, OS_VAR) Os_GucSync1;
/** Variable for number of active cores */
VAR(uint8, OS_VAR) Os_GucActivateCore;
#endif /*OS_MULTICORE == STD_ON */
#if(OS_APPLICATION == STD_ON)
VAR(ApplicationType, OS_VAR) Os_GddAppId[OS_CORE_COUNT];
#endif
#if (OS_TIMING_PROTECTION == STD_ON)
VAR(uint8, OS_VAR) Os_GucExecFail[OS_CORE_COUNT];
/** To save Task or ISR id when TPS trap occured in kernel mode */
VAR(TaskType, OS_VAR) Os_GddFaultyTask[OS_CORE_COUNT];
#if (OS_TRUSTED_FUNC_COUNT != OS_PRE_ZERO)
VAR(uint8, OS_VAR) Os_GucDelayBudget[OS_CORE_COUNT];
#endif
#endif /* OS_TIMING_PROTECTION == STD_ON */
#define OS_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"


#define OS_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, OS_VAR) Os_GusCallevelCheck[OS_CORE_COUNT];
/** This global variable used to save CPU load. */
#define OS_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"


#define OS_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
#if (OS_TIMING_PROTECTION == STD_ON)
VAR(uint32, OS_VAR) Os_GulBudgetTimerCount[OS_CORE_COUNT];
VAR(uint32, OS_VAR) Os_GulTFTimerCount[OS_CORE_COUNT];
#endif
#define OS_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"


#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
VAR(Tdd_Os_Task, OS_VAR) Os_GaaTask
    [OS_TASK_COUNT + OS_CAT2_ISR_COUNT + OS_CORE_COUNT];
/** Variable to hold running Task */
P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) Os_GpStaticTask[OS_CORE_COUNT];
/* polyspace<VARIABLE:ALL:Not a defect:No Action Planned> can be used according to configuration */
/** Variable to hold link lists */
VAR(TaskType, OS_VAR) Os_GaaLinkIndex
    [OS_TASK_COUNT + OS_CAT2_ISR_COUNT + OS_CORE_COUNT];
/** Variable to hold running link lists */
P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR)Os_GpLinkTask[OS_CORE_COUNT];
VAR(Os_OldLevel_T, OS_VAR) Os_GddOldSuspendOs[OS_CORE_COUNT];
VAR(Os_OldLevel_T, OS_VAR) Os_GddOldSuspendAll[OS_CORE_COUNT];
#if (OS_ERROR_HOOK == STD_ON)
VAR(Tdd_Os_ServiceCall, OS_VAR) Os_GddServiceCall[OS_CORE_COUNT];
#endif /* End of if (OS_ERROR_HOOK == STD_ON) */
#if (OS_COUNTER_COUNT != OS_PRE_ZERO)
/* polyspace<VARIABLE:ALL:Not a defect:No Action Planned> can be used according to configuration */
VAR(Tdd_Os_Counter, OS_VAR) Os_GaaCounter[OS_COUNTER_COUNT];
#endif /*OS_COUNTER_COUNT != OS_PRE_ZERO*/
#if (OS_APPLICATION == STD_ON)
/** Variable to dynamic Application Variable */
VAR(Tdd_Os_ApplicationData, OS_VAR) Os_GaaApplication[OS_APPLICATION_COUNT];
#endif /* OS_APPLICATION == STD_ON*/
#if (OS_MULTICORE == STD_ON)
/** Array to hold dynamic Variable for cores */
VAR(Tdd_Os_Core, OS_VAR) Os_GaaCore[OS_CORE_COUNT];
#endif /*OS_MULTICORE == STD_ON*/
#if (OS_TIMING_PROTECTION == STD_ON)
/** Variable to hold running schedule Wdg */
P2VAR(Tdd_Os_ScheduleWatchdog, AUTOMATIC, OS_VAR)
                                              Os_GpSchedWatchdog[OS_CORE_COUNT];
/** Variable to hold schedule Wdg */
VAR(Tdd_Os_TPWatchdog, OS_VAR) Os_GaaRunningWdg[OS_CORE_COUNT];
#endif
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace:end<MISRA-C3:20.1> */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
