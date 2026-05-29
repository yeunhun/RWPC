/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmEcdh.c                                              **
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
** 1.0.1     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.0     23-Mar-2020   EK Kim       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HSM Ecdh */
#include "Cry_HaeHsmEcdh.h"
/* Key Exchange Interface */
#if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON)
#if (CSM_KEYEXCHANGECALC_SECRET_HAEHSMECDH == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "Hsm_HostAPI.h"
#include "CryptoService_Ecc.h"
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
} Cry_HaeHsmEcdhTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Autoever ECC ECDH primitive library context */
static HSMAPI_CTX_t Cry_GddHaeHsmEcdhContext;


/* Global structure variable for HSM Ecdh transfer buffer */
static Cry_HaeHsmEcdhTransferBuffer Cry_GddHaeHsmEcdhTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHsmEcdhInit                                    **
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
**                      Cry_GddHaeHsmEcdhTb                                   **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmEcdhInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHsmEcdhTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmEcdhTb.pPrivateKeyPtr = NULL_PTR;
  Cry_GddHaeHsmEcdhTb.pPartnerPublicValuePtr = NULL_PTR;
  Cry_GddHaeHsmEcdhTb.ulPartnerPublicValueLength = CSM_ZERO;
  Cry_GddHaeHsmEcdhTb.pSharedSecretPtr = NULL_PTR;
  Cry_GddHaeHsmEcdhTb.pSharedSecretLengthPtr = NULL_PTR;
  Cry_GddHaeHsmEcdhTb.blTruncationIsAllowed = CSM_ZERO;

  (void)memset((void*)&Cry_GddHaeHsmEcdhContext, 0x00,
    sizeof(HSMAPI_CTX_t));
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmEcdhStart                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of HSM Ecdh, so that Ecdh is            **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHsmEcdhMainFunction() can process            **
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
**                        Cry_GddHaeHsmEcdhTb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeHsmEcdhInit,                                 **
**                        Csm_KeyExchangeServiceHasCallback,                  **
**                        Hsm_EcdhInit                                        **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmEcdhStart(const void* cfgPtr,
  const Csm_KeyExchangeBaseType* basePtr,
  const Csm_KeyExchangePrivateType* privateValuePtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblAsync;
  uint16 LusKeyNum;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);
  CSM_PARAM_UNUSED_PTR(basePtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddHaeHsmEcdhTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeHsmEcdhInit();

    /* Set the job state to JOB_START */
    Cry_GddHaeHsmEcdhTb.ucJobState = JOB_START;

    LblAsync = Csm_KeyExchangeCalcSecretServiceHasCallback();

    if (LblAsync == FALSE)
    {
       LusKeyNum = CSM_ZERO;
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (privateValuePtr->length == CSM_ONE)
      {
        LusKeyNum = privateValuePtr->data[CSM_ZERO];
      }
      else if (privateValuePtr->length == CSM_TWO)
      {
        LusKeyNum = privateValuePtr->data[CSM_ZERO];
        /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
	      LusKeyNum |= (privateValuePtr->data[CSM_ONE]) << 8;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_EccEcdhStart(&Cry_GddHaeHsmEcdhContext, LusKeyNum);

        if (LddReturnValue != E_OK)
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmEcdhTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmEcdhTb.ucJobState = NO_JOB;
      }

    }
    else
    {
      Cry_GddHaeHsmEcdhTb.pPrivateKeyPtr = privateValuePtr;
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
** Function Name        : Cry_HaeHsmEcdhUpdate                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Ecdh     **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmEcdhMainFunction() can process the        **
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
**                        Cry_GddHaeHsmEcdhTb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_KeyExchangeCalcSecretServiceHasCallback,        **
**                        Csm_KeyExchangeCalcSecretCallbackNotification,      **
**                        Hsm_EcdhUpdate                                      **
*******************************************************************************/

Std_ReturnType Cry_HaeHsmEcdhUpdate(Csm_ConfigIdType cfgId,
  const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength)
{
  Std_ReturnType LddReturnValue;

  boolean LblAsync;
  uint32 LulTimeout;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeHsmEcdhTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddHaeHsmEcdhTb.ucJobState = JOB_UPDATE;

    LblAsync = Csm_KeyExchangeCalcSecretServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:11.3,11.8 [Justified:Low] "No Impact of this rule violation" */
      LddReturnValue = HSM_EccEcdhUpdate(&Cry_GddHaeHsmEcdhContext, (ECC_PUBLICKEY_t *)partnerPublicValuePtr);

      if (LddReturnValue == E_OK)
      {
        LulTimeout = CSM_ZERO;
        do
        {
          LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmEcdhContext.jobId);
          LulTimeout++;
        } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

        if (LddReturnValue != E_OK)
        {
          (void)HSM_CancelJob(Cry_GddHaeHsmEcdhContext.jobId);
        }
      }

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHsmEcdhTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHsmEcdhTb.ucJobState = NO_JOB;
      }

    }

    else
    {
      Cry_GddHaeHsmEcdhTb.pPartnerPublicValuePtr = partnerPublicValuePtr;
      Cry_GddHaeHsmEcdhTb.ulPartnerPublicValueLength = partnerPublicValueLength;
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
** Function Name        : Cry_HaeHsmEcdhFinish                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Ecdh    **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHsmEcdhMainFunction() can finish the         **
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
**                        Cry_GddHaeHsmEcdhTb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_KeyExchangeCalcSecretServiceHasCallback,        **
**                        Csm_KeyExchangeCalcSecretCallbackNotification,      **
**                        Csm_KeyExchangeCalcSecretServiceFinishNotification, **
**                        Hsm_EcdhFinish                                      **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmEcdhFinish(Csm_ConfigIdType cfgId,
  uint8* sharedSecretPtr, uint32* sharedSecretLengthPtr,
  boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  boolean LblAsync;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeHsmEcdhTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddHaeHsmEcdhTb.ucJobState = JOB_FINISH;

    LblAsync = Csm_KeyExchangeCalcSecretServiceHasCallback();

    if (LblAsync == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*sharedSecretLengthPtr < ECC_BYTES_SIZE)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_EccEcdhFinish(&Cry_GddHaeHsmEcdhContext, sharedSecretPtr);
      }

      /* reset the state back to NO_JOB */
      Cry_GddHaeHsmEcdhTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHsmEcdhTb.pSharedSecretPtr = sharedSecretPtr;
      Cry_GddHaeHsmEcdhTb.pSharedSecretLengthPtr = sharedSecretLengthPtr;
      Cry_GddHaeHsmEcdhTb.blTruncationIsAllowed = TruncationIsAllowed;
    }
  }
  else
  {
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}


/*******************************************************************************
** Function Name        : Cry_HaeHsmEcdhMainFunction                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_KeyExchangeCalcSecretCallbackNotification()     **
**                        with the correct return value once the main function**
**                        has completely processed the cryptographic          **
**                        functions demanded by                               **
**                        Cry_HaeHsmEcdhStart() or                            **
**                        Cry_HaeHsmEcdhUpdate(). For                         **
**                        Cry_HaeHsmEcdhFinish invocation of                  **
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
**                        Cry_GddHaeHsmEcdhTb                                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hsm_HmacSha160Init                                  **
**                        Hsm_HmacSha160Update                                **
**                        Hsm_HmacSha160Finish                                **
**                        Csm_KeyExchangeCalcSecretCallbackNotification       **
**                        Csm_KeyExchangeCalcSecretServiceFinishNotification  **
*******************************************************************************/
void Cry_HaeHsmEcdhMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint16 LusKeyNum;
  uint32 LulTimeout;

  LddReturnValue = E_OK;

  switch (Cry_GddHaeHsmEcdhTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +11 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +10 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeHsmEcdhTb.pPrivateKeyPtr->length == CSM_ONE)
    {
      LusKeyNum = Cry_GddHaeHsmEcdhTb.pPrivateKeyPtr->data[CSM_ZERO];
    }
    else if (Cry_GddHaeHsmEcdhTb.pPrivateKeyPtr->length == CSM_TWO)
    {
      LusKeyNum = Cry_GddHaeHsmEcdhTb.pPrivateKeyPtr->data[CSM_ZERO];
      /* polyspace +1 MISRA-C3:10.6,10.7,12.2 [Justified:Low] "No Impact of this rule violation" */
      LusKeyNum |= (Cry_GddHaeHsmEcdhTb.pPrivateKeyPtr->data[CSM_ONE]) << 8;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = HSM_EccEcdhStart(&Cry_GddHaeHsmEcdhContext, LusKeyNum);

      if (LddReturnValue != E_OK)
      {
        LddReturnValue = E_NOT_OK;
        HSM_HaeGetErrorCode();
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmEcdhTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmEcdhTb.ucJobState = NO_JOB;
    }

    Csm_KeyExchangeCalcSecretCallbackNotification(LddReturnValue);

    break;

  case JOB_UPDATE:

    /* polyspace +1 MISRA-C3:11.3 [Justified:Low] "No Impact of this rule violation" */
    LddReturnValue = HSM_EccEcdhUpdate(&Cry_GddHaeHsmEcdhContext, (const ECC_PUBLICKEY_t *)Cry_GddHaeHsmEcdhTb.pPartnerPublicValuePtr);

    if (LddReturnValue == E_OK)
    {
      LulTimeout = CSM_ZERO;
      do
      {
        LddReturnValue = HSM_WaitResp(Cry_GddHaeHsmEcdhContext.jobId);
        LulTimeout++;
      } while ((LddReturnValue == HSM_E_WAIT) && (LulTimeout < CRYPTOLIB_HAE_HSM_TIMEOUT));

      if (LddReturnValue != E_OK)
      {
        (void)HSM_CancelJob(Cry_GddHaeHsmEcdhContext.jobId);
      }
    }

    if (LddReturnValue != E_OK)
    {
      LddReturnValue = E_NOT_OK;
      HSM_HaeGetErrorCode();
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHsmEcdhTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHsmEcdhTb.ucJobState = NO_JOB;
    }


    /* Notify respective Service about the completion of the task */
    Csm_KeyExchangeCalcSecretCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace-begin RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace-begin MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((*(Cry_GddHaeHsmEcdhTb.pSharedSecretLengthPtr) < ECC_BYTES_SIZE)
      && (Cry_GddHaeHsmEcdhTb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      LddReturnValue = HSM_EccEcdhFinish(&Cry_GddHaeHsmEcdhContext, Cry_GddHaeHsmEcdhTb.pSharedSecretPtr);
    }

    /* reset the state back to NO_JOB */
    Cry_GddHaeHsmEcdhTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_KeyExchangeCalcSecretCallbackNotification(LddReturnValue);
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

#endif /* (CSM_KEYEXCHANGECALC_SECRET_HAEHSMECDH == STD_ON) */
#endif /* (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */
/* polyspace-end RTE:IDP [Justified:Low] "No Impact of this rule violation" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
