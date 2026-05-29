/*******************************************************************************
**                                                                            **
**  (C) 2017 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Csm_Version.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Watchdog Manager Module                               **
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
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     27-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_Version.h"      /* Csm version header file */
#include "Csm.h"              /* Csm module header file */

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* Csm version check */
#if (CSM_AR_RELEASE_MAJOR_VERSION != CSM_VERSION_AR_RELEASE_MAJOR_VERSION)
  #error "Csm.h : Mismatch in Specification Major Version"
#endif
#if (CSM_AR_RELEASE_MINOR_VERSION != CSM_VERSION_AR_RELEASE_MINOR_VERSION)
  #error "Csm.h : Mismatch in Specification Minor Version"
#endif
#if (CSM_AR_RELEASE_REVISION_VERSION != CSM_VERSION_AR_RELEASE_REVISION_VERSION)
  #error "Csm.h : Mismatch in Specification Revision Version"
#endif
#if (CSM_SW_MAJOR_VERSION != CSM_VERSION_SW_MAJOR_VERSION)
  #error "Csm.h : Mismatch in Software Major Version"
#endif
#if (CSM_SW_MINOR_VERSION != CSM_VERSION_SW_MINOR_VERSION)
  #error "Csm.h : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
