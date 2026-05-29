/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : BswM_CanSM.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR BswM Module                                           **
**                                                                            **
**  PURPOSE   : Providing interface to CanSM                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 3.0.6     07-Sep-2021   Junho Cho     Redmine #31864                       **
** 1.0.0     04-Mar-2013   Daejun Park   Initial version                      **
*******************************************************************************/

#ifndef BSWM_CANSM_H
#define BSWM_CANSM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM.h"
#include "ComStack_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define BSWM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, BSWM_CODE) BswM_CanSM_CurrentState
  (NetworkHandleType Network, CanSM_BswMCurrentStateType CurrentState);
#define BSWM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* BSWM_CANSM_H */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
