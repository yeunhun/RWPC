;*******************************************************************************
;                                                                              ;
;  (C) 2020 HYUNDAI AUTRON Co., Ltd.                                           ;
;  Confidential Proprietary Information. Distribution Limited.                 ;
;  Do Not Copy Without Prior Permission                                        ;
;                                                                              ;
;  SRC-MODULE: Os_InitSram.s                                                   ;
;                                                                              ;
;  TARGET    : CYTxxx                                                          ;
;                                                                              ;
;  PRODUCT   : AUTOSAR OS Improvement Code                                     ;
;                                                                              ;
;  PURPOSE   : SRAM ECC Initialization                                         ;
;                                                                              ;
;  PLATFORM DEPENDANT [yes/no]: Yes                                            ;
;                                                                              ;
;  TO BE CHANGED BY USER [yes/no]: No                                          ;
;                                                                              ;
;*******************************************************************************

;*******************************************************************************
;                      Revision History
;*******************************************************************************
; Revision  Date           By            Description
;*******************************************************************************
; 2.0.0     17-Jun-2020    JH.Cho        Redmine #24132
; 1.0.0     20-Feb-2020    MJ.Woo        Redmine #20864
;*******************************************************************************

;*******************************************************************************
;                      Include Section
;*******************************************************************************
	.include "Os_ExceptTypes.s"

;***************************************************************************//**
;* Function Name        : Os_InitRamSector32
;*
;* Service ID           : NA
;*
;* Description          : This function initialize RAM in 32byte units.
;*                        r0 ~ r11 are used
;*
;* Sync/Async           : Synchronous
;*
;* Re-entrancy          : Non Re-entrant
;*
;* @param [in]            ramSectorCount : Length of Os_RamSectorType array
;* @param [in]            ramSector      : Pointer of Os_RamSectorType array
;*
;* @return              : void
;*
;* @pre                 : None
;*
;* @remarks             : Global Variable(s)     :
;*                        None
;*
;*                        Function(s) invoked    :
;*                        None
;*******************************************************************************
  .align 1
  .thumb2
  .type Os_InitRamSector32, $function
Os_InitRamSector32:
L1: 	; while (Os_Ram_Sector_Por_Count > 0)
  cmp   r0, #0
  beq   L3

  ; read values for RAM init.
  ldr   r4, [r1]        ; ulDefaultValue
  mov   r5, r4
  mov   r6, r4
  mov   r7, r4
  mov   r8, r4
  mov   r9, r4
  mov   r10, r4
  mov   r11, r4
  ldr   r2, [r1, #0x4] 	; ulBaseAddress
  ldr   r3, [r1, #0x8] 	; ulSize
  add   r3, r2, r3      ; End address of RAM area
L2:
  ; clear RAM area
  stmdb r3!, {r4-r11}
  cmp   r2, r3
  bne   L2

  ; continue loop
  sub   r0, r0, #0x1
  add   r1, r1, #0xc    ; Sizeof_Os_RamSectorType == 12
  b     L1
L3:
  bx    lr

;***************************************************************************//**
;* Function Name        : __ghs_board_memory_init
;*
;* Service ID           : NA
;*
;* Description          : Code to initialize all internal RAM
;*                        and set ECC detection
;*
;* Sync/Async           : Synchronous
;*
;* Re-entrancy          : Non Re-entrant
;*
;* Parameters           : None
;*
;* @return              : void
;*
;* @pre                 : This must be executed before using RAM to avoid
;*                        ECC errors.
;*
;* @remarks             : Global Variable(s)     :
;*                        Os_Ram_Sector_Por_Count,
;*                        Os_GaaRamSectorInitPowerOnReset
;*
;*                        Function(s) invoked    :
;*                        Os_InitRamSector32(),
;*                        Os_PreRamInitCallout(), Os_PostRamInitCallout()
;*******************************************************************************
  .globl __ghs_board_memory_init
__ghs_board_memory_init:
  mov   r12, lr 	; save pc register because stack area will be deleted

  ; Call Os_PreRamInitCallout()
  bl    Os_PreRamInitCallout
  ;------------------------------------------------
  ; Set ECC detection
  ;------------------------------------------------
  ; Set 'Fault Structure #1 Interrupt' to NMI
  ldr   r0, =OS_CPUSS_CMx_NMI_CTL0
  ldr   r1, =OS_SYSTEM_INT_NUM_FAULT1
  str   r1, [r0]

  ; Set Fault Report Structure for detecting ECC errors
  ; OS_FAULT_STRUCT1_MASK1 |= OS_FAULT_STRUCT1_MASK1_VALUE;
  ldr   r0, =OS_FAULT_STRUCT1_MASK1
  ldr   r1, [r0]
  ldr   r2, =OS_FAULT_STRUCT1_MASK1_VALUE
  orr   r1, r1, r2
  str   r1, [r0]
  ; OS_FAULT_STRUCT1_STATUS = 0;
  ldr   r0, =OS_FAULT_STRUCT1_STATUS
  mov   r1, #0
  str   r1, [r0]
  ; OS_FAULT_STRUCT1_INTR = 1;
  ldr   r0, =OS_FAULT_STRUCT1_INTR
  mov   r1, #1
  str   r1, [r0]
  ; Enable interrupt of FAULT_STRUCT1
  ; OS_FAULT_STRUCT1_INTR_MASK = 1;
  ldr   r0, =OS_FAULT_STRUCT1_INTR_MASK
  str   r1, [r0]

  ;------------------------------------------------
  ; Initialize RAM
  ;------------------------------------------------
  ; Check whether PowerOnReset(Reset which SRAM not retained) was occured
  ldr   r0, =OS_RES_CAUSE
  ldr   r0, [r0]
  ldr   r1, =OS_RES_CAUSE_NO_RETENTION_MASK
  ands  r2, r0, r1
  bne   PowerOnReset 	; PowerOnReset was occured
  ldr   r0, =OS_RES_CAUSE2
  ldr   r0, [r0]
  ldr   r1, =OS_RES_CAUSE2_NO_RETENTION_MASK
  ands  r2, r0, r1
  bne   PowerOnReset 	; PowerOnReset was occured

  ; Go to EndClearRam
  b     PassRamInit

PowerOnReset:
  ; Call Os_InitRamSector32()
  ldr   r0, _PtrGusOsRamSectorPorCount
  ldr   r0, [r0]
  ldr   r1, _PtrOsGaaRamSectorInitPowerOnReset
  bl 	  Os_InitRamSector32

PassRamInit:
  ; Call Os_PostRamInitCallout()
  bl    Os_PostRamInitCallout
  mov   lr, r12 	; restore lr register
  bx    lr

;***************************************************************************//**
;* Function Name        : Os_ResetMCU
;*
;* Service ID           : NA
;*
;* Description          : This function performs SW reset
;*                        1. Check the RAMx_STATUS.WBEMPTY register and wait
;*                           until the WB_EMPTY bit becomes 1
;*                        2. When WB_EMPTY bit becomes 1, set the retained mode
;*                           to the RAM0_PWR_MACRO_CTLy or RAMx_PWR_CTL register
;*                        3. Issue the software reset.
;*
;* Sync/Async           : Synchronous
;*
;* Re-entrancy          : Non Re-entrant
;*
;* Parameters           : None
;*
;* @return              : void
;*
;* @pre                 : None
;*
;* @remarks             : Global Variable(s)     :
;*                        None
;*
;*                        Function(s) invoked    :
;*                        None
;*******************************************************************************
  .align 1
  .thumb2
  .type Os_ResetMCU, $function
Os_ResetMCU:
  ldr   r1, =OS_CPUSS_RAM_CTL_ECC_EN_MASK

; The SRAM controller write buffer is only used when ECC checking is enabled
WriteBufferWaitRam0:
  ; if ((OS_CPUSS_RAM0_CTL & OS_CPUSS_RAM_CTL_ECC_EN_MASK) != OS_CPUSS_RAM_CTL_ECC_EN_MASK)
  ;   goto WriteBufferWaitRam1
  ldr   r0, =OS_CPUSS_RAM0_CTL
  ldr   r0, [r0]
  ands  r2, r0, r1
  beq   WriteBufferWaitRam1
  ; else
  ;   for (i = OS_WB_WAIT_COUNT; i > 0; i--)
  ;     if ((OS_CPUSS_RAM0_STATUS & WB_EMPTY) == WB_EMPTY)
  ;       goto WriteBufferWaitRam1
  ldr   r0, =OS_CPUSS_RAM0_STATUS
  ldr   r3, =OS_WB_WAIT_COUNT
WriteBufferWaitRam0Loop:
  ldr   r0, [r0]
  ands  r2, r0, #1
  bne   WriteBufferWaitRam1
  sub   r3, r3, #0x1
  cmp   r3, #0
  bne   WriteBufferWaitRam0Loop

WriteBufferWaitRam1:
  ; if ((OS_CPUSS_RAM1_CTL & OS_CPUSS_RAM_CTL_ECC_EN_MASK) != OS_CPUSS_RAM_CTL_ECC_EN_MASK)
  ;   goto ResetMCU
  ldr 	r0, =OS_CPUSS_RAM1_CTL
  ldr 	r0, [r0]
  ands 	r2, r0, r1
  beq 	ResetMCU
  ; else
  ;   for (i = OS_WB_WAIT_COUNT; i > 0; i--)
  ;     if ((OS_CPUSS_RAM1_STATUS & WB_EMPTY) == WB_EMPTY)
  ;       goto ResetMCU
  ldr 	r0, =OS_CPUSS_RAM1_STATUS
  ldr   r3, =OS_WB_WAIT_COUNT
WriteBufferWaitRam1Loop:
  ldr   r0, [r0]
  ands  r2, r0, #1
  bne   ResetMCU
  sub   r3, r3, #0x1
  cmp   r3, #0
  bne   WriteBufferWaitRam1Loop

ResetMCU:
  ; Set all RAM power status to RETAINED
  ldr 	r0, =OS_CPUSS_RAM0_PWR_MACRO_CTL
  ldr 	r1, =OS_CPUSS_PWR_CTL_RETAINED

  ldr   r2, =OS_RAM0_PWR_MACRO_CTL_COUNT
Ram0PwrMacroCtlLoop:
  str 	r1, [r0]
  add   r0, r0, #0x4 ; OS_CPUSS_RAM0_PWR_MACRO_CTL++
  sub   r2, r2, #0x1
  cmp   r2, #0
  bne   Ram0PwrMacroCtlLoop

  ldr 	r0, =OS_CPUSS_RAM1_PWR_CTL
  str 	r1, [r0]

  ; Requeset SW Reset
  ldr 	r0, =OS_CMx_AIRCR
  ldr 	r1, =OS_CMx_AIRCR_SYSRESETREQ
  str 	r1, [r0]

  bx 	lr

  .end
