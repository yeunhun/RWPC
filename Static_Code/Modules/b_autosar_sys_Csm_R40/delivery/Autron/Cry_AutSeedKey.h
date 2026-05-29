/*******************************************************************************
**                                                                            **
**  (C) 2015~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutSeedKey.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - Autron SeedKey                                            **
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
** 1.0.4     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.3     02-May-2016   Sinil        Redmine #4607                         **
** 1.0.0     10-Mar-2015   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_AUTSEEDKEY_H
#define CRY_AUTSEEDKEY_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_HASH_STATUS == STD_ON)
#if (CSM_HASH_AUTSEEDKEY == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern Std_ReturnType Cry_AutSeedKeyStart(const void* cfgPtr);

extern Std_ReturnType Cry_AutSeedKeyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength);

extern Std_ReturnType Cry_AutSeedKeyFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed);

extern void Cry_AutSeedKeyMainFunction(void);

#endif /* (CSM_HASH_AUTSEEDKEY == STATUS_ON) */
#endif /* (CSM_HASH_STATUS == STD_ON)  */

#endif /* CRY_AUTSEEDKEY_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
