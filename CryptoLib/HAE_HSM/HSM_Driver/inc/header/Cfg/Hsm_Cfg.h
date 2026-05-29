/*!
  @file Hsm_Cfg.h
  @brief HSM driver configuruation header file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef HSM_CFG_H_
#define HSM_CFG_H_

/******************************************************************************/
/*                    HSM Driver End User Configuration                       */
/******************************************************************************/

/* Communication Mode */
#define START_SYNC
#define UPDATE_ASYNC
#define FINISH_SYNC

#if defined (START_SYNC)
#define COM_MODE_START (SYNC_MODE)
#elif defined (START_ASYNC)
#define COM_MODE_START (ASYNC_MODE)
#endif

#if defined (UPDATE_SYNC)
#define COM_MODE_UPDATE (SYNC_MODE)
#elif defined (UPDATE_ASYNC)
#define COM_MODE_UPDATE (ASYNC_MODE)
#endif

#if defined (FINISH_SYNC)
#define COM_MODE_FINISH (SYNC_MODE)
#elif defined (FINISH_ASYNC)
#define COM_MODE_FINISH (ASYNC_MODE)
#endif

#endif /* HSM_CFG_H_ */
