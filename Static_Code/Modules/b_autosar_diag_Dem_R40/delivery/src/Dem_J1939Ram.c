/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_J1939Ram.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Declares the global variables for configurable values         **
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
** 1.3.1    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.3.0    10-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.2.0     16-11-2016   YJ.Yun      Changes made As per Redmine #6188       **
**                                                                            **
** 1.1.0     30-08-2016   YJ.Yun      Changes made As per Redmine #5011       **
**                                                                            **
** 1.0.0     08-06-2016   YJ.Yun      Initial Version                         **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dem.h" 
#include "Rte_Dem.h"
#if (DEM_J1939_SUPPORT == STD_ON)

/*******************************************************************************
**                      Global Data Types                                     **
******************************************************************************/

#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR) Dem_PriEvMemChronoOrder[DEM_MAX_NUMBER_EVENT_ENTRY_PRI];
VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR) Dem_PriEvMemChronoOrderNextLoc;

VAR(Dem_NumOfEventMemoryEntryType, DEM_VAR) Dem_J1939FirstDtcLoc;
#if (DEM_J1939_RATIO_SUPPORT == STD_ON)
VAR(uint8, DEM_VAR) Dem_J1939NextRatioIndex;
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#endif


