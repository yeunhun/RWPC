/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Btl_Types.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : This file provides common type definitions for the bootloader **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     18-Jul-2019   Sinil        Initial version                       **
*******************************************************************************/

#ifndef BTL_TYPES_H
#define BTL_TYPES_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#define MEM_ENABLE_SET_RESETVECTOR_API                                   STD_OFF

#define MODULE_IDLE                                                        0x00U
#define MODULE_UNINIT                                                      0x01U
#define MODULE_BUSY                                                        0x0AU
#define MODULE_BUSY_INTERNAL                                               0x0BU

#define MEM_ACT_TYPE_READ                                                  0x01U
#define MEM_ACT_TYPE_WRITE                                                 0x02U
#define MEM_ACT_TYPE_ERASE                                                 0x04U
#define MEM_ACT_TYPE_BLOCKED                                               0x00U

#define JOB_OK                                                             0x00U
#define JOB_NOT_OK                                                         0x01U
#define JOB_PENDING                                                        0x0AU

/* Initialize library macros */
#define MEM_INIT_CFLASH                                           ((uint8)0x01u)
#define MEM_INIT_DFLASH                                           ((uint8)0x02u)
#define MEM_INIT_CFLASH_AND_DFLASH                                ((uint8)0x03u)

/* Common error codes */
/* Function call successful */
#define MEM_OK                                            ((Mem_ErrorType)0x00u)
#define MEM_BUSY                                          ((Mem_ErrorType)0x02u)
/* Function call failed */
#define MEM_FAILED                                        ((Mem_ErrorType)0x01u)

/* Invalid parameter */
#define MEM_INVALID_PARAM                                 ((Mem_ErrorType)0x03u)
/* Invalid Memory address */
#define MEM_INVALID_ADDRESS                               ((Mem_ErrorType)0x04u)
/* Invalid Memory size */
#define MEM_INVALID_SIZE                                  ((Mem_ErrorType)0x05u)
/* Invalid version */
#define MEM_INVALID_VERSION                               ((Mem_ErrorType)0x09u)

/* Routine specific error codes */
/* Error during Memory initialization */
#define MEM_FCT_INIT                                      ((Mem_ErrorType)0x00u)
/* Error during Memory de-init */
#define MEM_FCT_DEINIT                                    ((Mem_ErrorType)0x20u)
/* Error during Memory erase */
#define MEM_FCT_ERASE                                     ((Mem_ErrorType)0x40u)
/* Error during Memory write */
#define MEM_FCT_WRITE                                     ((Mem_ErrorType)0x60u)
/* Error during Memory read */
#define MEM_FCT_READ                                      ((Mem_ErrorType)0x80u)

/* Memory init error codes */
#define MEM_INIT_FAILED               ((Mem_ErrorType)(MEM_FCT_INIT|MEM_FAILED))
#define MEM_INIT_INVALID_PARAM \
  ((Mem_ErrorType)(MEM_FCT_INIT|MEM_INVALID_PARAM))
#define MEM_INIT_INVALID_VERSION \
  ((Mem_ErrorType)(MEM_FCT_INIT|MEM_INVALID_VERSION))

/* Memory erase error codes */
#define MEM_ERASE_FAILED             ((Mem_ErrorType)(MEM_FCT_ERASE|MEM_FAILED))
#define MEM_ERASE_INVALID_ADDR \
  ((Mem_ErrorType)(MEM_FCT_ERASE|MEM_INVALID_ADDRESS))
#define MEM_ERASE_INVALID_SIZE \
  ((Mem_ErrorType)(MEM_FCT_ERASE|MEM_INVALID_SIZE))


/* Memory write error codes */
#define MEM_WRITE_FAILED             ((Mem_ErrorType)(MEM_FCT_WRITE|MEM_FAILED))
#define MEM_WRITE_INVALID_ADDR \
  ((Mem_ErrorType)(MEM_FCT_WRITE|MEM_INVALID_ADDRESS))
#define MEM_WRITE_INVALID_SIZE \
  ((Mem_ErrorType)(MEM_FCT_WRITE|MEM_INVALID_SIZE))


/* Memory read error codes */
#define MEM_READ_FAILED                                (MEM_FCT_READ|MEM_FAILED)
#define MEM_READ_INVALID_ADDR                 (MEM_FCT_READ|MEM_INVALID_ADDRESS)
#define MEM_READ_INVALID_SIZE                    (MEM_FCT_READ|MEM_INVALID_SIZE)

#define MEM_ZERO                                                       (uint8)0u
#define MEM_ONE                                                        (uint8)1u
#define MEM_ZERO_SIZE                                           (Mem_SizeType)0U
#define MEM_SIZE_ONE                                            (Mem_SizeType)1u
#define MEM_SIZE_TWO                                            (Mem_SizeType)2u
#define MEM_SIZE_FOUR                                           (Mem_SizeType)4u

#define MEM_INDEX_ZERO                                                        0U
#define MEM_INDEX_ONE                                                         1U
#define MEM_INDEX_TWO                                                         2U
#define MEM_INDEX_THREE                                                       3U

#define MEM_RAM_CLR_VALUE                                                   0x0U
#define MEM_ZERO_ADDRESS                                  (Mem_PositionType)0x0U
#define MEM_INITIAL_INDEX                                                   0x0U

#define MEM_LONG_WD_TRIGGER                                                   1u
#define MEM_SHORT_WD_TRIGGER                                                  2u

/* Macro for invalid block */
#define MEM_INVALID_BLK                                                    0xFFU

/* Macro for invalid page index */
#define MEM_INVALID_PAGE_INDEX                                             0xFFU

/* Memory function */
#define MEM_DRIVER_INIT(FlashFuncPtr,Mem_Param)\
         ((Mem_Fct)(FlashFuncPtr->dt_MemInitFct))(Mem_Param)

#define MEM_DRIVER_DEINIT(FlashFuncPtr,Mem_Param)\
         ((Mem_Fct)(FlashFuncPtr->dt_MemDeinitFct))(Mem_Param)

#define MEM_DRIVER_ERASE(FlashFuncPtr,Mem_Param)\
         ((Mem_Fct)(FlashFuncPtr->dt_MemEraseFct))(Mem_Param)

#define MEM_DRIVER_WRITE(FlashFuncPtr,Mem_Param)\
         ((Mem_Fct)(FlashFuncPtr->dt_MemWriteFct))(Mem_Param)

#define MEM_DRIVER_READ(FlashFuncPtr,Mem_Param)\
         ((Mem_Fct)(FlashFuncPtr->dt_MemReadFct))(Mem_Param)

#define GET_MEM_DRIVER_VERSION(Lpst_MemHeaderPtr)  (Lpst_MemHeaderPtr->u8_Version)

#define GET_MEM_DRIVER_MASKTYPE(Lpst_MemHeaderPtr) (Lpst_MemHeaderPtr->u8_MaskType)

#define GET_MEM_DRIVER_CPUTYPE(Lpst_MemHeaderPtr)  (Lpst_MemHeaderPtr->u8_CPUType)

/*******************************************************************************
**                              Type Definition                               **
*******************************************************************************/
typedef uint8 Std_StatusType;
typedef uint8 Mem_AccessType;
typedef uint8 Std_JobReturnType;

typedef uint32 Mem_SizeType;
typedef uint32 Mem_PositionType;
typedef uint16 Mem_ErrorType;
typedef uint8* Mem_MemPtrType;
typedef uint32 Mem_VersionType;

typedef uint8 Mem_BlockIdType;

/* Major Version number */
typedef uint8 Mem_MajorNumberType;

/* Minor version number */
typedef uint8 Mem_MinorNumberType;

/* Bugfix / dt_PatchLevel version number */
typedef uint8 Mem_BugFixVersionType;

/* Result of flash driver routines */
typedef uint16 Mem_OpertnResultType;

/* Watchdog trigger routine */
typedef void (*Mem_WDTriggerFct) (uint8 Lu8_CbkType);

typedef struct
{
  /* Initialization: in-out parameters */
  Mem_BugFixVersionType  dt_PatchLevel;                  /* Memory driver patch level version */
  Mem_MinorNumberType    dt_MinorNumber;                 /* Memory driver minor version number */
  Mem_MajorNumberType    dt_MajorNumber;                 /* Memory driver major version number */
  uint8                  u8_Reserved1;                   /* Reserved for future use, set to 0x00 for now */
  /* Return value / Error code: output parameters */
  Mem_OpertnResultType   dt_ErrorCode;                   /* Return value / error code */
  uint16                 u16_Reserved2;                  /* Reserved for future use, set to 0x0000 for now */
  /* Erase / Write: input parameters */
  Mem_PositionType       dt_Address;                     /* Logical target address */
  Mem_SizeType           dt_Length;                      /* Length information (in bytes) */
  Mem_MemPtrType         dt_Data;                        /* Pointer to data buffer */
  /* Additional input parameters */
  Mem_WDTriggerFct       dt_WdTriggerFct;                /* Pointer to watchdog trigger routine */
  /* Erase / Write: optional output parameters: debugging information */
  Mem_MemPtrType         adt_IntendedData[MEM_SIZE_TWO]; /* Intended data at error address */
  Mem_MemPtrType         adt_ActualData[MEM_SIZE_TWO];   /* Actual data at error address */
  Mem_PositionType       dt_ErrorAddress;                /* Address of error */
  uint16                 u16_FrequencyMHz;               /* Frequency of clock source */
  uint32                 au32_AuthID[MEM_SIZE_FOUR];     /* Authentication ID for flash access */
  /* Additional controller /Hardware specific parameters */
  /* To be specified by Memory driver vendor */
} Mem_Param_Styp;

/* Flash function pointer */
typedef void (*Mem_Fct)(Mem_Param_Styp* Lpst_Mem_Param);

/* Memory driver header */
typedef struct
{
  uint8 u8_Version;             /* Version of downloaded flash driver */
  uint8 u8_Reserved;            /* Reserved for future use */
  uint8 u8_MaskType;            /* Memory cell mask type */
  uint8 u8_CPUType;             /* Microcontroller type */
  Mem_Fct dt_MemInitFct;        /* Function pointer to init function */
  Mem_Fct dt_MemDeinitFct;      /* Function pointer to de-init function */
  Mem_Fct dt_MemEraseFct;       /* Function pointer to erase function */
  Mem_Fct dt_MemWriteFct;       /* Function pointer to write function */
  Mem_Fct dt_MemReadFct;        /* Function pointer to read function */
  #if (MEM_ENABLE_SET_RESETVECTOR_API == STD_ON)
  Mem_Fct dt_MemSetResetFct;    /* Function pointer to set reset vector */
  #endif /* MEM_ENABLE_SET_RESETVECTOR_API */
} Mem_Header_Styp;

/*******************************************************************************
**                      Global Data Types (ECU independent)                   **
*******************************************************************************/
typedef enum
{
  ETH_RECEIVED = 0,                 /* A frame has been received and there are no more frames in the queue */
  ETH_NOT_RECEIVED,                 /* No frames received */
  ETH_RECEIVED_MORE_DATA_AVAILABLE, /* A frame received and at least another one in the queue detected */
  ETH_RECEIVED_FRAMES_LOST          /* Ethernet frame has been received, some frames got lost */
} Eth_RxStatus_Etyp;

#endif /* BTL_TYPES_H */

/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
