/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmTrueRandomGenerate.c                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - HAE HSM True Random Generate                              **
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
** 1.0.5     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.4     04-Dec-2019   Sinil        Redmine #20495                        **
** 1.0.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.2     17-Apr-2018   Sinil        Redmine #12352                        **
** 1.0.1     05-Dec-2017   Sinil        Redmine #10845                        **
** 1.0.0     08-Aug-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_HaeHsmTrueRandomGenerate.h"
#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
#if (CSM_RANDOM_HAEHSMTRUERANDOMGENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "SecurityApp_Rng.h"
#include "string.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HAE HSM True Random Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Pointer of result */
  uint8* pResultPtr;
  /* Length of result */
  uint32 ulResultLength;
} Cry_HaeHsmTrueRandomGenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Cry_HaeHsmTrueRandomGenerateTransferBuffer Cry_GddHaeHsmTrueRandomGenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : Cry_HaeHsmTrueRandomGenerateInit                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the transfer buffer of the   **
**                      HAE True Random Generate. All module Global           **
**                      variables will be initialized after successful        **
**                      completion of this API.                               **
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
** Remarks            : Global Variable(s)  :                                 **
**                      Cry_GddHaeHsmTrueRandomGenerateTb                     **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmTrueRandomGenerateInit(void)
{
  Cry_GddHaeHsmTrueRandomGenerateTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmTrueRandomGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaeHsmTrueRandomGenerateTb.ulResultLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmTrueRandomGenerate                        **
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
**                        Cry_HaeHsmTrueRandomGenerateInit,                   **
**                        Csm_RandomGenerateServiceHasCallback,               **
**                        HSM_TrueRandomGenerate,                             **
**                        HSM_HaeGetErrorCode                                 **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmTrueRandomGenerate(const void* cfgPtr, uint8* resultPtr,
  uint32 resultLength)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmTrueRandomGenerateTb.ucJobState)
  {
    Cry_HaeHsmTrueRandomGenerateInit();

    Cry_GddHaeHsmTrueRandomGenerateTb.ucJobState = JOB_START;

    if (Csm_RandomGenerateServiceHasCallback() == FALSE)
    {
      if (resultLength > HSM_HAE_TRNG_MAX_LENGTH)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_TrueRandomGenerate(resultPtr, resultLength);

        if (LddReturnValue != E_OK)
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHsmTrueRandomGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHsmTrueRandomGenerateTb.pResultPtr = resultPtr;
      Cry_GddHaeHsmTrueRandomGenerateTb.ulResultLength = resultLength;
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
** Function Name        : Cry_HaeHsmTrueRandomGenerateMainFunction            **
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
**                        Cry_GddHaeHsmTrueRandomGenerateTb                   **
**                                                                            **
**                        Function(s) invoked:                                **
**                        HSM_TrueRandomGenerate,                             **
**                        HSM_HaeGetErrorCode,                                **
**                        Csm_RandomGenerateCallbackNotification              **
*******************************************************************************/
void Cry_HaeHsmTrueRandomGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint32 LulResultLength;
  uint8* LpResultPtr;

  LddReturnValue = E_OK;

  if (Cry_GddHaeHsmTrueRandomGenerateTb.ulResultLength
    > HSM_HAE_TRNG_MAX_LENGTH)
  {
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    LulResultLength = Cry_GddHaeHsmTrueRandomGenerateTb.ulResultLength;
    LpResultPtr = Cry_GddHaeHsmTrueRandomGenerateTb.pResultPtr;

    LddReturnValue = HSM_TrueRandomGenerate(LpResultPtr, LulResultLength);

    if (LddReturnValue != E_OK)
    {
      LddReturnValue = E_NOT_OK;
      HSM_HaeGetErrorCode();
    }
  }

  /* Update job state to NO_JOB irrespective of the result */
  Cry_GddHaeHsmTrueRandomGenerateTb.ucJobState = NO_JOB;

  Csm_RandomGenerateCallbackNotification(LddReturnValue);
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_RANDOM_HAEHSMTRUERANDOMGENERATE == STD_ON) */
#endif /* (CSM_RANDOM_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
