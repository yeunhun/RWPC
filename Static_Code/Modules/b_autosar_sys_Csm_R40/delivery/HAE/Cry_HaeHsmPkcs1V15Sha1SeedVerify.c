/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmPkcs1V15Sha1SeedVerify.c                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HAE HSM Pkcs1V15 Sha1 Seed Verify       **
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
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.0.5     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.4     04-Dec-2019   Sinil        Redmine #20495                        **
** 1.0.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.2     17-Apr-2018   Sinil        Redmine #12352                        **
** 1.0.1     10-Nov-2017   Sinil        Redmine #10550                        **
** 1.0.0     11-Aug-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_HaeHsmPkcs1V15Sha1SeedVerify.h"
#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA1SEEDVERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_RsaPkcs1.h"
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
} Cry_HaeHsmPkcs1V15Sha1SeedVerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaeHsmPkcs1V15Sha1SeedDigest[SHA160_DIGEST_SIZE];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HSMAPI_CTX_t Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext;

static Cry_HaeHsmPkcs1V15Sha1SeedVerifyTransferBuffer Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmPkcs1V15Sha1SeedVerifyInit                  **
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
**                      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb,                **
**                      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext,           **
**                      Cry_GaaHaeHsmPkcs1V15Sha1SeedDigest,                  **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmPkcs1V15Sha1SeedVerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pDataPtr = NULL_PTR;
  Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pSignaturePtr = NULL_PTR;
  Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ulSignatureLength = CSM_ZERO;
  Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext, 0x00,
    sizeof(HSMAPI_CTX_t));

  (void)memset((void*)Cry_GaaHaeHsmPkcs1V15Sha1SeedDigest, 0x00, SHA160_DIGEST_SIZE);
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmPkcs1V15Sha1SeedVerifyStart               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HAE HSM Pkcs1V15 Sha1, so that if    **
**                        is able to process the input data                   **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmPkcs1V15Sha1SeedVerifyMainFunction() can  **
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
**                        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb,              **
**                        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext,         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeHsmPkcs1V15Sha1SeedVerifyInit,               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        HSM_RsaPkcs1v15VerifyStart,                         **
**                        HSM_HaeGetErrorCode                                 **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPkcs1V15Sha1SeedVerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
    Cry_HaeHsmPkcs1V15Sha1SeedVerifyInit();

    Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_START;

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
        LddReturnValue = HSM_RsaPkcs1v15VerifyStart(
          &Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext,
          LusKeyNum);

        if (LddReturnValue != E_OK)
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeHsmPkcs1V15Sha1SeedVerifyUpdate              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha1     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmPkcs1V15Sha1SeedVerifyMainFunction() can  **
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
**                        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb,              **
**                        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext,         **
**                        Cry_GaaHaeHsmPkcs1V15Sha1SeedDigest                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback               **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPkcs1V15Sha1SeedVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  uint8 LucIndex;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
    Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      if (dataLength > SHA160_DIGEST_SIZE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        /* polyspace +1 MISRA-C3:D4.14 Justified:Low] "The length is checked" */
        for (LucIndex = CSM_ZERO; LucIndex < dataLength; LucIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          Cry_GaaHaeHsmPkcs1V15Sha1SeedDigest[LucIndex] = dataPtr[LucIndex];
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pDataPtr = dataPtr;
      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeHsmPkcs1V15Sha1SeedVerifyFinish              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1V15**
**                        Sha1 computation and store the result into the      **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmPkcs1V15Sha1SeedVerifyMainFunction() can  **
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
**                        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb,              **
**                        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext,         **
**                        Cry_GaaHaeHsmPkcs1V15Sha1SeedDigest                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        HSM_RsaPkcs1v15Sha160VerifyUpdate, HSM_WaitResp,    **
**                        HSM_RsaPkcs1v15VerifyFinish                         **
**                        HSM_HaeGetErrorCode                                 **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPkcs1V15Sha1SeedVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  uint32 LulTimeout;
  uint8 LucVerifyResult;

  LddReturnValue = E_OK;
  LucVerifyResult = (uint8)HSM_VERIFY_FAILURE;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
    Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_FINISH;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      if (signatureLength < HAC_RSA_BYTES_SIZE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_RsaPkcs1v15Sha160VerifyUpdate(
          &Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext,
          (const uint8*)Cry_GaaHaeHsmPkcs1V15Sha1SeedDigest,
          signaturePtr);

        if (LddReturnValue == E_OK)
        {
          LulTimeout = CSM_ZERO;
          do
          {
            LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext.jobId);
            LulTimeout++;
          } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

          if (LddReturnValue != E_OK)
          {
            (void)HSM_CancelJob(Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext.jobId);
          }
        }

        if (LddReturnValue == E_OK)
        {
          LddReturnValue = HSM_RsaPkcs1v15VerifyFinish(
            &Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext, &LucVerifyResult);

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

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pSignaturePtr = signaturePtr;
      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ulSignatureLength = signatureLength;
      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_HaeHsmPkcs1V15Sha1SeedVerifyMainFunction        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureVerifyCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeHsmPkcs1V15Sha1SeedVerifyStart() or          **
**                        Cry_HaeHsmPkcs1V15Sha1SeedVerifyUpdate(). For       **
**                        Cry_HaeHsmPkcs1V15Sha1SeedVerifyFinish invocation of**
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
**                        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb,              **
**                        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext,         **
**                        Cry_GaaHaeHsmPkcs1V15Sha1SeedDigest                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_RsaPkcs1v15VerifyStart                          **
**                        HSM_RsaPkcs1v15Sha160VerifyUpdate, HSM_WaitResp,    **
**                        HSM_RsaPkcs1v15VerifyFinish,                        **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
**                        HSM_HaeGetErrorCode                                 **
**                        HSM_CancelJob                                       **
*******************************************************************************/
void Cry_HaeHsmPkcs1V15Sha1SeedVerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;
  uint32 LulTimeout;
  uint8 LucVerifyResult;
  uint8 LucIndex;

  LddReturnValue = E_OK;
  LucVerifyResult = (uint8)HSM_VERIFY_FAILURE;

  switch (Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
  case JOB_START:
    LusKeyNum = CSM_ZERO;
    /* polyspace +11 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +10 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->length == CSM_ONE)
    {
      LusKeyNum = Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->data[CSM_ZERO];
    }
    else if (Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->length == CSM_TWO)
    {
      LusKeyNum = Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->data[CSM_ZERO];
      /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
      LusKeyNum |= (Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->data[CSM_ONE]) << 8;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = HSM_RsaPkcs1v15VerifyStart(
        &Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext,
        LusKeyNum);

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    if (Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ulDataLength > SHA160_DIGEST_SIZE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      for (LucIndex = CSM_ZERO;
        LucIndex < Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ulDataLength; LucIndex++)
      {
	/* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	/* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
        Cry_GaaHaeHsmPkcs1V15Sha1SeedDigest[LucIndex]
          = Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pDataPtr[LucIndex];
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
    }

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    if (Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ulSignatureLength
      < HAC_RSA_BYTES_SIZE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = HSM_RsaPkcs1v15Sha160VerifyUpdate(
        &Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext,
        (const uint8*)Cry_GaaHaeHsmPkcs1V15Sha1SeedDigest,
        Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pSignaturePtr);

      if (LddReturnValue == E_OK)
      {
        LulTimeout = CSM_ZERO;
        do
        {
          LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext.jobId);
          LulTimeout++;
        } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

        if (LddReturnValue != E_OK)
        {
          (void)HSM_CancelJob(Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext.jobId);
        }
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_RsaPkcs1v15VerifyFinish(
          &Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyContext, &LucVerifyResult);

        if (LddReturnValue == E_OK)
        {
          if (LucVerifyResult == (uint8)HSM_VERIFY_SUCCESS)
          {
	    /* polyspace +9 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	    /* polyspace +8 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
            *(Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pResultPtr) = CSM_E_VER_OK;
          }
          else
          {
            *(Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
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
    Cry_GddHaeHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SIGNATURE_HAEHSMPKCS1V15SHA1SEEDVERIFY == STD_ON) */
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
