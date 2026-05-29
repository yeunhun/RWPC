/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscPkcs1V15Sha1SeedVerify.c                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt Pkcs1V15 Sha1 Seed Verify       **
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
** 1.2.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.2     10-Nov-2017   Sinil        Redmine #10550                        **
** 1.2.1     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198, #7323                  **
** 1.0.11    21-Sep-2016   Sinil        Redmine #5554, #6128                  **
** 1.0.10    09-Aug-2016   Sinil        Redmine #5693, #5747                  **
** 1.0.9     12-Jul-2016   Sinil        Redmine #5514, #5540                  **
** 1.0.8     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.7     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.6     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.5     02-May-2016   Sinil        Redmine #4797, #4607                  **
** 1.0.4     05-Jan-2016   Sinil        Use const macro                       **
** 1.0.3     31-Dec-2015   Sinil        Adjust changed stucture               **
** 1.0.2     02-Dec-2015   Sinil        1. Using common library in FBL        **
**                                      2. Crypto api changed                 **
**                                      3. Memory section changed             **
** 1.0.1     19-Oct-2015   Sinil        Initialize hash digest buffer         **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_EscPkcs1V15Sha1SeedVerify.h"
#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_ESCPKCS1V15SHA1SEEDVERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "callback.h"
#include "pkcs1_v15.h"
#include "sha_1.h"
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
} Cry_EscPkcs1V15Sha1SeedVerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaEscPkcs1V15Sha1SeedVerifySeed[EscSha1_DIGEST_LEN];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Cry_EscPkcs1V15Sha1SeedVerifyTransferBuffer Cry_GddEscPkcs1V15Sha1SeedVerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscPkcs1V15Sha1SeedVerifyInit                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Pkcs1V15Sha1Seed module. **
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
**                      Cry_GddEscPkcs1V15Sha1SeedVerifyTb                    **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_EscPkcs1V15Sha1SeedVerifyInit(void)
{
  Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
  Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pDataPtr = NULL_PTR;
  Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pSignaturePtr = NULL_PTR;
  Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ulSignatureLength = CSM_ZERO;
  Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)Cry_GaaEscPkcs1V15Sha1SeedVerifySeed, 0x00,
    EscSha1_DIGEST_LEN);
}

/*******************************************************************************
** Function Name        : Cry_EscPkcs1V15Sha1SeedVerifyStart                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt Pkcs1V15 Seed, so that if is **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscPkcs1V15Sha1SeedVerifyMainFunction() can     **
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
**                        Cry_GddEscPkcs1V15Sha1SeedVerifyTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_EscPkcs1V15Sha1SeedVerifyInit                   **
*******************************************************************************/
Std_ReturnType Cry_EscPkcs1V15Sha1SeedVerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
    Cry_EscPkcs1V15Sha1SeedVerifyInit();

    Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_START;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != sizeof(Csm_EscRsaPublicKeyType))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr = keyPtr;

        Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr = keyPtr;
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
** Function Name        : Cry_EscPkcs1V15Sha1SeedVerifyUpdate                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Seed     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscPkcs1V15Sha1SeedVerifyMainFunction() can     **
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
**                        Cry_GddEscPkcs1V15Sha1SeedVerifyTb                  **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_EscPkcs1V15Sha1SeedVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  uint8 LucIndex;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
    Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      if (dataLength > EscSha1_DIGEST_LEN)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        /* polyspace +3 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The array and length is checked" */
        for (LucIndex = CSM_ZERO; LucIndex < dataLength; LucIndex++)
        {
          Cry_GaaEscPkcs1V15Sha1SeedVerifySeed[LucIndex] = dataPtr[LucIndex];
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pDataPtr = dataPtr;
      Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_EscPkcs1V15Sha1SeedVerifyFinish                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1V15**
**                        Seed computation and store the result into the      **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscPkcs1V15Sha1SeedVerifyMainFunction() can     **
**                        finish the computation and store the result in the  **
**                        memory location given                               **
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
**                        Cry_GddEscPkcs1V15Sha1SeedVerifyTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscPkcs1V15_Verify, EscCallback_setFunction         **
*******************************************************************************/
Std_ReturnType Cry_EscPkcs1V15Sha1SeedVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  const Csm_EscRsaPublicKeyType *LpEscRsaPublicKey;
  EscPkcs1V15_VerifyParamsT LddVerifyParams;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
    Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_FINISH;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      if (signatureLength < EscRsa_KEY_BYTES)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LpEscRsaPublicKey = (const Csm_EscRsaPublicKeyType*)
          ((const void*)(Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->data));
        /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        LddVerifyParams.hashDigest = Cry_GaaEscPkcs1V15Sha1SeedVerifySeed;
        LddVerifyParams.modulus = LpEscRsaPublicKey->modulus;
        LddVerifyParams.pubExp = LpEscRsaPublicKey->exponent;
        LddVerifyParams.signature = signaturePtr;
        LddVerifyParams.digestType = EscPkcs1V15_DIGEST_TYPE_SHA1;

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

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pSignaturePtr = signaturePtr;
      Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ulSignatureLength = signatureLength;
      Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_EscPkcs1V15Sha1SeedVerifyMainFunction           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureVerifyCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_EscPkcs1V15Sha1SeedVerifyStart() or             **
**                        Cry_EscPkcs1V15Sha1SeedVerifyUpdate(). For          **
**                        Cry_EscPkcs1V15Sha1SeedVerifyFinish invocation of   **
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
**                        Cry_GddEscPkcs1V15Sha1SeedVerifyTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscPkcs1V15_Verify, EscCallback_setFunction,        **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
void Cry_EscPkcs1V15Sha1SeedVerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  const Csm_EscRsaPublicKeyType *LpEscRsaPublicKey;
  EscPkcs1V15_VerifyParamsT LddVerifyParams;
  uint8 LucIndex;

  LddReturnValue = E_OK;

  switch (Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->length
      != sizeof(Csm_EscRsaPublicKeyType))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    if (Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ulDataLength > EscSha1_DIGEST_LEN)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      for (LucIndex = CSM_ZERO;
        LucIndex < Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ulDataLength; LucIndex++)
      {
        /* polyspace +2 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        Cry_GaaEscPkcs1V15Sha1SeedVerifySeed[LucIndex]
          = Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pDataPtr[LucIndex];
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    if (Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ulSignatureLength < EscRsa_KEY_BYTES)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LpEscRsaPublicKey = (const Csm_EscRsaPublicKeyType*)
        ((const void*)(Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->data));
      /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LddVerifyParams.hashDigest = Cry_GaaEscPkcs1V15Sha1SeedVerifySeed;
      LddVerifyParams.modulus = LpEscRsaPublicKey->modulus;
      LddVerifyParams.pubExp = LpEscRsaPublicKey->exponent;
      LddVerifyParams.signature = Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pSignaturePtr;
      LddVerifyParams.digestType = EscPkcs1V15_DIGEST_TYPE_SHA1;

      EscCallback_setFunction(NULL_PTR);

      LblReturnValue = EscPkcs1V15_Verify(&LddVerifyParams);

      if (LblReturnValue != CSM_TRUE)
      {
        /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        *(Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pResultPtr) = CSM_E_VER_OK;
      }
      else
      {
        /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        *(Cry_GddEscPkcs1V15Sha1SeedVerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SIGNATURE_ESCPKCS1V15SHA1SEEDVERIFY == STD_ON) */
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
