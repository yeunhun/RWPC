/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf.h                                                       **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides dummy functionality of CanIf               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef CANIF_H
#define CANIF_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "CanIf_Types.h"
#include "CanIf_Cfg.h"

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
extern void CanIf_Init(void);

extern Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId,
  const PduInfoType* PduInfoPtr);

/* RxIndication event referring to a CAN Controller for AUTOSAR 4.2.2*/
extern void CanIf_RxIndication(const Can_HwType* Mailbox,
  const PduInfoType* PduInfoPtr);

/* TxConfirmaton event referring to a CAN Controller */
extern void CanIf_TxConfirmation(PduIdType CanTxPduId);

/* BusOff event referring to a CAN Controller */
extern void CanIf_ControllerBusOff(uint8 ControllerId);

#endif /* CANIF_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
