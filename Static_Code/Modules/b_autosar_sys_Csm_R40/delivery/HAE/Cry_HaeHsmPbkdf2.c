/*******************************************************************************
**                                                                            **
**  (C) 2017~2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmPbkdf2.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM Pbkdf2 Interface                    **
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
** 2.6.3.0   24-Mar-2021   TamTV6       Redmine #18165                        **
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.0.1     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.0     25-Mar-2020   YoungJin Yun Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM Pbkdf2 */
#include "Cry_HaeHsmPbkdf2.h"
/* Key Derive Interface */
#if (CSM_KEY_DERIVATION_STATUS == STD_ON)
#if (CSM_KEYDERIVE_HAEHSMPBKDF2 == STD_ON)
#include "HSM_Hae.h"
#include "Csm_Cbk.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_Pbkdf2.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#define CSM_JOB_INITIAL       (E_NOT_OK + 1U)
#define CSM_JOB_PENDING       (E_NOT_OK + 2U)


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSM Pbkdf2 Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  uint32 ulKeyID;
  uint32 ulIterations;
  const uint8* pPasswordPtr;
  uint32 pPasswordLength;
  const uint8* pSaltPtr;
  uint32 ulSaltLength;
  Csm_SymKeyType* pKeyPtr;
  Std_ReturnType ucJobSubState;
  uint32 ulTimeOut;
} Cry_HaeHsmPbkdf2TransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HSMAPI_CTX_t Cry_GddHaeHsmPbkdf2Context;

/* Global structure variable for HSM Pbkdf2 transfer buffer */
static Cry_HaeHsmPbkdf2TransferBuffer Cry_GddHaeHsmPbkdf2Tb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/

static Std_ReturnType Cry_InternalHaeHsmPbkdf2Finish(Std_ReturnType JobStatus);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmPbkdf2Init                                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Pbkdf2 module.           **
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
**                      Cry_GddHaeHsmPbkdf2Tb                                 **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmPbkdf2Init(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHsmPbkdf2Tb.ucJobState = NO_JOB;
  Cry_GddHaeHsmPbkdf2Tb.ulKeyID = CSM_ZERO;
  Cry_GddHaeHsmPbkdf2Tb.ulIterations = CSM_ZERO;
  Cry_GddHaeHsmPbkdf2Tb.pPasswordPtr = NULL_PTR;
  Cry_GddHaeHsmPbkdf2Tb.pPasswordLength = CSM_ZERO;
  Cry_GddHaeHsmPbkdf2Tb.pSaltPtr = NULL_PTR;
  Cry_GddHaeHsmPbkdf2Tb.ulSaltLength = CSM_ZERO;
  Cry_GddHaeHsmPbkdf2Tb.ucJobSubState = CSM_JOB_INITIAL;
  Cry_GddHaeHsmPbkdf2Tb.ulTimeOut = 0U;

  (void)memset((void*)&Cry_GddHaeHsmPbkdf2Context, 0x00,
    sizeof(HSMAPI_CTX_t));
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmPbkdf2Start                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM Pbkdf2, so that Pbkdf2 is        **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmPbkdf2MainFunction() can process          **
**                        initialisation                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgPtr, keyLength, iterations                       **
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
**                        Cry_GddHaeHsmPbkdf2Tb                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeHsmPbkdf2Init,                               **
**                        Csm_KeyDeriveServiceHasCallback,                    **
**                        Csm_KeyDeriveCallbackNotification,                  **
**                        Hsm_Pbkdf2Init                                      **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPbkdf2Start(const void* cfgPtr, uint32 keyLength,
  uint32 iterations)
{
  Std_ReturnType LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmPbkdf2Tb.ucJobState)
  {
    Cry_HaeHsmPbkdf2Init();

    if (iterations == CSM_ZERO)
    {
      LddReturnValue = E_NOT_OK;
      /* Cry_GddHaeHsmPbkdf2Tb.ucJobState = NO_JOB; */
    }
    else
    {
      if (Csm_KeyDeriveServiceHasCallback() == FALSE)
      {
        if (E_OK != HSM_Pbkdf2Start(&Cry_GddHaeHsmPbkdf2Context, (uint16)keyLength))
        {
          Cry_GddHaeHsmPbkdf2Tb.ucJobState = NO_JOB;

          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
        else
        {
          Cry_GddHaeHsmPbkdf2Tb.ucJobState = JOB_DONE;
        }
      }
      else
      {
        Cry_GddHaeHsmPbkdf2Tb.ucJobState = JOB_START;
      }
      /* Save KeyId regardless of async and sync */
      Cry_GddHaeHsmPbkdf2Tb.ulKeyID = keyLength;
      Cry_GddHaeHsmPbkdf2Tb.ulIterations = iterations;
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
** Function Name        : Cry_HaeHsmPbkdf2Update                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Pbkdf2   **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmPbkdf2MainFunction() can process the      **
**                        input                                               **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, passwordPtr, passwordLength, saltPtr,        **
**                        saltLength                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddHaeHsmPbkdf2Tb                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_KeyDeriveServiceHasCallback,                    **
**                        Csm_KeyDeriveCallbackNotification,                  **
**                        Hsm_Pbkdf2Update                                    **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPbkdf2Update(Csm_ConfigIdType cfgId,
  const uint8* passwordPtr, uint32 passwordLength, const uint8* saltPtr,
  uint32 saltLength)
{
  Std_ReturnType LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmPbkdf2Tb.ucJobState)
  {
    /* if Key is zero, password should be used */
    if (Cry_GddHaeHsmPbkdf2Tb.ulKeyID == 0U)
    {
      if ((passwordPtr == NULL_PTR) || (passwordLength == CSM_ZERO))
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      if (Csm_KeyDeriveServiceHasCallback() == FALSE)
      {
        /* To support the Autoever HSM module in the AUTOSAR CSM,
         * perform the update function in the Finish function. */

        Cry_GddHaeHsmPbkdf2Tb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmPbkdf2Tb.ucJobState = JOB_UPDATE;
      }

      /* Save KeyId regardless of async and sync */
      Cry_GddHaeHsmPbkdf2Tb.pPasswordPtr = passwordPtr;
      Cry_GddHaeHsmPbkdf2Tb.pPasswordLength = passwordLength;
      Cry_GddHaeHsmPbkdf2Tb.pSaltPtr = saltPtr;
      Cry_GddHaeHsmPbkdf2Tb.ulSaltLength = saltLength;
    }
    else
    {
      Cry_GddHaeHsmPbkdf2Tb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeHsmPbkdf2Finish                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pbkdf2  **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmPbkdf2MainFunction() can finish the       **
**                        computation and store the result in the memory      **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : keyPtr                                              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddHaeHsmPbkdf2Tb                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_KeyDeriveServiceHasCallback,                    **
**                        Hsm_Pbkdf2Finish                                    **
*******************************************************************************/
static Std_ReturnType Cry_InternalHaeHsmPbkdf2Finish(Std_ReturnType JobStatus)
{
  Std_ReturnType LddReturnJobStatus = E_NOT_OK;

  switch(JobStatus)
  {
    case CSM_JOB_INITIAL:
      if (E_OK == HSM_Pbkdf2Update(
        &Cry_GddHaeHsmPbkdf2Context,
        (uint16)Cry_GddHaeHsmPbkdf2Tb.ulKeyID,
	/* polyspace +2 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	/* polyspace +1 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
        Cry_GddHaeHsmPbkdf2Tb.pKeyPtr->length,
        Cry_GddHaeHsmPbkdf2Tb.pPasswordPtr,
        Cry_GddHaeHsmPbkdf2Tb.pPasswordLength,
        Cry_GddHaeHsmPbkdf2Tb.pSaltPtr,
        Cry_GddHaeHsmPbkdf2Tb.ulSaltLength,
        Cry_GddHaeHsmPbkdf2Tb.ulIterations))
      {
        LddReturnJobStatus = CSM_JOB_PENDING;
      } /* else E_NOT_OK */

      break;
    case CSM_JOB_PENDING:
      Cry_GddHaeHsmPbkdf2Tb.ulTimeOut++;
      if (Cry_GddHaeHsmPbkdf2Tb.ulTimeOut >= CRYPTOLIB_HAE_HSM_TIMEOUT)
      {
        LddReturnJobStatus = E_NOT_OK;
        (void)HSM_CancelJob(Cry_GddHaeHsmPbkdf2Context.jobId);
      }
      else
      {
        Std_ReturnType LddResult;

        LddResult = HSM_WaitResp(Cry_GddHaeHsmPbkdf2Context.jobId);
        if (E_OK == LddResult)
        {
	  /* polyspace +5 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +4 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          LddResult = HSM_Pbkdf2Finish(
            &Cry_GddHaeHsmPbkdf2Context,
            Cry_GddHaeHsmPbkdf2Tb.pKeyPtr->length,
            &(Cry_GddHaeHsmPbkdf2Tb.pKeyPtr->data[0]) );

          if (E_OK != LddResult)
          {
            LddReturnJobStatus = E_NOT_OK;
          }
          else
          {
            LddReturnJobStatus = E_OK;
          }
        }
        else if (HSM_E_WAIT == LddResult)
        {
          LddReturnJobStatus = CSM_JOB_PENDING;
        }
        else
        {
          LddReturnJobStatus = E_NOT_OK;
          (void)HSM_CancelJob(Cry_GddHaeHsmPbkdf2Context.jobId);
        }
      }
      break;
    default:
      LddReturnJobStatus = E_NOT_OK;
      break;
  }

  return (LddReturnJobStatus);
}


/*******************************************************************************
** Function Name        : Cry_HaeHsmPbkdf2Finish                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pbkdf2  **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmPbkdf2MainFunction() can finish the       **
**                        computation and store the result in the memory      **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : keyPtr                                              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddHaeHsmPbkdf2Tb                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_KeyDeriveServiceHasCallback,                    **
**                        Hsm_Pbkdf2Finish                                    **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPbkdf2Finish(Csm_ConfigIdType cfgId,
  Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmPbkdf2Tb.ucJobState)
  {
    if (Csm_KeyDeriveServiceHasCallback() == FALSE)
    {
      /* polyspace +4 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (E_OK != HSM_Pbkdf2Update(
          &Cry_GddHaeHsmPbkdf2Context,
          (uint16)Cry_GddHaeHsmPbkdf2Tb.ulKeyID,
          keyPtr->length,
          Cry_GddHaeHsmPbkdf2Tb.pPasswordPtr,
          Cry_GddHaeHsmPbkdf2Tb.pPasswordLength,
          Cry_GddHaeHsmPbkdf2Tb.pSaltPtr,
          Cry_GddHaeHsmPbkdf2Tb.ulSaltLength,
          Cry_GddHaeHsmPbkdf2Tb.ulIterations))
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }
      else
      {
        uint32 LulTimeout = CSM_ZERO;
        do
        {
          LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmPbkdf2Context.jobId);
          LulTimeout++;
        } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

        if (LddReturnValue != E_OK)
        {
          (void)HSM_CancelJob(Cry_GddHaeHsmPbkdf2Context.jobId);
        }
        else
        {
          LddReturnValue = HSM_Pbkdf2Finish(
            &Cry_GddHaeHsmPbkdf2Context,
            keyPtr->length, &(keyPtr->data[0]));
        }

        if (LddReturnValue != E_OK)
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      Cry_GddHaeHsmPbkdf2Tb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHsmPbkdf2Tb.ulTimeOut = 0U;
      Cry_GddHaeHsmPbkdf2Tb.ucJobSubState = CSM_JOB_INITIAL;

      Cry_GddHaeHsmPbkdf2Tb.ucJobState = JOB_FINISH;

      Cry_GddHaeHsmPbkdf2Tb.pKeyPtr = keyPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmPbkdf2MainFunction                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_KeyDeriveCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeHsmPbkdf2Start() or                          **
**                        Cry_HaeHsmPbkdf2Update(). For                       **
**                        Cry_HaeHsmPbkdf2Finish invocation of                **
**                        Csm_KeyDeriveCallbackNotification()                 **
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
**                        Cry_GddHaeHsmPbkdf2Tb                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hsm_HmacSha160Init                                  **
**                        Hsm_HmacSha160Update                                **
**                        Hsm_HmacSha160Finish                                **
**                        Csm_KeyDeriveCallbackNotification                   **
**                        Csm_KeyDeriveServiceFinishNotification              **
*******************************************************************************/
void Cry_HaeHsmPbkdf2MainFunction(void)
{
  Std_ReturnType LddReturnValue = E_OK;

  switch (Cry_GddHaeHsmPbkdf2Tb.ucJobState)
  {
  case JOB_START:
    if (E_OK != HSM_Pbkdf2Start(
      &Cry_GddHaeHsmPbkdf2Context,
      (uint16)Cry_GddHaeHsmPbkdf2Tb.ulKeyID))
    {
      LddReturnValue = E_NOT_OK;
      /* if return is failure, set job state to NO_JOB */
      Cry_GddHaeHsmPbkdf2Tb.ucJobState = NO_JOB;

      HSM_HaeGetErrorCode();
    }
    else
    {
      Cry_GddHaeHsmPbkdf2Tb.ucJobState = JOB_DONE;
    }
    /* Notify respective Service about the completion of the task */
    Csm_KeyDeriveCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* To support the Autoever HSM module in the AUTOSAR CSM,
     * perform the update function in the Finish function. */

    Cry_GddHaeHsmPbkdf2Tb.ucJobState = JOB_DONE;

    /* Notify respective Service about the completion of the task */
    Csm_KeyDeriveCallbackNotification(LddReturnValue);

    break;

  case JOB_FINISH:
    do{
    Cry_GddHaeHsmPbkdf2Tb.ucJobSubState =
      Cry_InternalHaeHsmPbkdf2Finish(Cry_GddHaeHsmPbkdf2Tb.ucJobSubState);
    }while(CSM_JOB_PENDING == Cry_GddHaeHsmPbkdf2Tb.ucJobSubState);

    if (E_NOT_OK == Cry_GddHaeHsmPbkdf2Tb.ucJobSubState)
    {
      HSM_HaeGetErrorCode();
    }
    Cry_GddHaeHsmPbkdf2Tb.ucJobState = NO_JOB;
    Csm_KeyDeriveCallbackNotification(Cry_GddHaeHsmPbkdf2Tb.ucJobSubState);

    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_KeyDeriveServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_KEYDERIVE_HAEHSMPBKDF2 == STD_ON) */
#endif /* (CSM_KEY_DERIVATION_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
