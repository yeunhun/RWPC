/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_Version.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : C header for CanIf_Version.c                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By              Description                        **
********************************************************************************
** 3.0.0    08-Nov-2021    Sj.Kim    #32882                                   **
** 2.7.0    07-Oct-2020    Sj.Kim    #25877                                   **
** 2.6.0    22-Aug-2019    Js.Lim    #18384                                   **
** 2.5.0    06-Dec-2016    Js.Lim    #7077                                    **
** 1.0.1    13-Jun-2016    Kt.Kim    #5139                                    **
** 1.0.0    04-Feb-2013    Kt.Kim    Initial version                          **
*******************************************************************************/

#ifndef CANIF_VERSION_H
#define CANIF_VERSION_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
 /* AUTOSAR Specification Version Information */
#define CANIF_VERSION_AR_RELEASE_MAJOR_VERSION            4
#define CANIF_VERSION_AR_RELEASE_MINOR_VERSION            0
#define CANIF_VERSION_AR_RELEASE_REVISION_VERSION         3

/* Software Version Information */
#define CANIF_VERSION_SW_MAJOR_VERSION                    3
#define CANIF_VERSION_SW_MINOR_VERSION                    0

#define CANIF_ECUM_AR_RELEASE_MAJOR_VERSION               4
#define CANIF_ECUM_AR_RELEASE_MINOR_VERSION               0
#define CANIF_ECUM_AR_RELEASE_REVISION_VERSION            3

#define CANIF_CANSM_AR_RELEASE_MAJOR_VERSION              4
#define CANIF_CANSM_AR_RELEASE_MINOR_VERSION              0
#define CANIF_CANSM_AR_RELEASE_REVISION_VERSION           3

#define CANIF_PDUR_AR_RELEASE_MAJOR_VERSION               4
#define CANIF_PDUR_AR_RELEASE_MINOR_VERSION               0
#define CANIF_PDUR_AR_RELEASE_REVISION_VERSION            3

#define CANIF_CANNM_AR_RELEASE_MAJOR_VERSION              4
#define CANIF_CANNM_AR_RELEASE_MINOR_VERSION              0
#define CANIF_CANNM_AR_RELEASE_REVISION_VERSION           3

#define CANIF_CANTP_AR_RELEASE_MAJOR_VERSION              4
#define CANIF_CANTP_AR_RELEASE_MINOR_VERSION              0
#define CANIF_CANTP_AR_RELEASE_REVISION_VERSION           3

#define CANIF_DET_AR_RELEASE_MAJOR_VERSION                4
#define CANIF_DET_AR_RELEASE_MINOR_VERSION                0
#define CANIF_DET_AR_RELEASE_REVISION_VERSION             3

#define CANIF_SCHM_AR_RELEASE_MAJOR_VERSION               4
#define CANIF_SCHM_AR_RELEASE_MINOR_VERSION               0
#define CANIF_SCHM_AR_RELEASE_REVISION_VERSION            3

#if (STD_OFF == CANIF_MULTIPLE_CANDRV_SUPPORT)
#define CANIF_CAN_AR_RELEASE_MAJOR_VERSION   \
                CANIF_CAN_H_AR_RELEASE_MAJOR_VERSION
#define CANIF_CAN_AR_RELEASE_MINOR_VERSION \
                CANIF_CAN_H_AR_RELEASE_MINOR_VERSION
#endif /* #if (STD_OFF == CANIF_MULTIPLE_CANDRV_SUPPORT) */
#define CANIF_CAN_AR_RELEASE_REVISION_VERSION             3

#define CANIF_CANTRCV_AR_RELEASE_MAJOR_VERSION            4
#define CANIF_CANTRCV_AR_RELEASE_MINOR_VERSION            0
#define CANIF_CANTRCV_AR_RELEASE_REVISION_VERSION         3

#define CANIF_XCP_AR_RELEASE_MAJOR_VERSION                4
#define CANIF_XCP_AR_RELEASE_MINOR_VERSION                0
#define CANIF_XCP_AR_RELEASE_REVISION_VERSION             3

#define CANIF_CDD_AR_RELEASE_MAJOR_VERSION                4
#define CANIF_CDD_AR_RELEASE_MINOR_VERSION                0
#define CANIF_CDD_AR_RELEASE_REVISION_VERSION             3

#define CANIF_J1939TP_AR_RELEASE_MAJOR_VERSION            4
#define CANIF_J1939TP_AR_RELEASE_MINOR_VERSION            0
#define CANIF_J1939TP_AR_RELEASE_REVISION_VERSION         3

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* CANIF_VERSION_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
