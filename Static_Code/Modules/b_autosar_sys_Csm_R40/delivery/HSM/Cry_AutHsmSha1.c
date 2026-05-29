/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmSha1.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM Sha1 Interface                      **
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
** 1.0.2     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.1     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM Sha1 */
#include "Cry_AutHsmSha1.h"
/* Hash Interface */
#if (CSM_HASH_STATUS == STD_ON)
#if (CSM_HASH_AUTHSMSHA1 == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSM Sha1 Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  uint8* pResultPtr;
  uint32* pResultLengthPtr;
  boolean blTruncationIsAllowed;
} Cry_AutHsmSha1TransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Global structure variable for HSM Sha1 transfer buffer */
static Cry_AutHsmSha1TransferBuffer Cry_GddAutHsmSha1Tb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmSha1Callback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmSha1Init                                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Sha1 module.             **
**                      All the Global variables will be initialized after    **
**                      the successful completion of this API.                **
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
**                      Cry_GddAutHsmSha1Tb                                   **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmSha1Init(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmSha1Tb.ucJobState = NO_JOB;
  Cry_GddAutHsmSha1Tb.pDataPtr = NULL_PTR;
  Cry_GddAutHsmSha1Tb.ulDataLength = CSM_ZERO;
  Cry_GddAutHsmSha1Tb.pResultPtr = NULL_PTR;
  Cry_GddAutHsmSha1Tb.pResultLengthPtr = NULL_PTR;
  Cry_GddAutHsmSha1Tb.blTruncationIsAllowed = CSM_FALSE;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmSha1Start                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM Sha1, so that Sha1 is            **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmSha1MainFunction() can process            **
**                        initialisation                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgPtr                                              **
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
**                        Cry_GddAutHsmSha1Tb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmSha1Init,                                 **
**                        Csm_HashServiceHasCallback,                         **
**                        Hsm_Sha1Init                                        **
*******************************************************************************/
Std_ReturnType Cry_AutHsmSha1Start(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmSha1Tb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmSha1Init();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmSha1Tb.ucJobState = JOB_START;

    LblAsync = Csm_HashServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_Sha1Init(LblAsync, NULL_PTR);

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmSha1Tb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmSha1Tb.ucJobState = NO_JOB;
      }
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
** Function Name        : Cry_AutHsmSha1Update                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha1     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmSha1MainFunction() can process the        **
**                        input                                               **
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
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmSha1Tb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_HashServiceHasCallback,                         **
**                        Hsm_Sha1Update                                      **
*******************************************************************************/
Std_ReturnType Cry_AutHsmSha1Update(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddAutHsmSha1Tb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmSha1Tb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_HashServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_Sha1Update(LblAsync, NULL_PTR, dataPtr, dataLength);

      if (LddErr == HSM_NO_ERROR)
      {
        /* Set the job state to JOB_DONE */
        Cry_GddAutHsmSha1Tb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* Set the job state to NO_JOB */
        Cry_GddAutHsmSha1Tb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmSha1Tb.pDataPtr = dataPtr;
      Cry_GddAutHsmSha1Tb.ulDataLength = dataLength;
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
** Function Name        : Cry_AutHsmSha1Finish                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Sha1    **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmSha1MainFunction() can finish the         **
**                        computation and store the result in the memory      **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, TruncationIsAllowed                          **
**                                                                            **
** InOut parameter      : resultLengthPtr                                     **
**                                                                            **
** Output Parameters    : resultPtr                                           **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_BUSY: service state is already "active"       **
**                        CSM_E_SMALL_BUFFER: provided buffer is too small to **
**                                            store the result                **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmSha1Tb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_HashServiceHasCallback,                         **
**                        Hsm_Sha1Finish                                      **
*******************************************************************************/
Std_ReturnType Cry_AutHsmSha1Finish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutHsmSha1Tb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmSha1Tb.ucJobState = JOB_FINISH;

    LblAsync = Csm_HashServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < HAE_SHA160_DIGEST_SIZE)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }
      else
      {
        *resultLengthPtr = (*resultLengthPtr < HAE_SHA160_DIGEST_SIZE)
          ? (*resultLengthPtr) : HAE_SHA160_DIGEST_SIZE;

        LddErr = Hsm_Sha1Finish(LblAsync, NULL_PTR, resultPtr, *resultLengthPtr);

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmSha1Tb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmSha1Tb.pResultPtr = resultPtr;
      Cry_GddAutHsmSha1Tb.pResultLengthPtr = resultLengthPtr;
      Cry_GddAutHsmSha1Tb.blTruncationIsAllowed = TruncationIsAllowed;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmSha1Callback                              **
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
**                        Cry_GddAutHsmSha1Tb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_HashCallbackNotification,                       **
**                        Csm_HashServiceFinishNotification                   **
*******************************************************************************/
static void Cry_AutHsmSha1Callback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_HashCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmSha1Tb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmSha1Tb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmSha1Tb.ucJobState = NO_JOB;
      }
      Csm_HashCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmSha1Tb.ucJobState = NO_JOB;
      Csm_HashCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_HashServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmSha1MainFunction                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_HashCallbackNotification()                      **
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
** Preconditions        : Primitive should have been initialized              **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Cry_GddAutHsmSha1Tb                                 **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Hsm_Sha1Init, Hsm_Sha1Update, Hsm_Sha1Finish,       **
**                        Csm_HashCallbackNotification,                       **
**                        Csm_HashServiceFinishNotification                   **
*******************************************************************************/
void Cry_AutHsmSha1MainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmSha1Callback;

  switch (Cry_GddAutHsmSha1Tb.ucJobState)
  {
  case JOB_START:
    LddErr = Hsm_Sha1Init(CSM_TRUE, LpCallback);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmSha1Tb.ucJobState = NO_JOB;

      /* Callback notification will be invoking the application callback */
      Csm_HashCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    LddErr = Hsm_Sha1Update(CSM_TRUE, LpCallback,
      Cry_GddAutHsmSha1Tb.pDataPtr, Cry_GddAutHsmSha1Tb.ulDataLength);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmSha1Tb.ucJobState = NO_JOB;

      /* Callback notification will be invoking the application callback */
      Csm_HashCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((*(Cry_GddAutHsmSha1Tb.pResultLengthPtr) < HAE_SHA160_DIGEST_SIZE)
      && (Cry_GddAutHsmSha1Tb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }
    else
    {
      /* polyspace +3 MISRA-C3:12.1 [Justified:Low] "No Impact of this rule violation" */
      *(Cry_GddAutHsmSha1Tb.pResultLengthPtr)
        = *(Cry_GddAutHsmSha1Tb.pResultLengthPtr) < HAE_SHA160_DIGEST_SIZE
        ? *(Cry_GddAutHsmSha1Tb.pResultLengthPtr) : HAE_SHA160_DIGEST_SIZE;

      LddErr = Hsm_Sha1Finish(CSM_TRUE, LpCallback,
        Cry_GddAutHsmSha1Tb.pResultPtr,
        *(Cry_GddAutHsmSha1Tb.pResultLengthPtr));

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutHsmSha1Tb.ucJobState = NO_JOB;

      /* Callback notification will be invoking the application callback */
      Csm_HashCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_HashServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_HASH_AUTHSMSHA1 == STD_ON) */
#endif /* (CSM_HASH_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
