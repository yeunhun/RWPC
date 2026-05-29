/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DspSecureServices.c                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for UDS services           **
**              implemented by DSP layer of Dcm module                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                Description                      **
********************************************************************************
** 2.3.15    10-12-2021    KaHyun  Kim       #32499                           **
**                                                                            **
** 2.3.14    09-11-2021    KaHyun  Kim       #32499                           **
**                                                                            **
** 2.3.12    21-09-2021    YoungJin Yun      #32219                           **
**                                                                            **
** 2.3.8     26-04-2021    S.K     Park      #24991                           **
**                                                                            **
** 1.0.15    05-11-2020    EunKyung Kim      #26432                           **
**                                                                            **
** 1.0.14    02-28-2020    EunKyung Kim      #21551                           **
**                                                                            **
** 1.0.13    11-25-2019    EunKyung Kim      #19580                           **
**                                                                            **
** 1.0.12    16-11-2018    Y.S     Jeon      #14804                           **
**                                                                            **
** 1.0.11    09-11-2018    Y.S     Jeon      #13923                           **
**                                                                            **
** 1.0.10    13-09-2018    Y.S     Jeon      #14010                           **
**                                                                            **
** 1.0.9     23-11-2017    YoungJin Yun      #10719                           **
**                                                                            **
** 1.0.8     12-06-2017    Jin     Jung      #8760                            **
**                                                                            **
** 1.0.7     30-05-2017    Jin     Jung      #8656                            **
**                                                                            **
** 1.0.6     25-04-2017    Jin     Jung      #6973, #7075, #7079, #8006       **
**                                                                            **
** 1.0.5     28-03-2017    Jin     Jung      #4718                            **
**                                                                            **
** 1.0.4     05-12-2016    Jin     Jung      #6869                            **
**                                                                            **
** 1.0.3     18-10-2016    Jin     Jung      #5484                            **
**                                                                            **
** 1.0.2     20-06-2016    Jin     Jung      #4533                            **
**                                                                            **
** 1.0.1     24-05-2016    Jin     Jung      #4717, #4923, #4924, #4925       **
**                                                                            **
** 1.0.0     01-10-2015    Sungeol Baek      Initial Version                  **
*******************************************************************************/

/*******************************************************************************
**                       Include Section                                      **
*******************************************************************************/
/* polyspace-begin MISRA-C3:12.2 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.8 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.7 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-begin MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-begin RTE:OVFL [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "Not a defect" */

/*
  polyspace:begin<MISRA-C:5.1:Not a defect:Justify with annotations> No Impact of this rule violation
  polyspace:begin<MISRA-C:8.1:Not a defect:Justify with annotations> No Impact of this rule violation
  polyspace:begin<MISRA-C:8.7:Not a defect:Justify with annotations> No Impact of this rule violation
  polyspace:begin<MISRA-C:8.1:Not a defect:Justify with annotations> No Impact of this rule violation
  polyspace:begin<MISRA-C:11.4:Not a defect:Justify with annotations> No Impact of this rule violation
  polyspace:begin<MISRA-C:19.6:Not a defect:Justify with annotations> No Impact of this rule violation  
  polyspace:begin<RTE: NIVL : Not a defect : No Action Planned > initialized local variable
  polyspace:begin<RTE: NIV : Not a defect : No Action Planned > initialized variable
  polyspace:begin<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct
  polyspace:begin<RTE: ABS_ADDR : Not a defect : No Action Planned > All addresses passed to pointer's are fixed in the intended design
*/

#include "Std_Types.h"
#include "Dcm_Cfg.h"
#include "Dcm_Types.h"
#include "Dcm_DspSecureServices.h"

#if (DCM_CSAC_CONFIGURED == STD_ON) /* CSAC Algorithm */
#include "Dcm_CallOuts.h"
#include "Rte_Dcm.h"
#include "Csm.h"
#include "Dcm_Ram.h"

/*******************************************************************************
**                       Global Variables                                     **
*******************************************************************************/
/* Hac Random Generate */
#define DCM_HAE_HAC_RANDOM_SEED_LENGTH                  (16U)
#define DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH             (8U)

#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM       (STD_OFF)
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM            (STD_OFF)
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS           (STD_OFF)
/* polyspace +1 MISRA-C3:2.5 [Justified:Low] "Not a defect" */
#define DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE          (STD_OFF)

#if (defined(CSM_RANDOM_AUTHSMTRUERANDOMGENERATE) \
  && (CSM_RANDOM_AUTHSMTRUERANDOMGENERATE == STD_ON))

/*AutHsm TrueRandomGenerate*/
#if HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
#undef DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM       (STD_ON)
#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
uint8 Dcm_GaaRandom[DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH];
#pragma ghs section
#else
#undef DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM            (STD_ON)
#endif

#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_AUTHSMTRUERANDOMGENERATE_L21_INDEX)
/*End of AutHsm TrueRandomGenerate*/

/*
 * AutHsm PseudoRandomGenerate
 * #24991: When HSM applied, run TRNG at the 1st time only then run PRNG for all
 *         CSM will process appropriate logic according to DCM_RANDOM_GENERATE_CSM_ID value
 * */
#elif (defined(CSM_RANDOM_AUTHSMPSEUDORANDOMGENERATE) && (CSM_RANDOM_AUTHSMPSEUDORANDOMGENERATE == STD_ON))
#if HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
#undef DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM       (STD_ON)
#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
uint8 Dcm_GaaRandom[DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH];
#pragma ghs section
#else
#undef DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM            (STD_ON)
#endif

#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_AUTHSMPSEUDORANDOMGENERATE_L21_INDEX)
/*End of AutHsm PseudoRandomGenerate*/

#elif (defined(CSM_RANDOM_AUTICUSRANDOMGENERATE) && (CSM_RANDOM_AUTICUSRANDOMGENERATE == STD_ON))

#undef DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS           (STD_ON)

#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_AUTICUSRANDOMGENERATE_L21_INDEX)

/*HaeHsm TrueRandomGenerate*/
#elif (defined(CSM_RANDOM_HAEHSMTRUERANDOMGENERATE) && (CSM_RANDOM_HAEHSMTRUERANDOMGENERATE == STD_ON))

#undef DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM            (STD_ON)

#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEHSMTRUERANDOMGENERATE_L21_INDEX)
/*End of HaeHsm TrueRandomGenerate*/

/*
 * HaeHsm PseudoRandomGenerate
 * #24991: When HSM applied, run TRNG at the 1st time only then run PRNG for all
 *         CSM will process appropriate logic according to DCM_RANDOM_GENERATE_CSM_ID value *
 * */
#elif (defined(CSM_RANDOM_HAEHSMPSEUDORANDOMGENERATE) && (CSM_RANDOM_HAEHSMPSEUDORANDOMGENERATE == STD_ON))

#undef DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM            (STD_ON)

#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEHSMPSEUDORANDOMGENERATE_L21_INDEX)
/*End of HaeHsm PseudoRandomGenerate*/

#elif ((defined(CSM_RANDOM_HAEPSEUDORANDOMSEED) && (CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON)) \
  && (defined(CSM_RANDOM_HAEPSEUDORANDOMGENERATE) && (CSM_RANDOM_HAEPSEUDORANDOMGENERATE == STD_ON)))

#undef DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE
#define DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE          (STD_ON)

#define DCM_RANDOM_SEED_CSM_ID                          (CSM_HAEPSEUDORANDOMSEED_L21_INDEX)
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEPSEUDORANDOMGENERATE_L21_INDEX)

/* For Pseudo Random Generate */
static boolean Dcm_GblSetHaePseudoSeed = DCM_FALSE;

#elif ((defined(CSM_RANDOM_HAEHACRANDOMSEED) && (CSM_RANDOM_HAEHACRANDOMSEED == STD_ON)) \
  && (defined(CSM_RANDOM_HAEHACRANDOMGENERATE) && (CSM_RANDOM_HAEHACRANDOMGENERATE == STD_ON)))

 /* polyspace +1 MISRA-C3:20.5 [Justified:Low] "Not a defect" */
#undef DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE
#define DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE          (STD_ON)

#define DCM_RANDOM_SEED_CSM_ID                          (CSM_HAEHACRANDOMSEED_L21_INDEX)
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEHACRANDOMGENERATE_L21_INDEX)

/* For HAC Random Generate */
static boolean Dcm_GblSetHaePseudoSeed = DCM_FALSE;
#else
#error "Dcm_DspSecureServices.c Random generate configuration error!"
#endif


#define DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM               (STD_OFF)

#if ((defined(CSM_SIGNATURE_AUTHSMPKCS1V15SHA1VERIFY) \
    && (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1VERIFY == STD_ON)) \
  && (defined(CSM_SIGNATURE_AUTHSMPKCS1V15SHA1SEEDVERIFY) \
    && (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1SEEDVERIFY == STD_ON)))

#if HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
#undef DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM
#define DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM               (STD_ON)
#endif

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_AUTHSMPKCS1V15SHA1VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_AUTHSMPKCS1V15SHA1SEEDVERIFY_L21_INDEX)

#elif ((defined(CSM_SIGNATURE_AUTHSMPKCS1V15SHA256VERIFY) \
    && (CSM_SIGNATURE_AUTHSMPKCS1V15SHA256VERIFY == STD_ON)) \
  && (defined(CSM_SIGNATURE_AUTHSMPKCS1V15SHA256SEEDVERIFY) \
    && (CSM_SIGNATURE_AUTHSMPKCS1V15SHA256SEEDVERIFY == STD_ON)))

#if HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
#undef DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM
#define DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM               (STD_ON)
#endif

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_AUTHSMPKCS1V15SHA256VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_AUTHSMPKCS1V15SHA256SEEDVERIFY_L21_INDEX)

#elif ((defined(CSM_SIGNATURE_HAEPKCS1V15SHA1VERIFY) \
    && (CSM_SIGNATURE_HAEPKCS1V15SHA1VERIFY == STD_ON)) \
  && (defined(CSM_SIGNATURE_HAEPKCS1V15SHA1SEEDVERIFY) \
    && (CSM_SIGNATURE_HAEPKCS1V15SHA1SEEDVERIFY == STD_ON)))

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_HAEPKCS1V15SHA1VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_HAEPKCS1V15SHA1SEEDVERIFY_L21_INDEX)

#elif ((defined(CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY) \
    && (CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY == STD_ON)) \
  && (defined(CSM_SIGNATURE_HAEPKCS1V15SHA256SEEDVERIFY) \
    && (CSM_SIGNATURE_HAEPKCS1V15SHA256SEEDVERIFY == STD_ON)))

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_HAEPKCS1V15SHA256VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_HAEPKCS1V15SHA256SEEDVERIFY_L21_INDEX)

#elif ((defined(CSM_SIGNATURE_ESCPKCS1V15SHA1VERIFY) \
    && (CSM_SIGNATURE_ESCPKCS1V15SHA1VERIFY == STD_ON)) \
  && (defined(CSM_SIGNATURE_ESCPKCS1V15SHA1SEEDVERIFY) \
    && (CSM_SIGNATURE_ESCPKCS1V15SHA1SEEDVERIFY == STD_ON)))

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_ESCPKCS1V15SHA1VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_ESCPKCS1V15SHA1SEEDVERIFY_L21_INDEX)

#elif ((defined(CSM_SIGNATURE_ESCPKCS1V15SHA256VERIFY) \
    && (CSM_SIGNATURE_ESCPKCS1V15SHA256VERIFY == STD_ON)) \
  && (defined(CSM_SIGNATURE_ESCPKCS1V15SHA256SEEDVERIFY) \
    && (CSM_SIGNATURE_ESCPKCS1V15SHA256SEEDVERIFY == STD_ON)))

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_ESCPKCS1V15SHA256VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_ESCPKCS1V15SHA256SEEDVERIFY_L21_INDEX)

#else
#error "Dcm_DspSecureServices.c PKCS#1 V1.5 configuration error!"
#endif

#if (defined (CSM_PKCS1V15SHA256VERIFY_CRL_L21_INDEX))
#define DCM_SIGNATURE_VERIFY_CRL_CSM_ID                 (CSM_PKCS1V15SHA256VERIFY_CRL_L21_INDEX)
#endif

#if (defined (CSM_SHA256_CRL_INDEX))
#define DCM_SHA256_CRL_CSM_ID                 (CSM_SHA256_CRL_INDEX)
#endif


#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
#endif
static VAR(Csm_AsymPublicKeyType, DCM_VAR) Dcm_GddSignPublicKey;

static VAR(Csm_AsymPublicKeyType, DCM_VAR) Dcm_GddTesterSignPublicKey;
#if (DCM_SECURITY_CRL_ENABLE == STD_ON)

/* for Dcm UnitTest*/
#ifndef DCM_MODULE_ACTIVE
static
#endif

VAR(Csm_AsymPublicKeyType, DCM_VAR) Dcm_GddHashPublicKeyVal;
#endif
#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
#pragma ghs section
#endif



typedef enum
{
  DCM_CS_READY,
  DCM_CS_SERVER_CERT,
  DCM_CS_CRL_CERT,
  DCM_CS_CRL_KEYID,
  DCM_CS_MAKE_RANDOM,
  DCM_CS_TESTER_CERT,
} Dcm_CertStageType;

typedef enum
{
  DCM_CP_READY,
  DCM_CP_CRL_READY,
  DCM_CP_CRL_KEYID_READY,
  DCM_CP_DOING,
  DCM_CP_SUCCESS,
  DCM_CP_FAIL,
  DCM_CP_CRL_FAIL
} Dcm_CertProgressStatusType;

typedef enum
{
  DCM_CAS_READY,
  DCM_CAS_REQ_START,
  DCM_CAS_REQ_UPDATE,
  DCM_CAS_REQ_FINISH
} Dcm_CertAlgorithmStepType;

static FUNC(void, DCM_CODE) Dcm_DspSecure_MemCopy(  
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) aDest,
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) aSrc,
  CONST(uint32, DCM_CONST) aSize);

static VAR(Dcm_CertStageType, DCM_VAR) Dcm_GddCertStage;
static VAR(Dcm_CertProgressStatusType, DCM_VAR) Dcm_GddCertProgress;
static VAR(Dcm_CertAlgorithmStepType, DCM_VAR) Dcm_GddCertAlgorithmStep;

static VAR(Dcm_CertInfoType, DCM_APPL_DATA) Dcm_GstCertificationInfo;

#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
#endif
static VAR(uint8, DCM_VAR) Dcm_GaaSecureData[PLAINDATA + DCM_CERTIFICATE_SIGNATURE];
#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
#pragma ghs section
#endif

/*Certification Authority Reference Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCertAuthorityReference[DCM_AUTHORITY_REFERENCE];
/*Authorization Role Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaAuthorizationRole[DCM_HOLDER_ROLE];
/*Expiration Date Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaEffectiveDate[DCM_EFFECTIVE_DATE];
/*Expiration Date Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaExpirationDate[DCM_EXPERATION_DATE];
/*Certificate Holder Reference */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCertHolderReference[DCM_HOLDER_REFERENCE];

#if (DCM_SECURITY_CRL_ENABLE == STD_ON)
/*CRL Issuer Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLIssuer[DCM_CRL_ISSUER];
/*CRL Certification Group Count Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLCertGroupCount[DCM_CRL_CERT_GROUP_COUNT];
/*CRL Certification Authority Key ID Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLCertAuthorityKeyID[DCM_CRL_CERT_AUTHORITY_KEYID];
/*CRL Effective Date Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLEffectiveDate[DCM_CRL_EFFECTIVE_DATE];
/*CRL Expiration Date Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLExpirationDate[DCM_CRL_EXPIRATION_DATE];
/*CRL Distribution Point Name */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLDistributionPointName[DCM_CRL_DISTRIBUTION_NAME];
/*CRL Revoked Cert Start Seq Num */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLRevokedCertStartSeqNum[DCM_CRL_REVOKED_CERT_START_SEQNUM];
/*CRL Distribution Point Name */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLCertStatusSize[DCM_CRL_CERT_STATUS_SIZE];
/*CRL Distribution Point Name */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLCertStatusBits[DCM_CRL_CERT_STATUSBITS_MAX_SIZE];

static VAR(uint32, DCM_NOINIT_DATA) Dcm_GaaConvPresendDate;

/*CRL Distribution Point Name */

/* for Dcm UnitTest*/
#ifndef DCM_MODULE_ACTIVE
static
#endif
VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaHashPublicKey[DCM_CRL_CERT_AUTHORITY_KEYID];

/* for Dcm UnitTest*/
#ifndef DCM_MODULE_ACTIVE
static
#endif
VAR(uint32, DCM_NOINIT_DATA) Dcm_GaaCRLHashLength;
#endif /* #if (DCM_SECURITY_CRL_ENABLE == STD_ON) */

#if (DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE == STD_ON)
#ifdef DCM_MODULE_ACTIVE
static
#endif
VAR(uint8, DCM_VAR) Dcm_GaaHaeHacSalt[DCM_HAE_HAC_RANDOM_SEED_LENGTH];
#endif


#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
#endif
static VAR(Csm_VerifyResultType, DCM_VAR) Dcm_GddVerifyResult;
static VAR(uint8, DCM_VAR) Dcm_GaaSecureSeed[DCM_SECURE_SEED_SIZE];
#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
#pragma ghs section
#endif

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dcm_Secure_Init                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function initializes the secure service Module.**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dcm_GddVerifyResult,                                **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, DCM_CODE) Dcm_Secure_Init(void)
{
  Dcm_GddVerifyResult = CSM_E_VER_NOT_OK;
  
  Dcm_GddCertStage = DCM_CS_READY;
  Dcm_GddCertProgress = DCM_CP_READY;
  Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_MemCopy                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : It is used to copy the data from  src to dest.      **
**                        module                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : src                                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dest                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DspSecure_MemCopy(  
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) aDest,
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) aSrc,
  CONST(uint32, DCM_CONST) aSize)

{
  uint32 i = 0U;

  if ((NULL_PTR != aDest) && (NULL_PTR != aSrc))
  {
    for (i = 0; i < aSize; i++)
    {
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "Not a defect" */	
      aDest[i] = aSrc[i];
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspConvertNum                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : It is used to convert number from hex to dec.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : src                                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dest                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if (DCM_SECURITY_CRL_ENABLE == STD_ON)
static FUNC(uint32, DCM_CODE) Dcm_DspConvertNum(  
  CONST(uint32, DCM_CONST) aNum)

{
  uint32 temp, temp2, expo, retVal = 0U;
  uint8 count, i = 0U;

  
  temp = aNum;
  count = 0U;
  while(temp>0)
  { 

    temp2 = temp%16U;
    temp = temp/16U;

    expo = 1U;
    i = count;

    while(i>0)
    {
      expo = expo*10U;
      i--;
    }
    
    retVal += temp2*expo;
    count++;
   
  }

  return retVal;
  
}
#endif


/*******************************************************************************
** Function Name        : Dcm_DspParsePlaintext                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function parses the certification come from    **
**                        tester.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DspParsePlaintext(
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) pSecureData)
{
  uint8 *LpExponent;
  
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) LpSecureData;
  LpSecureData = pSecureData;

  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_PROFILE_ID];

  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCertAuthorityReference, LpSecureData, DCM_AUTHORITY_REFERENCE);
  
  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_AUTHORITY_REFERENCE];

  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaEffectiveDate, LpSecureData, DCM_EFFECTIVE_DATE);

  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_EFFECTIVE_DATE];

  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaExpirationDate, LpSecureData, DCM_EXPERATION_DATE);

  /* set pointer to read the AuthorizationRole data */
  LpSecureData = &LpSecureData[DCM_EXPERATION_DATE + DCM_AUTHORIZATION_OBJECT_ID];

  /* copy Certificate Holder Authorization */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCertHolderReference, LpSecureData, DCM_HOLDER_REFERENCE);

  /* set pointer to read the AuthorizationRole data */
  LpSecureData = &LpSecureData[DCM_HOLDER_REFERENCE];

  /* copy Certificate Holder Authorization */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaAuthorizationRole, LpSecureData, DCM_HOLDER_ROLE);

  /* set pointer to read the exponent data */
  LpSecureData = &LpSecureData[DCM_HOLDER_ROLE + DCM_PUBKEY_OBJECT_ID];

  Dcm_GddTesterSignPublicKey.length = DCM_PUBLICKEY_MODULUS + 4U;

  /* copy the exponent data */
/*  (void)Dcm_DspSecure_MemCopy(&(Dcm_GddSignPublicKey.data[(DCM_PUBLICKEY_MODULUS) / sizeof(Csm_AlignType)]),
    LpSecureData, 4);*/

  LpExponent = &(Dcm_GddTesterSignPublicKey.data[(DCM_PUBLICKEY_MODULUS) / sizeof(Csm_AlignType)]);
  #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)  
  LpExponent[0] = LpSecureData[3];
  LpExponent[1] = LpSecureData[2];
  LpExponent[2] = LpSecureData[1];
  LpExponent[3] = LpSecureData[0];
  #else
  LpExponent[0] = LpSecureData[0];
  LpExponent[1] = LpSecureData[1];
  LpExponent[2] = LpSecureData[2];
  LpExponent[3] = LpSecureData[3];
  #endif

  /* set pointer to read the Modulus data */
  LpSecureData = &LpSecureData[DCM_PUBLICKEY_EXPONENT];

  (void)Dcm_DspSecure_MemCopy((uint8*)(Dcm_GddTesterSignPublicKey.data),
    LpSecureData, DCM_PUBLICKEY_MODULUS);
}

/*******************************************************************************
** Function Name        : Dcm_DspParseCRLPlaintext                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function parses the CRL come from              **
**                        tester.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_SECURITY_CRL_ENABLE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_DspParseCRLPlaintext(
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) pSecureData)
{

  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) LpSecureData;
  LpSecureData = pSecureData;

  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_CRL_VERSION + DCM_CRL_SIGNATURE_ALGORITHM];

  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLIssuer, LpSecureData, DCM_CRL_ISSUER);

  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_CRL_ISSUER];

  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLDistributionPointName, LpSecureData, DCM_CRL_DISTRIBUTION_NAME);

  /* set pointer to read the Effective data */
  LpSecureData = &LpSecureData[DCM_CRL_DISTRIBUTION_NAME];
  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLCertGroupCount, LpSecureData, DCM_CRL_CERT_GROUP_COUNT);  

  /* set pointer to read the Effective data */
  LpSecureData = &LpSecureData[DCM_CRL_CERT_GROUP_COUNT];
  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLCertAuthorityKeyID, LpSecureData, DCM_CRL_CERT_AUTHORITY_KEYID);  
  
  /* set pointer to read the Effective data */
  LpSecureData = &LpSecureData[DCM_CRL_CERT_AUTHORITY_KEYID];
  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLEffectiveDate, LpSecureData, DCM_CRL_EFFECTIVE_DATE);  

  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_CRL_EFFECTIVE_DATE];
  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLExpirationDate, LpSecureData, DCM_CRL_EXPIRATION_DATE);

  /* set pointer to read the AuthorizationRole data */
  LpSecureData = &LpSecureData[DCM_EXPERATION_DATE];

  /* copy Certificate Holder Authorization */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLRevokedCertStartSeqNum, LpSecureData, DCM_CRL_REVOKED_CERT_START_SEQNUM);

  /* set pointer to read the AuthorizationRole data */
  LpSecureData = &LpSecureData[DCM_CRL_REVOKED_CERT_START_SEQNUM];

  /* copy Certificate Holder Authorization */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLCertStatusSize, LpSecureData, DCM_CRL_CERT_STATUS_SIZE);

  /* set pointer to read the AuthorizationRole data */
  LpSecureData = &LpSecureData[DCM_CRL_CERT_STATUS_SIZE];

  /* copy Certificate Holder Authorization */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLCertStatusBits, LpSecureData, (Dcm_GaaCRLLegnth - CRL_FIXED_PLAINDATA - DCM_CRL_SIGNATURE));


}
#endif


/*******************************************************************************
** Function Name        : Dcm_DspDoRandomSeed                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function provide the input data to the Random  **
**                        Seed service                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspDoRandomSeed(void)
{
  Std_ReturnType LddRetVal = E_OK;

  uint8 count;
  
  for(count=0; count<DCM_HAE_HAC_RANDOM_SEED_LENGTH; count++)
    {
       Dcm_GaaHaeHacSalt[count]=0U;
    }
  

  
  if (Dcm_GblSetHaePseudoSeed == DCM_FALSE)
  {
    /* Get RandomSeed */
    LddRetVal = Dcm_GetRandomSeed(Dcm_GaaHaeHacSalt);

    /* Update RandomSeed */
    if (LddRetVal == E_OK)
    {
      LddRetVal = Csm_RandomSeedStart(DCM_RANDOM_SEED_CSM_ID);
    }

    if (LddRetVal == E_OK)
    {
      LddRetVal = Csm_RandomSeedUpdate(DCM_RANDOM_SEED_CSM_ID,
        Dcm_GaaHaeHacSalt, DCM_HAE_HAC_RANDOM_SEED_LENGTH);
    }

    if (LddRetVal == E_OK)
    {
      LddRetVal = Csm_RandomSeedFinish(DCM_RANDOM_SEED_CSM_ID);
    }

    if (LddRetVal == E_OK)
    {
      Dcm_GblSetHaePseudoSeed = DCM_TRUE;
    }
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetRandomNum                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function generate random number                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : randomLength                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : random                                              **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS == STD_OFF) \
 && (DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM == STD_OFF))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetRandomNum(uint8* random,
  uint32 randomLength)
{
  Std_ReturnType LddRetVal;

  if ((random == NULL_PTR) || (randomLength != DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH))
  {
    LddRetVal = E_NOT_OK;
  }
  else
  {
    #if ((DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM == STD_ON) \
      || (DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE == STD_ON))
    LddRetVal = Csm_RandomGenerate(DCM_RANDOM_GENERATE_CSM_ID,
      random, randomLength);
    #endif

    #if (DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE == STD_ON)
    if (LddRetVal == CSM_E_ENTROPY_EXHAUSTION)
    {
      Dcm_GblSetHaePseudoSeed = DCM_FALSE;
      LddRetVal = Dcm_DspDoRandomSeed();

      if (LddRetVal == E_OK)
      {
        LddRetVal = Csm_RandomGenerate(DCM_RANDOM_GENERATE_CSM_ID,
          random, randomLength);
      }
    }
    #endif
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetSeedForSA                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Dcm_DspGetSeedForSA provides a means not only  **
**                        to process secure access for signature but also to  **
**                        get seed data.                                      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Seed, Error                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : DCM_ES95489_SUPPORT                                 **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/*polyspace<MISRA-C:16.4:Not a defect:Justify with annotations> This function depends on user configuration*/
/* polyspace +2 MISRA-C3:8.13 [Justified:Low] "Not a defect" */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetSeedForSA(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pSecurityAccessRecord,
  VAR(uint8, AUTOMATIC) LucOpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pSeed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrCode)
{
  Std_ReturnType LddRetVal = E_OK;
  uint8 LucIndex;

  if (DCM_INITIAL == LucOpStatus)
  {
    Dcm_Secure_Init();
  }

  switch (Dcm_GddCertProgress)
  {
  case DCM_CP_READY:
    if (Dcm_GddCertStage == DCM_CS_READY)
    {
      if (Dcm_GddCertAlgorithmStep == DCM_CAS_READY)
      {
	/* polyspace +2 MISRA-C3:9.3 [Justified:Low] "Not a defect" */
	/* polyspace +1 MISRA-C3:9.1 [Justified:Low] "Not a defect" */
        uint8 LaaPublicKey[DCM_PUBLICKEY_MODULUS] = {0U, };

        #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
        CONST(uint8, DCM_CONST) LaaTempExponent[4] = { 0x01U, 0x00U, 0x01U, 0x00U };
        #else
        CONST(uint8, DCM_CONST) LaaTempExponent[4] = { 0x00U, 0x01U, 0x00U, 0x01U };
        #endif

        /* Get the server's public key from FBL */
        Dcm_GetPublicKey(LaaPublicKey);

        Dcm_GddSignPublicKey.length = DCM_PUBLICKEY_MODULUS + 4U;

        (void)Dcm_DspSecure_MemCopy((uint8*)(Dcm_GddSignPublicKey.data),
          LaaPublicKey, DCM_PUBLICKEY_MODULUS);

        (void)Dcm_DspSecure_MemCopy(
          (uint8*)&(Dcm_GddSignPublicKey.data[(DCM_PUBLICKEY_MODULUS) / sizeof(Csm_AlignType)]),
          LaaTempExponent, 4);

        #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
		{
			uint8 LaaTempHashExponent[4] = { 0x00U, 0x01U, 0x00U, 0x01U };
	        /* public key for hash  */
	         Dcm_GddHashPublicKeyVal.length = DCM_PUBLICKEY_MODULUS + 4U;

	        (void)Dcm_DspSecure_MemCopy(
	            (uint8*)&(Dcm_GddHashPublicKeyVal.data), LaaTempHashExponent, 4);

	        (void)Dcm_DspSecure_MemCopy((uint8*)&(Dcm_GddHashPublicKeyVal.data[4U]),
	          LaaPublicKey, DCM_PUBLICKEY_MODULUS);
		  }
        #endif
          
        if (Csm_SignatureVerifyStart(DCM_SIGNATURE_VERIFY_CSM_ID, &Dcm_GddSignPublicKey) == E_OK)
        {
          (void)Dcm_DspSecure_MemCopy(Dcm_GaaSecureData, pSecurityAccessRecord,
            PLAINDATA + DCM_CERTIFICATE_SIGNATURE);

          LddRetVal = DCM_SECURE_PENDING;

          Dcm_GddCertStage = DCM_CS_SERVER_CERT; /* Server signature verification */
          Dcm_GddCertProgress = DCM_CP_DOING;
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_START;
        }
        else
        {
          *pErrCode = DCM_E_SECURITYACCESSDENIED;
          LddRetVal = E_NOT_OK;
        }
      }
      else
      {
      }
    }
    else
    {
    }    
    break;
	
  #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
  case DCM_CP_CRL_READY:
  {
    uint32 ExpirationDate;
    Dcm_DspParsePlaintext(Dcm_GaaSecureData);

    /*  1. date check  */
    if(NULL_PTR != Dcm_GaaCbkPresentDate.pGetPresentDateFun)
    {
      (void)Dcm_GaaCbkPresentDate.pGetPresentDateFun(Dcm_GaaPresentDate);
    }
    Dcm_GaaConvPresendDate = 
	(uint32)((uint32)((Dcm_GaaPresentDate[0]) 	<< 16U) +
    (uint32)((Dcm_GaaPresentDate[1]) 			<< 8U) +  
	(uint32)(Dcm_GaaPresentDate[2]));

    Dcm_GaaConvPresendDate = Dcm_DspConvertNum(Dcm_GaaConvPresendDate);

    ExpirationDate = (uint32)((uint32)((Dcm_GaaExpirationDate[0]) << 16U) +
                  (uint32)((Dcm_GaaExpirationDate[1]) << 8U) +  (uint32)(Dcm_GaaExpirationDate[2]));

    ExpirationDate = Dcm_DspConvertNum(ExpirationDate);


    if((Dcm_GaaConvPresendDate != 0) && (Dcm_GaaConvPresendDate <= ExpirationDate))    
    {
      #ifdef DCM_SIGNATURE_VERIFY_CRL_CSM_ID
      /* 7. CRL Integrity check  */
      if (Csm_SignatureVerifyStart(DCM_SIGNATURE_VERIFY_CRL_CSM_ID, &Dcm_GddSignPublicKey) == E_OK)
      {
        P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pSARecord;
        pSARecord = Dcm_GstMsgContext.reqData;
        (void)Dcm_DspSecure_MemCopy(Dcm_GaaSecureData, &pSARecord[PLAINDATA + DCM_CERTIFICATE_SIGNATURE+1],
         Dcm_GaaCRLLegnth);

        LddRetVal = DCM_SECURE_PENDING;

        Dcm_GddCertStage = DCM_CS_CRL_CERT; /* Server signature verification => need to change */ 
        Dcm_GddCertProgress = DCM_CP_DOING;
        Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_START;
      }
      else
      #endif
      {
        *pErrCode = DCM_E_CRLINTEGRITYCHECKFAILED;
        LddRetVal = E_NOT_OK;
      }       

    }
    else
    {
      *pErrCode = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
      LddRetVal = E_NOT_OK;       
    }


    break;
    }

  case DCM_CP_CRL_KEYID_READY:

    /* 6. CRL Key Identifier Check - public key hash */
    #ifdef DCM_SHA256_CRL_CSM_ID
    if (Csm_HashStart(DCM_SHA256_CRL_CSM_ID) == E_OK)
    {
      LddRetVal = DCM_SECURE_PENDING;

      Dcm_GddCertStage = DCM_CS_CRL_KEYID;
      Dcm_GddCertProgress = DCM_CP_DOING;
      Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_START;
    }
    else
    #endif
    {
      *pErrCode = DCM_E_CRLINTEGRITYCHECKFAILED;
      LddRetVal = E_NOT_OK;
    }

    break;
  #endif
  case DCM_CP_DOING:
    LddRetVal = DCM_SECURE_PENDING;
    break;

  case DCM_CP_SUCCESS:
  {
    #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
    boolean checkFail = DCM_FALSE;
    uint8 count;

    Dcm_DspParseCRLPlaintext(Dcm_GaaSecureData);

    /* 6. Public key Identifier check */
    checkFail = DCM_FALSE;
    for(count = 0; count < DCM_CRL_CERT_AUTHORITY_KEYID ; count++)
    {
      if(Dcm_GaaHashPublicKey[count] != Dcm_GaaCRLCertAuthorityKeyID[count])
      {
        checkFail = DCM_TRUE;
        break;
      }
    }

    if(checkFail == DCM_FALSE)
    {
      /*  1. CRL ExpirationDate Check */
      uint32 ExpirationDate;

      ExpirationDate = (uint32)((uint32)((Dcm_GaaCRLExpirationDate[0]) << 16U) +
                    (uint32)((Dcm_GaaCRLExpirationDate[1]) << 8U) +  (uint32)(Dcm_GaaCRLExpirationDate[2]));

      ExpirationDate = Dcm_DspConvertNum(ExpirationDate);

      if((Dcm_GaaConvPresendDate != 0) && (Dcm_GaaConvPresendDate <= ExpirationDate))
      {
        /*  2. Authority Reference Check  */
        for(count = 0; count < DCM_AUTHORITY_REFERENCE ; count++)
        {
          if(Dcm_GaaCertAuthorityReference[count] != Dcm_GaaCRLIssuer[count])
          {
            checkFail = DCM_TRUE;
            break;
          }
        }

        if(checkFail == DCM_FALSE)
        {

          uint32 holderReference, crlDistributionPoint, crlCertGroupCount;
	      /* polyspace +2 RTE:NIVL [Justified:Low] "Not a defect" */
          holderReference = (uint32)(((Dcm_GaaCertHolderReference[12]) << 24U) +  (uint32)((Dcm_GaaCertHolderReference[13]) << 16U) +
                            (uint32)((Dcm_GaaCertHolderReference[14]) << 8U) +  (uint32)(Dcm_GaaCertHolderReference[15]));

          holderReference = Dcm_DspConvertNum(holderReference);
          /* polyspace +2 RTE:NIVL [Justified:Low] "Not a defect" */
          crlDistributionPoint = (uint32)(((Dcm_GaaCRLDistributionPointName[12]) << 24U) +  (uint32)((Dcm_GaaCRLDistributionPointName[13]) << 16U) +
                            (uint32)((Dcm_GaaCRLDistributionPointName[14]) << 8U) +  (uint32)(Dcm_GaaCRLDistributionPointName[15]));

          crlDistributionPoint = Dcm_DspConvertNum(crlDistributionPoint);

	      /* polyspace +2 RTE:NIVL [Justified:Low] "Not a defect" */
          crlCertGroupCount = (uint32)(((Dcm_GaaCRLCertGroupCount[0]) << 24U) +  (uint32)((Dcm_GaaCRLCertGroupCount[1]) << 16U) +
                            (uint32)((Dcm_GaaCRLCertGroupCount[2]) << 8U) +  (uint32)(Dcm_GaaCRLCertGroupCount[3]));

          crlCertGroupCount = Dcm_DspConvertNum(crlCertGroupCount);

          /*  3. Company, Group Information Check */

          if((crlCertGroupCount != 0) && ((((holderReference -1U)/crlCertGroupCount)+1U ) == crlDistributionPoint))
          {

            /*  4. CRL Distribution Point Check */
            checkFail = DCM_FALSE;
            for(count = 0; count < (DCM_HOLDER_REFERENCE-4U) ; count++)
            {
              if(Dcm_GaaCertHolderReference[count] != Dcm_GaaCRLDistributionPointName[count])
              {
                checkFail = DCM_TRUE;
                break;
              }
            }

            if(checkFail == DCM_FALSE)
            {
              uint32 startSeqNum;
	          /* polyspace +2 RTE:NIVL [Justified:Low] "Not a defect" */
              startSeqNum = (uint32)(((Dcm_GaaCRLRevokedCertStartSeqNum[0]) << 24U) +  (uint32)((Dcm_GaaCRLRevokedCertStartSeqNum[1]) << 16U) +
                            (uint32)((Dcm_GaaCRLRevokedCertStartSeqNum[2]) << 8U) +  (uint32)(Dcm_GaaCRLRevokedCertStartSeqNum[3]));

              startSeqNum = Dcm_DspConvertNum(startSeqNum);

              /*   5. CRL Start num check */
              if( (((holderReference / crlCertGroupCount) * crlCertGroupCount) +1U ) == startSeqNum)
              {

                
                /* 8. CRL check */
                boolean isCrlList = DCM_FALSE;
                uint32 crlCount;
                uint32 certStatusSize;
                uint8 mBit;

		        /* polyspace +2 RTE:NIVL [Justified:Low] "Not a defect" */
                certStatusSize = (uint32)(((Dcm_GaaCRLCertStatusSize[0]) << 24U) +  (uint32)((Dcm_GaaCRLCertStatusSize[1]) << 16U) +
                                 (uint32)((Dcm_GaaCRLCertStatusSize[2]) << 8U) +  (uint32)(Dcm_GaaCRLCertStatusSize[3]));


                certStatusSize = Dcm_DspConvertNum(certStatusSize);

                if(certStatusSize > DCM_CRL_CERT_STATUSBITS_MAX_SIZE )
                {
                  certStatusSize = DCM_CRL_CERT_STATUSBITS_MAX_SIZE;
                }

                /* Validity Check */
                for(crlCount = 0 ; crlCount < certStatusSize; crlCount++)
                {
                  for(mBit = 0 ; mBit < 8U; mBit++)
                  {
		            /* polyspace +1 MISRA-C3:10.1 [Justified:Low] "Not a defect" */  
                    if( ((Dcm_GaaCRLCertStatusBits[crlCount] << mBit) & 0x80) == 0x80)
                    {
                         if((startSeqNum+(crlCount*8U)+mBit) == holderReference)
                           {
                              isCrlList = DCM_TRUE;
                              break;
                           }
                     }
                   }

                  if(isCrlList == DCM_TRUE)
                  {
                    *pErrCode = DCM_E_CONDITIONSNOTCORRECT;
                    LddRetVal = E_NOT_OK;
                    break;
                  }
                }

              }
              else
              {
                *pErrCode = DCM_E_CONDITIONSNOTCORRECT;
                LddRetVal = E_NOT_OK;       
              } 
            }
            else
            {
              *pErrCode = DCM_E_CONDITIONSNOTCORRECT;
              LddRetVal = E_NOT_OK;       
            }
          }
          else
          {
            *pErrCode = DCM_E_CONDITIONSNOTCORRECT;
            LddRetVal = E_NOT_OK;       
          }
        }
        else
        {
          *pErrCode = DCM_E_CONDITIONSNOTCORRECT;
          LddRetVal = E_NOT_OK;       
        }

      }
      else
      {
        *pErrCode = DCM_E_CRLEXPIRED;
        LddRetVal = E_NOT_OK;       
      }
    }
    else
    {
      *pErrCode = DCM_E_CRLINTEGRITYCHECKFAILED;
      LddRetVal = E_NOT_OK;
    }

    #else
      Dcm_DspParsePlaintext(Dcm_GaaSecureData);
    #endif


    if (LddRetVal != E_NOT_OK)
    {
      #if ((DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS == STD_ON) \
        || (DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM == STD_ON))

      if ( (Dcm_GddCertStage == DCM_CS_SERVER_CERT) || (Dcm_GddCertStage == DCM_CP_CRL_KEYID_READY))
      {
        Dcm_GddCertStage = DCM_CS_MAKE_RANDOM;
        Dcm_GddCertProgress = DCM_CP_DOING;
        Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_START;
        /* Async function */
        #if (DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS == STD_ON)
        /* RH850 F1K */
        LddRetVal = Csm_RandomGenerate(DCM_RANDOM_GENERATE_CSM_ID,
          pSeed, DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH);
        #elif (DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM == STD_ON)
        /* RH850 F1KM */
        LddRetVal = Csm_RandomGenerate(DCM_RANDOM_GENERATE_CSM_ID,
          Dcm_GaaRandom, DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH);
        #endif

        if (LddRetVal == E_OK)
        {
          LddRetVal = DCM_SECURE_PENDING;
        }
        else
        {
          *pErrCode = DCM_E_SECURITYACCESSDENIED;
          LddRetVal = E_NOT_OK;
        }
      }
      else if (Dcm_GddCertStage == DCM_CS_MAKE_RANDOM)
      {
        #if (DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM == STD_ON)
    	  (void)Dcm_DspSecure_MemCopy(pSeed, Dcm_GaaRandom,
          DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH);
        #endif
        for (LucIndex = 0; LucIndex < DCM_SECURE_SEED_SIZE; LucIndex++)
        {
          Dcm_GaaSecureSeed[LucIndex] = pSeed[LucIndex];
        }

        Dcm_Secure_Init();
      }
      else
      {
      
      }

      #else

      #if (DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE == STD_ON)
      LddRetVal = Dcm_DspDoRandomSeed();

      if (LddRetVal == E_OK)
      {
        LddRetVal = Dcm_DspGetRandomNum(pSeed, DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH);
      }
      #else
      LddRetVal = Dcm_DspGetRandomNum(pSeed, DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH);
      #endif

      if (LddRetVal == E_OK)
      {
        for (LucIndex = 0; LucIndex < DCM_SECURE_SEED_SIZE; LucIndex++)
        {
          Dcm_GaaSecureSeed[LucIndex] = pSeed[LucIndex];
        }
      }
      else
      {
        *pErrCode = DCM_E_SECURITYACCESSDENIED;
        LddRetVal = E_NOT_OK;
      }

      Dcm_Secure_Init();

      #endif
    }
  }
  break;

  case DCM_CP_CRL_FAIL:
    *pErrCode = DCM_E_CRLINTEGRITYCHECKFAILED;
    LddRetVal = E_NOT_OK;

    Dcm_Secure_Init();
    break;

  case DCM_CP_FAIL:
  default:
    *pErrCode = DCM_E_SECURITYACCESSDENIED;
    LddRetVal = E_NOT_OK;

    Dcm_Secure_Init();
    break;
  }
  
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspCompareKeyForSA                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Dcm_DspGetSeedForSA provides a means not only  **
**                        to process secure access for signature but also to  **
**                        compare key data.                                   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Key, OpStatus                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : DCM_ES95489_SUPPORT                                 **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA-C3:2.7 [Justified:Low] "Not a defect" */
/*polyspace<MISRA-C:16.4:Not a defect:Justify with annotations> This function depends on user configuration*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspCompareKeyForSA(
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) LpReqResData, 
  VAR(uint8, AUTOMATIC) LucOpStatus)
{
  Std_ReturnType LddRetVal = E_OK;

  switch (Dcm_GddCertProgress)
  {
  case DCM_CP_READY:
    if (Dcm_GddCertAlgorithmStep == DCM_CAS_READY)
    {
      if (Csm_SignatureVerifyStart(DCM_SIGNATURE_VERIFY_SEED_CSM_ID, &Dcm_GddTesterSignPublicKey) == E_OK)
      {
        (void)Dcm_DspSecure_MemCopy(Dcm_GaaSecureData, LpReqResData,
          DCM_CERTIFICATE_SIGNATURE);

        LddRetVal = DCM_SECURE_PENDING;

        Dcm_GddCertStage = DCM_CS_TESTER_CERT; /* Tester signature*/
        Dcm_GddCertProgress = DCM_CP_DOING;
        Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_START;
      }
      else
      {
        LddRetVal = E_NOT_OK;
      }
    }
    break;

  case DCM_CP_DOING:
    LddRetVal = DCM_SECURE_PENDING;
    break;

  case DCM_CP_SUCCESS:
    /* copy Certificate Expiration Date */
    (void)Dcm_DspSecure_MemCopy(Dcm_GstCertificationInfo.expirationDate, 
      Dcm_GaaExpirationDate, DCM_EXPERATION_DATE);

    /* copy Certificate Holder Authorization */
    (void)Dcm_DspSecure_MemCopy(Dcm_GstCertificationInfo.authorization, 
      Dcm_GaaAuthorizationRole, DCM_HOLDER_ROLE);
    
    Dcm_Secure_Init();
    break;

  case DCM_CP_FAIL:
  default:
    LddRetVal = E_NOT_OK;

    Dcm_Secure_Init();
    break;
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspVerifySignatureSeedCbk                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Dcm_DspVerifySignatureSeedCbk provides a means **
**                        not only to process secure access for signature but **
**                        also to compare key data.                           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Key, OpStatus                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : DCM_ES95489_SUPPORT                                 **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspVerifySignatureSeedCbk(Std_ReturnType retVal)
{
  if(E_OK == retVal)
  {
    switch (Dcm_GddCertStage)
    {
    case DCM_CS_SERVER_CERT:
      switch (Dcm_GddCertAlgorithmStep)
      {
      case DCM_CAS_REQ_START:
        if (Csm_SignatureVerifyUpdate(DCM_SIGNATURE_VERIFY_CSM_ID, Dcm_GaaSecureData, PLAINDATA) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_UPDATE;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        break;

      case DCM_CAS_REQ_UPDATE:
        if (Csm_SignatureVerifyFinish(DCM_SIGNATURE_VERIFY_CSM_ID, &Dcm_GaaSecureData[PLAINDATA],
          DCM_CERTIFICATE_SIGNATURE, &Dcm_GddVerifyResult) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_FINISH;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        break;

      case DCM_CAS_REQ_FINISH:
        if (Dcm_GddVerifyResult == CSM_E_VER_OK)
        {
          #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
            Dcm_GddCertProgress = DCM_CP_CRL_READY;
          #else
            Dcm_GddCertProgress = DCM_CP_SUCCESS;
          #endif
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
        break;

      default:
	/* Do Nothing */
        break;
      }
      break;
      
    #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
    case DCM_CS_CRL_CERT:
      switch (Dcm_GddCertAlgorithmStep)
      {
      case DCM_CAS_REQ_START:
        #ifdef DCM_SIGNATURE_VERIFY_CRL_CSM_ID
        if (Csm_SignatureVerifyUpdate(DCM_SIGNATURE_VERIFY_CRL_CSM_ID, Dcm_GaaSecureData, (Dcm_GaaCRLLegnth-DCM_CRL_SIGNATURE)) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_UPDATE;
        }
        else
        #endif
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        break;

      case DCM_CAS_REQ_UPDATE:
        #ifdef DCM_SIGNATURE_VERIFY_CRL_CSM_ID
        if (Csm_SignatureVerifyFinish(DCM_SIGNATURE_VERIFY_CRL_CSM_ID, &Dcm_GaaSecureData[Dcm_GaaCRLLegnth-DCM_CRL_SIGNATURE],
          DCM_CRL_SIGNATURE, &Dcm_GddVerifyResult) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_FINISH;
        }
        else
        #endif
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        break;

      case DCM_CAS_REQ_FINISH:
        if (Dcm_GddVerifyResult == CSM_E_VER_OK)
        {
          Dcm_GddCertProgress = DCM_CP_CRL_KEYID_READY;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
        break;

      default:
	      /* Do Nothing */
        break;
      }
      break;

     case DCM_CS_CRL_KEYID:
      switch (Dcm_GddCertAlgorithmStep)
      {
      case DCM_CAS_REQ_START:
        #ifdef DCM_SHA256_CRL_CSM_ID
        if (Csm_HashUpdate(DCM_SHA256_CRL_CSM_ID, Dcm_GddHashPublicKeyVal.data , Dcm_GddHashPublicKeyVal.length) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_UPDATE;
        }
        else
        #endif
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        break;

      case DCM_CAS_REQ_UPDATE:
      {
    	Dcm_GaaCRLHashLength = 32;
        #ifdef DCM_SHA256_CRL_CSM_ID
        if (Csm_HashFinish(DCM_SHA256_CRL_CSM_ID, Dcm_GaaHashPublicKey,
          &Dcm_GaaCRLHashLength, DCM_FALSE) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_FINISH;
        }
        else
        #endif
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        break;
      }

      case DCM_CAS_REQ_FINISH:
        if (Dcm_GddVerifyResult == CSM_E_VER_OK)
        {
          Dcm_GddCertProgress = DCM_CP_SUCCESS;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
        break;

      default:
	      /* Do Nothing */
        break;
      }
      break;
   #endif
      

    case DCM_CS_MAKE_RANDOM:
      if (Dcm_GddCertAlgorithmStep == DCM_CAS_REQ_START)
      {
        Dcm_GddCertProgress = DCM_CP_SUCCESS;
      }
      Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
      break;

    case DCM_CS_TESTER_CERT:
      switch (Dcm_GddCertAlgorithmStep)
      {
      case DCM_CAS_REQ_START:
        if (Csm_SignatureVerifyUpdate(DCM_SIGNATURE_VERIFY_SEED_CSM_ID, Dcm_GaaSecureSeed,
          DCM_SECURE_SEED_SIZE) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_UPDATE;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        break;

      case DCM_CAS_REQ_UPDATE:
        if (Csm_SignatureVerifyFinish(DCM_SIGNATURE_VERIFY_SEED_CSM_ID, Dcm_GaaSecureData,
          DCM_CERTIFICATE_SIGNATURE, &Dcm_GddVerifyResult) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_FINISH;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        break;

      case DCM_CAS_REQ_FINISH:
        if (Dcm_GddVerifyResult == CSM_E_VER_OK)
        {
          Dcm_GddCertProgress = DCM_CP_SUCCESS;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
        break;

      default:
	/* Do Nothing */
        break;
      }
      break;

    default:
      /* Do Nothing */
      break;
    }
  }
  else
  {
    if((Dcm_GddCertStage == DCM_CS_CRL_CERT) || (Dcm_GddCertStage == DCM_CS_CRL_KEYID))
    {
      Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
    }
    else
    {
      Dcm_GddCertProgress = DCM_CP_FAIL;
    }

     
  }

  return E_OK;
}

/*******************************************************************************
** Function Name        : Dcm_GetCertificationInfo                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Dcm_GetCertificationInfo provides information  **
**                        of the certification to application.                **
**                                                                            **
** Sync/Async           : synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpCertifInfo                                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : DCM_ES95489_SUPPORT                                 **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetCertificationInfo(
  P2VAR(Dcm_CertInfoType, AUTOMATIC, DCM_APPL_DATA) CertInfo)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 currentLevel;
      
  if (E_OK == Dcm_GetSecurityLevel(&currentLevel))
  {
    if (DcmConf_DcmDspSecurityRow_L21 == currentLevel)
    {
       /* copy Certificate Expiration Date */
      (void)Dcm_DspSecure_MemCopy(CertInfo->expirationDate, 
                  Dcm_GstCertificationInfo.expirationDate, DCM_EXPERATION_DATE);

      /* copy Certificate Holder Authorization */
      (void)Dcm_DspSecure_MemCopy(CertInfo->authorization, 
                       Dcm_GstCertificationInfo.authorization, DCM_HOLDER_ROLE);

      LddRetVal = E_OK;
    }
  }

  return LddRetVal;
}
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#else
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetCertificationInfo(
  P2VAR(Dcm_CertInfoType, AUTOMATIC, DCM_APPL_DATA) CertInfo)
{
  DCM_UNUSED_PTR(CertInfo);
  return E_NOT_OK;
}
/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* CSAC Algorithm */
/* 
  polyspace:end<MISRA-C:5.1:Not a defect:Justify with annotations> No Impact of this rule violation
  polyspace:end<MISRA-C:8.1:Not a defect:Justify with annotations> No Impact of this rule violation
  polyspace:end<MISRA-C:8.7:Not a defect:Justify with annotations> No Impact of this rule violation
  polyspace:end<MISRA-C:8.1:Not a defect:Justify with annotations> No Impact of this rule violation
  polyspace:end<MISRA-C:11.4:Not a defect:Justify with annotations> No Impact of this rule violation
  polyspace:end<MISRA-C:19.6:Not a defect:Justify with annotations> No Impact of this rule violation  
  polyspace:end<RTE: NIVL : Not a defect : No Action Planned > initialized local variable
  polyspace:end<RTE: NIV : Not a defect : No Action Planned > initialized variable
  polyspace:end<RTE: IDP : Not a defect : No Action Planned > address pointed to function is correct
  polyspace:end<RTE: ABS_ADDR : Not a defect : No Action Planned > All addresses passed to pointer's are fixed in the intended design
*/
/* polyspace-end RTE:OVFL [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Enter comment here" */
/* polyspace-end MISRA-C3:10.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.7 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.8 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:12.2 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:10.4 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.5 [Justified:Low] "Not a defect" */
/*******************************************************************************
 **                      End of File                                           **
 *******************************************************************************/
