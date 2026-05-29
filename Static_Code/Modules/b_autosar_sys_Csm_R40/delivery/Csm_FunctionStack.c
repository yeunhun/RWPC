/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_FunctionStack.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CSM Function Stack                          **
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
** 1.2.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.2     19-Mar-2018   Sinil        Redmine #11930                        **
** 1.2.1     21-Sep-2017   Sinil        Redmine #10038                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198                         **
** 1.0.6     09-Aug-2016   Sinil        Redmine #5760                         **
** 1.0.5     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.4     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.3     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.2     05-Jan-2016   Sinil        Use const macro                       **
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
#include "SchM_Csm.h"             /* Header File for CSM SchM Functions */
#if (CSM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Header file for DET */
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global variable for array of structure of function pointers */
Csm_FunctionStackType Csm_GddFunctionStack;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Csm_FunctionPush                                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Function to add an element to the stack.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : funcPtr                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: request successful                            **
**                        E_NOT_OK: request failed                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Csm_GddFunctionStack          **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_FUNCTION_PTR_PROTECTION              **
**                        SchM_Exit_Csm_FUNCTION_PTR_PROTECTION               **
*******************************************************************************/
Std_ReturnType Csm_FunctionPush(Csm_FunctionPtrType funcPtr)
{
  Std_ReturnType LddReturnValue;

  /* Entering into the Protected area */
  SchM_Enter_Csm_FUNCTION_PTR_PROTECTION();

  /* Check if the stack top reached the maximum size */
  if (Csm_GddFunctionStack.ucTop < CSM_STACK_MAXSIZE)
  {
    /* Insert data on to stack top */
    Csm_GddFunctionStack.paaFunctionPtr[Csm_GddFunctionStack.ucTop] = funcPtr;

    /* Increment Stack top by 1 */
    Csm_GddFunctionStack.ucTop = Csm_GddFunctionStack.ucTop + CSM_ONE;

    /* Set the return value to E_OK */
    LddReturnValue = E_OK;
  }
  else
  {
    /* Set the return value to E_NOT_OK */
    LddReturnValue = E_NOT_OK;
  }

  /* Exiting Protected area */
  SchM_Exit_Csm_FUNCTION_PTR_PROTECTION();

  return (LddReturnValue);
}

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
