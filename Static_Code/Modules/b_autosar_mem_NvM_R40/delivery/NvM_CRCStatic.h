/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_CRCStatic.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Provision of Macros and API Prototype Declarations            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date           By          Description                         **
********************************************************************************
** 1.1.7       09-Jul-2015  Song CY       As per RedMine 2265,                **
**                                        Change CompareCRCSID return type    **
** 1.1.6       03-Mar-2015  Song CY       As per RedMine 2216, Remove version **
**                                        Information                         **
** 1.1.4       02-Dec-2014  Song CY       RedMine 1719, Update for PolySpace  **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/

#ifndef NVM_CRCSTATIC_H
#define NVM_CRCSTATIC_H

/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */

/*******************************************************************************
**                   Include Section                                         ***
*******************************************************************************/
#include "NvM.h"
#include "NvM_PCTypes.h"

/*******************************************************************************
**                    Function Prototypes                                     **
*******************************************************************************/
#if((NVM_STATIC_ID_CHECK == STD_ON) || (NVM_CRC_SUPPORT == STD_ON))
#define NVM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, NVM_CODE) NvM_CalculateCRCStaticID
  (NvM_BlockIdType BlockId);
extern FUNC(Std_ReturnType, NVM_CODE) NvM_CompareCRCSID(void);
#define NVM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* polyspace-end MISRA-C3:20.1 [Justified:Low] "Implemented according to AUTOSAR specification" */

#endif /* NVM_CRCSTATIC_H */
/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
