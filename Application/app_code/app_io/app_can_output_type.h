/* Define to prevent recursive inclusion -------------------------------------------------------*/
#ifndef __APP_CAN_OUTPUT_TYPE_H__
#define __APP_CAN_OUTPUT_TYPE_H__


#include "Rte_Type.h"
#include "WPCType.h"





/*******************************************************************************
  Define Variables Type
*******************************************************************************/
typedef struct
{
  tVAR WPCDiagStateTimerStart;

  /* not real output value */
  tVAR  WPCDiagState;                        /* Diag Timeout for Diag logic : 5s */

  tVAR  CANBUSOFFState;
  tVAR  CANBUSOFFState_LCAN;
}tAPP_CAN_OUTPUT;

#endif  /* __APP_CAN_OUTPUT_TYPE_H__ */
