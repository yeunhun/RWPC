/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_FunctionStack.h                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Provides function prototypes and structure types for          **
**                          CSM_FunctionStack                                 **
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
** 1.0.7     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.6     19-Mar-2018   Sinil        Redmine #11930                        **
** 1.0.5     27-Feb-2017   Sinil        Redmine #7650                         **
** 1.0.4     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.3     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CSM_FUNCTIONSTACK_H
#define CSM_FUNCTIONSTACK_H
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define CSM_STACK_MAXSIZE                               (26)

typedef void (*Csm_FunctionPtrType)(void);

/* Declare a Stack structure */
typedef struct
{
  /* Define an array of structure of function pointers */
  Csm_FunctionPtrType paaFunctionPtr[CSM_STACK_MAXSIZE];

  /* Define stack top */
  uint8 ucTop;
} Csm_FunctionStackType;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global variable for array of structure of function pointers */
extern Csm_FunctionStackType Csm_GddFunctionStack;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

/*  Function for pushing function pointers on to Function stack*/
extern Std_ReturnType Csm_FunctionPush(Csm_FunctionPtrType funcPtr);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CSM_FUNCTIONSTACK_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
