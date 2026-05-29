/*******************************************************************************
**                                                                            **
**  (C) 2013-2017 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_ErrorExternal.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file containing the declaration of                     **
**              Hook functionality related functions.                         **
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
** 2.4.1     14-Sep-2017    MJ.Woo        Redmine #9937                       **
** 2.0.13    30-Jun-2016    MJ.Woo        Redmine #4595, 5368                 **
** 2.0.11    16-Feb-2016    JH.Lee,MJ.Woo Redmine #3963                       **
** 2.0.10    09-Dec-2015    SH.Yoo        Redmine #1661                       **
** 2.0.4     11-Nov-2013    SH.Yoo        CR: xar~179, TASK: xar~736          **
**           23-Oct-2013    DG.Lee        CR: xar~179, TASK: xar~736          **
** 2.0.3     16-Sep-2013    SH.Yoo        CR: xar~172, TASK: xar~691          **
** 2.0.0     22-Jul-2013    JH.Son,SH.Yoo CR: xar~107, TASK: xar~543          **
**                          DG.Lee,MJ.Woo                                     **
*******************************************************************************/
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Inline functions are needed for performance and Macro definitions are needed for performance and file size  */
/* polyspace:begin<MISRA-C:8.1:Not a defect:Justify with annotations> Prototype declaration of inline function is not needed */
/* polyspace:begin<MISRA-C:8.5:Not a defect:Justify with annotations> Inline functions should be implemented in header file  */
/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> Function like macro is used to improve performance */
/* polyspace:begin<MISRA-C3:8.10:Not a defect:Justify with annotations> inline function is verified manually */
/* polyspace:begin<RTE:OBAI:Not a defect:Justify with annotations> array index points pre-defined size */
#ifndef OS_ERROREXTERNAL_H
#define OS_ERROREXTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Ram.h"
#include "Os_Cfg.h"
#include "Os_Multicore.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
#define OS_PROCESS_ERROR(Error) (Os_ErrorHook(Error))
#else
#define OS_PROCESS_ERROR(Error)
#endif

#if (OS_ERROR_HOOK == STD_ON)
#define OS_STORE_SERVICE(Service)\
  do{ \
    Os_GddServiceCall[OS_CORE_ID].ucServiceID = (uint8)(Service); \
  } while(0)
#else
#define OS_STORE_SERVICE(Service)
#endif

/* polyspace:begin<MISRA-C:19.10:Not a defect:Justify with annotations> Left operand cannot be enclosed in parentheses */
#if (OS_STATUS == STANDARD)
#define OS_CHECK_NULL_PTR(Value, LenStatusReturn)
#else
#define OS_CHECK_NULL_PTR(Value, LenStatusReturn)\
  do{ \
    if (((LenStatusReturn) == E_OK) && ((Value) == NULL_PTR))\
    {\
      LenStatusReturn = E_OS_PARAM_POINTER;\
    } \
  } while(0)
#endif
/* polyspace:end<MISRA-C:19.10:Not a defect:Justify with annotations> Left operand cannot be enclosed in parentheses */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
extern FUNC(void, OS_CODE) Os_ErrorHook(StatusType Error);
#endif /* End of if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
        */

#if (OS_ERROR_HOOK == STD_ON)

#if (OS_USE_GET_SERVICE_ID == STD_ON)
inline OSServiceIdType OSErrorGetServiceId(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ucServiceID;
}
#else
#define OSErrorGetServiceId()
#endif

#if (OS_USER_PARAMETER_ACCESS == STD_ON)

/* CallTrustedFunction - FunctionIndex, FunctionParams */
inline TrustedFunctionIndexType OSError_CallTrustedFunction_FunctionIndex(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.FunctionIndex;
}

/* polyspace:begin<MISRA-C3:5.1:Not a defect:Justify with annotations> macro is unique */
inline TrustedFunctionParameterRefType \
                                OSError_CallTrustedFunction_FunctionParams(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.FunctionParams;
}
/* polyspace:end<MISRA-C3:5.1> */

/* StartScheduleTableRel - ScheduleTableID, Offset */
inline ScheduleTableType OSError_StartScheduleTableRel_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

inline TickType OSError_StartScheduleTableRel_Offset(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Offset;
}

/* StartScheduleTableAbs - ScheduleTableID, Start */
inline ScheduleTableType OSError_StartScheduleTableAbs_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

/* polyspace<MISRA-C3:5.1:Not a defect:Justify with annotations> macro is unique */
inline TickType OSError_StartScheduleTableAbs_Start(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Start;
}

/* StopScheduleTable - ScheduleTableID */
inline ScheduleTableType OSError_StopScheduleTable_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

/* NextScheduleTable - ScheduleTableID_From, ScheduleTableID_To */
inline ScheduleTableType OSError_NextScheduleTable_ScheduleTableIDFrom(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID_From;
}

/* polyspace<MISRA-C3:5.1:Not a defect:Justify with annotations> macro is unique */
inline ScheduleTableType OSError_NextScheduleTable_ScheduleTableIDTo(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.ScheduleTableID_To;
}

/* StartScheduleTableSynchron - ScheduleTableID */
inline ScheduleTableType OSError_StartScheduleTableSynchron_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

/* SyncScheduleTable - ScheduleTableID, Value */
inline ScheduleTableType OSError_SyncScheduleTable_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

inline TickType OSError_SyncScheduleTable_Value(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Value;
}

/* SetScheduleTableAsync - ScheduleTableID */
inline ScheduleTableType OSError_SetScheduleTableAsync_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

/* GetScheduleTableStatus - ScheduleTableID, ScheduleStatus */
inline ScheduleTableType OSError_GetScheduleTableStatus_ScheduleTableID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ScheduleTableID;
}

/* polyspace:begin<MISRA-C3:5.1:Not a defect:Justify with annotations> macro is unique */
inline ScheduleTableStatusRefType \
                             OSError_GetScheduleTableStatus_ScheduleStatus(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.ScheduleStatus;
}
/* polyspace:end<MISRA-C3:5.1> */

/* IncrementCounter - CounterID */
inline CounterType OSError_IncrementCounter_CounterID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.CounterID;
}

/* GetCounterValue - CounterID, Value */
inline CounterType OSError_GetCounterValue_CounterID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.CounterID;
}

inline TickRefType OSError_GetCounterValue_Value(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.ValueRef;
}

/* GetElapsedValue - CounterID, Value, ElapsedValue */
inline CounterType OSError_GetElapsedValue_CounterID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.CounterID;
}

inline TickRefType OSError_GetElapsedValue_Value(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.ValueRef;
}

inline TickRefType OSError_GetElapsedValue_ElapsedValue(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.ElapsedValue;
}

/* TerminateApplication - Application, RestartOption */
inline ApplicationType OSError_TerminateApplication_Application(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Application;
}

inline RestartType OSError_TerminateApplication_RestartOption(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.RestartOption;
}

/* GetApplicationState - Application, Value */
inline ApplicationType OSError_GetApplicationState_Application(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Application;
}

inline ApplicationStateRefType OSError_GetApplicationState_Value(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.AppValueRef;
}

/* ActivateTask - TaskID */
inline TaskType OSError_ActivateTask_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

/* ChainTask - TaskID */
inline TaskType OSError_ChainTask_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

/* GetTaskID - TaskID */
inline TaskRefType OSError_GetTaskID_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskIDRef;
}

/* GetTaskState - TaskID, State */
inline TaskType OSError_GetTaskState_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

inline TaskStateRefType OSError_GetTaskState_State(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.State;
}

/* GetResource - ResID */
inline ResourceType OSError_GetResource_ResID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ResID;
}

/* ReleaseResource - ResID */
inline ResourceType OSError_ReleaseResource_ResID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.ResID;
}

/* SetEvent - TaskID, Mask */
inline TaskType OSError_SetEvent_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

inline EventMaskType OSError_SetEvent_Mask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Mask;
}

/* ClearEvent - Mask */
inline EventMaskType OSError_ClearEvent_Mask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Mask;
}

/* GetEvent - TaskID, Event */
inline TaskType OSError_GetEvent_TaskID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.TaskID;
}

inline EventMaskRefType OSError_GetEvent_Event(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Event;
}

/* WaitEvent - Mask */
inline EventMaskType OSError_WaitEvent_Mask(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.Mask;
}

/* GetAlarmBase - AlarmID, Info */
inline AlarmType OSError_GetAlarmBase_AlarmID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.AlarmID;
}

inline AlarmBaseRefType OSError_GetAlarmBase_Info(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Info;
}

/* GetAlarm - AlarmID, Tick */
inline AlarmType OSError_GetAlarm_AlarmID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.AlarmID;
}

inline TickRefType OSError_GetAlarm_Tick(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Tick;
}

/* SetRelAlarm - AlarmID, Increment, Cycle */
inline AlarmType OSError_SetRelAlarm_AlarmID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.AlarmID;
}

inline TickType OSError_SetRelAlarm_Increment(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Increment;
}

inline TickType OSError_SetRelAlarm_Cycle(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.Cycle;
}

/* SetAbsAlarm - AlarmID, Start, Cycle */
inline AlarmType OSError_SetAbsAlarm_AlarmID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.AlarmID;
}

inline TickType OSError_SetAbsAlarm_Start(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Start;
}

inline TickType OSError_SetAbsAlarm_Cycle(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam3.Cycle;
}

/* CancelAlarm - AlarmID */
inline AlarmType OSError_CancelAlarm_AlarmID(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.AlarmID;
}

/* GetSpinlock - SpinlockId */
inline SpinlockIdType OSError_GetSpinlock_SpinlockId(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.SpinlockId;
}

/* ReleaseSpinlock - SpinlockId */
inline SpinlockIdType OSError_ReleaseSpinlock_SpinlockId(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.SpinlockId;
}

/* TryToGetSpinlock - SpinlockId, Success */
inline SpinlockIdType OSError_TryToGetSpinlock_SpinlockId(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam1.SpinlockId;
}

inline TryToGetSpinlockType* OSError_TryToGetSpinlock_Success(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  return Os_GddServiceCall[OS_CORE_ID].ddParameters.unParam2.Success;
}

#else

/* CallTrustedFunction - FunctionIndex, FunctionParams */
#define OSError_CallTrustedFunction_FunctionIndex()
#define OSError_CallTrustedFunction_FunctionParams()

/* StartScheduleTableRel - ScheduleTableID, Offset */
#define OSError_StartScheduleTableRel_ScheduleTableID()
#define OSError_StartScheduleTableRel_Offset()

/* StartScheduleTableAbs - ScheduleTableID, Start */
#define OSError_StartScheduleTableAbs_ScheduleTableID()
#define OSError_StartScheduleTableAbs_Start()

/* StopScheduleTable - ScheduleTableID */
#define OSError_StopScheduleTable_ScheduleTableID()

/* NextScheduleTable - ScheduleTableID_From, ScheduleTableID_To */
#define OSError_NextScheduleTable_ScheduleTableID_From()
#define OSError_NextScheduleTable_ScheduleTableID_To()

/* StartScheduleTableSynchron - ScheduleTableID */
#define OSError_StartScheduleTableSynchron_ScheduleTableID()

/* SyncScheduleTable - ScheduleTableID, Value */
#define OSError_SyncScheduleTable_ScheduleTableID()
#define OSError_SyncScheduleTable_Value()

/* SetScheduleTableAsync - ScheduleTableID */
#define OSError_SetScheduleTableAsync_ScheduleTableID()

/* GetScheduleTableStatus - ScheduleTableID, ScheduleStatus */
#define OSError_GetScheduleTableStatus_ScheduleTableID()
#define OSError_GetScheduleTableStatus_ScheduleStatus()

/* IncrementCounter - CounterID */
#define OSError_IncrementCounter_CounterID()

/* GetCounterValue - CounterID, Value */
#define OSError_GetCounterValue_CounterID()
#define OSError_GetCounterValue_Value()

/* GetElapsedValue - CounterID, Value, ElapsedValue */
#define OSError_GetElapsedValue_CounterID()
#define OSError_GetElapsedValue_Value()
#define OSError_GetElapsedValue_ElapsedValue()

/* TerminateApplication - Application, RestartOption */
#define OSError_TerminateApplication_Application()
#define OSError_TerminateApplication_RestartOption()

/* GetApplicationState - Application, Value */
#define OSError_GetApplicationState_Application()
#define OSError_GetApplicationState_Value()

/* ActivateTask - TaskID */
#define OSError_ActivateTask_TaskID()

/* ChainTask - TaskID */
#define OSError_ChainTask_TaskID()

/* GetTaskID - TaskID */
#define OSError_GetTaskID_TaskID()

/* GetTaskState - TaskID, State */
#define OSError_GetTaskState_TaskID()
#define OSError_GetTaskState_State()

/* GetResource - ResID */
#define OSError_GetResource_ResID()

/* ReleaseResource - ResID */
#define OSError_ReleaseResource_ResID()

/* SetEvent - TaskID, Mask */
#define OSError_SetEvent_TaskID()
#define OSError_SetEvent_Mask()

/* ClearEvent - Mask */
#define OSError_ClearEvent_Mask()

/* GetEvent - TaskID, Event */
#define OSError_GetEvent_TaskID()
#define OSError_GetEvent_Event()

/* WaitEvent - Mask */
#define OSError_WaitEvent_Mask()

/* GetAlarmBase - AlarmID, Info */
#define OSError_GetAlarmBase_AlarmID()
#define OSError_GetAlarmBase_Info()

/* GetAlarm - AlarmID, Tick */
#define OSError_GetAlarm_AlarmID()
#define OSError_GetAlarm_Tick()

/* SetRelAlarm - AlarmID, Increment, Cycle */
#define OSError_SetRelAlarm_AlarmID()
#define OSError_SetRelAlarm_Increment()
#define OSError_SetRelAlarm_Cycle()

/* SetAbsAlarm - AlarmID, Start, Cycle */
#define OSError_SetAbsAlarm_AlarmID()
#define OSError_SetAbsAlarm_Start()
#define OSError_SetAbsAlarm_Cycle()

/* CancelAlarm - AlarmID */
#define OSError_CancelAlarm_AlarmID()

/* GetSpinlock - SpinlockId */
#define OSError_GetSpinlock_SpinlockId()

/* ReleaseSpinlock - SpinlockId */
#define OSError_ReleaseSpinlock_SpinlockId()

/* TryToGetSpinlock - SpinlockId, Success */
#define OSError_TryToGetSpinlock_SpinlockId()
#define OSError_TryToGetSpinlock_Success()

#endif /*#if (OS_USER_PARAMETER_ACCESS == STD_ON)*/

#endif /* Error Hook */



#endif /* OS_ERROR_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Inline functions are needed for performance and Macro definitions are needed for performance and file size  */
/* polyspace:end<MISRA-C:8.1:Not a defect:Justify with annotations> Prototype declaration of inline function is not needed */
/* polyspace:end<MISRA-C:8.5:Not a defect:Justify with annotations> Inline functions should be implemented in header file  */
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> Function like macro is used to improve performance */
/* polyspace:end<MISRA-C3:8.10> */
/* polyspace:end<RTE:OBAI> */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
