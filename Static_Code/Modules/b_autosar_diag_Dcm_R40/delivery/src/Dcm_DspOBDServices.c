/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DspOBDServices.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for OBD services           **
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
** Revision  Date          By               Description                       **
********************************************************************************
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.2     03-03-2016    Sungeol Baek     #3754, RTRT reflection            **
**                                                                            **
** 1.0.1     16-04-2015    Sungeol Baek     #2171                             **
**                                                                            **
** 1.0.0     09-01-2013    Autron           Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_PCTypes.h"  /* Dcm PCTypes header file */
#include "Dcm_DspServices.h"
#include "Rte_Dcm.h"
#include "Dem.h"
#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DspOBDInternals.h"
#include "Dcm_Version.h"
#include "Dcm_DspOBDServices.h"

/*******************************************************************************
** Function Name        : Dcm_DcmOBDReqCurrentPowerTrainDiagData              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function that provides OBD service **
**                        0x01                                                **
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
** Remarks              : Global Variable(s) : Dcm_GddNegRespError            **
**                        Function(s) invoked : Dcm_DspGetAvailibiltyIDStatus **
**                        Dcm_DspReadOBD_AvlInfo, Dcm_DspReadOBD_1_DemInfo    **
**                        Dcm_DspGetSizeOfIDS                                 **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqCurrentPowerTrainDiagData(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer;
  Std_ReturnType LddReturnValue;
  uint16 LusRespLength;
  uint16 LusRespLengthRcvd;
  uint16 LusPidLength;
  uint8 LucPIDCount;
  uint8 LddReturnStatusValue;
  uint8 LucMix_DemRPort;

  LusRespLength = DCM_ZERO;
  LusRespLengthRcvd = DCM_ZERO;
  LusPidLength = DCM_ZERO;
  /* Get the pointer to the request data buffer */
  LpReqResData = pMsgContext->reqData;
  /* Update return value E_OK */
  LddReturnValue = E_OK;
  /* Update PIDCount with zero */
  LucPIDCount = DCM_ZERO;
  Dcm_GblAvailabilityPIDFlag = DCM_TRUE;
  /* Check for the validity of length */
  if((pMsgContext->reqDataLen < DCM_ONE) || (pMsgContext->reqDataLen > DCM_SIX))
  {
    /* Report the Condition not correct NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  /* Validate PIDs range */
  if((pMsgContext->reqDataLen > DCM_ZERO) &&
    (pMsgContext->reqDataLen < DCM_SEVEN))
  {
    /* Update the PIDs are exist in the request buffer */
    LucPIDCount = (uint8)pMsgContext->reqDataLen;
  }
  /* Check PID count */
  if(LucPIDCount > DCM_ZERO)
  {
    LucMix_DemRPort = DCM_ONE;
    /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
    LddReturnStatusValue = Dcm_DspGetAvailibiltyIDStatus(DCM_GET_PID,
      LpReqResData, LucPIDCount, LucMix_DemRPort);

    /* Validate DCM_AVAIL_ID for response length */
    if(LddReturnStatusValue == DCM_AVAIL_ID)
    {
      /* Total response = Number of PIDs + (Number of PIDs) * four */
      LusRespLength = LucPIDCount + (LucPIDCount << DCM_TWO);
    }
    /* Validate DCM_DEM_PID for response length */
    else if((LddReturnStatusValue == DCM_DEM_PID) ||
      (LddReturnStatusValue == DCM_R_PORT_PID))
    {
      /* Get the response length of requested PIDs */
      LddReturnValue = Dcm_DspGetSizeOfIDS( DCM_GET_PID, LucPIDCount,
        &LusRespLength, LpReqResData, DCM_ONE);
    }
    else
    {
      /* To avoid QAC warning */
    }
    /* Validate ID */
    if((LddReturnStatusValue != DCM_NOT_CONFIG_ID)  && (LddReturnValue == E_OK))
    {
      /*
      Check if the response buffer is capable of accommodating the
      complete response at once
      */
      if(LusRespLength <= (pMsgContext->resMaxDataLen))
      {
        LddReturnValue = E_OK;
      }
      else
      {
      /*
        Update the NRC if the response length is greater than the response
        buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled
      */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
        LddReturnValue = E_NOT_OK;
      }
      /* For non paged response */
      if(LddReturnValue == E_OK)
      {
        LpTxBuffer = pMsgContext->resData;
        /* For DCM_AVAIL_ID */
        if(LddReturnStatusValue == DCM_AVAIL_ID)
        {
          LusRespLengthRcvd = (uint16)Dcm_DspReadOBD_AvlInfo
            (LpReqResData, LpTxBuffer, LusRespLength, LucPIDCount, DCM_GET_PID);
        }
        /* For DCM_R_PORT_PID and  DCM_DEM_PID */
        else if((LddReturnStatusValue == DCM_R_PORT_PID) ||
          (LddReturnStatusValue == DCM_DEM_PID))
        {
          LddReturnValue = (uint8)Dcm_DspReadOBD_1_DemInfo(LpReqResData,
            LpTxBuffer, &LusPidLength, LucPIDCount);
          LusRespLengthRcvd = LusRespLength;
        }
        else
        {
          /* To avoid QAC warning */
        }
        if(LddReturnValue  != E_NOT_OK)
        {
          /* To indicate No NRC */
          Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
          /* Update Response length */
          pMsgContext->resDataLen = LusRespLengthRcvd;
          if(Dcm_GblAvailabilityPIDFlag == DCM_FALSE)
          {
             Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
          }
        }
      } /* End of non paged response */
    }
  }

  /* TODO: return value shall be processed */
  return E_OK;  
} /* End of Dcm_DcmOBDReqCurrentPowerTrainDiagData */
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmOBDReqPowerTrainFreezeFrameData              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function that provides OBD service **
**                        0x02                                                **
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
** Remarks              : Global Variable(s) : Dcm_GunDTC,                    **
**                        Dcm_GddNegRespError, Dem_GetDTCOfOBDFreezeFrame,    **
**                        Dcm_GddNegRespError, Dem_GetDTCOfOBDFreezeFrame.    **
**                        Function(s) invoked : Dcm_DspGetAvailibiltyIDStatus **
**                        Dcm_DspGetSizeOfIDS, Dcm_GaaPIDConfig,              **
**                        Dcm_GetIDIndex,                                     **
**                        Dem_ReadDataOfOBDFreezeFrame,                       **
**                        Dem_GetDTCOfOBDFreezeFrame,                         **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if(DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqPowerTrainFreezeFrameData(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2CONST(Dcm_DspPidData, AUTOMATIC, DCM_APPL_CONST)
    LpDcmDspPidData;
  Std_ReturnType LddReturnValue;
  Std_ReturnType requestResult = E_OK;
  uint32 LulCount2;
  uint16 LusRespLength;
  uint8 LucPIDValue;
  uint8 LucPIDIndex;
  uint8 LucPIDIndex_1;
  uint8 LucPIDCount;
  uint8 LucFreezeFrameRecord;
  uint8 LucSID;
  uint8 LucMix_DemRPort;
  uint8 LucNumofData;
  uint8 LucBufferSize;
  uint8 LucCount;
  uint8 LucSizeOfPID;
  uint8 LucDataElementIndex;
  uint8 LucIDIndex;
  uint8 LddAvlValueID;
  uint8 LucDestBuffer[DCM_MAXVALUE];

  LusRespLength = DCM_ZERO;
  /* Initialize the global variable to indicate that no NRC as occurred */
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_GblAvailabilityPIDFlag = DCM_TRUE;

  /* Get the pointer to the request data buffer */
  LpReqResData = pMsgContext->reqData;
  /* Update return value E_OK */
  LddReturnValue = E_OK;

  /* Update PIDCount with zero */
  LucPIDCount = DCM_ZERO;

  /* Check for the validity of length */
  if(pMsgContext->reqDataLen < DCM_TWO)
  {
    /* Report the Condition not correct NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  /* Validate PIDs + Freeze Frame range */
  if((pMsgContext->reqDataLen > DCM_ZERO) &&
    (pMsgContext->reqDataLen < DCM_SEVEN))
  {
    /* Update the PIDs are exist in the request buffer */
    LucPIDCount = (uint8)pMsgContext->reqDataLen/DCM_TWO;
  }

  /* To validate Freeze Frame record number */
  for(LucPIDIndex = DCM_ONE; LucPIDIndex < pMsgContext->reqDataLen;
    LucPIDIndex += DCM_TWO)
  {
    /* Validate whether the FF zero */
    if(LpReqResData[LucPIDIndex] != DCM_ZERO )
    {
      LucPIDCount = DCM_ZERO;
	  break;
    }
  }

  /* Check PID count */
  if(LucPIDCount > DCM_ZERO)
  {
    LucMix_DemRPort = DCM_TWO;
    /* It scans for all PIDs */
    /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
    LddAvlValueID = Dcm_DspGetAvailibiltyIDStatus(
      DCM_GET_PID, LpReqResData, LucPIDCount, LucMix_DemRPort);

    /* Validate DCM_AVAIL_ID for response length */
    if(LddAvlValueID == DCM_AVAIL_ID)
    {
      /* Total response = Num of PIDs + Number of FF + (Number of PIDs) * 4 */
      LusRespLength = ((LucPIDCount << DCM_ONE) + (LucPIDCount << DCM_TWO));
      pMsgContext->resDataLen = LusRespLength;
      Dcm_GblAvailabilityPIDFlag = DCM_FALSE;
    }
    /* Validate DCM_DEM_PID for response length */
    else if((LddAvlValueID == DCM_OTHER_PID) ||
      (LddAvlValueID == DCM_TWO_PID))
    {
      LucSID = DCM_TWO;
      /* Get the response length of requested PIDs */
      LddReturnValue = Dcm_DspGetSizeOfIDS( DCM_GET_PID, LucPIDCount,
        &LusRespLength, LpReqResData, LucSID);
      /* Update Response length */
      pMsgContext->resDataLen = LusRespLength;
      /*
      * the way of accessing PID from the request buffer,
      * because req buff will be having Freeze frame also
      */
    }
    else
    {
      /* To avoid QAC warning */
    }
    /*
     Check if the response buffer is capable of accommodating the
     complete response at once
    */
    if((LddAvlValueID != DCM_NOT_CONFIG_ID) && (LddReturnValue == E_OK))
    {
      /* Check Response length */
      if(LusRespLength <= (pMsgContext->resMaxDataLen))
      {
        LddReturnValue = E_OK;
      }
      else
      {
        /*
          Update the NRC if the response length is greater than the response
          buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled
        */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
        /* Set flag to go to end */
        LddReturnValue = E_NOT_OK;
      }

      /* For non paged response */
      if(LddReturnValue == E_OK)
      {
        LpTxBuffer = pMsgContext->resData;
        /* Load with zero */
        LucPIDIndex_1 = DCM_ZERO;

        for(LucPIDIndex = DCM_ZERO;
          ((LucPIDIndex < LucPIDCount) && (LddReturnValue == E_OK));
          LucPIDIndex++)
        {
          /* Get the PID value from the request buffer */
          LucPIDValue = LpReqResData[LucPIDIndex_1];
          /* Get the IDIndex for the PID */
          (void) Dcm_GetIDIndex(DCM_GET_PID, LucPIDValue, &LucIDIndex);
          /* For DCM_AVAIL_ID */
          if(LddAvlValueID == DCM_AVAIL_ID)
          {
            /* Update PID value to TX buffer*/
            LpTxBuffer[DCM_ZERO] = LucPIDValue;
            /* update Freezeframe Record number */
            LpTxBuffer[DCM_ONE] = LpReqResData[LucPIDIndex_1 + DCM_ONE];
            /* Move pointer by 2 bytes */
            LpTxBuffer = &LpTxBuffer[DCM_TWO];
            /* Get All Availability list of 4 bytes */
            LddReturnValue = Dcm_DspGetConfigIDS(LucPIDValue, DCM_GET_PID,
              LpTxBuffer, &LucSizeOfPID);
            /* check return value */
            if(LddReturnValue == E_OK)
            {
              /* MISRA Rule       : 17.4
                 Message          : Performing pointer arithmetic
                 Reason           : Increment operator not used
                                    to achieve better throughput.
                 Verification     : However, part of the code
                                    is verified manually and
                                    it is not having any impact.
              */
              LpTxBuffer = LpTxBuffer + DCM_FOUR;
              /* update response length 6 = PID + FF + 4 Data */
              Dcm_GblAvailabilityPIDFlag = DCM_TRUE;
            }
            else
            {
              LpTxBuffer = LpTxBuffer - DCM_TWO;
              /* Update Response length */
              LusRespLength = LusRespLength - DCM_SIX;
              pMsgContext->resDataLen = LusRespLength;
            }
          }
          else if((LddAvlValueID == DCM_OTHER_PID) ||
            (LddAvlValueID == DCM_TWO_PID))
          {
            if((LucPIDValue == DCM_TWO) &&
            (Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_TWO))
            {
              /* Get Freezeframe Record number */
              LucFreezeFrameRecord = LpReqResData[LucPIDIndex_1 + DCM_ONE];

              LddReturnValue = Dem_GetDTCOfOBDFreezeFrame(LucFreezeFrameRecord,
              &Dcm_GunDTC.ulLongReg32);

              if(LddReturnValue == E_OK)
              {
                /* Update PID value to TX buffer*/
                *LpTxBuffer = LucPIDValue;
				
                LpTxBuffer = &LpTxBuffer[1u];
                /* update Freezeframe Record number */
                *LpTxBuffer = LucFreezeFrameRecord;

                /* Increment pointer */
                LpTxBuffer = &LpTxBuffer[1u];
                /* DTC High Byte */
                *LpTxBuffer = Dcm_GunDTC.ddByte.ucMidHiByte;

                /* Increment pointer */
                LpTxBuffer = &LpTxBuffer[1u];

				/* DTC Middle Byte */
                *LpTxBuffer = Dcm_GunDTC.ddByte.ucMidLowByte;
 
                /* Increment pointer */
                LpTxBuffer = &LpTxBuffer[1u];
              }
              else
              {
                /* Update PID value to TX buffer*/
                *LpTxBuffer = LucPIDValue;

                /* Increment pointer */
                LpTxBuffer = &LpTxBuffer[1u];

				/* update Freezeframe Record number */
                *LpTxBuffer = LucFreezeFrameRecord;

                /* Increment pointer */
                LpTxBuffer = &LpTxBuffer[1u];

				/* DTC High Byte */
                *LpTxBuffer = DCM_ZERO;

                /* Increment pointer */
                LpTxBuffer = &LpTxBuffer[1u];

				/* DTC Middle Byte */
                *LpTxBuffer = DCM_ZERO;

                /* Increment pointer */
                LpTxBuffer = &LpTxBuffer[1u];
              }
            }
            else /* OTHER PIDS */
            {
              if((Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_TWO) ||
                (Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_THREE))
              {
                /* Get the Number of PID Data Configured */
                LucNumofData = Dcm_GaaPIDConfig[LucIDIndex].ucNumofPIDData;
                /* Get the PID Buffer Size */
                LucBufferSize = Dcm_GaaPIDConfig[LucIDIndex].ucPidBufferSize;

                LpDcmDspPidData = Dcm_GaaPIDConfig[LucIDIndex].pDcmDspPidData;

                /* Update PID value to TX buffer*/
                *LpTxBuffer = LucPIDValue;

                /* Increment pointer */
                LpTxBuffer = &LpTxBuffer[1u];
				
                /* update Freezeframe Record number */
                *LpTxBuffer = LpReqResData[LucPIDIndex_1 + DCM_ONE];

                /* Increment pointer */
                LpTxBuffer = &LpTxBuffer[1u];
				
                for(LucCount = DCM_ZERO;LucCount < LucNumofData;LucCount++)
                {
                  LucDataElementIndex = LpDcmDspPidData->ucPIDDataElementIndex;
          
                  LddReturnValue = Dem_ReadDataOfOBDFreezeFrame(LucPIDValue,
                    LucDataElementIndex,
                    &LucDestBuffer[DCM_ZERO], &LucBufferSize);

				  /* Increment pointer */
                  LpDcmDspPidData = &LpDcmDspPidData[1u];
				  
                  if(LddReturnValue == E_OK)
                  {

                    for(LulCount2 = DCM_ZERO;LulCount2 < LucBufferSize;
                    LulCount2++)
                    {
                      *LpTxBuffer = LucDestBuffer[LulCount2];

                      /* Increment pointer */
                      LpTxBuffer = &LpTxBuffer[1u];
                    }
                  }
                  else
                  {
                    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
                  }
                }
              }
            }
          }
          else
          {
            /* To avoid QAC warning */
          }
          /* Increment by two */
          LucPIDIndex_1 += DCM_TWO;
        }
        if(Dcm_GblAvailabilityPIDFlag == DCM_FALSE)
        {
          Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
        }
      } /* End of non paged response */
    }
    else
    {
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  else
  {
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }

  /* Send response from main function */
  Dcm_GblSendResponse = DCM_TRUE;
  /* Always E_OK */
  return requestResult;
}
#endif /* (DCM_OBDREGPOWERTRAINFREEZEFRAMEDATA_SERVICE == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DcmOBDGetDTC                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function that provides OBD service **
**                        0x03, 0x07, 0x0A                                    **
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
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GddNegRespError, Dcm_GpMsgContext,              **
**                        Dcm_GpReqResData, Dcm_PrtclTxBufStatus.             **
**                        Function(s) invoked :                               **
**                        Dem_SetDTCFilter,Dcm_DemGetNumberOfOBDDTC,          **
**                        Dcm_ExternalProcessingDone,                         **
**                        Dcm_ExternalSetNegResponse                          **
**                                                                            **
*******************************************************************************/
#if((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
 (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDGetDTC(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dem_DTCOriginType LddDTCOrigin;
  Dem_ReturnSetFilterType LddRetrunSetFilter;
  uint8 LucSID;
  uint8 LucStatusMask;

  /* Initialize variable with DCM_ZERO*/
  LucStatusMask = DCM_ZERO;
  /* MISRA Rule         : 12.7
     Message            : Bitwise operators shall not be applied to operands
                          whose underlying type is signed.
     Reason             : Bitwise operators used to achieve better
                          throughput.
     Verification       : However, part of the code is verified
                          manually and it is not having any impact.
  */
  /* Get SID */
  LucSID = ((Dcm_GstMsgContext.idContext) & ~(DCM_RESPONSE_ID));

  /* Check for the validity of length */
  if(pMsgContext->reqDataLen > DCM_ZERO)
  {
    /* Report the Condition not correct NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  if(Dcm_GddNegRespError != DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT)
  {
    /* Update DTC origin for 03 and 07 */
    LddDTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;

    switch(LucSID)
    {
      /* Check if the sub function requested is 0x08 */
      case DCM_OBD_GETDTC_03:
          /* Status Mask update as eight for OBD service 01 */
          LucStatusMask = DCM_EIGHT;
          break;
      case DCM_OBD_GETDTC_07:
          /* Status Mask update as eight for OBD service 07 */
          LucStatusMask = DCM_FOUR;
          break;
      case  DCM_OBD_GETDTC_0A:
          /* Status Mask update as eight for OBD service 0A */
          LucStatusMask = DCM_ZERO;
          /* Update DTC origin for  0A */
          LddDTCOrigin = DEM_DTC_ORIGIN_PERMANENT_MEMORY;
          break;
      default:
      break;
    }
    /* Invoke Dem API to set DTC filter */
    LddRetrunSetFilter = Dem_SetDTCFilter(LucStatusMask,
      DEM_DTC_KIND_EMISSION_REL_DTCS, DEM_DTC_FORMAT_OBD, LddDTCOrigin,
      DEM_FILTER_WITH_SEVERITY_NO, DCM_ZERO, (uint8)DEM_FILTER_FOR_FDC_NO);
    /* Check return value */
    if(LddRetrunSetFilter == DEM_FILTER_ACCEPTED)
    {
      Dcm_GpReqResData = pMsgContext->resData;
      Dcm_DemGetNumberOfOBDDTC();
    }
    /* [SWS_Dcm_01043]
     * If DEM_WRONG_FILTER value is returned from 
     * Dem_ReturnSetFilterType, the Dcm module shall send a negative response with 
     * NRC 0x31 (Request out of range). */    
    else if (DEM_WRONG_FILTER == LddRetrunSetFilter)
    {
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
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
    if(Dcm_PrtclTxBufStatus.ucReportOBDDtc == DCM_FALSE)
    {
      /* Send response from main function */
      Dcm_GblSendResponse = DCM_TRUE;
    }
  }

  /* TODO: return value shall be processed */
  return E_OK;  
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmOBDClrResetEmissionDiagInfo                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function that provides OBD service **
**                        0x04                                                **
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
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_PrtclTxBufStatus                                **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse,   **
**                        Dem_ClearDTC, Dcm_ExternalProcessingDone            **
**                                                                            **
*******************************************************************************/
#if(DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDClrResetEmissionDiagInfo(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dem_ReturnClearDTCType LddReturnValue;

  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_FALSE;

  /* Check for the validity of length */
  if(pMsgContext->reqDataLen != DCM_ZERO)
  {
    /* Report the Condition not correct NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  
  if(Dcm_GddNegRespError != DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT)
  {
    /* Invoke to clear DTC */
    LddReturnValue = Dem_ClearDTC(DEM_DTC_GROUP_ALL_DTCS,
      DEM_DTC_FORMAT_OBD, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
    /* Validate Return value */
    if(LddReturnValue == DEM_CLEAR_PENDING)
    {
      /* Set the Flag for returning of DCM_E_PENDING */
      Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_TRUE;
    }
    else if(LddReturnValue == DEM_CLEAR_OK)
    {
      Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
      /* Update total response length */
      pMsgContext->resDataLen = DCM_ZERO;
    }
    else if(LddReturnValue == DEM_CLEAR_FAILED)
    {
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
    else if((LddReturnValue == DEM_CLEAR_WRONG_DTC) ||
      (LddReturnValue == DEM_CLEAR_WRONG_DTCORIGIN))
    {
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      /* To avoid QAC warnings */
    }
  }
  
  if(Dcm_PrtclTxBufStatus.ucClearDTCStatus == DCM_FALSE)
  {
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  /* TODO: return value shall be processed */
  return E_OK;  
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmOBDReqOnboadMonitorResult                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to provide Request On-Board   **
**                        Monitoring Test-results for Specific Monitored      **
**                        Systems i.e. OBD service 0x06                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError            **
**                        Functions Invoked : None                            **
**                                                                            **
*******************************************************************************/
#if(DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqOnboadMonitorResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{

  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer;
  uint16 LusRespLength;
  uint8 LucOBDMIDCount;

  /* Get the pointer to the request data buffer */
  LpReqResData = pMsgContext->reqData;
  LpTxBuffer = pMsgContext->resData;
  LusRespLength = DCM_ZERO;

  /* Update PIDCount with zero */
  LucOBDMIDCount = DCM_ZERO;

  /* Check for the validity of length */
  if(pMsgContext->reqDataLen < DCM_ONE)
  {
    /* Report the Condition not correct NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  /* Validate PIDs range */
  if((pMsgContext->reqDataLen > DCM_ZERO) &&
    (pMsgContext->reqDataLen < DCM_SIX))
  {
    /* Update the PIDs are exist in the request buffer */
    LucOBDMIDCount = (uint8)pMsgContext->reqDataLen;
  }

  if(LucOBDMIDCount > DCM_ZERO)
  {
    Dcm_DcmOBDReqOnboadMonitorResultCall(LpReqResData, LpTxBuffer,
      LucOBDMIDCount, &LusRespLength);

    /* Update Response length */
    pMsgContext->resDataLen = LusRespLength;
  }
  else
  {
    /* Update NRC */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }

  /* TODO: return value shall be processed */
  return E_OK;  
}

/*******************************************************************************
** Function Name        : Dcm_DcmOBDReqOnboadMonitorResultCall                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to provide Request On-Board   **
**                        Monitoring Test-results for Specific Monitored      **
**                        Systems i.e. OBD service 0x06. This function is     **
**                        accessed from OBD and ReaddatabyID service          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpMsgContext,              **
**                        Dcm_GddNegRespError, Dcm_DspSerPgStatus,            **
**                        Dcm_GucPIDCount, Dcm_GaaTidUaSid.                   **
**                        Function(s) invoked : Dcm_DspGetAvailibiltyIDStatus,**
**                        Dcm_DspGetSizeOfIDS, Dcm_DsdStartPagedProcessing,   **
**                        Dcm_DspReadOBD_AvlInfo, Dcm_GetIDIndex,             **
**                        Dcm_GaaTidUaSid                                     **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE)Dcm_DcmOBDReqOnboadMonitorResultCall(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer, uint8 LucOBDMIDCount,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpResLength)
{
  /* MISRA Rule         : 18.4
     Message            : Unions shall not be used.
     Reason             : For optimization.
     Verification       : However, part of the code is verified
                          manually and it is not having any impact.
  */
  Tun_DcmWord16 LunDcmWord16;
  P2CONST(Dcm_OBDMidConfigType, AUTOMATIC, DCM_APPL_CONST) LpObdMidConfig;
  P2CONST(Dcm_OBDMidTids, AUTOMATIC, DCM_APPL_CONST) LpObdMidTids;
  Std_ReturnType LddReturnValue;
  uint16 LusTestval;
  uint16 LusMinlimit;
  uint16 LusMaxlimit;
  uint16 LusRespLength;
  uint16 LusRespLengthRcvd;
  uint8 LucOBDMIDValue;
  uint8 LucOBDMIDIndex;
  uint8 LucTID;
  uint8 LucUaSid;
  uint8 LucMix_DemRPort;
  uint8 LucStatus;
  uint8 LucIndex;
  uint8 LddReturnStatusValue;
  LusRespLength = DCM_ZERO;

  /* Update return value E_OK */
  LddReturnValue = E_OK;
  LucMix_DemRPort = DCM_SIX;
  Dcm_GblAvailabilityPIDFlag = DCM_TRUE;

  /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
  LddReturnStatusValue = Dcm_DspGetAvailibiltyIDStatus(DCM_GET_OBDMID,
    LpReqResData, LucOBDMIDCount, LucMix_DemRPort);

  /* Validate DCM_AVAIL_ID for response length */
  if(LddReturnStatusValue == DCM_AVAIL_ID)
  {
    /* Total response = Number of PIDs(subfunction) + (Number of PIDs) * four */
    LusRespLength = (LucOBDMIDCount + (LucOBDMIDCount << DCM_TWO));
  }
  /* Validate DCM_DEM_PID for response length */
  else if(LddReturnStatusValue == DCM_OTHER_PID)
  {
    /* Get the response length of requested PIDs */
    LddReturnValue = Dcm_DspGetSizeOfIDS( DCM_GET_OBDMID, LucOBDMIDCount,
      &LusRespLength, LpReqResData, DCM_SIX);
  }
  else
  {
    /* To avoid QAC warning */
  }

  if((LddReturnStatusValue != DCM_NOT_CONFIG_ID) && (LddReturnValue == E_OK))
  {
    /* Check if the response buffer is capable of accommodating the complete
    response at once */
    if(LusRespLength <= (Dcm_GstMsgContext.resMaxDataLen))
    {
      LddReturnValue = E_OK;
    }
    else
    {
      /* Update Response length */
      *LpResLength = LusRespLength;
      /* Check Page buffer enabled */
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      /* Application not supported Paging */
      if(LddReturnStatusValue == DCM_AVAIL_ID)
      {
        /* Set the global bit flag for paging started to TRUE */
        Dcm_DspSerPgStatus.ucPagingStarted = DCM_TRUE;
        /* Start the paged processing */
        Dcm_DsdStartPagedProcessing(&Dcm_GstMsgContext);
        /* Update PID count */
        Dcm_GucPIDCount = LucOBDMIDCount;
      }
      else
      {
        /* Update the NRC if the response length is greater than the
          response buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
      }
      #else
      {
        /* Update the NRC if the response length is greater than the
        response buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
      }
      #endif /* #if(DCM_PAGEDBUFFER_ENABLED == STD_ON) */

      /* Set flag to go to end */
      LddReturnValue = E_NOT_OK;
    }
    /* For non paged response */
    if(LddReturnValue == E_OK)
    {
      /* For DCM_AVAIL_ID */
      if(LddReturnStatusValue == DCM_AVAIL_ID)
      {

        LusRespLengthRcvd = (uint16)Dcm_DspReadOBD_AvlInfo(LpReqResData,
          LpTxBuffer, LusRespLength, LucOBDMIDCount, DCM_GET_OBDMID);
      }
      /* For DCM_R_PORT_PID and  DCM_DEM_PID */
      else
      {
        for(LucOBDMIDIndex = DCM_ZERO; ((LucOBDMIDIndex < LucOBDMIDCount) &&
          (LddReturnValue == E_OK)); LucOBDMIDIndex++)
        {
          /* Get the PID value from the request buffer */
          LucOBDMIDValue = LpReqResData[LucOBDMIDIndex];

          /* Update PID value to TX buffer*/
          LpTxBuffer[DCM_ZERO] = LucOBDMIDValue;
          LpTxBuffer = &LpTxBuffer[DCM_ONE];

          /* MISRA Rule        : 13.6
            Message            : Control variable modified in body of loop
            Reason             : Once the search element found, control
                                 exiting from the for loop to terminate
                                 next iteration.
            Verification       : However, part of the code
                                 is verified manually and
                                 it is not having any impact.
          */
          LddReturnValue = Dcm_GetIDIndex(DCM_GET_OBDMID, LucOBDMIDValue,
            &LucOBDMIDIndex);
          if(LddReturnValue == E_OK)
          {
            LpObdMidConfig = &Dcm_GaaOBDMidConfig[LucOBDMIDIndex];
            LpObdMidTids = LpObdMidConfig->pDcmObdMidTids;

            for(LucIndex = DCM_ZERO; LucIndex < LpObdMidConfig->ucNoOfTids;
                LucIndex++)
            {
              LddReturnValue = LpObdMidTids->pGetDTRValueFnc
             (DCM_INITIAL, &LusTestval, &LusMinlimit, &LusMaxlimit, &LucStatus);

              if(LddReturnValue == E_OK)
              {
                if(LucStatus == DCM_DTRSTATUS_VISIBLE)
                {
                  /* Get TID */
                  LucTID = LpObdMidTids->ucTestResultTestId;
                  /* Get UaSid */
                  LucUaSid = LpObdMidTids->ucTestResultUaSid;
                  /* update TID */
                  LpTxBuffer[DCM_ZERO] = LucTID;
                  /* update UaSid */
                  LpTxBuffer[DCM_ONE] = LucUaSid;
    
                  /* Update Test value */
                  LunDcmWord16.usWordReg16 = LusTestval;
                  /* update Test Value Hi byte */
                  LpTxBuffer[DCM_TWO] = LunDcmWord16.ddByte.ucMsByte;
                  /* update Test Value Lo byte */
                  LpTxBuffer[DCM_THREE] = LunDcmWord16.ddByte.ucLsByte;
    
                  /* Update Min Limit */
                  LunDcmWord16.usWordReg16 = LusMinlimit;
                  /* update Test Value Hi byte */
                  LpTxBuffer[DCM_FOUR] = LunDcmWord16.ddByte.ucMsByte;
                  /* update Test Value Lo byte */
                  LpTxBuffer[DCM_FIVE] = LunDcmWord16.ddByte.ucLsByte;
    
                  /* Update Max Limit */
                  LunDcmWord16.usWordReg16 = LusMaxlimit;
                  /* update Test Value Hi byte */
                  LpTxBuffer[DCM_SIX] = LunDcmWord16.ddByte.ucMsByte;
                  /* update Test Value Lo byte */
                  LpTxBuffer[DCM_SEVEN] = LunDcmWord16.ddByte.ucLsByte;
    
                  LpTxBuffer = &LpTxBuffer[DCM_EIGHT];
                  LpObdMidTids++;

                  /* To indicate No NRC */
                  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
                }
                else
                {
                  Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
                }
              }
              else if(LddReturnValue == DCM_E_PENDING)
              {
                Dcm_GddNegRespError = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
                LucIndex = LpObdMidConfig->ucNoOfTids;
              }
              else
              {
                /* To avoid QAC warning */
              }
            }
          }
        }
        LusRespLengthRcvd = LusRespLength;
      }

      if((LddReturnValue  != E_NOT_OK) && (LddReturnValue  != DCM_E_PENDING))
      {
        /* To indicate No NRC */
        Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
        /* Update Response length */
        *LpResLength = LusRespLengthRcvd;
        if(Dcm_GblAvailabilityPIDFlag == DCM_FALSE)
        {
           Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
        }
      }
	  
      if (LddReturnValue  == E_NOT_OK)
      {
        /* Update NRC */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
    } /* End of non paged response */
  }
  else
  {
    /* Update NRC */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmOBDReqCtlrOnboadSystem                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function used to Request Control of On-Board   **
**                        System, Test or Component i.e. provide OBD service  **
**                        0x08                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GddNegRespError, Dcm_GucPIDCount,               **
**                        Dcm_GaaRequestControlConfig.                        **
**                        Function(s) invoked : Dcm_DspGetAvailibiltyIDStatus,**
**                        Dcm_DsdStartPagedProcessing,                        **
**                        Dcm_DspReadOBD_AvlInfo, Dcm_GetIDIndex,             **
**                                                                            **
*******************************************************************************/
#if(DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqCtlrOnboadSystem(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpOutBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpInBuffer;
  Std_ReturnType LddReturnValue;
  uint16 LusRespLength;
  uint16 LusRespLengthRcvd;
  uint8 LucTIDValue;
  uint8 LucTIDCount;
  uint8 LucMix_DemRPort;
  uint8 LddReturnStatusValue;
  uint8 LucTIDIndex1 = DCM_ZERO;
  LusRespLength = DCM_ZERO;
  LusRespLengthRcvd = DCM_ZERO;

  /* Get the pointer to the request data buffer */
  LpReqResData = pMsgContext->reqData;

  /* Update PIDCount with zero */
  LucTIDCount = DCM_ZERO;
  Dcm_GblAvailabilityPIDFlag = DCM_TRUE;
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
  /* Check for the validity of length */
  if(pMsgContext->reqDataLen < DCM_ONE)
  {
    /* Report the Condition not correct NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    LucTIDCount = DCM_ONE;
    LucMix_DemRPort = DCM_EIGHT;
    /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
    LddReturnStatusValue = Dcm_DspGetAvailibiltyIDStatus(DCM_GET_TID,
      LpReqResData, LucTIDCount, LucMix_DemRPort);

    if(LddReturnStatusValue == DCM_OTHER_PID)
    {
      LucTIDValue = LpReqResData[DCM_ZERO];
      LddReturnValue = Dcm_GetIDIndex(DCM_GET_TID, LucTIDValue, &LucTIDIndex1);

      if(LddReturnValue == E_OK)
      {
        if(pMsgContext->reqDataLen != (uint32)(DCM_ONE + \
          Dcm_GaaRequestControlConfig[LucTIDIndex1].ucRequestControlInBufferSize))
        {
          /* Report the invalid length NRC */
          Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else
        {
          LucTIDCount = DCM_ONE;
        }
      }
    }
    else
    {
      if(pMsgContext->reqDataLen > DCM_SIX)
      {
        /* Report the invalid length NRC */
        Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }
      else
      {
        LucTIDCount = (uint8)pMsgContext->reqDataLen;
      }
    }
  }


  /* Validate PIDs range */
  if(Dcm_GddNegRespError == DCM_E_POSITIVERESPONSE)
  {
    LucMix_DemRPort = DCM_EIGHT;
    /* It scans for all PIDs */
    /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
    LddReturnStatusValue = Dcm_DspGetAvailibiltyIDStatus(DCM_GET_TID,
      LpReqResData, LucTIDCount, LucMix_DemRPort);

    /* Validate DCM_AVAIL_ID for response length */
    if(LddReturnStatusValue == DCM_AVAIL_ID)
    {
      /* Total response = Number of PIDs + (Number of PIDs) * four */
      LusRespLength = (uint16)(LucTIDCount + (LucTIDCount << DCM_TWO));
    }
    /* Validate DCM_DEM_PID for response length */
    else if(LddReturnStatusValue == DCM_OTHER_PID)
    {
      /* Total response = NPID */
      LusRespLength = (uint16)(LucTIDCount + \
        Dcm_GaaRequestControlConfig[LucTIDIndex1].ucRequestControlOutBufferSize);

    }
    else
    {
      /* To avoid QAC warning */
    }

    if((LddReturnStatusValue != DCM_NOT_CONFIG_ID))
    {
      /*
      Check if the response buffer is capable of accommodating the
      complete response at once
      */
      if(LusRespLength <= (pMsgContext->resMaxDataLen))
      {
        LddReturnValue = E_OK;
      }
      else
      {
        /* Update Response length */
        pMsgContext->resDataLen = LusRespLength;
        /* Check Page buffer enabled */
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        /* Application not supported Paging */
        if(LddReturnStatusValue == DCM_AVAIL_ID)
        {
          /* Set the global bit flag for paging started to TRUE */
          Dcm_DspSerPgStatus.ucPagingStarted = DCM_TRUE;
          /* Start the paged processing */
          Dcm_DsdStartPagedProcessing(pMsgContext);
          /* Update PID count */
          Dcm_GucPIDCount = LucTIDCount;
        }
        else
        {
          /*
            Update the NRC if the response length is greater than the response
            buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled
          */
          Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
        }
        #else
        {
          /*
            Update the NRC if the response length is greater than the response
            buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled
          */
          Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
        }
        #endif /* #if(DCM_PAGEDBUFFER_ENABLED == STD_ON) */

        /* Set flag to go to end */
        LddReturnValue = E_NOT_OK;
      }

      /* For non paged response */
      if(LddReturnValue == E_OK)
      {

        LpTxBuffer = pMsgContext->resData;
        /* For DCM_AVAIL_ID */
        if(LddReturnStatusValue == DCM_AVAIL_ID)
        {
          LusRespLengthRcvd = (uint16)Dcm_DspReadOBD_AvlInfo(LpReqResData,
            LpTxBuffer, LusRespLength, LucTIDCount, DCM_GET_TID);
        }
        /* For other than DCM_AVAIL_ID */
        else if(LddReturnStatusValue == DCM_OTHER_PID)
        {
          if(LucTIDCount == DCM_ONE)
          {
            /* Get the PID value from the request buffer */
            LucTIDValue = LpReqResData[DCM_ZERO];

            /* Update PID value to TX buffer*/
            LpTxBuffer[DCM_ZERO] = LucTIDValue;

            LddReturnValue = Dcm_GetIDIndex(DCM_GET_TID, LucTIDValue,
              &LucTIDIndex1);
            if(LddReturnValue == E_OK)
            {
              /* Initialize buffer */
              LpOutBuffer = &LpTxBuffer[DCM_ONE];
              LpInBuffer = pMsgContext->reqData;
              LddReturnValue = Dcm_GaaRequestControlConfig[LucTIDIndex1].
                          pReqControlFnc(LpOutBuffer, LpInBuffer);
              /* Validate return value */
              if(LddReturnValue == E_OK)
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
              }
              else if(LddReturnValue == DCM_E_PENDING)
              {
                /* Update NRC */
                Dcm_GddNegRespError = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
              }
              else
              {
                /* Update NRC */
                Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
              }
            }
          }
          else
          {
            /* For Condition not correct */
            LddReturnValue  = E_NOT_OK;
          }
          LusRespLengthRcvd = LusRespLength;
        }
        else
        {
          /* To avoid QAC warning */
        }

        if((LddReturnValue != E_NOT_OK) && (LddReturnValue != DCM_E_PENDING))
        {
          /* To indicate No NRC */
          Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
          if(Dcm_GblAvailabilityPIDFlag == DCM_FALSE)
          {
             Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
          }
        }
        if(LddReturnValue == E_NOT_OK)
        {
          /* Update NRC */
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        }
        /* Update Response length */
        pMsgContext->resDataLen = LusRespLengthRcvd;
      } /* End of non paged response */
    }
    else
    {
      /* Update NRC */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  else
  {
    /* Update NRC */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }

  /* TODO: return value shall be processed */
  return E_OK;  
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmOBDRegVehicleInfo                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to get Vehicle information    **
**                          i.e. provides OBD service 0x09                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GddNegRespError           **
**                        Function(s) invoked :                               **
**                        Dcm_DcmOBDRegVehicleInfoCall                        **
**                                                                            **
*******************************************************************************/
#if(DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDRegVehicleInfo(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  uint16 LusRespLength;
  uint8 LucVIDCount;

  LusRespLength = DCM_ZERO;

  /* Get the pointer to the request data buffer */
  LpReqResData = pMsgContext->reqData;
  /* Assign Response buffer to local buffer */
  LpTxBuffer = pMsgContext->resData;

  /* VID count as zero */
  LucVIDCount = DCM_ZERO;
  /* Check for the validity of length */
  if(pMsgContext->reqDataLen < DCM_ONE)
  {
    /* Report the Condition not correct NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  /* Validate PIDs range */
  if((pMsgContext->reqDataLen > DCM_ZERO) &&
    (pMsgContext->reqDataLen < DCM_SEVEN))
  {
    /* Update the PIDs are exist in the request buffer */
    LucVIDCount = (uint8)pMsgContext->reqDataLen;
  }
  /* Check VID count */
  if(LucVIDCount > DCM_ZERO)
  {

    Dcm_DcmOBDRegVehicleInfoCall(LpReqResData, LpTxBuffer, LucVIDCount,
      &LusRespLength);

    /* Update Response length */
    pMsgContext->resDataLen = LusRespLength;

  }
  else
  {
    /* Update NRC */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }

  /* TODO: return value shall be processed */
  return E_OK;  
}

/*******************************************************************************
** Function Name        : Dcm_DcmOBDRegVehicleInfoCall                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to get Vehicle information    **
**                        i.e. provides OBD service 0x09. This function is    **
**                        accessed from OBD service and ReaddatabyID service  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpMsgContext               **
**                        Dcm_GddNegRespError, Dcm_DspSerPgStatus,            **
**                        Dcm_GucPIDCount, Dcm_GaaVehInfoConfig               **
**                        Function(s) invoked : Dcm_DspGetAvailibiltyIDStatus,**
**                        Dcm_DspGetSizeOfIDS, Dcm_DsdStartPagedProcessing,   **
**                        Dcm_DspReadOBD_AvlInfo, Dcm_GetIDIndex.             **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DcmOBDRegVehicleInfoCall(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer, uint8 LucVIDCount,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpRespLength
  )
{

  P2CONST(Dcm_VehInfoData, AUTOMATIC, DCM_APPL_CONST) LpVehInfoData;
  P2CONST(Dcm_VehInfoConfigType, AUTOMATIC, DCM_APPL_CONST) LpVehInfoConfigData;
  Std_ReturnType LddReturnValue;
  uint16 LusRespLength;
  uint16 LusRespLengthRcvd;
  uint8 LucVIDValue;
  uint8 LucVIDIndex1;
  uint8 LucSID;
  uint8 LucMix_DemRPort;
  uint8 LddReturnStatusValue;
  uint8 LucIndex;

  /* Update return value E_OK */
  LddReturnValue = E_OK;
  LusRespLength = DCM_ZERO;
  LusRespLengthRcvd = DCM_ZERO;

  LucMix_DemRPort = DCM_NINE;
  Dcm_GblAvailabilityPIDFlag = DCM_TRUE;
  /* It scans for all PIDs */
  /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
  LddReturnStatusValue = Dcm_DspGetAvailibiltyIDStatus(DCM_GET_VID,
    LpReqResData, LucVIDCount, LucMix_DemRPort);

  /* Validate DCM_AVAIL_ID for response length */
  if(LddReturnStatusValue == DCM_AVAIL_ID)
  {
    /* Total response = Number of PIDs + (Number of PIDs) * four */
    LusRespLength = LucVIDCount + (LucVIDCount << DCM_TWO);
  }
  /* Validate DCM_DEM_PID for response length */
  else if(LddReturnStatusValue == DCM_OTHER_PID)
  {
    LucSID = DCM_NINE;
    /* Get the response length of requested PIDs */
    LddReturnValue = Dcm_DspGetSizeOfIDS( DCM_GET_VID, LucVIDCount,
      &LusRespLength, LpReqResData, LucSID);
  }
  else
  {
    /* To avoid QAC warning */
  }

  if((LddReturnStatusValue != DCM_NOT_CONFIG_ID) && (LddReturnValue == E_OK))
  {
    /* Check if the response buffer is capable of accommodating the
    complete response at once */
    if(LusRespLength <= (Dcm_GstMsgContext.resMaxDataLen))
    {
      LddReturnValue = E_OK;
    }
    else
    {
       /* Update Response length */
      *LpRespLength = LusRespLength;
      /* Check Page buffer enabled */
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      /* Application not supported Paging */
      if(LddReturnStatusValue == DCM_AVAIL_ID)
      {
        /* Set the global bit flag for paging started to TRUE */
        Dcm_DspSerPgStatus.ucPagingStarted = DCM_TRUE;
        /* Start the paged processing */
        Dcm_DsdStartPagedProcessing(&Dcm_GstMsgContext);
        /* Update PID count */
        Dcm_GucPIDCount = LucVIDCount;
      }
      else
      {
        /* Update the NRC if the response length is greater than
           the response buffer size and DCM_PAGEDBUFFER_ENABLED is
           not enabled
        */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
      }
      #else
      {
        /* Update the NRC if the response length is greater than the response
           buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
      }
      #endif /* #if(DCM_PAGEDBUFFER_ENABLED == STD_ON) */

      /* Set flag to go to end */
      LddReturnValue = E_NOT_OK;
    }

    /* For non paged response */
    if(LddReturnValue == E_OK)
    {

      /* For DCM_AVAIL_ID */
      if(LddReturnStatusValue == DCM_AVAIL_ID)
      {
        LusRespLengthRcvd = (uint16)Dcm_DspReadOBD_AvlInfo(LpReqResData,
            LpTxBuffer, LusRespLength, LucVIDCount, DCM_GET_VID);
      }
      /* For other than DCM_AVAIL_ID */
      else if(LddReturnStatusValue == DCM_OTHER_PID)
      {
        if(LucVIDCount == DCM_ONE)
        {
          /* Get the PID value from the request buffer */
          LucVIDValue = LpReqResData[DCM_ZERO];

          LddReturnValue = Dcm_GetIDIndex(DCM_GET_VID, LucVIDValue,
            &LucVIDIndex1);

          if(LddReturnValue == E_OK)
          {
            LpVehInfoConfigData = &Dcm_GaaVehInfoConfig[LucVIDIndex1];
            LpVehInfoData = LpVehInfoConfigData->pDcmVehInfoData;
            /* Update PID value to TX buffer*/
            LpTxBuffer[DCM_ZERO] = LucVIDValue;
            /* Update vehinfo data count to TX buffer*/
            LpTxBuffer[DCM_ONE] = LpVehInfoConfigData->ucNoOfVehInfoData;
            /* Move pointer by 2 bytes */
            LpTxBuffer = &LpTxBuffer[DCM_TWO];

            for(LucIndex=DCM_ZERO; (LucIndex <
              LpVehInfoConfigData->ucNoOfVehInfoData); LucIndex++)
            {
              LddReturnValue = LpVehInfoData->pGetVehInfoTypeFnc
                  (DCM_INITIAL, LpTxBuffer);
              /* Validate return value */
              if(LddReturnValue == E_OK)
              {
                /* Move pointer by ucVehInfoBufSize */
                LpTxBuffer = &LpTxBuffer[LpVehInfoData->ucVehInfoBufSize];
                /* To indicate No NRC */
                Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
              }
              else if(LddReturnValue == DCM_E_PENDING)
              {
                /* Update NRC */
                Dcm_GddNegRespError = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;

                /* break loop */
                break;
              }
              else
              {
                /* Avoid QAC warning */
              }

              LpVehInfoData = &LpVehInfoData[1u];
            }
          }
        }
        else
        {
          /* Update as E_NOT_OK */
          LddReturnValue = E_NOT_OK;
        }
        LusRespLengthRcvd = LusRespLength;
      }
      else
      {
        /* To avoid QAC warning */
      }

      if((LddReturnValue != E_NOT_OK) && (LddReturnValue != DCM_E_PENDING))
      {
        /* To indicate No NRC */
        Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;
        /* Update Response length */
        *LpRespLength = LusRespLengthRcvd;
        if(Dcm_GblAvailabilityPIDFlag == DCM_FALSE)
        {
           Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
        }
      }
	  
      if(LddReturnValue == E_NOT_OK)
      {
        /* Update NRC */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
    } /* End of non paged response */
  }
  else
  {
    /* Update NRC */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
}
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
