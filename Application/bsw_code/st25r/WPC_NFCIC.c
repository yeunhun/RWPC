

/******************************************************************************
  Include Headers
*******************************************************************************/

/*************** AUTOSAR ********************/
#include "Rte_CDD_NFCIC.h"
#include "Spi.h"

/*************** Application ********************/
#include "WPCType.h"

/*************** NFC IC ********************/
#include "WPC_NFCIC.h"
#include "platform.h"

#include "rfal_nfc.h"
#include "rfal_rf.h"
#include "rfal_analogConfig.h"
#include "st25r3916_irq.h"

#include "WPCLogicControl.h"
#include "WPCVehicleOption.h"

/*******************************************************************************
  Define  Variables
*******************************************************************************/
uint32 g1msCnt = 0u;

/*******************************************************************************
  Declare Internal Function
*******************************************************************************/
extern void st25r3916Isr(void);

/*******************************************************************************
  Declare Internal Variables
*******************************************************************************/


#define CDD_NFCIC_START_SEC_CODE
#include "CDD_NFCIC_MemMap.h"
/***********************************************************************************************************************
* Function Name:    nfcic_SpiTxRx
* Description :     Tx/Rx spi data
* Arguments :       none
* Return Value :    none
***********************************************************************************************************************/
void nfcic_SpiTxRx(const u8 *txbuf, u8 *rxbuf, u16 length)
{
  u8 spi_src_data[256];
  u8 spi_des_data[256];
  u8 retTransmit;

  if(txbuf != NULL)
  {
    ST_MEMCPY(spi_src_data, txbuf, length);
  }

  Spi_SetupEB(SpiConf_SpiChannel_SpiChannel_0, spi_src_data, spi_des_data, length);
  retTransmit = Spi_SyncTransmit(SpiConf_SpiSequence_SpiSequence_0);

  if(rxbuf != NULL)
  {
    ST_MEMCPY(rxbuf, spi_des_data, length);
  }
}

/***********************************************************************************************************************
* Function Name:    nfcic_CSControl
* Description :     spi chip Select/Deselect
* Arguments :       none
* Return Value :    none
***********************************************************************************************************************/
FUNC(void, CDD_NFCIC_CODE) nfcic_Select(void)
{
  Rte_Call_R_DigDir_SPI_CS_WriteDirect(IOHWAB_LOW);
}

FUNC(void, CDD_NFCIC_CODE) nfcic_Deselect(void)
{
  Rte_Call_R_DigDir_SPI_CS_WriteDirect(IOHWAB_HIGH);
}

/***********************************************************************************************************************
* Function Name:    nfcic_Int_EnableIRQ/nfcic_Int_DisableIRQ
* Description :     spi Interrupt Enable/Disable
* Arguments :       none
* Return Value :    none
***********************************************************************************************************************/
void nfcic_Int_EnableIRQ(void)
{
  Rte_Call_R_Icu_NFC_INTERRUPT_EnableNotification();
  Rte_Call_R_Icu_NFC_INTERRUPT_EnableEdgeDetection();
}

void nfcic_Int_DisableIRQ(void)
{
  Rte_Call_R_Icu_NFC_INTERRUPT_DisableEdgeDetection();
  Rte_Call_R_Icu_NFC_INTERRUPT_DisableNotification();
}

/***********************************************************************************************************************
* Function Name:    nfcic_int_pin_levelcheck
* Description :     spi Interrupt Pin Level check
* Arguments :       none
* Return Value :    none
***********************************************************************************************************************/
IoHwAb_LevelType nfcic_int_pin_levelcheck(void)
{
  IoHwAb_LevelType LddLevel;

  Rte_Call_R_DigDir_NFC_INTERRUPT_INT_ReadDirect(&LddLevel);

  return (IoHwAb_LevelType)LddLevel;
}

/***********************************************************************************************************************
* Function Name:    nfc_ticktimer_start/nfc_ticktimer_stop/get_ticktimer
* Description :     Timer start / stop / get timer count value
* Arguments :       none
* Return Value :    none
***********************************************************************************************************************/
FUNC(void, CDD_NFCIC_CODE) nfc_ticktimer_start(void)
{
  Rte_Call_R_Gpt_NFC_TickTimer_EnableNotification();

#if defined(USE_OVER_VOLTAGE_CHARGE_IC_PROTECT)
  Rte_Call_R_Gpt_NFC_TickTimer_StartTimer(250u);
#else
  Rte_Call_R_Gpt_NFC_TickTimer_StartTimer(1000u);
#endif
}

FUNC(void, CDD_NFCIC_CODE) nfc_ticktimer_stop(void)
{
  Rte_Call_R_Gpt_NFC_TickTimer_StopTimer();
  Rte_Call_R_Gpt_NFC_TickTimer_DisableNotification();
}

IoHwAb_GptValueType get_ticktimer(void)
{
  IoHwAb_GptValueType value;

  Rte_Call_CDD_NFCIC_R_Gpt_NFC_TickTimer_GetTimeElapsed(&value);

  return (IoHwAb_GptValueType)(value / 1000u);  /* return us -> ms */
}

#if defined(USE_OVER_VOLTAGE_CHARGE_IC_PROTECT)
extern void Protection_for_chargeIC(void);
extern void Protection_for_chargeIC_time_Measure(void);
#endif
//extgern uint8 get_init_nvm_test(void);
FUNC(void, CDD_NFCIC_CODE) nfc_ticktimer_Cbk(void) // 250us�� ����
{
#if defined(USE_OVER_VOLTAGE_CHARGE_IC_PROTECT)
  static u8 g1msCnt_tmp = 0;

  g1msCnt_tmp++;
  if(g1msCnt_tmp>=4)
  {
    g1msCnt_tmp = 0;
    g1msCnt++;
  }

	Protection_for_chargeIC();
  //Protection_for_chargeIC_time_Measure();
#else
	g1msCnt++;
#endif
}

/***********************************************************************************************************************
* Function Name:    IcuSignalEdgeDetection_NFC_INTERRUPT
* Description :     NFC IC External Interrupt ISR
* Arguments :       none
* Return Value :    none
***********************************************************************************************************************/
FUNC(void, CDD_NFCIC_CODE) nfcic_interrup_Cbk(void)
{
	st25r3916Isr();
}
#define CDD_NFCIC_STOP_SEC_CODE
#include "CDD_NFCIC_MemMap.h"




