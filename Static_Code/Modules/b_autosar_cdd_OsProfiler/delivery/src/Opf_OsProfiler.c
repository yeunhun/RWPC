/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_OsProfiler.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Implementation of OsProfiler module                           **
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
** 1.5.4     14-Dec-2021    YH.Han        Redmine #33312, #33448              **
** 1.5.3     08-Jan-2021    YH.Han        Redmine #27601                      **
** 1.5.2     24-Nov-2020    YH.Han        Redmine #26755                      **
** 1.5.1     17-Jun-2020    YH.Han        Redmine #24104                      **
** 1.4.0     23-Oct-2019    YH.Han        Redmine #17493                      **
** 1.3.0     29-Oct-2018    YH.Han        Redmine #12853                      **
** 1.1.2     30-Aug-2017    MJ.Woo        Redmine #6959                       **
** 1.1.0     24-Nov-2016    SH.Yoo        Redmine #6849, #6756                **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_OsProfiler.h"
#include "Opf_Ram.h"
#include "Opf_Port.h"
#include "Opf_ControlEventQueue.h"
#include "Opf_TimeService.h"
#include <string.h>

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OPF_START_SEC_CODE
#include "MemMap.h"

/***************************************************************************//**
 * Function             : Opf_InitOsProfiler
 *
 * Service ID           : NA
 *
 * Description          : This function is called to initialize OsProfiler
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
 *                        Opf_GulIndexTicks, Opf_GddEventQ, Opf_GddProfileEventQ
 *
 *                        Function(s) invoked    :
 *                        Opf_InitProfileTaskInfo(),
 *                        memset(), Opf_InitEventQueue(), Opf_PortGetStmClock()
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_InitOsProfiler(void)
{
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_EventQ *pCoreEventQ;
  Tdd_Opf_ProfileEventQ *pCoreProfileEventQ;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;
  uint32 *pCoreIndexTicks;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreEventQ = OPF_GET_EVENTQ_INFO(LddCoreID);
  pCoreProfileEventQ = OPF_GET_PROFILE_EVENTQ_INFO(LddCoreID);
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  pCoreIndexTicks = OPF_GET_INDEX_TICKS_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* Initialize ProfileTaskInfo */
  Opf_InitProfileTaskInfo();

  /* Initialize event/profiled event queue */
  Opf_InitEventQueue();

  /* Initialize task cache */
  /* polyspace<MISRA-C3:10.3:Not a defect:Justify with annotations> zero is not effected to cast of other type */
  memset(&Opf_GaaTaskCache[OPF_ZERO], OPF_ZERO,
                            (Sizeof_Tdd_Opf_GaaTaskCache * Opf_Max_Task_Id));

  /* Get System Timer Clock */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  pCoreOsProfiler->ddSTMClock = Opf_PortGetStmClock();
  #else
  Opf_GddOsProfiler.ddSTMClock = Opf_PortGetStmClock();
  #endif

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> can be reachable according to user configuration */
  /* polyspace:begin<DEFECT:USELESS_IF:Not a defect:Justify with annotations> below variable could be changed accroding to user configuration */
  /* polyspace:begin<MISRA-C3:14.3:Not a defect:Justify with annotations> below variable could be changed accroding to user configuration */
  /* polyspace:begin<DEFECT:DEAD_CODE:Not a defect:Justify with annotations> can be reachable according to user configuration */
  /* polyspace:begin<MISRA-C3:2.1:Not a defect:Justify with annotations> can be reachable according to user configuration */
  /* polyspace:begin<CERT-C:MSC12-C:Not a defect:Justify with annotations> can be reachable according to user configuration */
  if(Opf_Profile_Time_Index == STD_ON)
  {
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    *pCoreIndexTicks = OPF_MS_TO_TICKS(Opf_Time_Index_Msec);
    #else
    Opf_GulIndexTicks = OPF_MS_TO_TICKS(Opf_Time_Index_Msec);
    #endif
  }
  /* polyspace:end<RTE:UNR> */
  /* polyspace:end<DEFECT:USELESS_IF> */
  /* polyspace:end<MISRA-C3:14.3> */
  /* polyspace:end<DEFECT:DEAD_CODE> */
  /* polyspace:end<MISRA-C3:2.1> */
  /* polyspace:end<CERT-C:MSC12-C> */

  /* Initialize EventQ/ProfileEventQ address */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  pCoreOsProfiler->pEventQ = pCoreEventQ;
  pCoreOsProfiler->pProfileEventQ = pCoreProfileEventQ;
  #else
  Opf_GddOsProfiler.pEventQ = &Opf_GddEventQ;
  Opf_GddOsProfiler.pProfileEventQ = &Opf_GddProfileEventQ;
  #endif

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> can be reachable according to user configuration */
  /* polyspace:begin<DEFECT:USELESS_IF:Not a defect:Justify with annotations> below variable could be changed accroding to user configuration */
  /* polyspace:begin<MISRA-C3:14.3:Not a defect:Justify with annotations> below variable could be changed accroding to user configuration */
  /* polyspace:begin<DEFECT:DEAD_CODE:Not a defect:Justify with annotations> can be reachable according to user configuration */
  /* polyspace:begin<MISRA-C3:2.1:Not a defect:Justify with annotations> can be reachable according to user configuration */
  /* polyspace:begin<CERT-C:MSC12-C:Not a defect:Justify with annotations> can be reachable according to user configuration */
  if(Opf_Profile_Time_Index == STD_ON)
  {
    #if (OPF_UPWARD_DIRECTION_COUNT == STD_ON)
    /* Next index ticks */
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    pCoreOsProfiler->ddNextIndexTick = OPF_ZERO;
    #else
    Opf_GddOsProfiler.ddNextIndexTick = OPF_ZERO;
    #endif
    #else
    /* Next index ticks */
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    #if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
    pCoreOsProfiler->ddNextIndexTick = Opf_Max_Stm_Tick_Value;
    #else
    pCoreOsProfiler->ddNextIndexTick = OPF_MAX_STM_TICK;
    #endif
    #else
    #if (OPF_TARGET_OS == OPF_AUTRON_COMMON)
    Opf_GddOsProfiler.ddNextIndexTick = Opf_Max_Stm_Tick_Value;
    #else
    Opf_GddOsProfiler.ddNextIndexTick = OPF_MAX_STM_TICK;
    #endif
    #endif
    #endif
  }
  /* polyspace:end<RTE:UNR> */
  /* polyspace:end<DEFECT:USELESS_IF> */
  /* polyspace:end<MISRA-C3:14.3> */
  /* polyspace:end<DEFECT:DEAD_CODE> */
  /* polyspace:end<MISRA-C3:2.1> */
  /* polyspace:end<CERT-C:MSC12-C> */

}

/***************************************************************************//**
 * Function             : Opf_StartOsProfiler
 *
 * Service ID           : NA
 *
 * Description          : This function is called to start OsProfiler
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
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
 FUNC(void, OPF_CODE) Opf_StartOsProfiler(void)
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

  /* polyspace:begin<RTE:UNR:Not a defect:Justify with annotations> status check */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if(pCoreOsProfiler->ddRecMode == OPF_RECMODE_STOP)
  #else
  if(Opf_GddOsProfiler.ddRecMode == OPF_RECMODE_STOP)
  #endif
  {
    /* Start OsProfiler */
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    pCoreOsProfiler->ddRecMode = OPF_RECMODE_EVENT;
    #else
    Opf_GddOsProfiler.ddRecMode = OPF_RECMODE_EVENT;
    #endif
  }
  /* polyspace:end<RTE:UNR> */
}

/***************************************************************************//**
 * Function             : Opf_StopOsProfiler
 *
 * Service ID           : NA
 *
 * Description          : This function is called to stop OsProfiler
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
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_StopOsProfiler(void)
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
    /* Stop OsProfiler */
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    pCoreOsProfiler->ddRecMode = OPF_RECMODE_STOP;
    #else
    Opf_GddOsProfiler.ddRecMode = OPF_RECMODE_STOP;
    #endif

    /* Clear task information */
    memset(Opf_GaaTaskInfo, OPF_ZERO,
                             Sizeof_Tdd_Opf_TaskInfo * Opf_Profile_Task_Count);
  }
}

/***************************************************************************//**
 * Function             : Opf_RestartOsProfiler
 *
 * Service ID           : NA
 *
 * Description          : This function is called to restart OsProfiler
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
 *                        Opf_GddOsProfiler, Opf_GddEventQ,
 *                        Opf_GddProfileEventQ, Opf_GaaTaskInfo,
 *                        Opf_GaaProfileTaskInfo
 *
 *                        Function(s) invoked    :
 *                        memset(), Opf_InitEventQueue(),
 *                        Opf_GetSystimeSpan()
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_RestartOsProfiler(void)
{
  uint8 LddIdx;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_EventQ *pCoreEventQ;
  Tdd_Opf_ProfileEventQ *pCoreProfileEventQ;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreEventQ = OPF_GET_EVENTQ_INFO(LddCoreID);
  pCoreProfileEventQ = OPF_GET_PROFILE_EVENTQ_INFO(LddCoreID);
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* Clear event/profile event queue information */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  memset(pCoreEventQ, OPF_ZERO, Sizeof_Tdd_Opf_EventQ);
  memset(pCoreProfileEventQ, OPF_ZERO, Sizeof_Tdd_Opf_ProfileEventQ);
  #else
  memset(&Opf_GddEventQ, OPF_ZERO, Sizeof_Tdd_Opf_EventQ);
  memset(&Opf_GddProfileEventQ, OPF_ZERO, Sizeof_Tdd_Opf_ProfileEventQ);
  #endif

  /* Clear task information */
  memset(Opf_GaaTaskInfo, OPF_ZERO,
                             Sizeof_Tdd_Opf_TaskInfo * Opf_Profile_Task_Count);
  for(LddIdx = OPF_ZERO; LddIdx < Opf_Profile_Task_Count; LddIdx++)
  {
    Opf_GaaProfileTaskInfo[LddIdx].ddTaskPeriod = OPF_ZERO;
    Opf_GaaProfileTaskInfo[LddIdx].ddMinST = 0xFFFFFFFFu;
    Opf_GaaProfileTaskInfo[LddIdx].ddMaxJIT = OPF_ZERO;
    Opf_GaaProfileTaskInfo[LddIdx].ddMaxCET = OPF_ZERO;
    Opf_GaaProfileTaskInfo[LddIdx].ddMaxGET = OPF_ZERO;
    Opf_GaaProfileTaskInfo[LddIdx].ddMaxRT = OPF_ZERO;
    Opf_GaaProfileTaskInfo[LddIdx].ddOsLimitCount = OPF_ZERO;
  }

  /* Clear OsProfiler information */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  pCoreOsProfiler->ddRecMode = OPF_RECMODE_EVENT;
  #else
  Opf_GddOsProfiler.ddRecMode = OPF_RECMODE_EVENT;
  #endif

  /* Init system timer tick */
  (void)Opf_GetSystimeSpan();

  /* Init event queue */
  Opf_InitEventQueue();
}

/***************************************************************************//**
 * Function             : Opf_GetOsProfilerRecMode
 *
 * Service ID           : NA
 *
 * Description          : This function is called to get OsProfiler's record
 *                        mode
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
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
FUNC(OpfRecModeType, OPF_CODE) Opf_GetOsProfilerRecMode(void)
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

  /* Return OsProfiler's record mode */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  return pCoreOsProfiler->ddRecMode;
  #else
  return Opf_GddOsProfiler.ddRecMode;
  #endif
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
