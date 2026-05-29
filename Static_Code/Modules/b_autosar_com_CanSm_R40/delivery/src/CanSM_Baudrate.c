/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.								      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_Baudrate.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of the funtionality of CanSM_CheckBaudrate()        **
**              and CanSM_ChangeBaudrate()                                    **
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
** 1.12.3    12-Nov-2020   SM Kwon        #25247                              **
** 1.12.0    30-May-2019   SM Kwon        #17202                              **
** 1.11.0    23-Oct-2018   Lim Jong Sun   #14496                              **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7076                               **
** 1.9.8     25-Apr-2016   Lim Jong Sun   #4734                               **
** 1.9.7     19-Jan-2015   Lim Jong Sun   #3905                               **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM_InternalTypes.h"        /* CanSM PCTypes header file */
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#include "Det.h"                  /* Det header file */
#endif
#include "CanSM_Dcm.h"            /* CanSM_Dcm header */
#include "CanSM_Ram.h"            /* CanSM_Ram header file */
#include "CanSM_ComM.h"           /* CanSM_ComM header */
#include "BswM_CanSM.h"           /* BswM_CanSM header */


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_BAUDRATE_C_RELEASE_MAJOR_VERSION       4
#define CANSM_BAUDRATE_C_RELEASE_MINOR_VERSION       0
#define CANSM_BAUDRATE_C_RELEASE_REVISION_VERSION    3

/* CANSM software version information */
#define CANSM_BAUDRATE_C_SW_MAJOR_VERSION            1
#define CANSM_BAUDRATE_C_SW_MINOR_VERSION            12

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_BAUDRATE_C_RELEASE_MAJOR_VERSION )
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_BAUDRATE_C_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != \
                                      CANSM_BAUDRATE_C_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_BAUDRATE_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_BAUDRATE_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanSM_CheckBaudrate                                 **
**                                                                            **
** Service ID           : 0x0c                                                **
**                                                                            **
** Description          : This service shall check, if a certain baudrate is  **
**                        supported by the configured CAN controllers of a    **
**                        certain CAN network.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NetworkHandleType network,                          **
**                        const uint16 Baudrate                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
#if (STD_ON == CANSM_CHANGE_BAUDRATE_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_CheckBaudrate(NetworkHandleType network,
                                       CONST(uint16, CANIF_APPL_CONST) Baudrate)
{
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  #if ((STD_ON == CANSM_DEV_ERROR_DETECT) || \
       ((STD_OFF == CANSM_DEV_ERROR_DETECT) && (STD_OFF == CANSM_SINGLE_NW_CHANNEL)))
  NetworkHandleType LddNetworkHandle;	
  #endif
  
  Std_ReturnType LddResult;
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  uint8 LucNoOfController;
  uint8 LucControllerIndex;
  #endif
  #if ((STD_OFF == CANSM_DEV_ERROR_DETECT) && \
  (STD_ON == CANSM_SINGLE_CNTRL_CHANNEL))
  CANSM_UNUSED(network);
  #endif

  /* Initialize the Local variable with E_OK */
  LddResult = (Std_ReturnType)E_OK;

  #if (STD_ON == CANSM_DEV_ERROR_DETECT)

  /* Check if CanSM is greater than last network handle */
  CANSM_CHECK_INVALID_NETWORK(LddResult, network,
    CANSMSERVICEID_CHECKBAUDRATE);

  if ((Std_ReturnType)E_OK == LddResult)
  {
    /* load the internal network value from map array */
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Generated array index in range" */
    LddNetworkHandle = CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx][network];

    /* Check if network handle is Invalid */
    CANSM_CHECK_INVALID_NETWORK_HANDLE(LddResult, LddNetworkHandle,
      CANSMSERVICEID_CHECKBAUDRATE);
  }
  else
  {
    /*Nothing*/
  }
  if ((Std_ReturnType)E_OK == LddResult)
  #endif
  #if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL)
  {
    #if ((STD_OFF == CANSM_DEV_ERROR_DETECT) && (STD_OFF == CANSM_SINGLE_NW_CHANNEL)) 
    /* Load the network handle in the local variable */
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Generated array index in range" */
    LddNetworkHandle = CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx][network];
    #endif

    /* Get the address of the transition to the network map index */
    LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

    /* load the internal network value from map array */
    LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

    /* Get the controller Id */
    LucControllerIndex = LpStaticNetwork->ucControllerIndex;

    /* Get the controller Count */
    LucNoOfController = LpStaticNetwork->ucNumberOfController;

    do
    {
      /* Call the Function to check the Baudrate */
      /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect: Justified] "Generated array index in range" */
      LddResult |= CanIf_CheckBaudrate(CANSM_CNTRL_ID, Baudrate);

      /* Decrement the controller Count */
      LucNoOfController = LucNoOfController - CANSM_ONE;

      /* Increment the controller Index */
      LucControllerIndex = LucControllerIndex + CANSM_ONE;
    } while (CANSM_ZERO != LucNoOfController);

    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    LpNetwork->ucResult = (uint8)LddResult;
  } /* End of if ((Std_ReturnType)E_OK == LddResult) */

  if ((Std_ReturnType)E_OK == LddResult)
  {

    /* load the internal network value from map array */
    LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

    /* Load the Return Value in the Local variable */
    LpNetwork->usBaudrate = Baudrate;
  }
  #else /* End of if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL) */
  {
    #if((STD_OFF == CANSM_DEV_ERROR_DETECT) && (STD_OFF == CANSM_SINGLE_NW_CHANNEL))
    /* load the internal network value from map array */
    /* polyspace +1 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Generated array index in range" */
    LddNetworkHandle = CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx][network];
	#endif
	
    /* Call the Function to check the Baudrate */
    LddResult |= CanIf_CheckBaudrate(CANSM_CNTRL_ID, Baudrate);
  } /* End of if ((Std_ReturnType)E_OK == LddResult) */
  
  if ((Std_ReturnType)E_OK == LddResult)
  {

    /* load the internal network value from map array */
    LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];

    /* Load the Return Value in the Local variable */
    LpNetwork->usBaudrate = Baudrate;
  }
  #endif /* End of if (STD_OFF == CANSM_SINGLE_CNTRL_CHANNEL) */

  /* Return Lddresult */
  return (LddResult);
} /* End of CanSM_CheckBaudrate(NetworkHandleType network, const uint16
   *Baudrate) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_CHANGE_BAUDRATE_API) */

/*******************************************************************************
** Function Name        : CanSM_ChangeBaudrate                                **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : This service shall start an asynchronous process to **
**                        change the baudrate for the configured CAN          **
**                        controllers of a certain CAN network.               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NetworkHandleType network,                          **
**                        const uint16 Baudrate                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
#if (STD_ON == CANSM_CHANGE_BAUDRATE_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
/*polyspace<DEFECT:UNUSED_PARAMETER : Not a defect:Justified> It will call from upper layer*/
/*polyspace<MISRA-C3:2.7 : Not a defect:Justified> It will call from upper layer*/
FUNC(Std_ReturnType, CANSM_CODE) CanSM_ChangeBaudrate(NetworkHandleType network,
                                       CONST(uint16, CANIF_APPL_CONST) Baudrate)
{
  P2VAR(Tdd_CanSM_Network, AUTOMATIC, CANSM_VAR) LpNetwork;
  P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CANSM_CONST) LpStaticNetwork;
  NetworkHandleType LddNetworkHandle;
  Std_ReturnType LddResult;

  #if (STD_OFF == CANSM_DEV_ERROR_DETECT)
  CANSM_UNUSED(Baudrate);
  #endif

  LddResult = (Std_ReturnType)E_OK;

  #if (STD_ON == CANSM_DEV_ERROR_DETECT)
  /* Report the error to DET with CANSM_E_UNINIT */
  CANSM_INITED_DET_CHECK(LddResult, CANSMSERVICEID_CHANGEBAUDRATE);

  /* Check if CanSM is greater than last network handle */
  CANSM_CHECK_INVALID_NETWORK(LddResult, network,
      CANSMSERVICEID_CHANGEBAUDRATE);

   if ((Std_ReturnType)E_OK == LddResult)
  {
    /* load the internal network value from map array */
    /* polyspace +2 MISRA-C3:18.1, RTE:OBAI [Not a defect:Justified] "Generated array index in range" */
    #if (STD_OFF == CANSM_SINGLE_NW_CHANNEL)
    LddNetworkHandle = CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx][network];	
	
    /* Check if network handle is Invalid */
    CANSM_CHECK_INVALID_NETWORK_HANDLE(LddResult, LddNetworkHandle,
     CANSMSERVICEID_CHANGEBAUDRATE);
    #endif
    /* Get the address of CanSM_GaaNetwork to local pointer */
    LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];
		
    /* Check if Invalid baudrate is Requested */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Generated array index in range" */
    CANSM_CHECK_INVALID_BAUDRATE(LddResult, CANSMSERVICEID_CHANGEBAUDRATE);
  }
  else
  {
    /* Get the address of CanSM_GaaNetwork to local pointer */
    LpNetwork = &CanSM_GaaNetwork[CANSM_ZERO];
  }
  if ((Std_ReturnType)E_OK == LddResult)
  #endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */
  {
    /* polyspace-begin MISRA-C3:D4.14,18.1, RTE:OBAI,IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    #if (STD_OFF == CANSM_DEV_ERROR_DETECT)
    /* load the internal network value from map array */
    #if(STD_OFF == CANSM_SINGLE_NW_CHANNEL)
	LddNetworkHandle = CanSM_GaaInternalNetwork[CanSm_GucSelectedConfigIdx][network];    
    #endif
    /* Get the address of CanSM_GaaNetwork to local pointer */
    LpNetwork = &CanSM_GaaNetwork[CANSM_LDDNETWORKHANDLE];
    #endif

    if (CANSM_FULLCOMMUNICATION == LpNetwork->ucModeStatus)
    {
      /* Get the address of CanSM_GaaStaticNetwork to local pointer */
      LpStaticNetwork = &CanSM_GpStaticNw[CANSM_LDDNETWORKHANDLE];

      /* Enter Protection Area */
      SchM_Enter_CanSM_MODE_STATUS_PROTECTION();

      /* Set the mode of the CanSM to CANSM_CHECKBUSOFF state */
      LpNetwork->ucModeStatus = CANSM_CHANGEBAUDRATESERVICE;

      /* Exit Protection Area */
      SchM_Exit_CanSM_MODE_STATUS_PROTECTION();

      /* Get the current mode status */
      LpNetwork->ucCanSMNWIntSubState = CANSM_BR_CC_STOPPED;

      /* Notify internally stored network mode to the BsWM*/
      BswM_CanSM_CurrentState(LpStaticNetwork->ucCanSmNetworkHandle,
        CANSM_BSWM_CHANGE_BAUDRATE);

      /* Call the function for Baudrate Service */
      CanSM_ChangeBaudRateService(CANSM_LDDNETWORKHANDLE);
    } /* End of if (CANSM_FULLCOMMUNICATION == LpNetwork->ucModeStatus) */
    else
    {
      /* Return E_NOT_OK */
      LddResult = (Std_ReturnType)E_NOT_OK;
    }
    /* polyspace-end MISRA-C3:D4.14,18.1, RTE:OBAI,IDP [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
  }
  /* Return Lddresult */
  return (LddResult);
} /* End of CanSM_ChangeBaudrate(NetworkHandleType network, const uint16
   *Baudrate) */

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_CHANGE_BAUDRATE_API) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
