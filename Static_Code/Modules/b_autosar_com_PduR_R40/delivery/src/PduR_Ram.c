/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTOEVER Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: PduR_Ram.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Provision of Initialization of RAM area.                      **
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
** 2.0.3     24-Nov-2015   Chan Kim    Redmine #3545, #4519                   **
** 2.0.0     11-Aug-2015   Chan Kim    Redmine #2949                          **
** 1.0.0     29-Apr-2013   Autoever      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "PduR.h"                         /* PDU Router RAM header */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define PDUR_RAM_C_AR_RELEASE_MAJOR_VERSION     4
#define PDUR_RAM_C_AR_RELEASE_MINOR_VERSION     0
#define PDUR_RAM_C_AR_RELEASE_REVISION_VERSION  3

/* Software Version Information */
#define PDUR_RAM_C_SW_MAJOR_VERSION            2
#define PDUR_RAM_C_SW_MINOR_VERSION            9
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (PDUR_RAM_AR_RELEASE_MAJOR_VERSION != PDUR_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "PduR_Ram.c : Mismatch in Specification  Major Version"
#endif
#if (PDUR_RAM_AR_RELEASE_MINOR_VERSION != PDUR_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "PduR_Ram.c : Mismatch in Specification  Minor Version"
#endif
#if (PDUR_RAM_AR_RELEASE_REVISION_VERSION != \
  PDUR_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "PduR_Ram.c : Mismatch in Specification Revision Version"
#endif
#if (PDUR_RAM_SW_MAJOR_VERSION != PDUR_RAM_C_SW_MAJOR_VERSION)
  #error "PduR_Ram.c : Mismatch in Software Major Version"
#endif
#if (PDUR_RAM_SW_MINOR_VERSION != PDUR_RAM_C_SW_MINOR_VERSION)
  #error "PduR_Ram.c : Mismatch in Software Minor Version"
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store initialization status of PduR Module */
VAR(boolean, PDUR_VAR) PduR_GblInitStatus;
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */

#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
#define PDUR_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
VAR(uint8, PDUR_VAR) PduR_GaaRoutingPathGroupRam[PDUR_ROUTINGPATH_GROUP_ARRAY_SIZE];
#define PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
