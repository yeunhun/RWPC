/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_Version.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of Version Check                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
*******************************************************************************/

/*******************************************************************************
** Revision  Date          By              Description                        **
********************************************************************************
** 3.0.0    08-Nov-2021    Sj.Kim    #32882                                   **
** 2.7.0    07-Oct-2020    Sj.Kim    #25877                                   **
** 2.6.0    22-Aug-2019    Js.Lim    #18384                                   **
** 2.5.0    06-Dec-2016    Js.Lim    #7077                                    **
** 1.0.1    13-Jun-2016    Kt.Kim    #5139                                    **
** 1.0.0    30-Jan-2013    Kt.Kim    Initial version                          **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"                /* CAN Interface Module Header File */
#include "CanIf_Version.h"        /* CanIf Version Header File */
#include "SchM_CanIf.h"           /* SchM CanIf Header file */
#include "CanSM.h"                /* CanSM header file */
#if (STD_ON == CANIF_PDUR_CALLBACK)
#include "PduR.h"                 /* PduR header file */
#endif
#if (STD_ON == CANIF_CANTP_CALLBACK)
#include "CanTp.h"                /* CanTp header file */
#endif
#if (STD_ON == CANIF_CANNM_CALLBACK)
#include "CanNm.h"                /* CanNm header file */
#endif
#if (STD_ON == CANIF_WAKEUP_SUPPORT)
#include "EcuM.h"                 /* EcuM header file */
#endif
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#include "Det.h"                  /* Det header file */
#include "CanIf_Error.h"
#endif
#if (STD_OFF == CANIF_MULTIPLE_CANDRV_SUPPORT)
#include "CanIf_Can.h"            /* Can header file */
#endif
#if ((STD_ON == CANIF_CANTRCV_SUPPORT) && \
                                    (STD_OFF == CANIF_MULTIPLE_TRCVDRV_SUPPORT))
#include "CanIf_CanTrcv.h"        /* CanTrcv header file */
#endif
#if ((STD_ON == CANIF_RX_J1939TP_CALLBACK) || \
                                          (STD_ON == CANIF_TX_J1939TP_CALLBACK))
#include "J1939Tp.h"                /* J1939Tp header file */
#endif
#if ((STD_ON == CANIF_RX_XCP_CALLBACK) || (STD_ON == CANIF_TX_XCP_CALLBACK))
#include "Xcp.h"                /* J1939Tp header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_VERSION_C_AR_RELEASE_MAJOR_VERSION     4
#define CANIF_VERSION_C_AR_RELEASE_MINOR_VERSION     0
#define CANIF_VERSION_C_AR_RELEASE_REVISION_VERSION  3

/* Software Version Information */
#define CANIF_VERSION_C_SW_MAJOR_VERSION  3
#define CANIF_VERSION_C_SW_MINOR_VERSION  0
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (CANIF_VERSION_AR_RELEASE_MAJOR_VERSION != \
  CANIF_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "CanIf_Version.c : Mismatch in Specification Major Version"
#endif

#if (CANIF_VERSION_AR_RELEASE_MINOR_VERSION != \
  CANIF_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "CanIf_Version.c : Mismatch in Specification Minor Version"
#endif

#if (CANIF_VERSION_AR_RELEASE_REVISION_VERSION != \
  CANIF_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "CanIf_Version.c : Mismatch in Specification Revision Version"
#endif

#if (CANIF_VERSION_SW_MAJOR_VERSION != CANIF_VERSION_C_SW_MAJOR_VERSION)
  #error "CanIf_Version.c : Mismatch in Major Version"
#endif

#if (CANIF_VERSION_SW_MINOR_VERSION != CANIF_VERSION_C_SW_MINOR_VERSION)
  #error "CanIf_Version.c : Mismatch in Minor Version"
#endif

#if (STD_ON == CANIF_PDUR_CALLBACK)
#if (PDUR_AR_RELEASE_MAJOR_VERSION != CANIF_PDUR_AR_RELEASE_MAJOR_VERSION)
  #error "PduR.h : Mismatch in Specification Major Version"
#endif

#if (PDUR_AR_RELEASE_MINOR_VERSION != CANIF_PDUR_AR_RELEASE_MINOR_VERSION)
  #error "PduR.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (STD_ON == CANIF_CANTP_CALLBACK)
#if (CANTP_AR_RELEASE_MAJOR_VERSION != CANIF_CANTP_AR_RELEASE_MAJOR_VERSION)
  #error "CanTp.h : Mismatch in Specification Major Version"
#endif

#if (CANTP_AR_RELEASE_MINOR_VERSION != CANIF_CANTP_AR_RELEASE_MINOR_VERSION)
  #error "CanTp.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (STD_ON == CANIF_TX_XCP_CALLBACK)
#if (XCP_AR_RELEASE_MAJOR_VERSION != CANIF_XCP_AR_RELEASE_MAJOR_VERSION)
  #error "Xcp.h : Mismatch in Specification Major Version"
#endif

#if (XCP_AR_RELEASE_MINOR_VERSION != CANIF_XCP_AR_RELEASE_MINOR_VERSION)
  #error "Xcp.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (STD_ON == CANIF_TX_J1939TP_CALLBACK)
#if (J1939TP_AR_RELEASE_MAJOR_VERSION != CANIF_J1939TP_AR_RELEASE_MAJOR_VERSION)
  #error "J1939TP.h : Mismatch in Specification Major Version"
#endif

#if (J1939TP_AR_RELEASE_MINOR_VERSION != CANIF_J1939TP_AR_RELEASE_MINOR_VERSION)
  #error "J1939TP.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (STD_ON == CANIF_TX_CANNM_CALLBACK)
#if (CANNM_AR_RELEASE_MAJOR_VERSION != CANIF_CANNM_AR_RELEASE_MAJOR_VERSION)
  #error "CanNm.h : Mismatch in Specification Major Version"
#endif

#if (CANNM_AR_RELEASE_MINOR_VERSION != CANIF_CANNM_AR_RELEASE_MINOR_VERSION)
  #error "CanNm.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (STD_ON == CANIF_WAKEUP_SUPPORT)
#if (ECUM_AR_RELEASE_MAJOR_VERSION != CANIF_ECUM_AR_RELEASE_MAJOR_VERSION)
  #error "EcuM.h : Mismatch in Specification Major Version"
#endif

#if (ECUM_AR_RELEASE_MINOR_VERSION != CANIF_ECUM_AR_RELEASE_MINOR_VERSION)
  #error "EcuM.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (CANSM_AR_RELEASE_MAJOR_VERSION != CANIF_CANSM_AR_RELEASE_MAJOR_VERSION)
  #error "CanSM.h : Mismatch in Specification Major Version"
#endif

#if (CANSM_AR_RELEASE_MINOR_VERSION != CANIF_CANSM_AR_RELEASE_MINOR_VERSION)
  #error "CanSM.h : Mismatch in Specification Minor Version"
#endif

#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#if (DET_AR_RELEASE_MAJOR_VERSION != CANIF_DET_AR_RELEASE_MAJOR_VERSION)
  #error "Det.h : Mismatch in Specification Major Version"
#endif

#if (DET_AR_RELEASE_MINOR_VERSION != CANIF_DET_AR_RELEASE_MINOR_VERSION)
  #error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif

#if (STD_OFF == CANIF_MULTIPLE_CANDRV_SUPPORT)
#if (CAN_AR_RELEASE_MAJOR_VERSION != CANIF_CAN_AR_RELEASE_MAJOR_VERSION)
  #error "Can.h : Mismatch in Specification Major Version"
#endif

#if (CAN_AR_RELEASE_MINOR_VERSION != CANIF_CAN_AR_RELEASE_MINOR_VERSION)
  #error "Can.h : Mismatch in Specification Minor Version"
#endif
#endif

#if ((STD_ON == CANIF_CANTRCV_SUPPORT) && \
  (STD_OFF == CANIF_MULTIPLE_TRCVDRV_SUPPORT))
#if (CANTRCV_AR_RELEASE_MAJOR_VERSION != CANIF_CANTRCV_AR_RELEASE_MAJOR_VERSION)
  #error "CanTrcv.h : Mismatch in Specification Major Version"
#endif

#if (CANTRCV_AR_RELEASE_MINOR_VERSION != CANIF_CANTRCV_AR_RELEASE_MINOR_VERSION)
  #error "CanTrcv.h : Mismatch in Specification Minor Version"
#endif
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
