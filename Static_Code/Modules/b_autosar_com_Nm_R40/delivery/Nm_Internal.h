/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Nm_Internal.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm                                                    **
**                                                                            **
**  PURPOSE   : Header file for Nm_Internal.c                                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision      Date         By         Description                          **
********************************************************************************
** 2.2.0     28-Dec-2018   JeongSu Lim   #13630, #15277, #15276, #15275,      **
**                                       #15274                               **
** 1.0.0     26-Nov-2012   Kt Kim        Initial Version                      **
*******************************************************************************/

#ifndef NM_INTERNAL_H
#define NM_INTERNAL_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Nm_Cfg.h"
/*******************************************************************************
**                       Version Information                                  **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define NM_INTERNAL_AR_RELEASE_MAJOR_VERSION      (4)
#define NM_INTERNAL_AR_RELEASE_MINOR_VERSION      (0)
#define NM_INTERNAL_AR_RELEASE_REVISION_VERSION   (3)

/* Software Version Information */
#define NM_INTERNAL_SW_MAJOR_VERSION   (2)
#define NM_INTERNAL_SW_MINOR_VERSION   (3)
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, NM_CODE) Nm_ClusterWakeUp(
  CONST(uint8, NM_APPL_CONST MappingIndex),
  CONST(uint8, NM_APPL_CONST) ClusterSize);

extern FUNC(boolean, NM_CODE) Nm_IntGetChannelIndexFromChannelId(
  CONST(NetworkHandleType, NM_APPL_CONST) LddChannelId,
  P2VAR(NetworkHandleType, AUTOMATIC, NM_APPL_DATA) LpChannelIndex);

extern FUNC(Std_ReturnType, NM_CODE) Nm_IntDetReportError(
  uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);


#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
