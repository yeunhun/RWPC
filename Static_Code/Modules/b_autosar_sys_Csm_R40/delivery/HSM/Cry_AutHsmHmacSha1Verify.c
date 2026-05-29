/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmHmacSha1Verify.c                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM HMAC SHA1 Verify Interface          **
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
** 1.0.1     01-Sep-2017   Sinil        Redmine #14638                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM HMAC SHA1 Verify */
#include "Cry_AutHsmHmacSha1Verify.h"
/* Mac Interface */
#if (CSM_MAC_VERIFY_STATUS == STD_ON)
#if (CSM_MAC_AUTHSMHMACSHA1VERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSMHmacSha1Verify Transfer buffer*/
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
} Cry_AutHsmHmacSha1VerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Global variable for HSM HMAC SHA1 transfer buffer structure */
static Cry_AutHsmHmacSha1VerifyTransferBuffer Cry_GddAutHsmHmacSha1VerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmHmacSha1VerifyCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmHmacSha1VerifyInit                          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the HSM HMAC SHA1            **
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
**                      Cry_GddAutHsmHmacSha1VerifyTb                         **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmHmacSha1VerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = NO_JOB;
  Cry_GddAutHsmHmacSha1VerifyTb.pKeyPtr = NULL_PTR;
  Cry_GddAutHsmHmacSha1VerifyTb.pDataPtr = NULL_PTR;
  Cry_GddAutHsmHmacSha1VerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddAutHsmHmacSha1VerifyTb.pMacPtr = NULL_PTR;
  Cry_GddAutHsmHmacSha1VerifyTb.ulMacLength = CSM_ZERO;
  Cry_GddAutHsmHmacSha1VerifyTb.pResultPtr = NULL_PTR;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmHmacSha1VerifyStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM HMAC SHA1, so that if is         **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmHmacSha1VerifyMainFunction() can process  **
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
**                        Cry_GddAutHsmHmacSha1VerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmHmacSha1VerifyInit,                       **
**                        Csm_MacVerifyServiceHasCallback,                    **
**                        Hsm_HmacSha160Init                                  **
*******************************************************************************/
Std_ReturnType Cry_AutHsmHmacSha1VerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmHmacSha1VerifyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmHmacSha1VerifyInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = JOB_START;

    LblAsync = Csm_MacVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LddErr = Hsm_HmacSha160Init(LblAsync, NULL_PTR,
        (const uint8*)(keyPtr->data), keyPtr->length, CSM_FALSE);

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmHmacSha1VerifyTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_AutHsmHmacSha1VerifyUpdate                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the HSM      **
**                        HMAC SHA1                                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmHmacSha1VerifyMainFunction() can process  **
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
**                        Cry_GddAutHsmHmacSha1VerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyServiceHasCallback,                    **
**                        Hsm_HmacSha160Update                                **
*******************************************************************************/
Std_ReturnType Cry_AutHsmHmacSha1VerifyUpdate(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddAutHsmHmacSha1VerifyTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_MacVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_HmacSha160Update(LblAsync, NULL_PTR, dataPtr, dataLength,
        CSM_FALSE);

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmHmacSha1VerifyTb.pDataPtr = dataPtr;
      Cry_GddAutHsmHmacSha1VerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_AutHsmHmacSha1VerifyFinish                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the HSM     **
**                        HMAC SHA1 computation and store the result into     **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmHmacSha1VerifyMainFunction() can finish   **
**                        the computation and store the result in the memory  **
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
**                        Cry_GddAutHsmHmacSha1VerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyServiceHasCallback,                    **
**                        Hsm_HmacSha160Finish                                **
*******************************************************************************/
Std_ReturnType Cry_AutHsmHmacSha1VerifyFinish(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddAutHsmHmacSha1VerifyTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_MacVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +2 MISRA-C3:11.8 [Justified:Low] "No Impact of this rule violation" */
      LddErr = Hsm_HmacSha160Finish(LblAsync, NULL_PTR,
        (uint8*)MacPtr, MacLength, (uint8*)resultPtr, CSM_FALSE);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmHmacSha1VerifyTb.pMacPtr = MacPtr;
      Cry_GddAutHsmHmacSha1VerifyTb.ulMacLength = MacLength;
      Cry_GddAutHsmHmacSha1VerifyTb.pResultPtr = resultPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmHmacSha1VerifyCallback                    **
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
**                        Cry_GddAutHsmHmacSha1VerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_MacVerifyCallbackNotification,                  **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
static void Cry_AutHsmHmacSha1VerifyCallback(Hsm_ErrType ddRet)
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

    switch (Cry_GddAutHsmHmacSha1VerifyTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = NO_JOB;
      }
      Csm_MacVerifyCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = NO_JOB;
      Csm_MacVerifyCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_MacVerifyServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmHmacSha1VerifyMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacVerifyCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutHsmHmacSha1VerifyStart() or                  **
**                        Cry_AutHsmHmacSha1VerifyUpdate(). For               **
**                        Cry_AutHsmHmacSha1VerifyFinish invocation of        **
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
**                        Cry_GddAutHsmHmacSha1VerifyTb                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hsm_HmacSha160Init                                  **
**                        Hsm_HmacSha160Update                                **
**                        Hsm_HmacSha160Finish                                **
**                        Csm_MacVerifyCallbackNotification                   **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
void Cry_AutHsmHmacSha1VerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmHmacSha1VerifyCallback;

  switch (Cry_GddAutHsmHmacSha1VerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    LddErr = Hsm_HmacSha160Init(CSM_TRUE, LpCallback,
      (const uint8*)(Cry_GddAutHsmHmacSha1VerifyTb.pKeyPtr->data),
      Cry_GddAutHsmHmacSha1VerifyTb.pKeyPtr->length, CSM_FALSE);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_MacVerifyCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    LddErr = Hsm_HmacSha160Update(CSM_TRUE, LpCallback,
      Cry_GddAutHsmHmacSha1VerifyTb.pDataPtr,
      Cry_GddAutHsmHmacSha1VerifyTb.ulDataLength, CSM_FALSE);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_MacVerifyCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    /* polyspace +4 MISRA-C3:11.8 [Justified:Low] "No Impact of this rule violation" */
    LddErr = Hsm_HmacSha160Finish(CSM_TRUE, LpCallback,
      (uint8*)(Cry_GddAutHsmHmacSha1VerifyTb.pMacPtr),
      Cry_GddAutHsmHmacSha1VerifyTb.ulMacLength,
      (uint8*)(Cry_GddAutHsmHmacSha1VerifyTb.pResultPtr), CSM_FALSE);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue != E_OK)
    {
      /* reset the state back to NO_JOB */
      Cry_GddAutHsmHmacSha1VerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_MAC_AUTHSMHMACSHA1VERIFY == STD_ON) */
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
