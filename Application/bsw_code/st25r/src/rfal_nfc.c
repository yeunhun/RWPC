/**
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/*! \file rfal_nfc.c
 *
 *  \author Gustavo Patricio
 *
 *  \brief RFAL NFC device  
 *  
 *  This module provides the required features to behave as an NFC Poller 
 *  or Listener device. It grants an easy to use interface for the following
 *  activities: Technology Detection, Collision Resollution, Activation,
 *  Data Exchange, and Deactivation
 *  
 *  This layer is influenced by (but not fully aligned with) the NFC Forum 
 *  specifications, in particular: Activity 2.0 and NCI 2.0
 *
 */
 
/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */
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
#include "WPC_NFCIC.h"


//#include "utils.h"
/********************************************************************************
* NFC Module Includes
********************************************************************************/
#include "rfal_nfc.h"
#include "rfal_analogConfig.h"

#include "st_errno.h"

#include "rfal_nfc.h"
#include "nfc_utils.h"

#include "rfal_rf.h"
#include "rfal_analogConfig.h"
#include "st25r3916_irq.h"

#include "st25r3916.h"


#include "WPCLogicControl.h"
/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/

/*
******************************************************************************
* GLOBAL MACROS
******************************************************************************
*/
#define ECP_ENABLE  1
#define rfalNfcNfcNotify( st )         if( gNfcDev.disc.notifyCb != NULL )  gNfcDev.disc.notifyCb( st )


/*
******************************************************************************
* GLOBAL TYPES
******************************************************************************
*/


/*
******************************************************************************
* GLOBAL VARIABLES
******************************************************************************
*/

/*
 ******************************************************************************
 * LOCAL VARIABLES
 ******************************************************************************
 */
rfalNfc gNfcDev;
rfalNfcDiscoverParam discParam;

extern Dcm_MsgContextTypeLocal pMsgContext_Local;
/*
******************************************************************************
* LOCAL FUNCTION PROTOTYPES
******************************************************************************
*/
static ReturnCode rfalNfcPollTechDetetection( void );
static ReturnCode rfalNfcPollCollResolution( void );
static ReturnCode rfalNfcPollActivation( uint8_t devIt );
static ReturnCode rfalNfcDeactivation( void );
extern void nfc_ticktimer_start(void);

/*!
 *****************************************************************************
 * \brief Demo Notification
 *
 *  This function receives the event notifications from RFAL
 *****************************************************************************
 */
static void NfcNotif( rfalNfcState st )
{
	if( st == RFAL_NFC_STATE_POLL_TECHDETECT )
	{
		// to do.
	}
}

/*******************************************************************************/
ReturnCode rfalNfcInitialize( void )
{
	ReturnCode err;

	gNfcDev.state = RFAL_NFC_STATE_IDLE;
	rfalAnalogConfigInitialize();				/* Initialize RFAL's Analog Configs */
	err = rfalInitialize();     				/* Initialize RFAL */

	if(err == ERR_NONE)
	{
		discParam.compMode      = RFAL_COMPLIANCE_MODE_NFC;
		discParam.devLimit      = 1U;
		discParam.nfcfBR        = RFAL_BR_212;
		discParam.ap2pBR        = RFAL_BR_424;
		discParam.maxBR         = RFAL_BR_KEEP;

		discParam.notifyCb             = NfcNotif;
		discParam.wakeupEnabled        = true;//false;
		discParam.wakeupConfigDefault  = true;
		discParam.totalDuration        = 30U;		// 1cycle 30ms
		discParam.techs2Find           = 0U;
		discParam.techs2Find           |= RFAL_NFC_POLL_TECH_A;
		/* Added DK 2.0 Start */
		discParam.techs2Find           |= RFAL_NFC_POLL_TECH_PROPA;

		discParam.propAPoll[0] = 0x6A;		/* VASUP-A command				*/
		discParam.propAPoll[1] = 0x02;		/* Byte1 - Format : 2.0			*/
		discParam.propAPoll[2] = 0xC3;		/* Byte2 - Terminal Info		*/
		discParam.propAPoll[3] = 0x02;		/* Byte3 - Terminal Type		*/
		discParam.propAPoll[4] = 0x01;		/* Byte4 - Terminal Subtype		*/
		discParam.propAPoll[5] = 0x01;		/* Byte5 - TCI 1				*/
		discParam.propAPoll[6] = 0x00;		/* Byte6 - TCI 2				*/
		discParam.propAPoll[7] = 0x43;		/* Byte7 - TCI 3	KMC Spec	*/

		discParam.propAPollLen = 8U;
		/* Added DK 2.0 End */

		/* Check for valid configuration by calling Discover once */
		err = rfalNfcDiscover( &discParam );
		rfalNfcDeactivate( false );

		if( err != ERR_NONE )
		{
			return err;
		}

		gNfcDev.state = RFAL_NFC_STATE_IDLE;		/* Go to initialized */
		return err;
	}
	return err;
}

/*******************************************************************************/
ReturnCode rfalNfcDiscover( const rfalNfcDiscoverParam *disParams )
{
	/* Check if initialization has been performed */
	if( gNfcDev.state != RFAL_NFC_STATE_IDLE )
	{
		return ERR_WRONG_STATE;
	}

	/* Check valid parameters */
	if( (disParams == NULL) || (disParams->devLimit > RFAL_NFC_MAX_DEVICES) || (disParams->devLimit == 0U) || 
		( (disParams->maxBR > RFAL_BR_1695) && (disParams->maxBR != RFAL_BR_KEEP) ) ||
		( ( (disParams->techs2Find & RFAL_NFC_POLL_TECH_F) != 0U) && (disParams->nfcfBR != RFAL_BR_212) && (disParams->nfcfBR != RFAL_BR_424) ) ||
		( ( ( (disParams->techs2Find & RFAL_NFC_POLL_TECH_AP2P) != 0U) && (disParams->ap2pBR > RFAL_BR_424)) || (disParams->GBLen > RFAL_NFCDEP_GB_MAX_LEN) ) ||
		( ( (disParams->techs2Find & RFAL_NFC_POLL_TECH_PROPA) != 0U) && ( (disParams->devLimit != 1U) || (disParams->propAPollLen > RFAL_NFC_PROPA_POLL_LEN) ) ) )			/* Added DK 2.0 */
	{
		return ERR_PARAM;
	}

	if( (((disParams->techs2Find & RFAL_NFC_POLL_TECH_A) != 0U)			&& !((bool)RFAL_FEATURE_NFCA))		||
		(((disParams->techs2Find & RFAL_NFC_POLL_TECH_B) != 0U)			&& !((bool)RFAL_FEATURE_NFCB))		||
		(((disParams->techs2Find & RFAL_NFC_POLL_TECH_F) != 0U)			&& !((bool)RFAL_FEATURE_NFCF))		||
		(((disParams->techs2Find & RFAL_NFC_POLL_TECH_V) != 0U)			&& !((bool)RFAL_FEATURE_NFCV))		||
		(((disParams->techs2Find & RFAL_NFC_POLL_TECH_ST25TB) != 0U)	&& !((bool)RFAL_FEATURE_ST25TB))	||
		(((disParams->techs2Find & RFAL_NFC_POLL_TECH_AP2P) != 0U)		&& !((bool)RFAL_FEATURE_NFC_DEP))	||
		(((disParams->techs2Find & RFAL_NFC_POLL_TECH_PROPA) != 0U)		&& !((bool)RFAL_FEATURE_NFCA))		||		/* Added DK 2.0 */
		(((disParams->techs2Find & RFAL_NFC_LISTEN_TECH_A) != 0U)		&& !((bool)RFAL_FEATURE_NFCA))		||
		(((disParams->techs2Find & RFAL_NFC_LISTEN_TECH_B) != 0U)		&& !((bool)RFAL_FEATURE_NFCB))		||
		(((disParams->techs2Find & RFAL_NFC_LISTEN_TECH_F) != 0U)		&& !((bool)RFAL_FEATURE_NFCF))		||
		(((disParams->techs2Find & RFAL_NFC_LISTEN_TECH_AP2P) != 0U)	&& !((bool)RFAL_FEATURE_NFC_DEP)) )
	{
		return ERR_DISABLED;	/*  PRQA S  2880 # MISRA 2.1 - Unreachable code due to configuration option being set/unset  */ 
	}
    
	/* Initialize context for discovery */
	gNfcDev.activeDev       = NULL;
	gNfcDev.techsFound      = RFAL_NFC_TECH_NONE;
	gNfcDev.devCnt          = 0;
	gNfcDev.discRestart     = true;
	gNfcDev.isTechInit      = false;
	gNfcDev.disc            = *disParams;

	gNfcDev.state = RFAL_NFC_STATE_START;
    
	return ERR_NONE;
}

/*******************************************************************************/
ReturnCode rfalNfcDeactivate( bool discovery )
{
	/* Check for valid state */
	if( gNfcDev.state <= RFAL_NFC_STATE_IDLE )
	{
		return ERR_WRONG_STATE;
	}

	/* Check if discovery is to continue afterwards */
	if( (discovery == true) && (gNfcDev.disc.techs2Find != RFAL_NFC_TECH_NONE) )
	{
		/* If so let the state machine continue*/
		gNfcDev.discRestart = discovery;
		gNfcDev.state       = RFAL_NFC_STATE_DEACTIVATION;
	}
	else
	{
		/* Otherwise deactivate immediately and go to IDLE */
		rfalNfcDeactivation();
		gNfcDev.state = RFAL_NFC_STATE_IDLE;
	}

	return ERR_NONE;
}

/*******************************************************************************/
rfalNfcState rfalNfcGetState( void )
{
	return gNfcDev.state;
}

/*******************************************************************************/
ReturnCode rfalNfcGetActiveDevice( rfalNfcDevice **dev )
{
	/* Check for valid state */
	if( gNfcDev.state < RFAL_NFC_STATE_ACTIVATED )
	{
		return ERR_WRONG_STATE;
	}

	/* Check valid parameter */
	if( dev == NULL )
	{
		return ERR_PARAM;
	}

	/* Check for valid state */
	if( (gNfcDev.devCnt == 0U) || (gNfcDev.activeDev == NULL)  )
	{
		return ERR_REQUEST;
	}

	*dev = gNfcDev.activeDev;
	return ERR_NONE;
}


/*******************************************************************************/
void rfalNfcWorker( void )
{
	ReturnCode err;
	uint16_t   *rxLen;
	uint8_t    *rxData;
	static uint16_t wait_tp_response_timeout_cnt = 0u;

	rfalWorker();					/* Execute RFAL process  */

	switch( gNfcDev.state )
	{   
		/*******************************************************************************/
		case RFAL_NFC_STATE_NOTINIT:
		case RFAL_NFC_STATE_IDLE:
			break;

		/*******************************************************************************/
		case RFAL_NFC_STATE_START:
			
			SetX(kS_WPC_RQST, Off);
			SetX(kS_IAU_RSPS, Off);

			CancelTimer(p_tWaitingDelay3);
			CancelTimer(p_tWaitingDelay4);
			
			/* Initialize context for discovery cycle */
			gNfcDev.devCnt      = 0;
			gNfcDev.selDevIdx   = 0;
			gNfcDev.techsFound  = RFAL_NFC_TECH_NONE;
			gNfcDev.techs2do    = gNfcDev.disc.techs2Find;
			gNfcDev.state       = RFAL_NFC_STATE_POLL_TECHDETECT;

		 #if RFAL_FEATURE_WAKEUP_MODE    
            /* Check if Low power Wake-Up is to be performed */
            if( gNfcDev.disc.wakeupEnabled )
            {
                /* Initialize Low power Wake-up mode and wait */
                err = rfalWakeUpModeStart( (gNfcDev.disc.wakeupConfigDefault ? NULL : &gNfcDev.disc.wakeupConfig) );
                if( err == ERR_NONE )
                {
                    gNfcDev.state = RFAL_NFC_STATE_WAKEUP_MODE;
                    rfalNfcNfcNotify( gNfcDev.state );                                /* Notify caller that WU was started */
                }
            }
        #endif /* RFAL_FEATURE_WAKEUP_MODE */
		
			break;

		/*******************************************************************************/
        case RFAL_NFC_STATE_WAKEUP_MODE:
            
    #if RFAL_FEATURE_WAKEUP_MODE
            /* Check if the Wake-up mode has woke */
            if( rfalWakeUpModeHasWoke() )
            {
                rfalWakeUpModeStop();                                                 /* Disable Wake-up mode           */
                gNfcDev.state = RFAL_NFC_STATE_POLL_TECHDETECT;                       /* Go to Technology detection     */
                
                rfalNfcNfcNotify( gNfcDev.state );                                    /* Notify caller that WU has woke */
            }
    #endif /* RFAL_FEATURE_WAKEUP_MODE */

            break;
		/*******************************************************************************/
		case RFAL_NFC_STATE_POLL_TECHDETECT:

			/* Start total duration timer */
			platformTimerDestroy( gNfcDev.discTmr );
			gNfcDev.discTmr = (uint32_t)platformTimerCreate( gNfcDev.disc.totalDuration );

			err = rfalNfcPollTechDetetection();			/* Perform Technology Detection                         */
			if( err != ERR_BUSY )						/* Wait until all technologies are performed            */
			{
				if( ( err != ERR_NONE) || (gNfcDev.techsFound == RFAL_NFC_TECH_NONE) )	/* Check if any error occurred or no techs were found   */
				{
					gNfcDev.discRestart = true;
					gNfcDev.isTechInit = false;
					gNfcDev.state = RFAL_NFC_STATE_DEACTIVATION;		/* Nothing found as poller, go to deactivation */
					break;
				}

				gNfcDev.isOperOngoing = false;			/* No operation currently ongoing  */
				gNfcDev.techs2do = gNfcDev.techsFound;					/* Store the found technologies for collision resolution */
				gNfcDev.state    = RFAL_NFC_STATE_POLL_COLAVOIDANCE;	/* One or more devices found, go to Collision Avoidance  */
			}
			break;

		/*******************************************************************************/
		case RFAL_NFC_STATE_POLL_COLAVOIDANCE:

			err = rfalNfcPollCollResolution();						/* Resolve any eventual collision                       */
			if( err != ERR_BUSY )									/* Wait until all technologies are performed            */
			{
				if( (err != ERR_NONE) || (gNfcDev.devCnt == 0U) )	/* Check if any error occurred or no devices were found */
				{
					gNfcDev.discRestart = true;
					gNfcDev.isTechInit = false;
					gNfcDev.state = RFAL_NFC_STATE_DEACTIVATION;
					break;											/* Unable to retrieve any device, restart loop          */
				}

				/* If only one device or no callback has been set, activate the first device found */
				gNfcDev.isOperOngoing = false;
				gNfcDev.selDevIdx = 0U;
				gNfcDev.state = RFAL_NFC_STATE_POLL_ACTIVATION;
			}
			break;

		/*******************************************************************************/
		case RFAL_NFC_STATE_POLL_ACTIVATION:

			err = rfalNfcPollActivation( gNfcDev.selDevIdx );
			if( err != ERR_BUSY )					/* Wait until all Activation is complete */
			{
				if( err != ERR_NONE )				/* Activation failed selected device  */
				{
					gNfcDev.discRestart = true;
					gNfcDev.isTechInit = false;
					gNfcDev.state = RFAL_NFC_STATE_DEACTIVATION;		/* If Activation failed, restart loop */
					break;
				}

//				Receive_Flag_NFCDetection = kWPCNFCDetection_Detected;
				SetOutput(kC_WPC_NFCDetection, (u8)kWPCNFCDetection_Detected);
				StartTimer(TimerCANEvtmsgTimeout);
				wait_tp_response_timeout_cnt = 0;

				gNfcDev.state = RFAL_NFC_STATE_DATA_SET;		/* Device has been properly activated */
				rfalNfcNfcNotify( gNfcDev.state );				/* Inform upper layer that a device has been activated */
			}
			break;

		/*******************************************************************************/
		case RFAL_NFC_STATE_DATA_SET:

			wait_tp_response_timeout_cnt++;
			if((wait_tp_response_timeout_cnt >= Par_Timer_NFC_LongData_Receive_Timeout) ||
				(p_tWaitingDelay4.time >= Par_WaitingDelay4Time))
			{
				CancelTimer(p_tWaitingDelay4);
				gNfcDev.discRestart = false;
				gNfcDev.isTechInit = false;
				gNfcDev.state = RFAL_NFC_STATE_DEACTIVATION;
			}
			else
			{
				if(GetX(kS_IAU_RSPS) == On)		/* Data from CAN(IAU) */
				{
					SetX(kS_IAU_RSPS, Off);
					CancelTimer(p_tWaitingDelay4);

					gNfcDev.state = RFAL_NFC_STATE_DATAEXCHANGE_START;
				}
			}
			break;

        /*******************************************************************************/
		case RFAL_NFC_STATE_DATAEXCHANGE_START:

			err = rfalNfcDataExchangeStart( pMsgContext_Local.reqData, pMsgContext_Local.reqDataLen, &rxData, &rxLen );

			StartTimer(p_tWaitingDelay3);
			/* If a transceive has succesfully started flag Data Exchange as ongoing */
			if( err == ERR_NONE )
			{
				pMsgContext_Local.resDataLen = 0u;		// Ready for Receive

				gNfcDev.dataExErr = ERR_BUSY;
				gNfcDev.state     = RFAL_NFC_STATE_DATAEXCHANGE_CHECK;
			}
			else
			{
				gNfcDev.discRestart = false;
				gNfcDev.isTechInit = false;
				gNfcDev.state = RFAL_NFC_STATE_DEACTIVATION;
			}
			break;
			
        /*******************************************************************************/
        case RFAL_NFC_STATE_DATAEXCHANGE_CHECK:

			if(p_tWaitingDelay3.time >= Par_WaitingDelay3Time)
			{
				CancelTimer(p_tWaitingDelay3);
				
				gNfcDev.discRestart = false;
				gNfcDev.isTechInit = false;
				gNfcDev.state = RFAL_NFC_STATE_DEACTIVATION;
			}
			else
			{
				err = rfalNfcDataExchangeGetStatus();				/* Run the internal state machine */

				if( err != ERR_BUSY )								/* If Dataexchange has terminated */
				{
					gNfcDev.state = RFAL_NFC_STATE_DATA_SEND;		/* Go to data send state               */
					rfalNfcNfcNotify( gNfcDev.state );				/* And notify caller              */

					CancelTimer(p_tWaitingDelay3);
				}
			}
            break;
			
        /*******************************************************************************/
		case RFAL_NFC_STATE_DATA_SEND:

			ST_MEMMOVE(&pMsgContext_Local.resData[pMsgContext_Local.resDataLen], gNfcDev.rxBuf.isoDepBuf.apdu, gNfcDev.rxLen);
			pMsgContext_Local.resDataLen = gNfcDev.rxLen;

			SetX(kS_WPC_RQST, On);
			pMsgContext_Local.reqDataIdx = 0u;

			CancelTimer(p_tWaitingDelay3);
			wait_tp_response_timeout_cnt = 0u;
			
			//LocalCan_Tx();
			StartTimer(p_tWaitingDelay4);

			gNfcDev.state = RFAL_NFC_STATE_DATA_SET;
			break;

		/*******************************************************************************/
		case RFAL_NFC_STATE_DEACTIVATION:

			CancelTimer(p_tWaitingDelay3);
			CancelTimer(p_tWaitingDelay4);
			rfalNfcDeactivation();			/* Deactivate current device */

			gNfcDev.state = ((gNfcDev.discRestart) ? RFAL_NFC_STATE_START : RFAL_NFC_STATE_IDLE);
			rfalNfcNfcNotify( gNfcDev.state );		/* Notify caller             */
            break;

		/*******************************************************************************/
		case RFAL_NFC_STATE_ACTIVATED:
		default:
			return;
	}
}


/*******************************************************************************/
ReturnCode rfalNfcDataExchangeStart( uint8_t *txData, uint16_t txDataLen, uint8_t **rxData, uint16_t **rvdLen )
{
	ReturnCode            err;
	//rfalTransceiveContext ctx;

	/*******************************************************************************/
	/* The Data Exchange is divided in two different moments, the trigger/Start of *
	 *  the transfer followed by the check until its completion                    */
	if( (gNfcDev.state >= RFAL_NFC_STATE_ACTIVATED) && (gNfcDev.activeDev != NULL) )
	{
        
		/*******************************************************************************/
		/* In Listen mode is the Poller that initiates the communicatation             */
		/* Assign output parameters and rfalNfcDataExchangeGetStatus will return       */
		/* incoming data from Poller/Initiator                                         */
		if( (gNfcDev.state == RFAL_NFC_STATE_ACTIVATED) && rfalNfcIsRemDevPoller( gNfcDev.activeDev->type ) )
		{
			if( txDataLen > 0U )
			{
				return ERR_WRONG_STATE;
			}

			*rvdLen = (uint16_t*)&gNfcDev.rxLen;
			*rxData = (uint8_t*)((gNfcDev.activeDev->rfInterface == RFAL_NFC_INTERFACE_ISODEP) ? gNfcDev.rxBuf.isoDepBuf.apdu : 
								((gNfcDev.activeDev->rfInterface == RFAL_NFC_INTERFACE_NFCDEP) ? gNfcDev.rxBuf.nfcDepBuf.pdu  : gNfcDev.rxBuf.rfBuf));
			return ERR_NONE;
		}

		/*******************************************************************************/
		switch( gNfcDev.activeDev->rfInterface )		/* Check which RF interface shall be used/has been activated */
		{
			case RFAL_NFC_INTERFACE_ISODEP:
			{
				rfalIsoDepApduTxRxParam isoDepTxRx;

				if( txDataLen > sizeof(gNfcDev.txBuf.isoDepBuf.apdu) )
				{
					return ERR_NOMEM;
				}

				if( txDataLen > 0U )
				{
					ST_MEMCPY( (uint8_t*)gNfcDev.txBuf.isoDepBuf.apdu, txData, txDataLen );
				}

				isoDepTxRx.DID          = RFAL_ISODEP_NO_DID;
				isoDepTxRx.ourFSx       = RFAL_ISODEP_FSX_KEEP;
				isoDepTxRx.FSx          = gNfcDev.activeDev->proto.isoDep.info.FSx;
				isoDepTxRx.dFWT         = gNfcDev.activeDev->proto.isoDep.info.dFWT;
				isoDepTxRx.FWT          = gNfcDev.activeDev->proto.isoDep.info.FWT;
				isoDepTxRx.txBuf        = &gNfcDev.txBuf.isoDepBuf;
				isoDepTxRx.txBufLen     = txDataLen;
				isoDepTxRx.rxBuf        = &gNfcDev.rxBuf.isoDepBuf;
				isoDepTxRx.rxLen        = &gNfcDev.rxLen;
				isoDepTxRx.tmpBuf       = &gNfcDev.tmpBuf.isoDepBuf;
				*rxData                 = (uint8_t*)gNfcDev.rxBuf.isoDepBuf.apdu;
				*rvdLen                 = (uint16_t*)&gNfcDev.rxLen;

				/*******************************************************************************/
				/* Trigger a RFAL ISO-DEP Transceive                                           */
				err = rfalIsoDepStartApduTransceive( isoDepTxRx );
				break;
			}
			/*******************************************************************************/
			default:
				err = ERR_PARAM;
				break;
		}

		return err;
	}

	return ERR_WRONG_STATE;
}


/*******************************************************************************/
ReturnCode rfalNfcDataExchangeGetStatus( void )
{
	/*******************************************************************************/
	/* Check if it's the first frame received in Listen mode */
	if( gNfcDev.state == RFAL_NFC_STATE_ACTIVATED )
	{
		/* Continue data exchange as normal */
		gNfcDev.dataExErr = ERR_BUSY;
		gNfcDev.state     = RFAL_NFC_STATE_DATAEXCHANGE_CHECK;
	}

	/*******************************************************************************/    
	/* Check if Data exchange has been started */
	if( (gNfcDev.state != RFAL_NFC_STATE_DATAEXCHANGE_CHECK) )
	{
		return ERR_WRONG_STATE;
	}

	/* Check if Data exchange is still ongoing */
	if( gNfcDev.dataExErr == ERR_BUSY )
	{
		switch( gNfcDev.activeDev->rfInterface )
		{
			/*******************************************************************************/
			case RFAL_NFC_INTERFACE_ISODEP:
				gNfcDev.dataExErr = rfalIsoDepGetApduTransceiveStatus();
				break;

			/*******************************************************************************/
			default:
				gNfcDev.dataExErr = ERR_PARAM;
				break;
		}
	}

	return gNfcDev.dataExErr;
}


/*!
 ******************************************************************************
 * \brief Poller Technology Detection
 * 
 * This method implements the Technology Detection / Poll for different 
 * device technologies.
 * 
 * \return  ERR_NONE         : Operation completed with no error
 * \return  ERR_BUSY         : Operation ongoing
 * \return  ERR_XXXX         : Error occurred
 * 
 ******************************************************************************
 */
static ReturnCode rfalNfcPollTechDetetection( void )
{
	ReturnCode err;

	err = ERR_NONE;

	/* Supress warning when specific RFAL features have been disabled */
	NO_WARNING(err);

	/*******************************************************************************/
	/* Passive NFC-A Technology Detection                                          */
	/*******************************************************************************/
	if( ((gNfcDev.disc.techs2Find & RFAL_NFC_POLL_TECH_A) != 0U) && ((gNfcDev.techs2do & RFAL_NFC_POLL_TECH_A) != 0U) )
	{
		rfalNfcaSensRes sensRes;

		if( !gNfcDev.isTechInit )
		{
			EXIT_ON_ERR( err, rfalNfcaPollerInitialize() );			/* Initialize RFAL for NFC-A */
			EXIT_ON_ERR( err, rfalFieldOnAndStartGT() );			/* Turns the Field On and starts GT timer */
			gNfcDev.isTechInit = true;
		}

		if( rfalIsGTExpired() )					/* Wait until Guard Time is fulfilled */
		{
			err = rfalNfcaPollerTechnologyDetection( gNfcDev.disc.compMode, &sensRes );	/* Poll for NFC-A devices */
			if( err == ERR_NONE )
			{
				gNfcDev.techsFound = RFAL_NFC_POLL_TECH_A;

				return ERR_NONE;
			}

#if ECP_ENABLE
			gNfcDev.techs2do  &= ~RFAL_NFC_POLL_TECH_A;		/* Added DK 2.0 */
#endif
		}

		return ERR_BUSY;
	}

	/*******************************************************************************/
	/* Send VASUP poll comand		Added DK 2.0								   */
	/*******************************************************************************/
	if( ((gNfcDev.disc.techs2Find & RFAL_NFC_POLL_TECH_PROPA) != 0U) && ((gNfcDev.techs2do & RFAL_NFC_POLL_TECH_PROPA) != 0U) )
	{
#if ECP_ENABLE
		rfalNfcaSensRes sensRes;
		
		/* Send user defined proprietary poll comand */
		err = rfalTransceiveBlockingTxRx( (uint8_t*)&gNfcDev.disc.propAPoll, gNfcDev.disc.propAPollLen, (uint8_t*)&sensRes, sizeof(rfalNfcaSensRes), NULL, RFAL_TXRX_FLAGS_DEFAULT, rfalConvMsTo1fc(1) );
		if( (err == ERR_NONE) || (err == ERR_CRC) || (err == ERR_PAR) || (err == ERR_NOMEM) )
		{
			gNfcDev.techsFound = (RFAL_NFC_POLL_TECH_A | RFAL_NFC_POLL_TECH_PROPA);
		}

		gNfcDev.techs2do &= ~RFAL_NFC_POLL_TECH_PROPA;

		//return ERR_BUSY;
#endif
	}

	return ERR_NONE;
}


/*!
 ******************************************************************************
 * \brief Poller Collision Resolution
 * 
 * This method implements the Collision Resolution on all technologies that
 * have been detected before.
 * 
 * \return  ERR_NONE         : Operation completed with no error
 * \return  ERR_BUSY         : Operation ongoing
 * \return  ERR_XXXX         : Error occurred
 * 
 ******************************************************************************
 */
static ReturnCode rfalNfcPollCollResolution( void )
{
	uint8_t i;
	static uint8_t devCnt;
	ReturnCode err;

	err = ERR_NONE;
	i = 0;

	/* Supress warning when specific RFAL features have been disabled */
	NO_WARNING(err);
	NO_WARNING(devCnt);
	NO_WARNING(i);

	/* Check if device limit has been reached */
	if( gNfcDev.devCnt >= gNfcDev.disc.devLimit )
	{
		return ERR_NONE;
	}

	/*******************************************************************************/
	/* NFC-A Collision Resolution                                                  */
	/*******************************************************************************/
	if( ((gNfcDev.techsFound & RFAL_NFC_POLL_TECH_A) != 0U) && ((gNfcDev.techs2do & RFAL_NFC_POLL_TECH_A) != 0U) )   /* If a NFC-A device was found/detected, perform Collision Resolution */
	{
		static rfalNfcaListenDevice nfcaDevList[RFAL_NFC_MAX_DEVICES];

		if( !rfalIsGTExpired() )
		{
			return ERR_BUSY;
		}

		if( !gNfcDev.isOperOngoing )
		{
			EXIT_ON_ERR( err, rfalNfcaPollerStartFullCollisionResolution( gNfcDev.disc.compMode, (gNfcDev.disc.devLimit - gNfcDev.devCnt), nfcaDevList, &devCnt ) );

			gNfcDev.isOperOngoing = true;
			return ERR_BUSY;
		}

		err = rfalNfcaPollerGetFullCollisionResolutionStatus();
		if( err != ERR_BUSY )
		{
			if( (err == ERR_NONE) && (devCnt != 0U) )
			{
				for( i=0; i<devCnt; i++ )		/* Copy devices found form local Nfca list into global device list */
				{
					gNfcDev.devList[gNfcDev.devCnt].type     = RFAL_NFC_LISTEN_TYPE_NFCA;
					gNfcDev.devList[gNfcDev.devCnt].dev.nfca = nfcaDevList[i];
					gNfcDev.devList[gNfcDev.devCnt].dev.nfca.propA = ((gNfcDev.techsFound & RFAL_NFC_POLL_TECH_PROPA) != 0U);			/* Added DK 2.0 */
					gNfcDev.devCnt++;
				}
			}
		}

		return ERR_BUSY;
	}

	return ERR_NONE;			/* All technologies have been performed */
}


/*!
 ******************************************************************************
 * \brief Poller Activation
 * 
 * This method Activates a given device according to it's type and 
 * protocols supported
 *  
 * \param[in]  devIt : device's position on the list to be activated 
 * 
 * \return  ERR_NONE         : Operation completed with no error
 * \return  ERR_BUSY         : Operation ongoing
 * \return  ERR_XXXX         : Error occurred
 * 
 ******************************************************************************
 */
static ReturnCode rfalNfcPollActivation( uint8_t devIt )
{
	ReturnCode err;

	err = ERR_NONE;

	/* Supress warning when specific RFAL features have been disabled */
	NO_WARNING(err);

	if( devIt > gNfcDev.devCnt )
	{
		return ERR_WRONG_STATE;
	}

	switch( gNfcDev.devList[devIt].type )
	{
		/*******************************************************************************/
		case RFAL_NFC_LISTEN_TYPE_NFCA:

			if( gNfcDev.devList[devIt].dev.nfca.isSleep )		/* Check if desired device is in Sleep */
			{
				rfalNfcaSensRes sensRes;
				rfalNfcaSelRes  selRes;

				if( !gNfcDev.isOperOngoing )
				{
					/* Wake up all cards  */
					EXIT_ON_ERR( err, rfalNfcaPollerCheckPresence( RFAL_14443A_SHORTFRAME_CMD_WUPA, &sensRes ) ); 
					gNfcDev.isOperOngoing = true;
				}
				else
				{
					/* Select specific device */
					EXIT_ON_ERR( err, rfalNfcaPollerSelect( gNfcDev.devList[devIt].dev.nfca.nfcId1, gNfcDev.devList[devIt].dev.nfca.nfcId1Len, &selRes ) ); 
					gNfcDev.devList[devIt].dev.nfca.isSleep = false;
					gNfcDev.isOperOngoing = false;
				}
				return ERR_BUSY;
			}

			/* Set NFCID */
			gNfcDev.devList[devIt].nfcid    = gNfcDev.devList[devIt].dev.nfca.nfcId1;
			gNfcDev.devList[devIt].nfcidLen = gNfcDev.devList[devIt].dev.nfca.nfcId1Len;

			/*******************************************************************************/
			/* Perform protocol specific activation                                        */
			/*******************************************************************************/
			switch( gNfcDev.devList[devIt].dev.nfca.type )
			{
				/*******************************************************************************/
				case RFAL_NFCA_T4T:			/* Device supports ISO-DEP */

					if( !gNfcDev.isOperOngoing )
					{
						/* Perform ISO-DEP (ISO14443-4) activation: RATS and PPS if supported */
						rfalIsoDepInitialize();                    
						EXIT_ON_ERR( err, rfalIsoDepPollAStartActivation( (rfalIsoDepFSxI)RFAL_ISODEP_FSDI_DEFAULT, RFAL_ISODEP_NO_DID, gNfcDev.disc.maxBR, &gNfcDev.devList[devIt].proto.isoDep ) );

						gNfcDev.isOperOngoing = true;
						return ERR_BUSY;
					}

					err = rfalIsoDepPollAGetActivationStatus();
					if( err != ERR_NONE )
					{
						return err;
					}

					gNfcDev.devList[devIt].rfInterface = RFAL_NFC_INTERFACE_ISODEP;		/* NFC-A T4T device activated */

					break;
				/*******************************************************************************/
				default:
					return ERR_WRONG_STATE;
			}
			break;
		/*******************************************************************************/
		default:
			return ERR_WRONG_STATE;
	}

	gNfcDev.activeDev = &gNfcDev.devList[devIt];			/* Assign active device to be used further on */
	return ERR_NONE;
}


/*!
 ******************************************************************************
 * \brief Poller NFC Deactivate
 * 
 * This method Deactivates the device if a deactivation procedure exists 
 * 
 * \return  ERR_NONE  : Operation completed with no error
 * \return  ERR_BUSY  : Operation ongoing
 * \return  ERR_XXXX  : Error occurred
 * 
 ******************************************************************************
 */
static ReturnCode rfalNfcDeactivation( void )
{
	/* Check if a device has been activated */
	if( gNfcDev.activeDev != NULL )
	{
		if( rfalNfcIsRemDevListener( gNfcDev.activeDev->type ) )		/* Listen mode no additional deactivation to be performed*/
		{
			switch( gNfcDev.activeDev->rfInterface )
			{
				/*******************************************************************************/
				case RFAL_NFC_INTERFACE_RF:
					break;					/* No specific deactivation to be performed */

				/*******************************************************************************/
				case RFAL_NFC_INTERFACE_ISODEP:
					rfalIsoDepDeselect();	/* Send a Deselect to device */
					break;

				/*******************************************************************************/
				default:
					return ERR_REQUEST;
			}
		}
	}

	rfalFieldOff();
	 
	gNfcDev.activeDev = NULL;
	return ERR_NONE;
}



