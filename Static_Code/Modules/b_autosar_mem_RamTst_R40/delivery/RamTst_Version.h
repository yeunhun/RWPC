/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_Version.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR RAM Test                                              **
**                                                                            **
**  PURPOSE   : C header for RamTst_Version                                   **
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
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/

#ifndef RAMTST_VERSION_H
#define RAMTST_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "RamTst.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define RAMTST_VERSION_AR_RELEASE_MAJOR_VERSION RAMTST_AR_RELEASE_MAJOR_VERSION
#define RAMTST_VERSION_AR_RELEASE_MINOR_VERSION RAMTST_AR_RELEASE_MINOR_VERSION
#define RAMTST_VERSION_AR_RELEASE_REVISION_VERSION \
  RAMTST_AR_RELEASE_REVISION_VERSION

/* RamTst Software Version Information */
#define RAMTST_VERSION_SW_MAJOR_VERSION RAMTST_SW_MAJOR_VERSION
#define RAMTST_VERSION_SW_MINOR_VERSION RAMTST_SW_MINOR_VERSION

/* Det Software Version Information */
#if(RAMTST_DEV_ERROR_DETECT == STD_ON)
#define RAMTST_DET_AR_RELEASE_MAJOR_VERSION 4
#define RAMTST_DET_AR_RELEASE_MINOR_VERSION 0
#endif

#endif /* RAMTST_VERSION_H */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
