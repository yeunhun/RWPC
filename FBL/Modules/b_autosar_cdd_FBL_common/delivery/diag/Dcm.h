/*******************************************************************************
**                                                                            **
**  (C) 2019~2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dcm.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Dcm.c                                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.15.1.0  17-May-2021   SK Park      Redmine #29359                        **
** 1.0.1     07-Feb-2020   Sinil        Redmine #21498                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef DCM_H
#define DCM_H

/*******************************************************************************
**                            Include Section                                 **
*******************************************************************************/
#include "Dcm_Types.h"
#include "Dcm_PCTypes.h"
#include "Dcm_Cfg.h"
#include "Dcm_Globals.h"
#include "Dm_Swc.h"

#include "Util.h"
#include "Det.h"

/*******************************************************************************
**                      Function Declarations                                 **
*******************************************************************************/
#define DCM_READDATABYID_DID_F186                                        0xF186U
#define DCM_READDATABYID_DID_F186_SIZE                                        1U

#define DCM_MAXVALUE                                                       0xFFU

#define DCM_E_POSITIVERESPONSE                                              0x0U

/**
 * This return value indicates that the requested action has been rejected
 * by the application. The generalReject return value shall only be
 * implemented in the application if none of the negative return values
 * defined in this document meet the needs of the implementation. At no
 * means shall this return value be a general replacement for the return
 * values defined in this document.
 */
#ifndef DCM_E_GENERALREJECT
#define DCM_E_GENERALREJECT 0x10U
#endif
/**
 * This return value indicates that the requested action will not be taken
 * because the application does not support the requested service.
 * The application shall send this return value in case the client has sent
 * a request message with a service identifier, which is either unknown or
 * not supported by the application. Therefore this negative return value is
 * not shown in the list of negative return values to be supported for a
 * diagnostic service, because this negative return value is not applicable
 * for supported services.
 */
#ifndef DCM_E_SERVICENOTSUPPORTED
#define DCM_E_SERVICENOTSUPPORTED 0x11U
#endif
/**
 * This return value indicates that the requested action will not be taken
 * because the application does not support the service specific parameters
 * of the request message. The application shall send this return value in
 * case the client has sent a request message with a known and supported
 * service identifier but with "sub function" which is either unknown or not
 * supported.
 */
#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTED
#define DCM_E_SUBFUNCTIONNOTSUPPORTED 0x12U
#endif
/**
 * This return value indicates that the requested action will not be taken
 * because the length of the received request message does not match the
 * prescribed length for the specified service or the format of the
 * parameters do not match the prescribed format for the specified service.
 */
#ifndef DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT 0x13U
#endif

/**
 * This return value indicates that the buffer of the lower layer is not
 * large enough to transmit all data of the response.
 */
#ifndef DCM_E_RESPONSE_TOO_LONG
#define DCM_E_RESPONSE_TOO_LONG 0x14U
#endif
/**
 * This return value indicates that the application is temporarily too busy
 * to perform the requested operation. In this circumstance the client shall
 * perform repetition of the "identical request message" or "another request
 * message". The repetition of the request shall be delayed by a time
 * specified in the respective implementation documents.
 * Example: In a multi-client environment the diagnostic request of one
 * client might be blocked temporarily by a NRC 0x21 while a different
 * client finishes a diagnostic task.
 * Note: If the application is able to perform the diagnostic task but needs
 * additional time to finish the task and prepare the response, the NRC 0x78
 * shall be used instead of NRC 0x21. This return value is in general supported
 * by each diagnostic service, as not otherwise stated in the data link
 * specific implementation document, therefore it is not listed in the list
 * of applicable return values of the diagnostic services.
 */
#ifndef DCM_E_BUSYREPEATREQUEST
#define DCM_E_BUSYREPEATREQUEST 0x21U
#endif
/**
 * This return value indicates that the requested action will not be taken
 * because the application prerequisite conditions are not met.
 */
#ifndef DCM_E_CONDITIONSNOTCORRECT
#define DCM_E_CONDITIONSNOTCORRECT 0x22U
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application expects a different sequence of request messages
 * or message as sent by the client. This may occur when sequence sensitive
 * requests are issued in the wrong order.
 * EXAMPLE A successful SecurityAccess service specifies a sequence of
 * requestSeed and sendKey as sub-functions in the request messages. If the
 * sequence is sent different by the client the application shall send a
 * negative response message with the negative return value 0x24-
 * requestSequenceError.
 */
#ifndef DCM_E_REQUESTSEQUENCEERROR
#define DCM_E_REQUESTSEQUENCEERROR 0x24U
#endif
/**
 * This return value indicates that the requested action cannot be performed
 * because the subnet component did not respond within the specified time.
 */

#ifndef DCM_E_NORESPONSEFROMSUBNETCOMPONENT
#define DCM_E_NORESPONSEFROMSUBNETCOMPONENT 0x25U
#endif

/**
 * This response code indicates that the requested action will not be taken
 * because a failure condition, identified by a DTC has occurred and that this
 * failure condition prevents the server from performing the requested action.
 */

#ifndef DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION
#define DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION 0x26U
#endif


/**
 * This return value indicates that the requested action will not be taken
 * because the application has detected that the request message contains a
 * parameter which attempts to substitute a value beyond its range of
 * authority (e.g. attempting to substitute a data byte of 111 when the data
 * is only defined to 100), or which attempts to access a dataIdentifier-
 * routineIdentifer that is not supported or not supported in active session.
 * This return value shall be implemented for all services, which allow the
 * client to read data write data, or adjust functions by data in the
 * application.
 */
#ifndef DCM_E_REQUESTOUTOFRANGE
#define DCM_E_REQUESTOUTOFRANGE 0x31U
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application's security strategy has not been satisfied by the
 * client. The application shall send this return value if one of the
 * following cases occur:
 * - the test conditions of the application are not met,
 * - the required message sequence e.g. DiagnosticSessionControl,
 *   securityAccess is not met,
 * - the client has sent a request message which requires an unlocked
 *   application.
 * Beside the mandatory use of this negative return value as specified in
 * the applicable services within this standard, this negative return value
 * can also be used for any case where security is required and is not yet
 * granted to perform the required service.
 */
#ifndef DCM_E_SECURITYACCESSDENIED
#define DCM_E_SECURITYACCESSDENIED 0x33U
#endif

/**
 * This return value indicates that the application has not given security
 * access because the key sent by the client did not match with the key in
 * the application's memory. This counts as an attempt to gain security.
 * The application shall remain locked and increment is internal
 * securityAccessFailed counter.
 */
#ifndef DCM_E_INVALIDKEY
#define DCM_E_INVALIDKEY 0x35U
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the client has unsuccessfully attempted to gain security access
 * more times than the application's security strategy will allow.
 */
#ifndef DCM_E_EXCEEDNUMBEROFATTEMPTS
#define DCM_E_EXCEEDNUMBEROFATTEMPTS 0x36U
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the client's latest attempt to gain security access was initiated
 * before the application's required timeout period had elapsed.
 */
#ifndef DCM_E_REQUIREDTIMEDELAYNOTEXPIRED
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED 0x37U
#endif

/**
 * This return value indicates that an attempt to upload_download to a
 * application's memory cannot be accomplished due to some fault conditions.
 */
#ifndef DCM_E_UPLOADDOWNLOADNOTACCEPTED
#define DCM_E_UPLOADDOWNLOADNOTACCEPTED 0x70U
#endif

/**
 * This return value indicates that a data transfer operation was halted due
 * to some fault.
 */
#ifndef DCM_E_TRANSFERDATASUSPENDED
#define DCM_E_TRANSFERDATASUSPENDED 0x71U
#endif

/**
 * This return value indicates that the application detected an error when
 * erasing or programming a memory location in the permanent memory device
 * (e.g. Flash Memory).
 */
#ifndef DCM_E_GENERALPROGRAMMINGFAILURE
#define DCM_E_GENERALPROGRAMMINGFAILURE 0x72U
#endif

/**
 * This return value indicates that the application detected an error in the
 * sequence of blockSequenceCounter values. Note that the repetition of a
 * TransferData request message with a blockSequenceCounter equal to the one
 * included in the previous TransferData request message shall be accepted
 * by the application.
 */
#ifndef DCM_E_WRONGBLOCKSEQUENCECOUNTER
#define DCM_E_WRONGBLOCKSEQUENCECOUNTER 0x73U
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application does not support the requested sub-function in
 * the session currently active. This return value shall only be used when
 * the requested sub function is known to be supported in another session,
 * otherwise return value SFNS (subFunctionNotSupported) shall be used.
 * This return value shall be supported by each diagnostic service with a
 * sub-function parameter, if not otherwise stated in the data link specific
 * implementation document, therefore it is not listed in the list of
 * applicable return values of the diagnostic services.
 */
#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION 0x7EU
#endif

/**
 * This return value indicates that the requested action will not be taken
 * because the application does not support the requested service in the
 * session currently active. This return value shall only be used when the
 * requested service is known to be supported in another session, otherwise
 * return value SNS (serviceNotSupported) shall be used. This return value
 * is in general supported by each diagnostic service, as not otherwise
 * stated in the data link specific implementation document, therefore it is
 * not listed in the list of applicable return values of the diagnostic
 * services.
 */
#ifndef DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION 0x7FU
#endif

/**
 * This range of values is reserved for vehicle manufacturer specific condition
 * not correct scenarios. This NRC is used for blocking sending NRC for service
 * not supported in addressing mode
 */
#ifndef DCM_E_VM_CONDITIONSNOTCORRECT
#define DCM_E_VM_CONDITIONSNOTCORRECT 0xF0U
#endif
/**
 * This NRC indicates that the request message was received correctly, and that
 * all parameters in the request message were valid, but the action to be
 * performed is not yet completed and the server is not yet ready to receive
 * another request. As soon as the requested service has been completed, the
 * server shall send a positive response message or negative response message
 * with a response code different from this.
 */
#ifndef DCM_E_RCRRP
#define DCM_E_RCRRP 0x78U
#endif

/* CRL integrity check is failed */
#ifndef DCM_E_CRLINTEGRITYCHECKFAILED
#define DCM_E_CRLINTEGRITYCHECKFAILED 0xF0U
#endif

/* CRL is expired */
#ifndef DCM_E_CRLEXPIRED
#define DCM_E_CRLEXPIRED 0xF1U
#endif

/* Role and Right of Certificate verification failed */
#ifndef DCM_E_CERTVERIFICATIONFAILED
#define DCM_E_CERTVERIFICATIONFAILED 0xF2U
#endif

/*******************************************************************************
**                     Functions provided to BSW modules and to SW-Cs         **
*******************************************************************************/

/* Service Id of Dcm_GetSecurityLevel */
#define DCM_GET_SECURITY_LEVEL_SID                                 ((uint8)0x0D)

/* Service Id of Dcm_GetSesCtrlType */
#define DCM_GET_SES_CTRL_TYPE_SID                                  ((uint8)0x06)

/* Service Id of Dcm_GetVin */
#define DCM_GET_VIN_SID                                            ((uint8)0x07)

/* Service Id of Dcm_GetActiveProtocol */
#define DCM_GET_ACTIVE_PROTOCOL_SID                                ((uint8)0x0F)

/* Service Id of Dcm_ResetToDefaultSession */
#define DCM_RESET_TO_DEFAULTSESSION_SID                            ((uint8)0x2A)

/* Service Id of Dcm_TriggerOnEvent */
#define DCM_TRIGGER_ON_EVENT_SID                                   ((uint8)0x2D)

/*******************************************************************************
**                     Callback Notifications                                 **
*******************************************************************************/

/* Service Id of Dcm_StartOfReception */
#define DCM_START_OF_RECEPTION_SID                                 ((uint8)0x00)

/* Service Id of Dcm_CopyRxData */
#define DCM_COPY_RXDATA_SID                                        ((uint8)0x02)

/* Service Id of Dcm_TpRxIndication */
#define DCM_RX_INDICATION_SID                                      ((uint8)0x03)

/* Service Id of Dcm_CopyTxData */
#define DCM_COPY_TXDATA_SID                                        ((uint8)0x04)

/* Service Id of Dcm_TpTxConfirmation */
#define DCM_TX_CONFIRMATION_SID                                    ((uint8)0x05)

/* Service Id of Dcm_ComM_NoComModeEntered */
#define DCM_COMM_NO_COM_MODE_ENTERED_SID                           ((uint8)0x21)

/* Service Id of Dcm_ComM_SilentComModeEntered */
#define DCM_COMM_SILENT_COM_MODE_ENTERED_SID                       ((uint8)0x22)

/* Service Id of Dcm_ComM_FullComModeEntered */
#define DCM_COMM_FULL_COM_MODE_ENTERED_SID                         ((uint8)0x23)

/* Added service id by youngjin.yun ,2014-12-13 */
#define DCM_SYNC_READ_DATA_SID                                     ((uint8)0x34)
#define DCM_SYNC_WRITE_DATA_SID                                    ((uint8)0x35)

#define DCM_READ_DATA_LENGTH_SID                                   ((uint8)0x36)
#define DCM_CONDITION_CHECK_READ_SID                               ((uint8)0x37)

#define DCM_ASYNC_READ_DATA_SID                                    ((uint8)0x3B)
#define DCM_ASYNC_WRITE_DATA_SID                                   ((uint8)0x3E)

#define DCM_VARIANT_FUNC_SID                                       ((uint8)0x40)

/*******************************************************************************
**                     Callout Definitions                                    **
*******************************************************************************/

/* Service Id of Dcm_ReadMemory */
#define DCM_READ_MEMORY_SID                                        ((uint8)0x26)

/* Service Id of Dcm_WriteMemory */
#define DCM_WRITE_MEMORY_SID                                       ((uint8)0x27)

/* Dcm_<DiagnosticService> needs to be done */

/* Service Id of Dcm_Confirmation */
#define DCM_CONFIRMATION_SID                                       ((uint8)0x29)

/*******************************************************************************
**                     Scheduled Functions                                    **
*******************************************************************************/

/* Service Id of Dcm_MainFunction */
#define DCM_MAIN_FUNCTION_SID                                      ((uint8)0x25)

/* Service ID of Dcm_InitStartFromReset */
#define DCM_INIT_START_FROM_RESET_SID							   ((uint8)0x50)

/* Service ID of Dcm_DcmDiagnosticSessionControl */
#define DCM_DIAGGNOSTIC_SESSION_CONTROL_SID						   ((uint8)0x51)

/*******************************************************************************
**                             Scheduler function                             **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void Dcm_Init(const Dcm_ConfigType_Styp *Lpdt_Config);

extern void Dcm_MainFunction(void);

extern void Dcm_SetPrgrammingSession(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* DCM_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
