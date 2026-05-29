/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.				                      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_TxTimeoutException.h                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : As optional interface to the CanNm module.                    **
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
** 1.12.2    17-Jan-2020   SM Kwon        #20964                              **
** 1.12.0    17-Jun-2019   SM Kwon        #17747                              **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7076                               **
** 1.9.4     11-Sep-2015   Lim Jong Sun   Fixed MISRA-C Violation             **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/
#ifndef CANSM_TXTIMEOUTEXCEPTION_H
#define CANSM_TXTIMEOUTEXCEPTION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM_Cfg.h"            /* CanSM Config header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANSM_TIMEOUT_AR_REL_MAJOR_VER         4
#define CANSM_TIMEOUT_AR_REL_MINOR_VER         0
#define CANSM_TIMEOUT_AR_REL_REV_VER           3

/* Software Version Information */
#define CANSM_TIMEOUT_SW_MAJOR_VERSION                 1
#define CANSM_TIMEOUT_SW_MINOR_VERSION                 12

/*******************************************************************************
**                  Global Data Types                                         **
*******************************************************************************/

/*******************************************************************************
**                Function Prototypes                                         **
*******************************************************************************/
/* Extern for CanSM_TxTimeoutException */
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_TxTimeoutException(NetworkHandleType Channel);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif /* CANSM_TXTIMEOUTEXCEPTION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

