/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmPseudoRandomGenerate.c                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - HAE HSM Pseudo Random Generate                            **
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
** 1.0.1     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.0     04-Dec-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_HaeHsmPseudoRandomGenerate.h"
#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
#if (CSM_RANDOM_HAEHSMPSEUDORANDOMGENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "HSM_Hae.h"
#include "SecurityApp_Rng.h"
#include "string.h"
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HAE HSM Pseudo Random Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  /* Pointer of result */
  uint8* pResultPtr;
  /* Length of result */
  uint32 ulResultLength;
} Cry_HaeHsmPseudoRandomGenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Cry_HaeHsmPseudoRandomGenerateTransferBuffer Cry_GddHaeHsmPseudoRandomGenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : Cry_HaeHsmPseudoRandomGenerateInit                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This service initializes the transfer buffer of the   **
**                      HAE Pseudo Random Generate. All module Global         **
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
**                      Cry_GddHaeHsmPseudoRandomGenerateTb                   **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_HaeHsmPseudoRandomGenerateInit(void)
{
  Cry_GddHaeHsmPseudoRandomGenerateTb.ucJobState = NO_JOB;
  Cry_GddHaeHsmPseudoRandomGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddHaeHsmPseudoRandomGenerateTb.ulResultLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_HaeHsmPseudoRandomGenerate                      **
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
**                        Cry_HaeHsmPseudoRandomGenerateInit,                 **
**                        Csm_RandomGenerateServiceHasCallback,               **
**                        HSM_PseudoRandomGenerate,                           **
**                        HSM_HaeGetErrorCode,                                **
*******************************************************************************/
Std_ReturnType Cry_HaeHsmPseudoRandomGenerate(const void* cfgPtr, uint8* resultPtr,
  uint32 resultLength)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddHaeHsmPseudoRandomGenerateTb.ucJobState)
  {
    Cry_HaeHsmPseudoRandomGenerateInit();

    Cry_GddHaeHsmPseudoRandomGenerateTb.ucJobState = JOB_START;

    if (Csm_RandomGenerateServiceHasCallback() == FALSE)
    {
      if (resultLength > HSM_HAE_PRNG_MAX_LENGTH)
      {
        LddReturnValue = E_NOT_OK;
      }

      if (LddReturnValue == E_OK)
      {
        LddReturnValue = HSM_PseudoRandomGenerate(resultPtr, resultLength);

        if (LddReturnValue != E_OK)
        {
          LddReturnValue = E_NOT_OK;
          HSM_HaeGetErrorCode();
        }
      }

      /* Update job state to NO_JOB irrespective of the result */
      Cry_GddHaeHsmPseudoRandomGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddHaeHsmPseudoRandomGenerateTb.pResultPtr = resultPtr;
      Cry_GddHaeHsmPseudoRandomGenerateTb.ulResultLength = resultLength;
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
** Function Name        : Cry_HaeHsmPseudoRandomGenerateMainFunction          **
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
**                        Cry_GddHaeHsmPseudoRandomGenerateTb                 **
**                                                                            **
**                        Function(s) invoked:                                **
**                        HSM_PseudoRandomGenerate,                           **
**                        HSM_HaeGetErrorCode,                                **
**                        Csm_RandomGenerateCallbackNotification              **
*******************************************************************************/
void Cry_HaeHsmPseudoRandomGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  uint32 LulResultLength;
  uint8* LpResultPtr;

  LddReturnValue = E_OK;

  if (Cry_GddHaeHsmPseudoRandomGenerateTb.ulResultLength
    > HSM_HAE_PRNG_MAX_LENGTH)
  {
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    LulResultLength = Cry_GddHaeHsmPseudoRandomGenerateTb.ulResultLength;
    LpResultPtr = Cry_GddHaeHsmPseudoRandomGenerateTb.pResultPtr;

    LddReturnValue = HSM_PseudoRandomGenerate(LpResultPtr, LulResultLength);

    if (LddReturnValue != E_OK)
    {
      LddReturnValue = E_NOT_OK;
      HSM_HaeGetErrorCode();
    }
  }

  /* Update job state to NO_JOB irrespective of the result */
  Cry_GddHaeHsmPseudoRandomGenerateTb.ucJobState = NO_JOB;

  Csm_RandomGenerateCallbackNotification(LddReturnValue);
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_RANDOM_HAEHSMPSEUDORANDOMGENERATE == STD_ON) */
#endif /* (CSM_RANDOM_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
