/*******************************************************************************
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_Cbk.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Callback functions implementation for CanTp module.           **
**              CanTp_RxIndication                                            **
**              CanTp_TxConfirmation                                          **
**              CanTp_RxDetCheck                                              **
**              CanTp_CbkTxDetCheck                                           **
**              CanTp_ProcessRxData                                           **
**              CanTp_ProcessRxCF                                             **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.11.2    17-May-2021   NguyenTD3      Redmine #28737                      **
** 1.11.1    12-Jan-2021   SM Kwon        Redmine #27640                      **
** 1.10.2    31-Jul-2020   SM Kwon        Reddmine #24646, #25248             **
** 1.10.1    07-Oct-2019   SM Kwon        Redmine #19530, #19617              **
** 1.10.0    25-Sep-2019   SM Kwon        Redmine #19445                      **
** 1.9.0     30-Jul-2019   SM Kwon        Redmine #17748                      **
** 1.8.1     12-Mar-2019   SM Kwon        Redmine #15962, #16463, #16559      **
** 1.8.0     31-Jan-2018   Lim Jong Sun   Redmine #11554                      **
** 1.7.11    04-Jan-2018   Lim Jong Sun   Redmine #11124, #11125              **
** 1.7.10    24-Apr-2015   Lim Jong Sun   Redmine #8152, #8001                **
** 1.7.9     23-Mar-2017   Lim Jong Sum   Redmine #7881                       **
** 1.7.8     31-May-2016   Lim Jong Sun   Redmine #5084, #4409                **
** 1.7.7     02-May-2016   Lim Jong Sun   Redmine #4803                       **
** 1.7.4     23-Dec-2015   Lim Jong Sun   Redmine #3277                       **
** 1.7.3     31-Aug-2015   Lim Jong Sun   Redmine #2788                       **
** 1.0.5     25-Aug-2015   Lim Jong Sun   Redmine #2788                       **
** 1.0.1     20-Jun-2013   Lim Jong Sun   Library Release Version             **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp.h"                /* CanTp Module Header File */
#include "CanTp_Cbk.h"            /* CanTp Cbk Header File */
#include "SchM_CanTp.h"           /* SchM Header File */
#include "CanTp_PCTypes.h"        /* CanTp PCTypes Header File */
#include "CanTp_RxInternal.h"     /* CanTp RxInternal Header File */
#include "CanTp_TxInternal.h"     /* CanTp TxInternal Header File */
#include "CanTp_Ram.h"            /* CanTp Global RAM variables header file */
#include "PduR_CanTp.h"           /* PduR header for CAN TP */
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
#include "Det.h"                  /* DET header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANTP_CBK_C_AR_RELEASE_MAJOR_VERSION    4
#define CANTP_CBK_C_AR_RELEASE_MINOR_VERSION    0
#define CANTP_CBK_C_AR_RELEASE_REVISION_VERSION 3

/* CANTP software version information */
#define CANTP_CBK_C_SW_MAJOR_VERSION            1
#define CANTP_CBK_C_SW_MINOR_VERSION            11

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANTP_AR_RELEASE_MAJOR_VERSION != CANTP_CBK_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp_Cbk.c : Mismatch in Specification Major Version"
#endif
#if (CANTP_AR_RELEASE_MINOR_VERSION != CANTP_CBK_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp_Cbk.c : Mismatch in Specification Minor Version"
#endif
#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_CBK_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp_Cbk.c : Mismatch in Specification Revision Version"
#endif
#if (CANTP_SW_MAJOR_VERSION != CANTP_CBK_C_SW_MAJOR_VERSION)
#error "CanTp_Cbk.c : Mismatch in Software Major Version"
#endif
#if (CANTP_SW_MINOR_VERSION != CANTP_CBK_C_SW_MINOR_VERSION)
#error "CanTp_Cbk.c : Mismatch in Software Minor Version"
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
#if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) && (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, CANTP_CODE) CanTp_ProcessRxCF(PduIdType LddRxSduId, P2VAR(
    uint8, AUTOMATIC, CANTP_VAR) LpRxSrcPtr, P2CONST(PduInfoType,
    AUTOMATIC, CANTP_CONST) PduInfoPtr, CanTp_ChannelType LddChannel);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) && (STD_ON == CANTP_RX_NSDU) */

#if (STD_ON == CANTP_DEV_ERROR_DETECT)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(StatusType, CANTP_CODE) CanTp_RxDetCheck(PduIdType RxPduId, P2CONST(
    PduInfoType, AUTOMATIC, CANTP_VAR) LpPduInfoPt);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, CANTP_CODE) CanTp_CbkTxDetCheck(PduIdType TxPduId);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */

#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_ProcessRxData(PduIdType RxSduId, PduIdType
  RxPduId, P2CONST( PduInfoType, AUTOMATIC, CANTP_CONST) PduInfoPtr, VAR(
    uint8, AUTOMATIC) LucBytePos);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RxIndication                                  **
**                                                                            **
** Service ID           : 0x42                                                **
**                                                                            **
** Description          : This function is called by the CAN Interface after  **
**                        successful reception of a Rx CAN L-PDU.             **
**                        This callback service is called by the CanIf and    **
**                        implemented by the CanTp                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : RxPduId                                             **
**                        PduInfoPtr                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                 CanTp_GaaRxExtPdus,        **
**                                                 CanTp_GaaRxExtFcPdus,      **
**                                                 CanTp_GaaNSaOrNAeSduMapping**
**                 Cantp_Rx_Fcpdu_start      **
**                        Function(s) invoked    : Det_ReportError            **
**                                                 CanTp_RxBinarySearch       **
**                                                 CanTp_ProcessRxFc          **
**                                                 CanTp_RxDetCheck           **
*******************************************************************************/
#if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) || (STD_ON == CANTP_RX_NSDU))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/*
 *   MISRA Rule         : 16.7
 *   Message            : The object accessed by the pointer PduInfoPtr is not
 *                     modified in this function.
 *   Reason             : Since the AUTOSAR SWS defined PduInfoPtr as P2VAR.
 *   Verification       : However, part of the code is verified manually
 *                     and its not having any impact.
 */
FUNC(void, CANTP_CODE) CanTp_RxIndication(PduIdType RxPduId, P2CONST(
    PduInfoType, AUTOMATIC, CANTP_APPL_CONST) PduInfoPtr)
{
  #if ((CANTP_RX_NSDU == STD_ON) || (CANTP_TX_EXTENDED_ADDRESS == STD_ON)\
  || (CANTP_TX_MIXED_ADDRESS == STD_ON) ||\
  (CANTP_RX_EXTENDED_ADDRESS == STD_ON) || (CANTP_RX_MIXED_ADDRESS == STD_ON)\
  || (CANTP_DEV_ERROR_DETECT == STD_ON))
  P2CONST(CanTp_RxExtPdus, AUTOMATIC, CANTP_CONST) LpExtPduPtr;
  #endif
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS)\
  || (STD_ON == CANTP_TX_MIXED_ADDRESS))
  P2CONST(CanTp_RxNSaOrNAeSduMapping, AUTOMATIC, CANTP_CONST)
  LpSduMapPtr;
  #endif
  #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) LpRxSrcPtr;
  #endif
  #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_TX_MIXED_ADDRESS) || (STD_OFF == CANTP_SINGLE_CHANNEL) ||\
  (CANTP_RX_NSDU == STD_ON) ||((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)))
  PduIdType LddRxSduId = (PduIdType)CANTP_ZERO;
  #endif
  #if ((STD_ON == CANTP_RX_NSDU) || ((STD_ON == CANTP_TX_NSDU) &&\
  (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)))
  uint8 LucBytePos;
  #endif
  #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
  uint8 LucFrame;
  #endif
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS)\
  || (STD_ON == CANTP_TX_MIXED_ADDRESS))
  boolean LblInvalidTAFlag;
  #endif
  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  boolean LblDetErrorFlag;
  #endif
  /* #8001 */
  #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
  #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)
  P2CONST(CanTp_RxNsduStatic, AUTOMATIC, CANTP_CONST) LpRxNSdu;
  #endif
  #endif
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS)\
  || (STD_ON == CANTP_TX_MIXED_ADDRESS))
  LblInvalidTAFlag = CANTP_FALSE;
  #endif
  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  LblDetErrorFlag = CanTp_RxDetCheck(RxPduId, PduInfoPtr);

  /* Check if no development errors has occurred */
  if (CANTP_FALSE == LblDetErrorFlag)
  #endif /* #if(STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    #if ((CANTP_RX_NSDU == STD_ON) || (CANTP_TX_EXTENDED_ADDRESS == STD_ON)\
    || (CANTP_TX_MIXED_ADDRESS == STD_ON) ||\
    (CANTP_RX_EXTENDED_ADDRESS == STD_ON) || (CANTP_RX_MIXED_ADDRESS == STD_ON)\
    || (CANTP_DEV_ERROR_DETECT == STD_ON))
    #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
    /* Get the RxNSdu structure pointer for Addressing Mode */
    LpExtPduPtr = &CanTp_GaaRxExtPdus[RxPduId];
    #endif /* End of if ((STD_ON == CANTP_RX_NSDU) ||*/
    #endif /*   (STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||
            *   (CANTP_TX_MIXED_ADDRESS) ||
            *   (STD_ON == CANTP_RX_EXTENDED_ADDRESS) || (CANTP_RX_MIXED_ADDRESS
            * ==
            *   STD_ON) || (STD_ON == CANTP_DEV_ERROR_DETECT)) */
    #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP,OBAI [Not a defect: Justified] "Array index in range" */	
    LucBytePos = CanTp_GaaBytePos[LpExtPduPtr->ucAddressingMode];
    #endif
    #if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
    /* Get the Frame type */
    /* polyspace<MISRA-C3:D4.14 :: Not a defect Justified> Pointer is not a NULL and valid */
    LpRxSrcPtr = PduInfoPtr->SduDataPtr;

    LucFrame = (uint8)((LpRxSrcPtr[LucBytePos]) & (uint8)CANTP_PCI_MASK);
    #endif
    
    #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
    /* Check if the frame is a flow control frame */
    if ((uint8)CANTP_FC_PCI == LucFrame)
    {
      #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS)\
      || (STD_ON == CANTP_TX_MIXED_ADDRESS))

      /* Initialize Pdu structure for flow control frame */
      LpExtPduPtr = &CanTp_GaaRxExtFcPdus[RxPduId -
                      (PduIdType)Cantp_Rx_Fcpdu_start];
      #endif
    } /* End of if (CANTP_FC_PCI == LucFrame) */
    else
    #endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */
    {
      #if ((STD_ON == CANTP_RX_NSDU) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS)\
      || (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
      (STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
      (STD_ON == CANTP_RX_MIXED_ADDRESS))

      /* Initialize Pdu structure for normal frame */
      LpExtPduPtr = &CanTp_GaaRxExtPdus[RxPduId];
      #endif 
    }
    #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS)\
    || (STD_ON == CANTP_TX_MIXED_ADDRESS))
    /* Check if the requested Pdu is configured for extended addressing */
    /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if (LpExtPduPtr->ucAddressingMode != (uint8)CANTP_STANDARD_ADDRESS)
    {
      /* Check if more than one NPdus are extended */
      if (LpExtPduPtr->ddNoOfPdusOrSduId != (PduIdType)CANTP_ONE)
      {
        /* Search the Nsdu index based on the unique combination of NPduId and
         *   N_AI */
        LpSduMapPtr = CanTp_RxBinarySearch(
                         &CanTp_GaaNSaOrNAeSduMapping[LpExtPduPtr->ddRxNSaOrNAeSduMapIndex],
                         (uint8)(LpExtPduPtr->ddNoOfPdusOrSduId), *(PduInfoPtr->SduDataPtr));

        /* Check if requested Pdu has no NSA mapping. */
        if (NULL_PTR == LpSduMapPtr)
        {
          LblInvalidTAFlag = CANTP_TRUE;
          LddRxSduId = (PduIdType)CANTP_ZERO;
          #if (STD_ON == CANTP_DEV_ERROR_DETECT)

          /* Report to DET */
          (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
            CANTP_RXINDICATION_SID, CANTP_E_INVALID_RX_ID);
          LblDetErrorFlag = CANTP_TRUE;
          #endif
        } /* End of if (NULL_PTR == LpSduMapPtr) */
        else
        {
          /* Initialize RxNSDuId */
          LddRxSduId = LpSduMapPtr->ddSduIndex;
        }
      } /* if(LpExtPduPtr->ddNoOfPdusOrSduId != CANTP_ONE) */
      else
      {
        /* Access the address of the structure which contains the NSDU index */
        LpSduMapPtr = &CanTp_GaaNSaOrNAeSduMapping
                      [LpExtPduPtr->ddRxNSaOrNAeSduMapIndex];

        /* Initialize RxNSDuId */
        /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
        LddRxSduId = LpSduMapPtr->ddSduIndex;
      } /* End of else */
    } /* Rx Sdu is configured for extended address */
    else
    {
      /* Initialize Receive NSDu Id If Receive pdu is not configured for
       *   extended address */
      LddRxSduId = LpExtPduPtr->ddNoOfPdusOrSduId;
    }
    /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    #elif (STD_ON == CANTP_RX_NSDU)

    /* Initialize Receive NSDu Id If Receive pdu is not configured for
     *   extended address */
    LddRxSduId = LpExtPduPtr->ddNoOfPdusOrSduId;
    #endif /* #if(STD_ON == CANTP_EXTENDED_ADDRESS) */

    #if (STD_ON == CANTP_DEV_ERROR_DETECT)
    #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS)\
    || (STD_ON == CANTP_TX_MIXED_ADDRESS))
    /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justify with annotations] "condition will be executed based on the configured values" */
    if (CANTP_FALSE == LblDetErrorFlag)
    #endif
    #endif /* #if(STD_ON == CANTP_DEV_ERROR_DETECT) */
    {
      #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
      (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
      (STD_ON == CANTP_TX_EXTENDED_ADDRESS) || (STD_ON ==\
                                                CANTP_TX_MIXED_ADDRESS))

      /* Check if requested Pdu has NSA mapping. */
      /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "condition will be executed based on the configured values" */
      if (CANTP_FALSE == LblInvalidTAFlag)
      #endif /* End of if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||
              *(STD_ON == CANTP_RX_MIXED_ADDRESS) || \
              *   (STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
              *   (STD_ON == CANTP_TX_MIXED_ADDRESS)) */
      {
        #if ((STD_ON == CANTP_TX_NSDU) &&\
        (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))

        /* Check that received frame is a FC frame or not */
        if ((uint8)CANTP_FC_PCI == LucFrame)
        {  
          /* #8001 */
          #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)
          /* Get the pointer to current TxNSdu */
          LpRxNSdu = &CanTp_GaaRxSduStatic[LddRxSduId];

          /* If the RxNsdu supports Functional addressing */
          /* polyspace +2 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
          /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
          if ((uint8)CANTP_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType)
          {
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            /* Report to DET */          
            (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
              CANTP_RXINDICATION_SID, CANTP_E_PARAM_ID);
            #endif 
          }
          else /* End of if (CANTP_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType) */
          #endif
          {
            /* If frame is Flow control then process it for RxFc */
            CanTp_ProcessRxFc(LddRxSduId, LpRxSrcPtr);
          }
        } /* End of if (CANTP_FC_PCI == LucFrame) */
        else /* Received frame is not a FC frame */
        #endif /* #if(STD_ON == CANTP_TX_NSDU) && \
                *   (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)*/
        {
          #if (STD_ON == CANTP_RX_NSDU)
          #if (((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
          (STD_ON == CANTP_RX_MIXED_ADDRESS)) ||\
          ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) || (STD_ON ==\
                                                     CANTP_TX_MIXED_ADDRESS)))
          LucBytePos = (uint8)CanTp_GaaBytePos[LpExtPduPtr->ucAddressingMode];
          #else

          /* Get the N_PCI position */
          LucBytePos = (uint8)CANTP_ZERO;
          #endif
          CanTp_ProcessRxData(LddRxSduId, RxPduId, PduInfoPtr, LucBytePos);
          #endif /* End of if (STD_ON == CANTP_RX_NSDU) */
        } /* Received frame is not a FC frame */
      } /* if(LblInvalidTAFlag == CANTP_FALSE) */
    } /*
       * if(LblDetErrorFlag == CANTP_FALSE)
       **#endif
       */
  } /* if(LblDetErrorFlag == CANTP_FALSE) */
} /* End of CanTp_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType,
   * AUTOMATIC, CANTP_APPL_CONST) PduInfoPtr) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) || (CANTP_RX_NSDU
        *== STD_ON)) */

/*******************************************************************************
** Function Name        : CanTp_ProcessRxData                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the CanTp_RxIndication   **
**                        to process the Rx data frame received               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : RxSduId                                             **
**                        PduInfoPtr                                          **
**                        LpExtPduPtr                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblDetErrFlag                                       **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     :   Cantp_Channel_Id                       **
**                    CanTp_GaaRxSduDynamic    **
**                    Cantp_Maxno_Rx_Npdu      **
**                        Function(s) invoked    : CanTp_RequestRxBuffer      **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_ProcessRxData(PduIdType RxSduId, PduIdType RxPduId,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_CONST) PduInfoPtr, VAR(
    uint8, AUTOMATIC) LucBytePos)
{
  #if (STD_ON == CANTP_RX_NSDU)
  P2CONST(CanTp_RxNsduStatic, AUTOMATIC, CANTP_CONST) LpRxNSdu;
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  #endif
  #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
  P2CONST(CanTp_RxNSduDynamic, AUTOMATIC, CANTP_CONST) LpRxNSduDyna;
  #endif
  #if (STD_ON == CANTP_RX_NSDU)
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) LpRxSrcPtr;
  CanTp_ChannelType LddChannel;
  #endif
  #if (STD_ON == CANTP_RX_NSDU)
  uint8 LucReceivedDlc;
  uint8 LucChannelState;
  uint8 LucPci;
  uint8 LucFrame;
  uint32 LddDecodedSduLength;
  uint8 LucFfDlFirstByteLowNibble;
  #endif
  #if (STD_ON == CANTP_RX_NSDU)
  boolean LblDlcErrorFlag;
  boolean LblNewFrameFlag;
  #endif

  uint8 LucCpyBytePos = LucBytePos;
	
  #if (STD_ON == CANTP_RX_NSDU)
  LpRxSrcPtr = PduInfoPtr->SduDataPtr;

  /* Get the Frame type */
  LucFrame = (uint8)((LpRxSrcPtr[LucCpyBytePos]) & (uint8)CANTP_PCI_MASK);

  /* Set the status of the new frame received to the default */
  LblNewFrameFlag = CANTP_FALSE;
  #endif /* End of if (STD_ON == CANTP_RX_NSDU) */
  #if (STD_ON == CANTP_RX_NSDU)

  /* Initialize RxNSdu static structure according to RxNSduId */
  /* polyspace +7 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
  LpRxNSdu = &CanTp_GaaRxSduStatic[RxSduId];
  #if (STD_OFF == CANTP_SINGLE_CHANNEL)

  /* Initialize Channel according to RXNSDu structure channel */
  /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
  LddChannel = LpRxNSdu->ddChannelId;
  #else
  /* Initialize Channel according to RXNSDu structure channel */
  LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
  #endif
  /* Initialize Channel RAM structure according to addressing mode */
  LpChannelRam = &CanTp_GaaChannelRam[LddChannel];

  /* Initialize Channel state according RAM structure Channel */
  LucChannelState = LpChannelRam->ucChannelState;

  LddDecodedSduLength = 0;

  /* Get the N_PCI position */
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS))
  /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "condition will be executed based on the configured values" */
  if (LpRxNSdu->ucAddressingMode != (uint8)CANTP_STANDARD_ADDRESS)
  {
    /* Initialize byte position according structure addressing mode */
    LucCpyBytePos = (uint8)CANTP_ONE;
  }
  #endif /* End of if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||
          * (STD_ON == CANTP_RX_MIXED_ADDRESS)) */

  /* Update the data source pointer address */
  LpRxSrcPtr = &LpRxSrcPtr[LucCpyBytePos];

  /* Decode the N_PCI byte */
  LucPci = (uint8)((*LpRxSrcPtr) & (uint8)CANTP_PCI_MASK);

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  #if(CANTP_FD_SUPPORT == STD_ON)
  if(CANTP_SIXTYFOUR < PduInfoPtr->SduLength)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_PROCESSRXDATA_SID, CANTP_E_INVALID_RX_LENGTH);
  }
  #else
  if(CANTP_EIGHT < PduInfoPtr->SduLength)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_PROCESSRXDATA_SID, CANTP_E_INVALID_RX_LENGTH);
  }
  #endif /* (CANTP_FD_SUPPORT == STD_ON) */
  else
  #endif /* (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    /* Get the received data length of the PDU */
    LucReceivedDlc = (uint8)(PduInfoPtr->SduLength);
    #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)

    /*
     *   MISRA Rule        : 17.4
     *   Message           : Performing pointer arithmetic.
     *   Reason            : Array Indexing is not used to achieve better
     *                     throughput.
     *   Verification      : However, part of the code is verified manually
     *                     and it is not having any impact.
     */

    /* Initialize RxNSdu dynamic structure according to RxNSduId */
    LpRxNSduDyna = &CanTp_GaaRxSduDynamic[RxSduId];
    #endif

    /* Check the state of the CanTp channel */
    switch (LucChannelState)
    {
      case (uint8)CANTP_WAIT:

        /* Check if the received frame is SF or FF */
        if ((RxPduId < (PduIdType)Cantp_Maxno_Rx_Npdu) &&
            (((uint8)CANTP_SF_PCI == LucPci) || ((uint8)CANTP_FF_PCI == LucPci)))
        {
          
          LblNewFrameFlag = CANTP_TRUE;
        }
        break;

      case (uint8)CANTP_RXBUF_WAIT:

        if (((uint8)CANTP_SF_PCI == LucPci) || ((uint8)CANTP_FF_PCI == LucPci))
        {
          /* The reception is completed */
          CanTp_ReceptionComplete(LpChannelRam,
            (NotifResultType)NTFRSLT_E_UNEXP_PDU);

          /* Restore the Rx Id for the Current Reception */
          LblNewFrameFlag = CANTP_TRUE;
        } /* End of if ((CANTP_SF_PCI == LucPci) || (CANTP_FF_PCI == LucPci)) */
        break;

      case (uint8)CANTP_RX_CF:
        #if ((STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)&& (STD_ON == CANTP_RX_NSDU))
        LblNewFrameFlag = CanTp_ProcessRxCF(RxSduId, LpRxSrcPtr,
        PduInfoPtr, LddChannel);
        #endif /* #if(STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)*/
        break;

      default:
        /* Do Nothing */
        break;
    } /* End of switch case */

    /* Check if the new frame is received - Single Frame or First Frame */
    if (CANTP_TRUE == LblNewFrameFlag)
    {
      /* Initialize PDuId according to received RX NSduId */
      LpChannelRam->ddActivePduId = RxSduId;
      CanTp_GaaRxDl[LpChannelRam->ddActivePduId] = LucReceivedDlc;

      /* Calculate SF_DL or FF_DL */
      if((uint8)CANTP_SF_PCI == LucPci)
      {
        if(LucReceivedDlc <= 8)
        {
          LddDecodedSduLength = LpRxSrcPtr[CANTP_ZERO];
        }
        else
        {
          LddDecodedSduLength = LpRxSrcPtr[CANTP_ONE];
        }
      }
      else if((uint8)CANTP_FF_PCI == LucPci)
      {
        /* In case of FF_DL > 4095 Byte */
        if ((LpRxSrcPtr[CANTP_ONE] == CANTP_ZERO)
            && ((LpRxSrcPtr[CANTP_ZERO] & (uint8)CANTP_FF_ESCAPE_FIRST_BYTE_LOW_NIBBLE_MASK) == CANTP_ZERO))
        {
          LddDecodedSduLength = (uint32)LpRxSrcPtr[CANTP_TWO] << 24;
          LddDecodedSduLength = LddDecodedSduLength | ((uint32)LpRxSrcPtr[CANTP_THREE] << 16);
          LddDecodedSduLength = LddDecodedSduLength | ((uint32)LpRxSrcPtr[CANTP_FOUR] << 8);
          LddDecodedSduLength = LddDecodedSduLength | ((uint32)LpRxSrcPtr[CANTP_FIVE]);
        }
        /* In case of FF_DL <= 4095 Byte */
        else
        {
          LucFfDlFirstByteLowNibble = LpRxSrcPtr[CANTP_ZERO] & (uint8)CANTP_FF_LEN_MASK;
          LddDecodedSduLength = LucFfDlFirstByteLowNibble;
          LddDecodedSduLength = (((LddDecodedSduLength << 8)) | (uint32)LpRxSrcPtr[CANTP_ONE]);
        }
      }
      else
      {
        /* Do Nothing */
      }

      /* Validate the received DLC */
      LblDlcErrorFlag = CanTp_RxNewframeDlcCheck(LpRxNSdu,
        (P2CONST(uint8, AUTOMATIC, CANTP_CONST))LpRxSrcPtr,
        LucReceivedDlc, LddDecodedSduLength);

      /* Check if no DLC errors are occurred */
      if (LblDlcErrorFlag == CANTP_FALSE)
      {
        /* Update the byte position */
        LpChannelRam->ucCurrentBytePosition = LucCpyBytePos;

        /*Store the decoded Data Length into Global Variable */
        LpChannelRam->usByteCounter = (PduLengthType) LddDecodedSduLength;
        LpChannelRam->ddSduLength = (PduLengthType) LddDecodedSduLength;

        /* Update the frame type */
        LpChannelRam->ucFrameType = LucFrame;
        #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)

        /* Initialize the frame counter for new frame */
        LpChannelRam->ucFrameCounter = (uint8)CANTP_ZERO;
        #endif

        /* Update the channel status to Rx Normal for new frame */
        LpChannelRam->ucChannelState = (uint8)CANTP_RX_NORMAL;

        /* Initialize the CanTp local data byte length */
        LpChannelRam->ucLocalDataByteIndex = (uint8)CANTP_ZERO;

        /* Update the flow status to new frame */
        LpChannelRam->ucNewFrameFlag = (uint8)CANTP_ONE;

        /* Update the buffer length */
        #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
        /* In case of Single Frame */
        if ((uint8)CANTP_SF_PCI == LucPci)
        #endif
        {
          #if (CANTP_FD_SUPPORT == STD_ON)
          /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */ 
          if ((CANTP_CANFD_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType)||\
               (CANTP_CANFD_PHYSICAL_ADDRESS == LpRxNSdu->ucTaType))
          {
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            if(CANTP_SIXTYFOUR < LpChannelRam->ddSduLength)
            {
            /* Report to DET */
            (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
             CANTP_PROCESSRXDATA_SID, CANTP_E_INVALID_RX_LENGTH);
            }
            else
            #endif /* (STD_ON == CANTP_DEV_ERROR_DETECT) */
            {
              LpChannelRam->ucCurrentFrameLen = (uint8)LpChannelRam->ddSduLength;
            }
     
            /* Store source data address in upperlayer buffer pointer */
            if(LucReceivedDlc <= 8)
            {
              LpChannelRam->pUpLayerBuffPtr = &LpRxSrcPtr[CANTP_ONE];
            }
            else
            {
              LpChannelRam->pUpLayerBuffPtr = &LpRxSrcPtr[CANTP_TWO];
            }          

            /* Request for a new buffer */
            CanTp_RequestRxBuffer(LpChannelRam);
          }
          else
          #endif /* (CANTP_FD_SUPPORT == STD_ON) */
          {
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            if(CANTP_EIGHT < LpChannelRam->ddSduLength)
            {
              /* Report to DET */
              (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
                CANTP_PROCESSRXDATA_SID, CANTP_E_INVALID_RX_LENGTH);
            }
            else
            #endif /* (STD_ON == CANTP_DEV_ERROR_DETECT) */
            {
              /* Get the number of data bytes into local buffer */
              LpChannelRam->ucCurrentFrameLen =
                          (uint8)LpChannelRam->ddSduLength;
            }
                  
            /*  polyspace<MISRA-C:17.4:Not a defect:Justified> No Impact of this rule violation */ 
            LpRxSrcPtr++;

            /* Store source address in channel ptr for upperlayer buffer */
            LpChannelRam->pUpLayerBuffPtr = LpRxSrcPtr;

            /* Request for a new buffer */
            CanTp_RequestRxBuffer(LpChannelRam);
          }
          /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
        }
        #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
        /* In case of First Frame */
        else
        {
          /* Initialize Channel RAM according to RX NSdu dynamic structure
           *   wftmax value */
          LpChannelRam->usRxWftMax = LpRxNSduDyna->usRxWftMax;

          /*Initialize the BS variable to default value*/
          LpChannelRam->usBSVar = (uint16)CANTP_ZERO;
          
          /* In case of FF_DL > 4095 Byte */
          if ((LpRxSrcPtr[CANTP_ONE] == CANTP_ZERO) 
              && ((LpRxSrcPtr[CANTP_ZERO] & (uint8)CANTP_FF_ESCAPE_FIRST_BYTE_LOW_NIBBLE_MASK) == CANTP_ZERO))
          {
            LpChannelRam->ucCurrentFrameLen = (LucReceivedDlc - LucCpyBytePos) - CANTP_SIX;
            /* Store source data address in upperlayer buffer pointer */
            LpChannelRam->pUpLayerBuffPtr = &LpRxSrcPtr[CANTP_SIX];          
          }
          /* In case of FF_DL <= 4095 Byte */
          else
          {
            LpChannelRam->ucCurrentFrameLen = (LucReceivedDlc - LucCpyBytePos) - CANTP_TWO;
            /* Store source data address in upperlayer buffer pointer */
            LpChannelRam->pUpLayerBuffPtr = &LpRxSrcPtr[CANTP_TWO];
          }

          /* Request for a new buffer */
          CanTp_RequestRxBuffer(LpChannelRam);
        } /* End of else */
        #endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
      } /* Check if no DLC errors are occurred */
    } /* Check if the new frame is received */
    #endif /* #if ((STD_ON == CANTP_RX_NSDU) */
  }
} /* End of CanTp_ProcessRxData(PduIdType RxSduId, PduIdType RxPduId,
   * P2CONST(PduInfoType, AUTOMATIC, CANTP_CONST) PduInfoPtr,
   * P2CONST(CanTp_RxExtPdus, AUTOMATIC, CANTP_CONST) LpExtPduPtr) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) ||
        *   (STD_ON == CANTP_RX_NSDU)) */

/*******************************************************************************
** Function Name        : CanTp_ProcessRxCF                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the CanTp_RxIndication   **
**                        to process the Rx data frame received               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : RxSduId                                             **
**                        LpRxSrcPtr                                          **
**                        PduInfoPtr                                          **
**                        LddChannel                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblDetErrFlag                                       **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GblInitStatus        **
**                        Function(s) invoked    : CanTp_RxCfDlcCheck         **
**                                                 CanTp_ReceptionComplete    **
**                                                 CanTp_CopyRxFrame          **
*******************************************************************************/
#if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) && (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, CANTP_CODE) CanTp_ProcessRxCF(PduIdType LddRxSduId, P2VAR(
    uint8, AUTOMATIC, CANTP_VAR) LpRxSrcPtr, P2CONST(PduInfoType, AUTOMATIC,
    CANTP_CONST) PduInfoPtr, CanTp_ChannelType LddChannel)
{
  P2CONST(CanTp_RxNSduDynamic, AUTOMATIC, CANTP_CONST) LpRxNSduDyna;
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  uint16 LusNcrTimer;
  uint8 LucFramecount;
  uint8 LucReceivedDlc;
  uint8 LucPci;
  boolean LblDlcErrorFlag;
  boolean LblNewFrameFlag;

  LblNewFrameFlag = CANTP_FALSE;

  /* Initialize Channel RAM structure according to addressing mode */
  LpChannelRam = &CanTp_GaaChannelRam[LddChannel];

  /* Decode the N_PCI byte */
  LucPci = (uint8)((*LpRxSrcPtr) & (uint8)CANTP_PCI_MASK);
  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  #if(CANTP_FD_SUPPORT == STD_ON)
  if(CANTP_SIXTYFOUR < PduInfoPtr->SduLength)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_PROCCESSRXCF_SID, CANTP_E_INVALID_RX_LENGTH);
  }
  #else
  if(CANTP_EIGHT < PduInfoPtr->SduLength)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_PROCCESSRXCF_SID, CANTP_E_INVALID_RX_LENGTH);
  }
  #endif /* (CANTP_FD_SUPPORT == STD_ON) */
  else
  #endif /* (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    /* Check if the received frame PCI is for Consecutive frame */
    if ((uint8)CANTP_CF_PCI == LucPci)
    {
      /* Get the consecutive frame sequence number */
      LucFramecount = (*LpRxSrcPtr) & (uint8)CANTP_FF_LEN_MASK;

      /* Check if the expected*/
      if (LpChannelRam->ucFrameCounter < (uint8)CANTP_MAX_FRAME_COUNTER)
      {
        /* Expected Frame sequence */
        LpChannelRam->ucFrameCounter++;
      }
      else
      {
        /* Expected Frame sequence */
        LpChannelRam->ucFrameCounter = (uint8)CANTP_ZERO;
      }
      /* Update the flow status to new frame */
      LpChannelRam->ucNewFrameFlag = (uint8)CANTP_ZERO;

      /* Check if the correct Sequence number is received */
      if (LucFramecount == LpChannelRam->ucFrameCounter)
      {
        /* Validate the received DLC */
        /* Get the received data length of the PDU */
        LucReceivedDlc = (uint8)(PduInfoPtr->SduLength);
        LblDlcErrorFlag = CanTp_RxCfDlcCheck(&CanTp_GaaRxSduStatic[LddRxSduId],
                                             LucReceivedDlc);
        if (CANTP_FALSE == LblDlcErrorFlag)
        {
          /*
           *   MISRA Rule       : 17.8
           *   Message          : Increment or decrement operation
           *                    performed on pointer.
           *   Reason           : Increment operator is used to
           *                    achieve better throughput.
           *   Verification     : However, part of the code is
           *                    verified manually and it is not
           *                    having any impact.
           */
          if(((uint16)CANTP_ZERO != LpChannelRam->usBSVar) &&
             (CANTP_INFINITE_BS != LpChannelRam->usBSVar))
          {
            /* Decrement the block size variable */
            (LpChannelRam->usBSVar)--;
          }

          /* Update the frame type */
          LpChannelRam->ucFrameType = (uint8)CANTP_CF_PCI;

          /* Copy the received frame from lower layer */
          CanTp_CopyRxFrame(LpChannelRam, &LpRxSrcPtr[1]);
        } /* if(CANTP_FALSE == LblDlcErrorFlag) */
        else
        {
          /* Complete the reception */
          CanTp_ReceptionComplete(LpChannelRam,
            (NotifResultType)NTFRSLT_E_NOT_OK);
        }

        /* Check if the TP message is received completely */
        if ((uint16)CANTP_ZERO == LpChannelRam->usByteCounter)
        {
          /* Update the Tp Buffer status */
          LpChannelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY;

          /* Invoke upper layer Rx Indication for the ongoing Rx
           * frame */
          CanTp_ReceptionComplete(LpChannelRam, (NotifResultType)NTFRSLT_OK);
        } /* End of if (CANTP_ZERO == LpChannelRam->usByteCounter) */
        else
        {
          LpRxNSduDyna = &CanTp_GaaRxSduDynamic[LddRxSduId];

          /* Check if all the CFs are received in the block  */
          if ((uint16)CANTP_ZERO == LpChannelRam->usBSVar)
          {
            /* Stop N_Cr timer */
            LusNcrTimer = (uint16)CANTP_ZERO;

            /* Initialize Channel RAM according to RX NSdu dynamic
             *   structure wftmax value */
            LpChannelRam->usRxWftMax = LpRxNSduDyna->usRxWftMax;
          } /* End of if ((CANTP_ZERO == LpChannelRam->usBSVar) && */

          else
          {
            /* Start N_Cr timer */
            LusNcrTimer = LpRxNSduDyna->usNcrTimeoutValue;
          }
          CANTP_TIMER_UPDATE_MACRO(LddChannel, CANTP_NCR_TIMER,
            LusNcrTimer);
        } /* if(LpChannelRam->usByteCounter != CANTP_ZERO) */
      } /* if( == CANTP_ZERO == (LpChannelRam->ucFrameCounter - LucFramecount)) */
      else
      {
        /* Reception complete because of wrong sequence number of
         *   the received CF */
        CanTp_ReceptionComplete(LpChannelRam,
          (NotifResultType)NTFRSLT_E_WRONG_SN);
      }
    } /* if(LucPci == CANTP_CF_PCI) */
  /* if(LucPci == CANTP_CF_PCI) */
    else
    {
      if (((uint8)CANTP_SF_PCI == LucPci) || ((uint8)CANTP_FF_PCI == LucPci))
      {
        LblNewFrameFlag = CANTP_TRUE;

        /* Complete the Reception */
        #if (STD_ON == CANTP_SINGLE_CHANNEL)
        #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
        /* The reception is completed */
        CanTp_ReceptionComplete(LpChannelRam, (NotifResultType)NTFRSLT_E_NOT_OK);
        #else /* #if(STD_ON == CANTP_FULL_DUPLEX_MODE) */
        /* The reception is completed */
        CanTp_ReceptionComplete(LpChannelRam,
          (NotifResultType)NTFRSLT_E_UNEXP_PDU);
        #endif
        #else
        #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
        /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
        if (CANTP_MODE_FULL_DUPLEX == CanTp_GaaChannelMode[LddChannel])
        {
          /* The reception is completed */
          CanTp_ReceptionComplete(LpChannelRam,
            (NotifResultType)NTFRSLT_E_NOT_OK);
        }
        else
        #endif /* #if(STD_ON == CANTP_FULL_DUPLEX_MODE) */
        {
          /* The reception is completed */
          CanTp_ReceptionComplete(LpChannelRam,
            (NotifResultType)NTFRSLT_E_UNEXP_PDU);
        }
        /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
        #endif /* End of if (STD_ON == CANTP_SINGLE_CHANNEL) */
      } /* End of if (((uint8)CANTP_SF_PCI == LucPci) || ((uint8)CANTP_FF_PCI ==
         *LucPci)) */
    } /* else if((LucPci == CANTP_SF_PCI)... */
  }
  return (LblNewFrameFlag);
} /* End of CanTp_ProcessRxCF(PduIdType LddRxSduId, P2VAR( */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */

/*******************************************************************************
** Function Name        : CanTp_RxDetCheck                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the CanTp_RxIndication   **
**                        to indicate errors which may be due to invalid      **
**                        input data, or data length or buffer                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : RxPduId                                             **
**                        LpPduInfoPt                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblDetErrFlag                                       **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GblInitStatus        **
**                    Cantp_Max_Indic_Id    **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(StatusType, CANTP_CODE) CanTp_RxDetCheck(PduIdType RxPduId, P2CONST(
    PduInfoType, AUTOMATIC, CANTP_VAR) LpPduInfoPt)
{
  boolean LblDetErrFlag = CANTP_FALSE;

  if (CANTP_FALSE == CanTp_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_RXINDICATION_SID, CANTP_E_UNINIT);
    LblDetErrFlag = CANTP_TRUE;
  } /* End of if (CANTP_FALSE == CanTp_GblInitStatus) */

  /*if ((RxPduId > (PduIdType)CANTP_MAX_INDIC_ID) &&*/
  if ((RxPduId > (PduIdType)Cantp_Max_Indic_Id) &&
      (CANTP_FALSE == LblDetErrFlag))
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_RXINDICATION_SID, CANTP_E_INVALID_RX_ID);
    LblDetErrFlag = CANTP_TRUE;
  } /* End of if (RxPduId > CANTP_MAX_INDIC_ID) */

  #if ((STD_ON == CANTP_RX_NSDU) || (STD_ON == CANTP_TX_EXTENDED_ADDRESS)\
  || (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
  (STD_ON == CANTP_RX_EXTENDED_ADDRESS) || (STD_ON == CANTP_RX_MIXED_ADDRESS))
  /* Check if NPdu is valid. Applicable when the FcRxPduIds are
   *   discontinuous */
  /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
  if ((CANTP_FALSE == LblDetErrFlag) &&\
      ((uint8)CANTP_INVALID == CanTp_GaaRxExtPdus[RxPduId].ucAddressingMode))
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_RXINDICATION_SID, CANTP_E_INVALID_RX_ID);
    LblDetErrFlag = CANTP_TRUE;
  }
  #endif

  if ((NULL_PTR == LpPduInfoPt) && (CANTP_FALSE == LblDetErrFlag))
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_RXINDICATION_SID, CANTP_E_PARAM_POINTER);
    LblDetErrFlag = CANTP_TRUE;
  } /* End of if (NULL_PTR == LpPduInfoPt) */
  else
  {
    if (CANTP_FALSE == LblDetErrFlag)
    {
      /* Check if the received data buffer is NULL pointer */
      /* polyspace<MISRA-C3:D4.14 :: Not a defect Justified> Pointer is not a NULL and valid */
      if (NULL_PTR == LpPduInfoPt->SduDataPtr)
      {
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_RXINDICATION_SID, CANTP_E_PARAM_POINTER);
        LblDetErrFlag = CANTP_TRUE;
      } /* End of if (NULL_PTR == LpPduInfoPt->SduDataPtr) */

      /* Check if the data length is invalid */
      if ((uint16)CANTP_ZERO == LpPduInfoPt->SduLength)
      {
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_RXINDICATION_SID, CANTP_E_INVALID_RX_LENGTH);
        LblDetErrFlag = CANTP_TRUE;
      } /* End of if (CANTP_ZERO == LpPduInfoPt->SduLength) */
    } /* End of if (CANTP_FALSE == LblDetErrFlag) */
  } /* if LpPduInfoPt is not NULL_PTR */

  return (LblDetErrFlag);
} /* End of CanTp_RxDetCheck(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC,
   * CANTP_VAR) LpPduInfoPt) */
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */

/*******************************************************************************
** Function Name        : CanTp_TxConfirmation                                **
**                                                                            **
** Service ID           : 0x40                                                **
**                                                                            **
** Description          : This function is called by the CAN Interface after  **
**                        successful transmission of a Rx CAN N-PDU.          **
**                        This callback service is called by the CanIf and    **
**                        implemented by the CanTp                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different PduIds. Non reentrant for   **
**                        the same PduId.                                     **
**                                                                            **
** Input Parameters     : TxPduId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                 CanTp_GaaTxSduStatic,      **
**                                                 CanTp_GaaChannelMode,      **
**                                                 CanTp_GaaChannelRam,       **
**                                                 CanTp_GaaStMinTimers,      **
**                 Cantp_Channel_Id       **
**                        Function(s) invoked    : CanTp_CbkTxDetCheck        **
**                                                 CanTp_TransmissionComplete **
*******************************************************************************/
#if ((STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) || (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_TxConfirmation(PduIdType TxPduId)
{
  #if ((STD_ON == CANTP_TX_NSDU) && (STD_OFF == CANTP_SINGLE_CHANNEL))
  P2CONST(CanTp_TxNsduStatic, AUTOMATIC, CANTP_CONST) LpTxNSdu = NULL_PTR;
  #endif
  #if ((STD_ON == CANTP_TX_NSDU) || (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  #endif
  #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
  uint16 LusNarTimerValue;
  #endif
  #if ((STD_ON == CANTP_TX_NSDU) || (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
  CanTp_ChannelType LddChannel;
  #endif
  #if ((STD_ON == CANTP_TX_NSDU) || (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
  uint8 LucTxConfirmState;
  #endif
  #if (STD_ON == CANTP_TX_NSDU)
  uint8 LucActualChan;
  #endif
  #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
  uint8 LucNpciPos;
  #endif

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  boolean LblDetErrorFlag;

  /* DET error check */
  LblDetErrorFlag = CanTp_CbkTxDetCheck(TxPduId);

  /* Check whether Det Error occured */
  if (CANTP_FALSE == LblDetErrorFlag)
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
    #if (CANTP_SINGLE_CHANNEL == STD_OFF)
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect: Justified] "Genderated array index in range" */		
    LddChannel = (CanTp_ChannelType)CanTp_GaaRxSduMap[TxPduId];
    #else

    /* Get the channel according to receive SDU structure */
    LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
    /* Improvement #5084 */
    #if (STD_OFF == CANTP_DEV_ERROR_DETECT)
    CANTP_UNUSED(TxPduId);
    #endif /* STD_OFF == CANTP_DEV_ERROR_DETECT */
    #endif /* End of if (CANTP_SINGLE_CHANNEL == STD_OFF) */
    /* Get the channel ram according to transmit or receive channel */
    LpChannelRam = &CanTp_GaaChannelRam[LddChannel];

    /* Assign Tx confirm state according to channel RAM */
    LucTxConfirmState = LpChannelRam->ucTxConfirmState;

    /* Check whether the confirmation is awaited for FC Frame */
    if ((uint8)CANTP_FC_TX_CONF == LucTxConfirmState)
    {
      /* Stop N_Ar timer */
      LusNarTimerValue = (uint16)CANTP_ZERO;

      /* Update the Channel Confirmation State */
      LpChannelRam->ucTxConfirmState = (uint8)CANTP_TX_CONF_IDLE;

      /* Check whether FS is continue to send */
      if ((uint8)CANTP_FS_CTS == LpChannelRam->ucFlowStatus)
      {
        /* Change the channel state */
        LpChannelRam->ucChannelState = (uint8)CANTP_RX_CF;

        /*
         *   MISRA Rule        : 17.4
         *   Message           : Performing pointer arithmetic.
         *   Reason            : Array Indexing is not used to achieve better
         *                      throughput.
         *   Verification      : However, part of the code is verified manually
         *                      and it is not having any impact.
         */

        /* Start N_Cr timer */
        /* polyspace-begin MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Its boundary is pre-defined" */				
				CANTP_TIMER_UPDATE_MACRO(LddChannel, CANTP_NCR_TIMER,
          CanTp_GaaRxSduDynamic[LpChannelRam->ddActivePduId].usNcrTimeoutValue);
        /* polyspace-end MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Its boundary is pre-defined" */
      } /*
         * if(LpChannelRam->ucFlowStatus == CANTP_FS_CTS)
         * Reload N_Ar Timer
         */
      CANTP_TIMER_UPDATE_MACRO(LddChannel, CANTP_NAR_TIMER, LusNarTimerValue);
    } /*
       * if(LucTxConfirmState == CANTP_FC_TX_CONF)
       * End of confirmation is over for FcNpdu
       */
    #endif /* #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
    /* If FC confirmation is not awaited , check for Tx confirmations */
    #if ((STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) && (STD_ON == CANTP_TX_NSDU))
    else
    #endif
    {
      /* Check if confirmation is for TxNpdu */
      #if (STD_ON == CANTP_TX_NSDU)

      #if(STD_OFF == CANTP_SINGLE_CHANNEL)

      /* Get the Tp Tx Nsdu structure */
      LpTxNSdu = &CanTp_GaaTxSduStatic[TxPduId];
      #else
      /* Improvement #5084 */
      #if (STD_OFF == CANTP_DEV_ERROR_DETECT)
      CANTP_UNUSED(TxPduId);
      #endif /* STD_OFF == CANTP_DEV_ERROR_DETECT */
      #endif
      #if (STD_OFF == CANTP_SINGLE_CHANNEL)
      /* Get the connection channel structure address */
			/* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */	
      LddChannel = LpTxNSdu->ddChannelId;      
      #else
      /* Get the connection channel structure address */
      LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
      #endif /* #if(STD_OFF == CANTP_SINGLE_CHANNEL) */
      #if (STD_ON == CANTP_SINGLE_CHANNEL)
      #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
      /* Update actual channel value */
      LucActualChan = CanTp_GaaChannelMapping[LddChannel];
      LpChannelRam =
        &CanTp_GaaChannelRam[CanTp_GaaChannelMapping[LddChannel]];
      #else /* End of if (STD_ON == CANTP_FULL_DUPLEX_MODE) */
      LucActualChan = (uint8)LddChannel;
      LpChannelRam = &CanTp_GaaChannelRam[LddChannel];
      #endif /* #if(STD_ON == CANTP_FULL_DUPLEX_MODE) */
      #else
      #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
      LucActualChan = (uint8)LddChannel;

      /* Check if channel is Full duplex and get ID for Tx ChannelRam */
      /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      if (CANTP_MODE_FULL_DUPLEX == CanTp_GaaChannelMode[LddChannel])
      {
        LucActualChan = CanTp_GaaChannelMapping[LddChannel];
        LpChannelRam =
          &CanTp_GaaChannelRam[CanTp_GaaChannelMapping[LddChannel]];
      }
      else
      #else /* End of if (STD_ON == CANTP_FULL_DUPLEX_MODE) */
      LucActualChan = (uint8)LddChannel;
      #endif /* #if(STD_ON == CANTP_FULL_DUPLEX_MODE) */
      {
        LpChannelRam = &CanTp_GaaChannelRam[LddChannel];
      }
      #endif /* End of if (STD_ON == CANTP_SINGLE_CHANNEL) */
      /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      /* Assign Tx confirm state according to channel RAM */
      LucTxConfirmState = LpChannelRam->ucTxConfirmState;

      #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
      /* Get the current addressing */
      LucNpciPos = LpChannelRam->ucCurrentBytePosition;

      #if(STD_ON == CANTP_DEV_ERROR_DETECT)
      #if(CANTP_FD_SUPPORT == STD_ON)
      if(LucNpciPos > (LpTxNSdu->ucTxSduMaxLength - CANTP_ONE))
      #else
      if(LucNpciPos > CANTP_SEVEN)
      #endif
      {
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_TXCONFIRMATION_SID, CANTP_E_INVALID_TX_LENGTH);    
      }
      else if(LpChannelRam->ddActivePduId > CANTP_MAX_TX_SDUID)
      {
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_TXCONFIRMATION_SID, CANTP_E_INVALID_TX_ID);       
      }
      else
      #endif
      #endif
      {
        /* Check FC confirmation is not awaited  */
        if (LucTxConfirmState != (uint8)CANTP_TX_CONF_IDLE)
        {
          /* Check if the Tx confirmation is for SF or last frame of TP message */
          if ((uint8)CANTP_SF_LF_TX_CONF == LucTxConfirmState)
          {
            /* Process the transmission complete function */
            CanTp_TransmissionComplete(LpChannelRam, (NotifResultType)NTFRSLT_OK);

            /*
             *   MISRA Rule        : 9.1
             *   Message           : All automatic variables shall have been
             * assigned
             *                      a value before being used
             *   Reason            : LucActualChan is assigned value before use.
             *   Verification      : However, part of the code is verified
             * manually
             *                      and it is not having any impact.
             */

            /* Clear N_As Timer  */
            CANTP_TIMER_UPDATE_MACRO(LucActualChan, CANTP_NAS_TIMER,
              ((uint16)CANTP_ZERO));
          } /* End of if (CANTP_SF_LF_TX_CONF == LucTxConfirmState) */
          #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)

          /* Check if the Tx confirmation is for CF of TP message */
          else if ((uint8)CANTP_CF_TX_CONF == LucTxConfirmState)
          {
            /* Update the N_PCI byte */  
            /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Genderated array index in range" */		
            LpChannelRam->aaDataBuffer[LucNpciPos] =
              (LpChannelRam->ucFrameCounter | (uint8)CANTP_CF_PCI);            

            /* Update the Frame Type */
            LpChannelRam->ucFrameType = CANTP_CF_PCI;
            
            /* Start STmin timer */
            CanTp_GaaStMinTimers[LucActualChan] = LpChannelRam->ucStMinValue;

            /* Set the channel buffer state to request the buffer */
            LpChannelRam->ucBufferState = (uint8)CANTP_TX_NOTRDY_INITREQ;

            /* Clear N_As Timer  */
            CANTP_TIMER_UPDATE_MACRO(LucActualChan, CANTP_NAS_TIMER,
              (uint16)CANTP_ZERO);
          } /*
             * else if(LucTxConfirmState == CANTP_CF_TX_CONF)
             * Check if the Tx confirmation is for last CF of a block
             */
          else
          {
            if ((uint8)CANTP_LAST_CF_TX_CONF == LucTxConfirmState)
            {
              /* Update the N_PCI byte */   
              /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Genderated array index in range" */
              LpChannelRam->aaDataBuffer[LucNpciPos] =
                (LpChannelRam->ucFrameCounter | (uint8)CANTP_CF_PCI);              

              /* Update the Frame Type */
              LpChannelRam->ucFrameType = CANTP_CF_PCI;

              /*
               *   MISRA Rule        : 17.4
               *   Message           : Performing pointer arithmetic.
               *   Reason            : Array Indexing is not used to achieve
               * better
               *                      throughput.
               *   Verification      : However, part of the code is verified
               * manually
               *                      and it is not having any impact.
               */
              /* polyspace-begin MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Its boundary is pre-defined" */
              /* Start N_Bs timer */
              CANTP_TIMER_UPDATE_MACRO(LucActualChan, CANTP_NBS_TIMER,
                 CanTp_GaaTxSduDynamic[LpChannelRam->ddActivePduId].
                 usNbsTimeoutValue);
              /* polyspace-end MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Its boundary is pre-defined" */
              /* Set channel state to "waiting for Rx indication for FC" */
              LpChannelRam->ucChannelState = (uint8)CANTP_RX_FC;

              /* Clear N_As Timer  */
              CANTP_TIMER_UPDATE_MACRO(LucActualChan, CANTP_NAS_TIMER,
                (uint16)CANTP_ZERO);
            } /* End of if (CANTP_LAST_CF_TX_CONF == LucTxConfirmState) */
          } /* Frame is of type FF or CF */
          #endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */
        } /* Check that confirmation state is Tx flow control or Tx Ideal */
      }
      #endif /* #if (STD_ON == CANTP_TX_NSDU) */
    }
  } /* No DET Error */
} /* End of CanTp_TxConfirmation(PduIdType TxPduId) */


#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif 
/*******************************************************************************
** Function Name        : CanTp_CbkTxDetCheck                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the CanTp_TxConfirmatiom **
**                        to indicate errors which may be due to invalid      **
**                        input data, or data length or buffer                **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : TxPduId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblDetErrFlag                                       **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GblInitStatus        **
**                    Cantp_Max_Confirm_Id    **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, CANTP_CODE) CanTp_CbkTxDetCheck(PduIdType TxPduId)
{
  boolean LblDetErrFlag;
  LblDetErrFlag = CANTP_FALSE;

  /* If module is not initialise */
  if (CANTP_FALSE == CanTp_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TXCONFIRMATION_SID, CANTP_E_UNINIT);
    LblDetErrFlag = CANTP_TRUE;
  } /* End of if (CANTP_FALSE == CanTp_GblInitStatus) */

  if (CANTP_FALSE == LblDetErrFlag)
  {
    /*if (TxPduId > (PduIdType)CANTP_MAX_CONFIRM_ID)*/
    if (TxPduId > (PduIdType)Cantp_Max_Confirm_Id)
    {
      /* Report to DET */
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_TXCONFIRMATION_SID, CANTP_E_INVALID_TX_ID);
      LblDetErrFlag = CANTP_TRUE;
    } /* End of if (TxPduId > CANTP_MAX_CONFIRM_ID) */
  } /* End of if (CANTP_FALSE == LblDetErrFlag) */
  return (LblDetErrFlag);
} /* End of CanTp_CbkTxDetCheck(PduIdType TxPduId) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

