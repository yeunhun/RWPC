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
** 1.0.2     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.1     09-May-2018   Sinil        Redmine #12635                        **
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_AUTHSMECDH_H
#define CRY_AUTHSMECDH_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON)
#if (CSM_KEYEXCHANGECALC_SECRET_AUTHSMECDH == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_AutHsmEcdhStart(const void* cfgPtr,
  const Csm_KeyExchangeBaseType* basePtr,
  const Csm_KeyExchangePrivateType* privateValuePtr);

extern Std_ReturnType Cry_AutHsmEcdhUpdate(Csm_ConfigIdType cfgId,
  const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength);

extern Std_ReturnType Cry_AutHsmEcdhFinish(Csm_ConfigIdType cfgId,
  uint8* sharedSecretPtr, uint32* sharedSecretLengthPtr,
  boolean TruncationIsAllowed);

extern void Cry_AutHsmEcdhMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_KEYEXCHANGECALC_SECRET_AUTHSMECDH == STD_ON) */
#endif /* (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) */

#endif /* CRY_AUTHSMECDH_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
