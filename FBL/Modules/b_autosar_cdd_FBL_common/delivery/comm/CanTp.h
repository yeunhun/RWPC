/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides the function declaration                   **
**              for the CanTp APIS                                            **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.14.0.0  07-Apr-2021   JYS          Redmine #29231                        **
** 1.0.0     11-Sep-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef CANTP_H
#define CANTP_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "CanTp_Cfg.h"
#include "CanTp_Types.h"
#if (FBL_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Instance id */
#define CANTP_INSTANCE_ID                                             ((uint8)0)

/*  DET Error codes */
#define CANTP_E_PARAM_ID                                           ((uint8)0x02)
#define CANTP_E_PARAM_POINTER                                      ((uint8)0x03)
#define CANTP_E_UNINIT                                             ((uint8)0x20)
#define CANTP_E_INVALID_TX_ID                                      ((uint8)0x30)
#define CANTP_E_INVALID_RX_ID                                      ((uint8)0x40)
#define CANTP_E_INVALID_TX_LENGTH                                  ((uint8)0x70)
#define CANTP_E_INVALID_RX_LENGTH                                  ((uint8)0x80)
#define CANTP_E_INVALID_TATYPE                                     ((uint8)0x90)
#define CANTP_E_OPER_NOT_SUPPORTED                                 ((uint8)0xA0)
#define CANTP_E_COM                                                ((uint8)0xB0)
#define CANTP_E_RX_COM                                             ((uint8)0xC0)
#define CANTP_E_TX_COM                                             ((uint8)0xD0)

/* API Service IDs */
#define CANTP_INIT_SID                                             ((uint8)0x01)
#define CANTP_SHUTDOWN_SID                                         ((uint8)0x02)
#define CANTP_TRANSMIT_SID                                         ((uint8)0x03)
#define CANTP_MAINFUNCTION_SID                                     ((uint8)0x06)
#define CANTP_GETVERSIONINFO_SID                                   ((uint8)0x07)
#define CANTP_RXINDICATION_SID                                     ((uint8)0x42)
#define CANTP_TXCONFIRMATION_SID                                   ((uint8)0x40)
#define CANTP_CANCELTRANSMIT_SID                                   ((uint8)0x08)
#define CANTP_CANCELRECEIVE_SID                                    ((uint8)0x09)
#define CANTP_CHANGEPARAM_SID                                      ((uint8)0x0A)
#define CANTP_READPRAM_SID                                         ((uint8)0x0B)

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
/* Global variable to store CanTp Initialization status */
extern boolean CanTp_GblInitStatus;

/* Array to store Channel specific data variables*/
extern CanTp_ChannelRam CanTp_GaaChannelRam[CANTP_TOTAL_RX_TX_CHANNELS];

/* Array for N_As/N_Ar, N_Bs/N_Br, N_Cs/N_Cr Timersfor all the channels */
extern uint16 CanTp_GaaTimers[CANTP_TOTAL_RX_TX_CHANNELS][3];

/* Array for STMin timers of all channels*/
extern uint8 CanTp_GaaStMinTimers[CANTP_TOTAL_RX_TX_CHANNELS];

extern const uint8 Cantp_Padding_Byte[CANTP_SIXTEEN];

extern const CanTp_DiscreteLength Cantp_GaaDiscreteLength[];

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void CanTp_Init(void);

extern void CanTp_Shutdown(void);

extern Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);

extern Std_ReturnType CanTp_CancelReceive(PduIdType CanTpRxSduId);

extern void CanTp_MainFunction(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* CANTP_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
