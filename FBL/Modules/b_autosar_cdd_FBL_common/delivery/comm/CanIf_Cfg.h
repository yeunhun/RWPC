/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_Cfg.h                                                   **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This configuration information to the CanIf                   **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.10.0.0  07-Feb-2021   JYS          Redmine #24230                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef CANIF_CFG_H
#define CANIF_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "CanIf_Types.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#ifndef FBL_CANIF_CANFD_DISCRETE_DLC_SUPPORT
#define FBL_CANIF_CANFD_DISCRETE_DLC_SUPPORT                             STD_OFF
#endif

#define CANIF_RX_HRH_NUM                                                      1U

#define CANIF_RX_LPDU_NUM                                                     2U
#define CANIF_PDU_RX_PHY_PDU_ID                                             0x00
#define CANIF_PDU_RX_PHY_TARGET_ID                                          0x00
#define CANIF_PDU_RX_FUNC_PDU_ID                                            0x01
#define CANIF_PDU_RX_FUNC_TARGET_ID                                         0x01
#define CANIF_PDU_RX_PHY_PDU_DLC                                              8U
#define CANIF_PDU_RX_FUNC_PDU_DLC                                             8U

#define CANIF_TX_LPDU_NUM                                                     1U
#define CANIF_TX_HTH_ID                                                       0U
#define CANIF_PDU_TX_PHY_CONFIRM_PDU_ID                                     0x00
#define CANIF_PDU_TX_PHY_PDU_ID                                             0x00

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
extern const CanIf_Hrh CanIf_GaaHrh[CANIF_RX_HRH_NUM];

extern const CanIf_RxLpdu CanIf_GaaRxLpdu[CANIF_RX_LPDU_NUM];

extern const CanIf_TxLpdu CanIf_GaaTxLpdu[CANIF_TX_LPDU_NUM];

#endif /* CANIF_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
