/*******************************************************************************
**                                                                            **
**  (C) 2016~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscHmacSha256Verify.c                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt HMAC SHA256 Verify Interface    **
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
** 1.2.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.1     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198, #7323                  **
** 1.0.1     28-Sep-2016   Sinil        #6128                                 **
** 1.0.0     27-Sep-2016   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:D4.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Escrypt HMAC SHA256 Verify */
#include "Cry_EscHmacSha256Verify.h"
/* Mac Interface */
#if (CSM_MAC_VERIFY_STATUS == STD_ON)
#if (CSM_MAC_ESCHMACSHA256VERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "hmac_sha_2.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry EscHmacSha256Verify Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* pointer to the key necessary for the Escrypt HMAC SHA256 generation */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores raw data pointer used for Escrypt HMAC SHA256 Computation */
  const uint8* pDataPtr;
  /* Data length of the data used for Escrypt HMAC SHA256 Computation */
  uint32 ulDataLength;
  /* Stores Escrypt HMAC SHA256 provided for verification */
  const uint8* pMacPtr;
  /* length of the provided Escrypt HMAC SHA256 */
  uint32 ulMacLength;
  /* Stores verification result */
  Csm_VerifyResultType* pResultPtr;
} Cry_EscHmacSha256VerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Escrypt HMAC SHA256 primitive library context */
static EscHmacSha256_ContextT Cry_GddEscHmacSha256VerifyContext;

/* Global variable for Escrypt HMAC SHA256 transfer buffer structure */
static Cry_EscHmacSha256VerifyTransferBuffer Cry_GddEscHmacSha256VerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscHmacSha256VerifyInit                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Escrypt HMAC SHA256      **
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
** Remarks            : Global Variable(s):  Cry_GddEscHmacSha256VerifyTb     **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_EscHmacSha256VerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscHmacSha256VerifyTb.ucJobState = NO_JOB;
  Cry_GddEscHmacSha256VerifyTb.pKeyPtr = NULL_PTR;
  Cry_GddEscHmacSha256VerifyTb.pDataPtr = NULL_PTR;
  Cry_GddEscHmacSha256VerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddEscHmacSha256VerifyTb.pMacPtr = NULL_PTR;
  Cry_GddEscHmacSha256VerifyTb.ulMacLength = CSM_ZERO;
  Cry_GddEscHmacSha256VerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddEscHmacSha256VerifyContext, 0x00,
    sizeof(EscHmacSha256_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscHmacSha256VerifyStart                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt HMAC SHA256, so that if is   **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscHmacSha256VerifyMainFunction() can process   **
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
**                        Cry_GddEscHmacSha256VerifyTb                        **
**                        Cry_GpEscHmacSha256VerifyConfigPtr                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha256_Init                                  **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha256VerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddEscHmacSha256VerifyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_EscHmacSha256VerifyInit();

    Cry_GddEscHmacSha256VerifyTb.ucJobState = JOB_START;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LblReturnValue = EscHmacSha256_Init(&Cry_GddEscHmacSha256VerifyContext,
        (const uint8*)((const void*)(keyPtr->data)), keyPtr->length);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscHmacSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscHmacSha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscHmacSha256VerifyTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_EscHmacSha256VerifyUpdate                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Escrypt  **
**                        HMAC SHA256                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscHmacSha256VerifyMainFunction() can process   **
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
**                        Cry_GddEscHmacSha256VerifyTb                        **
**                        Cry_GpEscHmacSha256VerifyConfigPtr                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha256_Update                                **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha256VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddEscHmacSha256VerifyTb.ucJobState)
  {
    Cry_GddEscHmacSha256VerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      LblReturnValue = EscHmacSha256_Update(&Cry_GddEscHmacSha256VerifyContext,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscHmacSha256VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscHmacSha256VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscHmacSha256VerifyTb.pDataPtr = dataPtr;
      Cry_GddEscHmacSha256VerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_EscHmacSha256VerifyFinish                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Escrypt **
**                        HMAC SHA256 computation and store the result into   **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscHmacSha256VerifyMainFunction() can finish the**
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
**                        Cry_GddEscHmacSha256VerifyTb                        **
**                        Cry_GpEscHmacSha256VerifyConfigPtr                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha256_Finish                                **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha256VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha256Digest[EscSha256_DIGEST_LEN];
  uint32 LulIndex;
  uint32 LulMacLength;
  Csm_VerifyResultType LddVerifyResult;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddEscHmacSha256VerifyTb.ucJobState)
  {
    Cry_GddEscHmacSha256VerifyTb.ucJobState = JOB_FINISH;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

      LblReturnValue = EscHmacSha256_Finish(&Cry_GddEscHmacSha256VerifyContext,
        LaaSha256Digest);

      if (LblReturnValue != CSM_TRUE)
      {
        LulMacLength = MacLength;
        LddVerifyResult = CSM_E_VER_OK;
        if (LulMacLength > EscSha256_DIGEST_LEN * CSM_EIGHT)
        {
          LulMacLength = EscSha256_DIGEST_LEN * CSM_EIGHT;
        }

        /* Comparing the two MACs */
        /* polyspace +3 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer and length is checked" */
        for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
        {
          if (MacPtr[LulIndex] != LaaSha256Digest[LulIndex])
          {
            LddVerifyResult = CSM_E_VER_NOT_OK;
            break;
          }
        }
        if ((LddVerifyResult == CSM_E_VER_OK)
          && ((LulMacLength % CSM_EIGHT) > CSM_ZERO) )
        {
          for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength % CSM_EIGHT); LulIndex++)
          {
            /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:OBAI [Justified:Low] "The array index is checked" */
            if ((MacPtr[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
              != (LaaSha256Digest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
            {
              LddVerifyResult = CSM_E_VER_NOT_OK;
              break;
            }
          }
        }
        /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        *resultPtr = LddVerifyResult;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddEscHmacSha256VerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddEscHmacSha256VerifyTb.pMacPtr = MacPtr;
      Cry_GddEscHmacSha256VerifyTb.ulMacLength = MacLength;
      Cry_GddEscHmacSha256VerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_EscHmacSha256VerifyMainFunction                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacVerifyCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_EscHmacSha256VerifyStart() or                   **
**                        Cry_EscHmacSha256VerifyUpdate(). For                **
**                        Cry_EscHmacSha256VerifyFinish invocation of         **
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
**                        Cry_GddEscHmacSha256VerifyTb                        **
**                        Cry_GpEscHmacSha256VerifyConfigPtr                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha256_Init                                  **
**                        EscHmacSha256_Update                                **
**                        EscHmacSha256_Finish                                **
**                        Csm_MacVerifyCallbackNotification                   **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
void Cry_EscHmacSha256VerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha256Digest[EscSha256_DIGEST_LEN];
  uint32 LulIndex;
  uint32 LulMacLength;
  const uint8* LpMacPtr;
  Csm_VerifyResultType LddVerifyResult;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddEscHmacSha256VerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    LblReturnValue = EscHmacSha256_Init(&Cry_GddEscHmacSha256VerifyContext,
      (const uint8*)((const void*)(Cry_GddEscHmacSha256VerifyTb.pKeyPtr->data)),
      Cry_GddEscHmacSha256VerifyTb.pKeyPtr->length);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscHmacSha256VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscHmacSha256VerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = EscHmacSha256_Update(&Cry_GddEscHmacSha256VerifyContext,
      Cry_GddEscHmacSha256VerifyTb.pDataPtr,
      Cry_GddEscHmacSha256VerifyTb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscHmacSha256VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscHmacSha256VerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    (void)memset((void*)&LaaSha256Digest, 0x00, sizeof(LaaSha256Digest));

    LblReturnValue = EscHmacSha256_Finish(&Cry_GddEscHmacSha256VerifyContext,
      LaaSha256Digest);

    if (LblReturnValue != CSM_TRUE)
    {
      LulMacLength = Cry_GddEscHmacSha256VerifyTb.ulMacLength;
      LpMacPtr = Cry_GddEscHmacSha256VerifyTb.pMacPtr;
      LddVerifyResult = CSM_E_VER_OK;

      if (LulMacLength > EscSha256_DIGEST_LEN * CSM_EIGHT)
      {
        LulMacLength = EscSha256_DIGEST_LEN * CSM_EIGHT;
      }

      /* Comparing the two MACs */
      for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
      {
        /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        if (LpMacPtr[LulIndex] != LaaSha256Digest[LulIndex])
        {
          LddVerifyResult = CSM_E_VER_NOT_OK;
          break;
        }
      }
      if ((LddVerifyResult == CSM_E_VER_OK)
        && ((LulMacLength % CSM_EIGHT) > CSM_ZERO) )
      {
        for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength % CSM_EIGHT); LulIndex++)
        {
          /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:OBAI [Justified:Low] "The array index is checked" */
          if ((LpMacPtr[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
            != (LaaSha256Digest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
          {
            LddVerifyResult = CSM_E_VER_NOT_OK;
            break;
          }
        }
      }
      /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      *(Cry_GddEscHmacSha256VerifyTb.pResultPtr) = LddVerifyResult;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscHmacSha256VerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_MAC_ESCHMACSHA256VERIFY == STD_ON) */
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:D4.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
