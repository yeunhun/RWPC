/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_KeyExchangeCalc.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of Key Exchange Calculation Interface          **
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
** 1.2.4     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.2.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.2     09-May-2018   Sinil        Redmine #12635                        **
** 1.2.1     21-Sep-2017   Sinil        Redmine #10038                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198                         **
** 1.0.5     09-Aug-2016   Sinil        Redmine #5693, #5694, #5760           **
** 1.0.4     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.3     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.2     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.1     02-Dec-2015   Sinil        Memory section changed                **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm.h"                  /* Header file for function prototypes */
#include "Rte_Csm.h"
#if (CSM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Header file for DET */
#endif

#if ((CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON) || (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) || (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON))
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON) /* KeyExchangeCalcPubVal */
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveKeyExchangeCalcPubValService Csm_GddActiveKeyExchangeCalcPubValService;
#endif /* (CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON) */

#if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) /* KeyExchangeCalcSecret */
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveKeyExchangeCalcSecretService Csm_GddActiveKeyExchangeCalcSecretService;
#endif /* (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) */

#if (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON) /* KeyExchangeCalcSymKey */
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveKeyExchangeCalcSymKeyService Csm_GddActiveKeyExchangeCalcSymKeyService;
#endif /* (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON) */

#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
#if (CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON) /* KeyExchangeCalcPubVal */
/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcPubVal                           **
**                                                                            **
** Service ID           : 0x2e                                                **
**                                                                            **
** Description          : This function initiates the public value calculation**
**                        service of the CSM module.                          **
**                        It will store the configuration information as      **
**                        identified by cfgId and will call the corresponding **
**                        Cry_<primitive>() provided the service state is     **
**                        not "active" and shall return the value returned by **
**                        that function and set the service state to "active".**
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, basePtr, privateValuePtr                     **
**                                                                            **
** InOut parameter      : publicValueLengthPtr                                **
**                                                                            **
** Output Parameters    : publicValuePtr                                      **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        CSM_E_BUSY: service state is already "active"       **
**                        CSM_E_SMALL_BUFFER: provided buffer is too small to **
**                                            store the result                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                Csm_GddActiveKeyExchangeCalcPubValService   **
**                                Csm_GaaKeyExchangeCalcPubValConfigType      **
**                        Function(s) invoked : Cry_<Primitive>,              **
**                                              Det_ReportError,              **
**                                              Csm_FunctionPush              **
*******************************************************************************/
Std_ReturnType Csm_KeyExchangeCalcPubVal(Csm_ConfigIdType cfgId,
  const Csm_KeyExchangeBaseType* basePtr,
  const Csm_KeyExchangePrivateType* privateValuePtr, uint8* publicValuePtr,
  uint32* publicValueLengthPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if CSM module is initialized */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYEXCHANGECALCPUBVAL_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if Invalid cryptographic method is invoked for selected service */
    if (cfgId >= CSM_KEY_EXCHANGE_CALCSECRET_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCPUBVAL_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the basePtr is NULL */
    if (basePtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCPUBVAL_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (basePtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCPUBVAL_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the privateValuePtr is NULL */
    if (privateValuePtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCPUBVAL_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (privateValuePtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCPUBVAL_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the publicValuePtr is NULL */
    if (publicValuePtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCPUBVAL_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the publicValueLengthPtr is NULL */
    if (publicValueLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCPUBVAL_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*publicValueLengthPtr == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCPUBVAL_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveKeyExchangeCalcPubValService.ucServiceState
      & CSM_KEY_EXCHANGE_CALCPUBVAL_IDLE) != CSM_KEY_EXCHANGE_CALCPUBVAL_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Set the Service state to CSM_KEY_EXCHANGE_CALC_SECRET_START */
    Csm_GddActiveKeyExchangeCalcPubValService.ucServiceState =
      CSM_KEY_EXCHANGE_CALCPUBVAL_ACTIVE;

    /* Assign appropriate config address to the Active Service pointer */
    Csm_GddActiveKeyExchangeCalcPubValService.pActiveServiceConfig =
      &Csm_GaaKeyExchangeCalcPubValConfigType[cfgId];

    /*
     * Invoke respective primitive start function
     * argument will be provided by the Key exchange configuration
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveKeyExchangeCalcPubValService.
      pActiveServiceConfig->PrimitiveFct(
      (void*)Csm_GddActiveKeyExchangeCalcPubValService.
      pActiveServiceConfig->PrimitiveConfigPtr, basePtr, privateValuePtr,
      publicValuePtr, publicValueLengthPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveKeyExchangeCalcPubValService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        #if (CSM_DEV_ERROR_DETECT == STD_ON)
        if (LddReturnValue == CSM_E_SMALL_BUFFER)
        {
          (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
            CSM_KEYEXCHANGECALCPUBVAL_SID, CSM_E_BUFFER_TOO_SMALL);
        }
        #endif

        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveKeyExchangeCalcPubValService.ucServiceState =
          CSM_KEY_EXCHANGE_CALCPUBVAL_IDLE;
      }
      else
      {
        if (Csm_GddActiveKeyExchangeCalcPubValService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the primitive main function onto the Main Function stack */
          LddReturnValue = Csm_FunctionPush(
            Csm_GddActiveKeyExchangeCalcPubValService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcPubValCallbackNotification       **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Key Exchange public   **
**                        value calculation service with the argument given   **
**                        by "Result".                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ddResult                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                           Csm_GddActiveKeyExchangeCalcPubValService        **
**                        Function(s) invoked:  Det_ReportError               **
*******************************************************************************/
void Csm_KeyExchangeCalcPubValCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing. Previous request result will be returned */
    break;

  case CSM_E_SMALL_BUFFER:
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYEXCHANGECALCPUBVAL_SID, CSM_E_BUFFER_TOO_SMALL);
    #endif

    /* Setting the service state to idle irrespective of the result */
    Csm_GddActiveKeyExchangeCalcPubValService.ucServiceState =
      CSM_KEY_EXCHANGE_CALCPUBVAL_IDLE;
    break;

  default:
    /* Setting the service state to idle irrespective of the result */
    Csm_GddActiveKeyExchangeCalcPubValService.ucServiceState =
      CSM_KEY_EXCHANGE_CALCPUBVAL_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveKeyExchangeCalcPubValService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveKeyExchangeCalcPubValService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcPubValServiceFinishNotification  **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the Key        **
**                        Exchange public value calculation service to "idle".**
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                           Csm_GddActiveKeyExchangeCalcPubValService        **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_KeyExchangeCalcPubValServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveKeyExchangeCalcPubValService.ucServiceState =
    CSM_KEY_EXCHANGE_CALCPUBVAL_IDLE;
}

boolean Csm_KeyExchangeCalcPubValServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveKeyExchangeCalcPubValService.pActiveServiceConfig->
    CallbackFct != NULL_PTR)
  {
    LblHasCallback = TRUE;
  }
  else
  {
    LblHasCallback = FALSE;
  }

  return LblHasCallback;
}
#endif /* (CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON) */

#if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON)
/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcSecretStart                      **
**                                                                            **
** Service ID           : 0x2f                                                **
**                                                                            **
** Description          : This function initializes the Key Exchange service  **
**                        of CSM module.                                      **
**                        It will store the configuration information as      **
**                        identified by cfgId and will call the corresponding **
**                        Cry_<primitive>Start() provided the service state is**
**                        not "active" and shall return the value returned by **
**                        that function and set the service state to "active".**
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, basePtr, privateValuePtr                     **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Csm_GddActiveKeyExchangeCalcSecretService,          **
**                        Csm_GaaKeyExchangeCalcSecretConfigType              **
**                                                                            **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                        Csm_FunctionPush                                    **
*******************************************************************************/
Std_ReturnType Csm_KeyExchangeCalcSecretStart(Csm_ConfigIdType cfgId,
  const Csm_KeyExchangeBaseType* basePtr,
  const Csm_KeyExchangePrivateType* privateValuePtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if CSM module is initialized */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYEXCHANGECALCSECRETSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if Invalid cryptographic method is invoked for selected service */
    if (cfgId >= CSM_KEY_EXCHANGE_CALCSECRET_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSECRETSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  /* Not used parameter validation checking is disabled */
  /* Related algorithm : AutHsmEcdh */
  #if 0
  if (LddReturnValue == E_OK)
  {
    /* Check if the basePtr is NULL */
    if (basePtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSECRETSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (basePtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSECRETSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }
  #endif

  if (LddReturnValue == E_OK)
  {
    /* Check if the privateValuePtr is NULL */
    if (privateValuePtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSECRETSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
    if (privateValuePtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSECRETSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SECRET_IDLE) != CSM_KEY_EXCHANGE_CALC_SECRET_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Set the Service state to CSM_KEY_EXCHANGE_CALC_SECRET_START */
    Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState =
      CSM_KEY_EXCHANGE_CALC_SECRET_START;

    /* Assign appropriate config address to the Active Service pointer */
    Csm_GddActiveKeyExchangeCalcSecretService.pActiveServiceConfig =
      &Csm_GaaKeyExchangeCalcSecretConfigType[cfgId];

    /*
     * Invoke respective primitive start function
     * argument will be provided by the Key exchange configuration
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveKeyExchangeCalcSecretService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GaaKeyExchangeCalcSecretConfigType[cfgId].
      PrimitiveConfigPtr, basePtr, privateValuePtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveKeyExchangeCalcSecretService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_KEY_EXCHANGE_CALC_SECRET_ACTIVE */
          Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState =
            CSM_KEY_EXCHANGE_CALC_SECRET_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState =
            CSM_KEY_EXCHANGE_CALC_SECRET_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveKeyExchangeCalcSecretService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the primitive main function onto the Main Function stack */
          LddReturnValue = Csm_FunctionPush(
            Csm_GddActiveKeyExchangeCalcSecretService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcSecretUpdate                     **
**                                                                            **
** Service ID           : 0x30                                                **
**                                                                            **
** Description          : This function is used to feed the key exchange      **
**                        service with the public value coming from the       **
**                        partner of the key exchange protocol.               **
**                        Cry_<Primitive>Update of the primitive identified   **
**                        by the stored configuration information and return  **
**                        the value returned by that function.                **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, partnerPublicValuePtr,                       **
**                        partnerPublicValueLength                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Csm_GddActiveKeyExchangeCalcSecretService           **
**                        Function(s) invoked : Cry_<Primitive>Update         **
*******************************************************************************/
Std_ReturnType Csm_KeyExchangeCalcSecretUpdate(Csm_ConfigIdType cfgId,
  const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the input pointer is NULL */
  if (partnerPublicValuePtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYEXCHANGECALCSECRETUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (partnerPublicValueLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSECRETUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SECRET_START) == CSM_KEY_EXCHANGE_CALC_SECRET_START)
      || ((Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SECRET_UPDATE) == CSM_KEY_EXCHANGE_CALC_SECRET_UPDATE)
      || ((Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SECRET_FINISH) == CSM_KEY_EXCHANGE_CALC_SECRET_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SECRET_ACTIVE) != CSM_KEY_EXCHANGE_CALC_SECRET_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSECRETUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState =
      CSM_KEY_EXCHANGE_CALC_SECRET_UPDATE;

    /* Invoke respective primitive Update function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveKeyExchangeCalcSecretService.
      pActiveServiceConfig->PrimitiveUpdateFct(cfgId,
      partnerPublicValuePtr,
      partnerPublicValueLength);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveKeyExchangeCalcSecretService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_KEY_EXCHANGE_CALC_SECRET_ACTIVE */
          Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState =
            CSM_KEY_EXCHANGE_CALC_SECRET_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState =
            CSM_KEY_EXCHANGE_CALC_SECRET_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveKeyExchangeCalcSecretService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveKeyExchangeCalcSecretService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcSecretFinish                     **
**                                                                            **
** Service ID           : 0x31                                                **
**                                                                            **
** Description          : This function used to finish the Key exchange       **
**                        service. Generate service by calling                **
**                        Cry_<Primitive>Finish as identified by stored       **
**                        configuration information and returns the value     **
**                        returned by that function.                          **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, TruncationIsAllowed                          **
**                                                                            **
** InOut parameter      : sharedSecretLengthPtr                               **
**                                                                            **
** Output Parameters    : sharedSecretPtr                                     **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                        CSM_E_SMALL_BUFFER: provided buffer is too small to **
**                                            store the result                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                Csm_GddActiveKeyExchangeCalcSecretService   **
**                        Function(s) invoked : Cry_<Primitive>Finish,        **
**                                              Det_ReportError               **
*******************************************************************************/
Std_ReturnType Csm_KeyExchangeCalcSecretFinish(Csm_ConfigIdType cfgId,
  uint8* sharedSecretPtr, uint32* sharedSecretLengthPtr,
  boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the result pointer is NULL */
  if (sharedSecretPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYEXCHANGECALCSECRETFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the result length pointer is NULL_PTR */
    if (sharedSecretLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSECRETFINISH_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "No Impact of this rule violation" */
    if (*sharedSecretLengthPtr == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSECRETFINISH_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Checking whether the service is initialized or not */
    if (((Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SECRET_START) == CSM_KEY_EXCHANGE_CALC_SECRET_START)
      || ((Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SECRET_UPDATE) == CSM_KEY_EXCHANGE_CALC_SECRET_UPDATE)
      || ((Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SECRET_FINISH) == CSM_KEY_EXCHANGE_CALC_SECRET_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SECRET_ACTIVE) != CSM_KEY_EXCHANGE_CALC_SECRET_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSECRETFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState =
      CSM_KEY_EXCHANGE_CALC_SECRET_FINISH;

    /* Invoke respective primitive Finish function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveKeyExchangeCalcSecretService.
      pActiveServiceConfig->PrimitiveFinishFct(cfgId,
      sharedSecretPtr, sharedSecretLengthPtr, TruncationIsAllowed);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveKeyExchangeCalcSecretService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        #if (CSM_DEV_ERROR_DETECT == STD_ON)
        if (LddReturnValue == CSM_E_SMALL_BUFFER)
        {
          (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
            CSM_KEYEXCHANGECALCSECRETFINISH_SID, CSM_E_BUFFER_TOO_SMALL);
        }
        #endif

        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
          = CSM_KEY_EXCHANGE_CALC_SECRET_IDLE;
      }
      else
      {
        if (Csm_GddActiveKeyExchangeCalcSecretService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveKeyExchangeCalcSecretService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcSecretCallbackNotification       **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Key Exchange service  **
**                        with the argument given by "Result".                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ddResult                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                           Csm_GddActiveKeyExchangeCalcSecretService        **
**                        Function(s) invoked:  Det_ReportError               **
*******************************************************************************/
void Csm_KeyExchangeCalcSecretCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState)
    {
    case CSM_KEY_EXCHANGE_CALC_SECRET_START:
    case CSM_KEY_EXCHANGE_CALC_SECRET_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
        = CSM_KEY_EXCHANGE_CALC_SECRET_ACTIVE;
      break;

    case CSM_KEY_EXCHANGE_CALC_SECRET_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
        = CSM_KEY_EXCHANGE_CALC_SECRET_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState)
    {
    case CSM_KEY_EXCHANGE_CALC_SECRET_START:
    case CSM_KEY_EXCHANGE_CALC_SECRET_UPDATE:
      break;

    case CSM_KEY_EXCHANGE_CALC_SECRET_FINISH:
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      if (ddResult == CSM_E_SMALL_BUFFER)
      {
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          CSM_KEYEXCHANGECALCSECRETFINISH_SID, CSM_E_BUFFER_TOO_SMALL);
      }
      #endif
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState
      = CSM_KEY_EXCHANGE_CALC_SECRET_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveKeyExchangeCalcSecretService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveKeyExchangeCalcSecretService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcSecretServiceFinishNotification  **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the Key        **
**                        Exchange service to "idle".                         **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                           Csm_GddActiveKeyExchangeCalcSecretService        **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_KeyExchangeCalcSecretServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveKeyExchangeCalcSecretService.ucServiceState =
    CSM_KEY_EXCHANGE_CALC_SECRET_IDLE;
}

boolean Csm_KeyExchangeCalcSecretServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveKeyExchangeCalcSecretService.pActiveServiceConfig->
    CallbackFct != NULL_PTR)
  {
    LblHasCallback = TRUE;
  }
  else
  {
    LblHasCallback = FALSE;
  }

  return LblHasCallback;
}
#endif /* (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) */

#if (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON)
/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcSymKeyStart                      **
**                                                                            **
** Service ID           : 0x3D                                                **
**                                                                            **
** Description          : This function initializes the key exchange service  **
**                        of CSM module. It will store the configuration      **
**                        information identified by "cfgId" and will call the**
**                        corresponding Cry_<primitive>Start() provided the   **
**                        service state is not "active" and shall return the  **
**                        value returned by that function and set the service **
**                        state to "active".                                  **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, basePtr, privateValuePtr                     **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                Csm_GddActiveKeyExchangeCalcSymKeyService   **
**                                Csm_GaaKeyExchangeCalcSymKeyConfigType      **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                        Csm_FunctionPush                                    **
*******************************************************************************/
Std_ReturnType Csm_KeyExchangeCalcSymKeyStart(Csm_ConfigIdType cfgId,
  const Csm_KeyExchangeBaseType* basePtr,
  const Csm_KeyExchangePrivateType* privateValuePtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if CSM module is initialized */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYEXCHANGECALCSYMKEYSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if Invalid cryptographic method is invoked for selected service */
    if (cfgId >= CSM_KEY_EXCHANGE_CALCSYM_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSYMKEYSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the basePtr is NULL */
    if (basePtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSYMKEYSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (basePtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSYMKEYSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the privateValuePtr is NULL */
    if (privateValuePtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSYMKEYSTART_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (privateValuePtr->length == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSYMKEYSTART_SID, CSM_E_PARAM_KEY_TYPE_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SYM_KEY_IDLE) != CSM_KEY_EXCHANGE_CALC_SYM_KEY_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Set the Service state to CSM_KEY_EXCHANGE_VERIFY_START */
    Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState =
      CSM_KEY_EXCHANGE_CALC_SYM_KEY_START;

    /* Assign appropriate config address to the Active Service pointer */
    Csm_GddActiveKeyExchangeCalcSymKeyService.pActiveServiceConfig =
      &Csm_GaaKeyExchangeCalcSymKeyConfigType[cfgId];

    /*
     * Invoke respective primitive start function
     * argument will be provided by the Key exchange configuration
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveKeyExchangeCalcSymKeyService.
      pActiveServiceConfig->PrimitiveStartFct(
      (void*)Csm_GddActiveKeyExchangeCalcSymKeyService.
      pActiveServiceConfig->PrimitiveConfigPtr, basePtr, privateValuePtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveKeyExchangeCalcSymKeyService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_KEY_EXCHANGE_CALC_SYM_KEY_ACTIVE */
          Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState =
            CSM_KEY_EXCHANGE_CALC_SYM_KEY_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState =
            CSM_KEY_EXCHANGE_CALC_SYM_KEY_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveKeyExchangeCalcSymKeyService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the primitive main function onto the Main Function stack */
          LddReturnValue = Csm_FunctionPush(
            Csm_GddActiveKeyExchangeCalcSymKeyService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcSymKeyUpdate                     **
**                                                                            **
** Service ID           : 0x3E                                                **
**                                                                            **
** Description          : This function is used to feed the key exchange      **
**                        service with the public value coming from the       **
**                        partner of the key exchange protocol. It calls      **
**                        Cry_<Primitive>Update of the primitive identified   **
**                        by the stored configuration information and return  **
**                        the value returned by that function.                **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, partnerPublicValuePtr,                       **
**                        partnerPublicValueLength                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                Csm_GddActiveKeyExchangeCalcSymKeyService   **
**                        Function(s) invoked : Cry_<Primitive>Update         **
*******************************************************************************/
Std_ReturnType Csm_KeyExchangeCalcSymKeyUpdate(Csm_ConfigIdType cfgId,
  const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the input pointer is NULL */
  if (partnerPublicValuePtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYEXCHANGECALCSYMKEYUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (partnerPublicValueLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSYMKEYUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SYM_KEY_START) == CSM_KEY_EXCHANGE_CALC_SYM_KEY_START)
      || ((Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SYM_KEY_UPDATE) == CSM_KEY_EXCHANGE_CALC_SYM_KEY_UPDATE)
      || ((Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SYM_KEY_FINISH) == CSM_KEY_EXCHANGE_CALC_SYM_KEY_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SYM_KEY_ACTIVE) != CSM_KEY_EXCHANGE_CALC_SYM_KEY_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSYMKEYUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState =
      CSM_KEY_EXCHANGE_CALC_SYM_KEY_UPDATE;

    /* Invoke respective primitive Update function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveKeyExchangeCalcSymKeyService.
      pActiveServiceConfig->PrimitiveUpdateFct(cfgId,
      partnerPublicValuePtr, partnerPublicValueLength);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveKeyExchangeCalcSymKeyService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_KEY_EXCHANGE_CALC_SYM_KEY_ACTIVE */
          Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState =
            CSM_KEY_EXCHANGE_CALC_SYM_KEY_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState =
            CSM_KEY_EXCHANGE_CALC_SYM_KEY_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveKeyExchangeCalcSymKeyService.pActiveServiceConfig->
          PrimitiveMainFct != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveKeyExchangeCalcSymKeyService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcSymKeyFinish                     **
**                                                                            **
** Service ID           : 0x3F                                                **
**                                                                            **
** Description          : This function will be used to finish the Key        **
**                        Exchange service by calling Cry_<Primitive>Finish as**
**                        identified by the stored stored configuration       **
**                        information and returns the value returned by that  **
**                        function.                                           **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId                                               **
**                                                                            **
** InOut parameter      : sharedKeyPtr                                        **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                        CSM_E_BUSY: request failed, service is still busy   **
**                        E_NOT_OK: service state is "idle"                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                Csm_GddActiveKeyExchangeCalcSymKeyService   **
**                        Function(s) invoked : Cry_<Primitive>Finish         **
*******************************************************************************/
Std_ReturnType Csm_KeyExchangeCalcSymKeyFinish(Csm_ConfigIdType cfgId,
  Csm_SymKeyType* sharedKeyPtr)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the sharedKey pointer is NULL */
  if (sharedKeyPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_KEYEXCHANGECALCSYMKEYFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SYM_KEY_START) == CSM_KEY_EXCHANGE_CALC_SYM_KEY_START)
      || ((Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SYM_KEY_UPDATE) == CSM_KEY_EXCHANGE_CALC_SYM_KEY_UPDATE)
      || ((Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SYM_KEY_FINISH) == CSM_KEY_EXCHANGE_CALC_SYM_KEY_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
      & CSM_KEY_EXCHANGE_CALC_SYM_KEY_ACTIVE) != CSM_KEY_EXCHANGE_CALC_SYM_KEY_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_KEYEXCHANGECALCSYMKEYFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState =
      CSM_KEY_EXCHANGE_CALC_SYM_KEY_FINISH;

    /* Invoke respective primitive Finish function */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveKeyExchangeCalcSymKeyService.
      pActiveServiceConfig->PrimitiveFinishFct(cfgId, sharedKeyPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveKeyExchangeCalcSymKeyService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
          = CSM_KEY_EXCHANGE_CALC_SYM_KEY_IDLE;
      }
      else
      {
        if (Csm_GddActiveKeyExchangeCalcSymKeyService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveKeyExchangeCalcSymKeyService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcSymKeyCallbackNotification       **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Key Exchange service  **
**                        with the argument given by "Result".                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ddResult                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                           Csm_GddActiveKeyExchangeCalcSymKeyService        **
*******************************************************************************/
void Csm_KeyExchangeCalcSymKeyCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState)
    {
    case CSM_KEY_EXCHANGE_CALC_SYM_KEY_START:
    case CSM_KEY_EXCHANGE_CALC_SYM_KEY_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
        = CSM_KEY_EXCHANGE_CALC_SYM_KEY_ACTIVE;
      break;

    case CSM_KEY_EXCHANGE_CALC_SYM_KEY_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
        = CSM_KEY_EXCHANGE_CALC_SYM_KEY_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState)
    {
    case CSM_KEY_EXCHANGE_CALC_SYM_KEY_START:
    case CSM_KEY_EXCHANGE_CALC_SYM_KEY_UPDATE:
    case CSM_KEY_EXCHANGE_CALC_SYM_KEY_FINISH:
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState
      = CSM_KEY_EXCHANGE_CALC_SYM_KEY_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveKeyExchangeCalcSymKeyService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveKeyExchangeCalcSymKeyService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcSymKeyServiceFinishNotification  **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of the Key        **
**                        Exchange service to "idle".                         **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):                                 **
**                           Csm_GddActiveKeyExchangeCalcSymKeyService        **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_KeyExchangeCalcSymKeyServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveKeyExchangeCalcSymKeyService.ucServiceState =
    CSM_KEY_EXCHANGE_CALC_SYM_KEY_IDLE;
}

boolean Csm_KeyExchangeCalcSymKeyServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveKeyExchangeCalcSymKeyService.pActiveServiceConfig->
    CallbackFct != NULL_PTR)
  {
    LblHasCallback = TRUE;
  }
  else
  {
    LblHasCallback = FALSE;
  }

  return LblHasCallback;
}
#endif /* (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON) || (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) || (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON)) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
