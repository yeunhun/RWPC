/*******************************************************************************
**                          HYUNDAI AUTRON Co., Ltd.                          **
********************************************************************************
** Copyright (C) HYUNDAI AUTRON Co., Ltd. 2021 - All Rights Reserved          **
** The reproduction, distribution and utilization of this document as well as **
** the communication of its contents to others without explicit authorization **
** is prohibited. Offenders will be held liable for the payment of damages.   **
********************************************************************************
**  SRC-MODULE: StartupArm.c                                                  **
**                                                                            **
**  PRODUCT   : CAN and ToolBox Driver                                        **
**                                                                            **
**  PURPOSE   : This file provides the extern declaration for startup code    **
**              functions                                                     **
**                                                                            **
**  HARDWARE DEPENDANT [yes/no]: No                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision    Date          By           Description                         **
********************************************************************************
** 1.2.0       10-May-2021   JHLim        #28951                              **
** 1.1.0.0     23-Feb-2021   JHLim        Redmine #23964                      **
** 1.0.0       10-April-2020 JaeHyun      Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:D4.10,8.6,8.11,11.4,20.1,21.2 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                       Header File Include Section                          **
*******************************************************************************/
#include "Mcu.h"

/*******************************************************************************
**                Global Variable  Definitions                                **
*******************************************************************************/

extern uint32 RC_DATA_SRC[];
extern uint32 RC_DATA_DEST[];
extern uint32 RC_DATA_SIZE[];

extern uint32 RC_SDATA_SRC[];
extern uint32 RC_SDATA_DEST[];
extern uint32 RC_SDATA_SIZE[];

extern uint32 RC_BTL_DATA_SRC[];
extern uint32 RC_BTL_DATA_DEST[];
extern uint32 RC_BTL_DATA_SIZE[];

extern uint32 RC_RAMCODE_SIZE[];
extern uint32 RC_RAMCODE_SRC[];
extern uint32 RC_RAMCODE_DEST[];

extern uint32 FLS_COPY_SIZE[];
extern uint32 FLS_COPY_SRC[];
extern uint32 FLS_COPY_DEST[];

/* Declarations for symbols created in Startup.s assembly file */
extern uint32 Cy_u32StartupStackStartAddress;
extern uint32 Cy_u32StartupStackEndAddress;
extern void * __ecc_init_sram_start_address;
extern void * __ecc_init_sram_end_address;
extern void * __vector_table;
extern void * __ramVectors;
extern void * __Vectors_Size;

/* RAM start and end address for ECC initialisation */
#define STARTUP_CUSTOMIZE_ECC_INIT_SRAM_START_ADDRESS                          \
  ((uint32) &__ecc_init_sram_start_address)
#define STARTUP_CUSTOMIZE_ECC_INIT_SRAM_END_ADDRESS                            \
  ((uint32) &__ecc_init_sram_end_address)

/*******************************************************************************
**               API/Function External Declaration                            **
*******************************************************************************/
#define BTL_START_SEC_CODE
#include "Btl_MemMap.h"
extern void Startup_Init(void);
#define BTL_STOP_SEC_CODE
#include "Btl_MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:D4.10,8.6,8.11,11.4,20.1,21.2 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                    End of File                                             **
*******************************************************************************/

