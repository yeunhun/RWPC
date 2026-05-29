/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : EcuM_Os.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Provision of external declaration of APIs and Service IDs     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
** 3.0.5      17-Aug-2021   Junho Cho     Redmine #31552                      **
** 2.2.1      26-Dec-2014   Daejun Park   Redmine #1879                       **
**                                        -Update to AUTRON template          **
** 1.0.11     04-Jul-2013   Daejun Park   CR~129, XAR~581 : EcuM library      **
** 1.0.0      04-Mar-2013   Daejun Park   Initial version                     **
*******************************************************************************/

#ifndef ECUM_OS_H
#define ECUM_OS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (ECUM_ALARM_CLOCK_PRESENT == STD_ON)
#define ECUM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ECUM_CODE) EcuM_IncrementTimer(void);

#define ECUM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#endif /* ECUM_OS_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

