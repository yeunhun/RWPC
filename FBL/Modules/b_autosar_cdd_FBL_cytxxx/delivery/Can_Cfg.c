/*******************************************************************************
**                                                                            **
**  (C) 2020 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Can_Cfg.c                                                     **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides Can configuration                                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision    Date          By           Description                         **
********************************************************************************
** 1.1.0.0     23-Feb-2021   JHLim        Redmine #23964                      **
** 1.0.0       10-April-2020 JaeHyun      Initial version                     **
*******************************************************************************/

/*******************************************************************************
**               PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)               **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Can_Cfg.h"

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

/* TX handle information */
Can_TxHandleInfo Can_GastTxHandleInfo[CAN_MAX_TX_OBJECTS] =
{
  {
    /* CanTxBuffIndx */
    0U,

    /* CanFdPaddValue */
    0xAAU,
  },
  {
    /* CanTxBuffIndx */
    1U,

    /* CanFdPaddValue */
    0xAAU,
  },
};

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
