/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_Ram.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of RAM area.                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 2.6.0     03-Nov-2020   HM Shin     #24937                                 **
** 2.4.0     06-Sep-2019   HM Shin     #18909                                 **
** 2.3.0     22-Aug-2019   JS Lim      #18336                                 **
** 2.2.0     01-Feb-2017   Chan Kim    Redmine #6922                          **
** 2.1.0     17-Jun-2016   Chan Kim    Redmine #5190                          **
** 2.0.0     11-Aug-2015   Chan Kim    Redmine #2949                          **
** 1.0.0     29-Apr-2013   Autoever      Initial Version                        **
*******************************************************************************/

#ifndef PDUR_RAM_H
#define PDUR_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComStack_Types.h"       /* Com Stack Types header file */
#include "PduR_Cfg.h"
#include "PduR_PCTypes.h"


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define PDUR_RAM_AR_RELEASE_MAJOR_VERSION     4
#define PDUR_RAM_AR_RELEASE_MINOR_VERSION     0
#define PDUR_RAM_AR_RELEASE_REVISION_VERSION  3

/* Software Version Information */
#define PDUR_RAM_SW_MAJOR_VERSION            2
#define PDUR_RAM_SW_MINOR_VERSION            9
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
/* Global variable to store initialization status of PduR Module */
extern VAR(boolean, PDUR_VAR) PduR_GblInitStatus;
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */

#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(uint8, PDUR_VAR) PduR_GaaRoutingPathGroupRam[PDUR_ROUTINGPATH_GROUP_ARRAY_SIZE];
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#endif /* PDUR_RAM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
