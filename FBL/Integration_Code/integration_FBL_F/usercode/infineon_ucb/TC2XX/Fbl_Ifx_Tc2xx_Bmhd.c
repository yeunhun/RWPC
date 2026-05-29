/**
 * \file Fbl_IfxCpu_Bmhd.c

 * \brief This file contains the Bmhd for Aurix Plus.
 * \ingroup
 *
 *
 */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Fbl_Cfg.h"

#if (FBL_SUPPORT_MCU == FBL_MCU_TC23X) || (FBL_SUPPORT_MCU == FBL_MCU_TC29X)

/**************************************************************
 *  Name                 : BMH
 *  Description          :
 *  Parameters           :
 *  Return               :
 *  Critical/explanation :
 **************************************************************/
__asm( "\n"
"\t.sdecl	'.rodata.bbhwvect._BMH0', data, rom\n"
"\t.sect	'.rodata.bbhwvect._BMH0'\n"
"\t.align   32\n"
"_BMH0: .type	object\n"
"\t.size    _BMH0, 32\n"
"\t.word    0xA0000020, 0xB3590070, 0x00000000, 0x00000000, \
		    0x00000000, 0x00000000, 0x5DB996AC, 0xA2466953");

#endif /* (FBL_SUPPORT_MCU == FBL_MCU_TC23X) || (FBL_SUPPORT_MCU == FBL_MCU_TC29X) */
