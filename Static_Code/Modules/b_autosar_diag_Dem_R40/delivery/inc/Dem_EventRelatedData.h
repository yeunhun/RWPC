/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_EventRelatedData.h                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_EventRelatedData.c                            **
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
** 1.1.2    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.1.0    10-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.0.0    07-02-2015      YoungJin.Yun  Initial Version                     **
*******************************************************************************/


#ifndef DEM_EVENTRELATEDDATA_H
#define DEM_EVENTRELATEDDATA_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_PCTypes.h"
#include "Dem_Config.h"

#define DEM_START_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
**                Extern function definition                                  **
*******************************************************************************/

#if (DEM_SIZE_OF_FREEZEFRAME > 0U)    
extern FUNC(Std_ReturnType, DEM_CODE) 
Dem_GetSizeOfFreezeFrameByRecord(
  /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */	
  Dem_EventIdType EventId,
  Dem_RecordNumberType RecordNumber,
  Dem_DTCOriginType DTCOrigin,   /* DTCOrigin is verified by caller */
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) SizeOfFreezeFrame);

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
extern FUNC(boolean, DEM_CODE)
Dem_CaptureFFClass(
  Dem_FreezeFrameClassCPCType FFDataClass,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) OutBuffer,
  uint32 BufSize);
#endif

#endif

#if (DEM_SIZE_OF_EVENT_DATA > 0U)
extern FUNC(boolean, DEM_CODE)
Dem_StoreEventRelatedData(
 P2CONST(Dem_EventRelatedDataType, AUTOMATIC, DEM_CONST) EvData,
 Dem_EventMemoryEntryPtrType EvMemEntry);
#endif


#if (DEM_OBD_SUPPORT == STD_ON)
#if (DEM_SIZE_OF_OBD_FF > 0u)
extern FUNC(boolean, DEM_CODE)
Dem_StoreObdFFClass(
  Dem_EventRelatedDataCPCType EvData,
  Dem_EventMemoryEntryPtrType entry);
#endif
#endif


extern FUNC(Std_ReturnType, DEM_CODE) 
Dem_ReadDataOfExtendedData(
  Dem_EventRelatedDataPCType EvData,
  Dem_DTCOriginType DTCOrigin,
  Dem_ExtendedDataNumberType  ExtendedDataNumber,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize);



extern FUNC(Dem_ReturnReadEventDataType, DEM_CODE)
Dem_ReadDataOfFreezeFrame(
  Dem_EventRelatedDataPCType EvData,   
  Dem_DTCOriginType DTCOrigin,
  Dem_RecordNumberType RecordNumber,
  boolean ReportTotalDid,
  Dem_DataIdentifierType DataIdentifier,
  Dem_FFBufferFormatType HeaderType,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_VAR) BufSize);


extern FUNC(Dem_SizeOfExtendedDataClassType, DEM_CODE)
Dem_GetSizeOfExtendedData(
  Dem_ExtendedDataClassPCType EDClass,
  const Dem_ExtendedDataNumberType ExtendedDataNumber,
  P2VAR(Dem_NumOfExtendedDataRecordClassType, AUTOMATIC, DEM_VAR) NumOfMatchedEDR);


#if (DEM_J1939_SUPPORT == STD_ON)  
#if (DEM_SIZE_OF_J1939FREEZEFRAME > 0U) 
extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfJ1939FreezeFrameData(
    Dem_EventParameterCPCType event,
    P2VAR(Dem_SizeOfJ1939FreezeFrameDataType, AUTOMATIC, DEM_APPL_DATA) BufSize,
    Dem_J1939DcmSetFreezeFrameFilterType j1939FFType);

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetJ1939FreezeFrameData(
    Dem_EventParameterCPCType event,
    Dem_DTCOriginType DTCOrigin,
    P2VAR (uint8, AUTOMATIC, DEM_VAR) DestBuffer,
    P2VAR (uint16, AUTOMATIC, DEM_VAR) BufSize,
    Dem_J1939DcmSetFreezeFrameFilterType j1939FFType);
#endif
#endif
  
/**************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*************************************************/


#endif

