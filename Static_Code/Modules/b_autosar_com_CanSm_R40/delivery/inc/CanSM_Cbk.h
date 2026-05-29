/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.                                      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_Cbk.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
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
** 1.12.0    29-Apr-2019   SM Kwon        #17202                              **
** 1.11.0    23-Oct-2018   Lim Jong Sun   #14496                              **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7076                               **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/
#ifndef CANSM_CBK_H
#define CANSM_CBK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"                    /* CanIf header file */
#include "CanSM_Cfg.h"                /* CanSM Config header file */
#include "CanSM_InternalTypes.h"            /* CanSM PCTypes header file */
#include "CanSM_TxTimeOutException.h" /* CanSM TxTimeOutException header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANSM_CBK_H_AR_RELEASE_MAJOR_VERSION         4
#define CANSM_CBK_H_AR_RELEASE_MINOR_VERSION         0
#define CANSM_CBK_H_AR_RELEASE_REVISION_VERSION      3

/* Software Version Information */
#define CANSM_CBK_H_SW_MAJOR_VERSION                 1
#define CANSM_CBK_H_SW_MINOR_VERSION                 12

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                Function Prototypes                                         **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_ControllerBusOff(uint8 Controller);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_ConfirmPnAvailability(uint8 Transceiver);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_ControllerModeIndication(uint8 Controller,
  CanIf_ControllerModeType ControllerMode);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#if (STD_OFF == CANSM_DEV_ERROR_DETECT)
extern FUNC(void, CANSM_CODE) CanSM_ModeIndication(uint8 Transceiver);

#else
extern FUNC(void, CANSM_CODE) CanSM_ModeIndication(uint8 Transceiver, uint8
  ServiceID);

#endif /* End of #if (STD_ON == CANSM_DEV_ERROR_DETECT) */
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

#if (STD_ON == CANSM_CANTRCV_SUPPORT)
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_TransceiverModeIndication(uint8 Transceiver,
  CanTrcv_TrcvModeType TransceiverMode);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif /* End of #if (STD_ON == CANSM_CANTRCV_SUPPORT) */

#endif /* End of ifndef CANSM_CBK_H */

/*******************************************************************************
**                   End of File                                              **
*******************************************************************************/

