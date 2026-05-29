/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"
#include "App_OsHook.h"
#include "EcuM.h"
#if (OS_ERRM_USED == STD_ON)
#include "ErrM.h"
#endif
#include "Opf_OsProfiler.h"
#include "Gpt.h"
#include "Gpt_Cfg.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE
#include "MemMap.h"

FUNC(void, OS_CODE) ErrorHook(StatusType Error)
{
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OS_MULTICORE == STD_ON)
  CoreIDType LddCoreId = GetCoreID();
  #endif
  /* Do not modify : Start */
  if (E_OS_LIMIT == Error)
  {
    #if (OPF_PROFILE_ENABLED == STD_ON)
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    if (LddCoreId <= OS_CORE_TWO)
    #else
    #if (OS_MULTICORE == STD_ON)
    if (LddCoreId == OS_CORE_ZERO)
    #endif
    #endif
    {
      Opf_SetLimitErrorEvent();
    }
    #endif
  }
  #endif
  AppCallbackOnSystemError(Error);
  /* Do not modify : End */
}

FUNC(void, OS_CODE) PreTaskHook(void)
{
}

FUNC(void, OS_CODE) PostTaskHook(void)
{
}

FUNC(void, OS_CODE) StartupHook(void)
{
  /* Do not modify : Start */
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OS_MULTICORE == STD_ON)
  CoreIDType LddCoreId = GetCoreID();
  #else
  CoreIDType LddCoreId = (CoreIDType)OS_ZERO;
  #endif

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreId <= OS_CORE_TWO)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreId == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_InitOsProfiler();
    Opf_StartOsProfiler();
  }
  #endif

  /* If OS timer is Software, user must activated the below code */
  //Gpt_StopTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_STM);
  //Gpt_EnableNotification(GptConf_GptChannelConfiguration_GptChannelConfiguration_STM);
  //Gpt_StartTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_STM, 1250); /* 1000000 * 0.00125 */

  #if (OS_DEBUG_STACKDEPTH == STD_ON)
  Os_FillStackPattern();
  #endif

  #if (OS_DEBUG_CPULOAD == STD_ON)
  Os_InitCPULoad();
  #endif
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_IsrEntryHook(CoreIDType LddCoreId, ISRType LddIsrId)
{
  /* Do not modify : Start */
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreId <= OS_CORE_TWO)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreId == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetPreIsrEvent();
  }
  #endif

  /* CPU/Interrupt load */
  #if (OS_DEBUG_CPULOAD == STD_ON)
  Os_ITEntryForCPULoad();
  #endif
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_IsrExitHook(CoreIDType LddCoreId, ISRType LddIsrId)
{
  /* Do not modify : Start */
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreId <= OS_CORE_TWO)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreId == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetPostIsrEvent();
  }
  #endif

  /* CPU/Interrupt load */
  #if (OS_DEBUG_CPULOAD == STD_ON)
  Os_ITExitForCPULoad();
  #endif
  /* Do not modify : End */
}

FUNC(void, OS_CODE) ShutdownHook(StatusType Error)
{
  /* Do not modify : Start */
  AppCallbackOnSystemError(Error);
  EcuM_Shutdown();
  /* Do not modify : End */
}

FUNC(void, OS_CODE) AppCallbackOnSystemError(StatusType ErrorId)
{
  if (ErrorId == E_OS_SYS_RAMECC)
  {
    /* RAM ECC Error occurred!!
     * All global variables are cleared before call this callback */
  }
  else
  {
    /* Do not modify : Start */
    Os_UpdateOsErrorInfo(ErrorId);
    #if (OS_ERRM_USED == STD_ON)
    ErrM_OsErrorNotification(Error);
    #endif
    /* Do not modify : End */
  }
}

FUNC(void, OS_CODE) Os_TaskActivationHook(CoreIDType LddCoreId, TaskType LddTaskId)
{
  /* Do not modify : Start */
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreId <= OS_CORE_TWO)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreId == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetTaskEvent((OpfTaskIDType)LddTaskId, OPF_TASK_ACTIVATED);
  }
  #endif
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskTerminationHook(CoreIDType LddCoreId, TaskType LddTaskId)
{
  /* Do not modify : Start */
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreId <= OS_CORE_TWO)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreId == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetTaskEvent((OpfTaskIDType)LddTaskId, OPF_TASK_SUSPENDED);
  }
  #endif
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskPreemptionHook(CoreIDType LddCoreId, TaskType LddTaskId)
{
  /* Do not modify : Start */
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreId <= OS_CORE_TWO)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreId == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetTaskEvent((OpfTaskIDType)LddTaskId, OPF_TASK_READY);
  }
  #endif
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskRunningHook(CoreIDType LddCoreId, TaskType LddTaskId, TaskStateType LddTaskState)
{
  /* Do not modify : Start */
  #if (OPF_PROFILE_ENABLED == STD_ON)
  OpfRecModeType LddOpfMode;
  LddOpfMode = Opf_GetOsProfilerRecMode();

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreId <= OS_CORE_TWO)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreId == OS_CORE_ZERO)
  #endif
  #endif
  {
    /* Check restart */
    if (LddOpfMode == OPF_RECMODE_RESTART)
    {
      Opf_RestartOsProfiler();
    }
    Opf_SetTaskEvent((OpfTaskIDType)LddTaskId, OPF_TASK_RUNNING);
  }
  #endif
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskWaitingHook(CoreIDType LddCoreId, TaskType LddTaskId)
{
  /* Do not modify : Start */
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreId <= OS_CORE_TWO)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreId == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetTaskEvent((OpfTaskIDType)LddTaskId, OPF_TASK_WAITING);
  }
  #endif
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskReleaseHook(CoreIDType LddCoreId, TaskType LddTaskId)
{
  /* Do not modify : Start */
  #if (OPF_PROFILE_ENABLED == STD_ON)
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (LddCoreId <= OS_CORE_TWO)
  #else
  #if (OS_MULTICORE == STD_ON)
  if (LddCoreId == OS_CORE_ZERO)
  #endif
  #endif
  {
    Opf_SetTaskEvent((OpfTaskIDType)LddTaskId, OPF_TASK_READY);
  }
  #endif
  /* Do not modify : End */
}

FUNC(void, OS_CODE) Os_TaskKillHook(CoreIDType LddCoreId, TaskType LddTaskId)
{
}

FUNC(void, OS_CODE) Os_IsrKillHook(CoreIDType LddCoreId, ISRType LddIsrId)
{
  #if (OS_DEBUG_CPULOAD == STD_ON)
  Os_ITExitForCPULoad();
  #endif
}

FUNC(void, OS_CODE) Os_IdleEntryHook(CoreIDType LddCoreId)
{
}

FUNC(void, OS_CODE) Os_IdleExitHook(CoreIDType LddCoreId)
{
}

FUNC(void, OS_CODE) Os_PreRamInitCallout(void)
{
}

FUNC(void, OS_CODE) Os_PostRamInitCallout(void)
{
}

FUNC(void, OS_CODE) Os_MeasureCPULoadRun(void)
{
  /* Do not modify : Start */
  #if (OS_DEBUG_CPULOAD == STD_ON)
  Os_MeasureCPULoad();
  #endif
  /* Do not modify : End */
}
FUNC(void, OS_CODE) Gpt_Os_Sys_Timer_Notif(void)
{
  (void)IncrementCounter(OsCounter_0);
}

#define OS_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

