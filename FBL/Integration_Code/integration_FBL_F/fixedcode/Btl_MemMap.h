/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Btl_MemMap.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Provides all the memory abstractions used                     **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#if defined (START_BTL_MEMMAP)
/*******************************************************************************
**                Named memory segment for global variables                   **
*******************************************************************************/
#elif defined (BTL_START_SEC_VAR_NO_INIT)
  #undef BTL_START_SEC_VAR_NO_INIT
  #ifdef __TASKING__
    #pragma section farbss="BTL_U_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section bss=".BTL_U_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_VAR_NO_INIT)
  #undef BTL_STOP_SEC_VAR_NO_INIT
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef BTL_START_SEC_VAR_NO_INIT_BOOLEAN
  #ifdef __TASKING__
    #pragma section farbss="BTL_U_DATA"
    #pragma align 1
  #elif defined __GHS__
    #pragma ghs section bss=".BTL_U_DATA"
    #pragma alignvar (1)
  #endif
#elif defined (BTL_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef BTL_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_NO_INIT_8)
  #undef BTL_START_SEC_VAR_NO_INIT_8
  #ifdef __TASKING__
    #pragma section farbss="BTL_U_DATA"
    #pragma align 1
  #elif defined __GHS__
    #pragma ghs section bss=".BTL_U_DATA"
    #pragma alignvar (1)
  #endif
#elif defined (BTL_STOP_SEC_VAR_NO_INIT_8)
  #undef BTL_STOP_SEC_VAR_NO_INIT_8
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_NO_INIT_16)
  #undef BTL_START_SEC_VAR_NO_INIT_16
  #ifdef __TASKING__
    #pragma section farbss="BTL_U_DATA"
    #pragma align 2
  #elif defined __GHS__
    #pragma ghs section bss=".BTL_U_DATA"
    #pragma alignvar (2)
  #endif
#elif defined (BTL_STOP_SEC_VAR_NO_INIT_16)
  #undef BTL_STOP_SEC_VAR_NO_INIT_16
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_NO_INIT_32)
  #undef BTL_START_SEC_VAR_NO_INIT_32
  #ifdef __TASKING__
    #pragma section farbss="BTL_U_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section bss=".BTL_U_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_VAR_NO_INIT_32)
  #undef BTL_STOP_SEC_VAR_NO_INIT_32
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef BTL_START_SEC_VAR_NO_INIT_UNSPECIFIED
  #ifdef __TASKING__
    #pragma section farbss="BTL_U_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section bss=".BTL_U_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef BTL_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_CLEARED)
  #undef BTL_START_SEC_VAR_CLEARED
  #ifdef __TASKING__
    #pragma section farbss=".bss.BTL_U_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section bss=".bss.BTL_U_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_VAR_CLEARED)
  #undef BTL_STOP_SEC_VAR_CLEARED
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef BTL_START_SEC_VAR_CLEARED_BOOLEAN
  #ifdef __TASKING__
    #pragma section farbss=".bss.BTL_U_DATA"
    #pragma align 1
  #elif defined __GHS__
    #pragma ghs section bss=".bss.BTL_U_DATA"
    #pragma alignvar (1)
  #endif
#elif defined (BTL_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef BTL_STOP_SEC_VAR_CLEARED_BOOLEAN
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_CLEARED_8)
  #undef BTL_START_SEC_VAR_CLEARED_8
  #ifdef __TASKING__
    #pragma section farbss=".bss.BTL_U_DATA"
    #pragma align 1
  #elif defined __GHS__
    #pragma ghs section bss=".bss.BTL_U_DATA"
    #pragma alignvar (1)
  #endif
#elif defined (BTL_STOP_SEC_VAR_CLEARED_8)
  #undef BTL_STOP_SEC_VAR_CLEARED_8
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_CLEARED_16)
  #undef BTL_START_SEC_VAR_CLEARED_16
  #ifdef __TASKING__
    #pragma section farbss=".bss.BTL_U_DATA"
    #pragma align 2
  #elif defined __GHS__
    #pragma ghs section bss=".bss.BTL_U_DATA"
    #pragma alignvar (2)
  #endif
#elif defined (BTL_STOP_SEC_VAR_CLEARED_16)
  #undef BTL_STOP_SEC_VAR_CLEARED_16
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_CLEARED_32)
  #undef BTL_START_SEC_VAR_CLEARED_32
  #ifdef __TASKING__
    #pragma section farbss=".bss.BTL_U_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section bss=".bss.BTL_U_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_VAR_CLEARED_32)
  #undef BTL_STOP_SEC_VAR_CLEARED_32
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef BTL_START_SEC_VAR_CLEARED_UNSPECIFIED
  #ifdef __TASKING__
    #pragma section farbss=".bss.BTL_U_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section bss=".bss.BTL_U_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef BTL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_CLEARED_GLOBALB_UNSPECIFIED)
  #undef BTL_START_SEC_VAR_CLEARED_GLOBALB_UNSPECIFIED
  #ifdef __GHS__
  #pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
  #endif
#elif defined (BTL_STOP_SEC_VAR_CLEARED_GLOBALB_UNSPECIFIED)
  #undef BTL_STOP_SEC_VAR_CLEARED_GLOBALB_UNSPECIFIED
  #ifdef __GHS__
  #pragma ghs section
  #endif

#elif defined (BTL_START_SEC_VAR_INIT)
  #undef BTL_START_SEC_VAR_INIT
  #ifdef __TASKING__
    #pragma section fardata="BTL_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section data=".BTL_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_VAR_INIT)
  #undef BTL_STOP_SEC_VAR_INIT
  #ifdef __TASKING__
    #pragma section fardata restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_INIT_BOOLEAN)
  #undef BTL_START_SEC_VAR_INIT_BOOLEAN
  #ifdef __TASKING__
    #pragma section fardata="BTL_DATA"
    #pragma align 1
  #elif defined __GHS__
    #pragma ghs section data=".BTL_DATA"
    #pragma alignvar (1)
  #endif
#elif defined (BTL_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef BTL_STOP_SEC_VAR_INIT_BOOLEAN
  #ifdef __TASKING__
    #pragma section fardata restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_INIT_8)
  #undef BTL_START_SEC_VAR_INIT_8
  #ifdef __TASKING__
    #pragma section fardata="BTL_DATA"
    #pragma align 1
  #elif defined __GHS__
    #pragma ghs section data=".BTL_DATA"
    #pragma alignvar (1)
  #endif
#elif defined (BTL_STOP_SEC_VAR_INIT_8)
  #undef BTL_STOP_SEC_VAR_INIT_8
  #ifdef __TASKING__
    #pragma section fardata restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_INIT_16)
  #undef BTL_START_SEC_VAR_INIT_16
  #ifdef __TASKING__
    #pragma section fardata="BTL_DATA"
    #pragma align 2
  #elif defined __GHS__
    #pragma ghs section data=".BTL_DATA"
    #pragma alignvar (2)
  #endif
#elif defined (BTL_STOP_SEC_VAR_INIT_16)
  #undef BTL_STOP_SEC_VAR_INIT_16
  #ifdef __TASKING__
    #pragma section fardata restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_INIT_32)
  #undef BTL_START_SEC_VAR_INIT_32
  #ifdef __TASKING__
    #pragma section fardata="BTL_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section data=".BTL_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_VAR_INIT_32)
  #undef BTL_STOP_SEC_VAR_INIT_32
  #ifdef __TASKING__
    #pragma section fardata restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef BTL_START_SEC_VAR_INIT_UNSPECIFIED
  #ifdef __TASKING__
    #pragma section fardata="BTL_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section data=".BTL_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef BTL_STOP_SEC_VAR_INIT_UNSPECIFIED
  #ifdef __TASKING__
    #pragma section fardata restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

/*******************************************************************************
*                  Named memory segment for static variables                  **
*******************************************************************************/
#elif defined (BTL_START_SEC_SVAR_NO_INIT)
  #undef BTL_START_SEC_SVAR_NO_INIT
  #ifdef __TASKING__
    #pragma section farbss="BTL_SU_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section bss=".BTL_SU_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_SVAR_NO_INIT)
  #undef BTL_STOP_SEC_SVAR_NO_INIT
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_SVAR_CLEARED)
  #undef BTL_START_SEC_SVAR_CLEARED
  #ifdef __TASKING__
    #pragma section farbss="BTL_SU_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section bss=".BTL_SU_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_SVAR_CLEARED)
  #undef BTL_STOP_SEC_SVAR_CLEARED
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_SVAR_INIT)
  #undef BTL_START_SEC_SVAR_INIT
  #ifdef __TASKING__
    #pragma section fardata="BTL_S_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section data=".BTL_S_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_SVAR_INIT)
  #undef BTL_STOP_SEC_SVAR_INIT
  #ifdef __TASKING__
    #pragma section fardata restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

/*******************************************************************************
*                     Named memory segment for specific data                  **
*******************************************************************************/
#elif defined (BTL_START_SEC_VAR_RESET_SAVE)
  #undef BTL_START_SEC_VAR_RESET_SAVE
  #ifdef __TASKING__
    #pragma protect on
    #pragma section farbss="BTL_RS_DATA"
    #pragma section fardata="BTL_RS_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section data=".BTL_RS_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_VAR_RESET_SAVE)
  #undef BTL_STOP_SEC_VAR_RESET_SAVE
  #ifdef __TASKING__
    #pragma protect off
    #pragma section farbss restore
    #pragma section fardata restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_FLS_START_SEC_VAR_NO_INIT)
  #undef BTL_FLS_START_SEC_VAR_NO_INIT
  #ifdef __TASKING__
    #pragma section farbss="BTL_CFLS_BSS"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section bss=".BTL_CFLS_BSS"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_FLS_STOP_SEC_VAR_NO_INIT)
  #undef BTL_FLS_STOP_SEC_VAR_NO_INIT
  #ifdef __TASKING__
    #pragma section farbss restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_FLS_START_SEC_VAR_CLEARED)
  #undef BTL_FLS_START_SEC_VAR_CLEARED
  #ifdef __TASKING__
    #pragma section farnoclear="BTL_CFLS_BSS"
    #pragma align 4
  #endif
#elif defined (BTL_FLS_STOP_SEC_VAR_CLEARED)
  #undef BTL_FLS_STOP_SEC_VAR_CLEARED
  #ifdef __TASKING__
    #pragma section farnoclear restore
    #pragma align restore
  #endif

#elif defined (BTL_FLS_START_SEC_VAR_INIT)
  #undef BTL_FLS_START_SEC_VAR_INIT
  #ifdef __TASKING__
    #pragma section fardata="BTL_CFLS_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section data=".BTL_CFLS_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_FLS_STOP_SEC_VAR_INIT)
  #undef BTL_FLS_STOP_SEC_VAR_INIT
  #ifdef __TASKING__
    #pragma section fardata restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
  #endif

#elif defined (BTL_FLS_START_SEC_SVAR_NO_INIT)
  #undef BTL_FLS_START_SEC_SVAR_NO_INIT
  #ifdef __TASKING__
    #pragma section farnoclear="BTL_CFLS_BSS"
    #pragma align 4
  #endif
#elif defined (BTL_FLS_STOP_SEC_SVAR_NO_INIT)
  #undef BTL_FLS_STOP_SEC_SVAR_NO_INIT
  #ifdef __TASKING__
    #pragma section farnoclear restore
    #pragma align restore
  #endif

#elif defined (BTL_FLS_START_SEC_SVAR_CLEARED)
  #undef BTL_FLS_START_SEC_SVAR_CLEARED
  #ifdef __TASKING__
    #pragma section farnoclear="BTL_CFLS_BSS"
    #pragma align 4
  #endif
#elif defined (BTL_FLS_STOP_SEC_SVAR_CLEARED)
  #undef BTL_FLS_STOP_SEC_SVAR_CLEARED
  #ifdef __TASKING__
    #pragma section farnoclear restore
    #pragma align restore
  #endif

#elif defined (BTL_FLS_START_SEC_SVAR_INIT)
  #undef BTL_FLS_START_SEC_SVAR_INIT
  #ifdef __TASKING__
    #pragma section fardata="BTL_CFLS_DATA"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section data=".BTL_CFLS_DATA"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_FLS_STOP_SEC_SVAR_INIT)
  #undef BTL_FLS_STOP_SEC_SVAR_INIT
  #ifdef __TASKING__
    #pragma section fardata restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
  #endif

/*******************************************************************************
*                    Named memory segment for constants                       **
*******************************************************************************/
#elif defined (BTL_START_SEC_CONST)
  #undef BTL_START_SEC_CONST
  #ifdef __TASKING__
    #pragma section farrom="BTL_CONST"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section rodata=".BTL_CONST"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_CONST)
  #undef BTL_STOP_SEC_CONST
  #ifdef __TASKING__
    #pragma section farrom restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_SCONST)
  #undef BTL_START_SEC_SCONST
  #ifdef __TASKING__
    #pragma section farrom="BTL_CONST"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section rodata=".BTL_CONST"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_SCONST)
  #undef BTL_STOP_SEC_SCONST
  #ifdef __TASKING__
    #pragma section farrom restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
    #pragma alignvar (4)
  #endif

/*******************************************************************************
*                  Named memory segment for specific constants                **
*******************************************************************************/
#elif defined (BTL_START_iVERSION_INFO)
  #undef BTL_START_iVERSION_INFO
  #ifdef __TASKING__
    #pragma protect on
    #pragma section farrom="BTL_iVERSION_INFORMATION"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section rodata=".BTL_iVERSION_INFORMATION"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_iVERSION_INFO)
  #undef BTL_STOP_iVERSION_INFO
  #ifdef __TASKING__
   #pragma protect off
   #pragma section farrom restore
   #pragma align restore
  #elif defined __GHS__
   #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_eVERSION_INFO)
  #undef BTL_START_eVERSION_INFO
  #ifdef __TASKING__
    #pragma protect on
    #pragma section farrom="BTL_eVERSION_INFORMATION"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section rodata=".BTL_eVERSION_INFORMATION"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_eVERSION_INFO)
  #undef BTL_STOP_eVERSION_INFO
  #ifdef __TASKING__
    #pragma protect off
    #pragma section farrom restore
    #pragma align restore
  #elif defined __GHS__
   #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_FLS_START_SEC_HEADER)
  #undef BTL_FLS_START_SEC_HEADER
  #ifdef __TASKING__
    #pragma protect on
    #pragma section farrom="BTL_CFLS_HEADER"
    #pragma for_constant_data_use_memory farrom
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section rodata=".BTL_CFLS_HEADER"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_FLS_STOP_SEC_HEADER)
  #undef BTL_FLS_STOP_SEC_HEADER
  #ifdef __TASKING__
    #pragma protect off
    #pragma section farrom restore
    #pragma align restore
  #elif defined __GHS__
   #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_FLS_START_SEC_CONST)
  #undef BTL_FLS_START_SEC_CONST
  #ifdef __TASKING__
    #pragma section farrom="BTL_CFLS_CONST"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section rodata=".BTL_CFLS_CONST"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_FLS_STOP_SEC_CONST)
  #undef BTL_FLS_STOP_SEC_CONST
  #ifdef __TASKING__
    #pragma section farrom restore
    #pragma align restore
  #elif defined __GHS__
   #pragma ghs section
    #pragma alignvar (4)
  #endif

/*******************************************************************************
*                    Named memory segment for code(Flash)                     **
*******************************************************************************/
#elif defined (BTL_START_SEC_CODE)
  #undef BTL_START_SEC_CODE
  #ifdef __TASKING__
    #pragma section code="BTL_CODE"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section text=".BTL_CODE"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_CODE)
  #undef BTL_STOP_SEC_CODE
  #ifdef __TASKING__
    #pragma section code restore
    #pragma align restore
  #elif defined __GHS__
   #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_USER_CODE)
  #undef BTL_START_SEC_USER_CODE
  #ifdef __TASKING__
    #pragma section code="BTL_USER_CODE"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section text=".BTL_USER_CODE"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_USER_CODE)
  #undef BTL_STOP_SEC_USER_CODE
  #ifdef __TASKING__
    #pragma section code restore
    #pragma align restore
  #elif defined __GHS__
   #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_COMMON_CODE)
  #undef BTL_START_SEC_COMMON_CODE
  #ifdef __TASKING__
    #pragma section code="BTL_COMMON_CODE"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section text=".BTL_COMMON_CODE"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_COMMON_CODE)
  #undef BTL_STOP_SEC_COMMON_CODE
  #ifdef __TASKING__
    #pragma section code restore
    #pragma align restore
  #elif defined __GHS__
   #pragma ghs section
    #pragma alignvar (4)
  #endif

#elif defined (BTL_START_SEC_PJS_CODE)
  #undef BTL_START_SEC_PJS_CODE
  #ifdef __TASKING__
    #pragma section code="BTL_PJS_CODE"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section text=".BTL_PJS_CODE"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_STOP_SEC_PJS_CODE)
  #undef BTL_STOP_SEC_PJS_CODE
  #ifdef __TASKING__
    #pragma section code restore
    #pragma align restore
  #elif defined __GHS__
   #pragma ghs section
    #pragma alignvar (4)
  #endif

/*******************************************************************************
*                     Named memory segment for code(RAM)                      **
*******************************************************************************/
#elif defined (BTL_START_SEC_USER_RAM_CODE)
  #undef BTL_START_SEC_USER_RAM_CODE
  #ifdef __TASKING__
    #pragma section code="BTL_RAM_CODE"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section text=".BTL_RAM_CODE"
  #endif
#elif defined (BTL_STOP_SEC_USER_RAM_CODE)
  #undef BTL_STOP_SEC_USER_RAM_CODE
  #ifdef __TASKING__
    #pragma section code restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section text =default
  #endif

#elif defined (BTL_START_SEC_WDG_RAM_CODE)
  #undef BTL_START_SEC_WDG_RAM_CODE
  #ifdef __TASKING__
    #pragma section code="BTL_RAM_CODE"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section text=".BTL_RAM_CODE"
  #endif
#elif defined (BTL_STOP_SEC_WDG_RAM_CODE)
  #undef BTL_STOP_SEC_WDG_RAM_CODE
  #ifdef __TASKING__
    #pragma section code restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section text =default
  #endif

#elif defined (BTL_FLS_START_SEC_CODE)
  #undef BTL_FLS_START_SEC_CODE
  #ifdef __TASKING__
    #pragma protect on
    #pragma section code="BTL_CFLS_CODE"
    #pragma align 4
  #elif defined __GHS__
    #pragma ghs section text=".BTL_CFLS_CODE"
    #pragma alignvar (4)
  #endif
#elif defined (BTL_FLS_STOP_SEC_CODE)
  #undef BTL_FLS_STOP_SEC_CODE
  #ifdef __TASKING__
    #pragma protect off
    #pragma section code restore
    #pragma align restore
  #elif defined __GHS__
    #pragma ghs section
  #endif

/*******************************************************************************
*                              Error handling                                 **
*******************************************************************************/
#else
/**
 * Error ...! no memory section is found
 */
  #error "BTL_MemMap.h: No valid section define found...!"

/**
 * End of START_BTL_MEMMAP
 */
#endif

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
