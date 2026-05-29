/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutIcusAesEcbDecrypt.h                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - ICUS AES ECB Decrypt                                      **
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
** 2.6.3.0   24-Mar-2021   TamTV6       Redmine #18165                        **
** 1.0.1     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.0     14-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_AUTICUSAESECBDECRYPT_H
#define CRY_AUTICUSAESECBDECRYPT_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
#if (CSM_SYMBLOCK_AUTICUSAESECBDECRYPT == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_AutIcusAesEcbDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr);

extern Std_ReturnType Cry_AutIcusAesEcbDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr);

extern Std_ReturnType Cry_AutIcusAesEcbDecryptFinish(Csm_ConfigIdType cfgId);

extern void Cry_AutIcusAesEcbDecryptMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYMBLOCK_AUTICUSAESECBDECRYPT == STD_ON) */
#endif /* (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) */

#endif /* CRY_AUTICUSAESECBDECRYPT_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
