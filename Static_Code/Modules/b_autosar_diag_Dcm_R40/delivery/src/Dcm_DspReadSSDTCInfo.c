/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DspReadSSDTCInfo.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the implementation of the Read DTC         **
**              subfunctions  0x03, 0x04, 0x06 and 0x10.                      **
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
** 2.3.8.0   14-May-2021   S.K      Park     #29848                           **
**                                                                            **
** 2.3.4.0   28-Jan-2021   EunKyung Kim      #27997                           **
**                                                                            **
** 1.0.3     28-03-2017    Jin     Jung      #4718                            **
**                                                                            **
** 1.0.2     03-03-2016    Sungeol Baek      #3754                            **
**                                                                            **
** 1.0.1     16-04-2015    Sungeol Baek      #2171                            **
**                                                                            **
** 1.0.0     09-01-2013    Autron            Initial Version                  **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_DspReadSSDTCInfo.h"
#include "Dcm_DspMain.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DspNonPagedDTCSubFct.h"
#include "Dcm_Config.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
    (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DspGetSizeOfData(
  uint8 LucRecordNumber,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) LpRespLenOfData);

static FUNC(uint32, DCM_CODE) Dcm_DspProcessExtDataRecd(
  uint8 LucRecordNumber, uint32 LulBufferSize,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:17.8 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:USELESS_WRITE [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-begin CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */

/*******************************************************************************
** Function Name        : Dcm_DspRptDTCSnapshotRecByDTCNum                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is sub-function of the service Read DTC        **
**                        information (service 0x19) to read the snapshot     **
**                        records and extended records for a particular DTC   **
**                        or a particular record. This service will be        **
**                        invoked for sub-function values 0x04, 0x06          **
**                        and 0x10                                            **
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
** Remarks              : Global Variable(s) : Dcm_GpReqResData,              **
**                        Dcm_GddNegRespError,                                **
**                        Dcm_DspSerPgStatus, Dcm_GucRecordNumber,            **
**                        Dcm_GucReadGlobal ,Dcm_GpMsgContext.                **
**                        Function(s) invoked : Dcm_DspGetSizeOfData,         **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_DspProcessSubFctFFData,                         **
**                        Dcm_DspProcessExtDataRecd ,                         **
**                        Dcm_DsdStartPagedProcessing                         **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
    (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
FUNC(void, DCM_CODE) Dcm_DspRptDTCSnapshotRecByDTCNum(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  uint32 LulRespLenOfFreezeFrame = (uint32)0x00;
  uint32 LulRespLenOfBuffSize;
  uint8 LucRecordNumber = (uint8)0x00;
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
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
    /* Initialize the global pointer with request data buffer address */
    Dcm_GpReqResData = pMsgContext->reqData;
    LpReqResData = pMsgContext->reqData;

    /* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Not a defect" */
    /* Update the record number from the request buffer */
    LucRecordNumber = LpReqResData[DCM_FOUR];

    /* Get the DTC for the input request */
    /* Update the DTC info to LddDTC from the request from the 3rd position */
    Dcm_GunDTC.ddByte.ucLsByte      = LpReqResData[DCM_THREE];
    Dcm_GunDTC.ddByte.ucMidLowByte  = LpReqResData[DCM_TWO];
    Dcm_GunDTC.ddByte.ucMidHiByte   = LpReqResData[DCM_ONE];
    Dcm_GunDTC.ddByte.ucMsByte      = DCM_ZERO;
    /* polyspace-end MISRA-C3:18.1 [Justified:Low] "Not a defect" */

    /* Calculate the size of a Freeze frame for a single or multiple records */
    Dcm_DspGetSizeOfData(LucRecordNumber, &LulRespLenOfFreezeFrame);
    /* Check whether any NRC is updated */
    if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
    {
      /* Update total response length to the pMsgContext */
      pMsgContext->resDataLen = LulRespLenOfFreezeFrame;
      /* Initialize the global pointer to the response data buffer */
      Dcm_GpReqResData = pMsgContext->resData;
      /*
       * Check if the response buffer is capable of accommodating the
       * complete response at once
       */
      if(LulRespLenOfFreezeFrame <= (pMsgContext->resMaxDataLen))
      {
        /* Sub function 0x04, 0x06/0x10 */
        #if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
          (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
        /* Assemble the initial response message */
        Dcm_DspUpdateBasicsOfEventData();
        /* Update the offset for the response buffer pointer */
        #endif

        if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
        {
          /* Re-Initialize the response length pending */
          LulRespLenOfBuffSize = LulRespLenOfFreezeFrame - DCM_FIVE;
          /*
                         * This function will update the Dcm_GddNegRespError in
                         * case of negative response
                         */
          /* Check for Sub function 0x04 */
          if((Dcm_GucSubFunction & DCM_DSP_FFSIZE_FCTMASK) ==
             DCM_RD_SSRECBYDTC_FCTMASK)
          {
             /*
                * Assemble the response of Freeze frame data for a particular DTC
                * or a snap shot number. Invoke the internal function for
                * processing the subfunctions 0x04 and 0x05.
                */
            if(LulRespLenOfBuffSize > DCM_ONE)
            {
              (void)Dcm_DspProcessSubFctFFData(
                LucRecordNumber, LulRespLenOfBuffSize);
            }
          }
          /* Check for Sub function 0x06, 0x10 */
          else
          {
            /*
              * Assemble the response of extended data for the DTC from primary
              * or mirror memory.Invoke the internal function for processing
              * the subfunctions 0x06 and 0x10.
                             */
            if(LulRespLenOfBuffSize > DCM_ONE)
            {
              (void)Dcm_DspProcessExtDataRecd(LucRecordNumber,
              LulRespLenOfBuffSize, pMsgContext);
            }
          }
        }
      }
      else
      {
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
          /* Update the global bit flag indicating paging started to TRUE */
          Dcm_DspSerPgStatus.ucPagingStarted = DCM_TRUE;
          /* Update the global variable with the record number */
          Dcm_GucRecordNumber = LucRecordNumber;
          /* Start the paged processing */
          Dcm_DsdStartPagedProcessing(pMsgContext);
        #else
         /*
                  * Update the NRC if the response length is greater than the
                  * response buffer size
                  */
          Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
        #endif
      }
    }
  }
   
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
  #endif
  {
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}
#endif /* ((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) ||
                 (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON)) */

/*******************************************************************************
** Function Name        : Dcm_DspGetSizeOfData                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function to calculate the size  **
**                        of a Freeze frame or extended data for a single     **
**                        or multiple records                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucRecordNumber                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpRespLenOfData                                     **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_GunDTC.                                         **
**                        Function(s) invoked : Dem_GetSizeOfFreezeFrame,     **
**                        Dem_GetSizeOfExtendedDataRecordByDTC                **
**                        Dem_GetDTCOfFreezeFrameRecord                       **
**                                                                            **
*******************************************************************************/
#if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
    (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DspGetSizeOfData(uint8 LucRecordNumber,
      P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) LpRespLenOfData)
{
  Dem_DTCOriginType LddDTCOrigin;
  uint16 LusSizeOfData;
  uint8 LucReturnRes;
  LusSizeOfData = DCM_ZERO;
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

  if((Dcm_GucSubFunction & DCM_DSP_ORG_MASK) == DCM_DSP_ORG_MASK)
  {
    /* Update Mirror memory */
    LddDTCOrigin = DEM_DTC_ORIGIN_MIRROR_MEMORY;
  }
  else
  {
    /* Update Primary memory */
    LddDTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
  }

  if((Dcm_GucSubFunction == DCM_SIX) || (Dcm_GucSubFunction == DCM_SIXTEEN))
  {
    LucReturnRes = Dem_GetSizeOfExtendedDataRecordByDTC (
    Dcm_GunDTC.ulLongReg32, LddDTCOrigin, LucRecordNumber,
    &LusSizeOfData);

      /* For Qac */
    if((LucReturnRes == DEM_GET_SIZEOFEDRBYDTC_W_RNUM) ||
      (LucReturnRes == DEM_GET_SIZEOFEDRBYDTC_W_DTC) ||
      (LucReturnRes == DEM_GET_SIZEOFEDRBYDTC_W_DTCOR))
    {
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      /* For Qac */
    }
  }
  else /* if (Dcm_GucSubFunction == 0x04) */
  {
    /*Calculate the size of the freeze frame for sub function 0x04 */
    LucReturnRes = Dem_GetSizeOfFreezeFrameByDTC(Dcm_GunDTC.ulLongReg32,
      DEM_DTC_ORIGIN_PRIMARY_MEMORY, LucRecordNumber,
      &LusSizeOfData);
    /* check for positive return type */
      /* for Qac */
    if((LucReturnRes == DEM_GET_SIZEOFFF_WRONG_RNUM) ||
    (LucReturnRes == DEM_GET_SIZEOFFF_WRONG_DTC) ||
    (LucReturnRes == DEM_GET_SIZEOFFF_WRONG_DTCOR))
    {
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      /* for Qac */
    }
  }
  if((LucReturnRes == DCM_ZERO) && (LusSizeOfData != DCM_ZERO))
  {
    /* Update the complete freeze frame size for the output parameter */
    *LpRespLenOfData = (uint32)((uint32)0x05 + (uint32)LusSizeOfData);
  }
  else if (LusSizeOfData == DCM_ZERO)
  {
    /* Update the complete freeze frame size for the output parameter */
    *LpRespLenOfData = DCM_FIVE;
  }
  else
  {
  /* for Qac */
  }
}
#endif /* (DCM_READDTC_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DspProcessSubFctFFData                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function to assemble the        **
**                        response of Freeze frame data for a particular DTC  **
**                        or a snap shot number.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucRecordNumber, LulBufferSize                      **
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
**                        Dcm_GucRecordNumber, Dcm_GblMultipleRecord,         **
**                        Dcm_GddNegRespError, Dcm_GunDTC,                    **
**                        Dcm_GpReqResData.                                   **
**                        Function(s) invoked :                               **
**                        Dem_DisableDTCRecordUpdate,                         **
**                        Dem_GetFreezeFrameDataByDTC,                        **
**                        Dem_EnableDTCRecordUpdate,                          **
**                        Dem_GetDTCOfFreezeFrameRecord, Dem_GetStatusOfDTC   **
**                                                                            **
*******************************************************************************/
#if(DCM_READDTC_SUPPORT == STD_ON)
/* polyspace<MISRA-C:8.10:Not a defect:Justify with annotations> Whether the Dcm api function is required internal or external linkage, depends on user configuration */
FUNC(uint32, DCM_CODE) Dcm_DspProcessSubFctFFData(
  uint8 LucRecordNumber, uint32 LulBufferSize)
{
  Dem_DTCOriginType LddDTCOrigin;
  uint32 LulRemBufSize;
  uint32 LulRespBufferSize;
  uint16 LusTemp;
  uint8 LucTmpRecordNumber;
  uint8 LucReturnRes;
  boolean LblRecNumNegResp;

  /* Initialize variables */
  LucTmpRecordNumber = DCM_ZERO;
  LulRemBufSize = LulBufferSize;
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

  /* Primary memory */
  LddDTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
  /* Check if the pre compile option DCM_PAGEDBUFFER_ENABLED is enabled */
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /*
     * Check whether the global bit flag to indicate that it is other than the
     * first page which is to be processed
     */
  if(Dcm_DspSerPgStatus.ucFirstPage == DCM_TRUE)
  {
    /* Get the record number from the global variable */
    LucRecordNumber = Dcm_GucRecordNumber;
    /* Check whether multiple record */
    if (Dcm_GblMultipleRecord == DCM_TRUE)
    {
      /* Get the record number from the global variable */
      LucTmpRecordNumber = Dcm_GucRecordNumber;
    }
    else
    {
      /* Set the temporary record number to DCM_MAX_RECORDS */
      LucTmpRecordNumber = DCM_MAX_RECORDS;
    }
    LblRecNumNegResp = DCM_FALSE;
  }
  else
  #endif
  {
    /* Check if the record number requested is DCM_MAX_EXTND_RECORDS */
    if(LucRecordNumber == DCM_MAX_EXTND_RECORDS)
    {
      Dcm_DspSerPgStatus.ucMultipleRecd = DCM_TRUE;
      /* To indicate multiple record */
      Dcm_GblMultipleRecord = DCM_TRUE;
      /* Reset the record number to zero */
      LucRecordNumber = DCM_ZERO;
    }
    else
    {
      /* To indicate non multiple record */
      Dcm_GblMultipleRecord = DCM_FALSE;
      /* Set the temporary record number to DCM_MAX_RECORDS */
      LucTmpRecordNumber = DCM_MAX_RECORDS;
    }
    /* Disable data record update */
    LucReturnRes = Dem_DisableDTCRecordUpdate(
    Dcm_GunDTC.ulLongReg32, LddDTCOrigin);
    /* Check if the operation to disable data record update is not successful */
    if(LucReturnRes != E_OK)
    {
      /** 
       * FIXME
       * DEM_DISABLE_DTCRECUP_OK                                   ((uint8)0x00)
       * DEM_DISABLE_DTCRECUP_WRONG_DTC                            ((uint8)0x01)
       * DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN                      ((uint8)0x02)
       * DEM_DISABLE_DTCRECUP_PENDING                              ((uint8)0x03)
       *
       * [SWS_Dcm_01212] If Dem_DcmDisableDTCRecordUpdate() returns 
       * DEM_DISABLE_DTCRECUP_WRONG_DTC, the Dcm shall send a NRC 0x31 
       * (Request out of Range). 
       * 
       * [SWS_Dcm_01213] If Dem_DcmDisableDTCRecordUpdate() returns 
       * DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN, the Dcm shall send a NRC 
       * 0x31 (Request out of Range).
      */
      /* Update the error flag to TRUE */
      LblRecNumNegResp = DCM_TRUE;
      /* Update the global variable with the NRC value */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    /* Disable data record update is successful */
    else
    {
      /* Update the error flag to FALSE */
      LblRecNumNegResp = DCM_FALSE;
      /* Set bit flag indicating DTC record update is successfully disabled */
      Dcm_DspSerPgStatus.ucDemDisableInvoked = DCM_TRUE;
    }
  }
  /* Check till all the record numbers are read and no NRC is reported */
  while((LucTmpRecordNumber < DCM_MAX_EXTND_RECORDS) &&
    (LblRecNumNegResp == DCM_FALSE) && (LulRemBufSize != DCM_ZERO))
  {
      /* Check whether pre compile option DCM_PAGEDBUFFER_ENABLED is enabled */
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if (Dcm_DspSerPgStatus.ucPagingInMid == DCM_TRUE)
      {
        Dcm_DspSerPgStatus.ucPagingInMid = DCM_FALSE;
      }
      else
      #endif
      {
        /*
         * If the remaining buffer size is greater than the maximum
         * Freezeframe Data size for any DataId then update it with 256
         */
        if(LulRemBufSize > DCM_MAX_RECDDATA_SIZE)
        {
          /* Update buffer size as MAX */
          LulRespBufferSize = DCM_MAX_RECDDATA_SIZE;
        }
        else
        {
          /* Update buffer size from the local variable */
          LulRespBufferSize = LulRemBufSize;
        }
        if(Dcm_DspSerPgStatus.ucFirstPage == DCM_TRUE)
        {
          if(Dcm_GblMultipleRecord == DCM_FALSE)
          {
            /*Dcm_GpReqResData = Dcm_GpReqResData - DCM_ONE;*/
			Dcm_GpReqResData--;
            LulRemBufSize = LulRemBufSize + DCM_ONE;
            LulRespBufferSize = LulRespBufferSize + DCM_ONE;
          }
        }
        LusTemp = (uint16)LulRespBufferSize;
        LucReturnRes = Dem_GetFreezeFrameDataByDTC(Dcm_GunDTC.ulLongReg32,
        DEM_DTC_ORIGIN_PRIMARY_MEMORY, LucRecordNumber, Dcm_GpReqResData,
        &LusTemp);
        LulRespBufferSize = (uint32)LusTemp;
        /* Check whether FreezeFrame data is successfully returned */
        if(LucReturnRes == DEM_GET_FFDATABYDTC_OK)
        {
          /* Update remaining buffer size */
          LulRemBufSize = LulRemBufSize - LulRespBufferSize;
          /* Increment the pointer by BufSize bytes */
          Dcm_GpReqResData = &Dcm_GpReqResData[LulRespBufferSize];
        }
        /* Check provided buffer size is too small */
        else if(LucReturnRes == DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE)
        {
          /*
           * Check whether pre compile option DCM_PAGEDBUFFER_ENABLED
           * is enabled
           */
          #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
          /* Provided buffer is small */
          if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
          {
            Dcm_DspSerPgStatus.ucPagingInMid = DCM_TRUE;
            Dcm_GucRecordNumber = LucRecordNumber;
          }
          else
          #endif
          {
            /* First page in the loop exceeds the available buffer size */
            Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
          }
          /* Update the variables to exit from the function */
          LblRecNumNegResp = DCM_TRUE;
        }
        else if(LucReturnRes == DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER)
        {
          /* For single record, its an error */
          if(Dcm_DspSerPgStatus.ucMultipleRecd == DCM_FALSE)
          {
            /* Update the variable to exit from the function */
            LblRecNumNegResp = DCM_TRUE;
            /* Update Negative response code */
            Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
          }
          /*
             * For multiple record number, increment the current record to
             * process the next record
          */
        }
        else if((LucReturnRes == DEM_GET_FFDATABYDTC_WRONG_DTC) ||
                (LucReturnRes == DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN))
        {
          /* Update Negative response code */
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
          /* Update the variables to exit from the function */
          LblRecNumNegResp = DCM_TRUE;
        }
    else
    {
      /* To avoid QAC warning */
    }
      /* Increment the temporary record number */
      LucTmpRecordNumber++;
      /* Increment the record number */
      LucRecordNumber++;
    }
  }
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
   /* Check if it is the first page is updated */
  if((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) &&
     (Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE))
  {
    /*
     * Set the global bit flag to indicate that the first page is
     * already processed
     */
    Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
  }
  #endif

  if((Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE) &&
   (Dcm_DspSerPgStatus.ucDemDisableInvoked == DCM_TRUE))
  {
   /* MISRA Rule         : 16.10
      Message            : If a function returns error information,
                           then that error information shall be tested.
      Reason             : There is no need for Dcm to validate the return
                           value of Dem_EnableDTCRecordUpdate.
      Verification       : However, part of the code is verified
                           manually and it is not having any impact.
      */
   /*
        * Release the data contained in this record so has to access or
        * manipulate by the external application
        */
    (void)Dem_EnableDTCRecordUpdate();
    /* Clear the bit flag indicating DTC record update is enabled */
    Dcm_DspSerPgStatus.ucDemDisableInvoked = DCM_FALSE;
  }
  /* Return the remaining size of the buffer */
  return(LulBufferSize - LulRemBufSize);
}
#endif /* (DCM_READDTC_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DspProcessExtDataRecd                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function to assemble the        **
**                        response of extended data for a particular DTC from **
**                        primary or mirror memory.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucRecordNumber, LulBufferSize                      **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GblMultipleRecord,                              **
**                        Dcm_GunDTC, Dcm_GucRecordNumber,                    **
**                        Dcm_DspSerPgStatus.                                 **
**                        Function(s) invoked : Dem_DisableDTCRecordUpdate,   **
**                        Dem_GetExtendedDataRecordByDTC,                     **
**                        Dem_EnableDTCRecordUpdate                           **
**                                                                            **
*******************************************************************************/
#if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
    (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
static FUNC(uint32, DCM_CODE) Dcm_DspProcessExtDataRecd(
  uint8 LucRecordNumber, uint32 LulBufferSize,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpResData;
  Dem_DTCOriginType LddDTCOrigin;
  uint32 LulRemBufSize;
  uint32 LulRespBufferSize;
  uint16 LusTemp;
  uint8 LucTmpRecordNumber;
  uint8 LucReturnRes;
  boolean LblRecNumNegResp;
  boolean LblFirstRecordUpdate;

  LblFirstRecordUpdate = DCM_FALSE;
  LblRecNumNegResp = DCM_FALSE;

  /* Initialize the local variable LulRemBufSize */
  LulRemBufSize = LulBufferSize;

  if (
    (pMsgContext == NULL_PTR) || 
    (pMsgContext->resData == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR) ||
    (Dcm_GpReqResData == NULL_PTR)    
  )
  {
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    if((Dcm_GucSubFunction & DCM_DSP_ORG_MASK) == DCM_DSP_ORG_MASK)
    {
      /* Mirror memory */
      LddDTCOrigin = DEM_DTC_ORIGIN_MIRROR_MEMORY;
    }
    else
    {
      /* Primary memory */
      LddDTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    }
    /* Check whether the pre compile option DCM_PAGEDBUFFER_ENABLED is enabled */
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /* Check if it is other than the first page that is in progress */
    if(Dcm_DspSerPgStatus.ucFirstPage == DCM_TRUE)
    {
      /* Get the record number from the global variable */
      LucRecordNumber = Dcm_GucRecordNumber;
      /* Get the record number from the global variable */
      if (Dcm_GblMultipleRecord == DCM_TRUE)
      {
        /* Get the record number from the global variable */
        LucTmpRecordNumber = Dcm_GucRecordNumber;
      }
      else
      {
        /* Set the temporary record number to DCM_MAX_RECORDS */
        LucTmpRecordNumber = DCM_MAX_RECORDS;
      }
    }
    else
    #endif
    {
      /* Start of block comment 1 */
      if(LucRecordNumber == DCM_MAX_EXTND_RECORDS)
      {
        Dcm_DspSerPgStatus.ucMultipleRecd = DCM_TRUE;
        /* Reset the record number to one */
        LucRecordNumber = DCM_ONE;
        /* Reset the temporary record number to zero */
        LucTmpRecordNumber = DCM_ONE;
        /* To indicate multiple record */
        Dcm_GblMultipleRecord = DCM_TRUE;
      }
      else if(LucRecordNumber == DCM_MAX_RECORDS)
      {
        Dcm_DspSerPgStatus.ucMultipleRecd = DCM_TRUE;
        /* Initialize the record number to 0xFE */
        LucTmpRecordNumber = DCM_START_MAX_RECORDS;
        /* Reset the record number to zero */
        LucRecordNumber = DCM_START_MAX_RECORDS;
        /* To indicate multiple record */
        Dcm_GblMultipleRecord = DCM_TRUE;
      }
      else
      {
        LucTmpRecordNumber = DCM_MAX_RECORDS;
        /* To indicate no multiple record */
        Dcm_GblMultipleRecord = DCM_FALSE;
      }
      /* Check whether pre compile option DCM_PAGEDBUFFER_ENABLED is enabled */
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      /* Check whether the paged transmission is in progress */
      if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
      {
        /*
                   * Set the global bit flag to indicated that page other than
                   * first page is in progress
                   */
        Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
      }
      #endif

      /* Disable data record update */
      LucReturnRes = Dem_DisableDTCRecordUpdate(
      Dcm_GunDTC.ulLongReg32, LddDTCOrigin);

      /* Check if the operation to disable data record update is successful */
      if(LucReturnRes != E_OK)
      {
        /** 
         * FIXME
         * DEM_DISABLE_DTCRECUP_OK                                   ((uint8)0x00)
         * DEM_DISABLE_DTCRECUP_WRONG_DTC                            ((uint8)0x01)
         * DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN                      ((uint8)0x02)
         * DEM_DISABLE_DTCRECUP_PENDING                              ((uint8)0x03)
         *
         * [SWS_Dcm_01212] If Dem_DcmDisableDTCRecordUpdate() returns 
         * DEM_DISABLE_DTCRECUP_WRONG_DTC, the Dcm shall send a NRC 0x31 
         * (Request out of Range). 
         * 
         * [SWS_Dcm_01213] If Dem_DcmDisableDTCRecordUpdate() returns 
         * DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN, the Dcm shall send a NRC 
         * 0x31 (Request out of Range).
        */
        
        LblRecNumNegResp = DCM_TRUE;
        Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      }
      /* Check if the operation to disable data record update is failed */
      else
      {
        /* Set bit flag indicating DTC record update is successfully disabled */
        Dcm_DspSerPgStatus.ucDemDisableInvoked = DCM_TRUE;
        /* For the First Data subtract the 1 byte for record number */
        LulRemBufSize = LulBufferSize - DCM_ONE;
        LblFirstRecordUpdate = DCM_TRUE;
      }
    } /* end of block comment 1 */


     while((LucTmpRecordNumber < DCM_MAX_EXTND_RECORDS) &&
      (LblRecNumNegResp == DCM_FALSE) && (LulRemBufSize > DCM_ZERO))
    {
      /* Update the record number to the response data buffer */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      Dcm_GpReqResData[DCM_ZERO] = LucRecordNumber;
      
      /*
       * Update the response buffer address so as to get back the original
       * response buffer address in case the record number turns out to be
       * an invalid, based on return value other than DEM_RECORD_OK of the
       * Dem API Dem_GetExtendedDataRecordByDTC
       */
      LpResData = Dcm_GpReqResData;

      Dcm_GpReqResData = &Dcm_GpReqResData[1u];
      /*
       * If the remaining buffer size is greater than the maximum extended
       * frame Data size for any record then update it with 256
       */
      if(LulRemBufSize > DCM_MAX_RECDDATA_SIZE)
      {
        LulRespBufferSize = DCM_MAX_RECDDATA_SIZE;
      }
      else
      {
        LulRespBufferSize = LulRemBufSize;
      }
      LusTemp = (uint16)LulRespBufferSize;
      /* Get the complete extended data record for the requested DTC */
      LucReturnRes =  Dem_GetExtendedDataRecordByDTC(
      Dcm_GunDTC.ulLongReg32,LddDTCOrigin, LucRecordNumber,
      Dcm_GpReqResData, &LusTemp);
      LulRespBufferSize = (uint32)LusTemp;
      /* Check whether extended data record is successfully returned */
      if(LucReturnRes == DEM_RECORD_OK)
      {
        if(LulRespBufferSize != DCM_ZERO)
        {

          /* For the First Data subtract the 1 byte for record number */
          if(LblFirstRecordUpdate == DCM_FALSE)
          {
            LulRemBufSize -= DCM_ONE;
          }
          else
          {
            LblFirstRecordUpdate = DCM_FALSE;
          }
          LulRemBufSize -= LulRespBufferSize;
          /* Increment the pointer by BufSize bytes */
          Dcm_GpReqResData = &Dcm_GpReqResData[LulRespBufferSize];
        }
        else if(Dcm_GblMultipleRecord == DCM_FALSE)
        {
          Dcm_GpReqResData--;
          pMsgContext->resDataLen = DCM_FIVE;

        }
        else
        {
          /* To avoid QAC */
        }
      }
      /* Check whether provided buffer is too small */
      else if(LucReturnRes == DEM_RECORD_WRONG_BUFFERSIZE)
      {
        /* Check whether pre compile option DCM_PAGEDBUFFER_ENABLED is enabled */
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        /* Provided buffer is small */
        if((LucTmpRecordNumber != Dcm_GucRecordNumber) &&
          (Dcm_DspSerPgStatus.ucFirstPage == DCM_TRUE))
        {
          /* Update the global variable for the record number */
          Dcm_GucRecordNumber = LucRecordNumber;
          Dcm_GpReqResData = LpResData;
          LblRecNumNegResp = DCM_TRUE;
        }
        else
        #endif
        {
          /* First page in the loop exceeds the available buffer size */
          Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
          LblRecNumNegResp = DCM_TRUE;
        }
      }
      /* Check whether record number is wrong */
      else if(LucReturnRes == DEM_RECORD_WRONG_NUMBER)
      {
        /* For single record, its an error */
        if(Dcm_DspSerPgStatus.ucMultipleRecd == DCM_FALSE)
        {
          /* Update the variable to exit from the function */
          LblRecNumNegResp = DCM_TRUE;
          /* Update Negative response code */
          Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
        }
        else
        {
          Dcm_GpReqResData = LpResData;
        }
      }
      else if((LucReturnRes == DEM_RECORD_WRONG_DTC) ||
              (LucReturnRes == DEM_RECORD_WRONG_DTCORIGIN))
      {
        /* Update the variable to exit from the function */
        LblRecNumNegResp = DCM_TRUE;
        Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      }
      else
      {
        /* Update Negative response code */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        /* Update the variable to exit from the function */
        LblRecNumNegResp = DCM_TRUE;
      }
      if(((LucReturnRes == DEM_RECORD_OK) && (LulRespBufferSize == DCM_ZERO)) ||
       (LucReturnRes != DEM_RECORD_OK))
      {
        Dcm_GpReqResData = LpResData;
        if((LulBufferSize - LulRemBufSize) == DCM_ONE)
        {
          LulRemBufSize = LulRemBufSize + DCM_ONE;
        }
      }
      /* Increment the temporary record number */
      LucTmpRecordNumber++;
      /* Increment the record number */
      LucRecordNumber++;
    }
    if((Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE) &&
      (Dcm_DspSerPgStatus.ucDemDisableInvoked == DCM_TRUE))
    {
     /*
      * Release the data contained in this record so has to access or
      * manipulate by the external application
      */
      (void)Dem_EnableDTCRecordUpdate();
      /* Clear the bit flag indicating DTC record update is enabled */
      Dcm_DspSerPgStatus.ucDemDisableInvoked = DCM_FALSE;
    }
  }
  
  /* Return the remaining size of the buffer */
  return(LulBufferSize - LulRemBufSize);
}
#endif /* (DCM_READDTC_SUPPORT == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DspUpdateBasicsOfEventData                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function to assemble the        **
**                        initial response message for sub functions 0x04,    **
**                        0x06 and 0x10                                       **
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
**                        Dcm_GpReqResData, Dcm_GddNegRespError, Dcm_GunDTC.  **
**                        Function(s) invoked : Dem_GetStatusOfDTC            **
**                                                                            **
*******************************************************************************/
#if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
      (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
/* polyspace<MISRA-C:8.10:Not a defect:Justify with annotations> Whether the Dcm api function is required internal or external linkage, depends on user configuration */
FUNC(void, DCM_CODE) Dcm_DspUpdateBasicsOfEventData(void)
{
  Dem_DTCOriginType LddDTCOrigin;
  uint8 LddDTCStatus = (uint8)0x00;
  uint8 LucReturnRes;
  /* Set the NRC value */
  Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;

  if (Dcm_GpReqResData == NULL_PTR)    
  {
    /* For Misra-C Check */   
    /* Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT; */
  }
  else
  {
    if((Dcm_GucSubFunction & DCM_DSP_ORG_MASK) == DCM_DSP_ORG_MASK)
    {
      /* Mirror memory */
      LddDTCOrigin = DEM_DTC_ORIGIN_MIRROR_MEMORY;
    }
    else
    {
      /* Primary memory */
      LddDTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    }
    /* Get the status of DTC */
    LucReturnRes = Dem_GetStatusOfDTC(Dcm_GunDTC.ulLongReg32,
      LddDTCOrigin, &LddDTCStatus);
    /* Check whether status of DTC was OK */
    if(LucReturnRes == DEM_STATUS_OK)
    {
      /*  Sub-function number */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
      /*  DTC High Byte */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      Dcm_GpReqResData[DCM_ONE] = Dcm_GunDTC.ddByte.ucMidHiByte;
      /*  DTC Middle Byte */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidLowByte;
      /*  DTC Low Byte */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      Dcm_GpReqResData[DCM_THREE] = Dcm_GunDTC.ddByte.ucLsByte;
      /*  DTC Status Mask */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      Dcm_GpReqResData[DCM_FOUR] = LddDTCStatus;

      /* Re Initialize the response buffer pointer */
      Dcm_GpReqResData = &Dcm_GpReqResData[DCM_FIVE];
      /* Update the global variable, indicating no NRC as occurred */
      Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
    }
    else if((LucReturnRes == DEM_STATUS_WRONG_DTC) ||
      (LucReturnRes == DEM_STATUS_WRONG_DTCORIGIN))
    {
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
}
#endif /* ((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) ||
      (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON)) */

/*******************************************************************************
** Function Name        : Dcm_DspRptDTCSnapshotRecIdentfn                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the function used for the service Read DTC  **
**                        information (service 0x19) to read all the SnapShot **
**                        record numbers and its associated DTCs.It will be   **
**                        invoked for sub-function value 0x03                 **
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
** Remarks              : Global Variable(s) : Dcm_GpReqResData,              **
**                        Dcm_GpMsgContext, Dcm_GucReadGlobal,                **
**                        Dcm_GddNegRespError,                                **
**                        Dcm_DspSerPgStatus.                                 **
**                        Function(s) invoked :Dem_SetFreezeFrameRecordFilter **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptDTCSnapshotRecIdentfn(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)pMsgContext)
{
  uint32 LulResleng;
  uint16 LusNumberOfFilteredRecords;
  uint8 LucReturnSetDTCFilter;

  Dcm_GucReadGlobal = DCM_TRUE;
  LusNumberOfFilteredRecords = DCM_ZERO;
  /* Invoke for set filter for record */

  if (
    (pMsgContext == NULL_PTR) || 
    (pMsgContext->resData == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR) ||
    (Dcm_GpReqResData == NULL_PTR)    
  )
  {
    /* For Misra-C Check. */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
     LucReturnSetDTCFilter = Dem_SetFreezeFrameRecordFilter
       (DEM_DTC_FORMAT_UDS, &LusNumberOfFilteredRecords);
    /* Validate return value */
    if((LucReturnSetDTCFilter == DEM_FILTER_ACCEPTED) &&
      (LusNumberOfFilteredRecords == DCM_ZERO))
    {
      /* Update the sub function in the response buffer */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;

      /* Update the response length */
      pMsgContext->resDataLen = DCM_ONE;
      /* Update the NRC value */
      Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
    }
    else
    {
      if(LucReturnSetDTCFilter == DEM_FILTER_ACCEPTED)
      {
        /* DTCHighByte + DTCMiddleByte  + DTCLowByte + RecNum = 4 for every
         DTC + 1subfunction */
        LulResleng = (uint32)(((uint32)LusNumberOfFilteredRecords << (uint32)0x02) + (uint32)0x01);
        /* Update the complete response length that is to be transmitted */
        Dcm_GstMsgContext.resDataLen = LulResleng;
        /*
             * Check if the response buffer is capable of accommodating the
             * complete response at once
             */
        if(LulResleng <= (Dcm_GstMsgContext.resMaxDataLen))
        {
          /* Update the sub function */
          /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
          /* Reset the pointer to the response data buffer */
          Dcm_GpReqResData = &Dcm_GpReqResData[DCM_ONE];
          /*
              * Pass the buffer size with one value less since sub function
              is already updated
                   */
          LulResleng = LulResleng - DCM_ONE;

          (void)Dcm_DspRepDTCSnapRecID(LulResleng);
        }
        else
        {
          #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
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
      /* [SWS_Dcm_01043]
       * If DEM_WRONG_FILTER value is returned from 
       * Dem_ReturnSetFilterType, the Dcm module shall send a negative response with 
       * NRC 0x31 (Request out of range). */        
      else if (DEM_WRONG_FILTER == LucReturnSetDTCFilter)
      {
        Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      }    
      else
      {
        /* For QAC Check */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
  }
  
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
  #endif
  {
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}
#endif /* (DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DspRepDTCSnapRecID                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function for sub-functions 0x03    **
**                        used to list the SnapShot Record Number and the     **
**                        associated DTCs                                     **
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
**                        Dcm_GunDTC, Dcm_GddCurrentLength, Dcm_GpMsgContext. **
**                        Function(s) invoked : Dem_GetNextFilteredDTC        **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON)
/* polyspace<MISRA-C:8.10:Not a defect:Justify with annotations> Whether the Dcm api function is required internal or external linkage, depends on user configuration */
FUNC(uint32, DCM_CODE) Dcm_DspRepDTCSnapRecID(uint32 LulBufferSize)
{
  uint32 LulRespBufferSize;
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint32 LulRemainingLength;
  uint8 LucCount;
  #endif
  uint8 LucReturnRes;
  uint8 LucSnapShotrecord = (uint8)0x00;

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

  while((LulRespBufferSize > DCM_THREE) &&
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    (((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) &&
    (LulRemainingLength >= DCM_FOUR)) ||
    ((Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE))) &&
    #endif
    (LucReturnRes != DEM_FILTERED_NO_MATCHING_DTC))
  {
    LucReturnRes = Dem_GetNextFilteredRecord
      (&Dcm_GunDTC.ulLongReg32, &LucSnapShotrecord);

    if(LucReturnRes == DEM_FILTERED_OK)
    {
      /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
      *Dcm_GpReqResData = Dcm_GunDTC.ddByte.ucMidHiByte;

      Dcm_GpReqResData = &Dcm_GpReqResData[1u];
	
      /* DTC Middle Byte */
      /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
      *Dcm_GpReqResData = Dcm_GunDTC.ddByte.ucMidLowByte;

      Dcm_GpReqResData = &Dcm_GpReqResData[1u];
	
      /* DTC Low Byte */
      /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
      *Dcm_GpReqResData = Dcm_GunDTC.ddByte.ucLsByte;

      Dcm_GpReqResData = &Dcm_GpReqResData[1u];
	
      /* DTC Status Mask */
      /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Not a defect" */
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
      *Dcm_GpReqResData = LucSnapShotrecord;

      Dcm_GpReqResData = &Dcm_GpReqResData[1u];
	
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
      /* To avoid QAC warning */
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

          Dcm_GpReqResData = &Dcm_GpReqResData[1u];
        }

        /* MISRA Rule       : 21.1
           Message          : Unsigned arithmetic apparently results in
                    wraparound past zero. .
           Reason           : An value is decremented from the unsigned
                    variable
           Verification     : However, part of the code
                    is verified manually and
                    it is not having any impact.
        */
        LulRespBufferSize = LulRespBufferSize - DCM_FOUR;
        LulRemainingLength  = LulRemainingLength - DCM_FOUR;
      }while((LulRespBufferSize > DCM_THREE) &&
      (LulRemainingLength != DCM_ZERO));
    }
    #endif
  }
  return(LulBufferSize - LulRespBufferSize);
}
#endif /* (DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON) */
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<RTE: NIP : Not a defect : No Action Planned > pointer is not null */
/* polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct */
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:17.8 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:14.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:USELESS_WRITE [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:USELESS_IF [Justified:Low] "Not a defect" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This code maybe can not reach because of user configuration. No impact" */
/* polyspace-end CERT-C:MSC12-C [Justified:Low] "This code maybe can not reach because of user configuration. No impact" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
