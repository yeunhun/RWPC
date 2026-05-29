/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Nm.c                                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : This file provides definitions of following Nm APIs:          **
**              Nm_Init                                                       **
**              Nm_MainFunction                                               **
**              Nm_GetVersionInfo                                             **
**              Nm_PassiveStartUp                                             **
**              Nm_NetworkRequest                                             **
**              Nm_NetworkRelease                                             **
**              Nm_DisableCommunication                                       **
**              Nm_EnableCommunication                                        **
**              Nm_SetUserData                                                **
**              Nm_GetUserData                                                **
**              Nm_GetPduData                                                 **
**              Nm_RepeatMessageRequest                                       **
**              Nm_GetNodeIdentifier                                          **
**              Nm_GetLocalNodeIdentifier                                     **
**              Nm_CheckRemoteSleepIndication                                 **
**              Nm_GetState                                                   **
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
#include "Nm.h" /* Inclusion of Nm Header File */
#include "Nm_PCTypes.h" /* Inclusion for declaration  of structure types */
#include "Nm_Ram.h" /* Inclusion for global variables */
#include "Nm_Internal.h"  /* Inclusion of Internal Functions */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define NM_C_AR_RELEASE_MAJOR_VERSION     (4)
#define NM_C_AR_RELEASE_MINOR_VERSION     (0)
#define NM_C_AR_RELEASE_REVISION_VERSION  (3)

/* Software Version Information */
#define NM_C_SW_MAJOR_VERSION  (2)
#define NM_C_SW_MINOR_VERSION  (3)

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (NM_AR_RELEASE_MAJOR_VERSION != NM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Nm.c : Mismatch in Specification Major Version"
#endif

#if (NM_AR_RELEASE_MINOR_VERSION != NM_C_AR_RELEASE_MINOR_VERSION)
  #error "Nm.c : Mismatch in Specification Minor Version"
#endif

#if (NM_AR_RELEASE_REVISION_VERSION != NM_C_AR_RELEASE_REVISION_VERSION)
  #error "Nm.c : Mismatch in Specification Patch Version"
#endif

#if (NM_SW_MAJOR_VERSION != NM_C_SW_MAJOR_VERSION)
  #error "Nm.c : Mismatch in Software Major Version"
#endif

#if (NM_SW_MINOR_VERSION != NM_C_SW_MINOR_VERSION)
  #error "Nm.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Nm_Init                                             **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This service initializes the NM module.             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : This service function has to be called after the    **
**                        initialization of the respective bus interface.     **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus              **
**                          Nm_GaaClusterStatusFlag, Nm_GaaNetworkStatusFlag  **
**                          Nm_GaaShutdownTimer                               **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_Init(void)
{
  uint8 LucCount;
  
  for(LucCount = 0;LucCount < Nm_GucNumberOfChannels;LucCount++)
  {
    Nm_GaaClusterStatusFlag[LucCount] = NM_SLEEP;
    Nm_GaaNetworkStatusFlag[LucCount] = NM_NO_RELEASE;
    Nm_GaaShutdownTimer[LucCount] = NM_TIMER_RESET;
  }
  
  /* Set the global variable value TRUE */
  Nm_GblInitStatus = NM_TRUE;  
} /* End of Nm_Init */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_MainFunction                                     **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This function implements the processes of the NM    **
**                        Interface which need a fix cyclic scheduling. The   **
**                        evaluation of shutdown timers is done in this       **
**                        function.                                           **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Timing               : Fixed Cyclic                                        **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : This service function has to be called after the    **
**                        initialization of the respective bus interface.     **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GaaChannelConfig,          **
**                        Nm_GaaChannelCoord_ConfigInfo, Nm_GaaClusterList,   **
**                        Nm_GaaChnlArray,                                    **
**                        Nm_GaaShutdownTimer, Nm_GaaClusterStatusFlag,       **
**                        Nm_GaaSchMEnterFuncPtr, Nm_GaaSchMExitFuncPtr       **
**                                                                            **
**                        Function(s) invoked : <BusNm>_NetworkRelease()      **
**                        Nm_ClusterWakeUp()                                  **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
/* polyspace +1 MISRA-C3:8.4 [Not a defect: Justified] "It will call from RTE" */
FUNC(void, NM_CODE) Nm_MainFunction(void)
{
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;
  /*Variable to hold the Return Value */
  Std_ReturnType LenReturnVal;
  /* Index to refer to Nm_GaaClusterList structure */
  uint8 LucNmClusterListInfoIndex;
  /* Count variable */
  uint8 LucCount;
  /* Cluster Count variable */
  uint8 LucClusterCount;
  /* Local variable to store the cluster size */
  uint8 LucClusterSize;
  /* Local variable to store the mapping index */
  uint8 LucNmChnlMappingIndex;
  boolean LblSynchronizingNetwork;
  uint8 LucClusterStart;

  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NM_INSTANCE_ID, NM_MAINFUNCTION_SID, NM_E_UNINIT);
  }
  else
  {
    /* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */ 
    if ((Nm_GblCoordinatorSupportEnabled == STD_ON) && (Nm_GpClusterList != NULL_PTR) && (Nm_GpChnlArray != NULL_PTR))
    {
      /* For all the possible clusters */
      for(LucClusterCount = NM_ZERO; LucClusterCount < Nm_GucNumberOfChannels; LucClusterCount++)
      {
        if ((Nm_GblCoordinatorSyncSupport == STD_ON) && (Nm_GaaClusterStatusFlag[LucClusterCount] == NM_COORD_DELAY))
        {
          Nm_GaaCoordDelayTimer[LucClusterCount]--;
          
          if (Nm_GaaCoordDelayTimer[LucClusterCount] == NM_ZERO)
          {
            /* Check if any network is a synchronizing network */
            /* Initialize flag that indicates if synchronization
               indication is needed */
            LblSynchronizingNetwork = NM_FALSE;
            /* Get the index to Nm_GaaClusterList structure */
            LucNmClusterListInfoIndex = Nm_GaaChannelConfig[LucClusterCount].ucClusterListInfoIndex;
            /* Getting a mapping index to the array Nm_GaaChnlArray */
            LucNmChnlMappingIndex = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNmChnlMappingIndex;
             /* Get the size of the cluster */
            LucClusterSize = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNumOfChnls;

            /* Get the start index of the cluster */
            LucClusterStart = Nm_GpChnlArray[LucNmChnlMappingIndex];

            /* Checking if atleast one network is a Synchronizing Network */
            if (Nm_GaaChannelConfig[LucClusterCount].blSynchronizingNetwork == NM_TRUE)
            {
              /* Set the flag to true */
              LblSynchronizingNetwork =  NM_TRUE;
              /* MISRA Rule         : 13.6
               * Message            : Count variable, LucCount, modified in
               *                      body of loop
               * Reason             : This is done to break out of the loop
               * Verification       : However, part of the code is verified
               *                      manually and it is not having any impact
               */

            }
            /* polyspace-begin MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
            if (LblSynchronizingNetwork == NM_FALSE)
            {
              /* For the entire cluster */
              for(LucCount = NM_ZERO; LucCount < LucClusterSize; LucCount++)
              {
                /* Get the next channel in the cluster */
                LddNetworkIndex = Nm_GpChnlArray[LucNmChnlMappingIndex + LucCount];
                /* Set the shutdown delay timers */
                Nm_GaaShutdownTimer[LddNetworkIndex] = Nm_GaaChannelConfig[LddNetworkIndex].ulShutdownDelayTimerTick;
              } /*  End of for loop */
              
              /* Enter Data Protection */
              Nm_GaaSchMEnterFuncPtr[LucClusterStart].pSchMFuncPtr();
              /* Set the shutdown flag to indicate that timers are set */
              Nm_GaaClusterStatusFlag[LucClusterStart] = NM_TIMERS_SET;
              /* Exit Data Protection */
              Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();
            } /* End of if (LblSynchronizingNetwork == NM_FALSE) */
            else
            {
              /* Enter Data Protection */
              Nm_GaaSchMEnterFuncPtr[LucClusterStart].pSchMFuncPtr();
              /* If there is a synchronizing network do not set the timers */
              Nm_GaaClusterStatusFlag[LucClusterStart] = NM_SHUTDOWN_READY;
              /* Exit Data Protection */
              Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();
            }
						/* polyspace-end MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
          }
        }
        
        /* If shutdown has been initiated and timers have been set */
        if (Nm_GaaClusterStatusFlag[LucClusterCount] == NM_TIMERS_SET)
        {
          /* Get the index to Nm_GaaClusterList structure */
          LucNmClusterListInfoIndex = Nm_GaaChannelConfig[LucClusterCount].ucClusterListInfoIndex;
          /* Getting a mapping index to the array Nm_GaaChnlArray */
          LucNmChnlMappingIndex = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNmChnlMappingIndex;
          /* Get the size of the cluster */
          LucClusterSize = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNumOfChnls;
          /* Variable to store return value from Network Releases */
          LenReturnVal = E_OK;
          
          LucCount = NM_ZERO;
          
          /* For all the networks in the cluster */
          while(LucCount < LucClusterSize)
          {
            /* Get the index to the networks in the cluster */
            LddNetworkIndex = Nm_GpChnlArray[LucNmChnlMappingIndex + LucCount];
						/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
            if (Nm_GaaNetworkStatusFlag[LddNetworkIndex] == NM_COMM_BUSNM_RELEASE)
            {
              /* If the timer has elapsed and the bus is not already asleep */
              if (Nm_GaaShutdownTimer[LddNetworkIndex] == 0x0000)
              {
                /* Enter Data Protection */
                Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
                /* Exit Data Protection */
                Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
                
                if (Nm_GblBusSynchronizationEnabled == STD_ON)
                {
                  /* Call BusNm_RequestSynchronization */
                  (void)Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_RequestBusSynchronization(LddNetworkIndex);
                }
                
                /* Release the bus */								
								/* polyspace +1 RTE:COR [Not a defect:Justified] "Configured function pointer" */
                LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_NetworkRelease(LddNetworkIndex);
                /* Enter Data Protection */
                Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
                Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_NO_RELEASE;
                /* Exit Data Protection */
                Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
              }
              else
              {
                /* Decrement the timer */
                Nm_GaaShutdownTimer[LddNetworkIndex]--;
              }
            }
            /* Only if the return value from BusNm_NetworkRelease() is NOT OK */
            if (LenReturnVal == E_NOT_OK)
            {
              /* Enter Data Protection */
              Nm_GaaSchMEnterFuncPtr[LucClusterCount].pSchMFuncPtr();
              /* Indicate Aborted Shutdown */
              Nm_GaaClusterStatusFlag[LucClusterCount] = NM_SHUTDOWN_ABORTED;
              /* Exit Data Protection */
              Nm_GaaSchMExitFuncPtr[LucClusterCount].pSchMFuncPtr();
              /* Wake up the entire cluster by calling Nm_ClusterWakeUp() */
              Nm_ClusterWakeUp(LucNmChnlMappingIndex, LucClusterSize);
              LucCount = LucClusterSize;
            }
            LucCount++;
          }
        } /* end if (Nm_GaaClusterStatusFlag[LucClusterCount] == NM_TIMERS_SET) */
      } /* end of for loop */
    }
		/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
  } /* end of if (Nm_GblInitStatus == NM_INIT) */
} /* End of Nm_MainFunction */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_PassiveStartup()                                 **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This network is responsible for the passive startup **
**                        of the lower BusNm layer. If the node is a          **
**                        coordinator, Nm_PassiveStartup() is treated as      **
**                        Nm_NetworkRequest(). Hence, in case shutdown is     **
**                        aborted, the entire cluster will be kept requested. **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GpChnlIndexArray, Nm_GaaChannelConfig,           **
**                        Nm_GaaChannelCoord_ConfigInfo, Nm_GaaClusterList,   **
**                        Nm_GaaChnlArray, Nm_GaaClusterStatusFlag,           **
**                        Nm_GaaSchMEnterFuncPtr, Nm_GaaSchMExitFuncPtr       **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_PassiveStartUp,       **
**                        <BusNm>_NetworkRequest                              **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_PassiveStartUp(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle)
{
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Index to refer to Nm_GaaChannelCoord_ConfigInfo structure */
  uint8 LucChnlCoordInfoIndex;
  /* Index to refer to Nm_Nm_GaaClusterList structure */
  uint8 LucNmClusterListInfoIndex;
  /* Local variable to store the cluster size */
  uint8 LucClusterSize;
  /* Local variable to store the cluster starting index */
  uint8 LucClusterStart;
  /* Local variable to store the mapping index */
  uint8 LucNmChnlMappingIndex;
  uint8 LddChannelId;
  uint8 LucCount;

  /* Local variable to store return value */
  Std_ReturnType LenReturnVal = E_OK;
  
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_PASSIVESTARTUP_SID, NM_E_UNINIT);

    /* Set the Return value to not OK */
    LenReturnVal = E_NOT_OK;
  }
  else if (Nm_IntGetChannelIndexFromChannelId(NetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_PASSIVESTARTUP_SID, NM_E_HANDLE_UNDEF);

    /* Set the Return value to not OK */
    LenReturnVal = E_NOT_OK;
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_PASSIVESTARTUP_SID, NM_E_HANDLE_UNDEF);

    /* Set the Return value to not OK */
    LenReturnVal = E_NOT_OK;
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_PassiveStartUp == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_PASSIVESTARTUP_SID, NM_E_INVALID_REQUEST);

    /* Set the Return value to not OK */
    LenReturnVal = E_NOT_OK;
  }
  else
  {
		/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
    if ((Nm_GblCoordinatorSupportEnabled == STD_ON) && (Nm_GpClusterList != NULL_PTR) && (Nm_GpChnlArray != NULL_PTR))
    {
      /* Get the index to Nm_GaaChannelCoord_ConfigInfo structure */
      LucChnlCoordInfoIndex =
        Nm_GaaChannelConfig[LddNetworkIndex].ucChnlCoordInfoIndex;
      /* Call BusNm_NetworkRequest for this network */
			/* polyspace +1 RTE:COR [Not a defect:Justified] "Configured function pointer" */
      LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_NetworkRequest(NetworkHandle);
      if (LenReturnVal == E_OK)
      {
        /* Enter Data Protection */
        Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();

        /* Change the status of the network */
        Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_NO_RELEASE;

        /* Exit Data Protection */
        Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
      }
      else if (LenReturnVal == E_NOT_OK)
      {
        /* Enter Data Protection */
        Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();

        /* Change the status of the network */
        Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_SLEEP_INDICATED;

        /* Exit Data Protection */
        Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
      }
      else
      {
        /* For MISRA Compliance */
      }
      /* If the channel belongs to a cluster */
      if (LucChnlCoordInfoIndex != NM_INVALID)
      {
        /* Get the index to Nm_GaaClusterList structure */
        LucNmClusterListInfoIndex = Nm_GaaChannelConfig[LddNetworkIndex].ucClusterListInfoIndex;
        /* Getting a mapping index to the array Nm_GaaChnlArray */
        LucNmChnlMappingIndex = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNmChnlMappingIndex;
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
          /* Change the status of the flag to indicate abort */
          Nm_GaaClusterStatusFlag[LucClusterStart] = NM_SHUTDOWN_ABORTED;
          /* Exit Data Protection */
          Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();
          
          if (Nm_GblCoordinatorSyncSupport == STD_ON)
          {
            for (LucCount = NM_ZERO; LucCount <= LucClusterSize ; LucCount++)
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
      /* If the channel does not belong to a cluster */
      else
      {
        /* Call BusNm_PassiveStartUp for this network */
        LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_PassiveStartUp(NetworkHandle);
      }
    }
    else
    {
      /* Call BusNm_PassiveStartUp for this network */
      LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_PassiveStartUp(NetworkHandle);
    }
		/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
  }
  
  return(LenReturnVal);
} /* End of Nm_PassiveStartUp */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_GetVersionInfo                                   **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : This function returns the version information of the**
**                        Nm Module.                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : NmVerInfoPtr                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, NM_CODE) Nm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, NM_APPL_DATA) NmVerInfoPtr)
{
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblVersionInfoApi == STD_OFF)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NM_INSTANCE_ID, NM_GETVERSIONINFO_SID, NM_E_INVALID_REQUEST);
  }
  else if (NmVerInfoPtr == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NM_INSTANCE_ID, NM_GETVERSIONINFO_SID, NM_E_PARAM_POINTER);
  }
  else
  {
    /* Copy the vendor Id */
		/* polyspace +1 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
    NmVerInfoPtr->vendorID = NM_VENDOR_ID;
    /* Copy the module Id */
    NmVerInfoPtr->moduleID = NM_MODULE_ID;
    /* Copy Software Major Version */
    NmVerInfoPtr->sw_major_version = NM_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    NmVerInfoPtr->sw_minor_version = NM_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    NmVerInfoPtr->sw_patch_version = NM_SW_PATCH_VERSION;
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
} /* End of Nm_GetVersionInfo */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_NetworkRequest()                                 **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This service requests the appropriate lower BusNm   **
**                        Network. If the node is a coordinator, the entire   **
**                        cluster is requested.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GpChnlIndexArray, Nm_GaaChannelConfig,           **
**                        Nm_GaaChannelCoord_ConfigInfo, Nm_GaaClusterList,   **
**                        Nm_GaaChnlArray, Nm_GaaClusterStatusFlag,           **
**                        Nm_GaaSchMEnterFuncPtr, Nm_GaaSchMExitFuncPtr       **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_NetworkRequest,       **
**                        Nm_ClusterWakeUp                                    **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRequest(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle)
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

  /* Local variable to store return value */
  Std_ReturnType LenReturnVal;

  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_NETWORKREQUEST_SID, NM_E_UNINIT);

    /* Set the Return value to not Ok */
    LenReturnVal = E_NOT_OK;
  }
  else if (Nm_IntGetChannelIndexFromChannelId(NetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_NETWORKREQUEST_SID, NM_E_HANDLE_UNDEF);

    /* Set the Return value to not Ok */
    LenReturnVal = E_NOT_OK;
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_NETWORKREQUEST_SID, NM_E_HANDLE_UNDEF);

    /* Set the Return value to not Ok */
    LenReturnVal = E_NOT_OK;
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].blPassiveModeEnabled == NM_TRUE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_NETWORKREQUEST_SID, NM_E_INVALID_REQUEST);

    /* Set the Return value to not Ok */
    LenReturnVal = E_NOT_OK;
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_NetworkRequest == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_NETWORKREQUEST_SID, NM_E_INVALID_REQUEST);

    /* Set the Return value to not Ok */
    LenReturnVal = E_NOT_OK;
  }
  else
  {
		/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
    if ((Nm_GblCoordinatorSupportEnabled == STD_ON) && (Nm_GpClusterList != NULL_PTR) && (Nm_GpChnlArray != NULL_PTR))
    {
      /* Get the index to Nm_GaaChannelCoord_ConfigInfo structure */
      LucChnlCoordInfoIndex =
        Nm_GaaChannelConfig[LddNetworkIndex].ucChnlCoordInfoIndex;
      /* Call BusNm_NetworkRequest for this network */
      LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_NetworkRequest(NetworkHandle);
      if (LenReturnVal == E_OK)
      {
        /* Exit Data Protection */
        Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
        /* Change the status of the network */
        Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_NO_RELEASE;
        /* Exit Data Protection */
        Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
      }
      else if (LenReturnVal == E_NOT_OK)
      {
        /* Exit Data Protection */
        Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
        /* Change the status of the network */
        Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_SLEEP_INDICATED;
        /* Exit Data Protection */
        Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
      }
      else
      {
        /* For MISRA Compliance */
      }
      /* If the channel belongs to a cluster */
      if (LucChnlCoordInfoIndex != NM_INVALID)
      {
        /* Get the index to Nm_GaaClusterList structure */
        LucNmClusterListInfoIndex = Nm_GaaChannelConfig[LddNetworkIndex].ucClusterListInfoIndex;

        /* Getting a mapping index to the array Nm_GaaChnlArray */
        LucNmChnlMappingIndex = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNmChnlMappingIndex;
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
        }

        /* Call Nm_ClusterWakeUp with the mapping index for the cluster */
        Nm_ClusterWakeUp(LucNmChnlMappingIndex, LucClusterSize);
      } /* if (LucChnlCoordInfoIndex != NM_INVALID) */
      /* If the channel does not belong to a cluster */
      else
      {
        /* Call BusNm_NetworkRequest for this network */
        LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_NetworkRequest(NetworkHandle);
      }
    }
    else
    {
      /* Call BusNm_NetworkRequest for this network */
      LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_NetworkRequest(NetworkHandle);
    }
		/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
  }
  
  return(LenReturnVal);
} /* End of Nm_NetworkRequest */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_NetworkRelease()                                 **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This API releases the appropriate BusNm network.    **
**                        conditions are evaluated i.e., a check is           **
**                        performed to see if all the networks in the cluster **
**                        are ready to go to sleep.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GpChnlIndexArray, Nm_GaaChannelConfig,           **
**                        Nm_GaaChannelCoord_ConfigInfo, Nm_GaaClusterList,   **
**                        Nm_GaaChnlArray, Nm_GaaNetworkStatusFlag,           **
**                        Nm_GaaSchMEnterFuncPtr, Nm_GaaSchMExitFuncPtr       **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_NetworkRelease,       **
**                        <BusNm>_GetState                                    **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRelease(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle)
{
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;
  /* Local variable to hold the return value */
  Std_ReturnType LenReturnVal = E_NOT_OK;
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

  boolean LblCoordDelay = NM_FALSE;

  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_NETWORKRELEASE_SID, NM_E_UNINIT);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(NetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_NETWORKRELEASE_SID, NM_E_HANDLE_UNDEF);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_NETWORKRELEASE_SID, NM_E_HANDLE_UNDEF);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].blPassiveModeEnabled == NM_TRUE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_NETWORKRELEASE_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_NetworkRelease == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_NETWORKRELEASE_SID, NM_E_INVALID_REQUEST);
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
      /* Initialize the flag that indicates if the cluster can sleep or not */
      LblSleepFlag = NM_TRUE;
      /* Initialize flag that indicates if synchronization indication is needed */
      LblSynchronizingNetwork = NM_FALSE;
      
      /* Get the index to Nm_GaaClusterList structure */
      LucNmClusterListInfoIndex = Nm_GaaChannelConfig[LddNetworkIndex].ucClusterListInfoIndex;
      /* Getting a mapping index to the array Nm_GaaChnlArray */
      LucNmChnlMappingIndex = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNmChnlMappingIndex;
      /* Get the start index of the cluster */
      LucClusterStart = Nm_GpChnlArray[LucNmChnlMappingIndex];
      /* Get the size of the cluster */
      LucClusterSize = Nm_GpClusterList[LucNmClusterListInfoIndex].ucNumOfChnls;
      /* Change the status of the Network Status flag */
      /* If the Local ECU is not the sleep master */
      if (Nm_GaaChannelConfig[LddNetworkIndex].blChannelSleepMaster == NM_FALSE)
      {
        /* If no release has occurred */
        if (Nm_GaaNetworkStatusFlag[LddNetworkIndex] == NM_NO_RELEASE)
        {
          /* Enter Data Protection */
          Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
          /* Set flag to indicate that ComM has released the network */
          Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_COMM_RELEASE;
          /* Exit Data Protection */
          Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
        }
        /* If BusNm has released already */
        else if (Nm_GaaNetworkStatusFlag[LddNetworkIndex]== NM_BUSNM_RELEASE)
        {
          /* Enter Data Protection */
          Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
          /* Set flag to indicate that BusNm and ComM have released */
          Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_COMM_BUSNM_RELEASE;
          /* Exit Data Protection */
          Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
        }
        else
        {
          /* For MISRA Compliance */
        }
      }
      else
      {
        /* Enter Data Protection */
        Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
        /* If the Local ECU is sleep master */
        Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_COMM_BUSNM_RELEASE;
        /* Exit Data Protection */
        Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
      }
      /* For all the networks in the cluster */
      for(LucCount = NM_ZERO; LucCount < LucClusterSize; LucCount++)
      {
        /* Get the channel index for the next channel in the cluster */
        LddNetworkIndex = Nm_GpChnlArray[LucNmChnlMappingIndex+ LucCount];
        /* Get the Channel Id */
				/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
        LddChannelId = Nm_GaaChannelConfig[LddNetworkIndex].ddChannelId;
        /* Get the state of the bus */
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
          LblSynchronizingNetwork =  NM_TRUE;
        }
        /* Checking if all the networks have been released */
        if ((Nm_GaaNetworkStatusFlag[LddNetworkIndex] != NM_COMM_BUSNM_RELEASE) &&
            (Nm_GaaNetworkStatusFlag[LddNetworkIndex] != NM_SLEEP_INDICATED))
        {

          LblSleepFlag = NM_FALSE;
        }
      } /* End  of for loop */
      /* If the cluster is ready to sleep */
			/* polyspace-begin MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
      if (LblSleepFlag == NM_TRUE)
      {
        if (Nm_GblCoordinatorSyncSupport == STD_ON)
        {
          for(LucCount = NM_ZERO; LucCount < LucClusterSize; LucCount++)
          {
            /* Get the next channel in the cluster */
            LddNetworkIndex = Nm_GpChnlArray[LucNmChnlMappingIndex + LucCount];
            /* Get the index to Nm_GaaChannelCoord_ConfigInfo structure */

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
            /* Set the Coord delay timer */
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
            LddNetworkIndex = Nm_GpChnlArray[LucNmChnlMappingIndex + LucCount];
            /* Get the index to Nm_GaaChannelCoord_ConfigInfo structure */
            /* Set the shutdown delay timers */
            Nm_GaaShutdownTimer[LddNetworkIndex] =
              Nm_GaaChannelConfig[LddNetworkIndex].ulShutdownDelayTimerTick;
          } /*  End of for loop */
          /* Enter Data Protection */
          Nm_GaaSchMEnterFuncPtr[LucClusterStart].pSchMFuncPtr();
          /* Set the shutdown flag to indicate that timers are set */
          Nm_GaaClusterStatusFlag[LucClusterStart] = NM_TIMERS_SET;
          /* Exit Data Protection */
          Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();
        } /* End of if (LblSynchronizingNetwork == NM_FALSE) */
        /* 2013-06-28 Kt.Kim Fix error in defect list */
        else if (LblSynchronizingNetwork == NM_TRUE)
        {
          /* Enter Data Protection */
          Nm_GaaSchMEnterFuncPtr[LucClusterStart].pSchMFuncPtr();
          /* If there is a synchronizing network do not set the timers */
          Nm_GaaClusterStatusFlag[LucClusterStart] = NM_SHUTDOWN_READY;
          /* Exit Data Protection */
          Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();
        }
        else
        {
        }
      } /* End of if (LblSleepFlag == NM_TRUE) */
			/* polyspace-end MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
			
      LenReturnVal = E_OK;
    }
    else
    {
      /* Call BusNm_NetworkRelease for this network */
      LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_NetworkRelease(NetworkHandle);
    }
		/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
  }
  
  /* Return the Return Value */
  return (LenReturnVal);
} /* End of Nm_NetworkRelease */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_DisableCommunication()                           **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service calls DisableCommunication API of the  **
**                        appropriate BusNm layer.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GaaChannelConfig,                                **
**                        Nm_GaaChannelCoord_ConfigInfo, Nm_GaaClusterList,   **
**                        Nm_GpChnlIndexArray                                 **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_DisableCommunication, **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_DisableCommunication(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle)
{
  /* Local variable to store return value */
  Std_ReturnType LenReturnVal = E_NOT_OK;
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is not initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_DISABLECOMMUNICATION_SID, NM_E_UNINIT);
  }
  else if (Nm_GblComControlEnabled == STD_OFF)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_DISABLECOMMUNICATION_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(NetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_DISABLECOMMUNICATION_SID, NM_E_HANDLE_UNDEF);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_DISABLECOMMUNICATION_SID, NM_E_HANDLE_UNDEF);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_DisableCommunication == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_DISABLECOMMUNICATION_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    /* Call BusNm_DisableCommunication()*/
    LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_DisableCommunication(NetworkHandle);
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  
  return LenReturnVal;
} /* End of Nm_DisableCommunication */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_EnableCommunication()                            **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This service calls EnableCommunication API of the   **
**                        appropriate BusNm layer.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GaaChannelConfig,                                **
**                        Nm_GpChnlIndexArray                                 **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_EnableCommunication,  **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_EnableCommunication(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle)
{
  /* Local variable to store return value */
  Std_ReturnType LenReturnVal = E_NOT_OK;
 /* Local index for storing the index to to the channel config structure */
   NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is not initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_ENABLECOMMUNICATION_SID, NM_E_UNINIT);
  }
  else if (Nm_GblComControlEnabled == STD_OFF)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_ENABLECOMMUNICATION_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(NetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_ENABLECOMMUNICATION_SID, NM_E_HANDLE_UNDEF);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_ENABLECOMMUNICATION_SID, NM_E_HANDLE_UNDEF);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_EnableCommunication == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_ENABLECOMMUNICATION_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    /* Call BusNm_EnableCommunication()*/
    LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_EnableCommunication(NetworkHandle);
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  
  return LenReturnVal;
} /* End of Nm_EnableCommunication */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_RepeatMessageRequest()                           **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This service calls RepeatMessageRequest API of the  **
**                        appropriate BusNm layer.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GaaChannelConfig,                                **
**                        Nm_GpChnlIndexArray                                 **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_RepeatMessageRequest, **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, NM_CODE) Nm_RepeatMessageRequest(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle)
{
  /* Local variable to store return value */
  Std_ReturnType LenReturnVal = E_NOT_OK;
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is not initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_REPEATMESSAGEREQUEST_SID, NM_E_UNINIT);
  }
  else if (Nm_GblNodeDetectionEnabled == STD_OFF)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_REPEATMESSAGEREQUEST_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(NetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_REPEATMESSAGEREQUEST_SID, NM_E_HANDLE_UNDEF);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_REPEATMESSAGEREQUEST_SID, NM_E_HANDLE_UNDEF);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_RepeatMessageRequest == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_REPEATMESSAGEREQUEST_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    /* Call BusNm_RepeatMessageRequest() */
    LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_RepeatMessageRequest(NetworkHandle);
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  
  return LenReturnVal;
} /* End of Nm_RepeatMessageRequest */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_SetUserData()                                    **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This service call the SetUserData API for the       **
**                        appropriate BusNm layer.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle, nmUserDataPtr                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GaaChannelConfig,                                **
**                        Nm_GpChnlIndexArray                                 **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_SetUserData,          **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_SetUserData(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
  CONSTP2CONST(uint8, AUTOMATIC, NM_APPL_CONST) nmUserDataPtr)
{
  /* Local variable to store return value */
  Std_ReturnType LenReturnVal = E_NOT_OK;
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is not initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_SETUSERDATA_SID, NM_E_UNINIT);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(NetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_SETUSERDATA_SID, NM_E_HANDLE_UNDEF);
  }
  else if (nmUserDataPtr == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_SETUSERDATA_SID, NM_E_PARAM_POINTER);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_SETUSERDATA_SID, NM_E_HANDLE_UNDEF);
  }
  else if ((Nm_GblUserDataEnabled == STD_OFF) || (Nm_GblComUserDataSupport == STD_ON))
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_SETUSERDATA_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].blPassiveModeEnabled == NM_TRUE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_SETUSERDATA_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_SetUserData == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_SETUSERDATA_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    /* Call BusNm_EnableCommunication() */
    LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_SetUserData(NetworkHandle, nmUserDataPtr);
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  
  return LenReturnVal;
} /* End of Nm_SetUserData */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_GetUserData()                                    **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This service call the GetUserData API for the       **
**                        appropriate BusNm layer.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmUserDataPtr                                       **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GaaChannelConfig,                                **
**                        Nm_GpChnlIndexArray                                 **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_GetUserData,          **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, NM_CODE) Nm_GetUserData(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
  CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmUserDataPtr)
{
  /* Local variable to store return value */
  Std_ReturnType LenReturnVal = E_NOT_OK;
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is not initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETUSERDATA_SID, NM_E_UNINIT);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(NetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle,  NM_GETUSERDATA_SID, NM_E_HANDLE_UNDEF);
  }
  else if (nmUserDataPtr == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETUSERDATA_SID, NM_E_PARAM_POINTER);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle,  NM_GETUSERDATA_SID, NM_E_HANDLE_UNDEF);
  }
  else if (Nm_GblUserDataEnabled == STD_OFF)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle,  NM_GETUSERDATA_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetUserData == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle,  NM_GETUSERDATA_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    /* Call BusNm_GetUserData() */
    LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetUserData(NetworkHandle, nmUserDataPtr);
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  
  return LenReturnVal;
} /* End of Nm_GetUserData */
#define NM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Nm_GetPduData()                                     **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This service call the GetPduData API for the        **
**                        appropriate BusNm layer.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for the same NetworkHandle               **
**                                                                            **
** Input Parameters     : NetworkHandle                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmPduData                                           **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GaaChannelConfig,                                **
**                        Nm_GpChnlIndexArray                                 **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_GetPduData,           **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_GetPduData(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
  CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_CONST) nmPduData)
{
  /* Local variable to store return value */
  Std_ReturnType LenReturnVal = E_NOT_OK;
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is not initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETPDUDATA_SID, NM_E_UNINIT);
  }
  else if ((Nm_GblNodeIdEnabled == STD_OFF) && (Nm_GblUserDataEnabled == STD_OFF))
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETPDUDATA_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(NetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETPDUDATA_SID, NM_E_HANDLE_UNDEF);
  }
  else if (nmPduData == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETPDUDATA_SID, NM_E_PARAM_POINTER);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETPDUDATA_SID, NM_E_HANDLE_UNDEF);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetPduData == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETPDUDATA_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    /* Call BusNm_GetPduData() */
    LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetPduData(NetworkHandle, nmPduData);
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  
  return LenReturnVal;
} /* End of Nm_GetPduData */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_GetNodeIdentifier()                              **
**                                                                            **
** Service ID           : 0x0a                                                **
**                                                                            **
** Description          : This service call the GetNodeIdentifier API for the **
**                        appropriate BusNm layer.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmNodeIdPtr                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s) : Nm_GblInitStatus,              **
**                        Nm_GaaChannelConfig,                                **
**                        Nm_GpChnlIndexArray                                 **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_GetNodeIdentifier,    **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_GetNodeIdentifier(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
  CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_CONST) nmNodeIdPtr)
{
  /* Local variable to store return value */
  Std_ReturnType LenReturnVal = E_NOT_OK;
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is not initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETNODEIDENTIFIER_SID, NM_E_UNINIT);
  }
  else if (Nm_GblNodeIdEnabled == STD_OFF)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETNODEIDENTIFIER_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(NetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETNODEIDENTIFIER_SID, NM_E_HANDLE_UNDEF);
  }
  else if (nmNodeIdPtr == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETNODEIDENTIFIER_SID, NM_E_PARAM_POINTER);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETNODEIDENTIFIER_SID, NM_E_HANDLE_UNDEF);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetNodeIdentifier == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETNODEIDENTIFIER_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    /* Call BusNm_GetNodeIdentifier() */
    LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetNodeIdentifier(NetworkHandle, nmNodeIdPtr);
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  
  return LenReturnVal;
} /* End of Nm_GetNodeIdentifier */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_GetLocalNodeIdentifier()                         **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : This service call the GetLocalNodeIdentifier API    **
**                        for the appropriate BusNm layer.                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : NetworkHandle                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmNodeIdPtr                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GaaChannelConfig,                                **
**                        Nm_GpChnlIndexArray                                 **
**                                                                            **
**                      : Function(s) invoked :                               **
**                        <BusNm>_GetLocalNodeIdentifier                      **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_GetLocalNodeIdentifier(
  CONST(NetworkHandleType, NM_APPL_CONST) NetworkHandle,
  CONSTP2VAR(uint8, AUTOMATIC, NM_APPL_CONST) nmNodeIdPtr)
{
  /* Local variable to store return value */
  Std_ReturnType LenReturnVal = E_NOT_OK;
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is not initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETLOCALNODEIDENTIFIER_SID, NM_E_UNINIT);
  }
  else if (Nm_GblNodeIdEnabled == STD_OFF)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETLOCALNODEIDENTIFIER_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(NetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETLOCALNODEIDENTIFIER_SID, NM_E_HANDLE_UNDEF);
  }
  else if (nmNodeIdPtr == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETLOCALNODEIDENTIFIER_SID, NM_E_PARAM_POINTER);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETLOCALNODEIDENTIFIER_SID, NM_E_HANDLE_UNDEF);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetLocalNodeIdentifier == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NetworkHandle, NM_GETLOCALNODEIDENTIFIER_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    /* Call BusNm_GetLocalNodeIdentifier() */
    LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetLocalNodeIdentifier(NetworkHandle, nmNodeIdPtr);
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  
  return LenReturnVal;
} /* End of Nm_GetLocalNodeIdentifier */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_CheckRemoteSleepIndication()                     **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : This service call the CheckRemoteSleepIndication API**
**                        for the appropriate BusNm layer.                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant for the same NetworkHandle,           **
**                        reentrant otherwise                                 **
**                                                                            **
** Input Parameters     : nmNetworkHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmRemoteSleepIndPtr                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GaaChannelConfig,                                **
**                        Nm_GpChnlIndexArray                                 **
**                                                                            **
**                      : Function(s) invoked :                               **
**                        <BusNm>_CheckRemoteSleepInication                   **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, NM_CODE) Nm_CheckRemoteSleepIndication(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle,
  CONSTP2VAR(boolean, AUTOMATIC, NM_APPL_CONST) nmRemoteSleepIndPtr)
{
  /* Local variable to store return value */
  Std_ReturnType LenReturnVal = E_NOT_OK;
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is not initialized */
	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_CHECKREMOTESLEEPINDICATION_SID, NM_E_UNINIT);
  }
  else if (Nm_GblRemoteSleepIndEnabled == STD_OFF)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_CHECKREMOTESLEEPINDICATION_SID, NM_E_INVALID_REQUEST);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(nmNetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_CHECKREMOTESLEEPINDICATION_SID, NM_E_HANDLE_UNDEF);
  }
  else if (nmRemoteSleepIndPtr == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_CHECKREMOTESLEEPINDICATION_SID, NM_E_PARAM_POINTER);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_CHECKREMOTESLEEPINDICATION_SID, NM_E_HANDLE_UNDEF);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_CheckRemoteSleepIndication == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_CHECKREMOTESLEEPINDICATION_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    /* Call BusNm_CheckRemoteSleepIndication() */
    LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_CheckRemoteSleepIndication(nmNetworkHandle, nmRemoteSleepIndPtr);
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE [Not a defect:Justified] "Condition will be executed based on the configured values" */
  
  return LenReturnVal;
} /* End of Nm_CheckRemoteSleepIndication */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_GetState()                                       **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : This service call the GetState API for the          **
**                        appropriate BusNm layer.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : nmNetworkHandle                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : nmStatePtr, nmModePtr                               **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : BusNm and Nm should be initialized properly         **
**                                                                            **
** Remarks              : Global Variable(s)  : Nm_GblInitStatus,             **
**                        Nm_GaaChannelConfig,                                **
**                        Nm_GpChnlIndexArray                                 **
**                                                                            **
**                      : Function(s) invoked : <BusNm>_GetState,             **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, NM_CODE) Nm_GetState(
  CONST(NetworkHandleType, NM_APPL_CONST) nmNetworkHandle,
  CONSTP2VAR(Nm_StateType, AUTOMATIC, NM_APPL_CONST) nmStatePtr,
  CONSTP2VAR(Nm_ModeType, AUTOMATIC, NM_APPL_CONST) nmModePtr)
{
  /* Local variable to store return value */
  Std_ReturnType LenReturnVal = E_NOT_OK;
  /* Local index for storing the index to to the channel config structure */
  NetworkHandleType LddNetworkIndex;

  /* Check if the NM module is not initialized */
  if (Nm_GblInitStatus != NM_INIT)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_GETSTATE_SID, NM_E_UNINIT);
  }
  else if (Nm_IntGetChannelIndexFromChannelId(nmNetworkHandle, &LddNetworkIndex) == NM_FALSE)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_GETSTATE_SID, NM_E_HANDLE_UNDEF);
  }
  else if ((nmStatePtr == NULL_PTR) || (nmModePtr == NULL_PTR))
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_GETSTATE_SID, NM_E_PARAM_POINTER);
  }
  else if (LddNetworkIndex >= Nm_GucNumberOfChannels)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_GETSTATE_SID, NM_E_HANDLE_UNDEF);
  }
  else if (Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetState == NULL_PTR)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, nmNetworkHandle, NM_GETSTATE_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    /* Call BusNm_GetState()*/
    LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetState(nmNetworkHandle, nmStatePtr, nmModePtr);
  }
  
  return LenReturnVal;
} /* End of Nm_GetState */
#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
