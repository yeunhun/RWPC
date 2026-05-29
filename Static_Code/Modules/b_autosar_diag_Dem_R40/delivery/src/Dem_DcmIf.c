/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_DcmIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of Dcm interface functionality                      **
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
** 1.5.2    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.5.1    25-07-2019    EunKyung.Kim   Changes made As per Redmine #18087   **
**                                                                            **
** 1.5.0    10-12-2018    EunKyung.Kim   Changes made As per Redmine #8561    **
**                                                                            **
** 1.4.3    09-11-2018    EunKyung.Kim   Changes made As per Redmine #14481   **
**                                                                            **
** 1.4.2    31-10-2018    EunKyung.Kim   Changes made As per Redmine #13361   **
**                                                                            **
** 1.4.1    20-07-2017    EunKyung.Kim   Changes made As per Redmine #9294    **
**                                                                            **
** 1.4.0    06-02-2016    YoungJin.Yun   Changes made As per Redmine #7379    **
**                                                                            **
** 1.3.0    30-09-2016    YoungJin.Yun   Changes made As per Redmine #6097    **
**                                                                            **
** 1.2.0    15-06-2016    YoungJin.Yun   Changes made As per Redmine #1164    **
**                                                                            **
** 1.1.1    03-03-2016    YoungJin.Yun   Changes made As per Redmine #4215    **
**                                                                            **
** 1.1.0    07-01-2016    YoungJin.Yun   Changes made As per Redmine #3353,   **
**                                       #698, #3638,#2473,#3271,#2827,#1151, ** 
**                                       #2589                                **
**                                                                            **
** 1.0.2    16-04-2015    Sungeol Baek  As per reminde #2171                  **
**                                                                            **  
** 1.0.1     11-Jan-2014   YJ.Yun      Changes made As per Redmine #366,#367, **
**                                     #368,#371,#372,#405,#366,#367,#368,    **
**                                     #371,#372,#405,#369,#373,#374,#375,    **
**                                     #376,#370,#377,#381,#382,#383,#384,    **
**                                     #385,#386,#387,#388,#389,#390,#391,    **
**                                     #397,#398,#399,#400,#378,#380,#401,    **
**                                     #403,#404,#406,#409,#410,#411,#412     **
**                                                                            **
** 1.0.0     01-Jan-2013   Autron      Initial Version                        **
*******************************************************************************/ 

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "os.h"
#include "Dem.h"                /* DEM module Header File */
#include "Dem_Ram.h"            /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                /* Det Header File */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */

#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */

#include "Dem_Types.h"
#include "Dem_Event.h"
#include "Dem_Dtc.h"
#include "Dem_EventMemory.h"
#include "Dem_EventRelatedData.h"

#if (DEM_OBD_SUPPORT == STD_ON)
#include "Dem_Obd.h"
#endif

/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace-begin MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dem_SetDTCFilter                                    **
**                                                                            **
** Service ID           : 0x13                                                **
**                                                                            **
** Description          : The server shall perform a bit-wise logical AND-    **
**                        ing operation between the mask specified in the     **
**                        client's request and the actual status associated   **
**                        with each DTC supported by the server. In addition  **
**                        to the DTCStatusAvailabilityMask, the server shall  **
**                        return all DTCs for which the result of the AND-    **
**                        ing operation is non-zero [i.e. (statusOfDTC &      **
**                        DTCStatusMask) != 0]. If the client specifies a     **
**                        status mask that contains bits that the server      **
**                        does not support, then the server shall process     **
**                        the DTC information using only the bits that it     **
**                        does support. If no DTCs within the server match    **
**                        the masking criteria specified in the client's      **
**                        request, no DTC or status information shall be      **
**                        provided following the DTCStatusAvailabilityMask    **
**                        byte in the positive response message (statusOf     **
**                        DTC & DTCStatusMask) & (severity & DTCSeverity      **
**                        Mask) != 0                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCStatusMask, DTCKind, DTCOrigin, DTCFormat        **
**                        FilterWithSeverity, DTCSeverityMask                 **
**                        FilterForFaultDetectionCounter                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_ReturnSetFilterType                             **
**                                                                            **
** Preconditions        : The API Dem_Init()                                  **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(Dem_ReturnSetFilterType, DEM_CODE) 
Dem_SetDTCFilter(
  uint8 DTCStatusMask, 
  Dem_DTCKindType DTCKind, 
  Dem_DTCFormatType DTCFormat,
  Dem_DTCOriginType DTCOrigin, 
  Dem_FilterWithSeverityType FilterWithSeverity,
  Dem_DTCSeverityType DTCSeverityMask,
  Dem_FilterForFDCType FilterForFaultDetectionCounter)
{
  Dem_ReturnSetFilterType retVal = DEM_FILTER_ACCEPTED;
  
  /* Module initialization check */
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_UNINIT);
    retVal =  DEM_WRONG_FILTER;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  /* DTCOrigin check */
  else if ((boolean)DEM_FALSE == Dem_EvMem_DTCOriginIsValid(DTCOrigin))
  {
    DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_PARAM_CONFIG);
    retVal = DEM_WRONG_FILTER;
  }
  /* DTCKind check */
  else if (
    (DTCKind != DEM_DTC_KIND_ALL_DTCS) &&
    (DTCKind != DEM_DTC_KIND_EMISSION_REL_DTCS))
  {
    DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_PARAM_DATA);
    retVal = DEM_WRONG_FILTER;
  }
  /* DTCFormat check */
  else if (
    (DTCFormat != DEM_DTC_FORMAT_UDS) &&
    (DTCFormat != DEM_DTC_FORMAT_OBD))
  {  
    DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_PARAM_CONFIG);
    retVal = DEM_WRONG_FILTER;
  }
  /* FilterwithSeverity input is not defined */
  else if (
    (FilterWithSeverity != (Dem_FilterWithSeverityType)DEM_FILTER_WITH_SEVERITY_YES) &&
    (FilterWithSeverity != (Dem_FilterWithSeverityType)DEM_FILTER_WITH_SEVERITY_NO))
  {
    DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_PARAM_DATA);
    retVal = DEM_WRONG_FILTER;
  }
  /* FilterForFaultDetectionCounter input is not defined */
  else if (
    (FilterForFaultDetectionCounter != (Dem_FilterForFDCType)DEM_FILTER_FOR_FDC_YES) &&
    (FilterForFaultDetectionCounter != (Dem_FilterForFDCType)DEM_FILTER_FOR_FDC_NO) )
  {
    DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_PARAM_DATA);
    retVal = DEM_WRONG_FILTER;
  }
  #endif  
  /* @ISO 14229 11.3.1.9
   * (((statusOfDTC & DTCStatusMask) !=0) &&  
   * ((severity & DTCSeverityMask) != 0)) == TRUE    
   */   
  else if (
    (DTCSeverityMask != (Dem_DTCSeverityType)DEM_DTC_SEV_NO_SEVERITY) &&
    ((DTCSeverityMask & (Dem_DTCSeverityType)DEM_DTC_SEV_MASK) == 0)  )
  {
    DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_PARAM_DATA);
    retVal = DEM_WRONG_FILTER;
  }  
  else
  {
    Dem_EventIdType eventId;
    for (eventId = 1U; eventId <= Dem_Number_Of_Events; eventId++)
    {
      Dem_EvClearProcState(eventId, DEM_EVPROCSTATE_DTC_FILTER);
    }
    
    Dem_DTCFilterState.dfs_DTCOrigin = DTCOrigin;               
    Dem_DTCFilterState.dfs_FilterForFDC = FilterForFaultDetectionCounter;
    Dem_DTCFilterState.dfs_DTCKind = DTCKind;               
    Dem_DTCFilterState.dfs_DTCSeverityMask = DTCSeverityMask;     
    Dem_DTCFilterState.dfs_FilterWithSeverity = FilterWithSeverity;

    /*[SWS_Dem_01058] 
      The function Dem_DcmSetDTCFilter shall ignore unsupported bits
      (refer to configuration parameter DemDtcStatusAvailabilityMask) 
      retrieved in DTCStatusMask. */ 
    if(DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS)
    {
      Dem_DTCFilterState.dfs_DTCStatusMask = DTCStatusMask;
    }
    else
    {
      Dem_DTCFilterState.dfs_DTCStatusMask = DTCStatusMask & Dem_Status_Availability_Mask;
    }
    
    Dem_DTCFilterState.dfs_DTCFormat = DTCFormat;

    Dem_DTCFilterState.dfs_JobAction = DEM_JOB_TRIGGER;;
    Dem_DTCFilterState.dfs_NumOfFilteredDTC = 0U;

    /* Initialize the count for no.of filtered DTC's returned to DCM */
    Dem_DTCFilterState.dfs_NextEvent = 1U;
    
    /* retVal = DEM_FILTER_ACCEPTED; */
  }
  
  return retVal;
}

/*******************************************************************************
** Function Name        : Dem_SetFreezeFrameRecordFilter                      **
**                                                                            **
** Service ID           : 0x3f                                                **
**                                                                            **
** Description          : This API shall set a freeze frame Record filter     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCFormat                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint16* NumberOfFilteredRecords                     **
**                                                                            **
** Return parameter     : Dem_ReturnSetFilterType                             **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_FilteredFFRecord                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/

FUNC(Dem_ReturnSetFilterType, DEM_CODE)Dem_SetFreezeFrameRecordFilter(
  Dem_DTCFormatType DTCFormat,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) NumberOfFilteredRecords)
{
  Dem_ReturnSetFilterType retVal = DEM_FILTER_ACCEPTED;
  
  if (DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_SETFREEZEFRAMERECORDFILTER_SID, DEM_E_UNINIT);
    retVal = DEM_WRONG_FILTER;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (NULL_PTR == NumberOfFilteredRecords)
  {
    DEM_REPORT_ERROR(DEM_SETFREEZEFRAMERECORDFILTER_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_WRONG_FILTER;
  }
  else if ((DTCFormat != DEM_DTC_FORMAT_OBD) && (DTCFormat != DEM_DTC_FORMAT_UDS))
  {
    DEM_REPORT_ERROR(DEM_SETFREEZEFRAMERECORDFILTER_SID, DEM_E_PARAM_CONFIG);
    retVal = DEM_WRONG_FILTER;
  }
  #endif  
  else
  {
    uint16 recordFiltered = 0U; 
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0U) && (DEM_SIZE_OF_FREEZEFRAME > 0U))
    Dem_EventIdType evId;
    Dem_NumOfEventMemoryEntryType memLoc = 0U;            
    /* [SWS_Dem_00595] 
     * The function Dem_DcmSetFreezeFrameRecordFilter
     * shall set the static filter criteria attribute "all freeze frame records cur-
     * rently stored in the event memory" to be used for the subsequent calls of
     * Dem_DcmGetNextFilteredRecord. The filter criteria attributes shall be used until
     * the next call of Dem_DcmSetFreezeFrameRecordFilter or Dem initialization. */

    Dem_FilteredFFRecord.nextEvent = DEM_NO_EVENT;
    for (evId = 1U; evId <= Dem_Number_Of_Events; evId++)
    {
      Dem_EvClearProcState(evId, DEM_EVPROCSTATE_DTC_FILTER);
    }

    /* It can be processed regardless of combined event
     * because of searching the event from event memory, 
     * It always stores a first event out of combined events
     *
     * Note:
     * [SWS_Dem_00210] The function Dem_DcmSetFreezeFrameRecordFilter shall retrieve 
     * the number of filtered freeze frame records. This filter always belongs to primarymemory
     */        
    for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_PRIMARY_MEMORY]; memLoc++)
    {
      evId = Dem_EvMem_GetEventIdByEvMemEntry(DEM_DTC_ORIGIN_PRIMARY_MEMORY,memLoc);       
      /* if (DEM_TRUE == Dem_EventIdIsValid(evId)) */
      if ((evId <= Dem_Number_Of_Events) && (DEM_NO_EVENT != evId))
      {
        /* Filtering according to  expected DTCformat */
        if ((boolean)DEM_TRUE == Dem_DTCFormatIsValid(evId, DTCFormat))
        {      
          Dem_EventParameterPCType event = &Dem_Event[evId - 1U];    
          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
          if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
          {
            /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
            if (Dem_EventRelatedData[event->e_PointToData].FFClassPos < Dem_Num_Of_FreezeFrameClass)
            {
              Dem_RecordNumberType recordNumber = Dem_EvMem_GetRecNumOfFF( 
                Dem_EvMem_GetEmEntryByMemPosition(DEM_DTC_ORIGIN_PRIMARY_MEMORY, memLoc));
              /* RecordNumber 0 means that Freeze Frame Record is not stored in the event memory */
              if (0U != recordNumber)
              {            
                /* Compute the number of filtered records */
                recordFiltered += recordNumber;
                Dem_EvSetProcState(evId, DEM_EVPROCSTATE_DTC_FILTER);

                if (DEM_NO_EVENT == Dem_FilteredFFRecord.nextEvent)
                {
                  Dem_FilteredFFRecord.nextEvent = evId;
                }
              }
            }
          }
        }
      }
    }
    #endif
    
    /* Initialize the Index of record number for next event */  
    Dem_FilteredFFRecord.nextRecord =   0U;

    /* Set the number of filtered record to zero */
    *NumberOfFilteredRecords = recordFiltered;
  
    /* retVal = DEM_FILTER_ACCEPTED; */
  }
  
  return retVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetStatusOfDTC                                  **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : This API shall be used to read the status of a      **
**                        Gets the status of a DTC. For large configurations  **
**                        and DTC-calibration the interface behaviour can be  **
**                        asynchronous(splitting the DTC-search into segments)**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTC, DTCOrigin                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint8* DTCStatus                                    **
**                                                                            **
** Return parameter     : Dem_ReturnGetStatusOfDTCType                        **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
FUNC(Dem_ReturnGetStatusOfDTCType, DEM_CODE) 
Dem_GetStatusOfDTC(
  uint32 DTC, 
  Dem_DTCOriginType DTCOrigin,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DTCStatus)
{
  Dem_ReturnGetStatusOfDTCType retVal = DEM_STATUS_OK;
  
  /* Check module Initialization status */
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_GETSTATUSOFDTC_SID, DEM_E_UNINIT);
    retVal = DEM_STATUS_FAILED;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  /* Check DTC Status is a Null pointer */
  else if (DTCStatus == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_GETSTATUSOFDTC_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_STATUS_FAILED;
  }
  /* DTCOrigin check */
  else if (
    (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
    (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) &&
    (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) &&
    (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY) )
  {
    DEM_REPORT_ERROR(DEM_GETSTATUSOFDTC_SID, DEM_E_PARAM_CONFIG);
    retVal = DEM_STATUS_WRONG_DTCORIGIN;
  }
  #endif  
  else
  {    
    #if (DEM_DEV_ERROR_DETECT == STD_ON)
    Dem_EventIdType eventId = Dem_GetEventIdByDTC(DEM_GETSTATUSOFDTC_SID, DTC);
    #else
    Dem_EventIdType eventId = Dem_GetEventIdByDTC(DTC);
    #endif
    /* if (DEM_FALSE == Dem_EventIdIsValid(eventId)) */
    if ((eventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == eventId))
    {
      DEM_REPORT_ERROR(DEM_GETSTATUSOFDTC_SID, DEM_E_PARAM_CONFIG);
      retVal = DEM_STATUS_WRONG_DTC;
    }
    #if (DEM_MAX_EVENT_DESTINATION_SELECTED > 0U)
    else if ((boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(eventId, DTCOrigin))
    {
      retVal = DEM_STATUS_WRONG_DTCORIGIN;
    }     
    else if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP))
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always can evaluates to true/false according to DTCSuppression configuration */      
    {
      retVal = DEM_STATUS_FAILED;
    }
    else
    {
      P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) cbDTC = Dem_GetCbDTCByEventId(eventId);
      if(NULL_PTR != cbDTC)
      {
        /* If specific StatusAvailablilityMask of a DTC is existed */
        /* polyspace-begin DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because UdsStatusAvailabilityMask can be configured value 0 by user , this condition maybe evaluate to false" */
        if(0U != cbDTC->UdsStatusAvailabilityMask)
        {
          /* UdsStatusAvailabilityMask and Dem_DTCFilterState.dfs_DTCStatusMask are
          * subset of Dem_Status_Availability_Mask */
          *DTCStatus = Dem_GetDTCStatus(eventId) & cbDTC->UdsStatusAvailabilityMask;
          /* polyspace-end DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because UdsStatusAvailabilityMask can be configured value 0 by user , this condition maybe evaluate to false" */
        }
        else
        {            
          *DTCStatus = Dem_GetDTCStatus(eventId) & Dem_Status_Availability_Mask;  
        }
          /* retVal =  DEM_STATUS_OK; */
      }
      else
      {
        retVal = DEM_STATUS_FAILED;
      }
    }
    #else
    else
    {
      DEM_UNUSED(DTCOrigin);
      DEM_UNUSED(DTCStatus);      
      retVal =  DEM_STATUS_WRONG_DTCORIGIN;
    }
    #endif
  }

  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_GetDTCStatusAvailabilityMask                    **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : This API shall be used to get the DTC Status        **
**                        availability mask                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint8* DTCStatusMask                                **
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
FUNC(Std_ReturnType, DEM_CODE) 
Dem_GetDTCStatusAvailabilityMask(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DTCStatusMask)
{
  Std_ReturnType retVal = E_NOT_OK;
  
  /* Module initialization check */
  if(Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_GETDTCSTATUSAVAILABILITYMASK_SID, DEM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if(DTCStatusMask == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_GETDTCSTATUSAVAILABILITYMASK_SID, DEM_E_PARAM_POINTER);
    retVal = E_NOT_OK;
  }
  #endif  
  else
  {
    /* Set DTCStatusAvailabilityMask to DTCStatusMask */
    *DTCStatusMask = Dem_Status_Availability_Mask;
    retVal = E_OK;
  }
  
  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_GetNumberOfFilteredDTC                          **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : This API shall be used to get the number of         **
**                        Filtered DTC                                        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint16* NumberOfFilteredDTC                         **
**                                                                            **
** Return parameter     : Dem_ReturnGetNumberOfFilteredDTCType                **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
FUNC(Dem_ReturnGetNumberOfFilteredDTCType, DEM_CODE)
  Dem_GetNumberOfFilteredDTC(
  P2VAR (uint16, AUTOMATIC, DEM_APPL_DATA) NumberOfFilteredDTC)
{
  Dem_ReturnGetNumberOfFilteredDTCType retVal = DEM_NUMBER_PENDING;

  /*  Check   module  Initialization  status  */
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_GETNUMBEROFFILTEREDDTC_SID, DEM_E_UNINIT);
    retVal = DEM_NUMBER_FAILED;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)   
  else if (NumberOfFilteredDTC == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_GETNUMBEROFFILTEREDDTC_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_NUMBER_FAILED;
  }
  #endif   
  else
  {
    *NumberOfFilteredDTC = 0U;  
    /* DEM_JOB_TRIGGER: by Dem_SetFreezeFrameRecordFilter
     * DEM_JOB_RUNNING: by Dem_MainFunction
     * DEM_JOB_DONE:    after job is finished by Dem_MainFunction
     */
    if ((DEM_JOB_TRIGGER == Dem_DTCFilterState.dfs_JobAction) || (DEM_JOB_RUNNING == Dem_DTCFilterState.dfs_JobAction))
    {    
      /* Return appropriate value */
      retVal = DEM_FILTERED_PENDING;
    }
    else if(DEM_JOB_DONE == Dem_DTCFilterState.dfs_JobAction)
    {
      /* Return the number of filtered DTC's */
      *NumberOfFilteredDTC = Dem_DTCFilterState.dfs_NumOfFilteredDTC;  
      retVal = DEM_NUMBER_OK;
    }
    else
    {
      retVal = DEM_NUMBER_FAILED;
    }
  }
  
  return retVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetNextFilteredDTC                              **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : This API shall be used to get the next              **
**                        Filtered DTC                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint32* DTC,                                        **
**                        uint8* DTCStatus                                    **
**                                                                            **
** Return parameter     : Dem_ReturnGetNextFilteredDTCType                    **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
*******************************************************************************/
FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE) Dem_GetNextFilteredDTC(
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCStatus)
{
  Dem_ReturnGetNextFilteredDTCType retVal = DEM_FILTERED_NO_MATCHING_DTC;

  /* Check module Initialization status */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTC_SID, DEM_E_UNINIT);
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ( (NULL_PTR == DTC) || (NULL_PTR == DTCStatus))
  {
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTC_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  #endif  
  else if (
    (DEM_JOB_TRIGGER == Dem_DTCFilterState.dfs_JobAction) || 
    (DEM_JOB_RUNNING == Dem_DTCFilterState.dfs_JobAction))
  {    
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTC_SID, DEM_E_WRONG_CONDITION);
    /* Return appropriate value */
    retVal = DEM_FILTERED_PENDING;
  }  
  else if (DEM_JOB_DONE != Dem_DTCFilterState.dfs_JobAction)
  {
    Dem_DTCFilterState.dfs_NextEvent = DEM_NO_EVENT;
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  } 
  else if (DEM_NO_EVENT == Dem_DTCFilterState.dfs_NextEvent)
  {
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  } 
  else  
  {
    /* dfs_NextEvent is EventId.*/
    while (Dem_DTCFilterState.dfs_NextEvent <= Dem_Number_Of_Events) 
    {
      /* It can set a only first event(out of combined dtc) to true */
      if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(Dem_DTCFilterState.dfs_NextEvent, DEM_EVPROCSTATE_DTC_FILTER))
      {
        P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) cbDTC = Dem_GetCbDTCByEventId(Dem_DTCFilterState.dfs_NextEvent);
        
        Dem_EvClearProcState(Dem_DTCFilterState.dfs_NextEvent, DEM_EVPROCSTATE_DTC_FILTER);

        if (NULL_PTR != cbDTC)
        {  
          *DTC = Dem_GetDtcByCombineDTC(cbDTC);
                  
          /* If specific StatusAvailablilityMask of a DTC is existed */
          /* polyspace-begin DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because UdsStatusAvailabilityMask can be configured value 0 by user , 
             this condition maybe evaluate to false" */
          if (0U != cbDTC->UdsStatusAvailabilityMask)
          {
            /* UdsStatusAvailabilityMask and Dem_DTCFilterState.dfs_DTCStatusMask are
             * subset of Dem_Status_Availability_Mask */
            *DTCStatus = Dem_GetDTCStatus(Dem_DTCFilterState.dfs_NextEvent) & cbDTC->UdsStatusAvailabilityMask;
          /* polyspace-end DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because UdsStatusAvailabilityMask can be configured value 0 by user , 
             this condition maybe evaluate to false" */
          }
          else
          { 
            *DTCStatus = Dem_GetDTCStatus(Dem_DTCFilterState.dfs_NextEvent) & Dem_Status_Availability_Mask;

          }

          /*  The value 0x00 used as DTCStatusMask for the subfunctions 0x0A and 0x15    */
          if(((Dem_DTCFilterState.dfs_DTCStatusMask & (*DTCStatus)) != 0) || (Dem_DTCFilterState.dfs_DTCStatusMask == 0))
          {
            retVal =  DEM_FILTERED_OK;
            break;
          }
        }
        else
        {
          DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTC_SID, DEM_E_PARAM_DATA);
        }
      }
      
      Dem_DTCFilterState.dfs_NextEvent++;   
    }
    if (DEM_FILTERED_OK != retVal)
    {
      Dem_DTCFilterState.dfs_NextEvent = DEM_NO_EVENT;    
    }
  }
      
  return retVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetDTCByOccurrenceTime                          **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : Gets the DTC by occurrence time.                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCRequest                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint32* DTC                                         **
**                                                                            **
** Return parameter     : Dem_ReturnGetDTCByOccurrenceTimeType                **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
#if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
FUNC(Dem_ReturnGetDTCByOccurrenceTimeType, DEM_CODE)
Dem_GetDTCByOccurrenceTime(
  Dem_DTCRequestType DTCRequest,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC)
{
  Dem_ReturnGetDTCByOccurrenceTimeType retVal = DEM_OCCURR_NOT_AVAILABLE;

  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_GETDTCBYOCCURRENCETIME_SID, DEM_E_UNINIT);
    /* retVal = DEM_OCCURR_NOT_AVAILABLE; */
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (DTC == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_GETDTCBYOCCURRENCETIME_SID, DEM_E_PARAM_POINTER);
    /* retVal = DEM_OCCURR_NOT_AVAILABLE; */
  }
  else if (
    (DTCRequest != DEM_FIRST_FAILED_DTC) && 
    (DTCRequest != DEM_MOST_RECENT_FAILED_DTC) && 
    (DTCRequest != DEM_MOST_REC_DET_CONFIRMED_DTC) && 
    (DTCRequest != DEM_FIRST_DET_CONFIRMED_DTC))
  {
    DEM_REPORT_ERROR(DEM_GETDTCBYOCCURRENCETIME_SID, DEM_E_PARAM_DATA);
    /* retVal = DEM_OCCURR_NOT_AVAILABLE; */
  }
  #endif  
  else
  {
    /* [Dem219]  The function Dem_GetDTCByOccurrenceTime(refer to chapter
      8.3.4.1.7) shall provide the capability to get one DTC stored in 
      the primary event memory according to the API parameter DTCRequest,
      which specifies the relevant occurrence time.
  
     [SWS_Dem_00935]: 
     1.first failed DTC requested
     2.most recent failed DTC requested
     
     [SWS_Dem_00935]: 
     1. most recently detected confirmed DTC requested 
     2. first detected confirmed DTC requested 
    */
    if (E_OK == Dem_EvMem_GetDTCByOccurrenceTime(DTCRequest, DTC))
    {
      /* Set the return value */
      retVal = DEM_OCCURR_OK;
    }
    else
    {
      /* retVal = DEM_OCCURR_NOT_AVAILABLE; */
    }
  }
  
  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_GetNextFilteredRecord                           **
**                                                                            **
** Service ID           : 0x3a                                                **
**                                                                            **
** Description          : This API provides Gets the next freeze frame record **
**                        number and its associated DTC stored in the event   **
**                        memory. The interface has an asynchronous behaviour **
**                        because NvRAM access might be required.             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint32* DTC,                                        **
**                        uint8* RecordNumber                                 **
**                                                                            **
** Return parameter     : Dem_ReturnGetNextFilteredDTCType                    **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_FilteredFFRecord                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE)
Dem_GetNextFilteredRecord(
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) RecordNumber)
{
  Std_ReturnType retVal = DEM_FILTERED_NO_MATCHING_DTC;

  /* Check module Initialization status */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDRECORD_SID, DEM_E_UNINIT);
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ( (NULL_PTR == DTC) || (NULL_PTR == RecordNumber))
  {
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDRECORD_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  else if (DEM_NO_EVENT == Dem_FilteredFFRecord.nextEvent)
  {
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDRECORD_SID, DEM_E_PARAM_DATA);
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  #endif    
  else
  {
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0u) && \
         (DEM_SIZE_OF_FREEZEFRAME > 0u))
    Dem_EventIdType eventId;         
    Dem_EventMemoryEntryPtrType entry;   
    
    /*  if event is deleled or aged, Dem returns the next event.*/
    while (Dem_FilteredFFRecord.nextEvent <= Dem_Number_Of_Events) 
    {
      if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(Dem_FilteredFFRecord.nextEvent, DEM_EVPROCSTATE_DTC_FILTER))
      { 
        /* Session checking is not necessary.
         * Dcm calls the this function after calling
         * Dem_SetFreezeFrameRecordFilter                                       
         */                  
        eventId = Dem_FilteredFFRecord.nextEvent;                
        entry = Dem_EvMem_FindEntry(eventId, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
        if (NULL_PTR != entry)
        {
          Dem_EventParameterPCType event = &Dem_Event[eventId - 1U];    
          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
          if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
          { 
            Dem_EventRelatedDataCPCType evData = &Dem_EventRelatedData[event->e_PointToData];
            const Dem_RecordNumberType maxRecordCount = Dem_EvMem_GetRecNumOfFF(entry);
            if ( (Dem_FilteredFFRecord.nextRecord < maxRecordCount) &&                
            /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
            (Dem_FilteredFFRecord.nextRecord < evData->MaxNumOfFreezeFrameRecords) 
            )
            {
              /* if Event has no ff , FFRecordNumPos is 0xFFFF */
              const uint16 offset = evData->FFRecordNumPos + Dem_FilteredFFRecord.nextRecord;            
              if (offset < Dem_Max_ListOfFFRecordNumbers)
              {
                (void)Dem_GetEventDTC(&Dem_Event[eventId -1U], DTC, DEM_DTC_FORMAT_UDS);
                /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
                *RecordNumber = Dem_ListOfFFRecordNumbers[offset];
                /* Increment index count of record number for one dtc */
                Dem_FilteredFFRecord.nextRecord++;        
                retVal = DEM_FILTERED_OK;
          
                break;  
              }
            }
          }
        }

        /* [1] No exist in event memory 
         * [2] end loop about all records of a freeze frame of a event  
         * [3] etc */
        Dem_EvClearProcState(Dem_FilteredFFRecord.nextEvent, DEM_EVPROCSTATE_DTC_FILTER);
      }

      /* Initialize the Index for next event */
      Dem_FilteredFFRecord.nextRecord = 0U;
      /* Increment the record count returned to dcm */
      Dem_FilteredFFRecord.nextEvent++;      
    }
    #endif
  }
  /* polyspace-begin CERT-C:MSC12-C [Justified:Low] "Because free frame size can be configured value 0 by user , 
     this condition maybe evaluate to true" */
  if (DEM_FILTERED_OK != retVal)
  {
    Dem_FilteredFFRecord.nextRecord = 0U;
    Dem_FilteredFFRecord.nextEvent = DEM_NO_EVENT;      
  }  
  /* polyspace-end CERT-C:MSC12-C [Justified:Low] "Because free frame size can be configured value 0 by user , 
     this condition maybe evaluate to true" */

  return retVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetNextFilteredDTCAndFDC                        **
**                                                                            **
** Service ID           : 0x3b                                                **
**                                                                            **
** Description          : This API provides the capability to get the         **
**                        current DTC and its associated Fault Detection      **
**                        counter from the DEM                                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DTC,                                                **
**                        DTCFaultDetectionCounter                            **
**                                                                            **
** Return parameter     : Dem_ReturnGetNextFilteredDTCType                    **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                        Dem_GaaPreDebounceMonitorInternal                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE)
Dem_GetNextFilteredDTCAndFDC(
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (sint8, AUTOMATIC, DEM_APPL_DATA) DTCFaultDetectionCounter)
{
  Dem_ReturnGetNextFilteredDTCType retVal = DEM_FILTERED_NO_MATCHING_DTC;

  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDFDC_SID, DEM_E_UNINIT);
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if((NULL_PTR == DTC) || (NULL_PTR == DTCFaultDetectionCounter))
  {
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDFDC_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  #endif  
  /* Check whether filtering of FDC was TRUE */    
  else if (Dem_DTCFilterState.dfs_FilterForFDC == (Dem_FilterForFDCType)DEM_FILTER_FOR_FDC_NO)
  {
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDFDC_SID, DEM_E_WRONG_CONDITION);
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  else if ( (DEM_JOB_TRIGGER == Dem_DTCFilterState.dfs_JobAction) || 
    (DEM_JOB_RUNNING == Dem_DTCFilterState.dfs_JobAction))
  {    
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDFDC_SID, DEM_E_WRONG_CONDITION);
    /* Return appropriate value */
    retVal = DEM_FILTERED_PENDING;
  }  
  else if (DEM_JOB_DONE != Dem_DTCFilterState.dfs_JobAction)
  {
    Dem_DTCFilterState.dfs_NextEvent = DEM_NO_EVENT;
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  else if (DEM_NO_EVENT == Dem_DTCFilterState.dfs_NextEvent)
  {
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }   
  else
  {
    /* nextEvent is EventId.*/
    while (Dem_DTCFilterState.dfs_NextEvent <= Dem_Number_Of_Events) 
    {
      if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(Dem_DTCFilterState.dfs_NextEvent, DEM_EVPROCSTATE_DTC_FILTER))
      {        
        Dem_EventParameterPCType event;      
        Dem_EvClearProcState(Dem_DTCFilterState.dfs_NextEvent, DEM_EVPROCSTATE_DTC_FILTER);

        event = &Dem_Event[ Dem_DTCFilterState.dfs_NextEvent - 1U];
        if (E_OK == Dem_GetEventDTC(event, DTC, DEM_DTC_FORMAT_UDS))
        {
          /* Load the FDC value of the requested DTC */
          if (E_OK == Dem_GetFaultDetectionCounter(Dem_DTCFilterState.dfs_NextEvent, DTCFaultDetectionCounter))
          {        
            Dem_DTCFilterState.dfs_NextEvent++;          
            retVal = DEM_FILTERED_OK;   
            
            break;
          }
        }
      }
      
      Dem_DTCFilterState.dfs_NextEvent++;   
    }
    /* No matched DTC */
    if (DEM_FILTERED_OK != retVal)
    {
      Dem_DTCFilterState.dfs_NextEvent = DEM_NO_EVENT;    
    }
  }
  
  return retVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetNextFilteredDTCAndSeverity                   **
**                                                                            **
** Service ID           : 0x3d                                                **
**                                                                            **
** Description          : This API provides the capability to get the         **
**                        current DTC and its associated Severity             **
**                        from the DEM                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DTC, DTCStatus,                                     **
**                        DTCSeverity, DTCFunctionalUnit                      **
**                                                                            **
** Return parameter     : Dem_ReturnGetNextFilteredDTCType                    **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
FUNC(Dem_ReturnGetNextFilteredDTCType, DEM_CODE)
  Dem_GetNextFilteredDTCAndSeverity(
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCStatus,
  P2VAR (Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA) DTCSeverity,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCFunctionalUnit)
{
  Dem_ReturnGetNextFilteredDTCType retVal = DEM_FILTERED_NO_MATCHING_DTC;
  Dem_EventParameterPCType event;  
  P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) cbDTC;      

  /* Check module Initialization status */
  if (DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID, DEM_E_UNINIT);
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (
    (NULL_PTR == DTC) ||
    (NULL_PTR == DTCStatus) ||
    (NULL_PTR == DTCSeverity) ||
    (NULL_PTR == DTCFunctionalUnit))
  {
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  #endif  
  else if (Dem_DTCFilterState.dfs_FilterWithSeverity != DEM_FILTER_WITH_SEVERITY_YES)
  {
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID, DEM_E_WRONG_CONDITION);
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  else if ((DEM_JOB_TRIGGER == Dem_DTCFilterState.dfs_JobAction) || 
    (DEM_JOB_RUNNING == Dem_DTCFilterState.dfs_JobAction))
  {    
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID, DEM_E_WRONG_CONDITION);
    /* Return appropriate value */
    retVal = DEM_FILTERED_PENDING;
  }  
  else if (DEM_JOB_DONE != Dem_DTCFilterState.dfs_JobAction)
  {
    Dem_DTCFilterState.dfs_NextEvent = DEM_NO_EVENT;
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }
  else if (DEM_NO_EVENT == Dem_DTCFilterState.dfs_NextEvent)
  {
    retVal = DEM_FILTERED_NO_MATCHING_DTC;
  }   
  else
  {
    /* nextEvent is EventId.*/
    while (Dem_DTCFilterState.dfs_NextEvent <= Dem_Number_Of_Events) 
    {
      if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(Dem_DTCFilterState.dfs_NextEvent, DEM_EVPROCSTATE_DTC_FILTER))
      { 
        Dem_EvClearProcState(Dem_DTCFilterState.dfs_NextEvent, DEM_EVPROCSTATE_DTC_FILTER);
        
        event = &Dem_Event[Dem_DTCFilterState.dfs_NextEvent - 1U];
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
        if (event->e_PointToDTC < Dem_Max_Number_Of_DTC)
        {    
          cbDTC = &Dem_GaaCombinedDtc[event->e_PointToDTC];        
          #if(DEM_OBD_SUPPORT == STD_ON)
          if (cbDTC->ddDtcFormat != DEM_DTC_FORMAT_UDS)
          {
             /* Making DTC lowByte to zero for OBD DTC */
            *DTC = (uint32)cbDTC->usObdDtc << 8U ;
          }
          else
          #endif
          {
          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
          *DTC = cbDTC->ulUdsDtc;
          }

          *DTCSeverity = cbDTC->ddDtcSeverity;
          *DTCFunctionalUnit = cbDTC->ucDtcFunctionalUnit;          
          
          /* If specific StatusAvailablilityMask of a DTC is existed */
          /* polyspace-begin DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because UdsStatusAvailabilityMask can be configured value 0 by user , 
             this condition maybe evaluate to false" */
          if (0U != cbDTC->UdsStatusAvailabilityMask)
          {
            /* UdsStatusAvailabilityMask and Dem_DTCFilterState.dfs_DTCStatusMask are
             * subset of Dem_Status_Availability_Mask */
            *DTCStatus = Dem_GetDTCStatus(Dem_DTCFilterState.dfs_NextEvent) & cbDTC->UdsStatusAvailabilityMask;
            /* polyspace-end DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Because UdsStatusAvailabilityMask can be configured value 0 by user , 
               this condition maybe evaluate to false" */
          }
          else
          { 
            *DTCStatus = Dem_GetDTCStatus(Dem_DTCFilterState.dfs_NextEvent) & Dem_Status_Availability_Mask;
          }

          if((Dem_DTCFilterState.dfs_DTCStatusMask & (*DTCStatus)) != 0)
          {
            /* Increment the index to fetch the next DTC */
            Dem_DTCFilterState.dfs_NextEvent++;

            retVal = DEM_FILTERED_OK;
            break;
          }
        }
      }
      
      Dem_DTCFilterState.dfs_NextEvent++;   
    }
    if (DEM_FILTERED_OK != retVal)
    {
      Dem_DTCFilterState.dfs_NextEvent = DEM_NO_EVENT;    
    }
  }

  
  return retVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetTranslationType                              **
**                                                                            **
** Service ID           : 0x3c                                                **
**                                                                            **
** Description          : This API provides the capability to get the         **
**                        supported DTC formats of the ECU                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_DTCTranslationFormatType                        **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
FUNC(Dem_DTCTranslationFormatType, DEM_CODE) 
Dem_GetTranslationType(void)
{
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Module Initialization check */
  if(Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_GETTRANSLATIONTYPE_SID, DEM_E_UNINIT);
  }
  #endif

  /* Return Type of DTC supported */
  return  Dem_Type_Of_Dtc_Supported;
}
/*******************************************************************************
** Function Name        : Dem_GetSeverityOfDTC                                **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : Gets Severity of the requested DTC                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint32 DTC,                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_DTCSeverityType* DTCSeverity,                   **
**                                                                            **
** Return parameter     : Dem_ReturnGetSeverityOfDTCType                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
*******************************************************************************/
FUNC(Dem_ReturnGetSeverityOfDTCType, DEM_CODE) 
Dem_GetSeverityOfDTC(
  uint32 DTC, 
  P2VAR (Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA) DTCSeverity)
{
  Dem_ReturnGetSeverityOfDTCType retVal = DEM_GET_SEVERITYOFDTC_OK;

  /* Check module Initialization status */
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_GETSEVERITYOFDTC_SID, DEM_E_UNINIT);
    retVal = DEM_GET_SEVERITYOFDTC_NOSEVERITY;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (DTCSeverity == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_GETSEVERITYOFDTC_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_GET_SEVERITYOFDTC_NOSEVERITY;
  }
  else if (
    (DTC == DEM_DTC_GROUP_EMISSION_REL_DTCS) ||
    (DTC == DEM_DTC_GROUP_ALL_DTCS) ||
    (DTC == DEM_DTC_GROUP_CHASSIS_DTCS) ||
    (DTC == DEM_DTC_GROUP_BODY_DTCS) ||
    (DTC == DEM_DTC_GROUP_POWERTRAIN_DTCS) ||
    (DTC == DEM_DTC_GROUP_NETWORK_COM_DTCS))
  {
    DEM_REPORT_ERROR(DEM_GETSEVERITYOFDTC_SID, DEM_E_PARAM_DATA);
    retVal = DEM_GET_SEVERITYOFDTC_WRONG_DTC;
  }
  #endif  
  else
  {
    Dem_CombinedDtcPCType cbDTC = Dem_GetDtcByDtcId(DTC);    
    if (NULL_PTR == cbDTC)
    {
      DEM_REPORT_ERROR(DEM_GETSEVERITYOFDTC_SID, DEM_E_PARAM_CONFIG);
      retVal = DEM_GET_SEVERITYOFDTC_WRONG_DTC;
    }   
    else 
    {
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      *DTCSeverity = cbDTC->ddDtcSeverity;
      /* retVal = DEM_GET_SEVERITYOFDTC_OK; */
    }
  }
  
  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_GetFreezeFrameDataByDTC                         **
**                                                                            **
** Service ID           : 0x1d                                                **
**                                                                            **
** Description          : This API shall be used to get freeze frame data by  **
**                        DTC                                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint32 DTC,                                         **
**                        Dem_DTCOriginType DTCOrigin,                        **
**                        uint8 RecordNumber,                                 **
**                                                                            **
** InOut parameter      : BufSize                                             **
**                                                                            **
** Output Parameters    : uint8* DestBuffer,                                  **
**                                                                            **
** Return parameter     : Dem_ReturnGetFreezeFrameDataByDTCType               **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
**                        Dem_GetPIDDataOnRequest                             **
**                        Dem_CalcSizeOfDID                                   **
*******************************************************************************/
FUNC(Dem_ReturnGetFreezeFrameDataByDTCType, DEM_CODE)
  Dem_GetFreezeFrameDataByDTC(
  Dem_DTCType DTC, 
  Dem_DTCOriginType DTCOrigin,
  const Dem_RecordNumberType RecordNumber, 
  P2VAR (uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR (uint16, AUTOMATIC, DEM_VAR) BufSize)
{
  Dem_ReturnGetFreezeFrameDataByDTCType retVal = DEM_GET_FFDATABYDTC_OK;  
  
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETFREEZEFRAMEDATABYDTC_SID, DEM_E_UNINIT);
    retVal = DEM_GET_FFDATABYDTC_WRONG_DTC;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((NULL_PTR == DestBuffer) || (NULL_PTR == BufSize))
  /* polyspace<RTE:UNR:Not a defect:No action planned> No error. Avoid to 'Unreachable code' of the polyspace */  
  {
    DEM_REPORT_ERROR(DEM_GETFREEZEFRAMEDATABYDTC_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
  }
  #endif    
  else
  {
    /* The default value of result shall be DEM_GET_READEVDATA_WRONG_RECORDNUMBER */
    Dem_ReturnReadEventDataType result = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
    #if (DEM_DEV_ERROR_DETECT == STD_ON)
    Dem_EventIdType eventId = Dem_GetEventIdByDTC(DEM_GETFREEZEFRAMEDATABYDTC_SID, DTC);
    #else
    Dem_EventIdType eventId = Dem_GetEventIdByDTC(DTC);
    #endif
    /* if (DEM_FALSE == Dem_EventIdIsValid(eventId)) */
    if ((eventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == eventId))    
    {
      DEM_REPORT_ERROR(DEM_GETFREEZEFRAMEDATABYDTC_SID, DEM_E_PARAM_CONFIG);       
      retVal = DEM_GET_FFDATABYDTC_WRONG_DTC;
    } 
    else if ((boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(eventId, DTCOrigin))
    {
      DEM_REPORT_ERROR(DEM_GETFREEZEFRAMEDATABYDTC_SID, DEM_E_PARAM_CONFIG);       
      /* No destination of the event configured */
      retVal = DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN;    
    }
    else if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP))
    {
      DEM_REPORT_ERROR(DEM_GETFREEZEFRAMEDATABYDTC_SID, DEM_E_PARAM_CONFIG);       
      retVal = DEM_GET_FFDATABYDTC_WRONG_DTC; 
    }
    else
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0U) && (DEM_SIZE_OF_FREEZEFRAME > 0U))   
    { 
      Dem_EventParameterPCType event = &Dem_Event[eventId - 1U];
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
      {
        /* [Dem236] range : 1 ~ 254 (0xFE) */
        switch(RecordNumber)
        {
        /***************************************************************
         * The value 0x00 indicates the DTC-specific OBD freeze frame. *
         ***************************************************************/
        case DEM_OBD_RECORD_NUMBER:        
          #if (DEM_OBD2_SUPPORT == STD_ON) /* @IF_REQ : permanent memory ?*/
          result = Dem_GetOBDFreezeFrameData(event, DTCOrigin, DestBuffer,BufSize);
          #else
          /* result = DEM_GET_READEVDATA_WRONG_RECORDNUMBER; */
          #endif
          break;            
          
        /***************************************************************
         * The value 0xFF is not allowed.                              *
         ***************************************************************/
        case DEM_MAX_RECORD:  
          /* result = DEM_GET_READEVDATA_WRONG_RECORDNUMBER; */
          break;
          
        /***************************************************************
         * This record number is unique per DTC (relative addressing). *
         ***************************************************************/
        default:
          result = Dem_ReadDataOfFreezeFrame(
            &Dem_EventRelatedData[event->e_PointToData], DTCOrigin, RecordNumber, 
            DEM_TRUE, DEM_DATAID_IGNORED, DEM_FFFORMAT_TYPE_HDR_REC, DestBuffer, BufSize);
          break;
        }
      }
    }
    #else
    {
      DEM_UNUSED_PTR(BufSize);
      DEM_UNUSED_PTR(DestBuffer);
      DEM_UNUSED(RecordNumber);    
    }
    #endif
    
    if (DEM_GET_FFDATABYDTC_OK == retVal)
    {
      switch(result)
      {
        #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0U) && (DEM_SIZE_OF_FREEZEFRAME > 0U))   
        case DEM_GET_READEVDATA_OK:
          /* *BufSize is updated in the Dem_ReadDataOfFreezeFrame */
          retVal = DEM_GET_FFDATABYDTC_OK; 
          break;
        case DEM_GET_READEVDATA_NOT_STORED:
          *BufSize = 0U;
          retVal = DEM_GET_FFDATABYDTC_OK; 
          break;
        case DEM_GET_READEVDATA_WRONG_BUFFERSIZE:
          DEM_REPORT_ERROR(DEM_GETFREEZEFRAMEDATABYDTC_SID, DEM_E_PARAM_LENGTH);
          retVal = DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
          break;
        #endif
        case DEM_GET_READEVDATA_WRONG_RECORDNUMBER:
          /* DEM_REPORT_ERROR(DEM_GETFREEZEFRAMEDATABYDTC_SID, DEM_E_PARAM_CONFIG); */
          retVal = DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER;  
          break;
        /* polyspace<RTE:UNR:Not a defect:No action planned> No problem. Unreachable code */
        /* polyspace-begin DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Default clause added because avoid compile error, no impact" */
        default:
          retVal = DEM_GET_FFDATABYDTC_WRONG_DTC;
          break;
        /* polyspace-end DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Default clause added because avoid compile error, no impact" */
      }
    }
  }
  return retVal;
}/* End Of API */
/*******************************************************************************
** Function Name        : Dem_GetSizeOfFreezeFrameByDTC                       **
**                                                                            **
** Service ID           : 0x1f                                                **
**                                                                            **
** Description          : The API shall be used to get the size of freeze     **
**                        data by DTC                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint32 DTC,                                         **
**                        Dem_DTCOriginType DTCOrigin,                        **
**                        uint8 RecordNumber                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint16* SizeOfFreezeFrame                           **
**                                                                            **
** Return parameter     : Dem_ReturnGetSizeOfFreezeFrameByDTCType             **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
**                        Dem_CalcSizeOfDID                                   **
*******************************************************************************/
FUNC(Dem_ReturnGetSizeOfFreezeFrameByDTCType, DEM_CODE)
Dem_GetSizeOfFreezeFrameByDTC(
  uint32 DTC, 
  Dem_DTCOriginType DTCOrigin,
  uint8 RecordNumber, 
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) SizeOfFreezeFrame)
{
  Dem_ReturnGetSizeOfFreezeFrameByDTCType retVal = DEM_GET_SIZEOFFF_WRONG_DTC;

  if (DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMEBYDTC_SID, DEM_E_UNINIT);
    retVal = DEM_GET_SIZEOFFF_WRONG_DTC;
  } 
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (NULL_PTR == SizeOfFreezeFrame)
  {
    DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMEBYDTC_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_GET_SIZEOFFF_WRONG_DTC;
  } 
  else if (!DEM_IF_DTCORIGIN_IS_VALID(DTCOrigin))
  {
    DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMEBYDTC_SID, DEM_E_PARAM_CONFIG);
    retVal = DEM_GET_SIZEOFFF_WRONG_DTCOR;
  }
  #endif  
  else
  {
    #if (DEM_DEV_ERROR_DETECT == STD_ON)
    Dem_EventIdType eventId = Dem_GetEventIdByDTC(DEM_GETSIZEOFFREEZEFRAMEBYDTC_SID, DTC);
    #else
    Dem_EventIdType eventId = Dem_GetEventIdByDTC(DTC);
    #endif
    /* if (DEM_FALSE == Dem_EventIdIsValid(eventId)) */
    if ((eventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == eventId))
    {
      DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMEBYDTC_SID, DEM_E_PARAM_CONFIG);       
      retVal = DEM_GET_SIZEOFFF_WRONG_DTC;
    } 
    else if ((boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(eventId, DTCOrigin))
    {
      DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMEBYDTC_SID, DEM_E_PARAM_CONFIG);       
      /* No destination of the event configured */
      retVal = DEM_GET_SIZEOFFF_WRONG_DTCOR;    
    }
    else if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP))
    {
      DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMEBYDTC_SID, DEM_E_PARAM_CONFIG);       
      retVal = DEM_GET_SIZEOFFF_WRONG_DTC; 
    }
    else
    {  
      #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0U) && (DEM_SIZE_OF_FREEZEFRAME > 0u))    
      uint16 FreezeFrameSize = 0U;    
      /* NOTE : Why DEM_DTC_ORIGIN_PERMANENT_MEMORY  is not checked in the KPIT source? */      
      if (E_OK == Dem_GetSizeOfFreezeFrameByRecord(eventId, RecordNumber, DTCOrigin, &FreezeFrameSize) )
      {        
        *SizeOfFreezeFrame = FreezeFrameSize; /* 0U(not stored) or valid size*/
        retVal = DEM_GET_SIZEOFFF_OK;
      }
      else
      #endif
      {
        DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMEBYDTC_SID, DEM_E_PARAM_CONFIG);
        retVal = DEM_GET_SIZEOFFF_WRONG_RNUM; 
      }
    }
  }
  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_GetExtendedDataRecordByDTC                      **
**                                                                            **
** Service ID           : 0x20                                                **
**                                                                            **
** Description          : This function shall be used to return the complete  **
**                        Extended Data Record for the requested DTC          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint32 DTC,                                         **
**                        Dem_DTCOriginType DTCOrigin,                        **
**                        uint8 ExtendedDataNumber                            **
**                                                                            **
** InOut parameter      : BufSize                                             **
**                                                                            **
** Output Parameters    : uint8* DestBuffer,                                  **
**                                                                            **
** Return parameter     : Dem_ReturnGetExtendedDataRecordByDTCType            **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                        Dem_GaaEDRecord                                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
*******************************************************************************/
FUNC(Dem_ReturnGetExtendedDataRecordByDTCType, DEM_CODE)
  Dem_GetExtendedDataRecordByDTC(
  uint32 DTC, 
  Dem_DTCOriginType DTCOrigin,
  uint8 ExtendedDataNumber, 
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Dem_ReturnGetExtendedDataRecordByDTCType retVal = DEM_RECORD_WRONG_NUMBER;
   
  if (DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETEXTENDEDDATARECORDBYDTC_SID, DEM_E_UNINIT);
    retVal = DEM_RECORD_WRONG_DTC;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((NULL_PTR == DestBuffer) || (NULL_PTR == BufSize))
  {
    DEM_REPORT_ERROR(DEM_GETEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_RECORD_WRONG_BUFFERSIZE;
  }
  else if (
    (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
    (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY) &&
    (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) &&
    (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY) )
  {
    DEM_REPORT_ERROR(DEM_GETEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_CONFIG);
    retVal = DEM_RECORD_WRONG_DTCORIGIN;
  }
  #endif  
  /* Dem239 : The values 0xFE and 0xFF are not allowed. Valid values are from 0x01 to 0xEF. */  
  else if (
    (ExtendedDataNumber > DEM_MAX_VALID_EXTENDED_RECORD_NUMBER) ||
    (ExtendedDataNumber < DEM_MIN_VALID_EXTENDED_RECORD_NUMBER))
  {
    DEM_REPORT_ERROR(DEM_GETEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_CONFIG);
    retVal = DEM_RECORD_WRONG_NUMBER;       
  }
  else
  { 
    #if (DEM_DEV_ERROR_DETECT == STD_ON)
    Dem_EventIdType eventId = Dem_GetEventIdByDTC(DEM_GETEXTENDEDDATARECORDBYDTC_SID, DTC);
    #else
    Dem_EventIdType eventId = Dem_GetEventIdByDTC(DTC);
    #endif
    /* if (DEM_FALSE == Dem_EventIdIsValid(eventId)) */
    if ((eventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == eventId))
    {
      DEM_REPORT_ERROR(DEM_GETEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_CONFIG);       
      retVal = DEM_RECORD_WRONG_DTC;
    } 
    else if ((boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(eventId, DTCOrigin))
    {
      DEM_REPORT_ERROR(DEM_GETEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_CONFIG);       
      /* No destination of the event configured */
      retVal = DEM_RECORD_WRONG_DTCORIGIN;    
    }
    else if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP))
    {
      DEM_REPORT_ERROR(DEM_GETEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_CONFIG);       
      retVal = DEM_RECORD_WRONG_DTC; 
    }
    else
    {  
      #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0U) && (DEM_SIZE_OF_EXTENDED_DATA > 0U))
      Dem_EventParameterPCType event = &Dem_Event[eventId - 1U];    
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
      {        
        Dem_ReturnReadEventDataType 
        result = Dem_ReadDataOfExtendedData(&Dem_EventRelatedData[event->e_PointToData], 
          DTCOrigin, ExtendedDataNumber, DestBuffer, BufSize);
        switch(result)
        {
          case DEM_GET_READEVDATA_OK:
            /* *BufSize is updated in the Dem_ReadDataOfFreezeFrame */
            retVal = DEM_RECORD_OK; 
            break;
          case DEM_GET_READEVDATA_NOT_STORED:
            /* [Dem631] If Dem_GetExtendedDataRecordByDTC is called with a valid DTC
             * and a valid extended data record number which is not stored,
             * the Dem shall return DEM_RECORD_OK and BufSize 0 (empty buffer). */          
            *BufSize = 0U;
            retVal = DEM_RECORD_OK; 
            break;
          case DEM_GET_READEVDATA_WRONG_RECORDNUMBER:
            /* DEM_REPORT_ERROR(DEM_GETEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_CONFIG); */
            /*No record number configured */
            retVal = DEM_RECORD_WRONG_NUMBER;
            break;
          /* polyspace<RTE:UNR:Not a defect:No action planned> No problem. Unreachable code */            
          case DEM_GET_READEVDATA_WRONG_BUFFERSIZE:
            DEM_REPORT_ERROR(DEM_GETEXTENDEDDATARECORDBYDTC_SID,  DEM_E_PARAM_LENGTH);    
            retVal = DEM_RECORD_WRONG_BUFFERSIZE;
            break;
          /* polyspace<RTE:UNR:Not a defect:No action planned> No problem. Unreachable code */
          default:
            retVal = DEM_RECORD_WRONG_NUMBER;
            break;
        }
      }
      #else      
      retVal = DEM_RECORD_WRONG_NUMBER; /* No extended data configured */
      #endif     
    }
  }

  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_GetSizeOfExtendedDataRecordByDTC                **
**                                                                            **
** Service ID           : 0x21                                                **
**                                                                            **
** Description          : The API shall be used to return the size of the     **
**                        requested Extended Data Record                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTC,                                                **
**                        DTCOrigin,                                          **
**                        ExtendedDataNumber                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint16* SizeOfExtendedDataRecord                    **
**                                                                            **
** Return parameter     : Dem_ReturnGetSizeOfExtendedDataRecordByDTCType      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* polyspace:begin<MISRA-C:5.1:Not a defect:Justify with annotations> This Identifier is Specification. */
FUNC(Dem_ReturnGetSizeOfExtendedDataRecordByDTCType, DEM_CODE)
Dem_GetSizeOfExtendedDataRecordByDTC(
  uint32 DTC, 
  Dem_DTCOriginType DTCOrigin,
  uint8 ExtendedDataNumber, 
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) SizeOfExtendedDataRecord)
{
  Dem_ReturnGetSizeOfExtendedDataRecordByDTCType retVal = DEM_GET_SIZEOFEDRBYDTC_W_DTC;

  /* Check module Initialization */
  if (DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_SID, DEM_E_UNINIT);
    retVal = DEM_GET_SIZEOFEDRBYDTC_W_DTC;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (NULL_PTR == SizeOfExtendedDataRecord)
  {
    DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_GET_SIZEOFEDRBYDTC_W_DTC;
  }   
  #endif
  /* Dem240 : Identification/Number of requested extended data record. Valid values are from 0x01 to0xEF. 
   * Additionally the values 0xFE and 0xFF are explicitly allowed to request the overall size of all OBD records / all records. 
   *  i.   1 <= n <= EF
   *  ii.  FE, FF */     
  else if (
    (DEM_MIN_VALID_EXTENDED_RECORD_NUMBER  > ExtendedDataNumber) 
    ||    
    (
      ((uint8)DEM_MAX_EXTENDED_RECORD_NUMBER != ExtendedDataNumber) &&  
      ((uint8)DEM_EXTENDED_DATA_NUMBER_OBD  != ExtendedDataNumber) &&
      (DEM_MAX_VALID_EXTENDED_RECORD_NUMBER  < ExtendedDataNumber)
    )
  )
  {
    DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_DATA);
    retVal = DEM_GET_SIZEOFEDRBYDTC_W_RNUM;           
  }
  else 
  {
    #if (DEM_DEV_ERROR_DETECT == STD_ON)
    Dem_EventIdType eventId = Dem_GetEventIdByDTC(DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_SID, DTC);
    #else
    Dem_EventIdType eventId = Dem_GetEventIdByDTC(DTC);
    #endif
    /* if (DEM_FALSE == Dem_EventIdIsValid(eventId)) */
    if ((eventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == eventId))
    {
      DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_CONFIG);
      retVal = DEM_GET_SIZEOFEDRBYDTC_W_DTC;
    }
    else if ((boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(eventId, DTCOrigin))
    {
      DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_CONFIG);       
      /* No destination of the event configured */
      retVal = DEM_GET_SIZEOFEDRBYDTC_W_DTCOR;    
    }
    else if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP))
    {
      DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_CONFIG);       
      retVal = DEM_GET_SIZEOFEDRBYDTC_W_DTC; 
    }
    else    
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0U) && (DEM_SIZE_OF_EXTENDED_DATA >  0U))    
    {
      Dem_EventRelatedDataPCType evData = NULL_PTR;
      Dem_EventParameterPCType event = &Dem_Event[eventId - 1U];
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
      { 
        evData = &Dem_EventRelatedData[event->e_PointToData];      

        /* #if (DEM_OBD_SUPPORT ==  STD_ON) */
        if (DEM_EXTENDED_DATA_NUMBER_OBD == ExtendedDataNumber)
        {
          /*  OBD is not supported yet */
          DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_DATA);
          retVal = DEM_GET_SIZEOFEDRBYDTC_W_DTC;
        }
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
        else if (evData->EDClassPos < Dem_Num_Of_ExtendedDataClass)
        {   
          /* Dem076
           * record number 0xFE: the size of all OBD stored extended data records(0x90 to 0xEF)
           * record number 0xFF: the size of all stored extended data records (0x01 to 0xEF)*/    
          Dem_SizeOfExtendedDataClassType extendedDataSize = 0U;
          Dem_NumOfExtendedDataRecordClassType numOfMatchedEDR = 0U;
          extendedDataSize =Dem_GetSizeOfExtendedData(&Dem_ExtendedDataClass[evData->EDClassPos], 
                    ExtendedDataNumber, &numOfMatchedEDR);
          if (0U != extendedDataSize)
          {
            if (DEM_NO_EVMEM_ENTRY == Dem_EvMemToEventMap[eventId])
            {
              *SizeOfExtendedDataRecord = 0x0; /* Event is not stored.*/
            }
            else
            {  
              /*SWS_Dem_00240:  Size of the requested extended data record(s) 
                including number of 'extended data record' */
              *SizeOfExtendedDataRecord = extendedDataSize + numOfMatchedEDR;
            }
            retVal = DEM_GET_SIZEOFEDRBYDTC_OK;
          }
          else
          {     
            DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_SID,DEM_E_PARAM_CONFIG);
            retVal = DEM_GET_SIZEOFEDRBYDTC_W_RNUM;
          }
        }
        else
        {
          retVal = DEM_GET_SIZEOFEDRBYDTC_W_DTC;
        }
      }
    }
    #else
    {
      DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDBYDTC_SID, DEM_E_PARAM_CONFIG);       
      retVal = DEM_GET_FFDATABYDTC_WRONG_DTC;    
    }
    #endif      
  }  
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid to 'Unreachable code' of the polyspace */
  return retVal;
}
/* polyspace:end<MISRA-C:5.1:Not a defect:Justify with annotations> This Identifier is Specification. */

/*******************************************************************************
** Function Name        : Dem_ClearDTC                                        **
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
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                        Dem_GulDemClearTimeCount                            **
**                        Dem_GblClearTimeStartObd                            **
**                        Dem_GusWarmUpCycleCount                             **
**                        Dem_GulTimeSinceMilOn                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
**                        Dem_BinarySearch                                    **
**                        Dem_GetDTCGroupId                                   **
*******************************************************************************/
FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_ClearDTC(uint32 DTC,
  Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
  Dem_ReturnClearDTCType retVal = DEM_CLEAR_FAILED;

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  if ((DEM_CLEARDTC_STATE_USER_CDD == Dem_ClearDtcState.cds_User) ||
    (DEM_CLEARDTC_STATE_USER_J1939DCM == Dem_ClearDtcState.cds_User) )
  {
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    retVal = DEM_CLEAR_PENDING; /* It means 'busy' state */
  }
  else /* DEM_CLEARDTC_STATE_USER_DCM or IDLE */
  {
    Dem_ClearDtcState.cds_User = DEM_CLEARDTC_STATE_USER_DCM;
#if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
    Dem_ClearDtcState.cds_DTCTypeFilter = 0U; /* Not used */
#endif
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    
    retVal = Dem_InternalClearDTC(DTC, DTCFormat, DTCOrigin);
    if (DEM_CLEAR_PENDING != retVal)
    {
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();    
      Dem_ClearDtcState.cds_User = DEM_CLEARDTC_STATE_USER_IDLE;
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

    }
  }
  
  return retVal;
}

/*******************************************************************************
** Function Name        : Dem_DcmCancelOperation                              **
**                                                                            **
** Service ID           : 0x2a                                                **
**                                                                            **
** Description          : This function shall be called to Cancel pending     **
**                        operation started from Dcm.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, DEM_CODE) Dem_DcmCancelOperation(void)
{
  /* Module initialization check */
  if(Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_DCMCANCELOPERATION_SID, DEM_E_UNINIT);
  }
  else
  {  
    Dem_EventIdType eventId;  
    SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
    Dem_ClearDtcState.cds_RequestCancel = DEM_TRUE;
    Dem_DTCFilterState.dfs_JobAction = DEM_JOB_CANCEL;
    SchM_Exit_Dem_REQUEST_DATA_PROTECTION();

    for (eventId = 1U; eventId <= Dem_Number_Of_Events; eventId++)
    {
      Dem_EvClearProcState(eventId, DEM_EVPROCSTATE_DTC_FILTER);
      Dem_EvClearProcState(eventId, DEM_EVPROCSTATE_INITMON_ONCLEARDTC);      
    }    
  }
}
/*******************************************************************************
** Function Name        : Dem_DisableDTCSetting                               **
**                                                                            **
** Service ID           : 0x24                                                **
**                                                                            **
** Description          : This function shall be called to disable the DTC    **
**                        setting for a DTC group                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCGroup, DTCKind                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_ReturnControlDTCSettingType                     **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_GblDisableDtcSettingAllDTC                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
**                        Dem_GetDTCGroupId                                   **
*******************************************************************************/
FUNC(Dem_ReturnControlDTCSettingType, DEM_CODE)Dem_DisableDTCSetting
  (Dem_DTCGroupType DTCGroup, Dem_DTCKindType DTCKind)
{
  Dem_ReturnControlDTCSettingType retVal = DEM_CONTROL_DTC_SETTING_OK;

  /* Module initialization check */
  if(Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_DISABLEDTCSETTING_SID, DEM_E_UNINIT);
    retVal = DEM_CONTROL_DTC_SETTING_N_OK;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((DTCKind != DEM_DTC_KIND_ALL_DTCS) &&
      (DTCKind != DEM_DTC_KIND_EMISSION_REL_DTCS))
  {
    DEM_REPORT_ERROR(DEM_DISABLEDTCSETTING_SID, DEM_E_PARAM_DATA);
    retVal = DEM_CONTROL_DTC_SETTING_N_OK;
  }
  else if ((DTCGroup != DEM_DTC_GROUP_EMISSION_REL_DTCS) &&
      (DTCGroup != DEM_DTC_GROUP_ALL_DTCS) &&
      (DTCGroup != DEM_DTC_GROUP_CHASSIS_DTCS) &&
      (DTCGroup != DEM_DTC_GROUP_BODY_DTCS) &&
      (DTCGroup != DEM_DTC_GROUP_POWERTRAIN_DTCS) && 
      (DTCGroup != DEM_DTC_GROUP_NETWORK_COM_DTCS))
  {
    DEM_REPORT_ERROR(DEM_DISABLEDTCSETTING_SID, DEM_E_PARAM_DATA);
    retVal = DEM_CONTROL_DTC_WRONG_DTCGROUP;
  }
  #endif  
  else if(DTCGroup == DEM_DTC_GROUP_ALL_DTCS)
  {
    uint8 i;
    /* Disable DTC setting of the All DTC's */
    Dem_GblDisableDtcSettingAllDTC = DEM_TRUE;
    Dem_GucDisableDtcSettingDTCKind = DTCKind;
  
    for(i = 0U; i < Dem_Max_Num_Grp_DTC; i++)
    {
      /* Disable DTC setting of the requested group of DTC's */
      Dem_GaaDisableDtcSettingGroupDTC[i] = DEM_TRUE;
    }
  }
  else
  {
    uint8 groupId = 0U;
  
    /* Check DTC group availability */
    if (E_OK == Dem_GetDTCGroupId(DTCGroup, &groupId))
    {    
      /* Disable DTC setting of the requested group of DTC's */
      Dem_GaaDisableDtcSettingGroupDTC[groupId] = DEM_TRUE;
      Dem_GucDisableDtcSettingDTCKind = DTCKind;
    }
    else
    {
      DEM_REPORT_ERROR(DEM_DISABLEDTCSETTING_SID, DEM_E_PARAM_DATA);
      retVal = DEM_CONTROL_DTC_WRONG_DTCGROUP;
    }
  }
  
  /* Return the value */
  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_EnableDTCSetting                                **
**                                                                            **
** Service ID           : 0x25                                                **
**                                                                            **
** Description          : This function shall be called to enable the DTC     **
**                        setting for a DTC group                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCGroup, DTCKind                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_ReturnControlDTCSettingType                     **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_GblDisableDtcSettingAllDTC                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
**                        Dem_GetIndexOfDTCGroup                              **
*******************************************************************************/
FUNC(Dem_ReturnControlDTCSettingType, DEM_CODE)
Dem_EnableDTCSetting(
  Dem_DTCGroupType DTCGroup, 
  Dem_DTCKindType DTCKind)
{
  Dem_ReturnControlDTCSettingType retVal = DEM_CONTROL_DTC_SETTING_OK;

  DEM_UNUSED(DTCKind);
    
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_ENABLEDTCSETTING_SID, DEM_E_UNINIT);
    retVal = DEM_CONTROL_DTC_SETTING_N_OK;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((DTCKind != DEM_DTC_KIND_ALL_DTCS) &&
      (DTCKind != DEM_DTC_KIND_EMISSION_REL_DTCS))
  { 
    DEM_REPORT_ERROR(DEM_ENABLEDTCSETTING_SID, DEM_E_PARAM_DATA);
    retVal = DEM_CONTROL_DTC_SETTING_N_OK;
  }
  else if (
    (DTCGroup != DEM_DTC_GROUP_EMISSION_REL_DTCS) &&
    (DTCGroup != DEM_DTC_GROUP_ALL_DTCS) &&
    (DTCGroup != DEM_DTC_GROUP_CHASSIS_DTCS) &&
    (DTCGroup != DEM_DTC_GROUP_BODY_DTCS) &&
    (DTCGroup != DEM_DTC_GROUP_POWERTRAIN_DTCS) && 
    (DTCGroup != DEM_DTC_GROUP_NETWORK_COM_DTCS))
  {
    DEM_REPORT_ERROR(DEM_ENABLEDTCSETTING_SID, DEM_E_PARAM_DATA);
    retVal = DEM_CONTROL_DTC_WRONG_DTCGROUP;
  }
  #endif
  else
  {    
    uint8 DTCGroupId = 0U;
    
    /* @IF_REQ: DTCKind should be processed. */
    if (DTCGroup == DEM_DTC_GROUP_ALL_DTCS) 
    {
      /* Enable DTC setting of the All DTC's */
      Dem_GblDisableDtcSettingAllDTC = DEM_FALSE;
      for(DTCGroupId = 0U; DTCGroupId < Dem_Max_Num_Grp_DTC; DTCGroupId++)
      {
        /* Enable DTC setting of the requested group of DTC's */
        Dem_GaaDisableDtcSettingGroupDTC[DTCGroupId] = DEM_FALSE;
      }        
    }
    else
    {
      /* Check DTC group availability */
      if (E_OK == Dem_GetDTCGroupId(DTCGroup, &DTCGroupId))
      {    
        /* Enable DTC setting of the requested group of DTC's */
        Dem_GaaDisableDtcSettingGroupDTC[DTCGroupId] = DEM_FALSE;
      }
      else
      {
        DEM_REPORT_ERROR(DEM_DISABLEDTCSETTING_SID, DEM_E_PARAM_DATA);
        retVal = DEM_CONTROL_DTC_WRONG_DTCGROUP;
      }
    }
  }
  
  /* Return the value */
  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_DisableDTCRecordUpdate                          **
**                                                                            **
** Service ID           : 0x1a                                                **
**                                                                            **
** Description          : Disables the event memory update of a speci?c DTC   **
**                        (only one at one time).                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTC, DTCOrigin                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_ReturnDisableDTCRecordUpdateType                **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
**                        SchM_Exit_Dem_REQUEST_RECORD_PROTECTION             **
*******************************************************************************/
FUNC(Dem_ReturnDisableDTCRecordUpdateType, DEM_CODE)Dem_DisableDTCRecordUpdate
  (uint32 DTC, Dem_DTCOriginType DTCOrigin)
{
  Dem_ReturnDisableDTCRecordUpdateType retVal = DEM_DISABLE_DTCRECUP_OK;
  
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_DISABLEDTCRECORDUPDATE_SID, DEM_E_UNINIT);
    retVal = DEM_DISABLE_DTCRECUP_PENDING;
  }
  else
  {
    Dem_EventIdType eventId;
    switch( Dem_GetConditionOfDTCRecordUpdate(DTC,DTCOrigin))
    {
      case DEM_CONDITIONDTCRECUP_NO_DTC:      
        #if (DEM_DEV_ERROR_DETECT == STD_ON)
        eventId = Dem_GetEventIdByDTC(DEM_DISABLEDTCRECORDUPDATE_SID, DTC);
        #else
        eventId = Dem_GetEventIdByDTC(DTC);
        #endif  
        /* if (DEM_FALSE == Dem_EventIdIsValid(eventId)) */
        if ((eventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == eventId))
        {
          DEM_REPORT_ERROR(DEM_DISABLEDTCRECORDUPDATE_SID, DEM_E_PARAM_CONFIG);       
          retVal = DEM_DISABLE_DTCRECUP_WRONG_DTC;
        } 
        else if ((boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(eventId, DTCOrigin))
        {
          DEM_REPORT_ERROR(DEM_DISABLEDTCRECORDUPDATE_SID, DEM_E_PARAM_CONFIG);       
          /* No destination of the event configured */
          retVal = DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN;    
        }
        else if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP))
        {
          DEM_REPORT_ERROR(DEM_DISABLEDTCRECORDUPDATE_SID, DEM_E_PARAM_CONFIG);       
          retVal = DEM_DISABLE_DTCRECUP_WRONG_DTC; 
        }
        else
        {
          SchM_Enter_Dem_REQUEST_RECORD_PROTECTION();
          #if(DEM_OBD_SUPPORT == STD_ON)
          if (DEM_TRUE == Dem_DTCFormatIsValid(eventId, DEM_DTC_FORMAT_OBD))
          {
            /* Load the DTC for which record update to be disabled */
            Dem_GstRecordDisableDTC.usObdDtc = (uint16)DTC;
          }
          else
          #endif
          {
            /* Load the DTC for which record update to be disabled */
            Dem_GstRecordDisableDTC.ulUdsDtc = DTC;
          }      
          /* Load the origin of DTC for which record update to be disabled */
          Dem_GstRecordDisableDTC.ddDtcOrigin = DTCOrigin;  
          
          SchM_Exit_Dem_REQUEST_RECORD_PROTECTION();

          /* retVal = DEM_DISABLE_DTCRECUP_OK; */
        }        
        break;
        
      case DEM_CONDITIONDTCRECUP_DISABLED_DTC:
        /* retVal = DEM_DISABLE_DTCRECUP_OK; */
        break;
        
      /**
       * [SWS_Dem_00648] If development error detection is enabled and 
       * the function Dem_DcmDisableDTCRecordUpdate is called while 
       * another DTC is locked, the Dem module shall set the error code 
       * DEM_E_WRONG_CONDITION (refer also to [SWS_Dem_00370]) 
       */      
      case DEM_CONDITIONDTCRECUP_NO_MATCHING_DTC:
        DEM_REPORT_ERROR(DEM_DISABLEDTCRECORDUPDATE_SID, DEM_E_WRONG_CONDITION);
        retVal = DEM_DISABLE_DTCRECUP_PENDING;
        break;
      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */        
      /* polyspace-begin DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Default clause added because avoid compile error, no impact" */
      default: break;
      /* polyspace-end DEFECT:DEAD_CODE CERT-C:MSC12-C [Justified:Low] "Default clause added because avoid compile error, no impact" */
    }
  }
  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_EnableDTCRecordUpdate                           **
**                                                                            **
** Service ID           : 0x1b                                                **
**                                                                            **
** Description          : Enables the event memory update of the DTC disabled **
**                        by Dem_DcmDisableDTCRecordUpdate() before.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
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
**                        (void)Det_ReportError                               **
**                        SchM_Exit_Dem_REQUEST_RECORD_PROTECTION()           **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_EnableDTCRecordUpdate(void)
{
  Std_ReturnType retVal = E_OK;
  
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_ENABLEDTCRECORDUPDATE_SID, DEM_E_UNINIT);
    retVal = E_NOT_OK; 
  }
  else
  {
    SchM_Enter_Dem_REQUEST_RECORD_PROTECTION();
    #if(DEM_OBD_SUPPORT == STD_ON)
    /* Enable the record update */
    Dem_GstRecordDisableDTC.usObdDtc = DEM_ZERO;
  
    Dem_GstRecordDisableDTC.ulUdsDtc = DEM_ZERO;
    #else
    /* Enable the record update */
    Dem_GstRecordDisableDTC.ulUdsDtc = DEM_ZERO;
    #endif
  
    /* Clear the DTC origin */
    Dem_GstRecordDisableDTC.ddDtcOrigin = DEM_ZERO;
  
    SchM_Exit_Dem_REQUEST_RECORD_PROTECTION();
  }
  /* @IF_REQ : 
   * AR 4.2.1 SWS_Dem_00234
   * Std_ReturnType Always E_OK is returned. */
  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_GetFunctionalUnitOfDTC                          **
**                                                                            **
** Service ID           : 0x34                                                **
**                                                                            **
** Description          : This Gets the functional unit of the requested DTC  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTC                                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DTCFunctionalUnit                                   **
**                                                                            **
** Return parameter     : Dem_ReturnGetFunctionalUnitOfDTCType                **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
FUNC(Dem_ReturnGetFunctionalUnitOfDTCType, DEM_CODE)
  Dem_GetFunctionalUnitOfDTC(uint32 DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCFunctionalUnit)
{
  Dem_ReturnGetFunctionalUnitOfDTCType retVal = DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC;

  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_GETFUNCTIONALUNITOFDTC_SID, DEM_E_UNINIT);
    retVal = DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC;
  }                                                                       
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (
    (DTC == DEM_DTC_GROUP_EMISSION_REL_DTCS) ||
    (DTC == DEM_DTC_GROUP_ALL_DTCS) ||
    (DTC == DEM_DTC_GROUP_CHASSIS_DTCS) ||
    (DTC == DEM_DTC_GROUP_BODY_DTCS) ||
    (DTC == DEM_DTC_GROUP_POWERTRAIN_DTCS) ||
    (DTC == DEM_DTC_GROUP_NETWORK_COM_DTCS))
  {
    DEM_REPORT_ERROR(DEM_GETFUNCTIONALUNITOFDTC_SID, DEM_E_PARAM_DATA);
    retVal = DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC;
  }
  else if (DTCFunctionalUnit == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_GETFUNCTIONALUNITOFDTC_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC;
  }
  #endif  
  else
  {
    Dem_CombinedDtcPCType cbDTC = Dem_GetDtcByDtcId(DTC);    
    if (NULL_PTR == cbDTC)
    {
      DEM_REPORT_ERROR(DEM_GETFUNCTIONALUNITOFDTC_SID, DEM_E_PARAM_CONFIG);
      /* retVal = DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC; */
    }  
    else
    {
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
      *DTCFunctionalUnit = cbDTC->ucDtcFunctionalUnit;
      retVal = DEM_GET_FUNCTIONALUNITOFDTC_OK;
    }                                                                        
  }
  
  return retVal;
}
/*******************************************************************************
** Function Name        : Dem_GetFreezeFrameDataByRecord                      **
**                                                                            **
** Service ID           : 0x1C                                                **
**                                                                            **
** Description          : Gets DTC and its associated freeze frame record by  **
**                        absolute record number. The function stores the data**
**                        in the provided DestBuffer.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RecordNumber, DTCOrigin                             **
**                                                                            **
** InOut parameter      : BufSize                                             **
**                                                                            **
** Output Parameters    : DTC, DestBuffer                                     **
**                                                                            **
** Return parameter     : Dem_ReturnGetFreezeFrameDataByRecordType            **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                               **
**                                                                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if (DEM_OBD2_SUPPORT == STD_ON) /* unused macro || (DEM_RECORD_UNIQUE_SERVER == STD_ON)*/
FUNC(Dem_ReturnGetFreezeFrameDataByRecordType, DEM_CODE)
 Dem_GetFreezeFrameDataByRecord(
  uint8 RecordNumber,
  Dem_DTCOriginType DTCOrigin, 
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  P2VAR (uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Dem_ReturnGetFreezeFrameDataByRecordType 
    retVal = DEM_GET_FFBYRECORD_WRONG_RECORD;

  /* 
    1. Refer to Dcm SWS 7.4.2.5.10 
    " Due to DEM limitati on, the diagnostic service $19 05 is limited to the 
     OBD legislative freeze frame.
    
    2.  Refer to RfC  43992 :[Dem] Support of absolute record numbers ($19 03 and $19 05) 
    
    3 Dem_GetFreezeFrameDataByRecord is renamed  to Dem_DcmGetOBDFreezeFrameData()
      in the AUTOSAR R4.1.2
  */
  if (DEM_OBD_RECORD_NUMBER == RecordNumber)
  {
    retVal = Dem_DcmGetOBDFreezeFrameData(DTC, DestBuffer, BufSize); 
  }

  DEM_UNUSED(DTCOrigin);  
  
  return retVal;
}/* End the function*/
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

