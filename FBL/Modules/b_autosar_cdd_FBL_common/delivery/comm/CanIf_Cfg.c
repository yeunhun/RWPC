/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_Cfg.c                                                   **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides CanIf configuration                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "CanIf_Cfg.h"

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_CONST
#include "Btl_MemMap.h"

/* Structure for HRH */
const CanIf_Hrh CanIf_GaaHrh[CANIF_RX_HRH_NUM] =
{
  /* HRH 0 */
  {
    /* ddRxLpduIndex */
    0x0000,

    /* ddNoOfRxLpdusRange */
    0x00,

    /* ddNoOfRxLpdusList */
    0x02,

    /* ucFilterMethod */
    #if ((FBL_CAN_DIAG_MSG_PHY_REQ_ADDR_FORMAT == FBL_CAN_ADDR_STANDARD) || \
         (FBL_CAN_DIAG_MSG_FUNC_REQ_ADDR_FORMAT == FBL_CAN_ADDR_STANDARD))
    CANIF_FILTER_METHOD_BASICCAN_STANDARD
    #else
    CANIF_FILTER_METHOD_BASICCAN_EXTENDED
    #endif
  },
};

const CanIf_RxLpdu CanIf_GaaRxLpdu[CANIF_RX_LPDU_NUM] =
{
  /* RX-LIST-RANGE 0 */
  {
    /* ddCanIdLl */
    #if (FBL_CAN_DIAG_MSG_PHY_REQ_ADDR_FORMAT == FBL_CAN_ADDR_STANDARD)
    FBL_CAN_DIAG_MSG_PHY_REQ_ID,
    #else
    /* Set message ID type as Extended */
    (FBL_CAN_DIAG_MSG_PHY_REQ_ID + 0x80000000U),
    #endif

    /* ddCanIdUl */
    0,

    /* ddRxPduId */
    CANIF_PDU_RX_PHY_PDU_ID,

    /* ddTargetId */
    CANIF_PDU_RX_PHY_TARGET_ID,

    /* ucDlc */
    CANIF_PDU_RX_PHY_PDU_DLC,
  },
  /* RX-LIST-RANGE 1 */
  {
    /* ddCanIdLl */
    #if (FBL_CAN_DIAG_MSG_FUNC_REQ_ADDR_FORMAT == FBL_CAN_ADDR_STANDARD)
    FBL_CAN_DIAG_MSG_FUNC_REQ_ID,
    #else
    /* Set message ID type as Extended */
    (FBL_CAN_DIAG_MSG_FUNC_REQ_ID + 0x80000000U),
    #endif

    /* ddCanIdUl */
    0,

    /* ddRxPduId */
    CANIF_PDU_RX_FUNC_PDU_ID,

    /* ddTargetId */
    CANIF_PDU_RX_FUNC_TARGET_ID,

    /* ucDlc */
    CANIF_PDU_RX_FUNC_PDU_DLC,
  },
};

const CanIf_TxLpdu CanIf_GaaTxLpdu[CANIF_TX_LPDU_NUM] =
{
  /* TX LPDU - Diag Msg TP Phys Res */
  {
    /* ddCanId */
    #if (FBL_CAN_DIAG_MSG_PHY_RES_ADDR_FORMAT == FBL_CAN_ADDR_STANDARD)
    FBL_CAN_DIAG_MSG_PHY_RES_ID,
    #else
    /* Set message ID type as Extended */
    (FBL_CAN_DIAG_MSG_PHY_RES_ID + 0x80000000U),
    #endif

    /* ddHthIdorBufferId */
    CANIF_TX_HTH_ID,

    /* ddTxConfirmPduId */
    CANIF_PDU_TX_PHY_CONFIRM_PDU_ID,

    /* ddTxPduId */
    CANIF_PDU_TX_PHY_PDU_ID,
  },
};

#define BTL_STOP_SEC_CONST
#include "Btl_MemMap.h"

#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
