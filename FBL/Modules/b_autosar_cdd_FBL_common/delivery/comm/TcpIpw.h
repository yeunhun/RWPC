/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: TcpIpw.h                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides the function declaration                   **
**              for the TcpIp wrapper APIS                                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef TCPIPW_H
#define TCPIPW_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* Header file inclusion for standard type definitions */
#include "Btl.h"
#include "TcpIpw_Types.h"
#include "TcpIpw_Cfg.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Priority parameter for TCP's PCB */
#define TCPIPW_PARAMID_TCPPRIO                                             0x00u

/* Time to live parameter for TCP PCB */
#define TCPIPW_PARAMID_TTL                                                 0x01u

/* Type of service parameter for TCP PCB */
#define TCPIPW_PARAMID_TOS                                                 0x02u

/* Nagle algorithm parameter for TCP PCB */
#define TCPIPW_PARAMID_TCP_NAGLE                                           0x03u

/* Parameter for initial time wait before sending keepalive request */
#define TCPIPW_PARAMID_TCP_KEEPALIVE_TIME                                  0x04u

/* Parameter for maximum number of keepalive probes */
#define TCPIPW_PARAMID_TCP_KEEPALIVE_PROBES_MAX                            0x05u

/* Parameter for time interval between two keepalive probes */
#define TCPIPW_PARAMID_TCP_KEEPALIVE_INTERVAL                              0x06u

/* Parameter for enabling and disabling checksum for UDP */
#define TCPIPW_PARAMID_UDP_FLAGS_NOCHKSUM                                  0x07u

/* Enable nagle algorithm */
#define TCPIPW_ENABLE_NAGLE_ALGORITHM                                      0x09u

/* Disable nagle algorithm */
#define TCPIPW_DISABLE_NAGLE_ALGORITHM                                     0x0Au

/* enable udp_checksum */
#define TCPIPW_UDP_CHECKSUM_ENABLE                                         0x0Bu

/* Disable udp_checksum */
#define TCPIPW_UDP_CHECKSUM_DISABLE                                        0x0Cu

/* Invalid Socket identifier */
#define TCPIPW_SOCKID_INVALID                         (TcpIpw_SocketIdType)0xFFU

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/* External function definition for TcpIpw_Init() function */
extern void TcpIpw_Init(const TcpIpw_Config_Styp* Lpst_ConfigPtr);

/* External function definition for TcpIpw_GetSocket() function */
extern Std_ReturnType TcpIpw_GetSocket(
  TcpIpw_DomainType Ldt_Domain,
  TcpIpw_Protocol_Etyp Len_Protocol,
  TcpIpw_SocketIdType* Lpdt_SocketIdPtr);

/* External function definition for TcpIpw_Open() function */
extern Std_ReturnType TcpIpw_Open(TcpIpw_SocketIdType Ldt_SocketId);

/* External function definition for TcpIpw_ChangeParameter() function */
extern Std_ReturnType TcpIpw_ChangeParameter(
  TcpIpw_SocketIdType Ldt_SocketId,
  TcpIpw_ParamIdType Ldt_ParameterId,
  const uint8* Lpu8_ParameterValue);
  
/* External function definition for TcpIpw_RequestIpAddrAssignment() function */
extern Std_ReturnType TcpIpw_RequestIpAddrAssignment(
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId,
  TcpIpw_IpAddrAssignment_Etyp Len_Type,
  const TcpIpw_SockAddr_Styp* Lpst_LocalIpAddrPtr,
  uint8 Lu8_Netmask,
  const TcpIpw_SockAddr_Styp* Lpst_DefaultRouterPtr);
  
/* External function definition for TcpIpw_ReleaseIpAddrAssignment() function */
extern Std_ReturnType TcpIpw_ReleaseIpAddrAssignment(
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId);
  
/* External function definition for TcpIpw_GetLocalIpAddr() function */
extern Std_ReturnType TcpIpw_GetLocalIpAddr(
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId,
  TcpIpw_SockAddr_Styp* Lpst_SockAddrPtr,
  uint8* Lpu8_NetmaskPtr,
  TcpIpw_SockAddr_Styp* Lpst_DefaultRouterPtr);
  
/* External function definition for TcpIpw_DhcpReadOption() function */
extern Std_ReturnType TcpIpw_DhcpReadOption(
  TcpIpw_LocalAddrIdType Ldt_LocalIpAddrId,
  uint8 Lu8_Option,
  uint8* Lpu8_DataLength,
  uint8* Lpu8_DataPtr);

/* External function definition for TcpIpw_DhcpWriteOption() function */
extern Std_ReturnType TcpIpw_DhcpWriteOption(
  TcpIpw_LocalAddrIdType Ldt_LocalIpAddrId,
  uint8 Lu8_Option,
  uint8 Lu8_DataLength,
  const uint8* Lpu8_DataPtr);

/* External function definition for TcpIpw_Bind() function */
extern Std_ReturnType TcpIpw_Bind(
  TcpIpw_SocketIdType Ldt_SocketId,
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId,
  const uint16* Lpu16_PortPtr);

/* External function definition for TcpIpw_TcpConnect() function */
extern Std_ReturnType TcpIpw_TcpConnect(
  TcpIpw_SocketIdType Ldt_SocketId,
  const TcpIpw_SockAddr_Styp* Lpst_RemoteAddrPtr);

/* External function definition for TcpIpw_TcpListen() function */
extern Std_ReturnType TcpIpw_TcpListen(
  TcpIpw_SocketIdType Ldt_SocketId,
  uint16 Lu16_MaxChannels);

/* External function definition for TcpIpw_MainFunction() function */
extern void TcpIpw_MainFunction(void);

/* External function definition for TcpIpw_GetRemoteIpAddr() function */
extern Std_ReturnType TcpIpw_GetRemoteIpAddr(
  TcpIpw_SocketIdType Ldt_SocketId,
  TcpIpw_SockAddr_Styp* Lpst_RemoteSockInfo);
  
/* External function definition for TcpIpw_UdpTransmit() function */
extern Std_ReturnType TcpIpw_UdpTransmit(
  TcpIpw_SocketIdType Ldt_SocketId,
  const uint8* Lpu8_DataPtr,
  const TcpIpw_SockAddr_Styp* Lpst_RemoteAddrPtr,
  uint16 Lu16_TotalLength);

/* External function definition for TcpIpw_TcpTransmit() function */
extern Std_ReturnType TcpIpw_TcpTransmit(
  TcpIpw_SocketIdType Ldt_SocketId,
  const uint8* Lpu8_DataPtr,
  uint16 Lu16_AvailableLength,
  boolean Lbl_ForceRetrieve);

/* External function definition for TcpIpw_TcpReceived() function */
extern Std_ReturnType TcpIpw_TcpReceived(
  TcpIpw_SocketIdType Ldt_SocketId,
  uint32 Lu32_Length);

/* External function definition for TcpIpw_Close() function */
extern Std_ReturnType TcpIpw_Close(
  TcpIpw_SocketIdType Ldt_SocketId,
  boolean Lbl_Abort);

/* External function definition for TcpIpw_GetLocalPhysAddr() function */
extern Std_ReturnType TcpIpw_GetLocalPhysAddr(
  TcpIpw_LocalAddrIdType Ldt_LocalAddrId,
  uint8* Lpu8_PhysAddrPtr);

/* External function definition for TcpIpw_SysNow() function */
extern uint32 TcpIpw_SysNow(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* TCPIPW_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
