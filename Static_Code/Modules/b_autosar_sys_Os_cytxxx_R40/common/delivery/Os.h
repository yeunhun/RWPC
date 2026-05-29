/*******************************************************************************
**                                                                            **
**  (C) 2013-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os.h                                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of extern declaration of APIs and Service-ID's.     **
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
** 2.6.4     01-Jul-2020    JH.Cho        Redmine #24397                      **
** 2.6.1     06-Mar-2020    MJ.Woo        Redmine #22246                      **
** 2.6.0     18-Dec-2019    SH.Yoo        Redmine #13546, #16219, #17076      **
** 2.4.3     27-Mar-2018    SH.Yoo        Redmine #12132                      **
** 2.4.0     14-Aug-2017    MJ.Woo        Redmine #9530                       **
** 2.0.13    30-Jun-2016    MJ.Woo        Redmine #4592, #4566, #5368         **
** 2.0.8     27-Feb-2014    SH.Yoo        TASK: xar~842, Redmine #626         **
** 2.0.4     23-Oct-2013    DG.Lee        CR: xar~179, TASK: xar~736          **
** 2.0.2     04-Sep-2013    MJ.Woo        CR: xar~168, TASK: xar~675          **
** 2.0.0     22-Jul-2013    JH.Son,SH.Yoo CR: xar~107, TASK: xar~543          **
**                          DG.Lee,MJ.Woo                                     **
** 1.0.0     10-Jan-2013    JH.Son,SH.Yoo Initial version                     **
**                          DG.Lee,MJ.Woo                                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> see MEMMAP003 of AUTOSAR */

#ifndef OS_H
#define OS_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"            /* Standard Header */
#include "Compiler.h"             /* Compiler Header */
#include "Os_Definition.h"        /* Definition of OS */
#include "Os_Cfg.h"               /* Configuration header file */
#include "Os_PCfg.h"              /* Port Specific Configuration header file */
#include "Os_Types.h"             /* Type definition of OS */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Macros for UNUSED */
/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> use function like-macro for removing unused argument compiler warning */
/* polyspace +2 MISRA-C3:14.3 [Justified:Medium] "For unused argument" */
#define OS_UNUSED(x)                  do { \
                                          if((uint32)(x) != \
                                             (uint32)OS_ZERO) {} \
                                      } while(0)
#define OS_UNUSED_PTR(x)              do { \
                                          if((x) != NULL_PTR) {} \
                                      } while(0)
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> use function like-macro for removing unused argument compiler warning */

/* Macro to resolve signature name */
/* polyspace:begin<MISRA-C:19.4:Not a defect:Justify with annotations> Definition for function redirection does not use parenthesised expression */
#define GetElapsedCounterValue        GetElapsedValue
#define Os_MeasureCPULoadSlave1       Os_MeasureCPULoad
#define Os_MeasureCPULoadSlave2       Os_MeasureCPULoad
#define Os_MeasureCPULoadSlave3       Os_MeasureCPULoad
#define Os_MeasureCPULoadSlave4       Os_MeasureCPULoad
#define Os_MeasureCPULoadSlave5       Os_MeasureCPULoad
/* polyspace:end<MISRA-C:19.4:Not a defect:Justify with annotations> Definition for function redirection does not use parenthesised expression */

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/

#define OS_USERIF_START_SEC_CODE
#include "MemMap.h"
#if (OS_TASK == STD_ON)
extern FUNC(StatusType, OS_CODE) ActivateTask(TaskType TaskID);

extern FUNC(StatusType, OS_CODE) TerminateTask(void);

extern FUNC(StatusType, OS_CODE) ChainTask(TaskType TaskID);

extern FUNC(StatusType, OS_CODE) GetTaskID(TaskRefType TaskID);

extern FUNC(StatusType, OS_CODE) GetTaskState(TaskType TaskID,
                                                        TaskStateRefType State);

extern FUNC(StatusType, OS_CODE) Schedule(void);
#endif /* (OS_TASK == STD_ON) */

extern FUNC(void, OS_CODE) ResumeAllInterrupts(void);

extern FUNC(void, OS_CODE) SuspendAllInterrupts(void);

extern FUNC(void, OS_CODE) EnableAllInterrupts(void);

extern FUNC(void, OS_CODE) DisableAllInterrupts(void);

extern FUNC(void, OS_CODE) ResumeOSInterrupts(void);

extern FUNC(void, OS_CODE) SuspendOSInterrupts(void);

#if (OS_RESOURCE == STD_ON)
extern FUNC(StatusType, OS_CODE) GetResource(ResourceType ResID);

extern FUNC(StatusType, OS_CODE) ReleaseResource(ResourceType ResID);
#endif /* (OS_RESOURCE == STD_ON) */

#if (OS_EVENT == STD_ON)
extern FUNC(StatusType, OS_CODE) SetEvent(TaskType TaskID, EventMaskType Mask);

extern FUNC(StatusType, OS_CODE) ClearEvent(EventMaskType Mask);

extern FUNC(StatusType, OS_CODE) GetEvent(TaskType TaskID,
                                                        EventMaskRefType Event);

extern FUNC(StatusType, OS_CODE) WaitEvent(EventMaskType Mask);
#endif /*(OS_EVENT == STD_ON) */

#if (OS_ALARM == STD_ON)
extern FUNC(StatusType, OS_CODE) GetAlarmBase(AlarmType AlarmID,
                                                         AlarmBaseRefType Info);

extern FUNC(StatusType, OS_CODE) GetAlarm(AlarmType AlarmID, TickRefType Tick);

extern FUNC(StatusType, OS_CODE) SetRelAlarm(AlarmType AlarmID,
                                            TickType Increment, TickType Cycle);

extern FUNC(StatusType, OS_CODE) SetAbsAlarm(AlarmType AlarmID,
                                                TickType Start, TickType Cycle);

extern FUNC(StatusType, OS_CODE) CancelAlarm(AlarmType AlarmID);
#endif /* (OS_ALARM == STD_ON) */

extern FUNC(AppModeType, OS_CODE) GetActiveApplicationMode(void);

/* polyspace +2 MISRA-C3:D4.5 [Not a defect:Low] "Unique in OS name space" */
extern FUNC(void, OS_CODE) StartOS(AppModeType Mode);

extern FUNC(void, OS_CODE) ShutdownOS(StatusType Error);

#if (OS_PROTECTION_HOOK == STD_ON)
extern FUNC(ProtectionReturnType, OS_CODE) ProtectionHook(
                                                         StatusType Fatalerror);
#endif /* End of if (OS_PROTECTION_HOOK == STD_ON) */

extern FUNC(void, OS_CODE) ErrorHook(StatusType Error);

extern FUNC(void, OS_CODE) PreTaskHook(void);

extern FUNC(void, OS_CODE) PostTaskHook(void);

extern FUNC(void, OS_CODE) StartupHook(void);

extern FUNC(void, OS_CODE) ShutdownHook(StatusType Error);

#if (OS_CAT2_ISR_COUNT > OS_ZERO)
extern FUNC(ISRType, OS_CODE)  GetISRID(void);
#endif /* (OS_CAT2_ISR_COUNT > OS_ZERO) */

#if (OS_SCHEDTABLE == STD_ON)
extern FUNC(StatusType, OS_CODE) StartScheduleTableAbs(
                             ScheduleTableType ScheduleTableID, TickType Start);

extern FUNC(StatusType, OS_CODE) StartScheduleTableRel(
                            ScheduleTableType ScheduleTableID, TickType Offset);

extern FUNC(StatusType, OS_CODE) NextScheduleTable(
  ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To);

extern FUNC(StatusType, OS_CODE) GetScheduleTableStatus(
  ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus);

extern FUNC(StatusType, OS_CODE) StopScheduleTable(
                                            ScheduleTableType ScheduleTableID);
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
extern FUNC(StatusType, OS_CODE) StartScheduleTableSynchron(
                                             ScheduleTableType ScheduleTableID);

extern FUNC(StatusType, OS_CODE) SyncScheduleTable(
                             ScheduleTableType ScheduleTableID, TickType Value);

extern FUNC(StatusType, OS_CODE) SetScheduleTableAsync(
                                             ScheduleTableType ScheduleTableID);
#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */

#if (OS_COUNTER == STD_ON)
extern FUNC(StatusType, OS_CODE) IncrementCounter(CounterType CounterID);

extern FUNC(StatusType, OS_CODE) GetCounterValue(CounterType CounterID,
  TickRefType Value);

extern FUNC(StatusType, OS_CODE) GetElapsedValue(CounterType CounterID,
  TickRefType Value,
  TickRefType ElapsedValue);
#endif /* (OS_COUNTER == STD_ON) */

#if (OS_SPINLOCK == STD_ON)
extern FUNC(StatusType, OS_CODE) TryToGetSpinlock(SpinlockIdType SpinlockId,
                        P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success);

extern FUNC(StatusType, OS_CODE) GetSpinlock(SpinlockIdType SpinlockId);

extern FUNC(StatusType, OS_CODE) ReleaseSpinlock(SpinlockIdType SpinlockId);
#endif /* End of if (OS_SPINLOCK == STD_ON) */

#if (OS_MULTICORE == STD_ON)
extern FUNC(uint32, OS_CODE) GetNumberOfActivatedCores(void);

extern FUNC(CoreIdType, OS_CODE) GetCoreID(void);

extern FUNC(void, OS_CODE) StartCore(CoreIDType CoreID, StatusType * Status);

extern FUNC(void, OS_CODE) StartNonAutosarCore
                                       (CoreIDType CoreID, StatusType * Status);

extern FUNC(void, OS_CODE) ShutdownAllCores(StatusType Error);
#endif /* End of if (OS_MULTICORE == STD_ON) */

#if (OS_APPLICATION == STD_ON)
extern FUNC(ApplicationType, OS_CODE) GetApplicationID(void);

extern FUNC(ApplicationType, OS_CODE) CheckObjectOwnership(
                           ObjectTypeType ObjectType, ObjectTypeIndex ObjectID);

#if (OS_MEMORY_PROTECTION == STD_ON)

extern FUNC(StatusType, OS_CODE) AllowAccess(void);

extern FUNC(StatusType, OS_CODE) GetApplicationState(
                    ApplicationType Application, ApplicationStateRefType Value);

extern FUNC(ObjectAccessType, OS_CODE) CheckObjectAccess(
   ApplicationType ApplID, ObjectTypeType ObjectType, ObjectTypeIndex ObjectID);

extern FUNC(StatusType, OS_CODE) TerminateApplication(
                        ApplicationType Application, RestartType RestartOption);

extern FUNC(AccessType, OS_CODE) CheckTaskMemoryAccess(TaskType TaskID,
                           MemoryStartAddressType Address, MemorySizeType Size);

extern FUNC(AccessType, OS_CODE) CheckISRMemoryAccess(ISRType IsrID,
                           MemoryStartAddressType Address, MemorySizeType Size);

#if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
extern FUNC(StatusType, OS_CODE) CallTrustedFunction(TrustedFunctionIndexType
                  FunctionIndex,TrustedFunctionParameterRefType FunctionParams);
#endif /* (OS_TRUSTED_FUNC_COUNT != OS_ZERO) */
#endif /* (OS_MEMORY_PROTECTION == STD_ON) */
#endif /* (OS_APPLICATION == STD_ON) */

#if (OS_APPLICATION == STD_ON)
extern FUNC(Std_ReturnType, OS_CODE) IocRead(uint32 IocID,
                                     P2CONST(void, AUTOMATIC, OS_CONST) data[]);
extern FUNC(Std_ReturnType, OS_CODE) IocWrite(uint32 IocID,
                                CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[]);

extern FUNC(Std_ReturnType, OS_CODE) IocReceive(uint32 IocID,
                                     P2CONST(void, AUTOMATIC, OS_CONST) data[]);
extern FUNC(Std_ReturnType, OS_CODE) IocSend(uint32 IocID,
                                CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[]);
extern FUNC(Std_ReturnType, OS_CODE) IocEmptyQueue(uint32 IocID);

extern FUNC(void, OS_CODE) Os_IocPullCB
         (P2FUNC(void, OS_CONST, pIocPullCB) (void), ApplicationType recvAppID);
#endif

#if (OS_PROFILING_HOOK == STD_ON)
extern FUNC(void, OS_CODE) Os_IsrEntryHook(CoreIDType LddCoreId, ISRType LddIsrId);
extern FUNC(void, OS_CODE) Os_IsrExitHook(CoreIDType LddCoreId, ISRType LddIsrId);
extern FUNC(void, OS_CODE) Os_IsrKillHook(CoreIDType LddCoreId, ISRType LddIsrId);
extern FUNC(void, OS_CODE) Os_TaskActivationHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_TaskTerminationHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_TaskPreemptionHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_TaskRunningHook(CoreIDType LddCoreId, TaskType LddTaskId, TaskStateType LddTaskState);
extern FUNC(void, OS_CODE) Os_TaskWaitingHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_TaskReleaseHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_TaskKillHook(CoreIDType LddCoreId, TaskType LddTaskId);
extern FUNC(void, OS_CODE) Os_IdleEntryHook(CoreIDType LddCoreId);
extern FUNC(void, OS_CODE) Os_IdleExitHook(CoreIDType LddCoreId);
#endif

extern FUNC(void, OS_CODE) Os_Idle(CoreIDType LddCoreId);

#define OS_USERIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C3:20.1> */

#endif /*OS_H_*/
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
