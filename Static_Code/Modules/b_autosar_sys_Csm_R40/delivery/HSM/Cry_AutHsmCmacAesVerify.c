/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmCmacAesVerify.c                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM CMAC AES Verify Interface           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.0.3     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.1     17-Apr-2018   Sinil        Redmine #12351                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM CMAC AES Verify */
#include "Cry_AutHsmCmacAesVerify.h"
/* Mac Interface */
#if (CSM_MAC_VERIFY_STATUS == STD_ON)
#if (CSM_MAC_AUTHSMCMACAESVERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSMCmacAesVerify Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  const uint8* pMacPtr;
  uint32 ulMacLength;
  Csm_VerifyResultType* pResultPtr;
} Cry_AutHsmCmacAesVerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmCmacAesVerDataType;

static Hsm_DataIDType Cry_GddAutHsmCmacAesVerDataIDType;

/* Global variable for HSM CMAC AES transfer buffer structure */
static Cry_AutHsmCmacAesVerifyTransferBuffer Cry_GddAutHsmCmacAesVerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmCmacAesVerifyCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmCmacAesVerifyInit                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the HSM CMAC AES             **
**                      module. All the Global variables will be initialized  **
**                      after the successful completion of this API.          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non-Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s):                                   **
**                      Cry_GddAutHsmCmacAesVerifyTb                          **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmCmacAesVerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmCmacAesVerifyTb.ucJobState = NO_JOB;
  Cry_GddAutHsmCmacAesVerifyTb.pKeyPtr = NULL_PTR;
  Cry_GddAutHsmCmacAesVerifyTb.pDataPtr = NULL_PTR;
  Cry_GddAutHsmCmacAesVerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddAutHsmCmacAesVerifyTb.pMacPtr = NULL_PTR;
  Cry_GddAutHsmCmacAesVerifyTb.ulMacLength = CSM_ZERO;
  Cry_GddAutHsmCmacAesVerifyTb.pResultPtr = NULL_PTR;

  Cry_GddAutHsmCmacAesVerDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmCmacAesVerDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmCmacAesVerifyStart                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM CMAC AES, so that if is          **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmCmacAesVerifyMainFunction() can process   **
**                        initialisation                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgPtr, keyPtr                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                                                                            **
** Preconditions        : CSM should have been initialized                    **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmCmacAesVerifyTb                        **
**                        Cry_GpHSMCmacAesVerifyConfigPtr                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmCmacAesVerifyInit,                        **
**                        Csm_MacVerifyServiceHasCallback,                    **
**                        Hsm_AesCmacInit                                     **
*******************************************************************************/
Std_ReturnType Cry_AutHsmCmacAesVerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmCmacAesVerifyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmCmacAesVerifyInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmCmacAesVerifyTb.ucJobState = JOB_START;

    LblAsync = Csm_MacVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        Cry_GddAutHsmCmacAesVerDataType = HSM_DATA_AES_KEY;
        Cry_GddAutHsmCmacAesVerDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        LddErr = HSM_NO_ERROR;
      }
      else if (keyPtr->length == HSM_AES_KEY_BYTE_SIZE)
      {
        Cry_GddAutHsmCmacAesVerDataType = HSM_DATA_AES_RAM_KEY;
        Cry_GddAutHsmCmacAesVerDataIDType = CSM_SEVEN;

        LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_SEVEN,
          keyPtr->length, (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_AesCmacInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmCmacAesVerDataType, Cry_GddAutHsmCmacAesVerDataIDType,
          CSM_FALSE);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmCmacAesVerifyTb.pKeyPtr = keyPtr;
    }
  }
  else
  {
    /* Other job is still processing, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmCmacAesVerifyUpdate                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the HSM      **
**                        CMAC AES                                            **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmCmacAesVerifyMainFunction() can process   **
**                        the input                                           **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, dataPtr, dataLength                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_SMALL_BUFFER: the provided buffer is too      **
**                        small to store the result                           **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmCmacAesVerifyTb                        **
**                        Cry_GpHSMCmacAesVerifyConfigPtr                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyServiceHasCallback, Hsm_AesCmacUpdate  **
*******************************************************************************/
Std_ReturnType Cry_AutHsmCmacAesVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutHsmCmacAesVerifyTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmCmacAesVerifyTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_MacVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_AesCmacUpdate(LblAsync, NULL_PTR, dataPtr, dataLength,
        CSM_FALSE);

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmCmacAesVerifyTb.pDataPtr = dataPtr;
      Cry_GddAutHsmCmacAesVerifyTb.ulDataLength = dataLength;
    }
  }
  else
  {
    /* Job process still not complete, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmCmacAesVerifyFinish                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the HSM     **
**                        CMAC AES computation and store the result into      **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmCmacAesVerifyMainFunction() can finish the**
**                        computation and store the result in the memory      **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, MacPtr, MacLength                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_SMALL_BUFFER: provided buffer is too small to **
**                                            store the result                **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmCmacAesVerifyTb                        **
**                        Cry_GpHSMCmacAesVerifyConfigPtr                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyServiceHasCallback,                    **
**                        Hsm_AesCmacFinish                                   **
*******************************************************************************/
Std_ReturnType Cry_AutHsmCmacAesVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutHsmCmacAesVerifyTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmCmacAesVerifyTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_MacVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +2 MISRA-C3:11.8 [Justified:Low] "No Impact of this rule violation" */
      LddErr = Hsm_AesCmacFinish(LblAsync, NULL_PTR,
        (uint8*)MacPtr, MacLength, (uint8*)resultPtr, CSM_FALSE);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmCmacAesVerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmCmacAesVerifyTb.pMacPtr = MacPtr;
      Cry_GddAutHsmCmacAesVerifyTb.ulMacLength = MacLength;
      Cry_GddAutHsmCmacAesVerifyTb.pResultPtr = resultPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmCmacAesVerifyCallback                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : TBD                                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmCmacAesVerifyTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyCallbackNotification,                  **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
static void Cry_AutHsmCmacAesVerifyCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_MacVerifyCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmCmacAesVerifyTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmCmacAesVerifyTb.ucJobState = NO_JOB;
      }
      Csm_MacVerifyCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmCmacAesVerifyTb.ucJobState = NO_JOB;
      Csm_MacVerifyCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_MacVerifyServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmCmacAesVerifyMainFunction                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacVerifyCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutHsmCmacAesVerifyStart() or                   **
**                        Cry_AutHsmCmacAesVerifyUpdate(). For                **
**                        Cry_AutHsmCmacAesVerifyFinish invocation of         **
**                        Csm_MacVerifyCallbackNotification()                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmCmacAesVerifyTb                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hsm_AesCmacInit                                     **
**                        Hsm_AesCmacUpdate                                   **
**                        Hsm_AesCmacFinish                                   **
**                        Csm_MacVerifyCallbackNotification                   **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
void Cry_AutHsmCmacAesVerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmCmacAesVerifyCallback;

  switch (Cry_GddAutHsmCmacAesVerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmCmacAesVerifyTb.pKeyPtr->length == CSM_ONE)
    {
      Cry_GddAutHsmCmacAesVerDataType = HSM_DATA_AES_KEY;
      Cry_GddAutHsmCmacAesVerDataIDType
        = (Hsm_DataIDType)(Cry_GddAutHsmCmacAesVerifyTb.pKeyPtr->data[0]);
      LddErr = HSM_NO_ERROR;
    }
    else if (Cry_GddAutHsmCmacAesVerifyTb.pKeyPtr->length == HSM_AES_KEY_BYTE_SIZE)
    {
      Cry_GddAutHsmCmacAesVerDataType = HSM_DATA_AES_RAM_KEY;
      Cry_GddAutHsmCmacAesVerDataIDType = CSM_SEVEN;

      LddErr = Hsm_LoadRamKey(HSM_DATA_AES_RAM_KEY, CSM_SEVEN,
        Cry_GddAutHsmCmacAesVerifyTb.pKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmCmacAesVerifyTb.pKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_AesCmacInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmCmacAesVerDataType, Cry_GddAutHsmCmacAesVerDataIDType,
        CSM_FALSE);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmCmacAesVerifyTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_MacVerifyCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    LddErr = Hsm_AesCmacUpdate(CSM_TRUE, LpCallback,
      Cry_GddAutHsmCmacAesVerifyTb.pDataPtr,
      Cry_GddAutHsmCmacAesVerifyTb.ulDataLength, CSM_FALSE);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmCmacAesVerifyTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_MacVerifyCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    /* polyspace +4 MISRA-C3:11.8 [Justified:Low] "No Impact of this rule violation" */
    LddErr = Hsm_AesCmacFinish(CSM_TRUE, LpCallback,
      (uint8*)(Cry_GddAutHsmCmacAesVerifyTb.pMacPtr),
      Cry_GddAutHsmCmacAesVerifyTb.ulMacLength,
      (uint8*)(Cry_GddAutHsmCmacAesVerifyTb.pResultPtr), CSM_FALSE);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue != E_OK)
    {
      /* reset the state back to NO_JOB */
      Cry_GddAutHsmCmacAesVerifyTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_MacVerifyCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_MacVerifyServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_MAC_AUTHSMCMACAESVERIFY == STD_ON) */
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
