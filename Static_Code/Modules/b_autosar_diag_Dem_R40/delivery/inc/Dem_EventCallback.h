/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_EventCallback.h                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_EventCallback.c                              **
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
** 1.0.1    04-09-2020   EunKyung.Kim   Changes made As per Redmine #25254    **
**                                                                            **
** 1.0.0    07-02-2015      YoungJin.Yun  Initial Version                     **
*******************************************************************************/


#ifndef DEM_EVENTCALLBACK_H
#define DEM_EVENTCALLBACK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_PCTypes.h"

#define DEM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, DEM_CODE)
Dem_TriggerCallbackOnUdsStatus(
/* polyspace +3 MISRA-C3:D4.5 [Justified:Low] "Not a defect" */
  const Dem_EventIdType EventId,
  const Dem_UdsStatusByteType EventStatusByteOld,
  const Dem_UdsStatusByteType DTCStatusOld);

/**************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Follow Autosar Spec" */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*************************************************/
#endif

