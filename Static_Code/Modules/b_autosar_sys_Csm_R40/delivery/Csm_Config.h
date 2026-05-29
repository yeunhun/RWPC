/*******************************************************************************
**                                                                            **
**  (C) 2016~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Config.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Csm module const variable declarations for making a library   **
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
** 1.0.6     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.5     21-Sep-2017   Sinil        Redmine #10032                        **
** 1.0.4     11-Jan-2017   Sinil        Redmine #7198                         **
** 1.0.3     09-Aug-2016   Sinil        Redmine #5695, #5744                  **
** 1.0.2     29-Jul-2016   Sinil        Redmine #5514, #5716                  **
** 1.0.1     16-May-2016   Sinil        Redmine #4903                         **
** 1.0.0     12-May-2016   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CSM_CONFIG_H
#define CSM_CONFIG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_Type.h"
#include "Csm_Cfg.h"

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (CSM_HASH_STATUS == STD_ON)
/* CSM_HASH_CFGID_LIMIT */
extern const uint32 Csm_GddHashCfgidLimit;
#endif /* (CSM_HASH_STATUS == STD_ON) */

#if (CSM_MAC_GENERATE_STATUS == STD_ON)
/* CSM_MAC_GENERATE_CFGID_LIMIT */
extern const uint32 Csm_GddMacGenerateCfgidLimit;
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

#if (CSM_MAC_VERIFY_STATUS == STD_ON)
/* CSM_MAC_VERIFY_CFGID_LIMIT */
extern const uint32 Csm_GddMacVerifyCfgidLimit;
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

#if (CSM_RANDOM_SEED_STATUS == STD_ON)
/* CSM_RANDOM_SEED_CFGID_LIMIT */
extern const uint32 Csm_GddRandomSeedCfgidLimit;
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON) */

#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
#if (defined(CSM_RANDOM_AUTRANDOMSEED) && (CSM_RANDOM_AUTRANDOMSEED == STD_ON)) \
  || (defined(CSM_RANDOM_AUTRANDOMGENERATE) && (CSM_RANDOM_AUTRANDOMGENERATE == STD_ON))
/* CSM_AUTRANDOM_SEED_ADDR */
extern const uint32 Csm_GulAutRandomSeedAddr;
#endif
#endif /* (CSM_RANDOM_GENERATE_STATUS == STD_ON) */

#if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
/* CSM_SYM_BLOCK_ENCRYPT_CFGID_LIMIT */
extern const uint32 Csm_GddSymBlockEncryptCfgidLimit;
#endif /* (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
/* CSM_SYM_BLOCK_DECRYPT_CFGID_LIMIT */
extern const uint32 Csm_GddSymBlockDecryptCfgidLimit;
#endif /* (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) */

#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
/* CSM_SYM_ENCRYPT_CFGID_LIMIT */
extern const uint32 Csm_GddSymEncryptCfgidLimit;
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_DECRYPT_STATUS == STD_ON)
/* CSM_SYM_DECRYPT_CFGID_LIMIT */
extern const uint32 Csm_GddSymDecryptCfgidLimit;
#endif /* (CSM_SYM_DECRYPT_STATUS == STD_ON) */

#if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
/* CSM_ASYM_ENCRYPT_CFGID_LIMIT */
extern const uint32 Csm_GddAsymEncryptCfgidLimit;
#endif /* (CSM_ASYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_ASYM_DECRYPT_STATUS == STD_ON)
/* CSM_ASYM_DECRYPT_CFGID_LIMIT */
extern const uint32 Csm_GddAsymDecryptCfgidLimit;
#endif /* (CSM_ASYM_DECRYPT_STATUS == STD_ON) */

#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
/* CSM_SIGNATURE_GENERATE_CFGID_LIMIT */
extern const uint32 Csm_GddSignatureGenerateCfgidLimit;
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
/* CSM_SIGNATURE_VERIFY_CFGID_LIMIT */
extern const uint32 Csm_GddSignatureVerifyCfgidLimit;
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#endif /* CSM_CONFIG_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
