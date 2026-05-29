/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: EthDiag_Types.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides data types required in EthDiag                       **
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

#ifndef ETHDIAG_TYPES_H
#define ETHDIAG_TYPES_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "TcpIpw.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define ETHDIAG_TYPES_ZERO                                                  0x00
#define ETHDIAG_RX_BUFFER_SIZE                                               12U
#define ETHDIAG_TX_BUFFER_SIZE                                               12U

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
typedef enum
{
  ETHDIAG_TIMER_IDLE = ETHDIAG_TYPES_ZERO,
  ETHDIAG_TIMER_STOP,
  ETHDIAG_TIMER_RUNNING,
  ETHDIAG_TIMER_EXPIRED
}EthDiag_TimerState_Etyp;

typedef enum
{
  RX_BUFFER_IDLE = ETHDIAG_TYPES_ZERO,
  RX_IN_PROGRESS,
} EthDiag_RxProcessState_Etyp;

typedef enum
{
  TX_BUFFER_INIT = ETHDIAG_TYPES_ZERO,
  TX_BUFFER_READY,
  TX_IN_PROGRESS,
  TX_COMPLETE
} EthDiag_TxProcessState_Etyp;

typedef enum
{
  ETHDIAG_IPADDRESS_UNASSIGNED = ETHDIAG_TYPES_ZERO,
  ETHDIAG_IPADDRESS_ASSIGNED,
  ETHDIAG_IPADDRESS_REASSIGNED
}EthDiag_IPAddrAssignmentState_Etyp;

typedef enum
{
  ETHDIAG_SOCKET_OPENED = ETHDIAG_TYPES_ZERO,
  ETHDIAG_SOCKET_BOUND,
  ETHDIAG_SOCKET_LISTEN,
  ETHDIAG_SOCKET_CLOSING,
  ETHDIAG_SOCKET_CONNECTED,
  ETHDIAG_SOCKET_CLOSED
}EthDiag_SocketState_Etyp;

typedef enum
{
  ETHDIAG_SOCKET_STATE_POLLING = ETHDIAG_TYPES_ZERO,
  ETHDIAG_WAITING_FOR_CONNECTION,
  ETHDIAG_ACTIVE_CONNECTION
}EthDiag_CurrentState_Etyp;

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
typedef struct
{
  EthDiag_IPAddrAssignmentState_Etyp en_IPAddrAssignmentState;
  TcpIpw_LocalAddrIdType dt_LocalAddrId;
}EthDiag_IpAddressInfo_Styp;

typedef struct
{
  EthDiag_TimerState_Etyp en_TimerState;
  uint32 u32_TimerValue;
}EthDiag_Timer_Styp;

typedef struct
{
  TcpIpw_SocketIdType dt_SocketId;
  TcpIpw_SockAddr_Styp st_RemoteAddr;
  uint16 u16_ReceivedData;
  EthDiag_RxProcessState_Etyp en_ProcessState;
  uint32 u32_TpSduLength;
  uint8 au8_RxBuffer[ETHDIAG_RX_BUFFER_SIZE];
} EthDiag_RxBuffer_Styp;

typedef struct
{
  TcpIpw_SocketIdType dt_SocketId;
  EthDiag_SocketState_Etyp en_SocketState;
}EthDiag_SocketInfo_Styp;

typedef struct
{
  EthDiag_Timer_Styp st_AliveCheckTimer;
  EthDiag_SocketInfo_Styp st_SocketData;
  uint16 u16_PayloadType;
}EthDiag_TesterConnectionInfo_Styp;

typedef struct
{
  TcpIpw_SocketIdType dt_SocketId;
  TcpIpw_SockAddr_Styp st_RemoteAddr;
  EthDiag_TxProcessState_Etyp en_ProcessState;
  uint16 u16_PayloadType;
  uint16 u16_EthDiagHeaderLength;
  PduLengthType dt_SduLength;
  uint16 u16_Length;
  uint16 u16_LengthCopied;
  uint8 au8_TxBuffer[ETHDIAG_TX_BUFFER_SIZE];
} EthDiag_TxBuffer_Styp;

#endif /* ETHDIAG_TYPES_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
