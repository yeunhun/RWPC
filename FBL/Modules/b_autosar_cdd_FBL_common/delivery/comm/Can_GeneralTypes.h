/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Can_GeneralTypes.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Type Definition for CAN module                                **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef CAN_GENERALTYPES_H
#define CAN_GENERALTYPES_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Std_Types.h"
#include "ComStack_Types.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
/* Types for return values of CAN Driver APIs */
typedef enum
{
  CAN_OK,        /* success */
  CAN_NOT_OK,    /* error occurred or wakeup occurred during sleep transition */
  CAN_BUSY       /* transmit request could not be processed because no transmit 
                    object was available */
} Can_ReturnType;

/* CAN state transition data type */
typedef enum
{
  CAN_T_START,    /* CAN controller transition value to request state STARTED */
  CAN_T_STOP,     /* CAN controller transition value to request state STOPPED */
  CAN_T_SLEEP,    /* CAN controller transition value to request state SLEEP */
  CAN_T_WAKEUP    /* CAN controller transition value to request state STOPPED
                     from state SLEEP  */
} Can_StateTransitionType;

/* CAN Transceiver Network Mode data type */
typedef enum
{
  CANTRCV_TRCVMODE_NORMAL,
  CANTRCV_TRCVMODE_SLEEP,
  CANTRCV_TRCVMODE_STANDBY
} CanTrcv_TrcvModeType;

/* CAN Transceiver Wakeup Mode data type */
typedef enum
{
  CANTRCV_WUMODE_ENABLE,
  CANTRCV_WUMODE_DISABLE,
  CANTRCV_WUMODE_CLEAR
} CanTrcv_TrcvWakeupModeType;

/* CAN Transceiver Wake up Reason type */
typedef enum
{
  CANTRCV_WU_ERROR,
  CANTRCV_WU_NOT_SUPPORTED,
  CANTRCV_WU_BY_BUS,
  CANTRCV_WU_INTERNALLY,
  CANTRCV_WU_RESET,
  CANTRCV_WU_POWER_ON,
  CANTRCV_WU_BY_PIN,
  CANTRCV_WU_BY_SYSERR
} CanTrcv_TrcvWakeupReasonType;

/*******************************************************************************
**                              Type Definition                               **
*******************************************************************************/
/* CAN id Type Mixed is supported */
typedef uint32 Can_IdType;

/* Maximum of hardware objects in the CAN hardware unit is more than 256 */
typedef uint16 Can_HwHandleType;

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
/* Hardware Object Handle Type */
typedef struct
{
  Can_IdType CanId;         /* Standard/Extended CAN ID of CAN L-PDU */
  Can_HwHandleType Hoh;     /* ID of the corresponding Hardware Object */
  uint8 ControllerId;       /* ControllerId provided by CanIf */
} Can_HwType;

/* CAN protocol data unit type. Used to provide ID, DLC and SDU from
   CAN Interface to CAN driver */
typedef struct
{
  PduIdType swPduHandle;    /* SW Handle that will identify the request in
                               the confirmation callback function. */
  uint8 length;             /* DLC */
  Can_IdType id;            /* Identifier of L-PDU */
  uint8 *sdu;               /* Pointer to L-SDU */
} Can_PduType;

#endif /* CAN_GENERALTYPES_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
