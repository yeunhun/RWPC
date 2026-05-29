/*******************************************************************************
**  (C) 2013 Hyundai AUTRON Company                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: CanTp_IntTypes.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanTp                                                 **
**                                                                            **
**  PURPOSE   : To provide CanTp structure type definitions                   **
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
** 1.11.0    24-Nov-2020   SM Kwon        Redmine #26036                      **
** 1.10.2    03-Nov-2020   SM Kwon        Redmine #25248                      **
** 1.10.1    07-Oct-2019   SM Kwon        Redmine #19617                      **
** 1.9.0     11-Jul-2019   SM Kwon        Redmine #16557                      **
** 1.8.1     12-Mar-2019   SM Kwon        Redmine #14001, #15962              **
** 1.8.0     21-Mar-2018   Lim Jong Sun   Redmine #11554                      **
** 1.7.7     02-May-2016   Lim Jong Sun   Redmine #4803                       **
** 1.7.3     25-Aug-2015   Lim Jong Sun   Redmine #2786                       **
** 1.0.0     21-Mar-2013   Lim Jong Sun   Initial Version                     **
*******************************************************************************/

#ifndef CANTP_INTTYPES_H
#define CANTP_INTTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp.h"                /* Configuration header file */
#include "SchM_CanTp.h"           /* SchM header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANTP_INTTYPES_AR_RELEASE_MAJOR_VERSION    4
#define CANTP_INTTYPES_AR_RELEASE_MINOR_VERSION    0
#define CANTP_INTTYPES_AR_RELEASE_REVISION_VERSION 3

/* CANTP software version information */
#define CANTP_INTTYPES_SW_MAJOR_VERSION            1
#define CANTP_INTTYPES_SW_MINOR_VERSION            11

/*******************************************************************************
**                      Pre-Compile Options                                   **
*******************************************************************************/

/*******************************************************************************
**                       Global Symbols                                      **
*******************************************************************************/
#define CANTP_ZERO                     0x00
#define CANTP_ONE                      0x01
#define CANTP_TWO                      0x02
#define CANTP_THREE                    0x03
#define CANTP_FOUR                     0x04
#define CANTP_FIVE                     0x05
#define CANTP_SIX                      0x06
#define CANTP_SEVEN                    0x07
#define CANTP_EIGHT                    0x08
#define CANTP_NINE                     0x09
#define CANTP_TEN                      0x0A
#define CANTP_SIXTEEN                  0x10
#define CANTP_TWENTYFOUR               0x18
#define CANTP_THIRTY                   0x1E  /* 30 bytes */
#define CANTP_THIRTYONE                0x1F  /* 31 bytes */
#define CANTP_THIRTYTWO                0x20  /* 32 bytes */
#define CANTP_SIXTYTWO                 0x3E  /* 62 bytes */
#define CANTP_SIXTYTHREE               0x3F  /* 63 bytes */
#define CANTP_SIXTYFOUR                0x40  /* 64 bytes */
#define CANTP_FOURZERONINEFIVE         0xFFF /* 4095 bytes */

#define CANTP_CF_PCI_BYTES             0x01

#define CANTP_MAX_SDU_LENGTH           ((uint16) 4095) /* Allowed Max SDU
                                                        * length */

#define CANTP_PHYSICAL_ADDRESS         0x00 /* Physical Communication*/
#define CANTP_FUNCTIONAL_ADDRESS       0x01 /* Functional Communication*/
#define CANTP_CANFD_PHYSICAL_ADDRESS   0x02 /* Physical Communication for FD */
#define CANTP_CANFD_FUNCTIONAL_ADDRESS 0x03 /* Functional Communication for FD */

/* CanTp Addressing Mode */
#define CANTP_STANDARD_ADDRESS         0x00 /* Standard Addressing Mode*/

/* CanTp Frame PCI Byte */
#define CANTP_PCI_MASK                 0xF0 /* Mask to Extract PCI */
#define CANTP_SF_PCI                   0x00 /* Single Frame PCI InfoByte */
#define CANTP_FD_SF_PCI                0x00FF/*Single Frame PCI InfoByte for FD*/
#define CANTP_FF_PCI                   0x10 /* First Frame PCI InfoByte */
#define CANTP_CF_PCI                   0x20 /* Consecutive Frame PCI InfoByte
                                            **/
#define CANTP_FC_PCI                   0x30 /* Flow control PCI InfoByte*/
#define CANTP_FS_MASK                  0x0F /* Flow Status mask*/

#define CANTP_FD_SF_FIRST              0x00 /* Single Frame PCI InfoByte#1*/
#define CANTP_FD_FF_FIRST              0x10 /* First Frame PCI InfoByte#1*/
#define CANTP_FD_FF_SECOND             0x00 /* First Frame PCI InfoByte#2*/

/* Confirm States */
#define CANTP_TX_CONF_IDLE             0x00 /* Ideal Tx Confirmation State */
#define CANTP_SF_LF_TX_CONF            0x01 /* Indicates SF or last Frame
                                             *    Tx Confirmation*/
#define CANTP_CF_TX_CONF               0x02 /* Indicates CF Tx Confirmation*/
#define CANTP_FC_TX_CONF               0x03 /* Indicates FC Tx Confirmation*/
#define CANTP_LAST_CF_TX_CONF          0x04 /* Tx Confirmation for FF or last
                                             * CF in a block received */

/* Buffer States */
#define CANTP_TX_NOTRDY                0x00 /* Ideal Tx Buffer State */
#define CANTP_TX_RDY                   0x01 /* Ideal Tx Buffer available */
#define CANTP_TX_NOTRDY_INITREQ        0x02 /* Indicates Tx Buffer Busy */
#define CANTP_RX_NOTRDY_INITREQ        0x04 /* Indicates Rx Buffer unavailable
                                            **/
#define CANTP_RX_RDY                   0x05 /* Indicates Rx Buffer available */
#define CANTP_RX_NOTRDY                0x07 /* Indicates Rx Buffer to be
                                             *   requested */

/* Channel States */
#define CANTP_WAIT                     0x00 /* Ideal Channel State */
#define CANTP_TX_NORMAL                0x01 /* Frame is in Transmit process */
#define CANTP_RX_FC                    0x02 /* Waiting for Rx indication for
                                             *   FC */
#define CANTP_RX_NORMAL                0x03 /* Frame is in receive process */
#define CANTP_FC_TXCONF                0x04 /* Frame is in Transmit FC process
                                            **/
#define CANTP_RX_CF                    0x05 /* Frame is in RX CF process */
#define CANTP_RXBUF_WAIT               0x06 /* Waiting for receive buffer */
#define CANTP_MAX_TX_STATE             0x02 /* If channel state is greater
                                             *   than*/

/*
 * this state then Communication is
 * for reception
 */

#define CANTP_FS_CTS                   0x00 /* Flow Status is Continue To
                                             * Send*/
#define CANTP_FS_WT                    0x01 /* Flow Status is WAIT*/
#define CANTP_FS_OVFLW                 0x02 /* Flow Status is OverFlow*/

#define CANTP_TRUE                     ((boolean) 0x01)
#define CANTP_FALSE                    ((boolean) 0x00)

#define CANTP_NAS_TIMER                0x00 /* To access timer array for NAS*/
#define CANTP_NBS_TIMER                0x01 /* To access timer array for NBS*/
#define CANTP_NCS_TIMER                0x02 /* To access timer array for NCS*/
#define CANTP_MAX_FRAME_COUNTER        0x0F /* Max allowed frames */
#define CANTP_NAR_TIMER                0x00 /* To access timer array for NAR*/
#define CANTP_NBR_TIMER                0x01 /* To access timer array for NBR*/
#define CANTP_NCR_TIMER                0x02 /* To access timer array for NCR*/

#define CANTP_STMIN                    0x00 /* To identify STMIN in
                                             * ChangeParameter request */
#define CANTP_BS                       0x01 /* To identify BS in
                                             * ChangeParameter request */

#define CANTP_STMIN_DIRECT_VALUE_RANGE 0x7F /* Indicates STMIN in 0-127ms */

#define CANTP_STMIN_US_LOW             0xF1 /* Indicates STMIN in 100microsec
                                            **/
#define CANTP_STMIN_US_HIGH            0xF9 /* Indicates STMIN in 900microsec
                                            **/
#define CANTP_STMIN_MAP_MASK           0x0F /*Mask to access STMin Maping
                                             * Array*/
#define CANTP_MAX_STMIN_DELAY          0x7F /* Max STMIN 127ms */

#define CANTP_FF_LEN_MASK              0x0F /* First Frame Length Mask */

#define CANTP_FF_ESCAPE_FIRST_BYTE_LOW_NIBBLE_MASK           0x0F /* First Frame Escape Bit Mask */

#define CANTP_MAX_BS_VAL               0xFF /* Max Block size*/
#define CANTP_INFINITE_BS              0x1000 /* If Bs is 0, set BS to CANTP_INFINITE_BS */

#define CANTP_INVALID                  ((uint8) 0xFF)

/*First frame or successive frame */
#define CANTP_TX_SFORFF                0xFF /* Indicates FF or Single frame */
#define CANTP_CONSCFRAME               0x00 /* Indicates Consecutive frame */
#define CANTP_MAX_STMINBS_VAL          0xFF /* Upper limit for Blocksize or
                                             * STMIN */
                                             
#if(CANTP_START_OF_RECPT_FOUR_ONE_ONE == STD_ON)
#define NTFRSLT_E_NOT_OK_STARTOFRECP   (uint8)0x5E
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
typedef enum 
{
  CANTP_MODE_FULL_DUPLEX = 0,
  CANTP_MODE_HALF_DUPLEX
} CanTp_ChannelMode;


typedef struct 
{
  uint8 prevDiscreteLength;
  uint8 curDiscreteLength;
} CanTp_DiscreteLength;

/* Structure for Channel RAM variables */
typedef struct 
{
  /* Pointer given to Upper layer buffer while Tx*/
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) pUpLayerBuffPtr;
  
  /* PduId in Process */
  PduIdType ddActivePduId;

  /* SduLength in process */
  PduLengthType ddSduLength;
  #if (CANTP_RX_NSDU == STD_ON)

  /* Available Buffer length provided for Rx*/
  uint16 usAvlBuffLength;
  #endif

  /* Number of bytes remaining for Tx or Rx*/
  uint16 usByteCounter;
  #if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)

  /* To hold the max configured wait flow control frame to be transmitted */
  uint16 usRxWftMax;
  #endif

  /* Local Buffer to hold eight bytes*/
  #if (CANTP_FD_SUPPORT == STD_ON)
  uint8 aaDataBuffer[CANTP_SIXTYFOUR];
  #else /*(CANTP_FD_SUPPORT == STD_ON)*/
  uint8 aaDataBuffer[CANTP_EIGHT];
  #endif /*(CANTP_FD_SUPPORT == STD_ON)*/

  /* To hold CanTp individual channel state */
  uint8 ucChannelState;

  /* To hold the position from where data bytes to be processed */
  uint8 ucLocalDataByteIndex;

  /* To hold the position of PCI Byte */
  uint8 ucCurrentBytePosition;
  #if ((CANTP_TX_PHYSICAL_ADDRESSING == STD_ON) ||\
  (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON))

  /* To hold the CF sequence number */
  uint8 ucFrameCounter;
  #endif

  /* To hold the Tx Confirmation State */
  uint8 ucTxConfirmState;

  /*To hold the provided buffer status */
  uint8 ucBufferState;
  #if ((CANTP_TX_PHYSICAL_ADDRESSING == STD_ON) ||\
  (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON))

  /*To hold the Block size of Flow control frame*/
  uint16 usBSVar;
  #endif

  /* To hold the Flowstatus of Flow control frame*/
  uint8 ucFlowStatus;
  #if (CANTP_TX_PHYSICAL_ADDRESSING == STD_ON)

  /* To hold the STMin of Flow control frame*/
  uint8 ucStMinValue;
  #endif

  /* To hold the SF or FF or CF length */
  uint8 ucCurrentFrameLen;

  /* To indicate the SF or FF */
  uint8 ucNewFrameFlag;

  /* To indicate the SF or CF or FF*/
  uint8 ucFrameType;
} CanTp_ChannelRam;

#if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)

/* Rx Nsdu RAM structure */
typedef struct 
{
  /* Maximum number of N-PDUs the CanTp receiver allows the sender to send */
  uint16 usBlockSize;

  /* Separation  time between the transmissions of two CF N-PDU */
  uint8 ucSTMin;
} CanTp_STminBs;
#endif /* (CANTP_RX_PHYSICAL_ADDRESSING) */

#if (CANTP_TX_NSDU == STD_ON)

/* Tx Nsdu structure for static parameters */
typedef struct 
{
  /* Channel Id */
  CanTp_ChannelType ddChannelId;

  /* Pdu Length */
  uint16 usTxSduLength;
  
  /* Target address Type, '0'-Physical addressing, '1'- Functional addressing */
  uint8 ucTaType;
  #if ((CANTP_TX_EXTENDED_ADDRESS == STD_ON) ||\
  (CANTP_TX_MIXED_ADDRESS == STD_ON))

  /* Addressing mode, '0' - normal addressing, '1' - extended addressing,
   * '2' - Mixed addressing */
  uint8 ucAddressingMode;

  /* Nta or Nae value */
  uint8 ucNTaOrNAeValue;
  #endif /* End of if ((CANTP_TX_EXTENDED_ADDRESS == STD_ON) ||
          *(CANTP_TX_MIXED_ADDRESS == STD_ON)) */
  #if (CANTP_TX_SDU_PADDING_ACTIVATION == STD_ON)

  /* Padding action, 'TRUE' - Padding activation is STD_ON
   * 'FALSE' - Padding activation is off  */
  boolean blTxPaddingActivation;
  #endif

  uint8 ucTxSduMaxLength;
} CanTp_TxNsduStatic;
#endif /* End of if (CANTP_TX_NSDU == STD_ON) */

#if (CANTP_RX_NSDU == STD_ON)

/* Rx Nsdu structure for static parameters */
typedef struct 
{
  /* Channel Id */
  CanTp_ChannelType ddChannelId;

  /* Sdu Length */
  uint16 usRxSduLength;

  /* Target Address Type */
  uint8 ucTaType;

  #if ((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
  (CANTP_RX_MIXED_ADDRESS == STD_ON))

  /* Addressing mode, '0' - normal addressing, '1' - extended addressing,
   * '2' - Mixed addressing */
  uint8 ucAddressingMode;

  /* Nta or NAe value for Flow Control frame */
  uint8 ucFcNTaOrNAeValue;
  #endif /* End of if ((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||
          *(CANTP_RX_MIXED_ADDRESS == STD_ON)) */
  #if (CANTP_RX_SDU_PADDING_ACTIVATION == STD_ON)

  /* Padding action, 'TRUE' - Padding activation is STD_ON
   * 'FALSE' - Padding activation is off */
  boolean blRxPaddingActivation;
  #endif

  uint8 ucRxSduMaxLength;
} CanTp_RxNsduStatic;
#endif /* End of if (CANTP_RX_NSDU == STD_ON) */

/* The following structure is generated for each receive PDU if it is
 * configured for extended addressing. Incase of Rx FC frames, if the
 * associated Tx PDU is configured for extended addressing this will be
 * generated.*/
#if ((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||\
  (CANTP_RX_MIXED_ADDRESS == STD_ON) || (CANTP_TX_EXTENDED_ADDRESS == STD_ON)\
  || (CANTP_TX_MIXED_ADDRESS == STD_ON))
/* polyspace-begin MISRA-C3:D4.8 [Not a defect:Low] "No Impact of this rule violation" */
typedef struct 
{
  /* If the PDU belongs to the Rx FC then this should be CanTpTxNSduId
   * else this should be index of RxNSduId */
  PduIdType ddSduIndex;
  uint8 ucNSaOrNAe;
} CanTp_RxNSaOrNAeSduMapping;
/* polyspace-end MISRA-C3:D4.8 [Not a defect:Low] "No Impact of this rule violation" */
#endif /* End of if ((CANTP_RX_EXTENDED_ADDRESS == STD_ON) ||
        *(CANTP_RX_MIXED_ADDRESS == STD_ON) || (CANTP_TX_EXTENDED_ADDRESS ==
        * STD_ON) || (CANTP_TX_MIXED_ADDRESS == STD_ON)) */

/* The following structure is used for all the received PDUs which includes (FC)
 * PDUs. This structure will be used only if there is atleast one receive PDU is
 * configured for extended addressing */
typedef struct 
{
  /* If the PDU is configured for extended addressing this parameter should
   * give the number of SDUs the PDU is associated
   * If the PDU is configured for normal addressing this parameter gives either
   * RxSduId (if it is a normal receive frame) or gives the TxSduId (if it is
   * a Flow Control frame) */
  PduIdType ddNoOfPdusOrSduId;

  /* Index to the structure of Nsa and Sdu Mapping
   * If the PDU is not configured for extended addressing this should be
   *   "CANTP_INVALID" */
  PduIdType ddRxNSaOrNAeSduMapIndex;

  /* Addressing mode of the PDU */
  uint8 ucAddressingMode;
} CanTp_RxExtPdus;
/* polyspace:begin<MISRA-C:18.4:Not a defect:Justified> Union used for handling endian conversion */
typedef union 
{
  struct
  {
    /* If the processor is Big endian */
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    uint8 ucMSByte;               /* MS Byte */
    uint8 ucLSByte;               /* LS Byte */
    /* If the processor is Little endian */
    #else
    uint8 ucLSByte;               /* LS Byte */
    uint8 ucMSByte;               /* MS Byte */
    #endif /* End of if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
  } byte_val;

  uint16 usWholeWord;
} CanTp_WordAccess;
/* polyspace:end<MISRA-C:18.4:Not a defect:Justified> Union used for handling endian conversion */
#if (CANTP_TX_NSDU == STD_ON)

/* Tx Nsdu structure for dynamic parameters */
typedef struct 
{
  /* Confirmation SduId used for upper layer */
  PduIdType ddUpConfirmationSduId;

  /* PduId used for lower layer data transfer communication */
  PduIdType ddLoTargetPduId;

  /* Nas timeout value (count) */
  uint16 usNasTimeoutValue;

  #if (CANTP_TX_PHYSICAL_ADDRESSING == STD_ON)

  /* Nbs timeout value (count) */
  uint16 usNbsTimeoutValue;

  /* Ncs timeout value (count) */
  uint16 usNcsTimeoutValue;
  #endif /* End of if (CANTP_TX_PHYSICAL_ADDRESSING == STD_ON) */
} CanTp_TxNSduDynamic;
#endif /* End of if (CANTP_TX_NSDU == STD_ON) */

#if (CANTP_RX_NSDU == STD_ON)

/* Rx Nsdu structure for dynamic parameters*/
typedef struct 
{
  /* PduId used for upper layer communications */
  PduIdType ddUpTargetPduId;

  /* PduId used for lower layer Flow control frame CanTp->CanIf communication */
  #if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)
  PduIdType ddLoTxFcTargetPduId;
  #endif

  #if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)

  /* Nar timeout value (count) */
  uint16 usNarTimeoutValue;
  #endif

  /* Nbr timeout value (count) */
  uint16 usNbrTimeoutValue;

  #if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON)

  /* Ncr timeout value (count) */
  uint16 usNcrTimeoutValue;

  /* RxWftMax */
  uint16 usRxWftMax;
  #endif /* End of if (CANTP_RX_PHYSICAL_ADDRESSING == STD_ON) */
} CanTp_RxNSduDynamic;
#endif /* End of if (CANTP_RX_NSDU == STD_ON) */

/*******************************************************************************
**                      MACROs                                                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:D4.9:Not a defect:Justified> No Impact of this rule violation*/
#define CANTP_TIMER_UPDATE_MACRO(Channel, Timer, TimerValue)\
  do{\
    SchM_Enter_CanTp_TIMER_PROTECTION();\
    CanTp_GaaTimers[(uint8)(Channel)][(uint8)(Timer)] = (uint16)(TimerValue);\
    SchM_Exit_CanTp_TIMER_PROTECTION();\
  }while(0)

#if (STD_ON == CANTP_SINGLE_CHANNEL)
#if (CANTP_FULL_DUPLEX_MODE == STD_ON)
#define CANTP_STOP_ALL_TX_TIMERS(Channel)\
  do{\
    SchM_Enter_CanTp_TIMER_PROTECTION();\
    CanTp_GaaTimers\
    [CanTp_GaaChannelMapping[(uint8)(Channel)]][(uint8)CANTP_ZERO]\
      = (uint16)CANTP_ZERO;\
    CanTp_GaaTimers\
    [CanTp_GaaChannelMapping[(uint8)(Channel)]][(uint8)CANTP_ONE]\
      = (uint16)CANTP_ZERO;\
    CanTp_GaaTimers[CanTp_GaaChannelMapping[(uint8)(Channel)]][CANTP_TWO]\
      = (uint16)CANTP_ZERO;\
    CanTp_GaaStMinTimers[(Channel)] = (uint8)CANTP_ZERO;\
    SchM_Exit_CanTp_TIMER_PROTECTION();\
  }while(0)
#else /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
#define CANTP_STOP_ALL_TX_TIMERS(Channel)\
  do{\
    SchM_Enter_CanTp_TIMER_PROTECTION();\
    CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_ZERO] = (uint16)CANTP_ZERO;\
    CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_ONE] = (uint16)CANTP_ZERO;\
    CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_TWO] = (uint16)CANTP_ZERO;\
    CanTp_GaaStMinTimers[(uint8)(Channel)] = (uint8)CANTP_ZERO;\
    SchM_Exit_CanTp_TIMER_PROTECTION();\
  }while(0)
#endif /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
#else /* End of if (STD_ON == CANTP_SINGLE_CHANNEL) */
#if (CANTP_FULL_DUPLEX_MODE == STD_ON)
#define CANTP_STOP_ALL_TX_TIMERS(Channel)\
  do{\
    SchM_Enter_CanTp_TIMER_PROTECTION();\
    if (CanTp_GaaChannelMode[(uint8)(Channel)] == CANTP_MODE_FULL_DUPLEX)\
    {\
      CanTp_GaaTimers\
      [CanTp_GaaChannelMapping[(uint8)(Channel)]][(uint8)CANTP_ZERO]\
        = (uint16)CANTP_ZERO;\
      CanTp_GaaTimers\
      [CanTp_GaaChannelMapping[(uint8)(Channel)]][(uint8)CANTP_ONE]\
        = (uint16)CANTP_ZERO;\
      CanTp_GaaTimers[CanTp_GaaChannelMapping[(uint8)(Channel)]][CANTP_TWO]\
        = (uint16)CANTP_ZERO;\
    }\
    else\
    {\
      CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_ZERO] = (uint16)CANTP_ZERO;\
      CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_ONE] = (uint16)CANTP_ZERO;\
      CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_TWO] = (uint16)CANTP_ZERO;\
    }\
    CanTp_GaaStMinTimers[(Channel)] = (uint8)CANTP_ZERO;\
    SchM_Exit_CanTp_TIMER_PROTECTION();\
  }while(0)
#else /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
#define CANTP_STOP_ALL_TX_TIMERS(Channel)\
  do{\
    SchM_Enter_CanTp_TIMER_PROTECTION();\
    CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_ZERO] = (uint16)CANTP_ZERO;\
    CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_ONE] = (uint16)CANTP_ZERO;\
    CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_TWO] = (uint16)CANTP_ZERO;\
    CanTp_GaaStMinTimers[(uint8)(Channel)] = (uint8)CANTP_ZERO;\
    SchM_Exit_CanTp_TIMER_PROTECTION();\
  }while(0)
#endif /* End of if (CANTP_FULL_DUPLEX_MODE == STD_ON) */
#endif /* End of if (STD_ON == CANTP_SINGLE_CHANNEL) */

#define CANTP_STOP_ALL_RX_TIMERS(Channel)\
  do{\
    SchM_Enter_CanTp_TIMER_PROTECTION();\
    CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_ZERO] = (uint16)CANTP_ZERO;\
    CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_ONE] = (uint16)CANTP_ZERO;\
    CanTp_GaaTimers[(uint8)(Channel)][(uint8)CANTP_TWO] = (uint16)CANTP_ZERO;\
    SchM_Exit_CanTp_TIMER_PROTECTION();\
  }while(0)
/* polyspace:end<MISRA-C3:D4.9:Not a defect:Justified> No Impact of this rule violation*/
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* CANTP_INTTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

