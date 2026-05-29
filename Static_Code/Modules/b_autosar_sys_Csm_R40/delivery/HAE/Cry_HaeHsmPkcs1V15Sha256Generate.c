/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmPkcs1V15Sha256Generate.c                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HAE HSM Pkcs1V15 Sha256 Generate        **
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
** 1.0.4     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.3     04-Dec-2019   Sinil        Redmine #20495                        **
** 1.0.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.1     17-Apr-2018   Sinil        Redmine #12352                        **
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
#include "Cry_HaeHsmPkcs1V15Sha256Generate.h"
#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
#if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA256GENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_RsaPkcs1.h"
#include "CryptoService_Hash.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_AsymPrivateKeyType* pPrivateKeyPtr;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  uint8* pResultPtr;
  uint32* pResultLengthPtr;
} Cry_HaeHsmPkcs1V15Sha256GenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HSMAPI_CTX_t Cry_GddHaeHsmPkcs1V15Sha256GenerateContext;

static Cry_HaeHsmPkcs1V15Sha256GenerateTransferBuffer Cry_GddHaeHsmPkcs1V15Sha256GenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmPkcs1V15Sha256GenerateInit                  **
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
** Remarks            : Global Variable(s)  :                                 **
**                      Cry_GddHaeHsmPkcs1V15Sha256GenerateTb,                **
**                      Cry_GddHaeHsmPkcs1V15Sha256GenerateContext,           **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmPkcs1V15Sha256GenerateInit(void)
{
  Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pPrivateKeyPtr = NULL_PTR;
  Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pDataPtr = NULL_PTR;
  Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pResultLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeHsmPkcs1V15Sha256GenerateContext, 0x00,
    sizeof(HSMAPI_CTX_t));
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmPkcs1V15Sha256GenerateStart               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever Pkcs1V15 Sha256, so that it **
**                        is able to process the input data                   **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmPkcs1V15Sha256GenerateMainFunction() can  **
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
**                        Cry_GddHaeHsmPkcs1V15Sha256GenerateTb,              **
**                        Cry_GddHaeHsmPkcs1V15Sha256GenerateContext,         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeHsmPkcs1V15Sha256GenerateInit,               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        HSM_RsaPkcs1v15SignStart                            **
**                        HSM_HaeGetErrorCode                                 **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPkcs1V15Sha256GenerateStart(const void* cfgPtr,
  const Csm_AsymPrivateKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState)
  {
    Cry_HaeHsmPkcs1V15Sha256GenerateInit();

    Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = JOB_START;

    if (Csm_SignatureGenerateServiceHasCallback() == FALSE)
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
        LddReturnValue = HSM_RsaPkcs1v15SignStart(
          &Cry_GddHaeHsmPkcs1V15Sha256GenerateContext,
          LusKeyNum);

        if (LddReturnValue != E_OK)
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pPrivateKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeHsmPkcs1V15Sha256GenerateUpdate              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha1     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmPkcs1V15Sha256GenerateMainFunction() can  **
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
**                        Cry_GddHaeHsmPkcs1V15Sha256GenerateTb,              **
**                        Cry_GddHaeHsmPkcs1V15Sha256GenerateContext          **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        HSM_Sha256Start, HSM_Sha256Update, HSM_Sha256Finish,**
**                        HSM_RsaPkcs1v15SignUpdate, HSM_WaitResp,            **
**                        HSM_HaeGetErrorCode                                 **
**                        HSM_CancelJob                                       **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPkcs1V15Sha256GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  HSMAPI_CTX_t LddHaeHsmSha256Context;
  uint8 LaaSha256ResultBuffer[SHA256_DIGEST_SIZE];
  uint32 LulTimeout;
  uint32 LulRemainingLength;
  uint32 LulTxLength;
  const uint8* LpData;
  uint32 LulTextIndex;

  LddReturnValue = E_OK;
  LulTextIndex = CSM_ZERO;

  (void)memset((void*)&LddHaeHsmSha256Context, 0x00, sizeof(HSMAPI_CTX_t));

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState)
  {
    Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureGenerateServiceHasCallback() == FALSE)
    {
      LddReturnValue = HSM_Sha256Start(&LddHaeHsmSha256Context);

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = E_NOT_OK;

        LulRemainingLength = dataLength;
        LpData = dataPtr;
        /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "The length is checked" */
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
	        /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
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
        (void)memset((void*)&LaaSha256ResultBuffer, 0x00, sizeof(LaaSha256ResultBuffer));

        LddReturnValue = HSM_Sha256Finish(
          &LddHaeHsmSha256Context, LaaSha256ResultBuffer);
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_RsaPkcs1v15SignUpdate(
          &Cry_GddHaeHsmPkcs1V15Sha256GenerateContext,
          LaaSha256ResultBuffer);

        if (LddReturnValue == E_OK)
        {
          LulTimeout = CSM_ZERO;
          do
          {
            LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmPkcs1V15Sha256GenerateContext.jobId);
            LulTimeout++;
          } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

          if (LddReturnValue != E_OK)
          {
            (void)HSM_CancelJob(Cry_GddHaeHsmPkcs1V15Sha256GenerateContext.jobId);
          }
        }
      }

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pDataPtr = dataPtr;
      Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeHsmPkcs1V15Sha256GenerateFinish              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1V15**
**                        Sha256 computation and store the result into the    **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmPkcs1V15Sha256GenerateMainFunction() can  **
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
**                        CSM_E_SMALL_BUFFER: provided buffer is too small to **
**                                            store the result                **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddHaeHsmPkcs1V15Sha256GenerateTb,              **
**                        Cry_GddHaeHsmPkcs1V15Sha256GenerateContext          **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        HSM_RsaPkcs1v15SignFinish                           **
**                        HSM_HaeGetErrorCode                                 **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPkcs1V15Sha256GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState)
  {
    Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = JOB_FINISH;

    if (Csm_SignatureGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*resultLengthPtr < HAC_RSA_BYTES_SIZE)
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_RsaPkcs1v15SignFinish(
          &Cry_GddHaeHsmPkcs1V15Sha256GenerateContext,
          resultPtr);

        if (LddReturnValue == E_OK)
        {
          *resultLengthPtr = HAC_RSA_BYTES_SIZE;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pResultPtr = resultPtr;
      Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pResultLengthPtr = resultLengthPtr;
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
** Function Name        : Cry_HaeHsmPkcs1V15Sha256GenerateMainFunction        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureGenerateCallbackNotification() with the**
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeHsmPkcs1V15Sha256GenerateStart() or          **
**                        Cry_HaeHsmPkcs1V15Sha256GenerateUpdate(). For       **
**                        Cry_HaeHsmPkcs1V15Sha256GenerateFinish invocation of**
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
**                        Cry_GddHaeHsmPkcs1V15Sha256GenerateTb,              **
**                        Cry_GddHaeHsmPkcs1V15Sha256GenerateContext          **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_RsaPkcs1v15SignStart, HSM_WaitResp,             **
**                        Csm_SignatureGenerateCallbackNotification,          **
**                        Csm_SignatureGenerateServiceFinishNotification      **
**                        HSM_HaeGetErrorCode                                 **
**                        HSM_CancelJob                                       **
*******************************************************************************/
void Cry_HaeHsmPkcs1V15Sha256GenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;
  HSMAPI_CTX_t LddHaeHsmSha256Context;
  uint8 LaaSha256ResultBuffer[SHA256_DIGEST_SIZE];
  uint32 LulTimeout;
  uint32 LulRemainingLength;
  uint32 LulTxLength;
  const uint8* LpData;
  uint32 LulTextIndex;

  LddReturnValue = E_OK;
  LulTextIndex = CSM_ZERO;

  (void)memset((void*)&LddHaeHsmSha256Context, 0x00, sizeof(HSMAPI_CTX_t));

  switch (Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState)
  {
  case JOB_START:
    LusKeyNum = CSM_ZERO;
    /* polyspace +12 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +12 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pPrivateKeyPtr->length == CSM_ONE)
    {
      LusKeyNum = Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pPrivateKeyPtr->data[CSM_ZERO];
    }
    else if (Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pPrivateKeyPtr->length == CSM_TWO)
    {
      LusKeyNum = Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pPrivateKeyPtr->data[CSM_ZERO];
      /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
      LusKeyNum |= (Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pPrivateKeyPtr->data[CSM_ONE]) << 8;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = HSM_RsaPkcs1v15SignStart(
        &Cry_GddHaeHsmPkcs1V15Sha256GenerateContext,
        LusKeyNum);

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
    }

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LddReturnValue = HSM_Sha256Start(&LddHaeHsmSha256Context);

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = E_NOT_OK;

      LulRemainingLength = Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ulDataLength;
      LpData = Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pDataPtr;

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
      (void)memset((void*)&LaaSha256ResultBuffer, 0x00, sizeof(LaaSha256ResultBuffer));

      LddReturnValue = HSM_Sha256Finish(
        &LddHaeHsmSha256Context, LaaSha256ResultBuffer);
    }

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = HSM_RsaPkcs1v15SignUpdate(
        &Cry_GddHaeHsmPkcs1V15Sha256GenerateContext,
        LaaSha256ResultBuffer);

      if (LddReturnValue == E_OK)
      {
        LulTimeout = CSM_ZERO;
        do
        {
          LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmPkcs1V15Sha256GenerateContext.jobId);
          LulTimeout++;
        } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

        if (LddReturnValue != E_OK)
        {
          (void)HSM_CancelJob(Cry_GddHaeHsmPkcs1V15Sha256GenerateContext.jobId);
        }
      }
    }

    if (LddReturnValue != E_OK)
    {
      LddReturnValue = E_NOT_OK;
      HSM_HaeGetErrorCode();
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
    }

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +4 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pResultLengthPtr)
      < HAC_RSA_BYTES_SIZE)
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = HSM_RsaPkcs1v15SignFinish(
        &Cry_GddHaeHsmPkcs1V15Sha256GenerateContext,
        (uint8*)(Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pResultPtr));

      if (LddReturnValue == E_OK)
      {
        *(Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.pResultLengthPtr)
          = HAC_RSA_BYTES_SIZE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeHsmPkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SIGNATURE_HAEHSMPKCS1V15SHA256GENERATE == STD_ON) */
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
