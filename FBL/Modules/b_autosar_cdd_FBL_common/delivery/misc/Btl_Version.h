/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Btl_Version.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides all the macros for the allowed address     **
**              range of ram memory                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef BTL_VERSION_H
#define BTL_VERSION_H

/*******************************************************************************
**                       Header File Include Section                          **
*******************************************************************************/
/* Header file inclusion for standard type definitions */
#include "Btl.h"
/* Header file for project version information */
#include "Btl_Project_Version.h"
/* Header file for core version information */
#include "Btl_Core_Version.h"

/*******************************************************************************
**                           Macro Definition                                 **
*******************************************************************************/
#define BTL_VERSION_BYTES_FOR_COMPILER_VERSION                                8U
#define BTL_VERSION_BYTES_FOR_BUILD_TIME                                      9U
#define BTL_VERSION_BYTES_FOR_BUILD_DATE                                     12U

/*******************************************************************************
**                     Global Data Types                                      **
*******************************************************************************/
/* Project's version information */
typedef struct
{ /* Project major number */
  uint8 u8_MajorNumber;
  /* Project minor number */
  uint8 u8_MinorNumber;
  /* Project BugfixNumber */
  uint8 u8_BugfixNumber;
  /* Project checksum number */
  uint8 u8_Checksum;
}BTLV_ProjectVersionInfo_Styp;

/* Application interface version information */
typedef struct
{
  /* Application interface information */
  uint8 u8_AppIf;
}BTLV_AppIfVersionInfo_Styp;


/* Common code's version information */
typedef struct
{/* common information Major number */
  uint8 u8_MajorNumber;
  /* Common information Minor number */
  uint8 u8_MinorNumber;
  /* Common information Bugfix number */
  uint8 u8_BugfixNumber;
}BTLV_CommonVersionInfo_Styp;


/* Project build information */
typedef struct
{ /* Buffer for holding the  date */
  uint8 au8_Date[BTL_VERSION_BYTES_FOR_BUILD_DATE];
  /* Buffer for holding the time */
  uint8 au8_Time[BTL_VERSION_BYTES_FOR_BUILD_TIME];
  /* Buffer for holding the Compiler information */
  uint8 au8_CompilerVersion[BTL_VERSION_BYTES_FOR_COMPILER_VERSION];

}BTLV_BuildInfo_Styp;


/* BTL Project version and build information */
typedef struct
{
 /* Object for project version information */
  BTLV_ProjectVersionInfo_Styp   st_ProjectVersionInfo;
  /* Object for Application version information */
  BTLV_AppIfVersionInfo_Styp     st_AppIfVersionInfo;
  /* Object for common version information */
  BTLV_CommonVersionInfo_Styp    st_CommonVersionInfo;
  /* Object for Build information */
  BTLV_BuildInfo_Styp            st_BuildInfo;

}BTLV_VersionInfo_Styp;

/*******************************************************************************
**                Global constant Declaration                                 **
*******************************************************************************/
#define BTL_START_iVERSION_INFO
#include "Btl_MemMap.h"

/* External type declaration of the BTL version information */
extern const BTLV_VersionInfo_Styp BtlV_Gst_VersionInfo;

#define BTL_STOP_iVERSION_INFO
#include "Btl_MemMap.h"

#endif /* BTL_VERSION_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
