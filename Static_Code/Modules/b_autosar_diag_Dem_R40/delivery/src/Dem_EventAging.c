/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_EventAging.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provides the interface of varialble data that ara configurable**
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                     Revision History                                       **
********************************************************************************
** Revision Date:DD-MM-YYYY By            Description                         **
********************************************************************************
** 3.3.4    31-12-2021    LanhLT         Changes made As per Redmine #33335   **
**                                                                            **
** 1.2.2    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.2.1    09-11-2018    EunKyung.Kim  Changes made As per Redmine #14481    **
**                                                                            **
** 1.2.0    16-06-2016      YoungJin.Yun  Changes made As per Redmine #1164   **
**                                                                            **
** 1.2.0    10-06-2016      YoungJin.Yun  Changes made As per Redmine #5169   **
**                                                                            **
** 1.1.0    07-01-2016      YoungJin.Yun  Changes made As per Redmine #3353,  **
**                                        #698, #3638,#2473,#3271,#2827,#1151,**
**                                        #2589                               **
**                                                                            **
** 1.0.0    06-11-2015      Autron        Initial Version                     **
*******************************************************************************/

 

/*******************************************************************************
**                     Include Section                                       **
*******************************************************************************/
#include "Dem.h"        /* DEM module Header File */
#include "Dem_Ram.h"    /* DEM Ram Header File */

/* DEM_DEV_ERROR_DETECT is defined in Dem_Cfg.h
 * Dem_Cfg.h is included by Dem.h */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"        /* Det Module Header File */
#endif

#include "SchM_Dem.h"   /* Basic s/w module Scheduler symbols Header File */ 
#include "Rte_Dem.h"
#include "Dem_Event.h"
#include "Dem_Dtc.h"
#include "Dem_EventMemory.h"
#include "Dem_EventCallback.h"
#include "Dem_EventAging.h"

/* polyspace-begin MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-begin DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
 * Function Name        : Dem_EventAgingOnEventPassed > 2
 *
 * Service ID           : None
 *
 * Description          : Update WarningIndicatorRequest bit according to
 *                        event status
 *
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event, EventStatus
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *                        DEM_TRUE : WIR bit is on
 *                        DEM_FALSE: WIR bit is off
 *
 * Preconditions        : It is called when TFTOC changed from 0 to 1.
 *                        It shall be called once during one operation cycle.
 *                        It is called when WIR bit is zero. 
 * Remarks              :
 ******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EventAgingOnEventPassed(
  const Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,
  Dem_NumOfEventMemoryEntryType MemLocation)
{
  boolean aged = DEM_FALSE;
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  /* polyspace<RTE:UNR:Not a defect:No action planned>  Avoid the runtime error of the polyspace */        
  if ((DEM_NO_EVENT != EventId) && (EventId <= Dem_Number_Of_Events) )
  #endif
  {
    Dem_EventParameterCPCType event = &Dem_Event[EventId - 1U];
    
    /*
     * [1] Aging is supported
     * [2] Threshold for aging shall be equal to 0 (zero)
     * [3] Specific aging cycle is ignored    
     * [4] CombinedDTC's WarningIndicatorRequest bit7 == 0 (@SWS_Dem_01053)
     * [5] Event is qualified as passed (this function is called when event is qualified as passed)
     * [6] TestFailedThisOperationCycle bi is ignored , as soon as event is qualified as passed
     *     Event shall be aged */
    
    /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    if ((DEM_TRUE == DEM_GET_EVENTPARAM_AGING_ALLOWED(event->ParamFieldsA))  
      && 
      (0U == event->ucAgingCycleCounterThreshold)) /* [1][2][3] */
    {
      /* @SWS_Dem_01053 */
      #if(DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_TYPE1)  
      const Dem_UdsStatusByteType udsStatusByteOld = Dem_GetDTCStatus(EventId);
      #else
      /* @SWS_Dem_00541 */
      const Dem_UdsStatusByteType udsStatusByteOld = Dem_AllEventStatusByte[EventId];    
      #endif
          
      if (0U == (udsStatusByteOld & DEM_UDS_STATUS_WIR)) /* [4][5][6] */
      {       
        Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(EventId);
           
        Dem_EvMem_AgingEvMemEntry(EventId, DTCOrigin, Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, MemLocation));            

        if (NULL_PTR != cbDTC) /* Always true */
        {
          /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */  
          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
          Dem_EvMem_SetEvMemNvBlockStatus(DTCOrigin, MemLocation, cbDTC->EvMemTriggerFlag);                    
          /* polyspace +1 DEFECT:USELESS_WRITE [Justified:Low] "Not a defect" */
          #if (DEM_UDS_STATUS_IN_EVENT_NVBLOCK == STD_ON)
          Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, cbDTC->EvMemTriggerFlag);
          #endif
          /* polyspace-begin CERT-C:MSC12-C [Justified:Low] "Because EvMemTriggerFlag can be configured by user , 
             this condition maybe always evaluate to true" */
          if (DEM_EVMEM_STATUS_DIRTY_NVM == cbDTC->EvMemTriggerFlag)
          {
            Dem_EvMem_TriggerWriteAllBlocks();
          }
          /* polyspace-end CERT-C:MSC12-C [Justified:Low] "Because EvMemTriggerFlag can be configured by user , 
             this condition maybe always evaluate to true" */
        }
        aged = DEM_TRUE;
      }
      else
      {
        /* Do nothing */
      } 
    }
  }

  return aged;
}


/*******************************************************************************
** Function Name        : Dem_EventAgingOnOperationCycleChanged               **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : Interface for BSW Components to report Errors       **
**                        during start up (even before DEM initialization)    **
**                        and normal operation.                               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId,                                            **
**                        EventStatus                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @IF_REQ: for tuning
 * Need volatile event memory map[EventId,ref,], NumOfStoredEvents 
 *
 * NumOfStoredEvents = number of stored event in the event memory 
 * event memory map 
 * map[max entry] = {
 *   {EventId 0, Index 0 of Event Memory}
 *   {EventId 1, Index 1 of Event Memory}
 *
 * loop NumOfStoredEvents
 *   eventId = map[i].EventIdRef
 *   entry = &event_memory[map[i].index]
 *
 * map is initialized in the Dem_Init()  
 *  if EventMemory[i].EventIdRef != DEM_NO_EVENT)
 *      map[indexOfEvMem].eventId = EventMemory[i].EventId
 *      map[indexOfEvMem].index = i
 **/
#if (DEM_AGING_CYCLE_COUNTER_PROCESS == DEM_PROCESS_AGINGCTR_INTERN)
FUNC(void, DEM_CODE) Dem_EventAgingOnOperationCycleChanged(
  const Dem_DTCOriginType DTCOrigin,
  const uint8 OperationCycleId)
{  
  boolean eventIsAged = DEM_FALSE;
  uint8 evStatusBlkState = DEM_EVMEM_STATUS_DIRTY;

  Dem_NumOfEventMemoryEntryType memLoc;
  #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
  uint32 maxTimeStamp = 0U;
  #endif  
  
  for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[DTCOrigin]; memLoc++)
  {
    Dem_EventIdType eventId = Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin, memLoc);
    if ((eventId <= Dem_Number_Of_Events) && (DEM_NO_EVENT != eventId))
    {      
      boolean dirty = DEM_FALSE;    
      Dem_EventParameterPCType event = &Dem_Event[eventId-1u];     
      const Dem_UdsStatusByteType EventStatusByteOld = Dem_AllEventStatusByte[eventId];      
      const Dem_UdsStatusByteType DTCStatusOld = Dem_GetDTCStatus(eventId);  

      /* [SWS_Dem_01053] 
       * If the Dem module is requested to support combination on storage, 
       * the aging shall be calculated based on the combined DTC status.
       * So, if combined event is type 1 , Combined DTC Status shall be used during aging */      
      #if(DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_TYPE1)         
      Dem_UdsStatusByteType UdsStatusByte = DTCStatusOld;
      #else
      Dem_UdsStatusByteType UdsStatusByte = EventStatusByteOld;
      #endif  

      Dem_EventMemoryEntryPtrType memEntry = Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, memLoc);       
      /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      if ((DEM_TRUE == DEM_GET_EVENTPARAM_AGING_ALLOWED(event->ParamFieldsA)) && (event->e_AgingCycleId == OperationCycleId))
      {
        const Dem_TestResultType 
        testResult = Dem_GetTestResultThisOperation(UdsStatusByte, Dem_Aging_Requieres_Tested_Cycle);
        
        if (DEM_TEST_RESULT_PASSED_THIS_OPERATION == testResult)
        {
          /* [1] AgingCycle can be different with a OperationCycle for a event.
           * [2] WarningIndicatorRequest bit == 0
           *
           * In case of TYPE1, UdsStatusByte is combined event status */     
          if ((UdsStatusByte & DEM_UDS_STATUS_WIR) == 0U) /* @SWS_Dem_01053, @SWS_Dem_00541 */           
          {          
            /* [1] AgingCycle can be different with a OperationCycle for a event.
             * [2] Shall be called when OperationCycle is changed */      
            if (0U != event->ucAgingCycleCounterThreshold)
            {
              uint8 agingCounter = 0U;
	      /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */
              dirty |= Dem_EvMem_IncAgingCounter(memEntry, &agingCounter);          
              /* Aging Completed */
              if (agingCounter >= event->ucAgingCycleCounterThreshold)
              {             
                /* Shall use the event id : Clear All event */
                Dem_EvMem_AgingEvMemEntry(eventId, DTCOrigin, memEntry);   
                /* No need if (EventStatusByteOld != Dem_AllEventStatusByte[eventId]) */
                Dem_TriggerCallbackOnUdsStatus(eventId, EventStatusByteOld,DTCStatusOld); 

                dirty = DEM_TRUE;
                eventIsAged = DEM_TRUE;                
              }
            } 
            else
            {                
              /* If Dem_Aging_Requieres_Tested_Cycle set to false and Event is not failed during this operation cycle
               * Event shall be aged.
               * in case of Dem_Aging_Requieres_Tested_Cycle set to true , this code never be reached because 
               * event was cleared already */
              Dem_EvMem_AgingEvMemEntry(eventId, DTCOrigin, memEntry);              
              /* No need if (EventStatusByteOld != Dem_AllEventStatusByte[eventId]) */
              Dem_TriggerCallbackOnUdsStatus(eventId, EventStatusByteOld,DTCStatusOld); 

              eventIsAged = DEM_TRUE;              
              dirty = DEM_TRUE;
            }            
          } 
        } /* if event tested completed as failed this operation cycle */
        else if (DEM_TEST_RESULT_FAILED_THIS_OPERATION == testResult)
        {
          /* @SWS_Dem_00489 :Aging is independent of the UDS status bit 3 (ConfirmedDTC) and
           * therefore independent of the fault confirmation*/
          /* Clear aging counter when event status is changed to failed */
	   /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */ 
           dirty |= Dem_EvMem_SetAgingCounter(memEntry, 0U);
        } 
        else 
        {
          /* nothing to do */
        }      
      }

      /* Searching max time stamp */
      #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
      if (DEM_NO_EVENT != Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin, memLoc))
      {
        uint32 currTimeStamp = Dem_EvMem_GetTimeStamp(memEntry);       
        if (maxTimeStamp < currTimeStamp)
        {
          maxTimeStamp =  currTimeStamp;
        }
      }
      #endif
          
      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */    
      if (OperationCycleId == event->e_OperationCycleId)
      {
        if ((UdsStatusByte & DEM_BITMASK_RESET_TRIP) == 0U)              
        {
          /* [SWS_Dem_00391] 
           * Dem_SetOperationCycleState[
           *    OperationCycleId == DemOperationCycleRef && 
           *    testFailedThisOperationCycle == 0 && 
           *    testNotCompleteThisOperationCycle == 0] /failure counter = 0 */
	  /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */  
          dirty |= Dem_EvMem_SetFailureCounter(memEntry, 0U);
        } 
      }

      if (DEM_TRUE == dirty)
      {
        Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(eventId);
        if (NULL_PTR != cbDTC)
        {
	  /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */  
	  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */   
          evStatusBlkState |= cbDTC->EvMemTriggerFlag;        
          Dem_EvMem_SetEvMemNvBlockStatus(DTCOrigin, memLoc, cbDTC->EvMemTriggerFlag);            
        }
      }      
    }
  } 

  #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
  Dem_MaxTimeStamp[DTCOrigin] = maxTimeStamp;
  #endif

  if ((DEM_TRUE == Dem_Uds_Status_In_Event_NvBlock) && (DEM_TRUE == eventIsAged))
  {
    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, evStatusBlkState);
  }  
}
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-end DEFECT:USELESS_IF [Justified:Low] "Not a defect" */