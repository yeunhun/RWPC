/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_Cfg.c                                                   **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides CanTp configuration                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.23.1.0  06-Jun-2022   JSCHOI       Redmine #36032                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "CanTp_Cfg.h"

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_CONST
#include "Btl_MemMap.h"

const CanTp_RxNsduStatic CanTp_GaaRxSduStatic[] =
{
  /* Diag Msg TP Phys Req */
  {
    /* ddChannelId */
    1,

    /* usRxSduLength */
    0x0001,

    /* ucTaType */
    #if (FBL_CAN_TYPE == FBL_CAN_FD)
    CANTP_CANFD_PHYSICAL_ADDRESS,
    #else
    CANTP_PHYSICAL_ADDRESS,
    #endif

    /* blRxPaddingActivation */
    CANTP_TRUE
  },
  /* Diag Msg TP Func */
  {
    /* ddChannelId */
    0,

    /* usRxSduLength */
    0x0001,

    /* ucTaType */
    #if (FBL_CAN_TYPE == FBL_CAN_FD)
    CANTP_CANFD_FUNCTIONAL_ADDRESS,
    #else
    CANTP_FUNCTIONAL_ADDRESS,
    #endif

    /* blRxPaddingActivation */
    CANTP_TRUE
  },
};

const CanTp_RxNSduDynamic CanTp_GaaRxSduDynamic[] =
{
  {
    /* ddUpTargetPduId */
    0x0000,

    /* ddLoTxFcTargetPduId */
    0x0000,

    /* usNarTimeoutValue */
    0x00C8 * 25,

    /* usNbrTimeoutValue */
    0x0000,

    /* usNcrTimeoutValue */
    0x00C8 * 25,

    /* usRxWftMax */
    0x0000
  },
  {
    /* ddUpTargetPduId */
    0x0001,

    /* ddLoTxFcTargetPduId */
    0x00FF,

    /* usNarTimeoutValue */
    0x00C8 * 25,

    /* usNbrTimeoutValue */
    0x0000,

    /* usNcrTimeoutValue */
    0x00C8 * 25,

    /* usRxWftMax */
    0x0000
  },
};

const CanTp_RxExtPdus CanTp_GaaRxExtPdus[] =
{
  /* RxPDU 0 - 0 */
  {
    /* ddNoOfPdusOrSduId */
    0x00,

    /* ddRxNSaOrNAeSduMapIndex */
    CANTP_INVALID,

    /* ucAddressingMode */
    FBL_CAN_DIAG_MSG_PHY_REQ_ADDR_FORMAT
  },
  /* RxPDU 1 - 1 */
  {
    /* ddNoOfPdusOrSduId */
    0x01,

    /* ddRxNSaOrNAeSduMapIndex */
    CANTP_INVALID,

    /* ucAddressingMode */
    FBL_CAN_DIAG_MSG_PHY_RES_ADDR_FORMAT
  },
};

const CanTp_ChannelType CanTp_GaaRxSduMap[] =
{
  /* Index 0 */
  0x01,
};

const CanTp_TxNsduStatic CanTp_GaaTxSduStatic[] =
{
  {
    /* ddChannelId */
    1,

    /* usTxSduLength */
    0x0001,

    /* ucTaType */
    CANTP_PHYSICAL_ADDRESS,

    /* blTxPaddingActivation */
    CANTP_TRUE,

    /* ucTxSduMaxLength */
    0x08
  },
};

const CanTp_TxNSduDynamic CanTp_GaaTxSduDynamic[] =
{
  /* Diag Msg TP Phys Res */
  {
    /* ddUpConfirmationSduId */
    0x0000,

    /* ddLoTargetPduId */
    0x0000,

    /* usNasTimeoutValue */
    0x00C8 * 25,

    /* usNbsTimeoutValue */
    0x00C8 * 25,

    /* usNcsTimeoutValue */
    0x00C8 * 25,
  },
};

#define BTL_STOP_SEC_CONST
#include "Btl_MemMap.h"

#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

CanTp_STminBs CanTp_GaaSTminBs[] =
{
  {
    /* ucBlockSize */
    0x00U,

    /* ucSTMin */
    FBL_CAN_DIAG_MSG_PHY_REQ_STMIN
  },
  {
    /* ucBlockSize */
    0x00U,

    /* ucSTMin */
    0xFF
  }
};

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
