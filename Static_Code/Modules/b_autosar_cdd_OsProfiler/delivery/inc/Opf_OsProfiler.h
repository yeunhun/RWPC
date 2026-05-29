/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Opf_GetProfileData.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : OS Profiler                                                   **
**                                                                            **
**  PURPOSE   : Implementation of OsProfiler module                           **
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

#ifndef OPF_OSPROFILER_H
#define OPF_OSPROFILER_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Opf_Cfg.h"
#include "Opf_Types.h"
#include "Opf_ReceiveEvent.h"
#include "Opf_GetProfileData.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern FUNC(void, OPF_CODE) Opf_InitOsProfiler(void);
extern FUNC(void, OPF_CODE) Opf_StartOsProfiler(void);
extern FUNC(void, OPF_CODE) Opf_StopOsProfiler(void);
extern FUNC(OpfRecModeType, OPF_CODE) Opf_GetOsProfilerRecMode(void);
extern FUNC(void, OPF_CODE) Opf_RestartOsProfiler(void);

#endif /* OPF_OSPROFILER_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
