/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_Init.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Implementation of CRY Init function                           **
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
** 1.3.3     26-May-2020   JaeHyun      Redmine #22489 #23715 #23716          **
** 1.3.2     19-Mar-2020   JaeHyun      Redmine #22489                        **
** 1.3.1     13-Mar-2020   JaeHyun      Redmine #22362                        **
** 1.3.0     04-Dec-2019   Sinil        Redmine #20495                        **
** 1.2.7     04-Jul-2019   Sinil        Redmine #17741                        **
** 1.2.6     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.5     09-Aug-2018   Sinil        Redmine #13650                        **
** 1.2.4     09-May-2018   Sinil        Redmine #12635                        **
** 1.2.3     10-Nov-2017   Sinil        Redmine #10549                        **
** 1.2.2     21-Sep-2017   Sinil        Redmine #10044                        **
** 1.2.1     21-Sep-2017   Sinil        Redmine #10038                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7651                         **
** 1.1.0     11-Jan-2017   Sinil        Redmine #7198                         **
** 1.0.8     27-Sep-2016   Sinil        Redmine #6121                         **
** 1.0.7     09-Aug-2016   Sinil        Redmine #5695                         **
** 1.0.6     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.5     13-Jun-2016   Sinil        Redmine #4900                         **
** 1.0.4     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.3     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Cry_Init.h"
#include "CryptoLib_Cfg.h"
#include "HwResource.h"

#if ((CRYPTOLIB_SUPORT_HSM_SPC58X == STD_ON) || (CRYPTOLIB_SUPORT_HSM_ICUM == STD_ON))
#include "Hsm_AutIntDriver.h"
#endif

#if (CRYPTOLIB_SUPORT_HSM_CSEC == STD_ON)
#include "CSEc_Driver.h"
#include "Cry_AutCsecCommon.h"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : Cry_Init                                              **
**                                                                            **
** Service ID         : NOne                                                  **
**                                                                            **
** Description        : This service initializes the CRY primitives.          **
**                      All the Global variables will be initialized after    **
**                      the successful completion of this API.                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s): None                              **
**                      Function(s) invoked: Hsm_Init                         **
*******************************************************************************/
Std_ReturnType Cry_Init(void)
{
  Std_ReturnType LddRet = E_OK;;

  /* Hash Services */
  #if (CSM_HASH_STATUS == STD_ON)
  #if (CSM_HASH_AUTSEEDKEY == STD_ON)
  Cry_AutSeedKeyInit();
  #endif
  #if (CSM_HASH_HAEADVSEEDKEY == STD_ON)
  Cry_HaeAdvSeedKeyInit();
  #endif
  #if (CSM_HASH_ESCSHA1 == STD_ON)
  Cry_EscSha1Init();
  #endif
  #if (CSM_HASH_ESCSHA256 == STD_ON)
  Cry_EscSha256Init();
  #endif
  #if (CSM_HASH_HAESHA1 == STD_ON)
  Cry_HaeSha1Init();
  #endif
  #if (CSM_HASH_HAESHA256 == STD_ON)
  Cry_HaeSha256Init();
  #endif
  #if (CSM_HASH_AUTHSMSHA1 == STD_ON)
  Cry_AutHsmSha1Init();
  #endif
  #if (CSM_HASH_AUTHSMSHA256 == STD_ON)
  Cry_AutHsmSha256Init();
  #endif
  #if (CSM_HASH_HAEHSMSHA1 == STD_ON)
  Cry_HaeHsmSha1Init();
  #endif
  #if (CSM_HASH_HAEHSMSHA256 == STD_ON)
  Cry_HaeHsmSha256Init();
  #endif
  #endif

  /* MAC Services */
  #if (CSM_MAC_GENERATE_STATUS == STD_ON)
  #if (CSM_MAC_ESCHMACSHA1GENERATE == STD_ON)
  Cry_EscHmacSha1GenerateInit();
  #endif
  #if (CSM_MAC_ESCHMACSHA256GENERATE == STD_ON)
  Cry_EscHmacSha256GenerateInit();
  #endif
  #if (CSM_MAC_ESCCMACAESGENERATE == STD_ON)
  Cry_EscCmacAesGenerateInit();
  #endif
  #if (CSM_MAC_HAEHMACSHA1GENERATE == STD_ON)
  Cry_HaeHmacSha1GenerateInit();
  #endif
  #if (CSM_MAC_HAEHMACSHA256GENERATE == STD_ON)
  Cry_HaeHmacSha256GenerateInit();
  #endif
  #if (CSM_MAC_AUTHSMHMACSHA1GENERATE == STD_ON)
  Cry_AutHsmHmacSha1GenerateInit();
  #endif
  #if (CSM_MAC_AUTHSMHMACSHA256GENERATE == STD_ON)
  Cry_AutHsmHmacSha256GenerateInit();
  #endif
  #if (CSM_MAC_AUTHSMCMACAESGENERATE == STD_ON)
  Cry_AutHsmCmacAesGenerateInit();
  #endif
  #if (CSM_MAC_HAECMACAESGENERATE == STD_ON)
  Cry_HaeCmacAesGenerateInit();
  #endif
  #if (CSM_MAC_HAEHSMHMACSHA256GENERATE == STD_ON)
  Cry_HaeHsmHmacSha256GenerateInit();
  #endif
  #if (CSM_MAC_HAEHSMCMACAESGENERATE == STD_ON)
  Cry_HaeHsmCmacAesGenerateInit();
  #endif
  #if (CSM_MAC_AUTICUSCMACAESGENERATE == STD_ON)
  Cry_AutIcusCmacAesGenerateInit();
  #endif
  #if (CSM_MAC_AUTCSECCMACAESGENERATE == STD_ON)
  Cry_AutCsecInit(CRY_AUTCSEC_CMACAESGEN);
  #endif
  #endif

  #if (CSM_MAC_VERIFY_STATUS == STD_ON)
  #if (CSM_MAC_ESCHMACSHA1VERIFY == STD_ON)
  Cry_EscHmacSha1VerifyInit();
  #endif
  #if (CSM_MAC_ESCHMACSHA256VERIFY == STD_ON)
  Cry_EscHmacSha256VerifyInit();
  #endif
  #if (CSM_MAC_ESCCMACAESVERIFY == STD_ON)
  Cry_EscCmacAesVerifyInit();
  #endif
  #if (CSM_MAC_HAEHMACSHA1VERIFY == STD_ON)
  Cry_HaeHmacSha1VerifyInit();
  #endif
  #if (CSM_MAC_HAEHMACSHA256VERIFY == STD_ON)
  Cry_HaeHmacSha256VerifyInit();
  #endif
  #if (CSM_MAC_HAECMACAESVERIFY == STD_ON)
  Cry_HaeCmacAesVerifyInit();
  #endif
  #if (CSM_MAC_AUTHSMHMACSHA1VERIFY == STD_ON)
  Cry_AutHsmHmacSha1VerifyInit();
  #endif
  #if (CSM_MAC_AUTHSMHMACSHA256VERIFY == STD_ON)
  Cry_AutHsmHmacSha256VerifyInit();
  #endif
  #if (CSM_MAC_AUTHSMCMACAESVERIFY == STD_ON)
  Cry_AutHsmCmacAesVerifyInit();
  #endif
  #if (CSM_MAC_HAEHSMHMACSHA256VERIFY == STD_ON)
  Cry_HaeHsmHmacSha256VerifyInit();
  #endif
  #if (CSM_MAC_HAEHSMCMACAESVERIFY == STD_ON)
  Cry_HaeHsmCmacAesVerifyInit();
  #endif
  #if (CSM_MAC_AUTICUSCMACAESVERIFY == STD_ON)
  Cry_AutIcusCmacAesVerifyInit();
  #endif
  #if (CSM_MAC_AUTCSECCMACAESVERIFY == STD_ON)
  Cry_AutCsecInit(CRY_AUTCSEC_CMACASEVER);
  #endif
  #endif

  /* Random Number Generator Services */
  #if (CSM_RANDOM_SEED_STATUS == STD_ON)
  #if (CSM_RANDOM_AUTRANDOMSEED == STD_ON)
  Cry_AutRandomSeedInit();
  #endif
  #if (CSM_RANDOM_HAEADVRANDOMSEED == STD_ON)
  Cry_HaeAdvRandomSeedInit();
  #endif
  #if (CSM_RANDOM_HAEHACRANDOMSEED == STD_ON)
  Cry_HaeHacRandomSeedInit();
  #endif
  #if (CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON)
  Cry_HaePseudoRandomSeedInit();
  #endif
  #if (CSM_RANDOM_AUTICUSRANDOMSEED == STD_ON)
  Cry_AutIcusRandomSeedInit();
  #endif
  #if (CSM_RANDOM_AUTCSECRANDOMSEED == STD_ON)
  Cry_AutCsecInit(CRY_AUTCSEC_RANDOMSEED);
  #endif
  #endif

  #if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
  #if (CSM_RANDOM_AUTRANDOMGENERATE == STD_ON)
  Cry_AutRandomGenerateInit();
  #endif
  #if (CSM_RANDOM_HAEADVRANDOMGENERATE == STD_ON)
  Cry_HaeAdvRandomGenerateInit();
  #endif
  #if (CSM_RANDOM_HAEHACRANDOMGENERATE == STD_ON)
  Cry_HaeHacRandomGenerateInit();
  #endif
  #if (CSM_RANDOM_HAEPSEUDORANDOMGENERATE == STD_ON)
  Cry_HaePseudoRandomGenerateInit();
  #endif
  #if (CSM_RANDOM_AUTHSMPSEUDORANDOMGENERATE == STD_ON)
  Cry_AutHsmPseudoRandomGenerateInit();
  #endif
  #if (CSM_RANDOM_AUTHSMTRUERANDOMGENERATE == STD_ON)
  Cry_AutHsmTrueRandomGenerateInit();
  #endif
  #if (CSM_RANDOM_HAEHSMPSEUDORANDOMGENERATE == STD_ON)
  Cry_HaeHsmPseudoRandomGenerateInit();
  #endif
  #if (CSM_RANDOM_HAEHSMTRUERANDOMGENERATE == STD_ON)
  Cry_HaeHsmTrueRandomGenerateInit();
  #endif
  #if (CSM_RANDOM_AUTICUSRANDOMGENERATE == STD_ON)
  Cry_AutIcusRandomGenerateInit();
  #endif
  #if (CSM_RANDOM_AUTCSECRANDOMGENERATE == STD_ON)
  Cry_AutCsecInit(CRY_AUTCSEC_RANDOMGENERATE);
  #endif
  #endif

  /* Symmetrical Block Services */
  #if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
  #if (CSM_SYMBLOCK_ESCAESECBENCRYPT == STD_ON)
  Cry_EscAesEcbEncryptInit();
  #endif
  #if (CSM_SYMBLOCK_HAEAESECBENCRYPT == STD_ON)
  Cry_HaeAesEcbEncryptInit();
  #endif
  #if (CSM_SYMBLOCK_AUTHSMAESECBENCRYPT == STD_ON)
  Cry_AutHsmAesEcbEncryptInit();
  #endif
  #if (CSM_SYMBLOCK_HAEHSMAESECBENCRYPT == STD_ON)
  Cry_HaeHsmAesEcbEncryptInit();
  #endif
  #if (CSM_SYMBLOCK_AUTICUSAESECBENCRYPT == STD_ON)
  Cry_AutIcusAesEcbEncryptInit();
  #endif
  #if (CSM_SYMBLOCK_AUTCSECAESECBENCRYPT == STD_ON)
  Cry_AutCsecInit(CRY_AUTCSEC_AESECBENC);
  #endif
  #endif

  #if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
  #if (CSM_SYMBLOCK_ESCAESECBDECRYPT == STD_ON)
  Cry_EscAesEcbDecryptInit();
  #endif
  #if (CSM_SYMBLOCK_AUTHSMAESECBDECRYPT == STD_ON)
  Cry_AutHsmAesEcbDecryptInit();
  #endif
  #if (CSM_SYMBLOCK_HAEHSMAESECBDECRYPT == STD_ON)
  Cry_HaeHsmAesEcbDecryptInit();
  #endif  
  #if (CSM_SYMBLOCK_AUTICUSAESECBDECRYPT == STD_ON)
  Cry_AutIcusAesEcbDecryptInit();
  #endif
  #if (CSM_SYMBLOCK_AUTCSECAESECBDECRYPT == STD_ON)
  Cry_AutCsecInit(CRY_AUTCSEC_AESECBDEC);
  #endif
  #endif

  /* Symmetrical Services */
  #if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
  #if (CSM_SYM_ESCAESCBCENCRYPT == STD_ON)
  Cry_EscAesCbcEncryptInit();
  #endif
  #if (CSM_SYM_HAEAESCBCENCRYPT == STD_ON)
  Cry_HaeAesCbcEncryptInit();
  #endif
  #if (CSM_SYM_HAEAESCTRENCRYPT == STD_ON)
  Cry_HaeAesCtrEncryptInit();
  #endif
  #if (CSM_SYM_AUTHSMAESCBCENCRYPT == STD_ON)
  Cry_AutHsmAesCbcEncryptInit();
  #endif
  #if (CSM_SYM_AUTHSMAESCTRENCRYPT == STD_ON)
  Cry_AutHsmAesCtrEncryptInit();
  #endif
  #if (CSM_SYM_HAEHSMAESCBCENCRYPT == STD_ON)
  Cry_HaeHsmAesCbcEncryptInit();
  #endif
  #if (CSM_SYM_HAEHSMAESCTRENCRYPT == STD_ON)
  Cry_HaeHsmAesCtrEncryptInit();
  #endif  
  #if (CSM_SYM_AUTICUSAESCBCENCRYPT == STD_ON)
  Cry_AutIcusAesCbcEncryptInit();
  #endif
  #if (CSM_SYM_AUTCSECAESCBCENCRYPT == STD_ON)
  Cry_AutCsecInit(CRY_AUTCSEC_AESCBCENC);
  #endif
  #endif

  #if (CSM_SYM_DECRYPT_STATUS == STD_ON)
  #if (CSM_SYM_ESCAESCBCDECRYPT == STD_ON)
  Cry_EscAesCbcDecryptInit();
  #endif
  #if (CSM_SYM_HAEAESCBCDECRYPT == STD_ON)
  Cry_HaeAesCbcDecryptInit();
  #endif
  #if (CSM_SYM_HAEAESCTRDECRYPT == STD_ON)
  Cry_HaeAesCtrDecryptInit();
  #endif
  #if (CSM_SYM_AUTHSMAESCBCDECRYPT == STD_ON)
  Cry_AutHsmAesCbcDecryptInit();
  #endif
  #if (CSM_SYM_AUTHSMAESCTRDECRYPT == STD_ON)
  Cry_AutHsmAesCtrDecryptInit();
  #endif
  #if (CSM_SYM_HAEHSMAESCBCDECRYPT == STD_ON)
  Cry_HaeHsmAesCbcDecryptInit();
  #endif
  #if (CSM_SYM_HAEHSMAESCTRDECRYPT == STD_ON)
  Cry_HaeHsmAesCtrDecryptInit();
  #endif  
  #if (CSM_SYM_AUTICUSAESCBCDECRYPT == STD_ON)
  Cry_AutIcusAesCbcDecryptInit();
  #endif
  #if (CSM_SYM_AUTCSECAESCBCDECRYPT == STD_ON)
  Cry_AutCsecInit(CRY_AUTCSEC_AESCBCDEC);
  #endif
  #endif

  /* Asymmetrical Services */
  #if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
  #if (CSM_ASYM_ESCRSAENCRYPT == STD_ON)
  Cry_EscRsaEncryptInit();
  #endif
  #if (CSM_ASYM_HAERSAENCRYPT == STD_ON)
  Cry_HaeRsaEncryptInit();
  #endif
  #if (CSM_ASYM_AUTHSMECIESENCRYPT == STD_ON)
  Cry_AutHsmEciesEncryptInit();
  #endif
  #if (CSM_ASYM_AUTHSMRSAENCRYPT == STD_ON)
  Cry_AutHsmRsaEncryptInit();
  #endif
  #endif

  #if (CSM_ASYM_DECRYPT_STATUS == STD_ON)
  #if (CSM_ASYM_ESCRSADECRYPT == STD_ON)
  Cry_EscRsaDecryptInit();
  #endif
  #if (CSM_ASYM_HAERSADECRYPT == STD_ON)
  Cry_HaeRsaDecryptInit();
  #endif
  #if (CSM_ASYM_AUTHSMECIESDECRYPT == STD_ON)
  Cry_AutHsmEciesDecryptInit();
  #endif
  #if (CSM_ASYM_AUTHSMRSADECRYPT == STD_ON)
  Cry_AutHsmRsaDecryptInit();
  #endif
  #endif

  /* Signature Services */
  #if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
  #if (CSM_SIGNATURE_ESCPKCS1V15SHA1GENERATE == STD_ON)
  Cry_EscPkcs1V15Sha1GenerateInit();
  #endif
  #if (CSM_SIGNATURE_ESCPKCS1V15SHA256GENERATE == STD_ON)
  Cry_EscPkcs1V15Sha256GenerateInit();
  #endif
  #if (CSM_SIGNATURE_HAEPKCS1V15SHA1GENERATE == STD_ON)
  Cry_HaePkcs1V15Sha1GenerateInit();
  #endif
  #if (CSM_SIGNATURE_HAEPKCS1V15SHA256GENERATE == STD_ON)
  Cry_HaePkcs1V15Sha256GenerateInit();
  #endif
  #if (CSM_SIGNATURE_HAEHSMECDSASHA256GENERATE == STD_ON)
  Cry_HaeHsmEcdsaSha256GenerateInit();
  #endif
  #if (CSM_SIGNATURE_HAEHSMPKCS1PSSSHA256GENERATE == STD_ON)
  Cry_HaeHsmPkcs1PssSha256GenerateInit();
  #endif
  #if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA256GENERATE == STD_ON)
  Cry_HaeHsmPkcs1V15Sha256GenerateInit();
  #endif  
  #if (CSM_SIGNATURE_AUTHSMECDSASHA256GENERATE == STD_ON)
  Cry_AutHsmEcdsaSha256GenerateInit();
  #endif
  #if (CSM_SIGNATURE_AUTHSMPKCS1PSSSHA256GENERATE == STD_ON)
  Cry_AutHsmPkcs1PssSha256GenerateInit();
  #endif
  #if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1GENERATE == STD_ON)
  Cry_AutHsmPkcs1V15Sha1GenerateInit();
  #endif
  #if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA256GENERATE == STD_ON)
  Cry_AutHsmPkcs1V15Sha256GenerateInit();
  #endif
  #endif

  #if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
  #if (CSM_SIGNATURE_ESCPKCS1V15SHA1SEEDVERIFY == STD_ON)
  Cry_EscPkcs1V15Sha1SeedVerifyInit();
  #endif
  #if (CSM_SIGNATURE_ESCPKCS1V15SHA1VERIFY == STD_ON)
  Cry_EscPkcs1V15Sha1VerifyInit();
  #endif
  #if (CSM_SIGNATURE_ESCPKCS1V15SHA256SEEDVERIFY == STD_ON)
  Cry_EscPkcs1V15Sha256SeedVerifyInit();
  #endif
  #if (CSM_SIGNATURE_ESCPKCS1V15SHA256VERIFY == STD_ON)
  Cry_EscPkcs1V15Sha256VerifyInit();
  #endif
  #if (CSM_SIGNATURE_HAEPKCS1V15SHA1SEEDVERIFY == STD_ON)
  Cry_HaePkcs1V15Sha1SeedVerifyInit();
  #endif
  #if (CSM_SIGNATURE_HAEPKCS1V15SHA1VERIFY == STD_ON)
  Cry_HaePkcs1V15Sha1VerifyInit();
  #endif
  #if (CSM_SIGNATURE_HAEPKCS1V15SHA256SEEDVERIFY == STD_ON)
  Cry_HaePkcs1V15Sha256SeedVerifyInit();
  #endif
  #if (CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY == STD_ON)
  Cry_HaePkcs1V15Sha256VerifyInit();
  #endif
  #if (CSM_SIGNATURE_HAEHSMECDSASHA256VERIFY == STD_ON)
  Cry_HaeHsmEcdsaSha256VerifyInit();
  #endif
  #if (CSM_SIGNATURE_HAEHSMPKCS1PSSSHA256VERIFY == STD_ON)
  Cry_HaeHsmPkcs1PssSha256VerifyInit();
  #endif
  #if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA1SEEDVERIFY == STD_ON)
  Cry_HaeHsmPkcs1V15Sha1SeedVerifyInit();
  #endif
  #if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA1VERIFY == STD_ON)
  Cry_HaeHsmPkcs1V15Sha1VerifyInit();
  #endif
  #if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA256SEEDVERIFY == STD_ON)
  Cry_HaeHsmPkcs1V15Sha256SeedVerifyInit();
  #endif
  #if (CSM_SIGNATURE_HAEHSMPKCS1V15SHA256VERIFY == STD_ON)
  Cry_HaeHsmPkcs1V15Sha256VerifyInit();
  #endif
  #if (CSM_SIGNATURE_AUTHSMECDSASHA256VERIFY == STD_ON)
  Cry_AutHsmEcdsaSha256VerifyInit();
  #endif
  #if (CSM_SIGNATURE_AUTHSMPKCS1PSSSHA256VERIFY == STD_ON)
  Cry_AutHsmPkcs1PssSha256VerifyInit();
  #endif
  #if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1SEEDVERIFY == STD_ON)
  Cry_AutHsmPkcs1V15Sha1SeedVerifyInit();
  #endif
  #if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1VERIFY == STD_ON)
  Cry_AutHsmPkcs1V15Sha1VerifyInit();
  #endif
  #if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA256SEEDVERIFY == STD_ON)
  Cry_AutHsmPkcs1V15Sha256SeedVerifyInit();
  #endif
  #if (CSM_SIGNATURE_AUTHSMPKCS1V15SHA256VERIFY == STD_ON)
  Cry_AutHsmPkcs1V15Sha256VerifyInit();
  #endif
  #endif

  #if (CSM_KEY_DERIVATION_STATUS == STD_ON)
  #if (CSM_KEYDERIVE_AUTHSMPBKDF2 == STD_ON)
  Cry_AutHsmPbkdf2Init();
  #endif
  #if (CSM_KEYDERIVE_HAEHSMPBKDF2 == STD_ON)
  Cry_HaeHsmPbkdf2Init();
  #endif  
  #endif

  #if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON)
  #if (CSM_KEYEXCHANGECALC_SECRET_AUTHSMECDH == STD_ON)
  Cry_AutHsmEcdhInit();
  #endif
  #if (CSM_KEYEXCHANGECALC_SECRET_HAEHSMECDH == STD_ON)
  Cry_HaeHsmEcdhInit();
  #endif  
  #endif

  #if (CRYPTOLIB_SUPORT_HSM_CSEC == STD_ON)
  if (Csec_Init() != CSEC_ERC_NO_ERROR)
  {
    LddRet = E_NOT_OK;
  }
  #endif

  #if ((CRYPTOLIB_SUPORT_HSM_SPC58X == STD_ON) || (CRYPTOLIB_SUPORT_HSM_ICUM == STD_ON))
  if (Hsm_Init() != HSM_NO_ERROR)
  {
    LddRet = E_NOT_OK;
  }
  #endif

  return LddRet;
}


#define CSM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
