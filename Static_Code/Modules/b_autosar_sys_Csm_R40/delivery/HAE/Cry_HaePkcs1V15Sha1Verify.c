/*******************************************************************************
**                                                                            **
**  (C) 2018~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaePkcs1V15Sha1Verify.c                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HAE Pkcs1V15 Sha1 Verify Interface      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 2.6.3.0   24-Mar-2021   TamTV6       Redmine #18165                        **
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.0.2     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.1     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.0     01-Nov-2018   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_HaePkcs1V15Sha1Verify.h"
#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_HAEPKCS1V15SHA1VERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_Pkcs1.h"
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
} Cry_HaePkcs1V15Sha1VerifyTransferBuffer;

/*******************************************************************************
**                               Local Data                                   **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaePkcs1V15Sha1VerifyModulus[HMG_RSA_BYTES_SIZE];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HmgRsaPublickey Cry_GddHaePkcs1V15Sha1VerifyPublickey;

static HmgSha160Ctx Cry_GddHaePkcs1V15Sha1VerifySha1Context;

static Cry_HaePkcs1V15Sha1VerifyTransferBuffer Cry_GddHaePkcs1V15Sha1VerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaePkcs1V15Sha1VerifyInit                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Pkcs1V15 Sha1 module.    **
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
**                      Cry_GddHaePkcs1V15Sha1VerifyTb                        **
**                      Cry_GddHaePkcs1V15Sha1VerifyContext,                  **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaePkcs1V15Sha1VerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = NO_JOB;
  Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha1VerifyTb.pDataPtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha1VerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddHaePkcs1V15Sha1VerifyTb.pSignaturePtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha1VerifyTb.ulSignatureLength = CSM_ZERO;
  Cry_GddHaePkcs1V15Sha1VerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)Cry_GaaHaePkcs1V15Sha1VerifyModulus, 0x00, HMG_RSA_BYTES_SIZE);

  Cry_GddHaePkcs1V15Sha1VerifyPublickey.modulus = Cry_GaaHaePkcs1V15Sha1VerifyModulus;
  Cry_GddHaePkcs1V15Sha1VerifyPublickey.exponent = CSM_ZERO;

  (void)memset((void*)&Cry_GddHaePkcs1V15Sha1VerifySha1Context, 0x00,
    sizeof(HmgSha160Ctx));
}

/*******************************************************************************
** Function Name        : Cry_HaePkcs1V15Sha1VerifyStart                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HAE HSM Pkcs1V15 Sha1, so that if    **
**                        is able to process the input data                   **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaePkcs1V15Sha1VerifyMainFunction() can         **
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
**                        Cry_GddHaePkcs1V15Sha1VerifyTb,                     **
**                        Cry_GddHaePkcs1V15Sha1VerifyContext,                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaePkcs1V15Sha1VerifyInit,                      **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hmg_Sha160Start                                     **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha1VerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState)
  {
    Cry_HaePkcs1V15Sha1VerifyInit();

    Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = JOB_START;

    if (Csm_SignatureVerifyServiceHasCallback() == CSM_FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != (HMG_RSA_BYTES_SIZE + sizeof(uint32)))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblPrimitiveRet = Hmg_Sha160Start(&Cry_GddHaePkcs1V15Sha1VerifySha1Context);
        if (LblPrimitiveRet != HMG_SUCCESS)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        (void)memcpy((void*)(&Cry_GaaHaePkcs1V15Sha1VerifyModulus[0u]), \
          (const void*)(&(keyPtr->data[0u])), \
          HMG_RSA_BYTES_SIZE);

        Cry_GddHaePkcs1V15Sha1VerifyPublickey.exponent
          #if (defined(HIGH_BYTE_FIRST) && (CPU_BYTE_ORDER == HIGH_BYTE_FIRST))
          = ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE]) << 24)
          + ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 1]) << 16)
          + ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 2]) << 8)
          + (uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 3]);
          #else
          = (uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE])
          + ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 1]) << 8)
          + ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 2]) << 16)
          + ((uint32)(keyPtr->data[HMG_RSA_BYTES_SIZE + 3]) << 24);
          #endif

        Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr = keyPtr;
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
** Function Name        : Cry_HaePkcs1V15Sha1VerifyUpdate                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha1     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaePkcs1V15Sha1VerifyMainFunction() can         **
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
**                        Cry_GddHaePkcs1V15Sha1VerifyTb,                     **
**                        Cry_GddHaePkcs1V15Sha1VerifyContext                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hmg_Sha160Update                                    **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha1VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState)
  {
    Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureVerifyServiceHasCallback() == CSM_FALSE)
    {
      LblPrimitiveRet = Hmg_Sha160Update(&Cry_GddHaePkcs1V15Sha1VerifySha1Context,
        dataPtr, dataLength);
      if (LblPrimitiveRet != HMG_SUCCESS)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaePkcs1V15Sha1VerifyTb.pDataPtr = dataPtr;
      Cry_GddHaePkcs1V15Sha1VerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaePkcs1V15Sha1VerifyFinish                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1V15**
**                        Sha1 computation and store the result into the      **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaePkcs1V15Sha1VerifyMainFunction() can         **
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
**                        Cry_GddHaePkcs1V15Sha1VerifyTb,                     **
**                        Cry_GddHaePkcs1V15Sha1VerifyContext,                **
**                        Cry_GaaHaePkcs1V15Sha1Digest                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hmg_Sha160Finish, Hmg_RsaPkcs1v15Verify             **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha1VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;
  uint8 LaaSha1Digest[HMG_SHA160_DIGEST_SIZE];

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState)
  {
    Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = JOB_FINISH;

    if (Csm_SignatureVerifyServiceHasCallback() == CSM_FALSE)
    {
      if (signatureLength < HMG_RSA_BYTES_SIZE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha1Digest, 0x00, sizeof(LaaSha1Digest));

        LblPrimitiveRet = Hmg_Sha160Finish(&Cry_GddHaePkcs1V15Sha1VerifySha1Context,
          LaaSha1Digest);
        if (LblPrimitiveRet != HMG_SUCCESS)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        #ifdef HMG_ENABLE_CALLBACK
        Hmg_SetCallbackFunc(NULL_PTR);
        #endif

        LblPrimitiveRet = Hmg_RsaPkcs1v15Verify(
          signaturePtr,
          LaaSha1Digest,
          HMG_SHA_160,
          &Cry_GddHaePkcs1V15Sha1VerifyPublickey);

        if (LblPrimitiveRet == HMG_SUCCESS)
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
      Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha1VerifyTb.pSignaturePtr = signaturePtr;
      Cry_GddHaePkcs1V15Sha1VerifyTb.ulSignatureLength = signatureLength;
      Cry_GddHaePkcs1V15Sha1VerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_HaePkcs1V15Sha1VerifyMainFunction               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureVerifyCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaePkcs1V15Sha1VerifyStart() or                 **
**                        Cry_HaePkcs1V15Sha1VerifyUpdate(). For              **
**                        Cry_HaePkcs1V15Sha1VerifyFinish invocation of       **
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
**                        Cry_GddHaePkcs1V15Sha1VerifyTb,                     **
**                        Cry_GddHaePkcs1V15Sha1VerifyContext,                **
**                        Cry_GaaHaePkcs1V15Sha1Digest                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_Sha160Start, Hmg_Sha160Update, Hmg_Sha160Finish,**
**                        Hmg_RsaPkcs1v15Verify,                              **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
void Cry_HaePkcs1V15Sha1VerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;
  uint8 LaaSha1Digest[HMG_SHA160_DIGEST_SIZE];

  LddReturnValue = E_OK;

  switch (Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr->length
      != (HMG_RSA_BYTES_SIZE + sizeof(uint32)))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblPrimitiveRet = Hmg_Sha160Start(&Cry_GddHaePkcs1V15Sha1VerifySha1Context);
      if (LblPrimitiveRet != HMG_SUCCESS)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      (void)memcpy((void*)Cry_GaaHaePkcs1V15Sha1VerifyModulus,
        (const void*)(Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr->data),
        HMG_RSA_BYTES_SIZE);

      Cry_GddHaePkcs1V15Sha1VerifyPublickey.exponent
        #if (defined(HIGH_BYTE_FIRST) && (CPU_BYTE_ORDER == HIGH_BYTE_FIRST))
        = ((uint32)(Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE]) << 24)
        + ((uint32)(Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 1]) << 16)
        + ((uint32)(Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 2]) << 8)
        + (uint32)(Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 3]);
        #else
        = (uint32)(Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE])
        + ((uint32)(Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 1]) << 8)
        + ((uint32)(Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 2]) << 16)
        + ((uint32)(Cry_GddHaePkcs1V15Sha1VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 3]) << 24);
        #endif

      Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblPrimitiveRet = Hmg_Sha160Update(&Cry_GddHaePkcs1V15Sha1VerifySha1Context,
      Cry_GddHaePkcs1V15Sha1VerifyTb.pDataPtr,
      Cry_GddHaePkcs1V15Sha1VerifyTb.ulDataLength);
    if (LblPrimitiveRet != HMG_SUCCESS)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    if (Cry_GddHaePkcs1V15Sha1VerifyTb.ulSignatureLength < HMG_RSA_BYTES_SIZE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha1Digest, 0x00, sizeof(LaaSha1Digest));

      LblPrimitiveRet = Hmg_Sha160Finish(&Cry_GddHaePkcs1V15Sha1VerifySha1Context,
        LaaSha1Digest);
      if (LblPrimitiveRet != HMG_SUCCESS)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      #ifdef HMG_ENABLE_CALLBACK
      Hmg_SetCallbackFunc(NULL_PTR);
      #endif

      LblPrimitiveRet = Hmg_RsaPkcs1v15Verify(
        Cry_GddHaePkcs1V15Sha1VerifyTb.pSignaturePtr,
        LaaSha1Digest,
        HMG_SHA_160,
        &Cry_GddHaePkcs1V15Sha1VerifyPublickey);
      /* polyspace +9 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      /* polyspace +8 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      if (LblPrimitiveRet == HMG_SUCCESS)
      {
        *(Cry_GddHaePkcs1V15Sha1VerifyTb.pResultPtr) = CSM_E_VER_OK;
      }
      else
      {
        *(Cry_GddHaePkcs1V15Sha1VerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaePkcs1V15Sha1VerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SIGNATURE_HAEPKCS1V15SHA1VERIFY == STD_ON) */
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
