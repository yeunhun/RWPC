/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_Obd.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_Obd.c                                        **
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
** 3.3.3    19-10-2021    LanhLT       Changes made As per Redmine #31128     **
**                                                                            **
** 1.2.0    22-02-2021    EunKyung.Kim    Changes made As per Redmine #25380  **
**                                                                            **
** 1.1.0    10-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.0.0     06-11-2015    Autron      Initial Version                        **                      
*******************************************************************************/

#ifndef DEM_OBD_H
#define DEM_OBD_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_ObdRam.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"


#if(DEM_OBD_SUPPORT == STD_ON)

extern FUNC(void, DEM_CODE) Dem_InitOBD(void);
extern FUNC(void, DEM_CODE) Dem_MainFunctionOBD(void);



#ifdef DEM_MIL_INDICATORID
extern FUNC(void, DEM_CODE)
Dem_SetMalfuntionOnOff(void);
#endif

#if (DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO)
extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetReadDataOfPID(
  P2CONST(Dem_EventMemoryEntryType, AUTOMATIC, DEM_CONST)entry,
  P2VAR(uint8, AUTOMATIC, DEM_VAR)DestBuffer,
  boolean ReportTotalRecord,
  Dem_PidIdentifierType PidIdentifier,
  boolean ReportTotalDataElement,
  Dem_NumOfDataElementClassType DataElementIndexOfPID);
#endif

extern FUNC(void, DEM_CODE) Dem_CalcPIDValue(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PIDValue,
  uint8 LusByteValue, uint8 LucOBDReadinessGrp);

extern FUNC(void, DEM_CODE) Dem_CalcPID41_34(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41Value);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_ReadDataOfTimeEngineStart(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PIDValue);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetPIDDataOnRequest(
  P2CONST(Dem_EventMemoryEntryType, AUTOMATIC, DEM_APPL_CONST)LpEventMemory,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)DestBuffer,
  uint8 LucEventMemoryIndex, boolean ReportTotalRecord, uint16 DataIdentifier,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)LucTotalSizePid);

#if ((DEM_OBD2_SUPPORT == STD_ON) && (DEM_MAX_NUMBER_OF_PID_DATAELEMENT > 0U))
extern FUNC(Dem_ReturnGetFreezeFrameDataByRecordType, DEM_CODE)
Dem_DcmGetOBDFreezeFrameData(
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_VAR) DTC,
  P2VAR(uint8, AUTOMATIC, DEM_VAR)DestBuffer,
  P2VAR(uint8, AUTOMATIC, DEM_VAR)BufSize);

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfOBDFreezeFrameData(
    Dem_EventParameterCPCType event,
    const boolean ReportTotalRecord,
    const Dem_PidIdentifierType PidIdentifier,
    P2VAR(Dem_SizeOfOBDFreezeFrameDataType, AUTOMATIC, DEM_APPL_DATA) BufSize);
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U)
extern FUNC(Std_ReturnType, DEM_CODE)
Dem_SetPfcCycleSetPfcCycleQualified(void);

extern FUNC(Std_ReturnType, Dem_CODE) 
Dem_GetPfcCycleQualified(P2VAR(boolean, AUTOMATIC, DEM_VAR) pfcCycleisqualified);

#endif

#if(DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
extern FUNC(void, DEM_CODE) Dem_ProcessDen(uint8 LucOperationCycleId, Dem_EventIdType eventId);

extern FUNC(Std_ReturnType, DEM_CODE)Dem_ProcessIumpr(
    Dem_EventParameterCPCType event,
    Dem_UdsStatusByteType EventStatus);

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_OCStartInit(void);

#endif

extern FUNC(boolean, Dem_CODE) Dem_GetMalfuntionOnOff(void);

extern FUNC(Std_ReturnType, DEM_CODE)
    Dem_SetObdCycle(uint8 LucOperationCycleId);

extern FUNC(void, DEM_CODE) Dem_ClearObdInfomation(void);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID21( uint8* PID21value );
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID31( uint8* PID31value );
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID4D( uint8* PID4Dvalue );
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID4E( uint8* PID4Evalue );

#endif

#define DEM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DEM_INDICATOR_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/


