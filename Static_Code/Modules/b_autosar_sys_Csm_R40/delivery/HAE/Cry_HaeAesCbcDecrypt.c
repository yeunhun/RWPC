/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeAesCbcDecrypt.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever AES - CBC Decrypt Interface    **
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
** 1.0.0     12-Feb-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Autoever AES CBC */
#include "Cry_HaeAesCbcDecrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_DECRYPT_STATUS == STD_ON)
#if (CSM_SYM_HAEAESCBCDECRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_Aes.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeAesCbcDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const Csm_SymKeyType* pKeyPtr;
  const uint8* pCipherTextPtr;
  uint32 ulCipherTextLength;
  const uint8* pInitVectorPtr;
  uint32 ulInitVectorLength;
  uint8* pPlainTextPtr;
  uint32* pPlainTextLengthPtr;
} Cry_HaeAesCbcDecryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaeAesCbcDecryptIV[HMG_AES_N_BLOCK];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* AES primitive library context */
static HmgAeskeyCtx Cry_GddHaeAesCbcDecryptContext;

/* Global structure variable for Autoever AES CBC transfer buffer */
static Cry_HaeAesCbcDecryptTransferBuffer Cry_GddHaeAesCbcDecryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeAesCbcDecryptInit                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the AES module.              **
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
** Remarks            : Global Variable(s):  Cry_GddHaeAesCbcDecryptTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeAesCbcDecryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeAesCbcDecryptTb.ucJobState = NO_JOB;
  Cry_GddHaeAesCbcDecryptTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeAesCbcDecryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddHaeAesCbcDecryptTb.ulCipherTextLength = CSM_ZERO;
  Cry_GddHaeAesCbcDecryptTb.pInitVectorPtr = NULL_PTR;
  Cry_GddHaeAesCbcDecryptTb.ulInitVectorLength = CSM_ZERO;
  Cry_GddHaeAesCbcDecryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddHaeAesCbcDecryptTb.pPlainTextLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeAesCbcDecryptContext, 0x00, sizeof(HmgAeskeyCtx));
  (void)memset((void*)&Cry_GaaHaeAesCbcDecryptIV, 0x00, sizeof(Cry_GaaHaeAesCbcDecryptIV));
}

/*******************************************************************************
** Function Name        : Cry_HaeAesCbcDecryptStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever AES CBC, so that AES is able **
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeAesCbcDecryptMainFunction() can process      **
**                        initialisation                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgPtr, keyPtr, InitVectorPtr, InitVectorLength     **
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
**                        Cry_GddHaeAesCbcDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeAesCbcDecryptInit, Hmg_AesSetKey             **
*******************************************************************************/
Std_ReturnType Cry_HaeAesCbcDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddHaeAesCbcDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeAesCbcDecryptInit();

    Cry_GddHaeAesCbcDecryptTb.ucJobState = JOB_START;

    if (Csm_SymDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((keyPtr->length != HMG_AES_N_BLOCK)
        || (InitVectorLength != HMG_AES_N_BLOCK))
      {
        /* The length of key and init vector should be 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblReturnValue = Hmg_AesSetKey(&Cry_GddHaeAesCbcDecryptContext,
          (const uint8*)((const void*)(keyPtr->data)), HMG_AES_N_BLOCK);

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
        else
        {
          /* polyspace +1 MISRA-C3:D4.11 RTE:STD_LIB [Justified:Low] "The input is checked" */
          (void)memcpy((void*)Cry_GaaHaeAesCbcDecryptIV, (const void*)InitVectorPtr, \
            InitVectorLength);
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeAesCbcDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeAesCbcDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeAesCbcDecryptTb.pKeyPtr = keyPtr;
      Cry_GddHaeAesCbcDecryptTb.pInitVectorPtr = InitVectorPtr;
      Cry_GddHaeAesCbcDecryptTb.ulInitVectorLength = InitVectorLength;
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
** Function Name        : Cry_HaeAesCbcDecryptUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeAesCbcDecryptMainFunction() can process the  **
**                        input                                               **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, cipherTextPtr, cipherTextLength              **
**                                                                            **
** InOut parameter      : plainTextLengthPtr                                  **
**                                                                            **
** Output Parameters    : plainTextPtr                                        **
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
**                        Cry_GddHaeAesCbcDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesCbcDec                                       **
*******************************************************************************/
Std_ReturnType Cry_HaeAesCbcDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeAesCbcDecryptTb.ucJobState)
  {
    Cry_GddHaeAesCbcDecryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*plainTextLengthPtr < cipherTextLength)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((cipherTextLength < HMG_AES_N_BLOCK)
        || ((cipherTextLength % HMG_AES_N_BLOCK) != CSM_ZERO))
      {
        /* cipherTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        *plainTextLengthPtr = CSM_ZERO;

        LblReturnValue = Hmg_AesCbcDec(&Cry_GddHaeAesCbcDecryptContext,
          Cry_GaaHaeAesCbcDecryptIV, plainTextPtr, cipherTextPtr, cipherTextLength);

        if (LblReturnValue != CSM_TRUE)
        {
          *plainTextLengthPtr = cipherTextLength;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeAesCbcDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeAesCbcDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeAesCbcDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddHaeAesCbcDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddHaeAesCbcDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddHaeAesCbcDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
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
** Function Name        : Cry_HaeAesCbcDecryptFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeAesCbcDecryptMainFunction() can finish the   **
**                        computation and store the result in the memory      **
**                        location given                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
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
**                        Cry_GddHaeAesCbcDecryptTb                           **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_HaeAesCbcDecryptFinish(Csm_ConfigIdType cfgId,
  uint8* plainTextPtr, uint32* plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(plainTextPtr);
  CSM_PARAM_UNUSED_PTR(plainTextLengthPtr);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeAesCbcDecryptTb.ucJobState)
  {
    Cry_GddHaeAesCbcDecryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymDecryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeAesCbcDecryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeAesCbcDecryptMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymDecryptCallbackNotification() with the       **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_HaeAesCbcDecryptStart()   **
**                        or Cry_HaeAesCbcDecryptUpdate(). For                **
**                        Cry_HaeAesCbcDecryptFinish invocation of            **
**                        Csm_SymDecryptCallbackNotification()                **
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
**                        Cry_GddHaeAesCbcDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesSetKey,                                      **
**                        Hmg_AesCbcDec,                                      **
**                        Csm_SymDecryptCallbackNotification,                 **
**                        Csm_SymDecryptServiceFinishNotification             **
*******************************************************************************/
void Cry_HaeAesCbcDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeAesCbcDecryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((Cry_GddHaeAesCbcDecryptTb.pKeyPtr->length != HMG_AES_N_BLOCK)
      || (Cry_GddHaeAesCbcDecryptTb.ulInitVectorLength != HMG_AES_N_BLOCK))
    {
      /* The length of key and init vector should be 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblReturnValue = Hmg_AesSetKey(
        &Cry_GddHaeAesCbcDecryptContext,
        (const uint8*)((const void*)(Cry_GddHaeAesCbcDecryptTb.pKeyPtr->data)),
        HMG_AES_N_BLOCK);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* polyspace +3 MISRA-C3:D4.11 [Justified:Low] "No Impact of this rule violation" */
	      /* polyspace +3 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	      /* polyspace +2 RTE:STD_LIB [Justified:Low] "No Impact of this rule violation" */
        (void)memcpy((void*)Cry_GaaHaeAesCbcDecryptIV,
          (const void*)(Cry_GddHaeAesCbcDecryptTb.pInitVectorPtr),
          Cry_GddHaeAesCbcDecryptTb.ulInitVectorLength);
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeAesCbcDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeAesCbcDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaeAesCbcDecryptTb.pPlainTextLengthPtr)
      < Cry_GddHaeAesCbcDecryptTb.ulCipherTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddHaeAesCbcDecryptTb.ulCipherTextLength < HMG_AES_N_BLOCK)
      || ((Cry_GddHaeAesCbcDecryptTb.ulCipherTextLength % HMG_AES_N_BLOCK) != CSM_ZERO))
    {
      /* cipherTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddHaeAesCbcDecryptTb.pPlainTextLengthPtr) = CSM_ZERO;

      LblReturnValue = Hmg_AesCbcDec(&Cry_GddHaeAesCbcDecryptContext,
        Cry_GaaHaeAesCbcDecryptIV,
        Cry_GddHaeAesCbcDecryptTb.pPlainTextPtr,
        Cry_GddHaeAesCbcDecryptTb.pCipherTextPtr,
        Cry_GddHaeAesCbcDecryptTb.ulCipherTextLength);

      if (LblReturnValue != CSM_TRUE)
      {
        *(Cry_GddHaeAesCbcDecryptTb.pPlainTextLengthPtr)
          = Cry_GddHaeAesCbcDecryptTb.ulCipherTextLength;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeAesCbcDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeAesCbcDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeAesCbcDecryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_SymDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_SymDecryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYM_HAEAESCBCDECRYPT == STD_ON) */
#endif /* (CSM_SYM_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
