/*******************************************************************************
**                                                                            **
**  (C) 2018 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Hsm_F1km.h                                                    **
**                                                                            **
**  TARGET    : RH850 F1KM HSM                                                **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : This file contains the register and bit field definitions for **
**              the HSM module in the F1KM                                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     24-May-2018   Sinil        Initial version                       **
*******************************************************************************/

#ifndef HSM_F1KM_H
#define HSM_F1KM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Unions & Structures                                   **
*******************************************************************************/
/* LSB first */
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
/**
 * Module: ICUM_CMDREG
 */
struct STag_ICUM_CMDREG
{
  /* ICUM_CMDREG_base + 0x00 */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICUID:32;
    } B;
  } ICUID;

  /* ICUM_CMDREG_base + 0x04 */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICUVER:32;
    } B;
  } ICUVER;

  uint8 CMDREG_reserved0[8];

  /* ICUM_CMDREG_base + 0x10 */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICU2PES:32;
    } B;
  } ICU2PES;

  /* ICUM_CMDREG_base + 0x14 */
  union
  {
    uint32 R;
    struct
    {
      uint32 PE2ICUS:32;
    } B;
  } PE2ICUS;

  /* ICUM_CMDREG_base + 0x18 */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICUMACT:2;
      uint32:30;
    } B;
  } ACTFLAG;

  uint8 CMDREG_reserved1[4];

  /* ICUM_CMDREG_base + 0x20 */
  union
  {
    uint32 R;
    struct
    {
      uint32 FENTCUPREQ0:1;
      uint32 FENTDUPREQ0:1;
      uint32:30;
    } B;
  } PEFLPRG0REQ;

  uint8 CMDREG_reserved2[4];

  /* ICUM_CMDREG_base + 0x28 */
  union
  {
    uint32 R;
    struct
    {
      uint32 FENTCUPACK0:1;
      uint32 FENTDUPACK0:1;
      uint32 FENTDUPACKA0:1;
      uint32:29;
    } B;
  } PEFLPRG0ACK;

  uint8 CMDREG_reserved3[20];

  /* ICUM_CMDREG_base + 0x40 */
  union
  {
    uint32 R;
    struct
    {
      uint32 PE2ICUF:32;
    } B;
  } PE2ICUF;

  /* ICUM_CMDREG_base + 0x44 */
  union
  {
    uint32 R;
    struct
    {
      uint32 PE2ICUFS:32;
    } B;
  } PE2ICUFS;

  /* ICUM_CMDREG_base + 0x48 */
  union
  {
    uint32 R;
    struct
    {
      uint32 PE2ICUFC:32;
    } B;
  } PE2ICUFC;

  /* ICUM_CMDREG_base + 0x4C */
  union
  {
    uint32 R;
    struct
    {
      uint32 PE2ICUIE:32;
    } B;
  } PE2ICUIE;

  /* ICUM_CMDREG_base + 0x50 */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICU2PEF:32;
    } B;
  } ICU2PEF;

  /* ICUM_CMDREG_base + 0x54 */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICU2PEFS:32;
    } B;
  } ICU2PEFS;

  /* ICUM_CMDREG_base + 0x58 */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICU2PEFC:32;
    } B;
  } ICU2PEFC;

  /* ICUM_CMDREG_base + 0x5C */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICU2PEIE:32;
    } B;
  } ICU2PEIE;

  uint8 CMDREG_reserved4[16];

  /* ICUM_CMDREG_base + 0x70 */
  union
  {
    uint32 R;
    struct
    {
      uint32 PE2ICUSF0:1;
      uint32:31;
    } B;
  } PE2ICUSF;

  /* ICUM_CMDREG_base + 0x74 */
  union
  {
    uint32 R;
    struct
    {
      uint32 PE2ICUSFS0:1;
      uint32:31;
    } B;
  } PE2ICUSFS;

  /* ICUM_CMDREG_base + 0x78 */
  union
  {
    uint32 R;
    struct
    {
      uint32 PE2ICUSFC0:1;
      uint32:31;
    } B;
  } PE2ICUSFC;

  /* ICUM_CMDREG_base + 0x7C */
  union
  {
    uint32 R;
    struct
    {
      uint32 PE2ICUSIE0:1;
      uint32:31;
    } B;
  } PE2ICUSIE;

  /* ICUM_CMDREG_base + 0x80 */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICU2PESF0:1;
      uint32:31;
    } B;
  } ICU2PESF;

  /* ICUM_CMDREG_base + 0x84 */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICU2PESFS0:1;
      uint32:31;
    } B;
  } ICU2PESFS;

  /* ICUM_CMDREG_base + 0x88 */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICU2PESFC0:1;
      uint32:31;
    } B;
  } ICU2PESFC;

  /* ICUM_CMDREG_base + 0x8C */
  union
  {
    uint32 R;
    struct
    {
      uint32 ICU2PESIE0:1;
      uint32:31;
    } B;
  } ICU2PESIE;

  /* ICUM_CMDREG_base + 0x90 */
  union
  {
    uint32 R;
    struct
    {
      uint32 PESSEL:4;
      uint32:28;
    } B;
  } ICU2PESIS;

  uint8 CMDREG_reserved5[12];

  /* ICUM_CMDREG_base + 0xA0 */
  union
  {
    uint32 R;
    struct
    {
      uint32 SEMAPE1FL:30;
      uint32 AUTH:2;
    } B;
  } SEMAPE1;

  /* ICUM_CMDREG_base + 0xA4 */
  union
  {
    uint32 R;
    struct
    {
      uint32 SEMAPE2FL:30;
      uint32 AUTH:2;
    } B;
  } SEMAPE2;
};

/**
 * Module: ICUM_PROT0
 */
struct STag_ICUM_PROT0
{
  /* ICUM_PROT0_base + 0x00 */
  union
  {
    uint32 R;
    struct
    {
      uint32 PCMD:8;
      uint32:24;
    } B;
  } CMD;

  /* ICUM_PROT0_base + 0x04 */
  union
  {
    uint32 R;
    struct
    {
      uint32 PROTSERR:1;
      uint32:31;
    } B;
  } PS;
};
#else
#error "MSB first not supported"
#endif

/*******************************************************************************
**                                 Defines                                    **
*******************************************************************************/
#define HSM_F1KM_SEMA_IDLE                              (0U)
#define HSM_F1KM_SEMA_PE_CORE                           (2U)
#define HSM_F1KM_SEMA_ICUP_CORE                         (3U)

#define HSM_SEND_CMD_SEMA_ID                            (13U)
#define HSM_RECV_SYNC_SEMA_ID                           (14U)
#define HSM_RECV_ASYNC_SEMA_ID                          (15U)

#define HSM_PROT_CMD_REG_VAL                            (0xA5U)
#define HSM_PROT_STATUS_OK_VAL                          (1U)
#define HSM_PROT_LOOP_TIMEOUT                           ((uint8)0x32U)

/*******************************************************************************
**                               Global Data                                  **
*******************************************************************************/
/* ICUM_CMDREG */
#define ICUM_CMDREG                                     (*((volatile struct STag_ICUM_CMDREG*)0xFF1F0000UL))

/* ICUM_PROT0 */
#define ICUM_PROT0                                      (*((volatile struct STag_ICUM_PROT0*)0xFFFEE090UL))

#endif  /* HSM_F1KM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
