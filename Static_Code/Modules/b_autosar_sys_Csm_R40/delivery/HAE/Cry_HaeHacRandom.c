/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHacRandom.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - Autoever HAC Random                                       **
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
** 1.0.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.2     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.0.1     20-Sep-2017   Sinil        Redmine #10034                        **
** 1.0.0     27-Feb-2017   Sinil        Initial version, Redmine #7651        **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_HaeHacRandomSeed.h"
#include "Cry_HaeHacRandomGenerate.h"
#if ((CSM_RANDOM_SEED_STATUS == STD_ON) || (CSM_RANDOM_GENERATE_STATUS == STD_ON))
#if ((CSM_RANDOM_HAEHACRANDOMSEED) || (CSM_RANDOM_HAEHACRANDOMGENERATE == STD_ON))
#include "Csm_Cbk.h"
#include "Hac_Prng.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (CSM_RANDOM_HAEHACRANDOMSEED == STD_ON)
/* Cry HaeHacRandom Seed Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores raw data pointer used for HaeHacRandom Seed */
  const uint8* pSeedPtr;
  /* length of seed data */
  uint32 ulSeedLength;
} Cry_HaeHacRandomSeedTransferBuffer;
#endif

#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
/* Cry HaeHacRandom Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Pointer of result */
  uint8* pResultPtr;
  /* Length of result */
  uint32 ulResultLength;
} Cry_HaeHacRandomGenerateTransferBuffer;
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if ((CSM_RANDOM_HAEHACRANDOMSEED == STD_ON) || (CSM_RANDOM_HAEHACRANDOMGENERATE == STD_ON))
/* Aut HAC Random primitive library context */
static HacPrngCtx Cry_GddHaeHacRandomContext;
#endif

#if (CSM_RANDOM_HAEHACRANDOMSEED == STD_ON)
/* Structure variable for HaeHacRandom Seed transfer buffer */
static Cry_HaeHacRandomSeedTransferBuffer Cry_GddHaeHacRandomSeedTb;
#endif /* (CSM_RANDOM_HAEHACRANDOMSEED == STD_ON) */

#if (CSM_RANDOM_HAEHACRANDOMGENERATE == STD_ON)
/* Structure variable for HaeHacRandom Generate transfer buffer */
static Cry_HaeHacRandomGenerateTransferBuffer Cry_GddHaeHacRandomGenerateTb;
#endif /* (CSM_RANDOM_HAEHACRANDOMGENERATE == STD_ON) */

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_RANDOM_HAEHACRANDOMSEED == STD_ON)
/*******************************************************************************
** Function Name      : Cry_HaeHacRandomSeedInit                              **
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
** Remarks            : Global Variable(s): Cry_GddHaeHacRandomSeedTb         **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHacRandomSeedInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHacRandomSeedTb.ucJobState = NO_JOB;
  Cry_GddHaeHacRandomSeedTb.pSeedPtr = NULL_PTR;
  Cry_GddHaeHacRandomSeedTb.ulSeedLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeHacRandomSeedStart                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Random Seed, so that it is           **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        configuration provided in the arguments so that     **
**                        Cry_HaeHacRandomSeedMainFunction() can process      **
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
** Remarks              : Global Variable(s): Cry_GddHaeHacRandomSeedTb       **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Cry_HaeHacRandomSeedInit,                           **
**                        Csm_RandomSeedServiceHasCallback, Hac_PrngInit      **
*******************************************************************************/
Std_ReturnType Cry_HaeHacRandomSeedStart(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHacRandomSeedTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaeHacRandomSeedInit();

    Cry_GddHaeHacRandomSeedTb.ucJobState = JOB_START;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      Hac_PrngInit(&Cry_GddHaeHacRandomContext);

      Cry_GddHaeHacRandomSeedTb.ucJobState = JOB_DONE;
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
** Function Name        : Cry_HaeHacRandomSeedUpdate                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the          **
**                        Random Seed                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaeHacRandomSeedMainFunction() can process input**
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
** Remarks              : Global Variable(s): Cry_GddHaeHacRandomSeedTb       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_RandomSeedServiceHasCallback, Hac_PrngReseed    **
*******************************************************************************/
Std_ReturnType Cry_HaeHacRandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength)
{
  Std_ReturnType LddReturnValue;

  /* Setting the default return value */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaeHacRandomSeedTb.ucJobState)
  {
    Cry_GddHaeHacRandomSeedTb.ucJobState = JOB_UPDATE;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      if (seedLength != HAC_ENTROPY_LEN)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Hac_PrngReseed(&Cry_GddHaeHacRandomContext, seedPtr);

        Cry_GddHaeHacRandomSeedTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaeHacRandomSeedTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaeHacRandomSeedTb.pSeedPtr = seedPtr;
      Cry_GddHaeHacRandomSeedTb.ulSeedLength = seedLength;
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
** Function Name        : Cry_HaeHacRandomSeedFinish                          **
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
** Remarks              : Global Variable(s): Cry_GddHaeHacRandomSeedTb       **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Csm_RandomSeedServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_HaeHacRandomSeedFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaeHacRandomSeedTb.ucJobState)
  {
    Cry_GddHaeHacRandomSeedTb.ucJobState = JOB_FINISH;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHacRandomSeedTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaeHacRandomSeedMainFunction                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_RandomSeedCallbackNotification() with correct   **
**                        return value once the main function has completely  **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_HaeHacRandomSeedStart() or**
**                        Cry_HaeHacRandomSeedUpdate(). For                   **
**                        Cry_HaeHacRandomSeedFinish invocation of            **
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
** Remarks              : Global Variable(s): Cry_GddHaeHacRandomSeedTb       **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Hac_PrngInit, Hac_PrngReseed,                       **
**                        Csm_RandomSeedCallbackNotification,                 **
**                        Csm_RandomSeedServiceFinishNotification             **
*******************************************************************************/
void Cry_HaeHacRandomSeedMainFunction(void)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaeHacRandomSeedTb.ucJobState)
  {
  case JOB_START:
    Hac_PrngInit(&Cry_GddHaeHacRandomContext);

    Cry_GddHaeHacRandomSeedTb.ucJobState = JOB_DONE;

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    if (Cry_GddHaeHacRandomSeedTb.ulSeedLength != HAC_ENTROPY_LEN)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Hac_PrngReseed(&Cry_GddHaeHacRandomContext,
        Cry_GddHaeHacRandomSeedTb.pSeedPtr);
    }

    Cry_GddHaeHacRandomSeedTb.ucJobState = JOB_DONE;

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaeHacRandomSeedTb.ucJobState = NO_JOB;

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_DONE:
  case NO_JOB:
  default:
    /* Finish the request by notifying through finish function */
    Csm_RandomSeedServiceFinishNotification();
    break;
  }
}
#endif /* (CSM_RANDOM_HAEHACRANDOMSEED == STD_ON) */

#if (CSM_RANDOM_HAEHACRANDOMGENERATE == STD_ON)
/*******************************************************************************
** Function Name      : Cry_HaeHacRandomGenerateInit                          **
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
** Remarks            : Global Variable(s): Cry_GddHaeHacRandomGenerateTb     **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHacRandomGenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaeHacRandomGenerateTb.ucJobState = NO_JOB;
  Cry_GddHaeHacRandomGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaeHacRandomGenerateTb.ulResultLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeHacRandomGenerate                            **
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
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_HaeHacRandomGenerateInit,                       **
**                        Csm_RandomGenerateServiceHasCallback,               **
**                        Hac_PrngGetRand                                     **
*******************************************************************************/
Std_ReturnType Cry_HaeHacRandomGenerate(const void* cfgPtr, uint8* resultPtr,
  uint32 resultLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHacRandomGenerateTb.ucJobState)
  {
    /* Initializing Random Generate Global variables */
    Cry_HaeHacRandomGenerateInit();

    Cry_GddHaeHacRandomGenerateTb.ucJobState = JOB_START;

    if (Csm_RandomGenerateServiceHasCallback() == FALSE)
    {
      LblReturnValue = Hac_PrngGetRand(&Cry_GddHaeHacRandomContext,
        resultPtr, resultLength);

      switch (LblReturnValue)
      {
      case HAC_INVALID_LENGTH:
        LddReturnValue = CSM_E_SMALL_BUFFER;
        break;
      case HAC_INVALID_VALUE:
        LddReturnValue = CSM_E_ENTROPY_EXHAUSTION;
        break;
      case HAC_FAILURE:
        LddReturnValue = E_NOT_OK;
        break;
      case HAC_SUCCESS:
        LddReturnValue = E_OK;
        break;
      default:
        LddReturnValue = E_NOT_OK;
        break;
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHacRandomGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHacRandomGenerateTb.pResultPtr = resultPtr;
      Cry_GddHaeHacRandomGenerateTb.ulResultLength = resultLength;
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
** Function Name        : Cry_HaeHacRandomGenerateMainFunction                **
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
**                        Cry_GddHaeHacRandomGenerateTb                       **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Hac_PrngGetRand,                                    **
**                        Csm_RandomGenerateCallbackNotification              **
*******************************************************************************/
void Cry_HaeHacRandomGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  LblReturnValue = Hac_PrngGetRand(
      &Cry_GddHaeHacRandomContext,
      Cry_GddHaeHacRandomGenerateTb.pResultPtr,
      Cry_GddHaeHacRandomGenerateTb.ulResultLength);

  switch (LblReturnValue)
  {
  case HAC_INVALID_LENGTH:
    LddReturnValue = CSM_E_SMALL_BUFFER;
    break;
  case HAC_INVALID_VALUE:
    LddReturnValue = CSM_E_ENTROPY_EXHAUSTION;
    break;
  case HAC_FAILURE:
    LddReturnValue = E_NOT_OK;
    break;
  case HAC_SUCCESS:
    LddReturnValue = E_OK;
    break;
  default:
    LddReturnValue = E_NOT_OK;
    break;
  }

  /* Update job state to NO_JOB irrespective of the result */
  Cry_GddHaeHacRandomGenerateTb.ucJobState = NO_JOB;

  /* Callback notification will be invoking the application callback */
  Csm_RandomGenerateCallbackNotification(LddReturnValue);
}
#endif /* (CSM_RANDOM_HAEHACRANDOMGENERATE == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_RANDOM_HAEHACRANDOMSEED) || (CSM_RANDOM_HAEHACRANDOMGENERATE == STD_ON)) */
#endif /* ((CSM_RANDOM_SEED_STATUS == STD_ON) || (CSM_RANDOM_GENERATE_STATUS == STD_ON)) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
