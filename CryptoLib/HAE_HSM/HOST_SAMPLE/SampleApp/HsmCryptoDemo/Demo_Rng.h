#ifndef DEMO_RNG_H_
#define DEMO_RNG_H_

#include "Hsm_Types.h"
#include "Demo_CryptoTestDefine.h"

Std_ReturnType trngTest_Simple(HSM_RNG_TestVector hsmRngTestVector);
Std_ReturnType trngTest_RandomLength(void);
Std_ReturnType trngTest_allLength(void);
Std_ReturnType prngTest_Simple(HSM_RNG_TestVector hsmRngTestVector);
Std_ReturnType prngTest_RandomLength(void);


#endif /* DEMO_RNG_H_ */
