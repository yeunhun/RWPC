/*-----------------------------------------------------------------------------
* Hyundai-AutoEver Cryptography Library
* Copyright (c) 2015-2016 Hyundai-AutoEver all rights reserved.
------------------------------------------------------------------------------*/
/**
* \file     Hmg_Common.h
* \date     Jan. 2016.
* \version  1.6.0
* \author   Hyundai_Autoever Automotive Security Techology Team
* \brief    AutoEver Cryptography Configuration
* \see
*/

/* DEFINE TO PREVENT RECURSIVE INCLUSION -------------------------------------*/
#ifndef HMG_COMMON_H_
#define HMG_COMMON_H_

#include "Hmg_Config.h"

/* EXPORTED DEFINE -----------------------------------------------------------*/
/* \brief Ver: Major 01 / Minor 00 / Path 01*/
#define HMGLIB_COMPANYID  0x41UL
#define HMGLIB_VER_MAJOR  0x01UL
#define HMGLIB_VER_MINOR  0x06UL
#define HMGLIB_VER_PATCH  0x01UL
#define HMGLIB_VER_  HMGLIB_VER_MAJOR##HMGLIB_VER_MINOR##HMGLIB_VER_PATCH


/** \brief retune & Error Type*/
/** no value */
#define HMG_VOID
/** BOOL value true. */
#define HMG_SUCCESS         (0U)
/** BOOL value False. */
#define HMG_FAILURE         (1U)
/** Error type invalid value  */
#define HMG_NO_FUNCTION     (2U)
/** Error type invalid value  */
#define HMG_INVALID_VALUE   (3U)
/** Error type invalid length  */
#define HMG_INVALID_LENGTH  (4U)
/** BOOL value working fuction. */
#define HMG_WORK_SLICING    (5U)


/** Boolean Value */
#ifndef TRUE
#define TRUE    (1U)
#endif
#ifndef FALSE
#define FALSE   (0U)
#endif
/** \brief Parameter Prefix Type*/
#ifndef HMG_IN
/** parameter Input */
#define HMG_IN const
#endif
#ifndef HMG_OUT
/** parameter Output */
#define HMG_OUT
#endif
#ifndef HMG_INOUT
/** parameter Inout */
#define HMG_INOUT
#endif


#ifdef Polyspace
#include <stddef.h>
#define HMG_NULL    NULL
#else
#define HMG_NULL    (void *)0
#endif


/* EXPORTED FUNCTIONS  -------------------------------------------------------*/
#ifdef  __cplusplus
extern "C" {
#endif

#if HMG_MEMORY_USE

    #   ifndef HMG_MEMCPY
    #   define HMG_MEMCPY(dst, src, len)        Hmg_Memcpy((dst), (src), (len))
    #   endif

    #   ifndef HMG_MEMSET
    #   define HMG_MEMSET(dst, val, len)        Hmg_Memset((dst), (val), (len))
    #   endif

    #   ifndef HMG_MEMCMP
    #   define HMG_MEMCMP(s1, s2, n)    Hmg_Memcmp((s1), (s2), (n))
    #   endif

#else
#include <memory.h>
    #   ifndef HMG_MEMCPY
    #   define HMG_MEMCPY(d, s, l)      memcpy((d), (s), (l))
    #   endif

    #   ifndef HMG_MEMSET
    #   define HMG_MEMSET(d, v, l)      memset((d), (v), (l))
    #   endif

    #   ifndef HMG_MEMCMP
    #   define HMG_MEMCMP(s1, s2, n)    memcmp((s1), (s2), (n))
    #   endif

#endif

#if HMG_MEMORY_USE
void Hmg_Memcpy(
    HMG_OUT uint8* dst,
    HMG_IN  uint8* src,
    HMG_IN  uint32 len
    );

void Hmg_Memset(
    HMG_OUT uint8* dst,
    HMG_IN  uint8  src,
    HMG_IN  uint32 len
    );

uint32 Hmg_Memcmp(
    HMG_IN uint8* dst,
    HMG_IN uint8* src,
    HMG_IN uint32 len
    );
#endif

    uint32 Hmg_GetVersionInfo();

#ifdef HMG_ENABLE_CALLBACK
    /**
    * type for Hmg callback function.
    */
    typedef void (*Hmg_CallbackFunc)(void);

    /**
    * set the Hmg callback function.
    */
    void Hmg_SetCallbackFunc(Hmg_CallbackFunc callbackFunc);

    /**
    * execute previously set Hmg callback function.
    */
    void Hmg_ExecCallback(void);
#endif

#ifdef  __cplusplus
}
#endif

#endif
