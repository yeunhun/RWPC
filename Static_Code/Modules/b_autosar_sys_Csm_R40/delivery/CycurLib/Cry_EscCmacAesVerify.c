/*******************************************************************************
**                                                                            **
**  (C) 2016~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscCmacAesVerify.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Escrypt CMAC AES Verify Interface       **
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

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for Escrypt CMAC AES Verify */
#include "Cry_EscCmacAesVerify.h"
/* Mac Interface */
#if (CSM_MAC_VERIFY_STATUS == STD_ON)
#if (CSM_MAC_ESCCMACAESVERIFY == STD_ON)
#include "Csm_Cbk.h"
#include "aes_omac1.h"
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry EscCmacAesVerify Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* pointer to the key necessary for the Escrypt CMAC AES generation */
  const Csm_SymKeyType* pKeyPtr;
  /* Stores raw data pointer used for Escrypt CMAC AES Computation */
  const uint8* pDataPtr;
  /* Data length of the data used for Escrypt CMAC AES Computation */
  uint32 ulDataLength;
  /* Stores Escrypt CMAC AES provided for verification */
  const uint8* pMacPtr;
  /* length of the provided Escrypt CMAC AES */
  uint32 ulMacLength;
  /* Stores verification result */
  Csm_VerifyResultType* pResultPtr;
} Cry_EscCmacAesVerifyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Escrypt CMAC AES primitive library context */
static EscAesOmac1_ContextT Cry_GddEscCmacAesVerifyContext;

/* Global variable for Escrypt CMAC AES transfer buffer structure */
static Cry_EscCmacAesVerifyTransferBuffer Cry_GddEscCmacAesVerifyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_EscCmacAesVerifyInit                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the Escrypt CMAC AES         **
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
** Remarks            : Global Variable(s):  Cry_GddEscCmacAesVerifyTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_EscCmacAesVerifyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddEscCmacAesVerifyTb.ucJobState = NO_JOB;
  Cry_GddEscCmacAesVerifyTb.pKeyPtr = NULL_PTR;
  Cry_GddEscCmacAesVerifyTb.pDataPtr = NULL_PTR;
  Cry_GddEscCmacAesVerifyTb.ulDataLength = CSM_ZERO;
  Cry_GddEscCmacAesVerifyTb.pMacPtr = NULL_PTR;
  Cry_GddEscCmacAesVerifyTb.ulMacLength = CSM_ZERO;
  Cry_GddEscCmacAesVerifyTb.pResultPtr = NULL_PTR;

  (void)memset((void*)&Cry_GddEscCmacAesVerifyContext, 0x00,
    sizeof(EscAesOmac1_ContextT));
}

/*******************************************************************************
** Function Name        : Cry_EscCmacAesVerifyStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Escrypt CMAC AES, so that if is      **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_EscCmacAesVerifyMainFunction() can process      **
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
**                        Cry_GddEscCmacAesVerifyTb                           **
**                        Cry_GpEscCmacAesVerifyConfigPtr                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscAesOmac1_Init                                    **
*******************************************************************************/
Std_ReturnType Cry_EscCmacAesVerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddEscCmacAesVerifyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_EscCmacAesVerifyInit();

    Cry_GddEscCmacAesVerifyTb.ucJobState = JOB_START;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (keyPtr->length != EscAes_KEY_BYTES)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LblReturnValue = EscAesOmac1_Init(&Cry_GddEscCmacAesVerifyContext,
          (const uint8*)((const void*)(keyPtr->data)));

        if (LblReturnValue == CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscCmacAesVerifyTb.pKeyPtr = keyPtr;
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
** Function Name        : Cry_EscCmacAesVerifyUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Escrypt  **
**                        CMAC AES                                            **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscCmacAesVerifyMainFunction() can process      **
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
**                        Cry_GddEscCmacAesVerifyTb                           **
**                        Cry_GpEscCmacAesVerifyConfigPtr                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscAesOmac1_Update                                  **
*******************************************************************************/
Std_ReturnType Cry_EscCmacAesVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddEscCmacAesVerifyTb.ucJobState)
  {
    Cry_GddEscCmacAesVerifyTb.ucJobState = JOB_UPDATE;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      LblReturnValue = EscAesOmac1_Update(&Cry_GddEscCmacAesVerifyContext,
        dataPtr, dataLength);

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddEscCmacAesVerifyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddEscCmacAesVerifyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddEscCmacAesVerifyTb.pDataPtr = dataPtr;
      Cry_GddEscCmacAesVerifyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_EscCmacAesVerifyFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Escrypt **
**                        CMAC AES computation and store the result into      **
**                        the memory location given                           **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_EscCmacAesVerifyMainFunction() can finish the**
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
**                        Cry_GddEscCmacAesVerifyTb                           **
**                        Cry_GpEscCmacAesVerifyConfigPtr                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscAesOmac1_Finish                                  **
*******************************************************************************/
Std_ReturnType Cry_EscCmacAesVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaCmacAesDigest[EscAes_KEY_BYTES];
  uint32 LulIndex;
  Csm_VerifyResultType LddVerifyResult;
  uint32 LulMacLength;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddEscCmacAesVerifyTb.ucJobState)
  {
    Cry_GddEscCmacAesVerifyTb.ucJobState = JOB_FINISH;

    if (Csm_MacVerifyServiceHasCallback() == FALSE)
    {
      (void)memset((void*)&LaaCmacAesDigest, 0x00, sizeof(LaaCmacAesDigest));

      LblReturnValue = EscAesOmac1_Finish(&Cry_GddEscCmacAesVerifyContext,
        LaaCmacAesDigest, EscAes_KEY_BYTES);

      if (LblReturnValue != CSM_TRUE)
      {
        LulMacLength = MacLength;
        LddVerifyResult = CSM_E_VER_OK;
        if (LulMacLength > EscAes_KEY_BYTES * CSM_EIGHT)
        {
          LulMacLength = EscAes_KEY_BYTES * CSM_EIGHT;
        }

        /* Comparing the two MACs */
        /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The length is checked" */
        for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          if (MacPtr[LulIndex] != LaaCmacAesDigest[LulIndex])
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
            /* polyspace +3 MISRA-C3:18.1 RTE:IDP RTE:OBAI [Justified:Low] "The array index is checked" */
            /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            if ((MacPtr[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE)))
              != (LaaCmacAesDigest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
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
      Cry_GddEscCmacAesVerifyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddEscCmacAesVerifyTb.pMacPtr = MacPtr;
      Cry_GddEscCmacAesVerifyTb.ulMacLength = MacLength;
      Cry_GddEscCmacAesVerifyTb.pResultPtr = resultPtr;
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
** Function Name        : Cry_EscCmacAesVerifyMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_MacVerifyCallbackNotification() with the        **
**                        correct return value once the main function has     **
**                        completely processed the cryptographic              **
**                        functions demanded by                               **
**                        Cry_EscCmacAesVerifyStart() or                      **
**                        Cry_EscCmacAesVerifyUpdate(). For                   **
**                        Cry_EscCmacAesVerifyFinish invocation of            **
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
**                        Cry_GddEscCmacAesVerifyTb                           **
**                        Cry_GpEscCmacAesVerifyConfigPtr                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                        EscAesOmac1_Init                                    **
**                        EscAesOmac1_Update                                  **
**                        EscAesOmac1_Finish                                  **
**                        Csm_MacVerifyCallbackNotification                   **
**                        Csm_MacVerifyServiceFinishNotification              **
*******************************************************************************/
void Cry_EscCmacAesVerifyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LaaCmacAesDigest[EscAes_KEY_BYTES];
  uint32 LulIndex;
  Csm_VerifyResultType LddVerifyResult;
  uint32 LulMacLength;
  const uint8* LpMacPtr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddEscCmacAesVerifyTb.ucJobState)
  {
  case JOB_START:
    /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (Cry_GddEscCmacAesVerifyTb.pKeyPtr->length != EscAes_KEY_BYTES)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LblReturnValue = EscAesOmac1_Init(&Cry_GddEscCmacAesVerifyContext,
        (const uint8*)((const void*)(Cry_GddEscCmacAesVerifyTb.pKeyPtr->data)));

      if (LblReturnValue == CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscCmacAesVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscCmacAesVerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    LblReturnValue = EscAesOmac1_Update(&Cry_GddEscCmacAesVerifyContext,
      Cry_GddEscCmacAesVerifyTb.pDataPtr,
      Cry_GddEscCmacAesVerifyTb.ulDataLength);

    if (LblReturnValue == CSM_TRUE)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddEscCmacAesVerifyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddEscCmacAesVerifyTb.ucJobState = NO_JOB;
    }

    /* Notify respective Service about the completion of the task */
    Csm_MacVerifyCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    (void)memset((void*)&LaaCmacAesDigest, 0x00, sizeof(LaaCmacAesDigest));

    LblReturnValue = EscAesOmac1_Finish(&Cry_GddEscCmacAesVerifyContext,
      LaaCmacAesDigest, EscAes_KEY_BYTES);

    if (LblReturnValue != CSM_TRUE)
    {
      LulMacLength = Cry_GddEscCmacAesVerifyTb.ulMacLength;
      LpMacPtr = Cry_GddEscCmacAesVerifyTb.pMacPtr;
      LddVerifyResult = CSM_E_VER_OK;
      if (LulMacLength > EscAes_KEY_BYTES * CSM_EIGHT)
      {
        LulMacLength = EscAes_KEY_BYTES * CSM_EIGHT;
      }

      /* Comparing the two MACs */
      for (LulIndex = CSM_ZERO; LulIndex < (LulMacLength / CSM_EIGHT); LulIndex++)
      {
        /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        if (LpMacPtr[LulIndex] != LaaCmacAesDigest[LulIndex])
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
            != (LaaCmacAesDigest[LulMacLength / CSM_EIGHT] & (uint8)(CSM_ONE << (CSM_EIGHT - LulIndex - CSM_ONE))))
          {
            LddVerifyResult = CSM_E_VER_NOT_OK;
            break;
          }
        }
      }
      /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      *(Cry_GddEscCmacAesVerifyTb.pResultPtr) = LddVerifyResult;
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddEscCmacAesVerifyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_MAC_ESCCMACAESVERIFY == STD_ON) */
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
