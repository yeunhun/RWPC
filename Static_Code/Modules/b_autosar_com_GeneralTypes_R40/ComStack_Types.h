/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComStack_Types.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR BSW R4.0.3 Modules                                    **
**                                                                            **
**  PURPOSE   : Provision for Communication Stack dependent types             **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.2.1.0   23-Aug-2021   HM Shin     #31066                                 **
** 1.2.0     17-Apr-2018   Chan Kim    #12356                                 **
** 1.1.5     09-Dec-2016   Chan Kim    #6925                                  **
** 1.0.0     25-Jul-2013   Autron      Initial version                        **
*******************************************************************************/


#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Std_Types.h"       /* Standard AUTOSAR types           */
#include "ComStack_Cfg.h"    /* Communication Stack Configuration file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/*
 * AUTOSAR specification version information
 */
#define COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION      4
#define COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION      0
#define COMSTACK_TYPES_AR_RELEASE_REVISION_VERSION   3

/*
 * File version information
 */
#define COMSTACK_TYPES_SW_MAJOR_VERSION        1
#define COMSTACK_TYPES_SW_MINOR_VERSION        2

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* General return codes for NotifResultType */
#define NTFRSLT_OK                     0x00
#define NTFRSLT_E_NOT_OK               0x01
#define NTFRSLT_E_TIMEOUT_A            0x02
#define NTFRSLT_E_TIMEOUT_BS           0x03
#define NTFRSLT_E_TIMEOUT_CR           0x04
#define NTFRSLT_E_WRONG_SN             0x05
#define NTFRSLT_E_INVALID_FS           0x06
#define NTFRSLT_E_UNEXP_PDU            0x07
#define NTFRSLT_E_WFT_OVRN             0x08
#define NTFRSLT_E_ABORT                0x09
#define NTFRSLT_E_NO_BUFFER            0x0A
#define NTFRSLT_E_CANCELATION_OK       0x0B
#define NTFRSLT_E_CANCELATION_NOT_OK   0x0C
#define NTFRSLT_PARAMETER_OK           0x0D
#define NTFRSLT_E_PARAMETER_NOT_OK     0x0E
#define NTFRSLT_E_RX_ON                0x0F
#define NTFRSLT_E_VALUE_NOT_OK         0x10

/* General return codes for BusTrcvErrorType */
#define BUSTRCV_OK                     0x00
#define BUSTRCV_E_ERROR                0x01

/*******************************************************************************
**                      Global Data Types (ECU dependent)                     **
*******************************************************************************/

/* Variables of the type PNCHandleType shall be used to store the identifier of a partial network cluster. */
typedef uint16       PNCHandleType;

/* Variables of the type NotifResultType shall be used to store the result status of a notification (confirmation or indication). */
typedef uint8        NotifResultType;

/* Variables of the type BusTrcvErrorType shall be used to return the bus status evaluated by a transceiver. */
typedef uint8        BusTrcvErrorType;

/* Variables of the type NetworkHandleType shall be used to store the identifier of a communication channel. */
typedef uint8        NetworkHandleType;

/*******************************************************************************
**                      Global Data Types (ECU independent)                   **
*******************************************************************************/

/* Variables of this type shall be used to store the basic information about a PDU of any type, namely a pointer variable pointing to its SDU (payload) and the corresponding length of the SDU in bytes. */
typedef struct STag_PduInfoType
{
  P2VAR(uint8,AUTOMATIC,AUTOSAR_COMSTACKDATA) SduDataPtr;
  PduLengthType  SduLength;
} PduInfoType;                   /* Basic information about a PDU of any type */

/* Variables of this type shall be used to store the state of TP buffer. */
typedef enum
{
  TP_DATACONF,
  TP_DATARETRY,
  TP_CONFPENDING,
  TP_NORETRY
} TpDataStateType;                 /* Store the state of TP buffer          */

/* Variables of this type shall be used to store the information about Tp buffer handling. */
typedef struct STag_RetryInfoType
{
  TpDataStateType TpDataState;
  PduLengthType TxTpDataCnt;
} RetryInfoType;                   /* Store the information about Tp buffer 
                                      handling */
/* Variables of this type specify the parameter to which the value has to be changed (BS or STmin). */
typedef enum
{
  TP_STMIN,
  TP_BS,
  TP_BC
} TPParameterType;                 /* parameter to which the value has to be changed
                                      (BS or STmin)          */
/* Variables of this type shall be used to store the result of a buffer request. */
typedef enum
{
  BUFREQ_OK,
  BUFREQ_E_NOT_OK,
  BUFREQ_E_BUSY,
  BUFREQ_E_OVFL
} BufReq_ReturnType;                /* result of a buffer request          */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* COMSTACK_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
