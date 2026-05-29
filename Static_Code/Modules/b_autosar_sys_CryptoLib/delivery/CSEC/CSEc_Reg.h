/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CSEc_Reg.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for S32K CSEc                                     **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     13-May-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef CSEC_REG_H
#define CSEC_REG_H

/*******************************************************************************
**                                 Defines                                    **
*******************************************************************************/
/**
 * @brief  FTFC
 * @details S32K1XX System Memory Map
 */
#define FTFC_BASEADDR                                   ((uint32)0x40020000)

/**
 * @brief  PRAM
 * @details S32K14X System Memory Map
 */
#define PRAM_BASEADDR                                   ((uint32)0x14001000)

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/** @brief Flash Status Register (CSEC_FSTAT) */
#define CSEC_FSTAT_ADDR32                               ((uint32)(FTFC_BASEADDR + (uint32)0x00UL))
/** @brief Flash Configuration Register (CSEC_FCNFG) */
#define CSEC_FCNFG_ADDR32                               ((uint32)(FTFC_BASEADDR + (uint32)0x01UL))
/** @brief Flash CSE Status Register (CSEC_FCSESTAT) */
#define CSEC_FCSESTAT_ADDR32                            ((uint32)(FTFC_BASEADDR + (uint32)0x2CUL))
/** @brief Flash Common Command Object 0 Register (CSEC_FCCOB0) */
#define CSEC_FCCOB0_ADDR32                              ((uint32)(FTFC_BASEADDR + (uint32)0x07UL))
/** @brief Flash Common Command Object 1 Register (CSEC_FCCOB1) */
#define CSEC_FCCOB1_ADDR32                              ((uint32)(FTFC_BASEADDR + (uint32)0x06UL))
/** @brief Flash Common Command Object 2 Register (CSEC_FCCOB2) */
#define CSEC_FCCOB2_ADDR32                              ((uint32)(FTFC_BASEADDR + (uint32)0x05UL))
/** @brief Flash Common Command Object 3 Register (CSEC_FCCOB3) */
#define CSEC_FCCOB3_ADDR32                              ((uint32)(FTFC_BASEADDR + (uint32)0x04UL))
/** @brief Flash Common Command Object 4 Register (CSEC_FCCOB4) */
#define CSEC_FCCOB4_ADDR32                              ((uint32)(FTFC_BASEADDR + (uint32)0x0BUL))
/** @brief Flash Common Command Object 5 Register (CSEC_FCCOB5) */
#define CSEC_FCCOB5_ADDR32                              ((uint32)(FTFC_BASEADDR + (uint32)0x0AUL))
/** @brief PRAM page 0 header slot */
#define CSEC_PRAM_HDR_ADDR32                            (PRAM_BASEADDR + (uint32)0x00UL)
/** @brief PRAM page 0 error slot */
#define CSEC_PRAM_ERR_ADDR32                            (PRAM_BASEADDR + (uint32)0x06UL)
/** @brief PRAM page 1 */
#define CSEC_PRAM_PAGE1_ADDR32                          (PRAM_BASEADDR + (uint32)0x10UL)
/** @brief PRAM page 2 */
#define CSEC_PRAM_PAGE2_ADDR32                          (PRAM_BASEADDR + (uint32)0x20UL)
/** @brief PRAM page 3 */
#define CSEC_PRAM_PAGE3_ADDR32                          (PRAM_BASEADDR + (uint32)0x30UL)
/** @brief PRAM page 4 */
#define CSEC_PRAM_PAGE4_ADDR32                          (PRAM_BASEADDR + (uint32)0x40UL)
/** @brief PRAM page 5 */
#define CSEC_PRAM_PAGE5_ADDR32                          (PRAM_BASEADDR + (uint32)0x50UL)
/** @brief PRAM page 7 */
#define CSEC_PRAM_PAGE7_ADDR32                          (PRAM_BASEADDR + (uint32)0x70UL)
/** @brief PRAM page 0 length slot */
#define CSEC_PRAM_PAGE0_LENGTH_SLOT_ADDR16              (PRAM_BASEADDR + (uint32)0x0CUL)
/** @brief PRAM page 0 MAC length slot */
#define CSEC_PRAM_PAGE0_MAC_LENGTH_SLOT_ADDR16          (PRAM_BASEADDR + (uint32)0x0AUL)
/** @brief Verify MAC command */
#define CSEC_PRAM_PAGE1_MAC_STATUS_ADDR16               (CSEC_PRAM_PAGE1_ADDR32 + (uint32)0x06UL)
/** @brief Used for Get_ID command */
#define CSEC_PRAM_PAGE2_STATUS_REG_ADDR8                (CSEC_PRAM_PAGE2_ADDR32 + (uint32)0x0CUL)
/** @brief Used for Boot_define command */
#define CSEC_PRAM_PAGE1_BOOT_METHOD_ADDR8               (CSEC_PRAM_PAGE1_ADDR32 + (uint32)0x08UL)
/** @brief Used for Boot_define command */
#define CSEC_PRAM_PAGE1_BOOT_SIZE_ADDR32                (CSEC_PRAM_PAGE1_ADDR32 + (uint32)0x0CUL)

#define CSEC_PRAM_HDR_KEYID_U8                          ((uint32)0x00UL)
#define CSEC_PRAM_HDR_SEQ_U8                            ((uint32)0x08UL)
#define CSEC_PRAM_HDR_FORMAT_U8                         ((uint32)0x10UL)
#define CSEC_PRAM_HDR_CMD_U8                            ((uint32)0x18UL)

#define CSEC_PRAM_HDR_SEQ_ADDR32                        (CSEC_PRAM_HDR_ADDR32 + (uint32)0x01UL)

/* Flash CSE Status Register (CSEC_FCSESTAT) */
/** @brief Busy Flag */
#define CSEC_FCSESTAT_BSY_U8                            (0x01U)
/** @brief Secure Boot Flag */
#define CSEC_FCSESTAT_SB_U8                             (0x02U)
/** @brief Random Number Generator Initialized Flag */
#define CSEC_FCSESTAT_RIN_U8                            (0x20U)

/* Flash Configuration Register (CSEC_FCNFG) */
/** @brief RAM Ready */
#define CSEC_FCNFG_RAMRDY_U8                            (0x02U)
/** @brief EEE Ready */
#define CSEC_FCNFG_EEERDY_U8                            (0x01U)

/* Flash Status Register (FTFE_FSTAT) flags */
/** @brief Command Complete Interrupt Flag */
#define CSEC_FSTAT_CCIF_U8                              (0x80U)
/** @brief FTFE Read Collision Error Flag */
#define CSEC_FSTAT_RDCOLERR_U8                          (0x40U)
/** @brief Flash Access Error Flag */
#define CSEC_FSTAT_ACCERR_U8                            (0x20U)
/** @brief Flash Protection Violation Flag */
#define CSEC_FSTAT_FPVIOL_U8                            (0x10U)
/** @brief Memory Controller Command Completion Status Flag */
#define CSEC_FSTAT_MGSTAT0_U8                           (0x01U)

/* FSTAT masks for W1C operations */
#define CSEC_FSTAT_ACCERR_W1C                           (CSEC_FSTAT_ACCERR_U8)
#define CSEC_FSTAT_FPVIOL_W1C                           (CSEC_FSTAT_FPVIOL_U8)

/* Used to wait for FCSESTAT_BUSY flag to turn into 0 after a command is launched */
#define CSEC_COMMAND_IN_PROGRESS_U8                     ((uint8)1U)
#define CSEC_NO_COMMAND_IN_PROGRESS_U8                  ((uint8)0U)

/* Used to wait for FSTAT CCIF flag to verify no other command is in progress */
#define CSEC_CCIF_NO_COMMAND_IN_PROGRESS_U8             ((uint8)0x80U)

/* Program Partition flags */
/** @brief 0 key. none bytes are used in EEERAM */
#define CSEC_PGMPART_CSEC_KEY_SIZE_0_KEY_U8             ((uint8)0x00U)
/** @brief 1~5 keys. 128 bytes are used in EEERAM */
#define CSEC_PGMPART_CSEC_KEY_SIZE_5_KEYS_U8            ((uint8)0x01U)
/** @brief 1~10 keys. 256 bytes are used in EEERAM */
#define CSEC_PGMPART_CSEC_KEY_SIZE_10_KEYS_U8           ((uint8)0x02U)
/** @brief 1~20 keys. 512 bytes are used in EEERAM */
#define CSEC_PGMPART_CSEC_KEY_SIZE_20_KEYS_U8           ((uint8)0x03U)

/** @brief Flash Key 'Verify Only' attribute not enabled */
#define CSEC_PGMPART_SFE_DISABLED_U8                    ((uint8)0x00U)
/** @brief Flash Key 'Verify Only' attribute enabled */
#define CSEC_PGMPART_SFE_ENABLED_U8                     ((uint8)0x01U)

/** @brief FlexRAM loaded with valid EEPROM data during reset sequence */
#define CSEC_PGMPART_FLEXRAM_LOADED_U8                  ((uint8)0x00U)
/** @brief FlexRAM not loaded during reset sequence */
#define CSEC_PGMPART_FLEXRAM_NOT_LOADED_U8              ((uint8)0x01U)

/** @brief EEPROM Data Set Size 0 B */
#define CSEC_PGMPART_EEPROM_0B_U8                       ((uint8)0x0FU)
/** @brief EEPROM Data Set Size 2 KB */
#define CSEC_PGMPART_EEPROM_2K_U8                       ((uint8)0x03U)
/** @brief EEPROM Data Set Size 4 KB */
#define CSEC_PGMPART_EEPROM_4K_U8                       ((uint8)0x02U)

/** @brief EEPROM-Backup Size 0 B */
#define CSEC_PGMPART_EEPROM_BACKUP_0B_U8                ((uint8)0x00U)
/** @brief EEPROM-Backup Size 24 KB */
#define CSEC_PGMPART_EEPROM_BACKUP_24K_U8               ((uint8)0x09U)
/** @brief EEPROM-Backup Size 32 KB */
#define CSEC_PGMPART_EEPROM_BACKUP_32K_U8               ((uint8)0x03U)
/** @brief EEPROM-Backup Size 48 KB */
#define CSEC_PGMPART_EEPROM_BACKUP_48K_U8               ((uint8)0x0AU)
/** @brief EEPROM-Backup Size 64 KB */
#define CSEC_PGMPART_EEPROM_BACKUP_64K_U8               ((uint8)0x04U)

#endif /* CSEC_REG_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
