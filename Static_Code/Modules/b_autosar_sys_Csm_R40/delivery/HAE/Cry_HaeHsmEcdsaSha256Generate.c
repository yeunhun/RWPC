/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmEcdsaSha256Generate.c                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HAE HSM HAMC SHA256 Generate Interface  **
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
/* Header File for HAE HSM ECDSA SHA256 Generate */
#include "Cry_HaeHsmEcdsaSha256Generate.h"

#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
#if (CSM_SIGNATURE_HAEHSMECDSASHA256GENERATE == STD_ON)
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
/* Cry HaeHsmEcdsaSha256Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_AsymPrivateKeyType* pPrivateKeyPtr;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  uint8* pResultPtr;
  uint32* pResultLengthPtr;
} Cry_HaeHsmEcdsaSha256GenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HSMAPI_CTX_t Cry_GddHaeHsmEcdsaSha256GenerateContext;

static Cry_HaeHsmEcdsaSha256GenerateTransferBuffer Cry_GddHaeHsmEcdsaSha256GenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/

static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256GenerateStart(const void* cfgPtr,
  const Csm_AsymPrivateKeyType* keyPtr);

static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength);

static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32 *resultLengthPtr);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmEcdsaSha256GenerateInit                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the ECDSA Sha256 module.     **
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
**                      Cry_GddHaeHsmEcdsaSha256GenerateTb,                    **
**                      Cry_GddHaeHsmEcdsaSha256GenerateContext,               **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmEcdsaSha256GenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmEcdsaSha256GenerateTb.pPrivateKeyPtr = NULL_PTR;
  Cry_GddHaeHsmEcdsaSha256GenerateTb.pDataPtr = NULL_PTR;
  Cry_GddHaeHsmEcdsaSha256GenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeHsmEcdsaSha256GenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaeHsmEcdsaSha256GenerateTb.pResultLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeHsmEcdsaSha256GenerateContext, 0x00,
    sizeof(HSMAPI_CTX_t));
}

/*******************************************************************************
** Function Name        : Cry_InternalHaeHsmEcdsaSha256GenerateStart          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM ECDSA, so that it is             **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmEcdsaSha256GenerateMainFunction() can     **
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
**                        Cry_GddHaeHsmEcdsaSha256GenerateTb,                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_EcdsaSha256Start,                               **
**                        Cry_HaeHsmEcdsaSha256GenerateInit,                  **
**                        Csm_SignatureGenerateServiceHasCallback             **
*******************************************************************************/
static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256GenerateStart(const void* cfgPtr,
  const Csm_AsymPrivateKeyType* keyPtr)
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
    LddReturnValue =  HSM_EccEcdhStart(
      &Cry_GddHaeHsmEcdsaSha256GenerateContext,
      LusKeyNum);

    if (LddReturnValue != E_OK)
    {
      LddReturnValue = E_NOT_OK;
      HSM_HaeGetErrorCode();
    }
  }

  if (LddReturnValue == E_OK)
  {
    Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState = JOB_DONE;
  }
  else
  {
    Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_InternalHaeHsmEcdsaSha256GenerateUpdate         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of hash         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmEcdsaSha256GenerateMainFunction() can     **
**                        process the input data                              **
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
**                        Cry_GddHaeHsmEcdsaSha256GenerateTb,                 **
**                        Cry_GddHaeHsmEcdsaSha256GenerateContext             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_EcdsaSha256Update, HSM_WaitResp,                **
**                        Csm_SignatureGenerateServiceHasCallback             **
*******************************************************************************/
static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  HSMAPI_CTX_t LddHaeHsmSha256Context;
  uint8 LaaSha256ResultBuffer[SHA256_DIGEST_SIZE];
  uint32 LulTimeout;
  uint32 LulRemainingLength;
  uint32 LulTxLength;
  const uint8* LpData;
  const Csm_HaeHsmEcdsaDataType* LpEcsdsaData;
  uint32 LulTextIndex;

  LulTextIndex = CSM_ZERO;

  (void)memset((void*)&LddHaeHsmSha256Context, 0x00, sizeof(HSMAPI_CTX_t));

  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED(dataLength);

  /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
  LpEcsdsaData = (const Csm_HaeHsmEcdsaDataType*)dataPtr;

  LddReturnValue = HSM_Sha256Start(&LddHaeHsmSha256Context);

  if (LddReturnValue == E_OK)
  {
    LddReturnValue = E_NOT_OK;

    /* polyspace +2 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +1 MISRA-C3:18.1,D4.1,D4.14 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    LulRemainingLength = LpEcsdsaData->ulMessageLength;
    LpData = LpEcsdsaData->pMessage;

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
      /* polyspace +2 MISRA2012:11.8 [Justified:Low] "No Impact of this rule violation" */
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
    /* polyspace +4 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    LddReturnValue =  HSM_EccEcdsaSignUpdate(
      &Cry_GddHaeHsmEcdsaSha256GenerateContext,
      LaaSha256ResultBuffer, /* digest : Sha256 hash value with 32 byte */
      LpEcsdsaData->pSecretNumber /* secretNumer : random value */
      );

    if (LddReturnValue == E_OK)
    {
      LulTimeout = CSM_ZERO;
      do
      {
        LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmEcdsaSha256GenerateContext.jobId);
        LulTimeout++;
      } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

      if (LddReturnValue != E_OK)
      {
        (void)HSM_CancelJob(Cry_GddHaeHsmEcdsaSha256GenerateContext.jobId);
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
    Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState = JOB_DONE;
  }
  else
  {
    Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_InternalHaeHsmEcdsaSha256GenerateFinish         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the ECC     **
**                        ECDSA computation and store the result into the     **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmEcdsaSha256GenerateMainFunction() can     **
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
**                        Cry_GddHaeHsmEcdsaSha256GenerateTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hsm_EcdsaGenFinish                                  **
*******************************************************************************/
static Std_ReturnType Cry_InternalHaeHsmEcdsaSha256GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32 *resultLengthPtr)
{
  Std_ReturnType LddReturnValue;
  ECC_ECDSA_SIGN_t srcSign;
  Csm_HaeHsmEcdsaSignatureType *destResult;

  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(resultLengthPtr);

  /* polyspace +1 MISRA2012:11.3 [Justified:Low] "No Impact of this rule violation" */
  destResult = (Csm_HaeHsmEcdsaSignatureType *)resultPtr;

  LddReturnValue = HSM_EccEcdsaSignFinish(
    &Cry_GddHaeHsmEcdsaSha256GenerateContext,
    &srcSign);
  /* polyspace-begin MISRA-C3:18.1,D4.1,D4.11,D4.14 RTE:IDP RTE:STD_LIB RTE:IDP [Justified:Low] "No Impact of this rule violation" */
  memcpy((void*)(destResult->pSignatureR), (const void*)srcSign.r, ECC_BYTES_SIZE);
  memcpy((void*)(destResult->pSignatureS), (const void*)srcSign.s, ECC_BYTES_SIZE);
  /* polyspace-end MISRA-C3:18.1,D4.1,D4.11,D4.14 RTE:IDP RTE:STD_LIB RTE:IDP */


  Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;

  return (LddReturnValue);
}


/*******************************************************************************
** Function Name        : Cry_HaeHsmEcdsaSha256GenerateStart                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HAE HSM ECDSA SHA256, so that it is   **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmEcdsaSha256GenerateMainFunction() can      **
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
**                        Cry_GddHaeHsmEcdsaSha256GenerateTb,                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_EcdsaSha256Start,                               **
**                        Cry_HaeHsmEcdsaSha256GenerateInit,                  **
**                        Csm_SignatureGenerateServiceHasCallback             **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmEcdsaSha256GenerateStart(const void* cfgPtr,
  const Csm_AsymPrivateKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState)
  {
    Cry_HaeHsmEcdsaSha256GenerateInit();

    Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState = JOB_START;

    if (Csm_SignatureGenerateServiceHasCallback() == FALSE)
    {
      LddReturnValue = Cry_InternalHaeHsmEcdsaSha256GenerateStart(
        cfgPtr, keyPtr);
    }
    else
    {
      Cry_GddHaeHsmEcdsaSha256GenerateTb.pPrivateKeyPtr = keyPtr;
      /*LddReturnValue = E_OK; */
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
** Function Name        : Cry_HaeHsmEcdsaSha256GenerateUpdate                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the HAE HSM  **
**                        ECDSA SHA256                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmEcdsaSha256GenerateMainFunction() can      **
**                        process the input data                              **
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
**                        Cry_GddHaeHsmEcdsaSha256GenerateTb,                 **
**                        Cry_GddHaeHsmEcdsaSha256GenerateContext             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        HSM_EcdsaSha256Update, HSM_WaitResp,                **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmEcdsaSha256GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState)
  {
    Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureGenerateServiceHasCallback() == FALSE)
    {
      LddReturnValue = Cry_InternalHaeHsmEcdsaSha256GenerateUpdate(
        cfgId, dataPtr, dataLength);
    }
    else
    {
      Cry_GddHaeHsmEcdsaSha256GenerateTb.pDataPtr = dataPtr;
      Cry_GddHaeHsmEcdsaSha256GenerateTb.ulDataLength = dataLength;
      /* LddReturnValue = E_OK; */
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
** Function Name        : Cry_HaeHsmEcdsaSha256GenerateFinish                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the ECC     **
**                        ECDSA computation and store the result into the     **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmEcdsaSha256GenerateMainFunction() can     **
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
**                        Cry_GddHaeHsmEcdsaSha256GenerateTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hsm_EcdsaGenFinish                                  **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmEcdsaSha256GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32 *resultLengthPtr)
{
  Std_ReturnType LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState)
  {
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*resultLengthPtr < (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }
    else
    {
      Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState = JOB_FINISH;

      if (Csm_SignatureGenerateServiceHasCallback() == FALSE)
      {
        LddReturnValue = Cry_InternalHaeHsmEcdsaSha256GenerateFinish(
          cfgId, resultPtr, resultLengthPtr);
      }
      else
      {
        Cry_GddHaeHsmEcdsaSha256GenerateTb.pResultPtr = resultPtr;
        Cry_GddHaeHsmEcdsaSha256GenerateTb.pResultLengthPtr = resultLengthPtr;

        /* LddReturnValue = E_OK; */
      }
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}


/*******************************************************************************
** Function Name        : Cry_HaeHsmEcdsaSha256GenerateMainFunction            **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureGenerateCallbackNotification() with the**
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeHsmEcdsaSha256GenerateStart() or              **
**                        Cry_HaeHsmEcdsaSha256GenerateUpdate(). For           **
**                        Cry_HaeHsmEcdsaSha256GenerateFinish invocation of    **
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
**                        Cry_GddHaeHsmEcdsaSha256GenerateTb,                  **
**                        Cry_GddHaeHsmEcdsaSha256GenerateContext              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        HSM_EcdsaSha256Start, HSM_EcdsaSha256Update,          **
**                        HSM_WaitResp,                                       **
**                        HSM_EcdsaSha256Finish,                               **
**                        Csm_SignatureGenerateCallbackNotification,          **
**                        Csm_SignatureGenerateServiceFinishNotification      **
*******************************************************************************/
void Cry_HaeHsmEcdsaSha256GenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue = E_OK;

  switch (Cry_GddHaeHsmEcdsaSha256GenerateTb.ucJobState)
  {
  case JOB_START:
    LddReturnValue = Cry_InternalHaeHsmEcdsaSha256GenerateStart
      (NULL_PTR, Cry_GddHaeHsmEcdsaSha256GenerateTb.pPrivateKeyPtr);

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LddReturnValue = Cry_InternalHaeHsmEcdsaSha256GenerateUpdate(
      CSM_ZERO,
      Cry_GddHaeHsmEcdsaSha256GenerateTb.pDataPtr,
      Cry_GddHaeHsmEcdsaSha256GenerateTb.ulDataLength);

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:

    LddReturnValue = Cry_InternalHaeHsmEcdsaSha256GenerateFinish(
      CSM_ZERO,
      Cry_GddHaeHsmEcdsaSha256GenerateTb.pResultPtr,
      Cry_GddHaeHsmEcdsaSha256GenerateTb.pResultLengthPtr);

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

#endif /* (CSM_SIGNATURE_HAEHSMECDSASHA256GENERATE == STD_ON) */
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
