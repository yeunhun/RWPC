/***************************************************************************//**
* \file 12c.c
********************************************************************************
* \copyright
* Copyright 2016-2020, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <stdio.h>
#include <stdarg.h>

#include "cy_scb_i2c.h"

#include "WPCVehicleOption.h"

/* SCB - I2C Configuration */
#define USER_I2C_SCB_TYPE       SCB2

#define E_I2C_INCLK_TARGET_FREQ (10000000ul)  // modifiable
#define E_I2C_DATARATE          (400000ul)   // modifiable

#define E_I2C_SLAVE_ADDR        0x3Cu

static cy_stc_scb_i2c_context_t g_stc_i2c_context;

static const cy_stc_scb_i2c_config_t  g_stc_i2c_config =
{
  .i2cMode             = CY_SCB_I2C_MASTER,
  .useRxFifo           = true,
  .useTxFifo           = true,
  .slaveAddress        = E_I2C_SLAVE_ADDR,
  .slaveAddressMask    = E_I2C_SLAVE_ADDR,
  .acceptAddrInFifo    = false,
  .ackGeneralAddr      = false,
  .enableWakeFromSleep = false
};

static cy_stc_scb_i2c_master_xfer_config_t g_stc_i2c_master_config =
{
  .slaveAddress = E_I2C_SLAVE_ADDR,
  .buffer       = 0,
  .bufferSize   = 0,
  .xferPending  = false
};

/* Local Variables */
cy_en_scb_i2c_status_t I2C_MasterSendData(const uint8 * send_data, uint8_t length, bool sendstop, uint32_t timeout)
{
  uint8_t i = 0ul;
  uint8_t f_timeout = 0ul;
  uint32_t FifoStatus = 0ul;
  uint32_t waittime_emptyFifo;
  
  cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_MASTER_NOT_READY;

  waittime_emptyFifo = timeout;
  
  /* Make sure TX FIFO empty */
  do
  {
    FifoStatus = Cy_SCB_GetNumInTxFifo(USER_I2C_SCB_TYPE);

    if(FifoStatus == 0ul)
    {
      waittime_emptyFifo = 0ul;
      f_timeout = 0ul;
    }
    else
    {
      waittime_emptyFifo--;
      f_timeout = 1ul;
    }
  } while((FifoStatus != 0ul) || (waittime_emptyFifo != 0ul));

  if(f_timeout == 0ul)
  {
	  /* Send START and Receive ACK/NACK */
	  //retStatus = Cy_SCB_I2C_MasterSendStart(USER_I2C_SCB_TYPE, E_I2C_SLAVE_ADDR, CY_SCB_I2C_WRITE_XFER, 2000ul, &g_stc_i2c_context);
    retStatus = Cy_SCB_I2C_MasterSendStart(USER_I2C_SCB_TYPE, E_I2C_SLAVE_ADDR, CY_SCB_I2C_WRITE_XFER, 2ul, &g_stc_i2c_context);

	  if(retStatus == CY_SCB_I2C_SUCCESS)
	  {
	    for(i=0ul; i<length; i++)
	    {
		  /* Transmit One Byte Data */
	      //retStatus |= Cy_SCB_I2C_MasterWriteByte(USER_I2C_SCB_TYPE, (uint8_t)send_data[i], 2000ul, &g_stc_i2c_context);
	      retStatus |= Cy_SCB_I2C_MasterWriteByte(USER_I2C_SCB_TYPE, (uint8_t)send_data[i], 2ul, &g_stc_i2c_context);
	    }
	  }

	  if(sendstop == true)
    {
      /* Send STOP */
      //retStatus |= Cy_SCB_I2C_MasterSendWriteStop(USER_I2C_SCB_TYPE, 2000ul, &g_stc_i2c_context);
      retStatus |= Cy_SCB_I2C_MasterSendWriteStop(USER_I2C_SCB_TYPE, 2ul, &g_stc_i2c_context);
    }
  }
  else
  {
  	/* Tx Fifo Not empty */
  	retStatus = CY_SCB_I2C_MASTER_NOT_READY;
  }

  return (retStatus);
}

cy_en_scb_i2c_status_t I2C_MasterReceiveData(uint8_t * recv_data, uint8_t length, bool sendstop, uint32_t timeout)
{
  uint8_t i = 0ul;
  uint8_t f_timeout = 0ul;
  uint32_t FifoStatus = 0ul;
  uint32_t waittime_emptyFifo;

  cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_MASTER_NOT_READY;

  waittime_emptyFifo = timeout;

  /* Make sure TX FIFO empty */
  do
  {
    FifoStatus = Cy_SCB_GetNumInRxFifo(USER_I2C_SCB_TYPE);

    if(FifoStatus == 0ul)
    {
      waittime_emptyFifo = 0ul;
      f_timeout = 0ul;
    }
    else
    {
      waittime_emptyFifo--;
      f_timeout = 1ul;
    }
  } while((FifoStatus != 0ul) || (waittime_emptyFifo != 0ul));

  if(f_timeout == 0ul)
  {
    /* Send START and Receive ACK/NACK */
    //retStatus = Cy_SCB_I2C_MasterSendStart(USER_I2C_SCB_TYPE, E_I2C_SLAVE_ADDR, CY_SCB_I2C_READ_XFER, 2000ul, &g_stc_i2c_context);
    retStatus = Cy_SCB_I2C_MasterSendStart(USER_I2C_SCB_TYPE, E_I2C_SLAVE_ADDR, CY_SCB_I2C_READ_XFER, 2ul, &g_stc_i2c_context);

    if(retStatus  == CY_SCB_I2C_SUCCESS)
    {
      for(i=0ul; i<length; i++)
      {
        /* Receive One Byte Data */
        //retStatus |= Cy_SCB_I2C_MasterReadByte(USER_I2C_SCB_TYPE, CY_SCB_I2C_NAK, &recv_data[i], 2000ul, &g_stc_i2c_context);
        retStatus |= Cy_SCB_I2C_MasterReadByte(USER_I2C_SCB_TYPE, CY_SCB_I2C_NAK, &recv_data[i], 2ul, &g_stc_i2c_context);
      }
    }

    if(sendstop == true)
    {
      /* Send NACK (and stop) */
      //retStatus |= Cy_SCB_I2C_MasterSendReadStop(USER_I2C_SCB_TYPE, 2000ul, &g_stc_i2c_context);
      retStatus |= Cy_SCB_I2C_MasterSendReadStop(USER_I2C_SCB_TYPE, 2ul, &g_stc_i2c_context);
    }
  }
  else
  {
  	/* Rx Fifo Not empty */
  	retStatus = CY_SCB_I2C_MASTER_NOT_READY;
  }

  return (retStatus);
}

cy_en_scb_i2c_status_t I2C_MasterReceiveMultiData(uint8_t * recv_data, uint8_t length, bool sendstop, uint32_t timeout)
{
  uint8_t i = 0ul;
  uint8_t f_timeout = 0ul;
  uint32_t FifoStatus = 0ul;
  uint32_t waittime_emptyFifo;

  cy_en_scb_i2c_status_t retStatus = CY_SCB_I2C_MASTER_NOT_READY;

  waittime_emptyFifo = timeout;

  /* Make sure TX FIFO empty */
  do
  {
    FifoStatus = Cy_SCB_GetNumInRxFifo(USER_I2C_SCB_TYPE);

    if(FifoStatus == 0ul)
    {
      waittime_emptyFifo = 0ul;
      f_timeout = 0ul;
    }
    else
    {
      waittime_emptyFifo--;
      f_timeout = 1ul;
    }
  } while((FifoStatus != 0ul) || (waittime_emptyFifo != 0ul));

  if(f_timeout == 0ul)
  {
    /* Send START and Receive ACK/NACK */
    retStatus = Cy_SCB_I2C_MasterSendStart(USER_I2C_SCB_TYPE, E_I2C_SLAVE_ADDR, CY_SCB_I2C_READ_XFER, 2ul, &g_stc_i2c_context);

    if(retStatus  == CY_SCB_I2C_SUCCESS)
    {
      /* Receive Multi Byte Data */
      for(i=0ul; i<(length-1); i++)
      {
          retStatus |= Cy_SCB_I2C_MasterReadByte(USER_I2C_SCB_TYPE, CY_SCB_I2C_ACK, &recv_data[i], 2ul, &g_stc_i2c_context);
      }

      retStatus |= Cy_SCB_I2C_MasterReadByte(USER_I2C_SCB_TYPE, CY_SCB_I2C_NAK, &recv_data[i], 2ul, &g_stc_i2c_context);
    }

    if(sendstop == true)
    {
      /* Send NACK (and stop) */
      //retStatus |= Cy_SCB_I2C_MasterSendReadStop(USER_I2C_SCB_TYPE, 2000ul, &g_stc_i2c_context);
      retStatus |= Cy_SCB_I2C_MasterSendReadStop(USER_I2C_SCB_TYPE, 2ul, &g_stc_i2c_context);
    }
  }
  else
  {
    /* Rx Fifo Not empty */
    retStatus = CY_SCB_I2C_MASTER_NOT_READY;
  }

  return (retStatus);
}

void Scb_I2C_Initialize(void)
{
  Cy_SCB_I2C_DeInit(USER_I2C_SCB_TYPE);
  Cy_SCB_I2C_Init(USER_I2C_SCB_TYPE, &g_stc_i2c_config, &g_stc_i2c_context);
  Cy_SCB_I2C_SetDataRate(USER_I2C_SCB_TYPE, E_I2C_DATARATE, E_I2C_INCLK_TARGET_FREQ);
  Cy_SCB_I2C_RegisterEventCallback(USER_I2C_SCB_TYPE, NULL, &g_stc_i2c_context);
  Cy_SCB_I2C_Enable(USER_I2C_SCB_TYPE);
}

/* [] END OF FILE */

