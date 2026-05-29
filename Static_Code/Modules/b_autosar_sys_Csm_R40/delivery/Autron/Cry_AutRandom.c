/*******************************************************************************
**                                                                            **
**  (C) 2015~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutRandom.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - Autron Random                                             **
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
** 1.0.9     09-Aug-2016   Sinil        Redmine #5693, #5540                  **
** 1.0.8     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.7     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.6     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.5     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.4     02-May-2016   Sinil        Redmine #4607                         **
** 1.0.3     05-Jan-2016   Sinil        Use const macro                       **
** 1.0.2     29-Dec-2015   Sinil        Random number assignment changed      **
** 1.0.1     02-Dec-2015   Sinil        Memory section changed                **
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
/* Header File for Autron Random */
#include "Cry_AutRandomSeed.h"
#include "Cry_AutRandomGenerate.h"
/* Random Interface */
#if ((CSM_RANDOM_SEED_STATUS == STD_ON) || (CSM_RANDOM_GENERATE_STATUS == STD_ON))
#if ((CSM_RANDOM_AUTRANDOMSEED == STD_ON) || (CSM_RANDOM_AUTRANDOMGENERATE == STD_ON))
#include "Csm_Cbk.h"
#include "AutRandom.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (CSM_RANDOM_AUTRANDOMSEED == STD_ON)
/* Cry AutRandom Seed Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Stores raw data pointer used for Autron Random Seed */
  const uint8* pSeedPtr;
  /* length of seed data */
  uint32 ulSeedLength;
} Cry_AutRandomSeedTransferBuffer;
#endif

#if (CSM_RANDOM_AUTRANDOMGENERATE == STD_ON)
/* Cry AutRandom Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Pointer of result */
  uint8* pResultPtr;
  /* Length of result */
  uint32 ulResultLength;
} Cry_AutRandomGenerateTransferBuffer;
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (CSM_RANDOM_AUTRANDOMSEED == STD_ON)

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Structure variable for AutRandom Seed transfer buffer */
static Cry_AutRandomSeedTransferBuffer Cry_GddAutRandomSeedTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif

#if (CSM_RANDOM_AUTRANDOMGENERATE == STD_ON)

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Structure variable for AutRandom Generate transfer buffer */
static Cry_AutRandomGenerateTransferBuffer Cry_GddAutRandomGenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* AutRandom value */
static uint32 Cry_GulAutRandomValue;

#define CSM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_RANDOM_AUTRANDOMSEED == STD_ON)
/*******************************************************************************
** Function Name      : Cry_AutRandomSeedInit                                 **
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
** Remarks            : Global Variable(s): Cry_GddAutRandomSeedTb            **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutRandomSeedInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutRandomSeedTb.ucJobState = NO_JOB;
  Cry_GddAutRandomSeedTb.pSeedPtr = NULL_PTR;
  Cry_GddAutRandomSeedTb.ulSeedLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutRandomSeedStart                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function initializes the          **
**                        computation of Autron Random Seed, so that it is    **
**                        able to process the input data                      **
**                        Asynchronous: This function shall store the         **
**                        configuration provided in the arguments so that     **
**                        Cry_AutRandomSeedMainFunction() can process         **
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
** Remarks              : Global Variable(s): Cry_GddAutRandomSeedTb,         **
**                        Function(s) invoked:                                **
**                        Cry_AutRandomSeedInit                               **
*******************************************************************************/
Std_ReturnType Cry_AutRandomSeedStart(const void* cfgPtr)
{
  Std_ReturnType LddReturnValue;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutRandomSeedTb.ucJobState)
  {
    /* Init all the module variables with default values */
    Cry_AutRandomSeedInit();

    Cry_GddAutRandomSeedTb.ucJobState = JOB_START;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      Cry_GddAutRandomSeedTb.ucJobState = JOB_DONE;
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
** Function Name        : Cry_AutRandomSeedUpdate                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Synchronous: This function shall process a chunk of **
**                        the input data fed to the algorithm of the Autron   **
**                        Random Seed                                         **
**                        Asynchronous: This function shall store the         **
**                        information given in the arguments, so that         **
**                        Cry_AutRandomSeedMainFunction() can process input   **
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
** Remarks              : Global Variable(s): Cry_GddAutRandomSeedTb,         **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
Std_ReturnType Cry_AutRandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength)
{
  Std_ReturnType LddReturnValue;

  /* Setting the default return value */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the start is already complete & the module is ready to update */
  if (JOB_DONE == Cry_GddAutRandomSeedTb.ucJobState)
  {
    /* Set the job state to JOB_UPDATE */
    Cry_GddAutRandomSeedTb.ucJobState = JOB_UPDATE;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      Cry_GddAutRandomSeedTb.ucJobState = JOB_DONE;
    }
    else
    {
      Cry_GddAutRandomSeedTb.pSeedPtr = seedPtr;
      Cry_GddAutRandomSeedTb.ulSeedLength = seedLength;
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
** Function Name        : Cry_AutRandomSeedFinish                             **
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
** Remarks              : Global Variable(s): Cry_GddAutRandomSeedTb          **
**                        Function(s) invoked: None                           **
*******************************************************************************/
Std_ReturnType Cry_AutRandomSeedFinish(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* cfgId is unused */
  CSM_PARAM_UNUSED(cfgId);

  /* Check if the update is already complete & the module is ready to finish */
  if (JOB_DONE == Cry_GddAutRandomSeedTb.ucJobState)
  {
    Cry_GddAutRandomSeedTb.ucJobState = JOB_FINISH;

    if (Csm_RandomSeedServiceHasCallback() == FALSE)
    {
      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutRandomSeedTb.ucJobState = NO_JOB;
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
** Function Name        : Cry_AutRandomSeedMainFunction                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It will do the computation based on the             **
**                        cryptographic functions. It will call callback      **
**                        Csm_RandomSeedCallbackNotification() with correct   **
**                        return value once the main function has completely  **
**                        processed the cryptographic                         **
**                        functions demanded by Cry_AutRandomSeedStart() or   **
**                        Cry_AutRandomSeedUpdate(). For                      **
**                        Cry_AutRandomSeedFinish invocation of               **
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
** Remarks              : Global Variable(s): Cry_GddAutRandomSeedTb          **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Csm_RandomSeedCallbackNotification,                 **
**                        Csm_RandomSeedServiceFinishNotification             **
*******************************************************************************/
void Cry_AutRandomSeedMainFunction(void)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* State machine of AutRandom job processing */
  switch (Cry_GddAutRandomSeedTb.ucJobState)
  {
  case JOB_START:
    Cry_GddAutRandomSeedTb.ucJobState = JOB_DONE;

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_UPDATE:
    Cry_GddAutRandomSeedTb.ucJobState = JOB_DONE;

    /* Callback notification will be invoking the application callback */
    Csm_RandomSeedCallbackNotification(LddReturnValue);
    break;

  case JOB_FINISH:
    /* Update job state to NO_JOB irrespective of the result */
    Cry_GddAutRandomSeedTb.ucJobState = NO_JOB;

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
#endif /* (CSM_RANDOM_AUTRANDOMSEED == STD_ON) */

#if (CSM_RANDOM_AUTRANDOMGENERATE == STD_ON)
/*******************************************************************************
** Function Name      : Cry_AutRandomGenerateInit                             **
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
** Remarks            : Global Variable(s): Cry_GddAutRandomGenerateTb        **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutRandomGenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutRandomGenerateTb.ucJobState = NO_JOB;
  Cry_GddAutRandomGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddAutRandomGenerateTb.ulResultLength = CSM_ZERO;

  Cry_GulAutRandomValue = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutRandomGenerate                               **
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
** Remarks              : Global Variable(s): Cry_GddAutRandomGenerateTb      **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Cry_AutRandomGenerateInit,                          **
**                        AutRandom_Generate                                  **
*******************************************************************************/
Std_ReturnType Cry_AutRandomGenerate(const void* cfgPtr, uint8* resultPtr,
  uint32 resultLength)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LucIndex;
  uint32 LulValue;
  uint8* LpResult;
  uint32 LulResultLength;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutRandomGenerateTb.ucJobState)
  {
    Cry_AutRandomGenerateInit();

    Cry_GddAutRandomGenerateTb.ucJobState = JOB_START;

    if (Csm_RandomGenerateServiceHasCallback() == FALSE)
    {
      LpResult = resultPtr;
      LulResultLength = resultLength;
      do
      {
        LblReturnValue = AutRandom_Generate(&Cry_GulAutRandomValue,
          Csm_GulAutRandomSeedAddr);

        if (LblReturnValue == CSM_TRUE)
        {
          LulValue = Cry_GulAutRandomValue;

          if (LulResultLength >= Aut_Random_LEN)
          {
	          /* polyspace +1 MISRA-C3:18.1,D4.1,D4.14 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
            LpResult[CSM_ZERO] = (uint8)((LulValue & ((uint32)0xFFU << 24U)) >> 24U) & (uint8)0xFFU;
            LpResult[CSM_ONE] = (uint8)((LulValue & ((uint32)0xFFU << 16U)) >> 16U) & (uint8)0xFFU;
            LpResult[CSM_TWO] = (uint8)((LulValue & ((uint32)0xFFU << 8U)) >> 8U) & (uint8)0xFFU;
            /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
            LpResult[CSM_THREE] = (uint8)LulValue & (uint8)0xFFU;

            LpResult = &(LpResult[Aut_Random_LEN]);
            LulResultLength -= Aut_Random_LEN;
          }
          else
          {
            if (LulResultLength > CSM_ZERO)
            {
              for (LucIndex = CSM_ZERO; LucIndex < LulResultLength; LucIndex++)
              {
                /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
                LpResult[LucIndex] =
                  (uint8)((LulValue >> (CSM_EIGHT*(sizeof(LulValue)
                  - LucIndex - CSM_ONE))) & CSM_BYTE_MASK);
              }
            }
            LulResultLength = CSM_ZERO;
          }
        }
        else
        {
          LddReturnValue = E_NOT_OK;
          break;
        }
      } while (LulResultLength > CSM_ZERO);

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddAutRandomGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutRandomGenerateTb.pResultPtr = resultPtr;
      Cry_GddAutRandomGenerateTb.ulResultLength = resultLength;
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
** Function Name        : Cry_AutRandomGenerateMainFunction                   **
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
**                        Cry_GddAutRandomGenerateTb                          **
**                                                                            **
**                        Function(s) invoked:                                **
**                        AutRandom_Generate,                                 **
**                        Csm_RandomGenerateCallbackNotification              **
*******************************************************************************/
void Cry_AutRandomGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  boolean LblReturnValue;
  uint8 LucIndex;
  uint32 LulValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  do
  {
    LblReturnValue = AutRandom_Generate(&Cry_GulAutRandomValue,
      Csm_GulAutRandomSeedAddr);

    if (LblReturnValue == CSM_TRUE)
    {
      LulValue = Cry_GulAutRandomValue;
      /* polyspace-begin RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      /* polyspace-begin MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
      if (Cry_GddAutRandomGenerateTb.ulResultLength >= Aut_Random_LEN)
      {
        Cry_GddAutRandomGenerateTb.pResultPtr[CSM_ZERO]
          = (uint8)((LulValue & ((uint32)0xFFU << 24U)) >> 24U) & (uint8)0xFFU;
        Cry_GddAutRandomGenerateTb.pResultPtr[CSM_ONE]
          = (uint8)((LulValue & ((uint32)0xFFU << 16U)) >> 16U) & (uint8)0xFFU;
        Cry_GddAutRandomGenerateTb.pResultPtr[CSM_TWO]
          = (uint8)((LulValue & ((uint32)0xFFU << 8U)) >> 8U) & (uint8)0xFFU;
        Cry_GddAutRandomGenerateTb.pResultPtr[CSM_THREE]
          = (uint8)LulValue & (uint8)0xFFU;
        /* polyspace-end MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
        Cry_GddAutRandomGenerateTb.pResultPtr =
          &(Cry_GddAutRandomGenerateTb.pResultPtr[Aut_Random_LEN]);
        Cry_GddAutRandomGenerateTb.ulResultLength -= Aut_Random_LEN;
      }
      else
      {
        for (LucIndex = CSM_ZERO;
          LucIndex < Cry_GddAutRandomGenerateTb.ulResultLength; LucIndex++)
        {
	        /* polyspace +3 MISRA-C3:18.1,D4.1 RTE:IDP [Justified:Low] "No Impact of this rule violation" */
          Cry_GddAutRandomGenerateTb.pResultPtr[LucIndex]
            = (uint8)((LulValue >> (CSM_EIGHT*(sizeof(LulValue)
            - LucIndex - CSM_ONE))) & CSM_BYTE_MASK);
        }
        Cry_GddAutRandomGenerateTb.ulResultLength = CSM_ZERO;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
      break;
    }
  } while (Cry_GddAutRandomGenerateTb.ulResultLength > CSM_ZERO);

  /* Update job state to NO_JOB irrespective of the result */
  Cry_GddAutRandomGenerateTb.ucJobState = NO_JOB;

  /* Callback notification will be invoking the application callback */
  Csm_RandomGenerateCallbackNotification(LddReturnValue);
}
#endif /* (CSM_RANDOM_AUTRANDOMGENERATE == STATUS_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_RANDOM_AUTRANDOMSEED == STD_ON) || (CSM_RANDOM_AUTRANDOMGENERATE == STD_ON)) */
#endif /* ((CSM_RANDOM_SEED_STATUS == STD_ON) || (CSM_RANDOM_GENERATE_STATUS == STD_ON)) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:2.1,14.3 [Justified:Low] "No Impact of this rule violation" */
/* polyspace-end RTE:IDP [Justified:Low] "No Impact of this rule violation" */
/* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "This condition is covered by configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
