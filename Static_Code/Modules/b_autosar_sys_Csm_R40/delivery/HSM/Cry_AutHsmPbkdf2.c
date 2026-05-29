/*******************************************************************************
**                                                                            **
**  (C) 2017~2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmPbkdf2.c                                            **
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
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.0.3     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.2     06-Jan-2020   Sinil        Redmine #21000                        **
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
/* Header File for HSM Pbkdf2 */
#include "Cry_AutHsmPbkdf2.h"
/* Key Derive Interface */
#if (CSM_KEY_DERIVATION_STATUS == STD_ON)
#if (CSM_KEYDERIVE_AUTHSMPBKDF2 == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

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
} Cry_AutHsmPbkdf2TransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmPbkdf2DataType;

/* Global structure variable for HSM Pbkdf2 transfer buffer */
static Cry_AutHsmPbkdf2TransferBuffer Cry_GddAutHsmPbkdf2Tb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmPbkdf2Callback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmPbkdf2Init                                  **
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
**                      Cry_GddAutHsmPbkdf2Tb                                 **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmPbkdf2Init(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmPbkdf2Tb.ucJobState = NO_JOB;
  Cry_GddAutHsmPbkdf2Tb.ulKeyID = CSM_ZERO;
  Cry_GddAutHsmPbkdf2Tb.ulIterations = CSM_ZERO;
  Cry_GddAutHsmPbkdf2Tb.pPasswordPtr = NULL_PTR;
  Cry_GddAutHsmPbkdf2Tb.pPasswordLength = CSM_ZERO;
  Cry_GddAutHsmPbkdf2Tb.pSaltPtr = NULL_PTR;
  Cry_GddAutHsmPbkdf2Tb.ulSaltLength = CSM_ZERO;

  Cry_GddAutHsmPbkdf2DataType = HSM_DATA_INVALID_KEY;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPbkdf2Start                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM Pbkdf2, so that Pbkdf2 is        **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmPbkdf2MainFunction() can process          **
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
**                        Cry_GddAutHsmPbkdf2Tb                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmPbkdf2Init,                               **
**                        Csm_KeyDeriveServiceHasCallback,                    **
**                        Csm_KeyDeriveCallbackNotification,                  **
**                        Hsm_Pbkdf2Init                                      **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPbkdf2Start(const void* cfgPtr, uint32 keyLength,
  uint32 iterations)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutHsmPbkdf2Tb.ucJobState)
  {
    Cry_AutHsmPbkdf2Init();

    Cry_GddAutHsmPbkdf2Tb.ucJobState = JOB_START;

    LblAsync = Csm_KeyDeriveServiceHasCallback();

    if (LblAsync == FALSE)
    {
      if (iterations == CSM_ZERO)
      {
        LddErr = HSM_PARAMETER_ERROR;
      }
      else
      {
        if (keyLength == CSM_ZERO)
        {
          Cry_GddAutHsmPbkdf2DataType = HSM_DATA_AES_RAM_KEY;
        }
        else
        {
          Cry_GddAutHsmPbkdf2DataType = HSM_DATA_AES_KEY;
        }

        LddErr = HSM_NO_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_Pbkdf2Init(LblAsync, NULL_PTR, keyLength, iterations);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        Cry_GddAutHsmPbkdf2Tb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        Cry_GddAutHsmPbkdf2Tb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmPbkdf2Tb.ulKeyID = keyLength;
      Cry_GddAutHsmPbkdf2Tb.ulIterations = iterations;
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
** Function Name        : Cry_AutHsmPbkdf2Update                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Pbkdf2   **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmPbkdf2MainFunction() can process the      **
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
**                        Cry_GddAutHsmPbkdf2Tb                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_KeyDeriveServiceHasCallback,                    **
**                        Csm_KeyDeriveCallbackNotification,                  **
**                        Hsm_Pbkdf2Update                                    **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPbkdf2Update(Csm_ConfigIdType cfgId,
  const uint8* passwordPtr, uint32 passwordLength, const uint8* saltPtr,
  uint32 saltLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddAutHsmPbkdf2Tb.ucJobState)
  {
    Cry_GddAutHsmPbkdf2Tb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_KeyDeriveServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = HSM_NO_ERROR;
      if (Cry_GddAutHsmPbkdf2DataType == HSM_DATA_AES_RAM_KEY)
      {
        if ((passwordPtr == NULL_PTR) || (passwordLength == CSM_ZERO))
        {
          LddErr = HSM_PARAMETER_ERROR;
        }
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_Pbkdf2Update(LblAsync, NULL_PTR,
          passwordPtr, passwordLength, saltPtr, saltLength);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        Cry_GddAutHsmPbkdf2Tb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        Cry_GddAutHsmPbkdf2Tb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmPbkdf2Tb.pPasswordPtr = passwordPtr;
      Cry_GddAutHsmPbkdf2Tb.pPasswordLength = passwordLength;
      Cry_GddAutHsmPbkdf2Tb.pSaltPtr = saltPtr;
      Cry_GddAutHsmPbkdf2Tb.ulSaltLength = saltLength;
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
** Function Name        : Cry_AutHsmPbkdf2Finish                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pbkdf2  **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmPbkdf2MainFunction() can finish the       **
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
**                        Cry_GddAutHsmPbkdf2Tb                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_KeyDeriveServiceHasCallback,                    **
**                        Hsm_Pbkdf2Finish                                    **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPbkdf2Finish(Csm_ConfigIdType cfgId,
  Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddAutHsmPbkdf2Tb.ucJobState)
  {
    Cry_GddAutHsmPbkdf2Tb.ucJobState = JOB_FINISH;

    LblAsync = Csm_KeyDeriveServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LddErr = Hsm_Pbkdf2Finish(LblAsync, NULL_PTR,
        &(keyPtr->data[0]), keyPtr->length);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      Cry_GddAutHsmPbkdf2Tb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmPbkdf2Tb.pKeyPtr = keyPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPbkdf2Callback                            **
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
**                        Cry_GddAutHsmPbkdf2Tb                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_KeyDeriveCallbackNotification,                  **
**                        Csm_KeyDeriveServiceFinishNotification              **
*******************************************************************************/
static void Cry_AutHsmPbkdf2Callback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_KeyDeriveCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmPbkdf2Tb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmPbkdf2Tb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmPbkdf2Tb.ucJobState = NO_JOB;
      }
      Csm_KeyDeriveCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmPbkdf2Tb.ucJobState = NO_JOB;
      Csm_KeyDeriveCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_KeyDeriveServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPbkdf2MainFunction                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_KeyDeriveCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutHsmPbkdf2Start() or                          **
**                        Cry_AutHsmPbkdf2Update(). For                       **
**                        Cry_AutHsmPbkdf2Finish invocation of                **
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
**                        Cry_GddAutHsmPbkdf2Tb                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hsm_HmacSha160Init                                  **
**                        Hsm_HmacSha160Update                                **
**                        Hsm_HmacSha160Finish                                **
**                        Csm_KeyDeriveCallbackNotification                   **
**                        Csm_KeyDeriveServiceFinishNotification              **
*******************************************************************************/
void Cry_AutHsmPbkdf2MainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmPbkdf2Callback;

  switch (Cry_GddAutHsmPbkdf2Tb.ucJobState)
  {
  case JOB_START:
    if (Cry_GddAutHsmPbkdf2Tb.ulIterations == CSM_ZERO)
    {
      LddErr = HSM_PARAMETER_ERROR;
    }
    else
    {
      if (Cry_GddAutHsmPbkdf2Tb.ulKeyID == CSM_ZERO)
      {
        Cry_GddAutHsmPbkdf2DataType = HSM_DATA_AES_RAM_KEY;
      }
      else
      {
        Cry_GddAutHsmPbkdf2DataType = HSM_DATA_AES_KEY;
      }

      LddErr = HSM_NO_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_Pbkdf2Init(CSM_TRUE, LpCallback,
        Cry_GddAutHsmPbkdf2Tb.ulKeyID,
        Cry_GddAutHsmPbkdf2Tb.ulIterations);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmPbkdf2Tb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_KeyDeriveCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    LddErr = HSM_NO_ERROR;
    if (Cry_GddAutHsmPbkdf2DataType == HSM_DATA_AES_RAM_KEY)
    {
      if ((Cry_GddAutHsmPbkdf2Tb.pPasswordPtr == NULL_PTR)
        || (Cry_GddAutHsmPbkdf2Tb.pPasswordLength == CSM_ZERO))
      {
        LddErr = HSM_PARAMETER_ERROR;
      }
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_Pbkdf2Update(CSM_TRUE, LpCallback,
        Cry_GddAutHsmPbkdf2Tb.pPasswordPtr,
        Cry_GddAutHsmPbkdf2Tb.pPasswordLength,
        Cry_GddAutHsmPbkdf2Tb.pSaltPtr,
        Cry_GddAutHsmPbkdf2Tb.ulSaltLength);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmPbkdf2Tb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_KeyDeriveCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    /* polyspace +3 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    LddErr = Hsm_Pbkdf2Finish(CSM_TRUE, LpCallback,
      &(Cry_GddAutHsmPbkdf2Tb.pKeyPtr->data[0]),
      Cry_GddAutHsmPbkdf2Tb.pKeyPtr->length);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue != E_OK)
    {
      /* reset the state back to NO_JOB */
      Cry_GddAutHsmPbkdf2Tb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_KeyDeriveCallbackNotification(LddReturnValue);
    }
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

#endif /* (CSM_KEYDERIVE_AUTHSMPBKDF2 == STD_ON) */
#endif /* (CSM_KEY_DERIVATION_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
