/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DspMemoryServices.c                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for UDS services           **
**              implemented by DSP layer of Dcm module                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                 Description                     **
********************************************************************************
** 2.3.8.0   26-04-2021    S.K     Park      #27996                           **
**                                                                            **
** 2.3.7.0   08-04-2021    EunKyung.Kim      #29178                           **
**                                                                            **
** 2.3.5.0   16-02-2021    EunKyung.Kim      #28368                           **
**                                                                            **
** 2.3.4.0   28-Jan-2021   EunKyung Kim      #27909                           **
**                                                                            **
** 1.0.6     05-11-2020    EunKyung Kim      #26432                           **
**                                                                            **
** 1.0.5     20-03-2020    EunKyung Kim      #21905, #22523                   **
**                                                                            **
** 1.0.4     23-07-2019    Y.S     Jeon      #17172                           **
**                                                                            **
** 1.0.3     12-06-2017    Jin     Jung       #5428                           **
**                                                                            **
** 1.0.2     03-03-2016    Sungeol Baek       #3754                           **
**                                                                            **
** 1.0.1     16-04-2015    Sungeol Baek       #2171                           **
**                                                                            **
** 1.0.0     09-01-2013    Autron             Initial version                 **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DslInternal.h"
#include "Dcm_CallOuts.h"
#include "Dcm_DspMemoryServices.h"
#include "Dcm_Config.h"

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard-Chap 5.1.2)
*/
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
** Function Name        : Dcm_DcmReadMemoryByAddress                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : ReadMemoryByAddress service is used to get data     **
**                        from requested memory address.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : none                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : none                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_ServiceForcePendingStatus                       **
**                        Dcm_GddOpStatus , Dcm_GddNegRespError               **
**                        Dcm_GusMaxNoOfForceRespPend,Dcm_GaaReadMemRngConfig **
**                        Dcm_GaaAddressAndLengthFormatIds ,                  **
**                        Dcm_GulRMBAMemoryAddress, Dcm_GaaModeRuleConfig     **
**                        Function(s) invoked :                               **
**                        Dcm_DsdValidateSecurity, Dcm_DsdModeRuleCheck ,     **
**                        Dcm_DcmReadMemoryCall, Dcm_ExternalSetNegResponse , **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadMemoryByAddress(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  uint32 LulMemoryAddress;
  uint32 LulMemorySize;
  uint8 LucMemoryIdentifier;
  uint8 LucAddrLenForId = (uint8)0x00;
  uint8 LucMemAdrBytes;
  uint8 LucMemSizeBytes;
  uint8 LucLoopVar;
  boolean LblSearchResult;
  boolean LblItemFound;
  boolean LblReadMemoryApiInvoked;

  /* Set Force pending status flag to False */
  Dcm_ServiceForcePendingStatus.ucReadMemForcePendingStatus =
    DCM_FALSE;
  /* Initialize global variables */
  Dcm_GddOpStatus = DCM_INITIAL;
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
  /* Initialize local variables */
  LulMemoryAddress = DCM_ZERO;
  LulMemorySize = DCM_ZERO;
  LblReadMemoryApiInvoked = DCM_FALSE;
  LblItemFound = DCM_FALSE;

  if (
    (pMsgContext == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR)
  )
  {
    /* TODO : Det Error */
  }
  else
  {
    /* Get data from request */
    LpReqResData = pMsgContext->reqData;

    /*Get the addressAndLengthFormatIdentifier from the request*/
    LucAddrLenForId = pMsgContext->reqData[0];
    
    /* Get memory address and size bytes from AddressAndLengthFormatIdentifier */
    LucMemAdrBytes = (LucAddrLenForId & DCM_SIG_BYTE_MASK_VALUE);
    LucMemSizeBytes = ((LucAddrLenForId & DCM_SIG_SIZE_MASK_VALUE) >> DCM_FOUR);

    #if(DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG != DCM_ZERO)
    /* Check for configured Address and length format identifier */
    for(
      LucLoopVar = DCM_ZERO;
      LucLoopVar < Dcm_Num_Of_Address_Length_Format_ID_Config; 
      LucLoopVar++)
    {
      if(LucAddrLenForId == Dcm_GaaAddressAndLengthFormatIds[LucLoopVar])
      {
        LblItemFound = DCM_TRUE;
        break;
      }
    }
    #else
    LblItemFound = DCM_TRUE;
    #endif

    /*Check addressAndLengthFormatIdentifier is valid*/
    if(LblItemFound == DCM_TRUE)
    {
      /* Check Requested Data length is valid or not */
      if(pMsgContext->reqDataLen ==
        (uint32)((uint32)LucMemAdrBytes + (uint32)LucMemSizeBytes + (uint32)0x01))
      {
        LucLoopVar = DCM_ZERO;
        /* Get Memory address from request */
        do
        {         
          LulMemoryAddress = LulMemoryAddress << DCM_EIGHT;
          LpReqResData = &LpReqResData[1u];
  
          LulMemoryAddress |= *(LpReqResData);
          LucLoopVar++;
        }
        while(LucLoopVar < LucMemAdrBytes);

        LucLoopVar = DCM_ZERO;
      
        /*Get memory size from the request*/
        do
        {

          LulMemorySize = LulMemorySize << DCM_EIGHT;
          LpReqResData = &LpReqResData[1u];       
          LulMemorySize |= *(LpReqResData);            

          LucLoopVar++;
        }
        while(LucLoopVar < LucMemSizeBytes);

        /* Variable To break The Loop*/
        LblItemFound = DCM_FALSE;

        /* Check Current memory is within memory Range Configures */
        for(LucLoopVar = 0U; LucLoopVar < Dcm_Total_Num_Read_Memory_Configured; LucLoopVar++)
        {
          /* polyspace +2 MISRA-C3:10.6 [Justified:Low] "Not a defect" */
          Dcm_uint64 reqHighAddr = (LulMemoryAddress + (uint32)LulMemorySize) - 1U;
          Dcm_uint64 reqLowAddr = LulMemoryAddress;
          if ((reqLowAddr  >= Dcm_GaaReadMemRngConfig[LucLoopVar].ulReadMemRngLow) &&
              (reqHighAddr <= Dcm_GaaReadMemRngConfig[LucLoopVar].ulReadMemRngHigh))
          {
            LblItemFound = DCM_TRUE;
            break;
          }
        }

        if(LblItemFound == DCM_TRUE)
        {
          if(LucMemSizeBytes == DCM_ONE)
          {
            /* check memory size is valid or not */
			/* LulMemorySize+SID should be euqal to or less than pMsgContext->resMaxDataLen  */
            if(((LulMemorySize+1) > pMsgContext->resMaxDataLen) || (LulMemorySize < DCM_ONE))
            {
              /* set NRC RequestOutOfRange */
              Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
              LblItemFound = DCM_FALSE;
            }
            else
            {
              /* Do Nothing */
            }
          }

          if(DCM_TRUE == LblItemFound)
          {
            /* Get configured Memory range */
            if(Dcm_GaaReadMemRngConfig[LucLoopVar].pReadMemRngSec != NULL_PTR)
            {
              /* Invoke function for security validation */
              LblSearchResult = Dcm_DsdValidateSecurity(
                Dcm_GaaReadMemRngConfig[LucLoopVar].pReadMemRngSec, 
                Dcm_GaaReadMemRngConfig[LucLoopVar].ucReadMemSecCount);
            }
            else
            {
              LblSearchResult = DCM_TRUE;
            }

            /* Check is the current Security level supported by the service Id */
            if(LblSearchResult == DCM_TRUE)
            {
              #if(DCM_MODE_RULE == STD_ON)
              if(Dcm_GaaReadMemRngConfig[LucLoopVar].blModeRuleConfigured == DCM_TRUE)
              {
                LblSearchResult = Dcm_DsdModeRuleCheck
                  (Dcm_GaaReadMemRngConfig[LucLoopVar].ucDIDmoderuleArrayindex);
              }

              if(LblSearchResult != DCM_TRUE)
              {
                #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
                Dcm_GddNegRespError = 
                  Dcm_GaaModeRuleConfig[Dcm_GaaReadMemRngConfig[LucLoopVar].ucDIDmoderuleArrayindex].ucNRCType;
                #else
                Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
                #endif              
              }
              else
              #endif              
              {
                if(Dcm_GaaReadMemRngConfig[LucLoopVar].blUseMemoryValue == DCM_TRUE)
                {
                  /* Get configured memory identifier */
                  LucMemoryIdentifier = Dcm_GaaReadMemRngConfig[LucLoopVar].ucReadMemoryIdentifier;
                }
                else
                {
                  /* Get configured memory identifier */
                  LucMemoryIdentifier = DCM_ZERO;
                }
                /* Update Dcm_GulRMBAMemoryAddress */
                Dcm_GulRMBAMemoryAddress = LulMemoryAddress;
                /* Update Dcm_GusRMBAMemorySize */
                Dcm_GulRMBAMemorySize = LulMemorySize;
                /* Update Dcm_GucRMBAMemoryIdentifier */
                Dcm_GucRMBAMemoryIdentifier = LucMemoryIdentifier;
                LblReadMemoryApiInvoked = DCM_TRUE;
                /* Call to Dcm_ReadMemory() to get the data record */
                Dcm_DcmReadMemoryCall(pMsgContext);
              }
            }
            else
            {
              /* Report the Security Access Denied  NRC */
              Dcm_GddNegRespError = DCM_E_SECURITYACCESSDENIED;
            }
          }
          else
          {
            /* Do Nothing */
          }
        }
        else
        {
          /* Report the Request out of range NRC Because Memory Address
            Not With in Specified Memory Range */
          Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
        }
      }
      else
      {
        /* Report the Incorrect message length NRC */
        Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }
    }
    else
    {
      /* Report the Request out of range NRC Because of Wrong ALFID */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    if(LblReadMemoryApiInvoked == DCM_FALSE)
    {
      /* send response from main function */
      Dcm_GblSendResponse = DCM_TRUE;
    }
  }

  DCM_UNUSED(OpStatus);
  /* TODO: return value shall be processed */
  return E_OK;  
}

/*******************************************************************************
** Function Name        : Dcm_DcmReadMemoryCall                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_DcmReadMemoryCall function is used to call      **
**                        Dcm_ReadMemory callout.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GddNegRespError           **
**                        Dcm_MemServicePendingStatus,Dcm_GddOpStatus         **
**                        Dcm_GulRMBAMemoryAddress , Dcm_GusRMBAMemorySize    **
**                        Dcm_ServiceForcePendingStatus,Dcm_GpMsgContext      **
**                        Dcm_GusRMBAMemorySize , Dcm_GusMaxNoOfForceRespPend,**
**                        Dcm_GaaResponseBuf , Dcm_TxRespStatus               **
**                        Function(s) invoked :                               **
**                        Dcm_ReadMemory, Dcm_DslPduRTransmit ,               **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DcmReadMemoryCall(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_ReturnReadMemoryType LddReturnValue = (Dcm_ReturnReadMemoryType)0x00;
  uint32 LulMemoryAddress;
  uint32 LulMemorySize;
  uint8 LucMemoryIdentifier;

  /* Reset Dcm_GddNegRespError */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

  /* Set response pending flag to False */
  Dcm_MemServicePendingStatus.ucReadMemPendingStatus =
    DCM_FALSE;
  /* Set ForceRcrrp Pending flag to False */
  Dcm_ServiceForcePendingStatus.ucReadMemForcePendingStatus =
    DCM_FALSE;

  /* Get Memory address, memory size and Memory identifier */
  LulMemoryAddress = Dcm_GulRMBAMemoryAddress;
  LulMemorySize = Dcm_GulRMBAMemorySize;
  LucMemoryIdentifier = Dcm_GucRMBAMemoryIdentifier;

  /*  Fix For MISRA 21.1 - BSH  */
  if (
    (pMsgContext == NULL_PTR) || 
    (pMsgContext->resData == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR)
  )
  {
    /* TODO : Det Error */    
    Dcm_GddNegRespError = DCM_E_GENERALPROGRAMMINGFAILURE;
  }
  else
  {
    /* Invoke callout Dcm_ReadMemory  */
    LddReturnValue = Dcm_ReadMemory(Dcm_GddOpStatus, LucMemoryIdentifier,
      LulMemoryAddress, LulMemorySize, pMsgContext->resData);  
  
    /* Check for OpStatus */
    if(Dcm_GddOpStatus != DCM_CANCEL)
    {
      if(LddReturnValue == DCM_READ_OK)
      {
        /* Update Dcm_GddOpStatus */
        Dcm_GddOpStatus = DCM_INITIAL;

        /* Update response data length */
        pMsgContext->resDataLen = LulMemorySize;
      }
      else if(LddReturnValue == DCM_READ_PENDING)
      {
        /* Update Dcm_GddOpStatus */
        Dcm_GddOpStatus = DCM_PENDING;
        /* Set response pending flag to True */
        Dcm_MemServicePendingStatus.ucReadMemPendingStatus
          = DCM_TRUE;
      }
      else if(LddReturnValue == DCM_READ_FORCE_RCRRP)
      {
        /* Update Dcm_GddOpStatus */
        Dcm_GddOpStatus = DCM_FORCE_RCRRP_OK;
        /* Set Force response pending flag to True */
        Dcm_ServiceForcePendingStatus.
        ucReadMemForcePendingStatus = DCM_TRUE;
        /* Update Dcm_GusMaxNoOfForceRespPend */
        Dcm_GusMaxNoOfForceRespPend++;
        /* Check if Dcm_GusMaxNoOfForceRespPend reaches configured limit */
        /* 0xFF : limit threshold is unused */
        if(Dcm_GusMaxNoOfForceRespPend > (uint16)Dcm_diag_Resp_Max_Num_Respend)
        {
          /* Update Dcm_GddOpStatus */
          Dcm_GddOpStatus = DCM_INITIAL;
          /* Update Dcm_GddNegRespError */
          Dcm_GddNegRespError = DCM_E_GENERALREJECT;
            Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
          /* Invoke callout Dcm_ReadMemory with OpStatus as DCM_CANCEL */
          (void)Dcm_ReadMemory(DCM_CANCEL, LucMemoryIdentifier,
            LulMemoryAddress, LulMemorySize, pMsgContext->resData);

          /* Set Force response pending flag to false */
          Dcm_ServiceForcePendingStatus.
            ucReadMemForcePendingStatus  = DCM_FALSE;
        }
        else
        {

        }
      }
      else
      {
        /* Update Dcm_GddNegRespError */
        Dcm_GddNegRespError = DCM_E_GENERALPROGRAMMINGFAILURE;
      }
    }
  }

  /* To send positive and negative response */
  if (
    (Dcm_MemServicePendingStatus.ucReadMemPendingStatus == DCM_FALSE) && 
    (Dcm_ServiceForcePendingStatus.ucReadMemForcePendingStatus == DCM_FALSE) && 
    (Dcm_GddOpStatus != DCM_CANCEL)
  )
  {
    Dcm_GddOpStatus = DCM_INITIAL;

    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
  /* To send response pending */
  else if(Dcm_ServiceForcePendingStatus.ucReadMemForcePendingStatus == DCM_TRUE)
  {
    /* Update the negative response service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
     /* Update the service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ONE] = ((pMsgContext->idContext) & (DCM_BIT6_AND_MASK));
     /* Update the NRC in the response buffer */
    Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
    /* Update the bit flag for negative response to TRUE */
    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;
    
    /* Send response from main function */
    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
  else
  {
    /* To Avoid QAC Warning */
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmWriteMemoryByAddress                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_DcmWriteMemoryByAddress service is used to      **
**                        write data using a physical memory address          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_GusMaxNoOfForceRespPend,    **
**                        Dcm_GddNegRespError , Dcm_GddOpStatus,              **
**                        Dcm_GaaAddressAndLengthFormatIds ,Dcm_GpWriteData   **
**                        Dcm_GucMemAddrSizeBytes, Dcm_GaaWriteMemRngConfig   **
**                        Dcm_GulWriteMemoryAddress, Dcm_GusWriteMemorySize   **
**                        Dcm_GucMemoryIdentifier, Dcm_GaaModeRuleConfig      **
**                        Function(s) invoked :                               **
**                        Dcm_DsdValidateSecurity, Dcm_DsdModeRuleCheck ,     **
**                        Dcm_DcmWriteMemoryCall, Dcm_ExternalSetNegResponse ,**
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
#if(DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmWriteMemoryByAddress(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;

  #if((DCM_MODE_RULE  ==  STD_ON) && (DCM_DSP_MODE_RULE_NRC == STD_ON))
  P2CONST(Dcm_ModeRuleConfigType,  AUTOMATIC,  DCM_APPL_CONST)
    LpModeRule;
  #endif
  uint32 LulMemoryAddress;
  uint32 LulMemorySize;
  uint8 LucAddrLenForId = (uint8)0x00;
  uint8 LucMemAdrBytes;
  uint8 LucMemSizeBytes;
  uint8 LucMemoryIdentifier;
  uint8 LucLoopVar;
  boolean LblItemFound;
  boolean LblSearchResult;
  boolean LblWriteMemoryApiInvoked;

  /* Initialize local variables */
  LulMemoryAddress = DCM_ZERO;
  LulMemorySize = DCM_ZERO;
  LblItemFound = DCM_FALSE;
  LblWriteMemoryApiInvoked = DCM_FALSE;
  /* Resetting global variables */
  Dcm_GusMaxNoOfForceRespPend = DCM_E_POSITIVERESPONSE;
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_GddOpStatus = DCM_INITIAL;

  if (
    (pMsgContext == NULL_PTR) || 
    (pMsgContext->resData == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR)
  )
  {
    /* TODO : Det Error */    
    Dcm_GddNegRespError = DCM_E_GENERALPROGRAMMINGFAILURE;
  }
  else
  {
    /* Get data from request */
    LpReqResData = pMsgContext->reqData;
  
    /* Get the addressAndLengthFormatIdentifier from the request */
    LucAddrLenForId = *(LpReqResData);
  
  
    #if(DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG != DCM_ZERO)
    /* Check for configured Address and length format identifier */
    for(LucLoopVar = DCM_ZERO;
      LucLoopVar < Dcm_Num_Of_Address_Length_Format_ID_Config; LucLoopVar++)
    {
      if(LucAddrLenForId == Dcm_GaaAddressAndLengthFormatIds[LucLoopVar])
      {
        LblItemFound = DCM_TRUE;
        break;
      }
    }
    #else
    LblItemFound = DCM_TRUE;
    #endif

    if(LblItemFound == DCM_TRUE)
    {
      /* Get memory address and memory size bytes from
      AddressAndLengthFormatIdentifier*/
      LucMemAdrBytes = (LucAddrLenForId & DCM_SIG_BYTE_MASK_VALUE);
      LucMemSizeBytes = ((LucAddrLenForId & DCM_SIG_SIZE_MASK_VALUE) >> DCM_FOUR);

      Dcm_GucMemAddrSizeBytes = LucMemAdrBytes + LucMemSizeBytes + DCM_ONE;

      LucLoopVar = DCM_ZERO;

      /* Get Memory Address from the request */
      do
      {
        LulMemoryAddress = LulMemoryAddress << DCM_EIGHT;
    
        LpReqResData = &LpReqResData[1u];
        
        LulMemoryAddress |= *(LpReqResData);
        LucLoopVar++;
      }
      while(LucLoopVar < LucMemAdrBytes);

      LucLoopVar = DCM_ZERO;
    
      /* Get Memory Size from the request */
      do
      {       
        LulMemorySize = LulMemorySize << DCM_EIGHT;
    
        LpReqResData = &LpReqResData[1u];
        
        LulMemorySize |= *(LpReqResData);
        LucLoopVar++;    
      }
      while(LucLoopVar < LucMemSizeBytes);


      LpReqResData = &LpReqResData[1u];
      Dcm_GpWriteData = LpReqResData;

      /* Check length of request is valid or not */
      if(pMsgContext->reqDataLen == (uint32)((uint32)LulMemorySize + (uint32)LucMemAdrBytes + 
      (uint32)LucMemSizeBytes + (uint32)0x01))
      {
        /* Variable To break The Loop */
        LblItemFound = DCM_ZERO;

        /* Check Current memory is with in memory range configures */
        for(LucLoopVar = 0U; LucLoopVar < Dcm_Total_Num_Write_Memory_Configured; LucLoopVar++)
        {
	      /* polyspace +2 MISRA-C3:10.6 [Justified:Low] "Not a defect" */  
          Dcm_uint64 reqHighAddr = (LulMemoryAddress + (uint32)LulMemorySize) - 1U;
          Dcm_uint64 reqLowAddr = LulMemoryAddress;
          if ((reqLowAddr  >= Dcm_GaaWriteMemRngConfig[LucLoopVar].ulWriteMemRngLow) &&
              (reqHighAddr <= Dcm_GaaWriteMemRngConfig[LucLoopVar].ulWriteMemRngHigh))
          {
            LblItemFound = DCM_TRUE;
            break;
          }
        }

        if(DCM_TRUE == LblItemFound)
        {
          /* Get configured memory range */
          /* Check security for memory range is configured */
          if(Dcm_GaaWriteMemRngConfig[LucLoopVar].pWriteMemRngSec != NULL_PTR)
          {
            /* Invoke function for security validation */
            LblSearchResult = Dcm_DsdValidateSecurity(
              Dcm_GaaWriteMemRngConfig[LucLoopVar].pWriteMemRngSec,
                Dcm_GaaWriteMemRngConfig[LucLoopVar].ucWriteMemSecCount);
          }
          else
          {
            LblSearchResult = DCM_TRUE;
          }

          /* check is current security level supported by the service ID */
          if(LblSearchResult == DCM_TRUE)
          {
            #if(DCM_MODE_RULE  ==  STD_ON)
            if(Dcm_GaaWriteMemRngConfig[LucLoopVar].blModeRuleConfigured == DCM_TRUE)
            {
              LblSearchResult = Dcm_DsdModeRuleCheck
                (Dcm_GaaWriteMemRngConfig[LucLoopVar].ucDIDmoderuleArrayindex);
            }

            if(LblSearchResult  ==  DCM_TRUE)
            #endif
            {          
              /* Fixed by youngjin yun 2014.10.24 */
              if(Dcm_GaaWriteMemRngConfig[LucLoopVar].blUseMemoryValue == DCM_TRUE)
              {
                /* Get configured memory identifier */
                LucMemoryIdentifier = 
                  Dcm_GaaWriteMemRngConfig[LucLoopVar].ucWriteMemoryIdentifier;
              }
              else
              {
                /* Get configured memory identifier */
                LucMemoryIdentifier = DCM_ZERO;
              }

              /* Update Dcm_GulWriteMemoryAddress */
              Dcm_GulWriteMemoryAddress = LulMemoryAddress;
              /* Update Dcm_GusWriteMemorySize */
              Dcm_GulWriteMemorySize = LulMemorySize;
              /* Update Dcm_GucMemoryIdentifier */
              Dcm_GucMemoryIdentifier = LucMemoryIdentifier;
              LblWriteMemoryApiInvoked = DCM_TRUE;
              /* call to Dcm_DcmWriteMemoryCall to get data record */
              Dcm_DcmWriteMemoryCall(pMsgContext);
            }
            #if(DCM_MODE_RULE  ==  STD_ON)
            /*  Store  the  NRC  error  and  set  the  error  flag  */
            else
            {
              #if(DCM_DSP_MODE_RULE_NRC == STD_ON)
              LpModeRule  =  &Dcm_GaaModeRuleConfig
                  [Dcm_GaaWriteMemRngConfig[LucLoopVar].ucDIDmoderuleArrayindex];
              Dcm_GddNegRespError =  LpModeRule->ucNRCType;
              #else
              /* Update Negative Response Code */
              Dcm_GddNegRespError  =  DCM_E_CONDITIONSNOTCORRECT;
              #endif
            }
            #endif
          }
          else
          {
            /* 
              set NRC Security access denied because security level
                                is not supported by service ID */
            Dcm_GddNegRespError = DCM_E_SECURITYACCESSDENIED;
          }
        }
        else
        {
          /* Redmine #1677 ,Modified by youngjin.yun
            set NRC RequestOutOfRange because (memory address + size) is not
            with in the range */
          Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
        }
      }
      else
      {
        /* Set IncorrectMessageLengthOrInvalidFormatId NRC */
        Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }

    }
    else
    {
      /* Set NRC RequestOutOfRange because of wrong ALFID  */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
  }

  if(LblWriteMemoryApiInvoked == DCM_FALSE)
  {
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  DCM_UNUSED(OpStatus);
  
  /* TODO: return value shall be processed */
  return E_OK;  
}

/*******************************************************************************
** Function Name        : Dcm_DcmWriteMemoryCall                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_DcmWriteMemoryCall function is used to call     **
**                        Dcm_WriteMemory call out.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :Dcm_GddNegRespError,           **
**                        Dcm_MemServicePendingStatus ,Dcm_GddOpStatus        **
**                        Dcm_GulWriteMemoryAddress ,Dcm_GusWriteMemorySize , **
**                        Dcm_GucMemoryIdentifier, Dcm_GucMemAddrSizeBytes    **
**                        Dcm_ServiceForcePendingStatus ,                     **
**                        Dcm_GusMaxNoOfForceRespPend , Dcm_GaaResponseBuf ,  **
**                        Dcm_TxRespStatus                                    **
**                        Function(s) invoked :                               **
**                        Dcm_WriteMemory, Dcm_DslPduRTransmit ,              **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DcmWriteMemoryCall(
 P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_ReturnWriteMemoryType LddReturnValue;
  uint32 LulMemoryAddress;
  uint32 LulMemorySize;
  uint8 LucMemoryIdentifier;
  uint8 LucLoopVar;

  if (
    (pMsgContext == NULL_PTR) || 
    (pMsgContext->resData == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR)
  )
  {
    /* TODO : Det Error */    
    Dcm_GddNegRespError = DCM_E_GENERALPROGRAMMINGFAILURE;
  }
  else
  {
    /* Resetting Dcm_GddNegRespError */
    Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

    /* Set response pending flag to False */
    Dcm_MemServicePendingStatus.ucWriteMemPendingStatus  =  DCM_FALSE;
    /* Set ForceRcrrp Pending flag to False */
    Dcm_ServiceForcePendingStatus.ucWriteMemForcePendingStatus = DCM_FALSE;

    /* Get memory address, memory size and memory identifier */
    LulMemoryAddress = Dcm_GulWriteMemoryAddress;
    LulMemorySize = Dcm_GulWriteMemorySize;
    LucMemoryIdentifier = Dcm_GucMemoryIdentifier;

    /* Invoke callout Dcm_Write Memory  */
    LddReturnValue = Dcm_WriteMemory(Dcm_GddOpStatus, LucMemoryIdentifier,
      LulMemoryAddress, LulMemorySize, Dcm_GpWriteData);
    /* check for OpStatus */
    if(Dcm_GddOpStatus != DCM_CANCEL)
    {
      if(LddReturnValue == DCM_WRITE_OK)
      {
        /* Update response data length */
        pMsgContext->resDataLen = Dcm_GucMemAddrSizeBytes;
        /* send positive response */
        LucLoopVar = DCM_ZERO;
        /* Updat response data */
        do
        {
          /* polyspace<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
          pMsgContext->resData[LucLoopVar] = pMsgContext->reqData[LucLoopVar];
          LucLoopVar++;
        }
        while(LucLoopVar < Dcm_GucMemAddrSizeBytes);
        /* Update Dcm_GddOpStatus */
        Dcm_GddOpStatus = DCM_INITIAL;
      }
      else if(LddReturnValue == DCM_WRITE_PENDING)
      {
      /* Update Dcm_GddOpStatus */
        Dcm_GddOpStatus = DCM_PENDING;
        /* Set response pending flag to True */
        Dcm_MemServicePendingStatus.ucWriteMemPendingStatus =
          DCM_TRUE;
      }
      else if(LddReturnValue == DCM_WRITE_FORCE_RCRRP)
      {
        /* Update Dcm_GddOpStatus */
        Dcm_GddOpStatus = DCM_FORCE_RCRRP_OK;
        /* Set Force responsepending flag to True */
        Dcm_ServiceForcePendingStatus.
          ucWriteMemForcePendingStatus = DCM_TRUE;
        /* Update Dcm_GusMaxNoOfForceRespPend */
        Dcm_GusMaxNoOfForceRespPend++;
        /* Check for Dcm_GusMaxNoOfForceRespPend */
        /* 0xFF : limit threshold is unused */
        if(Dcm_GusMaxNoOfForceRespPend > (uint16)Dcm_diag_Resp_Max_Num_Respend)
        {
          /* Update Dcm_GddOpStatus */
          Dcm_GddOpStatus = DCM_INITIAL;
          /* Update Dcm_GddNegRespError */
          Dcm_GddNegRespError = DCM_E_GENERALREJECT;
          Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
          /* Invoke callout Dcm_WriteMemory  with OpStatus as DCM_CANCEL */
          (void) Dcm_WriteMemory(DCM_CANCEL, LucMemoryIdentifier,
            LulMemoryAddress, LulMemorySize, Dcm_GpWriteData);
          /* Set Force responsepending flag to False */
          Dcm_ServiceForcePendingStatus.
            ucWriteMemForcePendingStatus = DCM_FALSE;
        }
        else
        {

        }
      }
      else
      {
        /* Update Dcm_GddNegRespError */
        Dcm_GddNegRespError = DCM_E_GENERALPROGRAMMINGFAILURE;
      }
    }
  }

  /* To send positive and negative response */
  if((Dcm_MemServicePendingStatus.ucWriteMemPendingStatus ==
    DCM_FALSE) && (Dcm_ServiceForcePendingStatus.
    ucWriteMemForcePendingStatus == DCM_FALSE) && (Dcm_GddOpStatus != DCM_CANCEL))
  {
    Dcm_GddOpStatus = DCM_INITIAL;
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
  /* To send response pending */
  else if(Dcm_ServiceForcePendingStatus.
        ucWriteMemForcePendingStatus == DCM_TRUE)
  {
    /* Update the negative response service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
    /* Update the service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ONE] =
      ((pMsgContext->idContext) & (DCM_BIT6_AND_MASK));
    /* Update the NRC in the response buffer */
    Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
    /* Update the bit flag for negative response to TRUE */
    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;    
    /* Send response from main function */
    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
  else
  {
    /* To Avoid QAC Warning */
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmRequestDownLoad                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_DcmRequestDownLoad service is used to request   **
**                        the start of download process.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_GusMaxNoOfForceRespPend,    **
**                        Dcm_GddNegRespError , Dcm_GddOpStatus ,             **
**                        Dcm_GaaAddressAndLengthFormatIds ,Dcm_GulDLMemSize  **
**                        Dcm_GulDLMemAddress,                                **
**                        Dcm_GucDataForId ,                                  **
**                        Function(s) invoked :                               **
**                        Dcm_DcmDownLoadCall, Dcm_ExternalSetNegResponse ,   **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
#if(DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmRequestDownLoad(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  uint32 LulMemoryAddress;
  uint32 LulMemorySize;
  uint8 LucMemAdrBytes;
  uint8 LucMemSizeBytes;
  uint8 LucAddrLenForId;
  uint8 LucDataForId;
  #if(DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG != DCM_ZERO)
  uint8 LucLoopVar;
  #endif
  boolean LblDownLoadApiInvoked;
  boolean LddAddrLenForIdSupported;

  uint32 LulMaxValOfMemSizeBytes = 0;
  uint8 LucMemSizeCount = 0;

  LulMemoryAddress = DCM_ZERO;
  LulMemorySize = DCM_ZERO;
  Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
  LddAddrLenForIdSupported = DCM_FALSE;
  LblDownLoadApiInvoked = DCM_FALSE;

  /* set NRC flag to false */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_GddOpStatus = DCM_INITIAL;

  /* Get requested data */
  LpReqResData = pMsgContext->reqData;


  /* Get DataFormatIdentifier from the request */
  LucDataForId = *(LpReqResData);

  /* MISRA Rule        : 17.4
    Message            : Increment or decrement operation
                         performed on pointer
    Reason             : Increment operator not used
                         to achieve better throughput.
    Verification       : However, part of the code
                         is verified manually and
                         it is not having any impact.
  */
  /* Get the addressAndLengthFormatIdentifier from the request */
  LpReqResData++;
  LucAddrLenForId = *(LpReqResData);

  #if(DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG != DCM_ZERO)
  /* Check for configured Address and length format identifier */
  for(LucLoopVar = DCM_ZERO;
    LucLoopVar < Dcm_Num_Of_Address_Length_Format_ID_Config; LucLoopVar++)
  {
    if(LucAddrLenForId == Dcm_GaaAddressAndLengthFormatIds[LucLoopVar])
    {
      LddAddrLenForIdSupported = DCM_TRUE;
      /* MISRA Rule        : 13.6
        Message            : Control variable, LucLoopVar,
                             modified in body of loop
        Reason             : Once the search element found, control
                             exiting from the for loop to terminate
                             next iteration.
        Verification       : However, part of the code
                             is verified manually and
                             it is not having any impact.
      */
      /* To Break Loop */
      break;
    }
  }
  #else
  LddAddrLenForIdSupported = DCM_TRUE;
  #endif

  /* check AddressAndLengthFormatIdentifier is valid or not */
  if(LddAddrLenForIdSupported == DCM_TRUE)
  {
    /* Get the number of memory address and memory size bytes */
    LucMemAdrBytes = (LucAddrLenForId & DCM_SIG_BYTE_MASK_VALUE);
    LucMemSizeBytes = ((LucAddrLenForId & DCM_SIG_SIZE_MASK_VALUE) >> DCM_FOUR);

    /* check length of the request is valid or not */
    if(pMsgContext->reqDataLen ==
    /* polyspace +1 MISRA-C3:10.8 [Justified:Low] "Not a defect" */	    
      (uint16)(LucMemAdrBytes + LucMemSizeBytes + DCM_TWO))
    {
      /* Get memory address from the request */
      do
      {
        LulMemoryAddress = LulMemoryAddress << DCM_EIGHT;
        /* MISRA Rule        : 17.4
          Message            : Increment or decrement operation
                               performed on pointer
          Reason             : Increment operator not used
                               to achieve better throughput.
          Verification       : However, part of the code
                               is verified manually and
                               it is not having any impact.
        */
        LpReqResData++;
        LulMemoryAddress |= *(LpReqResData);
        LucMemAdrBytes--;
      }
      while(LucMemAdrBytes != DCM_ZERO);
      /* Get memory size from the request */
      do
      {
        LulMemorySize = LulMemorySize << DCM_EIGHT;
        /* MISRA Rule        : 17.4
          Message            : Increment or decrement operation
                               performed on pointer
          Reason             : Increment operator not used
                               to achieve better throughput.
          Verification       : However, part of the code
                               is verified manually and
                               it is not having any impact.
        */
        LpReqResData++;
        LulMemorySize |= *(LpReqResData);
        LucMemSizeBytes--;

        LulMaxValOfMemSizeBytes = LulMaxValOfMemSizeBytes << DCM_EIGHT;
        LucMemSizeCount++;
        LulMaxValOfMemSizeBytes |= (uint32)(0x000000FF);
      }
      while(LucMemSizeBytes != DCM_ZERO);

      /* Memory size overflow check */
	  #if(DCM_SECURE_FLASH_SUPPORT == STD_ON)
      if(LulMaxValOfMemSizeBytes > DCM_SIGNATURE_SIZE)
      {
    	  LulMaxValOfMemSizeBytes -= DCM_SIGNATURE_SIZE;
      }
      else
      {
    	  LulMaxValOfMemSizeBytes = 0;
      }
	  #endif

      if(LulMemorySize < LulMaxValOfMemSizeBytes)
      {
          /* Update Memory Address,Size and Dataformat ID */
          Dcm_GulDLMemAddress = LulMemoryAddress;
          Dcm_GulDLMemSize = LulMemorySize;
          Dcm_GucDataForId = LucDataForId;
          LblDownLoadApiInvoked = DCM_TRUE;
          /* Call to DownLoad call out */
          Dcm_DcmDownLoadCall(pMsgContext);
      }
      else
      {
    	  Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      }

    }
    else
    {
      /* set NRC IncorrectMessageLengthOrInvalidFormat */
      Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }
  else
  {
    /* set NRC RequestOutOfRange  because of wrong ALFID */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }
  if(LblDownLoadApiInvoked == DCM_FALSE)
  {
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  DCM_UNUSED(OpStatus);
  /* TODO: return value shall be processed */
  return E_OK;  
}

/*******************************************************************************
** Function Name        : Dcm_DcmDownLoadCall                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_DcmDownLoadCall function is used to call        **
**                        Dcm_ProcessRequestDownload callout.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):Dcm_GddNegRespError,             **
**                        Dcm_MemServicePendingStatus ,                       **
**                        Dcm_ServiceForcePendingStatus ,                     **
**                        Dcm_GulDLMemAddress,Dcm_GulDLMemSize                **
**                        Dcm_GucDataForId ,Dcm_GblDownLoadActive ,           **
**                        Dcm_GblUpLoadActive , Dcm_GucBlockSeqCounter        **
**                        Dcm_GddOpStatus , Dcm_GulBlockLength ,              **
**                        Dcm_GulNumOfBytesToBeTransfer,                      **
**                        Dcm_GusMaxNoOfForceRespPend,                        **
**                        Dcm_TxRespStatus, Dcm_GulBlockLength                **
**                        Dcm_GaaResponseBuf                                  **
**                        Function(s) invoked :                               **
**                        Dcm_ProcessRequestDownload, Dcm_DslPduRTransmit ,   **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DcmDownLoadCall(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_NegativeResponseCodeType LddNegativeErrorCode;
  Std_ReturnType LddReturnValue;
  uint32 LulMemoryAddress;
  uint32 LulMemorySize;
  uint32 LulBlockLength;
  uint8 LucDataForId;

  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  LddNegativeErrorCode = DCM_E_POSITIVERESPONSE;
  LulBlockLength = (uint32)DCM_ZERO;

  /* Set response pending flag to False */
  Dcm_MemServicePendingStatus.ucDlPendingStatus = DCM_FALSE;
  /* Set ForceRcrrp Pending flag to False */
  Dcm_ServiceForcePendingStatus.ucDlForcePendingStatus =
    DCM_FALSE;


  /* Updating Memory address, size and Data format ID */
  LulMemoryAddress = Dcm_GulDLMemAddress;
  LulMemorySize = Dcm_GulDLMemSize;
  LucDataForId = Dcm_GucDataForId;

  /* Invoke callout Dcm_ProcessRequestDownload */
  LddReturnValue = Dcm_ProcessRequestDownload(Dcm_GddOpStatus, LucDataForId,
    LulMemoryAddress, LulMemorySize, &LulBlockLength, &LddNegativeErrorCode);
  /* Check for OpStatus */
  if(Dcm_GddOpStatus != DCM_CANCEL)
  {
    if(LddReturnValue == E_OK)
    {
      /* Update Dcm_GblDownLoadActive */
      Dcm_GblDownLoadActive = DCM_TRUE;
      /* Update Dcm_GblUpLoadActive */
      Dcm_GblUpLoadActive = DCM_FALSE;
      /* Update Dcm_GucBlockSeqCounter */
      Dcm_GucBlockSeqCounter = DCM_ONE;
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_INITIAL;
      /* Update Dcm_GulBlockLength */
      /* polyspace +2 RTE:NIVL [Justified:Low] "Not a defect" */
      /* polyspace +1 MISRA-C3:9.1 [Justified:Low] "Not a defect" */
       Dcm_GulBlockLength = LulBlockLength;
      /* Update Dcm_GulNumOfBytesToBeTransfer */
      Dcm_GulNumOfBytesToBeTransfer = LulMemorySize;

	  #if(DCM_SECURE_FLASH_SUPPORT == STD_ON)
   	  Dcm_GulNumOfBytesToBeTransfer += DCM_SIGNATURE_SIZE;
	  #endif

    }
    else if(LddReturnValue == DCM_E_PENDING)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_PENDING;
      /* Set response pending flag to True */
      Dcm_MemServicePendingStatus.ucDlPendingStatus =
        DCM_TRUE;
    }
    else if(LddReturnValue == DCM_E_FORCE_RCRRP)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_FORCE_RCRRP_OK;
      /* Set Force responsepending flag to True */
      Dcm_ServiceForcePendingStatus.ucDlForcePendingStatus =
        DCM_TRUE;
      /* Update Dcm_GusMaxNoOfForceRespPend */
      Dcm_GusMaxNoOfForceRespPend++;
      /* 0xFF : limit threshold is unused */
      if(Dcm_GusMaxNoOfForceRespPend > (uint16)Dcm_diag_Resp_Max_Num_Respend)
      {
        /* Update Dcm_GddOpStatus */
        Dcm_GddOpStatus = DCM_INITIAL;
        /* Update Dcm_GddNegRespError */
        Dcm_GddNegRespError = DCM_E_GENERALREJECT;
          Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
        /* Invoke callout Dcm_ProcessRequestDownload with OpStatus DCM_CANCEL */
        (void) Dcm_ProcessRequestDownload(DCM_CANCEL, LucDataForId,
          LulMemoryAddress, LulMemorySize,
            &LulBlockLength, &LddNegativeErrorCode);
        /* Set DownLoad Force pending Status flag to false */
        Dcm_ServiceForcePendingStatus.
        ucDlForcePendingStatus = DCM_FALSE;
      }
    }
    else
    {
      /* Update Dcm_GddNegRespError */
      Dcm_GddNegRespError = LddNegativeErrorCode;
    }
  }

  if ((Dcm_MemServicePendingStatus.ucDlPendingStatus == DCM_FALSE) &&
      (Dcm_ServiceForcePendingStatus.ucDlForcePendingStatus == DCM_FALSE) &&  
      (Dcm_GddOpStatus != DCM_CANCEL))
  {
    Dcm_GddOpStatus = DCM_INITIAL;
    Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;    
    /* Check if the negative response needs to be updated here */
    if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
    {
      /* Report the NRC to the DSD layer */
      Dcm_ExternalSetNegResponse(pMsgContext, Dcm_GddNegRespError);
    }
    else
    {
      /* Send positive response */
      pMsgContext->resDataLen = 5U;
      pMsgContext->resData[0U] = 64;
      pMsgContext->resData[1U] = (uint8)((Dcm_GulBlockLength) >> 24U);
      pMsgContext->resData[2U] = (uint8)((Dcm_GulBlockLength) >> 16U);
      pMsgContext->resData[3U] = (uint8)((Dcm_GulBlockLength) >> 8U);
      pMsgContext->resData[4U] = (uint8)(Dcm_GulBlockLength);
    }
    
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
  else if(Dcm_ServiceForcePendingStatus.ucDlForcePendingStatus == DCM_TRUE)
  {
    /* Update the negative response service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
     /* Update the service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ONE] =
      ((pMsgContext->idContext) & (DCM_BIT6_AND_MASK));
     /* Update the NRC in the response buffer */
    Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;      
    /* Update the bit flag for negative response to TRUE */
    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;

    /* Send response from main function */
    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
  else
  {
    /* To Avoid QAC Warning */
  }
}
#endif

/*******************************************************************************
** Function Name       : Dcm_DcmRequestUpLoad                                 **
**                                                                            **
** Service ID          : NA                                                   **
**                                                                            **
** Description         : Dcm_DcmRequestUpLoad service is used to request      **
**                       Start of Upload process                              **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Non Reentrant                                        **
**                                                                            **
** Input Parameters    : None                                                 **
**                                                                            **
** InOut parameter     : pMsgContext                                          **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : void                                                 **
**                                                                            **
** Preconditions       : None.                                                **
**                                                                            **
** Remarks             : Global Variable(s) : Dcm_GddNegRespError             **
**                       Dcm_GusMaxNoOfForceRespPend ,Dcm_GulULMemAddress     **
**                       Dcm_MemServicePendingStatus , Dcm_GulULMemSize       **
**                       Dcm_GaaAddressAndLengthFormatIds, Dcm_GucDataForId   **
**                       Function(s) invoked :                                **
**                        Dcm_DcmUpLoadCall, Dcm_ExternalSetNegResponse ,     **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
#if(DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmRequestUpLoad(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  uint32 LulMemoryAddress;
  uint32 LulMemorySize;
  uint32 LulReqDataLength;
  uint8 LucMemAdrBytes;
  uint8 LucMemSizeBytes;
  uint8 LucAddrLenForId;
  uint8 LucDataForId;
    #if(DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG != DCM_ZERO)
  uint8 LucLoopVar;
  #endif
  boolean LddAddrLenForIdSupported;
  boolean LblUploadApiInvoked;

  /* Initialize local variables */
  LulMemoryAddress = DCM_ZERO;
  LulMemorySize = DCM_ZERO;
  LddAddrLenForIdSupported = DCM_FALSE;
  LblUploadApiInvoked = DCM_FALSE;

  /* Initialize global variables */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
  Dcm_GddOpStatus = DCM_INITIAL;

  /* Set response pending flag to False */
  Dcm_MemServicePendingStatus.ucUlPendingStatus = DCM_FALSE;
  /* Set ForceRcrrp Pending flag to False */
  Dcm_ServiceForcePendingStatus.ucUlForcePendingStatus =
    DCM_FALSE;


  /* Get Requested data from request */
  LpReqResData = pMsgContext->reqData;
  /* Get Requested data Length from request*/
  LulReqDataLength = pMsgContext->reqDataLen;

  /* Get DataFormatIdentifier from the request */
  LucDataForId = *(LpReqResData);

  /* MISRA Rule        : 17.4
    Message            : Increment or decrement operation
                         performed on pointer
    Reason             : Increment operator not used
                         to achieve better throughput.
    Verification       : However, part of the code
                         is verified manually and
                         it is not having any impact.
  */
  /*Get the addressAndLengthFormatIdentifier from the request*/
  LpReqResData++;
  LucAddrLenForId = *(LpReqResData);

  #if(DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG != DCM_ZERO)
  /* Check for configured Address and length format identifier */
  for(LucLoopVar = DCM_ZERO;
    LucLoopVar < Dcm_Num_Of_Address_Length_Format_ID_Config; LucLoopVar++)
  {
    if(LucAddrLenForId == Dcm_GaaAddressAndLengthFormatIds[LucLoopVar])
    {
      LddAddrLenForIdSupported = DCM_TRUE;
      /* MISRA Rule        : 13.6
        Message            : Control variable, LucLoopVar,
                             modified in body of loop
        Reason             : Once the search element found, control
                             exiting from the for loop to terminate
                             next iteration.
        Verification       : However, part of the code
                             is verified manually and
                             it is not having any impact.
      */
      /* To Break Loop */
      LucLoopVar = Dcm_Num_Of_Address_Length_Format_ID_Config;
    }
  }
  #else
  LddAddrLenForIdSupported = DCM_TRUE;
  #endif

  /* check AddressAndLengthFormatIdentifier is valid or not */
  if(LddAddrLenForIdSupported == DCM_TRUE)
  {
    /* Get Memory address bytes and memory size bytes
      from the request */
    LucMemAdrBytes = (LucAddrLenForId & DCM_SIG_BYTE_MASK_VALUE);
    LucMemSizeBytes =
      (uint8)((LucAddrLenForId & DCM_SIG_SIZE_MASK_VALUE) >> DCM_FOUR);

    /* check length of the request is valid or not */
    if(LulReqDataLength == (uint32)(LucMemAdrBytes + LucMemSizeBytes + DCM_TWO))
    {
      /* Get memory address from the request */
      do
      {
        LulMemoryAddress = LulMemoryAddress << DCM_EIGHT;
        /* MISRA Rule        : 17.4
          Message            : Increment or decrement operation
                               performed on pointer
          Reason             : Increment operator not used
                               to achieve better throughput.
          Verification       : However, part of the code
                               is verified manually and
                               it is not having any impact.
        */
        LpReqResData++;
        LulMemoryAddress |= *(LpReqResData);
        LucMemAdrBytes--;
      }
      while(LucMemAdrBytes != DCM_ZERO);

      /* Get memory size from the request */
      do
      {
        LulMemorySize = LulMemorySize << DCM_EIGHT;
        /* MISRA Rule        : 17.4
          Message            : Increment or decrement operation
                               performed on pointer
          Reason             : Increment operator not used
                               to achieve better throughput.
          Verification       : However, part of the code
                               is verified manually and
                               it is not having any impact.
        */
        LpReqResData++;
        LulMemorySize |= *(LpReqResData);
        LucMemSizeBytes--;
      }
      while(LucMemSizeBytes != DCM_ZERO);

      /* Update Memory Address,Size and Data format ID */
      Dcm_GulULMemAddress = LulMemoryAddress;
      Dcm_GulULMemSize = LulMemorySize;
      Dcm_GucDataForId = LucDataForId;
      LblUploadApiInvoked = DCM_TRUE;
      /* Invoke Request Upload call */
      Dcm_DcmUpLoadCall(pMsgContext);
    }
    else
    {

      /*set NRC IncorrectMessageLengthOrInvalidFormat */
      Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }
  else
  {
    /*set NRC RequestOutOfRange  because of wrong ALFID */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }

  if(LblUploadApiInvoked == DCM_FALSE)
  {
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  DCM_UNUSED(OpStatus);
  
  /* TODO: return value shall be processed */
  return E_OK;  
}

/*******************************************************************************
** Function Name        : Dcm_DcmUpLoadCall                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_DcmUpLoadCall function is used to invoke        **
**                        Dcm_ProcessRequestUpload callout.                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):Dcm_MemServicePendingStatus      **
**                        Dcm_ServiceForcePendingStatus , Dcm_GucDataForId    **
**                        Dcm_GulULMemAddress,Dcm_GulULMemSize,               **
**                        Dcm_GddOpStatus ,Dcm_GblUpLoadActive,               **
**                        Dcm_GblDownLoadActive ,Dcm_GucBlockSeqCounter,      **
**                        Dcm_GulBlockLength ,Dcm_GulNumOfBytesToBeTransfer   **
**                        Dcm_GusMaxNoOfForceRespPend , Dcm_TxRespStatus      **
**                        Dcm_GpMsgContext,Dcm_GaaResponseBuf                 **
**                        Function(s) invoked :                               **
**                        Dcm_ProcessRequestUpload, Dcm_DslPduRTransmit ,     **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DcmUpLoadCall(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_NegativeResponseCodeType LddNegativeErrorCode;
  Std_ReturnType LddReturnValue;
  uint32 LulMemoryAddress;
  uint32 LulMemorySize;
  uint32 LulBlockLength;
  uint8 LucDataForId;

  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  LddNegativeErrorCode = DCM_E_POSITIVERESPONSE;

  /* Set response pending flag to False */
  Dcm_MemServicePendingStatus.ucUlPendingStatus = DCM_FALSE;
  /* Set ForceRcrrp Pending flag to False */
  Dcm_ServiceForcePendingStatus.ucUlForcePendingStatus =
    DCM_FALSE;

  /* Update Memory address, Size and data format ID */
  LulMemoryAddress = Dcm_GulULMemAddress;
  LulMemorySize = Dcm_GulULMemSize;
  LucDataForId = Dcm_GucDataForId;

  /* Invoke callout Dcm_ProcessRequestUpload */
  LddReturnValue = Dcm_ProcessRequestUpload(Dcm_GddOpStatus, LucDataForId,
    LulMemoryAddress, LulMemorySize, &LulBlockLength, &LddNegativeErrorCode);
  /* check for OpStatus */
  if(Dcm_GddOpStatus != DCM_CANCEL)
  {
    if(LddReturnValue == E_OK)
    {
      /* Update Dcm_GblUpLoadActive */
      Dcm_GblUpLoadActive = DCM_TRUE;
      /* Update Dcm_GblDownLoadActive */
      Dcm_GblDownLoadActive = DCM_FALSE;
      /* Update Dcm_GucBlockSeqCounter */
      Dcm_GucBlockSeqCounter = DCM_ONE;
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_INITIAL;
      /* Update Dcm_GulBlockLength */
      Dcm_GulBlockLength = LulBlockLength;
      /* Update Dcm_GulNumOfBytesToBeTransfer */
      Dcm_GulNumOfBytesToBeTransfer = LulMemorySize;
    }
    else if(LddReturnValue == DCM_E_PENDING)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_PENDING;
      /* Set response pending flag to True */
      Dcm_MemServicePendingStatus.ucUlPendingStatus =
        DCM_TRUE;
    }
    else if(LddReturnValue == DCM_E_FORCE_RCRRP)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_FORCE_RCRRP_OK;
      /* Set Force responsepending flag to True */
      Dcm_ServiceForcePendingStatus.ucUlForcePendingStatus =
        DCM_TRUE;
      /* Update Dcm_GusMaxNoOfForceRespPend */
      Dcm_GusMaxNoOfForceRespPend++;
      /* 0xFF : limit threshold is unused */
      if(Dcm_GusMaxNoOfForceRespPend > (uint16)Dcm_diag_Resp_Max_Num_Respend)
      {
        /* Update Dcm_GddOpStatus */
        Dcm_GddOpStatus = DCM_INITIAL;
        /* Update Dcm_GddNegRespError */
        Dcm_GddNegRespError = DCM_E_GENERALREJECT;
          Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
        /* Invoke callout Dcm_ProcessRequestUpload with OpStatus DCM_CANCEL */
        (void) Dcm_ProcessRequestUpload(DCM_CANCEL, LucDataForId,
          LulMemoryAddress, LulMemorySize, &LulBlockLength,
            &LddNegativeErrorCode);
        /* Set Force responsepending flag to False */
        Dcm_ServiceForcePendingStatus.
        ucUlForcePendingStatus = DCM_FALSE;
      }
    }
    else
    {
      /* Update Dcm_GddNegRespError */
      Dcm_GddNegRespError = LddNegativeErrorCode;
    }
  }

  if((Dcm_MemServicePendingStatus.ucUlPendingStatus ==
    DCM_FALSE) &&
   (Dcm_ServiceForcePendingStatus.ucUlForcePendingStatus
    == DCM_FALSE) &&  (Dcm_GddOpStatus != DCM_CANCEL))
  {
    Dcm_GddOpStatus = DCM_INITIAL;
    Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_FALSE;    
    if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
    {
      Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
    }
    else
    {
      /* Update positive response */
      pMsgContext->resDataLen = DCM_FIVE;
      pMsgContext->resData[DCM_ZERO] = DCM_SIXTY_FOUR;
      pMsgContext->resData[DCM_ONE] =
        (uint8)((Dcm_GulBlockLength) >> DCM_TWENTYFOUR);
      pMsgContext->resData[DCM_TWO] =
        (uint8)((Dcm_GulBlockLength) >> DCM_SIXTEEN);
      pMsgContext->resData[DCM_THREE] =
        (uint8)((Dcm_GulBlockLength) >> DCM_EIGHT);
      pMsgContext->resData[DCM_FOUR] =
        (uint8)(Dcm_GulBlockLength);
    }
    
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
  else if(Dcm_ServiceForcePendingStatus.
    ucUlForcePendingStatus == DCM_TRUE)
  {
    /* Update the negative response service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
     /* Update the service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ONE] =
      ((Dcm_GstMsgContext.idContext) & (DCM_BIT6_AND_MASK));
     /* Update the NRC in the response buffer */
    Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;
    
    /* Update the bit flag for negative response to TRUE */
    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    
    /* Send response from main function */
    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
  else
  {
    /* To Avoid QAC Warning */
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmTransferData                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_DcmTransferData service is used to transfer     **
**                        Data during a download or upload process.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
** Remarks              : Global Variable(s) :Dcm_GddNegRespError,            **
**                        Dcm_GusMaxNoOfForceRespPend ,Dcm_GddOpStatus        **
**                        Dcm_MemServicePendingStatus ,Dcm_GpWriteData        **
**                        Dcm_ServiceForcePendingStatus ,                     **
**                        Dcm_GblDownLoadActive ,Dcm_GblUpLoadActive          **
**                        Dcm_GulBlockLength ,Dcm_GucBlockSeqCounter,         **
**                        Dcm_GblBlockSeqCounterRepeated,                     **
**                        Dcm_GulNumOfBytesToBeTransfer,                      **
**                        Dcm_GulTransferResponseLength                       **
**                        Function(s) invoked :                               **
**                        Dcm_DcmUpLoadCall, Dcm_ExternalSetNegResponse ,     **
**                        Dcm_ExternalProcessingDone.                         **
**                        Function(s) invoked :                               **
**                        Dcm_DownLoadTransferCall, Dcm_UpLoadTransferCall,   **
**                        Dcm_ExternalSetNegResponse ,                        **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
#if(DCM_TRANSFER_DATA_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmTransferData(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  uint32 LulReqDataLength;
  uint16 LusBlockSeqCounter;
  boolean LblDownLoadActive;
  boolean LblUpLoadActive;
  boolean LblSequenceResponse;
  boolean LblUpTransferDataApiInvoked;

  /* Initialize global variables */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
  Dcm_GddOpStatus = DCM_INITIAL;
  LblUpTransferDataApiInvoked = DCM_FALSE;

  /* Set response pending flag to False */
  Dcm_MemServicePendingStatus.ucTransferDataPendingStatus =
    DCM_FALSE;
  /* Set ForceRcrrp Pending flag to False */
  Dcm_ServiceForcePendingStatus.
    ucTransferDataForcePendingStatus = DCM_FALSE;

  LblSequenceResponse = DCM_FALSE;
  /* Update DownLoad and UpLoad Active flags */
  LblDownLoadActive = Dcm_GblDownLoadActive;
  LblUpLoadActive = Dcm_GblUpLoadActive;

  /* Get Requested data from request */
  LpReqResData = pMsgContext->reqData;
  /* Get Requested data length from request */
  LulReqDataLength = pMsgContext->reqDataLen;

  /* Get block sequence counter from the request */
  LusBlockSeqCounter = *(LpReqResData);

  /* Update data to transfer if DownLoad is active */
  if(LblDownLoadActive == DCM_TRUE)
  {
    /* MISRA Rule        : 17.4
      Message            : Increment or decrement operation
                           performed on pointer
      Reason             : Increment operator not used
                           to achieve better throughput.
      Verification       : However, part of the code
                           is verified manually and
                           it is not having any impact.
    */
    LpReqResData++;
    Dcm_GpWriteData = LpReqResData;
  }

  /* check for DownLoad or UpLoad activation */
  if((LblDownLoadActive == DCM_TRUE) || (LblUpLoadActive == DCM_TRUE))
  {

    /* check for length of request In case of Download */
    if((LblDownLoadActive == DCM_TRUE) &&
      (LulReqDataLength > (Dcm_GulBlockLength - DCM_ONE)))
    {
      /* set NRC IncorrectMessageLengthOrInvalidFormat */
      Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    /* check for length of request In case of UpLoad */
    else if((LblUpLoadActive == DCM_TRUE) && (LulReqDataLength != DCM_ONE))
    {
      /* set NRC IncorrectMessageLengthOrInvalidFormat */
      Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    /* Update Block Sequence Counter */
    /* polyspace +1 MISRA-C3:10.7 [Justified:Low] "Not a defect" */
    else if(LusBlockSeqCounter == (Dcm_GucBlockSeqCounter - DCM_ONE))
    {
      /* set a flag to indicate BlockSequenceCounter repeated */
      Dcm_GblBlockSeqCounterRepeated = DCM_TRUE;
    }
    /* check for Block Sequence Counter */
    else if(((LusBlockSeqCounter != DCM_ONE) &&
      (LusBlockSeqCounter != Dcm_GucBlockSeqCounter) &&
      (Dcm_GblBlockSeqCounterRepeated == DCM_FALSE)) ||
      ((LusBlockSeqCounter == DCM_ONE) &&
        (LusBlockSeqCounter != Dcm_GucBlockSeqCounter)))
    {
      /* set NRC WrongBlockSequenceCounter */
      Dcm_GddNegRespError = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
    }
    else if(Dcm_GulNumOfBytesToBeTransfer == DCM_ZERO)
    {
      /* set NRC RequestSequenceError */
      Dcm_GddNegRespError = DCM_E_REQUESTSEQUENCEERROR;
    }
    else if((LblDownLoadActive == DCM_TRUE) &&
      ((pMsgContext->reqDataLen - (DCM_ONE)) > Dcm_GulNumOfBytesToBeTransfer))
    {
      /* set NRC RequestOutOfRange */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      /* Do Nothing */
    }
  }
  else
  {
    /* set NRC RequestSequenceError */
    Dcm_GddNegRespError = DCM_E_REQUESTSEQUENCEERROR;
  }
  /* Check to find block sequence counter is repeated or not */
  if((Dcm_GblBlockSeqCounterRepeated == DCM_TRUE) &&
    (Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE))
  {
    pMsgContext->resData[0] = (uint8)LusBlockSeqCounter;

    /* Update Dcm_GblBlockSeqCounterRepeated */
    Dcm_GblBlockSeqCounterRepeated = DCM_FALSE;

    LblSequenceResponse = DCM_TRUE;
  }
  else
  {
    /* for QAC */
  }
  
  if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
  {
    if(LblSequenceResponse == DCM_FALSE)
    {
      /* Transfer data in case of DownLoad */
      if(LblDownLoadActive == DCM_TRUE)
      {
        #if(DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
        LblUpTransferDataApiInvoked = DCM_TRUE;
        /* Invoke Dcm_WriteMemory callout */
        Dcm_DownLoadTransferCall(pMsgContext);
        #endif
      }
      /* Transfer data in case of UpLoad */
      if(LblUpLoadActive == DCM_TRUE)
      {

        #if(DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
        LblUpTransferDataApiInvoked = DCM_TRUE;
        /* Invoke Dcm_ReadMemory callout */
        Dcm_UpLoadTransferCall(pMsgContext);
        #endif

      }
      if(Dcm_GucBlockSeqCounter == DCM_MAXVALUE)
      {
        /* Update Dcm_GucBlockSeqCounter */
        Dcm_GucBlockSeqCounter = DCM_ZERO;
      }
      else
      {
        /* Update Dcm_GucBlockSeqCounter */
        Dcm_GucBlockSeqCounter++;
      }
    }
    else
    {
      if(LblDownLoadActive == DCM_TRUE)
      {
        /* prev res is neg :
        2. Dcm_GddTransDataPosRes,multiple tran req is valid var. first request it wil be init~*/
        if (Dcm_GddTransDataPosRes == DCM_FALSE)
        {
          #if(DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
          LblUpTransferDataApiInvoked = DCM_TRUE;
          /* Invoke Dcm_WriteMemory callout */
		  Dcm_DownLoadTransferCall(pMsgContext);
		  #endif
        }
        else
        {
          /* Update response data length in case of DownLoad */
          pMsgContext->resDataLen = DCM_ONE;
        }
      }
      else if (LblUpLoadActive == DCM_TRUE)
      {
        /* Update response data length in case of UpLoad */
        pMsgContext->resDataLen = Dcm_GulTransferResponseLength;
      }
      else
      {
        /* QAC */
      }         
    }
  }
  else
  {
  	/* Negative */
  }


  if((LblUpTransferDataApiInvoked == DCM_FALSE)  ||
  (LblSequenceResponse == DCM_TRUE))
  {
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  DCM_UNUSED(OpStatus);
  /* TODO: return value shall be processed */
  return E_OK;
}

/*******************************************************************************
** Function Name        :Dcm_DownLoadTransferCall                             **
**                                                                            **
** Service ID           :NA                                                   **
**                                                                            **
** Description          : Dcm_DownLoadTransferCall function is used to        **
**                        invoke Dcm_WriteMemory callout.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions         :None                                                **
**                                                                            **
** Remarks               :Global Variable(s):Dcm_GddNegRespError ,            **
**                        Dcm_MemServicePendingStatus,Dcm_GulDLMemAddress     **
**                        Dcm_ServiceForcePendingStatus ,Dcm_GddOpStatus      **
**                        Dcm_GulBlockLength, Dcm_GaaWriteMemRngConfig        **
**                        Dcm_GulNumOfBytesToBeTransfer, Dcm_GaaResponseBuf   **
**                        Dcm_GusMaxNoOfForceRespPend ,Dcm_GpMsgContext       **
**                        Dcm_TxRespStatus                                    **
**                        Function(s) invoked :                               **
**                        Dcm_WriteMemory, Dcm_DslPduRTransmit ,              **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
#if(DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DownLoadTransferCall(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_WriteMemRngInfoConfigType, AUTOMATIC, DCM_APPL_CONST)
    LpWriteMemRng;
  Dcm_ReturnWriteMemoryType LddReturnValue;
  uint32 LulMemoryAddress;
  uint32 LulMemorySize;
  uint8 LucMemoryIdentifier;
  uint8 LucLoopVar;
  boolean LblMemoryFound;

  LulMemorySize = (uint32)DCM_ZERO;

  /* Update Dcm_GddNegRespError */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  LblMemoryFound = DCM_FALSE;
  
  Dcm_GddTransDataPosRes = DCM_FALSE;

  /* Set response pending flag to False */
  Dcm_MemServicePendingStatus.ucTransferDataPendingStatus =
    DCM_FALSE;
  /* Set ForceRcrrp Pending flag to False */
  Dcm_ServiceForcePendingStatus.
    ucTransferDataForcePendingStatus = DCM_FALSE;

  /* Update Memory address and memory size */
  LulMemoryAddress = Dcm_GulDLMemAddress;

  if (Dcm_GulBlockLength >= DCM_TWO)
  {
    LulMemorySize = Dcm_GulBlockLength - DCM_TWO;
  }

  /*Polyspace +2 MISRA-C3:10.1 [Justified:Low] "Not a defect" */
  for(LucLoopVar = DCM_ZERO;
  ((LucLoopVar < Dcm_Total_Num_Write_Memory_Configured) && (DCM_FALSE == LblMemoryFound));
    LucLoopVar++)
  {
    LpWriteMemRng = &Dcm_GaaWriteMemRngConfig[LucLoopVar];
    if((LulMemoryAddress >= LpWriteMemRng->ulWriteMemRngLow) &&
          (((LulMemoryAddress + LulMemorySize) - DCM_ONE) <=
          LpWriteMemRng->ulWriteMemRngHigh))
    {
      LblMemoryFound = DCM_TRUE;
    }
  }

  LpWriteMemRng = &Dcm_GaaWriteMemRngConfig[LucLoopVar - DCM_ONE];
  /* Get Configured Memory Identifier */
  LucMemoryIdentifier = LpWriteMemRng->ucWriteMemoryIdentifier;

  /* Invoke callout Dcm_WriteMemory  */
  LddReturnValue = Dcm_WriteMemory(Dcm_GddOpStatus, LucMemoryIdentifier,
    LulMemoryAddress, ((pMsgContext->reqDataLen) - DCM_ONE), Dcm_GpWriteData);
  /* check for OpStatus */
  if(Dcm_GddOpStatus != DCM_CANCEL)
  {
    if(LddReturnValue == DCM_WRITE_OK)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_INITIAL;

      Dcm_GddTransDataPosRes = DCM_TRUE;

      /* Update Response data Length */
      pMsgContext->resDataLen = DCM_ONE;
      /* Update Response data */
      pMsgContext->resData[DCM_ZERO] = pMsgContext->reqData[DCM_ZERO];
      /* Update Dcm_GulNumOfBytesToBeTransfer */
      Dcm_GulNumOfBytesToBeTransfer = (Dcm_GulNumOfBytesToBeTransfer -
        ((pMsgContext->reqDataLen) - DCM_ONE));
      /* Update Dcm_GulDLMemAddress */
      Dcm_GulDLMemAddress = Dcm_GulDLMemAddress + ((pMsgContext->reqDataLen) - DCM_ONE); 
    }
    else if(LddReturnValue == DCM_WRITE_PENDING)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_PENDING;
      /* Set response pending flag to True */
      Dcm_MemServicePendingStatus.
      ucTransferDataPendingStatus = DCM_TRUE;
    }
    else if(LddReturnValue == DCM_WRITE_FORCE_RCRRP)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_FORCE_RCRRP_OK;
      /* Set Force responsepending flag to True */
      Dcm_ServiceForcePendingStatus.
        ucTransferDataForcePendingStatus = DCM_TRUE;
      /* Update Dcm_GusMaxNoOfForceRespPend */
      Dcm_GusMaxNoOfForceRespPend++;
      /* Check if Dcm_GusMaxNoOfForceRespPend reaches configured limit */
      /* 0xFF : limit threshold is unused */
      if(Dcm_GusMaxNoOfForceRespPend > (uint16)Dcm_diag_Resp_Max_Num_Respend)
      {
        /* Update Dcm_GddOpStatus */
        Dcm_GddOpStatus = DCM_INITIAL;
        /* Update Dcm_GddNegRespError */
        Dcm_GddNegRespError = DCM_E_GENERALREJECT;
          Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
        /* Invoke callout Dcm_WriteMemory with OpStatus DCM_CANCEL */
        (void) Dcm_WriteMemory(DCM_CANCEL, LucMemoryIdentifier,
          LulMemoryAddress, LulMemorySize, Dcm_GpWriteData);
        /* Set Force responsepending flag to false */
        Dcm_ServiceForcePendingStatus.
          ucTransferDataForcePendingStatus = DCM_FALSE;
      }
      else
      {

      }
    }
    else
    {
      /* Update Dcm_GddNegRespError */
      Dcm_GddNegRespError = DCM_E_GENERALPROGRAMMINGFAILURE;
    }
  }

  if((Dcm_MemServicePendingStatus.
  ucTransferDataPendingStatus == DCM_FALSE) &&
  (Dcm_ServiceForcePendingStatus.
  ucTransferDataForcePendingStatus == DCM_FALSE) && (Dcm_GddOpStatus != DCM_CANCEL))
  {
    Dcm_GddOpStatus = DCM_INITIAL;
     
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
  else if(Dcm_ServiceForcePendingStatus.
    ucTransferDataForcePendingStatus == DCM_TRUE)
  {
    /* Update the negative response service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
     /* Update the service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ONE] =
      ((Dcm_GstMsgContext.idContext) & (DCM_BIT6_AND_MASK));
     /* Update the NRC in the response buffer */
    Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;    
    /* Update the bit flag for negative response to TRUE */
    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;

    /* Send response from main function */
    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
  else
  {
    /* To Avoid QAC Warning */
  }
}
#endif

/*******************************************************************************
** Function Name         : Dcm_UpLoadTransferCall                             **
**                                                                            **
** Service ID            : NA                                                 **
**                                                                            **
** Description           : Dcm_UpLoadTransferCall function is used to invoke  **
**                         Dcm_ReadMemory callout                             **
**                                                                            **
** Sync/Async            : Synchronous                                        **
**                                                                            **
** Re-entrancy           : Non Reentrant                                      **
**                                                                            **
** Input Parameters      : None                                               **
**                                                                            **
** InOut parameter       : pMsgContext                                        **
**                                                                            **
** Output Parameters     : None                                               **
**                                                                            **
** Return parameter      : void                                               **
**                                                                            **
** Preconditions         :None                                                **
**                                                                            **
** Remarks               :Global Variable(s):Dcm_GddNegRespError ,            **
**                        Dcm_MemServicePendingStatus ,                       **
**                        Dcm_ServiceForcePendingStatus ,                     **
**                        Dcm_GulULMemAddress ,Dcm_GulBlockLength             **
**                        Dcm_GaaReadMemRngConfig,Dcm_GddOpStatus             **
**                        Dcm_GulNumOfBytesToBeTransfer ,                     **
**                        Dcm_GusMaxNoOfForceRespPend ,Dcm_GpMsgContext       **
**                        Dcm_GaaResponseBuf ,Dcm_TxRespStatus                **
**                        Function(s) invoked :                               **
**                        Dcm_ReadMemory, Dcm_DslPduRTransmit ,               **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
#if(DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_UpLoadTransferCall(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_ReadMemRngInfoConfigType, AUTOMATIC, DCM_APPL_CONST)
    LpReadMemRng;
  Dcm_ReturnReadMemoryType LddReturnValue;
  uint32 LulMemoryAddress;
  uint32 LulMemorySize;
  uint8 LucMemoryIdentifier;
  uint8 LucLoopVar;
  boolean LblMemoryFound;


  /* Update Dcm_GddNegRespError*/
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  LblMemoryFound = DCM_FALSE;

  /* Set response pending flag to False */
  Dcm_MemServicePendingStatus.ucTransferDataPendingStatus =
    DCM_FALSE;
  /* Set ForceRcrrp Pending flag to False */
  Dcm_ServiceForcePendingStatus.
    ucTransferDataForcePendingStatus = DCM_FALSE;

  /* Update Memory address and memory size */
  LulMemoryAddress = Dcm_GulULMemAddress;
  LulMemorySize = Dcm_GulBlockLength - DCM_TWO;


  for(LucLoopVar = DCM_ZERO;
    ((LucLoopVar < Dcm_Total_Num_Read_Memory_Configured) && (!LblMemoryFound));
    LucLoopVar++)
  {
  /* Get Configured memory range */
    LpReadMemRng = &Dcm_GaaReadMemRngConfig[LucLoopVar];
    if((LulMemoryAddress >= LpReadMemRng->ulReadMemRngLow) &&
      (((LulMemoryAddress + LulMemorySize) - DCM_ONE) <=
      LpReadMemRng->ulReadMemRngHigh))
    {
      LblMemoryFound = DCM_TRUE;
    }

  }
  LpReadMemRng = &Dcm_GaaReadMemRngConfig[LucLoopVar - DCM_ONE];
  /* Get Configured Memory Identifier */
  LucMemoryIdentifier = LpReadMemRng->ucReadMemoryIdentifier;

  /* MISRA Rule        : 17.4
    Message            : Performing pointer arithmetic
    Reason             : Increment operator not used
                         to achieve better throughput.
    Verification       : However, part of the code
                         is verified manually and
                         it is not having any impact.
  */
  /* Invoke callout Dcm_ReadMemory  */
  LddReturnValue = Dcm_ReadMemory(Dcm_GddOpStatus, LucMemoryIdentifier,
    LulMemoryAddress, LulMemorySize, (Dcm_GstMsgContext.resData + DCM_ONE));
  /* Check for OpStatus */
  if(Dcm_GddOpStatus != DCM_CANCEL)
  {
    if(LddReturnValue == DCM_READ_OK)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_INITIAL;

      /* Update Response data */
      pMsgContext->resData[DCM_ZERO] = pMsgContext->reqData[DCM_ZERO];
      if(Dcm_GulNumOfBytesToBeTransfer >= (Dcm_GulBlockLength - DCM_TWO))
      {
        /* Update Response data Length */
        pMsgContext->resDataLen = (Dcm_GulBlockLength - DCM_ONE);
      }
      else
      {
        /* Update Response data Length */
        pMsgContext->resDataLen = (Dcm_GulNumOfBytesToBeTransfer + DCM_ONE);
      }
      /* Update Dcm_GulTransferResponseLength */
      Dcm_GulTransferResponseLength = pMsgContext->resDataLen;

      /* Update Dcm_GulNumOfBytesToBeTransfer */
      Dcm_GulNumOfBytesToBeTransfer = (Dcm_GulNumOfBytesToBeTransfer -
        ((pMsgContext->resDataLen) - DCM_ONE));
    }
    else if(LddReturnValue == DCM_READ_PENDING)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_PENDING;
      /* Set response pending flag to True */
      Dcm_MemServicePendingStatus.
      ucTransferDataPendingStatus = DCM_TRUE;
    }
    else if(LddReturnValue == DCM_READ_FORCE_RCRRP)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_FORCE_RCRRP_OK;
      /* Set Force responsepending flag to True */
      Dcm_ServiceForcePendingStatus.
        ucTransferDataForcePendingStatus = DCM_TRUE;
      /* Update Dcm_GusMaxNoOfForceRespPend */
      Dcm_GusMaxNoOfForceRespPend++;
      /* Check if Dcm_GusMaxNoOfForceRespPend reaches configured limit */
      /* 0xFF : limit threshold is unused */
      if(Dcm_GusMaxNoOfForceRespPend > (uint16)Dcm_diag_Resp_Max_Num_Respend)
      {
        /* Update Dcm_GddOpStatus */
        Dcm_GddOpStatus = DCM_INITIAL;
        /* Update Dcm_GddNegRespError */
        Dcm_GddNegRespError = DCM_E_GENERALREJECT;
        /* MISRA Rule        : 17.4
          Message            : Performing pointer arithmetic
          Reason             : Increment operator not used
                               to achieve better throughput.
          Verification       : However, part of the code
                               is verified manually and
                               it is not having any impact.
        */
          Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
        /* Invoke callout Dcm_ReadMemory with OpStatus DCM_CANCEL */
        (void) Dcm_ReadMemory(DCM_CANCEL, LucMemoryIdentifier,
          LulMemoryAddress, LulMemorySize,
          (Dcm_GstMsgContext.resData + DCM_ONE));
        /* Set Force responsepending flag to False */
        Dcm_ServiceForcePendingStatus.
          ucTransferDataForcePendingStatus = DCM_FALSE;
      }
      else
      {

      }
    }
    else
    {
      /* Update Dcm_GddNegRespError */
      Dcm_GddNegRespError = DCM_E_GENERALPROGRAMMINGFAILURE;
    }
  }


  if((Dcm_MemServicePendingStatus.
  ucTransferDataPendingStatus == DCM_FALSE) &&
  (Dcm_ServiceForcePendingStatus.
  ucTransferDataForcePendingStatus == DCM_FALSE) &&
  (Dcm_GddOpStatus != DCM_CANCEL))
  {
    Dcm_GddOpStatus = DCM_INITIAL;
    
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
  else if(Dcm_ServiceForcePendingStatus.
    ucTransferDataForcePendingStatus == DCM_TRUE)
  {
    /* Update the negative response service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
     /* Update the service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ONE] =
      ((Dcm_GstMsgContext.idContext) & (DCM_BIT6_AND_MASK));
     /* Update the NRC in the response buffer */
    Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;    
    /* Update the bit flag for negative response to TRUE */
    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    
    /* Send response from main function */
    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
  else
  {
    /* To Avoid QAC Warning */
  }
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmRequestTransferExit                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_DcmRequestTransferExit service is used to       **
**                        terminate a download or upload process              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None.                                               **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_GddNegRespError ,           **
**                        Dcm_GusMaxNoOfForceRespPend ,Dcm_GddOpStatus        **
**                        Dcm_MemServicePendingStatus ,                       **
**                        Dcm_GblDownLoadActive , Dcm_GblUpLoadActive         **
**                        Function(s) invoked :                               **
**                        Dcm_RequestTransferExitCall,                        **
**                        Dcm_ExternalSetNegResponse ,                        **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
#if(DCM_TRANSFER_EXIT_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmRequestTransferExit(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  boolean LblTransferExitDataApiInvoked;

  /* Initialize global variables */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
  Dcm_GddOpStatus = DCM_INITIAL;
  /* Set response pending flag to False */
  Dcm_MemServicePendingStatus.ucTransferExitPendingStatus =
    DCM_FALSE;
  /* Set ForceRcrrp Pending flag to False */
  Dcm_ServiceForcePendingStatus.
    ucTransferExitForcePendingStatus = DCM_FALSE;

  LblTransferExitDataApiInvoked = DCM_FALSE;

  /* Check for requested data length */
  if(pMsgContext->reqDataLen != DCM_ZERO)
  {
    /* set NRC Incorrect Message length */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    /* Update Dcm_GblDownLoadActive */
    Dcm_GblDownLoadActive = DCM_FALSE;
    /* Update Dcm_GblUpLoadActive */
    Dcm_GblUpLoadActive = DCM_FALSE;
  }
  else
  {

    /* check for DownLoad and UpLoad activation */
    if((Dcm_GblDownLoadActive == DCM_FALSE) &&
    (Dcm_GblUpLoadActive == DCM_FALSE))
    {
      /* set NRC RequestSequenceError */
      Dcm_GddNegRespError = DCM_E_REQUESTSEQUENCEERROR;
    }
  }

  if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
  {
    /* Invoke TransferExit callout */
    Dcm_RequestTransferExitCall(pMsgContext);
    LblTransferExitDataApiInvoked = DCM_TRUE;
  }
  if(LblTransferExitDataApiInvoked == DCM_FALSE)
  {
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  DCM_UNUSED(OpStatus);
  /* TODO: return value shall be processed */
  return E_OK;  
}

/*******************************************************************************
** Function Name        : Dcm_RequestTransferExitCall                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dcm_RequestTransferExitCall function is used to     **
**                        invoke Dcm_ProcessRequestTransferExit callout       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): Dcm_GddNegRespError ,           **
**                        Dcm_MemServicePendingStatus ,                       **
**                        Dcm_ServiceForcePendingStatus ,                     **
**                        Dcm_GddOpStatus , Dcm_GblDownLoadActive             **
**                        Dcm_GblUpLoadActive ,Dcm_GddNegRespError            **
**                        Dcm_GaaResponseBuf , Dcm_TxRespStatus               **
**                        Function(s) invoked :                               **
**                        Dcm_ProcessRequestTransferExit, Dcm_DslPduRTransmit **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone.                         **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_RequestTransferExitCall(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{

  uint32 LulParameterRecordSize;
  Dcm_NegativeResponseCodeType LddNegativeErrorCode;

  Std_ReturnType LddReturnValue;

  LulParameterRecordSize = DCM_ZERO;
  /* Update Dcm_GddNegRespError */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  LddNegativeErrorCode = DCM_E_POSITIVERESPONSE;

  /* Set response pending flag to False */
  Dcm_MemServicePendingStatus.ucTransferExitPendingStatus =
    DCM_FALSE;
  /* Set ForceRcrrp Pending flag to False */
  Dcm_ServiceForcePendingStatus.
    ucTransferExitForcePendingStatus = DCM_FALSE;

  /* Invoke callout Dcm_WriteMemory  */
  LddReturnValue = Dcm_ProcessRequestTransferExit(Dcm_GddOpStatus,
    &pMsgContext->resData[DCM_ZERO], &LulParameterRecordSize,
    &LddNegativeErrorCode);
  /* Check for OpStatus */
  if(Dcm_GddOpStatus != DCM_CANCEL)
  {
    if(LddReturnValue == E_OK)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_INITIAL;
      /* Update Response data length */
      pMsgContext->resDataLen = LulParameterRecordSize;
      /* Clear Dcm_GblDownLoadActive flag */
      Dcm_GblDownLoadActive = DCM_FALSE;
      /* Clear Dcm_GblUpLoadActive flag */
      Dcm_GblUpLoadActive = DCM_FALSE;

    }
    else if(LddReturnValue == DCM_E_PENDING)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_PENDING;
      /* Set response pending flag to True */
      Dcm_MemServicePendingStatus.
      ucTransferExitPendingStatus = DCM_TRUE;
    }
    else if(LddReturnValue == DCM_E_FORCE_RCRRP)
    {
      /* Update Dcm_GddOpStatus */
      Dcm_GddOpStatus = DCM_FORCE_RCRRP_OK;
      /* Set Force responsepending flag to True */
      Dcm_ServiceForcePendingStatus.
        ucTransferExitForcePendingStatus = DCM_TRUE;
      /* Update Dcm_GusMaxNoOfForceRespPend */
      Dcm_GusMaxNoOfForceRespPend++;
      /* Check if Dcm_GusMaxNoOfForceRespPend reaches configured limit */
      /* 0xFF : limit threshold is unused */
      if(Dcm_GusMaxNoOfForceRespPend > (uint16)Dcm_diag_Resp_Max_Num_Respend)
      {
        /* Update Dcm_GddOpStatus */
        Dcm_GddOpStatus = DCM_INITIAL;
        /* Update Dcm_GddNegRespError */
        Dcm_GddNegRespError = DCM_E_GENERALREJECT;
          Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;
        /* Invoke callout Dcm_WriteMemory with OpStatus DCM_CANCEL */
        (void) Dcm_ProcessRequestTransferExit(DCM_CANCEL,
          &pMsgContext->resData[DCM_ZERO],
          &LulParameterRecordSize, &LddNegativeErrorCode);
        /* Set Force responsepending flag to False */
        Dcm_ServiceForcePendingStatus.
          ucTransferExitForcePendingStatus = DCM_FALSE;
      }
      else
      {
        /* Set Force pending flag to True */
      }
    }
    else
    {
      /* Update Dcm_GddNegRespError */
      Dcm_GddNegRespError = LddNegativeErrorCode;
    }
  }

  /* Transmit Positive response and Negative response */
  if((Dcm_MemServicePendingStatus.
  ucTransferExitPendingStatus == DCM_FALSE) &&
    (Dcm_ServiceForcePendingStatus.
    ucTransferExitForcePendingStatus == DCM_FALSE) &&
    (Dcm_GddOpStatus != DCM_CANCEL))
  {
    Dcm_GddOpStatus = DCM_INITIAL;
    
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
  /* To transmit Response pending NRC in case of Force response pending */
  else if(Dcm_ServiceForcePendingStatus.
    ucTransferExitForcePendingStatus == DCM_TRUE)
  {
    /* Update the negative response service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ZERO] = DCM_NEGATIVE_RESPONSE_SID;
    /* Update the service Id in the response buffer */
    Dcm_GaaResponseBuf[DCM_ONE] =
      ((pMsgContext->idContext) & (DCM_BIT6_AND_MASK));
    /* Update the NRC in the response buffer */
    Dcm_GaaResponseBuf[DCM_TWO] = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;    
    /* Update the bit flag for negative response to TRUE */
    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    
    /* Send response from main function */
    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
  else
  {
    /* Update Dcm_GddOpStatus */
    Dcm_GddOpStatus = DCM_PENDING;
  }
}
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/*
polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard-Chap 5.1.2)
*/
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
