/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComM.c                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of ComM APIs                                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.9.6     11-Jan-2021   Jongsun Lim #27580                                 **
** 1.9.5     08-Dec-2020   Jongsun Lim #25703                                 **
** 1.9.4     26-Oct-2020   JS Lim      #26262                                 **
** 1.9.3     11-Aug-2020   JS Lim      #25552, #25554                         **
** 1.9.0     22-Aug-2019   JS Lim      #18922, #19094                         **
** 1.8.1     22-Aug-2019   JS Lim      #18922                                 **
** 1.8.0     23-Oct-2018   JS Lim      #12738, #13653                         **
** 1.7.15    19-Jun-2017   JH Jeong    #10455                                 **
** 1.7.14    19-Jun-2017   JH Jeong    #8337                                  **
** 1.0.7     24-Aug-2015   KT Kim      Justification for Runtime Error :      **
**                                     IDP, OBAI (Improvement #2998)          ** 
** 1.0.6     04-Jul-2013   Daejun Park CR~129, XAR~581 : ComM library         **
**                                     -Change the structure of ComM_Data     **
**                                     for library                            **
** 1.0.4     07-Jun-2013   Daejun Park CR~118, XAR~557 : ComM library         **
**                                     -Add inclusion of header file          **
**                                     ComM_Config.h                          **
**                                     -Convert macro to constant variables   **
**                                     ComM_GucEcuGroupClassification,        **
**                                     ComM_GucTotalChannels,                 **
**                                     ComM_GucTotalUsers,                    **
**                                     ComM_GucTotalPncs,                     **
**                                     ComM_GucTotalSignals,                  **
**                                     ComM_GucPncComMaxLength                **
** 1.0.0     12-Apr-2013   Daejun Park As per SCR ASRBSW403_SCR_408,          **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM.h"                 /* ComM header file */
#include "ComM_Internal.h"        /* ComM Internal functions header file */
#include "ComM_Ram.h"             /* ComM global Ram variables header file */
#include "ComM_Config.h"          /* ComM Config header file */
#if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
#include "Nm.h"                   /* Nm header file */
#endif
#include "SchM_ComM.h"            /* SchM ComM interface API header file */
#if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)
#include "NvM.h"                  /* NvM header file */
#endif
#if ((COMM_PNC_SUPPORT == STD_ON) &&\
  (COMM_PNC_ENABLED == STD_ON))
#include "Com.h"                  /*COM header File */
#endif
#if (COMM_BUSLOAD_DETECTING == STD_ON)
#include "CanIf.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COMM_C_AR_RELEASE_MAJOR_VERSION    4
#define COMM_C_AR_RELEASE_MINOR_VERSION    0
#define COMM_C_AR_RELEASE_REVISION_VERSION 3

/* Software Version Information */
#define COMM_C_SW_MAJOR_VERSION            1
#define COMM_C_SW_MINOR_VERSION            10

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (COMM_AR_RELEASE_MAJOR_VERSION != COMM_C_AR_RELEASE_MAJOR_VERSION)
#error "ComM.c : Mismatch in Specification Major Version"
#endif
#if (COMM_AR_RELEASE_MINOR_VERSION != COMM_C_AR_RELEASE_MINOR_VERSION)
#error "ComM.c : Mismatch in Specification Minor Version"
#endif
#if (COMM_AR_RELEASE_REVISION_VERSION != COMM_C_AR_RELEASE_REVISION_VERSION)
#error "ComM.c : Mismatch in Specification Revision Version"
#endif
#if (COMM_SW_MAJOR_VERSION != COMM_C_SW_MAJOR_VERSION)
#error "ComM.c : Mismatch in Software Major Version"
#endif
#if (COMM_SW_MINOR_VERSION != COMM_C_SW_MINOR_VERSION)
#error "ComM.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_Init                                           **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service initializes the AUTOSAR Communication  **
**                      : Manager Module                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GblInit, ComM_GaaChannels, ComM_GstData,       **
**                        ComM_GaaSubPNCMode, ComM_GaaChannelInhibition       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        NvM_GetErrorStatus()                                **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_Init(void)
{
  #if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)

  /* This variable is used to store the return value of NvM status */
  NvM_RequestResultType LddCondition = NVM_REQ_NOT_OK;
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  /*Variable to assure the sequential storage of inhibition value*/
  uint8 LucChannelInhibitionProtect;
  #endif
  #endif
  #if (((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
        (COMM_MODE_LIMITATION_ENABLED == STD_ON)) ||\
       (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) &&\
        ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
        (COMM_ETHNETWORK_PRESENT == STD_ON))))


  /* Channel, User, PNC Index */
  uint8 LucIndex;
  #endif
  #if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  /*Variable to assure the sequential storage of inhibition value*/
  LucChannelInhibitionProtect = COMM_ZERO;
  #endif
  #endif

  /* If the NvM block descriptors configured are same across channel and general
   *   containers */
  #if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)

  /* Check the Status of ComM Block */
  (void)NvM_GetErrorStatus(COMM_NVRAM_BLOCK_ID, &LddCondition);

  /* If request is not accepted successfully */
  if (LddCondition != NVM_REQ_OK)
  {
    #if (COMM_MODE_LIMITATION_ENABLED == STD_ON)

    /* Load default Data for Inhibit condition */
    ComM_GstData.usComMFullComInhibitCounter = COMM_ZERO;
    #endif

    /* Set default value of ECU group classification */
    ComM_GstData.ddComMEcuInhibition = ComM_GucEcuGroupClassification;

    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))

    /* Load value of channel inhibition and Full Com Request Notification */
    for (LucIndex = COMM_ZERO; LucIndex < ComM_GucTotalChannels; LucIndex++)
    {
      /*Stores all the channel inhibition in global array*/
      ComM_GaaChannelInhibition[LucIndex] =
        ComM_GaaChannels[LucIndex].ucComMInhibition;

      /* Default value of channel specific Notification: No Need to Store */
    }

    #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
            *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */
  } /* End of if (LddCondition != NVM_REQ_OK) */
  else /*If NVM_REQ_OK */
  {
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))

    for (LucIndex = COMM_ZERO; LucIndex < ComM_GucTotalChannels; LucIndex++)
    {
      /* channel Inhibition: For NVM as well as NVM Channel storage False */
      /* polyspace<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> condition will be executed based on the configured values */
      /* polyspace:begin<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
      if (ComM_GaaChannels[LucIndex].blNoWakeUpNvmStorage == COMM_TRUE)
      {
        ComM_GaaChannelInhibition[LucIndex] =
        ComM_GaaNvmChannelInhibition[LucChannelInhibitionProtect];
        LucChannelInhibitionProtect++;
      }
      else
      {
        ComM_GaaChannelInhibition[LucIndex] =
          ComM_GaaChannels[LucIndex].ucComMInhibition;
      }
      /* polyspace:end<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
    }

    #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
            *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */
  } /* End of else */
  #else /* End of if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON) */
  #if (COMM_MODE_LIMITATION_ENABLED == STD_ON)

  /* Load default Data for Inhibit condition */
  ComM_GstData.usComMFullComInhibitCounter = COMM_ZERO;
  #endif

  /* Set default value of ECU group classification */
  ComM_GstData.ddComMEcuInhibition = ComM_GucEcuGroupClassification;

  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  /* Default value of channel specific inhibition */
  for (LucIndex = COMM_ZERO; LucIndex < ComM_GucTotalChannels; LucIndex++)
  {
    ComM_GaaChannelInhibition[LucIndex] =
      ComM_GaaChannels[LucIndex].ucComMInhibition;
  }

  #endif

  /* Default value of channel Notification : No Need To Store*/
  #endif /* Block descriptors */

  #if((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
      (COMM_ETHNETWORK_PRESENT == STD_ON))
  for(LucIndex = COMM_ZERO; LucIndex < ComM_GucTotalPncs; LucIndex++)
  {
    /* Initialize Sub PNC modes :PNC_NO_COMMUNICATION = 3*/
    ComM_GaaSubPNCMode[LucIndex] = PNC_NO_COMMUNICATION;
  }

  #endif
  #endif

  /* Set the ComM Status to Initialized */
  ComM_GblInit = COMM_INIT;
} /* End of ComM_Init */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_GetVersionInfo                                 **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This service returns the published information      **
**                        including Major, Minor and Patch version            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(),                                  **
*******************************************************************************/
#if (COMM_VERSION_INFO_API == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect:Justified > Its boundary is pre-defined           */
FUNC(void, COMM_CODE) ComM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
    COMM_APPL_DATA) Versioninfo)
{
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if versioninfo pointer is equal to Null */
  if (Versioninfo == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_GETVERSIONINFO_SID, COMM_E_WRONG_PARAMETERS);
  }
  else
  #endif
  {
    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not NULL and validated  */ 
    /* Copy the vendor Id */
    Versioninfo->vendorID = COMM_VENDOR_ID;

    /* Copy the module Id */
    Versioninfo->moduleID = COMM_MODULE_ID;

    /* Copy Software Major Version */
    Versioninfo->sw_major_version = COMM_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    Versioninfo->sw_minor_version = COMM_SW_MINOR_VERSION;

    /* Copy Software Patch Version */
    Versioninfo->sw_patch_version = COMM_SW_PATCH_VERSION;
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not NULL and validated  */ 
  }
} /* End of ComM_GetVersionInfo*/
/* polyspace:end<RTE: IDP : Not a defect:Justified > Its boundary is pre-defined           */
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (COMM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_GetStatus                                      **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service returns the initialization status of   **
**                      : AUTOSAR Communication Manager Module                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Status                                              **
**                                                                            **
** Return parameter     : E_OK, E_NOT_OK                                      **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GblInit                                        **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<RTE: IDP : Not a defect:Justified > Its boundary is pre-defined           */

FUNC(Std_ReturnType, COMM_CODE) ComM_GetStatus(P2VAR(ComM_InitStatusType,
    AUTOMATIC, COMM_APPL_DATA) Status)
{
  /* This Variable is used to store return value */
  Std_ReturnType LddReturnValue;

  /* Initialize the return variable to E_OK */
  LddReturnValue = E_OK;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if passed status is equal to Null */
  if (Status == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, COMM_GETSTATUS_SID,
      COMM_E_WRONG_PARAMETERS);
    LddReturnValue = E_NOT_OK;
  } /* End of if (Status == NULL_PTR) */

  /* Check, if no development error occurred */
  if (LddReturnValue == E_OK)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /*   MISRA Rule         : 1.2
     *   Message            : Dereferencing pointer value that is apparently
     *                        NULL.
     *   Reason             : The pointer will be assigned with valid address.
     *   Verification       : However, part of the code is verified manually
     *                        and it is not having any impact.
     */
    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not NULL and validated  */
    /* Load the variable with the ComM initialization status */
    *Status = (ComM_InitStatusType)ComM_GblInit;
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not NULL and validated  */    
  } /* End of if (LddReturnValue == E_OK) */
  return (LddReturnValue);
} /* End of ComM_GetStatus */
/* polyspace:end<RTE: IDP : Not a defect:Justified > Its boundary is pre-defined           */
#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_GetState                                       **
**                                                                            **
** Service ID           : 0x34                                                **
**                                                                            **
** Description          : This function returns current state, including      **
**                        sub-state, of the ComM state machine                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : State                                               **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK or COMM_E_UNINIT                   **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaChannelMapArray[], ComM_GaaSubComMode[]     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_ChannelDETCheck()           **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE)
ComM_GetState(NetworkHandleType Channel, P2VAR(ComM_StateType, AUTOMATIC,
    COMM_APPL_DATA) State)
{
  /* This variable is to store the return values */
  Std_ReturnType LddReturnValue;

  /* Variable to store User Index */
  NetworkHandleType LddIndex;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if channel is valid and ComM is initialized */
  LddReturnValue = ComM_ChannelDETCheck(Channel, COMM_GETSTATE_SID);

  /* Check, if ComMode pointer is equal to Null */
  if (State == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, COMM_GETSTATE_SID,
      COMM_E_WRONG_PARAMETERS);
    LddReturnValue = E_NOT_OK;
  } /* End of if (State == NULL_PTR) */

  /* Check, if no development error occurred */
  if (LddReturnValue == E_OK)
  #endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET and pointer is not NULL */
    /* Check whether the configured are in sequence */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* If not in sequence, load from Mapping array */
    LddIndex = ComM_GaaChannelMapArray[Channel];
    #else

    /*If they are in sequence, use directly */
    LddIndex = Channel;
    #endif

    *State = ComM_GaaSubComMode[LddIndex];
    /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:end<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET and pointer is not NULL */

    /* Set return variable to E_OK */
    LddReturnValue = E_OK;

  } /* End of if (LddReturnValue == E_OK) */
  /* Return E_OK or E_NOT_OK or COMM_E_UNINIT */
  return (LddReturnValue);
} /* End of ComM_GetState */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"


#if (COMM_DIRECT_CHANNEL == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_ResetRequestedChannel(NetworkHandleType Channel)
{
  uint8 LucNoOfChannels;
  uint8 LucChannelIndex;
  uint8 LucIndex;  
  NetworkHandleType LddChannelIndex;
   
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if the module is initialized or not */
  if (ComM_GblInit == COMM_UNINIT)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, COMM_DEINIT_SID,
      COMM_E_NOT_INITED);
  }
  else
  #endif
  {
    /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET  */    
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
    if(Channel <= COMM_MAX_CHANNELID)
    {
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      /* Get the channel id from the mapping array */
      LddChannelIndex = ComM_GaaChannelMapArray[Channel];
      #else
      /* Channel Id is updated into local variable */
      LddChannelIndex = Channel;
      #endif
  
      /* Clear current communication mode */
      ComM_GaaCurComMode[LddChannelIndex] = COMM_NO_COMMUNICATION;
      /* Clear requests for communication modes */
      ComM_GaaReqedComModeCnt[LddChannelIndex] = COMM_ZERO;
      /* Clear sub communication mode */
      ComM_GaaSubComMode[LddChannelIndex] = COMM_NO_COM_NO_PENDING_REQUEST;
      /* Clear if any request were done for NM */
      ComM_GaaNmRequested[LddChannelIndex] = COMM_ZERO;
      /* Clear if any request were done for SM */
      ComM_GaaModeRequested[LddChannelIndex] = COMM_FALSE;
      /* Load default state for user */
      LucIndex = ComM_GucTotalUsers;
      while (LucIndex != COMM_ZERO)
      {
        LucIndex--;
        LucNoOfChannels = ComM_GaaUsers[LucIndex].ucNoOfDirectChannels;
        /* Clear all user requests */
        LucChannelIndex = ComM_GaaUsers[LucIndex].ucDirectChannelIndex;
        while (LucNoOfChannels != COMM_ZERO)
        {
          /* Get the Channel index from the Channel Index Array */          
          if(LddChannelIndex == ComM_GaaChnInxArr[LucChannelIndex])
          {
            ComM_GaaRequestedComMode[LucIndex] = COMM_NO_COMMUNICATION;
          }
          LucNoOfChannels--;
          LucChannelIndex++;
        }
      }
    }
    /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */    
    /* polyspace:end<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET  */
  }
}
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : ComM_DeInit                                         **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service returns the De-Initialization the      **
**                      : AUTOSAR Communication Manager Module                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GblInit, ComM_GucChannelsFullComMode           **
**                        ComM_GblWakeUp, ComM_GaaNmIndication, ComM_GstData, **
**                        ComM_GaaRequestedComMode[], ComM_GaaCurComMode[],   **
**                        ComM_GaaReqedComModeCnt[], ComM_GaaChannels[]       **
**                        ComM_GaaSubComMode, ComM_GaaModeRequested,          **
**                        ComM_GaaRequestedPNCMode, ComM_GaaPncRxEIRASignal   **
**                        ComM_GaaPncRxERAn, ComM_GaaPncRxEIRA,               **
**                        ComM_GaaPncRxERASignal                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_DeInit(void)
{
  #if((COMM_PNC_SUPPORT == STD_ON)&& (COMM_PNC_ENABLED == STD_ON))
  #if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
      (COMM_ETHNETWORK_PRESENT == STD_ON))
  
  /* Com Signal index Instance Index */
  uint16 LusIndex;

  /* Variable to store Channel*/
  uint8 LucChannel;
  #endif
  #endif
  #if ((COMM_NVM_BLOCK_DESCRIPTOR == STD_ON) &&\
  ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON)))
  uint8 LucChannelInhibitionProtect = COMM_ZERO;
  #endif
  uint8 LucIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if the module is initialized or not */
  if (ComM_GblInit == COMM_UNINIT)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, COMM_DEINIT_SID,
      COMM_E_NOT_INITED);
  }
  else
  #endif
  {
    /* check, if no channels are in Full Communication mode */
    if (ComM_GucChannelsFullComMode == COMM_ZERO)
    {
      #if ((COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)\
      && ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
      (COMM_MODE_LIMITATION_ENABLED == STD_ON)))

      for (LucIndex = COMM_ZERO; LucIndex < ComM_GucTotalChannels; LucIndex++)
      {
        /*Stores only the channel inhibition whose NVM Storage is TRUE*/
        if (ComM_GaaChannels[LucIndex].blNoWakeUpNvmStorage == COMM_TRUE)
        {
            ComM_GaaNvmChannelInhibition[LucChannelInhibitionProtect] =
            ComM_GaaChannelInhibition[LucIndex];
          LucChannelInhibitionProtect++;
        }
      }
      #endif /* End of if ((COMM_NVM_BLOCK_DESCRIPTOR == STD_ON) &&
              *((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
              *(COMM_MODE_LIMITATION_ENABLED == STD_ON))) */
      /*************************************************************************
      ** Design Taken: In Module COMM_UNINIT Reset the global variables to ZERO
      *************************************************************************/

      /* Load default states into global variables*/
      for (LucIndex = COMM_ZERO; LucIndex < ComM_GucTotalChannels; LucIndex++)
      {
        /* Clear all current communication modes */
        ComM_GaaCurComMode[LucIndex] = COMM_NO_COMMUNICATION;

        /* Clear all requests for communication modes */
        ComM_GaaReqedComModeCnt[LucIndex] = COMM_ZERO;

        /* Clear all sub communication modes */
        ComM_GaaSubComMode[LucIndex] = COMM_NO_COM_NO_PENDING_REQUEST;

        /* Clear all Nm indications */
        ComM_GaaNmIndication[LucIndex] = COMM_ZERO;

        /* Clear if any requests were done for SM */
        ComM_GaaModeRequested[LucIndex] = COMM_FALSE;
      }

      /* Load default state for user */
      for (LucIndex = COMM_ZERO; LucIndex < ComM_GucTotalUsers; LucIndex++)
      {
        /* Clear all user requests */
        ComM_GaaRequestedComMode[LucIndex] = COMM_NO_COMMUNICATION;
      }

      #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))

      /* Load default state for PNC */
      for (LucIndex = COMM_ZERO; LucIndex < ComM_GucTotalPncs; LucIndex++)
      {
        ComM_GaaRequestedPNCMode[LucIndex] = PNC_USER_NO_COMM;


        /*Reset ERA Information*/
        #if (COMM_PNC_GW_ENABLED == STD_ON)
        ComM_GaaPncRxERAn[LucIndex] = COMM_FALSE;
        #endif

        /*Reset EIRA Information*/
        ComM_GaaPncRxEIRA[LucIndex] = COMM_FALSE;

        for (LusIndex = COMM_ZERO; LusIndex < ComM_GucTotalSignals; LusIndex++)
        {
          /*Reset ERA and EIRA Com Signal Information*/
          #if (COMM_PNC_GW_ENABLED == STD_ON)
          ComM_GaaPncRxERASignal[((uint16)LucIndex * (uint16)ComM_GucTotalSignals) + LusIndex] = COMM_FALSE;
          #endif
          ComM_GaaPncRxEIRASignal[((uint16)LucIndex * (uint16)ComM_GucTotalSignals) + LusIndex] = COMM_FALSE;
        }
      }
      for (LucChannel = COMM_ZERO; LucChannel < ComM_GucTotalChannels; LucChannel++)
      {
         for (LucIndex = COMM_ZERO; LucIndex < ComM_GucPncComMaxLength; LucIndex++)
         {
           ComM_GaaSignalTx[LucChannel][LucIndex] = COMM_ZERO;
         }
      }
      #endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
              *STD_ON)) */

      /* Clear global wake up indication of all channels */
      ComM_GblWakeUp = COMM_FALSE;

      /************************************************************************/

      /* Set the Initialization status as COMM_UNINIT */
      ComM_GblInit = COMM_UNINIT;
    } /* End of if (ComM_GucChannelsFullComMode == COMM_ZERO) */
  }
} /* End of ComM_DeInit */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_ReadInhibitCounter                             **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : This service returns the amount of rejected "FULL   **
**                        COMMUNICATION" user requests                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : CounterValue                                        **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK or COMM_E_UNINIT                   **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GblInit, ComM_GstData                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
*******************************************************************************/
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE)
ComM_ReadInhibitCounter(P2VAR(uint16, AUTOMATIC, COMM_APPL_DATA) CounterValue)
{
  /* This variable is to store the return values */
  Std_ReturnType LddReturnValue;

  /* Initialize the return variable to E_OK */
  LddReturnValue = E_OK;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if the module is initialized or not */
  if (ComM_GblInit == COMM_UNINIT)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_READINHIBITCOUNTER_SID, COMM_E_NOT_INITED);
    LddReturnValue = COMM_E_UNINIT;
  }

  /* Check, if CounterValue pointer is equal to Null */
  if (CounterValue == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_READINHIBITCOUNTER_SID, COMM_E_WRONG_PARAMETERS);
    LddReturnValue = E_NOT_OK;
  }

  /* Check, if no development error occurred */
  if (LddReturnValue == E_OK)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Load Counter Pointer with the Inhibit Counter Value */
    /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> pointer is not NULL and valid */
    *CounterValue = ComM_GstData.usComMFullComInhibitCounter;
  }
  /* Return E_OK or E_NOT_OK or COMM_E_UNINIT */
  return (LddReturnValue);
} /* End of ComM_ReadInhibitCounter */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (COMM_MODE_LIMITATION_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_ResetInhibitCounter                            **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : This service resets the "Inhibited Full             **
**                        Communication Request Counter"                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK or COMM_E_UNINIT                               **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GblInit, ComM_GstData                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
*******************************************************************************/
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE) ComM_ResetInhibitCounter(void)
{
  /* This variable is to store the return values */
  Std_ReturnType LddReturnValue;

  /* Initialize the return variable to E_OK */
  LddReturnValue = E_OK;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Report to DET, if the module is initialized or not */
  if (ComM_GblInit == COMM_UNINIT)
  {
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_RESETINHIBITCOUNTER_SID, COMM_E_NOT_INITED);
    LddReturnValue = COMM_E_UNINIT;
  }
  else
  #endif /*#if(COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    ComM_GstData.usComMFullComInhibitCounter = COMM_ZERO;
  }
  /* Return E_OK or COMM_E_UNINIT */
  return (LddReturnValue);
} /* End of ComM_ResetInhibitCounter */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (COMM_MODE_LIMITATION_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_SetECUGroupClassification                      **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : This service changes the ECU Group Classification   **
**                        status                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Status                                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK or COMM_E_UNINIT                   **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GblInit, ComM_GstData                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE)
ComM_SetECUGroupClassification(ComM_InhibitionStatusType Status)
{
  /* This variable is to store the return values */
  Std_ReturnType LddReturnValue;

  /* Initialize the return variable to E_OK */
  LddReturnValue = E_OK;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if the module is initialized or not */
  if (ComM_GblInit == COMM_UNINIT)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_SETECUGROUPCLASSIFICATION_SID, COMM_E_NOT_INITED);
    LddReturnValue = COMM_E_UNINIT;
  }

  /* Check whether Status passed is valid or not */
  if (Status > COMM_INHIBITION_RANGE)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_SETECUGROUPCLASSIFICATION_SID, COMM_E_WRONG_PARAMETERS);
    LddReturnValue = E_NOT_OK;
  }

  /* Check, if no development error occurred */
  if (LddReturnValue == E_OK)
  #endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    ComM_GstData.ddComMEcuInhibition = Status;
  }
  /* Return E_OK or E_NOT_OK or COMM_E_UNINIT */
  return (LddReturnValue);
} /* End of ComM_SetECUGroupClassification*/

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_GetRequestedComMode                            **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This function returns the currently requested       **
**                        Communication mode of the corresponding user        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : User                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : ComMode                                             **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK or COMM_E_UNINIT                   **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaUserMapArray, ComM_GaaRequestedComMode      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_UserDETCheck(),             **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE)
ComM_GetRequestedComMode(ComM_UserHandleType User, P2VAR(ComM_ModeType,
    AUTOMATIC, COMM_APPL_DATA) ComMode)
{
  /* This variable is to store the return values */
  Std_ReturnType LddReturnValue;

  /* Variable to store User Index */
  uint8 LucUserIndex;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  LddReturnValue = ComM_UserDETCheck(User, COMM_GETREQUESTEDCOMMODE_SID);

  /* Check, if ComMode pointer is equal to Null */
  if (ComMode == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_GETREQUESTEDCOMMODE_SID, COMM_E_WRONG_PARAMETERS);
    LddReturnValue = E_NOT_OK;
  }

  /* Check, if no development error occurred */
  if (LddReturnValue == E_OK)
  #endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET and pointer is not NULL */
    #if (COMM_USER_SEQUENTIAL == STD_OFF)
    LucUserIndex = ComM_GaaUserMapArray[User];
    #else
    LucUserIndex = User;
    #endif


    /* Load the requested commode into the pointer variable */ 
    *ComMode = ComM_GaaRequestedComMode[LucUserIndex];
    /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:end<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET and pointer is not NULL */

    /* Set the return variable to E_OK */
    LddReturnValue = E_OK;
  }
  /* Return E_OK or E_NOT_OK or COMM_E_UNINIT*/
  return (LddReturnValue);
} /* End of ComM_GetRequestedComMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_GetInhibitionStatus                            **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : Returns the Inhibition Status of ComM channel       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Status                                              **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK or COMM_E_UNINIT                   **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaChannelMapArray, ComM_GaaChannelInhibition  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_ChannelDETCheck()           **
*******************************************************************************/
#if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE)
ComM_GetInhibitionStatus(NetworkHandleType Channel, P2VAR(
    ComM_InhibitionStatusType, AUTOMATIC, COMM_APPL_DATA) Status)
{
  /* Variable to store the Return values of functions */
  Std_ReturnType LddReturnValue;

  /* Variable to store the channel Index */
  NetworkHandleType LddIndex;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  LddReturnValue = ComM_ChannelDETCheck(Channel, COMM_GETINHIBITIONSTATUS_SID);

  /* Report to DET, if passed status is equal to Null */
  if (Status == NULL_PTR)
  {
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_GETINHIBITIONSTATUS_SID, COMM_E_WRONG_PARAMETERS);
    LddReturnValue = E_NOT_OK;
  }

  /* Check, if no development error occurred */
  if (LddReturnValue == E_OK)
  #endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET */
    LddIndex = ComM_GaaChannelMapArray[Channel];
    #else

    /* Load Channel index variable with channel */
    LddIndex = Channel;
    #endif

    /* Load the pointer with Inhibition status of the channel */
    /* polyspace<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET and pointer is not NULL */
    *Status = ComM_GaaChannelInhibition[LddIndex];

  /* Set the return variable to E_OK */
    LddReturnValue = E_OK;
  }
  /* Return E_OK or E_NOT_OK or COMM_E_UNINIT*/
  return (LddReturnValue);
} /* End of ComM_GetInhibitionStatus*/

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
        *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_GetCurrentComMode                              **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : Requests the Current communication mode of the user **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : User                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : ComMode                                             **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK or COMM_E_UNINIT                   **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaUserMapArray[], ComM_GaaUsers[]             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_GetCurComModeDirectChnl(),  **
**                        ComM_GetCurComModePNC, ComM_UserDETCheck()          **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE)
ComM_GetCurrentComMode(ComM_UserHandleType User, P2VAR(ComM_ModeType, AUTOMATIC,
    COMM_APPL_DATA) ComMode)
{
  /* Function Return Variable */
  Std_ReturnType LddReturnValue;

  /* Lowest mode requested by user (No-Slient-Full)*/
  ComM_ModeType LddLowestMode;
  #if (COMM_DIRECT_CHANNEL == STD_ON)

  /* variable to store the Total No. of Channels of the User/PNC */
  uint8 LucNoOfChannels;
  #endif
  #if (COMM_DIRECT_CHANNEL == STD_ON)

  /* Index to the channel Id's in the ChannelIndex Array */
  uint8 LucUserChannelIndex;
  #endif

  /* Variable to store the user Index */
  uint8 LucIndex;

  /* Init with highest mode (No-Slient-Full)*/
  LddLowestMode = COMM_FULL_COMMUNICATION;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the user id is valid and if ComM is initialized */
  LddReturnValue = ComM_UserDETCheck(User, COMM_GETCURRENTCOMMODE_SID);

  /* Check, if passed Communication mode is equal to Null */
  if (ComMode == NULL_PTR)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_GETCURRENTCOMMODE_SID, COMM_E_WRONG_PARAMETERS);
    LddReturnValue = E_NOT_OK;
  }

  /* Check, if no development error occurred */
  if (LddReturnValue == E_OK)
  #endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET and pointer is not NULL */
    /* User Index */
    #if (COMM_USER_SEQUENTIAL == STD_OFF)
    LucIndex = ComM_GaaUserMapArray[User];
    #else
    LucIndex = User;
    #endif

    #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
    #if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
         (COMM_ETHNETWORK_PRESENT == STD_ON))
    LddReturnValue = ComM_GetCurComModePNC(LucIndex, &LddLowestMode);

    /* The lowest mode may have been updated in ComM_GetCurComModePNC() */
    if ((LddLowestMode != COMM_NO_COMMUNICATION) &&
    (LddReturnValue != E_NOT_OK))
    #endif
    #endif
    {      
      #if (COMM_DIRECT_CHANNEL == STD_ON)
      /* Get the No of channels of the User */
      LucNoOfChannels = ComM_GaaUsers[LucIndex].ucNoOfDirectChannels;

      /* Channel Index */
      LucUserChannelIndex = ComM_GaaUsers[LucIndex].ucDirectChannelIndex;

      LddReturnValue = ComM_GetCurComModeDirectChnl(LucUserChannelIndex,
        LucNoOfChannels, &LddLowestMode);
      #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

    }/* End of if ((LddLowestMode != COMM_NO_COMMUNICATION) && 
                                                (LddReturnValue != E_NOT_OK)) */
    /* Update the Comm Mode   */
    *ComMode = LddLowestMode;

    /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:end<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET and pointer is not NULL */

  }
  
  return (LddReturnValue);
} /* End of ComM_GetCurrentComMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_PreventWakeUp                                  **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This service Changes the inhibition status          **
**                      : COMM_NO_WAKEUP for the corresponding channel.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel, Status                                     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK or COMM_E_UNINIT                   **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaChannelMapArray, ComM_GaaChannelInhibition, **
**                        ComM_GaaCurComMode                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck()                              **
*******************************************************************************/
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE)
ComM_PreventWakeUp(NetworkHandleType Channel, boolean Status)
{
  /* The variable LddStdRetVal is used for return values */
  Std_ReturnType LddStdRetVal;

  /* The variable Lucindex is used as array index */
  NetworkHandleType LddIndex;

  boolean LblFlag;

  LblFlag = COMM_FALSE;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  LddStdRetVal = ComM_ChannelDETCheck(Channel, COMM_PREVENTWAKEUP_SID);

  /* Check, if no development error occurred */
  if (LddStdRetVal == E_OK)
  #endif
  {

    /* Set the StdRetVal to E_OK */
    LddStdRetVal = E_OK;

    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    /* The index variable is updated with Channel */
    /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET */
    LddIndex = ComM_GaaChannelMapArray[Channel];
    #else
    LddIndex = Channel;
    #endif

    /* If the current mode is not No or Silent then set wake up inhibition */
    /* polyspace<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
    if ((ComM_GaaCurComMode[LddIndex] == COMM_NO_COMMUNICATION) ||
        (ComM_GaaCurComMode[LddIndex] == COMM_SILENT_COMMUNICATION))
    {
      if((ComM_GstData.ddComMEcuInhibition & (uint8)COMM_ONE) == (uint8)COMM_ONE)
      {
        /* Updating status array bit 0 for WAKEUP Status */
        if (Status == COMM_TRUE)
        {
          ComM_GaaChannelInhibition[LddIndex] =
            (ComM_GaaChannelInhibition[LddIndex] | (uint8)COMM_PREVENTWAKEUP_MASK_SET);
        }
        else
        {
          /* Updating status array bit 0 for WAKEUP Status */
          ComM_GaaChannelInhibition[LddIndex] =
            (ComM_GaaChannelInhibition[LddIndex] & COMM_PREVENTWAKEUP_MASK_CLR);
        }
      }
      else
      {
        LblFlag = COMM_TRUE;
      }
    } /* End of if ((ComM_GaaCurComMode[LddIndex] == COMM_NO_COMMUNICATION) ||
       **/
    else
    {
      LblFlag = COMM_TRUE;
    }
    if(LblFlag == COMM_TRUE)
    {
      LddStdRetVal = E_NOT_OK;
    }
  }
  /* Return E_OK or E_NOT_OK or COMM_E_UNINIT */
  return (LddStdRetVal);
} /* End of ComM_PreventWakeUp */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_LimitChannelToNoComMode                        **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : This service Changes the inhibition status          **
**                      : COMM_NO_WAKEUP for the corresponding channel.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel, Status                                     **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK or COMM_E_UNINIT                   **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaChannelMapArray, ComM_GaaChannelInhibition  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck()                              **
*******************************************************************************/
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE) ComM_LimitChannelToNoComMode(NetworkHandleType
  Channel, boolean Status)
{
  /* The variable LddStdRetVal is used for return values */
  Std_ReturnType LddStdRetVal;

  /* The variable LddIndex is used as array index */
  NetworkHandleType LddIndex;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  LddStdRetVal = ComM_ChannelDETCheck(Channel,
    COMM_LIMITCHANNELTONOCOMMODE_SID);

  /* Check, if no development error occurred */
  if (LddStdRetVal == E_OK)
  #endif
  {
    /* Set the StdRetVal to E_OK */
    LddStdRetVal = E_OK;    
    /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET and pointer is not NULL */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    LddIndex = ComM_GaaChannelMapArray[Channel];
    #else

    /* The index variable is updated with Channel*/
    LddIndex = Channel;
    #endif /* (COMM_CHANNEL_SEQUENTIAL == STD_OFF) */
    if((ComM_GstData.ddComMEcuInhibition & (uint8)COMM_TWO) == (uint8)COMM_TWO)
    {
      if (Status == COMM_TRUE)
      {
        /* Updating status array bit 1 for Limit channel to No comm inhibition*/
        ComM_GaaChannelInhibition[LddIndex] =
          (ComM_GaaChannelInhibition[LddIndex] |
           (uint8)COMM_LIMITCHANNELTONOCOMM_MASK_SET);
      }
      else
      {
        /* Updating status array bit 1 for Limit channel to No comm inhibition*/
        ComM_GaaChannelInhibition[LddIndex] =
          (ComM_GaaChannelInhibition[LddIndex] &
           COMM_LIMITCHANNELTONOCOMM_MASK_CLR);
      }
    }
    else
    {
      LddStdRetVal = E_NOT_OK;
    }
    /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET and pointer is not NULL */
    /* polyspace:end<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET and pointer is not NULL */
  }
  /* Return E_OK or E_NOT_OK or COMM_E_UNINIT */
  return (LddStdRetVal);
} /* End of ComM_LimitChannelToNoComMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (COMM_MODE_LIMITATION_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_LimitECUToNoComMode                            **
**                                                                            **
** Service ID           : 0x0c                                                **
**                                                                            **
** Description          : This service Changes the inhibition status to       **
**                      : COMM_NO_COM                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Status                                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK or COMM_E_UNINIT                   **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GblInit, ComM_GblLimitEcuToNoCom               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE) ComM_LimitECUToNoComMode(boolean Status)
{
  /* The variable LddStdRetVal is used for return values */
  Std_ReturnType LddStdRetVal;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Report to DET, Check whether the module is initialized or not */
  if (ComM_GblInit == COMM_UNINIT)
  {
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_LIMITECUTONOCOMMODE_SID, COMM_E_NOT_INITED);
    LddStdRetVal = COMM_E_UNINIT;
  }
  else
  #endif
  {
    /* Set the StdRetVal to E_OK */
    LddStdRetVal = E_OK;

    /* Update status value into global variable */
    ComM_GblLimitEcuToNoCom = Status;
  }
  /* Return E_OK or COMM_E_UNINIT */
  return (LddStdRetVal);
} /* End of ComM_LimitECUToNoComMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (COMM_MODE_LIMITATION_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_RequestComMode                                 **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : Requesting of Communication mode by a user          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : User, ComMode                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK or E_NOT_OK or COMM_E_UNINIT or                **
**                        COMM_E_MODE_LIMITATION                              **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaUserMapArray                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_RequestComModeDirectChnl(), **
**                        ComM_RequestComModePNC(), ComM_UserDETCheck()       **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComMode(ComM_UserHandleType User,
  ComM_ModeType ComMode)
{
  /* Index to the user Index */
  uint8 LucUserIndex;

  /* Function Return Variable */
  Std_ReturnType LddStdRetVal;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  LddStdRetVal = ComM_UserDETCheck(User, COMM_REQUESTCOMMODE_SID);

  /* Check, if no development error occurred */
  if (LddStdRetVal == E_OK)
  #endif
  {
    #if (COMM_DEV_ERROR_DETECT == STD_ON)

    /* If the requested mode is Silent then report to Det */
    if (ComMode == COMM_SILENT_COMMUNICATION)
    {
      (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
        COMM_REQUESTCOMMODE_SID, COMM_E_WRONG_PARAMETERS);
      LddStdRetVal = E_NOT_OK;
    }
    else
    #endif
    {      
      #if (COMM_USER_SEQUENTIAL == STD_OFF)
      /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET */
      LucUserIndex = ComM_GaaUserMapArray[User];
      #else /* if COMM_USER_SEQUENTIAL == OFF */
      /* Load the user in user index */
      LucUserIndex = User;
      #endif

      #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
      #if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
           (COMM_ETHNETWORK_PRESENT == STD_ON))
      LddStdRetVal = ComM_RequestComModePNC(LucUserIndex, ComMode);
      #endif
      #endif

      #if (COMM_DIRECT_CHANNEL == STD_ON)
      #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
      #if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
           (COMM_ETHNETWORK_PRESENT == STD_ON))
      /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
      /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
      if (LddStdRetVal == E_OK)
      #endif
      #endif
      {
        LddStdRetVal = ComM_RequestComModeDirectChnl(LucUserIndex, ComMode);
      }
      #endif /*(COMM_DIRECT_CHANNELS == STD_ON)*/
    }
  }
  return (LddStdRetVal);
}  /* End of ComM_RequestComMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_GetChannelBusLoad                              **
**                                                                            **
** Service ID           : 0x37                                                **
**                                                                            **
** Description          : This service provide Tx/Rx Message Counts of Channel**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : BusLoad                                             **
**                                                                            **
** Return parameter     : E_OK, E_NOT_OK                                      **
**                                                                            **
** Preconditions        : The Communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaChannelCtrlMapping                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError()                                   **
**                        CanIf_ReadBusMsgCount()                             **
*******************************************************************************/
#if (COMM_BUSLOAD_DETECTING == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
/* polyspace +2 MISRA-C3:8.5 [Not a defect:Justify with annotations] "No Impact of this rule violation" */
/* polyspace +1 MISRA-C3:8.4 [Not a defect:Justify with annotations] "No Impact of this rule violation" */
FUNC(Std_ReturnType, COMM_CODE) ComM_GetChannelBusLoad (VAR(NetworkHandleType, COMM_VAR_POWER_ON_INIT) Channel, P2VAR(ComM_BusMsgType, AUTOMATIC, COMM_APPL_DATA) BusLoad)
{
  /* This Variable is used to store return value */
  Std_ReturnType LddReturnValue;

  /* Initialize the return variable to E_OK */
  LddReturnValue = E_OK;

  if(Channel < COMM_TOTAL_CHANNELS)
  {
    #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if passed status is equal to Null */
  /* polyspace<DEFECT:DEAD_CODE::Not a defect Justify with annotations> condition will be executed based on the configured values */
  /* polyspace:begin<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
  if (ComM_GaaChannelCtrlMapping[Channel] == COMM_NOT_USED_CHANNEL_ID)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, COMM_GETCHANNELBUSLOAD_SID,
      COMM_E_WRONG_CHANNEL);
    LddReturnValue = E_NOT_OK;
  } /* End of if (Status == NULL_PTR) */

    /* Check, if no development error occurred */
    /* polyspace<DEFECT:USELESS_IF::Not a defect Justify with annotations> condition will be executed based on the configured values */
    /* polyspace:begin<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
    if (LddReturnValue == E_OK)
    #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
    {     
      /* polyspace<DEFECT:PTR_CAST::Not a defect Justify with annotations> Pointer is not NULL and validated */
      /* polyspace +1 MISRA-C3:11.3 [Not a defect:Justify with annotations] "No Impact of this rule violation" */
      (void)CanIf_ReadBusMsgCount(ComM_GaaChannelCtrlMapping[Channel], BusLoad); 
    } /* End of if (LddReturnValue == E_OK) */
  }
  else
  {
    LddReturnValue = E_NOT_OK;
  }
  
  return (LddReturnValue);
} /* End of ComM_GetStatus */
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

