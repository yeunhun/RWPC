/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmEcdsaSha256Verify.c                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM ECDSA Verify Interface              **
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
** 1.0.2     05-Jun-2018   Sinil        Redmine #12957                        **
** 1.0.1     17-Apr-2018   Sinil        Redmine #12350 ,#12351                **
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
#include "Cry_AutHsmEcdsaSha256Verify.h"
/* Signature Interface */
#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_AUTHSMECDSASHA256VERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSMEcdsaSha256Verify Transfer buffer*/
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
} Cry_AutHsmEcdsaSha256VerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmEcdsaSha256VerDataType;

static Hsm_DataIDType Cry_GddAutHsmEcdsaSha256VerDataIDType;

/* Global structure variable for HSM ECDSA transfer buffer */
static Cry_AutHsmEcdsaSha256VerifyTransferBuffer Cry_GddAutHsmEcdsaSha256VerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmEcdsaSha256VerifyCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmEcdsaSha256VerifyInit                       **
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
** Remarks            : Global Variable(s):                                   **
**                      Cry_GddAutHsmEcdsaSha256VerifyTb                      **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_AutHsmEcdsaSha256VerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;
  Cry_GddAutHsmEcdsaSha256VerifyTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddAutHsmEcdsaSha256VerifyTb.pDataPtr = NULL_PTR;
  Cry_GddAutHsmEcdsaSha256VerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddAutHsmEcdsaSha256VerifyTb.pSignaturePtr = NULL_PTR;
  Cry_GddAutHsmEcdsaSha256VerifyTb.ulSignatureLength = CSM_ZERO;
  Cry_GddAutHsmEcdsaSha256VerifyTb.pResultPtr = NULL_PTR;

  Cry_GddAutHsmEcdsaSha256VerDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmEcdsaSha256VerDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEcdsaSha256VerifyStart                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM ECDSA, so that it is             **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmEcdsaSha256VerifyMainFunction() can       **
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
**                        Cry_GddAutHsmEcdsaSha256VerifyTb                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hsm_EcdsaVerInit                                    **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEcdsaSha256VerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmEcdsaSha256VerifyInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = JOB_START;

    LblAsync = Csm_SignatureVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
        if (keyPtr->data[0] == HSM_DATA_CUSTOM_IAU_KEY)
        {
          Cry_GddAutHsmEcdsaSha256VerDataType = HSM_DATA_CUSTOM_IAU_PUBLIC_KEY;
          Cry_GddAutHsmEcdsaSha256VerDataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
        }
        else
        #endif
        {
          Cry_GddAutHsmEcdsaSha256VerDataType = HSM_DATA_ECC_PUBLIC_KEY;
          Cry_GddAutHsmEcdsaSha256VerDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        }
        LddErr = HSM_NO_ERROR;
      }
      else if (keyPtr->length == (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
      {
        Cry_GddAutHsmEcdsaSha256VerDataType = HSM_DATA_ECC_RAM_PUBLIC_KEY;
        Cry_GddAutHsmEcdsaSha256VerDataIDType = CSM_TWO;

        LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PUBLIC_KEY, CSM_TWO,
          keyPtr->length, (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_EcdsaVerInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmEcdsaSha256VerDataType,
          Cry_GddAutHsmEcdsaSha256VerDataIDType);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmEcdsaSha256VerifyTb.pPublicKeyPtr = keyPtr;
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
** Function Name        : Cry_AutHsmEcdsaSha256VerifyUpdate                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of hash         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmEcdsaSha256VerifyMainFunction() can       **
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
**                        Cry_GddAutHsmEcdsaSha256VerifyTb                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hsm_EcdsaVerUpdate                                  **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEcdsaSha256VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_SignatureVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_EcdsaVerUpdate(LblAsync, NULL_PTR,
        dataPtr, dataLength, HAE_SHA256);

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmEcdsaSha256VerifyTb.pDataPtr = dataPtr;
      Cry_GddAutHsmEcdsaSha256VerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_AutHsmEcdsaSha256VerifyFinish                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the ECC     **
**                        ECDSA computation and store the result into the     **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmEcdsaSha256VerifyMainFunction() can       **
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
**                        Cry_GddAutHsmEcdsaSha256VerifyTb                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hsm_EcdsaVerFinish                                  **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEcdsaSha256VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;
  const Csm_AutHsmEcdsaSignatureType* LpData;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState)
  {
    Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_SignatureVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      if (signatureLength < (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
	      /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
        LpData = (const Csm_AutHsmEcdsaSignatureType*)signaturePtr;
        /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        LddErr = Hsm_EcdsaVerFinish(LblAsync, NULL_PTR,
          (const uint8*)(LpData->pSignatureR), (const uint8*)(LpData->pSignatureS),
          signatureLength, (uint8*)resultPtr);

        if (LddErr == HSM_NO_ERROR)
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          *resultPtr = CSM_E_VER_OK;
        }
        else
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          *resultPtr = CSM_E_VER_NOT_OK;
        }
      }

      Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmEcdsaSha256VerifyTb.pSignaturePtr = signaturePtr;
      Cry_GddAutHsmEcdsaSha256VerifyTb.ulSignatureLength = signatureLength;
      Cry_GddAutHsmEcdsaSha256VerifyTb.pResultPtr = resultPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEcdsaSha256VerifyCallback                 **
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
**                        Cry_GddAutHsmEcdsaSha256VerifyTb                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
static void Cry_AutHsmEcdsaSha256VerifyCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_SignatureVerifyCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;
      }
      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;
      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_SignatureVerifyServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEcdsaSha256VerifyMainFunction             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureVerifyCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutHsmEcdsaSha256VerifyStart() or               **
**                        Cry_AutHsmEcdsaSha256VerifyUpdate(). For            **
**                        Cry_AutHsmEcdsaSha256VerifyFinish invocation of     **
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
**                        Cry_GddAutHsmEcdsaSha256VerifyTb                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscEcdsa_Verify, EscCallback_setFunction,           **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
void Cry_AutHsmEcdsaSha256VerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;
  const Csm_AutHsmEcdsaSignatureType* LpData;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmEcdsaSha256VerifyCallback;

  switch (Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmEcdsaSha256VerifyTb.pPublicKeyPtr->length == CSM_ONE)
    {
      #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
      if (Cry_GddAutHsmEcdsaSha256VerifyTb.pPublicKeyPtr->data[0] == HSM_DATA_CUSTOM_IAU_KEY)
      {
        Cry_GddAutHsmEcdsaSha256VerDataType = HSM_DATA_CUSTOM_IAU_PUBLIC_KEY;
        Cry_GddAutHsmEcdsaSha256VerDataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
      }
      else
      #endif
      {
        Cry_GddAutHsmEcdsaSha256VerDataType = HSM_DATA_ECC_PUBLIC_KEY;
        Cry_GddAutHsmEcdsaSha256VerDataIDType
          = (Hsm_DataIDType)(Cry_GddAutHsmEcdsaSha256VerifyTb.pPublicKeyPtr->data[0]);
      }
      LddErr = HSM_NO_ERROR;
    }
    else if (Cry_GddAutHsmEcdsaSha256VerifyTb.pPublicKeyPtr->length
      == (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
    {
      Cry_GddAutHsmEcdsaSha256VerDataType = HSM_DATA_ECC_RAM_PUBLIC_KEY;
      Cry_GddAutHsmEcdsaSha256VerDataIDType = CSM_TWO;

      LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PUBLIC_KEY, CSM_TWO,
        Cry_GddAutHsmEcdsaSha256VerifyTb.pPublicKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmEcdsaSha256VerifyTb.pPublicKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_EcdsaVerInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmEcdsaSha256VerDataType,
        Cry_GddAutHsmEcdsaSha256VerDataIDType);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;

      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    LddErr = Hsm_EcdsaVerUpdate(CSM_TRUE, LpCallback,
      Cry_GddAutHsmEcdsaSha256VerifyTb.pDataPtr,
      Cry_GddAutHsmEcdsaSha256VerifyTb.ulDataLength, HAE_SHA256);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;

      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    if (Cry_GddAutHsmEcdsaSha256VerifyTb.ulSignatureLength
      < (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      /* polyspace-begin MISRA-C3:11.3,18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      LpData = (const Csm_AutHsmEcdsaSignatureType*)
        (Cry_GddAutHsmEcdsaSha256VerifyTb.pSignaturePtr);

      LddErr = Hsm_EcdsaVerFinish(CSM_TRUE, LpCallback,
        (const uint8*)(LpData->pSignatureR), (const uint8*)(LpData->pSignatureS),
        Cry_GddAutHsmEcdsaSha256VerifyTb.ulSignatureLength,
        (uint8*)(Cry_GddAutHsmEcdsaSha256VerifyTb.pResultPtr));

      if (LddErr == HSM_NO_ERROR)
      {
        *(Cry_GddAutHsmEcdsaSha256VerifyTb.pResultPtr) = CSM_E_VER_OK;
      }
      else
      {
        *(Cry_GddAutHsmEcdsaSha256VerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
      }
      /* polyspace-end MISRA-C3:11.3,18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    }

    if (LddReturnValue != E_OK)
    {
      Cry_GddAutHsmEcdsaSha256VerifyTb.ucJobState = NO_JOB;

      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    }
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

#endif /* (CSM_SIGNATURE_AUTHSMECDSASHA256VERIFY == STD_ON) */
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
