/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: RamTst_CrcTypes.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Ram Test Module                                               **
**                                                                            **
**  PURPOSE   : Provision of Macros, unions for accessing byte fields and     **
**              global array declarations                                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                Description                      **
********************************************************************************
** 1.2.4     28-Dec-2018   YJ Yun           Redmine #15298                    **
** 1.2.3     05-Oct-2015   CY Song          Correct Misra Rule Error          **
** 1.0.0     07-Jun-2013   CY Song          Initial Version                   **
*******************************************************************************/
#ifndef RAMTST_CRCTYPES_H
#define RAMTST_CRCTYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Platform_Types.h"

/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.3 [Justified:Low] "Not a defect" */
/* polyspace-begin MISRA-C3:2.4 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define RAMTST_CRCTYPES_AR_MAJOR_VERSION         RAMTST_AR_RELEASE_MAJOR_VERSION
#define RAMTST_CRCTYPES_AR_MINOR_VERSION         RAMTST_AR_RELEASE_MINOR_VERSION
#define RAMTST_CRCTYPES_AR_RELEASE_REVISION_VERSION \
  RAMTST_AR_RELEASE_REVISION_VERSION

/* Software Version Information */
#define RAMTST_CRCTYPES_SW_MAJOR_VERSION   RAMTST_AR_RELEASE_MAJOR_VERSION
#define RAMTST_CRCTYPES_SW_MINOR_VERSION   RAMTST_AR_RELEASE_MINOR_VERSION
#define RAMTST_CRCTYPES_SW_PATCH_VERSION   RAMTST_SW_PATCH_VERSION

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define RAMTST_CRC_TRUE                 ((boolean)1)

#define RAMTST_CRC_ONE                  0x01L

#define RAMTST_CRC_EIGHT                0x08

#define RAMTST_CRC_THIRTYTWO            ((uint8)32u)

#define RAMTST_CRC_ZERO                 ((uint8)0u)

/* 8 bit MSB mask */
#define RAMTST_CRC_MSB8                 ((uint8)0x80u)

/* 16 bit MSB mask */
#define RAMTST_CRC_MSB16                ((uint16)0x8000u)

/* 32 bit MSB mask */
#define RAMTST_CRC_MS_BIT_LWORD         0x80000000UL

/* CRC-SAE-J1850  standard 8 bit generator polynomial */
#define RAMTST_CRC_POLY8                ((uint8)0x1Du)

/* CRC-8 bit 0x2F polynomial */
#define RAMTST_CRC_POLY8H2F             ((uint8)0x2Fu)

/* CRC-CCITT standard 16 bit generator polynomial */
#define RAMTST_CRC_POLY16               ((uint16)0x1021u)

/* IEEE-802.3 standard 32 bit generator polynomial */
#define RAMTST_CRC_POLY32               ((uint32)0x04C11DB7L)

/* Final XOR value for 8 bit checksum */
#define RAMTST_CRC_XOR_OUT8             ((uint8)0xFFu)

/* Final XOR value for 8 bit checksum with 0x2F polynomial*/
#define RAMTST_CRC_XOR_OUT8H2F          ((uint8)0xFFu)

/* Final XOR value for 32 bit checksum */
#define RAMTST_CRC_XOR_OUT32            0xFFFFFFFFUL

/* Array index of Table to perform CRC calculation */
#define RAMTST_CRC_COUNT256             ((uint16)256u)

/* Macro for the Initial value of 8 bit CRC calculation */
#define RAMTST_CRC_INITIAL_VALUE8       ((uint8)0xFFu)

/* Macro for the Initial value of 8 bit 0x2F CRC calculation */
#define RAMTST_CRC_INITIAL_VALUE8H2F    ((uint8)0xFFu)

/* Macro for the Initial value of 16 bit CRC calculation */
#define RAMTST_CRC_INITIAL_VALUE16      ((uint16)0xFFFFu)

/* Macro for the Initial value of 32 bit CRC calculation */
#define RAMTST_CRC_INITIAL_VALUE32      ((uint32)0xFFFFFFFFUL)



typedef struct STag_CRC_Word16
{
  uint8 LsByteForWord16;
  uint8 MsByteForWord16;
  uint16 WordReg16;
} RamTst_Crc_Word16;

typedef struct STag_CRC_Dword32
{
  uint8 LsByteFor32;
  uint8 MidLowByteFor32;
  uint8 MidHiByteFor32;
  uint8 MsByteFor32;
  uint32 LongReg32;
} RamTst_Crc_Dword32;
/* polyspace-end MISRA-C3:2.4 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.3 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.2 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:2.5 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/


#endif /* RAMTST_CRCTYPES_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
