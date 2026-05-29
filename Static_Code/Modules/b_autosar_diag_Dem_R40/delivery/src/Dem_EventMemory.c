/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_EventMemory.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of storage of non-volatile data to NvM              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*
 * @IF_REQ List
 * 1 . Dem_EvMem_ClearEvMemEntriesByClearDTC and Dem_ClearSingleDTCStatusByte
 *     shall be merged
 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date:DD-MM-YYYY By            Description                         **
********************************************************************************
** 3.3.4    31-12-2021    LanhLT          Changes made As per Redmine #33335  **
**                                                                            **
** 3.3.2    16-07-2021    LanhLT(FPT)     Changes made As per Redmine #30852  **
**                                                                            **
** 1.6.4    16-02-2021    EunKyung.Kim    Changes made As per Redmine #28213, **
**                                        #25380                              **
**                                                                            **
** 1.6.3    04-09-2020    EunKyung.Kim    Changes made As per Redmine #25254  **
**                                                                            **
** 1.6.2    02-04-2019    EunKyung.Kim    Changes made As per Redmine #16382  **
**                                                                            **
** 1.6.1    31-01-2019    EunKyung.Kim    Changes made As per Redmine #14481  **
**                                                                            **
** 1.6.0    10-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.5.4    12-12-2018    YoungJin.Yun    Changes made As per Redmine #14900  **
**                                                                            **
** 1.5.3    09-11-2018      EunKyung.Kim  Changes made As per Redmine #14481  **
**                                                                            **
** 1.5.2    20-07-2017      EunKyung.Kim  Changes made As per Redmine #9294   **
**                                                                            **
** 1.5.1    31-05-2017      EunKyung.Kim  Changes made As per Redmine #8166,  **
**                                        #8686                               **
**                                                                            **
** 1.5.0    09-03-2017      YoungJin.Yun  Changes made As per Redmine #6202   **
**                                                                            **
** 1.4.1    06-02-2016      YoungJin.Yun  Changes made As per Redmine #7379   **
**                                                                            **
** 1.4.0    16-11-2016      YoungJin.Yun  Changes made As per Redmine #6549   **
**                                        #6188                               **
**                                                                            **
** 1.3.0    30-09-2016      YoungJin.Yun  Changes made As per Redmine #6097   **
**                                                                            **
** 1.2.0    16-06-2016      YoungJin.Yun  Changes made As per Redmine #1164,  **
**                                        #4901                               **
**                                                                            **
** 1.1.3    08-06-2016      YoungJin.Yun  Changes made As per Redmine #5099,  **
**                                        #5169                               **
**                                                                            **
** 1.1.2    11-05-2016      YoungJin.Yun  Changes made As per Redmine #4833   **
**                                                                            **
** 1.1.1    03-03-2016      YoungJin.Yun  Changes made As per Redmine #4215   **
**                                                                            **
** 1.1.0    07-01-2016      YoungJin.Yun  Changes made As per Redmine #3353,  **
**                                        #698 , #3638, #2473, #3271, #2827,  **
**                                        #1151, #2589                        **
**                                                                            **
** 1.0.0    02-07-2015      YoungJin.Yun  Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"            /* DEM module Header File */
#include "Dem_Ram.h"        /* DEM Ram Header File */

#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"            /* Det Module Header File */
#endif
#include "NvM.h"            /* NVRAM manager symbols Header File */

#include "BswM.h"

#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "Rte_Dem.h"

#include "Dem_Event.h"
#include "Dem_EventCallback.h"
#include "Dem_NvData.h"
#include "Dem_EventRelatedData.h"
#include "Dem_Indicator.h"
#include "Dem_EventDebounce.h"
#include "Dem_Dtc.h"
#include "Dem_EventMemory.h"

#if (DEM_J1939_SUPPORT == STD_ON)
#include "Dem_J1939.h"
#include "Dem_J1939Types.h"
#include "Dem_J1939Ram.h"
#endif

/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace-begin MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-begin DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, DEM_CODE) Dem_EvMem_ClearEvMemEntriesByClearDTC(
  Dem_DTCOriginType DTCOrigin,
  boolean ClearDTCOccurrenceTime);

static FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_EvMem_ClearDTCOfAllGroup(
  Dem_DTCFormatType DTCFormat,  
  Dem_DTCOriginType DTCOrigin
  #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
  , Dem_J1939DcmSetClearFilterType DTCTypeFilter
  #endif
);

static FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_EvMem_ClearSingleDTC(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin); 

static FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_EvMem_ClearDTCOfDTCGroup(
  Dem_DTCGroupType DTCGroup,
  Dem_DTCFormatType DTCFormat,  
  Dem_DTCOriginType DTCOrigin);
  
static  FUNC(boolean, DEM_CODE) Dem_EvMem_WriteAll(
  const uint8 Filter); 

static  FUNC(boolean, DEM_CODE) Dem_EvMem_ReadAll(
  const uint8 Filter);     

#if (DEM_EVENT_CLEAR_SUPPORT == STD_ON)
static FUNC(void, DEM_CODE) Dem_EvMem_ClearEventStatusByte(void);
#endif

/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearEvMemEntriesByClearDTC               **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Clear the dtcs from event memory                    **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : DTCGroup, ClearDTCOccurrenceTime                    **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   :                                                     **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* polyspace +1 MISRA-C3:2.7 [Justified:Low] "Not a defect" */
static FUNC(void, DEM_CODE) Dem_EvMem_ClearEvMemEntriesByClearDTC(
  Dem_DTCOriginType DTCOrigin,
  boolean ClearDTCOccurrenceTime)
{
  Dem_NumOfEventMemoryEntryType memLoc;
  Dem_EventIdType eventId;

  /* Dem_EvMem_DTCOriginIsValid is duplcated code (checked by Dem_ClearDTC) , 
   * but this is added to prevent the orange error of the polyspace */        
  /* if (DEM_TRUE == Dem_EvMem_DTCOriginIsValid(Dem_ClearDtcState.cds_DTCOrigin)) */
  if ((DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC > 0U)          
   || (DEM_DTC_ORIGIN_SECONDARY_MEMORY == DTCOrigin)
  #endif
  )
  {
    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
    uint32 maxTimeStamp = 0U;
    #endif
      
    for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[DTCOrigin]; memLoc++)                    
    {      
      eventId = Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin,memLoc);
      /* if (DEM_TRUE == Dem_EventIdIsValid(eventId)) */
      if ((eventId <= Dem_Number_Of_Events) && (DEM_NO_EVENT != eventId))
      {         
        Dem_EventMemoryEntryPtrType entry = Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, memLoc);      
        /* SingleDTC or All DTCs are able to be deleted via flag DEM_EVPROCSTATE_EVENT_DEL */
        if (DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_EVENT_DEL))
        {       
          /* ISO-14229,160p:
           * first/most recent failed/comfirmed DTC information shall be cleared 
           * upon a successful ClearDiagnosticInformation request from the client */
          #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
          if ((DEM_TRUE == ClearDTCOccurrenceTime) 
            #if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC > 0U)
            && (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
            #endif
          )
          {
            Dem_DTCType dtcVal = 0U;
            /* Dem_GetEventDTC always is true because 
             * event with DTC is able to store in the memory */
            (void)Dem_GetEventDTC(&Dem_Event[eventId-1U], &dtcVal, DEM_DTC_FORMAT_UDS);
            if (DEM_TRUE == Dem_EvMem_ClearDTCOccurrenceTime(dtcVal, DEM_FALSE))
            {
              Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_CLEARDTC);            
            }            
          }
          #endif
          /* No need critical section */
          Dem_EvClearProcState(eventId,DEM_EVPROCSTATE_EVENT_DEL);

          #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)  
          Dem_EvMem_ClearMemLocInEvMemMap(eventId, DTCOrigin, entry);
          #else
          Dem_EvMem_ClearMemLocInEvMemMap(eventId, DTCOrigin);
          #endif
          
           /* Clear the event memory entry in RAM */
          Dem_EvMem_ClearEventMemoryEntry(entry); 

          /* NvBlock flag for EventStatus will be set after this job has been finished */          
          Dem_EvMem_SetEvMemNvBlockStatus(DTCOrigin, memLoc, DEM_EVMEM_STATUS_CLEARDTC);  
        }
        else
        {
          /* searching max time stamp */
          #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
          uint32 currTimeStamp = Dem_EvMem_GetTimeStamp(entry);       
          if (maxTimeStamp < currTimeStamp)
          {
            maxTimeStamp =  currTimeStamp;
          }
          #endif
        }
      }
    }
    #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
    Dem_MaxTimeStamp[DTCOrigin] = maxTimeStamp;
    #endif
  }
}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearDTCOfAllGroup                        **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Clear the dtcs from event memory                    **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : DTCGroup, DTCFormat,DTCOrigin                       **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   :                                                     **
 **                                                                           **
 ** Return parameter    : DEM_CLEAR_FAILED  : Operation is failed             **
 **                       DEM_CLEAR_OK : Clears at least one event            **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
static FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_EvMem_ClearDTCOfAllGroup(
  Dem_DTCFormatType DTCFormat,  
  Dem_DTCOriginType DTCOrigin
  #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
  , Dem_J1939DcmSetClearFilterType DTCTypeFilter
  #endif
)
{
  Dem_ReturnClearDTCType retVal = DEM_CLEAR_FAILED; 
  Dem_NumOfDTCValueType dtcLoc;
#if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
  Dem_ClearDtcState.cds_DTCTypeFilter = 0U; /* Not used */
#endif

  for (dtcLoc = 0u; dtcLoc < Dem_Max_Number_Of_DTC;  dtcLoc++)
  {
    Dem_CombinedDtcPCType cbDTC = &Dem_GaaCombinedDtc[dtcLoc];    
    if (DEM_TRUE == Dem_EvMem_DTCFormatIsValid(DTCFormat, cbDTC))   
    {
      Dem_EventIdType eventId = Dem_GetFirstEventOfDTC(cbDTC);
      /* polyspace<RTE:UNR:Not a defect:No action planned>If-condition always evaluates to true  */      
      if (DEM_NO_EVENT != eventId)
      {
        if (DEM_TRUE == Dem_DTCOriginBelongToEvent(eventId, DTCOrigin))
        {      
          /*
          +--------------------------------------+-----------------------------------------+
          | DEM_J1939DTC_CLEAR_ALL               | ConfirmedDTC == 1 AND TestFailed == 1   |
          +--------------------------------------+-----------------------------------------+
          | DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE | ConfirmedDTC == 1 AND TestFailed == 0   |
          +--------------------------------------+-----------------------------------------+*/ 
          #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
          boolean clearDTC = DEM_FALSE;
          if(DEM_DTC_FORMAT_J1939 == DTCFormat)
          {
            boolean obdDtc = Dem_EvMem_DTCFormatIsValid(DEM_DTC_FORMAT_OBD, Dem_GetCbDTCByEventId(eventId));
            /* DM11  */
            if (DEM_J1939DTC_CLEAR_ALL == DTCTypeFilter)
            {
              Dem_UdsStatusByteType dtcStatus = Dem_GetDTCStatus(eventId);             
              if (((dtcStatus & (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDTC)) == (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDTC)) || (DEM_TRUE == obdDtc))
              {
                clearDTC = DEM_TRUE;
              }
            }
            /* DM03 */
            else if (DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE == DTCTypeFilter)
            {
              Dem_UdsStatusByteType dtcStatus = Dem_GetDTCStatus(eventId);
              if (((dtcStatus & (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDTC)) == DEM_UDS_STATUS_CDTC) && (DEM_FALSE == obdDtc))
              {
                clearDTC = DEM_TRUE;
              }
            }
            else
            {
              clearDTC = DEM_TRUE;
            }
          }
          else
          {
            clearDTC = DEM_TRUE;
          }

          if (DEM_TRUE == clearDTC)
          #endif
          {                          
            if (E_OK == Dem_ClearSingleDTCStatusByte(cbDTC))
            {          
              retVal = DEM_CLEAR_OK;
            }
          }
 #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
          else
          {
            if(DEM_DTC_FORMAT_J1939 == DTCFormat)
            {
                retVal = DEM_CLEAR_OK;
            }
          }
 #endif
        }
      }
    }
  }

  return retVal;
}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearDTCOfDTCGroup                        **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Clear the all dtc with specific DTCOrigin           **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : DTCGroup, DTCFormat, DTCOrigin                      **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   :                                                     **
 **                                                                           **
 ** Return parameter    : Dem_ReturnClearDTCType                              **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
static FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_EvMem_ClearDTCOfDTCGroup(
  Dem_DTCGroupType DTCGroup,
  Dem_DTCFormatType DTCFormat,  
  Dem_DTCOriginType DTCOrigin)
{
  Dem_ReturnClearDTCType retVal = DEM_CLEAR_FAILED; 
  Dem_NumOfDTCValueType dtcLoc;
  Dem_EventIdType eventId;

  for (dtcLoc = 0u; dtcLoc < Dem_Max_Number_Of_DTC;  dtcLoc++)
  {
    Dem_CombinedDtcPCType cbDTC = &Dem_GaaCombinedDtc[dtcLoc];  
    eventId = Dem_GetFirstEventOfDTC(cbDTC);
    
    /* polyspace<RTE:UNR:Not a defect:No action planned> for misra */      
    if (DEM_NO_EVENT != eventId)
    {    
      if ( (cbDTC->ddDtcFormat == DTCFormat) && 
           (cbDTC->ddDtcGroup < Dem_Max_Num_Grp_DTC) && 
	   /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */   
           (Dem_GaaGroupDTC[cbDTC->ddDtcGroup] == DTCGroup) )
      {
        if (DEM_TRUE == Dem_DTCOriginBelongToEvent(eventId, DTCOrigin))
        {      
          if (E_OK == Dem_ClearSingleDTCStatusByte(cbDTC))
          {          
            retVal = DEM_CLEAR_OK;          
          }
        }
      }
    }
  }

  return retVal;
}


/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearSingleDTC                            **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Clear the single dtc data from memory               **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : Event, DTC, DTCOrigin                               **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   :                                                     **
 **                                                                           **
 ** Return parameter    : Dem_ReturnClearDTCType                              **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* polyspace +1 MISRA-C3:2.7 [Justified:Low] "Not a defect" */
static FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_EvMem_ClearSingleDTC(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin)
{
  Dem_ReturnClearDTCType retVal = DEM_CLEAR_FAILED; 

  Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(EventId);
  if (NULL_PTR != cbDTC)
  {
    Dem_EvClearProcState(EventId,DEM_EVPROCSTATE_EVENT_DEL);
    if (E_OK == Dem_ClearSingleDTCStatusByte(cbDTC))
    {
      retVal = DEM_CLEAR_OK;          
    }
  }
  
  return retVal;
}


/******************************************************************************
* Function Name        : Dem_EvMem_TriggerWriteAllBlocks
*
* Service ID           : None
*
* Description          : Triggers the operation for wirting the nv blocks
*
* Sync/Async           : synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : None
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_TriggerWriteAllBlocks(void)
{
  Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
}



/******************************************************************************
* Function Name        : Dem_EvMem_RequestWriteAllBlocks
*
* Service ID           : None
*
* Description          : Triggers the operation for wirting the nv blocks
*
* Sync/Async           : synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : None
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_RequestWriteAllBlocks(void)
{
  Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
  Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_TRUE);
  Dem_EvMem_SetWriteNvDataEndModeTrigger(DEM_JOB_TRIGGER);

  #ifndef NVM_GPT_CHANNEL_ID
  (void)SchM_Trigger_Dem_ReleasedTrigger_ToNvM();
  #endif
}


/******************************************************************************
* Function Name        : Dem_EvMem_RequestReadAllBlocks
*
* Service ID           : None
*
* Description          : Triggers the operation for reading the nv blocks
*
* Sync/Async           : Asynchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : None
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_RequestReadAllBlocks(void)
{
  Dem_EvMem_SetReadNvDataTrigger(DEM_TRUE);
}

/******************************************************************************
* Function Name        : Dem_EvMem_PreInit
*
* Service ID           : None
*
* Description          : init the variables for nv data
*
* Sync/Async           : synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : void
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_PreInit(void)
{
  /* Dem_NonVolatileDataState,Dem_EventMemoryState
   * are cleared as 0(zero) by 'VAR CLEARED SECTION' */
   
  Dem_EvMem_SetNvmResult(E_OK);
  Dem_EvMem_SetReadNvDataTrigger(DEM_FALSE);
  Dem_EvMem_SetWriteNvDataTrigger(DEM_FALSE);
  Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_FALSE); 
  Dem_EvMem_SetWriteNvDataEndModeTrigger(DEM_JOB_DONE); 

  Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_READY;
  Dem_ClearDtcState.cds_DTC = DEM_NO_DTC;      
  Dem_ClearDtcState.cds_DTCFormat = 0u;
  Dem_ClearDtcState.cds_DTCOrigin = 0U;
  Dem_ClearDtcState.cds_Result = DEM_CLEAR_FAILED;
  Dem_ClearDtcState.cds_EventIdRef = DEM_NO_EVENT;
  Dem_ClearDtcState.cds_RequestCancel = DEM_FALSE; 
  Dem_ClearDtcState.cds_User = DEM_CLEARDTC_STATE_USER_IDLE;
}

/******************************************************************************
* Function Name        : Dem_EvMem_ReadAll
*
* Service ID           : None
*
* Description          : read nv data from flash memory or eep rom
*
* Sync/Async           : Asynchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : Filter
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
static FUNC(boolean, DEM_CODE) Dem_EvMem_ReadAll(const uint8 Filter)
{
  boolean pending = DEM_FALSE;
  NvM_BlockIdType blockId = 0U;
  /* NvM_RequestResultType nvDataResult; */
  Dem_NumOfEventMemoryEntryType memLoc = 0U;
  Dem_EventMemoryEntryPtrType memEntry;
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr;
  uint8 idx;

  /* [@IF_REQ x 100, NOTE, @IF_REQ]
   * EventMemory[Num primary entry + num secondary entry...]
   * Regardles of DTCOrigin, only shall use MemLocation 
   */
  for (idx = 0U; idx < Dem_NumOfSupportedDTCOrigins; idx++)
  {
    Dem_DTCOriginType dtcOrigin = Dem_SupportedDTCOrigins[idx];
    for (memLoc = 0U; memLoc <  Dem_SizeOfEventMemory[dtcOrigin]; memLoc++)  
    { 
      if (DEM_TRUE == Dem_EvMem_IsEvMemNvBlockStatusFilter(dtcOrigin, memLoc, Filter))
      {
        memEntry = Dem_EvMem_GetEmEntryByMemPosition(dtcOrigin, memLoc);
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */
        if (NULL_PTR != memEntry)
        {  
          if (E_OK == Dem_NvData_GetNvMBlockId(DEM_NVDATA_EVENT_MEMORY_ID, dtcOrigin, memLoc, &blockId))
          {
            #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
            if(dtcOrigin == DEM_DTC_ORIGIN_PERMANENT_MEMORY)
            {
              NvM_DstPtr = &Dem_PerDtcState[memLoc];
            }
            else
            #endif
            {
              NvM_DstPtr = memEntry;
            }
              
            if (E_OK != NvM_ReadBlock(blockId, NvM_DstPtr))
            {
              /* if NvM is busy state, NvM_ReadBlock shall be called on next mainfunction */      
              pending = DEM_TRUE;
            }
            else
            { 
              Dem_EvMem_ClearEvMemNvBlockStatus(dtcOrigin, memLoc, Filter); 
              /* In case of ReadAll, Dem shall wait until nvm is completed */
              Dem_EvMem_SetEvMemNvBlockStatus(dtcOrigin, memLoc, DEM_EVMEM_STATUS_QUEUED_NVM); 
            }
          }
          /* No NvM Block is congigured */
          else
          /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to true. Avoid the runtime error of the polyspace */        
          {
            Dem_EvMem_ClearEvMemNvBlockStatus(dtcOrigin, memLoc, Filter); 
          }   
        }
        else
        /* polyspace<RTE:UNR:Not a defect:No action planned> Above If-condition always evaluates to true. Avoid the runtime error of the polyspace */        
        {
          Dem_EvMem_ClearEvMemNvBlockStatus(dtcOrigin, memLoc, Filter); 
        }        
      }
    }
  }

  for (idx = 0U; idx < Dem_NumOfSupportedSingleNvBlocks; idx++)
  {
    Dem_NvDataIdType dataId = Dem_DataIdOfSingleNvBlocks[idx];    
    if (DEM_TRUE == Dem_EvMem_NonVolatieDataStatusFilter(dataId, Filter))
    {
      Std_ReturnType result = Dem_NvData_ReadNonVolatileData(dataId);
      switch(result) {
      case E_OK:
        Dem_EvMem_ClearNonVolatieDataStatus(dataId, Filter);
        /* In case of ReadAll, Dem shall wait until nvm is completed */
        Dem_EvMem_SetNonVolatieDataStatus(dataId, DEM_EVMEM_STATUS_QUEUED_NVM); 
        break;
      case DEM_E_PENDING:        
        pending = DEM_TRUE;
        break;
      default:/* No NvM Block is congigured */      
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */      
        Dem_EvMem_ClearNonVolatieDataStatus(dataId, Filter);
        break;
      }
    }  
  }

  /* Read All event status */
  return pending;
}


/******************************************************************************
* Function Name        : Dem_EvMem_WriteAll
*
* Service ID           : None
*
* Description          : write nv data to flash memory or eep rom
*
* Sync/Async           : Asynchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : Filter
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : boolean
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
static FUNC(boolean, DEM_CODE) Dem_EvMem_WriteAll(
  const uint8 Filter)
{
  boolean pending = DEM_FALSE;
  Dem_NumOfEventMemoryEntryType memLoc = 0U;
  Dem_EventMemoryEntryPtrType memEntry;
  P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr;
  
  /* [@IF_REQ x 100, NOTE, @IF_REQ]
   * EventMemory[Num primary entry + num secondary entry...]
   * Regardles of DTCOrigin, only shall use MemLocation 
   */
  uint8 idx;
  for (idx = 0U; idx < Dem_NumOfSupportedDTCOrigins; idx++)
  {
    Dem_DTCOriginType dtcOrigin = Dem_SupportedDTCOrigins[idx];
    for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[dtcOrigin]; memLoc++) 
    {
      if (DEM_TRUE == Dem_EvMem_IsEvMemNvBlockStatusFilter(dtcOrigin, memLoc, Filter))
      {
        NvM_BlockIdType blockId = 0U;      
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */        
        if (E_OK == Dem_NvData_GetNvMBlockId (DEM_NVDATA_EVENT_MEMORY_ID, dtcOrigin, memLoc, &blockId))
        {
          NvM_RequestResultType nvResult = NVM_REQ_PENDING;
          if (E_OK == NvM_GetErrorStatus(blockId, &nvResult))
          {
            if (NVM_REQ_PENDING != nvResult)
            {
              #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
              if(dtcOrigin == DEM_DTC_ORIGIN_PERMANENT_MEMORY)
              {
                NvM_SrcPtr = &Dem_PerDtcState[memLoc];
              }
              else
              #endif
              {
                memEntry = Dem_EvMem_GetEmEntryByMemPosition(dtcOrigin, memLoc);
                NvM_SrcPtr = memEntry;
              }
              if (E_OK != NvM_WriteBlock(blockId, NvM_SrcPtr))
              {
                pending = DEM_TRUE;
              }
              else
              {
                Dem_EvMem_ClearEvMemNvBlockStatus(dtcOrigin, memLoc, Filter);
                if (DEM_TRUE == Dem_NvmWaitFinishJobIsTrigger())
                {            
                  Dem_EvMem_SetEvMemNvBlockStatus(dtcOrigin, memLoc, DEM_EVMEM_STATUS_QUEUED_NVM); 
                }
              }
            }
            else
            {
              pending = DEM_TRUE;            
            }            
          }
          /* Unknown state */
          else
          {
            Dem_EvMem_ClearEvMemNvBlockStatus(dtcOrigin, memLoc, Filter);
          }
        }
        /* No NvM Block is congigured */
        else
        {
          Dem_EvMem_ClearEvMemNvBlockStatus(dtcOrigin, memLoc, Filter);
        }
      }
    }
  }

  for (idx = 0U; idx < Dem_NumOfSupportedSingleNvBlocks; idx++)
  {
    Dem_NvDataIdType dataId = Dem_DataIdOfSingleNvBlocks[idx]; 
    if (DEM_TRUE == Dem_EvMem_NonVolatieDataStatusFilter(dataId, Filter))
    {
      Std_ReturnType result = Dem_NvData_WriteNonVolatileData(dataId);
      switch(result) {
      case E_OK:
        Dem_EvMem_ClearNonVolatieDataStatus(dataId, Filter);
        if (DEM_TRUE == Dem_NvmWaitFinishJobIsTrigger())
        {      
          Dem_EvMem_SetNonVolatieDataStatus(dataId, DEM_EVMEM_STATUS_QUEUED_NVM);
        }
        break;
      case DEM_E_PENDING:        
        pending = DEM_TRUE;
        break;
      default:/* No NvM Block is congigured */      
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */      
        Dem_EvMem_ClearNonVolatieDataStatus(dataId, Filter);
        break;
      }      
    }  
  }


  return pending;
}

/******************************************************************************
* Function Name        : Dem_EvMem_MainFunctionClearDtc
*
* Service ID           : None
*
* Description          : periodic task to clear DTC
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant
*
* Input Parameters     : None
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : void
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_MainFunctionClearDtc(void)
{
  Dem_ReturnClearDTCType result = DEM_CLEAR_FAILED;

  if (DEM_TRUE == Dem_ClearDtcState.cds_RequestCancel)
  {
    if (
     (DEM_CLEARDTC_STATE_PREPARE_CLEARDTC == Dem_ClearDtcState.cds_State) ||
     (DEM_CLEARDTC_STATE_RUNNING == Dem_ClearDtcState.cds_State)     
     /*||
     (DEM_CLEARDTC_STATE_WAIT == Dem_ClearDtcState.cds_State) ||
     (DEM_CLEARDTC_STATE_RESULT == Dem_ClearDtcState.cds_State)
     */)
    {
      Dem_EventIdType tmpEvId;

      for (tmpEvId = 1U; tmpEvId <= Dem_Number_Of_Events; tmpEvId++)        
      {
        Dem_EvClearProcState(tmpEvId, DEM_EVPROCSTATE_INITMON_ONCLEARDTC);         
      }
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();      
      Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_READY;
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();       
      Dem_ClearDtcState.cds_Result = DEM_CLEAR_FAILED;
      Dem_ClearDtcState.cds_RequestCancel = DEM_FALSE;      
    }
    /* If cds_RequestCancel is set to true , Dem_ClearDTC will be called by Dcm anymore.
     * So Dem-self shall stop the clearing processs */
    else if (DEM_CLEARDTC_STATE_RESULT == Dem_ClearDtcState.cds_State)
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();      
      Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_AFTER_CLEAROK;
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION(); 
    }
    else /* DEM_CLEARDTC_STATE_WAIT or DEM_CLEARDTC_STATE_CLEAR_EVMEM */
    {
    }       
  }
  /* [Relationship of state and RequestCancel]
   *+-+---------------+---------------+---------------+---------------+
   *| |    State      | ReqeustCancel |   behavior    |   next state  |
   *+-+---------------+---------------+---------------+---------------+
   *|1|   ready       |      1        |    N/A        |    N/A        |
   *+-+---------------+---------------+---------------+---------------+  
   *|2|   running     |      1        |    cancel     |    ready      |
   *+-+---------------+---------------+---------------+---------------+
   *|3|   wait        |      1        |    wait NvM   |    result     |
   *+-+---------------+---------------+---------------+---------------+
   *|4|   result      |      1        |    normal     |  after ok     |
   *+-+---------------+---------------+---------------+---------------+
   *|5|   after ok    |      1        |    normal     |    ready      |
   *+-+---------------+---------------+---------------+---------------+
   *|                   Normal process                                |
   *+-+---------------+---------------+---------------+---------------+
   *|1|   ready       |      0        |    N/A        |    N/A        |
   *+-+---------------+---------------+---------------+---------------+  
   *|2|   running     |      0        |    clearDTC   |    wait       |
   *+-+---------------+---------------+---------------+---------------+
   *|3|   wait        |      0        |    wait NvM   |    result     |
   *+-+---------------+---------------+---------------+---------------+
   *|4|   result      |      0        |    N/A        |    N/A        |
   *+-+---------------+---------------+---------------+---------------+
   *|5|   after ok    |      0        | call init mon |    ready      |
   *+-+---------------+---------------+---------------+---------------+ */
  if (DEM_CLEARDTC_STATE_READY != Dem_ClearDtcState.cds_State)
  { 
    switch (Dem_ClearDtcState.cds_State)
    {
      case DEM_CLEARDTC_STATE_PREPARE_CLEARDTC:
        if (DEM_FALSE == Dem_OperationCycleTrigger)
        {
          boolean locked = DEM_FALSE;
          Dem_EventIdType eventId;
          for (eventId = 1U; eventId <= Dem_Number_Of_Events; eventId++)       
          {
            if (DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_EVENT_LOCK))
            {
              locked = DEM_TRUE;
              break;
            }
          }
                    
          if (DEM_FALSE == locked)
          {
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_RUNNING;
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
        }
        break;
        
      case DEM_CLEARDTC_STATE_RUNNING:
        if ((DEM_DTC_ORIGIN_PRIMARY_MEMORY ==  Dem_ClearDtcState.cds_DTCOrigin)
          #if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC > 0U)          
          || (DEM_DTC_ORIGIN_SECONDARY_MEMORY ==  Dem_ClearDtcState.cds_DTCOrigin)
          #endif 
        )
        {
          /* Clear Group DTC : if cds_EventIdRef is null , then Dcm will clear All dtcs or group of dtc  */
          if (DEM_NO_EVENT == Dem_ClearDtcState.cds_EventIdRef)
          {
            if (DEM_DTC_GROUP_ALL_DTCS == Dem_ClearDtcState.cds_DTC)
            {        
              result = Dem_EvMem_ClearDTCOfAllGroup(Dem_ClearDtcState.cds_DTCFormat, 
                                                    Dem_ClearDtcState.cds_DTCOrigin
                                                    #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
                                                    , Dem_ClearDtcState.cds_DTCTypeFilter
                                                    #endif
                                                    );
            }                 
            else if (DEM_DTC_GROUP_EMISSION_REL_DTCS == Dem_ClearDtcState.cds_DTC)
            {
              #if (DEM_OBD_SUPPORT == STD_ON)
/*              @IF_REQ OBD is not implemented yet!!!!
              clear all dtc (evnet kind :DEM_DTC_KIND_EMISSION_REL_DTCS)
*/
              result = Dem_EvMem_ClearDTCOfAllGroup(Dem_ClearDtcState.cds_DTCFormat, 
                                                    Dem_ClearDtcState.cds_DTCOrigin
                                                    #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
                                                    , Dem_ClearDtcState.cds_DTCTypeFilter
                                                    #endif
                                                    );
              #else
              result = DEM_CLEAR_WRONG_DTC;
              #endif
            }
            else
            {
              result = Dem_EvMem_ClearDTCOfDTCGroup((Dem_DTCGroupType)Dem_ClearDtcState.cds_DTC,
                                                    Dem_ClearDtcState.cds_DTCFormat, 
                                                    Dem_ClearDtcState.cds_DTCOrigin);
            }
          }
          /* Clear a single DTC */
          else
          {   
            result = Dem_EvMem_ClearSingleDTC(Dem_ClearDtcState.cds_EventIdRef,
                                              Dem_ClearDtcState.cds_DTCOrigin);
          }
          /* checks whether at least one event is dirty or not */
          if (DEM_CLEAR_OK == result)
          {
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_CLEAR_EVMEM;
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
          else
          {
            Dem_ClearDtcState.cds_Result = result;
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();          
            Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_RESULT;
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }   
        }
        break;

      case DEM_CLEARDTC_STATE_CLEAR_EVMEM:

        if (DEM_DTC_GROUP_ALL_DTCS == Dem_ClearDtcState.cds_DTC)
        {
          Dem_EvMem_ClearEvMemEntriesByClearDTC(Dem_ClearDtcState.cds_DTCOrigin, DEM_FALSE);
      
          #if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
          if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == Dem_ClearDtcState.cds_DTCOrigin)
          {    
            /* ISO-14229,160p:
             * first/most recent failed/comfirmed DTC information shall be cleared 
             * upon a successful ClearDiagnosticInformation request from the client */       
            if (DEM_TRUE == Dem_EvMem_ClearDTCOccurrenceTime(0U, DEM_TRUE))
            {
              Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_CLEARDTC);            
            }   
          }
          #endif
            
          /* Dem399: 
          The event memory overflow indication of the respective event memory 
          shall be reset, if all DTCs of this memory are deleted by Dem_ClearDTC*/
          if (DEM_TRUE == Dem_EvMem_SetEvMemOverflowFlag(Dem_ClearDtcState.cds_DTCOrigin, DEM_FALSE))
          {
            Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_CLEARDTC);
          }
        }
        else
        {
          Dem_EvMem_ClearEvMemEntriesByClearDTC(Dem_ClearDtcState.cds_DTCOrigin, DEM_TRUE);
        } 

        #if (DEM_CLEAR_DTC_BEHAVIOUR == DEM_CLRRESP_NONVOLATILE_FINISH)
        Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
        Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_TRUE);
        #elif (DEM_CLEAR_DTC_BEHAVIOUR == DEM_CLRRESP_NONVOLATILE_TRIGGER)
        Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
        #else
        /* Do nothing */
        #endif    

        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        #if (DEM_EVENT_CLEAR_SUPPORT == STD_ON)

        Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_RESET_EVENTS;
     
        #else
        Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_WAIT;

        #endif
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION(); 
        break;   

        #if (DEM_EVENT_CLEAR_SUPPORT == STD_ON)
        case DEM_CLEARDTC_STATE_RESET_EVENTS:
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();          
        Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_WAIT;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        
        Dem_EvMem_ClearEventStatusByte();
           
        break;
        #endif
         
      case DEM_CLEARDTC_STATE_WAIT:
        if (DEM_FALSE == Dem_EvMem_WaitClearAllBlocks(&result))
        {
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_RESULT;
          Dem_ClearDtcState.cds_Result = result;
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        }
        break;

      /* After Dem_ClearDTC returns any value to Dcm */
      case DEM_CLEARDTC_STATE_AFTER_CLEAROK: /* last state! */       
      /* [SWS_Dem_00573] 
       * The Dem module shall provide the configuration parameter 
       * DemTriggerMonitorInitBeforeClearOk (refer to DemGeneral) to con?gure, if the
       * callback function InitMonitorForEvent (refer to section 7.2) has to be called be-
       * fore or after Dem_<...>ClearDTC returns DEM_CLEAR_OK. c(SRS_Diag_04065, SRS_Diag_04122) */    
        #if (DEM_TRIGGER_INIT_BEFORE_CLEAR_OK == STD_OFF)    
        if (DEM_CLEAR_OK == Dem_ClearDtcState.cds_Result)
        {
          Dem_EventIdType tmpEvId;
          Dem_EventParameterPCType event;
          for (tmpEvId = 1U; tmpEvId <= Dem_Number_Of_Events; tmpEvId++)              
          {
            if (DEM_TRUE == Dem_EvIsProcStateTriggered(tmpEvId, DEM_EVPROCSTATE_INITMON_ONCLEARDTC))
            {
              Dem_EvClearProcState(tmpEvId, DEM_EVPROCSTATE_INITMON_ONCLEARDTC);
              event = &Dem_Event[tmpEvId-1U];

              #if (DEM_NUMBER_OF_EVENT_CALLBACK > 0)
              if((event->e_PointToEventCallbackData < (Dem_EventIdType)DEM_NUMBER_OF_EVENT_CALLBACK) &&
                 (Dem_EventCallback[event->e_PointToEventCallbackData].pDemInitMonitorForEvent != NULL_PTR))
              {
                /* polyspace<RTE:COR:Not a defect:No action planned> Polyspace bug */
                Dem_EventCallback[event->e_PointToEventCallbackData].pDemInitMonitorForEvent
                  ((Dem_InitMonitorReasonType)DEM_INIT_MONITOR_CLEAR);
              }
              #endif
            }
          }
        }
        else
        {
          Dem_EventIdType tmpEvId;
          for (tmpEvId = 1U; tmpEvId <= Dem_Number_Of_Events; tmpEvId++)
          {
            Dem_EvClearProcState(tmpEvId, DEM_EVPROCSTATE_INITMON_ONCLEARDTC);         
          }
        }
        #endif
        
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        Dem_ClearDtcState.cds_State = DEM_CLEARDTC_STATE_READY;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

        Dem_ClearDtcState.cds_RequestCancel = DEM_FALSE; 

        /* @IF_REQ: Add one more phase => case XXX: */
        #if (DEM_J1939_SUPPORT == STD_ON) 
        Dem_EvMem_InitChronologicalOrder(Dem_ClearDtcState.cds_DTCOrigin);  
        #endif

        #if (DEM_OBD_SUPPORT == STD_ON)   
        #ifdef DEM_MIL_INDICATORID
        Dem_SetMalfuntionOnOff();
        #endif
        if(DEM_BIT7_MASK1 != Dem_GetMalfuntionOnOff()) 
        {

          Dem_ClearObdInfomation();
        }        
        #endif
        
        break;

      /* case DEM_CLEARDTC_STATE_RESULT: 
       *  Nothing to do while Dem_ClearDTC returns result */
      default: 
        /* Do Nothing */
        break;
    }
  }
}

/*******************************************************************************
 * Function Name        : Dem_EvMem_MainFunctionReadAll
 *
 * Service ID           : None
 *
 * Description          : Read all NvData
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : None
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : None
 *
 * Preconditions        : None
 *
 * Remarks              :
 ******************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_MainFunctionReadAll(void)
{  
  /* Sequence : 
   * [1] NvM_ReadBlock
   * [2] Wait until NvM's Job is finished*/  
  if (DEM_TRUE == Dem_EvMem_ReadNvDataIsTriggered())
  { 
    /* Is pending(TRUE: pending)*/  
    if (DEM_FALSE == Dem_EvMem_ReadAll(DEM_EVMEM_STATUS_INVALID))
    {  
      Dem_EvMem_SetReadNvDataTrigger(DEM_FALSE); 
      
      /* Trigger FinishJob after NvM_ReadBlock */
      Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_TRUE);
      #ifndef NVM_GPT_CHANNEL_ID
      (void)SchM_Trigger_Dem_ReleasedTrigger_ToNvM();
      #endif
    }
  }
  else
  {
    /* Wait the result of NvM after NvM_ReadBlock call */
    if (DEM_TRUE == Dem_NvmWaitFinishJobIsTrigger())
    {
      /* Is pending(TRUE: pending)*/      
      if (DEM_FALSE == Dem_NvData_WaitNvmFinishJob(DEM_EVMEM_STATUS_QUEUED_NVM, DEM_NVM_READ))
      {
        Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_FALSE);
        
        /* After BsM accept the DEM_BSWMMODE_DEM_INIT_FINISH,
         * Dem_Init is called by BswM */      
        BswM_RequestMode(DEM_MODULE_ID, DEM_BSWM_MODE_READBLOCK_END);           
      }
    }
  }  
}

/*******************************************************************************
 * Function Name        : Dem_EvMem_MainFunctionWriteAll
 *
 * Service ID           : None
 *
 * Description          : Write all NvData
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : None
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : None
 *
 * Preconditions        : None
 *
 * Remarks              :
 ******************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_MainFunctionWriteAll(void)
{  
  /* Sequence : 
   * [1] NvM_WriteBlock
   * [2] Wait until NvM's Job is finished*/
  if (DEM_TRUE == Dem_EvMem_WriteNvDataIsTriggered())
  {
    /* Is pending(TRUE: pending)*/  
    if (DEM_FALSE == Dem_EvMem_WriteAll(DEM_EVMEM_STATUS_DIRTY|DEM_EVMEM_STATUS_TRIGGER_NVM))
    {
      Dem_EvMem_SetWriteNvDataTrigger(DEM_FALSE); 
    }
  }
  else
  {
    if (DEM_TRUE == Dem_NvmWaitFinishJobIsTrigger())
    {
      /* Is pending(TRUE: pending)*/      
      if (DEM_FALSE == Dem_NvData_WaitNvmFinishJob(DEM_EVMEM_STATUS_QUEUED_NVM|DEM_EVMEM_STATUS_FINISH_NVM, DEM_NVM_WRITE))
      {      
        Dem_EvMem_SetWaitNvmFinishJobTrigger(DEM_FALSE);
        if (DEM_JOB_TRIGGER == Dem_EvMem_WriteNvDataEndModeTriggered())
        {
          Dem_EvMem_SetWriteNvDataEndModeTrigger(DEM_JOB_RUNNING);
        }
      }
    }
    else if (DEM_JOB_RUNNING == Dem_EvMem_WriteNvDataEndModeTriggered())
    {
      Dem_EvMem_SetWriteNvDataEndModeTrigger(DEM_JOB_DONE);
      BswM_RequestMode(DEM_MODULE_ID, DEM_BSWM_MODE_WRITEBLOCK_END);        
    }
    else
    {
      /* Do nothing */
    }
  }
}


/*******************************************************************************
 * Function Name        : Dem_EvMem_AgingEvMemEntry
 *
 * Service ID           : None
 *
 * Description          : Process aging for stored event to remove it from
 *                        event memory
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
 * Preconditions        : None
 *
 * Remarks              :
 ******************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_AgingEvMemEntry(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin,  
  Dem_EventMemoryEntryPtrType EvMemEntry)
{ 
  #if(DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_TYPE1)  
  Dem_CombinedDtcPCType cbDTC;
  #endif    

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();

  #if (DEM_J1939_SUPPORT == STD_ON) 
  Dem_EvMem_DelChronologicalOrder(DTCOrigin, Dem_EvMemToEventMap[EventId]);
  #endif
  

  /* @IF_REQ : Checking whether critical section is needed or not when event is removed from memory */
  /* Delete event memory entry  */
  #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)  
  Dem_EvMem_ClearMemLocInEvMemMap(EventId, DTCOrigin, EvMemEntry);          
  #else
  Dem_EvMem_ClearMemLocInEvMemMap(EventId, DTCOrigin);
  #endif

  Dem_EvMem_SetEventId(EvMemEntry, DEM_NO_EVENT);
  
  SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();  
  
  Dem_EvMem_ClearEventMemoryEntry(EvMemEntry);

  #if(DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_TYPE1)  
  /* [SWS_Dem_00442] 
   * If a combined DTC (combination on storage) is aged,
   * the Dem module shall remove this event memory entry and reset the status
   * bytes of all sub-events according to [SWS_Dem_00823], [SWS_Dem_00824] and
   * [SWS_Dem_00498]. */
  cbDTC = Dem_GetCbDTCByEventId(EventId);
  if (NULL_PTR != cbDTC)
  #endif  
  {
    #if(DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_TYPE1)
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Because ddNumberOfEvents can be configured by user , 
       this condition maybe awlays evaluate to false. No impact" */
    if (cbDTC->ddNumberOfEvents > 1U)
    {
      Dem_NumOfEventIdType startPos = Dem_GetStartEventIdMapOfCbDTC(cbDTC);
      const Dem_NumOfEventIdType endPos = Dem_GetEndEventIdMapOfCbDTC(cbDTC);                
      for (;startPos < endPos; startPos++)       
      {    
        Dem_EventIdType evId = Dem_ListOfCombinedEvents[startPos];

        /* Aging */
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        #if(DEM_STATUS_BIT_HANDLING_TFSLC == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
        /* TestFailedSinceLastClear bit5 = 0 , ConfirmedDTC bit = 0*/
        DEM_CLR_UDSSTATUSBYTE(evId, DEM_UDS_STATUS_TFSLC | DEM_UDS_STATUS_CDTC);
        #else
        DEM_CLR_UDSSTATUSBYTE(evId, DEM_UDS_STATUS_CDTC);      
        #endif
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        
        Dem_EvMem_SetUdsStatusByteToNvData(evId);
       /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Because ddNumberOfEvents can be configured by user , 
          this condition maybe awlays evaluate to false. No impact" */
      }
    }
    else
    #endif
    {    
      /* Aging */
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();    
      #if(DEM_STATUS_BIT_HANDLING_TFSLC == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
      /* TestFailedSinceLastClear bit5 = 0 , ConfirmedDTC bit = 0*/      
      DEM_CLR_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_TFSLC | DEM_UDS_STATUS_CDTC);
      #else
      DEM_CLR_UDSSTATUSBYTE(EventId, DEM_UDS_STATUS_CDTC);
      #endif
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

      /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "Not a defect" */
      Dem_EvMem_SetUdsStatusByteToNvData(EventId);
    }
  } 
}

/******************************************************************************
* Function Name        : Dem_EvMem_FindNewTimeStamp
*
* Service ID           : None
*
* Description          : Find the new time stamp to store it in new entry
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant(Not DTCOrigin)
*
* Input Parameters     : DTCOrigin
*                        
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : uint32
*
* Preconditions        : None
*
* Remarks              : 
*
*****************************************************************************/
#if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
FUNC(uint32, DEM_CODE) Dem_EvMem_FindNewTimeStamp(Dem_DTCOriginType DTCOrigin)
{
 /* Dem_EventMemoryEntryPtrType memEntry = NULL_PTR; */
  /* uint8 Dem_TimeStampSortingTable[255]; */

  /* Dem_NumOfEventMemoryEntryType memLoc = 0U;        */
  uint32 newTimeStamp = Dem_MaxTimeStamp[DTCOrigin];
 #if 0  
  uint32 curTimeStamp = 0U;

  for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[DTCOrigin]; memLoc++)
  {
    memEntry = Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, memLoc);    
    if (NULL_PTR != memEntry)
    {
      Dem_EventIdType evId = Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin, memLoc);
      if (DEM_TRUE == Dem_EventIdIsValid(evId))
      {
        curTimeStamp = Dem_EvMem_GetTimeStamp(memEntry);
        if (curTimeStamp > newTimeStamp)
        {
          newTimeStamp = curTimeStamp;
          /*Dem_TimeStampSortingTable[timeOrder] = it - 1U; */
        }
      }  
    }
  }
 #endif
  
  /*
  if (maxTimeStamp >= DEM_MAX_TIMESTAMP)
  { 
    Dem_NumOfEventMemoryEntryType num = Dem_SizeOfEventMemory[DTCOrigin];
    
    Refer to http:/ /embeddedgurus.com/stack-overflow/2009/03/sorting-in-embedded-systems/ 
    void shellsort(long *a, long num)
    { 
      Sedgewick-Incerpi sequence 
      uint32 step[16] = {1, 3, 7, 21, 48, 112, 336, 861, 1968, 4592, 13776, 33936, 86961, 198768, 463792, 1391376}; 
      uint32 i, j, k, s, t; 
      k = 6; (num < 256) ? 6 : 15; 
      do 
      { 
        for (s=step[k], i=s-1; i < num; i++) 
        { 
          t = a[i]; 
          
          for (j=i; j >= s && t > a[j-s]; a[j] = a[j-s], j -= s); 
          a[j] = t; 
        } 
      } while (k?);
    }
  }
  */
  if (newTimeStamp < (DEM_MAX_TIMESTAMP - (uint32)1U)) /* valild maximum valie is 0xFFFFFFFE*/
  {
    newTimeStamp++; 
  }
  else
  {  
    Dem_NumOfEventMemoryEntryType memLoc;        

        
    #if (DEM_J1939_SUPPORT == STD_ON)
    if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
    {     
      if (Dem_NumOfStoredEvtMemEntryies[DTCOrigin] < Dem_SizeOfEventMemory[DTCOrigin])
      {
        Dem_NumOfEventMemoryEntryType numStoredEntry;  

        newTimeStamp = 1U;
        for (numStoredEntry = 0U;  numStoredEntry < Dem_NumOfStoredEvtMemEntryies[DTCOrigin]; numStoredEntry++)
        {   
          memLoc = Dem_PriEvMemChronoOrder[numStoredEntry];
          if (memLoc < Dem_SizeOfEventMemory[DTCOrigin])
          {
            Dem_EventIdType evId = Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin, memLoc);        
            if (DEM_TRUE == Dem_EventIdIsValid(evId))
            {    
              Dem_EventMemoryEntryPtrType memEntry = Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, memLoc);
              Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(evId);        
              /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */        
              if ((NULL_PTR != cbDTC) && (NULL_PTR != memEntry))
              {
                Dem_EvMem_SetTimeStamp(memEntry, newTimeStamp);
                newTimeStamp++;
                Dem_EvMem_SetEvMemNvBlockStatus(DTCOrigin, memLoc, cbDTC->EvMemTriggerFlag);
              }
            }          
          }
        }
      }
    }
    else
    #endif
    {        
      /* @IF_REQ */
      /* Perhaps, almost timeStamp of events will be larage value (0xFFFFXXXX), so
       * these should be initialized*/  
      newTimeStamp = 1U;
      for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[DTCOrigin]; memLoc++)    
      {
        Dem_EventIdType evId = Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin, memLoc);
        if (DEM_TRUE == Dem_EventIdIsValid(evId))
        {    
          Dem_EventMemoryEntryPtrType memEntry = Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, memLoc);
          Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(evId);        
          /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */        
          if ((NULL_PTR != cbDTC) && (NULL_PTR != memEntry))
          {
            Dem_EvMem_SetTimeStamp(memEntry, newTimeStamp);
            newTimeStamp++;
	        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
            Dem_EvMem_SetEvMemNvBlockStatus(DTCOrigin, memLoc, cbDTC->EvMemTriggerFlag);
          }
        }
      }
    }
  } 

  Dem_MaxTimeStamp[DTCOrigin] = newTimeStamp;  
  
  return newTimeStamp;
}
#endif

/******************************************************************************
 * Function Name        : Dem_EvMem_FindEntryWithLowestPriority == 1
 *
 * Service ID           : None
 *
 * Description          : Function is used to find the event that can be      
 *                        displaced                                           
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventBase, DTCOrigin
 *                        
 * InOut parameter      : None
 *
 * Output Parameters    : EntryFound, EventMemoryIndex
 *
 * Return parameter     : Std_ReturnType (E_OK, E_NOT_OK)
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *                        
 *
 *****************************************************************************/
#if(DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON)
FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE) Dem_EvMem_FindEntryWithLowestPriority(
  Dem_EventIdType EventId,
  Dem_EventPriorityType PriorityOfNewEvent,
  Dem_DTCOriginType DTCOrigin)
{
  Dem_NumOfEventMemoryEntryType memLoc;
  boolean Passivefound = DEM_FALSE;
  boolean found;

  struct {
    /* 0 ~255  max number of event memory entries is 255 */  
    Dem_NumOfEventMemoryEntryType loc; 
    uint32 timeStamp;   
    Dem_EventPriorityType prio;
    Dem_EventIdType eventId;
  } LowestEvent;

  LowestEvent.loc = DEM_NO_EVMEM_IDX;
  LowestEvent.timeStamp = DEM_MAX_TIMESTAMP; /* newest time */  
  LowestEvent.prio = 0xFFU; /* lowest priority */
  LowestEvent.eventId = DEM_NO_EVENT;

  /***************************************************************
   * [Dem383] A priority value of 1 shall be the highest priority.
   *  Larger priority value shall define lower importance.
   ***************************************************************/
  for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[DTCOrigin]; memLoc++)    
  {
    Dem_EventIdType evId;

    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION(); 
    evId = Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin, memLoc);
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION(); 
    
    if ((evId <= Dem_Number_Of_Events) && (DEM_NO_EVENT != evId))
    {      
      /* EventId never be DEM_NO_EVENT, because Event memory is full */
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      Dem_EventPriorityType prioOfEvent = Dem_Event[evId-1U].ucEventPriority;

      /* Priority of reported event <= priority of found entries? */
      if (PriorityOfNewEvent <= prioOfEvent)
      {
        found = DEM_FALSE;
  
        /*Passive memory entries found?  Passive status = TestFailed bit is 0 */
        /* Group I : passsive event memory entries */
        if(0U == (Dem_AllEventStatusByte[evId] & (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF))
        {
          if (DEM_FALSE == Passivefound)
          {
            Passivefound = DEM_TRUE;
            LowestEvent.loc = DEM_NO_EVMEM_IDX;
          }
          found = DEM_TRUE;
        }
  
        /* Group II : No passive event ,
         * Priority of reported event < priority of found entries? */
        if (DEM_FALSE == Passivefound)
        {
          if (PriorityOfNewEvent < prioOfEvent)
          {
            found = DEM_TRUE;
          }
        }
  
        if (DEM_TRUE == found)
        {         
          Dem_EventMemoryEntryPtrType evMemEntry = Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, memLoc);
          /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */          
          if (NULL_PTR != evMemEntry)
          {
            uint32 tStamp = Dem_EvMem_GetTimeStamp(evMemEntry);
            /* Displace oldest found entry with reported event */
            if (DEM_NO_EVMEM_IDX == LowestEvent.loc)
            {
              LowestEvent.loc = memLoc;          
              LowestEvent.timeStamp = tStamp; 
              LowestEvent.prio = prioOfEvent;
              LowestEvent.eventId = evId;
            }
            else
            {
              /* if a current event is oldest and lower priority than a previous event  */
              if (prioOfEvent == LowestEvent.prio)
              {             
                /* lower time stamp is oldest event */
                if (tStamp < LowestEvent.timeStamp)
                {
                  LowestEvent.loc = memLoc;            
                  LowestEvent.timeStamp =  tStamp;
                  LowestEvent.prio = prioOfEvent;
                  LowestEvent.eventId = evId;                  
                }
              }
              else if (prioOfEvent > LowestEvent.prio)
              {                              
                LowestEvent.loc = memLoc;            
                LowestEvent.timeStamp =  tStamp;
                LowestEvent.prio = prioOfEvent;
                LowestEvent.eventId = evId;                
              }
              else 
              {
                /* Do nothing */
              }
            }
          }
        }
      }
    }
  }

  /* Found a event to be displaced */
  if (DEM_NO_EVMEM_IDX != LowestEvent.loc)
  {
    Dem_EventIdType eventIdOldest  = LowestEvent.eventId;
    
    Dem_EventMemoryEntryPtrType evMemEntry = Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin,LowestEvent.loc);    
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */      
    if (NULL_PTR != evMemEntry)
    {
      Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(eventIdOldest);
      if (NULL_PTR != cbDTC) /* useless if-condition */
      {
        /* @Dem409 :  Reset the bit3 to zero of the event getting displaced
         * @SWS_Dem_00409: Reset the UDS status bit 2 (PendingDTC) */    
        Dem_UdsStatusByteType MaskToClear = (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC | 
                                            (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC;

        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();      
        /* eventId shall be rechecked because of the preemption problem */
        if (Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin,LowestEvent.loc) == eventIdOldest)
        {
          Dem_EvInitProcState(eventIdOldest);  

          /*Set to new event id for locking an event memory entry. */
          Dem_EvMem_SetEventId(evMemEntry, EventId); 
          
          #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)  
          Dem_EvMem_ClearMemLocInEvMemMap(eventIdOldest, DTCOrigin, evMemEntry);          
          #else
          Dem_EvMem_ClearMemLocInEvMemMap(eventIdOldest, DTCOrigin);
          #endif 
          
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

          #if (DEM_J1939_SUPPORT == STD_ON) 
          Dem_EvMem_DelChronologicalOrder(DTCOrigin, LowestEvent.loc);
          #endif

          /* Dem784_Conf : the "TestFailedSinceLastClear" status bits are reset to 0 */
          #if(DEM_STATUS_BIT_HANDLING_TFSLC == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
          MaskToClear |= DEM_UDS_STATUS_TFSLC;
          #endif  

          /* [SWS_Dem_00443] 
           * If a combined DTC (combination on storage) is displaced,
           * the Dem module shall remove this event memory entry and reset the status
           * bytes of all sub-events according to [SWS_Dem_00409] and [SWS_Dem_01186] */ 
          #if(DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_TYPE1)      
          Dem_NumOfEventIdType startPos = Dem_GetStartEventIdMapOfCbDTC(cbDTC);
          const Dem_NumOfEventIdType endPos = Dem_GetEndEventIdMapOfCbDTC(cbDTC);        
          while (startPos < endPos)
          {
            Dem_EventIdType tmpEvId = Dem_ListOfCombinedEvents[startPos];    
            DEM_CLR_UDSSTATUSBYTE(tmpEvId, MaskToClear); 
            
            /* All EventStatus NvRam data shall be initialized */
            Dem_EvMem_SetUdsStatusByteToNvData(tmpEvId);         
            ++startPos;
          }
          #else
          DEM_CLR_UDSSTATUSBYTE(eventIdOldest, MaskToClear);        
          /* All EventStatus NvRam data shall be initialized */        
          Dem_EvMem_SetUdsStatusByteToNvData(eventIdOldest);
          #endif  

          /* EventStatus of removed events shall be updated to NvData */
          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
	      Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, cbDTC->EvMemTriggerFlag);
        }
        else
        {
          LowestEvent.loc = (Dem_NumOfEventMemoryEntryType)DEM_NO_EVENT;
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        }        
      }
    }
  }


  return LowestEvent.loc;
}
#endif

/* http:/ /stackoverflow.com/questions/25661925/quickly-find-whether-a-value-is-present-in-a-c-array 
bool check(uint32_t theArray[], uint32_t compareVal)
{
    uint32_t i;
    uint32_t x = theArray[SIZE-1];
    if (x == compareVal)
        return true;
    theArray[SIZE-1] = compareVal;
    for (i = 0; theArray[i] != compareVal; i++);
    theArray[SIZE-1] = x;
    return i != SIZE-1;
}
*/


/******************************************************************************
 * Function Name        : Dem_EvMem_VerifyAllEventMemories
 *
 * Service ID           : None
 *
 * Description          : Puts the default initial values into
 *                        non-volatile data
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
 * Return parameter     : None
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_VerifyAllEventMemories(void)
{
  uint8 idx_u8;
  uint8 clearType;
  Dem_EventIdType eventId;
  boolean NvmBlocksVirgin = DEM_TRUE;
  #if((0U != DEM_NVM_BLK_ID_EVENT_STATUS)  || (0 != DEM_NVM_BLK_ID_NON_VOLATILE_DATA))
  NvM_RequestResultType result;
  #endif

  /* Checks magic key */
  if (NVM_REQ_OK == Dem_NvData_GetNvMErrorStatus(Dem_NonVolatileDataBlkId))
  { 
    if (DEM_TRUE == Dem_EvMem_CheckFirstEcuRun()) 
    {
      NvmBlocksVirgin = DEM_FALSE;
    }
  }  
  if (DEM_TRUE == NvmBlocksVirgin)
  {
    Dem_EvMem_ResetManagementBlock(DEM_TRUE);
    #if (0U != DEM_NVM_BLK_ID_NON_VOLATILE_DATA)
    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_GENERIC_NVRAM_DATA_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);   
    #endif
  }
  

  /* Checks  the Event Status Block */
  clearType = DEM_NVBLOCK_INVALID;
  #if (0U != DEM_NVM_BLK_ID_EVENT_STATUS)
  result =  Dem_NvData_GetNvMErrorStatus(Dem_EventStatusNvRamBlkId);
  if (NVM_REQ_NV_INVALIDATED != result) /* It does not matter to #3260 */
  { 
    if ((DEM_FALSE == NvmBlocksVirgin) && ((NVM_REQ_OK == result)
      #if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)      
      || (NVM_REQ_BLOCK_SKIPPED == result)
      #endif
    ))
    {
      clearType = DEM_NVBLOCK_SUCCESS;  
    }
    else
    {
      /* If AllNvBlocksReset is TRUE and result of the block is not NVM_REQ_NV_INVALIDATED
        * it is not possible to determine whether a value of NvRam Block is valid */
      clearType = DEM_NVBLOCK_FAILED;
    }
  }
  #endif
  if (DEM_NVBLOCK_SUCCESS != clearType)
  {
    if (DEM_NVBLOCK_FAILED == clearType)
    {
      Dem_EvMem_ResetEventStatusNvRamBlock();      
      Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM);      
      Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE);
    }
    else /* DEM_NVBLOCK_INVALID */
    {
      Dem_EvMem_ResetEventStatusNvRamBlock();       
    }
  }

  for (eventId = 0U; eventId <= Dem_Number_Of_Events; eventId++) 
  {
   Dem_EvMemToEventMap[eventId] = DEM_NO_EVMEM_ENTRY; /* 0xFF */
  }
  /* Checks the Event Memory Entry Block */
  for (idx_u8 = 0U; idx_u8 < Dem_NumOfSupportedDTCOrigins; idx_u8++)
  {
    NvM_BlockIdType blockId;
    Dem_NumOfEventMemoryEntryType memLoc;
    Dem_DTCOriginType dtcOrigin = Dem_SupportedDTCOrigins[idx_u8];    

    Dem_NumOfStoredEvtMemEntryies[dtcOrigin] = 0;     
    for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[dtcOrigin]; memLoc++)  
    {   
      Dem_EventMemoryEntryPtrType memEntry = Dem_EvMem_GetEmEntryByMemPosition(dtcOrigin, memLoc);      
      eventId = Dem_EvMem_GetEventIdByEvMemEntry(dtcOrigin,memLoc);
      
      clearType = DEM_NVBLOCK_INVALID; /* Clear and Call NvM_WriteBlock */      
      /* polyspace<RTE:UNR:Not a defect:No action planned> Not a defect */  
      if (E_OK == Dem_NvData_GetNvMBlockId (DEM_NVDATA_EVENT_MEMORY_ID, dtcOrigin, memLoc, &blockId))
      {
        NvM_RequestResultType Lucresult = Dem_NvData_GetNvMErrorStatus(blockId);  
        if (NVM_REQ_NV_INVALIDATED != Lucresult) /* It does not matter to #3260 */
        { 
          clearType = DEM_NVBLOCK_FAILED;
          if ((DEM_FALSE == NvmBlocksVirgin) && ((NVM_REQ_OK == Lucresult)
#if defined(DEM_NVBLOCKS_CANBE_SKIPPED_ON_SWRESET)      
            || (NVM_REQ_BLOCK_SKIPPED == Lucresult)
#endif        
          ))
          {            
            /* Is empty? */
            if (0U != eventId) /* starts from 1 */
            {
              if (eventId <= Dem_Number_Of_Events)
              {
                if (DEM_TRUE == Dem_EventHasDtc(eventId))
                {
                  clearType = DEM_NVBLOCK_SUCCESS;
                  DEM_EVMEM_SET_MAX_TIMESTAMP( Dem_EvMem_GetTimeStamp(memEntry), dtcOrigin);            
                  Dem_EvMem_AddMemLocInEvMemMap(eventId, dtcOrigin, memLoc);
                } 
                /* else : failed */
              } 
              /* else : failed */
            }
            else
            {
              clearType = DEM_NVBLOCK_INVALID;
            }
          }
          /* else : failed */
        }
        /* else : invalidated */
      }
      /* else : invalidated */
      
      if (DEM_NVBLOCK_SUCCESS != clearType)
      {
        if (DEM_NVBLOCK_FAILED == clearType)
        {
          Dem_EvMem_ClearEventMemoryEntry(memEntry);
          #if ((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U)) 
          if(DEM_DTC_ORIGIN_PERMANENT_MEMORY == dtcOrigin)
          {
            Dem_EvMem_ClearPermanentMemEntry(memLoc);
          }
          #endif
          Dem_EvMem_SetEvMemNvBlockStatus(dtcOrigin, memLoc, DEM_EVMEM_STATUS_DIRTY_NVM);
          Dem_EvMem_SetWriteNvDataTrigger(DEM_TRUE); 
        }
        else /* DEM_NVBLOCK_INVALID */
        {
          /* If AllNvBlocksReset is TRUE and result of the block is not NVM_REQ_NV_INVALIDATED
           * it is not possible to determine whether a value of NvRam Block is valid */        
          Dem_EvMem_ClearEventMemoryEntry(memEntry); 
          #if ((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U)) 
          if(DEM_DTC_ORIGIN_PERMANENT_MEMORY == dtcOrigin)
          {
            Dem_EvMem_ClearPermanentMemEntry(memLoc);
          }
          #endif
        }
      }
    } 

    #if (DEM_J1939_SUPPORT == STD_ON) 
    Dem_EvMem_InitChronologicalOrder(dtcOrigin);  
    #endif    
  }            
}     

/******************************************************************************
 * Function Name        : Dem_EvMem_Init
 *
 * Service ID           : None
 *
 * Description          : Puts the default initial values into 
 *                        non-volatile data
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
 * Return parameter     : None
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        
 *
 *                        Function(s) invoked :
 *                        DEM_RST_UDSSTATUSBYTE()
 *****************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_Init(void)
{
  Dem_EventIdType eventId;    

  /* If WIR or TFTOC or TF or CDTC or PDTC or TFSLC bit is true 
   +--------------------------------------+-------+
   |Bit                                   |NotUsed|
   +------------------------------------+-+-------+
   | TestFailed                         |0|   0   |
   +------------------------------------+-+-------+
   | TestFailedThisOperationCycle       |1|   0   |
   +------------------------------------+-+-------+
   | PendingDTC                         |2|   0   | if TFTOC is 1, set to 1 on EvMemInit(?)
   +------------------------------------+-+-------+
   | ConfirmedDTC                       |3|   0   |
   +------------------------------------+-+-------+
   | TestNotCompletedSinceLastClear     |4|   1   | set to 1 on EvMemInit
   +------------------------------------+-+-------+
   | TestFailedSinceLastClear           |5|   0   |
   +------------------------------------+-+-------+
   | TestNotCompletedThisOperationCycle |6|   1   | set to 1 on operation cycle changed
   +------------------------------------+-+-------+
   | WarningIndicatorRequested          |7|   0   |
   +------------------------------------+-+-------+*/

  /* Loop through the number of events */
  DEM_RST_UDSSTATUSBYTE(DEM_NO_EVENT, 0U);
  for (eventId = 1U; eventId <= Dem_Number_Of_Events; eventId++) 
  {
    Dem_EventParameterPCType event = &Dem_Event[eventId-1U];
    Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(eventId);
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    Dem_DTCOriginType DTCOrigin = event->aaEventDestination;      
      
    if ((DEM_NO_DTC_ORIGIN != DTCOrigin) && (NULL_PTR != cbDTC))
    {
      boolean dirty = DEM_FALSE;    
      /* Get current EventStatusByte */      
      Dem_UdsStatusByteType EventStatusByteOld;
      Dem_NumOfEventMemoryEntryType memLoc = Dem_EvMemToEventMap[eventId];

      /* Read EventStatusByte from NvData */
      DEM_RST_UDSSTATUSBYTE(eventId, Dem_EvMem_GetUdsStatusByteToNvData(eventId, DTCOrigin));         
      
      /* Get old event status after Dem_EvMem_GetUdsStatusByteToNvData */
      EventStatusByteOld = Dem_AllEventStatusByte[eventId];
      
      /* If event is stored in the event memory */
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      if (memLoc < Dem_SizeOfEventMemory[DTCOrigin]) 
      {    
        uint8 cycleStateOld= DEM_CYCLE_STATE_START;        

        /* if OpCycleStorage is off, OperationCycleState was initialized as 0(START) by 'START CODE'
         * So , if OpCycleState is END(1), it means th OpCycleStorage is on and state is stored.*/
        Dem_EvMem_GetOpCycleState(event->e_OperationCycleId, &cycleStateOld);
        if ((DEM_CYCLE_STATE_END == cycleStateOld) && ((EventStatusByteOld & DEM_BITMASK_RESET_PDTC) == DEM_UDS_STATUS_PDTC))
        {
          DEM_CLR_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_PDTC);          
        }
        else
        {
          /* PedingDTC = 0->1 
           * [1] An event is stored
           * [2] TestFailedThisOperationCycle is true(Event was failed previously)
           * [3] storage  condition is not supported
           *     if it is used, the status of PDTC can not be determined.
           */
          #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
          if (0U == event->ucNumOfStorageCondition)
          #endif
          {
            if (DEM_IS_BIT_UNSET_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_PDTC)) 
            {
              if (DEM_IS_BIT_SET_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_TFTOC))
              {
                DEM_SET_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_PDTC); 
              }    
            }
          }
        }
        
        DEM_CLR_UDSSTATUSBYTE(eventId, (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC); /* Bit 6 */
        DEM_SET_UDSSTATUSBYTE(eventId, (Dem_UdsStatusByteType)DEM_UDS_STATUS_TFSLC);  /* Bit 5 */        
      }
      else
      {
        if (DEM_IS_BIT_SET_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_CDTC)) 
        {
          DEM_RST_UDSSTATUSBYTE(eventId, (DEM_UDS_STATUS_TNCTOC | DEM_UDS_STATUS_TNCSLC));
        }
      }

      /*[Checked]*/
      if (DEM_IS_BIT_SET_UDSSTATUSBYTE(eventId, 
        DEM_UDS_STATUS_TF    | /* Bit 0 */ 
        DEM_UDS_STATUS_TFTOC | /* Bit 1 */         
        DEM_UDS_STATUS_PDTC  | /* Bit 2 */ 
        DEM_UDS_STATUS_CDTC  | /* Bit 3 */ 
        DEM_UDS_STATUS_TFSLC | /* Bit 5 */ 
        DEM_UDS_STATUS_WIR))   /* Bit 7 */ 
      {
        DEM_SET_UDSSTATUSBYTE(eventId,(Dem_UdsStatusByteType)DEM_UDS_STATUS_TFSLC);  /* Bit 5 */
        DEM_CLR_UDSSTATUSBYTE(eventId,(Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC); /* Bit 6 */
      }
      /* @IF_REQ : Apply cbDTC->UdsStatusAvailabilityMask ?  */
      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */      
      else 
      {
        if (0U == (DEM_UDS_STATUS_TNCSLC & Dem_Status_Availability_Mask))
        {
          DEM_SET_UDSSTATUSBYTE(eventId, (Dem_UdsStatusByteType)DEM_UDS_STATUS_TNCSLC);  /* Bit 5 */            
          /* TFSLC is cleared already */
        }
      }     

      /* [Checked] */
      if (DEM_IS_BIT_SET_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_TF)) 
      {
        /* @IF_REQ : [SWS_Dem_00525] 
         * If the configuration parameter DemStatusBitStorageTestFailed is set to True, 
         * the Dem module shall retain the information for UDS DTC status bit 0 (TestFailed) over power cycles
         * Question) power cycle is ECU reset or Operation Cycle(DEM_OPCYC_POWER)? */             
        if (DEM_FALSE == DEM_GET_EVENTPARAM_STORAGE_TF(event->ParamFieldsA))
        {
          DEM_CLR_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_TF);
        }      
      }
      
      /*[Checked]*/
      if (
        (DEM_IS_BIT_SET_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_WIR)) && 
        (DEM_WIR_RESET_ON_OPERATIONCYCLE_START == DEM_GET_EVENTPARAM_RESET_WIR(event->ParamFieldsA)))
      {
        DEM_CLR_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_WIR);
	    /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */
        dirty |= Dem_InitIndicator(eventId);
      }

      /* SWS_Dem_00389 : SWS_Dem_00389 shoul not be applied in the Autron platform
       * to support the vendor specific requirements(aging/healing)
       * and therefore DEM_UDS_STATUS_TFTOC always is non-volatile data
       *
       * NOTE : DEM_UDS_STATUS_TNCTOC,DEM_UDS_STATUS_TFTOC SHALL BE INITIALIZED ON OPERATION CYCLE START 
       *
       * [SWS_Dem_00389]
       * The information for UDS DTC status bit 1 (TestFailedThisOperationCycle) is
       * non-volatile, if the PendingDTC bit is used (refer to [SWS_Dem_00006]) or if the Dem
       * module supports operation cycles over power cycles 
       * 1. PendingDTC is not used
       * 2. OperationCycleState Storage is off */    
      #if 0
      if ((0U == (DEM_UDS_STATUS_PDTC & Dem_Status_Availability_Mask)) &&
           (Dem_Operation_Cycle_Status_Storage == STD_OFF))
      {
        /* Reset DEM_UDS_STATUS_TNCTOC */
        DEM_SET_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_TNCTOC);
        /* SWS_Dem_00394 : Note:  The  information  for  UDS  DTC  status  bit  6
                      (TestNotCompleteThisOperationCycle)  needs  to  be  stored  non-volatile,
                      if the PendingDTC  bit is used (refer to  SWS_Dem_00006),
                      or if the  Dem  module supports operation cycles
                      over power cycles (refer to DemOperationCycleStatusStorage).*/
        DEM_CLR_UDSSTATUSBYTE(eventId, DEM_UDS_STATUS_TFTOC);
      }
      #endif        

      (void)Dem_EvMem_TriggerNvDataStorage(
        eventId, DTCOrigin, EventStatusByteOld,
	    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */      
        cbDTC->EvMemTriggerFlag, DEM_FALSE, dirty);
    }
    else
    {
      DEM_RST_UDSSTATUSBYTE(eventId, (DEM_UDS_STATUS_TNCTOC | DEM_UDS_STATUS_TNCSLC));
    }

    /* SWS_Dem_00391 : Note: The information for UDS DTC status bit 3(ConfirmedDTC) is non-volatile 
     * (but it is also calculable based on the respective event memory entry).
     * 
     * SWS_Dem_00392 : Note: The  information for  UDS DTC status bit 4(TestNotCompletedSinceLastClear) is non-volatile.
     * 
     * SWS_Dem_00393: Note: The  information for  UDS DTC status bit 5 (TestFailedSinceLastClear)  is  nonvolatile.
     *
     * SWS_Dem_00395 : Note: The  information for  UDS  DTC  status bit  7(WarningIndicatorRequested)  maybe volatile
     * (because it is calculated based on the assigned warning indicator states).
     *
     * But we don't use the warning indicator states, so bit 7 is non-volatile except MIL_ON */
  }  

  Dem_EvMem_InitIndicatorBehaviorAccumulator();

  /* polyspace<RTE:UNR:Not a defect:No action planned> This variable is configurable */
  #if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_OFF)
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */
  {
    uint8 operationCycleId = 0U;
    for (operationCycleId = 0 ; operationCycleId < Dem_Num_Operation_Cycles; operationCycleId++)
    {    
      (void)Dem_EvMem_SetOpCycleState(operationCycleId, DEM_CYCLE_STATE_END);
    }
  }
  #endif
}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_DTCOriginIsValid (>2)
 **
 ** Service ID          : None
 **
 ** Description         : Checks whether DTC Origin is supported or not
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : DTCOrigin
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : Std_ReturnType
 **
 ** Preconditions       : None
 **
 ** Remarks             : Global Variable(s)  :
 **
 **                       Function(s) invoked :
 *******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_DTCOriginIsValid(
    const Dem_DTCOriginType DTCOrigin)
{
  boolean valid;

  switch(DTCOrigin)
  {
  /* Primary memory is  mandatory */
  case DEM_DTC_ORIGIN_PRIMARY_MEMORY:

  #if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR > 0U)
  case DEM_DTC_ORIGIN_MIRROR_MEMORY:
  #endif

  #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U)
  case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
  #endif

  #if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC > 0U)
  case DEM_DTC_ORIGIN_SECONDARY_MEMORY:
  #endif
    valid = DEM_TRUE;
    break;

  default:
    valid = DEM_FALSE;
    break;
  }

  return valid;
}
/*******************************************************************************
 ** Function Name       : Dem_EvMem_Lock (>2)
 **
 ** Service ID          : None
 **
 ** Description         : Get lock status of the event memory
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : None
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : boolean
 **
 ** Preconditions       : None
 **
 ** Remarks             : 
 *******************************************************************************/
FUNC(boolean, DEM_CODE) Dem_EvMem_Lock(void)
{
  boolean lock;

  if (DEM_CLEARDTC_STATE_READY != Dem_ClearDtcState.cds_State)
  {
    lock = DEM_TRUE;
  }
  else
  {
    lock = DEM_FALSE;
  }
  
  return lock;
}

/******************************************************************************
* Function Name        : Dem_EvMem_RegisterPermanentDTC
*
* Service ID           : None
*
* Description          : Find the stored event in the event memory
*
* Sync/Async           : Synchronous
*
* Re-entrancy          : Reentrant(Not same event Id)
*
* Input Parameters     : EventId, DTCOrigin, MemLocation
*
* InOut parameter      : None
*
* Output Parameters    : None
*
* Return parameter     : pointer for event memory entry
*
* Preconditions        : None
*
* Remarks              :
*
*****************************************************************************/
#if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
FUNC(boolean, DEM_CODE) Dem_EvMem_RegisterPermanentDTC(
  Dem_EventIdType EventId)
{
  Dem_NumOfEventMemoryEntryType pmemLoc = DEM_NO_EVMEM_ENTRY;
 
  P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) cbDTC;
  boolean dirty = DEM_FALSE;
  boolean addEvent = DEM_TRUE;

  cbDTC = &Dem_GaaCombinedDtc[Dem_Event[EventId-1U].e_PointToDTC];

  if(DEM_DTC_KIND_EMISSION_REL_DTCS == cbDTC->ddDtcKind)
  {
    Dem_NumOfEventMemoryEntryType numOfMemEntries = Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_PERMANENT_MEMORY];
    if (Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PERMANENT_MEMORY] >= numOfMemEntries)
    {
      /* Displacement	*/
      addEvent = DEM_FALSE;
    }
    else
    {
      for (pmemLoc = 0U; pmemLoc < numOfMemEntries; pmemLoc++)
      {
        
        /* already stored */
        if(EventId == Dem_PerDtcState[pmemLoc].EventIdRef) 
        {
          addEvent = DEM_FALSE;
          break;
        }
      }
    }
      
    if(addEvent == DEM_TRUE)
    {
      for(pmemLoc = 0U; pmemLoc < numOfMemEntries; pmemLoc++)
      {
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        if(DEM_NO_EVENT == Dem_PerDtcState[pmemLoc].EventIdRef)
        {
          Dem_PerDtcState[pmemLoc].EventIdRef = EventId;  /* Set EventId */
          Dem_PerDtcState[pmemLoc].PfcQualified = DEM_FALSE;
          Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PERMANENT_MEMORY]++; 
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

          dirty = DEM_TRUE;
          break;
        }
        else
        {
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        }
      }
    }
  }

  if(dirty == DEM_TRUE)
  {
    Dem_EvMem_SetEvMemNvBlockStatus(DEM_DTC_ORIGIN_PERMANENT_MEMORY, pmemLoc, DEM_EVMEM_STATUS_DIRTY_NVM);
  }

  return dirty;
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearPermanentDTC
 **
 ** Service ID          : None
 **
 ** Description         : Clear Permanent DTCs
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : None
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : boolean
 **
 ** Preconditions       : None
 **
 ** Remarks             : 
 *******************************************************************************/
#if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
FUNC(void, DEM_CODE) Dem_EvMem_ClearPermanentDTC(Dem_EventIdType EventId, boolean pfc)
{
  Dem_NumOfEventMemoryEntryType memLoc = DEM_NO_EVMEM_ENTRY;
  Dem_NumOfEventMemoryEntryType numOfMemEntries = Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_PERMANENT_MEMORY];

  for(memLoc = 0U; memLoc < numOfMemEntries; memLoc++)
  {
  	SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    if((EventId == Dem_PerDtcState[memLoc].EventIdRef) && ((Dem_PerDtcState[memLoc].PfcQualified == DEM_TRUE) || pfc == DEM_TRUE) )
    {
      Dem_PerDtcState[memLoc].EventIdRef = DEM_NO_EVENT;
      Dem_PerDtcState[memLoc].PfcQualified  = DEM_FALSE;
      if (Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PERMANENT_MEMORY] > 0U)
      {
        Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PERMANENT_MEMORY]--;
      }
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

      Dem_EvMem_SetEvMemNvBlockStatus(DEM_DTC_ORIGIN_PERMANENT_MEMORY, memLoc, DEM_EVMEM_STATUS_DIRTY_NVM);
     
      break;      
    }
  	else
  	{
  		SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
  	}
    
  }

  return;

}
#endif

/*******************************************************************************
 ** Function Name       : Dem_EvMem_FindPerMemLoc
 **
 ** Service ID          : None
 **
 ** Description         : Find Permanent memory location 
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : None
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : boolean
 **
 ** Preconditions       : None
 **
 ** Remarks             : 
 *******************************************************************************/
#if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
FUNC(Dem_NumOfEventMemoryEntryType, DEM_CODE) Dem_EvMem_FindPerMemLoc(Dem_EventIdType EventId)
{
  Dem_NumOfEventMemoryEntryType memLoc = DEM_NO_EVMEM_ENTRY;
  Dem_NumOfEventMemoryEntryType numOfMemEntries = Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_PERMANENT_MEMORY];
  boolean findEvent = DEM_FALSE;

  for(memLoc = 0U; memLoc < numOfMemEntries; memLoc++)
  {
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    if(EventId == Dem_PerDtcState[memLoc].EventIdRef)
    {
      findEvent = DEM_TRUE;
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      
      break;
      
    }
    else
    {
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
  }

  if(findEvent == DEM_FALSE)
  {
    memLoc = DEM_NO_EVMEM_ENTRY;
  }

  return memLoc;
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearPermanentDTC
 **
 ** Service ID          : None
 **
 ** Description         : Clear Permanent DTCs
 **
 ** Sync/Async          : Synchronous
 **
 ** Re-entrancy         : Reentrant
 **
 ** Input Parameters    : None
 **
 ** InOut parameter     : None
 **
 ** Output Parameters   : None
 **
 ** Return parameter    : boolean
 **
 ** Preconditions       : None
 **
 ** Remarks             : 
 *******************************************************************************/
#if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
FUNC(void, DEM_CODE) Dem_EvMem_ClearPermanentMemEntry(Dem_NumOfEventMemoryEntryType MemLoc)
{

  Dem_NumOfEventMemoryEntryType numOfMemEntries = Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_PERMANENT_MEMORY];


  if(MemLoc < numOfMemEntries)
  {
  	SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();

    Dem_PerDtcState[MemLoc].EventIdRef = DEM_NO_EVENT;
    Dem_PerDtcState[MemLoc].PfcQualified  = DEM_FALSE;
    if (Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PERMANENT_MEMORY] > 0U)
    {
      Dem_NumOfStoredEvtMemEntryies[DEM_DTC_ORIGIN_PERMANENT_MEMORY]--;
    }
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

    Dem_EvMem_SetEvMemNvBlockStatus(DEM_DTC_ORIGIN_PERMANENT_MEMORY, MemLoc, DEM_EVMEM_STATUS_DIRTY_NVM);
  }
    

  return;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_EvMem_ClearEventStatusByte                      **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Clear the Events which is not assigned DTC          **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   :                                                     **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if (DEM_EVENT_CLEAR_SUPPORT == STD_ON)
static FUNC(void, DEM_CODE) Dem_EvMem_ClearEventStatusByte(void)
{
  Dem_EventIdType eventId;
  Dem_EventParameterPCType event;
  Dem_EventIdType EventIdIndex;
  boolean eventClear;
  Dem_UdsStatusByteType DTCStatusOld = 0;
  Dem_UdsStatusByteType EventStatusByteOld = 0;
  #if (DEM_TRIGGER_INIT_BEFORE_CLEAR_OK == STD_ON)
  Dem_EventParameterCallbackPtrType eventCbk;
  #endif

  for (EventIdIndex = 0; EventIdIndex < DEM_NUM_OF_DTCNOTASSIGNEDEVENTS; EventIdIndex++)
  {    
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */    
    eventId = Dem_ListOfDtcNotAssignedEvents[EventIdIndex];
    event= &Dem_Event[eventId-1U];
    #if (DEM_TRIGGER_INIT_BEFORE_CLEAR_OK == STD_ON)
    eventCbk = NULL_PTR;
    if(event->e_PointToEventCallbackData < (Dem_EventIdType)DEM_NUMBER_OF_EVENT_CALLBACK)
    {
      eventCbk = &Dem_Event_Callback[event->e_PointToEventCallbackData];
    }
    #endif
    EventStatusByteOld = Dem_AllEventStatusByte[eventId];
    eventClear = DEM_GET_EVENTPARAM_EVENT_CLEAR(event->ParamFieldsB);

    if(DEM_TRUE == eventClear)
    {
      /* Re-initialization triggered before the Dem module returns  DEM_CLEAR_OK */
      #if (DEM_TRIGGER_INIT_BEFORE_CLEAR_OK == STD_ON)
      if((NULL_PTR != eventCbk) && (eventCbk->pDemInitMonitorForEvent != NULL_PTR))
      {
        /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */    
        eventCbk->pDemInitMonitorForEvent((Dem_InitMonitorReasonType)DEM_INIT_MONITOR_CLEAR);
      }    
      #endif
    
      /* Clear events which are not assigned DTC  */
      DEM_RST_UDSSTATUSBYTE(eventId, (uint8)DEM_UDS_STATUS_TNCSLC |(uint8)DEM_UDS_STATUS_TNCTOC);

      if (EventStatusByteOld != Dem_AllEventStatusByte[eventId])
      {
        Dem_TriggerCallbackOnUdsStatus(eventId, EventStatusByteOld, DTCStatusOld);  
      }
    
    }    
    
  }
}
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/* polyspace-end DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

