/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DspNonPagedDTCSubFct.c                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions of the Read DTC            **
**              subfunctions  0x01, 0x07, 0x11, 0x12, 0x0B, 0x0C, 0x0D, 0x0E, **
**              and 0x05 that do not require paged processing                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.5     13-09-2018    Y.S     Jeon     #14010                            **
**                                                                            **
** 1.0.4     31-10-2017    YoungJin Yun     #7623                             **
**                                                                            **
** 1.0.3     03-03-2016    Sungeol Baek     #3754                             **
**                                                                            **
** 1.0.2     16-04-2015    Sungeol Baek     #2171                             **
**                                                                            **
** 1.0.1     04-03-2015    YoungJin Yun     #1689                             **
**                                                                            **
** 1.0.0     09-01-2013    Autron           Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_DspNonPagedDTCSubFct.h"
#include "Dem.h"
#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DspServices.h"
#include "Dcm_Config.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */

/*******************************************************************************
** Function Name        : Dcm_DspRptNoOfDTC                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for the service Read DTC      **
**                        information (service 0x19) to read the number of    **
**                        DTC matching a specific status mask, severity mask, **
**                        memory location and DTC type. It will be invoked    **
**                        for sub-function values 0x01, 0x07, 0x11 and 0x12   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s) :                                **
**                        Dcm_PrtclTxBufStatus, Dcm_GucReadGlobal,            **
**                        Dcm_GucAvailableDTCStatusMask, Dcm_GpReqResData,    **
**                        Dcm_GddNegRespError, Dcm_GucAvailableDTCStatusMask, **
**                        Dcm_GucTranslationType, Dcm_GpMsgContext            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dem_GetDTCStatusAvailabilityMask, Dem_SetDTCFilter, **
**                        Dcm_ExternalSetNegResponse, Dem_GetTranslationType, **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_RPT_NOOFDTC == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptNoOfDTC 
  (P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)pMsgContext)
{
  Dem_DTCSeverityType LddDTCSeverityMask = (Dem_DTCSeverityType)0x00;
  Dem_DTCOriginType LddDTCOrigin;
  Dem_FilterWithSeverityType LddFilterWithSeverity;
  Dem_DTCKindType LddDTCKind;
  Std_ReturnType LddReturnValue;
  uint8 LucDTCStatusMask = (uint8)0x00;
  
  Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;
  Dcm_GucReadGlobal = DCM_TRUE;
    
  if (
    (pMsgContext == NULL_PTR) || 
    (pMsgContext->resData == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR)
  )
  {
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* Update variable as DCM_ZERO */
    Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

    /* Check whether sub function requested is 0x07 */
    if(Dcm_GucSubFunction == DCM_REP_NUMOFDTC_BY_SEVERITYMASK)
    {
      LddFilterWithSeverity = (Dem_FilterWithSeverityType)DEM_FILTER_WITH_SEVERITY_YES;
      LddDTCSeverityMask = pMsgContext->reqData[DCM_ONE];
      LucDTCStatusMask = pMsgContext->reqData[DCM_TWO];
    }
    /* Without severity, For Sub function 0x01, 0x11, 0x12 */
    else
    {
      LddFilterWithSeverity = DEM_FILTER_WITH_SEVERITY_NO;
      LddDTCSeverityMask = DEM_SEVERITY_NO_SEVERITY;

      /* Get information of DTC StatusMask */
      LucDTCStatusMask = pMsgContext->reqData[DCM_ONE];
    }

    /* Update the origin to Primary Memory */
    if(Dcm_GucSubFunction == DCM_REP_NUMOFMMDTC_BY_STATUSMASK)
    {
      /* Update origin as primary for service 0x11 */
      LddDTCOrigin = DEM_DTC_ORIGIN_MIRROR_MEMORY;
    }
    else
    {
      /* Update origin as primary for service 0x01, 0x07, 0x12 */
      LddDTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    }

    /* Get the DTC status information supported by the DEM */

    /* Check whether the DTC status mask was successfully obtained */
    /* Check for Sub function 0x01, 0x07, 0x11 */
    if(Dcm_GucSubFunction != DCM_REP_NUMOFEMIOBDDTC_BY_STATUSMASK)
    {
     /* Update DTC kind as all */
     LddDTCKind = DEM_DTC_KIND_ALL_DTCS;
    }
    /* Check for Sub function 0x12 */
    else
    {
     /* Update DTC kind as emission related  */
     LddDTCKind = DEM_DTC_KIND_EMISSION_REL_DTCS;
    }

    LddReturnValue = Dem_GetDTCStatusAvailabilityMask(&Dcm_GucAvailableDTCStatusMask);
    if (LddReturnValue == E_OK)
    {
      /* Get the Translation type */
      Dcm_GucTranslationType = Dem_GetTranslationType();
      /* Check Whether Transalation type supported or not */
      if(
        (Dcm_GucTranslationType == DEM_DTC_TRANSLATION_ISO15031_6)  ||        /* 0x00 */
        (Dcm_GucTranslationType == DEM_DTC_TRANSLATION_ISO14229_1)  ||        /* 0x01 */
        (Dcm_GucTranslationType == DEM_DTC_TRANSLATION_SAEJ1939_73) ||        /* 0x02 */
        (Dcm_GucTranslationType == DEM_DTC_TRANSLATION_ISO11992_4)  ||        /* 0x03 */
        (Dcm_GucTranslationType == DEM_DTC_TRANSLATION_J2012DA_FORMAT_04) )   /* 0x04 */
      {
        if((LucDTCStatusMask != DCM_ZERO) && ((Dcm_GucAvailableDTCStatusMask & LucDTCStatusMask) != DCM_ZERO))
        {
          LddReturnValue = Dem_SetDTCFilter((Dcm_GucAvailableDTCStatusMask &
          LucDTCStatusMask), LddDTCKind, DEM_DTC_FORMAT_UDS, LddDTCOrigin,
          LddFilterWithSeverity, LddDTCSeverityMask, (uint8)DEM_FILTER_FOR_FDC_NO);

          /* Check if the filter was accepted */
          if(LddReturnValue == DEM_FILTER_ACCEPTED)
          {
            Dcm_DemGetNumberOfFilteredDtc(pMsgContext);
          }
          /* [SWS_Dcm_01043]
           * If DEM_WRONG_FILTER value is returned from 
           * Dem_ReturnSetFilterType, the Dcm module shall send a negative response with 
           * NRC 0x31 (Request out of range). */
          else if (DEM_WRONG_FILTER == LddReturnValue)
          {
            Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
          }
          else
          {
            /* For QAC Check */
            Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
          }
        }
        else
        {
          /* Update the response data length */
          pMsgContext->resDataLen = DCM_FIVE;

          /* Update sub-function number */
          pMsgContext->resData[0U] = Dcm_GucSubFunction;

          /* Update DTC status availabilityMask */
          pMsgContext->resData[1U] = Dcm_GucAvailableDTCStatusMask;

          /* Get Format Identifier */
          pMsgContext->resData[2U] = Dcm_GucTranslationType;

          /* Update DTC CountHighByte */
          pMsgContext->resData[3U] = DCM_ZERO;

          /* Update DTC CountLowByte */
          pMsgContext->resData[4U] = DCM_ZERO;
        
          /* Update the global variable to indicate that no NRC has occurred */
          Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
        }
      }
      else
      {
        /* For QAC Check */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
    else 
    {    
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }

  if(Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus == DCM_FALSE)
  {
    #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
    if(Dcm_GucResOnEventStatus == DCM_ROEONGOING)
    {
      if (Dcm_GddNegRespError != DCM_E_POSITIVERESPONSE)
      {
        Dcm_ExternalSetNegResponse(pMsgContext, Dcm_GddNegRespError);
      }    
      Dcm_ExternalProcessingDone(pMsgContext);
    }
    else
    #endif
    {
      /* Send response from main function */
      /* polyspace +1 MISRA-C3:10.3 [Justified:Low] "Not a defect" */
      Dcm_GblSendResponse = DCM_TRUE;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DemGetNumberOfFilteredDtc                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is a internal function for sub-function of the **
**                        service 0x19 to get the number of filtered DTC      **
**                        It will be invoked for sub-function values          **
**                        0x01, 0x07, 0x11 and 0x12                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s) :                                **
**                        Dcm_PrtclTxBufStatus, Dcm_GpMsgContext,             **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GucAvailableDTCStatusMask, Dcm_TxRespStatus     **
**                        Dcm_GucTranslationType                              **
**                        Function(s) invoked :                               **
**                        Dem_GetNumberOfFilteredDTC                          **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DemGetNumberOfFilteredDtc
  (P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{

  Dem_ReturnGetNumberOfFilteredDTCType LddNumFilteredDTCType;
  /* MISRA Rule : 18.4
     Message : Unions shall not be used.
     Reason : For optimization.
     Verification : However, part of the code is verified
                    manually and it is not having any impact.
  */
  Tun_DcmWord16 LunDcmWord16;
  uint16 LusNumberOfFilteredDTC = (uint16)0x00;

  Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;

  if (
    (pMsgContext == NULL_PTR) || 
    (pMsgContext->resData == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR)
  )
  {
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* Get the number of DTC matching the defined status mask */
    LddNumFilteredDTCType = Dem_GetNumberOfFilteredDTC(&LusNumberOfFilteredDTC);  
    
     /* Check whether getting number of DTC was successful */
    if(LddNumFilteredDTCType == DEM_NUMBER_OK)
    {
      /* Update the response data length */
      pMsgContext->resDataLen = DCM_FIVE;
      
      /*Response for the service 0x01, 0x07, 0x11 Subfunction +
        DTCStatusAvailabilityMask + DTCFormatIdentifier + DTC count */

      /* Update number of DTC matching the defined status mask */
      LunDcmWord16.usWordReg16 = LusNumberOfFilteredDTC;

      /* polyspace +15 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      /* Update sub-function number */
      pMsgContext->resData[0U] = Dcm_GucSubFunction;
  
      /* Update DTC status availabilityMask */
      pMsgContext->resData[1U] = Dcm_GucAvailableDTCStatusMask;
  
      /* Get Format Identifier */
      pMsgContext->resData[2U] = Dcm_GucTranslationType;
  
      /* Update DTC CountHighByte */
      pMsgContext->resData[3U] = LunDcmWord16.ddByte.ucMsByte;
  
      /* Update DTC CountLowByte */
      pMsgContext->resData[4U] =  LunDcmWord16.ddByte.ucLsByte;
  
      /* Update the global variable to indicate that no NRC has occurred */
      Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

    }
    else if(LddNumFilteredDTCType == DEM_NUMBER_PENDING)
    {
      /* Set the Flag for returning of DCM_E_PENDING */
      Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_TRUE;
      Dcm_TxRespStatus.ucNormResponse = DCM_TRUE;
    }
    else
    {
      /* For QAC Check */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspRptFailedConfirmedDTCInfo                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for service Read DTC          **
**                        information (service 0x19) to read the DTCs and the **
**                        associated status information for the first test    **
**                        failed, first test confirmed, most recent test      **
**                        failed, most recent confirmed DTCs. It will be      **
**                        invoked for sub-function values 0x0B, 0x0C, 0x0D    **
**                        and 0x0E                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GpReqResData,                                   **
**                        Dcm_GucReadGlobal, Dcm_GpMsgContext,                **
**                        Dcm_GddNegRespError, Dcm_GunDTC                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dem_GetStatusOfDTC, Dcm_ExternalSetNegResponse      **
**                        Dem_GetDTCStatusAvailabilityMask,                   **
**                        Dem_GetDTCByOccurrenceTime                          **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_FAILEDCONFIRMEDDTCINFO == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptFailedConfirmedDTCInfo(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType LddReturnValue;
  /* Initialize the array with request type for Dem_GetDTCByOccurrenceTime */
  uint8 LaaDTCType[DCM_FOUR] = {
    DEM_FIRST_FAILED_DTC,
    DEM_FIRST_DET_CONFIRMED_DTC,
    DEM_MOST_RECENT_FAILED_DTC,
    DEM_MOST_REC_DET_CONFIRMED_DTC
  };
  uint8 LucDTCStatus = (uint8)0x00;
  uint8 LucDTCStatusMask = (uint8)0x00;

  Dcm_GucReadGlobal = DCM_TRUE;

  if (
    (pMsgContext == NULL_PTR) || 
    (pMsgContext->resData == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR)
  )
  {
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    uint8 idx = pMsgContext->reqData[0U] - DCM_FAILED_CONFMD_IDX;

    /* Get the DTC status information supported by the DEM */
    LddReturnValue = Dem_GetDTCStatusAvailabilityMask(&LucDTCStatusMask);

    /* Check whether the DTC status mask was successful */
    if (
      (idx < 4U) && 
      (LddReturnValue == E_OK)
    )
    {
      LddReturnValue = Dem_GetDTCByOccurrenceTime (LaaDTCType[idx], &Dcm_GunDTC.ulLongReg32);
      
      /* Check whether status of DTC was OK */
      if(LddReturnValue == DEM_OCCURR_OK)
      {
        /* Get the status of DTC */
        LddReturnValue = Dem_GetStatusOfDTC (
          Dcm_GunDTC.ulLongReg32,
          DEM_DTC_ORIGIN_PRIMARY_MEMORY, 
          &LucDTCStatus
        );
        
        /* Check whether status of DTC was OK */
        if(LddReturnValue == DEM_STATUS_OK)
        {
          /* Update the response data length to the pMsgContext */
          pMsgContext->resDataLen = 6U;

          /* update sub-function number */
          pMsgContext->resData[0U] = Dcm_GucSubFunction;
          /* DTCStatusAvailabilityMask */
          pMsgContext->resData[1U] = LucDTCStatusMask;
          /* DTCHighByte */
          pMsgContext->resData[2U] = Dcm_GunDTC.ddByte.ucMidHiByte;
          /* DTCMiddleByte */
          pMsgContext->resData[3U] = Dcm_GunDTC.ddByte.ucMidLowByte;
          /* DTCLowByte */
          pMsgContext->resData[4U] = Dcm_GunDTC.ddByte.ucLsByte;
          /* DTCStatusMask */
          pMsgContext->resData[5U] = LucDTCStatus;
          
          /* Update the global variable indicating no NRC is reported */
          Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        }
      }
      else if(LddReturnValue == DEM_OCCURR_NOT_AVAILABLE)
      {
        /* Fixed by youngjin.yun,2014-12-15, DTCStatusAvailabilityMask shall be included */
        /* Update the response data length to the pMsgContext */
        pMsgContext->resDataLen = 2U;

        /* Empty response message */
        /* update sub-function number */
        pMsgContext->resData[0] = Dcm_GucSubFunction;
        pMsgContext->resData[1] = LucDTCStatusMask;
      }
      else
      {
        /* To avoid qac */
      }
    }
    else
    {
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  
  /* Send response from main function */
  /* polyspace +1 MISRA-C3:10.3 [Justified:Low] "Not a defect" */
  Dcm_GblSendResponse = DCM_TRUE;
}
#endif /* (DCM_RPT_FAILEDCONFIRMEDDTCINFO == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DspRptDTCSnapshotRecByRecordNum                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for service Read DTC          **
**                        information (service 0x19) to read the snapshot     **
**                        records and extended records for a particular DTC   **
**                        or a particular record. This service will be        **
**                        invoked for sub-function value 0x05                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GpReqResData, Dcm_GucReadGlobal                 **
**                        Dcm_GucReadGlobal,                                  **
**                        Dcm_GddNegRespError,                                **
**                        Dcm_GucDTCStatus, Dcm_GunDTC, Dcm_GpMsgContext      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dem_GetFreezeFrameDataByRecord, Dem_GetStatusOfDTC, **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptDTCSnapshotRecByRecordNum(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint16 LusMaxBufferSize;
  uint16 LusCount;
  uint8 LucRecordNumber;
  uint8 LucReturnRes;
  uint8 LddDTCStatus;

  Dcm_GucReadGlobal = DCM_TRUE;
  if (
    (pMsgContext == NULL_PTR) || 
    (pMsgContext->resData == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR)
  )
  {
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    CONST(uint16, DCM_CONST) DCM_HDR_SIZE = 6U;
    
    Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
    
    /* Get the record number from the request message */
    LucRecordNumber = pMsgContext->reqData[1U]; 
    
    LusMaxBufferSize = (uint16)(pMsgContext->resMaxDataLen - DCM_HDR_SIZE);

    /* Check If Requested Record Number Other than 0x00 */
    if(LucRecordNumber == DCM_ZERO)
    { 
      LucReturnRes = Dem_GetFreezeFrameDataByRecord(
        LucRecordNumber,
        DEM_DTC_ORIGIN_PRIMARY_MEMORY, 
        &Dcm_GunDTC.ulLongReg32,
        &pMsgContext->resData[DCM_HDR_SIZE], 
        &LusMaxBufferSize
      );

      /* Check whether DTC is successfully returned */
      if (LucReturnRes == DEM_GET_FFBYRECORD_OK)
      {
        if (LusMaxBufferSize <= (pMsgContext->resMaxDataLen - DCM_HDR_SIZE))
        {
          Dcm_GunDTC.ulLongReg32 = Dcm_GunDTC.ulLongReg32 >> 8;
          
          LucReturnRes = Dem_GetStatusOfDTC(
            Dcm_GunDTC.ulLongReg32,
            DEM_DTC_ORIGIN_PRIMARY_MEMORY, 
            &LddDTCStatus);

          if (LucReturnRes == DEM_STATUS_OK)
          {
            /* Fill the header frame */
            
            /* Update the response data length */
            pMsgContext->resDataLen = DCM_HDR_SIZE + LusMaxBufferSize;

            /* Update DTC status availabilityMask */
            pMsgContext->resData[0U] = Dcm_GucSubFunction;

            /* Update DTC status availabilityMask */
            pMsgContext->resData[1U] = LucRecordNumber;

            /* DTC High Byte */
            pMsgContext->resData[2U] = Dcm_GunDTC.ddByte.ucMidHiByte;

            /* DTC Middle Byte */
            pMsgContext->resData[3U] = Dcm_GunDTC.ddByte.ucMidLowByte;

            /* DTC Low Byte */
            pMsgContext->resData[4U] = Dcm_GunDTC.ddByte.ucLsByte;

            /* DTC Status Mask */
            pMsgContext->resData[5U] = LddDTCStatus;

            /* Update the global variable to indicate that no NRC has occurred */
            Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
          }
          else if (
            (LucReturnRes == DEM_STATUS_WRONG_DTC) ||
            (LucReturnRes == DEM_STATUS_WRONG_DTCORIGIN)
          )
          {
            /* Update the NRc DCM_E_REQUESTOUTOFRANGE */
            Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
          }
          else
          {
            Dcm_GddNegRespError =  DCM_E_CONDITIONSNOTCORRECT;
          }
        }
        else
        {
          /* Update the NRc Condition NOt Correct */
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        }
      }
      else
      {
        /* Update the NRc Condition NOt Correct */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
    else
    {
     /* Update the NRc Request Out Of Range */
     Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
  }

  /* Send response from main function */
  Dcm_GblSendResponse = DCM_TRUE;
}
#endif /* (DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON) */

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-end MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
