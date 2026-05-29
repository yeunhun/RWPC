/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanIf_Notif.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Header file of CanIf_Notif.c                                  **
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
** 2.7.1    25-Nov-2020    Sj.Kim    #26002                                   **
** 2.7.0    07-Oct-2020    Sj.Kim    #25877                                   **
** 2.6.0    22-Aug-2019    Js.Lim    #18384                                   **
** 2.5.0    06-Dec-2016    Js.Lim    #6745, #7077                             **
** 1.0.0    04-Feb-2013    Kt.Kim    Initial version                          **
*******************************************************************************/

#ifndef CANIF_NOTIF_H
#define CANIF_NOTIF_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Tx.h"              /* Tx Interface header file */
#include "CanIf_Cbk.h"             /* Call-back header file */
#include "CanIf.h"                 /* Call-back header file */
#include "CanIf_Ram.h"             /* Ram header file */
#include "CanIf_PCTypes.h"         /* Pre-compile time header file */
#include "CanIf_IntTypes.h"        /* Pre-compile time header file */
#include "CanSM_Cbk.h"             /* CAN State Manager call back header file */
#if (STD_ON == CANIF_WAKEUP_SUPPORT)
#include "EcuM_Cbk.h"              /* EcuM call back header file */
#endif
#include "SchM_CanIf.h"            /* SchM CanIf Header file */
#if  (STD_ON == CANIF_DEV_ERROR_DETECT)
#include "CanIf_Error.h"           /* DET Header file */
#endif
#include "CanIf_UserInc.h"         /* CanIf User included header file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_NOTIF_AR_RELEASE_MAJOR_VERSION       4
#define CANIF_NOTIF_AR_RELEASE_MINOR_VERSION       0
#define CANIF_NOTIF_AR_RELEASE_REVISION_VERSION    3

/* Software Version Information */
#define CANIF_NOTIF_SW_MAJOR_VERSION    3
#define CANIF_NOTIF_SW_MINOR_VERSION    0
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/



#endif /* CANIF_NOTIF_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
