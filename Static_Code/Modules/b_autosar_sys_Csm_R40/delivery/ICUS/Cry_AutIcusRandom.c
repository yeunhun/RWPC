/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutIcusRandom.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - ICUS Random                                               **
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
** 1.0.1     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.0     27-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_AutIcusRandomSeed.h"
#include "Cry_AutIcusRandomGenerate.h"
#if ((CSM_RANDOM_SEED_STATUS == STD_ON) || (CSM_RANDOM_GENERATE_STATUS == STD_ON))
#if ((CSM_RANDOM_AUTICUSRANDOMSEED) || (CSM_RANDOM_AUTICUSRANDOMGENERATE))
#include "Csm_Cbk.h"
#include "Icus_Driver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (CSM_RANDOM_AUTICUSRANDOMGENERATE == STD_ON)
/* Cry AutIcusRandom Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Pointer of result */
  uint8* pResultPtr;
  /* Length of result */
  uint32 ulResultLength;
} Cry_AutIcusRandomGenerateTransferBuffer;
#endif

#if (CSM_RANDOM_AUTICUSRANDOMSEED == STD_ON)
/* Cry AutIcusRandom Seed Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  const uint8* pSeedPtr;
  uint32 ulSeedLength;
} Cry_AutIcusRandomSeedTransferBuffer;
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_RANDOM_AUTICUSRANDOMSEED == STD_ON)
/* Structure variable for AutIcusRandom Seed transfer buffer */
static Cry_AutIcusRandomSeedTransferBuffer Cry_GddAutIcusRandomSeedTb;
#endif

#if (CSM_RANDOM_AUTICUSRANDOMGENERATE == STD_ON)
/* Structure variable for AutIcusRandom Generate transfer buffer */
static Cry_AutIcusRandomGenerateTransferBuffer Cry_GddAutIcusRandomGenerateTb;
#endif

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_RANDOM_AUTICUSRANDOMSEED == STD_ON)
/*******************************************************************************
** Function Name      : Cry_AutIcusRandomSeedInit                             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the transfer buffer of the   **
**                      Autron Random Seed. All module Global variables will  **
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
** Remarks            : Global Variable(s): Cry_GddAutIcusRandomSeedTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutIcusRandomSeedInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutIcusRandomSeedTb.ucJobState = NO_JOB;
  Cry_GddAutIcusRandomSeedTb.pSeedPtr = NULL_PTR;
  Cry_GddAutIcusRandomSeedTb.ulSeedLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutIcusRandomSeedStart                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autron Random Seed, so that it is    **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        configuration provided in the arguments so that     **
**                        Cry_AutIcusRandomSeedMainFunction() can process     **
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
** Remarks              : Global Variable(s): Cry_GddAutIcusRandomSeedTb      **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Cry_AutIcusRandomSeedInit, Icus_InitRnd,            **
**                        Csm_RandomSeedServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_AutIcusRandomSeedStart(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutIcusRandomSeedTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutIcusRandomSeedInit();

    Cry_GddAutIcusRandomSeedTb.ucJobState = JOB_START;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      LddErr = Icus_InitRnd();

      if (LddErr != ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutIcusRandomSeedTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusRandomSeedTb.ucJobState = NO_JOB;
      }
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
** Function Name        : Cry_AutIcusRandomSeedUpdate                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Autron   **
**                        Random Seed                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutIcusRandomSeedMainFunction() can process     **
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
** Remarks              : Global Variable(s): Cry_GddAutIcusRandomSeedTb      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_RandomSeedServiceHasCallback, Icus_ExtendSeed   **
*******************************************************************************/
Std_ReturnType Cry_AutIcusRandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength)
{
  Std_ReturnType LddReturnValue;
  uint32 LulSeed, LulIndex;
  Icus_ErrType LddErr;

  /* Setting the default return value */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutIcusRandomSeedTb.ucJobState)
  {
    Cry_GddAutIcusRandomSeedTb.ucJobState = JOB_UPDATE;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      if (seedLength != ICUS_RND_SEED_BYTE_LENGTH)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LulSeed = CSM_ZERO;
        for (LulIndex = CSM_ZERO; LulIndex < ICUS_RND_SEED_BYTE_LENGTH; LulIndex++)
        {
          /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          LulSeed += (uint32)(seedPtr[LulIndex]) << (LulIndex * CSM_EIGHT);
        }

        LddErr = Icus_ExtendSeed(LulSeed);

        if (LddErr != ERC_NO_ERROR)
        {
          LddReturnValue = E_NOT_OK;
        }
      }

      if (LddReturnValue == E_OK)
      {
        Cry_GddAutIcusRandomSeedTb.ucJobState = JOB_DONE;
      }
      else
      {
        Cry_GddAutIcusRandomSeedTb.ucJobState = NO_JOB;
      }
    }
    else
    {
      Cry_GddAutIcusRandomSeedTb.pSeedPtr = seedPtr;
      Cry_GddAutIcusRandomSeedTb.ulSeedLength = seedLength;
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
** Function Name        : Cry_AutIcusRandomSeedFinish                         **
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
** Remarks              : Global Variable(s): Cry_GddAutIcusRandomSeedTb      **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Csm_RandomSeedServiceHasCallback                    **
*******************************************************************************/
Std_ReturnType Cry_AutIcusRandomSeedFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutIcusRandomSeedTb.ucJobState)
  {
    Cry_GddAutIcusRandomSeedTb.ucJobState = JOB_FINISH;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutIcusRandomSeedTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutIcusRandomSeedMainFunction                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_RandomSeedCallbackNotification() with correct   **
**                        return value once the main function has completely  **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_AutIcusRandomSeedStart()  **
**                        or Cry_AutIcusRandomSeedUpdate(). For               **
**                        Cry_AutIcusRandomSeedFinish invocation of           **
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
** Remarks              : Global Variable(s): Cry_GddAutIcusRandomSeedTb      **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Csm_RandomSeedCallbackNotification,                 **
**                        Icus_InitRnd, Icus_ExtendSeed                       **
**                        Csm_RandomSeedServiceFinishNotification             **
*******************************************************************************/
void Cry_AutIcusRandomSeedMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Icus_ErrType LddErr;
  uint32 LulSeed, LulIndex;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of AutIcusRandom job processing */
  switch (Cry_GddAutIcusRandomSeedTb.ucJobState)
  {
  case JOB_START:
    LddErr = Icus_InitRnd();

    if (LddErr != ERC_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusRandomSeedTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusRandomSeedTb.ucJobState = NO_JOB;
    }

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    if (Cry_GddAutIcusRandomSeedTb.ulSeedLength != ICUS_RND_SEED_BYTE_LENGTH)
    {
      LddReturnValue = E_NOT_OK;
    }

    if (LddReturnValue == E_OK)
    {
      LulSeed = CSM_ZERO;
      for (LulIndex = CSM_ZERO; LulIndex < ICUS_RND_SEED_BYTE_LENGTH; LulIndex++)
      {
        /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        LulSeed += (uint32)(Cry_GddAutIcusRandomSeedTb.pSeedPtr[LulIndex])
          << (LulIndex * CSM_EIGHT);
      }

      LddErr = Icus_ExtendSeed(LulSeed);

      if (LddErr != ERC_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }
    }

    if (LddReturnValue == E_OK)
    {
      Cry_GddAutIcusRandomSeedTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutIcusRandomSeedTb.ucJobState = NO_JOB;
    }

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutIcusRandomSeedTb.ucJobState = NO_JOB;

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
#endif

#if (CSM_RANDOM_AUTICUSRANDOMGENERATE == STD_ON)
/*******************************************************************************
** Function Name      : Cry_AutIcusRandomGenerateInit                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the transfer buffer of the   **
**                      Autron Random Generate. All module Global variables   **
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
** Remarks            : Global Variable(s): Cry_GddAutIcusRandomGenerateTb    **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutIcusRandomGenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutIcusRandomGenerateTb.ucJobState = NO_JOB;
  Cry_GddAutIcusRandomGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddAutIcusRandomGenerateTb.ulResultLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutIcusRandomGenerate                           **
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
**                        Cry_AutIcusRandomGenerateInit,                      **
**                        Csm_RandomGenerateServiceHasCallback, Icus_Rnd      **
*******************************************************************************/
Std_ReturnType Cry_AutIcusRandomGenerate(const void* cfgPtr, uint8* resultPtr,
  uint32 resultLength)
{
  Std_ReturnType LddReturnValue;
  uint32 LulIndex, LulRnd;
  Icus_ErrType LddErr;
  uint32 LuResultLength;
  uint8* LddResultPtr;

  /* Setting Default return value */
  LddReturnValue = E_OK;
  LuResultLength = resultLength;
  LddResultPtr = resultPtr;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutIcusRandomGenerateTb.ucJobState)
  {
    Cry_AutIcusRandomGenerateInit();

    Cry_GddAutIcusRandomGenerateTb.ucJobState = JOB_START;

    if (Csm_RandomGenerateServiceHasCallback() == FALSE)
    {
      do
      {
        LulRnd = 0u;
        LddErr = Icus_Rnd(&LulRnd);

        if (LddErr == ERC_NO_ERROR)
        {
          if (LuResultLength >= ICUS_RND_GEN_BYTE_LENGTH)
          {
            /* polyspace-begin MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            LddResultPtr[CSM_ZERO] = (uint8)((LulRnd & ((uint32)0xFFU << 24U)) >> 24U) & (uint8)0xFFU;
            LddResultPtr[CSM_ONE] = (uint8)((LulRnd & ((uint32)0xFFU << 16U)) >> 16U) & (uint8)0xFFU;
            LddResultPtr[CSM_TWO] = (uint8)((LulRnd & ((uint32)0xFFU << 8U)) >> 8U) & (uint8)0xFFU;
            LddResultPtr[CSM_THREE] = (uint8)LulRnd & (uint8)0xFFU;

            LddResultPtr = &LddResultPtr[ICUS_RND_GEN_BYTE_LENGTH];
            LuResultLength -= ICUS_RND_GEN_BYTE_LENGTH;
          }
          else
          {
            for (LulIndex = CSM_ZERO; LulIndex < LuResultLength; LulIndex++)
            {
              LddResultPtr[LulIndex] =
                (uint8)((LulRnd >> (CSM_EIGHT*(sizeof(LulRnd)
                - LulIndex - CSM_ONE))) & CSM_BYTE_MASK);
            }
            LuResultLength = CSM_ZERO;
            /* polyspace-end MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
          break;
        }
      } while (LuResultLength > CSM_ZERO);

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutIcusRandomGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutIcusRandomGenerateTb.pResultPtr = LddResultPtr;
      Cry_GddAutIcusRandomGenerateTb.ulResultLength = LuResultLength;
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
** Function Name        : Cry_AutIcusRandomGenerateMainFunction               **
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
**                        Cry_GddAutIcusRandomGenerateTb                      **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Icus_Rnd, Csm_RandomGenerateCallbackNotification
*******************************************************************************/
void Cry_AutIcusRandomGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint32 LulIndex, LulRnd;
  Icus_ErrType LddErr;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  do
  {
    LulRnd = 0u;
    LddErr = Icus_Rnd(&LulRnd);

    if (LddErr == ERC_NO_ERROR)
    {
      if (Cry_GddAutIcusRandomGenerateTb.ulResultLength >= ICUS_RND_GEN_BYTE_LENGTH)
      {
        /* polyspace-begin MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
        Cry_GddAutIcusRandomGenerateTb.pResultPtr[CSM_ZERO]
          = (uint8)((LulRnd & ((uint32)0xFFU << 24U)) >> 24U) & (uint8)0xFFU;
        Cry_GddAutIcusRandomGenerateTb.pResultPtr[CSM_ONE]
          = (uint8)((LulRnd & ((uint32)0xFFU << 16U)) >> 16U) & (uint8)0xFFU;
        Cry_GddAutIcusRandomGenerateTb.pResultPtr[CSM_TWO]
          = (uint8)((LulRnd & ((uint32)0xFFU << 8U)) >> 8U) & (uint8)0xFFU;
        Cry_GddAutIcusRandomGenerateTb.pResultPtr[CSM_THREE]
          = (uint8)LulRnd & (uint8)0xFFU;

        Cry_GddAutIcusRandomGenerateTb.pResultPtr
          = &(Cry_GddAutIcusRandomGenerateTb.pResultPtr[ICUS_RND_GEN_BYTE_LENGTH]);
        Cry_GddAutIcusRandomGenerateTb.ulResultLength -= ICUS_RND_GEN_BYTE_LENGTH;
        /* polyspace-end MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
      }
      else
      {
        for (LulIndex = CSM_ZERO;
          LulIndex < Cry_GddAutIcusRandomGenerateTb.ulResultLength; LulIndex++)
        {
          /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
          Cry_GddAutIcusRandomGenerateTb.pResultPtr[LulIndex] =
            (uint8)((LulRnd >> (CSM_EIGHT*(sizeof(LulRnd)
            - LulIndex - CSM_ONE))) & CSM_BYTE_MASK);
        }
        Cry_GddAutIcusRandomGenerateTb.ulResultLength = CSM_ZERO;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
      break;
    }
  } while (Cry_GddAutIcusRandomGenerateTb.ulResultLength > CSM_ZERO);

  /* Update job state to NO_JOB irrespective of the result */
  Cry_GddAutIcusRandomGenerateTb.ucJobState = NO_JOB;

  /* Callback notification will be invoking the application callback */
  Csm_RandomGenerateCallbackNotification(LddReturnValue);
}
#endif

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif
#endif

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
