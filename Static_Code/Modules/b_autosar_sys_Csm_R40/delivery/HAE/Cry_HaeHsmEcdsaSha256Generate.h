/*******************************************************************************
**                                                                            **
**  (C) 2017~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_HaeHsmEcdsaSha256Generate.h                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - HAE HSM ECDSA SHA256 Generate                             **
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
** 1.0.1     15-Jun-2020   JaeHyun      Redmine #23571                        **
** 1.0.0     3-Apr-2020    JaeHyun      Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-begin MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

#ifndef CRY_HAEHSMECDSASHA256GENERATE_H
#define CRY_HAEHSMECDSASHA256GENERATE_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_SIGNATURE_GENERATE_STATUS == STD_ON)
#if (CSM_SIGNATURE_HAEHSMECDSASHA256GENERATE == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_HaeHsmEcdsaSha256GenerateStart(const void* cfgPtr,
  const Csm_AsymPrivateKeyType* keyPtr);
  
extern Std_ReturnType Cry_HaeHsmEcdsaSha256GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength);
  
extern Std_ReturnType Cry_HaeHsmEcdsaSha256GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32 *resultLengthPtr);

extern void Cry_HaeHsmEcdsaSha256GenerateMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_SIGNATURE_HAEHSMECDSASHA256GENERATE == STD_ON) */
#endif /* (CSM_SIGNATURE_GENERATE_STATUS == STD_ON) */

#endif /* CRY_HAEHSMECDSASHA256GENERATE_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */
/* polyspace-end MISRA2012:5.1 [Not a defect:Low] "Follow AUTOSAR standard naming rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
