/*******************************************************************************
**                                                                            **
**  (C) 2018~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaePkcs1V15Sha256SeedVerify.h                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - HAE HSM Pkcs1V15 Sha256 Seed Verify                       **
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
** 1.0.0     01-Nov-2018   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

#ifndef CRY_HAEPKCS1V15SHA256SEEDVERIFY_H
#define CRY_HAEPKCS1V15SHA256SEEDVERIFY_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_HAEPKCS1V15SHA256SEEDVERIFY == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_HaePkcs1V15Sha256SeedVerifyStart(const void* cfgPtr,
  const Csm_AsymPublicKeyType* keyPtr);

extern Std_ReturnType Cry_HaePkcs1V15Sha256SeedVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength);

extern Std_ReturnType Cry_HaePkcs1V15Sha256SeedVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType* resultPtr);

extern void Cry_HaePkcs1V15Sha256SeedVerifyMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SIGNATURE_HAEPKCS1V15SHA256SEEDVERIFY == STD_ON) */
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

#endif /* CRY_HAEPKCS1V15SHA256SEEDVERIFY_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
