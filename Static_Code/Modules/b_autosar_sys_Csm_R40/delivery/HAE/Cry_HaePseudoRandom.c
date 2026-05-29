/*******************************************************************************
**                                                                            **
**  (C) 2018~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaePseudoRandom.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - Autoever Pseudo Random                                    **
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
** 1.0.1     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.0     07-Nov-2018   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_HaePseudoRandomSeed.h"
#include "Cry_HaePseudoRandomGenerate.h"
#if ((CSM_RANDOM_SEED_STATUS == STD_ON) || (CSM_RANDOM_GENERATE_STATUS == STD_ON))
#if ((CSM_RANDOM_HAEPSEUDORANDOMSEED) || (CSM_RANDOM_HAEPSEUDORANDOMGENERATE == STD_ON))
#include "Csm_Cbk.h"
#include "Hmg_Prng.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON)
/* Cry HaePseudoRandom Seed Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores raw data pointer used for HaePseudoRandom Seed */
  const uint8* pSeedPtr;
  /* length of seed data */
  uint32 ulSeedLength;
} Cry_HaePseudoRandomSeedTransferBuffer;
#endif

#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
/* Cry HaePseudoRandom Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Pointer of result */
  uint8* pResultPtr;
  /* Length of result */
  uint32 ulResultLength;
} Cry_HaePseudoRandomGenerateTransferBuffer;
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if ((CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON) || (CSM_RANDOM_HAEPSEUDORANDOMGENERATE == STD_ON))
/* Hae Pseudo Random primitive library context */
static HmgPrngCtx Cry_GddHaePseudoRandomContext;
#endif

#if (CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON)
/* Structure variable for HaePseudoRandom Seed transfer buffer */
static Cry_HaePseudoRandomSeedTransferBuffer Cry_GddHaePseudoRandomSeedTb;
#endif /* (CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON) */

#if (CSM_RANDOM_HAEPSEUDORANDOMGENERATE == STD_ON)
/* Structure variable for HaePseudoRandom Generate transfer buffer */
static Cry_HaePseudoRandomGenerateTransferBuffer Cry_GddHaePseudoRandomGenerateTb;
#endif /* (CSM_RANDOM_HAEPSEUDORANDOMGENERATE == STD_ON) */

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON)
/*******************************************************************************
** Function Name      : Cry_HaePseudoRandomSeedInit                           **
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
** Remarks            : Global Variable(s): Cry_GddHaePseudoRandomSeedTb      **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaePseudoRandomSeedInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaePseudoRandomSeedTb.ucJobState = NO_JOB;
  Cry_GddHaePseudoRandomSeedTb.pSeedPtr = NULL_PTR;
  Cry_GddHaePseudoRandomSeedTb.ulSeedLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaePseudoRandomSeedStart                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Random Seed, so that it is           **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        configuration provided in the arguments so that     **
**                        Cry_HaePseudoRandomSeedMainFunction() can process   **
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
** Remarks              : Global Variable(s): Cry_GddHaePseudoRandomSeedTb    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Cry_HaePseudoRandomSeedInit,                        **
**                        Csm_RandomSeedServiceHasCallback, Hmg_PrngInit      **
*******************************************************************************/
Std_ReturnType Cry_HaePseudoRandomSeedStart(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaePseudoRandomSeedTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_HaePseudoRandomSeedInit();

    Cry_GddHaePseudoRandomSeedTb.ucJobState = JOB_START;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      Hmg_PrngInit(&Cry_GddHaePseudoRandomContext);

      Cry_GddHaePseudoRandomSeedTb.ucJobState = JOB_DONE;
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
** Function Name        : Cry_HaePseudoRandomSeedUpdate                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the          **
**                        Random Seed                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_HaePseudoRandomSeedMainFunction() can process   **
**                        input data                                          **
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
** Remarks              : Global Variable(s): Cry_GddHaePseudoRandomSeedTb    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_RandomSeedServiceHasCallback, Hmg_PrngReseed    **
*******************************************************************************/
Std_ReturnType Cry_HaePseudoRandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength)
{
  Std_ReturnType LddReturnValue;

  /* Setting the default return value */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddHaePseudoRandomSeedTb.ucJobState)
  {
    Cry_GddHaePseudoRandomSeedTb.ucJobState = JOB_UPDATE;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      if (seedLength != HMG_ENTROPY_LEN)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Hmg_PrngReseed(&Cry_GddHaePseudoRandomContext, seedPtr);

        Cry_GddHaePseudoRandomSeedTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddHaePseudoRandomSeedTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddHaePseudoRandomSeedTb.pSeedPtr = seedPtr;
      Cry_GddHaePseudoRandomSeedTb.ulSeedLength = seedLength;
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
** Function Name        : Cry_HaePseudoRandomSeedFinish                       **
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
** Remarks              : Global Variable(s): Cry_GddHaePseudoRandomSeedTb    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Csm_RandomSeedServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_HaePseudoRandomSeedFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddHaePseudoRandomSeedTb.ucJobState)
  {
    Cry_GddHaePseudoRandomSeedTb.ucJobState = JOB_FINISH;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaePseudoRandomSeedTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_HaePseudoRandomSeedMainFunction                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_RandomSeedCallbackNotification() with correct   **
**                        return value once the main function has completely  **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_HaePseudoRandomSeedStart()**
**                        or Cry_HaePseudoRandomSeedUpdate(). For             **
**                        Cry_HaePseudoRandomSeedFinish invocation of         **
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
** Remarks              : Global Variable(s): Cry_GddHaePseudoRandomSeedTb    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Hmg_PrngInit, Hmg_PrngReseed,                       **
**                        Csm_RandomSeedCallbackNotification,                 **
**                        Csm_RandomSeedServiceFinishNotification             **
*******************************************************************************/
void Cry_HaePseudoRandomSeedMainFunction(void)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  switch (Cry_GddHaePseudoRandomSeedTb.ucJobState)
  {
  case JOB_START:
    Hmg_PrngInit(&Cry_GddHaePseudoRandomContext);

    Cry_GddHaePseudoRandomSeedTb.ucJobState = JOB_DONE;

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    if (Cry_GddHaePseudoRandomSeedTb.ulSeedLength != HMG_ENTROPY_LEN)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Hmg_PrngReseed(&Cry_GddHaePseudoRandomContext,
        Cry_GddHaePseudoRandomSeedTb.pSeedPtr);
    }

    Cry_GddHaePseudoRandomSeedTb.ucJobState = JOB_DONE;

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddHaePseudoRandomSeedTb.ucJobState = NO_JOB;

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
#endif /* (CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON) */

#if (CSM_RANDOM_HAEPSEUDORANDOMGENERATE == STD_ON)
/*******************************************************************************
** Function Name      : Cry_HaePseudoRandomGenerateInit                       **
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
** Remarks            : Global Variable(s): Cry_GddHaePseudoRandomGenerateTb  **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaePseudoRandomGenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddHaePseudoRandomGenerateTb.ucJobState = NO_JOB;
  Cry_GddHaePseudoRandomGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaePseudoRandomGenerateTb.ulResultLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaePseudoRandomGenerate                         **
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
**                        Cry_HaePseudoRandomGenerateInit,                    **
**                        Csm_RandomGenerateServiceHasCallback,               **
**                        Hmg_PrngGetRand                                     **
*******************************************************************************/
Std_ReturnType Cry_HaePseudoRandomGenerate(const void* cfgPtr, uint8* resultPtr,
  uint32 resultLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaePseudoRandomGenerateTb.ucJobState)
  {
    /* Initializing Random Generate Global variables */
    Cry_HaePseudoRandomGenerateInit();

    Cry_GddHaePseudoRandomGenerateTb.ucJobState = JOB_START;

    if (Csm_RandomGenerateServiceHasCallback() == FALSE)
    {
      LblReturnValue = Hmg_PrngGetRand(&Cry_GddHaePseudoRandomContext,
        resultPtr, resultLength);

      switch (LblReturnValue)
      {
      case HMG_INVALID_LENGTH:
        LddReturnValue = CSM_E_SMALL_BUFFER;
        break;
      case HMG_INVALID_VALUE:
        LddReturnValue = CSM_E_ENTROPY_EXHAUSTION;
        break;
      case HMG_FAILURE:
        LddReturnValue = E_NOT_OK;
        break;
      case HMG_SUCCESS:
        LddReturnValue = E_OK;
        break;
      default:
        LddReturnValue = E_NOT_OK;
        break;
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaePseudoRandomGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaePseudoRandomGenerateTb.pResultPtr = resultPtr;
      Cry_GddHaePseudoRandomGenerateTb.ulResultLength = resultLength;
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
** Function Name        : Cry_HaePseudoRandomGenerateMainFunction             **
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
**                        Cry_GddHaePseudoRandomGenerateTb                    **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Hmg_PrngGetRand,                                 **
**                        Csm_RandomGenerateCallbackNotification              **
*******************************************************************************/
void Cry_HaePseudoRandomGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;

  LblReturnValue = Hmg_PrngGetRand(
      &Cry_GddHaePseudoRandomContext,
      Cry_GddHaePseudoRandomGenerateTb.pResultPtr,
      Cry_GddHaePseudoRandomGenerateTb.ulResultLength);

  switch (LblReturnValue)
  {
  case HMG_INVALID_LENGTH:
    LddReturnValue = CSM_E_SMALL_BUFFER;
    break;
  case HMG_INVALID_VALUE:
    LddReturnValue = CSM_E_ENTROPY_EXHAUSTION;
    break;
  case HMG_FAILURE:
    LddReturnValue = E_NOT_OK;
    break;
  case HMG_SUCCESS:
    LddReturnValue = E_OK;
    break;
  default:
    LddReturnValue = E_NOT_OK;
    break;
  }

  /* Update job state to NO_JOB irrespective of the result */
  Cry_GddHaePseudoRandomGenerateTb.ucJobState = NO_JOB;

  /* Callback notification will be invoking the application callback */
  Csm_RandomGenerateCallbackNotification(LddReturnValue);
}
#endif /* (CSM_RANDOM_HAEPSEUDORANDOMGENERATE == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_RANDOM_HAEPSEUDORANDOMSEED) || (CSM_RANDOM_HAEPSEUDORANDOMGENERATE == STD_ON)) */
#endif /* ((CSM_RANDOM_SEED_STATUS == STD_ON) || (CSM_RANDOM_GENERATE_STATUS == STD_ON)) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
