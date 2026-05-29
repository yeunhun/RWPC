/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: EthDiag_Cbk.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides declarations for callbacks provided by EthDiag       **
**              which will be used by lower layer                             **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef ETHDIAG_CBK_H
#define ETHDIAG_CBK_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "EthDiag_Types.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/* Function indicates the start of a message thorough TCP message */
extern BufReq_ReturnType EthDiag_TcpIpwTcpStartOfReception(
  TcpIpw_SocketIdType Ldt_SocketId,
  const uint8* Lpu8_DataPtr,
  uint16 Lu16_DataLength,
  uint16 Lu16_TotalDataLength,
  uint16* Lpu16_BufferSizePtr
);

/* Function copy message thorough TCP message */
extern BufReq_ReturnType EthDiag_TcpIpwTcpCopyRxData(
  TcpIpw_SocketIdType Ldt_SocketId,
  const uint8* Lpu8_DataPtr,
  uint16 Lu16_Length,
  uint16* Lpu16_BufferSizePtr
);

/* Function indicates the complete data is transferred  */
extern void EthDiag_TcpIpwTcpRxIndication(
  TcpIpw_SocketIdType Ldt_SocketId,
  Std_ReturnType Ldt_Result
);

/* Function copy message to lower layer buffer */
extern BufReq_ReturnType EthDiag_TcpIpwTcpCopyTxData(
  TcpIpw_SocketIdType Ldt_SocketId,
  uint8* Lpu8_BufPtr,
  uint16 Lu16_BufLength
);

/* Function indicates the result of transmission through a TCP socket */
extern void EthDiag_TcpIpwTcpTxConfirmation(
  TcpIpw_SocketIdType Ldt_SocketId,
  Std_ReturnType Ldt_Result
);

/* Function indicates the Socket is accepted */
extern Std_ReturnType EthDiag_TcpAccepted(
  TcpIpw_SocketIdType Ldt_SocketId,
  TcpIpw_SocketIdType Ldt_SocketIdConnected,
  const TcpIpw_SockAddr_Styp* Lpst_RemoteAddrPtr
);

/* Function indicates the change IP address */
extern void EthDiag_LocalIpAddrAssignmentChg(
  TcpIpw_LocalAddrIdType Ldt_IpAddrId,
  TcpIpw_IpAddrState_Etyp Len_State
);

/* Function indicates the closing of a TCP socket */
extern void EthDiag_TcpIpEvent(
  TcpIpw_SocketIdType Ldt_SocketId,
  TcpIpw_Event_Etyp Len_Event
);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* ETHDIAG_CBK_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
