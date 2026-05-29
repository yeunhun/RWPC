/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_Version.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
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
** 1.15.0    09-Mar-2021   Yangjin        #28664                              **
** 1.14.0    19-Feb-2021   Yangjin        #28378                              **
** 1.13.0    20-Jan-2021   Yangjin        #27464                              **
** 1.12.0    31-Dec-2020   Yangjin        #27199                              **
** 1.11.0    24-Sep-2020   Yangjin        #25514, #25515                      **
** 1.10.1    04-Aug-2020   Yangjin        #24902                              **
** 1.10.0    26-Jun-2020   Yangjin        #24001, #24033, #24095, #24234      **
** 1.9.0     04-Jun-2020   Yangjin        #23413, #23685, #23696, #23742      **
** 1.8.1     08-May-2020   Yangjin        #23096                              **
** 1.8.0     21-Apr-2020   Yangjin        #22141, #22744, #22850              **
** 1.7.0     27-Nov-2019   Yangjin        #19730, #19828, #20354, #20381      **
** 1.6.0     14-Oct-2019   Yangjin        #19085, #19413, #19520, #19521      **
** 1.5.0     28-Aug-2019   Yangjin        #18753                              **
** 1.4.0     30-Jul-2019   Yangjin        #18083                              **
** 1.0.3     09-Aug-2018   Jongyoung      #13075                              **
** 1.0.2     25-Mar-2015   Jongyoung      1.Manage the single module version  **
** 1.0.1     21-Mar-2014   Sinil          Task ID : 853                       **
**                                        Update Port and Dio version check   **
** 1.0.0     07-Mar-2014   Sinil          Initial version                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Version.h"

#if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define IOHWAB_VERSION_C_AR_RELEASE_MAJOR_VERSION       4
#define IOHWAB_VERSION_C_AR_RELEASE_MINOR_VERSION       0
#define IOHWAB_VERSION_C_AR_RELEASE_REVISION_VERSION    3

/* FILE VERSION INFORMATION */
#define IOHWAB_VERSION_C_SW_MAJOR_VERSION               1
#define IOHWAB_VERSION_C_SW_MINOR_VERSION               15

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.9 [Justified:Low] "It works as intended. Not a defect." */

#if (IOHWAB_AR_RELEASE_MAJOR_VERSION != \
  IOHWAB_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "IoHwAb_Version.c : Mismatch in Specification Major Version"
#endif

#if (IOHWAB_AR_RELEASE_MINOR_VERSION != \
  IOHWAB_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "IoHwAb_Version.c : Mismatch in Specification Minor Version"
#endif

#if (IOHWAB_AR_RELEASE_REVISION_VERSION != \
  IOHWAB_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "IoHwAb_Version.c : Mismatch in Specification Patch Version"
#endif

#if (IOHWAB_SW_MAJOR_VERSION != IOHWAB_VERSION_C_SW_MAJOR_VERSION)
  #error "IoHwAb_Version.c : Mismatch in Major Version"
#endif

#if (IOHWAB_SW_MINOR_VERSION != IOHWAB_VERSION_C_SW_MINOR_VERSION)
  #error "IoHwAb_Version.c : Mismatch in Minor Version"
#endif

#if ((IOHWAB_USE_DIG_DIR == STD_ON) || (IOHWAB_USE_DIG_IN == STD_ON) \
  || (IOHWAB_USE_DIG_OUT == STD_ON))
#ifndef IOHWAB_MCAL_TI_TDA4X
#if (PORT_AR_RELEASE_MAJOR_VERSION != IOHWAB_PORT_AR_RELEASE_MAJOR_VERSION)
  #error "Port.h : Mismatch in Specification Major Version"
#endif

#if (PORT_AR_RELEASE_MINOR_VERSION != IOHWAB_PORT_AR_RELEASE_MINOR_VERSION)
#if (PORT_AR_RELEASE_MINOR_VERSION != IOHWAB_PORT_AR_RELEASE_MINOR_VERSION_R42)
#if (PORT_AR_RELEASE_MINOR_VERSION != IOHWAB_PORT_AR_RELEASE_MINOR_VERSION_R44)
  #error "Port.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif
#endif

#if (DIO_AR_RELEASE_MAJOR_VERSION != IOHWAB_DIO_AR_RELEASE_MAJOR_VERSION)
  #error "Dio.h : Mismatch in Specification Major Version"
#endif

#if (DIO_AR_RELEASE_MINOR_VERSION != IOHWAB_DIO_AR_RELEASE_MINOR_VERSION)
#if (DIO_AR_RELEASE_MINOR_VERSION != IOHWAB_DIO_AR_RELEASE_MINOR_VERSION_R42)
#if (DIO_AR_RELEASE_MINOR_VERSION != IOHWAB_DIO_AR_RELEASE_MINOR_VERSION_R44)
  #error "Dio.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif
#endif /* ((IOHWAB_USE_DIG_DIR == STD_ON) || (IOHWAB_USE_DIG_IN == STD_ON) \
  || (IOHWAB_USE_DIG_OUT == STD_ON)) */

#if ((IOHWAB_USE_ANA_IN_DIR == STD_ON) || (IOHWAB_USE_ANA_IN == STD_ON))
#if (ADC_AR_RELEASE_MAJOR_VERSION != IOHWAB_ADC_AR_RELEASE_MAJOR_VERSION)
  #error "Adc.h : Mismatch in Specification Major Version"
#endif

#if (ADC_AR_RELEASE_MINOR_VERSION != IOHWAB_ADC_AR_RELEASE_MINOR_VERSION)
#if (ADC_AR_RELEASE_MINOR_VERSION != IOHWAB_ADC_AR_RELEASE_MINOR_VERSION_R42)
#if (ADC_AR_RELEASE_MINOR_VERSION != IOHWAB_ADC_AR_RELEASE_MINOR_VERSION_R44)
  #error "Adc.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif
#endif /* ((IOHWAB_USE_ANA_IN_DIR == STD_ON) || (IOHWAB_USE_ANA_IN == STD_ON))*/

#if ((IOHWAB_USE_MC33972 == STD_ON) || (IOHWAB_USE_L9826 == STD_ON))
#if (SPI_AR_RELEASE_MAJOR_VERSION != IOHWAB_SPI_AR_RELEASE_MAJOR_VERSION)
  #error "Spi.h : Mismatch in Specification Major Version"
#endif

#if (SPI_AR_RELEASE_MINOR_VERSION != IOHWAB_SPI_AR_RELEASE_MINOR_VERSION)
#if (SPI_AR_RELEASE_MINOR_VERSION != IOHWAB_SPI_AR_RELEASE_MINOR_VERSION_R42)
#if (SPI_AR_RELEASE_MINOR_VERSION != IOHWAB_SPI_AR_RELEASE_MINOR_VERSION_R44)
  #error "Spi.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif
#endif /* ((IOHWAB_USE_MC33972 == STD_ON) || (IOHWAB_USE_L9826 == STD_ON))*/

#if ((IOHWAB_USE_ICU == STD_ON) || (IOHWAB_MC33972_EXTINT == STD_ON))
#if (ICU_AR_RELEASE_MAJOR_VERSION != IOHWAB_ICU_AR_RELEASE_MAJOR_VERSION)
  #error "Icu.h : Mismatch in Specification Major Version"
#endif

#if (ICU_AR_RELEASE_MINOR_VERSION != IOHWAB_ICU_AR_RELEASE_MINOR_VERSION)
#if (ICU_AR_RELEASE_MINOR_VERSION != IOHWAB_ICU_AR_RELEASE_MINOR_VERSION_R42)
#if (ICU_AR_RELEASE_MINOR_VERSION != IOHWAB_ICU_AR_RELEASE_MINOR_VERSION_R44)
  #error "Icu.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif
#endif /* ((IOHWAB_USE_ICU == STD_ON) || (IOHWAB_MC33972_EXTINT == STD_ON))*/

#if (IOHWAB_USE_GPT == STD_ON)
#if (GPT_AR_RELEASE_MAJOR_VERSION != IOHWAB_GPT_AR_RELEASE_MAJOR_VERSION)
  #error "Gpt.h : Mismatch in Specification Major Version"
#endif

#if (GPT_AR_RELEASE_MINOR_VERSION != IOHWAB_GPT_AR_RELEASE_MINOR_VERSION)
#if (GPT_AR_RELEASE_MINOR_VERSION != IOHWAB_GPT_AR_RELEASE_MINOR_VERSION_R42)
#if (GPT_AR_RELEASE_MINOR_VERSION != IOHWAB_GPT_AR_RELEASE_MINOR_VERSION_R44)
  #error "Gpt.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif
#endif /* (IOHWAB_USE_GPT == STD_ON) */

#if (IOHWAB_USE_PWM == STD_ON)
#if (PWM_AR_RELEASE_MAJOR_VERSION != IOHWAB_PWM_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm.h : Mismatch in Specification Major Version"
#endif

#if (PWM_AR_RELEASE_MINOR_VERSION != IOHWAB_PWM_AR_RELEASE_MINOR_VERSION)
#if (PWM_AR_RELEASE_MINOR_VERSION != IOHWAB_PWM_AR_RELEASE_MINOR_VERSION_R42)
#if (PWM_AR_RELEASE_MINOR_VERSION != IOHWAB_PWM_AR_RELEASE_MINOR_VERSION_R44)
  #error "Pwm.h : Mismatch in Specification Minor Version"
#endif
#endif
#endif
#endif /* (IOHWAB_USE_PWM == STD_ON) */
/* polyspace-end MISRA-C3:20.9 [Justified:Low] "It works as intended. Not a defect." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
