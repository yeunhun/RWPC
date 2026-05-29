/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_J1939DcmIf.c                                              **
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
** Revision  Date          By          Description                            **
********************************************************************************
** 3.3.2    16-07-2021    LanhLT(FPT)    Changes made As per Redmine #30852   **
**                                                                            **
** 1.3.4    18-02-2021    EunKyung.Kim   Changes made As per Redmine #25380   **
**                                                                            **
** 1.3.3    04-09-2020   EunKyung.Kim   Changes made As per Redmine #25254    **
**                                                                            **
** 1.3.2    06-01-2020    EunKyung.Kim    Changes made As per Redmine #20595  **
**                                                                            **    
** 1.3.1    31-01-2019    EunKyung.Kim    Changes made As per Redmine #14481  **
**                                                                            **
** 1.3.0    10-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.2.7     30-11-2018  EunKyung.Kim  Changes made As per Redmine #14901     **
**                                                                            **
** 1.2.6     02-02-2018  EunKyung.Kim  Changes made As per Redmine #11274     **
**                                                                            **
** 1.2.5     31-08-2017  EunKyung.Kim  Changes made As per Redmine #9495      **
**                                                                            **
** 1.2.4     20-07-2017  EunKyung.Kim  Changes made As per Redmine #9294      **
**                                                                            **
** 1.2.3     30-12-2016  YoungJin.Yun  Changes made As per Redmine #6409      **
**                                                                            **
** 1.2.1     30-10-2016  YoungJin.Yun  Changes made As per Redmine #6188      **
**                                                                            **
** 1.2.0     30-09-2016  YoungJin.Yun  Changes made As per Redmine #5921      **
**                                                                            **
** 1.1.0     30-08-2016  YoungJin.Yun  Changes made As per Redmine #5011      **
**                                                                            **
** 1.0.0     10-06-2016  Youngjin.Yun  Initial Version                        **
*******************************************************************************/ 

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
  
/* 
   polyspace:begin<MISRA-C:5.1:Not a defect:Justify with annotations> Number of character is AUTOSAR standard
   polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect
   polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> Not a defect
   polyspace:begin<MISRA-C:8.8:Not a defect:Justify with annotations> Not a defect 
*/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */  

#include "Dem.h"                /* DEM module Header File */
#include "Dem_Ram.h"            /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                /* Det Header File */
#endif
#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */

#include "Dem_Types.h"
#include "Dem_Event.h"
#include "Dem_Dtc.h"
#include "Dem_EventMemory.h"
#include "Dem_EventRelatedData.h"

#if (DEM_J1939_SUPPORT == STD_ON)
#include "Dem_J1939Types.h"
#include "Dem_J1939Ram.h"

#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

static CONST(Dem_J1939LampType, DEM_CONST) Dem_J1939LampId = {

#ifdef DEM_MIL_INDICATORID
  DEM_MIL_INDICATORID,
#else
  DEM_J1939LAMP_NOT_AVAILABLE,
#endif

#ifdef DEM_J1939_REDSTOP_LAMP_INDICATORID
  DEM_J1939_REDSTOP_LAMP_INDICATORID,
#else
  DEM_J1939LAMP_NOT_AVAILABLE,
#endif

#ifdef DEM_J1939_AMBERWARNING_LAMP_INDICATORID
  DEM_J1939_AMBERWARNING_LAMP_INDICATORID,
#else
  DEM_J1939LAMP_NOT_AVAILABLE,
#endif

#ifdef DEM_J1939_PROTECT_LAMP_INDICATORID
  DEM_J1939_PROTECT_LAMP_INDICATORID
#else
  DEM_J1939LAMP_NOT_AVAILABLE
#endif
};


#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" 

static VAR(Dem_J1939DTCFilterStateType, DEM_VAR)  Dem_J1939DTCFilterState;

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
static FUNC(void, DEM_CODE) Dem_J1939CountAndStoreFilterDtc(void);

FUNC(Std_ReturnType, DEM_CODE) Dem_GetJ1939LampStatus(
  Dem_EventIdType EventId,
  P2VAR (Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_APPL_DATA) LampStatus);

#define DEM_START_SEC_CODE
#include "MemMap.h"
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
static FUNC(void, DEM_CODE) Dem_J1939CountAndStoreFilterDtc(void)
{
  #if(DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)

  Dem_NumOfDTCValueType dtcLoc = 0u;
  boolean milOn = DEM_FALSE;

  /* Loop can be cancelled by Dem_DcmCancelOperation (done DEM_JOB_RUNNING->DEM_JOB_CANCEL)*/
  for (dtcLoc = 0u; 
      (dtcLoc < Dem_Max_Number_Of_DTC) && (Dem_J1939DTCFilterState.j1939_JobAction == DEM_JOB_RUNNING); 
      dtcLoc++)
  {
    P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) cbDTC = &Dem_GaaCombinedDtc[dtcLoc];
    Dem_EventIdType eventId = Dem_GetFirstEventOfDTC(cbDTC);
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid to 'Unreachable code' of the polyspace */
    if ((DEM_NO_DTC != cbDTC->J1939DTCValue) && (DEM_NO_EVENT != eventId))
    {      
      #if(DEM_DTC_SUPPRESSION_SUPPORT == STD_ON)      
      /* Refer to Dem_SetDTCSuppression */
      if (DEM_FALSE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP)) 
      #endif
      {
        Dem_UdsStatusByteType dtcStatus = Dem_GetDTCStatus(eventId);                
        if ((cbDTC->ddDtcKind == Dem_J1939DTCFilterState.j1939_DTCKind) || (DEM_DTC_KIND_ALL_DTCS == Dem_J1939DTCFilterState.j1939_DTCKind) )
        {
          /* DM01 , DM12(OBD) Active DTC */
          if (DEM_J1939DTC_ACTIVE == Dem_J1939DTCFilterState.j1939_DTCStatusFilter)
          {
            if(Dem_J1939LampId.MilId == Dem_GaaIndicatorList[Dem_Event[eventId-1U].e_PointToIndicator].IndicatorIdRef)
            {
              milOn = Dem_EvMem_GetIndicatorAttStatus(eventId,  Dem_GaaIndicatorList[Dem_Event[eventId-1U].e_PointToIndicator].IndicatorAttStatusPos);
            }
              
            if (DEM_TRUE == cbDTC->J1939DM1ActCondCDTC)
            {              
              if (((dtcStatus & (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDTC)) == (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDTC)) || (milOn == DEM_TRUE))
              {
                Dem_EvSetProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);             
                Dem_J1939DTCFilterState.j1939_NumOfFilteredDTC++;
              }
            }
            else
            {
              if (0U != (dtcStatus & DEM_UDS_STATUS_TF))
              {
                Dem_EvSetProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);             
                Dem_J1939DTCFilterState.j1939_NumOfFilteredDTC++;
              }
            }
            
          }
          /* DM02 , DM23(OBD) */
          else if (DEM_J1939DTC_PREVIOUSLY_ACTIVE == Dem_J1939DTCFilterState.j1939_DTCStatusFilter)
          {
            if(Dem_J1939LampId.MilId == Dem_GaaIndicatorList[Dem_Event[eventId-1U].e_PointToIndicator].IndicatorIdRef)
            {
              milOn = Dem_EvMem_GetIndicatorAttStatus(eventId,  Dem_GaaIndicatorList[Dem_Event[eventId-1U].e_PointToIndicator].IndicatorAttStatusPos);
            }
            
            if (((dtcStatus & (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_CDTC)) == DEM_UDS_STATUS_CDTC) && (milOn == DEM_FALSE))
            {
              Dem_EvSetProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
              Dem_J1939DTCFilterState.j1939_NumOfFilteredDTC++;
            }
          }
          /* DM27, DM6(OBD) */
          else if (DEM_J1939DTC_PENDING == Dem_J1939DTCFilterState.j1939_DTCStatusFilter)
          {            
            if ((dtcStatus & DEM_UDS_STATUS_PDTC) == DEM_UDS_STATUS_PDTC)
            {
              Dem_EvSetProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
              Dem_J1939DTCFilterState.j1939_NumOfFilteredDTC++;
            }
          }
          /* DM28(OBD) */
          else if (DEM_J1939DTC_PERMANENT == Dem_J1939DTCFilterState.j1939_DTCStatusFilter)
          { 
            #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))           
            if(DEM_NO_EVMEM_ENTRY != Dem_EvMem_FindPerMemLoc(eventId))
            {
              Dem_EvSetProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
              Dem_J1939DTCFilterState.j1939_NumOfFilteredDTC++;
            }
            #endif
          } 
          /* DM35 */
          else if (DEM_J1939DTC_CURRENTLY_ACTIVE == Dem_J1939DTCFilterState.j1939_DTCStatusFilter)
          {            
            if ((dtcStatus & DEM_UDS_STATUS_TF) == DEM_UDS_STATUS_TF)
            {
              Dem_EvSetProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
              Dem_J1939DTCFilterState.j1939_NumOfFilteredDTC++;
            }
          }

          else
          {
          
          }
                                     
        }
        else
        {

        }
      }
    }
  }
  #endif

  SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
  /* polyspace<RTE:UNR:Not a defect:No action planned> if-condition will evaluate to false if Dem_DcmCancelOperation is called by Dcm */         
  if (DEM_JOB_RUNNING == Dem_J1939DTCFilterState.j1939_JobAction)
  {
    Dem_J1939DTCFilterState.j1939_JobAction = DEM_JOB_DONE;
  }
  SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
}


/*******************************************************************************
** Function Name        : Dem_MainFunction                                    **
**                                                                            **
** Service ID           : 0x55                                                **
**                                                                            **
** Description          : Interface for BSW Components to report Errors       **
**                        during start up (even before DEM initialization)    **
**                                                                            **
** Timing:              : FIXED_CYCLIC                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GblMilStarted                                   **
**                        Dem_GulTimeSinceMilOn                               **
**                        Dem_GulDemTimeObdmsCount                            **
**                        Dem_GucMilonFlag                                    **
**                        Dem_GblClearTimeStartObd                            **
**                        Dem_GulDemClearTimeCount                            **
**                        Dem_GulDemTimeObdSecCount                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        Dem_ProcessDebounceTimer                            **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, DEM_CODE) Dem_J1939MainFunction(void)
{
  /* Apply the filter mask and get the number of filtered DTC */
  SchM_Enter_Dem_REQUEST_DATA_PROTECTION();       
  if (Dem_J1939DTCFilterState.j1939_JobAction == DEM_JOB_TRIGGER)
  {
    Dem_J1939DTCFilterState.j1939_JobAction = DEM_JOB_RUNNING;
    SchM_Exit_Dem_REQUEST_DATA_PROTECTION(); 
    Dem_J1939CountAndStoreFilterDtc();
  }
  else
  {
    SchM_Exit_Dem_REQUEST_DATA_PROTECTION();       
  }
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dem_J1939DcmSetDTCFilter                            **
**                                                                            **
** Service ID           : 0x90                                                **
**                                                                            **
** Description          : The function sets the DTC filter for a specific node**
**                        and returns the composite lamp status of the        **
**                        filtered DTCs.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input parameter      : DTCStatusFilter                                     **
**                         The following types are available:                 **
**                         DEM_J1939DTC_ACTIVE                                **
**                         DEM_J1939DTC_PREVIOUSLY_ACTIVE                     **
**                         DEM_J1939DTC_PENDING                               **
**                         DEM_J1939DTC_PERMANENT                             **
**                         DEM_J1939DTC_CURRENTLY_ACTIVE                      **
**                                                                            **
**                        DTCKind                                             **
**                         Defines the functional group of DTCs to be reported**
**                         (e.g. all DTC, OBD-relevant DTC)                   **
**                                                                            **
**                        node                                                **
**                         Nm node Id                                         **
**                                                                            **
** Output Parameters    : LampStatus                                          **
**                         bits 8-7 - Malfunction Indicator Lamp Status       **
**                         bits 6-5 - Red Stop Lamp Status                    **
**                         bits 4-3 - Amber Warning Lamp Status               **
**                         bits 2-1 - Protect Lamp Status                     **
**                                                                            **
**                         bits 8-7 - Flash Malfunction Indicator Lamp        **
**                         bits 6-5 - Flash Red Stop Lamp                     **
**                         bits 4-3 - Flash Amber WarningLamp                 **
**                         bits 2-1 - Flash Protect Lamp                      **
**                                                                            **
** Return parameter     : Dem_ReturnSetFilterType                             **
**                         DEM_FILTER_ACCEPTED                                **
**                         DEM_WRONG_FILTER                                   **
**                                                                            **
** Preconditions        : The API Dem_Init()                                  **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
FUNC(Dem_ReturnSetFilterType, DEM_CODE) 
Dem_J1939DcmSetDTCFilter(
  Dem_J1939DcmDTCStatusFilterType DTCStatusFilter,
  Dem_DTCKindType DTCKind,
  uint8 NodeAddress,
  Dem_J1939DcmLampStatusType* LampStatus)  
{
  Dem_ReturnSetFilterType retVal = DEM_WRONG_FILTER;
  
  /* Module initialization check */
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMSETDTCFILTER_SID, DEM_E_UNINIT);
    retVal =  DEM_WRONG_FILTER;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  /* LampStatus check */
  else if (NULL_PTR == LampStatus)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMSETDTCFILTER_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_WRONG_FILTER;
  }
  /* DTCKind check */
  else if (
    (DTCKind != DEM_DTC_KIND_ALL_DTCS) &&
    (DTCKind != DEM_DTC_KIND_EMISSION_REL_DTCS))
  {
    DEM_REPORT_ERROR(DEM_J1939DCMSETDTCFILTER_SID, DEM_E_PARAM_DATA);
    retVal = DEM_WRONG_FILTER;
  }
  /* FilterwithSeverity input is not defined */
  else if (
    (DEM_J1939DTC_ACTIVE != DTCStatusFilter) &&
    (DEM_J1939DTC_PREVIOUSLY_ACTIVE != DTCStatusFilter) &&
    (DEM_J1939DTC_PENDING != DTCStatusFilter) &&
    (DEM_J1939DTC_PERMANENT != DTCStatusFilter) &&
    (DEM_J1939DTC_CURRENTLY_ACTIVE != DTCStatusFilter))
  {
    DEM_REPORT_ERROR(DEM_J1939DCMSETDTCFILTER_SID, DEM_E_PARAM_DATA);
    retVal = DEM_WRONG_FILTER;
  }
  #endif  
  else  /* node : N/A */
  {
    /*----------------------+-------------------------+-----------------+-------------------------+
     |  SetFilter Parameter |  DTC Status filter      | further filter  | DM representation       |
     |                      |                         | criteria        +---------+---------------+
     |                      |                         |                 |All DTCs | EmissionsDTCs |
     +----------------------+-------------------------+-----------------+---------+---------------+
     | DEM_J1939DTC_ACTIVE  | (ConfirmedDTC == 1      | n/a             |DM01     |DM12           |
     |                      | AND TestFailed == 1) OR |                 |         |               |
     |                      | MIL_ON                  |                 |         |               |
     +----------------------+-------------------------+-----------------+---------+---------------+
     | DEM_J1939DTC_        | ConfirmedDTC == 1 AND   | n/a             |DM02     |DM23           |
     | PREVIOUSLY_ACTIVE    | TestFailed == 0 AND     |                 |         |               |
     |                      | MIL_OFF                 |                 |         |               |
     +----------------------+-------------------------+-----------------+---------+---------------+
     | DEM_J1939DTC_PENDING | PendingDTC == 1         | n/a             |DM27     |DM06           |
     +----------------------+-------------------------+-----------------+---------+---------------+
     | DEM_J1939DTC_        | n/a                     | permanent       |n/a      |DM28           |
     | PERMANENT            |                         | memory          |         |               |
     |                      |                         | entry           |         |               |
     |                      |                         | available       |         |               |
     +----------------------+-------------------------+-----------------+---------+---------------+
     | DEM_J1939DTC         | TestFailed == 1         | n/a             |DM35     |n/a            |   
     |  _CURRENTLY_ACTIVE   |                         |                 |         |               |
     +----------------------+-------------------------+-----------------+---------+---------------+*/

    /* lamp Status 
     Unavailable / Do Not Flash (0x03) 
     Slow Flash (0x00)
     Fast Flash (0x01) 
    */
    if ((DEM_J1939DTC_ACTIVE == DTCStatusFilter) ||
        (DEM_J1939DTC_PREVIOUSLY_ACTIVE == DTCStatusFilter) || (DEM_J1939DTC_CURRENTLY_ACTIVE == DTCStatusFilter) ||
        (DEM_J1939DTC_PENDING == DTCStatusFilter) || (DEM_J1939DTC_PERMANENT == DTCStatusFilter))
    {
      Dem_EventIdType eventId;
      boolean MIL = DEM_J1939LAMP_OFF;
      boolean RedStopLamp = DEM_J1939LAMP_OFF;
      boolean WarningLamp = DEM_J1939LAMP_OFF;
      boolean ProtectLamp = DEM_J1939LAMP_OFF;

      Dem_IndicatorStatusType MILStatus = DEM_INDICATOR_OFF;
      Dem_IndicatorStatusType RedStopLampStatus = DEM_INDICATOR_OFF;
      Dem_IndicatorStatusType WarningLampStatus = DEM_INDICATOR_OFF;
      Dem_IndicatorStatusType ProtectLampStatus = DEM_INDICATOR_OFF;
  
      for (eventId = 1U; eventId <= Dem_Number_Of_Events; eventId++)
      {
        Dem_EvClearProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
      }
      
      if (DEM_J1939LAMP_NOT_AVAILABLE != Dem_J1939LampId.MilId)
      {
        (void)Dem_GetIndicatorStatus((uint8)Dem_J1939LampId.MilId,&MILStatus);
      }
      if (DEM_J1939LAMP_NOT_AVAILABLE != Dem_J1939LampId.RedStopLampId)
      {
        (void)Dem_GetIndicatorStatus((uint8)Dem_J1939LampId.RedStopLampId,&RedStopLampStatus);
      }
      if (DEM_J1939LAMP_NOT_AVAILABLE != Dem_J1939LampId.WarningLampId)
      {      
        (void)Dem_GetIndicatorStatus((uint8)Dem_J1939LampId.WarningLampId,&WarningLampStatus);
      }
      if (DEM_J1939LAMP_NOT_AVAILABLE != Dem_J1939LampId.ProtectLampId)
      {      
        (void)Dem_GetIndicatorStatus((uint8)Dem_J1939LampId.ProtectLampId,&ProtectLampStatus);      
      }

      /*  MIL */
      if (DEM_INDICATOR_SLOW_FLASH == MILStatus)
      {
        MILStatus = DEM_J1939LAMP_SLOW_FLASH;
        MIL = DEM_J1939LAMP_ON;
      }
      else if (DEM_INDICATOR_FAST_FLASH == MILStatus)
      {
        MILStatus = DEM_J1939LAMP_FAST_FLASH;
        MIL = DEM_J1939LAMP_ON;
      }
      else if (DEM_INDICATOR_CONTINUOUS == MILStatus)
      {
        MILStatus = DEM_J1939LAMP_DO_NOT_FLASH;
        MIL = DEM_J1939LAMP_ON;
      }      
      else 
      {
        MILStatus = DEM_J1939LAMP_DO_NOT_FLASH;
        MIL = DEM_J1939LAMP_OFF;
      }

      /*  Red Stop Lamp */
      if (DEM_INDICATOR_SLOW_FLASH == RedStopLampStatus)
      {
        RedStopLampStatus = DEM_J1939LAMP_SLOW_FLASH;
        RedStopLamp = DEM_J1939LAMP_ON;
      }
      else if (DEM_INDICATOR_FAST_FLASH == RedStopLampStatus)
      {
        RedStopLampStatus = DEM_J1939LAMP_FAST_FLASH;
        RedStopLamp = DEM_J1939LAMP_ON;
      }
      else if (DEM_INDICATOR_CONTINUOUS == RedStopLampStatus)
      {
        RedStopLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
        RedStopLamp = DEM_J1939LAMP_ON;
      }
      else 
      {
        RedStopLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
        RedStopLamp = DEM_J1939LAMP_OFF;
      }
      /*  Amber Warning Lamp */
      if (DEM_INDICATOR_SLOW_FLASH == WarningLampStatus)
      {
        WarningLampStatus = DEM_J1939LAMP_SLOW_FLASH;
        WarningLamp = DEM_J1939LAMP_ON;
      }
      else if (DEM_INDICATOR_FAST_FLASH == WarningLampStatus)
      {
        WarningLampStatus = DEM_J1939LAMP_FAST_FLASH;
        WarningLamp = DEM_J1939LAMP_ON;
      }
      else if (DEM_INDICATOR_CONTINUOUS == WarningLampStatus)
      {
        WarningLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
        WarningLamp = DEM_J1939LAMP_ON;
      }
      else 
      {
        WarningLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
        WarningLamp = DEM_J1939LAMP_OFF;
      }
      /*   Protect Lamp */
      if (DEM_INDICATOR_SLOW_FLASH == ProtectLampStatus)
      {
        ProtectLampStatus = DEM_J1939LAMP_SLOW_FLASH;
        ProtectLamp = DEM_J1939LAMP_ON;
      }
      else if (DEM_INDICATOR_FAST_FLASH == ProtectLampStatus)
      {
        ProtectLampStatus = DEM_J1939LAMP_FAST_FLASH;
        ProtectLamp = DEM_J1939LAMP_ON;
      }
      else if (DEM_INDICATOR_CONTINUOUS == ProtectLampStatus)
      {
        ProtectLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
        ProtectLamp = DEM_J1939LAMP_ON;
      }
      else 
      {
        ProtectLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
        ProtectLamp = DEM_J1939LAMP_OFF;
      }

      *LampStatus = (
      (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)MIL <<  (Dem_J1939DcmLampStatusType)(BIT_POS_6 + 0U)) | /* Flash Malfunction Indicator Lamp  */ 
      (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)RedStopLamp  <<  (Dem_J1939DcmLampStatusType)(BIT_POS_4 + 0U))      | /* Flash Red Stop Lamp  */ 
      (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)WarningLamp  <<  (Dem_J1939DcmLampStatusType)(BIT_POS_2 + 0U))      | /* Flash Amber Warning Lamp   */ 
      (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)ProtectLamp  <<  (Dem_J1939DcmLampStatusType)(BIT_POS_0 + 0U))      | /* Flash Protect Lamp */ 

      (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)MILStatus <<  (Dem_J1939DcmLampStatusType)(BIT_POS_6 + 8U)) | /* Flash Malfunction Indicator Lamp Status */ 
      (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)RedStopLampStatus   <<  (Dem_J1939DcmLampStatusType)(BIT_POS_4 + 8U))        | /* Flash Red Stop Lamp Status */ 
      (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)WarningLampStatus   <<  (Dem_J1939DcmLampStatusType)(BIT_POS_2 + 8U))        | /* Flash Amber Warning Lamp  Status */ 
      (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)ProtectLampStatus   <<  (Dem_J1939DcmLampStatusType)(BIT_POS_0 + 8U)));  /* Flash Protect Lamp Status */ 
      
      Dem_J1939DTCFilterState.j1939_DTCStatusFilter = DTCStatusFilter;               
      Dem_J1939DTCFilterState.j1939_DTCKind = DTCKind;               
      
      Dem_J1939DTCFilterState.j1939_JobAction = DEM_JOB_TRIGGER;
      Dem_J1939DTCFilterState.j1939_NumOfFilteredDTC = 0U;  
 
      retVal = DEM_FILTER_ACCEPTED;      
    }
    /* other filters are not supported yet */
    else
    {
      *LampStatus = (Dem_J1939DcmLampStatusType)0xFFFFU;
      retVal = DEM_WRONG_FILTER;
    }
  }
  
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNumberOfFilteredDTC                  **
**                                                                            **
** Service ID           : 0x91                                                **
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
#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
FUNC(Dem_ReturnGetNumberOfFilteredDTCType, DEM_CODE)
Dem_J1939DcmGetNumberOfFilteredDTC(
  uint16* NumberOfFilteredDTC)
{
  Dem_ReturnGetNumberOfFilteredDTCType retVal = DEM_NUMBER_PENDING;

  /*  Check   module  Initialization  status  */
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNUMBEROFFILTEREDDTC_SID, DEM_E_UNINIT);
    retVal = DEM_NUMBER_FAILED;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)   
  else if (NumberOfFilteredDTC == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNUMBEROFFILTEREDDTC_SID, DEM_E_PARAM_POINTER);
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
    if ((DEM_JOB_TRIGGER == Dem_J1939DTCFilterState.j1939_JobAction) || 
        (DEM_JOB_RUNNING == Dem_J1939DTCFilterState.j1939_JobAction))
    {    
      /* Return appropriate value */
      retVal = DEM_FILTERED_PENDING;
    }
    else if(DEM_JOB_DONE == Dem_J1939DTCFilterState.j1939_JobAction)
    {
      /* Return the number of filtered DTC's */
      *NumberOfFilteredDTC = Dem_J1939DTCFilterState.j1939_NumOfFilteredDTC;  
      retVal = DEM_NUMBER_OK;
    }
    else
    {
      retVal = DEM_NUMBER_FAILED;
    }
  }   
  return retVal;
}/* End of API */
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmFirstDTCwithLampStatus                  **
**                                                                            **
** Service ID           : 0x93                                                **
**                                                                            **
** Description          : The function set the filter to the first applicable **
**                        DTC for the DM31 response for a specifc node.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input parameter      : node                                                **
**                         Nm node Id                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The API Dem_Init()                                  **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DEM_J1939_DM31_SUPPORT == STD_ON)
FUNC(void, DEM_CODE) Dem_J1939DcmFirstDTCwithLampStatus( uint8 NodeAddress )
{
  
  /* Module initialization check */
  if (Dem_GucInit != DEM_INIT)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMFIRSTDTCWITHLAMPSTATUS_SID, DEM_E_UNINIT);
  }
  else  /* node : N/A */
  {
    #if(DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)
    Dem_NumOfDTCValueType dtcLoc = 0u;  
    Dem_EventIdType eventId;
    for (eventId = 1U; eventId <= Dem_Number_Of_Events; eventId++)
    {
      Dem_EvClearProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
    }

    Dem_J1939DTCFilterState.j1939_NumOfFilteredDTC = 0U;
    Dem_J1939FirstDtcLoc = 0xFF;
    
    for (dtcLoc = 0u; dtcLoc < Dem_Max_Number_Of_DTC ; dtcLoc++)
    {
      P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) cbDTC = &Dem_GaaCombinedDtc[dtcLoc];
      Dem_EventIdType eventId = Dem_GetFirstEventOfDTC(cbDTC);
      /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid to 'Unreachable code' of the polyspace */
      if ((DEM_NO_DTC != cbDTC->J1939DTCValue) && (DEM_NO_EVENT != eventId))
      {      
        #if(DEM_DTC_SUPPRESSION_SUPPORT == STD_ON)      
        /* Refer to Dem_SetDTCSuppression */
        if (DEM_FALSE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP)) 
        #endif
        {
          Dem_EvSetProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
          Dem_J1939DTCFilterState.j1939_NumOfFilteredDTC++;
          if(0xFFU == Dem_J1939FirstDtcLoc)
          {
            Dem_J1939FirstDtcLoc = dtcLoc;
          }
        }
      }
    }
    #endif
    
    Dem_J1939DTCFilterState.j1939_JobAction = DEM_JOB_DONE;  
    
  }

}
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNextFilteredDTC                      **
**                                                                            **
** Service ID           : 0x92                                                **
**                                                                            **
** Description          : This API shall be used to get next Filtered DTC     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint32* J1939DTC                                    **
**                        uint8*  OccurenceCounter                            **
**                                                                            **
** Return parameter     : Dem_ReturnGetNextFilteredElementType                **
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
#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE) 
Dem_J1939DcmGetNextFilteredDTC(
  uint32* J1939DTC,
  uint8* OccurenceCounter)
{
  Dem_ReturnGetNextFilteredElementType retVal = DEM_FILTERED_NO_MATCHING_ELEMENT; 

  /* Check module Initialization status */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFILTEREDDTC_SID, DEM_E_UNINIT);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ( (NULL_PTR == J1939DTC) || (NULL_PTR == OccurenceCounter))
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFILTEREDDTC_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  #endif  
  else if (
    (DEM_JOB_TRIGGER == Dem_J1939DTCFilterState.j1939_JobAction) || 
    (DEM_JOB_RUNNING == Dem_J1939DTCFilterState.j1939_JobAction))
  {    
    /* DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFILTEREDDTC_SID, DEM_E_WRONG_CONDITION); */
    /* Return appropriate value */
    retVal = DEM_FILTERED_PENDING;
  }  
  else if (DEM_JOB_DONE != Dem_J1939DTCFilterState.j1939_JobAction)
  {
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  } 
  else  
  {
    Dem_NumOfEventMemoryEntryType idxOfEntry  = Dem_PriEvMemChronoOrderNextLoc;
    struct {
      Dem_EventIdType prioEventId;
      Dem_EventPriorityType Priority;
    } HighestEvent = {0,0};

    #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
    if(DEM_J1939DTC_PERMANENT == Dem_J1939DTCFilterState.j1939_DTCStatusFilter)
    {
      idxOfEntry = DEM_MAX_NUMBER_EVENT_ENTRY_PER;
    }
    #endif
    
    /* Only DEM_DTC_ORIGIN_PRIMARY_MEMORY */
    while (idxOfEntry > 0U)
    {    
      /* @IF_REQ [SWS_Dem_00411] If the Dem module is requested to report in chronological order,
       * the most recent event memory entry shall be reported at first. */
      Dem_NumOfEventMemoryEntryType memLoc;

      --idxOfEntry;

      #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
      if(DEM_J1939DTC_PERMANENT == Dem_J1939DTCFilterState.j1939_DTCStatusFilter)
      {
        memLoc = idxOfEntry;
      }
      else
      #endif
      {
        memLoc= Dem_PriEvMemChronoOrder[idxOfEntry];
      }
      
      if (DEM_NO_EVMEM_ENTRY != memLoc)
      {
        Dem_EventIdType eventId = Dem_EvMem_GetEventIdByEvMemEntry(DEM_DTC_ORIGIN_PRIMARY_MEMORY, memLoc);

        #if((DEM_OBD_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U))
        if(DEM_J1939DTC_PERMANENT == Dem_J1939DTCFilterState.j1939_DTCStatusFilter)
        {
          eventId = Dem_PerDtcState[memLoc].EventIdRef;
        }
        #endif
      
        if (DEM_TRUE == Dem_EventIdIsValid(eventId) )
        {
          P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) cbDTC = Dem_GetCbDTCByEventId(eventId);
          if (NULL_PTR != cbDTC)
          {
            Dem_EventIdType firstEventId = Dem_GetFirstEventOfDTC(cbDTC);
            eventId = firstEventId;
          }
                 
          if (DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER))
          {    
            #if(DEM_DTC_SUPPRESSION_SUPPORT == STD_ON)      
            /* Refer to Dem_SetDTCSuppression */
            if (DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP)) 
            {
              Dem_EvClearProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
            }
            else
            #endif
            {  
              Dem_EventParameterCPCType event = &Dem_Event[eventId - 1U];            
                
              if (DEM_NO_EVENT != HighestEvent.prioEventId)
              {
                if (event->ucEventPriority < HighestEvent.Priority)
                {
                  HighestEvent.prioEventId = eventId;
                  HighestEvent.Priority = event->ucEventPriority;                
                }
              }
              else
              {
                HighestEvent.prioEventId = eventId;
                HighestEvent.Priority = event->ucEventPriority;  
              } 
            }
          }
        }
      }  
    }    

    if (DEM_NO_EVENT != HighestEvent.prioEventId)
    {  
      Dem_EventMemoryEntryPtrType memEntry = 
      Dem_EvMem_GetEmEntryByMemPosition(DEM_DTC_ORIGIN_PRIMARY_MEMORY, Dem_EvMemToEventMap[HighestEvent.prioEventId]);            
    
      Dem_EvClearProcState(HighestEvent.prioEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);      
      if (NULL_PTR != memEntry)
      {
        Dem_DTCType dtc = Dem_GetDTCValue(HighestEvent.prioEventId, DEM_DTC_FORMAT_J1939);
        if (DEM_NO_DTC != dtc)
        {
          *J1939DTC = dtc;
          *OccurenceCounter = Dem_EvMem_GetEventOccCounter(memEntry);
          /* [SWS_Dem_00877]
           * In case the occurrence counter is above +126 (0x7F), the returned values shall be set to +126 (0x7F). */
          if (*OccurenceCounter > 0x7F)
          {
            *OccurenceCounter = 0x7F;
          }                
            
          retVal = DEM_FILTERED_OK;   
        }
      }
    }
  }
      
  return retVal;
}/* End of API */
#endif

/*******************************************************************************
** Function Name        : Dem_GetJ1939LampStatus                              **
**                                                                            **
** Service ID           : None                                                **
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
FUNC(Std_ReturnType, DEM_CODE) Dem_GetJ1939LampStatus(
  Dem_EventIdType EventId,
  P2VAR (Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_APPL_DATA) LampStatus)
{
  Std_ReturnType retVal = E_NOT_OK;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  if( LampStatus == NULL_PTR )
  {
    /* retVal = E_NOT_OK;*/
  }
  else if(EventId < 1)
  {
    /* retVal = E_NOT_OK;*/
  }
  else
  #endif
  {
    Dem_EventParameterPCType event = &Dem_Event[EventId-1U];
    P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR)  indicator;
    Dem_NumOfIndicatorAttributeType max = event->e_PointToIndicator + event->ucNumberofIndicator;
    Dem_NumOfIndicatorAttributeType idx;
    boolean indicatorAttributeStatus;

    if (max <= Dem_Number_Of_Indicators)
    {
      boolean MIL = DEM_J1939LAMP_OFF;
      boolean RedStopLamp = DEM_J1939LAMP_OFF;
      boolean WarningLamp = DEM_J1939LAMP_OFF;
      boolean ProtectLamp = DEM_J1939LAMP_OFF;

      Dem_IndicatorStatusType MILStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      Dem_IndicatorStatusType RedStopLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      Dem_IndicatorStatusType WarningLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
      Dem_IndicatorStatusType ProtectLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;



      for (idx = event->e_PointToIndicator; idx < max ; idx++)
      {
        indicator = Dem_GetCfgIndicatorAtt(idx);
        indicatorAttributeStatus = Dem_EvMem_GetIndicatorAttStatus(indicator->EventIdRef, indicator->IndicatorAttStatusPos);

        if(Dem_J1939LampId.MilId == indicator->IndicatorIdRef)
        {
          MIL = indicatorAttributeStatus;
          if(DEM_INDICATOR_SLOW_FLASH == indicator->Behavior)
          {
            MILStatus = DEM_J1939LAMP_SLOW_FLASH;
          }
          else if(DEM_INDICATOR_FAST_FLASH == indicator->Behavior)
          {
            MILStatus = DEM_J1939LAMP_FAST_FLASH;
          }
          else
          {
            MILStatus = DEM_J1939LAMP_DO_NOT_FLASH;
          }
        }

        if(Dem_J1939LampId.RedStopLampId == indicator->IndicatorIdRef)
        {
          RedStopLamp = indicatorAttributeStatus;
          if(DEM_INDICATOR_SLOW_FLASH == indicator->Behavior)
          {
            RedStopLampStatus = DEM_J1939LAMP_SLOW_FLASH;
          }
          else if(DEM_INDICATOR_FAST_FLASH == indicator->Behavior)
          {
            RedStopLampStatus = DEM_J1939LAMP_FAST_FLASH;
          }
          else
          {
            RedStopLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
          }

        }

        if(Dem_J1939LampId.WarningLampId == indicator->IndicatorIdRef)
        {
          WarningLamp = indicatorAttributeStatus;
          if(DEM_INDICATOR_SLOW_FLASH == indicator->Behavior)
          {
            WarningLampStatus = DEM_J1939LAMP_SLOW_FLASH;
          }
          else if(DEM_INDICATOR_FAST_FLASH == indicator->Behavior)
          {
            WarningLampStatus = DEM_J1939LAMP_FAST_FLASH;
          }
          else
          {
            WarningLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
          }
        }

        if(Dem_J1939LampId.ProtectLampId == indicator->IndicatorIdRef)
        {
          ProtectLamp = indicatorAttributeStatus;
          if(DEM_INDICATOR_SLOW_FLASH == indicator->Behavior)
          {
            ProtectLampStatus = DEM_J1939LAMP_SLOW_FLASH;
          }
          else if(DEM_INDICATOR_FAST_FLASH == indicator->Behavior)
          {
            ProtectLampStatus = DEM_J1939LAMP_FAST_FLASH;
          }
          else
          {
            ProtectLampStatus = DEM_J1939LAMP_DO_NOT_FLASH;
          }
        }

        *LampStatus = (
        (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)MIL <<  (Dem_J1939DcmLampStatusType)(BIT_POS_6 + 0U)) | /* Flash Malfunction Indicator Lamp  */
        (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)RedStopLamp  <<  (Dem_J1939DcmLampStatusType)(BIT_POS_4 + 0U))      | /* Flash Red Stop Lamp  */
        (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)WarningLamp  <<  (Dem_J1939DcmLampStatusType)(BIT_POS_2 + 0U))      | /* Flash Amber Warning Lamp   */
        (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)ProtectLamp  <<  (Dem_J1939DcmLampStatusType)(BIT_POS_0 + 0U))      | /* Flash Protect Lamp */

        (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)MILStatus <<  (Dem_J1939DcmLampStatusType)(BIT_POS_6 + 8U)) | /* Flash Malfunction Indicator Lamp Status */
        (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)RedStopLampStatus   <<  (Dem_J1939DcmLampStatusType)(BIT_POS_4 + 8U))        | /* Flash Red Stop Lamp Status */
        (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)WarningLampStatus   <<  (Dem_J1939DcmLampStatusType)(BIT_POS_2 + 8U))        | /* Flash Amber Warning Lamp  Status */
        (Dem_J1939DcmLampStatusType)((Dem_J1939DcmLampStatusType)ProtectLampStatus   <<  (Dem_J1939DcmLampStatusType)(BIT_POS_0 + 8U)));  /* Flash Protect Lamp Status */
      }
    }

  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNextDTCwithLampStatus                **
**                                                                            **
** Service ID           : 0x94                                                **
**                                                                            **
** Description          : Gets the next filtered J1939 DTC for DM31 including **
**                        current LampStatus.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input parameter      : None                                                **
**                                                                            **
** Output Parameters    : LampStatus                                          **
**                         bits 8-7 - Malfunction Indicator Lamp Status       **
**                         bits 6-5 - Red Stop Lamp Status                    **
**                         bits 4-3 - Amber Warning Lamp Status               **
**                         bits 2-1 - Protect Lamp Status                     **
**                                                                            **
**                         bits 8-7 - Flash Malfunction Indicator Lamp        **
**                         bits 6-5 - Flash Red Stop Lamp                     **
**                         bits 4-3 - Flash Amber WarningLamp                 **
**                         bits 2-1 - Flash Protect Lamp                      **
**                                                                            **
**                        uint32* J1939DTC                                    **
**                        uint8* OccurenceCounter                             **
**                                                                            **
**                                                                            **
** Return parameter     : Dem_ReturnGetNextFilteredElementType                **
**                                                                            **
** Preconditions        : The API Dem_Init()                                  **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DEM_J1939_DM31_SUPPORT == STD_ON)
FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE)
Dem_J1939DcmGetNextDTCwithLampStatus( 
  Dem_J1939DcmLampStatusType* LampStatus, 
  uint32* J1939DTC, 
  uint8* OccurenceCounter )
{
  Dem_ReturnGetNextFilteredElementType retVal = DEM_FILTERED_NO_MATCHING_ELEMENT; 

  /* Check module Initialization status */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTDTCWITHLAMPSTATUS_SID, DEM_E_UNINIT);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((NULL_PTR == LampStatus) || (NULL_PTR == J1939DTC) || (NULL_PTR == OccurenceCounter))
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTDTCWITHLAMPSTATUS_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  #endif  
  else if (
    (DEM_JOB_TRIGGER == Dem_J1939DTCFilterState.j1939_JobAction) || 
    (DEM_JOB_RUNNING == Dem_J1939DTCFilterState.j1939_JobAction))
  {    
    /* DEM_REPORT_ERROR(DEM_J1939DcmGetNextDTCwithLampStatus_SID, DEM_E_WRONG_CONDITION); */
    /* Return appropriate value */
    retVal = DEM_FILTERED_PENDING;
  }  
  else if (DEM_JOB_DONE != Dem_J1939DTCFilterState.j1939_JobAction)
  {
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  } 
  else  
  {
    if(Dem_J1939FirstDtcLoc == 0xFFU)
    {
      Dem_J1939FirstDtcLoc = 0U;
    }

    while (Dem_J1939FirstDtcLoc< Dem_Max_Number_Of_DTC)
    {
      P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) cbDTC = &Dem_GaaCombinedDtc[Dem_J1939FirstDtcLoc];
      Dem_EventIdType eventId = Dem_GetFirstEventOfDTC(cbDTC);
      if (DEM_TRUE == Dem_EventIdIsValid(eventId) )
      {     
        if (DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER))
        {    
          #if(DEM_DTC_SUPPRESSION_SUPPORT == STD_ON)      
          /* Refer to Dem_SetDTCSuppression */
          if (DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP)) 
          {
            Dem_EvClearProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
          }
          else
          #endif
          {

            Dem_EventMemoryEntryPtrType memEntry = 
            Dem_EvMem_FindEntry(eventId, DEM_DTC_ORIGIN_PRIMARY_MEMORY); 

          
            Dem_EvClearProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);      
            if (NULL_PTR != memEntry)
            {
              Dem_DTCType dtc = Dem_GetDTCValue(eventId, DEM_DTC_FORMAT_J1939);
              if (DEM_NO_DTC != dtc)
              {

                *J1939DTC = dtc;
                *OccurenceCounter = Dem_EvMem_GetEventOccCounter(memEntry);
                /* [SWS_Dem_00877]
                 * In case the occurrence counter is above +126 (0x7F), the returned values shall be set to +126 (0x7F). */
                if (*OccurenceCounter > 0x7F)
                {
                  *OccurenceCounter = 0x7F;
                }

                (void)Dem_GetJ1939LampStatus(eventId, LampStatus); 
                
                  
                retVal = DEM_FILTERED_OK;
                break;
                
              }
            }      
          
          }

        }
      }
      Dem_J1939FirstDtcLoc++;
    }

  }


    
#if 0    
    /* Only DEM_DTC_ORIGIN_PRIMARY_MEMORY */
    while (idxOfEntry > 0U)
    {    
      /* @IF_REQ [SWS_Dem_00411] If the Dem module is requested to report in chronological order,
       * the most recent event memory entry shall be reported at first. */
      Dem_NumOfEventMemoryEntryType memLoc= Dem_PriEvMemChronoOrder[idxOfEntry];

      --idxOfEntry;     
      
      if (DEM_NO_EVMEM_ENTRY != memLoc)
      {
        Dem_EventIdType eventId = Dem_EvMem_GetEventIdByEvMemEntry(DEM_DTC_ORIGIN_PRIMARY_MEMORY, memLoc);
      
        if (DEM_TRUE == Dem_EventIdIsValid(eventId) )
        {     
          if (DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER))
          {    
            #if(DEM_DTC_SUPPRESSION_SUPPORT == STD_ON)      
            /* Refer to Dem_SetDTCSuppression */
            if (DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_DTC_SUPP)) 
            {
              Dem_EvClearProcState(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
            }
            else
            #endif
            {  
              Dem_EventParameterCPCType event = &Dem_Event[eventId - 1U];            
              
              if (DEM_NO_EVENT != HighestEvent.prioEventId)
              {
                if (event->ucEventPriority < HighestEvent.Priority)
                {
                  HighestEvent.prioEventId = eventId;
                  HighestEvent.Priority = event->ucEventPriority;                
                }
              }
              else
              {
                HighestEvent.prioEventId = eventId;
                HighestEvent.Priority = event->ucEventPriority;  
              }                          
            }
          }
        }
      }  
    }    

    if (DEM_NO_EVENT != HighestEvent.prioEventId)
    {  
      Dem_EventMemoryEntryPtrType memEntry = 
      Dem_EvMem_GetEmEntryByMemPosition(DEM_DTC_ORIGIN_PRIMARY_MEMORY, Dem_EvMemToEventMap[HighestEvent.prioEventId]);            
    
      Dem_EvClearProcState(HighestEvent.prioEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);      
      if (NULL_PTR != memEntry)
      {
        Dem_DTCType dtc = Dem_GetDTCValue(HighestEvent.prioEventId, DEM_DTC_FORMAT_J1939);
        if (DEM_NO_DTC != dtc)
        {

          *J1939DTC = dtc;
          *OccurenceCounter = Dem_EvMem_GetEventOccCounter(memEntry);
          /* [SWS_Dem_00877]
           * In case the occurrence counter is above +126 (0x7F), the returned values shall be set to +126 (0x7F). */
          if (*OccurenceCounter > 0x7F)
          {
            *OccurenceCounter = 0x7F;
          }

          (void)Dem_GetJ1939LampStatus(HighestEvent.prioEventId, *LampStatus);          
            
          retVal = DEM_FILTERED_OK;   
        }
      }
    }
  }
#endif
  
  
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmClearDTC                                **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : Clears active DTCs as well as previously avtive DTCs**
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCTypeFilter -                                     **
**                        The following types are available:                  **
**                        DEM_J1939DTC_CLEAR_ALL                              **
**                        DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE                **
**                                                                            **
**                        NodeAddress - node address of requesting client     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_ReturnClearDTCType                              **
**                          DEM_CLEAR_OK                                      **
**                          DEM_CLEAR_WRONG_DTC                               **
**                          DEM_CLEAR_WRONG_DTCORIGIN                         **
**                          DEM_CLEAR_FAILED                                  **
**                          DEM_CLEAR_PENDING                                 **
**                          DEM_CLEAR_BUSY                                    **
**                          DEM_CLEAR_MEMORY_ERROR                            **                                                        
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
Dem_ReturnClearDTCType Dem_J1939DcmClearDTC(
  Dem_J1939DcmSetClearFilterType DTCTypeFilter,
  uint8 NodeAddress)
{
  Dem_ReturnClearDTCType retVal = DEM_CLEAR_FAILED;

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  if ((DEM_CLEARDTC_STATE_USER_CDD == Dem_ClearDtcState.cds_User) ||
    (DEM_CLEARDTC_STATE_USER_DCM == Dem_ClearDtcState.cds_User))
  {
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    retVal = DEM_CLEAR_PENDING; /* It means 'busy' state */
  }
  else /* DEM_CLEARDTC_STATE_USER_DCM or IDLE */
  {
    if (
      (DEM_J1939DTC_CLEAR_ALL == DTCTypeFilter) || /* DM11 */
      (DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE == DTCTypeFilter) /* DM3*/
    )
    {  
      Dem_ClearDtcState.cds_User = DEM_CLEARDTC_STATE_USER_J1939DCM;
      Dem_ClearDtcState.cds_DTCTypeFilter = DTCTypeFilter;     
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

      /* Limitations : Supports only DEM_DTC_ORIGIN_PRIMARY_MEMORY according to 
       * J1939-73 
       * DM3 is not used to clear all diagnostic data relative to regulated OBD products. 
       * DM3 is not required to satisfy regulated
       * automotive OBD requirements. DM3 can be used for other manufacturer specific purposes */
      retVal = Dem_InternalClearDTC(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_FORMAT_J1939, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
      if (DEM_CLEAR_PENDING != retVal)
      {
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();    
        Dem_ClearDtcState.cds_User = DEM_CLEARDTC_STATE_USER_IDLE;
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

      }
    }
    else
    {
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
  }  

  return retVal;
}
#endif


/*******************************************************************************
** Function Name        : Dem_J1939DcmSetFreezeFrameFilter                    **
**                                                                            **
** Service ID           : 0x96                                                **
**                                                                            **
** Description          : This API shall set a J1939 freeze frame Record filter**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : FreezeFrameKind                                     **
**                        NodeAddress                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
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
#if ((DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT == STD_ON) || (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON))
FUNC(Dem_ReturnSetFilterType, DEM_CODE)
Dem_J1939DcmSetFreezeFrameFilter(
  Dem_J1939DcmSetFreezeFrameFilterType FreezeFrameKind,
  uint8 NodeAddress)
{

  Dem_ReturnSetFilterType retVal = DEM_FILTER_ACCEPTED;
  
  if (DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMSETFREEZEFRAMEFILTER_SID, DEM_E_UNINIT);
    retVal = DEM_WRONG_FILTER;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((FreezeFrameKind != DEM_J1939DCM_FREEZEFRAME) && (FreezeFrameKind != DEM_J1939DCM_EXPANDED_FREEZEFRAME) && (FreezeFrameKind != DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME))
  {
    DEM_REPORT_ERROR(DEM_J1939DCMSETFREEZEFRAMEFILTER_SID, DEM_E_PARAM_CONFIG);
    retVal = DEM_WRONG_FILTER;
  }
  #endif  
  else
  {
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0U) && ((DEM_SIZE_OF_J1939FREEZEFRAME > 0U) || (DEM_SIZE_OF_J1939EXPANDEDFREEZEFRAME > 0U)))
    Dem_EventIdType evId;
    Dem_NumOfEventMemoryEntryType memLoc = 0U;     

    for (evId = 1U; evId <= Dem_Number_Of_Events; evId++)
    {
      Dem_EvClearProcState(evId, DEM_EVPROCSTATE_J1939DTC_FILTER);
      Dem_EvClearProcState(evId, DEM_EVPROCSTATE_J1939EXFF_FILTER);
    }

    Dem_FilteredFFRecord.nextEvent = DEM_NO_EVENT;
    for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[DEM_DTC_ORIGIN_PRIMARY_MEMORY]; memLoc++)
    {
      evId = Dem_EvMem_GetEventIdByEvMemEntry(DEM_DTC_ORIGIN_PRIMARY_MEMORY,memLoc);       
      /* if (DEM_TRUE == Dem_EventIdIsValid(evId)) */
      if ((evId <= Dem_Number_Of_Events) && (DEM_NO_EVENT != evId))
      {
        P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) cbDTC = Dem_GetCbDTCByEventId(evId);    
        if (NULL_PTR != cbDTC)
        {
          /* Filtering according to  expected DTCformat */
          if (DEM_TRUE == Dem_EvMem_DTCFormatIsValid(DEM_DTC_FORMAT_J1939,cbDTC)) 
          {

            Dem_EventParameterPCType event = &Dem_Event[evId - 1U];    
            if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
            {
              if(FreezeFrameKind == DEM_J1939DCM_FREEZEFRAME)
              {
                if (Dem_EventRelatedData[event->e_PointToData].J1939FFClassPos < Dem_Num_Of_J1939FreezeFrameClass)  //need to change
                {
                  Dem_EvSetProcState(evId, DEM_EVPROCSTATE_J1939DTC_FILTER);
                  if (DEM_NO_EVENT == Dem_FilteredFFRecord.nextEvent)
                  {
                    Dem_FilteredFFRecord.nextEvent = evId;
                  }
                  
                }
              }
              else if ((FreezeFrameKind == DEM_J1939DCM_EXPANDED_FREEZEFRAME) || (FreezeFrameKind == DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME))
              {
                if (Dem_EventRelatedData[event->e_PointToData].J1939EXFFClassPos < Dem_Num_Of_J1939FreezeFrameClass)  //need to change
                {
                  Dem_EvSetProcState(evId, DEM_EVPROCSTATE_J1939EXFF_FILTER);
                  if (DEM_NO_EVENT == Dem_FilteredFFRecord.nextEvent)
                  {
                    Dem_FilteredFFRecord.nextEvent = evId;
                  }
                  
                }            
              }
              else 
              {
                /* Do Nothing */
              }
            }
          
          }
        }

      }

    }    
    #endif
  
  }
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNextFreezeFrame                      **
**                                                                            **
** Service ID           : 0x97                                                **
**                                                                            **
** Description          : Gets next freeze frame data. The function stores    **
**                        the data in the provided DestBuffer.                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : DestBuffer                                          **
**                        BufSize                                             **
**                                                                            **
** Output Parameters    : uint32* DTC,                                        **
**                        uint8* DestBuffer                                   **
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
#if ((DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT == STD_ON) || (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON))
FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE)
Dem_J1939DcmGetNextFreezeFrame(
    P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) J1939DTC,
    P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) OccurenceCounter,
    P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
    P2VAR (uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Dem_ReturnGetNextFilteredElementType retVal  = DEM_FILTERED_NO_MATCHING_ELEMENT;;

  /* Check module Initialization status */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFREEZEFRAME_SID, DEM_E_UNINIT);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ( (NULL_PTR == J1939DTC) || (NULL_PTR == OccurenceCounter) || (NULL_PTR == DestBuffer) || (NULL_PTR == BufSize))
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFREEZEFRAME_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  else if (DEM_NO_EVENT == Dem_FilteredFFRecord.nextEvent)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTFREEZEFRAME_SID, DEM_E_PARAM_DATA);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  #endif    
  else
  {
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0u) && \
		    (DEM_NUM_OF_J1939FREEZEFRAMECLASS > 0U))     
    Dem_EventMemoryEntryPtrType entry; 
    Dem_J1939DcmSetFreezeFrameFilterType j1939FFType = 0;

    Dem_NumOfEventMemoryEntryType idxOfEntry  = Dem_PriEvMemChronoOrderNextLoc;
    struct {
      Dem_EventIdType prioEventId;
      Dem_EventPriorityType Priority;
      Dem_J1939DcmSetFreezeFrameFilterType filerType;
    } HighestEvent = {0,0,0};


    
    /* Only DEM_DTC_ORIGIN_PRIMARY_MEMORY */
    while (idxOfEntry > 0U)
    {    
      /* @IF_REQ [SWS_Dem_00411] If the Dem module is requested to report in chronological order,
       * the most recent event memory entry shall be reported at first. */
      Dem_NumOfEventMemoryEntryType memLoc;

      --idxOfEntry;


      memLoc= Dem_PriEvMemChronoOrder[idxOfEntry];

      
      if (DEM_NO_EVMEM_ENTRY != memLoc)
      {
        Dem_EventIdType eventId = Dem_EvMem_GetEventIdByEvMemEntry(DEM_DTC_ORIGIN_PRIMARY_MEMORY, memLoc);

        if(DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_J1939DTC_FILTER))
        {
          j1939FFType = DEM_J1939DCM_FREEZEFRAME;
        }
        else if(DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_J1939EXFF_FILTER))
        {
          j1939FFType = DEM_J1939DCM_EXPANDED_FREEZEFRAME;
        }
        else
        {
          j1939FFType = 3;
        }

      
      
        if (DEM_TRUE == Dem_EventIdIsValid(eventId) )
        {     
          if ((j1939FFType == DEM_J1939DCM_FREEZEFRAME) || (j1939FFType == DEM_J1939DCM_EXPANDED_FREEZEFRAME))
          {    

 
            Dem_EventParameterCPCType event = &Dem_Event[eventId - 1U];            
            
            if (DEM_NO_EVENT != HighestEvent.prioEventId)
            {
              if (event->ucEventPriority < HighestEvent.Priority)
              {
                HighestEvent.prioEventId = eventId;
                HighestEvent.Priority = event->ucEventPriority; 
                HighestEvent.filerType = j1939FFType;
              }
            }
            else
            {
              HighestEvent.prioEventId = eventId;
              HighestEvent.Priority = event->ucEventPriority;
              HighestEvent.filerType = j1939FFType;
            }                          

          }
        }
      }  
    }    

    if (DEM_NO_EVENT != HighestEvent.prioEventId)
    {  
      Dem_EventMemoryEntryPtrType memEntry = 
      Dem_EvMem_GetEmEntryByMemPosition(DEM_DTC_ORIGIN_PRIMARY_MEMORY, Dem_EvMemToEventMap[HighestEvent.prioEventId]);            
    
      Dem_EvClearProcState(HighestEvent.prioEventId, DEM_EVPROCSTATE_J1939DTC_FILTER);
      Dem_EvClearProcState(HighestEvent.prioEventId, DEM_EVPROCSTATE_J1939EXFF_FILTER);

      entry = Dem_EvMem_FindEntry(HighestEvent.prioEventId, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
      if (NULL_PTR != entry)
      {
        Dem_EventParameterPCType event = &Dem_Event[HighestEvent.prioEventId - 1U];    
        if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
        {

          *J1939DTC = Dem_GetDTCValue(HighestEvent.prioEventId, DEM_DTC_FORMAT_J1939);

          (void)Dem_GetJ1939FreezeFrameData(event,DEM_DTC_ORIGIN_PRIMARY_MEMORY, DestBuffer, BufSize, HighestEvent.filerType);

          *OccurenceCounter = Dem_EvMem_GetEventOccCounter(entry);
          /* [SWS_Dem_00877]
           * In case the occurrence counter is above +126 (0x7F), the returned values shall be set to +126 (0x7F). */
          if (*OccurenceCounter > 0x7F)
          {
            *OccurenceCounter = 0x7F;
          }                

          Dem_FilteredFFRecord.nextEvent++;     
          retVal = DEM_FILTERED_OK;

        }

      }
    }
    #endif
  }


    

#if 0
    /*  if event is deleled or aged, Dem returns the next event.*/
    while (Dem_FilteredFFRecord.nextEvent <= Dem_Number_Of_Events) 
    {

      if(DEM_TRUE == Dem_EvIsProcStateTriggered(Dem_FilteredFFRecord.nextEvent, DEM_EVPROCSTATE_J1939DTC_FILTER))
      {
        j1939FFType = DEM_J1939DCM_FREEZEFRAME;
      }
      else if(DEM_TRUE == Dem_EvIsProcStateTriggered(Dem_FilteredFFRecord.nextEvent, DEM_EVPROCSTATE_J1939EXFF_FILTER))
      {
        j1939FFType = DEM_J1939DCM_EXPANDED_FREEZEFRAME;
      }
      else
      {
        j1939FFType = 3;
      }
    
      if ((j1939FFType == DEM_J1939DCM_FREEZEFRAME) || (j1939FFType == DEM_J1939DCM_EXPANDED_FREEZEFRAME))
      {
        eventId = Dem_FilteredFFRecord.nextEvent;                
        entry = Dem_EvMem_FindEntry(eventId, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
        if (NULL_PTR != entry)
        {
          Dem_EventParameterPCType event = &Dem_Event[eventId - 1U];    
          if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
          {
//            (void)Dem_GetEventDTC(event, J1939DTC, DEM_DTC_FORMAT_J1939);

            *J1939DTC = Dem_GetDTCValue(eventId, DEM_DTC_FORMAT_J1939);

            (void)Dem_GetJ1939FreezeFrameData(event,DEM_DTC_ORIGIN_PRIMARY_MEMORY, DestBuffer, BufSize, j1939FFType);

            *OccurenceCounter = Dem_EvMem_GetEventOccCounter(entry);
            /* [SWS_Dem_00877]
             * In case the occurrence counter is above +126 (0x7F), the returned values shall be set to +126 (0x7F). */
            if (*OccurenceCounter > 0x7F)
            {
              *OccurenceCounter = 0x7F;
            }                

            Dem_FilteredFFRecord.nextEvent++;     
            retVal = DEM_FILTERED_OK;
       
            break;  

          }

        }

        /* [1] No exist in event memory 
         * [2] end loop about all records of a freeze frame of a event  
         * [3] etc */
        Dem_EvClearProcState(Dem_FilteredFFRecord.nextEvent, DEM_EVPROCSTATE_J1939DTC_FILTER);
        Dem_EvClearProcState(Dem_FilteredFFRecord.nextEvent, DEM_EVPROCSTATE_J1939EXFF_FILTER);

      }
      /* Increment the record count returned to dcm */
      Dem_FilteredFFRecord.nextEvent++;      
    }


  }

  #endif

  return retVal;
}
#endif


/*******************************************************************************
** Function Name        : Dem_J1939DcmSetRatioFilter                          **
**                                                                            **
** Service ID           : 0x99                                                **
**                                                                            **
** Description          : The function set the Ratio filter for a specifc node**
**                        and returns the corresponding                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : FreezeFrameKind                                     **
**                        NodeAddress                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
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
#if(DEM_OBD_SUPPORT == STD_ON)
#if (DEM_J1939_RATIO_SUPPORT == STD_ON)
Dem_ReturnSetFilterType 
Dem_J1939DcmSetRatioFilter(
  uint16* IgnitionCycleCounter, 
  uint16* OBDMonitoringConditionsEncountered, 
  uint8 NodeAddress)
{

  Dem_ReturnSetFilterType retVal = DEM_FILTER_ACCEPTED;
  
  if (DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMSETRATIOFILTER_SID, DEM_E_UNINIT);
    retVal = DEM_WRONG_FILTER;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((IgnitionCycleCounter == NULL_PTR) || (OBDMonitoringConditionsEncountered == NULL_PTR))
  {
    DEM_REPORT_ERROR(DEM_J1939DCMSETRATIOFILTER_SID, DEM_E_PARAM_CONFIG);
    retVal = DEM_WRONG_FILTER;
  }
  #endif  
  else
  {
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0U) && (DEM_NUMBER_OF_RATIO_INFO > 0U))
    Dem_EventIdType evId;
    uint8 ratioIndex;

    for (evId = 1U; evId <= Dem_Number_Of_Events; evId++)
    {
       Dem_EvClearProcState(evId, DEM_EVPROCSTATE_J1939DTC_FILTER);
    }

    Dem_FilteredFFRecord.nextEvent = DEM_NO_EVENT;
    Dem_J1939NextRatioIndex = 0;
    for (ratioIndex = 0U; ratioIndex < DEM_NUMBER_OF_RATIO_INFO; ratioIndex++)
    {
      evId = Dem_GaaRatioIdInfo[ratioIndex].rid_EventId;
      /* if (DEM_TRUE == Dem_EventIdIsValid(evId)) */
      if ((evId <= Dem_Number_Of_Events) && (DEM_NO_EVENT != evId))
      {
        P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) cbDTC = Dem_GetCbDTCByEventId(evId);    
        if (NULL_PTR != cbDTC)
        {        
          /* Filtering according to  expected DTCformat */
          if (DEM_TRUE == Dem_EvMem_DTCFormatIsValid(DEM_DTC_FORMAT_J1939,cbDTC)) 
          {
            Dem_EvSetProcState(evId, DEM_EVPROCSTATE_J1939DTC_FILTER);
            *IgnitionCycleCounter = Dem_GusIgnitionCylCnt;
            *OBDMonitoringConditionsEncountered = Dem_GusGeneralDenominator;
            if ((DEM_NO_EVENT == Dem_FilteredFFRecord.nextEvent) || (evId < Dem_FilteredFFRecord.nextEvent) )
            {
              Dem_FilteredFFRecord.nextEvent = evId;
            }                          
          }
        }

      }

    }    
    #endif  
  }

  return retVal;
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNextFilteredRatio                    **
**                                                                            **
** Service ID           : 0x9a                                                **
**                                                                            **
** Description          : Gets next ratio data. The function reports          **
**                        the Numerator and Denominator.                      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : DestBuffer                                          **
**                        BufSize                                             **
**                                                                            **
** Output Parameters    : uin16* SPN,                                         **
**                        uint16* Numerator                                   **
**                        uint16* Denominator                                 **
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
#if(DEM_OBD_SUPPORT == STD_ON)
#if (DEM_J1939_RATIO_SUPPORT == STD_ON)
Dem_ReturnGetNextFilteredElementType
Dem_J1939DcmGetNextFilteredRatio(
  uint16* SPN,
  uint16* Numerator,
  uint16* Denominator)
{
	Dem_ReturnGetNextFilteredElementType retVal  = DEM_FILTERED_NO_MATCHING_ELEMENT;

  /* Check module Initialization status */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTRATIO_SID, DEM_E_UNINIT);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ( (NULL_PTR == SPN) || (NULL_PTR == Numerator) || (NULL_PTR == Denominator))
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTRATIO_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  else if (DEM_NO_EVENT == Dem_FilteredFFRecord.nextEvent)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTRATIO_SID, DEM_E_PARAM_DATA);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  #endif    
  else
  {
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0u) && \
		    (DEM_NUMBER_OF_RATIO_INFO > 0U))
    Dem_EventIdType eventId;         
    Dem_EventParameterPCType event;


    /*  if event is deleled or aged, Dem returns the next event.*/
    while (Dem_FilteredFFRecord.nextEvent <= Dem_Number_Of_Events) 
    {

      if(DEM_TRUE == Dem_EvIsProcStateTriggered(Dem_FilteredFFRecord.nextEvent, DEM_EVPROCSTATE_J1939DTC_FILTER))
      {
        Dem_DTCType DTC;
        eventId = Dem_FilteredFFRecord.nextEvent;                

        event = &Dem_Event[eventId - 1U];    

        (void)Dem_GetEventDTC(event, &DTC, DEM_DTC_FORMAT_J1939);
  

        if(event->aaRatioIndex[Dem_J1939NextRatioIndex] < DEM_NUMBER_OF_RATIO_INFO)
        {
          *SPN = (uint16)(DTC >>8);
          *Numerator = Dem_GaaIumprNumerator[Dem_GaaRatioIdInfo[event->aaRatioIndex[Dem_J1939NextRatioIndex]].ucIUMPRGroup];            
          *Denominator = Dem_GaaIumprDenominator[Dem_GaaRatioIdInfo[event->aaRatioIndex[Dem_J1939NextRatioIndex]].ucIUMPRGroup];
          
          Dem_EvClearProcState(Dem_FilteredFFRecord.nextEvent, DEM_EVPROCSTATE_J1939DTC_FILTER);

          if(Dem_J1939NextRatioIndex < (event->usRatioIdCount-1))
          {
            Dem_J1939NextRatioIndex++;
          }
          else
          {
            Dem_FilteredFFRecord.nextEvent++; 
            Dem_J1939NextRatioIndex = 0;
          }
              
          retVal = DEM_FILTERED_OK;
          break; 

        }       

      }
      /* Increment the record count returned to dcm */
      Dem_FilteredFFRecord.nextEvent++;      
    }

    #endif
  }
  

	return retVal;
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmReadDiagnosticReadiness1                **
**                                                                            **
** Service ID           : 0x9b                                                **
**                                                                            **
** Description          : Service to report the value of DiagnosticReadiness1 **
**                        (DM5) computed by the Dem.                          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 NodeAddress                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_J1939DcmDiagnosticReadiness1Type* DataValue,    **
**                                                                            **
** Return parameter     :                                                     **
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
#if(DEM_OBD_SUPPORT == STD_ON)
#if (DEM_J1939_READINESS1_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness1(
	Dem_J1939DcmDiagnosticReadiness1Type* DataValue,
	uint8 NodeAddress )
{
	Std_ReturnType retVal = E_OK;

	/* Check module Initialization status */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMREADDIAGNOSTICREADINESS1_SID, DEM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (NULL_PTR == DataValue)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMREADDIAGNOSTICREADINESS1_SID, DEM_E_PARAM_POINTER);
    retVal = E_NOT_OK;
  }
  #endif    
  else
  {
    VAR(uint16, AUTOMATIC) LusNumberOfFilteredDTC = 0;
    Dem_J1939DcmLampStatusType LampStatus;
    uint16 evIndex;

   const boolean rdGrp[] =
    {
      DEM_FALSE,
      DEM_TRUE,  /* DEM_OBD_RDY_MISF        0x01 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_AC          0x02 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_BOOSTPR     0x03 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_CAT         0x04 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_CMPRCMPT    0x05 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_EGSENS      0x06 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_EGR         0x07 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_EVAP        0x08 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_FLSYS       0x09 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_HCCAT       0x0A used   */
      DEM_TRUE,  /* DEM_OBD_RDY_HTCAT       0x0B used   */
      DEM_FALSE, /* DEM_OBD_RDY_NONE        0x0C used   */
      DEM_TRUE,  /* DEM_OBD_RDY_NOXCAT      0x0D used   */
      DEM_TRUE,  /* DEM_OBD_RDY_O2SENS      0x0E used   */
      DEM_TRUE,  /* DEM_OBD_RDY_O2SENSHT    0x0F used   */
      DEM_TRUE,  /* DEM_OBD_RDY_PMFLT       0x10 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_SECAIR      0x11 used   */
    };    

    const uint16 shiftMask[] =
    {
      0x00U,
      0x01U,     /* DEM_OBD_RDY_MISF        0x01    */
      0x0010U,   /* DEM_OBD_RDY_AC          0x02    */
      0x0200U,   /* DEM_OBD_RDY_BOOSTPR     0x03    */
      0x0001U,   /* DEM_OBD_RDY_CAT         0x04    */
      0x04U,     /* DEM_OBD_RDY_CMPRCMPT    0x05    */
      0x0020U,   /* DEM_OBD_RDY_EGSENS      0x06    */
      0x0080U,   /* DEM_OBD_RDY_EGR         0x07    */
      0x0004U,   /* DEM_OBD_RDY_EVAP        0x08    */
      0x02U,     /* DEM_OBD_RDY_FLSYS       0x09    */
      0x1000,    /* DEM_OBD_RDY_HCCAT       0x0A    */
      0x0002,    /* DEM_OBD_RDY_HTCAT       0x0B    */
      0x00,      /* DEM_OBD_RDY_NONE        0x0C    */
      0x0800,    /* DEM_OBD_RDY_NOXCAT      0x0D    */
      0x0100,    /* DEM_OBD_RDY_O2SENS      0x0E    */
      0x0040,    /* DEM_OBD_RDY_O2SENSHT    0x0F    */
      0x0400,    /* DEM_OBD_RDY_PMFLT       0x10    */
      0x0008     /* DEM_OBD_RDY_SECAIR      0x11    */   
    };
    
    /*  Byte 1 :   */
    if (DEM_FILTER_ACCEPTED == Dem_J1939DcmSetDTCFilter(DEM_J1939DTC_ACTIVE, DEM_DTC_KIND_ALL_DTCS,0, &LampStatus))
    {
      SchM_Enter_Dem_REQUEST_DATA_PROTECTION();       
      if (Dem_J1939DTCFilterState.j1939_JobAction == DEM_JOB_TRIGGER)
      {
        Dem_J1939DTCFilterState.j1939_JobAction = DEM_JOB_RUNNING;
        SchM_Exit_Dem_REQUEST_DATA_PROTECTION(); 
        Dem_J1939CountAndStoreFilterDtc();
      }
      else
      {
        SchM_Exit_Dem_REQUEST_DATA_PROTECTION();       
      }
  
      (void)Dem_J1939DcmGetNumberOfFilteredDTC(&LusNumberOfFilteredDTC);
      if(LusNumberOfFilteredDTC > DEM_J1939RDY_MAX_DTC_NUMBER)
      {
         LusNumberOfFilteredDTC = DEM_J1939RDY_MAX_DTC_NUMBER;
      }
      DataValue->ucActiveTroubleCodes = (uint8)LusNumberOfFilteredDTC;
    }
    else
    {
      return E_NOT_OK;
    }

    /*  Byte 2 :   */
    if (DEM_FILTER_ACCEPTED == Dem_J1939DcmSetDTCFilter(DEM_J1939DTC_PREVIOUSLY_ACTIVE, DEM_DTC_KIND_ALL_DTCS,0, &LampStatus))
    {
      SchM_Enter_Dem_REQUEST_DATA_PROTECTION();       
      if (Dem_J1939DTCFilterState.j1939_JobAction == DEM_JOB_TRIGGER)
      {
        Dem_J1939DTCFilterState.j1939_JobAction = DEM_JOB_RUNNING;
        SchM_Exit_Dem_REQUEST_DATA_PROTECTION(); 
        Dem_J1939CountAndStoreFilterDtc();
      }
      else
      {
        SchM_Exit_Dem_REQUEST_DATA_PROTECTION();       
      }
      
      (void)Dem_J1939DcmGetNumberOfFilteredDTC(&LusNumberOfFilteredDTC);
      if(LusNumberOfFilteredDTC > DEM_J1939RDY_MAX_DTC_NUMBER)
      {
         LusNumberOfFilteredDTC = DEM_J1939RDY_MAX_DTC_NUMBER;
      }
      DataValue->ucPreviouslyActiveDiagnosticTroubleCodes = (uint8)LusNumberOfFilteredDTC;
    }
    else
    {
      return E_NOT_OK;
    }

    
    /*  Byte 3 :   */
    DataValue->ucOBDCompliance = (uint8)DEM_OBD_COMPLIANCE;
    
    DataValue->ucContinuouslyMonitoredSystemsSupport_Status = 0;
    DataValue->usNonContinuouslyMonitoredSystemsSupport = 0;
    DataValue->usNonContinuouslyMonitoredSystemsStatus = 0;

    for(evIndex = 0; evIndex < DEM_NUMBER_OF_EVENTS ; evIndex++)
    {
      P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) cbDTC = Dem_GetCbDTCByEventId(evIndex+1);
      if ((NULL_PTR != cbDTC) && (DEM_NO_DTC != cbDTC->usObdDtc))
      {      
        #if(DEM_DTC_SUPPRESSION_SUPPORT == STD_ON)      
        /* Refer to Dem_SetDTCSuppression */
        if (DEM_FALSE == Dem_EvIsProcStateTriggered(evIndex+1, DEM_EVPROCSTATE_DTC_SUPP)) 
        #endif
        {
        
          Dem_UdsStatusByteType dtcStatus = Dem_GetDTCStatus(evIndex+1);  
          boolean tested = 0;
          if((DEM_UDS_STATUS_TNCSLC & dtcStatus) == 0)
          {
            tested = 1;
          }


          if (rdGrp[Dem_Event[evIndex].ulEventOBDReadinessGroup] == DEM_TRUE)
          {
            if((DEM_OBD_RDY_MISF == Dem_Event[evIndex].ulEventOBDReadinessGroup) || (DEM_OBD_RDY_FLSYS == Dem_Event[evIndex].ulEventOBDReadinessGroup) 
              || (DEM_OBD_RDY_CMPRCMPT == Dem_Event[evIndex].ulEventOBDReadinessGroup))
            {
              DataValue->ucContinuouslyMonitoredSystemsSupport_Status = DataValue->ucContinuouslyMonitoredSystemsSupport_Status|(uint8)shiftMask[Dem_Event[evIndex].ulEventOBDReadinessGroup];
              if(!tested)
              {
                DataValue->ucContinuouslyMonitoredSystemsSupport_Status = DataValue->ucContinuouslyMonitoredSystemsSupport_Status|(uint8)(shiftMask[Dem_Event[evIndex].ulEventOBDReadinessGroup]<<4);
              }

            }
            else
            {
              DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|shiftMask[Dem_Event[evIndex].ulEventOBDReadinessGroup];
              if(!tested)
              {
                DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|shiftMask[Dem_Event[evIndex].ulEventOBDReadinessGroup];
              }
            }
          }

#if 0
          /*  Byte 4 :   */
          if(DEM_OBD_RDY_MISF == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->ucContinuouslyMonitoredSystemsSupport_Status = DataValue->ucContinuouslyMonitoredSystemsSupport_Status|0x01;
            if(!tested)
            {
              DataValue->ucContinuouslyMonitoredSystemsSupport_Status = DataValue->ucContinuouslyMonitoredSystemsSupport_Status|0x10;
            }
          }
          else if(DEM_OBD_RDY_FLSYS == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->ucContinuouslyMonitoredSystemsSupport_Status = DataValue->ucContinuouslyMonitoredSystemsSupport_Status|0x02;
            if(!tested)
            {
              DataValue->ucContinuouslyMonitoredSystemsSupport_Status = DataValue->ucContinuouslyMonitoredSystemsSupport_Status|0x20;
            }
          }
          else if(DEM_OBD_RDY_CMPRCMPT == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->ucContinuouslyMonitoredSystemsSupport_Status = DataValue->ucContinuouslyMonitoredSystemsSupport_Status|0x04;
            if(!tested)
            {
              DataValue->ucContinuouslyMonitoredSystemsSupport_Status = DataValue->ucContinuouslyMonitoredSystemsSupport_Status|0x40;
            }
          } 
          /*  Byte 5 :   */
          else if(DEM_OBD_RDY_CAT == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0001;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0001;
            }
          }
          else if(DEM_OBD_RDY_HTCAT == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0002;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0002;
            }
          }
          else if(DEM_OBD_RDY_EVAP == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0004;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0004;
            }
          }
          else if(DEM_OBD_RDY_SECAIR == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0008;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0008;
            }
          }
          else if(DEM_OBD_RDY_AC == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0010;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0010;
            }
          }
          else if(DEM_OBD_RDY_EGSENS == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0020;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0020;
            }
          }
          else if(DEM_OBD_RDY_O2SENSHT == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0040;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0040;
            }
          }
          else if(DEM_OBD_RDY_EGR == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0080;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0080;
            }
          } 
          /*  Byte 6, 7 :   */
          else if(DEM_OBD_RDY_O2SENS == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0100;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0100;
            }
          }
          else if(DEM_OBD_RDY_BOOSTPR == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0200;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0200;
            }
          }
          else if(DEM_OBD_RDY_PMFLT == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0400;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0400;
            }
          }
          else if(DEM_OBD_RDY_NOXCAT == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x0800;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x0800;
            }
          }
          else if(DEM_OBD_RDY_HCCAT == Dem_Event[evIndex].ulEventOBDReadinessGroup)
          {
            DataValue->usNonContinuouslyMonitoredSystemsSupport = DataValue->usNonContinuouslyMonitoredSystemsSupport|0x1000;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystemsStatus = DataValue->usNonContinuouslyMonitoredSystemsStatus|0x1000;
            }
          }
          else
          {
            /* Do Nothging  */

          }
#endif
        }
      }
    }

  }

	return retVal;
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmReadDiagnosticReadiness2                **
**                                                                            **
** Service ID           : 0x9c                                                **
**                                                                            **
** Description          : Service to report the value of DiagnosticReadiness2 **
**                        (DM5) computed by the Dem.                          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 NodeAddress                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_J1939DcmDiagnosticReadiness2Type* DataValue,    **
**                                                                            **
** Return parameter     :                                                     **
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
#if(DEM_OBD_SUPPORT == STD_ON)
#if (DEM_J1939_READINESS2_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness2(
	Dem_J1939DcmDiagnosticReadiness2Type* DataValue,
	uint8 NodeAddress )
{
	Std_ReturnType retVal = E_OK;

	/* Check module Initialization status */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMREADDIAGNOSTICREADINESS2_SID, DEM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (NULL_PTR == DataValue)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMREADDIAGNOSTICREADINESS2_SID, DEM_E_PARAM_POINTER);
    retVal = E_NOT_OK;
  }
  #endif    
  else
  {
    uint8 PIDValue[2];

    /*  Byte 1-2 : Distance Traveled While MIL is activated (PID 0x21)  */
    Dem_DcmReadDataOfPID21(PIDValue);

    DataValue->usDistanceTraveledWhileMILisActivated = PIDValue[1]<<8;
    DataValue->usDistanceTraveledWhileMILisActivated |= PIDValue[0];
    


    if(DataValue->usDistanceTraveledWhileMILisActivated > DEM_J1939RDY_MAX_DISTANCE)
    {
      DataValue->usDistanceTraveledWhileMILisActivated = DEM_J1939RDY_MAX_DISTANCE;
    }
    /*  Byte 3-4 : Distance Since DTC Cleared (PID 0x31)  */

    Dem_DcmReadDataOfPID31(PIDValue);

    DataValue->usDistanceSinceDTCsCleared= PIDValue[1]<<8;
    DataValue->usDistanceSinceDTCsCleared |= PIDValue[0];
    

    if(DataValue->usDistanceSinceDTCsCleared > DEM_J1939RDY_MAX_DISTANCE)
    {
      DataValue->usDistanceSinceDTCsCleared = DEM_J1939RDY_MAX_DISTANCE;
    }

    /*  Byte 5-6 : Minutes Run by Engine While MIL is Activated (PID 0x4D)  */

    Dem_DcmReadDataOfPID4D(PIDValue);

    DataValue->usMinutesRunbyEngineWhileMILisActivated = PIDValue[1]<<8;
    DataValue->usMinutesRunbyEngineWhileMILisActivated |= PIDValue[0];
    

    if(DataValue->usMinutesRunbyEngineWhileMILisActivated > DEM_J1939RDY_MAX_TIME)
    {
      DataValue->usMinutesRunbyEngineWhileMILisActivated = DEM_J1939RDY_MAX_TIME;
    }

    /*  Byte 7-8 : Distance Since DTC Cleared (PID 0x4E)  */
    Dem_DcmReadDataOfPID4E(PIDValue);
    
    DataValue->usTimeSinceDiagnosticTroubleCodesCleared = PIDValue[1]<<8;
    DataValue->usTimeSinceDiagnosticTroubleCodesCleared |= PIDValue[0];
    

    if(DataValue->usTimeSinceDiagnosticTroubleCodesCleared > DEM_J1939RDY_MAX_TIME)
    {
      DataValue->usTimeSinceDiagnosticTroubleCodesCleared = DEM_J1939RDY_MAX_TIME;
    }

  }
  

	return retVal;
}
#endif
#endif


/*******************************************************************************
** Function Name        : Dem_J1939DcmReadDiagnosticReadiness3                **
**                                                                            **
** Service ID           : 0x9d                                                **
**                                                                            **
** Description          : Service to report the value of DiagnosticReadiness3 **
**                        (DM5) computed by the Dem.                          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : uint8 NodeAddress                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_J1939DcmDiagnosticReadiness3Type* DataValue,    **
**                                                                            **
** Return parameter     :                                                     **
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
#if(DEM_OBD_SUPPORT == STD_ON)
#if (DEM_J1939_READINESS3_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness3(
	Dem_J1939DcmDiagnosticReadiness3Type* DataValue,
	uint8 NodeAddress )
{
	Std_ReturnType retVal = E_OK;

	/* Check module Initialization status */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMREADDIAGNOSTICREADINESS3_SID, DEM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if (NULL_PTR == DataValue)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMREADDIAGNOSTICREADINESS3_SID, DEM_E_PARAM_POINTER);
    retVal = E_NOT_OK;
  }
  #endif    
  else
  {
    uint16 evIndex;
    uint8 PIDValue[2];

    const boolean rdGrp[] =
    {
      DEM_FALSE,
      DEM_TRUE,  /* DEM_OBD_RDY_MISF        0x01 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_AC          0x02 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_BOOSTPR     0x03 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_CAT         0x04 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_CMPRCMPT    0x05 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_EGSENS      0x06 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_EGR         0x07 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_EVAP        0x08 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_FLSYS       0x09 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_HCCAT       0x0A used   */
      DEM_TRUE,  /* DEM_OBD_RDY_HTCAT       0x0B used   */
      DEM_FALSE, /* DEM_OBD_RDY_NONE        0x0C used   */
      DEM_TRUE,  /* DEM_OBD_RDY_NOXCAT      0x0D used   */
      DEM_TRUE,  /* DEM_OBD_RDY_O2SENS      0x0E used   */
      DEM_TRUE,  /* DEM_OBD_RDY_O2SENSHT    0x0F used   */
      DEM_TRUE,  /* DEM_OBD_RDY_PMFLT       0x10 used   */
      DEM_TRUE,  /* DEM_OBD_RDY_SECAIR      0x11 used   */
    };    

    const uint16 shiftMask[] =
    {
      0x00U,
      0x01U,     /* DEM_OBD_RDY_MISF        0x01    */
      0x0010U,   /* DEM_OBD_RDY_AC          0x02    */
      0x0200U,   /* DEM_OBD_RDY_BOOSTPR     0x03    */
      0x0001U,   /* DEM_OBD_RDY_CAT         0x04    */
      0x04U,     /* DEM_OBD_RDY_CMPRCMPT    0x05    */
      0x0020U,   /* DEM_OBD_RDY_EGSENS      0x06    */
      0x0080U,   /* DEM_OBD_RDY_EGR         0x07    */
      0x0004U,   /* DEM_OBD_RDY_EVAP        0x08    */
      0x02U,     /* DEM_OBD_RDY_FLSYS       0x09    */
      0x1000,    /* DEM_OBD_RDY_HCCAT       0x0A    */
      0x0002,    /* DEM_OBD_RDY_HTCAT       0x0B    */
      0x00,      /* DEM_OBD_RDY_NONE        0x0C    */
      0x0800,    /* DEM_OBD_RDY_NOXCAT      0x0D    */
      0x0100,    /* DEM_OBD_RDY_O2SENS      0x0E    */
      0x0040,    /* DEM_OBD_RDY_O2SENSHT    0x0F    */
      0x0400,    /* DEM_OBD_RDY_PMFLT       0x10    */
      0x0008     /* DEM_OBD_RDY_SECAIR      0x11    */   
    };

    const uint16 rdGrpDisable[] =
    {
      0x00U,
      DEM_J1939RDY_DISABLE_MISF,      /* DEM_OBD_RDY_MISF        0x01    */
      DEM_J1939RDY_DISABLE_AC,        /* DEM_OBD_RDY_AC          0x02    */
      DEM_J1939RDY_DISABLE_BOOSTPR,   /* DEM_OBD_RDY_BOOSTPR     0x03    */
      DEM_J1939RDY_DISABLE_CAT,       /* DEM_OBD_RDY_CAT         0x04    */
      DEM_J1939RDY_DISABLE_CMPRCMPT,  /* DEM_OBD_RDY_CMPRCMPT    0x05    */
      DEM_J1939RDY_DISABLE_EGSENS,    /* DEM_OBD_RDY_EGSENS      0x06    */
      DEM_J1939RDY_DISABLE_EGR,       /* DEM_OBD_RDY_EGR         0x07    */
      DEM_J1939RDY_DISABLE_EVAP,      /* DEM_OBD_RDY_EVAP        0x08    */
      DEM_J1939RDY_DISABLE_FLSYS,     /* DEM_OBD_RDY_FLSYS       0x09    */
      DEM_J1939RDY_DISABLE_HCCAT,     /* DEM_OBD_RDY_HCCAT       0x0A    */
      DEM_J1939RDY_DISABLE_HTCAT,     /* DEM_OBD_RDY_HTCAT       0x0B    */
      0x00U,                          /* DEM_OBD_RDY_NONE        0x0C    */
      DEM_J1939RDY_DISABLE_NOXCAT,    /* DEM_OBD_RDY_NOXCAT      0x0D    */
      DEM_J1939RDY_DISABLE_O2SENS,    /* DEM_OBD_RDY_O2SENS      0x0E    */
      DEM_J1939RDY_DISABLE_O2SENSHT,  /* DEM_OBD_RDY_O2SENSHT    0x0F    */
      DEM_J1939RDY_DISABLE_PMFLT,     /* DEM_OBD_RDY_PMFLT       0x10    */
      DEM_J1939RDY_DISABLE_SECAIR     /* DEM_OBD_RDY_SECAIR      0x11    */   
    };
    
    /*  Byte 1-2 :   */
    Dem_ReadDataOfTimeEngineStart(PIDValue);
 
    DataValue->usTimeSinceEngineStart = PIDValue[1]<<8;
    DataValue->usTimeSinceEngineStart |= PIDValue[0];

    if(DataValue->usTimeSinceEngineStart > DEM_J1939RDY_MAX_TIME)
    {
      DataValue->usTimeSinceEngineStart = DEM_J1939RDY_MAX_TIME;
    }


    /*  Byte 3 :   */
    Dem_DcmReadDataOfPID30(PIDValue);

    if(PIDValue[0] > DEM_J1939RDY_MAX_WARMUP_NUMBER)
    {
      PIDValue[0] = DEM_J1939RDY_MAX_WARMUP_NUMBER;
    }
    DataValue->ucNumberofWarmupsSinceDTCsCleared = PIDValue[0];

    DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus = 0;
    DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = 0;
    DataValue->usNonContinuouslyMonitoredSystems = 0;
    

    /*  Byte 4 :   */    
    for(evIndex = 0; evIndex < DEM_NUMBER_OF_EVENTS ; evIndex++)
    {
      P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) cbDTC = Dem_GetCbDTCByEventId(evIndex+1);
      if ((NULL_PTR != cbDTC) && (DEM_NO_DTC != cbDTC->usObdDtc))
      {      
        #if(DEM_DTC_SUPPRESSION_SUPPORT == STD_ON)      
        /* Refer to Dem_SetDTCSuppression */
        if (DEM_FALSE == Dem_EvIsProcStateTriggered(evIndex+1, DEM_EVPROCSTATE_DTC_SUPP)) 
        #endif
        {
        
          Dem_UdsStatusByteType dtcStatus = Dem_GetDTCStatus(evIndex+1);  
          boolean tested = 0;
          if((DEM_UDS_STATUS_TNCTOC & dtcStatus) == 0)
          {
            tested = 1;
          }

          if ((rdGrp[Dem_Event[evIndex].ulEventOBDReadinessGroup] == DEM_TRUE) && ((Dem_GulEventIdDisabled & rdGrpDisable[Dem_Event[evIndex].ulEventOBDReadinessGroup]) != rdGrpDisable[Dem_Event[evIndex].ulEventOBDReadinessGroup]))
          {
            if((DEM_OBD_RDY_MISF == Dem_Event[evIndex].ulEventOBDReadinessGroup) || (DEM_OBD_RDY_FLSYS == Dem_Event[evIndex].ulEventOBDReadinessGroup) 
              || (DEM_OBD_RDY_CMPRCMPT == Dem_Event[evIndex].ulEventOBDReadinessGroup))
            {
              DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus = DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus|(uint8)shiftMask[Dem_Event[evIndex].ulEventOBDReadinessGroup];
              if(!tested)
              {
                DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus = DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus|(uint8)(shiftMask[Dem_Event[evIndex].ulEventOBDReadinessGroup]<<4);
              }

            }
            else
            {
              DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|shiftMask[Dem_Event[evIndex].ulEventOBDReadinessGroup];
              if(!tested)
              {
                DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|shiftMask[Dem_Event[evIndex].ulEventOBDReadinessGroup];
              }
            }
          }

#if 0
          /*  Byte 4 :   */
          if((DEM_OBD_RDY_MISF == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT0_MASK1) != DEM_BIT0_MASK1))
          {
            DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus = DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus|0x01;
            if(!tested)
            {
              DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus = DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus|0x10;
            }
          }
          else if((DEM_OBD_RDY_FLSYS == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT1_MASK1) != DEM_BIT1_MASK1))
          {
            DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus = DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus|0x02;
            if(!tested)
            {
              DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus = DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus|0x20;
            }
          }
          else if((DEM_OBD_RDY_CMPRCMPT == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT2_MASK1) != DEM_BIT2_MASK1))
          {
            DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus = DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus|0x04;
            if(!tested)
            {
              DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus = DataValue->ucContinuouslyMonitoredSystemsEnableCompletedStatus|0x40;
            }
          } 
          /*  Byte 5, 7 :   */
          else if((DEM_OBD_RDY_CAT == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT3_MASK1) != DEM_BIT3_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0001;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0001;
            }
          }
          else if((DEM_OBD_RDY_HTCAT == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT4_MASK1) != DEM_BIT4_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0002;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0002;
            }
          }
          else if((DEM_OBD_RDY_EVAP == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT5_MASK1) != DEM_BIT5_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0004;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0004;
            }
          }
          else if((DEM_OBD_RDY_SECAIR == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT6_MASK1) != DEM_BIT6_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0008;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0008;
            }
          }
          else if((DEM_OBD_RDY_AC == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT15_MASK1) != DEM_BIT15_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0010;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0010;
            }
          }
          else if((DEM_OBD_RDY_EGSENS == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT13_MASK1) != DEM_BIT13_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0020;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0020;
            }
          }
          else if((DEM_OBD_RDY_O2SENSHT == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT8_MASK1) != DEM_BIT8_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0040;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0040;
            }
          }
          else if((DEM_OBD_RDY_EGR == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT9_MASK1) != DEM_BIT9_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0080;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0080;
            }
          } 
          /*  Byte 6, 8 :   */
          else if((DEM_OBD_RDY_O2SENS == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT7_MASK1) != DEM_BIT7_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0100;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0100;
            }
          }
          else if((DEM_OBD_RDY_BOOSTPR == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT12_MASK1) != DEM_BIT12_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0200;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0200;
            }
          }
          else if((DEM_OBD_RDY_PMFLT == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT14_MASK1) != DEM_BIT14_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0400;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0400;
            }
          }
          else if((DEM_OBD_RDY_NOXCAT == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT11_MASK1) != DEM_BIT11_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x0800;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x0800;
            }
          }
          else if((DEM_OBD_RDY_HCCAT == Dem_Event[evIndex].ulEventOBDReadinessGroup) && ((Dem_GulEventIdDisabled & DEM_BIT10_MASK1) != DEM_BIT10_MASK1))
          {
            DataValue->usNonContinuouslyMonitoredSystemsEnableStatus = DataValue->usNonContinuouslyMonitoredSystemsEnableStatus|0x1000;
            if(!tested)
            {
              DataValue->usNonContinuouslyMonitoredSystems = DataValue->usNonContinuouslyMonitoredSystems|0x1000;
            }
          }
          else
          {
            /* Do Nothging  */

          }
#endif
        }
      }
    }

  }

	return retVal;
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dem_J1939DcmGetNextSPNInFreezeFrame                 **
**                                                                            **
** Service ID           : 0x98                                                **
**                                                                            **
** Description          : Gets next SPN                                       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : DestBuffer                                          **
**                        BufSize                                             **
**                                                                            **
** Output Parameters    : uint32* SPNSupported,                               **
**                        uint8* SPNDataLength                                **
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
#if (DEM_J1939_EXPANDED_FREEZEFRAME_SUPPORT == STD_ON)
FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE)
Dem_J1939DcmGetNextSPNInFreezeFrame(
	uint32* SPNSupported,
	uint8* SPNDataLength )
{
	Dem_ReturnGetNextFilteredElementType retVal  = DEM_FILTERED_NO_MATCHING_ELEMENT;

	  /* Check module Initialization status */
  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_SID, DEM_E_UNINIT);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ( (NULL_PTR == SPNSupported) || (NULL_PTR == SPNDataLength))
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_SID, DEM_E_PARAM_POINTER);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  else if (DEM_NO_EVENT == Dem_FilteredFFRecord.nextEvent)
  {
    DEM_REPORT_ERROR(DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_SID, DEM_E_PARAM_DATA);
    retVal = DEM_FILTERED_NO_MATCHING_ELEMENT;
  }
  #endif    
  else
  {
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > 0u) && \
		    (DEM_NUM_OF_J1939FREEZEFRAMECLASS > 0U))
    Dem_EventIdType eventId;         
    Dem_EventMemoryEntryPtrType entry; 
    Dem_SizeOfJ1939FreezeFrameDataType bufSize;

    Dem_NumOfEventMemoryEntryType idxOfEntry  = Dem_PriEvMemChronoOrderNextLoc;
    struct {
      Dem_EventIdType prioEventId;
      Dem_EventPriorityType Priority;
      Dem_J1939DcmSetFreezeFrameFilterType filerType;
    } HighestEvent = {0,0,0};


    /*  if event is deleled or aged, Dem returns the next event.*/
    while (idxOfEntry > 0U) 
    {
      Dem_NumOfEventMemoryEntryType memLoc;

      --idxOfEntry;

      memLoc= Dem_PriEvMemChronoOrder[idxOfEntry];

      if (DEM_NO_EVMEM_ENTRY != memLoc)
      {
        eventId = Dem_EvMem_GetEventIdByEvMemEntry(DEM_DTC_ORIGIN_PRIMARY_MEMORY, memLoc);  
        
        if(DEM_TRUE == Dem_EvIsProcStateTriggered(eventId, DEM_EVPROCSTATE_J1939EXFF_FILTER))
        {

          Dem_EventParameterCPCType event = &Dem_Event[eventId - 1U];            
            
          if (DEM_NO_EVENT != HighestEvent.prioEventId)
          {
            if (event->ucEventPriority < HighestEvent.Priority)
            {
              HighestEvent.prioEventId = eventId;
              HighestEvent.Priority = event->ucEventPriority; 
            }
          }
          else
          {
            HighestEvent.prioEventId = eventId;
            HighestEvent.Priority = event->ucEventPriority;
          }                       
        }
      } 
    }

    if (DEM_NO_EVENT != HighestEvent.prioEventId)
    {  
      Dem_EventMemoryEntryPtrType memEntry = 
      Dem_EvMem_GetEmEntryByMemPosition(DEM_DTC_ORIGIN_PRIMARY_MEMORY, Dem_EvMemToEventMap[HighestEvent.prioEventId]);            
    
      Dem_EvClearProcState(HighestEvent.prioEventId, DEM_EVPROCSTATE_J1939EXFF_FILTER);

      entry = Dem_EvMem_FindEntry(HighestEvent.prioEventId, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
      if (NULL_PTR != entry)
      {
        Dem_EventParameterPCType event = &Dem_Event[HighestEvent.prioEventId - 1U];    
        if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
        {

          *SPNSupported = Dem_GetDTCValue(HighestEvent.prioEventId, DEM_DTC_FORMAT_J1939);

          (void)Dem_GetSizeOfJ1939FreezeFrameData(event,&bufSize, DEM_J1939DCM_EXPANDED_FREEZEFRAME);
          *SPNDataLength = (uint8)bufSize;
      
          retVal = DEM_FILTERED_OK;

        }

      }
    }
    #endif
  }    

    

#if 0	
    /*  if event is deleled or aged, Dem returns the next event.*/
    while (Dem_FilteredFFRecord.nextEvent <= Dem_Number_Of_Events) 
    {
      if(DEM_TRUE == Dem_EvIsProcStateTriggered(Dem_FilteredFFRecord.nextEvent, DEM_EVPROCSTATE_J1939EXFF_FILTER))
      {
        eventId = Dem_FilteredFFRecord.nextEvent;
        entry = Dem_EvMem_FindEntry(eventId, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
        if (NULL_PTR != entry)
        {
          Dem_EventParameterPCType event = &Dem_Event[eventId - 1U];
          if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
          {
            *SPNSupported = Dem_GetDTCValue(eventId, DEM_DTC_FORMAT_J1939);

            (void)Dem_GetSizeOfJ1939FreezeFrameData(event, &bufSize, DEM_J1939DCM_EXPANDED_FREEZEFRAME);
            *SPNDataLength = (uint8)bufSize;
            Dem_FilteredFFRecord.nextEvent++;
            retVal = DEM_FILTERED_OK;

            break;
          }
        }
      }

      /* [1] No exist in event memory 
       * [2] end loop about all records of a freeze frame of a event  
       * [3] etc */
      Dem_EvClearProcState(Dem_FilteredFFRecord.nextEvent, DEM_EVPROCSTATE_J1939EXFF_FILTER);

      /* Increment the record count returned to dcm */
      Dem_FilteredFFRecord.nextEvent++;      
    }

//    #endif
  }
  #endif

	return retVal;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_EvMem_AddNewChronologicalOrder                  **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Add Event memory location num of the new event in   **
 **                       the order in which it occurs                        **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : DTCOrigin, MemLocation                              **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : none                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 **                                                                           **
 *******************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_AddNewChronologicalOrder(
  const Dem_DTCOriginType DTCOrigin,  
  const Dem_NumOfEventMemoryEntryType MemLocation)
{
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    if (Dem_PriEvMemChronoOrderNextLoc < Dem_SizeOfEventMemory[DTCOrigin])
    {    
      Dem_PriEvMemChronoOrder[Dem_PriEvMemChronoOrderNextLoc] = MemLocation;
      Dem_PriEvMemChronoOrderNextLoc++;
    }
  }
}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_DelChronologicalOrder                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Delete Event memory location num when it is cleared **
 **                       from Event memory                                   **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : DTCOrigin, MemLocation                              **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : none                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 **                                                                           **
 *******************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_DelChronologicalOrder(
  const Dem_DTCOriginType DTCOrigin,  
  const Dem_NumOfEventMemoryEntryType MemLocation)
{
  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {
    Dem_NumOfEventMemoryEntryType memLoc;  

    if (Dem_PriEvMemChronoOrderNextLoc <=  Dem_SizeOfEventMemory[DTCOrigin]) /* Note: less than or equal to */
    {
      for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[DTCOrigin]; memLoc++)    
      {
        if (Dem_PriEvMemChronoOrder[memLoc] == MemLocation)
        {
          Dem_NumOfEventMemoryEntryType memLocShift; 

          if (Dem_PriEvMemChronoOrderNextLoc >= 2)
          {
            /* if Dem_PriEvMemChronoOrderNextLoc is 255, Event Memory is full , valid range is 0~254 */ 
            for (memLocShift = memLoc; memLocShift < (Dem_PriEvMemChronoOrderNextLoc-1); memLocShift++)    
            {
              Dem_PriEvMemChronoOrder[memLocShift] = Dem_PriEvMemChronoOrder[memLocShift + 1];
            }
            Dem_PriEvMemChronoOrderNextLoc--;        
            Dem_PriEvMemChronoOrder[Dem_PriEvMemChronoOrderNextLoc] = DEM_NO_EVMEM_ENTRY;          
          }        
          else if (Dem_PriEvMemChronoOrderNextLoc == 1)
          {                
            Dem_PriEvMemChronoOrderNextLoc = 0U;        
            Dem_PriEvMemChronoOrder[0U] = DEM_NO_EVMEM_ENTRY;
          }
          else
          {
            /* Never be reached */
            Dem_PriEvMemChronoOrderNextLoc = 0U;        
            Dem_PriEvMemChronoOrder[0U] = DEM_NO_EVMEM_ENTRY;          
          }
          break;
        }
      }
    }
  }
}

/*******************************************************************************
 ** Function Name       : Dem_EvMem_InitChronologicalOrder                    **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Initialize  the chronological order of stored       **
 **                       eventts                                             **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : DTCOrigin                                           **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : none                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 **                                                                           **
 *******************************************************************************/
FUNC(void, DEM_CODE) Dem_EvMem_InitChronologicalOrder(
  Dem_DTCOriginType DTCOrigin)
{
  uint32 timeStampMax = DEM_MAX_TIMESTAMP;    
  Dem_NumOfEventMemoryEntryType memLoc;      

  if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == DTCOrigin)
  {     
    Dem_NumOfEventMemoryEntryType numStoredEntries = Dem_NumOfStoredEvtMemEntryies[DTCOrigin];  

    if (numStoredEntries <= Dem_SizeOfEventMemory[DTCOrigin]) /* Note: less than or equal to */
    {
      for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[DTCOrigin]; memLoc++)   
      {
        Dem_PriEvMemChronoOrder[memLoc] = DEM_NO_EVMEM_ENTRY;
      }  
      
      while(numStoredEntries > 0)   
      {   
        uint32 timeStampOld = 0U;
        Dem_NumOfEventMemoryEntryType memLocOld = DEM_NO_EVMEM_ENTRY;
        for (memLoc = 0U; memLoc < Dem_SizeOfEventMemory[DTCOrigin]; memLoc++)   
        {
          Dem_EventIdType eventId = Dem_EvMem_GetEventIdByEvMemEntry(DTCOrigin,memLoc);
          if (DEM_NO_EVENT != eventId)
          {
            uint32 current = Dem_EvMem_GetTimeStamp(Dem_EvMem_GetEmEntryByMemPosition(DTCOrigin, memLoc));
            if ((timeStampMax > current) && (current > timeStampOld))
            {
              timeStampOld = current;
              memLocOld = memLoc;
            }
          }
        }
        timeStampMax = timeStampOld;

        --numStoredEntries;
        Dem_PriEvMemChronoOrder[numStoredEntries] = memLocOld;
      }
      Dem_PriEvMemChronoOrderNextLoc = Dem_NumOfStoredEvtMemEntryies[DTCOrigin];
    }
  }
}


#define DEM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/* 
   polyspace:end<MISRA-C:5.1:Not a defect:Justify with annotations> Number of character is AUTOSAR standard
   polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect
   polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> Not a defect
   polyspace:end<MISRA-C:8.8:Not a defect:Justify with annotations> Not a defect 
*/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

