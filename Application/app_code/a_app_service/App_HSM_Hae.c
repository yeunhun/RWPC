/*******************************************************************************
**                                                                            **
**  (C) 2017 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: App_HSM_Hae.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : Hsm (Hardware Security Module)                                **
**                                                                            **
**  PURPOSE   : Implementation file for HSM                                   **
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
** 1.0.0     22-Jun-2020   JaeHyun      Redmine #22362                        **

*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_HSM_Hae.h"

#if (CRYPTOLIB_SUPORT_HSM_HAE_HSM_2_X == STD_ON)
#include "Hsm_HostAPI.h"
#include "Os.h"
#include "Mcu.h"

#include "SecurityApp_SecureBoot.h"
#include "SecurityApp_FwTamperDetection.h"
#include "SecurityApp_SecureDebug.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
uint16 HSMErrCode = 0u;

HSM_SECUREBOOT_STATE_t SecureBootState;
HSM_CONFIG_LOCK_STATE_t ConfigLockState;
HSM_SECURITY_INFO_t HSMSecurityInfo;

Std_ReturnType SecureBootResult = E_NOT_OK;
Std_ReturnType GetSecurityInfoResult = E_NOT_OK;
Std_ReturnType CfgLockStateResult = E_NOT_OK;

void UserCallout_HsmDriverInit(void)
{
  Std_ReturnType LddRT;

  LddRT = HSM_EnableService(0,6);   /*User must configurate ISR to Ecud_Os.arxml*/

  if (LddRT == E_OK)
  {
    LddRT = HSM_DriverInitialize();

    if (LddRT == E_OK)
    {
      SecureBootResult = HSM_SecureBootResult(&SecureBootState);
      GetSecurityInfoResult = HSM_GetAllSecurityInfo(&HSMSecurityInfo);
      CfgLockStateResult = HSM_GetConfigurationLockState(&ConfigLockState);
    }
  }
  
  if (LddRT != E_OK)
  {
    /*HSM initialize Fail*/
    HSMErrCode = HSM_GetLastErrorCode();
    Mcu_PerformReset();
  }
}

ISR(Hsm_Isr_Vector_4_Cat2)
{
  HSM_IrqHandler();
}

#endif /* (CRYPTOLIB_SUPORT_HSM_HAE_HSM_2_X == STD_ON) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
