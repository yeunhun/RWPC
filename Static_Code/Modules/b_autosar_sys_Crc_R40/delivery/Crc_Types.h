/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Crc_Types.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
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
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.6     30-Dec-2020   YJ Yun           Redmine 27373                     **
** 1.3.5     03-May-2019   YJ Yun           Redmine #17358, #6718             **
** 1.0.0     07-Feb-2013   CY Song          Initial Version                   **
*******************************************************************************/
#ifndef CRC_TYPES_H
#define CRC_TYPES_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/


/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] No Impact of this rule violation */

/*
  polyspace:begin<MISRA-C:18.4:Not a defect:Justify with annotations> Union used for hanlding endian conversion
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/* polyspace-begin MISRA-C3:2.5 [Not a defect:Low] "Not a defect" */

/* Macro for 8bit Table Mode of CRC Calculation */
#define CRC_8_TABLE              (0x00U)

/* Macro for 8bit Runtime Mode of CRC Calculation */
#define CRC_8_RUNTIME            (0x01U)

/* Macro for 8bit with polynomial 0x2F Table Mode of CRC Calculation */
#define CRC_8H2F_TABLE           (0x00U)

/* Macro for 8bit with polynomial 0x2F Runtime Mode of CRC Calculation */
#define CRC_8H2F_RUNTIME         (0x01U)

/* Macro for 16bit Table Mode of CRC Calculation */
#define CRC_16_TABLE             (0x00U)

/* Macro for 16bit Runtime Mode of CRC Calculation */
#define CRC_16_RUNTIME           (0x01U)

/* Macro for 32bit Table Mode of CRC Calculation */
#define CRC_32_TABLE             (0x00U)

/* Macro for 32bit Runtime Mode of CRC Calculation */
#define CRC_32_RUNTIME           (0x01U)

/* Macro to be used when none of the modes are configured */
#define CRC_NOT_CFG              (0x02U)

#define CRC_TRUE                 (0x01U)

#define CRC_ONE                  (0x01U)

#define CRC_EIGHT                (0x08U)

#define CRC_THIRTYTWO            (32U)

#define CRC_ZERO                 (0U)

#define CRC_FF                   (0xFFU)

/* 8 bit MSB mask */
#define CRC_MSB8                 (0x80U)

/* 16 bit MSB mask */
#define CRC_MSB16                (0x8000U)

/* 32 bit MSB mask */
#define CRC_MS_BIT_LWORD         (0x80000000UL)

/* CRC-SAE-J1850  standard 8 bit generator polynomial */
#define CRC_POLY8                (0x1DU)

/* CRC-8 bit 0x2F polynomial */
#define CRC_POLY8H2F             (0x2FU)

/* CRC-CCITT standard 16 bit generator polynomial */
#define CRC_POLY16               (0x1021U)

/* IEEE-802.3 standard 32 bit generator polynomial */
#define CRC_POLY32               (0x04C11DB7UL)

/* Final XOR value for 8 bit checksum */
#define CRC_XOR_OUT8             (0xFFU)

/* Final XOR value for 8 bit checksum with 0x2F polynomial*/
#define CRC_XOR_OUT8H2F          (0xFFU)

/* Final XOR value for 32 bit checksum */
#define CRC_XOR_OUT32            (0xFFFFFFFFUL)

/* Array index of Table to perform CRC calculation */
#define CRC_COUNT256             (256U)

/* Macro for the Initial value of 8 bit CRC calculation */
#define CRC_INITIAL_VALUE8       (0xFFU)

/* Macro for the Initial value of 8 bit 0x2F CRC calculation */
#define CRC_INITIAL_VALUE8H2F    (0xFFU)

/* Macro for the Initial value of 16 bit CRC calculation */
#define CRC_INITIAL_VALUE16      (0xFFFFU)

/* Macro for the Initial value of 32 bit CRC calculation */
#define CRC_INITIAL_VALUE32      (0xFFFFFFFFUL)

/* polyspace-end MISRA-C3:2.5 [Not a defect:Low] "Not a defect" */

/* Define union for direct manipulation of 16 bit data */
#if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)

typedef union
{
  struct                                   /* Defining byte fields */
  {
    uint8 LsByte;                          /* Least significant byte */
    uint8 MsByte;                          /* Most significant byte */
  } Byte;

  uint16 WordReg16;                        /* 16 bit CRC field*/

}Crc_Word16;

/* Define union for Big Endian */
#else

typedef union
{
  /* Structure for accessing byte fields */
  struct
  {
    uint8 MsByte;                          /* Most significant byte */
    uint8 LsByte;                          /* Least significant byte */
  } Byte;

  uint16 WordReg16;                        /* 16 bit CRC field */

} Crc_Word16;

#endif /* End if(CPU_BYTE_ORDER == LOW_BYTE_FIRST) */

/* Union for direct manipulation of 32 bit register */
#if(CPU_BYTE_ORDER == LOW_BYTE_FIRST)

typedef union                              /* Little Endian Ordering */
{
 struct
 {
   uint8 LsByte;                           /* Least Significant byte (0)*/
   uint8 MidLowByte;                       /* Byte (1)*/
   uint8 MidHiByte;                        /* Byte (2) */
   uint8 MsByte;                           /* Most Significant byte (3) */
 } Byte;

 uint32 LongReg32;                         /* 32 bit field */

} Crc_Dword32;

#else

typedef union                              /* Big Endian Ordering */
{
  struct
  {
    uint8 MsByte;                          /* Most Significant byte (3) */
    uint8 MidHiByte;                       /* Byte (2)*/
    uint8 MidLowByte;                      /* Byte (1)*/
    uint8 LsByte;                          /* Least Significant byte (0) */
  } Byte;

  uint32 LongReg32;                        /* 32 bit field */

} Crc_Dword32;

#endif /* End if(CPU_BYTE_ORDER == LOW_BYTE_FIRST) */



/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/

#endif /* CRC_TYPES_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/*
  polyspace:end<MISRA-C:18.4:Not a defect:Justify with annotations> Union used for hanlding endian conversion
*/

/* polyspace-end MISRA-C3:20.1 [Not a defect:Low] No Impact of this rule violation */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
