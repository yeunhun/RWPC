/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscPkcs1V15Sha256Verify.c                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt Pkcs1V15 Sha256 Verify Interface**
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
** 1.0.1     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.0     10-Aug-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_EscPkcs1V15Sha256Verify.h"
#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_ESCPKCS1V15SHA256VERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "callback.h"
#include "pkcs1_v15.h"
#include "sha_256.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_AsymPublicKeyType* pPublicKeyPtr;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  const uint8* pSignaturePtr;
  uint32 ulSignatureLength;
  Csm_VerifyResultType* pResultPtr;
} Cry_EscPkcs1V15Sha256VerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static EscSha256_ContextT Cry_GddEscPkcs1V15Sha256VerifyContext;

static Cry_EscPkcs1V15Sha256VerifyTransferBuffer Cry_GddEscPkcs1V15Sha256VerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscPkcs1V15Sha256VerifyInit                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Pkcs1V15Sha256 module.   **
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
** Remarks            : Global Variable(s):  Cry_GddEscPkcs1V15Sha256VerifyTb **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_EscPkcs1V15Sha256VerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
  Cry_GddEscPkcs1V15Sha256VerifyTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddEscPkcs1V15Sha256VerifyTb.pDataPtr = NULL_PTR;
  Cry_GddEscPkcs1V15Sha256VerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddEscPkcs1V15Sha256VerifyTb.pSignaturePtr = NULL_PTR;
  Cry_GddEscPkcs1V15Sha256VerifyTb.ulSignatureLength = CSM_ZERO;
  Cry_GddEscPkcs1V15Sha256VerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddEscPkcs1V15Sha256VerifyContext, 0x00,
    sizeof(EscSha256_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscPkcs1V15Sha256VerifyStart                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt Pkcs1V15 Sha256, so that if  **
**                        is able to process the input data                   **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscPkcs1V15Sha256VerifyMainFunction() can       **
**                        process initialisation                              **
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
**                        Cry_GddEscPkcs1V15Sha256VerifyTb                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_EscPkcs1V15Sha256VerifyInit,                    **
**                        EscSha256_Init                                      **
*******************************************************************************/
Std_ReturnType Cry_EscPkcs1V15Sha256VerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState)
  {
    Cry_EscPkcs1V15Sha256VerifyInit();

    Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = JOB_START;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != sizeof(Csm_EscRsaPublicKeyType))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblReturnValue = EscSha256_Init(&Cry_GddEscPkcs1V15Sha256VerifyContext);

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscPkcs1V15Sha256VerifyTb.pPublicKeyPtr = keyPtr;

        Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscPkcs1V15Sha256VerifyTb.pPublicKeyPtr = keyPtr;
    }
  }
  else
  {
    /* Job is busy in processing other job, set the return value to CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_EscPkcs1V15Sha256VerifyUpdate                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha256   **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscPkcs1V15Sha256VerifyMainFunction() can       **
**                        process the input                                   **
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
**                        Cry_GddEscPkcs1V15Sha256VerifyTb                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscSha256_Update                                    **
*******************************************************************************/
Std_ReturnType Cry_EscPkcs1V15Sha256VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState)
  {
    Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      LblReturnValue = EscSha256_Update(&Cry_GddEscPkcs1V15Sha256VerifyContext,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscPkcs1V15Sha256VerifyTb.pDataPtr = dataPtr;
      Cry_GddEscPkcs1V15Sha256VerifyTb.ulDataLength = dataLength;
    }
  }
  else
  {
    /* Job process is still not complete, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_EscPkcs1V15Sha256VerifyFinish                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1V15**
**                        Sha256 computation and store the result into the    **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscPkcs1V15Sha256VerifyMainFunction() can finish**
**                        the computation and store the result in the memory  **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, signaturePtr, signatureLength                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : resultPtr                                           **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddEscPkcs1V15Sha256VerifyTb                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscSha256_Finish,                                   **
**                        EscPkcs1V15_Verify, EscCallback_setFunction         **
*******************************************************************************/
Std_ReturnType Cry_EscPkcs1V15Sha256VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  const Csm_EscRsaPublicKeyType *LpEscRsaPublicKey;
  uint8 LaaSha256Digest[EscSha256_DIGEST_LEN];
  EscPkcs1V15_VerifyParamsT LddVerifyParams;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState)
  {
    Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = JOB_FINISH;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      if (signatureLength < EscRsa_KEY_BYTES)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

        LblReturnValue = EscSha256_Finish(
          &Cry_GddEscPkcs1V15Sha256VerifyContext, LaaSha256Digest);

        if (LblReturnValue != CSM_TRUE)
        {
          LpEscRsaPublicKey = (const Csm_EscRsaPublicKeyType*)
            ((const void*)(Cry_GddEscPkcs1V15Sha256VerifyTb.pPublicKeyPtr->data));
          /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          LddVerifyParams.hashDigest = LaaSha256Digest;
          LddVerifyParams.modulus = LpEscRsaPublicKey->modulus;
          LddVerifyParams.pubExp = LpEscRsaPublicKey->exponent;
          LddVerifyParams.signature = signaturePtr;
          LddVerifyParams.digestType = EscPkcs1V15_DIGEST_TYPE_SHA256;

          EscCallback_setFunction(NULL_PTR);

          LblReturnValue = EscPkcs1V15_Verify(&LddVerifyParams);

          if (LblReturnValue != CSM_TRUE)
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            *resultPtr = CSM_E_VER_OK;
          }
          else
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            *resultPtr = CSM_E_VER_NOT_OK;
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddEscPkcs1V15Sha256VerifyTb.pSignaturePtr = signaturePtr;
      Cry_GddEscPkcs1V15Sha256VerifyTb.ulSignatureLength = signatureLength;
      Cry_GddEscPkcs1V15Sha256VerifyTb.pResultPtr = resultPtr;
    }
  }
  else
  {
    /* Job process is still not complete, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_EscPkcs1V15Sha256VerifyMainFunction             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureVerifyCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_EscPkcs1V15Sha256VerifyStart() or               **
**                        Cry_EscPkcs1V15Sha256VerifyUpdate(). For            **
**                        Cry_EscPkcs1V15Sha256VerifyFinish invocation of     **
**                        Csm_SignatureVerifyCallbackNotification()           **
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
**                        Cry_GddEscPkcs1V15Sha256VerifyTb                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscSha256_Init,                                     **
**                        EscSha256_Update,                                   **
**                        EscSha256_Finish,                                   **
**                        EscPkcs1V15_Verify, EscCallback_setFunction,        **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
void Cry_EscPkcs1V15Sha256VerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  const Csm_EscRsaPublicKeyType *LpEscRsaPublicKey;
  uint8 LaaSha256Digest[EscSha256_DIGEST_LEN];
  EscPkcs1V15_VerifyParamsT LddVerifyParams;

  LddReturnValue = E_OK;

  switch (Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddEscPkcs1V15Sha256VerifyTb.pPublicKeyPtr->length
      != sizeof(Csm_EscRsaPublicKeyType))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblReturnValue = EscSha256_Init(&Cry_GddEscPkcs1V15Sha256VerifyContext);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = EscSha256_Update(&Cry_GddEscPkcs1V15Sha256VerifyContext,
      Cry_GddEscPkcs1V15Sha256VerifyTb.pDataPtr,
      Cry_GddEscPkcs1V15Sha256VerifyTb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    if (Cry_GddEscPkcs1V15Sha256VerifyTb.ulSignatureLength < EscRsa_KEY_BYTES)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

      LblReturnValue = EscSha256_Finish(
        &Cry_GddEscPkcs1V15Sha256VerifyContext, LaaSha256Digest);

      if (LblReturnValue != CSM_TRUE)
      {
        LpEscRsaPublicKey = (const Csm_EscRsaPublicKeyType*)
          ((const void*)(Cry_GddEscPkcs1V15Sha256VerifyTb.pPublicKeyPtr->data));
        /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        LddVerifyParams.hashDigest = LaaSha256Digest;
        LddVerifyParams.modulus = LpEscRsaPublicKey->modulus;
        LddVerifyParams.pubExp = LpEscRsaPublicKey->exponent;
        LddVerifyParams.signature =
          Cry_GddEscPkcs1V15Sha256VerifyTb.pSignaturePtr;
        LddVerifyParams.digestType = EscPkcs1V15_DIGEST_TYPE_SHA256;

        EscCallback_setFunction(NULL_PTR);

        LblReturnValue = EscPkcs1V15_Verify(&LddVerifyParams);

        if (LblReturnValue != CSM_TRUE)
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          *(Cry_GddEscPkcs1V15Sha256VerifyTb.pResultPtr) = CSM_E_VER_OK;
        }
        else
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          *(Cry_GddEscPkcs1V15Sha256VerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscPkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    Csm_SignatureVerifyServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SIGNATURE_ESCPKCS1V15SHA256VERIFY == STD_ON) */
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
