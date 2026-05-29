/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Checksum.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of Checksum Interface                          **
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
** 1.2.2     22-Feb-2019   Sinil        Redmine #16157                        **
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

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm.h"                  /* Header file for function prototypes */
#include "Rte_Csm.h"
#if (CSM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Header file for DET */
#endif

#if (CSM_CHECKSUM_STATUS == STD_ON)
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
Csm_ActiveChecksumService Csm_GddActiveChecksumService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Csm_ChecksumStart                                   **
**                                                                            **
** Service ID           : 0x28                                                **
**                                                                            **
** Description          : This function initializes the Checksum calculation  **
**                        service of CSM module.                              **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s): Csm_GddActiveChecksumService    **
**                                            Csm_GaaChecksumConfigType       **
**                        Function(s) invoked : Cry_<Primitive>Start,         **
**                        Csm_FunctionPush                                    **
*******************************************************************************/
Std_ReturnType Csm_ChecksumStart(Csm_ConfigIdType cfgId)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if CSM module is initialized */
  if (Csm_GblInitStatus != CSM_TRUE)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_CHECKSUMSTART_SID, CSM_E_UNINIT);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if Invalid cryptographic method is invoked for selected service */
    if (cfgId >= CSM_CHECKSUM_CFGID_LIMIT)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_CHECKSUMSTART_SID, CSM_E_PARAM_METHOD_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveChecksumService.ucServiceState
      & CSM_CHECKSUM_IDLE) != CSM_CHECKSUM_IDLE)
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Set the Service state to CSM_CHECKSUM_START */
    Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_START;

    /* Fetching service configuration as updated during initial configuration */
    Csm_GddActiveChecksumService.pActiveServiceConfig =
      &Csm_GaaChecksumConfigType[cfgId];

    /*
     * Invoke respective primitive start function
     * argument will be provided by the Checksum configuration
     */
    /* polyspace +2 MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveChecksumService.pActiveServiceConfig->
       PrimitiveStartFct((void*)Csm_GddActiveChecksumService.
       pActiveServiceConfig->PrimitiveConfigPtr);

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveChecksumService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_CHECKSUM_ACTIVE */
          Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveChecksumService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Pushing primitive main function onto the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveChecksumService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_ChecksumUpdate                                  **
**                                                                            **
** Service ID           : 0x29                                                **
**                                                                            **
** Description          : This function is used to feed the Checksum          **
**                        calculation service with the input data. It calls   **
**                        Cry_<Primitive>Update of the primitive identified   **
**                        by the stored configuration information and return  **
**                        the value returned by that function.                **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on configuration           **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : cfgId, dataPtr, dataLength                          **
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
** Remarks              : Global Variable(s): Csm_GddActiveChecksumService    **
**                        Function(s) invoked : Cry_<Primitive>Update         **
*******************************************************************************/
Std_ReturnType Csm_ChecksumUpdate(Csm_ConfigIdType cfgId, const uint8* dataPtr,
  uint32 dataLength)
{
  Std_ReturnType LddReturnValue;

  /* Set the default value to E_OK */
  LddReturnValue = E_OK;

  /* Check if the input pointer is NULL */
  if (dataPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_CHECKSUMUPDATE_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    if (dataLength == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_CHECKSUMUPDATE_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveChecksumService.ucServiceState
      & CSM_CHECKSUM_START) == CSM_CHECKSUM_START)
      || ((Csm_GddActiveChecksumService.ucServiceState
      & CSM_CHECKSUM_UPDATE) == CSM_CHECKSUM_UPDATE)
      || ((Csm_GddActiveChecksumService.ucServiceState
      & CSM_CHECKSUM_FINISH) == CSM_CHECKSUM_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveChecksumService.ucServiceState
      & CSM_CHECKSUM_ACTIVE) != CSM_CHECKSUM_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_CHECKSUMUPDATE_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to UPDATE */
    Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_UPDATE;

    /* Invoke respective primitive Update function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveChecksumService.pActiveServiceConfig->
      PrimitiveUpdateFct(cfgId, dataPtr, dataLength);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveChecksumService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        if (LddReturnValue == E_OK)
        {
          /* Set the Service State to CSM_CHECKSUM_ACTIVE */
          Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_ACTIVE;
        }
        else
        {
          /* Setting the service state to idle upon failure */
          Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_IDLE;
        }
      }
      else
      {
        if (Csm_GddActiveChecksumService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveChecksumService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_ChecksumFinish                                  **
**                                                                            **
** Service ID           : 0x2A                                                **
**                                                                            **
** Description          : This function used to finish the Checksum           **
**                        calculation service. Generate service by calling    **
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
** InOut parameter      : resultLengthPtr                                     **
**                                                                            **
** Output Parameters    : resultPtr                                           **
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
** Remarks              : Global Variable(s): Csm_GddActiveChecksumService    **
**                        Function(s) invoked : Cry_<Primitive>Finish,        **
**                                              Det_ReportError               **
*******************************************************************************/
Std_ReturnType Csm_ChecksumFinish(Csm_ConfigIdType cfgId, uint8* resultPtr,
  uint32* resultLengthPtr, boolean TruncationIsAllowed)
{
  Std_ReturnType LddReturnValue;

  /* Storing the default return value */
  LddReturnValue = E_OK;

  /* Check if the result pointer is NULL */
  if (resultPtr == NULL_PTR)
  {
    #if (CSM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      CSM_CHECKSUMFINISH_SID, CSM_E_PARAM_PTR_INVALID);
    #endif
    LddReturnValue = E_NOT_OK;
  }

  if (LddReturnValue == E_OK)
  {
    /* Check if the result length pointer is NULL */
    if (resultLengthPtr == NULL_PTR)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_CHECKSUMFINISH_SID, CSM_E_PARAM_PTR_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* Check for invalid parameter */
    /* polyspace +1 MISRA-C3:D4.14,18.1,D4.1 RTE:IDP [Justified:Low] "The pointer is checked" */
    if (*resultLengthPtr == CSM_ZERO)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_CHECKSUMFINISH_SID, CSM_E_PARAM_INVALID);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if (((Csm_GddActiveChecksumService.ucServiceState
      & CSM_CHECKSUM_START) == CSM_CHECKSUM_START)
      || ((Csm_GddActiveChecksumService.ucServiceState
      & CSM_CHECKSUM_UPDATE) == CSM_CHECKSUM_UPDATE)
      || ((Csm_GddActiveChecksumService.ucServiceState
      & CSM_CHECKSUM_FINISH) == CSM_CHECKSUM_FINISH))
    {
      LddReturnValue = CSM_E_BUSY;
    }
  }

  if (LddReturnValue == E_OK)
  {
    if ((Csm_GddActiveChecksumService.ucServiceState
      & CSM_CHECKSUM_ACTIVE) != CSM_CHECKSUM_ACTIVE)
    {
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_CHECKSUMFINISH_SID, CSM_E_SERVICE_NOT_STARTED);
      #endif
      LddReturnValue = E_NOT_OK;
    }
  }

  if (LddReturnValue == E_OK)
  {
    /* changing the state to FINISH */
    Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_FINISH;

    /* Invoke respective primitive Finish function */
    /* polyspace-begin MISRA-C3:18.1 RTE:IDP RTE:COR [Justified:Low] "The pointer is generated by configuration tool" */
    LddReturnValue = Csm_GddActiveChecksumService.pActiveServiceConfig->
      PrimitiveFinishFct(cfgId, resultPtr, resultLengthPtr, TruncationIsAllowed);
    /* polyspace-end MISRA-C3:18.1 RTE:IDP RTE:COR */

    if (LddReturnValue == CSM_E_BUSY)
    {
      /* Do nothing. Previous request is not done */
    }
    else
    {
      if (Csm_GddActiveChecksumService.pActiveServiceConfig->CallbackFct
        == NULL_PTR)
      {
        #if (CSM_DEV_ERROR_DETECT == STD_ON)
        if (LddReturnValue == CSM_E_SMALL_BUFFER)
        {
          (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
            CSM_CHECKSUMFINISH_SID, CSM_E_BUFFER_TOO_SMALL);
        }
        #endif

        /* Setting the service state to idle irrespective of the result */
        Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_IDLE;
      }
      else
      {
        if (Csm_GddActiveChecksumService.pActiveServiceConfig->PrimitiveMainFct
          != NULL_PTR)
        {
          /* Push the Primitive Main function into the implemented stack */
          LddReturnValue = Csm_FunctionPush(Csm_GddActiveChecksumService.
            pActiveServiceConfig->PrimitiveMainFct);
        }
      }
    }
  }

  return (LddReturnValue);
}

/*******************************************************************************
** Function Name        : Csm_ChecksumCallbackNotification                    **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function will call the callback function as    **
**                        given in the configuration of Checksum              **
**                        service with the argument given by "Result".        **
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
**                        Csm_GddActiveChecksumService                        **
**                        Function(s) invoked: Det_ReportError                **
*******************************************************************************/
void Csm_ChecksumCallbackNotification(Std_ReturnType ddResult)
{
  switch (ddResult)
  {
  case CSM_E_BUSY:
    /* Do nothing */
    break;

  case E_OK:
    switch (Csm_GddActiveChecksumService.ucServiceState)
    {
    case CSM_CHECKSUM_START:
    case CSM_CHECKSUM_UPDATE:
      /* State is set to ACTIVE upon success */
      Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_ACTIVE;
      break;

    case CSM_CHECKSUM_FINISH:
      /* Setting the service state to idle irrespective of the result */
      Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_IDLE;
      break;

    default:
      /* Do nothing */
      break;
    }
    break;

  default:
    switch (Csm_GddActiveChecksumService.ucServiceState)
    {
    case CSM_CHECKSUM_START:
    case CSM_CHECKSUM_UPDATE:
      break;

    case CSM_CHECKSUM_FINISH:
      #if (CSM_DEV_ERROR_DETECT == STD_ON)
      if (ddResult == CSM_E_SMALL_BUFFER)
      {
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          CSM_CHECKSUMFINISH_SID, CSM_E_BUFFER_TOO_SMALL);
      }
      #endif
      break;

    default:
      /* Do nothing */
      break;
    }

    /* state is set to IDLE upon Failure */
    Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_IDLE;
    break;
  }
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveChecksumService.pActiveServiceConfig->CallbackFct
    != NULL_PTR)
  {
    /* notify the application by invoking the callback */
    Csm_GddActiveChecksumService.pActiveServiceConfig->
      CallbackFct(ddResult);
  }
}

/*******************************************************************************
** Function Name        : Csm_ChecksumServiceFinishNotification               **
**                                                                            **
** Service ID           : --                                                  **
**                                                                            **
** Description          : This function shall set the state of Checksum       **
**                        service to "idle".                                  **
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
**                               Csm_GddActiveChecksumService                 **
**                        Function(s) invoked: None                           **
*******************************************************************************/
void Csm_ChecksumServiceFinishNotification(void)
{
  /* Setting the state to IDLE */
  Csm_GddActiveChecksumService.ucServiceState = CSM_CHECKSUM_IDLE;
}

boolean Csm_ChecksumServiceHasCallback(void)
{
  boolean LblHasCallback;
  /* polyspace +1 MISRA-C3:18.1 RTE:IDP [Justified:Low] "The pointer is checked" */
  if (Csm_GddActiveChecksumService.pActiveServiceConfig->
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

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_CHECKSUM_STATUS == STD_ON) */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
