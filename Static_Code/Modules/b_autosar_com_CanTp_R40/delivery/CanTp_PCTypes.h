/*******************************************************************************
**  (C) 2013 Hyundai AUTRON Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_PCTypes.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanTp                                                 **
**                                                                            **
**  PURPOSE   : To provide precompile configuration specific data types       **
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
** 1.10.2    03-Nov-2020   SM Kwon        Redmine #25248, #24646              **
** 1.10.1    07-Oct-2019   SM Kwon        Redmine #19617                      **
** 1.10.0    10-Sep-2019   SM Kwon        Redmine #19217                      **
** 1.9.0     30-Jul-2019   SM Kwon        Redmine #16557, #16558              **
** 1.8.1     12-Mar-2019   SM Kwon        Redmine #12889, #15962              **
** 1.8.0     21-Mar-2018   Lim Jong Sun   Redmine #11554                      **
** 1.7.10    24-Apr-2015   Lim Jong Sun   Redmine #8152                       **
** 1.7.7     02-May-2016   Lim Jong Sun   Redmine #4803                       **
** 1.7.5     02-Feb-2015   Lim Jong Sun   Redmine #3965                       **
** 1.7.4     14-Oct-2015   Lim Jong Sun   Redmine #3277                       **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

#ifndef CANTP_PCTYPES_H
#define CANTP_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp_IntTypes.h"       /* CanTp Internal types Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANTP_PCTYPES_AR_RELEASE_MAJOR_VERSION    4
#define CANTP_PCTYPES_AR_RELEASE_MINOR_VERSION    0
#define CANTP_PCTYPES_AR_RELEASE_REVISION_VERSION 3

/* File version information */
#define CANTP_PCTYPES_SW_MAJOR_VERSION            1
#define CANTP_PCTYPES_SW_MINOR_VERSION            11

/*******************************************************************************
**                      Pre-Compile Options                                   **
*******************************************************************************/

/*******************************************************************************
**                       Global Symbols                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
  /*
    * TODO: CanTp Library Relase
    * add by jslim
    * 2013.05.29
    */
#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, CANTP_CONST) Cantp_Main_Function_Period;
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, CANTP_CONST) Cantp_Channel_Id;
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, CANTP_CONST) Cantp_Total_Rx_Tx_Channels;
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, CANTP_CONST) CanTp_No_Of_Channels;
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
extern CONST(uint16, CANTP_CONST) Cantp_Maxno_Rx_Npdu;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
extern CONST(uint16, CANTP_CONST) Cantp_Maxno_Rx_Sdu;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
extern CONST(uint16, CANTP_CONST) Cantp_Max_Confirm_Id;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
extern CONST(uint16, CANTP_CONST) Cantp_Max_Indic_Id;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
extern CONST(uint16, CANTP_CONST) Cantp_Max_Tx_Sduid;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
extern CONST(uint16, CANTP_CONST) Cantp_Max_Rx_Sduid;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
extern CONST(uint16, CANTP_CONST) Cantp_Rx_Fcpdu_start;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

#define CANTP_START_SEC_CONST_16
#include "MemMap.h"
extern CONST(uint16, CANTP_CONST) Cantp_Max_Rx_Fcnpduid;
#define CANTP_STOP_SEC_CONST_16
#include "MemMap.h"

/*  polyspace:begin<MISRA-C:8.12:Not a defect:Justified> No Impact of this rule violation */

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(uint8, CANTP_CONST) Cantp_Padding_Byte[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#ifndef INVALID_CHANNELMAPS
#if (CANTP_FULL_DUPLEX_MODE == STD_ON)
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(uint8, CANTP_CONST) CanTp_GaaChannelMapping[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
#endif

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanTp_ChannelType, CANTP_CONST) CanTp_GaaRxSduMap[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanTp_ChannelMode, CANTP_CONST) CanTp_GaaChannelMode[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#if (CANTP_TX_NSDU == STD_ON)
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanTp_TxNsduStatic, CANTP_CONST) CanTp_GaaTxSduStatic[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if (CANTP_RX_NSDU == STD_ON)
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanTp_RxNsduStatic, CANTP_CONST) CanTp_GaaRxSduStatic[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanTp_RxExtPdus, CANTP_CONST) CanTp_GaaRxExtPdus[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#if (CANTP_TX_PHYSICAL_ADDRESSING == STD_ON)
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(uint8, CANTP_CONST) CanTp_GaaSTminMapping[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (CANTP_RX_NSDU == STD_ON)
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanTp_RxNSduDynamic, CANTP_CONST) CanTp_GaaRxSduDynamic[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(uint8, CANTP_CONST) CanTp_GaaBytePos[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#if (CANTP_TX_NSDU == STD_ON)
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanTp_TxNSduDynamic, CANTP_CONST) CanTp_GaaTxSduDynamic[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#ifndef INVALID_RXEXTFCPDUS
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Extended RxNsdu Flow Control ROM array */
extern CONST(CanTp_RxExtPdus, CANTP_CONST) CanTp_GaaRxExtFcPdus[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#ifndef INVALID_NSAORNAESDUMAPPING
#if ((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
  (CANTP_RX_MIXED_ADDRESS == STD_ON) || (CANTP_TX_EXTENDED_ADDRESS == STD_ON)\
  || (CANTP_TX_MIXED_ADDRESS == STD_ON))
#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Nsa and Sdu Mapping */
extern CONST(CanTp_RxNSaOrNAeSduMapping, CANTP_CONST)
CanTp_GaaNSaOrNAeSduMapping[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* End of if ((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||
        *(CANTP_RX_MIXED_ADDRESS == STD_ON) || (CANTP_TX_EXTENDED_ADDRESS ==
        * STD_ON) || (CANTP_TX_MIXED_ADDRESS == STD_ON)) */
#endif
  
#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(CanTp_ChannelRam, CANTP_VAR) CanTp_GaaChannelRam[];
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(uint16, CANTP_VAR) CanTp_GaaTimers[][CANTP_THREE];
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
extern VAR(uint8, CANTP_VAR) CanTp_GaaStMinTimers[];
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANTP_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)
extern VAR(CanTp_STminBs, CANTP_VAR) CanTp_GaaSTminBs[];
#endif
#define CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanTp_DiscreteLength, CANTP_CONST) Cantp_GaaDiscreteLength[];
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* polyspace:end<MISRA-C:8.12:Not a defect:Justified> No Impact of this rule violation */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* CANTP_PCTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

