/*******************************************************************************
**                                                                            **
**  (C) 2016~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Cbk.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Provides callback function prototypes to be used by the       **
**              underlying cryptographic library modules                      **
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
** 1.0.9     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.8     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.7     19-Mar-2018   Sinil        Redmine #11930                        **
** 1.0.6     21-Sep-2017   Sinil        Redmine #10040                        **
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
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

#ifndef CSM_CBK_H
#define CSM_CBK_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"            /* For AUTOSAR Standard types */
#include "Csm_Cfg.h"              /* Header file for configuration parameters */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

/* Hash Interface */
#if (CSM_HASH_STATUS == STD_ON)
/* Callback notification function for Hash */
extern void Csm_HashCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of Hash service to "idle" */
extern void Csm_HashServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_HashServiceHasCallback(void);
#endif /* (CSM_HASH_STATUS == STD_ON) */

/* MAC Interface */
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
/* Callback notification function for Mac Generate */
extern void Csm_MacGenerateCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of Mac Generate to "idle" */
extern void Csm_MacGenerateServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_MacGenerateServiceHasCallback(void);
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

#if (CSM_MAC_VERIFY_STATUS == STD_ON)
/* Callback notification function for Mac Verify */
extern void Csm_MacVerifyCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of Mac Verify to "idle" */
extern void Csm_MacVerifyServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_MacVerifyServiceHasCallback(void);
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/* Random seed Interface */
#if (CSM_RANDOM_SEED_STATUS == STD_ON)
/* Callback notification function for Random Seed */
extern void Csm_RandomSeedCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of Random Seed to "idle" */
extern void Csm_RandomSeedServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_RandomSeedServiceHasCallback(void);
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON) */

#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
/* Callback notification function for Random Generate */
extern void Csm_RandomGenerateCallbackNotification(Std_ReturnType ddResult);

/* function for checking asynchronous behavior of service */
extern boolean Csm_RandomGenerateServiceHasCallback(void);
#endif /* (CSM_RANDOM_GENERATE_STATUS == STD_ON) */

/* Symmetrical Block Encryption */
#if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
/* Callback notification function for symmetrical block encrypt */
extern void Csm_SymBlockEncryptCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of symmetrical block encrypt to "idle" */
extern void Csm_SymBlockEncryptServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_SymBlockEncryptServiceHasCallback(void);
#endif /* (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
/* Callback notification function for symmetrical block Decrypt */
extern void Csm_SymBlockDecryptCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of symmetrical block decrypt to "idle" */
extern void Csm_SymBlockDecryptServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_SymBlockDecryptServiceHasCallback(void);
#endif /* (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) */

/* Symmetrical Interface */
#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
/* Callback notification function for symmetrical encrypt */
extern void Csm_SymEncryptCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of symmetrical encrypt to "idle" */
extern void Csm_SymEncryptServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_SymEncryptServiceHasCallback(void);
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_DECRYPT_STATUS == STD_ON)
/* Callback notification function for symmetrical decrypt */
extern void Csm_SymDecryptCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of symmetrical decrypt to "idle" */
extern void Csm_SymDecryptServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_SymDecryptServiceHasCallback(void);
#endif /* (CSM_SYM_DECRYPT_STATUS == STD_ON) */

/* Asymmetrical Interface */
#if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
/* Callback notification function for asymmetrical encryption */
extern void Csm_AsymEncryptCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of asymmetrical encryption to "idle" */
extern void Csm_AsymEncryptServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_AsymEncryptServiceHasCallback(void);
#endif /* (CSM_ASYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_ASYM_DECRYPT_STATUS == STD_ON)
/* Callback notification function for asymmetrical decryption */
extern void Csm_AsymDecryptCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of asymmetrical decryption to "idle" */
extern void Csm_AsymDecryptServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_AsymDecryptServiceHasCallback(void);
#endif /* (CSM_ASYM_DECRYPT_STATUS == STD_ON) */

/* Signature Interface */
#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
/* Callback notification function for Signature Generate */
extern void Csm_SignatureGenerateCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of Signature Generate to "idle" */
extern void Csm_SignatureGenerateServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_SignatureGenerateServiceHasCallback(void);
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
/* Callback notification function for Signature Verify */
extern void Csm_SignatureVerifyCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of Signature Verify to "idle" */
extern void Csm_SignatureVerifyServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_SignatureVerifyServiceHasCallback(void);
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/* Checksum Interface */
#if (CSM_CHECKSUM_STATUS == STD_ON)
/* Callback notification function for Checksum */
extern void Csm_ChecksumCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of Checksum to "idle" */
extern void Csm_ChecksumServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_ChecksumServiceHasCallback(void);
#endif /* (CSM_CHECKSUM_STATUS == STD_ON) */

/* Key Derivation interface */
#if (CSM_KEY_DERIVATION_STATUS == STD_ON)
/* Callback notification function for key derivation */
extern void Csm_KeyDeriveCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of key derivation to "idle" */
extern void Csm_KeyDeriveServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_KeyDeriveServiceHasCallback(void);
#endif /* (CSM_KEY_DERIVATION_STATUS == STD_ON) */

/* KeyDeriveSymKey */
#if (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON)
/* Callback notification function for key derivation from key service */
extern void Csm_KeyDeriveSymKeyCallbackNotification(Std_ReturnType ddResult);

/* function for setting state of key derivation from key service to "idle" */
extern void Csm_KeyDeriveSymKeyServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_KeyDeriveSymKeyServiceHasCallback(void);
#endif /* (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON) */

/* KeyExchangeCalcPubVal */
#if (CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON)
/* Callback notification function for public value calculation */
extern void Csm_KeyExchangeCalcPubValCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of public value calculation to "idle" */
extern void Csm_KeyExchangeCalcPubValServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_KeyExchangeCalcPubValServiceHasCallback(void);
#endif /* (CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON) */

/* KeyExchangeCalcSecret */
#if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON)
/* Callback notification function for key exchange */
extern void Csm_KeyExchangeCalcSecretCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of key exchange to "idle" */
extern void Csm_KeyExchangeCalcSecretServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_KeyExchangeCalcSecretServiceHasCallback(void);
#endif /* (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) */

/* KeyExchangeCalcSymKey */
#if (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON)
/* Callback notification function for key exchange */
extern void Csm_KeyExchangeCalcSymKeyCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of key exchange to "idle" */
extern void Csm_KeyExchangeCalcSymKeyServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_KeyExchangeCalcSymKeyServiceHasCallback(void);
#endif /* (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON) */

/* Symmetrical Extract interface */
#if (CSM_SYM_KEY_EXTRACT_STATUS == STD_ON)
/* Callback notification function for symmetrical key extraction */
extern void Csm_SymKeyExtractCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of symmetrical key extraction to "idle" */
extern void Csm_SymKeyExtractServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_SymKeyExtractServiceHasCallback(void);
#endif /* (CSM_SYM_KEY_EXTRACT_STATUS == STD_ON) */

/* Symmetrical Wrapping Key */
#if (CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON)
/* Callback notification function for symmetrical key wrapping */
extern void Csm_SymKeyWrapSymCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of symmetrical key wrapping to "idle" */
extern void Csm_SymKeyWrapSymServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_SymKeyWrapSymServiceHasCallback(void);
#endif /* (CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON) */

/* Asymmetrical Wrapping key */
#if (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON)
/* Callback notification function for symmetrical key wrapping */
extern void Csm_SymKeyWrapAsymCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of symmetrical key wrapping to "idle" */
extern void Csm_SymKeyWrapAsymServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_SymKeyWrapAsymServiceHasCallback(void);
#endif /* (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON) */

/* AsymmPubKeyExtract */
#if (CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON)
/* Callback notification function for asymmetrical public key extraction */
extern void Csm_AsymPublicKeyExtractCallbackNotification(Std_ReturnType ddResult);

/* function for setting state of asymmetrical public key extraction to "idle" */
extern void Csm_AsymPublicKeyExtractServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_AsymPublicKeyExtractServiceHasCallback(void);
#endif /* (CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON) */

/* AsymmPrivKeyExtract */
#if (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON)
/* Callback notification function for asymmetrical private key extraction */
extern void Csm_AsymPrivateKeyExtractCallbackNotification(Std_ReturnType ddResult);

/* function for setting state of asymmetrical private key extraction to "idle"
  */
extern void Csm_AsymPrivateKeyExtractServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_AsymPrivateKeyExtractServiceHasCallback(void);
#endif /* (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON) */

/* Symmetrical wrapping key */
#if (CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON)
/* Callback notification function for asymmetrical key wrapping */
extern void Csm_AsymPrivateKeyWrapSymCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of asymmetrical key wrapping to "idle" */
extern void Csm_AsymPrivateKeyWrapSymServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_AsymPrivateKeyWrapSymServiceHasCallback(void);
#endif /* (CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON) */

/* Asymmetrical wrapping key */
#if (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON)
/* Callback notification function for asymmetrical key wrapping */
extern void Csm_AsymPrivateKeyWrapAsymCallbackNotification(Std_ReturnType ddResult);

/* function for setting the state of asymmetrical key wrapping to "idle" */
extern void Csm_AsymPrivateKeyWrapAsymServiceFinishNotification(void);

/* function for checking asynchronous behavior of service */
extern boolean Csm_AsymPrivateKeyWrapAsymServiceHasCallback(void);
#endif /* (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CSM_CBK_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
