/*******************************************************************************
**                                                                            **
**  (C) 2018 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Hsm_Spc58x.h                                                  **
**                                                                            **
**  TARGET    : SPC58x HSM                                                    **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : This file contains the register and bit field definitions for **
**              the HSM module in the SPC58x                                  **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     24-May-2018   Sinil        Initial version                       **
*******************************************************************************/

#ifndef HSM_REGSPC58X_H
#define HSM_REGSPC58X_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Unions & Structures                                   **
*******************************************************************************/
/* MSB first */
#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
/**
 * Module: HSMHostIF
 */
struct STag_HSMHostIF
{
  /* HSMHostIF_base + 0x00 */
  union
  {
    uint32 R;
    struct
    {
      uint32 FLAG31:1;
      uint32 FLAG30:1;
      uint32 FLAG29:1;
      uint32 FLAG28:1;
      uint32 FLAG27:1;
      uint32 FLAG26:1;
      uint32 FLAG25:1;
      uint32 FLAG24:1;
      uint32 FLAG23:1;
      uint32 FLAG22:1;
      uint32 FLAG21:1;
      uint32 FLAG20:1;
      uint32 FLAG19:1;
      uint32 FLAG18:1;
      uint32 FLAG17:1;
      uint32 FLAG16:1;
      uint32 FLAG15:1;
      uint32 FLAG14:1;
      uint32 FLAG13:1;
      uint32 FLAG12:1;
      uint32 FLAG11:1;
      uint32 FLAG10:1;
      uint32 FLAG9:1;
      uint32 FLAG8:1;
      uint32 FLAG7:1;
      uint32 FLAG6:1;
      uint32 FLAG5:1;
      uint32 FLAG4:1;
      uint32 FLAG3:1;
      uint32 FLAG2:1;
      uint32 FLAG1:1;
      uint32 FLAG0:1;
    } B;
  } HSM2HTF;

  /* HSMHostIF_base + 0x04 */
  union
  {
    uint32 R;
    struct
    {
      uint32 IE31:1;
      uint32 IE30:1;
      uint32 IE29:1;
      uint32 IE28:1;
      uint32 IE27:1;
      uint32 IE26:1;
      uint32 IE25:1;
      uint32 IE24:1;
      uint32 IE23:1;
      uint32 IE22:1;
      uint32 IE21:1;
      uint32 IE20:1;
      uint32 IE19:1;
      uint32 IE18:1;
      uint32 IE17:1;
      uint32 IE16:1;
      uint32 IE15:1;
      uint32 IE14:1;
      uint32 IE13:1;
      uint32 IE12:1;
      uint32 IE11:1;
      uint32 IE10:1;
      uint32 IE9:1;
      uint32 IE8:1;
      uint32 IE7:1;
      uint32 IE6:1;
      uint32 IE5:1;
      uint32 IE4:1;
      uint32 IE3:1;
      uint32 IE2:1;
      uint32 IE1:1;
      uint32 IE0:1;
    } B;
  } HSM2HTIE;

  /* HSMHostIF_base + 0x08 */
  union
  {
    uint32 R;
    struct
    {
      uint32 FLAG31:1;
      uint32 FLAG30:1;
      uint32 FLAG29:1;
      uint32 FLAG28:1;
      uint32 FLAG27:1;
      uint32 FLAG26:1;
      uint32 FLAG25:1;
      uint32 FLAG24:1;
      uint32 FLAG23:1;
      uint32 FLAG22:1;
      uint32 FLAG21:1;
      uint32 FLAG20:1;
      uint32 FLAG19:1;
      uint32 FLAG18:1;
      uint32 FLAG17:1;
      uint32 FLAG16:1;
      uint32 FLAG15:1;
      uint32 FLAG14:1;
      uint32 FLAG13:1;
      uint32 FLAG12:1;
      uint32 FLAG11:1;
      uint32 FLAG10:1;
      uint32 FLAG9:1;
      uint32 FLAG8:1;
      uint32 FLAG7:1;
      uint32 FLAG6:1;
      uint32 FLAG5:1;
      uint32 FLAG4:1;
      uint32 FLAG3:1;
      uint32 FLAG2:1;
      uint32 FLAG1:1;
      uint32 FLAG0:1;
    } B;
  } HT2HSMF;

  /* HSMHostIF_base + 0x0C */
  union
  {
    uint32 R;
    struct
    {
      uint32 IE31:1;
      uint32 IE30:1;
      uint32 IE29:1;
      uint32 IE28:1;
      uint32 IE27:1;
      uint32 IE26:1;
      uint32 IE25:1;
      uint32 IE24:1;
      uint32 IE23:1;
      uint32 IE22:1;
      uint32 IE21:1;
      uint32 IE20:1;
      uint32 IE19:1;
      uint32 IE18:1;
      uint32 IE17:1;
      uint32 IE16:1;
      uint32 IE15:1;
      uint32 IE14:1;
      uint32 IE13:1;
      uint32 IE12:1;
      uint32 IE11:1;
      uint32 IE10:1;
      uint32 IE9:1;
      uint32 IE8:1;
      uint32 IE7:1;
      uint32 IE6:1;
      uint32 IE5:1;
      uint32 IE4:1;
      uint32 IE3:1;
      uint32 IE2:1;
      uint32 IE1:1;
      uint32 IE0:1;
    } B;
  } HT2HSMIE;

  /* HSMHostIF_base + 0x10 */
  union
  {
    uint32 R;
    struct
    {
      uint32 STATUS31:1;
      uint32 STATUS30:1;
      uint32 STATUS29:1;
      uint32 STATUS28:1;
      uint32 STATUS27:1;
      uint32 STATUS26:1;
      uint32 STATUS25:1;
      uint32 STATUS24:1;
      uint32 STATUS23:1;
      uint32 STATUS22:1;
      uint32 STATUS21:1;
      uint32 STATUS20:1;
      uint32 STATUS19:1;
      uint32 STATUS18:1;
      uint32 STATUS17:1;
      uint32 STATUS16:1;
      uint32 STATUS15:1;
      uint32 STATUS14:1;
      uint32 STATUS13:1;
      uint32 STATUS12:1;
      uint32 STATUS11:1;
      uint32 STATUS10:1;
      uint32 STATUS9:1;
      uint32 STATUS8:1;
      uint32 STATUS7:1;
      uint32 STATUS6:1;
      uint32 STATUS5:1;
      uint32 STATUS4:1;
      uint32 STATUS3:1;
      uint32 STATUS2:1;
      uint32 STATUS1:1;
      uint32 STATUS0:1;
    } B;
  } HSM2HTS;

  /* HSMHostIF_base + 0x14 */
  union
  {
    uint32 R;
    struct
    {
      uint32 STATUS31:1;
      uint32 STATUS30:1;
      uint32 STATUS29:1;
      uint32 STATUS28:1;
      uint32 STATUS27:1;
      uint32 STATUS26:1;
      uint32 STATUS25:1;
      uint32 STATUS24:1;
      uint32 STATUS23:1;
      uint32 STATUS22:1;
      uint32 STATUS21:1;
      uint32 STATUS20:1;
      uint32 STATUS19:1;
      uint32 STATUS18:1;
      uint32 STATUS17:1;
      uint32 STATUS16:1;
      uint32 STATUS15:1;
      uint32 STATUS14:1;
      uint32 STATUS13:1;
      uint32 STATUS12:1;
      uint32 STATUS11:1;
      uint32 STATUS10:1;
      uint32 STATUS9:1;
      uint32 STATUS8:1;
      uint32 STATUS7:1;
      uint32 STATUS6:1;
      uint32 STATUS5:1;
      uint32 STATUS4:1;
      uint32 STATUS3:1;
      uint32 STATUS2:1;
      uint32 STATUS1:1;
      uint32 STATUS0:1;
    } B;
  } HT2HSMS;
} HSMHostIF;

union UTag_SEMA4_GATE
{
  uint8 R;
  struct
  {
    uint8 unused:4;
    uint8 GTFSM:4;
  } B;
} SEMA4_GATE;
#else
#error "LSB first not supported"
#endif

/*******************************************************************************
**                                 Defines                                    **
*******************************************************************************/
#define HSM_SPC58X_SEMA_HOST_CORE                       (2U)
#define HSM_SPC58X_SEMA_HSM_CORE                        (14U)

#define HSM_SEND_CMD_SEMA_ID                            (13U)
#define HSM_RECV_SYNC_SEMA_ID                           (14U)
#define HSM_RECV_ASYNC_SEMA_ID                          (15U)

/* HSM2HTF */
#define HSM_HSM2HT_TRAP_ERROR_MASK                      (0x40000000UL)
#define HSM_HSM2HT_KS_WARNING_MASK                      (0x20000000UL)
#define HSM_HSM2HT_BOOT_DONE_MASK                       (0x00000001UL)

/* HT2HSMF */
#define HSM_HT2HSM_SHARED_MEM_ADDR_MASK                 (0x80000000UL)

/* TRAP Event */
#define HSM_TRAP_STARTUP_FAILED                         (0x01000000UL)
#define HSM_TRAP_WRONG_SILICON_VERSION                  (0x02000000UL)
#define HSM_TRAP_UNRECOVERABLE_FLASH_ERR                (0x03000000UL)
#define HSM_TRAP_NO_SHARED_MEM_ERR                      (0x04000000UL)
#define HSM_TRAP_IVOR0_INTERRUPT                        (0x10000000UL)
#define HSM_TRAP_IVOR1_INTERRUPT                        (0x11000000UL)
#define HSM_TRAP_IVOR2_INTERRUPT                        (0x1200000UL)
#define HSM_TRAP_IVOR3_INTERRUPT                        (0x13000000UL)
#define HSM_TRAP_IVOR5_INTERRUPT                        (0x15000000UL)
#define HSM_TRAP_IVOR6_INTERRUPT                        (0x16000000UL)
#define HSM_TRAP_IVOR7_INTERRUPT                        (0x17000000UL)
#define HSM_TRAP_IVOR8_INTERRUPT                        (0x18000000UL)
#define HSM_TRAP_IVOR9_INTERRUPT                        (0x19000000UL)
#define HSM_TRAP_IVOR10_INTERRUPT                       (0x1A000000UL)
#define HSM_TRAP_IVOR11_INTERRUPT                       (0x1B000000UL)
#define HSM_TRAP_IVOR12_INTERRUPT                       (0x1C000000UL)
#define HSM_TRAP_IVOR13_INTERRUPT                       (0x1D000000UL)
#define HSM_TRAP_IVOR14_INTERRUPT                       (0x1E000000UL)
#define HSM_TRAP_IVOR15_INTERRUPT                       (0x1F000000UL)

/*******************************************************************************
**                               Global Data                                  **
*******************************************************************************/
#define HSM_HOST_IF          (*((volatile struct STag_HSMHostIF*)0xF7F30000UL))
#define SEMA4_GATE(x)        (*((volatile union UTag_SEMA4_GATE*)(0xF403C000UL + (x))))

#endif  /* HSM_REGSPC58X_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
