/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmPkcs1PssSha256Verify.c                              **
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
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.0.4     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.2     17-Apr-2018   Sinil        Redmine #12351                        **
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
/* Header File for HSM Pkcs1Pss Sha256 */
#include "Cry_AutHsmPkcs1PssSha256Verify.h"
/* Signature Interface */
#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_AUTHSMPKCS1PSSSHA256VERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

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
} Cry_AutHsmPkcs1PssSha256VerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmPkcs1PssSha256VerDataType;

static Hsm_DataIDType Cry_GddAutHsmPkcs1PssSha256VerDataIDType;

/* Global structure variable for HSM Pkcs1Pss Sha256 transfer buffer */
static Cry_AutHsmPkcs1PssSha256VerifyTransferBuffer Cry_GddAutHsmPkcs1PssSha256VerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmPkcs1PssSha256VerifyCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmPkcs1PssSha256VerifyInit                    **
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
**                      Cry_GddAutHsmPkcs1PssSha256VerifyTb                   **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_AutHsmPkcs1PssSha256VerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
  Cry_GddAutHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddAutHsmPkcs1PssSha256VerifyTb.pDataPtr = NULL_PTR;
  Cry_GddAutHsmPkcs1PssSha256VerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddAutHsmPkcs1PssSha256VerifyTb.pSignaturePtr = NULL_PTR;
  Cry_GddAutHsmPkcs1PssSha256VerifyTb.ulSignatureLength = CSM_ZERO;
  Cry_GddAutHsmPkcs1PssSha256VerifyTb.pResultPtr = NULL_PTR;

  Cry_GddAutHsmPkcs1PssSha256VerDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmPkcs1PssSha256VerDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1PssSha256VerifyStart                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM Pkcs1Pss Sha256, so that it is   **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmPkcs1PssSha256VerifyMainFunction() can    **
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
**                        Cry_GddAutHsmPkcs1PssSha256VerifyTb                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hsm_Pkcs1PssVerInit                                 **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPkcs1PssSha256VerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState)
  {
    Cry_AutHsmPkcs1PssSha256VerifyInit();

    Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_START;

    LblAsync = Csm_SignatureVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        Cry_GddAutHsmPkcs1PssSha256VerDataType = HSM_DATA_RSA_PUBLIC_KEY;
        Cry_GddAutHsmPkcs1PssSha256VerDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        LddErr = HSM_NO_ERROR;
      }
      else if ((keyPtr->length == HSM_RSA_KEY_BYTE_SIZE) \
        || (keyPtr->length == (HSM_RSA_KEY_BYTE_SIZE + CSM_FOUR)))
      {
        Cry_GddAutHsmPkcs1PssSha256VerDataType = HSM_DATA_RSA_RAM_PUBLIC_KEY;
        Cry_GddAutHsmPkcs1PssSha256VerDataIDType = CSM_FIVE;

        LddErr = Hsm_LoadRamKey(HSM_DATA_RSA_RAM_PUBLIC_KEY, CSM_FIVE,
          keyPtr->length, (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_Pkcs1PssVerInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmPkcs1PssSha256VerDataType,
          Cry_GddAutHsmPkcs1PssSha256VerDataIDType);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr = keyPtr;
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
** Function Name        : Cry_AutHsmPkcs1PssSha256VerifyUpdate                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha256   **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmPkcs1PssSha256VerifyMainFunction() can    **
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
**                        Cry_GddAutHsmPkcs1PssSha256VerifyTb                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hsm_Pkcs1PssVerUpdate                               **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPkcs1PssSha256VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;
  const Csm_AutHsmPkcs1PssDataType* LpData;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED(dataLength);

  if (JOB_DONE == Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState)
  {
    Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_SignatureVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
      LpData = (const Csm_AutHsmPkcs1PssDataType*)dataPtr;
      /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LddErr = Hsm_Pkcs1PssVerUpdate(LblAsync, NULL_PTR,
        LpData->pData, LpData->ulDataLength, HAE_SHA256,
        LpData->ulSaltLength);

      if (LddErr == HSM_NO_ERROR)
      {
        Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmPkcs1PssSha256VerifyTb.pDataPtr = dataPtr;
      Cry_GddAutHsmPkcs1PssSha256VerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_AutHsmPkcs1PssSha256VerifyFinish                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1Pss**
**                        Sha256 computation and store the result into the    **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmPkcs1PssSha256VerifyMainFunction() can    **
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
**                        Cry_GddAutHsmPkcs1PssSha256VerifyTb                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hsm_Pkcs1PssVerFinish                               **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPkcs1PssSha256VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState)
  {
    Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_SignatureVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      if (signatureLength < HAE_RSA_BYTES_SIZE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddErr = Hsm_Pkcs1PssVerFinish(LblAsync, NULL_PTR,
          signaturePtr, signatureLength, (uint8*)resultPtr);

        if (LddErr == HSM_NO_ERROR)
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          *resultPtr = CSM_E_VER_OK;
        }
        else
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          *resultPtr = CSM_E_VER_NOT_OK;
        }
      }

      Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmPkcs1PssSha256VerifyTb.pSignaturePtr = signaturePtr;
      Cry_GddAutHsmPkcs1PssSha256VerifyTb.ulSignatureLength = signatureLength;
      Cry_GddAutHsmPkcs1PssSha256VerifyTb.pResultPtr = resultPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1PssSha256VerifyCallback              **
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
**                        Cry_GddAutHsmPkcs1PssSha256VerifyTb                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
static void Cry_AutHsmPkcs1PssSha256VerifyCallback(Hsm_ErrType ddRet)
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

    switch (Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
      }
      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;
      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_SignatureVerifyServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1PssSha256VerifyMainFunction          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureVerifyCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutHsmPkcs1PssSha256VerifyStart() or            **
**                        Cry_AutHsmPkcs1PssSha256VerifyUpdate(). For         **
**                        Cry_AutHsmPkcs1PssSha256VerifyFinish invocation of  **
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
**                        Cry_GddAutHsmPkcs1PssSha256VerifyTb                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscPkcs1Pss_Verify, EscCallback_setFunction,        **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
void Cry_AutHsmPkcs1PssSha256VerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;
  const Csm_AutHsmPkcs1PssDataType* LpData;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmPkcs1PssSha256VerifyCallback;

  switch (Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr->length == CSM_ONE)
    {
      Cry_GddAutHsmPkcs1PssSha256VerDataType = HSM_DATA_RSA_PUBLIC_KEY;
      Cry_GddAutHsmPkcs1PssSha256VerDataIDType
        = (Hsm_DataIDType)(Cry_GddAutHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr->data[0]);
      LddErr = HSM_NO_ERROR;
    }
    else if ((Cry_GddAutHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr->length == HSM_RSA_KEY_BYTE_SIZE) \
      || (Cry_GddAutHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr->length == (HSM_RSA_KEY_BYTE_SIZE + CSM_FOUR)))
    {
      Cry_GddAutHsmPkcs1PssSha256VerDataType = HSM_DATA_RSA_RAM_PUBLIC_KEY;
      Cry_GddAutHsmPkcs1PssSha256VerDataIDType = CSM_FIVE;

      LddErr = Hsm_LoadRamKey(HSM_DATA_RSA_RAM_PUBLIC_KEY, CSM_FIVE,
        Cry_GddAutHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmPkcs1PssSha256VerifyTb.pPublicKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_Pkcs1PssVerInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmPkcs1PssSha256VerDataType,
        Cry_GddAutHsmPkcs1PssSha256VerDataIDType);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;

      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    /* polyspace +2 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
    LpData = (const Csm_AutHsmPkcs1PssDataType*)
      Cry_GddAutHsmPkcs1PssSha256VerifyTb.pDataPtr;

    /* polyspace +3 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    LddErr = Hsm_Pkcs1PssVerUpdate(CSM_TRUE, LpCallback,
      LpData->pData, LpData->ulDataLength, HAE_SHA256,
      LpData->ulSaltLength);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;

      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    if (Cry_GddAutHsmPkcs1PssSha256VerifyTb.ulSignatureLength
      < HAE_RSA_BYTES_SIZE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Hsm_Pkcs1PssVerFinish(CSM_TRUE, LpCallback,
        Cry_GddAutHsmPkcs1PssSha256VerifyTb.pSignaturePtr,
        Cry_GddAutHsmPkcs1PssSha256VerifyTb.ulSignatureLength,
        (uint8*)(Cry_GddAutHsmPkcs1PssSha256VerifyTb.pResultPtr));

      if (LddErr == HSM_NO_ERROR)
      {
	/* polyspace +6 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
        *(Cry_GddAutHsmPkcs1PssSha256VerifyTb.pResultPtr) = CSM_E_VER_OK;
      }
      else
      {
        *(Cry_GddAutHsmPkcs1PssSha256VerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      Cry_GddAutHsmPkcs1PssSha256VerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SIGNATURE_AUTHSMPKCS1PSSSHA256VERIFY == STD_ON) */
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
