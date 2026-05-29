/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmEcdh.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - HSM Ecdh                                                  **
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
** 1.0.1     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.0     23-Mar-2020   EK Kim       Initial version                      **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

#ifndef CRY_HAEHSMECDH_H
#define CRY_HAEHSMECDH_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON)
#if (CSM_KEYEXCHANGECALC_SECRET_HAEHSMECDH == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_HaeHsmEcdhStart(const void* cfgPtr,
  const Csm_KeyExchangeBaseType* basePtr,
  const Csm_KeyExchangePrivateType* privateValuePtr);

extern Std_ReturnType Cry_HaeHsmEcdhUpdate(Csm_ConfigIdType cfgId,
  const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength);

extern Std_ReturnType Cry_HaeHsmEcdhFinish(Csm_ConfigIdType cfgId,
  uint8* sharedSecretPtr, uint32* sharedSecretLengthPtr,
  boolean TruncationIsAllowed);

extern void Cry_HaeHsmEcdhMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_KEYEXCHANGECALC_SECRET_HAEHSMECDH == STD_ON) */
#endif /* (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) */

#endif /* CRY_HAEHSMECDH_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
