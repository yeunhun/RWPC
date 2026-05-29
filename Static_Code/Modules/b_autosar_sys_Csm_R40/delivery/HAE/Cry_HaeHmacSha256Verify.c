/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHmacSha256Verify.c                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever HMAC Sha256 Verify Interface   **
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
** 1.0.0     13-Feb-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Autoever HMAC Sha256 Verify */
#include "Cry_HaeHmacSha256Verify.h"
/* Mac Interface */
#if (CSM_MAC_VERIFY_STATUS == STD_ON)
#if (CSM_MAC_HAEHMACSHA256VERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_HmacSha256.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeHmacSha256Verify Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* pointer to the key necessary for the Autoever HMAC Sha256 generation */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores raw data pointer used for Autoever HMAC Sha256 Computation */
  const uint8* pDataPtr;
  /* Data length of the data used for Autoever HMAC Sha256 Computation */
  uint32 ulDataLength;
  /* Stores Autoever HMAC Sha256 provided for verification */
  const uint8* pMacPtr;
  /* length of the provided Autoever HMAC Sha256 */
  uint32 ulMacLength;
  /* Stores verification result */
  Csm_VerifyResultType* pResultPtr;
} Cry_HaeHmacSha256VerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Autoever HMAC Sha256 primitive library context */
static HmgHmacSha256Ctx Cry_GddHaeHmacSha256VerifyContext;

/* Global variable for Autoever HMAC Sha256 transfer buffer structure */
static Cry_HaeHmacSha256VerifyTransferBuffer Cry_GddHaeHmacSha256VerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHmacSha256VerifyInit                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Autoever HMAC Sha256     **
**                      module. All the Global variables will be initialized  **
**                      after the successful completion of this API.          **
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
** Remarks            : Global Variable(s):  Cry_GddHaeHmacSha256VerifyTb     **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHmacSha256VerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHmacSha256VerifyTb.ucJobState = NO_JOB;
  Cry_GddHaeHmacSha256VerifyTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeHmacSha256VerifyTb.pDataPtr = NULL_PTR;
  Cry_GddHaeHmacSha256VerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeHmacSha256VerifyTb.pMacPtr = NULL_PTR;
  Cry_GddHaeHmacSha256VerifyTb.ulMacLength = CSM_ZERO;
  Cry_GddHaeHmacSha256VerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeHmacSha256VerifyContext, 0x00,
    sizeof(HmgHmacSha256Ctx));
}

/*******************************************************************************
** Function Name        : Cry_HaeHmacSha256VerifyStart                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever HMAC Sha256, so that if is  **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHmacSha256VerifyMainFunction() can process   **
**                        initialisation                                      **
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
**                        Cry_GddHaeHmacSha256VerifyTb                        **
**                        Cry_GpHaeHmacSha256VerifyConfigPtr                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_HmacSha256Start                                 **
*******************************************************************************/
Std_ReturnType Cry_HaeHmacSha256VerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddHaeHmacSha256VerifyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeHmacSha256VerifyInit();

    Cry_GddHaeHmacSha256VerifyTb.ucJobState = JOB_START;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LblReturnValue = Hmg_HmacSha256Start(&Cry_GddHaeHmacSha256VerifyContext,
        (const uint8*)((const void*)(keyPtr->data)), keyPtr->length);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHmacSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHmacSha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHmacSha256VerifyTb.pKeyPtr = keyPtr;
    }
  }
  else
  {
    /* Job is busy in processing other job, set the return value to CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_HaeHmacSha256VerifyUpdate                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Autoever **
**                        HMAC Sha256                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHmacSha256VerifyMainFunction() can process   **
**                        the input                                           **
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
**                        Cry_GddHaeHmacSha256VerifyTb                        **
**                        Cry_GpHaeHmacSha256VerifyConfigPtr                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_HmacSha256Update                                **
*******************************************************************************/
Std_ReturnType Cry_HaeHmacSha256VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeHmacSha256VerifyTb.ucJobState)
  {
    Cry_GddHaeHmacSha256VerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      LblReturnValue = Hmg_HmacSha256Update(&Cry_GddHaeHmacSha256VerifyContext,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHmacSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHmacSha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHmacSha256VerifyTb.pDataPtr = dataPtr;
      Cry_GddHaeHmacSha256VerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeHmacSha256VerifyFinish                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Autoever**
**                        HMAC Sha256 computation and store the result into   **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHmacSha256VerifyMainFunction() can finish the**
**                        computation and store the result in the memory      **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, MacPtr, MacLength                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
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
**                        Cry_GddHaeHmacSha256VerifyTb                        **
**                        Cry_GpHaeHmacSha256VerifyConfigPtr                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_HmacSha256Finish                                **
*******************************************************************************/
Std_ReturnType Cry_HaeHmacSha256VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha256Digest[HMG_SHA256_DIGEST_SIZE];
  uint32 LulIndex;
  boolean LblResult;
  uint32 LulMacLength;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeHmacSha256VerifyTb.ucJobState)
  {
    Cry_GddHaeHmacSha256VerifyTb.ucJobState = JOB_FINISH;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

      LblReturnValue = Hmg_HmacSha256Finish(&Cry_GddHaeHmacSha256VerifyContext,
        LaaSha256Digest);

      if (LblReturnValue != CSM_TRUE)
      {
        LulMacLength = MacLength;
        if (LulMacLength > HMG_SHA256_DIGEST_SIZE * CSM_EIGHT)
        {
          LulMacLength = HMG_SHA256_DIGEST_SIZE * CSM_EIGHT;
        }

        /* Comparing the two MACs */
        LblResult = CSM_TRUE;
        /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The length is checked" */
        for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          if (MacPtr[LulIndex] != LaaSha256Digest[LulIndex])
          {
            LblResult = CSM_FALSE;
            break;
          }
        }
        if ((LblResult == CSM_TRUE)
          && ((LulMacLength % CSM_EIGHT) > CSM_ZERO) )
        {
          for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength % CSM_EIGHT); LulIndex++)
          {
            /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
	          /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP RTE:OBAI [Justified:Low] "No Impact of this rule violation" */
            if ((MacPtr[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
              != (LaaSha256Digest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
            {
              LblResult = CSM_FALSE;
              break;
            }
          }
        }

        if (LblResult == CSM_TRUE)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          *resultPtr = CSM_E_VER_OK;
        }
        else
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          *resultPtr = CSM_E_VER_NOT_OK;
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHmacSha256VerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHmacSha256VerifyTb.pMacPtr = MacPtr;
      Cry_GddHaeHmacSha256VerifyTb.ulMacLength = MacLength;
      Cry_GddHaeHmacSha256VerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_HaeHmacSha256VerifyMainFunction                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacVerifyCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeHmacSha256VerifyStart() or                   **
**                        Cry_HaeHmacSha256VerifyUpdate(). For                **
**                        Cry_HaeHmacSha256VerifyFinish invocation of         **
**                        Csm_MacVerifyCallbackNotification()                 **
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
**                        Cry_GddHaeHmacSha256VerifyTb                        **
**                        Cry_GpHaeHmacSha256VerifyConfigPtr                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_HmacSha256Start                                 **
**                        Hmg_HmacSha256Update                                **
**                        Hmg_HmacSha256Finish                                **
**                        Csm_MacVerifyCallbackNotification                   **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
void Cry_HaeHmacSha256VerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha256Digest[HMG_SHA256_DIGEST_SIZE];
  uint32 LulIndex;
  boolean LblResult;
  uint32 LulMacLength;
  const uint8* LpMacPtr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeHmacSha256VerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +4 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +3 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    LblReturnValue = Hmg_HmacSha256Start(&Cry_GddHaeHmacSha256VerifyContext,
      (const uint8*)((const void*)(Cry_GddHaeHmacSha256VerifyTb.pKeyPtr->data)),
      Cry_GddHaeHmacSha256VerifyTb.pKeyPtr->length);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHmacSha256VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHmacSha256VerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = Hmg_HmacSha256Update(&Cry_GddHaeHmacSha256VerifyContext,
      Cry_GddHaeHmacSha256VerifyTb.pDataPtr,
      Cry_GddHaeHmacSha256VerifyTb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHmacSha256VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHmacSha256VerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

    LblReturnValue = Hmg_HmacSha256Finish(&Cry_GddHaeHmacSha256VerifyContext,
      LaaSha256Digest);

    if (LblReturnValue != CSM_TRUE)
    {
      LulMacLength = Cry_GddHaeHmacSha256VerifyTb.ulMacLength;
      LpMacPtr = Cry_GddHaeHmacSha256VerifyTb.pMacPtr;

      if (LulMacLength > HMG_SHA256_DIGEST_SIZE * CSM_EIGHT)
      {
        LulMacLength = HMG_SHA256_DIGEST_SIZE * CSM_EIGHT;
      }

      /* Comparing the two MACs */
      LblResult = CSM_TRUE;
      for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
      {
	/* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	/* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
        if (LpMacPtr[LulIndex] != LaaSha256Digest[LulIndex])
        {
          LblResult = CSM_FALSE;
          break;
        }
      }
      if ((LblResult == CSM_TRUE)
        && ((LulMacLength % CSM_EIGHT) > CSM_ZERO) )
      {
        for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength % CSM_EIGHT); LulIndex++)
        {
	  /* polyspace +3 RTE:IDP,OBAI [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          if ((LpMacPtr[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
            != (LaaSha256Digest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
          {
            LblResult = CSM_FALSE;
            break;
          }
        }
      }
      /* polyspace +9 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      /* polyspace +8 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      if (LblResult == CSM_TRUE)
      {
        *(Cry_GddHaeHmacSha256VerifyTb.pResultPtr) = CSM_E_VER_OK;
      }
      else
      {
        *(Cry_GddHaeHmacSha256VerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeHmacSha256VerifyTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_MacVerifyServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_MAC_HAEHMACSHA256VERIFY == STD_ON) */
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
