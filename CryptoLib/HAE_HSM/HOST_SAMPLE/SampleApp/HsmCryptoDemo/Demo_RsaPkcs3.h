#ifndef DEMO_RSAPKCS3_H_
#define DEMO_RSAPKCS3_H_

#include "Hsm_Types.h"
#include "Demo_CryptoTestDefine.h"

Std_ReturnType pkcs3DHKeypairGenTest_Simple(HSM_Rsa_Pkcs3_DiffieHellman_TestVector pkcs3DiffieHellmanTv);
Std_ReturnType pkcs3DHSharedValueGenTest_Simple(HSM_Rsa_Pkcs3_DiffieHellman_TestVector pkcs3DiffieHellmanTv);

Std_ReturnType HSM_Pkcs3DHKeypairGenerate(const UINT8 *xa, const UINT8 *dh_base, const UINT8 *dh_prime, UINT8* public, UINT8 *private);
Std_ReturnType HSM_Pkcs3DHSharedValueGenerate(const UINT8* y, const UINT8* x, const UINT8* dh_prime, UINT8* secretValue);

#endif /* DEMO_RSAPKCS3_H_ */
