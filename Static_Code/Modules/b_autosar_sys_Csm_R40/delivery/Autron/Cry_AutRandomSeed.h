/*******************************************************************************
**                                                                            **
**  (C) 2015~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutRandomSeed.h                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - Autron Random Seed                                        **
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
** 1.0.10    22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.9     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.0.8     27-Feb-2017   Sinil        Redmine #7650                         **
** 1.0.7     09-Aug-2016   Sinil        Redmine #5693                         **
** 1.0.6     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.5     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.4     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.3     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.2     02-May-2016   Sinil        Redmine #4607                         **
** 1.0.0     10-Mar-2015   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_AUTRANDOMSEED_H
#define CRY_AUTRANDOMSEED_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_RANDOM_SEED_STATUS == STD_ON)
#if (CSM_RANDOM_AUTRANDOMSEED == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_AutRandomSeedStart(const void* cfgPtr);

extern Std_ReturnType Cry_AutRandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength);

extern Std_ReturnType Cry_AutRandomSeedFinish(Csm_ConfigIdType cfgId);

extern void Cry_AutRandomSeedMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_RANDOM_AUTRANDOMSEED == STD_ON)  */
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON)  */

#endif /* CRY_AUTRANDOMSEED_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
