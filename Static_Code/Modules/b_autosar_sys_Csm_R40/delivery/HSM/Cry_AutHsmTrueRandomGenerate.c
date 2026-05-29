/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmTrueRandomGenerate.c                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - HSM True Random Generate                                  **
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
** 1.0.3     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.1     19-Mar-2018   Sinil        Redmine #11930                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_AutHsmTrueRandomGenerate.h"
#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
#if (CSM_RANDOM_AUTHSMTRUERANDOMGENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSM True Random Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  uint8* pResultPtr;
  uint32 ulResultLength;
} Cry_AutHsmTrueRandomGenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Structure variable for HSMRandom Generate transfer buffer */
static Cry_AutHsmTrueRandomGenerateTransferBuffer Cry_GddAutHsmTrueRandomGenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmTrueRandomGenerateCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmTrueRandomGenerateInit                      **
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
** Remarks            : Global Variable(s):                                   **
**                      Cry_GddAutHsmTrueRandomGenerateTb                     **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmTrueRandomGenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmTrueRandomGenerateTb.ucJobState = NO_JOB;
  Cry_GddAutHsmTrueRandomGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddAutHsmTrueRandomGenerateTb.ulResultLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmTrueRandomGenerate                        **
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
**                        Cry_AutHsmTrueRandomGenerateInit,                   **
**                        Csm_RandomGenerateServiceHasCallback, Hsm_TrngGen   **
*******************************************************************************/
Std_ReturnType Cry_AutHsmTrueRandomGenerate(const void* cfgPtr, uint8* resultPtr,
  uint32 resultLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutHsmTrueRandomGenerateTb.ucJobState)
  {
    /* Initializing Autron Random Generate Global variables */
    Cry_AutHsmTrueRandomGenerateInit();

    /* Set the job state to JOB_GENERATE */
    Cry_GddAutHsmTrueRandomGenerateTb.ucJobState = JOB_START;

    LblAsync = Csm_RandomGenerateServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_TrngGen(LblAsync, NULL_PTR, resultPtr, resultLength);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      /* set job state to NO_JOB irrespective of the result */
      Cry_GddAutHsmTrueRandomGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmTrueRandomGenerateTb.pResultPtr = resultPtr;
      Cry_GddAutHsmTrueRandomGenerateTb.ulResultLength = resultLength;
    }
  }
  else
  {
    /* Other job is still processing, return CSM_E_BUSY */
    LddReturnValue = CSM_E_BUSY;
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmTrueRandomGenerateCallback                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : TBD                                                 **
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
**                        Cry_GddAutHsmTrueRandomGenerateTb                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_RandomGenerateCallbackNotification              **
*******************************************************************************/
static void Cry_AutHsmTrueRandomGenerateCallback(Hsm_ErrType ddRet)
{
  Std_ReturnType LddReturnValue;

  if (ddRet == HSM_BUSY)
  {
    LddReturnValue = CSM_E_BUSY;
  }
  else
  {
    /* Set the default value to E_OK */
    LddReturnValue = E_OK;

    if (ddRet != HSM_NO_ERROR)
    {
      LddReturnValue = E_NOT_OK;
    }

    /* set job state to NO_JOB irrespective of the result */
    Cry_GddAutHsmTrueRandomGenerateTb.ucJobState = NO_JOB;
  }

  /* Callback notification will be invoking the application callback */
  Csm_RandomGenerateCallbackNotification(LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmTrueRandomGenerateMainFunction            **
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
**                        Cry_GddAutHsmTrueRandomGenerateTb                   **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Hsm_TrngGen,                                        **
**                        Csm_RandomGenerateCallbackNotification              **
*******************************************************************************/
void Cry_AutHsmTrueRandomGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LpCallback = &Cry_AutHsmTrueRandomGenerateCallback;

  LddErr = Hsm_TrngGen(CSM_TRUE, LpCallback,
    Cry_GddAutHsmTrueRandomGenerateTb.pResultPtr,
    Cry_GddAutHsmTrueRandomGenerateTb.ulResultLength);

  if (LddErr != HSM_NO_ERROR)
  {
    LddReturnValue = E_NOT_OK;

    Cry_GddAutHsmTrueRandomGenerateTb.ucJobState = NO_JOB;

    Csm_RandomGenerateCallbackNotification(LddReturnValue);
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_RANDOM_AUTHSMTRUERANDOMGENERATE == STD_ON) */
#endif /* (CSM_RANDOM_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
