#ifndef __APP_SLEEP_VAR_TYPE_H__
#define __APP_SLEEP_VAR_TYPE_H__

#include "Rte_Type.h"




typedef struct
{
  tVAR  Slpwup_NvMJobFinished;

  tVAR  First_FullComMode_BCAN;
  tVAR  First_FullComMode_LCAN;

  tVAR  ComMNoti_BCAN;
  tVAR  ComMNoti_LCAN;

  tVAR  LddPrevBusState;
  tVAR  LddNextBusState;

  tVAR  LddPrevEcuMode;
  tVAR  LddNextEcuMode;
  tVAR  LddCurrEcuMode;
}tAPP_SLEEP;





#endif  /* __APP_SLEEP_VAR_TYPE_H__ */
