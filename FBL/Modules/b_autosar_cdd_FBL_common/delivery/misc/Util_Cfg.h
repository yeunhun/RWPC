/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Util_Cfg.h                                                    **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides the data structure type definitions        **
**              used in Bootloader                                            **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef UTIL_CFG_H
#define UTIL_CFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define UTIL_MAX_TIMER_COUNT                                                 16U
#define UTIL_MAX_DYNAMIC_ERROR_BUFFER                                         5U
#define UTIL_MAX_STATIC_ERROR_BUFFER                                          3U
#ifndef UTIL_MINIMAL_IMPLEMENTATION
#define UTIL_MINIMAL_IMPLEMENTATION                                       STD_ON
#endif

#if (BTL_DEBUG == STD_ON)
#define UTIL_WARNING_TRACE(warn_no, msg_string)
#define UTIL_WARNING_TRACE_ONCE(error_no, msg_string)
#else
#define UTIL_WARNING_TRACE(warn_no, msg_string)
#define UTIL_WARNING_TRACE_ONCE(error_no, msg_string)
#endif

#endif /* UTIL_CFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
