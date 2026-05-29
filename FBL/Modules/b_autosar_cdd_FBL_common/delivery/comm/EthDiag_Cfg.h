/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: EthDiag_Cfg.h                                                 **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides pre-compile configuration for EthDiag                **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef ETHDIAG_CFG_H
#define ETHDIAG_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "EthDiag_Types.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define ETHDIAG_MAIN_FUNCTION_PERIOD                                       0x01U
#define ETHDIAG_ALIVECHECK_RESPONSE_TIMEOUT \
  (60000U/ETHDIAG_MAIN_FUNCTION_PERIOD)

#define ETHDIAG_MAX_TESTER_COUNT                                            0x01

#define ETHDIAG_MAX_LOGICAL_REQ_SIZE                                       1500U

#define ETHDIAG_PDUR_RX_PHY_PDU_ID                                          0x00
#define ETHDIAG_PDUR_RX_FUNC_PDU_ID                                         0x01
#define ETHDIAG_TX_PDU_ID                                                   0x00

#define ETHDIAG_UNICAST_ADDRESS_ID                     TCPIPW_UNICAST_IP_ADDR_ID

#define ETHDIAG_NETMASK_UNICAST                                     ETHDIAG_ZERO
#define ETHDIAG_SOCKET_ID_INVALID                          TCPIPW_SOCKID_INVALID
#define ETHDIAG_TCP_FIN_RECEIVED                         TCPIPW_TCP_FIN_RECEIVED
#define ETHDIAG_TCP_CLOSED                                     TCPIPW_TCP_CLOSED
#define ETHDIAG_TCP_RESET                                       TCPIPW_TCP_RESET
#define ETHDIAG_IPPROTO_TCP                                   TCPIPW_IPPROTO_TCP

#define ETHDIAG_TCP_CLOSE_ABORT                                          STD_OFF

#endif /* ETHDIAG_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
