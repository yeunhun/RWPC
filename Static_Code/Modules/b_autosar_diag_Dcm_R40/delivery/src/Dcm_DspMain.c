/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DspMain.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions of the services of Dsp     **
**              layer                                                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                   Description                   **
********************************************************************************
** 1.0.8     18-06-2019    Y.S     Jeon         #17902                        **
**                                                                            **
** 1.0.7     09-11-2018    Y.S     Jeon         #13923                        **
**                                                                            **
** 1.0.6     12-09-2018    Y.S     Jeon         #13032  #14010                **
**                                                                            **
** 1.0.5     19-10-2016    Jin     Jung         #6217                         **
**                                                                            **
** 1.0.4     03-03-2016    Sungeol Baek         #4266, RTRT reflection        **
**                                                                            **
** 1.0.3     16-07-2015    Sungeol Baek         #2678                         **
**                                                                            **
** 1.0.2     16-04-2015    Sungeol Baek         #2171                         **
**                                                                            **
** 1.0.1     26-02-2015    YoungJin Yun         #414                          **
**                                                                            **
** 1.0.0     09-01-2013    Autron               Initial Version               **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Types.h"
#include "Dcm_Ram.h"
#include "Dcm_DspMain.h"
#include "Dcm_DslInternal.h"
#include "Dcm_DspReadDTCInfo.h"
#include "Dcm_DspReadSSDTCInfo.h"
#include "Rte_Dcm.h"

#if(DCM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "SchM_Dcm.h"
#include "BswM_Dcm.h"
#include "Dcm_CallOuts.h"
#include "Dem.h"
#include "Dcm_DspOBDInternals.h"
#include "Dcm_DspServices.h"
#include "Dcm_DsdInternal.h"
#include "ComM_Dcm.h"
#include "Dcm_Config.h"

/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:begin<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions
*******************************************************************************/
#if((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) || \
    (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))

#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, DCM_CODE) DcmCommControlConfirmation
   (Dcm_IdContextType LucIdContext, Dcm_ConfirmationStatusType LucStatus);

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
** Function Name        : Dcm_DspUpdatePage                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function that provides the page **
**                        buffering handling for the sub functions 0x02,      **
**                        0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0f, 0x10 and  **
**                        0x13 in DSP sub module                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PageBufPtr, PageLen                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_DspSerPgStatus, Dcm_GpReqResData,               **
**                        Dcm_GulBufferSize                                   **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspUpdatePage(
  Dcm_MsgType PageBufPtr, Dcm_MsgLenType PageLen)
{
  /*
   * Re-Initialize the global variable with zero to check if any error is
   * updated during the function execution
   */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  /* Update the global pointer to the response buffer */
  Dcm_GpReqResData = PageBufPtr;
  /* Update the response buffer size */
  Dcm_GulBufferSize = PageLen;
  /* Set the global bit flag indicating that DSP update page is called */
  Dcm_DspSerPgStatus.ucUpdatePageStarted = DCM_TRUE;
}
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DspProcessUpdatePage                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function that provides the page **
**                        buffering handling for the sub functions            **
**                        0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x10 and        **
**                        in DSP sub module                                   **
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
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_DspSerPgStatus,                                 **
**                        Dcm_GpReqResData, Dcm_GulBufferSize,Dcm_GucPIDCount **
**                        Dcm_GucRecordNumber, Dcm_GpMsgContext,              **
**                        Dcm_DspSerPgStatus , Dcm_GucNumofDTC             **
**                        Dcm_GaaPduIdTableConfig , Dcm_GddRxPduId            **
**                        Dcm_GaaBufferConfig ,                               **
**                        Function(s) invoked : Dcm_DspReadReqdDTCInfo,       **
**                        Dcm_DspUpdDTCBySeverityMask,                        **
**                        Dcm_DspProcessSubFctFFData,                         **
**                        Dcm_DspUpdtBasicsOfFreezeFrame,                     **
**                        Dcm_DspProcessExtDataRecd, Dcm_ProcessPage,         **
**                        Dcm_SetNegResponse, Dcm_ProcessingDone,             **
**                        Dcm_DspReadOBD_AvlInfo, Dcm_DspReadOBD_1_DemInfo    **
*******************************************************************************/
#if((DCM_PAGEDBUFFER_ENABLED == STD_ON) && ((DCM_READDTC_SUPPORT == STD_ON) || \
   (DCM_OBD_SUPPORT == STD_ON) || \
   ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON))))
FUNC(void, DCM_CODE) Dcm_DspProcessUpdatePage(void)
{
  #if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
  (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
  (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
  (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
  P2VAR (uint8, AUTOMATIC, DCM_APPL_DATA)LpRxBuffer;
  P2VAR (uint8, AUTOMATIC, DCM_APPL_DATA)LpTxBuffer;
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST)LpDcmPduIdTable;
  #endif
  uint32 LulFilledPgLen;
  #if((DCM_OBD_GETDTC_03_SERVICE == STD_ON) \
      || (DCM_OBD_GETDTC_07_SERVICE == STD_ON) \
      || (DCM_OBD_GETDTC_0A_SERVICE == STD_ON) \
      || (DCM_RPT_DTC == STD_ON) \
      || (DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON) \
      || (DCM_RPT_DTCBYSEVERITYINFOFDTC == STD_ON))
  uint8 LucFixedFilledPgLen;
  #endif

   #if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
   (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
   (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
   (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON) \
   || (DCM_OBD_GETDTC_03_SERVICE == STD_ON) \
   || (DCM_OBD_GETDTC_07_SERVICE == STD_ON) \
   || (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))

  uint8 LucSID;
  #endif

  #if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
   (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
   (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
   (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))

  uint8 LucRxTxBufferId;
  uint8 LucPIDCount;
  #endif

  #if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
     (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
  uint8 LucIDType;
  #endif

  #if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
     (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
  LucIDType = DCM_ZERO;
  #endif

  LulFilledPgLen = DCM_ZERO;

   #if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
   (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
   (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) \
   || (DCM_OBD_GETDTC_03_SERVICE == STD_ON) \
   || (DCM_OBD_GETDTC_07_SERVICE == STD_ON) \
   || (DCM_OBD_GETDTC_0A_SERVICE == STD_ON) \
   || (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))

  LucSID = Dcm_GstMsgContext.idContext & DCM_SID_MASK;

  /*
   * Check whether if it is the first page that is to be
   * transmitted
   */
  if((LucSID == DCM_THREE) || (LucSID == DCM_SEVEN) || (LucSID == DCM_TEN))
  {

    #if((DCM_OBD_GETDTC_03_SERVICE == STD_ON) \
      || (DCM_OBD_GETDTC_07_SERVICE == STD_ON) \
      || (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))
     if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
    {
      /*
      * Common response for services: SubFunction +
      * DTCStatusavailabilityMask
      */
      /* Update the Number of filtered DTCs to the response buffer */
      Dcm_GpReqResData[DCM_ZERO] = Dcm_GucNumofDTC;
      /* Re-Initialize the response buffer pointer */
      Dcm_GpReqResData = &Dcm_GpReqResData[DCM_ONE];
      /* Decrement the response buffer size by Two */
      Dcm_GulBufferSize -= DCM_ONE;
      /* Indicate how many bytes are filled in the page */
      LucFixedFilledPgLen = DCM_ONE;
    }
    else
    {
      LucFixedFilledPgLen = DCM_ZERO;
    }
    /*
      * Process the subfunction to update the buffer with response
      * data containing the DTC and Status information and update
      * the filled page length
    */
    LulFilledPgLen = Dcm_DspReadOBDDTCInfo(Dcm_GulBufferSize);
    /*
        * Update the final number of bytes that is filled in the page
        * that is to be processed
     */
    LulFilledPgLen += LucFixedFilledPgLen;
    #endif
  }
  else if((LucSID == DCM_ONE) || (LucSID == DCM_SIX) || (LucSID == DCM_EIGHT) || (LucSID == DCM_NINE))
  {
    #if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
        (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
        (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
        (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
    if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
    {
      /*  Update variable */
      Dcm_GulBufferSize = Dcm_GulBufferSize - DCM_ZERO;
      /* Request buffer */
      LpRxBuffer = Dcm_GstMsgContext.reqData;
      /* Response buffer */
      LpTxBuffer = Dcm_GstMsgContext.resData;
    }
    else
    {
      /* Request buffer */
      LpRxBuffer = &Dcm_GstMsgContext.reqData
        [Dcm_GstMsgContext.reqDataLen - Dcm_GucPIDCount];
      /* Update Pdu table */
      LpDcmPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
      /* Get the buffer Id of the TxPduId */
      LucRxTxBufferId = LpDcmPduIdTable->ucTxBufferId;
      /* Response buffer */
      LpTxBuffer = Dcm_GaaBufferConfig[LucRxTxBufferId].pBufferArea;
    }
    /* Update local variable with PID count */
    LucPIDCount = Dcm_GucPIDCount;

    switch(LucSID)
    {
      #if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON))
      case DCM_ONE :
           LucIDType = DCM_GET_PID;
      break;
      #endif

      #if((DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON))
      case DCM_SIX :
           LucIDType = DCM_GET_OBDMID;
      break;
      #endif

      #if((DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON))
      case DCM_EIGHT :
           LucIDType = DCM_GET_TID;
      break;
      #endif

      #if((DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
      case DCM_NINE :
           LucIDType = DCM_GET_VID;
      break;
      #endif
      default :
        /* Do Nothing */
      break;
    }
    #if(DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
    if((LucSID == DCM_ONE) && (Dcm_GucAvlState != DCM_AVAIL_ID))
    {
        /* Do Nothing */
    }
    else
    {
        LulFilledPgLen = Dcm_DspReadOBD_AvlInfo(LpRxBuffer, LpTxBuffer,
          Dcm_GulBufferSize, LucPIDCount, LucIDType);
    }
    #endif

    #if((DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
    (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
    (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
    LulFilledPgLen = Dcm_DspReadOBD_AvlInfo(LpRxBuffer,
      LpTxBuffer, Dcm_GulBufferSize, LucPIDCount, LucIDType);
    #endif

    #endif
  }
  else
  #endif
  {
    switch(Dcm_GucSubFunction)
    {
      #if((DCM_RPT_DTC == STD_ON) || (DCM_RPT_DTCBYSEVERITYMASKRECORD == \
                          STD_ON) || (DCM_RPT_DTCBYSEVERITYINFOFDTC == STD_ON))
      /*
        * Check if the requested sub function is either 0x08, 0x09, 0x0A,
        * or 0x0F
      */
      case DCM_TWO:
      case DCM_EIGHT:
      case DCM_NINE:
      case DCM_TEN:
      case DCM_FIFTEEN:
      case DCM_NINETEEN:
      case DCM_TWENTYONE:

        /*
        * Check whether if it is the first page that is to be
        * transmitted
        */
        if(Dcm_DspSerPgStatus.ucFirstPage ==
          DCM_FALSE)
        {
          /*
          * Common response for services: SubFunction +
          * DTCStatusavailabilityMask
          */
          /* Update the sub function to the response buffer */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
          /*
          * The variable Dcm_GucRecordNumber contains the
          * availability mask
          */
          Dcm_GpReqResData[DCM_ONE]  = Dcm_GucRecordNumber;
          /* Re-Initialize the response buffer pointer */
          Dcm_GpReqResData = &Dcm_GpReqResData[DCM_TWO];
          /* Decrement the response buffer size by Two */
          Dcm_GulBufferSize -= DCM_TWO;
          /* Indicate how many bytes are filled in the page */
          LucFixedFilledPgLen = DCM_TWO;
        }
        else
        {
          LucFixedFilledPgLen = DCM_ZERO;
        }
          #if(DCM_RPT_DTC == STD_ON)
          /* If the sub functions are 0x02, 0x0A, 0x0F */
          if(((Dcm_GucSubFunction & DCM_RD_SUPPORTED_DTC_FCTMASK) ==
             DCM_RD_SUPPORTED_DTC_FCTMASK) ||
             (Dcm_GucSubFunction == DCM_TWENTYONE))
          {
            /* If the sub functions is 0x0A*/
            /*
             * Process the subfunction to update the buffer with response
             * data containing the DTC and Status information and update
             * the filled page length
            */
            LulFilledPgLen = Dcm_DspReadReqdDTCInfo(Dcm_GulBufferSize);
          }
          else
          #endif
          {
            #if((DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON) || \
               (DCM_RPT_DTCBYSEVERITYINFOFDTC == STD_ON))
               /*
                * If the sub functions are 0x08 or 0x09, process the
                * subfunction to update the buffer with response
                * data containing the Severity, Functional unit, DTC and
                * Status information and update the filled page length
               */
              LulFilledPgLen =
                Dcm_DspUpdDTCBySeverityMask(Dcm_GulBufferSize);
            #endif
          }
           /*
            * Update the final number of bytes that is filled in the page
            * that is to be processed
           */
          LulFilledPgLen += LucFixedFilledPgLen;
      break;
      #endif
      #if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON))
      /* Check if the requested sub function is either 0x04 or 0x05 */
      case DCM_FOUR:
        /*
        * Check whether if it is the first page that is to be
        * transmitted
        */
        if(Dcm_DspSerPgStatus.ucFirstPage ==
           DCM_FALSE)
        {
           #if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
              (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
           /* Assemble the initial response message */
           Dcm_DspUpdateBasicsOfEventData();
           #endif
           /* Decrement the response buffer size by five */
           Dcm_GulBufferSize = Dcm_GulBufferSize - DCM_FIVE;

          /* Check if no NRC was reported */
          if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
          {
            LulFilledPgLen =
            Dcm_DspProcessSubFctFFData(Dcm_GucRecordNumber,
              Dcm_GulBufferSize);
          }
          /*
          * Update the final number of bytes that is filled in
          * the page that is to be processed
          */
          LulFilledPgLen += DCM_FIVE;
        }
        /* If the paged process is for other than the first page */
        else
        {
          LulFilledPgLen = Dcm_DspProcessSubFctFFData(
            Dcm_GucRecordNumber, Dcm_GulBufferSize);
        }
      break;
      #endif /* ((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) ||
                          (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM)) */

      #if((DCM_RPT_DTC_FLT_DET_CTR == STD_ON) || \
        (DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON))
      case DCM_TWENTY:
      case DCM_THREE:
        /*
        * Check whether if it is the first page that is to be
        * transmitted
        */
        if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
        {
          /* Update the sub function */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
          /* MISRA Rule        : 17.4
            Message            : Increment or decrement operation
                                 performed on pointer
            Reason             : Increment operator not used
                                 to achieve better throughput.
            Verification       : However, part of the code
                                 is verified manually and
                                 it is not having any impact.
          */
          /* Reset the pointer to the response data buffer */
          Dcm_GpReqResData++;
          /* Decrement the response buffer size by Two */
          Dcm_GulBufferSize -= DCM_ONE;
          #if(DCM_RPT_DTC_FLT_DET_CTR == STD_ON)
          LulFilledPgLen = Dcm_DspReadReqdDTCFDC(Dcm_GulBufferSize);
          #else
          LulFilledPgLen = Dcm_DspRepDTCSnapRecID(Dcm_GulBufferSize);
          #endif
          LulFilledPgLen = LulFilledPgLen + DCM_ONE;
        }
      break;
      #endif
      default:
      /* Do Nothing */
      break;
    }
  }
  /* Check if no NRC was reported */
  if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
  {
    /* Request DSD to process the page that was updated previously */
    Dcm_DsdProcessPage(LulFilledPgLen);
    /* Check if the process page was called for the last page */
    if(Dcm_DspSerPgStatus.ucLastPage == DCM_TRUE)
    {
      #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
      Dcm_InternalTroubleCodeService = DCM_FALSE;
      #endif

      #if(DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON)
      /*
        * Release the data contained in this record so has to access
        * or manipulate by the external application
        */
      if(Dcm_GucSubFunction == DCM_FOUR)

      {
        /* To enable DTC record update */
        (void)Dem_EnableDTCRecordUpdate();
      }
      #endif
      /* Clear the last page bit flag */
      Dcm_DspSerPgStatus.ucLastPage = DCM_FALSE;
    }
  }
  /* If any NRC occurred during paged transmission */
  else
  {
    #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
    Dcm_InternalTroubleCodeService = DCM_FALSE;
    #endif

    /* Set the negative response */
    Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
    /* Indicate DSD to transmit the negative response to the DSL layer */
    Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
  }
}
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : DspInternal_DcmConfirmation                         **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : This is an internal function that clears the        **
**                        appropriate variable based on the requested         **
**                        service. This service confirms the successful       **
**                        transmission or a transmission error of a           **
**                        diagnostic service                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : idContext, dcmRxPduId, status                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaDiagSessionConfig,      **
**                        Dcm_GucFailedSecurityAccessCount,                   **
**                        Function(s) invoked : DslInternal_SetSesCtrlType,   **
**                        Dcm_DslSetSesTimingValues                           **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) DspInternal_DcmConfirmation (Dcm_IdContextType LucIdContext,
  PduIdType LucDcmRxPduId, Dcm_ConfirmationStatusType LucStatus)
{
  #if((DCM_DSP_STOP_DIAG_SESSION_SERVICE == STD_ON) || \
      (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON))
  P2CONST(Dcm_DiagSessionConfigType, AUTOMATIC, DCM_APPL_CONST) LpDiagData;
  Dcm_TimerServerType LddTimerData;
  #endif

  if ((NULL_PTR != Dcm_GstMsgContext.reqData) && (Dcm_GstMsgContext.dcmRxPduId == LucDcmRxPduId))
      
  {
    switch(LucIdContext)
    {
      /* Service 0x87 LinkControl:  
      This service is used to gain bus bandwidth for diagnostic purposes        
      The Service LinkControl (0x87) is user optional. There are different project 
      specific use cases which are not handled in the default Dcm. One use case is to 
      switch the bandwidth in application an other use case performs an OEM bootloader 
      jump.  
       
      Therefore the service LinkControl needs to be implemented project specific as 
      external service (refer to Chapter 8.9 DCM as Service-Component) */
      /* case DCM_LINKCONTROL_SERVICE: */
      case DCM_DIAG_SESSION: 
      {
        /* TODO TODO TODO TODO TODO TODO:  SESSIONCONTROL SHALL BE  REDESIGNED */
        #if (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
        boolean doAction = DCM_FALSE;
        uint8 LucBootsession;
        
        /* Get the pointer to diagnostic session service */
        LpDiagData = &Dcm_GaaDiagSessionConfig[Dcm_DiagSessionState.sessionTableIndex];

	    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
        LucBootsession = LpDiagData->ucSesForBootLevel;

        /* in case of LblSendPendingResp sets to true in Dcm_Internal_GblFirstCallToMain
         * after ECUReset is processed with Dcm_GddProgConditions.ResponseRequired 1 at the BootLoader,
         * Dcm shall transmit a response message 
         * 
         * TODO : If session changeds to default(not programmingSession) in FBL , 
         * determine wether ECU performs reset or not */
	/* polyspace +1 MISRA-C3:10.4 [Justified:Low] "Not a defect" */
        if (DCM_FALSE == Dcm_GblPosRspTransOnReset) 
        {
          if (DCM_RES_NEG_OK == LucStatus)
          {
            /* ResponsePending */
	    /* polyspace +1 MISRA-C3:10.4 [Justified:Low] "Not a defect" */
            if (DCM_TRUE == Dcm_DiagSessionState.sendPendingResp)
            {    
              doAction = DCM_TRUE;
            }
          }
          else if (DCM_RES_POS_OK == LucStatus)
          {
            /*LblSendPendingResp = DCM_FALSE;*/
            doAction = DCM_TRUE;
          }
          else
          {
            /*LblSendPendingResp = DCM_FALSE;*/
            /* doAction == DCM_FALSE; */
          }
        }
        else
        {
          /*LblSendPendingResp = DCM_FALSE;*/
          /* doAction == DCM_FALSE; */
        }

        /* FIXME : Dcm_GblPosRspTransOnReset */
	/* polyspace +1 MISRA-C3:10.4 [Justified:Low] "Not a defect" */
        if ((DCM_TRUE == doAction) && (Dcm_DiagSessionState.sessionTableIndex < Dcm_Num_Of_Diag_Session_Config))
        {
          Dcm_SesCtrlType LucSessionLevel;     
          
          /* Update the P2ServerMax and P2*ServerMax timer values */
          LddTimerData.Timer_P2ServerMax = LpDiagData->usSesP2ServerMax;
          LddTimerData.Timer_P2StarServerMax =
                                  LpDiagData->usSesP2StrServerMax;

          LucSessionLevel = LpDiagData->ddSesCtrlLevel;
                                  
          /* Set the new session type */
          DslInternal_SetSesCtrlType(LucSessionLevel);
          
          /* Set the new session timing values */
          Dcm_DslSetSesTimingValues(&LddTimerData);
          
          (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(LucSessionLevel);        
                      
          /* Start - Bug : Session timeout , fixed by YoungJin Yun*/
          if (DCM_TRUE == Dcm_GstMsgContext.msgAddInfo.suppressPosResponse)
          {
            /* Start the s3 timer value */
            SchM_Enter_Dcm_TimerProtection();
            DCM_START_TIMER(DCM_S3SERVER_TIMER,
              (Dcm_GstCurrentTimingValue.Timer_S3Server));
            Dcm_TimerReqFlagStatus.ucS3Timer = DCM_TRUE;
            SchM_Exit_Dcm_TimerProtection();
          }      

          if ((LucBootsession == DCM_SESSION_JUMPTOBOOTLOADER) || 
                (LucBootsession == DCM_SESSION_JUMPTOSYSSUPPLIERBOOTLOADER))
          { 
            Dcm_GblExecuteECUReset = DCM_TRUE;
            Dcm_GblReset = DCM_TRUE;
          }
        }
        else
        {          
          if ((LucBootsession == DCM_SESSION_JUMPTOBOOTLOADER) || 
              (LucBootsession == DCM_SESSION_JUMPTOSYSSUPPLIERBOOTLOADER))
          {
            /* cancel reprogramming */
            Dcm_GddProgConditions.ReprogramingRequest = DCM_FALSE;
            (void)Dcm_SetProgConditions(&Dcm_GddProgConditions);
          }
        }
        Dcm_DiagSessionState.sendPendingResp = DCM_FALSE;
        Dcm_GblPosRspTransOnReset = DCM_FALSE;
        #endif
        break;
      }
      /* For Enable normal message transmission Service */
      case DCM_STOP_DIAGNOSTIC_SESSION:
        /* Added by youngjin.yun , new service is added as per ES95486 */
        #if(DCM_DSP_STOP_DIAG_SESSION_SERVICE== STD_ON)
        
        if (LucStatus == DCM_RES_POS_OK)
        {
          if (Dcm_DiagSessionState.sessionTableIndex < Dcm_Num_Of_Diag_Session_Config)
          {
            /* Get the pointer to diagnostic session service */
            LpDiagData = &Dcm_GaaDiagSessionConfig[Dcm_DiagSessionState.sessionTableIndex];
  
            /* Update the P2ServerMax and P2*ServerMax timer values */
	        /* polyspace+1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
            LddTimerData.Timer_P2ServerMax = LpDiagData->usSesP2ServerMax;
            LddTimerData.Timer_P2StarServerMax = LpDiagData->usSesP2StrServerMax;             
            DslInternal_SetSesCtrlType(DCM_DEFAULT_SESSION);
  
            /* Set the new session timing values */
            Dcm_DslSetSesTimingValues(&LddTimerData);
  
            (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(DCM_DEFAULT_SESSION);
  
            Dcm_GblNormalReq = DCM_FALSE;
            /* Inform ComM about the change in diagnostic session */
            ComM_DCM_InactiveDiagnostic((NetworkHandleType)Dcm_GulChannelIdentifier);
  
            /* Stop the timer */
            DCM_STOP_TIMER(DCM_S3SERVER_TIMER);
            Dcm_TimerReqFlagStatus.ucS3Timer = DCM_FALSE;    
          }
        }
        #endif
        break;
        
      case DCM_READDTC_SERVICE:
        /* if status is not ok? */
        Dcm_DspSerPgStatus.ucDemDisableInvoked = DCM_FALSE;
        Dcm_DspSerPgStatus.ucLastPage = DCM_FALSE;
        Dcm_DspSerPgStatus.ucUpdatePageStarted = DCM_FALSE;
        Dcm_DspSerPgStatus.ucPagingStarted = DCM_FALSE;
        Dcm_DspSerPgStatus.ucFirstPage = DCM_FALSE;
        Dcm_DspSerPgStatus.ucPagingInMid = DCM_FALSE;
        Dcm_DspSerPgStatus.ucMultipleRecd = DCM_FALSE;
        Dcm_DspSerPgStatus.ucSecSeedReq = DCM_FALSE;
        break;
        
      /*For EcuReset Services*/    
      case DCM_ECU_SERVICE:
        #if(DCM_ECURESET_SERVICE == STD_ON)     
        if (LucStatus == DCM_RES_POS_OK) 
        {
          /* polyspace<RTE: NIV : Not a defect : No Action Planned > initialized variable */
	      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */  
          if ((Dcm_GstMsgContext.reqData[0U] & DCM_SUBFUNCTION_MASK) == HARD)
          {
             Dcm_GblReset = DCM_TRUE;
          }

          /* Fixed by youngjin.yun  for preventing multiple activation reset task */
          Dcm_GblExecuteECUReset = DCM_TRUE;
          /*Invoke Reset Execution of of ECU*/
          /* SchM_Switch_Dcm_DcmEcuReset(EXECUTE); */
        }
        #endif      
        break;

      case DCM_COMMUNICATION_SERVICE:
        /* No break */
      case DCM_ENABLE_NORMAL_MESG_TRANSMISSION_SERVICE:
        #if((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) || (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
        if (LucStatus == DCM_RES_POS_OK)
        {
          DcmCommControlConfirmation (LucIdContext, LucStatus);
        }
        #endif
        break;      
      default:
	  /* Do Nothing */
        break;
    }
  }    
  else
  {
    #if((DCM_STANDARD_SUPPORT != DCM_ES96590_SUPPORT) && (DCM_STANDARD_SUPPORT != DCM_QZN04_SUPPORT))
    Dcm_GucFailedSecurityAccessCount = DCM_ZERO;

    #endif
    Dcm_DspSerPgStatus.ucSecSeedReq = DCM_FALSE;
    Dcm_DspSerPgStatus.ucDemDisableInvoked = DCM_FALSE;
    Dcm_DspSerPgStatus.ucLastPage = DCM_FALSE;
    Dcm_DspSerPgStatus.ucUpdatePageStarted = DCM_FALSE;
    Dcm_DspSerPgStatus.ucPagingStarted = DCM_FALSE;
    Dcm_DspSerPgStatus.ucFirstPage = DCM_FALSE;
    Dcm_DspSerPgStatus.ucPagingInMid = DCM_FALSE;
    Dcm_DspSerPgStatus.ucMultipleRecd = DCM_FALSE;
  }
}

/*******************************************************************************
** Function Name        : DcmCommControlConfirmation                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function that clears the        **
**                        appropriate variable based on the requested         **
**                        Communication Control service.                      **
**                        This service confirms the successful transmission   **
**                        or a transmission error of a diagnostic service     **
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
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_DspSerPgStatus                                  **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) || \
    (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
/* Fixed by youngjin.yun, 2014-12-12,
 * shall be processed when suppressed bit is true */
static FUNC(void, DCM_CODE) DcmCommControlConfirmation (Dcm_IdContextType LucIdContext,
  Dcm_ConfirmationStatusType LucStatus)
{
  uint8 LucLoopcount;

  CONST(uint8, DCM_CONST) commCtrlTypeList[4][4] =
  {
    /*The range of Dcm_GucCommunicationModeType is between 0x01 and 0x03, so
      the entity 0 is dummy set. */
    {
      DCM_COMMUNICATIONMODETYPE_UNDEFINED,
      DCM_COMMUNICATIONMODETYPE_UNDEFINED,
      DCM_COMMUNICATIONMODETYPE_UNDEFINED,
      DCM_COMMUNICATIONMODETYPE_UNDEFINED
    },
  #if(DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)
    /* ES95486 only support communicationType which is DCM_COMM_TYPE_NORMAL  */
    /* DCM_COMM_TYPE_NORMAL = 1 */
    {
      DCM_ENABLE_RX_TX_NORM,         /* DCM_CC_ENABLE_RX_AND_TX = 0 */
      DCM_DISABLE_RX_TX_NORM_NM,     /* DCM_CC_DISABLE_RX_AND_TX = 1 */
      DCM_DISABLE_RX_TX_NORM_NM,     /* DCM_CC_DISABLE_RX_AND_TX_NORESP = 2 */
      DCM_DISABLE_RX_TX_NORM         /* DCM_CC_DISABLE_RX_AND_TX_COMM_TYPE = 3 */
    },
    /* DCM_COMM_TYPE_NM = 2 */
    {
      DCM_ENABLE_RX_TX_NM,
      DCM_DISABLE_RX_TX_NORMAL,
      DCM_DISABLE_RX_TX_NORMAL,
      DCM_DISABLE_RX_TX_NM
    },
    /* DCM_COMM_TYPE_NM_AND_NORMAL = 3 */
    {
      DCM_ENABLE_RX_TX_NORM_NM,
      DCM_DISABLE_RX_TX_NORMAL,
      DCM_DISABLE_RX_TX_NORMAL,
      DCM_DISABLE_RX_TX_NORM_NM
    }
  };
  #else /*if(DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) */
    /* DCM_COMM_TYPE_NORMAL = 1 */
    { 
      DCM_ENABLE_RX_TX_NORM,              /* enableRxAndTx        0 */ 
      DCM_ENABLE_RX_DISABLE_TX_NORM,      /* enableRxAndDisableTx 1 */
      DCM_DISABLE_RX_ENABLE_TX_NORM,      /* disableRxAndEnableTx 2 */
      DCM_DISABLE_RX_TX_NORMAL            /* disableRxAndTx       3 */
    },
    /* DCM_COMM_TYPE_NM = 2 */
    {
      DCM_ENABLE_RX_TX_NM,                /* enableRxAndTx        0 */ 
      DCM_ENABLE_RX_DISABLE_TX_NM,        /* enableRxAndDisableTx 1 */
      DCM_DISABLE_RX_ENABLE_TX_NM,        /* disableRxAndEnableTx 2 */
      DCM_DISABLE_RX_TX_NM,               /* disableRxAndTx       3 */
    },
    /* DCM_COMM_TYPE_NM_AND_NORMAL = 3 */
    {
      DCM_ENABLE_RX_TX_NORM_NM,           /* enableRxAndTx        0 */ 
      DCM_ENABLE_RX_DISABLE_TX_NORM_NM,   /* enableRxAndDisableTx 1 */
      DCM_DISABLE_RX_ENABLE_TX_NORM_NM,   /* disableRxAndEnableTx 2 */
      DCM_DISABLE_RX_TX_NORM_NM           /* disableRxAndTx       3 */
    }
  };
  #endif
   
  /* Fixed by youngjin.yun, 2014-12-07,
   * DCM_RES_POS_NOT_OK : when suppression mask is true : By yj.yun */
  if ((LucIdContext == DCM_COMMUNICATION_SERVICE) &&
      (Dcm_GucCommunicationModeType <= DCM_COMM_TYPE_NM_AND_NORMAL) &&
      (Dcm_GucSubFunction <= DCM_CC_DISABLE_RX_AND_TX))
  {
    Dcm_GucComCtrlMode = commCtrlTypeList[Dcm_GucCommunicationModeType][Dcm_GucSubFunction];
    if (DCM_COMMUNICATIONMODETYPE_UNDEFINED != Dcm_GucComCtrlMode)
    {
      #if(DCM_TOTAL_NUM_OF_ALL_CHANNEL != 0u)
      if(Dcm_GucSubNetValue == 0u)
      {
        for(LucLoopcount = 0u;LucLoopcount < Dcm_Total_Num_Of_All_Channel; LucLoopcount++)
        {
	      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */  
          if(NULL_PTR != Dcm_GaaAllCommControlConfig[LucLoopcount].pSchMSwitchAllCommModeFunc)
          {
            Dcm_GaaAllCommControlConfig[LucLoopcount].pSchMSwitchAllCommModeFunc(Dcm_GucComCtrlMode);
            (void)BswM_Dcm_CommunicationMode_CurrentState(
             Dcm_GaaAllCommControlConfig[LucLoopcount].ucComChannelRef, Dcm_GucComCtrlMode);
          }
          else
          {
            DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);
          }
        }
      }
      else
      #endif    
      if(Dcm_GucSubNetValue == DCM_FIFTEEN)
      {
        if (Dcm_GstMsgContext.dcmRxPduId >= Dcm_Num_Of_PduidTableConfig)
        {
          DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);
        }
        else
        { 
          if(NULL_PTR != Dcm_GaaPduIdTableConfig[Dcm_GstMsgContext.dcmRxPduId].pSchMSwitchCommModeFunc) 
          {
            /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
            Dcm_GaaPduIdTableConfig[Dcm_GstMsgContext.dcmRxPduId].pSchMSwitchCommModeFunc(Dcm_GucComCtrlMode);
        
            (void)BswM_Dcm_CommunicationMode_CurrentState(
              Dcm_GaaPduIdTableConfig[Dcm_GstMsgContext.dcmRxPduId].ucRxComChannelRef, 
              Dcm_GucComCtrlMode);
          }
          else
          {
            DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);          
          }
        }
      }
      else
      {
        for (
          LucLoopcount = 0u; 
          LucLoopcount < Dcm_Num_Of_CommControlConfig;  /* == Dcm_Total_Num_Of_Specific_Channel*/
          LucLoopcount++)
        {
          if(Dcm_GaaCommControlConfig[LucLoopcount].ucSubNetNumber == Dcm_GucSubNetValue)
          {
            if(NULL_PTR != Dcm_GaaCommControlConfig[LucLoopcount].pSchMSwitchCommModeFunc)
            {
              Dcm_GaaCommControlConfig[LucLoopcount].pSchMSwitchCommModeFunc(Dcm_GucComCtrlMode);
              (void)BswM_Dcm_CommunicationMode_CurrentState(
                Dcm_GaaCommControlConfig[LucLoopcount].ucSingleComChannelRef, Dcm_GucComCtrlMode);
            }
            else
            {
              DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);            
            }
            break;
          }
        }      
      }
    }
  }
  /* Fixed by youngjin.yun, 2014-12-09, suppressed bit is true,
   * For Enable normal message transmission Service */
  else if (LucIdContext == DCM_ENABLE_NORMAL_MESG_TRANSMISSION_SERVICE)
  {
    /* Bug #6217 : Modified by Jin, 161019 */
    Dcm_GucComCtrlMode = commCtrlTypeList[Dcm_GucCommunicationModeType][DCM_CC_ENABLE_RX_AND_TX];
    
    #if(DCM_TOTAL_NUM_OF_ALL_CHANNEL != 0u)
    for (LucLoopcount = 0u;
      LucLoopcount < Dcm_Total_Num_Of_All_Channel; 
      LucLoopcount++)
    {
      if(NULL_PTR != Dcm_GaaAllCommControlConfig[LucLoopcount].pSchMSwitchAllCommModeFunc)
      {
        Dcm_GaaAllCommControlConfig[LucLoopcount].pSchMSwitchAllCommModeFunc(Dcm_GucComCtrlMode);
        (void)BswM_Dcm_CommunicationMode_CurrentState(
          Dcm_GaaAllCommControlConfig[LucLoopcount].ucComChannelRef, Dcm_GucComCtrlMode);
      }
      else
      {
        DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM_POINTER);      
      }
    }
    #endif
  }
  else
  {
    /* Do nothing */
  }

  DCM_UNUSED(LucStatus);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspCancelPagedBufferProcessing                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function to stop processing of  **
**                        the diagnostic service and to clear the internal    **
**                        variables if the page buffer processing was         **
**                        cancelled due to time out                           **
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
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_DspSerPgStatus                                  **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspCancelPagedBufferProcessing(void)
{
  /* Clear all read DTC service flags */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_GucSubFunction = DCM_ZERO;
  Dcm_DspSerPgStatus.ucDemDisableInvoked = DCM_FALSE;
  Dcm_DspSerPgStatus.ucLastPage = DCM_FALSE;
  Dcm_DspSerPgStatus.ucUpdatePageStarted = DCM_FALSE;
  Dcm_DspSerPgStatus.ucPagingStarted = DCM_FALSE;
  Dcm_DspSerPgStatus.ucFirstPage = DCM_FALSE;
  Dcm_DspSerPgStatus.ucPagingInMid = DCM_FALSE;
  Dcm_DspSerPgStatus.ucMultipleRecd = DCM_FALSE;
  Dcm_DspSerPgStatus.ucSecSeedReq = DCM_FALSE;
}
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace:end<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function */
/* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
