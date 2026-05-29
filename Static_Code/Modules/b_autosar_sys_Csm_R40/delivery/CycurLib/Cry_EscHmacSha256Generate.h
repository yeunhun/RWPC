/*******************************************************************************
**                                                                            **
**  (C) 2016~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscHmacSha256Generate.h                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - Escrypt HMAC SHA256 Generate                              **
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
** 1.0.3     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.2     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.0.1     27-Feb-2017   Sinil        Redmine #7650                         **
** 1.0.0     27-Sep-2016   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_ESCHMACSHA256GENERATE_H
#define CRY_ESCHMACSHA256GENERATE_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_MAC_GENERATE_STATUS == STD_ON)
#if (CSM_MAC_ESCHMACSHA256GENERATE == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_EscHmacSha256GenerateStart(const void* cfgPtr,
  const Csm_SymKeyType* keyPtr);

extern Std_ReturnType Cry_EscHmacSha256GenerateUpdate(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength);

extern Std_ReturnType Cry_EscHmacSha256GenerateFinish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed);

extern void Cry_EscHmacSha256GenerateMainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_MAC_ESCHMACSHA256GENERATE == STD_ON) */
#endif /* (CSM_MAC_GENERATE_STATUS == STD_ON) */

#endif /* CRY_ESCHMACSHA256GENERATE_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
