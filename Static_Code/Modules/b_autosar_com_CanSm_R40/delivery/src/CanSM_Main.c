/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.								                      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_Main.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of the funtionality of CanSM_MainFunction()         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.12.5    27-Dec-2021   SM Kwon        #33358, #33200                      **
** 1.12.3    25-Nov-2020   SM Kwon        #25247                              **
** 1.12.1    26-Aug-2019   SM Kwon        #18962                              **
** 1.12.0    31-Apr-2019   SM Kwon        #17202                              **
** 1.11.0    23-Oct-2018   Lim Jong Sun   #14496, #14519                      **
** 1.10.5    10-Dec-2018   Lim Jong Sun   #15077                              **
** 1.10.4    14-Nov-2018   Lim Jong Sun   #14720                              **
** 1.10.3    06-Feb-2018   Lim Jong Sun   #11551, #11584                      **
** 1.10.2    23-Nov-2017   Lim Jong Sun   #10689                              **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7076                               **
** 1.9.13    27-Oct-2016   Lim Jong Sun   #6325                               **
** 1.9.12    10-Oct-2016   Lim Jong Sun   #6235                               **
** 1.9.10    24-Jun-2016   Lim Jong Sun   #5314, #5318                        **
** 1.9.9     19-May-2016   Lim Jong Sun   #4872                               **
** 1.9.8     25-Apr-2016   Lim Jong Sun   #4734                               **
** 1.9.7     17-Feb-2016   Lim Jong Sun   #3905, #4159, #4142, #3975          **
** 1.9.6     13-Jan-2015   Lim Jong Sun   #3415, #3677                        **
** 1.9.5     20-Oct-2015   Lim Jong Sun   #3210 ,#3210                        **
** 1.9.4     07-Sep-2015   Lim Jong Sun   #2525, #3098                        **
** 1.0.5     09-Jan-2015   Lim Jong Sun   #1962                               **
** 1.0.4     10-Dec-2014   Lim Jong Sun   #1793                               **
** 1.0.3     25-Nov-2014   Lim Jong Sun   #1721                               **
** 1.0.2     26-May-2014   Lim Jong Sun   #703                                **
** 1.0.1     31-Dec-2013   Lim Jong Sun   #393                                **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "BswM.h"                 /* BswM header file */
#include "CanSM_Ram.h"            /* CanSM_Ram header file */
#include "CanIf.h"                /* CanIf header file */
#include "CanSM_InternalTypes.h"        /* CanSM PCTypes header file */
#include "CanSM_Internal.h"       /* CanSM Main header file */
#include "ComM.h"                 /* ComM header file */
#include "ComM_BusSM.h"           /* ComM_BusSM header file */
#include "BswM_CanSM.h"           /* BswM_CanSM header file */

#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h"                  /* Det header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_MAIN_C_RELEASE_MAJOR_VERSION       4
#define CANSM_MAIN_C_RELEASE_MINOR_VERSION       0
#define CANSM_MAIN_C_RELEASE_REVISION_VERSION    3

/* CANSM software version information */
#define CANSM_MAIN_C_SW_MAJOR_VERSION            1
#define CANSM_MAIN_C_SW_MINOR_VERSION            12

/*******************************************************************************
**                      Define Section                                       **
*******************************************************************************/
#define AUTOEVER_CANSM_DEFINE 1

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_MAIN_C_RELEASE_MAJOR_VERSION )
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_MAIN_C_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_MAIN_C_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_MAIN_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_MAIN_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/* extern for CanSM_GetTxConfirmationState */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
#if (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)
static FUNC(CanIf_NotifStatusType, CANSM_CODE) CanSM_GetTxConfirmationState(
  NetworkHandleType LddNetworkHandle);

#endif
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_ClearTrcvWuf */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
static FUNC(Std_ReturnType, CANSM_CODE) CanSM_ClearTrcvWuf(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_CheckTrcvWuf */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
static FUNC(Std_ReturnType, CANSM_CODE) CanSM_CheckTrcvWuf(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_SetCanControllerMode */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
static FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetCanControllerMode(
  NetworkHandleType LddNetworkHandle, CanIf_ControllerModeType LenMode);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_SetCanTrcvMode */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
static FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetCanTrcvMode(NetworkHandleType
  LddNetworkHandle, CanTrcv_TrcvModeType LenMode);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
/*******************************************************************************
** Function Name        : CanSM_MainFunction                                  **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : This service executes the bus-off recovery          **
**                        state machines of each network handle, which        **
**                        is configured for the CanSM.                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
** Remarks              : Global Variable(s)  : CanSM_GaaNetwork              **
**                                              CanSM_GblInitStatus           **
**                        Function(s) invoked : CanSM_NoCommunication         **
**                                              CanSM_FullCommunication       **
**                                              CanSM_SilentCommunication     **
**                                              CanSM_BORWait                 **
**                                              CanSM_CheckBusOff             **
**                                              CanSM_NoToFullCommRequested   **
**                                              CanSM_SilentToFullCommRequested*
**                                              CanSM_NoToSilentCommRequested **
**                                              CanSM_SilentCommRequested     **
**                                              CanSM_DeInitPnNotSupported    **
**                                              CanSM_DeInitPnSupported       **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_MainFunction(void)
{
  NetworkHandleType LddCanSmNwIndex;
  #if (STD_ON == CANSM_PN_AVAILABILITY)
  CanSM_TransFuncPtr CanSM_TransFuncPtrType[CANSM_THIRTEEN] =
  #else
  CanSM_TransFuncPtr CanSM_TransFuncPtrType[CANSM_ELEVEN] =
  #endif
  {
    {&CanSM_NoCommunication},       {&CanSM_SilentCommunication},       {&CanSM_FullCommunication},
    {&CanSM_BORStart},              {&CanSM_BORWait},                   {&CanSM_CheckBusOff},  
    {&CanSM_NoToFullCommRequested}, {&CanSM_SilentToFullCommRequested}, {&CanSM_SilentCommRequested},
    #if (STD_ON == CANSM_CHANGE_BAUDRATE_API) 
    {&CanSM_ChangeBaudRateService},
    #else
    {NULL_PTR},
    #endif
    {&CanSM_DeInitPnNotSupported},
    #if (STD_ON == CANSM_PN_AVAILABILITY)
    {&CanSM_DeInitPnSupported}, {&CanSM_TxTimeoutExceptionService}
    #endif
  };
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  Std_ReturnType LddResult;
  LddResult = (uint8)E_OK;
  /* Report the error to DET with CANSM_E_UNINIT */
  CANSM_INITED_DET_CHECK(LddResult, CANSMSERVICEID_MAINFUNCTION);
  if ((uint8)E_OK == LddResult)
  #endif
  {
    LddCanSmNwIndex = (NetworkHandleType)CANSM_NUMBER_OF_NETWORKS;

    /* Loop for all the networks */
    do
    {
      /* Decrement the network index */
      --LddCanSmNwIndex;
      /* polyspace:begin<MISRA-C3:18.1:Not a defect:Justify with annotations> ucModeStatus always has defined value (not exceeds boundary) */
      /* polyspace:begin<RTE: OBAI : Not a defect:Justified > Its boundary is pre-defined */
      /* polyspace:begin<RTE: COR : Not a defect:Justified > Its boundary is pre-defined */
      /* Process the current CanSM request */
      (CanSM_TransFuncPtrType[CanSM_GaaNetwork[LddCanSmNwIndex].ucModeStatus].
       pTransFuncPtr)(LddCanSmNwIndex);
      /* polyspace:begin<RTE: COR : Not a defect:Justified > Its boundary is pre-defined */
      /* polyspace:end<RTE: OBAI : Not a defect:Justified > Its boundary is pre-defined */
      /* polyspace:end<MISRA-C3:18.1:Not a defect:Justify with annotations> ucModeStatus always has defined value (not exceeds boundary) */
      
    } while ((NetworkHandleType)CANSM_ZERO != LddCanSmNwIndex);
    /* Process the current CanSM request */
  } /* End of if ((Std_ReturnType)E_OK == LddResult) */
} /* End of CanSM_MainFunction(void) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_BORStart                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function starts the bus of recovery procedure  **
**                        on bus off Occurence.                               **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GpStaticNw              **
**                                              CanSM_GaaNetwork              **
**                        Function(s) invoked : CanIf_SetPduMode()            **
**                                              CanIf_SetControllerMode()     **
**                                              Dem_ReportErrorStatus()       **
**                                              SchM_Enter_CanSM()            **
**                                              SchM_Exit_CanSM()             **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, CANSM_CODE) CanSM_BORStart(NetworkHandleType LddNetworkHandle)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  ComM_ModeType LddCurrentState;
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  uint8 LucNoOfController;
  uint8 LucControllerIndex;
  #endif
  Std_ReturnType LddResult;
  LddResult = CANSM_E_WAITSTATE;

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);
  #endif

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];
  /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
  if ((uint8)COMM_NO_COMMUNICATION == LpNetwork->ucReqModeStatus)
  {

    /* Update Internal Substate as Zero*/
    LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;

    /* Update Internal ddTimer as Zero*/
    LpNetwork->ddTimer = (CanSM_TimerType)CANSM_ZERO;

    /* Update Internal ddBusOffCounter as Zero*/
    LpNetwork->ddBusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;

    /* Notify the network mode to the BswM */
    BswM_CanSM_CurrentState(LpStaticNetwork->ucCanSmNetworkHandle,
      CANSM_BSWM_NO_COMMUNICATION);
    
    /* Enter Protection Area */
    SchM_Enter_CanSM_BUSOFF_STATUS_PROTECTION();
    
    /* Update the Mode status as DeInitPnSupported */
    LpNetwork->ucModeStatus = CANSM_DEINITPNNOTSUPPORTED;
    
    /* Exit Protection Area */
    SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();
  }else{  
  
    if (CANSM_FULL_T_BUSOFF == LpNetwork->ucCanSMNWIntSubState)
    {
      /* Notify the network mode to the BswM */
      BswM_CanSM_CurrentState(LpStaticNetwork->ucCanSmNetworkHandle,
        CANSM_BSWM_BUS_OFF);

      /* Notify bus-off node to the BswM */
      BswM_RequestMode((BswM_UserType)CANSM_BSWM_USER_ID(LpStaticNetwork->ucCanSmNetworkHandle),
                            (BswM_ModeType)CANSM_BSWM_BOR_START);
  

      /* Set the current mode of the network */
      LddCurrentState = (ComM_ModeType)COMM_SILENT_COMMUNICATION;

      /* Notify the current network mode to the ComM */
      ComM_BusSM_ModeIndication(LpStaticNetwork->ucCanSmNetworkHandle,
        &LddCurrentState);
      #if (STD_ON == CANSM_DEM_STATUS)
      /* Bug #1793 CANSM_NO_DEM_EVENT, Should not call Dem_ReportErrorStatus Api*/ 
      if(LpStaticNetwork->ddEventId != CANSM_DEM_NO_EVENT){
      
        /* Report the error to DEM with event id and DEM_EVENT_STATUS_PREFAILED */
        Dem_ReportErrorStatus(LpStaticNetwork->ddEventId, 
                               (Dem_EventStatusType)DEM_EVENT_STATUS_PREFAILED);
      }
      #endif

      /* Update the Internal Substate */
      LpNetwork->ucCanSMNWIntSubState = CANSM_FULL_RESTART_CC;
    
    } /* End of if (CANSM_FULL_T_BUSOFF == LpNetwork->ucCanSMNWIntSubState) */

    /* Check if the Internal subsate is CANSM_FULL_RESTART_CC */
    if (CANSM_FULL_RESTART_CC == LpNetwork->ucCanSMNWIntSubState)
    {
      LpNetwork->ucMode = (uint8)CANIF_CS_STARTED;
      /* Set the controller mode as CANIF_CS_STARTED */
      LddResult =
        CanSM_SetCanControllerMode(CANSM_LDDNETWORKHANDLE, CANIF_CS_STARTED);

    }

    /* Check if the Internal subsate is CANSM_FULL_TX_OFF */
    if (CANSM_FULL_TX_OFF == LpNetwork->ucCanSMNWIntSubState)
    {
      /* Update Local variable with E_OK */
      #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
      LddResult = (uint8)E_OK;

      /* Set Pdu Mode as Offline for multiple controllers*/
      /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Generated array index in range" */
      CANIF_SETPDUMODE(LpStaticNetwork->ucControllerIndex, CANIF_SET_TX_OFFLINE)
      #else

      /* Set Pdu Mode as Offline for single controller */
      LddResult = CanIf_SetPduMode
                                (LpStaticNetwork->ucControllerIndex,
                                 CANIF_SET_TX_OFFLINE);
      #endif

      /* Check if Local Variable is equal to E_OK */
      if ((uint8)E_OK == LddResult)
      {
        /* Update the Internal State as Zero */
        LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;

        /* Check the counter value is equal to ZERO */
        if (LpStaticNetwork->ddBorCounterL1ToL2 != CANSM_ZERO)
        {
          /* Check the counter value to load Timer */
          if (LpNetwork->ddBusOffCounter <
              (CanSM_BusOffCntType)(CANSM_BOR_L1TOL2 - CANSM_ONE))
          {
            /* Load CanSMBorTimeLVinay 1 Timer */
            LpNetwork->ddTimer = (CanSM_TimerType)CANSM_BOR_TIMEL1;

            /* Increment Bus Off Counter */
            LpNetwork->ddBusOffCounter++;
          }
          else
          {
            /* Load CanSMBorTimeL2 Timer */
            LpNetwork->ddTimer = (CanSM_TimerType)CANSM_BOR_TIMEL2;
            /* Bug #4872 */
            LpNetwork->ddBusOffCounter = (CanSM_BusOffCntType)CANSM_MAX_BOR_COUNTER;
          }
        }
        else
        {
          /* Load CanSMBorTimeL2 Timer */
          LpNetwork->ddTimer = (CanSM_TimerType)CANSM_BOR_TIMEL2;
          /* Bug #4872 */
          LpNetwork->ddBusOffCounter = (CanSM_BusOffCntType)CANSM_MAX_BOR_COUNTER;
        }
        /* Redmine 6235 */
        /* Enter Protection Area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();
        if(LpNetwork->ucBusOffRep != 1){
          /* Change internal status */
          LpNetwork->ucModeStatus = CANSM_BORWAIT;

          /* Exit Protection Area */
          SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
        }else{    
          /* Change internal status */
          LpNetwork->ucModeStatus = CANSM_BORSTART;
          LpNetwork->ucCanSMNWIntSubState = 0;
          LpNetwork->ucBusOffRep = 0;
          /* Exit Protection Area */
          SchM_Exit_CanSM_MODE_STATUS_PROTECTION();  
        }
      } /* End of if ((uint8)E_OK == LddResult) */
    } /* End of if (CANSM_FULL_TX_OFF == LpNetwork->ucCanSMNWIntSubState) */
    else if ((uint8)E_OK == LddResult)
    {
      /* load the Request Time into local variable */
      LpNetwork->ddCanSMModeReqReptTime =
        (CanSM_TimerType)CanSm_GddModeReqRepeatTime;
    }
    else
    {
      /* Call the TimeOut Processing Function */
      CanSM_TimeoutProcessing(CANSM_LDDNETWORKHANDLE, LddResult);
    }
  }
} /* End of CanSM_BORStart(NetworkHandleType LddNetworkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_BORWait                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function waits the bus of recovery timer to    **
**                        elapse for bus off recovery                         **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GaaNetwork              **
**                                              CanSM_GpStaticNw              **
**                        Function(s) invoked : SchM_Enter_CanSM()            **
**                                              SchM_Exit_CanSM()             **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_BORWait(NetworkHandleType LddNetworkHandle)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  ComM_ModeType LddCurrentState;
  Std_ReturnType LddResult;
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  uint8 LucControllerIndex;
  uint8 LucNoOfController;
  #endif

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);
  #endif

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];
  /* Fixed Bug #1962 */
  /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
  if ((CanSM_TimerType)CANSM_ZERO != LpNetwork->ddTimer)
  {
    /* Decrement the timer */
    (LpNetwork->ddTimer)--;
  }
  /* Exit BOR wait if timer becomes ZERO */
  if ((CanSM_TimerType)CANSM_ZERO == LpNetwork->ddTimer)
  {
    #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)

    LddResult = (uint8)E_OK;

    /* Set the Pdu mode to online */
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Generated array index in range" */
    CANIF_SETPDUMODE(LpStaticNetwork->ucControllerIndex, CANIF_SET_TX_ONLINE)
    #else

    /* Set the Pdu mode to online */
    LddResult = CanIf_SetPduMode(LpStaticNetwork->ucControllerIndex,
                                   CANIF_SET_TX_ONLINE);
    #endif

    /* Enter Protection Area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();
    if(LpNetwork->ucModeStatus != CANSM_BORSTART)
    {
      if ((uint8)E_OK == LddResult)
      {      
        /* Set the mode of the CanSM to CANSM_CHECKBUSOFF state */
        LpNetwork->ucModeStatus = CANSM_CHECKBUSOFF;


        #if (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)

        /* Check whether Polling is supported for the network */
        if ((boolean)CANSM_TRUE == LpStaticNetwork->blCanSMTxConfirmationPolling)
        {
          /* Lsoad the timer with value as One */
          LpNetwork->ddTimer = (CanSM_TimerType)CANSM_ONE;
        }
        else
        #endif /* (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING ) */
        {
          /* Load TX_ENSURED Timer to network timer */
          LpNetwork->ddTimer = (CanSM_TimerType)CANSM_BOR_TIME_TXENSURED;
        }
        /* Exit Protection Area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
        /* Notify the current network mode to the BsWM*/
        BswM_CanSM_CurrentState(LpStaticNetwork->ucCanSmNetworkHandle,
          CANSM_BSWM_FULL_COMMUNICATION);

        /* Set the current mode of the network */
        LddCurrentState = (ComM_ModeType)COMM_FULL_COMMUNICATION;

        /* Notify the current network mode to the ComM*/
        ComM_BusSM_ModeIndication(LpStaticNetwork->ucCanSmNetworkHandle,
          &LddCurrentState);
      } /* End of if ((Std_ReturnType)E_OK == LddResult) */
      else
      {
        /* Load timer with CANSM_ONE */
        LpNetwork->ddTimer = (CanSM_TimerType)CANSM_ONE;
        /* Exit Protection Area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();  
      }
    }
    else
    {
      /* Exit Protection Area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
    }
  } /* End of if ((CanSM_TimerType)CANSM_ZERO == LpNetwork->ddTimer) */
} /* End of CanSM_BORWait(NetworkHandleType LddNetworkHandle) */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_CheckBusOff                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function check the end of bus of recovery      **
**                        procedure and any new bus off Occurence             **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GpStaticNw              **
**                                              CanSM_GaaNetwork              **
**                        Function(s) invoked : SchM_Enter_CanSM()            **
**                                              SchM_Exit_CanSM()             **
**                                              Dem_ReportErrorStatus()       **
**                                              CanSM_GetTxConfirmationState()**
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_CheckBusOff(NetworkHandleType LddNetworkHandle)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;

  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  CanSM_TimerType LddBORTimerTxEnsured;
  
  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);
  #endif

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];
  if ((uint8)COMM_NO_COMMUNICATION == LpNetwork->ucReqModeStatus)
  {

    /* Update Internal Substate as Zero*/
    LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;

    /* Update Internal ddTimer as Zero*/
    LpNetwork->ddTimer = (CanSM_TimerType)CANSM_ZERO;

    /* Update Internal ddBusOffCounter as Zero*/
    LpNetwork->ddBusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;

    /* Notify the network mode to the BswM */
    BswM_CanSM_CurrentState(LpStaticNetwork->ucCanSmNetworkHandle,
      CANSM_BSWM_NO_COMMUNICATION);
    
    /* Enter Protection Area */
    SchM_Enter_CanSM_BUSOFF_STATUS_PROTECTION();
    
    /* Update the Mode status as DeInitPnSupported */
    LpNetwork->ucModeStatus = CANSM_DEINITPNNOTSUPPORTED;
    
    /* Exit Protection Area */
    SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();
  }else{  
    /* Load the TX ENSURED timer to local variable */
    LddBORTimerTxEnsured = LpNetwork->ddTimer;
  
    /* Fixed Bug #1962 */
    if ((CanSM_TimerType)CANSM_ZERO != LddBORTimerTxEnsured)
    {
      /* Decrement the timer */
      --LddBORTimerTxEnsured;
    }

    /* Load the timer back from local variable */
    LpNetwork->ddTimer = LddBORTimerTxEnsured;
  
    #if (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)
    /* Goto CANSM_FULLCOMMUNICATION is CanSM_GetTxConfirmationState
       result CANIF_TX_RX_NOTIFICATION */
    if ((boolean)CANSM_TRUE == LpStaticNetwork->blCanSMTxConfirmationPolling)
    {
      /* Call CanSM_GetTxConfirmationState function  */
      if (CanSM_GetTxConfirmationState(CANSM_LDDNETWORKHANDLE) ==
          CANIF_TX_RX_NOTIFICATION)
      {
        /* Redmine 6235 */
        /* Enter Protection Area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();
        /* Check whether ucModeStatus is CANSM_BORSTART */
        if(LpNetwork->ucModeStatus != CANSM_BORSTART)
        {      
          /* Set the mode of the CanSM to CANSM_FULLCOMMUNICATION state */
          LpNetwork->ucModeStatus = CANSM_FULLCOMMUNICATION;

          /* Exit Protection Area */
          SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
        
          /* Check Bus Off Event occurred */
          if(LpNetwork->ddBusOffCounter != (CanSM_BusOffCntType)CANSM_ZERO)
          {
            /* Notify bus-off node to the BswM */
            BswM_RequestMode((BswM_UserType)CANSM_BSWM_USER_ID(LpStaticNetwork->ucCanSmNetworkHandle),
                      (BswM_ModeType)CANSM_BSWM_BOR_COMPLETE);
          }
    
          /* make the bus off counter zero */
          LpNetwork->ddBusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;
          #if (STD_ON == CANSM_DEM_STATUS)
          if(LpStaticNetwork->ddEventId != CANSM_DEM_NO_EVENT){
            /* Report the error to DEM with event id and DEM_EVENT_STATUS_PASSED */
            Dem_ReportErrorStatus
              (LpStaticNetwork->ddEventId, (Dem_EventStatusType)DEM_EVENT_STATUS_PASSED);
          }
          #endif
        /* Redmine 6235 */
        }else{
          /* Exit Protection Area */
          SchM_Exit_CanSM_MODE_STATUS_PROTECTION();  
        }
      }
    }/* End of if ((boolean)CANSM_TRUE ==
       *LpStaticNetwork->blCanSMTxConfirmationPolling) */
    #endif
    /* Goto CANSM_FULLCOMMUNICATION is timer becomes zero */
    if ((CanSM_TimerType)CANSM_ZERO == LddBORTimerTxEnsured)
    {
      /* Enter Protection Area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* Check whether ucModeStatus is CANSM_BORSTART */
      if(LpNetwork->ucModeStatus != CANSM_BORSTART)
      {
        /* Set the mode of the CanSM to CANSM_FULLCOMMUNICATION state */
        LpNetwork->ucModeStatus = CANSM_FULLCOMMUNICATION;

        /* Exit Protection Area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

        /* Check Whether Bus Off occurred */
        if(LpNetwork->ddBusOffCounter != (CanSM_BusOffCntType)CANSM_ZERO)
        {
          /* Notify bus-off node to the BswM */
          BswM_RequestMode((BswM_UserType)CANSM_BSWM_USER_ID(LpStaticNetwork->ucCanSmNetworkHandle),
                  (BswM_ModeType)CANSM_BSWM_BOR_COMPLETE);
        }
    
        /* make the bus off counter zero */
        LpNetwork->ddBusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;
    
        #if (STD_ON == CANSM_DEM_STATUS)
        if(LpStaticNetwork->ddEventId != CANSM_DEM_NO_EVENT){
          /* Report the error to DEM with event id and DEM_EVENT_STATUS_PASSED */
          Dem_ReportErrorStatus
          (LpStaticNetwork->ddEventId, (Dem_EventStatusType)DEM_EVENT_STATUS_PASSED);
        }
        #endif
        /* Redmine 6235 */
      }else{
        /* Exit Protection Area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
      }
    }
  }
} /* End of CanSM_CheckBusOff(NetworkHandleType LddNetworkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_FullCommunication                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function indicates Full Communication          **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_FullCommunication(NetworkHandleType
  LddNetworkHandle)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  #if (STD_ON == CANSM_PN_AVAILABILITY)
  boolean LblPnSupported;
  #endif

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);
  #endif

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  /* Check if request Mode is not equal to Full Communication */
  /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Its boundary is pre-defined " */
  if ((uint8)COMM_FULL_COMMUNICATION != LpNetwork->ucReqModeStatus)
  {
    /* Update Internal Substate as Zero*/
    LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;

    /* Check if request Mode is equal to No Communication */
    if ((uint8)COMM_SILENT_COMMUNICATION == LpNetwork->ucReqModeStatus)
    {
      /* Check if Mode is equal to Silent*/
      LpNetwork->ucModeStatus = CANSM_SILENTCOMMREQUESTED;

      /* Call the SilentComRequested function */
      CanSM_SilentCommRequested(CANSM_LDDNETWORKHANDLE);
    }
    else
    {
      /* Notify the network mode to the BswM */
      BswM_CanSM_CurrentState(LpStaticNetwork->ucCanSmNetworkHandle,
        CANSM_BSWM_NO_COMMUNICATION);

      /* Update the Mode status as DeInitPnSupported */
      LpNetwork->ucModeStatus = CANSM_DEINITPNNOTSUPPORTED;
      #if (STD_ON == CANSM_PN_AVAILABILITY)

      /* Update the local variable with Pnsupported value from Structure*/
      LblPnSupported =
        CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE].blPnSupported;

      /* Check if PN is supported */
      if ((boolean)CANSM_TRUE == LblPnSupported)
      {
        /* Increment the Mode by One*/
        LpNetwork->ucModeStatus = LpNetwork->ucModeStatus + CANSM_ONE;

        /* Initiate Partial Networking */
        CanSM_DeInitPnSupported(CANSM_LDDNETWORKHANDLE);
      }
      else
      {
        /* Call PN not supported function */
        CanSM_DeInitPnNotSupported(CANSM_LDDNETWORKHANDLE);
      }
      #else /* End of if (STD_ON == CANSM_PN_AVAILABILITY) */

      /* Call PN not supported function */
      CanSM_DeInitPnNotSupported(CANSM_LDDNETWORKHANDLE);
      #endif /* End of if (STD_ON == CANSM_PN_AVAILABILITY) */
    } /* End of else */
  } /* End of if ((uint8)COMM_FULL_COMMUNICATION != LpNetwork->ucReqModeStatus)
     **/
} /* End of CanSM_FullCommunication(NetworkHandleType */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_GetTxConfirmationState                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine checks the Occurence of bus off        **
**                        in case of POLLING.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_GpStaticNw          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                                             CanIf_GetTxConfirmationState() **
*******************************************************************************/
#if (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(CanIf_NotifStatusType, CANSM_CODE) CanSM_GetTxConfirmationState(
  NetworkHandleType LddNetworkHandle)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  CanIf_NotifStatusType LenRetVal = CANIF_TX_RX_NOTIFICATION;
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  uint8 LucControllerIndex;
  uint8 LucNoOfController;
  #endif
  
  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  
  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  /* Get the array index to the local variable */
  LucControllerIndex = LpStaticNetwork->ucControllerIndex;
  /* Get Tx Confirmation State of all controllers in designated network */
  /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Generated array index in range" */
  CANIF_GETTXCONFIRMATIONSTATE(LucControllerIndex);
  #else /* End of if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL) */
  LenRetVal = CanIf_GetTxConfirmationState(CANSM_CNTRL_ID);
  #endif /* (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL ) */
  return (LenRetVal);
} /* End of CanSM_GetTxConfirmationState(NetworkHandleType LddNetworkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING ) */

/*******************************************************************************
** Function Name        : CanSM_DeInitPnNotSupported                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine handles the De initialization          **
**                        process for partial netowrk                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_GpStaticNw          **
**                                                  CanSM_GaaNetwork          **
**                                                                            **
**                        Function(s) invoked   : CanIf_SetControllerMode()   **
**                                                CanIf_SetTransceiverMode()  **
**                                                BswM_CanSM_CurrentState()   **
**                                                ComM_BusSM_ModeIndication() **
**                                                CanIf_ClearTrcvWufFlag()    **
**                                                CanIf_CheckTrcvWakeFlag()   **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_DeInitPnNotSupported(NetworkHandleType
  LddNetworkHandle)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  ComM_ModeType LddCurrentState;
  Std_ReturnType LddResult;

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  
  LddResult = CANSM_E_WAITSTATE;

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  /* Check the Internal Substate as CANSM_WOPN_CS_STOPPED */
  if (CANSM_WOPN_CS_STOPPED == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANIF_CS_STOPPED;
    /* Set the controller mode as CANIF_CS_STOPPED */
    LddResult =
      CanSM_SetCanControllerMode(CANSM_LDDNETWORKHANDLE, CANIF_CS_STOPPED);

  }

  /* Check the Internal Substate as CANSM_WOPN_CS_SLEEP */
  if (CANSM_WOPN_CS_SLEEP == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANIF_CS_SLEEP;
    /* Set the controller mode as CANIF_CS_SLEEP */
    LddResult =
      CanSM_SetCanControllerMode(CANSM_LDDNETWORKHANDLE, CANIF_CS_SLEEP);

  }

  /* Check the Internal Substate as CANSM_WOPN_TRCV_MODE_NORMAL */
  if (CANSM_WOPN_TRCV_MODE_NORMAL == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANTRCV_TRCVMODE_NORMAL;
    /* Set the Transceiver mode as CANTRCV_TRCVMODE_NORMAL */
    LddResult =
      CanSM_SetCanTrcvMode(CANSM_LDDNETWORKHANDLE, CANTRCV_TRCVMODE_NORMAL);

  }

  /* Check the Internal Substate as CANSM_WOPN_TRCV_MODE_STANDBY */
  if (CANSM_WOPN_TRCV_MODE_STANDBY == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANTRCV_TRCVMODE_STANDBY;
    /* Set the Transceiver mode as CANTRCV_TRCVMODE_STANDBY */
    LddResult =
      CanSM_SetCanTrcvMode(CANSM_LDDNETWORKHANDLE, CANTRCV_TRCVMODE_STANDBY);

  }

  /* Check the Internal Substate as CANSM_WOPN_NO_COMMUNICATION */
  if (CANSM_WOPN_NO_COMMUNICATION == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ddCanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_GddModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    LpNetwork->ucCanSMModeReqReptMax = (uint8)CanSm_GucModeReqMax;

    LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;

    /* Change internal status */
    LpNetwork->ucModeStatus = CANSM_NOCOMMUNICATION;

    /* Current state as COMM_SILENT_COMMUNICATION */
    LddCurrentState = (ComM_ModeType)COMM_NO_COMMUNICATION;

    /* Notify internally stored network mode to the ComM*/
    ComM_BusSM_ModeIndication(LpStaticNetwork->ucCanSmNetworkHandle,
      &LddCurrentState);
    
    /* Notify bus-off node to the BswM */
    BswM_RequestMode((BswM_UserType)CANSM_BSWM_USER_ID(LpStaticNetwork->ucCanSmNetworkHandle),
                      (BswM_ModeType)CANSM_BSWM_BOR_COMPLETE);
    
    /* Update Internal ddBusOffCounter as Zero*/
    LpNetwork->ddBusOffCounter = (CanSM_BusOffCntType)CANSM_ZERO;
    
  } /* End of if (CANSM_WOPN_NO_COMMUNICATION ==
     *LpNetwork->ucCanSMNWIntSubState) */
  else if ((uint8)E_OK == LddResult)
  {
    /* Load the request Repetition Time value in the Local variable */
    LpNetwork->ddCanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_GddModeReqRepeatTime;
  }
  else
  {
    /* Call the function for Time Out Processing */
    CanSM_TimeoutProcessing(CANSM_LDDNETWORKHANDLE, LddResult);
  }
} /* End of CanSM_DeInitPnNotSupported(NetworkHandleType */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_DeInitPnSupported                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine handles the De initialization          **
**                        process for partial netowrk                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_GpStaticNw          **
**                                                  CanSM_GaaNetwork          **
**                                                                            **
**                        Function(s) invoked   : CanIf_SetControllerMode()   **
**                                                CanIf_SetTransceiverMode()  **
**                                                BswM_CanSM_CurrentState()   **
**                                                ComM_BusSM_ModeIndication() **
**                                                CanIf_ClearTrcvWufFlag()    **
**                                                CanIf_CheckTrcvWakeFlag()   **
*******************************************************************************/
#if (STD_ON == CANSM_PN_AVAILABILITY)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_DeInitPnSupported(NetworkHandleType
  LddNetworkHandle)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  ComM_ModeType LddCurrentState;
  Std_ReturnType LddResult;

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  
  /* Initial value as Wait State */
  LddResult = CANSM_E_WAITSTATE;

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];
  #if (STD_ON == CANSM_PN_AVAILABILITY)
  /* Clear the Wake up Flag  */
  if (CANSM_PN_TRCV_CLEAR_WUF == LpNetwork->ucCanSMNWIntSubState)
  {
    LddResult = CanSM_ClearTrcvWuf(CANSM_LDDNETWORKHANDLE);
  }
  #endif /* #if (STD_ON == CANSM_PN_AVAILABILITY) */
  /* Set the Transceiver Mode to Stop */
  if (CANSM_PN_CC_STOPPED == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANIF_CS_STOPPED;
    LddResult =
      CanSM_SetCanControllerMode(CANSM_LDDNETWORKHANDLE, CANIF_CS_STOPPED);

  }

  /* Set the Transceiver Mode to Normal */
  if (CANSM_PN_TRCV_NORMAL == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANTRCV_TRCVMODE_NORMAL;
    LddResult =
      CanSM_SetCanTrcvMode(CANSM_LDDNETWORKHANDLE, CANTRCV_TRCVMODE_NORMAL);

  }

  /* Set the Transceiver Mode to StandBy */
  if (CANSM_PN_TRCV_STANDBY == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANTRCV_TRCVMODE_STANDBY;
    LddResult =
      CanSM_SetCanTrcvMode(CANSM_LDDNETWORKHANDLE, CANTRCV_TRCVMODE_STANDBY);

  }

  /* Set the Controller Mode to Sleep */
  if (CANSM_PN_CS_SLEEP == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANIF_CS_SLEEP;
    LddResult =
      CanSM_SetCanControllerMode(CANSM_LDDNETWORKHANDLE, CANIF_CS_SLEEP);

  }

  /* Check the Transceiver Wake Up Flag  */
  if ((CANSM_PN_TRCV_CHECK_WUF == LpNetwork->ucCanSMNWIntSubState) ||
      (CANSM_PN_WFLAG_IN_NOT_CC_SLEEP == LpNetwork->ucCanSMNWIntSubState))
  {
    LddResult = CanSM_CheckTrcvWuf(CANSM_LDDNETWORKHANDLE);
  }
  /* Reset the Substate to Initial Sunstate and update
   *                                             Mode of the network as No COMM
   * */

  if ((CANSM_PN_IN_NOT_CC_SLEEP_NOCOMM == LpNetwork->ucCanSMNWIntSubState) ||
      (CANSM_PN_NO_COMMUNICATION == LpNetwork->ucCanSMNWIntSubState))
  {
    LpNetwork->ddCanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_GddModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    LpNetwork->ucCanSMModeReqReptMax = (uint8)CanSm_GucModeReqMax;

    if (CANSM_PN_NO_COMMUNICATION == LpNetwork->ucCanSMNWIntSubState)
    {
      /* Change internal status */
      LpNetwork->ucModeStatus = CANSM_NOCOMMUNICATION;

      /* Current state as COMM_SILENT_COMMUNICATION */
      LddCurrentState = (ComM_ModeType)COMM_NO_COMMUNICATION;

      /* Notify internally stored network mode to the ComM*/
      ComM_BusSM_ModeIndication(LpStaticNetwork->ucCanSmNetworkHandle,
        &LddCurrentState);
    } /* End of if (CANSM_PN_NO_COMMUNICATION ==
       *LpNetwork->ucCanSMNWIntSubState) */
        
    /* #14519 Notify bus-off node to the BswM */
    BswM_RequestMode((BswM_UserType)CANSM_BSWM_USER_ID(LpStaticNetwork->ucCanSmNetworkHandle),
                      (BswM_ModeType)CANSM_BSWM_BOR_COMPLETE);       

    /* Update the SubState as Zero */
    LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;
  } /* End of if ((CANSM_PN_IN_NOT_CC_SLEEP_NOCOMM ==
     *LpNetwork->ucCanSMNWIntSubState) || */

  /* Check if LddResult is equal to E_OK */
  if ((uint8)E_OK == LddResult)
  {
    /* Load the request Repetition Time value in the Local variable */
    LpNetwork->ddCanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_GddModeReqRepeatTime;
  }
  else
  {
    /* Call the function for Time Out Processing */
    CanSM_TimeoutProcessing(CANSM_LDDNETWORKHANDLE, LddResult);
  }
} /* End of CanSM_DeInitPnSupported(NetworkHandleType */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_PN_AVAILABILITY) */

/*******************************************************************************
** Function Name        : CanSM_NoToFullCommRequested                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_FULL_COMMUNICATION for the corresponding      **
**                        network handle.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_GpStaticNw          **
**                                                  CanSM_GaaNetwork          **
**                                                                            **
**                        Function(s) invoked    :CanIf_SetTransceiverMode()  **
**                                                CanIf_SetControllerMode()   **
**                                                CanIf_SetPduMode()          **
**                                                BswM_CanSM_CurrentState()   **
**                                                ComM_BusSM_ModeIndication() **
**                                                SchM_Enter_CanSM()          **
**                                                SchM_Exit_CanSM()           **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_NoToFullCommRequested(NetworkHandleType
  LddNetworkHandle)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  ComM_ModeType LddCurrentState;
  Std_ReturnType LddResult;
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  uint8 LucControllerIndex;
  uint8 LucNoOfController;
  #endif

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  /* Initial value as Wait State */
  LddResult = CANSM_E_WAITSTATE;

  /* Set the Transceiver Mode to Normal */
  if (CANSM_PREFULL_TRCV_NORMAL == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANTRCV_TRCVMODE_NORMAL;
    LddResult =
      CanSM_SetCanTrcvMode(CANSM_LDDNETWORKHANDLE, CANTRCV_TRCVMODE_NORMAL);

  }

  /* Set the Transceiver Mode to StandBy */
  if (CANSM_PREFULL_CC_STOPPED == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANIF_CS_STOPPED;
    LddResult =
      CanSM_SetCanControllerMode(CANSM_LDDNETWORKHANDLE, CANIF_CS_STOPPED);

  }

  /* Set the Controller Mode to Sleep */
  if (CANSM_PREFULL_CC_STARTED == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANIF_CS_STARTED;
    LddResult =
      CanSM_SetCanControllerMode(CANSM_LDDNETWORKHANDLE, CANIF_CS_STARTED);

  }

  if (CANSM_PREFULL_CC_ONLINE == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ddCanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_GddModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    LpNetwork->ucCanSMModeReqReptMax = (uint8)CanSm_GucModeReqMax;
    LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;

    /* Enter Protection Area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /* Set the mode of the CanSM to CANSM_CHECKBUSOFF state */
    LpNetwork->ucModeStatus = CANSM_CHECKBUSOFF;

    /* Exit Protection Area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

    /* Notify internally stored network mode to the BsWM */
    BswM_CanSM_CurrentState(LpStaticNetwork->ucCanSmNetworkHandle,
      CANSM_BSWM_FULL_COMMUNICATION);
    #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Generated array index in range" */	
    CANIF_SETPDUMODE(LpStaticNetwork->ucControllerIndex, CANIF_SET_ONLINE)
    #else
    (void)CanIf_SetPduMode(CANSM_CNTRL_ID, CANIF_SET_ONLINE);
    #endif

    /* Internal state COMM_FULL_COMMUNICATION */
    LddCurrentState = (ComM_ModeType)COMM_FULL_COMMUNICATION;

    /* Notify internally stored network mode to the ComM */
    ComM_BusSM_ModeIndication(LpStaticNetwork->ucCanSmNetworkHandle,
      &LddCurrentState);
    
    #if (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)

    /* Check whether Polling is supported for the network */
    if (CANSM_TRUE == LpStaticNetwork->blCanSMTxConfirmationPolling)
    {
      LpNetwork->ddTimer = (CanSM_TimerType)CANSM_ONE;
    }
    else
    #endif /* (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING ) */
    {
      /* Load TX_ENSURED Timer to network timer */
      LpNetwork->ddTimer = (CanSM_TimerType)CANSM_BOR_TIME_TXENSURED;
    }
  } /* End of if (CANSM_PREFULL_CC_ONLINE == LpNetwork->ucCanSMNWIntSubState) */
  else if ((uint8)E_OK == LddResult)
  {
    /* Load the request Repetition Time value in the Local variable */
    LpNetwork->ddCanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_GddModeReqRepeatTime;
  }
  else
  {
    /* Call the function for Time Out Processing */
    CanSM_TimeoutProcessing(CANSM_LDDNETWORKHANDLE, LddResult);
  }
} /* End of CanSM_NoToFullCommRequested(NetworkHandleType */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_TxTimeoutExceptionService                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_FULL_COMMUNICATION for the corresponding      **
**                        network handle.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :  CanSM_GpStaticNw          **
**                                                  CanSM_GaaNetwork          **
**                                                                            **
**                        Function(s) invoked    :CanIf_SetTransceiverMode()  **
**                                                CanIf_SetControllerMode()   **
**                                                CanIf_SetPduMode()          **
**                                                BswM_CanSM_CurrentState()   **
**                                                ComM_BusSM_ModeIndication() **
**                                                SchM_Enter_CanSM()          **
**                                                SchM_Exit_CanSM()           **
*******************************************************************************/
#if (STD_ON == CANSM_PN_AVAILABILITY)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_TxTimeoutExceptionService(NetworkHandleType
  LddNetworkHandle)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  Std_ReturnType LddResult;
  
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  uint8 LucNoOfController;
  uint8 LucControllerIndex;
  #endif

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif

  /* #14496 */
  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  LddResult = CANSM_E_WAITSTATE;

  /* Check if Internal State is equal to CANSM_TIMEOUT_CC_STOPPED  */
  /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
  if (CANSM_TIMEOUT_CC_STOPPED == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANIF_CS_STOPPED;
    /* Set the Controller mode as CANIF_CS_STOPPED */
    LddResult =
      CanSM_SetCanControllerMode(CANSM_LDDNETWORKHANDLE, CANIF_CS_STOPPED);

  }

  /* Check if Internal State is equal to CANSM_TIMEOUT_CC_STARTED  */
  if (CANSM_TIMEOUT_CC_STARTED == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANIF_CS_STARTED;
    /* Set the Controller mode as CANIF_CS_STARTED */
    LddResult =
      CanSM_SetCanControllerMode(CANSM_LDDNETWORKHANDLE, CANIF_CS_STARTED);

  }

  /* Check if Internal State is equal to CANSM_TIMEOUT_CC_ONLINE  */
  if (CANSM_TIMEOUT_CC_ONLINE == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ddCanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_GddModeReqRepeatTime;

    /* Reset the Mode repetition request*/
    LpNetwork->ucCanSMModeReqReptMax = (uint8)CanSm_GucModeReqMax;

    /* Update the Internal SubState with the value as Zero*/
    LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;

    /* #14496 */
    #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Generated array index in range" */	
    CANIF_SETPDUMODE(LpStaticNetwork->ucControllerIndex, CANIF_SET_ONLINE)
    #else
    (void)CanIf_SetPduMode(CANSM_CNTRL_ID, CANIF_SET_ONLINE);
    #endif

    /* Enter protection area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /* Set the mode of the CanSM to ONLINE state */
    LpNetwork->ucModeStatus = CANSM_FULLCOMMUNICATION;

    /* Exit protection area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

    /* Initiate the Full Communication for the network */
    CanSM_FullCommunication(CANSM_LDDNETWORKHANDLE);
  } /* End of if (CANSM_TIMEOUT_CC_ONLINE == LpNetwork->ucCanSMNWIntSubState) */
  else if ((uint8)E_OK == LddResult)
  {
    /* Load the request Repetition Time value in the Local variable */
    LpNetwork->ddCanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_GddModeReqRepeatTime;
  }
  else
  {
    /* Call the function for Time Out Processing */
    CanSM_TimeoutProcessing(CANSM_LDDNETWORKHANDLE, LddResult);
  }
} /* End of CanSM_TxTimeoutExceptionService(NetworkHandleType */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : CanSM_ChangeBaudRateService                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_FULL_COMMUNICATION or CANSM_NO_COMMUNICATION  **
**                        for the corresponding network handle.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GpStaticNw              **
**                                              CanSM_GaaNetwork              **
**                        Function(s) invoked : CanIf_SetTransceiverMode()    **
**                                              CanIf_SetControllerMode()     **
**                                              CanIf_SetPduMode()            **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
**                                              SchM_Enter_CanSM()            **
**                                              SchM_Exit_CanSM()             **
*******************************************************************************/
#if (STD_ON == CANSM_CHANGE_BAUDRATE_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_ChangeBaudRateService(NetworkHandleType
  LddNetworkHandle)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  ComM_ModeType LddCurrentState;
  uint16 LusBaudrate;
  Std_ReturnType LddResult;
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  uint8 LucNoOfController;
  uint8 LucControllerIndex;
  #endif

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  /* Update the local Variable with default value */
  LddResult = CANSM_E_WAITSTATE;

  /* Check if Internal State is equal to CANSM_BR_CC_STOPPED  */
  if (CANSM_BR_CC_STOPPED == LpNetwork->ucCanSMNWIntSubState)
  {
    LpNetwork->ucMode = (uint8)CANIF_CS_STOPPED;
    /* Set the Controller mode as CANIF_CS_STOPPED */
    LddResult =
      CanSM_SetCanControllerMode(CANSM_LDDNETWORKHANDLE, CANIF_CS_STOPPED);

  }

  /* Check if Internal State is equal to CANSM_BR_STARTED  */
  if (CANSM_BR_STARTED == LpNetwork->ucCanSMNWIntSubState)
  {
    /* Set the current mode of the network as No Communication  */
    LddCurrentState = (ComM_ModeType)COMM_NO_COMMUNICATION;

    /* Notify to ComM */
    ComM_BusSM_ModeIndication(LpStaticNetwork->ucCanSmNetworkHandle,
      &LddCurrentState);

    /* Initialize the variable with E_OK */
    LddResult = (uint8)E_OK;
    LusBaudrate = LpNetwork->usBaudrate;
    #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)

    /* Change the Baudrate of the respective controllers*/
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Generated array index in range" */
    CANIF_CHANGEBAUDRATE(LpStaticNetwork->ucControllerIndex, LusBaudrate)
    #else

    /* Change the Baudrate of the respective controllers*/
    LddResult |= CanIf_ChangeBaudrate(CANSM_CNTRL_ID, LusBaudrate);
    #endif

    if ((uint8)E_OK == LddResult)
    {
      LpNetwork->ucMode = (uint8)CANIF_CS_STARTED;
      /* Set the Controller mode as CANIF_CS_STARTED */
      LddResult =
        CanSM_SetCanControllerMode(CANSM_LDDNETWORKHANDLE, CANIF_CS_STARTED);

    }
  } /* End of if (CANSM_BR_STARTED == LpNetwork->ucCanSMNWIntSubState) */

  /* Check if Internal State is equal to CANSM_TIMEOUT_CC_ONLINE  */
  if (CANSM_BR_CC_ONLINE == LpNetwork->ucCanSMNWIntSubState)
  {
    /* Update the Internal State as Zero */
    LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;

    /* Check if requested mode is Full Communication */
    if ((uint8)COMM_FULL_COMMUNICATION == LpNetwork->ucReqModeStatus)
    {
      /* update the Current state as Full Communication */
      LddCurrentState = (ComM_ModeType)COMM_FULL_COMMUNICATION;

      /* Notify to ComM */
      ComM_BusSM_ModeIndication(LpStaticNetwork->ucCanSmNetworkHandle,
        &LddCurrentState);
    }
    /* Enter protection area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /* Set the mode of the CanSM to ONLINE state */
    LpNetwork->ucModeStatus = CANSM_FULLCOMMUNICATION;

    /* Exit protection area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

    /* Initiate the Full communication */
    CanSM_FullCommunication(CANSM_LDDNETWORKHANDLE);
  } /* End of if (CANSM_BR_CC_ONLINE == LpNetwork->ucCanSMNWIntSubState) */
  else if ((uint8)E_OK == LddResult)
  {
    /* Load the request Repetition Time value in the Local variable */
    LpNetwork->ddCanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_GddModeReqRepeatTime;
  }
  else
  {
    /* Call the function for Time Out Processing */
    CanSM_TimeoutProcessing(CANSM_LDDNETWORKHANDLE, LddResult);
  }
} /* End of CanSM_ChangeBaudRateService(NetworkHandleType LddNetworkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : CanSM_SilentToFullCommRequested                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_FULL_COMMUNICATION for the corresponding      **
**                        network handle.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GpStaticNw        **
**                                              CanSM_GaaNetwork              **
**                        Function(s) invoked : CanIf_SetPduMode()            **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
**                                              SchM_Enter_CanSM()            **
**                                              SchM_Exit_CanSM()             **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_SilentToFullCommRequested(NetworkHandleType
  LddNetworkHandle)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  ComM_ModeType LddCurrentState;
  Std_ReturnType LddResult;
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  uint8 LucControllerIndex;
  uint8 LucNoOfController;
  #endif

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  
  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  /* Initialize the variable with E_OK */
  LddResult = (uint8)E_OK;

  /* Set the Pdu mode to online */
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Generated array index in range" */	
  CANIF_SETPDUMODE(LpStaticNetwork->ucControllerIndex, CANIF_SET_TX_ONLINE)
  #else
  LddResult |= CanIf_SetPduMode(LpStaticNetwork->ucControllerIndex,
    CANIF_SET_TX_ONLINE);
  #endif

  if ((uint8)E_OK == LddResult)
  {
    /* Enter Protection Area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /* Set the mode of the CanSM to CANSM_CHECKBUSOFF state */
    LpNetwork->ucModeStatus = CANSM_CHECKBUSOFF;

    /* Exit Protection Area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

    /* Load the timer with value One */
    LpNetwork->ddTimer = (CanSM_TimerType)CANSM_ONE;

    /* Current state as COMM_FULL_COMMUNICATION */
    LddCurrentState = (ComM_ModeType)COMM_FULL_COMMUNICATION;

    /* Notify internally stored network mode to the ComM*/
    ComM_BusSM_ModeIndication(LpStaticNetwork->ucCanSmNetworkHandle,
      &LddCurrentState);

    /* Notify internally stored network mode to the BsWM*/
    BswM_CanSM_CurrentState(LpStaticNetwork->ucCanSmNetworkHandle,
      CANSM_BSWM_FULL_COMMUNICATION);

    /* Call the BusOff Function */
    CanSM_CheckBusOff(CANSM_LDDNETWORKHANDLE);
  } /* End of if ((uint8)E_OK == LddResult) */
} /* End of CanSM_SilentToFullCommRequested(NetworkHandleType LddNetworkHandle)
   **/

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_SilentCommRequested                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall have a transition to             **
**                        CANSM_SILENT_COMMUNICATION for the corresponding    **
**                        network handle.                                     **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GpStaticNw              **
**                                              CanSM_GaaNetwork              **
**                        Function(s) invoked : CanIf_SetPduMode()            **
**                                              BswM_CanSM_CurrentState()     **
**                                              ComM_BusSM_ModeIndication()   **
**                                              SchM_Enter_CanSM()            **
**                                              SchM_Exit_CanSM()             **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_SilentCommRequested(NetworkHandleType
  LddNetworkHandle)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  ComM_ModeType LddCurrentState;
  Std_ReturnType LddResult;
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  uint8 LucControllerIndex;
  uint8 LucNoOfController;
  #endif

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  
  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  /* Notify internally stored network mode to the BsWM */
  BswM_CanSM_CurrentState(LpStaticNetwork->ucCanSmNetworkHandle,
    CANSM_BSWM_SILENT_COMMUNICATION);

  /* Set the Pdu mode to online */
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)

  /* Initialize the variable with E_OK */
  LddResult = (uint8)E_OK;
	
  /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Generated array index in range" */
  CANIF_SETPDUMODE(LpStaticNetwork->ucControllerIndex, CANIF_SET_ONLINE)
  #else

  /* Set PduMode as Online*/
  LddResult = CanIf_SetPduMode(LpStaticNetwork->ucControllerIndex,
                                                             CANIF_SET_ONLINE);
  #endif

  /* Check if E_OK is returned */
  if ((uint8)E_OK == LddResult)
  {
    #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)

    /* Set Pdu Mode as Offline */
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Generated array index in range" */
    CANIF_SETPDUMODE(LpStaticNetwork->ucControllerIndex, CANIF_SET_TX_OFFLINE)
    #else

    /* Set Pdu Mode as Offline */
    LddResult = CanIf_SetPduMode (LpStaticNetwork->ucControllerIndex,
                                                         CANIF_SET_TX_OFFLINE);
    #endif

    /* Check id E_OK is returned */
    if ((uint8)E_OK == LddResult)
    {
      /* Enter Protection area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* Set the mode of the CanSM to SILENT state */
      LpNetwork->ucModeStatus = CANSM_SILENTCOMMUNICATION;

      /* Exit Protection area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

      /* Current state as COMM_SILENT_COMMUNICATION */
      LddCurrentState = (ComM_ModeType)COMM_SILENT_COMMUNICATION;

      /* Notify internally stored network mode to the ComM*/
      ComM_BusSM_ModeIndication(LpStaticNetwork->ucCanSmNetworkHandle,
        &LddCurrentState);
    } /* End of if ((uint8)E_OK == LddResult) */
  } /* End of if ((uint8)E_OK == LddResult) */
} /* End of CanSM_SilentCommRequested(NetworkHandleType LddNetworkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_NoCommunication                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service indicates the current state as         **
**                        CANSM_NO_COMMUNICATION for the corresponding        **
**                        network handle.                                     **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : CanSM_NoToFullCommRequested() **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_NoCommunication(NetworkHandleType LddNetworkHandle)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  
  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);
  #endif

  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];
  
  /* Check if Requested Mode Status is equal to No communication */
  /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
  if ((uint8)COMM_NO_COMMUNICATION != LpNetwork->ucReqModeStatus)
  {
    /* Update the Mode status to CANSM_NOTOFULLCOMMREQUESTED */
    LpNetwork->ucModeStatus = CANSM_NOTOFULLCOMMREQUESTED;

    /* Update the Internal Substate as Zero */
    LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;
    CanSM_NoToFullCommRequested(CANSM_LDDNETWORKHANDLE);
  }
} /* End of CanSM_NoCommunication(NetworkHandleType LddNetworkHandle) */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_SilentCommunication                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service indicates the current state as         **
**                        CANSM_SILENT_COMMUNICATION for the corresponding    **
**                        network handle.                                     **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GaaNetwork              **
**                        Function(s) invoked : BswM_CanSM_CurrentState()     **
**                                              CanSM_DeInitPnSupported()     **
**                                              CanSM_DeInitPnNotSupported()  **
**                                           CanSM_SilentToFullCommRequested()**
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_SilentCommunication(NetworkHandleType
  LddNetworkHandle)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  #if (STD_ON == CANSM_PN_AVAILABILITY)
  boolean LblPnSupported;
  #endif

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  
  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  /* Check if Requested Mode Status is not equal to Silent Communication */
  /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
  if ((uint8)COMM_SILENT_COMMUNICATION != LpNetwork->ucReqModeStatus)
  {
    /* Update Internal Substate as zero */
    LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;

    /* Check if Requested Mode Status is not equal to Full Communication */		
    if ((uint8)COMM_FULL_COMMUNICATION == LpNetwork->ucReqModeStatus)
    {
      /* Update Internal Substate as CANSM_SILENTTOFULLCOMMREQUESTED */
      LpNetwork->ucModeStatus = CANSM_SILENTTOFULLCOMMREQUESTED;

      /* Call the function CanSM_SilentToFullCommRequested */
      CanSM_SilentToFullCommRequested(CANSM_LDDNETWORKHANDLE);
    }
    else
    {
      /* Notify the network mode to the BswM */
      BswM_CanSM_CurrentState(LpStaticNetwork->ucCanSmNetworkHandle,
        CANSM_BSWM_NO_COMMUNICATION);

      /* Update the Mode status as CANSM_DEINITPNNOTSUPPORTED */
      LpNetwork->ucModeStatus = CANSM_DEINITPNNOTSUPPORTED;
      #if (STD_ON == CANSM_PN_AVAILABILITY)
      LblPnSupported =
        CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE].blPnSupported;

      /* Check if Partial Networking is Available */
      if ((boolean)CANSM_TRUE == LblPnSupported)
      {
        /* Increment the mode by one */
        LpNetwork->ucModeStatus = LpNetwork->ucModeStatus + CANSM_ONE;

        /* Call the CanSM_DeInitPnSupported funcion  */
        CanSM_DeInitPnSupported(CANSM_LDDNETWORKHANDLE);
      }
      else
      {
        /* Call the CanSM_DeInitPnNotSupported funcion  */
        CanSM_DeInitPnNotSupported(CANSM_LDDNETWORKHANDLE);
      }
      #else /* End of if (STD_ON == CANSM_PN_AVAILABILITY) */

      /* Call the CanSM_DeInitPnNotSupported funcion  */
      CanSM_DeInitPnNotSupported(CANSM_LDDNETWORKHANDLE);
      #endif /* End of if (STD_ON == CANSM_PN_AVAILABILITY) */
    } /* End of else */
  } /* End of if ((uint8)COMM_SILENT_COMMUNICATION !=
     *LpNetwork->ucReqModeStatus) */
} /* End of CanSM_SilentCommunication(NetworkHandleType LddNetworkHandle) */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_ClearTrcvWuf                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine is called for Clearing the transceiver **
**                        flag.                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType  LddResult                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GpStaticNw              **
**                                              CanSM_GaaNetwork              **
**                        Function(s) invoked : CanIf_ClearTrcvWufFlag()      **
*******************************************************************************/
#if(STD_ON == CANSM_PN_AVAILABILITY)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANSM_CODE) CanSM_ClearTrcvWuf(NetworkHandleType
  LddNetworkHandle)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  #if (STD_ON == CANSM_CANTRCV_SUPPORT)
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  #endif
  Std_ReturnType LddResult;

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  
  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  /* Initialize the variable with E_OK */
  LddResult = (uint8)E_OK;
  #if (STD_ON == CANSM_CANTRCV_SUPPORT)

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  if (CANSM_CANTRCV_INVALID_ID != LpStaticNetwork->ucCanSmTranceiverId)
  {
    LddResult = CanIf_ClearTrcvWufFlag(LpStaticNetwork->ucCanSmTranceiverId);

    if ((uint8)E_OK == LddResult)
    {
      /* Update the Internal Substate*/
      LpNetwork->ucCanSMNWIntSubState =
        LpNetwork->ucCanSMNWIntSubState + CANSM_ONE;
    }
  }
  else
  #endif /* End of if (STD_ON == CANSM_CANTRCV_SUPPORT) */
  {
    /* Update the Internal Substate*/
    LpNetwork->ucCanSMNWIntSubState =
      LpNetwork->ucCanSMNWIntSubState + CANSM_TWO;
  }
  return (LddResult);
} /* End of CanSM_ClearTrcvWuf(NetworkHandleType LddNetworkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif/* #if(STD_ON == CANSM_PN_AVAILABILITY) */
/*******************************************************************************
** Function Name        : CanSM_CheckTrcvWuf                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine is called for Checking the transceiver **
**                        flag.                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType LddResult                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : CanSM_GpStaticNw           **
**                                                 CanSM_GaaNetwork           **
**                        Function(s) invoked    : CanIf_CheckTrcvWufFlag()   **
*******************************************************************************/
#if (STD_ON == CANSM_PN_AVAILABILITY)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANSM_CODE) CanSM_CheckTrcvWuf(NetworkHandleType
  LddNetworkHandle)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  #if (STD_ON == CANSM_CANTRCV_SUPPORT)
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  #endif
  Std_ReturnType LddResult;

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  
  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  /* Initialize the variable with E_OK */
  LddResult = (uint8)E_OK;
  #if (STD_ON == CANSM_CANTRCV_SUPPORT)

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  if (CANSM_CANTRCV_INVALID_ID != LpStaticNetwork->ucCanSmTranceiverId)
  {
    /*Check whether flag is cleared*/
    LddResult = CanIf_CheckTrcvWakeFlag(LpStaticNetwork->ucCanSmTranceiverId);

    /* Check if E_OK is returned */
    if ((uint8)E_OK == LddResult)
    {
      /* Increment the internal Substate by one */
      LpNetwork->ucCanSMNWIntSubState =
        LpNetwork->ucCanSMNWIntSubState + CANSM_ONE;
    }
  } /* End of if (CANSM_CANTRCV_INVALID_ID !=
     *LpStaticNetwork->ucCanSmTranceiverId) */
  else
  #endif /* End of if (STD_ON == CANSM_CANTRCV_SUPPORT) */
  {
    /* Update the Internal Substate*/
    LpNetwork->ucCanSMNWIntSubState =
      LpNetwork->ucCanSMNWIntSubState + CANSM_TWO;
  }
  return (LddResult);
} /* End of CanSM_CheckTrcvWuf(NetworkHandleType LddNetworkHandle) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif/* #if (STD_ON == CANSM_PN_AVAILABILITY) */
/*******************************************************************************
** Function Name        : CanSM_SetCanControllerMode                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine is called for setting the controller   **
**                        mode.                                               **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                        CanIf_ControllerModeType LenMode                    **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : CanSM_GpStaticNw           **
**                                                 CanSM_GaaNetwork           **
**                        Function(s) invoked    : CanIf_SetControllerMode()  **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(uint8, CANSM_CODE) CanSM_SetCanControllerMode(NetworkHandleType
  LddNetworkHandle, CanIf_ControllerModeType LenMode)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  Std_ReturnType LddResult;

  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  uint8 LucNoOfController;
  uint8 LucControllerIndex;
  #endif
  
  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  
  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)

  /* Initialize the variable with E_OK */
  LddResult = (uint8)E_OK;

  /* Set the controller mode to sleep */
  /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Generated array index in range" */
  CANIF_SETCONTROLLERMODE(LpStaticNetwork->ucControllerIndex, LenMode)
  #else

  /* Set the controllermode to sleep */
  LddResult = CanIf_SetControllerMode
                                (LpStaticNetwork->ucControllerIndex, LenMode);
  #endif

  /* Check if LddResult is equal to E_OK */
  if ((uint8)E_OK == LddResult)
  {
    /* Get the address of CanSM_GaaNetwork to local pointer */
    LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

    /* Update the Internal Substate*/
    LpNetwork->ucCanSMNWIntSubState =
      LpNetwork->ucCanSMNWIntSubState + CANSM_ONE;
  }
  return (LddResult);
} /* End of CanSM_SetCanControllerMode(NetworkHandleType LddNetworkHandle,
   *CanIf_ControllerModeType LenMode) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_SetCanTrcvMode                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine is called for setting the transceiver  **
**                        mode.                                               **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                        CanTrcv_TrcvModeType LenMode                        **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : CanSM_GaaNetwork           **
**                                                 CanSM_GpStaticNw           **
**                        Function(s) invoked    : CanIf_SetTrcvMode()        **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetCanTrcvMode(NetworkHandleType
  LddNetworkHandle, CanTrcv_TrcvModeType LenMode)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  #if (STD_ON == CANSM_CANTRCV_SUPPORT)
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  #endif
  Std_ReturnType LddResult;

  #if (STD_OFF == CANSM_CANTRCV_SUPPORT)
  CANSM_UNUSED(LenMode);
  #endif

  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  
  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  /* Initialize the variable with E_OK */
  LddResult = (uint8)E_OK;
  #if (STD_ON == CANSM_CANTRCV_SUPPORT)

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

  if ((uint8)CANSM_CANTRCV_INVALID_ID != LpStaticNetwork->ucCanSmTranceiverId)
  {
    /*Check whether the mode is set*/
    LddResult =
      CanIf_SetTrcvMode(LpStaticNetwork->ucCanSmTranceiverId, LenMode);

    /* Check if LddResult is equal to E_OK */
    if ((uint8)E_OK == LddResult)
    {
      /* Update the Internal Substate*/
      LpNetwork->ucCanSMNWIntSubState =
        LpNetwork->ucCanSMNWIntSubState + CANSM_ONE;
    }
  } /* End of if ((uint8)CANSM_CANTRCV_INVALID_ID !=
     *LpStaticNetwork->ucCanSmTranceiverId) */
  else
  #endif /* End of if (STD_ON == CANSM_CANTRCV_SUPPORT) */
  {
    /* Update the Internal Substate*/
    LpNetwork->ucCanSMNWIntSubState =
      LpNetwork->ucCanSMNWIntSubState + CANSM_TWO;
  }
  return (LddResult);
} /* End of CanSM_SetCanTrcvMode(NetworkHandleType LddNetworkHandle,
   *CanTrcv_TrcvModeType LenMode) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_TimeoutProcessing                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine is called for Processing the time      **
**                        required to srvice the requested mode change.       **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : NetworkHandleType LddNetworkHandle                  **
**                        Std_ReturnType LddResult                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GpStaticNw              **
**                        Function(s) invoked : CanIf_SetTrcvMode()           **
**                                              Dem_ReportErrorStatus()       **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_TimeoutProcessing(NetworkHandleType
  LddNetworkHandle, Std_ReturnType LddResult)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  CanSM_TimerType LddReqReptTime;
  
  /* #4509 */
  #if (STD_ON == CANSM_DEM_STATUS)
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;

  /* Get the address of CanSM_GpStaticNw to local pointer */
  LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];
  #endif /*STD_ON == CANSM_DEM_STATUS*/
  
  #if (STD_ON == CANSM_SINGLE_NW_CHANNEL)
  CANSM_UNUSED(LddNetworkHandle);  
  #endif
  
  /* Get the address of CanSM_GaaNetwork to local pointer */
  LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

  if ((uint8)E_NOT_OK == LddResult)
  {
    /* Decrement the counter */
    LpNetwork->ucCanSMModeReqReptMax =
      LpNetwork->ucCanSMModeReqReptMax - CANSM_ONE;
  }
  else
  {
    /* Load Request Repeat time in Local variable */
    LddReqReptTime = LpNetwork->ddCanSMModeReqReptTime;

    /* Check if Request Repeat time is zero */
    if ((CanSM_TimerType)CANSM_ZERO != LddReqReptTime)
    {
      /* Decrement the Request Repeat time */
      LddReqReptTime--;

      /* Check if Request Repeat time is zero */
      if ((CanSM_TimerType)CANSM_ZERO == LddReqReptTime)
      {
        /* Load Request Repeat time in Local variable */
        LddReqReptTime = (CanSM_TimerType)CanSm_GddModeReqRepeatTime;

        /* Check if Internal Substate is CANSM_PN_CS_SLEEP_WAIT */
        if (CANSM_PN_CS_SLEEP_WAIT == LpNetwork->ucCanSMNWIntSubState)
        {
          /* Update Internal Substate as CANSM_PN_WFLAG_IN_NOT_CC_SLEEP */
          LpNetwork->ucCanSMNWIntSubState = CANSM_PN_WFLAG_IN_NOT_CC_SLEEP;
        }
        else
        {
          /* Decrement the Internal Substate by one */
          /* polyspace +1 DEFECT:SIGN_CHANGE [Not a defect: Justified] "Overflow will not occur" */
          if(CANSM_ONE <= LpNetwork->ucCanSMNWIntSubState)
          {
            LpNetwork->ucCanSMNWIntSubState =
              LpNetwork->ucCanSMNWIntSubState - CANSM_ONE;
          }
        }
        /* Decrement the counter */
        LpNetwork->ucCanSMModeReqReptMax =
          LpNetwork->ucCanSMModeReqReptMax - CANSM_ONE;
      } /* End of if ((CanSM_TimerType)CANSM_ZERO == LddReqReptTime) */

      /* Load Request Repeat time in Local variable */
      LpNetwork->ddCanSMModeReqReptTime = LddReqReptTime;
    } /* End of if ((CanSM_TimerType)CANSM_ZERO != LddReqReptTime) */
  } /* End of else */

  /* Check if Mode Request max is equal to zero */
  if (CANSM_ZERO == LpNetwork->ucCanSMModeReqReptMax)
  {
    /* AUTOEVER_CANSM_DEFINE this function is not used in HKMC ES Spec */
    /* Reset the Sub Mode to initial Mode */
    LpNetwork->ucCanSMNWIntSubState = CANSM_ZERO;

    /* Reset the Mode repetition request*/
    LpNetwork->ucCanSMModeReqReptMax = (uint8)CanSm_GucModeReqMax;

    /* Reset the Request Repetition Time */
    LpNetwork->ddCanSMModeReqReptTime =
      (CanSM_TimerType)CanSm_GddModeReqRepeatTime;
    #if (STD_ON == CANSM_DEV_ERROR_DETECT)

    /* Report to Det */
    CANSM_TIMEOUT_DET_ERROR();
    #endif
    /* AUTOEVER_CANSM_DEFINE this function is not used in HKMC ES Spec */
    /* #4509 */
    #if (STD_ON == CANSM_DEM_STATUS)   
    /* 14720 */
    if(LpStaticNetwork->ddModeEventId != CANSM_DEM_NO_EVENT){
      /* Report the error to DEM with event id and DEM_EVENT_STATUS_PASSED */
      Dem_ReportErrorStatus(LpStaticNetwork->ddModeEventId, 
                               (Dem_EventStatusType)DEM_EVENT_STATUS_PASSED);
    }
    
    if(LpStaticNetwork->ddModeEventId != CANSM_DEM_NO_EVENT){
      /* Report the error to DEM with event id and DEM_EVENT_STATUS_FAILED */
      Dem_ReportErrorStatus(LpStaticNetwork->ddModeEventId, 
                               (Dem_EventStatusType)DEM_EVENT_STATUS_FAILED);
    }
    #endif /*STD_ON == CANSM_DEM_STATUS*/    
  } /* End of if (CANSM_ZERO == LpNetwork->ucCanSMModeReqReptMax) */
} /* End of CanSM_TimeoutProcessing(NetworkHandleType LddNetworkHandle, uint8
   *LddResult) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
