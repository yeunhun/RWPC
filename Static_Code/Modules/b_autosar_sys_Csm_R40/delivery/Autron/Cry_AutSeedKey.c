/*******************************************************************************
**                                                                            **
**  (C) 2015~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutSeedKey.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - Autron SeedKey                                            **
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
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.2.3     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.2.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.1     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198                         **
** 1.0.10    21-Sep-2016   Sinil        Redmine #5554, #6128                  **
** 1.0.9     09-Aug-2016   Sinil        Redmine #5693, #5540                  **
** 1.0.8     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.7     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.6     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.5     02-May-2016   Sinil        Redmine #4607                         **
** 1.0.4     05-Jan-2016   Sinil        Use const macro                       **
** 1.0.3     30-Dec-2015   Sinil        1. Crypto api used to exchange buffers**
**                                      2. Check seed & result length         **
** 1.0.2     02-Dec-2015   Sinil        1. Crypto api changed                 **
**                                      2. Memory section changed             **
** 1.0.1     09-Sep-2015   Sinil        Add endian conversion                 **
** 1.0.0     10-Mar-2015   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:2.1,14.3 [Justified:Low] "No Impact of this rule violation" */
/* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_AutSeedKey.h"
#if (CSM_HASH_STATUS == STD_ON)
#if (CSM_HASH_AUTSEEDKEY == STD_ON)
#include "Csm_Cbk.h"
#include "AutSeedKey.h"

/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/
/** Length of one hash block in bytes. */
#define AUT_SEEDKEY_BLOCK_BYTES                         Aut_SeedKey_BLOCK_BYTES
/** Length of digest in byte. */
#define AUT_SEEDKEY_DIGEST_LEN                          Aut_SeedKey_DIGEST_LEN

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry AutSeedKey Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const uint8* pDataPtr;
  uint32 ulDataLength;
  uint8* pResultPtr;
  uint32* pResultLengthPtr;
  boolean blTruncationIsAllowed;
} Cry_AutSeedKeyTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Autron SeedKey context structure */
static uint32 Cry_GulAutSeedKey;

/* Global pointer to variable for Autron SeedKey transfer buffer structure */
static Cry_AutSeedKeyTransferBuffer Cry_GddAutSeedKeyTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutSeedKeyInit                                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the transfer buffer of the   **
**                      Autron AdvSeedKey module. All module Global variables **
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
** Remarks            : Global Variable(s): Cry_GddAutSeedKeyTb               **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutSeedKeyInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutSeedKeyTb.ucJobState = NO_JOB;
  Cry_GddAutSeedKeyTb.pDataPtr = NULL_PTR;
  Cry_GddAutSeedKeyTb.ulDataLength = CSM_ZERO;
  Cry_GddAutSeedKeyTb.pResultPtr = NULL_PTR;
  Cry_GddAutSeedKeyTb.pResultLengthPtr = NULL_PTR;
  Cry_GddAutSeedKeyTb.blTruncationIsAllowed = CSM_FALSE;

  Cry_GulAutSeedKey = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutSeedKeyStart                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autron SeedKey, so that SeedKey is   **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        provided in the arguments so that                   **
**                        Cry_AutSeedKeyMainFunction() can process            **
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
** Remarks              : Global Variable(s): Cry_GddAutSeedKeyTb             **
**                        Function(s) invoked: Cry_AutSeedKeyInit             **
*******************************************************************************/
Std_ReturnType Cry_AutSeedKeyStart(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutSeedKeyTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutSeedKeyInit();

    Cry_GddAutSeedKeyTb.ucJobState = JOB_START;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      Cry_GddAutSeedKeyTb.ucJobState = JOB_DONE;
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
** Function Name        : Cry_AutSeedKeyUpdate                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Autron   **
**                        SeedKey                                             **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutSeedKeyMainFunction() can process the input  **
**                        data                                                **
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
** Remarks              : Global Variable(s): Cry_GddAutSeedKeyTb             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        AutSeedKey_Generate                                 **
*******************************************************************************/
Std_ReturnType Cry_AutSeedKeyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint32 LulValue = CSM_ZERO;

  /* Setting the default return value */
  LddReturnValue = E_OK;

  /* Mark the unused parameter */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutSeedKeyTb.ucJobState)
  {
    Cry_GddAutSeedKeyTb.ucJobState = JOB_UPDATE;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      if (dataLength < AUT_SEEDKEY_BLOCK_BYTES)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        /* Make big endian uint32 value */
        /* polyspace +2 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        LulValue
          = ((uint32)(dataPtr[CSM_ZERO]) << 24U)
          + ((uint32)(dataPtr[CSM_ONE]) << 16U)
          + ((uint32)(dataPtr[CSM_TWO]) << 8U)
          + (uint32)(dataPtr[CSM_THREE]);

        /* Feeding the data to primitive */
        LblReturnValue = AutSeedKey_Generate(&Cry_GulAutSeedKey, LulValue);

        if (LblReturnValue != CSM_TRUE)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutSeedKeyTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutSeedKeyTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutSeedKeyTb.pDataPtr = dataPtr;
      Cry_GddAutSeedKeyTb.ulDataLength = dataLength;
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
** Function Name        : Cry_AutSeedKeyFinish                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall finish the Autron  **
**                        SeedKey computation and store the result into the   **
**                        memory location given                               **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutSeedKeyMainFunction() can finish the         **
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
** Remarks              : Global Variable(s): Cry_GddAutSeedKeyTb             **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_AutSeedKeyFinish(Csm_ConfigIdType cfgId, uint8* resultPtr,
  uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;
  uint32 LulValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Mark the unused parameter */
  CSM_PARAM_UNUSED(cfgId);
  CSM_PARAM_UNUSED(TruncationIsAllowed);

  /* Check if the update is already complete & module is ready to finish */
  if (JOB_DONE == Cry_GddAutSeedKeyTb.ucJobState)
  {
    Cry_GddAutSeedKeyTb.ucJobState = JOB_FINISH;

    if (Csm_HashServiceHasCallback() == FALSE)
    {
      /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      if (*resultLengthPtr < AUT_SEEDKEY_DIGEST_LEN)
      {
        LddReturnValue = CSM_E_SMALL_BUFFER;
      }

      if (LddReturnValue == E_OK)
      {
        LulValue = Cry_GulAutSeedKey;
        /* polyspace +4 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        resultPtr[CSM_ZERO] = (uint8)((LulValue & ((uint32)0xFFU << 24U)) >> 24U) & (uint8)0xFFU;
        resultPtr[CSM_ONE] = (uint8)((LulValue & ((uint32)0xFFU << 16U)) >> 16U) & (uint8)0xFFU;
        resultPtr[CSM_TWO] = (uint8)((LulValue & ((uint32)0xFFU << 8U)) >> 8U) & (uint8)0xFFU;
        resultPtr[CSM_THREE] = (uint8)LulValue & (uint8)0xFFU;

        /* Update the length of the result buffer */
        *resultLengthPtr = AUT_SEEDKEY_DIGEST_LEN;
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutSeedKeyTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutSeedKeyTb.blTruncationIsAllowed = TruncationIsAllowed;
      Cry_GddAutSeedKeyTb.pResultPtr = resultPtr;
      Cry_GddAutSeedKeyTb.pResultLengthPtr = resultLengthPtr;
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
** Function Name        : Cry_AutSeedKeyMainFunction                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_HashCallbackNotification() with the correct     **
**                        return valueonce the main function has completely   **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_AutSeedKeyStart() or      **
**                        Cry_AutSeedKeyUpdate(). For Cry_AutSeedKeyFinish    **
**                        invocation of Csm_HashCallbackNotification()        **
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
** Remarks              : Global Variable(s): Cry_GddAutSeedKeyTb             **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Csm_HashCallbackNotification,                       **
**                        AutSeedKey_Generate,                                **
**                        Csm_HashServiceFinishNotification                   **
*******************************************************************************/
void Cry_AutSeedKeyMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint32 LulValue = CSM_ZERO;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of Autron AdvSeedKey job processing */
  switch (Cry_GddAutSeedKeyTb.ucJobState)
  {
  case JOB_START:
    Cry_GddAutSeedKeyTb.ucJobState = JOB_DONE;

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    if (Cry_GddAutSeedKeyTb.ulDataLength < AUT_SEEDKEY_BLOCK_BYTES)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
        /* Make big endian uint32 value */
      LulValue
	      /* polyspace +5 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
	      /* polyspace +4 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
        = ((uint32)(Cry_GddAutSeedKeyTb.pDataPtr[CSM_ZERO]) << 24U)
        + ((uint32)(Cry_GddAutSeedKeyTb.pDataPtr[CSM_ONE]) << 16U)
        + ((uint32)(Cry_GddAutSeedKeyTb.pDataPtr[CSM_TWO]) << 8U)
        + (uint32)(Cry_GddAutSeedKeyTb.pDataPtr[CSM_THREE]);

      /* Feeding the data to primitive */
      LblReturnValue = AutSeedKey_Generate(&Cry_GulAutSeedKey, LulValue);

      if (LblReturnValue != CSM_TRUE)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutSeedKeyTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutSeedKeyTb.ucJobState = NO_JOB;
    }

    /* Callback notification will be invoking the application callback */
    Csm_HashCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* polyspace +2 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    /* polyspace +1 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
    if (*(Cry_GddAutSeedKeyTb.pResultLengthPtr) < AUT_SEEDKEY_DIGEST_LEN)
    {
      LddReturnValue = CSM_E_SMALL_BUFFER;
    }

    if (LddReturnValue == E_OK)
    {
      LulValue = Cry_GulAutSeedKey;
      /* polyspace +9 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      /* polyspace +8 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      Cry_GddAutSeedKeyTb.pResultPtr[CSM_ZERO]
        = (uint8)((LulValue & ((uint32)0xFFU << 24U)) >> 24U) & (uint8)0xFFU;
      Cry_GddAutSeedKeyTb.pResultPtr[CSM_ONE]
        = (uint8)((LulValue & ((uint32)0xFFU << 16U)) >> 16U) & (uint8)0xFFU;
      Cry_GddAutSeedKeyTb.pResultPtr[CSM_TWO]
        = (uint8)((LulValue & ((uint32)0xFFU << 8U)) >> 8U) & (uint8)0xFFU;
      Cry_GddAutSeedKeyTb.pResultPtr[CSM_THREE]
        = (uint8)LulValue & (uint8)0xFFU;

      /* Update the length of the result buffer */
      *(Cry_GddAutSeedKeyTb.pResultLengthPtr) = AUT_SEEDKEY_DIGEST_LEN;
    }

    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutSeedKeyTb.ucJobState = NO_JOB;

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

#endif /* (CSM_HASH_AUTSEEDKEY == STATUS_ON) */
#endif /* (CSM_HASH_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:2.1,14.3 [Justified:Low] "No Impact of this rule violation" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
