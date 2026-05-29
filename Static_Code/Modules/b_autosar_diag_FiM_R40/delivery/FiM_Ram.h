/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FiM_Ram.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : c Header for Fim_Ram.c                                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 1.0.3     30-09-2016    Autron        Redmine #5057                        **
**                                                                            **
** 1.0.2     14-01-2013    Autron        Initial version                      **
*******************************************************************************/
#ifndef FIM_RAM_H
#define FIM_RAM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "FiM_PCTypes.h"  /* PCTypes header file */

/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/

#define FIM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global Variable to store FIM Initialization status */
extern VAR(boolean, FIM_VAR_POWER_ON_INIT) FiM_GblInitStatus;
#define FIM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"


#define FIM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global array to store FID permission state */
/* polyspace +3 MISRA-C3:8.11 [Justified:Low] "Not a defect" */
/* polyspace +2 MISRA-C3:8.5 [Justified:Low] "Not a defect" */
extern VAR(boolean, FIM_VAR_NOINIT)
  FiM_GaaFidPermissionState[];
#define FIM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define FIM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array to store inhibition counter for all FID’s */
/* polyspace +3 MISRA-C3:8.11 [Justified:Low] "Not a defect" */
/* polyspace +2 MISRA-C3:8.5 [Justified:Low] "Not a defect" */
extern VAR(FiM_FidsSizeType, FIM_VAR_NOINIT)
  FiM_GaaFidInhibitCounter[];
#define FIM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* End of FIM_RAM_H */

/* polyspace-end MISRA-C3:20.1 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
