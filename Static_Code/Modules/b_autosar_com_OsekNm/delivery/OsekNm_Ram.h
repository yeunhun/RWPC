/*============================================================================*/
/*                     HYUNDAI AUTRON SOFTWARE GROUP                          */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
* %name:              OsekNm_Ram.h %
* %instance:          xar_1 %
* %version:           1.2.4 %
* %created_by:        ca027 %

* %date_created:      2014/04/09 09:56:30 %
*=============================================================================*/
/* DESCRIPTION : header file for AUTOSAR OSEK NM                              */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/* Provision of OSEKNM extern variables for OsekNm module                     */
/*                                                                            */
/*============================================================================*/
/* COPYRIGHT (C) HYUNDAI AUTRON 2012                                          */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/* 1.0.0     | 16/May/2011 | Initial Creation              | Kyung Tae Kim    */
/* 1.4.0     | 28/Dec/2018 | #15280                        | JeongSu Lim      */
/* 1.5.0     | 13/May/2020 | #21188                        | JeongSu Lim      */
/* 1.5.1     | 27/Nov/2020 | #26628                        | Saemi Kwon       */
/*============================================================================*/

#ifndef OSEKNM_RAM_H
#define OSEKNM_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "OsekNm.h"        /* OSEKNM APIs header file */
#include "OsekNm_PCTypes.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define OSEKNM_RAM_AR_MAJOR_VERSION    4
#define OSEKNM_RAM_AR_MINOR_VERSION    0
#define OSEKNM_RAM_AR_PATCH_VERSION    3

/* File version information */
#define OSEKNM_RAM_SW_MAJOR_VERSION    1
#define OSEKNM_RAM_SW_MINOR_VERSION    6

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* Extern definitions */
#define OSEKNM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Global variable to hold initialization status */
extern VAR(boolean, OSEKNM_VAR) OsekNm_GblInitStatus;

/* polyspace-begin MISRA-C3:8.11 [Not a defect:Justified] "No Impact of this rule violation(Array size will fixed in linking time)" */

/* Global buffer for NMPDU data to send */
extern VAR(Tun_OsekNmPduType, OSEKNM_VAR) OsekNm_GaaTxPduData[];

/* Global buffer for received NMPDU data */
extern VAR(Tun_OsekNmPduType, OSEKNM_VAR) OsekNm_GaaRxPduData[];

/* Global variable to count consecutive transmission request 
   without confirmation in order to detect Limphome state */
extern VAR(uint8, OSEKNM_VAR) OsekNm_GaaTxCounter[];

/* Global variable to count going to RESET state without NM message reception */
extern VAR(uint8, OSEKNM_VAR) OsekNm_GaaRxCounter[];

/* Global variable contains node address of logical successor */
extern VAR(uint8, OSEKNM_VAR) OsekNm_GaaLogicalSuccessor[];

/* Global variable for timer */
extern VAR(uint16, OSEKNM_VAR) OsekNm_GaaTimer[];

/* Global variable for reception status */
extern VAR(Tun_OsekNmRxFlagStatus, OSEKNM_VAR) OsekNm_GunRxFlagStatus[];

/* Global variable for transmission status */
extern VAR(Tun_OsekNmTxFlagStatus, OSEKNM_VAR) 
  OsekNm_GunTxFlagStatus[];

/* Global variable for internal status */
extern VAR(Tun_OsekNmInternFlagStatus, OSEKNM_VAR) OsekNm_GunInternFlagStatus[];
  
/* Global variable to indicate if network is requested or released */ 
extern VAR(uint8, OSEKNM_VAR) OsekNm_GaaCurrentNetworkState[];

#if (OSEKNM_COM_CONTROL_ENABLED == STD_ON)  
/* Global variable to indicate whether transmission is disabled or not */
extern VAR(boolean, OSEKNM_VAR) OsekNm_GaaComControlArray[];
#endif
                  
/* Global variable to hold current state */
extern VAR(OsekNm_StateType, OSEKNM_VAR) OsekNm_GaaCurrentState[];

/* Global Variable to hold current mode */
extern VAR(OsekNm_ModeType, OSEKNM_VAR) OsekNm_GaaCurrentMode[];

/* Global variable to hold current network configuration */
extern VAR(NetworkConfigurationType, OSEKNM_VAR) OsekNm_GaaNetworkConfig[];
/* Global variable to deliver PDU */ 
extern VAR(PduInfoType, OSEKNM_VAR) OsekNm_GddPduInfo[];
#define OSEKNM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* polyspace-end MISRA-C3:8.11 [Not a defect:Justified] "No Impact of this rule violation(Array size will fixed in linking time)" */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* OSEKNM_RAM_H */

/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/

