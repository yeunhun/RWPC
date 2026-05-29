/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Dummy_HaeASK.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Dummy HAE library                                             **
**                                                                            **
**  PURPOSE   : Header file for dummy code                                    **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef DUMMY_HAEASK_H
#define DUMMY_HAEASK_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* HKMC_ASK_Server.h */
#if !defined(BYTE_defined)
	/** 8 bit unsigned integer. */
  typedef unsigned char BYTE;
	#define BYTE_defined
#endif
  
#ifndef uint8_defined
  /** 8 bit unsigned integer. */
  typedef unsigned char uint8;
	#define uint8_defined
#endif

#if !defined(uint16_defined)
	/** 16 bit unsigned integer. */
  typedef unsigned short uint16;
	#define uint16_defined
#endif

/*******************************************************************************
**                                Data Types                                  **
*******************************************************************************/

/*******************************************************************************
**                               Enumerations                                 **
*******************************************************************************/
/* HKMC_ASK_Server.h */
typedef enum{
  SEEDKEY_SUCCESS = 0,
  SEEDKEY_FAIL = 1,
} SEEDKEY_RT;

/*******************************************************************************
**                                Structures                                  **
*******************************************************************************/
typedef struct {
  uint16 vendorID;
  uint16 moduleID;
  uint8 majorVersion;
  uint8 minorVersion;
  uint8 patchVersion;
} VERSION_INFO;

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
extern SEEDKEY_RT ASK_KeyGenerate(const BYTE *seed_buffer_8byte, BYTE *key_buffer_8byte);

extern SEEDKEY_RT ASK_Rand8ByteGenerate(BYTE *seed_buffer_8byte);

extern void ASK_RandInit(unsigned long rand_seed);

extern void vGetVersionInfo(VERSION_INFO *pVersionInfo);

#endif /* DUMMY_HAEASK_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
