/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.								      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_Dcm.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of declaration of initialization function           **
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
** 1.12.3    12-Mar-2020   SM Kwon        #22336                              **
** 1.12.0    29-Apr-2019   SM Kwon        #17202                              **
** 1.11.0    07-Sep-2018   Lim Jong Sun   #14000, #14496                      **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7076                               **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/
#ifndef CANSM_DCM_H
#define CANSM_DCM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM.h"                     /* ComM header file */
#include "CanSM_Internal.h"           /* BaudRate header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANSM_DCM_H_AR_RELEASE_MAJOR_VERSION         4
#define CANSM_DCM_H_AR_RELEASE_MINOR_VERSION         0
#define CANSM_DCM_H_AR_RELEASE_REVISION_VERSION      3

/* Software Version Information */
#define CANSM_DCM_H_SW_MAJOR_VERSION                 1
#define CANSM_DCM_H_SW_MINOR_VERSION                 12


/*******************************************************************************
**                  Global Data Types                                         **
*******************************************************************************/

/*******************************************************************************
**                Function Prototypes                                         **
*******************************************************************************/
#if (STD_ON == CANSM_CHANGE_BAUDRATE_API)

#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_CheckBaudrate(NetworkHandleType
  network, CONST(uint16, CANSM_CONST) Baudrate);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_ChangeBaudrate(NetworkHandleType
  network, CONST(uint16, CANSM_CONST) Baudrate);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* End of if (STD_ON == CANSM_CHANGE_BAUDRATE_API) */
#endif /* CANSM_COMM_H */

/*******************************************************************************
**                   End of File                                              **
*******************************************************************************/

