/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DspOBDInternals.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for OBD internal Functions **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By                  Description                   **
********************************************************************************
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.1      15-02-2017    Jin    Jung    #5460                              **
**                                                                            **
** 1.0.0      09-01-2013    Autron         Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_DspOBDInternals.h"
#include "Rte_Dcm.h"
#include "Dem.h"
#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Cfg.h"
#include "Dcm_PackUnPack.h"
#include "Dcm_Config.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dcm_DemGetNumberOfOBDDTC                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function for the OBDservices   **
**                        (0x03, 0x07, 0x0A) to calculate the number          **
**                        of Filtered DTcs.                                   **
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
**                        Dcm_PrtclTxBufStatus, Dcm_TxRespStatus,             **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GpMsgContext, Dcm_GucNumofDTC,                  **
**                        Dcm_DspSerPgStatus                                  **
**                        Function(s) invoked :None                           **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
 (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))
FUNC(void, DCM_CODE) Dcm_DemGetNumberOfOBDDTC(void)
{

  Dem_ReturnGetNumberOfFilteredDTCType LddNumFilteredDTCType;
  uint32 LulRespLength;
  uint16 LusNumberOfFilteredDTC;
  Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_FALSE;
  Dcm_GddNegRespError = DCM_E_POSITIVERESPONSE;

  /* Get the number of DTC matching the defined status mask */
  LddNumFilteredDTCType = Dem_GetNumberOfFilteredDTC(&LusNumberOfFilteredDTC);
  /* Check whether getting number of DTC was successful */
  if(LddNumFilteredDTCType == DEM_NUMBER_OK)
  {
    /* DTCHighByte + DTCLowByte = 2 for every
       DTC + 1(No.of.DTC) */
    LulRespLength = (LusNumberOfFilteredDTC << DCM_ONE) + DCM_ONE;
    /* Update the complete response length that is to be transmitted */
    Dcm_GstMsgContext.resDataLen = LulRespLength;
    /*
    * Check if the response buffer is capable of accommodating the
    * complete response at once
    */
    if(LulRespLength <= (Dcm_GstMsgContext.resMaxDataLen))
    {
      /* Update the Number of Filtered DTC */
      Dcm_GpReqResData[DCM_ZERO] = (uint8)LusNumberOfFilteredDTC;
      /* Reset the pointer to the response data buffer */
      Dcm_GpReqResData = &Dcm_GpReqResData[DCM_ONE];
      /*
      * Pass the buffer size with two values less since sub function and
      * availabilityMask is already updated
      */
      LulRespLength = LulRespLength - DCM_ONE;
      (void)Dcm_DspReadOBDDTCInfo(LulRespLength);
    }
    else
    {
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      /* Store the number of filtered DTCs in this variable to update in page */
      Dcm_GucNumofDTC = (uint8)LusNumberOfFilteredDTC;
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
    Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_TRUE;
    Dcm_TxRespStatus.ucNormResponse = DCM_TRUE;
  }
  else /* if(LddNumFilteredDTCType == DEM_NUMBER_FAILED) */
  {
    /* Update Negative response code */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspReadOBDDTCInfo                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function for the OBDservices   **
**                        (0x03, 0x07, 0x0A) to report the Filtered DTcs      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LulBufferSize                                       **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GddCurrentLength, Dcm_GpMsgContext,             **
**                        Dcm_GddNegRespError, Dcm_GpReqResData,              **
**                        Dcm_GunDTC.                                         **
**                        Function(s) invoked : Dem_GetNextFilteredDTC        **
**                                                                            **
*******************************************************************************/
#if((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
 (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))
FUNC(uint32, DCM_CODE) Dcm_DspReadOBDDTCInfo(uint32 LulBufferSize)
{
  uint32 LulRespBufferSize;
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint32 LulRemainingLength;
  #endif
  uint8 LucReturnRes;
  uint8 LucDTCStatus;
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint8 LucCount;
  #endif

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
  while((LulRespBufferSize > DCM_ONE) &&
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    (((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) &&
    (LulRemainingLength >= DCM_TWO)) ||
    ((Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE))) &&
    #endif
    (LucReturnRes != DEM_FILTERED_NO_MATCHING_DTC))
  {
    LucReturnRes = Dem_GetNextFilteredDTC
    (&Dcm_GunDTC.ulLongReg32, &LucDTCStatus);

    if(LucReturnRes == DEM_FILTERED_OK)
    {
      /* DTC High Byte */
      Dcm_GpReqResData[DCM_ZERO] = Dcm_GunDTC.ddByte.ucMidHiByte;
      /* DTC Middle Byte */
      Dcm_GpReqResData[DCM_ONE] = Dcm_GunDTC.ddByte.ucMidLowByte;
      /* Increment pointer by two bytes */
      Dcm_GpReqResData = &Dcm_GpReqResData[DCM_TWO];
      /* Update the response buffer size */
      LulRespBufferSize = LulRespBufferSize - DCM_TWO;
      /* Update the Temporary length of response buffer */
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
      {
         /* MISRA Rule          : 21.1
           Message            : Unsigned arithmetic apparently results in
                    wraparound past zero.
           Reason             : This is the prototype specified in the
                    specification.
           Verification       : However, part of the code is verified
                    manually and it is not having any impact.
        */
        LulRemainingLength = LulRemainingLength - DCM_TWO;
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
      (LulRemainingLength >= DCM_TWO) && (LulRespBufferSize > DCM_ONE))
    {
      do
      {
        for(LucCount = DCM_ZERO; LucCount < DCM_TWO; LucCount++)
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
        LulRespBufferSize = LulRespBufferSize - DCM_TWO;
        LulRemainingLength  = LulRemainingLength - DCM_TWO;
      }while((LulRespBufferSize > DCM_ONE) && (LulRemainingLength != DCM_ZERO));
    }
    #endif
  }
  return(LulBufferSize - LulRespBufferSize);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_GetIDIndex                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This will give the index of ID(PID/VID/TID/OBDMID)  ** 
**                        in DcmDspPid configuration data.                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIDType and LucIDValue                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpIDIndex                                           **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpOBDBaseAddress           **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
(DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
(DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON) || \
(DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
(DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetIDIndex(uint8 LucIDType,
uint8 LucIDValue,
P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpIDIndex)
{
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) LpIDBuffer;
  Std_ReturnType LddRetVal;
  uint8 LucIndex;
  uint8 LucTotalID = (uint8)0x00;
  /* load E_NOT_OK */
  LddRetVal = E_NOT_OK;

  /* Get total number of IDs configured */
  if(DCM_GET_PID == LucIDType)
  {
    LucTotalID = Dcm_Total_Num_Of_PIDs;
  }
  else if (DCM_GET_OBDMID == LucIDType)
  {
    LucTotalID = Dcm_Total_Num_Of_OBDMIDs;
  }
  else if (DCM_GET_TID == LucIDType)
  {
    LucTotalID = Dcm_Total_Num_Of_TIDs;
  }
  else if (DCM_GET_VID == LucIDType)
  {
    LucTotalID = Dcm_Total_Num_OF_VIDs;
  }
  else
  {
  }

  /* To get Respective Buffer ID */
  LpIDBuffer = Dcm_GpOBDBaseAddress[LucIDType];
  for(LucIndex = DCM_ZERO; LucIndex < LucTotalID; LucIndex++)
  {
    /* Check the ID value with the respective buffer to get index */
    if(LucIDValue == LpIDBuffer[LucIndex])
    {
      LddRetVal = E_OK;
      *LpIDIndex = LucIndex;
      break;
    }
  }
  /* return the status */
  return (LddRetVal);
}

/*******************************************************************************
** Function Name        : Dcm_DspGetAvailibiltyIDStatus                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to provide the       **
**                        information regarding status of supported Ids       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIDType, ReqBuffer and LucIDCount                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LucMix_DemRPort                                     **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpOBDBaseAddress,          **
**                        Dcm_GaaPIDConfig                                    **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_DspGetAvailibiltyIDStatus
(uint8 LucIDType,
P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) ReqBuffer, uint8 LucIDCount,
uint8 LucMix_DemRPort )
{
  #if(DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
  uint8 LaaDemPID[DCM_EIGHT] = {
                                DCM_DEMPID1, DCM_DEMPID1C, DCM_DEMPID21,
                                DCM_DEMPID30, DCM_DEMPID31, DCM_DEMPID41,
                                DCM_DEMPID4D, DCM_DEMPID4E,
                              };
  #endif
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) LpIDBuffer;
  uint8 LddAVailID;
  uint8 LucIndex;
  uint8 LucIDValue;
  uint8 LucIDBufferIndex;
  #if(DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
  uint8 LucDemListIndex;
  #endif
  uint8 LucTotalIDConfig = DCM_ZERO;
  uint8 LucRPortCount;
  uint8 LucDemCount;
  uint8 LucAvlCount;
  uint8 LucOtherCount;
  uint8 LucMaskValue;

  LucRPortCount = DCM_ZERO;
  LucDemCount = DCM_ZERO;
  LucAvlCount = DCM_ZERO;
  LucOtherCount = DCM_ZERO;

  /* Get total number of ID configured */
  if(DCM_GET_PID == LucIDType)
  {
    LucTotalIDConfig = Dcm_Total_Num_Of_PIDs;
  }
  else if (DCM_GET_OBDMID == LucIDType)
  {
    LucTotalIDConfig = Dcm_Total_Num_Of_OBDMIDs;
  }
  else if (DCM_GET_TID == LucIDType)
  {
    LucTotalIDConfig = Dcm_Total_Num_Of_TIDs;
  }
  else if (DCM_GET_VID == LucIDType)
  {
    LucTotalIDConfig = Dcm_Total_Num_OF_VIDs;
  }
  else
  {
  }

  /* To get Respective Buffer ID */
  LpIDBuffer = Dcm_GpOBDBaseAddress[LucIDType];
  /* Assume ID not configured */
  LddAVailID = DCM_NOT_CONFIG_ID;
  for(LucIndex = DCM_ZERO; LucIndex < LucIDCount; LucIndex++)
  {
    /* First time its same for all SID */
    if(LucIndex != DCM_ZERO)
    {
      if(LucMix_DemRPort == DCM_TWO)
      {
        /* MISRA Rule        : 13.6
        Message            : Control variable, LucIndex,
                             modified in body of loop
        Reason             : Once the search element found, control
                             exiting from the for loop to terminate
                             next iteration.
        Verification       : However, part of the code
                             is verified manually and
                             it is not having any impact.
        */
        LucIndex++;
      }
    }
    /* Get ID value from the request buffer */
    LucIDValue = ReqBuffer[LucIndex];
    /* Search in the configured list */
    for(LucIDBufferIndex = DCM_ZERO; LucIDBufferIndex < LucTotalIDConfig;
      LucIDBufferIndex++)
    {
      /* Check whether ID configured or not */
      if(LucIDValue == LpIDBuffer[LucIDBufferIndex])
      {
        switch(LucMix_DemRPort)
        {
          case DCM_ONE:
            #if(DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)

            if((Dcm_GaaPIDConfig[LucIDBufferIndex].ucPidService == DCM_ONE) ||
              (Dcm_GaaPIDConfig[LucIDBufferIndex].ucPidService == DCM_THREE))
            {
              /* Assume PID is belongs to RPort */
              LddAVailID = DCM_R_PORT_PID;
              /* Search for configured one belongs to Dem or RPort */
              for(LucDemListIndex = DCM_ZERO; LucDemListIndex < DCM_EIGHT; LucDemListIndex++)
              {
                if(LucIDValue == LaaDemPID[LucDemListIndex])
                {
                  /* PID is belongs to Dem */
                  LddAVailID = DCM_DEM_PID;
                  /* MISRA Rule        : 13.6
                    Message            : Control variable, LucDemListIndex,
                                         modified in body of loop
                    Reason             : Once the search element found, control
                                         exiting from the for loop to terminate
                                         next iteration.
                    Verification       : However, part of the code
                                         is verified manually and
                                         it is not having any impact.
                  */
                  /* To skip the next iterations */
                  LucDemListIndex = DCM_NINE;
                }
              }
            }
            #endif
          break;

          case DCM_TWO:
              #if(DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON)
              if((Dcm_GaaPIDConfig[LucIDBufferIndex].ucPidService == DCM_TWO) ||
              (Dcm_GaaPIDConfig[LucIDBufferIndex].ucPidService == DCM_THREE))
              {
                if(LucIDValue == DCM_TWO)
                {
                  LddAVailID = DCM_TWO_PID;
                }
                else
                {
                  LddAVailID = DCM_OTHER_PID;
                }
              }
              #endif
          break;

          case DCM_SIX:
          case DCM_EIGHT:
          case DCM_NINE:
               LddAVailID = DCM_OTHER_PID;
          break;

          default   : break;

        } /* End of Switch */
        /* MISRA Rule        : 13.6
          Message            : Control variable, LucIDBufferIndex,
                               modified in body of loop
          Reason             : Once the search element found, control
                               exiting from the for loop to terminate
                               next iteration.
          Verification       : However, part of the code
                               is verified manually and
                               it is not having any impact.
        */
        /* To skip the next iterations */
        LucIDBufferIndex = LucTotalIDConfig;
      }
      else
      {
        LddAVailID = DCM_NOT_CONFIG_ID;
      }
    }
    /* when ID not matched in the configured list */
    if(LddAVailID == DCM_NOT_CONFIG_ID )
    {
      switch(LucIDValue)
      {

        case DCM_ZERO :
             LucMaskValue = DCM_ONE;
        break;
        case DCM_THIRTY_TWO :
             LucMaskValue = DCM_TWO;
        break;
        case DCM_SIXTY_FOUR :
             LucMaskValue = DCM_FOUR;
        break;
        case DCM_NINTY_SIX :
             LucMaskValue = DCM_EIGHT;
        break;
        case DCM_ONE_TWO_EIGHT :
             LucMaskValue = DCM_SIXTEEN;
        break;
        case DCM_ONE_SIXTY :
             LucMaskValue = DCM_THIRTY_TWO;
        break;
        case DCM_ONE_NINE_TWO :
             LucMaskValue = DCM_SIXTY_FOUR;
        break;
        case DCM_TWO_TWO_FOUR :
             LucMaskValue = DCM_ONE_TWO_EIGHT;
        break;
        default   :
             LucMaskValue = DCM_ZERO;
        break;
      }
      if(LucMaskValue != DCM_ZERO)
      {
        LddAVailID = DCM_AVAIL_ID;
      }
    }
    if((LddAVailID != DCM_NOT_CONFIG_ID))
    {
      if(LddAVailID == DCM_AVAIL_ID)
      {
        LucAvlCount++;
      }
      /* Check whether PID belongs to RPort PID */
      else if(LddAVailID == DCM_R_PORT_PID)
      {
        LucRPortCount++;
      }
      /* Check whether PID belongs to Dem service PID */
      else if (LddAVailID == DCM_DEM_PID)
      {
        LucDemCount++;
      }
      /* Check whether PID belongs to Dem service PID */
      else if (LddAVailID == DCM_OTHER_PID)
      {
        LucOtherCount++;
      }
      else
      {
        /* To avoid QAC warning */
      }
      /* combination not allowed */
      if(((LucAvlCount > DCM_ZERO) && (LucRPortCount > DCM_ZERO)) ||
        ((LucAvlCount > DCM_ZERO) && (LucDemCount > DCM_ZERO)) ||
        ((LucAvlCount > DCM_ZERO) && (LucOtherCount > DCM_ZERO)))
      {
        LddAVailID = DCM_NOT_CONFIG_ID;
        /* MISRA Rule        : 13.6
          Message            : Control variable, LucIndex,
                               modified in body of loop
          Reason             : Once the search element found, control
                               exiting from the for loop to terminate
                               next iteration.
          Verification       : However, part of the code
                               is verified manually and
                               it is not having any impact.
        */
        /* To terminate next iteration */
        LucIndex = LucIDCount;
      }
    }
  }

  return LddAVailID;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetSizeOfIDS                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Internal function is called for the OBD service**
**                        to get size of requested IDs                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIDType, LucIDCount,LpRespLenOfConfigPIDS and     **
**                        LucSID, LpReqResData                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaVehInfoConfig,          **
**                        Dcm_GaaPIDConfig                                    **
**                        Function(s) invoked : Dcm_GetIDIndex                **
**                                                                            **
*******************************************************************************/
#if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
(DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
(DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON) || \
(DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
(DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetSizeOfIDS
  ( uint8 LucIDType, uint8 LucIDCount,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpRespLenOfConfigPIDS,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) LpReqResData,
  uint8 LucSID)
{
  #if(DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
  P2CONST(Dcm_VehInfoData, AUTOMATIC, DCM_APPL_CONST) LpVehInfoData;
  P2CONST(Dcm_VehInfoConfigType, AUTOMATIC, DCM_APPL_CONST) LpVehInfoConfigData;
  #endif

  #if(DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
  P2CONST(Dcm_OBDMidConfigType, AUTOMATIC, DCM_APPL_CONST) LpObdMidConfig;
  #endif
  Std_ReturnType LddRetValue;
  uint8 LucPIDIndex;
  uint8 LucPIDValue;
  uint8 LucIDIndex;
  #if(DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
  uint8 LucIndex;
  #endif
  LddRetValue = E_OK;


  /* Initialize total length with zero */
  *LpRespLenOfConfigPIDS = DCM_ZERO;
  /* Calculate size of data related to all PIDs */
  for(LucPIDIndex = DCM_ZERO; LucPIDIndex < LucIDCount; LucPIDIndex++)
  {
    /* First time its same for all SID */
    if(LucPIDIndex != DCM_ZERO)
    {
      switch(LucSID)
      {
        case DCM_ONE:
        case DCM_SIX:
        case DCM_EIGHT:
        case DCM_NINE:

        break;

        case DCM_TWO:
        /* MISRA Rule        : 13.6
          Message            : Control variable, LucPIDIndex,
                               modified in body of loop
          Reason             : Once the search element found, control
                               exiting from the for loop to terminate
                               next iteration.
          Verification       : However, part of the code
                               is verified manually and
                               it is not having any impact.
        */
        LucPIDIndex++;
        break;

        default:  break;
      }
    }
    /* Get the PID value from the request buffer */
    LucPIDValue = LpReqResData[LucPIDIndex];
    LddRetValue = Dcm_GetIDIndex(LucIDType, LucPIDValue, &LucIDIndex);
    if(LddRetValue == E_OK)
    {
      switch(LucSID)
      {
        #if(DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
        case DCM_ONE:
          if((Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_ONE) ||
          (Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_THREE))
          {
            /* Total response length is PID + size of PID */
            *LpRespLenOfConfigPIDS = *LpRespLenOfConfigPIDS + DCM_ONE +
            Dcm_GaaPIDConfig[LucIDIndex].ucPidBufferSize;
          }
        break;
        #endif

        #if(DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON)
        case DCM_TWO:
          if((Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_TWO) ||
          (Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_THREE))
          {
            /* Total response length is
            ( PID + FF REC NUMBER + size of PID ) */
            *LpRespLenOfConfigPIDS = *LpRespLenOfConfigPIDS + DCM_ONE +
            DCM_ONE + Dcm_GaaPIDConfig[LucIDIndex].ucPidBufferSize;
          }
        break;
        #endif

        #if(DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
        case DCM_SIX:
          LpObdMidConfig = &Dcm_GaaOBDMidConfig[LucIDIndex];
          /* Total response length is PID + size of PID */
          *LpRespLenOfConfigPIDS = *LpRespLenOfConfigPIDS + DCM_ONE +
                    (DCM_EIGHT * LpObdMidConfig->ucNoOfTids);
        break;
        #endif

        #if(DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON)
        case DCM_EIGHT:
        break;
        #endif

        #if(DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
        case DCM_NINE:
           LpVehInfoConfigData = &Dcm_GaaVehInfoConfig[LucIDIndex];
           LpVehInfoData = LpVehInfoConfigData->pDcmVehInfoData;
           /* Total response length is PID + size of PID */
           *LpRespLenOfConfigPIDS = *LpRespLenOfConfigPIDS + DCM_ONE + DCM_ONE;
           for(LucIndex = DCM_ZERO; (LucIndex <
                 LpVehInfoConfigData->ucNoOfVehInfoData); LucIndex++)
           {
             *LpRespLenOfConfigPIDS = *LpRespLenOfConfigPIDS +
                   LpVehInfoData->ucVehInfoBufSize;
               
             LpVehInfoData = &LpVehInfoData[1u];
           }
        break;
        #endif
        default:
        break;
      } /* End of switch */
    }
    else
    {
      LddRetValue = E_NOT_OK;
      break;
    }
  }
  return LddRetValue;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspReadOBD_AvlInfo                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to update            **
**                        availability list                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LpRxBuffer,LucPIDCount,LucIDType and LulBufferSize  **
**                                                                            **
** InOut parameter      : LpTxBuffer                                          **
**                                                                            **
** Output Parameters    : LpTxBuffer                                          **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GucPIDCount                                     **
**                        Function(s) invoked : Dcm_DspGetConfigIDS           **
**                                                                            **
*******************************************************************************/
#if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
(DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
(DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
(DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
FUNC(uint32, DCM_CODE) Dcm_DspReadOBD_AvlInfo
( P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) LpRxBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer,
  uint32 LulBufferSize, uint8 LucPIDCount, uint8 LucIDType )
{
  Std_ReturnType LddReturnValue;
  uint32 LulRespBufferSize;
  uint8 LucPIDValue;
  uint8 LucPIDIndex;
  uint8 LucSizeOfPID;

  /* Initialize with the configured buffer size */
  LulRespBufferSize = LulBufferSize;

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
  }
  #endif
  Dcm_GblAvailabilityPIDFlag = DCM_FALSE;

  for(LucPIDIndex = DCM_ZERO; (LulRespBufferSize > DCM_FOUR) &&
   (LucPIDCount > DCM_ZERO); LucPIDIndex++)
  {
    /* Get the PID value from the request buffer */
    LucPIDValue = LpRxBuffer[LucPIDIndex];
    /* Update PID value to TX buffer*/
    *LpTxBuffer = LucPIDValue;
	/* Increase ptr */
    LpTxBuffer = &LpTxBuffer[DCM_ONE];
    /* Get All Availability list of 4 bytes */
    if(LucIDType == DCM_GET_PID)
    {
      #if(DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
      LddReturnValue =
      Dcm_DspGetConfigIDS1(LucPIDValue, LucIDType, LpTxBuffer, &LucSizeOfPID);
      #else
      LddReturnValue = E_NOT_OK;
      #endif
    }
    else
    {
      LddReturnValue =
      Dcm_DspGetConfigIDS(LucPIDValue, LucIDType, LpTxBuffer, &LucSizeOfPID);
    }
    if(LddReturnValue == E_OK)
    {
      /* Move response buffer pointer by 4 bytes */
      LpTxBuffer = &LpTxBuffer[DCM_FOUR];
      /* Update the response buffer size */
      LulRespBufferSize = LulRespBufferSize - DCM_FIVE;
      Dcm_GucPIDCount--;

      Dcm_GblAvailabilityPIDFlag = DCM_TRUE;
    }
    else
    {
      LpTxBuffer = &LpTxBuffer[-1];
    }

    LucPIDCount--;
  }
  LulBufferSize = LulBufferSize - LulRespBufferSize;
  return(LulBufferSize);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetConfigIDS                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to get the configured**
**                        Ids supported for the services                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIDValue and LucIDType                            **
**                                                                            **
** InOut parameter      : LpTxBuffer                                          **
**                                                                            **
** Output Parameters    : LpSizeOfID                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpEncodeByte,              **
**                        Dcm_GaaPIDEncodeByte.                               **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
(DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
(DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON) || \
(DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
(DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetConfigIDS
  (uint8 LucIDValue, uint8 LucIDType,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpSizeOfID )
{
  P2CONST(Dcm_IDEncodeByteConfig, AUTOMATIC, DCM_APPL_CONST)
    LpIDEncodeByte;
  Std_ReturnType LddRetValue;
  uint8 LucMaskValue;
  uint8 LucIndex;
  uint8 LucAvalListIndex;
  uint8 LucAvalConfigList = (uint8)0x00;
  uint8 LucRightPosition;

  LucRightPosition = DCM_ONE;
  LddRetValue = E_NOT_OK;

  LucAvalListIndex = DCM_ZERO;
  switch(LucIDValue)
  {

    case DCM_ZERO :
         LucMaskValue = DCM_ONE;
    break;
    case DCM_THIRTY_TWO :
         LucMaskValue = DCM_TWO;
    break;
    case DCM_SIXTY_FOUR :
         LucMaskValue = DCM_FOUR;
    break;
    case DCM_NINTY_SIX :
         LucMaskValue = DCM_EIGHT;
    break;
    case DCM_ONE_TWO_EIGHT :
         LucMaskValue = DCM_SIXTEEN;
    break;
    case DCM_ONE_SIXTY :
         LucMaskValue = DCM_THIRTY_TWO;
    break;
    case DCM_ONE_NINE_TWO :
         LucMaskValue = DCM_SIXTY_FOUR;
    break;
    case DCM_TWO_TWO_FOUR :
         LucMaskValue = DCM_ONE_TWO_EIGHT;
    break;
    default:
         LucMaskValue = DCM_ZERO;
    break;
  }

  if(DCM_GET_PID == LucIDType)
  {
    LucAvalConfigList = Dcm_PID_AVL_Config_List_FreezeFrame;
  }
  else if (DCM_GET_OBDMID == LucIDType)
  {
    LucAvalConfigList = DCM_OBDMID_AVL_Config_List;
  }
  else if (DCM_GET_TID == LucIDType)
  {
    LucAvalConfigList = Dcm_TID_AVL_Config_List;
  }
  else if (DCM_GET_VID == LucIDType)
  {
    LucAvalConfigList = Dcm_VID_AVL_Config_List;
  }
  else
  {
  }

  /* Generic for all services */
  if((LucAvalConfigList & LucMaskValue) != DCM_ZERO)
  {
    LddRetValue = E_OK;
    for(LucIndex = DCM_ZERO; (LucIndex < DCM_EIGHT) && (LucRightPosition <=
      LucMaskValue); LucIndex++)
    {
      if((LucAvalConfigList & LucRightPosition) != DCM_ZERO)
      {
        LucAvalListIndex++;
        if(LucRightPosition == LucMaskValue)
        {
          break;
        }
      }
      LucRightPosition <<= DCM_ONE;
    }

    /* Get SID */
    LucAvalListIndex = LucAvalListIndex - DCM_ONE;
    /* Get respective Encode Buffer for service 01 */
    #if(DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON)
    if(LucIDType == DCM_ZERO)
    {
      LpIDEncodeByte = &Dcm_GaaPIDEncodeByte[LucIDType];
    }
    else
    #endif
    {
      LpIDEncodeByte = Dcm_GpEncodeByte[LucIDType];
    }

    /* Update 32 bit information */
    *LpTxBuffer = LpIDEncodeByte[LucAvalListIndex].ucEncodeByteA;

    /* Increment pointer */
    LpTxBuffer = &LpTxBuffer[1u];
	
    *LpTxBuffer = LpIDEncodeByte[LucAvalListIndex].ucEncodeByteB;
	
    /* Increment pointer */
    LpTxBuffer = &LpTxBuffer[1u];
	
    *LpTxBuffer = LpIDEncodeByte[LucAvalListIndex].ucEncodeByteC;

    /* Increment pointer */
    LpTxBuffer = &LpTxBuffer[1u];
	
    *LpTxBuffer = LpIDEncodeByte[LucAvalListIndex].ucEncodeByteD;
	
    *LpSizeOfID = DCM_FOUR;
  }

  return LddRetValue;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetConfigIDS1                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Internal function is called for the OBD service**
**                        to get the Configured IDs for service(0x01)         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIDType, LucIDValue,LpRespLenOfConfigPIDS and     **
**                        LucSID                                              **
**                                                                            **
** InOut parameter      : LpTxBuffer                                          **
**                                                                            **
** Output Parameters    : LpSizeOfID                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GaaPIDEncodeByte1         **
**                        Function(s) invoked : Dcm_GetIDIndex                **
**                                                                            **
*******************************************************************************/
#if(DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetConfigIDS1
  (uint8 LucIDValue, uint8 LucIDType,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpSizeOfID )
{
  P2CONST(Dcm_IDEncodeByteConfig, AUTOMATIC, DCM_APPL_CONST)
    LpIDEncodeByte;
  Std_ReturnType LddRetValue;
  uint8 LucMaskValue;
  uint8 LucIndex;
  uint8 LucAvalListIndex;
  uint8 LucAvalConfigList = (uint8)0x00;
  uint8 LucRightPosition;

  LucRightPosition = DCM_ONE;
  LddRetValue = E_NOT_OK;

  LucAvalListIndex = DCM_ZERO;
  switch(LucIDValue)
  {

    case DCM_ZERO :
         LucMaskValue = DCM_ONE;
    break;
    case DCM_THIRTY_TWO :
         LucMaskValue = DCM_TWO;
    break;
    case DCM_SIXTY_FOUR :
         LucMaskValue = DCM_FOUR;
    break;
    case DCM_NINTY_SIX :
         LucMaskValue = DCM_EIGHT;
    break;
    case DCM_ONE_TWO_EIGHT :
         LucMaskValue = DCM_SIXTEEN;
    break;
    case DCM_ONE_SIXTY :
         LucMaskValue = DCM_THIRTY_TWO;
    break;
    case DCM_ONE_NINE_TWO :
         LucMaskValue = DCM_SIXTY_FOUR;
    break;
    case DCM_TWO_TWO_FOUR :
         LucMaskValue = DCM_ONE_TWO_EIGHT;
                break;
    default   :
         LucMaskValue = DCM_ZERO;
    break;
  }

  if(DCM_GET_PID == LucIDType)
  {
    LucAvalConfigList = Dcm_PID_AVL_Config_List;
  }
  else if (DCM_GET_OBDMID == LucIDType)
  {
    LucAvalConfigList = DCM_OBDMID_AVL_Config_List;
  }
  else if (DCM_GET_TID == LucIDType)
  {
    LucAvalConfigList = Dcm_TID_AVL_Config_List;
  }
  else if (DCM_GET_VID == LucIDType)
  {
    LucAvalConfigList = Dcm_VID_AVL_Config_List;
  }
  else
  {
  }
  
  /* Generic for all services */
  if((LucAvalConfigList & LucMaskValue) != DCM_ZERO)
  {
    LddRetValue = E_OK;
    for(LucIndex = DCM_ZERO; (LucIndex < DCM_EIGHT) && (LucRightPosition <=
      LucMaskValue); LucIndex++)
    {
      if((LucAvalConfigList & LucRightPosition) != DCM_ZERO)
      {
        LucAvalListIndex++;
        if(LucRightPosition == LucMaskValue)
        {
          break;
        }
      }
      LucRightPosition <<= DCM_ONE;
    }

    LpIDEncodeByte = &Dcm_GaaPIDEncodeByte1[LucIDType];

    /* MISRA Rule       : 21.1
       Message          : An integer expression with a value that is
                apparently negative is being converted to
                an unsigned type.
       Reason           : An value is decremented from the unsigned
                variable
       Verification     : However, part of the code
                is verified manually and
                it is not having any impact.
    */
    LucAvalListIndex = LucAvalListIndex - DCM_ONE;

    /* Update 32 bit information */
    *LpTxBuffer = LpIDEncodeByte[LucAvalListIndex].ucEncodeByteA;
    
    LpTxBuffer = &LpTxBuffer[1u];

	*LpTxBuffer= LpIDEncodeByte[LucAvalListIndex].ucEncodeByteB;

    LpTxBuffer = &LpTxBuffer[1u];
	
    *LpTxBuffer = LpIDEncodeByte[LucAvalListIndex].ucEncodeByteC;

    LpTxBuffer = &LpTxBuffer[1u];
	
    *LpTxBuffer = LpIDEncodeByte[LucAvalListIndex].ucEncodeByteD;
    *LpSizeOfID = DCM_FOUR;
    LddRetValue = E_OK;

  }

  return LddRetValue;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspReadOBD_1_DemInfo                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to Process the PID   **
**                        request for Service(0x01)                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LpRxBuffer,LulBufferSize and LucPIDCount            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTxBuffer, LpRespLength                            **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GpMsgContext, Dcm_GaaPidSignalData,             **
**                        Dcm_GaaPIDUint8Func, Dcm_GaaPIDSint32Func,          **
**                        Dcm_GaaPIDConfig, Dcm_GucPIDCount,                  **
**                        Dcm_GaaPIDUint16Func, Dcm_GaaPIDUint32Func,         **
**                        Dcm_GaaPIDSint8Func, Dcm_GaaPIDSint16Func,          **
**                        Dcm_GaaSigWrFuncPtr, Dcm_GddNegRespError.           **
**                        Function(s) invoked : Dcm_DspGetSizeOfIDS,          **
**                        Dcm_GetIDIndex                                      **
**                                                                            **
*******************************************************************************/
#if(DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
/* MISRA Rule         : 16.7
   Message            : A pointer parameter in a function prototype should be
                        declared as pointer to const if the pointer is not
                        used to modify the addressed object.
   Reason             : This is the prototype provided by Dcm.
   Verification       : However, part of the code is verified
                        manually and it is not having any impact.
*/
FUNC(uint16, DCM_CODE) Dcm_DspReadOBD_1_DemInfo
(
P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpRxBuffer,
P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer,
P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpRespLength, uint8 LucPIDCount)
{
  Std_ReturnType LddReturnValue;
  uint8 LucPIDValue;
  uint8 LucPIDIndex;
  uint8 LucNumofPIDData;
  uint8 LucDataIndex;
  uint8 LucIDIndex;
  uint8 LucPIDSize;
  uint8 LucCount;
  uint8 LucDestBuffer[DCM_MAXVALUE];
  uint8 LucDemListIndex;
  uint8 LucMix_DemRPort;
  #if(DCM_OBD_PID_SUPPORT_INFO == STD_ON)
  uint8 LucSupByte;
  uint8 LucSupRefBit;
  uint8 LucSupInfoByte;
  #endif
  #if(DCM_PID_DATA_SENDER_RECEIVER == STD_ON)
  uint8 LucDataType;
  #endif
  uint16 LusRespLength;
  uint8 LucStartByte;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxDataBuffer;
  P2CONST(Dcm_PIDConfigType, AUTOMATIC, DCM_APPL_CONST)LpPIDTAB;
  P2CONST(Dcm_DspPidData, AUTOMATIC, DCM_APPL_CONST)LpPIDData;
  P2CONST(Dcm_PIDPackSignal, AUTOMATIC, DCM_APPL_CONST)LpPackSignal;
  Dcm_PackUnpackSignalData LddPackSignal;
  P2CONST(Dcm_DspPidData, AUTOMATIC, DCM_APPL_CONST)LpDcmDspPidData;

  uint8 LaaDemPID[DCM_EIGHT] = {
                                DCM_DEMPID1, DCM_DEMPID1C, DCM_DEMPID21,
                                DCM_DEMPID30, DCM_DEMPID31, DCM_DEMPID41,
                                DCM_DEMPID4D, DCM_DEMPID4E,
                               };
  LucStartByte = DCM_ZERO;

  /* Get the response length of requested IDs For READ DID */
  LddReturnValue = Dcm_DspGetSizeOfIDS( DCM_GET_PID, LucPIDCount,
    &LusRespLength, LpRxBuffer, DCM_ONE);
  *LpRespLength = LusRespLength;
  if(LusRespLength <= (Dcm_GstMsgContext.resMaxDataLen))
  {
    for(LucPIDIndex = DCM_ZERO;
       (LucPIDIndex < LucPIDCount); LucPIDIndex++)
    {
      /* Get the PID value from the request buffer */
      LucPIDValue = LpRxBuffer[LucPIDIndex];
      /* Assume PID is belongs to RPort */
      LucMix_DemRPort = DCM_R_PORT_PID;
      /* Search for configured one belongs to Dem or RPort */
      for(LucDemListIndex = DCM_ZERO; LucDemListIndex < DCM_EIGHT; LucDemListIndex++)
      {
        if(LucPIDValue == LaaDemPID[LucDemListIndex])
        {
          /* PID is belongs to Dem */
          LucMix_DemRPort = DCM_DEM_PID;
          break;
        }
      }

      if(LucMix_DemRPort == DCM_DEM_PID)
      {
        (void) Dcm_GetIDIndex(DCM_GET_PID, LucPIDValue,
          &LucIDIndex);
        if((Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_ONE) ||
          (Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_THREE))
        {
          LpDcmDspPidData = Dcm_GaaPIDConfig[LucIDIndex].pDcmDspPidData;

          /*Get the PID size in bytes */
          LucPIDSize = Dcm_GaaPIDConfig[LucIDIndex].ucPidBufferSize;

          /* Update PID value to TX buffer*/
          *LpTxBuffer = LucPIDValue;
		  /* Increament buffer ptr */
		  LpTxBuffer = &LpTxBuffer[1u];

          LpDcmDspPidData->pGetPidValFnc(&LucDestBuffer[DCM_ZERO]);
          LucCount = DCM_ZERO;
          while(LucCount < LucPIDSize)
          {
            *LpTxBuffer = LucDestBuffer[LucCount];
            /* Increament buffer ptr */
            LpTxBuffer = &LpTxBuffer[1u];
            LucCount++;
          }
        }
      }
      else
      {
        (void) Dcm_GetIDIndex(DCM_GET_PID, LucPIDValue,
          &LucIDIndex);
        LpPIDTAB = &Dcm_GaaPIDConfig[LucIDIndex];
        /* Get the Number of PID Data configured for the PID */
        LucNumofPIDData = LpPIDTAB->ucNumofPIDData;
		
        #if(DCM_OBD_PID_SUPPORT_INFO == STD_ON)
        /* Initialize the Support Info Byte to ZERO */
        LucSupInfoByte = DCM_ZERO;
        if(LpPIDTAB->ucNumofPIDSupportInfo != DCM_ZERO)
        {
          LpPIDData = LpPIDTAB->pDcmDspPidData;
          for(LucDataIndex = DCM_ZERO; LucDataIndex < LucNumofPIDData;
          LucDataIndex++)
          {
            /* Check if Support Info is Configured for the signal */
            if(LpPIDData->pDcmDspPidDataSupportInfoRef != NULL_PTR)
            {
              LucSupRefBit = LpPIDData->ucDcmDspPidDataSupportInfoBit;
              LucSupRefBit = LucSupRefBit % DCM_EIGHT;
              LucSupByte = DCM_ONE << LucSupRefBit;
              LucSupInfoByte = LucSupInfoByte | LucSupByte;
            }
            LpPIDData++;
          }
        }
        #endif
		
        /* Initialize to the first PID signal */
        LpPIDData = LpPIDTAB->pDcmDspPidData;
        *LpTxBuffer = LucPIDValue;
        /* Increament buffer ptr */
        LpTxBuffer = &LpTxBuffer[1u];
        LpTxDataBuffer = LpTxBuffer;
		
        #if(DCM_OBD_PID_SUPPORT_INFO == STD_ON)
        if(LucSupInfoByte != DCM_ZERO)
        {
          *LpTxBuffer = LucSupInfoByte;
          /* Increament buffer ptr */
          LpTxBuffer = &LpTxBuffer[1u];
        }
        #endif
		
        for(LucDataIndex = DCM_ZERO; LucDataIndex < LucNumofPIDData; LucDataIndex++)
        {
          if(LpPIDData->ucDcmDspPidDataPos < DCM_EIGHT)
          {
            break;
          }
		  
          /* Increment to the next signal */
          LpPIDData = &LpPIDData[1u];
        }
        /* Initialize to the first PID signal */
        LpPIDData = LpPIDTAB->pDcmDspPidData;

        for(LucDataIndex = DCM_ZERO; LucDataIndex < LucNumofPIDData; LucDataIndex++)
        {
          /* Get the size of the Data */
          LpPackSignal = LpPIDData->pDcmDspPidPackSigRef;
          switch(LpPIDData->ucDcmDspPidDataUsePort)
          {
            case DCM_OBD_SYNCHCLIENT_FNC:
            case DCM_OBD_SYNCH_CLIENT_SERVER:
                #if((DCM_PID_DATA_SYNCH_CLIENT_SERVER == STD_ON) || \
                  (DCM_PID_DATA_SYNCHCLIENT_FNC == STD_ON))
                LddReturnValue = LpPIDData->pGetPidValFnc
                  (&Dcm_GaaPidSignalData[DCM_ZERO]);
                #endif
              break;

            #if(DCM_PID_DATA_SENDER_RECEIVER == STD_ON)
            case DCM_OBD_SENDER_RECEIVER:
            LucDataType = LpPIDData->ucDcmPIDDataType;
              switch(LucDataType)
              {
                case DCM_DSP_DATA_TYPE_UINT8:
                  #if(DCM_DSP_PID_UINT8 == STD_ON)
                  LddReturnValue =
                  Dcm_GaaPIDUint8Func[LpPIDData->ucReadFunctionIndex].
                    pReadWriteDataUint8Func(&Dcm_GaaPidSignalData[DCM_ZERO]);
                  #endif
                  break;
                case DCM_DSP_DATA_TYPE_UINT16:
                  #if(DCM_DSP_PID_UINT16 == STD_ON)
                  LddReturnValue =
                  Dcm_GaaPIDUint16Func[LpPIDData->ucReadFunctionIndex].
                  pReadWriteDataUint16Func
                  ((uint16*)&Dcm_GaaPidSignalData[DCM_ZERO]);
                  #endif
                  break;
                case DCM_DSP_DATA_TYPE_UINT32:
                  #if(DCM_DSP_PID_UINT32 == STD_ON)
                  LddReturnValue =
                  Dcm_GaaPIDUint32Func[LpPIDData->ucReadFunctionIndex].
                  pReadWriteDataUint32Func
                  ((uint32*)&Dcm_GaaPidSignalData[DCM_ZERO]);
                  #endif
                  break;
                case DCM_DSP_DATA_TYPE_SINT8:
                  #if(DCM_DSP_PID_SINT8 == STD_ON)
                  LddReturnValue =
                  Dcm_GaaPIDSint8Func[LpPIDData->ucReadFunctionIndex].
                    pReadWriteDataSint8Func
                    ((sint8*)&Dcm_GaaPidSignalData[DCM_ZERO]);
                  #endif
                  break;
                case DCM_DSP_DATA_TYPE_SINT16:
                  #if(DCM_DSP_PID_SINT16 == STD_ON)
                  LddReturnValue =
                  Dcm_GaaPIDSint16Func[LpPIDData->ucReadFunctionIndex].
                  pReadWriteDataSint16Func
                  ((sint16*)&Dcm_GaaPidSignalData[DCM_ZERO]);
                  #endif
                  break;
                case DCM_DSP_DATA_TYPE_SINT32:
                  #if(DCM_DSP_PID_SINT32 == STD_ON)
                  LddReturnValue =
                  Dcm_GaaPIDSint32Func[LpPIDData->ucReadFunctionIndex].
                  pReadWriteDataSint32Func
                  ((sint32*)&Dcm_GaaPidSignalData[DCM_ZERO]);
                  #endif
                  break;
                default:
                break;
              }
            break;
            #endif

            default:
            break;
          }
		  
          if(LddReturnValue == E_OK)
          {
            if(LucStartByte != LpPackSignal->ucSignalStartByte)
            {
               LpTxBuffer = &LpTxDataBuffer[LpPackSignal->ucSignalStartByte];
            }
            LddPackSignal.ucShiftBits = LpPackSignal->ucNoOfShiftBits;
            LddPackSignal.ucStartMask = LpPackSignal->ucStartMask;
            LddPackSignal.ucEndMask = LpPackSignal->ucEndMask;
            LddPackSignal.ucSignalTypeorSize = LpPackSignal->ucSignalTypeorSize;
            Dcm_GaaSigWrFuncPtr[LpPackSignal->ucWrFuncIndex].pWrFuncPtr
              (LddPackSignal, LpTxBuffer, Dcm_GaaPidSignalData);
            LucStartByte = LpPackSignal->ucSignalStartByte;
          }
		  
		  /* Increament buffer ptr */
          LpPIDData = &LpPIDData[1u];
        }
      }
    }
  }
  else
  {
    Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
  }
  
  return(LddReturnValue);
}
#endif

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
