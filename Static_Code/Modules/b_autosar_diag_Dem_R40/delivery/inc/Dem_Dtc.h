/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem
_Dtc.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_Dtc.c                                        **
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
** 1.2.2    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.2.1    31-01-2019    EunKyung.Kim    Changes made As per Redmine #14481  **
**                                                                            **
** 1.2.0    31-08-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.1.1    15-02-2017      YoungJin.Yun  Changes made As per Redmine #7379   **
**                                                                            **
** 1.1.0    30-08-2016      YoungJin.Yun  Changes made As per Redmine #5011   **
**                                                                            **
** 1.0.1    16-04-2016      Youngjin Yun  Changes made As per Redmine #1164   **
**                                                                            **
** 1.0.0    06-11-2015      Autron        Initial Version                     ** 
*******************************************************************************/

#ifndef DEM_DTC_H
#define DEM_DTC_H

/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetConditionOfDTCRecordUpdate(
  const Dem_DTCType DTC,
  const Dem_DTCOriginType DTCOrigin);

extern FUNC(void, DEM_CODE) Dem_CountAndStoreFilterDtc(void);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCGroupId(
  Dem_DTCGroupType DTCGroup,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DTCGroupId);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_ClearSingleDTCStatusByte(
  Dem_CombinedDtcPCType CbDTC);

extern FUNC(Dem_UdsStatusByteType, DEM_CODE) Dem_GetDTCStatus(
/* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
  const Dem_EventIdType EventId);

extern FUNC(Dem_ReturnClearDTCType, DEM_CODE) Dem_InternalClearDTC(uint32 DTC,
  Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin);
  

/* polyspace:begin<MISRA-C:1.1:Not a defect:No action planned> inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:begin<MISRA-C:8.1:Not a defect:No action planned> inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:begin<MISRA-C:8.5:Not a defect:No action planned> inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.5 [Justified:Low] "Not a defect" */

static DEM_INLINE FUNC(Dem_CombinedDtcPCType, DEM_CODE) Dem_GetCbDTCByEventId(Dem_EventIdType EventId)
{
  Dem_CombinedDtcPCType cbDTC;

  #if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to false. */  
  if ((EventId > Dem_Number_Of_Events) || (DEM_NO_EVENT == EventId))
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always evaluates to false. */    
  {
    cbDTC = NULL_PTR;
  }  
  else
  #endif
  {
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
    uint16 pos = Dem_Event[EventId - 1U].e_PointToDTC;
    if (pos < Dem_Max_Number_Of_DTC) 
    {
      cbDTC = &Dem_GaaCombinedDtc[pos];
    }
    else
    {
      cbDTC = NULL_PTR;
    }
  }
  
  return cbDTC;
}


static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_DTCFormatIsValid(
  Dem_EventIdType EventId, 
  Dem_DTCFormatType DTCFormat)
{
  boolean valid = DEM_FALSE;
  /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
  Dem_CombinedDtcPCType cbDTC = Dem_GetCbDTCByEventId(EventId);
  if (NULL_PTR != cbDTC)
  { 
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
    if (cbDTC->ddDtcFormat == DTCFormat)
    {
      valid = DEM_TRUE;
    }
  }     
  return valid;
}

static DEM_INLINE  FUNC(Dem_CombinedDtcPCType , DEM_CODE) Dem_GetDtcByDtcId(
  const uint32 DTC)
{
  /* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */    
  P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) cbDTC = NULL_PTR;
  uint16 dtcLoc;
  uint32 dtcVal;  
  
  for (dtcLoc = 0U; dtcLoc < Dem_Max_Number_Of_DTC; dtcLoc++)
  {     
    #if(DEM_OBD_SUPPORT == STD_ON)    
    if(Dem_GaaCombinedDtc[dtcLoc].ddDtcFormat != DEM_DTC_FORMAT_UDS)
    {
       /* Making DTC lowByte to zero for OBD DTC */
      dtcVal = Dem_GaaCombinedDtc[dtcLoc].usObdDtc << 8U ;
    }
    else
    #endif
    {
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      dtcVal = Dem_GaaCombinedDtc[dtcLoc].ulUdsDtc;
    }
      
    if (dtcVal == DTC)
    {
      cbDTC = &Dem_GaaCombinedDtc[dtcLoc];      
    }
  }
  
  return cbDTC;
}

static DEM_INLINE FUNC(Dem_NumOfEventIdType, DEM_CODE) Dem_GetStartEventIdMapOfCbDTC(Dem_CombinedDtcPCType CombinedDTC)
{
  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
  return CombinedDTC->dtc_PointToEventList;
}

static DEM_INLINE FUNC(Dem_EventIdType, DEM_CODE) Dem_GetEventIdByEventIdMapOfCbDTC(Dem_NumOfEventIdType EventIdMapIdx)
{
  return Dem_ListOfCombinedEvents[EventIdMapIdx];
}

static DEM_INLINE FUNC(Dem_NumOfEventIdType, DEM_CODE) Dem_GetEndEventIdMapOfCbDTC(Dem_CombinedDtcPCType CombinedDTC)
{
  Dem_NumOfEventIdType endPos = CombinedDTC->dtc_PointToEventList + CombinedDTC->ddNumberOfEvents;    
  if (endPos > Dem_Max_ListOfCombinedEvents)
  /* polyspace<RTE:UNR:Not a defect:No action planned> The block is only partially unreachable. */     
  {
    endPos = 0U;
  }
  return endPos;
}

static DEM_INLINE FUNC(Dem_DTCType, DEM_CODE) Dem_GetDtcByCombineDTC(
  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
  P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_CONST) cbDTC)
{
  Dem_DTCType DTC;
  #if(DEM_OBD_SUPPORT == STD_ON)
  if (cbDTC->ddDtcFormat != DEM_DTC_FORMAT_UDS)
  {
     /* Making DTC lowByte to zero for OBD DTC */
     /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
     DTC = (uint32)cbDTC->usObdDtc << 8U ;
  }
  else
  #endif
  {
    /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */  
    DTC = cbDTC->ulUdsDtc;
  }

  return DTC;
}

/* polyspace +4 MISRA-C3:2.7 [Justified:Low] "Not a defect" */
static DEM_INLINE FUNC(Dem_DTCType, DEM_CODE) Dem_GetDTCValue(
/* polyspace +1 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
  const Dem_EventIdType EventId,
  const Dem_DTCFormatType DTCFormat)
{
  Dem_DTCType DTC = DEM_NO_DTC;

  uint16 dtcLoc = Dem_Event[EventId - 1U].e_PointToDTC;
  if (dtcLoc < Dem_Max_Number_Of_DTC) 
  {
    #if(DEM_OBD_SUPPORT == STD_ON)
    if (DTCFormat == DEM_DTC_FORMAT_OBD)
    {
       /* Making DTC lowByte to zero for OBD DTC */
      DTC = (uint32)Dem_GaaCombinedDtc[dtcLoc].usObdDtc;
    }
    else
    #endif
    #if (DEM_J1939_SUPPORT == STD_ON)    
    if (DTCFormat == DEM_DTC_FORMAT_J1939)
    {
      DTC = Dem_GaaCombinedDtc[dtcLoc].J1939DTCValue;
    }
    else
    #endif    
    /* DEM_DTC_FORMAT_UDS */
    {
      DTC = Dem_GaaCombinedDtc[dtcLoc].ulUdsDtc;
    }
  }

  return DTC;
}

/* polyspace-end MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
/* polyspace:end<MISRA-C:8.5:Not a defect:No action planned> inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:end<MISRA-C:8.1:Not a defect:No action planned> inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:end<MISRA-C:1.1:Not a defect:No action planned> inline-MISRA C:2012 permits the use of inline functions in header files */

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DEM_DTC_H */

/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/


