/*******************************************************************************
**                                                                            **
**  (C) 2020 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Schd_Cfg.h                                                    **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Configuration file for Scheduler                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date           By           Description                          **
********************************************************************************
** 1.0.0     10-April-2020  JaeHyun      Initial version                      **
*******************************************************************************/

#ifndef SCHD_CFG_H
#define SCHD_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define SCHD_TASK_50_USEC                                                 STD_ON
#define SCHD_TASK_100_USEC                                                STD_ON
#define SCHD_TASK_200_USEC                                                STD_ON
#define SCHD_TASK_500_USEC                                                STD_ON
#define SCHD_TASK_1_MSEC                                                  STD_ON
#define SCHD_TASK_5_MSEC                                                  STD_ON
#define SCHD_TASK_10_MSEC                                                 STD_ON

#if (SCHD_TASK_50_USEC == STD_ON)
#define SCHD_USEC_50_COUNT                                                 50U
#endif

#if (SCHD_TASK_100_USEC == STD_ON)
#define SCHD_USEC_100_COUNT                                               100U
#endif

#if (SCHD_TASK_200_USEC == STD_ON)
#define SCHD_USEC_200_COUNT                                               200U
#endif

#if (SCHD_TASK_500_USEC == STD_ON)
#define SCHD_USEC_500_COUNT                                               500U
#endif

#if (SCHD_TASK_1_MSEC == STD_ON)
#define SCHD_MSEC_1_COUNT                                                1000U 
#endif

#if (SCHD_TASK_5_MSEC == STD_ON)
#define SCHD_MSEC_5_COUNT                                                5000U
#endif

#if (SCHD_TASK_10_MSEC == STD_ON)
#define SCHD_MSEC_10_COUNT                                              10000U
#endif

#endif /* SCHD_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
