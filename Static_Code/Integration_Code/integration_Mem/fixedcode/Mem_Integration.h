/*******************************************************************************
**                                                                            **
**  (C) 2013 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Mem_Integration.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemStack Integration Module                           **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

#ifndef MEMDRIVERINIT_H_
#define MEMDRIVERINIT_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "NvM.h"
#include "HwResource.h"
#include "MemIf_Cfg.h"
#include "Mem_Integration_User.h"

/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/
#define MEM_TRUE                                        (1U)
#define MEM_FALSE                                       (0U)

/* Service ID for OsTask_BSW_Mem_Process */
#define MEM_OSTASK_BSW_MEM_PROCESS_SID                  ((uint8)0x50U)


/* DET Code */
#define MEM_E_ALARM                                     0x19
#define MEM_E_EVENT                                     0x20

#ifdef MEMIF_FLS_DRIVER_INDEX
  #define MEM_FEE_USED          (STD_ON)     

  #if (HWRESOURCE_GET_FAMILY() == HWRESOURCE_RH850F1X)
    /* in case of RH850, Fls is not used but the specific library of the renesas 
     * is included int the Fee(EEL) */     
    #define MEM_FLS_USED          (STD_OFF)
  #else
    #define MEM_FLS_USED          (STD_ON)     
  #endif
  
#else 
  /* FEE is not configured */
  #define MEM_FEE_USED          (STD_OFF)   
  /* FLS is not configured */
  #define MEM_FLS_USED          (STD_OFF)
#endif

#ifdef MEMIF_EEP_DRIVER_INDEX
#define MEM_EA_USED          (STD_ON)
#else
#define MEM_EA_USED          (STD_OFF)
#endif


#define MEM_MAINFUNCTION_NVM()  do { NvM_MainFunction();} while(0)

#if (MEM_FEE_USED == STD_ON)
#define MEM_MAINFUNCTION_FEE()  do { Fee_MainFunction();} while(0)
#else
#define MEM_MAINFUNCTION_FEE()  do {} while(0)
#endif

#if (MEM_FLS_USED == STD_ON)
#define MEM_MAINFUNCTION_FLS()  do { Fls_MainFunction();} while(0)
#else
#define MEM_MAINFUNCTION_FLS()  do {} while(0)
#endif

#if (MEM_EA_USED == STD_ON)
#define MEM_MAINFUNCTION_EA()   do { Ea_MainFunction(); } while(0)
#define MEM_MAINFUNCTION_EEP()  do { Eep_MainFunction();} while(0)
#else
#define MEM_MAINFUNCTION_EA()   do {} while(0)
#define MEM_MAINFUNCTION_EEP()  do {} while(0)
#endif


#if (NVM_DEV_ERROR_DETECT == STD_ON)
#define MEM_REPORT_ERROR(sid,error) \
do {\
  (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, (sid), (error));\
} while(0)
#else
#define MEM_REPORT_ERROR(sid,error)  do {} while(0)
#endif /* end of DET */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
extern uint8 ConfigIDRamBlock[2];

#ifdef NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock1
extern uint8 NvMBlock_IntTst_TestBlock1_Ram_Block[10];
#endif

#ifdef NvMConf_NvMBlockDescriptor_NvMBlock_IntTst_TestBlock2
extern uint8 NvMBlock_IntTst_TestBlock2_Ram_Block[10];
#endif

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, NVM_CODE) Mem_Driver_StartUp(void);
extern FUNC(void, NVM_CODE) Mem_FlsInitPerform(void);
extern FUNC(void, NVM_CODE) Mem_FeeInitPerform(void);
extern FUNC(void, NVM_CODE) Mem_Driver_ShutDown(void);


#define NVM_STOP_SEC_CODE
#include "MemMap.h"


/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "Not a defect" */

#endif /* MEMDRIVERINIT_H_ */
