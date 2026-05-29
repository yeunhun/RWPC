/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Nm_Internal.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : Provides definition of Internal Function                      **
**              Nm_ClusterWakeUp                                              **
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
** 1.0.1     17-May-2016   Kt Kim        #4641                                **
** 1.0.0     01-Feb-2013   Kt Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Nm_Cfg.h" /* For Macros */
#include "Nm.h" /* For Macros */
#include "Nm_Internal.h"
#include "ComM_Nm.h"  /* For the ComM Callbacks */
#include "Nm_PCTypes.h" /* Inclusion for declaration of structure types */
#include "Nm_Ram.h" /* For declarations of global variables */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define NM_INTERNAL_C_AR_RELEASE_MAJOR_VERSION     (4)
#define NM_INTERNAL_C_AR_RELEASE_MINOR_VERSION     (0)
#define NM_INTERNAL_C_AR_RELEASE_REVISION_VERSION  (3)

/* Software Version Information */
#define NM_INTERNAL_C_SW_MAJOR_VERSION  (2)
#define NM_INTERNAL_C_SW_MINOR_VERSION  (3)

/*******************************************************************************
**                         V E R S I O N      C H E C K                       **
*******************************************************************************/
#if (NM_AR_RELEASE_MAJOR_VERSION != NM_INTERNAL_C_AR_RELEASE_MAJOR_VERSION)
  #error "Nm.c : Mismatch in Specification Major Version"
#endif

#if (NM_AR_RELEASE_MINOR_VERSION != NM_INTERNAL_C_AR_RELEASE_MINOR_VERSION)
  #error "Nm.c : Mismatch in Specification Minor Version"
#endif

#if (NM_AR_RELEASE_REVISION_VERSION != NM_INTERNAL_C_AR_RELEASE_REVISION_VERSION)
  #error "Nm.c : Mismatch in Specification Patch Version"
#endif

#if (NM_SW_MAJOR_VERSION != NM_INTERNAL_C_SW_MAJOR_VERSION)
  #error "Nm.c : Mismatch in Software Major Version"
#endif

#if (NM_SW_MINOR_VERSION != NM_INTERNAL_C_SW_MINOR_VERSION)
  #error "Nm.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define NM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Nm_ClusterWakeUp                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is called to keep all the networks in a    **
**                        particular cluster requested.                       **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : MappingIndex, ClusterSize                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Nm_GaaChnlArray,              **
**                        Nm_GaaChannelConfig,                                **
**                        Nm_GaaClusterStatusFlag, Nm_GaaShutdownTimer,       **
**                        Nm_GaaNetworkStatusFlag,                            **
**                        Nm_GaaSchMEnterFuncPtr, Nm_GaaSchMExitFuncPtr       **
**                        Function(s) Invoked : <BusNm>_GetState,             **
**                        <BusNm>_NetworkRequest                              **
**                                                                            **
*******************************************************************************/

FUNC(void, NM_CODE) Nm_ClusterWakeUp(
  CONST(uint8, NM_APPL_CONST) MappingIndex,
  CONST(uint8, NM_APPL_CONST) ClusterSize)
{
  /* Local index for storing the index to the channel config structure */
  NetworkHandleType LddNetworkIndex;
  /* Local variable to store the Channel Id */
  NetworkHandleType LddChannelId;
  /* Variable to access the  network state */
  Nm_StateType LenState;
  /* Variable to access the network mode */
  Nm_ModeType LenMode = NM_MODE_BUS_SLEEP;
  /* Local variable to store return value */
  Std_ReturnType LenReturnVal;
  /* Local variable to store the cluster size */
  uint8 LucClusterStart;
  /* Count Variable */
  uint8 LucCount;

	/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
  if (Nm_GblCoordinatorSupportEnabled == STD_OFF)
  {
    (void)Nm_IntDetReportError(NM_MODULE_ID, NM_INSTANCE_ID, NM_MAINFUNCTION_SID, NM_E_INVALID_REQUEST);
  }
  else
  {
    if (Nm_GpChnlArray != NULL_PTR)
    {
      /* Get the start index of the cluster */
      LucClusterStart = Nm_GpChnlArray[MappingIndex];
      
      for(LucCount = NM_ZERO; LucCount < ClusterSize; LucCount++)
      {
        /* Get the channel index for the next channel in the cluster */
        LddNetworkIndex = Nm_GpChnlArray[MappingIndex + LucCount];
        /* Reset the shutdown timers */
				/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
        Nm_GaaShutdownTimer[LucCount] = NM_TIMER_RESET;
        /* Get the Channel Id */
				/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
        LddChannelId = Nm_GaaChannelConfig[LddNetworkIndex].ddChannelId;
        /* Call <Bus>Nm_GetState() */
        (void)Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_GetState(LddChannelId, &LenState,
          &LenMode);

        if (LenMode == NM_MODE_PREPARE_BUS_SLEEP)
        {
          /* Call <Bus>Nm_NetworkRequest for this network */
					/* polyspace +1 RTE:COR [Not a defect:Justified] "Configured function pointer" */
          LenReturnVal = Nm_GaaChannelConfig[LddNetworkIndex].pfnBusNm_NetworkRequest(LddChannelId);
          if (LenReturnVal == E_OK)
          {
            /* Enter Data Protection */
            Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
            /* Change the status of the network */
            Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_NO_RELEASE;
            /* Exit Data Protection */
            Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
          }
          else
          {
            /* Enter Data Protection */
            Nm_GaaSchMEnterFuncPtr[LddNetworkIndex].pSchMFuncPtr();
            /* Change the status of the network */
            Nm_GaaNetworkStatusFlag[LddNetworkIndex] = NM_SLEEP_INDICATED;
            /* Exit Data Protection */
            Nm_GaaSchMExitFuncPtr[LddNetworkIndex].pSchMFuncPtr();
          }
        }
        else if ((LenMode == NM_MODE_BUS_SLEEP) &&
				/* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Genderated array index in range" */
                 (Nm_GaaClusterStatusFlag[LucClusterStart] ==  NM_SHUTDOWN_ABORTED))
        {
          /* Call ComM_Nm_RestartIndication() */
          ComM_Nm_RestartIndication(LddChannelId);
        }
        else
        {
          /* MISRA Compliance */
        }
      } /* End of for (LucCount = NM_ZERO; LucCount < ClusterSize; LucCount++) */
      /* Enter Data Protection */
			/* polyspace +1 MISRA-C3:18.1, RTE:IDP,OBAI [Not a defect:Justified] "Genderated array index in range" */
      Nm_GaaSchMEnterFuncPtr[LucClusterStart].pSchMFuncPtr();
      /* Change the cluster state to indicate that the cluster is now awake */
      Nm_GaaClusterStatusFlag[LucClusterStart] = NM_AWAKE;
      /* Exit Data Protection */
      Nm_GaaSchMExitFuncPtr[LucClusterStart].pSchMFuncPtr();
    }
  }
	/* polyspace-end MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect:Justified] "Condition will be executed based on the configured values" */
} /* End of Nm_ClusterWakeUp */

/*******************************************************************************
** Function Name        : Nm_IntGetChannelIndexFromChannelId                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is called to get channel index from        **
**                        channel id.                                         **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : LddChannelId                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpChannelIndex                                      **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Nm_GucMaxChnId, Nm_GaaChnlIndexArray                **
*******************************************************************************/

FUNC(boolean, NM_CODE) Nm_IntGetChannelIndexFromChannelId(
  CONST(NetworkHandleType, NM_APPL_CONST) LddChannelId,
  P2VAR(NetworkHandleType, AUTOMATIC, NM_APPL_DATA) LpChannelIndex)
{
  boolean LblResult = NM_FALSE;
  
  if (LddChannelId <= Nm_GucMaxChnId)
  {
    *LpChannelIndex = Nm_GaaChnlIndexArray[LddChannelId];
    LblResult = NM_TRUE;
  }

  return LblResult;
}

/*******************************************************************************
** Function Name        : Nm_IntDetReportError                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is called to raise DET error.              **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ModuleId, InstanceId, ApiId, ErrorId                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Nm_GblDevErrorDetect                                **
**                        Function(s) Invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/

FUNC(Std_ReturnType, NM_CODE) Nm_IntDetReportError(
  uint16 ModuleId,
  uint8 InstanceId,
  uint8 ApiId,
  uint8 ErrorId)
{
  Std_ReturnType result = (Std_ReturnType)E_OK;

		/* polyspace-begin MISRA-C3:14.3,2.1, DEFECT:DEAD_CODE,USELESS_IF [Not a defect: Justified] "condition will be executed based on the configured values" */
  if (Nm_GblDevErrorDetect == STD_ON)
  {
    result = Det_ReportError(ModuleId, InstanceId, ApiId, ErrorId);
  }

  return result;
}


#define NM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
