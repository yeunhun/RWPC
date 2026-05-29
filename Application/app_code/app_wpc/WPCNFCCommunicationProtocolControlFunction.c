/*******************************************************************************
* Include Headers                                                              *
*******************************************************************************/
#include "WPCVehicleOption.h"
#include "WPCType.h"
#include "Define.h"
#include "WPCTimer.h"
#include "Data.h"
#include "Rte_SWC_Input.h"

#include "app_can_input_type.h"
#include "app_can_input.h"
#include "app_input_type.h"
#include "app_input.h"
#include "app_output_type.h"
#include "app_output.h"

/********************************************************************************
* NFC Module Includes
********************************************************************************/
#include "st_errno.h"
#include "rfal_nfc.h"
//#include "utils.h"
#include "rfal_rf.h"
#include "rfal_analogConfig.h"
#include "st25r3916_irq.h"
#include "st25r3916.h"
#include "nfc_utils.h"

#include "WPC_NFCIC.h"
#include "WPCLogicControl.h"
/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/

extern uint32 g1msCnt;

/*
******************************************************************************
* GLOBAL TYPES
******************************************************************************
*/
extern void nfcic_Select(void);
extern void nfcic_Deselect(void);
extern void nfcic_Int_EnableIRQ(void);
extern void nfcic_Int_DisableIRQ(void);

/*******************************************************************************
 * GLOBAL VARIABLES
 *******************************************************************************/
//extern uint32_t g1msCnt;
tTimer8 TimerCANEvtmsgTimeout = {Off, 0u};
tTimer8 p_tWaitingDelay3 = {Off, 0u};
tTimer8 p_tWaitingDelay4 = {Off, 0u};

uint8 gLPCD_ENABLE = Off;
u8 Receive_Flag_NFCDetection = kWPCNFCDetection_Off;		/* FunctionSet 11 */
e_NFCState stateNFC = stsNFC_Init; //stsNFC_Deactivated; //stsNFC_None;

/*
******************************************************************************
* LOCAL FUNCTION PROTOTYPES
******************************************************************************
*/

/*
NFC_Work
return value
0 : not detected any card
> 0 : detected ( REQA ~ ADPU ... )
*/

u32 g1msCngOldValue;

void nonNFCCommunication(void)
{
  if(g1msCngOldValue != g1msCnt)
  {
    g1msCngOldValue = g1msCnt;
  }
  else
  {
    nfc_ticktimer_start();
  }
}

void NFCCommunication(void)
{
	static uint8_t nfc_mode_on_request = 0u;
	static uint8_t nfc_mode_off_request = 0u;

	ReturnCode err = ERR_NONE;

	UpTimer8(TimerCANEvtmsgTimeout);
	UpTimer8(p_tWaitingDelay3);
	UpTimer8(p_tWaitingDelay4);

	switch(stateNFC)
	{
		case stsNFC_Init:
			if(IsChgEvt(kb_WPCStatus, (u8)WPCStatus_WPCMode) ||
				IsChgEvt(kb_WPCStatus, (u8)WPCStatus_Off))
			{
				ClrEvt(kb_WPCStatus);
				//ext_irq_disable(int_NFC);
				nfcic_Int_DisableIRQ();
			}
				
			nfc_ticktimer_start();
			nfcic_Int_EnableIRQ();
			err = rfalNfcInitialize();
			
			if(err == ERR_NONE)
			{
				stateNFC = stsNFC_Deactivated;
			}
			
			//ext_irq_disable(int_NFC);
			
			//platformSpiDeselect();
			nfcic_Int_DisableIRQ();
			//nfcic_Deselect();
			break;
			
		case stsNFC_Deactivated:
			if(IsChgEvt(kb_WPCStatus, (u8)WPCStatus_NFCMode))
			{
				ClrEvt(kb_WPCStatus);
				ClrEvt(kC_WPCNFCcmd);
				ClrEvt(kC_BDCWPCNFCCmd);				/* FunctionSet 11 */
				//ext_irq_enable(int_NFC);
				nfcic_Int_EnableIRQ();
				nfc_mode_on_request = 1u;
			}
			else if((GetX(kb_WPCStatus) == (u8)WPCStatus_NFCMode) &&
					(IsChgEvt(kC_WPCNFCcmd, (u8)kWPCNFCcmd_NFCSearchingOn_HCE) ||
					 IsChgEvt(kC_WPCNFCcmd, (u8)kWPCNFCcmd_NFCSearchingOn_Usim) ||
					 IsChgEvt(kC_BDCWPCNFCCmd, (u8)kIAUWPCNFCcmd_NFCPolling_Search)))	/* FunctionSet 11 */
			{
				ClrEvt(kC_WPCNFCcmd);
				ClrEvt(kC_BDCWPCNFCCmd);				/* FunctionSet 11 */
				//ext_irq_enable(int_NFC);
				nfcic_Int_EnableIRQ();

				StartTimer(Timer_NFCTimeOutConfirm);	 // polling duration full time : 62s

				nfc_mode_on_request = 1u;
			}
			else if(IsChgEvt(kb_WPCStatus, (u8)WPCStatus_WPCMode) ||
					IsChgEvt(kb_WPCStatus, (u8)WPCStatus_Off))
			{
				ClrEvt(kb_WPCStatus);
				//ext_irq_disable(int_NFC);
				nfcic_Int_DisableIRQ();
				//nfc_ticktimer_stop();
			}
			else
			{
				/* MISRA-C */
			}

			if(nfc_mode_on_request > 0u)
			{
				//ext_irq_enable(int_NFC);
				nfcic_Int_EnableIRQ();
				rfalNfcaPollerInitialize();
				err= rfalFieldOnAndStartGT();
				if(err==ERR_NONE )
				{
					nfc_mode_on_request = 0;
					stateNFC = stsNFC_Activated;
					rfalNfcDeactivate(false);
					rfalNfcDiscover(&discParam);
				}
			}	
			break;
			
		case stsNFC_Activated:

			rfalNfcWorker();
			
			if(IsChgEvt(kb_WPCStatus, (u8)WPCStatus_WPCMode) ||
				IsChgEvt(kb_WPCStatus, (u8)WPCStatus_Off))
			{
				ClrEvt(kb_WPCStatus);
				
				nfc_mode_off_request = 1u;
			}
			else if (IsChgEvt(kC_WPCNFCcmd, (u8)kWPCNFCcmd_NFCSearchingOn_HCE) ||
					 IsChgEvt(kC_WPCNFCcmd, (u8)kWPCNFCcmd_NFCSearchingOn_Usim) ||
			         IsChgEvt(kC_BDCWPCNFCCmd, (u8)kIAUWPCNFCcmd_NFCPolling_Search))	/* FunctionSet 11 */
			{
				StartTimer(Timer_NFCTimeOutConfirm);	 // polling duration time : 62s
				ClrEvt(kC_WPCNFCcmd);
				ClrEvt(kC_BDCWPCNFCCmd);			/* FunctionSet 11 */
				
				nfc_mode_off_request = 2u;
			}
			else
			{
				/* MISRA-C */
			}

			if(nfc_mode_off_request > 0u)
			{
				if(nfc_mode_off_request == 1u)
				{
					err = rfalNfcDeactivate(false);
					if(err==ERR_NONE)
					{
						gNfcDev.discRestart = false;
						//gNfcDev.state = RFAL_NFC_STATE_DEACTIVATION;
						stateNFC = stsNFC_Deactivated;
					}	
				}
				else if(nfc_mode_off_request == 2u)
				{
					rfalNfcDeactivate(false);
					rfalNfcDiscover(&discParam);
				}
				else if(nfc_mode_off_request == 3u)
				{
					///ext_irq_disable(int_NFC);
					nfcic_Int_DisableIRQ();
					stateNFC = stsNFC_Deactivated;
				}
				else
				{
					/* misra c */
				}
				nfc_mode_off_request = 0u;
			}
			else
			{
				if(gNfcDev.state == RFAL_NFC_STATE_IDLE)
				{
					nfc_mode_off_request = 3u;
				}
			}
			break;
		default:
			/* MISRA-C */
			break;
	}

	if(TimerCANEvtmsgTimeout.time >= Time_ms(120))
	{
		CancelTimer(TimerCANEvtmsgTimeout);
//		Receive_Flag_NFCDetection = kWPCNFCDetection_Off;		/* FunctionSet 11 */
		SetOutput(kC_WPC_NFCDetection, (u8)kWPCNFCDetection_Off);
	}
}
