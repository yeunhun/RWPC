/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FiM_Config.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Function Inhibition Manager Module                    **
**                                                                            **
**  PURPOSE   : Configurable const variable definition                        **
**              of Function Inhibition Manager                                **
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
** 1.0.1     24-Feb-2018   EK Kim        Changes made As per Redmine #11732   **
**                                                                            **
** 1.0.0     01-Jan-2013   Autron        Initial version                      **
*******************************************************************************/

#ifndef FIM_CONFIG_H
#define FIM_CONFIG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_FiM_Type.h"
#include "FiM_Cfg.h"        /* FiM Cfg Definition Header File */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define FIM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Total number of FIDs configured in FiM */
extern const FiM_FidsSizeType Fim_Total_Num_Of_Fids;

/* Total number of DEM events referred in FIM */
extern const FiM_EventsSizeType Fim_Total_Num_Of_Dem_Events;

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

extern FUNC(boolean, FIM_CODE)FiM_EventIdSearch(
  Dem_EventIdType LddEventId,
  P2VAR(FiM_EventsSizeType, AUTOMATIC, FIM_VAR)LpEventIndex
);

extern FUNC(boolean, FIM_CODE)FiM_FidSearch(
  FiM_FunctionIdType LddFid,
  P2VAR(FiM_FidsSizeType, AUTOMATIC, FIM_VAR)LddFidArrayIndex
);




#endif /* FIM_CONFIG_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
