/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutIcusCmacAesVerify.h                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - ICUS CMAC AES Verify                                      **
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
** 1.0.0     14-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_AUTICUSCMACAESVERIFY_H
#define CRY_AUTICUSCMACAESVERIFY_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_MAC_VERIFY_STATUS == STD_ON)
#if (CSM_MAC_AUTICUSCMACAESVERIFY == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_AutIcusCmacAesVerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr);

extern Std_ReturnType Cry_AutIcusCmacAesVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength);

extern Std_ReturnType Cry_AutIcusCmacAesVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr);

extern void Cry_AutIcusCmacAesVerifyMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_MAC_AUTICUSCMACAESVERIFY == STD_ON) */
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

#endif /* CRY_AUTICUSCMACAESVERIFY_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
