/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dbg.h                                                         **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file externs global variable for CAN debug messages      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef DBG_H
#define DBG_H

/*******************************************************************************
**                        Global extern                                       **
*******************************************************************************/
#define BTL_START_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

extern uint16 Dbg_Gu16_TCnt_DCM_Phy_SOR_Rr;

extern uint16 Dbg_Gu16_TCnt_DCM_Phy_SOR_Rs;

extern uint16 Dbg_Gu16_TCnt_DCM_Fun_SOR_Rr;

extern uint16 Dbg_Gu16_TCnt_DCM_Fun_SOR_Rs;

extern uint16 Dbg_Gu16_TCnt_DCM_TX_PosReq;

extern uint16 Dbg_Gu16_TCnt_DCM_TX_NegReq;

extern uint16 Dbg_Gu16_TCnt_DCM_TX_Conf;

extern uint16 Dbg_Gu16_TCnt_TP_Phy_Rx;

extern uint16 Dbg_Gu16_TCnt_TP_Fun_Rx;

extern uint16 Dbg_Gu16_TCnt_TP_Tx_Req;

extern uint16 Dbg_Gu16_TCnt_TP_Tx_Copy;

extern uint16 Dbg_Gu16_TCnt_TP_Tx_Conf;

extern uint16 Dbg_Gu16_TCnt_CanIf_Phy_Rx;

extern uint16 Dbg_Gu16_TCnt_CanIf_Fun_Rx;

extern uint16 Dbg_Gu16_TCnt_CanIf_Tx_Req;

extern uint16 Dbg_Gu16_TCnt_CanIf_Tx_Req_Err;

extern uint16 Dbg_Gu16_TCnt_CanIf_Tx_Conf;

extern uint16 Dbg_Gu16_TCnt_CanIf_Unwanted_Rx;

extern uint16 Dbg_Gu16_TCnt_CanIf_FIFO_Of;

#define BTL_STOP_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

extern void Dbg_MsgTransmit(void);

extern Std_ReturnType Dbg_MsgTransmitSts(void);

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"

#endif /* DBG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
