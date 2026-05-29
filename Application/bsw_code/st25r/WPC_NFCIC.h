#ifndef _WPC_NFCIC_H
#define _WPC_NFCIC_H

#include "string.h"
#include "WPCType.h"

// ST RFAL
#define ST_MEMMOVE          memmove     /*!< map memmove to string library code */
#define ST_MEMCPY           memcpy      /*!< map memcpy to string library code  */
#define ST_MEMSET           memset      /*!< map memset to string library code  */
#define ST_BYTECMP          memcmp      /*!< map bytecmp to string library code */

/*******************************************************************************
* Global Data Types
*******************************************************************************/

/*******************************************************************************
  Declare External  Variables
*******************************************************************************/

/*******************************************************************************
  Declare External  Function
*******************************************************************************/

/***********************************************************************************************************************
* Global Function Prototypes (Declarations)
***********************************************************************************************************************/
void nfcic_SpiTxRx(const u8 *txbuf, u8 *rxbuf, u16 length);
void nfcic_Select(void);
void nfcic_Deselect(void);

void nfcic_Int_EnableIRQ(void);

void nfcic_Int_DisableIRQ(void);

IoHwAb_LevelType nfcic_int_pin_levelcheck(void);
void nfc_ticktimer_start(void);
void nfc_ticktimer_stop(void);
IoHwAb_GptValueType get_ticktimer(void);
void nfc_ticktimer_Cbk(void);

#endif
