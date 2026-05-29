/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_ModeCntrl.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of Mode Control Functionality Of the Controller     **
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
** 3.0.0    08-Nov-2021    Sj.Kim    #32882                                   **
** 2.7.5    27-May-2021    Sj.Kim    #30009                                   **
** 2.7.2    12-Jan-2021    Sj.Kim    #27560                                   **
** 2.7.1    25-Nov-2020    Sj.Kim    #26002                                   **
** 2.7.0    07-Oct-2020    Sj.Kim    #25877                                   **
** 2.6.2    15-May-2020    Sj.Kim    #23352, #21882, #23360                   **
** 2.6.0    22-Aug-2019    Js.Lim    #18384, #19016                           **
** 2.5.8    10-Jul-2019    Js.Lim    #18347                                   **
** 2.5.4    11-Oct-2017    C.Kim     #9850                                    **
** 2.5.1    23-Mar-2017    Js.Lim    #7042                                    **
** 2.5.0    06-Dec-2016    Js.Lim    #7077                                    **
** 2.1.7    12-Aug-2016    Kt.Kim    #5739                                    **
** 2.1.6    05-Mar-2016    Kt.Kim    #4337                                    **
** 2.1.5    05-Jan-2016    Kt.Kim    #3813                                    **
** 2.1.4    16-Dec-2015    Kt.Kim    Justification for RTE IDP                **
** 2.1.4    13-Jun-2015    Kt.Kim    #2724                                    **
** 2.1.3    23-May-2014    Kt.Kim    #904                                     **
** 2.1.0    30-May-2013    Kt.Kim    Lib-Build Support                        **
** 1.0.0    28-Mar-2013    Kt.Kim    Initial version                          **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"           /* CanIf header file */
#include "CanIf_Ram.h"       /* CanIf RAM header file */
#include "CanIf_PCTypes.h"   /* Pre-compile time header file */
#include "CanIf_ModeCntrl.h" /* Mode control header */
#include "SchM_CanIf.h"      /* SchM CanIf Header file */
#include "CanSM_Cbk.h"       /* CAN State Manager call back header file */
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#include "CanIf_Error.h" /* CanIf DET header file */
#endif
#if (STD_ON == CANIF_PDUR_CALLBACK)
#include "PduR.h" /* PduR header file */
#endif
#include "CanIf_UserInc.h" /* User Included CanIf Header file */
#include "CanIf_Cbk.h"     /* CanIf Callback header file */

#if (STD_ON == CANIF_IDSM_SUPPORT)
#include "IdsM_Cbk.h" /* IdsM Module header file */
#endif
#include "CanIf_Can.h"                  /* CAN Driver Module Header File */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANIF_MODECNTRL_C_AR_RELEASE_MAJOR_VERSION 4
#define CANIF_MODECNTRL_C_AR_RELEASE_MINOR_VERSION 0
#define CANIF_MODECNTRL_C_AR_RELEASE_REVISION_VERSION 3

/* File version information */
#define CANIF_MODECNTRL_C_SW_MAJOR_VERSION 3
#define CANIF_MODECNTRL_C_SW_MINOR_VERSION 0
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_MODECNTRL_AR_RELEASE_MAJOR_VERSION != \
     CANIF_MODECNTRL_C_AR_RELEASE_MAJOR_VERSION)
#error "CANIF_MODECNTRL.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_MODECNTRL_AR_RELEASE_MINOR_VERSION != \
     CANIF_MODECNTRL_C_AR_RELEASE_MINOR_VERSION)
#error "CANIF_MODECNTRL.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_MODECNTRL_AR_RELEASE_REVISION_VERSION != \
     CANIF_MODECNTRL_C_AR_RELEASE_REVISION_VERSION)
#error "CANIF_MODECNTRL.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_MODECNTRL_SW_MAJOR_VERSION != CANIF_MODECNTRL_C_SW_MAJOR_VERSION)
#error "CANIF_MODECNTRL.c : Mismatch in Software Major Version"
#endif
#if (CANIF_MODECNTRL_SW_MINOR_VERSION != CANIF_MODECNTRL_C_SW_MINOR_VERSION)
#error "CANIF_MODECNTRL.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETSetControllerMode (
                       VAR(uint8, CANIF_VAR) ControllerId,
                       VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "MemMap.h"
#if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
static FUNC(Can_ReturnType, CANIF_CODE) CanIf_SetControllerModeService (
                               VAR(uint8, CANIF_VAR) Controller,
                               VAR(Can_ControllerStateType, CANIF_VAR) CanMode);
#else
static FUNC(Can_ReturnType, CANIF_CODE) CanIf_SetControllerModeService (
                               VAR(uint8, CANIF_VAR) Controller,
                               VAR(Can_StateTransitionType, CANIF_VAR) CanMode);

#endif

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC (void, CANIF_CODE) CanIf_SetTxOrRxSts (
                      VAR(uint8, CANIF_VAR) ControllerId,
                      VAR(CanIf_PduSetModeType, CANIF_VAR) LddPduMode);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanIf_SetControllerMode                             **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service calls corresponding CAN Driver service **
**                        for changing of the CAN controller mode. It         **
**                        initiates a transition to the requested CAN         **
**                        controller mode of one or multiple CAN controllers. **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : Controller, ControllerMode                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialised.              **
**                                                                            **
** Remarks              : Global Variable(s):   CanIf_GblCanIfStatus          **
**                                              CanIf_GaaController           **
**                                              CanIf_GaaControllerConfigType **
**                                                                            **
**                        Function(s) invoked:  Det_ReportError               **
**                                              CanIf_SetControllerModeService**
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerMode(
                        VAR(uint8, CANIF_VAR) ControllerId,
                        VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode)
{
  #if (STD_ON == CANIF_TX_LPDU)
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST)
                                                             LpStaticController;
  #endif																													 
  P2CONST(CanIf_TxLpdu, AUTOMATIC, CANIF_CONST) LpTxLpdu;
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
  VAR(Can_ReturnType, CANIF_VAR) LenCanReturn;
  VAR(uint8, CANIF_VAR) LucCurrentMode;
  VAR(uint16, CANIF_VAR) LusCount;
  VAR(CanIf_ControllerModeType, CANIF_VAR) LddControllerMode = ControllerMode; 
  /* Initialize the Can Return Value with CAN_OK */
  LenCanReturn = CAN_OK;
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  LenStdRetVal = CanIf_DETSetControllerMode(ControllerId, LddControllerMode);
  /* Check if any development error occurred */
  if ((uint8)E_OK == LenStdRetVal)
  #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* Initialize the Standard Return Value with E_OK */
    LenStdRetVal = (uint8)E_OK;
    #if (STD_ON == CANIF_TX_LPDU)
    /* Get the pointer to current controller structure*/
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    LpStaticController = &CanIf_GaaControllerConfigTypeSelect[ControllerId];
    #else
    LpStaticController = &CanIf_GaaControllerConfigType[ControllerId];
    #endif
    #endif
    /* Get the pointer of current controller structure*/
    LpController = &CanIf_GaaController[ControllerId];
    /* Read the current controller mode */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */
    LucCurrentMode = LpController->ucControllerMode;
    /* Check the current and requested controller mode */
    /* polyspace +1 MISRA-C3:10.5 [Not a defect:Justified] "No Impact of this rule violation" */
    if ((CANIF_CS_SLEEP == (CanIf_ControllerModeType)LucCurrentMode) &&
        (LddControllerMode >= CANIF_CS_STARTED))
    {
      #if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
	  /* From SLEEP to STOPPED */
	  LenCanReturn = CanIf_SetControllerModeService(ControllerId, CAN_CS_STOPPED);
	  #else
      /* Invoke the CanIf_SetControllerModeService with CAN_T_WAKEUP */
      LenCanReturn = CanIf_SetControllerModeService(ControllerId, CAN_T_WAKEUP);
	  #endif
      if (CANIF_CS_STOPPED == LddControllerMode)
      {
        LddControllerMode = CANIF_CS_UNINIT;
      } /*(CANIF_CS_STOPPED == ControllerMode)*/
    }   /*if ((CANIF_CS_SLEEP == LucCurrentMode) && (...))*/
    /* Check the current and requested controller mode */
    /* polyspace +1 MISRA-C3:10.5 [Not a defect:Justified] "No Impact of this rule violation" */
    else if ((CANIF_CS_STARTED == (CanIf_ControllerModeType)LucCurrentMode) &&
             (CANIF_CS_SLEEP == LddControllerMode))
    /* Invoke the CanIf_SetControllerModeService with CAN_T_STOP */
    {
      #if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
      LenCanReturn = CanIf_SetControllerModeService(ControllerId, CAN_CS_STOPPED);
	  #else
      LenCanReturn = CanIf_SetControllerModeService(ControllerId, CAN_T_STOP);
	  #endif
    } /* ((CANIF_CS_STARTED == LucCurrentMode) && (...)) */
    else
    {
      /* To avoid qac warning */
    }

    if (CAN_OK == LenCanReturn)
    {
      switch (LddControllerMode)
      {
      /* Invoke the CanIf_SetControllerModeService with CAN_T_START */
      case CANIF_CS_STARTED:
	  	#if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
		LenCanReturn =
            CanIf_SetControllerModeService(ControllerId, CAN_CS_STARTED);
		#else
        LenCanReturn =
            CanIf_SetControllerModeService(ControllerId, CAN_T_START);
		#endif
        break;
      /*Invoke the CanIf_SetControllerModeService with CAN_T_SLEEP*/
      case CANIF_CS_SLEEP:
        #if (STD_ON == CANIF_TX_LPDU)
        /* Update Tx Gateway Buffer Status */
        LpTxLpdu = LpStaticController->pTxLpdu;
        for (LusCount = CANIF_ZERO; LusCount < LpStaticController->ddNoOfTxPdu; LusCount++)
        {
          /* polyspace +2 RTE:OBAI [Not a defect: Justified] "Pointer is not outside its bounds." */
          /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Pointer is not a NULL and valid" */
          CanIf_GaaTxPduGwStatus[LpTxLpdu->ddTxPduId] = CANIF_GW_NOCOMM;
          /* polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> Increment is used to achieve better throughput. */
          LpTxLpdu++;
        }
        #endif

		#if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
        LenCanReturn = CanIf_SetControllerModeService(ControllerId, CAN_CS_SLEEP);
        #else
		LenCanReturn = CanIf_SetControllerModeService(ControllerId, CAN_T_SLEEP);
		#endif
        /*CANIF756*/
        LpController->ucRxStatus = CANIF_RX_ENABLED;
        break;
      /*Invoke the CanIf_SetControllerModeService with CAN_T_STOP*/
      case CANIF_CS_STOPPED:
	  	#if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
        LenCanReturn =
            CanIf_SetControllerModeService(ControllerId, CAN_CS_STOPPED);
		#else
		LenCanReturn =
            CanIf_SetControllerModeService(ControllerId, CAN_T_STOP);
		#endif
        break;

      default:
        /* empty */
        break;
      }
    }
    /* If Can  driver returns CAN_NOT_OK LenStdRetVal returns E_NOT_OK */
    if (CAN_NOT_OK == LenCanReturn)
    {
      LenStdRetVal = (uint8)E_NOT_OK;
    }
  } /* End of if LenStdRetVal = E_NOT_OK */
  /* Return the E_OK or E_NOT_OK */
  return (LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : CanIf_SetBatteryVoltageMode                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service sets internal battery voltage mode     **
**                        for blocking transmit request when battery voltage  **
**                        level is abnormal.                                  **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     :  ControllerId, BatteryVolMode                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialized.              **
**                                                                            **
** Remarks              : Global Variable(s):   CanIf_GblCanIfStatus          **
**                                              CanIf_GaaController           **
**                                              CanIf_GaaControllerConfigType **
**                                                                            **
**                        Function(s) invoked:  Det_ReportError               **
*******************************************************************************/
#if (STD_ON == CANIF_CANCM_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetBatteryVoltageMode(
                                             VAR(uint8, CANIF_VAR) ControllerId,
                         VAR(CanIf_BatVolSetModeType, CANIF_VAR) BatteryVolMode)
{
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  VAR(uint8, CANIF_VAR) LucPrevVolStatus;
  VAR(uint16, CANIF_VAR) LusCount;
  P2CONST(CanIf_TxLpdu, AUTOMATIC, CANIF_CONST) LpTxLpdu;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST)
                                                             LpStaticController;
  /* Initialize the Standard Return Value with E_OK */
  LenStdRetVal = (uint8)E_OK;

#if (STD_ON == CANIF_DEV_ERROR_DETECT)

  /* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > configured memory access index */

  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_SET_PDU_MODE_SID, LenStdRetVal);
  /* Report to DET, if requested channel is more than available controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_SET_PDU_MODE_SID, LenStdRetVal);
  if ((uint8)E_OK == LenStdRetVal)
  {
    /* Get the pointer to corresponding Can Controller Config ControllerId*/
    LpController = &CanIf_GaaController[ControllerId];
    /* Report to DET, if requested controllermode is unintialized*/
    /* polyspace +1 MISRA-C3:18.1 [Not a defect:Justified] "Pointer is not outside its bounds." */	
    if ((uint8)CANIF_CS_UNINIT == LpController->ucControllerMode)
    {
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                            CANIF_SET_PDU_MODE_SID, CANIF_E_UNINIT);
      LenStdRetVal = (uint8)E_NOT_OK;
    }
  }
  if ((uint8)E_OK == LenStdRetVal)
#endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    LpController = &CanIf_GaaController[ControllerId];
    /* Disable relevant interrupts */
    SchM_Enter_CanIf_MODE_STATUS_PROTECTION();
    /* polyspace +1 MISRA-C3:18.1 [Not a defect:Justified] "Genderated array index in range" */	
    LucPrevVolStatus = LpController->ucBatVolStatus;
    if (CANIF_SET_BATVOL_CRITICAL == BatteryVolMode)
    {
      LpController->ucBatVolStatus = CANIF_TX_BAT_ERROR;
    }
    else if (CANIF_SET_BATVOL_NORMAL == BatteryVolMode)
    {
      LpController->ucBatVolStatus = CANIF_TX_BAT_NORMAL;
    }
    else
    {
      LenStdRetVal = (uint8)E_NOT_OK;
    }
#if (STD_ON == CANIF_TX_LPDU)
    /* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    LpStaticController = &CanIf_GaaControllerConfigTypeSelect[ControllerId];
    #else
    LpStaticController = &CanIf_GaaControllerConfigType[ControllerId];
    #endif  
    LpTxLpdu = LpStaticController->pTxLpdu;

    /* Update Tx Gateway Buffer Status */
    if ((LucPrevVolStatus == CANIF_TX_BAT_NORMAL) &&
        (LpController->ucBatVolStatus == CANIF_TX_BAT_ERROR))
    {
      for (LusCount = CANIF_ZERO; LusCount < LpStaticController->ddNoOfTxPdu; LusCount++)
      {
        /* polyspace +1 MISRA-C3:18.1 [Not a defect: Justified] "Pointer is not outside its bounds." */
        if (CanIf_GaaTxPduGwStatus[LpTxLpdu->ddTxPduId] != CANIF_GW_NOCOMM)
        {
          CanIf_GaaTxPduGwStatus[LpTxLpdu->ddTxPduId] = CANIF_GW_ERRVOL;
        }
        /* polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> Increment is used to achieve better throughput. */
        LpTxLpdu++;
      }
    }
    else if ((LucPrevVolStatus == CANIF_TX_BAT_ERROR) &&
             (LpController->ucBatVolStatus == CANIF_TX_BAT_NORMAL))
    {
      for (LusCount = CANIF_ZERO; LusCount < LpStaticController->ddNoOfTxPdu; LusCount++)
      {
        /* polyspace +1 MISRA-C3:18.1 [Not a defect: Justified] "Pointer is not outside its bounds." */
        if (CanIf_GaaTxPduGwStatus[LpTxLpdu->ddTxPduId] != CANIF_GW_NOCOMM)
        {
          if (LpController->ucTxStatus == CANIF_TX_DISABLED)
          {
            CanIf_GaaTxPduGwStatus[LpTxLpdu->ddTxPduId] = CANIF_GW_STOPPED;
          }
          else
          {
            CanIf_GaaTxPduGwStatus[LpTxLpdu->ddTxPduId] = CANIF_GW_NOREQUEST;
          }
        }
        /* polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> Increment is used to achieve better throughput. */
        LpTxLpdu++;
      }
    }
    else
    {
    }
/* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
/* polyspace:end<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
#endif /* (STD_ON == CANIF_TX_LPDU) */
    /* Enable relevant interrupts */
    SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
  }
  return LenStdRetVal;
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : CanIf_SetPduMode                                    **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This service sets the requested mode at all L-PDUs  **
**                        of the predefined logical PDU channel. The channel  **
**                        parameter can be derived from Controller.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : Controller, PduModeRequest                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialised.              **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_GblCanIfStatus            **
**                                            CanIf_GaaController             **
**                                            CanIf_GaaControllerConfigType   **
**                        Function(s)invoked: CanIf_ClearTxQueue              **
**                                            CanIf_SetTxOrRxSts,             **
**                                            SchM_Enter_CanIf_MODE_STATUS_   **
**                                            PROTECTION,                     **
**                                            SchM_Exit_CanIf_MODE_STATUS_    **
**                                            PROTECTION                      **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPduMode (
                            VAR(uint8, CANIF_VAR) ControllerId,
                            VAR(CanIf_PduSetModeType, CANIF_VAR) PduModeRequest)

{
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST)
                                                             LpStaticController;

  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;

  VAR(uint8, CANIF_VAR) LucTxStatus;

  /* Initialize the Standard Return Value with E_OK */
  LenStdRetVal = (uint8)E_OK;

#if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_SET_PDU_MODE_SID, LenStdRetVal);
  /* Report to DET, if requested channel is more than available controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_SET_PDU_MODE_SID, LenStdRetVal);
  if ((uint8)E_OK == LenStdRetVal)
  {
    /* Get the pointer to corresponding Can Controller Config ControllerId*/
    LpController = &CanIf_GaaController[ControllerId];
    /* Report to DET, if requested controllermode is unintialized*/    
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */
    if ((uint8)CANIF_CS_UNINIT == LpController->ucControllerMode)
    {
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,
                            CANIF_SET_PDU_MODE_SID, CANIF_E_UNINIT);
      LenStdRetVal = (uint8)E_NOT_OK;
    }
  }
  /* Report to DET, If requested channel mode state is invalid */
  CANIF_INVALID_PDU_MODE_REQ_ERROR(CANIF_SET_PDU_MODE_SID, LenStdRetVal);
  /* Polyspace Gray Code: for Checking PduModeRequest
                          As valid values of PduModeRequest are of enum type,
                          PduModeRequest can't have values other than defined
                          values. If such scenarios occurrs it will be taken
                          care by DET check  */
  /* Check if any development error occurred? */
  if ((uint8)E_OK == LenStdRetVal)
#endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* Get the pointer to corresponding Can Controller Config ControllerId*/
    LpController = &CanIf_GaaController[ControllerId];
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */	
    if ((uint8)CANIF_CS_STARTED == LpController->ucControllerMode)
    {
      /* Disable relevant interrupts */
      SchM_Enter_CanIf_MODE_STATUS_PROTECTION();
      /* Update the Rx and Tx status based on current channel status
      and controller status */
      CanIf_SetTxOrRxSts(ControllerId, PduModeRequest);
      /* Enable relevant interrupts */
      SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
#if (STD_ON == CANIF_PN_SUPPORT)
      if ((CANIF_SET_ONLINE == PduModeRequest) || (CANIF_SET_TX_ONLINE ==
                                                   PduModeRequest))
      {
        /* Check if partial networking is enabled for specific controller */
        if (CANIF_TRUE ==
        #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
            CanIf_GaaControllerConfigTypeSelect[ControllerId].blPartialNWEnabled)
        #else
            CanIf_GaaControllerConfigType[ControllerId].blPartialNWEnabled)
        #endif
        {
          /* Tx Status of controller is updated as CANIF_TX_PNENABLED */
          LpController->ucTxStatus |= CANIF_TX_PNENABLED;
        }
      }
#endif
#if (STD_ON == CANIF_TX_LPDU)
      /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
      /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      if (STD_ON == CanIf_GddPrecompOpt.ucTxBasicCanPdu)
      /* polyspace-end DEFECT:USELESS_IF [Not a defect:Medium] "The value is generated by Generator." */
      {
        /* Clear Tx queue if Tx Status is changed to offline active */
        LucTxStatus = ((LpController->ucTxStatus) & (CANIF_TX_STATUS_MASK));
        /* check the TxStatus of the controller*/
        if ((CANIF_TX_DISABLED == LucTxStatus) || (CANIF_TX_OFFLINE_ACTIVE ==
                                                   LucTxStatus))
        {
          #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
          LpStaticController = &CanIf_GaaControllerConfigTypeSelect[ControllerId];
          #else
          LpStaticController = &CanIf_GaaControllerConfigType[ControllerId];
          #endif
          /* Disabling relevant interrupts*/
          SchM_Enter_CanIf_TX_QUEUE_PROTECTION();
          /* Clear Tx queue */
          CanIf_ClearTxQueue(LpStaticController);
          /* Enabling relevant interrupts*/
          SchM_Exit_CanIf_TX_QUEUE_PROTECTION();
        }
      }
#endif
    } /* if ((uint8) CANIF_CS_STARTED == LpController->ucControllerMode)*/
  }   /*if (E_OK == LenStdRetVal)*/
  /* Return the value */
  return (LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_GetControllerMode                             **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service reports about the current status of    **
**                        the requested CAN Controller.                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : Controller                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : ControllerModePtr                                   **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialised.              **
**                                                                            **
** Remarks              : Global Variable(s)  : CanIf_GblCanIfStatus,         **
**                                              CanIf_GaaController           **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE)CanIf_GetControllerMode (
  VAR(uint8, CANIF_VAR) ControllerId,
  P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_DATA) ControllerModePtr)

{
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;

  /* Initialize the Standard Return Value with E_OK */
  LenStdRetVal = (uint8)E_OK;
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_GET_CNTRL_MODE_SID, LenStdRetVal);
  /* Report to DET, if requested channel is more than available controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_GET_CNTRL_MODE_SID, LenStdRetVal);
  /* Report to DET, if pointer is NULL */
  CANIF_NULL_PTR_ERROR(CANIF_GET_CNTRL_MODE_SID, LenStdRetVal,
                       ControllerModePtr);
  /* Check If any DET error occurred? */
  if ((uint8)E_OK == LenStdRetVal)
#endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    LpController = &CanIf_GaaController[ControllerId];

    /* polyspace +3 MISRA-C3:10.5 [Not a defect:Justified] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */
    *ControllerModePtr = (CanIf_ControllerModeType)(LpController->ucControllerMode);
  } /*if (E_OK == LenStdRetVal)*/
  /* Return the standard return value */
  return (LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_GetPduMode                                    **
**                                                                            **
** Service ID           : 0x0A                                                **
**                                                                            **
** Description          : This service reports about the current status of    **
**                        the requested Pdu channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : Controller                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : PduModePtr                                          **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialised.              **
**                                                                            **
** Remarks              : Global Variable(s)  : CanIf_GblCanIfStatus,         **
**                                              CanIf_GaaController           **
**                                                                            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE)CanIf_GetPduMode (
             VAR(uint8, CANIF_VAR) ControllerId,
             P2VAR(CanIf_PduGetModeType, AUTOMATIC, CANIF_APPL_DATA) PduModePtr)
{
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;
  VAR(uint8, CANIF_VAR) LucRxStatus;

  /* Initialize the Standard Return Value with E_OK */
  LenStdRetVal = (uint8)E_OK;
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_GET_PDU_MODE_SID, LenStdRetVal);
  /* Report to DET, if requested channel is more than available controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_GET_PDU_MODE_SID, LenStdRetVal);
  /* Report to DET, if pointer is NULL */
  CANIF_NULL_PTR_ERROR(CANIF_GET_PDU_MODE_SID, LenStdRetVal, PduModePtr);
  /* Check If any DET error occurred? */
  if ((uint8)E_OK == LenStdRetVal)
#endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* Get the pointer to corresponding Can Controller Config ControllerId*/
    LpController = &CanIf_GaaController[ControllerId];
    /* Get the Rx Status of the controller */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */
    LucRxStatus = LpController->ucRxStatus;
    /* CANIF_RX_STATUS_MASK ->0x0f */
    LucRxStatus = LucRxStatus & CANIF_RX_STATUS_MASK;
    /* polyspace<RTE: IDP : Not a defect : No Action Planned >
                                            Its boundary is pre-defined           */
    switch ((CANIF_TX_STATUS_MASK) & (LpController->ucTxStatus))
    {
      /* polyspace-begin MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */	
      /* Check the controller status for RX enabled if Tx is enabled */
    case CANIF_TX_ENABLED:
      if (CANIF_RX_ENABLED == LucRxStatus)
      {
        *PduModePtr = CANIF_GET_ONLINE;
      }
      else
      {
        *PduModePtr = CANIF_GET_TX_ONLINE;
      }
      break;
    /* Check the controller status for RX enabled Tx is disabled*/
    case CANIF_TX_DISABLED:
      if (CANIF_RX_ENABLED == LucRxStatus)
      {
        *PduModePtr = CANIF_GET_RX_ONLINE;
      }
      else
      {
        *PduModePtr = CANIF_GET_OFFLINE;
      }
      break;
    /* Check the controller status for RX enabled Tx is offline active*/
    case CANIF_TX_OFFLINE_ACTIVE:
      if (CANIF_RX_ENABLED == LucRxStatus)
      {
        *PduModePtr =
            CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE;
      }
      else
      {
        *PduModePtr = CANIF_GET_OFFLINE_ACTIVE;
      }
      break;
    default:
      /* empty */
      break;
      /* polyspace-end MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */	
      /* Polyspace Gray Code: for Default case of switch
                              As all the valid scenarios are taken care in
                              options of switch case */
    } /*switch ((CANIF_TX_STATUS_MASK) & (LpController->ucTxStatus))*/
  }   /*if (E_OK == LenStdRetVal)*/
  /* Return the standard return value */
  return (LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_SetTxOrRxSts                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This routine Sets Tx or Rx Status based on Current  **
**                        Mode Channel Status for Controller.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ControllerId, LddPduMode                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC (void, CANIF_CODE) CanIf_SetTxOrRxSts(VAR(uint8, CANIF_VAR) ControllerId,
                      VAR(CanIf_PduSetModeType, CANIF_VAR) LddPduMode)
{
  VAR(uint8, CANIF_VAR) LucPrevTxStatus;
  VAR(uint16, CANIF_VAR) LusCount;
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  P2CONST(CanIf_TxLpdu, AUTOMATIC, CANIF_CONST) LpTxLpdu;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST)
                                                             LpStaticController;

  /* Get the pointer of current controller structure*/
  LpController = &CanIf_GaaController[ControllerId];
  /* polyspace:begin<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
  #if (STD_ON == CANIF_TX_LPDU)
  LucPrevTxStatus = LpController->ucTxStatus;
  #endif
  switch (LddPduMode)
  {
  case CANIF_SET_ONLINE: /* Set Rx status to online */
    LpController->ucRxStatus = CANIF_RX_ENABLED;
    /* Set Tx status to online */
    LpController->ucTxStatus = CANIF_TX_ENABLED;
    break;

  case CANIF_SET_RX_OFFLINE: /* Set Rx Status to offline */
    LpController->ucRxStatus = CANIF_RX_DISABLED;
    break;

  case CANIF_SET_RX_ONLINE: /* Set Rx Status to online */
    LpController->ucRxStatus = CANIF_RX_ENABLED;
    break;

  case CANIF_SET_TX_OFFLINE: /* Set the Tx Status to offline */
    LpController->ucTxStatus = CANIF_TX_DISABLED;
    break;

  case CANIF_SET_TX_OFFLINE_ACTIVE: /* Set the Tx Status to offline active */
    LpController->ucTxStatus =
        CANIF_TX_OFFLINE_ACTIVE;
    break;

  case CANIF_SET_TX_ONLINE: /* Set the Tx Status to online */
    LpController->ucTxStatus = CANIF_TX_ENABLED;
    break;

  case CANIF_SET_OFFLINE: /* Set the Rx Status to offline */
    LpController->ucRxStatus = CANIF_RX_DISABLED;
    /* Set the Tx Status to offline */
    LpController->ucTxStatus = CANIF_TX_DISABLED;
    break;

  default:
    /* empty */
    break;
  } /*switch(LddPduMode)*/

  /* Update Tx Gateway Buffer Status only if voltage is normal */
#if (STD_ON == CANIF_TX_LPDU)
/* polyspace:begin<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
#if (STD_ON == CANIF_CANCM_SUPPORT)
  if (LpController->ucBatVolStatus != CANIF_TX_BAT_ERROR)
#endif
  {
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    LpStaticController = &CanIf_GaaControllerConfigTypeSelect[ControllerId];
    #else
    LpStaticController = &CanIf_GaaControllerConfigType[ControllerId];
    #endif
    LpTxLpdu = LpStaticController->pTxLpdu;
    if ((LucPrevTxStatus == CANIF_TX_ENABLED) &&
        (LpController->ucTxStatus == CANIF_TX_DISABLED))
    {
      for (LusCount = CANIF_ZERO; LusCount < LpStaticController->ddNoOfTxPdu; LusCount++)
      {
        /* polyspace +1 MISRA-C3:18.1 [Not a defect:Justified] "Genderated array index in range" */
        CanIf_GaaTxPduGwStatus[LpTxLpdu->ddTxPduId] = CANIF_GW_STOPPED;
        /* polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> Increment is used to achieve better throughput. */
        LpTxLpdu++;
      }
    }
    else if ((LucPrevTxStatus == CANIF_TX_DISABLED) &&
             (LpController->ucTxStatus == CANIF_TX_ENABLED))
    {
      for (LusCount = CANIF_ZERO; LusCount < LpStaticController->ddNoOfTxPdu; LusCount++)
      {
        /* polyspace +1 MISRA-C3:18.1 [Not a defect:Justified] "Genderated array index in range" */
        CanIf_GaaTxPduGwStatus[LpTxLpdu->ddTxPduId] = CANIF_GW_NOREQUEST;
        /* polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> Increment is used to achieve better throughput. */
        LpTxLpdu++;
      }
    }
    else
    {
    }
  }
  /* polyspace:end<RTE: IDP : Not a defect : No Action Planned > configured memory access index */
  /* polyspace:end<RTE: OBAI : Not a defect : No Action Planned > range is pre-defined */
#endif /* (STD_ON == CANIF_TX_LPDU) */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_ControllerModeIndication                      **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : This service indicates a controller state transition**
**                        referring to the corresponding CAN controller       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ControllerId, ControllerMode                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : CanIf_GaaControllerConfigType, **
**                                             CanIf_GblCanIfStatus,          **
**                                             CanIf_GaaController            **
**                        Function(s) invoked: SchM_Exit_CanIf_MODE_STATUS_   **
**                                             PROTECTION,                    **
**                                             CanSM_ControllerModeIndication **
**                                             CanIf_ClearTxQueue,            **
**                                             SchM_Enter_CanIf_MODE_STATUS_  **
**                                             PROTECTION,                    **
**                                             IdsM_ControllerModeIndication  **
*******************************************************************************/
/*
 * @Trace : SWS_CANIF_00699
 */
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ControllerModeIndication(
 VAR(uint8, CANIF_VAR) ControllerId,
#if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
 VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode
#else
 VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode
#endif
    )
{
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST)
                                                             LpStaticController;
  P2VAR(CanIf_Controller, AUTOMATIC, CANIF_VAR) LpController;
  VAR(uint8, CANIF_VAR) LucPrevTxStatus;
  VAR(uint16, CANIF_VAR) LusCount;
  P2CONST(CanIf_TxLpdu, AUTOMATIC, CANIF_CONST) LpTxLpdu;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;

  /* Initialize the Standard Return Value with E_OK */
  LenStdRetVal = (uint8)E_OK;
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CTRL_MODE_IND_SID, LenStdRetVal);
  /* Report to DET, if requested channel is more than available controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_CTRL_MODE_IND_SID, LenStdRetVal);
  /* Report to DET, if requested controller mode is invalid */
  CANIF_INVALID_CONTROLLER_MODE_ERROR(CANIF_CTRL_MODE_IND_SID, LenStdRetVal);
  /* Check If any DET error occurred? */
  if ((uint8)E_OK == LenStdRetVal)
#endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* Get the pointer to corresponding Can Controller Config ControllerId*/
    /* polyspace<MISRA-C:18.1:Not a defect:Justify with annotations> Pointer is not outside its bounds - Pointer is generated by Generator*/
    LpController = &CanIf_GaaController[ControllerId];
    /* Enable relevant interrupts */
    SchM_Enter_CanIf_MODE_STATUS_PROTECTION();
    /* Store the requested mode */
    /* polyspace +1 MISRA-C3:18.1, RTE:IDP [Not a defect:Justified] "Genderated array index in range" */
    LpController->ucControllerMode = (uint8)ControllerMode;
    /* Check whether current mode is started or not */
    #if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
    if (ControllerMode != CAN_CS_STARTED)
    #else
    if (ControllerMode != CANIF_CS_STARTED)
    #endif
      {
        /* Put the channel state of offline state */
        LpController->ucRxStatus = CANIF_RX_DISABLED;
        LpController->ucTxStatus = CANIF_TX_DISABLED;

#if (CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
        /* polyspace-begin MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
        CanIf_GaaTxMsgCnt[ControllerId] = CANIF_ZERO;
        CanIf_GaaRxMsgCnt[ControllerId] = CANIF_ZERO;
        /* polyspace-end MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
#endif

#if (STD_ON == CANIF_TX_LPDU)
      /* polyspace +1 MISRA-C3:2.1,14.3, DEFECT:DEAD_CODE [Not a defect: Justified] "Condition will be executed based on the configured values" */
      if ((STD_ON == CanIf_GddPrecompOpt.ucTxBasicCanPdu) &&
      #if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
          (ControllerMode == CAN_CS_STOPPED)
      #else
          (ControllerMode == CANIF_CS_STOPPED)
      #endif
         )
      {
        /* Get the pointer to corresponding Can Controller structure */
        #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
        LpStaticController = &CanIf_GaaControllerConfigTypeSelect[ControllerId];
        #else
        LpStaticController = &CanIf_GaaControllerConfigType[ControllerId];
        #endif
        /* Disabling relevant interrupts*/
        SchM_Enter_CanIf_TX_QUEUE_PROTECTION();
        /* Clear Tx queue */
        CanIf_ClearTxQueue(LpStaticController);
        /* Enabling relevant interrupts*/
        SchM_Exit_CanIf_TX_QUEUE_PROTECTION();
      }
#endif
      }
      else
      {
#if (STD_ON == CANIF_TX_LPDU)
        LucPrevTxStatus = LpController->ucTxStatus;
#endif
        /* Set the RxStatus of controller to enabled */
        LpController->ucRxStatus |= CANIF_RX_ENABLED;
        /* Set the txStatus of controller to enabled */
        LpController->ucTxStatus = CANIF_TX_ENABLED;
#if (STD_ON == CANIF_TX_LPDU)
#if (STD_ON == CANIF_CANCM_SUPPORT)
        if (LpController->ucBatVolStatus != CANIF_TX_BAT_ERROR)
#endif
        {
          if (LucPrevTxStatus == CANIF_TX_DISABLED) /*Improvement #7077 - Delete Condition */
          {
            #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
            LpStaticController = &CanIf_GaaControllerConfigTypeSelect[ControllerId];
            #else
            LpStaticController = &CanIf_GaaControllerConfigType[ControllerId];
            #endif
            LpTxLpdu = LpStaticController->pTxLpdu;
            for (LusCount = CANIF_ZERO; LusCount < LpStaticController->ddNoOfTxPdu; LusCount++)
            {
              /* polyspace-begin MISRA-C3:18.1, RTE:IDP [Not a defect: Justified] "Pointer is not a NULL and valid" */
              /* polyspace +1 RTE:OBAI [Not a defect: Justified] "Pointer is not outside its bounds." */
              CanIf_GaaTxPduGwStatus[LpTxLpdu->ddTxPduId] = CANIF_GW_NOREQUEST;
              /* polyspace<MISRA-C:17.4:Not a defect:Justify with annotations> Increment is used to achieve better throughput. */
              LpTxLpdu++;
            }
          }
        }
#endif /* (STD_ON == CANIF_TX_LPDU) */
      }    
    /* Disable relevant interrupts */
    SchM_Exit_CanIf_MODE_STATUS_PROTECTION();
#if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
    /* Invoke CanSM/Cdd_ControllerModIndication */
    CANIF_DISPATCH_USERCTRLMODEINDICATION_NAME(
          ControllerId, (Can_ControllerStateType) ControllerMode);
#if (STD_ON == CANIF_IDSM_SUPPORT)
    IdsM_ControllerModeIndication(
         ControllerId, (Can_ControllerStateType)ControllerMode);
#endif
#else
    /* Invoke CanSM/Cdd_ControllerModIndication */
    CANIF_DISPATCH_USERCTRLMODEINDICATION_NAME(
          ControllerId, (CanIf_ControllerModeType)ControllerMode);
#if (STD_ON == CANIF_IDSM_SUPPORT)
    IdsM_ControllerModeIndication(
         ControllerId, (CanIf_ControllerModeType)ControllerMode);
#endif
#endif

  } /* if ((uint8)E_OK == LenStdRetVal) */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_DETSetControllerMode                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for DET checks in the          **
**                        CanIf_SetControllerMOde API                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ControllerId, ControllerMode                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Can_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The CAN Interface must be initialised.              **
**                                                                            **
** Remarks              : Global Variable(s):  None                           **
**                                                                            **
**                        Function(s) invoked: CanIf_SetControllerModeService **
*******************************************************************************/
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETSetControllerMode(
    VAR(uint8, CANIF_VAR) ControllerId,
    VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode)
{
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;

  LenStdRetVal = (uint8)E_OK;
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_SET_CNTRL_MODE_SID, LenStdRetVal);
  /* Report to DET, if requested controller Id is more than available
  controller */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_SET_CNTRL_MODE_SID, LenStdRetVal);
  /* Report to DET, if requested controller mode is invalid */
  CANIF_INVALID_CONTROLLER_MODE_ERROR(CANIF_SET_CNTRL_MODE_SID, LenStdRetVal);
  /* Check if any development error occurred */
  return (LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : CanIf_SetControllerModeService                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to invoke the                 **
**                        Can_SetControllerMode                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : Controller, CanMode                                 **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanIf_Init() should be invoked                      **
**                                                                            **
** Remarks              : Global Variable(s): CanIf_GaaCanDriver              **
**                                            CanIf_GaaControllerConfigType   **
**                                                                            **
**                        Function(s) invoked: Can_SetControllerMode          **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
#if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_440)
static FUNC(Can_ReturnType, CANIF_CODE) CanIf_SetControllerModeService(
    VAR(uint8, CANIF_VAR) Controller,
    VAR(Can_ControllerStateType, CANIF_VAR) CanMode)
#else
static FUNC(Can_ReturnType, CANIF_CODE) CanIf_SetControllerModeService(
    VAR(uint8, CANIF_VAR) Controller,
    VAR(Can_StateTransitionType, CANIF_VAR) CanMode)
#endif

{
  VAR(Can_ReturnType, CANIF_VAR) LenDrvRetVal;
#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  P2CONST(CanIf_CanDriver, AUTOMATIC, CANIF_CONST) LpDriver;
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST)
                                                            LpStaticController;
  #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)         
  LpStaticController = &CanIf_GaaControllerConfigTypeSelect[Controller];
  #else                                                 
  LpStaticController = &CanIf_GaaControllerConfigType[Controller];
  #endif
  /* Get the pointer to corresponding Can Driver structure */
  LpDriver = &CanIf_GaaCanDriver[LpStaticController->ucCanDriverId];
  /* Invoke the function to set the controller mode for Can Driver*/
  LenDrvRetVal = LpDriver->pCanSetControllerMode(CAN_CONTROLLER_ID(Controller), CanMode);
#else
  /* Invoke the function to set the controller mode for Can Driver*/
  LenDrvRetVal = Can_SetControllerMode(CAN_CONTROLLER_ID(Controller), CanMode);
#endif
  return (LenDrvRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanIf_ReadBusMsgCount                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall provide Tx/Rx Message Counts of  **
**                        CAN Channel.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : Controller                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : MsgCnt                                              **
**                                                                            **
** Preconditions        : CanIf_Init() should be invoked                      **
**                                                                            **
** Remarks              : None                                                **
*******************************************************************************/
#if (CANIF_BUSLOAD_DETECTING_SUPPORT == STD_ON)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ReadBusMsgCount(VAR(uint8, CANIF_VAR) Controller,
                      P2VAR(CanIf_MsgType, AUTOMATIC, CANIF_APPL_DATA) MsgCnt)
{
  /* polyspace-begin MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
  /* polyspace +1 RTE:OBAI [Not a defect: Justified] "Pointer is not outside its bounds." */
  MsgCnt->usTxMsgCnt = CanIf_GaaTxMsgCnt[Controller];
  MsgCnt->usRxMsgCnt = CanIf_GaaRxMsgCnt[Controller];
  /* polyspace-end MISRA-C3:D4.14 [Not a defect: Justified] "Pointer is not a NULL and valid" */
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
