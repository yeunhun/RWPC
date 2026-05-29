/*******************************************************************************
**                                                                            **
**  (C) 2017~2018 HYUNDAI AUTRON Co., Ltd.                                    **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Hsm_AutDriver.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Header file for HSM                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.1.0     09-Aug-2018   Sinil        Redmine #13647                        **
** 1.0.0     16-Feb-2017   Sinil        Initial version                       **
*******************************************************************************/

#ifndef HSM_AUTDRIVER_H
#define HSM_AUTDRIVER_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Hsm_AutTypes.h"

#if ((CRYPTOLIB_SUPORT_HSM_SPC58X == STD_ON) || (CRYPTOLIB_SUPORT_HSM_ICUM == STD_ON))
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"

/* Secure Boot */
extern Hsm_ErrType Hsm_EnableSecureBoot(uint32 ulSecureBootAddress,
  uint32 ulSecureBootSize);
extern Hsm_ErrType Hsm_GetSecureBootStatus(
  HSM_SecureBootStatusType* pSecureBootStatus);

#if (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON)
extern Hsm_ErrType Hsm_CustomIauExportData(boolean blAsync, Hsm_CallbackPtr pCallback,
  Hsm_DataType ddDataType, uint32 ulDataLength, uint8* pRawData);
extern Hsm_ErrType Hsm_CustomIauPinningCheck(boolean blAsync, Hsm_CallbackPtr pCallback,
  boolean* pPinningCheckOk);
extern Hsm_ErrType Hsm_CustomIauGenSeedSc(boolean blAsync, Hsm_CallbackPtr pCallback,
  uint32 ulIterationCount, uint8* pConString, uint32 ulConStringLength,
  Hsm_DataIDType ddHsmAesKeyID, uint8* pSeecSc);
extern Hsm_ErrType Hsm_CustomIauKdf(boolean blAsync, Hsm_CallbackPtr pCallback,
  uint8* pRandomNumber, uint8* pTokenID, uint8* pEncSeed,
  Hsm_DataIDType ddHsmAesKeyID, uint8* pAuthKey, uint8* pEncKey);
#endif /* (CRYPTOLIB_SUPPORT_HSM_SPC58X_IAU == STD_ON) */

#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((CRYPTOLIB_SUPORT_HSM_SPC58X == STD_ON) || (CRYPTOLIB_SUPORT_HSM_ICUM == STD_ON)) */

#endif /* HSM_AUTDRIVER_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
