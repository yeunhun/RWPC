/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeAesCbcEncrypt.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever AES - CBC Encrypt Interface    **
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
/* Header File for Autoever AES CBC */
#include "Cry_HaeAesCbcEncrypt.h"
/* Symmetric Interface */
#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYM_HAEAESCBCENCRYPT == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_Aes.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeAesCbcEncrypt Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores encryption key pointer in Autoever AES CBC */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores plain data pointer used for encryption in Autoever AES CBC */
  const uint8* pPlainTextPtr;
  /* Data length of the plain data used for encryption */
  uint32 ulPlainTextLength;
  const uint8* pInitVectorPtr;
  uint32 ulInitVectorLength;
  /* Stores ciphered data pointer used for encryption in Autoever AES CBC */
  uint8* pCipherTextPtr;
  /* Pointer of ciphered data length */
  uint32* pCipherTextLengthPtr;
} Cry_HaeAesCbcEncryptTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

static uint8 Cry_GaaHaeAesCbcEncryptIV[HMG_AES_N_BLOCK];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* AES primitive library context */
static HmgAeskeyCtx Cry_GddHaeAesCbcEncryptContext;

/* Global structure variable for Autoever AES CBC transfer buffer */
static Cry_HaeAesCbcEncryptTransferBuffer Cry_GddHaeAesCbcEncryptTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeAesCbcEncryptInit                              **
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
** Remarks            : Global Variable(s):  Cry_GddHaeAesCbcEncryptTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeAesCbcEncryptInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeAesCbcEncryptTb.ucJobState = NO_JOB;
  Cry_GddHaeAesCbcEncryptTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeAesCbcEncryptTb.pPlainTextPtr = NULL_PTR;
  Cry_GddHaeAesCbcEncryptTb.ulPlainTextLength = CSM_ZERO;
  Cry_GddHaeAesCbcEncryptTb.pInitVectorPtr = NULL_PTR;
  Cry_GddHaeAesCbcEncryptTb.ulInitVectorLength = CSM_ZERO;
  Cry_GddHaeAesCbcEncryptTb.pCipherTextPtr = NULL_PTR;
  Cry_GddHaeAesCbcEncryptTb.pCipherTextLengthPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeAesCbcEncryptContext, 0x00, sizeof(HmgAeskeyCtx));
  (void)memset((void*)&Cry_GaaHaeAesCbcEncryptIV, 0x00, sizeof(Cry_GaaHaeAesCbcEncryptIV));
}

/*******************************************************************************
** Function Name        : Cry_HaeAesCbcEncryptStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever AES CBC, so that AES is able**
**                        to process the input data                           **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeAesCbcEncryptMainFunction() can process      **
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
**                        Cry_GddHaeAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeAesCbcEncryptInit, Hmg_AesSetKey             **
*******************************************************************************/
Std_ReturnType Cry_HaeAesCbcEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  /* Check the job processing state of the session */
  if (NO_JOB == Cry_GddHaeAesCbcEncryptTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeAesCbcEncryptInit();

    Cry_GddHaeAesCbcEncryptTb.ucJobState = JOB_START;

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
        LblReturnValue = Hmg_AesSetKey(&Cry_GddHaeAesCbcEncryptContext,
          (const uint8*)((const void*)(keyPtr->data)), HMG_AES_N_BLOCK);

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
        else
        {
          /* polyspace +1 MISRA-C3:D4.11 RTE:STD_LIB [Justified:Low] "The input is checked" */
          (void)memcpy((void*)Cry_GaaHaeAesCbcEncryptIV, (const void*)InitVectorPtr, \
            InitVectorLength);
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeAesCbcEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeAesCbcEncryptTb.pKeyPtr = keyPtr;
      Cry_GddHaeAesCbcEncryptTb.pInitVectorPtr = InitVectorPtr;
      Cry_GddHaeAesCbcEncryptTb.ulInitVectorLength = InitVectorLength;
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
** Function Name        : Cry_HaeAesCbcEncryptUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the AES      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeAesCbcEncryptMainFunction() can process the  **
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
**                        Cry_GddHaeAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesCbcEnc                                       **
*******************************************************************************/
Std_ReturnType Cry_HaeAesCbcEncryptUpdate(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddHaeAesCbcEncryptTb.ucJobState)
  {
    Cry_GddHaeAesCbcEncryptTb.ucJobState = JOB_UPDATE;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*cipherTextLengthPtr < plainTextLength)
      {
        /* Buffer size is invalid */
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if ((plainTextLength < HMG_AES_N_BLOCK)
        || ((plainTextLength % HMG_AES_N_BLOCK) != CSM_ZERO))
      {
        /* plainTextLength should be multiples of 16 */
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        *cipherTextLengthPtr = CSM_ZERO;

        LblReturnValue = Hmg_AesCbcEnc(&Cry_GddHaeAesCbcEncryptContext,
          Cry_GaaHaeAesCbcEncryptIV, cipherTextPtr, plainTextPtr, plainTextLength);

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
        Cry_GddHaeAesCbcEncryptTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeAesCbcEncryptTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeAesCbcEncryptTb.pPlainTextPtr = plainTextPtr;
      Cry_GddHaeAesCbcEncryptTb.ulPlainTextLength = plainTextLength;
      Cry_GddHaeAesCbcEncryptTb.pCipherTextPtr = cipherTextPtr;
      Cry_GddHaeAesCbcEncryptTb.pCipherTextLengthPtr = cipherTextLengthPtr;
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
** Function Name        : Cry_HaeAesCbcEncryptFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the AES     **
**                        computation and store the result into the memory    **
**                        location given                                      **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeAesCbcEncryptMainFunction() can finish the   **
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
**                        Cry_GddHaeAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_HaeAesCbcEncryptFinish(Csm_ConfigIdType cfgId,
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
  if (JOB_DONE == Cry_GddHaeAesCbcEncryptTb.ucJobState)
  {
    /* Set the job state to JOB_FINISH */
    Cry_GddHaeAesCbcEncryptTb.ucJobState = JOB_FINISH;

    if (Csm_SymEncryptServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeAesCbcEncryptTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeAesCbcEncryptMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_SymBlockEncryptCallbackNotification() with the  **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by Cry_HaeAesCbcEncryptStart()   **
**                        or Cry_HaeAesCbcEncryptUpdate(). For                **
**                        Cry_HaeAesCbcEncryptFinish invocation of            **
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
**                        Cry_GddHaeAesCbcEncryptTb                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesSetKey,                                      **
**                        Hmg_AesCbcEnc,                                      **
**                        Csm_SymBlockEncryptCallbackNotification,            **
**                        Csm_SymBlockEncryptServiceFinishNotification        **
*******************************************************************************/
void Cry_HaeAesCbcEncryptMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeAesCbcEncryptTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if ((Cry_GddHaeAesCbcEncryptTb.pKeyPtr->length != HMG_AES_N_BLOCK)
      || (Cry_GddHaeAesCbcEncryptTb.ulInitVectorLength != HMG_AES_N_BLOCK))
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblReturnValue = Hmg_AesSetKey(&Cry_GddHaeAesCbcEncryptContext,
          (const uint8*)((const void*)(Cry_GddHaeAesCbcEncryptTb.pKeyPtr->data)),
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
        (void)memcpy((void*)Cry_GaaHaeAesCbcEncryptIV,
          (const void*)(Cry_GddHaeAesCbcEncryptTb.pInitVectorPtr),
          Cry_GddHaeAesCbcEncryptTb.ulInitVectorLength);
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeAesCbcEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeAesCbcEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaeAesCbcEncryptTb.pCipherTextLengthPtr)
      < Cry_GddHaeAesCbcEncryptTb.ulPlainTextLength)
    {
      /* Buffer size is invalid */
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if ((Cry_GddHaeAesCbcEncryptTb.ulPlainTextLength < HMG_AES_N_BLOCK)
      || ((Cry_GddHaeAesCbcEncryptTb.ulPlainTextLength % HMG_AES_N_BLOCK) != CSM_ZERO))
    {
      /* plainTextLength should be multiples of 16 */
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      *(Cry_GddHaeAesCbcEncryptTb.pCipherTextLengthPtr) = CSM_ZERO;

      LblReturnValue = Hmg_AesCbcEnc(&Cry_GddHaeAesCbcEncryptContext,
          Cry_GaaHaeAesCbcEncryptIV,
          Cry_GddHaeAesCbcEncryptTb.pCipherTextPtr,
          Cry_GddHaeAesCbcEncryptTb.pPlainTextPtr,
          Cry_GddHaeAesCbcEncryptTb.ulPlainTextLength);

      if (LblReturnValue != CSM_TRUE)
      {
        *(Cry_GddHaeAesCbcEncryptTb.pCipherTextLengthPtr)
          = Cry_GddHaeAesCbcEncryptTb.ulPlainTextLength;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeAesCbcEncryptTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeAesCbcEncryptTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_SymEncryptCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeAesCbcEncryptTb.ucJobState = NO_JOB;

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

#endif /* (CSM_SYM_HAEAESCBCENCRYPT == STD_ON) */
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
