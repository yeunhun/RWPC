/*******************************************************************************
**                                                                            **
**  (C) 2015~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscAesCbcEncrypt.h                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - Escrypt AES CBC Encrypt                                   **
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
** 1.0.9     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.8     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.0.7     27-Feb-2017   Sinil        Redmine #7650                         **
** 1.0.6     09-Aug-2016   Sinil        Redmine #5693                         **
** 1.0.5     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.4     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.3     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.2     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.0     10-Mar-2015   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_ESCAESCBCENCRYPT_H
#define CRY_ESCAESCBCENCRYPT_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYM_ESCAESCBCENCRYPT == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_EscAesCbcEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength);

extern Std_ReturnType Cry_EscAesCbcEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr);

extern Std_ReturnType Cry_EscAesCbcEncryptFinish(Csm_ConfigIdType cfgId,
  uint8* cipherTextPtr, uint32* cipherTextLengthPtr);

extern void Cry_EscAesCbcEncryptMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SYM_ESCAESCBCENCRYPT == STD_ON) */
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

#endif /* CRY_ESCAESCBCENCRYPT_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
