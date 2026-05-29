/*============================================================================*/
/*                     HYUNDAI AUTRON SOFTWARE GROUP                          */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
* %name:              OsekNm_Ram.c %
* %instance:          xar_1 %
* %version:           1.2.4 %
* %created_by:        ca027 %

* %date_created:      2014/04/09 09:56:24 %
*=============================================================================*/
/* DESCRIPTION : C source file for AUTOSAR OSEK NM                            */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*  Global RAM variables for OsekNm module                                    */
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
/*============================================================================*/

/******************************************************************************
**                      Include Section                                     **
******************************************************************************/

#include "OsekNm_Ram.h"     /* Global RAM variables header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define OSEKNM_RAM_C_AR_MAJOR_VERSION    4
#define OSEKNM_RAM_C_AR_MINOR_VERSION    0
#define OSEKNM_RAM_C_AR_PATCH_VERSION    3

/* OsekNm software version information */
#define OSEKNM_RAM_C_SW_MAJOR_VERSION    1
#define OSEKNM_RAM_C_SW_MINOR_VERSION    6

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (OSEKNM_RAM_AR_MAJOR_VERSION != OSEKNM_RAM_C_AR_MAJOR_VERSION)
  #error "OsekNm_Ram.c : Mismatch in Specification Major Version"
#endif

#if (OSEKNM_RAM_AR_MINOR_VERSION != OSEKNM_RAM_C_AR_MINOR_VERSION)
  #error "OsekNm_Ram.c : Mismatch in Specification Minor Version"
#endif

#if (OSEKNM_RAM_AR_PATCH_VERSION != OSEKNM_RAM_C_AR_PATCH_VERSION)
  #error "OsekNm_Ram.c : Mismatch in Specification Patch Version"
#endif

#if (OSEKNM_RAM_SW_MAJOR_VERSION != OSEKNM_RAM_C_SW_MAJOR_VERSION)
   #error "OsekNm_Ram.c : Mismatch in Software Major Version"
#endif

#if (OSEKNM_RAM_SW_MINOR_VERSION != OSEKNM_RAM_C_SW_MINOR_VERSION)
   #error "OsekNm_Ram.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* Extern definitions */
#define OSEKNM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Global variable to hold initialization status */
VAR(boolean, OSEKNM_NOINIT_DATA) OsekNm_GblInitStatus;

/* Global buffer for NMPDU data to send */
VAR(Tun_OsekNmPduType, OSEKNM_NOINIT_DATA)
  OsekNm_GaaTxPduData[OSEKNM_NUMBER_OF_CHANNELS];

/* Global buffer for received NMPDU data */
VAR(Tun_OsekNmPduType, OSEKNM_VAR)
  OsekNm_GaaRxPduData[OSEKNM_NUMBER_OF_CHANNELS];

/* Global variable to count consecutive transmission request 
   without confirmation in order to detect Limphome state */
VAR(uint8, OSEKNM_VAR) 
  OsekNm_GaaTxCounter[OSEKNM_NUMBER_OF_CHANNELS];

/* Global variable to count going to RESET state without NM message reception */
VAR(uint8, OSEKNM_VAR) 
  OsekNm_GaaRxCounter[OSEKNM_NUMBER_OF_CHANNELS];

/* Global variable contains node address of logical successor */
VAR(uint8, OSEKNM_VAR) 
  OsekNm_GaaLogicalSuccessor[OSEKNM_NUMBER_OF_CHANNELS];

/* Global variable for timer */
VAR(uint16, OSEKNM_VAR) 
  OsekNm_GaaTimer[OSEKNM_NUMBER_OF_CHANNELS];

/* Global variable for reception status */
VAR(Tun_OsekNmRxFlagStatus, OSEKNM_VAR) 
  OsekNm_GunRxFlagStatus[OSEKNM_NUMBER_OF_CHANNELS];

/* Global variable for transmission status */
VAR(Tun_OsekNmTxFlagStatus, OSEKNM_VAR) 
  OsekNm_GunTxFlagStatus[OSEKNM_NUMBER_OF_CHANNELS];

/* Global variable for internal status */
VAR(Tun_OsekNmInternFlagStatus, OSEKNM_VAR) 
  OsekNm_GunInternFlagStatus[OSEKNM_NUMBER_OF_CHANNELS];
  
/* Global variable to indicate if network is requested or released */ 
VAR(uint8, OSEKNM_VAR)
  OsekNm_GaaCurrentNetworkState[OSEKNM_NUMBER_OF_CHANNELS];

#if (OSEKNM_COM_CONTROL_ENABLED == STD_ON)  
/* Global variable to indicate whether transmission is disabled or not */
VAR(boolean, OSEKNM_VAR)
  OsekNm_GaaComControlArray[OSEKNM_NUMBER_OF_CHANNELS];
#endif
                  
/* Global variable to hold current state */
VAR(OsekNm_StateType, OSEKNM_VAR)
  OsekNm_GaaCurrentState[OSEKNM_NUMBER_OF_CHANNELS];

/* Global Variable to hold current mode */
VAR(OsekNm_ModeType, OSEKNM_VAR)
  OsekNm_GaaCurrentMode[OSEKNM_NUMBER_OF_CHANNELS];

/* Global variable to hold current network configuration */
VAR(NetworkConfigurationType, OSEKNM_VAR) OsekNm_GaaNetworkConfig
  [OSEKNM_NUMBER_OF_CHANNELS*OSEKNM_NWCFG_ARRAY_SIZE];

/* Global variable to deliver PDU */ 
VAR(PduInfoType, OSEKNM_VAR) OsekNm_GddPduInfo
  [OSEKNM_NUMBER_OF_CHANNELS];

#define OSEKNM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
