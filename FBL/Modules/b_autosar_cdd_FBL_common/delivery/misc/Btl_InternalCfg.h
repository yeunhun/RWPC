/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Btl_InternalCfg.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Configuration for bootloader                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.10.0.0  07-Feb-2021   JYS          Redmine #28298 #27968                 **
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef BTL_INTERNALCFG_H
#define BTL_INTERNALCFG_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Configuration for Block erase support */
#ifndef BTL_BLOCK_ERASE
#define BTL_BLOCK_ERASE                                                   STD_ON
#endif

/* Configuration for debug configuration */
#ifndef BTL_DEBUG
#define BTL_DEBUG                                                        STD_OFF
#endif

/* Configuration for standard library support */
#ifndef BTL_USE_STDLIB
#define BTL_USE_STDLIB                                                   STD_OFF
#endif

/* ECU gateway address */
#define BTL_ECU_GATEWAY_ADDRESS                                      0x00000000U

/* ECU Netmask */
#define BTL_ECU_NETMASK                                                       0U

#endif /* BTL_INTERNALCFG_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
