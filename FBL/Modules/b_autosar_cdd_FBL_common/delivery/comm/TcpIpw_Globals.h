/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: TcpIpw_Globals.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : File provides external variable declaration for TcpIpw module **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef TCPIPW_GLOBALS_H
#define TCPIPW_GLOBALS_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* Header file inclusion for standard type definitions */
#include "Btl.h"
#include "TcpIpw_Types.h"
#include "TcpIpw_IntTypes.h"
#include "TcpIpw_Cfg.h"

/*******************************************************************************
**                              Global Variables                              **
*******************************************************************************/
#define BTL_START_SEC_CONST
#include "Btl_MemMap.h"

/* Data structure for holding call back functions */
extern const TcpIpw_UserCbk_Styp TcpIpw_Kst_CbkFunc;

#define BTL_STOP_SEC_CONST
#include "Btl_MemMap.h"

#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

/* Buffer for holding the DHCP host name */
extern char TcpIpw_Gau8_DhcpHostNameBuf[TCPIPW_DHCP_HOST_NAME_MAX_LENGTH+ TCPIPW_ONE];

/* Array for holding socket related information */
extern TcpIpw_SockInfo_Styp TcpIpw_Gast_SockIdConfigTab[TCPIPW_SOCKID_COUNT];

/* Array for holding TCP buffer location  */
extern TcpIpw_TcpTxBufInfo_Styp  TcpIpw_Gast_TcpBufConfigTab[TCPIPW_TCP_BUFFER_COUNT];

/* Array for holding IP address information */
extern TcpIpw_IpAddrInfo_Styp TcpIpw_Gast_IpAddrConfigTab[TCPIPW_IP_ADDR_ID_COUNT];

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"

#endif /* TCPIPW_GLOBALS_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
