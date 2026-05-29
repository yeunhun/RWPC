/*******************************************************************************
**                                                                            **
**  (C) 2013-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_InternalTypes.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of AUTOSAR OS type internally used macros,          **
**              structure declarations and extern declarations of variables   **
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
** 2.6.7     04-Nov-2020    JH.Cho        Redmine #26023                      **
** 2.6.3     04-Jun-2020    MJ.Woo        Redmine #21784                      **
** 2.6.1     06-Mar-2020    MJ.Woo        Redmine #19430, #22246              **
** 2.4.2     14-Feb-2018    MJ.Woo        Redmine #7001                       **
** 2.4.1     10-Oct-2017    MJ.Woo        Redmine #10100                      **
** 2.3.1     13-Jul-2017    MJ.Woo        Redmine #8275, #5362, #9148         **
** 2.3.0     09-Mar-2017    SH.Yoo        Redmine #7724                       **
** 2.1.1     10-Jan-2017    MJ.Woo        Redmine #7216                       **
** 2.1.0     05-Oct-2016    SH.Yoo        Redmine #6057                       **
** 2.0.13    30-Jun-2016    MJ.Woo        Redmine #4592, #4595, #4606, #5368  **
** 2.0.12    25-Apr-2016    JH.Lee        Redmine #4295                       **
** 2.0.11    16-Feb-2016    JH.Lee        Redmine #3963                       **
**           22-Dec-2015    MJ.Woo        Redmine #3684                       **
** 2.0.9     13-Jul-2015    SH.Yoo        Redmine #2849                       **
**           10-Dec-2014    MJ.Woo        Redmine #494, #1427                 **
**           04-May-2015    MJ.Woo        Redmine #2381, #1640                **
** 2.0.8     14-Apr-2014    SH.Yoo        TASK: xar~842, Redmine #626         **
**                          SH.Yoo        TASK: xar~842, Redmine #124         **
** 2.0.7     13-Feb-2014    MJ.Woo        TASK: xar~819, Redmine #587         **
** 2.0.6     08-Jan-2014    SH.Yoo        TASK: xar~810                       **
** 2.0.5     23-Dec-2013    MJ.Woo        CR: xar~212, TASK: xar~796          **
** 2.0.4     11-Nov-2013    SH.Yoo        CR: xar~179, TASK: xar~736          **
**           23-Oct-2013    DG.Lee        CR: xar~179, TASK: xar~736          **
** 2.0.3     25-Sep-2013    MJ.Woo        CR: xar~172, TASK: xar~691          **
** 2.0.2     10-Sep-2013    DG.Lee,MJ.Woo CR: xar~168, TASK: xar~675          **
** 2.0.1     13-Aug-2013    DG.Lee        CR: xar~160, TASK: xar~655          **
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
/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace:begin<MISRA-C3:20.1:Not a defect:Justify with annotations> see MEMMAP003 of AUTOSAR */
/* polyspace:begin<MISRA-C3:20.7:Not a defect:Justify with annotations> expressions is verified manually */

#ifndef OS_INTERNALTYPES_H
#define OS_INTERNALTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

#if (OS_TIMING_PROTECTION == STD_ON)
typedef enum
{
  OS_WDG_DISABLED = OS_ZERO,
  OS_EXEC_BUDGET,
  OS_TIME_FRAME,
  OS_REZ_LOCK,
  OS_INT_LOCK,
  OS_ALL_INT_LOCK
} Os_WatchdogType;

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
typedef struct STagTdd_Os_ScheduleWatchdog
{
  /* pointer to the current running task*/
  P2CONST(struct STagTdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
  /*pointer to  the same structure*/
  P2VAR(struct STagTdd_Os_ScheduleWatchdog, AUTOMATIC, OS_VAR)
  pNextSchedWatchdog;
  /* Absolute Time */
  TickType ddSchedTick;
} Tdd_Os_ScheduleWatchdog;

typedef struct
{
  /* Array index for Timing Protection */
  uint32 ulTPArrayIndx;
  /*Hold the types of currently running Timing Protection.*/
  Os_WatchdogType ddWdgType;
  /* Hold the pointer to the timing protected task or cat2 isr */
  P2CONST(struct STagTdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
} Tdd_Os_TPWatchdog;

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "AUTRON_MISRA_D4_8" */
typedef struct
{
  /* Array where timing protection is specified (or not) for each resource
   *   (zero if no timing protection) */
  P2CONST(uint32, AUTOMATIC, OS_CONST)  pResourceLockTime;
  /* Maximum duration the task can be active within a timeframe or maximum
   *   isr execution time since last activation */
  TickType ddExecutionBudget;
  /* Configured timeframe for this timing protection */
  TickType ddTimeFrame;
  /* Interrupt lock time */
  TickType ddInterruptLockTime;
  /* All interrupt lock time */
  TickType ddAllInterruptLockTime;
  /* Time Frame ID */
  uint8 ucTimeFrameWdgId;
  /* ExeBudgetIndex */
  #if ((OS_TASK_TP_EB == STD_ON) || (OS_ISR_TP_EB == STD_ON))
  uint8 ucTaskExeBudgetIndex;
  #endif
} Tdd_Os_TimingProtection;
#endif /* #if(OS_TIMING_PROTECTION == ON) */

typedef struct
{
  /* Access Mask for Spinlock */
  uint32 ulAppAccessMask;
  /* Index to the next Spinlock */
  SpinlockIdType ddNextSpinIndex;
  /* Spin lock acquired Task */
  TaskType ddTaskId;
} Tdd_Os_Spinlock;

typedef struct
{
  /* Min Id of the nested spinlock */
  uint32 ulMinSpinID;
  /* Max Id of the nested spinlock */
  uint32 ulMaxSpinID;
} Tdd_Os_StaticSpinlock;

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
typedef struct
{
  #if (OS_MEMORY_PROTECTION == STD_ON)
  /* Application Mask */
  uint32 ddAppAccesMask;
  #endif
  #if (OS_APPLICATION == STD_ON)
  /* Application Id */
  ApplicationType ddAppId;
  #endif
  /* Priority of the owner before accessing to the resource. This field is
   *   used to restore the priority of the task when the resource is released */
  uint32 ulOwnerPrevPriority;
  /* Ceiling priority as computed at system generation time. */
  uint32 ulCeilingPriority;
  /* Flag to tell if the internal resource is taken or not */
  uint8 ucTaken;
} Tdd_Os_InternalResource;

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
typedef struct STagTdd_Os_Resource
{
  /* Owner of the resource or NULL if the resource is not owned */
  P2VAR(struct STagTdd_Os_Task, AUTOMATIC, OS_VAR) pOwner;
  /* Pointer to the next resource used to link them together when a task get
   *   more than one resource */
  P2VAR(struct STagTdd_Os_Resource, AUTOMATIC, OS_VAR) pNextResource;
  #if (OS_MEMORY_PROTECTION == STD_ON)
  /* Application Mask */
  uint32 ddAppAccesMask;
  #endif
  /* Resource ID */
  ResourceType ddResID;
  /* Priority of the owner before accessing to the resource. This field is
   *   used to restore the priority of the task when the resource is released */
  uint32 ulOwnerPrevPriority;
  /* Ceiling priority as computed at system generation time. */
  uint32 ulCeilingPriority;
  #if (OS_APPLICATION == STD_ON)
  /* Application Id */
  ApplicationType ddAppId;
  #endif
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
  #if (OS_RES_TP_EB == STD_ON)
  /* Index in Os_GaaTimingProtValue array */
  uint8 ddResLockTimeIndex;
  #endif

  #if (OS_RES_INT_SHARE == STD_ON)
  /* Store previous interrupt priority */
  uint32 ulOwnerPrevHwPrio;
  #endif
} Tdd_Os_Resource;

typedef struct
{
  /* Hardware priority of Interrupt if shared between Task and ISR */
  uint32 ulHardwarePriority;
} Tdd_Os_HardWareResource;

/* polyspace +3 MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
/* polyspace +2 MISRA-C3:2.4 [Not a defect:Low] "Tag is used in other struct declaration" */
typedef struct STagTdd_Os_Task
{
  #if (OS_RESOURCE == STD_ON)
  /* Head of the ressources held */
  P2VAR(struct STagTdd_Os_Resource, AUTOMATIC, OS_VAR) pResources;
  #endif
  #if (OS_EVENT == STD_ON)
  /* Event */
  EventMaskType ddEventSet;
  /* Wait for Event */
  EventMaskType ddEventWait;
  #endif
  /* State */
  /* Suspended = 0x00,
   *   Ready = 0x01,
   *   Running = 0x02
   *   Waiting = 0x03,
   *   Dying = 0x07,
   *   Resurrect = 0x08 */
  TaskStateType ddState;
  /* Current activate count */
  uint8 ucActivateCount;
  #if (OS_SPINLOCK == STD_ON)
  SpinlockIdType ddSpinlock;
  #endif
  #if (OS_TIMING_PROTECTION == STD_ON)
  /* TimeFrame Flag */
  boolean blActivateAllowed;
  #endif
} Tdd_Os_Task;

/* polyspace<MISRA-C:5.3:Not a defect:Justify with annotations> This is exists for compiler restriction */
/* polyspace<MISRA-C:5.4:Not a defect:Justify with annotations> This is to refer structure of Os_PortTypes.h which include this file. */
/* polyspace<MISRA-C:18.1:Not a defect:Justify with annotations> This is to refer structure of Os_PortTypes.h which include this file. */
typedef struct STagTdd_Os_ContextSwitch * pContext;

/* polyspace +3 MISRA-C3:D4.8 [Justified:Low] "AUTRON_MISRA_D4_8" */
/* polyspace +2 MISRA-C3:2.4 [Not a defect:Low] "Tag is used in other struct declaration" */
typedef struct STagTdd_Os_StaticTask
{
  /* Context of the ISR */
  /* polyspace<MISRA-C:5.3:Not a defect:Justify with annotations> This is to refer structure of Os_PortTypes.h which include this file. */
  /* polyspace<MISRA-C:5.4:Not a defect:Justify with annotations> This is to refer structure of Os_PortTypes.h which include this file. */
  /* polyspace<MISRA-C:18.1:Not a defect:Justify with annotations> This is to refer structure of Os_PortTypes.h which include this file. */
  P2VAR(struct STagTdd_Os_ContextSwitch, AUTOMATIC, OS_VAR) pContext;
  #if (OS_TIMING_PROTECTION == STD_ON)
  /* Timing protection configuration (can be NULL if no timing protection is
   *   needed) */
  P2CONST(Tdd_Os_TimingProtection, AUTOMATIC, OS_CONST) pStaticTimProtection;
  #endif
  /* Pointer to static descriptor */
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) pTask;

  /* Pointer to Link list structure */
  P2VAR(struct STagTdd_Os_LinkTask, AUTOMATIC, OS_VAR) pLinkTask;
  #if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
  /* Pointer to an internal resource. NULL if the task does not have an
   *   internal resource */
  P2VAR(Tdd_Os_InternalResource, AUTOMATIC, OS_VAR) pInternalResource;
  #endif
  /* Function that is the entry point of the task/isr */
  P2FUNC(void, OS_VAR, pFuncEntry) (void);
  #if (OS_MEMORY_PROTECTION == STD_ON)
  /* Application Mask */
  uint32 ddAppAccesMask;
  #endif
  /* Type of the Task/ISR */
  /* OS_TASK_BASIC = 0x01,
   * OS_TASK_EXTENDED = 0x02,
   * OS_ISR_ROUTINE = 0x04*/
  uint16 usType;
  /* Stack Index */
  uint8 ucStackIndex;
  /* Id of task/isr */
  TaskType ddTaskId;
  /* Base priority of the task/isr */
  uint32 ulBasePriority;
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreId;
  #endif
  #if (OS_APPLICATION == STD_ON)
  /* ID of the application to which the task belongs */
  ApplicationType ddAppId;
  #endif
  /* Max activation count of a task/isr */
  uint8 ucMaxActivateCount;
} Tdd_Os_StaticTask;

typedef struct
{
  /* Core activation status */
  boolean blCoreStatus;
} Tdd_Os_Core;

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
typedef struct STagTdd_Os_LinkTask
{
  /* Pointer to the next Link list */
  P2VAR(struct STagTdd_Os_LinkTask, AUTOMATIC, OS_VAR) pLinkList;
  /* Task ID */
  TaskType ddTaskID;
  /* Priority of the task */
  uint32 ulPriority;
} Tdd_Os_LinkTask;

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
typedef struct STagTdd_Os_Alarm
{
  /* Next alarm in the active alarm list */
  P2VAR(struct STagTdd_Os_Alarm, AUTOMATIC, OS_VAR) pNextAlarm;
  /* Previous alarm in the active alarm list */
  P2VAR(struct STagTdd_Os_Alarm, AUTOMATIC, OS_VAR) pPrevAlarm;
  /* Pointer to Alarm object */
  P2CONST(struct STagTdd_Os_StaticAlarm, AUTOMATIC, OS_CONST) pStaticAlarm;
  /* Cycle delay for cyclic alarms */
  TickType ddCycle;
  /* Absolute date of the alarm */
  TickType ddAbsCount;
  /* State of the alarm*/
  /* OS_ALARM_SLEEP = 0
   * OS_ALARM_ACTIVE = 1 */
  uint8 ucAlarmState;
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreId;
  #endif
} Tdd_Os_Alarm;

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "AUTRON_MISRA_D4_8" */
typedef struct STagTdd_Os_AlarmExpAction
{
  /* Pointer to the Action which takes place on expiry of alarm*/
  P2FUNC(StatusType, OS_VAR, pAlarmExpFunc)
  (P2CONST(struct STagTdd_Os_AlarmExpAction, AUTOMATIC, OS_CONST)
   pAction);
} Tdd_Os_AlarmExpAction;

typedef struct
{
  /* Action which takes place on expiry of alarm*/
  Tdd_Os_AlarmExpAction ddAlarmExpAction;
  /* pAlarm Callback function */
  P2FUNC(void, OS_VAR, pAlarmCallBack) (void);
} Tdd_Os_AlarmCallback;

typedef struct
{
  /* Action which takes place on expiry of alarm*/
  Tdd_Os_AlarmExpAction ddAlarmExpAction;
  /* Task descriptor pointer */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
} Tdd_Os_ActivateTask;

typedef struct
{
  /* Action which takes place on expiry of alarm*/
  Tdd_Os_AlarmExpAction ddAlarmExpAction;
  /* Task descriptor pointer */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
  /* Event information */
  EventMaskType ddEventMask;
} Tdd_Os_AlarmEvent;

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "AUTRON_MISRA_D4_8" */
typedef struct
{
  /* Action which takes place on expiry of alarm*/
  Tdd_Os_AlarmExpAction ddAlarmExpAction;
  /* Task descriptor pointer */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
  /* Event information */
  EventMaskType ddEventMask;
} Tdd_Os_Action;

typedef struct
{
  /* Action which takes place on expiry of alarm*/
  Tdd_Os_AlarmExpAction ddAlarmExpAction;
  /* ID of the counter to be updated */
  CounterType ddCounterId;
} Tdd_Os_IncrementCounter;

/* polyspace +3 MISRA-C3:D4.8 [Justified:Low] "AUTRON_MISRA_D4_8" */
/* polyspace +2 MISRA-C3:2.4 [Not a defect:Low] "Tag is used in other struct declaration" */
typedef struct STagTdd_Os_StaticAlarm
{
  /* Pointer to Action Object */
  P2CONST(Tdd_Os_AlarmExpAction, AUTOMATIC, OS_CONST) pAlarmExpAction;
  /* Pointer to counter */
  P2VAR(struct STagTdd_Os_Counter, AUTOMATIC, OS_VAR) pCounter;
  /* Pointer to static counter */
  P2CONST(struct STagTdd_Os_StaticCounter, AUTOMATIC, OS_CONST)
  pStaticCounter;
  #if (OS_MEMORY_PROTECTION == STD_ON)
  /* Application Mask */
  uint32 ddAppAccesMask;
  #endif
  #if (OS_APPLICATION == STD_ON)
  /* Application Id */
  ApplicationType ddAppId;
  #endif
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
} Tdd_Os_StaticAlarm;

/* polyspace +3 MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
/* polyspace +2 MISRA-C3:2.4 [Not a defect:Low] "Tag is used in other struct declaration" */
typedef struct STagTdd_Os_Counter
{
  #if ((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON))
  /* Active alarms list head */
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR)  pHeadAlarm;
  #endif
  /* Counter flag for using */
  boolean blAlarmInUse;
  /* Current value of the counter */
  TickType ddCurrentCount;
  /* Count of delayed ticks more than 1 tick */
  uint32 ulCounterLoss;
} Tdd_Os_Counter;

/* polyspace<MISRA-C:5.4:Not a defect:Justify with annotations> This is to refer structure of Os_PortTypes.h which include this file. */
/* polyspace<MISRA-C:18.1:Not a defect:Justify with annotations> This is to refer structure of Os_PortTypes.h which include this file. */
/* polyspace +2 MISRA-C3:2.4 [Not a defect:Low] "Tag is used in other struct declaration" */
typedef struct STagTdd_Os_HardwareCounter Tdd_Os_HardwareCounter;

/* polyspace +3 MISRA-C3:D4.8 [Justified:Low] "AUTRON_MISRA_D4_8" */
/* polyspace +2 MISRA-C3:2.4 [Not a defect:Low] "Tag is used in other struct declaration" */
typedef struct STagTdd_Os_StaticCounter
{
  /* Pointer to RAM Counter */
  P2VAR(Tdd_Os_Counter, AUTOMATIC, OS_VAR) pCounter;
  /* Pointer to Hardware Counter Info */
  P2VAR(Tdd_Os_HardwareCounter, AUTOMATIC, OS_VAR) pHwCounter;
  /* Maximum allowed value for a counter */
  TickType ddMaxAllowedValue;
  /* Number of ticks until the counter increments */
  TickType ddMinCycle;
  #if (OS_MEMORY_PROTECTION == STD_ON)
  /* Application Mask */
  uint32 ddAppAccesMask;
  #endif
  #if (OS_APPLICATION == STD_ON)
  /* Application Id */
  ApplicationType ddAppId;
  #endif
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
} Tdd_Os_StaticCounter;

/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "AUTRON_MISRA_D4_8" */
typedef struct
{
  /* Pointer to first action associated with expiry point */
  P2CONST(Tdd_Os_Action, AUTOMATIC, OS_CONST) pAction;
  /* Offset of the actions from the start time of the schedule table */
  TickType ddOffset;
  /* Maximum Advance Period */
  TickType ddMaxAdvancePeriod;
  /* Maximum Retard Period */
  TickType ddMaxRetardPeriod;
  /* Number of actions associated with the expiry point */
  uint8 ucCount;
} Tdd_Os_ExpiryPoint;

typedef struct
{
  /* Pointer to first expiry points */
  P2CONST(Tdd_Os_ExpiryPoint, AUTOMATIC, OS_CONST) pExpiryPoint;
  /* Pointer to counter object */
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) pStaticCounter;
  /* Duration of schedule table */
  TickType ddSchedTblDuration;
  /* OsScheduleTblExplicitPrecision */
  TickType ddExplictPrecision;
  /* Index to Alarm object */
  AlarmType ddAlarmIndex;
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
  /* Number of expiry count */
  uint32 ulExpiryCount;
  /* Synchroinization strategy */
  /* OS_EXPLICIT = 0
   * OS_IMPLICIT = 1 */
  uint8 ucSynchStrategy;
  /* True if schedule table is repeating */
  boolean blPeriodic;
} Tdd_Os_StaticSchedTable;
/* polyspace-end MISRA-C3:D4.8 */

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
typedef struct
{
  /* Action which takes place on expiry of alarm*/
  Tdd_Os_AlarmExpAction ddAlarmExpAction;
  /* Offset of next expiry point to be processed from start */
  TickType ddExpiryOffset;
  /* Deviation */
  sint32 ssDeviation;
  /* Next schedule table to start */
  ScheduleTableType ddNextSchedTable;
  /* Index of the Schedule Table */
  ScheduleTableType ddSchedTableId;
  /* Next expiry point to process in the schedule table */
  uint32 ulIndex;
} Tdd_Os_SchedTable;

typedef struct
{
  /* Pointer to the task to be restarted */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
} Tdd_Os_ReStartTask;

/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "AUTRON_MISRA_D4_8" */
typedef struct
{
  /* Pointer to the task which is autostart */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pStaticTask;
} Tdd_Os_AutoStartTask;

typedef struct
{
  /* Pointer to the Alarm which is autostart */
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) pAlarm;
} Tdd_Os_AutoStartAlarm;

typedef struct
{
  /* Pointer to the ScheduleTable which is autostart */
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC,
    OS_CONST) pStaticSchedTable;
} Tdd_Os_AutoStartSchedTable;
/* polyspace-end MISRA-C3:D4.8 */

typedef struct
{
  /* Pointer to the AutosatrtTask Structure */
  P2CONST(Tdd_Os_AutoStartTask, AUTOMATIC, OS_CONST) pAutoStartTask;
  /* Pointer to the AutosatrtAlarm Structure */
  P2CONST(Tdd_Os_AutoStartAlarm, AUTOMATIC, OS_CONST) pAutoStartAlarm;
  /* Pointer to the AutosatrtScheduleTable Structure */
  P2CONST(Tdd_Os_AutoStartSchedTable, AUTOMATIC, OS_CONST)
  pAutoStartSchedTable;
  /* Number of Autostart Schedule Table */
  ScheduleTableType ddNoOfAutoStartSchedTable;
  /* Number of Autostart Task */
  TaskType ddNoOfAutoStartTask;
  /* Number of Autostart Alarm */
  AlarmType ddNoOfAutoStartAlarm;
} Tdd_Os_ApplMode;

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "AUTRON_MISRA_D4_8" */
typedef struct
{
  #if (OS_RESTART_TASK_COUNT != OS_PRE_ZERO)
  /* Pointer to the RestartTask in the application */
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) pRestartTask;
  #endif
  /* Pointer to the Alarm in the application */
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) pApplicationAlarm;
  /* Pointer to the ScheduleTable in the application */
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) pApplicationScheTbl;
  /*  Application Mask = 2^ddAppId */
  uint16 usAppMask;
  /* Number of Schedule Table in the application */
  ScheduleTableType ddNoOfStaticSchedTable;
  /* Number of Alarm in the application */
  AlarmType ddNoOfAlarm;
  /* Application Id */
  ApplicationType ddAppId;
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
  /* Stack Index */
  uint8 ucStackIndex;
  #if ((OS_SCALABILITY_CLASS == OS_SC3) || (OS_SCALABILITY_CLASS == OS_SC4))
  /* ucType */
  uint8 ucType;
  /* Base Index of memory blocks */
  uint8 ucBaseMemBlockIndex;
  /* Maximum Index of memory blocks */
  uint8 ucNoOfMemBlk;
  #endif
} Tdd_Os_Application;

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
typedef struct
{
  /* State of the Application */
  ApplicationStateType ddState;
} Tdd_Os_ApplicationData;

#if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
typedef struct
{
  /* Pointer to trusted function */
  P2FUNC(void, OS_VAR, pTrustedFunc) (void*);
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
} Tdd_Os_TrustedFunction;
#endif /* End of if (OS_TRUSTED_FUNC_COUNT != OS_ZERO) */
#if ((OS_APP_ERROR_HOOK == STD_ON) || (OS_APP_SHUTDOWN_HOOK == STD_ON) ||\
  (OS_APP_STARTUP_HOOK == STD_ON))
typedef struct
{
  #if (OS_APP_ERROR_HOOK == STD_ON)
  /* Application specific Error Hook function */
  P2FUNC(void, OS_VAR, pErrorHook) (StatusType);
  #endif

  #if (OS_APP_SHUTDOWN_HOOK == STD_ON)
  /* Application specific Error Hook function */
  P2FUNC(void, OS_VAR, pShutDownHook) (StatusType);
  #endif

  #if (OS_APP_STARTUP_HOOK == STD_ON)
  /* Application specific Error Hook function */
  P2FUNC(void, OS_VAR, pStartupHook) (void);
  #endif
  #if (OS_MULTICORE == STD_ON)
  /* Core ID of the belonging core */
  CoreIDType ddCoreID;
  #endif
} Tdd_Os_ApplicationHook;
#endif /* End of if ((OS_APP_ERROR_HOOK == STD_ON) || (OS_APP_SHUTDOWN_HOOK ==
        *STD_ON) || (OS_APP_STARTUP_HOOK == STD_ON)) */

#if (OS_ERROR_HOOK == STD_ON)

/* polyspace:begin<MISRA-C:18.4:Not a defect:Justify with annotations> These unions are used to specify error type */
typedef union
{
  TrustedFunctionIndexType FunctionIndex;
  TaskType TaskID;
  ScheduleTableType ScheduleTableID;
  ScheduleTableType ScheduleTableID_From;
  CounterType CounterID;
  ApplicationType Application;
  TaskRefType TaskIDRef;                   /* GetTaskID's 1st param - TaskID */
  ResourceType ResID;
  EventMaskType Mask;
  AlarmType AlarmID;
  SpinlockIdType SpinlockId;
} Tdd_Os_ParamBlock1;

typedef union
{
  TrustedFunctionParameterRefType FunctionParams;
  TickType Offset;
  TickType Start;
  ScheduleTableType ScheduleTableID_To;
  TickType Value;
  ScheduleTableStatusRefType ScheduleStatus;
  TickRefType ValueRef;                    /* GetCounterValue's 2nd param - Value */
                                           /* GetElapsedValue's 2nd param - Value */
  RestartType RestartOption;
  ApplicationStateRefType AppValueRef;     /* GetApplicationState's 2nd param - Value */
  TaskStateRefType State;
  EventMaskType Mask;
  EventMaskRefType Event;
  AlarmBaseRefType Info;
  TickRefType Tick;
  TickType Increment;
  TickType TickStart;                      /* SetAbsAlarm's 2nd param - Start */
  TryToGetSpinlockType* Success;
} Tdd_Os_ParamBlock2;

typedef union
{
  TickRefType ElapsedValue;
  TickType Cycle;
} Tdd_Os_ParamBlock3;
/* polyspace:end<MISRA-C:18.4:Not a defect:Justify with annotations> These unions are used to specify error type */

typedef struct
{
  Tdd_Os_ParamBlock1 unParam1;
  Tdd_Os_ParamBlock2 unParam2;
  Tdd_Os_ParamBlock3 unParam3;
} Tdd_Os_Parameter;

/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
typedef struct
{
  Tdd_Os_Parameter ddParameters;
  OSServiceIdType  ucServiceID;
} Tdd_Os_ServiceCall;
#endif /* #if (OS_ERROR_HOOK == STD_ON) */


/* Data types for Multi-core Scheduling with Cross-core Messaging */
#if (OS_MULTICORE == STD_ON)
/* Largest no. of parameters to a service */
#define OS_MAXPARAM   3

/* The number of messages in the queues
*/
#define OS_N_MESSAGES             (OS_CORE_COUNT-1)

/* Inter-core message queue.
 *
 * The message queue itself is an array of n message structures, where n is the largest number of
 * messages that can be queued at any time. This array is written by the sender and read by the
 * receiver.
 *
 * Queue control is achieved through three indices; the fill, the empty and the message counter.
 *
 * The fill index is written by the sender and is read-only for the receiver. The empty index
 * is read-only for the sender and is written by the receiver.
 * Message counter index is incremented by the sender and decremented by the receiver.
 */

/* A single message.
 */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
typedef struct
{
  uint32 opcode;
  uint32 result;
  uint32 parameter[OS_MAXPARAM];
  uint32 resultReady;
}Os_MessageType;

/* Message queue structure.
 */
typedef struct
{
  uint16 fill;
  uint16 empty;
  uint16 msgCnt;
  uint16 buffer[OS_N_MESSAGES];
  Os_MessageType msg[OS_N_MESSAGES];
}Os_MessageQueueType;

/* Message queue structure.
 * The size must be multiples of OS_CACHE_LINE_LEN
 */
typedef struct
{
  Os_MessageQueueType queue;
  uint16 dummy[11];
}Os_MessageQueueArchType;
#endif /* #if (OS_MULTICORE == STD_ON) */

/* Privilege mode type */
typedef enum
{
  OS_PRIV_UNKNOWN,     /* Unknown status */
  OS_PRIV_SUPERVISOR,  /* Privileged mode: Unrestricted access is available */
  OS_PRIV_USER         /* Non-privileged mode : Access is restricted */
} Os_PrivModeType;

typedef enum
{
  OS_LOCKTYPE_OS = 0,       /* Suspend/ResumeOSInterrupts() */
  OS_LOCKTYPE_ALL = 1,      /* Suspend/ResumeAllInterrupts() */
  OS_LOCKTYPE_NONEST = 2    /* Disable/EnableAllInterrupts() */
} OsIntLockType;

/** This data type identifies the nesting count of SuspendAll(OS)Interrupts. */
typedef uint8 Os_IsrLockType;

/** Types for structure of Stack Parameters */
 typedef struct
{
  P2VAR(Os_StackType, AUTOMATIC, OS_VAR) pStackArea; /**< Pointer Variable for Stack Area */
  uint16 usStackSize;                                /**< Variable for Stack size */
} Tdd_Os_Stack;

#define OS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#if ((OS_APP_ERROR_HOOK == STD_ON) || (OS_APP_SHUTDOWN_HOOK == STD_ON) ||\
                                                (OS_APP_STARTUP_HOOK == STD_ON))
extern CONST(Tdd_Os_ApplicationHook, OS_CONST) Os_GaaStaticAppHook[];
#endif /* End of if ((OS_APP_ERROR_HOOK == STD_ON) || (OS_APP_SHUTDOWN_HOOK ==
        *STD_ON) || (OS_APP_STARTUP_HOOK == STD_ON)) */
#if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
extern CONST(Tdd_Os_TrustedFunction, OS_CONST) Os_GaaTrustedFunction[];
#endif /* End of if (OS_TRUSTED_FUNC_COUNT != OS_ZERO) */
extern CONST(Tdd_Os_StaticTask, OS_CONST) Os_GaaStaticTask[];
extern CONST(Tdd_Os_HardWareResource, OS_CONST) Os_GaaHardWareResource[];
extern CONST(Tdd_Os_AutoStartTask, OS_CONST) Os_GaaAutoStartTask[];
extern CONST(Tdd_Os_AutoStartSchedTable, OS_CONST) Os_GaaAutoSchedTable[];
extern CONST(Tdd_Os_StaticCounter, OS_CONST) Os_GaaStaticCounter[];
extern CONST(Tdd_Os_StaticAlarm, OS_CONST) Os_GaaStaticAlarm[];
extern CONST(Tdd_Os_StaticSchedTable, OS_CONST) Os_GaaStaticSchedTable[];
extern CONST(Tdd_Os_ApplMode, OS_CONST) Os_GaaApplMode[];
extern CONST(Tdd_Os_Action, OS_CONST) Os_GaaAction[];
extern CONST(Tdd_Os_IncrementCounter, OS_CONST) Os_GaaIncrementCounter[];
extern CONST(Tdd_Os_AlarmCallback, OS_CONST) Os_GaaAlarmCallback[];
extern CONST(Tdd_Os_ActivateTask, OS_CONST) Os_GaaActivateTask[];
extern CONST(Tdd_Os_AlarmEvent, OS_CONST) Os_GaaAlarmEvent[];
extern CONST(Tdd_Os_AutoStartAlarm, OS_CONST) Os_GaaAutoStartAlarm[];
extern CONST(Tdd_Os_ReStartTask, OS_CONST) Os_GaaReStartTask[];
extern CONST(Tdd_Os_ExpiryPoint, OS_CONST) Os_GaaExpiryPoint[];
#if (OS_TIMING_PROTECTION == STD_ON)
extern CONST(Tdd_Os_TimingProtection, OS_CONST) Os_GaaTimingProtection[];
#endif /*OS_TIMING_PROTECTION == STD_ON*/
#if (OS_MULTICORE == STD_ON)
extern CONST(uint8, OS_CONST)  Os_GaaCAT2MaxPriority[];
extern CONST(uint8, OS_CONST)  Os_GaaCAT1LeastPriority[];
#endif /*OS_MULTICORE == STD_ON*/
#if (OS_SPINLOCK == STD_ON)
extern CONST(Tdd_Os_StaticSpinlock, OS_CONST) Os_GaaStaticSpinlock[];
#endif /*OS_SPINLOCK == STD_ON*/
#if (OS_APPLICATION == STD_ON)
extern CONST(Tdd_Os_Application, OS_CONST) Os_GaaStaticApplication[];
#endif
extern CONST(Tdd_Os_Stack, OS_CONST) Os_GaaStack[];
/* polyspace:begin<MISRA-C3:8.6:Not a defect:Justify with annotations> below variable can be used for the user */
extern CONST(AppModeType, OS_CONST) Os_ApplMode_Count;
extern CONST(TaskType, OS_CONST) Os_Task_Count;
extern CONST(ISRType, OS_CONST) Os_CAT2_ISR_Count;
extern CONST(ISRType, OS_CONST) Os_CAT1_ISR_Count;
extern CONST(ISRType, OS_CONST) Os_ISR_Count;
extern CONST(uint16, OS_CONST) Os_CAT2_Max_Priority;
extern CONST(uint16, OS_CONST) Os_CAT1_Least_Priority;
extern CONST(ISRType, OS_CONST) Os_Max_Nest_Level;
extern CONST(ResourceType, OS_CONST) OS_Resource_Count;
extern CONST(CounterType, OS_CONST) Os_Counter_Count;
extern CONST(AlarmType, OS_CONST) Os_Alarm_Count;
extern CONST(ScheduleTableType, OS_CONST) Os_Schedule_Count;
extern CONST(uint8, OS_CONST) Os_Core_Count;
extern CONST(SpinlockIdType, OS_CONST) Os_Spinlock_Count;
extern CONST(uint16, OS_CONST) Os_Ioc_Callback_Count;
extern CONST(uint16, OS_CONST) Os_Ioc_Count;
extern CONST(uint16, OS_CONST) Os_Ioc_Count_Queued;
extern CONST(uint16, OS_CONST) Os_Ioc_Count_Unqueued;
extern CONST(ApplicationType, OS_CONST) Os_Application_Count;
extern CONST(ApplicationType, OS_CONST) Os_Trusted_Start_Indx;
extern CONST(TrustedFunctionIndexType, OS_CONST) Os_Trusted_Func_Count;
extern CONST(uint16, OS_CONST) Os_App_MemBlk_Cnt;
/* polyspace:end<MISRA-C3:8.6> */
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_CONST_32
#include "MemMap.h"
extern CONST(uint32, OS_CONST) Os_User_Stack_Size;
#if (OS_TIMING_PROTECTION == STD_ON)
extern CONST(uint32, OS_CONST) Os_GaaResourceLock[];
#endif /*OS_TIMING_PROTECTION == STD_ON*/
#define OS_STOP_SEC_CONST_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(Tdd_Os_Task, OS_VAR) Os_GaaTask[];
extern VAR(Tdd_Os_Core, OS_VAR) Os_GaaCore[];
extern VAR(Tdd_Os_Counter, OS_VAR) Os_GaaCounter[];
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Tdd_Os_Alarm, OS_VAR) Os_GaaAlarm[];
extern VAR(Tdd_Os_LinkTask, OS_VAR) Os_GaaLinkTask[];
extern VAR(Tdd_Os_InternalResource, OS_VAR) Os_GaaInternalResource[];
extern VAR(Tdd_Os_Resource, OS_VAR) Os_GaaResourceTable[];
#if (OS_SCHEDTABLE == STD_ON)
extern VAR(Tdd_Os_SchedTable, OS_VAR) Os_GaaSchedTable[];
#endif /*OS_SCHEDTABLE == STD_ON*/
#if (OS_TIMING_PROTECTION == STD_ON)
extern VAR(Tdd_Os_ScheduleWatchdog, OS_VAR) Os_GaaSchedWatchdog[];
#endif /*OS_TIMING_PROTECTION == STD_ON*/
#if (OS_SPINLOCK == STD_ON)
extern VAR(Tdd_Os_Spinlock, OS_VAR) Os_GaaSpinlock[];
#endif /*OS_SPINLOCK == STD_ON*/
#define OS_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* Os_InternalTypes*/


/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> External linkage with array size makes error because of compiler optimization  */
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace:end<MISRA-C3:20.1> */
/* polyspace:end<MISRA-C3:20.7> */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
