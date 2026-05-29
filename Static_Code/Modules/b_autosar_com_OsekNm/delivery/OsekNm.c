/*============================================================================*/
/*                     HYUNDAI AUTRON SOFTWARE GROUP                          */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================
* %name:              OsekNm.c %
* %instance:          xar_1 %
* %version:           1.3.9 %
* %created_by:        ca027 %

* %date_created:      2014/04/03 08:53:44 %
*=============================================================================*/
/* DESCRIPTION : C source file for AUTOSAR OsekNm                             */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*  API Functions implementation for OsekNm module                            */
/*                                                                            */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/* Provision of OSEKNM extern variables for OsekNm module                     */
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
/* 1.5.0     | 13/May/2020 | #21188                        | JeongSu Lim      */
/* 1.5.1     | 27/Nov/2020 | #26628                        | Saemi Kwon       */
/* 1.6.0     | 22/Jan/2021 | #27903                        | Saemi Kwon       */
/*============================================================================*/



/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "OsekNm.h"         /* OsekNm APIs header file */
#include "OsekNm_PCTypes.h" /* OsekNm precompile configuration header */
#include "OsekNm_Internal.h" 
#include "OsekNm_Ram.h"     /* Global RAM variables header file */
#if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "CanIf.h"         /* CanIf Header File */
#include "Nm_Cbk.h"
#include "SchM_OsekNm.h"    /* Schedule Manager header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define OSEKNM_C_AR_MAJOR_VERSION    4
#define OSEKNM_C_AR_MINOR_VERSION    0
#define OSEKNM_C_AR_PATCH_VERSION    3

/* OsekNm software version information */
#define OSEKNM_C_SW_MAJOR_VERSION    1
#define OSEKNM_C_SW_MINOR_VERSION    6

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (OSEKNM_AR_MAJOR_VERSION != OSEKNM_C_AR_MAJOR_VERSION)
  #error "OsekNm.c : Mismatch in Specification Major Version"
#endif

#if (OSEKNM_AR_MINOR_VERSION != OSEKNM_C_AR_MINOR_VERSION)
  #error "OsekNm.c : Mismatch in Specification Minor Version"
#endif

#if (OSEKNM_AR_PATCH_VERSION != OSEKNM_C_AR_PATCH_VERSION)
  #error "OsekNm.c : Mismatch in Specification Patch Version"
#endif

#if (OSEKNM_SW_MAJOR_VERSION != OSEKNM_C_SW_MAJOR_VERSION)
   #error "OsekNm.c : Mismatch in Software Major Version"
#endif

#if (OSEKNM_SW_MINOR_VERSION != OSEKNM_C_SW_MINOR_VERSION)
   #error "OsekNm.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace:begin <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
* Function Name      : OsekNm_Init
*
* Service ID         : N/A
*
* Description        : This service performs complete initialization of the 
*                      OSEK NM Module.
*
* Re-entrancy        : Non Re-entrant
*
* Input Parameters   : None
*
* Output Parameters  : None
*
* Return parameter   : void
*
* Preconditions      : None
*
* Remarks            : Global Variable(s): OsekNm_GaaInternalChannelMap
*                      OsekNm_GaaChannelConfig, OsekNm_GaaRxCounter,
*                      OsekNm_GaaTxCounter, OsekNm_GunRxFlagStatus,
*                      OsekNm_GunTxFlagStatus, OsekNm_GunInternFlagStatus, 
*                      OsekNm_GaaLogicalSuccessor, OsekNm_GaaCurrentNetworkState,
*                      OsekNm_GaaCurrentMode, OsekNm_GaaCurrentState,
*                      OsekNm_GaaComControlArray, OsekNm_GaaTxPduData,
*                      OsekNm_GblInitStatus, OsekNm_GaaNetworkConfig  
*                      Function Invoked:
*                      Nm_BusSleepMode() 
*
*******************************************************************************/


#define OSEKNM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, OSEKNM_CODE) OsekNm_Init(void)
{
  P2CONST(Tdd_OsekNm_ChannelConfig, AUTOMATIC, OSEKNM_APPL_CONST) LpChannelPtr;
  NetworkHandleType  LddLocalChannelId;
  uint8 LucCount;
   
  for(LddLocalChannelId = OSEKNM_ZERO;
		  LddLocalChannelId < OSEKNM_NUMBER_OF_CHANNELS;LddLocalChannelId++)
  {                                              
    LpChannelPtr = &OsekNm_GaaChannelConfig[LddLocalChannelId];
     /* initialize TX/RX failure counter  */
     OsekNm_GaaRxCounter[LddLocalChannelId] = 0;
     OsekNm_GaaTxCounter[LddLocalChannelId] = 0;
     /* reset timer */
     OsekNm_GaaTimer[LddLocalChannelId] = OSEKNM_ZERO;             
     /* reset status variables */
     OsekNm_GunRxFlagStatus[LddLocalChannelId].ucMaskByte = 0;
     OsekNm_GunTxFlagStatus[LddLocalChannelId].ucMaskByte = 0;
     OsekNm_GunInternFlagStatus[LddLocalChannelId].ucMaskByte = 0;
     /* set default logical successor */
     OsekNm_GaaLogicalSuccessor[LddLocalChannelId] = LpChannelPtr->ucNodeId;
     /* Set destination address of NM PDU */
     NmTxPduDestAddr(LddLocalChannelId) = LpChannelPtr->ucNodeId;
     /* Set command flag of NM PDU */
     NmTxPduCmd(LddLocalChannelId) = OSEKNM_ALIVE;
     /* Set user data to default */
     NmTxPduUserData0(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_0;
     NmTxPduUserData1(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_1;
     NmTxPduUserData2(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_2;
     NmTxPduUserData3(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_3;
     NmTxPduUserData4(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_4;
     NmTxPduUserData5(LddLocalChannelId) = OSEKNM_USER_DATA_DEFAULT_5;
     /* Network state will be initialized as released */
     OsekNm_GaaCurrentNetworkState[LddLocalChannelId] = OSEKNM_RELEASED;
     /* Mode initialized as BUS SLEEP */
     OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_BUS_SLEEP;
     /* State initialized as RESET */
     OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_RESET;
     /* NM PDU transmission ability is set to enabled*/
     #if(OSEKNM_COM_CONTROL_ENABLED == STD_ON)
     OsekNm_GaaComControlArray[LddLocalChannelId] = OSEKNM_ENABLED;
     #endif
     /* Reset network configuration */
     for(LucCount = OSEKNM_ZERO;LucCount < OSEKNM_NWCFG_ARRAY_SIZE; LucCount++)
     {
       OsekNm_GaaNetworkConfig[(LddLocalChannelId*OSEKNM_NWCFG_ARRAY_SIZE) 
                                            + LucCount] = (uint32)OSEKNM_ZERO;
     }
     /* Notify Bus-Sleep mode to the upper layer */
     Nm_BusSleepMode(LpChannelPtr->ddNmChannelId);     
   } /* Channel loop */
   /* Set flag to indicate OsekNm is initialized */
   OsekNm_GblInitStatus = OSEKNM_TRUE;
   
}

#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
 * Function         :  OsekNm_SetUserData
 *
 * Service ID       :  0x06
 *
 * Description      :  Set user data for NM messages transmitted next on the 
 *                     bus.
 *
 * Re-entrancy      :  Non-Reentrant
 *
 * Input Parameters :  nmChannelHandle, nmUserDataPtr
 *
 * Output Parameters:  NA
 *
 * Return Parameter :  Std_ReturnType
 *
 * Preconditions    :  The OsekNm and the CanIf itself are initialized correctly.
 * 
 * Remarks          :  Global Variable(s):
 *                     OsekNm_GblInitStatus, OsekNm_GaaInternalChannelMap,
 *                     OsekNm_GaaTxPduData. 
 *                     Function Invoked:
 *                     SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT()
 *                     SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT()
 *
 ******************************************************************************/

#if(OSEKNM_USER_DATA_ENABLED == STD_ON)

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_SetUserData
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
                    CONSTP2CONST(uint8, AUTOMATIC, OSEKNM_APPL_CONST) nmUserDataPtr)
{
  P2CONST(uint8, AUTOMATIC, OSEKNM_PRIVATE_CONST) LpDataPtr;
  /* Return Type */
  Std_ReturnType LddReturnValue;
  NetworkHandleType LddLocalChannelId;
 
  LddReturnValue = E_OK;
   
  #if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
  LpDataPtr = nmUserDataPtr;
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, OSEKNM_SET_USERDATA_SID,
                                                               OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
    
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                           OSEKNM_SET_USERDATA_SID, OSEKE_INVALID_CHANNEL);
                    
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                             OSEKNM_SET_USERDATA_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }    

  /* Check if the pointer parameters are invalid */
  if(LpDataPtr == NULL_PTR)
  { 
     /* Report to DET */
     (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, OSEKNM_SET_USERDATA_SID, 
                                                       OSEKE_NULL_POINTER);
     /* Set return value E_NOT_OK */
     LddReturnValue = E_NOT_OK;
  }
  /* Check if no Development error occurred */
  if(LddReturnValue == E_OK)
  #endif
  {
    /* Get the Internal Channel Id of OSEKNM */
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
      /* Check if NM PDU is going out */
      if(NmTxWaitConfirm(LddLocalChannelId) == OSEKNM_FALSE)
      {
        LpDataPtr = (P2CONST(uint8, AUTOMATIC, OSEKNM_PRIVATE_CONST))nmUserDataPtr;
        /* Suspend all interrupts */
        SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
        /* Copy the data in user data array */
        /* polyspace +1 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
        NmTxPduUserData0(LddLocalChannelId) = *LpDataPtr;
        LpDataPtr++;
        NmTxPduUserData1(LddLocalChannelId) = *LpDataPtr;
        LpDataPtr++;
        NmTxPduUserData2(LddLocalChannelId) = *LpDataPtr;
        LpDataPtr++;
        NmTxPduUserData3(LddLocalChannelId) = *LpDataPtr;
        LpDataPtr++;
        NmTxPduUserData4(LddLocalChannelId) = *LpDataPtr;
        LpDataPtr++;
        NmTxPduUserData5(LddLocalChannelId) = *LpDataPtr;
				
        /* Resume all interrupts */
        SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
      }
      else
      {
        /* Set return value E_NOT_OK */
        LddReturnValue = E_NOT_OK;
      }
    }
    else
    {
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  return (LddReturnValue);
 }

#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
 * Function         : OsekNm_GetUserData
 *
 * Service ID       : 0x07
 *
 * Description      : Get user data out of the most recently received NM 
 *                    message.
 *
 * Re-entrancy      : Reentrant
 *
 * Input Parameters : nmChannelHandle
 *
 * Output Parameters: nmUserDataPtr, nmNodeIdPtr
 *
 * Return Parameter : Std_ReturnType
 *
 * Preconditions    : The OsekNm and the CanIf itself are initialized correctly.
 * 
 * Remarks          : Global Variable(s):
 *                    OsekNm_GblInitStatus, OsekNm_GaaInternalChannelMap,
 *                    OsekNm_GaaRxPduData
 *                    Function Invoked:
 *                    SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT(),
 *                    SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT(),
 *                    (void) Det_ReportError()
 ******************************************************************************/

#if (OSEKNM_USER_DATA_ENABLED == STD_ON) 

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_GetUserData
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
                     CONSTP2VAR(uint8, AUTOMATIC, OSEKNM_APPL_DATA) nmUserDataPtr)
{
  P2VAR(uint8, AUTOMATIC, OSEKNM_PRIVATE_DATA) LpSrcDataPtr;
  /* Return Type */
  Std_ReturnType LddReturnValue;   
  NetworkHandleType LddLocalChannelId;
  uint8 LucCount; 
  LddReturnValue = E_OK;

  #if(OSEKNM_DEV_ERROR_DETECT == STD_ON)
  LpSrcDataPtr = nmUserDataPtr;
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
    OSEKNM_GET_USERDATA_SID, OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
   LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
  
   if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
   {
     /* Report to DET */
     (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                           OSEKNM_GET_USERDATA_SID, OSEKE_INVALID_CHANNEL);
                    
     /* Set return value E_NOT_OK */
     LddReturnValue = E_NOT_OK;
   }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                             OSEKNM_GET_USERDATA_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }        
  /* Check if the pointer parameter is invalid */
  if((LpSrcDataPtr == NULL_PTR))
  { 
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, OSEKNM_GET_USERDATA_SID, 
    OSEKE_NULL_POINTER);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if no Development error occurred */
  if(LddReturnValue == E_OK)
  #endif
  {
    /* Get the Internal Channel Id of OSEKNM */
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
      LpSrcDataPtr = &(NmRxPduUserData0(LddLocalChannelId));
      LucCount = OSEKNM_ZERO;
      /* Suspend all interrupts */
      SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
           
      do
      {
        /* polyspace +2 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
        /* polyspace +1 MISRA-C3:18.4 [Not a defect: Justified] "Decrement and Increment operator is used to achieve better throughput" */
        *(nmUserDataPtr + (OsekNm_PtrSize)LucCount) = *LpSrcDataPtr;

        LpSrcDataPtr++;
        LucCount++;
      }while(LucCount < OSEKNM_USER_DATA_LENGTH);          
      
      /* Resume all interrupts */
      SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();

    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }
  }
  return (LddReturnValue);
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
 * Function         : OsekNm_GetNodeIdentifier
 *
 * Service ID       : 0x08
 *
 * Description      : Get node identifier out of the most recently received NM
 *                    message.
 *
 * Re-entrancy      : Reentrant
 *
 * Input Parameters : nmChannelHandle
 *
 * Output Parameters: nmNodeIdPtr
 *
 * Return Parameter : Std_ReturnType
 *
 * Preconditions    : The OsekNm and the CanIf itself are initialized correctly.
 * 
 * Remarks          : Global Variable(s):
 *                    OsekNm_GblInitStatus, OsekNm_GaaInternalChannelMap,
 *                    OsekNm_GaaRxPduData.
 *                    Function Invoked:
 *                    (void) Det_ReportError()
 *
 ******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC (Std_ReturnType, OSEKNM_CODE) OsekNm_GetNodeIdentifier
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
                       CONSTP2VAR(uint8, AUTOMATIC, OSEKNM_APPL_DATA) nmNodeIdPtr)
{
  #if(OSEKNM_DEV_ERROR_DETECT == STD_ON)
  P2VAR(uint8, AUTOMATIC, OSEKNM_PRIVATE_DATA) LpNodeIdPtr;
  #endif
  /* Return Type */
  Std_ReturnType LddReturnValue;
  NetworkHandleType LddLocalChannelId;
  LddReturnValue = E_OK;
  #if(OSEKNM_DEV_ERROR_DETECT == STD_ON)
  LpNodeIdPtr = nmNodeIdPtr;
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                                OSEKNM_GET_NODEIDENTIFIER_SID, OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
     {
       /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                        OSEKNM_GET_NODEIDENTIFIER_SID, OSEKE_INVALID_CHANNEL);
                    
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                       OSEKNM_GET_NODEIDENTIFIER_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }         
  /* Check if the pointer parameter is invalid */
  if(LpNodeIdPtr == NULL_PTR)
  { 
     /* Report to DET */
     (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                         OSEKNM_GET_NODEIDENTIFIER_SID, OSEKE_NULL_POINTER);
     /* Set return value E_NOT_OK */
     LddReturnValue = E_NOT_OK;
  }
  /* Check if no Development error occurred */
  if(LddReturnValue == E_OK)
  #endif
  {
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      /* Get the Internal Channel Id of OSEKNM */
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle]; 
      /* Update the nmNodeIdPtr */    
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */			
      *nmNodeIdPtr = (uint8)NmRxPduDestAddr(LddLocalChannelId);
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }  
  }   
  return (LddReturnValue);
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
 * Function         : OsekNm_GetLocalNodeIdentifier
 *
 * Service ID       : 0x09
 *
 * Description      : Get node identifier out of the most recently received NM 
 *                    message.
 *
 * Re-entrancy      : Reentrant
 *
 * Input Parameters : nmChannelHandle
 *
 * Output Parameters: nmNodeIdPtr
 *
 * Return Parameter : Std_ReturnType
 *
 * Preconditions    : The OsekNm and the CanIf itself are initialized correctly.
 * 
 * Remarks          : Global Variable(s):
 *                    OsekNm_GblInitStatus, OsekNm_GaaInternalChannelMap. 
 *                    Function Invoked:
 *                    (void) Det_ReportError()
 *
 ******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_GetLocalNodeIdentifier
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
                       CONSTP2VAR(uint8, AUTOMATIC, OSEKNM_APPL_DATA) nmNodeIdPtr)
{
  
  #if(OSEKNM_DEV_ERROR_DETECT == STD_ON)
  P2VAR(uint8, AUTOMATIC, OSEKNM_PRIVATE_DATA) LpNodeIdPtr;
  #endif
  /* Return Type */
  Std_ReturnType LddReturnValue; 
  NetworkHandleType LddLocalChannelId;
  LddReturnValue = E_OK;

  #if(OSEKNM_DEV_ERROR_DETECT == STD_ON)
   LpNodeIdPtr = nmNodeIdPtr;
   /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                            OSEKNM_GET_LOCALNODEIDENTIFIER_SID, OSEKE_NO_INIT);
     /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                      OSEKNM_GET_LOCALNODEIDENTIFIER_SID, OSEKE_INVALID_CHANNEL);
                          
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                  OSEKNM_GET_LOCALNODEIDENTIFIER_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }         
  /* Check if the pointer parameter is invalid */
  if(LpNodeIdPtr == NULL_PTR)
  { 
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                    OSEKNM_GET_LOCALNODEIDENTIFIER_SID, OSEKE_NULL_POINTER);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if no Development error occurred */
  if(LddReturnValue == E_OK)
  #endif
  {
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)    /* Get the Internal Channel Id of OSEKNM */
    {
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
      /* Update the nmNodeIdPtr */     
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
      *nmNodeIdPtr = OsekNm_GaaChannelConfig[LddLocalChannelId].ucNodeId;
    }
  }   
  return (LddReturnValue);
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
 * Function         : OsekNm_GetVersionInfo
 *
 * Service ID       : 0xF1
 *
 * Description      : This service returns the version information of the
 *                    module.
 *
 * Re-entrancy      : Reentrant
 *
 * Input Parameters : None
 *
 * Output Parameters: versionInfo
 *
 * Return Parameter : void
 *
 * Preconditions    : None.
 * 
 * Remarks          : Global Variable(s):
 *                    None
 *                    Function Invoked: 
 *                    (void) Det_ReportError()
 *
 ******************************************************************************/
#if(OSEKNM_VERSION_INFO_API == STD_ON)

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, OSEKNM_CODE) OsekNm_GetVersionInfo
             (P2VAR(Std_VersionInfoType, AUTOMATIC, OSEKNM_APPL_DATA) versionInfo)
{
  #if(OSEKNM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether Version Information is equal to Null Ptr */
  if(versionInfo == NULL_PTR)
  {
    /* Report to DET  */
    (void) Det_ReportError(OSEKNM_MODULE_ID, OSEKNM_ZERO, OSEKNM_GET_VERSIONINFO_SID,
                                                       OSEKE_NULL_POINTER);
  }
  else
  #endif
  {
    /* Copy the vendor Id */
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
    versionInfo->vendorID = OSEKNM_VENDOR_ID;
    /* Copy the module Id */
    versionInfo->moduleID = OSEKNM_MODULE_ID;
    /* Copy Software Major Version */
    versionInfo->sw_major_version = OSEKNM_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versionInfo->sw_minor_version = OSEKNM_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versionInfo->sw_patch_version = OSEKNM_SW_PATCH_VERSION;
  }
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
 * Function         : OsekNm_GetPduData
 *
 * Service ID       : 0x15
 *
 * Description      : Get the whole PDU data out of the most recently received
 *                    NM message.
 *
 * Re-entrancy      : Reentrant
 *
 * Input Parameters : nmChannelHandle
 *
 * Output Parameters: nmPduDataPtr
 *
 * Return Parameter : Std_ReturnType
 *
 * Preconditions    : The OsekNm and the CanIf itself are initialized correctly.
 * 
 * Remarks          : Global Variable(s):
 *                    OsekNm_GblInitStatus, OsekNm_GaaInternalChannelMap,
 *                    OsekNm_GaaRxPduData
 *                    Function Invoked: 
 *                    (void) Det_ReportError(), 
 *                    SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT(),
 *                    SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT() 
 ******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_GetPduData
                  (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
                      CONSTP2VAR(uint8, AUTOMATIC, OSEKNM_APPL_DATA) nmPduDataPtr)
{
  P2VAR(uint8, AUTOMATIC, OSEKNM_PRIVATE_DATA) LpSrcDataPtr;
  /* Return Type */
  Std_ReturnType LddReturnValue;
  NetworkHandleType LddLocalChannelId;
  uint8 LucCount;
  LddReturnValue = E_OK;

  #if(OSEKNM_DEV_ERROR_DETECT == STD_ON)
  LpSrcDataPtr = nmPduDataPtr;
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                                         OSEKNM_GET_PDUDATA_SID, OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                                 OSEKNM_GET_PDUDATA_SID, OSEKE_INVALID_CHANNEL);
                        
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                             OSEKNM_GET_PDUDATA_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }         
  /* Check if the pointer parameter is invalid */
  if(LpSrcDataPtr == NULL_PTR) 
  { 
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                                OSEKNM_GET_PDUDATA_SID, OSEKE_NULL_POINTER);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if no Development error occurred */
  if(LddReturnValue == E_OK)
  #endif
  {
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      /* Get the Internal Channel Id of OSEKNM */
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
      LucCount = OSEKNM_ZERO;
      LpSrcDataPtr = NmRxPduDataPtr(LddLocalChannelId);
      /* Suspend all interrupts */
      SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
          
      do
      {
        /* polyspace +2 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
        /* polyspace +1 MISRA-C3:18.4 [Not a defect: Justified] "Decrement and Increment operator is used to achieve better throughput" */
        *(nmPduDataPtr + (OsekNm_PtrSize)LucCount) = *LpSrcDataPtr;

        LpSrcDataPtr++;
        LucCount++;
      }while(LucCount < OSEKNM_NM_PDU_LENGTH);    
      
      /* Resume all interrupts */
      SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }
  }
  return (LddReturnValue);
}
 
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h" 			

/*******************************************************************************
** Function Name        : OsekNm_PassiveStartUp                               **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Starts the AUTOSAR OsekNm state machine from the    **
**                        Bus-Sleep Mode and triggers the transition to the   **
**                        Network Mode.                                       **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : OsekNm Module should be initialized.                **
**                                                                            **
** Remarks              : Global Variable(s)     : OsekNm_GblInitStatus,      **
**                        OsekNm_GaaCurrentMode, OsekNm_GaaStateTvalue        **
**                                                                            **
**                        Function(s) invoked    : (void) Det_ReportError(),  **
**                        Nm_NetworkMode()                                    **
*******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_PassiveStartUp
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle)
{
  /* Return Type */
  Std_ReturnType LddReturnValue;
  NetworkHandleType  LddLocalChannelId;
  P2CONST(Tdd_OsekNm_ChannelConfig, AUTOMATIC, OSEKNM_APPL_CONST) LpChannelPtr;
  LddReturnValue = E_OK;

  #if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, OSEKNM_PASSIVE_STARTUP_SID,
                                                                 OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                             OSEKNM_PASSIVE_STARTUP_SID, OSEKE_INVALID_CHANNEL);
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                          OSEKNM_PASSIVE_STARTUP_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }               
  /* Check if no Development error is occurred */
  if(LddReturnValue == E_OK)
  #endif /* OSEKNM_DEV_ERROR_DETECT */
  {
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
      LpChannelPtr = &OsekNm_GaaChannelConfig[LddLocalChannelId];
      /* Allow OsekNm start if current mode is in Bus sleep mode */
      if(OsekNm_GaaCurrentMode[LddLocalChannelId] == OSEKNM_MODE_BUS_SLEEP)
      {
        /* Initialize Mode to Network mode */
        OsekNm_GaaCurrentMode[LddLocalChannelId] = OSEKNM_MODE_AWAKE;
        /* Initialize Status to RESET */
        OsekNm_GaaCurrentState[LddLocalChannelId] = OSEKNM_STATE_RESET;
        /* reset logical successor to myself */
        OsekNm_GaaLogicalSuccessor[LddLocalChannelId] = LpChannelPtr->ucNodeId;        
        /* Notify the upper layer */
        Nm_NetworkMode(LpChannelPtr->ddNmChannelId);
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }
   
  } /* No development errors occurred */

 return (LddReturnValue);

}

#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : OsekNm_NetworkRequest                                  **
**                                                                            **
** Service ID           : N/A                                                **
**                                                                            **
** Description          : Request the network, since ECU needs to communicate **
**                        on the bus.Network state shall be changed to        **
**                       'requested'.                                         **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same channel)             **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                       **
**                                                                            **
** Preconditions        : OsekNm Module should be initialized.                  **
**                                                                            **
** Remarks              : Global Variable(s)     : OsekNm_GblInitStatus,         **
**                        OsekNm_GaaCurrentNetworkState,                         **
**                                                                            **
**                        Function(s) invoked    : (void) Det_ReportError(),         **
*******************************************************************************/

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_NetworkRequest
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle)
{
  /* Return Type */
  Std_ReturnType LddReturnValue;
  NetworkHandleType LddLocalChannelId;

  LddReturnValue = E_OK;

  #if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, OSEKNM_NETWORK_REQUEST_SID,
                                                                 OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];    
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                             OSEKNM_NETWORK_REQUEST_SID, OSEKE_INVALID_CHANNEL);
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                          OSEKNM_NETWORK_REQUEST_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }        
  /* Check if no Development error is occurred */
  if(LddReturnValue == E_OK)
  #endif /* OSEKNM_DEV_ERROR_DETECT */
  {      
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];  

      /* Network state initialized to requested */
      OsekNm_GaaCurrentNetworkState[LddLocalChannelId] = OSEKNM_REQUESTED;
      /* TX ON */
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }
  } /*No Development errors occurred */

  return (LddReturnValue);      
}

#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"



/*******************************************************************************
** Function Name        : OsekNm_NetworkRelease                                  **
**                                                                            **
** Service ID           : N/A                                                **
**                                                                            **
** Description          : Release the network, since ECU doesn't have to      **
**                        communicate on the bus.Network state shall be       **
**                        changed to 'released'.                              **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same channel)             **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : OsekNm Module should be initiaized.                 **
**                                                                            **
** Remarks              : Global Variable(s)     : OsekNm_GblInitStatus,      **
**                        OsekNm_GaaCurrentMode,                              **
**                        OsekNm_GaaCurrentNetworkState,                      **
**                        OsekNm_GaaCurrentState                              **
**                                                                            **
**                        Function(s) invoked    : (void) Det_ReportError(),  **
*******************************************************************************/

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_NetworkRelease
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle)
{

  /* Return Type */
  Std_ReturnType LddReturnValue;  
  NetworkHandleType LddLocalChannelId;   
  LddReturnValue = E_OK;
	
  #if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, OSEKNM_NETWORK_RELEASE_SID,
                                                                 OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                             OSEKNM_NETWORK_RELEASE_SID, OSEKE_INVALID_CHANNEL);
                        
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                          OSEKNM_NETWORK_RELEASE_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }   
  /* Check if no Development error is occurred */
  if(LddReturnValue == E_OK)
  #endif /* OSEKNM_DEV_ERROR_DETECT */
  {
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
      /* Currently network is released */
      OsekNm_GaaCurrentNetworkState[LddLocalChannelId] = OSEKNM_RELEASED;      
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }    
	
  } /* No development errors occured */
       
  return (LddReturnValue);
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : OsekNm_GetState                                     **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : This service returns the current state and mode of  **
**                        the network management.                             **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : nmStatePtr, nmModePtr                               **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : OsekNm Module should be initiaized.                 **
**                                                                            **
** Remarks              : Global Variable(s)     : OsekNm_GblInitStatus,      **
**                        OsekNm_GaaCurrentState, OsekNm_GaaCurrentMode       **
**                                                                            **
**                        Function(s) invoked    : (void) Det_ReportError()   **
*******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_GetState
   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
   CONSTP2VAR(Nm_StateType, AUTOMATIC, OSEKNM_APPL_DATA) nmStatePtr,
   CONSTP2VAR(Nm_ModeType, AUTOMATIC, OSEKNM_APPL_DATA) nmModePtr)
{

   /* Return Type */
  Std_ReturnType LddReturnValue;
  NetworkHandleType LddLocalChannelId;
  LddReturnValue = E_OK;

  #if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                                               OSEKNM_GET_STATE_SID, OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                                       OSEKNM_GET_STATE_SID, OSEKE_INVALID_CHANNEL);                      
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                             OSEKNM_GET_STATE_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }         
 
  /* Check if the pointer parameter is invalid */
  if((nmStatePtr == NULL_PTR) || (nmModePtr == NULL_PTR))
  { 
     /* Report to DET */
     (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                                         OSEKNM_GET_STATE_SID, OSEKE_NULL_POINTER);
     /* Set return value E_NOT_OK */
     LddReturnValue = E_NOT_OK;
  }
  /* Check if no Development error is occurred */
  if(LddReturnValue == E_OK)
  #endif
  {
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
			
      /* Copy the current OsekNm state and mode to output parameters */   
      switch(OsekNm_GaaCurrentState[LddLocalChannelId])
      {
        case OSEKNM_STATE_UNINIT:
         *nmStatePtr = NM_STATE_UNINIT;
        break;
        case OSEKNM_STATE_RESET:
          *nmStatePtr = NM_STATE_REPEAT_MESSAGE;
        break;
        case OSEKNM_STATE_NORMAL:
        case OSEKNM_STATE_LIMPHOME:
          if(OSEKNM_MODE_AWAKE == OsekNm_GaaCurrentMode[LddLocalChannelId])
          {
            *nmStatePtr = NM_STATE_NORMAL_OPERATION;
          }
          else if(OSEKNM_MODE_WAIT_SLEEP == OsekNm_GaaCurrentMode[LddLocalChannelId])
          {
            *nmStatePtr = NM_STATE_PREPARE_BUS_SLEEP;
          }
          else if(OSEKNM_MODE_BUS_SLEEP == OsekNm_GaaCurrentMode[LddLocalChannelId])
          {
            *nmStatePtr = NM_STATE_BUS_SLEEP;
          }
          else
          {
            *nmStatePtr = NM_STATE_READY_SLEEP;
          }
        break;
        
        default:
          /* Do Nothing */
          break;

      }

      if(OSEKNM_MODE_AWAKE == OsekNm_GaaCurrentMode[LddLocalChannelId])
      {
        *nmModePtr = NM_MODE_NETWORK;
      }
      else if(OSEKNM_MODE_WAIT_SLEEP == OsekNm_GaaCurrentMode[LddLocalChannelId])
      {
        *nmModePtr = NM_MODE_PREPARE_BUS_SLEEP;
      }
      else if(OSEKNM_MODE_BUS_SLEEP == OsekNm_GaaCurrentMode[LddLocalChannelId])
      {
        *nmModePtr = NM_MODE_BUS_SLEEP;
      }
      else if(OSEKNM_MODE_PREPARE_SLEEP == OsekNm_GaaCurrentMode[LddLocalChannelId])
      {
        *nmModePtr = NM_MODE_NETWORK;
      }
      else
      {
        *nmModePtr = NM_MODE_NETWORK;
      }
	  }
	  else
	  {
	    LddReturnValue = E_NOT_OK;
	  }
  }
   
  return (LddReturnValue);
}
 
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h" 


/*******************************************************************************
** Function Name        : OsekNm_RequestBusSynchronization                    **
**                                                                            **
** Service ID           : 0xC0                                                **
**                                                                            **
** Description          : Request Bus Synchronization.                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : OsekNm Module should be initialized.                 **
**                                                                            **
** Remarks              : Global Variable(s)     : OsekNm_GblInitStatus,      **
**                        OsekNm_GaaCurrentMode                               **
**                                                                            **
**                        Function(s) invoked    : (void) Det_ReportError(),         **
**                        OsekNm_TriggerTransmission()                        **
*******************************************************************************/
#if(OSEKNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON)

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_RequestBusSynchronization
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle)
{
  /* Not available for OSEK Nm */
  return (E_NOT_OK);
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
** Function Name        : OsekNm_CheckRemoteSleepIndication                   **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Check if remote sleep indication takes place or not.**
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same NM-Channel)          **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : nmRemoteSleepIndPtr                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : OsekNm Module should be initialized.                **
**                                                                            **
** Remarks              : Global Variable(s)     : OsekNm_GblInitStatus,      **
**                        OsekNm_GunRxFlagStatus                              **
**                                                                            **
**                        Function(s) invoked    : (void) Det_ReportError()          **
*******************************************************************************/
#if(OSEKNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_CheckRemoteSleepIndication
              (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
              CONSTP2VAR(boolean, AUTOMATIC, OSEKNM_APPL_DATA) nmRemoteSleepIndPtr)
{
  /* Return Type */
  Std_ReturnType LddReturnValue;
  NetworkHandleType LddLocalChannelId = 0;
  LddReturnValue = E_OK;

  #if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                             OSEKNM_CHECK_REMOTESLEEPINDICATION_SID, OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                     OSEKNM_CHECK_REMOTESLEEPINDICATION_SID, OSEKE_INVALID_CHANNEL);                    
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
              OSEKNM_CHECK_REMOTESLEEPINDICATION_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }                 
  /* Check if the pointer parameter is invalid */
  if(nmRemoteSleepIndPtr == NULL_PTR) 
  { 
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                        OSEKNM_CHECK_REMOTESLEEPINDICATION_SID, OSEKE_NULL_POINTER);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if no Development error is occurred */
  if(LddReturnValue != E_NOT_OK)
  #endif
  {
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];    
      if(OSEKNM_MODE_AWAKE == OsekNm_GaaCurrentMode[LddLocalChannelId])
      {
        *nmRemoteSleepIndPtr = NmRxRmtSleepIndNotif(LddLocalChannelId);
      }
    }
    else
    {
      LddReturnValue = E_OK;
    }
  } /* No Development errors occured */
  return (LddReturnValue);
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"

#endif



/*******************************************************************************
** Function Name        : OsekNm_DisableCommunication                         **
**                                                                            **
** Service ID           : 0x0C                                                **
**                                                                            **
** Description          : Disable the NM PDU transmission ability.            **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same NM-Channel)          **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : OsekNm Module should be initiaized.                 **
**                                                                            **
** Remarks              : Global Variable(s)     : OsekNm_GblInitStatus,      **
**                        OsekNm_GaaCurrentState,                             **
**                        OsekNm_GaaCurrentNetworkState,                      **
**                        OsekNm_GaaStateTvalue                               **
**                                                                            **
**                        Function(s) invoked    : (void) Det_ReportError(),         **
**                        OsekNm_StopTransmission()                           **
*******************************************************************************/
#if(OSEKNM_COM_CONTROL_ENABLED == STD_ON)

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_DisableCommunication
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle)
{
  /* Return Type */
  Std_ReturnType LddReturnValue;
  NetworkHandleType LddLocalChannelId;
  LddReturnValue = E_OK;

  #if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                                 OSEKNM_DISABLE_COMMUNICATION_SID, OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                           OSEKNM_DISABLE_COMMUNICATION_SID, OSEKE_INVALID_CHANNEL);
                        
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                    OSEKNM_DISABLE_COMMUNICATION_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }              
   /* Check if no Development error is occurred */
  if(LddReturnValue == E_OK)
  #endif
  {
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
      /* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      if(LddLocalChannelId != OSEKNM_INACTIVE_CHANNEL)
      {
        OsekNm_GaaComControlArray[LddLocalChannelId] = OSEKNM_DISABLED;
      }
      /* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      else
      {
        LddReturnValue = E_NOT_OK;  
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }
  }
  return (LddReturnValue);
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"	

#endif

/*******************************************************************************
** Function Name        : OsekNm_EnableCommunication                          **
**                                                                            **
** Service ID           : 0x0D                                                **
**                                                                            **
** Description          : Enable the NM PDU transmission ability.             **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same NM-Channel)          **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : OsekNm Module should be initiaized.                 **
**                                                                            **
** Remarks              : Global Variable(s)     : OsekNm_GblInitStatus,      **
**                        OsekNm_GaaCurrentState, OsekNm_GaaStateTvalue       **
**                                                                            **
**                        Function(s) invoked    : (void) Det_ReportError(),  **
**                        OsekNm_StartTransmission()                          **
*******************************************************************************/
#if(OSEKNM_COM_CONTROL_ENABLED == STD_ON)

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_EnableCommunication
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle)
{
  /* Return Type */
  Std_ReturnType LddReturnValue;
  NetworkHandleType LddLocalChannelId;
  LddReturnValue = E_OK;    
    
  #if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                                    OSEKNM_ENABLE_COMMUNICATION_SID, OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                            OSEKNM_ENABLE_COMMUNICATION_SID, OSEKE_INVALID_CHANNEL);
                        
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                     OSEKNM_ENABLE_COMMUNICATION_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }                     
  /* Check if no Development error is occurred */
  if(LddReturnValue == E_OK)
  #endif
  {
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
      /* check if disablecommunication is invoked*/	
  	  if(OsekNm_GaaComControlArray[LddLocalChannelId] == OSEKNM_DISABLED)
  	  {
        OsekNm_GaaComControlArray[LddLocalChannelId] = OSEKNM_ENABLED;
        if((OsekNm_GaaCurrentMode[LddLocalChannelId] != OSEKNM_MODE_BUS_SLEEP) && 
          (OsekNm_GaaCurrentMode[LddLocalChannelId] != OSEKNM_MODE_WAIT_SLEEP))
          {
		    SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
            /* Set time as 0 to transmit NM message immediately */
            OsekNm_GaaTimer[LddLocalChannelId] = OSEKNM_ZERO;
			/* Perform mode and state transition */
		    OsekNm_ModeProcessing(LddLocalChannelId);
		    /* Resume all interrupts */
		    SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
          }
  	  }
  	  else
  	  {
  	    LddReturnValue = E_NOT_OK;
  	  }
  	}
  	else
  	{
  	  LddReturnValue = E_NOT_OK;
  	}  
	} /* No development errors occured */ 
  
  return (LddReturnValue); 
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"	

#endif	

/*******************************************************************************
** Function Name        : OsekNm_RepeatMessageRequest                            **
**                                                                            **
** Service ID           : N/A                                                **
**                                                                            **
** Description          : For compatibility with AUTOSAR Nm                  **
**                                                                            **
** Re-entrancy          : Reentrant(but not for the same NM-Channel)          **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                       **
**                                                                            **
** Preconditions        : OsekNm Module should be initiaized.                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
*******************************************************************************/

#define OSEKNM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_RepeatMessageRequest
                   (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle)
{

  OSEKNM_UNUSED(nmChannelHandle);

  /* Not available for OSEK Nm */
  return E_NOT_OK;
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"	
/*******************************************************************************
** Function Name        : OsekNm_MainFunction                                 **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Perform cyclic jobs for OsekNm                      **
**                                                                            **
** Re-entrancy          : No Reentrant                                        **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : OsekNm Module should be initiaized.                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Function(s) invoked :                               **
**                         SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT(),    **
**                         SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT        **
*******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, OSEKNM_CODE) OsekNm_MainFunction(void)
{
  uint8 luc_channel;
  
  for(luc_channel = OSEKNM_ZERO;luc_channel < OSEKNM_NUMBER_OF_CHANNELS;
    luc_channel++)
  {
    /* Suspend all interrupts */
    SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
	  /* Perform mode and state transition */
    OsekNm_ModeProcessing(luc_channel);
    /* Resume all interrupts */
    SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
  }
}

#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"	

/*******************************************************************************
** Function Name        : OsekNm_GetConfiguration                             **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Provide current network configuration               **
**                                                                            **
** Re-entrancy          : No Reentrant                                        **
**                                                                            **
** Input Parameters     : nmChannelHandle                                     **
**                                                                            **
** Output Parameters    : NwConfigPtr                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : OsekNm Module should be initiaized.                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                         OsekNm_GaaInternalChannelMap, OsekNm_GaaChannelConfig  **
**                         OsekNm_GaaNetworkConfig                            **
**                        Function(s) invoked :                               **
**                         SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT(),    **
**                         SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT        **
*******************************************************************************/
#define OSEKNM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, OSEKNM_CODE) OsekNm_GetConfiguration
 (CONST(NetworkHandleType, OSEKNM_APPL_CONST) nmChannelHandle,
 CONSTP2VAR(NetworkConfigurationType, AUTOMATIC, OSEKNM_APPL_DATA) NwConfigPtr)
{
  /* Return Type */
  uint8 LucCount;
  Std_ReturnType LddReturnValue;
  NetworkHandleType LddLocalChannelId;
  LddReturnValue = E_OK; 
    
  #if (OSEKNM_DEV_ERROR_DETECT == STD_ON)
  /* Check if OsekNm is initialized */
  if(OsekNm_GblInitStatus != OSEKNM_TRUE)
  {
    /* Report to DET */
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                                    OSEKNM_GET_CONFIGURATION_SID, OSEKE_NO_INIT);
    /* Set return value E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }
  /* Check if the channel number is valid */
  if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
  {
    LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
    if(LddLocalChannelId == OSEKNM_INACTIVE_CHANNEL)
    {
      /* Report to DET */
      (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle,
                            OSEKNM_GET_CONFIGURATION_SID, OSEKE_INVALID_CHANNEL);
                        
      /* Set return value E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
  }
  else
  {
    (void) Det_ReportError (OSEKNM_MODULE_ID, nmChannelHandle, 
                     OSEKNM_GET_CONFIGURATION_SID, OSEKE_INVALID_NM_CHANNEL);
    LddReturnValue = E_NOT_OK;
  }                 
  /* Check if no Development error is occurred */
  if(LddReturnValue == E_OK)
  #endif
  {
    if(nmChannelHandle <= OSEKNM_MAX_NM_CHANNEL_ID)
    {
      LddLocalChannelId = OsekNm_GaaInternalChannelMap[nmChannelHandle];
      /* Assign Local Channel pointer channel Config Structure */
      if(NwConfigPtr != NULL_PTR)
      {
        /* Suspend all interrupts */
        SchM_Enter_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
        for(LucCount = OSEKNM_ZERO;LucCount < OSEKNM_NWCFG_ARRAY_SIZE; 
                                                                   LucCount++)
        {
          /* polyspace +2 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
          /* polyspace +1 MISRA-C3:18.4 [Not a defect: Justified] "Decrement and Increment operator is used to achieve better throughput" */
          *(NwConfigPtr + (OsekNm_PtrSize)LucCount) =
          OsekNm_GaaNetworkConfig[(LddLocalChannelId*OSEKNM_NWCFG_ARRAY_SIZE) 
                                                                  + LucCount];
        }
        /* Resume all interrupts */
        SchM_Exit_OsekNm_OSEKNM_BLOCK_ALL_INTERRUPT();
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }
  }
  return LddReturnValue;
}
#define OSEKNM_STOP_SEC_CODE
#include "MemMap.h"	
/* polyspace:end <RTE:UNR:Not a defect:Low> The code will be reachable in diffrent configuration */
/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
