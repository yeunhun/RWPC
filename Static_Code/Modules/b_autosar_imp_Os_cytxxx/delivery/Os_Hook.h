/*******************************************************************************
**                                                                            **
**  (C) 2020 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Hook.h                                                     **
**                                                                            **
**  TARGET    : CYTxxx                                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR OS Improvement Code                                   **
**                                                                            **
**  PURPOSE   : Header file for Os Hook containing the declaration of error   **
**              information                                                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.0.0     18-Feb-2020    MJ.Woo        Redmine #20864                      **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "Declare a name _VAR because it is same with VAR" */

#ifndef OS_HOOK_H
#define OS_HOOK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"
#include "Os_ErrorExternal.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define SZ_OSERROR 8
#define MASK_OSERROR_BUF 0x7

/** OS Error code redefine for easy to see in debugger */
typedef enum
{
  _E_OK = E_OK,
  _E_OS_ACCESS = E_OS_ACCESS,       /* Access to the service/object denied */
  _E_OS_CALLEVEL = E_OS_CALLEVEL,   /* Access to the service from
                                       the ISR is not permitted */
  _E_OS_ID = E_OS_ID,               /* Object ID is invalid */
  _E_OS_LIMIT = E_OS_LIMIT,         /* Limit of services/objects exceeded */
  _E_OS_NOFUNC = E_OS_NOFUNC,       /* The object is not used,
                                       service rejected */
  _E_OS_RESOURCE = E_OS_RESOURCE,   /* Task still occupies resource */
  _E_OS_STATE = E_OS_STATE,         /* The state of the object is not correct
                                       for the required service */
  _E_OS_VALUE = E_OS_VALUE,         /* Value outside of the admissible limit */
  _E_OS_SERVICEID = E_OS_SERVICEID, /* Service can not be called */
  _E_OS_ILLEGAL_ADDRESS = E_OS_ILLEGAL_ADDRESS, /* An invalid address is given
                                                  as a parameter to a service */
  _E_OS_MISSINGEND = E_OS_MISSINGEND,   /* Tasks terminates without a
                                          TerminateTask() or ChainTask() call */
  _E_OS_DISABLEDINT = E_OS_DISABLEDINT, /* A service of the OS is called inside
                                           an interrupt disable/enable pair */
  _E_OS_CORE = E_OS_CORE,          /* The OS API is not allowed between cores */
  _E_OS_INTERFERENCE_DEADLOCK = E_OS_INTERFERENCE_DEADLOCK, /* The spinlock
                                      referred by the parameter SpinlockID is
                             already occupied by a TASK/ISR2 on the same core */
  _E_OS_NESTING_DEADLOCK = E_OS_NESTING_DEADLOCK, /* A TASK tries to occupy the
                                    spinlock while holding a different spinlock
                                           in a way that may cause a deadlock */
  _E_OS_SPINLOCK = E_OS_SPINLOCK,  /* This error means de-scheduling with
                                                           occupied spinlock. */
  _E_OS_PARAM_POINTER = E_OS_PARAM_POINTER, /* A pointer argument of an API is
                                                                 NULL pointer */
  _E_OS_STACKFAULT = E_OS_STACKFAULT,       /* A stack fault detected via
                                                   stack monitoring by the OS */
  _E_OS_PROTECTION_MEMORY = E_OS_PROTECTION_MEMORY, /* A memory access
                                                         violation occurred */
  _E_OS_PROTECTION_TIME = E_OS_PROTECTION_TIME, /* A Task/Category 2 ISR exceeds
                                                    its execution time budget */
  _E_OS_PROTECTION_LOCKED = E_OS_PROTECTION_LOCKED, /* A Task/Category 2 ISR
                                                          blocks for too long */
  _E_OS_PROTECTION_EXCEPTION = E_OS_PROTECTION_EXCEPTION,  /* A trap occurred */
  _E_OS_PROTECTION_ARRIVAL = E_OS_PROTECTION_ARRIVAL, /* A Task/Category 2 ISR
                                                        arrives before its
                                                        timeframe has expired */
  /* Implementation specific error codes */
  _E_OS_SYS_ALARM_INUSE = E_OS_SYS_ALARM_INUSE,/* Counter interrupt is nested */
  _E_OS_SYS_RAMECC = E_OS_SYS_RAMECC, /* An ECC error has occurred on the RAM */
  _E_OS_SYS_DFLASHECC = E_OS_SYS_DFLASHECC, /* An ECC error has occurred
                                                            on the Data Flash */
  _E_OS_SYS_PFLASHECC = E_OS_SYS_PFLASHECC, /* An ECC error has occurred
                                                         on the Program Flash */
  _E_OS_SYS_CORE_IS_DOWN = E_OS_SYS_CORE_IS_DOWN, /* This error code means that
                                              the core is shutting down state */
  _E_OS_SYS_PANIC = E_OS_SYS_PANIC,       /* OS fatal error: Assertion failed */
  _E_OS_SYS_NMI = E_OS_SYS_NMI,           /* This error code means that
                                                        NMI handling is fault */
  _E_OS_SYS_INTERCOREMSG = E_OS_SYS_INTERCOREMSG, /* A problem occurred during
                                           the inter-core API request process */
} Os_ErrorValueType;

/** OS Service id redefine for easy to see in debugger */
typedef enum
{
  _StartOS = OSServiceId_StartOS,
  _ShutdownOS = OSServiceId_ShutdownOS,
  _GetActiveApplicationMode = OSServiceId_GetActiveApplicationMode,

  /* memory protection services */
  _CallTrustedFunction = OSServiceId_CallTrustedFunction,
  _CheckISRMemoryAccess = OSServiceId_CheckISRMemoryAccess,
  _CheckTaskMemoryAccess = OSServiceId_CheckTaskMemoryAccess,

  /* OS-Application services */
  _GetApplicationID = OSServiceId_GetApplicationID,
  _CheckObjectAccess = OSServiceId_CheckObjectAccess,
  _CheckObjectOwnership = OSServiceId_CheckObjectOwnership,
  _TerminateApplication = OSServiceId_TerminateApplication,
  _AllowAccess = OSServiceId_AllowAccess,
  _GetApplicationState = OSServiceId_GetApplicationState,

  _ShutdownAllCores = OSServiceId_ShutdownAllCores,

  /* task management services */
  _ActivateTask = OSServiceId_ActivateTask,
  _TerminateTask = OSServiceId_TerminateTask,
  _ChainTask = OSServiceId_ChainTask,
  _Schedule = OSServiceId_Schedule,
  _GetTaskID = OSServiceId_GetTaskID,
  _GetTaskState = OSServiceId_GetTaskState,

  /* interrupt handling services */
  _ResumeAllInterrupts = OSServiceId_ResumeAllInterrupts,
  _SuspendAllInterrupts = OSServiceId_SuspendAllInterrupts,
  _ResumeOSInterrupts = OSServiceId_ResumeOSInterrupts,
  _SuspendOSInterrupts = OSServiceId_SuspendOSInterrupts,
  _EnableAllInterrupts = OSServiceId_EnableAllInterrupts,
  _DisableAllInterrupts = OSServiceId_DisableAllInterrupts,
  _GetISRID = OSServiceId_GetISRID,

  /* resource management services */
  _GetResource = OSServiceId_GetResource,
  _ReleaseResource = OSServiceId_ReleaseResource,

  /* event control services */
  _SetEvent = OSServiceId_SetEvent,
  _ClearEvent = OSServiceId_ClearEvent,
  _GetEvent = OSServiceId_GetEvent,
  _WaitEvent = OSServiceId_WaitEvent,

  /* counter services */
  _IncrementCounter = OSServiceId_IncrementCounter,
  _GetCounterValue = OSServiceId_GetCounterValue,
  _GetElapsedValue = OSServiceId_GetElapsedValue,
  /* alarms services */
  _GetAlarmBase = OSServiceId_GetAlarmBase,
  _GetAlarm = OSServiceId_GetAlarm,
  _SetRelAlarm = OSServiceId_SetRelAlarm,
  _SetAbsAlarm = OSServiceId_SetAbsAlarm,
  _CancelAlarm = OSServiceId_CancelAlarm,

  /* schedule table services */
  _StartScheduleTableAbs = OSServiceId_StartScheduleTableAbs,
  _StartScheduleTableRel = OSServiceId_StartScheduleTableRel,
  _StopScheduleTable = OSServiceId_StopScheduleTable,
  _NextScheduleTable = OSServiceId_NextScheduleTable,
  _SyncScheduleTable = OSServiceId_SyncScheduleTable,
  _SetScheduleTableAsync = OSServiceId_SetScheduleTableAsync,
  _GetScheduleTableStatus = OSServiceId_GetScheduleTableStatus,
  _StartScheduleTableSynchron = OSServiceId_StartScheduleTableSynchron,

  /* multi-core services */
  _GetSpinlock = OSServiceId_GetSpinlock,
  _TryToGetSpinlock = OSServiceId_TryToGetSpinlock,
  _ReleaseSpinlock = OSServiceId_ReleaseSpinlock,
  _GetCoreID = OSServiceId_GetCoreID,
  _StartCore = OSServiceId_StartCore,

  /* No API service (e.g. Stack Monitoring) */
  _NoAPI = OS_INVALID_VALUE,
} Os_ErrorApiType;

/* polyspace-begin MISRA-C3:19.2 [Not a defect:Low] "These unions are used for debugging purposes only" */
/** This union is defined for first parameter of OS API */
typedef union
{
  AlarmType OsAlarmId;
  ApplicationType OsApplicationId;
  CounterType OsCounterId;
  ResourceType OsResourceId;
  TaskType OsTaskId;
  ScheduleTableType OsScheduleTableId;
  ScheduleTableType OsScheduleTableId_From;
  TrustedFunctionIndexType OsTrustedFunctionIndexId;
  EventMaskType OsMask;
  SpinlockIdType OsSpinlockId;
} Os_ParamBlockType1;

/** This union is defined for second parameter of OS API */
typedef union
{
  ScheduleTableType OsScheduleTableId_To;
  TickType OsValue;
  P2VAR(void, AUTOMATIC, OS_VAR) OsTrustedFunctionParams;
  RestartType OsRestartOption;
  EventMaskType OsMaskParam2;
  TickType OsIncrement;
  TickType OsOffset;
  TickType OsStart;
} Os_ParamBlockType2;

/** This union is defined for third parameter of OS API */
typedef union
{
  TickType OsCycle;
} Os_ParamBlockType3;
/* polyspace-end MISRA-C3:19.2 */

/** This structure is defined for OS error information type */
typedef struct
{
  Os_ErrorApiType enApi;       /**< OS API name */
  Os_ErrorValueType enErrorNo; /**< Error reason */
  Os_ParamBlockType1 unPar1;   /**< OS API first parameter */
  Os_ParamBlockType2 unPar2;   /**< OS API second parameter */
  Os_ParamBlockType3 unPar3;   /**< OS API third parameter */
} Os_ErrorType;

#define OS_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
extern VAR(uint32, OS_VAR) GulOsErrorCount;
extern VAR(uint32, OS_VAR) GulOsErrorLastPosition;
extern VAR(uint32, OS_VAR) Os_GulOsLimitError;
extern VAR(uint32, OS_VAR) Os_GulOsStackFaultError;
#define OS_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_ErrorType, OS_VAR) GucOsError[SZ_OSERROR];
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define OS_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, OS_CODE) Os_UpdateOsErrorInfo(StatusType LddError);
extern FUNC(void, OS_CALLOUT_CODE) AppCallbackOnSystemError(StatusType ErrorId);
#define OS_STOP_SEC_CODE
#include "MemMap.h"

#endif /* OS_HOOK_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:D4.5 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

