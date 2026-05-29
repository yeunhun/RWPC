#ifndef __ARM_IS
#define __ARM_IS

#ifdef __ARM_DSP
#include <arm9e_ghs.h>
#endif

#if defined(__CORE_ARM11__) || defined(__THUMB2_AWARE)
#include <arm11_ghs.h>
#endif

#ifdef __VFP
#include <vfp_ghs.h>

#if defined(__CORE_CORTEXA__) || defined(__CORE_PJ4__)
#include <arm_neon.h>
#endif
#endif

#ifdef __XScale
#include <xscale_ghs.h>
#endif

#if defined(__THUMB2_AWARE) && \
    !(defined(__CORE_ARM11T2__) || defined(__CORE_PJ4V6__))
#include <armv7_ghs.h>
#endif

#if defined(__CORE_ARMV6M__) || defined(__CORE_CORTEXM3__) || \
    defined(__CORE_CORTEXM4__) || defined(__CORE_CORTEXM7__)
#include <armv7m_ghs.h>
#endif


#ifdef __ghs__
#pragma ghs startnomisra
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__ARMPURESAFE)
#if defined(__ATTRIBUTES) 
#define __ARMPURESAFE __attribute__((const,pure))
#else
#define __ARMPURESAFE
#endif
#endif


/* CLZ32 : Count leading zeros */
unsigned int __CLZ32(unsigned int Rm) __ARMPURESAFE;

#if !defined(__CORE_ARMV6M__)
/* UMULL, SMULL : High 32 bits of 32x32->64 bit multiply */
unsigned int __MULUH(unsigned int Rm, unsigned int Rs) __ARMPURESAFE; /* unsigned */
  signed int __MULSH(  signed int Rm,   signed int Rs) __ARMPURESAFE; /* signed */

#if defined(__LLONG_BIT)
/* UMULL, SMULL : Full 64 bits of 32x32->64 bit multiply */
unsigned long long __UMULL(unsigned int Rm, unsigned int Rs) __ARMPURESAFE; /* unsigned */
  signed long long __SMULL(  signed int Rm,   signed int Rs) __ARMPURESAFE; /* signed */

/* SMLAL, UMLAL : 32x32->64 multiply with 64 bit accumulate */
  signed long long __SMLAL(  signed long long Rd,   signed int Rm,   signed int Rs) __ARMPURESAFE;
unsigned long long __UMLAL(unsigned long long Rd, unsigned int Rm, unsigned int Rs) __ARMPURESAFE;

/* __MULUH64 : High 64 bits of 64x64->128 bit multiply sequence using UMULL */
unsigned long long __MULUH64(unsigned long long Rm, unsigned long long Rs) __ARMPURESAFE;
#endif
#endif

/* MRS, MSR : retrieve and set the contents of the cpsr status register */
unsigned int __GETSR(void);
void __SETSR(unsigned int Rm);

/* MRS, MSR : retrieve and set the contents of the spsr status register */
unsigned int __GETSSR(void);
void __SETSSR(unsigned int Rm);

/* __DIR : Disable maskable interrupts, and return a key for use with __RIR */
unsigned int __DIR(void);

/* __EIR : Enable maskable interrupts, and return a key for use with __RIR */
unsigned int __EIR(void);

/* __RIR : Restore interrupts to their state prior to a call to __DIR or __EIR */
void __RIR(unsigned int);

/* __DI : Disable maskable interrupts */
void __DI(void);

/* __EI : Enable maskable interrupts */
void __EI(void);

/* Retrieve address for return from function from link register or frame.
   The level parameter is ignored. */
void * __builtin_return_address(unsigned int level);

/* __NOP : Insert No Operation instruction, which does nothing. */
void __NOP(void);

#ifdef __EDG__

/* Supervisor Call, causes an SVC exception */
void __SVC(__ghs_c_int__ code);
void __SWI(__ghs_c_int__ code);

/* BKPT Breakpoint Instruction */
void __BKPT(__ghs_c_int__ option);

/* MRC{2} : Move to ARM Register from Coprocessor. */
unsigned int __MRC(__ghs_c_int__ coproc, __ghs_c_int__ opcode1,
    __ghs_c_int__ CRn, __ghs_c_int__ CRm, __ghs_c_int__ opcode2);
unsigned int __MRC2(__ghs_c_int__ coproc, __ghs_c_int__ opcode1,
    __ghs_c_int__ CRn, __ghs_c_int__ CRm, __ghs_c_int__ opcode2);

/* MCR{2} : Move to Coprocessor from ARM Register. */
void __MCR(__ghs_c_int__ coproc, __ghs_c_int__ opcode1, unsigned int Rd,
    __ghs_c_int__ CRn, __ghs_c_int__ CRm, __ghs_c_int__ opcode2);
void __MCR2(__ghs_c_int__ coproc, __ghs_c_int__ opcode1, unsigned int Rd,
    __ghs_c_int__ CRn, __ghs_c_int__ CRm, __ghs_c_int__ opcode2);

/* CDP{2} : Coprocessor Data Processing. */
void __CDP(__ghs_c_int__ coproc, __ghs_c_int__ opcode1, __ghs_c_int__ CRd,
    __ghs_c_int__ CRn, __ghs_c_int__ CRm, __ghs_c_int__ opcode2);
void __CDP2(__ghs_c_int__ coproc, __ghs_c_int__ opcode1, __ghs_c_int__ CRd,
    __ghs_c_int__ CRn, __ghs_c_int__ CRm, __ghs_c_int__ opcode2);

/* LDC{2}{L} : Coprocessor Load. */
void __LDC(__ghs_c_int__ coproc, __ghs_c_int__ CRd, void *addr);
void __LDCL(__ghs_c_int__ coproc, __ghs_c_int__ CRd, void *addr);
void __LDC2(__ghs_c_int__ coproc, __ghs_c_int__ CRd, void *addr);
void __LDC2L(__ghs_c_int__ coproc, __ghs_c_int__ CRd, void *addr);

/* STC{2}{L} : Coprocessor Store. */
void __STC(__ghs_c_int__ coproc, __ghs_c_int__ CRd, void *addr);
void __STCL(__ghs_c_int__ coproc, __ghs_c_int__ CRd, void *addr);
void __STC2(__ghs_c_int__ coproc, __ghs_c_int__ CRd, void *addr);
void __STC2L(__ghs_c_int__ coproc, __ghs_c_int__ CRd, void *addr);

#if defined(__LLONG_BIT)
/* MRRC{2} : Move from Coprocessor to Two ARM Registers (v5). */
unsigned long long __MRRC(__ghs_c_int__ coproc, __ghs_c_int__ opcode,
    __ghs_c_int__ CRm);
unsigned long long __MRRC2(__ghs_c_int__ coproc, __ghs_c_int__ opcode,
    __ghs_c_int__ CRm);

/* MCRR{2} : Move Two ARM Registers to Coprocessor (v5). */
void __MCRR(__ghs_c_int__ coproc, __ghs_c_int__ opcode,
    unsigned long long Rd, __ghs_c_int__ CRm);
void __MCRR2(__ghs_c_int__ coproc, __ghs_c_int__ opcode,
    unsigned long long Rd, __ghs_c_int__ CRm);
#endif

/* Preload Data */
void __PLD(void *Rn);

#include <stddef.h>    /* for size_t */

/* stackccv/sortedstackccv: returns a pointer to the first location used for
 * the parameters of the current function */
void *__ghs_start_param(void);

/* stackccv/sortedstackccv: returns the size of the parameter space used by
 * the current function */
size_t __ghs_param_size(void);

#endif /* def __EDG__ */

#ifdef __cplusplus
}
#endif

#ifdef __ghs__
#pragma ghs endnomisra
#endif

#endif
