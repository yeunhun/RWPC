/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Provides function prototypes to access the CSM services       **
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
** 1.0.7     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.6     21-Sep-2017   Sinil        Redmine #10038                        **
** 1.0.5     27-Feb-2017   Sinil        Redmine #7650                         **
** 1.0.4     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.3     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.2     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:8.5 [Not a defect:Low] "No Impact of this rule violation" */

#ifndef CSM_H
#define CSM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"            /* Header file for Csm types */
#include "Csm_Cfg.h"              /* Header file for configuration parameters */
#include "Csm_Cbk.h"              /* Header file for callback function
                                     prototypes */
#include "Csm_FunctionStack.h"    /* Header file for MainFunction stack */


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to indicate the initialization of the module*/
extern boolean Csm_GblInitStatus;
#define CSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

/* Function for initializing CSM */
extern void Csm_Init(void);

#if (CSM_VERSION_INFO_API == STD_ON)
/* Function for version information */
extern void Csm_GetVersionInfo(
  Std_VersionInfoType *versioninfo);
#endif /* (CSM_VERSION_INFO_API == STD_ON) */

/* Hash Interface */
#if (CSM_HASH_STATUS == STD_ON)
/* Function for starting the Hash service */
extern Std_ReturnType Csm_HashStart(Csm_ConfigIdType cfgId);

/* Function for feeding Hash service with user data */
extern Std_ReturnType Csm_HashUpdate(Csm_ConfigIdType cfgId,
  const uint8 *dataPtr, uint32 dataLength);

/* Function for finishing the Hash service */
extern Std_ReturnType Csm_HashFinish(Csm_ConfigIdType cfgId,
  uint8 *resultPtr, uint32 *resultLengthPtr, boolean TruncationIsAllowed);
#endif /* (CSM_HASH_STATUS == STD_ON) */

/* MAC interface */
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
/* Function for starting the MAC Generate service */
extern Std_ReturnType Csm_MacGenerateStart(
  Csm_ConfigIdType cfgId, const Csm_SymKeyType *keyPtr);

/* Function for feeding MAC Generate service with user data */
extern Std_ReturnType Csm_MacGenerateUpdate(
  Csm_ConfigIdType cfgId, const uint8 *dataPtr, uint32 dataLength);

/* Function for finishing the MAC Generate service */
extern Std_ReturnType Csm_MacGenerateFinish(
  Csm_ConfigIdType cfgId, uint8 *resultPtr, uint32 *resultLengthPtr,
  boolean TruncationIsAllowed);
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

#if (CSM_MAC_VERIFY_STATUS == STD_ON)
/* Function for starting the MAC Verify service */
extern Std_ReturnType Csm_MacVerifyStart(Csm_ConfigIdType cfgId,
  const Csm_SymKeyType *keyPtr);

/* Function for feeding MAC Verify service with user data */
extern Std_ReturnType Csm_MacVerifyUpdate(
  Csm_ConfigIdType cfgId, const uint8 *dataPtr, uint32 dataLength);

/* Function for finishing the MAC Verify service */
extern Std_ReturnType Csm_MacVerifyFinish(
  Csm_ConfigIdType cfgId, const uint8 *MacPtr, uint32 MacLength,
  Csm_VerifyResultType *resultPtr);
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/* Random interface */
#if (CSM_RANDOM_SEED_STATUS == STD_ON)
/* Function for starting the Random Seed service */
extern Std_ReturnType Csm_RandomSeedStart(
  Csm_ConfigIdType cfgId);

/* Function for feeding Random Seed service with user data */
extern Std_ReturnType Csm_RandomSeedUpdate(
  Csm_ConfigIdType cfgId, const uint8 *seedPtr, uint32 seedLength);

/* Function for finishing the Random Seed service */
extern Std_ReturnType Csm_RandomSeedFinish(
  Csm_ConfigIdType cfgId);
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON) */

#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
/* Function for Random Generate service */
extern Std_ReturnType Csm_RandomGenerate(Csm_ConfigIdType cfgId,
  uint8 *resultPtr, uint32 resultLength);
#endif /* (CSM_RANDOM_GENERATE_STATUS == STD_ON) */

/* Symmetrical Block */
#if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
/* Function for starting the Symmetrical Block Encryption service */
extern Std_ReturnType Csm_SymBlockEncryptStart(
  Csm_ConfigIdType cfgId, const Csm_SymKeyType *keyPtr);

/* Function for feeding Symmetrical Block Encryption service with user data */
extern Std_ReturnType Csm_SymBlockEncryptUpdate(
  Csm_ConfigIdType cfgId, const uint8 *plainTextPtr, uint32 plainTextLength,
  uint8 *cipherTextPtr, uint32 *cipherTextLengthPtr);

/* Function for finishing the Symmetrical Block Encryption service */
extern Std_ReturnType Csm_SymBlockEncryptFinish(
  Csm_ConfigIdType cfgId);
#endif /* (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
/* Function for starting the Symmetrical Block Decryption service */
extern Std_ReturnType Csm_SymBlockDecryptStart(
  Csm_ConfigIdType cfgId, const Csm_SymKeyType *keyPtr);

/* Function for feeding Symmetrical Block Decryption service with user data */
extern Std_ReturnType Csm_SymBlockDecryptUpdate(
  Csm_ConfigIdType cfgId, const uint8 * cipherTextPtr, uint32 cipherTextLength,
  uint8 *plainTextPtr, uint32 *plainTextLengthPtr);

/* Function for finishing the Symmetrical Block Decryption service */
extern Std_ReturnType Csm_SymBlockDecryptFinish(
  Csm_ConfigIdType cfgId);
#endif /* (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) */

/* Symmetrical interface */
#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
/* Function for starting the Symmetrical Encryption service */
extern Std_ReturnType Csm_SymEncryptStart(
  Csm_ConfigIdType cfgId, const Csm_SymKeyType *keyPtr,
  const uint8 *InitVectorPtr, uint32 InitVectorLength);

/* Function for feeding Symmetrical Encryption service with user data */
extern Std_ReturnType Csm_SymEncryptUpdate(
  Csm_ConfigIdType cfgId, const uint8 *plainTextPtr, uint32 plainTextLength,
  uint8 *cipherTextPtr, uint32 *cipherTextLengthPtr);

/* Function for finishing the Symmetrical Encryption service */
extern Std_ReturnType Csm_SymEncryptFinish(
  Csm_ConfigIdType cfgId, uint8 *cipherTextPtr, uint32 *cipherTextLengthPtr);
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_DECRYPT_STATUS == STD_ON)
/* Function for starting the Symmetrical Decryption service */
extern Std_ReturnType Csm_SymDecryptStart(
  Csm_ConfigIdType cfgId, const Csm_SymKeyType *keyPtr,
  const uint8 *InitVectorPtr, uint32 InitVectorLength);

/* Function for feeding Symmetrical Decryption service with user data */
extern Std_ReturnType Csm_SymDecryptUpdate(
  Csm_ConfigIdType cfgId, const uint8 *cipherTextPtr, uint32 cipherTextLength,
  uint8 *plainTextPtr, uint32 *plainTextLengthPtr);

/* Function for finishing the Symmetrical Decryption service */
extern Std_ReturnType Csm_SymDecryptFinish(
  Csm_ConfigIdType cfgId, uint8 *plainTextPtr, uint32 *plainTextLengthPtr);
#endif /* (CSM_SYM_DECRYPT_STATUS == STD_ON) */

#if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
/* Function for starting the Assymmetrical Encryption service */
extern Std_ReturnType Csm_AsymEncryptStart(
  Csm_ConfigIdType cfgId, const Csm_AsymPublicKeyType *keyPtr);

/* Function for feeding Assymmetrical Encryption service with user data */
extern Std_ReturnType Csm_AsymEncryptUpdate(
  Csm_ConfigIdType cfgId, const uint8 *plainTextPtr, uint32 plainTextLength,
  uint8 *cipherTextPtr, uint32 *cipherTextLengthPtr);

/* Function for finishing the Assymmetrical Encryption service */
extern Std_ReturnType Csm_AsymEncryptFinish(
  Csm_ConfigIdType cfgId, uint8 *cipherTextPtr, uint32 *cipherTextLengthPtr);
#endif /* (CSM_ASYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_ASYM_DECRYPT_STATUS == STD_ON)
/* Function for starting the Assymmetrical Decryption service */
extern Std_ReturnType Csm_AsymDecryptStart(
  Csm_ConfigIdType cfgId, const Csm_AsymPrivateKeyType *keyPtr);

/* Function for feeding Assymmetrical Decryption service with user data */
extern Std_ReturnType Csm_AsymDecryptUpdate(
  Csm_ConfigIdType cfgId, const uint8 *cipherTextPtr, uint32 cipherTextLength,
  uint8 *plainTextPtr, uint32 *plainTextLengthPtr);

/* Function for finishing the Assymmetrical Decryption service */
extern Std_ReturnType Csm_AsymDecryptFinish(
  Csm_ConfigIdType cfgId, uint8 *plainTextPtr, uint32 *plainTextLengthPtr);
#endif /* (CSM_ASYM_DECRYPT_STATUS == STD_ON) */

#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
/* Function for starting the Signature Generate service */
extern Std_ReturnType Csm_SignatureGenerateStart(
  Csm_ConfigIdType cfgId, const Csm_AsymPrivateKeyType *keyPtr);

/* Function for feeding Signature Generate service with user data */
extern Std_ReturnType Csm_SignatureGenerateUpdate(
  Csm_ConfigIdType cfgId, const uint8 *dataPtr, uint32 dataLength);

/* Function for finishing the Signature Generate service */
extern Std_ReturnType Csm_SignatureGenerateFinish(
  Csm_ConfigIdType cfgId, uint8 *resultPtr, uint32 *resultLengthPtr);
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
/* Function for starting the Signature Verify service */
extern Std_ReturnType Csm_SignatureVerifyStart(
  Csm_ConfigIdType cfgId, const Csm_AsymPublicKeyType *keyPtr);

/* Function for feeding Signature Verify service with user data */
extern Std_ReturnType Csm_SignatureVerifyUpdate(
  Csm_ConfigIdType cfgId, const uint8 *dataPtr, uint32 dataLength);

/* Function for finishing the Signature Verify service */
extern Std_ReturnType Csm_SignatureVerifyFinish(
  Csm_ConfigIdType cfgId, const uint8 *signaturePtr, uint32 signatureLength,
  Csm_VerifyResultType *resultPtr);
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/* Checksum interface */
#if (CSM_CHECKSUM_STATUS == STD_ON)
/* Function for starting the Checksum service */
extern Std_ReturnType Csm_ChecksumStart(Csm_ConfigIdType cfgId);

/* Function for feeding Checksum service with user data */
extern Std_ReturnType Csm_ChecksumUpdate(Csm_ConfigIdType cfgId,
  const uint8 *dataPtr, uint32 dataLength);

/* Function for finishing the Checksum service */
extern Std_ReturnType Csm_ChecksumFinish(Csm_ConfigIdType cfgId,
  uint8 *resultPtr, uint32 *resultLengthPtr, boolean TruncationIsAllowed);
#endif /* (CSM_CHECKSUM_STATUS == STD_ON) */

/* Key Derivation */
#if (CSM_KEY_DERIVATION_STATUS == STD_ON)
/* Function for starting the Key Derive service */
extern Std_ReturnType Csm_KeyDeriveStart(Csm_ConfigIdType cfgId,
  uint32 keyLength, uint32 iterations);

/* Function for feeding Key Derive service with user data */
extern Std_ReturnType Csm_KeyDeriveUpdate(
  Csm_ConfigIdType cfgId, const uint8 *passwordPtr, uint32 passwordLength,
  const uint8 *saltPtr, uint32 saltLength);

/* Function for finishing the Key Derive service */
extern Std_ReturnType Csm_KeyDeriveFinish(
  Csm_ConfigIdType cfgId, Csm_SymKeyType *keyPtr);
#endif /* (CSM_KEY_DERIVATION_STATUS == STD_ON) */

/* Key derivation sym key */
#if (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON)
/* Function for starting the Key Derive Symmetrical Key service */
extern Std_ReturnType Csm_KeyDeriveSymKey(
  Csm_ConfigIdType cfgId, const Csm_SymKeyType *baseKeyPtr,
  const uint8 *customisationValPtr, uint32 customisationValLength,
  Csm_SymKeyType * derivedKeyPtr);
#endif /* (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON) */

/* Key Exchange CalcPubVal */
#if (CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON)
/* Function for starting the public value calculation service */
extern Std_ReturnType Csm_KeyExchangeCalcPubVal(
  Csm_ConfigIdType cfgId, const Csm_KeyExchangeBaseType *basePtr,
  const Csm_KeyExchangePrivateType *privateValuePtr, uint8 * publicValuePtr,
  uint32 *publicValueLengthPtr);
#endif /* (CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON) */

/* Key Exchange CalcSecret */
#if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON)
/* Function for starting the key exchange service */
extern Std_ReturnType Csm_KeyExchangeCalcSecretStart(
  Csm_ConfigIdType cfgId, const Csm_KeyExchangeBaseType *basePtr,
  const Csm_KeyExchangePrivateType *privateValuePtr);

/* Function for feeding key exchange service with user data */
extern Std_ReturnType Csm_KeyExchangeCalcSecretUpdate(
  Csm_ConfigIdType cfgId, const uint8 *partnerPublicValuePtr,
  uint32 partnerPublicValueLength);

/* Function for finishing the key exchange service */
extern Std_ReturnType Csm_KeyExchangeCalcSecretFinish(
  Csm_ConfigIdType cfgId, uint8 *sharedSecretPtr,
  uint32 *sharedSecretLengthPtr, boolean TruncationIsAllowed);
#endif /* (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) */

/* Key Exchange CalcSymKey */
#if (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON)
/* Function for starting the key exchange service */
extern Std_ReturnType Csm_KeyExchangeCalcSymKeyStart(
  Csm_ConfigIdType cfgId, const Csm_KeyExchangeBaseType *basePtr,
  const Csm_KeyExchangePrivateType *privateValuePtr);

/* Function for feeding key exchange service with user data */
extern Std_ReturnType Csm_KeyExchangeCalcSymKeyUpdate(
  Csm_ConfigIdType cfgId, const uint8 * partnerPublicValuePtr,
  uint32 partnerPublicValueLength);

/* Function for finishing the key exchange service */
extern Std_ReturnType Csm_KeyExchangeCalcSymKeyFinish(
  Csm_ConfigIdType cfgId, Csm_SymKeyType *sharedKeyPtr);
#endif /* (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON) */

/* Symmetrical Key Extraction */
#if (CSM_SYM_KEY_EXTRACT_STATUS == STD_ON)
/* Function for starting the symmetrical key extraction service */
extern Std_ReturnType Csm_SymKeyExtractStart(
  Csm_ConfigIdType cfgId);

/* Function for feeding symmetrical key extraction service with user data */
extern Std_ReturnType Csm_SymKeyExtractUpdate(
  Csm_ConfigIdType cfgId, const uint8 *dataPtr, uint32 dataLength);

/* Function for finishing the symmetrical key extraction service */
extern Std_ReturnType Csm_SymKeyExtractFinish(
  Csm_ConfigIdType cfgId, Csm_SymKeyType *keyPtr);
#endif /* (CSM_SYM_KEY_EXTRACT_STATUS == STD_ON) */

/* Symmetrical Key Wrap Sym Key */
#if (CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON)
/* Function for starting the symmetrical key wrapping service */
extern Std_ReturnType Csm_SymKeyWrapSymStart(
  Csm_ConfigIdType cfgId, const Csm_SymKeyType *keyPtr,
  const Csm_SymKeyType *wrappingKeyPtr);

/* Function for feeding symmetrical key wrapping service with user data */
extern Std_ReturnType Csm_SymKeyWrapSymUpdate(
  Csm_ConfigIdType cfgId, uint8 *dataPtr, uint32 *dataLengthPtr);

/* Function for finishing the symmetrical key wrapping service */
extern Std_ReturnType Csm_SymKeyWrapSymFinish(
  Csm_ConfigIdType cfgId);
#endif /* (CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON) */

/* Symmetrical Key Wrap Asym Key */
#if (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON)
/* Function for starting the symmetrical key wrapping service */
extern Std_ReturnType Csm_SymKeyWrapAsymStart(
  Csm_ConfigIdType cfgId, const Csm_SymKeyType *keyPtr,
  const Csm_AsymPublicKeyType *wrappingKeyPtr);

/* Function for feeding symmetrical key wrapping service with user data */
extern Std_ReturnType Csm_SymKeyWrapAsymUpdate(
  Csm_ConfigIdType cfgId, uint8 *dataPtr, uint32 *dataLengthPtr);

/* Function for finishing the symmetrical key wrapping service */
extern Std_ReturnType Csm_SymKeyWrapAsymFinish(
  Csm_ConfigIdType cfgId);
#endif /* (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON) */

/* Asymmetrical PubKeyExtraction */
#if (CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON)
/* Function for starting the asymmetrical public key extraction service */
extern Std_ReturnType Csm_AsymPublicKeyExtractStart(
  Csm_ConfigIdType cfgId);

/* Function for feeding asymmetrical public key extraction service with the user
 *data */
extern Std_ReturnType Csm_AsymPublicKeyExtractUpdate(
  Csm_ConfigIdType cfgId, const uint8 *dataPtr, uint32 dataLength);

/* Function for finishing the asymmetrical public key extraction service */
extern Std_ReturnType Csm_AsymPublicKeyExtractFinish(
  Csm_ConfigIdType cfgId, Csm_AsymPublicKeyType *keyPtr);
#endif /* (CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON) */

/* Asymmetrical PrivKeyExtraction */
#if (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON)
/* Function for starting the asymmetrical private key extraction service */
extern Std_ReturnType Csm_AsymPrivateKeyExtractStart(
  Csm_ConfigIdType cfgId);

/* Function for feeding asymmetrical private key extraction service with the
 *user data */
extern Std_ReturnType Csm_AsymPrivateKeyExtractUpdate(
  Csm_ConfigIdType cfgId, const uint8 *dataPtr, uint32 dataLength);

/* Function for finishing the asymmetrical private key extraction service */
extern Std_ReturnType Csm_AsymPrivateKeyExtractFinish(
  Csm_ConfigIdType cfgId, Csm_AsymPrivateKeyType *keyPtr);
#endif /* (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON) */

/* Asym Wrap using Sym key */
#if (CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON)
/* Function for starting the asymmetrical key wrapping service */
extern Std_ReturnType Csm_AsymPrivateKeyWrapSymStart(
  Csm_ConfigIdType cfgId, const Csm_AsymPrivateKeyType *keyPtr,
  const Csm_SymKeyType *wrappingKeyPtr);

/* Function for feeding asymmetrical key wrapping service with user data */
extern Std_ReturnType Csm_AsymPrivateKeyWrapSymUpdate(
  Csm_ConfigIdType cfgId, uint8 *dataPtr, uint32 *dataLengthPtr);

/* Function for finishing the asymmetrical key wrapping service */
extern Std_ReturnType Csm_AsymPrivateKeyWrapSymFinish(
  Csm_ConfigIdType cfgId);
#endif /* (CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON) */

/* Asym Wrap using Aym key */
#if (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON)
/* Function for starting the asymmetrical key wrapping service */
extern Std_ReturnType Csm_AsymPrivateKeyWrapAsymStart(
  Csm_ConfigIdType cfgId, const Csm_AsymPrivateKeyType *keyPtr,
  const Csm_AsymPublicKeyType *wrappingKeyPtr);

/* Function for feeding asymmetrical key wrapping service with user data */
extern Std_ReturnType Csm_AsymPrivateKeyWrapAsymUpdate(
  Csm_ConfigIdType cfgId, uint8 *dataPtr, uint32 *dataLengthPtr);

/* Function for finishing asymmetrical key wrapping service */
extern Std_ReturnType Csm_AsymPrivateKeyWrapAsymFinish(
  Csm_ConfigIdType cfgId);
#endif /* (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON) */

/* Function for process the requested services */
extern void Csm_MainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CSM_H */

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:8.5 [Not a defect:Low] "No Impact of this rule violation" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
