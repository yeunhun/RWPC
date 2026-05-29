/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_Event.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of management of diagnostic event                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date:DD-MM-YYYY By            Description                         **
********************************************************************************
** 3.3.4    31-12-2021    LanhLT          Changes made As per Redmine #33335  **
**                                                                            **
** 1.4.2    16-02-2021    EunKyung.Kim    Changes made As per Redmine #28250  **
**                                                                            **
** 1.4.1    01-06-2020    EunKyung.Kim    Changes made As per Redmine #20595  **
**                                                                            **    
** 1.4.0    10-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.3.3    09-11-2018   EunKyung.Kim     Changes made As per Redmine #14481  **
**                                                                            **
** 1.3.2    20-03-2018  EunKyung.Kim      Changes made As per Redmine #11177  **
**                                                                            **
** 1.3.1    20-07-2017  EunKyung.Kim      Changes made As per Redmine #9294   **
**                                                                            **
** 1.3.0    16-11-2016  YoungJin.Yun      Changes made As per Redmine #6549   **
**                                                                            **
** 1.2.0    16-05-2016  YoungJin.Yun      Changes made As per Redmine #1164   **
**                                                                            **
** 1.1.1    03-03-2016  YoungJin.Yun      Changes made As per Redmine #4215   **
**                                                                            **
** 1.1.0    07-01-2016  YoungJin.Yun      Changes made As per Redmine #3353,  **
**                                        #698 , #3638, #2473, #3271, #2827,  **
**                                        #1151, #2589                        **
**                                                                            **
** 1.0.0    07-02-2015  YoungJin.Yun      Initial Version                     **
*******************************************************************************/

/*
 * @IF_REQ List
 *
 * 1. Dem_GetTestResultThisOperation shall be optimized
 *   (status & mask) == target status
 *
 * 2.  if (event->aaEventDestination == DTCOrigin) =>
 *     if ((MemoryId & DTCOrigin) ==   DTCOrigin)
 *     
 */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"            /* DEM module Header File */
#include "Dem_Ram.h"        /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"            /* Det Module Header File */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */
#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "Dem_EventMemory.h"
#include "Dem_Event.h"
#include "Dem_Indicator.h"
#include "Dem_EventCallback.h"
#include "Dem_EventDebounce.h"
#include "Dem_Dtc.h"
#include "Dem_EventAging.h"


/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace-begin MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:17.8 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* static uint32 TimeForTest(uint32 cnt); */

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
static FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventStorageConditionState(
    Dem_EventParameterCPCType event);
#endif   


/******************************************************************************
 * Function Name        : Dem_DTCOriginBelongToEvent >2
 *
 * Service ID           : None
 *
 * Description          : Checks whether the DTCOrigin of an event correspond 
 *                        to the input DTCOrigin.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event
 *                        DTCOrigin
 *                        
 * InOut parameter      : None
 *
 * Output Parameters    : Std_ReturnType
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *
 *****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_DTCOriginBelongToEvent(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin)
{
  boolean belongToEvent = DEM_FALSE;
  
  if (
    (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin) 

  #if(DEM_MAX_NUMBER_EVENT_ENTRY_SEC > 0U)  
    || (DEM_DTC_ORIGIN_SECONDARY_MEMORY == DTCOrigin)
  #endif 

  #if(DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U)  
    || (DEM_DTC_ORIGIN_MIRROR_MEMORY == DTCOrigin)
  #endif

  #if(DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U)  
    || (DEM_DTC_ORIGIN_PERMANENT_MEMORY == DTCOrigin)
  #endif
  )
  {
    #if(DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)
    Dem_EventParameterCPCType event = &Dem_Event[EventId-1U];
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    if (event->aaEventDestination == DTCOrigin)
    {
      belongToEvent = DEM_TRUE;
    }
    #endif
  }

  return belongToEvent;
}


/******************************************************************************
 * Function Name        : Dem_GetEventConditionsAndControlDTCSetting == *1
 *
 * Service ID           : None
 *
 * Description          : Checks whether enable condions are true or not
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        : 
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 ******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) 
Dem_GetEventConditionsAndControlDTCSetting(Dem_EventIdType EventId)
{
  /*
   * pointer to a event should be verified by the caller
   */
  Std_ReturnType retVal = E_OK;
  Dem_EventParameterCPCType event = &Dem_Event[EventId - 1U];    

  #if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
  if (0U != event->ucNumOfEnableCondition)
  {
    uint16 i = 0u;
    const uint16 NumOfCond = event->PointToEnableConditionMap + event->ucNumOfEnableCondition;  

    /* Check the status of all enable conditions configured for the event */
    if (NumOfCond <= Dem_Max_ListOfEnableConditionId)
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */  
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      for(i = event->PointToEnableConditionMap; i < NumOfCond ; i++)
      {
        if( (boolean)DEM_FALSE == Dem_GetEnableConditionStatus(i))
        {
          retVal = E_NOT_OK;
          break;
        }
      }
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
  }
  if (E_OK == retVal)  
  #endif
  {
    if (event->e_PointToDTC < Dem_Max_Number_Of_DTC)
    {    
      P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) 
      cbDTC = &Dem_GaaCombinedDtc[event->e_PointToDTC];
      
      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. */    
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      if (cbDTC->ddDtcGroup < Dem_Max_Num_Grp_DTC)
      {
        Dem_DTCKindType kind = cbDTC->ddDtcKind;

        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        /* Check DTC Disable DTC Setting of AllDTC or
         * Check DTC Disable DTC Setting of Particular Group */        
        if ((Dem_GucDisableDtcSettingDTCKind == kind) &&
            ( ((boolean)DEM_TRUE == Dem_GblDisableDtcSettingAllDTC) ||
              ((boolean)DEM_TRUE == Dem_GaaDisableDtcSettingGroupDTC[cbDTC->ddDtcGroup]) ) )
        {
          retVal = E_NOT_OK;
        }
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
      else
      {
        /* Det Error */
        retVal = E_NOT_OK;
      }
    }
    else
    {
      /* If event does not has a DTC, condition will be E_OK */
      /* retVal = E_OK;*/
    } 
  }

  
  return retVal;
}

/*******************************************************************************
 ** Function Name       : Dem_MainfunctionBswEvents                           **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Processes Bsw events                                **
 **                                                                           **
 ** Sync/Async          : Asynchronous                                        **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if (DEM_BSW_ERROR_BUFFER_SIZE > 0U)
FUNC(void, DEM_CODE) Dem_MainfunctionBswEvents(void)
{
  uint8 idx;
  Dem_EventIdType eventId;
  Dem_EventStatusType eventStatus;

  /* @IF_REQ: 10 events? */
  /* No preempted by Dcm_MainFuntion, so no need 'SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION' */
  if ((boolean)DEM_FALSE == Dem_EvMem_Lock())
  {
    /* Load the BSW buffer to appropriate event memory */
    for(idx = 0u; idx < Dem_BSW_Error_Buffer_Size; idx++)
    {
      /* Check for valid event id */
      SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION(); 
      eventId = Dem_GaaErrorBuffer[idx];
       
      if ((boolean)DEM_TRUE == Dem_EventIdIsValid(eventId))
      {
        eventStatus = Dem_GaaErrorBufferStatus[idx];    
        Dem_GaaErrorBuffer[idx] = DEM_NO_EVENT;
        Dem_GaaErrorBufferStatus[idx] = 0U;    
        
        SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();

        (void)Dem_ProcessEventStatus(eventId, eventStatus);
      }
      else
      {
        SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();
      }
    }
    /*
    Initialize the buffer ReadIdx to zero 
    after processing all the events 
     */
    SchM_Enter_Dem_REQUEST_BUFFER_PROTECTION();      
    Dem_GucErrorWriteIndex = 0U;    
    SchM_Exit_Dem_REQUEST_BUFFER_PROTECTION();
  }
}

FUNC(void, DEM_CODE) Dem_InitBswEventQueue(void)
{
  /* No need 'critical section' because this function is called by Dem_PreInit() */
  uint8 idx; /* DemBswErrorBufferSize MAX : 255 */
  for(idx = 0u; idx < Dem_BSW_Error_Buffer_Size; idx++)
  {
    Dem_GaaErrorBuffer[idx] = DEM_NO_EVENT;
    Dem_GaaErrorBufferStatus[idx] = 0U;      
  }
  Dem_GucErrorWriteIndex = 0U;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_ProcessEventStatus 
 **
 ** Service ID          : None
 **
 ** Description         : It is used to process the event status.
 **
 ** Sync/Async          : Synchronous/Asynchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : EventId
 **                       EventStatus
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : Std_ReturnType
 **                       E_NOT_OK : set of event status failed or could not be accepted
 **                        @Dem183
 **                          [1] the operation cycle configured for this event has not been started
 **                          [2] enable condition for this event has been disabled
 ** Preconditions       : None
 **
 ** Remarks             : 
 *******************************************************************************/
 
FUNC(Std_ReturnType, DEM_CODE) Dem_ProcessEventStatus(
    Dem_EventIdType EventId,
    Dem_EventStatusType EventStatus)
{
  Std_ReturnType retVal = E_OK;

  /***************************************************************************
   *           General diagnostic event storage processing                   *
   *           [ Refer to Figure 7.25 ]                                      *
   ***************************************************************************/
  
  /* polyspace<RTE:UNR:Not a defect:No action planned> Avoid to runtime error of the polyspace */
  if ((EventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == EventId))
  {  
    retVal = E_NOT_OK;  
  }
  /***************************************************************************
   *           Check validity of operation cycle & enable conditions         *
   ***************************************************************************/     
  else if (E_NOT_OK == Dem_GetEventConditionsAndControlDTCSetting(EventId))
  {
    retVal = E_NOT_OK;
  } 
  else if ((boolean)DEM_FALSE == Dem_GetLocksByEventIdAndEvMem(EventId))
  { 
    retVal = E_NOT_OK;
  }  
  else 
  {
    Dem_EventParameterCPCType event = &Dem_Event[EventId - 1U];    
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    uint8 debounceType = DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(event->ParamFieldsA);
    Dem_NumOfEventMemoryEntryType memLocOld = Dem_EvMemToEventMap[EventId];  
    Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(EventId);
    
    /*************************************************************************
     *                 Process event debouncing                              *
     *************************************************************************/ 
    /* polyspace-begin MISRA-C3:17.8 [Justified:Low] "Not a defect" */
    if (DEM_DEBOUNCE_NO_DEBOUNCE_BASED != debounceType)       
    {      
      #if (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > 0U)
      if (DEM_DEBOUNCE_MONITOR_BASED == debounceType)     
      { 
        if ((DEM_EVENT_STATUS_PASSED != EventStatus) &&
            (DEM_EVENT_STATUS_FAILED != EventStatus))
        {
          /* [SWS_Dem_00437] Note: The monitor is not allowed to report the event states
           * DEM_EVENT_STATUS_PREFAILED and DEM_EVENT_STATUS_PREPASSED for monitor internal debouncing. */                
	      EventStatus = DEM_EVENT_STATUS_UNDEFINED;
          retVal = E_NOT_OK;
        }
      }
      else
      #endif
      #if (DEM_NUMBER_OF_PRE_DEBOUNCE_COUNTER > 0U)     
      if (DEM_DEBOUNCE_COUNTER_BASED == debounceType)
      {
        if ((boolean)DEM_FALSE == Dem_ProcessDebounceCounterBased(event->ucIndexOfDebounceAry, &EventStatus))
        {
          EventStatus = DEM_EVENT_STATUS_UNDEFINED;
        }
      }
      else
      #endif
      #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON)
      if (DEM_DEBOUNCE_TIME_BASED == debounceType)
      {
        if ((boolean)DEM_FALSE == Dem_ProcessDebounceTimeBased(event->ucIndexOfDebounceAry, &EventStatus))
        {
          EventStatus = DEM_EVENT_STATUS_UNDEFINED;
        }
      }
      else
      #endif    
      {
        EventStatus = DEM_EVENT_STATUS_UNDEFINED;
        retVal = E_NOT_OK;
      }
    }
    /* polyspace-end MISRA-C3:17.8 [Justified:Low] "Not a defect" */
    /* qualified as PASSED */
    if (
      (DEM_EVENT_STATUS_PASSED == EventStatus) &&
      (
        (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TNCTOC)) || /* Not Tested */
        (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF))        /* Failed To Passed */
        /* @IF_REQ : if TF was cleared by API ResetEventStatus? */
      )
    )
    {
      boolean statusDirty = DEM_FALSE;

      const Dem_UdsStatusByteType DTCStatusByteOld = Dem_GetDTCStatus(EventId);
      const Dem_UdsStatusByteType EventStatusByteOld = Dem_AllEventStatusByte[EventId];      
      const Dem_DTCOriginType DTCOrigin = event->aaEventDestination;

      /*
       * (1) Clears TestFailed bit to 0
       */
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      DEM_CLR_UDSSTATUSBYTE(EventId, 
        (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF     | /* Bit 0 TestNotCompletedThisOperationCycle */
        (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC | /* Bit 4 TestNotCompletedSinceLastClear     */ 
        (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCTOC); /* Bit 6 TestNotCompletedThisOperationCycle */                    
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

      if ((DEM_NO_DTC_ORIGIN != DTCOrigin) && (NULL_PTR != cbDTC))
      {
        boolean eventIsAged = DEM_FALSE;        
        /*
         * (2) Clears WarningIndicatorRequest bit 7 to 0 immediately when healing threshold is 0
         *
         * [1] @RfC 63657,Always the operation cycle of indicator is DemOperationCycleRef
         * [2] Indicator is supported
         * [3] A specific event's WarningIndicatorRequest bit = 1 
         * [4] Only indicator is set when event has a DTC

         * WarningIndicatorRequestOffCondition : Counter:N/A
         * Dem_DeActivateIndicatorOnEventPassed shall be called regardless DEM_UDS_STATUS_WIR
         * because Failure Counter shall be initialized */
        statusDirty = Dem_DeActivateIndicatorOnEventPassed(EventId);

        /* if event is stored */
	    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
        if (memLocOld < Dem_SizeOfEventMemory[DTCOrigin])
        {
          /* (3) Delete Event immediately when aging threshold is 0 */
          eventIsAged = Dem_EventAgingOnEventPassed(EventId, DTCOrigin, memLocOld);
        }
        /*
         * (4) Clears prestored freeze frame buffer when EventStatus changes from passed to failed
         *
         * @SWS_Dem_00465
         * If an event gets qualified as passed(UDS DTC status bit 0 changes from 1 to 0)
         * the Dem module shall release the pre-stored freeze frame for the specific event. */
        #if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
        if ( 0U != (EventStatusByteOld & (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF) )
        {
          (void)Dem_ClearSinglePrestoredFFbyEventId(EventId);
        }
        #endif

        if ((boolean)DEM_FALSE == eventIsAged)
        {
          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
          /* polyspace-begin DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because EvMemTriggerFlag can be configured by user , 
             this condition maybe always evaluate to true" */
          uint8 triggerNvStorage = (DEM_EVMEM_STATUS_DIRTY_NVM == cbDTC->EvMemTriggerFlag) ?
            Dem_EvMem_EventIsImmediateStorage(DTCOrigin, EventId) : DEM_EVMEM_STATUS_DIRTY;
          /* polyspace-end DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because EvMemTriggerFlag can be configured by user , 
           this condition maybe always evaluate to true" */

          if (DEM_EVMEM_STATUS_DIRTY_NVM == Dem_EvMem_TriggerNvDataStorage(
            EventId, DTCOrigin, EventStatusByteOld, triggerNvStorage, DEM_FALSE, statusDirty))
          {
            Dem_EvMem_TriggerWriteAllBlocks();
          }
        }
      }
      /* Trigger callback EventStatusChanged, UdsStatusChanged */
      if (EventStatusByteOld != Dem_AllEventStatusByte[EventId])
      {
        Dem_TriggerCallbackOnUdsStatus(EventId, EventStatusByteOld, DTCStatusByteOld);
      }

      #if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
      Dem_ProcessIumpr( event, Dem_AllEventStatusByte[EventId]);
      #endif
    }
    /* qualified as FAILED
     * @Dem184: Store an event which is qualified as failed(UDS DTC status bit 0 changes from 0 to 1)
     * @RfC 61309, PassedToFailed problem */
    else if (
      (DEM_EVENT_STATUS_FAILED == EventStatus)
        &&
      (
        (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TNCTOC)) || /* Tested at first */
        (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF)) ||   /* Passed to Failed */
        ((NULL_PTR != cbDTC) && (DEM_NO_EVMEM_ENTRY == memLocOld))  /* Not stored */
      )
    )
    {
      boolean statusDirty = DEM_FALSE;
        
      const Dem_UdsStatusByteType DTCStatusByteOld = Dem_GetDTCStatus(EventId);
      const Dem_UdsStatusByteType EventStatusByteOld = Dem_AllEventStatusByte[EventId];      
      const Dem_DTCOriginType DTCOrigin = event->aaEventDestination;
      Dem_EventIdType EvMemEntEventId = DEM_NO_EVENT;
      Dem_UdsStatusByteType EvMemEventStatusByteOld = 0;
      Dem_EventMemoryEntryPtrType memEntry = NULL_PTR;
      Dem_UdsStatusByteType EvMemEventStatusByteNew = 0;

      if (memLocOld < Dem_SizeOfEventMemory[DTCOrigin])
      { 
        memEntry = Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, memLocOld);
        if(memEntry != NULL_PTR)
        {
          EvMemEntEventId =  memEntry->EventIdRef;
          EvMemEventStatusByteOld = Dem_AllEventStatusByte[EvMemEntEventId];          
        }
      }     
    
      /*********************************************************************
       *                     TestFailed bit = 1,                           *
       *                     TestFailedThisOpCycle = 1,                    *
       *                     (TestFailedSinceLastClear = 1)*               *
       *                     TestNotCompleteThisOpCycle = 0;               *
       *                     TestNotCompleteSinceLastClear = 0             *
       *********************************************************************/
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      DEM_SET_UDSSTATUSBYTE(EventId,
          (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF |    /* Bit 0 TestFailed                   */
          (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFTOC | /* Bit 1 TestFailedThisOperationCycle */             
          (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFSLC); /* Bit 5 TestFailedSinceLastClear     */


      DEM_CLR_UDSSTATUSBYTE(EventId, 
        (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC | /* Bit 4 TestNotCompletedSinceLastClear     */         
        (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCTOC); /* Bit 6 TestNotCompletedThisOperationCycle */
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();   
      
      /* @RfC 60025 : no memory entry for events without having a DTC */         
      if ((DEM_NO_DTC_ORIGIN != DTCOrigin) && (NULL_PTR != cbDTC))
      {  
        boolean eventDirty = DEM_FALSE; 
        /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
        /* polyspace-begin DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because EvMemTriggerFlag can be configured by user , 
           this condition maybe always evaluate to true" */
        uint8 triggerNvStorage = 
          (DEM_EVMEM_STATUS_DIRTY_NVM == cbDTC->EvMemTriggerFlag) ?
          Dem_EvMem_EventIsImmediateStorage(DTCOrigin, EventId) : DEM_EVMEM_STATUS_DIRTY;
        /* polyspace-end DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because EvMemTriggerFlag can be configured by user , 
           this condition maybe always evaluate to false" */

        #if ((DEM_SIZE_OF_EVENT_DATA > 0U) || (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)) 
        Dem_DTCType DTC = Dem_GetDtcByCombineDTC(cbDTC); 
        #endif

        #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
        /* @IF_REQ : disabled condition returns E_OK or E_NOT_OK? */    
        if (E_OK == Dem_GetEventStorageConditionState(event)) 
        #endif
        {
          Std_ReturnType result = Dem_EvMem_ProcessEventRetention(
            EventId, 
            DTCOrigin,
            EventStatusByteOld, 
            #if(DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_TYPE1)  
            DTCStatusByteOld,
            #endif
            #if ((DEM_SIZE_OF_EVENT_DATA > 0U) || (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)) 
            DTC,
            #endif 
            memEntry,
            &eventDirty, 
            &statusDirty);

            #if((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && (DEM_OBD_SUPPORT == STD_ON))
            Dem_ProcessIumpr( event, Dem_AllEventStatusByte[EventId]);
            #endif
          
          if (DEM_PROCESSEVENTRETENTION_OK == result)              
          {
            if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_PDTC))
            {
              SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
              DEM_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_PDTC);
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            }   
            #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
	    	/* polyspace +1  MISRA-C3:10.1 [Justified:Low] "Not a defect" */
            statusDirty |= Dem_EvMem_SetFirstLastFailedDtc(DTCOrigin, DTC);
            #endif          
            /* retVal = E_OK; */  
          }
          else if (DEM_PROCESSEVENTRETENTION_FULL == result)   
          {
            /* [Dem397] The Dem module shall indicate for each event memory if the event memory is full 
             * and there was an attempt to store an additional event in this event  memory.*/
            if ((boolean)DEM_TRUE == Dem_EvMem_SetEvMemOverflowFlag(DTCOrigin, DEM_TRUE))
            {
              /* @IF_REQ : Need it? */
              Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM); 
              Dem_EvMem_TriggerWriteAllBlocks(); 
            }
            /* @IF_REQ: Returns E_OK as per AUTOSAR Specification,but E_NOT_OK is used as return value by user requirement */
            retVal = E_NOT_OK;
          }
          else /* (DEM_PROCESSEVENTRETENTION_FAILED == result) */
          {
           /* Never be reached */
            retVal = E_NOT_OK; 
          }
        }/* else { retVal = E_OK } */
        
        if (DEM_EVMEM_STATUS_DIRTY_NVM == Dem_EvMem_TriggerNvDataStorage( 
          EventId, DTCOrigin, EventStatusByteOld, 
          triggerNvStorage, eventDirty, statusDirty))
        {
          Dem_EvMem_TriggerWriteAllBlocks();                                    
        }

        /*  Update Confirmed bit of Combined DTC */
        EvMemEventStatusByteNew = Dem_AllEventStatusByte[EvMemEntEventId];
        if(EvMemEventStatusByteOld != EvMemEventStatusByteNew)
        {
          if (DEM_EVMEM_STATUS_DIRTY_NVM == Dem_EvMem_TriggerNvDataStorage( 
          EvMemEntEventId, DTCOrigin, EvMemEventStatusByteOld, 
          triggerNvStorage, eventDirty, statusDirty))
          {
            Dem_EvMem_TriggerWriteAllBlocks();                                    
          }
        }
      
        /* Need to save if Operation Cycle was not Stored due to optimization */
        if((boolean)DEM_TRUE == Dem_EvMem_NonVolatieDataStatusFilter(DEM_NVDATA_GENERIC_NVRAM_DATA_ID, DEM_EVMEM_STATUS_TRIGGER_WAIT_NVM))
        {
          Dem_EvMem_ClearNonVolatieDataStatus(DEM_NVDATA_GENERIC_NVRAM_DATA_ID, DEM_EVMEM_STATUS_TRIGGER_WAIT_NVM);

          Dem_EvMem_SetNonVolatieDataStatus(
          DEM_NVDATA_GENERIC_NVRAM_DATA_ID,
          (DEM_EVMEM_STATUS_DIRTY | DEM_EVMEM_STATUS_TRIGGER_NVM));

          Dem_EvMem_TriggerWriteAllBlocks();
        }

      }
      /* Trigger callback EventStatusChanged, UdsStatusChanged */
      if (EventStatusByteOld != Dem_AllEventStatusByte[EventId])
      {
        Dem_TriggerCallbackOnUdsStatus(EventId, EventStatusByteOld, DTCStatusByteOld);      
      }
    }    
    else
    {
      /* Do nothing */
    }
    Dem_FreeLockByEventId(EventId);
  }
  
 
  return retVal;
}
      
      
/******************************************************************************
 * Function Name        : Dem_GetEventDTC > 2
 *
 * Service ID           : None
 *
 * Description          : Gets the DTC value of an event
 *
 * Sync/Async           : Synchronous/Asynchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DTC
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *                        None
 ******************************************************************************/
FUNC(Dem_EventIdType, DEM_CODE) Dem_GetEventIdByDTC(
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  uint8 ApiId,
  #endif
  const Dem_DTCType DTC)
{
  uint16 dtcId;
  Dem_EventIdType eventId = DEM_NO_EVENT;    

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  if ( 
    (DEM_MAX_DTC_VALUE < DTC ) ||
    (DEM_DTC_GROUP_EMISSION_REL_DTCS == DTC) || /* == DEM_NO_DTC */
    (DEM_DTC_GROUP_ALL_DTCS == DTC) || 
    (DEM_DTC_GROUP_CHASSIS_DTCS == DTC) ||
    (DEM_DTC_GROUP_BODY_DTCS == DTC) || 
    (DEM_DTC_GROUP_POWERTRAIN_DTCS == DTC) || 
    (DEM_DTC_GROUP_NETWORK_COM_DTCS == DTC) )
  {    
    DEM_REPORT_ERROR(ApiId, DEM_E_PARAM_DATA);
  }
  else
  #endif
  {
    for (dtcId = 0U; dtcId < Dem_Max_Number_Of_DTC; dtcId++)
    {
      Dem_DTCType dtcValue;    
      #if(DEM_OBD_SUPPORT == STD_ON)
      if (DEM_DTC_FORMAT_UDS != Dem_GaaCombinedDtc[dtcId].ddDtcFormat)
      {
        dtcValue = Dem_GaaCombinedDtc[dtcId].usObdDtc; /* @IF_REQ: Dem_GaaCombinedDtc[i].usObdDtc << 8 */
      }
      else
      #endif
      {
	    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
        dtcValue = Dem_GaaCombinedDtc[dtcId].ulUdsDtc;
      }    
      if (dtcValue == DTC)
      {
        eventId = Dem_GetFirstEventOfDTC(&Dem_GaaCombinedDtc[dtcId]);        
        break;
      }
    }
  }
  
  return eventId;                                  
}

      
/******************************************************************************
 * Function Name        : Dem_GetEventDTC > 2
 *
 * Service ID           : None
 *
 * Description          : Gets the DTC value of an event
 *
 * Sync/Async           : Synchronous/Asynchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DTC
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *                        None
 ******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventDTC(
  Dem_EventParameterCPCType event,
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA) DTC, Dem_DTCFormatType DTCFormat)
{
  Std_ReturnType retVal = E_NOT_OK; 

  *DTC  = DEM_NO_DTC;  
  /* no need to check 'if (DEM_NO_DTC_IDX != event->e_PointToDTC)' */
  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
  if (event->e_PointToDTC < Dem_Max_Number_Of_DTC)
  {

    switch(DTCFormat)
    {

      case DEM_DTC_FORMAT_UDS:
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */	  
        *DTC = Dem_GaaCombinedDtc[event->e_PointToDTC].ulUdsDtc;
      break;
      
      #if (DEM_OBD_SUPPORT == STD_ON)
      case DEM_DTC_FORMAT_OBD:
        *DTC = Dem_GaaCombinedDtc[event->e_PointToDTC].usObdDtc << 8U;
      break;
      #endif
      #if (DEM_J1939_SUPPORT == STD_ON) 
      case DEM_DTC_FORMAT_J1939:
	/* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
        *DTC = Dem_GaaCombinedDtc[event->e_PointToDTC].J1939DTCValue << 8U;
      break;
      #endif
      default:
	/* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
        *DTC = Dem_GaaCombinedDtc[event->e_PointToDTC].ulUdsDtc;
      break;
      
    }
  }
  
  if (DEM_NO_DTC != *DTC)
  {
    retVal = E_OK;
  }
  
  return  retVal;                                     
}


/******************************************************************************
 * Function Name        : Dem_GetEventDTCOrigin > 2
 *
 * Service ID           : None
 *
 * Description          : This function is used to get the main origin
 *                        of an event.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DTCOrigin
 *
 * Return parameter     : StdReturnType
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *
 ******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventDTCOrigin(
    Dem_EventParameterCPCType event,
    P2VAR(Dem_DTCOriginType, AUTOMATIC, DEM_VAR) DTCOrigin)
{
  Std_ReturnType retVal = E_NOT_OK;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  if ( (NULL_PTR == DTCOrigin) || (NULL_PTR == event) )
  /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to false. Avoid to runtime error of the polyspace */
  {
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_POINTER);  
  }
  else
  #endif
  {
    if (
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      (event->aaEventDestination == DEM_DTC_ORIGIN_PRIMARY_MEMORY) ||
      (event->aaEventDestination == DEM_DTC_ORIGIN_SECONDARY_MEMORY)
    )
    {
      *DTCOrigin = event->aaEventDestination;
      retVal = E_OK;
    }
  }

  return retVal;
}



/******************************************************************************
 * Function Name        : Dem_GetEventStorageConditionState == *1
 *
 * Service ID           : None
 *
 * Description          : Checks whether storage condions are true or not
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        : 
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 ******************************************************************************/
#if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
static FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventStorageConditionState(
    Dem_EventParameterCPCType event)
{
  Std_ReturnType retVal = E_OK;
  uint16 i = 0U;
  const uint16 NumOfCond = event->PointToStorageConditionMap + event->ucNumOfStorageCondition;

  if (NumOfCond <= Dem_Max_ListOfStorageConditionId)
  {
    /* Check the status of all enable conditions configured for the event by SW-C*/
    for(i = event->PointToStorageConditionMap; i < NumOfCond ; i++)
    {
      /* enable storage == all condition is true */
      if((boolean)DEM_FALSE == Dem_GetStorageConditionStatus(i))
      {
        retVal = E_NOT_OK;
        break;
      }
    }
  }

  return retVal;
}
#endif


/******************************************************************************
 * Function Name        : Dem_GetOpCycleStateByEvent == 2
 *
 * Service ID           : None
 *
 * Description          : Checks whether the  operation of an event
 *                        is started or not
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Std_ReturnType
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *                        Dem_EvMem_GetOpCycleState()
 *****************************************************************************/


FUNC(Std_ReturnType, DEM_CODE) Dem_GetOpCycleStateByEvent(
  Dem_EventIdType EventId,
  P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_VAR) CycleState)
{
  Std_ReturnType retVal = E_NOT_OK;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to false. Avoid to runtime error of the polyspace */
  if ((EventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == EventId))
  {
    DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */
  }  
  else if (NULL_PTR == CycleState)
  /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to false. Avoid to runtime error of the polyspace */  
  {
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_POINTER);
  }
  else 
  #endif  
  {
    /* @IF_REQ : e_OperationCycleId == Dem_GaaOperationCycleIdsList[0].ucOperationCycleId */
    /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to true. Avoid to runtime error of the polyspace */
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
    if ( Dem_Event[EventId-1U].e_OperationCycleId < Dem_Num_Operation_Cycles )
    {
      *CycleState = (Dem_OperationCycleStateType)DEM_CYCLE_STATE_END;
      Dem_EvMem_GetOpCycleState(Dem_Event[EventId-1U].e_OperationCycleId, CycleState);
      retVal = E_OK;
    }
  }

  return retVal;
}



/*******************************************************************************
 * Function Name        : Dem_GetTestResultThisOperation
 *
 * Service ID           : None
 *
 * Description          : Get a test result after event is processed
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Dem_TestResultType
 *                        DEM_TEST_RESULT_PASSED_THIS_OPERATION
 *                        DEM_TEST_RESULT_FAILED_THIS_OPERATION
 *                        DEM_TEST_RESULT_PASSED_FIRST
 *                        DEM_TEST_RESULT_FAILED_FIRST
 *                        DEM_TEST_RESULT_NO_RESULT : Test not completed
 * Preconditions        : None
 *
 * Remarks              :
 ******************************************************************************/
FUNC(Dem_TestResultType, DEM_CODE) Dem_GetTestResultThisOperation( 
  Dem_UdsStatusByteType EventStatusByte, 
  boolean RequireTestedCycle)
{
  Dem_TestResultType testResult = DEM_TEST_RESULT_NO_RESULT;

  if ((boolean)DEM_TRUE == RequireTestedCycle)
  {
    /* [SWS_Dem_00826] 
     * If the configuration parameter DemAgingRequieresTestedCycle
     * (refer DemGeneral) set to True, the Dem module shall process (count further) the aging
     * cycle counter value, if the respective aging cycle ends/restarts and the UDS status bit
     * 6 (TestNotCompleteThisOperationCycle) is set to zero. */
    if ((EventStatusByte & DEM_UDS_STATUS_TNCTOC) == 0U)
    {      
      if ((EventStatusByte & DEM_UDS_STATUS_TFTOC) != 0U)
      {
        testResult = DEM_TEST_RESULT_FAILED_THIS_OPERATION;
      }      
      else
      {
        testResult = DEM_TEST_RESULT_PASSED_THIS_OPERATION;
      }
    }
    else
    {
      testResult = DEM_TEST_RESULT_NO_RESULT;
    }
  }
  else
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */  
  {    
    /* [testFailedThisOperationCycle==1 */  
    if ((EventStatusByte & DEM_UDS_STATUS_TFTOC) != 0U)
    {
      testResult = DEM_TEST_RESULT_FAILED_THIS_OPERATION;
    } 
    /* [SWS_Dem_00490] 
     * If the configuration parameter DemAgingRequieresTestedCycle
     * (refer to DemGeneral) set to False, the Dem module shall process (count further) the
     * aging counter value, if the respective aging cycle ends/restarts. c()
     * Note: The aging counter in [SWS_Dem_00490] is processed also if no new test
     * result is available in the respective aging cycle. */         
    else
    {
      testResult = DEM_TEST_RESULT_PASSED_THIS_OPERATION;
    }
  }

  return testResult;
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:17.8 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

