/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_Init.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for CRY initialization                            **
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
** 1.0.8     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.7     26-May-2020   JaeHyun      Redmine #22754                        **
** 1.0.6     04-Jul-2019   Sinil        Redmine #17741                        **
** 1.0.5     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.4     09-Aug-2018   Sinil        Redmine #13650                        **
** 1.0.3     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */


#ifndef  CRY_INIT_H
#define  CRY_INIT_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Csm_Cfg.h"
#include "Csm_Types.h"

/*******************************************************************************
**                      External Function Prototypes                          **
*******************************************************************************/
/* Hash Services */
#if (CSM_HASH_STATUS == STD_ON)
#if (CSM_HASH_AUTSEEDKEY == STD_ON)
extern void Cry_AutSeedKeyInit(void);
#endif
#if (CSM_HASH_HAEADVSEEDKEY == STD_ON)
extern void Cry_HaeAdvSeedKeyInit(void);
#endif
#if (CSM_HASH_ESCSHA1 == STD_ON)
extern void Cry_EscSha1Init(void);
#endif
#if (CSM_HASH_ESCSHA256 == STD_ON)
extern void Cry_EscSha256Init(void);
#endif
#if (CSM_HASH_HAESHA1 == STD_ON)
extern void Cry_HaeSha1Init(void);
#endif
#if (CSM_HASH_HAESHA256 == STD_ON)
extern void Cry_HaeSha256Init(void);
#endif
#if (CSM_HASH_AUTHSMSHA1 == STD_ON)
extern void Cry_AutHsmSha1Init(void);
#endif
#if (CSM_HASH_AUTHSMSHA256 == STD_ON)
extern void Cry_AutHsmSha256Init(void);
#endif
#if (CSM_HASH_HAEHSMSHA1 == STD_ON)
extern void Cry_HaeHsmSha1Init(void);
#endif
#if (CSM_HASH_HAEHSMSHA256 == STD_ON)
extern void Cry_HaeHsmSha256Init(void);
#endif
#endif

/* MAC Services */
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
#if (CSM_MAC_ESCHMACSHA1GENERATE == STD_ON)
extern void Cry_EscHmacSha1GenerateInit(void);
#endif
#if (CSM_MAC_ESCHMACSHA256GENERATE == STD_ON)
extern void Cry_EscHmacSha256GenerateInit(void);
#endif
#if (CSM_MAC_ESCCMACAESGENERATE == STD_ON)
extern void Cry_EscCmacAesGenerateInit(void);
#endif
#if (CSM_MAC_HAEHMACSHA1GENERATE == STD_ON)
extern void Cry_HaeHmacSha1GenerateInit(void);
#endif
#if (CSM_MAC_HAEHMACSHA256GENERATE == STD_ON)
extern void Cry_HaeHmacSha256GenerateInit(void);
#endif
#if (CSM_MAC_AUTHSMHMACSHA1GENERATE == STD_ON)
extern void Cry_AutHsmHmacSha1GenerateInit(void);
#endif
#if (CSM_MAC_AUTHSMHMACSHA256GENERATE == STD_ON)
extern void Cry_AutHsmHmacSha256GenerateInit(void);
#endif
#if (CSM_MAC_AUTHSMCMACAESGENERATE == STD_ON)
extern void Cry_AutHsmCmacAesGenerateInit(void);
#endif
#if (CSM_MAC_HAECMACAESGENERATE == STD_ON)
extern void Cry_HaeCmacAesGenerateInit(void);
#endif
#if (CSM_MAC_HAEHSMHMACSHA256GENERATE == STD_ON)
extern void Cry_HaeHsmHmacSha256GenerateInit(void);
#endif
#if (CSM_MAC_HAEHSMCMACAESGENERATE == STD_ON)
extern void Cry_HaeHsmCmacAesGenerateInit(void);
#endif
#if (CSM_MAC_AUTICUSCMACAESGENERATE == STD_ON)
extern void Cry_AutIcusCmacAesGenerateInit(void);
#endif
#endif

#if (CSM_MAC_VERIFY_STATUS == STD_ON)
#if (CSM_MAC_ESCHMACSHA1VERIFY == STD_ON)
extern void Cry_EscHmacSha1VerifyInit(void);
#endif
#if (CSM_MAC_ESCHMACSHA256VERIFY == STD_ON)
extern void Cry_EscHmacSha256VerifyInit(void);
#endif
#if (CSM_MAC_ESCCMACAESVERIFY == STD_ON)
extern void Cry_EscCmacAesVerifyInit(void);
#endif
#if (CSM_MAC_HAEHMACSHA1VERIFY == STD_ON)
extern void Cry_HaeHmacSha1VerifyInit(void);
#endif
#if (CSM_MAC_HAEHMACSHA256VERIFY == STD_ON)
extern void Cry_HaeHmacSha256VerifyInit(void);
#endif
#if (CSM_MAC_HAECMACAESVERIFY == STD_ON)
extern void Cry_HaeCmacAesVerifyInit(void);
#endif
#if (CSM_MAC_AUTHSMHMACSHA1VERIFY == STD_ON)
extern void Cry_AutHsmHmacSha1VerifyInit(void);
#endif
#if (CSM_MAC_AUTHSMHMACSHA256VERIFY == STD_ON)
extern void Cry_AutHsmHmacSha256VerifyInit(void);
#endif
#if (CSM_MAC_AUTHSMCMACAESVERIFY == STD_ON)
extern void Cry_AutHsmCmacAesVerifyInit(void);
#endif
#if (CSM_MAC_HAEHSMHMACSHA256VERIFY == STD_ON)
extern void Cry_HaeHsmHmacSha256VerifyInit(void);
#endif
#if (CSM_MAC_HAEHSMCMACAESVERIFY == STD_ON)
extern void Cry_HaeHsmCmacAesVerifyInit(void);
#endif
#if (CSM_MAC_AUTICUSCMACAESVERIFY == STD_ON)
extern void Cry_AutIcusCmacAesVerifyInit(void);
#endif
#endif

/* Random Number Generator Services */
#if (CSM_RANDOM_SEED_STATUS == STD_ON)
#if (CSM_RANDOM_AUTRANDOMSEED == STD_ON)
extern void Cry_AutRandomSeedInit(void);
#endif
#if (CSM_RANDOM_HAEADVRANDOMSEED == STD_ON)
extern void Cry_HaeAdvRandomSeedInit(void);
#endif
#if (CSM_RANDOM_HAEHACRANDOMSEED == STD_ON)
extern void Cry_HaeHacRandomSeedInit(void);
#endif
#if (CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON)
extern void Cry_HaePseudoRandomSeedInit(void);
#endif
#if (CSM_RANDOM_AUTICUSRANDOMSEED == STD_ON)
extern void Cry_AutIcusRandomSeedInit(void);
#endif
#endif

#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
#if (CSM_RANDOM_AUTRANDOMGENERATE == STD_ON)
extern void Cry_AutRandomGenerateInit(void);
#endif
#if (CSM_RANDOM_HAEADVRANDOMGENERATE == STD_ON)
extern void Cry_HaeAdvRandomGenerateInit(void);
#endif
#if (CSM_RANDOM_HAEHACRANDOMGENERATE == STD_ON)
extern void Cry_HaeHacRandomGenerateInit(void);
#endif
#if (CSM_RANDOM_HAEPSEUDORANDOMGENERATE == STD_ON)
extern void Cry_HaePseudoRandomGenerateInit(void);
#endif
#if (CSM_RANDOM_AUTHSMPSEUDORANDOMGENERATE == STD_ON)
extern void Cry_AutHsmPseudoRandomGenerateInit(void);
#endif
#if (CSM_RANDOM_AUTHSMTRUERANDOMGENERATE == STD_ON)
extern void Cry_AutHsmTrueRandomGenerateInit(void);
#endif
#if (CSM_RANDOM_HAEHSMPSEUDORANDOMGENERATE == STD_ON)
extern void Cry_HaeHsmPseudoRandomGenerateInit(void);
#endif
#if (CSM_RANDOM_HAEHSMTRUERANDOMGENERATE == STD_ON)
extern void Cry_HaeHsmTrueRandomGenerateInit(void);
#endif
#if (CSM_RANDOM_AUTICUSRANDOMGENERATE == STD_ON)
extern void Cry_AutIcusRandomGenerateInit(void);
#endif
#endif

/* Symmetrical Block Services */
#if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYMBLOCK_ESCAESECBENCRYPT == STD_ON)
extern void Cry_EscAesEcbEncryptInit(void);
#endif
#if (CSM_SYMBLOCK_HAEAESECBENCRYPT == STD_ON)
extern void Cry_HaeAesEcbEncryptInit(void);
#endif
#if (CSM_SYMBLOCK_HAEHSMAESECBENCRYPT == STD_ON)
extern void Cry_HaeHsmAesEcbEncryptInit(void);
#endif
#if (CSM_SYMBLOCK_AUTHSMAESECBENCRYPT == STD_ON)
extern void Cry_AutHsmAesEcbEncryptInit(void);
#endif
#if (CSM_SYMBLOCK_AUTICUSAESECBENCRYPT == STD_ON)
extern void Cry_AutIcusAesEcbEncryptInit(void);
#endif
#endif

#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
#if (CSM_SYMBLOCK_ESCAESECBDECRYPT == STD_ON)
extern void Cry_EscAesEcbDecryptInit(void);
#endif
#if (CSM_SYMBLOCK_HAEHSMAESECBDECRYPT == STD_ON)
extern void Cry_HaeHsmAesEcbDecryptInit(void);
#endif
#if (CSM_SYMBLOCK_AUTHSMAESECBDECRYPT == STD_ON)
extern void Cry_AutHsmAesEcbDecryptInit(void);
#endif
#if (CSM_SYMBLOCK_AUTICUSAESECBDECRYPT == STD_ON)
extern void Cry_AutIcusAesEcbDecryptInit(void);
#endif
#endif

/* Symmetrical Services */
#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_SYM_ESCAESCBCENCRYPT == STD_ON)
extern void Cry_EscAesCbcEncryptInit(void);
#endif
#if (CSM_SYM_HAEAESCBCENCRYPT == STD_ON)
extern void Cry_HaeAesCbcEncryptInit(void);
#endif
#if (CSM_SYM_HAEAESCTRENCRYPT == STD_ON)
extern void Cry_HaeAesCtrEncryptInit(void);
#endif
#if (CSM_SYM_HAEHSMAESCBCENCRYPT == STD_ON)
extern void Cry_HaeHsmAesCbcEncryptInit(void);
#endif
#if (CSM_SYM_HAEHSMAESCTRENCRYPT == STD_ON)
extern void Cry_HaeHsmAesCtrEncryptInit(void);
#endif
#if (CSM_SYM_AUTHSMAESCBCENCRYPT == STD_ON)
extern void Cry_AutHsmAesCbcEncryptInit(void);
#endif
#if (CSM_SYM_AUTHSMAESCTRENCRYPT == STD_ON)
extern void Cry_AutHsmAesCtrEncryptInit(void);
#endif
#if (CSM_SYM_AUTICUSAESCBCENCRYPT == STD_ON)
extern void Cry_AutIcusAesCbcEncryptInit(void);
#endif
#endif

#if (CSM_SYM_DECRYPT_STATUS == STD_ON)
#if (CSM_SYM_ESCAESCBCDECRYPT == STD_ON)
extern void Cry_EscAesCbcDecryptInit(void);
#endif
#if (CSM_SYM_HAEAESCBCDECRYPT == STD_ON)
extern void Cry_HaeAesCbcDecryptInit(void);
#endif
#if (CSM_SYM_HAEAESCTRDECRYPT == STD_ON)
extern void Cry_HaeAesCtrDecryptInit(void);
#endif
#if (CSM_SYM_HAEHSMAESCBCDECRYPT == STD_ON)
extern void Cry_HaeHsmAesCbcDecryptInit(void);
#endif
#if (CSM_SYM_HAEHSMAESCTRDECRYPT == STD_ON)
extern void Cry_HaeHsmAesCtrDecryptInit(void);
#endif
#if (CSM_SYM_AUTHSMAESCBCDECRYPT == STD_ON)
extern void Cry_AutHsmAesCbcDecryptInit(void);
#endif
#if (CSM_SYM_AUTHSMAESCTRDECRYPT == STD_ON)
extern void Cry_AutHsmAesCtrDecryptInit(void);
#endif
#if (CSM_SYM_AUTICUSAESCBCDECRYPT == STD_ON)
extern void Cry_AutIcusAesCbcDecryptInit(void);
#endif
#endif

/* Asymmetrical Services */
#if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
#if (CSM_ASYM_ESCRSAENCRYPT == STD_ON)
extern void Cry_EscRsaEncryptInit(void);
#endif
#if (CSM_ASYM_HAERSAENCRYPT == STD_ON)
extern void Cry_HaeRsaEncryptInit(void);
#endif
#if (CSM_ASYM_AUTHSMECIESENCRYPT == STD_ON)
extern void Cry_AutHsmEciesEncryptInit(void);
#endif
#if (CSM_ASYM_AUTHSMRSAENCRYPT == STD_ON)
extern void Cry_AutHsmRsaEncryptInit(void);
#endif
#endif

#if (CSM_ASYM_DECRYPT_STATUS == STD_ON)
#if (CSM_ASYM_ESCRSADECRYPT == STD_ON)
extern void Cry_EscRsaDecryptInit(void);
#endif
#if (CSM_ASYM_HAERSADECRYPT == STD_ON)
extern void Cry_HaeRsaDecryptInit(void);
#endif
#if (CSM_ASYM_AUTHSMECIESDECRYPT == STD_ON)
extern void Cry_AutHsmEciesDecryptInit(void);
#endif
#if (CSM_ASYM_AUTHSMRSADECRYPT == STD_ON)
extern void Cry_AutHsmRsaDecryptInit(void);
#endif
#endif

/* Signature Services */
#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
#if (CSM_SIGNATURE_ESCPKCS1V15SHA1GENERATE == STD_ON)
extern void Cry_EscPkcs1V15Sha1GenerateInit(void);
#endif
#if (CSM_SIGNATURE_ESCPKCS1V15SHA256GENERATE == STD_ON)
extern void Cry_EscPkcs1V15Sha256GenerateInit(void);
#endif
#if (CSM_SIGNATURE_HAEPKCS1V15SHA1GENERATE == STD_ON)
extern void Cry_HaePkcs1V15Sha1GenerateInit(void);
#endif
#if (CSM_SIGNATURE_HAEPKCS1V15SHA256GENERATE == STD_ON)
extern void Cry_HaePkcs1V15Sha256GenerateInit(void);
#endif
#if (CSM_SIGNATURE_HAEHSMECDSASHA256GENERATE == STD_ON)
extern void Cry_HaeHsmEcdsaSha256GenerateInit(void);
#endif
#if (CSM_SIGNATURE_HAEHSMPKCS1PSSSHA256GENERATE == STD_ON)
extern void Cry_HaeHsmPkcs1PssSha256GenerateInit(void);
#endif
#if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA256GENERATE == STD_ON)
extern void Cry_HaeHsmPkcs1V15Sha256GenerateInit(void);
#endif
#if (CSM_SIGNATURE_AUTHSMECDSASHA256GENERATE == STD_ON)
extern void Cry_AutHsmEcdsaSha256GenerateInit(void);
#endif
#if (CSM_SIGNATURE_AUTHSMPKCS1PSSSHA256GENERATE == STD_ON)
extern void Cry_AutHsmPkcs1PssSha256GenerateInit(void);
#endif
#if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1GENERATE == STD_ON)
extern void Cry_AutHsmPkcs1V15Sha1GenerateInit(void);
#endif
#if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA256GENERATE == STD_ON)
extern void Cry_AutHsmPkcs1V15Sha256GenerateInit(void);
#endif
#endif

#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
#if (CSM_SIGNATURE_ESCPKCS1V15SHA1SEEDVERIFY == STD_ON)
extern void Cry_EscPkcs1V15Sha1SeedVerifyInit(void);
#endif
#if (CSM_SIGNATURE_ESCPKCS1V15SHA1VERIFY == STD_ON)
extern void Cry_EscPkcs1V15Sha1VerifyInit(void);
#endif
#if (CSM_SIGNATURE_ESCPKCS1V15SHA256SEEDVERIFY == STD_ON)
extern void Cry_EscPkcs1V15Sha256SeedVerifyInit(void);
#endif
#if (CSM_SIGNATURE_ESCPKCS1V15SHA256VERIFY == STD_ON)
extern void Cry_EscPkcs1V15Sha256VerifyInit(void);
#endif
#if (CSM_SIGNATURE_HAEPKCS1V15SHA1SEEDVERIFY == STD_ON)
extern void Cry_HaePkcs1V15Sha1SeedVerifyInit(void);
#endif
#if (CSM_SIGNATURE_HAEPKCS1V15SHA1VERIFY == STD_ON)
extern void Cry_HaePkcs1V15Sha1VerifyInit(void);
#endif
#if (CSM_SIGNATURE_HAEPKCS1V15SHA256SEEDVERIFY == STD_ON)
extern void Cry_HaePkcs1V15Sha256SeedVerifyInit(void);
#endif
#if (CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY == STD_ON)
extern void Cry_HaePkcs1V15Sha256VerifyInit(void);
#endif
#if (CSM_SIGNATURE_HAEHSMECDSASHA256VERIFY == STD_ON)
extern void Cry_HaeHsmEcdsaSha256VerifyInit(void);
#endif
#if (CSM_SIGNATURE_HAEHSMPKCS1PSSSHA256VERIFY == STD_ON)
extern void Cry_HaeHsmPkcs1PssSha256VerifyInit(void);
#endif
#if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA1SEEDVERIFY == STD_ON)
extern void Cry_HaeHsmPkcs1V15Sha1SeedVerifyInit(void);
#endif
#if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA1VERIFY == STD_ON)
extern void Cry_HaeHsmPkcs1V15Sha1VerifyInit(void);
#endif
#if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA256SEEDVERIFY == STD_ON)
extern void Cry_HaeHsmPkcs1V15Sha256SeedVerifyInit(void);
#endif
#if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA256VERIFY == STD_ON)
extern void Cry_HaeHsmPkcs1V15Sha256VerifyInit(void);
#endif
#if (CSM_SIGNATURE_AUTHSMECDSASHA256VERIFY == STD_ON)
extern void Cry_AutHsmEcdsaSha256VerifyInit(void);
#endif
#if (CSM_SIGNATURE_AUTHSMPKCS1PSSSHA256VERIFY == STD_ON)
extern void Cry_AutHsmPkcs1PssSha256VerifyInit(void);
#endif
#if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1SEEDVERIFY == STD_ON)
extern void Cry_AutHsmPkcs1V15Sha1SeedVerifyInit(void);
#endif
#if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1VERIFY == STD_ON)
extern void Cry_AutHsmPkcs1V15Sha1VerifyInit(void);
#endif
#if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA256SEEDVERIFY == STD_ON)
extern void Cry_AutHsmPkcs1V15Sha256SeedVerifyInit(void);
#endif
#if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA256VERIFY == STD_ON)
extern void Cry_AutHsmPkcs1V15Sha256VerifyInit(void);
#endif
#endif

#if (CSM_KEY_DERIVATION_STATUS == STD_ON)
#if (CSM_KEYDERIVE_AUTHSMPBKDF2 == STD_ON)
extern void Cry_AutHsmPbkdf2Init(void);
#endif
#if (CSM_KEYDERIVE_HAEHSMPBKDF2 == STD_ON)
extern void Cry_HaeHsmPbkdf2Init(void);
#endif
#endif

#if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON)
#if (CSM_KEYEXCHANGECALC_SECRET_AUTHSMECDH == STD_ON)
extern void Cry_AutHsmEcdhInit(void);
#endif
#if (CSM_KEYEXCHANGECALC_SECRET_HAEHSMECDH == STD_ON)
extern void Cry_HaeHsmEcdhInit(void);
#endif
#endif

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* Function for CRY initialization */
extern Std_ReturnType Cry_Init(void);

#endif /* CRY_INIT_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Assumed to be false detection" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
