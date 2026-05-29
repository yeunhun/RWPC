/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Wdg_76_Acw_Version.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTRON CUSTOM WDG                                     **
**                                                                            **
**  PURPOSE   : Header for Wdg_76_Acw_Version.c                               **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.8.2.0   18-Oct-2021   YH.Han       Redmine #32698                        **
** 1.5.0     25-Apr-2019   YH.Han       Redmine #16478                        **
** 1.0.1     28-Apr-2016   Sinil        Redmine #4744                         **
** 1.0.0     02-Feb-2015   Sinil        Initial version                       **
*******************************************************************************/

#ifndef WDG_76_ACW_VERSION_H
#define WDG_76_ACW_VERSION_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw_Cfg.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define WDG_76_ACW_VERSION_AR_RELEASE_MAJOR_VERSION    WDG_76_ACW_AR_RELEASE_MAJOR_VERSION
#define WDG_76_ACW_VERSION_AR_RELEASE_MINOR_VERSION    WDG_76_ACW_AR_RELEASE_MINOR_VERSION
#define WDG_76_ACW_VERSION_AR_RELEASE_REVISION_VERSION WDG_76_ACW_AR_RELEASE_REVISION_VERSION

/* Software Version Information */
#define WDG_76_ACW_VERSION_SW_MAJOR_VERSION     WDG_76_ACW_SW_MAJOR_VERSION
#define WDG_76_ACW_VERSION_SW_MINOR_VERSION     WDG_76_ACW_SW_MINOR_VERSION
#define WDG_76_ACW_VERSION_SW_PATCH_VERSION     WDG_76_ACW_SW_PATCH_VERSION

/*Version information of Det module */
#define WDG_76_ACW_DET_AR_RELEASE_MAJOR_VERSION          4
#define WDG_76_ACW_DET_AR_RELEASE_MINOR_VERSION          0

/*Version information of Dem module */
#define WDG_76_ACW_DEM_AR_RELEASE_MAJOR_VERSION          4
#define WDG_76_ACW_DEM_AR_RELEASE_MINOR_VERSION          0

/*Version information of Dio module */
#define WDG_76_ACW_DIO_AR_RELEASE_MAJOR_VERSION          4
#define WDG_76_ACW_DIO_AR_RELEASE_MINOR_VERSION_L        0
#define WDG_76_ACW_DIO_AR_RELEASE_MINOR_VERSION_U        4

/* polyspace-begin MISRA-C3:2.5 [Not a Defect] 
                              "macro is used according to user configuration" */
/*Version information of Spi module */
#define WDG_76_ACW_SPI_AR_RELEASE_MAJOR_VERSION          4
#define WDG_76_ACW_SPI_AR_RELEASE_MINOR_VERSION          0
/* polyspace-end<MISRA-C3:2.5 */

/*Version information of Gpt module */
#define WDG_76_ACW_GPT_AR_RELEASE_MAJOR_VERSION          4
#define WDG_76_ACW_GPT_AR_RELEASE_MINOR_VERSION_L        0
#define WDG_76_ACW_GPT_AR_RELEASE_MINOR_VERSION_U        4

#endif /* WDG_76_ACW_VERSION_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
