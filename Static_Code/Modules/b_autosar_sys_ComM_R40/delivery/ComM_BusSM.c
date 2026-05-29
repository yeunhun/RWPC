/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComM_BusSM.c                                                  **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of ComM SM Indication                               **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date             By                   Description                **
********************************************************************************
** 1.9.6     11-Jan-2021   Jongsun Lim #27580                                 **
** 1.9.5     08-Dec-2020   Jongsun Lim #25703                                 **
** 1.9.3     11-Aug-2020   JS Lim      #25552, #25554                         **
** 1.9.0     22-Aug-2019   JS Lim      #18922, #19094                         **
** 1.8.0     23-Oct-2018   JS Lim      #13653                                 **
** 1.7.14    19-Jun-2017   JH Jeong    #8337                                  **
** 1.1.0     07-Sep-2015   KT Kim      Justification for Runtime Error        ** 
** 1.0.9     24-Aug-2015   KT Kim      Justification for MISRA rule 16.7      ** 
** 1.0.8     21-JUL-2015   KT Kim      Disabled RTE port access               ** 
** 1.0.7     13-May-2014   KT Kim      Bug #921 Add CanCM support feature     **
** 1.0.6     04-Jul-2013   Daejun Park CR~129, XAR~581 : ComM library         **
**                                     -Include ComM_Config.h for library     **
** 1.0.4     07-Jun-2013   Daejun Park CR~118, XAR~557 : ComM library         **
**                                     -Convert local variable LblUserRteInd  **
**                                      to global variable ComM_GaaUserRteInd **
** 1.0.0     28-May-2013   Daejun Park Initial version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM.h"                 /* ComM header file */
#include "ComM_Ram.h"             /* ComM global Ram variables header file */
#include "ComM_BusSM.h"           /* ComM and SM callback header file */
#include "SchM_ComM.h"            /* SchM ComM interface API header file */
#include "ComM_Internal.h"        /* ComM Internal functions header file */
#include "ComM_Config.h"          /* ComM Config header file */
#include "Rte_ComM.h"             /* RTE generated header file */
#if (COMM_CANCM_SUPPORT == STD_ON)
#include "CanCM_Cbk.h"                   /* CanCM header file */
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COMM_BUSSM_C_AR_RELEASE_MAJOR_VERSION    4
#define COMM_BUSSM_C_AR_RELEASE_MINOR_VERSION    0
#define COMM_BUSSM_C_AR_RELEASE_REVISION_VERSION 3

/* Software Version Information */
#define COMM_BUSSM_C_SW_MAJOR_VERSION            1
#define COMM_BUSSM_C_SW_MINOR_VERSION            10

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (COMM_BUSSM_AR_RELEASE_MAJOR_VERSION !=\
     COMM_BUSSM_C_AR_RELEASE_MAJOR_VERSION)
#error "ComM_BusSM.c : Mismatch in Specification Major Version"
#endif
#if (COMM_BUSSM_AR_RELEASE_MINOR_VERSION !=\
     COMM_BUSSM_C_AR_RELEASE_MINOR_VERSION)
#error "ComM_BusSM.c : Mismatch in Specification Minor Version"
#endif
#if (COMM_BUSSM_AR_RELEASE_REVISION_VERSION !=\
     COMM_BUSSM_C_AR_RELEASE_REVISION_VERSION)
#error "ComM_BusSM.c : Mismatch in Specification Revision Version"
#endif
#if (COMM_BUSSM_SW_MAJOR_VERSION != COMM_BUSSM_C_SW_MAJOR_VERSION)
#error "ComM_BusSM.c : Mismatch in Software Major Version"
#endif
#if (COMM_BUSSM_SW_MINOR_VERSION != COMM_BUSSM_C_SW_MINOR_VERSION)
#error "ComM_BusSM.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_BusSM_ModeIndication                           **
**                                                                            **
** Service ID           : 0x33                                                **
**                                                                            **
** Description          : Indication of actual bus mode by the corresponding  **
**                        Bus State Manager                                   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel, ComMode                                    **
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
**                        ComM_GaaChannelMapArray[], ComM_GaaChnInxArr[],     **
**                        ComM_GaaCurComMode[], ComM_GaaUsers[],              **
**                        ComM_GaaModeRequested[], ComM_GaaChannels           **
**                        ComM_GaaChannelToPncMapping, ComM_GaaPncs,          **
**                        ComM_GaaPncToUserMapping, ComM_GaaUserMapArray      **
**                        ComM_GaaChannelToUserMapping, ComM_GaaUserRteInd[]  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Rte_Ports_ComM_CurrentMode_P(), Det_ReportError()   **
**                        ComM_ChannelDETCheck(), ComM_SwitchToNoCom()        **
**                        ComM_SwitchToFullCom(),                             **
**                        SchM_Enter_ComM_CURRENT_MODE_PROTECTION(),          **
**                        SchM_Exit_ComM_CURRENT_MODE_PROTECTION()            **
**                        ComM_FullComMToSilentComM(),ComM_PncUserLowestMode()**
*******************************************************************************/
#define COMM_START_SEC_CODE
#include "MemMap.h"
/* polyspace:begin<MISRA-C3:8.13:Not a defect:Justified> No impact on behavior and used pointer 
without const qualifier as per specification  */
FUNC(void, COMM_CODE) ComM_BusSM_ModeIndication(NetworkHandleType Channel,
  P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode)
/* polyspace:end<MISRA-C3:8.13:Not a defect:Justified> No impact on behavior and used pointer 
without const qualifier as per specification  */
{
  #if(COMM_DIRECT_USER_MAPPING == STD_OFF)
  /* Variable to store the User Id from the mapping array */
  ComM_UserHandleType LddUserId;
  #endif

  #if(COMM_DEV_ERROR_DETECT == STD_ON)

  /* Variable to store return value E_OK or E_NOT_OK or COMM_E_UNINIT */
  Std_ReturnType LddStdRetVal;
  #endif /* #if(COMM_DEV_ERROR_DETECT == STD_ON) */

  /* Channel Index */
  uint8 LucChannelIndex;

  #if(COMM_DIRECT_USER_MAPPING == STD_OFF)
  /* Variable to store the User index from the mapping array */
  uint8 LucUserIndx;
  #if((COMM_PNC_SUPPORT == STD_OFF) && (COMM_PNC_ENABLED == STD_OFF))

  /* Variable to access Rte function */
  #if(COMM_RTE_NOTIF == STD_ON)
  Rte_PortHandle_ComM_CurrentMode_P LddComMRteMode; 
  
  /* Lowest mode requested by user (No-Slient-Full)*/
  ComM_ModeType LddLowestMode;
  #endif

  /* Variable to store the channel index from the mapping array */
  NetworkHandleType LddChnInd;

  /* Variable to store the Total No. of Channels of the User */
  uint8 LucNoOfChannels;

  /* Index to the channel Id's in the ChannelIndex Array */
  uint8 LucUserChannelIndex;
  #endif

  #if(COMM_DIRECT_CHANNEL == STD_ON)

  /* Variable to store the Total No. of Users of the Channel */
  uint8 LucNoOfUsers;

  /* Index to the User Id's in the ChannelToUserMapping Array */
  uint8 LucUserIndex;
  #endif

  #if((COMM_PNC_SUPPORT == STD_ON)&& (COMM_PNC_ENABLED == STD_ON))
  #if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
      (COMM_ETHNETWORK_PRESENT == STD_ON))
  /* Variable to get the No of PNCs of the Channel */
  uint8 LucNoOfPncs;

  /* variable to get the PNC Index of the channel */
  uint8 LucPncIndex;

  /* variable to get PNC Index from channel to pnc mapping */
  uint8 LucPncInx;

  /* variable to store user associated with pnc */
  uint8 LucPncUserCount;

  /* variable to store user index of users associated with the pnc */
  uint8 LucPncUserIndex;

  /* variable to store user count */
  uint8 LucUserCount;

  LucUserCount = ComM_GucTotalUsers;
  while (LucUserCount != COMM_ZERO)
  {
    LucUserCount--;
    ComM_GaaUserRteInd[LucUserCount] = COMM_FALSE;
  }
  #endif
  #endif

  #if ((COMM_PNC_SUPPORT == STD_OFF) && (COMM_PNC_ENABLED == STD_OFF))

  /* Initialization to pointer to function */
  #if(COMM_RTE_NOTIF == STD_ON)
  LddComMRteMode =
    (Rte_PortHandle_ComM_CurrentMode_P)Rte_Ports_ComM_CurrentMode_P();
  
  /* Initialize to Full communication */
  LddLowestMode = COMM_FULL_COMMUNICATION;
  #endif
  #endif
  #endif

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check if channel is valid or not */
  LddStdRetVal = ComM_ChannelDETCheck(Channel, COMM_BUSSM_MODEINDICATION_SID);

  /* Check, if passed Communication mode is equal to Null */
  if (ComMode == NULL_PTR)
  {
    (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID,
      COMM_BUSSM_MODEINDICATION_SID, COMM_E_WRONG_PARAMETERS);
    LddStdRetVal = E_NOT_OK;
  }

  /* Check, if no development error occurred */
  if (LddStdRetVal == E_OK)
  #endif /* #if(COMM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* polyspace:begin<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET */ 
    /* Get Channel Index */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)

    /* Get the channel id from the mapping array */
    LucChannelIndex = ComM_GaaChannelMapArray[Channel];
    #else

    /* Channel Id is updated into local variable */
    LucChannelIndex = Channel;
    #endif /* #if(COMM_CHANNEL_SEQUENTIAL == STD_OFF) */

    /* Check if the current mode and the indicated mode is not same */
    /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Its boundary is pre-defined  */
    /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> Pointer is not outside its bounds - Pointer is generated by Generator*/
    if (ComM_GaaCurComMode[LucChannelIndex] != *ComMode)
    {

      /* Enter Data Protection */
      SchM_Enter_ComM_CURRENT_MODE_PROTECTION();

      /* Set the Current Communication Mode to indicated mode */
      ComM_GaaCurComMode[LucChannelIndex] = *ComMode;

      /* After SM indicates the mode change for the channel which had requested
       *   the change in mode, clear the flag */
      ComM_GaaModeRequested[LucChannelIndex] = COMM_FALSE;

      /* Exit Data Protection */
      SchM_Exit_ComM_CURRENT_MODE_PROTECTION();

      /* If indicated mode is No communication */
      if (*ComMode == COMM_NO_COMMUNICATION)
      {        
        /* Invoke switching to No communication */
        ComM_SwitchToNoCom(LucChannelIndex);
      }
      #if ((COMM_CANNETWORK_PRESENT == STD_ON) ||\
           (COMM_ETHNETWORK_PRESENT == STD_ON))

      /* If indicated mode is Silent communication */
      else if (*ComMode == COMM_SILENT_COMMUNICATION)
      {
        ComM_FullComMToSilentComM(LucChannelIndex);
      }
      #endif
      else
      {
        /* Invoke switching to Full communication */
        ComM_SwitchToFullCom(LucChannelIndex);
      }
      #if (COMM_CANCM_SUPPORT == STD_ON)
      /* Only if bus type is CAN */
      /* polyspace<DEFECT:USELESS_IF::Not a defect Justify with annotations> condition will be executed based on the configured values */
	  /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
      if(COMM_ZERO == ComM_GaaChannels[LucChannelIndex].ucBusType)
      {
        /* Report Communication Mode change to CanCM */
        (void)CanCM_ComModeIndication(ComM_GaaChannels[LucChannelIndex].ddChannelId,
          *ComMode);
      }
      #endif

    } /* End of if (ComM_GaaCurComMode[LucChannelIndex] != *ComMode) */

    #if (COMM_DIRECT_USER_MAPPING == STD_OFF)
    #if (((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON)) &&\
         ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
          (COMM_ETHNETWORK_PRESENT == STD_ON)))

    /* If the Channel is associated  with a PNC: PNC Channel */
    /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
    /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
    if (ComM_GaaChannels[LucChannelIndex].blChannelPnc == COMM_TRUE)
    {
      /* Get the No of PNCs of the Channel */
      LucNoOfPncs = ComM_GaaChannels[LucChannelIndex].ucPncCount;

      /* PNC Index of the channel */
      LucPncIndex = ComM_GaaChannels[LucChannelIndex].ucPncIndex;
      while (LucNoOfPncs != COMM_ZERO)
      {
        /* PNC Index from channel to pnc mapping */
        LucPncInx = ComM_GaaChannelToPncMapping[LucPncIndex];

        /* Decrement the count*/
        LucNoOfPncs--;

        /* user associated with the pnc */
        LucPncUserCount = ComM_GaaPncs[LucPncInx].ucUserCount;

        /* user index of users associated with the pnc */
        LucPncUserIndex = ComM_GaaPncs[LucPncInx].ucUserIndex;
        while (LucPncUserCount != COMM_ZERO)
        {
          LucPncUserCount--;

          /* Get the User Index: Map array provides ID of the User */
          LddUserId = ComM_GaaPncToUserMapping[LucPncUserIndex];

          #if (COMM_USER_SEQUENTIAL == STD_OFF)
          LucUserIndx = ComM_GaaUserMapArray[LddUserId];
          #else
          LucUserIndx = LddUserId;
          #endif

          /* ComM_GaaUserRteInd[]: variable to avoid same user indication more
           * than once to RTE, Eg: Two PNC may refer to same user */
          /* polyspace<DEFECT:USELESS_IF::Not a defect Justified> condition will be executed based on the configured values */
          /* polyspace<MISRA-C3:14.3:Not a defect:Justified> condition will be executed based on the configured values */
          if (ComM_GaaUserRteInd[LucUserIndx] != COMM_TRUE)
          {
            /* Indicate lowest mode of user :PNC channels and Direct channels */
            ComM_PncUserLowestMode(LucUserIndx);

            /* User : Executed in one of the PNC */
            ComM_GaaUserRteInd[LucUserIndx] = COMM_TRUE;
          }
          /* Increment the user index of the pnc  */
          LucPncUserIndex++;
        }
        /* Increment the pnc index */
        LucPncIndex++;
      }
    } /* End of if (ComM_GaaChannels[LucChannelIndex].blChannelPnc == COMM_TRUE)
       **/
    #if (COMM_DIRECT_CHANNEL == STD_ON)
    /* Note: PNC is Enabled but, Channel is not part of PNC: Direct Channel */
    else
    {
      /* Get the No of Users of the Channel */
      LucNoOfUsers = ComM_GaaChannels[LucChannelIndex].ucChannelUserCount;

      /* User Index */
      LucUserIndex = ComM_GaaChannels[LucChannelIndex].ucChannelUserIndex;
      /* Check the Current Communication Mode of the Each channel */
      while (LucNoOfUsers != COMM_ZERO)
      {
        /* Decrement the Number of channels */
        LucNoOfUsers--;

        /* Get the User Id from the channel to user mapping  */
        LddUserId = ComM_GaaChannelToUserMapping[LucUserIndex];

        #if (COMM_USER_SEQUENTIAL == STD_OFF)
        LucUserIndx = ComM_GaaUserMapArray[LddUserId];
        #else /* if COMM_USER_SEQUENTIAL == OFF */
        /* Load the user in user index */
        LucUserIndx = LddUserId;
        #endif

        /* Indicate lowest mode of user : PNC channels and Direct channels */
        ComM_PncUserLowestMode(LucUserIndx);
        LucUserIndex++;
      }
    } /* End of else */
    #endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */
    #endif

    /* Note: PNC is not Enabled : Get the No of Users of the Channel */
    #if ((COMM_PNC_SUPPORT == STD_OFF) && (COMM_PNC_ENABLED == STD_OFF))

    /* User Count */
    LucNoOfUsers = ComM_GaaChannels[LucChannelIndex].ucChannelUserCount;
    /* User Index */
    LucUserIndex = ComM_GaaChannels[LucChannelIndex].ucChannelUserIndex;

    /* Check the Current Communication Mode of the Each channel */
    while (LucNoOfUsers != COMM_ZERO)
    {
      /* Get the Channel from Index Array */      
      LddUserId = ComM_GaaChannelToUserMapping[LucUserIndex];

      /* Decrement the Number of channels */
      LucNoOfUsers--;

      #if (COMM_USER_SEQUENTIAL == STD_OFF)
      LucUserIndx = ComM_GaaUserMapArray[LddUserId];
      #else /* if COMM_USER_SEQUENTIAL == OFF */
      /* Load the user in user index */
      LucUserIndx = LddUserId;
      #endif

      /* Get the No of channels of the User */      
      LucNoOfChannels = ComM_GaaUsers[LucUserIndx].ucNoOfDirectChannels;

      /* Channel Index */
      LucUserChannelIndex = ComM_GaaUsers[LucUserIndx].ucDirectChannelIndex;

      /* polyspace<DEFECT:DEAD_CODE::Not a defect Justified> condition will be executed based on the configured values */
      /* polyspace<MISRA-C3:2.1, 14.3:Not a defect:Justified> condition will be executed based on the configured values */
      /* If there are more than one user for the channel */
      if (LucNoOfChannels > COMM_ONE)
      {
        /* Check the Current Communication Mode of the Each channel */
        while (LucNoOfChannels != COMM_ZERO)
        {
          /* Get the Channel from Index Array */          
          LddChnInd = ComM_GaaChnInxArr[LucUserChannelIndex];

          /* Decrement the Number of channels */
          LucNoOfChannels--;

          /* Check the current Communication Mode */          
          if (ComM_GaaCurComMode[LddChnInd] == COMM_NO_COMMUNICATION)
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
            #if(COMM_RTE_NOTIF == STD_ON)
            /* Check for Silent communication */
            if (ComM_GaaCurComMode[LddChnInd] == COMM_SILENT_COMMUNICATION)
            {
              /* Get the lowest mode */
              LddLowestMode = COMM_SILENT_COMMUNICATION;
            }
            #endif
            /* Check next channel associated with the same user */
            LucUserChannelIndex++;
          } /* End of else */
        } /* End While */
      } /* End of if (LucNoOfChannels > COMM_ONE) */
      else
      {
        /* If the channel has single user, directly get the current mode of the
         *   channel */
        #if(COMM_RTE_NOTIF == STD_ON)
        LddLowestMode = ComM_GaaCurComMode[LucChannelIndex];
        #endif
      }
      /* Indicate NO_COMM/SILENT_COMM/FULL_COMM mode to RTE */
      #if(COMM_RTE_NOTIF == STD_ON)
      if(LddComMRteMode[LucUserIndx].Switch_currentMode != NULL_PTR)
      {
        LddComMRteMode[LucUserIndx].Switch_currentMode(LddLowestMode);
      }
      #endif
      LucUserIndex++;
    }
    #endif /* End of ((COMM_PNC_SUPPORT == STD_OFF) &&
            * (COMM_PNC_ENABLED == STD_OFF)) */
    #endif  /**/
    /* polyspace:end<MISRA-C3:D4.14:Not a defect:Justified> Array index is valid and validated by DET  */
    /* polyspace:end<RTE: OBAI : Not a defect:Justified > Its boundary is pre-defined  */
    /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> Pointer is not outside its bounds - Pointer is generated by Generator*/
  }
} /* End of ComM_BusSM_ModeIndication */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

