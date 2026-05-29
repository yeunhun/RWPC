/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComM_EcuMBswM.c                                               **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of ComM EcuM/BswM Indication APIs                   **
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
** 1.9.5     08-Dec-2020   Jongsun Lim #25703                                 **
** 1.9.3     11-Aug-2020   JS Lim      #25552, #25554                         **
** 1.9.0     22-Aug-2019   JS Lim      #18922                                 **
** 1.8.0     23-Oct-2018   JS Lim      #13567                                 **
** 1.0.1     24-Aug-2015   KT Kim      Code change for Run Time Error(#2998)  **
** 1.0.0     12-Apr-2013   Daejun Park Initial version                        **
 *******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM_Internal.h"
#include "ComM_Ram.h"
#include "ComM_EcuMBswM.h"
#include "BswM_ComM.h"
#include "SchM_ComM.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COMM_ECUMBSWM_C_AR_RELEASE_MAJOR_VERSION    4
#define COMM_ECUMBSWM_C_AR_RELEASE_MINOR_VERSION    0
#define COMM_ECUMBSWM_C_AR_RELEASE_REVISION_VERSION 3

/* Software Version Information */
#define COMM_ECUMBSWM_C_SW_MAJOR_VERSION            1
#define COMM_ECUMBSWM_C_SW_MINOR_VERSION            10

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (COMM_ECUMBSWM_AR_RELEASE_MAJOR_VERSION !=\
     COMM_ECUMBSWM_C_AR_RELEASE_MAJOR_VERSION)
#error "ComM_EcuMBswM.c : Mismatch in Specification Major Version"
#endif
#if (COMM_ECUMBSWM_AR_RELEASE_MINOR_VERSION !=\
     COMM_ECUMBSWM_C_AR_RELEASE_MINOR_VERSION)
#error "ComM_EcuMBswM.c : Mismatch in Specification Minor Version"
#endif
#if (COMM_ECUMBSWM_AR_RELEASE_REVISION_VERSION !=\
     COMM_ECUMBSWM_C_AR_RELEASE_REVISION_VERSION)
#error "ComM_EcuMBswM.c : Mismatch in Specification Revision Version"
#endif
#if (COMM_ECUMBSWM_SW_MAJOR_VERSION != COMM_ECUMBSWM_C_SW_MAJOR_VERSION)
#error "ComM_EcuMBswM.c : Mismatch in Software Major Version"
#endif
#if (COMM_ECUMBSWM_SW_MINOR_VERSION != COMM_ECUMBSWM_C_SW_MINOR_VERSION)
#error "ComM_EcuMBswM.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_CommunicationAllowed                           **
**                                                                            **
** Service ID           : 0x35                                                **
**                                                                            **
** Description          : Indicates ComM when communication is allowed        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel, Allowed                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaCommunicationAllowed[],                     **
**                        ComM_GaaChannelMapArray[]                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck()                              **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
  ComM_CommunicationAllowed(NetworkHandleType Channel, boolean Allowed)
{
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType LddReturnValue;
  #endif

  /* Variable to store channel */
  NetworkHandleType LddChannelIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  LddReturnValue = ComM_ChannelDETCheck(Channel, COMM_COMMUNICATIONALLOWED_SID);

  /* Check, if no development error occurred */
  if (LddReturnValue == E_OK)
  #endif
  {
    /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET  */
    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    /* Get the channel id from the mapping array */    
    LddChannelIndex = ComM_GaaChannelMapArray[Channel];
    #else
    /* Channel Id is updated into local variable */
    LddChannelIndex = Channel;
    #endif
    
    if (Allowed == TRUE)
    {
      /* Variable stored if communication is allowed for ComM */
      ComM_GaaCommunicationAllowed[LddChannelIndex] = COMM_TRUE;
    }
    else
    {
      /* Variable stored if communication is not allowed for ComM */
      ComM_GaaCommunicationAllowed[LddChannelIndex] = COMM_FALSE;
    }
    /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
    /* polyspace:end<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET  */

  } /* End of if (LddReturnValue == E_OK) */
} /* End of ComM_CommunicationAllowed */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_EcuM_WakeUpIndication                          **
**                                                                            **
** Service ID           : 0x2a                                                **
**                                                                            **
** Description          : Notification of a WakeUp of the corresponding       **
**                        channel                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaWakeupIndication[],ComM_GaaChannels[],      **
**                        ComM_GaaChannelMapArray[],ComM_GaaPncTimeCnt[],     **
**                        ComM_GaaPNCWakeupIndication[],ComM_GaaSubPNCMode[], **
**                        ComM_GaaChannelToPncMapping[]                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_ECUM_WAKEUP_IND(),                  **
**                        SchM_Exit_ComM_ECUM_WAKEUP_IND(),                   **
**                        SchM_Enter_ComM_PNC_PREPARE_TIMER(),                **
**                        SchM_Exit_ComM_PNC_PREPARE_TIMER(),                 **
**                        SchM_Enter_ComM_PNC_WAKEUP_IND(),                   **
**                        SchM_Exit_ComM_PNC_WAKEUP_IND(),                    **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_EcuM_WakeUpIndication(NetworkHandleType Channel)
{
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType LddReturnValue;
  #endif

  /* Variable to store channel */
  NetworkHandleType LddChannelIndex;
  #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
  #if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
      (COMM_ETHNETWORK_PRESENT == STD_ON))
  /* Variable for Number of Pncs linked to the Channel */
  uint8 LucNoOfPncs;
  /* Variable for Pnc Index */
  uint8 LucPncIndex;
  /* Variable for channel to pnc mapping */
  uint8 LucIndex;
  #endif
  #endif

  #if(COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
  /* #13567 */ 
  uint8 LucChannelLoopIndex;
  #endif

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the channel is valid or not */
  LddReturnValue = ComM_ChannelDETCheck(Channel,
    COMM_ECUM_WAKEUPINDICATION_SID);

  /* Check, if no development error occurred */
  if (LddReturnValue == E_OK)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
  {    
    #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
    #if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
         (COMM_ETHNETWORK_PRESENT == STD_ON))
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)

    /* #13567 */ 
    for(LucChannelLoopIndex = COMM_ZERO; LucChannelLoopIndex < COMM_TOTAL_CHANNELS; LucChannelLoopIndex++)
    {
      LddChannelIndex = LucChannelLoopIndex;
      /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
      /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
      if (ComM_GaaChannels[LddChannelIndex].blChannelPnc == COMM_TRUE)
      {
        /* Number of Pncs linked to the Channel */
        LucNoOfPncs = ComM_GaaChannels[LddChannelIndex].ucPncCount;

        /* Index in the Pnc Index array in the User */
        LucPncIndex = ComM_GaaChannels[LddChannelIndex].ucPncIndex;

        /*-----Handling all the PNCs associated  with the channel------*/
        while (LucNoOfPncs != COMM_ZERO)
        {
          LucIndex = ComM_GaaChannelToPncMapping[LucPncIndex];

          /* Start the PNC Timer for the channel*/
          SchM_Enter_ComM_PNC_PREPARE_TIMER();
          ComM_GaaPncTimeCnt[LucIndex] =
          ComM_GaaChannels[LddChannelIndex].usPncPrepareSleepTimer;
          SchM_Exit_ComM_PNC_PREPARE_TIMER();
          /* Decrement the PNC Count*/
          LucNoOfPncs--;

          if (ComM_GaaSubPNCMode[LucIndex] == PNC_NO_COMMUNICATION)
          {
            /* Enter Data Protection */
            SchM_Enter_ComM_PNC_WAKEUP_IND();

            /* Update Status of Global Variable wake up indication*/
            ComM_GaaPNCWakeupIndication[LucIndex] = COMM_FALSE;

            /* Exit Data Protection */
            SchM_Exit_ComM_PNC_WAKEUP_IND();

            /* PNC Sub State changed to : PNC_PREPARE_SLEEP */
            ComM_GaaSubPNCMode[LucIndex] = PNC_PREPARE_SLEEP;

            /*Indication to BswM Module*/
            BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucIndex].ddPncId,
              PNC_PREPARE_SLEEP);
          } /* End of if (ComM_GaaSubPNCMode[LucIndex] == PNC_NO_COMMUNICATION) */

          else
          {
            /* Enter Data Protection */
            SchM_Enter_ComM_PNC_WAKEUP_IND();

            /* Update Status of Global Variable wake up indication*/
            ComM_GaaPNCWakeupIndication[LucIndex] = COMM_TRUE;

            /* Exit Data Protection */
            SchM_Exit_ComM_PNC_WAKEUP_IND();
          }
          LucPncIndex++;
        }
      }
    }
    #else /* if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */

    /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET  */
    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    LddChannelIndex = ComM_GaaChannelMapArray[Channel];
    #else

    /* Channel Id is updated into local variable */
    LddChannelIndex = Channel;
    #endif
    /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
    /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
    if (ComM_GaaChannels[LddChannelIndex].blChannelPnc == COMM_TRUE)
    {
      /* Number of Pncs linked to the Channel */
      LucNoOfPncs = ComM_GaaChannels[LddChannelIndex].ucPncCount;

      /* Index in the Pnc Index array in the User */
      LucPncIndex = ComM_GaaChannels[LddChannelIndex].ucPncIndex;

      /*-----Handling all the PNCs associated  with the channel------*/
      while (LucNoOfPncs != COMM_ZERO)
      {
        LucIndex = ComM_GaaChannelToPncMapping[LucPncIndex];

        /* Start the PNC Timer for the channel*/
        /* #13567 */
        SchM_Enter_ComM_PNC_PREPARE_TIMER();
        ComM_GaaPncTimeCnt[LucIndex] =
        ComM_GaaChannels[LddChannelIndex].usPncPrepareSleepTimer;
        SchM_Exit_ComM_PNC_PREPARE_TIMER();
        /* Decrement the PNC Count*/
        LucNoOfPncs--;

        if (ComM_GaaSubPNCMode[LucIndex] == PNC_NO_COMMUNICATION)
        {
          /* Enter Data Protection */
          SchM_Enter_ComM_PNC_WAKEUP_IND();

          /* Update Status of Global Variable wake up indication*/
          ComM_GaaPNCWakeupIndication[LucIndex] = COMM_FALSE;

          /* Exit Data Protection */
          SchM_Exit_ComM_PNC_WAKEUP_IND();

          /* #13308 - [SWS_ComM-00990] */
          #if 0
          /* PNC Sub State changed to : PNC_PREPARE_SLEEP */
          ComM_GaaSubPNCMode[LucIndex] = PNC_PREPARE_SLEEP;

          /*Indication to BswM Module*/
          BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucIndex].ddPncId,
            PNC_PREPARE_SLEEP);
          #endif
        } /* End of if (ComM_GaaSubPNCMode[LucIndex] == PNC_NO_COMMUNICATION) */

        else
        {
          /* Enter Data Protection */
          SchM_Enter_ComM_PNC_WAKEUP_IND();

          /* Update Status of Global Variable wake up indication*/
          ComM_GaaPNCWakeupIndication[LucIndex] = COMM_TRUE;

          /* Exit Data Protection */
          SchM_Exit_ComM_PNC_WAKEUP_IND();
        }
        LucPncIndex++;
      }
    } /* End of if (ComM_GaaChannels[LddChannelIndex].blChannelPnc == COMM_TRUE)
       **/
    #endif /* End of if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) */
    #endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
      *(COMM_FRNETWORK_PRESENT == STD_ON)) */
    #endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
      *STD_ON)) */

    /* Enter Data Protection */
    SchM_Enter_ComM_ECUM_WAKEUP_IND();

    /* Update Status of Global Variable wake up indication in bit 0*/
    /* polyspace<RTE: OBAI : Not a defect:Justified > 
                                        Its boundary is pre-defined           */
    /* #13567 */ 
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    for(LucChannelLoopIndex = COMM_ZERO; LucChannelLoopIndex < COMM_TOTAL_CHANNELS; LucChannelLoopIndex++)
    {
      ComM_GaaWakeupIndication[LucChannelLoopIndex] = COMM_TRUE;
    }
    COMM_UNUSED(Channel);
    #else    
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    LddChannelIndex = ComM_GaaChannelMapArray[Channel];
    #else

    /* Channel Id is updated into local variable */
    LddChannelIndex = Channel;
    #endif    
    ComM_GaaWakeupIndication[LddChannelIndex] = COMM_TRUE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_ECUM_WAKEUP_IND();
    /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Array index is valid and validated by DET */
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
    /* polyspace:end<RTE: OBAI : Not a defect:Justified > Array index is valid and validated by DET  */
  } /* End of if (LddReturnValue == E_OK) */
} /* End of ComM_EcuM_WakeUpIndication */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : ComM_EcuM_PNCWakeUpIndication                       **
**                                                                            **
** Service ID           : 0x37                                                **
**                                                                            **
** Description          : Notification of a WakeUp on the corresponding       **
**                        partial network cluster                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : PNCid                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_GaaWakeupIndication[],ComM_GaaChannels[],      **
**                        ComM_GaaChannelMapArray[],ComM_GaaPncTimeCnt[],     **
**                        ComM_GaaPNCWakeupIndication[],ComM_GaaSubPNCMode[], **
**                        ComM_GaaChannelToPncMapping[]                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_ECUM_WAKEUP_IND(),                  **
**                        SchM_Exit_ComM_ECUM_WAKEUP_IND(),                   **
**                        SchM_Enter_ComM_PNC_PREPARE_TIMER(),                **
**                        SchM_Exit_ComM_PNC_PREPARE_TIMER(),                 **
**                        SchM_Enter_ComM_PNC_WAKEUP_IND(),                   **
**                        SchM_Exit_ComM_PNC_WAKEUP_IND(),                    **
**                        BswM_ComM_CurrentPNCMode()                          **
*******************************************************************************/
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE) ComM_EcuM_PNCWakeUpIndication(PNCHandleType PNCid)
{
#if 0
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Standard return type variable */
  Std_ReturnType LddReturnValue;
  #endif

  /* Variable to store channel */
  NetworkHandleType LddChannelIndex;

  #if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON))
  /* Variable for Number of Pncs linked to the Channel */
  uint8 LucNoOfPncs;
  /* Variable for Pnc Index */
  uint8 LucPncIndex;
  /* Variable for channel to pnc mapping */
  uint8 LucIndex;
  uint8 LucChannelLoopIndex;
  #endif

#if 0
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the channel is valid or not */
  LddReturnValue = ComM_ChannelDETCheck(Channel,
    COMM_ECUM_WAKEUPINDICATION_SID);

  /* Check, if no development error occurred */
  if (LddReturnValue == E_OK)
  #endif /* End of if (COMM_DEV_ERROR_DETECT == STD_ON) */
#endif
  {
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    LddChannelIndex = ComM_GaaChannelMapArray[Channel];
    #else

    /* Channel Id is updated into local variable */
    LddChannelIndex = Channel;
    #endif

    #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||(COMM_FRNETWORK_PRESENT == STD_ON))
    /* #13567 */ 
    for(LucChannelLoopIndex = COMM_ZERO; LucChannelLoopIndex < COMM_TOTAL_CHANNELS; LucChannelLoopIndex++)
    {
      LddChannelIndex = LucChannelLoopIndex;
      if (ComM_GaaChannels[LddChannelIndex].blChannelPnc == COMM_TRUE)
      {
        /* Number of Pncs linked to the Channel */
        LucNoOfPncs = ComM_GaaChannels[LddChannelIndex].ucPncCount;

        /* Index in the Pnc Index array in the User */
        //LucPncIndex = ComM_GaaChannels[LddChannelIndex].ucPncIndex;
        LucPncIndex = PNCid;

        /*-----Handling all the PNCs associated  with the channel------*/
        while (LucNoOfPncs != COMM_ZERO)
        {
          LucIndex = ComM_GaaChannelToPncMapping[LucPncIndex];

          /* Start the PNC Timer for the channel*/
          SchM_Enter_ComM_PNC_PREPARE_TIMER();
          ComM_GaaPncTimeCnt[LucIndex] =
          ComM_GaaChannels[LddChannelIndex].usPncPrepareSleepTimer;
          SchM_Exit_ComM_PNC_PREPARE_TIMER();
          /* Decrement the PNC Count*/
          LucNoOfPncs--;

          if (ComM_GaaSubPNCMode[LucIndex] == PNC_NO_COMMUNICATION)
          {
            /* Enter Data Protection */
            SchM_Enter_ComM_PNC_WAKEUP_IND();

            /* Update Status of Global Variable wake up indication*/
            ComM_GaaPNCWakeupIndication[LucIndex] = COMM_FALSE;

            /* Exit Data Protection */
            SchM_Exit_ComM_PNC_WAKEUP_IND();

            /* PNC Sub State changed to : PNC_PREPARE_SLEEP */
            ComM_GaaSubPNCMode[LucIndex] = PNC_PREPARE_SLEEP;

            /*Indication to BswM Module*/
            BswM_ComM_CurrentPNCMode(ComM_GaaPncs[LucIndex].ddPncId,
              PNC_PREPARE_SLEEP);
          } /* End of if (ComM_GaaSubPNCMode[LucIndex] == PNC_NO_COMMUNICATION) */

          else
          {
            /* Enter Data Protection */
            SchM_Enter_ComM_PNC_WAKEUP_IND();

            /* Update Status of Global Variable wake up indication*/
            ComM_GaaPNCWakeupIndication[LucIndex] = COMM_TRUE;

            /* Exit Data Protection */
            SchM_Exit_ComM_PNC_WAKEUP_IND();
          }
          LucPncIndex++;
        }
      }
    }
    #endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
      *(COMM_FRNETWORK_PRESENT == STD_ON)) */

    /* Enter Data Protection */
    SchM_Enter_ComM_ECUM_WAKEUP_IND();

    /* Update Status of Global Variable wake up indication in bit 0*/
    /* polyspace<RTE: OBAI : Not a defect:Justified > 
                                        Its boundary is pre-defined           */
    /* #13567 */ 
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)       
    for(LucChannelLoopIndex = COMM_ZERO; LucChannelLoopIndex < COMM_TOTAL_CHANNELS; LucChannelLoopIndex++)
    {
      ComM_GaaWakeupIndication[LucChannelLoopIndex] = COMM_TRUE;
    }
    #else    
    ComM_GaaWakeupIndication[LddChannelIndex] = COMM_TRUE;
    #endif

    /* Exit Data Protection */
    SchM_Exit_ComM_ECUM_WAKEUP_IND();
  } /* End of if (LddReturnValue == E_OK) */
#endif
} /* End of ComM_EcuM_PNCWakeUpIndication */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

