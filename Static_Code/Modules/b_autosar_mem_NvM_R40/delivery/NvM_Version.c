/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: NvM_Version.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM                                                   **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
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
** 1.3.1       21-Sep-2016   Song CY      Redmine #6058                       **
** 1.1.0     18-Apr-2014   Song CY     RedMine718 Version is updated          **
** 1.0.0       25-Jan-2013    CY Song     Initial version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM_Version.h"             /* NvM Version Header File */
#if(NVM_DEMERROR_REPORT == STD_ON)
#include "NvM_Dem_Cfg.h"                            /* Dem header file */
#endif

#include "MemIf.h"                   /* MemIf header file */

#if(NVM_CRC_SUPPORT == STD_ON)
#include "Crc.h"                     /* Crc header file */
#endif

#if(NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                     /* Det header file */
#endif

#include "Rte.h"                     /* Rte header file */
#include "EcuM.h"                    /* EcuM header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR SPECIFICATION VERSION INFORMATION */
#define NVM_VERSION_C_AR_RELEASE_MAJOR_VERSION     4
#define NVM_VERSION_C_AR_RELEASE_MINOR_VERSION     0
#define NVM_VERSION_C_AR_RELEASE_REVISION_VERSION  3

/* FILE VERSION INFORMATION */
#define NVM_VERSION_C_SW_MAJOR_VERSION  1
#define NVM_VERSION_C_SW_MINOR_VERSION  5

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (NVM_VERSION_AR_RELEASE_MAJOR_VERSION != \
  NVM_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "NvM.c : Mismatch in Specification Major Version"
#endif

#if (NVM_VERSION_AR_RELEASE_MINOR_VERSION != \
  NVM_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "NvM.c : Mismatch in Specification Minor Version"
#endif

#if (NVM_VERSION_AR_RELEASE_REVISION_VERSION != \
  NVM_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "NvM.c : Mismatch in Specification Revision Version"
#endif

#if (NVM_VERSION_SW_MAJOR_VERSION != NVM_VERSION_C_SW_MAJOR_VERSION)
  #error "NvM.c : Mismatch in Software Major Version"
#endif

#if (NVM_VERSION_SW_MINOR_VERSION != NVM_VERSION_C_SW_MINOR_VERSION)
  #error "NvM.c : Mismatch in Software Minor Version"
#endif

#if (NVM_DEV_ERROR_DETECT == STD_ON)
#if (DET_AR_RELEASE_MAJOR_VERSION != NVM_DET_AR_RELEASE_MAJOR_VERSION)
  #error "Det.h : Mismatch in Specification Major Version"
#endif

#if (DET_AR_RELEASE_MINOR_VERSION != NVM_DET_AR_RELEASE_MINOR_VERSION)
  #error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif

#if(NVM_DEMERROR_REPORT == STD_ON)
#if (DEM_AR_RELEASE_MAJOR_VERSION != NVM_DEM_AR_RELEASE_MAJOR_VERSION)
  #error "Dem.h : Mismatch in Specification Major Version"
#endif

#if (DEM_AR_RELEASE_MINOR_VERSION != NVM_DEM_AR_RELEASE_MINOR_VERSION)
  #error "Dem.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (RTE_AR_RELEASE_MAJOR_VERSION != NVM_RTE_AR_RELEASE_MAJOR_VERSION)
  #error "Rte.h : Mismatch in Specification Major Version"
#endif

#if (RTE_AR_RELEASE_MINOR_VERSION != NVM_RTE_AR_RELEASE_MINOR_VERSION)
  #error "Rte.h : Mismatch in Specification Minor Version"
#endif

#if (MEMIF_AR_RELEASE_MAJOR_VERSION != NVM_MEMIF_AR_RELEASE_MAJOR_VERSION)
  #error "Memif.h : Mismatch in Specification Major Version"
#endif

#if (MEMIF_AR_RELEASE_MINOR_VERSION != NVM_MEMIF_AR_RELEASE_MINOR_VERSION)
  #error "Memif.h : Mismatch in Specification Minor Version"
#endif

#if (ECUM_AR_RELEASE_MAJOR_VERSION != NVM_ECUM_AR_RELEASE_MAJOR_VERSION)
  #error "EcuM.h : Mismatch in Specification Major Version"
#endif

#if (ECUM_AR_RELEASE_MINOR_VERSION != NVM_ECUM_AR_RELEASE_MINOR_VERSION)
  #error "EcuM.h : Mismatch in Specification Minor Version"
#endif

#if (NVM_CRC_SUPPORT == STD_ON)
#if (CRC_AR_RELEASE_MAJOR_VERSION != NVM_CRC_AR_RELEASE_MAJOR_VERSION)
  #error "Crc.h : Mismatch in Specification Major Version"
#endif

#if (CRC_AR_RELEASE_MINOR_VERSION != NVM_CRC_AR_RELEASE_MINOR_VERSION)
  #error "Crc.h : Mismatch in Specification Minor Version"
#endif
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
