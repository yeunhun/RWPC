/*
 * DN8_WPC_Init.h
 *
 *  Created on: 2017. 9. 13.
 *      Author: Seoyon
 */

#ifndef WPC_INITIALIZATION_H_
#define WPC_INITIALIZATION_H_




/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++                   EXTERNAL FUNCTION
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

uint8 IsInit(void);
uint8 IsReset(void);
void ClearReset(void);
uint8 WPC_Initialize(void);
void WPC_Setting_Option(void);
void Init_Eeprom_OK(void);


#endif /* WPC_10W_INIT_H_ */
