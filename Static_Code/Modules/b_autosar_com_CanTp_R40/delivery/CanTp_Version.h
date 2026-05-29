/*******************************************************************************
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_Version.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : C header for CanTp_Version                                    **
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
** 1.8.1     18-Mar-2019   SM Kwon        Redmine #16559                      **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/
#ifndef CANTP_VERSION_H
#define CANTP_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp.h"                /* CAN TP Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define CANTP_VERSION_AR_RELEASE_MAJOR_VERSION    4
#define CANTP_VERSION_AR_RELEASE_MINOR_VERSION    0
#define CANTP_VERSION_AR_RELEASE_REVISION_VERSION 3

/* Software Version Information */
#define CANTP_VERSION_SW_MAJOR_VERSION            1
#define CANTP_VERSION_SW_MINOR_VERSION            11

/* Other (Interface) module version information */
#define CANTP_PDUR_AR_RELEASE_MAJOR_VERSION  4
#define CANTP_PDUR_AR_RELEASE_MINOR_VERSION  0

#define CANTP_CANIF_AR_RELEASE_MAJOR_VERSION 4
#define CANTP_CANIF_AR_RELEASE_MINOR_VERSION 0

#if (CANTP_DEV_ERROR_DETECT == STD_ON)
#define CANTP_DET_AR_RELEASE_MAJOR_VERSION   4
#define CANTP_DET_AR_RELEASE_MINOR_VERSION   0
#endif

#define CANTP_RTE_AR_RELEASE_MAJOR_VERSION   4
#define CANTP_RTE_AR_RELEASE_MINOR_VERSION   0

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* CANTP_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

