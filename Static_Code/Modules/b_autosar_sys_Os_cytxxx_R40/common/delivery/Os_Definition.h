/*******************************************************************************
**                                                                            **
**  (C) 2013-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Definition.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of AUTOSAR OS Standard Type Definitions.            **
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
** 2.6.7     04-Nov-2020    JH.Cho        Redmine #26412                      **
** 2.6.3     04-Jun-2020    MJ.Woo        Redmine #21784                      **
** 2.6.1     06-Mar-2020    MJ.Woo        Redmine #22246                      **
** 2.4.3     27-Mar-2018    SH.Yoo        Redmine #12132                      **
** 2.4.1     14-Sep-2017    MJ.Woo        Redmine #9937                       **
** 2.3.1     04-May-2017    MJ.Woo        Redmine #8275                       **
** 2.3.0     28-Mar-2017    SH.Yoo        Redmine #5967                       **
** 2.0.13    30-Jun-2016    MJ.Woo        Redmine #5368                       **
** 2.0.12    18-Apr-2016    SH.Yoo        Redmine #4686                       **
** 2.0.11    16-Feb-2016    JH.Lee,MJ.Woo Redmine #3963                       **
** 2.0.9     13-Jul-2015    SH.Yoo        Redmine #2849                       **
**           10-Dec-2014    MJ.Woo        Redmine #1189                       **
** 2.0.8     27-Feb-2014    SH.Yoo        TASK: xar~842, Redmine #626         **
** 2.0.4     23-Oct-2013    DG.Lee        CR: xar~179, TASK: xar~736          **
** 2.0.2     10-Sep-2013    MJ.Woo        CR: xar~168, TASK: xar~675          **
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
/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> Function like macro is used to improve performance */


#ifndef OS_DEFINITIONS_H
#define OS_DEFINITIONS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
*                      Services identifiers                                    *
*                                                                              *
*******************************************************************************/
/* Service ID for ActivateTask */
#define OSServiceId_ActivateTask               21

/* Service ID for TerminateTask */
#define OSServiceId_TerminateTask              22

/* Service ID for ChainTask */
#define OSServiceId_ChainTask                  23

/* Service ID for Schedule */
#define OSServiceId_Schedule                   24

/* Service ID for GetTaskID */
#define OSServiceId_GetTaskID                  25

/* Service ID for GetTaskState */
#define OSServiceId_GetTaskState               26

/* Service ID for EnableAllInterrupts */
#define OSServiceId_EnableAllInterrupts        27

/* Service ID for DisableAllInterrupts */
#define OSServiceId_DisableAllInterrupts       28

/* Service ID for ResumeAllInterrupts */
#define OSServiceId_ResumeAllInterrupts        29

/* Service ID for SuspendAllInterrupts */
#define OSServiceId_SuspendAllInterrupts       30

/* Service ID for ResumeOSInterrupts */
#define OSServiceId_ResumeOSInterrupts         31

/* Service ID for SuspendOSInterrupts */
#define OSServiceId_SuspendOSInterrupts        32

/* Service ID for GetResource */
#define OSServiceId_GetResource                33

/* Service ID for ReleaseResource */
#define OSServiceId_ReleaseResource            34

/* Service ID for SetEvent */
#define OSServiceId_SetEvent                   35

/* Service ID for ClearEvent */
#define OSServiceId_ClearEvent                 36

/* Service ID for GetEvent */
#define OSServiceId_GetEvent                   37

/* Service ID for WaitEvent */
#define OSServiceId_WaitEvent                  38

/* Service ID for GetAlarmBase */
#define OSServiceId_GetAlarmBase               39

/* Service ID for GetAlarm */
#define OSServiceId_GetAlarm                   40

/* Service ID for SetRelAlarm */
#define OSServiceId_SetRelAlarm                41

/* Service ID for SetAbsAlarm */
#define OSServiceId_SetAbsAlarm                42

/* Service ID for CancelAlarm */
#define OSServiceId_CancelAlarm                43

/* Service ID for GetActiveApplicationMode */
#define OSServiceId_GetActiveApplicationMode   44

/* Service ID for StartOS */
#define OSServiceId_StartOS                    45

/* Service ID for ShutdownOS */
#define OSServiceId_ShutdownOS                 46

/* Service ID for StartScheduleTableRel */
#define OSServiceId_StartScheduleTableRel      7

/* Service ID for StartScheduleTableAbs */
#define OSServiceId_StartScheduleTableAbs      8

/* Service ID for StopScheduleTable */
#define OSServiceId_StopScheduleTable          9

/* Service ID for NextScheduleTable */
#define OSServiceId_NextScheduleTable          10

/* Service ID for IncrementCounter */
#define OSServiceId_IncrementCounter           15

/* Service ID for GetCounterValue */
#define OSServiceId_GetCounterValue            16

/* Service ID for GetElapsedValue */
#define OSServiceId_GetElapsedValue            17

/* Service ID for GetScheduleTableStatus */
#define OSServiceId_GetScheduleTableStatus     14

/* Service ID for GetTaskID */
#define OSServiceId_GetISRID                   1

/* Service ID for StartScheduleTableSynchron */
#define OSServiceId_StartScheduleTableSynchron 11

/* Service ID for SyncScheduleTable */
#define OSServiceId_SyncScheduleTable          12

/* Service ID for SetScheduleTableAsync */
#define OSServiceId_SetScheduleTableAsync      13

/* Service ID for GetCoreID */
#define OSServiceId_GetCoreID                  47

/* Service ID for GetSpinlock */
#define OSServiceId_GetSpinlock                48

/* Service ID for ReleaseSpinlock */
#define OSServiceId_ReleaseSpinlock            49

/* Service ID for TryToGetSpinlock */
#define OSServiceId_TryToGetSpinlock           50

/* Service ID for GetApplicationID */
#define OSServiceId_GetApplicationID           0x0

/* Service ID for CallTrustedFunction */
#define OSServiceId_CallTrustedFunction        2

/* Service ID for CheckISRMemoryAccess */
#define OSServiceId_CheckISRMemoryAccess       3

/* Service ID for CheckTaskMemoryAccess */
#define OSServiceId_CheckTaskMemoryAccess      4

/* Service ID for CheckObjectAccess */
#define OSServiceId_CheckObjectAccess          5

/* Service ID for CheckObjectOwnership */
#define OSServiceId_CheckObjectOwnership       6

/* Service ID for AllowAccess */
#define OSServiceId_AllowAccess                19

/* Service ID for GetApplicationState */
#define OSServiceId_GetApplicationState        20

/* Service ID for TerminateApplication */
#define OSServiceId_TerminateApplication       18

/* Service ID for StartCore */
#define OSServiceId_StartCore                  55

/* Service ID for ShutdownAllCores */
#define OSServiceId_ShutdownAllCores           56

/* Service ID for Os_IocRead */
#define IOCServiceId_IOC_Read                  60

/* Service ID for Os_IocWrite */
#define IOCServiceId_IOC_Write                 61

/* Service ID for Os_IocPullCB */
#define IOCServiceId_IOC_Receive               62

/* Service ID for Os_IocSend */
#define IOCServiceId_IOC_Send                  63

/* Service ID for Os_IocEmptyQueue */
#define IOCServiceId_IOC_EmptyQueue            64

/* Service ID for Os_IocPullCB */
#define OSServiceId_Os_IocPullCB               65

/* Service ID for Os_ErrorTerminateTask */
#define OSServiceId_Os_ErrorTerminateTask      66

/*
 * @def IOC_E_OK
 *
 * This error code means : No error occurred
 */
#ifndef IOC_E_OK
#define IOC_E_OK                              ((Std_ReturnType) 0)
#endif

/*
 * @def IOC_E_NOK
 *
 * This error code means : Error occurred. Shall be used to identify error
 * cases without error specification.
 */
#ifndef IOC_E_NOK
#define IOC_E_NOK                             ((Std_ReturnType) 1)
#endif

/*
 * @def IOC_E_LIMIT
 *
 * This error code means : In case of "event"(queued) semantic, the internal
 * buffer within the IOC communication service is full (Case: Receiver slower
 * than sender). This error produces additionally an Overlayed Error on the
 * receiver side at the next data reception.
 */
#ifndef IOC_E_LIMIT
#define IOC_E_LIMIT                           ((Std_ReturnType) 130)
#endif

/*
 * @def IOC_E_LOST_DATA
 *
 * This error code means : In case of "event"(queued) semantic, this Overlayed
 * Error indicates that the IOC service refuses an IocSend request due to
 * internal buffer overflow.
 */
#ifndef IOC_E_LOST_DATA
#define IOC_E_LOST_DATA                       ((Std_ReturnType) 64)
#endif

/*
 * @def IOC_E_NO_DATA
 *
 * This error code means : In case of "event"(queued) semantic,
 * no data is available for reception.
 */
#ifndef IOC_E_NO_DATA
#define IOC_E_NO_DATA                         ((Std_ReturnType) 131)
#endif

/*
 * @def E_OS_ACCESS
 *
 * This error code means : calling task is not an extended task
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_ACCESS                           ((uint8) 1)

/*
 * @def E_OS_CALLEVEL
 *
 * This error code means : call at interrupt level
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_CALLEVEL                         ((uint8) 2)

/*
 * @def E_OS_ID
 *
 * This error code means : invalid identifier
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_ID                               ((uint8) 3)

/*
 * @def E_OS_LIMIT
 *
 * This error code means : limit exceeded. The only limit known to raise this
 * error is the number of task activations
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_LIMIT                            ((uint8) 4)

/*
 * @def E_OS_NOFUNC
 *
 * This error code means : not appropriate.
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_NOFUNC                           ((uint8) 5)

/*
 * @def E_OS_RESOURCE
 *
 * This error code means : calling task still occupies resources
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_RESOURCE                         ((uint8) 6)

/*
 * @def E_OS_STATE
 *
 * This error code means : related state not appropriate
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_STATE                            ((uint8) 7)

/*
 * @def E_OS_VALUE
 *
 * This error code means : value outside of the admissible limits
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_VALUE                            ((uint8) 8)

/*
 * @def E_OS_STACKFAULT
 *
 * This error code means : value outside of the admissible limits
 *
 */
#define E_OS_STACKFAULT                       ((uint8) 9)

/*
 * @def E_OS_PROTECTION_ARRIVAL
 *
 * This error code means : value outside of the admissible limits
 *
 */
#define E_OS_PROTECTION_ARRIVAL               ((uint8) 10)

/*
 * @def E_OS_PROTECTION_TIME
 *
 * This error code means : value outside of the admissible limits
 *
 */
#define E_OS_PROTECTION_TIME                  ((uint8) 11)

/*
 * @def E_OS_PROTECTION_LOCKED
 *
 * This error code means : value outside of the admissible limits
 */

#define E_OS_PROTECTION_LOCKED                ((uint8) 12)

/*
 * @def E_OS_MISSINGEND
 *
 * This error code means : Tasks terminates without a TerminateTask()
 *                          or ChainTask() call.
 *
 */
#define E_OS_MISSINGEND                       ((uint8) 35)

/*
 * @def E_OS_DISABLEDINT
 *
 * This error code means : A service of the OS is called inside an interrupt
 *                          disable/enable pair.
 */
#define E_OS_DISABLEDINT                      ((uint8) 13)

/*
 * @def E_OS_PROTECTION_EXCEPTION
 *
 * This error code means : If an instruction exception occurs
 *                          (e.g. division by zero).
 */

#define E_OS_PROTECTION_EXCEPTION             ((uint8) 14)
/*
 * @def E_OS_CORE
 *
 * This error code means : All functions that are not allowed to operate cross
 *               core shall return E_OS_CORE in extended status if
 *               called with parameters that require a cross core
 *               operation
 */

#define E_OS_CORE                             ((uint8) 15)

/*
 * @def E_OS_INTERFERENCE_DEADLOCK
 *
 * This error code means : The function GetSpinlock shall return  this error if
 *                         the spinlock referred by the parameter SpinlockID is
 *                     already occupied by a TASK/ISR2 on the same core.
 */

#define E_OS_INTERFERENCE_DEADLOCK            ((uint8) 16)

/*
 * @def E_OS_NESTING_DEADLOCK
 *
 * This error code means : A TASK tries to occupy the spinlock while holding a
 *              different spinlock in a way that may cause a deadlock.
 */

#define E_OS_NESTING_DEADLOCK                 ((uint8) 17)

/*
 * @def E_OS_SPINLOCK
 *
 * This error code means : This error means de-scheduling with occupied
 *spinlock.
 *
 */

#define E_OS_SPINLOCK                         ((uint8) 18)

/*
 * @def E_OS_SERVICEID
 *
 * This error code means : If the function index in a call of
 *               CallTrustedFunction() is undefined.
 */

#define E_OS_SERVICEID                        ((uint8) 19)
/*
 * @def E_OS_PARAM_POINTER
 *
 * This error code means : If A pointer argument of an API is NULL pointer
 *
 */
#define E_OS_PARAM_POINTER                    ((uint8) 20)
/*
 * @def E_OS_PROTECTION_MEMORY
 *
 * This error code means : A memory access violation occurred
 */
#define E_OS_PROTECTION_MEMORY                ((uint8) 21)
/*
 * @def E_OS_ILLEGAL_ADDRESS
 *
 * This error code means : An invalid address is given as a parameter to a
 *                         service.
 */
#define E_OS_ILLEGAL_ADDRESS                  ((uint8) 22)
/*
 * @def E_OS_SYS_ALARMINUSE
 *
 * This error code means : An invalid address is given as a alarm is in use
 *
 */
#define E_OS_SYS_ALARM_INUSE                  ((uint8) 23)
/*
 * @def E_OS_SYS_RAMECC
 *
 * This error code means : An ECC error has occurred on the RAM
 *
 */
#define E_OS_SYS_RAMECC                       ((uint8) 24)
/*
 * @def E_OS_SYS_DFLASHECC
 *
 * This error code means : An ECC error has occurred on the Data Flash
 *
 */
#define E_OS_SYS_DFLASHECC                    ((uint8) 25)
/*
 * @def E_OS_SYS_PFLASHECC
 *
 * This error code means : An ECC error has occurred on the Program Flash
 *
 */
#define E_OS_SYS_PFLASHECC                    ((uint8) 26)
/*
 * @def E_OS_SYS_CORE_IS_DOWN
 *
 * This error code means : When an inter-core API request is made,
 * the target core on which the API is actually executed is already shutdown
 * and the API request can not be processed.
 *
 */
#define E_OS_SYS_CORE_IS_DOWN                 ((uint8)100)
/*
 * @def E_OS_SYS_PANIC
 *
 * This error code means : A fatal OS error occurs
 *
 */
#define E_OS_SYS_PANIC                        ((uint8)101)
/*
 * @def E_OS_SYS_NMI
 *
 * This error code means : The OS is terminated by NMI
 *
 */
#define E_OS_SYS_NMI                          ((uint8)102)
/*
 * @def E_OS_SYS_INTERCOREMSG
 *
 * This error code means : A problem occurred during the inter-core API
 * request process.
 *
 */
#define E_OS_SYS_INTERCOREMSG                 ((uint8)103)


/******************************************************************************
 **                      Always existing application mode                    **
 *****************************************************************************/

/*
 * @def OSDEFAULTAPPMODE
 *
 * Default application mode, always a valid parameter to StartOS.
 *
 * @see #StartOS
 * @see #AppModeType
 */
#define OSDEFAULTAPPMODE                      ((uint8) 0xfe)

/*
 * @def DONOTCARE
 *
 * Default application mode, always a valid parameter to StartOS.
 *
 * @see #StartOS
 * @see #AppModeType
 */
#define DONOTCARE                             ((uint8) 0xff)

/*******************************************************************************
 *                        Task flags for the type field                        *
 ******************************************************************************/
/*
 * @def TASK_BASIC
 *
 * identifies a Basic task
 *
 */

#define OS_TASK_BASIC                         ((uint8) 0x01)

/*
 * @def TASK_EXTENDED
 *
 * identifies an extended task
 *
 */
#define OS_TASK_EXTENDED                      ((uint8) 0x02)

/*
 * @def OS_ISR2
 *
 * identifies a category 2 Interrupt Service Routine
 *
 */

#define OS_ISR2                               ((uint8) 0x04)

/******************************************************************************
 *                            Tasks states and actions                        *
 *****************************************************************************/

#define OS_TASK_UNINITIALIZED                 ((uint8) 0x0)
/*
 * @def SUSPENDED
 *
 * This is a state of a task
 */
#define SUSPENDED                             ((uint8) 0x4)
/*
 * @def READY
 *
 * This is a state of a task
 */
#define READY                                 ((uint8) 0x2)
/*
 * @def RUNNING
 *
 * This is a state of a task
 */
#define RUNNING                               ((uint8) 0x6)
/*
 * @def WAITING
 *
 * This is a state of a task
 */
#define WAITING                               ((uint8) 0x5)
/*
 * @def DYING
 *
 * This is a state of a task
 */
#define DYING                                 ((uint8) 0xD)
/*
 * @def RESURRECT
 *
 * This is a state of a task
 */
#define RESURRECT                             ((uint8) 0x15)
/*
 * @def OS_READY_AND_NEW
 *
 * This is a state of a task
 */
#define OS_READY_AND_NEW                      ((uint8) 0xA)
/*
 * @def OS_READY_AND_WAITING
 *
 * This is a state of a task
 */
#define OS_READY_AND_WAITING                  ((uint8) 0x1A)

/*
 * @def INVALID_TASK
 *
 * This is a ID of an invalid Task. */
#define INVALID_TASK                          ((TaskType)0xff)

/*
 * @def INVALID_ISR
 *
 * This is a ID of an invalid ISR. */
#define INVALID_ISR                           ((ISRType)0xff)

/******************************************************************************
 * Alarms states and actions                                                  *
 *****************************************************************************/
/*
 * @def OS_ALARM_SLEEP
 *
 * This is a state of a Alarm
 */
#define OS_ALARM_SLEEP                        ((uint8) 0)

/**
 * @def OS_ALARM_ACTIVE
 *
 * This is a state of a Alarm
 */
#define OS_ALARM_ACTIVE                       ((uint8) 1)

/******************************************************************************
 * Schedule Table states and actions                                          *
 *****************************************************************************/
/**
 * @def SCHEDULETABLE_STOPPED
 *
 * This is a state of a ScheduleTable.
 */
#define SCHEDULETABLE_STOPPED                 ((StatusType) 0)

/**
 * @def SCHEDULETABLE_NEXT
 *
 * This is a state of a ScheduleTable.
 */
#define SCHEDULETABLE_NEXT                    ((StatusType) 1)

/**
 * @def SCHEDULETABLE_RUNNING
 *
 * This is a state of a ScheduleTable.
 */
#define SCHEDULETABLE_RUNNING                 ((StatusType) 2)

/**
 * @def SCHEDULETABLE_STOPPED
 *
 * This is a state of a ScheduleTable.
 */
#define SCHEDULETABLE_WAITING                 ((StatusType) 3)

/**
 * @def OS_SCHEDULETABLE_EXP_DEV
 *
 * This is a state of a ScheduleTable.
 */
#define OS_SCHEDULETABLE_EXP_DEV              ((StatusType) 4)

/**
 * @def SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS
 *
 * This is a state of a ScheduleTable.
 */
#define SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS ((StatusType) 5)

/**
 * @def OS_SCHEDULETABLE_EXP_REQ
 *
 * This is a state of a ScheduleTable.
 */
#define OS_SCHEDULETABLE_EXP_REQ              ((StatusType) 6)

/**
 * @def OS_SCHEDULETABLE_EXP_PRE
 *
 * This is a state of a ScheduleTable.
 */
#define OS_SCHEDULETABLE_EXP_PRE              ((StatusType) 7)

/**
 * @def TASK
 *
 * Macro used to define (declare) a task
 *
 * @param Name the name (C identifier) of the task
 */
/* polyspace +2 MISRA-C3:20.10 [Not a defect:Low] "## preprocessor is needed to naming task" */
#define TASK(Name)                       void TASK_##Name(void)

/**
 * @def ISR
 *
 * Macro used to define (declare) a category 2 interrupt service routine.
 *
 * @param Name the name (C identifier) of the IRS
 */

/* polyspace +2 MISRA-C3:20.10 [Not a defect:Low] "## preprocessor is needed to naming ISR" */
#define ISR(Name)                        void ISR_##Name(void)

/**
 * @def OSMEMORY_IS_READABLE
 *
 * Macro to check if memory is readable.
 * For following macros if argument is NO_ACCESS(=1), the macro will negate it
 * as the macro is suppose to return zero in case of NO_ACCESS.
 * Note: changing value of NO_ACCESS as zero will have its side-effects on
 * Error checking. As E_OK is mapped to ACCESS is mapped to OS_ZERO
 */
#define OSMEMORY_IS_READABLE(Argument)\
  ((NO_ACCESS == (Argument)) ? OS_ZERO : OS_ONE)

/**
 * @def OSMEMORY_IS_WRITEABLE
 *
 * Macro to check if memory is Writeable.
 */
#define OSMEMORY_IS_WRITEABLE(Argument)\
((OS_READ_WRITE == (Argument)) ? OS_ONE : OS_ZERO)

/**
 * @def OSMEMORY_IS_STACKSPACE
 *
 * Macro to check if memory is in stack space.
 */
#define OSMEMORY_IS_STACKSPACE(Argument)\
  ((OS_READ_WRITE == (Argument)) ? OS_ONE : OS_ZERO)

/**
 * @def OSMEMORY_IS_STACKSPACE
 *
 * Macro to check if memory is in stack space. This Will always return that the
 * memory is executable
 */
#define OSMEMORY_IS_EXECUTABLE(Argument) \
                     ((OS_EXECUTE == ((Argument) & OS_EXECUTE)) ? OS_ONE : OS_ZERO)

/**
 * @def ALARMCALLBACK
 *
 * Macro used to define an alarm callback function
 *
 * @param Name callback name
 *
 * @warning don't be confused with ALARM_CALLBACK
 */
/* polyspace +2 MISRA-C3:20.10 [Not a defect:Low] "## preprocessor is needed to naming alarm callback" */
#define ALARMCALLBACK(Name)              void OSALMCB_##Name(void)

/**
 * @def ACCESS
 *
 * Return for accessible.
 *
 * @param access return values
 *
 */
#define ACCESS                                ((ObjectAccessType)0x0)

/**
 * @def NO_ACCESS
 *
 * Return for non-accessible.
 *
 * @param access return values
 *
 */
#define NO_ACCESS                             ((ObjectAccessType)0x1)
/**
 * @def OS_FULLACCESS
 *
 * Return for Fully-accessible.
 *
 * @param access return values
 *
 */
/* polyspace<MISRA-C3:7.3:Not a defect:Justify with annotations> macro shall be uppercase character */
#define OS_FULLACCESS                         0xFFFFFFFFul
/**
 * @def CoreIDType
 *
 * Macro used to remove the case sensitivity
 *
 */
/* polyspace<MISRA-C:19.4:Not a defect:Justify with annotations> Definition for function redirection does not use parenthesised expression */
#define CoreIDType                            CoreIdType
/**
 * @def INVALID_OSAPPLICATION
 *
 * This is a ID of an invalid application.
 */
#define INVALID_OSAPPLICATION                 ((ApplicationType)0xff)
/**
 * @def APPLICATION_ACCESSIBLE
 *
 * This is a state of a Application.
 */
#define APPLICATION_ACCESSIBLE                ((ApplicationStateType) 0x00)
/**
 * @def APPLICATION_RESTARTING
 *
 * This is a state of a Application.
 */
#define APPLICATION_RESTARTING                ((ApplicationStateType) 0x01)
/**
 * @def APPLICATION_TERMINATED
 *
 * This is a state of a Application.
 */
#define APPLICATION_TERMINATED                ((ApplicationStateType) 0x02)
/**
 * @def OS_TRUSTED
 *
 * Type of a Application.
 */
#define OS_TRUSTED                            ((uint8)255)
/**
 * @def OS_NON_TRUSTED
 *
 * Type of a Application.
 */
#define OS_NON_TRUSTED                        ((uint8)254)
/**
 * @def OBJECT_TASK
 *
 * Type of a Object.
 */
#define OBJECT_TASK                           ((ObjectTypeType)0x0)
/**
 * @def OBJECT_ISR
 *
 * Type of a Object.
 */
#define OBJECT_ISR                            ((ObjectTypeType)0x1)
/**
 * @def OBJECT_ALARM
 *
 * Type of a Object.
 */
#define OBJECT_ALARM                          ((ObjectTypeType)0x2)
/**
 * @def OBJECT_RESOURCE
 *
 * Type of a Object.
 */
#define OBJECT_RESOURCE                       ((ObjectTypeType)0x3)
/**
 * @def OBJECT_COUNTER
 *
 * Type of a Object.
 */
#define OBJECT_COUNTER                        ((ObjectTypeType)0x4)
/**
 * @def OBJECT_SCHEDULETABLE
 *
 * Type of a Object.
 */
#define OBJECT_SCHEDULETABLE                  ((ObjectTypeType)0x5)
/**
 * @def OS_SCHEDTABLE_NONE_SYNC
 *
 * Synchronization Strategy of Schedule Table.
 */
#define OS_SCHEDTABLE_NONE_SYNC               ((uint8) 0)
/**
 * @def OS_SCHEDTABLE_EXPLICIT_SYNC
 *
 * Synchronization Strategy of Schedule Table.
 */
#define OS_SCHEDTABLE_EXPLICIT_SYNC           ((uint8) 1)
/**
 * @def OS_SCHEDTABLE_IMPLICIT_SYNC
 *
 * Synchronization Strategy of Schedule Table.
 */
#define OS_SCHEDTABLE_IMPLICIT_SYNC           ((uint8) 2)
/**
 * @def OS_CAT1_ISR
 *
 * Type of ISR.
 */
#define OS_CAT1_ISR                           (0x0u)
/**
 * @def OS_CAT2_ISR
 *
 * Type of ISR.
 */
#define OS_CAT2_ISR                           (0x1u)
/**
 * @def OS_CAT2_TP
 *
 * Type of ISR.
 */
#define OS_CAT2_TP                            (0x2u)
/**
 * @def OS_CAT2_WO_ISR
 *
 * Type of ISR.
 */
#define OS_CAT2_WO_ISR                        (0x3u)
/**
 * @def RESTART
 *
 * Restart Option.
 */
#define RESTART                               ((RestartType)(0))
/**
 * @def NO_RESTART
 *
 * Restart Option.
 */
#define NO_RESTART                            ((RestartType)(0x1))
/**
 * @def OS_SOFTWARE_COUNTER
 *
 * Type of Counter.
 */
#define OS_SOFTWARE_COUNTER                   ((sint8) 0x0)
/**
 * @def OS_HARDWARE_COUNTER
 *
 * Type of Counter.
 */
#define OS_HARDWARE_COUNTER                   ((sint8) 0x01)
/**
 * @def PRO_TERMINATETASKISR
 *
 * return from ProtectionHook.
 */
#define PRO_TERMINATETASKISR                  0x00
/**
 * @def PRO_TERMINATEAPPL
 *
 * return from ProtectionHook.
 */
#define PRO_TERMINATEAPPL                     0x01
/**
 * @def PRO_TERMINATEAPPL_RESTART
 *
 * return from ProtectionHook.
 */
#define PRO_TERMINATEAPPL_RESTART             0x02
/**
 * @def PRO_SHUTDOWN
 *
 * return from ProtectionHook.
 */
#define PRO_SHUTDOWN                          0x03
/**
 * @def PRO_IGNORE
 *
 * return from ProtectionHook.
 */
#define PRO_IGNORE                            0x04

/* Os Internal Macros for values */
#define OS_FALSE                              ((uint8) 0x00)
#define OS_TRUE                               ((uint8) 0x01)
#define OS_ZERO                               0x00
#define OS_PRE_ZERO                           0x00
#define OS_PRE_ONE                            0x01
#define OS_ONE                                0x01
#define OS_TWO                                0x02
#define OS_THREE                              0x03
#define OS_FOUR                               0x04
#define OS_FIVE                               0x05
#define OS_SIX                                0x06
#define OS_SEVEN                              0x07
#define OS_EIGHT                              0x08
#define OS_NINE                               0x09
#define OS_TEN                                0x0A
#define OS_ELEVEN                             0x0B
#define OS_TWELVE                             0x0C
#define OS_THIRTEEN                           0x0D
#define OS_FOURTEEN                           0x0E
#define OS_FIFTEEN                            0x0F
#define OS_THOUSAND                           (1000u)
#define OS_MILLION                            (1000000u)
#define OS_LONG_BIT_COUNT                     0x20
#define OS_SECOND_STEP                        0x02
#define OS_THIRD_STEP                         0x03
#define OS_INVALID_VALUE                      ((uint8) 0xFF)
#define OS_INVALID_MASK                       ((uint32) 0xFFFFFFFFu)
#define OS_MINUS_ONE                          ((sint8)(-1))
#define OS_INVALID_PRIORITY                   ((sint8)(-1))
#define OS_RES_SCHEDULER_PRIORITY             ((sint8) 0x02)
#define USER0                                 0x00
/* FIXME: OS_DEFECT_27 Resource extension to interrupts. */
/* NOTE: Os_GaaHardWareResource[] generator update required. */
#define OS_INVALID_HW_PRIORITY                ((uint32) 0xFFFFFFFFu)
#define OS_UINT_MAX                           ((uint32) 0xFFFFFFFFu)

/* Os Internal Status return values */
#define OS_E_OK_AND_SCHEDULE                  ((StatusType) 0x40)
#define OS_E_OK_AND_LOAD                      ((StatusType) 0x80)
#define OS_STATUS_MASK                        ((StatusType) 0x1f)
#define OS_TASK_STATUS                        ((StatusType) 0x07)
#define OS_SLEEP                              ((uint8) 0x01)
#define OS_CAN_BE_ACTIVATED                   ((uint8) 0x00)
#define OS_ALREADY_ACTIVATED                  ((uint8) 0x01)
#define OS_E_OK_AND_RESTARTAPPL               ((StatusType) 0x50)
#define OS_E_OK_AND_TERMINATEAPPL             ((StatusType) 0x60)

/* Macro for access, according to linux permission style */
#define OS_READ_ONLY                          0x4
#define OS_READ_WRITE                         0x6
#define OS_EXECUTE                            0x7


/* Scalability class */
#define OS_SC1                                0x1
#define OS_SC2                                0x2
#define OS_SC3                                0x3
#define OS_SC4                                0x4

/* Os status*/
#define STANDARD                              0x1
#define EXTENDED                              0x2

/******************************************************************************
**                      Function Prototypes                                  **
******************************************************************************/

#endif /* OS_DEFINITION_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> Function like macro is used to improve performance */

/******************************************************************************
**                      End of File                                          **
******************************************************************************/
