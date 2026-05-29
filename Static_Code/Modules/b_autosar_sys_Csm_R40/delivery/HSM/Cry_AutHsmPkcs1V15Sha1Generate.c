/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmPkcs1V15Sha1Generate.c                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM Pkcs1V15Sha1 Generate Interface     **
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
** 1.0.3     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.1     17-Apr-2018   Sinil        Redmine #12351                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_AutHsmPkcs1V15Sha1Generate.h"
#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
#if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1GENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

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
} Cry_AutHsmPkcs1V15Sha1GenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmPkcs1V15Sha1GenDataType;

static Hsm_DataIDType Cry_GddAutHsmPkcs1V15Sha1GenDataIDType;

static Cry_AutHsmPkcs1V15Sha1GenerateTransferBuffer Cry_GddAutHsmPkcs1V15Sha1GenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmPkcs1V15Sha1GenerateCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmPkcs1V15Sha1GenerateInit                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Pkcs1V15Sha1 module.     **
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
**                      Cry_GddAutHsmPkcs1V15Sha1GenerateTb                   **
**                                                                            **
**                     Function(s) invoked: None                              **
**                                                                            **
*******************************************************************************/
void Cry_AutHsmPkcs1V15Sha1GenerateInit(void)
{
  Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
  Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pPrivateKeyPtr = NULL_PTR;
  Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pDataPtr = NULL_PTR;
  Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pResultPtr = NULL_PTR;
  Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pResultLengthPtr = NULL_PTR;

  Cry_GddAutHsmPkcs1V15Sha1GenDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmPkcs1V15Sha1GenDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1V15Sha1GenerateStart                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM Pkcs1V15 Sha1, so that it is     **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmPkcs1V15Sha1GenerateMainFunction() can    **
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
**                        Cry_GddAutHsmPkcs1V15Sha1GenerateTb                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hsm_Pkcs1v15GenInit                                 **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPkcs1V15Sha1GenerateStart(const void *cfgPtr,
  const Csm_AsymPrivateKeyType *keyPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState)
  {
    Cry_AutHsmPkcs1V15Sha1GenerateInit();

    Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = JOB_START;

    LblAsync = Csm_SignatureGenerateServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length == CSM_ONE)
      {
        Cry_GddAutHsmPkcs1V15Sha1GenDataType = HSM_DATA_RSA_PRIVATE_KEY;
        Cry_GddAutHsmPkcs1V15Sha1GenDataIDType = (Hsm_DataIDType)(keyPtr->data[0]);
        LddErr = HSM_NO_ERROR;
      }
      else if (keyPtr->length == (HSM_RSA_KEY_BYTE_SIZE * CSM_TWO))
      {
        Cry_GddAutHsmPkcs1V15Sha1GenDataType = HSM_DATA_RSA_RAM_PRIVATE_KEY;
        Cry_GddAutHsmPkcs1V15Sha1GenDataIDType = CSM_ONE;

        LddErr = Hsm_LoadRamKey(HSM_DATA_RSA_RAM_PRIVATE_KEY, CSM_ONE,
          keyPtr->length, (const uint8*)(keyPtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_Pkcs1v15GenInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmPkcs1V15Sha1GenDataType, Cry_GddAutHsmPkcs1V15Sha1GenDataIDType);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pPrivateKeyPtr = keyPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1V15Sha1GenerateUpdate                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha1     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmPkcs1V15Sha1GenerateMainFunction() can    **
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
**                        Cry_GddAutHsmPkcs1V15Sha1GenerateTb                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hsm_Pkcs1v15GenUpdate                               **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPkcs1V15Sha1GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState)
  {
    Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_SignatureGenerateServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_Pkcs1v15GenUpdate(LblAsync, NULL_PTR,
        dataPtr, dataLength, HAE_SHA160);

      if (LddErr == HSM_NO_ERROR)
      {
        Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pDataPtr = dataPtr;
      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ulDataLength = dataLength;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1V15Sha1GenerateFinish                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1V15**
**                        Sha1 computation and store the result into the      **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmPkcs1V15Sha1GenerateMainFunction() can    **
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
**                        Cry_GddAutHsmPkcs1V15Sha1GenerateTb                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hsm_Pkcs1v15GenFinish                               **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPkcs1V15Sha1GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32 *resultLengthPtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState)
  {
    Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_SignatureGenerateServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*resultLengthPtr < HAE_RSA_BYTES_SIZE)
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        LddErr = Hsm_Pkcs1v15GenFinish(LblAsync, NULL_PTR,
          resultPtr, resultLengthPtr);

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pResultPtr = resultPtr;
      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pResultLengthPtr = resultLengthPtr;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1V15Sha1GenerateCallback              **
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
**                        Cry_GddAutHsmPkcs1V15Sha1GenerateTb                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateCallbackNotification,          **
**                        Csm_SignatureGenerateServiceFinishNotification      **
*******************************************************************************/
static void Cry_AutHsmPkcs1V15Sha1GenerateCallback(Hsm_ErrType ddRet)
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

    switch (Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
      }
      Csm_SignatureGenerateCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
      Csm_SignatureGenerateCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_SignatureGenerateServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPkcs1V15Sha1GenerateMainFunction          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureGenerateCallbackNotification() with the**
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_AutHsmPkcs1V15Sha1GenerateStart() or            **
**                        Cry_AutHsmPkcs1V15Sha1GenerateUpdate(). For         **
**                        Cry_AutHsmPkcs1V15Sha1GenerateFinish invocation of  **
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
**                        Cry_GddAutHsmPkcs1V15Sha1GenerateTb                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        AutHsmSha1_Init,                                    **
**                        AutHsmSha1_Update,                                  **
**                        AutHsmSha1_Finish,                                  **
**                        AutHsmPkcs1V15_Sign, AutHsmCallback_setFunction,    **
**                        Csm_SignatureGenerateCallbackNotification,          **
**                        Csm_SignatureGenerateServiceFinishNotification      **
*******************************************************************************/
void Cry_AutHsmPkcs1V15Sha1GenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmPkcs1V15Sha1GenerateCallback;

  switch (Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pPrivateKeyPtr->length == CSM_ONE)
    {
      Cry_GddAutHsmPkcs1V15Sha1GenDataType = HSM_DATA_RSA_PRIVATE_KEY;
      Cry_GddAutHsmPkcs1V15Sha1GenDataIDType
        = (Hsm_DataIDType)(Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pPrivateKeyPtr->data[0]);
      LddErr = HSM_NO_ERROR;
    }
    else if (Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pPrivateKeyPtr->length == (HSM_RSA_KEY_BYTE_SIZE * CSM_TWO))
    {
      Cry_GddAutHsmPkcs1V15Sha1GenDataType = HSM_DATA_RSA_RAM_PRIVATE_KEY;
      Cry_GddAutHsmPkcs1V15Sha1GenDataIDType = CSM_ONE;

      LddErr = Hsm_LoadRamKey(HSM_DATA_RSA_RAM_PRIVATE_KEY, CSM_ONE,
        Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pPrivateKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pPrivateKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_Pkcs1v15GenInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmPkcs1V15Sha1GenDataType, Cry_GddAutHsmPkcs1V15Sha1GenDataIDType);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;

      Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    LddErr = Hsm_Pkcs1v15GenUpdate(CSM_TRUE, LpCallback,
      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pDataPtr,
      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ulDataLength, HAE_SHA160);

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;

      Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pResultLengthPtr) < HAE_RSA_BYTES_SIZE)
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Hsm_Pkcs1v15GenFinish(CSM_TRUE, LpCallback,
        Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pResultPtr,
        Cry_GddAutHsmPkcs1V15Sha1GenerateTb.pResultLengthPtr);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      Cry_GddAutHsmPkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1GENERATE == STD_ON) */
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
