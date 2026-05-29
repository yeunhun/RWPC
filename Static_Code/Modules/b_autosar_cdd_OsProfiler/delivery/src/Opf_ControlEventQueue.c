/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_ControlEventQueue.c                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Implementation of ControlEventQueue module                    **
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
** 1.5.4     14-Dec-2021    YH.Han        Redmine #33448                      **
** 1.5.2     24-Nov-2020    YH.Han        Redmine #26755                      **
** 1.3.0     29-Oct-2018    YH.Han        Redmine #12853                      **
** 1.1.2     30-Aug-2017    MJ.Woo        Redmine #6959                       **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE:STD_LIB:Not a defect:Justify with annotations> function is called with a valid arguments that are confirmed by testing */
/* polyspace:begin<RTE: OBAI : Not a defect : Justify with annotations > configured array index */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_Cfg.h"
#include "Opf_ControlEventQueue.h"
#include "Opf_Ram.h"
#include "Opf_Task.h"
#include <string.h>     /* memcpy and memset */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
static FUNC(void, OPF_CODE) Opf_AddNewProfileEvent(Tdd_Opf_Event *pEvent);

#define OPF_START_SEC_CODE
#include "MemMap.h"

/***************************************************************************//**
 * Function             : Opf_InitEventQueue
 *
 * Service ID           : NA
 *
 * Description          : This function initializes event queue and profile
 *                        event queue
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddEventQ, Opf_GddProfileEventQ
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_InitEventQueue(void)
{
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_EventQ *pCoreEventQ;
  Tdd_Opf_ProfileEventQ *pCoreProfileEventQ;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreEventQ = OPF_GET_EVENTQ_INFO(LddCoreID);
  pCoreProfileEventQ = OPF_GET_PROFILE_EVENTQ_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* initialize the Queue length */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  pCoreEventQ->ddEventQueueSize = Opf_Event_Queue_Length;
  pCoreProfileEventQ->ddEventQueueSize = Opf_Event_Queue_Length;
  #else
  Opf_GddEventQ.ddEventQueueSize = Opf_Event_Queue_Length;
  Opf_GddProfileEventQ.ddEventQueueSize = Opf_Event_Queue_Length;
  #endif

  /* initialize the last of the event position */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  pCoreEventQ->ddLastEventPos = OPF_ZERO;
  pCoreProfileEventQ->ddLastEventPos = OPF_ZERO;
  #else
  Opf_GddEventQ.ddLastEventPos = OPF_ZERO;
  Opf_GddProfileEventQ.ddLastEventPos = OPF_ZERO;
  #endif

  /* initialize count of event */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  pCoreEventQ->ddEventCount = OPF_ZERO;
  #else
  Opf_GddEventQ.ddEventCount = OPF_ZERO;
  #endif
}

/***************************************************************************//**
 * Function             : Opf_AddNewEvent
 *
 * Service ID           : NA
 *
 * Description          : This function insert new event to event queue and
 *                        increase event count.
 *                        This function also insert new event to profile event
 *                        queue when Record Mode of OS Profiler is PROFILE
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            pEvent        Reference to an Event
 *
 * @return              : void
 *
 * @pre                 : Opf_InitEventQueue() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddEventQ, Opf_GddOsProfiler
 *
 *                        Function(s) invoked    :
 *                        memcpy(), Opf_AddNewProfileEvent()
 *
 * @ingroup               OPF-SRS-FUN-002, OPF-SRS-FUN-003, OPF-SRS-FUN-005,
 *                        OPF-SRS-FUN-006, OPF-SRS-FUN-007
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_AddNewEvent(Tdd_Opf_Event *pEvent)
{
  uint16 LusIdx;
  uint16 LusSize;
  Tdd_Opf_Event *pEventEntry;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_EventQ *pCoreEventQ;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreEventQ = OPF_GET_EVENTQ_INFO(LddCoreID);
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* polyspace-begin RTE:UNR [Not a Defect] "necessary for NULL pointer check " */
  /* if pEvent is NULL, do nothing */
  if(pEvent != OPF_NULL)
  /* polyspace-end RTE:UNR */
  {
  #if (OPF_MULTICORE_ENABLED == STD_ON)
    LusIdx = pCoreEventQ->ddLastEventPos;
    LusSize = pCoreEventQ->ddEventQueueSize;
  #else
    LusIdx = Opf_GddEventQ.ddLastEventPos;
    LusSize = Opf_GddEventQ.ddEventQueueSize;
  #endif

    /* if current index is larger than queue size, do nothing */
    if(LusIdx < LusSize)
    {
      LusIdx++;

      if(LusIdx >= LusSize)
      {
        LusIdx = OPF_ZERO;
      }
      #if (OPF_MULTICORE_ENABLED == STD_ON)
      pEventEntry = &(pCoreEventQ->ddEvent[LusIdx]);
      #else
      pEventEntry = &(Opf_GddEventQ.ddEvent[LusIdx]);
      #endif

      /* add new event into event queue */
      /* polyspace<MISRA-C3:D4.11:Not a defect:Justify with annotations> 1st argument is configured array index and 2nd argument is checked at upper 'if' condition */
      memcpy(pEventEntry, pEvent, Sizeof_Tdd_Opf_Event);

      #if (OPF_MULTICORE_ENABLED == STD_ON)
      pCoreEventQ->ddLastEventPos = LusIdx;
      pCoreEventQ->ddEventCount++;
      #else
      Opf_GddEventQ.ddLastEventPos = LusIdx;
      Opf_GddEventQ.ddEventCount++;
      #endif
    }

    #if (OPF_MULTICORE_ENABLED == STD_ON)
    if(pCoreOsProfiler->ddRecMode == OPF_RECMODE_PROFILE)
    #else
    if(Opf_GddOsProfiler.ddRecMode == OPF_RECMODE_PROFILE)
    #endif
    {
      Opf_AddNewProfileEvent(pEvent);
    }
  }
}

/***************************************************************************//**
 * Function             : Opf_AddNewProfileEvent
 *
 * Service ID           : NA
 *
 * Description          : This function insert new event to profile event queue.
 *                        If profile event queue is full, set Record Mode of
 *                        OS Profiler to EVENT(Event only)
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            pEvent        Reference to an Event
 *
 * @return              : void
 *
 * @pre                 : Opf_InitEventQueue() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddProfileEventQ, Opf_GddOsProfiler
 *
 *                        Function(s) invoked    :
 *                        memcpy()
 *
 * @ingroup               OPF-SRS-FUN-002, OPF-SRS-FUN-003
 ******************************************************************************/
static FUNC(void, OPF_CODE) Opf_AddNewProfileEvent(Tdd_Opf_Event *pEvent)
{
  uint16 LusIdx;
  uint16 LusSize;
  Tdd_Opf_Event *pEventEntry;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_ProfileEventQ *pCoreProfileEventQ;
  Tdd_Opf_OsProfiler *pCoreOsProfiler;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreProfileEventQ = OPF_GET_PROFILE_EVENTQ_INFO(LddCoreID);
  pCoreOsProfiler = OPF_GET_OS_PROFILER_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* polyspace-begin RTE:UNR [Not a Defect] "necessary for NULL pointer check " */
  /* if pEvent is NULL, do nothing */
  if(pEvent != OPF_NULL)
  /* polyspace-end RTE:UNR */
  {
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    LusIdx = pCoreProfileEventQ->ddLastEventPos;
    LusSize = pCoreProfileEventQ->ddEventQueueSize;
    #else
    LusIdx = Opf_GddProfileEventQ.ddLastEventPos;
    LusSize = Opf_GddProfileEventQ.ddEventQueueSize;
    #endif

    /* if current index is larger than queue size, do nothing */
    if(LusIdx < LusSize)
    {
      LusIdx++;

      #if (OPF_MULTICORE_ENABLED == STD_ON)
      pEventEntry = &(pCoreProfileEventQ->ddEvent[LusIdx]);
      #else
      pEventEntry = &(Opf_GddProfileEventQ.ddEvent[LusIdx]);
      #endif

      /* add new event into profile event queue */
      /* polyspace<MISRA-C3:D4.11:Not a defect:Justify with annotations> 1st argument is configured array index and 2nd argument is checked at upper 'if' condition */
      memcpy(pEventEntry, pEvent, Sizeof_Tdd_Opf_Event);

      #if (OPF_MULTICORE_ENABLED == STD_ON)
      pCoreProfileEventQ->ddLastEventPos = LusIdx;
      #else
      Opf_GddProfileEventQ.ddLastEventPos = LusIdx;
      #endif
    }

    if(LusIdx == (LusSize - OPF_ONE))
    {
      #if (OPF_MULTICORE_ENABLED == STD_ON)
      pCoreOsProfiler->ddRecMode = OPF_RECMODE_EVENT;
      #else
      Opf_GddOsProfiler.ddRecMode = OPF_RECMODE_EVENT;
      #endif
    }
  }
}

/***************************************************************************//**
 * Function             : Opf_GetLastEvent
 *
 * Service ID           : NA
 *
 * Description          : This function returns pointer of last event
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : Tdd_Opf_Event *
 *                        - NULL_PTR : If last position of event is invalid
 *                        - other : If last position of event is valid
 *
 * @pre                 : Opf_InitEventQueue() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddEventQ
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
/* polyspace-begin MISRA-C3:20.7 [Not a Defect] "AUTOSAR compiler abstraction" */
FUNC(Tdd_Opf_Event*, OPF_CODE) Opf_GetLastEvent(void)
/* polyspace-end MISRA-C3:20.7 */
{
  uint16 LusIdx;
  Tdd_Opf_Event *pEventEntry;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_EventQ *pCoreEventQ;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreEventQ = OPF_GET_EVENTQ_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  LusIdx = pCoreEventQ->ddLastEventPos;
  #else
  LusIdx = Opf_GddEventQ.ddLastEventPos;
  #endif

  /* Check if last position of event is valid */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if(LusIdx < pCoreEventQ->ddEventQueueSize)
  #else
  if(LusIdx < Opf_GddEventQ.ddEventQueueSize)
  #endif
  {
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    pEventEntry = &(pCoreEventQ->ddEvent[LusIdx]);
    #else
    pEventEntry = &(Opf_GddEventQ.ddEvent[LusIdx]);
    #endif
  }
  else
  {
    pEventEntry = NULL_PTR;
  }

  return pEventEntry;
}

/***************************************************************************//**
 * Function             : Opf_GetLastProfileEvent
 *
 * Service ID           : NA
 *
 * Description          : This function returns pointer of last profiled event
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : Tdd_Opf_Event *
 *                        - NULL_PTR : If last position of profiled event is
 *                                     invalid
 *                        - other : If last position of profiled event is valid
 *
 * @pre                 : Opf_InitEventQueue() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddProfileEventQ
 *
 *                        Function(s) invoked    :
 *                        None
 *
 * @ingroup               OPF-SRS-FUN-002, OPF-SRS-FUN-003
 ******************************************************************************/
/* polyspace-begin MISRA-C3:20.7 [Not a Defect] "AUTOSAR compiler abstraction" */
FUNC(Tdd_Opf_Event*, OPF_CODE) Opf_GetLastProfileEvent(void)
/* polyspace-end MISRA-C3:20.7 */
{
  uint16 LusIdx;
  Tdd_Opf_Event *pEventEntry;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_ProfileEventQ *pCoreProfileEventQ;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreProfileEventQ = OPF_GET_PROFILE_EVENTQ_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  LusIdx = pCoreProfileEventQ->ddLastEventPos;
  #else
  LusIdx = Opf_GddProfileEventQ.ddLastEventPos;
  #endif

  /* Check if last position of profiled event is valid */
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  if(LusIdx < pCoreProfileEventQ->ddEventQueueSize)
  #else
  if(LusIdx < Opf_GddProfileEventQ.ddEventQueueSize)
  #endif
  {
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    pEventEntry = &(pCoreProfileEventQ->ddEvent[LusIdx]);
    #else
    pEventEntry = &(Opf_GddProfileEventQ.ddEvent[LusIdx]);
    #endif
  }
  else
  {
    pEventEntry = NULL_PTR;
  }

  return pEventEntry;
}

/***************************************************************************//**
 * Function             : Opf_SetLastEvent
 *
 * Service ID           : NA
 *
 * Description          : This function updates last queued event
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            pEvent        Reference to an Event
 *
 * @return              : void
 *
 * @pre                 : Opf_InitEventQueue() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddEventQ
 *
 *                        Function(s) invoked    :
 *                        memcpy()
 *
 * @ingroup               OPF-SRS-FUN-005
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_SetLastEvent(Tdd_Opf_Event *pEvent)
{
  uint16 LusIdx;
  uint16 LusSize;
  Tdd_Opf_Event *pEventEntry;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_EventQ *pCoreEventQ;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreEventQ = OPF_GET_EVENTQ_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  /* polyspace-begin RTE:UNR [Not a Defect] "necessary for NULL pointer check " */
  /* if pEvent is NULL, do nothing */
  if(pEvent != OPF_NULL)
  /* polyspace-end RTE:UNR */
  {
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    LusIdx = pCoreEventQ->ddLastEventPos;
    LusSize = pCoreEventQ->ddEventQueueSize;
    #else
    LusIdx = Opf_GddEventQ.ddLastEventPos;
    LusSize = Opf_GddEventQ.ddEventQueueSize;
    #endif

    /* if the current index is larger than the queue size, do nothing */
    if(LusIdx < LusSize)
    {
      #if (OPF_MULTICORE_ENABLED == STD_ON)
      pEventEntry = &(pCoreEventQ->ddEvent[LusIdx]);
      #else
      pEventEntry = &(Opf_GddEventQ.ddEvent[LusIdx]);
      #endif

      /* update the last event */
      /* polyspace<MISRA-C3:D4.11:Not a defect:Justify with annotations> 1st argument is configured array index and 2nd argument is checked at upper 'if' condition */
      memcpy(pEventEntry, pEvent, Sizeof_Tdd_Opf_Event);
    }
  }
}

/***************************************************************************//**
 * Function             : Opf_ClearEventQueue
 *
 * Service ID           : NA
 *
 * Description          : This function sets all event queue data to zero
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : Opf_InitEventQueue() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddEventQ
 *
 *                        Function(s) invoked    :
 *                        memset()
 *
 * @ingroup               OPF-SRS-FUN-017
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_ClearEventQueue(void)
{
  uint16 LusIdx;
  uint16 LusSize;
  Tdd_Opf_Event *pEventEntry;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_EventQ *pCoreEventQ;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreEventQ = OPF_GET_EVENTQ_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  LusSize = pCoreEventQ->ddEventQueueSize;
  #else
  LusSize = Opf_GddEventQ.ddEventQueueSize;
  #endif

  for(LusIdx = OPF_ZERO; LusIdx < LusSize; LusIdx++)
  {
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    pEventEntry = &(pCoreEventQ->ddEvent[LusIdx]);
    #else
    pEventEntry = &(Opf_GddEventQ.ddEvent[LusIdx]);
    #endif

    /* clear the event */
    /* polyspace<MISRA-C3:D4.11:Not a defect:Justify with annotations> 1st argument is configured array index */
    memset(pEventEntry, OPF_ZERO, Sizeof_Tdd_Opf_Event);
  }
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  pCoreEventQ->ddLastEventPos = OPF_ZERO;
  #else
  Opf_GddEventQ.ddLastEventPos = OPF_ZERO;
  #endif
}

/***************************************************************************//**
 * Function             : Opf_UpdateProfiledEventQueue
 *
 * Service ID           : NA
 *
 * Description          : This function updates current profiled event from
 *                        event queue and prepares queue that will be saved
 *                        next event
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameter            : None
 *
 * @return              : void
 *
 * @pre                 : Opf_InitEventQueue() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Opf_GddProfileEventQ, Opf_GddEventQ
 *
 *                        Function(s) invoked    :
 *                        memcpy(), memset()
 *
 * @ingroup               OPF-SRS-FUN-002, OPF-SRS-FUN-003
 ******************************************************************************/
FUNC(void, OPF_CODE) Opf_UpdateProfiledEventQueue(void)
{
  uint16 LusIdx;
  uint16 LusEventQueueIdx;
  uint16 LusSize;
  uint16 LusEventQueueSize;
  Tdd_Opf_Event *pProfiledEventEntry;
  Tdd_Opf_Event *pEventEntry;
  #if (OPF_MULTICORE_ENABLED == STD_ON)
  CoreIDType LddCoreID;
  Tdd_Opf_EventQ *pCoreEventQ;
  Tdd_Opf_ProfileEventQ *pCoreProfileEventQ;

  /* polyspace:begin<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  LddCoreID = GetCoreID();
  pCoreEventQ = OPF_GET_EVENTQ_INFO(LddCoreID);
  pCoreProfileEventQ = OPF_GET_PROFILE_EVENTQ_INFO(LddCoreID);
  /* polyspace:end<MISRA-C3:D4.1:Not a defect:Justify with annotations> configured array index */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> range checked at caller */
  #endif

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  LusSize = pCoreProfileEventQ->ddEventQueueSize;
  LusEventQueueIdx = pCoreEventQ->ddLastEventPos;
  LusEventQueueSize = pCoreEventQ->ddEventQueueSize;
  #else
  LusSize = Opf_GddProfileEventQ.ddEventQueueSize;
  LusEventQueueIdx = Opf_GddEventQ.ddLastEventPos;
  LusEventQueueSize = Opf_GddEventQ.ddEventQueueSize;
  #endif

  /* get first index of event queue to copy */
  if(LusEventQueueIdx >= (LusEventQueueSize/OPF_TWO))
  {
    LusEventQueueIdx = (LusEventQueueIdx-(LusEventQueueSize/OPF_TWO)) + OPF_ONE;
  }
  else
  {
    LusEventQueueIdx = LusEventQueueIdx + (LusEventQueueSize/OPF_TWO) + OPF_ONE;
  }

  /* update and clear profiled event queue */
  for(LusIdx = OPF_ZERO; LusIdx < LusSize; LusIdx++)
  {
    #if (OPF_MULTICORE_ENABLED == STD_ON)
    pProfiledEventEntry = &(pCoreProfileEventQ->ddEvent[LusIdx]);
    pEventEntry = &(pCoreEventQ->ddEvent[LusEventQueueIdx]);
    #else
    pProfiledEventEntry = &(Opf_GddProfileEventQ.ddEvent[LusIdx]);
    pEventEntry = &(Opf_GddEventQ.ddEvent[LusEventQueueIdx]);
    #endif

    if(LusIdx < (LusSize/OPF_TWO))
    {
      /* update the event from event queue */
      /* polyspace<MISRA-C3:D4.11:Not a defect:Justify with annotations> 1st and 2nd argumentr are configured array index */
      memcpy(pProfiledEventEntry, pEventEntry, Sizeof_Tdd_Opf_Event);
    }
    else
    {
      /* clear the event */
      /* polyspace<MISRA-C3:D4.11:Not a defect:Justify with annotations> 1st argument is configured array index */
      memset(pProfiledEventEntry, OPF_ZERO, Sizeof_Tdd_Opf_Event);
    }

    /* increase index of event queue to copy */
    LusEventQueueIdx++;
    if(LusEventQueueIdx >= LusEventQueueSize)
    {
      LusEventQueueIdx = OPF_ZERO;
    }
  }

  #if (OPF_MULTICORE_ENABLED == STD_ON)
  pCoreProfileEventQ->ddLastEventPos = (LusSize/OPF_TWO) - OPF_ONE;
  #else
  Opf_GddProfileEventQ.ddLastEventPos = (LusSize/OPF_TWO) - OPF_ONE;
  #endif
}

#define OPF_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<RTE:STD_LIB:Not a defect:Justify with annotations> function is called with a valid arguments that are confirmed by testing */
/* polyspace:end<RTE: OBAI : Not a defect : Justify with annotations > configured array index */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
