/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_EventRelatedData.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provision of event related data functionality                 **
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
** 3.3.3    19-10-2021    LanhLT         Changes made As per Redmine #31660   **
**                                                                            **
** 1.2.3    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.2.2    01-06-2020    EunKyung.Kim    Changes made As per Redmine #20595  **
**                                                                            **    
** 1.2.1    31-01-2019    EunKyung.Kim    Changes made As per Redmine #14481  **
**                                                                            **
** 1.2.0    10-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.1.2    20-07-2017  EunKyung.Kim  Changes made As per Redmine #9294       **
**                                                                            **
** 1.1.1    10-06-2016  YoungJin.Yun  Changes made As per Redmine #5169       **
**                                                                            **
** 1.1.0    07-01-2016  YoungJin.Yun  Changes made As per Redmine #3353,      **
**                                     #698 , #3638, #2473, #3271, #2827,     **
**                                     #1151, #2589                           **
**                                                                            **
** 1.0.0    02-07-2015  YoungJin.Yun  Initial Version                         **
*******************************************************************************/

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
#include "Rte_Dem.h"

#include "Dem_Event.h"
#include "Dem_EventRelatedData.h"
#include "Dem_EventMemory.h"

#if(DEM_OBD_SUPPORT == STD_ON)
#include "Dem_Obd.h"
#endif



/* polyspace:begin<MISRA-C:1.1:Not a defect:No action planned> Not defect  */ 
/* polyspace-begin MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */ 
/* polyspace-begin DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (DEM_SIZE_OF_EXTENDED_DATA> 0u)
static FUNC(boolean, DEM_CODE)
Dem_CaptureEDClass(
  Dem_ExtendedDataClassCPCType EDDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize,  
  Dem_EventOccurrenceType EventOccurrence);
 
#endif

#if (DEM_SIZE_OF_EVENT_DATA > 0u)
static FUNC(boolean, DEM_CODE) 
Dem_CaptureDataElementClass(
  uint16 DataClassMap,
  const Dem_NumOfDataElementClassType NumOfDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize);
  

static FUNC(void, DEM_CODE)
Dem_CaptureInternalDataElementClass(
  const Dem_EventIdType EventId,
  const Dem_DTCOriginType DTCOrigin,
  Dem_EventMemoryEntryPtrType MemEntry,
  const uint16 DataClassMap,
  const Dem_NumOfDataElementClassType NumOfDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer);
#endif  

#if (DEM_SIZE_OF_FREEZEFRAME > 0U)
static FUNC(Dem_SizeOfFreezeFrameClassType, DEM_CODE) 
Dem_GetSizeOfFreezeFrameData(
  Dem_FreezeFrameClassPCType FFClass,
  const Dem_FFBufferFormatType FFBufferType);

static FUNC(Std_ReturnType, DEM_CODE) 
Dem_FFRecordNumBelongToFFClass(
  Dem_EventRelatedDataPCType EvData,
  const Dem_RecordNumberType RecordNumber,
  const Dem_NumOfRecordNumberType NumOfFFRecords,
  P2VAR(Dem_NumOfRecordNumberType, AUTOMATIC, DEM_APPL_DATA) RelRecordIndex);  

#if (DEM_MAX_NUMBER_PRESTORED_FF == 0U)
static FUNC(boolean, DEM_CODE) Dem_CaptureFFClass(
  Dem_FreezeFrameClassCPCType FFDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize);
#endif

#endif


#if (DEM_SIZE_OF_EXTENDED_DATA> 0U)

static FUNC(boolean, DEM_CODE)
Dem_StoreUdsEDClass(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry);
#endif

#if (DEM_SIZE_OF_FREEZEFRAME > 0U)
static FUNC(boolean, DEM_CODE)
Dem_StoreUdsFFClass(
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPtrType MemEntry);
#endif

#if (DEM_J1939_SUPPORT == STD_ON)
#if (DEM_NUM_OF_J1939FREEZEFRAMECLASS > 0U)
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfJ1939FreezeFrameData(
    Dem_EventParameterCPCType event,
    P2VAR(Dem_SizeOfJ1939FreezeFrameDataType, AUTOMATIC, DEM_APPL_DATA) BufSize, 
    Dem_J1939DcmSetFreezeFrameFilterType j1939FFType);
#endif
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_START_SEC_CODE
#include "MemMap.h"

#if (DEM_SIZE_OF_FREEZEFRAME > 0U)  
/******************************************************************************
 * Function Name        : Dem_FFRecordNumBelongToFFClass
 *
 * Service ID           : None
 *
 * Description          : Checks whether input record number belongs to Freeze
 *                        Frame Class
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : FFClass
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DestBuffer
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_DidClass
 *
 *                        Function(s) invoked :
 *****************************************************************************/
static FUNC(Std_ReturnType, DEM_CODE) 
Dem_FFRecordNumBelongToFFClass(
  Dem_EventRelatedDataPCType EvData,
  const Dem_RecordNumberType RecordNumber,
  const Dem_NumOfRecordNumberType NumOfFFRecords,
  P2VAR(Dem_NumOfRecordNumberType, AUTOMATIC, DEM_APPL_DATA) RelRecordIndex)
{
  Std_ReturnType retVal = E_NOT_OK;  

  uint16 maxFFRecord = EvData->FFRecordNumPos + (uint16)NumOfFFRecords;
  if (maxFFRecord <= Dem_Max_ListOfFFRecordNumbers) /* Note : <= */
  {
    uint16 iRecord;
    for (iRecord = EvData->FFRecordNumPos; iRecord < maxFFRecord; iRecord++)
    {
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */	
      if (RecordNumber == Dem_ListOfFFRecordNumbers[iRecord])
      {
        /* Range : 0~ 255 */
        uint16 idxFromZero = iRecord - EvData->FFRecordNumPos;
        *RelRecordIndex = (Dem_NumOfRecordNumberType)idxFromZero;

        retVal = E_OK;
        break;
      }
    }
  }
  
  return retVal;
}

/******************************************************************************
 * Function Name        : Dem_GetSizeOfFreezeFrameByRecord
 *
 * Service ID           : None
 *
 * Description          : The API shall be used to get the size of freeze frame 
 *                        by record.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : FFClass
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DestBuffer
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_DidClass
 *
 *                        Function(s) invoked :
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) 
Dem_GetSizeOfFreezeFrameByRecord(
  Dem_EventIdType EventId,
  Dem_RecordNumberType RecordNumber,
  Dem_DTCOriginType DTCOrigin,   /* DTCOrigin is verified by caller */
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) SizeOfFreezeFrame)
{
  Std_ReturnType retVal = E_NOT_OK;  

  /* OBD */
  if (DEM_OBD_RECORD_NUMBER == RecordNumber)
  {
    #if (DEM_OBD2_SUPPORT ==  STD_ON)
    if (event->e_PointToDTC < Dem_Max_Number_Of_DTC)
    {
      @IF_REQ : Not Implemented yet
      if (DEM_DTC_FORMAT_OBD == Dem_GaaCombinedDtc[event->e_PointToDTC].ddDtcKind)
      {
       if (E_OK == Dem_EvDataGetEvDataWithOBDFreezeFrame(event, &EvData))
        {
          *SizeOfFreezeFrame = 0x0;
          /* Report size of all PIDs */
          Dem_GetSizeOfOBDFreezeFrameData(event, DEM_TRUE, 0U, SizeOfFreezeFrame);

          retVal = E_OK;
        }
      }
    }
    #endif
  }
  /* UDS */
  else 
  {
    Dem_EventParameterPCType event = &Dem_Event[EventId - 1U];    
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    if (event->e_PointToData < Dem_Num_Of_EventRelatedData)
    { 
      Dem_EventRelatedDataCPCType EvData = &Dem_EventRelatedData[event->e_PointToData];      
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */ 
      if (EvData->FFClassPos < Dem_Num_Of_FreezeFrameClass)
      {
        Dem_NumOfRecordNumberType recordIndex = 0U;
        Dem_EventMemoryEntryPtrType entry;      
        
        if (DEM_MAX_RECORD == RecordNumber) 
        {
          retVal = E_OK; /* No Error */
          *SizeOfFreezeFrame = 0x0;
          
          /* SWS_Dem_00076
           * Note: If the record number value 0xFF is requested, the Dem considers the size
           * of all stored extended data records (in the range of 0x01 to 0xEF) */
          entry = Dem_EvMem_FindEntry(EventId, DTCOrigin);
          if (NULL_PTR != entry)
          {
            *SizeOfFreezeFrame = Dem_GetSizeOfFreezeFrameData(&Dem_FreezeFrameClass[EvData->FFClassPos], DEM_FFFORMAT_TYPE_HDR_REC);     
            /* number of record that stored FF. */
            *SizeOfFreezeFrame = *SizeOfFreezeFrame * Dem_EvMem_GetRecNumOfFF(entry);
          }
        }
        else if (E_OK == Dem_FFRecordNumBelongToFFClass(
          EvData, RecordNumber, EvData->MaxNumOfFreezeFrameRecords, &recordIndex))
        {
          retVal = E_OK;              
          *SizeOfFreezeFrame = 0U;
          
          entry= Dem_EvMem_FindEntry(EventId, DTCOrigin);
          if (NULL_PTR != entry)
          {
            Dem_NumOfRecordNumberType maxCount = Dem_EvMem_GetRecNumOfFF(entry);
            if (recordIndex < maxCount)
            {            
              *SizeOfFreezeFrame = Dem_GetSizeOfFreezeFrameData(&Dem_FreezeFrameClass[EvData->FFClassPos], DEM_FFFORMAT_TYPE_HDR_REC);   
            }
          }      
        }
        else
        {
          /* retVal = E_NOT_OK;*/
        }
      }
    }
  }

  return retVal;
}


/******************************************************************************
 * Function Name        : Dem_CaptureFFClass > 2
 *
 * Service ID           : None
 *
 * Description          : Loads the Dids in the DestBuffer
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : FFClass
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DestBuffer
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_DidClass
 *
 *                        Function(s) invoked :
 *****************************************************************************/
#if (DEM_MAX_NUMBER_PRESTORED_FF == 0U)
static
#endif
FUNC(boolean, DEM_CODE) Dem_CaptureFFClass(
  Dem_FreezeFrameClassCPCType FFDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize) 
{
  boolean dirty = DEM_FALSE;
  uint16 i;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */  
  if ((NULL_PTR != FFDataClass) && (NULL_PTR != OutBuffer)) 
  #endif
  {
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
    uint16 max = FFDataClass->PointToDidMap +  FFDataClass->NumOfDidClass;
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */
    if ((BufSize >= FFDataClass->size) && (max <= Dem_Max_ListOfDidClassIndex))
    {
      uint32 idxForDst = 0U;
      for(i = FFDataClass->PointToDidMap; i < max; i++)
      {
        CONSTP2CONST(Dem_DidClassType, AUTOMATIC, DEM_CONST)
	    /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
        didClass =  &Dem_DidClass[Dem_ListOfDidClassIndex[i]];
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
        if ((idxForDst + (uint32)didClass->size) <= BufSize)
        {
          /* Read Data Element from SW-C through RTE */
          /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */
	      dirty |= Dem_CaptureDataElementClass(didClass->PointToDataElementMap,
              didClass->NumOfDataElementClass, &OutBuffer[idxForDst],didClass->size);
              
          idxForDst += didClass->size;
        }
        else
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */        
        {

        }
      }
    }
  }

  return dirty;
}
#endif

/******************************************************************************
 * Function Name        : Dem_CaptureOBDFFClass
 *
 * Service ID           : None
 *
 * Description          : It is used to load the OBD freeze frame
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : OBDClass
 *                        
 * InOut parameter      : None
 *
 * Output Parameters    : DestBuffer
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *****************************************************************************/
#if (DEM_OBD2_SUPPORT == STD_ON)
FUNC(boolean, DEM_CODE)
Dem_CaptureOBDFFClass(
    CONSTP2CONST(Dem_OBDClassType, AUTOMATIC, DEM_CONST) OBDClass,
    P2VAR(Dem_OBDFreezeFrameDataType, AUTOMATIC, DEM_VAR) OBDFreezeFrameData)
{
  boolean dirty = DEM_FALSE;
  Dem_NumOfPidDataElementType DataIndex = 0U;
  Dem_NumOfPidClassType i = 0U;
  const Dem_NumOfPidClassType NumOfPid = OBDClass->NumOfPidClass;

  CONSTP2CONST(Dem_PidClassType, AUTOMATIC, DEM_CONST) PID = OBDClass->PidClass;

  for(i = 0; i < NumOfPid; i++)
  {
    Dem_NumOfPidDataElementType j = 0U;
    const Dem_NumOfPidDataElementType NumOfPidData = PID[i].NumOfPidDataElements;

    for(j = 0; j < NumOfPidData; j++)
    {
      /* Read Data Element from SW-C through RTE */
      dirty |= Dem_CaptureDataElementClass(&PID[i].ListOfDataElementPtr[j],
          &OBDFreezeFrameData->PIDData[DataIndex][0U],
          1 /* NumOfDataElementClass */);
      DataIndex++;
    }
  }

  return dirty;
}
#endif




/******************************************************************************
 * Function Name        : Dem_CaptureEDClass
 *
 * Service ID           : None
 *
 * Description          : It is used to load the extended data.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EDClass
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DestBuffer
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_ExtendedDataRecordClass
 *
 *                        Function(s) invoked :
 *****************************************************************************/
#if (DEM_SIZE_OF_EXTENDED_DATA > 0u)
static FUNC(boolean, DEM_CODE)
Dem_CaptureEDClass(
  Dem_ExtendedDataClassCPCType EDDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize,
  Dem_EventOccurrenceType EventOccurrence)
{
  boolean dirty = DEM_FALSE;
  
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */  
  if ((NULL_PTR != EDDataClass) && (NULL_PTR != OutBuffer))
  #endif
  {
    uint32 idxForDst = 0U;
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    uint16 maxEDR = EDDataClass->PointToEDRecordMap + EDDataClass->NumOfEDRecordClass;
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */    
    if (maxEDR <= Dem_Max_ListOfEDRecordClassIndex)
    { 
      uint16 iEDR;
      /* Loop through the no. of data elements for the Did */
      for(iEDR = EDDataClass->PointToEDRecordMap; iEDR < maxEDR; iEDR++)
      { 
        CONSTP2CONST(Dem_ExtendedDataRecordClassType, AUTOMATIC, DEM_CONST) 
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
	    EDRecord = &Dem_ExtendedDataRecordClass[Dem_ListOfEDRecordClassIndex[iEDR]];      
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
        if ((idxForDst + (uint32)EDRecord->size) <= BufSize)
        {
          /* Check if the record should be updated once or every time a event fails */
            /* Check if the record should be updated once or every time a event fails */
          if ((DEM_UPDATE_RECORD_YES == EDRecord->RecordUpdate) ||
              (1U == EventOccurrence) 
              /* && (DEM_UPDATE_RECORD_NO == EDRecord->RecordUpdate)) */)    
          {
            /* Read Data Element from SW-C through RTE */
            /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */
	        dirty |= Dem_CaptureDataElementClass(EDRecord->PointToDataElementMap,
                EDRecord->NumOfDataElementClass,
                &OutBuffer[idxForDst], EDRecord->size);
          }
          idxForDst += EDRecord->size;
        }
        else
        {

        }
      }
    }
  }

  return dirty;
}
#endif

/******************************************************************************
 * Function Name        : Dem_CaptureJ1939FFClass > 2
 *
 * Service ID           : None
 *
 * Description          : Loads the Dids in the DestBuffer
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : J1939FFClass
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DestBuffer
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_DidClass
 *
 *                        Function(s) invoked :
 *****************************************************************************/
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_NUM_OF_J1939FREEZEFRAMECLASS > 0U))
static
FUNC(boolean, DEM_CODE) Dem_CaptureJ1939FFClass(
  CONSTP2CONST(Dem_J1939FreezeFrameClassType, AUTOMATIC, DEM_CONST) J1939FFDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize) 
{
  boolean dirty = DEM_FALSE;
  uint16 i;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */  
  if ((NULL_PTR != J1939FFDataClass) && (NULL_PTR != OutBuffer)) 
  #endif
  {
    uint16 max = J1939FFDataClass->PointToSpnMap +  J1939FFDataClass->NumOfSpnClass;
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */
    if ((BufSize >= J1939FFDataClass->size) && (max <= Dem_Max_ListOfSpnClassIndex))
    {
      uint32 idxForDst = 0U;
      for(i = J1939FFDataClass->PointToSpnMap; i < max; i++)
      {
        CONSTP2CONST(Dem_SPNClassType, AUTOMATIC, DEM_CONST)
        spnClass =  &Dem_SPNClass[Dem_ListOfSPNClassIndex[i]];

        if ((idxForDst + (uint32)spnClass->size) <= BufSize)
        {
          /* Read Data Element from SW-C through RTE */
          dirty |= Dem_CaptureDataElementClass(spnClass->PointToDataElementMap,
              spnClass->NumOfSpnDataElements, &OutBuffer[idxForDst],spnClass->size);
              
          idxForDst += spnClass->size;
        }
        else
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */        
        {

        }
      }
    }
  }

  return dirty;
}
#endif



#if (DEM_SIZE_OF_EVENT_DATA > 0u)

/******************************************************************************
 * Function Name        : Dem_CaptureDataElementClass > 2
 *
 * Service ID           : None
 *
 * Description          : This function is used to get the extended data or
 *                        freeze frame data from SW-C
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : PointToDataElementMap,
 *                        NumOfDataElementClass
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DestBuffer
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_DataElementClass,
 *
 *                        Function(s) invoked :
 *                        Callback ReadDataElement()
 *
 *****************************************************************************/


static FUNC(boolean, DEM_CODE)
Dem_CaptureDataElementClass(
  uint16 DataClassMap,
  const Dem_NumOfDataElementClassType NumOfDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize)
{
  boolean dirty = DEM_FALSE;
  uint16 iData = 0U;
  const uint16 maxData = DataClassMap + NumOfDataClass;    
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */    
  if ((NULL_PTR != OutBuffer) && (maxData <= Dem_Max_ListOfDataElementClassIndex))
  {
    uint32 idxForDst = 0U;
  
    /* Loop through the no. of data elements for the Did */
    for(iData = DataClassMap; iData < maxData; iData++)
    {
      uint8 result = E_NOT_OK;
      CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
      /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      elementClass = &Dem_DataElementClass[Dem_ListOfDataElementClassIndex[iData]];
      
      if ((idxForDst + (uint32)elementClass->size) <= BufSize)
      {
        if (DEM_DATA_ELEMENT_EXTERNAL == elementClass->type)
        {
          if (NULL_PTR != elementClass->ReadFunc)
          {      
            /* @IF_REQ : GeneralInterfaceSupported is false and callback event data changed is none , use destBuffer */            
            /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */                        
            result = elementClass->ReadFunc(Dem_EvEventDataCapture);
            if (E_NOT_OK == result)
            {
              DEM_REPORT_ERROR(DEM_CAPTUREDATAELEMENTCLASS_SID, DEM_E_NODATAAVAILABLE);
            }
          }
          else
          {
            DEM_REPORT_ERROR(DEM_CAPTUREDATAELEMENTCLASS_SID, DEM_E_PARAM_POINTER);
          }
        }
        /* internal data or returned value of ReadFunc is  E_NOT_OK */
        if (E_OK == result)
        {
          uint32 k;
          for (k = 0; k < elementClass->size; k++)
          {
            /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations  a defect> Rule violation by runtime error(orange) of PolySpace */
            /* polyspace<RTE:IDP:Not a defect:No action planned> Polyspace bug */            
            if ( (DEM_FALSE == dirty) && (OutBuffer[idxForDst + k] != Dem_EvEventDataCapture[k]) )
            {
              dirty = DEM_TRUE;
            }
            /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations  a defect> Rule violation by runtime error(orange) of PolySpace */
            /* polyspace<RTE:IDP:Not a defect:No action planned> Polyspace bug */            
            OutBuffer[idxForDst + k] = Dem_EvEventDataCapture[k];
          }
        }
        else
        {
          uint32 k;
          for(k = 0; k < elementClass->size; k++)
          {
           /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations  a defect> Rule violation by runtime error(orange) of PolySpace */
           /* polyspace<RTE:IDP:Not a defect:No action planned> Polyspace bug */           
            OutBuffer[idxForDst + k] = DEM_DATA_PADDING;
          }
        }
        
        idxForDst += elementClass->size;
      }
    }
  }

  return dirty;
}


/******************************************************************************
 * Function Name        : Dem_CaptureInternalDataElementClass == *1
 *
 * Service ID           : None
 *
 * Description          : This function is used to get the extended data or
 *                        freeze frame data from Dem internally
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : entry, PointToDataElementMap,
 *                        NumOfDataElementClass
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DestBuffer
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *****************************************************************************/
static FUNC(void, DEM_CODE)
Dem_CaptureInternalDataElementClass(
  const Dem_EventIdType EventId,
  const Dem_DTCOriginType DTCOrigin,
  Dem_EventMemoryEntryPtrType MemEntry,
  const uint16 DataClassMap,
  const Dem_NumOfDataElementClassType NumOfDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer)
{
  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */  
  if ((NULL_PTR != MemEntry) && (NULL_PTR != OutBuffer))
  #endif
  {
    uint16 i = 0U;  
    uint16 max = DataClassMap + NumOfDataClass;
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */
    if (max <= Dem_Max_ListOfDataElementClassIndex)
    {
      /* Loop through the no. of data elements for the Did */
      for(i = DataClassMap; i < max; i++)
      {
        Std_ReturnType result = E_NOT_OK;    
    
        CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
        /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
	    element = &Dem_DataElementClass[Dem_ListOfDataElementClassIndex[i]];
    
        if (DEM_DATA_ELEMENT_EXTERNAL != element->type)
        {
          switch(element->type)
          {            
            /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */          
            case DEM_DATA_ELEMENT_OVFLIND:
	          /* polyspace +2 MISRA-C3:10.5 [Justified:Low] "Not a defect" */	
              /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */		
              *OutBuffer = (uint8)Dem_EvMem_GetEvMemOverflowFlag(DTCOrigin);
              result = E_OK;  
            break;

            case DEM_DATA_ELEMENT_AGINGCTR:
	        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
              *OutBuffer = Dem_EvMem_GetAgingCounter(MemEntry);
              result = E_OK;
            break;
            
            case DEM_DATA_ELEMENT_OCCCTR:
	        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */	
              *OutBuffer = Dem_EvMem_GetEventOccCounter(MemEntry);
              result = E_OK;
            break;
            /* No impement */
            /* polyspace<RTE:UNR:Not a defect:No action planned> Switch-expression never evaluates to DEM_DATA_ELEMENT_SIGNIFICANCE */                        
            case DEM_DATA_ELEMENT_SIGNIFICANCE:
	        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
              *OutBuffer = DEM_GET_EVENTPARAM_SIGNIFICANCE(Dem_Event[EventId-1U].ParamFieldsA);
              result = E_OK;
            break;
            /* polyspace<RTE:UNR:Not a defect:No action planned> Default switch clause is unreachable. switch-expression */              
            default :
              DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_NODATAAVAILABLE);
              result = E_NOT_OK;
            break;
          }
          /* @IF_REQ : Det Error */
          if (E_OK != result)
          /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */          
          {
            Dem_SizeOfDataElementClassType k;
            for(k = 0; k < element->size; k++)
            {
	        /* polyspace +6 MISRA-C3:17.8 [Justified:Low] "Not a defect" */	
	        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
              OutBuffer[k] = DEM_DATA_PADDING;
            }
          }
        }
        OutBuffer = &OutBuffer[element->size];
      }
    }
  }
}

#endif

/******************************************************************************
 * Function Name        : Dem_ReadDataOfExtendedData == 2
 *
 * Service ID           : None
 *
 * Description          : Reads the extended data from an event memory
 *                        entry
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EvData, entry, ExtendedDataNumber
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DestBuffer
 *
 * Return parameter     : Std_ReturnType(E_OK or E_NOT_OK)
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *****************************************************************************/
#if (DEM_SIZE_OF_EXTENDED_DATA >  0U)
FUNC(Std_ReturnType, DEM_CODE)
Dem_ReadDataOfExtendedData(
  Dem_EventRelatedDataPCType  EvData,
  Dem_DTCOriginType DTCOrigin,
  Dem_ExtendedDataNumberType  ExtendedDataNumber,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize)
{
  Dem_ReturnReadEventDataType retVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
  /* Note: range of EvData->EventIdRef */
  if ( 
    (NULL_PTR != DestBuffer) 
      && 
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    (EvData->EDClassPos < Dem_Num_Of_ExtendedDataClass) 
      &&
    (EvData->EventIdRef <= Dem_Number_Of_Events) 
      &&
    (DEM_NO_EVENT != EvData->EventIdRef)    
  )
  {    
    Dem_ExtendedDataClassPCType extendedData = &Dem_ExtendedDataClass[EvData->EDClassPos];    
      /* In case of BufSize is 0U, Read FF regardless of a size of DestBuffer */
    uint16 extendedDataSize = Dem_GetSizeOfExtendedData(extendedData, ExtendedDataNumber, NULL_PTR);
    uint16 bufSizeForDst = (NULL_PTR != BufSize) ? *BufSize : extendedDataSize;      
    
    /* If extended data record number is invalid , 
     * returned extendedDataSize value of Dem_GetSizeOfExtendedData is zero */
    if (0U == extendedDataSize) 
    {
      retVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;      
    }
    else if ( (0U == bufSizeForDst) || (extendedDataSize > bufSizeForDst) )
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */    
    {
      retVal = DEM_GET_READEVDATA_WRONG_BUFFERSIZE;
    }
    else
    {
      Dem_EventMemoryEntryPtrType memEntry = Dem_EvMem_FindEntry(EvData->EventIdRef, DTCOrigin);
      if (NULL_PTR == memEntry)
      {
        retVal = DEM_GET_READEVDATA_NOT_STORED;
      }
      else
      {
        uint32 bufSizeForSrc = 0U;
        P2VAR(uint8, AUTOMATIC, DEM_VAR) src = Dem_EvMem_GetEDBuffer(EvData, memEntry, &bufSizeForSrc);        
        
        Dem_NumOfExtendedDataRecordClassType iEDR;
        Dem_NumOfExtendedDataRecordClassType maxEDR;

        maxEDR = extendedData->PointToEDRecordMap + extendedData->NumOfEDRecordClass;
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */        
        if ((NULL_PTR != src) && 
            (bufSizeForSrc >= extendedData->size) &&             
            (maxEDR <= Dem_Max_ListOfEDRecordClassIndex))
        {        
          uint32 idxForSrc = 0U;
          uint32 idxForDst = 0U;          
          /* Loop through the no. of data elements for the Did */
          for(iEDR = extendedData->PointToEDRecordMap; iEDR < maxEDR; iEDR++)
          {
            P2CONST(Dem_ExtendedDataRecordClassType, AUTOMATIC, DEM_CONST) 
            /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
	        EDRecord = &Dem_ExtendedDataRecordClass[Dem_ListOfEDRecordClassIndex[iEDR]];              

            #if (DEM_DEV_ERROR_DETECT == STD_ON)
	        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */	    
            if ( ((idxForDst + (uint32)EDRecord->size) > bufSizeForDst) ||
                 ((idxForSrc + (uint32)EDRecord->size) > bufSizeForSrc) )
            {
              DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_OUT_OF_BOUNDS);              
            }
            else
            #endif
            {
              /* if ExtendedDataNumber is equal to DEM_MAX_RECORD, report all records. */
              if ( (ExtendedDataNumber == EDRecord->ExtendedDataRecordNumber) ||
                  (DEM_MAX_RECORD == ExtendedDataNumber) )
              {               
                Dem_SizeOfExtendedDataClassType idx;
                /* Copy external data element from event memory entry */          
                for (idx = 0U; idx < EDRecord->size; idx++)
                {
                  /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations  a defect> Rule violation by runtime error(orange) of PolySpace */                
                  DestBuffer[idxForDst + idx] = src[idxForSrc + idx];
                }        
                /* Read Data Internal Element such as aging counter, healing counter */
                Dem_CaptureInternalDataElementClass(
                    EvData->EventIdRef,
                    DTCOrigin,
                    memEntry,
                    EDRecord->PointToDataElementMap,
                    EDRecord->NumOfDataElementClass,
                    &DestBuffer[idxForDst]);
                idxForDst += EDRecord->size;
                
                if (DEM_MAX_RECORD != ExtendedDataNumber)
                {
                  break; /* exit loop */
                }              
              }
              idxForSrc += EDRecord->size;
            }
          }

          if(0U != idxForDst)
          {
            if (NULL_PTR != BufSize)
            {
              *BufSize = extendedDataSize;
            }
            retVal = DEM_GET_READEVDATA_OK;
          } 
        }
      }
    }
  }

  return retVal;
}
#endif


/******************************************************************************
 * Function Name        : Dem_GetJ1939FreezeFrameData
 *
 * Service ID           : None
 *
 * Description          : Reads the J1939 Freeze Frame data from an event memory
 *                        entry
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : Event, DTCOrigin
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DestBuffer, BufSize
 *
 * Return parameter     : Std_ReturnType(E_OK or E_NOT_OK)
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *****************************************************************************/
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_SIZE_OF_J1939FREEZEFRAME > 0U))
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetJ1939FreezeFrameData(
    Dem_EventParameterCPCType event,
    Dem_DTCOriginType DTCOrigin,
    P2VAR (uint8, AUTOMATIC, DEM_VAR) DestBuffer,
    P2VAR (uint16, AUTOMATIC, DEM_VAR) BufSize,
    Dem_J1939DcmSetFreezeFrameFilterType j1939FFType)
{

  Dem_ReturnReadEventDataType retVal = DEM_GET_READEVDATA_OK;

  P2VAR(uint8, AUTOMATIC, DEM_VAR)   dest = DestBuffer;
  Dem_NumOfJ1939FreezeFrameClassType ffClassPos;

  P2CONST(Dem_J1939FreezeFrameClassType, AUTOMATIC, DEM_CONST) J1939ffDataClass = NULL_PTR;
  P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) cbDTC;
  P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_VAR) EvData;
  cbDTC = &Dem_GaaCombinedDtc[event->e_PointToDTC];
  EvData = &Dem_EventRelatedData[event->e_PointToData];

  if((NULL_PTR == DestBuffer) || (NULL_PTR == DestBuffer))
  {
    retVal = DEM_GET_READEVDATA_WRONG_DTC;
  }

  if (Dem_EvMem_DTCFormatIsValid(DEM_DTC_FORMAT_J1939, cbDTC) == DEM_FALSE)
  {
    /* No J1939 event */
    retVal = DEM_GET_READEVDATA_WRONG_DTC;
  }

  if(j1939FFType == DEM_J1939DCM_EXPANDED_FREEZEFRAME)
  {
    ffClassPos = EvData->J1939EXFFClassPos;
  }
  else 
  {
    ffClassPos = EvData->J1939FFClassPos;
  }
  
  J1939ffDataClass = &Dem_J1939FreezeFrameClass[ffClassPos];


  if (DEM_NO_IDX_U16 == ffClassPos) 
  {
    /* No J1939 freeze frame configured of event. */
     retVal = DEM_GET_READEVDATA_WRONG_DTC;
  }

  if (0U == J1939ffDataClass->size)
  {
    /* No obd freeze frame configured */
    retVal = DEM_GET_READEVDATA_WRONG_DTC;
  }


  if(DEM_GET_READEVDATA_OK == retVal)
  {

    uint32 bufSizeForSrc = 0U;
    Dem_EventMemoryEntryPtrType memEntry = Dem_EvMem_FindEntry(EvData->EventIdRef, DTCOrigin);
    P2VAR(uint8, AUTOMATIC, DEM_VAR) src = Dem_EvMem_GetJ1939FFBuffer(EvData, memEntry, &bufSizeForSrc, j1939FFType);
    uint16 iSpn;
    uint16 maxSpn;
    
    Dem_SizeOfSpnClassType idx;

    maxSpn = J1939ffDataClass->PointToSpnMap + J1939ffDataClass->NumOfSpnClass;



    if ((NULL_PTR != src) && 
        (bufSizeForSrc >= J1939ffDataClass->size) &&             
        (maxSpn <= Dem_Max_ListOfSpnClassIndex))
    {

      for(iSpn = J1939ffDataClass->PointToSpnMap; iSpn < maxSpn; iSpn++)
      {
        CONSTP2CONST(Dem_SPNClassType, AUTOMATIC, DEM_CONST) SPN = &Dem_SPNClass[Dem_ListOfSPNClassIndex[iSpn]];

        for(idx = 0; idx < SPN->size; idx++)
        {
          dest[idx] = src[idx];
        }

        dest = &dest[SPN->size]; /* For Read all */
        src = &src[SPN->size];
        
      }

      if(dest != DestBuffer)
      {
        if (NULL_PTR != BufSize)
        {
          *BufSize = (uint16)J1939ffDataClass->size;
        }
        retVal = DEM_GET_READEVDATA_OK;
      }
    }
    else
    {
      retVal = DEM_GET_READEVDATA_NOT_STORED;
    }
    
  }  

  return retVal;

}
#endif


#if (DEM_OBD2_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetOBDFreezeFrameData(
    Dem_EventParameterPCType event,
    Dem_DTCOriginType DTCOrigin,
    P2VAR (uint8, AUTOMATIC, DEM_VAR) DestBuffer,
    P2VAR (uint16, AUTOMATIC, DEM_VAR) BufSize)
{
  P2VAR(Dem_EventMemoryEntryType,AUTOMATIC,DEM_CONST) entry = NULL_PTR;
  Dem_SizeOfOBDFreezeFrameDataType size = 0U;
  Std_ReturnType result = 0U;

  P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) cbDTC;
  cbDTC = &Dem_GaaCombinedDtc[event->e_PointToDTC];

   

  if (DEM_DTC_FORMAT_OBD != cbDTC->ddDtcFormat)
  {
    /* No OBD event */
    return DEM_DATA_WRONG_DTC;
  }

  result = Dem_GetSizeOfOBDFreezeFrameData(event,DEM_TRUE, 0U,&size);
  if (E_NOT_OK == result)
  {
    /* No obd freeze frame configured */
    return DEM_DATA_WRONG_DTC;
  }

  if (0U == size)
  {
    /* No obd freeze frame configured */
    return DEM_DATA_WRONG_DTC;
  }

  if(*BufSize < size)
  {
    /* Target buffer size is too small */
    return DEM_DATA_WRONG_BUFFERSIZE;
  }
  
  entry = Dem_EvMem_FindEntry(Dem_GetFirstEventOfDTC(&cbDTC), DTCOrigin);
  if (NULL_PTR != entry)
  {
    /* Dem630: If Dem_GetFreezeFrameDataByDTC is called with a valid DTC and
      a valid freeze frame record number which is not stored,
      the Dem shall return DEM_GET_FFDATABYDTC_OK and BufSize 0 (empty buffer). */
    *BufSize = 0;

    return DEM_DATA_OK;
  }

  result = Dem_GetReadDataOfPID(entry, DestBuffer,
      DEM_TRUE, 0U, /* ignore pid number */
      DEM_TRUE, 0U);/* ignore data index */
  if (E_NOT_OK == result)
  {
    /* Refer to Dem630 */
    *BufSize = 0;

    return DEM_DATA_OK;
  }

  *BufSize = size;

  return DEM_DATA_OK;
}
#endif


/******************************************************************************
 * Function Name        : Dem_ReadDataOfFreezeFrame > 2
 *
 * Service ID           : None
 *
 * Description          : Reads the freeze frame data from an event memory
 *                        entry
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EvData, entry, RecordNumber, ReportTotalDid,
 *                        DataIdentifier, HeaderType
 *
 *
 * InOut parameter      : None
 *
 * Output Parameters    : DestBuffer
 *
 * Return parameter     : Std_ReturnType(E_OK or E_NOT_OK)
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *****************************************************************************/
#if(DEM_SIZE_OF_FREEZEFRAME > 0U)
FUNC(Dem_ReturnReadEventDataType, DEM_CODE)
Dem_ReadDataOfFreezeFrame(
  Dem_EventRelatedDataPCType  EvData,
  Dem_DTCOriginType DTCOrigin,
  Dem_RecordNumberType RecordNumber,
  boolean ReportTotalDid,
  Dem_DataIdentifierType DataIdentifier,
  Dem_FFBufferFormatType HeaderType,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize)
{
  Dem_ReturnReadEventDataType retVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;

  Dem_NumOfRecordNumberType iRecord = 0U;
  Dem_NumOfRecordNumberType NumOfStoredRecords = 0u;

  P2VAR(uint8, AUTOMATIC, DEM_VAR)   dest = DestBuffer;
  P2CONST(uint8, AUTOMATIC, DEM_VAR) src  = NULL_PTR;
  P2CONST(uint8, AUTOMATIC, DEM_VAR) base = NULL_PTR;
  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
  if ((DEM_NO_EVENT != EvData->EventIdRef) &&
      (EvData->EventIdRef <= Dem_Number_Of_Events) &&
      (EvData->FFClassPos < Dem_Num_Of_FreezeFrameClass) )
  {    
    /* index shall be checked by caller */
    Dem_FreezeFrameClassPCType ffDataClass = &Dem_FreezeFrameClass[EvData->FFClassPos];
    Dem_SizeOfFreezeFrameClassType FFClassSize = Dem_GetSizeOfFreezeFrameData(ffDataClass, HeaderType);    
    Dem_SizeOfFreezeFrameClassType bufSizeForDst = (NULL_PTR != BufSize) ? *BufSize : FFClassSize;

    #if (DEM_DEV_ERROR_DETECT == STD_ON)   
    if (0U == FFClassSize)
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */    
    {
      DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_CONFIG);
      retVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
    }    
    else 
    #endif
    if (bufSizeForDst < FFClassSize)
    {
      retVal = DEM_GET_READEVDATA_WRONG_BUFFERSIZE;
    }
    else if (DEM_RDFF_RECENT_FFRECNUM == RecordNumber)
    {
      retVal = DEM_GET_READEVDATA_OK;
    }
    else if (E_OK == Dem_FFRecordNumBelongToFFClass(EvData,RecordNumber,EvData->MaxNumOfFreezeFrameRecords,&iRecord))
    {
      retVal = DEM_GET_READEVDATA_OK;
    }
    else
    {          
      /* retVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER; */
    }
  
    if (DEM_GET_READEVDATA_OK == retVal)
    {
      Dem_EventMemoryEntryPtrType memEntry = Dem_EvMem_FindEntry(EvData->EventIdRef, DTCOrigin);
      
      retVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
      if (NULL_PTR != memEntry) 
      {
        uint16 maxDID = ffDataClass->PointToDidMap +  ffDataClass->NumOfDidClass;
        /* @NumOfStoredRecords shall be greater than 0 */
        NumOfStoredRecords = Dem_EvMem_GetRecNumOfFF(memEntry);
        
        /* read recent freeze frame record number , but not specific record number */
        if (DEM_RDFF_RECENT_FFRECNUM == RecordNumber)
        {
          /* get a buffer index that record number is stored */
          iRecord = NumOfStoredRecords - 1U;          
        }

        if (NumOfStoredRecords > EvData->MaxNumOfFreezeFrameRecords)
        {
          DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_CONFIG);
          /* retVal = DEM_GET_READEVDATA_WRONG_RECORDNUMBER; */
        }
        /* iRecord : index from zero */
        else if (iRecord >= NumOfStoredRecords)
        {
          retVal = DEM_GET_READEVDATA_NOT_STORED;
        }
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to true. Avoid the runtime error of the polyspace */
        else if (maxDID <= Dem_Max_ListOfDidClassIndex) /* Note : <= */
        {        
          uint16 iDID = 0U;        
          /*  [SWS_Dem_00575] : Buffer format of Freeze Frame
           *
           *  |Record Number(or N/A)| Num of DIDs | 1st DID | Data #1|... | Nth DID | Data #n |
           *
           *  Record Number : Record Number of Freeze Frame
           *  Num of DIDs : Number of all the DID.
           *  Nth DID : Size of the Nth DID */        
          base = Dem_EvMem_GetEventDataBuffer(memEntry);  
          if (NULL_PTR != base)          
          {        
            src = &base[iRecord * ffDataClass->size];    
            if(HeaderType == DEM_FFFORMAT_TYPE_HDR_REC)
            {
              /* | Record Number | Number Of DID | ... */
              dest[0U] = RecordNumber;
              dest[1U] = ffDataClass->NumOfDidClass;
              dest = &dest[2U];          
            }
            else if(HeaderType == DEM_FFFORMAT_TYPE_HDR_DID)
            /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */          
            {
              /* | Number Of DID | ... */
              dest[0U] = ffDataClass->NumOfDidClass;
              dest = &dest[1u];
            }
            else /* if(HeaderType == DEM_FFFORMAT_TYPE_RAW) */
            {
              /* | ... */        
              /* nothing to do */        
            }
        
            for(iDID = ffDataClass->PointToDidMap; iDID < maxDID ; iDID++)
            {
              /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */	
              Dem_DidClassCPCType DID = &Dem_DidClass[Dem_ListOfDidClassIndex[iDID]];        
	          /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
	          if ((DEM_TRUE == ReportTotalDid) || (DID->DataId == DataIdentifier))
              {
                Dem_SizeOfDidClassType idx;          
                if((HeaderType == DEM_FFFORMAT_TYPE_HDR_REC) || (HeaderType == DEM_FFFORMAT_TYPE_HDR_DID))
                {
		          /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
		          dest[0U] = (uint8)((DID->DataId & DEM_MASK_UPPER_BYTE) >> 8u);
                  dest[1U] = (uint8) (DID->DataId & DEM_MASK_LOWER_BYTE);
                  dest = &dest[2u];
                }        
                /* Copy external data element from event memory entry */          
                /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
	        	for (idx= 0; idx < DID->size; idx++)
                {
                  /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations  a defect> Rule violation by runtime error(orange) of PolySpace */                
                  dest[idx] = src[idx];
                }              
                dest = &dest[DID->size]; /* For Read all */
                if (DEM_FALSE == ReportTotalDid)
                {
                  break; /* exit loop */
                }
              }
              src = &src[DID->size];
            }  
            if(dest != DestBuffer)
            {
              if (NULL_PTR != BufSize)
              {
                *BufSize = FFClassSize;
              }
              retVal = DEM_GET_READEVDATA_OK;
            }          
          }
          else
          {
            DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_PARAM_CONFIG);
          }
        } 
        else
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */        
        {

        }
      }
      else
      {
        retVal = DEM_GET_READEVDATA_NOT_STORED;
      } 
    }
  }
  
  return retVal;
}


#endif

/******************************************************************************
 * Function Name        : Dem_StoreUdsEDClass == *1
 *
 * Service ID           : None
 *
 * Description          : Loads the extended data in the event memory
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EvData
 *
 * InOut parameter      : entry
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Dem_ExtendedDataRecordClass
 *
 *                        Function(s) invoked :
 *
 *****************************************************************************/
#if (DEM_SIZE_OF_EXTENDED_DATA > 0u)
/* polyspace:begin<MISRA-C:16.7:Not a defect:Justify with annotations> A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object. */
static FUNC(boolean, DEM_CODE)
Dem_StoreUdsEDClass(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType MemEntry)
{
  boolean dirty = DEM_FALSE;

  if ((NULL_PTR != MemEntry) && (EvData->EDClassPos < Dem_Num_Of_ExtendedDataClass))
  {
    uint32 bufSize = 0U;    
    Dem_ExtendedDataClassPCType edDataClass = &Dem_ExtendedDataClass[EvData->EDClassPos];      
    /* Gets ptr of buffer to save the event data(FF+EXT) of an event */
    P2VAR(uint8, AUTOMATIC, DEM_VAR) dst = Dem_EvMem_GetEDBuffer(EvData, MemEntry, &bufSize);     
    
    dirty = Dem_CaptureEDClass(edDataClass, dst, bufSize, Dem_EvMem_GetEventOccCounter(MemEntry));
  }
  
  return dirty;
}
/* polyspace:end<MISRA-C:16.7:Not a defect:Justify with annotations> A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object. */
#endif


/******************************************************************************
 * Function Name        : Dem_StoreUdsFFClass == *1
 *
 * Service ID           : None
 *
 * Description          : Loads the freeze frame data in the event memory
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EvData
 *
 * InOut parameter      : entry
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *****************************************************************************/
#if (DEM_SIZE_OF_FREEZEFRAME > 0u)
static FUNC(boolean, DEM_CODE)
Dem_StoreUdsFFClass(
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPtrType MemEntry)
{
  boolean dirty = DEM_FALSE;

  if (
   (NULL_PTR != MemEntry) && 
   (NULL_PTR != EvData)  &&
   /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */	  
   (EvData->FFClassPos < Dem_Num_Of_FreezeFrameClass) && 
   (EvData->FFRecordNumPos < Dem_Max_ListOfFFRecordNumbers))
  {
    P2CONST(Dem_FreezeFrameClassType, AUTOMATIC, DEM_VAR) ffDataClass = &Dem_FreezeFrameClass[EvData->FFClassPos];
    P2VAR(uint8, AUTOMATIC, DEM_VAR) dst = NULL_PTR; 
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */    
    uint32 bufSize = ffDataClass->size;
    
    dst = Dem_EvMem_GetFFBufferForWriting(EvData->MaxNumOfFreezeFrameRecords, MemEntry, &bufSize);
    if (NULL_PTR != dst)
    {
      #if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
      P2VAR(uint8, AUTOMATIC, DEM_VAR) src = NULL_PTR;          
      /* Prestored freeze frame data */
      if(DEM_TRUE == EvData->FFPreStorageSupported)
      {
        /*
         * SWS_Dem_00464: If a pre-stored freeze frame  is available, the  Dem  module shall
         * use the data of the pre-stored freeze  frame instead of the current  data  at the point in
         * time when  the  event  related  date  is  captured  (refer  to  SWS_Dem_00461  ) and
         * SWS_Dem_00190.
         */
        src = Dem_GetBufferOfPrestoredFF(EvData->EventIdRef, NULL_PTR);
      }
      /* found prestored freeze frame in the buffer. */
      if (NULL_PTR != src)
      {
        Dem_SizeOfFreezeFrameClassType idx;
        for (idx = 0; idx < ffDataClass->size; idx++)
        {      
          /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations  a defect> Rule violation */
          if ( (DEM_FALSE == dirty) && (dst[idx] != src[idx]) )
          {
            dirty = DEM_TRUE;
          } 
          /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations  a defect> Rule violation */
          dst[idx] = src[idx];
        }            
      }
      else
      #endif
      {
	    /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */  
        dirty |= Dem_CaptureFFClass(ffDataClass, dst, bufSize);
      }
    }
    else
    {
      /* Det Error */
    }
  }
  
  return dirty;
}
#endif


/******************************************************************************
 * Function Name        : Dem_StoreJ1939FFClass == 1
 *
 * Service ID           : None
 *
 * Description          : Loads the j1939 freeze frame data in the event memory
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EvData
 *
 * InOut parameter      : entry
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *****************************************************************************/
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_SIZE_OF_J1939FREEZEFRAME > 0U))
FUNC(boolean, DEM_CODE)
Dem_StoreJ1939FFClass(
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPtrType MemEntry)
{
  boolean dirty = DEM_FALSE;

  if ((NULL_PTR != MemEntry) && (EvData->J1939FFClassPos < Dem_Num_Of_J1939FreezeFrameClass))
  {
    uint32 bufSize = 0U;    
    P2CONST(Dem_J1939FreezeFrameClassType, AUTOMATIC, DEM_CONST) j1939FFDataClass = &Dem_J1939FreezeFrameClass[EvData->J1939FFClassPos];      
    /* Gets ptr of buffer to save the event data(FF+EXT) of an event */
    P2VAR(uint8, AUTOMATIC, DEM_VAR) dst = Dem_EvMem_GetJ1939FFBuffer(EvData, MemEntry, &bufSize, 0);
    
    dirty = Dem_CaptureJ1939FFClass(j1939FFDataClass, dst, bufSize);
  }  

  return dirty;
}
#endif

/******************************************************************************
 * Function Name        : Dem_StoreJ1939EXFFClass == 1
 *
 * Service ID           : None
 *
 * Description          : Loads the j1939 expanded freeze frame data in the event memory
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EvData
 *
 * InOut parameter      : entry
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *****************************************************************************/
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_SIZE_OF_J1939EXPANDEDFREEZEFRAME > 0U))
FUNC(boolean, DEM_CODE)
Dem_StoreJ1939EXFFClass(
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPtrType MemEntry)
{
  boolean dirty = DEM_FALSE;

  if ((NULL_PTR != MemEntry) && (EvData->J1939EXFFClassPos < Dem_Num_Of_J1939FreezeFrameClass))
  {
    uint32 bufSize = 0U;    
    P2CONST(Dem_J1939FreezeFrameClassType, AUTOMATIC, DEM_CONST) j1939ExFFDataClass = &Dem_J1939FreezeFrameClass[EvData->J1939EXFFClassPos];      
    /* Gets ptr of buffer to save the event data(FF+EXT) of an event */
    P2VAR(uint8, AUTOMATIC, DEM_VAR) dst = Dem_EvMem_GetJ1939FFBuffer(EvData, MemEntry, &bufSize, 1);
    
    dirty = Dem_CaptureJ1939FFClass(j1939ExFFDataClass, dst, bufSize);
  }  

  return dirty;
}
#endif


/******************************************************************************
 * Function Name        : Dem_StoreObdFFClass
 *
 * Service ID           : None
 *
 * Description          : This function is used to get the extended data
 *                        or freeze frame data internally from Dem or from
 *                        some external function
 *
 * Sync/Async           : Synchronous/Asynchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : LusEventParameterIndex
 *                        LucIndex
 *                        LucDataElementtype
 *                        LucSize
 *
 * InOut parameter      : None
 *
 * Output Parameters    : LpData
 *
 * Return parameter     : StdReturnType
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_GaaDataElementExternalCS
 *                        Dem_GaaDataElementInternal
 *
 *                        Function(s) invoked :
 *                        None
 ******************************************************************************/
#if((DEM_OBD2_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_OF_PID_RECDS > 0U))
FUNC(boolean, DEM_CODE)
Dem_StoreObdFFClass(
    Dem_EventRelatedDataCPCType EvData,
    Dem_EventMemoryEntryPtrType entry)
    {
  Std_ReturnType result = E_NOT_OK;
  boolean found = DEM_FALSE;
  boolean dirty = DEM_FALSE;
  Dem_NumOfRecordNumberType RecordIndex = 0u;

  P2VAR(uint8, AUTOMATIC, DEM_VAR) src = NULL_PTR;
  P2VAR(uint8, AUTOMATIC, DEM_VAR) dst = NULL_PTR;
  P2VAR(uint8, AUTOMATIC, DEM_VAR) base = NULL_PTR;

  /* Get buffer of event memory for a specific event */
  base = Dem_EvMem_GetEventDataBuffer(entry);

  /* Get buffer of event memory entry */
  DEM_GET_BUFFER_OF_OBD_FREEZEFRAME(EvData,EvData->MaxNumOfFreezeFrameRecords,base, dst);

  #if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
  /* Prestored freeze frame data */
  if(DEM_TRUE == EvData->FFPreStorageSupported)
  {
    /*
     * SWS_Dem_00464: If a pre-stored freeze frame  is available, the  Dem  module shall
     * use the data of the pre-stored freeze  frame instead of the current  data  at the point in
     * time when  the  event  related  date  is  captured  (refer  to  SWS_Dem_00461  ) and
     * SWS_Dem_00190.
     */
    src = Dem_GetBufferOfPrestoredFF(EvData->EventIdRef, NULL_PTR);
  }
  /* Found prestored freeze frame in the buffer. */
  if (NULL_PTR != src)
  {  
    if (EvData->FFClassPos < Dem_Num_Of_FreezeFrameClass)
    {    
      src += Dem_FreezeFrameClass[EvData->FFClassPos].size;
    }
    else
    {
      /* Do thing */
    }
  }
  else
  #endif
  {
    if (NULL_PTR != EvData->CallbackEventDataChanged)
    {
      /* Use temporary buffer to check the difference between Old and New data. */
      src = Dem_EvOBDFFDataCapture;
    }
    else
    {
      src = dst;
    }
    Dem_CaptureOBDFFClass(EvData->OBDClassPos, src);
  }

  if (src != dst)
  {
    Dem_NumOfPidDataElementType DataIndex = 0U;
    Dem_NumOfPidClassType i = 0U;
    const Dem_NumOfPidClassType NumOfPid = EvData->OBDClassPos->NumOfPidClass;

    CONSTP2CONST(Dem_PidClassType, AUTOMATIC, DEM_CONST) PID = EvData->OBDClassPos->PidClass;

    for(i = 0; i < NumOfPid; i++)
    {
      Dem_NumOfPidDataElementType j = 0U;
      const Dem_NumOfPidDataElementType NumOfPidData = PID[i].NumOfPidDataElements;

      for(j = 0; j < NumOfPidData; j++)
      {
        uint8 size = PID[i].PidDataElement[j].size;

        Dem_SizeOfFreezeFrameClassType idx;
        for (idx = 0; idx < size; idx++)
        {      
          if (DEM_FALSE == dirty)
          {
            if ( dst[idx] != src[idx] )
            {
              dirty = DEM_TRUE;
            }
          }      
          dst[idx] = src[idx];
        }

        dst += size;
        src += size;
      }
    }
  }
  else
  {
    /* FF is already stored in the FFBuffer */
  }

  return dirty;
}


#endif



/*******************************************************************************
 ** Function Name       : Dem_GetReadDataOfPID                                **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Provision to give the pid data                      **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : entry, ReportTotalPid, PidIdentifier                **
 **                       ReportTotalDataElement, DataElementIndexOfPID       **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : DestBuffer                                          **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s):  None                           **
 **                                                                           **
 **                       Function(s) invoked: None                           **
 *******************************************************************************/
#if (DEM_OBD2_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetReadDataOfPID(
    Dem_EventMemoryEntryCPCType entry,
    P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
    const boolean ReportTotalPid,
    const Dem_PidIdentifierType PidIdentifier,
    const boolean ReportTotalDataElement,
    const Dem_NumOfDataElementClassType DataElementIndexOfPID)
{
  Std_ReturnType retVal = E_NOT_OK;

  Dem_EventIdType eventId = DEM_NO_EVENT;
  Dem_NumOfPidClassType IndexOfPid = 0U;
  Dem_NumOfPidClassType NumOfPid = 0U;
  Dem_NumOfPidDataElementType IndexOfAllDataElement = 0U;

  P2VAR(Dem_EventRelatedDataType, AUTOMATIC, DEM_VAR) EvData = NULL_PTR;

  P2VAR(Dem_PidClassType, AUTOMATIC, DEM_VAR) PID = NULL_PTR;
  Dem_EventParameterPtrType event = NULL_PTR;
  Dem_EventParameterPCType event = NULL_PTR;

  P2CONST(uint8, AUTOMATIC, DEM_VAR) base = NULL_PTR;
  P2CONST(uint8, AUTOMATIC, DEM_VAR) src = NULL_PTR;
  P2VAR(uint8, AUTOMATIC, DEM_VAR) dst = DestBuffer;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  if ((DEM_TRUE == ReportTotalPid) && (DEM_FALSE == ReportTotalDataElement))
  {
    /* wrong usage */
    DEM_REPORT_ERROR(DEM_UNSPECIFIED_SID, DEM_E_WRONG_CONDITION);
    return E_NOT_OK;
  }
  #endif

  eventId = Dem_EvMem_GetEventIdByEvMemEntry(entry);
  if (DEM_FALSE == Dem_EventIdIsValid(eventId))
  {
    return E_NOT_OK;
  }
  event = &Dem_Event[eventId-1U];
  if (DEM_NO_EVENT_DATA == event->e_PointToData)
  {
    return E_NOT_OK;
  }
  if (NULL_PTR == EvData->OBDClassPos)
  {
    return E_NOT_OK;
  }
  PID = EvData->OBDClassPos->PidClass;
  NumOfPid = EvData->OBDClassPos->NumOfPidClass;

  /* Get buffer of event memory for a specific event */
  base = Dem_EvMem_GetEventDataBuffer(entry);
  /* Get buffer of event memory entry */
  DEM_GET_BUFFER_OF_OBD_FREEZEFRAME(EvData, EvData->MaxNumOfFreezeFrameRecords,
      base, src);

  IndexOfAllDataElement = 0U;

  for(IndexOfPid = 0; IndexOfPid < NumOfPid; IndexOfPid++)
  {
    const Dem_NumOfPidDataElementType
    NumOfDataElement = PID[IndexOfPid].NumOfPidDataElements;

    if ((DEM_TRUE == ReportTotalPid) ||
        (PidIdentifier == PID[IndexOfPid].PidIdentifier))
    {
      Dem_NumOfPidDataElementType pids;

      for(pids = 0;
          pids < NumOfDataElement;
          pids++)
      {

        CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
            ListOfDataElementPtr = PID[IndexOfPid].PidDataElement;

        if ((DEM_TRUE == ReportTotalDataElement) ||
            (DataElementIndexOfPID == pids))
        {
          Dem_SizeOfDataElementClassType i;
          Dem_SizeOfDataElementClassType size = ListOfDataElementPtr[pids].size;
          
          src = size * DataElementIndexOfPID;
          for (i = 0; i < size; i++)
          {
            dst[i] = src[i];
          }
          
          dst += ListOfDataElementPtr[pids].size;

          if (DEM_FALSE == ReportTotalDataElement)
          {
            break; /* Exit loop */
          }
        }
        /* increase index of PIDData for next pid data element */
        src += ListOfDataElementPtr[pids].size;
      }

      if (DEM_FALSE == ReportTotalPid)
      {
        break; /* Exit loop */
      }
    }
    else
    {
      src += PID[IndexOfPid].size;
    }
  }

  if (dst != DestBuffer)
  {
    retVal = E_OK;
  }

  return retVal;
}
#endif



/******************************************************************************
 * Function Name        : Dem_GetSizeOfFreezeFrameData
 *
 * Service ID           : None
 *
 * Description          : The API shall be used to get the size of freeze frame
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EvData, type
 *
 * InOut parameter      : None
 *
 * Output Parameters    : BufSize
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *                        Dem_DidClass
 *
 *                        Function(s) invoked :
 *
 *****************************************************************************/
#if (DEM_SIZE_OF_FREEZEFRAME > 0u)
static FUNC(Dem_SizeOfFreezeFrameClassType, DEM_CODE)
Dem_GetSizeOfFreezeFrameData(
  Dem_FreezeFrameClassPCType FFClass,
  const Dem_FFBufferFormatType FFBufferType)
{
  Dem_SizeOfFreezeFrameClassType bufSize = 0U;

  /* variable range for calculation
   * ffDataClass->size : 0 ~ 65535 
   * ffDataClass->NumOfDidClass : 0 ~ 255  
   * sizeof(Dem_DataIdentifierType) : 2
   * ffDataClass->NumOfDidClass * sizeof(Dem_DataIdentifierType) : 0~500 <- need casting
   * sizeof(Dem_NumOfDidClassType) : 1
   */
  /* |NumofDIDs|1st DID|Data#1|*/
  if (DEM_FFFORMAT_TYPE_HDR_DID == FFBufferType)
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */  
  {
    bufSize = 
      FFClass->size + 
      ((Dem_SizeOfFreezeFrameClassType)FFClass->NumOfDidClass * (Dem_SizeOfFreezeFrameClassType)sizeof(Dem_DataIdentifierType)) +
      (Dem_SizeOfFreezeFrameClassType)sizeof(Dem_NumOfDidClassType);
  }
  /* |RecNum|NumofDIDs|1st DID|Data#1|*/
  else if (DEM_FFFORMAT_TYPE_HDR_REC == FFBufferType)
  {
    /* polyspace +2 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    bufSize =  
      FFClass->size + 
      ((Dem_SizeOfFreezeFrameClassType)FFClass->NumOfDidClass * (Dem_SizeOfFreezeFrameClassType)sizeof(Dem_DataIdentifierType)) +
      (Dem_SizeOfFreezeFrameClassType)sizeof(Dem_NumOfDidClassType) + 
      (Dem_SizeOfFreezeFrameClassType)sizeof(Dem_RecordNumberType);
  }
  /* else if (DEM_FFFORMAT_TYPE_RAW == type) */
  else
  {
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
    bufSize = FFClass->size;
  }

  return bufSize;
}
#endif


/******************************************************************************
 * Function Name        : Dem_GetSizeOfExtendedData
 *
 * Service ID           : None
 *
 * Description          : Gets the size of extended data
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EvData, ReportTotalRecord, ExtendedDataNumber
 *
 * InOut parameter      : None
 *
 * Output Parameters    : BufSize
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *
 *                        Function(s) invoked :
 *
 *****************************************************************************/
#if (DEM_SIZE_OF_EXTENDED_DATA > 0U)
FUNC(Dem_SizeOfExtendedDataClassType, DEM_CODE)
Dem_GetSizeOfExtendedData(
  Dem_ExtendedDataClassPCType EDClass,
  const Dem_ExtendedDataNumberType ExtendedDataNumber,
  P2VAR(Dem_NumOfExtendedDataRecordClassType, AUTOMATIC, DEM_VAR) NumOfMatchedEDR)
{
  Dem_SizeOfExtendedDataClassType bufSize = 0U;

  /* [1] All Extended Data Record Number */        
  if (DEM_MAX_EXTENDED_RECORD_NUMBER == ExtendedDataNumber)
  {
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
    bufSize = EDClass->size;
    if (NULL_PTR != NumOfMatchedEDR)
    {
      *NumOfMatchedEDR = EDClass->NumOfEDRecordClass;
    }
  } 
  #if (DEM_OBD_SUPPORT == STD_ON)    
  else if (DEM_EXTENDED_DATA_NUMBER_OBD == ExtendedDataNumber)
  {
    /* [SWS_Dem_00076]
     * Note: If the record number value 0xFE is requested, the Dem considers the size
     * of all OBD stored extended data records in the range of 0x90 to 0xEF */
    Dem_ExtendedDataNumberType from = (Dem_ExtendedDataNumberType)DEM_MIN_VALID_OBD_EXTENDED_RECORD_NUMBER;
    Dem_ExtendedDataNumberType to = (Dem_ExtendedDataNumberType)DEM_MAX_VALID_OBD_EXTENDED_RECORD_NUMBER;

    Dem_NumOfExtendedDataRecordClassType iEDR;      
    Dem_NumOfExtendedDataRecordClassType maxEDR;              
    
    maxEDR = EDClass->PointToEDRecordMap + EDClass->NumOfEDRecordClass;
    if (maxEDR <= Dem_Max_ListOfEDRecordClassIndex)
    {       
      for(iEDR = EDClass->PointToEDRecordMap; iEDR < maxEDR; iEDR++)
      {
        CONSTP2CONST(Dem_ExtendedDataRecordClassType, AUTOMATIC, DEM_CONST)
          EDRecord = &Dem_ExtendedDataRecordClass[Dem_ListOfEDRecordClassIndex[iEDR]];      
    
        if  ((EDRecord->ExtendedDataRecordNumber >= from ) &&
            (EDRecord->ExtendedDataRecordNumber <= to ))
        {
          bufSize += EDRecord->size;
          if (NULL_PTR != NumOfMatchedEDR)
          {
            *NumOfMatchedEDR += 1U;
          }           
        }   
      }
    }
  }
  #endif
  /* [2] A specific Extended Data Record Number */
  else
  {     
    Dem_NumOfExtendedDataRecordClassType iEDR;      
    Dem_NumOfExtendedDataRecordClassType maxEDR;              
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    maxEDR = EDClass->PointToEDRecordMap + EDClass->NumOfEDRecordClass;
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates to true or false according to configuration */
    if (maxEDR <= Dem_Max_ListOfEDRecordClassIndex)
    {       
      for(iEDR = EDClass->PointToEDRecordMap; iEDR < maxEDR; iEDR++)
      {
        CONSTP2CONST(Dem_ExtendedDataRecordClassType, AUTOMATIC, DEM_CONST)
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
   	    EDRecord = &Dem_ExtendedDataRecordClass[Dem_ListOfEDRecordClassIndex[iEDR]];      
        /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */    
        if (EDRecord->ExtendedDataRecordNumber == ExtendedDataNumber)
        {            
          bufSize = EDRecord->size; 
          if (NULL_PTR != NumOfMatchedEDR)
          {
            *NumOfMatchedEDR = 1U;
          }          
          break;
        }      
      }
    }
  }
  
  return bufSize;
}
#endif

/******************************************************************************
 * Function Name        : Dem_StoreEventRelatedData
 *
 * Service ID           : None
 *
 * Description          : Store the event related data in the event memory
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EvMemEntry
 *
 * InOut parameter      : None
 *
 * Output Parameters    : EvData
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *
 *                        Function(s) invoked :
 *
 *****************************************************************************/
#if (DEM_SIZE_OF_EVENT_DATA > 0U)
FUNC(boolean, DEM_CODE)
Dem_StoreEventRelatedData(
 P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_CONST) EvData,
 Dem_EventMemoryEntryPtrType EvMemEntry)
{
  boolean dirty = DEM_FALSE;

  /* Freeze Frame Data */
  #if (DEM_SIZE_OF_FREEZEFRAME > 0u)
  dirty = Dem_StoreUdsFFClass(EvData, EvMemEntry);
  #endif    
  /* Extended Data  */
  #if (DEM_SIZE_OF_EXTENDED_DATA > 0u)
  /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */
  dirty |= Dem_StoreUdsEDClass(EvData, EvMemEntry);
  #endif    
  /* OBD Freeze Frame Data */
  #if ((DEM_OBD2_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_OF_PID_RECDS > 0U))
  dirty |= Dem_StoreObdFFClass(EvData, EvMemEntry);
  #endif
  /* J1939 Freeze Frame Data */
  #if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_SIZE_OF_J1939FREEZEFRAME > 0U))
  dirty |= Dem_StoreJ1939FFClass(EvData, EvMemEntry);
  #endif
  #if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_SIZE_OF_J1939EXPANDEDFREEZEFRAME > 0U))
  dirty |= Dem_StoreJ1939EXFFClass(EvData, EvMemEntry);
  #endif
  

  /* This callback should be called only when the event has the event related data. */
  if (DEM_TRUE == dirty) 
  {    
    if (NULL_PTR != EvData->CallbackEventDataChanged)
    {
      /* polyspace<RTE:COR:Not a defect:No action planned> Polyspace bug */      
      (void)EvData->CallbackEventDataChanged();
    }           
    /* #if (DEM_GENERAL_INTERFACE_SUPPORT == STD_ON) */
    (void)Rte_Call_GeneralCBDataEvt_EventDataChanged(EvData->EventIdRef);
    /* #endif */
  }

  /* Clear prestored freeze frame buffer */
  #if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
  (void)Dem_ClearSinglePrestoredFFbyEventId(EvData->EventIdRef);
  #endif 

  return dirty;
}
#endif

/******************************************************************************
 * Function Name        : Dem_GetSizeOfOBDFreezeFrameData
 *
 * Service ID           : None
 *
 * Description          : Gets the size of OBD Freeze Frame data
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event, ReportTotalRecord, PidIdentifier
 *
 * InOut parameter      : None
 *
 * Output Parameters    : BufSize
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *
 *                        Function(s) invoked :
 *
 *****************************************************************************/
#if (DEM_OBD2_SUPPORT == STD_ON)
#if (DEM_MAX_NUMBER_OF_PID_DATAELEMENT > 0U)
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfOBDFreezeFrameData(
    Dem_EventParameterCPCType event,
    const boolean ReportTotalRecord,
    const Dem_PidIdentifierType PidIdentifier,
    P2VAR(Dem_SizeOfOBDFreezeFrameDataType, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Std_ReturnType retVal = E_NOT_OK;

   P2VAR(Dem_EventRelatedDataType, AUTOMATIC, DEM_VAR) EvData = NULL_PTR;
  *BufSize = 0;



  if (NULL_PTR == EvData->OBDClassPos)
  {
    /* No OBD freeze frame configured of event. */
     retVal = E_NOT_OK;
  }
  else if (DEM_TRUE == ReportTotalRecord)
  {
    *BufSize =  EvData->OBDClassPos->size;
    retVal = E_OK;
  }
  else
  {
    Dem_NumOfPidClassType i = 0U;
    const Dem_NumOfPidClassType num = EvData->OBDClassPos->NumOfPidClass;
    P2VAR(Dem_PidClassType, AUTOMATIC, DEM_VAR) PID = EvData->OBDClassPos->PidClass;

    for(i = 0; i < num; i++)
    {
      if (PidIdentifier == PID[i].PidIdentifier)
      {
        *BufSize = PID[i].size;
        retVal = E_OK;
      }
    }
  }

  return retVal;
}

#endif
#endif

/******************************************************************************
 * Function Name        : Dem_GetSizeOfJ1939FreezeFrameData
 *
 * Service ID           : None
 *
 * Description          : Gets the size of extended data
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : event, j1939FFType
 *
 * InOut parameter      : None
 *
 * Output Parameters    : BufSize
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *
 *                        Function(s) invoked :
 *
 *****************************************************************************/
#if (DEM_J1939_SUPPORT == STD_ON)  
#if (DEM_NUM_OF_J1939FREEZEFRAMECLASS > 0U)
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfJ1939FreezeFrameData(
    Dem_EventParameterCPCType event,
    P2VAR(Dem_SizeOfJ1939FreezeFrameDataType, AUTOMATIC, DEM_APPL_DATA) BufSize, 
    Dem_J1939DcmSetFreezeFrameFilterType j1939FFType)
{
  Std_ReturnType retVal = E_NOT_OK;

   P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_VAR) EvData;
   P2CONST(Dem_J1939FreezeFrameClassType, AUTOMATIC, DEM_VAR) J1939FFClass = NULL_PTR;
   Dem_NumOfJ1939FreezeFrameClassType ffClassPos;
  *BufSize = 0;
   EvData = &Dem_EventRelatedData[event->e_PointToData];
   
  if(j1939FFType == DEM_J1939DCM_EXPANDED_FREEZEFRAME)
  {
    ffClassPos = EvData->J1939EXFFClassPos;
  }
  else 
  {
    ffClassPos = EvData->J1939FFClassPos;
  }
  
  if (DEM_NO_IDX_U16 == ffClassPos)
  {
    /* No J1939 freeze frame configured of event. */
     retVal = E_NOT_OK;
  }
  else
  {
    J1939FFClass = &Dem_J1939FreezeFrameClass[ffClassPos];
    *BufSize =  J1939FFClass->size;
    retVal = E_OK;
  }


  return retVal;
}
#endif
#endif

/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace:end<MISRA-C:1.1:Not a defect:No action planned> Not defect  */

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"


/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */ 
/* polyspace-end DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

