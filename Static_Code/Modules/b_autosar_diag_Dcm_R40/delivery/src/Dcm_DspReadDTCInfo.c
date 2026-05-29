/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DspReadDTCInfo.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the implementation of the Read DTC         **
**              subfunctions  0x02, 0x0A, 0x0F, 0x13, 0x15, ,0x14, 0x08       **
**              and 0x09                                                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By              Description                        **
********************************************************************************
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.4     28-03-2017    Jin     Jung    #4718                              **
**                                                                            **
** 1.0.3     03-03-2016    Sungeol Baek    #3754, RTRT reflection             **
**                                                                            **
** 1.0.2     19-06-2015    YoungJin Yun    #2171                              **
**                                                                            **
** 1.0.1     16-04-2015    Sungeol Baek    #2171                              **
**                                                                            **
** 1.0.0     09-01-2013    Autron          Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_DspReadDTCInfo.h"
#include "Dem.h"

#if(DCM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "Dcm_Ram.h"
#include "Dcm_DspMain.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Config.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions
*******************************************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
static FUNC(void, DCM_CODE) Dcm_DspUpdDTCBySeverityMaskInfo(void);
#endif
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-begin MISRA-C3:2.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
** Function Name        : Dcm_DspRptDTC                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for the service Read DTC      **
**                        information (service 0x19) to list the DTCs and the **
**                        associated status information matching a specific   **
**                        status mask, severity mask, memory location and DTC **
**                        type. It will be invoked for sub-function values    **
**                        0x02, 0x0A, 0x0F, 0x13 and 0x15.                    **
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
**                        Dcm_GpMsgContext, Dcm_DspSerPgStatus,               **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_PrtclTxBufStatus, Dcm_GucReadGlobal,            **
**                        Dcm_GucAvailableDTCStatusMask                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dem_GetDTCStatusAvailabilityMask, Dem_SetDTCFilter, **
**                        Dcm_DemGetNumberOfReportedDTC,                      **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_RPT_DTC == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptDTC(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_MsgType LpReqResData;

  Dem_DTCOriginType LddDTCOrigin;
  Dem_DTCKindType LddDTCKind;
  Std_ReturnType LddReturnValue;
  uint8 LucDTCStatusMask = (uint8)0x00;

   /* Update variable as DCM_E_POSITIVERESPONSE */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;

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
    LpReqResData = pMsgContext->reqData;
    Dcm_GucReadGlobal = DCM_TRUE;

    /* update DTCKind type, for 0x0A and 0x15 */
    if((Dcm_GucSubFunction == DCM_RD_ALL_SUPPORTED_DTC) ||
      (Dcm_GucSubFunction == DCM_DSP_PERMNT_STATUS_SUBFCT))
    {
      /* @SWS_Dem_00208
        Status-byte mask for DTC status-byte ﬁltering Val-
        ues: 0x00: Autosar-speciﬁc value to deactivate the
        status-byte ﬁltering (different meaning than in ISO
        14229-1) to report all supported DTCs (used for
        service 0x19 subfunctions 0x0A/0x15) 0x01..0xFF:
        Status-byte mask according to ISO 14229-1 DTC-
        StatusMask (handed over by Dcm from service re-
        quest directly) to ﬁlter for DTCs with at least one sta-
        tus bit set matching this status-byte mask
      */
      /* Update status mask */
      LucDTCStatusMask = DCM_STATUS_MASK_ALL;
    }
    else
    {
      /* Update status mask from the request */
      LucDTCStatusMask = LpReqResData[DCM_ONE];
    }
    /* Check if the sub function requested is DCM_RD_MIRROR_MEM_BYDTCMASK */
    if(Dcm_GucSubFunction == DCM_RD_MIRROR_MEM_BYDTCMASK)
    {
      /* Mirror Memory */
      LddDTCOrigin = DEM_DTC_ORIGIN_MIRROR_MEMORY;
    }
    /* sub function 0x15 */
    else if(Dcm_GucSubFunction == DCM_DSP_PERMNT_STATUS_SUBFCT)
    {
      /* Primary Memory */
      LddDTCOrigin = DEM_DTC_ORIGIN_PERMANENT_MEMORY;
    }
    else
    {
      /* Primary Memory */
      LddDTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    }
    /* update DTCKind type, for ox13 */
    if(Dcm_GucSubFunction == DCM_DSP_EMI_OBD_DTC_SUBFCT)
    {
      LddDTCKind = DEM_DTC_KIND_EMISSION_REL_DTCS;
    }
    else
    {
      LddDTCKind = DEM_DTC_KIND_ALL_DTCS;
    }

    /* Get the DTC status information supported by the DEM */
    LddReturnValue = Dem_GetDTCStatusAvailabilityMask
      (&Dcm_GucAvailableDTCStatusMask);
    #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
    if (DCM_TRUE == Dcm_InternalTroubleCodeService)
    {
      Dcm_GucAvailableDTCStatusMask = DCM_ITC_STATUS_MASK & Dcm_GucAvailableDTCStatusMask;
    }
    #endif
  
    if(LddReturnValue == E_OK)
    {  
      if((((LucDTCStatusMask != DCM_ZERO) &&
        (Dcm_GucAvailableDTCStatusMask != DCM_ZERO)) &&
        ((LucDTCStatusMask & Dcm_GucAvailableDTCStatusMask) != DCM_ZERO)) ||
        ((LucDTCStatusMask == DCM_ZERO) &&
        (Dcm_GucAvailableDTCStatusMask != DCM_ZERO) &&
        (Dcm_GucSubFunction == DCM_RD_ALL_SUPPORTED_DTC)) ||
        ((LucDTCStatusMask == DCM_ZERO) &&
        (Dcm_GucAvailableDTCStatusMask != DCM_ZERO) &&
        (Dcm_GucSubFunction == DCM_DSP_PERMNT_STATUS_SUBFCT)))
      {
        LddReturnValue = Dem_SetDTCFilter
        ((Dcm_GucAvailableDTCStatusMask & LucDTCStatusMask), LddDTCKind,
        DEM_DTC_FORMAT_UDS, LddDTCOrigin, DEM_FILTER_WITH_SEVERITY_NO,
        DEM_SEVERITY_NO_SEVERITY, (uint8)DEM_FILTER_FOR_FDC_NO);
        if(LddReturnValue == DEM_FILTER_ACCEPTED)
        {
          Dcm_DemGetNumberOfReportedDTC();
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

        Dcm_GstMsgContext.resDataLen = DCM_TWO;

        Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
  
        Dcm_GpReqResData[DCM_ONE] = Dcm_GucAvailableDTCStatusMask;
      
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
  
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
  #endif
  {
    /* Dcm_PrtclTxBufStatus.ReportNumOfDtc set to true
     * when reporting is pending */
    if(Dcm_PrtclTxBufStatus.ReportNumOfDtc == DCM_FALSE)
    {
      #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
      Dcm_InternalTroubleCodeService = DCM_FALSE;
      #endif

      /* Send response from main function */
      Dcm_GblSendResponse = DCM_TRUE;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DemGetNumberOfReportedDTC                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function of the service Read   **
**                        DTC information (service 0x19) to list the number   **
**                        of Reported DTcs.It will be invoked for             **
**                        sub-function values 0x02, 0x0A, 0x0F, 0x13          **
**                        and 0x15                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_PrtclTxBufStatus, Dcm_GucRecordNumber,          **
**                        Dcm_TxRespStatus, Dcm_DspSerPgStatus,               **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GpMsgContext, Dcm_GucAvailableDTCStatusMask     **
**                        Function(s) invoked :                               **
**                        Dem_GetNumberOfFilteredDTC, Dcm_DspReadReqdDTCInfo  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DemGetNumberOfReportedDTC(void)
{
  Dem_ReturnGetNumberOfFilteredDTCType LddNumFilteredDTCType;
  uint32 LulRespLength;
  uint16 LusNumberOfFilteredDTC = (uint16)0x00;
  Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;

  if (
    (Dcm_GpReqResData == NULL_PTR) 
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
      #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
      if (DCM_TRUE == Dcm_InternalTroubleCodeService)
      {
        /* DTCHighByte + DTCLowByte + DTCStatus = 3 for every
          DTC + 2(DTCAvailableMask and subfunction */
        LulRespLength = (LusNumberOfFilteredDTC * 3) + DCM_TWO;
      }
      else
      #endif
      {
        /* DTCHighByte + DTCMiddleByte  + DTCLowByte + DTCStatus = 4 for every
         DTC + 2(DTCAvailableMask and subfunction */
        LulRespLength = (uint32)(((uint32)LusNumberOfFilteredDTC << (uint32)0x02) + (uint32)0x02);
      }

      /* Update the complete response length that is to be transmitted */
      Dcm_GstMsgContext.resDataLen = LulRespLength;

    
      /*
        * Check if the response buffer is capable of accommodating the
        * complete response at once
        */
      if(LulRespLength <= (Dcm_GstMsgContext.resMaxDataLen))
      {
        /* Update the sub function */
        Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
        /* Update DTC status availabilityMask */
        Dcm_GpReqResData[DCM_ONE] = Dcm_GucAvailableDTCStatusMask;
        /* Reset the pointer to the response data buffer */
        Dcm_GpReqResData = &Dcm_GpReqResData[DCM_TWO];

        /*
          * Pass the buffer size with two values less since sub function and
          * availabilityMask is already updated
          */
        LulRespLength = LulRespLength - DCM_TWO;

        (void)Dcm_DspReadReqdDTCInfo(LulRespLength);
      }
      else
      {
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON) /* 0x0A */
        /* This variable is re used to store DTC Mask */
        Dcm_GucRecordNumber = Dcm_GucAvailableDTCStatusMask;
        /* Set the global bit flag for paging started to TRUE */
        Dcm_DspSerPgStatus.ucPagingStarted = DCM_TRUE;
        /* Start the paged processing */
        Dcm_DsdStartPagedProcessing(&Dcm_GstMsgContext);

        #else

         /*
          * Update the NRC if the response length is greater than the
          * response buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled
          */
          Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;

        #endif
      }
    }
    else if(LddNumFilteredDTCType == DEM_NUMBER_PENDING)
    {
      /* Set the Flag for returning of DCM_E_PENDING */
      Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_TRUE;
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
** Function Name        : Dcm_DspRptDTCFltDetCtr                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for the service Read DTC      **
**                        information (service 0x19) to list the Fault        **
**                        Detection Counter for all the DTCs with Prefailed   **
**                        Status It will be invoked for sub-function value    **
**                        0x14                                                **
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
**                        Dcm_GucReadGlobal, Dcm_GblFaultDetcetionCounter     **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_DspSerPgStatus, Dcm_GpMsgContext                **
**                        Function(s) invoked :                               **
**                        Dem_SetDTCFilter, Dcm_DspReadReqdDTCFDC             **
**                        Dem_GetNumberOfFilteredDTC,                         **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTC_FLT_DET_CTR == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptDTCFltDetCtr(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dem_ReturnGetNumberOfFilteredDTCType LddNumFilteredDTCType;
  uint32 LulRespLength;
  uint16 LusNumberOfFilteredDTC = (uint16)0x00;
  uint8 LucReturnRes;

  Dcm_GucReadGlobal = DCM_TRUE;
  
  if (
    (pMsgContext == NULL_PTR) || 
    (Dcm_GpReqResData == NULL_PTR)
  )
  {
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    LucReturnRes = DEM_FILTER_ACCEPTED;
    /*
    * Set the filter mask over all DTCs for the API Dem_GetNextFilteredDTC
    * and reset the internal counter to the first event that matches the
    * filter settings
    */
    if(Dcm_GblFaultDetcetionCounter != DCM_TRUE)
    {
     LucReturnRes = Dem_SetDTCFilter(DCM_ZERO, DEM_DTC_KIND_ALL_DTCS,
      DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY,
      DEM_FILTER_WITH_SEVERITY_NO, DEM_SEVERITY_NO_SEVERITY,
      DEM_FILTER_FOR_FDC_YES);

    }
    else
    {
      Dcm_GblFaultDetcetionCounter = DCM_FALSE;
    }
    /* Check if the filter was accepted */
    if(LucReturnRes == DEM_FILTER_ACCEPTED)
    {
      /* Get the number of DTC matching the defined status mask */
      LddNumFilteredDTCType = Dem_GetNumberOfFilteredDTC(&LusNumberOfFilteredDTC);

      /* Check whether getting number of DTC was successful */
      if(LddNumFilteredDTCType == DEM_NUMBER_OK)
      {
        /* (3DTC + FDC counter)*counter + Sub functions */
        LulRespLength = (uint32)(((uint32)LusNumberOfFilteredDTC << (uint32)0x02) + (uint32)0x01);

        /* Update the complete response length that is to be transmitted */
        pMsgContext->resDataLen = LulRespLength;

        if(LulRespLength <= (pMsgContext->resMaxDataLen))
        {
          /* Update the sub function */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
          Dcm_GpReqResData = &Dcm_GpReqResData[1u];

          /*
           * Pass the buffer size with two values less since sub function and
           * availabilityMask is already updated
           */
          LulRespLength = LulRespLength - DCM_ONE;
          
          (void)Dcm_DspReadReqdDTCFDC(LulRespLength);    
        }
        else
        {
          #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)

          /* Set the global bit flag for paging started to TRUE */
          Dcm_DspSerPgStatus.ucPagingStarted = DCM_TRUE;
          /* Start the paged processing */
          Dcm_DsdStartPagedProcessing(pMsgContext);

          #else

           /*
            * Update the NRC if the response length is greater than the response
            * buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled
                        */
          Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;

          #endif
        }
      }
      else if(LddNumFilteredDTCType == DEM_NUMBER_PENDING)
      {
        /* Set the Flag for returning of DCM_E_PENDING */
        Dcm_GblFaultDetcetionCounter = DCM_TRUE;
      }
      else
      {
        /* For QAC Check */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
    /* [SWS_Dcm_01043]
     * If DEM_WRONG_FILTER value is returned from 
     * Dem_ReturnSetFilterType, the Dcm module shall send a negative response with 
     * NRC 0x31 (Request out of range). */      
    else if (DEM_WRONG_FILTER == LucReturnRes)
    {
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }       
    else
    {
      /* For QAC Check */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  
  if((Dcm_GblFaultDetcetionCounter == DCM_FALSE) &&
  (Dcm_GblDTCFDCPending == DCM_FALSE))
  {
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspReadReqdDTCInfo                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function of the service Read   **
**                        DTC information (service 0x19) to list the filtered **
**                        DTcs.It will be invoked for sub-function values     **
**                        0x02, 0x0A, 0x0F, 0x13 and 0x15                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LulBufferSize                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GddNegRespError, Dcm_GpReqResData,              **
**                        Dcm_GunDTC, Dcm_GddCurrentLength, Dcm_GpMsgContext  **
**                        Function(s) invoked : Dem_GetNextFilteredDTC        **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTC == STD_ON)
/* polyspace<MISRA-C:8.10:Not a defect:Justify with annotations> Whether the Dcm api function is required internal or external linkage, depends on user configuration */
FUNC(uint32, DCM_CODE) Dcm_DspReadReqdDTCInfo(uint32 LulBufferSize)
{
  uint32 LulRespBufferSize = 0U;
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint32 LulRemainingLength = 0U;
  uint8 LucCount = 0U;
  #endif

  uint8 DTCAndStatusRecordLength = 0U;
  uint8 LucReturnRes = 0U;
  uint8 LucDTCStatus = (uint8)0x00;

  if (
    (Dcm_GpReqResData == NULL_PTR)
  )
  {
    /* For Misra-C Check */   
    /* Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT; */
  }
  else
  {
    #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
    if (DCM_TRUE == Dcm_InternalTroubleCodeService)
    {
      DTCAndStatusRecordLength = 3;
    }
    else
    #endif
    {
      DTCAndStatusRecordLength = 4;
    }

    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    LulRemainingLength = DCM_ZERO;
    #endif

    /* If paging is enabled load the filtered DTC from stored */
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /* Check if paged transmission is in progress */
    if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
    {
      /* Check if it is the first page that is to be updated */
      if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
      {
        /*
         * Reset the global bit flag to indicate that it is other than the first
         * page which is to be processed
         */
        Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
      }
      LulRemainingLength = Dcm_GddCurrentLength;
    }
    #endif
    /* Initialize with the configured buffer size */
    LulRespBufferSize = LulBufferSize;
    /* Initialize the global variable to indicate that no NRC as occurred */
    Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
    LucReturnRes = DCM_ZERO;
    while(
      (LulRespBufferSize >= DTCAndStatusRecordLength) &&

      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      (
        (
          (Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) &&
          (LulRemainingLength != DCM_ZERO)
        ) 
        ||
        (
          (Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
        )
      ) &&
      #endif
      
      (LucReturnRes != DEM_FILTERED_NO_MATCHING_DTC) &&
      (Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
    )
    {
      LucReturnRes = Dem_GetNextFilteredDTC
        (&Dcm_GunDTC.ulLongReg32, &LucDTCStatus);

      if(LucReturnRes == DEM_FILTERED_OK)
      {
        #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
        if (DCM_TRUE == Dcm_InternalTroubleCodeService)
        { /* DTC Hight Byte */
          Dcm_GpReqResData[0] = Dcm_GunDTC.ddByte.ucMidLowByte;
          /* DTC Low Byte */
          Dcm_GpReqResData[1] = Dcm_GunDTC.ddByte.ucLsByte;
          /* DTC Status Mask */
          Dcm_GpReqResData[2] = LucDTCStatus;
        }
        else
        #endif
        {
	  /* polyspace +8 MISRA-C3:18.1 [Justified:Low] "Not a defect" */  
          /* DTC High Byte */
          Dcm_GpReqResData[0] = Dcm_GunDTC.ddByte.ucMidHiByte;
          /* DTC Middle Byte */
          Dcm_GpReqResData[1] = Dcm_GunDTC.ddByte.ucMidLowByte;
          /* DTC Low Byte */
          Dcm_GpReqResData[2] = Dcm_GunDTC.ddByte.ucLsByte;
          /* DTC Status Mask */
          Dcm_GpReqResData[3] = LucDTCStatus;
        }

        /* Increment pointer by DTCAndStatusRecordLength bytes */
        Dcm_GpReqResData = &Dcm_GpReqResData[DTCAndStatusRecordLength];

        /* Update the response buffer size */
        LulRespBufferSize = LulRespBufferSize - DTCAndStatusRecordLength;
        /* Update the Temporary length of response buffer */
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
        {
          LulRemainingLength = LulRemainingLength - DTCAndStatusRecordLength;
        }
        #endif
      }
      else if(LucReturnRes == DEM_FILTERED_NO_MATCHING_DTC)
      {
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
        {
          Dcm_GstMsgContext.resDataLen =
          Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        }
        #else
        /* Decrease the response length by DTCAndStatusRecordLength bytes */
        Dcm_GstMsgContext.resDataLen =
        Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        #endif
      }
      else
      {
        /* To avoid QAC warning */
      }
    }
    
    if(LucReturnRes == DEM_FILTERED_NO_MATCHING_DTC)
    {
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)&&
        (LulRemainingLength != DCM_ZERO) &&
        (LulRespBufferSize >= DTCAndStatusRecordLength))
      {
        do
        {
          for(LucCount = DCM_ZERO; LucCount < DTCAndStatusRecordLength; LucCount++)
          {
            *Dcm_GpReqResData = DCM_ZERO;
            
            Dcm_GpReqResData++;
          }
          LulRespBufferSize = LulRespBufferSize - DTCAndStatusRecordLength;
          LulRemainingLength  = LulRemainingLength - DTCAndStatusRecordLength;
        }while((LulRespBufferSize >= DTCAndStatusRecordLength) &&
               (LulRemainingLength != DCM_ZERO));
      }
      #endif
    }
  }
  
  return(LulBufferSize - LulRespBufferSize);
}
#endif /* (DCM_RPT_DTC == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DspReadReqdDTCFDC                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function of the service Read   **
**                        DTC information (service 0x19) to list the Fault    **
**                        Detection Counter for all the DTCs with prefailed   **
**                        Status .It will be invoked for sub-function value   **
**                        0x14                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LulBufferSize                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GunDTC,                    **
**                        Dcm_GblDTCFDCPending, Dcm_GulFDCRespSize,           **
**                        Dcm_DspSerPgStatus, Dcm_GpMsgContext                **
**                        Dcm_GddNegRespError, Dcm_GpReqResData,              **
**                        Dcm_GddCurrentLength                                **
**                        Function(s) invoked :                               **
**                        Dem_GetNextFilteredDTCAndFDC                        **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTC_FLT_DET_CTR == STD_ON)
FUNC(uint32, DCM_CODE) Dcm_DspReadReqdDTCFDC(uint32 LulBufferSize)
{
  uint32 LulRespBufferSize = 0U;
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint32 LulRemainingLength = 0U;
  #endif
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint8 LucCount = 0U;
  #endif
  uint8 LucReturnRes = 0U;
  sint8 LscDTCFaultDetectionCounter = (sint8)0x00;

  Dcm_GblDTCFDCPending = DCM_FALSE;
  Dcm_GulFDCRespSize = LulBufferSize;
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  LulRemainingLength = DCM_ZERO;
  #endif

  if ( 
    (Dcm_GpReqResData == NULL_PTR)
  )
  {
    /* For Misra-C Check */   
    /* Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT; */
  }
  else
  {  
    /* If paging is enabled load the filtered DTC from stored */
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /* Check if paged transmission is in progress */
    if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
    {
      /* Check if it is the first page that is to be updated */
      if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
      {
        /*
        * Reset the global bit flag to indicate that it is other than the first
        * page which is to be processed
        */
        Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
      }
      LulRemainingLength = Dcm_GddCurrentLength;
    }
    #endif
    /* Initialize with the configured buffer size */
    LulRespBufferSize = LulBufferSize;
    /* Initialize the global variable to indicate that no NRC as occurred */
    Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
    LucReturnRes = DCM_ZERO;
    while(
      (LulRespBufferSize > DCM_THREE) &&

      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      (
        (
          (Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) &&
          (LulRemainingLength != DCM_ZERO)
        ) 
        ||
        (
          (Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
        )
      ) &&
      #endif
      (LucReturnRes != DEM_FILTERED_NO_MATCHING_DTC)
    )
    {
      LucReturnRes = Dem_GetNextFilteredDTCAndFDC(&Dcm_GunDTC.ulLongReg32,
        &LscDTCFaultDetectionCounter);

      if(LucReturnRes == DEM_FILTERED_OK)
      {
        /* DTC High Byte */
        *Dcm_GpReqResData = Dcm_GunDTC.ddByte.ucMidHiByte;
        Dcm_GpReqResData =  &Dcm_GpReqResData[1u];
       
        /* DTC Middle Byte */
        *Dcm_GpReqResData = Dcm_GunDTC.ddByte.ucMidLowByte;
  
        Dcm_GpReqResData =  &Dcm_GpReqResData[1u];
    
        /* DTC Low Byte */
        *Dcm_GpReqResData = Dcm_GunDTC.ddByte.ucLsByte;
  
        Dcm_GpReqResData =  &Dcm_GpReqResData[1u];
    
        /* DTC Status Mask */
        *Dcm_GpReqResData = (uint8)LscDTCFaultDetectionCounter;

        Dcm_GpReqResData =  &Dcm_GpReqResData[1u];
    
        /* Update the response buffer size */
        LulRespBufferSize = LulRespBufferSize - DCM_FOUR;
        /* Update the Temporary length of response buffer */
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
        {
          LulRemainingLength = LulRemainingLength - DCM_FOUR;
        }
        #endif
      }
      else if(LucReturnRes == DEM_FILTERED_NO_MATCHING_DTC)
      {
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
        {
          Dcm_GstMsgContext.resDataLen =
          Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        }
        else
        {
          /* To avoid QAC */
        }
        #else
        /* Decrease the response length by 4 bytes */
        Dcm_GstMsgContext.resDataLen =
        Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        
        #endif
      }
      else
      {
        Dcm_GblDTCFDCPending = DCM_TRUE;
      }
    }
    if(LucReturnRes == DEM_FILTERED_NO_MATCHING_DTC)
    {
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)&&
        (LulRemainingLength != DCM_ZERO) && (LulRespBufferSize > DCM_THREE))
      {
        do
        {
          for(LucCount = DCM_ZERO; LucCount < DCM_FOUR; LucCount++)
          {
            *Dcm_GpReqResData = DCM_ZERO;
            /* MISRA Rule        : 17.4
              Message            : Increment or decrement operation
                                   performed on pointer
              Reason             : Increment operator not used
                                   to achieve better throughput.
              Verification       : However, part of the code
                                   is verified manually and
                                   it is not having any impact.
            */
            Dcm_GpReqResData++;
          }
          LulRespBufferSize = LulRespBufferSize - DCM_FOUR;
          LulRemainingLength  = LulRemainingLength - DCM_FOUR;
        }while((LulRespBufferSize > DCM_THREE) &&
        (LulRemainingLength != DCM_ZERO));
      }
      #endif
    }
  }
  
  return(LulBufferSize - LulRespBufferSize);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspRptDTCBySeverityInfo                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is sub-function of the service Read DTC        **
**                        information (service 0x19) to read the DTC and      **
**                        associated severity and status information matching **
**                        a specific severity mask. It will be invoked for    **
**                        sub-function value 0x08                             **
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
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GblNumFilterDTCStatusBySevirtMask               **
**                        Dcm_GusMaxNoOfRespPend, Dcm_DspSerPgStatus,         **
**                        Dcm_GucReadGlobal, Dcm_GucAvailableDTCStatusMask    **
**                        Function(s) invoked :                               **
**                        Dem_GetDTCStatusAvailabilityMask, Dem_SetDTCFilter  **
**                        Dcm_GetNumberOfFilteredDtcBySeverityInfo            **
**                        Dcm_ExternalSetNegResponse                          **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptDTCBySeverityInfo(
 P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dem_DTCSeverityType LddSeverityMask = (Dem_DTCSeverityType)0x00;
  Std_ReturnType LucReturnRes;
  uint8 LucDTCStatusMask = (uint8)0x00;

  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_GusMaxNoOfRespPend = DCM_ZERO;
  Dcm_GblNumFilterDTCStatusBySevirtMask = DCM_FALSE;
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
    /* Get the DTC status information supported by the DEM */
    LucReturnRes = Dem_GetDTCStatusAvailabilityMask(&Dcm_GucAvailableDTCStatusMask);
    
    /* Check whether the DTC status mask was successful */
    if(LucReturnRes == E_OK)
    {
      /* Get information of DTC Status Mask */
      LddSeverityMask = pMsgContext->reqData[1U];
      /* Get information of DTC Status Mask */
      LucDTCStatusMask = pMsgContext->reqData[2U];

      /*
       * Set the filter mask over all DTCs for the API Dem_GetNextFilteredDTC
       * and reset the internal counter to the first event that matches the
       * filter settings
       */
      if (
        (LucDTCStatusMask != DCM_ZERO) &&
        ((LucDTCStatusMask & Dcm_GucAvailableDTCStatusMask) != DCM_ZERO)
      )
      {
        LucReturnRes = Dem_SetDTCFilter(
          (Dcm_GucAvailableDTCStatusMask & LucDTCStatusMask),
          DEM_DTC_KIND_ALL_DTCS, 
          DEM_DTC_FORMAT_UDS,
          DEM_DTC_ORIGIN_PRIMARY_MEMORY, 
          (uint8)DEM_FILTER_WITH_SEVERITY_YES,
          LddSeverityMask, 
          (uint8)DEM_FILTER_FOR_FDC_NO
        );
        
        /* Check if the filter was accepted */
        if(LucReturnRes == DEM_FILTER_ACCEPTED)
        {
          Dcm_GetNumberOfFilteredDtcBySeverityInfo();
        }
        /* [SWS_Dcm_01043]
         * If DEM_WRONG_FILTER value is returned from 
         * Dem_ReturnSetFilterType, the Dcm module shall send a negative response with 
         * NRC 0x31 (Request out of range). */          
        else if (DEM_WRONG_FILTER == LucReturnRes)
        {
          Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
        }      
        else
        {
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        }
      }
      else
      {
        /* Update the response data length */
        pMsgContext->resDataLen = 2U;

        pMsgContext->resData[0U] = Dcm_GucSubFunction;      
      
        /* Update DTC status availabilityMask */
        pMsgContext->resData[1U] = Dcm_GucAvailableDTCStatusMask;

        /* Update the global variable to indicate that no NRC has occurred */
        Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
      }
    }
    else
    {
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT; /* TODO : DCM_E_REQUESTOUTOFRANGE; */
    }
  }
  
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
  #endif
  {
    if(Dcm_GblNumFilterDTCStatusBySevirtMask == DCM_FALSE)
    {
      /* Send response from main function */
      Dcm_GblSendResponse = DCM_TRUE;
    }
  }
}
#endif

/*******************************************************************************
** Function Name        :Dcm_GetNumberOfFilteredDtcBySeverityInfo             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          :  This is the internal function of the service Read  **
**                         DTC information (service 0x19) to list the number  **
**                         of Reported Filtered DTcs by Severity Information. **
**                         It will be invoked for sub-function value          **
**                         0x08                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GblNumFilterDTCStatusBySevirtMask,              **
**                        Dcm_GpMsgContext, Dcm_GucAvailableDTCStatusMask,    **
**                        Dcm_GucRecordNumber, Dcm_DspSerPgStatus,            **
**                        Function(s) invoked :                               **
**                        Dem_GetNumberOfFilteredDTC                          **
**                        Dcm_DspUpdDTCBySeverityMask                         **
**                        Dcm_DsdStartPagedProcessing                         **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
FUNC(void, DCM_CODE) Dcm_GetNumberOfFilteredDtcBySeverityInfo(void)
{

  Dem_ReturnGetNumberOfFilteredDTCType LddNumFilteredDTCType;
  uint32 LulRespLength;
  uint16 LusNumberOfFilteredDTC = (uint16)0x00;
  Dcm_GblNumFilterDTCStatusBySevirtMask = DCM_FALSE;

  if (Dcm_GpReqResData == NULL_PTR)
  {
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* Get the number of DTC matching the defined status mask */
    LddNumFilteredDTCType = Dem_GetNumberOfFilteredDTC(&LusNumberOfFilteredDTC);

    /* Check if the response buffer is to be updated */
    if(LddNumFilteredDTCType == DEM_NUMBER_OK)
    {

      /* DTCHighByte + DTCLiddleByte  + DTCLowByte + DTCStatus +
             DTCFunctionalUnit + DTCSeverity = 6 for every DTC + 2 */
      LulRespLength = (uint32)(((uint32)LusNumberOfFilteredDTC << (uint32)0x02) +\
        ((uint32)LusNumberOfFilteredDTC << (uint32)0x01) + (uint32)0x02);

      Dcm_GstMsgContext.resDataLen = LulRespLength;
            
      if(LulRespLength <= (Dcm_GstMsgContext.resMaxDataLen))
      {
        /* Update the sub function */
        Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
        /* Update DTC status availabilityMask */
        Dcm_GpReqResData[DCM_ONE] = Dcm_GucAvailableDTCStatusMask;
        /* Reset the pointer to the response data buffer */
        Dcm_GpReqResData = &Dcm_GpReqResData[DCM_TWO];

        /*
        * Pass the buffer size with two values less since sub function and
        * availabilityMask is already updated
        */
        LulRespLength = LulRespLength - DCM_TWO;

        (void)Dcm_DspUpdDTCBySeverityMask(LulRespLength);
      }
      else
      {
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        /* This variable is reused to store DTCMask */
        Dcm_GucRecordNumber = Dcm_GucAvailableDTCStatusMask;
        /* Set the global bit flag for paging started to TRUE */
        Dcm_DspSerPgStatus.ucPagingStarted = DCM_TRUE;
        /* Start the paged processing */
        Dcm_DsdStartPagedProcessing(&Dcm_GstMsgContext);
        #else
        /*
         * Update the NRC if the response length is greater than the response
         * buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled
         */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
        #endif
      }
    }
    else if(LddNumFilteredDTCType == DEM_NUMBER_PENDING)
    {
      /* Set the Flag for returning of DCM_E_PENDING */
      Dcm_GblNumFilterDTCStatusBySevirtMask = DCM_TRUE;
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
** Function Name        : Dcm_DspUpdDTCBySeverityMask                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function used for sub-functions**
**                        0x08 to read the DTC and associated severity Record **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LulBufferSize                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GddNegRespError, Dcm_GddCurrentLength,          **
**                        Dcm_GpReqResData, Dcm_GunDTC, Dcm_GpMsgContext.     **
**                        Function(s) invoked :                               **
**                        Dem_GetStatusOfDTC,                                 **
**                        Dem_GetNextFilteredDTCAndSeverity                   **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
/* polyspace<MISRA-C:8.10:Not a defect:Justify with annotations> Whether the Dcm api function is required internal or external linkage, depends on user configuration */
FUNC(uint32, DCM_CODE) Dcm_DspUpdDTCBySeverityMask(
  uint32 LulBufferSize)
{
  Dem_ReturnGetNextFilteredDTCType LddGetNextFilteredDTC;
  Dem_DTCSeverityType LddDTCSeverity = (Dem_DTCSeverityType)0x00;
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint32 LulRemainingLength = 0U;
  #endif
  uint32 LulRespBufferSize = 0U;
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint8 LucCount = 0U;
  #endif
  uint8 LucDTCStatus = (uint8)0x00;
  uint8 DTCFunctionalUnit = DEM_NO_FUNCTIONAL_UNIT;

  LddGetNextFilteredDTC = DCM_ZERO;
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  LulRemainingLength = DCM_ZERO;
  #endif

  if (
    (Dcm_GpReqResData == NULL_PTR)
  )
  {
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* If paging is enabled load the filtered DTC from stored */
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /* Check if paged transmission is in progress */
    if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
    {
      /* Check if it is the first page that is to be updated */
      if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
      {
        /*
        * Reset the global bit flag to indicate that it is other than the first
        * page which is to be processed
        */
        Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
      }
      LulRemainingLength = Dcm_GddCurrentLength;
    }
    #endif

    LulRespBufferSize = LulBufferSize;
    /* Set the global variable indicating NRC occurred to FALSE */
    Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

    /* Check if the response buffer is available and the filled
    length is not greater than the remaining length to be transmitted */
    while (
      (LulRespBufferSize > DCM_FIVE) &&
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      (((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) && (LulRemainingLength != DCM_ZERO)) ||
       (Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE))
      &&
      #endif
      (LddGetNextFilteredDTC != DEM_FILTERED_NO_MATCHING_DTC)
    )
    {
      /* Get the current DTC, Status, Severity, Functional Unit */
      LddGetNextFilteredDTC =  Dem_GetNextFilteredDTCAndSeverity
        (&Dcm_GunDTC.ulLongReg32, &LucDTCStatus, &LddDTCSeverity,
        &DTCFunctionalUnit);
      if(LddGetNextFilteredDTC == DEM_FILTERED_OK)
      {
        /* Update severity */
        Dcm_GpReqResData[DCM_ZERO] = LddDTCSeverity;
        /* FunctionalUnit */
        Dcm_GpReqResData[DCM_ONE] = DTCFunctionalUnit;
        /* DTC High Byte */
        Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidHiByte;
        /* DTC Middle Byte */
        Dcm_GpReqResData[DCM_THREE] = Dcm_GunDTC.ddByte.ucMidLowByte;
        /* DTC Low Byte */
        Dcm_GpReqResData[DCM_FOUR] = Dcm_GunDTC.ddByte.ucLsByte;
        /* DTC Status Mask */
        Dcm_GpReqResData[DCM_FIVE] = LucDTCStatus;

        /* Increment pointer by six bytes */
        Dcm_GpReqResData = &Dcm_GpReqResData[DCM_SIX];
        /* Update the response buffer size */
        LulRespBufferSize = LulRespBufferSize - DCM_SIX;
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
        {
          LulRemainingLength = LulRemainingLength - DCM_SIX;
        }
        #endif
      }
      else if(LddGetNextFilteredDTC == DEM_FILTERED_NO_MATCHING_DTC)
      {
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
        {
          Dcm_GstMsgContext.resDataLen =
            Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        }
        else
        {
          /* To avoid QAC */
        }
        #else
        /* To exit from while loop */
        /* Decrease the response length by 4 bytes */
        Dcm_GstMsgContext.resDataLen =
          Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        #endif
      }
      else
      {
        /* To avoid QAC warning */
      }
    }

    if(LddGetNextFilteredDTC == DEM_FILTERED_NO_MATCHING_DTC)
    {
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)&&
        (LulRemainingLength != DCM_ZERO) && (LulRespBufferSize > DCM_FIVE))
      {
        do
        {
          for(LucCount = DCM_ZERO; LucCount < DCM_SIX; LucCount++)
          {
            *Dcm_GpReqResData = DCM_ZERO;
            /* MISRA Rule        : 17.4
              Message            : Increment or decrement operation
                                   performed on pointer
              Reason             : Increment operator not used
                                   to achieve better throughput.
              Verification       : However, part of the code
                                   is verified manually and
                                   it is not having any impact.
            */
            Dcm_GpReqResData++;
          }
          LulRespBufferSize = LulRespBufferSize - DCM_SIX;
          LulRemainingLength  = LulRemainingLength - DCM_SIX;
        }while((LulRespBufferSize > DCM_FIVE) &&
        (LulRemainingLength != DCM_ZERO));
      }
      #endif
    }

    LulRespBufferSize = (LulBufferSize - LulRespBufferSize);
  }

  return LulRespBufferSize;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspRptDTCBySeverityInfoOfDTC                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the function used for the service Read DTC  **
**                        information (service 0x19) to read the DTC and      **
**                        associated severity and status information matching **
**                        a specific severity mask. It will be invoked for    **
**                        sub-function values 0x09                            **
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
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GucRecordNumber, Dcm_DspSerPgStatus,            **
**                        Dcm_GucReadGlobal                                   **
**                        Function(s) invoked :                               **
**                        Dem_GetDTCStatusAvailabilityMask,                   **
**                        Dcm_DsdStartPagedProcessing,                        **
**                        Dcm_DspUpdDTCBySeverityMaskInfo,                    **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptDTCBySeverityInfoOfDTC(
 P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint32 LulRespLength;
  uint8 LucAvailableDTCStatusMask = (uint8)0x00;
  uint8 LucReturnRes;
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
    /* Initialize the pointer to the request data buffer */
    /* Get the DTC status information supported by the DEM */
    LucReturnRes = Dem_GetDTCStatusAvailabilityMask(&LucAvailableDTCStatusMask);
    /* Check whether the DTC status mask was successful */
    if(LucReturnRes == E_OK)
    {
      /* Initialize the global pointer with request data buffer address */
      /* polyspace +1 DEFECT:USELESS_WRITE [Justified:Low] "Not a defect" */
      Dcm_GpReqResData = pMsgContext->reqData;
      /*
      * Update the local variable for response length.
      * Response bytes -> Subfunction + DTCStatusAvailabilityMask + DTCHighByte
      * + DTCLiddleByte + DTCLowByte + DTCStatus + DTCFunctionalUnit +
      * DTCSeverity
      */
      LulRespLength = DCM_EIGHT;
      /* Get the DTC for the input request */
      Dcm_GunDTC.ddByte.ucLsByte      = pMsgContext->reqData[DCM_THREE];
      Dcm_GunDTC.ddByte.ucMidLowByte  = pMsgContext->reqData[DCM_TWO];
      Dcm_GunDTC.ddByte.ucMidHiByte   = pMsgContext->reqData[DCM_ONE];
      Dcm_GunDTC.ddByte.ucMsByte      = DCM_ZERO;
      

      /* Initialize the global pointer with response data buffer address */
      Dcm_GpReqResData = pMsgContext->resData;

      /* Update the response data length in the pMsgContext */
      pMsgContext->resDataLen = LulRespLength;
      /*
      * Check if the response buffer is capable of accommodating the complete
      * response at once
      */
      if(LulRespLength <= (pMsgContext->resMaxDataLen))
      {
        /* Update the sub function */
        Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
        /* Update DTC status availabilityMask */
        Dcm_GpReqResData[DCM_ONE] = LucAvailableDTCStatusMask;
        /* Reset the pointer to the response data buffer */
        Dcm_GpReqResData = &Dcm_GpReqResData[DCM_TWO];
       
        /*
        * Pass the buffer size with two values less since sub function
        * and availabilityMask is already updated
        */

        Dcm_DspUpdDTCBySeverityMaskInfo();
      }
      else
      {
        /* This variable is reused to store DTCMask */
        /* Set the global bit flag for paging started to TRUE */
        /* Start the paged processing */
        /*
        * Update the NRC if the response length is greater than the
        * response buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled
        */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
      }
    }
    else
    {
      /* Update Negative response as condition not correct  */
      Dcm_GddNegRespError  =  DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  
  /* Send response from main function */
  Dcm_GblSendResponse = DCM_TRUE;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspUpdDTCBySeverityMaskInfo                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function for sub-functions 0x09    **
**                        used to read the DTC and associated severity and    **
**                        status information matching a specific severity mask**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GunDTC,                    **
**                        Dcm_GddNegRespError, Dcm_GpReqResData,              **
**                        Function(s) invoked :                               **
**                        Dem_GetStatusOfDTC, Dem_GetSeverityOfDTC,           **
**                        Dem_GetFunctionalUnitOfDTC                          **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
static FUNC(void, DCM_CODE) Dcm_DspUpdDTCBySeverityMaskInfo(void)
{
  Dem_ReturnGetStatusOfDTCType LddDTCStatusType;
  Dem_ReturnGetSeverityOfDTCType LddDTCSeverity;
  Dem_ReturnGetFunctionalUnitOfDTCType LddFunctionalUnit = DEM_NO_FUNCTIONAL_UNIT;
  uint8 LddDTCStatus = (uint8)0x00;
  uint8 LucSvtyStatus = (uint8)0x00;
  uint8 LddFuncUnit;

  if (Dcm_GpReqResData == NULL_PTR)
  {
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {

    /* If paging is enabled load the filtered DTC from stored */
    /* Check if paged transmission is in progress */

    /* Check if it is the first page that is to be updated */
    /*
     * Reset the global bit flag to indicate that it is other than the first
     * page which is to be processed
    */

    /* Set the global variable indicating NRC occurred to FALSE */
    Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

    /* Get the status of the DTC */
    LddDTCStatusType = Dem_GetStatusOfDTC(
      Dcm_GunDTC.ulLongReg32,
      DEM_DTC_ORIGIN_PRIMARY_MEMORY, 
      &LddDTCStatus
    );
    
    if(LddDTCStatusType == DEM_STATUS_OK)
    {
      /* Read the severity of the DTC */
      LddDTCSeverity = Dem_GetSeverityOfDTC(Dcm_GunDTC.ulLongReg32,
        &LucSvtyStatus);

      if(LddDTCSeverity == DEM_GET_SEVERITYOFDTC_OK)
      {
        LddFuncUnit = Dem_GetFunctionalUnitOfDTC(Dcm_GunDTC.ulLongReg32,
          &LddFunctionalUnit);

        if(LddFuncUnit == DEM_GET_FUNCTIONALUNITOFDTC_OK)
        {
          /* Update severity */
          Dcm_GpReqResData[DCM_ZERO] = LucSvtyStatus;
          /* FunctionalUnit */
          Dcm_GpReqResData[DCM_ONE] = LddFunctionalUnit;
          /* DTC High Byte */
          Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidHiByte;
          /* DTC Middle Byte */
          Dcm_GpReqResData[DCM_THREE] = Dcm_GunDTC.ddByte.ucMidLowByte;
          /* DTC Low Byte */
          Dcm_GpReqResData[DCM_FOUR] = Dcm_GunDTC.ddByte.ucLsByte;
          /* DTC Status Mask */
          Dcm_GpReqResData[DCM_FIVE] = LddDTCStatus;

          /* Increment pointer by six bytes */
          /* Update the response buffer size */
        }
        else /* if(LddFuncUnit == DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC */
        {
          /* Update NRC to 0x31 */
          Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
        }
      }
      else if(LddDTCSeverity == DEM_GET_SEVERITYOFDTC_WRONG_DTC)
      {
        /* Update NRC to 0x31 */
        Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      }
      else
      {
        /* Update NRC to 0x22 */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
    else if((LddDTCStatusType == DEM_STATUS_WRONG_DTC) ||
            (LddDTCStatusType == DEM_STATUS_WRONG_DTCORIGIN))
    {
      /* Update NRC to 0x31 */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      /* Update NRC to 0x22 */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
}
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
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
