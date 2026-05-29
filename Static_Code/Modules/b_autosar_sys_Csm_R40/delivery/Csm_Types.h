/*******************************************************************************
**                                                                            **
**  (C) 2013~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Types.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Provides the types, particularly the configuration types, for **
**              the CSM module                                                **
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
** 2.6.1.0   08-Oct-2020   JaeHyun      Redmine #25964                        **
** 1.2.7     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.2.6     23-Mar-2020   JaeHyun      Redmine #22545                        **
** 1.2.5     20-Mar-2020   JaeHyun      Redmine #22407                        **
** 1.2.4     04-Jul-2019   Sinil        Redmine #17741                        **
** 1.2.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.2.2     17-Apr-2018   Sinil        Redmine #12351                        **
** 1.2.1     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.2.0     27-Feb-2017   Sinil        Redmine #7650, #7672                  **
** 1.0.9     09-Aug-2016   Sinil        Redmine #5693, #5540                  **
** 1.0.8     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.7     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.6     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.5     02-May-2016   Sinil        Redmine #4607                         **
** 1.0.0     01-Jan-2013   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:D4.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:2.5 [Not a defect:Low] "Macro can be used according to configuration" */

#ifndef CSM_TYPES_H
#define CSM_TYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"            /* For AUTOSAR Standard types */
#include "Rte_Csm_Type.h"         /* Header file for Rte Types */
#include "Csm_Cfg.h"              /* Header file for configuration parameters */
#include "Csm_Config.h"

/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/
/* Autron */
#ifndef CSM_RANDOM_AUTRANDOMGENERATE
#define CSM_RANDOM_AUTRANDOMGENERATE                    (STD_OFF)
#endif

#ifndef CSM_RANDOM_AUTRANDOMSEED
#define CSM_RANDOM_AUTRANDOMSEED                        (STD_OFF)
#endif

#ifndef CSM_HASH_AUTSEEDKEY
#define CSM_HASH_AUTSEEDKEY                             (STD_OFF)
#endif

#ifndef CSM_HASH_HAEADVSEEDKEY
#define CSM_HASH_HAEADVSEEDKEY                          (STD_OFF)
#endif

/* CycurLib */
#ifndef CSM_SYM_ESCAESCBCDECRYPT
#define CSM_SYM_ESCAESCBCDECRYPT                        (STD_OFF)
#endif

#ifndef CSM_SYM_ESCAESCBCENCRYPT
#define CSM_SYM_ESCAESCBCENCRYPT                        (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_ESCAESECBDECRYPT
#define CSM_SYMBLOCK_ESCAESECBDECRYPT                   (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_ESCAESECBENCRYPT
#define CSM_SYMBLOCK_ESCAESECBENCRYPT                   (STD_OFF)
#endif

#ifndef CSM_MAC_ESCCMACAESGENERATE
#define CSM_MAC_ESCCMACAESGENERATE                      (STD_OFF)
#endif

#ifndef CSM_MAC_ESCCMACAESVERIFY
#define CSM_MAC_ESCCMACAESVERIFY                        (STD_OFF)
#endif

#ifndef CSM_MAC_ESCHMACSHA1GENERATE
#define CSM_MAC_ESCHMACSHA1GENERATE                     (STD_OFF)
#endif

#ifndef CSM_MAC_ESCHMACSHA1VERIFY
#define CSM_MAC_ESCHMACSHA1VERIFY                       (STD_OFF)
#endif

#ifndef CSM_MAC_ESCHMACSHA256GENERATE
#define CSM_MAC_ESCHMACSHA256GENERATE                   (STD_OFF)
#endif

#ifndef CSM_MAC_ESCHMACSHA256VERIFY
#define CSM_MAC_ESCHMACSHA256VERIFY                     (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_ESCPKCS1V15SHA1GENERATE
#define CSM_SIGNATURE_ESCPKCS1V15SHA1GENERATE           (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_ESCPKCS1V15SHA1SEEDVERIFY
#define CSM_SIGNATURE_ESCPKCS1V15SHA1SEEDVERIFY         (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_ESCPKCS1V15SHA1VERIFY
#define CSM_SIGNATURE_ESCPKCS1V15SHA1VERIFY             (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_ESCPKCS1V15SHA256GENERATE
#define CSM_SIGNATURE_ESCPKCS1V15SHA256GENERATE         (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_ESCPKCS1V15SHA256SEEDVERIFY
#define CSM_SIGNATURE_ESCPKCS1V15SHA256SEEDVERIFY       (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_ESCPKCS1V15SHA256VERIFY
#define CSM_SIGNATURE_ESCPKCS1V15SHA256VERIFY           (STD_OFF)
#endif

#ifndef CSM_ASYM_ESCRSADECRYPT
#define CSM_ASYM_ESCRSADECRYPT                          (STD_OFF)
#endif

#ifndef CSM_ASYM_ESCRSAENCRYPT
#define CSM_ASYM_ESCRSAENCRYPT                          (STD_OFF)
#endif

#ifndef CSM_HASH_ESCSHA1
#define CSM_HASH_ESCSHA1                                (STD_OFF)
#endif

#ifndef CSM_HASH_ESCSHA256
#define CSM_HASH_ESCSHA256                              (STD_OFF)
#endif

/* HAE */
#ifndef CSM_RANDOM_HAEADVRANDOMGENERATE
#define CSM_RANDOM_HAEADVRANDOMGENERATE                 (STD_OFF)
#endif

#ifndef CSM_RANDOM_HAEADVRANDOMSEED
#define CSM_RANDOM_HAEADVRANDOMSEED                     (STD_OFF)
#endif

#ifndef CSM_HASH_HAEADVSEEDKEY
#define CSM_HASH_HAEADVSEEDKEY                          (STD_OFF)
#endif

#ifndef CSM_SYM_HAEAESCBCDECRYPT
#define CSM_SYM_HAEAESCBCDECRYPT                        (STD_OFF)
#endif

#ifndef CSM_SYM_HAEAESCBCENCRYPT
#define CSM_SYM_HAEAESCBCENCRYPT                        (STD_OFF)
#endif

#ifndef CSM_SYM_HAEAESCTRDECRYPT
#define CSM_SYM_HAEAESCTRDECRYPT                        (STD_OFF)
#endif

#ifndef CSM_SYM_HAEAESCTRENCRYPT
#define CSM_SYM_HAEAESCTRENCRYPT                        (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_HAEAESECBDECRYPT
#define CSM_SYMBLOCK_HAEAESECBDECRYPT                   (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_HAEAESECBENCRYPT
#define CSM_SYMBLOCK_HAEAESECBENCRYPT                   (STD_OFF)
#endif

#ifndef CSM_MAC_HAECMACAESGENERATE
#define CSM_MAC_HAECMACAESGENERATE                      (STD_OFF)
#endif

#ifndef CSM_MAC_HAECMACAESVERIFY
#define CSM_MAC_HAECMACAESVERIFY                        (STD_OFF)
#endif

#ifndef CSM_RANDOM_HAEHACRANDOMGENERATE
#define CSM_RANDOM_HAEHACRANDOMGENERATE                 (STD_OFF)
#endif

#ifndef CSM_RANDOM_HAEHACRANDOMSEED
#define CSM_RANDOM_HAEHACRANDOMSEED                     (STD_OFF)
#endif

#ifndef CSM_MAC_HAEHMACSHA1GENERATE
#define CSM_MAC_HAEHMACSHA1GENERATE                     (STD_OFF)
#endif

#ifndef CSM_MAC_HAEHMACSHA1VERIFY
#define CSM_MAC_HAEHMACSHA1VERIFY                       (STD_OFF)
#endif

#ifndef CSM_MAC_HAEHMACSHA256GENERATE
#define CSM_MAC_HAEHMACSHA256GENERATE                   (STD_OFF)
#endif

#ifndef CSM_MAC_HAEHMACSHA256VERIFY
#define CSM_MAC_HAEHMACSHA256VERIFY                     (STD_OFF)
#endif

#ifndef CSM_MAC_HAEHSMCMACAESGENERATE
#define CSM_MAC_HAEHSMCMACAESGENERATE                   (STD_OFF)
#endif

#ifndef CSM_MAC_HAEHSMCMACAESVERIFY
#define CSM_MAC_HAEHSMCMACAESVERIFY                     (STD_OFF)
#endif

#ifndef CSM_MAC_HAEHSMHMACSHA256GENERATE
#define CSM_MAC_HAEHSMHMACSHA256GENERATE                (STD_OFF)
#endif

#ifndef CSM_MAC_HAEHSMHMACSHA256VERIFY
#define CSM_MAC_HAEHSMHMACSHA256VERIFY                  (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEHSMPKCS1V15SHA1SEEDVERIFY
#define CSM_SIGNATURE_HAEHSMPKCS1V15SHA1SEEDVERIFY      (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEHSMPKCS1V15SHA1VERIFY
#define CSM_SIGNATURE_HAEHSMPKCS1V15SHA1VERIFY          (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEHSMPKCS1V15SHA256GENERATE
#define CSM_SIGNATURE_HAEHSMPKCS1V15SHA256GENERATE      (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEHSMPKCS1V15SHA256SEEDVERIFY
#define CSM_SIGNATURE_HAEHSMPKCS1V15SHA256SEEDVERIFY    (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEHSMPKCS1V15SHA256VERIFY
#define CSM_SIGNATURE_HAEHSMPKCS1V15SHA256VERIFY        (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEHSMPKCS1PSSSHA256GENERATE
#define CSM_SIGNATURE_HAEHSMPKCS1PSSSHA256GENERATE      (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEHSMPKCS1PSSSHA256VERIFY
#define CSM_SIGNATURE_HAEHSMPKCS1PSSSHA256VERIFY        (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEHSMECDSASHA256GENERATE
#define CSM_SIGNATURE_HAEHSMECDSASHA256GENERATE         (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEHSMECDSASHA256VERIFY
#define CSM_SIGNATURE_HAEHSMECDSASHA256VERIFY           (STD_OFF)
#endif

#ifndef CSM_KEYEXCHANGECALC_SECRET_HAEHSMECDH
#define CSM_KEYEXCHANGECALC_SECRET_HAEHSMECDH           (STD_OFF)
#endif

#ifndef CSM_KEYDERIVE_HAEHSMPBKDF2
#define CSM_KEYDERIVE_HAEHSMPBKDF2                      (STD_OFF)
#endif

#ifndef CSM_HASH_HAEHSMSHA1
#define CSM_HASH_HAEHSMSHA1                             (STD_OFF)
#endif

#ifndef CSM_HASH_HAEHSMSHA256
#define CSM_HASH_HAEHSMSHA256                           (STD_OFF)
#endif

#ifndef CSM_RANDOM_HAEHSMTRUERANDOMGENERATE
#define CSM_RANDOM_HAEHSMTRUERANDOMGENERATE             (STD_OFF)
#endif

#ifndef CSM_RANDOM_HAEHSMPSEUDORANDOMGENERATE
#define CSM_RANDOM_HAEHSMPSEUDORANDOMGENERATE           (STD_OFF)
#endif

#ifndef CSM_SYM_HAEHSMAESCBCENCRYPT
#define CSM_SYM_HAEHSMAESCBCENCRYPT                     (STD_OFF)
#endif

#ifndef CSM_SYM_HAEHSMAESCBCDECRYPT
#define CSM_SYM_HAEHSMAESCBCDECRYPT                     (STD_OFF)
#endif

#ifndef CSM_SYM_HAEHSMAESCTRENCRYPT
#define CSM_SYM_HAEHSMAESCTRENCRYPT                     (STD_OFF)
#endif

#ifndef CSM_SYM_HAEHSMAESCTRDECRYPT
#define CSM_SYM_HAEHSMAESCTRDECRYPT                     (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_HAEHSMAESECBDECRYPT
#define CSM_SYMBLOCK_HAEHSMAESECBDECRYPT                (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_HAEHSMAESECBENCRYPT
#define CSM_SYMBLOCK_HAEHSMAESECBENCRYPT                (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEPKCS1V15SHA1GENERATE
#define CSM_SIGNATURE_HAEPKCS1V15SHA1GENERATE           (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEPKCS1V15SHA1SEEDVERIFY
#define CSM_SIGNATURE_HAEPKCS1V15SHA1SEEDVERIFY         (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEPKCS1V15SHA1VERIFY
#define CSM_SIGNATURE_HAEPKCS1V15SHA1VERIFY             (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEPKCS1V15SHA256GENERATE
#define CSM_SIGNATURE_HAEPKCS1V15SHA256GENERATE         (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEPKCS1V15SHA256SEEDVERIFY
#define CSM_SIGNATURE_HAEPKCS1V15SHA256SEEDVERIFY       (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY
#define CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY           (STD_OFF)
#endif

#ifndef CSM_RANDOM_HAEPSEUDORANDOMGENERATE
#define CSM_RANDOM_HAEPSEUDORANDOMGENERATE              (STD_OFF)
#endif

#ifndef CSM_RANDOM_HAEPSEUDORANDOMSEED
#define CSM_RANDOM_HAEPSEUDORANDOMSEED                  (STD_OFF)
#endif

#ifndef CSM_ASYM_HAERSADECRYPT
#define CSM_ASYM_HAERSADECRYPT                          (STD_OFF)
#endif

#ifndef CSM_ASYM_HAERSAENCRYPT
#define CSM_ASYM_HAERSAENCRYPT                          (STD_OFF)
#endif

#ifndef CSM_HASH_HAESHA1
#define CSM_HASH_HAESHA1                                (STD_OFF)
#endif

#ifndef CSM_HASH_HAESHA256
#define CSM_HASH_HAESHA256                              (STD_OFF)
#endif

/* HSM */
#ifndef CSM_SYM_AUTHSMAESCBCDECRYPT
#define CSM_SYM_AUTHSMAESCBCDECRYPT                     (STD_OFF)
#endif

#ifndef CSM_SYM_AUTHSMAESCBCENCRYPT
#define CSM_SYM_AUTHSMAESCBCENCRYPT                     (STD_OFF)
#endif

#ifndef CSM_SYM_AUTHSMAESCTRDECRYPT
#define CSM_SYM_AUTHSMAESCTRDECRYPT                     (STD_OFF)
#endif

#ifndef CSM_SYM_AUTHSMAESCTRENCRYPT
#define CSM_SYM_AUTHSMAESCTRENCRYPT                     (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_AUTHSMAESECBDECRYPT
#define CSM_SYMBLOCK_AUTHSMAESECBDECRYPT                (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_AUTHSMAESECBENCRYPT
#define CSM_SYMBLOCK_AUTHSMAESECBENCRYPT                (STD_OFF)
#endif

#ifndef CSM_MAC_AUTHSMCMACAESGENERATE
#define CSM_MAC_AUTHSMCMACAESGENERATE                   (STD_OFF)
#endif

#ifndef CSM_MAC_AUTHSMCMACAESVERIFY
#define CSM_MAC_AUTHSMCMACAESVERIFY                     (STD_OFF)
#endif

#ifndef CSM_KEYEXCHANGECALC_SECRET_AUTHSMECDH
#define CSM_KEYEXCHANGECALC_SECRET_AUTHSMECDH           (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_AUTHSMECDSASHA256GENERATE
#define CSM_SIGNATURE_AUTHSMECDSASHA256GENERATE         (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_AUTHSMECDSASHA256VERIFY
#define CSM_SIGNATURE_AUTHSMECDSASHA256VERIFY           (STD_OFF)
#endif

#ifndef CSM_ASYM_AUTHSMECIESDECRYPT
#define CSM_ASYM_AUTHSMECIESDECRYPT                     (STD_OFF)
#endif

#ifndef CSM_ASYM_AUTHSMECIESENCRYPT
#define CSM_ASYM_AUTHSMECIESENCRYPT                     (STD_OFF)
#endif

#ifndef CSM_MAC_AUTHSMHMACSHA1GENERATE
#define CSM_MAC_AUTHSMHMACSHA1GENERATE                  (STD_OFF)
#endif

#ifndef CSM_MAC_AUTHSMHMACSHA1VERIFY
#define CSM_MAC_AUTHSMHMACSHA1VERIFY                    (STD_OFF)
#endif

#ifndef CSM_MAC_AUTHSMHMACSHA256GENERATE
#define CSM_MAC_AUTHSMHMACSHA256GENERATE                (STD_OFF)
#endif

#ifndef CSM_MAC_AUTHSMHMACSHA256VERIFY
#define CSM_MAC_AUTHSMHMACSHA256VERIFY                  (STD_OFF)
#endif

#ifndef CSM_KEYDERIVE_AUTHSMPBKDF2
#define CSM_KEYDERIVE_AUTHSMPBKDF2                      (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_AUTHSMPKCS1PSSSHA256GENERATE
#define CSM_SIGNATURE_AUTHSMPKCS1PSSSHA256GENERATE      (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_AUTHSMPKCS1PSSSHA256VERIFY
#define CSM_SIGNATURE_AUTHSMPKCS1PSSSHA256VERIFY        (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_AUTHSMPKCS1V15SHA1GENERATE
#define CSM_SIGNATURE_AUTHSMPKCS1V15SHA1GENERATE        (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_AUTHSMPKCS1V15SHA1SEEDVERIFY
#define CSM_SIGNATURE_AUTHSMPKCS1V15SHA1SEEDVERIFY      (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_AUTHSMPKCS1V15SHA1VERIFY
#define CSM_SIGNATURE_AUTHSMPKCS1V15SHA1VERIFY          (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_AUTHSMPKCS1V15SHA256GENERATE
#define CSM_SIGNATURE_AUTHSMPKCS1V15SHA256GENERATE      (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_AUTHSMPKCS1V15SHA256SEEDVERIFY
#define CSM_SIGNATURE_AUTHSMPKCS1V15SHA256SEEDVERIFY    (STD_OFF)
#endif

#ifndef CSM_SIGNATURE_AUTHSMPKCS1V15SHA256VERIFY
#define CSM_SIGNATURE_AUTHSMPKCS1V15SHA256VERIFY        (STD_OFF)
#endif

#ifndef CSM_RANDOM_AUTHSMPSEUDORANDOMGENERATE
#define CSM_RANDOM_AUTHSMPSEUDORANDOMGENERATE           (STD_OFF)
#endif

#ifndef CSM_ASYM_AUTHSMRSADECRYPT
#define CSM_ASYM_AUTHSMRSADECRYPT                       (STD_OFF)
#endif

#ifndef CSM_ASYM_AUTHSMRSAENCRYPT
#define CSM_ASYM_AUTHSMRSAENCRYPT                       (STD_OFF)
#endif

#ifndef CSM_HASH_AUTHSMSHA1
#define CSM_HASH_AUTHSMSHA1                             (STD_OFF)
#endif

#ifndef CSM_HASH_AUTHSMSHA256
#define CSM_HASH_AUTHSMSHA256                           (STD_OFF)
#endif

#ifndef CSM_RANDOM_AUTHSMTRUERANDOMGENERATE
#define CSM_RANDOM_AUTHSMTRUERANDOMGENERATE             (STD_OFF)
#endif

/* ICUS */
#ifndef CSM_SYM_AUTICUSAESCBCDECRYPT
#define CSM_SYM_AUTICUSAESCBCDECRYPT                    (STD_OFF)
#endif

#ifndef CSM_SYM_AUTICUSAESCBCENCRYPT
#define CSM_SYM_AUTICUSAESCBCENCRYPT                    (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_AUTICUSAESECBDECRYPT
#define CSM_SYMBLOCK_AUTICUSAESECBDECRYPT               (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_AUTICUSAESECBENCRYPT
#define CSM_SYMBLOCK_AUTICUSAESECBENCRYPT               (STD_OFF)
#endif

#ifndef CSM_MAC_AUTICUSCMACAESGENERATE
#define CSM_MAC_AUTICUSCMACAESGENERATE                  (STD_OFF)
#endif

#ifndef CSM_MAC_AUTICUSCMACAESVERIFY
#define CSM_MAC_AUTICUSCMACAESVERIFY                    (STD_OFF)
#endif

#ifndef CSM_RANDOM_AUTICUSRANDOMGENERATE
#define CSM_RANDOM_AUTICUSRANDOMGENERATE                (STD_OFF)
#endif

#ifndef CSM_RANDOM_AUTICUSRANDOMSEED
#define CSM_RANDOM_AUTICUSRANDOMSEED                    (STD_OFF)
#endif

/* CSEC */
#ifndef CSM_MAC_AUTCSECCMACAESGENERATE
#define CSM_MAC_AUTCSECCMACAESGENERATE                  (STD_OFF)
#endif

#ifndef CSM_MAC_AUTCSECCMACAESVERIFY
#define CSM_MAC_AUTCSECCMACAESVERIFY                    (STD_OFF)
#endif

#ifndef CSM_RANDOM_AUTCSECRANDOMSEED
#define CSM_RANDOM_AUTCSECRANDOMSEED                    (STD_OFF)
#endif

#ifndef CSM_RANDOM_AUTCSECRANDOMGENERATE
#define CSM_RANDOM_AUTCSECRANDOMGENERATE                (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_AUTCSECAESECBENCRYPT
#define CSM_SYMBLOCK_AUTCSECAESECBENCRYPT               (STD_OFF)
#endif

#ifndef CSM_SYMBLOCK_AUTCSECAESECBDECRYPT
#define CSM_SYMBLOCK_AUTCSECAESECBDECRYPT               (STD_OFF)
#endif

#ifndef CSM_SYM_AUTCSECAESCBCENCRYPT
#define CSM_SYM_AUTCSECAESCBCENCRYPT                    (STD_OFF)
#endif

#ifndef CSM_SYM_AUTCSECAESCBCDECRYPT
#define CSM_SYM_AUTCSECAESCBCDECRYPT                    (STD_OFF)
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Csm instance Id */
#define CSM_INSTANCE_ID                          (0)

/* Macro for const value */
#define CSM_ZERO                                 (0x00U)
#define CSM_ONE                                  (0x01U)
#define CSM_TWO                                  (0x02U)
#define CSM_THREE                                (0x03U)
#define CSM_FOUR                                 (0x04U)
#define CSM_FIVE                                 (0x05U)
#define CSM_SIX                                  (0x06U)
#define CSM_SEVEN                                (0x07U)
#define CSM_EIGHT                                (0x08U)
#define CSM_BYTE_MASK                            (0xFFU)

#define CSM_TRUE                                 ((boolean) 0x01)
#define CSM_FALSE                                ((boolean) 0x00)

/* Generic Macros used in CRY interfaces */
/* In Cry_<>Start */
#define JOB_START                                (0x01)
/* In Cry_<>Update */
#define JOB_UPDATE                               (0x02)
/* In Cry_<>Finish */
#define JOB_FINISH                               (0x03)
/* Jobs are successfully executed */
#define JOB_DONE                                 (0x04)
/* No jobs, ready to take new jobs */
#define NO_JOB                                   (0x00)

/* the service request failed because the service is still busy */
#define CSM_E_BUSY                               (0x02U)
/* the service request failed because the provided
  buffer is too small to store the result of the service */
#define CSM_E_SMALL_BUFFER                       (0x03U)
/* the service request failed because the entropy of the
  random number generator is exhausted */
#define CSM_E_ENTROPY_EXHAUSTION                 (0x04U)

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* This DET error is reported if the parameter of API is an invalid pointer */
#define CSM_E_PARAM_PTR_INVALID                  ((uint8)0x01)

/* This DET error is reported if the Requested service is not yet initialized */
#define CSM_E_SERVICE_NOT_STARTED                ((uint8)0x02)

/* This DET error is reported if the API request is called with invalid
  method for selected service */
#define CSM_E_PARAM_METHOD_INVALID               ((uint8)0x03)

/* This DET error is reported if the API request is called with invalid key
  type for selected service */
#define CSM_E_PARAM_KEY_TYPE_INVALID             ((uint8)0x04)

/* This Det error is returned if API service is used before CSM is intialized */
#define CSM_E_UNINIT                             ((uint8)0x05)

/* This Det error is returned if Provided buffer for storing the result of a
  computation is too small */
#define CSM_E_BUFFER_TOO_SMALL                   ((uint8)0x06)

/* This Det error is reported if parameter provided as arguement is 0 */
#define CSM_E_PARAM_INVALID                      ((uint8)0x07)

/*******************************************************************************
**                      Service IDs                                           **
*******************************************************************************/
#if (CSM_DEV_ERROR_DETECT == STD_ON)
/* General Service Ids */
#define CSM_INIT_SID                             (0x00U)
#define CSM_MAINFUNCTION_SID                     (0x01U)
#define CSM_INTERRUPTION_SID                     (0x02U)
#define CSM_GETVERSIONINFO_SID                   (0x3BU)

/* Service Ids for Hash Interface */
#define CSM_HASHSTART_SID                        (0x03U)
#define CSM_HASHUPDATE_SID                       (0x04U)
#define CSM_HASHFINISH_SID                       (0x05U)

/* Service Ids for MAC Interface */
#define CSM_MACGENERATESTART_SID                 (0x06U)
#define CSM_MACGENERATEUPDATE_SID                (0x07U)
#define CSM_MACGENERATEFINISH_SID                (0x08U)
#define CSM_MACVERIFYSTART_SID                   (0x09U)
#define CSM_MACVERIFYUPDATE_SID                  (0x0AU)
#define CSM_MACVERIFYFINISH_SID                  (0x0BU)

/* Service Ids for Random Interface */
#define CSM_RANDOMSEEDSTART_SID                  (0x0CU)
#define CSM_RANDOMSEEDUPDATE_SID                 (0x0DU)
#define CSM_RANDOMSEEDFINISH_SID                 (0x0EU)
#define CSM_RANDOMGENERATE_SID                   (0x0FU)

/* Service Ids for Symmetrical block Interface */
#define CSM_SYMBLOCKENCRYPTSTART_SID             (0x10U)
#define CSM_SYMBLOCKENCRYPTUPDATE_SID            (0x11U)
#define CSM_SYMBLOCKENCRYPTFINISH_SID            (0x12U)
#define CSM_SYMBLOCKDECRYPTSTART_SID             (0x13U)
#define CSM_SYMBLOCKDECRYPTUPDATE_SID            (0x14U)
#define CSM_SYMBLOCKDECRYPTFINISH_SID            (0x15U)

/* Service Ids for Symmetrical Interface */
#define CSM_SYMENCRYPTSTART_SID                  (0x16U)
#define CSM_SYMENCRYPTUPDATE_SID                 (0x17U)
#define CSM_SYMENCRYPTFINISH_SID                 (0x18U)
#define CSM_SYMDECRYPTSTART_SID                  (0x19U)
#define CSM_SYMDECRYPTUPDATE_SID                 (0x1AU)
#define CSM_SYMDECRYPTFINISH_SID                 (0x1BU)

/* Service Ids for Asymmetrical Interface */
#define CSM_ASYMENCRYPTSTART_SID                 (0x1CU)
#define CSM_ASYMENCRYPTUPDATE_SID                (0x1DU)
#define CSM_ASYMENCRYPTFINISH_SID                (0x1EU)
#define CSM_ASYMDECRYPTSTART_SID                 (0x1FU)
#define CSM_ASYMDECRYPTUPDATE_SID                (0x20U)
#define CSM_ASYMDECRYPTFINISH_SID                (0x21U)

/* Service Ids for Signature Interface */
#define CSM_SIGNATUREGENERATESTART_SID           (0x22U)
#define CSM_SIGNATUREGENERATEUPDATE_SID          (0x23U)
#define CSM_SIGNATUREGENERATEFINISH_SID          (0x24U)
#define CSM_SIGNATUREVERIFYSTART_SID             (0x25U)
#define CSM_SIGNATUREVERIFYUPDATE_SID            (0x26U)
#define CSM_SIGNATUREVERIFYFINISH_SID            (0x27U)

/* Service Ids for Checksum Interface */
#define CSM_CHECKSUMSTART_SID                    (0x28U)
#define CSM_CHECKSUMUPDATE_SID                   (0x29U)
#define CSM_CHECKSUMFINISH_SID                   (0x2AU)

/* Service Ids for Key derivation Interface */
#define CSM_KEYDERIVESTART_SID                   (0x2BU)
#define CSM_KEYDERIVEUPDATE_SID                  (0x2CU)
#define CSM_KEYDERIVEFINISH_SID                  (0x2DU)

/* Service Ids for Key exchange Interface */
#define CSM_KEYEXCHANGECALCPUBVAL_SID            (0x2EU)

/* Service Id */
#define CSM_KEYEXCHANGECALCSECRETSTART_SID       (0x2FU)
#define CSM_KEYEXCHANGECALCSECRETUPDATE_SID      (0x30U)
#define CSM_KEYEXCHANGECALCSECRETFINISH_SID      (0x31U)

/* Service Ids for Symmetrical key extract Interface */
#define CSM_SYMKEYEXTRACTSTART_SID               (0x32U)
#define CSM_SYMKEYEXTRACTUPDATE_SID              (0x33U)
#define CSM_SYMKEYEXTRACTFINISH_SID              (0x34U)

/* Service Ids for Asymmetrical key extract Interface */
#define CSM_ASYMPUBLICKEYEXTRACTSTART_SID        (0x35U)
#define CSM_ASYMPUBLICKEYEXTRACTUPDATE_SID       (0x36U)
#define CSM_ASYMPUBLICKEYEXTRACTFINISH_SID       (0x37U)

/* Service Id */
#define CSM_ASYMPRIVATEKEYEXTRACTSTART_SID       (0x38U)
#define CSM_ASYMPRIVATEKEYEXTRACTUPDATE_SID      (0x39U)
#define CSM_ASYMPRIVATEKEYEXTRACTFINISH_SID      (0x3AU)

/* Service Id */
#define CSM_KEYEXCHANGECALCSYMKEYSTART_SID       (0x3DU)
#define CSM_KEYEXCHANGECALCSYMKEYUPDATE_SID      (0x3EU)
#define CSM_KEYEXCHANGECALCSYMKEYFINISH_SID      (0x3FU)

/* Service Ids */
#define CSM_SYMKEYWRAPSYMSTART_SID               (0x40U)
#define CSM_SYMKEYWRAPSYMUPDATE_SID              (0x41U)
#define CSM_SYMKEYWRAPSYMFINISH_SID              (0x42U)

/* Service Ids */
#define CSM_SYMKEYWRAPASYMSTART_SID              (0x43U)
#define CSM_SYMKEYWRAPASYMUPDATE_SID             (0x44U)
#define CSM_SYMKEYWRAPASYMFINISH_SID             (0x45U)

/* Service Ids */
#define CSM_ASYMPRIVATEKEYWRAPSYMSTART_SID       (0x46U)
#define CSM_ASYMPRIVATEKEYWRAPSYMUPDATE_SID      (0x47U)
#define CSM_ASYMPRIVATEKEYWRAPSYMFINISH_SID      (0x48U)

/* Service Ids */
#define CSM_ASYMPRIVATEKEYWRAPASYMSTART_SID      (0x49U)
#define CSM_ASYMPRIVATEKEYWRAPASYMUPDATE_SID     (0x4AU)
#define CSM_ASYMPRIVATEKEYWRAPASYMFINISH_SID     (0x4BU)

/* Service Id */
#define CSM_KEYDERIVESYMKEY_SID                  (0x4CU)
#endif

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.9 [Not a defect:Low] "macro is used for improving performance" */
#define CSM_PARAM_UNUSED(x)                      do { \
                                                   if((uint32)(x) != (uint32)CSM_ZERO) {} \
                                                 } while(0)

#define CSM_PARAM_UNUSED_PTR(x)                  do { \
                                                   if((x) != NULL_PTR) {} \
                                                 } while(0)
/* polyspace-end MISRA-C3:D4.9 */
/*******************************************************************************
**                      Common Global Data Types                              **
*******************************************************************************/
/* Function pointer for callback function invocation upon service completion */
typedef Std_ReturnType (*Csm_CallbackType)(Std_ReturnType retVal);

/*******************************************************************************
**                      Hash Interface                                        **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.6 [Justified:Low] "The global variable shall be generated by configuration tool " */
#if (CSM_HASH_STATUS == STD_ON)
/* Macros for Hash Interface */
/* Hash Interface States */
#define CSM_HASH_IDLE                            (0x01U)
#define CSM_HASH_START                           (0x02U)
#define CSM_HASH_ACTIVE                          (0x04U)
#define CSM_HASH_UPDATE                          (0x08U)
#define CSM_HASH_FINISH                          (0x10U)

/* Structure contains all the information needed for Hash interface */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* dataPtr, uint32 dataLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_HashConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_HashConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveHashService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_HashConfigType Csm_GaaHashConfigType[CSM_HASH_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveHashService Csm_GddActiveHashService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_HASH_STATUS == STD_ON) */

/*******************************************************************************
**                      MAC Interface                                         **
*******************************************************************************/
#if (CSM_MAC_GENERATE_STATUS == STD_ON)
/* MAC Interface States */
#define CSM_MAC_GENERATE_IDLE                    (0x01U)
#define CSM_MAC_GENERATE_START                   (0x02U)
#define CSM_MAC_GENERATE_ACTIVE                  (0x04U)
#define CSM_MAC_GENERATE_UPDATE                  (0x08U)
#define CSM_MAC_GENERATE_FINISH                  (0x10U)

/* Structure contains all the information needed for Mac Generate interface */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_SymKeyType* keyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* dataPtr, uint32 dataLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_MacGenerateConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_MacGenerateConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveMacGenerateService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_MacGenerateConfigType
  Csm_GaaMacGenerateConfigType[CSM_MAC_GENERATE_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveMacGenerateService Csm_GddActiveMacGenerateService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

#if (CSM_MAC_VERIFY_STATUS == STD_ON)
/* MAC Interface States */
#define CSM_MAC_VERIFY_IDLE                      (0x01U)
#define CSM_MAC_VERIFY_START                     (0x02U)
#define CSM_MAC_VERIFY_ACTIVE                    (0x04U)
#define CSM_MAC_VERIFY_UPDATE                    (0x08U)
#define CSM_MAC_VERIFY_FINISH                    (0x10U)

/* Structure contains all the information needed for Mac Verify interface */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_SymKeyType* keyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* dataPtr, uint32 dataLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    const uint8* MacPtr, uint32 MacLength, Csm_VerifyResultType* resultPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_MacVerifyConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_MacVerifyConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveMacVerifyService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_MacVerifyConfigType
  Csm_GaaMacVerifyConfigType[CSM_MAC_VERIFY_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveMacVerifyService Csm_GddActiveMacVerifyService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**                      Random Interface                                      **
*******************************************************************************/
#if (CSM_RANDOM_SEED_STATUS == STD_ON)
/* Random interface States */
#define CSM_RANDOM_SEED_IDLE                     (0x01U)
#define CSM_RANDOM_SEED_START                    (0x02U)
#define CSM_RANDOM_SEED_ACTIVE                   (0x04U)
#define CSM_RANDOM_SEED_UPDATE                   (0x08U)
#define CSM_RANDOM_SEED_FINISH                   (0x10U)

/* Structure contains all the information needed for Random Seed interface */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* seedPtr, uint32 seedLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_RandomSeedConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_RandomSeedConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveRandomSeedService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_RandomSeedConfigType
  Csm_GaaRandomSeedConfigType[CSM_RANDOM_SEED_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveRandomSeedService Csm_GddActiveRandomSeedService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON) */

#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
/* Random interface States */
#define CSM_RANDOM_GENERATE_IDLE                 (0x01U)
#define CSM_RANDOM_GENERATE_ACTIVE               (0x02U)

/* Structure contains all the information needed for Random Generate interface
 **/
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Function */
  Std_ReturnType (*PrimitiveFct)(const void* cfgPtr, uint8* resultPtr,
    uint32 resultLength);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_RandomGenerateConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_RandomGenerateConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveRandomGenerateService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_RandomGenerateConfigType
  Csm_GaaRandomGenerateConfigType[CSM_RANDOM_GENERATE_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveRandomGenerateService Csm_GddActiveRandomGenerateService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_RANDOM_GENERATE_STATUS == STD_ON) */

/*******************************************************************************
**                      Symmetrical Block Interface                           **
*******************************************************************************/
#if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
/* Symmetrical Block Interface States */
#define CSM_SYM_BLOCK_ENCRYPT_IDLE               (0x01U)
#define CSM_SYM_BLOCK_ENCRYPT_START              (0x02U)
#define CSM_SYM_BLOCK_ENCRYPT_ACTIVE             (0x04U)
#define CSM_SYM_BLOCK_ENCRYPT_UPDATE             (0x08U)
#define CSM_SYM_BLOCK_ENCRYPT_FINISH             (0x10U)

/* Structure contains all the information needed for Symmetrical Block *
 * Encryption interface                                                *
 */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_SymKeyType* keyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* plainTextPtr, uint32 plainTextLength,
    uint8* cipherTextPtr, uint32* cipherTextLengthPtr);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_SymBlockEncryptConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_SymBlockEncryptConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveSymBlockEncryptService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_SymBlockEncryptConfigType
  Csm_GaaSymBlockEncryptConfigType[CSM_SYM_BLOCK_ENCRYPT_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveSymBlockEncryptService Csm_GddActiveSymBlockEncryptService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#endif /* (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
/* Symmetrical Block Interface States */
#define CSM_SYM_BLOCK_DECRYPT_IDLE               (0x01U)
#define CSM_SYM_BLOCK_DECRYPT_START              (0x02U)
#define CSM_SYM_BLOCK_DECRYPT_ACTIVE             (0x04U)
#define CSM_SYM_BLOCK_DECRYPT_UPDATE             (0x08U)
#define CSM_SYM_BLOCK_DECRYPT_FINISH             (0x10U)

/* Structure contains all the information needed for Symmetrical Block *
 * Decryption interface                                                *
 */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_SymKeyType* keyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* cipherTextPtr, uint32 cipherTextLength,
    uint8* plainTextPtr, uint32* plainTextLengthPtr);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_SymBlockDecryptConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_SymBlockDecryptConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveSymBlockDecryptService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_SymBlockDecryptConfigType
  Csm_GaaSymBlockDecryptConfigType[CSM_SYM_BLOCK_DECRYPT_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveSymBlockDecryptService Csm_GddActiveSymBlockDecryptService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**                      Symmetrical Interface                                 **
*******************************************************************************/
#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
/* Symmetrical Interface States */
#define CSM_SYM_ENCRYPT_IDLE                     (0x01U)
#define CSM_SYM_ENCRYPT_START                    (0x02U)
#define CSM_SYM_ENCRYPT_ACTIVE                   (0x04U)
#define CSM_SYM_ENCRYPT_UPDATE                   (0x08U)
#define CSM_SYM_ENCRYPT_FINISH                   (0x10U)

/* Structure contains all the information needed for Symmetrical Encryption */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
    uint32 InitVectorLength);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* plainTextPtr, uint32 plainTextLength,
    uint8* cipherTextPtr, uint32* cipherTextLengthPtr);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    uint8* cipherTextPtr, uint32* cipherTextLengthPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_SymEncryptConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_SymEncryptConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveSymEncryptService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_SymEncryptConfigType
  Csm_GaaSymEncryptConfigType[CSM_SYM_ENCRYPT_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveSymEncryptService Csm_GddActiveSymEncryptService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_DECRYPT_STATUS == STD_ON)
#define CSM_SYM_DECRYPT_IDLE                     (0x01U)
#define CSM_SYM_DECRYPT_START                    (0x02U)
#define CSM_SYM_DECRYPT_ACTIVE                   (0x04U)
#define CSM_SYM_DECRYPT_UPDATE                   (0x08U)
#define CSM_SYM_DECRYPT_FINISH                   (0x10U)

/* Structure contains all the information needed for Symmetrical Decryption */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_SymKeyType* keyPtr, const uint8* InitVectorPtr,
    uint32 InitVectorLength);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* cipherTextPtr, uint32 cipherTextLength,
    uint8* plainTextPtr, uint32* plainTextLengthPtr);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    uint8* plainTextPtr, uint32* plainTextLengthPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_SymDecryptConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_SymDecryptConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveSymDecryptService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_SymDecryptConfigType
  Csm_GaaSymDecryptConfigType[CSM_SYM_DECRYPT_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveSymDecryptService Csm_GddActiveSymDecryptService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_SYM_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**                      Asymmetrical Interface                                **
*******************************************************************************/
#if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
/* Asymmetrical Interface States */
#define CSM_ASYM_ENCRYPT_IDLE                    (0x01U)
#define CSM_ASYM_ENCRYPT_START                   (0x02U)
#define CSM_ASYM_ENCRYPT_ACTIVE                  (0x04U)
#define CSM_ASYM_ENCRYPT_UPDATE                  (0x08U)
#define CSM_ASYM_ENCRYPT_FINISH                  (0x10U)

/* Structure contains all the information needed for Asymmetrical Encryption */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_AsymPublicKeyType* keyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* plainTextPtr, uint32 plainTextLength,
    uint8* cipherTextPtr, uint32* cipherTextLengthPtr);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    uint8* cipherTextPtr, uint32* cipherTextLengthPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_AsymEncryptConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_AsymEncryptConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveAsymEncryptService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_AsymEncryptConfigType
  Csm_GaaAsymEncryptConfigType[CSM_ASYM_ENCRYPT_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveAsymEncryptService Csm_GddActiveAsymEncryptService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_ASYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_ASYM_DECRYPT_STATUS == STD_ON)
/* Asymmetrical Interface States */
#define CSM_ASYM_DECRYPT_IDLE                    (0x01U)
#define CSM_ASYM_DECRYPT_START                   (0x02U)
#define CSM_ASYM_DECRYPT_ACTIVE                  (0x04U)
#define CSM_ASYM_DECRYPT_UPDATE                  (0x08U)
#define CSM_ASYM_DECRYPT_FINISH                  (0x10U)

/* Structure contains all the information needed for Asymmetrical Decryption */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_AsymPrivateKeyType* keyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* cipherTextPtr, uint32 cipherTextLength,
    uint8* plainTextPtr, uint32* plainTextLengthPtr);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    uint8* plainTextPtr, uint32* plainTextLengthPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_AsymDecryptConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_AsymDecryptConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveAsymDecryptService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_AsymDecryptConfigType
  Csm_GaaAsymDecryptConfigType[CSM_ASYM_DECRYPT_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveAsymDecryptService Csm_GddActiveAsymDecryptService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_ASYM_DECRYPT_STATUS == STD_ON) */

/*******************************************************************************
**                      Signature Interface                                   **
*******************************************************************************/
#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
/* Signature Interface States */
#define CSM_SIGNATURE_GENERATE_IDLE              (0x01U)
#define CSM_SIGNATURE_GENERATE_START             (0x02U)
#define CSM_SIGNATURE_GENERATE_ACTIVE            (0x04U)
#define CSM_SIGNATURE_GENERATE_UPDATE            (0x08U)
#define CSM_SIGNATURE_GENERATE_FINISH            (0x10U)

/* Structure contains all the information needed for Signature Generation */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_AsymPrivateKeyType* keyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* dataPtr, uint32 dataLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    uint8* resultPtr, uint32* resultLengthPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_SignatureGenerateConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_SignatureGenerateConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveSignatureGenerateService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_SignatureGenerateConfigType
  Csm_GaaSignatureGenerateConfigType[CSM_SIGNATURE_GENERATE_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveSignatureGenerateService Csm_GddActiveSignatureGenerateService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
/* Signature Interface States */
#define CSM_SIGNATURE_VERIFY_IDLE                (0x01U)
#define CSM_SIGNATURE_VERIFY_START               (0x02U)
#define CSM_SIGNATURE_VERIFY_ACTIVE              (0x04U)
#define CSM_SIGNATURE_VERIFY_UPDATE              (0x08U)
#define CSM_SIGNATURE_VERIFY_FINISH              (0x10U)

/* Structure contains all the information needed for SignatureVerification */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_AsymPublicKeyType* keyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* dataPtr, uint32 dataLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    const uint8* signaturePtr, uint32 signatureLength,
    Csm_VerifyResultType* resultPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_SignatureVerifyConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_SignatureVerifyConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveSignatureVerifyService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_SignatureVerifyConfigType
  Csm_GaaSignatureVerifyConfigType[CSM_SIGNATURE_VERIFY_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveSignatureVerifyService Csm_GddActiveSignatureVerifyService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

/*******************************************************************************
**                      Checksum Interface                                    **
*******************************************************************************/
#if (CSM_CHECKSUM_STATUS == STD_ON)
/* Macros for Checksum Interface */
/* Checksum Interface States */
#define CSM_CHECKSUM_IDLE                        (0x01U)
#define CSM_CHECKSUM_START                       (0x02U)
#define CSM_CHECKSUM_ACTIVE                      (0x04U)
#define CSM_CHECKSUM_UPDATE                      (0x08U)
#define CSM_CHECKSUM_FINISH                      (0x10U)

/* Structure contains all the information needed for Checksum */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* dataPtr, uint32 dataLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_ChecksumConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_ChecksumConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveChecksumService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_ChecksumConfigType
  Csm_GaaChecksumConfigType[CSM_CHECKSUM_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveChecksumService Csm_GddActiveChecksumService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_CHECKSUM_STATUS == STD_ON) */

/*******************************************************************************
**                      Key Derivation Interface                              **
*******************************************************************************/
#if (CSM_KEY_DERIVATION_STATUS == STD_ON)
/* Macros for Key derivation Interface */
/* Key Derivation Interface States */
#define CSM_KEY_DERIVE_IDLE                      (0x01U)
#define CSM_KEY_DERIVE_START                     (0x02U)
#define CSM_KEY_DERIVE_ACTIVE                    (0x04U)
#define CSM_KEY_DERIVE_UPDATE                    (0x08U)
#define CSM_KEY_DERIVE_FINISH                    (0x10U)

/* Structure contains all the information needed for Key Derivation */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr, uint32 keyLength,
    uint32 iterations);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* passwordPtr, uint32 passwordLength, const uint8* saltPtr,
    uint32 saltLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    Csm_SymKeyType* keyPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_KeyDeriveConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_KeyDeriveConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveKeyDeriveService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_KeyDeriveConfigType
  Csm_GaaKeyDeriveConfigType[CSM_KEY_DERIVE_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveKeyDeriveService Csm_GddActiveKeyDeriveService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_KEY_DERIVATION_STATUS == STD_ON) */

/*******************************************************************************
**                      KeyDeriveSymKey Interface                             **
*******************************************************************************/
#if (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON)
/* States */
#define CSM_KEY_DERIVE_SYMKEY_IDLE               (0x01U)
#define CSM_KEY_DERIVE_SYMKEY_ACTIVE             (0x02U)

/* Structure contains all the information needed for Symmetrical Key Derivation
 **/
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Function */
  Std_ReturnType (*PrimitiveFct)(const void* cfgPtr,
    const Csm_SymKeyType* baseKeyPtr, const uint8* customisationValPtr,
    uint32 customisationValLength, Csm_SymKeyType* derivedKeyPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_KeyDeriveSymKeyConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_KeyDeriveSymKeyConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveKeyDeriveSymKeyService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_KeyDeriveSymKeyConfigType
  Csm_GaaKeyDeriveSymKeyConfigType[CSM_KEY_DERIVE_SYMKEY_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveKeyDeriveSymKeyService Csm_GddActiveKeyDeriveSymKeyService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_KEY_DERIVATION_SYM_KEY_STATUS == STD_ON) */

/*******************************************************************************
**                      KeyExchangeCalcPubVal Interface                       **
*******************************************************************************/
#if (CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON)
/* Macros for Key exchange Interface */
/* Key exchange Interface States */
#define CSM_KEY_EXCHANGE_CALCPUBVAL_IDLE         (0x01U)
#define CSM_KEY_EXCHANGE_CALCPUBVAL_ACTIVE       (0x02U)

/* Structure contains all the information needed for public value calulation */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Function */
  Std_ReturnType (*PrimitiveFct)(const void* cfgPtr,
    const Csm_KeyExchangeBaseType* basePtr,
    const Csm_KeyExchangePrivateType* privateValuePtr,
    uint8* publicValuePtr, uint32* publicValueLengthPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_KeyExchangeCalcPubValConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_KeyExchangeCalcPubValConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveKeyExchangeCalcPubValService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_KeyExchangeCalcPubValConfigType
  Csm_GaaKeyExchangeCalcPubValConfigType[CSM_KEY_EXCHANGE_CALCPUBVAL_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveKeyExchangeCalcPubValService
  Csm_GddActiveKeyExchangeCalcPubValService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_KEY_EXCHANGE_CALC_PUB_VAL_STATUS == STD_ON) */

/*******************************************************************************
**                      KeyExchangeCalcSecret Interface                       **
*******************************************************************************/
#if (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON)
/* States */
#define CSM_KEY_EXCHANGE_CALC_SECRET_IDLE        (0x01U)
#define CSM_KEY_EXCHANGE_CALC_SECRET_START       (0x02U)
#define CSM_KEY_EXCHANGE_CALC_SECRET_ACTIVE      (0x04U)
#define CSM_KEY_EXCHANGE_CALC_SECRET_UPDATE      (0x08U)
#define CSM_KEY_EXCHANGE_CALC_SECRET_FINISH      (0x10U)

/* Structure contains all the information needed for Key Exchange */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Low] "No Impact of this rule violation" */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_KeyExchangeBaseType* basePtr,
    const Csm_KeyExchangePrivateType* privateValuePtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    uint8* sharedSecretPtr, uint32* sharedSecretLengthPtr,
    boolean TruncationIsAllowed);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_KeyExchangeCalcSecretConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_KeyExchangeCalcSecretConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveKeyExchangeCalcSecretService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_KeyExchangeCalcSecretConfigType
  Csm_GaaKeyExchangeCalcSecretConfigType[CSM_KEY_EXCHANGE_CALCSECRET_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveKeyExchangeCalcSecretService
  Csm_GddActiveKeyExchangeCalcSecretService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_KEY_EXCHANGE_CALC_SECRET_STATUS == STD_ON) */

/*******************************************************************************
**                      KeyExchangeCalcSymKey Interface                       **
*******************************************************************************/
#if (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON)
/* States */
#define CSM_KEY_EXCHANGE_CALC_SYM_KEY_IDLE       (0x01U)
#define CSM_KEY_EXCHANGE_CALC_SYM_KEY_START      (0x02U)
#define CSM_KEY_EXCHANGE_CALC_SYM_KEY_ACTIVE     (0x04U)
#define CSM_KEY_EXCHANGE_CALC_SYM_KEY_UPDATE     (0x08U)
#define CSM_KEY_EXCHANGE_CALC_SYM_KEY_FINISH     (0x10U)

/* Structure contains all the information needed for Symmetrical Key Exchange */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_KeyExchangeBaseType* basePtr,
    const Csm_KeyExchangePrivateType* privateValuePtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
  	Csm_SymKeyType* sharedKeyPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_KeyExchangeCalcSymKeyConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_KeyExchangeCalcSymKeyConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveKeyExchangeCalcSymKeyService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_KeyExchangeCalcSymKeyConfigType
  Csm_GaaKeyExchangeCalcSymKeyConfigType[CSM_KEY_EXCHANGE_CALCSYM_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveKeyExchangeCalcSymKeyService
  Csm_GddActiveKeyExchangeCalcSymKeyService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_KEY_EXCHANGE_CALC_SYM_KEY_STATUS == STD_ON) */

/*******************************************************************************
**                      Symmetrical Key Extraction Interface                  **
*******************************************************************************/
#if (CSM_SYM_KEY_EXTRACT_STATUS == STD_ON)
/* Macros for Symmetrical key extract Interface */
/* Symmetrical key extract Interface States */
#define CSM_SYM_KEY_EXTRACT_IDLE                 (0x01U)
#define CSM_SYM_KEY_EXTRACT_START                (0x02U)
#define CSM_SYM_KEY_EXTRACT_ACTIVE               (0x04U)
#define CSM_SYM_KEY_EXTRACT_UPDATE               (0x08U)
#define CSM_SYM_KEY_EXTRACT_FINISH               (0x10U)

/* Structure contains all the information needed for Key Extraction interface */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* dataPtr, uint32 dataLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    Csm_SymKeyType* keyPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_SymKeyExtractConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_SymKeyExtractConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveSymKeyExtractService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_SymKeyExtractConfigType
  Csm_GaaSymKeyExtractConfigType[CSM_SYM_KEY_EXTRACT_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveSymKeyExtractService Csm_GddActiveSymKeyExtractService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_SYM_KEY_EXTRACT_STATUS == STD_ON) */

/*******************************************************************************
**                      AsymmPubKeyExtract Interface                          **
*******************************************************************************/
#if (CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON)
/* Macros for Asymmetrical key extract Interface */
#define CSM_ASYM_PUBLIC_KEY_EXTRACT
/* Asymmetrical key extract Interface States */
#define CSM_ASYM_PUBLIC_KEY_EXTRACT_IDLE         (0x01U)
#define CSM_ASYM_PUBLIC_KEY_EXTRACT_START        (0x02U)
#define CSM_ASYM_PUBLIC_KEY_EXTRACT_ACTIVE       (0x04U)
#define CSM_ASYM_PUBLIC_KEY_EXTRACT_UPDATE       (0x08U)
#define CSM_ASYM_PUBLIC_KEY_EXTRACT_FINISH       (0x10U)

/* Structure contains all the information needed for Public Key Extraction */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* dataPtr, uint32 dataLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    Csm_AsymPublicKeyType* keyPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_AsymPublicKeyExtractConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_AsymPublicKeyExtractConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveAsymPublicKeyExtractService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_AsymPublicKeyExtractConfigType
  Csm_GaaAsymPublicKeyExtractConfigType[CSM_ASYM_PUBLIC_KEY_EXTRACT_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveAsymPublicKeyExtractService
  Csm_GddActiveAsymPublicKeyExtractService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_ASYM_PUBLIC_KEY_EXTRACT_STATUS == STD_ON) */

/*******************************************************************************
**                      AsymmPrivKeyExtract Interface                         **
*******************************************************************************/
#if (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON)
#define CSM_ASYM_PRIVATE_KEY_EXTRACT
/* States */
#define CSM_ASYM_PRIVATE_KEY_EXTRACT_IDLE        (0x01U)
#define CSM_ASYM_PRIVATE_KEY_EXTRACT_START       (0x02U)
#define CSM_ASYM_PRIVATE_KEY_EXTRACT_ACTIVE      (0x04U)
#define CSM_ASYM_PRIVATE_KEY_EXTRACT_UPDATE      (0x08U)
#define CSM_ASYM_PRIVATE_KEY_EXTRACT_FINISH      (0x10U)

/* Structure contains all the information needed for Private Key Extraction */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    const uint8* dataPtr, uint32 dataLength);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId,
    Csm_AsymPrivateKeyType* keyPtr);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_AsymPrivateKeyExtractConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_AsymPrivateKeyExtractConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveAsymPrivateKeyExtractService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_AsymPrivateKeyExtractConfigType
  Csm_GaaAsymPrivateKeyExtractConfigType[CSM_ASYM_PRIVATE_KEY_EXTRACT_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveAsymPrivateKeyExtractService
  Csm_GddActiveAsymPrivateKeyExtractService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_ASYM_PRIVATE_KEY_EXTRACT_STATUS == STD_ON) */

/*******************************************************************************
**                      Symmetrical Key Interface                             **
*******************************************************************************/
#if (CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON)
/* Macros for Symmetrical Key Wrap using Symmetrical key  */
#define CSM_SYM_KEY_WRAP_SYM
/* States */
#define CSM_SYM_KEY_WRAP_SYM_IDLE                (0x01U)
#define CSM_SYM_KEY_WRAP_SYM_START               (0x02U)
#define CSM_SYM_KEY_WRAP_SYM_ACTIVE              (0x04U)
#define CSM_SYM_KEY_WRAP_SYM_UPDATE              (0x08U)
#define CSM_SYM_KEY_WRAP_SYM_FINISH              (0x10U)

/* Structure contains all the information needed for Key Wrapping interface */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_SymKeyType* keyPtr, const Csm_SymKeyType* wrappingKeyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    uint8* dataPtr, uint32* dataLengthPtr);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_SymKeyWrapSymConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_SymKeyWrapSymConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveSymKeyWrapSymService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_SymKeyWrapSymConfigType
  Csm_GaaSymKeyWrapSymConfigType[CSM_SYM_KEY_WRAP_SYM_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveSymKeyWrapSymService Csm_GddActiveSymKeyWrapSymService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_SYM_KEY_WRAP_SYM_STATUS == STD_ON) */

/*******************************************************************************
**                      Asymmetrical Key Interface                            **
*******************************************************************************/
#if (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON)
/* Macros for Symmetrical Key Wrap using asymmetrical key  */
#define CSM_SYM_KEY_WRAP_ASYM
/* States */
#define CSM_SYM_KEY_WRAP_ASYM_IDLE               (0x01U)
#define CSM_SYM_KEY_WRAP_ASYM_START              (0x02U)
#define CSM_SYM_KEY_WRAP_ASYM_ACTIVE             (0x04U)
#define CSM_SYM_KEY_WRAP_ASYM_UPDATE             (0x08U)
#define CSM_SYM_KEY_WRAP_ASYM_FINISH             (0x10U)

/* Structure contains all the information needed for  Key Wrapping interface */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_SymKeyType* keyPtr, const Csm_AsymPublicKeyType* wrappingKeyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    uint8* dataPtr, uint32* dataLengthPtr);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_SymKeyWrapAsymConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_SymKeyWrapAsymConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveSymKeyWrapAsymService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_SymKeyWrapAsymConfigType
  Csm_GaaSymKeyWrapAsymConfigType[CSM_SYM_KEY_WRAP_ASYM_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveSymKeyWrapAsymService Csm_GddActiveSymKeyWrapAsymService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_SYM_KEY_WRAP_ASYM_STATUS == STD_ON) */

/*******************************************************************************
**                      Symmetrical key Interface                             **
*******************************************************************************/
#if (CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON)
/* Macros for Asymmetrical wrapping using Symmetrical Key */
#define CSM_ASYM_KEY_WRAP_SYM
/* States */
#define CSM_ASYM_PRIVATE_KEY_WRAP_SYM_IDLE       (0x01U)
#define CSM_ASYM_PRIVATE_KEY_WRAP_SYM_START      (0x02U)
#define CSM_ASYM_PRIVATE_KEY_WRAP_SYM_ACTIVE     (0x04U)
#define CSM_ASYM_PRIVATE_KEY_WRAP_SYM_UPDATE     (0x08U)
#define CSM_ASYM_PRIVATE_KEY_WRAP_SYM_FINISH     (0x10U)

/* Structure contains all the information needed for Private Key Wrapping */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_AsymPrivateKeyType* keyPtr, const Csm_SymKeyType* wrappingKeyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    uint8* dataPtr, uint32* dataLengthPtr);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_AsymPrivateKeyWrapSymConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_AsymPrivateKeyWrapSymConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveAsymPrivateKeyWrapSymService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_AsymPrivateKeyWrapSymConfigType
  Csm_GaaAsymPrivateKeyWrapSymConfigType[CSM_ASYM_KEY_WRAP_SYM_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveAsymPrivateKeyWrapSymService
  Csm_GddActiveAsymPrivateKeyWrapSymService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_ASYM_KEY_WRAP_SYM_STATUS == STD_ON) */

/*******************************************************************************
**                      Asymmetrical key Interface                            **
*******************************************************************************/
#if (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON)
/* Macros for Asymmetrical wrapping using asymmetrical key */
#define CSM_ASYM_KEY_WRAP_ASYM
/* States */
#define CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_IDLE      (0x01U)
#define CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_START     (0x02U)
#define CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_ACTIVE    (0x04U)
#define CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_UPDATE    (0x08U)
#define CSM_ASYM_PRIVATE_KEY_WRAP_ASYM_FINISH    (0x10U)

/* Structure contains all the information needed for Private Key Wrapping */
typedef struct
{
  /* pointer to the callback function to be called upon service completion */
  Csm_CallbackType CallbackFct;

  /* pointer to Primitive Start Function */
  Std_ReturnType (*PrimitiveStartFct)(const void* cfgPtr,
    const Csm_AsymPrivateKeyType* keyPtr,
    const Csm_AsymPublicKeyType* wrappingKeyPtr);

  /* pointer to Primitive Update Function */
  Std_ReturnType (*PrimitiveUpdateFct)(Csm_ConfigIdType cfgId,
    uint8* dataPtr, uint32* dataLengthPtr);

  /* pointer to Primitive Finish Function */
  Std_ReturnType (*PrimitiveFinishFct)(Csm_ConfigIdType cfgId);

  void (*PrimitiveMainFct)(void); /* pointer to Primitive Function */

  void* PrimitiveConfigPtr; /* pointer to configuration of Primitive */

  Csm_ConfigIdType configId;      /* Configuration Identifier */
} Csm_AsymPrivateKeyWrapAsymConfigType;

/* RAM structure for CSM context storage */
typedef struct
{
  /* Pointer to the current active service type */
  const Csm_AsymPrivateKeyWrapAsymConfigType* pActiveServiceConfig;

  /* Stores the current state of corresponding service */
  uint8 ucServiceState;
} Csm_ActiveAsymPrivateKeyWrapAsymService;

#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const Csm_AsymPrivateKeyWrapAsymConfigType
  Csm_GaaAsymPrivateKeyWrapAsymConfigType[CSM_ASYM_KEY_WRAP_ASYM_CFGID_LIMIT];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global structure variable to indicate the state of CSM interfaces */
extern Csm_ActiveAsymPrivateKeyWrapAsymService
  Csm_GddActiveAsymPrivateKeyWrapAsymService;
#define CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (CSM_ASYM_KEY_WRAP_ASYM_STATUS == STD_ON) */

/* polyspace-end MISRA-C3:8.6 [Justified:Low] "The global variable shall be generated by configuration tool " */

#endif /* CSM_TYPES_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:D4.5 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:2.5 [Not a defect:Low] "Macro can be used according to configuration" */

/******************************************************************************
**                      End of File                                          **
******************************************************************************/
