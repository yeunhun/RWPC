/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  FILE-NAME : BswM_Sd.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR BswM Module                                           **
**                                                                            **
**  PURPOSE   : Providing interface to Sd                                     **
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
** 2.7.0     11-Mar-2020   Junho Cho     Initial version                      **
*******************************************************************************/

#ifndef BSWM_SD_H
#define BSWM_SD_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Sd.h"

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
/* Extern for BswM_Sd_ClientServiceCurrentState */
extern FUNC(void, BSWM_CODE) BswM_Sd_ClientServiceCurrentState
 (uint16 SdClientServiceHandleId, Sd_ClientServiceCurrentStateType CurrentClientState);

/* Extern for BswM_Sd_ConsumedEventGroupCurrentState */
extern FUNC(void, BSWM_CODE) BswM_Sd_ConsumedEventGroupCurrentState
 (uint16 SdConsumedEventGroupHandleId, Sd_ConsumedEventGroupCurrentStateType ConsumedEventGroupState);

/* Extern for BswM_Sd_EventHandlerCurrentState */
extern FUNC(void, BSWM_CODE) BswM_Sd_EventHandlerCurrentState
 (uint16 SdEventHandlerHandleId, Sd_EventHandlerCurrentStateType EventHandlerStatus);
#define BSWM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* BSWM_SD_H */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
