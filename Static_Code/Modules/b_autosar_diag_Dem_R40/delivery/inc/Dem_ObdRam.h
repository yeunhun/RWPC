/*******************************************************************************
**  (C) 2014 Hyundai Autron Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dem_ObdRam.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Header file for Dem_ObdRam.c                                  **
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
** 1.1.1    04-09-2020    EunKyung.Kim   Changes made As per Redmine #25254   **
**                                                                            **
** 1.1.0    10-12-2018    EunKyung.Kim    Changes made As per Redmine #8561   **
**                                                                            **
** 1.0.0    18-11-2016      Autron      Initial Version                       **
*******************************************************************************/


#ifndef DEM_OBDRAM_H
#define DEM_OBDRAM_H
 
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"        /* Dem module header file */
#include "NvM.h"        /* NVRAM manager symbols Header File */

#if (DEM_OBD_SUPPORT == STD_ON)

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/


/*************************************************************************
 * VAR INIT_UNSPECIFIED
 ************************************************************************/
#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

/*************************************************************************
 * NO_INIT_UNSPECIFIED == SAVED_ZONE
 ************************************************************************/
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U)
/* Permanent Event Memory variable */
extern VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT) Dem_PermanentEventMemory[];
extern VAR(Dem_PerDtcStateType, DEM_VAR_NOINIT) Dem_PerDtcState[];
#endif

#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"


/*************************************************************************
 * VAR CLEARED_32
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* Used to Store the Mil on time */
extern VAR(uint32, DEM_VAR) Dem_GulTimeSinceMilOn;
/* Used to calculate time in milli sec */
extern VAR(uint32, DEM_VAR) Dem_GulDemTimeObdmsCount;
/* Used to Store whether event is disabled or not for pid41e */
extern VAR(uint32, DEM_VAR) Dem_GulEventIdDisabled;
/* Used to Store time since clear dtc is called count in min */
extern VAR(uint32, DEM_VAR) Dem_GulDemClearTimeCount;

#define DEM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

/*************************************************************************
 * CLEARED_16
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* Store the value of General Denominator*/
extern VAR(uint16, DEM_VAR) Dem_GusGeneralDenominator;
/* Store the value of ignition counter */
extern VAR(uint16, DEM_VAR) Dem_GusIgnitionCylCnt;
/* Global variable is used for store the first obd dtc  */
extern VAR(uint16, DEM_VAR) Dem_GusObdDtcFirstStored;
/* Pointer point the memory location in which Obd event is stored */
extern VAR(uint16, DEM_VAR) Dem_GusEventstoredinPermanent;
/* Store the value of General Denominator*/
extern VAR(uint16, DEM_VAR) Dem_GaaIumprDenominator[];
/* Store the value of General Denominator*/
extern VAR(uint16, DEM_VAR) Dem_GaaIumprNumerator[];
/* Used to Store the warm up cycle count */
extern VAR(uint16, DEM_VAR) Dem_GusWarmUpCycleCount;

#define DEM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/*************************************************************************
 * CLEARED_8
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Used to calculate Mil status of pid01 */
extern VAR(uint8, DEM_VAR) Dem_GucMilonFlag;
/* Used to calculate Warm up cycle count when Mil status is off */
extern VAR(uint8, DEM_VAR) Dem_GucWarmUpCycleCountMil;
/* Used to calculate Warm up cycle count when DTC is cleared */
extern VAR(uint8, DEM_VAR) Dem_GucWarmUpCycleCountDtcClear;

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > 0U)
/* Permanent Event Memory variable */
extern VAR(uint8, DEM_VAR) Dem_PermanentEventMemoryState[];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

/*****************************************************************************/
/* VAR CLEARED BOOLEAN                                                       */
/*****************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Current operation cycle Id Value */
extern VAR(boolean, DEM_VAR) Dem_ObdEventStored;
/* Used to calculate Mil status of pid01 */
extern VAR(boolean, DEM_VAR) Dem_GblMilStarted;
/* Used to calculate Clear Dtc time */
extern VAR(boolean, DEM_VAR) Dem_GblDtcCleared;
/* Used to Store the pto status */
extern VAR(boolean, DEM_VAR) Dem_GblPtoStatus;
/* Used to calculate time since clear dtc is called */
extern VAR(boolean, DEM_VAR) Dem_GblClearTimeStartObd;
#if (DEM_NUMBER_OF_RATIO_INFO > 0U)
/* Store the value of General Denominator*/
extern VAR(boolean, DEM_VAR) Dem_GblRatioInit;
extern VAR(boolean, DEM_VAR) Dem_GusRatioIdDisable[];
extern VAR(boolean, DEM_VAR) Dem_GusRatioFaultFound[];
extern VAR(boolean, DEM_VAR) Dem_GusRatioMonitored[];
extern VAR(boolean, DEM_VAR) Dem_GusRatioDenCondState[];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*************************************************************************
 * CONST
 ************************************************************************/
 
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  

/*****************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "Not a defect" */
/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */
#endif /* DEM_OBD_SUPPORT == STD_ON */
#endif /* DEM_OBDRAM_H */

/*******************************************************************************
**                       End of File                                          **
*******************************************************************************/

