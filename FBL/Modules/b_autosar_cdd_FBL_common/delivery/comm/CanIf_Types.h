/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_Types.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides data types required in CanIf                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     11-Sep-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Can_GeneralTypes.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define CANIF_TRUE                                                 ((uint8)0x01)
#define CANIF_FALSE                                                ((uint8)0x00)

#define CANIF_ZERO                                                        (0x00)
#define CANIF_ONE                                                         (0x01)
#define CANIF_TWO                                                         (0x02)
#define CANIF_SEVEN                                                       (0x07)
#define CANIF_EIGHT                                                       (0x08)
#define CANIF_NINE                                                        (0x09)
#define CANIF_THIRTYTWO                                                   (0x20)
#define CANIF_16                                                          (0x10)

#define CANIF_RX_DISABLED                                         ((uint8) 0x00)
#define CANIF_RX_ENABLED                                          ((uint8) 0x01)
#define CANIF_TX_DISABLED                                         ((uint8) 0x00)
#define CANIF_TX_ENABLED                                          ((uint8) 0x01)

#define CAN_CONTROLLER_ID                                                   (0U)

/* Tx status mask for controller */
#define CANIF_TX_STATUS_MASK                                       ((uint8)0x0f)
/* Status value to indicate that Queue is occupied */
#define CANIF_TXQUEUE_OCCUPIED                                     ((uint8)0x80)
/* Rx status mask for controller */
#define CANIF_RX_STATUS_MASK                                       ((uint8)0x0f)
/* Rx Validate wake up value for controller */
#define CANIF_RX_VALIDATE_WAKEUP                                   ((uint8)0x81)
/* Status value to indicate that Queue is free */
#define CANIF_INVALID_TXQUEUE                        ((CanIf_TxQueueType)0xffff)
/* to fill the controller id field in structure */
#define CANIF_INVALID_CONTROLLER                                   ((uint8)0xff)
/* to check whether the upper layer is correct or not */
#define CANIF_TX_INVALID_UL_USER                                   ((uint8)0xff)
/* to check whether the upper layer is correct or not */
#define CANIF_RX_INVALID_UL_USER                                   ((uint8)0xff)
/* to check whether the Dynamic CanId is configured or not */
#define CANIF_INVALID_DYNCANID                     ((CanIf_DynamicIdType)0xffff)
/* Mask value to get the upper layer Id */
#define CANIF_UL_MASK                                              ((uint8)0x0f)
/* Mask value to get the HTH type */
#define CANIF_HTHTYPE_MASK                                         ((uint8)0x0f)
/* Status Mask value to get the Partial Networking status */
#define CANIF_PN_STATUS_MASK                                       ((uint8)0x10)
/* both Partial network and TX confirmation indication */
#define CANIF_TX_CONFIRM_PN_ENABLED                                ((uint8)0x90)
/* TX confirm bit is MSB of Higher nibble, PN enabled bit is MSB of lower
 nibble */
#define CANIF_TX_CONFIRM_STATUS_MASK                               ((uint8)0x80)
/* Status mask for getting the Notification value */
#define CANIF_NOTIFY_STATUS_MASK                                   ((uint8)0x80)
/* Status mask for getting the Rx Notification value */
#define CANIF_RX_NOTIFY_STATUS_MASK                                ((uint8)0x10)
/* Status mask for getting the Rx Data value */
#define CANIF_RX_DATA_STATUS_MASK                                  ((uint8)0x20)
/* Status mask for IDSM report target PDU */
#define CANIF_RX_IDSM_REPORT_MASK                                  ((uint8)0x40)
/* Status mask for getting the Dlc value */
#define CANIF_RX_DLC_STATUS_MASK                                   ((uint8)0x0f)
/* Status mask for getting the queue status */
#define CANIF_QUEUE_STATUS_MASK                                    ((uint8)0xF0)
/* mask for getting the Tx Status of the controller */
#define CANIF_TX_ENABLED_MASK                                      ((uint8)0x0f)
/* mask for getting the Tx confirmation Status of the controller */
#define CANIF_TX_CONFIRMED                                         ((uint8)0x80)
/*mask for getting battery voltage status for blocking transmit request */
#define CANIF_TX_BAT_STATUS_MASK                                   ((uint8)0x20)
/* Mask for Standard CAN ID */
#define CANIF_STANDARD_ID_MASK                                  ((uint16)0x07FF)
/* Mask for Extended CAN ID */
#define CANIF_EXTENDED_ID_MASK                              ((uint32)0x1FFFFFFF)
/* Mask for CAN Frame Type */
#define CANIF_FRAME_TYPE_MASK                               ((uint32)0xC0000000)
/* IP Table of each Controller */
#define CANIF_IPTABLE_COUNT                                         ((uint8)0x8)
/* Mask for First CAN ID bit*/
#define CANIF_STANDARD_ID_FIRSTBIT_MASK                         ((uint16)0x0700)


#define CANIF_RX_BASIC_CAN_STD                                     ((uint8)0x00)
#define CANIF_RX_BASIC_CAN_EXT                                     ((uint8)0x01)
#define CANIF_RX_BASIC_CAN_MIXED                                   ((uint8)0x02)
#define CANIF_RX_FULL_CAN_STD                                      ((uint8)0x03)
#define CANIF_RX_FULL_CAN_EXT                                      ((uint8)0x04)
#define CANIF_RX_FULL_CAN_MIXED                                    ((uint8)0x05)


#define CANIF_STANDARD_CANID_VALUE                               ((uint32)0x7FF)
#define CANIF_EXTENDED_CANID_VALUE                         ((uint32)0x9FFFFFFFU)


#define CANIF_RANGE_SUCCESS                                        ((uint8)0x80)
#define CANIF_FAILURE                                              ((uint8)0x00)


#define CANIF_BASIC_CAN                                            ((uint8)0x00)
#define CANIF_FULL_CAN                                             ((uint8)0x01)

#define CANIF_FILTER_METHOD_BASICCAN_STANDARD                      ((uint8)0x00)
#define CANIF_FILTER_METHOD_BASICCAN_EXTENDED                      ((uint8)0x01)
#define CANIF_FILTER_METHOD_BASICCAN_MIXED                         ((uint8)0x02)
#define CANIF_FILTER_METHOD_FULLCAN_STANDARD                       ((uint8)0x03)
#define CANIF_FILTER_METHOD_FULLCAN_EXTENDED                       ((uint8)0x04)
#define CANIF_FILTER_METHOD_FULLCAN_MIXED                          ((uint8)0x05)

/*******************************************************************************
**                              Type Definition                               **
*******************************************************************************/
typedef uint16 CanIf_TxQueueType;
typedef uint16 CanIf_DynamicIdType;

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
/* State transitions that are used by the function CanIf_SetControllerMode */
typedef enum
{
  CANIF_CS_UNINIT = 0,
  CANIF_CS_SLEEP,
  CANIF_CS_STARTED,
  CANIF_CS_STOPPED
} CanIf_ControllerModeType;

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
/* Structure for HRH */
typedef struct
{
  PduIdType ddRxLpduIndex;        /* Pointer to first range or list kind of
                                    Rx L-PDU(s) structure */
  PduIdType ddNoOfRxLpdusRange;   /* Number of range kind of Rx L-PDU(s) */
  PduIdType ddNoOfRxLpdusList;    /* Number of list kind of Rx L-PDU(s) */
  uint8 ucFilterMethod;           /* Filter Method : 
                                    0x00: -> BasicCAN WITH STANDARD
                                    0x01: -> BASICCAN WITH EXTENDED
                                    0x02: -> BASICCAN WITH MIXED
                                    0x03: -> FULLCAN WITH STANDARD
                                    0x04: -> FULLCAN WITH EXTENDED
                                    0x05: -> FULLCAN WITH MIXED */
} CanIf_Hrh;

typedef struct
{
  Can_IdType ddCanIdLl;  /* CAN-ID lower limit (Range), / actual ID(List) */
  Can_IdType ddCanIdUl;  /* CAN-ID upper limit */
  PduIdType ddRxPduId;  
  PduIdType ddTargetId;  /* TargetPduId */
  uint8 ucDlc;  /* Statically configured DLC */
} CanIf_RxLpdu;

typedef struct
{
  Can_IdType ddCanId;                     /* CAN-ID */
  Can_HwHandleType ddHthIdorBufferId;     /* Statically configured Hth Id */
  PduIdType ddTxConfirmPduId;             /* Handle Id - for confirmation */
  PduIdType ddTxPduId;                    /* Handle Id - CanTxPduId */
} CanIf_TxLpdu;

#endif /* CANIF_TYPES_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
