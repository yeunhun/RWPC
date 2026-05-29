/*******************************************************************************
**                                                                            **
**  (C) 2019~2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dcm_Types.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file contains type definitions for Dcm                   **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.15.1.0  17-May-2021   SK Park      Redmine #29359                        **
** 1.14.0.0  06-May-2021   JYS          Redmine #29285                        **
** 1.0.1     07-Feb-2020   Sinil        Redmine #21594                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Justified:Unset] "No Impact of this rule violation" */
#ifndef DCM_TYPES_H
#define DCM_TYPES_H
/*******************************************************************************
**                            Included header files                           **
*******************************************************************************/
#include "Btl.h"
#include "ComStack_Types.h"

/*******************************************************************************
**                             DCM Data types                                **
*******************************************************************************/
typedef uint8 Dcm_SesCtrlType;
typedef uint8 Dcm_SessionForBootType;
typedef uint8 Dcm_SecLevelType;
typedef uint8 Dcm_NegativeResponseCodeType;
typedef uint8 Dcm_ProtocolType;

/* Length of diagnostic message (request, positive or negative response) */
typedef uint32 Dcm_MsgLenType;

/* Base type for diagnostic message item */
typedef uint8 Dcm_MsgItemType;

/* Base type for diagnostic message (request, positive or negative response) */
typedef Dcm_MsgItemType* Dcm_MsgType;

/*
 * IdContext is used to determine the relation between request and response
 * confirmation
 */
typedef uint8 Dcm_IdContextType;

/* Additional information on message request */
typedef struct
{
  /* To know if the request type is physical or functional */
  uint8 u8_reqType;
  /* To know if the positive response is to be suppressed */
  uint8 u8_suppressPosResponse;
  /* To know if the Cancel operation is pending  */
  uint8 u8_cancelOperation;
}Dcm_MsgAddInfoType;

/*
 * This structure contains all information, which is necessary to process a
 * diagnostic message from request to response and response confirmation.
 */
typedef struct
{
  /* Request data, starting directly after service identifier */
  Dcm_MsgType pdt_reqData;
  /* Request data length (excluding service identifier) */
  Dcm_MsgLenType dt_reqDataLen;
  /* Positive response data, starting directly after service identifier */
  Dcm_MsgType pdt_resData;
  /* Positive response data length (excluding service identifier) */
  Dcm_MsgLenType dt_resDataLen;
  /* Additional information about service request and response */
  Dcm_MsgAddInfoType st_msgAddInfo;
  /* This message context identifier can be used to determine the relation
   * between request and response confirmation
   */
  Dcm_IdContextType dt_idContext;
  /* Pdu Identifier on which the request was received */
  PduIdType dt_dcmRxPduId;
}Dcm_MsgContextType;

typedef struct
{
  uint16 u16_P2StarServerMin;
  uint16 u16_P2StarServerMax;
  uint16 u16_P2ServerAdjust;
  uint16 u16_P2StrServerAdjust;
  uint16 u16_S3Server;
  uint16 u16_P2ServerMax;
}Dcm_DiagTimerType;

typedef uint8 Dcm_ConfirmationStatusType;

#define DCM_RES_POS_OK                          (Dcm_ConfirmationStatusType)0x00

#define DCM_RES_POS_NOT_OK                      (Dcm_ConfirmationStatusType)0x01

#define DCM_RES_NEG_OK                          (Dcm_ConfirmationStatusType)0x02

#define DCM_RES_NEG_NOT_OK                      (Dcm_ConfirmationStatusType)0x03

/*******************************************************************************
**                             Dcm_OpStatusType                               **
*******************************************************************************/
typedef uint8 Dcm_OpStatusType;

/* Indicates the initial call to the operation */
#define DCM_INITIAL                                       (Dcm_OpStatusType)0x0A

/* Indicates the final call to the operation */
#define DCM_FINAL                                         (Dcm_OpStatusType)0x0B

/* Indicates that the DCM requests to cancel the pending operation */
#define DCM_CANCEL                                        (Dcm_OpStatusType)0x0C

/* Confirm a response pending transmission */
#define DCM_FORCE_RCRRP_OK                                (Dcm_OpStatusType)0x0D

/*******************************************************************************
**                            Dcm_ReturnReadMemoryType                        **
*******************************************************************************/
/* Return values of Callout Dm_Swc_ReadMemory */
typedef uint8 Dcm_ReturnReadMemoryType;

/* Reading has been done */
#define DCM_READ_OK                               (Dcm_ReturnReadMemoryType)0x00

/* Reading is pending, another call is request to finalize the reading */
#define DCM_READ_PENDING                          (Dcm_ReturnReadMemoryType)0x01

/* Reading has failed */
#define DCM_READ_FAILED                           (Dcm_ReturnReadMemoryType)0x02

#define DCM_READ_FORCE_RCRRP                      (Dcm_ReturnReadMemoryType)0x03

/*******************************************************************************
**                            Dcm_ReturnWriteMemoryType                       **
*******************************************************************************/
/* Return type of callout Dcm_WriteMemory */
typedef uint8 Dcm_ReturnWriteMemoryType;

/* Writing has been done */
#define DCM_WRITE_OK                             (Dcm_ReturnWriteMemoryType)0x00

/* Writing is pending, another called is requested */
#define DCM_WRITE_PENDING                        (Dcm_ReturnWriteMemoryType)0x01

/* The writing has failed */
#define DCM_WRITE_FAILED                         (Dcm_ReturnWriteMemoryType)0x02

#define DCM_WRITE_FORCE_RCRRP                    (Dcm_ReturnWriteMemoryType)0x03

/*******************************************************************************
**                         Dcm_EcuStartModeType                               **
*******************************************************************************/
/* Allows the DCM to know if a diagnostic response shall be sent in the case
 * of a jump from bootloader
 */
typedef uint8 Dcm_EcuStartModeType;

/* The ECU starts normally */
#define DCM_COLD_START                                (Dcm_EcuStartModeType)0x00

/* The ECU starts from a bootloader jump */
#define DCM_WARM_START                                (Dcm_EcuStartModeType)0x01

/*******************************************************************************
**                          Macro ID For response                             **
*******************************************************************************/
#define DCM_PRS_ID                                                   (uint8)0x40

/*******************************************************************************
**                              Macros for Mask                               **
*******************************************************************************/
#define DCM_DEFAULT_SESSION_MASK                                     (uint8)0x01
#define DCM_PROG_SESSION_MASK                                        (uint8)0x02
#define DCM_EXTENDED_SESSION_MASK                                    (uint8)0x04

#define DCM_ECU_PROG_MODE_MASK                                       (uint8)0x08
#define DCM_EXTENDED_DIAGNOSTIC_MODE_MASK                            (uint8)0x10

#if (FBL_SUPPORT_DIAGNOSTIC_STANDARD == FBL_ES95486_00)
#define DCM_ALL_SESSION_MASK                                         (uint8)0x1F
#else
#define DCM_ALL_SESSION_MASK                                         (uint8)0x07
#endif

#define DCM_ADDR_PHYSICAL_MASK                                       (uint8)0x01
#define DCM_ADDR_FUNCTIONAL_MASK                                     (uint8)0x02

#define DCM_BIT0_AND_MASK                                            (uint8)0x01
#define DCM_BIT6_AND_MASK                                            (uint8)0xBF

#define DCM_SUBFUNCTION_MASK                                         (uint8)0x7F
#define DCM_SUPRESSBIT_MASK                                          (uint8)0x80

#define DCM_SIG_SIZE_MASK                                            (uint8)0xF0
#define DCM_SIG_BYTE_MASK                                            (uint8)0x0F

#define DCM_HIGH_NIBBLE_MASK                                         (uint8)0xF0
#define DCM_LOW_NIBBLE_MASK                                          (uint8)0x0F

/* Services and Sub functions allowed having Security Access level configured
 * as Level 0 can have access to all the security levels present . Services
 * configured in other levels don't have access in this level at all.
 * Use the Macro accordingly.
*/

/*******************************************************************************
**                        Macros for DcmDspDataUsePort                        **
*******************************************************************************/
#define DCM_USEBLOCKID                                               (uint8)0x00
#define DCM_USEECUSIGNAL                                             (uint8)0x01
#define DCM_USE_DATA_ASYNCH_CLIENT_SERVER                            (uint8)0x02
#define DCM_USE_DATA_SYNCH_CLIENT_SERVER                             (uint8)0x03
#define DCM_USE_DATA_SENDER_RECEIVER                                 (uint8)0x04
#define DCM_USE_DATA_SYNCH_FNC                                       (uint8)0x05
#define DCM_USE_DATA_ASYNCH_FNC                                      (uint8)0x06

/*******************************************************************************
**                          Bootloader Type Macro                             **
*******************************************************************************/
#define DCM_NO_BOOT                                                  (uint8)0x00
#define DCM_OEM_BOOT                                                 (uint8)0x01
#define DCM_SYS_BOOT                                                 (uint8)0x02

/*******************************************************************************
**                     Diagnostic Service Ids                                 **
*******************************************************************************/

#define DCM_DIAGNOSTICSESSIONCONTROL                                 (uint8)0x10
#define DCM_ECURESET                                                 (uint8)0x11
#define DCM_CLEARDIAGNOSTICINFORMATION                               (uint8)0x14
#define DCM_READDTCINFORMATION                                       (uint8)0x19
#define DCM_READDATABYIDENTIFIER                                     (uint8)0x22
#define DCM_READMEMORYBYADDRESS                                      (uint8)0x23
#define DCM_READSCALINGDATABYIDENTIFIER                              (uint8)0x24
#define DCM_SECURITYACCESS                                           (uint8)0x27
#define DCM_COMMUNICATIONCONTROL                                     (uint8)0x28
#define DCM_READDATABYPERIODICIDENTIFIER                             (uint8)0x2A
#define DCM_DYNAMICALLYDEFINEDATAIDENTIFIER                          (uint8)0x2C
#define DCM_WRITEDATABYIDENTIFIER                                    (uint8)0x2E
#define DCM_INPUTOUTPUTCONTROLBYIDENTIFIER                           (uint8)0x2F
#define DCM_ROUTINECONTROL                                           (uint8)0x31
#define DCM_REQUESTDOWNLOAD                                          (uint8)0x34
#define DCM_REQUESTUPLOAD                                            (uint8)0x35
#define DCM_TRANSFERDATA                                             (uint8)0x36
#define DCM_REQUESTTRANSFEREXIT                                      (uint8)0x37
#define DCM_WRITEMEMORYBYADDRESS                                     (uint8)0x3D
#define DCM_TESTERPRESENT                                            (uint8)0x3E
#define DCM_ACCESSTIMINGPARAMETER                                    (uint8)0x83
#define DCM_SECUREDDATATRANSMISSION                                  (uint8)0x84
#define DCM_CONTROLDTCSETTING                                        (uint8)0x85
#define DCM_RESPONSEONEVENT                                          (uint8)0x86
#define DCM_LINKCONTROL                                              (uint8)0x87

#define DCM_PRSID_DIAGNOSTICSESSIONCONTROL                           (uint8)0x50
#define DCM_PRSID_ECURESET                                           (uint8)0x51
#define DCM_PRSID_ROUTINECONTROL                                     (uint8)0x71

/*******************************************************************************
**                      DET ERROR CODES                                       **
*******************************************************************************/
/* Timeout is reported using following error code */
#define DCM_E_INTERFACE_TIMEOUT                                      (uint8)0x01

/* Return-value out of range is reported using following error code */
#define DCM_E_INTERFACE_RETURN_VALUE                                 (uint8)0x02

/* Buffer Overflow is reported using following error code */
#define DCM_E_INTERFACE_BUFFER_OVERFLOW                              (uint8)0x03

/* Protocol mismatch is reported using following error code */
#define DCM_E_INTERFACE_PROTOCOL_MISMATCH                            (uint8)0x04

/* Dcm not initialized is reported using following error code */
#define DCM_E_UNINIT                                                 (uint8)0x05

/*
 * Dcm API function with invalid input parameter is reported using following
 * error code
 */
#define DCM_E_PARAM                                                  (uint8)0x06
/*
 * Dcm API function with invalid pointer parameter is reported using following
 * error code
 */
#define DCM_E_PARAM_POINTER                                          (uint8)0x07

/* 
 * No matched session exists in SessionConfigTalbe is reported 
 * using following error code 
 */
#define DCM_E_MATCHED_SESSION_NOT_EXIST                              (uint8)0x08

/*******************************************************************************
**                     Diagnostic Service Sub Func Ids                        **
*******************************************************************************/
#define DCM_DEFAULT_SESSION                                                0x01U
#define DCM_PROG_SESSION                                                   0x02U
#define DCM_EXTENDED_SESSION                                               0x03U

#define DCM_ECU_PROG_MODE                                                  0x05U
#define DCM_EXTENDED_DIAGNOSTIC_MODE                                       0x10U

/* DcmEcuReset type definition */
typedef uint8 Dcm_EcuResetType;

#define DCM_RESET_NONE                                    (Dcm_EcuResetType)0x00
#define DCM_RESET_HARD                                    (Dcm_EcuResetType)0x01
#define DCM_RESET_KEYONOFF                                (Dcm_EcuResetType)0x02
#define DCM_RESET_SOFT                                    (Dcm_EcuResetType)0x03
#define DCM_RESET_ENABLE_RAPIDPOWERSHUTDOWN               (Dcm_EcuResetType)0x04
#define DCM_RESET_DISABLE_RAPIDPOWERSHUTDOWN              (Dcm_EcuResetType)0x05

#define DCM_RESET_JUMPTOBOOTLOADER                        (Dcm_EcuResetType)0x06
#define DCM_RESET_JUMPTOSYSSUPPLIERBOOTLOADER             (Dcm_EcuResetType)0x07

#define DCM_RESET_EXECUTE                                 (Dcm_EcuResetType)0x08

#define DCM_ROUTINE_START                                                  0x01U
#define DCM_ROUTINE_START_SUPRESS                                          0x81U
#define DCM_ROUTINE_STOP                                                   0x02U
#define DCM_ROUTINE_REQUESTRESULT                                          0x03U

#define DCM_TESTERPRESENT_SUBFUNC                                          0x00U

#define DCM_FULL_COMMUNICATION                                             0x00U
#define DCM_SILENT_COMMUNICATION                                           0x01U
#define DCM_NO_COMMUNICATION                                               0x02U

#define DCM_VERIFY_MODE_TRANSITION_FIXED_PARAM                             0x01U
#define DCM_VERIFY_MODE_TRANSITION_SPECIFIC_PARAM                          0x02U
#define DCM_TRANSITION_MODE                                                0x03U

#define DCM_ENABLE_RX_TX                                                   0x00U
#define DCM_ENABLE_RX_DISABLE_TX                                           0x01U
#define DCM_DISABLE_RX_ENABLE_TX                                           0x02U
#define DCM_DISABLE_RX_TX                                                  0x03U

#define DCM_DTC_ON                                                         0x01U
#define DCM_DTC_OFF                                                        0x02U

#define DCM_READ_EXTENDED_TIMING_PARAMETER_SET                             0x01U
#define DCM_SET_TIMING_PARAMETERS_TO_DEFAULT_VALUES                        0x02U
#define DCM_READ_CURRENTLY_ACTIVE_TIMING_PARAMETERS                        0x03U
#define DCM_SET_TIMING_PARAMETERS_TO_GIVEN_VALUES                          0x04U

/*******************************************************************************
**                         Macros for Transfer Data                           **
*******************************************************************************/
#define DCM_TD_IDLE                                                  (uint8)0x00
#define DCM_TD_FF                                                    (uint8)0x01
#define DCM_TD_CF                                                    (uint8)0x02
#define DCM_TD_LF                                                    (uint8)0x03

/*******************************************************************************
**                          Numerical Macros                                  **
*******************************************************************************/
#define DCM_ZERO                                                   ((uint8)0x00)
#define DCM_ONE                                                    ((uint8)0x01)
#define DCM_TWO                                                    ((uint8)0x02)
#define DCM_THREE                                                  ((uint8)0x03)
#define DCM_FOUR                                                   ((uint8)0x04)
#define DCM_FIVE                                                   ((uint8)0x05)
#define DCM_SIX                                                    ((uint8)0x06)
#define DCM_SEVEN                                                  ((uint8)0x07)
#define DCM_EIGHT                                                  ((uint8)0x08)
#define DCM_NINE                                                   ((uint8)0x09)
#define DCM_TEN                                                    ((uint8)0x0A)
#define DCM_ELEVEN                                                 ((uint8)0x0B)
#define DCM_TEWELVE                                                ((uint8)0x0C)
#define DCM_THIRTEEN                                               ((uint8)0x0D)
#define DCM_FOURTEEN                                               ((uint8)0x0E)
#define DCM_FIFTEEN                                                ((uint8)0x0F)
#define DCM_THIRTY_TWO                                             ((uint8)0x20)
#define DCM_SIXTY_FOUR                                             ((uint8)0x40)
#define DCM_NINTY_SIX                                              ((uint8)0x60)
#define DCM_ONE_TWO_EIGHT                                          ((uint8)0x80)
#define DCM_ONE_SIXTY                                              ((uint8)0xA0)
#define DCM_ONE_NINE_TWO                                           ((uint8)0xC0)
#define DCM_TWO_TWO_FOUR                                           ((uint8)0xE0)
#define DCM_SIXTEEN                                                ((uint8)0x10)
#define DCM_TWENTY                                                 ((uint8)0x14)
#define DCM_NINETEEN                                               ((uint8)0x13)
#define DCM_TWENTYONE                                              ((uint8)0x15)
#define DCM_SEVENTEEN                                              ((uint8)0x11)
#define DCM_EIGHTTEEN                                              ((uint8)0x12)
#define DCM_TWENTYFOUR                                             ((uint8)0x18)
#define DCM_ONE_HUNDRED_TWENTY_FIVE                                ((uint8) 125)

/*******************************************************************************
**                            Boolean Macros                                  **
*******************************************************************************/
#define DCM_FALSE                                              (boolean)DCM_ZERO
#define DCM_TRUE                                                (boolean)DCM_ONE
#define DCM_UNINITIALISED                                              DCM_FALSE
#define DCM_INITIALISED                                                 DCM_TRUE

/*******************************************************************************
**                            Security Macros                                 **
*******************************************************************************/
#define DCM_MAX_SEC_LEVEL_COUNT         (DCM_SUPPORTED_SEC_LEVEL_COUNT + DCM_ONE)
/* DCM_MAX_SEC_SUBFUNC_COUNT  =  1*2  */
#define DCM_MAX_SEC_SUBFUNC_COUNT                             (DCM_ONE<<DCM_ONE)

#define DCM_SECURITY_LEVEL_0                                               0x00U
#define DCM_SECURITY_LEVEL_0_MASK                                          0x80U
#define DCM_SECURITY_LEVEL_0_L0                                            0x00U

/*******************************************************************************
**                          Miscellaneous DCM Macros                          **
*******************************************************************************/
#define DCM_SERVICE_NOT_CONFIGURED                                   (uint8)0xFF
#define DCM_ADDR_FUNCTIONAL                                          (uint8)0x01
#define DCM_ADDR_PHYSICAL                                            (uint8)0x00
#define DCM_NEGATIVE_RESPONSE_SID                                    (uint8)0x7F
#define DCM_QBUFFER_NOT_AVAILABLE                                    (uint8)0xFF

/* Macro for Unused parameter */
#define DCM_UNUSED(x)                                                  (void)(x)

#define DCM_E_PENDING                                                (uint8)0x02
#define DCM_E_FORCE_RCRRP                                            (uint8)0x0C

/* Position of sub function value in the requested buffer */
#define DCM_DSP_POSITION_SUBFUNC                                     (uint8)0x00

#define DCM_DSP_LOWER_BYTE_MASK                                   (uint16)0x00FF

/* Macro for invalid session config table index */
#define DCM_INVALID_SESSION_IDX_U8									 (uint8)0xFF

#endif /* DCM_TYPES_H */
/* polyspace-end MISRA-C3:2.5 [Justified:Unset] "No Impact of this rule violation" */
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
