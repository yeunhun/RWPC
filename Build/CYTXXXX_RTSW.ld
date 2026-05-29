/* __DISCLAIMER_START__                                                      */
/******************************************************************************
* (c) 2014-2017, Cypress Semiconductor Corporation
* or a subsidiary of Cypress Semiconductor Corporation. All rights
* reserved.
*
* This software, including source code, documentation and related
* materials ( "Software" ), is owned by Cypress Semiconductor
* Corporation or one of its subsidiaries ( "Cypress" ) and is protected by
* and subject to worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ( "EULA" ).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress' s
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
* significant property damage, injury or death ( "High Risk Product" ). By
* including Cypress' s product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
******************************************************************************/
/* __DISCLAIMER_END__                                                        */
/*****************************************************************************/

// Check that necessary definitions are available
#define CY_MCU_rev_a

#if (!defined(_LINK_flash_)) && (!defined(_LINK_sram_))
  #error "Link location not defined or not supported!"
#endif

#if (!defined(_CORE_cm0plus_)) && (!defined(_CORE_cm4_))
  #error "Target core not defined or not supported!"
#endif

#if (!defined(CY_MCU_rev_a)) && (!defined(CY_MCU_rev_b)) && (!defined(CY_MCU_rev_c))
  #error "MCU revision is not defined or not supported!"
#endif
//=======================================================================================
// Following symbol and memory area definitions are used by linker_directives.ld
//=======================================================================================

DEFAULTS
{
    // Constants
    code_flash_total_size      = 2112K
    sram_total_size            = 256K
    sram_base                  = 0x08000000
    sram_used_by_boot_base     = sram_base + sram_total_size - 6K
    sram_private_for_srom      = 2K
    cm0plus_intvec_alignment   = 256   // CPU specific vector table alignment requirement
    cm4_intvec_alignment       = 1024  // CPU specific vector table alignment requirement
    ecc_init_width             = 8

  #if defined(_LINK_sram_)
    sram_can_lin_boot_reserve  = 512
  #else
    sram_can_lin_boot_reserve  = 0
  #endif

  #if defined(CY_MCU_rev_a) || defined(CY_MCU_rev_b)
    sram_start_reserve         = 0                     + sram_can_lin_boot_reserve
    sram_end_reserve           = sram_private_for_srom
  #else
    sram_start_reserve         = sram_private_for_srom + sram_can_lin_boot_reserve
    sram_end_reserve           = 0
  #endif

    sram_start_reserve         = sram_private_for_srom + sram_can_lin_boot_reserve
    sram_end_reserve           = sram_private_for_srom


    sram_total_size_user       = sram_total_size - sram_start_reserve - sram_end_reserve

    //===================================================================================
    //                              USER CONFIGURATION
    //===================================================================================

    // Specify how much SRAM and CODE_FLASH (starting from the first address of the respective memory) shall
    // be used by CM0+ application, the rest of the memory will be automatically assigned to CM4 application
    cm0plus_sram_reserve       = 40K - sram_start_reserve
    cm0plus_code_flash_reserve = 288K
    cm4_RTSW_Reset_Handler_offset = 1K
    //-----------------------------------------------------------------------------------

    // Specify stack and heap sizes for CM0+ and CM4 application independently
    cm0plus_heap_reserve       = 512
    cm0plus_stack_reserve      = 1K
    cm4_heap_reserve           = 512
    cm4_stack_reserve          = 1K
    //===================================================================================


    // Calculation of SRAM distribution among all cores
    cm0plus_sram_offset        = sram_start_reserve
    cm4_sram_offset            = cm0plus_sram_offset  + cm0plus_sram_reserve
    cm4_sram_reserve           = sram_total_size_user - cm4_sram_offset

    // Calculation of CODE_FLASH distribution among all cores

    cm0plus_code_flash_offset  = 0
    cm4_code_flash_offset      = cm0plus_code_flash_offset + cm0plus_code_flash_reserve
    cm4_code_flash_reserve     = code_flash_total_size     - cm4_code_flash_offset

    // Map core dependent definition to generic name for memory and section definition
  #if defined(_CORE_cm0plus_)
    heap_reserve               = cm0plus_heap_reserve
    stack_reserve              = (cm0plus_stack_reserve + (ecc_init_width - 1)) & (~((ecc_init_width - 1))) // Ensure that stack size is an integer multiple of ECC init width (round up)
    sram_offset                = cm0plus_sram_offset
    sram_reserve               = cm0plus_sram_reserve
    code_flash_offset          = cm0plus_code_flash_offset
    code_flash_reserve         = cm0plus_code_flash_reserve
    intvec_alignment           = cm0plus_intvec_alignment

  #else // CM4
    heap_reserve               = cm4_heap_reserve
    stack_reserve              = (cm4_stack_reserve + (ecc_init_width - 1)) & (~((ecc_init_width - 1))) // Ensure that stack size is an integer multiple of ECC init width (round up)
    sram_offset                = cm4_sram_offset
    sram_reserve               = cm4_sram_reserve
    code_flash_offset          = cm4_code_flash_offset
    code_flash_reserve         = cm4_code_flash_reserve
    intvec_alignment           = cm4_intvec_alignment

  #endif

}


MEMORY
{
    SRAM                 : ORIGIN = sram_base + sram_offset,        LENGTH = sram_reserve
    RESET_HANDLER		 : ORIGIN = 0x10000000 + code_flash_offset, LENGTH = cm4_RTSW_Reset_Handler_offset // Offset : (M0+) + (FBL)
    CODE_FLASH           : ORIGIN = 0x10000000 + code_flash_offset+cm4_RTSW_Reset_Handler_offset, LENGTH = code_flash_reserve - cm4_RTSW_Reset_Handler_offset
    WORK_FLASH           : ORIGIN = 0x14000000,                     LENGTH = 0x00020000         //  128 KB
    SFLASH               : ORIGIN = 0x17000000,                     LENGTH = 0x00008000         //   32 KB
    SFLASH_ALT           : ORIGIN = 0x17800000,                     LENGTH = 0x00008000         //   32 KB
}

//
// Program layout
//
SECTIONS
{

    //============================================================================================================
    // ROM type sections
    //------------------------------------------------------------------------------------------------------------

  #if   defined(_LINK_flash_)
    #define MEMORY_FOR_ROM_TYPE_SECTIONS     CODE_FLASH
  #elif defined(_LINK_sram_)
    #define MEMORY_FOR_ROM_TYPE_SECTIONS     SRAM
  #endif


    // Note: .intvec must be the first section in ROM in order for __cmx_vector_base_linker_symbol to be correctly calculated!

    .START_CODE                          ALIGN(4)                : > RESET_HANDLER
    .vector.EXCEPTION                    ALIGN(intvec_alignment) : > CODE_FLASH
     .picbase                                                    : > .
     MAINSW_MODULE_INFO                            0x10048800    : > . /* ID */
     MAINSW_CRC 				   				   0x10048810    : > . /* CRC */
     MAINSW_SECURITY_KEY                           0x10048900    : > . /* Security Key */
     MAINSW_CPD_KEY 				  			   0x100489F0    : > . /* CPD Security Key */
     MAINSW_SIGNATURE 				  			   0x10048A00    : > . /* Signature 512 Byte */
     MAINSW_SIGINFO								   0x10048C00	 : > . /* Siginfo 256 Byte */
     
    .MEM_CHK_ID                                    0x10048D00    : > . /* RomTst */
    .MEM_CHK_CRC                                   0x10048D0C    : > . /* RomTst */
    .MEM_CHECK                                     0x10048D20    : > . /* RomTst */

    .text                                                        : > .
    .ghtws.text                                                  : > .    /* For Green Hills Compiler */
    .intercall                                                   : > .
    .interfunc                                                   : > .
    .fixaddr                                                     : > .
    .fixtype                                                     : > .
    .secinfo                                                     : > .
    .robase                                                      : > .
    .rodata                                                      : > .
    .syscall                                         ALIGN(8)    : > .
    HSM_DRIVER_SECTION_CODE										 : > .
    .ROM.data        ROM(.data)                                  : > .
    .LIB_CODE                                       ALIGN(4K)    : { *(".text.OS_API_CODE") } > .
    .EcucPartition_Main_CODE                        ALIGN(32)    : { *(".text.EcucPartition_Main_CODE")
                                                                     *(".text.EcucPartition_Sub_CODE")
                                                                     *(".text.DEFAULT_CODE")
                                                                     *(".text.DEFAULT_CALLOUT_CODE")
                                                                     *(".text.RTE_CODE")
                                                                     *(".text.OSEKNM_CODE")
                                                                     *(".text.DCM_CODE")
                                                                     *(".text.DEM_CODE")
                                                                     *(".text.CANTP_CODE") 
								     *(".text.DATALOG_CODE")
                                                                     *("HSM_DRIVER_SECTION_CODE") } > .
    .EcucPartition_Main_CONST                       ALIGN(32)    : { *(".rodata.EcucPartition_Main_ROM_CONST")
                                                                     *(".rodata.DEFAULT_ROM_CONST*") } > .
  #if defined(_LINK_sram_)
    // Cypress (ROM and Flash) boot firmware needs an area in SRAM (e.g. for stack). This may cause issues in case of
    // RAM build configurations when code/const sections are loaded there by the debugger, but may get overwritten
    // if reset is triggered by the debug script later on. So in case of RAM build configurations the following
    // statement checks if the area of ROM type sections overlaps the boot area.
    // Comment the statement if the sections shall be linked there anyway.
    //
    // A simple check is sufficient because the boot area is from SRAM_MAX-6KB to SRAM_MAX-2KB and it is unlikely that the ROM sections would only
    // start in the last 2KB (which are anyway not accessible in early MCU revisions because of private SROM RAM area)
    //
    // !!! This statement should be the last entry in the ROM type sections !!! (Note: The symbol will not be used, it is just used to implement the error check)

    __rom_type_sections_end_address = (. < sram_used_by_boot_base) ? . : error("ROM type sections are overlapping the area used by Cypress boot firmware. Check comment in linker file!");
  #endif

    //============================================================================================================
    // RAM type sections
    //------------------------------------------------------------------------------------------------------------

    // >>> SRAM <<<

    .sram_base       ALIGN(ecc_init_width)                       : > SRAM
    .stack           ALIGN(ecc_init_width)    PAD(stack_reserve) : > .
    .OS_STACK_CORE0  ALIGN(8)                            CLEAR   : { *(".bss.OS_RAM_STACK_CORE0_CLEARED_UNSPECIFIED") } > .
    .bss             ALIGN(8)                            CLEAR   : { *(".bss.EcucPartition_Main_RAM_VAR_CLEARED*")
                                                                     *(".bss.DEFAULT_RAM_VAR_CLEARED*")
                                                                     *(".bss.DEFAULT_SAFETY_VAR_CLEARED*")
                                                                     *(".bss.RTE_RAM_VAR_CLEARED*")
                                                                     *(".bss.NVM_RAM_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED")
                                                                     *(".bss.DEFAULT_RAM_VAR_POWER_ON_CLEARED*")
                                                                     *("HSM_DRIVER_SECTION_BSS")
                                                                     *("HSM_DRIVER_SECTION_CTX") } > .
    .bss_noclear                                       NOCLEAR   : { *(".bss.DEFAULT_RAM_VAR_NO_INIT*")
                                                                     *(".bss.DEFAULT_RAM_VAR_SAVED_ZONE*")
                                                                     *(".bss.*NO_INIT*")
                                                                     *(".bss.*SAVED_ZONE") } > .
    .intvec_ram      ALIGN(intvec_alignment)             NOCLEAR : > .
    .pidbase                                        ALIGN(16)    : > .
    .data                                           ALIGN(32)    : { *(".data")
                                                                     *(".feeInitArea_data")
                                                                     *(".data.EcucPartition_Main_RAM_VAR_INIT*")
                                                                     *(".data.DEFAULT_RAM_VAR_INIT*")} > .

    OS_MAIN_BOS = addr(.stack);
    OS_MAIN_TOS = addr(.stack)+sizeof(.stack);

    //============================================================================================================
    // These special symbols mark the bounds of RAM and ROM memory.
    // They are used by the MULTI debugger.
    //------------------------------------------------------------------------------------------------------------
    __ghs_romstart = MEMADDR(CODE_FLASH);
    __ghs_romend   = MEMENDADDR(SFLASH_ALT);
    __ghs_ramstart = MEMADDR(SRAM);
    __ghs_ramend   = MEMENDADDR(SRAM);

    //============================================================================================================
    // These special symbols help GHS to identify the run type of this build: RAM, ROM, ROM-to-RAM
    //------------------------------------------------------------------------------------------------------------
  #if   defined(_LINK_flash_)
    __ghs_rombootcodestart = MEMADDR(CODE_FLASH);
    __ghs_rombootcodeend   = MEMENDADDR(CODE_FLASH);
    __ghs_rambootcodestart = 0;
    __ghs_rambootcodeend   = 0;
  #elif defined(_LINK_sram_)
    __ghs_rombootcodestart = 0;
    __ghs_rombootcodeend   = 0;
    __ghs_rambootcodestart = 0;
    __ghs_rambootcodeend   = 0;
  #endif

    //============================================================================================================
    // The start of CM4 vector table is required by CM0+ application to correctly
    // set CPUSS->CM4_VECTOR_TABLE_BASE register before releasing CM4 from reset
    // Following statements also ensure that the created symbol has the correct alignment
    //------------------------------------------------------------------------------------------------------------
  #ifdef _CORE_cm0plus_
      #if   defined(_LINK_flash_)
        __cm4_rom_start = MEMADDR(CODE_FLASH) - cm0plus_code_flash_offset + cm4_code_flash_offset;
      #elif defined(_LINK_sram_)
        __cm4_rom_start = MEMADDR(SRAM)       - cm0plus_sram_offset       + cm4_sram_offset;
      #endif
    __cm4_vector_base_linker_symbol = (__cm4_rom_start + cm4_intvec_alignment - 1) & ~(cm4_intvec_alignment - 1);
  #endif

    //============================================================================================================
    // These symbols will be used by startup.c / startup_customize.h for RAM ECC initialisation
    //------------------------------------------------------------------------------------------------------------
  #if defined(_LINK_sram_)
    // If "ROM type" sections are linked to SRAM they shall not be cleared by the startup code
    __ecc_init_sram_start_address = ADDR(.sram_base); // The empty .sram_base section is a marker for the start of "RAM type" sections in SRAM
  #else
    __ecc_init_sram_start_address = MEMADDR(SRAM);
  #endif
    __ecc_init_sram_end_address   = MEMENDADDR(SRAM) - 1;


}
