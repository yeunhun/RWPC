/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODUE: Spi.h                                                         **
**                                                                            **
**  TARGET    : CYTXXX                                                        **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Spi.c                                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision    Date          By           Description                         **
********************************************************************************
** 1.3.1.0     11-Jun-2021   JHLim        Redmine #30328                      **
** 1.0.0       07-Jun-2021 VuPH6        Initial version                       **
**                                      Redmine #28436                        **
*******************************************************************************/

#ifndef SPI_H
#define SPI_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Mcu.h"
#include "Platform_Types.h"
#include "Fbl_cfg.h"
/*******************************************************************************
**                           Macro Definition                                 **
*******************************************************************************/
#define SPI_CHANNEL_0                               0U
#define SPI_CHANNEL_1                               1U
#define SPI_CHANNEL_2                               2U
#define SPI_CHANNEL_3                               3U
#define SPI_CHANNEL_4                               4U
#define SPI_CHANNEL_5                               5U
#define SPI_CHANNEL_6                               6U
#define SPI_CHANNEL_7                               7U
#if((FBL_MCU_NAME == CYT3BBXX) || (FBL_MCU_NAME == CYT4BBXX) || (FBL_MCU_NAME == CYT4BFXX))
#define SPI_CHANNEL_8                               8U
#define SPI_CHANNEL_9                               9U
#define SPI_CHANNEL_10                              10U
#endif
/* define SPI channel base address */
#define SPI_BASE_0                                  SCB0
#define SPI_BASE_1                                  SCB1
#define SPI_BASE_2                                  SCB2
#define SPI_BASE_3                                  SCB3
#define SPI_BASE_4                                  SCB4
#define SPI_BASE_5                                  SCB5
#define SPI_BASE_6                                  SCB6
#define SPI_BASE_7                                  SCB7
#if((FBL_MCU_NAME == CYT3BBXX) || (FBL_MCU_NAME == CYT4BBXX) || (FBL_MCU_NAME == CYT4BFXX))
#define SPI_BASE_8                                  SCB8
#define SPI_BASE_9                                  SCB9
#define SPI_BASE_10                                 SCB10
#endif

/* SCB CTRL modes */
#define SCB_CTRL_MODE_I2C                           0U
#define SCB_CTRL_MODE_SPI                           1U
#define SCB_CTRL_MODE_UART                          2U
/* SPI divider OVS number */
#define SPI_OVS_DIVIDER_NUMBER                      4U
/* SCB CTRL MEM_WIDTH (Number of bits per FIFIO data element) */
#define SPI_DATA_WIDTH_BYTE                         8U
#define SPI_DATA_WIDTH_HALFWORD                     16U
#define SPI_DATA_WIDTH_WORD                         32U
/* SCB CTRL MEM_WIDTH REGISTER */
#define SPI_CTRL_MEM_WIDTH_BYTE                     0U
#define SPI_CTRL_MEM_WIDTH_HALFWORD                 1U
#define SPI_CTRL_MEM_WIDTH_WORD                     2U
/* Configures SCB for SPI Slave operation */
#define SCB_SPI_SLAVE                               0U
/* Configures SCB for SPI Master operation */
#define SCB_SPI_MASTER                              1U
/** Configures an SPI for a standard Motorola SPI operation */
#define SCB_SPI_MOTOROLA                            0U
/* Max number of bits for byte mode */
#define SCB_BYTE_WIDTH                              8U
#define SCB_HALFWORD_WIDTH                          16U
#define SCB_WORD_WIDTH                              32U
/* SPI chip select */
#define SPI_CHIP_SELECT_0                           0U
#define SPI_CHIP_SELECT_1                           1U
#define SPI_CHIP_SELECT_2                           2U
#define SPI_CHIP_SELECT_3                           3U
/* Clock input to SCB peripheral */
#define SPI_SCB_CLOCK_SOURCE                        80000000U
/* Number of bit of FRAC5_DIV */
#define SPI_NUM_OF_BIT_FRAC5_DIV                    5U
#define SPI_FRAC5_DIV_MASK                          0x0000001FU
#define SPI_24INT24_DIV_DIV_MASK                    0x00000FFFU
/* define number of 24_5 devider in CYT2BXXX MCU */
#define SPI_NUM_OF_24_5_DEVIDER_CYT2BXXX            PERI_DIV_24_5_NR
/* define number of 24_5 devider in CYT3BXXX/CYT4BXXX MCU */
#define SPI_NUM_OF_24_5_DEVIDER_CYT3BXXX_CYT4BXXX   PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT
/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#if (FBL_SPI_CTRL_ENABLE == STD_ON)
extern uint8 Fbl_Gu8_NumOfSpiCtrl;

#define BTL_START_SEC_PJS_CODE
#include "Btl_MemMap.h"

extern void Spi_Init(void);

#define BTL_STOP_SEC_PJS_CODE
#include "Btl_MemMap.h"
#endif
#endif /* SPI_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
