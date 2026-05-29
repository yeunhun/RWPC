/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_EventCallback.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of call of event related callbacks                  **
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
** 3.3.4    31-12-2021    LanhLT       Changes made As per Redmine #33335     **
**                                                                            **
** 1.4.2    04-09-2020   EunKyung.Kim  Changes made As per Redmine #25254     **
**                                                                            **
** 1.4.1     20-07-2017  EunKyung.Kim  Changes made As per Redmine #9294      **
**                                                                            **
** 1.4.0     30-09-2016  YoungJin.Yun  Changes made As per Redmine #5921      **
**                                                                            **
** 1.3.0     30-08-2016  YoungJin.Yun  Changes made As per Redmine #5011      **
**                                                                            **
** 1.2.0     16-05-2016  YoungJin.Yun  Changes made As per Redmine #1164      **
**                                                                            **
** 1.0.0     02-07-2015  YoungJin.Yun  Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"            /* DEM module Header File */
#include "Dem_Ram.h"        /* DEM Ram Header File */

#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"            /* Det Module Header File */
#endif
#if ((DEM_FIM_INTEGRATED == STD_ON) && (DEM_TRIGGER_FIM_REPORTS == STD_ON))
#include "FiM.h"              /* FiM module header file */
#endif

#if (DEM_TRIGGER_DLT_REPORTS == STD_ON)
#include "Dlt.h"
#endif

#if (DEM_TRIGGER_DCM_REPORTS == STD_ON)
#include "Dcm.h"
#endif


#include "NvM.h"              /* NVRAM manager symbols Header File */

#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "Rte_Dem.h"

#include "Dem_Dtc.h"
#include "Dem_Event.h"
#include "Dem_EventCallback.h"

#if (DEM_J1939_SUPPORT == STD_ON)
#include "J1939Dcm_Cbk.h"
#endif

/* polyspace-begin MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/


#define DEM_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************
 * Function Name        : Dem_TriggerCallbackOnUdsStatus == 2
 *
 * Service ID           : None
 *
 * Description          : Trigger the callback functions on event status change
 *
 * Sync/Async           : Synchronous/Asynchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event, EventStatusByteOld, EventStatusByteNew
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *
 *                        Dcm_DemTriggerOnDTCStatus
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_TriggerCallbackOnUdsStatus(
  const Dem_EventIdType EventId,
  const Dem_UdsStatusByteType EventStatusByteOld,
  const Dem_UdsStatusByteType DTCStatusOld)
{
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to false. Avoid the runtime error of the polyspace */        
  if ((DEM_NO_EVENT != EventId) && (EventId <= Dem_Number_Of_Events) )
  #endif
  {  
    const Dem_UdsStatusByteType EventStatusByteNew = Dem_AllEventStatusByte[EventId];

    /* if eventStatus is not changed, DTCStatus will be not changed */  
    if (EventStatusByteOld != EventStatusByteNew)
    {
      Dem_EventParameterPCType event = &Dem_Event[EventId - 1U];
      
      /* if callbacks EventStatusChanged are configured , Dcm shall invoke all configured callbacks */          
      /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      if((0U != event->ddNumOfEventStatusFct) && 
         (0U != ((EventStatusByteOld ^ EventStatusByteNew) & Dem_Status_Availability_Mask)) )
      {       
        Dem_NumOfEvtStatFctsType max = event->PointToEventStatusFncMap + event->ddNumOfEventStatusFct;
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */    
        if (max <= Dem_Max_ListOfEvtStatusChangedFctPtr)
        {
          Dem_NumOfEvtStatFctsType idx;          
          for (idx = event->PointToEventStatusFncMap; idx < max; idx++)
          {           
            /* notify Application/Bsw that Event Status has changed */
            /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
            /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */    
            /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
	        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
	        if (NULL_PTR != Dem_ListOfEvtStatusChangedFctPtr[idx])
            {
              (void)Dem_ListOfEvtStatusChangedFctPtr[idx](EventStatusByteOld, EventStatusByteNew);
            }
          }
        }
      }

      /* #if (DEM_GENERAL_INTERFACE_SUPPORT == STD_ON) */
      (void)Rte_Call_GeneralCBStatusEvt_EventStatusChanged(EventId,EventStatusByteOld, EventStatusByteNew);
      /* #endif */

      /* Trigger FIM on event status changes */      
      #if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
        #if (DEM_FIM_INTEGRATED == STD_ON)
        FiM_DemTriggerOnEventStatus (EventId, EventStatusByteOld, EventStatusByteNew);
        #else 
        #error "In case DemTriggerFiMReports is true, DemFimIntegrated shall be true"
        #endif
      #endif
    
      /* Trigger DLT on event status changes */
      #if(DEM_TRIGGER_DLT_REPORTS == STD_ON)
      Dlt_DemTriggerOnEventStatus(EventId, EventStatusByteOld, EventStatusByteNew);
      #endif    

      /* Has DTC ? */
      if (event->e_PointToDTC < Dem_Max_Number_Of_DTC)
      {
        const Dem_UdsStatusByteType DTCStatusNew = Dem_GetDTCStatus(EventId);
        Dem_CombinedDtcPCType cbDTC = &Dem_GaaCombinedDtc[event->e_PointToDTC];

        #if (DEM_TRIGGER_DCM_REPORTS == STD_ON)
        /* @IF_REQ : Apply cbDTC->UdsStatusAvailabilityMask : Generator shall be modified  */
        if (((DTCStatusOld ^ DTCStatusNew) & Dem_Status_Availability_Mask) != 0U)
        {              
          if (DEM_NO_DTC != cbDTC->ulUdsDtc)
          {
            /* [SWS_Dem_00284] The Dem module shall trigger the callback function configured
             * in DemCallbackDTCStatusChanged on every DemDTC status change.
             * 
             * ECUC_Dem_00626 :Status change notifications are supported for DTCs in primary memory only.*/
            if (DEM_DTC_ORIGIN_PRIMARY_MEMORY == event->aaEventDestination)
            {
              uint32 cbkIdx = 0U;
              while(cbkIdx < Dem_Max_Num_Of_DTC_Stat_Chng_Fcts)
              {  
                /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to false. Avoid the runtime error of the polyspace */                    
                /* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations  a defect> Enter comment here */
                if (NULL_PTR != Dem_GaaDtcStatusChangedFctPtr[cbkIdx])
                /* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations  a defect> Enter comment here */                
                {
                  Dem_GaaDtcStatusChangedFctPtr[cbkIdx](cbDTC->ulUdsDtc, DTCStatusOld, DTCStatusNew);
                }
                ++cbkIdx;
              }
            }
      
            /* Dem565: If the Dem module informs the Dcm module about a status change of a DTC. */
            /* [SWS_Dem_00255] Triggers on changes of the UDS DTC status byte. 
             * Allows to trigger on ROE Event for subservice OnDTCStatusChanged. */           
            
            (void)Dcm_DemTriggerOnDTCStatus(cbDTC->ulUdsDtc, DTCStatusOld, DTCStatusNew);
          } /* End of if (DEM_NO_DTC != cbDTC->ulUdsDtc) */

          /* @IF_REQ
           * [SWS_Dem_00987] The Dem module shall trigger the callback function configured
           * in DemCallbackJ1939DTCStatusChanged on every DemJ1939DTC status change. */                       

          /* @IF_REQ
           * [SWS_Dem_00986] The Dem module shall trigger the callback function configured
           * in DemCallbackOBDDTCStatusChanged on every DemObdDTC status change. */          
        }
        #else
        #if ( 0 != DEM_MAX_NUM_OF_DTC_STAT_CHNG_FCTS)
        /* @IF_REQ : Apply cbDTC->UdsStatusAvailabilityMask : Generator shall be modified  */
        if (
        /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
        (DEM_NO_DTC != cbDTC->ulUdsDtc) && 
          (DEM_DTC_ORIGIN_PRIMARY_MEMORY == event->aaEventDestination) && 
          (0U != ((DTCStatusOld ^ DTCStatusNew) & Dem_Status_Availability_Mask))
        )
        {
          /* [SWS_Dem_00284] The Dem module shall trigger the callback function configured
            * in DemCallbackDTCStatusChanged on every DemDTC status change.
            * 
            * ECUC_Dem_00626 :Status change notifications are supported for DTCs in primary memory only.*/
          uint32 cbkIdx = 0U;
          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
          while(cbkIdx < Dem_Max_Num_Of_DTC_Stat_Chng_Fcts)
          {
            /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
            /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
            /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to false. Avoid the runtime error of the polyspace */                    
            if (NULL_PTR != Dem_GaaDtcStatusChangedFctPtr[cbkIdx])
            {
              Dem_GaaDtcStatusChangedFctPtr[cbkIdx](cbDTC->ulUdsDtc, DTCStatusOld, DTCStatusNew);
            }
            ++cbkIdx;
          }
        }
        #endif
        #endif
        
        #if (DEM_J1939_SUPPORT == STD_ON)
        if (DEM_NO_DTC != cbDTC->J1939DTCValue)
        {
          /* [SWS_Dem_00971] In case the TestFailed bit in the event status changes
           * and a J1939 DTC number is assigned to that event parameter, the function
           * J1939Dcm_DemTriggerOnDTCStatus shall be called. */   
          if (((DTCStatusOld ^ DTCStatusNew) & DEM_UDS_STATUS_TF) != 0U)             
          {
            /* polyspace<MISRA-C:8.1:Not a defect:Justify with annotations  a defect> This function is defined by Dcm */
            /* polyspace<MISRA-C:16.10:Not a defect:Justify with annotations  a defect> This don't return error information */
            J1939Dcm_DemTriggerOnDTCStatus(cbDTC->J1939DTCValue);            
          }
        }
        #endif
      }
    }
  }
}

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/





