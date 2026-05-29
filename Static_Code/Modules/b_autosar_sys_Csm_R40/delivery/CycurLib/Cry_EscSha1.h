/*******************************************************************************
**                                                                            **
**  (C) 2015~2019 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Cry_EscSha1.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crypto Service Manager Module                         **
**                                                                            **
**  PURPOSE   : Header file for primitives interface                          **
**                - Escrypt Sha1                                              **
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
** 1.0.8     22-Feb-2019   Sinil        Redmine #16157                        **
** 1.0.7     21-Sep-2017   Sinil        Redmine #10040                        **
** 1.0.6     27-Feb-2017   Sinil        Redmine #7650                         **
** 1.0.5     09-Aug-2016   Sinil        Redmine #5693                         **
** 1.0.4     12-Jul-2016   Sinil        Redmine #5514                         **
** 1.0.3     26-May-2016   Sinil        Redmine #4533                         **
** 1.0.2     13-May-2016   Sinil        Redmine #4887                         **
** 1.0.1     02-Dec-2015   Sinil        Memory section changed                **
** 1.0.0     10-Mar-2015   Autron       Initial version                       **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef CRY_ESCSHA1_H
#define CRY_ESCSHA1_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Types.h"
#include "Cry_Init.h"

#if (CSM_HASH_STATUS == STD_ON)
#if (CSM_HASH_ESCSHA1 == STD_ON)
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

extern Std_ReturnType Cry_EscSha1Start(const void* cfgPtr);

extern Std_ReturnType Cry_EscSha1Update(Csm_ConfigIdType cfgId,
  const uint8* dataPtr, uint32 dataLength);

extern Std_ReturnType Cry_EscSha1Finish(Csm_ConfigIdType cfgId,
  uint8* resultPtr, uint32* resultLengthPtr, boolean TruncationIsAllowed);

extern void Cry_EscSha1MainFunction(void);

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (CSM_HASH_ESCSHA1 == STATUS_ON) */
#endif /* (CSM_HASH_STATUS == STD_ON)  */

#endif /* CRY_ESCSHA1_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
