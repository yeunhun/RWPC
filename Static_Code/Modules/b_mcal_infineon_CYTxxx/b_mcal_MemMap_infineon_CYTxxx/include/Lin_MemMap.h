
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
   Justification: #undef to clear the macro definition of error detection. */
/* PRQA S 841 EOF */

/*------------------[Start of module LIN ]--------------------------------------*/

#ifdef LIN_START_SEC_CODE_ASIL_B
  #undef LIN_START_SEC_CODE_ASIL_B
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CODE_ASIL_B_STARTED
#endif

#ifdef LIN_STOP_SEC_CODE_ASIL_B
  #undef LIN_STOP_SEC_CODE_ASIL_B
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CODE_ASIL_B_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CODE_ASIL_B_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CALLOUT_CODE_ASIL_B
  #undef LIN_START_SEC_CALLOUT_CODE_ASIL_B
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CALLOUT_CODE_ASIL_B_STARTED
#endif

#ifdef LIN_STOP_SEC_CALLOUT_CODE_ASIL_B
  #undef LIN_STOP_SEC_CALLOUT_CODE_ASIL_B
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CALLOUT_CODE_ASIL_B_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CALLOUT_CODE_ASIL_B_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CODE_FAST_ASIL_B
  #undef LIN_START_SEC_CODE_FAST_ASIL_B
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CODE_FAST_ASIL_B_STARTED
#endif

#ifdef LIN_STOP_SEC_CODE_FAST_ASIL_B
  #undef LIN_STOP_SEC_CODE_FAST_ASIL_B
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CODE_FAST_ASIL_B_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CODE_FAST_ASIL_B_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CODE_SLOW_ASIL_B
  #undef LIN_START_SEC_CODE_SLOW_ASIL_B
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CODE_SLOW_ASIL_B_STARTED
#endif

#ifdef LIN_STOP_SEC_CODE_SLOW_ASIL_B
  #undef LIN_STOP_SEC_CODE_SLOW_ASIL_B
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CODE_SLOW_ASIL_B_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CODE_SLOW_ASIL_B_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONST_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_CONST_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONST_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_CONST_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONST_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONST_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONST_ASIL_B_8
  #undef LIN_START_SEC_CONST_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONST_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_CONST_ASIL_B_8
  #undef LIN_STOP_SEC_CONST_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONST_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONST_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONST_ASIL_B_16
  #undef LIN_START_SEC_CONST_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONST_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_CONST_ASIL_B_16
  #undef LIN_STOP_SEC_CONST_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONST_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONST_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONST_ASIL_B_32
  #undef LIN_START_SEC_CONST_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONST_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_CONST_ASIL_B_32
  #undef LIN_STOP_SEC_CONST_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONST_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONST_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONST_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONST_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONST_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #undef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #undef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #undef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONST_SAVED_RECOVERY_ZONE_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CALIB_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_CALIB_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CALIB_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_CALIB_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CALIB_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CALIB_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CALIB_ASIL_B_8
  #undef LIN_START_SEC_CALIB_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CALIB_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_CALIB_ASIL_B_8
  #undef LIN_STOP_SEC_CALIB_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CALIB_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CALIB_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CALIB_ASIL_B_16
  #undef LIN_START_SEC_CALIB_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CALIB_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_CALIB_ASIL_B_16
  #undef LIN_STOP_SEC_CALIB_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CALIB_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CALIB_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CALIB_ASIL_B_32
  #undef LIN_START_SEC_CALIB_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CALIB_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_CALIB_ASIL_B_32
  #undef LIN_STOP_SEC_CALIB_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CALIB_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CALIB_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_CALIB_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CALIB_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_CALIB_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CALIB_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CALIB_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONFIG_DATA_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_ASIL_B_8
  #undef LIN_START_SEC_CONFIG_DATA_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONFIG_DATA_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #undef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONFIG_DATA_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONFIG_DATA_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_ASIL_B_16
  #undef LIN_START_SEC_CONFIG_DATA_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONFIG_DATA_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #undef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONFIG_DATA_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONFIG_DATA_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_ASIL_B_32
  #undef LIN_START_SEC_CONFIG_DATA_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONFIG_DATA_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #undef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONFIG_DATA_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONFIG_DATA_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_NO_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_ASIL_B_8
  #undef LIN_START_SEC_VAR_NO_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_NO_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_NO_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_NO_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_ASIL_B_16
  #undef LIN_START_SEC_VAR_NO_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_NO_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_NO_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_NO_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_ASIL_B_32
  #undef LIN_START_SEC_VAR_NO_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_NO_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_NO_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_NO_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_CLEARED_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_CLEARED_ASIL_B_8
  #undef LIN_START_SEC_VAR_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_CLEARED_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_CLEARED_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_CLEARED_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_CLEARED_ASIL_B_16
  #undef LIN_START_SEC_VAR_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_CLEARED_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_CLEARED_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_CLEARED_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_CLEARED_ASIL_B_32
  #undef LIN_START_SEC_VAR_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_CLEARED_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_CLEARED_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_CLEARED_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_CLEARED_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_INIT_ASIL_B_8
  #undef LIN_START_SEC_VAR_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_INIT_ASIL_B_16
  #undef LIN_START_SEC_VAR_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_INIT_ASIL_B_32
  #undef LIN_START_SEC_VAR_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_CLEARED_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_FAST_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_CLEARED_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SLOW_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_NO_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #undef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #undef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #undef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_CLEARED_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #undef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #undef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #undef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #undef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #undef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #undef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_INTERNAL_VAR_POWER_ON_INIT_ASIL_B_UNSPECIFIED_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #undef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_BOOLEAN_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_8_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #undef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_8
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_8_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_8_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_16_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #undef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_16
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_16_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_16_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_32_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #undef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_32
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_32_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_32_STARTED
  #endif
#endif

#ifdef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifdef MEMMAP_STARTED
    #error "MemMap error: Section started without stopping of previous section."
  #else
    #define MEMMAP_STARTED
  #endif
  #define LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED_STARTED
#endif

#ifdef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #undef LIN_STOP_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED
  #ifndef MEMMAP_ERROR
    #error "MemMap error: Multiple sections selected."
  #endif
  #undef MEMMAP_ERROR
  #ifndef MEMMAP_STARTED
    #error "MemMap error: Section must be started before stopping."
  #else
    #undef MEMMAP_STARTED
  #endif
  #ifndef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED_STARTED
    #error "MemMap error: Stop section does not match start section."
  #else
    #undef LIN_START_SEC_VAR_SAVED_ZONE_ASIL_B_UNSPECIFIED_STARTED
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
