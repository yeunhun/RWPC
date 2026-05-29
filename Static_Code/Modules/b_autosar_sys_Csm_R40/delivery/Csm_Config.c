/*******************************************************************************
**                                                                            **
**  (C) 2016~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Config.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                  **
**                                                                            **
**  PURPOSE   : Csm module const variable definitions for making a library    **
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

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Config.h"

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (CSM_HASH_STATUS == STD_ON)
/* CSM_HASH_CFGID_LIMIT */
const uint32 Csm_GddHashCfgidLimit = CSM_HASH_CFGID_LIMIT;
#endif /* (CSM_HASH_STATUS == STD_ON) */

#if (CSM_MAC_GENERATE_STATUS == STD_ON)
/* CSM_MAC_GENERATE_CFGID_LIMIT */
const uint32 Csm_GddMacGenerateCfgidLimit = CSM_MAC_GENERATE_CFGID_LIMIT;
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

#if (CSM_MAC_VERIFY_STATUS == STD_ON)
/* CSM_MAC_VERIFY_CFGID_LIMIT */
const uint32 Csm_GddMacVerifyCfgidLimit = CSM_MAC_VERIFY_CFGID_LIMIT;
#endif /* (CSM_MAC_VERIFY_STATUS == STD_ON) */

#if (CSM_RANDOM_SEED_STATUS == STD_ON)
/* CSM_RANDOM_SEED_CFGID_LIMIT */
const uint32 Csm_GddRandomSeedCfgidLimit = CSM_RANDOM_SEED_CFGID_LIMIT;
#endif /* (CSM_RANDOM_SEED_STATUS == STD_ON) */

#if (CSM_RANDOM_GENERATE_STATUS == STD_ON)
#if (defined(CSM_RANDOM_AUTRANDOMSEED) && (CSM_RANDOM_AUTRANDOMSEED == STD_ON)) \
  || (defined(CSM_RANDOM_AUTRANDOMGENERATE) && (CSM_RANDOM_AUTRANDOMGENERATE == STD_ON))
/* CSM_AUTRANDOM_SEED_ADDR */
const uint32 Csm_GulAutRandomSeedAddr = CSM_AUTRANDOM_SEED_ADDR;
#endif
#endif /* (CSM_RANDOM_GENERATE_STATUS == STD_ON) */

#if (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON)
/* CSM_SYM_BLOCK_ENCRYPT_CFGID_LIMIT */
const uint32 Csm_GddSymBlockEncryptCfgidLimit = CSM_SYM_BLOCK_ENCRYPT_CFGID_LIMIT;
#endif /* (CSM_SYM_BLOCK_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON)
/* CSM_SYM_BLOCK_DECRYPT_CFGID_LIMIT */
const uint32 Csm_GddSymBlockDecryptCfgidLimit = CSM_SYM_BLOCK_DECRYPT_CFGID_LIMIT;
#endif /* (CSM_SYM_BLOCK_DECRYPT_STATUS == STD_ON) */

#if (CSM_SYM_ENCRYPT_STATUS == STD_ON)
/* CSM_SYM_ENCRYPT_CFGID_LIMIT */
const uint32 Csm_GddSymEncryptCfgidLimit = CSM_SYM_ENCRYPT_CFGID_LIMIT;
#endif /* (CSM_SYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_SYM_DECRYPT_STATUS == STD_ON)
/* CSM_SYM_DECRYPT_CFGID_LIMIT */
const uint32 Csm_GddSymDecryptCfgidLimit = CSM_SYM_DECRYPT_CFGID_LIMIT;
#endif /* (CSM_SYM_DECRYPT_STATUS == STD_ON) */

#if (CSM_ASYM_ENCRYPT_STATUS == STD_ON)
/* CSM_ASYM_ENCRYPT_CFGID_LIMIT */
const uint32 Csm_GddAsymEncryptCfgidLimit = CSM_ASYM_ENCRYPT_CFGID_LIMIT;
#endif /* (CSM_ASYM_ENCRYPT_STATUS == STD_ON) */

#if (CSM_ASYM_DECRYPT_STATUS == STD_ON)
/* CSM_ASYM_DECRYPT_CFGID_LIMIT */
const uint32 Csm_GddAsymDecryptCfgidLimit = CSM_ASYM_DECRYPT_CFGID_LIMIT;
#endif /* (CSM_ASYM_DECRYPT_STATUS == STD_ON) */

#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
/* CSM_SIGNATURE_GENERATE_CFGID_LIMIT */
const uint32 Csm_GddSignatureGenerateCfgidLimit = CSM_SIGNATURE_GENERATE_CFGID_LIMIT;
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

#if (CSM_SIGNATURE_VERIFY_STATUS == STD_ON)
/* CSM_SIGNATURE_VERIFY_CFGID_LIMIT */
const uint32 Csm_GddSignatureVerifyCfgidLimit = CSM_SIGNATURE_VERIFY_CFGID_LIMIT;
#endif /* (CSM_SIGNATURE_VERIFY_STATUS == STD_ON) */

#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
