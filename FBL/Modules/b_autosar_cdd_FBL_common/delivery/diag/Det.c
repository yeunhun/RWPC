/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Det.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Development Error Tracer                              **
**                                                                            **
**  PURPOSE   : This file contains the API definitions for Det module         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.14.0.0  07-Apr-2021   JYS          Redmine #29231                        **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Det.h"

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
#define BTL_START_SEC_VAR_RESET_SAVE
#include "Btl_MemMap.h"

/* Global array of structure to store the development error parameters */
Det_ErrorType Fbl_Det_GaaErrors[DET_RAM_BUFFER_SIZE] = {0,};

#define BTL_STOP_SEC_VAR_RESET_SAVE
#include "Btl_MemMap.h"

#define BTL_START_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"

/* Global variable used to store index of array of structure */
uint16 Fbl_Det_GusErrorsBuffIndex;

/* Global variable to store status of Det */
boolean Det_GblInitStatus;

#define BTL_STOP_SEC_SVAR_NO_INIT
#include "Btl_MemMap.h"

/*******************************************************************************
**                        Global Function Definition                          **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
** Function Name      : Det_Init                                              **
**                                                                            **
** Service ID         : 0x00                                                  **
**                                                                            **
** Description        : This function is used to clear the logged errors and  **
**                      the reported error count.                             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :Fbl_Det_GusErrorsBuffIndex,       **
**                                          Det_GblInitStatus                 **
**                      Function(s) invoked:None                              **
*******************************************************************************/
void Det_Init(void)
{
  /* Initialize RAM buffer index */
  Fbl_Det_GusErrorsBuffIndex = DET_ZERO;

  /* Update the module init status variable */
  Det_GblInitStatus = DET_INITIALIZED;
}

/*******************************************************************************
** Function Name      : Det_ReportError                                       **
**                                                                            **
** Service ID         : 0x01                                                  **
**                                                                            **
** Description        : Development Error Tracer to report errors.            **
**                                                                            **
** Sync/Async         : Depending on implemented functionality: 1. Breakpoint **
**                      set: no return 2. Internal error counting/logging in  **
**                      RAM: synchronous 3. External error logging via        **
**                      communication interface: asynchronous                 **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : uint16 ModuleId                                       **
**                      uint8 InstanceId                                      **
**                      uint8 ApiId                                           **
**                      uint8 ErrorId                                         **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :Fbl_Det_GusErrorsBuffIndex        **
**                                          Fbl_Det_GaaErrors                 **
**                                          Det_GblInitStatus                 **
**                      Function(s) invoked:Dlt_DetForwardErrorTrace(),       **
**                                       SchM_Enter_Det_RAM_DATA_PROTECTION(),**
**                                       SchM_Exit_Det_RAM_DATA_PROTECTION()  **
*******************************************************************************/
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId,
  uint8 ApiId, uint8 ErrorId)
{
  Det_ErrorType* LpErrors;
  Std_ReturnType LddReturnVal;

  /* This API call will be always success */
  LddReturnVal = E_OK;

  if ((Det_GblInitStatus == DET_INITIALIZED)
      && (Fbl_Det_GusErrorsBuffIndex < DET_RAM_BUFFER_SIZE)
     )
  {
    /* Get a pointer to point global structure Fbl_Det_GaaErrors */
    LpErrors = &Fbl_Det_GaaErrors[Fbl_Det_GusErrorsBuffIndex];

    /* Store development error parameter got through Det_ReportError function */
    LpErrors->usModuleId = ModuleId;
    LpErrors->ucInstanceId = InstanceId;
    LpErrors->ucApiId = ApiId;
    LpErrors->ucErrorId = ErrorId;

    /* Increment array of structure index */
    Fbl_Det_GusErrorsBuffIndex++;

    if (Fbl_Det_GusErrorsBuffIndex >= DET_RAM_BUFFER_SIZE)
    {
      /* Initialize array of structure index */
      Fbl_Det_GusErrorsBuffIndex = DET_ZERO;
    }
    else
    {
      /* To avoid QAC warning */
    }
  }
  else
  {
    /* To avoid QAC warning */
  }

  return (LddReturnVal);
}

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
