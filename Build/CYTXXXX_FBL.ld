/*******************************************************************************
**                                                                            **
**  (C) 2020~21 HYUNDAI AUTOEVER Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CYT4BXXX_FBL.ld                                               **
**                                                                            **
**  TARGET    : TRAVEO II                                                     **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides Linker commands for memory placements      **
**				driver software for TRAVEO II.               				  **
**                                                                            **
**  HARDWARE DEPENDANT [yes/no]: Yes                                          **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision    Date          By           Description                         **
********************************************************************************
** 1.0.0.0     22-Apr-2021   JHLim        Initial version                     **
*******************************************************************************/

 /*
  * [Memory Layout for mobilgene Classic SWP] 
  * -----------------------------------------------------------------------------
  * | CM0+ [HSM]      | CM4 or CM7_0 [FBL] | CM4 or CM7_0 [RTSW]                |
  * | RAM : 40KB      | RAM : 40KB         | RAM : End of CM0+ ~ End of MCU     |
  * | ROM : 160KB     | ROM : 128KB        | ROM : End of FBL  ~ End of MCU     |
  * -----------------------------------------------------------------------------
  */

 /* [CODE Blocks Information of TV-II] 
  *  (SB : Single Bank, DB : Dual Bank, LS : Large Sector, SS : Small Sector)
  * 
  * {CYT2B7XX_1M}
  *  - SRAM0             : 0x0800_0000--0x0800_FFFF   (64KB) 
  *  - SRAM1             : 0x0801_0000--0x0801_FFFF   (64KB) 
  *  - CODE_SB_LS[32KB]  : 0x1000_0000--0x100E_FFFF  (960KB) 
  *  - CODE_SB_SS[8KB]   : 0x100F_0000--0x1010_FFFF  (128KB)
  *  - CODE_DB_LS[32KB]  : 0x1000_0000--0x1007_7FFF  (480KB) 
  *  - CODE_DB_SS[8KB]   : 0x1007_8000--0x1008_8000   (64KB)  
  *
  * {CYT2B9XX_2M}
  *  - SRAM0             : 0x0800_0000--0x0801_FFFF  (128KB) 
  *  - SRAM1             : 0x0802_0000--0x0803_FFFF  (128KB) 
  *  - CODE_SB_LS[32KB]  : 0x1000_0000--0x101E_FFFF (1984KB) 
  *  - CODE_SB_SS[8KB]   : 0x101F_0000--0x1020_FFFF  (128KB) 
  *  - CODE_DB_LS[32KB]  : 0x1000_0000--0x100F_7FFF  (992KB) 
  *  - CODE_DB_SS[8KB]   : 0x100F_8000--0x1010_7FFF   (64KB) 
  *  
  * {CYT2BLXX_4M}
  *  - SRAM0             : 0x0800_0000--0x0803_FFFF  (256KB) 
  *  - SRAM1             : 0x0804_0000--0x0807_FFFF  (256KB) 
  *  - CODE_SB_LS[32KB]  : 0x1000_0000--0x103E_FFFF (4032KB) 
  *  - CODE_SB_SS[8KB]   : 0x103F_0000--0x1040_FFFF  (128KB) 
  *  - CODE_DB_LS[32KB]  : 0x1000_0000--0x101F_7FFF (2016KB) 
  *  - CODE_DB_SS[8KB]   : 0x101F_8000--0x1020_7FFF   (64KB)   
  * 
  * {CYT3BB_4BB_4M}
  *  - SRAM0             : 0x2800_0000--0x2807_FFFF  (512KB)
  *  - SRAM1             : 0x2808_0000--0x280B_FFFF  (256KB)
  *  - CODE_SB_LS[32KB]  : 0x1000_0000--0x103E_FFFF (4032KB) 
  *  - CODE_SB_SS[8KB]   : 0x103F_0000--0x1040_FFFF  (128KB) 
  *  - CODE_DB_LS[32KB]  : 0x1000_0000--0x101F_7FFF (2016KB) 
  *  - CODE_DB_SS[8KB]   : 0x101F_8000--0x1020_7FFF   (64KB)   
  * 
  * {CYT4BFXX_8M}
  *  - SRAM0             : 0x2800_0000--0x2807_FFFF  (512KB)
  *  - SRAM1             : 0x2808_0000--0x280B_FFFF  (256KB)  
  *  - SRAM2             : 0x280C_0000--0x280F_FFFF  (256KB)  
  *  - CODE_SB_LS[32KB]  : 0x1000_0000--0x107E_FFFF (8128KB) 
  *  - CODE_SB_SS[8KB]   : 0x107F_0000--0x1082_FFFF  (256KB) 
  *  - CODE_DB_LS[32KB]  : 0x1000_0000--0x103F_7FFF (4064KB) 
  *  - CODE_DB_LS[8KB]   : 0x103F_8000--0x1041_7FFF  (128KB)
  */

MEMORY
{
  /* ROM allocations */
  CM0_ROM_Reserved       : ORIGIN = 0x10000000, LENGTH = 0x28000     /* 160KB      - ROM for CM0 Executable */
  
  FBL_RESET	             : ORIGIN = 0x10028000, LENGTH = 0x200       /* 512 Bytes  - FBL Reset Vector */
  FBL_CODE               : ORIGIN = 0x10028200, LENGTH = 0x1FDB0     /* 127KB      - FBL Executable */
  BTL_iVERSION           : ORIGIN = 0x10047FB0, LENGTH = 0x40        /* 64 Bytes   - FBL version info for internal use */
  BTL_eVERSION           : ORIGIN = 0x10047FF0, LENGTH = 0x10        /* 16 Bytes   - FBL version info for external use */

  /* RAM allocations */
  CM0_RAM_Reserved       : ORIGIN = 0x08000000, LENGTH = 0xA000      /* 40KB       - RAM for CM0 executable */
  
  STARTUP_COMMAND        : ORIGIN = 0x0800A000, LENGTH = 0x10        /* 16 Bytes    - RAM to store Startup command by application to retain control in Bootloader for re-programming */
  BTL_APPL_COMMON_RAM    : ORIGIN = 0x0800A010, LENGTH = 0x40        /* 48 Bytes   - Shared RAM between application to store Programming conditions */
 
  RAM_FLSDRV             : ORIGIN = 0x0800A050, LENGTH = 0xC00       /* 3K         - RAM for Flash driver executable */
  RAM_CODE               : ORIGIN = 0x0800AC50, LENGTH = 0x400       /* 1K         - RAM for RAM CODE */
  RAM_FLS_SCRATCH        : ORIGIN = 0x0800B050, LENGTH = 0x10        /* 16 Bytes   - RAM for SROM system call operation */
  RAM_DATA               : ORIGIN = 0x0800B060, LENGTH = 0x57A0      /* 21K        - RAM for General purpose use */
  RAM_STACK              : ORIGIN = 0x08010800, LENGTH = 0x2000      /* 8KB        - RAM for Stack */

  RAM_RST_NOCLEAR_BTL    : ORIGIN = 0x08012800, LENGTH = 0x1000      /* 4KB        - RAM for debug variables for FBL */
  RETENTION_RAM_UNUSED   : ORIGIN = 0x08013800, LENGTH = 0x800       /* 2KB        - ~ unused by Bootloader 0x28013FFF (40KB)  */
}

SECTIONS
{
  /* ROM SECTIONS */
  .intvec                                    ALIGN(128) : > FBL_RESET
  .picbase                                              : > .
  .startup                                              : > . /* Reset code*/
  .systeminit                                  ALIGN(8) : > . /* SystemInit */
  
   FBL_MODULE_INFO                          0x10028200  : > FBL_CODE
   FBL_CRC                                  0x10028210  : > .
   FBL_SHARED_DATA                          0x10028240  : > .
   FBL_SECURITY_KEY              PAD(256)   0x10028300  : > .
   FBL_SIGNATURE			           PAD(512)   0x10028400  : > .

  .BTL_CODE                                             : > .
  .text                                                 : > .
  .ghtws.text                                           : > .
  
  .BTL_PJS_CODE                                         : > .
  .BTL_USER_CODE                                        : > .
  .BTL_COMMON_CODE                                      : > .
   HSM_DRIVER_SECTION_CODE                              : > . /* HAE HSM 2.0 DRIVER */

  .robase                                     align(4)  : > .
  .rodata                                               : {*(".rodata.*")} > .
  .ROMBYTE                                              : > .
  .sdata2                                               : > .
  .BTL_CONST                                   ALIGN(8) : > .
  .BTL_SCONST                                  ALIGN(8) : > .
  .DRV_SCONST                                           : > .
  .DRV_CONST                                            : > .
  .SEG_BOOT_IDENT                                       : > .
  .SEG_BOOT_CRC                                         : > .
  .SEG_BOOT_BAIFT                                       : > .
  
  .ROM.sdata                                ROM(.sdata) : > .
  .ROM.BTL_S_DATA                      ROM(.BTL_S_DATA) : > .
  .ROM.BTL_RS_DATA                    ROM(.BTL_RS_DATA) : > .

  .ROM.data                                  ROM(.data) : > .
  .ROM.BTL_DATA                          ROM(.BTL_DATA) : > .

  .ROM.BTL_CFLS_HEADER            ROM(.BTL_CFLS_HEADER) : > .
  .ROM.BTL_CFLS_CODE              ROM(.BTL_CFLS_CODE)   : > .
  .ROM.BTL_CFLS_CONST             ROM(.BTL_CFLS_CONST)  : > .
  .ROM.BTL_CFLS_DATA              ROM(.BTL_CFLS_DATA)   : > .
  .ROM.BTL_CFLS_BSS               ROM(.BTL_CFLS_BSS)    : > .
  .ROM.BTL_RAM_CODE               ROM(.BTL_RAM_CODE)    : > .

  .BTL_iVERSION_INFORMATION                    ALIGN(8) : > BTL_iVERSION
  .BTL_eVERSION_INFORMATION                    ALIGN(8) : > BTL_eVERSION


  .BTL_APPL_RS_DATA  NOCLEAR           ALIGN(8) : > STARTUP_COMMAND
  .APPIF_COMMON_RAM  NOCLEAR           ALIGN(8) : > BTL_APPL_COMMON_RAM

   /* RAM SECTIONS */
  .BTL_CFLS_HEADER                            ALIGN(16) : > RAM_FLSDRV
  .BTL_CFLS_CODE                               ALIGN(8) : > . 
  .BTL_CFLS_CONST                              ALIGN(8) : > . 
  .BTL_CFLS_DATA                               ALIGN(8) : > . 
  .BTL_CFLS_BSS                                ALIGN(8) : > .

  .BTL_RAM_CODE                                ALIGN(8) : > RAM_CODE
  
  .sdabase                                     ALIGN(8) : > RAM_DATA
  .sdata                                       ALIGN(8) : {*(".sdata.*")} > .
  .BTL_S_DATA                                  ALIGN(8) : > .
  .data                                        ALIGN(8) : {*(".data.*")} > .
  .BTL_DATA                                    ALIGN(8) : > .
  .sbss                                        ALIGN(8) : > .
  .BTL_SU_DATA                                 ALIGN(8) : > .
  .bss                                         ALIGN(8) : {*(".bss.*")} > .
  .RAM_ZERO_BYTE                               ALIGN(8) : > .
  .RAM_ZERO_LONG                               ALIGN(8) : > .
  .RAM_ZERO_WORD                               ALIGN(8) : > .
  .DRV_U_DATA                                  ALIGN(8) : > .
  .BTL_U_DATA                                  ALIGN(8) : > .
   HSM_DRIVER_SECTION_BSS                      ALIGN(8) : > . /* HAE HSM 2.0 DRIVER */
   HSM_DRIVER_SECTION_CTX                      ALIGN(8) : > . /* HAE HSM 2.0 DRIVER */

  .BTL_FLS_SCRATCH_DATA                        ALIGN(8) : > RAM_FLS_SCRATCH
   
  .stack                           ALIGN(8) PAD(0x1F00) : > RAM_STACK
  .heapbase                                             : > .
  .heap                     NOCLEAR ALIGN(8) PAD(0x100) : > .

  .BTL_RS_DATA                        NOCLEAR ALIGN(8)  : > RAM_RST_NOCLEAR_BTL

  __ghsbegin_stack = ADDR(.stack);
  __ghsend_stack = ENDADDR(.stack);
  __ghsbegin_robase = ADDR(.robase);
    
  __ecc_init_sram_start_address = MEMADDR(RAM_FLSDRV);
  __ecc_init_sram_end_address = MEMENDADDR(RAM_DATA);

  __ghsbegin_picbase     = 0;
  __ghsbegin_robase      = 0;
  __ghsbegin_pidbase     = 0;
  __ghs_rombootcodestart = MEMADDR(FBL_RESET);
  __ghs_rombootcodeend   = MEMENDADDR(BTL_eVERSION);
  __ghs_rambootcodestart = 0;
  __ghs_rambootcodeend   = 0;


  RC_SDATA_SIZE = ((ENDADDR(.ROM.BTL_S_DATA) - ADDR(.ROM.sdata))%8 == 0) ? ((ENDADDR(.ROM.BTL_S_DATA) - ADDR(.ROM.sdata))/8) : ((ENDADDR(.ROM.BTL_S_DATA) - ADDR(.ROM.sdata))/8) + 1 ;
  RC_SDATA_SRC = ADDR(.ROM.sdata);
  RC_SDATA_DEST = ADDR(.sdata);

  RC_DATA_SIZE = ((ENDADDR(.ROM.BTL_DATA) - ADDR(.ROM.data))%8 == 0) ? ((ENDADDR(.ROM.BTL_DATA) - ADDR(.ROM.data))/8) : ((ENDADDR(.ROM.BTL_DATA) - ADDR(.ROM.data))/8) + 1 ;
  RC_DATA_SRC = ADDR(.ROM.data);
  RC_DATA_DEST = ADDR(.data);

  RC_BTL_DATA_SIZE = ((ENDADDR(.ROM.BTL_DATA) - ADDR(.ROM.BTL_DATA))%8 == 0) ? ((ENDADDR(.ROM.BTL_DATA) - ADDR(.ROM.BTL_DATA))/8) : ((ENDADDR(.ROM.BTL_DATA) - ADDR(.ROM.BTL_DATA))/8) + 1 ;
  RC_BTL_DATA_SRC = ADDR(.ROM.BTL_DATA);
  RC_BTL_DATA_DEST = ADDR(.BTL_DATA);

  FLS_COPY_SIZE = ((ENDADDR(.ROM.BTL_CFLS_DATA) - ADDR(.ROM.BTL_CFLS_HEADER))%8 == 0) ? ((ENDADDR(.ROM.BTL_CFLS_DATA) - ADDR(.ROM.BTL_CFLS_HEADER))/8) : ((ENDADDR(.ROM.BTL_CFLS_DATA) - ADDR(.ROM.BTL_CFLS_HEADER))/8) + 1 ;
  FLS_COPY_SRC = ADDR(.ROM.BTL_CFLS_HEADER);
  FLS_COPY_DEST = ADDR(.BTL_CFLS_HEADER);

  RC_RAMCODE_SIZE = ((ENDADDR(.ROM.BTL_RAM_CODE) - ADDR(.ROM.BTL_RAM_CODE))%8 == 0) ? ((ENDADDR(.ROM.BTL_RAM_CODE) - ADDR(.ROM.BTL_RAM_CODE))/8) : ((ENDADDR(.ROM.BTL_RAM_CODE) - ADDR(.ROM.BTL_RAM_CODE))/8) + 1 ;
  RC_RAMCODE_SRC = ADDR(.ROM.BTL_RAM_CODE);
  RC_RAMCODE_DEST = ADDR(.BTL_RAM_CODE);
  
  LD_BTL_RS_ADDR = ADDR(RAM_RST_NOCLEAR_BTL);
  LD_BTL_RS_SIZE = ENDADDR(RAM_RST_NOCLEAR_BTL) - ADDR(RAM_RST_NOCLEAR_BTL);

  LD_BTL_APPIF_RS_ADDR = ADDR(STARTUP_COMMAND);
  LD_BTL_APPIF_RS_SIZE = ENDADDR(BTL_APPL_COMMON_RAM) - ADDR(STARTUP_COMMAND);

}

/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
