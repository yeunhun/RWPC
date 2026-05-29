/*******************************************************************************
**  (C) 2014 HYUNDAI AUTRON Company                                           **
**  Confidential Proprietary Information Distribution Limited                 **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**                                                                            **
**  SRC-MODULE: Dcm_DspSecureServices.h                                       **
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
** 2.3.2.0   05-Nov-2020   EunKyung Kim    #26432                             **
**                                                                            **
** 1.0.3     11-25-2019    EunKyung Kim      #19580                           **
**                                                                            **
** 1.0.2     20-04-2017    Jin     Jung      #7075 #7079                      **
**                                                                            **
** 1.0.1     05-12-2016    Jin     Jung      #6869                            **
**                                                                            **
** 1.0.0     01-10-2015    Sungeol Baek      Initial Version                  **
*******************************************************************************/

#ifndef DCM_DSPSECURESERVICES_H
#define DCM_DSPSECURESERVICES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Platform_Types.h"
#include "Dcm_Cfg.h"

/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Macros for DCM_ES95489_SUPPORT                        **
*******************************************************************************/
#define DCM_CHKCERTIFICATION                ((uint8)0x01)
#define DCM_CHKKEY                          ((uint8)0x02)

#define DCM_SECURE_INITIAL                  ((uint8)0x00)
#define DCM_SECURE_COMPLETE                 ((uint8)0x01)
#define DCM_SECURE_FAILURE                  ((uint8)0x02)

/* For algorithm processing step */ 
#define DCM_ALGM_INITIAL                    ((uint8)0x00)
#define DCM_ALGM_UPDATE                     ((uint8)0x01)
#define DCM_ALGM_FINISH                     ((uint8)0x02)
#define DCM_ALGM_VERIFY                     ((uint8)0x03)

#define DCM_SECURE_SEED_SIZE                (8U)

#define DCM_CERT                            (0U)  
#define DCM_CERTCRL                         (1U)          

/* Certificate field information */
#define DCM_PROFILE_ID                      (1U)
#define DCM_AUTHORITY_REFERENCE             (14U)
#define DCM_EFFECTIVE_DATE                  (3U)
#define DCM_EXPERATION_DATE                 (3U)
#define DCM_AUTHORIZATION_OBJECT_ID         (23U)
#define DCM_HOLDER_REFERENCE                (16U)
#define DCM_HOLDER_ROLE                     (4U)
#define DCM_PUBKEY_OBJECT_ID                (20U)
#define DCM_PUBLICKEY_EXPONENT              (4U)
#define DCM_PUBLICKEY_MODULUS               (256U)
#define DCM_CERTIFICATE_SIGNATURE           (256U)

#define PLAINDATA                           (DCM_PROFILE_ID +\
                                             DCM_AUTHORITY_REFERENCE +\
                                             DCM_EFFECTIVE_DATE +\
                                             DCM_EXPERATION_DATE +\
                                             DCM_AUTHORIZATION_OBJECT_ID +\
                                             DCM_HOLDER_REFERENCE +\
                                             DCM_HOLDER_ROLE +\
                                             DCM_PUBKEY_OBJECT_ID +\
                                             DCM_PUBLICKEY_EXPONENT +\
                                             DCM_PUBLICKEY_MODULUS)

/* CRL field information */
#define DCM_CRL_VERSION                     (1U) 
#define DCM_CRL_SIGNATURE_ALGORITHM         (22U)
#define DCM_CRL_ISSUER                      (14U)
#define DCM_CRL_DISTRIBUTION_NAME           (16U)
#define DCM_CRL_CERT_GROUP_COUNT            (4U)
#define DCM_CRL_CERT_AUTHORITY_KEYID        (32U)
#define DCM_CRL_EFFECTIVE_DATE              (3U)
#define DCM_CRL_EXPIRATION_DATE             (3U)
#define DCM_CRL_REVOKED_CERT_START_SEQNUM   (4U)
#define DCM_CRL_CERT_STATUS_SIZE            (4U)
#define DCM_CRL_CERT_STATUS_BITS            (126U)
#define DCM_CRL_RESERVED_FIELD              (16U)
#define DCM_CRL_SIGNATURE                   (256U)

#define CRL_PLAINDATA                       (DCM_CRL_VERSION +\
                                             DCM_CRL_SIGNATURE_ALGORITHM +\
                                             DCM_CRL_ISSUER +\
                                             DCM_CRL_DISTRIBUTION_NAME +\
                                             DCM_CRL_CERT_GROUP_COUNT +\
                                             DCM_CRL_CERT_AUTHORITY_KEYID +\
                                             DCM_CRL_EFFECTIVE_DATE +\
                                             DCM_CRL_EXPIRATION_DATE +\
                                             DCM_CRL_REVOKED_CERT_START_SEQNUM +\
                                             DCM_CRL_CERT_STATUS_SIZE +\
                                             DCM_CRL_CERT_STATUS_BITS +\
                                             DCM_CRL_RESERVED_FIELD)

#define CRL_FIXED_PLAINDATA                 (DCM_CRL_VERSION +\
                                             DCM_CRL_SIGNATURE_ALGORITHM +\
                                             DCM_CRL_ISSUER +\
                                             DCM_CRL_DISTRIBUTION_NAME +\
                                             DCM_CRL_CERT_GROUP_COUNT +\
                                             DCM_CRL_CERT_AUTHORITY_KEYID +\
                                             DCM_CRL_EFFECTIVE_DATE +\
                                             DCM_CRL_EXPIRATION_DATE +\
                                             DCM_CRL_REVOKED_CERT_START_SEQNUM +\
                                             DCM_CRL_CERT_STATUS_SIZE +\
                                             DCM_CRL_RESERVED_FIELD)


#define DCM_CRL_CERT_STATUSBITS_MAX_SIZE     (1251U)

#define DCM_SECURE_PENDING                  (10U)

/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> Not a defect */
#define DCM_UNUSED_PTR(x)   do{if((x) != NULL_PTR) {}} while(0)
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> Not a defect */
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* polyspace:begin<MISRA-C:8.8:Not a defect:Justify with annotations> Prototype of this function is made in other header file(Rte_*.h) which can not be included here because of Autosar Requiremtns */
#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_CSAC_CONFIGURED == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetSeedForSA(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pSecurityAccessRecord,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pSeed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrCode);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspCompareKeyForSA(
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) LpReqResData, 
  VAR(uint8, AUTOMATIC) LucOpStatus);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspVerifySignatureSeedCbk(
  Std_ReturnType retVal);
#endif

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetCertificationInfo(
  P2VAR(Dcm_CertInfoType, AUTOMATIC, DCM_APPL_DATA) CertInfo);

/* polyspace +2 MISRA-C3:20.1 [Justified:Low] "Not a defect" */
#define DCM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end<MISRA-C:8.8:Not a defect:Justify with annotations> Prototype of this function is made in other header file(Rte_*.h) which can not be included here because of Autosar Requiremtns */
#endif

/* polyspace-end MISRA-C3:2.5 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
