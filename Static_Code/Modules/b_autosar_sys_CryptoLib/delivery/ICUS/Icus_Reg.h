/*******************************************************************************
**                                                                            **
**  (C) 2017 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Icus_Reg.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for F1K ICUS                                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     16-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

/* polyspace-begin MISRA2012:D4.6,2.3,2.5 [Not a defect:Low] "No Impact of this rule violation" */
/* polyspace-begin MISRA2012:11.4 [Not a defect:Low] "Type casting is checked" */
/* polyspace-begin MISRA2012:19.2 [Not a defect:Low] "Follow AUTOSAR standard rules" */

#ifndef ICUS_REG_H
#define ICUS_REG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/

/*******************************************************************************
**                      Enumerations                                          **
*******************************************************************************/

/*******************************************************************************
**                      Register bits struct                                  **
*******************************************************************************/
typedef struct
{
  unsigned int CMD:16;
  unsigned int KEYID:4;
  unsigned int KEYMD:1;
  unsigned int reserved_27:7;
  unsigned int AIS31EN:1;
  unsigned int reserved_31:3;
} ICUS0ICRCMD_Bits;

typedef struct
{
  unsigned int IDAT:32;
} ICUS0ICRIDAT_Bits;

typedef struct
{
  unsigned int ODAT:32;
} ICUS0ICRODAT_Bits;

typedef struct
{
  unsigned int BUSY:1;
  unsigned int SECURE_BOOT:1;
  unsigned int BOOT_INIT:1;
  unsigned int BOOT_FINISHED:1;
  unsigned int BOOT_OK:1;
  unsigned int RND_INIT:1;
  unsigned int EXT_DEBUGGER:1;
  unsigned int INT_DEBUGGER:1;
  unsigned int reserved_31:24;
} ICUS0ICRSTS_Bits;

typedef struct
{
  unsigned int ERR0:1;
  unsigned int ERR1:1;
  unsigned int ERR2:1;
  unsigned int ERR3:1;
  unsigned int ERR4:1;
  unsigned int ERR5:1;
  unsigned int ERR6:1;
  unsigned int ERR7:1;
  unsigned int ERR8:1;
  unsigned int ERR9:1;
  unsigned int ERR10:1;
  unsigned int ERR11:1;
  unsigned int reserved_31:20;
} ICUS0ICRERR_Bits;

typedef struct
{
  unsigned int TXREQ:1;
  unsigned int RXREQ:1;
  unsigned int reserved_31:30;
} ICUS0ICRSWINT_Bits;

typedef struct
{
  unsigned int ICUEN:1;
  unsigned int reserved_31:31;
} ICUS0ICRICUSTS_Bits;

typedef struct
{
  unsigned int IDATNUM:32;
} ICUS0ICRIDATNUM_Bits;

typedef struct
{
  unsigned int ICRACC:1;
  unsigned int reserved_31:31;
} ICUS0ICRACC_Bits;

typedef struct
{
  unsigned int TXREQCLR:1;
  unsigned int RXREQCLR:1;
  unsigned int reserved_31:30;
} ICUS0ICRSWINTCL_Bits;

typedef struct
{
  unsigned int MALKEY:32;
} ICUS0MALKEY_Bits;

typedef struct
{
  unsigned int MALDAT:32;
} ICUS0MALDAT_Bits;

typedef struct
{
  unsigned int MALMAC:32;
} ICUS0MALMAC_Bits;

typedef struct
{
  unsigned int reserved_0:1;
  unsigned int ECER1F:1;
  unsigned int ECER2F:1;
  unsigned int reserved_8:6;
  unsigned int ECER1C:1;
  unsigned int ECER2C:1;
  unsigned int reserved_31:21;
} ICUS0ECCCTL_Bits;

typedef struct
{
  unsigned int EC1EDIC:1;
  unsigned int reserved_31:31;
} ICUS0ECCERRINT_Bits;

typedef struct
{
  unsigned int ERRCLR:1;
  unsigned int reserved_31:31;
} ICUS0ICRERRCL_Bits;

typedef struct
{
  unsigned int MIN_ML:7;
  unsigned int MIN_ML_NV:1;
  unsigned int reserved_15:8;
  unsigned int NSBF_PSM:1;
  unsigned int reserved_19:3;
  unsigned int BCLR_PSM:1;
  unsigned int reserved_31:11;
} ICUS0MODESTS_Bits;

/*******************************************************************************
**                      Registers                                             **
*******************************************************************************/
typedef union
{
  unsigned int U;
  ICUS0ICRCMD_Bits B;
} ICUS0ICRCMD;

typedef union
{
  unsigned int U;
  ICUS0ICRIDAT_Bits B;
} ICUS0ICRIDAT;

typedef union
{
  unsigned int U;
  ICUS0ICRODAT_Bits B;
} ICUS0ICRODAT;

typedef union
{
  unsigned int U;
  ICUS0ICRSTS_Bits B;
} ICUS0ICRSTS;

typedef union
{
  unsigned int U;
  ICUS0ICRERR_Bits B;
} ICUS0ICRERR;

typedef union
{
  unsigned int U;
  ICUS0ICRSWINT_Bits B;
} ICUS0ICRSWINT;

typedef union
{
  unsigned int U;
  ICUS0ICRICUSTS_Bits B;
} ICUS0ICRICUSTS;

typedef union
{
  unsigned int U;
  ICUS0ICRIDATNUM_Bits B;
} ICUS0ICRIDATNUM;

typedef union
{
  unsigned int U;
  ICUS0ICRACC_Bits B;
} ICUS0ICRACC;

typedef union
{
  unsigned int U;
  ICUS0ICRSWINTCL_Bits B;
} ICUS0ICRSWINTCL;

typedef union
{
  unsigned int U;
  ICUS0MALKEY_Bits B;
} ICUS0MALKEY;

typedef union
{
  unsigned int U;
  ICUS0MALDAT_Bits B;
} ICUS0MALDAT;

typedef union
{
  unsigned int U;
  ICUS0MALMAC_Bits B;
} ICUS0MALMAC;

typedef union
{
  unsigned int U;
  ICUS0ECCCTL_Bits B;
} ICUS0ECCCTL;

typedef union
{
  unsigned int U;
  ICUS0ECCERRINT_Bits B;
} ICUS0ECCERRINT;

typedef union
{
  unsigned int U;
  ICUS0ICRERRCL_Bits B;
} ICUS0ICRERRCL;

typedef union
{
  unsigned int U;
  ICUS0MODESTS_Bits B;
} ICUS0MODESTS;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define ICUS_ICUS0ICRCMD            (*((volatile ICUS0ICRCMD*)    0xFFF60000UL))
#define ICUS_ICUS0ICRIDAT           (*((volatile ICUS0ICRIDAT*)   0xFFF60004UL))
#define ICUS_ICUS0ICRODAT           (*((volatile ICUS0ICRODAT*)   0xFFF60008UL))
#define ICUS_ICUS0ICRSTS            (*((volatile ICUS0ICRSTS*)    0xFFF6000CUL))
#define ICUS_ICUS0ICRERR            (*((volatile ICUS0ICRERR*)    0xFFF60010UL))
#define ICUS_ICUS0ICRSWINT          (*((volatile ICUS0ICRSWINT*)  0xFFF60014UL))
#define ICUS_ICUS0ICRICUSTS         (*((volatile ICUS0ICRICUSTS*) 0xFFF60018UL))
#define ICUS_ICUS0ICRIDATNUM        (*((volatile ICUS0ICRIDATNUM*)0xFFF6001CUL))
#define ICUS_ICUS0ICRACC            (*((volatile ICUS0ICRACC*)    0xFFF60020UL))
#define ICUS_ICUS0ICRSWINTCL        (*((volatile ICUS0ICRSWINTCL*)0xFFF60024UL))
#define ICUS_ICUS0MALKEY0           (*((volatile ICUS0MALKEY*)    0xFFF60090UL))
#define ICUS_ICUS0MALKEY1           (*((volatile ICUS0MALKEY*)    0xFFF60094UL))
#define ICUS_ICUS0MALKEY2           (*((volatile ICUS0MALKEY*)    0xFFF60098UL))
#define ICUS_ICUS0MALKEY3           (*((volatile ICUS0MALKEY*)    0xFFF6009CUL))
#define ICUS_ICUS0MALDAT0           (*((volatile ICUS0MALDAT*)    0xFFF600A0UL))
#define ICUS_ICUS0MALDAT1           (*((volatile ICUS0MALDAT*)    0xFFF600A4UL))
#define ICUS_ICUS0MALDAT2           (*((volatile ICUS0MALDAT*)    0xFFF600A8UL))
#define ICUS_ICUS0MALDAT3           (*((volatile ICUS0MALDAT*)    0xFFF600ACUL))
#define ICUS_ICUS0MALMAC0           (*((volatile ICUS0MALMAC*)    0xFFF600B0UL))
#define ICUS_ICUS0MALMAC1           (*((volatile ICUS0MALMAC*)    0xFFF600B4UL))
#define ICUS_ICUS0MALMAC2           (*((volatile ICUS0MALMAC*)    0xFFF600B8UL))
#define ICUS_ICUS0MALMAC3           (*((volatile ICUS0MALMAC*)    0xFFF600BCUL))
#define ICUS_ICUS0ECCCTL            (*((volatile ICUS0ECCCTL*)    0xFFF600C0UL))
#define ICUS_ICUS0ECCERRINT         (*((volatile ICUS0ECCERRINT*) 0xFFF600C4UL))
#define ICUS_ICUS0ICRERRCL          (*((volatile ICUS0ICRERRCL*)  0xFFF6002CUL))
#define ICUS_ICUS0MODESTS           (*((volatile ICUS0MODESTS*)   0xFFF600E8UL))

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* ICUS_REG_H */

/* polyspace-end MISRA2012:D4.6,2.3,2.5 [Not a defect:Low] "No Impact of this rule violation" */
/* polyspace-end MISRA2012:11.4 [Not a defect:Low] "Type casting is checked" */
/* polyspace-end MISRA2012:19.2 [Not a defect:Low] "Follow AUTOSAR standard rules" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
