/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Sec_SwVersionCheck.c                                          **
**                                                                            **
**  TARGET    : ALL													                                  **
**                                                                            **
**  PRODUCT   : Cdd_FBL                                                       **
**                                                                            **
**  PURPOSE   : SW Version Check                                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.23.1.0  06-Jun-2022   JSCHOI       Redmine #36032                        **
** 1.23.0    27-Dec-2021   JH Lim       R40-Redmine #31776                    **
*******************************************************************************/

#ifndef SEC_SOFTWAREVERSIONCHECKER_H
#define SEC_SOFTWAREVERSIONCHECKER_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Fbl_Cfg.h"
#include "Fbl_Config.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* The following macros are used to specify job type */
typedef enum {
  FBL_BLK_INIT = 0,
  /* State 1 : Header and Trailer have no value */
  FBL_BLK_VIRGIN,
  /* State 2 : Header is Invalid, Trailer is Valid */
  FBL_BLK_HEADER_INVALID,
  /* State 3 : Header's current version is higher than Trailer */
  FBL_BLK_HEADER_UPDATED,
  /* State 4 : Both Current version are same */
  FBL_BLK_NORMAL,
  /* State 5 : Header is valid, Trailer is Invalid */
  FBL_BLK_TRAILER_INVALID,    
  /* State 6 : Trailer version is more latest then Header */
  FBL_BLK_TRAILER_UPDATED, 
} Fbl_BlkStateType; 

typedef enum {
  /* State 0 : INIT State */
  FBL_VERSION_INIT = 0,
  /* State 1 : Version OK */
  FBL_VERSION_OK,
  /* State 2 : Version NOT OK */
  FBL_VERSION_NOT_OK,
} Fbl_VerStateType;

typedef struct
{
  uint32 magicNumber;
  uint32 currentVersion;
  uint32 previousVersion;
} Fbl_BlkInfo;

typedef struct
{
  Fbl_BlkInfo blkInfo;
  uint16 blkCrcInit;
  uint16 blkCrc16;
} Fbl_BlkCrcInfo;

typedef struct
{
  /* [1] Calculate offset of Address
   *
   *   +----------------+-------------------+---------------+--------------------+------+-----+-----------+--------------+
   *   | magicNumber(4) | currentVersion(4) | reserved(248) | previousVersion(4) | crcInit(2) | crcVal(2) | reserved(248)|
   *   +----------------+-------------------+---------------+--------------------+------+-----+-----------+--------------+
   *   |<------------0x100 (App Data)---------------------->|<-----------------------0x100 (FBL Note)-------------------->|
   */
  /* Magic Number 4-byte*/
  uint32 magicNumber;
  /* Current Version 4-byte */
  uint32 currentVersion;
  /* Reserved for write unit 248-byte */
  uint8 reserved_1[248];
  /* Magic Number 4-byte*/
  uint32 previousVersion;
  /* crcInit 2-byte */
  uint16 crcInit;
  /* crcVal 2-byte */
  uint16 crcVal;
  /* Reserved for write unit 248-byte */
  uint8 reserved_2[248]; 
} Fbl_BlkFlashInfo;

/* Instance id */
#define SVC_INSTANCE_ID                                               ((uint8)0)

#define SVC_MAIN_FUNCTION_SID                                         ((uint8)0)

#define FBL_BLK_MAGIC_NUMBER_HEADER                                (0x6D6F6269U)

#define FBL_BLK_MAGIC_NUMBER_TRAILER                               (0x6C67656EU)

#define FBL_BLK_SWVERSION_INIT                                     (0x00000000U)

#define FBL_BLK_SWVERSION_MAX                                      (0xFFFFFFFFU)

#define FBL_BLK_CRC_TARGET_LENGTH                                         (0xCU)

#define FBL_BLK_HALF_LENGTH                                             (0x100U)

#define FBL_BLK_TOTAL_LENGTH                                            (0x200U)
/*******************************************************************************
**                      DET ERROR CODES                                       **
*******************************************************************************/
/* Version check Index Failed */
#define SVC_E_VCINDEX                                              ((uint8)0x00)

/* Detect the Flash Downgrade  */
#define SVC_E_DETECT_DOWNGRADE                                     ((uint8)0x01)

/* Detect the Flash Downgrade  */
#define SVC_E_BLK_VERIFY_FAIL                                      ((uint8)0x02)

/* Detect the Flash Downgrade  */
#define SVC_E_BLK_RECOVERY_FAIL                                    ((uint8)0x03)

/* Detect the Flash Downgrade  */
#define SVC_E_BLK_UPDATE_FAIL                                      ((uint8)0x04)

/* Detect the Flash Downgrade  */
#define SVC_E_BLK_NOT_FOUND                                        ((uint8)0x05)


/*******************************************************************************
**                      DET ERROR CODES                                       **
*******************************************************************************/
#define BTL_START_SEC_VAR_INIT
#include "Btl_MemMap.h"

extern uint32 Fbl_Gu32_PreviousVersion;

extern uint32 Fbl_Gu32_CurrentVersion;

extern uint32 Fbl_Gu32_NewVersion;

extern Fbl_VerStateType Fbl_Gbl_VersionStatus;

extern uint32 Fbl_Gu32_EraseReservedStartAddress;

extern uint32 Fbl_Gu32_EraseReservedLength;

extern uint32 Fbl_Gu32_EraseStartAddress;

extern uint32 Fbl_Gu32_EraseLength;

extern Fbl_BlkStateType Fbl_Gen_BlkState;

#define BTL_STOP_SEC_VAR_INIT
#include "Btl_MemMap.h"
/*******************************************************************************
**                        Global Function Definition                          **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void Sec_SvcInit(void);

extern Std_ReturnType Sec_SvcGetVersion(const Fbl_BlkFlashInfo* pHeader, \
  const Fbl_BlkFlashInfo* pTrailer, uint32* pCurrentVersion, uint32* pPreviousVersion);

extern Std_ReturnType Sec_SvcUpdateBlk(const Fbl_BlkFlashInfo* pTarget, \
  uint32 previousVersion);
  
extern Std_ReturnType Sec_SvcRecoveryBlk(const Fbl_BlkFlashInfo* pTarget, \
  Fbl_BlkCrcInfo* pSource);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* SEC_SWCHECK_H */
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
