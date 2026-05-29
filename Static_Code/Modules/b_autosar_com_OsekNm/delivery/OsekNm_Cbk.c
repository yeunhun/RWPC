/*============================================================================*/
/*                     HYUNDAI AUTRON SOFTWARE GROUP                          */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
* %name:              OsekNm_Cbk.c %
* %instance:          xar_1 %
* %version:           1.6 %
* %created_by:        ca027 %

* %date_created:      2014/04/03 08:53:26 %
*=============================================================================*/
/* DESCRIPTION : C source file for AUTOSAR OSEKNM                             */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*  Callback Functions implementation for OsekNm module                       */
/*                                                                            */
/*============================================================================*/
/* COPYRIGHT (C) HYUNDAI AUTRON 2012                                          */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/* 1.0.0     | 16/May/2011 | Initial Creation              | Kyung Tae Kim    */
/* 1.4.0     | 28/Dec/2018 | #15280                        | JeongSu Lim      */
/* 1.4.2     | 08/Mar/2019 | #16398                        | JeongSu Lim      */
/* 1.5.0     | 13/May/2020 | #21188                        | JeongSu Lim      */
/* 1.5.1     | 27/Nov/2020 | #26628                        | Saemi Kwon       */
/* 1.6.0     | 22/Jan/2021 | #27903                        | Saemi Kwon       */
/*============================================================================*/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "CanIf.h"
#include "CanSM_Cbk.h"
#include "OsekNm_Cbk.h"  
#include "OsekNm_PCTypes.h"
#include "OsekNm_Ram.h" /* Global RAM variables header file */
#if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "Nm_Cbk.h"
#include "SchM_OsekNm.h"    /* Schedule Manager header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define OSEKNM_CBK_C_AR_MAJOR_VERSION    4
#define OSEKNM_CBK_C_AR_MINOR_VERSION    0
#define OSEKNM_CBK_C_AR_PATCH_VERSION    3

/* OsekNm software version information */
#define OSEKNM_CBK_C_SW_MAJOR_VERSION    1
#define OSEKNM_CBK_C_SW_MINOR_VERSION    6

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (OSEKNM_CBK_AR_MAJOR_VERSION != OSEKNM_CBK_C_AR_MAJOR_VERSION)
  #error "OsekNm_Cbk.c : Mismatch in Specification Major Version"
#endif

#if (OSEKNM_CBK_AR_MINOR_VERSION != OSEKNM_CBK_C_AR_MINOR_VERSION)
  #error "OsekNm_Cbk.c : Mismatch in Specification Minor Version"
#endif

#if (OSEKNM_CBK_AR_PATCH_VERSION != OSEKNM_CBK_C_AR_PATCH_VERSION)
  #error "OsekNm_Cbk.c : Mismatch in Specification Patch Version"
#endif

#if (OSEKNM_CBK_SW_MAJOR_VERSION != OSEKNM_CBK_C_SW_MAJOR_VERSION)
   #error "OsekNm_Cbk.c : Mismatch in Major Version"
#endif

#if (OSEKNM_CBK_SW_MINOR_VERSION != OSEKNM_CBK_C_SW_MINOR_VERSION)
   #error "OsekNm_Cbk.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                    **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
static FUNC(void, OSEKNM_CODE) OsekNm_ProcessRingMessage(
  NetworkHandleType  ChannelId,
  uint8 SrcAddress);

/*******************************************************************************
* Function Name      : OsekNm_TxConfirmation
*
* Service ID         : N/A
*
* Description        : Notify OSEKNM that an NM message has been successfully 
 *                     transmitted.
*
* Re-entrancy        : Re-entrant(but not for the same NM-channel)
*
* Input Parameters   : canNmTxPduId
*
* Output Parameters  : None
*
* Return parameter   : void
*
* Preconditions      : The OsekNm and the CanIf itself are initialized 
*
* Remarks            : Global Variable(s):
*                      OsekNm_GblInitStatus, OsekNm_GaaOsekNmTxPduIdChannelMap
*                      OsekNm_GaaTxCounter, OsekNm_GaaCurrentMode, 
*                      OsekNm_GaaChannelConfig, OsekNm_GunTxFlagStatus,
*                      OsekNm_GaaTxPduData
*                      Function Invoked:
*                      (void) Det_ReportError()
*                      Nm_PrepareBusSleepMode()
*******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"
 
FUNC(void, OSEKNM_CODE) OsekNm_TxConfirmation(PduIdType canNmTxPduId)
{
  NetworkHandleType  LddLocalChannelId;
  uint8 LucCount;
  P2CONST(Tdd_OsekNm_ChannelConfig, AUTOMATIC, OSEKNM_APPL_CONST) LpChannelPtr; 

  #if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;
  /* Initialize error flag to false */
  LblDetErrFlag = OSEKNM_FALSE;
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, (uint8)canNmTxPduId, OSEKNM_TX_CONFIRMATION_SID, OSEKE_NO_INIT);
    /* Set error flag to true */
    LblDetErrFlag = OSEKNM_TRUE;                          
  }
  /* Check if the channel number is valid */
  if (canNmTxPduId >= OSEKNM_NUMBER_OF_CHANNELS)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, (uint8)canNmTxPduId, OSEKNM_TX_CONFIRMATION_SID, OSEKE_INVALID_CHANNEL);
    /* Set error flag to true */
    LblDetErrFlag = OSEKNM_TRUE;                      
  }
  else
  {
     
    LddLocalChannelId = OsekNm_GaaOsekNmTxPduIdChannelMap[canNmTxPduId];
    /* polyspace +1 MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values." */ 
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, (uint8)canNmTxPduId, OSEKNM_TX_CONFIRMATION_SID, OSEKE_INVALID_CHANNEL);
      /* Set error flag to true */
      LblDetErrFlag = OSEKNM_TRUE;                  
    }
    
  } 
  /* Check if no Development error occurred */
  if(LblDetErrFlag == OSEKNM_FALSE)
  #endif /* OSEKNM_DEV_ERROR_DETECT */
  {
    /* Get the Internal Channel Id of OSEKNM */
    /* polyspace +1 MISRA-C3:18.1,D4.14, RTE:OBAI [Not a defect:Justified] "Pointer is in range and vaild" */
    LddLocalChannelId = OsekNm_GaaOsekNmTxPduIdChannelMap[canNmTxPduId];
    LpChannelPtr = &OsekNm_GaaChannelConfig[LddLocalChannelId];  
    /* Clear tx failure counter */
    OsekNm_GaaTxCounter[LddLocalChannelId] = OSEKNM_ZERO;
    /* Check command type */
    if(NmTxPduCmd(LddLocalChannelId) == OSEKNM_RING)
    {
      /* Copying user data is allowed */
      NmTxWaitConfirm(LddLocalChannelId) = OSEKNM_FALSE;
      /* check previous remote sleep indication */
      #if(OSEKNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
      if(NmRxRmtSleepInd(LddLocalChannelId) == OSEKNM_TRUE)
      {
        if(NmRxRmtSleepIndNotif(LddLocalChannelId) == OSEKNM_FALSE)
        {
          NmRxRmtSleepIndNotif(LddLocalChannelId) = OSEKNM_TRUE;
          Nm_RemoteSleepIndication(LpChannelPtr->ddNmChannelId);
        }
      } 
      /* start checking remote sleep indication */
      NmRxRmtSleepInd(LddLocalChannelId) = OSEKNM_TRUE;
      #endif
      /* Check to restart monitoring SleepInd on NM messages
         because NM message has been transmitted           */
      if(NmRxSleepIndStat(LddLocalChannelId) == OSEKNM_FALSE)
      {
         /* Turn on the monitoring flag for sleep indication
            in the other nodes on the network. */
         NmRxSleepIndStat(LddLocalChannelId) = OSEKNM_TRUE;
      }

      if((OSEKNM_RELEASED == OsekNm_GaaCurrentNetworkState[LddLocalChannelId])
          && (NmTxPduSleepInd(LddLocalChannelId) == OSEKNM_TRUE))
      {
         /* Network is released and RING message with sleep indication bit set
            has been sent by own node. */ 
        if(NmTxPduSleepAck(LddLocalChannelId) == OSEKNM_TRUE)
        {
          /* transition to OSEKNM_MODE_WAIT_SLEEP mode */
          OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_WAIT_SLEEP;
          /* Invoke Nm callback */
          Nm_PrepareBusSleepMode(LpChannelPtr->ddNmChannelId);
          /* start the timer */
          OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutWaitSleep;
          /* TX OFF */
          (void)CanIf_SetPduMode(LpChannelPtr->ucControllerId, CANIF_SET_TX_OFFLINE);
          /* Reset network configuration */
          for(LucCount = OSEKNM_ZERO;LucCount < OSEKNM_NWCFG_ARRAY_SIZE; LucCount++)
          {
           OsekNm_GaaNetworkConfig[(LddLocalChannelId*OSEKNM_NWCFG_ARRAY_SIZE) 
                                              + LucCount] = (uint32)OSEKNM_ZERO;
          }
        }
      }
    }
    else if(NmTxPduCmd(LddLocalChannelId) == OSEKNM_LIMPHOME)
    {
      NmTxLimphomeConf(LddLocalChannelId) = OSEKNM_TRUE;
    }
    else
    {
    }
  }    
}   

#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h" 
/*******************************************************************************
* Function Name      : OsekNm_ProcessRingMessage
*
* Service ID         : N/A
*
* Description        : Process received RING message.  
*                     
*
* Re-entrancy        : Re-entrant(but not for the same NM-channel)
*
* Input Parameters   : ChannelId, SrcAddress
*
* Output Parameters  : None
*
* Return parameter   : void
*
* Preconditions      : The OsekNm is initialized 
*
* Remarks            : Global Variable(s):
*                      OsekNm_GaaChannelConfig, OsekNm_GunRxFlagStatus,
*                      OsekNm_GaaRxPduData
*                      Function Invoked:
*                      (void) Det_ReportError()
*                      Nm_PrepareBusSleepMode()
*******************************************************************************/

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"
 
static FUNC(void, OSEKNM_CODE) OsekNm_ProcessRingMessage
                                 (NetworkHandleType  ChannelId, uint8 SrcAddress)
{
  /* Assign Local Channel pointer channel Config Structure */
  P2CONST(Tdd_OsekNm_ChannelConfig, AUTOMATIC, OSEKNM_APPL_CONST) LpChannelPtr;
  
  LpChannelPtr = &OsekNm_GaaChannelConfig[ChannelId];
  /* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values." */ 
  if((NmRxPduDestAddr(ChannelId) == LpChannelPtr->ucNodeId)
         || (NmRxPduDestAddr(ChannelId) == SrcAddress))
  {
    /* Check condition for sending SleepAck */
    if(NmRxPduDestAddr(ChannelId) == LpChannelPtr->ucNodeId)
    {
      if((NmRxSleepIndStat(ChannelId) == OSEKNM_TRUE) &&
        (OSEKNM_RELEASED == 
               OsekNm_GaaCurrentNetworkState[ChannelId])&&
              (NmTxPduSleepInd(ChannelId) == OSEKNM_TRUE))
      {
        /* Set SleepAck flag */
        NmTxSleepAckStat(ChannelId) = OSEKNM_TRUE;
      }
      else
      {
        /* Clear SleepAck flag */
        NmTxSleepAckStat(ChannelId) = OSEKNM_FALSE;
      }
    }
    if(NmWaitRing(ChannelId) == OSEKNM_TRUE)
    {
      /* OsekNm goes to transmission mode */
      NmWaitRing(ChannelId) = OSEKNM_FALSE;
      NmRxSleepIndStat(ChannelId) = OSEKNM_FALSE;
    }
    /* Set timer for transmission */
    OsekNm_GaaTimer[ChannelId] = LpChannelPtr->usTimeoutTyp;        
  }
  else
  {
    /* Reset Ring Message Timeout */
    OsekNm_GaaTimer[ChannelId] = LpChannelPtr->usTimeoutMax;
    /* Check if transmission in progress */
    if((NmWaitRing(ChannelId) == OSEKNM_FALSE) 
      && (NmTxPduCmd(ChannelId) == OSEKNM_RING))
    {
      /* Cancel transmission for Ring message */
      NmWaitRing(ChannelId) = OSEKNM_TRUE;
    }
  }
  /* Check SkippedOver */
  if(NmRxPduDestAddr(ChannelId) > LpChannelPtr->ucNodeId)
  {
    if((NmRxPduDestAddr(ChannelId) < SrcAddress) ||
      (LpChannelPtr->ucNodeId > SrcAddress))
    {
      NmSkippedOver(ChannelId) = OSEKNM_TRUE;  
    }
  }
  else if(NmRxPduDestAddr(ChannelId) < SrcAddress)
  {
    if(LpChannelPtr->ucNodeId > SrcAddress)
    { 
      NmSkippedOver(ChannelId) = OSEKNM_TRUE;
    }
  }
  /* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values." */ 
  else
  {
    /* No SkippedOver */
  }  
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h" 
/*******************************************************************************
* Function Name      : OsekNm_RxIndication
*
* Service ID         : N/A
*
* Description        : Notify OSEKNM that an NM message has been received.
*
* Re-entrancy        : Re-entrant(but not for the same NM-channel)
*
* Input Parameters   : OsekNmRxPduId, PduInfoPtr
*
* Output Parameters  : None
*
* Return parameter   : void
*
* Preconditions      : The OsekNm and the CanIf itself are initialized
*
* Remarks            : Global Variable(s):
*                      OsekNm_GblInitStatus, OsekNm_GaaInternalChannelMap,
*                      OsekNm_GaaRxPduData, OsekNm_GaaBusLdRdnStatus,
*                      OsekNm_GaaMessageCycleTimer, OsekNm_GaaMessageTimeOutTimer.
*                      Function Invoked:
*                      (void) Det_ReportError(), Nm_PduRxIndication(),
*                      CanIf_ReadRxCanId(), Nm_NetworkMode(),
*                      SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT(),
*                      SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT()
*******************************************************************************/

#define OSEKNM_START_SEC_CODE
#include "MemMap.h" 

FUNC(void, OSEKNM_CODE) OsekNm_RxIndication (PduIdType canNmRxPduId, 
                         P2CONST(PduInfoType, AUTOMATIC, OSEKNM_APPL_CONST) PduInfoPtr)
{
   P2CONST(uint8, AUTOMATIC, OSEKNM_PRIVATE_DATA) LpSrcDataPtr;
   P2VAR(uint8, AUTOMATIC, OSEKNM_PRIVATE_DATA) LpDestnDataPtr;
   P2CONST(Tdd_OsekNm_ChannelConfig, AUTOMATIC, OSEKNM_APPL_CONST) LpChannelPtr;
   NetworkHandleType  LddLocalChannelId;
   Can_IdType LddRxCanId;
   uint8 LucCount;
   uint8 LucSrcAddress;
      
   #if(OSEKNM_DEV_ERROR_DETECT == STD_ON)
   boolean LblDetErrFlag;
   /* Initialize error flag to false */
   LblDetErrFlag = OSEKNM_FALSE;
   /* Check whether CanSdu is equal to Null Ptr */
   if(PduInfoPtr == NULL_PTR)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, OSEKNM_ZERO, OSEKNM_RX_INDICATION_SID,
                                                       OSEKE_NULL_POINTER);
    /* Set error flag to true */
    LblDetErrFlag = OSEKNM_TRUE; 
  }   
   /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, (uint8)canNmRxPduId, OSEKNM_RX_INDICATION_SID, OSEKE_NO_INIT);
    /* Set error flag to true */
    LblDetErrFlag = OSEKNM_TRUE; 
  }
   /* Check if the channel number is valid */
  if (canNmRxPduId >= OsekNm_GddNumberOfRxPdu)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, (uint8)canNmRxPduId, OSEKNM_RX_INDICATION_SID, OSEKE_INVALID_CHANNEL);
                        
    /* Set error flag to true */
    LblDetErrFlag = OSEKNM_TRUE; 
  }
  else
  {
	 /* Improvement #1129 */
     LddLocalChannelId = OsekNm_GaaOsekNmRxPduIdChannelMap[canNmRxPduId];
     
     /* polyspace +1 MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values." */ 
     if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
     {
       /* Report to DET */
       (void) Det_ReportError (OSEKNM_MODULE_ID, (uint8)canNmRxPduId, OSEKNM_RX_INDICATION_SID, OSEKE_INVALID_CHANNEL);
       /* Set error flag to true */
       LblDetErrFlag = OSEKNM_TRUE; 
     } 
  } 
  /* Check if no Development error occurred */
  if(LblDetErrFlag == OSEKNM_FALSE)
  #endif /* OSEKNM_DEV_ERROR_DETECT */
  {
    LddRxCanId = OSEKNM_ZERO;
    /* Get the Internal Channel Id of OSEKNM */
    /* Improvement #1129 */
    /* polyspace +1 MISRA-C3:18.1,D4.14, RTE:OBAI [Not a defect:Justified] "Pointer is in range and vaild" */    
    LddLocalChannelId = OsekNm_GaaOsekNmRxPduIdChannelMap[canNmRxPduId];
    LucCount = OSEKNM_ZERO;
    /* Assign SduDataPtr to local pointer */  
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */		
    LpSrcDataPtr = PduInfoPtr->SduDataPtr;
    /* Assign Local pointer to Receive Array */
    LpDestnDataPtr = NmRxPduDataPtr(LddLocalChannelId);
    /* Assign Local Channel pointer channel Config Structure */
    LpChannelPtr = &OsekNm_GaaChannelConfig[LddLocalChannelId];
    /* Enter the critical area for Rx User Data Protection */
    SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();    

    do
    { 
      /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Pointer is in range and vaild" */
      *LpDestnDataPtr = *LpSrcDataPtr;
      LpSrcDataPtr++;
      LpDestnDataPtr++;
      LucCount++;
    }while(LucCount < PduInfoPtr->SduLength);
		
    SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
    /* read source address of received NM message */
    CanIf_ReadRxCanId(&LddRxCanId); 
    LucSrcAddress = (uint8)(LddRxCanId & NM_ADDRESS_MASK);
    
    /* Write network configuration */
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Pointer is in range and vaild" */		
    OsekNm_GaaNetworkConfig[(LddLocalChannelId*OSEKNM_NWCFG_ARRAY_SIZE) +
                      (LucSrcAddress/OSEKNM_NWCFG_BIT_SIZE)]|=
              (((uint32)OSEKNM_ONE) << (LucSrcAddress % OSEKNM_NWCFG_BIT_SIZE));
    
    /* polyspace +1 MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values." */ 
    if (OsekNm_GblPduRxIndicationEnabled == OSEKNM_TRUE)
    {
      /* Notify the upper layer */
      Nm_PduRxIndication(LpChannelPtr->ddNmChannelId);
    }
    
    /* Clear rx failure counter because a valid NM message is received */
    OsekNm_GaaRxCounter[LddLocalChannelId] = OSEKNM_ZERO;
    NmRxNmMessageRecv(LddLocalChannelId) = OSEKNM_TRUE;
         
    if((NmRxPduCmd(LddLocalChannelId) == OSEKNM_RING) || 
      (NmRxPduCmd(LddLocalChannelId) == OSEKNM_ALIVE))
    {
      /* Read sleep indication bit */
      if(NmRxPduSleepInd(LddLocalChannelId) == OSEKNM_FALSE)
      {
        /* Clear monitoring flag for sleep indication */
        NmRxSleepIndStat(LddLocalChannelId) = OSEKNM_FALSE;
        /* Clear remote sleep indication bit */
        #if(OSEKNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
        NmRxRmtSleepInd(LddLocalChannelId) = OSEKNM_FALSE;
        if(NmRxRmtSleepIndNotif(LddLocalChannelId) == OSEKNM_TRUE)
        {
          NmRxRmtSleepIndNotif(LddLocalChannelId) = OSEKNM_FALSE;
          Nm_RemoteSleepCancellation(LpChannelPtr->ddNmChannelId);
        }
        #endif
      }
                  
      if(OsekNm_GaaCurrentMode[LddLocalChannelId] == OSEKNM_MODE_BUS_SLEEP)
      {
  	    /* Nm_NetworkStartIndication(LpChannelPtr->ddNmChannelId); */
        NmWakeup(LddLocalChannelId) = OSEKNM_TRUE;
      }
      else if(OsekNm_GaaCurrentMode[LddLocalChannelId] == OSEKNM_MODE_WAIT_SLEEP)
      {
        if(NmRxPduSleepInd(LddLocalChannelId) == OSEKNM_FALSE)
        {
  	      /* Check previous state was LIMPHOME */
    	    if(OsekNm_GaaCurrentState[LddLocalChannelId] == OSEKNM_STATE_LIMPHOME)
    	    {
    	      /* To send Limphome message once after sleep cancellation */
    	      NmTxLimphomeConf(LddLocalChannelId) = OSEKNM_FALSE;
    	      /* NmRxNmMessageRecv(LddLocalChannelId) = OSEKNM_FALSE;*/
    	      /* Reset timer for LIMPHOME message */
    	      OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutError;
    	    }
    	    else
    	    {
    		    /* Go to RESET state to transmit ALIVE message */
    	      OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_RESET;
    	    }
    	    NmSleepCancel(LddLocalChannelId) = OSEKNM_TRUE;
        }
      }
      else
      {
        /* update logical successor */
        if(OsekNm_GaaLogicalSuccessor[LddLocalChannelId] > 
                                                         LpChannelPtr->ucNodeId)
        {
          if((LucSrcAddress < OsekNm_GaaLogicalSuccessor[LddLocalChannelId]) &&
                                       (LucSrcAddress > LpChannelPtr->ucNodeId))
          {
            /* New logical successor is found */
            OsekNm_GaaLogicalSuccessor[LddLocalChannelId] = LucSrcAddress;
          }   
        }
        else
        {
          if((LucSrcAddress < OsekNm_GaaLogicalSuccessor[LddLocalChannelId]) || 
                                       (LucSrcAddress > LpChannelPtr->ucNodeId))
          {
            /* Initial logical successor is set */
            OsekNm_GaaLogicalSuccessor[LddLocalChannelId] = LucSrcAddress;
          }
        }
        if(NmRxPduCmd(LddLocalChannelId) == OSEKNM_RING)
        {
          if((NmRxPduSleepAck(LddLocalChannelId) == OSEKNM_TRUE) &&
           (OSEKNM_RELEASED == OsekNm_GaaCurrentNetworkState[LddLocalChannelId]) 
                         &&(NmRxSleepIndStat(LddLocalChannelId) == OSEKNM_TRUE))
          {
            /* SleepAck flag is received and all the nodes set SleepInd flag 
            Transition to OSEKNM_MODE_WAIT_SLEEP is allowed               */
            OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_WAIT_SLEEP;
            /* Invoke Nm Callback */
            Nm_PrepareBusSleepMode(LpChannelPtr->ddNmChannelId);
            /* start the timer */
            OsekNm_GaaTimer[LddLocalChannelId] = 
                                               LpChannelPtr->usTimeoutWaitSleep;
            /* Clear SleepAck flag */
            NmTxSleepAckStat(LddLocalChannelId) = OSEKNM_FALSE;
            /* Reset network configuration */
            for(LucCount = OSEKNM_ZERO;LucCount < OSEKNM_NWCFG_ARRAY_SIZE; LucCount++)
            {
              OsekNm_GaaNetworkConfig[(LddLocalChannelId*OSEKNM_NWCFG_ARRAY_SIZE)
                                            + LucCount] = (uint32)OSEKNM_ZERO;
            }
            /* TX OFF */
            (void)CanIf_SetPduMode(LpChannelPtr->ucControllerId, CANIF_SET_TX_OFFLINE);
          } 
          else 
          {
            /* Check if NM message should be sent */
            /* 2014.11.26 kt.kim +++ Bug #1726 
               If OsekNm is currently in transmission mode 
               timer must not be reset.                     
            */
            if(OsekNm_GaaCurrentState[LddLocalChannelId] != 
                                                          OSEKNM_STATE_LIMPHOME)
            {
              OsekNm_ProcessRingMessage(LddLocalChannelId, LucSrcAddress);
            }/* if(OsekNm_GaaCurrentState[LddLocalChannelId] 
                 != OSEKNM_STATE_LIMPHOME) */
          }
        }
        else
        {
          /*This is an ALIVE message */
          /* Clear monitoring flag for sleep indication */
          NmRxSleepIndStat(LddLocalChannelId) = OSEKNM_FALSE;
          /* Clear Sleep Ack flag */
          NmTxSleepAckStat(LddLocalChannelId) = OSEKNM_FALSE;
  		    /* Ring is not stable */
  		    NmRingStable(LddLocalChannelId) = OSEKNM_FALSE;
        }
      }
    }
    else
    {
      /* This is an invalid NM message */
      /* Ring is not stable */
	    NmRingStable(LddLocalChannelId) = OSEKNM_FALSE;     
    }
  
  } /* No Development errors occurred */
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"  


/*******************************************************************************
* Function Name      : OsekNm_ControllerBusOff                                 *
*                                                                              *
* Service ID         : N/A                                                     *
*                                                                              * 
* Description        : Notify OsekNm that a Bus Off has been taken place.      *
*                                                                              *
* Re-entrancy        : Re-entrant(but not for the same NM-channel)             *
*                                                                              *
* Input Parameters   : ControllerId                                            *
*                                                                              *
* Output Parameters  : None                                                    *
*                                                                              *
* Return parameter   : void                                                    *
*                                                                              *
* Preconditions      : The OsekNm and the CanIf itself                         *
*                      are initialized correctly                               *
*                                                                              *
* Remarks            : Global Variable(s):                                     *
*                      Function Invoked:                                       *
*******************************************************************************/

#define OSEKNM_START_SEC_CODE
#include "MemMap.h" 

FUNC(void, OSEKNM_CODE) OsekNm_ControllerBusOff ( 
   VAR(uint8, OSEKNM_VAR) CanControllerId)
{  
  NetworkHandleType LddLocalChannelId;
  uint8 LucCount;
  
  #if(OSEKNM_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;
  
  LblDetErrFlag = OSEKNM_FALSE;
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, CanControllerId, OSEKNM_CTRL_BUSOFF_SID, OSEKE_NO_INIT);
    /* Set error flag to true */
    LblDetErrFlag = OSEKNM_TRUE; 
  }
  else if (CanControllerId > OSEKNM_MAX_CANIF_CTRL_ID)
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, CanControllerId, OSEKNM_CTRL_BUSOFF_SID, OSEKE_INVALID_PARAM);
    /* Set error flag to true */
    LblDetErrFlag = OSEKNM_TRUE; 
  }
  else
  {
    ;
  }
  
  
  /* Check if no Development error occurred */
  if(LblDetErrFlag == OSEKNM_FALSE)
  #endif /* OSEKNM_DEV_ERROR_DETECT */
  { 
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Array index in range and vaild" */
    LddLocalChannelId = OsekNm_GaaOsekNmCanIfChannelMap[CanControllerId];
    /* polyspace +1 MISRA-C3:14.3, DEFECT:USELESS_IF [Not a defect: Justified] "Condition will be executed based on the configured values" */
  	if(OSEKNM_INACTIVE_CHANNEL != LddLocalChannelId)
  	{
  	  /* reset counter */
      OsekNm_GaaTxCounter[LddLocalChannelId] = OSEKNM_ZERO;
      OsekNm_GaaRxCounter[LddLocalChannelId] = OSEKNM_ZERO;
      /* Reset message receive flag */
      NmRxNmMessageRecv(LddLocalChannelId) = OSEKNM_FALSE;
      /* goto LIMPHOME mode */
      OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_LIMPHOME;

      /* Avoid blocking going from WAIT BUS SLEEP to BUS SLEEP
         by resetting timer on consecutive Bus-Offs             */
      if(OsekNm_GaaCurrentMode[LddLocalChannelId] != OSEKNM_MODE_WAIT_SLEEP)
      {
        /* start timer with Terror */
        OsekNm_GaaTimer[LddLocalChannelId] =
            OsekNm_GaaChannelConfig[LddLocalChannelId].usTimeoutError;
      }

      /* Reset network configuration */
      for(LucCount = OSEKNM_ZERO;LucCount < OSEKNM_NWCFG_ARRAY_SIZE; 
                                                                   LucCount++)
      {
        OsekNm_GaaNetworkConfig[(LddLocalChannelId*OSEKNM_NWCFG_ARRAY_SIZE) 
                                            + LucCount] = (uint32)OSEKNM_ZERO;
      }
  	}
  }
  CanSM_ControllerBusOff(CanControllerId);  
}

#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"  
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
