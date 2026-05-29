/***********************************************************************************************************************
 * File Name		:
 * Description		: 
 * Hex File Name	: 
 * Date				: 
 * Version			: 
***********************************************************************************************************************/
#if 1

#include "WPCEepControl.h"
#include "Data.h"
#include "define.h"
#include "WPCVehicleOption.h"


#include "app_input_type.h"
#include "app_input.h"

#include "WPCTimer.h"

#include "WPCI2CControl.h"
#include "WPCPWMControl.h"

#include "WPCP9450Update.h"



//extern uint8 b_UpdateFlashCmd;
uint8 b_UpdateFlashCmd = Off;
e_EraseFlashCtrl reprog_state = EraseFlashCtrl_Start;

e_EraseFlashCtrl sts_EraseFlashCtrl = EraseFlashCtrl_Start;
uint16 EraseFlashCmdCnt = 0u;
uint16 WriteFlashCmdCnt = 0u;
uint16 VerityFlashCmdCnt = 0u;
uint16 IdReqCmdCnt = 0x00u;
tTimer16 Timer_EraseDelay = {Off, 0u};

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
uint8 p9450_auto_reprog_mode_f = 0u;
uint8 wpc_ecu_reset_f = 0u;
uint8 p9450_auto_reprog_retry_f = 0u;

void set_wpc_ecu_reset(void)
{
  wpc_ecu_reset_f = 1u;
}

void clr_wpc_ecu_reset(void)
{
  wpc_ecu_reset_f = 0u;
}

uint8 get_wpc_ecu_reset(void)
{
  return wpc_ecu_reset_f;
}

void Set_p9450_Auto_Reprog_Retry_Ready(void)
{
  p9450_auto_reprog_retry_f = 1;
}

void Set_p9450_Auto_Reprog_Retry_Start(void)
{
  p9450_auto_reprog_retry_f = 2;
}

void Clr_p9450_auto_reprog_retry(void)
{
  p9450_auto_reprog_retry_f = 0;
}

uint8 Get_p9450_auto_reprog_retry(void)
{
  return p9450_auto_reprog_retry_f;
}



uint8 set_p9450_auto_reprog_ready(void)
{
  p9450_auto_reprog_mode_f = 1u;
}

uint8 clr_p9450_auto_reprog_ready(void)
{
  p9450_auto_reprog_mode_f = 0u;
}

uint8 get_p9450_auto_reprog_ready(void)
{
  return p9450_auto_reprog_mode_f;
}


void set_p9450_auto_reprog_start(void)
{
  b_UpdateFlashCmd = On;
}

void set_p9450_auto_reprog_stop(void)
{
  b_UpdateFlashCmd = Off;
}

uint8 Get_p9450_auto_reprog_on_off_status(void)
{
  return b_UpdateFlashCmd;
}
#endif


typedef struct
{
  u8 TxBuf[4];
  u8 SizeOfCmd;
} tEraseFlashCmd;

typedef struct
{
  uint8 TxBuf[4];
  uint8 SizeOfCmd;
} tWriteFullFlashCmd;


tEraseFlashCmd EraseFlashCmd_2nd[23] =
{
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x01}, 0x03},                // Halt M0, stop potential FW execution
    {{0x56, 0x40, 0x01}, 0x03},                 // GP0 - SPI MCLK
    {{0x56, 0x44, 0x01}, 0x03},                 // GP1 - SPI MOSI
    {{0x56, 0x48, 0x41}, 0x03},                 // GP2 - SPI MISO
    {{0x56, 0x4C, 0x01}, 0x03},                 // GP3 - SPI CS
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC WPROT KEY
    {{0x40, 0x04, 0x12, 0x02}, 0x04},           // Enable SCLK; address [9:8]: SCLK Clock select, 0h = 6.6MHz; 1h = 8MHz; 2h = 10MHz
    {{0x4E, 0x00, 0xE0}, 0x03},                 // SPIM Reset

    // First enable WRITE ENABLE
    {{0x4E, 0x04, 0x01}, 0x03},                 // TX size - 1-byte (only HAL_FLASH_CMD_WE = 0x06)
    {{0x4E, 0x0C, 0x06}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    // FLASH UNLOCK
    {{0x4E, 0x04, 0x02}, 0x03},                 // TX size - 2-bytes (only HAL_FLASH_CMD_WSR + register val)
    {{0x4E, 0x0C, 0x01}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x0C, 0x00}, 0x03},                 // HAL_FLASH_STATUS_BP0 - block protection set to 0
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    // WRITE ENABLE
    {{0x4E, 0x04, 0x01}, 0x03},                 // TX size - 1-byte (only HAL_FLASH_CMD_WE = 0x06)
    {{0x4E, 0x0C, 0x06}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    // ERASE FULL flash
    {{0x4E, 0x04, 0x01}, 0x03},                 // TX size - 1-byte (only HAL_FLASH_CMD_CE = 0x60)
    {{0x4E, 0x0C, 0x60}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX


    {{EndOfCmd,}, EndOfCmd}
};



tWriteFullFlashCmd arr__p9450_flash_write_cmd_data[14] =
{
    // WRITE ENABLE
    {{0x4E, 0x04, 0x01}, 0x03},                 // TX size - 1-byte (only HAL_FLASH_CMD_WE = 0x06)
    {{0x4E, 0x0C, 0x06}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    // FLASH WRITE
    {{0x4E, 0x04, 0x08}, 0x03},                 // TX size - 8-bytes ( OPCODE + 3 address + 4 bytes data )
    {{0x4E, 0x0C, 0x02}, 0x03},                 // Write OP code to TX FIFO HAL_FLASH_CMD_BP
    {{0x4E, 0x0C, 0x00}, 0x03},                 // Address[23:16] to TX FIFO
    {{0x4E, 0x0C, 0x00}, 0x03},                 // Address[15: 8] to TX FIFO
    {{0x4E, 0x0C, 0x00}, 0x03},                 // Address[ 7: 0] to TX FIFO

    // Add also 4 data bytes to FIFO
    {{0x4E, 0x0C, 0x00}, 0x03},                 // Write data to TX FIFO HAL_FLASH_CMD_BP
    {{0x4E, 0x0C, 0x00}, 0x03},                 // Write data to TX FIFO HAL_FLASH_CMD_BP
    {{0x4E, 0x0C, 0x00}, 0x03},                 // Write data to TX FIFO HAL_FLASH_CMD_BP
    {{0x4E, 0x0C, 0x00}, 0x03},                 // Write data to TX FIFO HAL_FLASH_CMD_BP

    // FIFO is FULL we start transaction
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    {{EndOfCmd,}, EndOfCmd}
};

#if 0
tWriteFullFlashCmd RebootCmd[28] =
{
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x80}, 0x03},                 // M0 Reset
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x80}, 0x03},                 // M0 Reset

    {{0x44, 0xF0, 0xA5}, 0x03},                 // ???

    {{0x40, 0x00, 0x5A}, 0x03},                 // flash_access
    {{0x40, 0x40, 0x01}, 0x03},

    {{0x44, 0x54, 0x73}, 0x03},                 // ???
    {{0x44, 0x55, 0x01}, 0x03},

    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x80}, 0x03},                 // M0 Reset
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x80}, 0x03},                 // M0 Reset

    {{0x44, 0xF0, 0xA5}, 0x03},                 // ???

    {{0x40, 0x00, 0x5A}, 0x03},                 // flash_access
    {{0x40, 0x40, 0x01}, 0x03},

    {{0x44, 0x54, 0x73}, 0x03},                 // ???
    {{0x44, 0x55, 0x01}, 0x03},

    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x80}, 0x03},                 // M0 Reset
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x80}, 0x03},                 // M0 Reset

    {{0x44, 0xF0, 0xA5}, 0x03},                 // ???
    {{0x44, 0xF4, 0x94}, 0x03},                 // ???
    {{0x44, 0xF4, 0x50}, 0x03},                 // ???
    {{0x44, 0x84, 0x07}, 0x03},                 // ???
    {{0x40, 0x40, 0x80}, 0x03},                 // M0 Reset

    {{EndOfCmd,}, EndOfCmd}
};
#endif
#if 0
tWriteFullFlashCmd RebootCmd[7] =
{
    {{0x44, 0xF0, 0xA5}, 0x03},                 // ???
    {{0x44, 0xF4, 0x94}, 0x03},                 // ???
    {{0x44, 0xF4, 0x50}, 0x03},                 // ???
    {{0x44, 0x84, 0x07}, 0x03},                 // ???
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x80}, 0x03},                 // M0 Reset

    {{EndOfCmd,}, EndOfCmd}
};
#endif


#if 0
tWriteFullFlashCmd RebootCmd[13] =
{
    {{0x44, 0xF0, 0xA5}, 0x03},                 // ???
    {{0x44, 0xF4, 0x94}, 0x03},                 // ???
    {{0x44, 0xF4, 0x50}, 0x03},                 // ???
    {{0x44, 0x84, 0x07}, 0x03},                 // ???
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x80}, 0x03},                 // M0 Reset

    {{0x44, 0xF0, 0xA5}, 0x03},                 // ???
    {{0x44, 0xF4, 0x94}, 0x03},                 // ???
    {{0x44, 0xF4, 0x50}, 0x03},                 // ???
    {{0x44, 0x84, 0x07}, 0x03},                 // ???
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x80}, 0x03},                 // M0 Reset

    {{EndOfCmd,}, EndOfCmd}
};
#endif

#if 1
tWriteFullFlashCmd RebootCmd[24] =
{
   // {{0x40, 0x40, 0x80}, 0x03}, // 00
    {{0x40, 0x00, 0x5A}, 0x03}, // 0
    {{0x40, 0x40, 0x80}, 0x03}, // 1
    {{0x40, 0x00, 0x5A}, 0x03}, // 2
    {{0x40, 0x40, 0x80}, 0x03}, // 3
    {{0x44, 0xF0, 0xA5}, 0x03}, // 4

    {{0x40, 0x00, 0x5A}, 0x03}, // 5

    {{0x40, 0x40, 0x01}, 0x03}, // 6

    {{0x44, 0x54, 0x73}, 0x03}, // 7
    {{0x44, 0x55, 0x01}, 0x03}, // 8

    {{0x40, 0x00, 0x5A}, 0x03}, // 9
    {{0x40, 0x40, 0x80}, 0x03}, // 10
    {{0x40, 0x00, 0x5A}, 0x03}, // 11
    {{0x40, 0x40, 0x80}, 0x03}, // 12
    {{0x44, 0xF0, 0xA5}, 0x03}, // 13

    {{0x40, 0x00, 0x5A}, 0x03}, // 14
    {{0x40, 0x00, 0x01}, 0x03}, // 15
    {{0x40, 0x40, 0x01}, 0x03}, // 16

    {{0x44, 0x54, 0x73}, 0x03}, // 17
    {{0x44, 0x55, 0x81}, 0x03}, // 18

    {{0x40, 0x00, 0x5A}, 0x03}, // 19
    {{0x40, 0x40, 0x80}, 0x03}, // 20
    {{0x40, 0x00, 0x5A}, 0x03}, // 21
    {{0x40, 0x40, 0x80}, 0x03}, // 22

    {{EndOfCmd,}, EndOfCmd}
};
#endif

typedef struct
{
  uint8 TxBuf[2];
  uint8 SizeOfCmd;
} tRead_id_Cmd;

tRead_id_Cmd IdReqCmd[9] =
{
    {{0x40, 0xE0}, 0x02},
    {{0x40, 0xE1}, 0x02},
    {{0x40, 0xE2}, 0x02},
    {{0x40, 0xE3}, 0x02},
    {{0x40, 0xE4}, 0x02},
    {{0x40, 0xE5}, 0x02},
    {{0x40, 0xE6}, 0x02},
    {{0x40, 0xE7}, 0x02},

    {{EndOfCmd,}, EndOfCmd}
};

const uint8 Rd_P9450_Id[2] = {0x40u, 0xE0u};

typedef struct
{
  uint8 TxBuf[2];
  uint8 SizeOfCmd;
} tRead_temp1_Cmd;

typedef struct
{
  uint8 TxBuf[2];
  uint8 SizeOfCmd;
} tRead_temp2_Cmd;

tRead_temp1_Cmd ReadTemp1ReqCmd[4] =
{
    {{0xFF, 0xF0}, 0x02},
    {{0xFF, 0xF1}, 0x02},
    {{0xFF, 0xF2}, 0x02},

    {{EndOfCmd,}, EndOfCmd}
};

const uint8 Rd_P9450_Tmp1[2] = {0xFFu, 0xF0u};

tRead_temp2_Cmd ReadTemp2ReqCmd[13] =
{
    {{0xFE, 0xE0}, 0x02},
    {{0xFE, 0xE1}, 0x02},
    {{0xFE, 0xE2}, 0x02},
    {{0xFE, 0xE3}, 0x02},
    {{0xFE, 0xE4}, 0x02},
    {{0xFE, 0xE5}, 0x02},
    {{0xFE, 0xE6}, 0x02},
    {{0xFE, 0xE7}, 0x02},
    {{0xFE, 0xE8}, 0x02},
    {{0xFE, 0xE9}, 0x02},
    {{0xFE, 0xEA}, 0x02},
    {{0xFE, 0xEB}, 0x02},

    {{EndOfCmd,}, EndOfCmd}
};

const uint8 Rd_P9450_Tmp2[2] = {0xFEu, 0xE0u};


extern cy_en_scb_i2c_status_t I2C_MasterReceiveData(uint8_t * recv_data, uint8_t length, bool sendstop, uint32_t timeout);
extern cy_en_scb_i2c_status_t I2C_MasterSendData(const uint8 * send_data, uint8_t length, bool sendstop, uint32_t timeout);

void p9450_disable_watchdog(void);
void p9450_flash_access(void);
void p9450_flash_getID(void);


uint8 p9450_flash_id_address_l[2] = {0x40u, 0xE0u };
uint8 p9450_flash_id_address_h[2] = {0x40u, 0xE4u };
uint8 p9450_flash_Rxbuffer1[20] = {0x00u, };
uint8 p9450_flash_Rxbuffer2[20] = {0x00u, };
uint8 p9450_flash_Rxbuffer3[20] = {0x00u, };
uint8 p9450_flash_Rxbuffer4[20] = {0x00u, };
uint8 p9450_read_err_cnt = 0x00u;
uint8 Delay_Erase_Flash_step = 0x00u;
volatile uint8 veryfi_cnt_test = 0x00u;

volatile uint16 delaycnt = 0u;
volatile uint32 done_time_sec = 0x00u;
volatile uint32 done_time_5mSec = 0x00u;
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
void Set_P9450_SWver_to_rom(void);
extern void Retry_Reading_Charge_IC_Version(void);
#endif

extern void I2C_WPC_ReadRealTimeSystemData(const uint8 * Command, uint8 * rxBuff, uint8 txSize, uint8 rxSize);
void EraseFlashCtrl(void)
{
  volatile uint32 idx = 0x00u;
  static sint32 i2c_status = ERR_NONE;
  //static const uint8 StopCommand[6] = {0x00u, 0xFCu, 0x03u, 0x00u, 0x01u, 0x00u};
  static const uint8 StopCommand[6] = {0x0Du, 0x24u, 0x03u, 0x00u, 0x01u, 0x00u};
  //static const u8 CommonWriteCmd[5] = {0x1Cu, 0x0Cu, 0x01u, 0x06u, 0xFFu};
  //static u8 Rxbuffer[20] = {0u};

  uint8 dummy = 0u;

  UpTimer16(Timer_EraseDelay);

  if(b_UpdateFlashCmd == 1)
  {
    done_time_5mSec++;
  }

  if(done_time_5mSec==200)
  {
    done_time_5mSec = 0;
    done_time_sec++;
  }

  switch(sts_EraseFlashCtrl)
  {
    case EraseFlashCtrl_Start:
      /* Init State */
      CancelTimer(Timer_EraseDelay);
      EraseFlashCmdCnt = 0u;
      WriteFlashCmdCnt = 0u;
      VerityFlashCmdCnt = 0u;
      delaycnt = 0u;

      sts_EraseFlashCtrl = Update_Stop;
      break;


    case Update_Stop:
      /* 1. Update_Stop -> Erase_Flash */
      if(b_UpdateFlashCmd == On)
      {
        EraseFlashCmdCnt = 0u;
        sts_EraseFlashCtrl = Delay_Erase_Flash;
        delaycnt = 2u;
        StartTimer(Timer_EraseDelay);

        i2c_status = I2C_MasterSendData((const u8 *)StopCommand, 6, 1, 1000);
        delaycnt = 200;
        Delay_Erase_Flash_step = 0x00u;
      }
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      else
      {
        sts_EraseFlashCtrl = EraseFlashCtrl_Start;
      }
#endif
      break;


    case Delay_Erase_Flash:
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      if(b_UpdateFlashCmd == On)
      {
#endif
        if(delaycnt > 0u)
        {
          delaycnt--;
        }

        if((delaycnt == 0u))
        {
          switch(Delay_Erase_Flash_step)
          {
            case 0:
              I2C_WPC_ReadRealTimeSystemData(Rd_P9450_Id, &p9450_flash_Rxbuffer1[0], sizeof(Rd_P9450_Id), 8u);

              Delay_Erase_Flash_step = 1;
              break;
            case 1:
              I2C_WPC_ReadRealTimeSystemData(Rd_P9450_Tmp1, &p9450_flash_Rxbuffer2[0], sizeof(Rd_P9450_Tmp1), 3u);

              Delay_Erase_Flash_step = 2;
              break;
            case 2:
              I2C_WPC_ReadRealTimeSystemData(Rd_P9450_Tmp2, &p9450_flash_Rxbuffer3[0], sizeof(Rd_P9450_Tmp2), 12u);

              Delay_Erase_Flash_step = 3;
              break;
            case 3:
              I2C_WPC_ReadRealTimeSystemData(Rd_P9450_Id, &p9450_flash_Rxbuffer4[0], sizeof(Rd_P9450_Id), 8u);

              Delay_Erase_Flash_step = 20;
              break;
            case 4:
              break;
            case 5:
              break;
            case 20:
              CancelTimer(Timer_EraseDelay);
              sts_EraseFlashCtrl = Erase_Flash_1st;
              delaycnt = 200;
              break;
            default:
              break;
          }
        }
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      }
      else
      {
        sts_EraseFlashCtrl = EraseFlashCtrl_Start;
      }
#endif

      break;


    case Erase_Flash_1st:
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      if(b_UpdateFlashCmd == On)
      {
#endif
        EraseFlashCmdCnt = 0u;
        delaycnt = 200;
        sts_EraseFlashCtrl = Erase_Flash_2nd;
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      }
      else
      {
        sts_EraseFlashCtrl = EraseFlashCtrl_Start;
      }
#endif

      break;


    case Erase_Flash_2nd:
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      if(b_UpdateFlashCmd == On)
      {
#endif
        /* during */
        if(delaycnt > 0u)
        {
          delaycnt--;
        }

        if((EraseFlashCmd_2nd[EraseFlashCmdCnt].SizeOfCmd!=EndOfCmd) && (delaycnt == 0u))
        {
          i2c_status = I2C_MasterSendData((const u8 *)EraseFlashCmd_2nd[EraseFlashCmdCnt].TxBuf,
                                          EraseFlashCmd_2nd[EraseFlashCmdCnt].SizeOfCmd, 1, 1000);
          EraseFlashCmdCnt++;
          reprog_state = Erase_Flash_2nd;
        }

        /* 1. Erase_Flash_2st -> Update_Stop */
        if(i2c_status!=ERR_NONE)
        {
          b_UpdateFlashCmd = Off;
          EraseFlashCmdCnt = 0u;
          sts_EraseFlashCtrl = Update_Stop;
        }
        /* 2. EraseFlashCmd_2nd -> Write_Flash */
        else if(EraseFlashCmd_2nd[EraseFlashCmdCnt].SizeOfCmd==EndOfCmd)
        {
          EraseFlashCmdCnt = 0u;
          WriteFlashCmdCnt = 0u;
          veryfi_cnt_test = 0u;
          //delaycnt = 500u;
          sts_EraseFlashCtrl = Write_Flash_Cmd;
        }
        else
        {
          /* MISRA-C */
        }
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      }
      else
      {
        sts_EraseFlashCtrl = EraseFlashCtrl_Start;
      }
#endif

      break;


    case Write_Flash_Cmd:
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      if(b_UpdateFlashCmd == On)
      {
#endif
        WriteFlashCmdCnt = 0u;
        delaycnt = 100;
        sts_EraseFlashCtrl = Write_Flash_Data;
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      }
      else
      {
        sts_EraseFlashCtrl = EraseFlashCtrl_Start;
      }
#endif

      break;


    case Write_Flash_Data:
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      if(b_UpdateFlashCmd == On)
      {
#endif
        /* during */
        if(delaycnt > 0u)
        {
          delaycnt--;
        }

        if((WriteFlashData[WriteFlashCmdCnt].SizeOfCmd!=EndOfCmd) && (delaycnt == 0u))
        {
          arr__p9450_flash_write_cmd_data[5].TxBuf[2] = WriteFlashData[WriteFlashCmdCnt].TxBuf[1];
          arr__p9450_flash_write_cmd_data[6].TxBuf[2] = WriteFlashData[WriteFlashCmdCnt].TxBuf[2];
          arr__p9450_flash_write_cmd_data[7].TxBuf[2] = WriteFlashData[WriteFlashCmdCnt].TxBuf[3];

          arr__p9450_flash_write_cmd_data[8].TxBuf[2] = WriteFlashData[WriteFlashCmdCnt].TxBuf[4];
          arr__p9450_flash_write_cmd_data[9].TxBuf[2] = WriteFlashData[WriteFlashCmdCnt].TxBuf[5];
          arr__p9450_flash_write_cmd_data[10].TxBuf[2] = WriteFlashData[WriteFlashCmdCnt].TxBuf[6];
          arr__p9450_flash_write_cmd_data[11].TxBuf[2] = WriteFlashData[WriteFlashCmdCnt].TxBuf[7];

          for(idx=0; idx<14; idx++)
          {
            if(arr__p9450_flash_write_cmd_data[idx].SizeOfCmd != EndOfCmd)
            {
              i2c_status = I2C_MasterSendData((const u8 *)arr__p9450_flash_write_cmd_data[idx].TxBuf,
                                              arr__p9450_flash_write_cmd_data[idx].SizeOfCmd, 1, 1000);
            }
          }

          WriteFlashCmdCnt++;
          reprog_state = Write_Flash_Data;
        }

        if(WriteFlashData[WriteFlashCmdCnt].SizeOfCmd==EndOfCmd)
        {
          VerityFlashCmdCnt = 0u;
          delaycnt = 1500;
          sts_EraseFlashCtrl = Verify_Flash;
        }
        else
        {
          /* MISRA-C */
        }
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      }
      else
      {
        sts_EraseFlashCtrl = EraseFlashCtrl_Start;
      }
#endif

      break;



    case Verify_Flash:
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      if(b_UpdateFlashCmd == On)
      {
#endif
        /* during */
        if(delaycnt > 0u)
        {
          delaycnt--;
        }

        if((RebootCmd[VerityFlashCmdCnt].SizeOfCmd!=EndOfCmd) && (delaycnt == 0u))
        {
            i2c_status = I2C_MasterSendData((const u8 *)RebootCmd[VerityFlashCmdCnt].TxBuf,
                                            RebootCmd[VerityFlashCmdCnt].SizeOfCmd, 1, 1000);

          VerityFlashCmdCnt++;
          veryfi_cnt_test++;
          reprog_state = Verify_Flash;
          delaycnt=2;
        }
        else if(RebootCmd[VerityFlashCmdCnt].SizeOfCmd==EndOfCmd)
        {
          b_UpdateFlashCmd = Off;

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
          Set_P9450_SWver_to_rom();
          clr_p9450_auto_reprog_ready();
          Retry_Reading_Charge_IC_Version();
#endif

          WriteFlashCmdCnt = 0u;
          VerityFlashCmdCnt = 0u;
          bStartupI2CDelayCnt = 15u;
          sts_EraseFlashCtrl = EraseFlashCtrl_Start;

          dummy = GetXOld(kb_WPCRunMode);
          SetX(kb_WPCRunMode, dummy);

          TXCommInit();
          Pwm_IND_Stop(Amber);
          Pwm_IND_Stop(Green1);
          Pwm_IND_Stop(Green2);
          Pwm_IND_Stop(Green3);
        }
        else
        {
          /* MISRA-C */
        }
#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
      }
      else
      {
        sts_EraseFlashCtrl = EraseFlashCtrl_Start;
      }
#endif

      break;
    default:
      /* MISRA-C */
      break;
  }
}

uint8 GetReprogrammingProgress(void)
{
  uint8 p = 0u;

  p = (uint8)((WriteFlashCmdCnt*100)/P9261APPLINECOUNT);

  return p;
}

#if defined(USE_CHARGE_IC_AUTO_REPROGRAMMING_DEF)
void Set_P9450_SWver_to_rom(void)
{
  uint8 SubSWVer_tmp[5] = {P9450_SwVer};

  Set_EepromData_DUMMY((u8)kDummy_ChargeICver_0, (u8)SubSWVer_tmp[0]);
  Set_EepromData_DUMMY((u8)kDummy_ChargeICver_1, (u8)SubSWVer_tmp[1]);
  Set_EepromData_DUMMY((u8)kDummy_ChargeICver_2, (u8)SubSWVer_tmp[2]);
  Set_EepromData_DUMMY((u8)kDummy_ChargeICver_3, (u8)SubSWVer_tmp[3]);
  Set_EepromData_DUMMY((u8)kDummy_ChargeICver_4, (u8)SubSWVer_tmp[4]);
}

void Set_P9450_Init_SWver_For_Factory(void)
{
  uint8 SubSWVer_tmp[5] = {P9450_Factory_Init_SwVer};

  Set_EepromData_DUMMY((u8)kDummy_ChargeICver_0, (u8)SubSWVer_tmp[0]);
  Set_EepromData_DUMMY((u8)kDummy_ChargeICver_1, (u8)SubSWVer_tmp[1]);
  Set_EepromData_DUMMY((u8)kDummy_ChargeICver_2, (u8)SubSWVer_tmp[2]);
  Set_EepromData_DUMMY((u8)kDummy_ChargeICver_3, (u8)SubSWVer_tmp[3]);
  Set_EepromData_DUMMY((u8)kDummy_ChargeICver_4, (u8)SubSWVer_tmp[4]);
}

uint8 Get_P9450_Header_Software_Version(uint8 idx)
{
  uint8 SubSWVer_tmp[5] = {P9450_SwVer};

  return SubSWVer_tmp[idx];
}

uint8 Cmp_P9450_SWver(void)
{
  uint8 header_SubSWVer_tmp[5] = {P9450_SwVer};
  uint8 rom_SubSWVer_tmp[5] = {0u, };
  uint8 rom_SubSWVer_for_factory_tmp[5] = {P9450_Factory_Init_SwVer };
  uint8 rom_SubSWVer_for_old_field_tmp[5] = {P9450_Old_Field_Init_SwVer };
  int result;
  uint8 ret;

  rom_SubSWVer_tmp[0] = Get_EepromData_DUMMY((u8)kDummy_ChargeICver_0);
  rom_SubSWVer_tmp[1] = Get_EepromData_DUMMY((u8)kDummy_ChargeICver_1);
  rom_SubSWVer_tmp[2] = Get_EepromData_DUMMY((u8)kDummy_ChargeICver_2);
  rom_SubSWVer_tmp[3] = Get_EepromData_DUMMY((u8)kDummy_ChargeICver_3);
  rom_SubSWVer_tmp[4] = Get_EepromData_DUMMY((u8)kDummy_ChargeICver_4);

  result= memcmp(&header_SubSWVer_tmp[0], &rom_SubSWVer_tmp[0], sizeof(rom_SubSWVer_tmp));

  if(result == 0)
  {
    ret = 0u;
  }
  else
  {
    if(memcmp(&rom_SubSWVer_for_factory_tmp[0], &rom_SubSWVer_tmp[0], sizeof(rom_SubSWVer_tmp)) == 0u)
    {
      ret = 1u;
    }
    else if(memcmp(&rom_SubSWVer_for_old_field_tmp[0], &rom_SubSWVer_tmp[0], sizeof(rom_SubSWVer_tmp)) == 0u)
    {
      ret = 2u;
    }
    else
    {
      ret = 3u;
    }
  }

  return ret;
}
#endif




void p9450_disable_watchdog(void)
{
  sint32 i2c_status = ERR_NONE;
  volatile uint8 idx = 0x00u;
  uint8 arr_tmp1[2] = {0x40u, 0x00u};
  uint8 arr_tmp2[3] = {0x40u, 0x00u, 0x5A};
  uint8 arr_tmp3[3] = {0x40u, 0x24u, 0x03};
  uint8 arr_tmp4[3] = {0x40u, 0x20u, 0x00};
  uint8 arr_rxbuf[3] = {0x00u, };

  // disable watchdog before programming
   i2c_status = I2C_MasterSendData(arr_tmp1, 2, 1, 1000);
   if(i2c_status==ERR_NONE)
   {
     i2c_status = I2C_MasterReceiveData(arr_rxbuf, 1, 1, 10000);
   }

   if(arr_rxbuf[0]==0x00u)
   {
     i2c_status = I2C_MasterSendData(arr_tmp2, 3, 1, 1000);
   }

   i2c_status = I2C_MasterSendData(arr_tmp3, 3, 1, 1000);
   i2c_status = I2C_MasterSendData(arr_tmp4, 3, 1, 1000);
}




//===============================================================================================
#define P9450CmdDir_W 0
#define P9450CmdDir_R 1

typedef struct
{
  uint8 DirofCmd;
  uint8 Addr[2];
  uint8 TxSizeOfCmd;
  uint8 RxSizeOfCmd;
} tGetIdCmd;

uint8 ReadBuf_kkh_tmp[20] = {0x00u, };

void p9450_read_data(uint8 * addr, uint8 * ReadBuf, uint8 Txlen, uint8 Rxlen)
{
  volatile uint8 idx = 0x00u;
  sint32 i2c_status = ERR_NONE;
  uint16 real_addr = 0x0000u;
  uint16 base_addr_tmp = 0x0000u;


  base_addr_tmp |= (uint16)addr[1];
  base_addr_tmp |= (uint16)addr[0]<<8;

  for(idx = 0; idx<Rxlen; idx++)
  {

    real_addr = base_addr_tmp + idx;

    addr[1] = (uint8)real_addr;
    addr[0] = (uint8)((real_addr >> 8U) & 0xFFU);


    i2c_status = I2C_MasterSendData(addr, Txlen, 1, 1000);
    if(i2c_status==ERR_NONE)
    {

      i2c_status = I2C_MasterReceiveData(&ReadBuf[idx], 1, 1, 10000);
    }
  }
}

void p9450_flash_getID(void)
{
  tGetIdCmd arr_get_id[2] =
  {
      {P9450CmdDir_R, {0x40, 0xE0}, 0x02, 0x08},

      {{EndOfCmd,}, EndOfCmd}
  };

  if(arr_get_id[0].DirofCmd==P9450CmdDir_R)
  {
    p9450_read_data(&arr_get_id[0].Addr, &ReadBuf_kkh_tmp[0], arr_get_id[0].TxSizeOfCmd, arr_get_id[0].RxSizeOfCmd);
  }
}

void p9450_flash_getID_test(void)
{
  sint32 i2c_status = ERR_NONE;
  uint8 read_addr[2]={0x40, 0xE0};

  i2c_status = I2C_MasterSendData(read_addr, 2, 1, 1000);
  if(i2c_status==ERR_NONE)
  {
    i2c_status = I2C_MasterReceiveData(&ReadBuf_kkh_tmp[0], 8, 1, 10000);
  }
}








//===============================================================================================
void p9450_flash_access(void)
{
  sint32 i2c_status = ERR_NONE;

  uint8 arr_rxbuf1[3] = {0x00u, };
  uint8 arr_rxbuf2[3] = {0x00u, };
  uint8 arr_tmp1[3] = {0x40u, 0x00u, 0x5A};
  uint8 arr_tmp2[2] = {0x40u, 0x00u};
  uint8 arr_tmp3[3] = {0x40u, 0x40u, 0x01};
  uint8 arr_tmp4[2] = {0x40u, 0x40u};

  // unlocking using SYC_KEY
  i2c_status = I2C_MasterSendData(arr_tmp1, 3, 1, 1000);
  i2c_status = I2C_MasterSendData(arr_tmp2, 2, 1, 1000);
  if(i2c_status==ERR_NONE)
  {
    i2c_status = I2C_MasterReceiveData(arr_rxbuf1, 1, 1, 10000);
  }

  // hold mcu
  i2c_status = I2C_MasterSendData(arr_tmp3, 3, 1, 1000);
  i2c_status = I2C_MasterSendData(arr_tmp4, 2, 1, 1000);
  if(i2c_status==ERR_NONE)
  {
    i2c_status = I2C_MasterReceiveData(arr_rxbuf2, 1, 1, 10000);
  }
}


//===============================================================================================
typedef struct
{
  uint8 TxBuf[4];
  uint8 SizeOfCmd;
} tInitFlashCmd;

void p9450_flash_init(void)
{
  volatile uint8 idx = 0x00u;
  sint32 i2c_status = ERR_NONE;
  tInitFlashCmd arr_flash_init[8] =
  {
      {{0x56, 0x40, 0x01}, 0x03},                 // GP0 - SPI MCLK
      {{0x56, 0x44, 0x01}, 0x03},                 // GP1 - SPI MOSI
      {{0x56, 0x48, 0x41}, 0x03},                 // GP2 - SPI MISO
      {{0x56, 0x4C, 0x01}, 0x03},                 // GP3 - SPI CS
      {{0x40, 0x00, 0x5A}, 0x03},                 // SYC WPROT KEY
      {{0x40, 0x04, 0x12, 0x02}, 0x04},           // Enable SCLK; address [9:8]: SCLK Clock select, 0h = 6.6MHz; 1h = 8MHz; 2h = 10MHz
      {{0x4E, 0x00, 0xE0}, 0x03},                 // SPIM Reset
      {{EndOfCmd,}, EndOfCmd}
  };

  for(idx=0; idx<8; idx++)
  {
    if(arr_flash_init[idx].SizeOfCmd!=EndOfCmd)
    {
      i2c_status = I2C_MasterSendData(&arr_flash_init[idx].TxBuf, arr_flash_init[idx].SizeOfCmd, 1, 1000);
    }
  }
}

//===============================================================================================
typedef struct
{
  uint8 TxBuf[3];
  uint8 SizeOfCmd;
} tDisablePwmCmd;

void p9450_disable_pwm(void)
{
  volatile uint8 idx = 0x00u;
  sint32 i2c_status = ERR_NONE;
  tDisablePwmCmd arr_disable_pwm[5] =
  {
      {{0x80, 0x00, 0x01}, 0x03},                 // disable inverter and PWM and bridge controller
      {{0x80, 0x22, 0x01}, 0x03},
      {{0x74, 0x44, 0x00}, 0x03},                 // disable VBRG
      {{0x74, 0x40, 0x00}, 0x03},

      {{EndOfCmd,}, EndOfCmd}
  };

  for(idx=0; idx<5; idx++)
  {
    if(arr_disable_pwm[idx].SizeOfCmd!=EndOfCmd)
    {
      i2c_status = I2C_MasterSendData(&arr_disable_pwm[idx].TxBuf, arr_disable_pwm[idx].SizeOfCmd, 1, 1000);
    }
  }
}

//===============================================================================================
typedef struct
{
  uint8 TxBuf[3];
  uint8 SizeOfCmd;
} tWriteEnableCmd;

void p9450_write_enable(void)
{
  volatile uint8 idx = 0x00u;
  sint32 i2c_status = ERR_NONE;
  tWriteEnableCmd arr_write_enable[4] =
  {
      {{0x4E, 0x04, 0x01}, 0x03},
      {{0x4E, 0x0C, 0x06}, 0x03},
      {{0x4E, 0x00, 0x01}, 0x03},

      {{EndOfCmd,}, EndOfCmd}
  };

  for(idx=0; idx<4; idx++)
  {
    if(arr_write_enable[idx].SizeOfCmd!=EndOfCmd)
    {
      i2c_status = I2C_MasterSendData(&arr_write_enable[idx].TxBuf, arr_write_enable[idx].SizeOfCmd, 1, 1000);
    }
  }
}

//===============================================================================================
typedef struct
{
  uint8 TxBuf[3];
  uint8 SizeOfCmd;
} tWriteFlashUnlockCmd;

void p9450_flash_unlock(void)
{
  volatile uint8 idx = 0x00u;
  sint32 i2c_status = ERR_NONE;
  tWriteFlashUnlockCmd arr_write_flash_unlock[5] =
  {
      {{0x4E, 0x04, 0x02}, 0x03},
      {{0x4E, 0x0C, 0x01}, 0x03},
      {{0x4E, 0x0C, 0x00}, 0x03},
      {{0x4E, 0x00, 0x01}, 0x03},

      {{EndOfCmd,}, EndOfCmd}
  };

  for(idx=0; idx<5; idx++)
  {
    if(arr_write_flash_unlock[idx].SizeOfCmd!=EndOfCmd)
    {
      i2c_status = I2C_MasterSendData(&arr_write_flash_unlock[idx].TxBuf, arr_write_flash_unlock[idx].SizeOfCmd, 1, 1000);
    }
  }
}

//===============================================================================================
volatile uint8 flash_phase_cnt = 0u;
void Flash_Test_Program(void)
{
  switch(flash_phase_cnt)
  {
    case 1:
      //temp_p9450_flash_erase();
      //if(flash_erase_step_f==0xffu)
      //{
        flash_phase_cnt = 0;
      //}
      break;
    case 2:
      //temp_p9450_flash_write();
     // if(flash_write_step_f==0xffu)
      //{
        flash_phase_cnt = 0;
      //}

      break;
    case 3:
      //p9450_program_read();
      flash_phase_cnt = 0;
      break;
    case 4:
      p9450_flash_getID();
      flash_phase_cnt = 0;
    default:
      break;
  }
}


/*================================================================================================*/
/*================================================================================================*/
/*================================================================================================*/
/*================================================================================================*/
/*================================================================================================*/
/*================================================================================================*/
#if 0

volatile uint16 delay_cnt_tmp = 0x0000u;
volatile uint16 DeviceID_tmp = 0xFFFFu;
volatile get_id_rx_buf0 = 0x00u;
volatile get_id_rx_buf1 = 0x00u;
volatile get_id_rx_buf2 = 0x00u;
volatile get_id_rx_buf3 = 0x00u;
volatile get_id_rx_buf4 = 0x00u;
volatile get_id_rx_buf5 = 0x00u;
volatile get_id_rx_buf6 = 0x00u;
volatile get_id_rx_buf7 = 0x00u;
uint16 p9450_flash_getid(void)
{
  volatile sint32 i2c_status = ERR_NONE;
  uint8 DeviceIdAddr1[2] = {0x40, 0xE0};
  uint8 DeviceIdAddr2[2] = {0x40, 0xE4};
  uint8 rxBuf1[4] = {0x00u, };
  uint8 rxBuf2[4] = {0x00u, };

  uint16 DeviceID_tmp = 0xFFFFu;

  i2c_status = I2C_MasterSendData(DeviceIdAddr1, 0x02u, 1, 1000);

  if(i2c_status==ERR_NONE)
  {
    i2c_status = I2C_MasterReceiveData(rxBuf1, 1, 1, 10000);
    DeviceID_tmp = rxBuf1[0];
  }

  i2c_status = I2C_MasterSendData(DeviceIdAddr2, 0x02u, 1, 1000);

  if(i2c_status==ERR_NONE)
  {
    i2c_status = I2C_MasterReceiveData(rxBuf2, 1, 1, 10000);
    DeviceID_tmp |= rxBuf2[0];
  }

  get_id_rx_buf0 = rxBuf1[0];
  get_id_rx_buf1 = rxBuf1[1];
  get_id_rx_buf2 = rxBuf1[2];
  get_id_rx_buf3 = rxBuf1[3];
  get_id_rx_buf4 = rxBuf2[0];
  get_id_rx_buf5 = rxBuf2[1];
  get_id_rx_buf6 = rxBuf2[2];
  get_id_rx_buf7 = rxBuf2[3];



  //DeviceID_tmp = rxBuf1[0];
  //DeviceID_tmp = (DeviceID_tmp << 8) + rxBuf2[0];


  return DeviceID_tmp;
}

uint16 id_tmp = 0xFFFFu;
uint16 p9450_flash_detect(void)
{
  uint8 retval = 0x00u;
  volatile uint8 cnt = 0x00u;


  id_tmp = 0xFFFFu;

  for(cnt=0; cnt<4; cnt++)
  {
    id_tmp = p9450_flash_getid();

    if(id_tmp == 0x9450)
    {
      retval = 0x01u;
      break;
    }
  }

  if(cnt==4)
  {
    retval = 0x00u;
  }

  return id_tmp;
}









#define OK    0x00u
#define NOT_OK 0x01u;
volatile uint8 flash_phase_cnt = 0u;
volatile uint8 erase_phase_cnt = 0x00u;



volatile uint8 write_phase_cnt = 0x00u;





typedef struct
{
  u8 TxBuf[4];
  u8 SizeOfCmd;
} tAccessFlashCmd;

typedef struct
{
  u8 TxBuf[3];
  u8 SizeOfCmd;
} tReadfromAddressFlashCmd;

//===============================================================================================
tAccessFlashCmd arr_setup_p9450_flash_access[10] =
{
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x01}, 0x03},                // Halt M0, stop potential FW execution
    {{0x56, 0x40, 0x01}, 0x03},                 // GP0 - SPI MCLK
    {{0x56, 0x44, 0x01}, 0x03},                 // GP1 - SPI MOSI
    {{0x56, 0x48, 0x41}, 0x03},                 // GP2 - SPI MISO
    {{0x56, 0x4C, 0x01}, 0x03},                 // GP3 - SPI CS
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC WPROT KEY
    {{0x40, 0x04, 0x12, 0x02}, 0x04},           // Enable SCLK; address [9:8]: SCLK Clock select, 0h = 6.6MHz; 1h = 8MHz; 2h = 10MHz
    {{0x4E, 0x00, 0xE0}, 0x03},                 // SPIM Reset
    {{EndOfCmd,}, EndOfCmd}
};

//===============================================================================================
tReadfromAddressFlashCmd arr_flash_read_from_address[8] =
{
  {{0x4E, 0x04, 0x04}, 0x03},         // RX size - 4-bytes
  {{0x4E, 0x0C, 0x0B}, 0x03},         // Write OP code HAL_FLASH_CMD_RSR to TX FIFO
  {{0x4E, 0x0C, 0x00}, 0x03},         // Address[23:16] to TX FIFO
  {{0x4E, 0x0C, 0x00}, 0x03},         // Address[15: 8] to TX FIFO
  {{0x4E, 0x0C, 0x00}, 0x03},         // Address[ 7: 0] to TX FIFO
  {{0x4E, 0x0C, 0x00}, 0x03},         // Dummy 0 to TX FIFO - important!
  {{0x4E, 0x00, 0x01}, 0x03},          // Start TX
  {{EndOfCmd,}, EndOfCmd}
};
//===============================================================================================

volatile uint32 memory_compare_read_data_f = 0x00u;
volatile uint32 memory_compare_read_data_ok_f = 0x00u;
volatile uint32 memory_compare_read_data_err_f = 0x00u;
volatile uint32  memory_compare_read_data_err_confirm_f = 0x00u;
uint8 read_4byte_data_tmp[4] = {0x00u, };
volatile uint32 WriteFlashData_cnt = 0u;
volatile uint32 total_rd_cnt = 0u;
volatile uint32 total_rd_len = 0u;
volatile uint8 WriteFlashDataSizeOfCmd = 0x00u;
void p9450_program_read(void)
{
  uint32_t delay_cnt_tmp = 0u;
  sint32 i2c_status = ERR_NONE;
  uint8 idx = 0x00u;
  uint8 read_i2c_cmd_addr[2] = {0x4E, 0x10};


  total_rd_len = sizeof(WriteFlashData) / 10;

  for(idx=0; idx<10; idx++)
  {
    if(arr_setup_p9450_flash_access[idx].SizeOfCmd != EndOfCmd)
    {
      i2c_status = I2C_MasterSendData((const u8 *)arr_setup_p9450_flash_access[idx].TxBuf,
                                      arr_setup_p9450_flash_access[idx].SizeOfCmd, 1, 1000);
    }
  }

  for(total_rd_cnt = 0; total_rd_cnt<(total_rd_len); total_rd_cnt++)
  {
    for(delay_cnt_tmp=0; delay_cnt_tmp<10000; delay_cnt_tmp++)
    {

    }

    WriteFlashDataSizeOfCmd = WriteFlashData[total_rd_cnt].SizeOfCmd;
    if(WriteFlashData[total_rd_cnt].SizeOfCmd != EndOfCmd)
    {
      arr_flash_read_from_address[2].TxBuf[2] = WriteFlashData[total_rd_cnt].TxBuf[1];
      arr_flash_read_from_address[3].TxBuf[2] = WriteFlashData[total_rd_cnt].TxBuf[2];
      arr_flash_read_from_address[4].TxBuf[2] = WriteFlashData[total_rd_cnt].TxBuf[3];


      for(idx=0; idx<8; idx++)
      {
        if(arr_flash_read_from_address[idx].SizeOfCmd != EndOfCmd)
        {
          i2c_status = I2C_MasterSendData((const u8 *)arr_flash_read_from_address[idx].TxBuf,
                                          arr_flash_read_from_address[idx].SizeOfCmd, 1, 1000);
        }
      }

      for(idx=0; idx<4; idx++)
      {
        i2c_status = I2C_MasterSendData((const u8 *)read_i2c_cmd_addr, 2, 1, 1000);
        i2c_status = I2C_MasterReceiveData(&read_4byte_data_tmp[idx], 1, 1, 10000);
      }

      if( memcmp(&WriteFlashData[total_rd_cnt].TxBuf[4], read_4byte_data_tmp, 4) == 0x00u)
      {
        memory_compare_read_data_ok_f++;
      }
      else
      {
        if(memory_compare_read_data_err_f<1000)
        {
          memory_compare_read_data_err_f++;
          total_rd_cnt--;
        }
        else
        {
          memory_compare_read_data_err_f = 0;
          memory_compare_read_data_err_confirm_f++;
        }
      }
    }
    else
    {
      memory_compare_read_data_f = 0xffu;
    }
  }
}






typedef struct
{
  u8 TxBuf[3];
  u8 SizeOfCmd;
} tEraseFullFlashCmd;




tEraseFullFlashCmd arr__p9450_flash_erase_cmd_data[15] =
{
    // First enable WRITE ENABLE
    {{0x4E, 0x04, 0x01}, 0x03},                 // TX size - 1-byte (only HAL_FLASH_CMD_WE = 0x06)
    {{0x4E, 0x0C, 0x06}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    // FLASH UNLOCK
    {{0x4E, 0x04, 0x02}, 0x03},                 // TX size - 2-bytes (only HAL_FLASH_CMD_WSR + register val)
    {{0x4E, 0x0C, 0x01}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x0C, 0x00}, 0x03},                 // HAL_FLASH_STATUS_BP0 - block protection set to 0
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    // WRITE ENABLE
    {{0x4E, 0x04, 0x01}, 0x03},                 // TX size - 1-byte (only HAL_FLASH_CMD_WE = 0x06)
    {{0x4E, 0x0C, 0x06}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    // ERASE FULL flash
    {{0x4E, 0x04, 0x01}, 0x03},                 // TX size - 1-byte (only HAL_FLASH_CMD_CE = 0x60)
    {{0x4E, 0x0C, 0x60}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    {{0x40, 0x40, 0x80}, 0x03},                 // Start TX

    {{EndOfCmd,}, EndOfCmd}
};




tAccessFlashCmd arr_setup_p9450_flash_access_and_erase[23] =
{
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x01}, 0x03},                // Halt M0, stop potential FW execution
    {{0x56, 0x40, 0x01}, 0x03},                 // GP0 - SPI MCLK
    {{0x56, 0x44, 0x01}, 0x03},                 // GP1 - SPI MOSI
    {{0x56, 0x48, 0x41}, 0x03},                 // GP2 - SPI MISO
    {{0x56, 0x4C, 0x01}, 0x03},                 // GP3 - SPI CS
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC WPROT KEY
    {{0x40, 0x04, 0x12, 0x02}, 0x04},           // Enable SCLK; address [9:8]: SCLK Clock select, 0h = 6.6MHz; 1h = 8MHz; 2h = 10MHz
    {{0x4E, 0x00, 0xE0}, 0x03},                 // SPIM Reset

    // First enable WRITE ENABLE
    {{0x4E, 0x04, 0x01}, 0x03},                 // TX size - 1-byte (only HAL_FLASH_CMD_WE = 0x06)
    {{0x4E, 0x0C, 0x06}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    // FLASH UNLOCK
    {{0x4E, 0x04, 0x02}, 0x03},                 // TX size - 2-bytes (only HAL_FLASH_CMD_WSR + register val)
    {{0x4E, 0x0C, 0x01}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x0C, 0x00}, 0x03},                 // HAL_FLASH_STATUS_BP0 - block protection set to 0
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    // WRITE ENABLE
    {{0x4E, 0x04, 0x01}, 0x03},                 // TX size - 1-byte (only HAL_FLASH_CMD_WE = 0x06)
    {{0x4E, 0x0C, 0x06}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    // ERASE FULL flash
    {{0x4E, 0x04, 0x01}, 0x03},                 // TX size - 1-byte (only HAL_FLASH_CMD_CE = 0x60)
    {{0x4E, 0x0C, 0x60}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX


    {{EndOfCmd,}, EndOfCmd}
};
volatile uint8 flash_erase_cnt_f_tmp = 0x00u;
volatile uint8 flash_erase_step_f = 0x00u;
void temp_p9450_flash_erase(void)
{
  volatile uint32_t delay_cnt_tmp = 0u;
  sint32 i2c_status = ERR_NONE;




  if(arr_setup_p9450_flash_access_and_erase[flash_erase_cnt_f_tmp].SizeOfCmd != EndOfCmd)
  {
    flash_erase_step_f = 0x00u;
    i2c_status = I2C_MasterSendData((const u8 *)arr_setup_p9450_flash_access_and_erase[flash_erase_cnt_f_tmp].TxBuf,
                                    arr_setup_p9450_flash_access_and_erase[flash_erase_cnt_f_tmp].SizeOfCmd, 1, 1000);
    flash_erase_cnt_f_tmp++;
  }
  else if(arr_setup_p9450_flash_access_and_erase[flash_erase_cnt_f_tmp].SizeOfCmd == EndOfCmd)
  {
    flash_erase_step_f = 0xffu;
  }
}


typedef struct
{
  uint8 TxBuf[3];
  uint8 SizeOfCmd;
} tWriteFullFlashCmd;
tWriteFullFlashCmd arr__p9450_flash_write_cmd_data[14] =
{
    // WRITE ENABLE
    {{0x4E, 0x04, 0x01}, 0x03},                 // TX size - 1-byte (only HAL_FLASH_CMD_WE = 0x06)
    {{0x4E, 0x0C, 0x06}, 0x03},                 // Write OP code to TX FIFO
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    // FLASH WRITE
    {{0x4E, 0x04, 0x08}, 0x03},                 // TX size - 8-bytes ( OPCODE + 3 address + 4 bytes data )
    {{0x4E, 0x0C, 0x02}, 0x03},                 // Write OP code to TX FIFO HAL_FLASH_CMD_BP
    {{0x4E, 0x0C, 0x00}, 0x03},                 // Address[23:16] to TX FIFO
    {{0x4E, 0x0C, 0x00}, 0x03},                 // Address[15: 8] to TX FIFO
    {{0x4E, 0x0C, 0x00}, 0x03},                 // Address[ 7: 0] to TX FIFO

    // Add also 4 data bytes to FIFO
    {{0x4E, 0x0C, 0x40}, 0x03},                 // Write data to TX FIFO HAL_FLASH_CMD_BP
    {{0x4E, 0x0C, 0x41}, 0x03},                 // Write data to TX FIFO HAL_FLASH_CMD_BP
    {{0x4E, 0x0C, 0x42}, 0x03},                 // Write data to TX FIFO HAL_FLASH_CMD_BP
    {{0x4E, 0x0C, 0x43}, 0x03},                 // Write data to TX FIFO HAL_FLASH_CMD_BP

    // FIFO is FULL we start transaction
    {{0x4E, 0x00, 0x01}, 0x03},                 // Start TX

    {{EndOfCmd,}, EndOfCmd}
};

tWriteFullFlashCmd arr__p9450_flash_write_end_cmd_data[3] =
{
    {{0x40, 0x00, 0x5A}, 0x03},                 // SYC _KEY unlock
    {{0x40, 0x40, 0x80}, 0x03},                 // M0 Reset

    {{EndOfCmd,}, EndOfCmd}
};

volatile uint8 flash_write_step_f = 0x00u;
volatile uint32 flash_write_cnt_f_tmp = 0x00u;
void temp_p9450_flash_write(void)
{
  sint32 i2c_status = ERR_NONE;
  volatile uint8 idx = 0x00u;

  switch(flash_write_step_f)
  {
    case 0:
      //if(arr__p9450_flash_write_cmd_data[flash_write_cnt_f_tmp].SizeOfCmd != EndOfCmd)
      if(WriteFlashData[flash_write_cnt_f_tmp].SizeOfCmd != EndOfCmd)
      {
        arr__p9450_flash_write_cmd_data[5].TxBuf[2] = WriteFlashData[flash_write_cnt_f_tmp].TxBuf[1];
        arr__p9450_flash_write_cmd_data[6].TxBuf[2] = WriteFlashData[flash_write_cnt_f_tmp].TxBuf[2];
        arr__p9450_flash_write_cmd_data[7].TxBuf[2] = WriteFlashData[flash_write_cnt_f_tmp].TxBuf[3];

        arr__p9450_flash_write_cmd_data[8].TxBuf[2] = WriteFlashData[flash_write_cnt_f_tmp].TxBuf[4];
        arr__p9450_flash_write_cmd_data[9].TxBuf[2] = WriteFlashData[flash_write_cnt_f_tmp].TxBuf[5];
        arr__p9450_flash_write_cmd_data[10].TxBuf[2] = WriteFlashData[flash_write_cnt_f_tmp].TxBuf[6];
        arr__p9450_flash_write_cmd_data[11].TxBuf[2] = WriteFlashData[flash_write_cnt_f_tmp].TxBuf[7];

        for(idx=0; idx<14; idx++)
        {
          if(arr__p9450_flash_write_cmd_data[idx].SizeOfCmd != EndOfCmd)
          {
            i2c_status = I2C_MasterSendData((const u8 *)arr__p9450_flash_write_cmd_data[idx].TxBuf,
                                            arr__p9450_flash_write_cmd_data[idx].SizeOfCmd, 1, 1000);
          }
        }

        flash_write_cnt_f_tmp++;
      }
      //else if(arr__p9450_flash_write_cmd_data[flash_write_cnt_f_tmp].SizeOfCmd == EndOfCmd)
      else if(WriteFlashData[flash_write_cnt_f_tmp].SizeOfCmd == EndOfCmd)
      {
        flash_write_cnt_f_tmp = 0x00u;
        flash_write_step_f = 1;
      }
      break;
    case 1:
      if(arr__p9450_flash_write_end_cmd_data[flash_write_cnt_f_tmp].SizeOfCmd != EndOfCmd)
      {
        i2c_status = I2C_MasterSendData((const u8 *)arr__p9450_flash_write_end_cmd_data[flash_write_cnt_f_tmp].TxBuf,
                                        arr__p9450_flash_write_end_cmd_data[flash_write_cnt_f_tmp].SizeOfCmd, 1, 1000);
        flash_write_cnt_f_tmp++;
      }
      else if(arr__p9450_flash_write_end_cmd_data[flash_write_cnt_f_tmp].SizeOfCmd == EndOfCmd)
      {
        flash_write_cnt_f_tmp = 0x00u;
        flash_write_step_f = 0xffu;
      }
      break;
    default:
      break;
  }
}



void Flash_Test_Program(void)
{
  switch(flash_phase_cnt)
  {
    case 1:
      temp_p9450_flash_erase();
      if(flash_erase_step_f==0xffu)
      {
        flash_phase_cnt = 0;
      }
      break;
    case 2:
      temp_p9450_flash_write();
      if(flash_write_step_f==0xffu)
      {
        flash_phase_cnt = 0;
      }

      break;
    case 3:
      p9450_program_read();
      flash_phase_cnt = 0;
      break;
    case 4:
      p9450_flash_getID();
      flash_phase_cnt = 0;
    default:
      break;
  }
}
#endif
/*================================================================================================*/

























#endif
