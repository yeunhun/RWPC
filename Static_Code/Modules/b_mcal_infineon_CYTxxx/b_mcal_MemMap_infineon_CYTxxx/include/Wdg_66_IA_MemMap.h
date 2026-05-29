
/******************************************************************************
* \brief AUTOSAR Memory Mapping Header
* 
* This file is the sample file for the Autosar memory mapping.
* This file contains the template implementation of the Autosar memory mapping.
* See document "Specification of Memory Mapping"
*
* \version 1.0.0
*
* Product: SW-MCAL42-DRV
******************************************************************************/
/*****************************************************************************/
/* __DISCLAIMER_START__                                                      */
/******************************************************************************
* (c) 2017-2020, Cypress Semiconductor Corporation
* or a subsidiary of Cypress Semiconductor Corporation. All rights
* reserved.
*
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation or one of its subsidiaries ("Cypress") and is protected by
* and subject to worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
******************************************************************************/
/* __DISCLAIMER_END__                                                        */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[MemMap error checking]----------------------------------*/

/* Deviation from MISRA-C:2004 rule 19.15, MISRA-C:2012 Dir-4.10
   Justification: AUTOSAR specification to be included more than once in a single compilation unit. */
/* PRQA S 883 1 */
#if (defined MEMMAP_ERROR) /* to prevent double definition */
#error MEMMAP_ERROR defined, wrong MemMap.h usage
#endif /* if (defined MEMMAP_ERROR) */

/** \brief Checks if this file has been correctly used
 **
 ** This definition checks if this file has been correctly included
 ** the last time.
 ** We do it here, before the big if-elif. */
#define MEMMAP_ERROR

/* Deviation from MISRA-C:2004 rule 19.6, MISRA-C:2012 Rule-20.5
   Justification: This implementation is specified by AUTOSAR specification. */
/* PRQA S 841 EOF */

/*------------------[Start of module WDG ]--------------------------------------*/

#ifdef WDG_66_IA_START_SEC_CODE
  #undef WDG_66_IA_START_SEC_CODE
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CODE_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CODE
  #undef WDG_66_IA_STOP_SEC_CODE
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CODE_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CODE_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CALLOUT_CODE
  #undef WDG_66_IA_START_SEC_CALLOUT_CODE
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CALLOUT_CODE_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CALLOUT_CODE
  #undef WDG_66_IA_STOP_SEC_CALLOUT_CODE
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CALLOUT_CODE_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CALLOUT_CODE_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CODE_FAST
  #undef WDG_66_IA_START_SEC_CODE_FAST
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CODE_FAST_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CODE_FAST
  #undef WDG_66_IA_STOP_SEC_CODE_FAST
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CODE_FAST_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CODE_FAST_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CODE_SLOW
  #undef WDG_66_IA_START_SEC_CODE_SLOW
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CODE_SLOW_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CODE_SLOW
  #undef WDG_66_IA_STOP_SEC_CODE_SLOW
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CODE_SLOW_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CODE_SLOW_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONST_BOOLEAN
  #undef WDG_66_IA_START_SEC_CONST_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONST_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_CONST_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONST_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONST_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONST_8
  #undef WDG_66_IA_START_SEC_CONST_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONST_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_8
  #undef WDG_66_IA_STOP_SEC_CONST_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONST_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONST_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONST_16
  #undef WDG_66_IA_START_SEC_CONST_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONST_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_16
  #undef WDG_66_IA_STOP_SEC_CONST_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONST_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONST_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONST_32
  #undef WDG_66_IA_START_SEC_CONST_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONST_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_32
  #undef WDG_66_IA_STOP_SEC_CONST_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONST_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONST_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONST_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_CONST_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONST_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_CONST_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONST_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONST_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #undef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #undef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #undef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #undef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #undef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #undef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #undef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CALIB_BOOLEAN
  #undef WDG_66_IA_START_SEC_CALIB_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CALIB_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CALIB_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_CALIB_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CALIB_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CALIB_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CALIB_8
  #undef WDG_66_IA_START_SEC_CALIB_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CALIB_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CALIB_8
  #undef WDG_66_IA_STOP_SEC_CALIB_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CALIB_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CALIB_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CALIB_16
  #undef WDG_66_IA_START_SEC_CALIB_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CALIB_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CALIB_16
  #undef WDG_66_IA_STOP_SEC_CALIB_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CALIB_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CALIB_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CALIB_32
  #undef WDG_66_IA_START_SEC_CALIB_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CALIB_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CALIB_32
  #undef WDG_66_IA_STOP_SEC_CALIB_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CALIB_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CALIB_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CALIB_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_CALIB_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CALIB_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CALIB_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_CALIB_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CALIB_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CALIB_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONFIG_DATA_BOOLEAN
  #undef WDG_66_IA_START_SEC_CONFIG_DATA_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONFIG_DATA_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONFIG_DATA_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_CONFIG_DATA_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONFIG_DATA_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONFIG_DATA_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONFIG_DATA_8
  #undef WDG_66_IA_START_SEC_CONFIG_DATA_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONFIG_DATA_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONFIG_DATA_8
  #undef WDG_66_IA_STOP_SEC_CONFIG_DATA_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONFIG_DATA_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONFIG_DATA_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONFIG_DATA_16
  #undef WDG_66_IA_START_SEC_CONFIG_DATA_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONFIG_DATA_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONFIG_DATA_16
  #undef WDG_66_IA_STOP_SEC_CONFIG_DATA_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONFIG_DATA_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONFIG_DATA_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONFIG_DATA_32
  #undef WDG_66_IA_START_SEC_CONFIG_DATA_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONFIG_DATA_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONFIG_DATA_32
  #undef WDG_66_IA_STOP_SEC_CONFIG_DATA_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONFIG_DATA_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONFIG_DATA_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_CONFIG_DATA_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_CONFIG_DATA_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_CONFIG_DATA_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_CONFIG_DATA_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_CONFIG_DATA_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_NO_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_NO_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_NO_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_NO_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_8
  #undef WDG_66_IA_START_SEC_VAR_NO_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_NO_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_8
  #undef WDG_66_IA_STOP_SEC_VAR_NO_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_NO_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_NO_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_16
  #undef WDG_66_IA_START_SEC_VAR_NO_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_NO_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_16
  #undef WDG_66_IA_STOP_SEC_VAR_NO_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_NO_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_NO_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_32
  #undef WDG_66_IA_START_SEC_VAR_NO_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_NO_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_32
  #undef WDG_66_IA_STOP_SEC_VAR_NO_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_NO_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_NO_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_NO_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_NO_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_NO_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_NO_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_CLEARED_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_CLEARED_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_CLEARED_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_CLEARED_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_CLEARED_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_CLEARED_8
  #undef WDG_66_IA_START_SEC_VAR_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_CLEARED_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_CLEARED_8
  #undef WDG_66_IA_STOP_SEC_VAR_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_CLEARED_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_CLEARED_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_CLEARED_16
  #undef WDG_66_IA_START_SEC_VAR_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_CLEARED_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_CLEARED_16
  #undef WDG_66_IA_STOP_SEC_VAR_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_CLEARED_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_CLEARED_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_CLEARED_32
  #undef WDG_66_IA_START_SEC_VAR_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_CLEARED_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_CLEARED_32
  #undef WDG_66_IA_STOP_SEC_VAR_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_CLEARED_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_CLEARED_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_CLEARED_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_CLEARED_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_CLEARED_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_8
  #undef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_8
  #undef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_16
  #undef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_16
  #undef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_32
  #undef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_32
  #undef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_8
  #undef WDG_66_IA_START_SEC_VAR_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_8
  #undef WDG_66_IA_STOP_SEC_VAR_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_16
  #undef WDG_66_IA_START_SEC_VAR_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_16
  #undef WDG_66_IA_STOP_SEC_VAR_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_32
  #undef WDG_66_IA_START_SEC_VAR_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_32
  #undef WDG_66_IA_STOP_SEC_VAR_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_8
  #undef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_8
  #undef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_16
  #undef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_16
  #undef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_32
  #undef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_32
  #undef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_8
  #undef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_8
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_16
  #undef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_16
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_32
  #undef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_32
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_CLEARED_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_8
  #undef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_CLEARED_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_8
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_16
  #undef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_CLEARED_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_16
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_32
  #undef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_CLEARED_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_32
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_FAST_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_INIT_8
  #undef WDG_66_IA_START_SEC_VAR_FAST_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_8
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_INIT_16
  #undef WDG_66_IA_START_SEC_VAR_FAST_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_16
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_INIT_32
  #undef WDG_66_IA_START_SEC_VAR_FAST_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_32
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_FAST_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_8
  #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_8
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_16
  #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_16
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_32
  #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_32
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_8
  #undef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_8
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_16
  #undef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_16
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_32
  #undef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_32
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_8
  #undef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_8
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_16
  #undef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_16
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_32
  #undef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_32
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_CLEARED_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_SLOW_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_INIT_8
  #undef WDG_66_IA_START_SEC_VAR_SLOW_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_8
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_INIT_16
  #undef WDG_66_IA_START_SEC_VAR_SLOW_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_16
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_INIT_32
  #undef WDG_66_IA_START_SEC_VAR_SLOW_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_32
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_8
  #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_8
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_16
  #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_16
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_32
  #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_32
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_8
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_8
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_16
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_16
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_32
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_32
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_8
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_8
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_16
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_16
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_32
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_32
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_8
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_8
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_16
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_16
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_32
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_32
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_BOOLEAN
  #undef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SAVED_ZONE_BOOLEAN_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_BOOLEAN
  #undef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_BOOLEAN_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_8
  #undef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SAVED_ZONE_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_8
  #undef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_16
  #undef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SAVED_ZONE_16_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_16
  #undef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_16_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_32
  #undef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SAVED_ZONE_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_32
  #undef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE0_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE0_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE1_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE1_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE0_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE0_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE0_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_LOCAL_CORE0_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_INIT_LOCAL_CORE0_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE0_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE0_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE0_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_OR_GLOBAL_CORE1_UNSPECIFIED_STARTED
  #endif
#endif


#ifdef WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE1_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE1_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE1_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_LOCAL_CORE1_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_INIT_LOCAL_CORE1_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE1_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_INIT_LOCAL_CORE1_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_8
  #undef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE0_8
  #undef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE0_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_8
  #undef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_8_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE1_8
  #undef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE1_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_8_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_32
  #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE0_32
  #undef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE0_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE0_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_32
  #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_32_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE1_32
  #undef WDG_66_IA_STOP_SEC_VAR_NO_INIT_LOCAL_CORE1_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_NO_INIT_LOCAL_CORE1_32_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE0_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE0_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE0_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_UNSPECIFIED
  #undef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_UNSPECIFIED_STARTED
#endif

#ifdef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE1_UNSPECIFIED
  #undef WDG_66_IA_STOP_SEC_VAR_INIT_GLOBAL_CORE1_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef WDG_66_IA_START_SEC_VAR_INIT_GLOBAL_CORE1_UNSPECIFIED_STARTED
  #endif
#endif

/*------------------[MemMap error checking]----------------------------------*/

#if (defined MEMMAP_ERROR) /* to prevent double definition */
#error MEMMAP_ERROR defined, wrong MemMap.h usage
#endif /* if (defined MEMMAP_ERROR) */

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
