/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Btl_Project_Version.h                                         **
**                                                                            **
**  TARGET    : TC3XX                                                         **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file contains Project version information                **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef BTL_PROJECT_VERSION_H
#define BTL_PROJECT_VERSION_H

/*******************************************************************************
**                           Macro Definition                                 **
*******************************************************************************/
/* Macro for PROJECT_VERSION_MAJOR_NUMBER information */
#define PROJECT_VERSION_MAJOR_NUMBER   1U
/* Macro for PROJECT_VERSION_MINOR_NUMBER information */
#define PROJECT_VERSION_MINOR_NUMBER   2U
/* Macro for PROJECT_VERSION_BUGFIX_NUMBER information */
#define PROJECT_VERSION_BUGFIX_NUMBER  0U

/* Inline function for CHECKSUM calculation
 * Checksum is the sum of the PROJECT_VERSION_MAJOR_NUMBER plus
 * PROJECT_VERSION_MINOR_NUMBER plus PROJECT_VERSION_BUGFIX_NUMBER
 * and ignoring the carry of the result
 */
#define PROJECT_VERSION_CHECKSUM  \
  (uint8)(PROJECT_VERSION_MAJOR_NUMBER + \
   PROJECT_VERSION_MINOR_NUMBER + \
   PROJECT_VERSION_BUGFIX_NUMBER)

#endif /* BTL_PROJECT_VERSION_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
