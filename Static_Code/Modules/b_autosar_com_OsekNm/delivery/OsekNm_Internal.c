/*============================================================================*/
/*                     HYUNDAI AUTRON SOFTWARE GROUP                          */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
* %name:              OsekNm_Internal.c %
* %instance:          xar_1 %
* %version:           1.5 %
* %created_by:        ca027 %

* %date_created:      2014/04/03 08:53:38 %
*=============================================================================*/
/* DESCRIPTION : C source file for AUTOSAR OSEKNM                             */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*  Internal Functions implementation for OsekNm module                       */
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
/* 1.0.0     | 16/May/2013 | Initial Creation              | Kyung Tae Kim    */
/* 1.4.0     | 28/Dec/2018 | #15280                        | JeongSu Lim      */
/* 1.5.0     | 13/May/2020 | #21188                        | JeongSu Lim      */
/* 1.5.1     | 27/Nov/2020 | #26628                        | Saemi Kwon       */
/* 1.6.0     | 20/Jan/2021 | #27588, #27903                | Saemi Kwon       */
/*============================================================================*/

/******************************************************************************
**                      Include Section                                     **
******************************************************************************/

#include "OsekNm_Internal.h"   /* OsekNm internal functions header */
#include "OsekNm_PCTypes.h"    /* OsekNm precompile configuration header */
#include "CanIf.h"             /* CanIf Header File */
#include "Nm.h"                /* NM Header File */
#include "Nm_Cbk.h"            /* NM Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define OSEKNM_INTERNAL_C_AR_MAJOR_VERSION    4
#define OSEKNM_INTERNAL_C_AR_MINOR_VERSION    0
#define OSEKNM_INTERNAL_C_AR_PATCH_VERSION    3

/* OsekNm software version information */
#define OSEKNM_INTERNAL_C_SW_MAJOR_VERSION    1
#define OSEKNM_INTERNAL_C_SW_MINOR_VERSION    6

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (OSEKNM_INTERNAL_AR_MAJOR_VERSION != OSEKNM_INTERNAL_C_AR_MAJOR_VERSION)
  #error "OsekNm_Internal.c : Mismatch in Specification Major Version"
#endif

#if (OSEKNM_INTERNAL_AR_MINOR_VERSION != OSEKNM_INTERNAL_C_AR_MINOR_VERSION)
  #error "OsekNm_Internal.c : Mismatch in Specification Minor Version"
#endif

#if (OSEKNM_INTERNAL_AR_PATCH_VERSION != OSEKNM_INTERNAL_C_AR_PATCH_VERSION)
  #error "OsekNm_Internal.c : Mismatch in Specification Patch Version"
#endif

#if (OSEKNM_INTERNAL_SW_MAJOR_VERSION != OSEKNM_INTERNAL_C_SW_MAJOR_VERSION)
   #error "OsekNm_Internal.c : Mismatch in Software Major Version"
#endif

#if (OSEKNM_INTERNAL_SW_MINOR_VERSION != OSEKNM_INTERNAL_C_SW_MINOR_VERSION)
   #error "OsekNm_Internal.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
static FUNC(void, OSEKNM_CODE) OsekNm_StateProcessing(
  CONST(NetworkHandleType, OSEKNM_APPL_CONST) LddLocalChannelId);

/*******************************************************************************
** Function Name        : OsekNm_ModeProcessing                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function  updates current mode for             **
**                        OsekNm                                              **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : OsekNm Module should be initiaized.                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        OsekNm_GaaTimer, OsekNm_GaaChannelConfig,           **
**                        OsekNm_GaaCurrentState, OsekNm_GaaCurrentMode       **
**                        OsekNm_GaaLogicalSuccessor,                         **
**                        OsekNm_GaaCurrentNetworkState                       **
**                        Function(s) invoked    :                            **
**                        Nm_RemoteSleepIndication(),                         **
**                        Nm_StateChangeNotification(),                       **
**                        Nm_PrepareBusSleepMode()                            **
**                        Nm_BusSleepMode(), OsekNm_GetState                  **
**                        OsekNm_StateProcessing                              **
*******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, OSEKNM_CODE) OsekNm_ModeProcessing
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) LddLocalChannelId)
{
  OsekNm_StateType LddCurrentState;
  OsekNm_ModeType LddCurrentMode;
  P2CONST(Tdd_OsekNm_ChannelConfig, AUTOMATIC, OSEKNM_APPL_CONST) LpChannelPtr;
  
  /* Assign Local Channel pointer channel Config Structure */
  LpChannelPtr = &OsekNm_GaaChannelConfig[LddLocalChannelId];
  
  /* Get the current state of OsekNm in the local variable */  
  LddCurrentState = OsekNm_GaaCurrentState[LddLocalChannelId];
  LddCurrentMode = OsekNm_GaaCurrentMode[LddLocalChannelId];
  
  /* decrement timer counter */
  if(OsekNm_GaaTimer[LddLocalChannelId] != OSEKNM_ZERO)
  {
    OsekNm_GaaTimer[LddLocalChannelId]--;
  }
  
  switch(LddCurrentMode)
  {
    case OSEKNM_MODE_AWAKE:
      if(LddCurrentState == OSEKNM_STATE_LIMPHOME)
      {
        if((OsekNm_GaaCurrentNetworkState[LddLocalChannelId] == OSEKNM_RELEASED)
          && (OsekNm_GaaTimer[LddLocalChannelId] == OSEKNM_ZERO))          
        {
          /* Transmit a Limphome message before transition */
          NmTxPduDestAddr(LddLocalChannelId) = LpChannelPtr->ucNodeId;
          NmTxPduSleepAck(LddLocalChannelId) = OSEKNM_FALSE;
          NmTxPduSleepInd(LddLocalChannelId) = OSEKNM_TRUE;
          NmTxPduCmd(LddLocalChannelId)      = OSEKNM_LIMPHOME;
          /* Set user data as default */
          NmTxPduUserData0(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_0;
          NmTxPduUserData1(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_1;
          NmTxPduUserData2(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_2;
          NmTxPduUserData3(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_3;
          NmTxPduUserData4(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_4;
          NmTxPduUserData5(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_5;
          /* Request to send */
          NmTxRequest(LddLocalChannelId) = OSEKNM_TRUE;
          
          /* transition to OSEKNM_MODE_PREPARE_SLEEP */
          OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_PREPARE_SLEEP;
          /* start the timer with Tmax */
          OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutMax;
        }  
      }
    break;
    
    case OSEKNM_MODE_PREPARE_SLEEP:
      if(LddCurrentState == OSEKNM_STATE_LIMPHOME)
      {
        if(((NmRxNmMessageRecv(LddLocalChannelId) == OSEKNM_TRUE) && 
          (NmRxPduSleepInd(LddLocalChannelId) == OSEKNM_FALSE)) || 
          (OsekNm_GaaCurrentNetworkState[LddLocalChannelId] == OSEKNM_REQUESTED))
        {
          /* NM message with sleep inication bit cleared is received 
          or network is requested */
          OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_AWAKE;
          /* restart the timer */
          OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutError;

        }
        else
        {
          if(OsekNm_GaaTimer[LddLocalChannelId] == OSEKNM_ZERO)
          {
            /* transition to OSEKNM_MODE_WAIT_SLEEP */
            OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_WAIT_SLEEP;
            /* start the timer */
            OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutWaitSleep;
            /* Invoke Nm Callback */
            Nm_PrepareBusSleepMode(LpChannelPtr->ddNmChannelId);
          }
        }
      }
      else
      {
        if(OsekNm_GaaCurrentNetworkState[LddLocalChannelId] == OSEKNM_REQUESTED)
        {
          OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_AWAKE;
        }
      }
    break;
    
    case OSEKNM_MODE_WAIT_SLEEP:
       /* Check if network is requested by own node or another one */
      if(OsekNm_GaaCurrentNetworkState[LddLocalChannelId] == OSEKNM_REQUESTED)
      {
        
        /* Cancel sleep process and go to OSEKNM_MODE_AWAKE 
           because network is requested                      */
        OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_AWAKE;
        /* Check if previous state was LIMPHOME */
        if(OsekNm_GaaCurrentState[LddLocalChannelId] == OSEKNM_STATE_LIMPHOME)
  	    {
 	        /* Reset timer for LIMPHOME message */
  	      OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutError;
  	    }
  	    else
  	    {
  	      OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_RESET;
  	    }
  	    
        /* reset logical successor */
        OsekNm_GaaLogicalSuccessor[LddLocalChannelId] = LpChannelPtr->ucNodeId;
        /* Notify upper layer */
        Nm_NetworkMode(LpChannelPtr->ddNmChannelId);
      }
      else 
      {  
        if(NmSleepCancel(LddLocalChannelId) == OSEKNM_TRUE)
        {
          NmSleepCancel(LddLocalChannelId) = OSEKNM_FALSE;
          OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_AWAKE;
          /* reset logical successor to myself */
          OsekNm_GaaLogicalSuccessor[LddLocalChannelId] = LpChannelPtr->ucNodeId;
    	    /* Notify upper layer */
      	  Nm_NetworkMode(LpChannelPtr->ddNmChannelId);
      	  /* TX ON */
      	  (void)CanIf_SetPduMode(LpChannelPtr->ucControllerId, CANIF_SET_TX_ONLINE);
        }
        else if(OsekNm_GaaTimer[LddLocalChannelId] == OSEKNM_ZERO)
        {
          /* Reset failure counters */
          OsekNm_GaaTxCounter[LddLocalChannelId] = OSEKNM_ZERO;
          OsekNm_GaaRxCounter[LddLocalChannelId] = OSEKNM_ZERO;
          /* transition to OSEKNM_MODE_BUS_SLEEP */
          OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_BUS_SLEEP;
		      Nm_BusSleepMode(LpChannelPtr->ddNmChannelId);
        }
        else
        {
        }
      }  
    break;

    case OSEKNM_MODE_BUS_SLEEP:
      /* Check if network is requested by own node */
      if(OsekNm_GaaCurrentNetworkState[LddLocalChannelId] == OSEKNM_REQUESTED)
      {
        /* Cancel Bus Sleep Mode */
        OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_AWAKE;
		    OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_RESET;
        /* reset logical successor */
        OsekNm_GaaLogicalSuccessor[LddLocalChannelId] =
        OsekNm_GaaChannelConfig[LddLocalChannelId].ucNodeId;
		    /* Notify upper layer */
		    Nm_NetworkMode(LpChannelPtr->ddNmChannelId);
        /* TX ON */
        (void)CanIf_SetPduMode(LpChannelPtr->ucControllerId, CANIF_SET_TX_ONLINE); 
      }
      else if(NmWakeup(LddLocalChannelId) == OSEKNM_TRUE)
      {
        NmWakeup(LddLocalChannelId) = OSEKNM_FALSE;
        Nm_NetworkStartIndication(LpChannelPtr->ddNmChannelId);
        (void)CanIf_SetPduMode(LpChannelPtr->ucControllerId, CANIF_SET_TX_ONLINE); 
      }
      else
      {
      }
    break;
    
    default:
      /* Do Nothing */
    break;    
  }
  LddCurrentMode = OsekNm_GaaCurrentMode[LddLocalChannelId];
  if((LddCurrentMode == OSEKNM_MODE_AWAKE)||
    (LddCurrentMode == OSEKNM_MODE_PREPARE_SLEEP))
  { 
    Nm_StateType LddPrevNmState = NM_STATE_UNINIT;
    Nm_StateType LddCurrentNmState = NM_STATE_UNINIT;
    Nm_ModeType LddNmMode;
    Std_ReturnType LddReturnValue = E_NOT_OK;
    
    /* polyspace +1 MISRA-C3:14.3,2.1, DEFECT:USELESS_IF,DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */ 
    if (OsekNm_GblStateChangeIndEnabled == OSEKNM_TRUE)
    {
      LddReturnValue = OsekNm_GetState(LpChannelPtr->ddNmChannelId, &LddPrevNmState, &LddNmMode);
    }
    
    /* NM message exchange is done only before transition to BUS SLEEP MODE */
    OsekNm_StateProcessing(LddLocalChannelId);
    
    /* polyspace +1 MISRA-C3:14.3,2.1, DEFECT:USELESS_IF,DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */ 
    if (OsekNm_GblStateChangeIndEnabled == OSEKNM_TRUE)
    {
      if(LddReturnValue == E_OK)
      {
        LddReturnValue = 
          OsekNm_GetState(LpChannelPtr->ddNmChannelId, &LddCurrentNmState, &LddNmMode);
        if(LddReturnValue == E_OK)
        {
          if(LddCurrentNmState != LddPrevNmState)
          { 
            Nm_StateChangeNotification
            (LpChannelPtr->ddNmChannelId, LddPrevNmState, LddCurrentNmState);
          }
        }
      }
    }
  }
  
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : OsekNm_StateProcessing                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function  updates current state for            **
**                        OsekNm                                              **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : NA                                                  **
**                                                                            **
** Preconditions        : OsekNm Module should be initiaized.                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        OsekNm_GaaTimer, OsekNm_GaaChannelConfig,           **
**                        OsekNm_GaaCurrentState, OsekNm_GaaCurrentMode       **
**                        OsekNm_GaaLogicalSuccessor, OsekNm_GaaTxCounter     **
**                        OsekNm_GaaCurrentNetworkState, OsekNm_GaaTxCounter  **
**                        Function(s) invoked    :                            **
**                       Nm_RemoteSleepIndication, Nm_RemoteSleepCancellation **
**                        CanIf_Transmit                                      ** 
*******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, OSEKNM_CODE) OsekNm_StateProcessing
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) LddLocalChannelId)
{
  OsekNm_StateType LddCurrentState;
  P2VAR(PduInfoType, AUTOMATIC, OSEKNM_PRIVATE_DATA) LpPduInfoPtr;
  P2CONST(Tdd_OsekNm_ChannelConfig, AUTOMATIC, OSEKNM_APPL_CONST) LpChannelPtr;
  uint8 LucCount;
  
  /* get the pointer of current channel config */
  LpChannelPtr = &OsekNm_GaaChannelConfig[LddLocalChannelId];
  /* Get the current state of OsekNm in the local variable */  
  LddCurrentState = OsekNm_GaaCurrentState[LddLocalChannelId];
  switch(LddCurrentState)
  {  
    case OSEKNM_STATE_RESET:
      /* Reset state variables */
      OsekNm_GunRxFlagStatus[LddLocalChannelId].ucMaskByte     = OSEKNM_ZERO;
      OsekNm_GunTxFlagStatus[LddLocalChannelId].ucMaskByte     = OSEKNM_ZERO;
      OsekNm_GunInternFlagStatus[LddLocalChannelId].ucMaskByte = OSEKNM_ZERO;
      /* Reset Remote Sleep Indication flags */
      #if(OSEKNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
      NmRxRmtSleepInd(LddLocalChannelId) = OSEKNM_ZERO;
      NmRxRmtSleepIndNotif(LddLocalChannelId) = OSEKNM_ZERO;
      #endif
      /* Reset network configuration */
      for(LucCount = OSEKNM_ZERO;LucCount < OSEKNM_NWCFG_ARRAY_SIZE;
                                                                LucCount++)
      {
        OsekNm_GaaNetworkConfig[(LddLocalChannelId*OSEKNM_NWCFG_ARRAY_SIZE) 
                                            + LucCount] = (uint32)OSEKNM_ZERO;
      }
      /* initialize Tx NM PDU */
      NmTxPduDestAddr(LddLocalChannelId) = LpChannelPtr->ucNodeId;
      NmTxPduSleepAck(LddLocalChannelId) = OSEKNM_FALSE;
      NmTxPduSleepInd(LddLocalChannelId) = OSEKNM_FALSE;
      NmTxPduCmd(LddLocalChannelId)      = OSEKNM_ALIVE;
      NmTxPduUserData0(LddLocalChannelId) =  OSEKNM_USER_DATA_DEFAULT_0;
      NmTxPduUserData1(LddLocalChannelId) =  OSEKNM_USER_DATA_DEFAULT_1;
      NmTxPduUserData2(LddLocalChannelId) =  OSEKNM_USER_DATA_DEFAULT_2;
      NmTxPduUserData3(LddLocalChannelId) =  OSEKNM_USER_DATA_DEFAULT_3;
      NmTxPduUserData4(LddLocalChannelId) =  OSEKNM_USER_DATA_DEFAULT_4;
      NmTxPduUserData5(LddLocalChannelId) =  OSEKNM_USER_DATA_DEFAULT_5;
      /* Send NM PDU */
      NmTxRequest(LddLocalChannelId) = OSEKNM_TRUE;
      /* Increment rx counter */
      OsekNm_GaaRxCounter[LddLocalChannelId]++;
      /* Check Limphome condition */
      if((OsekNm_GaaTxCounter[LddLocalChannelId] > OSEKNM_TX_LIMIT) ||
          (OsekNm_GaaRxCounter[LddLocalChannelId] > OSEKNM_RX_LIMIT))
      {
        /* reset counter */
        OsekNm_GaaTxCounter[LddLocalChannelId] = OSEKNM_ZERO;
        OsekNm_GaaRxCounter[LddLocalChannelId] = OSEKNM_ZERO;
        /* Reset message receive flag */
        NmRxNmMessageRecv(LddLocalChannelId) = OSEKNM_FALSE;
        /* Goto LIMPHOME state */
        OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_LIMPHOME;
        /* start timer with Terror */
        OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutError;
        /* Remote Sleep Indication is true */
        #if(OSEKNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
        if(NmRxRmtSleepIndNotif(LddLocalChannelId) == OSEKNM_FALSE)
        {
          NmRxRmtSleepIndNotif(LddLocalChannelId) = OSEKNM_TRUE;
          Nm_RemoteSleepIndication(LpChannelPtr->ddNmChannelId);
        }
        #endif
      }
      else
      {
        /* Goto NORMAL state */
        OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_NORMAL;
        /* start timer with Ttyp */
        OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutTyp;        
      }
    break;
    
    case OSEKNM_STATE_NORMAL:
      if(OsekNm_GaaTxCounter[LddLocalChannelId] >= OSEKNM_TX_LIMIT)
      {
        /* reset counter */
        OsekNm_GaaTxCounter[LddLocalChannelId] = OSEKNM_ZERO;
        OsekNm_GaaRxCounter[LddLocalChannelId] = OSEKNM_ZERO;
        /* Reset message receive flag */
        NmRxNmMessageRecv(LddLocalChannelId) = OSEKNM_FALSE;
        /* goto LIMPHOME mode */
	      OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_LIMPHOME;
	      /* start timer with Terror */
	      OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutError;
        /* Remote Sleep Indication is true */
        #if(OSEKNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
        if(NmRxRmtSleepIndNotif(LddLocalChannelId) == OSEKNM_FALSE)
        {
          NmRxRmtSleepIndNotif(LddLocalChannelId) = OSEKNM_TRUE;
          Nm_RemoteSleepIndication(LpChannelPtr->ddNmChannelId);
        }
        #endif
      }
      else
      {
        /* 2014.11.26 kt.kim +++ Bug #1726 
          SkippedOver must be checked first
        */
        if(NmSkippedOver(LddLocalChannelId) == OSEKNM_TRUE)
        {
          /* Own node is skipped over */
          NmSkippedOver(LddLocalChannelId) = OSEKNM_FALSE;
          /* go to RESET mode  */
          OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_RESET;
        }
        else if(NmWaitRing(LddLocalChannelId) == OSEKNM_TRUE)
        {         
          if(OsekNm_GaaTimer[LddLocalChannelId] == OSEKNM_ZERO)
          {
            /* Tmax timer is expired thus go to RESET state */
            OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_RESET;
            /* reset logical successor */
            OsekNm_GaaLogicalSuccessor[LddLocalChannelId] = 
              LpChannelPtr->ucNodeId;
            /* Notify Nm for message timeout */
            Nm_TxTimeoutException(LpChannelPtr->ddNmChannelId);
          }  
        }
        else
        {
          /* Waiting for TYP timeout to send a RING message */
          if(OsekNm_GaaTimer[LddLocalChannelId] == OSEKNM_ZERO)
          {
            /* Make up NM PDU*/
            NmTxPduDestAddr(LddLocalChannelId) =
              OsekNm_GaaLogicalSuccessor[LddLocalChannelId];
            NmTxPduSleepAck(LddLocalChannelId) = 
              NmTxSleepAckStat(LddLocalChannelId);
            /* Set SleepInd bit of TX NM PDU */
            if(OSEKNM_RELEASED ==
                OsekNm_GaaCurrentNetworkState[LddLocalChannelId])
            {
              NmTxPduSleepInd(LddLocalChannelId) = OSEKNM_ONE;
            }
            else{
              NmTxPduSleepInd(LddLocalChannelId) = OSEKNM_ZERO;
            }
            NmTxPduCmd(LddLocalChannelId)      = OSEKNM_RING;
            /* Copying user data is not allowed */
            NmTxWaitConfirm(LddLocalChannelId) = OSEKNM_TRUE;
            /* Check if Ring is stable */
            if(OsekNm_GaaLogicalSuccessor[LddLocalChannelId] 
              != LpChannelPtr->ucNodeId)
            {
              /* Set user data as normal */
              NmTxPduUserData0(LddLocalChannelId) = OSEKNM_USER_DATA_NORMAL_0;
              NmTxPduUserData1(LddLocalChannelId) = OSEKNM_USER_DATA_NORMAL_1;
              NmTxPduUserData2(LddLocalChannelId) = OSEKNM_USER_DATA_NORMAL_2;
              NmTxPduUserData3(LddLocalChannelId) = OSEKNM_USER_DATA_NORMAL_3;
              NmTxPduUserData4(LddLocalChannelId) = OSEKNM_USER_DATA_NORMAL_4;
              NmTxPduUserData5(LddLocalChannelId) = OSEKNM_USER_DATA_NORMAL_5;
            }
            else
            {
              /* Set user data as default */
              NmTxPduUserData0(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_0;
              NmTxPduUserData1(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_1;
              NmTxPduUserData2(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_2;
              NmTxPduUserData3(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_3;
              NmTxPduUserData4(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_4;
              NmTxPduUserData5(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_5;
            }
            /* Request to send */
            NmTxRequest(LddLocalChannelId) = OSEKNM_TRUE;
            /* Timer to wait for Ring message */
            OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutMax;
            NmWaitRing(LddLocalChannelId) = OSEKNM_TRUE;  
          }         
        }
      } 
    break;
    
    case OSEKNM_STATE_LIMPHOME:
      /* Check condition to get out of LIMPHOME state */
      if((NmRxNmMessageRecv(LddLocalChannelId) == OSEKNM_TRUE) && 
        (NmTxLimphomeConf(LddLocalChannelId) == OSEKNM_TRUE))
      {
        /* Limphome message transmitted and any NM message received */
        /* Goto RESET mode */
        OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_RESET;
        /* reset the timer */
        OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutError;
        NmTxLimphomeConf(LddLocalChannelId )= OSEKNM_FALSE;
        /* reset logical successor */
        OsekNm_GaaLogicalSuccessor[LddLocalChannelId] = LpChannelPtr->ucNodeId;        
		    /* Cancel Remote Sleep Indication*/
        #if(OSEKNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
        if(NmRxRmtSleepIndNotif(LddLocalChannelId) == OSEKNM_TRUE)
        {
          NmRxRmtSleepIndNotif(LddLocalChannelId) = OSEKNM_FALSE;
          Nm_RemoteSleepCancellation(LpChannelPtr->ddNmChannelId);
        }
        #endif 
      }
      /* Check condition to transmit LimpHome message */
      else if((OsekNm_GaaTimer[LddLocalChannelId] == OSEKNM_ZERO)
        && (OsekNm_GaaCurrentMode[LddLocalChannelId] == OSEKNM_MODE_AWAKE))
      {
        /* Send Limphome message */
        NmTxPduDestAddr(LddLocalChannelId) = LpChannelPtr->ucNodeId;
        NmTxPduSleepAck(LddLocalChannelId) = OSEKNM_FALSE;
        NmTxPduSleepInd(LddLocalChannelId) = OSEKNM_FALSE;
        NmTxPduCmd(LddLocalChannelId)      = OSEKNM_LIMPHOME;
        /* Set user data as default */
        NmTxPduUserData0(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_0;
        NmTxPduUserData1(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_1;
        NmTxPduUserData2(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_2;
        NmTxPduUserData3(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_3;
        NmTxPduUserData4(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_4;
        NmTxPduUserData5(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_5;
        /* Request to send */
        NmTxRequest(LddLocalChannelId) = OSEKNM_TRUE;
        /* Restart the timer for next one */
        OsekNm_GaaTimer[LddLocalChannelId] = LpChannelPtr->usTimeoutError;
      }
      else
      {
        /* Do nothing */
      }
    break;
    
    
   
    default:
      /* Do Nothing */
    break;
  }

  /* NmRxNmMessageRecv(LddLocalChannelId) = OSEKNM_FALSE; */
  if(NmTxRequest(LddLocalChannelId) == OSEKNM_TRUE)
  {
    /* Send a PDU*/
    #if(OSEKNM_COM_CONTROL_ENABLED == STD_ON)
    if(OsekNm_GaaComControlArray[LddLocalChannelId] == OSEKNM_ENABLED)
    #endif
    {
      LpChannelPtr = &OsekNm_GaaChannelConfig[LddLocalChannelId]; 
      LpPduInfoPtr = &OsekNm_GddPduInfo[LddLocalChannelId];
      /* Assign Data Pointer to Transmit Array */ 
      LpPduInfoPtr->SduDataPtr = NmTxPduDataPtr(LddLocalChannelId);
      /* Assign the PDU Length */
      LpPduInfoPtr->SduLength = OSEKNM_NM_PDU_LENGTH;
      
      #if(OSEKNM_TX_NM_PDU_CALLOUT_SUPPORT == STD_ON)
      if((OsekNm_GaaOsekNmTxNmPduCallout[LddLocalChannelId].pTxNmPduCallout) != NULL_PTR)
      {
        (OsekNm_GaaOsekNmTxNmPduCallout[LddLocalChannelId].pTxNmPduCallout)(LpChannelPtr->ddOsekNmTxPduId, LpPduInfoPtr);
      }
      #endif
      
      (void)CanIf_Transmit(LpChannelPtr->ddTxPduId, LpPduInfoPtr);
    }
	  NmTxRequest(LddLocalChannelId) = OSEKNM_FALSE;
	  /* Increment tx counter */
	  OsekNm_GaaTxCounter[LddLocalChannelId]++;
  }  
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/******************************************************************************
**                          END OF FILE                                      **
******************************************************************************/
