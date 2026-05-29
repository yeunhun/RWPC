/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComM_Internal.c                                               **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of Internal State Change Functionality              **
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
** 1.10.1    13-Sep-2021   Jongsun Lim #29173, #32059                         **
** 1.9.5     08-Dec-2020   Jongsun Lim #25703                                 **
** 1.9.4     26-Oct-2020   JS Lim      #26262                                 **
** 1.9.3     07-Sep-2020   Jongsun Lim #25479, #25552, #25554                 **
** 1.9.1     16-Dec-2019   JS Lim      #20684                                 **
** 1.9.0     22-Aug-2019   JS Lim      #18922, #19094, 16521                  **
** 1.8.0     23-Oct-2018   JS Lim      #13018, #13017, #13653                 **
** 1.7.16    19-Jul-2018   Chan Kim    #11240                                 **
** 1.7.14    19-Jun-2017   JH Jeong    #8337                                  **
** 1.1.6     07-Sep-2015   KT Kim      Justification for Runtime Errors       ** 
** 1.1.5     25-Aug-2015   KT Kim      Compile error fixed(#3010)             ** 
** 1.1.4     24-Aug-2015   KT Kim      Code change for MISRA rule 9.1         ** 
** 1.1.3     13-Jul-2015   KT Kim      Corrected condition for setting        ** 
**                                     SubComMode in ComM_SwitchToFullCom     **
**                                     (#2894)                                **
**                                     Disabled RTE port access               **
** 1.1.2     13-May-2015   KT Kim      Cleared errors against MISRA rule      **
** 1.1.1     27-Mar-2015   KT Kim      Revised ComM_SwitchToFullCom()         **
**                                     (#2402)                                **
** 1.1.0     09-Jan-2015   KT Kim      Revised ComM_SwitchComMMode()          **
** 1.0.8     10-Jul-2014   KT Kim      Redmine #1080: Reset timer in case     **
**                                     of NO COMMUNICATION if timer is        **
**                                     already expired                        **
**                                     #585                                   **
** 1.0.7     18-Feb-2014   KT Kim      #572 : check user request              ** 
**                                     after MinFullComMode timeout           **
** 1.0.6     04-Jul-2013   Daejun Park CR~129, XAR~581 : ComM library         **
**                                     Change the structure of ComM_Data      **
**                                     for library                            **
** 1.0.4     07-Jun-2013   Daejun Park CR~118, XAR~557 : ComM library         **
**                                     Add inclusion of header file           **
**                                     ComM_Config.h                          **
**                                     Convert macro to constant variables    **
**                                     ComM_GucTotalChannels,                 **
**                                     ComM_GucMaxChannelId,                  **
**                                     ComM_GucTotalPncs,                     **
**                                     ComM_GucPncComMaxLength                **
** 1.0.0   28-May-2013   Daejun Park   Initial version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM_Internal.h"
#include "ComM_Ram.h"
#include "ComM_Config.h"          /* ComM Config header file */
#include "SchM_ComM.h"
#include "Dcm_Cbk.h"
#include "BswM_ComM.h"
#include "Rte_ComM.h"             /* RTE generated header file */
#if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
#include "Nm.h"                   /* Nm header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COMM_INTERNAL_C_AR_RELEASE_MAJOR_VERSION    4
#define COMM_INTERNAL_C_AR_RELEASE_MINOR_VERSION    0
#define COMM_INTERNAL_C_AR_RELEASE_REVISION_VERSION 3

/* Software Version Information */
#define COMM_INTERNAL_C_SW_MAJOR_VERSION            1
#define COMM_INTERNAL_C_SW_MINOR_VERSION            10

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (COMM_INTERNAL_AR_RELEASE_MAJOR_VERSION !=\
     COMM_INTERNAL_C_AR_RELEASE_MAJOR_VERSION)
#error "ComM_Internal.c : Mismatch in Specification Major Version"
#endif

#if (COMM_INTERNAL_AR_RELEASE_MINOR_VERSION !=\
     COMM_INTERNAL_C_AR_RELEASE_MINOR_VERSION)
#error "ComM_Internal.c : Mismatch in Specification Minor Version"
#endif

#if (COMM_INTERNAL_AR_RELEASE_REVISION_VERSION !=\
     COMM_INTERNAL_C_AR_RELEASE_REVISION_VERSION)
#error "ComM_Internal.c : Mismatch in Specification Revision Version"
#endif

#if (COMM_INTERNAL_SW_MAJOR_VERSION != COMM_INTERNAL_C_SW_MAJOR_VERSION)
#error "ComM_Internal.c : Mismatch in Major Version"
#endif

#if (COMM_INTERNAL_SW_MINOR_VERSION != COMM_INTERNAL_C_SW_MINOR_VERSION)
#error "ComM_Internal.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) &&\
  (COMM_DIRECT_USER_MAPPING == STD_OFF))
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_RequestComModeRteUpdate(uint8 LucIndex, uint8
  LucUserIndex, ComM_ModeType LddComMMode);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, COMM_CODE) ComM_RequestComModeInhibitionCheck(uint8
  LucIndex, ComM_ModeType LddComMMode);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON))

#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_ComSignalReception(Com_SignalIdType SignalId,
  P2CONST(uint8, AUTOMATIC, COMM_APPL_DATA) ComSignalRxPtr );

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_PncUserHandle(uint8 LucPncIndex,
  ComM_ModeType ComMode);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#endif
#endif
/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to switch Communication mode        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIndex, LddComMMode                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaChannels, ComM_GaaSMGetCurComModeFun,       **
**                        ComM_GaaSMReqComModeFun, ComM_GaaCurComMode[].      **
**                        ComM_GaaModeRequested                               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanSM_GetCurrentComMode                             **
**                        LinSM_GetCurrentComMode, FrSM_GetCurrentComMode     **
**                        CanSM_RequestComMode, LinSM_RequestComMode,         **
**                        FrSM_RequestComMode.                                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not NULL and validated  */
/* polyspace:begin<RTE:IDP : Not a defect:Justified > This vaule is generated by Tool */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_SwitchComMMode(uint8 LucIndex, ComM_ModeType
  LddComMMode)
{
  #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)

  /* This variable is stores the Channel ID */
  NetworkHandleType LddChannelID;

  /* This variable is used to store the Channel Mode */
  ComM_ModeType LddModePtr;

  /* This variable is used to store the Bus Index */
  uint8 LucBusIndex;
  LddModePtr = ComM_GaaCurComMode[LucIndex];

  /* Loading the address of structure to local pointer */
  LddChannelID = ComM_GaaChannels[LucIndex].ddChannelId;

  /* Load the bus type from the structure */
  LucBusIndex = ComM_GaaChannels[LucIndex].ucBusType;

  /* polyspace<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
  /* polyspace:begin<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
  if (LucBusIndex != COMM_INTERNAL)
  {
    /* Get the current mode of respective SM */
    /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Its boundary is pre-defined  */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Pointer is not outside its bounds - Pointer is generated by Generator*/
    (void)ComM_GaaSMGetCurComModeFun[LucBusIndex](LddChannelID, &LddModePtr);

    /* Check if current mode and requested modes are same */
    if ((LddModePtr != LddComMMode))
    {
      if (ComM_GaaModeRequested[LucIndex] == COMM_FALSE)
      {
        /* Redmine #585 */
        ComM_GaaModeRequested[LucIndex] = COMM_TRUE;
        #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
             (COMM_ETHNETWORK_PRESENT == STD_ON))
        /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
        if (!((LddComMMode == COMM_SILENT_COMMUNICATION) &&
              ((LucBusIndex == COMM_TWO) || (LucBusIndex == COMM_FOUR))))
        #endif
        {
          /* Request the communication mode from respective SM */
          if(E_OK != ComM_GaaSMReqComModeFun[LucBusIndex](LddChannelID, LddComMMode))
          {
            ComM_GaaModeRequested[LucIndex] = COMM_FALSE;
          }
        }
      } /* End of if (ComM_GaaModeRequested[LucIndex] == COMM_FALSE) */
    } /* End of if (LddModePtr != LddComMMode) */
  } /* End of if (LucBusIndex != COMM_INTERNAL) */
  else
  #endif /* End of if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) */
  {
    /* Enter Data Protection */
    SchM_Enter_ComM_CURRENT_MODE_PROTECTION();
    
    /* If the modes are same, do not request SM or if bus type is Internal */
    ComM_GaaCurComMode[LucIndex] = LddComMMode;

    /* Exit Data Protection */
    SchM_Exit_ComM_CURRENT_MODE_PROTECTION();    
  }
  /* polyspace:begin<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
  /* polyspace:end<RTE: OBAI : Not a defect:Justified > Its boundary is pre-defined  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Pointer is not outside its bounds - Pointer is generated by Generator*/
} /* End of ComM_SwitchComMMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_SwitchToFullCom                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to change communication mode        **
**                        to Full communication                               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIndex                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaSubComMode[], ComM_GucChannelsFullComMode   **
**                        ComM_GaaChannels[], ComM_GaaWakeupIndication[],     **
**                        ComM_GblWakeUp.                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        BswM_ComM_CurrentMode(),                            **
**                        Dcm_ComM_FullComModeEntered                         **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_SwitchToFullCom(uint8 LucIndex)
{
  /* Variable to store Channel*/
  uint8 LucChannel;

  /* Variable to store the count on number of channels */
  uint8 LucCount;

  /* Initial to ZERO */
  LucCount = COMM_ZERO;

  /* Indication that Channel left the No Communication Mode */
  ComM_GucChannelsFullComMode++;

  /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
  /* Report Communication Mode change to DCM */
  Dcm_ComM_FullComModeEntered(ComM_GaaChannels[LucIndex].ddChannelId);

  /* Report Communication Mode change to BswM */
  BswM_ComM_CurrentMode(ComM_GaaChannels[LucIndex].ddChannelId,
    COMM_FULL_COMMUNICATION);

  /* Set SubComMode */
  if((ComM_GaaReqedComModeCnt[LucIndex]!= COMM_ZERO) 
    || (ComM_GaaDcmActiveDiagnostic[LucIndex] == TRUE)
    || (ComM_GaaWakeupIndication[LucIndex] == COMM_TRUE))
  {
    ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_NETWORK_REQUESTED;
  }
  else{
    ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_READY_SLEEP;
  }

  /* Clear the wake up indication for that channel */
  if (ComM_GaaWakeupIndication[LucIndex] == COMM_TRUE)
  {
    ComM_GaaWakeupIndication[LucIndex] = COMM_FALSE;
  }

  /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */

  for (LucChannel = COMM_ZERO; LucChannel < ComM_GucTotalChannels; LucChannel++)
  {
    /* Clear wakeup indication of all channels */
    if (ComM_GaaWakeupIndication[LucChannel] == COMM_FALSE)
    {
      /* Increment Counter */
      LucCount++;
    }
  }

  /* If wake up indication of all channels is cleared */
  if (LucCount == ComM_GucTotalChannels)
  {
    /*Clear Global WakeUp */
    ComM_GblWakeUp = COMM_FALSE;
  }
} /* End of ComM_SwitchToFullCom */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_SwitchToNoCom                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to change communication mode from   **
**                        Full or Silent to No communication                  **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIndex                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaSubComMode[], ComM_GucChannelsFullComMode   **
**                        ComM_GaaRequestedComMode[], ComM_GaaReqedComModeCnt **
**                        ComM_GblWakeUp, ComM_GaaChannelInhibition           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Dcm_ComM_NoComModeEntered(),                        **
**                        BswM_ComM_CurrentMode()                             **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_SwitchToNoCom(uint8 LucIndex)
{
  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
      (COMM_ETHNETWORK_PRESENT == STD_ON))
  /* Variable for Number of Pncs linked to the Channel */
  uint8 LucNoOfPncs;
  /* Variable for Pnc Index */
  uint8 LucPncIndex;
  /* Variable for channel to pnc mapping */
  uint8 LucIndexValue;  
  #endif
  #endif
  
  /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
  /* Report the No communication mode to DCM */
  Dcm_ComM_NoComModeEntered(ComM_GaaChannels[LucIndex].ddChannelId);

  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
      (COMM_ETHNETWORK_PRESENT == STD_ON))
  /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
  if (ComM_GaaChannels[LucIndex].blChannelPnc == COMM_TRUE)
  {
    /* Number of Pncs linked to the Channel */
    LucNoOfPncs = ComM_GaaChannels[LucIndex].ucPncCount;

    /* Index in the Pnc Index array in the User */
    LucPncIndex = ComM_GaaChannels[LucIndex].ucPncIndex;

    while (LucNoOfPncs != COMM_ZERO)
    {
      /* polyspace<RTE: OBAI : Not a defect:Justified > Arry index generated by Generation tool and valid  */
      /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> Arry index generated by Generation tool and valid  */
      LucIndexValue = ComM_GaaChannelToPncMapping[LucPncIndex];

      /* Start the PNC Timer for the channel*/
      SchM_Enter_ComM_PNC_PREPARE_TIMER();
      /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
      /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
      ComM_GaaPncTimeCnt[LucIndexValue] = COMM_ZERO;
      SchM_Exit_ComM_PNC_PREPARE_TIMER();
      /* Decrement the PNC Count*/
      LucNoOfPncs--;
      LucPncIndex++;
      
      ComM_GaaSubPNCMode[LucIndexValue] = PNC_NO_COMMUNICATION;

      /* Indication to BswM Module */
      BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucIndexValue].ddPncId,
        PNC_NO_COMMUNICATION);      
    }
  }
  #endif
  #endif    

  /* Report Communication Mode change to BswM */
  BswM_ComM_CurrentMode(ComM_GaaChannels[LucIndex].ddChannelId,
    COMM_NO_COMMUNICATION);

  /* Indication that Channel entered No Communication Mode */
  ComM_GucChannelsFullComMode--;

  /* Change Sub State of No Communication*/
  ComM_GaaSubComMode[LucIndex] = COMM_NO_COM_NO_PENDING_REQUEST;

  /* Clear all Requests for the Specific user of the channel */
  /*ComM_GaaRequestedComMode[LucIndex] = COMM_NO_COMMUNICATION;*/
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  /*  Check for Limit channel inhibition condition and Limit ECU to No Com */
  if ((ComM_GaaChannelInhibition[LucIndex] &
    COMM_LIMITCHANNELTONOCOMM_MASK_SET) == COMM_LIMITCHANNELTONOCOMM_MASK_SET)
  {
    ComM_GaaChannelInhibition[LucIndex] = (ComM_GaaChannelInhibition[LucIndex] &
      COMM_LIMITCHANNELTONOCOMM_MASK_CLR);
  }
  #endif
  /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */


  /*Clear Global WakeUp */
  ComM_GblWakeUp = COMM_FALSE;
} /* End of ComM_SwitchToNoCom */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_FullComMToSilentComM                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to change communication mode from   **
**                        Full to Silent communication                        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIndex                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaChannels[], ComM_GaaSubComMode[]            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Dcm_ComM_SilentComModeEntered,BswM_ComM_CurrentMode **
*******************************************************************************/
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_FullComMToSilentComM(uint8 LucIndex)
{
  /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
  ComM_GaaSubComMode[LucIndex] = COMM_SILENT_COM;

  /* Report the Silent communication mode to DCM */
  Dcm_ComM_SilentComModeEntered(ComM_GaaChannels[LucIndex].ddChannelId);

  /* Report Communication Mode change to BswM */
  BswM_ComM_CurrentMode(ComM_GaaChannels[LucIndex].ddChannelId,
    COMM_SILENT_COMMUNICATION);
  /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
}

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if(COMM_CANNETWORK_PRESENT == STD_ON) ||
  * (COMM_ETHNETWORK_PRESENT == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_RequestComModeInhibitionCheck                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to check for inhibition when there  **
**                        is a request using API ComM_RequestComMode          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucIndex, LddComMMode                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblComModeErrorFlg                                  **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaChannels[], ComM_GblLimitEcuToNoCom,        **
**                        ComM_GaaInhibitionReqst, ComM_GstData               **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_ComM_INHIBIT_CNT_PROTECTION(),           **
**                        SchM_Exit_ComM_INHIBIT_CNT_PROTECTION()             **
*******************************************************************************/
#if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, COMM_CODE) ComM_RequestComModeInhibitionCheck
  (uint8 LucIndex, ComM_ModeType LddComMMode)
{
  #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)

  /* Variable to check if inhibition is due to wake up inhibition */
  boolean LblInhibitionFlag;
  #endif
  boolean LblComModeErrorFlg;
  #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)

  /* Initialize the variable */
  LblInhibitionFlag = COMM_FALSE;
  #endif
  LblComModeErrorFlg = COMM_FALSE;

  /* Mode cannot be granted because of the Mode Limitation */
  if (LddComMMode == COMM_FULL_COMMUNICATION)
  {
    /* Check if wake up inhibition is enabled in ECU group
     *   classification and Nm running in passive mode */
    /* polyspace<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> condition will be executed based on the configured values */
    if ((ComM_GaaChannels[LucIndex].ucNmVariant == COMM_NMVARIANT_PASSIVE) &&
        (ComM_GstData.ddComMEcuInhibition == COMM_ONE))
    {
      /* Error Flag is set*/
      LblComModeErrorFlg = COMM_TRUE;
    }
    #if (COMM_MODE_LIMITATION_ENABLED == STD_ON)

    /* Limit to No Communication functionality is enabled and
     *   Limit ECU to No Communication is Enabled */

    /* Prevent Wake Up is enabled */
    else if (((ComM_GaaChannelInhibition[LucIndex] &
               COMM_LIMITCHNTONOCOM_MASK) == COMM_TWO) ||
             (ComM_GblLimitEcuToNoCom == COMM_TRUE))
    {
      /* Error Flag is set*/
      LblComModeErrorFlg = COMM_TRUE;
    }
    #endif /* End of if (COMM_MODE_LIMITATION_ENABLED == STD_ON) */
    #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)

    /* Prevent Wake Up is enabled */
    else if ((ComM_GaaChannelInhibition[LucIndex] &
              COMM_PREVENTWAKEUP_MASK) == COMM_ONE)
    {
      /* Error Flag is set*/
      LblComModeErrorFlg = COMM_TRUE;

      /* Flag to store that inhibition is due to Prevent wake up */
      LblInhibitionFlag = COMM_TRUE;
    }
    #endif /* End of if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) */
    else
    {
      /* To avoid MISRA warning */
    }
  } /* End of if (LddComMMode == COMM_FULL_COMMUNICATION) */
  #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)

  /*  Check for Limit channel inhibition condition and Limit ECU to No Com */
  else if ((ComM_GaaChannelInhibition[LucIndex] &
            COMM_PREVENTWAKEUP_MASK) == COMM_ONE)
  {
    /* Store the no communication request due to prevent wake up
     *   inhibition */
    ComM_GaaInhibitionReqst[LucIndex]--;
  }
  else
  {
    /* To avoid Misra warning */
  }
  #endif /* (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) */

  /* Mode cannot be granted because of the Mode Limitation */
  if (LblComModeErrorFlg == COMM_TRUE)
  {
    #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)

    /* The Full Communication request during inhibition is checked */
    if (LblInhibitionFlag == COMM_TRUE)
    {
      /* Update request when prevent wakeup is enabled */
      ComM_GaaInhibitionReqst[LucIndex]++;
    }
    #endif
    #if (COMM_MODE_LIMITATION_ENABLED == STD_ON)

    if ((LddComMMode == COMM_FULL_COMMUNICATION) &&
        (ComM_GstData.usComMFullComInhibitCounter < COMM_INHIBITCNT_MAX))
    {
      /* Enter in Data Protection */
      SchM_Enter_ComM_INHIBIT_CNT_PROTECTION();

      /* Increment full communication inhibit counter */
      ComM_GstData.usComMFullComInhibitCounter++;

      /* Exit Data Protection */
      SchM_Exit_ComM_INHIBIT_CNT_PROTECTION();
    } /* End of if LddComMMode == COMM_FULL_COMMUNICATION */
    #endif /* End of if (COMM_MODE_LIMITATION_ENABLED == STD_ON) */
  } /* End of if(LblComModeErrorFlg = COMM_TRUE) */
  return (LblComModeErrorFlg);
} /* End of ComM_RequestComModeInhibitionCheck */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif  /* ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
  * || (COMM_MODE_LIMITATION_ENABLED == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_ChannelDETCheck                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to check DET for the ChannelID      **
**                        passed                                              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel, ApiId                                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK, E_NOT_OK and COMM_E_UNINIT                    **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GblInit, ComM_GaaChannelMapArray               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE) ComM_ChannelDETCheck
  (NetworkHandleType Channel, uint8 ApiId)
{
  /* This variable is to store the return values */
  Std_ReturnType LddReturnValue;

  /* Initialize the return variable to E_OK */
  LddReturnValue = E_OK;

  /* Check, if the module is initialized or not */
  if (ComM_GblInit == COMM_UNINIT)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_NOT_INITED);

    /* Set return value to indicate ComM is uninitialized */
    LddReturnValue = COMM_E_UNINIT;
  }

  /*Check if Channel ID is more than the Id configured */
  if (Channel > ComM_GucMaxChannelId)
  {
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_WRONG_PARAMETERS);

    /* Set return value to indicate the channel is not within configured
     *   channels */
    LddReturnValue = E_NOT_OK;
  }
  #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
  else if (ComM_GaaChannelMapArray[Channel] == COMM_INVALID_CHANNEL)
  {
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_WRONG_PARAMETERS);

    /* Set return value to indicate the channel is not a configured channel */
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /* To avoid MISRA warning */
  }
  #endif /* End of if (COMM_CHANNEL_SEQUENTIAL == STD_OFF) */
  return (LddReturnValue);
} /* End of ComM_ChannelDETCheck */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_UserDETCheck                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to check DET for the UserID passed  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : User, ApiId                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK, E_NOT_OK and COMM_E_UNINIT                    **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GblInit, ComM_GaaUserMapArray                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE) ComM_UserDETCheck
  (ComM_UserHandleType User, uint8 ApiId)
{
  /* This variable is to store the return values */
  Std_ReturnType LddReturnValue;

  /* Initialize the return variable to E_OK */
  LddReturnValue = E_OK;

  /* Check, if the module is initialized or not */
  if (ComM_GblInit == COMM_UNINIT)
  {
    /* Report to DET */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_NOT_INITED);

    /* Set return value to indicate ComM is uninitialized */
    LddReturnValue = COMM_E_UNINIT;
  }

  /* Check if User ID is  more than total users and
   *   is more than the Id configured */
  if ((User == COMM_NOT_USED_USER_ID) || (User > ComM_GucMaxUserId))
  {
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_WRONG_PARAMETERS);

    /* Set return value to indicate the user is not valid Id */
    LddReturnValue = E_NOT_OK;
  }
  #if (COMM_USER_SEQUENTIAL == STD_OFF)
  else if (ComM_GaaUserMapArray[User] == COMM_INVALID_USER)
  {
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, ApiId,
      COMM_E_WRONG_PARAMETERS);

    /* Set return value to indicate the user is not a configured user */
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /* To avoid MISRA warning */
  }
  #endif /* End of if (COMM_USER_SEQUENTIAL == STD_OFF) */
  return (LddReturnValue);
} /* End of ComM_UserDETCheck */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_RequestComModeRteUpdate                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to update Rte the user requesting   **
**                        Fullcommunication for a channel using API           **
**                        ComM_RequestComMode                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucIndex, LucUserIndex, LddComMMode                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GstData,ComM_GaaChannels[],ComM_GaaUsers[]     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Write_fullComRequestors()                           **
**                        SchM_Enter_ComM_REQ_MODECNT_PROTECTION()            **
**                        SchM_Exit_ComM_REQ_MODECNT_PROTECTION()             **
*******************************************************************************/
#if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
  (COMM_DIRECT_USER_MAPPING == STD_OFF))
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_RequestComModeRteUpdate(uint8 LucIndex, uint8
  LucUserIndex, ComM_ModeType LddComMMode)
{
  /* Variable to store the maximum requestors of a channel */
  uint8 LucMaxChannelReq;

  /* Variable to store the last user id who requested the channel */
  uint8 LucLastUserId;

  /* Variable to store the index of requestors of a channel */
  uint8 LucReqIndex;

  /* Variable to write the maximum requestors of a channel to Rte */
  Rte_PortHandle_ComM_CurrentChannelRequest_P LddComMRteFullComWrite;

  #if(COMM_RTE_NOTIF == STD_ON)
  LddComMRteFullComWrite = (Rte_PortHandle_ComM_CurrentChannelRequest_P)
                           Rte_Ports_ComM_CurrentChannelRequest_P();
  #endif
  /* Initializing the index with recent user requestor of the
   *   channel*/
  LucMaxChannelReq = ComM_GstFullComReq[LucIndex].numberOfRequesters;

  if((LucMaxChannelReq < MAX_CHANNEL_REQUESTERS) && (LucMaxChannelReq != COMM_ZERO))
  {
    /*If the mode is Full communication */
    if (LddComMMode == COMM_FULL_COMMUNICATION)
    {
      /* Enter in Data Protection */
      SchM_Enter_ComM_REQ_MODECNT_PROTECTION();

      /* Store the user id of the user of the channel */
      /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET */
      ComM_GstFullComReq[LucIndex].handleArray[LucMaxChannelReq] =
        ComM_GaaUsers[LucUserIndex].ddUserId;

      /* Store the number of requestors of the channel */
      ComM_GstFullComReq[LucIndex].numberOfRequesters++;

      /* Exit data protection */
      SchM_Exit_ComM_REQ_MODECNT_PROTECTION();
    } /* End of if (LddComMMode == COMM_FULL_COMMUNICATION) */
    else
    {
      /* Get the last user id */
      LucLastUserId = ComM_GstFullComReq[LucIndex].handleArray
                      [LucMaxChannelReq - COMM_ONE];

      /* If the current user had requested for Full Communication
      *   before */
     
      if (LucLastUserId != ComM_GaaUsers[LucUserIndex].ddUserId)
      {
        /* Check if user is present in the array of Full Communication
        *   requestors of that channel */
        for (LucReqIndex = COMM_ZERO; LucReqIndex < LucMaxChannelReq;
            LucReqIndex++)
        {
          /* Find the user */
          if (ComM_GstFullComReq[LucIndex].handleArray
              [LucReqIndex] == ComM_GaaUsers[LucUserIndex].ddUserId)
          {
            /* Enter in Data Protection */
            SchM_Enter_ComM_REQ_MODECNT_PROTECTION();

            /* Overwrite the ID with last user id */
            ComM_GstFullComReq[LucIndex].handleArray
            [LucReqIndex] = LucLastUserId;

            /* Exit data protection */
            SchM_Exit_ComM_REQ_MODECNT_PROTECTION();
          } /* End of if (ComM_GstFullComReq[LucIndex].handleArray */
        }
      } /* End of if (LucLastUserId != ComM_GaaUsers[LucUserIndex].ddUserId) */
      /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET */
      /* Enter in Data Protection */
      SchM_Enter_ComM_REQ_MODECNT_PROTECTION();

      /* Decrement total number of requestors requested count */
      ComM_GstFullComReq[LucIndex].numberOfRequesters--;

      /* Exit data protection */
      SchM_Exit_ComM_REQ_MODECNT_PROTECTION();
    } /* End of else */
    /* Update Rte with the required information */
    #if(COMM_RTE_NOTIF == STD_ON)
    LddComMRteFullComWrite[LucIndex].
                          Write_fullComRequestors(&ComM_GstFullComReq[LucIndex]);
    #endif
  }
} /* End of ComM_RequestComModeRteUpdate */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_PncUserHandle                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall save user mode request for PNC   **
**                        State changes                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucPncIndex,   LddComMode                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        ComM_GaaPncs,ComM_GaaPncToUserMapping,              **
**                        ComM_GaaUserMapArray,ComM_GaaRequestedComMode,      **
**                        ComM_GaaRequestedPNCMod,                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_PncUserHandle(uint8 LucPncIndex, ComM_ModeType
  ComMode)
{
  /* The Variable to store User Index */
  uint8 LucPncUserIndex;

  /* The Variable to store User Count */
  uint8 LucPncUserCount;

  /* The Variable to store User ID */
  uint8 LddUserId;

  /* The Variable to store User Index from user map array */
  uint8 LucIndex;

  ComM_ModeType LddComMode = ComMode;

  /* Get User Index */
  LucPncUserIndex = ComM_GaaPncs[LucPncIndex].ucUserIndex;

  /* Get User Count */
  LucPncUserCount = ComM_GaaPncs[LucPncIndex].ucUserCount;
  while (LucPncUserCount != COMM_ZERO)
  {
    LucPncUserCount--;

    /* Note: Mapping provides ID of the User */
    /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
    LddUserId = ComM_GaaPncToUserMapping[LucPncUserIndex];
    #if (COMM_USER_SEQUENTIAL == STD_OFF)
    LucIndex = ComM_GaaUserMapArray[LddUserId];
    #else
    LucIndex = LddUserId;
    #endif

    /* Checking mode of all the users of the PNC*/
    /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
    if (LddComMode < ComM_GaaRequestedComMode[LucIndex])
    {
      LddComMode = ComM_GaaRequestedComMode[LucIndex];
    }
    LucPncUserIndex++;
  }

  /* full communication mode :Atleast one User in Full Com */
  if (LddComMode == COMM_FULL_COMMUNICATION)
  {
    /* full communication mode */
    ComM_GaaRequestedPNCMode[LucPncIndex] = PNC_USER_FULL_COMM;
  }
  else
  /* No communication mode :All user request No Com */
  {
    /* ready sleep mode */
    ComM_GaaRequestedPNCMode[LucPncIndex] = PNC_USER_NO_COMM;
  }
} /* End of ComM_PncUserHandle */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
  *STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_PncUserLowestMode                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall indicate RTE about the PNC Users **
**                        Lowest communication Mode of the associated channels**
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucUserIndx                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        ComM_GaaUsers, ComM_GaaPncUserInxArr, ComM_GaaPncs  **
**                        ComM_GaaChnPncInxArr, ComM_GaaChannelMapArray       **
**                        ComM_GaaCurComMode, ComM_GaaChnInxArr               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Rte_Switch_ComM_UMxxx_currentMode()                 **
*******************************************************************************/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_PncUserLowestMode(uint8 LucUserIndx)
{
  #if(COMM_RTE_NOTIF == STD_ON)
  /* Lowest mode requested by user (No-Slient-Full)*/
  ComM_ModeType LddLowestMode;
  #endif

  /* variable to store the Channel ID from ComM_GaaChnPncInxArr */
  NetworkHandleType LddCHId;
  #if (COMM_DIRECT_CHANNEL == STD_ON)

  /* Variable to store the Total No. of Channels of the User */
  uint8 LucNoOfChannels;

  /* Index to the channel Id's in the ChannelIndex Array */
  uint8 LucUserChannelIndex;

  /* The Variable to store Channel Index */
  uint8 LucChnInd;
  #endif

  /* variable to store the total No of PNCS associated with User */
  uint8 LucPncCnt;

  /* variable to store the start PNC Index */
  uint8 LucPncIx;

  /* variable to store index from the respective users */
  uint8 LucIx;

  /* variable to store the Channel Count from pnc */
  uint8 LucCHCnt;

  /* variable to store the start channel index from pnc */
  uint8 LucCHInx;

  /* variable to store the index */
  NetworkHandleType LddCHIndex;

  /* Rte_PortHandle_ComM_CurrentMode_P LddComMRteMode; */

  #if(COMM_RTE_NOTIF == STD_ON)
  LddComMRteMode =
    (Rte_PortHandle_ComM_CurrentMode_P)Rte_Ports_ComM_CurrentMode_P();  

  /* Initialize to Full communication */
  LddLowestMode = COMM_FULL_COMMUNICATION;
  #endif

  #if (COMM_DIRECT_CHANNEL == STD_ON)

  /* Get the No of User Direct channels */
  /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
  /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
  LucNoOfChannels = ComM_GaaUsers[LucUserIndx].ucNoOfDirectChannels;

  /* Get the Direct channels Index */
  LucUserChannelIndex = ComM_GaaUsers[LucUserIndx].ucDirectChannelIndex;
  #endif

  /* Get the total No of PNCS associated with User*/
  LucPncCnt = ComM_GaaUsers[LucUserIndx].ucNoOfPncUser;

  /* Get the start PNC Index */
  LucPncIx = ComM_GaaUsers[LucUserIndx].ucPncUserIndex;
  /*PNC loop to channel Loop */
  while (LucPncCnt != COMM_ZERO)
  {
    /* Decrement the pnc count */
    LucPncCnt--;

    /* Get the index from the user */
    /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
    LucIx = ComM_GaaPncUserInxArr[LucPncIx];

    /* Get the Channel Count from pnc */
    /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
    LucCHCnt = ComM_GaaPncs[LucIx].ucNoOfChannelPnc;

    /* Get the start channel index from pnc */
    LucCHInx = ComM_GaaPncs[LucIx].ucChannelPncIndex;
    while (LucCHCnt != COMM_ZERO)
    {
      LucCHCnt--;

      /*
       * Note: pnc Index array provides ID of the channel
       * variable to store the channel ID
       */
      /* polyspace<MISRA-C3:18.1:Not a defect:Unset> Pointer range is valid and validated by DET */
      /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */    
      LddCHId = ComM_GaaChnPncInxArr[LucCHInx];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

      /* variable to store the channel index  */
      LddCHIndex = ComM_GaaChannelMapArray[LddCHId];
      #else
      LddCHIndex = LddCHId;
      #endif
      /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
      /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
      if (ComM_GaaCurComMode[LddCHIndex] == COMM_NO_COMMUNICATION)
      {
        #if(COMM_RTE_NOTIF == STD_ON)
        /* Get the lowest mode */
        LddLowestMode = COMM_NO_COMMUNICATION;
        #endif

        /* Break from while: channel */
        LucCHCnt = COMM_ZERO;

        /* Break from while: PNC */
        LucPncCnt = COMM_ZERO;
        #if (COMM_DIRECT_CHANNEL == STD_ON)

        /* Break from while: direct channel */
        LucNoOfChannels = COMM_ZERO;
        #endif
      } /* End of if (ComM_GaaCurComMode[LddCHIndex] == COMM_NO_COMMUNICATION)
         **/
      else
      {
        /* Check for Silent communication */
        if (ComM_GaaCurComMode[LddCHIndex] == COMM_SILENT_COMMUNICATION)
        {
          #if(COMM_RTE_NOTIF == STD_ON)
          /* Get the lowest mode */
          LddLowestMode = COMM_SILENT_COMMUNICATION;
          #endif
        }
        /* Check next channel associated with the same PNC */
        LucCHInx++;
      } /* End of else */
    }
    LucPncIx++;
  }

  #if (COMM_DIRECT_CHANNEL == STD_ON)
  /* Direct channel Loop */
  while (LucNoOfChannels != COMM_ZERO)
  {
    /* Decrement the direct channel count */
    LucNoOfChannels--;

    /* Get the channel index  */
    /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
    LucChnInd = ComM_GaaChnInxArr[LucUserChannelIndex];
    /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
    /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
    if (ComM_GaaCurComMode[LucChnInd] == COMM_NO_COMMUNICATION)
    {
      #if(COMM_RTE_NOTIF == STD_ON)
      /* Get the lowest mode */
      LddLowestMode = COMM_NO_COMMUNICATION;
      #endif

      /* Break from while */
      LucNoOfChannels = COMM_ZERO;
    }
    else
    {
      /* Check for Silent communication */
      if (ComM_GaaCurComMode[LucChnInd] == COMM_SILENT_COMMUNICATION)
      {
        #if(COMM_RTE_NOTIF == STD_ON)
        /* Get the lowest mode */
        LddLowestMode = COMM_SILENT_COMMUNICATION;
        #endif
      }
      /* Check next channel associated with the same user */
      LucUserChannelIndex++;
    } /* End of else */
  }

  #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

  /* Indicate NO_COMM/SILENT_COMM/FULL_COMM mode to RTE */
  #if(COMM_RTE_NOTIF == STD_ON)
  LddComMRteMode[LucUserIndx].Switch_currentMode(LddLowestMode);
  #endif

} /* End of ComM_PncUserLowestMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
  *STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_ComSignalReception                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall save EIRA and ERAn Signals of PNC**
**                        as indicated by Com Module                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : SignalId, ComSignalRxPtr                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        ComM_GaaPncs,ComM_GaaComSignal,ComM_GaaPncRxEIRA    **
**                        ComM_GaaPncRxEIRASignal,ComM_GaaPncRxERASignal,     **
**                        ComM_GaaPncRxERAn                                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                                                                            **
*******************************************************************************/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, COMM_CODE) ComM_ComSignalReception(Com_SignalIdType SignalId,
  P2CONST(uint8, AUTOMATIC, COMM_APPL_DATA) ComSignalRxPtr )
{
  /* Variable to Store the Count of Total Signals */
  uint16 LusComSignalCnt;

  /* Variable to Store the Signal start Instance*/
  uint16 LusSignalInst;

  /* Variable to store Bit Index of PNC */
  uint8 LucBitIndex;

  /* Variable to store Byte Index of PNC */
  uint8 LucByteIndex;

  /* Variable to store PNC Index*/
  PNCHandleType LddPncIndex;

  /* Variable to store the PNC Identifier*/
  PNCHandleType LddPncId;

  /* Variable to store Signal Kind {EIRA/ERA} */
  uint8 LucSignalKind;

  /*Variable to store Mask Value for the bit Index*/
  uint8 LucMask;

  for (LddPncIndex = COMM_ZERO; LddPncIndex < ComM_GucTotalPncs; LddPncIndex++)
  {
    /*Calculating the PNC ID for the Pnc Index*/
    LddPncId = ComM_GaaPncs[LddPncIndex].ddPncId;

    /*Calculation Of Byte Index*/
    /* #20684 */
    LucByteIndex = (uint8)(LddPncId >> (uint8)COMM_THREE) - COMM_PNC_VECTOR;

    /*Calculation Of Bit Index within the Byte */
    LucBitIndex = (uint8)(LddPncId % COMM_EIGHT);

    /*Calculating the Mask Value for the bit Index*/
    LucMask = (uint8)((uint8)COMM_ONE << LucBitIndex);

    /* Count of Total Signal with this PNC */
    LusComSignalCnt = ComM_GaaPncs[LddPncIndex].usNoOfComSignal;

    /* Start Index of the Signal Instance within this PNC */
    LusSignalInst = ComM_GaaPncs[LddPncIndex].usComSignalIndex;
    /*Traversing whole signals of the PNC*/
    /* polyspace<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> condition will be executed based on the configured values */    
    while (LusComSignalCnt != COMM_ZERO)
    {
      LusComSignalCnt--;
      /* polyspace<RTE:OBAI:Not a defect:Justified> Array index is in range and valid */
      /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
      if ((SignalId == ComM_GaaComSignal[LusSignalInst].ddComMComSigId) && \
          (COMM_RX == ComM_GaaComSignal[LusSignalInst].ucComMPncComSigDir))
      {

        /* Com Signal Kind */
        LucSignalKind = ComM_GaaComSignal[LusSignalInst].ucComMPncComSignalKind;

        /* EIRA is Received : Rx EIRA in a PNC */
        /* polyspace<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> condition will be executed based on the configured values */
        if (LucSignalKind == COMM_EIRA)
        {
          /* #25479
          * Same SignalHandleId is present in PNC more than once(Tx, Rx)
          * Signal search is over : Break From Loop
          */
          LusComSignalCnt = COMM_ZERO;
          /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
          if ((ComSignalRxPtr[LucByteIndex] & LucMask) == COMM_ZERO)
          {
            /* Clear PNC EIRA Signal Instance*/
            ComM_GaaPncRxEIRASignal[((uint16)LddPncIndex * (uint16)ComM_GucTotalSignals) + LusSignalInst] = COMM_FALSE;
            
          }
          else
          {
            ComM_GaaPncRxEIRA[LddPncIndex] = COMM_TRUE;

            /* Set PNC EIRA Signal Instance*/
            ComM_GaaPncRxEIRASignal[((uint16)LddPncIndex * (uint16)ComM_GucTotalSignals) + LusSignalInst] = COMM_TRUE;
          }
        } /* End of if ((LucSignalKind == COMM_EIRA) && (LucSignalDxn ==
           * COMM_RX)) */
        #if (COMM_PNC_GW_ENABLED == STD_ON)

        /* ERA is Received: n ERA in a PNC */
        /* polyspace<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> condition will be executed based on the configured values */    
        else if (LucSignalKind == COMM_ERA)
        {
          /* #25479
          * Same SignalHandleId is present in PNC more than once(Tx, Rx)
          * Signal search is over : Break From Loop
          */
          LusComSignalCnt = COMM_ZERO;
          if ((ComSignalRxPtr[LucByteIndex] & LucMask) == COMM_ZERO)
          {
            /* The ERA Received for Signal Instance : COMM_FALSE */
            ComM_GaaPncRxERASignal[((uint16)LddPncIndex * (uint16)ComM_GucTotalSignals) + LusSignalInst] = COMM_FALSE;
          }
          else
          {
            ComM_GaaPncRxERAn[LddPncIndex] = COMM_TRUE;

            /* The ERA Received for Signal Instance : COMM_TRUE */
            ComM_GaaPncRxERASignal[((uint16)LddPncIndex * (uint16)ComM_GucTotalSignals) + LusSignalInst] = COMM_TRUE;
          }
        } /* End of if ((LucSignalKind == COMM_ERA) && (LucSignalDxn ==
           *COMM_RX)) */
        #endif /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */
        else
        {
          /* Check all of Signals #25479 */
          LusSignalInst++;
        }
      } /* End of if (SignalId ==
         *ComM_GaaComSignal[LusSignalInst].ddComMComSigId) */
      else
      {
        LusSignalInst++;
      }
    }
  }
} /* End of ComM_ComSignalReception */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
  *STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_RequestComModeDirectChnl                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to update RTE about the user request**
**                        for Full communication of direct channels using API **
**                        ComM_RequestComMode                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucUserIndex, ComMode                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddStdRetVal                                        **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaUsers, ComM_GaaRequestedComMode,            **
**                        ComM_GaaChnInxArr, ComM_GaaReqedComModeCnt          **
**                        ComM_GaaChannels, ComM_GaaTimeCnt                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_RequestComModeRteUpdate()                      **
**                        ComM_RequestComModeInhibitionCheck()                **
**                        SchM_Enter_ComM_REQ_MODECNT_PROTECTION()            **
**                        SchM_Exit_ComM_REQ_MODECNT_PROTECTION()             **
*******************************************************************************/
#if (COMM_DIRECT_CHANNEL == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComModeDirectChnl(uint8
  LucUserIndex, ComM_ModeType ComMode)
{
  /* Function Return Variable */
  Std_ReturnType LddStdRetVal;

  /* variable to store the Total No. of Channels of the User/PNC */
  uint8 LucNoOfChannels;

  /* Index to the ComM_GaaChnInxArr/ComM_GaaChnPncInxArr Array */
  uint8 LucChannelIndex;

  /* Variable to store the channel Index */
  uint8 LucIndex;

  /* Flag to check FULL/NO communication request is stored in global variable */
  uint8 LucComModeReqFlag;

  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  boolean LblInhibitionRetVal;
  #endif

  /* Initialize the request variable to predefined value */
  LucComModeReqFlag = COMM_ZERO;

  /* Initialize the return variable to E_OK */
  LddStdRetVal = E_OK;
  /*
   * Note: Direct channel may be Present in case of PNC ENABLED
   * Number of Direct Channel linked to the User
   */

  /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET */
  /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
  LucNoOfChannels = ComM_GaaUsers[LucUserIndex].ucNoOfDirectChannels;

  /* Index in the Direct Channel Index array in the User */
  LucChannelIndex = ComM_GaaUsers[LucUserIndex].ucDirectChannelIndex;
  while (LucNoOfChannels != COMM_ZERO)
  {
    /* Get the Channel index from the Channel Index Array */
    LucIndex = ComM_GaaChnInxArr[LucChannelIndex];

    /* Decrement the Channel */
    LucNoOfChannels--;
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    LblInhibitionRetVal =
      ComM_RequestComModeInhibitionCheck(LucIndex, ComMode);

    /* If no inhibition is set */
    if (LblInhibitionRetVal == COMM_FALSE)
    #endif
    {
      /* Enter in Data Protection */
      SchM_Enter_ComM_REQ_MODECNT_PROTECTION();

      if (ComMode == COMM_FULL_COMMUNICATION)
      {
        /* If the previous request of that user is not
         *   Full communication */
        if (ComM_GaaRequestedComMode[LucUserIndex] != COMM_FULL_COMMUNICATION)
        {
          /* Load the Requested Full Com Mode into the User
           *   Requested Com mode array */
          ComM_GaaRequestedComMode[LucUserIndex] =
            COMM_FULL_COMMUNICATION;

          /* Flag to know that the user has requested only once */
          LucComModeReqFlag = COMM_FULLCOMMREQ_ACCPTD;
        }
      } /* End of if (ComMode == COMM_FULL_COMMUNICATION) */
      else if (ComM_GaaRequestedComMode[LucUserIndex] != COMM_NO_COMMUNICATION)
      {
        /* Load the Requested No Com Mode into the User
         *   Requested Com mode array */
        ComM_GaaRequestedComMode[LucUserIndex] = COMM_NO_COMMUNICATION;

        /* Flag to know that the user has requested only once */
        LucComModeReqFlag = COMM_NOCOMMREQ_ACCPTD;        
      }
      else
      {
        /* To avoid MISRA warning */
      }
      /* If the user request was accepted */
      if (LucComModeReqFlag == COMM_FULLCOMMREQ_ACCPTD)
      {
        /* Load the Requested ComMode in the Array */        
        ComM_GaaReqedComModeCnt[LucIndex]++;
        #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
        (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

        /* Stop the timer if there is user request when there is no NM
         *   available */
        ComM_GaaTimeCnt[LucIndex] = (ComM_TimeType)COMM_ZERO;
        #endif
      }
      else if (LucComModeReqFlag == COMM_NOCOMMREQ_ACCPTD)
      {
        /* Load the Requested ComMode in the Array */        
        ComM_GaaReqedComModeCnt[LucIndex]--;
      }
      else
      {
        /* To avoid MISRA warning */
      }
      /* Exit data protection */
      SchM_Exit_ComM_REQ_MODECNT_PROTECTION();

      /* Next Channel Index */
      LucChannelIndex++;
      #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
        (COMM_DIRECT_USER_MAPPING == STD_OFF))

      /* Update Rte with the user who has requested the channel */
      /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
      if (ComM_GaaChannels[LucIndex].blFullCommReqNotifEn == COMM_TRUE)
      {
        ComM_RequestComModeRteUpdate(LucIndex, LucUserIndex, ComMode);
      }
      #endif
    }
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    else
    {
      LddStdRetVal = COMM_E_MODE_LIMITATION;
    }
    #endif
  } /* End of While */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
  /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET */
  /* polyspace:end<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET */
  return (LddStdRetVal);
} /* End of ComM_RequestComModeDirectChnl */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_GetCurComModeDirectChnl                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to update Lowest mode of direct     **
**                        channels for the API ComM_GetCurComMode             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucUserChannelIndex, LucNoOfChannels, LddLowestMode **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : LddReturnValue                                      **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaChnInxArr, ComM_GaaChannels,                **
**                        ComM_GaaCurComMode                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        CanSM_GetCurrentComMode(), LinSM_GetCurrentComMode()**
**                        FrSM_GetCurrentComMode(), EthSM _GetCurrentComMode()**
**                        Det_ReportError()                                   **
*******************************************************************************/
#if (COMM_DIRECT_CHANNEL == STD_ON)
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE) ComM_GetCurComModeDirectChnl(uint8
  LucUserChannelIndex, uint8 LucNoOfChannels, P2VAR(ComM_ModeType, AUTOMATIC,
    COMM_APPL_DATA) LddLowestMode)
{
  /* The variable to get the direct channel Index */
  uint8 LucChannelIndex;

  uint8 lucChnIdx;
  uint8 luctotalChnls;
  
  Std_ReturnType LddReturnValue;
  #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)

  /* Pointer to load the current mode of respective SM */
  ComM_ModeType LddModePtr;
  
  LddModePtr = COMM_NO_COMMUNICATION;
  #endif

  /*Initialize the Return value*/
  LddReturnValue = E_OK;
  lucChnIdx = LucUserChannelIndex;
  luctotalChnls = LucNoOfChannels;
  /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Input parameters are valid, Pointer is not a NULL and Valid  */
  /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Its boundary is pre-defined  */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Pointer is not outside its bounds - Pointer is generated by Generator*/
  /* Check the Current Communication Mode of the Each Direct channel */
  while (luctotalChnls != COMM_ZERO)
  {
    /* Get the Channel from Index Array */    
    LucChannelIndex = ComM_GaaChnInxArr[lucChnIdx];

    /* Decrement the Number of channels */
    luctotalChnls--;
    #if (COMM_DEV_ERROR_DETECT == STD_ON)

    /* Validate the channel */
    /* polyspace<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> condition will be executed based on the configured values */
    /* polyspace:begin<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
    if (LucChannelIndex > ComM_GucTotalChannels)
    {
      (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
        COMM_GETCURRENTCOMMODE_SID, COMM_E_WRONG_PARAMETERS);

      /* Break While Loop */
      luctotalChnls = COMM_ZERO;

      /* Return E_NOT_OK */
      LddReturnValue = E_NOT_OK;
    }
    else
    #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
    {
      #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)
      /* polyspace<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
      if (ComM_GaaChannels[LucChannelIndex].ucBusType != COMM_INTERNAL)
      {
        /* Check the SM channel mode*/
        /* polyspace<RTE: COR : Not a defect:Justified > 
                       function pointer shall be validated in precompile time */        
        (void) ComM_GaaSMGetCurComModeFun[ComM_GaaChannels[LucChannelIndex].
          ucBusType](ComM_GaaChannels[LucChannelIndex].ddChannelId,
            &LddModePtr);

        /* Check the current Communication Mode */
        if (LddModePtr == COMM_NO_COMMUNICATION)
        {
          /* Get the lowest mode */
          *LddLowestMode = COMM_NO_COMMUNICATION;

          /* Break from while */
          luctotalChnls = COMM_ZERO;
        }
        else
        {
          /* Check for Silent comm */
          if (LddModePtr == COMM_SILENT_COMMUNICATION)
          {
            /* Get the lowest mode */
            *LddLowestMode = COMM_SILENT_COMMUNICATION;
            lucChnIdx++;
          }
          else
          {
            /* Check the next channel associated with the user */
            lucChnIdx++;
          }
        } /* End of else */
      } /* End of if (ComM_GaaChannels[LucChannelIndex].ucBusType !=
         * COMM_INTERNAL) */
      else
      #endif /* End of if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) */
      {
        /* Check the current CommunicationMode */
        if (ComM_GaaCurComMode[LucChannelIndex] == COMM_NO_COMMUNICATION)
        {
          /* Get the lowest mode */
          *LddLowestMode = COMM_NO_COMMUNICATION;

          /* Break from while */
          luctotalChnls = COMM_ZERO;
        }
        else
        {
          /* Check for Silent comm */
          if (ComM_GaaCurComMode[LucChannelIndex] == COMM_SILENT_COMMUNICATION)
          {
            /* Get the lowest mode */
            *LddLowestMode = COMM_SILENT_COMMUNICATION;
            lucChnIdx++;
          }
          else
          {
            lucChnIdx++;
          }
        } /* End of else */
      }
    }
  }
  /* polyspace:end<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
  /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Input parameters are valid, Pointer is not a NULL and Valid  */
  /* polyspace:end<RTE: OBAI : Not a defect:Justified > Its boundary is pre-defined  */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Pointer is not outside its bounds - Pointer is generated by Generator*/
  return (LddReturnValue);
} /* End of ComM_GetCurComModeDirectChnl*/

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

/*******************************************************************************
** Function Name        : ComM_PNCFullModeRequested                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve the PNC_FULL_COMMUNICATION **
**                        sub state PNC_REQUESTED                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucPncIndex                                         **
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
**                        ComM_GaaPncs, ComM_GaaPncRxERASignal,               **
**                        ComM_GaaPncRxERAn, ComM_GaaSubPNCMode,              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_PNCFullModeRequested(uint8 LucPncIndex)
{
  #if (COMM_PNC_GW_ENABLED == STD_ON)
  /* variable to store the count of signals */
  uint16 LusNoOfSignals;

  /* variable to store the start instance of signal container */
  uint16 LusSignalInsIndex;

  boolean LblERAnFlag;

  /* Initialize the condition of ERAn*/
  LblERAnFlag = COMM_FALSE;

  /* Get the Com Signals associated with the PNC*/
  LusNoOfSignals = ComM_GaaPncs[LucPncIndex].usNoOfComSignal;

  /*Com Signal Instance Index */
  LusSignalInsIndex = ComM_GaaPncs[LucPncIndex].usComSignalIndex;
  while (LusNoOfSignals != COMM_ZERO)
  {
    if (ComM_GaaPncRxERASignal[((uint16)LucPncIndex * (uint16)ComM_GucTotalSignals) + LusSignalInsIndex] == COMM_TRUE)
    {
      LblERAnFlag = COMM_TRUE;

      /* Condition to break From Loop: ERAn is !COMM_ZERO */
      LusNoOfSignals = COMM_ZERO;
    }
    else
    {
      /* Decrement the Number of channels */
      LusNoOfSignals--;
    }
    /* Increment the channel Index*/
    LusSignalInsIndex++;
  }

  /* Check for PNC state Change to : PNC_READY_SLEEP */
  if (LblERAnFlag != COMM_TRUE)
  {
    ComM_GaaPncRxERAn[LucPncIndex] = COMM_FALSE;
  }
  #endif /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */

  /* Condition to Enter : PNC_READY_SLEEP */
  if ((ComM_GaaRequestedPNCMode[LucPncIndex] == PNC_USER_NO_COMM)
      #if (COMM_PNC_GW_ENABLED == STD_ON)
      && (!(ComM_GaaPncRxERAn[LucPncIndex] == COMM_TRUE))
      #endif
      )
  {
    ComM_GaaSubPNCMode[LucPncIndex] = PNC_READY_SLEEP;

    /* Indication to BswM Module about the Sub State */
    BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucPncIndex].ddPncId,
      PNC_READY_SLEEP);
  }
} /* End of ComM_PNCFullModeRequested */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_PNCFullModeReadySleep                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve the PNC_FULL_COMMUNICATION **
**                        sub state PNC_READY_SLEEP                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucPncIndex                                         **
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
**                        ComM_GaaRequestedPNCMode, ComM_GaaPncRxERAn,        **
**                        ComM_GaaPncRxEIRASignal, ComM_GaaPncRxEIRA          **
**                        ComM_GaaChnPncInxArr, ComM_GaaChannelMapArray,      **
**                        ComM_GaaChannels, ComM_GaaPncTimeCnt                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_PNCFullModeReadySleep(uint8 LucPncIndex)
{
  /* variable to store the count of signals */
  uint16 LusNoOfSignals;

  /* variable to store the start instance of signal container */
  uint16 LusSignalInsIndex;

  /* variable to store the Channel index from channel map array */
  uint8 LucIndex;

  /* variable to store the count of channels */
  uint8 LucNoOfChannels;

  /* variable to store the start index of channel from pnc */
  NetworkHandleType LddChannelIndex;

  /* variable to store the channel ID */
  NetworkHandleType LddId;

  /* variable to check EIRA conditions */
  boolean LblEIRAFlag;

  /* Initialize the EIRA Flag */
  LblEIRAFlag = COMM_FALSE;

  /* Check for PNC state Change to : PNC_REQUESTED */
  if ((ComM_GaaRequestedPNCMode[LucPncIndex] == PNC_USER_FULL_COMM)
      #if (COMM_PNC_GW_ENABLED == STD_ON)
      || (ComM_GaaPncRxERAn[LucPncIndex] == COMM_TRUE)
      #endif
      )
  {
    ComM_GaaSubPNCMode[LucPncIndex] = PNC_REQUESTED;

    /* Indication to BswM Module about the Sub State */
    BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucPncIndex].ddPncId, PNC_REQUESTED);

  }
  /* If still state is PNC_READY_SLEEP : Check for EIRA == COMM_FALSE*/
  else
  {
    /* Get the Com Signals associated with the PNC*/
    LusNoOfSignals = ComM_GaaPncs[LucPncIndex].usNoOfComSignal;

    /*Com Signal Instance Index */
    LusSignalInsIndex = ComM_GaaPncs[LucPncIndex].usComSignalIndex;
    /* polyspace<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> condition will be executed based on the configured values */
    /* polyspace<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
    while (LusNoOfSignals != COMM_ZERO)
    {
      /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
      /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */
      if (ComM_GaaPncRxEIRASignal[((uint16)LucPncIndex * (uint16)ComM_GucTotalSignals) + LusSignalInsIndex] == COMM_TRUE)
      {
        LblEIRAFlag = COMM_TRUE;

        /* Condition to break From Loop: ERAn is !COMM_ZERO */
        LusNoOfSignals = COMM_ZERO;
      }
      else
      {
        /* Decrement the Number of channels */
        LusNoOfSignals--;
      }
      /* Increment the channel Index*/
      LusSignalInsIndex++;
    }

    /* Check for PNC state Change to : PNC_PREPARE_SLEEP */
    /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
    /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
    if (LblEIRAFlag != COMM_TRUE)
    {
      /* Reset the EIRA flag as the Channels of PNC has EIRA == COMM_FALSE */
      ComM_GaaPncRxEIRA[LucPncIndex] = COMM_FALSE;

      /* Indication to BswM Module about the Sub State */
      ComM_GaaSubPNCMode[LucPncIndex] = PNC_PREPARE_SLEEP;

      /*Indication to BswM Module*/
      BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucPncIndex].ddPncId,
        PNC_PREPARE_SLEEP);

      /* Get the Channels associated with the PNC*/
      LucNoOfChannels = ComM_GaaPncs[LucPncIndex].ucNoOfChannelPnc;

      /*Channel Index */
      LddChannelIndex = ComM_GaaPncs[LucPncIndex].ucChannelPncIndex;
      while (LucNoOfChannels != COMM_ZERO)
      {
        /* Get the Channel ID from PNC Index Array */
        /* polyspace<MISRA-C3:18.1: Not a defect: Justified> Pointer range is valid and validated by DET */
        /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
        /* polyspace<DEFECT:OUT_BOUND_ARRAY: Not a defect: Justified> Array index in range and handled by generation tool */
        LddId = ComM_GaaChnPncInxArr[LddChannelIndex];
        #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
        LucIndex = ComM_GaaChannelMapArray[LddId];
        #else
        LucIndex = LddId;
        #endif

        /* Start the PNC Timer for the channel*/
        /* #13018 */
        ComM_GaaPncTimeCnt[LucPncIndex] =
        /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
        /* polyspace<MISRA-C3:18.1:Not a defect:Justified> Pointer range is valid and validated by DET */ 
        ComM_GaaChannels[LucIndex].usPncPrepareSleepTimer;
        
        /* Decrement the Number of channels */
        LucNoOfChannels--;

        /* Increment the channel Index */
        LddChannelIndex++;
      }
    } /* End of if (LblEIRAFlag != COMM_TRUE) */
  } /* End of else */
} /* End of ComM_PNCFullModeReadySleep */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_PNCFullModePrepareSleep                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve the PNC_FULL_COMMUNICATION **
**                        sub state PNC_PREPARE_SLEEP                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucPncIndex                                         **
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
**                        ComM_GaaRequestedPNCMode, ComM_GaaChnPncInxArr,     **
**                        ComM_GaaPncs, ComM_GaaPncRxERAn, ComM_GaaSubPNCMode **
**                        ComM_GaaPncTimeCnt, ComM_GaaPncRxEIRA               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_PNCFullModePrepareSleep(uint8 LucPncIndex)
{
  /* variable to store the count of channels */
  uint8 LucNoOfChannels;

  /* variable to store the start index of channel from pnc */
  NetworkHandleType LddChannelIndex;  

  /* variable to store the track of PNC_NO_COMMUNICATION*/
  boolean LblPncNoComFlag;

  if ((ComM_GaaRequestedPNCMode[LucPncIndex] == PNC_USER_FULL_COMM)
    #if (COMM_PNC_GW_ENABLED == STD_ON)
    || (ComM_GaaPncRxERAn[LucPncIndex] == COMM_TRUE)
    #endif
    )
  {
    /* Mode Changed: PNC_PREPARE_SLEEP to PNC_REQUESTED*/
    ComM_GaaSubPNCMode[LucPncIndex] = PNC_REQUESTED;

    /* Indication to BswM Module about the Sub State */
    BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucPncIndex].ddPncId,
      PNC_REQUESTED);

    /* Get the Channels associated with the PNC*/
    LucNoOfChannels = ComM_GaaPncs[LucPncIndex].ucNoOfChannelPnc;

    /*Channel Index */
    LddChannelIndex = ComM_GaaPncs[LucPncIndex].ucChannelPncIndex;
    while (LucNoOfChannels != COMM_ZERO)
    {

      /* Decrement the Number of channels */
      LucNoOfChannels--;

      /*Reset the PNC timer for the Channel*/
      /* #13018 */      
      ComM_GaaPncTimeCnt[LucPncIndex] = COMM_ZERO;
      LddChannelIndex++;
    }
  } /* End if (ComM_GaaRequestedPNCMode[LucPncIndex] == PNC_USER_FULL_COMM) */
  else if (ComM_GaaPncRxEIRA[LucPncIndex] == COMM_TRUE)
  {
    ComM_GaaSubPNCMode[LucPncIndex] = PNC_READY_SLEEP;

    /*Indication to BswM Module*/
    BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucPncIndex].ddPncId,
      PNC_READY_SLEEP);

    /* Get the Channels associated with the PNC*/
    LucNoOfChannels = ComM_GaaPncs[LucPncIndex].ucNoOfChannelPnc;

    /*Channel Index */
    LddChannelIndex = ComM_GaaPncs[LucPncIndex].ucChannelPncIndex;
    while (LucNoOfChannels != COMM_ZERO)
    {

      /* #13018 */      
      ComM_GaaPncTimeCnt[LucPncIndex] = COMM_ZERO;

      /* Decrement the Number of channels */
      LucNoOfChannels--;

      /* Increment the channel Index */
      LddChannelIndex++;
    }
  } /* End of if (ComM_GaaPncRxEIRA[LucPncIndex] == COMM_TRUE) */
  /* If still the sub state is PNC_PREPARE_SLEEP */
  else
  {
    /* Get the Channels associated with the PNC */
    LucNoOfChannels = ComM_GaaPncs[LucPncIndex].ucNoOfChannelPnc;

    /*Channel Index */
    LddChannelIndex = ComM_GaaPncs[LucPncIndex].ucChannelPncIndex;

    /*Variable to check for condition : PNC_NO_COMMUNICATION */
    LblPncNoComFlag = COMM_FALSE;
    while (LucNoOfChannels != COMM_ZERO)
    {


      /* Decrement the Number of channels */
      LucNoOfChannels--;

      /* Check the timer status of each channel */
      /* #13018 */      
      if (ComM_GaaPncTimeCnt[LucPncIndex] != COMM_ZERO)
      {
        /* Set the Flag HIGH*/
        LblPncNoComFlag = COMM_TRUE;

        /* Break From Loop */
        LucNoOfChannels = COMM_ZERO;
      }
      else
      {
        /* Increment the channel Index */
        LddChannelIndex++;
      }
    }

    if (LblPncNoComFlag != COMM_TRUE)
    {
      ComM_GaaSubPNCMode[LucPncIndex] = PNC_NO_COMMUNICATION;

      /* Indication to BswM Module */
      BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucPncIndex].ddPncId,
        PNC_NO_COMMUNICATION);
    }
  } /* End of else */
} /* End of ComM_PNCFullModePrepareSleep */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_RequestComModePNC                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve the requested communication**
**                        mode for the PNCs associated  with users            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucUserIndex, ComMode                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : LddStdRetVal                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        ComM_GaaUsers, ComM_GaaPncUserInxArr, ComM_GaaPncs  **
**                        ComM_GaaChnPncInxArr, ComM_GaaChannelMapArray,      **
**                        ComM_GaaRequestedComMode, ComM_GaaReqedComModeCnt,  **
**                        ComM_GaaTimeCnt, ComM_GaaChannels                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_RequestComModeInhibitionCheck()                **
**                        SchM_Enter_ComM_REQ_MODECNT_PROTECTION()            **
**                        SchM_Exit_ComM_REQ_MODECNT_PROTECTION()             **
**                        ComM_RequestComModeRteUpdate()                      **
**                        ComM_PncUserHandle()                                **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComModePNC(uint8 LucUserIndex,
  ComM_ModeType ComMode)
{
  /* variable to store the Total No. of PNCs */
  uint8 LucNoOfPncs;

  /* Variable to store the user pnc index */
  uint8 LucUserPncIndex;

  /* Variable to store the pnc index */
  uint8 LucPncIndex;

  /* Variable to store the channel count for RTE Indication */
  uint8 LucChannelCount;

  /* variable to store the Total No. of Channels of the User/PNC */
  uint8 LucNoOfChannels;

  /* Index to the ComM_GaaChnInxArr/ComM_GaaChnPncInxArr Array */
  NetworkHandleType LddChannelIndex;

  /* Variable to store the channel Index */
  uint8 LucIndex;
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
  boolean LblInhibitionRetVal;
  #endif

  /* Flag to check if full/no communication request is stored in global
   *   variable */

  /* Variable to store the channel RTE Indication */
  boolean LaaChannelRteInd[COMM_TOTAL_CHANNELS];

  /* Flag to check if full/no communication request is stored in global
   *   variable */
  uint8 LucComModeReqFlag;

  /* Function Return Variable */
  Std_ReturnType LddStdRetVal;

  /* Initialize the return variable to E_OK */
  LddStdRetVal = E_OK;

  /* Initialize the request variable */
  LucComModeReqFlag = COMM_ZERO;

  /* Initialize the Channel count */
  LucChannelCount = ComM_GucTotalChannels;
  while (LucChannelCount != COMM_ZERO)
  {
    LucChannelCount--;
    LaaChannelRteInd[LucChannelCount] = COMM_FALSE;
  }
  
  /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET */
  /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
  /* Number of Pncs linked to the User */
  LucNoOfPncs = ComM_GaaUsers[LucUserIndex].ucNoOfPncUser;

  /* Pnc Index in the User */
  LucUserPncIndex = ComM_GaaUsers[LucUserIndex].ucPncUserIndex;
  while (LucNoOfPncs != COMM_ZERO)
  {
    LucNoOfPncs--;
    LucPncIndex = ComM_GaaPncUserInxArr[LucUserPncIndex];

    /* Number of Channel linked to the PNC */
    LucNoOfChannels = ComM_GaaPncs[LucPncIndex].ucNoOfChannelPnc;

    /* Index in the Channel Index array in the PNC*/
    LddChannelIndex = ComM_GaaPncs[LucPncIndex].ucChannelPncIndex;
    while (LucNoOfChannels != COMM_ZERO)
    {
      /* Decrement the Channel */
      LucNoOfChannels--;
        
      /* Get the Channel ID from Index Array */
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      LucIndex = ComM_GaaChannelMapArray[ComM_GaaChnPncInxArr[LddChannelIndex]];
      #else
      /* polyspace<DEFECT:OUT_BOUND_ARRAY::Not a defect Justified> Array index in range and handled by generation tool */
      LucIndex = ComM_GaaChnPncInxArr[LddChannelIndex];
      #endif

      /* LblChannelRteInd : To avoid multiple indication to RTE */
      /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
      /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
      if (LaaChannelRteInd[LucIndex] != COMM_TRUE)
      {
        #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
        (COMM_MODE_LIMITATION_ENABLED == STD_ON))
        LblInhibitionRetVal =
          ComM_RequestComModeInhibitionCheck(LucIndex, ComMode);

        /* If no inhibition is set */
        if (LblInhibitionRetVal == COMM_FALSE)
        #endif
        {
          /* Enter in Data Protection */
          SchM_Enter_ComM_REQ_MODECNT_PROTECTION();

          if (ComMode == COMM_FULL_COMMUNICATION)
          {
            /* If the previous request of that user is not
             *   Full communication */
            if (ComM_GaaRequestedComMode[LucUserIndex] !=
                COMM_FULL_COMMUNICATION)
            {
              /* Load the Requested Full Com Mode into the User
               *   Requested Com mode array */
              ComM_GaaRequestedComMode[LucUserIndex] = COMM_FULL_COMMUNICATION;

              /* Flag to know that the user has requested only once */
              LucComModeReqFlag = COMM_FULLCOMMREQ_ACCPTD;
            }
          } /* End of if (ComMode == COMM_FULL_COMMUNICATION) */
          else if (ComM_GaaRequestedComMode[LucUserIndex] !=
                   COMM_NO_COMMUNICATION)
          {
            /* Load the Requested No Com Mode into the User
             *   Requested Com mode array */
            ComM_GaaRequestedComMode[LucUserIndex] = COMM_NO_COMMUNICATION;

            /* Flag to know that the user has requested only once */
            LucComModeReqFlag = COMM_NOCOMMREQ_ACCPTD;
          }
          else
          {
            /* To avoid MISRA warning */
          }

          /* If the user request was accepted */
          if (LucComModeReqFlag == COMM_FULLCOMMREQ_ACCPTD)
          {
            /* Load the Requested ComMode in the Array */
            ComM_GaaReqedComModeCnt[LucIndex]++;
            #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
            (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

            /* Stop the timer if there is user request when there is no NM
             *   available */
            ComM_GaaTimeCnt[LucIndex] = (ComM_TimeType)COMM_ZERO;
            #endif
          }
          else if (LucComModeReqFlag == COMM_NOCOMMREQ_ACCPTD)
          {
            /* Load the Requested ComMode in the Array */
            ComM_GaaReqedComModeCnt[LucIndex]--;
          }
          else
          {
            /* To avoid MISRA warning */
          }
          /* Exit data protection */
          SchM_Exit_ComM_REQ_MODECNT_PROTECTION();

          /* Increment the Channel Index */
          LddChannelIndex++;
          #if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) && \
            (COMM_DIRECT_USER_MAPPING == STD_OFF))
          /* Update Rte with the user who has requested the channel */
          /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
          /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
          if (ComM_GaaChannels[LucIndex].blFullCommReqNotifEn == COMM_TRUE)
          {
            ComM_RequestComModeRteUpdate(LucIndex, LucUserIndex, ComMode);

            /* The RTE is indicated with Channel mode*/
            LaaChannelRteInd[LucIndex] = COMM_TRUE;
          }
          #endif
        }
        #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
        (COMM_MODE_LIMITATION_ENABLED == STD_ON))
        else
        {
          /* Load Return Value with COMM_E_MODE_LIMITATION */
          LddStdRetVal = COMM_E_MODE_LIMITATION;
        }
        #endif
      } /* End of if (LaaChannelRteInd[LucIndex] != COMM_TRUE) */
    } /* End of While */

    /* PNC State changes associated  with the user */
    ComM_PncUserHandle(LucPncIndex, ComMode);
    LucUserPncIndex++;
  }
  
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
  /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET */
  /* polyspace:end<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET */
  return (LddStdRetVal);
} /* End of ComM_RequestComModePNC */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_GetCurComModePNC                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to update Lowest mode of PNC for the**
**                        API ComM_GetCurComMode                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucIndex, LddLowestMode                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaUsers, ComM_GaaPncUserInxArr, ComM_GaaPncs, **
**                        ComM_GaaChnPncInxArr, ComM_GaaChannelMapArray,      **
**                        ComM_GaaChannels, ComM_GaaCurComMode                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), CanSM_GetCurrentComMode(),       **
**                        LinSM_GetCurrentComMode(), FrSM_GetCurrentComMode(),**
**                        EthSM_GetCurrentComMode()                           **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COMM_CODE) ComM_GetCurComModePNC(uint8 LucIndex, P2VAR(
    ComM_ModeType, AUTOMATIC, COMM_APPL_DATA) LddLowestMode)
{
  Std_ReturnType LddReturnValue;
  #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)

  /* Pointer to load the current mode of respective SM */
  ComM_ModeType LddModePtr = COMM_NO_COMMUNICATION;
  #endif

  /* Variable to store No of PNCs of the User */
  uint8 LucNoOfPNCs;

  /* Variable for PNC Index associated with users */
  uint8 LucUserPNCIndex;

  /* Variable for Pnc Index */
  uint8 LucPncIndex;

  /* Variable for Pnc Channel Index */
   NetworkHandleType LddPNCChannelIndex;

  /* Variable for Channel ID associated with a PNC */
  uint8 LucChannelId;

  /* Variable for Pnc Channel Index */
  uint8 LucPncChannelInx;

  /* Variable to get number of channels */
  uint8 LucNoOfChannels;

  /* Initialize the variable */
  LddReturnValue = E_OK;

  /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Input parameters are valid, Pointer is not a NULL and Valid  */
  /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET */
  /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
  /* Get the No of PNCs of the User */
  LucNoOfPNCs = ComM_GaaUsers[LucIndex].ucNoOfPncUser;

  /* PNC Index */
  LucUserPNCIndex = ComM_GaaUsers[LucIndex].ucPncUserIndex;
  /* Check the Current Communication Mode of the Each channel of each PNC */
  while (LucNoOfPNCs != COMM_ZERO)
  {
    /* Get the PNC Index from Index Array */
    LucPncIndex = ComM_GaaPncUserInxArr[LucUserPNCIndex];

    /* Decrement the Number of PNCs */
    LucNoOfPNCs--;

    /* Get the Channels associated with the PNC*/
    LucNoOfChannels = ComM_GaaPncs[LucPncIndex].ucNoOfChannelPnc;

    /*Channel Index of Pnc */
    LddPNCChannelIndex = ComM_GaaPncs[LucPncIndex].ucChannelPncIndex;
    /* Check the Current Communication Mode Each channel */
    while (LucNoOfChannels != COMM_ZERO)
    {
      /* Get the Channel ID from PNC Index Array */
      LucChannelId = ComM_GaaChnPncInxArr[LddPNCChannelIndex];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

      /* The index variable is updated with Channel */
      LucPncChannelInx = ComM_GaaChannelMapArray[LucChannelId];
      #else
      LucPncChannelInx = LucChannelId;
      #endif

      /* Decrement the Number of channels */
      LucNoOfChannels--;
      #if (COMM_DEV_ERROR_DETECT == STD_ON)
      /* polyspace<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
      /* polyspace<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
      /* Validate the channel */
      if (LucPncChannelInx > ComM_GucTotalChannels)
      {
        (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
          COMM_GETCURRENTCOMMODE_SID, COMM_E_WRONG_PARAMETERS);

        /* Break While Loop */
        LucNoOfChannels = COMM_ZERO;

        /* Return E_NOT_OK */
        LddReturnValue = E_NOT_OK;
      }
      else
      #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
      {
        #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)
        /* polyspace<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
        /* polyspace:begin<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
        if (ComM_GaaChannels[LucPncChannelInx].ucBusType != COMM_INTERNAL)
        {
          /* Check the SM channel mode*/
          (void) ComM_GaaSMGetCurComModeFun[ComM_GaaChannels[LucPncChannelInx].
            ucBusType](ComM_GaaChannels[LucPncChannelInx].ddChannelId,
            &LddModePtr);

          /* Check the current Communication Mode */
          if (LddModePtr == COMM_NO_COMMUNICATION)
          {
            /* Get the lowest mode */
            *LddLowestMode = COMM_NO_COMMUNICATION;

            /* Break from while : Channels */
            LucNoOfChannels = COMM_ZERO;

            /* Break from while : PNCs */
            LucNoOfPNCs = COMM_ZERO;
          } /* End of if (LddModePtr == COMM_NO_COMMUNICATION) */
          else
          {
            /* Check for Silent comm */
            if (LddModePtr == COMM_SILENT_COMMUNICATION)
            {
              /* Get the lowest mode */
              *LddLowestMode = COMM_SILENT_COMMUNICATION;
              LddPNCChannelIndex++;
            }
            else
            {
              /* Check the next channel associated with the user */
              LddPNCChannelIndex++;
            }
          } /* End of else */
        } /* End of if (ComM_GaaChannels[LucPncChannelInx].ucBusType !=
           *COMM_INTERNAL) */
        else
        #endif /* (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) */
        {
          /* Check the current CommunicationMode */
          if(ComM_GaaCurComMode[LucPncChannelInx] == COMM_NO_COMMUNICATION)
          {
            /* Get the lowest mode */
            *LddLowestMode = COMM_NO_COMMUNICATION;

            /* Break from while : Channels */
            LucNoOfChannels = COMM_ZERO;

            /* Break from while : PNCs */
            LucNoOfPNCs = COMM_ZERO;
          } /* End of if (ComM_GaaCurComMode[LucPncChannelInx] ==
             *COMM_NO_COMMUNICATION) */
          else
          {
            /* Check for Silent comm */
            if (ComM_GaaCurComMode[LucPncChannelInx] ==
                COMM_SILENT_COMMUNICATION)
            {
              /* Get the lowest mode */
              *LddLowestMode = COMM_SILENT_COMMUNICATION;
              LddPNCChannelIndex++;
            }
            else
            {
              LddPNCChannelIndex++;
            }
          } /* End of else */
        }
        /* polyspace:end<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
      }
    }
    LucUserPNCIndex++;
  } /* End While */
  /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
  /* polyspace:end<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET */
  /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Input parameters are valid, Pointer is not a NULL and Valid  */
  return (LddReturnValue);
} /* End of ComM_GetCurComModePNC */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  * (COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
  * STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_FullComNetwReqSubTwo                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall check other conditions than timer**
**                        expiry for full communication sub state READY SLEEP **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucIndex                                            **
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
**                        ComM_GaaChannelInhibition, ComM_GaaInhibitionReqst  **
**                        ComM_GaaReqedComModeCnt,ComM_GaaDcmActiveDiagnostic,**
**                        ComM_GaaDcmInactiveDiagnostic, ComM_GaaSubComMode,  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_FullComNetwReqSubTwo(uint8 LucIndex)
{
  /* #13017 */
  #if((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
      (COMM_ETHNETWORK_PRESENT == STD_ON))
  /* The variable is used for PNC Index */
  uint8 LucPncIndex;

  /* The variable is used for PNC Count */
  uint8 LucPncCount;

  /* The variable is used for Indexing*/
  uint8 LucSubPNCIndex;

  uint8 LucIsAllNoCom = 0;
  #endif
  #endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
          *STD_ON)) */

  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
       (COMM_ETHNETWORK_PRESENT == STD_ON))

  /* Check if the channel is part of a PNC */
  /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
  /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
  /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not a NULL and valid */
  if (ComM_GaaChannels[LucIndex].blChannelPnc == COMM_TRUE)
  {
    LucPncIndex = ComM_GaaChannels[LucIndex].ucPncIndex;
    LucPncCount = ComM_GaaChannels[LucIndex].ucPncCount;
    /*State transitions of the PNC state machines */
    while (LucPncCount != COMM_ZERO)
    {
      /* Decrement the pnc count */
      LucPncCount--;
      
      /* ComM_GaaChannelToPncMapping[] :The Map provides Index*/
      /* polyspace +2 MISRA-C3:18.1 [Not a defect:Justify with annotations] "Pointer is not outside its bounds - Pointer is generated by Generator" */
      /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
      LucSubPNCIndex = ComM_GaaChannelToPncMapping[LucPncIndex];

      /* 16521 */
      /* polyspace +2 MISRA-C3:18.1 [Not a defect:Justify with annotations] "Pointer is not outside its bounds - Pointer is generated by Generator" */
      /* polyspace<RTE:OBAI:Not a defect:Justified> Array index is in range and valid */
      if ((ComM_GaaSubPNCMode[LucSubPNCIndex] != PNC_NO_COMMUNICATION) &&
         (ComM_GaaSubPNCMode[LucSubPNCIndex] != PNC_READY_SLEEP) &&
         (ComM_GaaSubPNCMode[LucSubPNCIndex] != PNC_PREPARE_SLEEP))      
      {
        LucIsAllNoCom++;
      }
      LucPncIndex++;
    } /*End of PNC Counts of Channel*/
  } /* End of if (ComM_GaaChannels[LddChnlIndex].blChannelPnc == COMM_TRUE) */
  #endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
          *(COMM_FRNETWORK_PRESENT == STD_ON)) */
  #endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
          *STD_ON)) */


  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  if ((ComM_GaaChannelInhibition[LucIndex] &
       COMM_PREVENTWAKEUP_MASK_SET) != COMM_PREVENTWAKEUP_MASK_SET)
  #endif
  {
    #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)

    /* Check for Full Communication request during inhibition */
    if (ComM_GaaInhibitionReqst[LucIndex] != COMM_ZERO)
    {
      /* Full communication request during inhibition is loaded into
       *   request variable */
      ComM_GaaReqedComModeCnt[LucIndex] = ComM_GaaInhibitionReqst[LucIndex];
      ComM_GaaInhibitionReqst[LucIndex]--;
    }
    #endif

    /* If there is no user request */
    /* #13017 */
    /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not a NULL and valid */
    if ((ComM_GaaReqedComModeCnt[LucIndex] == COMM_ZERO)
    #if((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
    #if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||(COMM_ETHNETWORK_PRESENT == STD_ON))
        && (LucIsAllNoCom == COMM_ZERO)
    #endif
    #endif    

    )
    {
      /* If there is active diagnostic */
      if (ComM_GaaDcmActiveDiagnostic[LucIndex] == COMM_TRUE)
      {
        /* If Inactive diagnostic is called */
        if (ComM_GaaDcmInactiveDiagnostic[LucIndex] == COMM_TRUE)
        {
          /* Enter Data Protection */
          SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();
          
          /* Change sub state to Ready Sleep */
          ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_READY_SLEEP;

          /* Clear diagnostic flag */
          ComM_GaaDcmActiveDiagnostic[LucIndex] = COMM_FALSE;

          /* Clear diagnostic flag */
          ComM_GaaDcmInactiveDiagnostic[LucIndex] = COMM_FALSE;

          /* Exit Data Protection */
          SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
        }
      } /* End of if (ComM_GaaDcmActiveDiagnostic[LucIndex] == COMM_TRUE) */
                                  /* If there is no diagnostic set */
      else
      {
        /* Change sub state to Ready Sleep */
        ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_READY_SLEEP;
      }
    } /* End of if (ComM_GaaReqedComModeCnt[LucIndex] == COMM_ZERO) */
  }
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  /* If inhibition is set */
  else
  {
    /* Change sub state to Ready Sleep */
    ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_READY_SLEEP;
  }
  #endif
} /* End of ComM_FullComNetwReqSubTwo */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_FullComNetwReqSubOne                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall check the timer expiry for full  **
**                        communication sub state READY SLEEP when Nm variant **
**                        LIGHT and NONE                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucIndex                                            **
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
**                        ComM_GaaChannels,ComM_GaaTimeCnt,ComM_GaaSubComMode **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, COMM_CODE) ComM_FullComNetwReqSubOne(uint8 LucIndex)
{
  #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
  /* The Variable is used to load the Nm Light Time out of channel */
  ComM_TimeType LddTimeOut;

  /* Variable to store the Nm variant value */
  uint8 LucNmVarient;
  #endif
  /* Variable to store the flag if NM is in different mode */
  uint8 LucFlag;

  /* Clear Timer State */
  LucFlag = COMM_ZERO;

  #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
  /* Get the Nm Variant of the channel */
  /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not NULL and validated  */
  LucNmVarient = ComM_GaaChannels[LucIndex].ucNmVariant;

  /* Load the address of structure into local variable */
  LddTimeOut = ComM_GaaChannels[LucIndex].ddNmLightTimeout;
  #endif

  /* Enter Data Protection */
  SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();
  /* If the timer has not expired */
  /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not a NULL and valid */
  if (ComM_GaaTimeCnt[LucIndex] != (ComM_TimeType)COMM_ZERO)
  {
    /* Decrement the Timeout */
    ComM_GaaTimeCnt[LucIndex]--;
    LucFlag = COMM_ONE;
   
    if (ComM_GaaTimeCnt[LucIndex] == (ComM_TimeType)COMM_ZERO)
    {
      LucFlag = COMM_ZERO;
      /* Check if there is any user request            *
       * 18/Feb/2014 Kt.Kim according to redmine #572  *
       */
      /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not a NULL and valid */
      if(ComM_GaaReqedComModeCnt[LucIndex] == COMM_ZERO)
      {
        /* Change sub state to Ready Sleep */
        #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
        /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
        /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
        if (LucNmVarient == COMM_NMVARIANT_LIGHT)
        {
          /* Start the Nm light time out duration in full Communication */
          ComM_GaaTimeCnt[LucIndex] = LddTimeOut;
        }
        #endif
      }  
    } /* End of if (ComM_GaaTimeCnt[LucIndex] == (ComM_TimeType)COMM_ZERO) */
  } /* End of if (ComM_GaaTimeCnt[LucIndex] != (ComM_TimeType)COMM_ZERO) */
  /* 2014.07.10 Bug Fix #1080 by KtKim */
#if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
  /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
  /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
  else if (LucNmVarient == COMM_NMVARIANT_LIGHT)
  {
      
    /* If timer is expired reset timer if NO COMMUNICATION is
       requested.                                               */
    /* polyspace<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not a NULL and valid */
    if(ComM_GaaReqedComModeCnt[LucIndex] == COMM_ZERO)
    {
      /* Start the Nm light time out duration in full Communication */
      ComM_GaaTimeCnt[LucIndex] = LddTimeOut;
    }
  }
  else
  {

  }
#endif

  /* Exit Data Protection */
  SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
  return (LucFlag);
} /* End of ComM_FullComNetwReqSubOne */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||
        *(COMM_NONE_NMVARIANT_SUPPORT == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_COMCbk                                         **
**                                                                            **
** Service ID           : 0x61                                                **
**                                                                            **
** Description          : This service shall Receive PNC ERAn and EIRA signal **
**                      : as indicated by Com                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : SignalId                                            **
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
**                        ComM_GaaComSignal                                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), Com_ReceiveSignal(),             **
**                        ComM_ComSignalReception()                           **
*******************************************************************************/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_COMCbk(Com_SignalIdType SignalId)
{
  /*
   * Variable to Store Signal Information in ComM
   * Note: Fetched the signal length
   */
  uint8 LaaComSignalRx[PNC_COM_MAX_LENGTH];

  /* Variable used to init the com Signals */
  uint8 LucComSignalInit;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* This variable is to store the return values */
  Std_ReturnType LddReturnValue;

  #endif

  /* Init the com Signals */
  LucComSignalInit = ComM_GucPncComMaxLength;
  while (LucComSignalInit != COMM_ZERO)
  {
    /* decrement the variable */
    LucComSignalInit--;

    /* Initialize Signal Rx */
    LaaComSignalRx[LucComSignalInit] = COMM_ZERO;
  }

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Initialize the return variable to E_OK */
  LddReturnValue = E_OK;

  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check, if the module is initialized or not */
  if (ComM_GblInit == COMM_UNINIT)
  {
    /* Report to DET  */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_COMCBK_SID, COMM_E_NOT_INITED);
    LddReturnValue = COMM_E_UNINIT;
  }

  /* Check, if there is no development error occurred */
  if (LddReturnValue == E_OK)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    if (E_OK == Com_ReceiveSignal(SignalId, (void*)LaaComSignalRx))
    {
      /* Rational: A signal can have 48 PNC Information  */
      ComM_ComSignalReception(SignalId, LaaComSignalRx);
    }
  }
} /* End of ComM_COMCbk */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
        *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */
/* polyspace:end<RTE:IDP : Not a defect:Justified > This vaule is generated by Tool */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
