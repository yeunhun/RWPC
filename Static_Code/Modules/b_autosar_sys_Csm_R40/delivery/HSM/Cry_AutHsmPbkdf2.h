/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutHsmPbkdf2.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - HSM Pbkdf2                                                **
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
** 1.0.0     18-Apr-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_AUTHSMPBKDF2_H
#define CRY_AUTHSMPBKDF2_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_KEY_DERIVATION_STATUS == STD_ON)
#if (CSM_KEYDERIVE_AUTHSMPBKDF2 == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_AutHsmPbkdf2Start(const void* cfgPtr, uint32 keyLength,
  uint32 iterations);

extern Std_ReturnType Cry_AutHsmPbkdf2Update(Csm_ConfigIdType cfgId,
  const uint8* passwordPtr, uint32 passwordLength, const uint8* saltPtr,
  uint32 saltLength);

extern Std_ReturnType Cry_AutHsmPbkdf2Finish(Csm_ConfigIdType cfgId,
  Csm_SymKeyType* keyPtr);

extern void Cry_AutHsmPbkdf2MainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_KEYDERIVE_AUTHSMPBKDF2 == STD_ON) */
#endif /* (CSM_KEY_DERIVATION_STATUS == STD_ON) */


/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
#endif /* CRY_AUTHSMPBKDF2_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
