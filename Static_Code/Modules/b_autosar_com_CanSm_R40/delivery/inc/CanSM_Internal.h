/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.								      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_Internal.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AAUTOSAR CAN State Manager Module                             **
**                                                                            **
**  PURPOSE   : Header file for CanSM_MainFunction related API                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.12.3    12-Nov-2020   SM Kwon        #25247                              **
** 1.12.0    29-Apr-2019   SM KWon        #17202                              **
** 1.11.0    23-Oct-2018   Lim Jong Sun   #14496                              **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7076                               **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/
#ifndef CANSM_INTERNAL_H
#define CANSM_INTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM.h"                /* CanSM header file */
#include "CanIf.h"                /* CanIf header file */
#include "ComM.h"                 /* ComM header file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANSM_INTERNAL_H_AR_RELEASE_MAJOR_VERSION         4
#define CANSM_INTERNAL_H_AR_RELEASE_MINOR_VERSION         0
#define CANSM_INTERNAL_H_AR_RELEASE_REVISION_VERSION      3

/* Software Version Information */
#define CANSM_INTERNAL_H_SW_MAJOR_VERSION                 1
#define CANSM_INTERNAL_H_SW_MINOR_VERSION                 12


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/* extern for CanSM_NoCommunication */
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_NoCommunication(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_SilentCommunication */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_SilentCommunication(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_FullCommunication */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_FullCommunication(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_BORStart */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_BORStart(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_BORWait */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_BORWait(NetworkHandleType LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_CheckBusOff */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_CheckBusOff(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_DeInitPnNotSupported */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_DeInitPnNotSupported(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_DeInitPnSupported */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
#if (STD_ON == CANSM_PN_AVAILABILITY)
extern FUNC(void, CANSM_CODE) CanSM_DeInitPnSupported(NetworkHandleType
  LddNetworkHandle);

#endif
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_NoToFullCommRequested */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_NoToFullCommRequested(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_SilentToFullCommRequested */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_SilentToFullCommRequested(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_TxTimeoutExceptionService */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_TxTimeoutExceptionService(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_TimeoutProcessing */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_TimeoutProcessing(NetworkHandleType
  LddNetworkHandle, Std_ReturnType LddResult);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_ChangeBaudRateService */
#if (STD_ON == CANSM_CHANGE_BAUDRATE_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_ChangeBaudRateService(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif

/* extern for CanSM_SilentCommRequested */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_SilentCommRequested(NetworkHandleType
  LddNetworkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

#endif /* CANSM_MAIN_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

