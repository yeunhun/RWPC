/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeAesCtrEncrypt.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever AES - CTR Encrypt Interface    **
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
/* Header File for Autoever AES CTR */
#include "Cry_HaeAesCtrEncrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYM_HAEAESCTRENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_Aes.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeAesCtrEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores encryption key pointer in Autoever AES CTR */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores plain data pointer used for encryption in Autoever AES CTR */
  const uint8* pPlainTextPtr;
  /* Data length of the plain data used for encryption */
  uint32 ulPlainTextLength;
  const uint8* pInitVectorPtr;
  uint32 ulInitVectorLength;
  /* Stores ciphered data pointer used for encryption in Autoever AES CTR */
  uint8* pCipherTextPtr;
  /* Pointer of ciphered data length */
  uint32* pCipherTextLengthPtr;
} Cry_HaeAesCtrEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaeAesCtrEncryptCounter[HMG_AES_N_BLOCK];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* AES primitive library context */
static HmgAeskeyCtx Cry_GddHaeAesCtrEncryptContext;

/* Global structure variable for Autoever AES CTR transfer buffer */
static Cry_HaeAesCtrEncryptTransferBuffer Cry_GddHaeAesCtrEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeAesCtrEncryptInit                              **
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
** Remarks            : Global Variable(s):  Cry_GddHaeAesCtrEncryptTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeAesCtrEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeAesCtrEncryptTb.ucJobState = NO_JOB;
  Cry_GddHaeAesCtrEncryptTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeAesCtrEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddHaeAesCtrEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddHaeAesCtrEncryptTb.pInitVectorPtr = NULL_PTR;
  Cry_GddHaeAesCtrEncryptTb.ulInitVectorLength = CSM_ZERO;
  Cry_GddHaeAesCtrEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddHaeAesCtrEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeAesCtrEncryptContext, 0x00, sizeof(HmgAeskeyCtx));
  (void)memset((void*)&Cry_GaaHaeAesCtrEncryptCounter, 0x00, sizeof(Cry_GaaHaeAesCtrEncryptCounter));
}

/*******************************************************************************
** Function Name        : Cry_HaeAesCtrEncryptStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever AES CTR, so that AES is able**
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeAesCtrEncryptMainFunction() can process      **
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
**                        Cry_GddHaeAesCtrEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeAesCtrEncryptInit, Hmg_AesSetKey             **
*******************************************************************************/
Std_ReturnType Cry_HaeAesCtrEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddHaeAesCtrEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeAesCtrEncryptInit();

    Cry_GddHaeAesCtrEncryptTb.ucJobState = JOB_START;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if ((keyPtr->length != HMG_AES_N_BLOCK)
        || (InitVectorLength != HMG_AES_N_BLOCK))
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblReturnValue = Hmg_AesSetKey(&Cry_GddHaeAesCtrEncryptContext,
          (const uint8*)((const void*)(keyPtr->data)), HMG_AES_N_BLOCK);

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
        else
        {
          /* polyspace +1 MISRA-C3:D4.11 RTE:STD_LIB [Justified:Low] "The input is checked" */
          (void)memcpy((void*)Cry_GaaHaeAesCtrEncryptCounter, (const void*)InitVectorPtr,\
           InitVectorLength);
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeAesCtrEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeAesCtrEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeAesCtrEncryptTb.pKeyPtr = keyPtr;
      Cry_GddHaeAesCtrEncryptTb.pInitVectorPtr = InitVectorPtr;
      Cry_GddHaeAesCtrEncryptTb.ulInitVectorLength = InitVectorLength;
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
** Function Name        : Cry_HaeAesCtrEncryptUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeAesCtrEncryptMainFunction() can process the  **
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
**                        Cry_GddHaeAesCtrEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesCtr                                          **
*******************************************************************************/
Std_ReturnType Cry_HaeAesCtrEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeAesCtrEncryptTb.ucJobState)
  {
    Cry_GddHaeAesCtrEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*cipherTextLengthPtr < plainTextLength)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        *cipherTextLengthPtr = CSM_ZERO;

        LblReturnValue = Hmg_AesCtr(&Cry_GddHaeAesCtrEncryptContext,
          Cry_GaaHaeAesCtrEncryptCounter, cipherTextPtr, plainTextPtr, plainTextLength);

        if (LblReturnValue != CSM_TRUE)
        {
          *cipherTextLengthPtr = plainTextLength;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeAesCtrEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeAesCtrEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeAesCtrEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddHaeAesCtrEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddHaeAesCtrEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddHaeAesCtrEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_HaeAesCtrEncryptFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeAesCtrEncryptMainFunction() can finish the   **
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
**                        Cry_GddHaeAesCtrEncryptTb                           **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_HaeAesCtrEncryptFinish(Csm_ConfigIdType cfgId,
  uint8* cipherTextPtr, uint32* cipherTextLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED_PTR(cipherTextPtr);
  CSM_PARAM_UNUSED_PTR(cipherTextLengthPtr);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeAesCtrEncryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddHaeAesCtrEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeAesCtrEncryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeAesCtrEncryptMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockEncryptCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_HaeAesCtrEncryptStart()   **
**                        or Cry_HaeAesCtrEncryptUpdate(). For                **
**                        Cry_HaeAesCtrEncryptFinish invocation of            **
**                        Csm_SymBlockEncryptCallbackNotification()           **
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
**                        Cry_GddHaeAesCtrEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesSetKey,                                      **
**                        Hmg_AesCtr,                                         **
**                        Csm_SymBlockEncryptCallbackNotification,            **
**                        Csm_SymBlockEncryptServiceFinishNotification        **
*******************************************************************************/
void Cry_HaeAesCtrEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeAesCtrEncryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((Cry_GddHaeAesCtrEncryptTb.pKeyPtr->length != HMG_AES_N_BLOCK)
      || (Cry_GddHaeAesCtrEncryptTb.ulInitVectorLength != HMG_AES_N_BLOCK))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblReturnValue = Hmg_AesSetKey(&Cry_GddHaeAesCtrEncryptContext,
          (const uint8*)((const void*)(Cry_GddHaeAesCtrEncryptTb.pKeyPtr->data)),
          HMG_AES_N_BLOCK);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* polyspace +3 MISRA-C3:D4.11 [Justified:Low] "No Impact of this rule violation" */
	      /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	      /* polyspace +2 RTE:STD_LIB [Justified:Low] "No Impact of this rule violation" */
        (void)memcpy((void*)Cry_GaaHaeAesCtrEncryptCounter,
          (const void*)(Cry_GddHaeAesCtrEncryptTb.pInitVectorPtr),
          Cry_GddHaeAesCtrEncryptTb.ulInitVectorLength);
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeAesCtrEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeAesCtrEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaeAesCtrEncryptTb.pCipherTextLengthPtr)
      < Cry_GddHaeAesCtrEncryptTb.ulPlainTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddHaeAesCtrEncryptTb.pCipherTextLengthPtr) = CSM_ZERO;

      LblReturnValue = Hmg_AesCtr(&Cry_GddHaeAesCtrEncryptContext,
          Cry_GaaHaeAesCtrEncryptCounter,
          Cry_GddHaeAesCtrEncryptTb.pCipherTextPtr,
          Cry_GddHaeAesCtrEncryptTb.pPlainTextPtr,
          Cry_GddHaeAesCtrEncryptTb.ulPlainTextLength);

      if (LblReturnValue != CSM_TRUE)
      {
        *(Cry_GddHaeAesCtrEncryptTb.pCipherTextLengthPtr)
          = Cry_GddHaeAesCtrEncryptTb.ulPlainTextLength;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeAesCtrEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeAesCtrEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeAesCtrEncryptTb.ucJobState = NO_JOB;

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_SymEncryptServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYM_HAEAESCTRENCRYPT == STD_ON) */
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
