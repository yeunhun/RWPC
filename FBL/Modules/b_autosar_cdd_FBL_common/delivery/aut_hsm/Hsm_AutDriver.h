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

#if (FBL_USE_AUT_HSM == STD_ON)

#if ((FBL_SUPPORT_MCU == FBL_MCU_SPC58X) || (FBL_SUPPORT_MCU == FBL_MCU_RH850F1KM))
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* Secure Boot */
extern Hsm_ErrType Hsm_EnableSecureBoot(uint32 ulSecureBootAddress,
  uint32 ulSecureBootSize);
extern Hsm_ErrType Hsm_GetSecureBootStatus(
  HSM_SecureBootStatusType* pSecureBootStatus);

#endif /* ((FBL_SUPPORT_MCU == FBL_MCU_SPC58X) || (FBL_SUPPORT_MCU == FBL_MCU_RH850F1KM)) */

#endif /* (FBL_USE_AUT_HSM == STD_ON) */

#endif /* HSM_AUTDRIVER_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
