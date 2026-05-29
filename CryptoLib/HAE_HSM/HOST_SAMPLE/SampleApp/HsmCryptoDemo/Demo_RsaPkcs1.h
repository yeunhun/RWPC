#ifndef DEMO_RSAPKCS1_H_
#define DEMO_RSAPKCS1_H_

#include "Hsm_Types.h"
#include "Demo_CryptoTestDefine.h"

Std_ReturnType pkcs1v15SignTest_Simple(HSM_Rsa_Pkcs1_v15_Sign_TestVector pkcs1v15SignTv);
Std_ReturnType pkcs1v15VerifyTest_Simple(HSM_Rsa_Pkcs1_v15_Sign_TestVector pkcs1v15SignTv);
Std_ReturnType pkcs1v15Sha160VerifyTest_Simple(HSM_Rsa_Pkcs1_v15_Sign_TestVector pkcs1v15Sha160VerifyTv);
Std_ReturnType pkcs1v15EncTest_Simple(HSM_Rsa_Pkcs1_v15_Enc_TestVector pkcs1v15EncTv);
Std_ReturnType pkcs1v15DecTest_Simple(HSM_Rsa_Pkcs1_v15_Enc_TestVector pkcs1v15DecTv);
Std_ReturnType pkcs1PssSignTest_Simple(HSM_Rsa_Pkcs1_Pss_Sign_TestVector pkcs1PssSignTv);
Std_ReturnType pkcs1PssVerifyTest_Simple(HSM_Rsa_Pkcs1_Pss_Sign_TestVector pkcs1PssSignTv);
Std_ReturnType pkcs1OaepEncTest_Simple(HSM_Rsa_Pkcs1_Oaep_Enc_TestVector pkcs1oaepEncTv);
Std_ReturnType pkcs1OaepDecTest_Simple(HSM_Rsa_Pkcs1_Oaep_Enc_TestVector pkcs1oaepDecTv);

Std_ReturnType HSM_Pkcs1v15SignGenerate(const UINT16 keyNum, const UINT8 *digest, UINT8 *sign);
Std_ReturnType HSM_Pkcs1v15SignVerify(const UINT16 keyNum, const UINT8 *digest, const UINT8* sign, UINT8 *verifyResult);
Std_ReturnType HSM_Pkcs1v15Sha160SignVerify(const UINT16 keyNum, const UINT8 *digest, const UINT8* sign, UINT8 *verifyResult);
Std_ReturnType HSM_Pkcs1v15Enc(const UINT16 keyNum, const UINT8 *msg, const UINT32 mLen, UINT8 *cipher);
Std_ReturnType HSM_Pkcs1v15Dec(const UINT16 keyNum, const UINT8 *cipher, UINT8 *msg, UINT32 *mLen);
Std_ReturnType HSM_Pkcs1PssSignGenerate(const UINT16 keyNum, const UINT8 *digest, const UINT8 *salt, const UINT8 saltLen, UINT8 *sign);
Std_ReturnType HSM_Pkcs1PssSignVerify(const UINT16 keyNum, const UINT8 *digest, const UINT8* sign, const UINT8 saltLen, UINT8 *verifyResult);
Std_ReturnType HSM_Pkcs1OaepEnc(const UINT16 keyNum, const UINT8 *msg, const UINT32 mLen, const UINT8 *seed, UINT8 *cipher);
Std_ReturnType HSM_Pkcs1OaepDec(const UINT16 keyNum, const UINT8 *cipher, UINT8 *msg, UINT32 *mLen);

#endif /* DEMO_RSAPKCS1_H_ */
