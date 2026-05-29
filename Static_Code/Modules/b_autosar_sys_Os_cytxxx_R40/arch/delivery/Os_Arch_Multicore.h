/*******************************************************************************
**                                                                            **
**  (C) 2020 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Os_Arch_Multicore.h                                           **
**                                                                            **
**  TARGET    : CYTxxx                                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for CYTxxx related multicore API                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:    Yes                                       **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 2.1.0     11-Dec-2020    JH.Cho        Redmine #26391                      **
** 1.0.0     23-Dec-2019    MJ.Woo        Redmine #18913                      **
*******************************************************************************/
#ifndef OS_ARCH_MULTICORE_H_
#define OS_ARCH_MULTICORE_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Arch_Regs.h"
#include "Os_PortTypes.h"
#include "Os_Multicore.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (OS_MULTICORE == STD_ON)
/* Defines IPC Index */
#define  OS_IC_0_IPC_INDEX             (4u)
#define  OS_IC_1_IPC_INDEX             (5u)
#define  OS_SPINLOCK_IPC_INDEX         (6u)

/* Defines a value to indicate that no notification events are needed */
#define OS_IPC_NO_NOTIFICATION         (uint32)(0x00000000ul)

/* Defines function return status */
#define OS_IPC_DRV_SUCCESS             (0u)
#define OS_IPC_DRV_ERROR               (1u)

/* Pointer to IPC structure used for semaphores */
static volatile OS_IPC_STRUCT_type* os_semaIpcStruct = &OS_IPC_ADDR->STRUCT[OS_SPINLOCK_IPC_INDEX];

#endif /* if (OS_MULTICORE == STD_ON) */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (OS_MULTICORE == STD_ON)
extern FUNC(void, OS_CODE) Os_NotifyCore(uint32 core);
extern FUNC(void, OS_CODE) Os_AckNotifyCore(uint32 core);
extern FUNC(void, OS_CODE) Os_InterCoreInterruptHandler(void);

/*******************************************************************************
** Function Name        : OS_IPC_Drv_LockAcquire                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to acquire the IPC channel.   **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : base                                                **
**                        : This parameter is a handle that represents the    **
**                          base address of the registers of the IPC channel. **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : OS_IPC_DRV_SUCCESS                                  **
**                        : Function was successfully executed                **
**                        OS_IPC_DRV_ERROR                                    **
**                        : The IPC was not acquired because it was           **
**                          already acquired by another master                **
**                                                                            **
** Preconditions        : StartOs() function should be called                 **
**                                                                            **
**                                                                            **
*******************************************************************************/
static inline uint8 OS_IPC_Drv_LockAcquire (volatile OS_IPC_STRUCT_type const * base)
{
    uint8 retStatus;

    if( 0ul != base->ACQUIRE.B.SUCCESS )
    {
        retStatus = OS_IPC_DRV_SUCCESS;
    }
    else
    {
        retStatus = OS_IPC_DRV_ERROR;
    }
    return(retStatus);
}

/*******************************************************************************
** Function Name        : OS_IPC_Drv_ReleaseNotify                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function generates a notify event to            **
**                        an IPC interrupt structure.                         **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : base                                                **
**                        : This parameter is a handle that represents the    **
**                          base address of the registers of the IPC channel. **
**                        notifyEventIntr                                     **
**                        : Bit encoded list of IPC interrupt lines that      **
**                          are triggered by a notification                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Void                                                **
**                                                                            **
** Preconditions        : StartOs() function should be called                 **
**                                                                            **
**                                                                            **
*******************************************************************************/
static inline void  OS_IPC_Drv_ReleaseNotify (volatile OS_IPC_STRUCT_type* base, uint32 notifyEventIntr)
{
    OS_IPC_STRUCT_RELEASE_type reg = { 0 };
    reg.B.INTR_RELEASE = notifyEventIntr;
    base->RELEASE.U = reg.U;
}

/*******************************************************************************
** Function Name        : OS_IPC_Drv_LockAcquire                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is used to test the status of          **
**                        an IPC channel. The function tells the reader if    **
**                        the IPC channel was in the locked or released state.**
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : base                                                **
**                        : This parameter is a handle that represents the    ** 
**                          base address of the registers of the IPC channel. **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : true                                                **
**                        : The IPC channel is in the Locked state.           **
**                        false                                               **
**                        : The IPC channel is in the Released state.         **
**                                                                            **
** Preconditions        : StartOs() function should be called                 **
**                                                                            **
**                                                                            **
*******************************************************************************/
static inline uint8 OS_IPC_Drv_IsLockAcquired (volatile OS_IPC_STRUCT_type const * base)
{
    return ( 0u != base->LOCK_STATUS.B.ACQUIRED );
}

/*******************************************************************************
** Function Name        : OS_IPC_Drv_LockRelease                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is used to release an IPC channel      **
**                        from the locked state.                              **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : base                                                **
**                        : This parameter is a handle that represents the    **
**                          base address of the registers of the IPC channel. **
**                        releaseEventIntr                                    **
**                        : Bit encoded list of IPC interrupt lines that      **
**                          are triggered by a release event.                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : OS_IPC_DRV_SUCCESS                                  **
**                        : The function executed successfully                **
**                          and the IPC channel was released.                 **
**                        OS_IPC_DRV_ERROR                                    **
**                        : The IPC channel is in the Released state.         **
**                                                                            **
** Preconditions        : StartOs() function should be called                 **
**                                                                            **
**                                                                            **
*******************************************************************************/
static inline uint8 OS_IPC_Drv_LockRelease (volatile OS_IPC_STRUCT_type* base, uint32 releaseEventIntr)
{
  uint8 retStatus;

  /* Check to make sure the IPC is Acquired */
  if( OS_IPC_Drv_IsLockAcquired(base) )
  {
    /* The IPC was acquired, release the IPC channel */
    OS_IPC_Drv_ReleaseNotify(base, releaseEventIntr);

    retStatus = OS_IPC_DRV_SUCCESS;
  }
  else   /* The IPC channel was already released (not acquired) */
  {
    retStatus = OS_IPC_DRV_ERROR;
  }
  return(retStatus);
}

#endif /* if (OS_MULTICORE == STD_ON) */

#endif /* OS_ARCH_MULTICORE_H_ */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

