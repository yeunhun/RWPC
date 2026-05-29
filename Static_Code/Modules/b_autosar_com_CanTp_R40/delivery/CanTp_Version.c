/*******************************************************************************
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_Version.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp_Version.h"        /* CanTp Version Header File */
#include "PduR_CanTp.h"           /* PduR header for CAN TP */
#include "CanIf.h"                /* CanIf header file */
#include "SchM_CanTp.h"           /* Scheduler Header File */
#include "Rte.h"                  /* Rte Header File */
#include "PduR.h"                 /* PduR Header File */
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
#include "Det.h"                  /* DET header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define CANTP_VERSION_C_AR_RELEASE_MAJOR_VERSION    4
#define CANTP_VERSION_C_AR_RELEASE_MINOR_VERSION    0
#define CANTP_VERSION_C_AR_RELEASE_REVISION_VERSION 3

/* Software Version Information */
#define CANTP_VERSION_C_SW_MAJOR_VERSION            1
#define CANTP_VERSION_C_SW_MINOR_VERSION            11
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/* CAN TP Version Check */
#if (CANTP_AR_RELEASE_MAJOR_VERSION != CANTP_VERSION_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANTP_AR_RELEASE_MINOR_VERSION != CANTP_VERSION_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_VERSION_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp_Version.c : Mismatch in Specification Revision Version"
#endif

#if (CANTP_SW_MAJOR_VERSION != CANTP_VERSION_C_SW_MAJOR_VERSION)
#error "CanTp_Version.c : Mismatch in Software Major Version"
#endif

#if (CANTP_SW_MINOR_VERSION != CANTP_VERSION_C_SW_MINOR_VERSION)
#error "CanTp_Version.c : Mismatch in Software Minor Version"
#endif

/* PDUR Version Check */
#if (PDUR_AR_RELEASE_MAJOR_VERSION != CANTP_PDUR_AR_RELEASE_MAJOR_VERSION)
#error "PduR.h : Mismatch in Specification Major Version"
#endif

#if (PDUR_AR_RELEASE_MINOR_VERSION != CANTP_PDUR_AR_RELEASE_MINOR_VERSION)
#error "PduR.h : Mismatch in Specification Minor Version"
#endif

/* CAN Interface Version Check */
#if (CANIF_AR_RELEASE_MAJOR_VERSION != CANTP_CANIF_AR_RELEASE_MAJOR_VERSION)
#error "CanIf.h : Mismatch in Specification Major Version"
#endif

#if (CANIF_AR_RELEASE_MINOR_VERSION != CANTP_CANIF_AR_RELEASE_MINOR_VERSION)
#error "CanIf.h : Mismatch in Specification Minor Version"
#endif

/* DET Version Check */
#if (CANTP_DEV_ERROR_DETECT == STD_ON)
#if (DET_AR_RELEASE_MAJOR_VERSION != CANTP_DET_AR_RELEASE_MAJOR_VERSION)
#error "Det.h : Mismatch in Specification Major Version"
#endif

#if (DET_AR_RELEASE_MINOR_VERSION != CANTP_DET_AR_RELEASE_MINOR_VERSION)
#error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */

/* SCHM Version Check */
#if (RTE_AR_RELEASE_MAJOR_VERSION != CANTP_RTE_AR_RELEASE_MAJOR_VERSION)
#error "Rte.h : Mismatch in Rte Specification Major Version"
#endif
#if (RTE_AR_RELEASE_MINOR_VERSION != CANTP_RTE_AR_RELEASE_MINOR_VERSION)
#error "Rte.h : Mismatch in Rte Specification Minor Version"
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

