/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Sec_SecurityAccess.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file for Security Access check                         **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef SEC_SECURITYACCESS_H
#define SEC_SECURITYACCESS_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Btl.h"
#include "Dcm.h"
#include "Dcm_Types.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
/* Instance id */
#define SA_INSTANCE_ID                                                ((uint8)0)
/*******************************************************************************
**                     Callback Notifications                                 **
*******************************************************************************/

/* Service Id of Secure flash mainfunction */
#define SA_MAIN_FUNCTION_SID                                       ((uint8)0x00)
/*******************************************************************************
**                      DET ERROR CODES                                       **
*******************************************************************************/
/* Verify CERT signagure Failed */
#define SA_E_VERIFYCERTSIG                                         ((uint8)0x00)

/* Check CERT expire Failed */
#define SA_E_CHECKCERTEXPIRE                                       ((uint8)0x01)

/* Verity CRL signature Failed */
#define SA_E_VERIFYCRLSIG                                          ((uint8)0x02)

/* Check CRL expire Failed */
#define SA_E_CHECKCRLEXPIRE                                        ((uint8)0x03)

/* Check validity cert Failed */
#define SA_E_CHECKVALIDITYCERT                                     ((uint8)0x04)

/* Get Seed Failed */
#define SA_E_GETSEED                                               ((uint8)0x05)

/* Compare Key Failed */
#define SA_E_COMPAREKEY                                            ((uint8)0x06)

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define BTL_START_SEC_COMMON_CODE
#include "Btl_MemMap.h"

extern void Sec_SecurityAccessInit(void);

extern Std_ReturnType Sec_SecurityAccessGetSeed(
  uint8 Lu8_SecLvl,
  const uint8* Lpu8_ReqData,
  uint8* Lpu8_ResData,
  uint32* Lpu32_SeedLength);

extern Std_ReturnType Sec_SecurityAccessCompareKey(
  uint8 Lu8_SecLvl,
  const uint8* Lpu8_ReqData,
  uint32* Lpu32_KeyLength);

extern Std_ReturnType Sec_SecurityAccessGetStatus(
  uint32* Lpu32_Length,
  Dcm_NegativeResponseCodeType* Lpdt_ErrorCode);

extern void Sec_SecurityAccessMainFunction(void);

#define BTL_STOP_SEC_COMMON_CODE
#include "Btl_MemMap.h"

#endif /* SEC_SECURITYACCESS_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
