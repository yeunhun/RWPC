/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Btl_Macros.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides  definitions for general macros                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef BTL_MACROS_H
#define BTL_MACROS_H

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Determine the absolute value, type=[int?_t] */
#define ABS(type, x)  (type)((x) < (type)0 ? (type)(-(x)) : (type)(x))

/* Determine the maximum value */
#define MAX(type, x, y)  (type)((x) < (type)y ? (type)(y) : (type)(x))

#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
/* No translation needed for big endian system */
#define Swap2Bytes(val) val
#define Swap4Bytes(val) val
#define Swap8Bytes(val) val
#else
 /* Swap 2 byte, 16 bit values: */
#define Swap2Bytes(val) \
 ( (((val) >> 8U) & 0x00FFU) | (((val) << 8U) & 0xFF00U) )
/* Swap 4 byte, 32 bit values: */
#define Swap4Bytes(val) \
 ( (((val) >> 24U) & 0x000000FFU) | (((val) >>  8U) & 0x0000FF00U) | \
   (((val) <<  8U) & 0x00FF0000U) | (((val) << 24U) & 0xFF000000U) )
/* Swap 8 byte, 64 bit values: */
#define Swap8Bytes(val) \
 ((((val)>>56U)&0x00000000000000FFU) | (((val)>>40U)&0x000000000000FF00U) | \
  (((val)>>24U)&0x0000000000FF0000U) | (((val)>> 8U)&0x00000000FF000000U) | \
  (((val)<< 8U)&0x000000FF00000000U) | (((val)<<24U)&0x0000FF0000000000U) | \
  (((val)<<40U)&0x00FF000000000000U) | (((val)<<56U)&0xFF00000000000000U) )
#endif

#endif /* BTL_MACROS_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
