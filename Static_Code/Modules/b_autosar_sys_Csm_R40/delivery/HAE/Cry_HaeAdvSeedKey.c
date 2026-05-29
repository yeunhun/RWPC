/*******************************************************************************
**                                                                            **
**  (C) 2015~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeAdvSeedKey.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - Autoever AdvSeedKey                                       **
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
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.2.4     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.2.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.2     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.2.1     20-Sep-2017   Sinil        Redmine #10034                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198                         **
** 1.0.9     21-Sep-2016   Sinil        Redmine #5554, #6128                  **
** 1.0.8     09-Aug-2016   Sinil        Redmine #5693                         **
** 1.0.7     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.6     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.5     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.4     02-May-2016   Sinil        Redmine #4797, #4607                  **
** 1.0.3     05-Jan-2016   Sinil        Use const macro                       **
** 1.0.2     30-Dec-2015   Sinil        1. Remove unnecessary unused macro    **
**                                      2. Check seed & result length         **
** 1.0.1     02-Dec-2015   Sinil        1. Fix wrong feature macro            **
**                                      2. Memory section changed             **
** 1.0.0     16-Sep-2015   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Header File for HaeAdvSeedKey */
#include "Cry_HaeAdvSeedKey.h"
/* Hash Interface */
#if (CSM_HASH_STATUS == STD_ON)
#if (CSM_HASH_HAEADVSEEDKEY == STD_ON)
#include "Csm_Cbk.h"
#include "HKMC_ASK_Server.h"
#include "string.h"

/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/
/** Length of seed in bytes. */
#define CSM_HAE_ADVSEEDKEY_SEED_BYTES                    (8U)
/** Length of key in bytes. */
#define CSM_HAE_ADVSEEDKEY_KEY_BYTES                     (8U)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HaeAdvSeedKey Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  uint8* pResultPtr;
  uint32* pResultLengthPtr;
  boolean blTruncationIsAllowed;
} Cry_HaeAdvSeedKeyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* AdvSeedKey seed value */
static uint8 Cry_GaaHaeAdvSeedValue[CSM_HAE_ADVSEEDKEY_SEED_BYTES];

#define CSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Global pointer to variable for AdvSeedKey transfer buffer structure */
static Cry_HaeAdvSeedKeyTransferBuffer Cry_GddHaeAdvSeedKeyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_HaeAdvSeedKeyInit                                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the transfer buffer of the   **
**                      AdvSeedKey module. All module Global variables        **
**                      will be initialized after successful completion of    **
**                      this API.                                             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
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
** Remarks            : Global Variable(s): Cry_GddHaeAdvSeedKeyTb            **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeAdvSeedKeyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeAdvSeedKeyTb.ucJobState = NO_JOB;
  Cry_GddHaeAdvSeedKeyTb.pDataPtr = NULL_PTR;
  Cry_GddHaeAdvSeedKeyTb.ulDataLength = CSM_ZERO;
  Cry_GddHaeAdvSeedKeyTb.pResultPtr = NULL_PTR;
  Cry_GddHaeAdvSeedKeyTb.pResultLengthPtr = NULL_PTR;
  Cry_GddHaeAdvSeedKeyTb.blTruncationIsAllowed = CSM_FALSE;

  (void)memset((void*)Cry_GaaHaeAdvSeedValue, 0x00, CSM_HAE_ADVSEEDKEY_SEED_BYTES);
}

/*******************************************************************************
** Function Name        : Cry_HaeAdvSeedKeyStart                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of AdvSeedKey, so that AdvSeedKey       **
**                        is able to process the input data                   **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_HaeAdvSeedKeyMainFunction() can process         **
**                        initialisation                                      **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgPtr                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : CSM should have been initialized                    **
**                                                                            **
** Remarks              : Global Variable(s): Cry_GddHaeAdvSeedKeyTb          **
**                        Function(s) invoked: Cry_HaeAdvSeedKeyInit          **
*******************************************************************************/
Std_ReturnType Cry_HaeAdvSeedKeyStart(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeAdvSeedKeyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeAdvSeedKeyInit();

    Cry_GddHaeAdvSeedKeyTb.ucJobState = JOB_START;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      Cry_GddHaeAdvSeedKeyTb.ucJobState = JOB_DONE;
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
** Function Name        : Cry_HaeAdvSeedKeyUpdate                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the          **
**                        AdvSeedKey                                          **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeAdvSeedKeyMainFunction() can process the     **
**                        input data                                          **
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
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : Primitive should have been successfully initialized **
**                                                                            **
** Remarks              : Global Variable(s): Cry_GddHaeAdvSeedKeyTb          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_HaeAdvSeedKeyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  uint8 LucIndex;

  /* Setting the default return value */
  LddReturnValue = E_OK;

  /* Mark the unused parameter */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeAdvSeedKeyTb.ucJobState)
{
    Cry_GddHaeAdvSeedKeyTb.ucJobState = JOB_UPDATE;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      if (dataLength < CSM_HAE_ADVSEEDKEY_SEED_BYTES)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        for (LucIndex = CSM_ZERO; LucIndex < CSM_HAE_ADVSEEDKEY_SEED_BYTES;
          LucIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          Cry_GaaHaeAdvSeedValue[LucIndex] = (uint8)(dataPtr[LucIndex]);
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddHaeAdvSeedKeyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeAdvSeedKeyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeAdvSeedKeyTb.pDataPtr = dataPtr;
      Cry_GddHaeAdvSeedKeyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_HaeAdvSeedKeyFinish                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the         **
**                        AdvSeedKey computation and store the result into the**
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeAdvSeedKeyMainFunction() can finish the      **
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
**                        CSM_E_BUSY: service state is already "active"       **
**                        CSM_E_SMALL_BUFFER: provided buffer is too small to **
**                                            store the result                **
**                                                                            **
** Preconditions        : Primitive should have been successfully initialized **
**                                                                            **
** Remarks              : Global Variable(s): Cry_GddHaeAdvSeedKeyTb          **
**                                                                            **
**                        Function(s) invoked : ASK_KeyGenerate               **
*******************************************************************************/
Std_ReturnType Cry_HaeAdvSeedKeyFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  SEEDKEY_RT LddPrimitiveReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Mark the unused parameter */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED(TruncationIsAllowed);

  /* Check if the update is already complete & module is ready to finish */
  if (JOB_DONE == Cry_GddHaeAdvSeedKeyTb.ucJobState)
  {
    Cry_GddHaeAdvSeedKeyTb.ucJobState = JOB_FINISH;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*resultLengthPtr < CSM_HAE_ADVSEEDKEY_KEY_BYTES)
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        LddPrimitiveReturnValue = ASK_KeyGenerate(Cry_GaaHaeAdvSeedValue,
          resultPtr);

        if (LddPrimitiveReturnValue == SEEDKEY_SUCCESS)
        {
          *resultLengthPtr = CSM_HAE_ADVSEEDKEY_KEY_BYTES;
        }
        else
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeAdvSeedKeyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeAdvSeedKeyTb.blTruncationIsAllowed = TruncationIsAllowed;
      Cry_GddHaeAdvSeedKeyTb.pResultPtr = resultPtr;
      Cry_GddHaeAdvSeedKeyTb.pResultLengthPtr = resultLengthPtr;
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
** Function Name        : Cry_HaeAdvSeedKeyMainFunction                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_HashCallbackNotification() with the correct     **
**                        return valueonce the main function has completely   **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_HaeAdvSeedKeyStart() or   **
**                        Cry_HaeAdvSeedKeyUpdate(). For                      **
**                        Cry_HaeAdvSeedKeyFinish invocation of               **
**                        Csm_HashCallbackNotification()                      **
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
** Remarks              : Global Variable(s): Cry_GddHaeAdvSeedKeyTb          **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Csm_HashCallbackNotification,                       **
**                        ASK_KeyGenerate,                                    **
**                        Csm_HashServiceFinishNotification                   **
*******************************************************************************/
void Cry_HaeAdvSeedKeyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  SEEDKEY_RT LddPrimitiveReturnValue;
  uint8 LucIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeAdvSeedKeyTb.ucJobState)
  {
  case JOB_START:
    Cry_GddHaeAdvSeedKeyTb.ucJobState = JOB_DONE;

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    if (Cry_GddHaeAdvSeedKeyTb.ulDataLength < CSM_HAE_ADVSEEDKEY_SEED_BYTES)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      for (LucIndex = CSM_ZERO; LucIndex < CSM_HAE_ADVSEEDKEY_SEED_BYTES;
        LucIndex++)
      {
	/* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	/* polyspace +2 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
        Cry_GaaHaeAdvSeedValue[LucIndex]
          = (uint8)(Cry_GddHaeAdvSeedKeyTb.pDataPtr[LucIndex]);
      }
    }

    Cry_GddHaeAdvSeedKeyTb.ucJobState = JOB_DONE;

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +3 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +1 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddHaeAdvSeedKeyTb.pResultLengthPtr) < CSM_HAE_ADVSEEDKEY_KEY_BYTES)
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      LddPrimitiveReturnValue = ASK_KeyGenerate(Cry_GaaHaeAdvSeedValue,
        Cry_GddHaeAdvSeedKeyTb.pResultPtr);

      if (LddPrimitiveReturnValue == SEEDKEY_SUCCESS)
      {
        *(Cry_GddHaeAdvSeedKeyTb.pResultLengthPtr)
          = CSM_HAE_ADVSEEDKEY_KEY_BYTES;
      }
      else
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeAdvSeedKeyTb.ucJobState = NO_JOB;

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_HashServiceFinishNotification();
    break;
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_HASH_HAEADVSEEDKEY == STATUS_ON) */
#endif /* (CSM_HASH_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
