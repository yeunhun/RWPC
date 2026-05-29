/*******************************************************************************
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_Ram.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Global RAM variables of CanTp                                 **
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
** 1.10.1    16-Oct-2019   SM Kwon        Redmine #19629                      **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp_IntTypes.h"       /* CanTp Internal types header file */
#include "SchM_CanTp.h"           /* SchM Header File */
#include "CanTp_PCTypes.h"        /* CanTp PCTypes Header File */
#include "CanTp_Ram.h"            /* CanTp PCTypes Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANTP_RAM_C_AR_RELEASE_MAJOR_VERSION    4
#define CANTP_RAM_C_AR_RELEASE_MINOR_VERSION    0
#define CANTP_RAM_C_AR_RELEASE_REVISION_VERSION 3

/* CANTP software version information */
#define CANTP_RAM_C_SW_MAJOR_VERSION            1
#define CANTP_RAM_C_SW_MINOR_VERSION            11

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANTP_AR_RELEASE_MAJOR_VERSION != CANTP_RAM_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp_Ram.c : Mismatch in Specification Major Version"
#endif
#if (CANTP_AR_RELEASE_MINOR_VERSION != CANTP_RAM_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp_Ram.c : Mismatch in Specification Minor Version"
#endif
#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_RAM_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp_Ram.c : Mismatch in Specification Revision Version"
#endif
#if (CANTP_SW_MAJOR_VERSION != CANTP_RAM_C_SW_MAJOR_VERSION)
#error "CanTp_Ram.c : Mismatch in Software Major Version"
#endif
#if (CANTP_SW_MINOR_VERSION != CANTP_RAM_C_SW_MINOR_VERSION)
#error "CanTp_Ram.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define CANTP_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store CanTp Initialization status */
VAR(boolean, CANTP_VAR) CanTp_GblInitStatus;
#define CANTP_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if (CANTP_RX_NSDU == STD_ON)
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
VAR(uint8, CANTP_VAR) CanTp_GaaRxDl[CANTP_MAXNO_RX_SDU];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

