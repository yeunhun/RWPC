/*******************************************************************************
**  (C) 2013 Hyundai AUTRON Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_Config.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : CanTp Library Relase.                                         **
**                                                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.10.2    05-Nov-2020   SM Kwon        Redmine #24646                      **
** 1.10.1    16-Oct-2019   SM Kwon        Redmine #19617                      **
** 1.10.0    10-Sept-2019  SM Kwon        Redmine #19217                      **
** 1.9.0     12-Jul-2019   SM Kwon        Redmine #16557 ,#16558              **
** 1.8.1     12-Mar-2019   SM Kwon        Redmine #15962                      **
** 1.8.0     21-Mar-2018   Lim Jong Sun   Redmine #11554                      **
** 1.7.11    19-Dec-2017   Lim Jong Sun   Redmine #10454                      **
** 1.7.10    24-Apr-2015   Lim Jong Sun   Redmine #8152                       **
** 1.7.5     02-Feb-2015   Lim Jong Sun   Redmine #3965                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Platform_Types.h"
#include "CanTp_Cfg.h"
#include "CanTp_PCTypes.h"

/*******************************************************************************
**            Variable for Library                  **
*******************************************************************************/
#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
CONST(uint8, CANTP_CONST) Cantp_Main_Function_Period = CANTP_MAIN_FUNCTION_PERIOD;
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
CONST(uint8, CANTP_CONST) Cantp_Channel_Id = CANTP_CHANNEL_ID;
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
CONST(uint8, CANTP_CONST) Cantp_Total_Rx_Tx_Channels = CANTP_TOTAL_RX_TX_CHANNELS;
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
CONST(uint8, CANTP_CONST) CanTp_No_Of_Channels = CANTP_NO_OF_CHANNELS;
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(uint8, CANTP_CONST) Cantp_Padding_Byte[CANTP_SIXTEEN] = {CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, 
                                                               CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, 
                                                               CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE,
                                                               CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE, CANTP_PADDING_BYTE};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
CONST(uint16, CANTP_CONST) Cantp_Maxno_Rx_Npdu = CANTP_MAXNO_RX_NPDU;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
CONST(uint16, CANTP_CONST) Cantp_Maxno_Rx_Sdu = CANTP_MAXNO_RX_SDU;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
CONST(uint16, CANTP_CONST) Cantp_Max_Confirm_Id = CANTP_MAX_CONFIRM_ID;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
CONST(uint16, CANTP_CONST) Cantp_Max_Indic_Id = CANTP_MAX_INDIC_ID;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
#ifndef CANTP_MAX_TX_SDUID
#define CANTP_MAX_TX_SDUID 0
#endif
CONST(uint16, CANTP_CONST) Cantp_Max_Tx_Sduid = CANTP_MAX_TX_SDUID;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
#ifndef CANTP_MAX_RX_SDUID
#define CANTP_MAX_RX_SDUID 0
#endif
CONST(uint16, CANTP_CONST) Cantp_Max_Rx_Sduid = CANTP_MAX_RX_SDUID;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
#ifndef CANTP_RX_FCPDU_START
#define CANTP_RX_FCPDU_START 0
#endif
CONST(uint16, CANTP_CONST) Cantp_Rx_Fcpdu_start = CANTP_RX_FCPDU_START;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
#ifndef CANTP_MAX_RX_FCNPDUID
#define CANTP_MAX_RX_FCNPDUID 0
#endif
CONST(uint16, CANTP_CONST) Cantp_Max_Rx_Fcnpduid = CANTP_MAX_RX_FCNPDUID;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(CanTp_DiscreteLength, CANTP_CONST) Cantp_GaaDiscreteLength[CANTP_SEVEN]
      = {{9, 12}, {12, 16}, {16, 20}, {20, 24}, {24, 32}, {32, 48}, {48, 64}};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

