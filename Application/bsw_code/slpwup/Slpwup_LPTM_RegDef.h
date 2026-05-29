/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**   This file copyed from 'b_pf_autosar_cypress_bundle'.                     **
**                                                                            **
*******************************************************************************/

#ifndef SLPWUP_LPTM_REGDEF_H
#define SLPWUP_LPTM_REGDEF_H
/**
** Register Settings
**/

#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
*                                    CPUSS
*******************************************************************************/

#define CPUSS_BASE                              0x40200000UL
#define CPUSS                                   ((volatile stc_CPUSS_t*) CPUSS_BASE)

/*******************************************************************************
*                                     PASS
*******************************************************************************/

#define PASS0_BASE                              0x40900000UL
#define PASS0                                   ((volatile stc_PASS_t*) PASS0_BASE)                               /* 0x40900000 */
#define PASS0_SAR0                              ((volatile stc_PASS_SAR_t*) &PASS0->SAR[0])                       /* 0x40900000 */
#define PASS0_SAR1                              ((volatile stc_PASS_SAR_t*) &PASS0->SAR[1])                       /* 0x40901000 */
#define PASS0_SAR2                              ((volatile stc_PASS_SAR_t*) &PASS0->SAR[2])                       /* 0x40902000 */



/*******************************************************************************
*                                    CPUSS
*******************************************************************************/

#define CPUSS_SECTION_SIZE                      0x00010000UL

/**
  * \brief Identity (CPUSS_IDENTITY)
  */
typedef struct stc_CPUSS_IDENTITY_field {
  uint32_t                         u1P:1;
  uint32_t                         u1NS:1;
  uint32_t                         :2;
  uint32_t                         u4PC:4;
  uint32_t                         u4MS:4;
  uint32_t                         :20;
} stc_CPUSS_IDENTITY_field_t;

typedef union un_CPUSS_IDENTITY {
  uint32_t                         u32Register;
  stc_CPUSS_IDENTITY_field_t       stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_IDENTITY_t;

/**
  * \brief CM7 0 status (CPUSS_CM7_0_STATUS)
  */
typedef struct stc_CPUSS_CM7_0_STATUS_field {
  uint32_t                         u1SLEEPING:1;
  uint32_t                         u1SLEEPDEEP:1;
  uint32_t                         :2;
  uint32_t                         u1PWR_DONE:1;
  uint32_t                         :4;
  uint32_t                         u1TCMC_CM7_1_MS:1;
  uint32_t                         u1TCMC_EXT_MS_2_TO_0:1;
  uint32_t                         u1TCMC_EXT_MS_3:1;
  uint32_t                         u1TCMC_AHB_MS:1;
  uint32_t                         :19;
} stc_CPUSS_CM7_0_STATUS_field_t;

typedef union un_CPUSS_CM7_0_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_0_STATUS_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_0_STATUS_t;

/**
  * \brief Fast 0 clock control (CPUSS_FAST_0_CLOCK_CTL)
  */
typedef struct stc_CPUSS_FAST_0_CLOCK_CTL_field {
  uint32_t                         :3;
  uint32_t                         u5FRAC_DIV:5;
  uint32_t                         u8INT_DIV:8;
  uint32_t                         :16;
} stc_CPUSS_FAST_0_CLOCK_CTL_field_t;

typedef union un_CPUSS_FAST_0_CLOCK_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_FAST_0_CLOCK_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_FAST_0_CLOCK_CTL_t;

/**
  * \brief CM7 0 control (CPUSS_CM7_0_CTL)
  */
typedef struct stc_CPUSS_CM7_0_CTL_field {
  uint32_t                         u4PPB_LOCK:4;
  uint32_t                         u1CPU_WAIT:1;
  uint32_t                         :3;
  uint32_t                         u2INIT_TCM_EN:2;
  uint32_t                         u2INIT_RMW_EN:2;
  uint32_t                         :4;
  uint32_t                         u1ITCM_ECC_EN:1;
  uint32_t                         u1ITCM_ECC_INJ_EN:1;
  uint32_t                         u1ITCM_READ_WS:1;
  uint32_t                         u1ITCM_ECC_CHECK_DIS:1;
  uint32_t                         u1DTCM_ECC_EN:1;
  uint32_t                         u1DTCM_ECC_INJ_EN:1;
  uint32_t                         u1DTCM_READ_WS:1;
  uint32_t                         u1TCMC_EN:1;
  uint32_t                         u1IOC_MASK:1;
  uint32_t                         u1DZC_MASK:1;
  uint32_t                         u1OFC_MASK:1;
  uint32_t                         u1UFC_MASK:1;
  uint32_t                         u1IXC_MASK:1;
  uint32_t                         :2;
  uint32_t                         u1IDC_MASK:1;
} stc_CPUSS_CM7_0_CTL_field_t;

typedef union un_CPUSS_CM7_0_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_0_CTL_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_0_CTL_t;

/**
  * \brief CM7 0 interrupt status (CPUSS_CM7_0_INT_STATUS)
  */
typedef struct stc_CPUSS_CM7_0_INT_STATUS_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :21;
  uint32_t                         u1SYSTEM_INT_VALID:1;
} stc_CPUSS_CM7_0_INT_STATUS_field_t;

typedef union un_CPUSS_CM7_0_INT_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_0_INT_STATUS_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_0_INT_STATUS_t;

/**
  * \brief CM7 0 vector table base (CPUSS_CM7_0_VECTOR_TABLE_BASE)
  */
typedef struct stc_CPUSS_CM7_0_VECTOR_TABLE_BASE_field {
  uint32_t                         :7;
  uint32_t                         u25ADDR25:25;
} stc_CPUSS_CM7_0_VECTOR_TABLE_BASE_field_t;

typedef union un_CPUSS_CM7_0_VECTOR_TABLE_BASE {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_0_VECTOR_TABLE_BASE_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_0_VECTOR_TABLE_BASE_t;

/**
  * \brief CM7 0 NMI control (CPUSS_CM7_0_NMI_CTL)
  */
typedef struct stc_CPUSS_CM7_0_NMI_CTL_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :22;
} stc_CPUSS_CM7_0_NMI_CTL_field_t;

typedef union un_CPUSS_CM7_0_NMI_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_0_NMI_CTL_field_t  stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_0_NMI_CTL_t;

/**
  * \brief UDB power control (CPUSS_UDB_PWR_CTL)
  */
typedef struct stc_CPUSS_UDB_PWR_CTL_field {
  uint32_t                         u2PWR_MODE:2;
  uint32_t                         :14;
  uint32_t                         u16VECTKEYSTAT:16;
} stc_CPUSS_UDB_PWR_CTL_field_t;

typedef union un_CPUSS_UDB_PWR_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_UDB_PWR_CTL_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_UDB_PWR_CTL_t;

/**
  * \brief UDB power control (CPUSS_UDB_PWR_DELAY_CTL)
  */
typedef struct stc_CPUSS_UDB_PWR_DELAY_CTL_field {
  uint32_t                         u10UP:10;
  uint32_t                         :22;
} stc_CPUSS_UDB_PWR_DELAY_CTL_field_t;

typedef union un_CPUSS_UDB_PWR_DELAY_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_UDB_PWR_DELAY_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_UDB_PWR_DELAY_CTL_t;

/**
  * \brief Trace and debug clock control (CPUSS_TRC_DBG_CLOCK_CTL)
  */
typedef struct stc_CPUSS_TRC_DBG_CLOCK_CTL_field {
  uint32_t                         :8;
  uint32_t                         u8INT_DIV:8;
  uint32_t                         :16;
} stc_CPUSS_TRC_DBG_CLOCK_CTL_field_t;

typedef union un_CPUSS_TRC_DBG_CLOCK_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_TRC_DBG_CLOCK_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_TRC_DBG_CLOCK_CTL_t;

/**
  * \brief CM7 1status (CPUSS_CM7_1_STATUS)
  */
typedef struct stc_CPUSS_CM7_1_STATUS_field {
  uint32_t                         u1SLEEPING:1;
  uint32_t                         u1SLEEPDEEP:1;
  uint32_t                         :2;
  uint32_t                         u1PWR_DONE:1;
  uint32_t                         :3;
  uint32_t                         u1TCMC_CM7_0_MS:1;
  uint32_t                         :1;
  uint32_t                         u1TCMC_EXT_MS_2_TO_0:1;
  uint32_t                         u1TCMC_EXT_MS_3:1;
  uint32_t                         u1TCMC_AHB_MS:1;
  uint32_t                         :19;
} stc_CPUSS_CM7_1_STATUS_field_t;

typedef union un_CPUSS_CM7_1_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_1_STATUS_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_1_STATUS_t;

/**
  * \brief Fast 1 clock control (CPUSS_FAST_1_CLOCK_CTL)
  */
typedef struct stc_CPUSS_FAST_1_CLOCK_CTL_field {
  uint32_t                         :3;
  uint32_t                         u5FRAC_DIV:5;
  uint32_t                         u8INT_DIV:8;
  uint32_t                         :16;
} stc_CPUSS_FAST_1_CLOCK_CTL_field_t;

typedef union un_CPUSS_FAST_1_CLOCK_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_FAST_1_CLOCK_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_FAST_1_CLOCK_CTL_t;

/**
  * \brief CM7 1 control (CPUSS_CM7_1_CTL)
  */
typedef struct stc_CPUSS_CM7_1_CTL_field {
  uint32_t                         u4PPB_LOCK:4;
  uint32_t                         u1CPU_WAIT:1;
  uint32_t                         :3;
  uint32_t                         u2INIT_TCM_EN:2;
  uint32_t                         u2INIT_RMW_EN:2;
  uint32_t                         :4;
  uint32_t                         u1ITCM_ECC_EN:1;
  uint32_t                         u1ITCM_ECC_INJ_EN:1;
  uint32_t                         u1ITCM_READ_WS:1;
  uint32_t                         u1ITCM_ECC_CHECK_DIS:1;
  uint32_t                         u1DTCM_ECC_EN:1;
  uint32_t                         u1DTCM_ECC_INJ_EN:1;
  uint32_t                         u1DTCM_READ_WS:1;
  uint32_t                         u1TCMC_EN:1;
  uint32_t                         u1IOC_MASK:1;
  uint32_t                         u1DZC_MASK:1;
  uint32_t                         u1OFC_MASK:1;
  uint32_t                         u1UFC_MASK:1;
  uint32_t                         u1IXC_MASK:1;
  uint32_t                         :2;
  uint32_t                         u1IDC_MASK:1;
} stc_CPUSS_CM7_1_CTL_field_t;

typedef union un_CPUSS_CM7_1_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_1_CTL_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_1_CTL_t;

/**
  * \brief CM7 1 interrupt status (CPUSS_CM7_1_INT_STATUS)
  */
typedef struct stc_CPUSS_CM7_1_INT_STATUS_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :21;
  uint32_t                         u1SYSTEM_INT_VALID:1;
} stc_CPUSS_CM7_1_INT_STATUS_field_t;

typedef union un_CPUSS_CM7_1_INT_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_1_INT_STATUS_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_1_INT_STATUS_t;

/**
  * \brief CM7 1 vector table base (CPUSS_CM7_1_VECTOR_TABLE_BASE)
  */
typedef struct stc_CPUSS_CM7_1_VECTOR_TABLE_BASE_field {
  uint32_t                         :7;
  uint32_t                         u25ADDR25:25;
} stc_CPUSS_CM7_1_VECTOR_TABLE_BASE_field_t;

typedef union un_CPUSS_CM7_1_VECTOR_TABLE_BASE {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_1_VECTOR_TABLE_BASE_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_1_VECTOR_TABLE_BASE_t;

/**
  * \brief CM7 1 NMI control (CPUSS_CM7_1_NMI_CTL)
  */
typedef struct stc_CPUSS_CM7_1_NMI_CTL_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :22;
} stc_CPUSS_CM7_1_NMI_CTL_field_t;

typedef union un_CPUSS_CM7_1_NMI_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_1_NMI_CTL_field_t  stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_1_NMI_CTL_t;

/**
  * \brief CM0+ control (CPUSS_CM0_CTL)
  */
typedef struct stc_CPUSS_CM0_CTL_field {
  uint32_t                         u1SLV_STALL:1;
  uint32_t                         u1ENABLED:1;
  uint32_t                         :14;
  uint32_t                         u16VECTKEYSTAT:16;
} stc_CPUSS_CM0_CTL_field_t;

typedef union un_CPUSS_CM0_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_CTL_field_t        stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_CTL_t;

/**
  * \brief CM0+ status (CPUSS_CM0_STATUS)
  */
typedef struct stc_CPUSS_CM0_STATUS_field {
  uint32_t                         u1SLEEPING:1;
  uint32_t                         u1SLEEPDEEP:1;
  uint32_t                         :30;
} stc_CPUSS_CM0_STATUS_field_t;

typedef union un_CPUSS_CM0_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_STATUS_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_STATUS_t;

/**
  * \brief Slow clock control (CPUSS_SLOW_CLOCK_CTL)
  */
typedef struct stc_CPUSS_SLOW_CLOCK_CTL_field {
  uint32_t                         :8;
  uint32_t                         u8INT_DIV:8;
  uint32_t                         :16;
} stc_CPUSS_SLOW_CLOCK_CTL_field_t;

typedef union un_CPUSS_SLOW_CLOCK_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_SLOW_CLOCK_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_SLOW_CLOCK_CTL_t;

/**
  * \brief Peripheral interconnect clock control (CPUSS_PERI_CLOCK_CTL)
  */
typedef struct stc_CPUSS_PERI_CLOCK_CTL_field {
  uint32_t                         :8;
  uint32_t                         u8INT_DIV:8;
  uint32_t                         :16;
} stc_CPUSS_PERI_CLOCK_CTL_field_t;

typedef union un_CPUSS_PERI_CLOCK_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_PERI_CLOCK_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_PERI_CLOCK_CTL_t;

/**
  * \brief Memory clock control (CPUSS_MEM_CLOCK_CTL)
  */
typedef struct stc_CPUSS_MEM_CLOCK_CTL_field {
  uint32_t                         :8;
  uint32_t                         u8INT_DIV:8;
  uint32_t                         :16;
} stc_CPUSS_MEM_CLOCK_CTL_field_t;

typedef union un_CPUSS_MEM_CLOCK_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_MEM_CLOCK_CTL_field_t  stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_MEM_CLOCK_CTL_t;

/**
  * \brief CM0+ interrupt 0 status (CPUSS_CM0_INT0_STATUS)
  */
typedef struct stc_CPUSS_CM0_INT0_STATUS_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :21;
  uint32_t                         u1SYSTEM_INT_VALID:1;
} stc_CPUSS_CM0_INT0_STATUS_field_t;

typedef union un_CPUSS_CM0_INT0_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_INT0_STATUS_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_INT0_STATUS_t;

/**
  * \brief CM0+ interrupt 1 status (CPUSS_CM0_INT1_STATUS)
  */
typedef struct stc_CPUSS_CM0_INT1_STATUS_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :21;
  uint32_t                         u1SYSTEM_INT_VALID:1;
} stc_CPUSS_CM0_INT1_STATUS_field_t;

typedef union un_CPUSS_CM0_INT1_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_INT1_STATUS_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_INT1_STATUS_t;

/**
  * \brief CM0+ interrupt 2 status (CPUSS_CM0_INT2_STATUS)
  */
typedef struct stc_CPUSS_CM0_INT2_STATUS_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :21;
  uint32_t                         u1SYSTEM_INT_VALID:1;
} stc_CPUSS_CM0_INT2_STATUS_field_t;

typedef union un_CPUSS_CM0_INT2_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_INT2_STATUS_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_INT2_STATUS_t;

/**
  * \brief CM0+ interrupt 3 status (CPUSS_CM0_INT3_STATUS)
  */
typedef struct stc_CPUSS_CM0_INT3_STATUS_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :21;
  uint32_t                         u1SYSTEM_INT_VALID:1;
} stc_CPUSS_CM0_INT3_STATUS_field_t;

typedef union un_CPUSS_CM0_INT3_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_INT3_STATUS_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_INT3_STATUS_t;

/**
  * \brief CM0+ interrupt 4 status (CPUSS_CM0_INT4_STATUS)
  */
typedef struct stc_CPUSS_CM0_INT4_STATUS_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :21;
  uint32_t                         u1SYSTEM_INT_VALID:1;
} stc_CPUSS_CM0_INT4_STATUS_field_t;

typedef union un_CPUSS_CM0_INT4_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_INT4_STATUS_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_INT4_STATUS_t;

/**
  * \brief CM0+ interrupt 5 status (CPUSS_CM0_INT5_STATUS)
  */
typedef struct stc_CPUSS_CM0_INT5_STATUS_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :21;
  uint32_t                         u1SYSTEM_INT_VALID:1;
} stc_CPUSS_CM0_INT5_STATUS_field_t;

typedef union un_CPUSS_CM0_INT5_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_INT5_STATUS_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_INT5_STATUS_t;

/**
  * \brief CM0+ interrupt 6 status (CPUSS_CM0_INT6_STATUS)
  */
typedef struct stc_CPUSS_CM0_INT6_STATUS_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :21;
  uint32_t                         u1SYSTEM_INT_VALID:1;
} stc_CPUSS_CM0_INT6_STATUS_field_t;

typedef union un_CPUSS_CM0_INT6_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_INT6_STATUS_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_INT6_STATUS_t;

/**
  * \brief CM0+ interrupt 7 status (CPUSS_CM0_INT7_STATUS)
  */
typedef struct stc_CPUSS_CM0_INT7_STATUS_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :21;
  uint32_t                         u1SYSTEM_INT_VALID:1;
} stc_CPUSS_CM0_INT7_STATUS_field_t;

typedef union un_CPUSS_CM0_INT7_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_INT7_STATUS_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_INT7_STATUS_t;

/**
  * \brief CM0+ vector table base (CPUSS_CM0_VECTOR_TABLE_BASE)
  */
typedef struct stc_CPUSS_CM0_VECTOR_TABLE_BASE_field {
  uint32_t                         :8;
  uint32_t                         u24ADDR24:24;
} stc_CPUSS_CM0_VECTOR_TABLE_BASE_field_t;

typedef union un_CPUSS_CM0_VECTOR_TABLE_BASE {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_VECTOR_TABLE_BASE_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_VECTOR_TABLE_BASE_t;

/**
  * \brief CM0+ NMI control (CPUSS_CM0_NMI_CTL)
  */
typedef struct stc_CPUSS_CM0_NMI_CTL_field {
  uint32_t                         u10SYSTEM_INT_IDX:10;
  uint32_t                         :22;
} stc_CPUSS_CM0_NMI_CTL_field_t;

typedef union un_CPUSS_CM0_NMI_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_NMI_CTL_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_NMI_CTL_t;

/**
  * \brief CM7 0 power control (CPUSS_CM7_0_PWR_CTL)
  */
typedef struct stc_CPUSS_CM7_0_PWR_CTL_field {
  uint32_t                         u2PWR_MODE:2;
  uint32_t                         :14;
  uint32_t                         u16VECTKEYSTAT:16;
} stc_CPUSS_CM7_0_PWR_CTL_field_t;

typedef union un_CPUSS_CM7_0_PWR_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_0_PWR_CTL_field_t  stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_0_PWR_CTL_t;

/**
  * \brief CM7 0 power delay control (CPUSS_CM7_0_PWR_DELAY_CTL)
  */
typedef struct stc_CPUSS_CM7_0_PWR_DELAY_CTL_field {
  uint32_t                         u10UP:10;
  uint32_t                         :22;
} stc_CPUSS_CM7_0_PWR_DELAY_CTL_field_t;

typedef union un_CPUSS_CM7_0_PWR_DELAY_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_0_PWR_DELAY_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_0_PWR_DELAY_CTL_t;

/**
  * \brief CM7 1 power control (CPUSS_CM7_1_PWR_CTL)
  */
typedef struct stc_CPUSS_CM7_1_PWR_CTL_field {
  uint32_t                         u2PWR_MODE:2;
  uint32_t                         :14;
  uint32_t                         u16VECTKEYSTAT:16;
} stc_CPUSS_CM7_1_PWR_CTL_field_t;

typedef union un_CPUSS_CM7_1_PWR_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_1_PWR_CTL_field_t  stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_1_PWR_CTL_t;

/**
  * \brief CM7 1 power delay control (CPUSS_CM7_1_PWR_DELAY_CTL)
  */
typedef struct stc_CPUSS_CM7_1_PWR_DELAY_CTL_field {
  uint32_t                         u10UP:10;
  uint32_t                         :22;
} stc_CPUSS_CM7_1_PWR_DELAY_CTL_field_t;

typedef union un_CPUSS_CM7_1_PWR_DELAY_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_1_PWR_DELAY_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_1_PWR_DELAY_CTL_t;

/**
  * \brief RAM 0 control (CPUSS_RAM0_CTL0)
  */
typedef struct stc_CPUSS_RAM0_CTL0_field {
  uint32_t                         u2SLOW_WS:2;
  uint32_t                         :6;
  uint32_t                         u2FAST_WS:2;
  uint32_t                         :6;
  uint32_t                         u1ECC_EN:1;
  uint32_t                         u1ECC_AUTO_CORRECT:1;
  uint32_t                         u1ECC_INJ_EN:1;
  uint32_t                         u1ECC_CHECK_DIS:1;
  uint32_t                         :12;
} stc_CPUSS_RAM0_CTL0_field_t;

typedef union un_CPUSS_RAM0_CTL0 {
  uint32_t                         u32Register;
  stc_CPUSS_RAM0_CTL0_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_RAM0_CTL0_t;

/**
  * \brief RAM 0 status (CPUSS_RAM0_STATUS)
  */
typedef struct stc_CPUSS_RAM0_STATUS_field {
  uint32_t                         u1WB_EMPTY:1;
  uint32_t                         :31;
} stc_CPUSS_RAM0_STATUS_field_t;

typedef union un_CPUSS_RAM0_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_RAM0_STATUS_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_RAM0_STATUS_t;

/**
  * \brief RAM 0 power control (CPUSS_RAM0_PWR_MACRO_CTL)
  */
typedef struct stc_CPUSS_RAM0_PWR_MACRO_CTL_field {
  uint32_t                         u2PWR_MODE:2;
  uint32_t                         :14;
  uint32_t                         u16VECTKEYSTAT:16;
} stc_CPUSS_RAM0_PWR_MACRO_CTL_field_t;

typedef union un_CPUSS_RAM0_PWR_MACRO_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_RAM0_PWR_MACRO_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_RAM0_PWR_MACRO_CTL_t;

/**
  * \brief RAM 1 control (CPUSS_RAM1_CTL0)
  */
typedef struct stc_CPUSS_RAM1_CTL0_field {
  uint32_t                         u2SLOW_WS:2;
  uint32_t                         :6;
  uint32_t                         u2FAST_WS:2;
  uint32_t                         :6;
  uint32_t                         u1ECC_EN:1;
  uint32_t                         u1ECC_AUTO_CORRECT:1;
  uint32_t                         u1ECC_INJ_EN:1;
  uint32_t                         u1ECC_CHECK_DIS:1;
  uint32_t                         :12;
} stc_CPUSS_RAM1_CTL0_field_t;

typedef union un_CPUSS_RAM1_CTL0 {
  uint32_t                         u32Register;
  stc_CPUSS_RAM1_CTL0_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_RAM1_CTL0_t;

/**
  * \brief RAM 1 status (CPUSS_RAM1_STATUS)
  */
typedef struct stc_CPUSS_RAM1_STATUS_field {
  uint32_t                         u1WB_EMPTY:1;
  uint32_t                         :31;
} stc_CPUSS_RAM1_STATUS_field_t;

typedef union un_CPUSS_RAM1_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_RAM1_STATUS_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_RAM1_STATUS_t;

/**
  * \brief RAM 1 power control (CPUSS_RAM1_PWR_CTL)
  */
typedef struct stc_CPUSS_RAM1_PWR_CTL_field {
  uint32_t                         u2PWR_MODE:2;
  uint32_t                         :14;
  uint32_t                         u16VECTKEYSTAT:16;
} stc_CPUSS_RAM1_PWR_CTL_field_t;

typedef union un_CPUSS_RAM1_PWR_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_RAM1_PWR_CTL_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_RAM1_PWR_CTL_t;

/**
  * \brief RAM 2 control (CPUSS_RAM2_CTL0)
  */
typedef struct stc_CPUSS_RAM2_CTL0_field {
  uint32_t                         u2SLOW_WS:2;
  uint32_t                         :6;
  uint32_t                         u2FAST_WS:2;
  uint32_t                         :6;
  uint32_t                         u1ECC_EN:1;
  uint32_t                         u1ECC_AUTO_CORRECT:1;
  uint32_t                         u1ECC_INJ_EN:1;
  uint32_t                         u1ECC_CHECK_DIS:1;
  uint32_t                         :12;
} stc_CPUSS_RAM2_CTL0_field_t;

typedef union un_CPUSS_RAM2_CTL0 {
  uint32_t                         u32Register;
  stc_CPUSS_RAM2_CTL0_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_RAM2_CTL0_t;

/**
  * \brief RAM 2 status (CPUSS_RAM2_STATUS)
  */
typedef struct stc_CPUSS_RAM2_STATUS_field {
  uint32_t                         u1WB_EMPTY:1;
  uint32_t                         :31;
} stc_CPUSS_RAM2_STATUS_field_t;

typedef union un_CPUSS_RAM2_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_RAM2_STATUS_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_RAM2_STATUS_t;

/**
  * \brief RAM 2 power control (CPUSS_RAM2_PWR_CTL)
  */
typedef struct stc_CPUSS_RAM2_PWR_CTL_field {
  uint32_t                         u2PWR_MODE:2;
  uint32_t                         :14;
  uint32_t                         u16VECTKEYSTAT:16;
} stc_CPUSS_RAM2_PWR_CTL_field_t;

typedef union un_CPUSS_RAM2_PWR_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_RAM2_PWR_CTL_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_RAM2_PWR_CTL_t;

/**
  * \brief Power up delay used for all SRAM power domains (CPUSS_RAM_PWR_DELAY_CTL)
  */
typedef struct stc_CPUSS_RAM_PWR_DELAY_CTL_field {
  uint32_t                         u10UP:10;
  uint32_t                         :22;
} stc_CPUSS_RAM_PWR_DELAY_CTL_field_t;

typedef union un_CPUSS_RAM_PWR_DELAY_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_RAM_PWR_DELAY_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_RAM_PWR_DELAY_CTL_t;

/**
  * \brief ROM control (CPUSS_ROM_CTL)
  */
typedef struct stc_CPUSS_ROM_CTL_field {
  uint32_t                         u2SLOW_WS:2;
  uint32_t                         :6;
  uint32_t                         u2FAST_WS:2;
  uint32_t                         :22;
} stc_CPUSS_ROM_CTL_field_t;

typedef union un_CPUSS_ROM_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_ROM_CTL_field_t        stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_ROM_CTL_t;

/**
  * \brief ECC control (CPUSS_ECC_CTL)
  */
typedef struct stc_CPUSS_ECC_CTL_field {
  uint32_t                         u24WORD_ADDR:24;
  uint32_t                         u8PARITY:8;
} stc_CPUSS_ECC_CTL_field_t;

typedef union un_CPUSS_ECC_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_ECC_CTL_field_t        stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_ECC_CTL_t;

/**
  * \brief Product identifier and version (same as CoreSight RomTables) (CPUSS_PRODUCT_ID)
  */
typedef struct stc_CPUSS_PRODUCT_ID_field {
  uint32_t                         u12FAMILY_ID:12;
  uint32_t                         :4;
  uint32_t                         u4MAJOR_REV:4;
  uint32_t                         u4MINOR_REV:4;
  uint32_t                         :8;
} stc_CPUSS_PRODUCT_ID_field_t;

typedef union un_CPUSS_PRODUCT_ID {
  uint32_t                         u32Register;
  stc_CPUSS_PRODUCT_ID_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_PRODUCT_ID_t;

/**
  * \brief Debug port status (CPUSS_DP_STATUS)
  */
typedef struct stc_CPUSS_DP_STATUS_field {
  uint32_t                         u1SWJ_CONNECTED:1;
  uint32_t                         u1SWJ_DEBUG_EN:1;
  uint32_t                         u1SWJ_JTAG_SEL:1;
  uint32_t                         :29;
} stc_CPUSS_DP_STATUS_field_t;

typedef union un_CPUSS_DP_STATUS {
  uint32_t                         u32Register;
  stc_CPUSS_DP_STATUS_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_DP_STATUS_t;

/**
  * \brief Access port control (CPUSS_AP_CTL)
  */
typedef struct stc_CPUSS_AP_CTL_field {
  uint32_t                         u1CM0_ENABLE:1;
  uint32_t                         u1CM7_ENABLE:1;
  uint32_t                         u1SYS_ENABLE:1;
  uint32_t                         :13;
  uint32_t                         u1CM0_DISABLE:1;
  uint32_t                         u1CM7_DISABLE:1;
  uint32_t                         u1SYS_DISABLE:1;
  uint32_t                         :13;
} stc_CPUSS_AP_CTL_field_t;

typedef union un_CPUSS_AP_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_AP_CTL_field_t         stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_AP_CTL_t;

/**
  * \brief Buffer control (CPUSS_BUFF_CTL)
  */
typedef struct stc_CPUSS_BUFF_CTL_field {
  uint32_t                         u1WRITE_BUFF:1;
  uint32_t                         :31;
} stc_CPUSS_BUFF_CTL_field_t;

typedef union un_CPUSS_BUFF_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_BUFF_CTL_field_t       stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_BUFF_CTL_t;

/**
  * \brief SysTick timer control (CPUSS_SYSTICK_CTL)
  */
typedef struct stc_CPUSS_SYSTICK_CTL_field {
  uint32_t                         u24TENMS:24;
  uint32_t                         u2CLOCK_SOURCE:2;
  uint32_t                         :4;
  uint32_t                         u1SKEW:1;
  uint32_t                         u1NOREF:1;
} stc_CPUSS_SYSTICK_CTL_field_t;

typedef union un_CPUSS_SYSTICK_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_SYSTICK_CTL_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_SYSTICK_CTL_t;

/**
  * \brief Memory BIST status (CPUSS_MBIST_STAT)
  */
typedef struct stc_CPUSS_MBIST_STAT_field {
  uint32_t                         u1SFP_READY:1;
  uint32_t                         u1SFP_FAIL:1;
  uint32_t                         :30;
} stc_CPUSS_MBIST_STAT_field_t;

typedef union un_CPUSS_MBIST_STAT {
  uint32_t                         u32Register;
  stc_CPUSS_MBIST_STAT_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_MBIST_STAT_t;

/**
  * \brief Calibration support set and read (CPUSS_CAL_SUP_SET)
  */
typedef struct stc_CPUSS_CAL_SUP_SET_field {
  uint32_t                         u32DATA:32;
} stc_CPUSS_CAL_SUP_SET_field_t;

typedef union un_CPUSS_CAL_SUP_SET {
  uint32_t                         u32Register;
  stc_CPUSS_CAL_SUP_SET_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CAL_SUP_SET_t;

/**
  * \brief Calibration support clear and reset (CPUSS_CAL_SUP_CLR)
  */
typedef struct stc_CPUSS_CAL_SUP_CLR_field {
  uint32_t                         u32DATA:32;
} stc_CPUSS_CAL_SUP_CLR_field_t;

typedef union un_CPUSS_CAL_SUP_CLR {
  uint32_t                         u32Register;
  stc_CPUSS_CAL_SUP_CLR_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CAL_SUP_CLR_t;

/**
  * \brief CM0+ protection context control (CPUSS_CM0_PC_CTL)
  */
typedef struct stc_CPUSS_CM0_PC_CTL_field {
  uint32_t                         u4VALID:4;
  uint32_t                         :28;
} stc_CPUSS_CM0_PC_CTL_field_t;

typedef union un_CPUSS_CM0_PC_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_PC_CTL_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_PC_CTL_t;

/**
  * \brief CM0+ protection context 0 handler (CPUSS_CM0_PC0_HANDLER)
  */
typedef struct stc_CPUSS_CM0_PC0_HANDLER_field {
  uint32_t                         u32ADDR:32;
} stc_CPUSS_CM0_PC0_HANDLER_field_t;

typedef union un_CPUSS_CM0_PC0_HANDLER {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_PC0_HANDLER_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_PC0_HANDLER_t;

/**
  * \brief CM0+ protection context 1 handler (CPUSS_CM0_PC1_HANDLER)
  */
typedef struct stc_CPUSS_CM0_PC1_HANDLER_field {
  uint32_t                         u32ADDR:32;
} stc_CPUSS_CM0_PC1_HANDLER_field_t;

typedef union un_CPUSS_CM0_PC1_HANDLER {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_PC1_HANDLER_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_PC1_HANDLER_t;

/**
  * \brief CM0+ protection context 2 handler (CPUSS_CM0_PC2_HANDLER)
  */
typedef struct stc_CPUSS_CM0_PC2_HANDLER_field {
  uint32_t                         u32ADDR:32;
} stc_CPUSS_CM0_PC2_HANDLER_field_t;

typedef union un_CPUSS_CM0_PC2_HANDLER {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_PC2_HANDLER_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_PC2_HANDLER_t;

/**
  * \brief CM0+ protection context 3 handler (CPUSS_CM0_PC3_HANDLER)
  */
typedef struct stc_CPUSS_CM0_PC3_HANDLER_field {
  uint32_t                         u32ADDR:32;
} stc_CPUSS_CM0_PC3_HANDLER_field_t;

typedef union un_CPUSS_CM0_PC3_HANDLER {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_PC3_HANDLER_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_PC3_HANDLER_t;

/**
  * \brief Protection status (CPUSS_PROTECTION)
  */
typedef struct stc_CPUSS_PROTECTION_field {
  uint32_t                         u3STATE:3;
  uint32_t                         :29;
} stc_CPUSS_PROTECTION_field_t;

typedef union un_CPUSS_PROTECTION {
  uint32_t                         u32Register;
  stc_CPUSS_PROTECTION_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_PROTECTION_t;

/**
  * \brief ROM trim control (CPUSS_TRIM_ROM_CTL)
  */
typedef struct stc_CPUSS_TRIM_ROM_CTL_field {
  uint32_t                         u32TRIM:32;
} stc_CPUSS_TRIM_ROM_CTL_field_t;

typedef union un_CPUSS_TRIM_ROM_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_TRIM_ROM_CTL_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_TRIM_ROM_CTL_t;

/**
  * \brief RAM trim control for less than 100MHz SRAMs (CPUSS_TRIM_RAM_CTL)
  */
typedef struct stc_CPUSS_TRIM_RAM_CTL_field {
  uint32_t                         u32TRIM:32;
} stc_CPUSS_TRIM_RAM_CTL_field_t;

typedef union un_CPUSS_TRIM_RAM_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_TRIM_RAM_CTL_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_TRIM_RAM_CTL_t;

/**
  * \brief RAM trim control for 100MHz - 200MHz SRAMs (CPUSS_TRIM_RAM200_CTL)
  */
typedef struct stc_CPUSS_TRIM_RAM200_CTL_field {
  uint32_t                         u32TRIM:32;
} stc_CPUSS_TRIM_RAM200_CTL_field_t;

typedef union un_CPUSS_TRIM_RAM200_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_TRIM_RAM200_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_TRIM_RAM200_CTL_t;

/**
  * \brief RAM trim control for more than 200MHz SRAMs (CPUSS_TRIM_RAM350_CTL)
  */
typedef struct stc_CPUSS_TRIM_RAM350_CTL_field {
  uint32_t                         u32TRIM:32;
} stc_CPUSS_TRIM_RAM350_CTL_field_t;

typedef union un_CPUSS_TRIM_RAM350_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_TRIM_RAM350_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_TRIM_RAM350_CTL_t;

/**
  * \brief CM0+ system interrupt control (CPUSS_CM0_SYSTEM_INT_CTL)
  */
typedef struct stc_CPUSS_CM0_SYSTEM_INT_CTL_field {
  uint32_t                         u3CM0_CPU_INT_IDX:3;
  uint32_t                         :28;
  uint32_t                         u1CPU_INT_VALID:1;
} stc_CPUSS_CM0_SYSTEM_INT_CTL_field_t;

typedef union un_CPUSS_CM0_SYSTEM_INT_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM0_SYSTEM_INT_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM0_SYSTEM_INT_CTL_t;

/**
  * \brief CM7 0 system interrupt control (CPUSS_CM7_0_SYSTEM_INT_CTL)
  */
typedef struct stc_CPUSS_CM7_0_SYSTEM_INT_CTL_field {
  uint32_t                         u4CPU_INT_IDX:4;
  uint32_t                         :27;
  uint32_t                         u1CPU_INT_VALID:1;
} stc_CPUSS_CM7_0_SYSTEM_INT_CTL_field_t;

typedef union un_CPUSS_CM7_0_SYSTEM_INT_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_0_SYSTEM_INT_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_0_SYSTEM_INT_CTL_t;

/**
  * \brief CM7 1 system interrupt control (CPUSS_CM7_1_SYSTEM_INT_CTL)
  */
typedef struct stc_CPUSS_CM7_1_SYSTEM_INT_CTL_field {
  uint32_t                         u4CPU_INT_IDX:4;
  uint32_t                         :27;
  uint32_t                         u1CPU_INT_VALID:1;
} stc_CPUSS_CM7_1_SYSTEM_INT_CTL_field_t;

typedef union un_CPUSS_CM7_1_SYSTEM_INT_CTL {
  uint32_t                         u32Register;
  stc_CPUSS_CM7_1_SYSTEM_INT_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_CPUSS_CM7_1_SYSTEM_INT_CTL_t;



/**
  * \brief CPU subsystem (CPUSS) (CPUSS)
  */
typedef struct stc_CPUSS {
  un_CPUSS_IDENTITY_t              unIDENTITY;         /*!< 0x00000000 Identity */
  un_CPUSS_CM7_0_STATUS_t          unCM7_0_STATUS;     /*!< 0x00000004 CM7 0 status */
  un_CPUSS_FAST_0_CLOCK_CTL_t      unFAST_0_CLOCK_CTL; /*!< 0x00000008 Fast 0 clock control */
  un_CPUSS_CM7_0_CTL_t             unCM7_0_CTL;        /*!< 0x0000000C CM7 0 control */
  uint32_t                         au32Reserved[60];
  un_CPUSS_CM7_0_INT_STATUS_t      unCM7_0_INT_STATUS[16]; /*!< 0x00000100 CM7 0 interrupt status */
  uint32_t                         au32Reserved1[48];
  un_CPUSS_CM7_0_VECTOR_TABLE_BASE_t unCM7_0_VECTOR_TABLE_BASE; /*!< 0x00000200 CM7 0 vector table base */
  uint32_t                         au32Reserved2[15];
  un_CPUSS_CM7_0_NMI_CTL_t         unCM7_0_NMI_CTL[4]; /*!< 0x00000240 CM7 0 NMI control */
  uint32_t                         au32Reserved3[44];
  un_CPUSS_UDB_PWR_CTL_t           unUDB_PWR_CTL;      /*!< 0x00000300 UDB power control */
  un_CPUSS_UDB_PWR_DELAY_CTL_t     unUDB_PWR_DELAY_CTL; /*!< 0x00000304 UDB power control */
  uint32_t                         au32Reserved4[6];
  un_CPUSS_TRC_DBG_CLOCK_CTL_t     unTRC_DBG_CLOCK_CTL; /*!< 0x00000320 Trace and debug clock control */
  uint32_t                         au32Reserved5[56];
  un_CPUSS_CM7_1_STATUS_t          unCM7_1_STATUS;     /*!< 0x00000404 CM7 1status */
  un_CPUSS_FAST_1_CLOCK_CTL_t      unFAST_1_CLOCK_CTL; /*!< 0x00000408 Fast 1 clock control */
  un_CPUSS_CM7_1_CTL_t             unCM7_1_CTL;        /*!< 0x0000040C CM7 1 control */
  uint32_t                         au32Reserved6[60];
  un_CPUSS_CM7_1_INT_STATUS_t      unCM7_1_INT_STATUS[16]; /*!< 0x00000500 CM7 1 interrupt status */
  uint32_t                         au32Reserved7[48];
  un_CPUSS_CM7_1_VECTOR_TABLE_BASE_t unCM7_1_VECTOR_TABLE_BASE; /*!< 0x00000600 CM7 1 vector table base */
  uint32_t                         au32Reserved8[15];
  un_CPUSS_CM7_1_NMI_CTL_t         unCM7_1_NMI_CTL[4]; /*!< 0x00000640 CM7 1 NMI control */
  uint32_t                         au32Reserved9[620];
  un_CPUSS_CM0_CTL_t               unCM0_CTL;          /*!< 0x00001000 CM0+ control */
  un_CPUSS_CM0_STATUS_t            unCM0_STATUS;       /*!< 0x00001004 CM0+ status */
  un_CPUSS_SLOW_CLOCK_CTL_t        unSLOW_CLOCK_CTL;   /*!< 0x00001008 Slow clock control */
  un_CPUSS_PERI_CLOCK_CTL_t        unPERI_CLOCK_CTL;   /*!< 0x0000100C Peripheral interconnect clock control */
  un_CPUSS_MEM_CLOCK_CTL_t         unMEM_CLOCK_CTL;    /*!< 0x00001010 Memory clock control */
  uint32_t                         au32Reserved10[59];
  un_CPUSS_CM0_INT0_STATUS_t       unCM0_INT0_STATUS;  /*!< 0x00001100 CM0+ interrupt 0 status */
  un_CPUSS_CM0_INT1_STATUS_t       unCM0_INT1_STATUS;  /*!< 0x00001104 CM0+ interrupt 1 status */
  un_CPUSS_CM0_INT2_STATUS_t       unCM0_INT2_STATUS;  /*!< 0x00001108 CM0+ interrupt 2 status */
  un_CPUSS_CM0_INT3_STATUS_t       unCM0_INT3_STATUS;  /*!< 0x0000110C CM0+ interrupt 3 status */
  un_CPUSS_CM0_INT4_STATUS_t       unCM0_INT4_STATUS;  /*!< 0x00001110 CM0+ interrupt 4 status */
  un_CPUSS_CM0_INT5_STATUS_t       unCM0_INT5_STATUS;  /*!< 0x00001114 CM0+ interrupt 5 status */
  un_CPUSS_CM0_INT6_STATUS_t       unCM0_INT6_STATUS;  /*!< 0x00001118 CM0+ interrupt 6 status */
  un_CPUSS_CM0_INT7_STATUS_t       unCM0_INT7_STATUS;  /*!< 0x0000111C CM0+ interrupt 7 status */
  un_CPUSS_CM0_VECTOR_TABLE_BASE_t unCM0_VECTOR_TABLE_BASE; /*!< 0x00001120 CM0+ vector table base */
  uint32_t                         au32Reserved11[7];
  un_CPUSS_CM0_NMI_CTL_t           unCM0_NMI_CTL[4];   /*!< 0x00001140 CM0+ NMI control */
  uint32_t                         au32Reserved12[44];
  un_CPUSS_CM7_0_PWR_CTL_t         unCM7_0_PWR_CTL;    /*!< 0x00001200 CM7 0 power control */
  un_CPUSS_CM7_0_PWR_DELAY_CTL_t   unCM7_0_PWR_DELAY_CTL; /*!< 0x00001204 CM7 0 power delay control */
  uint32_t                         au32Reserved13[2];
  un_CPUSS_CM7_1_PWR_CTL_t         unCM7_1_PWR_CTL;    /*!< 0x00001210 CM7 1 power control */
  un_CPUSS_CM7_1_PWR_DELAY_CTL_t   unCM7_1_PWR_DELAY_CTL; /*!< 0x00001214 CM7 1 power delay control */
  uint32_t                         au32Reserved14[58];
  un_CPUSS_RAM0_CTL0_t             unRAM0_CTL0;        /*!< 0x00001300 RAM 0 control */
  un_CPUSS_RAM0_STATUS_t           unRAM0_STATUS;      /*!< 0x00001304 RAM 0 status */
  uint32_t                         au32Reserved15[14];
  un_CPUSS_RAM0_PWR_MACRO_CTL_t    unRAM0_PWR_MACRO_CTL[16]; /*!< 0x00001340 RAM 0 power control */
  un_CPUSS_RAM1_CTL0_t             unRAM1_CTL0;        /*!< 0x00001380 RAM 1 control */
  un_CPUSS_RAM1_STATUS_t           unRAM1_STATUS;      /*!< 0x00001384 RAM 1 status */
  un_CPUSS_RAM1_PWR_CTL_t          unRAM1_PWR_CTL;     /*!< 0x00001388 RAM 1 power control */
  uint32_t                         au32Reserved16[5];
  un_CPUSS_RAM2_CTL0_t             unRAM2_CTL0;        /*!< 0x000013A0 RAM 2 control */
  un_CPUSS_RAM2_STATUS_t           unRAM2_STATUS;      /*!< 0x000013A4 RAM 2 status */
  un_CPUSS_RAM2_PWR_CTL_t          unRAM2_PWR_CTL;     /*!< 0x000013A8 RAM 2 power control */
  uint32_t                         au32Reserved17[5];
  un_CPUSS_RAM_PWR_DELAY_CTL_t     unRAM_PWR_DELAY_CTL; /*!< 0x000013C0 Power up delay used for all SRAM power domains */
  un_CPUSS_ROM_CTL_t               unROM_CTL;          /*!< 0x000013C4 ROM control */
  un_CPUSS_ECC_CTL_t               unECC_CTL;          /*!< 0x000013C8 ECC control */
  uint32_t                         au32Reserved18[13];
  un_CPUSS_PRODUCT_ID_t            unPRODUCT_ID;       /*!< 0x00001400 Product identifier and version (same as CoreSight
                                                                                RomTables) */
  uint32_t                         au32Reserved19[3];
  un_CPUSS_DP_STATUS_t             unDP_STATUS;        /*!< 0x00001410 Debug port status */
  un_CPUSS_AP_CTL_t                unAP_CTL;           /*!< 0x00001414 Access port control */
  uint32_t                         au32Reserved20[58];
  un_CPUSS_BUFF_CTL_t              unBUFF_CTL;         /*!< 0x00001500 Buffer control */
  uint32_t                         au32Reserved21[63];
  un_CPUSS_SYSTICK_CTL_t           unSYSTICK_CTL;      /*!< 0x00001600 SysTick timer control */
  uint32_t                         au32Reserved22[64];
  un_CPUSS_MBIST_STAT_t            unMBIST_STAT;       /*!< 0x00001704 Memory BIST status */
  uint32_t                         au32Reserved23[62];
  un_CPUSS_CAL_SUP_SET_t           unCAL_SUP_SET;      /*!< 0x00001800 Calibration support set and read */
  un_CPUSS_CAL_SUP_CLR_t           unCAL_SUP_CLR;      /*!< 0x00001804 Calibration support clear and reset */
  uint32_t                         au32Reserved24[510];
  un_CPUSS_CM0_PC_CTL_t            unCM0_PC_CTL;       /*!< 0x00002000 CM0+ protection context control */
  uint32_t                         au32Reserved25[15];
  un_CPUSS_CM0_PC0_HANDLER_t       unCM0_PC0_HANDLER;  /*!< 0x00002040 CM0+ protection context 0 handler */
  un_CPUSS_CM0_PC1_HANDLER_t       unCM0_PC1_HANDLER;  /*!< 0x00002044 CM0+ protection context 1 handler */
  un_CPUSS_CM0_PC2_HANDLER_t       unCM0_PC2_HANDLER;  /*!< 0x00002048 CM0+ protection context 2 handler */
  un_CPUSS_CM0_PC3_HANDLER_t       unCM0_PC3_HANDLER;  /*!< 0x0000204C CM0+ protection context 3 handler */
  uint32_t                         au32Reserved26[29];
  un_CPUSS_PROTECTION_t            unPROTECTION;       /*!< 0x000020C4 Protection status */
  uint32_t                         au32Reserved27[14];
  un_CPUSS_TRIM_ROM_CTL_t          unTRIM_ROM_CTL;     /*!< 0x00002100 ROM trim control */
  un_CPUSS_TRIM_RAM_CTL_t          unTRIM_RAM_CTL;     /*!< 0x00002104 RAM trim control for less than 100MHz SRAMs */
  un_CPUSS_TRIM_RAM200_CTL_t       unTRIM_RAM200_CTL;  /*!< 0x00002108 RAM trim control for 100MHz - 200MHz SRAMs */
  un_CPUSS_TRIM_RAM350_CTL_t       unTRIM_RAM350_CTL;  /*!< 0x0000210C RAM trim control for more than 200MHz SRAMs */
  uint32_t                         au32Reserved28[6076];
  un_CPUSS_CM0_SYSTEM_INT_CTL_t    unCM0_SYSTEM_INT_CTL[1023]; /*!< 0x00008000 CM0+ system interrupt control */
  uint32_t                         au32Reserved29[1025];
  un_CPUSS_CM7_0_SYSTEM_INT_CTL_t  unCM7_0_SYSTEM_INT_CTL[1023]; /*!< 0x0000A000 CM7 0 system interrupt control */
  uint32_t                         au32Reserved30[1025];
  un_CPUSS_CM7_1_SYSTEM_INT_CTL_t  unCM7_1_SYSTEM_INT_CTL[1023]; /*!< 0x0000C000 CM7 1 system interrupt control */
} stc_CPUSS_t;

/**
  * \brief Analog control register. (PASS_SAR_CTL)
  */
typedef struct stc_PASS_SAR_CTL_field {
  uint32_t                         u8PWRUP_TIME:8;
  uint32_t                         u1IDLE_PWRDWN:1;
  uint32_t                         u1MSB_STRETCH:1;
  uint32_t                         u1HALF_LSB:1;
  uint32_t                         :18;
  uint32_t                         u1SARMUX_EN:1;
  uint32_t                         u1ADC_EN:1;
  uint32_t                         u1ENABLED:1;
} stc_PASS_SAR_CTL_field_t;

typedef union un_PASS_SAR_CTL {
  uint32_t                         u32Register;
  stc_PASS_SAR_CTL_field_t         stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CTL_t;

/**
  * \brief Diagnostic Reference control register. (PASS_SAR_DIAG_CTL)
  */
typedef struct stc_PASS_SAR_DIAG_CTL_field {
  uint32_t                         u4DIAG_SEL:4;
  uint32_t                         :27;
  uint32_t                         u1DIAG_EN:1;
} stc_PASS_SAR_DIAG_CTL_field_t;

typedef union un_PASS_SAR_DIAG_CTL {
  uint32_t                         u32Register;
  stc_PASS_SAR_DIAG_CTL_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_DIAG_CTL_t;

/**
  * \brief Preconditioning control register. (PASS_SAR_PRECOND_CTL)
  */
typedef struct stc_PASS_SAR_PRECOND_CTL_field {
  uint32_t                         u4PRECOND_TIME:4;
  uint32_t                         :28;
} stc_PASS_SAR_PRECOND_CTL_field_t;

typedef union un_PASS_SAR_PRECOND_CTL {
  uint32_t                         u32Register;
  stc_PASS_SAR_PRECOND_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_PRECOND_CTL_t;

/**
  * \brief Current analog calibration values (PASS_SAR_ANA_CAL)
  */
typedef struct stc_PASS_SAR_ANA_CAL_field {
  uint32_t                         u8AOFFSET:8;
  uint32_t                         :8;
  uint32_t                         u5AGAIN:5;
  uint32_t                         :11;
} stc_PASS_SAR_ANA_CAL_field_t;

typedef union un_PASS_SAR_ANA_CAL {
  uint32_t                         u32Register;
  stc_PASS_SAR_ANA_CAL_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_ANA_CAL_t;

/**
  * \brief Current digital calibration values (PASS_SAR_DIG_CAL)
  */
typedef struct stc_PASS_SAR_DIG_CAL_field {
  uint32_t                         u12DOFFSET:12;
  uint32_t                         :4;
  uint32_t                         u6DGAIN:6;
  uint32_t                         :10;
} stc_PASS_SAR_DIG_CAL_field_t;

typedef union un_PASS_SAR_DIG_CAL {
  uint32_t                         u32Register;
  stc_PASS_SAR_DIG_CAL_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_DIG_CAL_t;

/**
  * \brief Alternate analog calibration values (PASS_SAR_ANA_CAL_ALT)
  */
typedef struct stc_PASS_SAR_ANA_CAL_ALT_field {
  uint32_t                         u8AOFFSET:8;
  uint32_t                         :8;
  uint32_t                         u5AGAIN:5;
  uint32_t                         :11;
} stc_PASS_SAR_ANA_CAL_ALT_field_t;

typedef union un_PASS_SAR_ANA_CAL_ALT {
  uint32_t                         u32Register;
  stc_PASS_SAR_ANA_CAL_ALT_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_ANA_CAL_ALT_t;

/**
  * \brief Alternate digital calibration values (PASS_SAR_DIG_CAL_ALT)
  */
typedef struct stc_PASS_SAR_DIG_CAL_ALT_field {
  uint32_t                         u12DOFFSET:12;
  uint32_t                         :4;
  uint32_t                         u6DGAIN:6;
  uint32_t                         :10;
} stc_PASS_SAR_DIG_CAL_ALT_field_t;

typedef union un_PASS_SAR_DIG_CAL_ALT {
  uint32_t                         u32Register;
  stc_PASS_SAR_DIG_CAL_ALT_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_DIG_CAL_ALT_t;

/**
  * \brief Calibration update command (PASS_SAR_CAL_UPD_CMD)
  */
typedef struct stc_PASS_SAR_CAL_UPD_CMD_field {
  uint32_t                         u1UPDATE:1;
  uint32_t                         :31;
} stc_PASS_SAR_CAL_UPD_CMD_field_t;

typedef union un_PASS_SAR_CAL_UPD_CMD {
  uint32_t                         u32Register;
  stc_PASS_SAR_CAL_UPD_CMD_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CAL_UPD_CMD_t;

/**
  * \brief Trigger pending status (PASS_SAR_TR_PEND)
  */
typedef struct stc_PASS_SAR_TR_PEND_field {
  uint32_t                         u32TR_PEND:32;
} stc_PASS_SAR_TR_PEND_field_t;

typedef union un_PASS_SAR_TR_PEND {
  uint32_t                         u32Register;
  stc_PASS_SAR_TR_PEND_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_TR_PEND_t;

/**
  * \brief Channel working data register 'valid' bits (PASS_SAR_WORK_VALID)
  */
typedef struct stc_PASS_SAR_WORK_VALID_field {
  uint32_t                         u32WORK_VALID:32;
} stc_PASS_SAR_WORK_VALID_field_t;

typedef union un_PASS_SAR_WORK_VALID {
  uint32_t                         u32Register;
  stc_PASS_SAR_WORK_VALID_field_t  stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_WORK_VALID_t;

/**
  * \brief Range detected (PASS_SAR_WORK_RANGE)
  */
typedef struct stc_PASS_SAR_WORK_RANGE_field {
  uint32_t                         u32RANGE:32;
} stc_PASS_SAR_WORK_RANGE_field_t;

typedef union un_PASS_SAR_WORK_RANGE {
  uint32_t                         u32Register;
  stc_PASS_SAR_WORK_RANGE_field_t  stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_WORK_RANGE_t;

/**
  * \brief Range detect above Hi flag (PASS_SAR_WORK_RANGE_HI)
  */
typedef struct stc_PASS_SAR_WORK_RANGE_HI_field {
  uint32_t                         u32ABOVE_HI:32;
} stc_PASS_SAR_WORK_RANGE_HI_field_t;

typedef union un_PASS_SAR_WORK_RANGE_HI {
  uint32_t                         u32Register;
  stc_PASS_SAR_WORK_RANGE_HI_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_WORK_RANGE_HI_t;

/**
  * \brief Pulse detected (PASS_SAR_WORK_PULSE)
  */
typedef struct stc_PASS_SAR_WORK_PULSE_field {
  uint32_t                         u32PULSE:32;
} stc_PASS_SAR_WORK_PULSE_field_t;

typedef union un_PASS_SAR_WORK_PULSE {
  uint32_t                         u32Register;
  stc_PASS_SAR_WORK_PULSE_field_t  stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_WORK_PULSE_t;

/**
  * \brief Channel result data register 'valid' bits (PASS_SAR_RESULT_VALID)
  */
typedef struct stc_PASS_SAR_RESULT_VALID_field {
  uint32_t                         u32RESULT_VALID:32;
} stc_PASS_SAR_RESULT_VALID_field_t;

typedef union un_PASS_SAR_RESULT_VALID {
  uint32_t                         u32Register;
  stc_PASS_SAR_RESULT_VALID_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_RESULT_VALID_t;

/**
  * \brief Channel Range above Hi flags (PASS_SAR_RESULT_RANGE_HI)
  */
typedef struct stc_PASS_SAR_RESULT_RANGE_HI_field {
  uint32_t                         u32ABOVE_HI:32;
} stc_PASS_SAR_RESULT_RANGE_HI_field_t;

typedef union un_PASS_SAR_RESULT_RANGE_HI {
  uint32_t                         u32Register;
  stc_PASS_SAR_RESULT_RANGE_HI_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_RESULT_RANGE_HI_t;

/**
  * \brief Current status of internal SAR registers (mostly for debug) (PASS_SAR_STATUS)
  */
typedef struct stc_PASS_SAR_STATUS_field {
  uint32_t                         u5CUR_CHAN:5;
  uint32_t                         :3;
  uint32_t                         u3CUR_PRIO:3;
  uint32_t                         :1;
  uint32_t                         u2CUR_PREEMPT_TYPE:2;
  uint32_t                         :15;
  uint32_t                         u1DBG_FREEZE:1;
  uint32_t                         u1PWRUP_BUSY:1;
  uint32_t                         u1BUSY:1;
} stc_PASS_SAR_STATUS_field_t;

typedef union un_PASS_SAR_STATUS {
  uint32_t                         u32Register;
  stc_PASS_SAR_STATUS_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_STATUS_t;

/**
  * \brief Current averaging status (for debug) (PASS_SAR_AVG_STAT)
  */
typedef struct stc_PASS_SAR_AVG_STAT_field {
  uint32_t                         u20CUR_AVG_ACCU:20;
  uint32_t                         :4;
  uint32_t                         u8CUR_AVG_CNT:8;
} stc_PASS_SAR_AVG_STAT_field_t;

typedef union un_PASS_SAR_AVG_STAT {
  uint32_t                         u32Register;
  stc_PASS_SAR_AVG_STAT_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_AVG_STAT_t;



/**
  * \brief PASS control register (PASS_PASS_CTL)
  */
typedef struct stc_PASS_PASS_CTL_field {
  uint32_t                         u1SUPPLY_MON_EN_A:1;
  uint32_t                         u1SUPPLY_MON_LVL_A:1;
  uint32_t                         :2;
  uint32_t                         u1SUPPLY_MON_EN_B:1;
  uint32_t                         u1SUPPLY_MON_LVL_B:1;
  uint32_t                         :15;
  uint32_t                         u2REFBUF_MODE:2;
  uint32_t                         :5;
  uint32_t                         u4DBG_FREEZE_EN:4;
} stc_PASS_PASS_CTL_field_t;

typedef union un_PASS_PASS_CTL {
  uint32_t                         u32Register;
  stc_PASS_PASS_CTL_field_t        stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_PASS_CTL_t;

/**
  * \brief per SAR generic input trigger select (PASS_SAR_TR_IN_SEL)
  */
typedef struct stc_PASS_SAR_TR_IN_SEL_field {
  uint32_t                         u4IN0_SEL:4;
  uint32_t                         u4IN1_SEL:4;
  uint32_t                         u4IN2_SEL:4;
  uint32_t                         u4IN3_SEL:4;
  uint32_t                         u4IN4_SEL:4;
  uint32_t                         :12;
} stc_PASS_SAR_TR_IN_SEL_field_t;

typedef union un_PASS_SAR_TR_IN_SEL {
  uint32_t                         u32Register;
  stc_PASS_SAR_TR_IN_SEL_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_TR_IN_SEL_t;

/**
  * \brief per SAR generic output trigger select (PASS_SAR_TR_OUT_SEL)
  */
typedef struct stc_PASS_SAR_TR_OUT_SEL_field {
  uint32_t                         u6OUT0_SEL:6;
  uint32_t                         :2;
  uint32_t                         u6OUT1_SEL:6;
  uint32_t                         :18;
} stc_PASS_SAR_TR_OUT_SEL_field_t;

typedef union un_PASS_SAR_TR_OUT_SEL {
  uint32_t                         u32Register;
  stc_PASS_SAR_TR_OUT_SEL_field_t  stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_TR_OUT_SEL_t;

/**
  * \brief Trigger control. (PASS_SAR_CH_TR_CTL)
  */
typedef struct stc_PASS_SAR_CH_TR_CTL_field {
  uint32_t                         u3SEL:3;
  uint32_t                         :1;
  uint32_t                         u3PRIO:3;
  uint32_t                         :1;
  uint32_t                         u2PREEMPT_TYPE:2;
  uint32_t                         :1;
  uint32_t                         u1GROUP_END:1;
  uint32_t                         :19;
  uint32_t                         u1DONE_LEVEL:1;
} stc_PASS_SAR_CH_TR_CTL_field_t;

typedef union un_PASS_SAR_CH_TR_CTL {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_TR_CTL_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_TR_CTL_t;
/**
  * \brief Sample control. (PASS_SAR_CH_SAMPLE_CTL)
  */
typedef struct stc_PASS_SAR_CH_SAMPLE_CTL_field {
  uint32_t                         u6PIN_ADDR:6;
  uint32_t                         u2PORT_ADDR:2;
  uint32_t                         u3EXT_MUX_SEL:3;
  uint32_t                         u1EXT_MUX_EN:1;
  uint32_t                         u2PRECOND_MODE:2;
  uint32_t                         u2OVERLAP_DIAG:2;
  uint32_t                         u12SAMPLE_TIME:12;
  uint32_t                         :3;
  uint32_t                         u1ALT_CAL:1;
} stc_PASS_SAR_CH_SAMPLE_CTL_field_t;

typedef union un_PASS_SAR_CH_SAMPLE_CTL {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_SAMPLE_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_SAMPLE_CTL_t;

/**
  * \brief Post processing control (PASS_SAR_CH_POST_CTL)
  */
typedef struct stc_PASS_SAR_CH_POST_CTL_field {
  uint32_t                         u3POST_PROC:3;
  uint32_t                         :3;
  uint32_t                         u1LEFT_ALIGN:1;
  uint32_t                         u1SIGN_EXT:1;
  uint32_t                         u8AVG_CNT:8;
  uint32_t                         u5SHIFT_R:5;
  uint32_t                         :1;
  uint32_t                         u2RANGE_MODE:2;
  uint32_t                         :1;
  uint32_t                         u1TR_DONE_GRP_VIO:1;
  uint32_t                         :6;
} stc_PASS_SAR_CH_POST_CTL_field_t;

typedef union un_PASS_SAR_CH_POST_CTL {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_POST_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_POST_CTL_t;

/**
  * \brief Range thresholds (PASS_SAR_CH_RANGE_CTL)
  */
typedef struct stc_PASS_SAR_CH_RANGE_CTL_field {
  uint32_t                         u16RANGE_LO:16;
  uint32_t                         u16RANGE_HI:16;
} stc_PASS_SAR_CH_RANGE_CTL_field_t;

typedef union un_PASS_SAR_CH_RANGE_CTL {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_RANGE_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_RANGE_CTL_t;

/**
  * \brief Interrupt request register. (PASS_SAR_CH_INTR)
  */
typedef struct stc_PASS_SAR_CH_INTR_field {
  uint32_t                         u1GRP_DONE:1;
  uint32_t                         u1GRP_CANCELLED:1;
  uint32_t                         u1GRP_OVERFLOW:1;
  uint32_t                         :5;
  uint32_t                         u1CH_RANGE:1;
  uint32_t                         u1CH_PULSE:1;
  uint32_t                         u1CH_OVERFLOW:1;
  uint32_t                         :21;
} stc_PASS_SAR_CH_INTR_field_t;

typedef union un_PASS_SAR_CH_INTR {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_INTR_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_INTR_t;

/**
  * \brief Interrupt set request register (PASS_SAR_CH_INTR_SET)
  */
typedef struct stc_PASS_SAR_CH_INTR_SET_field {
  uint32_t                         u1GRP_DONE_SET:1;
  uint32_t                         u1GRP_CANCELLED_SET:1;
  uint32_t                         u1GRP_OVERFLOW_SET:1;
  uint32_t                         :5;
  uint32_t                         u1CH_RANGE_SET:1;
  uint32_t                         u1CH_PULSE_SET:1;
  uint32_t                         u1CH_OVERFLOW_SET:1;
  uint32_t                         :21;
} stc_PASS_SAR_CH_INTR_SET_field_t;

typedef union un_PASS_SAR_CH_INTR_SET {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_INTR_SET_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_INTR_SET_t;

/**
  * \brief Interrupt mask register. (PASS_SAR_CH_INTR_MASK)
  */
typedef struct stc_PASS_SAR_CH_INTR_MASK_field {
  uint32_t                         u1GRP_DONE_MASK:1;
  uint32_t                         u1GRP_CANCELLED_MASK:1;
  uint32_t                         u1GRP_OVERFLOW_MASK:1;
  uint32_t                         :5;
  uint32_t                         u1CH_RANGE_MASK:1;
  uint32_t                         u1CH_PULSE_MASK:1;
  uint32_t                         u1CH_OVERFLOW_MASK:1;
  uint32_t                         :21;
} stc_PASS_SAR_CH_INTR_MASK_field_t;

typedef union un_PASS_SAR_CH_INTR_MASK {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_INTR_MASK_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_INTR_MASK_t;

/**
  * \brief Interrupt masked request register (PASS_SAR_CH_INTR_MASKED)
  */
typedef struct stc_PASS_SAR_CH_INTR_MASKED_field {
  uint32_t                         u1GRP_DONE_MASKED:1;
  uint32_t                         u1GRP_CANCELLED_MASKED:1;
  uint32_t                         u1GRP_OVERFLOW_MASKED:1;
  uint32_t                         :5;
  uint32_t                         u1CH_RANGE_MASKED:1;
  uint32_t                         u1CH_PULSE_MASKED:1;
  uint32_t                         u1CH_OVERFLOW_MASKED:1;
  uint32_t                         :21;
} stc_PASS_SAR_CH_INTR_MASKED_field_t;

typedef union un_PASS_SAR_CH_INTR_MASKED {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_INTR_MASKED_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_INTR_MASKED_t;

/**
  * \brief Working data register (PASS_SAR_CH_WORK)
  */
typedef struct stc_PASS_SAR_CH_WORK_field {
  uint32_t                         u16WORK:16;
  uint32_t                         :12;
  uint32_t                         u1ABOVE_HI_MIR:1;
  uint32_t                         u1RANGE_MIR:1;
  uint32_t                         u1PULSE_MIR:1;
  uint32_t                         u1VALID_MIR:1;
} stc_PASS_SAR_CH_WORK_field_t;

typedef union un_PASS_SAR_CH_WORK {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_WORK_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_WORK_t;

/**
  * \brief Result data register (PASS_SAR_CH_RESULT)
  */
typedef struct stc_PASS_SAR_CH_RESULT_field {
  uint32_t                         u16RESULT:16;
  uint32_t                         :12;
  uint32_t                         u1ABOVE_HI_MIR:1;
  uint32_t                         u1RANGE_INTR_MIR:1;
  uint32_t                         u1PULSE_INTR_MIR:1;
  uint32_t                         u1VALID_MIR:1;
} stc_PASS_SAR_CH_RESULT_field_t;

typedef union un_PASS_SAR_CH_RESULT {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_RESULT_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_RESULT_t;

/**
  * \brief Group status register (PASS_SAR_CH_GRP_STAT)
  */
typedef struct stc_PASS_SAR_CH_GRP_STAT_field {
  uint32_t                         u1GRP_COMPLETE:1;
  uint32_t                         u1GRP_CANCELLED:1;
  uint32_t                         u1GRP_OVERFLOW:1;
  uint32_t                         :5;
  uint32_t                         u1CH_RANGE_COMPLETE:1;
  uint32_t                         u1CH_PULSE_COMPLETE:1;
  uint32_t                         u1CH_OVERFLOW:1;
  uint32_t                         :5;
  uint32_t                         u1GRP_BUSY:1;
  uint32_t                         :15;
} stc_PASS_SAR_CH_GRP_STAT_field_t;

typedef union un_PASS_SAR_CH_GRP_STAT {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_GRP_STAT_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_GRP_STAT_t;

/**
  * \brief Enable register (PASS_SAR_CH_ENABLE)
  */
typedef struct stc_PASS_SAR_CH_ENABLE_field {
  uint32_t                         u1CHAN_EN:1;
  uint32_t                         :31;
} stc_PASS_SAR_CH_ENABLE_field_t;

typedef union un_PASS_SAR_CH_ENABLE {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_ENABLE_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_ENABLE_t;

/**
  * \brief Software triggers (PASS_SAR_CH_TR_CMD)
  */
typedef struct stc_PASS_SAR_CH_TR_CMD_field {
  uint32_t                         u1START:1;
  uint32_t                         :31;
} stc_PASS_SAR_CH_TR_CMD_field_t;

typedef union un_PASS_SAR_CH_TR_CMD {
  uint32_t                         u32Register;
  stc_PASS_SAR_CH_TR_CMD_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PASS_SAR_CH_TR_CMD_t;

/**
  * \brief Channel structure (PASS_SAR_CH)
  */
typedef struct stc_PASS_SAR_CH {
  un_PASS_SAR_CH_TR_CTL_t          unTR_CTL;           /*!< 0x00000000 Trigger control. */
  un_PASS_SAR_CH_SAMPLE_CTL_t      unSAMPLE_CTL;       /*!< 0x00000004 Sample control. */
  un_PASS_SAR_CH_POST_CTL_t        unPOST_CTL;         /*!< 0x00000008 Post processing control */
  un_PASS_SAR_CH_RANGE_CTL_t       unRANGE_CTL;        /*!< 0x0000000C Range thresholds */
  un_PASS_SAR_CH_INTR_t            unINTR;             /*!< 0x00000010 Interrupt request register. */
  un_PASS_SAR_CH_INTR_SET_t        unINTR_SET;         /*!< 0x00000014 Interrupt set request register */
  un_PASS_SAR_CH_INTR_MASK_t       unINTR_MASK;        /*!< 0x00000018 Interrupt mask register. */
  un_PASS_SAR_CH_INTR_MASKED_t     unINTR_MASKED;      /*!< 0x0000001C Interrupt masked request register */
  un_PASS_SAR_CH_WORK_t            unWORK;             /*!< 0x00000020 Working data register */
  un_PASS_SAR_CH_RESULT_t          unRESULT;           /*!< 0x00000024 Result data register */
  un_PASS_SAR_CH_GRP_STAT_t        unGRP_STAT;         /*!< 0x00000028 Group status register */
  uint32_t                         au32Reserved[3];
  un_PASS_SAR_CH_ENABLE_t          unENABLE;           /*!< 0x00000038 Enable register */
  un_PASS_SAR_CH_TR_CMD_t          unTR_CMD;           /*!< 0x0000003C Software triggers */
} stc_PASS_SAR_CH_t;


/**
  * \brief SAR ADC with Sequencer for S40E (PASS_SAR)
  */
typedef struct stc_PASS_SAR {
  un_PASS_SAR_CTL_t                unCTL;              /*!< 0x00000000 Analog control register. */
  un_PASS_SAR_DIAG_CTL_t           unDIAG_CTL;         /*!< 0x00000004 Diagnostic Reference control register. */
  uint32_t                         au32Reserved[2];
  un_PASS_SAR_PRECOND_CTL_t        unPRECOND_CTL;      /*!< 0x00000010 Preconditioning control register. */
  uint32_t                         au32Reserved1[27];
  un_PASS_SAR_ANA_CAL_t            unANA_CAL;          /*!< 0x00000080 Current analog calibration values */
  un_PASS_SAR_DIG_CAL_t            unDIG_CAL;          /*!< 0x00000084 Current digital calibration values */
  uint32_t                         au32Reserved2[2];
  un_PASS_SAR_ANA_CAL_ALT_t        unANA_CAL_ALT;      /*!< 0x00000090 Alternate analog calibration values */
  un_PASS_SAR_DIG_CAL_ALT_t        unDIG_CAL_ALT;      /*!< 0x00000094 Alternate digital calibration values */
  un_PASS_SAR_CAL_UPD_CMD_t        unCAL_UPD_CMD;      /*!< 0x00000098 Calibration update command */
  uint32_t                         au32Reserved3[25];
  un_PASS_SAR_TR_PEND_t            unTR_PEND;          /*!< 0x00000100 Trigger pending status */
  uint32_t                         au32Reserved4[31];
  un_PASS_SAR_WORK_VALID_t         unWORK_VALID;       /*!< 0x00000180 Channel working data register 'valid' bits */
  un_PASS_SAR_WORK_RANGE_t         unWORK_RANGE;       /*!< 0x00000184 Range detected */
  un_PASS_SAR_WORK_RANGE_HI_t      unWORK_RANGE_HI;    /*!< 0x00000188 Range detect above Hi flag */
  un_PASS_SAR_WORK_PULSE_t         unWORK_PULSE;       /*!< 0x0000018C Pulse detected */
  uint32_t                         au32Reserved5[4];
  un_PASS_SAR_RESULT_VALID_t       unRESULT_VALID;     /*!< 0x000001A0 Channel result data register 'valid' bits */
  un_PASS_SAR_RESULT_RANGE_HI_t    unRESULT_RANGE_HI;  /*!< 0x000001A4 Channel Range above Hi flags */
  uint32_t                         au32Reserved6[22];
  un_PASS_SAR_STATUS_t             unSTATUS;           /*!< 0x00000200 Current status of internal SAR registers (mostly for
                                                                                debug) */
  un_PASS_SAR_AVG_STAT_t           unAVG_STAT;         /*!< 0x00000204 Current averaging status (for debug) */
  uint32_t                         au32Reserved7[382];
  stc_PASS_SAR_CH_t                CH[32];             /*!< 0x00000800 Channel structure */
} stc_PASS_SAR_t;                                      /*!< Size = 4096 (0x1000) */

/**
  * \brief PASS top-level MMIO (Generic Triggers) (PASS_EPASS_MMIO)
  */
typedef struct stc_PASS_EPASS_MMIO {
  un_PASS_PASS_CTL_t               unPASS_CTL;         /*!< 0x00000000 PASS control register */
  uint32_t                         au32Reserved[7];
  un_PASS_SAR_TR_IN_SEL_t          unSAR_TR_IN_SEL[4]; /*!< 0x00000020 per SAR generic input trigger select */
  uint32_t                         au32Reserved1[4];
  un_PASS_SAR_TR_OUT_SEL_t         unSAR_TR_OUT_SEL[4]; /*!< 0x00000040 per SAR generic output trigger select */
  uint32_t                         au32Reserved2[1004];
} stc_PASS_EPASS_MMIO_t;                               /*!< Size = 4096 (0x1000) */

/**
  * \brief Programmable Analog Subsystem for S40E (PASS)
  */
typedef struct stc_PASS {
  stc_PASS_SAR_t                   SAR[4];             /*!< 0x00000000 SAR ADC with Sequencer for S40E */
  uint32_t                         au32Reserved[241664];
  stc_PASS_EPASS_MMIO_t            EPASS_MMIO;         /*!< 0x000F0000 PASS top-level MMIO (Generic Triggers) */
} stc_PASS_t;  


/**
* \defgroup group_syslib_macro_status_codes Status codes
* \{
* Function status type codes
*/
#define CY_PDL_STATUS_CODE_Pos  (0u)        /**< The module status code position in the status code */
#define CY_PDL_STATUS_TYPE_Pos  (16u)       /**< The status type position in the status code */
#define CY_PDL_MODULE_ID_Pos    (18u)       /**< The software module ID position in the status code */
#define CY_PDL_STATUS_INFO      (0UL << CY_PDL_STATUS_TYPE_Pos)    /**< Information status type */
#define CY_PDL_STATUS_WARNING   (1UL << CY_PDL_STATUS_TYPE_Pos)    /**< Warning status type */
#define CY_PDL_STATUS_ERROR     (2UL << CY_PDL_STATUS_TYPE_Pos)    /**< Error status type */
#define CY_PDL_MODULE_ID_Msk    (0x3FFFu)   /**< The software module ID mask */
/** Get the software PDL module ID */
#define CY_PDL_DRV_ID(id)       ((uint32_t)((uint32_t)((id) & CY_PDL_MODULE_ID_Msk) << CY_PDL_MODULE_ID_Pos))
#define CY_SYSLIB_ID            CY_PDL_DRV_ID(0x11u)     /**< SYSLIB PDL ID */
/** \} group_syslib_macro_status_codes */


/**
* \addtogroup group_adc_macro
* \{
*/

/** Driver major version */
#define CY_ADC_DRV_VERSION_MAJOR    1

/** Driver minor version */
#define CY_ADC_DRV_VERSION_MINOR    0

/** Adc driver ID */
#define CY_ADC_ID CY_PDL_DRV_ID(0x36u)

/** \} group_adc_macro */

/***************************************
*       Enumeration
***************************************/

/**
* \addtogroup group_adc_enums
* \{
*/

/**
* Adc Driver error codes
*/
typedef enum
{
    CY_ADC_SUCCESS   = 0x00u,                                     /**< Returned successful */
    CY_ADC_BAD_PARAM = CY_ADC_ID | CY_PDL_STATUS_ERROR | 0x01u, /**< Bad parameter was passed */
} cy_en_adc_status_t;

/** When set use 2 cycles for the Most Significant Bit (MSB) */
typedef enum {
    CY_ADC_MSB_STRETCH_MODE_1CYCLE = 0u,   /**< Use 1 clock cycles per conversion. */
    CY_ADC_MSB_STRETCH_MODE_2CYCLE = 1u    /**< Use 2 clock cycles per conversion. */
} cy_en_adc_msb_stretch_mode_t;

/** Select Diagnostic Reference function. */
typedef enum {
    CY_ADC_DIAG_REFERENCE_SELECT_VREFL          = 0u,   /**< DiagOut = VrefL */
    CY_ADC_DIAG_REFERENCE_SELECT_VREFH_1DIV8    = 1u,   /**< DiagOut = VrefH * 1/8 */
    CY_ADC_DIAG_REFERENCE_SELECT_VREFH_2DIV8    = 2u,   /**< DiagOut = VrefH * 2/8 */
    CY_ADC_DIAG_REFERENCE_SELECT_VREFH_3DIV8    = 3u,   /**< DiagOut = VrefH * 3/8 */
    CY_ADC_DIAG_REFERENCE_SELECT_VREFH_4DIV8    = 4u,   /**< DiagOut = VrefH * 4/8 */
    CY_ADC_DIAG_REFERENCE_SELECT_VREFH_5DIV8    = 5u,   /**< DiagOut = VrefH * 5/8 */
    CY_ADC_DIAG_REFERENCE_SELECT_VREFH_6DIV8    = 6u,   /**< DiagOut = VrefH * 6/8 */
    CY_ADC_DIAG_REFERENCE_SELECT_VREFH_7DIV8    = 7u,   /**< DiagOut = VrefH * 7/8 */
    CY_ADC_DIAG_REFERENCE_SELECT_VREFH          = 8u,   /**< DiagOut = VrefH */
    CY_ADC_DIAG_REFERENCE_SELECT_VREFX          = 9u,   /**< DiagOut = VrefX = VrefH * 199/200 */
    CY_ADC_DIAG_REFERENCE_SELECT_VBG            = 10u,  /**< DiagOut = Vbg from SRSS */
    CY_ADC_DIAG_REFERENCE_SELECT_VIN1           = 11u,  /**< DiagOut = Vin1 */
    CY_ADC_DIAG_REFERENCE_SELECT_VIN2           = 12u,  /**< DiagOut = Vin2 */
    CY_ADC_DIAG_REFERENCE_SELECT_VIN3           = 13u,  /**< DiagOut = Vin3 */
    CY_ADC_DIAG_REFERENCE_SELECT_I_SOURCE       = 14u,  /**< DiagOut = Isource (10uA) */
    CY_ADC_DIAG_REFERENCE_SELECT_I_SINK         = 15u   /**< DiagOut = Isink (10uA) */
} cy_en_adc_diag_reference_select_t;

/** The ADC trigger mode selection. */
typedef enum {
    CY_ADC_TRIGGER_OFF          = 0u,    /**< Use for channels in group, except the first channel */
    CY_ADC_TRIGGER_TCPWM        = 1u,    /**< Trigger from corresponding TCPWM channel */
    CY_ADC_TRIGGER_GENERIC0     = 2u,    /**< Generic trigger input 0 */
    CY_ADC_TRIGGER_GENERIC1     = 3u,    /**< Generic trigger input 1 */
    CY_ADC_TRIGGER_GENERIC2     = 4u,    /**< Generic trigger input 2 */
    CY_ADC_TRIGGER_GENERIC3     = 5u,    /**< Generic trigger input 3 */
    CY_ADC_TRIGGER_GENERIC4     = 6u,    /**< Generic trigger input 4 */
    CY_ADC_TRIGGER_CONTINUOUS   = 7u     /**< Always triggered (also called idle), can only be used for at most 1 channel */
} cy_en_adc_trigger_selection_t;

/** The ADC preemption type selection. */
typedef enum {
    CY_ADC_PREEMPTION_ABORT_CANCEL  = 0u,   /**< Abort ongoing acquisition, do not return. */
    CY_ADC_PREEMPTION_ABORT_RESTART = 1u,   /**< Abort ongoing acquisition, up on return Restart group from first channel. */
    CY_ADC_PREEMPTION_ABORT_RESUME  = 2u,   /**< Abort ongoing acquisition, up on return Resume group from aborted channel. */
    CY_ADC_PREEMPTION_FINISH_RESUME = 3u    /**< Complete ongoing acquisition (including averaging), up on return Resume group from next channel. */
} cy_en_adc_preemption_type_t;

/** Conversion done trigger output selection. */
typedef enum {
    CY_ADC_DONE_LEVEL_PULSE = 0u,   /**< Conversion done signal for other IPs is a 2 cycle pulse (clk_sys), no need to read the result regisgter.
                                         Typically used for triggering another IPs other than DW. */
    CY_ADC_DONE_LEVEL_LEVEL = 1u    /**< Conversion done signal for other IPs is level output until result register is read.
                                         Typically used for DW and also overflow detection. */
} cy_en_adc_done_level_t;

/** Address of the analog signal (pin) to be sampled by corresponding channel. */
typedef enum {
    CY_ADC_PIN_ADDRESS_AN0          = 0u,   /**<  Vout = AN0, select corresponding analog input. */
    CY_ADC_PIN_ADDRESS_AN1          = 1u,
    CY_ADC_PIN_ADDRESS_AN2          = 2u,
    CY_ADC_PIN_ADDRESS_AN3          = 3u,
    CY_ADC_PIN_ADDRESS_AN4          = 4u,
    CY_ADC_PIN_ADDRESS_AN5          = 5u,
    CY_ADC_PIN_ADDRESS_AN6          = 6u,
    CY_ADC_PIN_ADDRESS_AN7          = 7u,
    CY_ADC_PIN_ADDRESS_AN8          = 8u,
    CY_ADC_PIN_ADDRESS_AN9          = 9u,
    CY_ADC_PIN_ADDRESS_AN10         = 10u,
    CY_ADC_PIN_ADDRESS_AN11         = 11u,
    CY_ADC_PIN_ADDRESS_AN12         = 12u,
    CY_ADC_PIN_ADDRESS_AN13         = 13u,
    CY_ADC_PIN_ADDRESS_AN14         = 14u,
    CY_ADC_PIN_ADDRESS_AN15         = 15u,
    CY_ADC_PIN_ADDRESS_AN16         = 16u,
    CY_ADC_PIN_ADDRESS_AN17         = 17u,
    CY_ADC_PIN_ADDRESS_AN18         = 18u,
    CY_ADC_PIN_ADDRESS_AN19         = 19u,
    CY_ADC_PIN_ADDRESS_AN20         = 20u,
    CY_ADC_PIN_ADDRESS_AN21         = 21u,
    CY_ADC_PIN_ADDRESS_AN22         = 22u,
    CY_ADC_PIN_ADDRESS_AN23         = 23u,
    CY_ADC_PIN_ADDRESS_AN24         = 24u,
    CY_ADC_PIN_ADDRESS_AN25         = 25u,
    CY_ADC_PIN_ADDRESS_AN26         = 26u,
    CY_ADC_PIN_ADDRESS_AN27         = 27u,
    CY_ADC_PIN_ADDRESS_AN28         = 28u,
    CY_ADC_PIN_ADDRESS_AN29         = 29u,
    CY_ADC_PIN_ADDRESS_AN30         = 30u,
    CY_ADC_PIN_ADDRESS_AN31         = 31u,
    CY_ADC_PIN_ADDRESS_VMOTOR       = 32u,  /**< Vout = Vmotor, select motor input. */
    CY_ADC_PIN_ADDRESS_VAUX         = 33u,  /**< Vout = Vaux, select auxiliarly input. */
    CY_ADC_PIN_ADDRESS_AMUXBUS_A    = 34u,  /**< Vout = AmuxbusA. */
    CY_ADC_PIN_ADDRESS_AMUXBUS_B    = 35u,  /**< Vout = AmuxbusB. */
    CY_ADC_PIN_ADDRESS_VCCD         = 36u,  /**< Vout = Vccd. */
    CY_ADC_PIN_ADDRESS_VDDA         = 37u,  /**< Vout = Vdda. */
    CY_ADC_PIN_ADDRESS_VBG          = 38u,  /**< Vout = Vbg, Bandgap voltage from SRSS. */
    CY_ADC_PIN_ADDRESS_VTEMP        = 39u,  /**< Vout = Vtemp, select temperature sensor. Make sure that only 1 ADC is allowed to use this.. */
    CY_ADC_PIN_ADDRESS_VREF_L       = 62u,  /**< Vout = VrefL (VrefL actually bypasses the SARMUX (XSL)). */
    CY_ADC_PIN_ADDRESS_VREF_H       = 63u   /**< Vout = VrefH  (VrefH actually bypasses the SARMUX (XSH)) */
} cy_en_adc_pin_address_t;

/** Select the physical port. This field is only valid for ADC0. */
typedef enum {
    CY_ADC_PORT_ADDRESS_SARMUX0 = 0u,   /**< ADC uses it's own SARMUX. */
    CY_ADC_PORT_ADDRESS_SARMUX1 = 1u,   /**< ADC0 uses SARMUX1 (only valid for ADC0, undefined result if used for ADC1-3). */
    CY_ADC_PORT_ADDRESS_SARMUX2 = 2u,   /**< ADC0 uses SARMUX2 (only valid for ADC0, undefined result if used for ADC1-3). */
    CY_ADC_PORT_ADDRESS_SARMUX3 = 3u    /**< ADC0 uses SARMUX3 (only valid for ADC0, undefined result if used for ADC1-3). */
} cy_en_adc_port_address_t;

/** Select preconditioning mode.
    Preconditioning (dis)charges the SAR sample capacitor to the selected reference voltage for precondition time (global) cycles,
    a break before make cycle will be inserted before sampling starts sample time.
    See also \ref cy_stc_adc_config_t */
typedef enum {
    CY_ADC_PRECONDITION_MODE_OFF    = 0u,   /**< No preconditioning. */
    CY_ADC_PRECONDITION_MODE_VREFL  = 1u,   /**< Discharge to VREFL. */
    CY_ADC_PRECONDITION_MODE_VREFH  = 2u,   /**< Charge to VREFH. */
    CY_ADC_PRECONDITION_MODE_DIAG   = 3u    /**< Connect the Diagnostic reference output during preconditioning.
                                                 The Diagnostic reference should be configured to output a reference voltage. */
} cy_en_adc_precondition_mode_t;

/** Select Overlap mode or SARMUX Diagnostics, in both cases the Diagnostic reference is used. */
typedef enum {
    CY_ADC_OVERLAP_DIAG_MODE_OFF        = 0u,   /**< No overlap or SARMUX Diagnostics. */
    CY_ADC_OVERLAP_DIAG_MODE_HALF       = 1u,   /**< Sample the selected analog input for 2 sample time periods.
                                                     During the first period use overlap sampling,
                                                     i.e. connect both the analog input and Diagnostic reference.
                                                     During second period only connect the analog input */
    CY_ADC_OVERLAP_DIAG_MODE_FULL       = 2u,   /**< Like normal sample the selected analog input for a single sample time period
                                                     but use overlap sampling, i.e. connect both the analog input and Diagnostic reference. */
    CY_ADC_OVERLAP_DIAG_MODE_MUX_DIAG   = 3u    /**< Select Diagnostic reference instead of analog signal at the input of the SARMUX.
                                                     This enables a functional safety check of the SARMUX analog connections. */
} cy_en_adc_overlap_diag_mode_t;

/** Select calibration values. */
typedef enum {
    CY_ADC_CALIBRATION_VALUE_REGULAR    = 0u,   /**< use regular calibration values */
    CY_ADC_CALIBRATION_VALUE_ALTERNATE  = 1u    /**< use alternate calibration values */
} cy_en_adc_calibration_value_select_t;


/** Select post processing mode. */
typedef enum {
    CY_ADC_POST_PROCESSING_MODE_NONE        = 0u,  /**< No postprocessing. */
    CY_ADC_POST_PROCESSING_MODE_AVG         = 1u,  /**< Averaging. */
    CY_ADC_POST_PROCESSING_MODE_AVG_RANGE   = 2u,  /**< Averaging followed by Range detect. */
    CY_ADC_POST_PROCESSING_MODE_RANGE       = 3u,  /**< Range detect. */
    CY_ADC_POST_PROCESSING_MODE_RANGE_PULSE = 4u,  /**< Range detect followed by pulse detect. */
} cy_en_adc_post_processing_mode_t;

/** Select result data alignment. */
typedef enum {
    CY_ADC_RESULT_ALIGNMENT_RIGHT           = 0u, /**< the data is right aligned in result[11:0], with sign extension to 16 bits if enabled. */
    CY_ADC_RESULT_ALIGNMENT_LEFT            = 1u, /**< the data is left aligned in result[15:4] with the lower nibble 0.
                                                       Caveat if the result was more than 12 bits (e.g. after averaging)
                                                       then the bits above 12 will be discarded. */
} cy_en_adc_result_alignment_t;

/** Select whether result data is signed or unsigned. */
typedef enum {
    CY_ADC_SIGN_EXTENTION_UNSIGNED          = 0u, /**< Result data is unsigned (zero extended if needed). */
    CY_ADC_SIGN_EXTENTION_SIGNED            = 1u, /**< Result data is signed (sign extended if needed). */
} cy_en_adc_sign_extention_t;

/** Select range detection mode. */
typedef enum {
    CY_ADC_RANGE_DETECTION_MODE_BELOW_LO        = 0u,   /**< Below Low threshold (result < Lo) */
    CY_ADC_RANGE_DETECTION_MODE_INSIDE_RANGE    = 1u,   /**< Inside range (Lo <= result < Hi) */
    CY_ADC_RANGE_DETECTION_MODE_ABOVE_HI        = 2u,   /**< Above high threshold (Hi <= result) */
    CY_ADC_RANGE_DETECTION_MODE_OUTSIDE_RANGE   = 3u    /**< Outside range (result < Lo || Hi <= result) */
} cy_en_adc_range_detection_mode_t;

/** \} group_adc_enums */

/***************************************
*       Configuration Structure
***************************************/

/** Channel conversion status */
typedef struct
{
    bool aboveHi;       /**< If true out of range was detected and the value was above the Hi threshold */
    bool rangeIntr;     /**< If true range detected. */
    bool pulseIntr;     /**< If true pulse detected. */
    bool valid;         /**< If true result data is valid. */
} cy_stc_adc_ch_status_t;

/** Interrupt sources */
typedef struct
{
    bool grpDone;       /**< (Group) Done interrupt */
    bool grpCancelled;  /**< (Group) Cancelled Interrupt */
    bool grpOverflow;   /**< (Group) Overflow Interrupt */
    bool chRange;       /**< Range detect Interrupt */
    bool chPulse;       /**< Pulse detect Interrupt */
    bool chOverflow;    /**< Channel overflow Interrupt */
} cy_stc_adc_interrupt_source_t;

/** Group sources */
typedef struct
{
    bool grpComplete;       /**< Group acquisition complete. */
    bool grpCancelled;      /**< Group Cancelled. */
    bool grpOverflow;       /**< Group Overflow. */
    bool chRangeComplete;   /**< Channel Range complete. */
    bool chPulseComplete;   /**< Channel Pulse complete. */
    bool chOverflow;        /**< Channel Overflow.  */
    bool grpBusy;           /**< Group acquisition busy. */
} cy_stc_adc_group_status_t;

/**
* \addtogroup group_adc_data_structures
* \{
*/

/** Configuration structure of a ADC */
typedef struct {
    uint8_t                         preconditionTime;       /**< Number ADC clock cycles that Preconditioning is done before the sample window starts. */
    uint8_t                         powerupTime;            /**< Number cycles to wait to power up after IDLE_PWRDWN. */
    bool                            enableIdlePowerDown;    /**< When idle automatcially power down the analog if true. */
    cy_en_adc_msb_stretch_mode_t    msbStretchMode;         /**< When set use 2 cycles for the Most Significant Bit (MSB), see \ref cy_en_adc_msb_stretch_mode_t */
    bool                            enableHalfLsbConv;      /**< When true take an extra cycle to convert the half LSB and add it to 12-bit result for Missing Code Recovery */
    bool                            sarMuxEnable;           /**< Enable the SARMUX (only valid if sarIpEnable = true). */
    bool                            adcEnable;              /**< Enable the SAR ADC and SAR sequencer (only valid if sarIpEnable = true). */
    bool                            sarIpEnable;            /**< Enable the SAR IP. */
} cy_stc_adc_config_t;

/** Configuration structure of a ADC channel */
typedef struct {
    cy_en_adc_trigger_selection_t       triggerSelection;   /**< The ADC trigger mode selection, see \ref cy_en_adc_trigger_selection_t */
    uint8_t                             channelPriority;    /**< Channel priority. 0=highest, 7=lowest. Valid range = [0..7].*/
    cy_en_adc_preemption_type_t         preenptionType;     /**< The ADC preemption type selection, see \ref cy_en_adc_preemption_type_t */
    bool                                isGroupEnd;         /**< This value indicates that this channel is the last channel of a group or not */
    cy_en_adc_done_level_t              doneLevel;          /**< Conversion done trigger output selection, see \ref cy_en_adc_done_level_t */
    cy_en_adc_pin_address_t             pinAddress;         /**< Address of the analog signal (pin) to be sampled by corresponding channel,
                                                              *  see \ref cy_en_adc_pin_address_t
                                                              */
    cy_en_adc_port_address_t            portAddress;        /**< Select the physical port, see \ref cy_en_adc_port_address_t */
    uint8_t                             extMuxSelect;       /**< External analog mux select. */
    bool                                extMuxEnable;       /**< External analog mux enable. */
    cy_en_adc_precondition_mode_t       preconditionMode;   /**< Select preconditioning mode, see \ref cy_en_adc_precondition_mode_t */
    cy_en_adc_overlap_diag_mode_t       overlapDiagMode;    /**< Select Overlap mode or SARMUX Diagnostics, see \ref cy_en_adc_overlap_diag_mode_t */
    uint16_t                            sampleTime;         /**< Sample time (aperture) in ADC clock cycles. Minimum is 1 (0 gives the same result as 1),
                                                              *  minimum time needed for proper settling is at least 300ns,
                                                              *  i.e. 6 clock cycles at the max frequency of 20MHz.
                                                              */
    cy_en_adc_calibration_value_select_t calibrationValueSelect;    /**< Select calibration values, see \ref cy_en_adc_calibration_value_select_t */
    cy_en_adc_post_processing_mode_t    postProcessingMode; /**< Select post processing mode, see \ref cy_en_adc_post_processing_mode_t */
    cy_en_adc_result_alignment_t        resultAlignment;    /**< Select result data alignment, see \ref cy_en_adc_result_alignment_t */
    cy_en_adc_sign_extention_t          signExtention;      /**< Select whether result data is signed or unsigned, see \ref cy_en_adc_sign_extention_t */
    uint8_t                             averageCount;       /**< Either averaging count (minus 1) or Pulse positive reload value. */
    uint8_t                             rightShift;         /**< Either Shift Right (no pulse detection) or Pulse nagative reload value (if pulse detection is enabled).
                                                              *  When using other than pulse detection, setting value is used for right shift value of the
                                                              *  conversion result. Typically it is used for the averaging. Averaging data may be over 12bits,
                                                              *  therefore user must ensure conversion result not to over 12bits by using this value.
                                                              *  This value is also used to fit the 12-bit result in 8bits.
                                                              *  When using other than pulse detection, valid range is [0..12].
                                                              *  In pulse detection mode this value is used as negative reload value.
                                                              */
    cy_en_adc_range_detection_mode_t    rangeDetectionMode; /**< Select range detection mode, see \ref cy_en_adc_range_detection_mode_t */
    uint16_t                            rangeDetectionLoThreshold;  /**< Range detect low threshold (Lo) */
    uint16_t                            rangeDetectionHiThreshold;  /**< Range detect high threshold (Hi) */
    cy_stc_adc_interrupt_source_t       mask;               /**< Select the interrupt sources. \ref cy_stc_adc_interrupt_source_t */
} cy_stc_adc_channel_config_t;

/** Digital calibration values. */
typedef struct {
    uint16_t    offset; /**< Digital offset correction. Valid range is [0..4096] */
    uint8_t     gain;   /**< Digital gain correction. Valid range is [0..63] */
} cy_stc_adc_digital_calibration_conifg_t;

/** Analog calibration values. */
typedef struct {
    uint8_t     offset; /**< Analog offset correction. Valid range is [0..255] */
    uint8_t     gain;   /**< Analog gain correction. Valid range is [0..31] */
} cy_stc_adc_analog_calibration_conifg_t;

/** Configuration structure of diagnosis function. */
typedef struct {
    cy_en_adc_diag_reference_select_t   referenceSelect;    /**< Select Diagnostic Reference function, see \ref cy_en_adc_diag_reference_select_t */
} cy_stc_adc_diag_config_t;

/** Control freeze feature for debugging. */
typedef struct {
    bool      enableFreezeAdc0; /**< If true, freeze ADC0 in debug mode. */
    bool      enableFreezeAdc1; /**< If true, freeze ADC1 in debug mode. */
    bool      enableFreezeAdc2; /**< If true, freeze ADC2 in debug mode. */
    bool      enableFreezeAdc3; /**< If true, freeze ADC3 in debug mode. */
} cy_stc_adc_debug_freeze_config_t;

/** \} group_adc_data_structures */

/***************************************
*       Global Variable
***************************************/
/* N/A */

/***************************************
*              Constants
***************************************/

/** \cond INTERNAL */

/** \endcond */


/***************************************
*       Function Prototypes
***************************************/
/**
* \addtogroup group_adc_functions
* \{
*/

/* For each ADC */
cy_en_adc_status_t Cy_Adc_Init(volatile stc_PASS_SAR_t * base, const cy_stc_adc_config_t * config);
void Cy_Adc_DeInit(volatile stc_PASS_SAR_t * base);
uint32_t Cy_Adc_GetPendingStatus(const volatile stc_PASS_SAR_t * base);
uint32_t Cy_Adc_GetWorkValidStatus(const volatile stc_PASS_SAR_t * base);
uint32_t Cy_Adc_GetWorkRangeStatus(const volatile stc_PASS_SAR_t * base);
uint32_t Cy_Adc_GetWorkRangeHiStatus(const volatile stc_PASS_SAR_t * base);
uint32_t Cy_Adc_GetWorkPulseStatus(const volatile stc_PASS_SAR_t * base);
uint32_t Cy_Adc_GetResultValidStatus(const volatile stc_PASS_SAR_t * base);
uint32_t Cy_Adc_GetResultRangeHiStatus(const volatile stc_PASS_SAR_t * base);

/* For each channels */
cy_en_adc_status_t Cy_Adc_Channel_Init(volatile stc_PASS_SAR_CH_t * base, const cy_stc_adc_channel_config_t * config);
void Cy_Adc_Channel_DeInit(volatile stc_PASS_SAR_CH_t * base);
void Cy_Adc_Channel_Enable(volatile stc_PASS_SAR_CH_t * base);
void Cy_Adc_Channel_Disable(volatile stc_PASS_SAR_CH_t * base);
void Cy_Adc_Channel_SoftwareTrigger(volatile stc_PASS_SAR_CH_t * base);
cy_en_adc_status_t Cy_Adc_Channel_GetResult(const volatile stc_PASS_SAR_CH_t * base, uint16_t * result, cy_stc_adc_ch_status_t * status);
cy_en_adc_status_t Cy_Adc_Channel_GetWorkingData(const volatile stc_PASS_SAR_CH_t * base, uint16_t * result, cy_stc_adc_ch_status_t * status);
cy_en_adc_status_t Cy_Adc_Channel_GetGroupStatus(const volatile stc_PASS_SAR_CH_t * base, cy_stc_adc_group_status_t * status);
cy_en_adc_status_t Cy_Adc_Channel_SetInterruptMask(volatile stc_PASS_SAR_CH_t * base, const cy_stc_adc_interrupt_source_t * mask);
cy_en_adc_status_t Cy_Adc_Channel_GetInterruptMask(const volatile stc_PASS_SAR_CH_t * base, cy_stc_adc_interrupt_source_t * mask);
cy_en_adc_status_t Cy_Adc_Channel_ClearInterruptStatus(volatile stc_PASS_SAR_CH_t * base, const cy_stc_adc_interrupt_source_t * source);
cy_en_adc_status_t Cy_Adc_Channel_GetInterruptStatus(const volatile stc_PASS_SAR_CH_t * base, cy_stc_adc_interrupt_source_t * status);
cy_en_adc_status_t Cy_Adc_Channel_GetInterruptMaskedStatus(const volatile stc_PASS_SAR_CH_t * base, cy_stc_adc_interrupt_source_t * status);

/* For diagnosis function */
cy_en_adc_status_t Cy_Adc_Diag_Init(volatile stc_PASS_SAR_t * base, const cy_stc_adc_diag_config_t * config);
void Cy_Adc_Diag_Enable(volatile stc_PASS_SAR_t * base);
void Cy_Adc_Diag_Disable(volatile stc_PASS_SAR_t * base);

/* For calibration */
void Cy_Adc_TriggerCalibrationUpdate(volatile stc_PASS_SAR_t * base);
bool Cy_Adc_IsCalibrationUpdateDone(const volatile stc_PASS_SAR_t * base);
cy_en_adc_status_t Cy_Adc_SetDigitalCalibrationValue(volatile stc_PASS_SAR_t * base, const cy_stc_adc_digital_calibration_conifg_t * config);
cy_en_adc_status_t Cy_Adc_GetDigitalCalibrationValue(const volatile stc_PASS_SAR_t * base, cy_stc_adc_digital_calibration_conifg_t * config);
cy_en_adc_status_t Cy_Adc_SetAltDigitalCalibrationValue(volatile stc_PASS_SAR_t * base, const cy_stc_adc_digital_calibration_conifg_t * config);
cy_en_adc_status_t Cy_Adc_GetAltDigitalCalibrationValue(const volatile stc_PASS_SAR_t * base, cy_stc_adc_digital_calibration_conifg_t * config);
cy_en_adc_status_t Cy_Adc_SetAnalogCalibrationValue(volatile stc_PASS_SAR_t * base, const cy_stc_adc_analog_calibration_conifg_t * config);
cy_en_adc_status_t Cy_Adc_GetAnalogCalibrationValue(const volatile stc_PASS_SAR_t * base, cy_stc_adc_analog_calibration_conifg_t * config);
cy_en_adc_status_t Cy_Adc_SetAltAnalogCalibrationValue(volatile stc_PASS_SAR_t * base, const cy_stc_adc_analog_calibration_conifg_t * config);
cy_en_adc_status_t Cy_Adc_GetAltAnalogCalibrationValue(const volatile stc_PASS_SAR_t * base, cy_stc_adc_analog_calibration_conifg_t * config);

/* For debugging */
cy_en_adc_status_t Cy_Adc_SetDebugFreezeMode(volatile stc_PASS_EPASS_MMIO_t * base, const cy_stc_adc_debug_freeze_config_t * config);

/* For SAR general trigger input / output trigger setting */
cy_en_adc_status_t Cy_Adc_SetGenericTriggerInput(volatile stc_PASS_EPASS_MMIO_t * base, uint8_t numOfAdc, uint8_t triggerInputNumber, uint8_t genericTriggerValue);
cy_en_adc_status_t Cy_Adc_SetGenericOutpuTrigger(volatile stc_PASS_EPASS_MMIO_t * base, uint8_t numOfAdc, uint8_t outputTriggerNumber, uint8_t genericTriggerValue);

/** \} group_adc_functions */

#if defined(__cplusplus)
}
#endif


/** \} group_adc */

/* [] END OF FILE */



/*****************cy_evtgen.h**********************/


typedef enum
{
    CY_EVTGEN_RATIO_CONTROL_SW    = 0u,
    CY_EVTGEN_RATIO_CONTROL_HW,
} cy_en_evtgendrv_ratio_control;

typedef enum
{
    CY_EVTGEN_ACTIVE_FUNCTIONALITY    = 0u,
    CY_EVTGEN_DEEPSLEEP_FUNCTIONALITY,
} cy_en_evtgendrv_struct_functionality;

typedef enum
{
    CY_EVTGEN_LEVEL_SENSITIVE    = 0u,
    CY_EVTGEN_EDGE_SENSITIVE,
} cy_en_evtgendrv_struct_trg_edge_t;

/**
* \defgroup group_evtgen_returns  Event generator return values
* \{
* Specifies return values meaning
*/

/** This enum has the return values of the Event generator driver */
typedef enum
{
    CY_EVTGEN_OK    = 0u,
    CY_EVTGEN_ERR,
} cy_en_evtgendrv_status_t;

typedef enum
{
    CY_EVTGEN_DISABLE    = 0u,
    CY_EVTGEN_ENABLE     = 1u,
} cy_en_evtgendrv_enable_t;

typedef enum
{
    CY_EVTGEN_COUNTER_STATUS_INVALID = 0u,
    CY_EVTGEN_COUNTER_STATUS_VALID   = 1u,
} cy_en_evtgen_counter_status_t;

typedef enum
{
    CY_EVTGEN_RATIO_DYNAMIC_MODE0    = 0u, // new RATIO value = (RATIO + measurement + 1) / 2.
    CY_EVTGEN_RATIO_DYNAMIC_MODE1    = 1u, // new RATIO value = (3*RATIO + measurement + 2) / 4.
    CY_EVTGEN_RATIO_DYNAMIC_MODE2    = 2u, // new RATIO value = (7*RATIO + measurement + 4) / 8.
    CY_EVTGEN_RATIO_DYNAMIC_MODE3    = 3u, // new RATIO value = (15*RATIO + measurement + 8) / 16.
    CY_EVTGEN_RATIO_DYNAMIC_MODE4    = 4u, // new RATIO value = (31*RATIO + measurement + 16) / 32.
    CY_EVTGEN_RATIO_DYNAMIC_MODE5    = 5u, // new RATIO value = (63*RATIO + measurement + 32) / 64.
    CY_EVTGEN_RATIO_DYNAMIC_MODE6    = 6u, // new RATIO value = (127*RATIO + measurement + 64) / 128.
    CY_EVTGEN_RATIO_DYNAMIC_MODE7    = 7u, // new RATIO value = (255*RATIO + measurement + 128) / 256.
} cy_en_evtgendrv_ratio_dynamic_mode_t;

typedef enum
{
    CY_EVTGEN_DSLEEP_COMP_DISABLE    = 0u,
    CY_EVTGEN_DSLEEP_COMP_ENABLE,
} cy_en_evtgendrv_enable_dsleep_cmp_t;


/** \} group_evtgen_returns */

/***************************************
* Data Structure definitions
***************************************/

/**
* \addtogroup group_evtgen_data_structure
* \{
*/

/** Event generator driver context */
typedef struct
{
    uint32_t frequencyRef;
    uint32_t frequencyLf;
    uint32_t frequencyTick;
    cy_en_evtgendrv_ratio_control ratioControlMode;
    cy_en_evtgendrv_ratio_dynamic_mode_t ratioValueDynamicMode; /**< Specifies the configuration of evtgen operation */
}cy_stc_evtgen_config_t;

typedef void (* cy_evtgen_handler)(void);   /**< Type of ISR callbacks */

typedef struct
{
    cy_en_evtgendrv_struct_functionality functionalitySelection;
    cy_en_evtgendrv_struct_trg_edge_t triggerOutEdge;              /**< Specifies the code of evtgen operation */
    uint32_t valueActiveComparator;                                /**< Specifies the configuration of evtgen operation */
    uint32_t valueDeepSleepComparator;                             /**< Specifies the configuration of evtgen operation */
    cy_evtgen_handler userIsr;
}cy_stc_evtgen_struct_config_t;

typedef struct
{
    uint32_t addValueForCOMP0;                                /**< Specifies the configuration of evtgen operation */
    cy_evtgen_handler userIsr;
}cy_stc_evtgen_struct_context_t;

/** \} group_evtgen_data_structure */

/****************************cyip_evtgen.h*************************************/

/*******************************************************************************
*                                    EVTGEN
*******************************************************************************/

#define EVTGEN_COMP_STRUCT_SECTION_SIZE         0x00000020UL
#define EVTGEN_SECTION_SIZE                     0x00001000UL

/**
  * \brief Comparator control (EVTGEN_COMP_STRUCT_COMP_CTL)
  */
typedef struct stc_EVTGEN_COMP_STRUCT_COMP_CTL_field {
  uint32_t                         u1COMP0_EN:1;
  uint32_t                         u1COMP1_EN:1;
  uint32_t                         :14;
  uint32_t                         u1TR_OUT_EDGE:1;
  uint32_t                         :14;
  uint32_t                         u1ENABLED:1;
} stc_EVTGEN_COMP_STRUCT_COMP_CTL_field_t;

typedef union un_EVTGEN_COMP_STRUCT_COMP_CTL {
  uint32_t                         u32Register;
  stc_EVTGEN_COMP_STRUCT_COMP_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_COMP_STRUCT_COMP_CTL_t;

/**
  * \brief Comparator 0 (Active functionality) (EVTGEN_COMP_STRUCT_COMP0)
  */
typedef struct stc_EVTGEN_COMP_STRUCT_COMP0_field {
  uint32_t                         u32INT32:32;
} stc_EVTGEN_COMP_STRUCT_COMP0_field_t;

typedef union un_EVTGEN_COMP_STRUCT_COMP0 {
  uint32_t                         u32Register;
  stc_EVTGEN_COMP_STRUCT_COMP0_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_COMP_STRUCT_COMP0_t;

/**
  * \brief Comparator 1 (DeepSleep functionality) (EVTGEN_COMP_STRUCT_COMP1)
  */
typedef struct stc_EVTGEN_COMP_STRUCT_COMP1_field {
  uint32_t                         u32INT32:32;
} stc_EVTGEN_COMP_STRUCT_COMP1_field_t;

typedef union un_EVTGEN_COMP_STRUCT_COMP1 {
  uint32_t                         u32Register;
  stc_EVTGEN_COMP_STRUCT_COMP1_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_COMP_STRUCT_COMP1_t;



/**
  * \brief Control (EVTGEN_CTL)
  */
typedef struct stc_EVTGEN_CTL_field {
  uint32_t                         :31;
  uint32_t                         u1ENABLED:1;
} stc_EVTGEN_CTL_field_t;

typedef union un_EVTGEN_CTL {
  uint32_t                         u32Register;
  stc_EVTGEN_CTL_field_t           stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_CTL_t;

/**
  * \brief Comparator structures comparator 0 status (EVTGEN_COMP0_STATUS)
  */
typedef struct stc_EVTGEN_COMP0_STATUS_field {
  uint32_t                         u16COMP0_OUT:16;
  uint32_t                         :16;
} stc_EVTGEN_COMP0_STATUS_field_t;

typedef union un_EVTGEN_COMP0_STATUS {
  uint32_t                         u32Register;
  stc_EVTGEN_COMP0_STATUS_field_t  stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_COMP0_STATUS_t;

/**
  * \brief Comparator structures comparator 1 status (EVTGEN_COMP1_STATUS)
  */
typedef struct stc_EVTGEN_COMP1_STATUS_field {
  uint32_t                         u16COMP1_OUT:16;
  uint32_t                         :16;
} stc_EVTGEN_COMP1_STATUS_field_t;

typedef union un_EVTGEN_COMP1_STATUS {
  uint32_t                         u32Register;
  stc_EVTGEN_COMP1_STATUS_field_t  stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_COMP1_STATUS_t;

/**
  * \brief Counter status (EVTGEN_COUNTER_STATUS)
  */
typedef struct stc_EVTGEN_COUNTER_STATUS_field {
  uint32_t                         :31;
  uint32_t                         u1VALID:1;
} stc_EVTGEN_COUNTER_STATUS_field_t;

typedef union un_EVTGEN_COUNTER_STATUS {
  uint32_t                         u32Register;
  stc_EVTGEN_COUNTER_STATUS_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_COUNTER_STATUS_t;

/**
  * \brief Counter (EVTGEN_COUNTER)
  */
typedef struct stc_EVTGEN_COUNTER_field {
  uint32_t                         u32INT32:32;
} stc_EVTGEN_COUNTER_field_t;

typedef union un_EVTGEN_COUNTER {
  uint32_t                         u32Register;
  stc_EVTGEN_COUNTER_field_t       stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_COUNTER_t;

/**
  * \brief Ratio control (EVTGEN_RATIO_CTL)
  */
typedef struct stc_EVTGEN_RATIO_CTL_field {
  uint32_t                         :16;
  uint32_t                         u3DYNAMIC_MODE:3;
  uint32_t                         :11;
  uint32_t                         u1DYNAMIC:1;
  uint32_t                         u1VALID:1;
} stc_EVTGEN_RATIO_CTL_field_t;

typedef union un_EVTGEN_RATIO_CTL {
  uint32_t                         u32Register;
  stc_EVTGEN_RATIO_CTL_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_RATIO_CTL_t;

/**
  * \brief Ratio (EVTGEN_RATIO)
  */
typedef struct stc_EVTGEN_RATIO_field {
  uint32_t                         :8;
  uint32_t                         u8FRAC8:8;
  uint32_t                         u16INT16:16;
} stc_EVTGEN_RATIO_field_t;

typedef union un_EVTGEN_RATIO {
  uint32_t                         u32Register;
  stc_EVTGEN_RATIO_field_t         stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_RATIO_t;

/**
  * \brief Reference clock control (EVTGEN_REF_CLOCK_CTL)
  */
typedef struct stc_EVTGEN_REF_CLOCK_CTL_field {
  uint32_t                         u8INT_DIV:8;
  uint32_t                         :24;
} stc_EVTGEN_REF_CLOCK_CTL_field_t;

typedef union un_EVTGEN_REF_CLOCK_CTL {
  uint32_t                         u32Register;
  stc_EVTGEN_REF_CLOCK_CTL_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_REF_CLOCK_CTL_t;

/**
  * \brief Interrupt (EVTGEN_INTR)
  */
typedef struct stc_EVTGEN_INTR_field {
  uint32_t                         u16COMP0:16;
  uint32_t                         :16;
} stc_EVTGEN_INTR_field_t;

typedef union un_EVTGEN_INTR {
  uint32_t                         u32Register;
  stc_EVTGEN_INTR_field_t          stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_INTR_t;

/**
  * \brief Interrupt set (EVTGEN_INTR_SET)
  */
typedef struct stc_EVTGEN_INTR_SET_field {
  uint32_t                         u16COMP0:16;
  uint32_t                         :16;
} stc_EVTGEN_INTR_SET_field_t;

typedef union un_EVTGEN_INTR_SET {
  uint32_t                         u32Register;
  stc_EVTGEN_INTR_SET_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_INTR_SET_t;

/**
  * \brief Interrupt mask (EVTGEN_INTR_MASK)
  */
typedef struct stc_EVTGEN_INTR_MASK_field {
  uint32_t                         u16COMP0:16;
  uint32_t                         :16;
} stc_EVTGEN_INTR_MASK_field_t;

typedef union un_EVTGEN_INTR_MASK {
  uint32_t                         u32Register;
  stc_EVTGEN_INTR_MASK_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_INTR_MASK_t;

/**
  * \brief Interrupt masked (EVTGEN_INTR_MASKED)
  */
typedef struct stc_EVTGEN_INTR_MASKED_field {
  uint32_t                         u16COMP0:16;
  uint32_t                         :16;
} stc_EVTGEN_INTR_MASKED_field_t;

typedef union un_EVTGEN_INTR_MASKED {
  uint32_t                         u32Register;
  stc_EVTGEN_INTR_MASKED_field_t   stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_INTR_MASKED_t;

/**
  * \brief DeepSleep interrupt (EVTGEN_INTR_DPSLP)
  */
typedef struct stc_EVTGEN_INTR_DPSLP_field {
  uint32_t                         u16COMP1:16;
  uint32_t                         :16;
} stc_EVTGEN_INTR_DPSLP_field_t;

typedef union un_EVTGEN_INTR_DPSLP {
  uint32_t                         u32Register;
  stc_EVTGEN_INTR_DPSLP_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_INTR_DPSLP_t;

/**
  * \brief DeepSleep interrupt set (EVTGEN_INTR_DPSLP_SET)
  */
typedef struct stc_EVTGEN_INTR_DPSLP_SET_field {
  uint32_t                         u16COMP1:16;
  uint32_t                         :16;
} stc_EVTGEN_INTR_DPSLP_SET_field_t;

typedef union un_EVTGEN_INTR_DPSLP_SET {
  uint32_t                         u32Register;
  stc_EVTGEN_INTR_DPSLP_SET_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_INTR_DPSLP_SET_t;

/**
  * \brief DeepSleep interrupt mask (EVTGEN_INTR_DPSLP_MASK)
  */
typedef struct stc_EVTGEN_INTR_DPSLP_MASK_field {
  uint32_t                         u16COMP1:16;
  uint32_t                         :16;
} stc_EVTGEN_INTR_DPSLP_MASK_field_t;

typedef union un_EVTGEN_INTR_DPSLP_MASK {
  uint32_t                         u32Register;
  stc_EVTGEN_INTR_DPSLP_MASK_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_INTR_DPSLP_MASK_t;

/**
  * \brief DeepSleep interrupt masked (EVTGEN_INTR_DPSLP_MASKED)
  */
typedef struct stc_EVTGEN_INTR_DPSLP_MASKED_field {
  uint32_t                         u16COMP1:16;
  uint32_t                         :16;
} stc_EVTGEN_INTR_DPSLP_MASKED_field_t;

typedef union un_EVTGEN_INTR_DPSLP_MASKED {
  uint32_t                         u32Register;
  stc_EVTGEN_INTR_DPSLP_MASKED_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_EVTGEN_INTR_DPSLP_MASKED_t;



/**
  * \brief Comparator structure (EVTGEN_COMP_STRUCT)
  */
typedef struct stc_EVTGEN_COMP_STRUCT {
  un_EVTGEN_COMP_STRUCT_COMP_CTL_t unCOMP_CTL;         /*!< 0x00000000 Comparator control */
  un_EVTGEN_COMP_STRUCT_COMP0_t    unCOMP0;            /*!< 0x00000004 Comparator 0 (Active functionality) */
  un_EVTGEN_COMP_STRUCT_COMP1_t    unCOMP1;            /*!< 0x00000008 Comparator 1 (DeepSleep functionality) */
  uint32_t                         au32Reserved[5];
} stc_EVTGEN_COMP_STRUCT_t;                            /*!< Size = 32 (0x20) */

/**
  * \brief Event generator (EVTGEN)
  */
typedef struct stc_EVTGEN {
  un_EVTGEN_CTL_t                  unCTL;              /*!< 0x00000000 Control */
  un_EVTGEN_COMP0_STATUS_t         unCOMP0_STATUS;     /*!< 0x00000004 Comparator structures comparator 0 status */
  un_EVTGEN_COMP1_STATUS_t         unCOMP1_STATUS;     /*!< 0x00000008 Comparator structures comparator 1 status */
  uint32_t                         u32Reserved;
  un_EVTGEN_COUNTER_STATUS_t       unCOUNTER_STATUS;   /*!< 0x00000010 Counter status */
  un_EVTGEN_COUNTER_t              unCOUNTER;          /*!< 0x00000014 Counter */
  uint32_t                         au32Reserved1[2];
  un_EVTGEN_RATIO_CTL_t            unRATIO_CTL;        /*!< 0x00000020 Ratio control */
  un_EVTGEN_RATIO_t                unRATIO;            /*!< 0x00000024 Ratio */
  uint32_t                         au32Reserved2[2];
  un_EVTGEN_REF_CLOCK_CTL_t        unREF_CLOCK_CTL;    /*!< 0x00000030 Reference clock control */
  uint32_t                         au32Reserved3[435];
  un_EVTGEN_INTR_t                 unINTR;             /*!< 0x00000700 Interrupt */
  un_EVTGEN_INTR_SET_t             unINTR_SET;         /*!< 0x00000704 Interrupt set */
  un_EVTGEN_INTR_MASK_t            unINTR_MASK;        /*!< 0x00000708 Interrupt mask */
  un_EVTGEN_INTR_MASKED_t          unINTR_MASKED;      /*!< 0x0000070C Interrupt masked */
  un_EVTGEN_INTR_DPSLP_t           unINTR_DPSLP;       /*!< 0x00000710 DeepSleep interrupt */
  un_EVTGEN_INTR_DPSLP_SET_t       unINTR_DPSLP_SET;   /*!< 0x00000714 DeepSleep interrupt set */
  un_EVTGEN_INTR_DPSLP_MASK_t      unINTR_DPSLP_MASK;  /*!< 0x00000718 DeepSleep interrupt mask */
  un_EVTGEN_INTR_DPSLP_MASKED_t    unINTR_DPSLP_MASKED; /*!< 0x0000071C DeepSleep interrupt masked */
  uint32_t                         au32Reserved4[56];
  stc_EVTGEN_COMP_STRUCT_t         COMP_STRUCT[32];    /*!< 0x00000800 Comparator structure */
} stc_EVTGEN_t;                                        /*!< Size = 3072 (0xC00) */


/* EVTGEN.RATIO */
#define EVTGEN_RATIO_FRAC8_Msk                  0xFF00UL
#define EVTGEN_RATIO_INT16_Pos                  16UL
#define EVTGEN_RATIO_INT16_Msk                  0xFFFF0000UL

/*****************************core_cm7.h**********************************/

#ifndef   __ASM
  #define __ASM                     __asm
#endif

#ifndef   __WFI
  #define __WFI()                   __ASM("wfi")
#endif

#ifndef   __WFE
  #define __WFE()                   __ASM("wfe")
#endif

#ifndef __NVIC_PRIO_BITS
  #define __NVIC_PRIO_BITS          3U
#endif


/**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  volatile const  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  volatile uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  volatile uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  volatile uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  volatile uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  volatile uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  volatile uint8_t  SHPR[12U];              /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  volatile uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  volatile uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  volatile uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  volatile uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  volatile uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  volatile uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  volatile uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  volatile const  uint32_t ID_PFR[2U];             /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  volatile const  uint32_t ID_DFR;                 /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  volatile const  uint32_t ID_AFR;                 /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  volatile const  uint32_t ID_MFR[4U];             /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  volatile const  uint32_t ID_ISAR[5U];            /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[1U];
  volatile const  uint32_t CLIDR;                  /*!< Offset: 0x078 (R/ )  Cache Level ID register */
  volatile const  uint32_t CTR;                    /*!< Offset: 0x07C (R/ )  Cache Type register */
  volatile const  uint32_t CCSIDR;                 /*!< Offset: 0x080 (R/ )  Cache Size ID Register */
  volatile uint32_t CSSELR;                 /*!< Offset: 0x084 (R/W)  Cache Size Selection Register */
  volatile uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
        uint32_t RESERVED3[93U];
  volatile  uint32_t STIR;                   /*!< Offset: 0x200 ( /W)  Software Triggered Interrupt Register */
        uint32_t RESERVED4[15U];
  volatile const  uint32_t MVFR0;                  /*!< Offset: 0x240 (R/ )  Media and VFP Feature Register 0 */
  volatile const  uint32_t MVFR1;                  /*!< Offset: 0x244 (R/ )  Media and VFP Feature Register 1 */
  volatile const  uint32_t MVFR2;                  /*!< Offset: 0x248 (R/ )  Media and VFP Feature Register 2 */
        uint32_t RESERVED5[1U];
  volatile  uint32_t ICIALLU;                /*!< Offset: 0x250 ( /W)  I-Cache Invalidate All to PoU */
        uint32_t RESERVED6[1U];
  volatile  uint32_t ICIMVAU;                /*!< Offset: 0x258 ( /W)  I-Cache Invalidate by MVA to PoU */
  volatile  uint32_t DCIMVAC;                /*!< Offset: 0x25C ( /W)  D-Cache Invalidate by MVA to PoC */
  volatile  uint32_t DCISW;                  /*!< Offset: 0x260 ( /W)  D-Cache Invalidate by Set-way */
  volatile  uint32_t DCCMVAU;                /*!< Offset: 0x264 ( /W)  D-Cache Clean by MVA to PoU */
  volatile  uint32_t DCCMVAC;                /*!< Offset: 0x268 ( /W)  D-Cache Clean by MVA to PoC */
  volatile  uint32_t DCCSW;                  /*!< Offset: 0x26C ( /W)  D-Cache Clean by Set-way */
  volatile  uint32_t DCCIMVAC;               /*!< Offset: 0x270 ( /W)  D-Cache Clean and Invalidate by MVA to PoC */
  volatile  uint32_t DCCISW;                 /*!< Offset: 0x274 ( /W)  D-Cache Clean and Invalidate by Set-way */
        uint32_t RESERVED7[6U];
  volatile uint32_t ITCMCR;                 /*!< Offset: 0x290 (R/W)  Instruction Tightly-Coupled Memory Control Register */
  volatile uint32_t DTCMCR;                 /*!< Offset: 0x294 (R/W)  Data Tightly-Coupled Memory Control Registers */
  volatile uint32_t AHBPCR;                 /*!< Offset: 0x298 (R/W)  AHBP Control Register */
  volatile uint32_t CACR;                   /*!< Offset: 0x29C (R/W)  L1 Cache Control Register */
  volatile uint32_t AHBSCR;                 /*!< Offset: 0x2A0 (R/W)  AHB Slave Control Register */
        uint32_t RESERVED8[1U];
  volatile uint32_t ABFSR;                  /*!< Offset: 0x2A8 (R/W)  Auxiliary Bus Fault Status Register */
} SCB_Type;



/* Memory mapping of Core Hardware */
#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */
#define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct */
#define SCB_SCR_SLEEPDEEP_Pos               2U                                            /*!< SCB SCR: SLEEPDEEP Position */
#define SCB_SCR_SLEEPDEEP_Msk              (1UL << SCB_SCR_SLEEPDEEP_Pos)                 /*!< SCB SCR: SLEEPDEEP Mask */

/*******************************************************************************
*                                    EVTGEN
*******************************************************************************/

#define EVTGEN0_BASE                            0x403F0000UL
#define EVTGEN0                                 ((volatile stc_EVTGEN_t*) EVTGEN0_BASE)                           /* 0x403F0000 */

/********************************************************************************************************************************************/

/*SRSS BASE 0x40260000 */
/*******************************************************************************
*                                     SRSS
*******************************************************************************/
#define SRSS0_BASE                              0x40261000UL
#define SRSS0                                   ((volatile stc_SRSS0_t*) SRSS0_BASE)                                      /* 0x40261000 */

#define WATCHDOG_BASE                           0x40268000UL
#define WATCHDOG                                ((volatile stc_WATCHDOG_t*) WATCHDOG_BASE)                                      /* 0x40268000 */
#define MCWDT0                                  ((volatile stc_MCWDT_t*) &WATCHDOG->MCWDT[0])                                   /* 0x40268000 */
#define MCWDT1                                  ((volatile stc_MCWDT_t*) &WATCHDOG->MCWDT[1])                                   /* 0x40268100 */
#define BASICWDT                                ((volatile stc_WDT_t*) &WATCHDOG->WDT)                                          /* 0x4026C000 */


typedef struct stc_MCWDT_LOCK_field {
  uint32_t                         u2MCWDT_LOCK:2;
  uint32_t                         :30;
} stc_MCWDT_LOCK_field_t;

typedef union un_MCWDT_LOCK {
  uint32_t                         u32Register;
  stc_MCWDT_LOCK_field_t           stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_LOCK_t;

typedef struct stc_MCWDT_SERVICE_field {
  uint32_t                         u1CTR0_SERVICE:1;
  uint32_t                         u1CTR1_SERVICE:1;
  uint32_t                         :30;
} stc_MCWDT_SERVICE_field_t;

typedef union un_MCWDT_SERVICE {
  uint32_t                         u32Register;
  stc_MCWDT_SERVICE_field_t        stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_SERVICE_t;

/**
  * \brief MCWDT Subcounter Control Register (MCWDT_CTR_CTL)
  */
typedef struct stc_MCWDT_CTR_CTL_field {
  uint32_t                         u1ENABLED:1;
  uint32_t                         :30;
  uint32_t                         u1ENABLE:1;
} stc_MCWDT_CTR_CTL_field_t;

typedef union un_MCWDT_CTR_CTL {
  uint32_t                         u32Register;
  stc_MCWDT_CTR_CTL_field_t        stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_CTR_CTL_t;

typedef struct stc_MCWDT_CTR_LOWER_LIMIT_field {
  uint32_t                         u16LOWER_LIMIT:16;
  uint32_t                         :16;
} stc_MCWDT_CTR_LOWER_LIMIT_field_t;

typedef union un_MCWDT_CTR_LOWER_LIMIT {
  uint32_t                         u32Register;
  stc_MCWDT_CTR_LOWER_LIMIT_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_CTR_LOWER_LIMIT_t;

typedef struct stc_MCWDT_CTR_UPPER_LIMIT_field {
  uint32_t                         u16UPPER_LIMIT:16;
  uint32_t                         :16;
} stc_MCWDT_CTR_UPPER_LIMIT_field_t;


typedef union un_MCWDT_CTR_UPPER_LIMIT {
  uint32_t                         u32Register;
  stc_MCWDT_CTR_UPPER_LIMIT_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_CTR_UPPER_LIMIT_t;

typedef struct stc_MCWDT_CTR_WARN_LIMIT_field {
  uint32_t                         u16WARN_LIMIT:16;
  uint32_t                         :16;
} stc_MCWDT_CTR_WARN_LIMIT_field_t;

typedef union un_MCWDT_CTR_WARN_LIMIT {
  uint32_t                         u32Register;
  stc_MCWDT_CTR_WARN_LIMIT_field_t stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_CTR_WARN_LIMIT_t;

typedef struct stc_MCWDT_CTR_CONFIG_field {
  uint32_t                         u2LOWER_ACTION:2;
  uint32_t                         :2;
  uint32_t                         u2UPPER_ACTION:2;
  uint32_t                         :2;
  uint32_t                         u1WARN_ACTION:1;
  uint32_t                         :3;
  uint32_t                         u1AUTO_SERVICE:1;
  uint32_t                         :15;
  uint32_t                         u1DEBUG_TRIGGER_EN:1;
  uint32_t                         :1;
  uint32_t                         u1SLEEPDEEP_PAUSE:1;
  uint32_t                         u1DEBUG_RUN:1;
} stc_MCWDT_CTR_CONFIG_field_t;

typedef union un_MCWDT_CTR_CONFIG {
  uint32_t                         u32Register;
  stc_MCWDT_CTR_CONFIG_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_CTR_CONFIG_t;

typedef struct stc_MCWDT_CTR_CNT_field {
  uint32_t                         u16CNT:16;
  uint32_t                         :16;
} stc_MCWDT_CTR_CNT_field_t;

typedef union un_MCWDT_CTR_CNT {
  uint32_t                         u32Register;
  stc_MCWDT_CTR_CNT_field_t        stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_CTR_CNT_t;

typedef struct stc_MCWDT_CTR {
  un_MCWDT_CTR_CTL_t               unCTL;              /*!< 0x00000000 MCWDT Subcounter Control Register */
  un_MCWDT_CTR_LOWER_LIMIT_t       unLOWER_LIMIT;      /*!< 0x00000004 MCWDT Subcounter Lower Limit Register */
  un_MCWDT_CTR_UPPER_LIMIT_t       unUPPER_LIMIT;      /*!< 0x00000008 MCWDT Subcounter Upper Limit Register */
  un_MCWDT_CTR_WARN_LIMIT_t        unWARN_LIMIT;       /*!< 0x0000000C MCWDT Subcounter Warn Limit Register */
  un_MCWDT_CTR_CONFIG_t            unCONFIG;           /*!< 0x00000010 MCWDT Subcounter Configuration Register */
  un_MCWDT_CTR_CNT_t               unCNT;              /*!< 0x00000014 MCWDT Subcounter Count Register */
  uint32_t                         au32Reserved[2];
} stc_MCWDT_CTR_t;

typedef struct stc_MCWDT_CTR2_CTL_field {
  uint32_t                         u1ENABLED:1;
  uint32_t                         :30;
  uint32_t                         u1ENABLE:1;
} stc_MCWDT_CTR2_CTL_field_t;

typedef union un_MCWDT_CTR2_CTL {
  uint32_t                         u32Register;
  stc_MCWDT_CTR2_CTL_field_t       stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_CTR2_CTL_t;

typedef struct stc_MCWDT_CPU_SELECT_field {
  uint32_t                         u2CPU_SEL:2;
  uint32_t                         :30;
} stc_MCWDT_CPU_SELECT_field_t;

typedef union un_MCWDT_CPU_SELECT {
  uint32_t                         u32Register;
  stc_MCWDT_CPU_SELECT_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_CPU_SELECT_t;

/**
  * \brief MCWDT Subcounter 2 Count Register (MCWDT_CTR2_CNT)
  */
typedef struct stc_MCWDT_CTR2_CNT_field {
  uint32_t                         u32CNT2:32;
} stc_MCWDT_CTR2_CNT_field_t;

typedef union un_MCWDT_CTR2_CNT {
  uint32_t                         u32Register;
  stc_MCWDT_CTR2_CNT_field_t       stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_CTR2_CNT_t;

/**
  * \brief MCWDT Subcounter 2 Configuration register (MCWDT_CTR2_CONFIG)
  */
typedef struct stc_MCWDT_CTR2_CONFIG_field {
  uint32_t                         u1ACTION:1;
  uint32_t                         :15;
  uint32_t                         u5BITS:5;
  uint32_t                         :7;
  uint32_t                         u1DEBUG_TRIGGER_EN:1;
  uint32_t                         :1;
  uint32_t                         u1SLEEPDEEP_PAUSE:1;
  uint32_t                         u1DEBUG_RUN:1;
} stc_MCWDT_CTR2_CONFIG_field_t;

typedef union un_MCWDT_CTR2_CONFIG {
  uint32_t                         u32Register;
  stc_MCWDT_CTR2_CONFIG_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_CTR2_CONFIG_t;

typedef struct stc_MCWDT_INTR_field {
  uint32_t                         u1CTR0_INT:1;
  uint32_t                         u1CTR1_INT:1;
  uint32_t                         u1CTR2_INT:1;
  uint32_t                         :29;
} stc_MCWDT_INTR_field_t;

typedef union un_MCWDT_INTR {
  uint32_t                         u32Register;
  stc_MCWDT_INTR_field_t           stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_INTR_t;

/**
  * \brief MCWDT Interrupt Set Register (MCWDT_INTR_SET)
  */
typedef struct stc_MCWDT_INTR_SET_field {
  uint32_t                         u1CTR0_INT:1;
  uint32_t                         u1CTR1_INT:1;
  uint32_t                         u1CTR2_INT:1;
  uint32_t                         :29;
} stc_MCWDT_INTR_SET_field_t;

typedef union un_MCWDT_INTR_SET {
  uint32_t                         u32Register;
  stc_MCWDT_INTR_SET_field_t       stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_INTR_SET_t;

/**
  * \brief MCWDT Interrupt Mask Register (MCWDT_INTR_MASK)
  */
typedef struct stc_MCWDT_INTR_MASK_field {
  uint32_t                         u1CTR0_INT:1;
  uint32_t                         u1CTR1_INT:1;
  uint32_t                         u1CTR2_INT:1;
  uint32_t                         :29;
} stc_MCWDT_INTR_MASK_field_t;

typedef union un_MCWDT_INTR_MASK {
  uint32_t                         u32Register;
  stc_MCWDT_INTR_MASK_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_INTR_MASK_t;

/**
  * \brief MCWDT Interrupt Masked Register (MCWDT_INTR_MASKED)
  */
typedef struct stc_MCWDT_INTR_MASKED_field {
  uint32_t                         u1CTR0_INT:1;
  uint32_t                         u1CTR1_INT:1;
  uint32_t                         u1CTR2_INT:1;
  uint32_t                         :29;
} stc_MCWDT_INTR_MASKED_field_t;

typedef union un_MCWDT_INTR_MASKED {
  uint32_t                         u32Register;
  stc_MCWDT_INTR_MASKED_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_MCWDT_INTR_MASKED_t;

typedef struct stc_MCWDT {
  stc_MCWDT_CTR_t                  CTR[2];             /*!< 0x00000000 MCWDT Configuration for Subcounter 0 and 1 */
  un_MCWDT_CPU_SELECT_t            unCPU_SELECT;       /*!< 0x00000040 MCWDT CPU selection register */
  uint32_t                         au32Reserved[15];
  un_MCWDT_CTR2_CTL_t              unCTR2_CTL;         /*!< 0x00000080 MCWDT Subcounter 2 Control register */
  un_MCWDT_CTR2_CONFIG_t           unCTR2_CONFIG;      /*!< 0x00000084 MCWDT Subcounter 2 Configuration register */
  un_MCWDT_CTR2_CNT_t              unCTR2_CNT;         /*!< 0x00000088 MCWDT Subcounter 2 Count Register */
  uint32_t                         u32Reserved1;
  un_MCWDT_LOCK_t                  unLOCK;             /*!< 0x00000090 MCWDT Lock Register */
  un_MCWDT_SERVICE_t               unSERVICE;          /*!< 0x00000094 MCWDT Service Register */
  uint32_t                         au32Reserved2[2];
  un_MCWDT_INTR_t                  unINTR;             /*!< 0x000000A0 MCWDT Interrupt Register */
  un_MCWDT_INTR_SET_t              unINTR_SET;         /*!< 0x000000A4 MCWDT Interrupt Set Register */
  un_MCWDT_INTR_MASK_t             unINTR_MASK;        /*!< 0x000000A8 MCWDT Interrupt Mask Register */
  un_MCWDT_INTR_MASKED_t           unINTR_MASKED;      /*!< 0x000000AC MCWDT Interrupt Masked Register */
  uint32_t                         au32Reserved3[20];
} stc_MCWDT_t;                                         /*!< Size = 256 (0x100) */



typedef struct stc_WDT_SERVICE_field {
  uint32_t                         u1SERVICE:1;
  uint32_t                         :31;
} stc_WDT_SERVICE_field_t;


typedef union un_WDT_SERVICE {
  uint32_t                         u32Register;
  stc_WDT_SERVICE_field_t          stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_WDT_SERVICE_t;

typedef struct stc_WDT_CONFIG_field {
  uint32_t                         u1LOWER_ACTION:1;
  uint32_t                         :3;
  uint32_t                         u1UPPER_ACTION:1;
  uint32_t                         :3;
  uint32_t                         u1WARN_ACTION:1;
  uint32_t                         :3;
  uint32_t                         u1AUTO_SERVICE:1;
  uint32_t                         :15;
  uint32_t                         u1DEBUG_TRIGGER_EN:1;
  uint32_t                         u1DPSLP_PAUSE:1;
  uint32_t                         u1HIB_PAUSE:1;
  uint32_t                         u1DEBUG_RUN:1;
} stc_WDT_CONFIG_field_t;

typedef union un_WDT_CONFIG {
  uint32_t                         u32Register;
  stc_WDT_CONFIG_field_t           stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];

} un_WDT_CONFIG_t;

/**
  * \brief WDT Count Register (WDT_CNT)
  */
typedef struct stc_WDT_CNT_field {
  uint32_t                         u32CNT:32;
} stc_WDT_CNT_field_t;

typedef union un_WDT_CNT {
  uint32_t                         u32Register;
  stc_WDT_CNT_field_t              stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_WDT_CNT_t;

/**
  * \brief WDT Lock register (WDT_LOCK)
  */
typedef struct stc_WDT_LOCK_field {
  uint32_t                         u2WDT_LOCK:2;
  uint32_t                         :30;
} stc_WDT_LOCK_field_t;

typedef union un_WDT_LOCK {
  uint32_t                         u32Register;
  stc_WDT_LOCK_field_t             stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_WDT_LOCK_t;

/**
  * \brief WDT Interrupt Register (WDT_INTR)
  */
typedef struct stc_WDT_INTR_field {
  uint32_t                         u1WDT:1;
  uint32_t                         :31;
} stc_WDT_INTR_field_t;

typedef union un_WDT_INTR {
  uint32_t                         u32Register;
  stc_WDT_INTR_field_t             stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_WDT_INTR_t;

/**
  * \brief WDT Interrupt Set Register (WDT_INTR_SET)
  */
typedef struct stc_WDT_INTR_SET_field {
  uint32_t                         u1WDT:1;
  uint32_t                         :31;
} stc_WDT_INTR_SET_field_t;

typedef union un_WDT_INTR_SET {
  uint32_t                         u32Register;
  stc_WDT_INTR_SET_field_t         stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_WDT_INTR_SET_t;

/**
  * \brief WDT Interrupt Mask Register (WDT_INTR_MASK)
  */
typedef struct stc_WDT_INTR_MASK_field {
  uint32_t                         u1WDT:1;
  uint32_t                         :31;
} stc_WDT_INTR_MASK_field_t;

typedef union un_WDT_INTR_MASK {
  uint32_t                         u32Register;
  stc_WDT_INTR_MASK_field_t        stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_WDT_INTR_MASK_t;

/**
  * \brief WDT Interrupt Masked Register (WDT_INTR_MASKED)
  */
typedef struct stc_WDT_INTR_MASKED_field {
  uint32_t                         u1WDT:1;
  uint32_t                         :31;
} stc_WDT_INTR_MASKED_field_t;

typedef union un_WDT_INTR_MASKED {
  uint32_t                         u32Register;
  stc_WDT_INTR_MASKED_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_WDT_INTR_MASKED_t;

/**
  * \brief WDT Control Register (WDT_CTL)
  */
typedef struct stc_WDT_CTL_field {
  uint32_t                         u1ENABLED:1;
  uint32_t                         :30;
  uint32_t                         u1ENABLE:1;
} stc_WDT_CTL_field_t;

typedef union un_WDT_CTL {
  uint32_t                         u32Register;
  stc_WDT_CTL_field_t              stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_WDT_CTL_t;

/**
  * \brief WDT Lower Limit Register (WDT_LOWER_LIMIT)
  */
typedef struct stc_WDT_LOWER_LIMIT_field {
  uint32_t                         u32LOWER_LIMIT:32;
} stc_WDT_LOWER_LIMIT_field_t;

typedef union un_WDT_LOWER_LIMIT {
  uint32_t                         u32Register;
  stc_WDT_LOWER_LIMIT_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_WDT_LOWER_LIMIT_t;

/**
  * \brief WDT Upper Limit Register (WDT_UPPER_LIMIT)
  */
typedef struct stc_WDT_UPPER_LIMIT_field {
  uint32_t                         u32UPPER_LIMIT:32;
} stc_WDT_UPPER_LIMIT_field_t;

typedef union un_WDT_UPPER_LIMIT {
  uint32_t                         u32Register;
  stc_WDT_UPPER_LIMIT_field_t      stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_WDT_UPPER_LIMIT_t;

/**
  * \brief WDT Warn Limit Register (WDT_WARN_LIMIT)
  */
typedef struct stc_WDT_WARN_LIMIT_field {
  uint32_t                         u32WARN_LIMIT:32;
} stc_WDT_WARN_LIMIT_field_t;

typedef union un_WDT_WARN_LIMIT {
  uint32_t                         u32Register;
  stc_WDT_WARN_LIMIT_field_t       stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_WDT_WARN_LIMIT_t;

typedef struct stc_WDT {
  un_WDT_CTL_t                     unCTL;              /*!< 0x00000000 WDT Control Register */
  un_WDT_LOWER_LIMIT_t             unLOWER_LIMIT;      /*!< 0x00000004 WDT Lower Limit Register */
  un_WDT_UPPER_LIMIT_t             unUPPER_LIMIT;      /*!< 0x00000008 WDT Upper Limit Register */
  un_WDT_WARN_LIMIT_t              unWARN_LIMIT;       /*!< 0x0000000C WDT Warn Limit Register */
  un_WDT_CONFIG_t                  unCONFIG;           /*!< 0x00000010 WDT Configuration Register */
  un_WDT_CNT_t                     unCNT;              /*!< 0x00000014 WDT Count Register */
  uint32_t                         au32Reserved[10];
  un_WDT_LOCK_t                    unLOCK;             /*!< 0x00000040 WDT Lock register */
  un_WDT_SERVICE_t                 unSERVICE;          /*!< 0x00000044 WDT Service register */
  uint32_t                         au32Reserved1[2];
  un_WDT_INTR_t                    unINTR;             /*!< 0x00000050 WDT Interrupt Register */
  un_WDT_INTR_SET_t                unINTR_SET;         /*!< 0x00000054 WDT Interrupt Set Register */
  un_WDT_INTR_MASK_t               unINTR_MASK;        /*!< 0x00000058 WDT Interrupt Mask Register */
  un_WDT_INTR_MASKED_t             unINTR_MASKED;      /*!< 0x0000005C WDT Interrupt Masked Register */
  uint32_t                         au32Reserved2[8];
} stc_WDT_t;


typedef struct stc_WATCHDOG {

  stc_MCWDT_t                      MCWDT[4];           /*!< 0x00008000 Multi-Counter Watchdog Timer */
  uint32_t                         au32Reserved27[3840];
  stc_WDT_t                        WDT;                /*!< 0x0000C000 Watchdog Timer */

} stc_WATCHDOG_t;


/*210823, to control REG Hc Enable*/
/**
  * \brief Power Mode Control (PWR_CTL)
  */
typedef struct stc_PWR_CTL_field {
  uint32_t                         u2POWER_MODE:2;
  uint32_t                         :2;
  uint32_t                         u1DEBUG_SESSION:1;
  uint32_t                         u1LPM_READY:1;
  uint32_t                         :26;
} stc_PWR_CTL_field_t;

typedef union un_PWR_CTL {
  uint32_t                         u32Register;
  stc_PWR_CTL_field_t              stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_CTL_t;

/**
  * \brief Power Mode Control 2 (PWR_CTL2)
  */
typedef struct stc_PWR_CTL2_field {
  uint32_t                         u1LINREG_DIS:1;
  uint32_t                         u1LINREG_OK:1;
  uint32_t                         u1LINREG_LPMODE:1;
  uint32_t                         :1;
  uint32_t                         u1DPSLP_REG_DIS:1;
  uint32_t                         :3;
  uint32_t                         u1RET_REG_DIS:1;
  uint32_t                         :3;
  uint32_t                         u1NWELL_REG_DIS:1;
  uint32_t                         :3;
  uint32_t                         u1REFV_DIS:1;
  uint32_t                         u1REFV_OK:1;
  uint32_t                         :2;
  uint32_t                         u1REFVBUF_DIS:1;
  uint32_t                         u1REFVBUF_OK:1;
  uint32_t                         u1REFVBUF_LPMODE:1;
  uint32_t                         :1;
  uint32_t                         u1REFI_DIS:1;
  uint32_t                         u1REFI_OK:1;
  uint32_t                         u1REFI_LPMODE:1;
  uint32_t                         u1PORBOD_LPMODE:1;
  uint32_t                         u1BGREF_LPMODE:1;
  uint32_t                         :2;
  uint32_t                         u1PLL_LS_BYPASS:1;
} stc_PWR_CTL2_field_t;

typedef union un_PWR_CTL2 {
  uint32_t                         u32Register;
  stc_PWR_CTL2_field_t             stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_CTL2_t;


/**
  * \brief HIBERNATE Mode Register (PWR_HIBERNATE)
  */
typedef struct stc_PWR_HIBERNATE_field {
  uint32_t                         u8TOKEN:8;
  uint32_t                         u8UNLOCK:8;
  uint32_t                         :1;
  uint32_t                         u1FREEZE:1;
  uint32_t                         u1MASK_HIBALARM:1;
  uint32_t                         u1MASK_HIBWDT:1;
  uint32_t                         u4POLARITY_HIBPIN:4;
  uint32_t                         u4MASK_HIBPIN:4;
  uint32_t                         :2;
  uint32_t                         u1HIBERNATE_DISABLE:1;
  uint32_t                         u1HIBERNATE:1;
} stc_PWR_HIBERNATE_field_t;

typedef union un_PWR_HIBERNATE {
  uint32_t                         u32Register;
  stc_PWR_HIBERNATE_field_t        stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_HIBERNATE_t;

/**
  * \brief Buck Control Register (PWR_BUCK_CTL)
  */
typedef struct stc_PWR_BUCK_CTL_field {
  uint32_t                         u3BUCK_OUT1_SEL:3;
  uint32_t                         :27;
  uint32_t                         u1BUCK_EN:1;
  uint32_t                         u1BUCK_OUT1_EN:1;
} stc_PWR_BUCK_CTL_field_t;

typedef union un_PWR_BUCK_CTL {
  uint32_t                         u32Register;
  stc_PWR_BUCK_CTL_field_t         stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_BUCK_CTL_t;

/**
  * \brief Buck Control Register 2 (PWR_BUCK_CTL2)
  */
typedef struct stc_PWR_BUCK_CTL2_field {
  uint32_t                         u3BUCK_OUT2_SEL:3;
  uint32_t                         :27;
  uint32_t                         u1BUCK_OUT2_HW_SEL:1;
  uint32_t                         u1BUCK_OUT2_EN:1;
} stc_PWR_BUCK_CTL2_field_t;

typedef union un_PWR_BUCK_CTL2 {
  uint32_t                         u32Register;
  stc_PWR_BUCK_CTL2_field_t        stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_BUCK_CTL2_t;

/**
  * \brief Supply Supervision Control Register (PWR_SSV_CTL)
  */
typedef struct stc_PWR_SSV_CTL_field {
  uint32_t                         u1BODVDDD_VSEL:1;
  uint32_t                         :2;
  uint32_t                         u1BODVDDD_ENABLE:1;
  uint32_t                         u1BODVDDA_VSEL:1;
  uint32_t                         :1;
  uint32_t                         u2BODVDDA_ACTION:2;
  uint32_t                         u1BODVDDA_ENABLE:1;
  uint32_t                         :2;
  uint32_t                         u1BODVCCD_ENABLE:1;
  uint32_t                         :4;
  uint32_t                         u1OVDVDDD_VSEL:1;
  uint32_t                         :2;
  uint32_t                         u1OVDVDDD_ENABLE:1;
  uint32_t                         u1OVDVDDA_VSEL:1;
  uint32_t                         :1;
  uint32_t                         u2OVDVDDA_ACTION:2;
  uint32_t                         u1OVDVDDA_ENABLE:1;
  uint32_t                         :2;
  uint32_t                         u1OVDVCCD_ENABLE:1;
  uint32_t                         :4;
} stc_PWR_SSV_CTL_field_t;

typedef union un_PWR_SSV_CTL {
  uint32_t                         u32Register;
  stc_PWR_SSV_CTL_field_t          stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_SSV_CTL_t;

/**
  * \brief Supply Supervision Status Register (PWR_SSV_STATUS)
  */
typedef struct stc_PWR_SSV_STATUS_field {
  uint32_t                         u1BODVDDD_OK:1;
  uint32_t                         u1BODVDDA_OK:1;
  uint32_t                         u1BODVCCD_OK:1;
  uint32_t                         :5;
  uint32_t                         u1OVDVDDD_OK:1;
  uint32_t                         u1OVDVDDA_OK:1;
  uint32_t                         u1OVDVCCD_OK:1;
  uint32_t                         :5;
  uint32_t                         u1OCD_ACT_LINREG_OK:1;
  uint32_t                         u1OCD_DPSLP_REG_OK:1;
  uint32_t                         :14;
} stc_PWR_SSV_STATUS_field_t;

typedef union un_PWR_SSV_STATUS {
  uint32_t                         u32Register;
  stc_PWR_SSV_STATUS_field_t       stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_SSV_STATUS_t;

/**
  * \brief High Voltage / Low Voltage Detector (HVLVD) Configuration Register (PWR_LVD_CTL)
  */
typedef struct stc_PWR_LVD_CTL_field {
  uint32_t                         u4HVLVD1_TRIPSEL:4;
  uint32_t                         u3HVLVD1_SRCSEL:3;
  uint32_t                         u1HVLVD1_EN:1;
  uint32_t                         u5HVLVD1_TRIPSEL_HT:5;
  uint32_t                         :1;
  uint32_t                         u1HVLVD1_DPSLP_EN_HT:1;
  uint32_t                         u1HVLVD1_EN_HT:1;
  uint32_t                         u2HVLVD1_EDGE_SEL:2;
  uint32_t                         u1HVLVD1_ACTION:1;
  uint32_t                         :13;
} stc_PWR_LVD_CTL_field_t;

typedef union un_PWR_LVD_CTL {
  uint32_t                         u32Register;
  stc_PWR_LVD_CTL_field_t          stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_LVD_CTL_t;

/**
  * \brief High Voltage / Low Voltage Detector (HVLVD) Configuration Register #2 (PWR_LVD_CTL2)
  */
typedef struct stc_PWR_LVD_CTL2_field {
  uint32_t                         :8;
  uint32_t                         u5HVLVD2_TRIPSEL_HT:5;
  uint32_t                         :1;
  uint32_t                         u1HVLVD2_DPSLP_EN_HT:1;
  uint32_t                         u1HVLVD2_EN_HT:1;
  uint32_t                         u2HVLVD2_EDGE_SEL:2;
  uint32_t                         u1HVLVD2_ACTION:1;
  uint32_t                         :13;
} stc_PWR_LVD_CTL2_field_t;

typedef union un_PWR_LVD_CTL2 {
  uint32_t                         u32Register;
  stc_PWR_LVD_CTL2_field_t         stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_LVD_CTL2_t;

/**
  * \brief REGHC Control Register (PWR_REGHC_CTL)
  */
typedef struct stc_PWR_REGHC_CTL_field {
  uint32_t                         u1REGHC_MODE:1;
  uint32_t                         :1;
  uint32_t                         u2REGHC_PMIC_DRV_VOUT:2;
  uint32_t                         u5REGHC_VADJ:5;
  uint32_t                         :1;
  uint32_t                         u1REGHC_PMIC_USE_LINREG:1;
  uint32_t                         u1REGHC_PMIC_USE_RADJ:1;
  uint32_t                         u3REGHC_PMIC_RADJ:3;
  uint32_t                         :1;
  uint32_t                         u1REGHC_PMIC_CTL_OUTEN:1;
  uint32_t                         u1REGHC_PMIC_CTL_POLARITY:1;
  uint32_t                         u1REGHC_PMIC_STATUS_INEN:1;
  uint32_t                         u1REGHC_PMIC_STATUS_POLARITY:1;
  uint32_t                         u10REGHC_PMIC_STATUS_WAIT:10;
  uint32_t                         u1REGHC_TRANS_USE_OCD:1;
  uint32_t                         u1REGHC_CONFIGURED:1;
} stc_PWR_REGHC_CTL_field_t;

typedef union un_PWR_REGHC_CTL {
  uint32_t                         u32Register;
  stc_PWR_REGHC_CTL_field_t        stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_REGHC_CTL_t;

/**
  * \brief REGHC Status Register (PWR_REGHC_STATUS)
  */
typedef struct stc_PWR_REGHC_STATUS_field {
  uint32_t                         u1REGHC_ENABLED:1;
  uint32_t                         u1REGHC_OCD_OK:1;
  uint32_t                         u1REGHC_CKT_OK:1;
  uint32_t                         :5;
  uint32_t                         u1REGHC_UV_OUT:1;
  uint32_t                         u1REGHC_OV_OUT:1;
  uint32_t                         :2;
  uint32_t                         u1REGHC_PMIC_STATUS_OK:1;
  uint32_t                         :18;
  uint32_t                         u1REGHC_SEQ_BUSY:1;
} stc_PWR_REGHC_STATUS_field_t;

typedef union un_PWR_REGHC_STATUS {
  uint32_t                         u32Register;
  stc_PWR_REGHC_STATUS_field_t     stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_REGHC_STATUS_t;

/**
  * \brief REGHC Control Register 2 (PWR_REGHC_CTL2)
  */
typedef struct stc_PWR_REGHC_CTL2_field {
  uint32_t                         u8REGHC_PMIC_STATUS_TIMEOUT:8;
  uint32_t                         :23;
  uint32_t                         u1REGHC_EN:1;
} stc_PWR_REGHC_CTL2_field_t;

typedef union un_PWR_REGHC_CTL2 {
  uint32_t                         u32Register;
  stc_PWR_REGHC_CTL2_field_t       stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PWR_REGHC_CTL2_t;

typedef struct stc_SRSS0 {
  un_PWR_CTL_t                     unPWR_CTL;          /*!< 0x00001000 Power Mode Control */
  un_PWR_CTL2_t                    unPWR_CTL2;         /*!< 0x00001004 Power Mode Control 2 */
  un_PWR_HIBERNATE_t               unPWR_HIBERNATE;    /*!< 0x00001008 HIBERNATE Mode Register */
  uint32_t                         u32Reserved4;
  un_PWR_BUCK_CTL_t                unPWR_BUCK_CTL;     /*!< 0x00001010 Buck Control Register */
  un_PWR_BUCK_CTL2_t               unPWR_BUCK_CTL2;    /*!< 0x00001014 Buck Control Register 2 */
  un_PWR_SSV_CTL_t                 unPWR_SSV_CTL;      /*!< 0x00001018 Supply Supervision Control Register */
  un_PWR_SSV_STATUS_t              unPWR_SSV_STATUS;   /*!< 0x0000101C Supply Supervision Status Register */
  un_PWR_LVD_CTL_t                 unPWR_LVD_CTL;      /*!< 0x00001020 High Voltage / Low Voltage Detector (HVLVD)
                                                                                Configuration Register */
  un_PWR_LVD_CTL2_t                unPWR_LVD_CTL2;     /*!< 0x00001024 High Voltage / Low Voltage Detector (HVLVD)
                                                                                Configuration Register #2 */
  un_PWR_REGHC_CTL_t               unPWR_REGHC_CTL;    /*!< 0x00001028 REGHC Control Register */
  un_PWR_REGHC_STATUS_t            unPWR_REGHC_STATUS; /*!< 0x0000102C REGHC Status Register */
  un_PWR_REGHC_CTL2_t              unPWR_REGHC_CTL2;   /*!< 0x00001030 REGHC Control Register 2 */
} stc_SRSS0_t;


/*******************************************************************************
*                                     PERI
*******************************************************************************/

#define PERI_BASE                               0x40004000UL
#define PERI                                    ((volatile stc_PERI_t*) PERI_BASE)                                /* 0x40000000 */

/**
  * \brief Clock control (PERI_GR_CLOCK_CTL)
  */
typedef struct stc_PERI_GR_CLOCK_CTL_field {
  uint32_t                         :8;
  uint32_t                         u8INT8_DIV:8;
  uint32_t                         :16;
} stc_PERI_GR_CLOCK_CTL_field_t;

typedef union un_PERI_GR_CLOCK_CTL {
  uint32_t                         u32Register;
  stc_PERI_GR_CLOCK_CTL_field_t    stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PERI_GR_CLOCK_CTL_t;

/**
  * \brief Slave control (PERI_GR_SL_CTL)
  */
typedef struct stc_PERI_GR_SL_CTL_field {
  uint32_t                         u1ENABLED_0:1;
  uint32_t                         u1ENABLED_1:1;
  uint32_t                         u1ENABLED_2:1;
  uint32_t                         u1ENABLED_3:1;
  uint32_t                         u1ENABLED_4:1;
  uint32_t                         u1ENABLED_5:1;
  uint32_t                         u1ENABLED_6:1;
  uint32_t                         u1ENABLED_7:1;
  uint32_t                         u1ENABLED_8:1;
  uint32_t                         u1ENABLED_9:1;
  uint32_t                         u1ENABLED_10:1;
  uint32_t                         u1ENABLED_11:1;
  uint32_t                         u1ENABLED_12:1;
  uint32_t                         u1ENABLED_13:1;
  uint32_t                         u1ENABLED_14:1;
  uint32_t                         u1ENABLED_15:1;
  uint32_t                         :16;
} stc_PERI_GR_SL_CTL_field_t;

typedef union un_PERI_GR_SL_CTL {
  uint32_t                         u32Register;
  stc_PERI_GR_SL_CTL_field_t       stcField;
  uint8_t                          au8Byte[4];
  uint16_t                         au16Halfword[2];
} un_PERI_GR_SL_CTL_t;

/**
  * \brief Peripheral group structure (PERI_GR)
  */
typedef struct stc_PERI_GR {
  un_PERI_GR_CLOCK_CTL_t           unCLOCK_CTL;        /*!< 0x00000000 Clock control */
  uint32_t                         au32Reserved[3];
  un_PERI_GR_SL_CTL_t              unSL_CTL;           /*!< 0x00000010 Slave control */
  uint32_t                         au32Reserved1[11];
} stc_PERI_GR_t;

typedef struct stc_PERI {
  stc_PERI_GR_t                    GR[16];             /*!< 0x00004000 Peripheral group structure */
} stc_PERI_t;



#define UNKNOWN_WAKE_UP         0x00U
#define EVENT_GENERATOR_WAKE_UP 0x01U
#define CAN_WAKE_UP             0x02U
#define LIN_WAKE_UP             0x04U
#define ADC_WAKE_UP             0x08U // LPTask time > WDG TIMEOUT

typedef enum
{
    CY_MCWDT_COUNTER0,  /**< Sub-counter#0 identifier. */
    CY_MCWDT_COUNTER1,  /**< Sub-counter#1 identifier. */
    CY_MCWDT_COUNTER2   /**< Sub-counter#2 identifier. */
} cy_en_mcwdtctr_t;

typedef enum
{
    CY_MCWDT_PAUSED_BY_DPSLP_CM0 = 0u,
    CY_MCWDT_PAUSED_BY_DPSLP_CM4_CM7_0 = 1u,
    CY_MCWDT_PAUSED_BY_DPSLP_CM7_1 = 2u,
    CY_MCWDT_PAUSED_BY_NO_CORE = 3u,
} cy_en_mcwdt_select_core_t;

typedef enum
{
    CY_MCWDT_ACTION_NONE,                 /**< The No action mode. It is used for Set/GetMode functions. */
    CY_MCWDT_ACTION_FAULT,                /**< The Fault mode. It is used for Set/GetMode functions. */
    CY_MCWDT_ACTION_FAULT_THEN_RESET,     /**< The Reset mode. It is used for Set/GetMode functions. */
} cy_en_mcwdt_lower_upper_action_t;

typedef enum
{
    CY_MCWDT_WARN_ACTION_NONE,
    CY_MCWDT_WARN_ACTION_INT,
} cy_en_mcwdt_warn_action_t;

/*
 * Define NULL pointer value.
 */
#ifndef NULL
#define NULL  (void *) 0
#endif

#define LP_ADC_PHY_NO             8
#define LP_ADC_LOGICAL_CH         8
#define LP_ADC_CH_NO      ((volatile stc_PASS_SAR_CH_t*) &PASS0->SAR[0].CH[LP_ADC_LOGICAL_CH]) //ADC[0]_8 P7.0 IGN AI


#endif /* #define SLPWUP_LPTM_REGDEF_H */
