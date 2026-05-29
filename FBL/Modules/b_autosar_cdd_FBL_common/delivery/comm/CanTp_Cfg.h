/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_Cfg.h                                                   **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This configuration information to the CanTp                   **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.23.1.0  06-Jun-2022   JSCHOI       Redmine #36032                        **
** 1.21.0    27-Oct-2021   JYS          Redmine #29277 #29449                 **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef CANTP_CFG_H
#define CANTP_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "CanTp_Types.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Number of Rx and Tx connection channels configured in CanTp */
#define CANTP_TOTAL_RX_TX_CHANNELS                                           (2)

/* Transmit frame padding byte */
#define CANTP_PADDING_BYTE                                               (0xAAU)

/* Main function Period */
#define CANTP_MAIN_FUNCTION_PERIOD                                   ((uint8)1U)

/* Maximum transmit SDU ID */
#define CANTP_MAX_TX_SDUID                                           ((uint16)1)

/* Maximum receive SDU ID */
#define CANTP_MAX_RX_SDUID                                           ((uint16)2)

/* Maximum Rx Indication PduId configured */
#define CANTP_MAX_INDIC_ID                                           ((uint16)2)

/* Maximum number of confirmation PduId */
#define CANTP_MAX_CONFIRM_ID                                         ((uint16)1)

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
extern const CanTp_RxNsduStatic CanTp_GaaRxSduStatic[];

extern uint8 CanTp_GaaRxDl[];

extern const CanTp_RxNSduDynamic CanTp_GaaRxSduDynamic[];

extern const CanTp_TxNsduStatic CanTp_GaaTxSduStatic[];

extern const CanTp_TxNSduDynamic CanTp_GaaTxSduDynamic[];

extern const CanTp_RxExtPdus CanTp_GaaRxExtPdus[];

extern const CanTp_ChannelType CanTp_GaaRxSduMap[];

extern CanTp_STminBs CanTp_GaaSTminBs[];

#endif /* CANTP_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
