/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmEcdh.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY HSM Ecdh Interface                      **
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
** 1.0.3     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.1     09-May-2018   Sinil        Redmine #12635                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM Ecdh */
#include "Cry_AutHsmEcdh.h"
/* Key Exchange Interface */
#if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON)
#if (CSM_KEYEXCHANGECALC_SECRET_AUTHSMECDH == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSM Ecdh Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_KeyExchangePrivateType* pPrivateKeyPtr;
  const uint8* pPartnerPublicValuePtr;
  uint32 ulPartnerPublicValueLength;
  uint8* pSharedSecretPtr;
  uint32* pSharedSecretLengthPtr;
  boolean blTruncationIsAllowed;
} Cry_AutHsmEcdhTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Hsm_DataType Cry_GddAutHsmEcdhPrivateDataType;
static Hsm_DataType Cry_GddAutHsmEcdhPartnerPublicDataType;

static Hsm_DataIDType Cry_GddAutHsmEcdhPrivateDataIDType;
static Hsm_DataIDType Cry_GddAutHsmEcdhPartnerPublicDataIDType;

/* Global structure variable for HSM Ecdh transfer buffer */
static Cry_AutHsmEcdhTransferBuffer Cry_GddAutHsmEcdhTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmEcdhCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmEcdhInit                                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Ecdh module.             **
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
**                      Cry_GddAutHsmEcdhTb                                   **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmEcdhInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmEcdhTb.ucJobState = NO_JOB;

  Cry_GddAutHsmEcdhPrivateDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmEcdhPrivateDataIDType = CSM_ZERO;
  Cry_GddAutHsmEcdhPartnerPublicDataType = HSM_DATA_INVALID_KEY;
  Cry_GddAutHsmEcdhPartnerPublicDataIDType = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEcdhStart                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM Ecdh, so that Ecdh is            **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutHsmEcdhMainFunction() can process            **
**                        initialisation                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgPtr, keyLength, iterations                       **
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
**                        Cry_GddAutHsmEcdhTb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutHsmEcdhInit,                                 **
**                        Csm_KeyExchangeServiceHasCallback,                  **
**                        Hsm_EcdhInit                                        **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEcdhStart(const void* cfgPtr,
  const Csm_KeyExchangeBaseType* basePtr,
  const Csm_KeyExchangePrivateType* privateValuePtr)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);
  CSM_PARAM_UNUSED_PTR(basePtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddAutHsmEcdhTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutHsmEcdhInit();

    /* Set the job state to JOB_START */
    Cry_GddAutHsmEcdhTb.ucJobState = JOB_START;

    LblAsync = Csm_KeyExchangeCalcSecretServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (privateValuePtr->length == CSM_ONE)
      {
        #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
        if (privateValuePtr->data[0] == HSM_DATA_CUSTOM_IAU_KEY)
        {
          Cry_GddAutHsmEcdhPrivateDataType = HSM_DATA_CUSTOM_IAU_PRIVATE_KEY;
          Cry_GddAutHsmEcdhPrivateDataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
        }
        else
        #endif
        {
          Cry_GddAutHsmEcdhPrivateDataType = HSM_DATA_ECC_PRIVATE_KEY;
          Cry_GddAutHsmEcdhPrivateDataIDType = (Hsm_DataIDType)(privateValuePtr->data[0]);
        }
        LddErr = HSM_NO_ERROR;
      }
      else if (privateValuePtr->length == HSM_ECC_KEY_BYTE_SIZE)
      {
        Cry_GddAutHsmEcdhPrivateDataType = HSM_DATA_ECC_RAM_PRIVATE_KEY;
        Cry_GddAutHsmEcdhPrivateDataIDType = CSM_THREE;

        LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PRIVATE_KEY, CSM_THREE,
          privateValuePtr->length, (const uint8*)(privateValuePtr->data));
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_EcdhInit(LblAsync, NULL_PTR,
          Cry_GddAutHsmEcdhPrivateDataType, Cry_GddAutHsmEcdhPrivateDataIDType);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* if return is Success, set job state to JOB_DONE */
        Cry_GddAutHsmEcdhTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* if return is failure, set job state to NO_JOB */
        Cry_GddAutHsmEcdhTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmEcdhTb.pPrivateKeyPtr = privateValuePtr;
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
** Function Name        : Cry_AutHsmEcdhUpdate                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Ecdh     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmEcdhMainFunction() can process the        **
**                        input                                               **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, passwordPtr, passwordLength, saltPtr,        **
**                        saltLength                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmEcdhTb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_KeyExchangeCalcSecretServiceHasCallback,        **
**                        Csm_KeyExchangeCalcSecretCallbackNotification,      **
**                        Hsm_EcdhUpdate                                      **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEcdhUpdate(Csm_ConfigIdType cfgId,
  const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutHsmEcdhTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutHsmEcdhTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_KeyExchangeCalcSecretServiceHasCallback();

    if (LblAsync == FALSE)
    {
      if (partnerPublicValueLength == CSM_ONE)
      {
        #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
        if (partnerPublicValuePtr[0] == HSM_DATA_CUSTOM_IAU_KEY)
        {
          Cry_GddAutHsmEcdhPartnerPublicDataType = HSM_DATA_CUSTOM_IAU_PUBLIC_KEY;
          Cry_GddAutHsmEcdhPartnerPublicDataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
        }
        else
        #endif
        {
          Cry_GddAutHsmEcdhPartnerPublicDataType = HSM_DATA_ECC_PUBLIC_KEY;
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          Cry_GddAutHsmEcdhPartnerPublicDataIDType = (Hsm_DataIDType)(partnerPublicValuePtr[0]);
        }
        LddErr = HSM_NO_ERROR;
      }
      else if (partnerPublicValueLength == (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
      {
        Cry_GddAutHsmEcdhPartnerPublicDataType = HSM_DATA_ECC_RAM_PUBLIC_KEY;
        Cry_GddAutHsmEcdhPartnerPublicDataIDType = CSM_THREE;

        LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PUBLIC_KEY, CSM_THREE,
          partnerPublicValueLength, partnerPublicValuePtr);
      }
      else
      {
        LddErr = HSM_KEY_INVALID_ERROR;
      }

      if (LddErr == HSM_NO_ERROR)
      {
        LddErr = Hsm_EcdhUpdate(LblAsync, NULL_PTR,
          Cry_GddAutHsmEcdhPartnerPublicDataType,
          Cry_GddAutHsmEcdhPartnerPublicDataIDType);
      }

      if (LddErr == HSM_NO_ERROR)
      {
        /* Set the job state to JOB_DONE */
        Cry_GddAutHsmEcdhTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* Set the job state to NO_JOB */
        Cry_GddAutHsmEcdhTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutHsmEcdhTb.pPartnerPublicValuePtr = partnerPublicValuePtr;
      Cry_GddAutHsmEcdhTb.ulPartnerPublicValueLength = partnerPublicValueLength;
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
** Function Name        : Cry_AutHsmEcdhFinish                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Ecdh    **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutHsmEcdhMainFunction() can finish the         **
**                        computation and store the result in the memory      **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : keyPtr                                              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                                                                            **
** Preconditions        : Primitive should have been successfuly initialized  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Cry_GddAutHsmEcdhTb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_KeyExchangeCalcSecretServiceHasCallback,        **
**                        Csm_KeyExchangeCalcSecretCallbackNotification,      **
**                        Csm_KeyExchangeCalcSecretServiceFinishNotification, **
**                        Hsm_EcdhFinish                                      **
*******************************************************************************/
Std_ReturnType Cry_AutHsmEcdhFinish(Csm_ConfigIdType cfgId,
  uint8* sharedSecretPtr, uint32* sharedSecretLengthPtr,
  boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutHsmEcdhTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddAutHsmEcdhTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_KeyExchangeCalcSecretServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*sharedSecretLengthPtr < HSM_ECC_KEY_BYTE_SIZE)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        LddErr = Hsm_EcdhFinish(LblAsync, NULL_PTR,
          sharedSecretPtr, *sharedSecretLengthPtr);

        if (LddErr != HSM_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* reset the state back to NO_JOB */
      Cry_GddAutHsmEcdhTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmEcdhTb.pSharedSecretPtr = sharedSecretPtr;
      Cry_GddAutHsmEcdhTb.pSharedSecretLengthPtr = sharedSecretLengthPtr;
      Cry_GddAutHsmEcdhTb.blTruncationIsAllowed = TruncationIsAllowed;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEcdhCallback                              **
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
**                        Cry_GddAutHsmEcdhTb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_KeyExchangeCalcSecretCallbackNotification,      **
**                        Csm_KeyExchangeCalcSecretServiceFinishNotification  **
*******************************************************************************/
static void Cry_AutHsmEcdhCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;

    Csm_KeyExchangeCalcSecretCallbackNotification(LddReturnValue);
  }
  else
  {
    LddReturnValue = E_OK;

    switch (Cry_GddAutHsmEcdhTb.ucJobState)
    {
    case JOB_START:
    case JOB_UPDATE:
      if (ddRet == HSM_NO_ERROR)
      {
        Cry_GddAutHsmEcdhTb.ucJobState = JOB_DONE;
      }
      else
      {
        LddReturnValue = E_NOT_OK;

        /* task failure move job state to NO_JOB */
        Cry_GddAutHsmEcdhTb.ucJobState = NO_JOB;
      }
      Csm_KeyExchangeCalcSecretCallbackNotification(LddReturnValue);
      break;

    case JOB_FINISH:
      if (ddRet != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
      Cry_GddAutHsmEcdhTb.ucJobState = NO_JOB;
      Csm_KeyExchangeCalcSecretCallbackNotification(LddReturnValue);
      break;

    default:
      Csm_KeyExchangeCalcSecretServiceFinishNotification();
      break;
    }
  }
}

/*******************************************************************************
** Function Name        : Cry_AutHsmEcdhMainFunction                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_KeyExchangeCalcSecretCallbackNotification()     **
**                        with the correct return value once the main function**
**                        has completely processed the cryptographic          **
**                        functions demanded by                               **
**                        Cry_AutHsmEcdhStart() or                            **
**                        Cry_AutHsmEcdhUpdate(). For                         **
**                        Cry_AutHsmEcdhFinish invocation of                  **
**                        Csm_KeyExchangeCalcSecretCallbackNotification()     **
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
**                        Cry_GddAutHsmEcdhTb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hsm_HmacSha160Init                                  **
**                        Hsm_HmacSha160Update                                **
**                        Hsm_HmacSha160Finish                                **
**                        Csm_KeyExchangeCalcSecretCallbackNotification       **
**                        Csm_KeyExchangeCalcSecretServiceFinishNotification  **
*******************************************************************************/
void Cry_AutHsmEcdhMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LddReturnValue = E_OK;

  LpCallback = &Cry_AutHsmEcdhCallback;

  switch (Cry_GddAutHsmEcdhTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddAutHsmEcdhTb.pPrivateKeyPtr->length == CSM_ONE)
    {
      #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
      if (Cry_GddAutHsmEcdhTb.pPrivateKeyPtr->data[0] == HSM_DATA_CUSTOM_IAU_KEY)
      {
        Cry_GddAutHsmEcdhPrivateDataType = HSM_DATA_CUSTOM_IAU_PRIVATE_KEY;
        Cry_GddAutHsmEcdhPrivateDataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
      }
      else
      #endif
      {
        Cry_GddAutHsmEcdhPrivateDataType = HSM_DATA_ECC_PRIVATE_KEY;
        Cry_GddAutHsmEcdhPrivateDataIDType
          = (Hsm_DataIDType)(Cry_GddAutHsmEcdhTb.pPrivateKeyPtr->data[0]);
      }
      LddErr = HSM_NO_ERROR;
    }
    else if (Cry_GddAutHsmEcdhTb.pPrivateKeyPtr->length == HSM_ECC_KEY_BYTE_SIZE)
    {
      Cry_GddAutHsmEcdhPrivateDataType = HSM_DATA_ECC_RAM_PRIVATE_KEY;
      Cry_GddAutHsmEcdhPrivateDataIDType = CSM_THREE;

      LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PRIVATE_KEY, CSM_THREE,
        Cry_GddAutHsmEcdhTb.pPrivateKeyPtr->length,
        (const uint8*)(Cry_GddAutHsmEcdhTb.pPrivateKeyPtr->data));
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_EcdhInit(CSM_TRUE, LpCallback,
        Cry_GddAutHsmEcdhPrivateDataType, Cry_GddAutHsmEcdhPrivateDataIDType);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      Cry_GddAutHsmEcdhTb.ucJobState = NO_JOB;

      Csm_KeyExchangeCalcSecretCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_UPDATE:
    if (Cry_GddAutHsmEcdhTb.ulPartnerPublicValueLength == CSM_ONE)
    {
      #if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
      /* polyspace +2 MISRA-C3:11.3,18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      if (Cry_GddAutHsmEcdhTb.pPartnerPublicValuePtr[0] == HSM_DATA_CUSTOM_IAU_KEY)
      {
        Cry_GddAutHsmEcdhPartnerPublicDataType = HSM_DATA_CUSTOM_IAU_PUBLIC_KEY;
        Cry_GddAutHsmEcdhPartnerPublicDataIDType = (Hsm_DataIDType)HSM_DATA_CUSTOM_IAU_KEY;
      }
      else
      #endif
      {
        /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        Cry_GddAutHsmEcdhPartnerPublicDataType = HSM_DATA_ECC_PUBLIC_KEY;
        Cry_GddAutHsmEcdhPartnerPublicDataIDType
          = (Hsm_DataIDType)(Cry_GddAutHsmEcdhTb.pPartnerPublicValuePtr[0]);
      }
      LddErr = HSM_NO_ERROR;
    }
    else if (Cry_GddAutHsmEcdhTb.ulPartnerPublicValueLength == (HSM_ECC_KEY_BYTE_SIZE * CSM_TWO))
    {
      Cry_GddAutHsmEcdhPartnerPublicDataType = HSM_DATA_ECC_RAM_PUBLIC_KEY;
      Cry_GddAutHsmEcdhPartnerPublicDataIDType = CSM_THREE;

      LddErr = Hsm_LoadRamKey(HSM_DATA_ECC_RAM_PUBLIC_KEY, CSM_THREE,
        Cry_GddAutHsmEcdhTb.ulPartnerPublicValueLength,
        Cry_GddAutHsmEcdhTb.pPartnerPublicValuePtr);
    }
    else
    {
      LddErr = HSM_KEY_INVALID_ERROR;
    }

    if (LddErr == HSM_NO_ERROR)
    {
      LddErr = Hsm_EcdhUpdate(CSM_TRUE, LpCallback,
        Cry_GddAutHsmEcdhPartnerPublicDataType,
        Cry_GddAutHsmEcdhPartnerPublicDataIDType);
    }

    if (LddErr != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;

      /* if return is failure, set job state to NO_JOB */
      Cry_GddAutHsmEcdhTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_KeyExchangeCalcSecretCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_FINISH:

    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((*(Cry_GddAutHsmEcdhTb.pSharedSecretLengthPtr) < HSM_ECC_KEY_BYTE_SIZE)
      && (Cry_GddAutHsmEcdhTb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      LddErr = Hsm_EcdhFinish(CSM_TRUE, LpCallback,
        Cry_GddAutHsmEcdhTb.pSharedSecretPtr,
        *(Cry_GddAutHsmEcdhTb.pSharedSecretLengthPtr));

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue != E_OK)
    {
      /* reset the state back to NO_JOB */
      Cry_GddAutHsmEcdhTb.ucJobState = NO_JOB;

      /* Notify respective Service about the completion of the task */
      Csm_KeyExchangeCalcSecretCallbackNotification(LddReturnValue);
    }
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_KeyExchangeCalcSecretServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_KEYEXCHANGECALC_SECRET_AUTHSMECDH == STD_ON) */
#endif /* (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
