/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Eth_Cfg.h                                                     **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides internal functions required in Eth driver            **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.2.0     10-May-2021   JHLim        #28951                                **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef ETH_CFG_H
#define ETH_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define ETH_RTX_BUFFER_SIZE                                                1536U
#define ETH_MAX_RX_BUFFERS                                                   16U
#define ETH_MAX_TX_BUFFERS                                                    8U
/* Speed 0->10mbps 1->100mbps */
#define ETH_SPEED                                                             1U
/* Duplex Mode: 0=Half Duplex, 1=Full duplex */
#define ETH_DUPLEX_MODE                                                       1U

#endif /* ETH_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
