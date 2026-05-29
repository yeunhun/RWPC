/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.								      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_Version.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.12.0    29-Apr-2019   SM Kwon        #17202                              **
** 1.11.0    23-Oct-2018   Lim Jong Sun   #14496                              **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7076                               **
** 1.9.9     18-May-2016   Lim Jong Sun   #4975                               **
** 1.9.7     19-Jan-2015   Lim Jong Sun   #3905                               **
** 1.0.1     16-Apr-2014   Lim Jong Sun   Bug #872                            **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion of CanSM header */
#include "CanSM.h"

#include "CanSM_Error.h"

/* Version Information File */
#include "CanSM_Version.h"

/* Inclusion of ComM header file */
#include "ComM.h"

/* Inclusion of CanIf header file */
#include "CanIf.h"

/* Inclusion of Det header file */
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h"
#endif

/* #4975 */
#if (STD_ON == CANSM_DEM_STATUS)
#include "Dem.h"                  /* Dem header file */
#endif

/* Inclusion of SchM header file */
#include "SchM_CanSM.h"

/* Inclusion of BswM header file */
#include "BswM.h"

#if (STD_ON == CANSM_PN_AVAILABILITY)
/* Inclusion of CanNm header file */
#include "CanNm.h"
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_VERSION_C_AR_RELEASE_MAJOR_VERSION       4
#define CANSM_VERSION_C_AR_RELEASE_MINOR_VERSION       0
#define CANSM_VERSION_C_AR_RELEASE_REV_VERSION         3

/* CANSM software version information */
#define CANSM_VERSION_C_SW_MAJOR_VERSION               1
#define CANSM_VERSION_C_SW_MINOR_VERSION               12

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_VERSION_C_AR_RELEASE_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_VERSION_C_AR_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_VERSION_C_AR_RELEASE_REV_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_VERSION_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_VERSION_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/* CanIf version check */
#if (CANIF_AR_RELEASE_MAJOR_VERSION != CANSM_CANIF_AR_RELEASE_MAJOR_VERSION)
#error "CanIf.h : Mismatch in Specification Major Version"
#endif

#if (CANIF_AR_RELEASE_MINOR_VERSION != CANSM_CANIF_AR_RELEASE_MINOR_VERSION)
#error "CanIf.h : Mismatch in Specification Minor Version"
#endif

/* ComM version check */
#if (COMM_AR_RELEASE_MAJOR_VERSION != CANSM_COMM_AR_RELEASE_MAJOR_VERSION)
#error "ComM.h : Mismatch in Specification Major Version"
#endif
#if (COMM_AR_RELEASE_MINOR_VERSION != CANSM_COMM_AR_RELEASE_MINOR_VERSION)
#error "ComM.h : Mismatch in Specification Minor Version"
#endif

/* DET Version check */
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#if (DET_AR_RELEASE_MAJOR_VERSION != CANSM_DET_AR_RELEASE_MAJOR_VERSION)
#error "Det.h : Mismatch in Specification Major Version"
#endif
#if (DET_AR_RELEASE_MINOR_VERSION != CANSM_DET_AR_RELEASE_MINOR_VERSION)
#error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (STD_ON == CANSM_DEM_STATUS)
/* DEM Version check */
#if (DEM_AR_RELEASE_MAJOR_VERSION != CANSM_DEM_AR_RELEASE_MAJOR_VERSION)
#error "Dem.h : Mismatch in Specification Major Version"
#endif
#if (DEM_AR_RELEASE_MINOR_VERSION != CANSM_DEM_AR_RELEASE_MINOR_VERSION)
#error "Dem.h : Mismatch in Specification Minor Version"
#endif
#endif /* (STD_ON == CANSM_DEM_STATUS) */

/* BswM Version check */
#if (BSWM_AR_RELEASE_MAJOR_VERSION != CANSM_BSWM_AR_RELEASE_MAJOR_VERSION)
#error "BswM.h : Mismatch in Specification Major Version"
#endif
#if (BSWM_AR_RELEASE_MINOR_VERSION != CANSM_BSWM_AR_RELEASE_MINOR_VERSION)
#error "BswM.h : Mismatch in Specification Minor Version"
#endif

#if (STD_ON == CANSM_PN_AVAILABILITY)
/* CanNM Version check */
#if (CANNM_AR_RELEASE_MAJOR_VERSION != CANSM_CANNM_AR_RELEASE_MAJOR_VERSION)
#error "CanNm.h : Mismatch in Specification Major Version"
#endif
#if (CANNM_AR_RELEASE_MINOR_VERSION != CANSM_CANNM_AR_RELEASE_MINOR_VERSION)
#error "CanNm.h : Mismatch in Specification Minor Version"
#endif
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
