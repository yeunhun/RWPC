/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: EthDiag_Internal.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides declarations for internal functions, variables       **
**              and macros of EthDiag                                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.1     06-Dec-2019   Sinil        Redmine #20452                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef ETHDIAG_INTERNAL_H
#define ETHDIAG_INTERNAL_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "EthDiag_Types.h"
#include "EthDiag_Cfg.h"
#include "Util.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define ETHDIAG_FALSE                                             (boolean)FALSE
#define ETHDIAG_TRUE                                               (boolean)TRUE

#define ETHDIAG_ZERO                                                       0x00u
#define ETHDIAG_ONE                                                        0x01u
#define ETHDIAG_TWO                                                        0x02u
#define ETHDIAG_THREE                                                      0x03u
#define ETHDIAG_FOUR                                                       0x04u
#define ETHDIAG_SIX                                                        0x06u
#define ETHDIAG_EIGHT                                                      0x08u
#define ETHDIAG_TEN                                                        0x0Au
#define ETHDIAG_TWELVE                                                     0x0Cu

/* Payload type */
#define ETHDIAG_ALIVE_CHECK_REQ_PAYLOADTYPE                      (uint16)0x0007u
#define ETHDIAG_ALIVE_CHECK_RESP_PAYLOADTYPE                     (uint16)0x0007u
#define ETHDIAG_DIAG_MSG_REQ_PAYLOADTYPE                         (uint16)0x8001u
#define ETHDIAG_MASS_DATA_TFR_PAYLOADTYPE                        (uint16)0xFCBCu

#define ETHDIAG_RX_MAX_BUFFER_COUNT                                        0x02u
#define ETHDIAG_TX_MAX_BUFFER_COUNT                                        0x01u

#define ETHDIAG_MEMCOPY                                              Util_Memcpy

#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
#define ETHDIAG_ENDIANNESSCONV_32(_var,_result)                            \
  *(uint32*)_result = ((((_var) & 0x000000ffUL) << 24) |                   \
            (((_var) & 0x0000ff00UL) <<  8) |                              \
            (((_var) & 0x00ff0000UL) >>  8) |                              \
            (((_var) & 0xff000000UL) >> 24));
#else
#define ETHDIAG_ENDIANNESSCONV_32(_var,_result)                            \
  *(uint32*)_result = _var;

#endif /* (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */

#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
#define ETHDIAG_ENDIANNESSCONV_16(_var, _result)                           \
  *(uint16*)_result = ((((_var) & 0x00ffUL) << 8) | (((_var) & 0xff00UL) >> 8));
#else
#define ETHDIAG_ENDIANNESSCONV_16(_var, _result)                           \
  *(uint16*)_result = _var;
#endif /* (CPU_BYTE_ORDER == LOW_BYTE_FIRST) */

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

extern EthDiag_TesterConnectionInfo_Styp EthDiag_Gast_TesterConnectionData[ETHDIAG_MAX_TESTER_COUNT];

extern EthDiag_IpAddressInfo_Styp EthDiag_Gst_IPAddrAssignmentInfo;

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"

#define BTL_START_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

extern EthDiag_TxBuffer_Styp EthDiag_Gadt_TxBuffer[ETHDIAG_TX_MAX_BUFFER_COUNT];

extern EthDiag_SocketInfo_Styp EthDiag_Gast_SocketData;

#define BTL_STOP_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/* Function provides the buffer index of tx buffer */
Std_ReturnType EthDiag_GetTxBufferIndex(
  uint8 *Lpu8_Index
);

/* Function prepares the Alive check request */
Std_ReturnType EthDiag_SendAliveCheckRequest(
  TcpIpw_SocketIdType Ldt_SocketId
);

/* Function to copy data */
void EthDiag_MemCopy(
  uint8* Lpu8_Target,
  const uint8* Lpu8_Source,
  uint16 Lu16_Length
);

/* Function to compare data */
Std_ReturnType EthDiag_MemCompare(
  const uint8* Lpu8_Target,
  const uint8* Lpu8_Source,
  uint16 Lu16_Length
);

/* Function triggers Ip address assignment */
Std_ReturnType EthDiag_SocketStatePolling(
  const EthDiag_IpAddressInfo_Styp *Lpst_IPAddrAssignmentInfo
);

/* Function triggers closing a socket */
Std_ReturnType EthDiag_CloseSocket(
  TcpIpw_SocketIdType Ldt_SocketId
);

/* Function to check if any transmission is ongoing */
boolean EthDiag_IfTxOngoing(void);

/* Function to reset buffer */
void EthDiag_ResetBuffers(
  EthDiag_RxBuffer_Styp *Lpst_RxBuffer,
  EthDiag_TxBuffer_Styp *Lpst_TxBuffer
);

Std_ReturnType EthDiag_DiagnosticValidateRequest(
  EthDiag_RxBuffer_Styp Lst_RxBuffer
);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* ETHDIAG_INTERNAL_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
