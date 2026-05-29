/*******************************************************************************
**                                                                            **
**  (C) 2018~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaePkcs1V15Sha256Generate.c                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HAE Pkcs1V15 Sha256 Generate            **
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
** 1.0.2     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.1     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.0     01-Nov-2018   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_HaePkcs1V15Sha256Generate.h"
#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
#if (CSM_SIGNATURE_HAEPKCS1V15SHA256GENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_Pkcs1.h"
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
} Cry_HaePkcs1V15Sha256GenerateTransferBuffer;

/*******************************************************************************
**                               Local Data                                   **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaePkcs1V15Sha256GenerateModulus[HMG_RSA_BYTES_SIZE];
static uint8 Cry_GaaHaePkcs1V15Sha256GenerateExponent[HMG_RSA_BYTES_SIZE];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HmgRsaPrivatekey Cry_GddHaePkcs1V15Sha256GeneratePrivatekey;

static HmgSha256Ctx Cry_GddHaePkcs1V15Sha256GenerateSha256Context;

static Cry_HaePkcs1V15Sha256GenerateTransferBuffer Cry_GddHaePkcs1V15Sha256GenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaePkcs1V15Sha256GenerateInit                     **
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
**                      Cry_GddHaePkcs1V15Sha256GenerateTb,                   **
**                      Cry_GddHaePkcs1V15Sha256GenerateContext,              **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaePkcs1V15Sha256GenerateInit(void)
{
  Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
  Cry_GddHaePkcs1V15Sha256GenerateTb.pPrivateKeyPtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha256GenerateTb.pDataPtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha256GenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddHaePkcs1V15Sha256GenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha256GenerateTb.pResultLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GaaHaePkcs1V15Sha256GenerateModulus, 0x00, HMG_RSA_BYTES_SIZE);
  (void)memset((void*)&Cry_GaaHaePkcs1V15Sha256GenerateExponent, 0x00, HMG_RSA_BYTES_SIZE);

  Cry_GddHaePkcs1V15Sha256GeneratePrivatekey.modulus = Cry_GaaHaePkcs1V15Sha256GenerateModulus;
  Cry_GddHaePkcs1V15Sha256GeneratePrivatekey.exponent = Cry_GaaHaePkcs1V15Sha256GenerateExponent;

  (void)memset((void*)&Cry_GddHaePkcs1V15Sha256GenerateSha256Context, 0x00, sizeof(HmgSha256Ctx));
}

/*******************************************************************************
** Function Name        : Cry_HaePkcs1V15Sha256GenerateStart                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever Pkcs1V15 Sha256, so that it **
**                        is able to process the input data                   **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaePkcs1V15Sha256GenerateMainFunction() can     **
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
**                        Cry_GddHaePkcs1V15Sha256GenerateTb,                 **
**                        Cry_GddHaePkcs1V15Sha256GenerateContext,            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaePkcs1V15Sha256GenerateInit,                  **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hmg_Sha256Start                                     **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha256GenerateStart(const void* cfgPtr,
  const Csm_AsymPrivateKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState)
  {
    Cry_HaePkcs1V15Sha256GenerateInit();

    Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = JOB_START;

    if (Csm_SignatureGenerateServiceHasCallback() == CSM_FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != (HMG_RSA_BYTES_SIZE * CSM_TWO))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblPrimitiveRet = Hmg_Sha256Start(&Cry_GddHaePkcs1V15Sha256GenerateSha256Context);
        if (LblPrimitiveRet != HMG_SUCCESS)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        (void)memcpy((void*)Cry_GaaHaePkcs1V15Sha256GenerateModulus,\
          (const void*)keyPtr->data,\
          HMG_RSA_BYTES_SIZE);
        (void)memcpy((void*)Cry_GaaHaePkcs1V15Sha256GenerateExponent,
          (const void*)(&(keyPtr->data[HMG_RSA_BYTES_SIZE])),
          HMG_RSA_BYTES_SIZE);

        Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaePkcs1V15Sha256GenerateTb.pPrivateKeyPtr = keyPtr;
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
** Function Name        : Cry_HaePkcs1V15Sha256GenerateUpdate                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha256   **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaePkcs1V15Sha256GenerateMainFunction() can     **
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
**                        Cry_GddHaePkcs1V15Sha256GenerateTb,                 **
**                        Cry_GddHaePkcs1V15Sha256GenerateContext             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hmg_Sha256Update                                    **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha256GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState)
  {
    Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureGenerateServiceHasCallback() == CSM_FALSE)
    {
      LblPrimitiveRet = Hmg_Sha256Update(&Cry_GddHaePkcs1V15Sha256GenerateSha256Context,
        dataPtr, dataLength);
      if (LblPrimitiveRet != HMG_SUCCESS)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaePkcs1V15Sha256GenerateTb.pDataPtr = dataPtr;
      Cry_GddHaePkcs1V15Sha256GenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaePkcs1V15Sha256GenerateFinish                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1V15**
**                        Sha256 computation and store the result into the    **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaePkcs1V15Sha256GenerateMainFunction() can     **
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
**                        Cry_GddHaePkcs1V15Sha256GenerateTb,                 **
**                        Cry_GddHaePkcs1V15Sha256GenerateContext             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hmg_Sha256Finish, Hmg_RsaPkcs1v15Sign               **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha256GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;
  uint8 LaaSha256Digest[HMG_SHA256_DIGEST_SIZE];

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState)
  {
    Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = JOB_FINISH;

    if (Csm_SignatureGenerateServiceHasCallback() == CSM_FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*resultLengthPtr < HMG_RSA_BYTES_SIZE)
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

        LblPrimitiveRet = Hmg_Sha256Finish(&Cry_GddHaePkcs1V15Sha256GenerateSha256Context,
          LaaSha256Digest);
        if (LblPrimitiveRet != HMG_SUCCESS)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        #ifdef HMG_ENABLE_CALLBACK
        Hmg_SetCallbackFunc(NULL_PTR);
        #endif

        LblPrimitiveRet = Hmg_RsaPkcs1v15Sign(
          resultPtr,
          LaaSha256Digest,
          HMG_SHA_256,
          &Cry_GddHaePkcs1V15Sha256GeneratePrivatekey);

        if (LblPrimitiveRet == HMG_SUCCESS)
        {
          *resultLengthPtr = HMG_RSA_BYTES_SIZE;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha256GenerateTb.pResultPtr = resultPtr;
      Cry_GddHaePkcs1V15Sha256GenerateTb.pResultLengthPtr = resultLengthPtr;
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
** Function Name        : Cry_HaePkcs1V15Sha256GenerateMainFunction           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureGenerateCallbackNotification() with the**
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaePkcs1V15Sha256GenerateStart() or             **
**                        Cry_HaePkcs1V15Sha256GenerateUpdate(). For          **
**                        Cry_HaePkcs1V15Sha256GenerateFinish invocation of   **
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
**                        Cry_GddHaePkcs1V15Sha256GenerateTb,                 **
**                        Cry_GddHaePkcs1V15Sha256GenerateContext             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_Sha256Start, Hmg_Sha256Update, Hmg_Sha256Finish,**
**                        Hmg_RsaPkcs1v15Sign,                                **
**                        Csm_SignatureGenerateCallbackNotification,          **
**                        Csm_SignatureGenerateServiceFinishNotification      **
*******************************************************************************/
void Cry_HaePkcs1V15Sha256GenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;
  uint8 LaaSha256Digest[HMG_SHA256_DIGEST_SIZE];

  LddReturnValue = E_OK;

  switch (Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaePkcs1V15Sha256GenerateTb.pPrivateKeyPtr->length
      != (HMG_RSA_BYTES_SIZE * CSM_TWO))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblPrimitiveRet = Hmg_Sha256Start(&Cry_GddHaePkcs1V15Sha256GenerateSha256Context);
      if (LblPrimitiveRet != HMG_SUCCESS)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      (void)memcpy((void*)Cry_GaaHaePkcs1V15Sha256GenerateModulus,
        (const void*)(Cry_GddHaePkcs1V15Sha256GenerateTb.pPrivateKeyPtr->data),
        HMG_RSA_BYTES_SIZE);
      (void)memcpy((void*)Cry_GaaHaePkcs1V15Sha256GenerateExponent,
        (const void*)(&(Cry_GddHaePkcs1V15Sha256GenerateTb.pPrivateKeyPtr->data[HMG_RSA_BYTES_SIZE])),
        HMG_RSA_BYTES_SIZE);

      Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
    }

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblPrimitiveRet = Hmg_Sha256Update(&Cry_GddHaePkcs1V15Sha256GenerateSha256Context,
      Cry_GddHaePkcs1V15Sha256GenerateTb.pDataPtr,
      Cry_GddHaePkcs1V15Sha256GenerateTb.ulDataLength);
    if (LblPrimitiveRet != HMG_SUCCESS)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;
    }

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaePkcs1V15Sha256GenerateTb.pResultLengthPtr) < HMG_RSA_BYTES_SIZE)
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

      LblPrimitiveRet = Hmg_Sha256Finish(&Cry_GddHaePkcs1V15Sha256GenerateSha256Context,
        LaaSha256Digest);
      if (LblPrimitiveRet != HMG_SUCCESS)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      #ifdef HMG_ENABLE_CALLBACK
      Hmg_SetCallbackFunc(NULL_PTR);
      #endif

      LblPrimitiveRet = Hmg_RsaPkcs1v15Sign(
        Cry_GddHaePkcs1V15Sha256GenerateTb.pResultPtr,
        LaaSha256Digest,
        HMG_SHA_256,
        &Cry_GddHaePkcs1V15Sha256GeneratePrivatekey);

      if (LblPrimitiveRet == HMG_SUCCESS)
      {
        *(Cry_GddHaePkcs1V15Sha256GenerateTb.pResultLengthPtr) = HMG_RSA_BYTES_SIZE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaePkcs1V15Sha256GenerateTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SIGNATURE_HAEPKCS1V15SHA256GENERATE == STD_ON) */
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
