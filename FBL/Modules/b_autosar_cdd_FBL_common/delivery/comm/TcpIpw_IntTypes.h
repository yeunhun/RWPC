/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: TcpIpw_IntTypes.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides internal type definitions to the TcpIpw    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef TCPIPW_INTTYPES_H
#define TCPIPW_INTTYPES_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "TcpIpw_Types.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Macro for zero */
#define TCPIPW_ZERO                                                           0U

/* Invalid Domain */
#define TCPIPW_DOMAIN_INVALID                           (TcpIpw_DomainType)0xFFU

/* Invalid IP address identifier */
#define TCPIPW_IP_ID_INVALID                       (TcpIpw_LocalAddrIdType)0xFFU

/* Macro for no pending transmit data bytes */
#define TCPIPW_NO_BYTES_TO_TRANSMIT                                  TCPIPW_ZERO

/* Initial IP address */
#define TCPIPW_INITIAL_IP_ADDR                                       TCPIPW_ZERO

/* Initial port number */
#define TCPIPW_INITIAL_PORT_NUM                                      TCPIPW_ZERO

/* Initial netmask */
#define TCPIPW_INITIAL_NETMASK                                       TCPIPW_ZERO

/* Initial gateway address */
#define TCPIPW_INITIAL_GATEWAY_ADDR                                  TCPIPW_ZERO

/* Maximum number of network address bits */
#define TCPIPW_NETWORK_ADDR_BITS_MAX                                         32u

/* Macro for making a parameter unused */
#define TCPIPW_UNUSED_ARG(x)                                           ((void)x)

#define TCPIPW_INDEX_ZERO                                            TCPIPW_ZERO

#define TCPIPW_LWIP_MEM_ERR                                       (err_t)ERR_MEM

#define TCPIPW_LWIP_E_OK                                           (err_t)ERR_OK

#define TCPIPW_MAC_ADDR_LEN                                                0x06U

/* Added typecasting to remove assigning to narrower expression */
#define TCPIPW_TCP_SOCK_STRT_RNG                             (uint8) TCPIPW_ZERO

#define TCPIPW_TCP_SOCK_END_RNG \
  (uint8) (TCPIPW_TCP_SOCK_STRT_RNG + TCPIPW_TCP_SOCKID_COUNT)

#define TCPIPW_UDP_SOCK_STRT_RNG \
  (uint8) (TCPIPW_TCP_SOCK_STRT_RNG + TCPIPW_TCP_SOCKID_COUNT)

#define TCPIPW_UDP_SOCK_END_RNG \
  (uint8) (TCPIPW_UDP_SOCK_STRT_RNG + TCPIPW_UDP_SOCKID_COUNT)

#define TCPIPW_SOCK_STRT_RNG                    (uint8) TCPIPW_TCP_SOCK_STRT_RNG

#define TCPIPW_SOCK_END_RNG                      (uint8) TCPIPW_UDP_SOCK_END_RNG

#define TCPIPW_IP_ADDR_STRT_RNG                                      TCPIPW_ZERO

#define TCPIPW_IP_ADDR_END_RNG \
  (TCPIPW_IP_ADDR_STRT_RNG + TCPIPW_IP_ADDR_ID_COUNT)

/* Macro for Tx operation on socket */
#define TCPIPW_ACTIVE_OP_TX                                         (uint8)0x01u

/* Macro for Rx operation on socket */
#define TCPIPW_ACTIVE_OP_RX                                         (uint8)0x02u

/* Macro for no operation on socket */
#define TCPIPW_ACTIVE_OP_IDLE                                       (uint8)0x00u

/* Close operation is not requested by remote node or user module */
#define TCPIPW_CLOSE_NOT_REQUESTED                                  (uint8)0x00u

/* Macro for active close operation */
#define TCPIPW_ACTIVE_CLOSE                                         (uint8)0x01u

/* Macro for passive close operation */
#define TCPIPW_PASSIVE_CLOSE                                        (uint8)0x02u

/* Macro for invalid socket buffer ID */
#define TCPIPW_BUFFER_ID_INVALID                                    (uint8)0xFFu

/* Macro for conversion of seconds to milliseconds */
#define TCPIPW_CONVERT_SEC_TO_MS                                  (uint32)1000UL

/* Flag for TCP_WRITE_FLAG_COPY in tcp_write API */
#define TCPIPW_APIFLAGS                                              (uint8)0x01

/* As PrevChunk sent flag is bit no 2 of Activeop byte */
#define TCPIPW_PREVCHUNK_SENTFLAG_MASK                              (uint8)0x04U

#define TCPIPW_ACTIVE_OP_TX_WITH_PREV_CHUNK_SENT                    (uint8)0x05U

#define TCPIPW_IPADDR_ISANY                                           IPADDR_ANY

/* Macro definitions for socket ID initialization */
#define TCPIPW_ONE                                                     (uint8)1u
#define TCPIPW_TWO                                                     (uint8)2u
#define TCPIPW_THREE                                                   (uint8)3u
#define TCPIPW_FOUR                                                    (uint8)4u
#define TCPIPW_FIVE                                                    (uint8)5u

/*******************************************************************************
**                              Type Definition                               **
*******************************************************************************/
typedef enum
{
  TCPIPW_IP_ADDR_DEFAULT = 0x00u,
  TCPIPW_IP_ADDR_UNICAST = 0x01u,
  TCPIPW_IP_ADDR_MULTICAST = 0x02u,
  TCPIPW_IP_ADDR_BROADCAST = 0x03u
}TcpIpw_IpAddr_Etyp;

/*
 * Data type for Socket state
 */
typedef enum
{
  TCPIPW_SOCK_STATE_CLOSED    = 0x01u,
  TCPIPW_SOCK_STATE_OPENED    = 0x02u,
  TCPIPW_SOCK_STATE_BOUND     = 0x03u,
  TCPIPW_SOCK_STATE_LISTEN    = 0x04u,
  TCPIPW_SOCK_STATE_CONNECTED = 0x05u,
  TCPIPW_SOCK_STATE_CLOSING   = 0x06u
}TcpIpw_SockState_Etyp;

/*
 * Data type for Socket information
 */
typedef struct
{
  /* Local socket address information */
  TcpIpw_SockAddr_Styp st_LocalSockAddr;

  /* Remote address information */
  TcpIpw_SockAddr_Styp st_RemoteSockAddr;

  /* Related Protocol Control Block */
  void * pt_RelatedPcb;

  /* Socket state */
  TcpIpw_SockState_Etyp en_SockState;

  /* Protocol Type */
  TcpIpw_Protocol_Etyp en_ProtocolType;

  /* Indicates remaining bytes to transmit */
  uint16 u16_RemainingTxBytes;

  /* Bytes acknowledged by the upper layer  */
  uint16 u16_AckRxBytesCount;

  /* Available for holding buffer size value of user module */
  uint16 u16_DestRxBufSize;

  /* Socket ID of the current socket */
  TcpIpw_SocketIdType dt_SockId;

  /* IP address identifier */
  TcpIpw_LocalAddrIdType dt_IpAddrId;

  /* Operation currently active on socket */
  uint8 u8_ActiveOp;

  /* Type of close operation */
  uint8 u8_CloseOpType;

  /* Buffer ID for related buffer */
  uint8 u8_TcpTxBufferId;

}TcpIpw_SockInfo_Styp;

/*
 * Data type for Socket information
 */
typedef struct
{
  /* Local IP address */
  uint32 au32_IpAddr[TCPIPW_NO_WORDS_FOR_IP_ADDR];

  /* Gateway address */
  uint32 au32_GatewayAddr[TCPIPW_NO_WORDS_FOR_IP_ADDR];

  /* IP address state */
  TcpIpw_IpAddrState_Etyp en_IpAddrState;

  /* Type of IP address assignment */
  TcpIpw_IpAddrAssignment_Etyp en_IpAddrAssignType;

  /* Type of IP address (Unicast, Multicast, Broadcast) */
  TcpIpw_IpAddr_Etyp en_IpAddrType;

  /* Local netmask */
  uint8 u8_NetMask;

  /* Domain Type */
  TcpIpw_DomainType dt_Domain;

  /* Element to provide notification for the released IP address */
  boolean bl_ReleasePending;
}TcpIpw_IpAddrInfo_Styp;

/*
 * Data type for TX buffer information
 */
typedef struct
{
  /* TCP Buffer location */
  struct pbuf * pst_BufPtr;

  /* Active operation on TCP buffer */
  uint8 u8_ActiveOp;

  /* Buffer Identifier */
  uint8 u8_BufId;
}TcpIpw_TcpTxBufInfo_Styp;

#endif /* TCPIPW_INTTYPES_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
