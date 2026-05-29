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
**  PURPOSE   : This configuration information to the Can                     **
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
/* polyspace-begin MISRA2012:2.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CAN_CFG_H
#define CAN_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define CAN_MAX_RX_OBJECTS                                                    1U

/* Rx event FIFO 0 start address (F0SA) */
#define CAN_RX_EVENT_FIFO0_START_ADDR                            (uint32)0x080UL
/* Rx event FIFO 1 start address (F1SA) */
#define CAN_RX_EVENT_FIFO1_START_ADDR                            (uint32)0x0A0UL
/* Rx buffer start address (RBSA) */
#define CAN_RX_BUF_START_ADDR                                    (uint32)0x0C0UL
/* Rx FIFO 0 size */
#define CAN_RX_FIFO0_SIZE                                                  0x40U
/* Rx FIFO 0 size */
#define CAN_RX_FIFO0_THRESHOLD_SIZE                                        0x40U

/* Filter address for standard Id's */
#define CAN_SID_FILTER_ADDR                                     (uint32)0x1700UL
/* Filter address for extended Id's */
#define CAN_EID_FILTER_ADDR                                     (uint32)0x1300UL

/* Values for Set Global register for reject RTR and Non Match Frames */
#define CAN_GFC_REJT_RTR_NONMATCH                          (uint32)(0x0000003FU)


#define CAN_MAX_TX_OBJECTS                                                    2U

/* Tx event FIFO start address (EFSA) */
#define CAN_TX_EVENT_FIFO_START_ADDR                             (uint32)0x2A0UL
/* Tx buffer start address (TBSA) */
#define CAN_TX_BUF_START_ADDR1                                    (uint32)0x500UL
/* Tx dedicated buffer size */
#define CAN_TX_DED_BUFFER_SIZE                                             0x20U
/* Tx event FIFO size */
#define CAN_TX_EVENT_FIFO_SIZE                                             0x20U

/* Message RAM element size with FD support */
#define CAN_MSG_RAM_ELEMENT_SIZE_FD                                   (uint32)72
/* Message RAM element size with No FD support */
#define CAN_MSG_RAM_ELEMENT_SIZE_NFD                                  (uint32)16


/* Values used for FD mask and Extended Id Mask */
#define CAN_EXTENDED_ID_SET                                (uint32)(0x80000000U)
#define CAN_EXTENDED_ID_MASK                               (uint32)(0x1FFFFFFFU)
#define CAN_STANDARD_ID_MASK                               (uint32)(0x000007FFU)

#define CAN_ID_FD_ENABLE_SET                               (uint32)(0x40000000U)

#define CAN_TX_MSG_RTR                                                       29U
#define CAN_TX_MSG_XTD                                                       30U
#define CAN_TX_MSG_STD_ID                                                    18U
#define CAN_TX_MSG_FDF                                                       21U
#define CAN_TX_MSG_BRS                                                       20U
#define CAN_TX_MSG_DLC                                                       16U
#define CAN_TX_MSG_EFC                                                       23U
#define CAN_TX_MSG_MM                                                        24U

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
typedef struct
{
  /* Tx Buffer index number */
  uint8 CanTxBuffIndx;
  /* The CAN FD padding Value */
  uint8 CanFdPaddValue;
} Can_TxHandleInfo;

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
/* TX handle information */
extern Can_TxHandleInfo Can_GastTxHandleInfo[CAN_MAX_TX_OBJECTS];

#endif /* CAN_CFG_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:2.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
