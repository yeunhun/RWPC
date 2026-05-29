/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: IoHwAb_Version.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : C header for IoHwAb_Version                                   **
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
** 1.13.1    27-Jan-2021   Yangjin        #27951                              **
** 1.13.0    20-Jan-2021   Yangjin        #27464                              **
** 1.12.0    31-Dec-2020   Yangjin        #27199                              **
** 1.11.0    24-Sep-2020   Yangjin        #25514, #25515                      **
** 1.10.2    13-Aug-2020   Yangjin        #25147                              **
** 1.10.1    04-Aug-2020   Yangjin        #24902                              **
** 1.10.0    26-Jun-2020   Yangjin        #24001, #24033, #24095, #24234      **
** 1.9.0     04-Jun-2020   Yangjin        #23413, #23685, #23696, #23742      **
** 1.8.1     08-May-2020   Yangjin        #23096                              **
** 1.8.0     21-Apr-2020   Yangjin        #22141, #22744, #22850              **
** 1.7.1     26-Feb-2020   Yangjin        #21555, #21627, #21781              **
** 1.7.0     27-Nov-2019   Yangjin        #19730, #19828, #20354, #20381      **
** 1.6.0     14-Oct-2019   Yangjin        #19085, #19413, #19520, #19521      **
** 1.4.0     30-Jul-2019   Yangjin        #18083                              **
** 1.3.1     30-Apr-2019   Yangjin        #16954                              **
** 1.0.4     09-Aug-2018   Jongyoung      #13075                              **
** 1.0.3     05-Dec-2016   Jongyoung      #6845                               **
*******************************************************************************/

#ifndef IOHWAB_VERSION_H
#define IOHWAB_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Cfg.h"

#if (defined(IOHWAB_MCAL_CYPRESS_S6J32XX) || defined(IOHWAB_MCAL_CYPRESS_S6J33XX ))
#include "Dio_Version.h"
#include "Port_Version.h"
#include "Icu_Version.h"
#include "Gpt_Version.h"
#include "Pwm_Version.h"
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Justified:Low] "whether this macro is used depends on the configurations." */
/* AUTOSAR Specification Version Information */
#define IOHWAB_VERSION_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_VERSION_AR_RELEASE_MINOR_VERSION     0u
#define IOHWAB_VERSION_AR_RELEASE_REVISION_VERSION  3u

/* Software Version Information */
#define IOHWAB_VERSION_SW_MAJOR_VERSION             1u
#define IOHWAB_VERSION_SW_MINOR_VERSION             15u
#define IOHWAB_VERSION_SW_PATCH_VERSION             0u

/* Included Files AUTOSAR Specification Version */
#define IOHWAB_ADC_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ADC_AR_RELEASE_MINOR_VERSION     0u
#define IOHWAB_ADC_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_ADC_AR_RELEASE_MINOR_VERSION_R44 4u

#define IOHWAB_SPI_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_SPI_AR_RELEASE_MINOR_VERSION     0u
#define IOHWAB_SPI_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_SPI_AR_RELEASE_MINOR_VERSION_R44 4u

#define IOHWAB_DIO_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION     0u
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION_R44 4u

#define IOHWAB_PWM_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_PWM_AR_RELEASE_MINOR_VERSION     0u
#define IOHWAB_PWM_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_PWM_AR_RELEASE_MINOR_VERSION_R44 4u

#define IOHWAB_PORT_AR_RELEASE_MAJOR_VERSION    4u
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION    0u
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION_R44 4u

#define IOHWAB_ICU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ICU_AR_RELEASE_MINOR_VERSION     0u
#define IOHWAB_ICU_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_ICU_AR_RELEASE_MINOR_VERSION_R44 4u

#define IOHWAB_GPT_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION     0u
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION_R44 4u

/* polyspace-end MISRA-C3:2.5 [Justified:Low] "whether this macro is used depends on the configurations." */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* IOHWAB_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
