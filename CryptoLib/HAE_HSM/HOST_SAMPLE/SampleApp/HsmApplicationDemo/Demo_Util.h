#ifndef DEMO_UTIL_H_
#define DEMO_UTIL_H_

#include "Hsm_Types.h"
#include "Demo_AppTestDefine.h"

Std_ReturnType HostTest_HSM_FactoryHsmConfigurationLock(void);
Std_ReturnType HostTest_HSM_GetConfigurationLockState(void);
Std_ReturnType HostTest_HSM_GetMcuUid(void);
Std_ReturnType HostTest_HSM_GetAllSecurityInfo(void);
Std_ReturnType HostTest_HSM_GetVersionInfo(void);
Std_ReturnType HostTest_HSM_TempStop(void);
Std_ReturnType HostTest_HSM_Restart(void);

#endif /* DEMO_UTIL_H_ */
