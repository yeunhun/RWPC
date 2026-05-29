/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_IOManager.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : C header for IO Manager                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By         Description                             **
********************************************************************************
** 1.15.0.2  09-Sep-2021   Yangjin    #31974                                  **
** 1.13.0    20-Jan-2021   Yangjin    #27489                                  **
** 1.9.0     04-Jun-2020   Yangjin    #23413                                  **
** 1.3.1     30-Apr-2019   Yangjin    #17059                                  **
** 1.0.7     06-Jul-2017   Jongyoung  #9107                                   **
** 1.0.6     31-Mar-2017   Jongyoung  #7890                                   **
** 1.0.5     05-Mar-2017   Jongyoung  #7764                                   **
** 1.0.4     05-Jun-2015   Jongyoung  1.Misra-C coding Rule adaption          **
**                                      Duplicated Extern declaration (8.8)   **
** 1.0.3     27-Sep-2014   Jongyoung  Polyspace result Adaption               **
** 1.0.2     18-Sep-2014   Sinil      1. Remove unnecessary include           **
** 1.0.1     28-Apr-2014   Sinil         Task ID : 853                        **
**                                       Update including os header with      **
**                                       mcal info                            **
** 1.0.0     07-Mar-2014   Sinil      Initial version                         **
*******************************************************************************/
#ifndef IOHWAB_IOMANAGER_H
#define IOHWAB_IOMANAGER_H
/* polyspace-begin MISRA-C3:D4.5 [Justified:Unset] "Not a defect" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"
#include "Os.h"


#if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
#include "CoSvAb_FastTimer.h"
#endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */

#if (IOHWAB_USE_PM_MODULE == STD_ON)
extern FUNC(Std_ReturnType, Pm_CODE) Pm_GetPowerMode(P2VAR(Pm_PowerModeType, AUTOMATIC, RTE_APPL_DATA) mode);
#endif /* (IOHWAB_USE_PM_MODULE == STD_ON) */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/*polyspace:begin<MISRA-C:8.8:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : Rte SWS #7283)*/

#if (IOHWAB_USE_IO_MAN == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMInit(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMDeInit(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMAnaInAcqEnd(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOML2H(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMH2L(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMInputsLP(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMOutputsLP(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMOnTimer(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, IOHWAB_CODE)IoHwAb_IOMDelayTicks(uint32 ticks);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */
/*polyspace:end<MISRA-C:8.8:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : Rte SWS #7283)*/
/* polyspace-end MISRA-C3:D4.5 [Justified:Unset] "Not a defect" */
#endif /* IOHWAB_IOMANAGER_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
