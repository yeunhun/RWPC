/***************************************************************************/
/*!

   \file        HKMC_ASK_Server.h

   \title       Advanced Seedkey Server Header File

   \version		v1.2

 */
/***************************************************************************/


#ifndef __ADV_SEED_KEY_SERVER_H__
#define __ADV_SEED_KEY_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef uint8_defined
	typedef unsigned char uint8;
	#define uint8_defined
#endif
#ifndef uint16_defined
	typedef unsigned short uint16;
	#define uint16_defined
#endif
#ifndef uint32_defined
	typedef unsigned long uint32;
	#define uint32_defined
#endif

typedef enum{
    SEEDKEY_SUCCESS = 0,
    SEEDKEY_FAIL = 1,
} SEEDKEY_RT;

#ifndef VERSION_INFO_AVAILABLE
#define VERSION_INFO_AVAILABLE
#endif

typedef struct {
    uint16 vendorID;
    uint16 moduleID;
    uint8 majorVersion;
    uint8 minorVersion;
    uint8 patchVersion;
} VERSION_INFO;

SEEDKEY_RT ASK_KeyGenerate(const uint8 *seed_buffer_8byte, uint8 *key_buffer_8byte);
SEEDKEY_RT ASK_Rand8ByteGenerate(uint8 *seed_buffer_8byte);
void ASK_RandInit(uint32 rand_seed);
void vGetVersionInfo(VERSION_INFO *pVersionInfo);

#ifdef __cplusplus
};
#endif
#endif
