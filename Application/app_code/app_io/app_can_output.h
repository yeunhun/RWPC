/* Define to prevent recursive inclusion -------------------------------------------------------*/
#ifndef __APP_CAN_OUTPUT_H__
#define __APP_CAN_OUTPUT_H__


#include "WPCType.h"


/*******************************************************************************
  Declare External  Variables
*******************************************************************************/
extern  tAPP_CAN_OUTPUT APP_CAN_OUTPUT_IF;


/*******************************************************************************
  Define  Variables
*******************************************************************************/

/* OUTPUT */

/* OUTPUT B-CAN */

/* OUTPUT L-CAN */


/* OUTPUT INTERNAL */
#define kb_WPCDiagStateTimerStart                    APP_CAN_OUTPUT_IF.WPCDiagStateTimerStart

/* not real output value */
#define kC_WPCDiagState                              APP_CAN_OUTPUT_IF.WPCDiagState

#define  b_CANBUSOFFState                            APP_CAN_OUTPUT_IF.CANBUSOFFState
#define  b_CANBUSOFFState_LCAN                       APP_CAN_OUTPUT_IF.CANBUSOFFState_LCAN


#endif  /* __APP_CAN_OUTPUT_H__ */
