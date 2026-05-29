/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_BaudRate.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision to change the baud rate functionality               **
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
** 2.7.1    25-Nov-2020    Sj.Kim    #26002                                   **
** 2.7.0    07-Oct-2020    Sj.Kim    #25877                                   **
** 2.6.0    22-Aug-2019    Js.Lim    #18384                                   **
** 2.5.0    06-Dec-2016    Js.Lim    #7077                                    **
** 1.0.1    13-Jun-2015    Kt.Kim    Improvement #2724                        **
** 1.0.0    28-Mar-2013    Kt.Kim    Initial version                          **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"               /* CanIf header file */
#include "CanIf_BaudRate.h"               /* CanIf header file */
#include "CanIf_Ram.h"           /* CanIf RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#include "CanIf_Error.h"         /* CanIf DET header file */
#endif
#include "CanIf_Can.h"                  /* CAN Driver Module Header File */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANIF_BAUDRATE_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_BAUDRATE_C_AR_RELEASE_MINOR_VERSION    0
#define CANIF_BAUDRATE_C_AR_RELEASE_REVISION_VERSION 3

/* File version information */
#define CANIF_BAUDRATE_C_SW_MAJOR_VERSION    3
#define CANIF_BAUDRATE_C_SW_MINOR_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_BAUDRATE_AR_RELEASE_MAJOR_VERSION != \
  CANIF_BAUDRATE_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_BAUDRATE.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_BAUDRATE_AR_RELEASE_MINOR_VERSION != \
  CANIF_BAUDRATE_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_BAUDRATE.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_BAUDRATE_AR_RELEASE_REVISION_VERSION != \
  CANIF_BAUDRATE_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_BAUDRATE.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_BAUDRATE_SW_MAJOR_VERSION != CANIF_BAUDRATE_C_SW_MAJOR_VERSION)
  #error "CANIF_BAUDRATE.c : Mismatch in Software Major Version"
#endif
#if (CANIF_BAUDRATE_SW_MINOR_VERSION != CANIF_BAUDRATE_C_SW_MINOR_VERSION)
  #error "CANIF_BAUDRATE.c : Mismatch in Software Minor Version"
#endif
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanIf_CheckBaudrate                                 **
**                                                                            **
** Service ID           : 0x1c                                                **
**                                                                            **
** Description          : This service shall check, if a certain CAN          **
**                        controller supports a requested baudrate            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ControllerId, BaudRate                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanIf module must be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s)  : CanIf_GblCanIfStatus          **
**                                              CanIf_GaaControllerConfigType **
**                                              CanIf_GaaCanDriver            **
**                        Function(s) invoked : Can_CheckBaudrate()           **
**                                              Det_ReportError()             **
*******************************************************************************/
#if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_403)
#if (STD_ON == CANIF_CHANGE_BAUDRATE_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckBaudrate (
                                            VAR(uint8, CANIF_VAR) ControllerId,
                                            CONST(uint16, CANIF_CONST) Baudrate)


{
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST)
                                                             LpStaticController;
  P2CONST(CanIf_CanDriver, AUTOMATIC, CANIF_CONST) LpDriver;
  #endif

  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)

  /* Initialize the Standard Return Value with E_OK */
  LenStdRetVal = (uint8)E_OK;
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CHECK_BAUD_RATE_SID, LenStdRetVal);
  /* Report to DET, if controller ID is out of range */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_CHECK_BAUD_RATE_SID, LenStdRetVal);  /* Is any DET error invoked */
  if ((uint8)E_NOT_OK != LenStdRetVal)
  #endif/*#if (STD_ON == CANIF_DEV_ERROR_DETECT)*/
  {
    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    /* Get the pointer to corresponding Can Controller structure */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    LpStaticController = &CanIf_GaaControllerConfigTypeSelect[ControllerId];
    #else
    LpStaticController = &CanIf_GaaControllerConfigType[ControllerId];
    #endif
    /* Get the pointer to corresponding Can Driver structure */
    LpDriver = &CanIf_GaaCanDriver[LpStaticController->ucCanDriverId];
    /* Invoke the function Can_CheckBaudrate */
    LenStdRetVal = LpDriver->pCanCheckBaudrate(CAN_CONTROLLER_ID(ControllerId), Baudrate);
    #else
    /* Invoke the function Can_CheckBaudrate */
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    LenStdRetVal = Can_CheckBaudrate(CAN_CONTROLLER_ID(ControllerId), Baudrate);
    #endif/* #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT) */
  }
  return (LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/* #if (STD_ON == CANIF_CHANGE_BAUDRATE_SUPPORT) */
#endif

/*******************************************************************************
** Function Name        : CanIf_ChangeBaudrate                                **
**                                                                            **
** Service ID           : 0x1b                                                **
**                                                                            **
** Description          : This service shall change, if requested, a certain  **
**                        CAN controller supports a requested baudrate        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ControllerId, BaudRate                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanIf module must be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s)  : CanIf_GblCanIfStatus          **
**                                              CanIf_GaaControllerConfigType **
**                                              CanIf_GaaCanDriver            **
**                        Function(s) invoked : Can_ChangeBaudrate()          **
**                                              Det_ReportError()             **
*******************************************************************************/
#if (CANIF_CANDRV_VERSION_SUPPORT == CANIF_VER_403)
#if (STD_ON == CANIF_CHANGE_BAUDRATE_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ChangeBaudrate(
                                            VAR(uint8, CANIF_VAR) ControllerId,
                                            CONST(uint16, CANIF_CONST) Baudrate)
{
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST)
                                                             LpStaticController;
  P2CONST(CanIf_CanDriver, AUTOMATIC, CANIF_CONST) LpDriver;
  #endif
  VAR(Std_ReturnType, CANIF_VAR) LenStdRetVal;

  /* Initialize the Standard Return Value with E_OK */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  LenStdRetVal = (uint8)E_OK;
  /* Report to DET, if module is not initialized */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CHANGE_BAUD_RATE_SID, LenStdRetVal);
  /* Report to DET, if controller ID is out of range */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_CHANGE_BAUD_RATE_SID, LenStdRetVal);
  /* Is any DET error invoked */
  if ((uint8)E_NOT_OK != LenStdRetVal)
  #endif/* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    /* Get the pointer to corresponding Can Controller structure */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    LpStaticController = &CanIf_GaaControllerConfigTypeSelect[ControllerId];
    #else
    LpStaticController = &CanIf_GaaControllerConfigType[ControllerId];
    #endif
    /* Get the pointer to corresponding Can Driver structure */
    LpDriver = &CanIf_GaaCanDriver[LpStaticController->ucCanDriverId];
    /* Invoke the function Can_ChangeBaudrate */
    LenStdRetVal = LpDriver->pCanChangeBaudrate(CAN_CONTROLLER_ID(ControllerId), Baudrate);
    #else
    /* Invoke the function Can_ChangeBaudrate */
    /* polyspace +1 MISRA-C3:D4.14,18.1, RTE:OBAI [Not a defect:Justified] "Configuration Index is generated value based on Ecudescription" */
    LenStdRetVal = Can_ChangeBaudrate(CAN_CONTROLLER_ID(ControllerId), Baudrate);
    #endif/*#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT) */
  }/* if (E_OK == LenStdRetVal) */
  return (LenStdRetVal);
}
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/* #if (STD_ON == CANIF_CHANGE_BAUDRATE_SUPPORT) */
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
