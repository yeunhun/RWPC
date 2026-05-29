/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_ReceiveEvent.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Implementation of ReceiveEvent module                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE: OBAI : Not a defect : Justify with annotations > configured array index */

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.5.4     14-Dec-2021    YH.Han        Redmine #33412, #33448              **
** 1.5.3     08-Jan-2021    YH.Han        Redmine #27601                      **
** 1.5.2     24-Nov-2020    YH.Han        Redmine #26755                      **
** 1.3.0     29-Oct-2018    YH.Han        Redmine #12853                      **
** 1.2.0     09-Mar-2018    YH.Han        Redmine #10251                      **
** 1.1.2     22-Aug-2017    MJ.Woo        Redmine #6959                       **
** 1.1.0     24-Nov-2016    SH.Yoo        Redmine #6849, #6755, #6847         **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include <string.h>
#include "Opf_Cfg.h"
#include "Opf_ReceiveEvent.h"
#include "Opf_ControlEventQueue.h"
#include "Opf_TimeService.h"
#include "Opf_Ram.h"
#include "Opf_Port.h"
#include "Opf_Task.h"
#include "Opf_OsProfiler.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OPF_START_SEC_CODE
#include "MemMap.h"

/***************************************************************************//**
 * Function             : Opf_SetPreTaskEvent
 *
 * Service ID           : NA
 *
 * Description          : This function is called from PreTaskHook
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddOsProfiler, Opf_GaaTaskCache
 *
 *                        Function(s) invoked    :
 *                        Opf_PortProcessPreTask(), Opf_RestartOsProfiler(),
 *                        Opf_PortGetTaskID(), Opf_GetLastEvent(),
 *                        Opf_PortGetTaskState(), Opf_GetLastProfileEvent(),
 *                        Opf_UpdateTaskInfo(), Opf_ValidateTask(),
 *                        Opf_SaveTimeStamp(), Opf_AddNewEvent()
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
/* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
FUNC(void, OPF_CODE) Opf_SetPreTaskEvent(void)
{
  Tdd_Opf_Event LddEventEntry;
  Tdd_Opf_Event *pLastEventEntry;
  Tdd_Opf_Event *pLastProfileEventEntry;
  OpfTaskIDType LddOpfTaskID;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  LddCoreID = GetCoreID();
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  #endif

  /* Process PreTask for system specific job */
    /* polyspace<MISRA-C3:2.2:Not a defect:Justify with annotations> used for future job */
  Opf_PortProcessPreTask();

  /* Check restart */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if(pCoreOsProfiler->ddRecMode == OPF_RECMODE_RESTART)
  #else
  if(Opf_GddOsProfiler.ddRecMode == OPF_RECMODE_RESTART)
  #endif
  {
    Opf_RestartOsProfiler();
  }

  /* Get Task ID */
  LddOpfTaskID = (OpfTaskIDType)Opf_PortGetTaskID();

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if(pCoreOsProfiler->ddRecMode != OPF_RECMODE_STOP)
  #else
  if(Opf_GddOsProfiler.ddRecMode != OPF_RECMODE_STOP)
  #endif
  {
    /* polyspace:begin<DEFECT:NULL_PTR:Not a defect:Justify with annotations> below ptr does not indicate NULL because it indicates a valid area of pre-defined array */
    /* Update the last event's state */
    pLastEventEntry = Opf_GetLastEvent();
    /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Pointer only accesses the range that is configured by user */
    /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
    if (pLastEventEntry != NULL_PTR)
    {
      if((pLastEventEntry->ddObject == OPF_OBJECT_TASK)
                                &&(pLastEventEntry->ddState == OPF_TASK_DELAYED))
      /* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Pointer only accesses the range that is configured by user */
      /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
      {
        if(pLastEventEntry->ddObjectID == LddOpfTaskID)
        {
          pLastEventEntry->ddState = OPF_TASK_SUSPENDED;
        }
        else
        {
          pLastEventEntry->ddState = Opf_PortGetTaskState\
                                                    (pLastEventEntry->ddObjectID);
        }

        #if (OPF_MULTICORE_ENABLED == STD_ON)
        if(pCoreOsProfiler->ddRecMode == OPF_RECMODE_PROFILE)
        #else
        if(Opf_GddOsProfiler.ddRecMode == OPF_RECMODE_PROFILE)
        #endif
        {
          /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Pointer only accesses the range that is configured by user */
          /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
          /* Update the last event's state */
          pLastProfileEventEntry = Opf_GetLastProfileEvent();
          if (pLastProfileEventEntry != NULL_PTR)
          {
            pLastProfileEventEntry->ddState = pLastEventEntry->ddState;
          }
          /* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Pointer only accesses the range that is configured by user */
          /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
        }

        /* Verify task is eligible for profiling */
        Opf_ValidateTask(pLastEventEntry->ddObjectID);

        /* If valid task, update the task's information */
        if((OPF_ISVALID_TASK((pLastEventEntry->ddObjectID))) == TRUE)
        {
          Opf_UpdateTaskInfo(pLastEventEntry);
        }
      }
    }
    /* polyspace:end<DEFECT:NULL_PTR> */

    /* Save current time and time span between current and the last event */
    Opf_SaveTimeStamp();

    /* Add new event */
    LddEventEntry.ddSysTime = Opf_GetSavedSystime();
    LddEventEntry.ddTimeSpan = Opf_GetSavedSystimeSpan();
    LddEventEntry.ddObject = OPF_OBJECT_TASK;
    LddEventEntry.ddObjectID = LddOpfTaskID;
    LddEventEntry.ddState = OPF_TASK_RUNNING;
    Opf_AddNewEvent(&LddEventEntry);

    /* Verify task is eligible for profiling */
    Opf_ValidateTask(LddOpfTaskID);

    /* If valid task, update the task's information */
    if((OPF_ISVALID_TASK(LddOpfTaskID)) == TRUE)
    {
      Opf_UpdateTaskInfo(&LddEventEntry);
    }
  }
}
/* polyspace:end<MISRA-C3:18.1> */

/***************************************************************************//**
 * Function             : Opf_SetPostTaskEvent
 *
 * Service ID           : NA
 *
 * Description          : This function is called from PostTaskHook
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddOsProfiler, Opf_GaaTaskCache
 *
 *                        Function(s) invoked    :
 *                        Opf_PortProcessPostTask(), Opf_PortGetTaskID(),
 *                        Opf_ValidateTask(), Opf_SaveTimeStamp(),
 *                        Opf_AddNewEvent(), Opf_UpdateTaskInfo()
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
/* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
FUNC(void, OPF_CODE) Opf_SetPostTaskEvent(void)
{
  Tdd_Opf_Event LddEventEntry;
  OpfTaskIDType LddOpfTaskID;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  LddCoreID = GetCoreID();
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  #endif

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if(pCoreOsProfiler->ddRecMode != OPF_RECMODE_STOP)
  #else
  if(Opf_GddOsProfiler.ddRecMode != OPF_RECMODE_STOP)
  #endif
  {
    /* Process PostTask for system specific job */
    /* polyspace<MISRA-C3:2.2:Not a defect:Justify with annotations> used for future job */
    Opf_PortProcessPostTask();

    /* Save current time and time span between current and the last event */
    Opf_SaveTimeStamp();

    /* Get Task ID */
    LddOpfTaskID = (OpfTaskIDType)Opf_PortGetTaskID();

    /* Add new event */
    LddEventEntry.ddSysTime = Opf_GetSavedSystime();
    LddEventEntry.ddTimeSpan = Opf_GetSavedSystimeSpan();
    LddEventEntry.ddObject = OPF_OBJECT_TASK;
    LddEventEntry.ddObjectID = LddOpfTaskID;
    LddEventEntry.ddState = OPF_TASK_DELAYED; /* READY, WAITING, SUSPENDED */
    Opf_AddNewEvent(&LddEventEntry);

    /* Verify task is eligible for profiling */
    Opf_ValidateTask(LddOpfTaskID);

    /* If valid task, update the task's information */
    if((OPF_ISVALID_TASK(LddOpfTaskID)) == TRUE)
    {
      Opf_UpdateTaskInfo(&LddEventEntry);
    }
  }
}
/* polyspace:end<MISRA-C3:18.1> */

/***************************************************************************//**
 * Function             : Opf_SetPreIsrEvent
 *
 * Service ID           : NA
 *
 * Description          : This function is called from PreIsrHook
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddOsProfiler
 *
 *                        Function(s) invoked    :
 *                        Opf_PortProcessPreIsr(), Opf_SaveTimeStamp(),
 *                        GetISRID(), Opf_AddNewEvent()
 *
 * @ingroup               OPF-SRS-FUN-006
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_SetPreIsrEvent(void)
{
  Tdd_Opf_Event LddEventEntry;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* polyspace:begin<MISRA-C3:2.2:Not a defect:Justify with annotations> Opf coulde be off from user request */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (pCoreOsProfiler->ddRecMode != OPF_RECMODE_STOP)
  #else
  if (Opf_GddOsProfiler.ddRecMode != OPF_RECMODE_STOP)
  #endif
  {
    /* Process PreIsr for system specific job */
    Opf_PortProcessPreIsr();

    /* Save current time and time span between current and the last event */
    Opf_SaveTimeStamp();

    /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> can be reachable according to user configuration */
    /* polyspace:begin<DEFECT:USELESS_IF:Not a defect:Justify with annotations> below variable could be changed accroding to user configuration */
    /* polyspace:begin<MISRA-C3:14.3:Not a defect:Justify with annotations> below variable could be changed accroding to user configuration */
    /* polyspace:begin<DEFECT:DEAD_CODE:Not a defect:Justify with annotations> can be reachable according to user configuration */
    /* polyspace:begin<MISRA-C3:2.1:Not a defect:Justify with annotations> can be reachable according to user configuration */
    /* polyspace:begin<CERT-C:MSC12-C:Not a defect:Justify with annotations> can be reachable according to user configuration */
    if (Opf_Profile_Isr == STD_ON)
    {
      /* Add new event */
      LddEventEntry.ddSysTime = Opf_GetSavedSystime();
      LddEventEntry.ddTimeSpan = Opf_GetSavedSystimeSpan();
      LddEventEntry.ddObject = OPF_OBJECT_ISR;
      LddEventEntry.ddObjectID = (OpfObjectIDType)GetISRID();
      LddEventEntry.ddState = OPF_ISR_ENTER;

      /* Update task information */
      Opf_AddNewEvent(&LddEventEntry);
    }
    /* polyspace:end<RTE:UNR> */
    /* polyspace:end<DEFECT:USELESS_IF> */
    /* polyspace:end<MISRA-C3:14.3> */
    /* polyspace:end<DEFECT:DEAD_CODE> */
    /* polyspace:end<MISRA-C3:2.1> */
    /* polyspace:end<CERT-C:MSC12-C> */
  }
  /* polyspace-end MISRA-C3:2.2 */
}

/***************************************************************************//**
 * Function             : Opf_SetPostIsrEvent
 *
 * Service ID           : NA
 *
 * Description          : This function is called from PostIsrHook
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddOsProfiler
 *
 *                        Function(s) invoked    :
 *                        Opf_PortProcessPostIsr(), Opf_SaveTimeStamp(),
 *                        GetISRID(), Opf_AddNewEvent()
 *
 * @ingroup               OPF-SRS-FUN-006
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_SetPostIsrEvent(void)
{
  Tdd_Opf_Event LddEventEntry;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if(pCoreOsProfiler->ddRecMode != OPF_RECMODE_STOP)
  #else
  if(Opf_GddOsProfiler.ddRecMode != OPF_RECMODE_STOP)
  #endif
  {
    /* To use preisr's saved time information for counter */
    /* Process PostIsr for system specific job */
    /* polyspace<MISRA-C3:2.2:Not a defect:Justify with annotations> used for future job */
    Opf_PortProcessPostIsr();

    /* Save current time and time span between current event and the last event */
    Opf_SaveTimeStamp();

    /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> can be reachable according to user configuration */
    /* polyspace:begin<DEFECT:USELESS_IF:Not a defect:Justify with annotations> below variable could be changed accroding to user configuration */
    /* polyspace:begin<MISRA-C3:14.3:Not a defect:Justify with annotations> below variable could be changed accroding to user configuration */
    /* polyspace:begin<DEFECT:DEAD_CODE:Not a defect:Justify with annotations> can be reachable according to user configuration */
    /* polyspace:begin<MISRA-C3:2.1:Not a defect:Justify with annotations> can be reachable according to user configuration */
    /* polyspace:begin<CERT-C:MSC12-C:Not a defect:Justify with annotations> can be reachable according to user configuration */
    if (Opf_Profile_Isr == STD_ON)
    {
      /* Add new event */
      LddEventEntry.ddSysTime = Opf_GetSavedSystime();
      LddEventEntry.ddTimeSpan = Opf_GetSavedSystimeSpan();
      LddEventEntry.ddObject = OPF_OBJECT_ISR;
      LddEventEntry.ddObjectID = (OpfObjectIDType)GetISRID();
      LddEventEntry.ddState = OPF_ISR_EXIT;

      /* Update task information */
      Opf_AddNewEvent(&LddEventEntry);
    }
    /* polyspace:end<RTE:UNR> */
    /* polyspace:end<DEFECT:USELESS_IF> */
    /* polyspace:end<MISRA-C3:14.3> */
    /* polyspace:end<DEFECT:DEAD_CODE> */
    /* polyspace:end<MISRA-C3:2.1> */
    /* polyspace:end<CERT-C:MSC12-C> */
  }
}

/***************************************************************************//**
 * Function             : Opf_SetLimitErrorEvent
 *
 * Service ID           : NA
 *
 * Description          : This function is called from ErrorHook
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddOsProfiler
 *
 *                        Function(s) invoked    :
 *                        Opf_PortProcessLimitError(), Opf_SaveTimeStamp()
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_SetLimitErrorEvent(void)
{
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if(pCoreOsProfiler->ddRecMode != OPF_RECMODE_STOP)
  #else
  if(Opf_GddOsProfiler.ddRecMode != OPF_RECMODE_STOP)
  #endif
  {
    /* Save current time and time span between current event and the last event */
    Opf_SaveTimeStamp();

    /* Process Limit Error for system speocific job */
    Opf_PortProcessLimitError();
  }
}

/***************************************************************************//**
 * Function             : Opf_SetActivateTaskEvent
 *
 * Service ID           : NA
 *
 * Description          : This function is called from the point that a task is
 *                        activated
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LddTaskID     ID of the task
 *                        LddTimeSpan   Time Span of activation event
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GaaTaskCache
 *
 *                        Function(s) invoked    :
 *                        Opf_ValidateTask(), Opf_AddNewEvent(),
 *                        Opf_UpdateTaskInfo()
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
FUNC(void, OPF_CODE) Opf_SetActivateTaskEvent(OpfTaskIDType LddTaskID,
                                                    OpfTimeSpanType LddTimeSpan)
/* polyspace-end MISRA-C3:D4.5 */
{
  Tdd_Opf_Event LddEventEntry;

  /* Add new event */
  LddEventEntry.ddSysTime = Opf_GetSavedSystime();
  LddEventEntry.ddTimeSpan = LddTimeSpan;
  LddEventEntry.ddObject = OPF_OBJECT_TASK;
  LddEventEntry.ddObjectID = LddTaskID;
  LddEventEntry.ddState = OPF_TASK_ACTIVATED;
  Opf_AddNewEvent(&LddEventEntry);

  /* Verify task is eligible for profiling */
  Opf_ValidateTask(LddTaskID);

  /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justify with annotations> array index is within pre-defined range */
  /* If valid task, update the task's information */
  if((OPF_ISVALID_TASK(LddTaskID)) == TRUE)
  /* polyspace:end<MISRA-C3:D4.14> */
  {
    Opf_UpdateTaskInfo(&LddEventEntry);
  }
}

/***************************************************************************//**
 * Function             : Opf_SetTaskEvent
 *
 * Service ID           : NA
 *
 * Description          : This function is used to add a new Task event and
 *                        update Task info
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LddTaskID     ID of the task
 *
 * @param [in]            LddState      Task State
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GaaTaskCache
 *
 *                        Function(s) invoked    :
 *                        Opf_ValidateTask(), Opf_AddNewEvent(),
 *                        Opf_UpdateTaskInfo()
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
FUNC(void, OPF_CODE) Opf_SetTaskEvent(OpfTaskIDType LddTaskID,
                                                          OpfStateType LddState)
/* polyspace-end MISRA-C3:D4.5 */
{
  Tdd_Opf_Event LddEventEntry;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> check status */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if (pCoreOsProfiler->ddRecMode != OPF_RECMODE_STOP)
  #else
  if (Opf_GddOsProfiler.ddRecMode != OPF_RECMODE_STOP)
  #endif
  {
    /* Save current time and time span between current and the last event */
    Opf_SaveTimeStamp();

    /* Add new event */
    LddEventEntry.ddSysTime = Opf_GetSavedSystime();
    LddEventEntry.ddTimeSpan = Opf_GetSavedSystimeSpan();
    LddEventEntry.ddObject = OPF_OBJECT_TASK;
    LddEventEntry.ddObjectID = LddTaskID;
    LddEventEntry.ddState = LddState;
    Opf_AddNewEvent(&LddEventEntry);

    /* Verify task is eligible for profiling */
    Opf_ValidateTask(LddTaskID);

    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justify with annotations> array index is within pre-defined range */
    /* If valid task, update the task's information */
    if ((OPF_ISVALID_TASK(LddTaskID)) == TRUE)
    /* polyspace:end<MISRA-C3:D4.14> */
    {
      if ((LddState == OPF_TASK_SUSPENDED) || (LddState == OPF_TASK_READY))
      {
        LddEventEntry.ddState = OPF_TASK_DELAYED;
        Opf_UpdateTaskInfo(&LddEventEntry);
        LddEventEntry.ddState = LddState;
      }
      Opf_UpdateTaskInfo(&LddEventEntry);
    }
  }
  /* polyspace:end<RTE:UNR> */
}

/***************************************************************************//**
 * Function             : Opf_SetLimitTaskEvent
 *
 * Service ID           : NA
 *
 * Description          : This function is called from the point that an limit
 *                        error is reproduced
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LddTaskID     ID of the task
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GaaTaskCache
 *
 *                        Function(s) invoked    :
 *                        Opf_ValidateTask(), Opf_GetTimeSpan(),
 *                        Opf_AddNewEvent(), Opf_GetSavedSystimeSpan()
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
FUNC(void, OPF_CODE) Opf_SetLimitTaskEvent(OpfTaskIDType LddTaskID)
/* polyspace-end MISRA-C3:D4.5 */
{
  Tdd_Opf_Event LddEventEntry;

  /* Verify task is eligible for profiling */
  Opf_ValidateTask(LddTaskID);

  /* If valid task, add that event into event queue */
  if((OPF_ISVALID_TASK(LddTaskID)) == TRUE)
  {
    /* Add new event */
    LddEventEntry.ddSysTime = Opf_GetSavedSystime();
    LddEventEntry.ddTimeSpan = Opf_GetSavedSystimeSpan();
    LddEventEntry.ddObject = OPF_OBJECT_TASK;
    LddEventEntry.ddObjectID = LddTaskID;
    LddEventEntry.ddState = OPF_TASK_LIMMITERROR;
    Opf_AddNewEvent(&LddEventEntry);

    /* Update task information */
    Opf_UpdateTaskInfo(&LddEventEntry);
  }
}

/***************************************************************************//**
 * Function             : Opf_SetTimeIndexEvent
 *
 * Service ID           : NA
 *
 * Description          : This function adds a Time Index Event to Event Queue
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LddSpanTick   Span tick of system time index
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Opf_AddNewEvent()
 *
 * @ingroup               OPF-SRS-FUN-007
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_SetTimeIndexEvent(OpfSpanTickType LddSpanTick)
{
  Tdd_Opf_Event LddEventEntry;

  /* Add new event */
  LddEventEntry.ddSysTime = Opf_GetSavedSystime();
  LddEventEntry.ddTimeSpan = LddSpanTick;
  LddEventEntry.ddObject = OPF_OBJECT_TIME;
  LddEventEntry.ddObjectID = OPF_ZERO;
  LddEventEntry.ddState = OPF_TIME_INDEX;

  /* Update task information */
  Opf_AddNewEvent(&LddEventEntry);
}

#define OPF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<RTE: OBAI : Not a defect : Justify with annotations > configured array index */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
