/*******************************************************************************
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_RxInternal.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Internal Functions implementation for CanTp module            **
**              CanTp_RxPduBufferChk                                          **
**              CanTp_RequestRxBuffer                                         **
**              CanTp_TransmitFc                                              **
**              CanTp_CopyRxFrame                                             **
**              CanTp_RxCfDlcCheck                                            **
**              CanTp_RxNewframeDlcCheck                                      **
**              CanTp_RxBinarySearch                                          **
**              CanTp_ReceptionComplete                                       **
**              CanTp_CopyRxDatToLocalBuff                                    **
**              CanTp_RxBufferChk                                             **
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
** 1.11.0    24-Nov-2020   SM Kwon        Redmine #26036, #20053              **
** 1.10.2    29-Jul-2020   SM Kwon        Redmine #24646, #25248, #26004      **
** 1.10.1    07-Oct-2019   SM Kwon        Redmine #19617                      **
** 1.10.0    10-Sep-2019   SM Kwon        Redmine #19217, #19445              **
** 1.9.0     29-Jul-2019   SM Kwon        Redmine #16557, #16558, #17748,     **
                                                  #18299                      **
** 1.8.1     12-Mar-2019   SM Kwon        Redmine #15962, #16463, #16559      **
** 1.8.0     21-Mar-2018   Lim Jong Sun   Redmine #11554                      **
** 1.7.11    19-Dec-2017   Lim Jong Sun   Redmine #10756                      **
** 1.7.7     02-May-2016   Lim Jong Sun   Redmine #4803                       **
** 1.7.4     16-Dec-2015   Lim Jong Sun   Redmine #3252                       **
** 1.0.5     25-Aug-2015   Lim Jong Sun   Redmine #2788                       **
** 1.0.1     20-Jun-2013   Lim Jong Sun   Library Release Version             **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp.h"                /* CanTp RxInternal Header File */
#include "CanTp_PCTypes.h"        /* CanTp PCTypes Header File */
#include "CanTp_RxInternal.h"     /* CanTp RxInternal Header File */
#include "CanTp_Ram.h"            /* CanTp Global RAM variables header file */
#include "PduR_CanTp.h"           /* PduR Header File */
#include "SchM_CanTp.h"           /* SchM Header File */
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
#include "Det.h"                  /* DET header file */
#endif
#include "CanIf.h"                /* CanIf Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANTP_RXINTERNAL_C_AR_RELEASE_MAJOR_VERSION    4
#define CANTP_RXINTERNAL_C_AR_RELEASE_MINOR_VERSION    0
#define CANTP_RXINTERNAL_C_AR_RELEASE_REVISION_VERSION 3

/* CANTP software version information */
#define CANTP_RXINTERNAL_C_SW_MAJOR_VERSION            1
#define CANTP_RXINTERNAL_C_SW_MINOR_VERSION            11

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANTP_AR_RELEASE_MAJOR_VERSION !=\
 CANTP_RXINTERNAL_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp_RxInternal.c : Mismatch in Specification Major Version"
#endif
#if (CANTP_AR_RELEASE_MINOR_VERSION !=\
 CANTP_RXINTERNAL_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp_RxInternal.c : Mismatch in Specification Minor Version"
#endif
#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_RXINTERNAL_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp_RxInternal.c : Mismatch in Specification Revision Version"
#endif
#if (CANTP_SW_MAJOR_VERSION != CANTP_RXINTERNAL_C_SW_MAJOR_VERSION)
#error "CanTp_RxInternal.c : Mismatch in Software Major Version"
#endif
#if (CANTP_SW_MINOR_VERSION != CANTP_RXINTERNAL_C_SW_MINOR_VERSION)
#error "CanTp_RxInternal.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (CANTP_RX_NSDU == STD_ON)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_CopyRxDatToLocalBuff(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam, P2CONST(uint8, AUTOMATIC, CANTP_CONST) LpRxSrcPtr);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_RxPduBufferChk(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam, P2VAR(uint8, AUTOMATIC, CANTP_VAR) LpRxSrcPtr);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_RxBufferChk(P2VAR(CanTp_ChannelRam,
    AUTOMATIC, CANTP_VAR) LpChanelRam);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON  == CANTP_RX_NSDU) */

#if ((CANTP_RX_PHYSICAL_ADDRESSING == STD_ON) && (CANTP_RX_NSDU == STD_ON))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_TransmitFc(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam);

#endif
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanTp_ReceptionComplete                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for completing the            **
**                        reception and indicate the upper layer about        **
**                        reception result                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpChannelRam                                        **
**                        LddResult                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaRxSduStatic,      **
**                                                 CanTp_GpRxSduDynamic       **
**                     Cantp_Channel_Id    **
**                        Function(s) invoked    : PduR_CanTpRxIndication     **
**                                                 Dem_ReportErrorStatus      **
**                                                 Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_ReceptionComplete (P2VAR(CanTp_ChannelRam,
    AUTOMATIC, CANTP_VAR) LpChannelRam, NotifResultType LddResult)
{
  PduIdType LddActivePduId;
  #if (STD_OFF == CANTP_SINGLE_CHANNEL)
  P2CONST(CanTp_RxNsduStatic, AUTOMATIC, CANTP_CONST) LpRxNSdu = NULL_PTR;
  #endif
  P2CONST(CanTp_RxNSduDynamic, AUTOMATIC, CANTP_CONST) LpRxNSduDyna;
  /* Get activating Pdu ID */
  LddActivePduId = LpChannelRam->ddActivePduId;
  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  if (CANTP_MAXNO_RX_SDU <= LddActivePduId)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_RECEPTIONCOMPLETE_SID, CANTP_E_INVALID_RX_ID);
  }
  else
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    /* Initialize the channel state to IDLE (i.e. TxWait and RxWait) */
    LpChannelRam->ucChannelState = (uint8)CANTP_WAIT;

    /* Reset Tx Confirmation state to IDLE */
    LpChannelRam->ucTxConfirmState = (uint8)CANTP_TX_CONF_IDLE;
    #if (STD_OFF == CANTP_SINGLE_CHANNEL)
    /* Get the static RxNSdu structure Pointer */
    LpRxNSdu = &CanTp_GaaRxSduStatic[LddActivePduId];
    #endif

    /*
     *   MISRA Rule        : 17.4
     *   Message           : Performing pointer arithmetic.
     *   Reason            : Array Indexing is not used to achieve better
     *                             throughput.
     *   Verification      : However, part of the code is verified manually and
     *                             it is not having any impact.
     */
    /* polyspace-begin RTE:IDP [Not a defect: Justified] "Its boundary is pre-defined" */ 
    /* Get the dynamic RxNSdu structure Pointer */
    LpRxNSduDyna = &CanTp_GaaRxSduDynamic[LddActivePduId];

    /* Reset the Ram variable */
    LpChannelRam->ddActivePduId = (PduIdType)CANTP_ZERO;

    #if (CANTP_START_OF_RECPT_FOUR_ONE_ONE == STD_ON)
    if(LddResult != NTFRSLT_E_NOT_OK_STARTOFRECP)
    {
      /* Invoke upper layer Rx indication with LddResult */
    /* polyspace +1 MISRA-C3:18.1 [Not a defect: Justified] "Pointer is not a NULL and valid" */ 
      PduR_CanTpRxIndication(LpRxNSduDyna->ddUpTargetPduId, LddResult);  
    }
    else
    {
      /* Should not invoke PduR_CanTpRxIndication */
    }
    #else
    /* Invoke upper layer Rx indication with LddResult */
    /* polyspace +1 MISRA-C3:18.1 [Not a defect: Justified] "Pointer is not a NULL and valid" */ 
    PduR_CanTpRxIndication(LpRxNSduDyna->ddUpTargetPduId, LddResult);
    #endif
    /* polyspace-end RTE:IDP [Not a defect: Justified] "Its boundary is pre-defined" */ 
    /* Check the communication Result value other than NTFRSLT_OK to report Dem */
    if (LddResult != (NotifResultType)NTFRSLT_OK)
    {
      #if (STD_ON == CANTP_DEV_ERROR_DETECT)

      /* Report error through DET with CANTP_E_RX_COM if any timeout error */
      if ((LddResult == (NotifResultType)NTFRSLT_E_TIMEOUT_A) ||
          (LddResult == (NotifResultType)NTFRSLT_E_TIMEOUT_CR)
          || (LddResult == (NotifResultType)NTFRSLT_E_WFT_OVRN))
      {
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_RXINDICATION_SID, CANTP_E_RX_COM);
      } /* if((LddResult == NTFRSLT_E_TIMEOUT_A) ||(LddResult == ..) */
      else /* Report error through DET with CANTP_E_COM if other than timeout
            *   error */
      {
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_RXINDICATION_SID, CANTP_E_COM);
      }
      #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
    } /* if(LddResult != NTFRSLT_OK) */

    /* polyspace-begin MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Its bound is pre-defined" */ 
    #if (STD_OFF == CANTP_SINGLE_CHANNEL)
    /* Store the connection channel in local variable*/
    CANTP_STOP_ALL_RX_TIMERS(LpRxNSdu->ddChannelId);
    #else

    /* Store the connection channel in local variable*/
    /*CANTP_STOP_ALL_RX_TIMERS((uint8)CANTP_CHANNEL_ID)*/
    CANTP_STOP_ALL_RX_TIMERS((uint8)Cantp_Channel_Id);
    #endif
    /* polyspace-end MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Its bound is pre-defined" */ 
  }
} /* End of CanTp_ReceptionComplete(P2VAR(CanTp_ChannelRam, AUTOMATIC,
   * CANTP_VAR) LpChannelRam, NotifResultType LddResult) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_TransmitFc                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is responsible for transmitting       **
**                        the FC                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpChannelRam                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaRxSduStatic,      **
**                                                 CanTp_GpRxSduDynamic,      **
**                Cantp_Channel_Id      **
**                Cantp_Padding_Byte    **
**                        Function(s) invoked    : CanIf_Transmit             **
*******************************************************************************/
#if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) && (CANTP_RX_NSDU == STD_ON)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_TransmitFc(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam)
{
  P2CONST(CanTp_STminBs, AUTOMATIC, CANTP_CONST) LpRxNSduRam;
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
  (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION) ||\
  (STD_OFF == CANTP_SINGLE_CHANNEL))
  P2CONST(CanTp_RxNsduStatic, AUTOMATIC, CANTP_CONST) LpRxNSdu;
  #endif
  P2CONST(CanTp_RxNSduDynamic, AUTOMATIC, CANTP_CONST) LpRxNSduDyna;
  PduLengthType LddBufferLength;
  PduLengthType LddBsEstimated;
  PduInfoType LddPduInfo;
  CanTp_ChannelType LddChannel;
  uint16 LusNarTimer;
  uint8 LaaDataArray[CANTP_EIGHT];
  uint8 LucFrameSize;
  uint8 LucBytePos;
  uint8 LucRemByte;
  #if(CANTP_FD_SUPPORT == STD_ON)
  uint8 LucRxDl;
  #endif

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  if (CANTP_MAXNO_RX_SDU <= LpChannelRam->ddActivePduId)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TRANSMITFC_SID, CANTP_E_INVALID_RX_ID);
  }
  else if(CANTP_ZERO == CanTp_GaaRxDl[LpChannelRam->ddActivePduId])
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TRANSMITFC_SID, CANTP_E_INVALID_RX_LENGTH);
  }
  else
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED_ADDRESS) ||\
    (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION) ||\
    (STD_OFF == CANTP_SINGLE_CHANNEL))
    /* Get the static RxNSdu structure Pointer */
    LpRxNSdu = &CanTp_GaaRxSduStatic[LpChannelRam->ddActivePduId];
    #endif /* End of if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||
            *(STD_ON == CANTP_RX_MIXED_ADDRESS) ||
            *(STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION) || (CANTP_SINGLE_CHANNEL
            *== STD_OFF)) */

    /*
     *   MISRA Rule        : 17.4
     *   Message           : Performing pointer arithmetic.
     *   Reason            : Array Indexing is not used to achieve better
     *                      throughput.
     *   Verification      : However, part of the code is verified manually and
     *                      it is not having any impact.
     */

    /* Get the dynamic RxNSdu structure Pointer */
    LpRxNSduDyna = &CanTp_GaaRxSduDynamic[LpChannelRam->ddActivePduId];
    #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED_ADDRESS))

    /* polyspace-begin MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Its bound is pre-defined" */ 
    /* Get the N_PCI position if transmit NSDU is configured as Extended */
    LucBytePos = CanTp_GaaBytePos[LpRxNSdu->ucAddressingMode];
    #else
    LucBytePos = (uint8)CANTP_ZERO;
    #endif
    #if (STD_OFF == CANTP_SINGLE_CHANNEL)

    /* Get the channel according to receive SDU structure */
    /* polyspace<RTE:OBAI : Not a defect: Justified> Genderated array index in range */
    LddChannel = LpRxNSdu->ddChannelId;
    #else

    /* Get the channel according to receive SDU structure */
    /*LddChannel = (CanTp_ChannelType)CANTP_CHANNEL_ID;*/
    LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
    #endif
    #if(CANTP_FD_SUPPORT == STD_ON)
    LucRxDl = CanTp_GaaRxDl[LpChannelRam->ddActivePduId];
    #endif

    /* polyspace-end MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Its bound is pre-defined" */ 
    /* Set the frame size */
    #if(CANTP_FD_SUPPORT == STD_ON)
    LucFrameSize = (LucRxDl - CANTP_ONE) - LucBytePos;
    #else
    LucFrameSize = (uint8)CANTP_SEVEN - LucBytePos;
    #endif
    
    #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED_ADDRESS))

    /* Check and store the N_Ta in local buffer */
    /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "condition will be executed based on the configured values" */
    if ((uint8)CANTP_ONE == LucBytePos)
    {
      LaaDataArray[CANTP_ZERO] = LpRxNSdu->ucFcNTaOrNAeValue;
    }
    #endif /* End of if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||
            *(STD_ON == CANTP_RX_MIXED_ADDRESS)) */

    /* Store the N_PCI byte 1 in the local buffer */
    LaaDataArray[LucBytePos] = ((uint8)CANTP_FC_PCI) | LpChannelRam->ucFlowStatus;
    LucBytePos++;

    /* Get the pointer to STMin and BS array */
    LpRxNSduRam = &CanTp_GaaSTminBs[LpChannelRam->ddActivePduId];

    if ((uint8)CANTP_FS_CTS == LpChannelRam->ucFlowStatus)
    {
      /* Check if the available buffer length greater than number of bytes needs
       * to be received and configured BS is ZERO. */
      if ((LpChannelRam->usAvlBuffLength >= LpChannelRam->usByteCounter)
          && (LpRxNSduRam->usBlockSize == (uint16)CANTP_ZERO))
      {
        /* Store the Configure BS that is ZERO */
        LpChannelRam->usBSVar = CANTP_INFINITE_BS;
      }
      else
      {
        /* Check if the available buffer length greater than number of bytes needs
         * to be received. */
        if (LpChannelRam->usAvlBuffLength >= LpChannelRam->usByteCounter)
        {
          /* Store the byte counter as buffer length in local variable */
          LddBufferLength = (PduLengthType)LpChannelRam->usByteCounter;

          /* Check data is exact multiple of framelength*/
          /* 10756 */
          /* polyspace<RTE:ZDV : Not a defect: Justified> Genderated array index in range */
          LucRemByte = (uint8)(LddBufferLength % (PduLengthType)LucFrameSize);

          if ((uint8)CANTP_ZERO == LucRemByte)
          {
            LddBsEstimated = 
                               (((PduLengthType)LddBufferLength) /
                               (PduLengthType)LucFrameSize);
          }
          else
          {
            LddBsEstimated = ((((PduLengthType)LddBufferLength) /
                               (PduLengthType)LucFrameSize) +
                               (PduLengthType)CANTP_ONE);
          }
        } /* else if(LpChannelRam->usAvlBuffLength >=LpChannelRam->usByteCounter) */
        else
        {
          /* Store the buffer length in local variable */
          LddBufferLength = (PduLengthType)LpChannelRam->usAvlBuffLength;
    
          /* Estimate the possible BS value */
          /* polyspace<RTE:ZDV : Not a defect: Justified> Genderated array index in range */
          LddBsEstimated = (((PduLengthType)LddBufferLength) /
          (PduLengthType)LucFrameSize);
        } /*
         * End of else
         * Store the Block Size value
         */
        LpChannelRam->usBSVar = LpRxNSduRam->usBlockSize;

        /* Check if the estimated BS value is less than maximum BS configured */
        if ((LddBsEstimated < LpRxNSduRam->usBlockSize)
             || ((0 == LpRxNSduRam->usBlockSize)&&(LddBsEstimated != 0)))
        {
          /* Store the Estimate possible Block Size value */
          LpChannelRam->usBSVar = LddBsEstimated;
        } 
      }
      /* Store the Block size as N_PCI byte 2 in the local buffer */
      LaaDataArray[LucBytePos] = (uint8)((LpChannelRam->usBSVar) & 0x00FFU);
    } /* Flow status is CTS */
    else
    {
      /* Store the null as N_PCI byte 2 in the local buffer */
      LaaDataArray[LucBytePos] = (uint8)CANTP_ZERO;
    }
    
    LucBytePos++;

    /* Store the separation Time value as N_PCI byte 3 in the local buffer */
    LaaDataArray[LucBytePos] = LpRxNSduRam->ucSTMin;
    LucBytePos++;

    #if (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION)
    /* Initialize the Sdu Length as 3 if padding activation off */
    LddPduInfo.SduLength = (PduLengthType)LucBytePos;

    /* Check if the SDU is configured for PADDING ACTIVATION equal to STD_ON */
    /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "condition will be executed based on the configured values" */
    if (CANTP_TRUE == LpRxNSdu->blRxPaddingActivation)
    {
      CANTP_MEMCPY(&LaaDataArray[LucBytePos], &Cantp_Padding_Byte[0], (uint8)(CANTP_EIGHT - LucBytePos));
      
      /* Initialize the Sdu Length as eight */
      LddPduInfo.SduLength = (PduLengthType)CANTP_EIGHT;
    } /* end if(LpRxNSdu->blRxPaddingActivation == CANTP_TRUE) */
    #else /* End of if (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION) */
    /* Initialize the Sdu Length as 3 if padding activation off */
    LddPduInfo.SduLength = (PduLengthType)LucBytePos;
    #endif /* End of if (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION) */

    LddPduInfo.SduDataPtr = LaaDataArray;

    /* Initiate lower layer transmit request */
    if (LpChannelRam->ucFlowStatus < (uint8)CANTP_FS_OVFLW)
    {
      LusNarTimer = LpRxNSduDyna->usNarTimeoutValue;

      /* Load Nar timer based on Buffer busy state */
      if (((uint8)CANTP_ONE == LpChannelRam->ucNewFrameFlag) ||
          ((uint8)CANTP_CF_PCI == LpChannelRam->ucFrameType))
      {
        LusNarTimer = LpRxNSduDyna->usNarTimeoutValue + (uint16)CANTP_ONE;
      }
      /* Start N_Ar timer */
      CANTP_TIMER_UPDATE_MACRO(LddChannel, CANTP_NAR_TIMER,
        LusNarTimer);

      /* Update the channel state */
      LpChannelRam->ucChannelState = (uint8)CANTP_FC_TXCONF;
      LpChannelRam->ucTxConfirmState = (uint8)CANTP_FC_TX_CONF;
    } /* End of if (LpChannelRam->ucFlowStatus < CANTP_FS_OVFLW) */

    /* Invoke lower layer API for transmission of
     * FC */
    (void)CanIf_Transmit(LpRxNSduDyna->ddLoTxFcTargetPduId, &LddPduInfo);
  }
} /* End of CanTp_TransmitFc(P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR)
   * LpChannelRam) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */

/*******************************************************************************
** Function Name        : CanTp_CopyRxFrame                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies data to the upper layer(PduR)  **
**                        buffer either from lower layer(CanIf) buffer or     **
**                        CanTp local buffer.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpChannelRam                                        **
**                        LpRxSrcPtr                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaRxSduDynamic      **
**                        Function(s) invoked    : PduR_CanTpCopyRxData       **
**                                                 CanTp_TransmitFc           **
**                                                 CanTp_ReceptionComplete    **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_CopyRxFrame(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam, P2VAR(uint8, AUTOMATIC, CANTP_VAR) LpRxSrcPtr)
{
  P2CONST(CanTp_RxNSduDynamic, AUTOMATIC, CANTP_CONST) LpRxNSduDyna;
  PduInfoType LddRxPduInfo;
  BufReq_ReturnType LenBufferStatus;
  PduLengthType LddBufferSize;
  PduLengthType LddDataBytes;
  /*Fixed MISRA-C 9.1 */
  /* 10756 */
  LddBufferSize = (PduLengthType)CANTP_ZERO;
  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  if (CANTP_MAXNO_RX_SDU <= LpChannelRam->ddActivePduId)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_COPYRXFRAME_SID, CANTP_E_INVALID_RX_ID);
  }
  #if (STD_ON == CANTP_FD_SUPPORT)
  else if (CANTP_SIXTYFOUR < LpChannelRam->ucCurrentFrameLen)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_COPYRXFRAME_SID, CANTP_E_INVALID_RX_LENGTH);
  }
  #else
  else if (CANTP_EIGHT < LpChannelRam->ucCurrentFrameLen)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_COPYRXFRAME_SID, CANTP_E_INVALID_RX_LENGTH);
  }
  #endif
  else
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    /* Get the current frame length to copy */
    LddDataBytes = (PduLengthType)LpChannelRam->ucCurrentFrameLen;

    /*
     *   MISRA Rule        : 17.4
     *   Message           : Performing pointer arithmetic.
     *   Reason            : Array Indexing is not used to achieve better
     *                      throughput.
     *   Verification      : However, part of the code is verified manually and
     *                             it is not having any impact.
     */

    /* Initialize RxNSdu dynamic structure according to RxNSduId */
    LpRxNSduDyna = &CanTp_GaaRxSduDynamic[LpChannelRam->ddActivePduId];

    /* Set the flow status as CTS */
    LpChannelRam->ucFlowStatus = (uint8)CANTP_FS_CTS;

    /*
     *   MISRA Rule         : 17.4.
     *   Message            : Performing pointer arithmetic
     *   Reason             : Increment operator not used to achieve better
     *                       throughput.
     *   Verification       : However, part of the code is verified manually and
     *                       it is not having any impact.
     */

    /* polyspace-begin RTE:IDP [Not a defect: Justified] "Its bound is pre-defined" */ 
    /* Copy the data from lower layer to upper layer buffer */
    LddRxPduInfo.SduDataPtr = LpRxSrcPtr;
    LddRxPduInfo.SduLength = LddDataBytes;
    /* polyspace +1 MISRA-C3:18.1 [Not a defect: Justified] "Pointer is not a NULL and valid" */ 
    LenBufferStatus = PduR_CanTpCopyRxData(LpRxNSduDyna->ddUpTargetPduId,
      &LddRxPduInfo, &LddBufferSize);
    /* polyspace-end RTE:IDP [Not a defect: Justified] "Its bound is pre-defined" */ 

    if (BUFREQ_OK == LenBufferStatus)
    {    
      /* Update the available upperlayer buffer length */
      LpChannelRam->usAvlBuffLength = (uint16)LddBufferSize;

      #if (STD_ON == CANTP_DEV_ERROR_DETECT)
      if(LpChannelRam->usByteCounter < LddDataBytes)
      {
         /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
           CANTP_COPYRXFRAME_SID, CANTP_E_INVALID_RX_LENGTH);
      }
      else
      #endif /* (STD_ON == CANTP_DEV_ERROR_DETECT) */
      {
        /* Decrement the byte counter */
        LpChannelRam->usByteCounter =
          LpChannelRam->usByteCounter - (uint16)LddDataBytes;  
      } 

      /* Check if enough buffer is available after receiving last CF in a Block
       */
      #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)

      if (((uint16)CANTP_ZERO == LpChannelRam->usBSVar)
          && (LpChannelRam->usByteCounter != (uint16)CANTP_ZERO))
      {
        /* Check buffer available enough to next the next block */
        if (((uint16)LddBufferSize >= (uint16)(LpChannelRam->ucCurrentFrameLen))
            || ((uint16)LddBufferSize >= LpChannelRam->usByteCounter))
        {
          if ((uint8)CANTP_ONE == LpChannelRam->ucNewFrameFlag)
          {
            /* Update the channel status */
            LpChannelRam->ucFlowStatus = (uint8)CANTP_FS_WT;

            /* Transmit FC if Tx confirmation is not awaited
             *   for previous Transmission*/
            if ((uint8)CANTP_TX_CONF_IDLE == LpChannelRam->ucTxConfirmState)
            {
              /* Transmit the flow control frame */
              CanTp_TransmitFc(LpChannelRam);
            }
          } /* End of if (CANTP_ONE == LpChannelRam->ucNewFrameFlag) */
          else
          {
            /* Update the channel status */
            LpChannelRam->ucFlowStatus = (uint8)CANTP_FS_CTS;

            /* Transmit the flow control frame */
            CanTp_TransmitFc(LpChannelRam);
          } /* End of else */
        } /* End of if ((LddBufferSize >= LpChannelRam->ucCurrentFrameLen) */
        else
        {
          /* Update the buffer state to indicate waiting for receive buffer */
          LpChannelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY_INITREQ;
        }
      } /* end if((LpChannelRam->usBSVar == CANTP_ZERO)... */

      #endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
    } /* end if(LenBufferStatus == BUFREQ_OK) */
    else if (BUFREQ_E_BUSY == LenBufferStatus) /* Check if the buffer is BUSY */
    {
      /* Update the Tp Buffer status */
      LpChannelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY;

      /* check for the last frame */
      if ((uint8)CANTP_ONE == LpChannelRam->ucNewFrameFlag)
      {
        #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
      /* Update the channel status */
        LpChannelRam->ucFlowStatus = (uint8)CANTP_FS_WT;

        /* Transmit FC if Tx confirmation is not awaited
         *      for previous Transmission*/
        if (LpChannelRam->ucTxConfirmState == (uint8)CANTP_TX_CONF_IDLE)
        {
          /* Transmit the flow control frame */
          CanTp_TransmitFc(LpChannelRam);
        }
      #endif
      } /* End of if (CANTP_ONE == LpChannelRam->ucNewFrameFlag) */
      else
      {
        /* Invoke upper layer Rx Indication to abort reception of this N-SDU */
        CanTp_ReceptionComplete(LpChannelRam, (NotifResultType)NTFRSLT_E_NOT_OK);
      }
    } /* if(LenBufferStatus == BUFREQ_E_BUSY) */
    else /*Check if the buffer is NOT_OK*/
    {
      /* Update the Tp Buffer status */
      LpChannelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY;

      /* Invoke upper layer Rx Indication to abort the reception of this N-SDU */
      CanTp_ReceptionComplete(LpChannelRam, (NotifResultType)NTFRSLT_E_NOT_OK);
    } /* else if(LenBufferStatus == BUFREQ_E_NOT_OK) */
  }  
} /* End of CanTp_CopyRxFrame(P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR)
   * LpChannelRam, P2VAR(uint8, AUTOMATIC, CANTP_VAR) LpRxSrcPtr) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RequestRxBuffer                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function requests upper Layer for Rx buffer    **
**                        and also handles the request results provided by    **
**                        upper layer                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpChannelRam                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaRxSduStatic,      **
**                                                 CanTp_GaaTimers            **
**                Cantp_Channel_Id    **
**                        Function(s) invoked    : PduR_CanTpCopyRxData       **
**                                                 CanTp_TransmitFc           **
**                                                 CanTp_ReceptionComplete    **
**                                                 PduR_CanTpStartOfReception **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_RequestRxBuffer(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam)
{
  #if (STD_OFF == CANTP_SINGLE_CHANNEL)
  P2CONST(CanTp_RxNsduStatic, AUTOMATIC, CANTP_CONST) LpRxNSdu = NULL_PTR;
  #endif
  P2CONST(CanTp_RxNSduDynamic, AUTOMATIC, CANTP_CONST) LpRxNSduDyna;
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) LpRxSrcPtr;
  PduInfoType LddPduInfo;
  BufReq_ReturnType LenBufferStatus;
  PduLengthType LddBufferSize;
  PduIdType LddActiveSduId;
  CanTp_ChannelType LddChannel;
  uint16 LusNbrTimer;
  #if (CANTP_START_OF_RECPT_FOUR_ONE_ONE == STD_ON)
  boolean LblStartOfRecpNotOk;
  LblStartOfRecpNotOk = CANTP_FALSE;
  #endif
  
  /*FIXED MISRA-C 9.1 */
  /* 10756 */
  LddBufferSize = (PduLengthType)CANTP_ZERO;

  /* Initialize the source pointer */
  LpRxSrcPtr = LpChannelRam->pUpLayerBuffPtr;

  /* Update the Tp Buffer status */
  LpChannelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY_INITREQ;

  /*Get the SduId */
  LddActiveSduId = LpChannelRam->ddActivePduId;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  if (CANTP_MAXNO_RX_SDU <= LpChannelRam->ddActivePduId)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_REQUESTRXBUFFER_SID, CANTP_E_INVALID_RX_ID);
  }
  else
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    #if (STD_OFF == CANTP_SINGLE_CHANNEL)

    /* Get the static RxNSdu structure Pointer */
    LpRxNSdu = &CanTp_GaaRxSduStatic[LddActiveSduId];
    #endif

    /*
     *   MISRA Rule        : 17.4
     *   Message           : Performing pointer arithmetic.
     *   Reason            : Array Indexing is not used to achieve better
     *                      throughput.
     *   Verification      : However, part of the code is verified manually and
     *                      it is not having any impact.
     */

    /* polyspace-begin RTE:IDP [Not a defect: Justified] "Configured memory access index" */ 
    /* Get the dynamic RxNSdu structure Pointer */
    LpRxNSduDyna = &CanTp_GaaRxSduDynamic[LddActiveSduId];

    #if (STD_OFF == CANTP_SINGLE_CHANNEL)
    /* Get the channel according to receive SDU structure */
    /* polyspace +1 MISRA-C3:18.1 [Not a defect: Justified] "Pointer is not a NULL and valid" */ 
    LddChannel = LpRxNSdu->ddChannelId;
    #else

    /* Get the channel according to receive SDU structure */
    /*LddChannel = (CanTp_ChannelType)CANTP_CHANNEL_ID;*/
    LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
    #endif
    
    LusNbrTimer = CanTp_GaaTimers[LddChannel][CANTP_NBR_TIMER];
    /* polyspace-end RTE:IDP [Not a defect: Justified] "Configured memory access index" */ 

    /* Check if N_Br Timer is not started */
    if ((uint16)CANTP_ZERO == LusNbrTimer)
    {
      /* Start N_Br timer */
      LusNbrTimer = LpRxNSduDyna->usNbrTimeoutValue;
    }
    /* Update the Nbr timer value */
    CANTP_TIMER_UPDATE_MACRO(LddChannel, CANTP_NBR_TIMER, LusNbrTimer);

    /* Check if the buffer request for FF or SF */
    if ((uint8)CANTP_ONE == LpChannelRam->ucNewFrameFlag)
    {
      #if (CANTP_START_OF_RECPT_FOUR_ONE_ONE == STD_ON)
      LddPduInfo.SduDataPtr = LpRxSrcPtr;
      LddPduInfo.SduLength = LpChannelRam->ucCurrentFrameLen;
      
      /* Invoke the buffer request for FF or SF reception */
      LenBufferStatus = PduR_CanTpStartOfReception(LpRxNSduDyna->ddUpTargetPduId,
        &LddPduInfo, LpChannelRam->ddSduLength, &LddBufferSize);

      if(LenBufferStatus == BUFREQ_E_NOT_OK)
      {
        LblStartOfRecpNotOk = CANTP_TRUE;
    }
    
      #else
      /* Invoke the buffer request for FF or SF reception */
      LenBufferStatus = PduR_CanTpStartOfReception(LpRxNSduDyna->ddUpTargetPduId,
        LpChannelRam->ddSduLength, &LddBufferSize);
      #endif
    }
    else /* The buffer request for CF */
    {
      /* Initialize the PduInfo to request buffer for CF */
      LddPduInfo.SduDataPtr = NULL_PTR;
      LddPduInfo.SduLength = (PduLengthType)CANTP_ZERO;

      /* Invoke the buffer request for CF reception */
      LenBufferStatus = PduR_CanTpCopyRxData(LpRxNSduDyna->ddUpTargetPduId,
        &LddPduInfo, &LddBufferSize);
    } /* End of else */

    /* Check if the buffer is ready */
    if (BUFREQ_OK == LenBufferStatus)
    {
      /* Copy the PDU router buffer length to global variable */
      LpChannelRam->usAvlBuffLength = (uint16)LddBufferSize;

      if (LpChannelRam->usAvlBuffLength >=
          (uint16)(LpChannelRam->ucCurrentFrameLen))
      {
        /* Stop N_Br timer */
        LusNbrTimer = (uint16)CANTP_ZERO;
      }
      CanTp_RxPduBufferChk(LpChannelRam, LpRxSrcPtr);
    } /*
       * if(LenBufferStatus == BUFREQ_OK)
       * Check if the buffer is busy
       */
    else if (BUFREQ_E_BUSY == LenBufferStatus)
    {
      CanTp_RxBufferChk(LpChannelRam);
    } /*
       * else if(LenBufferStatus == BUFREQ_E_BUSY)
       * Check if the buffer is overflow
       */
    else if (BUFREQ_E_OVFL == LenBufferStatus)
    {
      #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)
      LpChannelRam->ucFlowStatus = (uint8)CANTP_FS_OVFLW;

      /* Update the Tp Buffer status */
      LpChannelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY;

      /*Invoke lower layer Tx API */
      CanTp_TransmitFc(LpChannelRam);
      #endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
      /* Invoke upper layer Rx Indication to abort the reception of this N-SDU */
      CanTp_ReceptionComplete(LpChannelRam, (NotifResultType)NTFRSLT_E_NO_BUFFER);
    } /*
       * else if(LenBufferStatus == BUFREQ_E_OVFL)
       * Check if the buffer is NOT_OK
       */
    else
    {
      /* Update the Tp Buffer status */
      LpChannelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY;

      #if (CANTP_START_OF_RECPT_FOUR_ONE_ONE == STD_ON)
      if(LblStartOfRecpNotOk == CANTP_TRUE)
    {
      CanTp_ReceptionComplete(LpChannelRam, (NotifResultType)NTFRSLT_E_NOT_OK_STARTOFRECP);
    }
    else
    {
      CanTp_ReceptionComplete(LpChannelRam, (NotifResultType)NTFRSLT_E_NOT_OK);
    }
    #else
      /* Invoke upper layer Rx Indication to abort the reception of this N-SDU */
      CanTp_ReceptionComplete(LpChannelRam, (NotifResultType)NTFRSLT_E_NOT_OK);
    #endif
    } /* else if(LenBufferStatus == BUFREQ_E_NOT_OK) */

    if (((uint16)CANTP_ZERO == LpChannelRam->usByteCounter) &&
        (LpChannelRam->ucChannelState != (uint8)CANTP_WAIT))
    {
      /* Update the Tp Buffer status */
      LpChannelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY;

      /* Invoke upper layer Rx Indication */
      CanTp_ReceptionComplete(LpChannelRam, (NotifResultType)NTFRSLT_OK);
    } /* End of if ((LpChannelRam->usByteCounter == CANTP_ZERO) && */
    CANTP_TIMER_UPDATE_MACRO(LddChannel, CANTP_NBR_TIMER, LusNbrTimer);
  }
} /* End of CanTp_RequestRxBuffer(P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR)
   * LpChannelRam) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RxPduBufferChk                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function Check if the buffer given by PDU      **
**                        router is enough to store the complete receive      **
**                        data or atleast current frame length of received    **
**                        data.                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpChannelRam                                        **
**                        LpRxSrcPtr                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : CanTp_CopyRxFrame          **
**                                                 CanTp_TransmitFc           **
**                                                 CanTp_CopyRxDatToLocalBuff **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_RxPduBufferChk(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam, P2VAR(uint8, AUTOMATIC, CANTP_VAR) LpRxSrcPtr)
{
  P2VAR(uint8, AUTOMATIC, CANTP_CONST) LpCpyRxSrcPtr = LpRxSrcPtr;
  /* Check if the buffer given by PDU router is enough to store the
   * complete receive data or atleast current frame length of received data
   */
  if (LpChannelRam->usAvlBuffLength >=
      (uint16)(LpChannelRam->ucCurrentFrameLen))
  {
    /* Check if any local data bytes are available */
    if (LpChannelRam->ucLocalDataByteIndex > (uint8)CANTP_ZERO)
    {
      /* Update no local data available by next time */
      LpChannelRam->ucLocalDataByteIndex = (uint8)CANTP_ZERO;

      /* Get the address of CanTp local data */
      LpCpyRxSrcPtr = &LpChannelRam->aaDataBuffer[CANTP_ZERO];
    } /* End of if (LpChannelRam->ucLocalDataByteIndex > CANTP_ZERO) */

    /* Update the flow status for not a new frame
    **/
    LpChannelRam->ucNewFrameFlag = (uint8)CANTP_ZERO;

    /* Update the Tp Buffer status */
    LpChannelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY;

    /*Invoke copy Rx Frame if only SF or FF or Start of new block*/
    if (LpChannelRam->ucFrameType != (uint8)CANTP_CF_PCI)
    {
      /* Copy the received frame into upper layer */
      CanTp_CopyRxFrame(LpChannelRam, LpCpyRxSrcPtr);
    }
    else
    {
      #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)

      /* Update the channel status */
      LpChannelRam->ucFlowStatus = (uint8)CANTP_FS_CTS;

      /* Transmit FC if Tx confirmation is not awaited
       *   for previous Transmission*/
      if ((uint8)CANTP_TX_CONF_IDLE == LpChannelRam->ucTxConfirmState)
      {
        /* Transmit the flow control frame */
        CanTp_TransmitFc(LpChannelRam);
      }
      #endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
    } /* End of else */
  } /* if((LpChannelRam->usAvlBuffLength >= LpChannelRam->usByteCounter)*/
  else
  {
    if (((uint8)CANTP_ZERO == LpChannelRam->ucLocalDataByteIndex)
        || ((uint8)CANTP_ONE == LpChannelRam->ucNewFrameFlag))
    {
      /* Copy data received to the local buffer */
      CanTp_CopyRxDatToLocalBuff(LpChannelRam, LpCpyRxSrcPtr);
      #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)

      /* Send the flow control frame if the frame is not a single frame */
      if (LpChannelRam->ucFrameType != (uint8)CANTP_SF_PCI)
      {
        /* Check whether the WFTmax counter value reaches the maximum
         *   configured value. */
        if ((uint16)CANTP_ZERO == LpChannelRam->usRxWftMax)
        {
          /* Update the Tp Buffer status */
          LpChannelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY;

          /* Update the CanTp local data length */
          LpChannelRam->ucLocalDataByteIndex = (uint8)CANTP_ZERO;

          /* Invoke upper layer Rx Indication to abort the reception of
           * this N-SDU with the result NTFRSLT_E_WFT_OVRN*/
          CanTp_ReceptionComplete(LpChannelRam,
            (NotifResultType)NTFRSLT_E_WFT_OVRN);
        } /* End of if (CANTP_ZERO == LpChannelRam->usRxWftMax) */
        else
        {
          /* Decrement the WFTmax counter to send only the maximum number of
           *   flow control frame*/
          (LpChannelRam->usRxWftMax)--;
	  
          /* Update the flow status as wait */
          LpChannelRam->ucFlowStatus = (uint8)CANTP_FS_WT;

          /* Transmit FC if Tx confirmation is not awaited
           *   for previous Transmission*/
          if ((uint8)CANTP_TX_CONF_IDLE == LpChannelRam->ucTxConfirmState)
          {
            /* Transmit the flow control frame */
            CanTp_TransmitFc(LpChannelRam);
          }
        } /* End of else */
      } /* end if(LpChannelRam->ucFrameType != CANTP_SF_PCI) */
      #endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
    } /* end if((LpChannelRam->ucLocalDataByteIndex == CANTP_ZERO)... */
  } /* Available buffer length is not enough to copy the received frame  */
} /* End of CanTp_RxPduBufferChk(P2VAR(CanTp_ChannelRam, AUTOMATIC, */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RxCfDlcCheck                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs the data length checks on    **
**                        consecutive frames                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpRxNSdu                                            **
**                        LucReceivedDlc                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblDlcErrorFlag                                     **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaChannelRam        **
**                                                 CanTp_GaaBytePos           **
**                Cantp_Channel_Id      **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, CANTP_CODE) CanTp_RxCfDlcCheck(P2CONST(CanTp_RxNsduStatic,
    AUTOMATIC, CANTP_CONST) LpRxNSdu, uint8 LucReceivedDlc)
{
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  uint16 LusByteCounter;
  uint8 LucBytePos;
  uint8 LucPayloadDataLength;
  boolean LblDlcErrorFlag;
  uint8 LucIteration;
  uint8 LucDiscreteLen;
  uint8 LucTotalLength;
  uint8 LucRxDl;

  /* Initialise the Default value as No Datalength error */
  LblDlcErrorFlag = CANTP_FALSE;
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) || (STD_ON == CANTP_RX_MIXED_ADDRESS))
  /* Get the N_PCI position if transmit NSDU is configured as Extended */
  LucBytePos = CanTp_GaaBytePos[LpRxNSdu->ucAddressingMode] + CANTP_CF_PCI_BYTES;
  #else
  /* Initialise the Addressing format value as Standard */
  LucBytePos = CANTP_CF_PCI_BYTES;
  #endif
  #if (STD_OFF == CANTP_SINGLE_CHANNEL)

  /* Get the channel according to receive SDU structure */
  LpChannelRam = &CanTp_GaaChannelRam[LpRxNSdu->ddChannelId];
  #else
    LpChannelRam = &CanTp_GaaChannelRam[Cantp_Channel_Id];
  #endif
  /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Genderated array index in range" */
  LucRxDl = CanTp_GaaRxDl[LpChannelRam->ddActivePduId];

  #if (CANTP_FD_SUPPORT == STD_ON)
  if((CANTP_CANFD_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType)||\
		   (CANTP_CANFD_PHYSICAL_ADDRESS == LpRxNSdu->ucTaType))
  {
    LucPayloadDataLength = LucRxDl - LucBytePos;
  }else
  #endif/*(CANTP_FD_SUPPORT == STD_ON)*/
  {
    /* Get the current frame length */
    LucPayloadDataLength = CANTP_EIGHT - LucBytePos;
  }

  LusByteCounter = LpChannelRam->usByteCounter;


  /* 1. For All CFs*/
  /* If Padding is on, DLC 2...7 must be padded to DLC 8 */
  #if(CANTP_RX_SDU_PADDING_ACTIVATION == STD_ON)
  if((LpRxNSdu->blRxPaddingActivation == CANTP_TRUE) && (LucReceivedDlc < CANTP_EIGHT))
  {
    LblDlcErrorFlag = CANTP_TRUE;
  }
  #endif

  /* 2. For CFs except for Last CF */
  if(LusByteCounter > LucPayloadDataLength)
  {
    /*LucReceivedDlc: CAN_DL / ucRxSduMaxLength: RX_DL*/
    if(LucReceivedDlc != LucRxDl)
    {
      LblDlcErrorFlag = CANTP_TRUE;
    }
  }
  /* 3. For Last CF */
  else
  {
    LucTotalLength = (uint8)LusByteCounter + LucBytePos;

    /* Last CF's CAN_DL is equal to or less than 8 byte */
    /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if(LucTotalLength <= (uint8)CANTP_EIGHT)
    { 
      #if(CANTP_RX_SDU_PADDING_ACTIVATION == STD_OFF)
      if(LucTotalLength != LucReceivedDlc)
      {
        LblDlcErrorFlag = CANTP_TRUE;
      }
      else
      {
        /* Do nothing */
      }
      #else
      if((LpRxNSdu->blRxPaddingActivation == CANTP_FALSE) && (LucTotalLength != LucReceivedDlc))
      {
        LblDlcErrorFlag = CANTP_TRUE;
      }
      else if((LpRxNSdu->blRxPaddingActivation == CANTP_TRUE) && (LucReceivedDlc != CANTP_EIGHT))
      {
        LblDlcErrorFlag = CANTP_TRUE;
      }
      else
      {
        /* Do nothing */
      }
      #endif
    }
    /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    else
    {
      LucDiscreteLen = 0;

      /* Find Discrete DLC for total length of remaining data */
      for(LucIteration = 0 ; LucIteration < CANTP_SEVEN ; LucIteration ++)
      {
        /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "condition will be executed based on the configured values" */
        if(LucTotalLength <= Cantp_GaaDiscreteLength[LucIteration].curDiscreteLength)
        {        
          LucDiscreteLen = Cantp_GaaDiscreteLength[LucIteration].curDiscreteLength;
          break;
        }
      }

      /* Mandatory Padding Check */
      if(LucDiscreteLen != LucReceivedDlc)
      {
        LblDlcErrorFlag = CANTP_TRUE;
      }      
    }

    if(LblDlcErrorFlag == CANTP_FALSE)
    {
      LucPayloadDataLength = (uint8)LusByteCounter;
    }
  }
  LpChannelRam->ucCurrentFrameLen = LucPayloadDataLength;
  return (LblDlcErrorFlag);
} /* End of CanTp_RxCfDlcCheck(uint8 LucReceivedDlc) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RxNewframeDlcCheck                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs the data length checks on    **
**                        new frames                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpRxNSdu                                            **
**                        LucReceivedDlc                                      **
**                        LpSrcPtr                                            **
**                        LddDecodedSduLength                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblDlcErrorFlag                                     **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaChannelRam        **
**                                                 CanTp_GaaBytePos           **
**                Cantp_Channel_Id      **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, CANTP_CODE) CanTp_RxNewframeDlcCheck(P2CONST(CanTp_RxNsduStatic,
    AUTOMATIC, CANTP_CONST) LpRxNSdu, P2CONST(uint8, AUTOMATIC, CANTP_CONST)
  LpSrcPtr, uint8 LucReceivedDlc, uint32 LddDecodedSduLength)
{
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  uint8 LucBytePos;
  uint8 LucPci;
  uint8 LucPciByte;
  boolean LblDlcErrorFlag;
  uint8 LucRxDl;
  #if(CANTP_FD_SUPPORT == STD_ON)
  uint8 LucIteration;
  uint8 LucPrevDiscreteLen;
  uint8 LucDiscreteLen;
  #endif

  LblDlcErrorFlag = CANTP_FALSE;
  
  /* polyspace +5 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
  #if (STD_OFF == CANTP_SINGLE_CHANNEL)
  /* Get the channel according to receive SDU structure */
  LpChannelRam = &CanTp_GaaChannelRam[LpRxNSdu->ddChannelId];
  #else
  /*LpChannelRam = &CanTp_GaaChannelRam[CANTP_CHANNEL_ID];*/
  LpChannelRam = &CanTp_GaaChannelRam[Cantp_Channel_Id];
  #endif
  
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) || (STD_ON == CANTP_RX_MIXED_ADDRESS))
  /* Get the N_PCI position if transmit NSDU is configured as Extended */
  LucBytePos = CanTp_GaaBytePos[LpRxNSdu->ucAddressingMode];
  #else
  /* Initialise the Addressing format value as Standard */
  LucBytePos = (uint8)CANTP_ZERO;
  #endif
  /* Get the N_PCI byte */
  LucPciByte = *LpSrcPtr;

  /* Decode the N_PCI byte for PCI information */
  LucPci = (uint8)(LucPciByte & (uint8)CANTP_PCI_MASK);

  #if (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION)
  /* If Padding is On, either Classic or CAN FD frames must be padded 8 bytes at least */
  if((LpRxNSdu->blRxPaddingActivation == CANTP_TRUE) &&
     (LucReceivedDlc < (uint8)CANTP_EIGHT))
  {
    LblDlcErrorFlag = CANTP_TRUE;
  }
  #endif /* End of if (STD_ON == CANTP_RX_SDU_PADDING_ACTIVATION) */

  #if (CANTP_FD_SUPPORT == STD_ON)

  LucPrevDiscreteLen = 0;
  LucDiscreteLen = 0;

  /* #19445: To Check Discrete Length Padding */ 
  if (((CANTP_CANFD_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType)||\
			  (CANTP_CANFD_PHYSICAL_ADDRESS == LpRxNSdu->ucTaType))) 
  {
    if(LucReceivedDlc <= 8)
    {
      /* Do Nothing */
    }
    /* FD Padding Byte Check - DLC 9..15: Check Mandatory Padding */
    else if(LucReceivedDlc < 65)
    {
      LblDlcErrorFlag = CANTP_TRUE;
     
      for(LucIteration = 0 ; LucIteration < CANTP_SEVEN ; LucIteration ++)
      {
        if(LucReceivedDlc == Cantp_GaaDiscreteLength[LucIteration].curDiscreteLength)
        {
          LblDlcErrorFlag = CANTP_FALSE;
          
          LucDiscreteLen = Cantp_GaaDiscreteLength[LucIteration].curDiscreteLength;
          LucPrevDiscreteLen = Cantp_GaaDiscreteLength[LucIteration].prevDiscreteLength;

          break;
        }
      }
    }
    /* FD Length check: Maximum supported byte: 64 */
    else
    {
      LblDlcErrorFlag = CANTP_TRUE;
    }
  }
  #endif 

  
  /* Now we only suppoort PduLengthType in uint16. */
  if(65535 < LddDecodedSduLength)
  {
    LblDlcErrorFlag = CANTP_TRUE;
  }

  if (CANTP_FALSE == LblDlcErrorFlag)
  {		
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Genderated array index in range" */
    LucRxDl = CanTp_GaaRxDl[LpChannelRam->ddActivePduId];

    /* In case of Single Frame */
    if ((uint8)CANTP_SF_PCI == LucPci)
    {
      #if (CANTP_FD_SUPPORT == STD_ON) 
      /* In case of CAN-FD */
      if ((CANTP_CANFD_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType)||\
    			  (CANTP_CANFD_PHYSICAL_ADDRESS == LpRxNSdu->ucTaType))
      {
        /* In case CAN_DL <= 8 */
        if(LucReceivedDlc <= 8)
        {
          /* 1. Check if SF_DL exceeds CAN_DL-1(normal add.) or CAN_DL-2(mixed/extended add.) */
          if(LucReceivedDlc < (LddDecodedSduLength + LucBytePos + CANTP_ONE))
          {
             LblDlcErrorFlag = CANTP_TRUE;
          }
          #if (STD_OFF == CANTP_RX_SDU_PADDING_ACTIVATION)  
          /*Redmine #19445*/
          /* 2. Check SF_DL and CAN_DL are matched only in case of optimized CAN_DL (PADDING ACTIVATION is STD_OFF)*/
          else if(LucReceivedDlc != (LddDecodedSduLength + LucBytePos + CANTP_ONE))
          {
             LblDlcErrorFlag = CANTP_TRUE;
          }
          #endif
          /* 3. Check if SF_DL is 0 */
          else if(LddDecodedSduLength == CANTP_ZERO)
          {
             LblDlcErrorFlag = CANTP_TRUE;
          }
          else
          {
            /* Do Nothing */
          }
        }
        /* In case CAN_DL > 8*/
        else
        {          
          /* 1. If first PCI byte is not equal to 0 */
          if(!((PduLengthType)LucPciByte == CANTP_ZERO))
          {
            LblDlcErrorFlag = CANTP_TRUE;
          }

          /* 2. Check SF_DL and CAN_DL are matched */
          else if((LddDecodedSduLength < ((uint32)LucPrevDiscreteLen - CANTP_ONE - LucBytePos)) 
                  || (LddDecodedSduLength > ((uint32)LucDiscreteLen - CANTP_TWO - LucBytePos)))
          {
            LblDlcErrorFlag = CANTP_TRUE;
          }
          else
          {
            /* Do Nothing */
          }
        }
      }
      /* In case of Classic CAN*/
      else
      {
        /* 1. Check if SF_DL exceeds CAN_DL-1(normal add.) or CAN_DL-2(mixed/extended add.) */
        if(LucReceivedDlc < (LddDecodedSduLength + LucBytePos + CANTP_ONE))
        {
          LblDlcErrorFlag = CANTP_TRUE;
        }
        #if (STD_OFF == CANTP_RX_SDU_PADDING_ACTIVATION)
        /*Redmine #19445*/
        /* 2. Check SF_DL and CAN_DL are matched only in case of optimized CAN_DL (PADDING ACTIVATION is STD_OFF)*/
        else if(!(LucReceivedDlc == (LddDecodedSduLength + LucBytePos + CANTP_ONE)))
        {
           LblDlcErrorFlag = CANTP_TRUE;
        }
        #endif
        /* 3. Check if SF_DL is 0 */
        else if(LddDecodedSduLength == CANTP_ZERO)
        {
           LblDlcErrorFlag = CANTP_TRUE;
        }
        /* 4. Check LddDecodedSduLength validity - does it exceed maximum capacity */
        else if (LddDecodedSduLength > ((uint32)CANTP_SEVEN - LucBytePos))
        {
          LblDlcErrorFlag = CANTP_TRUE;
        }
        else
        {
          /* Do Nothing */
        }
      }
      #else /* (CANTP_FD_SUPPORT == STD_ON)  */
      /* In case of Classic CAN*/
      /* 1. Check if SF_DL exceeds CAN_DL-1(normal add.) or CAN_DL-2(mixed/extended add.) */
      if(LucReceivedDlc < (LddDecodedSduLength + LucBytePos + CANTP_ONE))
      {
         LblDlcErrorFlag = CANTP_TRUE;
      }
      #if (STD_OFF == CANTP_RX_SDU_PADDING_ACTIVATION)
      /*Redmine #19445*/
      /* 2. Check SF_DL and CAN_DL are matched only in case of optimized CAN_DL (PADDING ACTIVATION is STD_OFF)*/
      else if(!(LucReceivedDlc == (LddDecodedSduLength + LucBytePos + CANTP_ONE)))
      {
         LblDlcErrorFlag = CANTP_TRUE;
      }      
      #endif
      /* 3. Check if SF_DL is 0 */
      else if(LddDecodedSduLength == CANTP_ZERO)
      {
         LblDlcErrorFlag = CANTP_TRUE;
      }
      /* 4. Check LddDecodedSduLength validity - does it exceed maximum capacity*/
      else if (LddDecodedSduLength > ((uint32)CANTP_SEVEN - LucBytePos))
      {
        LblDlcErrorFlag = CANTP_TRUE;
      }
      else
      {
        /* Do Nothing */
      } 
      #endif /* (CANTP_FD_SUPPORT == STD_ON) */
    } /* if(LucPci == CANTP_SF_PCI) */

    /* In case of First Frame */
    else
    { 
      /* 1. Check if CAN_DL is less than 8 */ 
      if(LucRxDl < ((uint8)(CANTP_EIGHT)))
      {
         LblDlcErrorFlag = CANTP_TRUE;
      }
      /* 2. Check if it has escape sequence even though FF_DL is less than 4095 byte */
      else if((LpSrcPtr[CANTP_ONE] == CANTP_ZERO) 
              && ((LpSrcPtr[CANTP_ZERO] & (uint8)CANTP_FF_ESCAPE_FIRST_BYTE_LOW_NIBBLE_MASK) == CANTP_ZERO))
      {
        if(LddDecodedSduLength <= 4095)
        {
          LblDlcErrorFlag = CANTP_TRUE;
        }
      }
      /* 3. Check if received FF_DL is less than min(FF_DL) - should be transmitted by SF */
      /* 3.1. TX_DL of sender is equal to 8 */
      else if((LucRxDl == CANTP_EIGHT) && (((uint32)CANTP_EIGHT - LucBytePos) > LddDecodedSduLength))
      {
         LblDlcErrorFlag = CANTP_TRUE;
      }
      /* 3.2. TX_DL of sender is more than 8 */
      else if((LucRxDl > CANTP_EIGHT) 
          && (LddDecodedSduLength < (((uint32)LucRxDl - CANTP_ONE) - LucBytePos)))
      {
         LblDlcErrorFlag = CANTP_TRUE;
      }
      #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)
      /* 4. Functionally addressed FirstFrame shall be ignored. */
      #if (CANTP_FD_SUPPORT == STD_ON)
      else if(((uint8)CANTP_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType) ||
         ((uint8)CANTP_CANFD_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType))
      #else
      else if((uint8)CANTP_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType)
      #endif
      {
        LblDlcErrorFlag = CANTP_TRUE;
      }
      #endif
  	  else
  	  {
  	    /* Do Nothing */
  	  }
    } /* End of In case of First Frame */

    if (CANTP_FALSE == LblDlcErrorFlag)
    {
      /* Check the SDU length */
      if (LddDecodedSduLength < LpRxNSdu->usRxSduLength)
      {
        LblDlcErrorFlag = CANTP_TRUE;
      }
    } /* if(LblDlcErrorFlag == CANTP_FALSE) */
   } /* if(LblDlcErrorFlag == CANTP_FALSE) */

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)

  if (CANTP_TRUE == LblDlcErrorFlag)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_RXINDICATION_SID, CANTP_E_INVALID_RX_LENGTH);
  }
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  return (LblDlcErrorFlag);
} /* End of CanTp_RxNewframeDlcCheck(P2CONST(CanTp_RxNsduStatic, AUTOMATIC,
   * CANTP_CONST) LpRxNSdu, P2CONST(uint8, AUTOMATIC, CANTP_CONST) LpSrcPtr,
   * uint8 LucReceivedDlc, uint32 LddDecodedSduLength) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RxBinarySearch                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs the binary search to find    **
**                        the Sdu for extended addressing modes               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpFirstSduMapPtr                                    **
**                        LucSize                                             **
**                        LucRxNsa                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LpSduMapPtr                                         **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS)) || ((STD_ON == CANTP_TX_EXTENDED_ADDRESS)\
  || (STD_ON == CANTP_TX_MIXED_ADDRESS)))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
/* polyspace +1 MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
FUNC(P2CONST(CanTp_RxNSaOrNAeSduMapping, AUTOMATIC, CANTP_CONST),
  CANTP_CODE) CanTp_RxBinarySearch(P2CONST(CanTp_RxNSaOrNAeSduMapping,
    AUTOMATIC, CANTP_CONST) LpFirstSduMapPtr, uint8 LucSize, uint8 LucRxNsa)
{
  P2CONST(CanTp_RxNSaOrNAeSduMapping, AUTOMATIC, CANTP_CONST) LpSduMapPtr;
  uint8 LucTpCurrNSaOrNAe;
  uint8 LucLow;
  uint8 LucHigh;
  uint8 LucMid;

  /* Initialize LucHigh variable with number of Rx Sdus associated to the Pdu */
  /* polyspace +1 DEFECT:SIGN_CHANGE [Not a defect: Justified] "Check the calling function. so Overflow can not occur. " */ 
  LucHigh = LucSize - (uint8)CANTP_ONE;

  /* Initialize LucLow variable with one */
  LucLow = CANTP_ONE;

  /* Initialize return value with null pointer */
  LpSduMapPtr = NULL_PTR;

  /* Get the lower limit of Nsa */
  /* polyspace-begin MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Genderated array index in range" */
  LucTpCurrNSaOrNAe = LpFirstSduMapPtr->ucNSaOrNAe;

  /* Check whether search Nsa is in range */
  /* polyspace-begin MISRA-C3:18.4 [Not a defect: Justified] "No Impact" */
  if ((LucRxNsa >= LucTpCurrNSaOrNAe) &&
      (LucRxNsa <= ((LpFirstSduMapPtr + LucHigh)->ucNSaOrNAe)))
  /* polyspace-end MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Genderated array index in range" */		
  {
    /* Check whether requested Nsa is same as first Nsa of the list */
    if (LucRxNsa != LucTpCurrNSaOrNAe)
    {
      do
      {
        /* Get the middle index number */
        LucMid = (LucHigh + LucLow) >> (uint8)CANTP_ONE;

        /* Get the Nsa of the mid Tp Rx PDU */
        LucTpCurrNSaOrNAe = ((LpFirstSduMapPtr + LucMid)->ucNSaOrNAe);

        /* Compare Nsa with the requested one */
        if (LucTpCurrNSaOrNAe == LucRxNsa)
        {
          /* Update the return pointer with the Rx SDU mapping structure */
          LpSduMapPtr = (LpFirstSduMapPtr + LucMid);

          /* Set LucHigh to zero to break the loop */
          LucHigh = (uint8)CANTP_ZERO;
        } /* End of if (LucTpCurrNSaOrNAe == LucRxNsa) */
        else
        {
          /* Compare the Nsa with the requested one */
          if (LucRxNsa < LucTpCurrNSaOrNAe)
          {
            /* If the received Nsa is lower, update LucHigh */
            LucHigh = LucMid - (uint8)CANTP_ONE;
          }
          else
          {
            /* If the received Nsa is higher, update LucLow */
            LucLow = LucMid + (uint8)CANTP_ONE;
          }
        } /* end if(LucTpCurrNSaOrNAe == LucRxNsa) */
      } while (LucLow <= LucHigh);
    } /* if(LucRxNsa != LucTpCurrNSaOrNAe) */
    else
    {
      /* Update the return pointer with the actual Sdu mapping structure */
      LpSduMapPtr = LpFirstSduMapPtr;
    }
  } 
  /* polyspace-end MISRA-C3:18.4 [Not a defect: Justified] "No Impact" */
    /*
     * if((LucRxNsa >= LucTpCurrNSaOrNAe) &&...
     * Return Sdu mapping pointer
     */
  return (LpSduMapPtr);
} /* End of CanTp_RxBinarySearch(P2CONST(CanTp_RxNSaOrNAeSduMapping, AUTOMATIC,
   * CANTP_CONST) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||
        *(STD_ON == CANTP_RX_MIXED_ADDRESS)) || ((CANTP_TX_EXTENDED_ADDRESS ==
        * STD_ON) || (STD_ON == CANTP_TX_MIXED_ADDRESS))) */

/*******************************************************************************
** Function Name        : CanTp_CopyRxDatToLocalBuff                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs the binary search to find    **
**                        the Sdu for extended addressing modes               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpChannelRam                                        **
**                        LpRxSrcPtr                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_CopyRxDatToLocalBuff(P2VAR(CanTp_ChannelRam,
    AUTOMATIC,CANTP_VAR) LpChannelRam, P2CONST(
    uint8, AUTOMATIC, CANTP_CONST) LpRxSrcPtr)
{
  uint8 LucCurrentFrameLen;
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) LpDataDstnPtr;
  P2CONST(uint8, AUTOMATIC, CANTP_CONST) LpCpyRxSrcPtr = LpRxSrcPtr;

  /* Get Current frameLen for copy */
  LucCurrentFrameLen = LpChannelRam->ucCurrentFrameLen;
  
  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  #if (STD_ON == CANTP_FD_SUPPORT)
  if (CANTP_SIXTYFOUR < LucCurrentFrameLen)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_COPYRXDATTOLOCALBUFF_SID, CANTP_E_INVALID_RX_LENGTH);
  }
  #else
  if (CANTP_EIGHT < LucCurrentFrameLen)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_COPYRXDATTOLOCALBUFF_SID, CANTP_E_INVALID_RX_LENGTH);
  }
  #endif
  else
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    /* Set the flow status as wait */
    LpChannelRam->ucFlowStatus = (uint8)CANTP_FS_WT;

    /* Update the buffer state to indicate waiting for receive buffer */
    LpChannelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY_INITREQ;

    /* Get the address of CanTp local buffer */
    LpDataDstnPtr = &LpChannelRam->aaDataBuffer[CANTP_ZERO];

    /* Copy the data from lower layer to CanTp local buffer */
    while (LucCurrentFrameLen != (uint8)CANTP_ZERO)
    {
      /* Copy the contents of Source pointer to Destination pointer */
      /* polyspace-begin RTE:IDP [Not a defect: Justified] "Configured memory access index" */ 
      /* polyspace-begin RTE:NIV [Not a defect: Justified] "Initialized variable" */    
      /* polyspace +1 MISRA-C3:18.1 [Not a defect: Justified] "Pointer is not a NULL and valid" */ 
      *LpDataDstnPtr = *LpCpyRxSrcPtr;
      /* polyspace-end RTE:NIV [Not a defect: Justified] "Initialized variable" */
      /* polyspace-end RTE:IDP [Not a defect: Justified] "Configured memory access index" */  

      /* Increment the destination pointer */
      LpDataDstnPtr++;

      /* Increment the source pointer */
      LpCpyRxSrcPtr++;

      /* Decrement the upper layer byte count */
      LucCurrentFrameLen--;
    } /* End of while(LpChannelRam->ucCurrentFrameLen != CANTP_ZERO) */

    /* Update the channel state to indicate waiting for receive buffer */
    LpChannelRam->ucChannelState = (uint8)CANTP_RXBUF_WAIT;

    /* After finishing data from CAN driver rx pointer to CanTp Local Data Buffer, Update pUpLayerBuffPtr to Local Data Buffer */
    LpChannelRam->pUpLayerBuffPtr = &LpChannelRam->aaDataBuffer[CANTP_ZERO];
  }
} /* End of CanTp_CopyRxDatToLocalBuff(P2VAR(CanTp_ChannelRam, AUTOMATIC,
   * CANTP_VAR) LpChannelRam, P2CONST(uint8, AUTOMATIC, CANTP_CONST) LpRxSrcPtr)
   **/

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
** Function Name        : CanTp_RxBufferChk                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function will check for buffer availabilty and **
**                        if buffer i sbusy it will perform necessary         **
**                        operation                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpChannelRam                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : CanTp_CopyRxDatToLocalBuff **
**                                                 CanTp_ReceptionComplete    **
**                                                 CanTp_TransmitFc           **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_RxBufferChk(P2VAR(CanTp_ChannelRam,
    AUTOMATIC, CANTP_VAR) LpChanelRam)
{
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) LpRxSrcPtr;

  /* Initialize the source pointer */
  LpRxSrcPtr = LpChanelRam->pUpLayerBuffPtr;

  if ((uint8)CANTP_ZERO == LpChanelRam->ucLocalDataByteIndex)
  {
    /* Copy data received to the local buffer */
    CanTp_CopyRxDatToLocalBuff(LpChanelRam, LpRxSrcPtr);
  }
  #if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)

  /* Send the flow control frame if the frame is not a single frame */
  if (LpChanelRam->ucFrameType != (uint8)CANTP_SF_PCI)
  {
    /* Check whether the WFTmax counter value reaches the maximum configured
     * value.
     */
    if ((uint16)CANTP_ZERO == LpChanelRam->usRxWftMax)
    {
      /* Update the Tp Buffer status */
      LpChanelRam->ucBufferState = (uint8)CANTP_RX_NOTRDY;

      /* Update the CanTp local data length */
      LpChanelRam->ucLocalDataByteIndex = (uint8)CANTP_ZERO;

      /* Invoke upper layer Rx Indication to abort the reception of
       * this N-SDU with the result NTFRSLT_E_WFT_OVRN
       */
      CanTp_ReceptionComplete(LpChanelRam, (NotifResultType)NTFRSLT_E_WFT_OVRN);
    } /* End of if (CANTP_ZERO == LpChanelRam->usRxWftMax) */
    else
    {
      /* Decrement the WFTmax counter to send only the maximum number of flow
       * control frame */
      (LpChanelRam->usRxWftMax)--;
      
      /* Update the flow status as wait */
      LpChanelRam->ucFlowStatus = (uint8)CANTP_FS_WT;

      /* Transmit FC if Tx confirmation is not awaited
       *   for previous Transmission*/
      if ((uint8)CANTP_TX_CONF_IDLE == LpChanelRam->ucTxConfirmState)
      {
        /* Transmit the flow control frame */
        CanTp_TransmitFc(LpChanelRam);
      }
    } /* End of else */
  } /* end if(LpChanelRam->ucFrameType != CANTP_SF_PCI) */
  #endif /* End of if (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING) */
} /* End of CanTp_RxBufferChk(P2VAR(CanTp_ChannelRam, */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON  == CANTP_RX_NSDU) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

