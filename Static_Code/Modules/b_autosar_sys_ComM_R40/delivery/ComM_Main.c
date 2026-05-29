/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComM_Main.c                                                   **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of Main Functionality                               **
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
** 1.10.1    13-Sep-2021   Jongsun Lim #29173,#32059,#32231                   **
** 1.10.0    21-Jun-2021   HieuTM8     #29910                                 **
** 1.9.5     08-Dec-2020   Jongsun Lim #25703                                 **
** 1.9.4     26-Oct-2020   JS Lim      #26262                                 **
** 1.9.3     12-Aug-2020   Jongsun Lim #22924, #25120, #25552, #25554         **
** 1.9.2     03-Jan-2020   Jongsun Lim #20992                                 **
** 1.9.0     22-Aug-2019   JS Lim      #18922, #19094                         **
** 1.8.0     23-Oct-2018   JS Lim      #13018, #13653                         **
** 1.7.16    19-Jul-2018   Chan Kim    #11240                                 **
** 1.7.15    19-Jun-2017   JH Jeong    #11240                                 **
** 1.0.10    30-May-2017   KT Kim      #8639                                  **
** 1.0.9     16-Jul-2015   KT Kim      #2883 #2896                            **
** 1.0.7     10-Jul-2014   KT Kim      #1081                                  **
** 1.0.6     04-Jul-2013   Daejun Park CR~129, XAR~581 : ComM library         **
** 1.0.0     12-Apr-2013   Daejun Park Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM_Internal.h"        /* ComM Internal functions header file */
#include "ComM_Ram.h"             /* ComM global Ram variables header file */
#include "ComM_Config.h"          /* ComM Config header file */
#include "SchM_ComM.h"            /* SchM data protection API header file */

#if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
#include "Nm.h"                   /* Nm header file */
#endif
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#include "Com.h"
#endif
#endif
#include "BswM_ComM.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COMM_MAIN_C_AR_RELEASE_MAJOR_VERSION    4
#define COMM_MAIN_C_AR_RELEASE_MINOR_VERSION    0
#define COMM_MAIN_C_AR_RELEASE_REVISION_VERSION 3

/* Software Version Information */
#define COMM_MAIN_C_SW_MAJOR_VERSION            1
#define COMM_MAIN_C_SW_MINOR_VERSION            10

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (COMM_INTERNAL_AR_RELEASE_MAJOR_VERSION !=\
     COMM_MAIN_C_AR_RELEASE_MAJOR_VERSION)
#error "ComM_Main.c : Mismatch in Specification Major Version"
#endif

#if (COMM_INTERNAL_AR_RELEASE_MINOR_VERSION !=\
     COMM_MAIN_C_AR_RELEASE_MINOR_VERSION)
#error "ComM_Main.c : Mismatch in Specification Minor Version"
#endif

#if (COMM_INTERNAL_AR_RELEASE_REVISION_VERSION !=\
     COMM_MAIN_C_AR_RELEASE_REVISION_VERSION)
#error "ComM_Main.c : Mismatch in Specification Revision Version"
#endif

#if (COMM_INTERNAL_SW_MAJOR_VERSION != COMM_MAIN_C_SW_MAJOR_VERSION)
#error "ComM_Main.c : Mismatch in Major Version"
#endif

#if (COMM_INTERNAL_SW_MINOR_VERSION != COMM_MAIN_C_SW_MINOR_VERSION)
#error "ComM_Main.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Extern for processing the Pending Request in no Communication */
static FUNC(boolean, COMM_CODE) ComM_NoComNoPendingRequest(uint8 LucIndex);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Extern for processing the Request Pending in no Communication */
static FUNC(void, COMM_CODE) ComM_NoComRequestPending(uint8 LucIndex, boolean
  LblPassiveWakeFlag);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"


#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
(COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Static function if current PNC mode is Full */
static FUNC(void, COMM_CODE) ComM_PNCFullMode(uint8 LucPncIndex);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Static function if current PNC mode is No */
static FUNC(void, COMM_CODE) ComM_PNCNoMode(uint8 LucPncIndex);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_PNCComSigFullCom(uint8 LucIndex);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_PNCNetwReq(uint8 LucPncInx, uint8 LucByteIndex, uint8
  LucMask, uint8 LucIndex);


#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#define COMM_START_SEC_CODE
#include "MemMap.h"

/* STATIC function if current comm mode is Full comm */
static FUNC(void, COMM_CODE) ComM_FullComMode(uint8 LucIndex);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"

/* STATIC function if current comm mode is No comm */
static FUNC(void, COMM_CODE) ComM_NoComMode(uint8 LucIndex);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"

/* STATIC function if current comm mode is Silent comm */
static FUNC(void, COMM_CODE) ComM_SilentComMode(uint8 LucIndex);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_FullComNetwReq(uint8 LucIndex);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_FullComReadySleep(uint8 LucIndex);

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_MainFunction                                   **
**                                                                            **
** Service ID           : 0x60                                                **
**                                                                            **
** Description          : This Service is Main function for the Channels and  **
**                        all associated PNCs of the channels                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : NetworkHandleType Channel                           **
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
**                        ComM_GaaChannelMapArray, ComM_GblInit,              **
**                        ComM_GaaCurComMode, ComM_GaaChannelToPncMapping[],  **
**                        ComM_GaaSubPNCMode, ComM_GaaPncs, ComM_GaaPncTimeCnt**
**                        ComM_GaaChannels                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Det_ReportError(), ComM_PNCFullMode(),              **
**                        ComM_PNCNoMode(),ComM_NoComMode(),ComM_FullComMode()**
**                        ComM_SilentComMode()                                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Pointer is not outside its bounds - Pointer is generated by Generator*/
/* polyspace:begin<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET and pointer is not NULL */
/* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not NULL and validated  */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_MainFunction(NetworkHandleType Channel)
{
  /* The variable Lucindex is used as array index */
  NetworkHandleType LddChnlIndex;
  #if((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON)||\
      (COMM_ETHNETWORK_PRESENT == STD_ON))
  /* The variable is used for PNC Index */
  uint8 LucPncIndex;

  /* The variable is used for PNC Count */
  uint8 LucPncCount;

  /* The variable is used for Indexing*/
  uint8 LucIndex;
  #endif
  #endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
          *STD_ON)) */

  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check whether the module is initialized or not */
  if (ComM_GblInit == COMM_UNINIT)
  {
    /* Report to DET */
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_MAINFUNCTION_SID, COMM_E_NOT_INITED);
  }
  else
  #endif
  {
    /* Get Channel Index */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    LddChnlIndex = ComM_GaaChannelMapArray[Channel];
    #else
    LddChnlIndex = Channel;
    #endif

    #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
    #if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
         (COMM_ETHNETWORK_PRESENT == STD_ON))

    /* Check if the channel is part of a PNC */
    /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
    /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
    if (ComM_GaaChannels[LddChnlIndex].blChannelPnc == COMM_TRUE)
    {
      LucPncIndex = ComM_GaaChannels[LddChnlIndex].ucPncIndex;
      LucPncCount = ComM_GaaChannels[LddChnlIndex].ucPncCount;
      /*State transitions of the PNC state machines */
      while (LucPncCount != COMM_ZERO)
      {
        /* Decrement the pnc count */
        LucPncCount--;

        /* ComM_GaaChannelToPncMapping[] :The Map provides Index*/
        LucIndex = ComM_GaaChannelToPncMapping[LucPncIndex];

        if (ComM_GaaSubPNCMode[LucIndex] != PNC_NO_COMMUNICATION)
        {
          /* Call PNC State Change: Full */
          ComM_PNCFullMode(LucIndex);
        }
        else
        {
          /* Call PNC State Change: No */
          ComM_PNCNoMode(LucIndex);
        }
        LucPncIndex++;
      } /*End of PNC Counts of Channel*/
    } /* End of if (ComM_GaaChannels[LddChnlIndex].blChannelPnc == COMM_TRUE) */
    #endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
              *(COMM_FRNETWORK_PRESENT == STD_ON)) */
    #endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
              *STD_ON)) */
      /* polyspace<DEFECT:OUT_BOUND_ARRAY:Not a defect: Justify with annotations> Array index is valid and validated */
      /* polyspace<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated */
    if (ComM_GaaCurComMode[LddChnlIndex] == COMM_NO_COMMUNICATION)
    {
      /* Call No Mode switch function*/
      ComM_NoComMode(LddChnlIndex);
    }
    #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
    (COMM_ETHNETWORK_PRESENT == STD_ON))
    else if (ComM_GaaCurComMode[LddChnlIndex] == COMM_SILENT_COMMUNICATION)
    {
      /* Call Silent Mode switch function */
      ComM_SilentComMode(LddChnlIndex);
    }
    #endif
    else
    {
      /* Call Full Mode switch function */
      ComM_FullComMode(LddChnlIndex);
    }
  } /* End of Else */
} /* END OF MAIN */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_NoComMode                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve COMM_NO_COMMUNICATION mode **
**                        for the corresponding Channel index                 **
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
** Return Parameters    : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaSubComMode, ComM_GaaCommunicationAllowed    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_NoComNoPendingRequest(),                        **
**                        ComM_NoComRequestPending()                         **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_NoComMode(uint8 LucIndex)
{
  /* Variable to store passive wake up */
  boolean LblPassiveWakeFlag;

  /* Clear wakeup flag */
  LblPassiveWakeFlag = COMM_FALSE;

  /* If sub state is No request is pending */
  if (ComM_GaaSubComMode[LucIndex] == COMM_NO_COM_NO_PENDING_REQUEST)
  {
    /* Process the sub state COMM_NO_COM_NO_PENDING_REQUEST */
    LblPassiveWakeFlag = ComM_NoComNoPendingRequest(LucIndex);
  }

  /* If sub state is Pending request */
  if ((ComM_GaaSubComMode[LucIndex] == COMM_NO_COM_REQUEST_PENDING) &&
      (ComM_GaaCommunicationAllowed[LucIndex] == COMM_TRUE))
  {
    /* Process the sub state COMM_NO_COM_REQUEST_PENDING */
    ComM_NoComRequestPending(LucIndex, LblPassiveWakeFlag);
  }
} /* End of ComM_NoComMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_SilentComMode                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve COMM_SILENT_COMMUNICATION  **
**                        mode for the corresponding Channel index            **
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
**                        ComM_GaaWakeupIndication[], ComM_GaaSubComMode[],   **
**                        ComM_GaaDcmActiveDiagnostic[],                      **
**                        ComM_GaaReqedComModeCnt[], ComM_GaaNmRequested[],   **
**                        ComM_GaaChannelInhibition[], ComM_GaaNmIndication[] **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_SwitchComMMode()                               **
*******************************************************************************/
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_SilentComMode(uint8 LucIndex)
{
  /* If sub state is COMM_SILENT_COM */
  if (ComM_GaaSubComMode[LucIndex] == COMM_SILENT_COM)
  {
    /* If Bus Sleep Mode indication or Check if requested
     *   mode is No Communication */
    SchM_Enter_ComM_NM_INDICATION_PROTECTION(); 
    if ((ComM_GaaNmIndication[LucIndex] == COMM_BUSSLEEPMODE_IND) &&
        (ComM_GaaReqedComModeCnt[LucIndex] == COMM_ZERO))
    {
      /* Switch to No Communication from Silent Communication */
      ComM_SwitchComMMode(LucIndex, COMM_NO_COMMUNICATION);
      ComM_GaaNmRequested[LucIndex] = COMM_ZERO;
      ComM_GaaNmIndication[LucIndex] = COMM_ZERO;
      
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();

    }
    else
    {
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
      /* If Network Mode indication indication by NM */
      if (ComM_GaaNmIndication[LucIndex] == COMM_NMMODE_IND)
      {
        /* Switch to Full Communication Mode from Silent Comm */
        ComM_SwitchComMMode(LucIndex, COMM_FULL_COMMUNICATION);

        /* Change sub state to Ready Sleep */
        ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_READY_SLEEP;
        ComM_GaaNmIndication[LucIndex] = COMM_ZERO;
      }

      /* Check for Active Diagnostic, Wake Up indication and
       *   User requested Mode */
      if ((ComM_GaaDcmActiveDiagnostic[LucIndex] == COMM_TRUE) ||
          (ComM_GaaWakeupIndication[LucIndex] == COMM_TRUE) 
          #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
                                       (COMM_MODE_LIMITATION_ENABLED == STD_ON))
          || (((ComM_GaaChannelInhibition[LucIndex] &
                COMM_PREVENTWAKEUP_MASK_SET) != COMM_PREVENTWAKEUP_MASK_SET) &&
                              (ComM_GaaReqedComModeCnt[LucIndex] != COMM_ZERO)))
          #else
          || (ComM_GaaReqedComModeCnt[LucIndex] != COMM_ZERO)) /* Bug #2883 */
          #endif
      {
        /* Switch to Full Communication Mode from Silent Comm */
        ComM_SwitchComMMode(LucIndex, COMM_FULL_COMMUNICATION);
        ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_NETWORK_REQUESTED;
      }
    } /* End of else */
  } /* End of if (ComM_GaaSubComMode[LucIndex] == COMM_SILENT_COM) */
} /* End of ComM_SilentComMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  *(COMM_ETHNETWORK_PRESENT == STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_FullComMode                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve COMM_FULL_COMMUNICATION    **
**                        mode for the corresponding Channel index            **
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
**                        ComM_GaaSubComMode                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_PNCComSigFullCom(), ComM_FullComNetwReq(),     **
**                        ComM_FullComReadySleep()                            **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_FullComMode(uint8 LucIndex)
{
  /* PNC related function to be done before channel function */
  #if((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
      (COMM_ETHNETWORK_PRESENT == STD_ON))
  ComM_PNCComSigFullCom(LucIndex);
  #endif
  #endif

  /* If Sub State is Network Requested */
  if (ComM_GaaSubComMode[LucIndex] == COMM_FULL_COM_NETWORK_REQUESTED)
  {
    ComM_FullComNetwReq(LucIndex);
  }

  /* If sub state is Ready Sleep */
  if (ComM_GaaSubComMode[LucIndex] == COMM_FULL_COM_READY_SLEEP)
  {
    ComM_FullComReadySleep(LucIndex);
  }
} /* END OF FULL COMM*/

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_NoComNoPendingRequest                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to Process the channel request came **
**                        in ComM sub state COMM_NO_COM_NO_PENDING_REQUEST    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIndex                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : LblPassiveWakeFlag                                  **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The communication manager must be initialized.      **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaDcmActiveDiagnostic, ComM_GaaNmIndication   **
**                        ComM_GaaChannelInhibition, ComM_GblLimitEcuToNoCom, **
**                        ComM_GaaWakeupIndication, ComM_GaaReqedComModeCnt   **
**                        ComM_GblWakeUp, ComM_GaaSubComMode                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(boolean, COMM_CODE) ComM_NoComNoPendingRequest(uint8 LucIndex)
{
  /* Variable to Store Full Comm set or not */
  boolean LblFullFlag;

  /* Variable to store passive wake up */
  boolean LblPassiveWakeFlag;

  /* Clear Full Comm Flag */
  LblFullFlag = COMM_FALSE;

  /* Clear wakeup flag */
  LblPassiveWakeFlag = COMM_FALSE;

  /* Check for Active Diagnostics */
  if (ComM_GaaDcmActiveDiagnostic[LucIndex] == COMM_TRUE)
  {
    /* Set Full Comm Flag */
    LblFullFlag = COMM_TRUE;
  }
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  /*  Check for Limit channel inhibition condition and Limit ECU to No Com */
  if (((ComM_GaaChannelInhibition[LucIndex] &
        COMM_LIMITCHANNELTONOCOMM_MASK_SET) ==
       COMM_LIMITCHANNELTONOCOMM_MASK_SET)
      || (ComM_GblLimitEcuToNoCom == COMM_TRUE))
  {
    /* Do Nothing */
  }
  else
  #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
          *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */
  {
    /* Check for Passive wakeup and Synchronous Wakeup enabled */
    if (ComM_GaaWakeupIndication[LucIndex] == COMM_TRUE)
    {
      #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)

      /*Set Global WakeUp */
      ComM_GblWakeUp = COMM_TRUE;
      #else

      /* Set Full Comm Flag */
      LblFullFlag = COMM_TRUE;
      #endif

      /* Set Passive Comm Flag */
      LblPassiveWakeFlag = COMM_TRUE;
    } /* End of if (ComM_GaaWakeupIndication[LucIndex] == COMM_TRUE) */

    /* Check For Nm Start Indication */
    if (ComM_GaaNmIndication[LucIndex] == COMM_NMSTART_IND)
    {
      ComM_GaaNmIndication[LucIndex] = COMM_ZERO;

      /* Set Passive Comm Flag */
      LblPassiveWakeFlag = COMM_TRUE;
    }
    /* Check For Nm Restart Indication */
    else if (ComM_GaaNmIndication[LucIndex] == COMM_NMRST_IND)
    {
      /* Nm Restart Indication implemented so clear Nm indication */
      ComM_GaaNmIndication[LucIndex] = COMM_ZERO;

      /* Set Passive Comm Flag */
      LblPassiveWakeFlag = COMM_TRUE;
    }
    else
    {
      /* To Avoid MISRA warning */
    }
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
      (COMM_MODE_LIMITATION_ENABLED == STD_ON))

    if ((ComM_GaaChannelInhibition[LucIndex] &
         COMM_PREVENTWAKEUP_MASK_SET) != COMM_PREVENTWAKEUP_MASK_SET)
    #endif
    {
      /* Check For Full Communication Request */
      if (ComM_GaaReqedComModeCnt[LucIndex] != COMM_ZERO)
      {
        /* Set Full Comm Flag */
        LblFullFlag = COMM_TRUE;
      }
    }
  }
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  /* Check for Full Communication Request during mode limitation */
  if (((ComM_GaaChannelInhibition[LucIndex] &
        COMM_PREVENTWAKEUP_MASK_SET) != COMM_PREVENTWAKEUP_MASK_SET) &&
      (ComM_GaaInhibitionReqst[LucIndex] != COMM_ZERO))
  {
    /* Set Full Comm Flag */
    LblFullFlag = COMM_TRUE;
  }
  #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
    *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */

  /* If there is request for full communication */
  if ((LblFullFlag == COMM_TRUE) || (LblPassiveWakeFlag == COMM_TRUE))
  {
    /* Change the sub mode in No communication */
    ComM_GaaSubComMode[LucIndex] = COMM_NO_COM_REQUEST_PENDING;
  }
  /* Return checked in Next sub state: COMM_NO_COM_NO_PENDING_REQUEST*/
  return (LblPassiveWakeFlag);
} /* End of ComM_NoComNoPendingRequest */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_NoComRequestPending                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is to Process the channel request came **
**                        in ComM sub state COMM_NO_COM_NO_REQUEST_PENDING    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : LucIndex, LblPassiveWakeFlag                        **
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
**                        ComM_GaaChannels,ComM_GaaSubComMode,ComM_GaaTimeCnt,**
**                        ComM_GaaReqedComModeCnt,ComM_GaaDcmActiveDiagnostic **
**                        ComM_GaaDcmInactiveDiagnostic                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_SwitchComMMode(), Nm_PassiveStartUp()          **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_NoComRequestPending(uint8 LucIndex, boolean
  LblPassiveWakeFlag)
{
  #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)

  /* Variable to Store the BusType when bus is not internal */
  uint8 LucBusIndex;

  /* Get the BusType */
  LucBusIndex = ComM_GaaChannels[LucIndex].ucBusType;
  #endif

  /* If the bus type is other than Internal */
  #if (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON)

  /* polyspace<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
  /* polyspace:begin<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
  if (LucBusIndex != COMM_INTERNAL)
  {
    /* Switch to Full Communication Mode from No Communication */
    ComM_SwitchComMMode(LucIndex, COMM_FULL_COMMUNICATION);

    /* Change sub state to Network Requested */
    ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_NETWORK_REQUESTED;
    #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
    (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

    /* Start the Min amount of duration in full Communication counter */
    ComM_GaaTimeCnt[LucIndex] = ComM_GaaChannels[LucIndex].ddMinFullComMode;
    #endif
    #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
    (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
    /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
    if ((ComM_GaaChannels[LucIndex].ucNmVariant == COMM_NMVARIANT_FULL) ||
        (ComM_GaaChannels[LucIndex].ucNmVariant == COMM_NMVARIANT_PASSIVE))
    {
      /* If the Passive wake up is set */
      if (LblPassiveWakeFlag == COMM_TRUE)
      {
        /* Request Nm Bus Communication */
        (void)Nm_PassiveStartUp(ComM_GaaChannels[LucIndex].ddChannelId);

        /* Set Flag for Nm is requested for Passive start up */
        ComM_GaaNmRequested[LucIndex] = COMM_ONE;
      }
    }
    #endif /* Nm Variant Full or Passive */
  } /* End of if (LucBusIndex != COMM_INTERNAL) */
  /* If the bus type is Internal */
  else
  #endif /* (COMM_FUNC_BUSSMCOMMODE_SUPPORT == STD_ON) */
  {
    /* Switch to Full Communication Mode from No Communication */
    ComM_SwitchComMMode(LucIndex, COMM_FULL_COMMUNICATION);

    /* Change sub state to Network Requested */
    ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_NETWORK_REQUESTED;

    /* Start the Min amount of duration in full Communication counter */
    ComM_GaaTimeCnt[LucIndex] = ComM_GaaChannels[LucIndex].ddMinFullComMode;
  }
  /* polyspace:end<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
  /* If there is no user request for Full communication */
  if (ComM_GaaReqedComModeCnt[LucIndex] == COMM_ZERO)
  {
    /* If Dcm had indicated Active diagnostic */
    if (ComM_GaaDcmActiveDiagnostic[LucIndex] == COMM_TRUE)
    {
      /* If Dcm had indicated inactive diagnostic */
      if ((ComM_GaaDcmInactiveDiagnostic[LucIndex] == COMM_TRUE) &&
          (LblPassiveWakeFlag == COMM_FALSE))
      {
        /* Switch the sub state */
        ComM_GaaSubComMode[LucIndex] = COMM_NO_COM_NO_PENDING_REQUEST;
      }
    }
    else if (LblPassiveWakeFlag == COMM_FALSE)
    {
      /* Change sub state to COMM_NO_COM_NO_PENDING_REQUEST */
      ComM_GaaSubComMode[LucIndex] = COMM_NO_COM_NO_PENDING_REQUEST;
    }
    else
    {
      /* To avoid MISRA - C */
    }
  } /* End of if (ComM_GaaReqedComModeCnt[LucIndex] == COMM_ZERO) */
} /* End of ComM_NoComRequestPending */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_PNCFullMode                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve for PNC_FULL_COMMUNICATION **
**                        state.                                              **
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
**                        ComM_GaaSubPNCMode                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_PNCFullModeRequested()                         **
**                        ComM_PNCFullModeReadySleep()                        **
**                        ComM_PNCFullModePrepareSleep()                      **
*******************************************************************************/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_PNCFullMode(uint8 LucPncIndex)
{
  /* PNC Sub State (1): PNC_REQUESTED */
  if (ComM_GaaSubPNCMode[LucPncIndex] == PNC_REQUESTED)
  {
    ComM_PNCFullModeRequested(LucPncIndex);
  }
  /* PNC Sub State (2): PNC_READY_SLEEP */
  else if (ComM_GaaSubPNCMode[LucPncIndex] == PNC_READY_SLEEP)
  {
    ComM_PNCFullModeReadySleep(LucPncIndex);
  }
  /* PNC Sub State (3): PNC_PREPARE_SLEEP */
  else
  {
    ComM_PNCFullModePrepareSleep(LucPncIndex);
  }
} /* End of ComM_PNCFullMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
        *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_PNCNoMode                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve for PNC_NO_COMMUNICATION   **
**                        state.                                              **
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
** Remarks              : Global Variable(s):                                 **
**                        ComM_GaaRequestedPNCMode, ComM_GaaPncRxERAn,        **
**                        ComM_GaaPncRxEIRA, ComM_GaaPNCWakeupIndication      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_PNCNoMode(uint8 LucPncIndex)
{
  /* User Request or  ERAn Changes*/
  if ((ComM_GaaRequestedPNCMode[LucPncIndex] == PNC_USER_FULL_COMM)
      #if (COMM_PNC_GW_ENABLED == STD_ON)
      || (ComM_GaaPncRxERAn[LucPncIndex] == COMM_TRUE)
      #endif
      )
  {
    /*PNC Sub State changed to : PNC_REQUESTED*/
    ComM_GaaSubPNCMode[LucPncIndex] = PNC_REQUESTED;

    /*Indication to BswM Module*/
    BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucPncIndex].ddPncId,
      PNC_REQUESTED);

  } /* End of if ((ComM_GaaRequestedPNCMode[LucPncIndex] == PNC_USER_FULL_COMM)
     **/
  #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)

  /* Conditions:  WakeUp Indication  */
  else if (ComM_GaaPNCWakeupIndication[LucPncIndex] == COMM_TRUE)
  {
    ComM_GaaPNCWakeupIndication[LucPncIndex] = COMM_FALSE;

    /* PNC Sub State changed to : PNC_PREPARE_SLEEP */
    ComM_GaaSubPNCMode[LucPncIndex] = PNC_PREPARE_SLEEP;

    /*Indication to BswM Module*/
    BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucPncIndex].ddPncId,
      PNC_PREPARE_SLEEP);
  }
  #endif /* End of if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */

  /* Conditions: No Local Request */
  else if (ComM_GaaPncRxEIRA[LucPncIndex] == COMM_TRUE)
  {
    /*PNC Sub State changed to : PNC_READY_SLEEP*/
    ComM_GaaSubPNCMode[LucPncIndex] = PNC_READY_SLEEP;

    /*Indication to BswM Module*/
    BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucPncIndex].ddPncId,
      PNC_READY_SLEEP);
  }
  else
  {
    /* No State Change */
  }
} /* End of ComM_PNCNoMode */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
  *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
  *STD_ON)) */


/*******************************************************************************
** Function Name        : ComM_PNCComSigFullCom                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve PNC entry activities in    **
**                        COMM_FULL_COMMUNICATION for the corresponding       **
**                        Channel index                                       **
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
**                        ComM_GaaChannelToPncMapping, ComM_GaaChannels,      **
**                        ComM_GaaSubPNCMode,                                 **
**                        ComM_GaaSignalTx, ComM_GaaComSignal, ComM_GaaPncs   **
**                        ComM_GaaPncTimeCnt                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_PNCNetwReq(), Com_SendSignal()                 **
*******************************************************************************/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_PNCComSigFullCom(uint8 LucIndex)
{
  /* The variable is used for PNC Index */
  PNCHandleType LddPncIndex;

  /* The variable is used for PNC ID */
  PNCHandleType LddPncId;

  NetworkHandleType LddChannelId;

  /* The variable is used for PNC Count */
  uint8 LucPncCount;

  /* The variable is used for PNC Indexing */
  PNCHandleType LddPncInx;

  /* The variable is used for storing Byte Index */
  uint8 LucByteIndex;

  /* The variable is used for storing Bit Index */
  uint8 LucBitIndex;

  /* The variable is used to store Mask Value */
  uint8 LucMask;

  /* The variable is used to store Mask Value to clear bit */
  uint8 LucMaskClear;

  /* The variable is used for Signal Indexing */
  uint16 LusSignalIndex;

  /* The variable is used for Signal counting */
  uint16 LusSignalCount;

  /* The variable is used to store signal ID */
  uint16 LusSignalHandleId;

  /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
  /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
  if (ComM_GaaChannels[LucIndex].blChannelPnc == COMM_TRUE)
  {
    LddPncIndex = ComM_GaaChannels[LucIndex].ucPncIndex;
    LucPncCount = ComM_GaaChannels[LucIndex].ucPncCount;
    /*State transitions of the PNC state machines */
    while (LucPncCount != COMM_ZERO)
    {
      /* Decrement the pnc count */
      LucPncCount--;

      /* ComM_GaaChannelToPncMapping[] :The Map provides Index*/
      LddPncInx = ComM_GaaChannelToPncMapping[LddPncIndex];

      /*Calculating the PNC ID for the Pnc Index*/
      LddPncId = ComM_GaaPncs[LddPncInx].ddPncId;

      /*Calculation Of Byte Index*/
      /* #20992 */
      LucByteIndex = (uint8)(LddPncId >> COMM_THREE) - COMM_PNC_VECTOR;

      /*Calculation Of Bit Index within the Byte */
      LucBitIndex = (uint8)(LddPncId % COMM_EIGHT);

      /*Calculating the Mask Value for the bit Index*/
      LucMask = (uint8)((uint8)COMM_ONE << LucBitIndex);

      if (ComM_GaaSubPNCMode[LddPncInx] != PNC_NO_COMMUNICATION)
      {
        /* On entry of PNC sub state PNC_REQUESTED */
        if (ComM_GaaSubPNCMode[LddPncInx] == PNC_REQUESTED)
        {
          ComM_PNCNetwReq(LddPncInx, LucByteIndex, LucMask, LucIndex);
        }
        /* On entry PNC sub state PNC_READY_SLEEP */
        else if (ComM_GaaSubPNCMode[LddPncInx] == PNC_READY_SLEEP)
        {
          /* polyspace<MISRA-C3:14.3 ::Not a defect Justified> Condition will be 
             executed based on the input values */
          /* polyspace<DEFECT:USELESS_IF ::Not a defect Justified> Condition will be 
             executed based on the input values */
          if ((ComM_GaaSignalTx[LucIndex][LucByteIndex] & (LucMask)) != COMM_FALSE)
          {
            LucMaskClear = (~LucMask);

            ComM_GaaSignalTx[LucIndex][LucByteIndex] =
              (ComM_GaaSignalTx[LucIndex][LucByteIndex] & LucMaskClear);

            /* Signal Instance Index associated with the PNC */
            LusSignalIndex = ComM_GaaPncs[LddPncInx].usComSignalIndex;

            /* Signal Count of the PNC */
            LusSignalCount = ComM_GaaPncs[LddPncInx].usNoOfComSignal;
            /* polyspace<DEFECT:DEAD_CODE:Not a defect: Justify with annotations> condition will be executed based on the configured values */
            /* polyspace<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
            while (LusSignalCount != COMM_ZERO)
            {
              if (ComM_GaaComSignal[LusSignalIndex].ucComMPncComSigDir ==
                  COMM_TX)
              {
                LusSignalHandleId =
                  ComM_GaaComSignal[LusSignalIndex].ddComMComSigId;

                LddChannelId = ComM_GaaComSignal[LusSignalIndex].ddComMChannelId;

                (void)Com_SendSignal(LusSignalHandleId,
                  (const void*)ComM_GaaSignalTx[LddChannelId]);
              }
              LusSignalIndex++;
              LusSignalCount--;
            }
          } /* End of if (ComM_GaaSignalTx[LucIndex][LucByteIndex] & (LucMask)) != COMM_FALSE */
        } /* End of if (ComM_GaaSubPNCMode[LddPncInx] == PNC_READY_SLEEP) */
          /* On entry of PNC sub state PNC_PREPARE_SLEEP */

        else
        {
          /* #13018 */
          if (ComM_GaaPncTimeCnt[LddPncInx] != COMM_ZERO)
          {
            /* Decrement the PNC timer for the Channel */
            ComM_GaaPncTimeCnt[LddPncInx]--;
          }
        }
      } /* End of if (ComM_GaaSubPNCMode[LddPncInx] != PNC_NO_COMMUNICATION) */
      LddPncIndex++;
    } /*End of PNC Counts of Channel*/
  } /* End of if (ComM_GaaChannels[LucIndex].blChannelPnc == COMM_TRUE) */
} /* End of ComM_PNCComSigFullCom */

/* END OF FULL COMM*/
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
        *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */

/*******************************************************************************
** Function Name        : ComM_PNCNetwReq                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve PNC entry activities in    **
**                        PNC_FULL_COMMUNICATION sub state PNC_REQUESTED      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : LucPncInx, LucByteIndex, LucMask, LucIndex          **
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
**                        ComM_GaaPncs, ComM_GaaComSignal,                    **
**                        ComM_GaaRequestedPNCMode, ComM_GaaChannelMapArray   **
**                        ComM_GaaPncRxERASignal                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Com_SendSignal(), Nm_NetworkRequest()               **
*******************************************************************************/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_PNCNetwReq(uint8 LucPncInx, uint8 LucByteIndex, uint8
  LucMask, uint8 LucIndex)
{
  /* The variable is used for Signal Indexing */
  uint16 LusSignalIndex;

  NetworkHandleType LddChannelId;

  /* The variable is used for Signal counting */
  uint16 LusSignalCount;

  /* The variable is used to store signal ID */
  uint16 LusSignalHandleId;

  #if (COMM_PNC_GW_ENABLED == STD_ON)
  /* The variable is used to store Mask Value to clear bit */
  uint8 LucMaskClear;

  NetworkHandleType LddChannelIndex;

  /* The variable to store the channel ID*/
  NetworkHandleType LddCHId;

  /* The variable is used for Passive Gateway: Active Rx ERA  */
  boolean LblActiveRxERA;

  /* The variable is used for Passive Gateway: User No COMM Request */
  boolean LblPncUserFlag;

  /* variable to store the count of channels */
  uint8 LucNoOfChannelsInPNC;

  /* variable to store the start index of channel from pnc */
  NetworkHandleType LddChannelIndexInPNC;  

  NetworkHandleType LddChannelIdTmp;

  /* Initialization of ACTIVE Rx ERA */
  LblActiveRxERA = COMM_FALSE;

  /* Initialization of user No communication Flag */
  LblPncUserFlag = COMM_FALSE;  
  
  #endif /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */

  /* On entry of PNC sub state  Com_SendSignal()
   * and ComM_PncNetworkRequest()*/
  if((ComM_GaaSignalTx[LucIndex][LucByteIndex] & (LucMask)) == COMM_FALSE)
  {
   /* PNC Bit for all Com signals assigned as TX: 1*/
   ComM_GaaSignalTx[LucIndex][LucByteIndex] =
   (ComM_GaaSignalTx[LucIndex][LucByteIndex] | (LucMask));

    #if (COMM_PNC_GW_ENABLED == STD_ON)


/////////////////////////////////////////////////////////////////////////////////////

    /* If all users request No Communication */
    if (ComM_GaaRequestedPNCMode[LucPncInx] == PNC_USER_NO_COMM)
    {
      LblPncUserFlag = COMM_TRUE;
    }
    /* Signal Instance Index associated with the PNC */
    LusSignalIndex = ComM_GaaPncs[LucPncInx].usComSignalIndex;

    /* Signal Count of the PNC */
    LusSignalCount = ComM_GaaPncs[LucPncInx].usNoOfComSignal;
    while (LusSignalCount != COMM_ZERO)
    {
      /* Get the Channel Id from Com Signal*/
      LddCHId = ComM_GaaComSignal[LusSignalIndex].ddComMChannelId;
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      LddChannelIndex = ComM_GaaChannelMapArray[LddCHId];
      #else
      LddChannelIndex = LddCHId;
      #endif

      if ((ComM_GaaChannels[LddChannelIndex].ucPncGatewayType ==
           COMM_ACTIVE_GW) &&
          (ComM_GaaComSignal[LusSignalIndex].ucComMPncComSigDir ==
           COMM_RX) &&
          (ComM_GaaComSignal[LusSignalIndex].ucComMPncComSignalKind
           == COMM_ERA))
      {
        if (ComM_GaaPncRxERASignal[((uint16)LucPncInx * (uint16)ComM_GucTotalSignals) + LusSignalIndex] == COMM_TRUE)
        {
          LblActiveRxERA = COMM_TRUE;

          /* Condition to break from Loop*/
          LusSignalCount = COMM_ZERO;
        }
        else
        {
          /* Decrement the Number of Signals */
          LusSignalCount--;
        }
      }
      else
      {
        /* Decrement the Number of Signals */
        LusSignalCount--;
      }
      /* Increment the Signal Index */
      LusSignalIndex++;
    }
  
    // if (((!LblActiveRxERA) && LblPncUserFlag) == COMM_TRUE)
    if ((LblActiveRxERA == (boolean)COMM_FALSE) && (LblPncUserFlag == (boolean)COMM_TRUE))
    {
      LucMaskClear = (~LucMask);
      /* PNC Bit for all Com signals assigned as TX: 0*/
      ComM_GaaSignalTx[LddChannelIndex][LucByteIndex] =
        (ComM_GaaSignalTx[LddChannelIndex][LucByteIndex] & LucMaskClear);
    } /* End of if (((!LblActiveRxERA) && LblPncUserFlag) == COMM_TRUE) */

    /* Get the Channels associated with the PNC*/
    LucNoOfChannelsInPNC = ComM_GaaPncs[LucPncInx].ucNoOfChannelPnc;

    /*Channel Index */
    LddChannelIndexInPNC = ComM_GaaPncs[LucPncInx].ucChannelPncIndex;
    while (LucNoOfChannelsInPNC != COMM_ZERO)
    {
      /* Get the Channel ID from PNC Index Array */
      /* polyspace<MISRA-C3:18.1, :Not a defect:Justified> Pointer range is valid and validated by DET */
      /* polyspace<RTE:OBAI: Not a defect: Justified> Array index is in range and valid */
      /* polyspace<DEFECT:OUT_BOUND_ARRAY:Not a defect: Justified> Array index in range and handled by generation tool */
      LddChannelIdTmp = ComM_GaaChnPncInxArr[LddChannelIndexInPNC];
      #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
      LddChannelId = ComM_GaaChannelMapArray[LddChannelIdTmp];
      #else
      LddChannelId = LddChannelIdTmp;
      #endif

      /* The channel is ACTIVE */
      /* polyspace<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
      /* polyspace:begin<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
      if (ComM_GaaChannels[LddChannelId].ucPncGatewayType == COMM_ACTIVE_GW)
      {
        /* Signal Instance Index associated with the PNC */
        LusSignalIndex = ComM_GaaPncs[LucPncInx].usComSignalIndex;

        /* Signal Count of the PNC */
        LusSignalCount = ComM_GaaPncs[LucPncInx].usNoOfComSignal;
        while (LusSignalCount != COMM_ZERO)
        {
          /* Get the Channel Id from Com Signal*/
          LddCHId = ComM_GaaComSignal[LusSignalIndex].ddComMChannelId;
          #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
          LddChannelIndex = ComM_GaaChannelMapArray[LddCHId];
          #else
          LddChannelIndex = LddCHId;
          #endif        
          if ((LddChannelId == LddChannelIndex) && (ComM_GaaComSignal[LusSignalIndex].ucComMPncComSigDir == COMM_TX))
          {
            /* Get the signal ID */
            LusSignalHandleId = ComM_GaaComSignal[LusSignalIndex].ddComMComSigId;

            /* Invoke ComSendSignal of Com */
            (void)Com_SendSignal(LusSignalHandleId,
              (const void*)ComM_GaaSignalTx[LddChannelIndex]);
          }
          LusSignalIndex++;
          LusSignalCount--;
        }
      } /* End of if (ComM_GaaChannels[LucIndex].ucPncGatewayType ==
         *COMM_ACTIVE_GW) */
      /* The channel is PASSIVE */
      /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
      else if (ComM_GaaChannels[LddChannelId].ucPncGatewayType == COMM_PASSIVE_GW)
      {
        /* Signal Instance Index associated with the PNC */
        LusSignalIndex = ComM_GaaPncs[LucPncInx].usComSignalIndex;

        /* Signal Count of the PNC */
        LusSignalCount = ComM_GaaPncs[LucPncInx].usNoOfComSignal;
        while (LusSignalCount != COMM_ZERO)
        {
          /* Get the Channel Id from Com Signal*/
          LddCHId = ComM_GaaComSignal[LusSignalIndex].ddComMChannelId;
          #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
          LddChannelIndex = ComM_GaaChannelMapArray[LddCHId];
          #else
          LddChannelIndex = LddCHId;
          #endif
          if ((LddChannelId == LddChannelIndex) && (ComM_GaaComSignal[LusSignalIndex].ucComMPncComSigDir == COMM_TX))
          {
            /* Get the signal ID */
            LusSignalHandleId =
              ComM_GaaComSignal[LusSignalIndex].ddComMComSigId;

            /* Invoke ComSendSignal of Com */
            (void)Com_SendSignal(LusSignalHandleId,
              (const void*)ComM_GaaSignalTx[LddChannelId]);
          }
          LusSignalIndex++;
          LusSignalCount--;
        }
      } /* End of if (ComM_GaaChannels[LucIndex].ucPncGatewayType ==
         *COMM_PASSIVE_GW) */
      else
      {
        /* To Avoid MISRA-C */
      }


    
      /* Decrement the Number of channels */
      LucNoOfChannelsInPNC--;

      /* Increment the channel Index */
      LddChannelIndexInPNC++;

      /* Network request for the channel under PNC, Provided FULL NM variant*/
      /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
      if ((ComM_GaaChannels[LddChannelId].blPncNmRequest == COMM_TRUE) &&
        (ComM_GaaChannels[LddChannelId].ucNmVariant == COMM_NMVARIANT_FULL))
      {

        #if 0
        if(LddChannelId == 0)
        {
        /* Invoke Network Request from PNC Entry*/
        //(void)Nm_NetworkRequest(ComM_GaaChannels[LddChannelId].ddChannelId);
        //(void)Nm_NetworkRequest(ComM_GaaChannels[LddChannelId].ddChannelId);
        }
        else
        {
                /* Request Nm Bus Communication */
              /* Switch to Full Communication Mode from No Communication */
        ComM_SwitchComMMode(LddChannelId, COMM_FULL_COMMUNICATION);

        /* Change sub state to Network Requested */
        ComM_GaaSubComMode[LddChannelId] = COMM_FULL_COM_NETWORK_REQUESTED;

        /* Start the Min amount of duration in full Communication counter */
        ComM_GaaTimeCnt[LddChannelId] = ComM_GaaChannels[LddChannelId].ddMinFullComMode;
        }
        #endif

        ComM_SwitchComMMode(LddChannelId, COMM_FULL_COMMUNICATION);

        /* Change sub state to Network Requested */
        ComM_GaaSubComMode[LddChannelId] = COMM_FULL_COM_NETWORK_REQUESTED;

        /* Start the Min amount of duration in full Communication counter */
        ComM_GaaTimeCnt[LddChannelId] = ComM_GaaChannels[LddChannelId].ddMinFullComMode;

        (void)Nm_NetworkRequest(ComM_GaaChannels[LddChannelId].ddChannelId);
      }
      /* polyspace:end<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
    }
/////////////////////////////////////////////////////////////////////////////////////    


    #if 0
    /* The channel is ACTIVE */
    if (ComM_GaaChannels[LucIndex].ucPncGatewayType == COMM_ACTIVE_GW)
    {
      /* Signal Instance Index associated with the PNC */
      LusSignalIndex = ComM_GaaPncs[LucPncInx].usComSignalIndex;

      /* Signal Count of the PNC */
      LusSignalCount = ComM_GaaPncs[LucPncInx].usNoOfComSignal;
      while (LusSignalCount != COMM_ZERO)
      {
        if (ComM_GaaComSignal[LusSignalIndex].ucComMPncComSigDir == COMM_TX)
        {
          /* Get the signal ID */
          LusSignalHandleId = ComM_GaaComSignal[LusSignalIndex].ddComMComSigId;

          /* Invoke ComSendSignal of Com */
          (void)Com_SendSignal(LusSignalHandleId,
            (const void*)ComM_GaaSignalTx);
        }
        LusSignalIndex++;
        LusSignalCount--;
      }
    } /* End of if (ComM_GaaChannels[LucIndex].ucPncGatewayType ==
       *COMM_ACTIVE_GW) */
    /* The channel is PASSIVE */
    else if (ComM_GaaChannels[LucIndex].ucPncGatewayType == COMM_PASSIVE_GW)
    {
      /* If all users request No Communication */
      if (ComM_GaaRequestedPNCMode[LucPncInx] == PNC_USER_NO_COMM)
      {
        LblPncUserFlag = COMM_TRUE;
      }
      /* Signal Instance Index associated with the PNC */
      LusSignalIndex = ComM_GaaPncs[LucPncInx].usComSignalIndex;

      /* Signal Count of the PNC */
      LusSignalCount = ComM_GaaPncs[LucPncInx].usNoOfComSignal;
      while (LusSignalCount != COMM_ZERO)
      {
        /* Get the Channel Id from Com Signal*/
        LddCHId = ComM_GaaComSignal[LusSignalIndex].ddComMChannelId;
        #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
        LddChannelIndex = ComM_GaaChannelMapArray[LddCHId];
        #else
        LddChannelIndex = LddCHId;
        #endif

        if ((ComM_GaaChannels[LddChannelIndex].ucPncGatewayType ==
             COMM_ACTIVE_GW) &&
            (ComM_GaaComSignal[LusSignalIndex].ucComMPncComSigDir ==
             COMM_RX) &&
            (ComM_GaaComSignal[LusSignalIndex].ucComMPncComSignalKind
             == COMM_ERA))
        {
          if (ComM_GaaPncRxERASignal[LucPncInx*ComM_GucTotalSignals + LusSignalIndex] == COMM_TRUE)
          {
            LblActiveRxERA = COMM_TRUE;

            /* Condition to break from Loop*/
            LusSignalCount = COMM_ZERO;
          }
          else
          {
            /* Decrement the Number of Signals */
            LusSignalCount--;
          }
        }
        else
        {
          /* Decrement the Number of Signals */
          LusSignalCount--;
        }
        /* Increment the Signal Index */
        LusSignalIndex++;
      }

      if (((!LblActiveRxERA) && LblPncUserFlag) == COMM_TRUE)
      {
        LucMaskClear = (~LucMask);
        /* PNC Bit for all Com signals assigned as TX: 0*/
        ComM_GaaSignalTx[LucByteIndex] =
          (ComM_GaaSignalTx[LucByteIndex] & LucMaskClear);
      } /* End of if (((!LblActiveRxERA) && LblPncUserFlag) == COMM_TRUE) */

      /* Signal Instance Index associated with the PNC */
      LusSignalIndex = ComM_GaaPncs[LucPncInx].usComSignalIndex;

      /* Signal Count of the PNC */
      LusSignalCount = ComM_GaaPncs[LucPncInx].usNoOfComSignal;
      while (LusSignalCount != COMM_ZERO)
      {
        if (ComM_GaaComSignal[LusSignalIndex].ucComMPncComSigDir == COMM_TX)
        {
          /* Get the signal ID */
          LusSignalHandleId =
            ComM_GaaComSignal[LusSignalIndex].ddComMComSigId;

          /* Invoke ComSendSignal of Com */
          (void)Com_SendSignal(LusSignalHandleId,
            (const void*)ComM_GaaSignalTx);
        }
        LusSignalIndex++;
        LusSignalCount--;
      }
    } /* End of if (ComM_GaaChannels[LucIndex].ucPncGatewayType ==
       *COMM_PASSIVE_GW) */
    else
    {
      /* To Avoid MISRA-C */
    }
    #endif
    #else /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */

    /* Signal Instance Index associated with the PNC */
    LusSignalIndex = ComM_GaaPncs[LucPncInx].usComSignalIndex;

    /* Signal Count of the PNC */

    LusSignalCount = ComM_GaaPncs[LucPncInx].usNoOfComSignal;
    /* polyspace<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
    /* polyspace<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
    while (LusSignalCount != COMM_ZERO)
    {
      if (ComM_GaaComSignal[LusSignalIndex].ucComMPncComSigDir == COMM_TX)
      {
        /* Get the signal ID */
        LusSignalHandleId = ComM_GaaComSignal[LusSignalIndex].ddComMComSigId;
        LddChannelId = ComM_GaaComSignal[LusSignalIndex].ddComMChannelId;

        /* Invoke ComSendSignal of Com */
        (void)Com_SendSignal(LusSignalHandleId, (const void*)ComM_GaaSignalTx[LddChannelId]);
      }
      LusSignalIndex++;
      LusSignalCount--;
    }

    /* Network request for the channel under PNC, Provided FULL NM variant*/
    /* polyspace<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
    /* polyspace<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
    /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
    if ((ComM_GaaChannels[LucIndex].blPncNmRequest == COMM_TRUE) &&
      (ComM_GaaChannels[LucIndex].ucNmVariant == COMM_NMVARIANT_FULL))
    {
      /* Invoke Network Request from PNC Entry*/
      (void)Nm_NetworkRequest(ComM_GaaChannels[LucIndex].ddChannelId);
    }

    #endif /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */

    #if 0
    /* Network request for the channel under PNC, Provided FULL NM variant*/
    if ((ComM_GaaChannels[LucIndex].blPncNmRequest == COMM_TRUE) &&
      (ComM_GaaChannels[LucIndex].ucNmVariant == COMM_NMVARIANT_FULL))
    {
      /* Invoke Network Request from PNC Entry*/
      (void)Nm_NetworkRequest(ComM_GaaChannels[LucIndex].ddChannelId);
    }
    #endif
  } /* End of if((ComM_GaaSignalTx[LucIndex][LucByteIndex] & (LucMask)) == COMM_FALSE) */
} /* End of ComM_PNCNetwReq */

/* END OF FULL COMM*/
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
        *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */
/* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Pointer is not outside its bounds - Pointer is generated by Generator*/
/*******************************************************************************
** Function Name        : ComM_FullComNetwReq                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve COMM_FULL_COMMUNICATION sub**
**                        state COMM_FULL_COM_NETWORK_REQUESTED.              **
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
**                        ComM_GaaChannels, ComM_GaaNmRequested,              **
**                        ComM_GaaChannelInhibition, ComM_GblLimitEcuToNoCom, **
**                        ComM_GaaSubComMode, ComM_GaaTimeCnt,                **
**                        ComM_GaaReqedComModeCnt, ComM_GaaInhibitionReqst,   **
**                        ComM_GaaDcmActiveDiagnostic, ComM_GaaNmIndication   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Nm_NetworkRequest(), ComM_FullComNetwReqSubTwo()    **
**                        ComM_FullComNetwReqSubOne(),ComM_SwitchComMMode()   **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_FullComNetwReq(uint8 LucIndex)
{
  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

  /* Variable to store the flag if NM is in different mode */
  uint8 LucFlag;
  #endif

  /* Variable to store the Nm variant value */
  uint8 LucNmVarient;
  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)

  /* Variable to store Nm request in inhibition mode */
  boolean LblNmReq;
  Std_ReturnType LenReturnVal = E_NOT_OK;
  #endif

  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)

  /* Initialize Nm request flag to COMM_FALSE */
  LblNmReq = COMM_FALSE;
  
  #endif
  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

  /* Clear Timer State */
  LucFlag = COMM_ZERO;
  #endif

  /* Get Nm Variant*/
  LucNmVarient = ComM_GaaChannels[LucIndex].ucNmVariant;
  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

  /* Check if Nm Variant is light or None and Check for
   *     No Full Comm Mode or Active Diagnostic Disabled  */
  /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
  /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
  if ((LucNmVarient == COMM_NMVARIANT_LIGHT) ||
      (LucNmVarient == COMM_NMVARIANT_NONE))
  {
    LucFlag = ComM_FullComNetwReqSubOne(LucIndex);
  }
  #endif /* if Nm Variant is light or none */
  #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))

  /* Check for channel inhibition condition and
       Limit ECU to No Com by masking with 0xF0 & check if bit 4 is set*/
  if((((ComM_GaaChannelInhibition[LucIndex] &
    COMM_LIMITCHANNELTONOCOMM_MASK_SET) ==
    COMM_LIMITCHANNELTONOCOMM_MASK_SET) || (ComM_GblLimitEcuToNoCom ==
    COMM_TRUE)) && (ComM_GaaDcmActiveDiagnostic[LucIndex] != COMM_TRUE))
  {
    /* Change sub state to Ready Sleep */
    ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_READY_SLEEP;
    /* Clear User Request, if any */
    if(ComM_GaaReqedComModeCnt[LucIndex] != COMM_ZERO)
    {
      ComM_GaaReqedComModeCnt[LucIndex] = COMM_ZERO;
    }

    #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)

    /* Check if Nm Variant is light or None and Check for
     *   No Full Comm Mode or Active Diagnostic Disabled  */
    /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
    /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
    if (LucNmVarient == COMM_NMVARIANT_LIGHT)
    {
      /* Start the Nm light time out duration in full
       *   Communication */
      ComM_GaaTimeCnt[LucIndex] = ComM_GaaChannels[LucIndex].ddNmLightTimeout;
    }
    #endif
  } /* End of if ((((ComM_GaaChannelInhibition[LucIndex] & */
  #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
          *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */

  #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)

  /* Check if NM Variant is FULL */
  /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
  /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
  if (LucNmVarient == COMM_NMVARIANT_FULL)
  {
    /* Enter Data Protection */
    SchM_Enter_ComM_NM_INDICATION_PROTECTION();
    /* To Silent Communication */    
    if ((ComM_GaaNmIndication[LucIndex] == COMM_PREPBUSSLEEPMODE_IND)
      && (ComM_GaaNmRequestProcessing[LucIndex] == COMM_FALSE))
    {
      /* Exit Data Protection */
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
      /* Switch to Silent Comm Mode from Full Communication */
      ComM_SwitchComMMode(LucIndex, COMM_SILENT_COMMUNICATION);
      ComM_GaaNmIndication[LucIndex] = COMM_ZERO;
    }
    /* Check if NM is already requested */
    else if (ComM_GaaNmRequested[LucIndex] != COMM_TWO)
    {
      #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
        (COMM_MODE_LIMITATION_ENABLED == STD_ON))

      /* Check For Prevent WakeUp Inhibition */
      if ((ComM_GaaChannelInhibition[LucIndex] &
           COMM_PREVENTWAKEUP_MASK_SET) != COMM_PREVENTWAKEUP_MASK_SET)
      {
      #endif

        if ((ComM_GaaReqedComModeCnt[LucIndex] != COMM_ZERO)
          || (ComM_GaaDcmActiveDiagnostic[LucIndex] == COMM_TRUE)
          #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
          || (ComM_GaaInhibitionReqst[LucIndex] != COMM_ZERO)
          #endif
          )
        {
          /* Set a flag */
          LblNmReq = COMM_TRUE;
        } /* End of if ((ComM_GaaChannelInhibition[LucIndex] & */

      #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
        (COMM_MODE_LIMITATION_ENABLED == STD_ON))
      } /* End of if (ComM_GaaNmRequested[LucIndex] != COMM_TWO) */
        /* Active diagnostic shall not be inhibited */
      else if (ComM_GaaDcmActiveDiagnostic[LucIndex] == COMM_TRUE)
      {
        /* Set a flag */
        LblNmReq = COMM_TRUE;
      }
      else
      {
      /* To avoid MISRA warning */
      }
      #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
              *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */
      if (LblNmReq == COMM_TRUE)
      {
        /* 25120 */
        /* Request Nm Bus Communication */
        LenReturnVal = Nm_NetworkRequest(ComM_GaaChannels[LucIndex].ddChannelId);

        if(E_OK == LenReturnVal)
        {
          /* Set Flag for Nm is requested for network */
          ComM_GaaNmRequested[LucIndex] = COMM_TWO;
          ComM_GaaNmRequestProcessing[LucIndex] = COMM_TRUE;
        }else{
          /* To do Nothing */
        }
      }
      /* Exit Data Protection */
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    }
    else
    {
      /* Exit Data Protection */
      SchM_Exit_ComM_NM_INDICATION_PROTECTION();
    }
    
  } /* End of if (LucNmVarient == COMM_NMVARIANT_FULL) */
  #endif /* (COMM_FULL_NMVARIANT_SUPPORT == STD_ON) */

  /* If the Nm is present or if the timer has not expired when Nm is
   *   Light or None */
  #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

  if (LucFlag != COMM_ONE)
  #endif
  {
    ComM_FullComNetwReqSubTwo(LucIndex);
  }
  #if ((COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON) &&\
  ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
   (COMM_ETHNETWORK_PRESENT == STD_ON)))

  /* To Silent Communication */
  if ((LucNmVarient == COMM_NMVARIANT_PASSIVE) &&
      (ComM_GaaNmIndication[LucIndex] == COMM_PREPBUSSLEEPMODE_IND))
  {
    /* Switch to Silent Comm Mode from Full Communication */
    ComM_SwitchComMMode(LucIndex, COMM_SILENT_COMMUNICATION);
    ComM_GaaNmIndication[LucIndex] = COMM_ZERO;
  }
  #endif /* End of if ((COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON) &&
    *((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_ETHNETWORK_PRESENT ==
    *STD_ON))) */

  /* If Nm indicates Bus Sleep */
  if ((ComM_GaaNmIndication[LucIndex] == COMM_BUSSLEEPMODE_IND)
      #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
      && (ComM_GaaNmRequestProcessing[LucIndex] == COMM_FALSE)
      #endif
      )
  {
    ComM_SwitchComMMode(LucIndex, COMM_NO_COMMUNICATION);
    ComM_GaaNmIndication[LucIndex] = COMM_ZERO;
  }
} /* End of ComM_FullComNetwReq */

/* END OF FULL COMM*/
#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_FullComReadySleep                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall serve COMM_FULL_COMMUNICATION sub**
**                        state COMM_FULL_COM_READY_SLEEP.                    **
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
**                        ComM_GaaChannelInhibition, ComM_GblLimitEcuToNoCom, **
**                        ComM_GaaSubComMode,ComM_GaaTimeCnt,ComM_GaaChannels,**
**                        ComM_GaaNmRequested, ComM_GaaReqedComModeCnt,       **
**                        ComM_GaaDcmActiveDiagnostic, ComM_GaaNmIndication   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Nm_NetworkRelease(), ComM_SwitchComMMode()          **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COMM_CODE) ComM_FullComReadySleep(uint8 LucIndex)
{
  #if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON))
  /* Variable to store the Nm variant value */
  uint8 LucNmVarient;
  Std_ReturnType LenReturnVal = E_NOT_OK;
  /* Get Nm Variant*/
  LucNmVarient = ComM_GaaChannels[LucIndex].ucNmVariant;
  #endif
  /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
  /* polyspace<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
  /* polyspace<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
  /* If the bus type is other than Internal */
  if (ComM_GaaChannels[LucIndex].ucBusType != COMM_INTERNAL)
  {
    #if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)

    /* Check NM Variant is FULL */
    /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
    /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
    if (LucNmVarient == COMM_NMVARIANT_FULL)
    {
      if (ComM_GaaNmRequested[LucIndex] != COMM_ZERO)
      {
        /* Release Nm Bus Communication */
        LenReturnVal = Nm_NetworkRelease(ComM_GaaChannels[LucIndex].ddChannelId);
        /* #22924 */
        if(E_OK == LenReturnVal)
        {
          /* Resetting the Nm Request global variable */
          ComM_GaaNmRequested[LucIndex] = COMM_ZERO;
        }else{
          /* Nothing To Do */
        }
      }
    }
    #endif /* #if(COMM_FULL_NMVARIANT_SUPPORT == STD_ON) */
    #if (((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
          (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON)) &&\
         ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
          (COMM_ETHNETWORK_PRESENT == STD_ON)))

    /* To Silent Communication */
    if (((LucNmVarient == COMM_NMVARIANT_FULL) ||
         (LucNmVarient == COMM_NMVARIANT_PASSIVE)) &&
        (ComM_GaaNmIndication[LucIndex] == COMM_PREPBUSSLEEPMODE_IND))
    {
      /* Switch to Silent Comm Mode from Full Communication */
      ComM_SwitchComMMode(LucIndex, COMM_SILENT_COMMUNICATION);
      ComM_GaaNmIndication[LucIndex] = COMM_ZERO;
    }
    #endif /* End of if (((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||
            * (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON)) &&
            * ((COMM_CANNETWORK_PRESENT == STD_ON) ||(COMM_ETHNETWORK_PRESENT ==
            * STD_ON))) */
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))

    if ((ComM_GaaChannelInhibition[LucIndex] &
         COMM_PREVENTWAKEUP_MASK_SET) != COMM_PREVENTWAKEUP_MASK_SET)
    #endif
    {
      /*
       * Check if requested mode is NO Communication
       * or if Bus Sleep Mode indication
       */
      if ((ComM_GaaReqedComModeCnt[LucIndex] == COMM_ZERO) &&
          (ComM_GaaNmIndication[LucIndex] == COMM_BUSSLEEPMODE_IND))
      {
        /* Switch to No communication */
        ComM_SwitchComMMode(LucIndex, COMM_NO_COMMUNICATION);
        ComM_GaaNmIndication[LucIndex] = COMM_ZERO;
      }
    }
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    else if (ComM_GaaNmIndication[LucIndex] == COMM_BUSSLEEPMODE_IND)
    {
      /* Switch to No communication */
      ComM_SwitchComMMode(LucIndex, COMM_NO_COMMUNICATION);
      ComM_GaaNmIndication[LucIndex] = COMM_ZERO;
    }
    else
    {
      /* To avoid MISRA warning */
    }
    #endif /* End of if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||
            *(COMM_MODE_LIMITATION_ENABLED == STD_ON)) */
    #if (COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON)
    /* Enter Data Protection */
    SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();
    
    /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
    /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
    if (LucNmVarient == COMM_NMVARIANT_LIGHT)
    {
      /* polyspace:begin<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
      /* polyspace:begin<MISRA-C3:2.1:Not a defect:Justified> condition will be executed based on the configured values */
      if (ComM_GaaTimeCnt[LucIndex] != (ComM_TimeType)COMM_ZERO)
      {
        /* Decrement the Timeout */
        ComM_GaaTimeCnt[LucIndex]--;

        /* If Timer expires */
        if (ComM_GaaTimeCnt[LucIndex] == (ComM_TimeType)COMM_ZERO)
        {
          /* Switch to No Communication from Full Communication */
          ComM_SwitchComMMode(LucIndex, COMM_NO_COMMUNICATION);
        }
      } /* End of if (ComM_GaaTimeCnt[LucIndex] != (ComM_TimeType)COMM_ZERO) */
      /* 2014.07.10 - Fixed Bug #1081 by KtKim */
      /* If configured LightTimeout is 0 then switch to NO COMM immediately */
      /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
      else if(ComM_GaaChannels[LucIndex].ddNmLightTimeout == (ComM_TimeType)COMM_ZERO)
      {
          /* Switch to No Communication from Full Communication */
          ComM_SwitchComMMode(LucIndex, COMM_NO_COMMUNICATION);
      }
      else
      {
        /* Switch to No Communication if NO COMM is requested and timer is 0 */
        if (ComM_GaaReqedComModeCnt[LucIndex] == COMM_ZERO)
        {
          ComM_SwitchComMMode(LucIndex, COMM_NO_COMMUNICATION);
        }
      }
      /* polyspace:end<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
      /* polyspace:end<MISRA-C3:2.1:Not a defect:Justified> condition will be executed based on the configured values */
    } /* End of if (LucNmVarient == COMM_NMVARIANT_LIGHT) */
    
    /* Exit Data Protection */
    SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
    #endif /* #if(COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) */
    #if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
    (COMM_MODE_LIMITATION_ENABLED == STD_ON))

    /* Check For Inhibition */
    if (((ComM_GaaChannelInhibition[LucIndex] &
          COMM_PREVENTWAKEUP_MASK_SET) != COMM_PREVENTWAKEUP_MASK_SET) &&
        (ComM_GblLimitEcuToNoCom != COMM_TRUE))
    #endif
    {
      if (ComM_GaaReqedComModeCnt[LucIndex] != COMM_ZERO)
      {
        /* Change sub state to Network Requested */
        ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_NETWORK_REQUESTED;
      }
    }

    if (ComM_GaaDcmActiveDiagnostic[LucIndex] == COMM_TRUE)
    {
      /* Change sub state to Network Requested */
      ComM_GaaSubComMode[LucIndex] = COMM_FULL_COM_NETWORK_REQUESTED;
    }
  } /* End of if (ComM_GaaChannels[LucIndex].ucBusType != COMM_INTERNAL) */

  /* If bus type is Internal */
  #if (COMM_NONE_NMVARIANT_SUPPORT == STD_ON)

  if ((ComM_GaaChannels[LucIndex].ucBusType == COMM_INTERNAL) &&
      (ComM_GaaReqedComModeCnt[LucIndex] == COMM_ZERO))
  {
    /* Switch to No Communication from Full Communication */
    ComM_SwitchComMMode(LucIndex, COMM_NO_COMMUNICATION);
    /* Switch submode to No Com pending request from Full Com */
    ComM_GaaSubComMode[LucIndex] = COMM_NO_COM_NO_PENDING_REQUEST;
  }
  #endif /* (COMM_NONE_NMVARIANT_SUPPORT == STD_ON) */
} /* End of ComM_FullComReadySleep */

/* END OF FULL COMM*/
#define COMM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET and pointer is not NULL */
/* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Pointer is not NULL and validated  */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

