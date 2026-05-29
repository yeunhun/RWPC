/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_DltIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of Dlt interface functionality                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.0.7    04-09-2020  EunKyung.Kim   Changes made As per Redmine #25254     **
**                                                                            **
** 1.0.6    20-07-2017  EunKyung.Kim   Changes made As per Redmine #9294      **
**                                                                            **
** 1.0.5    11-Jan-2014   YJ.Yun       Changes made As per Redmine #366,#367, **
**                                     #368,#371,#372,#405,#366,#367,#368,    **
**                                     #371,#372,#405,#369,#373,#374,#375,    **
**                                     #376,#370,#377,#381,#382,#383,#384,    **
**                                     #385,#386,#387,#388,#389,#390,#391,    **
**                                     #397,#398,#399,#400,#378,#380,#401,    **
**                                     #403,#404,#406,#409,#410,#411,#412     **
**                                                                            **
** 1.0.0     01-Jan-2013   Autron      Initial Version                        **
*******************************************************************************/


/*----------------------------------------------------------------------------*
 *                              @IF_REQ List                                     *
 *----------------------------------------------------------------------------*
 * 1. DLT Support
 *----------------------------------------------------------------------------*/
 
 
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"                /* DEM module Header File */
#include "Dem_Ram.h"            /* DEM Ram Header File */

#include "NvM.h"              /* NVRAM manager symbols Header File */

#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                /* Det Module Header File */
#endif
#if (DEM_TRIGGER_DLT_REPORTS == STD_ON)
#include "Dlt.h"
#endif
#include "Dem_Dtc.h"
#include "Dem_Event.h"
#include "Dem_EventMemory.h"
#include "Dem_EventRelatedData.h"


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dem_DltGetMostRecentFreezeFrameRecordData           **
**                                                                            **
** Service ID           : 0x41                                                **
**                                                                            **
** Description          : It is used by Dlt  to get the most recent freeze    **
**                        frame data.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : EventId                                             **
**                                                                            **
** InOut parameter      : BufSize                                             **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Dem_GucInit,                                        **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked  :                              **
**                        Det_ReportError                                     **
**                        Dem_GetPIDDataOnRequest                             **
**                        Dem_CalcSizeOfDID                                   **
*******************************************************************************/
#if (DEM_TRIGGER_DLT_REPORTS == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)Dem_DltGetMostRecentFreezeFrameRecordData
 (Dem_EventIdType EventId, uint8* DestBuffer, uint16* BufSize)
{
  Std_ReturnType retVal = E_NOT_OK;
  
  Dem_DTCOriginType DTCOrigin = 0U;

  Dem_EventParameterPCType event = NULL_PTR;
  Dem_SizeOfFreezeFrameClassType size = 0U;
  Dem_EventMemoryEntryPtrType MemEntry = NULL_PTR;  
  
  /* @IF_REQ : NOT COMPLETED YET.....   I've no time to implement. */

  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, 
                      DEM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if(NULL_PTR == DestBuffer)
  {
    DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, 
                      DEM_E_PARAM_POINTER);
    retVal = E_NOT_OK;
  }
  else if(NULL_PTR == BufSize)
  {
    DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, 
                      DEM_E_PARAM_POINTER);
    retVal = E_NOT_OK;
  }
  else if ((EventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == EventId))  
  {
    DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, 
                      DEM_E_PARAM_CONFIG);
    retVal = E_NOT_OK;
  }
  #endif    
  else
  { 
    #if(DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)  
    event = &Dem_Event[EventId-1U];   
    if (E_NOT_OK == Dem_GetEventDTCOrigin(event, &DTCOrigin))
    {
      DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, 
                        DEM_E_PARAM_CONFIG);  
      retVal = E_NOT_OK;
    }
    #if (DEM_OBD2_SUPPORT == STD_ON)
    else if (DEM_DTC_FORMAT_OBD == event->ddDtcFormat)
    {
      /* Not impemented yet */
      if (true == event has obdff)
      if (E_NOT_OK == Dem_GetSizeOfOBDFreezeFrameData(event, DEM_TRUE, 0U, &size))
      {
        DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, DEM_E_PARAM_CONFIG);
      } 
      else if(*BufSize < size)
      {  
        DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, DEM_E_PARAM_LENGTH);
      }
      else
      {
        MemEntry = Dem_EvMem_FindEntry(event, DTCOrigin);
        if (NULL_PTR == MemEntry)
        {
          DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, DEM_E_NODATAAVAILABLE);       
        }
        /* ignore pid number , ignore data index */ 
        else if (E_NOT_OK == Dem_GetReadDataOfPID(MemEntry, DestBuffer, DEM_TRUE, 0U, DEM_TRUE, 0U) 
        {
          DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, DEM_E_NODATAAVAILABLE);                 
        }
        else
        {
          *BufSize = size;
          retVal = E_OK;
        }
      }
    }
    #endif  
    else  
    {
      Dem_ReturnReadEventDataType result = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
      #if(DEM_SIZE_OF_FREEZEFRAME > 0U)      
      if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
      {
        result = Dem_ReadDataOfFreezeFrame(
          &Dem_EventRelatedData[event->e_PointToData], DTCOrigin, 
          DEM_RDFF_RECENT_FFRECNUM, DEM_TRUE, DEM_DATAID_IGNORED, 
          DEM_FFFORMAT_TYPE_RAW, DestBuffer, BufSize);
      }
      #endif
      switch(result)
      {
        case DEM_GET_READEVDATA_OK:
          /* *BufSize is updated in the Dem_ReadDataOfFreezeFrame */        
          retVal = E_OK; 
          break;
        case DEM_GET_READEVDATA_WRONG_BUFFERSIZE:
          DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, DEM_E_PARAM_LENGTH);          
          /* No break */          
        case DEM_GET_READEVDATA_NOT_STORED:
          /* No break */
        case DEM_GET_READEVDATA_WRONG_RECORDNUMBER:
          /* No break */
        default:
          DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, DEM_E_NODATAAVAILABLE);         
          retVal = E_NOT_OK;
          break;
      }
    }
    #else
    DEM_REPORT_ERROR(DEM_DLTGETMOSTRECENTFREEZEFRAMERECORDDATA_SID, DEM_E_PARAM_CONFIG);
    retVal = E_NOT_OK;
    #endif    
  }

  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_DltGetAllExtendedDataRecords                    **
**                                                                            **
** Service ID           : 0x40                                                **
**                                                                            **
** Description          : Used by Dlt to get extended data records.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : EventId                                             **
**                                                                            **
** InOut parameter      : BufSize                                             **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if((DEM_SIZE_OF_EXTENDED_DATA > 0u) && \
  (DEM_TRIGGER_DLT_REPORTS == STD_ON))
FUNC(Std_ReturnType, DEM_CODE)Dem_DltGetAllExtendedDataRecords
  (Dem_EventIdType EventId, uint8* DestBuffer, uint16* BufSize)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint16 totalSize = 0U; 

  if(DEM_INIT != Dem_GucInit)
  {
    DEM_REPORT_ERROR(DEM_DLTGETALLEXTENDEDDATARECORDS_SID, DEM_E_UNINIT);
    /* retVal = E_NOT_OK; */    
  }
  #if (DEM_DEV_ERROR_DETECT == STD_ON)  
  else if ((NULL_PTR == BufSize) || (NULL_PTR == DestBuffer))
  {
    DEM_REPORT_ERROR(DEM_DLTGETALLEXTENDEDDATARECORDS_SID, DEM_E_PARAM_POINTER);
   /* retVal = E_NOT_OK; */
  }
  #endif  
  else
  {
    /* if (DEM_TRUE == Dem_EventIdIsValid(EventId)) */
    if ((EventId <= Dem_Number_Of_Events) && (DEM_NO_EVENT != EventId))
    {
      Dem_DTCOriginType dtcOrigin = DEM_NO_DTC_ORIGIN;     
      Dem_EventParameterPCType event = &Dem_Event[EventId - 1U];

      if (DEM_TRUE == Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_DTC_SUPP))
      {
        DEM_REPORT_ERROR(DEM_DLTGETALLEXTENDEDDATARECORDS_SID, DEM_E_PARAM_CONFIG);
        /* retVal = E_NOT_OK; */
      }
      else if (E_NOT_OK == Dem_GetEventDTCOrigin(event, &dtcOrigin))
      {
        DEM_REPORT_ERROR(DEM_DLTGETALLEXTENDEDDATARECORDS_SID, DEM_E_PARAM_CONFIG);
        /* retVal = E_NOT_OK; */
      }
      else if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
      { 
        Dem_ReturnReadEventDataType 
        result = Dem_ReadDataOfExtendedData(&Dem_EventRelatedData[event->e_PointToData], 
                  dtcOrigin, DEM_MAX_RECORD, DestBuffer, BufSize);
        switch(result)
        {
          case DEM_GET_READEVDATA_OK:
            retVal = E_OK; 
            break;
          case DEM_GET_READEVDATA_NOT_STORED:
            /* retVal = E_NOT_OK; */
            break;
          case DEM_GET_READEVDATA_WRONG_BUFFERSIZE:
            DEM_REPORT_ERROR(DEM_DLTGETALLEXTENDEDDATARECORDS_SID, DEM_E_PARAM_LENGTH);
            /* retVal = E_NOT_OK; */
            break;
          /* case DEM_GET_READEVDATA_WRONG_RECORDNUMBER: */
          default:
            DEM_REPORT_ERROR(DEM_DLTGETALLEXTENDEDDATARECORDS_SID, DEM_E_PARAM_CONFIG);
            /* retVal = E_NOT_OK; */
            break;
        }
      }
      else
      {
        /* retVal = E_NOT_OK; */
      }
    }
    else
    {
      DEM_REPORT_ERROR(DEM_DLTGETALLEXTENDEDDATARECORDS_SID, DEM_E_PARAM_CONFIG);
      /* retVal = E_NOT_OK; */
    }    
  }

  return (retVal);
}
#endif

  /* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/





