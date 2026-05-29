/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_Version.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM                                                   **
**                                                                            **
**  PURPOSE   : C header for NvM_Version                                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date           By          Description                         **
********************************************************************************
** 1.5.1       30-Dec-2020   Yun YJ       Redmine #27374                      **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/
#ifndef NVM_VERSION_H
#define NVM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM_Cfg.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR SPECIFICATION VERSION */
#define NVM_VERSION_AR_RELEASE_MAJOR_VERSION     NVM_AR_RELEASE_MAJOR_VERSION
#define NVM_VERSION_AR_RELEASE_MINOR_VERSION     NVM_AR_RELEASE_MINOR_VERSION
#define NVM_VERSION_AR_RELEASE_REVISION_VERSION  NVM_AR_RELEASE_REVISION_VERSION

/* SOFTWARE VERSION INFORMATION */
#define NVM_VERSION_SW_MAJOR_VERSION        NVM_SW_MAJOR_VERSION
#define NVM_VERSION_SW_MINOR_VERSION        NVM_SW_MINOR_VERSION

#if(NVM_DEV_ERROR_DETECT == STD_ON)
#define NVM_DET_AR_RELEASE_MAJOR_VERSION            4
#define NVM_DET_AR_RELEASE_MINOR_VERSION            0
#endif

#define NVM_RTE_AR_RELEASE_MAJOR_VERSION           4
#define NVM_RTE_AR_RELEASE_MINOR_VERSION           0

#if(NVM_DEMERROR_REPORT == STD_ON)
#define NVM_DEM_AR_RELEASE_MAJOR_VERSION           4
#define NVM_DEM_AR_RELEASE_MINOR_VERSION           0
#endif

#define NVM_MEMIF_AR_RELEASE_MAJOR_VERSION         4
#define NVM_MEMIF_AR_RELEASE_MINOR_VERSION         0

#define NVM_ECUM_AR_RELEASE_MAJOR_VERSION         4
#define NVM_ECUM_AR_RELEASE_MINOR_VERSION         0

#if(NVM_CRC_SUPPORT == STD_ON)
#define NVM_CRC_AR_RELEASE_MAJOR_VERSION           4
#define NVM_CRC_AR_RELEASE_MINOR_VERSION           0
#endif

#endif /* NVM_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
