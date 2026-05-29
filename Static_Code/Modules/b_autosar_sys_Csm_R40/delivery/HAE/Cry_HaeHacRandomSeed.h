/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHacRandomSeed.h                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - Autoever HAC Random Seed                                  **
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
** 1.0.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.2     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.0.1     20-Sep-2017   Sinil        Redmine #10034                        **
** 1.0.0     27-Feb-2017   Sinil        Initial version, Redmine #7651        **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_HAEHACRANDOMSEED_H
#define CRY_HAEHACRANDOMSEED_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_RANDOM_SEED_STATUS == STD_ON)
#if (CSM_RANDOM_HAEHACRANDOMSEED == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_HaeHacRandomSeedStart(const void* cfgPtr);

extern Std_ReturnType Cry_HaeHacRandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength);

extern Std_ReturnType Cry_HaeHacRandomSeedFinish(Csm_ConfigIdType cfgId);

extern void Cry_HaeHacRandomSeedMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_RANDOM_HAEHACRANDOMSEED == STD_ON)  */
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON)  */

#endif /* CRY_HAEHACRANDOMSEED_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
