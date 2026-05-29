/**
 * \file Fbl_Ifx_Ssw.h
 * \brief Startup Software configuration. Can configure which core to be enabled.
 *
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
 *
 * $Date: 2017-05-12 08:52:44
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

#ifndef FBL_IFX_SSW_H_
#define FBL_IFX_SSW_H_

/******************************************************************************/
/*                          Typedefs                                          */
/******************************************************************************/
/** \brief Structure definition for the BMHD
 * Based on BMI and start address respective CRC and Inverted CRC values has to be calculated and updated.
 * CRC-32 polynomial as defined in the IEEE 802.3 standard is used to generate the CRC value. The CRC algorithm
 * treats input data as a stream of bits.
 *
 * Eg. To calculate the CRC data has to given in big-endian order.
 * for the below values:
 *    bmi    = 0x00FE
 *    bmhdid = 0xB359
 *    stad   = 0xA00A0000
 * CRC calculation:
 *    Input        = 0xB35900FEA00A0000
 *    CRC value    = 0x3CEED0A6
 *    CRC Inverted = 0xC3112F59
 */
typedef struct
{
    unsigned short bmi;             /**< \brief 0x000: Boot Mode Index (BMI)*/
    unsigned short bmhdid;          /**< \brief 0x002: Boot Mode Header ID (CODE) = B359H*/
    unsigned int   stad;            /**< \brief 0x004: User Code start address*/
    unsigned int   crc;             /**< \brief 0x008: Check Result for the BMI Header (offset 000H - 007H)*/
    unsigned int   crcInv;          /**< \brief 0x00C: Inverted Check Result for the BMI Header (offset 000H - 007H)*/
    unsigned int   reserved0[60];   /**< \brief 0x010: Reserved area (60 words) till the offset 0x100*/
    unsigned int   pw[8];           /**< \brief 0x100: Password protection (8 words) till the offset 0x120 */
    unsigned int   reserved1[52];   /**< \brief 0x120: Reserved area (52 words) till the offset 0x1F0*/
    unsigned int   confirmation;    /**< \brief 0x1F0: 32-bit CODE, (always same)*/
} Fbl_Ifx_Ssw_Bmhd;

typedef struct
{
    unsigned int   markerl;         /**< \brief 0x000: UCB_SWAP_ORIG_MARKERLx */
    unsigned int   markerh;         /**< \brief 0x004: UCB_SWAP_ORIG_MARKERHx */
    unsigned int   confirmationl;   /**< \brief 0x008: UCB_SWAP_ORIG_CONFIRMATIONLx */
    unsigned int   confirmationh;   /**< \brief 0x00C: UCB_SWAP_ORIG_CONFIRMATIONHx */
    unsigned int   reserved0[60];   /**< \brief 0x010: Reserved area (60 words) till the offset 0x100*/
    unsigned int   pw[8];           /**< \brief 0x100: Password protection (8 words) till the offset 0x120 */
    unsigned int   reserved1[52];   /**< \brief 0x120: Reserved area (52 words) till the offset 0x1F0*/
    unsigned int   confirmation;    /**< \brief 0x1F0: 32-bit CODE, (always same)*/
} Fbl_Ifx_Ucb_Swap;

typedef struct
{
    unsigned int   proconotpp0;     /**< \brief 0x000: DMU_HP_PROCONOTPp0 */
    unsigned int   proconotpp1;     /**< \brief 0x004: DMU_HP_PROCONOTPp1 */
    unsigned int   proconotpp2;     /**< \brief 0x008: DMU_HP_PROCONOTPp2 */
    unsigned int   proconotpp3;     /**< \brief 0x00C: DMU_HP_PROCONOTPp3 */
    unsigned int   proconotpp4;     /**< \brief 0x010: DMU_HP_PROCONOTPp4 */
    unsigned int   proconotpp5;     /**< \brief 0x014: DMU_HP_PROCONOTPp5 */
    unsigned int   reserved0[58];   /**< \brief 0x018: Reserved area (58 words) till the offset 0x100*/
    unsigned int   proconwopp0;     /**< \brief 0x100: DMU_HP_PROCONWOPp0 */
    unsigned int   proconwopp1;     /**< \brief 0x104: DMU_HP_PROCONWOPp1 */
    unsigned int   proconwopp2;     /**< \brief 0x108: DMU_HP_PROCONWOPp2 */
    unsigned int   proconwopp3;     /**< \brief 0x10C: DMU_HP_PROCONWOPp3 */
    unsigned int   proconwopp4;     /**< \brief 0x110: DMU_HP_PROCONWOPp4 */
    unsigned int   proconwopp5;     /**< \brief 0x114: DMU_HP_PROCONWOPp5 */
    unsigned int   reserved1[52];   /**< \brief 0x118: Reserved area (52 words) till the offset 0x1E8*/
    unsigned int   procontp;        /**< \brief 0x1E8: DMU_HF_PROCONTP */
    unsigned int   reserved2;       /**< \brief 0x1EC: Reserved area (1 words) till the offset 0x1F0*/
    unsigned int   confirmation;    /**< \brief 0x1F0: 32-bit CODE, (always same)*/
} Fbl_Ifx_Ucb_Otp;

#endif /* FBL_IFX_SSW_H_ */
