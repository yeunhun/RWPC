/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmEcdsaSha256Generate.c                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM ECDSA Sha256 Generate Interface     **
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
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.0.4     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.2     17-Apr-2018   Sinil        Redmine #12350 ,#12351                **
** 1.0.1     13-Nov-2017   Sinil        Redmine #10574                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM ECDSA */
#include "Cry_AutHsmEcdsaSha256Generate.h"
/* Signature Interface */
#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
#if (CSM_SIGNATURE_AUTHSMECDSASHA256GENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSMEcdsaSha256Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_AsymPrivateKeyType* pPrivateKeyPtr;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  uint8* pResultPtr;
  uint32* pResultLengthPtr;
} Cry_AutHsmEcdsaSha256GenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmEcdsaSha256GenDataType;

static Hsm_DataIDType Cry_GddAutHsmEcdsaSha256GenDataIDType;

/* Global structure variable for HSM ECDSA transfer buffer */
static Cry_AutHsmEcdsaSha256GenerateTransferBuffer Cry_GddAutHsmEcdsaSha256GenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmEcdsaSha256GenerateCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmEcdsaSha256GenerateInit                     **
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
** Remarks            : Global Variable(s):                                   **
**                      Cry_GddAutHsmEcdsaSha256GenerateTb                    **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_AutHsmEcdsaSha256GenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;
  Cry_GddAutHsmEcdsaSha256GenerateTb.pPrivateKeyPtr = NULL_PTR;
  Cry_GddAutHsmEcdsaSha256GenerateTb.pDataPtr = NULL_PTR;
  Cry_GddAutHsmEcdsaSha256GenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddAutHsmEcdsaSha256GenerateTb.pResultPtr = NULL_PTR;
  Cry_GddAutHsmEcdsaSha256GenerateTb.pResultLengthPtr = NULL_PTR;

  Cry_GddAutHsmEcdsaSha256GenDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmEcdsaSha256GenDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEcdsaSha256GenerateStart                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM ECDSA, so that it is             **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmEcdsaSha256GenerateMainFunction() can     **
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
**                        Cry_GddAutHsmEcdsaSha256GenerateTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hsm_EcdsaGenInit                                    **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEcdsaSha256GenerateStart(const void *cfgPtr,
  const Csm_AsymPrivateKeyType *keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmEcdsaSha256GenerateInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = JOB_START;

    LblAsync = Csm_SignatureGenerateServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
        if (keyPtr->data[0] == HSM_DATA_CUSTOM_IAU_KEY)
        {
          Cry_GddAutHsmEcdsaSha256GenDataType = HSM_DATA_CUSTOM_IAU_PRIVATE_KEY;
          Cry_GddAutHsmEcdsaSha256GenDataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
        }
        else
        #endif
        {
          Cry_GddAutHsmEcdsaSha256GenDataType = HSM_DATA_ECC_PRIVATE_KEY;
          Cry_GddAutHsmEcdsaSha256GenDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        }
        LddErr = HSM_NO_ERROR;
      }
      else if (keyPtr->length == HSM_ECC_KEY_BYTE_SIZE)
      {
        Cry_GddAutHsmEcdsaSha256GenDataType = HSM_DATA_ECC_RAM_PRIVATE_KEY;
        Cry_GddAutHsmEcdsaSha256GenDataIDType = CSM_TWO;

        LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PRIVATE_KEY, CSM_TWO,
          keyPtr->length, (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_EcdsaGenInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmEcdsaSha256GenDataType, Cry_GddAutHsmEcdsaSha256GenDataIDType);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmEcdsaSha256GenerateTb.pPrivateKeyPtr = keyPtr;
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
** Function Name        : Cry_AutHsmEcdsaSha256GenerateUpdate                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of hash         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmEcdsaSha256GenerateMainFunction() can     **
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
**                        Cry_GddAutHsmEcdsaSha256GenerateTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hsm_EcdsaGenUpdate                                  **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEcdsaSha256GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;
  const Csm_AutHsmEcdsaDataType* LpData;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED(dataLength);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_SignatureGenerateServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
      LpData = (const Csm_AutHsmEcdsaDataType*)dataPtr;

      /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LddErr = Hsm_EcdsaGenUpdate(LblAsync, NULL_PTR,
        LpData->pMessage, LpData->ulMessageLength, HAE_SHA256,
        LpData->pSecretNumber, HSM_ECC_KEY_BYTE_SIZE);

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmEcdsaSha256GenerateTb.pDataPtr = dataPtr;
      Cry_GddAutHsmEcdsaSha256GenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_AutHsmEcdsaSha256GenerateFinish                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the ECC     **
**                        ECDSA computation and store the result into the     **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmEcdsaSha256GenerateMainFunction() can     **
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
**                        Cry_GddAutHsmEcdsaSha256GenerateTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hsm_EcdsaGenFinish                                  **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEcdsaSha256GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32 *resultLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;
  Csm_AutHsmEcdsaSignatureType* LpData;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState)
  {
    Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_SignatureGenerateServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*resultLengthPtr < (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
	      /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
        LpData = (Csm_AutHsmEcdsaSignatureType*)resultPtr;
        /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        LddErr = Hsm_EcdsaGenFinish(LblAsync, NULL_PTR,
          LpData->pSignatureR, LpData->pSignatureS, resultLengthPtr);

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmEcdsaSha256GenerateTb.pResultPtr = resultPtr;
      Cry_GddAutHsmEcdsaSha256GenerateTb.pResultLengthPtr = resultLengthPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEcdsaSha256GenerateCallback               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : TBD                                                 **
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
**                        Cry_GddAutHsmEcdsaSha256GenerateTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateCallbackNotification,          **
**                        Csm_SignatureGenerateServiceFinishNotification      **
*******************************************************************************/
static void Cry_AutHsmEcdsaSha256GenerateCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;
      }
      Csm_SignatureGenerateCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;
      Csm_SignatureGenerateCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_SignatureGenerateServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEcdsaSha256GenerateMainFunction           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureGenerateCallbackNotification() with the**
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutHsmEcdsaSha256GenerateStart() or             **
**                        Cry_AutHsmEcdsaSha256GenerateUpdate(). For          **
**                        Cry_AutHsmEcdsaSha256GenerateFinish invocation of   **
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
**                        Cry_GddAutHsmEcdsaSha256GenerateTb                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        AutHsmSha256_Init,                                  **
**                        AutHsmSha256_Update,                                **
**                        AutHsmSha256_Finish,                                **
**                        AutHsmEcdsa_Sign, AutHsmCallback_setFunction,       **
**                        Csm_SignatureGenerateCallbackNotification,          **
**                        Csm_SignatureGenerateServiceFinishNotification      **
*******************************************************************************/
void Cry_AutHsmEcdsaSha256GenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;
  const Csm_AutHsmEcdsaDataType* LpData;
  const Csm_AutHsmEcdsaSignatureType* LpSignature;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmEcdsaSha256GenerateCallback;

  switch (Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmEcdsaSha256GenerateTb.pPrivateKeyPtr->length == CSM_ONE)
    {
      #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
      if (Cry_GddAutHsmEcdsaSha256GenerateTb.pPrivateKeyPtr->data[0] == HSM_DATA_CUSTOM_IAU_KEY)
      {
        Cry_GddAutHsmEcdsaSha256GenDataType = HSM_DATA_CUSTOM_IAU_PRIVATE_KEY;
        Cry_GddAutHsmEcdsaSha256GenDataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
      }
      else
      #endif
      {
        Cry_GddAutHsmEcdsaSha256GenDataType = HSM_DATA_ECC_PRIVATE_KEY;
        Cry_GddAutHsmEcdsaSha256GenDataIDType
          = (Hsm_DataIDType)(Cry_GddAutHsmEcdsaSha256GenerateTb.pPrivateKeyPtr->data[0]);
      }
      LddErr = HSM_NO_ERROR;
    }
    else if (Cry_GddAutHsmEcdsaSha256GenerateTb.pPrivateKeyPtr->length == HSM_ECC_KEY_BYTE_SIZE)
    {
      Cry_GddAutHsmEcdsaSha256GenDataType = HSM_DATA_ECC_RAM_PRIVATE_KEY;
      Cry_GddAutHsmEcdsaSha256GenDataIDType = CSM_TWO;

      LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PRIVATE_KEY, CSM_TWO,
        Cry_GddAutHsmEcdsaSha256GenerateTb.pPrivateKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmEcdsaSha256GenerateTb.pPrivateKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_EcdsaGenInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmEcdsaSha256GenDataType, Cry_GddAutHsmEcdsaSha256GenDataIDType);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;

      Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    /* polyspace +6 MISRA-C3:11.3,18.1,D4.1 [Justified:Low] "No Impact of this rule violation" */
    LpData = (const Csm_AutHsmEcdsaDataType*)
      Cry_GddAutHsmEcdsaSha256GenerateTb.pDataPtr;
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    LddErr = Hsm_EcdsaGenUpdate(CSM_TRUE, LpCallback,
      LpData->pMessage, LpData->ulMessageLength, HAE_SHA256,
      LpData->pSecretNumber, HSM_ECC_KEY_BYTE_SIZE);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;

      Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    /* polyspace +1 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddAutHsmEcdsaSha256GenerateTb.pResultLengthPtr)
      < (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      /* polyspace +6 MISRA-C3:11.3,18.1,D4.1 [Justified:Low] "No Impact of this rule violation" */
      LpSignature = (Csm_AutHsmEcdsaSignatureType*)
        (Cry_GddAutHsmEcdsaSha256GenerateTb.pResultPtr);
      /* polyspace +2 MISRA-C3:18.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      LddErr = Hsm_EcdsaGenFinish(CSM_TRUE, LpCallback,
        LpSignature->pSignatureR, LpSignature->pSignatureS,
        Cry_GddAutHsmEcdsaSha256GenerateTb.pResultLengthPtr);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      Cry_GddAutHsmEcdsaSha256GenerateTb.ucJobState = NO_JOB;

      Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    }
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

#endif /* (CSM_SIGNATURE_AUTHSMECDSASHA256GENERATE == STD_ON) */
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
