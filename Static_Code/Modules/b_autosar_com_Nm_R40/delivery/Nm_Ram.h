/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Nm_Ram.h                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm Module                                             **
**                                                                            **
**  PURPOSE   : Provision of header file for Nm_Ram.c                         **
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
** 1.0.0     26-Nov-2012   Kt Kim        Initial version                      **
*******************************************************************************/
#ifndef NM_RAM_H
#define NM_RAM_H
/*******************************************************************************
**                       Include Section                                      **
*******************************************************************************/
#include "Std_Types.h" /* For inclusion of Boolean and compiler specific type */
#include "Nm_Cfg.h" /* For inclusion Nm_Cfg.h file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define NM_RAM_AR_RELEASE_MAJOR_VERSION     (4)
#define NM_RAM_AR_RELEASE_MINOR_VERSION     (0)
#define NM_RAM_AR_RELEASE_REVISION_VERSION  (3)

/* Nm software version information */
#define NM_RAM_SW_MAJOR_VERSION    (2)
#define NM_RAM_SW_MINOR_VERSION    (3)

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* Extern definitions */
#define NM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store status of Nm Module */
extern VAR (boolean, NM_VAR_POWER_ON_INIT) Nm_GblInitStatus;
#define NM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
#endif /* NM_RAM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
