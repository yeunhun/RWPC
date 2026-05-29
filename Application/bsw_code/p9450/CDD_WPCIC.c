/*******************************************************************************
**                       HYUNDAI-AUTOEVER PVT LTD                             **
********************************************************************************
** Copyright (C) HYUNDAI-AUTOEVER PVT LTD - All Rights Reserved               **
** Unauthorized copying of this file, via any medium is strictly prohibited   **
** Auto generated file                                                        **
*******************************************************************************/
#include "Rte_CDD_WPCIC.h"
#include "cy_scb_i2c.h"

#define CDD_WPCIC_START_SEC_CODE
#include "CDD_WPCIC_MemMap.h"


volatile uint8 test_read_val = 0u;

FUNC(void, CDD_WPCIC_CODE) wpcic_enable(void) 
{
  Rte_Call_R_DigDir_VBATSW_EN_WriteDirect(IOHWAB_HIGH);
}

FUNC(void, CDD_WPCIC_CODE) wpcic_disable(void) 
{
  Rte_Call_R_DigDir_VBATSW_EN_WriteDirect(IOHWAB_LOW);
}

FUNC(void, CDD_WPCIC_CODE) VBATSW_EN_Read(void)
{
/*****************************************************************************/
/*               Start of Runnable                                           */
/*****************************************************************************/
VAR(IoHwAb_LevelType, AUTOMATIC) VBATSW_EN_Read_00;
VAR(Std_ReturnType, AUTOMATIC) retVBATSW_EN_Read_0;

/* PROTECTED REGION START ID(User Defined Variable):(RE_VBATSW_EN_Read) */
/* Start of user defined code  - Do not remove this comment */
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Variable):(RE_VBATSW_EN_Read) */
/* **********************Rte Synchronous Call API************************ */
retVBATSW_EN_Read_0 = Rte_Call_R_DigDir_VBATSW_EN_ReadDirect(&VBATSW_EN_Read_00);

/* PROTECTED REGION START ID(User Defined Code):(RE_VBATSW_EN_Read) */
/* Start of user defined code  - Do not remove this comment */

test_read_val = VBATSW_EN_Read_00;
/* End of user defined code - Do not remove this comment */
/* PROTECTED REGION END ID(User Defined Code):(RE_VBATSW_EN_Read) */
/*****************************************************************************/
/*               End of Runnable                                             */
/*****************************************************************************/
}

uint8 adfadf(void)
{
  VAR(IoHwAb_LevelType, AUTOMATIC) VBATSW_EN_Read_00;

  (void)Rte_Call_R_DigDir_VBATSW_EN_ReadDirect(&VBATSW_EN_Read_00);

  return VBATSW_EN_Read_00;
}






#define CDD_WPCIC_STOP_SEC_CODE
#include "CDD_WPCIC_MemMap.h"
