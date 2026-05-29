/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeCmacAesVerify.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Autoever CMAC AES Verify Interface      **
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
/* Header File for Autoever CMAC AES Verify */
#include "Cry_HaeCmacAesVerify.h"
/* Mac Interface */
#if (CSM_MAC_VERIFY_STATUS == STD_ON)
#if (CSM_MAC_HAECMACAESVERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "Hmg_Aes.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeCmacAesVerify Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* pointer to the key necessary for the Autoever CMAC AES generation */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores raw data pointer used for Autoever CMAC AES Computation */
  const uint8* pDataPtr;
  /* Data length of the data used for Autoever CMAC AES Computation */
  uint32 ulDataLength;
  /* Stores Autoever CMAC AES provided for verification */
  const uint8* pMacPtr;
  /* length of the provided Autoever CMAC AES */
  uint32 ulMacLength;
  /* Stores verification result */
  Csm_VerifyResultType* pResultPtr;
} Cry_HaeCmacAesVerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Autoever CMAC AES primitive library context */
static HmgAesCmacCtx Cry_GddHaeCmacAesVerifyContext;

/* Global variable for Autoever CMAC AES transfer buffer structure */
static Cry_HaeCmacAesVerifyTransferBuffer Cry_GddHaeCmacAesVerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeCmacAesVerifyInit                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Autoever CMAC AES        **
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
** Remarks            : Global Variable(s):  Cry_GddHaeCmacAesVerifyTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeCmacAesVerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeCmacAesVerifyTb.ucJobState = NO_JOB;
  Cry_GddHaeCmacAesVerifyTb.pKeyPtr = NULL_PTR;
  Cry_GddHaeCmacAesVerifyTb.pDataPtr = NULL_PTR;
  Cry_GddHaeCmacAesVerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeCmacAesVerifyTb.pMacPtr = NULL_PTR;
  Cry_GddHaeCmacAesVerifyTb.ulMacLength = CSM_ZERO;
  Cry_GddHaeCmacAesVerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddHaeCmacAesVerifyContext, 0x00,
    sizeof(HmgAesCmacCtx));
}

/*******************************************************************************
** Function Name        : Cry_HaeCmacAesVerifyStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autoever CMAC AES, so that if is     **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeCmacAesVerifyMainFunction() can process      **
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
**                        Cry_GddHaeCmacAesVerifyTb                           **
**                        Cry_GpHaeCmacAesVerifyConfigPtr                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesCmacStart                                    **
*******************************************************************************/
Std_ReturnType Cry_HaeCmacAesVerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeCmacAesVerifyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeCmacAesVerifyInit();

    Cry_GddHaeCmacAesVerifyTb.ucJobState = JOB_START;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != HMG_AES_N_BLOCK)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblReturnValue = Hmg_AesCmacStart(&Cry_GddHaeCmacAesVerifyContext,
          (const uint8*)((const void*)(keyPtr->data)), HMG_AES_N_BLOCK);

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeCmacAesVerifyTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_HaeCmacAesVerifyUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Autoever  **
**                        CMAC AES                                            **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeCmacAesVerifyMainFunction() can process      **
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
**                        Cry_GddHaeCmacAesVerifyTb                           **
**                        Cry_GpHaeCmacAesVerifyConfigPtr                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesCmacUpdate                                   **
*******************************************************************************/
Std_ReturnType Cry_HaeCmacAesVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeCmacAesVerifyTb.ucJobState)
  {
    Cry_GddHaeCmacAesVerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      LblReturnValue = Hmg_AesCmacUpdate(&Cry_GddHaeCmacAesVerifyContext,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeCmacAesVerifyTb.pDataPtr = dataPtr;
      Cry_GddHaeCmacAesVerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeCmacAesVerifyFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Autoever**
**                        CMAC AES computation and store the result into      **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeCmacAesVerifyMainFunction() can finish the   **
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
**                        Cry_GddHaeCmacAesVerifyTb                           **
**                        Cry_GpHaeCmacAesVerifyConfigPtr                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesCmacFinish                                   **
*******************************************************************************/
Std_ReturnType Cry_HaeCmacAesVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaCmacAesDigest[HMG_AES_N_BLOCK];
  uint32 LulIndex;
  boolean LblResult;
  uint32 LulMacLength;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeCmacAesVerifyTb.ucJobState)
  {
    Cry_GddHaeCmacAesVerifyTb.ucJobState = JOB_FINISH;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      (void)memset((void*)&LaaCmacAesDigest, 0x00, sizeof(LaaCmacAesDigest));

      LblReturnValue = Hmg_AesCmacFinish(&Cry_GddHaeCmacAesVerifyContext,
        LaaCmacAesDigest);

      if (LblReturnValue != CSM_TRUE)
      {
        LulMacLength = MacLength;
        if (LulMacLength > HMG_AES_N_BLOCK * CSM_EIGHT)
        {
          LulMacLength = HMG_AES_N_BLOCK * CSM_EIGHT;
        }

        /* Comparing the two MACs */
        LblResult = CSM_TRUE;
        /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer and length is checked" */
        for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer and length is checked" */
          if (MacPtr[LulIndex] != LaaCmacAesDigest[LulIndex])
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
	          /* polyspace-begin MISRA-C3:18.1,D4.1,D4.14 RTE:IDP RTE:OBAI [Justified:Low] "No Impact of this rule violation" */
            if ((MacPtr[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
              != (LaaCmacAesDigest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
            {
              LblResult = CSM_FALSE;
              break;
            }
            /* polyspace-end MISRA-C3:18.1,D4.1,D4.14 RTE:IDP RTE:OBAI */
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
      Cry_GddHaeCmacAesVerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeCmacAesVerifyTb.pMacPtr = MacPtr;
      Cry_GddHaeCmacAesVerifyTb.ulMacLength = MacLength;
      Cry_GddHaeCmacAesVerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_HaeCmacAesVerifyMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacVerifyCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_HaeCmacAesVerifyStart() or                      **
**                        Cry_HaeCmacAesVerifyUpdate(). For                   **
**                        Cry_HaeCmacAesVerifyFinish invocation of            **
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
**                        Cry_GddHaeCmacAesVerifyTb                           **
**                        Cry_GpHaeCmacAesVerifyConfigPtr                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Hmg_AesCmacStart                                    **
**                        Hmg_AesCmacUpdate                                   **
**                        Hmg_AesCmacFinish                                   **
**                        Csm_MacVerifyCallbackNotification                   **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
void Cry_HaeCmacAesVerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaCmacAesDigest[HMG_AES_N_BLOCK];
  uint32 LulIndex;
  boolean LblResult;
  uint32 LulMacLength;
  const uint8* LpMacPtr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeCmacAesVerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (Cry_GddHaeCmacAesVerifyTb.pKeyPtr->length != HMG_AES_N_BLOCK)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblReturnValue = Hmg_AesCmacStart(&Cry_GddHaeCmacAesVerifyContext,
        (const uint8*)((const void*)(Cry_GddHaeCmacAesVerifyTb.pKeyPtr->data)),
        HMG_AES_N_BLOCK);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeCmacAesVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeCmacAesVerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = Hmg_AesCmacUpdate(&Cry_GddHaeCmacAesVerifyContext,
      Cry_GddHaeCmacAesVerifyTb.pDataPtr,
      Cry_GddHaeCmacAesVerifyTb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddHaeCmacAesVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddHaeCmacAesVerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    (void)memset((void*)&LaaCmacAesDigest, 0x00, sizeof(LaaCmacAesDigest));

    LblReturnValue = Hmg_AesCmacFinish(&Cry_GddHaeCmacAesVerifyContext,
      LaaCmacAesDigest);

    if (LblReturnValue != CSM_TRUE)
    {
      LulMacLength = Cry_GddHaeCmacAesVerifyTb.ulMacLength;
      LpMacPtr = Cry_GddHaeCmacAesVerifyTb.pMacPtr;

      if (LulMacLength > HMG_AES_N_BLOCK * CSM_EIGHT)
      {
        LulMacLength = HMG_AES_N_BLOCK * CSM_EIGHT;
      }

      /* Comparing the two MACs */
      LblResult = CSM_TRUE;
      for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
      {
	/* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	/* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
        if (LpMacPtr[LulIndex] != LaaCmacAesDigest[LulIndex])
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
	  /* polyspace +4 RTE:OBAI [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	  /* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          if ((LpMacPtr[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
            != (LaaCmacAesDigest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
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
        *(Cry_GddHaeCmacAesVerifyTb.pResultPtr) = CSM_E_VER_OK;
      }
      else
      {
        *(Cry_GddHaeCmacAesVerifyTb.pResultPtr) = CSM_E_VER_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeCmacAesVerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_MAC_HAECMACAESVERIFY == STD_ON) */
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
