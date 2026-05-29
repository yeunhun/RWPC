/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_Version.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR RAM Test                                              **
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
** Revision  Date          By     Description                                 **
********************************************************************************
** 1.2.4     28-Dec-2018   YJ Yun           Redmine #15207                    **
** 1.2.5     16-May-2016   CY Song          RedMine #4902                     **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst_Version.h"
#if (RAMTST_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"            /* Det header*/
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define RAMTST_VERSION_C_AR_RELEASE_MAJOR_VERSION     4
#define RAMTST_VERSION_C_AR_RELEASE_MINOR_VERSION     0
#define RAMTST_VERSION_C_AR_RELEASE_REVISION_VERSION  3

/* Software Version Information */
#define RAMTST_VERSION_C_SW_MAJOR_VERSION  1
#define RAMTST_VERSION_C_SW_MINOR_VERSION  3

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if(RAMTST_VERSION_AR_RELEASE_MAJOR_VERSION != \
  RAMTST_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "RamTst_Version.c : Mismatch in Specification Major Version"
#endif
#if(RAMTST_VERSION_AR_RELEASE_MINOR_VERSION != \
  RAMTST_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "RamTst_Version.c : Mismatch in Specification Minor Version"
#endif
#if(RAMTST_VERSION_AR_RELEASE_REVISION_VERSION != \
  RAMTST_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "RamTst_Version.c : Mismatch in Specification Revision Version"
#endif

#if(RAMTST_VERSION_SW_MAJOR_VERSION != RAMTST_VERSION_C_SW_MAJOR_VERSION)
  #error "RamTst_Version.c : Mismatch in Major Version"
#endif
#if(RAMTST_VERSION_SW_MINOR_VERSION != RAMTST_VERSION_C_SW_MINOR_VERSION)
  #error "RamTst_Version.c : Mismatch in Minor Version"
#endif

/* Det AUTOSAR Specification Version Information */
#if(RAMTST_DEV_ERROR_DETECT == STD_ON)
#if(DET_AR_RELEASE_MAJOR_VERSION != RAMTST_DET_AR_RELEASE_MAJOR_VERSION)
  #error "Det.h : Mismatch in Specification Major Version"
#endif
#if(DET_AR_RELEASE_MINOR_VERSION != RAMTST_DET_AR_RELEASE_MINOR_VERSION)
  #error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
