/*******************************************************************************
**                                                                            **
**  (C) 2019-2020 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_PortTypes.h                                                **
**                                                                            **
**  TARGET    : CYTxxx                                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for CYTxxx related register                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:       Yes                                    **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:    No                                     **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 2.3.0     26-Jan-2021    YH.Han        Redmine #27953                      **
** 2.1.0     11-Dec-2020    JH.Cho        Redmine #26391                      **
** 2.0.1     14-Aug-2020    JH.Cho        Redmine #25096                      **
** 2.0.0     16-JUN-2020    JH.Cho        Redmine #23917 #24316               **
** 1.1.0     06-Mar-2020    MJ.Woo        Redmine #22057                      **
** 1.0.0     23-Dec-2019    MJ.Woo        Redmine #18913                      **
*******************************************************************************/
#ifndef OS_PORTTYPES_H
#define OS_PORTTYPES_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "Reviewed and tested code" */
/* polyspace:begin<MISRA-C3:2.4:Not a defect:Justify with annotations> Tags may be used for cross reference */
/* polyspace:begin<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace:begin<MISRA-C3:8.5:Not a defect:Justify with annotations> Redundant declaration for generated code */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"
#include "arm_ghs.h"
#include "Os_Arch_SystemCall.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/**
 * @addtogroup OS_CYTXXX_ESDD
 * @{ */

/*
 * Define NULL pointer value.
 */
#ifndef NULL
#define NULL  (void *) 0
#endif

/* Types for address/size of memory object
*/
typedef int               Os_Sint_T;
typedef int               Os_Address_T;
typedef unsigned int      Os_Int_T;
typedef unsigned int      Os_Size_T;

/** Types for integer type
 *  \n{Ref: SWR_OS_CYTXXX_011} */
typedef uint32    Os_OldLevel_T;
/** Types for size of memory object
 *  \n{Ref: SWR_OS_CYTXXX_011} */
typedef unsigned int Os_IntStatus_T;
/** Types for bit filed of 8bit register
 *  \n{Ref: SWR_OS_CYTXXX_011} */
typedef unsigned char Os_Reg8;
/** Types for bit filed of 32bit register
 *  \n{Ref: SWR_OS_CYTXXX_011} */
typedef unsigned int Os_Reg32;

/** Types for returning from context save/load function
 *  \n{Ref: SWR_OS_CYTXXX_006} */
typedef struct STagTdd_Os_ContextSwitch
{
  /*------------SW Context (4*10)--------------*/
  uint32 ulR4;   /* Expression register, preserved by child function */
  uint32 ulR5;   /* Expression register, preserved by child function */
  uint32 ulR6;   /* Expression register, preserved by child function */
  uint32 ulR7;   /* Expression register, argument pointer(AP), preserved by child function */
  uint32 ulR8;   /* Expression register, preserved by child function */
  uint32 ulR9;   /* Expression register, preserved by child function */
  uint32 ulR10;  /* Expression register, preserved by child function */
  uint32 ulR11;  /* Expression register, preserved by child function */
  uint32 ulSP;   /* Stack Pointer(R13)  */
  uint32 ulEXC_RETURN;
  /*------------HW Context (4*8)--------------*/
  uint32 ulR0;   /* Argument register, return register, expression register, preserved by parent function  */
  uint32 ulR1;   /* Argument register, return register, expression register, preserved by parent function  */
  uint32 ulR2;   /* Argument register, return register, preserved by parent function  */
  uint32 ulR3;   /* Argument register, return register, preserved by parent function  */
  uint32 ulR12;  /* Expression register, instruction pointer(IP), preserved by parent function */
  uint32 ulLR;   /* Link register, expression register (R14) */
  uint32 ulPC;   /* Program counter, not preserved */
  uint32 ulPSR;  /* Program status register, preserved by child function */

  /* Address of current stack frame of Task or CAT2 ISR */
  P2VAR(Os_StackType, AUTOMATIC, OS_VAR) pPowerOnSP;
} Tdd_Os_ContextSwitch;

/** Types for structure of Os ISR priority configuration
 *  \n{Ref: SWR_OS_CYTXXX_001} */
typedef struct
{
  /* polyspace +2 MISRA-C3:20.7 [Justified:Low] "AUTOSAR compiler abstraction" */
  P2VAR(volatile uint32, AUTOMATIC, OS_VAR) pICRAddress;
                            /**< Variable to Interrupt Control Register(CPUSS_CMx_SYSTEM_INT_CTLn (x: 4, 7_0, 7_1))
                             *   address of interrupt */
  volatile uint16 usISRPriorityMask;
                            /**< Variable to indicate priority of
                             *   interrupt along with processor select bits */
  uint8 ucISRType;          /**< Type of ISR */

  #if (OS_APPLICATION == STD_ON)
  ApplicationType ddAppId;  /**< Application ID */
  #endif
} Tdd_Os_ISRPriority;

/** Types for structure of Os ISR index configuration
 *  \n{Ref: SWR_OS_CYTXXX_001} */
typedef struct
{
  uint8 ucIsrCount;         /**< Variable to give total no of ISR */
  uint8 ucIsrStartIdx;      /**< Variable to give start Index of ISR */
} Tdd_Os_ISRIndex;
/** @} */

/** Types for structure of Category 1 ISR function pointer
 *  \n{Ref: SWR_OS_CYTXXX_001} */
typedef void (*Os_Cat1IsrPtrType)(void);

/*
 * Exceptions
 */

/** Enum for Trap(Exception) category
 *  \n{Ref: SWR_OS_CYTXXX_004} */
typedef enum
{
  OS_TRAP_NONE             = 0U,
  OS_TRAP_RESET            = 1U,
  OS_TRAP_NMI              = 2U,
  OS_TRAP_HARD_FAULT       = 3U,
  OS_TRAP_MEMORY_MNG_FAULT = 4U,
  OS_TRAP_BUS_FAULT        = 5U,
  OS_TRAP_USAGE_FAULT      = 6U,
  OS_TRAP_UNDEFINED        = 256U
} Os_TrapType;

/** Types for structure of HardFault Status
 *  \n{Ref: SWR_OS_CYTXXX_004} */
typedef volatile struct
{
  Os_Reg32 Reserved1:  1; /**< Reserved */
  Os_Reg32 VECTTBL:    1; /**< BusFault on vector table reading during exception processing */
  Os_Reg32 Reserved2: 28; /**< Reserved */
  Os_Reg32 FORCED:     1; /**< Forced hard fault from Configurable priority that can not be handles, either because of priority or because it is disabled */
  Os_Reg32 DEBUGEVT:   1; /**< Reserved for Debug use */
} Os_HardFaultStatusType;

/** Types for structure of UsageFault Status
 *  \n{Ref: SWR_OS_CYTXXX_004} */
typedef volatile struct
{
  Os_Reg32 UNDEFINSTR: 1; /**< Reserved */
  Os_Reg32 INVSTATE:   1; /**< Invalid state UsageFault, execute an instruction that makes illegal usage of the EPSR. */
  Os_Reg32 INVPC:      1; /**< Invalid PC load UsageFault, caused by an invalid PC loaded by EXC_RETURN */
  Os_Reg32 NOCP:       1; /**< No coprocessor UsageFault */
  Os_Reg32 UNALIGNED:  1; /**< Unaligned access UsageFault */
  Os_Reg32 DIVBYZERO:  1; /**< Divide by Zero UsageFault */
  Os_Reg32 Reserved:   6; /**< Reserved */
} Os_UsageFaultStatusType;

/** Types for structure of BusFault Status
 *  \n{Ref: SWR_OS_CYTXXX_004} */
typedef volatile struct
{
  Os_Reg32 IBUSERR:    1; /**< Instruction bus error */
  Os_Reg32 PRECISERR:  1; /**< PC value stacked for the exception return points to the instruction that caused the fault. (BFAR) */
  Os_Reg32 IMPRECISERR:1; /**< Imprecise data bus error */
  Os_Reg32 UNSTKERR:   1; /**< BusFault from unstacking for a return from exception */
  Os_Reg32 STKERR:     1; /**< BusFault from stacking for an exception entry */
  Os_Reg32 LSPERR:     1; /**< BusFault from floating-point lazy state preservation */
  Os_Reg32 Reserved:   1; /**< Reserved */
  Os_Reg32 BFARVALID:  1; /**< BusFault Address Register(BFAR) valid flag */
} Os_BusFaultStatusType;

/** Types for structure of MemFault Status
 *  \n{Ref: SWR_OS_CYTXXX_004} */
typedef volatile struct
{
  Os_Reg32 IACCVIOL:   1; /**< Instruction access violation */
  Os_Reg32 DACCVIOL:   1; /**< Data access violation, the processor attempted a load/store at a location that does not permit the operation (MMAR)*/
  Os_Reg32 Reserved1:  1; /**< Reserved */
  Os_Reg32 MUNSTKERR:  1; /**< MemFault from unstacking for exception entry */
  Os_Reg32 MSTKERR:    1; /**< MemFault from stacking for exception entry */
  Os_Reg32 MLSPERR:    1; /**< MemFault from floating-poin lazy state perservation */
  Os_Reg32 Reserved2:  1; /**< Reserved */
  Os_Reg32 MMARVALID:  1; /**< MemManage Fault Address(MMFAR) valid flag */
} Os_MemFaultStatusType;

/** Types for structure of ConfigFault Status
 *  \n{Ref: SWR_OS_CYTXXX_004} */
typedef volatile struct
{
  Os_MemFaultStatusType   MMFSR; /**< MemFault */
  Os_BusFaultStatusType   BFSR;  /**< BusFault */
  Os_UsageFaultStatusType UFSR;  /**< UsageFault */
} Os_ConfigFaultStatusType;

/** Macro to define the address of CFSR
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_CONFIG_FAULT_STATUS_ADDR      (0xE000ED28UL)
/** Macro to define the address of MMFSR
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_CONFIG_MMFSR_STATUS_ADDR      (0xE000ED28UL)
/** Macro to define the address of BFSR
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_CONFIG_BFSR_STATUS_ADDR       (0xE000ED29UL)
/** Macro to define the address of UFSR
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_CONFIG_UFSR_STATUS_ADDR       (0xE000ED2AUL)
/** Macro to define the address of HFSR
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_HARD_FAULT_STATUS_ADDR        (0xE000ED2CUL)
/** Macro to define the address of MMFAR
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_CONFIG_MMFAR_ADDR             (0xE000ED34UL)
/** Macro to define the address of BFAR
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_CONFIG_BFAR_ADDR              (0xE000ED38UL)
/** Macro to define the mask of HardFault status
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_HARD_FAULT_STATUS_MASK        (0xC0000003UL)
/** Macro to define the mask of MemManage status
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_CONFIG_MMFSR_FAULT_STATUS_MASK       (0xFFU)
/** Macro to define the mask of BusFault status
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_CONFIG_BFSR_FAULT_STATUS_MASK        (0xFFU)
/** Macro to define the mask of UsageFault status
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_CONFIG_UFSR_FAULT_STATUS_MASK      (0x030FU)

/** Types for structure of saving exception information
 *  \n{Ref: SWR_OS_CYTXXX_004} */
typedef struct
{
  Os_TrapType               enTrapClass;  /* Exception category */
  uint32                    HFSR;         /* HardFault Status Register */
  uint32                    CFSR;         /* Configurable Fault Status Register */
  Tdd_Os_ContextSwitch      ExecCtxt;     /* Exception Context */
  MemoryStartAddressType    pExecAddr;    /* Exception occurred Address */
  MemoryStartAddressType    pMMFAR;       /* Memory Fault Address */
  MemoryStartAddressType    pBFAR;        /* Bus Fault Address */
} Os_TrapInfoType;

/** The following enum is defined for HW Timer channel id */
typedef enum
{
  OS_SYSTICK = 0u,   /* OS Counter */
  OS_TCPWM0_2_1,     /* Timing Protection - TimeBudget */
  OS_TCPWM0_2_2,     /* Timing Protection - TimeFrame */
  OS_TCPWM0_2_3,     /* Timing Protection - TimeBudget for M7-1 */
  OS_TCPWM0_2_4,     /* Timing Protection - TimeFrame for M7-1 */
  OS_TCPWM1_2_1,     /* Timing Protection - TimeBudget for M7-1 */
  OS_TCPWM1_2_2,     /* Timing Protection - TimeFrame for M7-1 */
  OS_INVALID_TIMER
} Os_TimerIdType;

struct STagTdd_Os_HardwareCounter
{
  /* polyspace +2 MISRA-C3:20.7 [Justified:Low] "AUTOSAR compiler abstraction" */
  P2VAR(volatile uint32, AUTOMATIC, OS_VAR) pNextInterruptTick;
                              /**< Pointer
                                   to the next timer interrupt tick(HW) */
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) pStaticCounter;
                              /**< Pointer to counter object */
  TickType ddNextCount;       /**< The next counter tick value
                                   at next timer interrupt */
  TickType ddTicksPerBase;    /**< HW timer ticks to raise 1 Counter tick */
  Os_TimerIdType enChannelId; /**< Timer Channel ID*/
};

/** Type of NVIC_IPR register. MSB 3bits are valid(prioriy range 0 ~ 7) */
typedef volatile Os_Reg8 OS_NVIC_IPR_type;

/* System Handler controls */
/** Macro to define SHCSR (System Handler Control and State Register)
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_SYSHANDLER_CTRL_ADDR        (0xE000ED24U)
/** Macro to define the mask of USGFAULTENA
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_USAGE_F_ENA                 (0x00040000U)
/** Macro to define the mask of BUSFAULTENA
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_BUS_F_ENA                   (0x00020000U)
/** Macro to define the mask of MEMFAULTENA
 *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_ARM_M_MEM_F_ENA                   (0x00010000U)

/* IRQ controls */
/** Macro to define CYT2B7
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define CYT2B7 1
/** Macro to define CYT2B9
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define CYT2B9 2
/** Macro to define CYT2BL
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define CYT2BL 3
/** Macro to define CYT4BB
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define CYT4BB 4
/** Macro to define CYT4BF
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define CYT4BF 5
/** Macro to define the number of External Interrupt
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#if (OS_PROCESSOR_SERIES == CYT2B7)
#define OS_ARM_M_NUM_NVIC_EXTERNAL           (16U)
#elif (OS_PROCESSOR_SERIES == CYT2B9)
#define OS_ARM_M_NUM_NVIC_EXTERNAL           (16U)
#elif (OS_PROCESSOR_SERIES == CYT2BL)
#define OS_ARM_M_NUM_NVIC_EXTERNAL           (16U)
#elif (OS_PROCESSOR_SERIES == CYT4BB)
#define OS_ARM_M_NUM_NVIC_EXTERNAL           (16U)
#elif (OS_PROCESSOR_SERIES == CYT4BF)
#define OS_ARM_M_NUM_NVIC_EXTERNAL           (16U)
#else
#error "Specified MCU is not supported."
#endif
/** Macro to define the start address of ISER (Interrupt Set-Enable Register)
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define OS_ARM_M_IRQ_EN_SET_START            (0xE000E100U)
/** Macro to define the end address of ISER (Interrupt Set-Enable Register)
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define OS_ARM_M_IRQ_EN_SET_END              (OS_ARM_M_IRQ_EN_SET_START + \
                                             ((OS_ARM_M_NUM_NVIC_EXTERNAL >> 5) * 4U))
/** Macro to define the start address of ICER (Interrupt Clear-Enable Register)
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define OS_ARM_M_IRQ_EN_CLR_START            (0xE000E180U)
/** Macro to define the end address of ICER (Interrupt Clear-Enable Register)
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define OS_ARM_M_IRQ_EN_CLR_END              (OS_ARM_M_IRQ_EN_CLR_START + \
                                             ((OS_ARM_M_NUM_NVIC_EXTERNAL >> 5) * 4U))
/** Macro to define the start address of ICPR (Interrupt Clear-Pending Register)
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define OS_ARM_M_IRQ_CLEAR_PENDING_START     (0xE000E280U)
/** Macro to define the end address of ICPR (Interrupt Clear-Pending Register)
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define OS_ARM_M_IRQ_CLEAR_PENDING_END       (OS_ARM_M_IRQ_CLEAR_PENDING_START + \
                                             ((OS_ARM_M_NUM_NVIC_EXTERNAL >> 5) * 4U))
/** Macro to define the start address of IABR (Interrupt Active Bit Register)
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define OS_ARM_M_IRQ_ACTIVE_START            (0xE000E300U)
/** Macro to define the end address of IABR (Interrupt Active Bit Register)
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define OS_ARM_M_IRQ_ACTIVE_END              (OS_ARM_M_IRQ_ACTIVE_START + \
                                             ((OS_ARM_M_NUM_NVIC_EXTERNAL >> 5) * 4U))
/** Macro to define the start address of IPR (Interrupt Priority Register)
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define OS_ARM_M_IRQ_IPR_START               (0xE000E400U)
/** Macro to define the end address of IPR (Interrupt Priority Register)
 *  \n{Ref: SWR_OS_CYTXXX_001} */
#define OS_ARM_M_IRQ_IPR_END                 (OS_ARM_M_IRQ_IPR_START + \
                                             ((OS_ARM_M_NUM_NVIC_EXTERNAL >> 2) * 4U))
/*
 * CPU, TOOL, OS Definition
 */
/* OS_CACHE_MODE must be set to one of these in the architecture. Other
 * macros (like OS_CACHE_LINE_LEN) need to be set, and the architecture must supply
 * primitives for cache operations.
 * See kern-cacheflush.c/kern-cacheinvalidate.c/kern-cacheflushinvalidate.c for details.
*/
/** Macro to define no Cache operation
 *  \n{Ref: SWR_OS_CYTXXX_011} */
#define OS_CACHE_MODE_NONE    1   /* No cache, or no cache operations. */
/** Macro to define Cache operations performed on single line
 *  \n{Ref: SWR_OS_CYTXXX_011} */
#define OS_CACHE_MODE_LINE    2   /* Cache operations performed on single line. */
/** Macro to define Cache operation mode
 *  \n{Ref: SWR_OS_CYTXXX_011} */
#define OS_CACHE_MODE       OS_CACHE_MODE_NONE
/** Macro to define Cache line length
 *  \n{Ref: SWR_OS_CYTXXX_011} */
#define OS_CACHE_LINE_LEN     32
/** Macro to define SafeyKernel usage
 *  \n{Ref: SWR_OS_CYTXXX_011} */
#define OS_SAFETY_KERNEL      STD_OFF

#if (OS_MULTICORE == STD_ON)
/** Structure of CPUSS_IDENTITY register
 *  \n{Ref: SWR_OS_CYTXXX_011} */
typedef volatile union
{
  struct
  {
    Os_Reg32 P        :1;
    Os_Reg32 NS       :1;
    Os_Reg32          :2;
    Os_Reg32 PC       :4;
    Os_Reg32 MS       :4;
    Os_Reg32          :20;
  } B;
  sint32 I;
  uint32 U;
} OS_CPUSS_IDENTITY_type;

/** CPUSS_IDENTITY Register
 *  \n{Ref: SWR_OS_CYTXXX_011} */
#define OS_CPUSS_IDENTITY            (*(volatile OS_CPUSS_IDENTITY_type*) 0x40200000UL)

/** Macro to define core id for CM7_0
 *  \n{Ref: SWR_OS_CYTXXX_009} */
#define CM7_0                 0u
/** Macro to define core id for CM7_1
 *  \n{Ref: SWR_OS_CYTXXX_009} */
#define CM7_1                 1u
/** Macro to get current core id
 *  \n{Ref: SWR_OS_CYTXXX_009} */
#define Os_MyCore()           ((OS_CPUSS_IDENTITY.B.MS == 14) ? CM7_0 : CM7_1)
/** Macro to get Core ID
 *  \n{Ref: SWR_OS_CYTXXX_009} */
#define OS_GET_CORE_ID(OS_CORE_ID)\
    do{\
    OS_CORE_ID = Os_MyCore();\
    }while(0)
#else
/** Macro to get current core id
 *  \n{Ref: SWR_OS_CYTXXX_009} */
#define Os_MyCore()           0u
/** Macro to get Core ID
 *  \n{Ref: SWR_OS_CYTXXX_009} */
#define OS_GET_CORE_ID(OS_CORE_ID)
#endif
/** Macro to define the core id of core 0
 *  \n{Ref: SWR_OS_CYTXXX_009} */
#define OS_CORE_ZERO          0u

/** Macro to define the core id of Master core (OS628)
 *  \n{Ref: SWR_OS_CYTXXX_009} */
#define OS_CORE_ID_MASTER               OS_CORE_ZERO

/* polyspace<MISRA-C3:8.6:Not a defect:Justify with annotations> Defined in .ld file */
extern void OS_ROM_API_CODE_START;
/* polyspace<MISRA-C3:8.6:Not a defect:Justify with annotations> Defined in .ld file */
extern void OS_ROM_API_CODE_END;
/* polyspace<MISRA-C3:8.6:Not a defect:Justify with annotations> Defined in .ld file */
extern void LIB_VAR_START;
/* polyspace<MISRA-C3:8.6:Not a defect:Justify with annotations> Defined in .ld file */
extern void LIB_VAR_END;

/*
 * Timer
 */
 /** Macro to define margine(50us) to prevent missing System Timer interrupt
  *  It used updating Timer compare register
  *  \n{Ref: SWR_OS_CYTXXX_007} */
#define OS_STM_MARGINE                  ((Os_GulStmClock >> 6) * 50u) //62.5

 /** Macro to define size of exception vector table
  *  \n{Ref: SWR_OS_CYTXXX_004} */
#define NUM_ELE_VECTOR_TABLE            256
 /** Macro to define Invalid index value of ISR Table
  *  \n{Ref: SWR_OS_CYTXXX_004} */
#define OS_INVALID_ISR_ID               (uint16)0xFFFFu

/** @} */

#define OS_DEBUG                        STD_ON
#if (OS_DEBUG == STD_ON)
/* polyspace +2 MISRA-C3:10.3 [Justified:Medium] "Harmless comparison expression used" */
#define OS_ASSERT(x)                    Os_Assert(x)
#else
#define OS_ASSERT(x)
#endif

#ifndef UNUSED
  /* Check for unused parameter warnings*/
  #define UNUSED(variable)              (void) variable
#endif

/*
 * Inline function for system call
 */

#if (OS_TIMING_PROTECTION == STD_ON)
/** The highest ISR priority value supported by the hardware.
 *  When Timing Protection enabled, MAX Priority value will decreased 1.
 *  Because MAXIMUM value is reserved for Timing Protection interrupt */
#define OS_INT_MAX_PRIORITY              (2U)
#else
#define OS_INT_MAX_PRIORITY              (1U) /* Used for Os_SuspendInterrupt */
#endif

#define Os_Halt()                        asm("wfi");

/*
 * Memory Protection
 */

/* Macro to define number of memory region */
#define OS_MPU_RGD_COUNT     8u

/* Macro to define supervisor's access right for read,write,execute */
#define OS_MPU_SM_RWX        (0 << 3)

/* Macro to define supervisor's access right for read,execute */
#define OS_MPU_SM_RX         (1 << 3)

/* Macro to define supervisor's access right for read,write */
#define OS_MPU_SM_RW         (2 << 3)

/* Macro to define supervisor's same access right with user */
#define OS_MPU_SM_USER       (3 << 3)

/* Macro to define user's no access right */
#define OS_MPU_UM_NOACCESS   0

/* Macro to define user's access right for execute */
#define OS_MPU_UM_X          1

/* Macro to define user's access right for write */
#define OS_MPU_UM_W          2

/* Macro to define user's access right for read */
#define OS_MPU_UM_R          4

/* Macro to define user's access right for execute */
#define OS_MPU_UM_XO         OS_MPU_UM_X

/* Macro to define user's access right for write */
#define OS_MPU_UM_WO         OS_MPU_UM_W

/* Macro to define user's access right for read */
#define OS_MPU_UM_RO         OS_MPU_UM_R

/* Macro to define user's access right for execute */
#define OS_MPU_UM_RX         OS_MPU_UM_R | OS_MPU_UM_X

/* Macro to define user's access right for read,write */
#define OS_MPU_UM_RW         OS_MPU_UM_R | OS_MPU_UM_W

/* Macro to define user's access right for read,write,execute */
#define OS_MPU_UM_RWX        OS_MPU_UM_R | OS_MPU_UM_W | OS_MPU_UM_X

/* Macro to define mask of supervisor and user's access right */
#define OS_MPU_M0_MASK       0x1Fu

#define OS_MPU_CESR_ERR_MASK 0xF8000000u

/* polyspace-begin MISRA-C:8.12 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
extern CONSTP2CONST(void, AUTOMATIC, OS_CONST) Os_GaaSyscallTable[];

#define OS_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Tdd_Os_HardwareCounter, OS_VAR) Os_GaaHardwareCounter[];
#define OS_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#if (OS_MEMORY_PROTECTION == STD_ON)
#define OS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Tdd_Os_MemoryBlock, OS_CONST) Os_GaaStaticMemBlock[];
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /*#if (OS_MEMORY_PROTECTION == STD_ON)*/
/* polyspace-end MISRA-C:8.12 */

#define OS_START_SEC_CONST_32
#include "MemMap.h"
extern CONST(uint32, OS_CONST) Os_User_Stack_Size;
#define OS_STOP_SEC_CONST_32
#include "MemMap.h"

#if (OS_APPLICATION == STD_OFF)
#define OS_START_SEC_STACK_CORE0_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* polyspace<MISRA-C3:8.11:Not a defect:Justify with annotations> for array with external linkage , size would come from configuration files hence not specified explicitly */
extern VAR(Os_StackType, OS_VAR) Os_GaaRamUserStack[];
#define OS_STOP_SEC_STACK_CORE0_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* #if (OS_APPLICATION == STD_OFF) */

/***************************************************************************//**
 * Function Name        : OS_INFINITELOOP
 *
 * Service ID           : NA
 *
 * Description          : Inline function to loop infinitely
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * return               : void
 *
 * pre                  : StartOS() function should be called
 *
 * remarks              : Global Variable(s)     :
 *                        None
 *                        Function(s) invoked    :
 *                        None
 *
 * {Ref: SWR_OS_CYTXXX_005}
 *
 * @ingroup               OS_CYTXXX_ESDD_003
 ******************************************************************************/
static inline FUNC(void, OS_CODE) OS_INFINITELOOP(void)
{
  /* polyspace<RTE : NTL :Not a defect:Justify with annotations> Infinite loop is intended instruction for failed init. */
	while(1)
	{
	}
}

#endif /* End of ifndef OS_PORTTYPES_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-end MISRA-C3:D4.8 */
/* polyspace:end<MISRA-C3:2.4:Not a defect:Justify with annotations> Tags may be used for cross reference */
/* polyspace:end<MISRA-C3:D4.9:Not a defect:Justify with annotations> Function like macro is used to improve performance  */
/* polyspace:end<MISRA-C3:8.5:Not a defect:Justify with annotations> Redundant declaration for generated code */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
