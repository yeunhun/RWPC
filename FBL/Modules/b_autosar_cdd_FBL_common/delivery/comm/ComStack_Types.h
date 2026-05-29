/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComStack_Types.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provision for Communication Stack dependent types             **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Std_Types.h"
#include "ComStack_Cfg.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* General return codes for NotifResultType */
#define NTFRSLT_OK                                         (NotifResultType)0x00
#define NTFRSLT_E_NOT_OK                                   (NotifResultType)0x01
#define NTFRSLT_E_TIMEOUT_A                                (NotifResultType)0x02
#define NTFRSLT_E_TIMEOUT_BS                               (NotifResultType)0x03
#define NTFRSLT_E_TIMEOUT_CR                               (NotifResultType)0x04
#define NTFRSLT_E_WRONG_SN                                 (NotifResultType)0x05
#define NTFRSLT_E_INVALID_FS                               (NotifResultType)0x06
#define NTFRSLT_E_UNEXP_PDU                                (NotifResultType)0x07
#define NTFRSLT_E_WFT_OVRN                                 (NotifResultType)0x08
#define NTFRSLT_E_ABORT                                    (NotifResultType)0x09
#define NTFRSLT_E_NO_BUFFER                                (NotifResultType)0x0A
#define NTFRSLT_E_CANCELATION_OK                           (NotifResultType)0x0B
#define NTFRSLT_E_CANCELATION_NOT_OK                       (NotifResultType)0x0C
#define NTFRSLT_PARAMETER_OK                               (NotifResultType)0x0D
#define NTFRSLT_E_PARAMETER_NOT_OK                         (NotifResultType)0x0E
#define NTFRSLT_E_RX_ON                                    (NotifResultType)0x0F
#define NTFRSLT_E_VALUE_NOT_OK                             (NotifResultType)0x10

/* General return codes for BusTrcvErrorType */
#define BUSTRCV_OK                                                          0x00
#define BUSTRCV_E_ERROR                                                     0x01

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/

/*******************************************************************************
**                              Type Definition                               **
*******************************************************************************/
/* Variables of the type PNCHandleType shall be used to store
  the identifier of a partial network cluster. */
typedef uint8        PNCHandleType;
/* Variables of the type NotifResultType shall be used to store
  the result status of a notification (confirmation or indication). */
typedef uint8        NotifResultType;
/* Variables of the type BusTrcvErrorType shall be used to return
  the bus status evaluated by a transceiver. */
typedef uint8        BusTrcvErrorType;
/* Variables of the type NetworkHandleType shall be used to store
  the identifier of a communication channel. */
typedef uint8        NetworkHandleType;

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/

/* Variables of this type shall be used to store the basic information
  about a PDU of any type, namely a pointer variable pointing to its SDU (payload)
  and the corresponding length of the SDU in bytes. */
/* Basic information about a PDU of any type */
typedef struct STag_PduInfoType
{
  uint8* SduDataPtr;
  PduLengthType SduLength;
} PduInfoType;

/* Variables of this type shall be used to store the state of TP buffer. */
/* Store the state of TP buffer */
typedef enum
{
  TP_DATACONF,
  TP_DATARETRY,
  TP_CONFPENDING,
  TP_NORETRY
} TpDataStateType;

/* Variables of this type shall be used to store the information
  about Tp buffer handling. */
/* Store the information about Tp buffer handling */

typedef struct STag_RetryInfoType
{
  TpDataStateType TpDataState;
  PduLengthType TxTpDataCnt;
} RetryInfoType;

/* Variables of this type specify the parameter to which the value
  has to be changed (BS or STmin). */
/* parameter to which the value has to be changed (BS or STmin) */

typedef enum
{
  TP_STMIN,
  TP_BS,
  TP_BC
} TPParameterType;

/* Variables of this type shall be used to store the result of a buffer request. */
/* result of a buffer request */
typedef enum
{
  BUFREQ_OK,
  BUFREQ_E_NOT_OK,
  BUFREQ_E_BUSY,
  BUFREQ_E_OVFL
} BufReq_ReturnType;

#endif /* COMSTACK_TYPES_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
