/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_ControllEventQueue.h                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Implementation of ControlEventQueue module                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.5.4     14-Dec-2021    YH.Han        Redmine #33448                      **
** 1.0.0     14-Jul-2016    SH.Yoo        Redmine #4024                       **
*******************************************************************************/

#ifndef OPF_CONTROLLEVENTQUEUE_H
#define OPF_CONTROLLEVENTQUEUE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_Types.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.7 [Not a Defect] "AUTOSAR compiler abstraction" */
extern FUNC(void, OPF_CODE) Opf_InitEventQueue(void);
extern FUNC(void, OPF_CODE) Opf_AddNewEvent(Tdd_Opf_Event *pEvent);
extern FUNC(Tdd_Opf_Event*, OPF_CODE) Opf_GetLastEvent(void);
extern FUNC(Tdd_Opf_Event*, OPF_CODE) Opf_GetLastProfileEvent(void);
extern FUNC(void, OPF_CODE) Opf_SetLastEvent(Tdd_Opf_Event *pEvent);
extern FUNC(void, OPF_CODE) Opf_ClearEventQueue(void);
extern FUNC(void, OPF_CODE) Opf_UpdateProfiledEventQueue(void);
/* polyspace-end MISRA-C3:20.7 */

#endif /* OPF_CONTROLLEVENTQUEUE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
