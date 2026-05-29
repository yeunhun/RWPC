/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmEcdsaSha256Verify.c                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HAE HSM ECDSA SHA256 Verify Interface    **
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
** 1.0.0     3-Apr-2020    JaeHyun      Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HAE HSM ECDSA SHA256 Verify */
#include "Cry_HaeHsmEcdsaSha256Verify.h"

#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_HAEHSMECDSASHA256VERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_Hash.h"
#include "CryptoService_Ecc.h"
#include "string.h"

/*******************************************************************************
**                     Macros                                                 **
*******************************************************************************/
#define HSM_ECC_KEY_BYTE_SIZE                           ((uint32)(32))

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeHsmEcdsaSha256Verify Transfer buffer*/
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
} Cry_HaeHsmEcdsaSha256VerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaeHsmEcdsaSha256Digest[SHA256_DIGEST_SIZE];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HSMAPI_CTX_t Cry_GddHaeHsmEcdsaSha256VerifyContext;

static Cry_HaeHsmEcdsaSha256VerifyTransferBuffer Cry_GddHaeHsmEcdsaSha256VerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256VerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr);

static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength);

static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr);

#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmEcdsaSha256VerifyInit                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the ECDSA module.            **
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
**                      Cry_GddHaeHsmEcdsaSha256VerifyTb,                      **
**                      Cry_GddHaeHsmEcdsaSha256VerifyContext,                 **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmEcdsaSha256VerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmEcdsaSha256VerifyTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddHaeHsmEcdsaSha256VerifyTb.pDataPtr = NULL_PTR;
  Cry_GddHaeHsmEcdsaSha256VerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeHsmEcdsaSha256VerifyTb.pSignaturePtr = NULL_PTR;
  Cry_GddHaeHsmEcdsaSha256VerifyTb.ulSignatureLength = CSM_ZERO;
  Cry_GddHaeHsmEcdsaSha256VerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeHsmEcdsaSha256VerifyContext, 0x00,
    sizeof(HSMAPI_CTX_t));

  (void)memset((void*)Cry_GaaHaeHsmEcdsaSha256Digest, 0x00, SHA256_DIGEST_SIZE);
}

/*******************************************************************************
** Function Name        : Cry_InternalHaeHsmEcdsaSha256VerifyStart            **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM ECDSA, so that it is             **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmEcdsaSha256VerifyMainFunction() can process**
**                        initialisation                                      **
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
**                        Cry_GddHaeHsmEcdsaSha256VerifyTb                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_EccEcdsaVerifyStart,                            **
*******************************************************************************/
static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256VerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  LusKeyNum = CSM_ZERO;
  /* polyspace +2 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
  /* polyspace +1 MISRA-C3:18.1,D4.1,D4.14 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
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
    LddReturnValue = HSM_EccEcdsaVerifyStart(
      &Cry_GddHaeHsmEcdsaSha256VerifyContext,
      LusKeyNum);

    if (LddReturnValue != E_OK)
    {
      LddReturnValue = E_NOT_OK;

      HSM_HaeGetErrorCode();
    }
  }

  if (LddReturnValue == E_OK)
  {
    Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState = JOB_DONE;
  }
  else
  {
    Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_InternalHaeHsmEcdsaSha256VerifyUpdate           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of hash         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmEcdsaSha256VerifyMainFunction() can process**
**                        the input                                           **
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
**                        Cry_GddHaeHsmEcdsaSha256VerifyTb,                    **
**                        Cry_GddHaeHsmEcdsaSha256VerifyContext                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        HSM_EccEcdsaVerifyUpdate, HSM_WaitResp,                 **
*******************************************************************************/
static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  HSMAPI_CTX_t LddHaeHsmSha256Context;
	uint32 LulTimeout;
	uint32 LulRemainingLength;
	uint32 LulTxLength;
	const uint8* LpData;
	uint32 LulTextIndex;

  LulTextIndex = CSM_ZERO;

	(void)memset((void*)&LddHaeHsmSha256Context, 0x00, sizeof(HSMAPI_CTX_t));

  CSM_PARAM_UNUSED(cfgId);

  LddReturnValue = HSM_Sha256Start(&LddHaeHsmSha256Context);

  if (LddReturnValue == E_OK)
  {
    LddReturnValue = E_NOT_OK;

    LulRemainingLength = dataLength;
    LpData = dataPtr;
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The length is checked" */
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
    LddReturnValue = HSM_Sha256Finish(
      &LddHaeHsmSha256Context, Cry_GaaHaeHsmEcdsaSha256Digest);
  }

  /* HSM_EccEcdsaVerifyFinish will be called in the finish function */

  if (LddReturnValue != E_OK)
  {
    LddReturnValue = E_NOT_OK;
    HSM_HaeGetErrorCode();
  }

  if (LddReturnValue == E_OK)
  {
    Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState = JOB_DONE;
  }
  else
  {
    Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_InternalHaeHsmEcdsaSha256VerifyFinish           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the ECC     **
**                        ECDSA computation and store the result into the     **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmEcdsaSha256VerifyMainFunction() can       **
**                        finish the computation and store the result in the  **
**                        memory location given                               **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, signaturePtr, signatureLength, resultPtr     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
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
**                        Cry_GddHaeHsmEcdsaSha256VerifyTb,                    **
**                        Cry_GddHaeHsmEcdsaSha256VerifyContext                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        HSM_EccEcdsaVerifyFinish                                **
*******************************************************************************/
static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  uint32 LulTimeout;
  uint8 LucVerifyResult;
  ECC_ECDSA_SIGN_t srcSign;

  /* polyspace +1 MISRA-C3:11.3,11.8 [Justified:Low] "No Impact of this rule violation" */
  Csm_HaeHsmEcdsaSignatureType *destResult = (Csm_HaeHsmEcdsaSignatureType *)signaturePtr;

  LucVerifyResult = (uint8)HSM_VERIFY_FAILURE;

  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED(signatureLength);

  /* polyspace-begin MISRA-C3:18.1,D4.1,D4.11,D4.14 RTE:IDP RTE:STD_LIB RTE:IDP [Justified:Low] "No Impact of this rule violation" */
  memcpy((void*)(srcSign.r), (const void*)(destResult->pSignatureR), ECC_BYTES_SIZE);
  memcpy((void*)(srcSign.s), (const void*)(destResult->pSignatureS), ECC_BYTES_SIZE);
  /* polyspace-end MISRA-C3:18.1,D4.1,D4.11,D4.14 RTE:IDP RTE:STD_LIB RTE:IDP */

  LddReturnValue = HSM_EccEcdsaVerifyUpdate(
    &Cry_GddHaeHsmEcdsaSha256VerifyContext,
    (const uint8*)Cry_GaaHaeHsmEcdsaSha256Digest,
     &srcSign);



  if (LddReturnValue == E_OK)
  {
    LulTimeout = CSM_ZERO;
    do
    {
      LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmEcdsaSha256VerifyContext.jobId);
      LulTimeout++;
    } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

    if (LddReturnValue != E_OK)
    {
      (void)HSM_CancelJob(Cry_GddHaeHsmEcdsaSha256VerifyContext.jobId);
    }
  }

  if (LddReturnValue == E_OK)
  {
    LddReturnValue = HSM_EccEcdsaVerifyFinish(
      &Cry_GddHaeHsmEcdsaSha256VerifyContext, &LucVerifyResult);

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

  /* Update job state to NO_JOB irrespective of the result */
  Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;

  return (LddReturnValue);
}



/*******************************************************************************
** Function Name        : Cry_HaeHsmEcdsaSha256VerifyStart                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM ECDSA, so that it is             **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmEcdsaSha256VerifyMainFunction() can process**
**                        initialisation                                      **
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
**                        Cry_GddHaeHsmEcdsaSha256VerifyTb                    **
**                                                                            **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmEcdsaSha256VerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState)
  {
    Cry_HaeHsmEcdsaSha256VerifyInit();

    Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState = JOB_START;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      LddReturnValue = Cry_InternalHaeHsmEcdsaSha256VerifyStart(cfgPtr, keyPtr);
    }
    else
    {
      Cry_GddHaeHsmEcdsaSha256VerifyTb.pPublicKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeHsmEcdsaSha256VerifyUpdate                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of hash         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmEcdsaSha256VerifyMainFunction() can process**
**                        the input                                           **
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
** Remarks              :                                                     **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmEcdsaSha256VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState)
  {
    Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
    {
      LddReturnValue = Cry_InternalHaeHsmEcdsaSha256VerifyUpdate(
        cfgId, dataPtr, dataLength);
    }
    else
    {
      Cry_GddHaeHsmEcdsaSha256VerifyTb.pDataPtr = dataPtr;
      Cry_GddHaeHsmEcdsaSha256VerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeHsmEcdsaSha256VerifyFinish                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the ECC     **
**                        ECDSA computation and store the result into the     **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmEcdsaSha256VerifyMainFunction() can       **
**                        finish the computation and store the result in the  **
**                        memory location given                               **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, signaturePtr, signatureLength, resultPtr     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_SMALL_BUFFER: provided buffer is too small to **
**                                            store the result                **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmEcdsaSha256VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState)
  {
    if (signatureLength < (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
    {
      LddReturnValue = E_NOT_OK;
    }
    else
    {
      Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState = JOB_FINISH;

      if (Csm_SignatureVerifyServiceHasCallback() == FALSE)
      {
        LddReturnValue = Cry_InternalHaeHsmEcdsaSha256VerifyFinish(
        cfgId, signaturePtr, signatureLength, resultPtr);
      }
      else
      {
        Cry_GddHaeHsmEcdsaSha256VerifyTb.pSignaturePtr = signaturePtr;
        Cry_GddHaeHsmEcdsaSha256VerifyTb.ulSignatureLength = signatureLength;
        Cry_GddHaeHsmEcdsaSha256VerifyTb.pResultPtr = resultPtr;
      }
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
** Function Name        : Cry_HaeHsmEcdsaSha256VerifyMainFunction              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureVerifyCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeHsmEcdsaSha256VerifyStart() or               **
**                        Cry_HaeHsmEcdsaSha256VerifyUpdate(). For            **
**                        Cry_HaeHsmEcdsaSha256VerifyFinish invocation of     **
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
**                        Cry_GddHaeHsmEcdsaSha256VerifyTb,                   **
**                        Cry_GddHaeHsmEcdsaSha256VerifyContext               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_EccEcdsaVerifyStart, HSM_EccEcdsaVerifyUpdate,  **
**                        HSM_WaitResp,                                       **
**                        HSM_EccEcdsaVerifyFinish,                           **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
void Cry_HaeHsmEcdsaSha256VerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;

  switch (Cry_GddHaeHsmEcdsaSha256VerifyTb.ucJobState)
  {
  case JOB_START:
    LddReturnValue = Cry_InternalHaeHsmEcdsaSha256VerifyStart(
      NULL_PTR,
      Cry_GddHaeHsmEcdsaSha256VerifyTb.pPublicKeyPtr);

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LddReturnValue = Cry_InternalHaeHsmEcdsaSha256VerifyUpdate(
      CSM_ZERO,
      Cry_GddHaeHsmEcdsaSha256VerifyTb.pDataPtr,
      Cry_GddHaeHsmEcdsaSha256VerifyTb.ulDataLength);

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    LddReturnValue = Cry_InternalHaeHsmEcdsaSha256VerifyFinish(
      CSM_ZERO,
      Cry_GddHaeHsmEcdsaSha256VerifyTb.pSignaturePtr,
      Cry_GddHaeHsmEcdsaSha256VerifyTb.ulSignatureLength,
      Cry_GddHaeHsmEcdsaSha256VerifyTb.pResultPtr);

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

#endif /* (CSM_SIGNATURE_HAEHSMECDSASHA256VERIFY == STD_ON) */
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
