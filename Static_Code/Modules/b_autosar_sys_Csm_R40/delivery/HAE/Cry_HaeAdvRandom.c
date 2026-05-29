/*******************************************************************************
**                                                                            **
**  (C) 2015~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeAdvRandom.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - Autoever Advanced Random                                  **
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
** 1.2.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.2     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.2.1     20-Sep-2017   Sinil        Redmine #10034                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198                         **
** 1.0.11    21-Sep-2016   Sinil        Redmine #5554, #6128                  **
** 1.0.10    09-Aug-2016   Sinil        Redmine #5693, #5540                  **
** 1.0.9     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.8     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.7     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.6     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.5     02-May-2016   Sinil        Redmine #4797, #4607                  **
** 1.0.4     05-Jan-2016   Sinil        Use const macro                       **
** 1.0.3     31-Dec-2015   Sinil        Crypto common api used                **
** 1.0.2     29-Dec-2015   Sinil        1. Random number assignment changed   **
** 1.0.1     02-Dec-2015   Sinil        1. Fix wrong feature macro            **
**                                      2. Crypto api changed                 **
**                                      3. Memory section changed             **
** 1.0.0     15-Sep-2015   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_HaeAdvRandomSeed.h"
#include "Cry_HaeAdvRandomGenerate.h"
#if ((CSM_RANDOM_SEED_STATUS == STD_ON) || (CSM_RANDOM_GENERATE_STATUS == STD_ON))
#if ((CSM_RANDOM_HAEADVRANDOMSEED == STD_ON) || (CSM_RANDOM_HAEADVRANDOMGENERATE == STD_ON))
#include "Csm_Cbk.h"
#include "HKMC_ASK_Server.h"

/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/
/** Length of random seed in bytes. */
#define CSM_HAE_ADVRANDOM_SEED_BYTES                    4U

/** Length of advanced random number in byte. */
#define CSM_HAE_ADVRANDOM_NUM_BYTES                     8U

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (CSM_RANDOM_HAEADVRANDOMSEED == STD_ON)
/* Cry HaeAdvRandom Seed Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores raw data pointer used for HaeAdvRandom Seed */
  const uint8* pSeedPtr;
  /* length of seed data */
  uint32 ulSeedLength;
} Cry_HaeAdvRandomSeedTransferBuffer;
#endif

#if (CSM_RANDOM_HAEADVRANDOMGENERATE == STD_ON)
/* Cry HaeAdvRandom Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Pointer of result */
  uint8* pResultPtr;
  /* Length of result */
  uint32 ulResultLength;
} Cry_HaeAdvRandomGenerateTransferBuffer;
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_RANDOM_HAEADVRANDOMSEED == STD_ON)
/* Structure variable for HaeAdvRandom Seed transfer buffer */
static Cry_HaeAdvRandomSeedTransferBuffer Cry_GddHaeAdvRandomSeedTb;
#endif

#if (CSM_RANDOM_HAEADVRANDOMGENERATE == STD_ON)
/* Structure variable for HaeAdvRandom Generate transfer buffer */
static Cry_HaeAdvRandomGenerateTransferBuffer Cry_GddHaeAdvRandomGenerateTb;
#endif

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_RANDOM_HAEADVRANDOMSEED == STD_ON)
/*******************************************************************************
** Function Name      : Cry_HaeAdvRandomSeedInit                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the transfer buffer of the   **
**                      Random Seed. All module Global variables will         **
**                      be initialized after successful completion of this    **
**                      API.                                                  **
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
** Remarks            : Global Variable(s): Cry_GddHaeAdvRandomSeedTb         **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeAdvRandomSeedInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeAdvRandomSeedTb.ucJobState = NO_JOB;
  Cry_GddHaeAdvRandomSeedTb.pSeedPtr = NULL_PTR;
  Cry_GddHaeAdvRandomSeedTb.ulSeedLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeAdvRandomSeedStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Random Seed, so that it is           **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        configuration provided in the arguments so that     **
**                        Cry_HaeAdvRandomSeedMainFunction() can process      **
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
** Remarks              : Global Variable(s): Cry_GddHaeAdvRandomSeedTb,      **
**                        Function(s) invoked: Cry_HaeAdvRandomSeedInit       **
*******************************************************************************/
Std_ReturnType Cry_HaeAdvRandomSeedStart(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeAdvRandomSeedTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeAdvRandomSeedInit();

    Cry_GddHaeAdvRandomSeedTb.ucJobState = JOB_START;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      Cry_GddHaeAdvRandomSeedTb.ucJobState = JOB_DONE;
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
** Function Name        : Cry_HaeAdvRandomSeedUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the          **
**                        Random Seed                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeAdvRandomSeedMainFunction() can process input**
**                        data                                                **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, seedPtr, seedLength                          **
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
** Remarks              : Global Variable(s): Cry_GddHaeAdvRandomSeedTb       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        ASK_RandInit                                        **
*******************************************************************************/
Std_ReturnType Cry_HaeAdvRandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength)
{
  Std_ReturnType LddReturnValue;
  uint32 LulValue = CSM_ZERO;

  /* Setting the default return value */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeAdvRandomSeedTb.ucJobState)
  {
    Cry_GddHaeAdvRandomSeedTb.ucJobState = JOB_UPDATE;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      if (seedLength != CSM_HAE_ADVRANDOM_SEED_BYTES)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        /* Make big endian uint32 value */
        /* polyspace +5 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        LulValue
          = ((uint32)(seedPtr[CSM_ZERO]) << 24U)
          + ((uint32)(seedPtr[CSM_ONE]) << 16U)
          + ((uint32)(seedPtr[CSM_TWO]) << 8U)
          + (uint32)(seedPtr[CSM_THREE]);

        ASK_RandInit(LulValue);

        Cry_GddHaeAdvRandomSeedTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeAdvRandomSeedTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeAdvRandomSeedTb.pSeedPtr = seedPtr;
      Cry_GddHaeAdvRandomSeedTb.ulSeedLength = seedLength;
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
** Function Name        : Cry_HaeAdvRandomSeedFinish                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function will not be doing any computation.    **
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
**                        CSM_E_BUSY: service state is already "active"       **
**                                                                            **
** Preconditions        : Primitive should have been successfully initialized **
**                                                                            **
** Remarks              : Global Variable(s): Cry_GddHaeAdvRandomSeedTb       **
**                        Function(s) invoked: None                           **
*******************************************************************************/
Std_ReturnType Cry_HaeAdvRandomSeedFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeAdvRandomSeedTb.ucJobState)
  {
    Cry_GddHaeAdvRandomSeedTb.ucJobState = JOB_FINISH;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeAdvRandomSeedTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeAdvRandomSeedMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_RandomSeedCallbackNotification() with correct   **
**                        return value once the main function has completely  **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_HaeAdvRandomSeedStart() or**
**                        Cry_HaeAdvRandomSeedUpdate(). For                   **
**                        Cry_HaeAdvRandomSeedFinish invocation of            **
**                        Csm_RandomSeedCallbackNotification()                **
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
** Preconditions        : Primitive should have been initialized              **
**                                                                            **
** Remarks              : Global Variable(s): Cry_GddHaeAdvRandomSeedTb       **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Csm_RandomSeedCallbackNotification,                 **
**                        ASK_RandInit,                                       **
**                        Csm_RandomSeedServiceFinishNotification             **
*******************************************************************************/
void Cry_HaeAdvRandomSeedMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint32 LulValue = CSM_ZERO;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeAdvRandomSeedTb.ucJobState)
  {
  case JOB_START:
    Cry_GddHaeAdvRandomSeedTb.ucJobState = JOB_DONE;

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    if (Cry_GddHaeAdvRandomSeedTb.ulSeedLength != CSM_HAE_ADVRANDOM_SEED_BYTES)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      /* Make big endian uint32 value */
      /* polyspace +2 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      LulValue
        = ((uint32)(Cry_GddHaeAdvRandomSeedTb.pSeedPtr[CSM_ZERO]) << 24U)
        + ((uint32)(Cry_GddHaeAdvRandomSeedTb.pSeedPtr[CSM_ONE]) << 16U)
        + ((uint32)(Cry_GddHaeAdvRandomSeedTb.pSeedPtr[CSM_TWO]) << 8U)
        + (uint32)(Cry_GddHaeAdvRandomSeedTb.pSeedPtr[CSM_THREE]);

      ASK_RandInit(LulValue);
    }

    Cry_GddHaeAdvRandomSeedTb.ucJobState = JOB_DONE;

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeAdvRandomSeedTb.ucJobState = NO_JOB;

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_RandomSeedServiceFinishNotification();
    break;
  } /* End of switch (Cry_GddHaeAdvRandomSeedTb.ucJobState) */
}
#endif /* (CSM_RANDOM_HAEADVRANDOMSEED == STD_ON) */

#if (CSM_RANDOM_HAEADVRANDOMGENERATE == STD_ON)
/*******************************************************************************
** Function Name      : Cry_HaeAdvRandomGenerateInit                          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the transfer buffer of the   **
**                      Random Generate. All module Global variables          **
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
** Remarks            : Global Variable(s): Cry_GddHaeAdvRandomGenerateTb     **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeAdvRandomGenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeAdvRandomGenerateTb.ucJobState = NO_JOB;
  Cry_GddHaeAdvRandomGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaeAdvRandomGenerateTb.ulResultLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeAdvRandomGenerate                            **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function processes the cryptographic primitive **
**                        with the given input data and store the result in   **
**                        the memory location given.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : cfgPtr, resultLength                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : resultPtr                                           **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy   **
**                        of random number generator is exhausted             **
**                                                                            **
** Preconditions        : Seed should have been generated                     **
**                                                                            **
** Remarks              : Global Variable(s): None                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeAdvRandomGenerateInit, ASK_Rand8ByteGenerate **
*******************************************************************************/
Std_ReturnType Cry_HaeAdvRandomGenerate(const void* cfgPtr, uint8* resultPtr,
  uint32 resultLength)
{
  Std_ReturnType LddReturnValue;
  SEEDKEY_RT LddPrimitiveReturnValue;
  uint8 LucIndex;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeAdvRandomGenerateTb.ucJobState)
  {
    Cry_HaeAdvRandomGenerateInit();

    Cry_GddHaeAdvRandomGenerateTb.ucJobState = JOB_START;

    if (Csm_RandomGenerateServiceHasCallback() == FALSE)
    {
      if ((resultLength % CSM_HAE_ADVRANDOM_NUM_BYTES) != CSM_ZERO)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        /* polyspace +5 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer and length is checked" */
        for (LucIndex = CSM_ZERO;
          LucIndex < (resultLength / CSM_HAE_ADVRANDOM_NUM_BYTES); LucIndex++)
        {
          LddPrimitiveReturnValue = ASK_Rand8ByteGenerate(
            &(resultPtr[CSM_HAE_ADVRANDOM_NUM_BYTES * LucIndex]));

          if (LddPrimitiveReturnValue != SEEDKEY_SUCCESS)
          {
            LddReturnValue = E_NOT_OK;
            break;
          }
        }

        /* Update job state to NO_JOB irrespective of the result */
        Cry_GddHaeAdvRandomGenerateTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeAdvRandomGenerateTb.pResultPtr = resultPtr;
      Cry_GddHaeAdvRandomGenerateTb.ulResultLength = resultLength;
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
** Function Name        : Cry_HaeAdvRandomGenerateMainFunction                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_RandomGenerateCallbackNotification()            **
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
** Preconditions        : Primitive should have been initialized              **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                        Cry_GddHaeAdvRandomGenerateTb                       **
**                                                                            **
**                        Function(s) invoked:                                **
**                        ASK_Rand8ByteGenerate                               **
**                        Csm_RandomGenerateCallbackNotification              **
*******************************************************************************/
void Cry_HaeAdvRandomGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  SEEDKEY_RT LddPrimitiveReturnValue;
  uint8 LucIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  if ((Cry_GddHaeAdvRandomGenerateTb.ulResultLength % CSM_HAE_ADVRANDOM_NUM_BYTES) != CSM_ZERO)
  {
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    for (LucIndex = CSM_ZERO;
      LucIndex < (Cry_GddHaeAdvRandomGenerateTb.ulResultLength
        / CSM_HAE_ADVRANDOM_NUM_BYTES); LucIndex++)
    {
      LddPrimitiveReturnValue = ASK_Rand8ByteGenerate(
        &(Cry_GddHaeAdvRandomGenerateTb.pResultPtr[CSM_HAE_ADVRANDOM_NUM_BYTES * LucIndex]));

      if (LddPrimitiveReturnValue != SEEDKEY_SUCCESS)
      {
        LddReturnValue = E_NOT_OK;
        break;
      }
    }
  }

  /* Update job state to NO_JOB irrespective of the result */
  Cry_GddHaeAdvRandomGenerateTb.ucJobState = NO_JOB;

  /* Callback notification will be invoking the application callback */
  Csm_RandomGenerateCallbackNotification(LddReturnValue);
}
#endif /* (CSM_RANDOM_HAEADVRANDOMGENERATE == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_RANDOM_HAEADVRANDOMSEED) || (CSM_RANDOM_HAEADVRANDOMGENERATE)) */
#endif /* ((CSM_RANDOM_SEED_STATUS == STD_ON) || (CSM_RANDOM_GENERATE_STATUS == STD_ON)) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
