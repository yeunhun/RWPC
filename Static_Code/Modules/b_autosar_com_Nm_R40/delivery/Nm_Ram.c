/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Nm_Ram.c                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : This file provides definitions of global variables used in    **
**              the module                                                    **
**                                                                            **
**  PURPOSE   : Global Ram variables of Nm Interface                          **
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
** 1.0.2     17-May-2016   Kt Kim        #4641                                **
** 1.0.0     26-Nov-2012   Kt Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Nm.h" /* For inclusion of Nm Header file */
#include "Nm_Ram.h" /* Module RAM header */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define NM_RAM_C_AR_RELEASE_MAJOR_VERSION     (4)
#define NM_RAM_C_AR_RELEASE_MINOR_VERSION     (0)
#define NM_RAM_C_AR_RELEASE_REVISION_VERSION  (3)

/* Software Version Information */
#define NM_RAM_C_SW_MAJOR_VERSION  (2)
#define NM_RAM_C_SW_MINOR_VERSION  (3)

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (NM_RAM_AR_RELEASE_MAJOR_VERSION != NM_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Nm_Ram.c : Mismatch in Specification Major Version"
#endif

#if (NM_RAM_AR_RELEASE_MINOR_VERSION != NM_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Nm_Ram.c : Mismatch in Specification Minor Version"
#endif

#if (NM_RAM_AR_RELEASE_REVISION_VERSION != NM_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Nm_Ram.c : Mismatch in Specification Patch Version"
#endif

#if (NM_RAM_SW_MAJOR_VERSION != NM_RAM_C_SW_MAJOR_VERSION)
   #error "Nm_Ram.c : Mismatch in Software Major Version"
#endif

#if (NM_RAM_SW_MINOR_VERSION != NM_RAM_C_SW_MINOR_VERSION)
   #error "Nm_Ram.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define NM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store status of Nm Module */
VAR (boolean, NM_VAR_POWER_ON_INIT) Nm_GblInitStatus;
#define NM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
