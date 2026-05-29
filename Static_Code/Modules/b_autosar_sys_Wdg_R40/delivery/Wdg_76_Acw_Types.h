/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Wdg_76_Acw_Types.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTRON CUSTOM WDG                                     **
**                                                                            **
**  PURPOSE   : Header file to publish Autron Custom Watchdog types           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.8.2.0   18-Oct-2021   YH.Han       Redmine #32698                        **
** 1.1.0     17-Jul-2017   Kuksun       Redmine #8886                         **
** 1.0.2     19-Dec-2016   Kuksun       Redmine #6708                         **
** 1.0.1     28-Apr-2016   Sinil        Redmine #4744                         **
** 1.0.0     21-Apr-2016   Sinil        Initial version                       **
*******************************************************************************/

#ifndef WDG_76_ACW_TYPES_H
#define WDG_76_ACW_TYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw_Cfg.h"
#if (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
#include "Spi.h"
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON) */

/*******************************************************************************
**                      MACRO Definitions                                     **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Not a Defect] 
                              "macro is used according to user configuration" */
/* ARISUCAN SBC SPI REGISTER */
#define WDG_76_ACW_ARISUCAN_WD_CTRL_REG_W             ((uint16)0x0083)
#define WDG_76_ACW_ARISUCAN_WD_CTRL_REG_R             ((uint16)0x0003)

/* WD_CTRL */
/* Registor bit
  CHECKSUM    :7 - Watchdog Setting Check Sum Bit
  WD_STM_EN_0 :6 - Watchdog Deactivation during Stop Mode, bit 0
  WD_WIN      :5 - Watchdog Type Selection
  WD_EN_WK_BUS:4 - Watchdog Enable after Bus (CANx) Wake in SBC Stop Mode
  MAX_3_RST   :3 - Limit number of resets due to a Watchdog failure
  WD_TIMER_2  :2 - Watchdog Timer Period
  WD_TIMER_1  :1 - Watchdog Timer Period
  WD_TIMER_0  :0 - Watchdog Timer Period
*/
#define WDG_76_ACW_ARISUCAN_WD_CTRL_CHECKSUM_BIT      ((uint16)0x0001 << 15)
#define WDG_76_ACW_ARISUCAN_WD_CTRL_WD_STM_EN_0_BIT   ((uint16)0x0001 << 14)
#define WDG_76_ACW_ARISUCAN_WD_CTRL_WD_WIN_BIT        ((uint16)0x0001 << 13)
#define WDG_76_ACW_ARISUCAN_WD_CTRL_WD_EN_WK_BUS_BIT  ((uint16)0x0001 << 12)
#define WDG_76_ACW_ARISUCAN_WD_CTRL_MAX_3_RST_BIT     ((uint16)0x0001 << 11)
#define WDG_76_ACW_ARISUCAN_WD_CTRL_WD_TIMER_2_BIT    ((uint16)0x0001 << 10)
#define WDG_76_ACW_ARISUCAN_WD_CTRL_WD_TIMER_1_BIT    ((uint16)0x0001 << 9)
#define WDG_76_ACW_ARISUCAN_WD_CTRL_WD_TIMER_0_BIT    ((uint16)0x0001 << 8)

/* Macros for numerical Values */
#define WDG_76_ZERO                                   ((uint8)0x00)
#define WDG_76_ONE                                    ((uint8)0x01)
#define WDG_76_TWO                                    ((uint8)0x02)
#define WDG_76_THREE                                  ((uint8)0x03)
#define WDG_76_FOUR                                   ((uint8)0x04)
/* polyspace-end<MISRA-C3:2.5 */

/*******************************************************************************
**                      Global Enumerations                                   **
*******************************************************************************/
typedef enum 
{
  WDG_76_ACW_UNINIT = 0x00,
  WDG_76_ACW_IDLE,
  WDG_76_ACW_BUSY,
  WDG_76_ACW_EXPIRED
} Wdg_76_Acw_StatusType;

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.8 [Not a Defect] 
                                             "struct is visible to help user" */
typedef struct 
{
  uint32 ulSlowPeriodMs;
  Gpt_ValueType ddSlowPeriodTick;
  uint32 ulFastPeriodMs;
  Gpt_ValueType ddFastPeriodTick;
  #if (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON)
  uint32 ulSlowDutyUs;
  Gpt_ValueType ddSlowDutyTick;
  uint32 ulFastDutyUs;
  Gpt_ValueType ddFastDutyTick;
  #endif /* (WDG_76_ACW_EXTERNAL_MODULE_DIO == STD_ON) */
  #if (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON)
  uint32 ulInitialPeriodMS;
  Gpt_ValueType ddInitialPeriodTick;
  uint32 ulSlowDutyUs;
  Gpt_ValueType ddSlowDutyTick;
  uint32 ulFastDutyUs;
  Gpt_ValueType ddFastDutyTick;
  #endif /* (WDG_76_ACW_EXTERNAL_MODULE_MPQ6411 == STD_ON) */  
} Wdg_76_Acw_ConfigType;
/* polyspace-end MISRA-C3:D4.8 */

#if (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON)
typedef struct 
{
  uint16 TriggerData;  
} Wdg_76_Acw_ArisuCanConfigType;
#endif /* (WDG_76_ACW_EXTERNAL_MODULE_ARISUCAN == STD_ON) */

#endif /* WDG_76_ACW_TYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
