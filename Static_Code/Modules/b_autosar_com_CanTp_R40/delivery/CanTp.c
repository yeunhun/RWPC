/*******************************************************************************
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp.c                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : APIs implementation for CanTp module                          **
**              CanTp_Init                                                    **
**              CanTp_Shutdown                                                **
**              CanTp_Transmit                                                **
**              CanTp_MainFunction                                            **
**              CanTp_GetVersionInfo                                          **
**              CanTp_CancelTransmit                                          **
**              CanTp_CancelReceive                                           **
**              CanTp_ChangeParameter                                         **
**              CanTp_ReadParameter                                           **
**              CanTp_TimeoutProcessing                                       **
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
** 1.11.1    12-Jan-2021   SM Kwon        Redmine #27640                      **
** 1.10.2    31-Jul-2020   SM Kwon        Redmine #24646, #25248              **
** 1.10.1    16-Oct-2019   SM Kwon        Redmine #19617                      **
** 1.10.0    28-Aug-2019   SM Kwon        Redmine #18863                      **
** 1.9.0     11-Jul-2019   SM Kwon        Redmine #17748                      **
** 1.8.1     13-Mar-2019   SM Kwon        Redmine #15962, #16463, #16559      **
** 1.8.0     21-Mar-2018   Lim Jong Sun   Redmine #11554                      **
** 1.7.11    19-Dec-2017   Lim Jong Sun   Redmine #10756                      **
** 1.7.10    24-Apr-2015   Lim Jong Sun   Redmine #8152                       **
** 1.7.8     31-May-2016   Lim Jong Sun   Redmine #4409                       **
** 1.7.7     02-May-2016   Lim Jong Sun   Redmine #4803                       **
** 1.7.5     02-Feb-2015   Lim Jong Sun   Redmine #3965                       **
** 1.7.4     26-Nov-2015   Lim Jong Sun   Redmine #2786                       **
** 1.7.3     25-Aug-2015   Lim Jong Sun   Redmine #2788                       **
** 1.0.4     26-Jan-2015   Lim Jong Sun   Redmine #2045                       **
** 1.0.3     03-Jan-2014   Lim Jong Sun   Redmine #413                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "SchM_CanTp.h"           /* SchM Header File */
#include "CanTp_PCTypes.h"        /* CanTp PCTypes Header File */
#include "CanTp_Cbk.h"            /* CanTp Callback APIs Header File */
#include "CanTp_TxInternal.h"     /* CanTp TxInternal Header File */
#include "CanTp_RxInternal.h"     /* CanTp RxInternal Header File */
#include "CanTp_Ram.h"            /* CanTp Ram Header File */
#include "PduR_CanTp.h"           /* PduR header for CAN TP */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANTP_C_AR_RELEASE_MAJOR_VERSION    4
#define CANTP_C_AR_RELEASE_MINOR_VERSION    0
#define CANTP_C_AR_RELEASE_REVISION_VERSION 3

/* CANTP software version information */
#define CANTP_C_SW_MAJOR_VERSION            1
#define CANTP_C_SW_MINOR_VERSION            11

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANTP_AR_RELEASE_MAJOR_VERSION != CANTP_C_AR_RELEASE_MAJOR_VERSION)
#error "CanTp.c : Mismatch in Specification Major Version"
#endif
#if (CANTP_AR_RELEASE_MINOR_VERSION != CANTP_C_AR_RELEASE_MINOR_VERSION)
#error "CanTp.c : Mismatch in Specification Minor Version"
#endif
#if (CANTP_AR_RELEASE_REVISION_VERSION !=\
     CANTP_C_AR_RELEASE_REVISION_VERSION)
#error "CanTp.c : Mismatch in Specification Revision Version"
#endif
#if (CANTP_SW_MAJOR_VERSION != CANTP_C_SW_MAJOR_VERSION)
#error "CanTp.c : Mismatch in Software Major Version"
#endif
#if (CANTP_SW_MINOR_VERSION != CANTP_C_SW_MINOR_VERSION)
#error "CanTp.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* Byte position in the frames */
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(uint8, CANTP_CONST) CanTp_GaaBytePos[] =
{
  CANTP_ZERO,
  CANTP_ONE,
  CANTP_ONE
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
#if (STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_DEV_ERROR_DETECT)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxDetCheck(PduIdType
  CanTpTxSduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_CONST) LpCanTpTxInfoPtr);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (CANTP_TX_NSDU == STD_ON)&& (STD_ON == CANTP_DEV_ERROR_DETECT) */

#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANTP_CODE) CanTp_TimeoutProcessing(P2VAR(CanTp_ChannelRam,
    AUTOMATIC, CANTP_VAR) LpChannelRam, P2VAR(uint16, AUTOMATIC,
    CANTP_VAR) LpTimers);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanTp_Init                                          **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service initializes all global variables of    **
**                        the CAN Transport Layer and set the CanTp module to **
**                        idle state.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : CfgPtr                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GblInitStatus,       **
**                                                 CanTp_GaaChannelRam        **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_Init(P2CONST(CanTp_ConfigType, AUTOMATIC,
    CANTP_APPL_CONST) CfgPtr)
{
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  uint8 LucRxTxInstances;

  /* Initialize  Instance counter to zero  */
  LucRxTxInstances = (uint8)CANTP_ZERO;

  do
  {
    /* Get the address of first channel Ram */
    LpChannelRam = &CanTp_GaaChannelRam[LucRxTxInstances];
  
    /* Change the channel state to IDLE */
    LpChannelRam->ucChannelState = (uint8)CANTP_WAIT;

    /* Change the Tx confirm state to IDLE */
    LpChannelRam->ucTxConfirmState = (uint8)CANTP_TX_CONF_IDLE;
    #if (CANTP_RX_NSDU == STD_ON)
    /* Change the usAvlBuffLength value to ZERO */
    /* 10756 */
    LpChannelRam->usAvlBuffLength = (uint16)CANTP_ZERO;
    #endif
    /* Increment Instance counter */
    LucRxTxInstances++;
  } while (LucRxTxInstances < ((uint8)Cantp_Total_Rx_Tx_Channels));

  /* Set the Initialization status to CANTP_ON */
  CanTp_GblInitStatus = CANTP_TRUE;
  CANTP_UNUSED_PTR(CfgPtr);
} /* End of CanTp_Init(P2CONST(CanTp_ConfigType, AUTOMATIC, */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanTp_Shutdown                                      **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service closes all pending transport protocol  **
**                        connections, frees all resources and sets the       **
**                        corresponding CanTp module into the CANTP_TRUE state**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTP_GblInitStatus,       **
**                                                 CanTp_GaaChannelRam        **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_Shutdown(void)
{
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  uint8 LucRxTxInstances;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)

  /* CanTp not Initilized */
  if (CANTP_FALSE == CanTp_GblInitStatus)
  {
    /* Report Det Error */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_SHUTDOWN_SID, CANTP_E_UNINIT);
  }
  else
  #endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */
  {
    LucRxTxInstances = (uint8)CANTP_ZERO;
    /* Get the address of first channel Ram */
    LpChannelRam = &CanTp_GaaChannelRam[LucRxTxInstances];

    /* Reset all channels to the default value */
    do
    {
      /* Change the channel state to WAIT/IDLE */
      LpChannelRam->ucChannelState = (uint8)CANTP_WAIT;

      /* Change the Tx confirm state to IDLE */
      LpChannelRam->ucTxConfirmState = (uint8)CANTP_TX_CONF_IDLE;
    
      /* Increment Instance counter */
      LucRxTxInstances++;
    } while (LucRxTxInstances < ((uint8)Cantp_Total_Rx_Tx_Channels));

    /* Set the Global Initialization status */
    CanTp_GblInitStatus = CANTP_FALSE;
  } /* If no development error has occurred */
} /* End of CanTp_Shutdown(void) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanTp_Transmit                                      **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service is used to request the transfer of     **
**                        segmented data.                                     **
**                                                                            **
** Sync/Async           : Asnchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CanTpTxSduId                                        **
**                        CanTpTxInfoPtr                                      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                                                **
**                        E_NOT_OK                                            **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaBytePos,          **
**                                                 CanTp_GaaTxSduStatic,      **
**                                                 CanTp_GaaChannelRam        **
**                                                 Cantp_Channel_Id           **
**                        Function(s) invoked    : Det_ReportError            **
**                                                 CanTp_TxDetCheck           **
**                                                 CanTp_TxDlcCheck           **
**                                         CanTp_TransmissionComplete         **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANTP_CODE) CanTp_Transmit(PduIdType CanTpTxSduId, P2CONST(
    PduInfoType, AUTOMATIC, CANTP_APPL_CONST) CanTpTxInfoPtr)
{
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  #if (STD_OFF == CANTP_SINGLE_CHANNEL)
  P2CONST(CanTp_TxNsduStatic, AUTOMATIC, CANTP_CONST) LpStaticTxNSdu;
  #endif
  Std_ReturnType LddReturnValue;
  CanTp_ChannelType LddChannel;
  CanTp_WordAccess LddDataLen;
  uint8 LucBytePosition;
  boolean LblDlcErrorFlag;
  #if (CANTP_FD_SUPPORT == STD_ON)
  uint8 LucTxDataMaxLength;
  #endif


  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  LddReturnValue = CanTp_TxDetCheck(CanTpTxSduId, CanTpTxInfoPtr);

  if (((Std_ReturnType)E_OK) == LddReturnValue)
  #endif /* #if(CANTP_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the pointer to current TxNsdu */
    LpStaticTxNSdu = &CanTp_GaaTxSduStatic[CanTpTxSduId];
    
    /* Set return value (uint8) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
    #if (CANTP_FD_SUPPORT == STD_ON)
    LucTxDataMaxLength = LpStaticTxNSdu->ucTxSduMaxLength;
    #endif
    /* polyspace +4 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
    #if (STD_OFF == CANTP_SINGLE_CHANNEL)
    /* Get the connection channel Id */
    LddChannel = LpStaticTxNSdu->ddChannelId;
    #else
    /* Get the connection channel Id */
    /*LddChannel = (CanTp_ChannelType)CANTP_CHANNEL_ID;*/
    LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
    #endif
    #if (STD_ON == CANTP_SINGLE_CHANNEL)
    #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
    LpChannelRam = &CanTp_GaaChannelRam[CanTp_GaaChannelMapping[LddChannel]];
    #else /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
    LpChannelRam = &CanTp_GaaChannelRam[LddChannel];
    #endif
    #else
    #if (STD_ON == CANTP_FULL_DUPLEX_MODE)

    if (CANTP_MODE_FULL_DUPLEX == CanTp_GaaChannelMode[LddChannel])
    {
      LpChannelRam = &CanTp_GaaChannelRam[CanTp_GaaChannelMapping[LddChannel]];
    }
    else
    #endif /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
    {
      LpChannelRam = &CanTp_GaaChannelRam[LddChannel];
    }
    #endif /* End of if (STD_ON == CANTP_SINGLE_CHANNEL) */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
    if ((uint8)CANTP_WAIT == LpChannelRam->ucChannelState)
    {
      /* Set the channel state to CANTP_TX_NORMAL */
      LpChannelRam->ucChannelState = (uint8)CANTP_TX_NORMAL;

      /* Set the active PduId */
      LpChannelRam->ddActivePduId = CanTpTxSduId;

      /* Copy the requested NSDU length into union variable */
      /* polyspace<MISRA-C3:D4.14 :: Not a defect Justified> Pointer is not a NULL and valid */
      LddDataLen.usWholeWord = (uint16)CanTpTxInfoPtr->SduLength;

      /* Validate DLC. Error flag is set to TRUE in following condition.
       *   1. If Nsdu is configured for physical addressing and DLC is less
       *      than configured sdu length.
       *   2. If Nsdu is configured for functional addressing and DLC is
       *      greater than 6 byte.
       */
      LblDlcErrorFlag = CanTp_TxDlcCheck(LpStaticTxNSdu,
        (PduLengthType)LddDataLen.usWholeWord);

      if (CANTP_TRUE == LblDlcErrorFlag)
      {
        /* Terminate the new transmission */
        CanTp_TransmissionComplete
          (LpChannelRam, (NotifResultType)NTFRSLT_E_NOT_OK);
      }
      else /* No DLC error */
      {
        /* Copy the NSDU length to global variable */
        LpChannelRam->usByteCounter = LddDataLen.usWholeWord;
        #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
        (STD_ON == CANTP_TX_MIXED_ADDRESS))

        /* Get the N_PCI position if transmit NSDU is configured as Extended */
        LucBytePosition = CanTp_GaaBytePos[LpStaticTxNSdu->ucAddressingMode];
        /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justify with annotations] "condition will be executed based on the configured values" */
        if (LucBytePosition != (uint8)CANTP_STANDARD_ADDRESS)
        {
          /* Set the first byte of the data frame with N_TA */
          LpChannelRam->aaDataBuffer[CANTP_ZERO] =
            LpStaticTxNSdu->ucNTaOrNAeValue;
        }
        #else /* End of if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) || (STD_ON ==
               * CANTP_TX_MIXED_ADDRESS)) */

        /* Initialise the Addressing format value as Standard */
        LucBytePosition = (uint8)CANTP_ZERO;
        #endif /* End of if ((CANTP_TX_EXTENDED_ADDRESS == STD_ON) ||
                *(CANTP_TX_MIXED_ADDRESS == STD_ON)) */

        /* Based on LucBytePos, update the current addressing global variable
         * LucBytePos = 0 -> CANTP_STANDARD_ADDRESS
         * LucBytePos = 1 -> CANTP_EXTENDED_ADDRESS */
         
        LpChannelRam->ucCurrentBytePosition = LucBytePosition;	
        
        #if (CANTP_FD_SUPPORT == STD_ON)
        /* In case of CAN-FD Frame */
        /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
        if ((CANTP_CANFD_FUNCTIONAL_ADDRESS == LpStaticTxNSdu->ucTaType)||\
            (CANTP_CANFD_PHYSICAL_ADDRESS == LpStaticTxNSdu->ucTaType))	
        {
          /* In case of Single Frame and CAN_DL <= 8*/
          if (LddDataLen.usWholeWord <= (((uint16)CANTP_SEVEN) - (uint16)LucBytePosition))
          {
            /* Set the PCI byte for single frame (SF) */
            LpChannelRam->aaDataBuffer[LucBytePosition] = LddDataLen.byte_val.ucLSByte;
            
            /* Set the frame type as SF */
            LpChannelRam->ucFrameType = (uint8)CANTP_SF_PCI;
          }
          /* In case of Single Frame and CAN_DL > 8 */					
          else if (LddDataLen.usWholeWord <=
              (((uint16)LucTxDataMaxLength - CANTP_TWO)- (uint16)LucBytePosition))
          {
            /* Set the PCI byte#1 for single frame (SF) */
            LpChannelRam->aaDataBuffer[LucBytePosition] = (uint8)CANTP_FD_SF_FIRST;
    	    LucBytePosition++;
  	        /* Set the PCI byte#2 for single frame (SF) */
            LpChannelRam->aaDataBuffer[LucBytePosition] = LddDataLen.byte_val.ucLSByte;

      	    /* Set the frame type as SF */
    	      LpChannelRam->ucFrameType = (uint8)CANTP_SF_PCI;
			  
          }
          /* In case of First Frame and FF_DL > 4095*/
          else if ( LddDataLen.usWholeWord >
  	      	   (((uint16)4095 - (uint16)CANTP_SIX) - (uint16)LucBytePosition))	      	
  	      {
            /* Set the PCI byte#1 for first frame (FF) */
            LpChannelRam->aaDataBuffer[LucBytePosition] = (uint8)CANTP_FD_FF_FIRST;
    	    LucBytePosition++;
            /* Set the PCI byte#2 for first frame (FF) */
            LpChannelRam->aaDataBuffer[LucBytePosition] = (uint8)CANTP_FD_FF_SECOND;
    	    LucBytePosition++;            			
            /* Set the PCI byte#4 for first frame (FF) */
            LpChannelRam->aaDataBuffer[LucBytePosition] = (uint8)CANTP_ZERO;
    	    LucBytePosition++;            			  
            /* Set the PCI byte#5 for first frame (FF) */
            LpChannelRam->aaDataBuffer[LucBytePosition] = (uint8)CANTP_ZERO;
    	    LucBytePosition++;            			  
            /* Set the PCI byte#3 for first frame (FF) */
            LpChannelRam->aaDataBuffer[LucBytePosition] =
              (LddDataLen.byte_val.ucMSByte);
    	    LucBytePosition++;              
            /* Set the PCI byte#6 for first frame (FF) */
            LpChannelRam->aaDataBuffer[LucBytePosition] = LddDataLen.byte_val.ucLSByte;

            #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
            /* Initialize frame counter */
            LpChannelRam->ucFrameCounter = (uint8)CANTP_ZERO;
            #endif

            /* Set the frame type as FF */
            LpChannelRam->ucFrameType = (uint8)CANTP_FF_PCI;
	      	
          }
          /* In case of First Frame and FF_DL <= 4095*/
          else
          {
            /* Set the PCI byte for first frame (FF) */	  
            LpChannelRam->aaDataBuffer[LucBytePosition] =
            (((uint8)CANTP_FF_PCI) | (LddDataLen.byte_val.ucMSByte));
    	    LucBytePosition++;
            /* Set the byte2 in the first frame */
            LpChannelRam->aaDataBuffer[LucBytePosition] = LddDataLen.byte_val.ucLSByte;

            #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
            /* Initialize frame counter */
            LpChannelRam->ucFrameCounter = (uint8)CANTP_ZERO;
            #endif

            /* Set the frame type as FF */
            LpChannelRam->ucFrameType = (uint8)CANTP_FF_PCI;
			  
  	      }
        } /*End of else if ((CANTP_CANFD_FUNCTIONAL_ADDRESS == LpStaticTxNSdu->ucTaType)||\
                            (CANTP_CANFD_PHYSICAL_ADDRESS == LpStaticTxNSdu->ucTaType))	*/
        /* In case of Classic Can Frame */
        else
        {
          /* In case of Single Frame and CAN_DL <= 8 */
          if (LddDataLen.usWholeWord <= (((uint16)CANTP_SEVEN) - (uint16)LucBytePosition))
          {
            /* Set the PCI byte for single frame (SF) */
            LpChannelRam->aaDataBuffer[LucBytePosition] = LddDataLen.byte_val.ucLSByte;

            /* Set the frame type as SF */
            LpChannelRam->ucFrameType = (uint8)CANTP_SF_PCI;
          }
          /* Requested SDU contains multiple frames */
          else
          {
            /* Requested SDU contains multiple frames */
            /* Set the PCI byte for first frame (FF) */
            LpChannelRam->aaDataBuffer[LucBytePosition] =
              (((uint8)CANTP_FF_PCI) | LddDataLen.byte_val.ucMSByte);
    	    LucBytePosition++;
            /* Set the byte2 in the first frame */
            LpChannelRam->aaDataBuffer[LucBytePosition] = LddDataLen.byte_val.ucLSByte;
              
            #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
            /* Initialize frame counter */
            LpChannelRam->ucFrameCounter = (uint8)CANTP_ZERO;
            #endif

            /* Set the frame type as FF */
            LpChannelRam->ucFrameType = (uint8)CANTP_FF_PCI;
          }
        }
        /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
        #else /*(CANTP_FD_SUPPORT == STD_OFF)*/
        /* In case of Single Frame and CAN_DL <= 8 */
        if (LddDataLen.usWholeWord <= (((uint16)CANTP_SEVEN) - (uint16)LucBytePosition))
        {
          /* Set the PCI byte for single frame (SF) */
          LpChannelRam->aaDataBuffer[LucBytePosition] = LddDataLen.byte_val.ucLSByte;

          /* Set the frame type as SF */
          LpChannelRam->ucFrameType = (uint8)CANTP_SF_PCI;
        } 
        /* Requested SDU contains multiple frames */
        else
        {
          /* Set the PCI byte for first frame (FF) */
          LpChannelRam->aaDataBuffer[LucBytePosition] =
            (((uint8)CANTP_FF_PCI) | LddDataLen.byte_val.ucMSByte);

          LucBytePosition++;
		  
          /* Set the byte2 in the first frame */
          LpChannelRam->aaDataBuffer[LucBytePosition] = LddDataLen.byte_val.ucLSByte;
          
          #if (STD_ON == CANTP_TX_PHYSICAL_ADDRESSING)
          /* Initialize frame counter */
          LpChannelRam->ucFrameCounter = (uint8)CANTP_ZERO;
          #endif

          /* Set the frame type as FF */
          LpChannelRam->ucFrameType = (uint8)CANTP_FF_PCI;
        }
        #endif/*(CANTP_FD_SUPPORT == STD_ON)*/
        
        LpChannelRam->ucLocalDataByteIndex = LucBytePosition + (uint8)CANTP_ONE;

        /* Set the channel buffer state to request the buffer */
        LpChannelRam->ucBufferState = (uint8)CANTP_TX_NOTRDY_INITREQ;

        /* Set the new frame flag status as start of Transmission of FF or SF */
        LpChannelRam->ucNewFrameFlag = (uint8)CANTP_TX_SFORFF;

        /* Set return value (uint8) E_OK */
        LddReturnValue = (Std_ReturnType)E_OK;
      } /* No DLC error */
    } /* Tx channel is in WAIT state */
  } /* No development errors occurred */
  return (LddReturnValue);
} /* End of CanTp_Transmit(PduIdType CanTpTxSduId, P2CONST(PduInfoType,
   * AUTOMATIC, CANTP_APPL_CONST) CanTpTxInfoPtr) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (CANTP_TX_NSDU == STD_ON) */

/*******************************************************************************
** Function Name        : CanTp_TxDetCheck                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service will check the for any error in the    **
**                        input parameters passed to CanTp_Transmit API       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CanTpTxSduId                                        **
**                        LpCanTpTxInfoPtr                                    **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                                                **
**                        E_NOT_OK                                            **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GaaTxSduStatic       **
**                                      Cantp_Max_Tx_Sduid      **
**                        Function(s) invoked    : Det_ReportError            **
**                                                                            **
*******************************************************************************/
#if (STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_DEV_ERROR_DETECT)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANTP_CODE) CanTp_TxDetCheck(PduIdType CanTpTxSduId,
  P2CONST( PduInfoType, AUTOMATIC, CANTP_CONST) LpCanTpTxInfoPtr)
{

  #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)
  P2CONST(CanTp_TxNsduStatic, AUTOMATIC, CANTP_CONST) LpTxNSduStatic;
  uint8 LucBytePos;
  #endif
  PduLengthType LddPduLength;
  Std_ReturnType LddReturnValue;
  #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)
  LddPduLength = (PduLengthType)CANTP_ZERO;
  #endif

  /* Initialize return status with (uint8) E_OK */
  LddReturnValue = (Std_ReturnType)E_OK;

  /* Check if CanTp is not Initialized */
  if (CANTP_FALSE == CanTp_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TRANSMIT_SID, CANTP_E_UNINIT);

    /* Set return value (uint8) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CANTP_FALSE == CanTp_GblInitStatus) */

  /* Check if Tx SduId is greater than maximum value */
  /*if ((uint16)CanTpTxSduId > CANTP_MAX_TX_SDUID)*/
  if ((uint16)CanTpTxSduId > Cantp_Max_Tx_Sduid)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TRANSMIT_SID, CANTP_E_PARAM_ID);

    /* Set return value (uint8) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CanTpTxSduId > CANTP_MAX_TX_SDUID) */

  /* Check if the input parameter pointer is a NULL pointer */
  if (NULL_PTR == LpCanTpTxInfoPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_TRANSMIT_SID, CANTP_E_PARAM_POINTER);

    /* Set return value (uint8) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (NULL_PTR == LpCanTpTxInfoPtr) */
  else
  {
    if ((Std_ReturnType)E_OK == LddReturnValue)
    {
      /* Get the complete PDU length */
      /* polyspace<MISRA-C3:D4.14 :: Not a defect Justified> Pointer is not a NULL and valid */
      LddPduLength = LpCanTpTxInfoPtr->SduLength;

      /* Check if the data length is invalid */
      if ((PduLengthType)CANTP_ZERO == LddPduLength)
      {
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_TRANSMIT_SID, CANTP_E_INVALID_TX_LENGTH);

        /* Set return value (uint8) E_NOT_OK */
        LddReturnValue = (Std_ReturnType)E_NOT_OK;
      } /* End of if (CANTP_ZERO == LddPduLength) */
    } /* End of if ((uint8)E_OK == LddReturnValue) */
  } /* End of else */
  #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)

  /* Check if no DET error occurred */
  if ((Std_ReturnType)E_OK == LddReturnValue)
  {
    /* Get the pointer to current TxNsdu */
    LpTxNSduStatic = &CanTp_GaaTxSduStatic[CanTpTxSduId];

    /* Check if the TxNsdu is configured for functional addressing */
    if ((uint8)CANTP_FUNCTIONAL_ADDRESS == LpTxNSduStatic->ucTaType)
    {
      #if ((STD_ON == CANTP_TX_EXTENDED_ADDRESS) ||\
      (STD_ON == CANTP_TX_MIXED_ADDRESS))

      /* Get the N_PCI position if transmit NSDU is configured as Extended */
      LucBytePos = CanTp_GaaBytePos[LpTxNSduStatic->ucAddressingMode];
      #else

      /* Initialise the Addressing format value as Standard */
      LucBytePos = (uint8)CANTP_ZERO;
      #endif

      /* Check if the requested SduLength is not fit into a single frame */
      if (LddPduLength > (((PduLengthType)CANTP_SEVEN) - LucBytePos))
      {
        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_TRANSMIT_SID, CANTP_E_INVALID_TATYPE);

        /* Set return value (uint8) E_NOT_OK */
        LddReturnValue = (Std_ReturnType)E_NOT_OK;
      } /* End of if (LddPduLength > (CANTP_SEVEN - LucBytePos)) */
    } /* if(LpTpTxNsdu->ucTaType == CANTP_FUNCTIONAL_ADDRESS) */
  } /* if(LddReturnValue == (uint8) E_OK) */
  #endif /* #if(CANTP_TX_FUNCTIONAL_ADDRESSING == STD_ON) */

  return (LddReturnValue);
} /* End of CanTp_TxDetCheck(PduIdType CanTpTxSduId, P2CONST( PduInfoType,
   * AUTOMATIC, CANTP_CONST) LpCanTpTxInfoPtr) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (CANTP_TX_NSDU == STD_ON) && (CANTP_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** Function Name        : CanTp_CancelTransmit                                **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This service allows the upper layer to cancel a     **
**                        transmission in progress                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CanTpTxSduId                                        **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                                                **
**                        E_NOT_OK                                            **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GblInitStatus,       **
**                                                 CanTp_GaaTxSduStatic,      **
**                                                 CanTp_GaaChannelRam,       **
**                             Cantp_Channel_Id **
**                             Cantp_Max_Tx_Sduid           **
**                        Function(s) invoked    : Det_ReportError            **
**                                                 CanTp_TransmissionComplete **
*******************************************************************************/
#if ((STD_ON == CANTP_TX_NSDU) && (STD_ON == CANTP_TC))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelTransmit(PduIdType CanTpTxSduId)
{
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  #if ((STD_OFF == CANTP_SINGLE_CHANNEL) ||\
  ((STD_ON == CANTP_DEV_ERROR_DETECT) &&\
  (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)))
  P2CONST(CanTp_TxNsduStatic, AUTOMATIC, CANTP_CONST) LpTxNSdu;
  #endif
  CanTp_ChannelType LddChannel;
  Std_ReturnType LddReturnValue;

  /* Initialize return status with (uint8) E_OK */
  LddReturnValue = (Std_ReturnType)E_OK;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)

  /* Check if CanTp is not Initialized */
  if (CANTP_FALSE == CanTp_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CANCELTRANSMIT_SID, CANTP_E_UNINIT);

    /* Set return value (uint8) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CANTP_FALSE == CanTp_GblInitStatus) */

  /* Check the CanTpTxSduId is valid */
  /*if (CanTpTxSduId > (PduIdType)CANTP_MAX_TX_SDUID)*/
  if (CanTpTxSduId > (PduIdType)Cantp_Max_Tx_Sduid)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CANCELTRANSMIT_SID, CANTP_E_PARAM_ID);

    /* Set return value (uint8) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CanTpTxSduId > CANTP_MAX_TX_SDUID) */
  else
  {
    #if (STD_ON == CANTP_TX_FUNCTIONAL_ADDRESSING)
    /* Get the pointer to current TxNsdu */
    LpTxNSdu = &CanTp_GaaTxSduStatic[CanTpTxSduId];

    /* If the TxNsdu supports Functional addressing */
    if ((uint8)CANTP_FUNCTIONAL_ADDRESS == LpTxNSdu->ucTaType)
    {
      /* Report to DET */
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_CANCELTRANSMIT_SID, CANTP_E_PARAM_ID);

      /* Set return value (uint8) E_NOT_OK */
      LddReturnValue = (Std_ReturnType)E_NOT_OK;
    } /* End of if (CANTP_FUNCTIONAL_ADDRESS == LpTxNSdu->ucTaType) */
    #endif /* End of if (CANTP_TX_FUNCTIONAL_ADDRESSING == STD_ON) */
  } /* End of else */

  /* Check if any DET error is occurred */
  if ((Std_ReturnType)E_OK == LddReturnValue)
  #endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (STD_OFF == CANTP_SINGLE_CHANNEL)
    /* Get the pointer to current TxNsdu */
    LpTxNSdu = &CanTp_GaaTxSduStatic[CanTpTxSduId];

    /* Get the connection channel structure address */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
    LddChannel = LpTxNSdu->ddChannelId;
    #else

    /* Get the connection channel structure address */
    /*LddChannel = (CanTp_ChannelType)CANTP_CHANNEL_ID;*/
    LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
    #endif /* End of if (CANTP_SINGLE_CHANNEL == STD_OFF) */
    #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
    /* polyspace-begin MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if (CANTP_MODE_FULL_DUPLEX == CanTp_GaaChannelMode[LddChannel])
    {
      /* Load the address of the channel RAM */
      LpChannelRam = &CanTp_GaaChannelRam[CanTp_GaaChannelMapping[LddChannel]];
    }
    else
    #endif /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
    {
      LpChannelRam = &CanTp_GaaChannelRam[LddChannel];
    }
    /* polyspace-end MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */

    /* Check requested PduId is Active PduId */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
    if (LpChannelRam->ddActivePduId == CanTpTxSduId)
    {
      /* Check current state is not transmit state */
      if ((uint8)CANTP_WAIT == LpChannelRam->ucChannelState)
      {
        /* Set return value (uint8) E_NOT_OK */
        LddReturnValue = (Std_ReturnType)E_NOT_OK;
      }
      /* Check currently SF transmission is in progress */
      else if ((uint8)CANTP_SF_PCI == LpChannelRam->ucFrameType)
      {
        /* Set return value (uint8) E_NOT_OK */
        LddReturnValue = (Std_ReturnType)E_NOT_OK;
      }
      else
      {
        /* Abort the ongoing transmission */
        CanTp_TransmissionComplete(LpChannelRam,
          (NotifResultType)NTFRSLT_E_CANCELATION_OK);
      }
    } /* if(CanTpTxSduId == LpChannelRam->ddActivePduId) */
    else
    {
      #if (STD_ON == CANTP_DEV_ERROR_DETECT)

      /* Report to DET */
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_CANCELTRANSMIT_SID, CANTP_E_OPER_NOT_SUPPORTED);

      /* Set return value (uint8) E_NOT_OK */
      LddReturnValue = (Std_ReturnType)E_NOT_OK;
      #endif
    } /* End of else */
  } /* Check if any DET error is occurred */
  return (LddReturnValue);
} /* End of CanTp_CancelTransmit(PduIdType CanTpTxSduId) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((CANTP_TX_NSDU == STD_ON) && (CANTP_TC == STD_ON)) */

/*******************************************************************************
** Function Name        : CanTp_CancelReceive                                 **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This service allows the upper layer to cancel a     **
**                        reception in progress                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CanTpRxSduId                                        **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                                                **
**                        E_NOT_OK                                            **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GblInitStatus,       **
**                                                 CanTp_GaaRxSduStatic,      **
**                                                 CanTp_GaaChannelMode,      **
**                                                 CanTp_GaaChannelRam        **
**                             Cantp_Channel_Id         **
**                             Cantp_Max_Rx_Sduid       **
**                        Function(s) invoked    : Det_ReportError            **
**                                                 CanTp_ReceptionComplete    **
*******************************************************************************/
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelReceive(PduIdType CanTpRxSduId)
{
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
  (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_OFF == CANTP_SINGLE_CHANNEL))
  P2CONST(CanTp_RxNsduStatic, AUTOMATIC, CANTP_CONST) LpRxNSdu;
  #endif
  CanTp_ChannelType LddChannel;
  Std_ReturnType LddReturnValue;
  uint8 LucBytePos;

  /* Initialize return status with (uint8) E_OK */
  LddReturnValue = (Std_ReturnType)E_OK;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)

  /* Check if CanTp is not Initialized */
  if (CANTP_FALSE == CanTp_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CANCELRECEIVE_SID, CANTP_E_UNINIT);

    /* Set return value (uint8) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CANTP_FALSE == CanTp_GblInitStatus) */

  /* check the validity of CanTpRxSduId  */
  /*if (CanTpRxSduId > (PduIdType)CANTP_MAX_RX_SDUID)*/
  if (CanTpRxSduId > (PduIdType)Cantp_Max_Rx_Sduid)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CANCELRECEIVE_SID, CANTP_E_PARAM_ID);

    /* Set return value (uint8) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CanTpRxSduId > CANTP_MAX_RX_SDUID) */
  else
  {
    #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_OFF == CANTP_SINGLE_CHANNEL))
    #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)
    /* Get the pointer to current TxNSdu */
    LpRxNSdu = &CanTp_GaaRxSduStatic[CanTpRxSduId];
    #endif
    /* If the RxNsdu supports Functional addressing */
    #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)

    /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if ((uint8)CANTP_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType)
    {
      /* Report to DET */
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_CANCELRECEIVE_SID, CANTP_E_PARAM_ID);

      /* Set return value (uint8) E_NOT_OK */
      LddReturnValue = (Std_ReturnType)E_NOT_OK;
    } /* End of if (CANTP_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType) */
    #endif /* #if(STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)  */
    #endif /* #if((STD_ON == CANTP_RX_EXTENDED_ADDRESS ) || \
            *   (STD_ON == CANTP_RX_MIXED_ADDRESS) ||
            *   (STD_ON == CANTP_SINGLE_CHANNEL)) */
  } /* End of else */

  /* Check if any DET error is occurred */
  if ((Std_ReturnType)E_OK == LddReturnValue)
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
    (STD_ON == CANTP_RX_MIXED_ADDRESS) || (STD_OFF == CANTP_SINGLE_CHANNEL))

    /* Get the pointer to current RxNsdu */
    LpRxNSdu = &CanTp_GaaRxSduStatic[CanTpRxSduId];
    #endif
    #if (STD_OFF == CANTP_SINGLE_CHANNEL)

    /* Get the connection channel structure address */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
    LddChannel = LpRxNSdu->ddChannelId;
    #else

    /* Get the connection channel structure address */
    /*LddChannel = (CanTp_ChannelType)CANTP_CHANNEL_ID;*/
    LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
    #endif

    #if (STD_ON == CANTP_SINGLE_CHANNEL)
    #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
    LpChannelRam = &CanTp_GaaChannelRam[CanTp_GaaChannelMapping[LddChannel]];
    #else /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
    LpChannelRam = &CanTp_GaaChannelRam[LddChannel];
    #endif
    #else
    #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
		/* polyspace +4 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if (CANTP_MODE_FULL_DUPLEX == CanTp_GaaChannelMode[LddChannel])
    {
      LpChannelRam = &CanTp_GaaChannelRam[CanTp_GaaChannelMapping[LddChannel]];
    }
    else
    #endif /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
    {
      LpChannelRam = &CanTp_GaaChannelRam[LddChannel];
    }
    #endif /* End of if (STD_ON == CANTP_SINGLE_CHANNEL) */

    /* Check requested PduId is Active PduId */
    if (CanTpRxSduId == LpChannelRam->ddActivePduId)
    {
      if ((uint8)CANTP_WAIT == LpChannelRam->ucChannelState)
      {
        #if (STD_ON == CANTP_DEV_ERROR_DETECT)

        /* Report to DET */
        (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
          CANTP_CANCELRECEIVE_SID, CANTP_E_OPER_NOT_SUPPORTED);

        /* Set return value (uint8) E_NOT_OK */
        LddReturnValue = (Std_ReturnType)E_NOT_OK;
        #endif
      } /* End of if (CANTP_WAIT == LpChannelRam->ucChannelState) */
      else
      {
        #if ((STD_ON == CANTP_RX_EXTENDED_ADDRESS) ||\
        (STD_ON == CANTP_RX_MIXED_ADDRESS))

        /* Get the N_PCI position if transmit NSDU is configured as Extended */
        LucBytePos = CanTp_GaaBytePos[LpRxNSdu->ucAddressingMode];
        #else

        /* Initialise the Addressing format value as Standard */
        LucBytePos = (uint8)CANTP_ZERO;
        #endif

        /* Check currently SF reception is in progress */
        if ((uint8)CANTP_SF_PCI == LpChannelRam->ucFrameType)
        {
          /* Set return value (uint8) E_NOT_OK */
          LddReturnValue = (Std_ReturnType)E_NOT_OK;
        }
        /* Check whether last consecutive frame of the N-SDU reception in
         * progress */
        else if (LpChannelRam->usByteCounter <=
                 ((uint16)CANTP_SEVEN - (uint16)LucBytePos))
        {
          /* Set return value (uint8) E_NOT_OK */
          LddReturnValue = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
          /* Process the reception complete function */
          CanTp_ReceptionComplete(LpChannelRam,
            (NotifResultType)NTFRSLT_E_CANCELATION_OK);
        }
      } /* End of else */
    } /* Check requested PduId is Active PduId */
    else
    {
      #if (STD_ON == CANTP_DEV_ERROR_DETECT)
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_CANCELRECEIVE_SID, CANTP_E_OPER_NOT_SUPPORTED);

      /* Set return value (uint8) E_NOT_OK */
      LddReturnValue = (Std_ReturnType)E_NOT_OK;
      #endif
    } /* End of else */
  } /* Check if any DET error is occurred */
  return (LddReturnValue);
} /* End of CanTp_CancelReceive(PduIdType CanTpRxSduId) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (CANTP_RX_NSDU == STD_ON) */

/*******************************************************************************
** Function Name        : CanTp_MainFunction                                  **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : The main function for scheduling the CanTp          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : CanTp module should be initialized                  **
**                                                                            **
** Remarks              : Global Variable(s)     : CanTp_GblInitStatus        **
**                                                 CanTp_GaaChannelRam,       **
**                                                 CanTp_GaaStMinTimers,      **
**                                                 CanTp_GaaTimers,           **
**                                                 CanTp_GaaTxSduStatic       **
**                        Function(s) invoked    : Det_ReportError            **
**                                                 CanTp_RequestCopyTxData    **
**                                                 CanTp_RequestRxBuffer      **
*******************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_MainFunction(void)
{
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;

  #if (STD_ON == CANTP_TX_NSDU)
  P2CONST(CanTp_TxNsduStatic, AUTOMATIC, CANTP_CONST) LpTxNSdu;
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) LpStMinTimer;
  uint16 LusTimerValue;
  #endif
  P2VAR(uint16, AUTOMATIC, CANTP_VAR) LpTimer;
  uint8 LucRxTxInstances;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)
  /* Check if CanTp is not Initialized */
  if (CANTP_FALSE == CanTp_GblInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_MAINFUNCTION_SID, CANTP_E_UNINIT);
  }
  else
  #endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the address of first channel Ram */
    LpChannelRam = &CanTp_GaaChannelRam[CANTP_ZERO];
    #if (STD_ON == CANTP_TX_NSDU)

    /* Get the Stmin timer start address */
    
    LpStMinTimer = &CanTp_GaaStMinTimers[CANTP_ZERO];
    #endif

    /* Initialize channel count equal to zero */
    LucRxTxInstances = (uint8)CANTP_ZERO;
    /* Loop for all channels */
    while (LucRxTxInstances < (uint8)Cantp_Total_Rx_Tx_Channels)
    {
      /* Initialize the timer */
      LpTimer = &CanTp_GaaTimers[LucRxTxInstances][CANTP_ZERO];

      /* Check if the channel is not in IDLE state */
      if (LpChannelRam->ucChannelState != (uint8)CANTP_WAIT)
      {
        #if (STD_ON == CANTP_TX_NSDU)

        if ((uint8)CANTP_TX_NOTRDY_INITREQ == LpChannelRam->ucBufferState)
        {
          /* Request upper layer Copy Tx Data */
          CanTp_RequestCopyTxData(LpChannelRam);
        }
        #endif /* End of if (STD_ON == CANTP_TX_NSDU) */
        #if (STD_ON == CANTP_RX_NSDU)

        /*
         * Check if receive buffer needs to be requested
         * Check if the FC confirmation is not awaited
         */
        if ((LpChannelRam->ucBufferState == (uint8)CANTP_RX_NOTRDY_INITREQ) &&
            (LpChannelRam->ucTxConfirmState != (uint8)CANTP_FC_TX_CONF))
        {
          /* Request buffer from upper layer and Copy Rx Data */
          CanTp_RequestRxBuffer(LpChannelRam);
        }
        #endif /* End of if (CANTP_RX_NSDU == STD_ON) */

        CanTp_TimeoutProcessing(LpChannelRam, LpTimer);

        /* Check if TxNsdu is configured */
        #if (STD_ON == CANTP_TX_NSDU)

        /* Check if the communication is for transmission */
        if (LpChannelRam->ucChannelState <= (uint8)CANTP_MAX_TX_STATE)
        {
            LusTimerValue = (uint16)(*LpStMinTimer);
          /* Check if the STmin timer is running */
          if (LusTimerValue != (uint16)CANTP_ZERO)
          {
            /* Decrement the STmin timer */
            LusTimerValue--;

            /* Update the timer variable */
            SchM_Enter_CanTp_TIMER_PROTECTION();
            *LpStMinTimer = (uint8)LusTimerValue;
            SchM_Exit_CanTp_TIMER_PROTECTION();
          } /* End of if (LusTimerValue != CANTP_ZERO) */

          /* Check if the STmin timer is expired and buffer is available */
          if ((LusTimerValue == (uint16)CANTP_ZERO) &&
              (LpChannelRam->ucBufferState == (uint8)CANTP_TX_RDY))
          {
            #if (STD_ON == CANTP_DEV_ERROR_DETECT)
            if(LpChannelRam->ddActivePduId > CANTP_MAX_TX_SDUID)
            {
              /* Report to DET */
              (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
                CANTP_MAINFUNCTION_SID, CANTP_E_INVALID_TX_ID);
            }
            else
            #endif
            {/* Get the TxNSdu structure address */
              LpTxNSdu = &CanTp_GaaTxSduStatic[LpChannelRam->ddActivePduId];

              /* Transmit the data to lower layer */
              CanTp_CanIfTransmit(LpTxNSdu);
            }
          } /* End of if ((CANTP_ZERO == LusTimerValue) && */
        } /*  #if (STD_ON == CANTP_TX_NSDU) */
        #endif /* End of if (STD_ON == CANTP_TX_NSDU) */
      } /* Channel is not in IDLE state */

      /* Go to the next RX or TX NSDU */
      LpChannelRam++;
      /* by JSLim 2013.01.03 -- [Bug#413]Fixed : Multiple Channel bug */
      #if ((STD_ON == CANTP_TX_NSDU) && (STD_OFF == CANTP_SINGLE_CHANNEL))
	  /* polyspace-begin MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "Condition will be executed based on the configured values" */
      if (LucRxTxInstances < (uint8)CanTp_No_Of_Channels)
      {
        LpStMinTimer++;
      }
      /* polyspace-end MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "Condition will be executed based on the configured values" */
      #endif
      /* Go to the next RX or TX NSDU */
      LucRxTxInstances++;
    }
  } /* No Development errors occurred */
} /* End of CanTp_MainFunction(void) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanTp_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        CanTp module. The version information includes:     **
**                        - Module Id                                         **
**                        - Vendor Id                                         **
**                        - Vendor specific version numbers.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANTP_VERSION_INFO_API)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANTP_CODE) CanTp_GetVersionInfo(P2VAR(Std_VersionInfoType,
    AUTOMATIC, CANTP_APPL_DATA) versioninfo)
{
  #if (STD_ON == CANTP_DEV_ERROR_DETECT)

  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
    /* Report to DET  */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_GETVERSIONINFO_SID, CANTP_E_PARAM_POINTER);
  }
  else
  #endif /* (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    /* polyspace-begin MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
    /* Copy the vendor Id */
    versioninfo->vendorID = CANTP_VENDOR_ID;

    /* Copy the module Id */
    versioninfo->moduleID = CANTP_MODULE_ID;

    /* Copy Software Major Version */
    versioninfo->sw_major_version = (uint8)CANTP_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = (uint8)CANTP_SW_MINOR_VERSION;

    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = (uint8)CANTP_SW_PATCH_VERSION;
    /* polyspace-end MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
  }
} /* End of CanTp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
   * CANTP_APPL_DATA) versioninfo) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_VERSION_INFO_API) */

/*******************************************************************************
** Function Name       : CanTp_ChangeParameter                                **
**                                                                            **
** Service ID          : 0x0A                                                 **
**                                                                            **
** Description         : This service primitive is used to request the change **
**                       of the value of the TP_STMIN or TP_BS                **
**                       parameter. The value is given by value.              **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Non Reentrant                                        **
**                                                                            **
** Input Parameters    : id,                                                  **
**                       parameter,                                           **
**                       value                                                **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : (uint8) E_OK                                         **
**                       (uint8) E_NOT_OK                                     **
**                                                                            **
** Preconditions       : The CanTp module must be initialized before this call**
**                                                                            **
** Remarks             : Global Variable(s)     : CanTp_GblInitStatus,        **
**                                                CanTp_GaaRxSduStatic,       **
**                                                CanTp_GaaChannelMode,       **
**                                                CanTp_GaaChannelRam,        **
**                                                CanTp_GaaSTminBs            **
**                            Cantp_Channel_Id       **
**                            Cantp_Max_Rx_Sduid         **
**                       Function(s) invoked   :  Det_ReportError             **
*******************************************************************************/
#if ((STD_ON == CANTP_CHANGE_PARAMETER_API)\
  && (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANTP_CODE) CanTp_ChangeParameter(PduIdType id,
  TPParameterType parameter, VAR(uint16, AUTOMATIC) Value)
{
  #if (((STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)) ||\
  (STD_OFF == CANTP_SINGLE_CHANNEL))
  P2CONST(CanTp_RxNsduStatic, AUTOMATIC, CANTP_CONST) LpRxNSdu;
  #endif
  P2VAR(CanTp_ChannelRam, AUTOMATIC, CANTP_VAR) LpChannelRam;
  CanTp_ChannelType LddChannel;
  Std_ReturnType LddReturnValue;

  /* Initialize return status with (uint8) E_OK */
  LddReturnValue = (Std_ReturnType)E_OK;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)

  /* Check whether CanTp module initialization has not been done*/
  if (CANTP_FALSE == CanTp_GblInitStatus)
  {
    /* Report to DET  */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CHANGEPARAM_SID, CANTP_E_UNINIT);

    /* Set return LddReturnValue (uint8) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CANTP_FALSE == CanTp_GblInitStatus) */

  /* Check if the parameter is invalid */
  if ((parameter != TP_BS) && (parameter != TP_STMIN))
  {
    /* Report to DET  */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CHANGEPARAM_SID, CANTP_E_PARAM_ID);

    /* Set return LddReturnValue E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (parameter > TP_BS) */

  /* check the validity of CanTpRxSduId  */
  /*if (id > (PduIdType)CANTP_MAX_RX_SDUID)*/
  if (id > (PduIdType)Cantp_Max_Rx_Sduid)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_CHANGEPARAM_SID, CANTP_E_PARAM_ID);

    /* Set return LddReturnValue (uint8) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (id > CANTP_MAX_RX_SDUID) */
  else
  {
    /* If the RxNsdu supports Functional addressing */
    #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)

    /* If the RxNsdu supports Functional addressing */
    /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if ((uint8)CANTP_FUNCTIONAL_ADDRESS == CanTp_GaaRxSduStatic[id].ucTaType)
    {
      /* Report to DET */
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_CHANGEPARAM_SID, CANTP_E_PARAM_ID);

      /* Set return LddReturnValue (Std_ReturnType) E_NOT_OK */
      LddReturnValue = (Std_ReturnType)E_NOT_OK;
    } /* End of if (CANTP_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType) */
    #endif /* #if(STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)  */
  } /* End of else */

  /* Check if no Det error detected */
  if ((Std_ReturnType)E_OK == LddReturnValue)
  #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
  {
    #if (STD_OFF == CANTP_SINGLE_CHANNEL)

    /* Get the pointer to current RxNsdu */
    LpRxNSdu = &CanTp_GaaRxSduStatic[id];
    /* Get the channel ram data structure in to local pointer */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Array index in range" */
    LddChannel = LpRxNSdu->ddChannelId;
    #else

    /* Get the channel ram data structure in to local pointer */
    /*LddChannel = (CanTp_ChannelType)CANTP_CHANNEL_ID;*/
    LddChannel = (CanTp_ChannelType)Cantp_Channel_Id;
    #endif /* End of if (CANTP_SINGLE_CHANNEL == STD_OFF) */

    #if (STD_ON == CANTP_SINGLE_CHANNEL)
    #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
    LpChannelRam = &CanTp_GaaChannelRam[CanTp_GaaChannelMapping[LddChannel]];
    #else /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
    LpChannelRam = &CanTp_GaaChannelRam[LddChannel];
    #endif
    #else
    #if (STD_ON == CANTP_FULL_DUPLEX_MODE)
    /* polyspace +4 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if (CANTP_MODE_FULL_DUPLEX == CanTp_GaaChannelMode[LddChannel])
    {
      LpChannelRam = &CanTp_GaaChannelRam[CanTp_GaaChannelMapping[LddChannel]];
    }
    else
    #endif /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
    {
      LpChannelRam = &CanTp_GaaChannelRam[LddChannel];
    }
    #endif /* End of if (STD_ON == CANTP_SINGLE_CHANNEL) */

    /* Check if the communication is not for reception */
    if ((LpChannelRam->ucChannelState < (uint8)CANTP_MAX_TX_STATE) ||
        (LpChannelRam->ddActivePduId != id))
    {
      /* Check request is for 'TP_STMIN' parameter */
      if (TP_STMIN == parameter)
      {
        #if (STD_ON == CANTP_DEV_ERROR_DETECT)

        /* Check new Value of the parameter 'CANTP_STMIN' is within a range */
        if (((Value > (uint16)CANTP_STMIN_DIRECT_VALUE_RANGE) &&
             (Value < (uint16)CANTP_STMIN_US_LOW)) || (Value >
                                                       (uint16)
                                                       CANTP_STMIN_US_HIGH))
        {
          /* Report to DET */
          (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
            CANTP_CHANGEPARAM_SID, CANTP_E_PARAM_ID);

          /* Set return Value (Std_ReturnType) E_NOT_OK */
          LddReturnValue = (Std_ReturnType)E_NOT_OK;
        } /*
           * End of if (((Value > CANTP_STMIN_DIRECT_VALUE_RANGE) &&
           * Accept the new Value if it is valid
           */
        else
        #endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */
        {
          /* Store new CanTp_STMin Value */
          CanTp_GaaSTminBs[id].ucSTMin = (uint8)Value;
        }
      } /*
         * if(parameter == TP_STMIN)
         * If request is for 'CanTp_BS' parameter
         */
      else
      {
        #if (STD_ON == CANTP_DEV_ERROR_DETECT)

        /* Check the new Value of parameter 'CanTp_BS' is within a range */
        if (Value > (uint16)CANTP_MAX_BS_VAL)
        {
          /* Report to DET  */
          (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
            CANTP_CHANGEPARAM_SID, CANTP_E_PARAM_ID);

          /* Set return LddReturnValue (Std_ReturnType) E_NOT_OK */
          LddReturnValue = (Std_ReturnType)E_NOT_OK;
        } /* if(Value > CANTP_MAX_BS_VAL) */
        else
        #endif /* End of if (STD_ON == CANTP_DEV_ERROR_DETECT) */
        {
          /* Store new BS Value */
          CanTp_GaaSTminBs[id].usBlockSize = (uint16)Value;
        }
      } /* if(parameter == CANTP_BS) */
    } /*
       * if((LpChannelRam->ucChannelState < CANTP_MAX_TX_STATE) ||...
       * Check change parameter confirmation is enabled
       */
    else
    {
      /* Set return LddReturnValue (Std_ReturnType) E_NOT_OK */
      LddReturnValue = (Std_ReturnType)E_NOT_OK;
    }
  } /* if(LddReturnValue = (uint8) (uint8) E_OK) */
  return (LddReturnValue);
} /* End of CanTp_ChangeParameter(PduIdType id, TPParameterType parameter,
   * uint16 Value) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /*   #if(CANTP_CHANGE_PARAMETER_API) */

/*******************************************************************************
** Function Name       : CanTp_ReadParameter                                  **
**                                                                            **
** Service ID          : 0x0B                                                 **
**                                                                            **
** Description         : This service primitive is used to Read               **
**                       the value of the TP_STMIN or TP_BS                   **
**                       parameter. The value is stored in poiner value.      **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Non Reentrant                                        **
**                                                                            **
** Input Parameters    : id,                                                  **
**                       parameter,                                           **
**                       Pointer where the parameter LpValue will be provided.**
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : E_OK                                                 **
**                       E_NOT_OK                                             **
**                                                                            **
** Preconditions       : The CanTp module must be initialized before this call**
**                                                                            **
** Remarks             : Global Variable(s)     : CanTp_GblInitStatus,        **
**                                                CanTp_GaaRxSduStatic,       **
**                                                CanTp_GaaSTminBs            **
**                             Cantp_Max_Rx_Sduid         **
**                       Function(s) invoked    : Det_ReportError             **
*******************************************************************************/
#if ((STD_ON == CANTP_READ_PARAMETER_API)\
  && (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANTP_CODE) CanTp_ReadParameter(PduIdType id,
  TPParameterType parameter, P2VAR(uint16, AUTOMATIC, CANTP_APPL_DATA) LpValue)
{
  #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)
  P2CONST(CanTp_RxNsduStatic, AUTOMATIC, CANTP_CONST) LpRxNSdu;
  #endif
  Std_ReturnType LddReturnValue;

  /* Initialize return status with (Std_ReturnType) E_OK */
  LddReturnValue = (Std_ReturnType)E_OK;

  #if (STD_ON == CANTP_DEV_ERROR_DETECT)

  /* Check whether CanTp module initialization has not been done*/
  if (CANTP_FALSE == CanTp_GblInitStatus)
  {
    /* Report to DET  */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_READPRAM_SID, CANTP_E_UNINIT);

    /* Set return LddReturnValue (Std_ReturnType) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (CANTP_FALSE == CanTp_GblInitStatus) */

  /* check the validity of CanTpRxSduId  */
  /*if (id > (PduIdType)CANTP_MAX_RX_SDUID)*/
  if (id > (PduIdType)Cantp_Max_Rx_Sduid)
  {
    /* Report to DET */
    (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
      CANTP_READPRAM_SID, CANTP_E_PARAM_ID);

    /* Set return LddReturnValue (Std_ReturnType) E_NOT_OK */
    LddReturnValue = (Std_ReturnType)E_NOT_OK;
  } /* End of if (id > CANTP_MAX_RX_SDUID) */
  else
  {
    /* If the RxNsdu supports Functional addressing */
    #if (STD_ON == CANTP_RX_FUNCTIONAL_ADDRESSING)

    /* Get the pointer to current TxNSdu */
    LpRxNSdu = &CanTp_GaaRxSduStatic[id];

    /* If the RxNsdu supports Functional addressing */
    /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
    if ((uint8)CANTP_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType)
    {
      /* Report to DET */
      (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID,
        CANTP_READPRAM_SID, CANTP_E_PARAM_ID);

      /* Set return LpValue (Std_ReturnType) E_NOT_OK */
      LddReturnValue = (Std_ReturnType)E_NOT_OK;
    } /* End of if (CANTP_FUNCTIONAL_ADDRESS == LpRxNSdu->ucTaType) */
    #endif /* #if(CANTP_RX_FUNCTIONAL_ADDRESSING == STD_ON)  */
  } /* End of else */

  /* Check if no Det error detected */
  if ((Std_ReturnType)E_OK == LddReturnValue)
  #endif /* End of if (CANTP_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check request is for 'TP_STMIN' parameter */
    if (parameter == TP_STMIN)
    {
      /* Store CanTp_STMin Value */
      /* polyspace<MISRA-C3:D4.14 : Not a defect: Justified> Pointer is not a NULL and valid */
      /* polyspace<MISRA-C3:18.1 : Not a defect: Justified> Array index in range */
      /* polyspace<RTE:OBAI : Not a defect: Justified> Array index in range */
      *LpValue = (uint16)CanTp_GaaSTminBs[id].ucSTMin;
    } /*
       * if(parameter == CANTP_STMIN)
       * If request is for 'CanTp_BS' parameter
       */
    else
    {
      /* Store CanTp_STMinBs Value */
      /* polyspace<MISRA-C3:D4.14 : Not a defect: Justified> Pointer is not a NULL and valid */
      /* polyspace<MISRA-C3:18.1 : Not a defect: Justified> Array index in range */
      /* polyspace<RTE:OBAI : Not a defect: Justified> Array index in range */
      *LpValue = (uint16)CanTp_GaaSTminBs[id].usBlockSize;
    } /* if(parameter == CANTP_BS) */
  } /* if(LddReturnValue = E_OK) */
  return (LddReturnValue);
} /* End of CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16
   **LpValue) */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /*   #if(CANTP_READ_PARAMETER_API) */

/*******************************************************************************
** Function Name       : CanTp_TimeoutProcessing                              **
**                                                                            **
** Service ID          : NA                                                   **
**                                                                            **
** Description         : This service primitive is used to read/modify        **
**                       the timer                                            **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Non Reentrant                                        **
**                                                                            **
** Input Parameters    : LpChannelRam                                         **
**                       LpTimers                                             **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : None                                                 **
**                                                                            **
** Preconditions       : The CanTp module must be initialized before this call**
**                                                                            **
** Remarks             : Global Variable(s)     : CanTp_GaaRxNotifSts         **
**                                                CanTp_GaaTxNotifSts         **
**                       Function(s) invoked    :                             **
**                                          SchM_Exit_CanTp_TIMER_PROTECTION  **
**                                          SchM_Enter_CanTp_TIMER_PROTECTION **
**                                          CanTp_ReceptionComplete           **
**                                          CanTp_TransmissionComplete        **
*******************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"
static FUNC(void,CANTP_VAR) CanTp_TimeoutProcessing(P2VAR(CanTp_ChannelRam, AUTOMATIC,
    CANTP_VAR) LpChannelRam, P2VAR(uint16, AUTOMATIC, CANTP_VAR) LpTimers)
{
  #if (STD_ON == CANTP_RX_NSDU)
  static CONST(NotifResultType, CANTP_CONST) LaaRxNotifSts[CANTP_THREE] =
  {
    (NotifResultType)NTFRSLT_E_TIMEOUT_CR,
    (NotifResultType)NTFRSLT_E_WFT_OVRN,
    (NotifResultType)NTFRSLT_E_TIMEOUT_A
  };
  #endif
  #if (STD_ON == CANTP_TX_NSDU)
  static CONST(NotifResultType, CANTP_CONST) LaaTxNotifSts[CANTP_THREE] =
  {
    (NotifResultType)NTFRSLT_E_NOT_OK,
    (NotifResultType)NTFRSLT_E_TIMEOUT_BS,
    (NotifResultType)NTFRSLT_E_TIMEOUT_A
  };
  #endif
  P2VAR(uint16, AUTOMATIC, CANTP_VAR) LpCpyTimers = LpTimers;
  uint16 LusTimerVal;
  uint8 LucTimer;

  /* Make number of timers equal to three */
  LucTimer = (uint8)CANTP_THREE;

  /* Check all the timers of the channel whether it is running */
  do
  {
    /* Decrement timer count */
    LucTimer--;

    /* Get the current timer */
    LusTimerVal = *LpCpyTimers;

    /* Check if the timer is running */
    if (LusTimerVal != (uint8)CANTP_ZERO)
    {
      /* Decrement the timer value */
      LusTimerVal--;
      SchM_Enter_CanTp_TIMER_PROTECTION();

      /* Update the timer variable */
      *LpCpyTimers = LusTimerVal;
      SchM_Exit_CanTp_TIMER_PROTECTION();

      /* Check if the timer is expired */
      if ((uint8)CANTP_ZERO == LusTimerVal)
      {
        #if (STD_ON == CANTP_RX_NSDU)

        /* Check if the communication is for reception */
        if (LpChannelRam->ucChannelState > (uint8)CANTP_MAX_TX_STATE)
        {
          /* Invoke the reception complete with corresponding result
           * Timer N_Ar -- error result NTFRSLT_E_TIMEOUT_A
           * Timer N_Br -- error result NTFRSLT_E_WFT_OVRN
           * Timer N_Cr -- error result NTFRSLT_E_TIMEOUT_CR
           */

          /* If timer is not Br, then reception is completed */
          CanTp_ReceptionComplete(LpChannelRam,
            LaaRxNotifSts[LucTimer]);
        } /* if(LpChannelRam->ucChannelState > CANTP_MAX_TX_STATE) */
        else /* Communication is for transmission */
        #endif /* #if (CANTP_RX_NSDU == STD_ON) */
        {
          /* Invoke the transmission complete with corresponding result
           * Timer N_As -- error result NTFRSLT_E_TIMEOUT_A
           * Timer N_Bs -- error result NTFRSLT_E_TIMEOUT_BS
           * Timer N_Cs -- error result NTFRSLT_E_NOT_OK
           */
          #if (STD_ON == CANTP_TX_NSDU)

          /* Transmission is completed */
          CanTp_TransmissionComplete(LpChannelRam,
            LaaTxNotifSts[LucTimer]);
          #endif
        }
      } /* Timer is expired */
    } /* Timer is running */

    LpCpyTimers++;
  } while (LucTimer != (uint8)CANTP_ZERO);
} /* End of CanTp_TimeoutProcessing(P2VAR(CanTp_ChannelRam, AUTOMATIC, */

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

