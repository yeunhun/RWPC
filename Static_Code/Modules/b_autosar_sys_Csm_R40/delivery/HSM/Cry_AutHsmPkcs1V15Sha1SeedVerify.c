/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmPkcs1V15Sha1SeedVerify.c                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM Pkcs1V15 Sha1 Seed Verify Interface **
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
** 1.0.4     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.3     09-Aug-2018   Sinil        Redmine #13652                        **
** 1.0.2     17-Apr-2018   Sinil        Redmine #12351                        **
** 1.0.1     10-Nov-2017   Sinil        Redmine #10550                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_AutHsmPkcs1V15Sha1SeedVerify.h"
#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1SEEDVERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"
#include "HwResource.h"
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
} Cry_AutHsmPkcs1V15Sha1SeedVerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
#define CSM_START_SEC_VAR_CLEARED_GLOBALB_8
#else
#define CSM_START_SEC_VAR_CLEARED_8
#endif
#include "MemMap.h"

static uint8 Cry_GaaHSMPkcs1V15Sha1Seed[HAE_SHA160_DIGEST_SIZE];

#if HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
#define CSM_STOP_SEC_VAR_CLEARED_GLOBALB_8
#else
#define CSM_STOP_SEC_VAR_CLEARED_8
#endif
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmPkcs1V15Sha1SeedVerDataType;

static Hsm_DataIDType Cry_GddAutHsmPkcs1V15Sha1SeedVerDataIDType;

static Cry_AutHsmPkcs1V15Sha1SeedVerifyTransferBuffer Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmPkcs1V15Sha1SeedVerifyCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmPkcs1V15Sha1SeedVerifyInit                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Pkcs1V15Sha1Seed module. **
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
**                      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb                 **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_AutHsmPkcs1V15Sha1SeedVerifyInit(void)
{
  Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
  Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr = NULL_PTR;
  Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pDataPtr = NULL_PTR;
  Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pSignaturePtr = NULL_PTR;
  Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ulSignatureLength = CSM_ZERO;
  Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)Cry_GaaHSMPkcs1V15Sha1Seed, 0x00, HAE_SHA160_DIGEST_SIZE);

  Cry_GddAutHsmPkcs1V15Sha1SeedVerDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmPkcs1V15Sha1SeedVerDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1V15Sha1SeedVerifyStart               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM Pkcs1V15 Seed, so that it is     **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmPkcs1V15Sha1SeedVerifyMainFunction() can  **
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
**                        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hsm_Pkcs1v15VerInit                                 **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPkcs1V15Sha1SeedVerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
    Cry_AutHsmPkcs1V15Sha1SeedVerifyInit();

    Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_START;

    LblAsync = Csm_SignatureVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        Cry_GddAutHsmPkcs1V15Sha1SeedVerDataType = HSM_DATA_RSA_PUBLIC_KEY;
        Cry_GddAutHsmPkcs1V15Sha1SeedVerDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        LddErr = HSM_NO_ERROR;
      }
      else if ((keyPtr->length == HSM_RSA_KEY_BYTE_SIZE) \
        || (keyPtr->length == (HSM_RSA_KEY_BYTE_SIZE + CSM_FOUR)))
      {
        Cry_GddAutHsmPkcs1V15Sha1SeedVerDataType = HSM_DATA_RSA_RAM_PUBLIC_KEY;
        Cry_GddAutHsmPkcs1V15Sha1SeedVerDataIDType = CSM_ONE;

        LddErr = Hsm_LoadRamKey(HSM_DATA_RSA_RAM_PUBLIC_KEY, CSM_ONE,
          keyPtr->length, (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_Pkcs1v15VerInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmPkcs1V15Sha1SeedVerDataType, Cry_GddAutHsmPkcs1V15Sha1SeedVerDataIDType);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr = keyPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1V15Sha1SeedVerifyUpdate              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Seed     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmPkcs1V15Sha1SeedVerifyMainFunction() can  **
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
**                        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback               **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPkcs1V15Sha1SeedVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;
  uint8 LucIndex;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
    Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_SignatureVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      if (dataLength > HAE_SHA160_DIGEST_SIZE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The input is checked" */
        for (LucIndex = CSM_ZERO; LucIndex < dataLength; LucIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          Cry_GaaHSMPkcs1V15Sha1Seed[LucIndex] = dataPtr[LucIndex];
        }

        LddErr = Hsm_Pkcs1v15VerUpdate(LblAsync, NULL_PTR,
          Cry_GaaHSMPkcs1V15Sha1Seed, dataLength,
          HAE_SHA160_CALCULATED);

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pDataPtr = dataPtr;
      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ulDataLength = dataLength;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1V15Sha1SeedVerifyFinish              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1V15**
**                        Seed computation and store the result into the      **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmPkcs1V15Sha1SeedVerifyMainFunction() can  **
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
**                        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyServiceHasCallback,              **
**                        Hsm_Pkcs1v15VerFinish                               **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPkcs1V15Sha1SeedVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
    Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_SignatureVerifyServiceHasCallback();

    if (LblAsync == FALSE)
    {
      if (signatureLength < HAE_RSA_BYTES_SIZE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddErr = Hsm_Pkcs1v15VerFinish(LblAsync, NULL_PTR,
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

      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pSignaturePtr = signaturePtr;
      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ulSignatureLength = signatureLength;
      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pResultPtr = resultPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1V15Sha1SeedVerifyCallback            **
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
**                        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
static void Cry_AutHsmPkcs1V15Sha1SeedVerifyCallback(Hsm_ErrType ddRet)
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

    switch (Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
      }
      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;
      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_SignatureVerifyServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1V15Sha1SeedVerifyMainFunction        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureVerifyCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutHsmPkcs1V15Sha1SeedVerifyStart() or          **
**                        Cry_AutHsmPkcs1V15Sha1SeedVerifyUpdate(). For       **
**                        Cry_AutHsmPkcs1V15Sha1SeedVerifyFinish invocation   **
**                        of Csm_SignatureVerifyCallbackNotification()        **
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
**                        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscPkcs1V15_Verify, EscCallback_setFunction,        **
**                        Csm_SignatureVerifyCallbackNotification,            **
**                        Csm_SignatureVerifyServiceFinishNotification        **
*******************************************************************************/
void Cry_AutHsmPkcs1V15Sha1SeedVerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;
  uint8 LucIndex;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmPkcs1V15Sha1SeedVerifyCallback;

  switch (Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->length == CSM_ONE)
    {
      Cry_GddAutHsmPkcs1V15Sha1SeedVerDataType = HSM_DATA_RSA_PUBLIC_KEY;
      Cry_GddAutHsmPkcs1V15Sha1SeedVerDataIDType
        = (Hsm_DataIDType)(Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->data[0]);
      LddErr = HSM_NO_ERROR;
    }
    else if ((Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->length == HSM_RSA_KEY_BYTE_SIZE) \
      || (Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->length == (HSM_RSA_KEY_BYTE_SIZE + CSM_FOUR)))
    {
      Cry_GddAutHsmPkcs1V15Sha1SeedVerDataType = HSM_DATA_RSA_RAM_PUBLIC_KEY;
      Cry_GddAutHsmPkcs1V15Sha1SeedVerDataIDType = CSM_ONE;

      LddErr = Hsm_LoadRamKey(HSM_DATA_RSA_RAM_PUBLIC_KEY, CSM_ONE,
        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pPublicKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_Pkcs1v15VerInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmPkcs1V15Sha1SeedVerDataType,
        Cry_GddAutHsmPkcs1V15Sha1SeedVerDataIDType);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;

      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    if (Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ulDataLength > HAE_SHA160_DIGEST_SIZE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      for (LucIndex = CSM_ZERO;
        LucIndex < Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ulDataLength; LucIndex++)
      {
	/* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
        Cry_GaaHSMPkcs1V15Sha1Seed[LucIndex]
          = Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pDataPtr[LucIndex];
      }

      LddErr = Hsm_Pkcs1v15VerUpdate(CSM_TRUE, LpCallback,
        Cry_GaaHSMPkcs1V15Sha1Seed,
        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ulDataLength,
        HAE_SHA160_CALCULATED);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;

      Csm_SignatureVerifyCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    if (Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ulSignatureLength
      < HAE_RSA_BYTES_SIZE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Hsm_Pkcs1v15VerFinish(CSM_TRUE, LpCallback,
        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pSignaturePtr,
        Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ulSignatureLength,
        (uint8*)(Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pResultPtr));

      if (LddErr == HSM_NO_ERROR)
      {
	      /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        *(Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pResultPtr) = CSM_E_VER_OK;
      }
      else
      {
        /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        *(Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      Cry_GddAutHsmPkcs1V15Sha1SeedVerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1SEEDVERIFY == STD_ON) */
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
