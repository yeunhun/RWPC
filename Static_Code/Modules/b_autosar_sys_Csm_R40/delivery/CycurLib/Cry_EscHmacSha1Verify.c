/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscHmacSha1Verify.c                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt HMAC SHA1 Verify Interface      **
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
** 1.0.8     21-Sep-2016   Sinil        Redmine #5554, #6128                  **
** 1.0.7     09-Aug-2016   Sinil        Redmine #5693, #5026, #5747           **
** 1.0.6     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.5     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.4     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.3     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.2     02-May-2016   Sinil        Redmine #4607                         **
** 1.0.1     02-Dec-2015   Sinil        Memory section changed                **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:D4.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Escrypt HMAC SHA1 Verify */
#include "Cry_EscHmacSha1Verify.h"
/* Mac Interface */
#if (CSM_MAC_VERIFY_STATUS == STD_ON)
#if (CSM_MAC_ESCHMACSHA1VERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "hmac_sha_1.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry EscHmacSha1Verify Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* pointer to the key necessary for the Escrypt HMAC SHA1 generation */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores raw data pointer used for Escrypt HMAC SHA1 Computation */
  const uint8* pDataPtr;
  /* Data length of the data used for Escrypt HMAC SHA1 Computation */
  uint32 ulDataLength;
  /* Stores Escrypt HMAC SHA1 provided for verification */
  const uint8* pMacPtr;
  /* length of the provided Escrypt HMAC SHA1 */
  uint32 ulMacLength;
  /* Stores verification result */
  Csm_VerifyResultType* pResultPtr;
} Cry_EscHmacSha1VerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Escrypt HMAC SHA1 primitive library context */
static EscHmacSha1_ContextT Cry_GddEscHmacSha1VerifyContext;

/* Global variable for Escrypt HMAC SHA1 transfer buffer structure */
static Cry_EscHmacSha1VerifyTransferBuffer Cry_GddEscHmacSha1VerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscHmacSha1VerifyInit                             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Escrypt HMAC SHA1        **
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
** Remarks            : Global Variable(s):  Cry_GddEscHmacSha1VerifyTb       **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_EscHmacSha1VerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscHmacSha1VerifyTb.ucJobState = NO_JOB;
  Cry_GddEscHmacSha1VerifyTb.pKeyPtr = NULL_PTR;
  Cry_GddEscHmacSha1VerifyTb.pDataPtr = NULL_PTR;
  Cry_GddEscHmacSha1VerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddEscHmacSha1VerifyTb.pMacPtr = NULL_PTR;
  Cry_GddEscHmacSha1VerifyTb.ulMacLength = CSM_ZERO;
  Cry_GddEscHmacSha1VerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddEscHmacSha1VerifyContext, 0x00,
    sizeof(EscHmacSha1_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscHmacSha1VerifyStart                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt HMAC SHA1, so that if is     **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscHmacSha1VerifyMainFunction() can process     **
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
**                        Cry_GddEscHmacSha1VerifyTb                          **
**                        Cry_GpEscHmacSha1VerifyConfigPtr                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha1_Init                                    **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha1VerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddEscHmacSha1VerifyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_EscHmacSha1VerifyInit();

    Cry_GddEscHmacSha1VerifyTb.ucJobState = JOB_START;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LblReturnValue = EscHmacSha1_Init(&Cry_GddEscHmacSha1VerifyContext,
        (const uint8*)((const void*)(keyPtr->data)), keyPtr->length);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscHmacSha1VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscHmacSha1VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscHmacSha1VerifyTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_EscHmacSha1VerifyUpdate                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Escrypt  **
**                        HMAC SHA1                                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscHmacSha1VerifyMainFunction() can process     **
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
**                        Cry_GddEscHmacSha1VerifyTb                          **
**                        Cry_GpEscHmacSha1VerifyConfigPtr                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha1_Update                                  **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha1VerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddEscHmacSha1VerifyTb.ucJobState)
  {
    Cry_GddEscHmacSha1VerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      LblReturnValue = EscHmacSha1_Update(&Cry_GddEscHmacSha1VerifyContext,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscHmacSha1VerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscHmacSha1VerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscHmacSha1VerifyTb.pDataPtr = dataPtr;
      Cry_GddEscHmacSha1VerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_EscHmacSha1VerifyFinish                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Escrypt **
**                        HMAC SHA1 computation and store the result into the **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscHmacSha1VerifyMainFunction() can finish the  **
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
**                        Cry_GddEscHmacSha1VerifyTb                          **
**                        Cry_GpEscHmacSha1VerifyConfigPtr                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha1_Finish, memcmp                          **
*******************************************************************************/
Std_ReturnType Cry_EscHmacSha1VerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha1Digest[EscSha1_DIGEST_LEN];
  uint32 LulIndex;
  uint32 LulMacLength;
  Csm_VerifyResultType LddVerifyResult;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddEscHmacSha1VerifyTb.ucJobState)
  {
    Cry_GddEscHmacSha1VerifyTb.ucJobState = JOB_FINISH;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      (void)memset((void*)&LaaSha1Digest, 0x00, sizeof(LaaSha1Digest));

      LblReturnValue = EscHmacSha1_Finish(&Cry_GddEscHmacSha1VerifyContext,
        LaaSha1Digest);

      if (LblReturnValue != CSM_TRUE)
      {
        LulMacLength = MacLength;
        LddVerifyResult = CSM_E_VER_OK;
        if (LulMacLength > EscSha1_DIGEST_LEN * CSM_EIGHT)
        {
          LulMacLength = EscSha1_DIGEST_LEN * CSM_EIGHT;
        }

        /* Comparing the two MACs */
        /* polyspace +3 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer and length is checked" */
        for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
        {
          if (MacPtr[LulIndex] != LaaSha1Digest[LulIndex])
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
              != (LaaSha1Digest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
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
      Cry_GddEscHmacSha1VerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddEscHmacSha1VerifyTb.pMacPtr = MacPtr;
      Cry_GddEscHmacSha1VerifyTb.ulMacLength = MacLength;
      Cry_GddEscHmacSha1VerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_EscHmacSha1VerifyMainFunction                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacVerifyCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_EscHmacSha1VerifyStart() or                     **
**                        Cry_EscHmacSha1VerifyUpdate(). For                  **
**                        Cry_EscHmacSha1VerifyFinish invocation of           **
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
**                        Cry_GddEscHmacSha1VerifyTb                          **
**                        Cry_GpEscHmacSha1VerifyConfigPtr                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscHmacSha1_Init                                    **
**                        EscHmacSha1_Update                                  **
**                        EscHmacSha1_Finish, memcmp                          **
**                        Csm_MacVerifyCallbackNotification                   **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
void Cry_EscHmacSha1VerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaSha1Digest[EscSha1_DIGEST_LEN];
  uint32 LulIndex;
  uint32 LulMacLength;
  const uint8* LpMacPtr;
  Csm_VerifyResultType LddVerifyResult;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddEscHmacSha1VerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    LblReturnValue = EscHmacSha1_Init(&Cry_GddEscHmacSha1VerifyContext,
      (const uint8*)((const void*)(Cry_GddEscHmacSha1VerifyTb.pKeyPtr->data)),
      Cry_GddEscHmacSha1VerifyTb.pKeyPtr->length);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscHmacSha1VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscHmacSha1VerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = EscHmacSha1_Update(&Cry_GddEscHmacSha1VerifyContext,
      Cry_GddEscHmacSha1VerifyTb.pDataPtr,
      Cry_GddEscHmacSha1VerifyTb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscHmacSha1VerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscHmacSha1VerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    (void)memset((void*)&LaaSha1Digest, 0x00, sizeof(LaaSha1Digest));

    LblReturnValue = EscHmacSha1_Finish(&Cry_GddEscHmacSha1VerifyContext,
      LaaSha1Digest);

    if (LblReturnValue != CSM_TRUE)
    {
      LulMacLength = Cry_GddEscHmacSha1VerifyTb.ulMacLength;
      LpMacPtr = Cry_GddEscHmacSha1VerifyTb.pMacPtr;
      LddVerifyResult = CSM_E_VER_OK;
      if (LulMacLength > EscSha1_DIGEST_LEN * CSM_EIGHT)
      {
        LulMacLength = EscSha1_DIGEST_LEN * CSM_EIGHT;
      }

      /* Comparing the two MACs */
      for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
      {
        /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        if (LpMacPtr[LulIndex] != LaaSha1Digest[LulIndex])
        {
          LddVerifyResult = CSM_E_VER_NOT_OK;
          break;
        }
      }
      if ((LddVerifyResult == CSM_E_VER_OK)
        && ((LulMacLength % CSM_EIGHT) > CSM_ZERO))
      {
        for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength % CSM_EIGHT); LulIndex++)
        {
          /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:OBAI [Justified:Low] "The array index is checked" */
          if ((LpMacPtr[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
            != (LaaSha1Digest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
          {
            LddVerifyResult = CSM_E_VER_NOT_OK;
            break;
          }
        }
      }
      /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      *(Cry_GddEscHmacSha1VerifyTb.pResultPtr) = LddVerifyResult;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscHmacSha1VerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_MAC_ESCHMACSHA1VERIFY == STD_ON) */
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:D4.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
