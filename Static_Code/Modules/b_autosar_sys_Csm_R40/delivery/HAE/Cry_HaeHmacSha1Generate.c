/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHmacSha1Generate.c                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever HMAC Sha160 Generate Interface **
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
/* Header File for Autoever HMAC Sha160 Generate */
#include "Cry_HaeHmacSha1Generate.h"
/* Mac Interface */
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
#if (CSM_MAC_HAEHMACSHA1GENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_HmacSha160.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeHmacSha160Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  uint8* pResultPtr;
  uint32* pResultLengthPtr;
  boolean blTruncationIsAllowed;
} Cry_HaeHmacSha160GenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Autoever HMAC Sha160 primitive library context */
static HmgHmacSha160Ctx Cry_GddHaeHmacSha160GenerateContext;

/* Global variable for Autoever HMAC Sha160 transfer buffer structure */
static Cry_HaeHmacSha160GenerateTransferBuffer Cry_GddHaeHmacSha160GenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeHmacSha1GenerateInit                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Autoever HMAC Sha160     **
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
** Remarks            : Global Variable(s):  Cry_GddHaeHmacSha160GenerateTb   **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHmacSha1GenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHmacSha160GenerateTb.ucJobState = NO_JOB;
  Cry_GddHaeHmacSha160GenerateTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeHmacSha160GenerateTb.pDataPtr = NULL_PTR;
  Cry_GddHaeHmacSha160GenerateTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeHmacSha160GenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaeHmacSha160GenerateTb.pResultLengthPtr = NULL_PTR;
  Cry_GddHaeHmacSha160GenerateTb.blTruncationIsAllowed = CSM_FALSE;

  (void)memset((void*)&Cry_GddHaeHmacSha160GenerateContext, 0x00,
    sizeof(HmgHmacSha160Ctx));
}

/*******************************************************************************
** Function Name        : Cry_HaeHmacSha1GenerateStart                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever HMAC Sha160, so that it is  **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeHmacSha1GenerateMainFunction() can           **
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
**                        Cry_GddHaeHmacSha160GenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_HmacSha160Start, Cry_HaeHmacSha1GenerateInit    **
*******************************************************************************/
Std_ReturnType Cry_HaeHmacSha1GenerateStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHmacSha160GenerateTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeHmacSha1GenerateInit();

    Cry_GddHaeHmacSha160GenerateTb.ucJobState = JOB_START;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LblReturnValue = Hmg_HmacSha160Start(&Cry_GddHaeHmacSha160GenerateContext,
        (const uint8*)((const void*)(keyPtr->data)), keyPtr->length);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHmacSha160GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHmacSha160GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHmacSha160GenerateTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeHmacSha1GenerateUpdate                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Autoever **
**                        HMAC Sha160                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHmacSha1GenerateMainFunction() can process   **
**                        the input data                                      **
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
**                        Cry_GddHaeHmacSha160GenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_HmacSha160Update                                **
*******************************************************************************/
Std_ReturnType Cry_HaeHmacSha1GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeHmacSha160GenerateTb.ucJobState)
  {
    Cry_GddHaeHmacSha160GenerateTb.ucJobState = JOB_UPDATE;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      LblReturnValue = Hmg_HmacSha160Update(&Cry_GddHaeHmacSha160GenerateContext,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeHmacSha160GenerateTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHmacSha160GenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHmacSha160GenerateTb.pDataPtr = dataPtr;
      Cry_GddHaeHmacSha160GenerateTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeHmacSha1GenerateFinish                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Autoever**
**                        HMAC Sha160 computation and store the result into   **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHmacSha1GenerateMainFunction() can finish the**
**                        computation and store the result in the memory      **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, TruncationIsAllowed                          **
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
**                        Cry_GddHaeHmacSha160GenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_HmacSha160Finish                                **
*******************************************************************************/
Std_ReturnType Cry_HaeHmacSha1GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha160Digest[HMG_SHA160_DIGEST_SIZE];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeHmacSha160GenerateTb.ucJobState)
  {
    Cry_GddHaeHmacSha160GenerateTb.ucJobState = JOB_FINISH;

    if (Csm_MacGenerateServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((*resultLengthPtr < HMG_SHA160_DIGEST_SIZE)
        && (TruncationIsAllowed != CSM_TRUE))
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        (void)memset((void*)&LaaSha160Digest, 0x00, sizeof(LaaSha160Digest));

        LblReturnValue = Hmg_HmacSha160Finish(&Cry_GddHaeHmacSha160GenerateContext,
          LaaSha160Digest);

        if (LblReturnValue != CSM_TRUE)
        {
          *resultLengthPtr = (*resultLengthPtr < HMG_SHA160_DIGEST_SIZE)
            ? (*resultLengthPtr) : HMG_SHA160_DIGEST_SIZE;

          for (LulIndex = CSM_ZERO; LulIndex < *resultLengthPtr; LulIndex++)
          {
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            resultPtr[LulIndex] = LaaSha160Digest[LulIndex];
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHmacSha160GenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHmacSha160GenerateTb.pResultPtr = resultPtr;
      Cry_GddHaeHmacSha160GenerateTb.pResultLengthPtr = resultLengthPtr;
      Cry_GddHaeHmacSha160GenerateTb.blTruncationIsAllowed = TruncationIsAllowed;
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
** Function Name        : Cry_HaeHmacSha1GenerateMainFunction                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacGenerateCallbackNotification() with the      **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeHmacSha1GenerateStart() or                   **
**                        Cry_HaeHmacSha1GenerateUpdate(). For                **
**                        Cry_HaeHmacSha1GenerateFinish invocation of         **
**                        Csm_MacGenerateCallbackNotification()               **
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
**                        Cry_GddHaeHmacSha160GenerateTb                      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_HmacSha160Start                                 **
**                        Hmg_HmacSha160Update                                **
**                        Hmg_HmacSha160Finish                                **
**                        Csm_MacGenerateCallbackNotification                 **
**                        Csm_MacGenerateServiceFinishNotification            **
*******************************************************************************/
void Cry_HaeHmacSha1GenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha160Digest[HMG_SHA160_DIGEST_SIZE];
  uint32 LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeHmacSha160GenerateTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +4 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +3 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    LblReturnValue = Hmg_HmacSha160Start(&Cry_GddHaeHmacSha160GenerateContext,
      (const uint8*)((const void*)(Cry_GddHaeHmacSha160GenerateTb.pKeyPtr->data)),
      Cry_GddHaeHmacSha160GenerateTb.pKeyPtr->length);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHmacSha160GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHmacSha160GenerateTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = Hmg_HmacSha160Update(&Cry_GddHaeHmacSha160GenerateContext,
      Cry_GddHaeHmacSha160GenerateTb.pDataPtr,
      Cry_GddHaeHmacSha160GenerateTb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeHmacSha160GenerateTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeHmacSha160GenerateTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((*(Cry_GddHaeHmacSha160GenerateTb.pResultLengthPtr) < HMG_SHA160_DIGEST_SIZE)
      && (Cry_GddHaeHmacSha160GenerateTb.blTruncationIsAllowed != CSM_TRUE))
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      (void)memset((void*)&LaaSha160Digest, 0x00, sizeof(LaaSha160Digest));

      LblReturnValue = Hmg_HmacSha160Finish(&Cry_GddHaeHmacSha160GenerateContext,
        LaaSha160Digest);

      if (LblReturnValue != CSM_TRUE)
      {
        *(Cry_GddHaeHmacSha160GenerateTb.pResultLengthPtr) =
          (*(Cry_GddHaeHmacSha160GenerateTb.pResultLengthPtr) < HMG_SHA160_DIGEST_SIZE)
          ? (*(Cry_GddHaeHmacSha160GenerateTb.pResultLengthPtr))
          : HMG_SHA160_DIGEST_SIZE;

        for (LulIndex = CSM_ZERO; LulIndex
          < *(Cry_GddHaeHmacSha160GenerateTb.pResultLengthPtr); LulIndex++)
        {
	  /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          Cry_GddHaeHmacSha160GenerateTb.pResultPtr[LulIndex]
            = LaaSha160Digest[LulIndex];
        }
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeHmacSha160GenerateTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_MacGenerateCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_MacGenerateServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_MAC_HAEHMACSHA1GENERATE == STD_ON) */
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
