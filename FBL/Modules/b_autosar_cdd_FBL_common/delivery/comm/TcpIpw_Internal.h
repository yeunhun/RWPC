/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: TcpIpw_Internal.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides the internal function declaration          **
**              for the TcpIp wrapper                                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.10.0.0  07-Feb-2021   JYS          Redmine #28218                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef TCPIPW_INTERNAL_H
#define TCPIPW_INTERNAL_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* Header file inclusion for standard type definitions */
#include "Btl.h"
#include "TcpIpw_Types.h"
/* Header file for extern definition of the TCPIP wrapper functions */
#include "TcpIpw.h"
/* Header file for TcpIpw configuration settings */
#include "TcpIpw_Cfg.h"
/* Header file for inclusion of all global variables declared using configuration information */
#include "TcpIpw_Globals.h"
/* Header file for Ethernet related functionality */
#include "netif/ethernet.h"
/* Header file for network interface related type definitions */
#include "lwip/netif.h"
/* Header file for memory allocation related type definitions */
#include "lwip/pbuf.h"
/* Header file for TCP related data structures */
#include "lwip/tcp.h"
/* Header file for UDP related data structures */
#include "lwip/udp.h"
/* Header file for type definitions of error handling */
#include "lwip/err.h"
/* Header file for Ethernet interface functionality */
#include "netif/ethernetif.h"
/* Header file for lwIP stack initialization functionality */
#include "lwip/init.h"
/* Header file for lwIP stack timing functionality */
#include "lwip/timeouts.h"
/* Header file containing common utility's like a copy utility */
#include "Util.h"

#include "EthDiag_Internal.h"

#if (((STD_ON == TCPIPW_AUTOIP)&&(STD_OFF == TCPIPW_DHCP)) || ((STD_ON == TCPIPW_AUTOIP)&&(STD_ON == TCPIPW_DHCP)))
/* Header file for AutoIp address assignment */
#include "lwip/autoip.h"
#endif

#if (((STD_ON == TCPIPW_DHCP)&&(STD_OFF == TCPIPW_AUTOIP)) || ((STD_ON == TCPIPW_AUTOIP)&&(STD_ON == TCPIPW_DHCP)))
/* Header file for DHCP address assignment */
#include "lwip/dhcp.h"
#endif

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Macro to check whether socket is valid or not added additional brackets to prevent 12.1 lint */
#define TCPIPW_IS_SOCK_VALID(SockId)  (((SockId >= TCPIPW_SOCK_STRT_RNG) && \
  (SockId < TCPIPW_SOCK_END_RNG))? TRUE: FALSE)

/* Macro to check whether provided UDP socket is valid or not */
#define TCPIPW_IS_TCP_SOCK_VALID(SockId)  (((SockId >= TCPIPW_TCP_SOCK_STRT_RNG) && \
  (SockId < TCPIPW_TCP_SOCK_END_RNG))? TRUE: FALSE)

/* Macro to check whether provided TCP socket is valid or not */
#define TCPIPW_IS_UDP_SOCK_VALID(SockId)  (((SockId >= TCPIPW_UDP_SOCK_STRT_RNG) && \
  (SockId < TCPIPW_UDP_SOCK_END_RNG))? TRUE: FALSE)

/* Macro to check whether provided IP address ID is valid or not */
#define TCPIPW_IS_IP_ADDR_ID_VALID(AddrId)  (((AddrId >= TCPIPW_IP_ADDR_STRT_RNG) && \
  (AddrId < TCPIPW_IP_ADDR_END_RNG))? TRUE: FALSE)

/* Macro for converting number of netmask bits to netmask address */
#define TCPIPW_GET_NETMASK_ADDR_FROM_BITS(Bits) \
  (uint32)(0xFFFFFFFFu ^ (0xFFFFFFFFu >> Bits))

#define TCPIPW_DEFAULT_IP_INFO_INDEX                                          2u

#if ((TCPIPW_DHCP == STD_ON) && (TCPIPW_AUTOIP == STD_ON))

#define TCPIPW_AUTOIP_MASK                                           0xFFFF0000u

#define TCPIPW_AUTOIP_PATTERN                                        0xA9FE0000u

#endif
#define TCPIPW_DISCARD      (uint8)0
#define TCPIPW_NOT_ENOUGH   (uint8)1
#define TCPIPW_PASS         (uint8)2
#define TCPIPW_MAXIMUM_FIRST_CHUNK_SIZE 1600
#define ETHDIAG_HEADER_LEGNTH 8
#define ETHDIAG_MASSDATA_LENGTH_WITH_ATLEAST_ONE_DATA 13

/*******************************************************************************
**                            Global Variables                                **
*******************************************************************************/
#define BTL_START_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

/* Variable for holding Network interface information */
extern struct netif  TcpIpw_Gst_EthernetNetIfZero;

#define BTL_STOP_SEC_VAR_NO_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/* Function for allocation of TCP buffers */
extern  Std_ReturnType TcpIpw_AllocTcpBuf(void);

extern Std_ReturnType TcpIpw_AssignUdpSock(
  TcpIpw_SocketIdType* Lpdt_SocketIdPtr);
  
extern Std_ReturnType TcpIpw_AssignTcpSock(
  TcpIpw_SocketIdType* Lpdt_SocketIdPtr);
  
/* Function for allocation of UDP buffers */
extern Std_ReturnType TcpIpw_AllocAndMapTcpRsrc(
  TcpIpw_SocketIdType Ldt_SocketId);

/* Function for allocation of UDP buffers */
extern Std_ReturnType TcpIpw_AllocAndMapUdpRsrc(
  TcpIpw_SocketIdType Ldt_SocketId);

/* Function used to change the priority of Pcb related to socket */
extern Std_ReturnType TcpIpw_ChangePriority(
  const TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  uint8 Lu8_ParameterValue);

/* Function used to change the Time to live of Pcb related to socket */
extern Std_ReturnType TcpIpw_ChangeTimeToLive(
  const TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  uint8 Lu8_ParameterValue);

/* Function used to change the type of service of Pcb related to socket */
extern Std_ReturnType TcpIpw_ChangeTypeOfService(
  const TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  uint8 Lu8_ParameterValue);

/* Function used to change the Nagle algorithm status */
extern Std_ReturnType TcpIpw_ChangeNagleAlgorithm(
  const TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  uint8 Lu8_ParameterValue);

/* Function used to change time after which keep alive message is sent */
extern Std_ReturnType TcpIpw_ChangeKeepAliveTime(
  const TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  uint8 Lu8_ParameterValue);

/* Function used to change no of keep alive probes */
extern Std_ReturnType TcpIpw_ChangeKeepAliveProbeCnt(
  const TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  uint8 Lu8_ParameterValue);

/* Function used to change no of keep alive interval */
extern Std_ReturnType TcpIpw_ChangeKeepAliveInterval(
  const TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  uint8 Lu8_ParameterValue);

/* Function used to change status of UDP checksum flag */
extern Std_ReturnType TcpIpw_ChangeUdpChecksumFlag(
  const TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  uint8 Lu8_ParameterValue);

/* Local function for AutoIp IP address assignment initialization */
extern Std_ReturnType TcpIpw_StrtAutoIpAddrAssignment(
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId,
  TcpIpw_IpAddrAssignment_Etyp Len_Type);

/* Local function for DHCP IP address assignment initialization */
extern Std_ReturnType TcpIpw_StrtDhcpIpAddrAssignment(
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId);

/* Local function for Static IP address assignment initialization */
extern Std_ReturnType TcpIpw_StrtStaticIpAddrAsgmnt(
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId,
  TcpIpw_IpAddrAssignment_Etyp Len_Type,
  const TcpIpw_SockAddr_Styp* Lpst_LocalIpAddrPtr,
  uint8 Lu8_Netmask,
  const TcpIpw_SockAddr_Styp* Lpst_DefaultRouterPtr);

/* Local function for releasing assigned DHCP IP address */
extern Std_ReturnType TcpIpw_ReleaseDhcpIpAddr(
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId);

/* Local function for releasing assigned AUTOIP IP address */
extern Std_ReturnType TcpIpw_ReleaseAutoIpAddr(
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId);

/* Function for releasing static IP address */
extern Std_ReturnType TcpIpw_ReleaseStaticIpAddr(
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId);

/* Function to check available input data */
extern void TcpIpw_ChkRxInputData(void);

/* Function for providing the timing to lwIP stack */
extern void TcpIpw_CheckTimeout(void);

/* Function for error handing of TCP connection */
extern void TcpIpw_TcpErrCbk(
  void *Lpv_Arg,
  err_t Ldt_Err);

/* Function for data received on TCP connection */
extern err_t TcpIpw_TcpRecvCbk(
  void* Lpv_Arg,
  struct tcp_pcb*  Lpst_TcpPcb,
  struct pbuf * Lpst_Pbuf,
  err_t  Ldt_Err);

/* Callback function in case of connection request successful event */
extern err_t TcpIpw_TcpConnectedCbk(
  void *Lpv_Arg,
  struct tcp_pcb *Lpst_TempPcb,
  err_t Ldt_Err);

/* Callback function in case of connection request accepted event */
extern err_t TcpIpw_TcpAcceptedCbk(
  void *Lpv_Arg,
  struct tcp_pcb *Lpst_NewPcb,
  err_t Ldt_Err);

/* Callback function in case of transmission successful event */
extern err_t TcpIpw_SentCbk(
  void * Lpv_Arg,
  struct tcp_pcb * Lpst_TcpPcb,
  u16_t Lu16_Length);

/* Call back function for Udp receive events */
extern void TcpIpw_UdpRecvCbk(
  void *Lpv_Arg,
  struct udp_pcb *Lpst_Pcb,
  struct pbuf *Lpst_Pbuf,
  const ip_addr_t *Lpst_Ipaddr,
  u16_t Lu16_Port);

/* Function for processing close operation on TCP socket */
extern Std_ReturnType TcpIpw_TcpClose(
  TcpIpw_SocketIdType Ldt_SocketId,
  boolean Lbl_Abort);

/* Function for processing close operation on UDP socket */
extern Std_ReturnType TcpIpw_UdpClose(TcpIpw_SocketIdType Ldt_SocketId);

/* Local function for set and reset IP address information */
extern void TcpIpw_UpdateIpAddrInfo(
  TcpIpw_IpAddrInfo_Styp * Lpst_IpAddrInfo,
  boolean Lbl_OperationType);

/* Function to notify the upper layer about the released IP address */
extern void TcpIpw_NotifyAbtReleasedIpAddr(void);

/* Function used to bind a TCP socket */
extern Std_ReturnType TcpIpw_RequestTcpBind(
  TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  uint16 Lu16_PortNo,
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId);

/* Function used to bind a UDP socket  */
extern Std_ReturnType TcpIpw_RequestUdpBind(
  TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  uint16 Lu16_PortNo,
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId);

/* Function for checking available IP address */
extern void TcpIpw_ChkIpAddr(void);

/* Function for processing active close operation */
extern void TcpIpw_ProcessActiveCls(void);

/* Function for processing Passive close operation */
extern void TcpIpw_ProcessPassiveCls(void);

/* Function for performing Pending Tx on any socket */
extern void TcpIpw_FindAndHandleTx(void);

/* Function used to find an unused buffer out of pool of buffers */
extern Std_ReturnType TcpIpw_FindIdleBuffer(
  uint8* Lpu8_BufferIdPtr);

/* Function used for transmission of data when direct data buffer is not provided by upper layer */
extern Std_ReturnType TcpIpw_IndirectTx(
  TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  TcpIpw_TcpTxBufInfo_Styp* Lpst_TcpBufInfo,
  uint16 Lu16_AvailableLength,
  TcpIpw_SocketIdType Ldt_SocketId);

/* Function used for transmission when direct data buffer is provided by upper layer */
extern Std_ReturnType TcpIpw_DirectTx(
  TcpIpw_SockInfo_Styp* Lpst_SockInfo,
  TcpIpw_TcpTxBufInfo_Styp* Lpst_TcpBufInfo,
  uint16 Lu16_AvailableLength,
  TcpIpw_SocketIdType Ldt_SocketId,
  const uint8* Lpu8_DataPtr);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* TCPIPW_INTERNAL_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
