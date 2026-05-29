/*============================================================================*/
/*                        CARNES SOFTWARE GROUP                               */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* %name:              OsekNm_Cbk.h %
* %instance:          xar_1 %
* %version:           3 %
* %created_by:        ca027 %

* %date_created:      2014/04/03 19:19:59 %
*=============================================================================*/
/* DESCRIPTION : header file for AUTOSAR CAN NM                               */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/* Provision of callback declarations and macro definitions for OsekNm module */
/*                                                                            */
/*============================================================================*/
/* COPYRIGHT (C) CARNES 2006                                                  */
/* AUTOMOTIVE ELECTRONICS                                                     */
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
/* 1.4.2     | 08/Mar/2019 | #16398                        | JeongSu Lim      */
/* 1.5.0     | 13/May/2020 | #21188                        | JeongSu Lim      */
/*============================================================================*/

#ifndef OSEKNM_CBK_H
#define OSEKNM_CBK_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "OsekNm.h"           /* API Header file */
#include "NmStack_Types.h" /* Nm Interface type definitions header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define OSEKNM_CBK_AR_MAJOR_VERSION  4
#define OSEKNM_CBK_AR_MINOR_VERSION  0
#define OSEKNM_CBK_AR_PATCH_VERSION  3

/* OSEKNM software version information */
#define OSEKNM_CBK_SW_MAJOR_VERSION  1
#define OSEKNM_CBK_SW_MINOR_VERSION  6

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, OSEKNM_CODE) OsekNm_TxConfirmation 
                                                       (PduIdType canNmTxPduId);
    
extern FUNC(void, OSEKNM_CODE) OsekNm_RxIndication (PduIdType canNmRxPduId,
                        P2CONST(PduInfoType, AUTOMATIC, OSEKNM_APPL_CONST) PduInfoPtr);

    
extern FUNC(void, OSEKNM_CODE) OsekNm_TxTimeoutException 
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle);

extern FUNC(void, OSEKNM_CODE) OsekNm_ControllerBusOff 
                                       (VAR(uint8, OSEKNM_VAR) CanControllerId);

#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* OSEKNM_CBK_H */

/******************************************************************************
**                               END OF FILE                                 **
******************************************************************************/
