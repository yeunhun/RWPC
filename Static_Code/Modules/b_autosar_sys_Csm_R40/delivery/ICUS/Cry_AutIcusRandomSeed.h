/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutIcusRandomSeed.h                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - ICUS Random Seed                                          **
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
** 1.0.0     27-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_AUTICUSRANDOMSEED_H
#define CRY_AUTICUSRANDOMSEED_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_RANDOM_SEED_STATUS == STD_ON)
#if (CSM_RANDOM_AUTICUSRANDOMSEED == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_AutIcusRandomSeedStart(const void* cfgPtr);

extern Std_ReturnType Cry_AutIcusRandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength);

extern Std_ReturnType Cry_AutIcusRandomSeedFinish(Csm_ConfigIdType cfgId);

extern void Cry_AutIcusRandomSeedMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_RANDOM_AUTICUSRANDOMSEED == STD_ON)  */
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON)  */

#endif /* CRY_AUTICUSRANDOMSEED_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
