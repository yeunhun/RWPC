/*******************************************************************************
**                                                                            **
**  (C) 2018~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaePkcs1V15Sha256Verify.c                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HAE Pkcs1V15 Sha256 Verify Interface    **
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
** 1.0.2     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.1     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.0     01-Nov-2018   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_HaePkcs1V15Sha256Verify.h"
#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY == STD_ON)
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
} Cry_HaePkcs1V15Sha256VerifyTransferBuffer;

/*******************************************************************************
**                               Local Data                                   **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaePkcs1V15Sha256VerifyModulus[HMG_RSA_BYTES_SIZE];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HmgRsaPublickey Cry_GddHaePkcs1V15Sha256VerifyPublickey;

static HmgSha256Ctx Cry_GddHaePkcs1V15Sha256VerifySha256Context;

static Cry_HaePkcs1V15Sha256VerifyTransferBuffer Cry_GddHaePkcs1V15Sha256VerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaePkcs1V15Sha256VerifyInit                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Pkcs1V15 Sha256 module.  **
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
**                      Cry_GddHaePkcs1V15Sha256VerifyTb                      **
**                      Cry_GddHaePkcs1V15Sha256VerifyContext,                **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaePkcs1V15Sha256VerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
  Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha256VerifyTb.pDataPtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha256VerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddHaePkcs1V15Sha256VerifyTb.pSignaturePtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha256VerifyTb.ulSignatureLength = CSM_ZERO;
  Cry_GddHaePkcs1V15Sha256VerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)Cry_GaaHaePkcs1V15Sha256VerifyModulus, 0x00, HMG_RSA_BYTES_SIZE);

  Cry_GddHaePkcs1V15Sha256VerifyPublickey.modulus = Cry_GaaHaePkcs1V15Sha256VerifyModulus;
  Cry_GddHaePkcs1V15Sha256VerifyPublickey.exponent = CSM_ZERO;

  (void)memset((void*)&Cry_GddHaePkcs1V15Sha256VerifySha256Context, 0x00,
    sizeof(HmgSha256Ctx));
}

/*******************************************************************************
** Function Name        : Cry_HaePkcs1V15Sha256VerifyStart                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HAE HSM Pkcs1V15 Sha256, so that if  **
**                        is able to process the input data                   **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaePkcs1V15Sha256VerifyMainFunction() can       **
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
**                        Cry_GddHaePkcs1V15Sha256VerifyTb,                   **
**                        Cry_GddHaePkcs1V15Sha256VerifyContext,              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaePkcs1V15Sha256VerifyInit,                    **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hmg_Sha256Start                                     **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha256VerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState)
  {
    Cry_HaePkcs1V15Sha256VerifyInit();

    Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = JOB_START;

    if (Csm_SignatureVerifyServiceHasCallback() == CSM_FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != (HMG_RSA_BYTES_SIZE + sizeof(uint32)))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblPrimitiveRet = Hmg_Sha256Start(&Cry_GddHaePkcs1V15Sha256VerifySha256Context);
        if (LblPrimitiveRet != HMG_SUCCESS)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        (void)memcpy((void*)Cry_GaaHaePkcs1V15Sha256VerifyModulus, \
          (const void*)(keyPtr->data), HMG_RSA_BYTES_SIZE);

        Cry_GddHaePkcs1V15Sha256VerifyPublickey.exponent
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

        Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr = keyPtr;
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
** Function Name        : Cry_HaePkcs1V15Sha256VerifyUpdate                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha256   **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaePkcs1V15Sha256VerifyMainFunction() can       **
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
**                        Cry_GddHaePkcs1V15Sha256VerifyTb,                   **
**                        Cry_GddHaePkcs1V15Sha256VerifyContext               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hmg_Sha256Update                                    **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha256VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState)
  {
    Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureVerifyServiceHasCallback() == CSM_FALSE)
    {
      LblPrimitiveRet = Hmg_Sha256Update(&Cry_GddHaePkcs1V15Sha256VerifySha256Context,
        dataPtr, dataLength);
      if (LblPrimitiveRet != HMG_SUCCESS)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaePkcs1V15Sha256VerifyTb.pDataPtr = dataPtr;
      Cry_GddHaePkcs1V15Sha256VerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaePkcs1V15Sha256VerifyFinish                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1V15**
**                        Sha256 computation and store the result into the    **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaePkcs1V15Sha256VerifyMainFunction() can       **
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
**                        Cry_GddHaePkcs1V15Sha256VerifyTb,                   **
**                        Cry_GddHaePkcs1V15Sha256VerifyContext,              **
**                        Cry_GaaHaePkcs1V15Sha256Digest                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hmg_Sha256Finish, Hmg_RsaPkcs1v15Verify             **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha256VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;
  uint8 LaaSha256Digest[HMG_SHA256_DIGEST_SIZE];

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState)
  {
    Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = JOB_FINISH;

    if (Csm_SignatureVerifyServiceHasCallback() == CSM_FALSE)
    {
      if (signatureLength < HMG_RSA_BYTES_SIZE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

        LblPrimitiveRet = Hmg_Sha256Finish(&Cry_GddHaePkcs1V15Sha256VerifySha256Context,
          LaaSha256Digest);
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
          LaaSha256Digest,
          HMG_SHA_256,
          &Cry_GddHaePkcs1V15Sha256VerifyPublickey);

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
      Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha256VerifyTb.pSignaturePtr = signaturePtr;
      Cry_GddHaePkcs1V15Sha256VerifyTb.ulSignatureLength = signatureLength;
      Cry_GddHaePkcs1V15Sha256VerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_HaePkcs1V15Sha256VerifyMainFunction             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureVerifyCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaePkcs1V15Sha256VerifyStart() or               **
**                        Cry_HaePkcs1V15Sha256VerifyUpdate(). For            **
**                        Cry_HaePkcs1V15Sha256VerifyFinish invocation of     **
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
**                        Cry_GddHaePkcs1V15Sha256VerifyTb,                   **
**                        Cry_GddHaePkcs1V15Sha256VerifyContext,              **
**                        Cry_GaaHaePkcs1V15Sha256Digest                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_Sha256Start, Hmg_Sha256Update, Hmg_Sha256Finish,**
**                        Hmg_RsaPkcs1v15Verify,                              **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
void Cry_HaePkcs1V15Sha256VerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;
  uint8 LaaSha256Digest[HMG_SHA256_DIGEST_SIZE];

  LddReturnValue = E_OK;

  switch (Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr->length
      != (HMG_RSA_BYTES_SIZE + sizeof(uint32)))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblPrimitiveRet = Hmg_Sha256Start(&Cry_GddHaePkcs1V15Sha256VerifySha256Context);
      if (LblPrimitiveRet != HMG_SUCCESS)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      (void)memcpy((void*)Cry_GaaHaePkcs1V15Sha256VerifyModulus,
        (const void*)(Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr->data),
        HMG_RSA_BYTES_SIZE);

      Cry_GddHaePkcs1V15Sha256VerifyPublickey.exponent
        #if (defined(HIGH_BYTE_FIRST) && (CPU_BYTE_ORDER == HIGH_BYTE_FIRST))
        = ((uint32)(Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE]) << 24)
        + ((uint32)(Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 1]) << 16)
        + ((uint32)(Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 2]) << 8)
        + (uint32)(Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 3]);
        #else
        = (uint32)(Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE])
        + ((uint32)(Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 1]) << 8)
        + ((uint32)(Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 2]) << 16)
        + ((uint32)(Cry_GddHaePkcs1V15Sha256VerifyTb.pPublicKeyPtr->data[HMG_RSA_BYTES_SIZE + 3]) << 24);
        #endif

      Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblPrimitiveRet = Hmg_Sha256Update(&Cry_GddHaePkcs1V15Sha256VerifySha256Context,
      Cry_GddHaePkcs1V15Sha256VerifyTb.pDataPtr,
      Cry_GddHaePkcs1V15Sha256VerifyTb.ulDataLength);
    if (LblPrimitiveRet != HMG_SUCCESS)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    if (Cry_GddHaePkcs1V15Sha256VerifyTb.ulSignatureLength < HMG_RSA_BYTES_SIZE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

      LblPrimitiveRet = Hmg_Sha256Finish(&Cry_GddHaePkcs1V15Sha256VerifySha256Context,
        LaaSha256Digest);
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
        Cry_GddHaePkcs1V15Sha256VerifyTb.pSignaturePtr,
        LaaSha256Digest,
        HMG_SHA_256,
        &Cry_GddHaePkcs1V15Sha256VerifyPublickey);
      /* polyspace +9 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      /* polyspace +8 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      if (LblPrimitiveRet == HMG_SUCCESS)
      {
        *(Cry_GddHaePkcs1V15Sha256VerifyTb.pResultPtr) = CSM_E_VER_OK;
      }
      else
      {
        *(Cry_GddHaePkcs1V15Sha256VerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaePkcs1V15Sha256VerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY == STD_ON) */
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
