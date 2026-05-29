;*****************************************************************************
;                                                                            ;
;  (C) 2020 HYUNDAI AUTRON Co., Ltd.                                         ;
;  Confidential Proprietary Information. Distribution Limited.               ;
;  Do Not Copy Without Prior Permission                                      ;
;                                                                            ;
;  SRC-MODULE: Os_ExceptTypes.s                                              ;
;                                                                            ;
;  TARGET    : CYTxxx                                                        ;
;                                                                            ;
;  PRODUCT   : AUTOSAR OS Improvement Code                                   ;
;                                                                            ;
;  PURPOSE   : Provision of interrupt specific functionality                 ;
;                                                                            ;
;  PLATFORM DEPENDANT [yes/no]: Yes                                          ;
;                                                                            ;
;  TO BE CHANGED BY USER [yes/no]: No                                        ;
;                                                                            ;
;*****************************************************************************

;*****************************************************************************
;                      Revision History
;*****************************************************************************
; Revision  Date           By            Description
;*****************************************************************************
; 2.0.0     17-Jun-2020    JH.Cho        Redmine #24132
; 1.0.0     29-Jan-2020    MJ.Woo        Redmine #20864
;*****************************************************************************

;*****************************************************************************
;                      Include Section
;*****************************************************************************
  .thumb2

  .globl Os_InitRamSector32
  .globl Os_ResetMCU
  .globl Os_PreRamInitCallout
  .globl Os_PostRamInitCallout

  .globl Os_Ram_Sector_Por_Count
  .globl Os_GaaRamSectorInitPowerOnReset


  ; NMI Control register of CM4 and CM7_0
  .set OS_CPUSS_CMx_NMI_CTL0           0x40200240
  ; Number of CPUSS Fault Structure #1 Interrupt
  .set OS_SYSTEM_INT_NUM_FAULT1        9
  ; Fault Subsystem Registers
  .set OS_FAULT_STRUCT1_STATUS         0x4021010C
  .set OS_FAULT_STRUCT1_MASK1          0x40210154
  .set OS_FAULT_STRUCT1_INTR           0x402101C0
  .set OS_FAULT_STRUCT1_INTR_MASK      0x402101C8
  ; CPUSS_FLASHC_MAIN_NC_ECC(50), CPUSS_RAMC0_NC_ECC(59), CPUSS_RAMC1_NC_ECC(61)
  .set OS_FAULT_STRUCT1_MASK1_VALUE    0x28040000

  ; Reset Cause Observation Register
  .set OS_RES_CAUSE                    0x40261800
  ; Reset Cause Mask which SRAM Retention not supported
  ; - PORVDDD[30], STRUCT_XRES[29], PXRES[28], OCD[23:24], OVD[20:22], BOD[17:19], XRES[16]
  .set OS_RES_CAUSE_NO_RETENTION_MASK  0x71FF0000
  ; Reset Cause Observation Register 2
  .set OS_RES_CAUSE2                   0x40261804
  ; Reset Cause 2 Mask which SRAM Retention not supported
  ; - CSV_REF[16]
  .set OS_RES_CAUSE2_NO_RETENTION_MASK 0x00010000

  ; RAM0 Control register
  .set OS_CPUSS_RAM0_CTL               0x40201300
  ; RAM0 Status register
  .set OS_CPUSS_RAM0_STATUS            0x40201304
  ; RAM0 Power Control register
  .set OS_CPUSS_RAM0_PWR_MACRO_CTL     0x40201340
  ; RAM1 Control register
  .set OS_CPUSS_RAM1_CTL               0x40201380
  ; RAM1 Status register
  .set OS_CPUSS_RAM1_STATUS            0x40201384
  ; RAM1 Power Control register
  .set OS_CPUSS_RAM1_PWR_CTL           0x40201388
  ; ECC_EN mask of the RAM Control register
  .set OS_CPUSS_RAM_CTL_ECC_EN_MASK    0x00010000
  ; Write Buffer Wait Count
  .set OS_WB_WAIT_COUNT                0xFF
  ; Power Control value (VECTKEY|RETAINED) for RETAINED
  .set OS_CPUSS_PWR_CTL_RETAINED       0x05FA0002
  ; Count of RAM0_PWR_MACRO_CTL
  .set OS_RAM0_PWR_MACRO_CTL_COUNT     16

  ; Application Interrupt and Reset Control Register, AIRCR
  .set OS_CMx_AIRCR                    0xE000ED0C
  ; AIRCR value(VECTKEY|SYSRESETREQ) for SW Reset
  .set OS_CMx_AIRCR_SYSRESETREQ        0x05FA0004


  ; Label Address
  .align 4
_PtrGusOsRamSectorPorCount             .word    Os_Ram_Sector_Por_Count
_PtrOsGaaRamSectorInitPowerOnReset     .word    Os_GaaRamSectorInitPowerOnReset

  .end
