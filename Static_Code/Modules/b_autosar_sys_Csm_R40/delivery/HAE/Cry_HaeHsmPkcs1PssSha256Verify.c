/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmPkcs1PssSha256Verify.c                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM Pkcs1PssSha256 Verify Interface     **
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
** 1.0.1     27-Apr-2020   JaeHyun      Redmine #23211      		          **
** 1.0.0     03-Apr-2020   YongSung     Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM Pkcs1Pss Sha256 */
#include "Cry_HaeHsmPkcs1PssSha256Verify.h"
/* Signature Interface */
#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_HAEHSMPKCS1PSSSHA256VERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_RsaPkcs1.h"
#include "CryptoService_Hash.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSMPkcs1PssSha256Verify Transfer buffer*/
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
} Cry_HaeHsmPkcs1PssSha256VerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaeHsmPkcs1PssSha256Digest[SHA256_DIGEST_SIZE];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

static uint32 Cry_GusHaeHsmPkcs1PssSha256SaltLength;

#define CSM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HSMAPI_CTX_t Cry_GddHaeHsmPkcs1PssSha256VerifyContext;

/* Global structure variable for HSM Pkcs1Pss Sha256 transfer buffer */
static Cry_HaeHsmPkcs1PssSha256VerifyTransferBuffer Cry_GddHaeHsmPkcs1PssSha256VerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmPkcs1PssSha256VerifyInit                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Pkcs1PssSha256 module.   **
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
**                      Cry_GddHaeHsmPkcs1PssSha256VerifyTb                   **
**                      Cry_GddHaeHsmPkcs1PssSha256VerifyContext,             **
**                      Cry_GaaHaeHsmPkcs1PssSha256Digest,                    **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_HaeHsmPkcs1PssSha256VerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pDataPtr = NULL_PTR;
  Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pSignaturePtr = NULL_PTR;
  Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ulSignatureLength = CSM_ZERO;
  Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeHsmPkcs1PssSha256VerifyContext, 0x00,
    sizeof(HSMAPI_CTX_t));

  (void)memset((void*)Cry_GaaHaeHsmPkcs1PssSha256Digest, 0x00, SHA256_DIGEST_SIZE);

  Cry_GusHaeHsmPkcs1PssSha256SaltLength=CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmPkcs1PssSha256VerifyStart                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM Pkcs1Pss Sha256, so that it is   **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmPkcs1PssSha256VerifyMainFunction() can    **
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
**                        Cry_GddHaeHsmPkcs1PssSha256VerifyTb                 **
**                        Cry_GddHaeHsmPkcs1PssSha256VerifyContext,           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeHsmPkcs1PssSha256VerifyInit,                 **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        HSM_RsaPkcs1PssVerifyStart                          **
**                        HSM_HaeGetErrorCode                                 **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPkcs1PssSha256VerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState)
  {
    Cry_HaeHsmPkcs1PssSha256VerifyInit();

    Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_START;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      LusKeyNum = CSM_ZERO;
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        LusKeyNum = keyPtr->data[CSM_ZERO];
      }
      else if (keyPtr->length == CSM_TWO)
      {
        LusKeyNum = keyPtr->data[CSM_ZERO];
        /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
      	LusKeyNum |= (keyPtr->data[CSM_ONE]) << 8;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_RsaPkcs1PssVerifyStart(
          &Cry_GddHaeHsmPkcs1PssSha256VerifyContext,
          LusKeyNum);

        if (LddReturnValue != E_OK)
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeHsmPkcs1PssSha256VerifyUpdate                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha256   **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmPkcs1PssSha256VerifyMainFunction() can    **
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
**                        Cry_GddHaeHsmPkcs1PssSha256VerifyTb                 **
**                        Cry_GddHaeHsmPkcs1PssSha256VerifyContext            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        HSM_Sha256Start, HSM_Sha256Update, HSM_Sha256Finish,**
**                        HSM_WaitResp,                                       **
**                        HSM_HaeGetErrorCode                                 **
**                        HSM_CancelJob                                       **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPkcs1PssSha256VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  HSMAPI_CTX_t LddHaeHsmSha256Context;
  uint32 LulTimeout;
  uint32 LulRemainingLength;
  uint32 LulTxLength;
  const uint8* LpData;
  uint32 LulTextIndex;
  const Csm_HaeHsmPkcs1PssDataType* LpPkcs1PssData;

  LddReturnValue = E_OK;
  LulTextIndex = CSM_ZERO;

  /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
  LpPkcs1PssData = (const Csm_HaeHsmPkcs1PssDataType*)dataPtr;

  (void)memset((void*)&LddHaeHsmSha256Context, 0x00, sizeof(HSMAPI_CTX_t));

  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED(dataLength);

  if (JOB_DONE == Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      LddReturnValue = HSM_Sha256Start(&LddHaeHsmSha256Context);

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = E_NOT_OK;

        /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        LulRemainingLength = LpPkcs1PssData->ulDataLength;
        LpData = LpPkcs1PssData->pData;

        while (LulRemainingLength > CSM_ZERO)
        {
          if (LulRemainingLength > HSM_HAE_SHA256_MAX_LENGTH)
          {
            LulTxLength = HSM_HAE_SHA256_MAX_LENGTH;
          }
          else
          {
            LulTxLength = LulRemainingLength;
          }

          LddReturnValue = HSM_Sha256Update(&LddHaeHsmSha256Context,
            &LpData[LulTextIndex], LulTxLength);

          if (LddReturnValue == E_OK)
          {
            LulTimeout = CSM_ZERO;
            do
            {
              LddReturnValue = HSM_WaitResp(LddHaeHsmSha256Context.jobId);
              LulTimeout++;
            } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

            if (LddReturnValue == E_OK)
            {
              LulRemainingLength -= LulTxLength;
              LulTextIndex += LulTxLength;
            }
            else
            {
              LulRemainingLength = CSM_ZERO;
              (void)HSM_CancelJob(LddHaeHsmSha256Context.jobId);
            }
          }
          else
          {
            LulRemainingLength = CSM_ZERO;
          }
        }
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_Sha256Finish(
          &LddHaeHsmSha256Context, Cry_GaaHaeHsmPkcs1PssSha256Digest);
      }

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }

      if (LddReturnValue == E_OK)
      {
        /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        Cry_GusHaeHsmPkcs1PssSha256SaltLength = LpPkcs1PssData->ulSaltLength;
        Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pDataPtr = dataPtr;
      Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeHsmPkcs1PssSha256VerifyFinish                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1Pss**
**                        Sha256 computation and store the result into the    **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmPkcs1PssSha256VerifyMainFunction() can    **
**                        finish the computation and store the result in the  **
**                        memory location given                               **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, signaturePtr, signatureLength                **
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
**                        Cry_GddHaeHsmPkcs1PssSha256VerifyTb                 **
**                        Cry_GddHaeHsmPkcs1PssSha256VerifyContext,           **
**                        Cry_GaaHaeHsmPkcs1PssSha256Digest                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        HSM_RsaPkcs1PssVerifyUpdate, HSM_WaitResp,          **
**                        HSM_RsaPkcs1PssVerifyFinish                         **
**                        HSM_HaeGetErrorCode                                 **
**                        HSM_CancelJob                                       **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPkcs1PssSha256VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  uint32 LulTimeout;
  uint8 LucVerifyResult;

  LddReturnValue = E_OK;
  LucVerifyResult = (uint8)HSM_VERIFY_FAILURE;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState)
  {
    Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_FINISH;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      if (signatureLength < HAC_RSA_BYTES_SIZE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_RsaPkcs1PssVerifyUpdate(
          &Cry_GddHaeHsmPkcs1PssSha256VerifyContext,
          (const uint8*)Cry_GaaHaeHsmPkcs1PssSha256Digest,
          signaturePtr, Cry_GusHaeHsmPkcs1PssSha256SaltLength);

        if (LddReturnValue == E_OK)
        {
          LulTimeout = CSM_ZERO;
          do
          {
            LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmPkcs1PssSha256VerifyContext.jobId);
            LulTimeout++;
          } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

          if (LddReturnValue != E_OK)
          {
            (void)HSM_CancelJob(Cry_GddHaeHsmPkcs1PssSha256VerifyContext.jobId);
          }
        }

        if (LddReturnValue == E_OK)
        {
          LddReturnValue = HSM_RsaPkcs1PssVerifyFinish(
            &Cry_GddHaeHsmPkcs1PssSha256VerifyContext, &LucVerifyResult);

          if (LddReturnValue == E_OK)
          {
            if (LucVerifyResult == (uint8)HSM_VERIFY_SUCCESS)
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
        }

        if (LddReturnValue != E_OK)
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pSignaturePtr = signaturePtr;
      Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ulSignatureLength = signatureLength;
      Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pResultPtr = resultPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmPkcs1PssSha256VerifyMainFunction          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureVerifyCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeHsmPkcs1PssSha256VerifyStart() or            **
**                        Cry_HaeHsmPkcs1PssSha256VerifyUpdate(). For         **
**                        Cry_HaeHsmPkcs1PssSha256VerifyFinish invocation of  **
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
**                        Cry_GddHaeHsmPkcs1PssSha256VerifyTb                 **
**                        Cry_GddHaeHsmPkcs1PssSha256VerifyContext,           **
**                        Cry_GaaHaeHsmPkcs1PssSha256Digest                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_RsaPkcs1PssVerifyStart                          **
**                        HSM_Sha256Start, HSM_Sha256Update, HSM_Sha256Finish,**
**                        HSM_RsaPkcs1PssVerifyUpdate, HSM_WaitResp,          **
**                        HSM_RsaPkcs1PssVerifyFinish,                        **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
void Cry_HaeHsmPkcs1PssSha256VerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;
  HSMAPI_CTX_t LddHaeHsmSha256Context;
  uint32 LulTimeout;
  uint32 LulRemainingLength;
  uint32 LulTxLength;
  uint8 LucVerifyResult;
  const uint8* LpData;
  uint32 LulTextIndex;
  const Csm_HaeHsmPkcs1PssDataType* LpPkcs1PssData;

  LddReturnValue = E_OK;
  LulTextIndex = CSM_ZERO;
  LucVerifyResult = (uint8)HSM_VERIFY_FAILURE;

  (void)memset((void*)&LddHaeHsmSha256Context, 0x00, sizeof(HSMAPI_CTX_t));

  switch (Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState)
  {
  case JOB_START:
    LusKeyNum = CSM_ZERO;
    /* polyspace +11 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +10 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr->length == CSM_ONE)
    {
      LusKeyNum = Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr->data[CSM_ZERO];
    }
    else if (Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr->length == CSM_TWO)
    {
      LusKeyNum = Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr->data[CSM_ZERO];
      /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
      LusKeyNum |= (Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr->data[CSM_ONE]) << 8;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = HSM_RsaPkcs1PssVerifyStart(
        &Cry_GddHaeHsmPkcs1PssSha256VerifyContext,
        LusKeyNum);

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:

    /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
    LpPkcs1PssData = (const Csm_HaeHsmPkcs1PssDataType*)Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pDataPtr;

    LddReturnValue = HSM_Sha256Start(&LddHaeHsmSha256Context);

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = E_NOT_OK;

      /* polyspace +2 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      /* polyspace +1 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      LulRemainingLength = LpPkcs1PssData->ulDataLength;
      LpData = LpPkcs1PssData->pData;

      while (LulRemainingLength > CSM_ZERO)
      {
        if (LulRemainingLength > HSM_HAE_SHA256_MAX_LENGTH)
        {
          LulTxLength = HSM_HAE_SHA256_MAX_LENGTH;
        }
        else
        {
          LulTxLength = LulRemainingLength;
        }

        LddReturnValue = HSM_Sha256Update(&LddHaeHsmSha256Context,
          &LpData[LulTextIndex], LulTxLength);

        if (LddReturnValue == E_OK)
        {
          LulTimeout = CSM_ZERO;
          do
          {
            LddReturnValue = HSM_WaitResp(LddHaeHsmSha256Context.jobId);
            LulTimeout++;
          } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

          if (LddReturnValue == E_OK)
          {
            LulRemainingLength -= LulTxLength;
            LulTextIndex += LulTxLength;
          }
          else
          {
            LulRemainingLength = CSM_ZERO;
            (void)HSM_CancelJob(LddHaeHsmSha256Context.jobId);
          }
        }
        else
        {
          LulRemainingLength = CSM_ZERO;
        }
      }
    }

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = HSM_Sha256Finish(
        &LddHaeHsmSha256Context, Cry_GaaHaeHsmPkcs1PssSha256Digest);
    }

    if (LddReturnValue != E_OK)
    {
      LddReturnValue = E_NOT_OK;
      HSM_HaeGetErrorCode();
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GusHaeHsmPkcs1PssSha256SaltLength = LpPkcs1PssData->ulSaltLength;
      Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    if (Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ulSignatureLength < HAC_RSA_BYTES_SIZE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = HSM_RsaPkcs1PssVerifyUpdate(
        &Cry_GddHaeHsmPkcs1PssSha256VerifyContext,
        (const uint8*)Cry_GaaHaeHsmPkcs1PssSha256Digest,
       Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pSignaturePtr, Cry_GusHaeHsmPkcs1PssSha256SaltLength);

      if (LddReturnValue == E_OK)
      {
        LulTimeout = CSM_ZERO;
        do
        {
          LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmPkcs1PssSha256VerifyContext.jobId);
          LulTimeout++;
        } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

        if (LddReturnValue != E_OK)
        {
          (void)HSM_CancelJob(Cry_GddHaeHsmPkcs1PssSha256VerifyContext.jobId);
        }
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_RsaPkcs1PssVerifyFinish(
          &Cry_GddHaeHsmPkcs1PssSha256VerifyContext, &LucVerifyResult);

        if (LddReturnValue == E_OK)
        {
	  /* polyspace +9 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +8 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          if (LucVerifyResult == (uint8)HSM_VERIFY_SUCCESS)
          {
            *(Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pResultPtr) = CSM_E_VER_OK;
          }
          else
          {
            *(Cry_GddHaeHsmPkcs1PssSha256VerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
          }
        }
      }

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SIGNATURE_HAEHSMPKCS1PSSSHA256VERIFY == STD_ON) */
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
