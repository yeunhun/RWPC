/*******************************************************************************
**                                                                            **
**  (C) 2018~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaePkcs1V15Sha1Generate.c                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HAE Pkcs1V15 Sha1 Generate              **
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
#include "Cry_HaePkcs1V15Sha1Generate.h"
#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
#if (CSM_SIGNATURE_HAEPKCS1V15SHA1GENERATE == STD_ON)
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
} Cry_HaePkcs1V15Sha1GenerateTransferBuffer;

/*******************************************************************************
**                               Local Data                                   **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaePkcs1V15Sha1GenerateModulus[HMG_RSA_BYTES_SIZE];
static uint8 Cry_GaaHaePkcs1V15Sha1GenerateExponent[HMG_RSA_BYTES_SIZE];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static HmgRsaPrivatekey Cry_GddHaePkcs1V15Sha1GeneratePrivatekey;

static HmgSha160Ctx Cry_GddHaePkcs1V15Sha1GenerateSha1Context;

static Cry_HaePkcs1V15Sha1GenerateTransferBuffer Cry_GddHaePkcs1V15Sha1GenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaePkcs1V15Sha1GenerateInit                       **
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
** Remarks            : Global Variable(s)  :                                 **
**                      Cry_GddHaePkcs1V15Sha1GenerateTb,                     **
**                      Cry_GddHaePkcs1V15Sha1GenerateContext,                **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaePkcs1V15Sha1GenerateInit(void)
{
  Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
  Cry_GddHaePkcs1V15Sha1GenerateTb.pPrivateKeyPtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha1GenerateTb.pDataPtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha1GenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddHaePkcs1V15Sha1GenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaePkcs1V15Sha1GenerateTb.pResultLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GaaHaePkcs1V15Sha1GenerateModulus, 0x00, HMG_RSA_BYTES_SIZE);
  (void)memset((void*)&Cry_GaaHaePkcs1V15Sha1GenerateExponent, 0x00, HMG_RSA_BYTES_SIZE);

  Cry_GddHaePkcs1V15Sha1GeneratePrivatekey.modulus = Cry_GaaHaePkcs1V15Sha1GenerateModulus;
  Cry_GddHaePkcs1V15Sha1GeneratePrivatekey.exponent = Cry_GaaHaePkcs1V15Sha1GenerateExponent;

  (void)memset((void*)&Cry_GddHaePkcs1V15Sha1GenerateSha1Context, 0x00, sizeof(HmgSha160Ctx));
}

/*******************************************************************************
** Function Name        : Cry_HaePkcs1V15Sha1GenerateStart                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever Pkcs1V15 Sha1, so that it   **
**                        is able to process the input data                   **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaePkcs1V15Sha1GenerateMainFunction() can       **
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
**                        Cry_GddHaePkcs1V15Sha1GenerateTb,                   **
**                        Cry_GddHaePkcs1V15Sha1GenerateContext,              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaePkcs1V15Sha1GenerateInit,                    **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hmg_Sha160Start                                     **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha1GenerateStart(const void* cfgPtr,
  const Csm_AsymPrivateKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState)
  {
    Cry_HaePkcs1V15Sha1GenerateInit();

    Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = JOB_START;

    if (Csm_SignatureGenerateServiceHasCallback() == CSM_FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != (HMG_RSA_BYTES_SIZE * CSM_TWO))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblPrimitiveRet = Hmg_Sha160Start(&Cry_GddHaePkcs1V15Sha1GenerateSha1Context);
        if (LblPrimitiveRet != HMG_SUCCESS)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        (void)memcpy((void*)Cry_GaaHaePkcs1V15Sha1GenerateModulus,\
          (const void*)(keyPtr->data),\
          HMG_RSA_BYTES_SIZE);
        (void)memcpy((void*)Cry_GaaHaePkcs1V15Sha1GenerateExponent,\
          (const void*)(&(keyPtr->data[HMG_RSA_BYTES_SIZE])),\
          HMG_RSA_BYTES_SIZE);

        Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaePkcs1V15Sha1GenerateTb.pPrivateKeyPtr = keyPtr;
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
** Function Name        : Cry_HaePkcs1V15Sha1GenerateUpdate                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Sha1     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaePkcs1V15Sha1GenerateMainFunction() can       **
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
**                        Cry_GddHaePkcs1V15Sha1GenerateTb,                   **
**                        Cry_GddHaePkcs1V15Sha1GenerateContext               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hmg_Sha160Update                                    **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha1GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState)
  {
    Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_SignatureGenerateServiceHasCallback() == CSM_FALSE)
    {
      LblPrimitiveRet = Hmg_Sha160Update(&Cry_GddHaePkcs1V15Sha1GenerateSha1Context,
        dataPtr, dataLength);
      if (LblPrimitiveRet != HMG_SUCCESS)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaePkcs1V15Sha1GenerateTb.pDataPtr = dataPtr;
      Cry_GddHaePkcs1V15Sha1GenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaePkcs1V15Sha1GenerateFinish                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Pkcs1V15**
**                        Sha1 computation and store the result into the      **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaePkcs1V15Sha1GenerateMainFunction() can       **
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
**                        Cry_GddHaePkcs1V15Sha1GenerateTb,                   **
**                        Cry_GddHaePkcs1V15Sha1GenerateContext               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_SignatureGenerateServiceHasCallback,            **
**                        Hmg_Sha160Finish, Hmg_RsaPkcs1v15Sign               **
*******************************************************************************/
Std_ReturnType Cry_HaePkcs1V15Sha1GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;
  uint8 LaaSha1Digest[HMG_SHA160_DIGEST_SIZE];

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED(cfgId);

  if (JOB_DONE == Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState)
  {
    Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = JOB_FINISH;

    if (Csm_SignatureGenerateServiceHasCallback() == CSM_FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*resultLengthPtr < HMG_RSA_BYTES_SIZE)
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha1Digest, 0x00, sizeof(LaaSha1Digest));

        LblPrimitiveRet = Hmg_Sha160Finish(&Cry_GddHaePkcs1V15Sha1GenerateSha1Context,
          LaaSha1Digest);
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
          LaaSha1Digest,
          HMG_SHA_160,
          &Cry_GddHaePkcs1V15Sha1GeneratePrivatekey);

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
      Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha1GenerateTb.pResultPtr = resultPtr;
      Cry_GddHaePkcs1V15Sha1GenerateTb.pResultLengthPtr = resultLengthPtr;
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
** Function Name        : Cry_HaePkcs1V15Sha1GenerateMainFunction             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SignatureGenerateCallbackNotification() with the**
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaePkcs1V15Sha1GenerateStart() or               **
**                        Cry_HaePkcs1V15Sha1GenerateUpdate(). For            **
**                        Cry_HaePkcs1V15Sha1GenerateFinish invocation of     **
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
**                        Cry_GddHaePkcs1V15Sha1GenerateTb,                   **
**                        Cry_GddHaePkcs1V15Sha1GenerateContext               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_Sha160Start, Hmg_Sha160Update, Hmg_Sha160Finish,**
**                        Hmg_RsaPkcs1v15Sign,                                **
**                        Csm_SignatureGenerateCallbackNotification,          **
**                        Csm_SignatureGenerateServiceFinishNotification      **
*******************************************************************************/
void Cry_HaePkcs1V15Sha1GenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblPrimitiveRet;
  uint8 LaaSha1Digest[HMG_SHA160_DIGEST_SIZE];

  LddReturnValue = E_OK;

  switch (Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaePkcs1V15Sha1GenerateTb.pPrivateKeyPtr->length
      != (HMG_RSA_BYTES_SIZE * CSM_TWO))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblPrimitiveRet = Hmg_Sha160Start(&Cry_GddHaePkcs1V15Sha1GenerateSha1Context);
      if (LblPrimitiveRet != HMG_SUCCESS)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      (void)memcpy((void*)Cry_GaaHaePkcs1V15Sha1GenerateModulus,
        (const void*)(Cry_GddHaePkcs1V15Sha1GenerateTb.pPrivateKeyPtr->data),
        HMG_RSA_BYTES_SIZE);
      (void)memcpy((void*)Cry_GaaHaePkcs1V15Sha1GenerateExponent,
        (const void*)(&(Cry_GddHaePkcs1V15Sha1GenerateTb.pPrivateKeyPtr->data[HMG_RSA_BYTES_SIZE])),
        HMG_RSA_BYTES_SIZE);

      Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
    }

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblPrimitiveRet = Hmg_Sha160Update(&Cry_GddHaePkcs1V15Sha1GenerateSha1Context,
      Cry_GddHaePkcs1V15Sha1GenerateTb.pDataPtr,
      Cry_GddHaePkcs1V15Sha1GenerateTb.ulDataLength);
    if (LblPrimitiveRet != HMG_SUCCESS)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;
    }

    Csm_SignatureGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaePkcs1V15Sha1GenerateTb.pResultLengthPtr) < HMG_RSA_BYTES_SIZE)
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha1Digest, 0x00, sizeof(LaaSha1Digest));

      LblPrimitiveRet = Hmg_Sha160Finish(&Cry_GddHaePkcs1V15Sha1GenerateSha1Context,
        LaaSha1Digest);
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
        Cry_GddHaePkcs1V15Sha1GenerateTb.pResultPtr,
        LaaSha1Digest,
        HMG_SHA_160,
        &Cry_GddHaePkcs1V15Sha1GeneratePrivatekey);

      if (LblPrimitiveRet == HMG_SUCCESS)
      {
        *(Cry_GddHaePkcs1V15Sha1GenerateTb.pResultLengthPtr) = HMG_RSA_BYTES_SIZE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaePkcs1V15Sha1GenerateTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SIGNATURE_HAEPKCS1V15SHA1GENERATE == STD_ON) */
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
