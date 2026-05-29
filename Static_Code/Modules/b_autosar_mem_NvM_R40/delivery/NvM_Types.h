/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_Types.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Provision of Type Definitions.                                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date           By          Description                         **
********************************************************************************
** 1.3.4       25-Sep-2019   Yun  YJ      Redmine #19313                      **
** 1.1.8       20-Sep-2017    Yun  YJ     Redmine #9669                       **
** 1.1.7       09-Jul-2015    Song CY     Justify MISRA-Rule Violation        **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/

#ifndef NVM_TYPES_H
#define NVM_TYPES_H
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*
 polyspace-begin MISRA-C3:1.1:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard-Chap 5.1.2)
 polyspace-begin MISRA-C3:2.5 [Justified:Low] "Used according to configuration" 
 polyspace-begin MISRA-C3:D4.9 [Justified:Low] "Not a defect"
 */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_NvM_Type.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/* MACROS for API configuration classes */
#define NVM_API_CONFIG_CLASS_1        0
#define NVM_API_CONFIG_CLASS_2        1
#define NVM_API_CONFIG_CLASS_3        2

typedef enum
{
  NVM_BLOCK_NATIVE = 0,
  NVM_BLOCK_REDUNDANT,
  NVM_BLOCK_DATASET
} NvM_BlockManagementType;

typedef enum
{
  NVM_OPSTATUS_UNINIT = 0,
  NVM_OPSTATUS_IDLE,
  NVM_OPSTATUS_BUSY
} NvM_OpStatusType;

/* Macro for Unused parameter */
/* polyspace +3 MISRA-C3:19.7:Not a defect:Justify with annotations> Not a defect */
/* polyspace +2 MISRA-C3:D4.9 [Justified:Low] "Not a defect" */
#define NVM_UNUSED(x)       do{if((uint8)(x) != (uint8)NVM_ZERO) {}} while(0)
/* polyspace +3 MISRA-C3:19.7:Not a defect:Justify with annotations> Not a defect */
/* polyspace +2 MISRA-C3:D4.9 [Justified:Low] "Not a defect" */
#define NVM_UNUSED_PTR(x)   do{if((x) != NULL_PTR) {}} while(0)

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/*
 polyspace-end MISRA-C3:D4.9 [Justified:Low] "Not a defect"
 polyspace-end MISRA-C3:2.5 [Justified:Low] "Used according to configuration"
 polyspace-end MISRA-C3:1.1:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard-Chap 5.1.2)
*/

#endif /* NVM_TYPES_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
