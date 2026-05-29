/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_Dtc.c                                                     **
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
** 3.3.4    31-12-2021    LanhLT          Changes made As per Redmine #33335  **
**                                                                            **
** 3.3.3    13-10-2021    LanhLT          Changes made As per Redmine #31127  **
**                                                                            **
** 1.5.4    16-02-2021    EunKyung.Kim    Changes made As per Redmine #28213  **
**                                                                            **
** 1.5.3    04-09-2020    EunKyung.Kim    Changes made As per Redmine #24648, **
**                                        #25254                              **
**                                                                            **
** 1.5.2    06-01-2020    EunKyung.Kim    Changes made As per Redmine #20595  **
**                                                                            **    
** 1.5.1    31-01-2019    EunKyung.Kim    Changes made As per Redmine #14481  **
**                                                                            **
** 1.5.0    10-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.4.0    09-03-2017    YoungJin.Yun    Changes made As per Redmine #6202   **
**                                                                            **
** 1.3.0    06-02-2016    YoungJin.Yun    Changes made As per Redmine #7379   **
**                                                                            **
** 1.2.0    16-06-2016    YoungJin.Yun    Changes made As per Redmine #1164   **
**                                                                            **
** 1.1.1    10-06-2016    YoungJin.Yun    Changes made As per Redmine #5169   **
**                                                                            **
** 1.1.0    07-01-2016    YoungJin.Yun    Changes made As per Redmine #3353,  **
**                                        #698, #3638,#2473,#3271,#2827,#1151,**
**                                        #2589                               **
**                                                                            **
** 1.0.0    06-11-2015    Autron      Initial Version                         **
*******************************************************************************/

/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */ 
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace:begin<MISRA-C:1.1:Not a defect:No action planned> Not a defect  */
/* polyspace-begin MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
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
#include "Dem_EventCallback.h"
#include "Dem_EventMemory.h"
#include "Dem_EventDebounce.h"
#include "Dem_Indicator.h"
#include "Dem_Dtc.h"

#define DEM_START_SEC_CODE
#include "MemMap.h"


static FUNC(Std_ReturnType, DEM_CODE) Dem_DTCGroupIsValid(
  const Dem_DTCGroupType DTCGroup);
  
/*******************************************************************************
 ** Function Name       : Dem_GetDTCGroupId                                   **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : This internal function whether Group DTC input is   **
 **                       configured or not and arranges necessary variables  **
 **                                                                           **
 ** Sync/Async          : Asynchronous                                        **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : LddDTCGroup                                         **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : LpIndex                                             **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCGroupId(
  Dem_DTCGroupType DTCGroup,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DTCGroupId)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint8 i;

  /* Loop through the number of DTC's to get the index of group dtc array */
  for (i = 0U; i < Dem_Max_Num_Grp_DTC; i++)
  {
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    if (Dem_GaaGroupDTC[i] == DTCGroup)
    {
      *DTCGroupId = i;
      retVal = E_OK;
      break;
    }
  }

  return retVal;
}

/*******************************************************************************
 ** Function Name       : Dem_DTCGroupIsValid                                 **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : This internal function checks whether Group DTC     **
 **                       input is configured or not                          **
 **                                                                           **
 ** Sync/Async          : Asynchronous                                        **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : DTCGroup                                            **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
static FUNC(Std_ReturnType, DEM_CODE) 
Dem_DTCGroupIsValid(const Dem_DTCGroupType DTCGroup)
{
  Std_ReturnType retVal = E_NOT_OK;

  if ( (DEM_DTC_GROUP_ALL_DTCS == DTCGroup) ||  (DEM_DTC_GROUP_EMISSION_REL_DTCS == DTCGroup) )
  {
    retVal = E_OK;
  }
  else
  {
    uint8 dtcGroupId;
    for (dtcGroupId = 0U; dtcGroupId < Dem_Max_Num_Grp_DTC; dtcGroupId++)
    {
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */	
      if (Dem_GaaGroupDTC[dtcGroupId] == DTCGroup)
      {
        retVal = E_OK;
        break;
      }
    }
  }

  return retVal;
}


/******************************************************************************
 * Function Name        : Dem_GetConditionOfDTCRecordUpdate == *1
 *
 * Service ID           : None
 *
 ** Description          : It is used to check the condition of a DTC for
 **                        Processing
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : DTC, DTCOrigin
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Std_ReturnType(E_OK or E_NOT_OK)
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *
 ******************************************************************************/
FUNC(Dem_ReturnConditionOfDTCRecordUpdateType, DEM_CODE)
Dem_GetConditionOfDTCRecordUpdate(
  const Dem_DTCType DTC,
  const Dem_DTCOriginType DTCOrigin)
{
  Dem_ReturnConditionOfDTCRecordUpdateType retVal = DEM_CONDITIONDTCRECUP_NO_DTC;

  /* Check already a record is disabled */
  #if(DEM_OBD_SUPPORT == STD_ON)
  if ((Dem_GstRecordDisableDTC.usObdDtc != 0U) ||
      (Dem_GstRecordDisableDTC.ulUdsDtc != 0U))
  #else
  if  (Dem_GstRecordDisableDTC.ulUdsDtc != 0U)
  #endif
  { 
    #if(DEM_OBD_SUPPORT == STD_ON)
    if(((Dem_GstRecordDisableDTC.usObdDtc == DTC) ||
        (Dem_GstRecordDisableDTC.ulUdsDtc == DTC)) &&
    #else
    if((Dem_GstRecordDisableDTC.ulUdsDtc == DTC) &&
    #endif
       (Dem_GstRecordDisableDTC.ddDtcOrigin == DTCOrigin))
    {
      retVal = DEM_CONDITIONDTCRECUP_DISABLED_DTC;
    }
    else
    {
      retVal = DEM_CONDITIONDTCRECUP_NO_MATCHING_DTC;
    }
  }
  
  return retVal;
}


/*******************************************************************************
 ** Function Name       : Dem_CountAndStoreFilterDtc > 2                      **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Counts and store the filtered dtc as per request by **
 **                       Dcm                                                 **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/


FUNC(void, DEM_CODE) Dem_CountAndStoreFilterDtc(void)
{
  #if(DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)

  Dem_NumOfDTCValueType dtcLoc = 0u;
  Std_ReturnType result = E_NOT_OK;

  /* Loop can be cancelled by Dem_DcmCancelOperation (done DEM_JOB_RUNNING->DEM_JOB_CANCEL)*/
  for (dtcLoc = 0u; 
      (dtcLoc < Dem_Max_Number_Of_DTC) && (Dem_DTCFilterState.dfs_JobAction == DEM_JOB_RUNNING); 
      dtcLoc++)
  {
    P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) cbDTC = &Dem_GaaCombinedDtc[dtcLoc];
    Dem_EventIdType eventId = Dem_GetFirstEventOfDTC(cbDTC);
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid to 'Unreachable code' of the polyspace */
    if (DEM_NO_EVENT != eventId)
    {
      /* DTCSuppressionStatus: Don't worry aboue combination type 1, type2
       * Refer to Dem_SetDTCSuppression 
       * E_OK means 'DTCSuppression == false' */

      /* polyspace<RTE:UNR:Not a defect:No action planned> Unreachable code' according to DTCSuppression configuration */       
      if (DEM_FALSE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP)) 
      {
        Dem_UdsStatusByteType dtcStatus = Dem_GetDTCStatus(eventId);   
        
        #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))        
        if ( (DEM_DTC_ORIGIN_PERMANENT_MEMORY == Dem_DTCFilterState.dfs_DTCOrigin) )
        {
          Dem_NumOfEventMemoryEntryType memLoc = DEM_NO_EVMEM_ENTRY;
          memLoc = Dem_EvMem_FindPerMemLoc(eventId);
          if(memLoc != DEM_NO_EVMEM_ENTRY)
          {
            result = E_OK;
          }
          else
          {
            result = E_NOT_OK;
          }
        }
        else
        #endif           
        
        {          
          result = E_OK; 
          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
          if (Dem_Event[eventId-1].aaEventDestination != Dem_DTCFilterState.dfs_DTCOrigin)
          {
            result = E_NOT_OK;
          }
          /* Check for DTCKind filter matching */
          else if((cbDTC->ddDtcKind != Dem_DTCFilterState.dfs_DTCKind)  && (Dem_DTCFilterState.dfs_DTCKind != DEM_DTC_KIND_ALL_DTCS) )
          /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to false. But condition can be changed according the Diagnotic Request of the Tester */      
          {
            result = E_NOT_OK;
          }
          /* Check for DTCFormat filter matching */
          else if (Dem_EvMem_DTCFormatIsValid(Dem_DTCFilterState.dfs_DTCFormat, cbDTC) != DEM_TRUE)
          {
            result = E_NOT_OK;
          }
          /* Check for DTCStatusMask filter matching */
          else if (0U != Dem_DTCFilterState.dfs_DTCStatusMask)
          {
            Dem_UdsStatusByteType statusMask = Dem_DTCFilterState.dfs_DTCStatusMask;

            /* If specific StatusAvailablilityMask of a DTC is existed */
            if (0U != cbDTC->UdsStatusAvailabilityMask)
            {
              /* UdsStatusAvailabilityMask and Dem_DTCFilterState.dfs_DTCStatusMask are
               * subset of Dem_Status_Availability_Mask */
              statusMask = Dem_DTCFilterState.dfs_DTCStatusMask & cbDTC->UdsStatusAvailabilityMask;
            }
            if ((dtcStatus & statusMask) == 0U)
            {
              result = E_NOT_OK;
            }
          }
          else
          {
            /* [SWS_Dcm_00378 
             * The value 0x00 used as DTCStatusMask for the subfunctions 0x0A and 0x15 
             * disables the status byte filtering in Dem_DcmSetDTCFilter() */          
          }          
          
          /* Check for DTCSeverity filter matching */
          if ((Dem_DTCFilterState.dfs_FilterWithSeverity == (Dem_FilterWithSeverityType)DEM_FILTER_WITH_SEVERITY_YES) &&
             ((cbDTC->ddDtcSeverity & Dem_DTCFilterState.dfs_DTCSeverityMask) == 0U))
          {
            result = E_NOT_OK;
          }
          
          /* Check if Filter with FDC supported */
          if(Dem_DTCFilterState.dfs_FilterForFDC == (Dem_FilterForFDCType)DEM_FILTER_FOR_FDC_YES)
          {
            sint8 FDC = (sint8)0x00;
            
            /* If event don't support FDC , FDC is zero, so 'result' is no-ok  */
            if (E_OK == Dem_GetFaultDetectionCounter(eventId, &FDC))
            {
              /* [SWS_Dem_00208]: The FDC values should be in the range 0x01-0x7E */
              if((FDC < (sint8)1) || (FDC > (sint8)0x7E))
              {
                result = E_NOT_OK;          
              }
            }
          }
        }

        if (E_OK == result)
        {
          Dem_EvSetProcState(eventId, DEM_EVPROCSTATE_DTC_FILTER);
          /* Increment the number of filtered DTC */
          Dem_DTCFilterState.dfs_NumOfFilteredDTC++;              
        }
      }
    }
  }
  #endif

  SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
  /* polyspace<RTE:UNR:Not a defect:No action planned> if-condition will evaluate to false if Dem_DcmCancelOperation is called by Dcm */         
  if (DEM_JOB_RUNNING == Dem_DTCFilterState.dfs_JobAction)
  {
    Dem_DTCFilterState.dfs_JobAction = DEM_JOB_DONE;
  }
  SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
}

FUNC(Std_ReturnType, DEM_CODE) Dem_ClearSingleDTCStatusByte(
  Dem_CombinedDtcPCType CbDTC)
{
  Std_ReturnType retVal = E_NOT_OK;

  Dem_EventIdType eventId;
  Dem_EventParameterPCType event;
  Dem_EventParameterCallbackPtrType eventCbk;

  boolean clearAllowed;
  
  Dem_NumOfEventIdType startPos = Dem_GetStartEventIdMapOfCbDTC(CbDTC);
  const Dem_NumOfEventIdType endPos = Dem_GetEndEventIdMapOfCbDTC(CbDTC); 
  
  for (;startPos < endPos; startPos++)
  {
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */    
    eventId = Dem_ListOfCombinedEvents[startPos];
    event = &Dem_Event[eventId-1U];

    Dem_EvClearProcState(eventId,DEM_EVPROCSTATE_EVENT_DEL);
        
    clearAllowed = DEM_TRUE; 

    #if ( DEM_NUMBER_OF_EVENT_CALLBACK > 0)
    if(event->e_PointToEventCallbackData < (Dem_EventIdType)DEM_NUMBER_OF_EVENT_CALLBACK)
    {
      eventCbk = &Dem_EventCallback[event->e_PointToEventCallbackData];
    }
    else
    #endif
    {
      eventCbk = NULL_PTR;
    }
    
    if ((NULL_PTR != eventCbk) && (NULL_PTR != eventCbk->pDemClearEventAllowed))
    { 
      boolean allowed = DEM_TRUE;    
      /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */    
      if (E_OK == eventCbk->pDemClearEventAllowed(&allowed))
      {
        /* [SWS_Dem_00667] If the out-parameter 'Allowed' of the callback ClearEventAllowed
         * returns 'false' (and the return value is equal to E_OK) after the execution of this call-
         * back function, the respective event memory entry and Dem-internal data values
         * must not be cleared. (SRS_Diag_04092, SRS_Diag_04122) */
        if (DEM_FALSE == allowed)
        {
          clearAllowed = DEM_FALSE;          
        }
      }
      else
      {
        /* [SWS_Dem_00516] 
         * If the return value of the callback ClearEventAllowed is not
         * equal to E_OK, the event-deletion is allowed anyway (because of safety aspects).
         * (SRS_Diag_04092, SRS_Diag_04122) */
      }
    }
    
    if(DEM_TRUE == clearAllowed)
    {     
      uint8 debType = DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(event->ParamFieldsA);
      Dem_UdsStatusByteType DTCStatusOld = Dem_GetDTCStatus(eventId);
      Dem_UdsStatusByteType EventStatusByteOld = Dem_AllEventStatusByte[eventId];

      /* @IF_REQ: SWS_Dem_00301 :
       * Permanent DTCs must only be cleared once they have been self-healed if the last
       * diagnosis result is detected as a PASS and the MIL is no longer being triggered for this event. */
       
      /* Re-initialization triggered before the Dem module returns  DEM_CLEAR_OK */
      #if (DEM_TRIGGER_INIT_BEFORE_CLEAR_OK == STD_ON)
      if ((NULL_PTR != eventCbk) && (eventCbk->pDemInitMonitorForEvent != NULL_PTR))
      {
        /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */    
        eventCbk->pDemInitMonitorForEvent((Dem_InitMonitorReasonType)DEM_INIT_MONITOR_CLEAR);
      }    
      #endif
    
      /* [Dem077] 
       * The function Dem_ClearDTC shall clear the status of all event(s) related
       * to the specified DTC(s), as well as all associated event memory entries for these event(s). */
      DEM_RST_UDSSTATUSBYTE(eventId, (uint8)DEM_UDS_STATUS_TNCSLC |(uint8)DEM_UDS_STATUS_TNCTOC);
    
      /* Dem343:
       * After receiving a command for clearing the event memory (refer to Dem_ClearDTC), 
       * the respective fault detection counters shall be initialized with 0,
       * presuming event debouncing is handled Dem-internally. */
      if ( (DEM_DEBOUNCE_TIME_BASED == debType)|| (DEM_DEBOUNCE_COUNTER_BASED == debType) )
      {
        Dem_ResetFaultDectectionCounter(event);
      }  
    
      /* Reset the indicator failure cycle counter to zero */
      if (DEM_TRUE == Dem_InitIndicator(eventId))
      {
        Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_CLEARDTC);            
      }
      
      #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
      {
        Dem_NumOfEventMemoryEntryType memLoc = DEM_NO_EVMEM_ENTRY;
        memLoc = Dem_EvMem_FindPerMemLoc(eventId);
        if(DEM_NO_EVMEM_ENTRY != memLoc)
        {
  /*      MRM is considered to apply later
          if(MRM == 1)
          {
            if(Dem_GaaIndicatorList[event->e_PointToIndicator].NumHealingCycles>0)
            {
              Dem_EvMem_SetIndicatorHealingCounter( Dem_GaaIndicatorList[event->e_PointToIndicator].HealingCycleCounterPos, Dem_GaaIndicatorList[event->e_PointToIndicator].NumHealingCycles-1);
            }
          }
          else
  */
          {
            if(Dem_GaaIndicatorList[event->e_PointToIndicator].NumHealingCycles>1)
            {
              Dem_EvMem_SetIndicatorHealingCounter(Dem_GaaIndicatorList[event->e_PointToIndicator].HealingCycleCounterPos, Dem_GaaIndicatorList[event->e_PointToIndicator].NumHealingCycles-2);
  /*          Dem_EvMem_SetIndicatorAttStatus(eventId, Dem_GaaIndicatorList[event->e_PointToIndicator].IndicatorAttStatusPos, DEM_TRUE); */
              Dem_PerDtcState[memLoc].PfcQualified  = DEM_FALSE;
            }
          }
        }
      }
      #endif
      

      if (EventStatusByteOld != Dem_AllEventStatusByte[eventId])
      {
        Dem_TriggerCallbackOnUdsStatus(eventId, EventStatusByteOld, DTCStatusOld);  
        /* polyspace +1 DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
        #if (DEM_UDS_STATUS_IN_EVENT_NVBLOCK == STD_ON)
        if (((EventStatusByteOld ^ Dem_AllEventStatusByte[eventId]) & DEM_UDS_STATUS_MASK_ALLEVENTSTATUS) != 0U)
        {
          /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "Not a defect" */
          Dem_EvMem_SetUdsStatusByteToNvData(eventId);
          Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_CLEARDTC);
        }
        #endif
      }
  
      #if (DEM_TRIGGER_INIT_BEFORE_CLEAR_OK == STD_OFF)
      /* Re-initialization triggered after the Dem module returns DEM_CLEAR_OK */
      /* if (DEM_CLEAR_OK == retVal) : condition is always true */
      Dem_EvSetProcState(eventId,DEM_EVPROCSTATE_INITMON_ONCLEARDTC);
      #endif      

      if (DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_EVENT_STORED))
      {
        Dem_EvSetProcState(eventId,DEM_EVPROCSTATE_EVENT_DEL);
      }
      
      retVal = E_OK;        
    }
  }
  
  return retVal;
}

/******************************************************************************
 * Function Name        : Dem_GetDTCStatus
 *
 * Service ID           : None
 *
 * Description          : This function is used to update data and 
 *                        to add new event in the event memory
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
 * Return parameter     : Dem_UdsStatusByteType
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *****************************************************************************/
FUNC(Dem_UdsStatusByteType, DEM_CODE) Dem_GetDTCStatus(
  const Dem_EventIdType EventId)
{
  Dem_UdsStatusByteType DTCStatus = 0U; 
  
  #if (DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_DISABLED)
  P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) cbDTC = Dem_GetCbDTCByEventId(EventId);    
  if (NULL_PTR != cbDTC)
  {    
    volatile Dem_UdsStatusByteType CbDTCStatus = 0u;    
    Dem_NumOfEventIdType startPos = Dem_GetStartEventIdMapOfCbDTC(cbDTC);
    const Dem_NumOfEventIdType endPos = Dem_GetEndEventIdMapOfCbDTC(cbDTC);                
    for (;startPos < endPos; startPos++)
    {
      /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      /* Compute the DTC status */
      DTCStatus |= Dem_AllEventStatusByte[Dem_ListOfCombinedEvents[startPos]];
    }
    /* As per SWS SWS_Dem_00441 : CbEvtBit 4 = (Event[1]Bit 4 | Event[2]Bit 4 | ... | Event[n]Bit 4) & ! CbEvtBit 5 */
    if (0U != (DTCStatus & DEM_UDS_STATUS_TFSLC))
    {
      DTCStatus &= (Dem_UdsStatusByteType)((uint8)0xFFU & ~(Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC);
    }
    /* As per SWS SWS_Dem_00441 : CbEvtBit 6 = (Event[1]Bit 6 | Event[2]Bit 6 | ... | Event[n]Bit 6) & ! CbEvtBit 1  */    
    if (0U != (DTCStatus & DEM_UDS_STATUS_TFTOC))
    {
      DTCStatus &= (Dem_UdsStatusByteType)((uint8)0xFFU & ~(Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCTOC);
    }
  }
  #else  
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. */
  if (DEM_TRUE == Dem_EventIdIsValid(EventId))
  {
    /* Update the DTC Status */
    DTCStatus = Dem_AllEventStatusByte[EventId];
  }
  #endif  

  return DTCStatus;
}

/* polyspace:end<MISRA-C:5.1:Not a defect:Justify with annotations> This Identifier is Specification. */

/*******************************************************************************
** Function Name        : Dem_InternalClearDTC                                **
**                                                                            **
** Service ID           : 0x22                                                **
**                                                                            **
** Description          : This API shall be used to clear single DTC's as     **
**                        well as group of DTC's                              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Uint32 DTC                                          **
**                        DTCOrigin, DTCFormat                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_ReturnClearDTCType                              **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_InternalClearDTC(uint32 DTC,
  Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
  Dem_ReturnClearDTCType retVal = DEM_CLEAR_FAILED;

  if (DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_UNINIT);
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((DEM_DTC_FORMAT_OBD != DTCFormat) && (DEM_DTC_FORMAT_UDS != DTCFormat) && (DEM_DTC_FORMAT_J1939 != DTCFormat))
  {
    DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_PARAM_CONFIG); 
  }
  /* checks supported DTCOrigin in ECU */  
  else if (DEM_FALSE == Dem_EvMem_DTCOriginIsValid(DTCOrigin))
  {
    DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_PARAM_CONFIG);
    retVal = DEM_CLEAR_WRONG_DTCORIGIN;
  }  
  #endif       
  else 
  {
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    if ( 
      (DEM_FALSE == Dem_ClearDtcState.cds_RequestCancel) 
      ||
      ( (DEM_TRUE == Dem_ClearDtcState.cds_RequestCancel) 
        &&
        ((DEM_CLEARDTC_STATE_AFTER_CLEAROK == Dem_ClearDtcState.cds_State) || /* return pending */
         (DEM_CLEARDTC_STATE_READY == Dem_ClearDtcState.cds_State)) /* new request can be accepted */
          /* other states shall be processed in Dem_EvMem_MainFunctionClearDtc */
      )
    )
    {
      switch (Dem_ClearDtcState.cds_State) 
      {  
        case DEM_CLEARDTC_STATE_READY:   

          Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_PREPARE_CLEARDTC;
          
          Dem_ClearDtcState.cds_RequestCancel = DEM_FALSE; 
          Dem_ClearDtcState.cds_DTC = DTC;      
          Dem_ClearDtcState.cds_DTCFormat = DTCFormat;
          Dem_ClearDtcState.cds_DTCOrigin = DTCOrigin;
          Dem_ClearDtcState.cds_Result = DEM_CLEAR_FAILED;
          Dem_ClearDtcState.cds_MemLocation = 0U;
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

          retVal = DEM_CLEAR_WRONG_DTC;
          
          /* Single DTC - Note: E_NOT_OK means Single DTC  */
          if (E_NOT_OK == Dem_DTCGroupIsValid(DTC))
          { 
            /* [SWS_Dem_00718] In Master, Primary and Dependent / Secondary ECUs
             * executing service $04 shall clear all emission-related diagnostic information in primary
             * and user defined (event) memory (if con?gured) as defined in SAE J1979 [18]. 
             */             
            if (DEM_DTC_FORMAT_OBD != DTCFormat)
            {      
              #if (DEM_DEV_ERROR_DETECT == STD_ON)
              Dem_EventIdType eventId = Dem_GetEventIdByDTC(DEM_CLEARDTC_SID, DTC);
              #else
              Dem_EventIdType eventId = Dem_GetEventIdByDTC(DTC);
              #endif  
              /* if (DEM_TRUE == Dem_EventIdIsValid(eventId)) */
              if ((eventId <= Dem_Number_Of_Events) && (DEM_NO_EVENT != eventId))
              {
                Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(eventId);
                /* Only clear the event(s) assigned to a single DTC */           
                if (DEM_TRUE == Dem_EvMem_DTCFormatIsValid(DTCFormat, cbDTC)) /* DEM_DTC_FORMAT_UDS */
                {
                  if (DEM_TRUE == Dem_DTCOriginBelongToEvent(eventId, DTCOrigin))               
                  {                        
                    Dem_ClearDtcState.cds_EventIdRef = eventId;               
                    retVal = DEM_CLEAR_PENDING;
                  }
                  else
                  {
                    retVal = DEM_CLEAR_WRONG_DTCORIGIN;              
                  }
                }
              }
            }
          }
          /* Group DTC */
          else
          {
            Dem_ClearDtcState.cds_EventIdRef = DEM_NO_EVENT; /* If event is null-ptr, DTC is DTC Group */
            retVal = DEM_CLEAR_PENDING;              
          }      

          if (DEM_CLEAR_PENDING != retVal)
          {
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_READY;
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();            
            DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_PARAM_DATA);   
          }
          break;

        case DEM_CLEARDTC_STATE_PREPARE_CLEARDTC: /* No break; */
        case DEM_CLEARDTC_STATE_RUNNING: /* No break; */
        case DEM_CLEARDTC_STATE_CLEAR_EVMEM: /* No break; */
        case DEM_CLEARDTC_STATE_RESET_EVENTS: /* No break; */
        case DEM_CLEARDTC_STATE_WAIT:    /* No break; */
        case DEM_CLEARDTC_STATE_AFTER_CLEAROK: 
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

          /* Note: DEM_CLEARDTC_STATE_AFTER_CLEAROK
           * If new request is accepted and Dem don't completed previous request's job yet, 
           * The dem returns DEM_CLEAR_PENDING , and after finishing job , Dem will process new request */              
          retVal = DEM_CLEAR_PENDING;
          break;            
        case DEM_CLEARDTC_STATE_RESULT:
          Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_AFTER_CLEAROK;        
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION(); 

          retVal = Dem_ClearDtcState.cds_Result;  
          break;      
        /* polyspace<RTE:UNR:Not a defect:No action planned> No error. Avoid to 'Unreachable code' of the polyspace */        
        default:
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          retVal = DEM_CLEAR_FAILED;
          DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_UNEXPECTED_RESULT);    
          break;  
      }
    }
    else
    {
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION(); 
    }
  }
  
  return retVal;
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace:end<MISRA-C:1.1:Not a defect:No action planned> Not a defect  */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */

