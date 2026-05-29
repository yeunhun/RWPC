
/******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under ST MYLIBERTY SOFTWARE LICENSE AGREEMENT (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/myliberty
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
******************************************************************************/
/*! \file
 *
 *  \author 
 *
 *  \brief Platform header file. Defining platform independent functionality.
 *
 */


/*
 *      PROJECT:   
 *      $Revision: $
 *      LANGUAGE:  ISO C99
 */

/*! \file platform.h
 *
 *  \author Gustavo Patricio
 *
 *  \brief Platform specific definition layer  
 *  
 *  This should contain all platform and hardware specifics such as 
 *  GPIO assignment, system resources, locks, IRQs, etc
 *  
 *  Each distinct platform/system/board must provide this definitions 
 *  for all SW layers to use
 *  
 */

#ifndef PLATFORM_H
#define PLATFORM_H

/*
******************************************************************************
* INCLUDES
******************************************************************************
*/


#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "st_errno.h"

#include "timer.h"
#include "WPC_NFCIC.h"
/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/
#if 0
#define ST25R_SS_PIN            (16u) 							   /*!< GPIO pin used for ST25R SPI SS                */ 
#define ST25R_SS_PORT           (GPIO_PORTA) 					   /*!< GPIO port used for ST25R SPI SS port          */ 

#if defined (__SAMC21G18A__)
#define ST25R_INT_PIN           (22u) 						        /*!< GPIO pin used for ST25R IRQ                   */
#define ST25R_INT_PORT          (GPIO_PORTB) 					    /*!< GPIO port used for ST25R IRQ port             */
#endif

#if defined (__SAMC21J18A__)
#define ST25R_INT_PIN           (16u) //IRQ_3911_Pin        /*!< GPIO pin used for ST25R3911 External Interrupt    */
#define ST25R_INT_PORT          (GPIO_PORTB) //IRQ_3911_GPIO_Port  /*!< GPIO port used for ST25R3911 External Interrupt   */
#endif
#endif
/*
******************************************************************************
* GLOBAL MACROS
******************************************************************************
*/
//#define platformIrqST25R3911Disable()                 ext_irq_disable(int_NFC)           /*!< Disables ST353911 MCU's external interrupt  */
//#define platformIrqST25R3911Enable()                  ext_irq_enable(int_NFC)          /*!< Enables ST353911 MCU's external interrupt   */
#define platformProtectST25RComm()                	  nfcic_Int_DisableIRQ()//ext_irq_disable(int_NFC)		/*!< Protect unique access to ST25R communication channel - IRQ disable on single thread environment (MCU) ; Mutex lock on a multi thread environment      */
#define platformUnprotectST25RComm()              	  nfcic_Int_EnableIRQ()//ext_irq_enable(int_NFC)		/*!< Unprotect unique access to ST25R communication channel - IRQ enable on a single thread environment (MCU) ; Mutex unlock on a multi thread environment */

#define platformProtectST25RIrqStatus()           platformProtectST25RComm()                /*!< Protect unique access to IRQ status var - IRQ disable on single thread environment (MCU) ; Mutex lock on a multi thread environment */
#define platformUnprotectST25RIrqStatus()         platformUnprotectST25RComm()              /*!< Unprotect the IRQ status var - IRQ enable on a single thread environment (MCU) ; Mutex unlock on a multi thread environment         */              

#define platformProtectWorker()                                                                     /* Protect RFAL Worker/Task/Process from concurrent execution on multi thread platforms   */
#define platformUnprotectWorker()                                                                   /* Unprotect RFAL Worker/Task/Process from concurrent execution on multi thread platforms */
//#define platformIrqST25R3911SetCallback( cb )          
//#define platformIrqST25R3911PinInitialize()			
#define platformIrqST25RSetCallback( cb )          
#define platformIrqST25RPinInitialize()
#define platformLedsInitialize()



//#define platformGpioSet( port, pin )                  _gpio_set_level(port, 1U << GPIO_PIN(pin), 1u) //HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET)    /*!< Turns the given GPIO High                   */
//#define platformGpioClear( port, pin )                _gpio_set_level(port, 1U << GPIO_PIN(pin), 0u) //HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET)  /*!< Turns the given GPIO Low                    */
//#define platformGpioToogle( port, pin )               HAL_GPIO_TogglePin(port, pin)                 /*!< Toogles the given GPIO                      */
//#define platformGpioIsHigh( port, pin )               ((_gpio_get_level(port) & (1U << GPIO_PIN(pin))) != 0) //(HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET) /*!< Checks if the given LED is High             */
//#define platformGpioIsLow( port, pin )                (!platformGpioIsHigh(port, pin))              /*!< Checks if the given LED is Low              */
#define platformGpioIsHigh()						  (nfcic_int_pin_levelcheck() == 1u) 
#define platformGpioIsLow()                		  	  (!platformGpioIsHigh())              /*!< Checks if the given LED is Low              */

#define platformTimerCreate( t )                      timerCalculateTimer(t)                        /*!< Create a timer with the given time (ms)     */
#define platformTimerIsExpired( timer )               timerIsExpired(timer)                         /*!< Checks if the given timer is expired        */
#define platformTimerDestroy( timer )                                                               /*!< Stop and release the given timer            */
#define platformDelay( t )                            // HAL_Delay( t )                                /*!< Performs a delay for the given time (ms)    */
#define platformGetSysTick()                          (g1msCnt)//get_ticktimer()//HAL_GetTick()                                 /*!< Get System Tick ( 1 tick = 1 ms)            */

#define platformErrorHandle()                         //_Error_Handler(__FILE__,__LINE__)             /*!< Global error handler or trap                 */

#define platformSpiSelect()                           nfcic_Select()//platformGpioClear(ST25R_SS_PORT, ST25R_SS_PIN) /*!< SPI SS\CS: Chip|Slave Select                */
#define platformSpiDeselect()                         nfcic_Deselect()//platformGpioSet(ST25R_SS_PORT, ST25R_SS_PIN)   /*!< SPI SS\CS: Chip|Slave Deselect              */
#define platformSpiTxRx( txBuf, rxBuf, len )          nfcic_SpiTxRx(txBuf, rxBuf, len)//NFC_spi_tranceiver(txBuf, rxBuf, len) //LPSPI_DRV_MasterTransfer(LPSPICOM1, txBuf, rxBuf, len)                    /*!< SPI transceive                              */

#define platformI2CTx( txBuf, len )                                                                 /*!< I2C Transmit                                */
#define platformI2CRx( txBuf, len )                                                                 /*!< I2C Receive                                 */
#define platformI2CStart()                                                                          /*!< I2C Start condition                         */
#define platformI2CStop()                                                                           /*!< I2C Stop condition                          */
#define platformI2CRepeatStart()                                                                    /*!< I2C Repeat Start                            */
#define platformI2CSlaveAddrWR(add)                                                                 /*!< I2C Slave address for Write operation       */
#define platformI2CSlaveAddrRD(add)                                                                 /*!< I2C Slave address for Read operation        */

#define platformLog(...)                                                                            /*!< Log method                                  */


/*
******************************************************************************
* RFAL FEATURES CONFIGURATION
******************************************************************************
*/

#if 0
#define RFAL_FEATURE_NFCA                      true                   /*!< Enable/Disable RFAL support for NFC-A (ISO14443A)                         */
#define RFAL_FEATURE_NFCB                      true                   /*!< Enable/Disable RFAL support for NFC-B (ISO14443B)                         */
#define RFAL_FEATURE_NFCF                      true                   /*!< Enable/Disable RFAL support for NFC-F (FeliCa)                            */
#define RFAL_FEATURE_NFCV                      true                   /*!< Enable/Disable RFAL support for NFC-V (ISO15693)                          */
#define RFAL_FEATURE_T1T                       true                   /*!< Enable/Disable RFAL support for T1T (Topaz)                               */
#define RFAL_FEATURE_ST25TB                    true                   /*!< Enable/Disable RFAL support for ST25TB                                    */
#define RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG     true                   /*!< Enable/Disable Analog Configs to be dynamically updated (RAM)             */
#define RFAL_FEATURE_DYNAMIC_POWER             false                  /*!< Enable/Disable RFAL dynamic power support                                 */
#define RFAL_FEATURE_ISO_DEP                   true                   /*!< Enable/Disable RFAL support for ISO-DEP (ISO14443-4)                      */
#define RFAL_FEATURE_NFC_DEP                   true                   /*!< Enable/Disable RFAL support for NFC-DEP (NFCIP1/P2P)                      */
#endif

#define RFAL_FEATURE_LISTEN_MODE               false       /*!< Enable/Disable RFAL support for Listen Mode                               */
#define RFAL_FEATURE_WAKEUP_MODE               true       /*!< Enable/Disable RFAL support for the Wake-Up mode						  */
#define RFAL_FEATURE_LOWPOWER_MODE             true       /*!< Enable/Disable RFAL support for the Low Power mode                        */
#define RFAL_FEATURE_NFCA                      true       /*!< Enable/Disable RFAL support for NFC-A (ISO14443A)                         */
#define RFAL_FEATURE_NFCB                      false       /*!< Enable/Disable RFAL support for NFC-B (ISO14443B)                         */
#define RFAL_FEATURE_NFCF                      false       /*!< Enable/Disable RFAL support for NFC-F (FeliCa)                            */
#define RFAL_FEATURE_NFCV                      false       /*!< Enable/Disable RFAL support for NFC-V (ISO15693)                          */
#define RFAL_FEATURE_T1T                       false       /*!< Enable/Disable RFAL support for T1T (Topaz)                               */
#define RFAL_FEATURE_T2T                       false       /*!< Enable/Disable RFAL support for T2T (Mifare)                              */
#define RFAL_FEATURE_T4T                       true       /*!< Enable/Disable RFAL support for T4T                                       */
#define RFAL_FEATURE_ST25TB                    false       /*!< Enable/Disable RFAL support for ST25TB                                    */
#define RFAL_FEATURE_ST25xV                    false       /*!< Enable/Disable RFAL support for  ST25TV/ST25DV                            */
#define RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG     false      /*!< Enable/Disable Analog Configs to be dynamically updated (RAM)             */
#define RFAL_FEATURE_DPO                       false      /*!< Enable/Disable RFAL dynamic power support                                 */
#define RFAL_FEATURE_ISO_DEP                   true       /*!< Enable/Disable RFAL support for ISO-DEP (ISO14443-4)                      */
#define RFAL_FEATURE_ISO_DEP_POLL              true       /*!< Enable/Disable RFAL support for Poller mode (PCD) ISO-DEP (ISO14443-4)    */
#define RFAL_FEATURE_ISO_DEP_LISTEN            false       /*!< Enable/Disable RFAL support for Listen mode (PICC) ISO-DEP (ISO14443-4)   */
#define RFAL_FEATURE_NFC_DEP                   false       /*!< Enable/Disable RFAL support for NFC-DEP (NFCIP1/P2P)                      */

#define RFAL_FEATURE_ISO_DEP_IBLOCK_MAX_LEN    256U       /*!< ISO-DEP I-Block max length. Please use values as defined by rfalIsoDepFSx */
#define RFAL_FEATURE_NFC_DEP_BLOCK_MAX_LEN     254U       /*!< NFC-DEP Block/Payload length. Allowed values: 64, 128, 192, 254           */
#define RFAL_FEATURE_NFC_RF_BUF_LEN            258U       /*!< RF buffer length used by RFAL NFC layer                                   */

#define RFAL_FEATURE_ISO_DEP_APDU_MAX_LEN      1024U       /*!< ISO-DEP APDU max length. Please use multiples of I-Block max length       */
#define RFAL_FEATURE_NFC_DEP_PDU_MAX_LEN       512U       /*!< NFC-DEP PDU max length.                                                   */

/*
******************************************************************************
* RFAL CUSTOM SETTINGS
******************************************************************************
  Custom analog configs are used to cope with Automatic Antenna Tuning (AAT)
  that are optimized differently for each board.
*/
//#define RFAL_ANALOG_CONFIG_CUSTOM                         /*!< Use Custom Analog Configs when defined                                    */


/*************************/
#define ST25R3916

/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

