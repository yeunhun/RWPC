/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_AutCsecCommon.h                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - CSEC Common header                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 2.6.3.0   24-Mar-2021   TamTV6       Redmine #18165                        **
** 1.0.0     27-May-2019   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_AUTCSECCOMMON_H
#define CRY_AUTCSECCOMMON_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
typedef enum
{
  CRY_AUTCSEC_RANDOMSEED,
  CRY_AUTCSEC_RANDOMGENERATE,
  CRY_AUTCSEC_AESECBENC,
  CRY_AUTCSEC_AESECBDEC,
  CRY_AUTCSEC_AESCBCENC,
  CRY_AUTCSEC_AESCBCDEC,
  CRY_AUTCSEC_CMACAESGEN,
  CRY_AUTCSEC_CMACASEVER
} Cry_AutCsecAlgorithmType;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern void Cry_AutCsecInit(Cry_AutCsecAlgorithmType algorithm);

#if (CSM_RANDOM_SEED_STATUS == STD_ON) && (CSM_RANDOM_AUTCSECRANDOMSEED == STD_ON)
extern Std_ReturnType Cry_AutCsecRandomSeedStart(const void* cfgPtr);

extern Std_ReturnType Cry_AutCsecRandomSeedUpdate(Csm_ConfigIdType cfgId,
  const uint8* seedPtr, uint32 seedLength);

extern Std_ReturnType Cry_AutCsecRandomSeedFinish(Csm_ConfigIdType cfgId);

extern void Cry_AutCsecRandomSeedMainFunction(void);
#endif

#if (CSM_RANDOM_GENERATE_STATUS == STD_ON) && (CSM_RANDOM_AUTCSECRANDOMGENERATE == STD_ON)
extern Std_ReturnType Cry_AutCsecRandomGenerate(const void* cfgPtr,
  uint8* resultPtr, uint32 resultLength);

extern void Cry_AutCsecRandomGenerateMainFunction(void);
#endif

#if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) && (CSM_SYMBLOCK_AUTCSECAESECBENCRYPT == STD_ON)
extern Std_ReturnType Cry_AutCsecAesEcbEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr);

extern Std_ReturnType Cry_AutCsecAesEcbEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32* cipherTextLengthPtr);

extern Std_ReturnType Cry_AutCsecAesEcbEncryptFinish(Csm_ConfigIdType cfgId);

extern void Cry_AutCsecAesEcbEncryptMainFunction(void);
#endif

#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) && (CSM_SYMBLOCK_AUTCSECAESECBDECRYPT == STD_ON)
extern Std_ReturnType Cry_AutCsecAesEcbDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr);

extern Std_ReturnType Cry_AutCsecAesEcbDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr);

extern Std_ReturnType Cry_AutCsecAesEcbDecryptFinish(Csm_ConfigIdType cfgId);

extern void Cry_AutCsecAesEcbDecryptMainFunction(void);
#endif

#if (CSM_SYM_ENCRYPT_STATUS == STD_ON) && (CSM_SYM_AUTCSECAESCBCENCRYPT == STD_ON)
extern Std_ReturnType Cry_AutCsecAesCbcEncryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength);

extern Std_ReturnType Cry_AutCsecAesCbcEncryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* plainTextPtr, uint32 plainTextLength, uint8* cipherTextPtr,
  uint32 *cipherTextLengthPtr);

extern Std_ReturnType Cry_AutCsecAesCbcEncryptFinish(Csm_ConfigIdType cfgId,
  uint8* cipherTextPtr, uint32* cipherTextLengthPtr);

extern void Cry_AutCsecAesCbcEncryptMainFunction(void);
#endif

#if (CSM_SYM_DECRYPT_STATUS == STD_ON) && (CSM_SYM_AUTCSECAESCBCDECRYPT == STD_ON)
extern Std_ReturnType Cry_AutCsecAesCbcDecryptStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
  uint32 InitVectorLength);

extern Std_ReturnType Cry_AutCsecAesCbcDecryptUpdate(Csm_ConfigIdType cfgId,
  const uint8* cipherTextPtr, uint32 cipherTextLength, uint8* plainTextPtr,
  uint32* plainTextLengthPtr);

extern Std_ReturnType Cry_AutCsecAesCbcDecryptFinish(Csm_ConfigIdType cfgId,
  uint8* plainTextPtr, uint32* plainTextLengthPtr);

extern void Cry_AutCsecAesCbcDecryptMainFunction(void);
#endif

#if (CSM_MAC_GENERATE_STATUS == STD_ON) && (CSM_MAC_AUTCSECCMACAESGENERATE == STD_ON)
extern Std_ReturnType Cry_AutCsecCmacAesGenerateStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr);

extern Std_ReturnType Cry_AutCsecCmacAesGenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength);

extern Std_ReturnType Cry_AutCsecCmacAesGenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed);

extern void Cry_AutCsecCmacAesGenerateMainFunction(void);
#endif

#if (CSM_MAC_VERIFY_STATUS == STD_ON) && (CSM_MAC_AUTCSECCMACAESVERIFY == STD_ON)
extern Std_ReturnType Cry_AutCsecCmacAesVerifyStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr);

extern Std_ReturnType Cry_AutCsecCmacAesVerifyUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength);

extern Std_ReturnType Cry_AutCsecCmacAesVerifyFinish(Csm_ConfigIdType cfgId,
  const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr);

extern void Cry_AutCsecCmacAesVerifyMainFunction(void);
#endif

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CRY_AUTCSECCOMMON_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
