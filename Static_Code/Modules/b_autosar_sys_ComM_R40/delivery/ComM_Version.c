/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: ComM_Version.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
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
** Revision  Date          By          Description                            **
********************************************************************************
** 1.9.3     12-Aug-2020   Jongsun Lim #21439, #25552                         **
** 1.9.0     22-Aug-2019   JS Lim      #18922                                 **
** 1.8.0     23-Oct-2018   JS Lim      #13653                                 **
** 1.0.0     17-Dec-2012   Daejun Park Initial version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM_PCTypes.h"         /* ComM Pre Compile Types header file */
#include "ComM_Version.h"         /* Version info header file */
#include "Dcm.h"                  /* Dcm header file to get version info */
#include "BswM.h"                 /* BswM header file to get version info */
#if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
#include "Nm.h"                   /* Nm header file to get version info */
#endif
#if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)
#include "NvM.h"                  /* NvM header file to get version info */
#endif
#include "Rte.h"                  /* Rte header file to get version info */
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#include "Com.h"                  /* Com header file to get version info */
#endif
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define COMM_VERSION_C_AR_RELEASE_MAJOR_VERSION    4
#define COMM_VERSION_C_AR_RELEASE_MINOR_VERSION    0
#define COMM_VERSION_C_AR_RELEASE_REVISION_VERSION 3

/* Software Version Information */
#define COMM_VERSION_C_SW_MAJOR_VERSION            1
#define COMM_VERSION_C_SW_MINOR_VERSION            10

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if(COMM_VERSION_AR_RELEASE_MAJOR_VERSION != \
  COMM_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "ComM_Version.c : Mismatch in Specification Major Version"
#endif
#if(COMM_VERSION_AR_RELEASE_MINOR_VERSION != \
  COMM_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "ComM_Version.c : Mismatch in Specification Minor Version"
#endif
#if(COMM_VERSION_AR_RELEASE_REVISION_VERSION != \
  COMM_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "ComM_Version.c : Mismatch in Specification Revision Version"
#endif
#if(COMM_VERSION_SW_MAJOR_VERSION != COMM_VERSION_C_SW_MAJOR_VERSION)
  #error "ComM_Version.c : Mismatch in Major Version"
#endif
#if(COMM_VERSION_SW_MINOR_VERSION != COMM_VERSION_C_SW_MINOR_VERSION)
  #error "ComM_Version.c : Mismatch in Minor Version"
#endif

/* Dcm AUTOSAR Specification Version Information */
#if(DCM_AR_RELEASE_MAJOR_VERSION != COMM_DCM_AR_RELEASE_MAJOR_VERSION)
  #error "Dcm.h : Mismatch in Specification Major Version"
#endif
#if(DCM_AR_RELEASE_MINOR_VERSION != COMM_DCM_AR_RELEASE_MINOR_VERSION)
  #error "Dcm.h : Mismatch in Specification Minor Version"
#endif

#if((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) || \
    (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
/* Nm AUTOSAR Specification Version Information */
#if(NM_AR_RELEASE_MAJOR_VERSION != COMM_NM_AR_RELEASE_MAJOR_VERSION)
  #error "Nm.h : Mismatch in Specification Major Version"
#endif
#if(NM_AR_RELEASE_MINOR_VERSION != COMM_NM_AR_RELEASE_MINOR_VERSION)
  #error "Nm.h : Mismatch in Specification Minor Version"
#endif
#endif

/* NvM AUTOSAR Specification Version Information */
#if(COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)
#if(NVM_AR_RELEASE_MAJOR_VERSION != COMM_NVM_AR_RELEASE_MAJOR_VERSION)
  #error "NvM.h : Mismatch in Specification Major Version"
#endif
#if(NVM_AR_RELEASE_MINOR_VERSION != COMM_NVM_AR_RELEASE_MINOR_VERSION)
  #error "NvM.h : Mismatch in Specification Minor Version"
#endif
#endif

/* Rte AUTOSAR Specification Version Information */
#if(RTE_AR_RELEASE_MAJOR_VERSION != COMM_RTE_AR_RELEASE_MAJOR_VERSION)
  #error "Rte.h : Mismatch in Specification Major Version"
#endif
#if(RTE_AR_RELEASE_MINOR_VERSION != COMM_RTE_AR_RELEASE_MINOR_VERSION)
  #error "Rte.h : Mismatch in Specification Minor Version"
#endif

/* CanSM AUTOSAR Specification Version Information */
#if(COMM_CANNETWORK_PRESENT == STD_ON)

#if(CANSM_AR_RELEASE_MAJOR_VERSION != COMM_CANSM_AR_RELEASE_MAJOR_VERSION)
  #error "CanSM.h : Mismatch in Specification Major Version"
#endif
#if(CANSM_AR_RELEASE_MINOR_VERSION != COMM_CANSM_AR_RELEASE_MINOR_VERSION)
  #error "CanSM.h : Mismatch in Specification Minor Version"
#endif

#endif

/* FrSM AUTOSAR Specification Version Information */
#if(COMM_FRNETWORK_PRESENT == STD_ON)

#if(FRSM_AR_RELEASE_MAJOR_VERSION != COMM_FRSM_AR_RELEASE_MAJOR_VERSION)
  #error "FrSM.h : Mismatch in Specification Major Version"
#endif
#if(FRSM_AR_RELEASE_MINOR_VERSION != COMM_FRSM_AR_RELEASE_MINOR_VERSION)
  #error "FrSM.h : Mismatch in Specification Minor Version"
#endif

#endif

/* LinSM AUTOSAR Specification Version Information */
#if(COMM_LINNETWORK_PRESENT == STD_ON)

#if(LINSM_AR_RELEASE_MAJOR_VERSION != COMM_LINSM_AR_RELEASE_MAJOR_VERSION)
  #error "LinSM.h : Mismatch in Specification Major Version"
#endif
#if(LINSM_AR_RELEASE_MINOR_VERSION != COMM_LINSM_AR_RELEASE_MINOR_VERSION)
  #error "LinSM.h : Mismatch in Specification Minor Version"
#endif

#endif

/* EthSM AUTOSAR Specification Version Information */
#if(COMM_ETHNETWORK_PRESENT == STD_ON)

#if(ETHSM_AR_RELEASE_MAJOR_VERSION != COMM_ETHSM_AR_RELEASE_MAJOR_VERSION)
  #error "EthSM.h : Mismatch in Specification Major Version"
#endif
#if(ETHSM_AR_RELEASE_MINOR_VERSION > COMM_ETHSM_AR_RELEASE_MINOR_VERSION_H)
  #error "EthSM.h : Mismatch in Specification Minor Version"
#endif
#if(ETHSM_AR_RELEASE_MINOR_VERSION < COMM_ETHSM_AR_RELEASE_MINOR_VERSION_L)
  #error "EthSM.h : Mismatch in Specification Minor Version"
#endif

#endif

/* Det AUTOSAR Specification Version Information */
#if(COMM_DEV_ERROR_DETECT == STD_ON)

#if(DET_AR_RELEASE_MAJOR_VERSION != COMM_DET_AR_RELEASE_MAJOR_VERSION)
  #error "Det.h : Mismatch in Specification Major Version"
#endif
#if(DET_AR_RELEASE_MINOR_VERSION != COMM_DET_AR_RELEASE_MINOR_VERSION)
  #error "Det.h : Mismatch in Specification Minor Version"
#endif

#endif

/* BswM AUTOSAR Specification Version Information*/
#if(BSWM_AR_RELEASE_MAJOR_VERSION != COMM_BSWM_AR_RELEASE_MAJOR_VERSION)
  #error "BswM.h : Mismatch in Specification Major Version"
#endif
#if(BSWM_AR_RELEASE_MINOR_VERSION != COMM_BSWM_AR_RELEASE_MINOR_VERSION)
  #error "BswM.h : Mismatch in Specification Minor Version"
#endif

/* Com AUTOSAR Specification Version Information*/
#if((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
    (COMM_ETHNETWORK_PRESENT == STD_ON))
#if(COM_AR_RELEASE_MAJOR_VERSION != COMM_COM_AR_RELEASE_MAJOR_VERSION)
  #error "Com.h : Mismatch in Specification Major Version"
#endif
#if(COM_AR_RELEASE_MINOR_VERSION != COMM_COM_AR_RELEASE_MINOR_VERSION)
  #error "Com.h : Mismatch in Specification Minor Version"
#endif
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

