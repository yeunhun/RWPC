/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmPseudoRandomGenerate.c                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Interface                               **
**                - HSM Pseudo Random Generate                                **
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
#include "Cry_AutHsmPseudoRandomGenerate.h"
#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
#if (CSM_RANDOM_AUTHSMPSEUDORANDOMGENERATE == STD_ON)
#include "Csm_Cbk.h"
#include "Hsm_AutIntDriver.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Cry HSM Pseudo Random Generate Transfer buffer*/
typedef struct
{
  /* Define job state */
  uint8 ucJobState;
  uint8* pResultPtr;
  uint32 ulResultLength;
} Cry_AutHsmPseudoRandomGenerateTransferBuffer;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Structure variable for HSMRandom Generate transfer buffer */
static Cry_AutHsmPseudoRandomGenerateTransferBuffer Cry_GddAutHsmPseudoRandomGenerateTb;

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Local Function Prototypes                             **
*******************************************************************************/
static void Cry_AutHsmPseudoRandomGenerateCallback(Hsm_ErrType ddRet);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : Cry_AutHsmPseudoRandomGenerateInit                    **
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
**                      Cry_GddAutHsmPseudoRandomGenerateTb                   **
**                                                                            **
**                      Function(s) invoked: None                             **
*******************************************************************************/
void Cry_AutHsmPseudoRandomGenerateInit(void)
{
  /* Initialize the module data variables to default values */
  Cry_GddAutHsmPseudoRandomGenerateTb.ucJobState = NO_JOB;
  Cry_GddAutHsmPseudoRandomGenerateTb.pResultPtr = NULL_PTR;
  Cry_GddAutHsmPseudoRandomGenerateTb.ulResultLength = CSM_ZERO;
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPseudoRandomGenerate                      **
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
**                        Cry_AutHsmPseudoRandomGenerateInit,                 **
**                        Csm_RandomGenerateServiceHasCallback, Hsm_PrngGen   **
*******************************************************************************/
Std_ReturnType Cry_AutHsmPseudoRandomGenerate(const void* cfgPtr, uint8* resultPtr,
  uint32 resultLength)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  boolean LblAsync;

  /* Setting Default return value */
  LddReturnValue = E_OK;

  CSM_PARAM_UNUSED_PTR(cfgPtr);

  if (NO_JOB == Cry_GddAutHsmPseudoRandomGenerateTb.ucJobState)
  {
    /* Initializing Autron Random Generate Global variables */
    Cry_AutHsmPseudoRandomGenerateInit();

    /* Set the job state to JOB_GENERATE */
    Cry_GddAutHsmPseudoRandomGenerateTb.ucJobState = JOB_START;

    LblAsync = Csm_RandomGenerateServiceHasCallback();

    if (LblAsync == FALSE)
    {
      LddErr = Hsm_PrngGen(LblAsync, NULL_PTR, resultPtr, resultLength);

      if (LddErr != HSM_NO_ERROR)
      {
        LddReturnValue = E_NOT_OK;
      }

      /* set job state to NO_JOB irrespective of the result */
      Cry_GddAutHsmPseudoRandomGenerateTb.ucJobState = NO_JOB;
    }
    else
    {
      Cry_GddAutHsmPseudoRandomGenerateTb.pResultPtr = resultPtr;
      Cry_GddAutHsmPseudoRandomGenerateTb.ulResultLength = resultLength;
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
** Function Name        : Cry_AutHsmPseudoRandomGenerateCallback              **
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
**                        Cry_GddAutHsmPseudoRandomGenerateTb                 **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_RandomGenerateCallbackNotification              **
*******************************************************************************/
static void Cry_AutHsmPseudoRandomGenerateCallback(Hsm_ErrType ddRet)
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
    Cry_GddAutHsmPseudoRandomGenerateTb.ucJobState = NO_JOB;
  }

  /* Callback notification will be invoking the application callback */
  Csm_RandomGenerateCallbackNotification(LddReturnValue);
}

/*******************************************************************************
** Function Name        : Cry_AutHsmPseudoRandomGenerateMainFunction          **
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
**                        Cry_GddAutHsmPseudoRandomGenerateTb                 **
**                                                                            **
**                        Function(s) invoked:                                **
**                        Hsm_PrngGen,                                        **
**                        Csm_RandomGenerateCallbackNotification              **
*******************************************************************************/
void Cry_AutHsmPseudoRandomGenerateMainFunction(void)
{
  Std_ReturnType LddReturnValue;
  Hsm_ErrType LddErr;
  Hsm_CallbackPtr LpCallback;

  LpCallback = &Cry_AutHsmPseudoRandomGenerateCallback;

  LddErr = Hsm_PrngGen(CSM_TRUE, LpCallback,
    Cry_GddAutHsmPseudoRandomGenerateTb.pResultPtr,
    Cry_GddAutHsmPseudoRandomGenerateTb.ulResultLength);

  if (LddErr != HSM_NO_ERROR)
  {
    LddReturnValue = E_NOT_OK;

    Cry_GddAutHsmPseudoRandomGenerateTb.ucJobState = NO_JOB;

    Csm_RandomGenerateCallbackNotification(LddReturnValue);
  }
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_RANDOM_AUTHSMPSEUDORANDOMGENERATE == STD_ON) */
#endif /* (CSM_RANDOM_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
