/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: TcpIpw_Types.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides data types definition to the user module             **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef TCPIPW_TYPES_H
#define TCPIPW_TYPES_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "ComStack_Types.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Domain type for IPv4 protocol */
#define TCPIPW_AF_INET                                             (uint16)0x02u
#define TCPIPW_NO_WORDS_FOR_IP_ADDR                                           1u

/*******************************************************************************
**                              Type Definition                               **
*******************************************************************************/
/*
* Data type for domain information
*/
typedef uint16 TcpIpw_DomainType;

/*
* Data type for parameter identification
*/
typedef uint8 TcpIpw_ParamIdType;

/*
* Data type for IP address identification
*/
typedef uint8 TcpIpw_LocalAddrIdType;

/*
* Data type for socket identification
*/
typedef uint8 TcpIpw_SocketIdType;

/*
* Data type for wild card IP address
*/
typedef uint32 TcpIpw_IpAddrWildcardType;

/*
* Data type for wild card port number
*/
typedef uint16 TcpIpw_PortWildcardType;

/* Data type for configuration information */
typedef struct
{
  uint32 dummy;
}TcpIpw_Config_Styp;

/*
* Data type for protocol information
*/
typedef enum
{
  TCPIPW_IPPROTO_TCP = 0x06u,
  TCPIPW_IPPROTO_UDP = 0x11u,
  TCPIPW_IPPROTO_INVALID = 0xFFu
}TcpIpw_Protocol_Etyp;

/*
* Data type for IP address assignment type
*/
typedef enum
{
  TCPIPW_IPADDR_ASSIGNMENT_STATIC = 0x01u,
  TCPIPW_IPADDR_ASSIGNMENT_DHCP = 0x03u,
  TCPIPW_IPADDR_ASSIGNMENT_LINKLOCAL = 0x04u,
  TCPIPW_IPADDR_ASSIGNMENT_INVALID = 0x05u
}TcpIpw_IpAddrAssignment_Etyp;

/*
* Data type for IP address state type
*/
typedef enum
{
  TCPIPW_IPADDR_STATE_ASSIGNED = 0x01u,
  TCPIPW_IPADDR_STATE_REQUESTED = 0x02u,
  TCPIPW_IPADDR_STATE_UNASSIGNED = 0x03u
}TcpIpw_IpAddrState_Etyp;

/*
* Data type for Event type
*/
typedef enum
{
  TCPIPW_TCP_RESET = 0x01u,
  TCPIPW_TCP_CLOSED = 0x02u,
  TCPIPW_TCP_FIN_RECEIVED = 0x03u,
  TCPIPW_UDP_CLOSED = 0x04u
}TcpIpw_Event_Etyp;

/*
* Data type for Socket Address
*/
typedef struct
{
  TcpIpw_DomainType dt_Domain;
  uint16 u16_Port;
  uint32 au32_Addr[TCPIPW_NO_WORDS_FOR_IP_ADDR];
}TcpIpw_SockAddr_Styp;

/*
* Type definition for the callback function that are to be called for providing
* notification to the upper layer
*/
typedef struct
{
  /* Common callback notification  */

  /* Function pointer for notification of IP address change */
  void(*pt_LocalIpAddrAssignmentChg)(TcpIpw_LocalAddrIdType Ldt_IpAddrId, TcpIpw_IpAddrState_Etyp Len_State);

  /* Function pointer for notification of event occuring on TCP or UDP socket */
  void(*pt_TcpIpEvent)(TcpIpw_SocketIdType Ldt_SocketId, TcpIpw_Event_Etyp Len_Event);

  /* TCP socket Callbacks */
  /* Function pointer for notification of connected TCP socket */
  void(*pt_TcpConnected)(TcpIpw_SocketIdType Ldt_SocketId);

  /* Function pointer for notification of Accepted TCP socket */
  Std_ReturnType (*pt_TcpAccepted)(TcpIpw_SocketIdType Ldt_SocketId, TcpIpw_SocketIdType Ldt_SocketIdConnected,
    const TcpIpw_SockAddr_Styp* Lpst_RemoteAddrPtr);

  /* Function pointer for indication of received data over TCP socket */
  BufReq_ReturnType (*pt_TcpIpwTcpStartOfReception)(TcpIpw_SocketIdType Ldt_SocketId, const uint8* Lpu8_DataPtr,
    uint16 Lu16_DataLength, uint16  Lu16_TotalDataLength, uint16* Lpu16_BufferSizePtr);

  /* Function pointer for copying received data to upper module buffer */
  BufReq_ReturnType (*pt_TcpIpwTcpCopyRxData)(TcpIpw_SocketIdType Ldt_SocketId, const uint8* Lpu8_DataPtr,
    uint16 Lu16_Length, uint16* Lpu16_BufferSizePtr);

  /* Function pointer for notification of Received data on TCP socket */
  void (*pt_TcpIpwTcpRxIndication)(TcpIpw_SocketIdType Ldt_SocketId, Std_ReturnType Ldt_Result);

  /* Function pointer for copying requested data to TCPIPW TX buffer */
  BufReq_ReturnType (*pt_TcpIpwTcpCopyTxData)( TcpIpw_SocketIdType Ldt_SocketId, uint8* Lpu8_BufPtr,
    uint16 Lu16_BufLength);

  /* Function pointer for notification of successful transmission over TCP socket */
  void (*pt_TcpIpwTcpTxConfirmation)(TcpIpw_SocketIdType Ldt_SocketId, Std_ReturnType Ldt_Result);

  /* UDP callbacks */

  /* Function pointer for notification of received data over UDP socket */
  void (*pt_TcpIpwUdpRxIndication)(TcpIpw_SocketIdType Ldt_SocketId,
    const TcpIpw_SockAddr_Styp*  Lpst_RemoteAddrPtr, uint8* Lpu8_BufPtr, uint16 Lu16_Length);

 /* Function pointer for confirmation of the transmission of requested data on UDP socket */
  void (*pt_TcpIpwUdpTxConfirmation)(TcpIpw_SocketIdType Ldt_SocketId, Std_ReturnType Ldt_Result);

}TcpIpw_UserCbk_Styp;

#endif /* TCPIPW_TYPES_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
