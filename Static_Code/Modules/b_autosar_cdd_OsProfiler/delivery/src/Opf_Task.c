/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_Task.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Implementation of TimeService module                          **
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
** 1.5.2     24-Nov-2020    YH.Han        Redmine #26755                      **
** 1.3.0     29-Oct-2018    YH.Han        Redmine #12853                      **
** 1.1.2     22-Aug-2017    MJ.Woo        Redmine #6959                       **
** 1.1.0     24-Nov-2016    SH.Yoo        Redmine #6755, #6756                **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_Port.h"
#include "Opf_Cfg.h"
#include "Opf_Ram.h"
#include "Opf_ControlEventQueue.h"
#include "Opf_Task.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
static FUNC(void, OPF_CODE) Opf_UpdateTaskCache(OpfTaskIDType LddTaskID);
/* polyspace-end MISRA-C3:D4.5 */

#define OPF_START_SEC_CODE
#include "MemMap.h"

/***************************************************************************//**
 * Function             : Opf_ValidateTask
 *
 * Service ID           : NA
 *
 * Description          : This function updates task cache when task id does not
 *                        checked before
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LddTaskID    Profile target task id
 *
 * @return              : void
 *
 * @pre                 : Opf_InitEventQueue() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GaaTaskCache
 *
 *                        Function(s) invoked    :
 *                        Opf_UpdateTaskCache()
 *
 * @ingroup               OPF-SRS-FUN-001, OPF-SRS-FUN-003, OPF-SRS-FUN-004,
 *                        OPF-SRS-FUN-005, OPF-SRS-FUN-008, OPF-SRS-FUN-010,
 *                        OPF-SRS-FUN-012, OPF-SRS-FUN-014, OPF-SRS-FUN-016
 ******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
FUNC(void, OPF_CODE) Opf_ValidateTask(OpfTaskIDType LddTaskID)
/* polyspace-end MISRA-C3:D4.5 */
{
  /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace<MISRA-C3:18.1:Not a defect> its boundary is limited to array size */
  /* polyspace<MISRA-C3:D4.14:Not a defect:Justify with annotations> array index is within pre-defined range */
  if (Opf_GaaTaskCache[LddTaskID].ddIsValid == OPF_TC_NOCHECK)
  {
    Opf_UpdateTaskCache(LddTaskID);
  }
}

/***************************************************************************//**
 * Function             : Opf_UpdateTaskCache
 *
 * Service ID           : NA
 *
 * Description          : This function updates cache of Task profile data index
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LddTaskID    Profile target task id
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GaaTaskCache, Opf_GaaProfileTaskInfo
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-001, OPF-SRS-FUN-003, OPF-SRS-FUN-004,
 *                        OPF-SRS-FUN-005, OPF-SRS-FUN-008, OPF-SRS-FUN-010,
 *                        OPF-SRS-FUN-012, OPF-SRS-FUN-014, OPF-SRS-FUN-016
 ******************************************************************************/
/* polyspace-begin MISRA-C3:D4.5 [Not a Defect] "variable is not in same name space" */
static FUNC(void, OPF_CODE) Opf_UpdateTaskCache(OpfTaskIDType LddTaskID)
/* polyspace-end MISRA-C3:D4.5 */
{
  uint8 idxTaskList;

  /* polyspace<MISRA-C3:D4.14:Not a defect:Justify with annotations> array index is within pre-defined range */
  Opf_GaaTaskCache[LddTaskID].ddIsValid = OPF_TC_INVALID;

#if (OPF_TARGET_OS == OPF_FREESCALE_MPC560XB)
  Opf_PortUpdateAlarmTask(LddTaskID);
#endif

  for(idxTaskList = 0; idxTaskList < Opf_Profile_Task_Count; idxTaskList++)
  {
    if(Opf_GaaProfileTaskInfo[idxTaskList].ddTaskID == LddTaskID)
    {
      Opf_GaaTaskCache[LddTaskID].ddIsValid = OPF_TC_VALID;
      Opf_GaaTaskCache[LddTaskID].ddIndex = idxTaskList;
      break;
    }
  }
}

/***************************************************************************//**
 * Function             : Opf_UpdateTaskInfo
 *
 * Service ID           : NA
 *
 * Description          : This function updates profile info of Task
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            pEvent       Reference of an Event
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GaaTaskCache, Opf_GaaTaskInfo,
 *                        Opf_GaaProfileTaskInfo, Opf_GddProfileEventQ,
 *                        Opf_GddOsProfiler
 *
 *                        Function(s) invoked    :
 *                        Opf_GetSavedSystime(), Opf_GetSystimeDiff(),
 *                        Opf_UpdateProfiledEventQueue()
 *
 * @ingroup               OPF-SRS-FUN-001, OPF-SRS-FUN-003, OPF-SRS-FUN-009,
 *                        OPF-SRS-FUN-011, OPF-SRS-FUN-013, OPF-SRS-FUN-015,
 *                        OPF-SRS-FUN-017
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_UpdateTaskInfo(Tdd_Opf_Event *pEvent)
{
  OpfTaskInfoIdxType LddListIdx;
  OpfTickType LddCurTick;
  OpfTickType LddTimerTick;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_ProfileEventQ *pCoreProfileEventQ;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;

  LddCoreID = GetCoreID();
  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  pCoreProfileEventQ = OPF_GET_PROFILE_EVENTQ_INFO(LddCoreID);
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  #endif

  if((pEvent != OPF_NULL) && (pEvent->ddObject == OPF_OBJECT_TASK) && (pEvent->ddObjectID <= OPF_MAX_TASK_ID))
  {
    /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
    /* polyspace<MISRA-C3:18.1:Not a defect> its boundary is limited to array size */
    LddListIdx = Opf_GaaTaskCache[pEvent->ddObjectID].ddIndex;
    LddCurTick = Opf_GetSavedSystime();

    /* ACTIVATED */
    if(pEvent->ddState == OPF_TASK_ACTIVATED)
    {
      /* Period */
      /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
      /* polyspace<MISRA-C3:10.4:Not a defect:Justify with annotations> both operands are not effected to result */
      /* polyspace<MISRA-C3:18.1:Not a defect> its boundary is limited to array size */
      if(Opf_GaaTaskInfo[LddListIdx].ddNewReadyTV_ == OPF_TRUE)
      {
        Opf_GaaProfileTaskInfo[LddListIdx].ddTaskPeriod = \
                  Opf_GetSystimeDiff(Opf_GaaTaskInfo[LddListIdx].ddNewReadyT_, \
                                                                    LddCurTick);
      }

      /* ST (Slack Time)
       * : Suspended <-> Activated */
      if((Opf_GaaProfileTaskInfo[LddListIdx].ddTaskPeriod != OPF_ZERO) && 
                       (Opf_GaaTaskInfo[LddListIdx].ddSuspendedTV_ == OPF_TRUE))
      {
        Opf_GaaTaskInfo[LddListIdx].ddSlackT_ = \
             Opf_GetSystimeDiff(Opf_GaaTaskInfo[LddListIdx].ddSuspendedT_, \
                                                                    LddCurTick);

        /* polyspace:begin<RTE:ZDV:Not a defect:Justify with annotations> Already checked at upper 'if' condition */
        /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> Already checked at upper 'if' condition  */
        #if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
        if(Opf_GaaTaskInfo[LddListIdx].ddSlackT_ < \
                                         (Opf_Max_Stm_Tick_Value/OPF_FULL_PERMILLAGE))
        #else
        if(Opf_GaaTaskInfo[LddListIdx].ddSlackT_ < \
                                         (OPF_MAX_STM_TICK/OPF_FULL_PERMILLAGE))
        #endif
        {
          Opf_GaaTaskInfo[LddListIdx].ddST = \
              ((Opf_GaaTaskInfo[LddListIdx].ddSlackT_ * OPF_FULL_PERMILLAGE) / \
                     Opf_GaaProfileTaskInfo[LddListIdx].ddTaskPeriod);
        }
        else
        {
          Opf_GaaTaskInfo[LddListIdx].ddST = \
            (Opf_GaaTaskInfo[LddListIdx].ddSlackT_ / \
              (Opf_GaaProfileTaskInfo[LddListIdx].ddTaskPeriod / \
              OPF_FULL_PERMILLAGE));
        }
        /* polyspace:end<RTE:ZDV:Not a defect:Justify with annotations> Already checked at upper 'if' condition */
        /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> Already checked at upper 'if' condition  */

        if(Opf_GaaTaskInfo[LddListIdx].ddST < \
                                Opf_GaaProfileTaskInfo[LddListIdx].ddMinST)
        {
          /* Update profiled queue information */
          #if (OPF_MULTICORE_ENABLED == STD_ON)
          if(pCoreProfileEventQ->pCurProfiledTaskInfo == OPF_NULL)
          #else
          if(Opf_GddProfileEventQ.pCurProfiledTaskInfo == OPF_NULL)
          #endif
          {
            Opf_UpdateProfiledEventQueue();
            #if (OPF_MULTICORE_ENABLED == STD_ON)
            pCoreOsProfiler->ddRecMode = OPF_RECMODE_PROFILE;
            pCoreProfileEventQ->pCurProfiledTaskInfo = \
                                          &(Opf_GaaProfileTaskInfo[LddListIdx]);
            #else
            Opf_GddOsProfiler.ddRecMode = OPF_RECMODE_PROFILE;
            Opf_GddProfileEventQ.pCurProfiledTaskInfo = \
                                          &(Opf_GaaProfileTaskInfo[LddListIdx]);
            #endif
          }
          else
          {
            /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> Zero initialized data */
            /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
            /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
            /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> pointer accesses already defined struct */
            #if (OPF_MULTICORE_ENABLED == STD_ON)
            if(Opf_GaaTaskInfo[LddListIdx].ddST <
                              pCoreProfileEventQ->pCurProfiledTaskInfo->ddMinST)
            #else
            if(Opf_GaaTaskInfo[LddListIdx].ddST <
                             Opf_GddProfileEventQ.pCurProfiledTaskInfo->ddMinST)
            #endif
            /* polyspace:end<RTE:NIV:Not a defect:Justify with annotations> Zero initialized data */
            /* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
            /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
            /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> pointer accesses already defined struct */
            {
              Opf_UpdateProfiledEventQueue();
              #if (OPF_MULTICORE_ENABLED == STD_ON)
              pCoreOsProfiler->ddRecMode = OPF_RECMODE_PROFILE;
              pCoreProfileEventQ->pCurProfiledTaskInfo = \
                                          &(Opf_GaaProfileTaskInfo[LddListIdx]);
              #else
              Opf_GddOsProfiler.ddRecMode = OPF_RECMODE_PROFILE;
              Opf_GddProfileEventQ.pCurProfiledTaskInfo = \
                                          &(Opf_GaaProfileTaskInfo[LddListIdx]);
              #endif
            }
          }
          Opf_GaaProfileTaskInfo[LddListIdx].ddMinST = \
                                               Opf_GaaTaskInfo[LddListIdx].ddST;
        }
      }

      Opf_GaaTaskInfo[LddListIdx].ddNewReadyT_ = LddCurTick;
      /* polyspace<MISRA-C3:10.3:Not a defect:Justify with annotations> right side is not effected to cast of other type */
      Opf_GaaTaskInfo[LddListIdx].ddNewReadyTV_ = (OpfTickType) OPF_TRUE;
      Opf_GaaTaskInfo[LddListIdx].ddPrevReadyT_ = LddCurTick;
      Opf_GaaTaskInfo[LddListIdx].ddJitterT_ = OPF_ZERO;
      Opf_GaaTaskInfo[LddListIdx].ddCumulExecT_ = OPF_ZERO;
      Opf_GaaTaskInfo[LddListIdx].ddFirstRunningT_ = OPF_ZERO;
    }
    /* DELAYED (Preempted or Terminated) */
    else if(pEvent->ddState == OPF_TASK_DELAYED)
    {
      /* execution time slice++ */
      /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
      /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> its boundary is limited to array size */
      LddTimerTick = \
               Opf_GetSystimeDiff(Opf_GaaTaskInfo[LddListIdx].ddPrevRunningT_, \
                                                                    LddCurTick);
      /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
      /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> its boundary is limited to array size */
      Opf_GaaTaskInfo[LddListIdx].ddCumulExecT_ += LddTimerTick;
      /* suspended time */
      Opf_GaaTaskInfo[LddListIdx].ddSuspendedT_ = LddCurTick;
    }
    /* RUNNING */
    else if(pEvent->ddState == OPF_TASK_RUNNING)
    {
      /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
      /* polyspace<MISRA-C3:18.1:Not a defect> its boundary is limited to array size */
      Opf_GaaTaskInfo[LddListIdx].ddPrevRunningT_ = LddCurTick;

      /* JIT (Jitter)
       * : Activated <-> Running */
      /* polyspace:begin<MISRA-C3:10.4:Not a defect:Justify with annotations> both operands are not effected to result  */
      if((Opf_GaaProfileTaskInfo[LddListIdx].ddTaskPeriod != OPF_ZERO) &&
                        (Opf_GaaTaskInfo[LddListIdx].ddNewReadyTV_ == OPF_TRUE))
      /* polyspace:end<MISRA-C3:10.4:Not a defect:Justify with annotations> both operands are not effected to result  */
      {
        Opf_GaaTaskInfo[LddListIdx].ddJitterT_ = \
            Opf_GetSystimeDiff(Opf_GaaTaskInfo[LddListIdx].ddNewReadyT_, \
                                                                    LddCurTick);
        if(Opf_GaaTaskInfo[LddListIdx].ddJitterT_ < \
                                         (OPF_MAX_STM_TICK/OPF_FULL_PERMILLAGE))
        {
          /* polyspace:begin<RTE:ZDV:Not a defect:Justify with annotations> Already checked at upper 'if' condition */
          /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> Already checked at upper 'if' condition  */
          Opf_GaaTaskInfo[LddListIdx].ddJIT = \
             ((Opf_GaaTaskInfo[LddListIdx].ddJitterT_ * OPF_FULL_PERMILLAGE) / \
                               Opf_GaaProfileTaskInfo[LddListIdx].ddTaskPeriod);
          /* polyspace:end<RTE:ZDV:Not a defect:Justify with annotations> Already checked at upper 'if' condition */
          /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> Already checked at upper 'if' condition  */
        }
        else
        {
          /* polyspace:begin<RTE:ZDV:Not a defect:Justify with annotations> Already checked at upper 'if' condition */
          /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> Already checked at upper 'if' condition  */
          Opf_GaaTaskInfo[LddListIdx].ddJIT = \
            (Opf_GaaTaskInfo[LddListIdx].ddJitterT_  / \
            (Opf_GaaProfileTaskInfo[LddListIdx].ddTaskPeriod / \
            OPF_FULL_PERMILLAGE));
          /* polyspace:end<RTE:ZDV:Not a defect:Justify with annotations> Already checked at upper 'if' condition */
          /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> Already checked at upper 'if' condition  */
        }
      }

      if(Opf_GaaTaskInfo[LddListIdx].ddJIT > \
                               Opf_GaaProfileTaskInfo[LddListIdx].ddMaxJIT)
      {
        Opf_GaaProfileTaskInfo[LddListIdx].ddMaxJIT = \
                                              Opf_GaaTaskInfo[LddListIdx].ddJIT;
      }

      /* fist running time */
      if(Opf_GaaTaskInfo[LddListIdx].ddFirstRunningT_ == OPF_ZERO)
      {
        Opf_GaaTaskInfo[LddListIdx].ddFirstRunningT_ = LddCurTick;
      }
    }
    /* SUSPENDED */
    else if(pEvent->ddState == OPF_TASK_SUSPENDED)
    {
      /* RT (Response Time)
       * : Activated <-> Suspended */
      /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
      /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> its boundary is limited to array size */
      Opf_GaaTaskInfo[LddListIdx].ddRT = \
                  Opf_GetSystimeDiff(Opf_GaaTaskInfo[LddListIdx].ddNewReadyT_, \
                                     Opf_GaaTaskInfo[LddListIdx].ddSuspendedT_);
      /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
      /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> its boundary is limited to array size */
      if(Opf_GaaTaskInfo[LddListIdx].ddRT > \
                                Opf_GaaProfileTaskInfo[LddListIdx].ddMaxRT)
      {
        Opf_GaaProfileTaskInfo[LddListIdx].ddMaxRT = \
                                               Opf_GaaTaskInfo[LddListIdx].ddRT;
      }

      /* CET (Core Execution Time)
       * : Real Execution Time */
      Opf_GaaTaskInfo[LddListIdx].ddCET = \
                                       Opf_GaaTaskInfo[LddListIdx].ddCumulExecT_;

      if(Opf_GaaTaskInfo[LddListIdx].ddCumulExecT_ >
                               Opf_GaaProfileTaskInfo[LddListIdx].ddMaxCET)
      {
        Opf_GaaProfileTaskInfo[LddListIdx].ddMaxCET = \
                                       Opf_GaaTaskInfo[LddListIdx].ddCumulExecT_;
      }

      /* GET (Gross Execution Time)
       * : First Running <-> Suspended */
      Opf_GaaTaskInfo[LddListIdx].ddGET = \
              Opf_GetSystimeDiff(Opf_GaaTaskInfo[LddListIdx].ddFirstRunningT_, \
                                     Opf_GaaTaskInfo[LddListIdx].ddSuspendedT_);
      if(Opf_GaaTaskInfo[LddListIdx].ddGET >
                               Opf_GaaProfileTaskInfo[LddListIdx].ddMaxGET)
      {
        Opf_GaaProfileTaskInfo[LddListIdx].ddMaxGET = \
                                              Opf_GaaTaskInfo[LddListIdx].ddGET;
      }

      if(Opf_GaaTaskInfo[LddListIdx].ddSuspendedTV_ == OPF_FALSE)
      {
        Opf_GaaTaskInfo[LddListIdx].ddSuspendedTV_ = OPF_TRUE;
      }
    }
    /* LIMIT ERROR */
    else if(pEvent->ddState == OPF_TASK_LIMMITERROR)
    {
      /* polyspace:begin<RTE:NIV:Not a defect:Justify with annotations> Zero initialized data */
      /* polyspace:begin<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
      /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
      /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> pointer accesses already defined struct */
      #if (OPF_MULTICORE_ENABLED == STD_ON)
      if((pCoreProfileEventQ->pCurProfiledTaskInfo == OPF_NULL) ||
               (pCoreProfileEventQ->pCurProfiledTaskInfo->ddMinST != OPF_ZERO))
      #else
      if((Opf_GddProfileEventQ.pCurProfiledTaskInfo == OPF_NULL) ||
               (Opf_GddProfileEventQ.pCurProfiledTaskInfo->ddMinST != OPF_ZERO))
      #endif
      /* polyspace:end<RTE:NIV:Not a defect:Justify with annotations> Zero initialized data */
      /* polyspace:end<RTE:IDP:Not a defect:Justify with annotations> Configured memory access index */
      /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
      /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> pointer accesses already defined struct */
      {
        /* polyspace<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
        /* polyspace<MISRA-C3:18.1:Not a defect> its boundary is limited to array size */
        Opf_GaaTaskInfo[LddListIdx].ddSlackT_ = OPF_ZERO;
        Opf_GaaTaskInfo[LddListIdx].ddST = OPF_ZERO;
        Opf_GaaProfileTaskInfo[LddListIdx].ddMinST = OPF_ZERO;

        /* Update profiled queue information */
        Opf_UpdateProfiledEventQueue();
        #if (OPF_MULTICORE_ENABLED == STD_ON)
        pCoreOsProfiler->ddRecMode = OPF_RECMODE_PROFILE;
        pCoreProfileEventQ->pCurProfiledTaskInfo = \
                                          &(Opf_GaaProfileTaskInfo[LddListIdx]);
        #else
        Opf_GddOsProfiler.ddRecMode = OPF_RECMODE_PROFILE;
        Opf_GddProfileEventQ.pCurProfiledTaskInfo = \
                                          &(Opf_GaaProfileTaskInfo[LddListIdx]);
        #endif
      }
    }
    else
    {
      /* Do Nothing */
    }
  }
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
