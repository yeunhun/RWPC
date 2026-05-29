/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Nm_Cbk.c                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : This file provides definitions of Callback APIs               **
**              Nm_NetworkStartIndication                                     **
**              Nm_NetworkMode                                                **
**              Nm_PrepareBusSleepMode                                        **
**              Nm_BusSleepMode                                               **
**              Nm_RemoteSleepIndication                                      **
**              Nm_RemoteSleepCancellation                                    **
**              Nm_SynchronizationPoint                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision      Date         By         Description                          **
********************************************************************************
** 2.3.0     30-Nov-2020   HM Shin       #26864                               **
** 2.2.0     28-Dec-2018   JeongSu Lim   #13630, #15277, #15276, #15275,      **
**                                       #15274                               **
** 1.0.2     06-Sep-2016   Kt Kim        #5954                                **
** 1.0.1     17-May-2016   Kt Kim        #4641                                **
** 1.0.0     10-Apr-2013   Kt Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion for declaration of call back functions */
#include "Nm_Cbk.h"
#include "Nm_Ram.h"
#include "Nm_PCTypes.h"
#include "Nm_Internal.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define NM_CBK_C_AR_RELEASE_MAJOR_VERSION     (4)
#define NM_CBK_C_AR_RELEASE_MINOR_VERSION     (0)
#define NM_CBK_C_AR_RELEASE_REVISION_VERSION  (3)

/* Software Version Information */
#define NM_CBK_C_SW_MAJOR_VERSION  (2)
#define NM_CBK_C_SW_MINOR_VERSION  (3)

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (NM_CBK_AR_RELEASE_MAJOR_VERSION != NM_CBK_C_AR_RELEASE_MAJOR_VERSION)
  #error "Nm_Cbk.c : Mismatch in Specification Major Version"
#endif

#if (NM_CBK_AR_RELEASE_MINOR_VERSION != NM_CBK_C_AR_RELEASE_MINOR_VERSION)
  #error "Nm_Cbk.c : Mismatch in Specification Minor Version"
#endif

#if (NM_CBK_AR_RELEASE_REVISION_VERSION != NM_CBK_C_AR_RELEASE_REVISION_VERSION)
  #error "Nm_Cbk.c : Mismatch in Specification Patch Version"
#endif

#if (NM_CBK_SW_MAJOR_VERSION != NM_CBK_C_SW_MAJOR_VERSION)
   #error "Nm_Cbk.c : Mismatch in Software Major Version"
#endif

#if (NM_CBK_SW_MINOR_VERSION != NM_CBK_C_SW_MINOR_VERSION)
   #error "Nm_Cbk.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Nm_NetworkStartIndication                           **
**                                                                            **
** Service ID           : 0x11                                                **
**                                                                            **
** Description          : This service shall notify ComM that a NM-message    **
**                        has been received in the Bus-Sleep Mode, what       **
**                        indicates that some nodes in the  network have      **
**                        entered the Network Mode. In case shutdown is       **
**                        underway, this will result in shutdown abort.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_GblInitStatus,              **
**                        Nm_GpChnlIndexArray                                 **
**                        Function(s) invoked :                               **
**                        ComM_Nm_NetworkStartIndication                      **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_NetworkStartIndication(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle)
{
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is already initialized */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_NETWORKSTARTINDICATION_SID, NM_E_UNINIT);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(nmNetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NM_INSTANCE_ID, NM_NETWORKSTARTINDICATION_SID, NM_E_HANDLE_UNDEF);
  }
  else
  {
    /* Call ComM function for this network */
    ComM_Nm_NetworkStartIndication(nmNetworkHandle);
  }
} /* End of Nm_NetworkStartIndication */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_NetworkMode                                      **
**                                                                            **
** Service ID           : 0x12                                                **
**                                                                            **
** Description          : This service shall notify the upper layer(ComM) that**
**                        the network management has entered Network Mode.    **
**                        In case coordinated shutdown is underway, this      **
**                        callback will result in aborted shutdown.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_GblInitStatus,              **
**                        Nm_GpChnlIndexArray, Nm_GaaChannelConfig,          **
**                        Nm_GaaChannelCoord_ConfigInfo, Nm_GaaClusterList,   **
**                        Nm_GaaChnlArray, Nm_GaaClusterStatusFlag,           **
**                        Nm_GaaSchMEnterFuncPtr, Nm_GaaSchMExitFuncPtr       **
**                                                                            **
**                        Function(s) invoked : ComM_Nm_NetworkMode,          **
**                        Nm_ClusterWakeUp                                    **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_NetworkMode(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle)
{
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;
  /* Index to refer to Nm_GaaChannelCoord_ConfigInfo structure */
  uint8 LucChnlCoordInfoIndex;
  /* Index to refer to Nm_Nm_GaaClusterList structure */
  uint8 LucNmClusterListInfoIndex;
  /* Local variable to store the cluster size */
  uint8 LucClusterSize;
  /* Local variable to store the cluster size */
  uint8 LucClusterStart;
  /* Local variable to store the mapping index */
  uint8 LucNmChnlMappingIndex;
  /* For saving the bus type  */
  uint8 LddChannelId;
  uint8 LucCount;

  /* Check if the NM module is already initialized */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_NETWORKMODE_SID, NM_E_UNINIT);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(nmNetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_NETWORKMODE_SID, NM_E_HANDLE_UNDEF);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_NETWORKMODE_SID, NM_E_HANDLE_UNDEF);
  }
  else
  {
    /* Get the index to Nm_GaaChannelCoord_ConfigInfo structure */
    LucChnlCoordInfoIndex = Nm_GaaChannelConfig[LddNetworkIndex].ucChnlCoordInfoIndex;
    
		/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
    if ((Nm_GblCoordinatorSupportEnabled == STD_ON) &&
        (Nm_GpClusterList != NULL_PTR) &&
        (Nm_GpChnlArray != NULL_PTR) &&
        (LucChnlCoordInfoIndex != NM_INVALID))
    {
      /* Get the index to Nm_GaaClusterList structure */
      LucNmClusterListInfoIndex = Nm_GaaChannelConfig[LddNetworkIndex].ucClusterListInfoIndex;
      /* Getting a mapping index to the array Nm_GaaChnlArray */
      LucNmChnlMappingIndex = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNmChnlMappingIndex;
      /* Get the cluster size */
      LucClusterSize = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNumOfChnls;
      /* Get the start index of the cluster */
      LucClusterStart = Nm_GpChnlArray[LucNmChnlMappingIndex];
      
      /* If the appropriate flag has been set to indicate shutdown */
			/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
      if ((Nm_GaaClusterStatusFlag[LucClusterStart] == NM_SHUTDOWN_READY) ||
          (Nm_GaaClusterStatusFlag[LucClusterStart] == NM_TIMERS_SET))
      {
        /* Enter Data Protection */
        Nm_GaaSchMEnterFuncPtr[LucClusterStart].pSchMFuncPtr();
        /* Change the status of the flag to indicate abort */
        Nm_GaaClusterStatusFlag[LucClusterStart] = NM_SHUTDOWN_ABORTED;
        /* Exit Data Protection */
        Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();

        if (Nm_GblCoordinatorSyncSupport == STD_ON)
        {
          for (LucCount = NM_ZERO; LucCount <= LucClusterSize; LucCount++)
          {
            /* Get the next channel in the cluster */
						/* polyspace +3 MISRA-C3:18.1, DEFECT:OUT_BOUND_PTR [Not a defect:Justified] "Genderated array index in range" */
            LddNetworkIndex = Nm_GpChnlArray[LucNmChnlMappingIndex + LucCount];
            /* polyspace +1 RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
            if (Nm_GaaChannelConfig[LddNetworkIndex].blActiveCoordinator == NM_TRUE)
            {
              /* Get the Channel Id */
              LddChannelId = Nm_GaaChannelConfig[LddNetworkIndex].ddChannelId;

              (void)Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_SetSleepReadyBit(LddChannelId, NM_SLEEP_BIT_RESET);
            }
            else
            {
              /* Ignore, To avoid QAC warning */
            }
          }
        }

        /* Call Nm_ClusterWakeUp with the mapping index for the cluster */
        Nm_ClusterWakeUp(LucNmChnlMappingIndex, LucClusterSize);
      }
			/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
    }
    
    /* Call the appropriate ComM function */
    ComM_Nm_NetworkMode(nmNetworkHandle);
  }
} /* End of Nm_NetworkMode */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_PrepareBusSleepMode                              **
**                                                                            **
** Service ID           : 0x13                                                **
**                                                                            **
** Description          : This service provides notification to the upper     **
**                        layer that the network has entered Prepare          **
**                        Bus Sleep Mode.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_GblInitStatus,              **
**                        Nm_GpChnlIndexArray                                **
**                                                                            **
**                        Function(s) invoked : ComM_Nm_PrepareBusSleeMode,   **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_PrepareBusSleepMode(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle)
{
  /* Local index for storing the index to to the channel config structure */
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is already initialized */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_PREPAREBUSSLEEPMODE_SID, NM_E_UNINIT);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(nmNetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NM_INSTANCE_ID, NM_PREPAREBUSSLEEPMODE_SID, NM_E_HANDLE_UNDEF);
  }
  else
  {
    /* Call ComM function for this network */
    ComM_Nm_PrepareBusSleepMode(nmNetworkHandle);
  }
} /* End of Nm_PrepareBusSleepMode */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_BusSleepMode                                     **
**                                                                            **
** Service ID           : 0x14                                                **
**                                                                            **
** Description          : Callback function for bus sleep mode indication     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_GblInitStatus,              **
**                        Nm_GpChnlIndexArray, Nm_GaaChannelConfig,          **
**                        Nm_GaaChannelCoord_ConfigInfo, Nm_GaaClusterList,   **
**                        Nm_GaaChnlArray, Nm_GaaNetworkStatusFlag,           **
**                        Nm_GaaClusterStatusFlag, Nm_GaaSchMEnterFuncPtr,    **
**                       Nm_GaaSchMExitFuncPtr                                **
**                                                                            **
**                        Function(s) invoked : ComM_Nm_BusSleepMode,         **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_BusSleepMode(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle)
{
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Index to refer to Nm_GaaChannelCoord_ConfigInfo structure */
  uint8 LucChnlCoordInfoIndex;
  /* Index to refer to Nm_Nm_GaaClusterList structure */
  uint8 LucNmClusterListInfoIndex;
  /* Local variable to store the cluster size */
  uint8 LucClusterSize;
  /* Local variable to store the cluster size */
  uint8 LucClusterStart;
  /* Local variable to store the mapping index */
  uint8 LucNmChnlMappingIndex;
  /* Count Variable */
  uint8 LucCount;
  /* Boolean variable to check if all the networks have indicated sleep */
  boolean LblSleepFlag;

  /* Check if the NM module is already initialized */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_BUSSLEEPMODE_SID, NM_E_UNINIT);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(nmNetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NM_INSTANCE_ID, NM_BUSSLEEPMODE_SID, NM_E_HANDLE_UNDEF);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NM_INSTANCE_ID, NM_BUSSLEEPMODE_SID, NM_E_HANDLE_UNDEF);
  }
  else
  {
    /* Call ComM function for this network */
    ComM_Nm_BusSleepMode(nmNetworkHandle);
		
		/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
    if ((Nm_GblCoordinatorSupportEnabled == STD_ON) && (Nm_GpClusterList != NULL_PTR) && (Nm_GpChnlArray != NULL_PTR))
    {
      /* Initialize the sleep flag */
      LblSleepFlag = NM_TRUE;
      /* Get the index to Nm_GaaChannelCoord_ConfigInfo structure */
      LucChnlCoordInfoIndex =
        Nm_GaaChannelConfig[LddNetworkIndex].ucChnlCoordInfoIndex;

      if (LucChnlCoordInfoIndex != NM_INVALID)
      {
        /* Get the index to Nm_GaaClusterList structure */
        LucNmClusterListInfoIndex = Nm_GaaChannelConfig[LddNetworkIndex].ucClusterListInfoIndex;
        /* Getting a mapping index to the array Nm_GaaChnlArray */
        LucNmChnlMappingIndex =
        Nm_GpClusterList[LucNmClusterListInfoIndex].ucNmChnlMappingIndex;
        /* Get the cluster size */
        LucClusterSize =
          Nm_GpClusterList[LucNmClusterListInfoIndex].ucNumOfChnls;
        /* Get the start index of the cluster */
        LucClusterStart = Nm_GpChnlArray[LucNmChnlMappingIndex];
        /* Enter Data Protection */
        Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
        /* Change the status of flag to indicate that bus has
         * indicated sleep
         */
        Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_SLEEP_INDICATED;
        /* Exit Data Protection */
        Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
        LucCount = NM_ZERO;
        while(LucCount <= LucClusterSize)
        {
          /* Get the channel index for the next channel in the cluster */	
					/* polyspace +3 MISRA-C3:18.1, DEFECT:OUT_BOUND_PTR [Not a defect:Justified] "Genderated array index in range" */					
          LddNetworkIndex = Nm_GpChnlArray[LucNmChnlMappingIndex + LucCount];				
					/* polyspace +1 RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
          if (Nm_GaaNetworkStatusFlag[LddNetworkIndex] == NM_SLEEP_INDICATED)
          {
            LblSleepFlag = (LblSleepFlag) & (NM_TRUE);
          }
          else
          {
            LblSleepFlag = NM_FALSE;
            LucCount = LucClusterSize;
          }
          LucCount++;
        } /* End of for loop */
        if (LblSleepFlag == NM_TRUE)
        {
          /* Enter Data Protection */
					/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
          Nm_GaaSchMEnterFuncPtr[LucClusterStart].pSchMFuncPtr();
          /*Change the cluster status to indicate that shutdown is complete*/
          Nm_GaaClusterStatusFlag[LucClusterStart] = NM_SLEEP;
          /* Exit Data Protection */
          Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();
        }
      } /* if (LucChnlCoordInfoIndex != NM_INVALID) */
    }
		/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
  }
} /* End of Nm_BusSleepMode */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_RemoteSleepIndication                            **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : Callback function for Remote sleep mode indication  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NetworkHandle                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_GblInitStatus,              **
**                        Nm_GpChnlIndexArray, Nm_GaaChannelConfig,           **
**                        Nm_GaaChannelCoord_ConfigInfo, Nm_GaaClusterList,   **
**                        Nm_GaaChnlArray, Nm_GaaNetworkStatusFlag,           **
**                        Nm_GaaClusterStatusFlag, Nm_GaaSchMEnterFuncPtr,    **
**                        Nm_GaaSchMExitFuncPtr,                              **
**                                                                            **
**                        Function(s) invoked : <BusNm>_GetState,             **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_RemoteSleepIndication(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle)
{
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  boolean LblCoordDelay;

  /* Index to refer to Nm_GaaChannelCoord_ConfigInfo structure */
  uint8 LucChnlCoordInfoIndex;
  /* Index to refer to Nm_Nm_GaaClusterList structure */
  uint8 LucNmClusterListInfoIndex;
  /* Count Variable */
  uint8 LucCount;
  /* Local variable to store the cluster size */
  uint8 LucClusterSize;
  /* Local variable to store the mapping index */
  uint8 LucNmChnlMappingIndex;
  /* Local flag to indicate if all the networks can sleep */
  boolean LblSleepFlag;
  /* Local flag to indicate if a synchronizing network is present */
  boolean LblSynchronizingNetwork;
  /* Local variable to store the cluster size */
  uint8 LucClusterStart;
  /* Variable to access the  network state */
  Nm_StateType LenState;
  /* Variable to access the network mode */
  Nm_ModeType LenMode = NM_MODE_BUS_SLEEP;
  /* Local variable to store the Channel Id */
  NetworkHandleType LddChannelId;
   /* Local variable to access Coordinator delay */

  /* Code snippet to avoid "unused parameter" warnings */
  /*
  * MISRA Rule   : 14.2
  * Message      : This statements has no side effects it can be removed.
  * Reason       : The statement is used only to avoid compilation warning.
  * Verification : However, part of the code is verified manually
  *                and it is not having any impact.
  */
  NM_UNUSED(nmNetworkHandle);

  /* Check if the NM module is already initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_REMOTESLEEPINDICATION_SID, NM_E_UNINIT);
  }
  else if ((Nm_GblRemoteSleepIndEnabled == STD_OFF) || (Nm_GblCoordinatorSupportEnabled == STD_OFF))
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_REMOTESLEEPINDICATION_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(nmNetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NM_INSTANCE_ID, NM_REMOTESLEEPINDICATION_SID, NM_E_HANDLE_UNDEF);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NM_INSTANCE_ID, NM_REMOTESLEEPINDICATION_SID, NM_E_HANDLE_UNDEF);
  }
  else
  {
    LblCoordDelay = NM_FALSE;

    if ((Nm_GpClusterList != NULL_PTR) && (Nm_GpChnlArray != NULL_PTR))
    {
      LblSleepFlag = NM_TRUE;
      LblSynchronizingNetwork = NM_FALSE;
      /* Get the index to Nm_GaaChannelCoord_ConfigInfo structure */
      LucChnlCoordInfoIndex =
        Nm_GaaChannelConfig[LddNetworkIndex].ucChnlCoordInfoIndex;
      /* If the channel belongs to a cluster */
      if (LucChnlCoordInfoIndex != NM_INVALID)
      {
        /* Get the index to Nm_GaaClusterList structure */
        LucNmClusterListInfoIndex = Nm_GaaChannelConfig[LddNetworkIndex].ucClusterListInfoIndex;
        /* Getting a mapping index to the array Nm_GaaChnlArray */
        LucNmChnlMappingIndex =
          Nm_GpClusterList[LucNmClusterListInfoIndex].ucNmChnlMappingIndex;
        /* Get the start index of the cluster */
        LucClusterStart = Nm_GpChnlArray[LucNmChnlMappingIndex];
        /* Get the size of the cluster */
        LucClusterSize =
          Nm_GpClusterList[LucNmClusterListInfoIndex].ucNumOfChnls;
        /* Change the status of the Network Status flag */
        /* If no release has occurred */
        if (Nm_GaaNetworkStatusFlag[LddNetworkIndex] == NM_NO_RELEASE)
        {
          /* Enter Data Protection */
          Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
          /*Set flag to indicate that ComM has released the network*/
          Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_BUSNM_RELEASE;
          /* Exit Data Protection */
          Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
        }
        /* If BusNm has released already */
        else if (Nm_GaaNetworkStatusFlag[LddNetworkIndex] == NM_COMM_RELEASE)
        {
          /* Enter Data Protection */
          Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
          /*Set flag to indicate that BusNm and ComM have released*/
          Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_COMM_BUSNM_RELEASE;
          /* Exit Data Protection */
          Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
        }
        else
        {
          /* To avoid QAC warning */
        }
        LucCount = NM_ZERO;
        /* For all the networks in the cluster */
        while(LucCount <= LucClusterSize)
        {
          /* Get the channel index for the next channel in the cluster */
					/* polyspace +3 MISRA-C3:18.1, DEFECT:OUT_BOUND_PTR [Not a defect:Justified] "Genderated array index in range" */
          LddNetworkIndex = Nm_GpChnlArray[LucNmChnlMappingIndex + LucCount];
          /* Get the Channel Id */
					/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */					
          LddChannelId = Nm_GaaChannelConfig[LddNetworkIndex].ddChannelId;
          /* Get the mode and state of the bus */
         (void)Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetState(LddChannelId, &LenState,
          &LenMode);
          /* If the bus is already in Bus-Sleep Mode */
          if ((LenMode == NM_MODE_BUS_SLEEP) &&
              (Nm_GaaNetworkStatusFlag[LddNetworkIndex] != NM_SLEEP_INDICATED))
          {
            /* Enter Data Protection */
            Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
            Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_SLEEP_INDICATED;
            /* Exit Data Protection */
            Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
          }

          /* Checking if atleast one network is a Synchronizing Network */
          if ((Nm_GaaChannelConfig[LddNetworkIndex].blSynchronizingNetwork == NM_TRUE) && (LblSynchronizingNetwork == NM_FALSE))
          {
            /* Set the flag to true */
            LblSynchronizingNetwork = NM_TRUE;
          }
          /* Checking if all the networks have been released */
         if ((Nm_GaaNetworkStatusFlag[LddNetworkIndex] != NM_COMM_BUSNM_RELEASE) &&
             (Nm_GaaNetworkStatusFlag[LddNetworkIndex] != NM_SLEEP_INDICATED))
          {
            LblSleepFlag = NM_FALSE;
            LucCount = LucClusterSize;
          }
          LucCount++;
        } /* End for loop */
        /* If the cluster is ready to sleep */
        if (LblSleepFlag == NM_TRUE)
        {
          if (Nm_GblCoordinatorSyncSupport == STD_ON)
          {
            for(LucCount = NM_ZERO; LucCount < LucClusterSize; LucCount++)
            {
              /* Get the next channel in the cluster */
              LddNetworkIndex = Nm_GpChnlArray[LucNmChnlMappingIndex + LucCount];
							
							/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
              if (Nm_GaaChannelConfig[LddNetworkIndex].blActiveCoordinator == NM_TRUE)
              {
                 /* Get the Channel Id */
                LddChannelId = Nm_GaaChannelConfig[LddNetworkIndex].ddChannelId;

                (void)Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_SetSleepReadyBit(LddChannelId, NM_SLEEP_BIT_SET);

                 LblCoordDelay = NM_TRUE;
                 LblSynchronizingNetwork = NM_FALSE;
              }
            }
            if (LblCoordDelay == NM_TRUE)
            {
              /* Set the Co-Ordinator delay timer */
							/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
              Nm_GaaCoordDelayTimer[LucClusterStart] = Nm_GpClusterList[LucNmClusterListInfoIndex].usCoordDelayTimer;

              /* Set the cluster */
              Nm_GaaClusterStatusFlag[LucClusterStart] = NM_COORD_DELAY;
            }
          }

          /* If no network is a Synchronizing Network */
          if ((LblSynchronizingNetwork == NM_FALSE) && (LblCoordDelay == NM_FALSE))
          {
            /* For the entire cluster */
            for(LucCount = NM_ZERO; LucCount < LucClusterSize; LucCount++)
            {
              /* Get the next channel in the cluster */
              LddNetworkIndex =
                Nm_GpChnlArray[LucNmChnlMappingIndex + LucCount];

              /* Set the shutdown delay timers */
							/* polyspace +2 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
              Nm_GaaShutdownTimer[LddNetworkIndex] =
                Nm_GaaChannelConfig[LddNetworkIndex].ulShutdownDelayTimerTick;
            }
            /* Enter Data Protection */
						/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
            Nm_GaaSchMEnterFuncPtr[LucClusterStart].pSchMFuncPtr();
            /*Set the shutdown flag to indicate that timers are set*/
            Nm_GaaClusterStatusFlag[LucClusterStart] = NM_TIMERS_SET;
            /* Exit Data Protection */
            Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();
          }
          else if (LblSynchronizingNetwork == NM_TRUE)
          { 
            /* Enter Data Protection */
						/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
             Nm_GaaSchMEnterFuncPtr[LucClusterStart].pSchMFuncPtr();
             /*If there is a synchronizing network do not set the timers*/
             Nm_GaaClusterStatusFlag[LucClusterStart] = NM_SHUTDOWN_READY;
             /* Exit Data Protection */
             Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();
           }
          else
          {
            
          }
        } /* if (LblSleepFlag == NM_TRUE) */
      } /* if (LucChnlCoordInfoIndex != NM_INVALID) */
    }
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
} /* End of Nm_RemoteSleepIndication */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_RemoteSleepCancellation                          **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : Callback function for Remote sleep mode indication  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_GblInitStatus,              **
**                        Nm_GpChnlIndexArray, Nm_GaaChannelConfig,          **
**                        Nm_GaaChannelCoord_ConfigInfo, Nm_GaaClusterList,   **
**                        Nm_GaaChnlArray, Nm_GaaClusterStatusFlag            **
**                        Nm_GaaSchMEnterFuncPtr,  Nm_GaaSchMExitFuncPtr      **
**                                                                            **
**                        Function(s) invoked : Nm_ClusterWakeUp,             **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_RemoteSleepCancellation(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle)
{
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;
  /* Index to refer to Nm_GaaChannelCoord_ConfigInfo structure */
  uint8 LucChnlCoordInfoIndex;
  /* Index to refer to Nm_Nm_GaaClusterList structure */
  uint8 LucNmClusterListInfoIndex;
  /* Local variable to store the cluster size */
  uint8 LucClusterSize;
  /* Local variable to store the cluster size */
  uint8 LucClusterStart;
  /* Local variable to store the mapping index */
  uint8 LucNmChnlMappingIndex;
  uint8 LddChannelId;
  uint8 LucCount;

  /* Code snippet to avoid "unused parameter" warnings */
  /*
  * MISRA Rule   : 14.2
  * Message      : This statements has no side effects it can be removed.
  * Reason       : The statement is used only to avoid compilation warning.
  * Verification : However, part of the code is verified manually
  *                and it is not having any impact.
  */
  NM_UNUSED(nmNetworkHandle);

  /* Check if the NM module is already initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_REMOTESLEEPCANCELLATION_SID, NM_E_UNINIT);
  }
  else if ((Nm_GblRemoteSleepIndEnabled == STD_OFF) || (Nm_GblCoordinatorSupportEnabled == STD_OFF))
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_REMOTESLEEPCANCELLATION_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(nmNetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_REMOTESLEEPCANCELLATION_SID, NM_E_HANDLE_UNDEF);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_REMOTESLEEPCANCELLATION_SID, NM_E_HANDLE_UNDEF);
  }
  else
  {
    if ((Nm_GpClusterList != NULL_PTR) && (Nm_GpChnlArray != NULL_PTR))
    {
      LucChnlCoordInfoIndex =
      Nm_GaaChannelConfig[LddNetworkIndex].ucChnlCoordInfoIndex;

      /* If the channel belongs to a cluster */
      if (LucChnlCoordInfoIndex != NM_INVALID)
      {
        /* Get the index to Nm_GaaClusterList structure */
        LucNmClusterListInfoIndex = Nm_GaaChannelConfig[LddNetworkIndex].ucClusterListInfoIndex;
        /* Getting a mapping index to the array Nm_GaaChnlArray */
        LucNmChnlMappingIndex =
          Nm_GpClusterList[LucNmClusterListInfoIndex].ucNmChnlMappingIndex;
        /* Get the cluster size */
        LucClusterSize =
          Nm_GpClusterList[LucNmClusterListInfoIndex].ucNumOfChnls;
        /* Get the start index of the cluster */
        LucClusterStart = Nm_GpChnlArray[LucNmChnlMappingIndex];
        /* If the appropriate flag has been set to indicate shutdown */
				/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */	
        if ((Nm_GaaClusterStatusFlag[LucClusterStart] == NM_SHUTDOWN_READY) ||
            (Nm_GaaClusterStatusFlag[LucClusterStart] == NM_TIMERS_SET) ||
            (Nm_GaaClusterStatusFlag[LucClusterStart] == NM_COORD_DELAY))
        {
          /* Enter Data Protection */
          Nm_GaaSchMEnterFuncPtr[LucClusterStart].pSchMFuncPtr();
          /*Change the status of the flag to indicate abort*/
          Nm_GaaClusterStatusFlag[LucClusterStart] = NM_SHUTDOWN_ABORTED;
          /* Exit Data Protection */
          Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();

          if (Nm_GblCoordinatorSyncSupport == STD_ON)
          {
            for (LucCount = NM_ZERO; LucCount <= LucClusterSize; LucCount++)
            {
              /* Get the next channel in the cluster */
							/* polyspace +3 MISRA-C3:18.1, DEFECT:OUT_BOUND_PTR [Not a defect:Justified] "Genderated array index in range" */
              LddNetworkIndex = Nm_GpChnlArray[LucNmChnlMappingIndex + LucCount];
							/* polyspace +1 RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */							
              if (Nm_GaaChannelConfig[LddNetworkIndex].blActiveCoordinator == NM_TRUE)
              {
                /* Get the Channel Id */
                LddChannelId = Nm_GaaChannelConfig[LddNetworkIndex].ddChannelId;

                (void)Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_SetSleepReadyBit(LddChannelId, NM_SLEEP_BIT_RESET);
              }
              else
              {
                /* Ignore, To avoid QAC warning */
              }
            }
          }

          /* Call Nm_ClusterWakeUp with the mapping index for the cluster */
          Nm_ClusterWakeUp(LucNmChnlMappingIndex, LucClusterSize);
        }
      } /* if (LucChnlCoordInfoIndex != NM_INVALID) */
    }
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
} /* End of Nm_RemoteCancellation */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_SynchronizationPoint                             **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : Callback function for Remote sleep mode indication  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : nmNetworkHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Nm Module should be initialized                     **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_GblInitStatus,              **
**                        Nm_GpChnlIndexArray, Nm_GaaChannelConfig,           **
**                        Nm_GaaChannelCoord_ConfigInfo, Nm_GaaClusterList,   **
**                        Nm_GaaChnlArray, Nm_GaaClusterStatusFlag            **
**                        Nm_GaaSchMEnterFuncPtr,  Nm_GaaSchMExitFuncPtr      **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_SynchronizationPoint(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle)
{
  /* Code snippet to avoid "unused parameter" warnings */
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Index to refer to Nm_GaaChannelCoord_ConfigInfo structure */
  uint8 LucChnlCoordInfoIndex;
  /* Index to refer to Nm_Nm_GaaClusterList structure */
  uint8 LucNmClusterListInfoIndex;
  /* Count Variable */
  uint8 LucCount;
  /* Local variable to store the cluster size */
  uint8 LucClusterSize;
  /* Local variable to store the cluster size */
  uint8 LucClusterStart;
  /* Local variable to store the mapping index */
  uint8 LucNmChnlMappingIndex;

  /* Check if the NM module is already initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_SYNCHRONIZATIONPOINT_SID, NM_E_UNINIT);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(nmNetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_SYNCHRONIZATIONPOINT_SID, NM_E_HANDLE_UNDEF);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_SYNCHRONIZATIONPOINT_SID, NM_E_HANDLE_UNDEF);
  }
  else if (Nm_GblCoordinatorSupportEnabled == STD_OFF)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_SYNCHRONIZATIONPOINT_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    if ((Nm_GpClusterList != NULL_PTR) && (Nm_GpChnlArray != NULL_PTR))
    {
      /* Get the index to Nm_GaaChannelCoord_ConfigInfo structure */
      LucChnlCoordInfoIndex = Nm_GaaChannelConfig[LddNetworkIndex].ucChnlCoordInfoIndex;
      
      if (LucChnlCoordInfoIndex != NM_INVALID)
      {
        /* Get the index to Nm_GaaClusterList structure */
        LucNmClusterListInfoIndex = Nm_GaaChannelConfig[LddNetworkIndex].ucClusterListInfoIndex;
        /* Getting a mapping index to the array Nm_GaaChnlArray */
        LucNmChnlMappingIndex = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNmChnlMappingIndex;
        /* Get the cluster size */
        LucClusterSize = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNumOfChnls;
        /* Get the start index of the cluster */
        LucClusterStart = Nm_GpChnlArray[LucNmChnlMappingIndex];
        
        /* If the network is configured as a synchronizing network */
        if (Nm_GaaChannelConfig[LddNetworkIndex].blSynchronizingNetwork == NM_TRUE)
        {
          /* If shutdown has been initiated */
					/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
          if (Nm_GaaClusterStatusFlag[LucClusterStart] == NM_SHUTDOWN_READY)
          {
            for (LucCount = NM_ZERO; LucCount < LucClusterSize; LucCount++)
            {
              /* Get the next channel in the cluster */
              LddNetworkIndex = Nm_GpChnlArray[LucNmChnlMappingIndex + LucCount];
              /* Set the shutdown delay timers */
							/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
              Nm_GaaShutdownTimer[LddNetworkIndex] = Nm_GaaChannelConfig[LddNetworkIndex].ulShutdownDelayTimerTick;
            }
            /* Enter Data Protection */
            Nm_GaaSchMEnterFuncPtr[LucClusterStart].pSchMFuncPtr();
            /* Change the status of the flag to indicate timers are set */
            Nm_GaaClusterStatusFlag[LucClusterStart] = NM_TIMERS_SET;
            /* Exit Data Protection */
            Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();
          }
        } /* If the network is configured as a synchronizing network */
      } /* if (LucChnlCoordInfoIndex != NM_INVALID) */
    }
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
} /* End of Nm_SynchronizationPoint */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
 **                          END OF FILE                                      **
 ******************************************************************************/
