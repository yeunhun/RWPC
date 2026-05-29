/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeAesEcbDecrypt.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever AES - ECB Decrypt Interface    **
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
** 1.0.0     12-Fen-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Autoever AES ECB */
#include "Cry_HaeAesEcbDecrypt.h"
/* Symmetric Block Interface */
#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
#if (CSM_SYMBLOCK_HAEAESECBDECRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_Aes.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeAesEcbDecrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores encryption key pointer in Autoever AES ECB */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores plain data pointer used for encryption in Autoever AES ECB */
  const uint8* pCipherTextPtr;
  /* Data length of the plain data used for encryption */
  uint32 ulCipherTextLength;
  /* Stores ciphered data pointer used for encryption in Autoever AES ECB */
  uint8* pPlainTextPtr;
  /* Pointer of ciphered data length */
  uint32* pPlainTextLengthPtr;
} Cry_HaeAesEcbDecryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* AES primitive library context */
static HmgAeskeyCtx Cry_GddHaeAesEcbDecryptContext;

/* Global structure variable for Autoever AES ECB transfer buffer */
static Cry_HaeAesEcbDecryptTransferBuffer Cry_GddHaeAesEcbDecryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeAesEcbDecryptInit                              **
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
** Remarks            : Global Variable(s):  Cry_GddHaeAesEcbDecryptTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
static void Cry_HaeAesEcbDecryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeAesEcbDecryptTb.ucJobState = NO_JOB;
  Cry_GddHaeAesEcbDecryptTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeAesEcbDecryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddHaeAesEcbDecryptTb.ulCipherTextLength = CSM_ZERO;
  Cry_GddHaeAesEcbDecryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddHaeAesEcbDecryptTb.pPlainTextLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeAesEcbDecryptContext, 0x00, sizeof(HmgAeskeyCtx));
}

/*******************************************************************************
** Function Name        : Cry_HaeAesEcbDecryptStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever AES ECB, so that AES is able**
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeAesEcbDecryptMainFunction() can process      **
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
**                        Cry_GddHaeAesEcbDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeAesEcbDecryptInit, Hmg_AesSetKey             **
*******************************************************************************/
Std_ReturnType Cry_HaeAesEcbDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddHaeAesEcbDecryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeAesEcbDecryptInit();

    Cry_GddHaeAesEcbDecryptTb.ucJobState = JOB_START;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != HMG_AES_N_BLOCK)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblReturnValue = Hmg_AesSetKey(&Cry_GddHaeAesEcbDecryptContext,
          (const uint8*)((const void*)(keyPtr->data)), HMG_AES_N_BLOCK);

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeAesEcbDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeAesEcbDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeAesEcbDecryptTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeAesEcbDecryptUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeAesEcbDecryptMainFunction() can process the  **
**                        input                                               **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, plainTextPtr, plainTextLength                **
**                                                                            **
** InOut parameter      : cipherTextLengthPtr                                 **
**                                                                            **
** Output Parameters    : cipherTextPtr                                       **
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
**                        Cry_GddHaeAesEcbDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesEcbDec                                       **
*******************************************************************************/
Std_ReturnType Cry_HaeAesEcbDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32 *plainTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeAesEcbDecryptTb.ucJobState)
  {
    Cry_GddHaeAesEcbDecryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
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
        /* plainTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        *plainTextLengthPtr = CSM_ZERO;

        LblReturnValue = Hmg_AesEcbDec(&Cry_GddHaeAesEcbDecryptContext,
          plainTextPtr, cipherTextPtr, cipherTextLength);

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
        Cry_GddHaeAesEcbDecryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeAesEcbDecryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeAesEcbDecryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddHaeAesEcbDecryptTb.ulCipherTextLength = cipherTextLength;
      Cry_GddHaeAesEcbDecryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddHaeAesEcbDecryptTb.pPlainTextLengthPtr = plainTextLengthPtr;
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
** Function Name        : Cry_HaeAesEcbDecryptFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeAesEcbDecryptMainFunction() can finish the   **
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
**                        Cry_GddHaeAesEcbDecryptTb                           **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_HaeAesEcbDecryptFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeAesEcbDecryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddHaeAesEcbDecryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymBlockDecryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeAesEcbDecryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeAesEcbDecryptMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockDecryptCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_HaeAesEcbDecryptStart()   **
**                        or Cry_HaeAesEcbDecryptUpdate(). For                **
**                        Cry_HaeAesEcbDecryptFinish invocation of            **
**                        Csm_SymBlockDecryptCallbackNotification()           **
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
**                        Cry_GddHaeAesEcbDecryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesSetKey,                                      **
**                        Hmg_AesEcbDec,                                      **
**                        Csm_SymBlockDecryptCallbackNotification,            **
**                        Csm_SymBlockDecryptServiceFinishNotification        **
*******************************************************************************/
void Cry_HaeAesEcbDecryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeAesEcbDecryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +2 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +1 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeAesEcbDecryptTb.pKeyPtr->length != HMG_AES_N_BLOCK)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblReturnValue = Hmg_AesSetKey(&Cry_GddHaeAesEcbDecryptContext,
          (const uint8*)((const void*)(Cry_GddHaeAesEcbDecryptTb.pKeyPtr->data)),
          HMG_AES_N_BLOCK);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeAesEcbDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeAesEcbDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaeAesEcbDecryptTb.pPlainTextLengthPtr)
      < Cry_GddHaeAesEcbDecryptTb.ulCipherTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddHaeAesEcbDecryptTb.ulCipherTextLength < HMG_AES_N_BLOCK)
      || ((Cry_GddHaeAesEcbDecryptTb.ulCipherTextLength % HMG_AES_N_BLOCK) != CSM_ZERO))
    {
      /* plainTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddHaeAesEcbDecryptTb.pPlainTextLengthPtr) = CSM_ZERO;

      LblReturnValue = Hmg_AesEcbDec(&Cry_GddHaeAesEcbDecryptContext,
          Cry_GddHaeAesEcbDecryptTb.pPlainTextPtr,
          Cry_GddHaeAesEcbDecryptTb.pCipherTextPtr,
          Cry_GddHaeAesEcbDecryptTb.ulCipherTextLength);

      if (LblReturnValue != CSM_TRUE)
      {
        *(Cry_GddHaeAesEcbDecryptTb.pPlainTextLengthPtr)
          = Cry_GddHaeAesEcbDecryptTb.ulCipherTextLength;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeAesEcbDecryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeAesEcbDecryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeAesEcbDecryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_SymBlockDecryptCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_SymBlockDecryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYMBLOCK_HAEAESECBDECRYPT == STD_ON) */
#endif /* (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
