/* polyspace-begin MISRA-C3:D4.10 [Not a defect:Medium] "No Impact of this rule violation (AUTOSAR Standard : Memory Mapping)" */
/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Mcal_MemMap.h                                                 **
**                                                                            **
**  TARGET    : Traveo-II using GHS complier                                  **
**                                                                            **
**  PRODUCT   :                                                               **
**                                                                            **
**  PURPOSE   : Provision for sections for memory mapping.                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0     22-10-2021     SH.Park       Initial version                     **
*******************************************************************************/

/* polyspace-begin MISRA-C3:20.1 [Jestified:Low] "Disapplied" */
/* polyspace-begin MISRA-C3:20.5 [Not a defect:Low] "This violation is not impact." */

/*******************************************************************************
**                      Module section mapping                                **
*******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

#define MCAL_SECTION_NOT_FOUND

#ifdef ADC_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE2_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE3_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE4_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE5_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE6_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef ADC_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE7_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Adc_MemMap.h"
#endif

#ifdef CAN_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Can_MemMap.h"
#endif

#ifdef DIO_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef DIO_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Dio_MemMap.h"
#endif

#ifdef FEE_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fee_MemMap.h"
#endif

#ifdef FLS_START_SEC_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CALLOUT_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CALLOUT_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CODE_FAST
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CODE_FAST
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CODE_SLOW
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CODE_SLOW
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONST_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONST_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONST_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONST_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONST_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONST_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONST_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONST_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONST_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONST_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CALIB_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CALIB_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CALIB_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CALIB_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CALIB_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CALIB_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CALIB_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CALIB_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CALIB_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CALIB_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONFIG_DATA_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONFIG_DATA_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONFIG_DATA_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONFIG_DATA_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONFIG_DATA_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONFIG_DATA_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONFIG_DATA_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONFIG_DATA_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SAVED_ZONE_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SAVED_ZONE_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SAVED_ZONE_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SAVED_ZONE_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SAVED_ZONE_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SAVED_ZONE_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SAVED_ZONE_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SAVED_ZONE_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_START_SEC_SYSCALLSHARED_VAR_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef FLS_STOP_SEC_SYSCALLSHARED_VAR_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Fls_MemMap.h"
#endif

#ifdef GPT_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Gpt_MemMap.h"
#endif

#ifdef ICU_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_DMA_WRITEBUFF_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_DMA_WRITEBUFF_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_DMA_WRITEBUFF_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_DMA_WRITEBUFF_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_DMA_READBUFF_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_DMA_READBUFF_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_STOP_SEC_VAR_NO_INIT_ASIL_B_DMA_READBUFF_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef ICU_START_SEC_VAR_NO_INIT_ASIL_B_DMA_READBUFF_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Icu_MemMap.h"
#endif

#ifdef LIN_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Lin_MemMap.h"
#endif

#ifdef MCU_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_START_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef MCU_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Mcu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef OCU_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Ocu_MemMap.h"
#endif

#ifdef PORT_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PORT_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Port_MemMap.h"
#endif

#ifdef PWM_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef PWM_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Pwm_MemMap.h"
#endif

#ifdef SPI_START_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CODE_FAST_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CODE_SLOW_ASIL_B
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONST_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONST_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONST_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CALIB_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CALIB_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CALIB_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_DMA_WRITEBUFF_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_DMA_WRITEBUFF_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_DMA_WRITEBUFF_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_DMA_WRITEBUFF_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_DMA_READBUFF_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_DMA_READBUFF_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_DMA_READBUFF_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_DMA_READBUFF_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_START_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_VAR_NO_INIT_ASIL_B_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Spi_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CALLOUT_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CALLOUT_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CODE_FAST
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CODE_FAST
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CODE_SLOW
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CODE_SLOW
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONST_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONST_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONST_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONST_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONST_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CALIB_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CALIB_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CALIB_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CALIB_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CALIB_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CALIB_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CALIB_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CALIB_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CALIB_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CALIB_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONFIG_DATA_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONFIG_DATA_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONFIG_DATA_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONFIG_DATA_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONFIG_DATA_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONFIG_DATA_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONFIG_DATA_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONFIG_DATA_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_BOOLEAN
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_16
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_LOCAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_LOCAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE0_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE1_8
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE0_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE1_32
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE0_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE1_UNSPECIFIED
  #undef MCAL_SECTION_NOT_FOUND
  #include "Wdg_66_IA_MemMap.h"
#endif

/* For mobilgene */
#ifdef CAN_START_SEC_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #undef CAN_START_SEC_CODE
  #define CAN_START_SEC_CODE_ASIL_B
  #include "Can_MemMap.h"
#endif

#ifdef CAN_STOP_SEC_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #undef CAN_STOP_SEC_CODE
  #define CAN_STOP_SEC_CODE_ASIL_B
  #include "Can_MemMap.h"
#endif

#ifdef FEE_START_SEC_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #undef FEE_START_SEC_CODE
  #define FEE_START_SEC_CODE_ASIL_B
  #include "Fee_MemMap.h"
#endif

#ifdef FEE_STOP_SEC_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #undef FEE_STOP_SEC_CODE
  #define FEE_STOP_SEC_CODE_ASIL_B
  #include "Fee_MemMap.h"
#endif

#ifdef SPI_START_SEC_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #undef SPI_START_SEC_CODE
  #define SPI_START_SEC_CODE_ASIL_B
  #include "Spi_MemMap.h"
#endif

#ifdef SPI_STOP_SEC_CODE
  #undef MCAL_SECTION_NOT_FOUND
  #undef SPI_STOP_SEC_CODE
  #define SPI_STOP_SEC_CODE_ASIL_B
  #include "Spi_MemMap.h"
#endif

#ifdef MCAL_SECTION_NOT_FOUND
  #undef MCAL_SECTION_NOT_FOUND
  #define SECTION_NOT_FOUND
#endif

#ifdef __cplusplus
}
#endif

/* polyspace-end MISRA-C3:20.1 */
/* polyspace-end MISRA-C3:20.5 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

