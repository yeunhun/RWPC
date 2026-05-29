/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_PCTypes.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of PduR Structure definitions                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 2.8.1     07-Jun-2021   HM Shin     #30157                                 **
** 2.6.0     03-Nov-2020   HM Shin     #24937, #24858                         **
** 2.5.0.0   28-Feb-2020   HM Shin     #19725                                 **
** 2.4.0     06-Sep-2019   HM Shin     #18909                                 **
** 2.3.0     22-Aug-2019   JS Lim      #18336                                 **
** 2.2.0     01-Feb-2017   Chan Kim    Redmine #6922                          **
** 2.1.5     21-Sep-2016   Chan Kim    Redmine #6706, #6771, #6774            **
** 2.1.2     21-Sep-2016   Chan Kim    Redmine #6014                          **
** 2.1.1     17-Jun-2016   Chan Kim    Redmine #5490, #5632, #5680            **
** 2.1.0     17-Jun-2016   Chan Kim    Redmine #5190, #5250                   **
** 2.0.8     10-Jun-2016   Chan Kim    Redmine #5143                          **
** 2.0.5     06-Apr-2016   Chan Kim    Redmine #4519                          **
** 2.0.4     19-Feb-2016   Chan Kim    Redmine #3429, #3425, #3813            **
** 2.0.3     23-Dec-2015   Chan Kim    Redmine #3746                          **
** 2.0.3     24-Nov-2015   Chan Kim    Redmine #3545, #4519                   **
** 2.0.0     11-Aug-2015   Chan Kim    Redmine #2949                          **
** 1.1.2     18-Nov-2014   Chan Kim    Redmine #1639                          **
** 1.1.1     18-Jul-2014   Chan Kim    Redmine #1171                          **
** 1.0.7     10-Jun-2013   Chan Kim    Change code for release Library        **
** 1.0.0     29-Apr-2013   Autoever      Initial Version                        **
*******************************************************************************/
#ifndef PDUR_PCTYPES_H
#define PDUR_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* #1639 : Add Include Header File */
#include "PduR.h"
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* DET module header */
#endif
#if (PDUR_ZERO_COST_OPERATION == STD_ON)
#include "PduR_Incl.h"            /* Dependent module Header files*/
#endif
#include "PduR_Types.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define PDUR_PCTYPES_AR_RELEASE_MAJOR_VERSION    4
#define PDUR_PCTYPES_AR_RELEASE_MINOR_VERSION    0
#define PDUR_PCTYPES_AR_RELEASE_REVISION_VERSION 3

/* Software Version Information */
#define PDUR_PCTYPES_SW_MAJOR_VERSION            2
#define PDUR_PCTYPES_SW_MINOR_VERSION            9
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Macro for upper layer indication */
#define PDUR_UPPER_LAYER                      ((uint16)0xFFFF)

/* Macro for buffer unavailable condition */
#define PDUR_GATEWAY_NOBUFFER                 ((uint16)0xFFFE)

/* Macro for invalid condition */
#define PDUR_INVALID_BUFFER                   ((uint16)0xFFFF)

/* Macro for D fifo */
#define PDUR_D_FIFO                           0x40

/* Macro for TT fifo */
#define PDUR_TT_FIFO                          0x80

/* Buffer mask */
#define PDUR_BUFFER_MASK                      0xC0

/* Mask for multicast transmission */
#define PDUR_MULTICAST_MASK                   0x80

/* Mask for gateway condition */
#define PDUR_GATEWAY_MASK                     ((uint8)0x40)

/* Mask for nongateway condition */
#define PDUR_NONGATEWAY_MASK                  ((uint8)0xC0)

/* Mask for upper layer */
#define PDUR_UPPERLAYER_MASK                  ((uint8)0x80)

/* Mask for target index */
#define PDUR_TARGETINDX_MASK                  ((uint8)0x7F)

/* The following mask is used in case of Uptransmit */
/* For masking the value from structure element - ucFraTIOrNoOfRoute */
#define PDUR_TARGET_INDEX_MASK                ((uint8)0x3F)

/* Mask for number of routes */
#define PDUR_NOOFROUTE_MASK                   ((uint8)0x7F)

/* Mask for index */
#define PDUR_INDEX_MASK                       ((uint8)0x3F)

/* Macro for zero */
#define PDUR_ZERO                             0x00

/*Macro for one */
#define PDUR_ONE                              0x01

/*Macro for one */
#define PDUR_TWO                              0x02

/* Initialization check macro for uninitialized condition */
#define PDUR_INITIALIZED                      PDUR_ONE

/* Initialization check macro for initialized condition */
#define PDUR_UNINITIALIZED                    PDUR_ZERO

/* Macro for true condition  */
#define PDUR_TRUE                             PDUR_ONE

/* Macro for false condition  */
#define PDUR_FALSE                            PDUR_ZERO

#define PDUR_ROUTING_DISABLED                 PDUR_ZERO

#define PDUR_ROUTING_ENABLED                  PDUR_ONE 

/* Macro for cancel range */
#define PDUR_CANCEL_RANGE                     ((uint8)0x03)

/* Macro for invalid condition */
#define PDUR_INVALID                          ((uint8)0xFF)

/* Macro for undefined condition */
#define PDUR_UNDEFINED                        ((uint16)0xFFFF)

#define PDUR_UNDEFINED_ROUTINGPATH_GROUP      ((uint16)0xFFFF)

/* Macro for undefined condition */
#define PDUR_MAX_BUFFER_VALUE                 ((uint16)0xFFFF)

/* Macro for STMIN direct value range */
#define PDUR_STMIN_DIRECT_VALUE_RANGE         ((uint8)0x7F)

/* Macro for STMIN low */
#define PDUR_STMIN_US_LOW                     ((uint8)0xF1)

/* Macro for STMIN high */
#define PDUR_STMIN_US_HIGH                    ((uint8)0xF9)

/* Macro for max BS value */
#define PDUR_MAX_BS_VAL                       ((uint8)0xFF)

/* Macro for TP Layer */
#define PDUR_TP_LAYER                         ((uint8)0x40)

/* Macro for zero length */
#define PDUR_LENGTH_ZERO                      ((uint8)0x00)

#if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
/* Macro for TP transmission done */
#define PDUR_TPTX_DONE                        ((uint8)0x00)

/* Macro for TP transmission Pending */
#define PDUR_TPTX_PENDING                     ((uint8)0x01)
#endif

/*
 * Lower layer communication interface module
 * Macro's for ucModuleType present in structure.
 */

/*Lower layer communication interface module for CanIf*/
#define PDUR_CANIF                            ((uint8)0x00)

/*Lower layer communication interface module for CanNm*/
#define PDUR_CANNM                            ((uint8)0x01)

/*Lower layer communication interface module for FrIf*/
#define PDUR_FRIF                             ((uint8)0x03)

/*Lower layer communication interface module for FrNm*/
#define PDUR_FRNM                             ((uint8)0x04)

/*Lower layer communication interface module for LinIf*/
#define PDUR_LINIF                            ((uint8)0x05)

/*Lower layer communication interface module for SoAdIf*/
#define PDUR_SOADIF                           ((uint8)0x06)

/*Lower layer communication interface module for Cdd*/
#define PDUR_CDDIF                            ((uint8)0x07)

/*Lower layer communication interface module for SecOC*/
#define PDUR_SECOC_LO                         ((uint8)0x07)

/*Lower layer communication interface module for UdpNm*/
#define PDUR_UDPNM                            ((uint8)0x0C)

/*
 * Lower layer transport protocol module
 * Macro's for ucModuleType present in structure.
 */
 
/*Lower layer transport protocol module for CanTp*/
#define PDUR_CANTP                            ((uint8)0x00)

/*Lower layer transport protocol module for J1939Tp*/
#define PDUR_J1939TP                          ((uint8)0x01)

/*Upper layer module for SomeIpTp*/
#define PDUR_SOMEIPTP                         ((uint8)0x10)

/*Upper layer module for LdCom*/
#define PDUR_LDCOM                            ((uint8)0x11)

/*Upper layer module for LdComTp*/
#define PDUR_LDCOMTP                          ((uint8)0x12)

/*Lower layer transport protocol module for FrTp*/
#define PDUR_FRTP                             ((uint8)0x03)

/*Lower layer transport protocol module for LinTp*/
#define PDUR_LINTP                            ((uint8)0x05)

/*Lower layer transport protocol module for SoAdTp*/
#define PDUR_SOADTP                           ((uint8)0x06)

/*Lower layer transport protocol module for Cdd*/
#define PDUR_CDDTP                            ((uint8)0x07)

/*Lower layer transport protocol module for DoIP*/
#define PDUR_DOIP                             ((uint8)0x0D)


/*
 * Upper layer module
 * Macro's for ucModuleType present in structure.
 */

/*Upper layer module for Com*/
#define PDUR_COM                              ((uint8)0x08)

/*Upper layer module for Dcm*/
#define PDUR_DCM                              ((uint8)0x09)

/*Upper layer module for IpduM*/
#define PDUR_IPDUM                            ((uint8)0x0A)

/*Upper layer module for Dbg*/
#define PDUR_DBG                              ((uint8)0x0B)

/*Upper layer module for Dlt*/
#define PDUR_DLT                              ((uint8)0x0C)

/*Upper layer module for Cdd*/
#define PDUR_CDD                              ((uint8)0x0C)

/*Upper layer module for SecOC*/
#define PDUR_SECOC_UP                         ((uint8)0x0C)

/*Upper layer module for J1939RM*/
#define PDUR_J1939RM                          ((uint8)0x0E)

/*Upper layer module for J1939RMIF*/
#define PDUR_J1939RMIF                        ((uint8)0x0E)

/*Upper layer module for J1939RMTP*/
#define PDUR_J1939RMTP                        ((uint8)0x0E)

/*Upper layer module for J1939DCM*/
#define PDUR_J1939DCM                         ((uint8)0x0F)


 
/*Lower layer IF type ID*/
#define PDUR_LOWERLAYER_CANIF                 ((uint8)0x00)

/* Upper Module type ID */
#define PDUR_UPPER_DCM                        ((uint8)0x00)

#define PDUR_UPPER_J1939DCM                   ((uint8)0x02)

#define PDUR_UPPER_SECOC                      ((uint8)0x04)

#define PDUR_UPPER_LDCOM                      ((uint8)0x06)

#define PDUR_UPPER_CDDTP                      ((uint8)0x07)



/* Value to check whether Gateway on the Fly is configured or not */
#define PDUR_GATEWAY_ONFLY_CONF               ((uint16)0xFFFE)

/* The following are the macros used for the Receive states in PduR for TP */
/* Reception yet to be started */
#define PDUR_RX_YETTOSTART                    ((uint8) 0x00)
/* Reception has been completed. */
#define PDUR_RX_COMPLETED                     ((uint8) 0x01)
/* PduR is waiting for an Acknowledgement */
#define PDUR_RX_ACKNOWLEDGE                   ((uint8) 0x02)
/* Reception has been started */
#define PDUR_RX_START                         ((uint8) 0x03)
/* Reception is in progress */
#define PDUR_RX_IN_PROGRESS                   ((uint8) 0x04)
/* TP transmit is called in Copy Rx data and TpTransmit is also */
#define PDUR_RX_TX_COMPLETED                  ((uint8) 0x05)
/* For Starting Reception process if requested length is zero*/
#define PDUR_RECEPTION_START                  ((uint8) 0x06)
/* Macro for undefined condition */
#define PDUR_MULTICAST_GATEWAY                ((uint32)0xFFFFFFFFU)

/*
 * Type definition for function pointer.
 */

 /* Typedefine for Interface RxIndication function */
typedef P2FUNC(void, PDUR_APPL_CODE,PduRIfReceiveFuncPtr)
  (PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pPduInfoptr);

/*Typedefine for Interface Trigger Transmit function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRIfTriggerTxFuncPtr)
  (PduIdType id,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) pPduInfoptr);

/*Typedefine for Interface TxConfirmation function*/
typedef P2FUNC(void, PDUR_APPL_CODE, PduRIfTxConfFuncPtr)
  (PduIdType id);

/*Typedefine for Interface transmit function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRIfTransmitFuncPtr)
  (PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pPduInfoptr);

/*Typedefine for Interface Cancel transmit function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRIfCancelTransmitFuncPtr)
  (PduIdType id);

/*Typedefine for Tp CopyTx Data function*/
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduRTpCopyTxDataFuncPtr)
  (PduIdType id, 
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) info,
  P2VAR(RetryInfoType, AUTOMATIC, PDUR_VAR) retry,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) Length);

/*Typedefine for TxConfirmation function*/
typedef P2FUNC(void, PDUR_APPL_CODE, PduRTpConfirmFuncPtr)
  (PduIdType id, NotifResultType Result);

/*Typedefine for Tp Cancel Reason function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRTpCancelFuncPtr)
  (PduIdType id);

/*Typedefine for RxTp Cancel Reason function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRRxTpCancelFuncPtr) 
  (PduIdType id);

/*Typedefine for Tp StartOf Reception function*/
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduRTpStReceptionFuncPtr)
  (PduIdType id, PduLengthType TpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr);

#if (PDUR_FOUR_ONE_ONE == STD_ON)
/*Typedefine for Tp StartOf Reception function*/
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduRTpStReceptionInfoFuncPtr)
  (PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) info,
  PduLengthType TpSduLength, 
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) bufferSizePtr);
#endif

/*Typedefine for Tp Copy RxData function*/
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduRTpCopyRxDataFuncPtr)
  (PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) info,
  P2VAR(PduLengthType, AUTOMATIC, PDUR_VAR) Length);

/*Typedefine for Tp Transmit function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRTpTransmitFuncPtr)
  (PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) pPduInfoptr);

/*Typedefine for Tp RxIndication function*/
typedef P2FUNC(void, PDUR_APPL_CODE, PduRTpReceiveFuncPtr)
  (PduIdType id, NotifResultType Result);

/*Typedefine for Tp Change Parameter function*/
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduRTpChangeParamFuncPtr)
  (PduIdType id,TPParameterType parameter, uint16 Value);

/*Typedefine for Rx Indication Callout function*/
typedef P2FUNC(boolean, PDUR_APPL_CODE, PduRRxIndCallOut)
  (PduIdType PduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_CONST) PduInfoPtr);

/* Structure for  PduR_FifoBuffer */

/* polyspace-begin MISRA-C3:D4.8 [Not a defect:Low] "No Impact of this rule violation" */
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
typedef struct 
{
  /* Read Index */
  uint8 ucRead;
  /* Write Index */
  uint8 ucWrite;
  /* Depth Index */
  uint8 ucDepth;
} PduR_FifoBuffer;
#endif
/* polyspace-end MISRA-C3:D4.8 [Not a defect:Low] "No Impact of this rule violation" */
/**
 * @typedef PduR_TxBuffer
 *
 * This structure is require to be generated in case of interface to interface
 *   gateway
 */
typedef struct 
{
  /* Index to PduInfoPtr Generation Tool should allocate pointer to
   PduInfoType. This parameter is used to store the data and length
   information for gatewayed PDU */
  P2VAR(PduInfoType, AUTOMATIC, PDUR_VAR) pPduInfoPtr;
  #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  /* Index to the FIFO RAM array  */
  P2VAR(PduR_FifoBuffer, AUTOMATIC, PDUR_VAR) pFifoBuffer;
  #endif
  #if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
  /* Depth of the Tx Buffer */
  uint8 ucFIFODepth;
  #endif

} PduR_TxBuffer;

/* Structure for Rx Indication Callout functions */
/* polyspace-begin MISRA-C3:D4.8 [Not a defect Justify with annotations] "Structure will be derefernenced based on Configuration" */
typedef struct 
{
  PduRRxIndCallOut pFuncPduRCallOut;
} PduR_RxIndicationCallOut;
/* polyspace-end MISRA-C3:D4.8 [Not a defect Justify with annotations] "Structure will be derefernenced based on Configuration" */

 /* PduR_LoGWRxIndication */
/* polyspace-begin MISRA-C3:D4.8 [Not a defect Justify with annotations] "Structure will be derefernenced based on Configuration" */
typedef struct 
{
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 usGroupMaskValue;
  #endif
/* Updated Length of PDU */
  PduLengthType ddPduLength;

  /* PDUR_GATEWAY_NOBUFFER and PDUR_UPPER_LAYER */
  uint16 usTxBufferIndex;

  /* TargetPduId. Generation tool should provide the handle id of the target
   *   module if configured. In case, handle id of the target module is not
   *   configured then the handle name should be considered */
  PduIdType ddTargetPduId;

  /* First two bits are set for type of Buffer*/
  /* 0x40 - Direct FIFO Buffer
   * 0x80 - TT -FIFO Buffer
   Rest six bits gives TargetIndex */

  uint8 ucTargetIndexBufType;

} PduR_LoGWRxIndication;
/* polyspace-end MISRA-C3:D4.8 [Not a defect Justify with annotations] "Structure will be derefernenced based on Configuration" */
/**
 * typedef PduR_LoRxIndication
 *
 * This structure is require to be generated in case of receive indication
 *   from interface
 */
typedef struct 
{
  #if(PDUR_IF_GATEWAY_OPERATION)
  P2CONST(PduR_LoGWRxIndication, AUTOMATIC, PDUR_CONST) pGWIfPdu;
  #endif
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  /* PduR group Mask Value for Pdu*/
  uint16 usGroupMaskValue;
  #endif
  /* Incase of non gateway ucTargetIndex shall contain target id*/
  #if (PDUR_FUN_IFRXINDICATION_SUPPORT == STD_ON)
  PduIdType ddUpTargetPduId;
  #endif
  /* Incase of non gateway ucTargetIndex shall point to function pointer index
   *   In case of gateway without multicast=> 0x40
   *   In case of gateway with multicast => 0x80 | no or route
   *   Index for Receive or Gateway  Or Multicast Gateway */
  uint8 ucTargetIndexOrRoutePDU;
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  /*Module type i.e. PDUR_<Msn>*/
  uint8 ucModuleType;
  #endif

  uint16 usRxLoIndCallOutIdx;
}PduR_LoRxInd;

/**
 * typedef PduR_MulticastTxPdu
 *
 * This structure is require to be generated in case of Multicast Tx Pdu
 */
typedef struct 
{
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 usGroupMaskValue;
  #endif
  /* TargetPduId. Generation tool should provide the handle id of the target
   * module if configured. In case, handle id of the target module is not
   * configured then the handle name should be considered */
  PduIdType ddTargetPduId;
  /* Target Index for If Transmit, If Rx Indication */
  uint8 ucTargetIndex;

} PduR_MulticastTxPdu;

/**
 * typedef PduR_UpTx
 *
 * This structure is require to be generated in case of Up Transmit (Com /IpduM)
*/
typedef struct 
{
  /* Pointer to Multicast Tx confirmation count */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) pRamArea;
  /* Pointer to MulticastTpPdu or MultiCastTxPdu structure */
  P2CONST(void, AUTOMATIC, PDUR_CONST) pMulticastTpOrTxPdu;
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 usGroupMaskValue;
  #endif
  /* In case of single cast will provide the handle id of the target
     module configured */
  PduIdType ddLoTargetPduId;
  /* This element indicates the frame type(Fra) - Tp or Interface
   * 6th bit will be set if the frame is Tp and 7th bit will be set
   * in case of multicast transmission. */
  uint8 ucFraTIOrNoOfRoute;
  /*
   * No of Tx confimations configured
   * Count of PduRTransmissionConfirmation
   */
  uint8 ucTxConfirmMask;

  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  /*Module type i.e. PDUR_<Msn>*/
  uint8 ucModuleType;
  #endif

} PduR_UpTx;

/**
 * typedef PduR_LoTxConfirmation
 *
 * This structure is require to be generated in case of transmit confirmation
  and trigger transmit from interface
*/
typedef struct 
{
  /* Pointer to UpTx array */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) pRamArea;

  /* Updated Length of PDU */
  PduLengthType ddPduLength;

  /* Pointer to Tx buffer */
  uint16 usTxBufferIndex;

  /* TargetPduId. Generation tool should provide the handle id of the target
  *  module if configured */
  /* Id need to be generated from PduRSrcPduRef of upper layer*/
  PduIdType ddTargetPduId;
  /*
  * Index for Transmit and Transmit Confirmation
  * In case of Gateway, ucTargetIndex shall be 0x40 | Index
  */
  uint8 ucTargetIndex;
  #if ((PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) || \
        (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))
  /* Type Of Buffer
     0x00: Single Buffer
     0x40: D-FIFO
     0x80: T-FIFO */
  uint8 ucBufferType;
  #endif
  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  /*Module type i.e. PDUR_<Msn>*/
  uint8 ucModuleType;
  #endif
  uint8 ucTxConfirmMask;

  /* 0 - Indicates confirmation is not configured for the specific destination
   1 - Indicates confirmation is configured for the specific destination */
  boolean blLoTxConfirmation;

  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 usGroupMaskValue;
  #endif
} PduR_LoTxConf;

/**
 * typedef PduR_TpBuffer
 * This structure is required to be generated in case of Tp to Tp gateway
 */

typedef struct 
{
  /* Data pointer */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) pSduPtr;
  /* Data Length */
  PduLengthType ddPduLength;

  #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)

  /* Requested length */
  PduLengthType ddReqLength;

  /* Length configured for Gateway On Fly */
  PduLengthType ddOnFlyLength;

  /* Length of copied length */
  PduLengthType ddCopiedLength;
  #endif

  /* Confirmation status */
  uint8 ucTxConfStatus;
}PduR_TpBuffer;

/* Multicast Gateway Tp PDU */
#if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
typedef struct 
{
  /* Result */
  NotifResultType ddResult;
  /* Confirmation Status */
  uint8 ucConfStatus;
}PduR_MulticastTpInfo;
#endif
/* Multicast Gateway Tp PDU */
typedef struct 
{
  /* This pointer gives index to the TpBuffer */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) pRamArea;
  /* PduR group Mask Value for Pdu*/
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 usGroupMaskValue;
  #endif
  #if (PDUR_GATEWAY_ONFLY_SUPPORT == STD_ON)
  /* Tp Threshold value */
  uint16 usTpThreshold;
  #endif
  /* TargetPduId. Generation tool should provide the handle id of the target
    module if configured. */
  PduIdType ddTargetPduId;
  /* Target Index for Tp Transmit, Receive Indication
    if upper layer OR with 0x80 */
  uint8 ucTargetIndex;
  /* Mask for Tx Confirmation */
  uint8 ucTxCnfrmStsMask;
} PduR_GWRxTpPdu;

/* Structure for Tp Rx Indication */
typedef struct 
{
  /* Tp Receive Status  */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) pRamArea;
  #if (PDUR_TP_GATEWAY_OPERATION == STD_ON)
  P2CONST(PduR_GWRxTpPdu, AUTOMATIC, PDUR_CONST) pGWRxTpPdu;
  #endif
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  /* PduR group Mask Value for Pdu*/
  uint16 usGroupMaskValue;
  #endif
  /* Target Layer ID */
  PduIdType ddUpTargetPduId;
  /* Target Index for Tp Transmit
    0x40 in case of Singlecast Gateway
    0x80 | no of route in case of multicast gateway */
  uint8 ucTargetIndexOrNoOfRoute;

  /* Source Index for TpChangeparameter or cancel receive */
  #if((PDUR_FUN_CHANGEPARAMETER_SUPPORT == STD_ON) || \
      (PDUR_CANCEL_RECEIVE_SUPPORT == STD_ON))
  uint8 ucSourceIndex;
  #endif
  #if(PDUR_DEV_ERROR_DETECT == STD_ON)

  /* Module type i.e. PDUR_<Msn> */
  uint8 ucModuleType;
  #endif
  #if(PDUR_SECOC_SUPPORT == STD_ON)
  /*true if upper layer is SECOC*/
  boolean blupperlayer;
  #endif

  uint16 usRxTpIndCallOutIdx;
}PduR_TpRxIndication;

/**
 * typedef PduR_MulticastTpPdu
 *
 * This structure is require to be generated in case of Tp Multicast
 */
#if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON) 
typedef struct 
{
  /* Multicast Tp Info Index */
  P2VAR(PduR_MulticastTpInfo, AUTOMATIC, PDUR_VAR) pMulticastTpInfo;
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
 /* PduR group Mask Value for Pdu*/
  uint16 usGroupMaskValue;
  #endif

  /* ddTargetPduId. Generation tool should provide the handle id of the target
    module configured. */
  PduIdType ddTargetPduId;

  /* Target Index for Tp Transmit, Tp Cancellation, Tp Change Parameter */
  uint8 ucTargetIndex;
} PduR_MulticastTpPdu;
#endif

/* Structure for Tp Copy Tx Buffer */
typedef struct 
{
  #if (PDUR_MULTICAST_TOTXTP_SUPPORT == STD_ON)
  P2VAR(PduR_MulticastTpInfo, AUTOMATIC, PDUR_VAR) pMulticastTpInfo;
  #endif
  #if(PDUR_TP_GATEWAY_OPERATION == STD_ON)
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) pRamArea;
  #endif
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  /* PduR group Mask Value for Pdu*/
  uint16 usGroupMaskValue;
  #endif
  /* TargetPduId handle id of the target module configured,
   Id need to be generated from PduRSrcPduRef of upper layer */
  PduIdType ddUpTargetPduId;
  /* 1. Target Index in case Non_Gateway case
     2. 0x40 | Target index in case of singlecast gateway
     3. 0x80 | Target index in case of multicast gateway */
  uint8 ucTargetIndex;

  /* Mask for Tx Confirmation */
  uint8 ucTxCnfrmStsMask;

  #if (PDUR_DEV_ERROR_DETECT == STD_ON)
  /*Module type i.e. PDUR_<Msn>*/
  uint8 ucModuleType;
  #endif
} PduR_TpCopyTxDataBuf;

/* Structure for Transmit functions */
typedef struct 
{
  PduRIfTransmitFuncPtr pTargetLayer;
} PduR_IfTransmitFun;

/* Structure for Transmit cancel functions */
typedef struct 
{
  PduRIfCancelTransmitFuncPtr pTargetLayer;
} PduR_IfCancelTransmitFun;

/* Structure for If Receive functions */
typedef struct 
{
  PduRIfReceiveFuncPtr pTargetLayer;
} PduR_IfReceive;

/* Structure for If Trigger Transmit functions */
typedef struct 
{
  PduRIfTriggerTxFuncPtr pTargetLayer;
} PduR_IfTriggerTx;

/* Structure for If Confirmation functions */
typedef struct 
{
  PduRIfTxConfFuncPtr pTargetLayer;
} PduR_IfConfirmation;

/* Structure for Transmit functions */
typedef struct 
{
  PduRTpTransmitFuncPtr pTargetLayer;
} PduR_TpTransmitFun;

/* Structure for Tp Receive functions */
typedef struct 
{
  PduRTpReceiveFuncPtr pTargetLayer;
} PduR_TpReceive;

/* Structure for Tp Confirmation functions */
typedef struct 
{
  PduRTpConfirmFuncPtr pTargetLayer;
} PduR_TpConfirmation;

/* Structure for Tp Cancellation functions */
typedef struct 
{
  PduRTpCancelFuncPtr pTargetLayer;
} PduR_TpCancellation;

/* Structure for Rx Tp Cancellation functions */
typedef struct 
{
  PduRRxTpCancelFuncPtr pTargetLayer;
} PduR_RxTpCancellation;

/* Structure for Tp Changeparameter functions */
typedef struct 
{
  PduRTpChangeParamFuncPtr pTargetLayer;
} PduR_TpChangeparameter;

/* Structure for Tp StartOfReception functions */
typedef struct 
{
  PduRTpStReceptionFuncPtr pTargetLayer;
} PduR_TpStartOfReception;

#if (PDUR_FOUR_ONE_ONE == STD_ON)
/* Structure for Tp StartOfReceptionInfo functions */
typedef struct 
{
  PduRTpStReceptionInfoFuncPtr pTargetLayer;
} PduR_TpStartOfReceptionInfo;
#endif
/* Structure for Tp CopyRxData functions */
typedef struct 
{
  PduRTpCopyRxDataFuncPtr pTargetLayer;
} PduR_TpCopyRxData;

/* Structure for Tp CopyTxData functions */
typedef struct 
{
  PduRTpCopyTxDataFuncPtr pTargetLayer;
} PduR_TpCopyTxData;

typedef signed int PduR_PtrType;

/*This is an array of function pointers of <Lo>_Transmit*/
#if (PDUR_TOTAL_COUNT_IF_TRANSMIT > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_IfTransmitFun, PDUR_CONST)
                            PduR_GaaIfTransmitService[PDUR_TOTAL_COUNT_IF_TRANSMIT];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Lo>_CancelTransmit*/
#if (PDUR_TOTAL_COUNT_IF_CANCEL_TRANSMIT > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_IfCancelTransmitFun, PDUR_CONST)
                      PduR_GaaIfCancelTransmitService[PDUR_TOTAL_COUNT_IF_CANCEL_TRANSMIT];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_TriggerTransmit*/
#if (PDUR_TOTAL_COUNT_IF_TRIGGER > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_IfTriggerTx, PDUR_CONST)
                PduR_GaaIfTriggerTransmit[PDUR_TOTAL_COUNT_IF_TRIGGER];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_RxIndication*/
#if (PDUR_TOTAL_COUNT_IF_RECEIVE > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_IfReceive, PDUR_CONST) 
                        PduR_GaaIfReceive[PDUR_TOTAL_COUNT_IF_RECEIVE];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_TxConfirmation.*/
#if (PDUR_TOTAL_COUNT_IF_CONFIRMATION > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_IfConfirmation, PDUR_CONST)
                    PduR_GaaIfConfirmation[PDUR_TOTAL_COUNT_IF_CONFIRMATION];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <LoTp>_Transmit.*/
#if (PDUR_TOTAL_COUNT_TP_TRANSMIT > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpTransmitFun, PDUR_CONST)
                            PduR_GaaTpTransmitService[PDUR_TOTAL_COUNT_TP_TRANSMIT];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_StartOfReception*/
#if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpStartOfReception, PDUR_CONST)
                            PduR_GaaTpStartOfReception[PDUR_TOTAL_COUNT_TP_UP_RX];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_StartOfReception*/
#if (PDUR_FOUR_ONE_ONE == STD_ON)
#if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpStartOfReceptionInfo, PDUR_CONST)
PduR_GaaTpStartOfReceptionInfo[PDUR_TOTAL_COUNT_TP_UP_RX];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

/*This is an array of function pointers of <Up>_RxIndication*/
#if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpReceive, PDUR_CONST)
                                      PduR_GaaTpReceive[PDUR_TOTAL_COUNT_TP_UP_RX];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_TxConfirmation.*/
#if (PDUR_TOTAL_COUNT_TP_UP_TX > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpConfirmation, PDUR_CONST)
                                PduR_GaaTpConfirmation[PDUR_TOTAL_COUNT_TP_UP_TX];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <LoTp>_CancelTransmit.*/
#if (PDUR_TOTAL_COUNT_TP_CANCEL_TRANSMIT > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpCancellation, PDUR_CONST)
                          PduR_GaaTpCancellation[PDUR_TOTAL_COUNT_TP_CANCEL_TRANSMIT];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <LoTp>_CancelReceive.*/
#if (PDUR_TOTAL_COUNT_TP_CANCEL_RECEIVE > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_RxTpCancellation, PDUR_CONST)
                          PduR_GaaTpCancelReceive[PDUR_TOTAL_COUNT_TP_CANCEL_RECEIVE];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <LoTp>_ChangeParameter*/
#if (PDUR_TOTAL_COUNT_TP_CHG_PRM > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpChangeparameter, PDUR_CONST)
                        PduR_GaaTpChangeparameter[PDUR_TOTAL_COUNT_TP_CHG_PRM];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_CopyRxData.*/
#if (PDUR_TOTAL_COUNT_TP_UP_RX > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpCopyRxData, PDUR_CONST)
                                PduR_GaaTpCopyRxData[PDUR_TOTAL_COUNT_TP_UP_RX];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array of function pointers of <Up>_CopyTxData.*/
#if (PDUR_TOTAL_COUNT_TP_UP_TX > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpCopyTxData, PDUR_CONST)
                                  PduR_GaaTpCopyTxData[PDUR_TOTAL_COUNT_TP_UP_TX];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is the global structure array of TxBuffer*/
#if (PDUR_TX_BUFFER_INDEX_COUNT > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TxBuffer, PDUR_CONST)
                                  PduR_GaaTxBuffer[PDUR_TX_BUFFER_INDEX_COUNT];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is the global structure array of the If and IpduM Rx Indication.*/

#if(PDUR_LO_RXINDICATION_MAXPDUID > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_LoRxInd, PDUR_CONST)
                          PduR_GaaLoRxIndication[PDUR_LO_RXINDICATION_MAXPDUID];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is the global structure array of the Com and IpduM Transmit.*/
#if(PDUR_UP_MAXPDUID > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_UpTx, PDUR_CONST) PduR_GaaUpTransmit[PDUR_UP_MAXPDUID];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is the global structure array of the CanIf, FrIf, LinIf and IpduM Tx
Confirmation.*/
#if(PDUR_LO_TXCONFIRMATION_MAXPDUID > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_LoTxConf, PDUR_CONST)
                      PduR_GaaLoTxConfirmation[PDUR_LO_TXCONFIRMATION_MAXPDUID];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is the global structure array of the Tp Rx Indication.*/
#if(PDUR_TP_RXINDICATION_MAXPDUID > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpRxIndication, PDUR_CONST)
                          PduR_GaaTpRxIndication[PDUR_TP_RXINDICATION_MAXPDUID];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*This is an array which consists of the information regarding the data to be
copied to the lower layer in case of TP.*/
#if(PDUR_TP_TXCONFIRMATION_MAXPDUID > PDUR_ZERO)
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_TpCopyTxDataBuf, PDUR_CONST)
                      PduR_GaaTpCopyTxDataBuf[PDUR_TP_TXCONFIRMATION_MAXPDUID];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*global variable is used as an array of buffer configured for Tp.*/
#if(PDUR_TP_NO_BUFFER_COUNT > PDUR_ZERO)
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduR_TpBuffer, PDUR_VAR)
                                      PduR_GaaTpBuffer[PDUR_TP_NO_BUFFER_COUNT];
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

/* global variable is used as an array of FIFO buffer for IF.*/
#if(PDUR_FIFO_BUFFER_INDEX_COUNT > PDUR_ZERO)
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(PduR_FifoBuffer, PDUR_VAR)
                              PduR_GaaFifoBuffer[PDUR_FIFO_BUFFER_INDEX_COUNT];
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif
#endif /* End of if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON) */

#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
#if (PDUR_ROUTINGPATH_GROUP_ARRAY_SIZE > PDUR_ZERO)
#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern const VAR(uint8, PDUR_CONST) PduR_GaaRoutingPathGroup[PDUR_ROUTINGPATH_GROUP_ARRAY_SIZE];
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(PduR_RxIndicationCallOut, AUTOMATIC, PDUR_CONST) 
                              PduR_GpRxLoIndicationUserCallout;
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern P2CONST(PduR_RxIndicationCallOut, AUTOMATIC, PDUR_CONST) 
                              PduR_GpRxTpIndicationUserCallout;
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/*******************************************************************************
**                      Variable for Library                                  **
*******************************************************************************/
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "Memmap.h"		
extern CONST(PduR_RoutingPathGroupIdType, PDUR_CONST) PduR_Max_RoutingPath_Group_ID;

extern CONST(PduIdType, PDUR_CONST) 	PduR_Total_No_Of_TP_RxPdu;

extern CONST(PduIdType, PDUR_CONST) 	PduR_Lo_RxIndication_MaxPduID;

extern CONST(PduIdType, PDUR_CONST) 	PduR_Lo_TxConfirmation_MaxPduID;

extern CONST(PduIdType, PDUR_CONST) 	PduR_Up_MaxPduID;

extern CONST(PduLengthType, PDUR_CONST) PduR_TP_Buffer_Max_Length;

extern CONST(PduIdType, PDUR_CONST) 	PduR_TP_TxConfirmation_MaxPduID;

extern CONST(PduIdType, PDUR_CONST) 	PduR_TP_RxIndication_MaxPduID;

extern CONST(uint16, PDUR_CONST) PduR_TP_Buffer_Index_Count;

extern CONST(uint16, PDUR_CONST) 	PduR_FIFO_Buffer_Index_Count;
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "Memmap.h"

#endif /* #ifndef PDUR_PCTYPES_H */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
