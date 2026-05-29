#ifndef DEMO_PROACTIVE_DATA_PROTECTION_H_
#define DEMO_PROACTIVE_DATA_PROTECTION_H_

#include "Hsm_Types.h"
#include "Demo_AppTestDefine.h"

/* Proactive Data Protection */
Std_ReturnType HostTest_HSM_PDPConfig(HSM_PROACTIVE_DATA_PROTECTION_TestVector_t hsmPdpTv);
Std_ReturnType HostTest_HSM_PDPDataVerify(void);
Std_ReturnType HostTest_HSM_PDPDataUpdate(void);
Std_ReturnType HostTest_HSM_PDPDisable(void);

#endif /* DEMO_PROACTIVE_DATA_PROTECTION_H_ */
