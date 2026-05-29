/*******************************************************************************
**                                                                            **
**  (C) 2018~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaePseudoRandomSeed.h                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - Autoever Pseudo Random Seed                               **
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
** 1.0.1     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.0     07-Nov-2018   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_HAEPSEUDORANDOMSEED_H
#define CRY_HAEPSEUDORANDOMSEED_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_RANDOM_SEED_STATUS == STD_ON)
#if (CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_HaePseudoRandomSeedStart(const void* cfgPtr);

extern Std_ReturnType Cry_HaePseudoRandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength);

extern Std_ReturnType Cry_HaePseudoRandomSeedFinish(Csm_ConfigIdType cfgId);

extern void Cry_HaePseudoRandomSeedMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON)  */
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON)  */

#endif /* CRY_HAEPSEUDORANDOMSEED_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
