/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscPkcs1V15Sha256Generate.c                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt Pkcs1V15 Sha256 Generate        **
**              Interface                                                     **
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
#include "Cry_EscPkcs1V15Sha256Generate.h"
#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
#if (CSM_SIGNATURE_ESCPKCS1V15SHA256GENERATE == STD_ON)
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
  /* Stores private key pointer in RSA */
  const Csm_AsymPrivateKeyType* pPrivateKeyPtr;
  /* Stores raw data pointer used for Escrypt Pkcs1V15 Computation */
  const uint8* pDataPtr;
  /* Data length of the data used for Escrypt Pkcs1V15 Computation */
  uint32 ulDataLength;
  /* Stores result data pointer used for Escrypt Pkcs1V15 Computation */
  uint8* pResultPtr;
  /* Pointer of result data length */
  uint32* pResultLengthPtr;
} Cry_EscPkcs1V15Sha256GenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static EscSha256_ContextT Cry_GddEscPkcs1V15Sha256GenerateContext;

static Cry_EscPkcs1V15Sha256GenerateTransferBuffer Cry_GddEscPkcs1V15Sha256GenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscPkcs1V15Sha256GenerateInit                     **
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
** Remarks            : Global Variable(s):                                   **
**                      Cry_GddEscPkcs1V15Sha256GenerateTb                    **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_EscPkcs1V15Sha256GenerateInit(void)
{
  Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
  Cry_GddEscPkcs1V15Sha256GenerateTb.pPrivateKeyPtr = NULL_PTR;
  Cry_GddEscPkcs1V15Sha256GenerateTb.pDataPtr = NULL_PTR;
  Cry_GddEscPkcs1V15Sha256GenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddEscPkcs1V15Sha256GenerateTb.pResultPtr = NULL_PTR;
  Cry_GddEscPkcs1V15Sha256GenerateTb.pResultLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddEscPkcs1V15Sha256GenerateContext, 0x00,
    sizeof(EscSha256_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscPkcs1V15Sha256GenerateStart                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt Pkcs1V15 Sha256, so that it  **
**                        is able to process the input data                   **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscPkcs1V15Sha256GenerateMainFunction() can     **
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
**                        Cry_GddEscPkcs1V15Sha256GenerateTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscSha256_Init                                      **
*******************************************************************************/
Std_ReturnType Cry_EscPkcs1V15Sha256GenerateStart(const void *cfgPtr,
  const Csm_AsymPrivateKeyType *keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState)
  {
    Cry_EscPkcs1V15Sha256GenerateInit();

    Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = JOB_START;

    if (Csm_SignatureGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != sizeof(Csm_EscRsaPrivateKeyType))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblReturnValue = EscSha256_Init(&Cry_GddEscPkcs1V15Sha256GenerateContext);

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscPkcs1V15Sha256GenerateTb.pPrivateKeyPtr = keyPtr;

        Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscPkcs1V15Sha256GenerateTb.pPrivateKeyPtr = keyPtr;
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
** Function Name        : Cry_EscPkcs1V15Sha256GenerateUpdate                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha256   **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscPkcs1V15Sha256GenerateMainFunction() can     **
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
**                        Cry_GddEscPkcs1V15Sha256GenerateTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscSha256_Update                                    **
*******************************************************************************/
Std_ReturnType Cry_EscPkcs1V15Sha256GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState)
  {
    Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureGenerateServiceHasCallback() == FALSE)
    {
      LblReturnValue = EscSha256_Update(&Cry_GddEscPkcs1V15Sha256GenerateContext,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscPkcs1V15Sha256GenerateTb.pDataPtr = dataPtr;
      Cry_GddEscPkcs1V15Sha256GenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_EscPkcs1V15Sha256GenerateFinish                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1V15**
**                        Sha256 computation and store the result into the    **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscPkcs1V15Sha256GenerateMainFunction() can     **
**                        finish the computation and store the result in the  **
**                        memory location given                               **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : resultLengthPtr                                     **
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
**                        Cry_GddEscPkcs1V15Sha256GenerateTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscSha256_Finish,                                   **
**                        EscPkcs1V15_Sign, EscCallback_setFunction           **
*******************************************************************************/
Std_ReturnType Cry_EscPkcs1V15Sha256GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32 *resultLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  const Csm_EscRsaPrivateKeyType *LpEscRsaPrivateKey;
  uint8 LaaSha256Digest[EscSha256_DIGEST_LEN];
  EscPkcs1V15_PrivKeyT LddPrivKey;
  EscPkcs1V15_SignParamsT LddSignParams;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState)
  {
    Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = JOB_FINISH;

    if (Csm_SignatureGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*resultLengthPtr < EscRsa_KEY_BYTES)
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

        LblReturnValue = EscSha256_Finish(
          &Cry_GddEscPkcs1V15Sha256GenerateContext, LaaSha256Digest);

        if (LblReturnValue != CSM_TRUE)
        {
          *resultLengthPtr = CSM_ZERO;

          LpEscRsaPrivateKey = (const Csm_EscRsaPrivateKeyType*)
            ((const void*)(Cry_GddEscPkcs1V15Sha256GenerateTb.pPrivateKeyPtr->data));
          /* polyspace +1 MISRA-C3:D4.11 RTE:STD_LIB [Justified:Low] "The input is checked" */
          (void)memcpy((void*)(&LddPrivKey.modulus[0u]), \
            (const void*)(&(LpEscRsaPrivateKey->modulus[0u])), \
            EscRsa_KEY_BYTES);
          (void)memcpy((void*)(&LddPrivKey.privExp[0u]), \
            (const void*)(&(LpEscRsaPrivateKey->exponent[0u])), \
            EscRsa_KEY_BYTES);

          LddSignParams.hashDigest = LaaSha256Digest;
          LddSignParams.privKey = &LddPrivKey;
          LddSignParams.signature = resultPtr;
          LddSignParams.digestType = EscPkcs1V15_DIGEST_TYPE_SHA256;

          EscCallback_setFunction(NULL_PTR);

          LblReturnValue = EscPkcs1V15_Sign(&LddSignParams);

          if (LblReturnValue != CSM_TRUE)
          {
            *resultLengthPtr = EscRsa_KEY_BYTES;
          }
          else
          {
            LddReturnValue = E_NOT_OK;
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddEscPkcs1V15Sha256GenerateTb.pResultPtr = resultPtr;
      Cry_GddEscPkcs1V15Sha256GenerateTb.pResultLengthPtr = resultLengthPtr;
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
** Function Name        : Cry_EscPkcs1V15Sha256GenerateMainFunction           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureGenerateCallbackNotification() with the**
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_EscPkcs1V15Sha256GenerateStart() or             **
**                        Cry_EscPkcs1V15Sha256GenerateUpdate(). For          **
**                        Cry_EscPkcs1V15Sha256GenerateFinish invocation of   **
**                        Csm_SignatureGenerateCallbackNotification()         **
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
**                        Cry_GddEscPkcs1V15Sha256GenerateTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscSha256_Init,                                     **
**                        EscSha256_Update,                                   **
**                        EscSha256_Finish,                                   **
**                        EscPkcs1V15_Sign, EscCallback_setFunction,          **
**                        Csm_SignatureGenerateCallbackNotification,          **
**                        Csm_SignatureGenerateServiceFinishNotification      **
*******************************************************************************/
void Cry_EscPkcs1V15Sha256GenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  const Csm_EscRsaPrivateKeyType *LpEscRsaPrivateKey;
  uint8 LaaSha256Digest[EscSha256_DIGEST_LEN];
  EscPkcs1V15_PrivKeyT LddPrivKey;
  EscPkcs1V15_SignParamsT LddSignParams;

  LddReturnValue = E_OK;

  switch (Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddEscPkcs1V15Sha256GenerateTb.pPrivateKeyPtr->length
      != sizeof(Csm_EscRsaPrivateKeyType))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblReturnValue = EscSha256_Init(&Cry_GddEscPkcs1V15Sha256GenerateContext);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
    }

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = EscSha256_Update(&Cry_GddEscPkcs1V15Sha256GenerateContext,
      Cry_GddEscPkcs1V15Sha256GenerateTb.pDataPtr,
      Cry_GddEscPkcs1V15Sha256GenerateTb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
    }

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*(Cry_GddEscPkcs1V15Sha256GenerateTb.pResultLengthPtr) < EscRsa_KEY_BYTES)
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

      LblReturnValue = EscSha256_Finish(&Cry_GddEscPkcs1V15Sha256GenerateContext,
        LaaSha256Digest);

      if (LblReturnValue != CSM_TRUE)
      {
        *(Cry_GddEscPkcs1V15Sha256GenerateTb.pResultLengthPtr) = CSM_ZERO;

        LpEscRsaPrivateKey = (const Csm_EscRsaPrivateKeyType*)
          ((const void*)(Cry_GddEscPkcs1V15Sha256GenerateTb.pPrivateKeyPtr->data));
        /* polyspace +1 MISRA-C3:D4.11 RTE:STD_LIB [Justified:Low] "The input is checked" */
        (void)memcpy((void*)(&LddPrivKey.modulus[0u]), \
          (const void*)(&(LpEscRsaPrivateKey->modulus[0u])), \
          EscRsa_KEY_BYTES);
        (void)memcpy((void*)(&LddPrivKey.privExp[0u]), \
          (const void*)(&(LpEscRsaPrivateKey->exponent[0u])), \
          EscRsa_KEY_BYTES);

        LddSignParams.hashDigest = LaaSha256Digest;
        LddSignParams.privKey = &LddPrivKey;
        LddSignParams.signature = Cry_GddEscPkcs1V15Sha256GenerateTb.pResultPtr;
        LddSignParams.digestType = EscPkcs1V15_DIGEST_TYPE_SHA256;

        EscCallback_setFunction(NULL_PTR);

        LblReturnValue = EscPkcs1V15_Sign(&LddSignParams);

        if (LblReturnValue != CSM_TRUE)
        {
          *(Cry_GddEscPkcs1V15Sha256GenerateTb.pResultLengthPtr)
            = EscRsa_KEY_BYTES;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    Csm_SignatureGenerateServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SIGNATURE_ESCPKCS1V15SHA256GENERATE == STD_ON) */
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
