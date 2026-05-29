/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.								                      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_Cbk.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
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
** 1.12.5    27-Dec-2021   SM Kwon        #33358                              **
** 1.12.3    12-Nov-2020   SM Kwon        #25247                              **
** 1.12.2    17-Jan-2020   SM Kwon        #20964                              **
** 1.12.1    22-Aug-2019   SM Kwon        #18962                              **
** 1.12.0    30-May-2019   SM Kwon        #17202                              **
** 1.11.0    23-Oct-2018   Lim Jong Sun   #14496, #14520                      **
** 1.10.3    06-Feb-2018   Lim Jong Sun   #11551, #11584                      **
** 1.10.2    23-Nov-2017   Lim Jong Sun   #10689                              **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7076                               **
** 1.9.8     25-Apr-2016   Lim Jong Sun   #4734                               **
** 1.9.7     19-Jan-2015   Lim Jong Sun   #3905                               **
** 1.9.4     07-Sep-2015   Lim Jong Sun   #2525                               **
** 1.0.4     04-Jul-2014   Lim Jong Sun   #1099                               **  
** 1.0.3     26-May-2014   Lim Jong Sun   #703                                **
** 1.0.2     26-May-2014   Lim Jong Sun   #829                                ** 
** 1.0.1     10-Jan-2014   Lim Jong Sun   #528                                **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM_Cbk.h"            /* CanSM Cbk header file */
#include "CanSM_Internal.h"       /* CanSM Main header file */
#include "CanSM_Ram.h"            /* CanSM_Ram header file */
#include "CanSM_Error.h"          /* CanSM_Error header file */
#include "BswM_CanSM.h"           /* BswM_CanSM header file */
#if (STD_ON == CANSM_PN_AVAILABILITY)
#include "CanSM_TxTimeoutException.h" /* CanSM TxTimeoutException */
#include "CanNm.h"                 /* CanNm header file */
#endif
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h"                  /* Det header file */
#endif
/*******************************************************************************
**                      Define Section                                       **
*******************************************************************************/
#define AUTOEVER_CANSM_DEFINE 1
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_CBK_C_RELEASE_MAJOR_VERSION       4
#define CANSM_CBK_C_RELEASE_MINOR_VERSION       0
#define CANSM_CBK_C_RELEASE_REVISION_VERSION    3

/* CANSM software version information */
#define CANSM_CBK_C_SW_MAJOR_VERSION            1
#define CANSM_CBK_C_SW_MINOR_VERSION            12

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_CBK_C_RELEASE_MAJOR_VERSION )
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_CBK_C_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_CBK_C_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_CBK_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_CBK_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : CanSM_ControllerBusOff                              **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : The CanSM is notified about a bus-off event on a    **
**                        certain CAN controller with this call out function. **
**                        It shall execute the bus-off recovery state machine **
**                        for the corresponding network handle.               **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : Controller                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GblInitStatus           **
**                        Function(s) invoked : Det_ReportError()             **
**                                              SchM_Enter_CanSM()            **
**                                              SchM_Exit_CanSM()             **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_ControllerBusOff(uint8 Controller)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  /*add by jslim*/
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  /* MISRA Rule    : 14.2
     Message       : This statement has no side affect
     Reason        : ConfigPtr is not used since its pre compile
     Verification  : However, part of the code is verified manually and it
                     is not having any impact.
  */
  #if ((STD_OFF == CANSM_DEV_ERROR_DETECT) && \
    (STD_ON == CANSM_SINGLE_CNTRL_CHANNEL))
  CANSM_UNUSED(Controller);
  #endif
  
  #if (STD_ON == CANSM_PN_AVAILABILITY)
  boolean LblPnSupported;
  #endif

  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  Std_ReturnType LddResult;
  LddResult = (uint8)E_OK;
  /* Check if CanSM is uninitialised */
  CANSM_INITED_DET_CHECK(LddResult, CANSMSERVICEID_CONTROLLERBUSOFF);
  
  /* Check if CanSM is greater than last controller handle */
  CANSM_CHECK_INVALID_CONTROLLER(LddResult, Controller,
    CANSMSERVICEID_CONTROLLERBUSOFF);
    
  if ((uint8)E_OK == LddResult)
  #endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {
    #if (STD_OFF == CANSM_SINGLE_NW_CHANNEL)
    /* Get the addres of the Network corresponding to the controller */
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    LpNetwork = &CanSM_GaaNetwork[CanSM_GaaInternalController[CanSm_GucSelectedConfigIdx][Controller]];
    #else
    /* Get the addres of the first Network  */
    LpNetwork = &CanSM_GaaNetwork[CANSM_ZERO];
    #endif

    #ifdef AUTOEVER_CANSM_DEFINE
    #if (STD_OFF == CANSM_SINGLE_NW_CHANNEL)
    /* Get the address of CanSM_GpStaticNw to local pointer */
    LpStaticNetwork = &CanSM_GpStaticNw
                               [CanSM_GaaInternalController[CanSm_GucSelectedConfigIdx][Controller]];
    #else
    /* Get the address of CanSM_GpStaticNw to local pointer */
    LpStaticNetwork = &CanSM_GpStaticNw[CANSM_ZERO];
    #endif
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
      /* Update the Mode status as DeInitPnNotSupported */
      LpNetwork->ucModeStatus = CANSM_DEINITPNNOTSUPPORTED;
      /* Exit Protection Area */
      SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();
      #if (STD_ON == CANSM_PN_AVAILABILITY)
   
      /* Update the local variable with Pnsupported value from Structure*/
      LblPnSupported =
        CanSM_GpStaticNw[CanSM_GaaInternalController[CanSm_GucSelectedConfigIdx][Controller]]
        .blPnSupported;
           /* Check if PN is supported */
      if ((boolean)CANSM_TRUE == LblPnSupported)
      {
        /* Enter Protection Area */
        SchM_Enter_CanSM_BUSOFF_STATUS_PROTECTION();
        /* Update the Mode status as DeInitPnSupported */
        LpNetwork->ucModeStatus = CANSM_DEINITPNSUPPORTED;
        /* Exit Protection Area */
        SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();    
        /* Initiate Partial Networking */
        CanSM_DeInitPnSupported(CanSM_GaaInternalController[CanSm_GucSelectedConfigIdx][Controller]);
      }
      else
      {
        /* Call PN not supported function */
        CanSM_DeInitPnNotSupported(CanSM_GaaInternalController[CanSm_GucSelectedConfigIdx][Controller]);
      }
      #else /* End of if (STD_ON == CANSM_PN_AVAILABILITY) */
      /* Call PN not supported function */
      /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Generated array index in range" */
      CanSM_DeInitPnNotSupported(CanSM_GaaInternalController[CanSm_GucSelectedConfigIdx][Controller]);
      #endif /* End of if (STD_ON == CANSM_PN_AVAILABILITY) */
    }
    else if (LpNetwork->ucModeStatus <= CANSM_CHECKBUSOFF)
    {
      /* Bug #703 - Add to check duplicate Bus off Event while Bus Off Recovery */
      if(LpNetwork->ucModeStatus != CANSM_BORSTART)
      {    
        /* Enter Protection Area */
        SchM_Enter_CanSM_BUSOFF_STATUS_PROTECTION();
        /* Set the BusOff status to True */
        LpNetwork->ucModeStatus = CANSM_BORSTART;
        /* Exit Protection Area */
        SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();
      }else{
        /* Enter Protection Area */
        SchM_Enter_CanSM_BUSOFF_STATUS_PROTECTION();

        LpNetwork->ucBusOffRep = CANSM_ONE;
              
        /* Exit Protection Area */
        SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();
      }
    }
    else
    {
			
    }
    #else /* Else of if (ifdef AUTOEVER_CANSM_DEFINE) */
    if (LpNetwork->ucModeStatus <= CANSM_CHECKBUSOFF)
    {
      if(LpNetwork->ucModeStatus != CANSM_BORSTART)
      {    
        /* Enter Protection Area */
        SchM_Enter_CanSM_BUSOFF_STATUS_PROTECTION();

        /* Set the BusOff status to True */
        LpNetwork->ucModeStatus = CANSM_BORSTART;

        /* Exit Protection Area */
        SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();
      }else{
        /* Enter Protection Area */
        SchM_Enter_CanSM_BUSOFF_STATUS_PROTECTION();
      
        LpNetwork->ucBusOffRep = CANSM_ONE;
                  
        /* Exit Protection Area */
        SchM_Exit_CanSM_BUSOFF_STATUS_PROTECTION();
      }
    }
    #endif /* End of if (ifdef AUTOEVER_CANSM_DEFINE) */
  }
} /* End of CanSM_ControllerBusOff(uint8 Controller) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_ConfirmPnAvailability                         **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : The CanSM is notified about the availability of     **
**                        Partial networking foa a certain CAN Transceiver    **
**                        It shall intern call the CanNm_ConfirmPnAvailability**
**                        with the related CAN network as channel to confirm  **
**                        the PN availability to the CanNm module.            **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : Transceiver                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GblInitStatus           **
**                                              CanSM_GpStaticNw              **
**                        Function(s) invoked : Det_ReportError()             **
**                                              CanNm_ConfirmPnAvailability   **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, CANSM_CODE) CanSM_ConfirmPnAvailability(uint8 Transceiver)
{
  #if (STD_ON == CANSM_PN_AVAILABILITY)
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  Std_ReturnType LddResult;
  LddResult = (uint8)E_OK;
  /* Check if CanSM is uninitialized */
  CANSM_INITED_DET_CHECK(LddResult, CANSMSERVICEID_CONFIRMPNAVAILABILTY);

  /* Det Check for invalide Transciever ID */
  /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
  CANSM_VALID_TRCV_NETWORK_CHECK(LddResult,
    Transceiver, CANSMSERVICEID_CONFIRMPNAVAILABILTY);

  if ((uint8)E_OK == LddResult)
  #endif
  {

    /* Call CanNm_ConfirmPnAvailability to confirm PN availability to CanNm */
    CanNm_ConfirmPnAvailability(CanSM_GpStaticNw
                   [CanSM_GaaStaticTrvToNw[CanSm_GucSelectedConfigIdx][Transceiver]].ucCanSmNetworkHandle);
  }
  #endif /* (STD_ON == CANSM_PN_AVAILABILITY ) */
} /* End of CanSM_ConfirmPnAvailability(uint8 Transceiver) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_TxTimeoutException                            **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : The CanSM is notified that the CanNm has detected   **
**                        for the affected partial CAN network a tx timeout   **
**                        exception.                                          **
**                        The CanSM shall recover this a transition to no     **
**                        communication and back to the requested             **
**                        communication mode again.                           **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GblInitStatus           **
**                                              CanSM_GaaNetwork              **
**                        Function(s) invoked : SchM_Enter_CanSM()            **
**                                              SchM_Exit_CanSM()             **
**                                              Det_ReportError()             **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_TxTimeoutException(NetworkHandleType Channel)
{
  #if (STD_ON == CANSM_PN_AVAILABILITY)
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  NetworkHandleType LddNetworkHandle;
  Std_ReturnType LddResult;
  LddResult = (uint8)E_OK;

  /* Check if CanSM is uninitialized */
  CANSM_INITED_DET_CHECK(LddResult, CANSMSERVICEID_TXTIMEOUTEXCEPTION);

  /* Det Check for invalide Network ID */
  CANSM_CHECK_INVALID_NETWORK(LddResult, Channel,
    CANSMSERVICEID_TXTIMEOUTEXCEPTION);

  if ((uint8)E_OK == LddResult)
  {
    /* load the internal network value from map array */
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    LddNetworkHandle = CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx][Channel];

    /* Check if network handle is Invalid */
    CANSM_CHECK_INVALID_NETWORK_HANDLE(LddResult, LddNetworkHandle,
    CANSMSERVICEID_TXTIMEOUTEXCEPTION);
  }

  if ((uint8)E_OK == LddResult)
  #endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {
    LpNetwork = &CanSM_GaaNetwork[CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx][Channel]];
    if(LpNetwork->ucModeStatus == CANSM_FULLCOMMUNICATION)
    {
      /* Enter Protection Area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* Load the mode status to the netwrok variable */
      LpNetwork->ucModeStatus = CANSM_TXTIMEOUTEXCEPTIONSERVICE;

      /* Exit Protection Area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
    }
    else
    {
      /* Do Nothing. The call of this function is only valid when it is called
         in the state 'CANSM_FULLCOMMUNICATION' */
    }
  }
#else
  CANSM_UNUSED(Channel);
#endif
} /* End of CanSM_TxTimeoutException(NetworkHandleType Channel) */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanSM_ModeIndication                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service notifies about the mode Indication.    **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : uint8 Transceiver                                   **
**                        Uint8 ServiceID                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :  CanSM_GaaNetwork             **
**                        Function(s) invoked :  SchM_Enter_CanSM()           **
**                                               SchM_Exit_CanSM()            **
**                                               Det_ReportError()            **
*******************************************************************************/
#if (STD_ON == CANSM_CANTRCV_SUPPORT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
#if (STD_OFF == CANSM_DEV_ERROR_DETECT)
FUNC(void, CANSM_CODE) CanSM_ModeIndication(uint8 Transceiver)
#else
FUNC(void, CANSM_CODE) CanSM_ModeIndication(uint8 Transceiver, uint8 ServiceID)
#endif
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;

  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  Std_ReturnType LddResult;
  LddResult = (uint8)E_OK;
  /* Check if CanSM is uninitialized  */
  CANSM_INITED_DET_CHECK(LddResult, ServiceID);

  if(LddResult == E_OK)
  {		
    /* Det Check for invalid Transciever ID */		
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    CANSM_VALID_TRCV_NETWORK_CHECK(LddResult, Transceiver, ServiceID);
  }
  
  /* Check if E_OK is returned */
  if ((uint8)E_OK == LddResult)
  #endif
  {
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Generated array index in range" */
    LpNetwork = &CanSM_GaaNetwork[CanSM_GaaStaticTrvToNw[CanSm_GucSelectedConfigIdx][Transceiver]];

    /* Enter Protection Area */
    SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

    /* clear internal mode indication  */
    /* polyspace +2 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    LpNetwork->ucCanSMNWIntSubState =
      LpNetwork->ucCanSMNWIntSubState + CANSM_ONE;

    /* Exit Protection Area */
    SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
  }
} /* End of CanSM_ModeIndication(uint8 Transceiver, uint8 ServiceID) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if(STD_ON == CANSM_CANTRCV_SUPPORT) */

/*******************************************************************************
** Function Name        : CanSM_TransceiverModeIndication                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service notifies about the mode Indication.    **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : uint8 Transceiver                                   **
**                        Uint8 ServiceID                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :  CanSM_GaaNetwork             **
**                        Function(s) invoked :  SchM_Enter_CanSM()           **
**                                               SchM_Exit_CanSM()            **
**                                               Det_ReportError()            **
*******************************************************************************/
#if (STD_ON == CANSM_CANTRCV_SUPPORT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_TransceiverModeIndication(uint8 Transceiver,
    CanTrcv_TrcvModeType TransceiverMode)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  Std_ReturnType LddResult;

  LddResult = (uint8)E_OK;
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  /* Check if CanSM is uninitialized  */
  CANSM_INITED_DET_CHECK(LddResult, CANSMSERVICEID_TRCVMODEINDICATION);

  if ((uint8)E_OK == LddResult)
  {
    /* Det Check for invalide Transciever ID */
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    CANSM_VALID_TRCV_NETWORK_CHECK(LddResult, Transceiver,
      CANSMSERVICEID_TRCVMODEINDICATION);
  }
  /* Check if E_OK is returned */
  if ((uint8)E_OK == LddResult)
  #endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Generated array index in range" */
    LpNetwork = &CanSM_GaaNetwork[CanSM_GaaStaticTrvToNw[CanSm_GucSelectedConfigIdx][Transceiver]];

    /* Check if requested mode is equal to indicated mode */
    /* polyspace<MISRA-C3:10.5 : Not a defect Justified:> Not an Impact */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    if ((uint8)TransceiverMode == LpNetwork->ucMode)
    {
      /* Enter Protection Area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* clear internal mode indication  */
      LpNetwork->ucCanSMNWIntSubState =
        LpNetwork->ucCanSMNWIntSubState + CANSM_ONE;

      /* Exit Protection Area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
    } /* End of if (LucMode == LpNetwork->ucMode) */
    else
    {
      /* Load the request Repetition Time value in the Local variable */
      LpNetwork->ddCanSMModeReqReptTime =
        (CanSM_TimerType)CanSm_GddModeReqRepeatTime;

      CanSM_TimeoutProcessing(CanSM_GaaStaticTrvToNw[CanSm_GucSelectedConfigIdx][Transceiver], LddResult);
    }
  }
} /* End of CanSM_TransceiverModeIndication(uint8 Transceiver, uint8 LucMode) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if(STD_ON == CANSM_CANTRCV_SUPPORT) */

/*******************************************************************************
** Function Name        : CanSM_ControllerModeIndication                      **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : This service notifies about the mode Indication.    **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : uint8 Controller                                    **
**                        CanIf_ControllerModeType  ControllerMode            **
**                                                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CanSM_GaaNetwork              **
**                        Function(s) invoked : SchM_Enter_CanSM()            **
**                                              SchM_Exit_CanSM()             **
**                                              Det_ReportError()             **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANSM_CODE) CanSM_ControllerModeIndication(uint8 Controller,
  CanIf_ControllerModeType                                  ControllerMode)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  Std_ReturnType LddResult;
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  uint8 LucNoOfController;
  #endif

  LddResult = (uint8)E_OK;
  #if (STD_ON == CANSM_DEV_ERROR_DETECT)

  /* Check if CanSM is uninitialized  */
  CANSM_INITED_DET_CHECK(LddResult, CANSMSERVICEID_CHECKCONTRLMODEINDICATON);
  
  /* Det Check for invalide Transciever ID */
  CANSM_CHECK_INVALID_CONTROLLER(LddResult, Controller,
    CANSMSERVICEID_CHECKCONTRLMODEINDICATON);
	
  /* Check if E_OK is returned */
  if ((uint8)E_OK == LddResult)
  #endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {    
    /* Get the addres of the Network corresponding to the controller */
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    LpNetwork = &CanSM_GaaNetwork[CanSM_GaaInternalController[CanSm_GucSelectedConfigIdx][Controller]];

    /* Check if requested mode is equal to indicated mode */
    /* polyspace<MISRA-C3:10.5 : Not a defect Justified :> Not an Impact */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    if ((uint8)ControllerMode == LpNetwork->ucMode)
    {
      #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
      /* Get the number of controller for the corresponding network */
      LucNoOfController =
        CanSM_GpStaticNw[CanSM_GaaInternalController[CanSm_GucSelectedConfigIdx][Controller]].
        ucNumberOfController;

      /* Check if number of Controller is greater than one */
      if (CANSM_ONE < LucNoOfController)
      {
        /* Increment the Controller count */
        LpNetwork->ucCanSMCtrlCount++;

        /* Check if Number of controller is equal to controller in the Network*/
        if (LucNoOfController == LpNetwork->ucCanSMCtrlCount)
        {
          /* Assign zero value to the Controller count */
          LpNetwork->ucCanSMCtrlCount = CANSM_ZERO;

          /* Enter Protection Area */
          SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

          /* Upadte the Internal Network SubState */
          LpNetwork->ucCanSMNWIntSubState =
            LpNetwork->ucCanSMNWIntSubState + CANSM_ONE;

          /* Exit Protection Area */
          SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
        } /* End of if (LucNoOfController == LpNetwork->ucCanSMCtrlCount) */
        else
        {
          
        }
      } /* End of if (CANSM_ONE < LucNoOfController) */
      else
      {
        /* Enter Protection Area */
        SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

        /* Upadte the Internal Network SubState */
        LpNetwork->ucCanSMNWIntSubState =
          LpNetwork->ucCanSMNWIntSubState + CANSM_ONE;

        /* Exit Protection Area */
        SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
      } /* End of else */
      #else /* End of if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL) */

      /* Enter Protection Area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* Upadte the Internal Network SubState */
      LpNetwork->ucCanSMNWIntSubState =
        LpNetwork->ucCanSMNWIntSubState + CANSM_ONE;

      /* Exit Protection Area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();
      #endif /* End of if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL) */
    } /* End of if (ControllerMode == LpNetwork->ucMode) */
    else
    {
      /* Load the request Repetition Time value in the Local variable */
      LpNetwork->ddCanSMModeReqReptTime =
        (CanSM_TimerType)CanSm_GddModeReqRepeatTime;
      CanSM_TimeoutProcessing(CanSM_GaaInternalController[CanSm_GucSelectedConfigIdx][Controller],
                                                                     LddResult);
    }
  }
} /* End of CanSM_ControllerModeIndication(uint8 Controller,
   *CanIf_ControllerModeType ControllerMode) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
