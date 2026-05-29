/*******************************************************************************
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_TxInternal.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Internal Functions implementation for CanTp module            **
**              CanTp_RequestCopyTxData                                       **
**              CanTp_CanIfTransmit                                           **
**              CanTp_ProcessRxFc                                             **
**              CanTp_TransmissionComplete                                    **
**              CanTp_UpdateTxFrameStatus                                     **
**              CanTp_TxDlcCheck                                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
**                                                                            **
*********************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.11.2    17-May-2021   NguyenTD3      Redmine #28737                      **
** 1.11.1    12-Jan-2021   SM Kwon        Redmine #27640                      **
** 1.10.2    03-Nov-2020   SM Kwon        Redmine #25248                      **
** 1.10.1    07-Oct-2019   SM Kwon        Redmine #19617                      **
** 1.10.0    10-Sept-2019  SM Kwon        Redmine #19217                      **
** 1.9.0     12-Jul-2019   SM Kwon        Redmine #16658, #17748              **
** 1.8.1     13-Mar-2019   SM Kwon        Redmine #15962, #16559              **
** 1.8.0     21-Mar-2018   Lim Jong Sun   Redmine #11554                      **
** 1.7.11    19-Dec-2017   Lim Jong Sun   Redmine #8900                       **
** 1.7.10    10-Apr-2017   Lim Jong Sun   Redmine #8001                       **
** 1.7.3     31-Aug-2015   Lim Jong Sun   Fixed Run-Time Error                **
** 1.0.1     20-Jun-2013   Lim Jong Sun   Library Release Version             **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp.h"                /* CanTp Module Header File */
#include "SchM_CanTp.h"           /* SchM Header File */
#include "CanTp_PCTypes.h"        /* CanTp PCTypes Header File */
#include "CanTp_TxInternal.h"     /* CanTp TxInternal Header File */
#include "CanTp_Ram.h"            /* CanTp Global RAM variables header file */
#include "PduR_CanTp.h"           /* PduR Header File */
#if (STD_ON == CANTP_DEV_ERROR_DETECT)
#include "Det.h"                  /* DET header file */
#endif
#include "CanIf.h"                /* CanIf Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANTP_TXINTERNAL_C_AR_RELEASE_MAJOR_VERSION    4
#define CANTP_TXINTERNAL_C_AR_RELEASE_MINOR_VERSION    0
#define CANTP_TXINTERNAL_C_AR_RELEASE_REVISION_VERSION 3

/* CANTP software version information */
#define CANTP_TXINTERNAL_C_SW_MAJOR_VERSION            1
#define CANTP_TXINTERNAL_C_SW_MINOR_VERSION            11

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANTP_AR_RELEASE_MAJOR_VERSION !=\
 CANTP_TXINTERNAL_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp_TxInternal.c : Mismatch in Specification Major Version"
#endif
#if (CANTP_AR_RELEASE_MINOR_VERSION !=\
 CANTP_TXINTERNAL_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp_TxInternal.c : Mismatch in Specification Minor Version"
#endif
#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_TXINTERNAL_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp_TxInternal.c : Mismatch in Specification Revision Version"
#endif
#if (CANTP_SW_MAJOR_VERSION != CANTP_TXINTERNAL_C_SW_MAJOR_VERSION)
#error "CanTp_TxInternal.c : Mismatch in Software Major Version"
#endif
#if (CANTP_SW_MINOR_VERSION != CANTP_TXINTERNAL_C_SW_MINOR_VERSION)
#error "CanTp_TxInternal.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_UpdateTxFrameStatus(P2VAR(CanTp_ChannelRam,
    AUTOMATIC, CANTP_VAR) LpChannelRam, P2CONST(CanTp_TxNsduStatic,
    AUTOMATIC, CANTP_CONST) LpTxNSdu);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_TX_NSDU ) */
/*******************************************************************************
** Function Name        : CanTp_TransmissionComplete                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for completing the            **
**                        transmission and indicate the upper layer about     **
**                        transmission result                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpChannelRam                                        **
**                      : LddResult                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaTxSduStatic       **
**                    Cantp_Channel_Id    **
**                        Function(s) invoked    : PduR_CanTpTxConfirmation   **
**                                                 Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_TransmissionComplete(P2VAR(CanTp_ChannelRam,
    AUTOMATIC, CANTP_VAR) LpChannelRam, NotifResultType LddResult)
{
  P2CONST(CanTp_TxNSduDynamic, AUTOMATIC, CANTP_CONST) LpTxNSduDyna;
  #if (STD_OFF == CANTP_SINGLE_CHANNEL)
  P2CONST(CanTp_TxNsduStatic, AUTOMATIC, CANTP_CONST) LpTxNSdu = NULL_PTR;
  #endif
  PduIdType LddActiveSduId;
  
  /* Initialize the active pdu id */
  LddActiveSduId = LpChannelRam->ddActivePduId;

  /* Initialize the channel state to IDLE (i.e. TxWait and RxWait) */
  LpChannelRam->ucChannelState = (uint8)CANTP_WAIT;

  /* Reset Tx Confirmation state to IDLE */
  LpChannelRam->ucTxConfirmState = (uint8)CANTP_TX_CONF_IDLE;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  if(LddActiveSduId > CANTP_MAX_TX_SDUID)
  {
    /* Report to DET */
   (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TXCONFIRMATION_SID, CANTP_E_INVALID_TX_ID);
  }
  else
  #endif
  {
    /* Get the dynamic RxNSdu structure Pointer */
    LpTxNSduDyna = &CanTp_GaaTxSduDynamic[LddActiveSduId];

    #if(CANTP_SINGLE_CHANNEL == STD_OFF)
      /* Get the connection channel structure address */
      LpTxNSdu = &CanTp_GaaTxSduStatic[LddActiveSduId];
    #endif /* End of if ( STD_OFF == CANTP_SINGLE_CHANNEL) */

    /* Invoke upper layer Rx indication with LddResult */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
    PduR_CanTpTxConfirmation(LpTxNSduDyna->ddUpConfirmationSduId, LddResult);

    /* Check the communication Result value other than NTFRSLT_OK to report Dem*/
    if (LddResult != (NotifResultType)NTFRSLT_OK)
    {
      #if (STD_ON == CANTP_DEV_ERROR_DETECT)

      /* Report error though DET with CANTP_E_TX_COM if any timeout error */
      if ((LddResult == (NotifResultType)NTFRSLT_E_TIMEOUT_A) ||
          (LddResult == (NotifResultType)NTFRSLT_E_TIMEOUT_BS))
      {
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_TXCONFIRMATION_SID, CANTP_E_TX_COM);
      } /* if((LddResult == NTFRSLT_E_TIMEOUT_A) ||(LddResult == ..) */
      else /* Report error though DET with CANTP_E_COM if other than timeout
            *   error */
      {
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_TXCONFIRMATION_SID, CANTP_E_COM);
      }
      #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
    } /* if(LddResult != NTFRSLT_OK) */

    #if(CANTP_SINGLE_CHANNEL == STD_OFF)
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect Justify with annotations] "Genderated array index in range" */	
    CANTP_STOP_ALL_TX_TIMERS(LpTxNSdu->ddChannelId);
    #else
    CANTP_STOP_ALL_TX_TIMERS(Cantp_Channel_Id);
    #endif
  }
} /* End of CanTp_TransmissionComplete(P2VAR(CanTp_ChannelRam, AUTOMATIC,
   * CANTP_VAR) LpChannelRam, NotifResultType LddResult) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON == CANTP_TX_NSDU ) */

/*******************************************************************************
** Function Name        : CanTp_RequestCopyTxData                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function requests upper Layer to copy Tx data  **
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
** Remarks              : Global Variable(s)     : CanTp_GaaTxSduStatic,      **
**                                                 CanTp_GaaChannelMapping,   **
**                                                 CanTp_GaaTimers,           **
**                 Cantp_Channel_Id    **
**                        Function(s) invoked    : PduR_CanTpCopyTxData       **
**                                                 CanTp_TransmissionComplete **
**                                                 CanTp_CanIfTransmit        **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_RequestCopyTxData(P2VAR(CanTp_ChannelRam,
    AUTOMATIC, CANTP_VAR) LpChannelRam)
{
  #if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) &&\
  ((STD_OFF == CANTP_SINGLE_CHANNEL) ||\
  (STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION) ||\
  (STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
  (STD_ON == CANTP_FD_SUPPORT)))
  P2CONST(CanTp_TxNsduStatic, AUTOMATIC, CANTP_CONST) LpTxNSdu = NULL_PTR;
  #endif /* End of if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) &&
          *((STD_OFF == CANTP_SINGLE_CHANNEL) ||
          *(STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION) ||
          *(STD_ON  == CANTP_TX_EXTENDED_ADDRESS) || (CANTP_TX_MIXED_ADDRESS ==
          * STD_ON))) */
  PduInfoType LddPdu;
  uint16 LusByteCount;
  PduLengthType LddAvailableDataPtr;
  BufReq_ReturnType LenBufferStatus;
  RetryInfoType LddRetryInfo;

  #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
  uint16 LusNcsTimer;
  CanTp_ChannelType LddChannel;
  #endif
  PduLengthType LddCount;
  #if(CANTP_FD_SUPPORT == STD_ON)
  PduLengthType LddMaxLength;
  #endif
  uint8 LucIndex;
  #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
  uint8 LucChannelIndex;
  #endif
  PduIdType LddActiveSduId;

  /* Initialize the active pdu id */
  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  LddActiveSduId = LpChannelRam->ddActivePduId;
  #endif
  /* Initialize the retry info values */
  /* #8900 TP_NORETRY --> TP_DATACONF */
  LddRetryInfo.TpDataState = (TpDataStateType)TP_DATACONF;

  /* Set data count to default value */
  LddRetryInfo.TxTpDataCnt = (PduLengthType)CANTP_ZERO;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  if(LddActiveSduId > CANTP_MAX_TX_SDUID)
  {
    /* Report to DET */
   (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TXCONFIRMATION_SID, CANTP_E_INVALID_TX_ID);
  }
  #if ((CANTP_FD_SUPPORT == STD_ON) && \
      (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING))
  /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */ 
  else if (((CANTP_CANFD_FUNCTIONAL_ADDRESS == CanTp_GaaTxSduStatic[LddActiveSduId].ucTaType) || \
	  (CANTP_CANFD_PHYSICAL_ADDRESS == CanTp_GaaTxSduStatic[LddActiveSduId].ucTaType)) && \
	  (LpChannelRam->ucLocalDataByteIndex > CanTp_GaaTxSduStatic[LddActiveSduId].ucTxSduMaxLength))
  {
    /* Report to DET */
   (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TXCONFIRMATION_SID, CANTP_E_INVALID_TX_LENGTH);
  }
  else if (CANTP_EIGHT < LpChannelRam->ucLocalDataByteIndex)
  {
    /* Report to DET */
   (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TXCONFIRMATION_SID, CANTP_E_INVALID_TX_LENGTH);
  }
  #else
  else if (CANTP_EIGHT < LpChannelRam->ucLocalDataByteIndex)
  {
    /* Report to DET */
   (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TXCONFIRMATION_SID, CANTP_E_INVALID_TX_LENGTH);
  }
  #endif
  else
  #endif /* (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    #if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) &&\
    ((STD_OFF == CANTP_SINGLE_CHANNEL) ||\
    (STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION) ||\
    (STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_TX_MIXED_ADDRESS) ||\
    (STD_ON == CANTP_FD_SUPPORT)))
    /* Get the TxNSdu structure address */
    LpTxNSdu = &CanTp_GaaTxSduStatic[LpChannelRam->ddActivePduId];
    #endif
    
	#if(CANTP_FD_SUPPORT == STD_ON)
    LddMaxLength = LpTxNSdu->ucTxSduMaxLength;
    #endif
    
    /* Get the number of data bytes to be transmitted */
    LusByteCount = (LpChannelRam->usByteCounter);

    #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
    #if (STD_OFF == CANTP_SINGLE_CHANNEL)   
    /* Get the connection channel structure address */
		/* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
    LddChannel = LpTxNSdu->ddChannelId;
    #else
    /* Get the connection channel structure address */
    /*LddChannel = (CanTp_ChannelType)CANTP_CHANNEL_ID;*/
    LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
    #endif
    #if (STD_ON == CANTP_SINGLE_CHANNEL)
    #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
    LucChannelIndex = CanTp_GaaChannelMapping[LddChannel];
    #else /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
    LucChannelIndex = (uint8)LddChannel;
    #endif
    #else
    #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
    /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if (CANTP_MODE_FULL_DUPLEX == CanTp_GaaChannelMode[LddChannel])
    {
      LucChannelIndex = CanTp_GaaChannelMapping[LddChannel];
    }
    else
    #endif /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
    {
      LucChannelIndex = (uint8)LddChannel;
    }
    /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    #endif

    /* Get the N_Cs Timer value */
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Genderated array index in range" */
    LusNcsTimer = CanTp_GaaTimers[LucChannelIndex][CANTP_NCS_TIMER];

    /* Check if N_Cs timer is  not started */
    if ((uint16)CANTP_ZERO == LusNcsTimer)
    {
      /* Start N_Cs Timer */
      LusNcsTimer =
        CanTp_GaaTxSduDynamic
        [LpChannelRam->ddActivePduId].usNcsTimeoutValue;
    } /* End of if (CANTP_ZERO == LusNcsTimer) */
    #endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */
    /* Get the local data buffer index from where the data needs to be filled */
    LucIndex = LpChannelRam->ucLocalDataByteIndex;
    #if (CANTP_FD_SUPPORT == STD_ON)
    #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
    /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */	
    if ((CANTP_CANFD_FUNCTIONAL_ADDRESS == LpTxNSdu->ucTaType)||\
  		  (CANTP_CANFD_PHYSICAL_ADDRESS == LpTxNSdu->ucTaType))
    {
      LddCount = LddMaxLength - LucIndex;
    }
    else
    #endif/*((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) &&..*/
    #endif/*(CANTP_FD_SUPPORT == STD_ON)*/
    {
      /* Get the number of bytes to be filled in the present frame */
      LddCount = (uint16)CANTP_EIGHT - LucIndex;
    }

	/* Set the destination(local) buffer address */
	LddPdu.SduDataPtr = &(LpChannelRam->aaDataBuffer[LucIndex]);
	#if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)

	if(LpChannelRam->ucFrameType == (uint8)CANTP_FF_PCI)
	{
	LddPdu.SduLength = LddCount;
	}
	/* Check frame type is not a single frame - CF or FF */
	else if (LpChannelRam->ucFrameType == (uint8)CANTP_CF_PCI)
	{
	#if (CANTP_FD_SUPPORT == STD_ON)      
	if ((CANTP_CANFD_FUNCTIONAL_ADDRESS == LpTxNSdu->ucTaType)||\
	  (CANTP_CANFD_PHYSICAL_ADDRESS == LpTxNSdu->ucTaType))
	{
	  #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
	  (STD_ON == CANTP_TX_MIXED_ADDRESS))
	  /* Check if current frame for transmission is the last CF */
	  if (LusByteCount <= ((LddMaxLength - CANTP_ONE) -
			CanTp_GaaBytePos[LpTxNSdu->ucAddressingMode]))

	  #else /* End of if ((STD_ON  == CANTP_TX_EXTENDED_ADDRESS) ||
			 *(STD_ON == CANTP_TX_MIXED_ADDRESS)) */
	  if (LusByteCount <= (LddMaxLength - CANTP_ONE))
	  #endif /* End of if ((STD_ON  == CANTP_TX_EXTENDED_ADDRESS) ||
			  *(STD_ON == CANTP_TX_MIXED_ADDRESS)) */    
	  {
		/* Set the number of bytes to be filled in the  last CF */
		LddPdu.SduLength = (PduLengthType)LusByteCount;
	  }
	  else
	  {
		/* Set the number of bytes to be filled in the  last CF */
		LddPdu.SduLength = LddCount;
	  }
	}
	else
	{
	  #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
	  (STD_ON == CANTP_TX_MIXED_ADDRESS))
	  /* Check if current frame for transmission is the last CF */
	  if (LusByteCount <= (((uint16)CANTP_SEVEN) -
			CanTp_GaaBytePos[LpTxNSdu->ucAddressingMode]))
	  #else /* End of if ((STD_ON  == CANTP_TX_EXTENDED_ADDRESS) ||
			 *(STD_ON == CANTP_TX_MIXED_ADDRESS)) */
	  if (LusByteCount <= (uint16)CANTP_SEVEN)
	  #endif /* End of if ((STD_ON  == CANTP_TX_EXTENDED_ADDRESS) ||
			  *(STD_ON == CANTP_TX_MIXED_ADDRESS)) */
	  {
		/* Set the number of bytes to be filled in the  last CF */
		LddPdu.SduLength = (PduLengthType)LusByteCount;
	  }
	  else
	  {
		/* Set the number of bytes to be filled in the  last CF */
		LddPdu.SduLength = LddCount;
	  }
	}    
	#else /* (CANTP_FD_SUPPORT == STD_ON) */
	#if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
	(STD_ON == CANTP_TX_MIXED_ADDRESS))
	/* Check if current frame for transmission is the last CF */
	if (LusByteCount <= (((uint16)CANTP_SEVEN) -
		  CanTp_GaaBytePos[LpTxNSdu->ucAddressingMode]))
	#else /* End of if ((STD_ON  == CANTP_TX_EXTENDED_ADDRESS) ||
		   *(STD_ON == CANTP_TX_MIXED_ADDRESS)) */

	if (LusByteCount <= (uint16)CANTP_SEVEN)
	#endif /* End of if ((STD_ON  == CANTP_TX_EXTENDED_ADDRESS) ||
			*(STD_ON == CANTP_TX_MIXED_ADDRESS)) */

	{
	  /* Set the number of bytes to be filled in the  last CF */
	  LddPdu.SduLength = (PduLengthType)LusByteCount;
	}
	else
	{
	  /* Set the number of bytes to be filled in the  last CF */
	  LddPdu.SduLength = (PduLengthType)LddCount;
	}
	#endif /* (CANTP_FD_SUPPORT == STD_ON) */
	} /* else if(LpChannelRam->ucFrameType == CANTP_CF_PCI) */
	/* Frame type is single frame */
	else
	#endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */
	{
	/* Set the number of bytes to be filled in the SF */
	LddPdu.SduLength = (PduLengthType)LusByteCount;
	}
	/* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */    

	/* Request to copy the Tx data */
	LenBufferStatus = PduR_CanTpCopyTxData(CanTp_GaaTxSduDynamic
	[LpChannelRam->ddActivePduId].
	ddUpConfirmationSduId, &LddPdu,
	&LddRetryInfo, &LddAvailableDataPtr);

	/* Buffer status is okay */
	if (BUFREQ_OK == LenBufferStatus)
	{
	#if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)

	/* Stop N_Cs timer */
	LusNcsTimer = (uint16)CANTP_ZERO;
	#endif

	/* Check if the frame is last frame */
	if (LusByteCount <= LddCount)
	{
	  /* Set number of bytes to be copied equal to total remaining bytes */
	  LddCount = LusByteCount;
	}

	/* Update the Byte counter and Available buffer length */
	(LpChannelRam->usByteCounter) = LusByteCount - LddCount;

	/* Update the current frame length */
	LpChannelRam->ucCurrentFrameLen = (uint8)(LddCount + LucIndex);

	/* Check if current frame for transmission is SF or FF */
	if (LpChannelRam->ucNewFrameFlag == (uint8)CANTP_TX_SFORFF)
	{
	  /* Transmit the data to lower layer */
	  CanTp_CanIfTransmit(LpTxNSdu);      
	  /*Set the new frame flag status as start of Transmission of CF */
	  LpChannelRam->ucNewFrameFlag = (uint8)CANTP_CONSCFRAME;
	} /* End of if (LpChannelRam->ucNewFrameFlag == CANTP_TX_SFORFF) */
	else
	{
	  /* Set the buffer state to buffer ready */
	  LpChannelRam->ucBufferState = (uint8)CANTP_TX_RDY;
	}
	} /* if(LenBufferStatus == BUFREQ_OK) */
	else if (BUFREQ_E_NOT_OK == LenBufferStatus)
	{
	/* Invoke TxConfirmation with failure */
	CanTp_TransmissionComplete(LpChannelRam, (NotifResultType)NTFRSLT_E_NOT_OK);
	} /* BUFREQ_E_NOT_OK */
	else if (BUFREQ_E_BUSY == LenBufferStatus)
	{
	/* Update the Tp Buffer status */
	LpChannelRam->ucBufferState = (uint8)CANTP_TX_NOTRDY_INITREQ;
	} /* BUFREQ_E_BUSY */
	else
	{
	/* To avoid QAC error */
	}
	#if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
	/* Reload the N_Cs timer */
	CANTP_TIMER_UPDATE_MACRO(LucChannelIndex, CANTP_NCS_TIMER, LusNcsTimer);
	#endif
  }
} /* End of CanTp_RequestCopyTxData(P2VAR(CanTp_ChannelRam, AUTOMATIC,
   * CANTP_VAR) LpChannelRam) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON == CANTP_TX_NSDU ) */

/*******************************************************************************
** Function Name        : CanTp_CanIfTransmit                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to check STmin timer and      **
**                        hence invoke CanIf_Transmit function                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LpTxNSdu                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaChannelMode,      **
**                                                 CanTp_GaaChannelMapping,   **
**                                                 CanTp_GaaChannelRam,       **
**                                                 CanTp_GaaStMinTimers       **
**                 Cantp_Channel_Id    **
**                 Cantp_Padding_Byte    **
**                        Function(s) invoked    : CanTp_UpdateTxFrameStatus  **
**                                                 CanIf_Transmit             **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"

FUNC(void, CANTP_CODE) CanTp_CanIfTransmit(P2CONST(CanTp_TxNsduStatic,
    AUTOMATIC, CANTP_CONST) LpTxNSdu)
{
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  PduInfoType LddPduInfo;
  CanTp_ChannelType LddChannel;
  #if (STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION)
  uint16 LusLength;
  #endif
  uint16 LusNasTimer;
  uint8 LucChannelIndex;
  #if(CANTP_FD_SUPPORT == STD_ON)
  uint8 LucIteration;
  uint8 LucDiscreteLen;
  #endif
	
  #if ((STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) &&\
    (STD_OFF == CANTP_SINGLE_CHANNEL))
  /* Get the connection channel structure address */
  /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
  LddChannel = LpTxNSdu->ddChannelId;
  #else
  /* Get the connection channel structure address */
  /*LddChannel = (CanTp_ChannelType)CANTP_CHANNEL_ID;*/
  LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
  #endif
  

  #if (STD_ON == CANTP_SINGLE_CHANNEL)
  #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
  LucChannelIndex = CanTp_GaaChannelMapping[LddChannel];
  #else /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
  LucChannelIndex = (uint8)LddChannel;
  #endif
  #else
  #if (STD_ON == CANTP_FULL_DUPLEX_MODE)

  if (CANTP_MODE_FULL_DUPLEX == CanTp_GaaChannelMode[LddChannel])
  {
    LucChannelIndex = CanTp_GaaChannelMapping[LddChannel];
  }
  else
  #endif /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
  {
    LucChannelIndex = (uint8)LddChannel;
  }
  #endif /* End of if (STD_ON == CANTP_SINGLE_CHANNEL) */

  /* Get the pointer to channel RAM*/
  LpChannelRam = &CanTp_GaaChannelRam[LucChannelIndex];

  /* Check if the STMin timer expired */
  if ((uint8)CANTP_ZERO == CanTp_GaaStMinTimers[LddChannel])
  {
    LddPduInfo.SduDataPtr = LpChannelRam->aaDataBuffer;
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
    LddPduInfo.SduLength = (PduLengthType)LpChannelRam->ucCurrentFrameLen;

    #if (STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION)
    #if (CANTP_FD_SUPPORT == STD_ON)
    if ((CANTP_CANFD_FUNCTIONAL_ADDRESS == LpTxNSdu->ucTaType)||\
        (CANTP_CANFD_PHYSICAL_ADDRESS == LpTxNSdu->ucTaType)) 
    {
      /* Selective Padding in case of DLC 1..7 */
      if(LddPduInfo.SduLength == CANTP_EIGHT)
      {
        /* Do Nothing */
      }
      else if(LddPduInfo.SduLength < CANTP_EIGHT)
      {
        if (CANTP_TRUE == LpTxNSdu->blTxPaddingActivation)
        {
          /* if LucLength is less than CANTP_EIGHT, it needs to be padded */
          LusLength = (uint16)(LddPduInfo.SduLength);
          LddPduInfo.SduLength = (PduLengthType)CANTP_EIGHT;
          CANTP_MEMCPY(&LddPduInfo.SduDataPtr[LusLength], &Cantp_Padding_Byte[0], (uint8)(CANTP_EIGHT - LusLength));
        }
      }
      /* Mandatory Padding in case of DLC 9...15 */
      else
      {
        LucDiscreteLen = 0;

        /* Find Discreted Data Length for this transmission */
        for(LucIteration = 0; LucIteration < CANTP_SEVEN; LucIteration++)
        {
          if(LddPduInfo.SduLength <= Cantp_GaaDiscreteLength[LucIteration].curDiscreteLength)
          {
            LucDiscreteLen = Cantp_GaaDiscreteLength[LucIteration].curDiscreteLength;
            break;
          }
        }
        /* if LucLength is equal to Discrete Length, it doesn't need to be padded */
        if(LddPduInfo.SduLength < LucDiscreteLen)
        {
          LusLength = (uint16)(LddPduInfo.SduLength);
          LddPduInfo.SduLength = LucDiscreteLen;
          /* polyspace +1 MISRA-C3:D4.11,D4.14 RTE:STD_LIB [Not a defect: Justified] "Valid arguments are passed" */
          CANTP_MEMCPY(&LddPduInfo.SduDataPtr[LusLength], &Cantp_Padding_Byte[0], (uint8)(LucDiscreteLen - LusLength));  
        }
      }
    }
    else
	  #endif/*#if(CANTP_FD_SUPPORT == STD_ON)*/
    {
      /* Check if the SDU is configured for PADDING ACTIVATION equal to STD_ON */
      if (CANTP_TRUE == LpTxNSdu->blTxPaddingActivation)
      {
        if (LddPduInfo.SduLength < (PduLengthType)CANTP_EIGHT)
        { 
           /* if LucLength is less than CANTP_EIGHT, it needs to be padded */
           LusLength = (uint16)(LddPduInfo.SduLength);
           LddPduInfo.SduLength = (PduLengthType)CANTP_EIGHT;
           CANTP_MEMCPY(&LddPduInfo.SduDataPtr[LusLength], &Cantp_Padding_Byte[0], (uint8)(CANTP_EIGHT - LusLength));
         } /* End of if (LddPduInfo.SduLength != CANTP_EIGHT) */
       } /* if(CANTP_TRUE == LpTxNSdu->blTxPaddingActivation) */
    }
    #endif /* End of if (STD_ON == CANTP_TX_SDU_PADDING_ACTIVATION) */

    #if(STD_ON == CANTP_DEV_ERROR_DETECT)
    if(LpChannelRam->ddActivePduId > CANTP_MAX_TX_SDUID)
    {
      /* Report to DET */
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_MAINFUNCTION_SID, CANTP_E_INVALID_TX_ID);
    }
    else
    #endif
    {
      /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect Justify with annotations] "Genderated array index in range" */
      LusNasTimer = (CanTp_GaaTxSduDynamic[LpChannelRam->ddActivePduId].
                     usNasTimeoutValue + ((uint16)(LpChannelRam->ucNewFrameFlag) &
                                          (uint16)CANTP_ONE));     

      /* Start N_As timer */
      CANTP_TIMER_UPDATE_MACRO(LucChannelIndex, CANTP_NAS_TIMER, LusNasTimer);

      /* Update the frame parameters */
      CanTp_UpdateTxFrameStatus(LpChannelRam, LpTxNSdu);

      /* Request lower layer (CanIf) transmit request */
      /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Genderated array index in range" */
      (void)CanIf_Transmit(CanTp_GaaTxSduDynamic[LpChannelRam->ddActivePduId].ddLoTargetPduId, &LddPduInfo);     
    }
  } /* if(CanTp_GaaStMinTimers[LddChannel] == CANTP_ZERO) */
} /* End of CanTp_CanIfTransmit(void) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_TX_NSDU ) */

/*******************************************************************************
** Function Name        : CanTp_UpdateTxFrameStatus                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to update the status of next  **
**                        frame to be sent                                    **
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
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_UpdateTxFrameStatus(P2VAR(CanTp_ChannelRam,
    AUTOMATIC, CANTP_VAR) LpChannelRam, P2CONST(CanTp_TxNsduStatic,
    AUTOMATIC, CANTP_CONST) LpTxNSdu)
{
  uint8 LucNpciPos;
  uint8 LucTxConfirmState;

  #if(CANTP_FD_SUPPORT == STD_ON)
  uint8 LucTxSduMaxLength = LpTxNSdu->ucTxSduMaxLength;
  #endif

  /* Update the PCI byte position*/
  LucNpciPos = LpChannelRam->ucCurrentBytePosition;

  
  #if(STD_ON == CANTP_DEV_ERROR_DETECT)
  #if(CANTP_FD_SUPPORT == STD_ON)
  if((LucTxSduMaxLength > CANTP_SIXTYFOUR) || \
     (LucNpciPos > (LucTxSduMaxLength - CANTP_ONE)))
  #else
  if(CANTP_EIGHT <= LucNpciPos)
  #endif
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
    CANTP_MAINFUNCTION_SID, CANTP_E_INVALID_TX_LENGTH);
  }
  else
  #endif /* (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {	
    /* Check if the frame is not the last frame */
    if (LpChannelRam->usByteCounter != (uint16)CANTP_ZERO)
    {
      #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)

      /* Check if frame counter is greater than 15 */
      if (LpChannelRam->ucFrameCounter >= (uint8)CANTP_MAX_FRAME_COUNTER)
      {
        /* Reset the frame counter */
        LpChannelRam->ucFrameCounter = (uint8)CANTP_ZERO;
      }
      else
      {
        /* Increment frame counter */
        (LpChannelRam->ucFrameCounter)++;
      }
      #endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */

      /* Update the buffer index from where the data needs to be loaded */
      LpChannelRam->ucLocalDataByteIndex = LucNpciPos + (uint8)CANTP_ONE;

      /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Genderated array index in range" */
      if ((LpChannelRam->aaDataBuffer[LucNpciPos] & (uint8)(CANTP_FF_PCI)) ==
          ((uint8)CANTP_FF_PCI))      
      {
        /* Update the Tx confirmation state to CF */
        LucTxConfirmState = (uint8)CANTP_LAST_CF_TX_CONF;
      }
      else
      {
        /* Update the Tx confirmation state to CF */
        LucTxConfirmState = (uint8)CANTP_CF_TX_CONF;
      }
      #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)

      if((LpChannelRam->usBSVar != (uint16)CANTP_ZERO)
         && (LpChannelRam->usBSVar != CANTP_INFINITE_BS))
      {
        /* Decrement the BlockSize variable */
        (LpChannelRam->usBSVar)--;

        if ((uint16)CANTP_ZERO == LpChannelRam->usBSVar)
        {
          /* Update the Tx confirmation state to last CF in the block */
          LucTxConfirmState = (uint8)CANTP_LAST_CF_TX_CONF;
        }
      } /* End of if (LpChannelRam->usBSVar != CANTP_ZERO) */
      #endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */
    } /* Check if the frame is not the last frame */
    else
    {
      /* Update the Tx confirmation state as last frame in the TP message */
      LucTxConfirmState = (uint8)CANTP_SF_LF_TX_CONF;
    }

    /* Copy the Tx confirmation state to global variable */
    LpChannelRam->ucTxConfirmState = LucTxConfirmState;

    /* Update the Tx BufferState state to TX Buffer not ready */
    LpChannelRam->ucBufferState = (uint8)CANTP_TX_NOTRDY;
  }
  #if(CANTP_FD_SUPPORT == STD_OFF)
  CANTP_UNUSED_PTR(LpTxNSdu);
  #endif
} /* End of CanTp_UpdateTxFrameStatus(P2VAR(CanTp_ChannelRam, AUTOMATIC,
   * CANTP_VAR) LpChannelRam) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_TX_NSDU ) */

/*******************************************************************************
** Function Name        : CanTp_ProcessRxFc                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for transmission of           **
**                        flow control to the sender                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LddTxSduId                                          **
**                        CanTpRxPduPtr                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaTxSduStatic,      **
**                                                 CanTp_GaaChannelMode,      **
**                                                 CanTp_GaaChannelMapping,   **
**                                                 CanTp_GaaChannelRam,       **
**                                                 CanTp_GaaSTminMapping,     **
**                                                 CanTp_GaaBytePos           **
**                                                 CanTp_GaaTxSduDynamic      **
**                 Cantp_Main_Function_Period   **
**                 Cantp_Channel_Id         **
**                        Function(s) invoked    : CanTp_TransmissionComplete **
*******************************************************************************/
#if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_ProcessRxFc(PduIdType LddTxSduId, P2CONST(uint8,
    AUTOMATIC, CANTP_CONST) CanTpRxPduPtr)
{
  #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_TX_MIXED_ADDRESS) || (STD_OFF == CANTP_SINGLE_CHANNEL))
  P2CONST(CanTp_TxNsduStatic, AUTOMATIC, CANTP_CONST) LpTxNSdu = NULL_PTR;
  #endif
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  uint8 LucBytePos;
  uint8 LucFlowStatus;
  uint8 LucStMin;
  uint8 LucFrame;
  CanTp_ChannelType LddChannel;
  uint8 LucChannelIndex;
  #if(STD_ON == CANTP_DEV_ERROR_DETECT)
  boolean LblDetResult = E_OK;
  #endif

  /* #8001 */
  #if((STD_ON == CANTP_DEV_ERROR_DETECT) && ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_TX_MIXED_ADDRESS) || (STD_OFF == CANTP_SINGLE_CHANNEL)))
  /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "condition will be executed based on the configured values" */	
  if ((uint16)LddTxSduId > Cantp_Max_Tx_Sduid)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_RXINDICATION_SID, CANTP_E_PARAM_ID);
    LblDetResult = E_NOT_OK;
  }
  else
  {
    LblDetResult = E_OK;
  }
  if(LblDetResult == E_OK) /* End of if (CanTpTxSduId > CANTP_MAX_TX_SDUID) */
  #endif
  {
    #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_TX_MIXED_ADDRESS) || (STD_OFF == CANTP_SINGLE_CHANNEL))
      LpTxNSdu = &CanTp_GaaTxSduStatic[LddTxSduId];
    #endif
    #if (STD_OFF == CANTP_SINGLE_CHANNEL)
    /* Get the connection channel structure address */
    LddChannel = LpTxNSdu->ddChannelId;
    #else
    /* Get the connection channel structure address */
    /*LddChannel = (CanTp_ChannelType)CANTP_CHANNEL_ID;*/
    LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
    #endif

    #if (STD_ON == CANTP_SINGLE_CHANNEL)
    #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
    LucChannelIndex = CanTp_GaaChannelMapping[LddChannel];
    #else /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
    LucChannelIndex = (uint8)LddChannel;
    #endif
    #else
    #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
    /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if (CANTP_MODE_FULL_DUPLEX == CanTp_GaaChannelMode[LddChannel])
    {
      LucChannelIndex = CanTp_GaaChannelMapping[LddChannel];
    }
    else
    #endif /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
    {
      LucChannelIndex = (uint8)LddChannel;
    }
    /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    #endif /* End of if (STD_ON == CANTP_SINGLE_CHANNEL) */

    LpChannelRam = &CanTp_GaaChannelRam[LucChannelIndex];

    if ((uint8)CANTP_RX_FC == LpChannelRam->ucChannelState)
    {
      #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
      (STD_ON == CANTP_TX_MIXED_ADDRESS))

      /* Get the N_PCI position if transmit NSDU is configured as Extended */
      LucBytePos = CanTp_GaaBytePos[LpTxNSdu->ucAddressingMode];
      #else

      /* Get the N_PCI position */
      LucBytePos = (uint8)CANTP_ZERO;
      #endif

      /* Get the flow status value into local variable */
      LucFlowStatus = (CanTpRxPduPtr[LucBytePos]) & ((uint8)CANTP_FS_MASK);

      /* Get the current frame type through PDU pointer */
      LucFrame = (uint8)((CanTpRxPduPtr[LucBytePos]) & ((uint8)CANTP_PCI_MASK));

      if ((uint8)CANTP_FC_PCI == LucFrame)
      {
        /* Decode the flow status */
        switch (LucFlowStatus)
        {
          case (uint8)CANTP_FS_CTS:
            LucBytePos++;

            /* Copy the BS value into global variables */
            LpChannelRam->usBSVar = CanTpRxPduPtr[LucBytePos];

            if(0U == LpChannelRam->usBSVar)
            {
              LpChannelRam->usBSVar = CANTP_INFINITE_BS;
            }
            LucBytePos++;

            /* Copy the STmin value into local variable */
            LucStMin = CanTpRxPduPtr[LucBytePos];

            if (LucStMin <= (uint8)CANTP_STMIN_DIRECT_VALUE_RANGE)
            {
              if (LucStMin != (uint8)CANTP_ZERO)
              {
                /* Update the current transmission STmin value =
                 * 2+(Received STmin - 1)/MainFunctionPeriod */

                LpChannelRam->ucStMinValue =
                  /*((LucStMin - ((uint8)CANTP_ONE)) / CANTP_MAIN_FUNCTION_PERIOD) +*/
                  ((LucStMin - ((uint8)CANTP_ONE)) / Cantp_Main_Function_Period ) +
                  (uint8)CANTP_TWO;
              } /* End of if (LucStMin != CANTP_ZERO) */
              else
              {
                /* Update the Minimum Separation Time value equal to '0' */
                LpChannelRam->ucStMinValue = (uint8)CANTP_ZERO;
              }
            } /*
               * if(LucStMin <= CANTP_STMIN_DIRECT_VALUE_RANGE)
               * Check if the received STmin is in 100us - 900us range
               */
            else if ((LucStMin >= (uint8)CANTP_STMIN_US_LOW) &&
                     (LucStMin <= (uint8)CANTP_STMIN_US_HIGH))
            {
              /* Update the STmin value based on the received STmin */
              LpChannelRam->ucStMinValue =
                CanTp_GaaSTminMapping
                [LucStMin & (uint8)CANTP_STMIN_MAP_MASK];
            } /* End of if ((LucStMin >= CANTP_STMIN_US_LOW) && */
            else                    /* Received STmin value is a reserved value */
            {
              /* Update the STmin value equal to Max STmin delay(i.e 127ms) */

              /* Update the current transmission STmin value =
               *                     2+(Maximum STmin - 1)/MainFunctionPeriod */
              LpChannelRam->ucStMinValue =
                (uint8)(((uint8)CANTP_MAX_STMIN_DELAY - (uint8)CANTP_ONE) /
          /*           CANTP_MAIN_FUNCTION_PERIOD) + (uint8)CANTP_TWO;*/
             Cantp_Main_Function_Period) + (uint8)CANTP_TWO;
            } /*
               * End of else
               * Update channel state to normal
               */
            LpChannelRam->ucChannelState = (uint8)CANTP_TX_NORMAL;

            /* Stop N_Bs timer */
            CANTP_TIMER_UPDATE_MACRO(LucChannelIndex, CANTP_NBS_TIMER,
            ((uint16)CANTP_ZERO));

            /* Set the channel buffer state to request the buffer */
            LpChannelRam->ucBufferState = (uint8)CANTP_TX_NOTRDY_INITREQ;
            break;

          case (uint8)CANTP_FS_WT:

            /* (Re)Start the N_Bs timer */          
            #if(STD_ON == CANTP_DEV_ERROR_DETECT)
            if(LpChannelRam->ddActivePduId > CANTP_MAX_TX_SDUID)
            {
              /* Report to DET */
              (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
                CANTP_RXINDICATION_SID, CANTP_E_INVALID_TX_ID);
            }
            else
            #endif
            {
              /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect Justify with annotations] "Genderated array index in range" */
              CANTP_TIMER_UPDATE_MACRO(LucChannelIndex, CANTP_NBS_TIMER,
              CanTp_GaaTxSduDynamic[LpChannelRam->ddActivePduId].
              usNbsTimeoutValue);
            }
            break;

          case (uint8)CANTP_FS_OVFLW:

            /* Invoke upper layer Tx confirmation to mention there is no
             *   receive buffer to receive further bytes */
            CanTp_TransmissionComplete(LpChannelRam,
            (NotifResultType)NTFRSLT_E_NO_BUFFER);
            break;

          default:                  /* Invalid flow status */

            /* Invoke upper layer Tx confirmation to mention an Invalid
             *   Flow status is received */
            /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect Justify with annotations] "Genderated array index in range" */ 
            CanTp_TransmissionComplete(LpChannelRam,
            (NotifResultType)NTFRSLT_E_INVALID_FS);
            break;
        } /* End of switch statement */
      } /* if(LucFrame == CANTP_FC_PCI) */
    } /* if(LpChannelRam->ucChannelState == CANTP_RX_FC) */
  }
} /* End of CanTp_ProcessRxFc(P2CONST(uint8, AUTOMATIC, CANTP_CONST)
   * CanTpRxPduPtr) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING) */

/*******************************************************************************
** Function Name        : CanTp_TxDlcCheck                                    **
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
** Input Parameters     : LpTxNSdu                                            **
**                        LucTxDatalength                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblDlcErrorFlag                                     **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaBytePos           **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, CANTP_CODE) CanTp_TxDlcCheck(P2CONST(CanTp_TxNsduStatic,
    AUTOMATIC, CANTP_CONST) LpTxNSdu, PduLengthType LucTxDatalength)
{
  #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)
  PduLengthType LddSduLength;
  uint8 LucBytePos;
  #endif
  boolean LblDlcErrorFlag;

  /* Assign the default value to be used */
  LblDlcErrorFlag = CANTP_FALSE;

  /* Check Tx datalength is less than minimum length configured for
   *   transmission */
  if ((uint16)LucTxDatalength < (uint16)(LpTxNSdu->usTxSduLength))
  {
    LblDlcErrorFlag = CANTP_TRUE;
  }

  /* Check Tx datalength fits in single frame for Functional addressing */
  #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)

  if (CANTP_FALSE == LblDlcErrorFlag)
  {
    #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_TX_MIXED_ADDRESS))

    /* Get the N_PCI position if transmit NSDU is configured as Extended */
    LucBytePos = CanTp_GaaBytePos[LpTxNSdu->ucAddressingMode];
    #else

    /* Assign the default value to be used */
    LucBytePos = (uint8)CANTP_ZERO;
    #endif

    /* Set the expected SduLength */
    LddSduLength = ((PduLengthType)CANTP_SEVEN - LucBytePos);

    /* Check if the TxNsdu supports Functional addressing */
    if (((uint8)CANTP_FUNCTIONAL_ADDRESS == LpTxNSdu->ucTaType) &&
        ((PduLengthType)LucTxDatalength > LddSduLength))
    {
      LblDlcErrorFlag = CANTP_TRUE;
    }
  } /* if(LblDlcErrorFlag == CANTP_FALSE) */
  #endif /* End of if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING) */
  return (LblDlcErrorFlag);
} /* End of CanTp_TxDlcCheck(P2CONST(CanTp_TxNsduStatic, AUTOMATIC, CANTP_CONST)
   * LpTxNSdu, PduLengthType LucTxDatalength) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (STD_ON == CANTP_TX_NSDU ) */
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

