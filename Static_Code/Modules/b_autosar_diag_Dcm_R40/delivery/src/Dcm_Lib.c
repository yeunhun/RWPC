/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_Lib.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for UDS services           **
**              implemented by DSP layer of Dcm module                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                Description                      **
********************************************************************************
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.6     18-06-2019    Y.S     Jeon      #17902                           **
**                                                                            **
** 1.0.5     12-09-2018    Y.S     Jeon      #13032                           **
**                                                                            **
** 1.0.4     27-03-2017    Jin     Jung      #7864                            **
**                                                                            **
** 1.0.3     28-10-2016    Jin     Jung      #6341                            **
**                                                                            **
** 1.0.2     13-10-2016    Jin     Jung      #6217                            **
**                                                                            **
** 1.0.1     30-06-2016    Jin     Jung      #5380                            **
**                                                                            **
** 1.0.0     25-05-2016    Sungeol Baek      Initial Version                  **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_PCTypes.h" 
#include "Dcm_Types.h"
#include "Dcm_Ram.h"
#include "Rte_Dcm_Type.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Config.h"
#include "Dcm_DspServices.h"
#include "Dcm_Lib.h"

/*******************************************************************************
**                      STATIC MACRO                                          **
*******************************************************************************/  

/*******************************************************************************
**                      STATIC FUNCTION DECLARATIONS                          **
*******************************************************************************/

/*******************************************************************************
**                      STATIC DATA TYPES                                     **
*******************************************************************************/

/* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > configured memory access index */

/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                STATIC FUNCTION DEFINITIONS                                 **
*******************************************************************************/

/*******************************************************************************
**                EXTERNAL FUNCTION DEFINITIONS                               **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

#if((DCM_STANDARD_SUPPORT != DCM_ES96590_SUPPORT) && (DCM_STANDARD_SUPPORT != DCM_QZN04_SUPPORT))
static void Dcm_ChkSecAccessCntDec(uint8* LpFailedSecurityAccessCount);
#endif


#if(DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
Std_ReturnType Dcm_ChkSessionLevel(Dcm_SesCtrlType ucSessionLevel)
{
  Std_ReturnType ret = E_NOT_OK;

  if ((ucSessionLevel == DCM_PROGRAMMING_SESSION) || (ucSessionLevel == DCM_ECU_PROGRAMMING_MODE_05H) ) 
  {
    ret = E_OK;
  }

  return ret;
}
#endif

Std_ReturnType Dcm_ChkSuppressPosResponse(P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) LpRxData, Dcm_MsgLenType MsgDataLen)
{
  Std_ReturnType ret = E_NOT_OK;

  /* For ES95485 support  */
  /* noResponseRequired : Subfunction 0x02 */  
  if ((LpRxData[0U] == DCM_COMMUNICATIONCONTROL) &&
      (1U == MsgDataLen) && 
      (DCM_CC_DIABLE_NM_TRANS_NORESP == LpRxData[1U]))
  {
    ret = E_OK;
  }
  /* noResponseRequired : Subfunction 0x02 */      
  else if ((LpRxData[0U] == DCM_ENABLENORMALMESSAGETRANSMISSION) &&
           (1U == MsgDataLen) && 
           (2U == LpRxData[1U]))
  {
    ret = E_OK;
  }
  else
  {}
      
  return ret;
}

#if(DCM_DSP_SECURITY_SERVICE == STD_ON)
void Dcm_ChkSecAccessCntInc(uint8* FailedSecurityAccessCount, uint8 SecNumMaxAttDelay)
{
  if(*FailedSecurityAccessCount < SecNumMaxAttDelay)
  {
    *FailedSecurityAccessCount = *FailedSecurityAccessCount + 1;
  }
}

#if((DCM_STANDARD_SUPPORT != DCM_ES96590_SUPPORT) && (DCM_STANDARD_SUPPORT != DCM_QZN04_SUPPORT))
static
#endif
void Dcm_ChkSecAccessCntDec(uint8* LpFailedSecurityAccessCount)
{
  if(*LpFailedSecurityAccessCount > (uint8)0x00)
  {
    *LpFailedSecurityAccessCount = *LpFailedSecurityAccessCount - 1;
  }
}

Std_ReturnType Dcm_SetSecAccessCntInc(uint8* LpFailedSecurityAccessCount, 
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST) LpSecData)
{
  Std_ReturnType ret = E_OK;
  /* Increment the security access count */
  *LpFailedSecurityAccessCount = *LpFailedSecurityAccessCount + 1;

  if(*LpFailedSecurityAccessCount >= LpSecData->ucSecNumMaxAttDelay)
  {
    /* Report the exceeded number of attempts NRC */
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_EXCEEDNUMBEROFATTEMPTS);                  
    DCM_START_TIMER(DCM_SECURITY_TIMER, LpSecData->usSecDelayInvKey);

    Dcm_ChkSecAccessCntDec(LpFailedSecurityAccessCount);
    /* Set global bit flag indicating the security seed request to FALSE */
    Dcm_DspSerPgStatus.ucSecSeedReq = DCM_FALSE;
    ret = E_NOT_OK;
  }

  return ret;
}

void Dcm_SetSecAccessCntDec(uint8* LpFailedSecurityAccessCount, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pNegRespError,
  P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST) LpSecData)
{
  if(*LpFailedSecurityAccessCount >= (LpSecData->ucSecNumMaxAttDelay))
  {
    /* Report the exceeded number of attempts NRC */
    *pNegRespError = DCM_E_EXCEEDNUMBEROFATTEMPTS;
    DCM_START_TIMER(DCM_SECURITY_TIMER, LpSecData->usSecDelayInvKey);
    Dcm_DspServiceProcessingSts.ucSecSeedReqPending = DCM_FALSE;
    Dcm_GddOpStatus = DCM_INITIAL;
    
    Dcm_ChkSecAccessCntDec(LpFailedSecurityAccessCount);
    /* Set global bit flag indicating the security seed request to FALSE */
    Dcm_DspSerPgStatus.ucSecSeedReq = DCM_FALSE;
  }
  else
  {
    /* Increment the security access count */
    *LpFailedSecurityAccessCount = *LpFailedSecurityAccessCount + 1;
  }
}
#endif

#if(DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_DcmEnableNormalMsgTransmission(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /*The length of the message is wrong*/
  /* #6341 Jin 161028 */
  if(pMsgContext->reqDataLen != 1U)
  {
    /* As per ES95486, conditionsNotCorrect:  wrong diagnosticService length or not supported LID */
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
  }
  else
  {
    /*
     * responseRequired of ES95486
     * 01: responseRequired,
     * 02: noResponseRequired */
    Dcm_GucSubNetValue = 0U;
    /* Update Communication mode type for DCM_ENABLE_RX_TX_NORM_NM */
    Dcm_GucCommunicationModeType = DCM_COMM_TYPE_NM_AND_NORMAL;

    /* The entire response data is only Response Service Id #69 as per ES95486 */
    pMsgContext->resDataLen = 0; /* Will be incremented as 1 when response is transmitted */
  }
  Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);

}
#endif

#if(DCM_DSP_STOP_DIAG_SESSION_SERVICE== STD_ON)   
FUNC(void, DCM_CODE) Dcm_DspInternal_DcmStopDiagnosticSession(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST) protocolCfg;

  /* polyspace +1 MISRA-C3:10.3 [Justified:Low] "Not a defect" */
  Dcm_DiagSessionState.sendPendingResp = DCM_FALSE;

  protocolCfg = Dcm_DsdInternal_GetProcotocolByRxPduId(pMsgContext->dcmRxPduId); 
  /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
  /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
  if ((NULL_PTR == protocolCfg) || (NULL_PTR == protocolCfg->pSessiontable))
  {
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
  }
  else
  {
    P2CONST(Dcm_DiagSessionConfigType, AUTOMATIC, DCM_APPL_CONST) sessionCfg = NULL_PTR;

    sessionCfg = Dcm_DsdInternal_GetSessionCfg(
      protocolCfg, DCM_DEFAULT_SESSION, &Dcm_DiagSessionState.sessionTableIndex);
    
    if (NULL_PTR != sessionCfg)
    {
      /* note : Request data length and data - excluding service identifier*/
      
      /**
       * [ES95486 4.11.2  StopDiagnosticSession positive Response]
       * Even if there would have been sent further parameters (#2 etc.) in the request, the positive response 
       * would just include them (and have the same length as the request)  */
      if (pMsgContext->reqDataLen > 0)
      {
        if (pMsgContext->resMaxDataLen < pMsgContext->reqDataLen)
        {
          pMsgContext->resDataLen = pMsgContext->resMaxDataLen;
        }
        else
        {
          pMsgContext->resDataLen = pMsgContext->reqDataLen;
        }
        Dcm_DspInternal_MemCopy(pMsgContext->resData,pMsgContext->reqData, pMsgContext->resDataLen);
      }
      else
      {
        /* response : only SID #60 */
        pMsgContext->resDataLen = 0;
      }
    }
    else
    {
      /* Never reach here */
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    }
  }

  Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
}
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

