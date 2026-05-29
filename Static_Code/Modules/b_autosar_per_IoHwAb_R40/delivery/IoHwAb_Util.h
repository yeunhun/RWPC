/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_Util.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : Time constant definitions for IOHWAB                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.15.0.2  09-Sep-2021   Yangjin        #31974                              **
** 1.15.0    09-Sep-2021   Yangjin        #31974                              **
** 1.11.0    24-Sep-2020   Yangjin        #25514, #25515                      **
** 1.10.1    04-Aug-2020   Yangjin        #24902                              **
** 1.9.0     04-Jun-2020   Yangjin        #23696, #23742                      **
** 1.8.1     08-May-2020   Yangjin        #23096                              **
** 1.8.0     21-Apr-2020   Yangjin        #22141                              **
** 1.7.0     26-Nov-2019   Yangjin        #19730                              **
** 1.5.0     28-Aug-2019   Yangjin        #18753                              **
** 1.3.2     04-Jun-2019   Yangjin        #17709                              **
** 1.3.1     30-Apr-2019   Yangjin        #16955                              **
** 1.1.1     08-Aug-2018   Jongyoung      #13075                              **
** 1.1.0     05-Apr-2018   Jongyoung      #12280                              **
** 1.0.13    18-Sep-2017   Jongyoung      #9949, #9939                        **
** 1.0.12    05-Mar-2017   Jongyoung      #7764, #7328                        **
** 1.0.11    12-Jan-2017   Jongyoung      #7140                               **
** 1.0.10    11-Dec-2016   Jongyoung      #6845, #6929                        **
** 1.0.9     05-Dec-2016   Jongyoung      #5227, #6845                        **
** 1.0.8     19-Apr-2016   Jongyoung      #5613, #5686                        **
** 1.0.7     19-Apr-2016   Jongyoung      #4654, #4514                        **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.9 [Justified:Unset] "Not a defect" */
/* polyspace-begin MISRA-C3:10.7 [Justified:Low] "Validated by test cases. It works as intended." */

#ifndef IOHWAB_UTIL_H
#define IOHWAB_UTIL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Cfg.h"

#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#include "Reg_eSys_Stm.h"
#include "Reg_eSys_Rtc.h"
#include "Reg_eSys_SIUL.h"
#include "Reg_eSys_ADCDig.h"
#include "Reg_Macros.h"

#elif (defined(IOHWAB_MCAL_ST_SPC58XCX) || defined(IOHWAB_MCAL_ST_SPC58XHX))
#include "Reg_eSys_Stm.h"
#include "Reg_eSys_Rtc.h"
#include "Reg_eSys_SIUL.h"
#include "Reg_eSys_ADCDigv2.h"
#include "Reg_Macros.h"

#elif (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
    || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
    || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X) \
    || defined(IOHWAB_MCAL_INFINEON_TC38X) || defined(IOHWAB_MCAL_INFINEON_TC39X) )
#include "Os_Arch_Regs.h"
#include "IfxPort_reg.h"
#include "IfxSrc_reg.h"

#elif (defined(IOHWAB_MCAL_CYPRESS_S6J32XX))
#include "s6j3200_ADC12B.h"
#include "Adc_Stream.h"
#include "s6j3200_RLT.h"

#elif (defined(IOHWAB_MCAL_CYPRESS_S6J33XX))
#include "s6j3300_ADC12B.h"
#include "Adc_Stream.h"
#include "s6j3300_RLT.h"

#elif (defined(IOHWAB_MCAL_CYPRESS_CYT2B9XX) || defined(IOHWAB_MCAL_CYPRESS_CYT4BBXX))
#include "Adc_Internal.h"
#include "Adc_Data.h"

#elif (defined(IOHWAB_MCAL_FREESCALE_MPC574XR))
#include "Adc_Reg_eSys_Adcdig.h"
#include "Reg_eSys_Stm.h"
#include "Reg_eSys_Rtc.h"
#include "Reg_eSys_SIUL2.h"
#include "StdRegMacros.h"

#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413) \
    || defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
#include "Adc_Private.h"

#elif (defined(IOHWAB_MCAL_NXP_S32K14X))
#include "Os.h"
#include "StdRegMacros.h"
#include "Adc_Reg_eSys_Adc12bsarv2.h"

#elif (defined(IOHWAB_MCAL_NXP_S32G2X))
#include "Os.h"
#include "StdRegMacros.h"
#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.3 [Justified:Low] "whether this macro is used depends on the configurations." */
/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "whether this macro is used depends on the configurations." */
/* Multiple to convert sec to msec */
#define IOHWAB_SEC_TO_MSEC      (1000u)

/* Multiple to convert msec to usec */
#define IOHWAB_MSEC_TO_USEC     (1000u)

/* Multiple to convert sec to usec */
#define IOHWAB_SEC_TO_USEC      (1000000u)

typedef uint32	IoHwAb_DelayUsecType;
typedef uint16	IoHwAb_DelayMsecType;
typedef float32 IoHwAb_DelaySecType;

typedef uint32	IoHwAb_StmTickType;
typedef uint32	IoHwAb_GptTickType;
#if (defined(IOHWAB_MCAL_FREESCALE_MPC560XB) || (defined(IOHWAB_MCAL_ST_SPC58XCX)) \
  || defined(IOHWAB_MCAL_ST_SPC58XHX))
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> No Impact of this rule violation */
typedef unsigned long long  IoHwAb_LongType;
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> No Impact of this rule violation */
#elif (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
    || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
    || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X) \
    || defined(IOHWAB_MCAL_INFINEON_TC38X) || defined(IOHWAB_MCAL_INFINEON_TC39X) )
typedef uint32  IoHwAb_LongType;
#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413) \
    || defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
typedef uint8  IoHwAb_StmStatusType;
typedef uint32 IoHwAb_LongType;

#elif (defined(IOHWAB_MCAL_CYPRESS_S6J33XX) || defined(IOHWAB_MCAL_CYPRESS_CYT2B9XX) \
    || defined(IOHWAB_MCAL_CYPRESS_CYT4BBXX))
typedef uint32 IoHwAb_LongType;

#endif

/*******************************************************************************
**                      Mcu Dependent Macros                                  **
*******************************************************************************/
/* polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation */
/* polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations> No Impact of this rule violation */
/* Freescale Bolero */
#if (defined(IOHWAB_MCAL_FREESCALE_MPC560XB) || (defined(IOHWAB_MCAL_ST_SPC58XCX)) \
  || defined(IOHWAB_MCAL_ST_SPC58XHX))
#define IOHWAB_MCU_CLK_DIV      (4U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */
/* Upper limit of STM ticks */
#define IOHWAB_STM_TICK_MAX     ((IoHwAb_StmTickType) STM_CNT_MAX_VALUE)
/* Upper limit of GPT ticks */
#define IOHWAB_GPT_TICK_MAX     ((IoHwAb_GptTickType) RTC_API_RTCC_APIVAL_MAX_VALUE)

#define IOHWAB_NOP()            do{__asm("  nop");}while(0)
	
#define IOHWAB_ADC_ISR_ECH      (0x00000001U)

#if (ADC_SW_MAJOR_VERSION_REG > 1)
  #define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
      (REG_READ32(ADC_ISR_REG(ADC_ADDRESS(ADC_HWUNIT_NUM)))&(IOHWAB_ADC_ISR_ECH))
  #define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
      (REG_WRITE32( ADC_ISR_REG(ADC_ADDRESS(ADC_HWUNIT_NUM)),IOHWAB_ADC_ISR_ECH))
#else
  #define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
      (REG_READ32(ADC_ISR_REG(ADC_HWUNIT_NUM))&(IOHWAB_ADC_ISR_ECH))
  #define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
      (REG_WRITE32( ADC_ISR_REG(ADC_HWUNIT_NUM),IOHWAB_ADC_ISR_ECH))
#endif

/* Bolero do not need.*/
/* #define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  IOHWAB_NOP() */

/* Infineon AURIX */
#elif (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
    || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
    || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X) )
extern uint32 Os_GulStmClock;
#define IOHWAB_STM_FREQ_HZ      (Os_GulStmClock * 1000000)
#define IOHWAB_GPT_FREQ_HZ      (24414u)  /* GTM_FIXED_CLOCK_3 : 100MHz / 2^12 */
#define IOHWAB_NOP()            __nop()
#define IOHWAB_GET_TIMESTAMP()  OS_STM0_TIM0.U
#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xF0038984u
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(((uint32)(*(volatile uint32*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0x10u*(ADC_HWUNIT_NUM)))))&(((uint32)1U)<<24))
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
do{(((*(volatile uint32*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0x10u*(ADC_HWUNIT_NUM)))))|=(((uint32)1U)<<25));}while(0)
#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_IsrSrn1AdcRS1(ADC_HWUNIT_NUM);}while(0)

/* TC38X, TC39X */
#elif (defined(IOHWAB_MCAL_INFINEON_TC38X)) || (defined(IOHWAB_MCAL_INFINEON_TC39X))
extern uint32 Os_GulStmClock;
#define IOHWAB_STM_FREQ_HZ      (Os_GulStmClock * 1000000)
#define IOHWAB_GPT_FREQ_HZ      (24414u)  /* GTM_FIXED_CLOCK_3 : 100MHz / 2^12 */
#define IOHWAB_NOP()            __nop()
#define IOHWAB_GET_TIMESTAMP()  OS_STM0_TIM0.U
#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xF0038670u
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(((uint32)(*(volatile uint32*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0x10u*(ADC_HWUNIT_NUM)))))&(((uint32)1U)<<24))
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
do{(((*(volatile uint32*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0x10u*(ADC_HWUNIT_NUM)))))|=(((uint32)1U)<<25));}while(0)
#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_RS0EventInterruptHandler(ADC_HWUNIT_NUM);}while(0)

/* Renesas RH850F1L */
#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413))
#define IOHWAB_MCU_CLK_DIV      (6U)
#define IOHWAB_STM_FREQ_HZ      (8000000u) /* 8M/80 */
#define IOHWAB_GPT_FREQ_HZ      (8000000u) /* 8M/80 */

#define IOHWAB_NOP()            do{__asm("nop");}while(0)

#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xFFFF9014UL

/* Incase of INT sequence */
/* SG1 only for AdcReadDirect */
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
((uint32)(*(volatile uint32*)(0xfff20308UL + (0x1000UL*(ADC_HWUNIT_NUM)))&((uint32)0x0002U)))
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
do{(((*(volatile uint16*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0x1186UL*(ADC_HWUNIT_NUM)))))&=( (uint16)0xEFFFu ));}while(0)
#define IOHWAB_ADC_CONV_PROC( ADC_HWUNIT_NUM )  do{Adc_Isr( (uint8)(ADC_HWUNIT_NUM), 0U );}while(0)

/* Renesas RH850F1K */
#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM)) 
#define IOHWAB_MCU_CLK_DIV      (6U)
#define IOHWAB_STM_FREQ_HZ      (8000000u) /* 8M/80 */
#define IOHWAB_GPT_FREQ_HZ      (8000000u) /* 8M/80 */

#define IOHWAB_NOP()            do{__asm("nop");}while(0)


#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xFFFEEA24UL

/* Incase of INT sequence */
/* SG1 only for AdcReadDirect */
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(uint32)((*(volatile uint32*)(0xffd6d308UL + (0x1b3000UL*(((ADC_HWUNIT_NUM)+1u)&0x0001u))))&((uint32)0x0002u))

#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
do{(((*(volatile uint16*)(IOHWAB_ADC_CONV_BASE_ADDRESS + (0xc786UL*(ADC_HWUNIT_NUM)))))&=( (uint16)0xEFFFu ));}while(0)

#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_Isr( (uint8)(ADC_HWUNIT_NUM), 0U );}while(0)


/* Cypress S6J3200 */
#elif (defined(IOHWAB_MCAL_CYPRESS_S6J32XX))
#define IOHWAB_MCU_CLK_DIV      (6U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */

#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xB48C0300UL /* ADC12B0_CDONEIRQ0 */

#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(uint32)( (*(volatile uint32*)(0xB48C0300UL)) + (*(volatile uint32*)(0xB48C0304UL)) )
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) do{}while(0)

#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_IsrGroupConversionFinished(ADC_HWUNIT_NUM);}while(0)


/* Cypress S6J3300 */
#elif (defined(IOHWAB_MCAL_CYPRESS_S6J33XX) )
#define IOHWAB_MCU_CLK_DIV      (6U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */

#define IOHWAB_NOP()            
#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xB48C0300UL /* ADC12B0_CDONEIRQ0 */

#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(uint32)( (*(volatile uint32*)(0xB48C0300UL)) + (*(volatile uint32*)(0xB48C0304UL)) )
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) do{}while(0)

#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_IsrGroupConversionFinished(ADC_HWUNIT_NUM);}while(0)


/* Cypress CYT2B9XX, CYT4BBXX */
#elif (defined(IOHWAB_MCAL_CYPRESS_CYT2B9XX) || defined(IOHWAB_MCAL_CYPRESS_CYT4BBXX))
#define IOHWAB_MCU_CLK_DIV      (6U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */

#define IOHWAB_NOP()            
#define IOHWAB_ADC_CONV_BASE_ADDRESS 0xB48C0300UL /* ADC12B0_CDONEIRQ0 */

#define IOHWAB_ADC_CONV_COMPLETED(ADC_CH_BASE) \
(uint32)( (*(volatile uint32*)((ADC_CH_BASE) + 0x10UL)) )

#define IOHWAB_ADC_CONV_PROC(ADC_GROUP)  \
do{Adc_IsrGroupConversionFinished((const Adc_GroupConfigType *)Adc_GetGroupConfig(ADC_GROUP));}while(0)


/* Freescale MPC574XR */
#elif (defined(IOHWAB_MCAL_FREESCALE_MPC574XR))
#define IOHWAB_MCU_CLK_DIV      (4U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) 
#define IOHWAB_GPT_FREQ_HZ      (1000000u) 

#define IOHWAB_NOP()            do{__asm("  nop");}while(0)
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
        (REG_READ32(ADCDIG_ISR_REG_ADDR32(ADC_HWUNIT_NUM))&(ADCDIG_ISR_END_CHAIN_NORM_CLEAN_U32))
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
        (REG_WRITE32( ADCDIG_ISR_REG_ADDR32(ADC_HWUNIT_NUM),ADCDIG_ISR_END_CHANNEL_NORM_CONV_U32))

#elif (defined(IOHWAB_MCAL_NXP_S32K14X))
#define IOHWAB_MCU_CLK_DIV      (4U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */
/* Upper limit of STM ticks */
#define IOHWAB_STM_TICK_MAX     ((IoHwAb_StmTickType) STM_CNT_MAX_VALUE)
/* Upper limit of GPT ticks */
#define IOHWAB_GPT_TICK_MAX     ((IoHwAb_GptTickType) RTC_API_RTCC_APIVAL_MAX_VALUE)

#define IOHWAB_NOP()            do{__asm("  nop");}while(0)
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM, ADC_GROUP_LENGH)  (REG_READ32(ADC12BSARV2_SC1_REG_ADDR32((ADC_HWUNIT_NUM), (uint32)ADC_GROUP_LENGH)) & (0x00000080UL))

#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) ((*(volatile uint32*)((ADC12BSARV2_SC1_REG_ADDR32((ADC_HWUNIT_NUM), (uint32)0)))) &= (0xFFFFFFFFUL - 0xC0UL) )

/* NXP S32G2X */
#elif (defined(IOHWAB_MCAL_NXP_S32G2X))
#define IOHWAB_MCU_CLK_DIV      (4U)
#define IOHWAB_STM_FREQ_HZ      (1000000u) /* 64M/64 */
#define IOHWAB_GPT_FREQ_HZ      (1000000u) /* 64M/64 */
/* Upper limit of STM ticks */
#define IOHWAB_STM_TICK_MAX     ((IoHwAb_StmTickType) STM_CNT_MAX_VALUE_U32)
/* Upper limit of GPT ticks */
#define IOHWAB_GPT_TICK_MAX     ((IoHwAb_GptTickType) RTC_API_RTCC_APIVAL_MAX_VALUE_U32)

#define IOHWAB_NOP()            do{__asm("  nop");}while(0)
#define IOHWAB_ADC_BASE         (0x401F8000u)
#define IOHWAB_ADC_ISR_OFFSET   (0x00000010u)
#define IOHWAB_ADC_ISR_ADDRESS  (IOHWAB_ADC_BASE + IOHWAB_ADC_ISR_OFFSET)
#define IOHWAB_ADC_HWUNIT_OFFSET (0x000F0000u)

#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(((uint32)(*(volatile uint32*)((IOHWAB_ADC_ISR_ADDRESS) + (IOHWAB_ADC_HWUNIT_OFFSET*(ADC_HWUNIT_NUM)))))&(((uint32)1U)<<0))

#if (ADC_SW_MAJOR_VERSION >= 2)
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM)
#else
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
do{(((*(volatile uint32*)(IOHWAB_ADC_ISR_ADDRESS + (IOHWAB_ADC_HWUNIT_OFFSET*(ADC_HWUNIT_NUM)))))|=(((uint32)1U)<<0));}while(0)
#endif
/* TI TDA4X */
#elif (defined(IOHWAB_MCAL_TI_TDA4X))
#define IOHWAB_ADDRESS_ADC_STATUS_RAW 0x40200024UL /* ADC_STATUS_RAW Register */
#define IOHWAB_ADDRESS_ADC_STATUS 0x40200028UL  /* ADC_STATUS Register */
#define IOHWAB_ADC_CONV_COMPLETED(ADC_HWUNIT_NUM) \
(((uint32)(*(volatile uint32*)((IOHWAB_ADDRESS_ADC_STATUS_RAW) + (0x10000u*(ADC_HWUNIT_NUM)))))&(((uint32)1U)<<1))
#define IOHWAB_ADC_ACKNOWLEDGED(ADC_HWUNIT_NUM) \
do{(((*(volatile uint32*)(IOHWAB_ADDRESS_ADC_STATUS + (0x10000u*(ADC_HWUNIT_NUM)))))|=(((uint32)1U)<<1));}while(0)

#define IOHWAB_ADC_CONV_PROC(ADC_HWUNIT_NUM)  do{Adc_IrqTxRx(&Adc_DrvObj.hwUnitObj[ADC_HWUNIT_NUM]);}while(0)

#define IOHWAB_ADDRESS_GPIO0 0x00600000UL
#define IOHWAB_ADDRESS_GPIO1 0x00601000UL
#define IOHWAB_ADDRESS_GPIO2 0x00610000UL
#define IOHWAB_ADDRESS_GPIO3 0x00611000UL
#define IOHWAB_ADDRESS_GPIO4 0x00620000UL
#define IOHWAB_ADDRESS_GPIO5 0x00621000UL
#define IOHWAB_ADDRESS_GPIO6 0x00630000UL
#define IOHWAB_ADDRESS_GPIO7 0x00680000UL
#define IOHWAB_ADDRESS_WKUP_GPIO1 0x42100000UL
#define IOHWAB_ADDRESS_WKUP_GPIO0 0x42110000UL

#endif

/*******************************************************************************
**                      Upper limit ticks                                     **
*******************************************************************************/
#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
/* Upper limit of GPT time in sec */
#define IOHWAB_GPT_DELAY_MAX_SEC \
    ((IoHwAb_DelaySecType) IOHWAB_GPT_TICK_MAX / IOHWAB_GPT_FREQ_HZ)
#endif


/*******************************************************************************
**                      Convert STM ticks to time                             **
*******************************************************************************/
/* Convert STM ticks to time in sec */
#define IOHWAB_STM_TICK_TO_SEC(tick) \
    (((IoHwAb_DelaySecType) (tick)) / IOHWAB_STM_FREQ_HZ)

/* Convert STM ticks to time in msec */
#define IOHWAB_STM_TICK_TO_MSEC(tick) \
    ((IoHwAb_DelayMsecType) ((((IoHwAb_LongType)(tick))*IOHWAB_SEC_TO_MSEC) / IOHWAB_STM_FREQ_HZ))

/* Convert STM ticks to time in usec */
#define IOHWAB_STM_TICK_TO_USEC(tick) \
    ((IoHwAb_DelayUsecType) ((((uint32)(tick))*IOHWAB_SEC_TO_USEC) / IOHWAB_STM_FREQ_HZ))


/*******************************************************************************
**                      Convert time to STM ticks                             **
*******************************************************************************/
/* Convert Time in sec to STM ticks */
#define IOHWAB_SEC_TO_STM_TICK(time) \
    ((IoHwAb_StmTickType) ((time) * IOHWAB_STM_FREQ_HZ))

/* Convert Time in msec to STM ticks */
#define IOHWAB_MSEC_TO_STM_TICK(time) \
    ((IoHwAb_StmTickType) (((IoHwAb_LongType)(time) * IOHWAB_STM_FREQ_HZ) / IOHWAB_SEC_TO_MSEC))

/* Convert Time in usec to STM ticks */
#define IOHWAB_USEC_TO_STM_TICK(time) \
    ((IoHwAb_StmTickType) (((IoHwAb_LongType)(time) * IOHWAB_STM_FREQ_HZ) / IOHWAB_SEC_TO_USEC))


/*******************************************************************************
**                      Convert GPT ticks to time                             **
*******************************************************************************/
/* Convert GPT ticks to time in sec */
#define IOHWAB_GPT_TICK_TO_SEC(tick) \
    ((IoHwAb_DelaySecType) (tick) / IOHWAB_GPT_FREQ_HZ)

/* Convert GPT ticks to time in msec */
#define IOHWAB_GPT_TICK_TO_MSEC(tick) \
    ((IoHwAb_DelayMsecType) (((IoHwAb_LongType)(tick)*IOHWAB_SEC_TO_MSEC) / IOHWAB_GPT_FREQ_HZ))

/* Convert GPT ticks to time in usec */
#define IOHWAB_GPT_TICK_TO_USEC(tick) \
    ((IoHwAb_DelayUsecType) (((IoHwAb_LongType)(tick)*IOHWAB_SEC_TO_USEC) / IOHWAB_GPT_FREQ_HZ))


/*******************************************************************************
**                      Convert time to GPT ticks                             **
*******************************************************************************/
/* Convert Time in sec to GPT ticks */
#define IOHWAB_SEC_TO_GPT_TICK(time) \
    ((IoHwAb_GptTickType) ((time) * IOHWAB_GPT_FREQ_HZ))
    
/* Convert Time in msec to GPT ticks */
#define IOHWAB_MSEC_TO_GPT_TICK(time) \
    ((IoHwAb_GptTickType) (((IoHwAb_LongType)(time) * IOHWAB_GPT_FREQ_HZ) / IOHWAB_SEC_TO_MSEC))

/* Convert Time in usec to GPT ticks */
#define IOHWAB_USEC_TO_GPT_TICK(time) \
    ((IoHwAb_GptTickType) (((IoHwAb_LongType)(time) * IOHWAB_GPT_FREQ_HZ) / IOHWAB_SEC_TO_USEC))


/*******************************************************************************
**                      Convert between GPT ans STM ticks                     **
*******************************************************************************/
/* Convert STM ticks to GPT ticks */
#define IOHWAB_STM_TICK_TO_GPT_TICK(tick) \
    ((IoHwAb_GptTickType) (((IoHwAb_LongType)(tick) * IOHWAB_GPT_FREQ_HZ) / IOHWAB_STM_FREQ_HZ))

/* Convert GPT ticks to STM ticks */
#define IOHWAB_GPT_TICK_TO_STM_TICK(tick) \
    ((IoHwAb_StmTickType) (((IoHwAb_LongType)(tick) * IOHWAB_STM_FREQ_HZ) / IOHWAB_GPT_FREQ_HZ))


/*******************************************************************************
**                      Current STM Clock in ticks or time                    **
*******************************************************************************/
/* Current STM Clock in ticks */
#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#define IOHWAB_STM_BASE_ADDRESS         (0xFFF3C004UL)
#define IOHWAB_CURRENT_CLOCK_TICK()     ((IoHwAb_StmTickType)(REG_READ32((uint32)IOHWAB_STM_BASE_ADDRESS)))

#elif (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
    || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
    || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X) \
    || defined(IOHWAB_MCAL_INFINEON_TC38X) || defined(IOHWAB_MCAL_INFINEON_TC39X) )
#define IOHWAB_CURRENT_CLOCK_TICK()     ((IoHwAb_StmTickType) IOHWAB_GET_TIMESTAMP())

#elif (defined(IOHWAB_MCAL_FREESCALE_MPC574XR))
#define IOHWAB_CURRENT_CLOCK_TICK()     ((IoHwAb_StmTickType) STM_GET_COUNTER())

#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413))
#define IOHWAB_CURRENT_CLOCK_TICK()   ((IoHwAb_StmTickType)(*(volatile uint32*)(0xFFEC0004UL))) 

#elif (defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
#define IOHWAB_CURRENT_CLOCK_TICK()   ((IoHwAb_StmTickType)(*(volatile uint32*)(0xFFD70004UL))) 

#elif (defined(IOHWAB_MCAL_ST_SPC58XCX) || defined(IOHWAB_MCAL_ST_SPC58XHX))
  #if (REG_ESYS_STM_SW_MAJOR_VERSION > 1)
    #define IOHWAB_CURRENT_CLOCK_TICK()   STM_CNT(0xF4068000UL)
  #else
    #define IOHWAB_CURRENT_CLOCK_TICK()   STM_CNT(0)
  #endif

#elif (defined(IOHWAB_MCAL_CYPRESS_S6J32XX))
#define IOHWAB_CURRENT_CLOCK_TICK()   RLT32_TMR

#elif (defined(IOHWAB_MCAL_CYPRESS_S6J33XX))
#define IOHWAB_CURRENT_CLOCK_TICK()   RLT0_TMR

#endif

#ifndef IOHWAB_MCAL_NXP_S32K14X
/* Current STM Clock in sec */
#define IOHWAB_CURRENT_CLOCK_SEC()      (IOHWAB_STM_TICK_TO_SEC(IOHWAB_CURRENT_CLOCK_TICK()))

/* Current STM Clock in msec */
#define IOHWAB_CURRENT_CLOCK_MSEC()     (IOHWAB_STM_TICK_TO_MSEC(IOHWAB_CURRENT_CLOCK_TICK()))

/* Current STM Clock in usec */
#define IOHWAB_CURRENT_CLOCK_USEC()     (IOHWAB_STM_TICK_TO_USEC(IOHWAB_CURRENT_CLOCK_TICK()))
#endif
/*******************************************************************************
**                      DIO Util                                              **
*******************************************************************************/
#if (defined(IOHWAB_MCAL_FREESCALE_MPC560XB)||defined(IOHWAB_MCAL_ST_SPC58XCX) \
  || defined(IOHWAB_MCAL_ST_SPC58XHX))
#define IOHWAB_WRITE_CH(id, value)      do{REG_WRITE8(SIUL_GPDO((id)), (value));}while(0)

#elif (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
    || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
    || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X) \
    || defined(IOHWAB_MCAL_INFINEON_TC38X) || defined(IOHWAB_MCAL_INFINEON_TC39X) )

#define IOHWAB_WRITE_CH(id, value)      do{(id) = (value);}while(0) 

#elif (defined(IOHWAB_MCAL_FREESCALE_MPC574XR))
#define IOHWAB_WRITE_CH(id, value)      do{REG_WRITE8(SIUL2_GPDO_ADDR8((id)), (value));}while(0)

#endif
/* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> No Impact of this rule violation */
/* polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation */
#endif /* IOHWAB_UTIL_H */
/* polyspace-end MISRA-C3:2.3 [Justified:Low] "whether this macro is used depends on the configurations." */
/* polyspace-end MISRA-C3:2.5 [Justified:Low] "whether this macro is used depends on the configurations." */
/* polyspace-end MISRA-C3:20.9 [Justified:Unset] "Not a defect" */
/* polyspace-end MISRA-C3:10.7 [Justified:Low] "Validated by test cases. It works as intended." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
