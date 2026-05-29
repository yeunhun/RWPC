#ifndef __APP_SLEEP_VAR_H__
#define __APP_SLEEP_VAR_H__





extern  tAPP_SLEEP  APP_SLEEP_IF;


/* e_LocalInput */
#define Slpwup_NvMJobFinished               APP_SLEEP_IF.Slpwup_NvMJobFinished

#define First_FullComMode_BCAN              APP_SLEEP_IF.First_FullComMode_BCAN
#define First_FullComMode_LCAN              APP_SLEEP_IF.First_FullComMode_LCAN

#define ComMNoti_BCAN                       APP_SLEEP_IF.ComMNoti_BCAN
#define ComMNoti_LCAN                       APP_SLEEP_IF.ComMNoti_LCAN

#define LddPrevBusState                     APP_SLEEP_IF.LddPrevBusState
#define LddNextBusState                     APP_SLEEP_IF.LddNextBusState

#define LddPrevEcuMode                      APP_SLEEP_IF.LddPrevEcuMode
#define LddNextEcuMode                      APP_SLEEP_IF.LddNextEcuMode
#define LddCurrEcuMode                      APP_SLEEP_IF.LddCurrEcuMode




#endif  /* __APP_SLEEP_VAR_H__ */
