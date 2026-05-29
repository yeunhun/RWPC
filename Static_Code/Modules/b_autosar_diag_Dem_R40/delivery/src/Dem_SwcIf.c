/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_SwcIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of Software Components Interface Functionality      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date:DD-MM-YYYY By            Description                         **
********************************************************************************
** 3.3.4    31-12-2021    LanhLT         Changes made As per Redmine #33335   **
**                                                                            **
** 1.5.1    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.5.0    14-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.4.4    12-12-2018    YoungJin.Yun  Changes made As per Redmine #14900    **
**                                                                            **
** 1.4.3    09-11-2018    EunKyung.Kim  Changes made As per Redmine #14481    **
**                                                                            **
** 1.4.2    20-03-2018      EunKyung.Kim  Changes made As per Redmine #11177  **
**                                                                            **
** 1.4.1    20-07-2017      EunKyung.Kim  Changes made As per Redmine #9294   **
**                                                                            **
** 1.4.0    28-04-2017      EunKyung.Kim  Changes made As per Redmine #8166   **
**                                                                            **
** 1.3.0    16-11-2016      YoungJin.Yun  Changes made As per Redmine #6549   **
**                                        #6188                               **
**                                                                            **
** 1.2.0    16-05-2016      YoungJin.Yun  Changes made As per Redmine #1164   **
**                                                                            **
** 1.1.2    11-05-2016      YoungJin.Yun  Changes made As per Redmine #4833   **
**                                                                            **
** 1.1.1    03-03-2016      YoungJin.Yun  Changes made As per Redmine #4215   **
**                                                                            **
** 1.1.0    07-01-2016      YoungJin.Yunn Changes made As per Redmine #3353,  **
**                                        #698 , #3638, #2473, #3271, #2827,  **
**                                        #1151, #2589                        **
**                                                                            **
** 1.0.13   26-03-2015      YoungJin.Yun  Changes made As per Redmine #2592   **                      
**                                                                            **
** 1.0.7    11-01-2014      YoungJin.Yun  Changes made As per Redmine #366,   ** 
**                                        #368,#371,#372,#405,#366,#367,#368, **
**                                        #371,#372,#405,#369,#373,#374,#375, **
**                                        #376,#370,#377,#381,#382,#383,#384, **
**                                        #385,#386,#387,#388,#389,#390,#391, **
**                                        #397,#398,#399,#400,#378,#380,#401, **
**                                        #403,#404,#406,#409,#410,#411,#412  **
**                                        #367,                               **
**                                                                            **
** 1.0.0     01-01-2013     Autron        Initial Version                     **
*******************************************************************************/ 

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"
#include "Dem_Ram.h"
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "NvM.h"              /* NVRAM manager symbols Header File */
#if (DEM_TRIGGER_DLT_REPORTS == STD_ON)
#include "Dlt.h"
#endif
#include "SchM_Dem.h"
#include "Rte_Dem.h"

#include "Dem_NvData.h"
#include "Dem_Event.h"
#include "Dem_EventRelatedData.h"
#include "Dem_EventCallback.h"
#include "Dem_Indicator.h"
#include "Dem_EventDebounce.h"
#include "Dem_Dtc.h"
#include "Dem_EventAging.h"
#include "Dem_EventMemory.h"


/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace-begin MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dem_SetEventStatus                                  **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : Interface for Sw Components to report Errors        **
**                        during normal operation                             **
**                                                                            **
** Sync/Async           : Synchronous/Asynchronous                            **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId,                            **
**                        Dem_EventStatusType EventStatus                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                        Dem_GaaPreDebounceTimeBased                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dem_ProcessEventStatus()                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus
  (Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* Check module initialization */
  if (DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((EventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == EventId))
  {
    DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */
  }
  else if (DEM_FALSE == Dem_EventStatusIsValid(EventStatus))
  {
    DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
    /* retVal = E_NOT_OK; */
  }
  else if(DEM_EVENT_KIND_SWC != Dem_GetEventKind(EventId))
  {
    DEM_REPORT_ERROR(DEM_SETEVENTSTATUS_SID, DEM_E_PARAM_CONFIG);
  /* retVal = E_NOT_OK; */
  }
  #endif  
  else
  {
    Dem_OperationCycleStateType cycleState = (Dem_OperationCycleStateType)DEM_CYCLE_STATE_END;
    
    (void)Dem_GetOpCycleStateByEvent(EventId, &cycleState);    
    if (DEM_CYCLE_STATE_START == cycleState)
    {
      retVal = Dem_ProcessEventStatus(EventId, EventStatus);
    }
  }
  
  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_ResetEventStatus                                **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This service shall be used to reset the Event       **
**                        Status stored in the Event Memory in the DEM        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
** Global Variable(s)   :                                                     **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
**                        Dem_DtcStatusUpdate()                               **
**                        Dcm_DemTriggerOnDTCStatus()                         **
**                        Dlt_DemTriggerOnEventStatus()                       **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_ResetEventStatus(Dem_EventIdType EventId)
{
  Std_ReturnType retVal = E_NOT_OK;
 
  if(DEM_INIT != Dem_GucInit) 
  {
    DEM_REPORT_ERROR(DEM_RESETEVENTSTATUS_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */    
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  else if ((EventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == EventId))
  {
    DEM_REPORT_ERROR(DEM_RESETEVENTSTATUS_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */    
  }
  #endif     
  else if (DEM_FALSE == Dem_GetLocksByEventIdAndEvMem(EventId))
  { 
    /* retVal = E_NOT_OK; */
  }
  else  
  {  
    /** [SWS_Dem_00638] 
     * The function Dem_ResetEventStatus shall return E_NOT_OK,
     * if the event was already tested this operation cycle (UDS DTC status bit 6 - TestNot-
     * CompletedThisOperationCycle is set to 0).
     *
     * The operation cycle status has no impact on Dem_ResetEventDebounceStatus and Dem_ResetEventStatus. */
    if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TNCTOC))
    {
      Dem_EventParameterPCType event = &Dem_Event[EventId - 1U];

      /* @SWS_Dem_00525, If test failed bit is set then reset it */
      if (DEM_IS_BIT_SET_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF))
      {    
        const Dem_UdsStatusByteType DTCStatusOld = Dem_GetDTCStatus(EventId);
        const Dem_UdsStatusByteType EventStatusByteOld = Dem_AllEventStatusByte[EventId];
        /* Reset the Status */
        DEM_CLR_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TF);
	    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
        if (DEM_TRUE == DEM_GET_EVENTPARAM_STORAGE_TF(event->ParamFieldsA))
        {
          Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(EventId);
          if ((NULL_PTR != cbDTC) && (DEM_NO_DTC_ORIGIN != event->aaEventDestination))            
          {
            /* Ignore ImmediateStorageLimit */ 
            if (DEM_EVMEM_STATUS_DIRTY_NVM == Dem_EvMem_TriggerNvDataStorage(
              EventId, event->aaEventDestination, EventStatusByteOld, 
	          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */	    
              cbDTC->EvMemTriggerFlag, DEM_FALSE, DEM_FALSE))
            {
              Dem_EvMem_TriggerWriteAllBlocks();                                    
            }
          }
        }
        /*No need  if (EventStatusByteOld != Dem_AllEventStatusByte[EventId]) */
        Dem_TriggerCallbackOnUdsStatus(EventId, EventStatusByteOld, DTCStatusOld);
      }
      /* Reset the debounce counters */
      Dem_ResetFaultDectectionCounter(event);

      /* @[SWS_Dem_00626: Control DTC setting has no impact  Dem_ResetEventStatus */
      retVal = E_OK;
    }
    else
    {
      /* [SWS_Dem_00638] The function Dem_ResetEventStatus shall return E_NOT_OK,
       * if the event was already tested this operation cycle (UDS DTC status bit 6 - TestNot-
       * CompletedThisOperationCycle is set to 0).*/
      DEM_REPORT_ERROR(DEM_RESETEVENTSTATUS_SID, DEM_E_PARAM_DATA);
      retVal = E_NOT_OK;
    }
    Dem_FreeLockByEventId(EventId);    
  }
  
  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_PrestoreFreezeFrame                             **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This API call is used to capture the FreezeFrame    **
**                        data for a specific EventId before the Monitor      **
**                        Function reports the event status                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
**                        Dem_PrestorePid()                                   **
*******************************************************************************/
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U) 
FUNC(Std_ReturnType, DEM_CODE) Dem_PrestoreFreezeFrame(Dem_EventIdType EventId)
{
  Std_ReturnType retVal = E_NOT_OK;

  if( DEM_INIT != Dem_GucInit ) 
  { 
    DEM_REPORT_ERROR(DEM_PRESTOREFREEZEFRAME_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */    
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((EventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == EventId))
  { 
    DEM_REPORT_ERROR(DEM_PRESTOREFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */        
  }
  #endif      
  else if (DEM_FALSE == Dem_GetLockByEventId(EventId))
  { 
    /* retVal = E_NOT_OK; */
  }  
  else
  {
    P2VAR(uint8, AUTOMATIC, DEM_VAR) base = NULL_PTR;
    Dem_NumOfPrestoredFFType BufferIndex = 0U;
  
    Dem_EventParameterCPCType event = &Dem_Event[EventId - 1U];
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    if (event->e_PointToData < Dem_Num_Of_EventRelatedData) 
    {
      Dem_EventRelatedDataPCType EvData = &Dem_EventRelatedData[event->e_PointToData];  
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      if (DEM_TRUE == EvData->FFPreStorageSupported) 
      {
        /* @IF_REQ : 1. buffer need the lock. 2. need to optimize. */
        /* Search for empty entry in Prestored buffer */
        base = Dem_GetBufferOfPrestoredFF(EventId, &BufferIndex);
        if (NULL_PTR == base)
        {
          base = Dem_GetBufferOfPrestoredFF(DEM_NO_EVENT, &BufferIndex);
        }

        if (NULL_PTR != base)
        {
          /* @IF_REQ step 1: check FFClassPos, step 2 get buffer */
          #if (DEM_SIZE_OF_FREEZEFRAME > 0U)         
          if (EvData->FFClassPos < Dem_Num_Of_FreezeFrameClass)
          {
            (void)Dem_CaptureFFClass(&Dem_FreezeFrameClass[EvData->FFClassPos], base, Dem_Size_Of_Prestored_FF);
            Dem_SetEventIdOfPrestoredFF(BufferIndex,EventId);         
            retVal = E_OK;            
          }
          #endif    
          #if((DEM_OBD2_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_OF_PID_RECDS > 0U))
          if (EvData->OBDFFClassPos < Dem_Num_Of_OBDFreezeFrameClass)
          {
            if (EvData->FFClassPos < Dem_Num_Of_FreezeFrameClass)
            {
              base += Dem_FreezeFrameClass[EvData->FFClassPos].size;
            }
            Dem_CaptureOBDFFClass(EventId, EvData->OBDClass, base);           
            Dem_SetEventIdOfPrestoredFF(BufferIndex,EventId);         
            retVal = E_OK;            
          }
          #endif
        }
        else
        {
          DEM_REPORT_ERROR(DEM_PRESTOREFREEZEFRAME_SID, DEM_E_NODATAAVAILABLE);          
        }
      }
    }
    Dem_FreeLockByEventId(EventId);
  }
  
  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_ClearPrestoredFreezeFrame                       **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : The API shall be called to delete or release        **
**                        the prestored FreezeFrame for specific EventId      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
**                        Dem_ClearPrestorePid()                              **
*******************************************************************************/
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U )
FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearPrestoredFreezeFrame(Dem_EventIdType EventId)
{
  Std_ReturnType retVal = E_NOT_OK;
  
  /* check module initialization */
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_CLEARPRESTOREDFREEZEFRAME_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((EventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == EventId))
  {
    DEM_REPORT_ERROR(DEM_CLEARPRESTOREDFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */
  }
  else if (0u == Dem_Max_Number_Prestored_FF)
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */  
  {
    DEM_REPORT_ERROR(DEM_CLEARPRESTOREDFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */
  }
  #endif  
  else if (DEM_FALSE == Dem_GetLockByEventId(EventId))
  { 
    /* retVal = E_NOT_OK; */
  }  
  else
  {
    retVal = Dem_ClearSinglePrestoredFFbyEventId(EventId);
    Dem_FreeLockByEventId(EventId);
  }
  
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_SetOperationCyclestate                          **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : The API shall be called to report the status        **
**                        change of an operation cycle state                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_OperationCycleType OperationCycleId             **
**                        Dem_OperationCycleStateType CycleState              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetOperationCycleState(
  uint8  OperationCycleId,
  Dem_OperationCycleStateType CycleState
)
{
  Dem_OperationCycleStateType cycleStateOld = (Dem_OperationCycleStateType)DEM_CYCLE_STATE_END;
  /* Dem_OperationCycleStateType cycleStateNew;*/
  
  Std_ReturnType retVal = E_NOT_OK;
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_SETOPERATIONCYCLESTATE_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (OperationCycleId >= Dem_Num_Operation_Cycles)
  {
    DEM_REPORT_ERROR(DEM_SETOPERATIONCYCLESTATE_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */
  }
  /* Unreachable code 
  else if (0xFFU == OperationCycleId)  
    DEM_REPORT_ERROR(DEM_SETOPERATIONCYCLESTATE_SID, DEM_E_PARAM_CONFIG);
    retVal = E_NOT_OK; 
  */  
  else if ((CycleState != DEM_CYCLE_STATE_START) &&
           (CycleState != DEM_CYCLE_STATE_END))
  {
    DEM_REPORT_ERROR(DEM_SETOPERATIONCYCLESTATE_SID, DEM_E_PARAM_DATA);
    /* retVal = E_NOT_OK; */
  }
  #endif 
  else 
  {
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();          
    if (DEM_FALSE == Dem_EvMem_Lock())
    {
      boolean dirty = DEM_FALSE;          
      Dem_EventIdType eventId; 

      Dem_OperationCycleTrigger = DEM_TRUE;
      
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      
      Dem_EvMem_GetOpCycleState(OperationCycleId, &cycleStateOld);
      /* Store cycle state */   
      if (DEM_TRUE == Dem_EvMem_SetOpCycleState(OperationCycleId, CycleState))
      {
        /* if there is no DTC, operation cycle state should not be stored (optimization) */
        if((Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PRIMARY_MEMORY] > 0U)
            #if(DEM_MAX_NUMBER_EVENT_ENTRY_SEC > 0u)
            || (Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_SECONDARY_MEMORY] > 0U)
            #endif
            )
        {
          /* If ECU doesn't have a power latch functionality, DemOperationCycleStatusStorage should be configured as TRUE */
          Dem_EvMem_SetNonVolatieDataStatus(
            DEM_NVDATA_GENERIC_NVRAM_DATA_ID,
            (DEM_EVMEM_STATUS_DIRTY | DEM_EVMEM_STATUS_TRIGGER_NVM));
        }
        else
        {
          /* operation cycle state would be stored later */
          Dem_EvMem_SetNonVolatieDataStatus(
                      DEM_NVDATA_GENERIC_NVRAM_DATA_ID,
                      DEM_EVMEM_STATUS_TRIGGER_WAIT_NVM);
        }
      }

      /* Aging, healing shall be processed 
       * [1] if operation state transmits from START to END ( for specific aging cycle such as warm cycle)
       * [2] if operation state transmits from START to START( no power latch, DemOperationCycleStatusStorage == true)  
       *
       * If ECU doesn't have a power latch functionality, DemOperationCycleStatusStorage should be configured 
       * as TRUE */
      if (DEM_CYCLE_STATE_START == cycleStateOld)
      {
        /*
         * Aging - 1
         */
        #if (DEM_AGING_CYCLE_COUNTER_PROCESS == DEM_PROCESS_AGINGCTR_INTERN)
        if (Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PRIMARY_MEMORY] > 0U)
        {
          Dem_EventAgingOnOperationCycleChanged(DEM_DTC_ORIGIN_PRIMARY_MEMORY, OperationCycleId);
        }
        #if(DEM_MAX_NUMBER_EVENT_ENTRY_SEC > 0u)  
        if (Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_SECONDARY_MEMORY] > 0U)
        {
          Dem_EventAgingOnOperationCycleChanged(DEM_DTC_ORIGIN_SECONDARY_MEMORY, OperationCycleId);
        }
        #endif      
        #endif

      }

      if (DEM_CYCLE_STATE_START == CycleState)
      {
        #if(DEM_OBD_SUPPORT == STD_ON)
        #if(DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO )
        Dem_OCStartInit();
        #endif
        
        Dem_SetObdCycle(OperationCycleId);
        #endif
      }
     

      /* Initialize Event Status
       * 
       * 1. Healing, PDTC
       * 2. EventStatus initialization on OperationCycle is started
       */      
      for (eventId = 1U; eventId <= Dem_Number_Of_Events; eventId++)
      {  
        Dem_EventParameterPCType event = &Dem_Event[eventId-1U];
        Dem_EventParameterCallbackPtrType eventCbk;
        #if (DEM_NUMBER_OF_EVENT_CALLBACK > 0)
        if (event->e_PointToEventCallbackData < (Dem_EventIdType)DEM_NUMBER_OF_EVENT_CALLBACK)
        {
          eventCbk = &Dem_EventCallback[event->e_PointToEventCallbackData];
        }
        else
        #endif
        {
          eventCbk = NULL_PTR;
        }

        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition can evaluate to true/false according to configuration */
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
	    if (OperationCycleId == event->e_OperationCycleId)
        {
          const Dem_UdsStatusByteType EventStatusByteOld = Dem_AllEventStatusByte[eventId];
          
          /* [1] if operation state transmits from START to END ( for specific aging cycle such as warm cycle)
           * [2] if operation state transmits from START to START( no power latch, DemOperationCycleStatusStorage == true) */        
          if (DEM_CYCLE_STATE_START == cycleStateOld)
          {
            if ( event->ucNumberofIndicator > 0U)
            {
              if (DEM_WIR_RESET_ON_OPERATIONCYCLE_END == DEM_GET_EVENTPARAM_RESET_WIR(event->ParamFieldsA))
              {
                 if (DEM_IS_BIT_SET_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_WIR))
                 {
                   SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
                   DEM_CLR_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_WIR);
                   SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
                   /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */
		           dirty |= Dem_InitIndicator(eventId);
                 }
              }
              else
              {
                Dem_TestResultType testResult;
                /* Event qualified as passed and tested completed this operation cycle to avoid unnecessary loop */
                testResult = Dem_GetTestResultThisOperation(EventStatusByteOld, Dem_Healing_Requieres_Tested_Cycle);
                if (DEM_TEST_RESULT_PASSED_THIS_OPERATION == testResult)
                {
                  /* Healing : WarningIndicatorRequestOffCondition
                   * [1] Indicator Failure/Healing Operation Cycle is a OperationCycle for  a event
                   * [2] Indicator is supported */
		          /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */
                  dirty |= Dem_DeActivateIndicatorOnOperationChange(eventId);
                }
              }
            }


            /* [SWS_Dem_00390] : PedingDTC = 0 
             * [1] NOT TestFailedThisOperationCycle AND
             * [2] NOT TestNotCompletedThisOperationCycle AND
             * [3] CycleState = DEM_CYCLE_STATE_END|RESTART) */            
            if ((EventStatusByteOld & DEM_BITMASK_RESET_PDTC) == DEM_UDS_STATUS_PDTC)
            {                        
              SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
              DEM_CLR_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_PDTC);
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
              /* dirty = DEM_TRUE; */
            }
          }

          if (DEM_CYCLE_STATE_START == CycleState)
          {
             const Dem_UdsStatusByteType DTCStatusOld = Dem_GetDTCStatus(eventId);
                  
            /* [SWS_Dem_00439] 
             * Note: For resetting the fault detection counter implemented in a monitor, the Dem
             * module uses the callback-function InitMonitorForEvent (refer to section 7.2 and Init-
             * MonitorForEvent). */
            if (DEM_DEBOUNCE_NO_DEBOUNCE_BASED != DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(event->ParamFieldsA))
            {
              Dem_ResetFaultDectectionCounter(event);
            }

            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();        
            /* TestFailedThisOperationCycle bit1 = 0 */
            DEM_CLR_UDSSTATUSBYTE(eventId ,DEM_UDS_STATUS_TFTOC);        
            /* TestNotCompletedThisOperationCycle bit6 = 1 */
            DEM_SET_UDSSTATUSBYTE(eventId,DEM_UDS_STATUS_TNCTOC); 

            if (DEM_IS_BIT_SET_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_TF))       
            {
              if (DEM_FALSE == DEM_GET_EVENTPARAM_STORAGE_TF(event->ParamFieldsA))
              /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */                
              {
                DEM_CLR_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_TF);
              }
            }

            if ( event->ucNumberofIndicator > 0U)
            {
              if (DEM_WIR_RESET_ON_OPERATIONCYCLE_START == DEM_GET_EVENTPARAM_RESET_WIR(event->ParamFieldsA))
              {
                if (DEM_IS_BIT_SET_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_WIR))
                {
                  DEM_CLR_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_WIR);
                  /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */
		          dirty |= Dem_InitIndicator(eventId);
                }
              }          
            }

            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();            
          
            /* [SWS_Dem_00016] 
             * The Dem module shall trigger the event-speci?c callback-function EventStatusChanged
             * on each event status change. */
            if (EventStatusByteOld != Dem_AllEventStatusByte[eventId])
            {
              Dem_TriggerCallbackOnUdsStatus(eventId, EventStatusByteOld, DTCStatusOld);      
            }
            
            /* Call Callback for initialization of monitor for a event */
            if ((NULL_PTR !=eventCbk) && (NULL_PTR != eventCbk->pDemInitMonitorForEvent))
            {
              /*Return value unused - only for compatibility with according RTE operation.*/
              /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */              
              (void)eventCbk->pDemInitMonitorForEvent((Dem_InitMonitorReasonType)DEM_INIT_MONITOR_RESTART);
            }

            #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))
              Dem_ProcessDen(OperationCycleId, eventId);
            #endif


          }


          if (EventStatusByteOld != Dem_AllEventStatusByte[eventId])
          {
            Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(eventId);
            if ((NULL_PTR != cbDTC) && (DEM_NO_DTC_ORIGIN != event->aaEventDestination))
            {
	          /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  	
              (void)Dem_EvMem_TriggerNvDataStorage(
                eventId, event->aaEventDestination, EventStatusByteOld, 
                cbDTC->EvMemTriggerFlag, DEM_FALSE, dirty);
            }
          }
        }
      }
      
      Dem_EvMem_TriggerWriteAllBlocks();  
      Dem_OperationCycleTrigger = DEM_FALSE;
      retVal = E_OK;    
    }
    else
    {
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
  }
  /* Return appropriate value */
  return retVal;
}

/*******************************************************************************
** Function Name        : Dem_GetEventStatus                                  **
**                                                                            **
** Service ID           : 0x0A                                                **
**                                                                            **
** Description          : This API shall be used to read the event status     **
**                        from the DEM                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_UdsStatusByteType  *EventStatusExtended         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
**                        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION()           **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventStatus(
    Dem_EventIdType EventId,
    P2VAR (Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA) EventStatusExtended
)
{
  Std_ReturnType retVal = E_NOT_OK;
  
  if(Dem_GucInit != DEM_INIT) 
  {
    DEM_REPORT_ERROR(DEM_GETEVENTSTATUS_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if((DEM_NO_EVENT == EventId) || (EventId > Dem_Number_Of_Events)) 
  {
    DEM_REPORT_ERROR(DEM_GETEVENTSTATUS_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */    
  }
  else if(NULL_PTR == EventStatusExtended) 
  {
    DEM_REPORT_ERROR(DEM_GETEVENTSTATUS_SID, DEM_E_PARAM_POINTER);
    /* retVal = E_NOT_OK; */    
  }
  
  #endif  
  else
  {
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    *EventStatusExtended = Dem_AllEventStatusByte[EventId];
    /*EventStatusExtended = *EventStatusExtended & Dem_Status_Availability_Mask; */
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

    retVal = E_OK;
  }

  return retVal;
}


/*******************************************************************************
** Function Name        : Dem_GetEventFailed                                  **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : This API shall be used to read the event failed     **
**                        status of an event                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : boolean *EventFailed                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
**                        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION()           **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventFailed(
  Dem_EventIdType EventId, 
  P2VAR (boolean, AUTOMATIC, DEM_APPL_DATA) EventFailed)
{
  Std_ReturnType retVal = E_NOT_OK;

  if (DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETEVENTFAILED_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */ 
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if((DEM_NO_EVENT == EventId) || (EventId > Dem_Number_Of_Events))
  {
    DEM_REPORT_ERROR(DEM_GETEVENTFAILED_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */ 
  }
  else if(NULL_PTR == EventFailed)
  {
    DEM_REPORT_ERROR(DEM_GETEVENTFAILED_SID, DEM_E_PARAM_POINTER);
    /* retVal = E_NOT_OK; */ 
  }
  #endif
  else
  {
    /* Check for event is failed */
    if(0U != (Dem_AllEventStatusByte[EventId] & (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF))
    {
      /* Test failed bit is set */
      *EventFailed = DEM_TRUE;
    }
    else
    {
      /* Test failed bit is not set */
      *EventFailed = DEM_FALSE;
    }
    
    retVal = E_OK;
  }
  
  return retVal;
}

/*******************************************************************************
** Function Name        : Dem_GetEventTested                                  **
**                                                                            **
** Service ID           : 0x0C                                                **
**                                                                            **
** Description          : This API shall be used to read Bit 6 of             **
**                        Dem_UdsStatusByteType  from the DEM                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : boolean *EventTested                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
**                        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION             **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventTested(
  Dem_EventIdType EventId,
  P2VAR (boolean, AUTOMATIC, DEM_APPL_DATA) EventTested)
{
  Std_ReturnType retVal = E_NOT_OK;

  if (DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETEVENTTESTED_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */ 
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if((DEM_NO_EVENT == EventId) || (EventId > Dem_Number_Of_Events))
  {
    DEM_REPORT_ERROR(DEM_GETEVENTTESTED_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */ 
  }
  else if(NULL_PTR == EventTested)
  {
    DEM_REPORT_ERROR(DEM_GETEVENTTESTED_SID, DEM_E_PARAM_POINTER);
    /* retVal = E_NOT_OK; */ 
  }
  #endif
  else
  {
    if(0u != (Dem_AllEventStatusByte[EventId] & (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCTOC))
    {
      /* Event is not tested */
      *EventTested = DEM_FALSE;
    }
    else
    {
      /* Event is tested */
      *EventTested = DEM_TRUE;
    }
    retVal = E_OK;
  }
  
  return retVal;
}

/*******************************************************************************
** Function Name        : Dem_GetDTCOfEvent                                   **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : Gets the DTC which is mapped to EventId by          **
**                        DEM Configuration                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId,                            **
**                        Dem_DTCFormatType DTCFormat                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint32 *DTCOfEvent,                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCOfEvent(
  Dem_EventIdType EventId, 
  Dem_DTCFormatType DTCFormat,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTCOfEvent)
{
  Std_ReturnType retVal = DEM_E_NO_DTC_AVAILABLE;

  /* Module initialization check */
  if(Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_GETDTCOFEVENT_SID, DEM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  else if(DTCOfEvent == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_GETDTCOFEVENT_SID, DEM_E_PARAM_POINTER);
    retVal = E_NOT_OK;
  }
  else if((EventId == DEM_NO_EVENT) || (EventId > Dem_Number_Of_Events))
  {
    DEM_REPORT_ERROR(DEM_GETDTCOFEVENT_SID, DEM_E_PARAM_CONFIG);
    retVal = E_NOT_OK;
  }
  else if((DTCFormat != DEM_DTC_FORMAT_OBD) &&
    (DTCFormat != DEM_DTC_FORMAT_UDS))
  {
    DEM_REPORT_ERROR(DEM_GETDTCOFEVENT_SID, DEM_E_PARAM_CONFIG);
    retVal = E_NOT_OK;
  }
  #endif  
  else
  {  
    if (DEM_FALSE == Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_DTC_SUPP))
    {
      if (DEM_TRUE == Dem_DTCFormatIsValid(EventId, DTCFormat))
      {
        retVal = Dem_GetEventDTC(&Dem_Event[EventId-1U], DTCOfEvent, DTCFormat);
      }
    }
  }
  
  return retVal;
}

/*******************************************************************************
** Function Name        : Dem_GetIndicatorStatus                              **
**                                                                            **
** Service ID           : 0x29                                                **
**                                                                            **
** Description          : This function shall be used to read the             **
**                        indicator-Status derived from the event status      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 IndicatorId                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_IndicatorStatusType* IndicatorStatus            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace:begin<MISRA-C:5.6:Not a defect:Justify with annotations> Depends on Dem specfication */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetIndicatorStatus(uint8 IndicatorId,
  P2VAR (Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA) IndicatorStatus)
{
  Std_ReturnType retVal = E_NOT_OK;
  
  if(Dem_GucInit != DEM_INIT) 
  {
    DEM_REPORT_ERROR(DEM_GETINDICATORSTATUS_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK;*/
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if( IndicatorStatus == NULL_PTR ) 
  {
    DEM_REPORT_ERROR(DEM_GETINDICATORSTATUS_SID, DEM_E_PARAM_POINTER);
    /* retVal = E_NOT_OK;*/    
  }
  else if( IndicatorId >= Dem_Num_Of_IndicatorId ) 
  {
    DEM_REPORT_ERROR(DEM_GETINDICATORSTATUS_SID, DEM_E_PARAM_DATA);
    /* retVal = E_NOT_OK;*/    
  }
  #endif
  else
  {
    *IndicatorStatus = DEM_INDICATOR_OFF;  
    
    #if(DEM_NUMBER_OF_INDICATORS > 0U)      
    {
      Dem_NumOfIndicatorAttributeType *behavior = Dem_IndicatorBehaviorAccumulator[IndicatorId];

      if (0U != behavior[DEM_INDICATOR_CONTINUOUS])
      {
        *IndicatorStatus |= DEM_INDICATOR_CONTINUOUS;
      }
      if (0U !=behavior[DEM_INDICATOR_BLINKING])
      {
        *IndicatorStatus |= DEM_INDICATOR_BLINKING;
      }
      if (0U != behavior[DEM_INDICATOR_BLINK_CONT])
      {
        *IndicatorStatus |= DEM_INDICATOR_BLINK_CONT;
      }    

      #if (DEM_J1939_SUPPORT == STD_ON)
      if (0U != behavior[DEM_INDICATOR_SLOW_FLASH])
      {
        *IndicatorStatus |= DEM_INDICATOR_SLOW_FLASH;
      }
      if (0U != behavior[DEM_INDICATOR_FAST_FLASH])
      {
        *IndicatorStatus |= DEM_INDICATOR_FAST_FLASH;
      }    
      #endif
      
      #if defined(DEM_INDICATOR_ON_DEMAND)
      if (0U != behavior[DEM_INDICATOR_ON_DEMAND])
      {
        *IndicatorStatus |= DEM_INDICATOR_ON_DEMAND;
      }
      if (0U != behavior[DEM_INDICATOR_SHORT])
      {
        *IndicatorStatus |= DEM_INDICATOR_SHORT;
      }    
      #endif    
    }
    #endif  
    
    retVal = E_OK;
  }
  
  return retVal;
}
/* polyspace:end<MISRA-C:5.6:Not a defect:Justify with annotations> Depends on Dem specfication */

/*******************************************************************************
** Function Name        : Dem_SetEnableCondition                              **
**                                                                            **
** Service ID           : 0x39                                                **
**                                                                            **
** Description          : This function shall set the EnableCondition         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EnableConditionID, ConditionFulfilled               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
**                        SchM_Exit_Dem_REQUEST_DATA_PROTECTION()             **
*******************************************************************************/
#if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEnableCondition
  (uint8 EnableConditionID, boolean ConditionFulfilled)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* Check if the Dem module is not initialized */
  if(Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_SETENABLECONDITION_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK;*/
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if((ConditionFulfilled != DEM_TRUE) &&
    (ConditionFulfilled != DEM_FALSE))
  {
    DEM_REPORT_ERROR(DEM_SETENABLECONDITION_SID, DEM_E_PARAM_DATA);
    /* retVal = E_NOT_OK;*/
  }
  #endif  
  else
  {   
    if(EnableConditionID < Dem_Num_Enable_Condition)
    {
      SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
      Dem_SetEnableConditionStatus(EnableConditionID, ConditionFulfilled);
      SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
      retVal = E_OK;
    }
    else
    {
      DEM_REPORT_ERROR(DEM_SETENABLECONDITION_SID, DEM_E_PARAM_CONFIG);
      /* retVal = E_NOT_OK; */
    }
  }
  
  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_SetStorageCondition                             **
**                                                                            **
** Service ID           : 0x38                                                **
**                                                                            **
** Description          : This function shall set the StorageCondition        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : StorageConditionID, ConditionFulfilled              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
#if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetStorageCondition
  (uint8 StorageConditionID, boolean ConditionFulfilled)
{
  Std_ReturnType retVal = E_NOT_OK;

  if(Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_SETSTORAGECONDITION_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if((ConditionFulfilled != DEM_TRUE) && (ConditionFulfilled != DEM_FALSE))
  {
    DEM_REPORT_ERROR(DEM_SETSTORAGECONDITION_SID, DEM_E_PARAM_DATA);
    /* retVal = E_NOT_OK; */
  }
  #endif  
  else
  {
    if(StorageConditionID < Dem_Number_Storage_Condition)
    {
      /* Set the condition for StorageConditionID */
      SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
      /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "Not a defect" */
      Dem_SetStorageConditionStatus(StorageConditionID, ConditionFulfilled);
      SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
      retVal = E_OK;
    }
    else
    {
      DEM_REPORT_ERROR(DEM_SETSTORAGECONDITION_SID, DEM_E_PARAM_CONFIG);
      /* retVal = E_NOT_OK; */
    }
  }
  
  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_GetFaultDetectionCounter                        **
**                                                                            **
** Service ID           : 0x3E                                                **
**                                                                            **
** Description          : Gets the FaultDetectionCounter value of an event    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : sint8* FaultDetectionCounter                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_GetFaultDetectionCounter
  (Dem_EventIdType EventId,
  P2VAR (sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter)
{
  Std_ReturnType retVal = E_NOT_OK;
  
  /* Check if the Dem module is not initialized */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETFAULTDETECTIONCOUNTER_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if((DEM_NO_EVENT == EventId) || (EventId > Dem_Number_Of_Events))
  {
    DEM_REPORT_ERROR(DEM_GETFAULTDETECTIONCOUNTER_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */
  }
  else if (NULL_PTR == FaultDetectionCounter)
  /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to true . configuration error  */
  {
    DEM_REPORT_ERROR(DEM_GETFAULTDETECTIONCOUNTER_SID, DEM_E_PARAM_POINTER);
    /* retVal = E_NOT_OK; */
  }
  #endif  
  else
  {
    /* [SWS_Dem_00415] The Dem module shall calculate the fault detection counter
     * (-128 ... +127 according to UDS) based on the value and range of the internal de-
     * bounce counter to map the internal counter values linearly to the external values*/  
    Dem_EventParameterPCType event = &Dem_Event[EventId-1U];
    #if ((DEM_DEBOUNCE_COUNTER_SUPPORT == STD_ON) || (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > 0u))    
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    Dem_NumOfDebounceType DebounceId = event->ucIndexOfDebounceAry;
    #endif
    
    switch(DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(event->ParamFieldsA))
    {
      /* Debounce Counter Based */
      #if (DEM_DEBOUNCE_COUNTER_SUPPORT == STD_ON)
      case DEM_DEBOUNCE_COUNTER_BASED:
        /* polyspace<RTE:UNR:Not a defect:No action planned>If-condition always evaluates to true  */
        if(DebounceId < Dem_Number_Of_Pre_Debounce_Counter)
        { 
          P2CONST(Dem_PreDebounceCounterType, AUTOMATIC, DEM_CONST) 
          dcb = &Dem_GaaPreDebounceCounter[DebounceId];      
          if ( Dem_GssTempCounter[DebounceId] > 0)
          {
            #if (DEM_DEV_ERROR_DETECT == STD_ON)
            /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
	        if (Dem_GssTempCounter[DebounceId] > dcb->ssDemCounterFailedThreshold)
            {
              DEM_REPORT_ERROR(DEM_GETFAULTDETECTIONCOUNTER_SID, DEM_E_OUT_OF_BOUNDS);
            }
            else
            #endif
            {
              /* polyspace +9 MISRA-C3:2.1 [Justified:Low] "Not a defect" */	
              /* polyspace +8 MISRA-C3:14.3 [Justified:Low] "Not a defect" */
              if (0 != dcb->ssDemCounterFailedThreshold)
              {
                 /* fomula : FDC = 127 * (counter value * FDC threshold) */ 
                 /* polyspace<RTE:OVFL:Not a defect:No action planned> to avoid floating point math */
                 *FaultDetectionCounter = (Dem_FaultDetectionCounterType)
                  (((sint32)Dem_GssTempCounter[DebounceId] * (sint32)DEM_COUNTER_MAX)/
                    dcb->ssDemCounterFailedThreshold); /* (+) value */              
              }
              /* polyspace +5 MISRA-C3:2.1 [Justified:Low] "Not a defect" */
              else
              /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to true  */                            
              {
                *FaultDetectionCounter = 0;
              }
            }
          }
          else
          {            
            #if (DEM_DEV_ERROR_DETECT == STD_ON)
            /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
            if (Dem_GssTempCounter[DebounceId] < dcb->ssDemCounterPassedThreshold)
            /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to false  */
            {
              DEM_REPORT_ERROR(DEM_GETFAULTDETECTIONCOUNTER_SID, DEM_E_OUT_OF_BOUNDS);
            }
            else
            #endif
            {
              if (0 != dcb->ssDemCounterPassedThreshold)
              {
                /* fomula : FDC = -128 * (counter value / FDC threshold) */ 
                /* polyspace<RTE:OVFL:Not a defect:No action planned> to avoid floating point math */
                *FaultDetectionCounter = (Dem_FaultDetectionCounterType)
                  (((sint32)Dem_GssTempCounter[DebounceId] * DEM_COUNTER_MIN)/
                  dcb->ssDemCounterPassedThreshold); /* (-) value */                               
              }
              else
              {
                *FaultDetectionCounter = 0;
              }
            }
          }
          retVal = E_OK;          
        }
      break;
      #endif
    
      /* Debounce Time Based */
      #if (DEM_DEBOUNCE_TIME_SUPPORT == STD_ON) 
      case DEM_DEBOUNCE_TIME_BASED:   
        (void)Dem_GetFDCDebounceTimeBased(event, FaultDetectionCounter);
        /*@IF_REQ ,, OK or NOK according to return value */
        retVal = E_OK;
      break;
      #endif
    
      #if (DEM_NUMBER_OF_PRE_DEBOUNCE_MONITOR_INTERNAL > 0u)
      case DEM_DEBOUNCE_MONITOR_BASED:
        if (DebounceId < Dem_Number_Of_Pre_Debounce_Monitor_Internal)
        {
	      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
          if (NULL_PTR != Dem_GaaPreDebounceMonitorInternal[DebounceId].pDemCallBackGetFDCnt)
          {
            /* [SWS_Dem_00439] If the callback-function GetFaultDetectionCounter returns
             * other than E_OK, this return value shall also be returned by the API
             * Dem_GetFaultDetectionCounter. c(SRS_Diag_04068, SRS_Diag_04010) */
            retVal = Dem_GaaPreDebounceMonitorInternal[DebounceId].pDemCallBackGetFDCnt(FaultDetectionCounter);
            if (E_OK != retVal)
            {
              *FaultDetectionCounter = 0;
            }
          }
          else
          /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to true . configuration error  */
          {
            /* [SWS_Dem_00671] 
             * If the callback-function GetFaultDetectionCounter is not configured 
             * (refer to configuration container DemCallbackGetFDC) for a given event,
             * the API Dem_GetFaultDetectionCounter shall return DEM_E_NO_FDC_AVAILABLE.(SRS_Diag_04010) */
             
             /* retVal = E_NOT_OK instead of DEM_E_NO_FDC_AVAILABLE; */
          }
        }
      break;
      #endif
    
      default:
        *FaultDetectionCounter = 0;
        /* retVal = E_NOT_OK;  DEM_E_NO_FDC_AVAILABLE; */
      break;
      
    }
  }

  /* Return the value */
  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_GetEventMemoryOverflow                          **
**                                                                            **
** Service ID           : 0x32                                                **
**                                                                            **
** Description          : Gets the event memory overflow indication status.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Dem_DTCOriginType DTCOrigin                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : boolean* OverflowIndication                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)Dem_GetEventMemoryOverflow
  (Dem_DTCOriginType DTCOrigin,
  P2VAR (boolean, AUTOMATIC, DEM_APPL_DATA) OverflowIndication)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* Check if the Dem module is not initialized */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETEVENTMEMORYOVERFLOW_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if(NULL_PTR == OverflowIndication)
  {
    DEM_REPORT_ERROR(DEM_GETEVENTMEMORYOVERFLOW_SID, DEM_E_PARAM_POINTER);
    /* retVal = E_NOT_OK; */
  }
  else if((DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
    (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) &&
    (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) &&
    (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY))
  {
    DEM_REPORT_ERROR(DEM_GETEVENTMEMORYOVERFLOW_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */
  }
  #endif  
  else
  {
    switch(DTCOrigin)
    {
    case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
    #if(DEM_MAX_NUMBER_EVENT_ENTRY_MIR > 0u)
    case DEM_DTC_ORIGIN_MIRROR_MEMORY:
    #endif
    #if(DEM_MAX_NUMBER_EVENT_ENTRY_SEC > 0u)
    case DEM_DTC_ORIGIN_SECONDARY_MEMORY:
    #endif
    #if(DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0u)
    case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
    #endif
  
      *OverflowIndication = Dem_EvMem_GetEvMemOverflowFlag(DTCOrigin);
      retVal = E_OK;
      break;
    default :
      /*  Do Nothing  */
      break;
    }
  }
  
  return retVal;
}

/* @IF_REQ*/
/*******************************************************************************
** Function Name        : Dem_SetAgingCycleCounterValue                       **
**                                                                            **
** Service ID           : 0x12                                                **
**                                                                            **
** Description          : Provides the value of the external aging            **
**                        cycle counter                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 CounterValue                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_Event                               **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
#if (DEM_AGING_CYCLE_COUNTER_PROCESS == DEM_PROCESS_AGINGCTR_EXTERN)

/* #error "DEM_PROCESS_AGINGCTR_EXTERN: Not supported" */
#if 1 /* Not supported */

FUNC(Std_ReturnType, DEM_CODE)Dem_SetAgingCycleCounterValue(uint8 CounterValue)
{
  Std_ReturnType LddReturnValue = E_OK;
  #if 0
  Std_ReturnType LddTempRetVal;

  P2VAR(Dem_EventMemoryEntryType, AUTOMATIC, DEM_APPL_DATA) LpEventMemory;
  uint16 LusCount;
  uint8 LucStatus;
  uint8 LucCount;
  uint8 LucMaxNumOfEventEntry;
  #if(DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)
  uint8 LucEventDestinationCnt;
  uint8 LucOrigin;
  #endif
  boolean LblAgingCounter;

  LddReturnValue = E_OK;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the Dem module is not initialized */
  if(Dem_GucInit != DEM_INIT)
  {
    /* Report to DET */
    (void)Det_ReportError(DEM_MODULE_ID, DEM_INSTANCE_ID,
      DEM_SETAGINGCYCLECOUNTERVALUE_SID, DEM_E_UNINIT);

    /* Set the return value */
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
  /* Loop for number of events */
    for(LusCount = DEM_ZERO; LusCount < Dem_Number_Of_Events; LusCount++)
    { 
      Dem_EventParameterCPCType event = &Dem_Event[LusCount];
      LucStatus = Dem_GetDTCStatus(LusCount);

      /* Check if aging is allowed and Test has Passed this operation cycle */
      if((Dem_Event[LusCount].blAgingAllowed == DEM_TRUE) &&
        ((LucStatus & DEM_BIT1_MASK1) == DEM_ZERO))
      {
        LddTempRetVal = E_NOT_OK;
        #if(DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)
        LucMaxNumOfEventEntry =  DEM_ZERO;
        LpEventMemory = &Dem_PrimaryEventMemory[DEM_ZERO];
        /* Loop for the number of the destination for a event */
        for(LucEventDestinationCnt = DEM_ZERO; ((LucEventDestinationCnt <
          Dem_Event[LusCount].ucNoOfDestinationSelected) &&
          (LddTempRetVal == E_NOT_OK)); LucEventDestinationCnt++)
        {
          /* Get the destination of event */
          Dem_EvMem_GetEventDTCOrigin(&Dem_Event[LusCount],
           LucEventDestinationCnt, &LucOrigin);
          
          if (DEM_TRUE == Dem_EvMem_DTCOriginIsValid(LucOrigin))
          {
            LpEventMemory = Dem_EventMemory[LucOrigin];
            LucMaxNumOfEventEntry = Dem_SizeOfEventMemory[LucOrigin];
            if ((NULL_PTR != LpEventMemory) && (0U != LucMaxNumOfEventEntry))
            {
              LddTempRetVal = E_OK;
            }
          }
        }
        #endif
        /* Check whether the event memory is found */
        if(LddTempRetVal == E_OK)
        {
          /* Initialise the counter to false as event not in memory */
          LblAgingCounter = DEM_FALSE;

          /* Search for event in memory */
          for(LucCount = DEM_ZERO;((LucCount < LucMaxNumOfEventEntry)
            && (LblAgingCounter == DEM_FALSE)); LucCount++)
          {
             /* Event ID is Matching */
             if((LusCount + DEM_ONE) == LpEventMemory[LucCount].EventIdRef)
             {
                /* Event is present in memory */
                LblAgingCounter = DEM_TRUE;
             }
          }
          /* Check event is present in memory then process aging counter */
          if (LblAgingCounter == DEM_TRUE)
          {
            uint8 AgingCycleCounter = 0u;
            
            (void)Dem_EvMem_SetAgingCounter(&LpEventMemory[LucCount - DEM_ONE],
              (uint8)((CounterValue + event->ucAgingCycleCounterThreshold)% DEM_EXTERN_COUNTER_MAX));

            AgingCycleCounter= Dem_EvMem_GetAgingCounter(&LpEventMemory[LucCount - DEM_ONE]);
            /* Check for the aging counter threshold */
            if(AgingCycleCounter >= event->ucAgingCycleCounterThreshold)
            {
              #if(DEM_STATUS_BIT_HANDLING_TFSLC == \
                DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
                /* Reset the TFSLC bit i.e. bit 5 */
                DEM_CLR_UDSSTATUSBYTE(event->e_EventId, DEM_UDS_STATUS_TFSLC);
              #endif
              
              DEM_CLR_UDSSTATUSBYTE(event->e_EventId, DEM_UDS_STATUS_CDTC);

              Dem_EvClearProcState(event->e_EventId, DEM_EVPROCSTATE_EVENT_STORED);
              
              /* Clear the event from memory */
              Dem_EvMem_ClearEventMemoryEntry(&LpEventMemory[LucCount - DEM_ONE]);
            }/* Check for the aging counter threshold */
          }/* Check event is present in memory then process aging counter */
        }/* Check whether the event memory is found */
      }/* Check if aging is allowed and Test has Passed this operation cycle */
      else
      {
        /* Need it? 
        SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
        Dem_EvMem_SetAgingCounter[LusCount] = CounterValue;
        SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
        */
      }/* Check if aging is allowed and Test has Passed this operation cycle */
    }/* Loop for number of events */
  }/* Det Check */
  #endif
  
  return(LddReturnValue);
}
#endif

#endif

/*******************************************************************************
** Function Name        : Dem_GetEventFreezeFrameData                         **
**                                                                            **
** Service ID           : 0x31                                                **
**                                                                            **
** Description          : Gets the data of a freeze frame by event.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId                                             **
**                        RecordNumber                                        **
**                        ReportTotalRecord                                   **
**                        DataIdentifier                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
**                        Dem_GetPIDDataOnRequest()                           **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventFreezeFrameData(
  Dem_EventIdType EventId, 
  uint8 RecordNumber, 
  boolean ReportTotalRecord,
  uint16 DataIdentifier, 
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer)
{
  Std_ReturnType retVal = E_NOT_OK;
  #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0U) && (DEM_SIZE_OF_FREEZEFRAME > 0U))  
  Dem_DTCOriginType DTCOrigin = DEM_NO_DTC_ORIGIN; 
  #endif

  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATA_SID, DEM_E_UNINIT);
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  /* lse if (DEM_FALSE == Dem_EventIdIsValid(EventId)) */
  else if ((EventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == EventId))
  {
    DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATA_SID, DEM_E_PARAM_CONFIG);
  }
  else if ((DEM_TRUE != ReportTotalRecord) && (DEM_FALSE != ReportTotalRecord))
  {
    DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATA_SID, DEM_E_PARAM_DATA);
  }
  else if (NULL_PTR == DestBuffer)
  /* polyspace<RTE:UNR:Not a defect:No action planned>If-condition always evaluates to false  */
  {
    DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATA_SID, DEM_E_PARAM_POINTER);
  }
  #endif    
  else
  {
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0U) && (DEM_SIZE_OF_FREEZEFRAME > 0U))   
    Dem_EventParameterPCType event = &Dem_Event[EventId-1U];
    if (E_OK == Dem_GetEventDTCOrigin(event, &DTCOrigin))
    {   
      if (DEM_TRUE == Dem_DTCFormatIsValid(EventId, DEM_DTC_FORMAT_OBD))        
      /* polyspace<RTE:UNR:Not a defect:No action planned>If-condition always evaluates to false . No Supported OBD */    
      {
        #if (DEM_OBD2_SUPPORT ==  STD_ON)
        uint16 LusAvoidError;           
        if(0U == RecordNumber)
        {
          /* Dem_GetReadDataOfPID */
          retVal = Dem_GetPIDDataOnRequest(entry, DestBuffer, ReportTotalRecord, DataIdentifier, &LusAvoidError);
        }
        #else
        DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATA_SID, DEM_E_PARAM_CONFIG);      
        #endif
      }
      /* UDS */
      else
      { 
        Dem_ReturnReadEventDataType result = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;    
        if (event->e_PointToData < Dem_Num_Of_EventRelatedData)  
        {
          result = Dem_ReadDataOfFreezeFrame(
            &Dem_EventRelatedData[event->e_PointToData], DTCOrigin, RecordNumber, 
            ReportTotalRecord, DataIdentifier, DEM_FFFORMAT_TYPE_RAW, DestBuffer, NULL_PTR);
        }
        switch(result) {
        case DEM_GET_READEVDATA_OK:
          retVal = E_OK; 
          break;
        case DEM_GET_READEVDATA_NOT_STORED:
          DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATA_SID, DEM_E_PARAM_DATA);    
          retVal = E_NOT_OK; 
          break;        
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */        
        case DEM_GET_READEVDATA_WRONG_BUFFERSIZE:
          DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATA_SID, DEM_E_PARAM_LENGTH);
          retVal = E_NOT_OK;
          break;
        /* case DEM_GET_READEVDATA_WRONG_RECORDNUMBER: */
        default:
          DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATA_SID, DEM_E_PARAM_CONFIG);
          retVal = E_NOT_OK;
          break;
        }      
      }
    }
    else
    #endif
    {
      /* polyspace:begin<RTE:UNR:Not a defect:No action planned> No problem. Unreachable code */
      DEM_UNUSED(EventId);
      DEM_UNUSED(RecordNumber);
      DEM_UNUSED(ReportTotalRecord);
      DEM_UNUSED(DataIdentifier);
      DEM_UNUSED_PTR(DestBuffer);    
      DEM_REPORT_ERROR(DEM_GETEVENTFREEZEFRAMEDATA_SID, DEM_E_PARAM_DATA);
      retVal = E_NOT_OK;
      /* polyspace:end<RTE:UNR:Not a defect:No action planned> No problem. Unreachable code */    
    }
  }
  
  return retVal;
}



/*******************************************************************************
** Function Name        : Dem_GetEventExtendedDataRecord                      **
**                                                                            **
** Service ID           : 0x30                                                **
**                                                                            **
** Description          : Gets the data of an extended data record by event.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : EventId                                             **
**                        RecordNumber                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
 #if(DEM_SIZE_OF_EXTENDED_DATA > 0u)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventExtendedDataRecord(
  Dem_EventIdType EventId, 
  uint8 RecordNumber,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer)
{
  Std_ReturnType retVal = E_NOT_OK;
  Dem_DTCOriginType dtcOrigin = DEM_NO_DTC_ORIGIN;

  if(Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORD_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if((EventId == DEM_NO_EVENT) || (EventId > Dem_Number_Of_Events))
  {
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORD_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */
  }
  else if(DestBuffer == NULL_PTR)
  /* polyspace<RTE:UNR:Not a defect:No action planned>If-condition always evaluates to false  */  
  {
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORD_SID, DEM_E_PARAM_POINTER);
    /* retVal = E_NOT_OK; */
  }
  else if(((RecordNumber < (uint8)DEM_ONE) ||
    (RecordNumber > (uint8)DEM_MAX_VALID_RECORD_NUMBER)) &&
    (RecordNumber != DEM_MAX_RECORD))
  {
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORD_SID, DEM_E_PARAM_CONFIG);
  }
  #endif  
  else  
  #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0U) && (DEM_SIZE_OF_EXTENDED_DATA > 0U))  
  if (E_NOT_OK == Dem_GetEventDTCOrigin(&Dem_Event[EventId-1U], &dtcOrigin))
  {
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORD_SID, DEM_E_PARAM_CONFIG);
  }
  else
  {
    Dem_ReturnReadEventDataType result = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
    Dem_EventParameterPCType event = &Dem_Event[EventId - 1U];    
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
    { 
      result = Dem_ReadDataOfExtendedData(&Dem_EventRelatedData[event->e_PointToData], 
        dtcOrigin, RecordNumber, DestBuffer, NULL_PTR);
    }
    switch(result) {
    case DEM_GET_READEVDATA_OK:
      retVal = E_OK; 
      break;
    case DEM_GET_READEVDATA_NOT_STORED:
      DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORD_SID, DEM_E_PARAM_DATA);    
      retVal = E_NOT_OK; 
      break;        
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */      
    case DEM_GET_READEVDATA_WRONG_BUFFERSIZE:
      DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORD_SID, DEM_E_PARAM_LENGTH);
      retVal = E_NOT_OK;
      break;
    /* case DEM_GET_READEVDATA_WRONG_RECORDNUMBER: */
    default:
      DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORD_SID, DEM_E_PARAM_CONFIG);
      retVal = E_NOT_OK;
      break;
    }
  }
  
  #else

  {
    DEM_REPORT_ERROR(DEM_GETEVENTEXTENDEDDATARECORD_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */

    DEM_UNUSED(EventId);
    DEM_UNUSED(RecordNumber);
    DEM_UNUSED_PTR(DestBuffer);
  }
  #endif
  
  
  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_SetDTCSuppression                               **
**                                                                            **
** Service ID           : 0x33                                                **
**                                                                            **
** Description          : Set the suppression status of a specific DTC.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : DTC                                                 **
**                        SuppressionStatus                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if(DEM_DTC_SUPPRESSION_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)Dem_SetDTCSuppression(
  uint32 DTC, 
  Dem_DTCFormatType DTCFormat, 
  boolean SuppressionStatus)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* Check if the Dem module is not initialized */
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_SETDTCSUPPRESSION_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (
    (DTC == DEM_DTC_GROUP_EMISSION_REL_DTCS) || /* == DEM_NO_DTC */
    (DTC == DEM_DTC_GROUP_ALL_DTCS) ||
    (DTC == DEM_DTC_GROUP_CHASSIS_DTCS) ||
    (DTC == DEM_DTC_GROUP_BODY_DTCS) ||
    (DTC == DEM_DTC_GROUP_POWERTRAIN_DTCS) ||
    (DTC == DEM_DTC_GROUP_NETWORK_COM_DTCS))
  {
    DEM_REPORT_ERROR(DEM_SETDTCSUPPRESSION_SID, DEM_E_PARAM_DATA);
    /* retVal = E_NOT_OK; */
  }
  else if ((SuppressionStatus != DEM_TRUE) && (SuppressionStatus != DEM_FALSE))
  {
    DEM_REPORT_ERROR(DEM_SETDTCSUPPRESSION_SID, DEM_E_PARAM_DATA);
    /* retVal = E_NOT_OK; */
  }
  else if ((DTCFormat != DEM_DTC_FORMAT_OBD) &&
      (DTCFormat != DEM_DTC_FORMAT_UDS))
  {
    DEM_REPORT_ERROR(DEM_SETDTCSUPPRESSION_SID, DEM_E_PARAM_CONFIG);
    /* retVal = E_NOT_OK; */
  }
  #endif  
  else
  {
    /* Dem588 is ignored according to AR 4.2.2 
     *
     * Dem588: The API Dem_SetDTCSuppression shall reject the request and return E_NOT_OK , 
     * if the event memory entry exists already */
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    Dem_CombinedDtcPCType cbDTC = Dem_GetDtcByDtcId(DTC);
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    if ( (NULL_PTR != cbDTC) && (cbDTC->ddDtcFormat == DTCFormat) )
    {
      Dem_NumOfEventIdType startPos = Dem_GetStartEventIdMapOfCbDTC(cbDTC);
      const Dem_NumOfEventIdType endPos = Dem_GetEndEventIdMapOfCbDTC(cbDTC);                
      for (;startPos < endPos; startPos++)
      { 
    	/* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
        Dem_EventIdType eventId = Dem_ListOfCombinedEvents[startPos];
        SchM_Enter_Dem_REQUEST_DATA_PROTECTION();      
        if (DEM_TRUE == SuppressionStatus)
        {
          Dem_EvSetProcState(eventId, DEM_EVPROCSTATE_DTC_SUPP);
        }
        else
        {
          Dem_EvClearProcState(eventId, DEM_EVPROCSTATE_DTC_SUPP);
        }
        SchM_Exit_Dem_REQUEST_DATA_PROTECTION();            
        
        retVal = E_OK;      
      }
    }
    else
    {
      DEM_REPORT_ERROR(DEM_SETDTCSUPPRESSION_SID, DEM_E_PARAM_CONFIG);
      retVal = E_NOT_OK;
    }    
  }
  
  return retVal;
}
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
