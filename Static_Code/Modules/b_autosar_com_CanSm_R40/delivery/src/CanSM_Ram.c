/*******************************************************************************
**  (C) 2021 HYUNDAI  AUTOEVER Co., Ltd.								                      **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanSM_Ram.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of initialization of RAM area.                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.12.0    17-Jun-2019   SM Kwon        #17202                              **
** 1.11.0    23-Oct-2018   Lim Jong Sun   #14496                              **
** 1.10.0    27-Oct-2016   Lim Jong Sun   #7076                               **
** 1.9.7     19-Jan-2015   Lim Jong Sun   #3905 Mismatch                      **
**                                        CANSM_AR_RELEASE_REVISION_VERSION   **
** 1.9.4     11-Sep-2015   Lim Jong Sun   Fixed MISRA-C Violation             **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM_InternalTypes.h"        /* CanSM PCTypes header file */
#include "CanSM_Ram.h"            /* CanSM_Ram header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANSM_RAM_C_RELEASE_MAJOR_VERSION       4
#define CANSM_RAM_C_RELEASE_MINOR_VERSION       0
#define CANSM_RAM_C_RELEASE_REVISION_VERSION    3

/* CANSM software version information */
#define CANSM_RAM_C_SW_MAJOR_VERSION            1
#define CANSM_RAM_C_SW_MINOR_VERSION            12

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* CanSM version check */
#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANSM_RAM_C_RELEASE_MAJOR_VERSION )
#error "CanSM_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANSM_RAM_C_RELEASE_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANSM_AR_RELEASE_REVISION_VERSION != CANSM_RAM_C_RELEASE_REVISION_VERSION)
#error "CanSM_Version.c : Mismatch in Specification Patch Version"
#endif

#if (CANSM_SW_MAJOR_VERSION != CANSM_RAM_C_SW_MAJOR_VERSION)
#error "CanSM_Version.c : Mismatch in Major Version"
#endif

#if (CANSM_SW_MINOR_VERSION != CANSM_RAM_C_SW_MINOR_VERSION)
#error "CanSM_Version.c : Mismatch in Minor Version"
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#if (STD_ON == CANSM_DEV_ERROR_DETECT)
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* Memmap header file */
/* Global variable to store initialization status of CanSM Module */
VAR(boolean, CAN_VAR) CanSM_GblInitStatus;
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* Memmap header file */
#endif

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */
VAR(Tdd_CanSM_Network, CAN_VAR) CanSM_GaaNetwork[CANSM_NUMBER_OF_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
VAR(uint8, CAN_VAR) CanSm_GucModeReqMax;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* Memmap header file */
VAR(uint16, CAN_VAR) CanSm_GddModeReqRepeatTime;
#define CANSM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global pointer to start address of static network for selected configuration */
P2CONST(Tdd_CanSM_StaticNetwork, AUTOMATIC, CAN_VAR) CanSM_GpStaticNw;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
VAR(uint8, CAN_VAR) CanSm_GucSelectedConfigIdx;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* Memmap header file */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
