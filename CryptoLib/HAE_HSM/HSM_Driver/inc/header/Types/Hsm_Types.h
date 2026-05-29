/*!
  @file Hsm_Types.h
  @brief HSM type definition header file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef HSM_TYPES_H_
#define HSM_TYPES_H_

#ifndef UINT64
/** 64 bit unsigned integer. */
#define UINT64 unsigned long long /*           0 .. 18446744073709551615, */
#endif

#ifndef UINT32
/** 32 bit unsigned integer. */
#define UINT32 unsigned long /*           0 .. 4294967295, */
#endif

#ifndef UINT16
/** 16 bit unsigned integer. */
#define UINT16 unsigned short /*           0 .. 65535,*/
#endif

#ifndef UINT8
/** 8 bit unsigned integer. */
#define UINT8 unsigned char /*           0 .. 255, 0xff             */
#endif

#ifndef SINT8
#define SINT8 signed char /*        -128 .. +127(7F) */
#endif

#ifndef SINT16
#define SINT16 signed short /*      -32768 .. +32767 (0x7FFF)*/
#endif

#ifndef SINT32
#define SINT32 signed long /* -2147483648 .. +2147483647(0x7FFF FFFF)     */
#endif

#ifndef BOOL
#define BOOL unsigned char /* -2147483648 .. +2147483647(0x7FFF FFFF)     */
#endif

#ifndef VUINT32
#define VUINT32 volatile unsigned long // -2147483648 .. +2147483647(0x7FFF FFFF)
#endif

#ifndef VUINT8
#define VUINT8 volatile unsigned char //0 .. 255, 0xff
#endif

#ifndef VUINT16
#define VUINT16 volatile unsigned short //0 .. 65535,
#endif

#ifndef ARR_SIZE
	#define ARR_SIZE
	#define ARR_SIZE_1024 (1024u)
	#define ARR_SIZE_32 (32u)
	#define ARR_SIZE_16 (16u)
#endif

#if 0	// Not used after V2.4.5
#ifndef NULL
	#define NULL ((void *)0)
#endif
#endif

#ifndef FALSE
	#define FALSE 0U
#endif

#ifndef TRUE
	#define TRUE 1U
#endif


/* All errors of API services */
#if defined(STATUSTYPEDEFINED)
/* another AUTOSAR component has already defined the status type */
#else
	#define STATUSTYPEDEFINED
	#define Std_ReturnType					UINT8
	#define E_OK 							((UINT8)0x00)       /*!< This is returned when a function execution is successful */
	#define E_NOT_OK 						((UINT8)0x01)       /*!< This is returned when a function execution fails */
#endif
	#define HSM_E_BUSY  					((UINT8)0x02)       /*!< HSM internal task is busy. \n
                                                                    If you call same type of Crypto API even though the previous task has not finished (NOT Finish Phase), \n
                                                                    it causes corruption in task. The HOST should call the function again after HSM internal job is done. \n
                                                                    (refer to HSM_WaitResp) */
	#define HSM_E_WAIT  					((UINT8)0x03)       /*!< This value usually returned by calling Update API. \n
                                                                    If API should be wait until the result of the previous API call, \n
                                                                    its return value ‘HSM_E_WAIT’ means HSM is still working with HOST’s request. \n
                                                                    (refer to HSM_WaitResp) */
	#define HSM_E_WRONG_SEQ  				((UINT8)0x04)       /*!< API call sequence is incorrect */
	#define HSM_E_NOT_SUPPORTED  			((UINT8)0x05)       /*!< Not supported feature in HSM Framework */
	#define HSM_E_LENGTH_NOT_VALID  		((UINT8)0x06)       /*!< Invalid parameter length */
	#define HSM_E_VALUE_NOT_VALID			((UINT8)0x07)       /*!< Invalid parameter value */
	#define HSM_E_KEY_NOT_VALID				((UINT8)0x08)       /*!< Invalid key index parameter */
	#define HSM_E_UNINIT					((UINT8)0x09)       /*!< HSM_DriverInitialize is not performed */
	#define HSM_E_HW_RST					((UINT8)0x10)		/*!< HW block reset	*/
    #define HSM_E_VERSION_MISMATCH          ((UINT8)0x11)		/*!< Driver and HSM version is not compatible */
	#define HSM_E_HW_ERR					((UINT8)0x12)

typedef struct
{
	UINT16 jobId;                                       /*!< Crypto Service Job ID */
	UINT16 taskPriority;                                /*!< Crypto Service Task Priority */
	UINT16 mode;                                        /*!< only used in AES Crypto Service */
	UINT16 apiProcessMode;                              /*!< Set blocking = 0 / non-blocking = 1 mode */
} HSMAPI_CTX_t;

typedef struct
{
	HSMAPI_CTX_t apiCtx;
	UINT32 outputLen;
	UINT8 *outputPtr;
} HSMAPI_OBJ_t;

typedef enum
{
    HSM_API_BLOCKING_MODE = 0,
    HSM_API_NON_BLOCKING_MODE = 1
} HSM_API_OP_MODE;

typedef enum
{
    SYNC_MODE = 1,
    ASYNC_MODE = 2
} COM_MODE;

typedef struct
{
    UINT16 cmd;
    UINT16 taskPriority;
    UINT16 jobId;
    UINT16 keyNum;
    COM_MODE synchMode;
	UINT8 *sendData;
	UINT32 sendDataLength;
	UINT8 *recvData;
	UINT32 recvDataLength;
} HSM_REQ_INFO_t;

typedef enum
{
	HSM_VERIFY_SUCCESS = 0,
	HSM_VERIFY_FAILURE
} HSM_VERIFY_RT;

//driver only err code
//you can add items freely
typedef enum
{
	HSM_ERR_NOERROR = 0,                                /*!< No Error */
	HSM_ERR_TIMEOUT = 0xA1,                             /*!< No response received from the HSM within the time limit */
	HSM_ERR_INVALID_KEY_NUM = 0xA2,                     /*!< Invalid input key number at HSM input */
	HSM_ERR_INVALID_INPUT_LENGTH = 0xA3,                /*!< Invalid input data length at HSM input */
	HSM_ERR_INVALID_VALUE = 0xA4,                       /*!< Invalid input data value at HSM input */
	HSM_ERR_INVALID_JOBID = 0xA5,                       /*!< Service requested with invalid JOB ID */
	HSM_ERR_WRONG_SEQ = 0xA6,                           /*!< Service not requested in correct order */
	HSM_ERR_NO_FUNCTION = 0xA7,                         /*!< Requested feature not provided by the HSM framework */
	HSM_ERR_FAIL = 0xA8,                                /*!< FAIL occurred during HSM Framework work (HAE inquiry) */
	HSM_ERR_HSM_TEMP_STOP_STATE = 0xA9,                 /*!< HSM Framework is pasused */
	HSM_ERR_UNKOWN = 0xAF,                              /*!< Other errors */

	/* Initialize Error Code */
	HSM_ERR_INIT_FAIL_SET_HSM_INIT_DONE = 0x0A00,       /*!< HSM does not receive an Init done message */
	HSM_ERR_INIT_FAIL_GET_INITIALIZE_VALUE,             /*!< HSM does not receive the correct Initialize result */
	HSM_ERR_INIT_HOSTBUFFER_CHECK_ERROR,                /*!< HOST Buffer check error during Initialize */
	HSM_ERR_INIT_HSMBUFFER_CHECK_ERROR,                 /*!< HSM Buffer check error during Initialize */
	HSM_ERR_INIT_SEND_INIT_MSG_TIMEOUT,                 /*!< Timeout after sending Buffer Set message */
	HSM_ERR_INIT_GET_WRONG_RESP,                        /*!< Incorrect result value received after sending Buffer Set message */
	HSM_ERR_INIT_UNINITIALIZE,                          /*!< HSM_DriverInitialize is not performed */
    HSM_ERR_INIT_VERSION_MISMATCH,                      /*!< Driver and HSM version is not compatible */
	
	/* Spinlock Error Code */
	HSM_ERR_SPINLOCK_FAILED_GET_GLOBAL_ID = 0x0B00,     /*!< Failed to acquire Global ID when using Spinlock */
	HSM_ERR_SPINLOCK_FAILED_GET_API_ID = 0x0B01,        /*!< Failed to acquire API ID when using Spinlock */
	HSM_ERR_SPINLOCK_INVALID_SPINLOCK_ID = 0x0B02,      /*!< Incorrect ID input when using Spinlock */
	HSM_ERR_SPINLOCK_HOSTBUFF_NOT_READ_YET = 0x0B03,    /*!< HSM does not read the HOST Buffer */
	HSM_ERR_SPINLOCK_TIMEOUT = 0x0B04,                  /*!< Spinlock acquisition failure for a certain period of time */

	/* Tasklock Error Code */
	HSM_ERR_TASKLOCK_FAILED_GET_TASKLOCK = 0x0C00,      /*!< TaskLock acquisition failed */
	HSM_ERR_TASKLOCK_INVALID_TASK_PRIORITY = 0x0C01,    /*!< When an incorrect task priority is entered */

	/* Buffer Error Code */
	HSM_ERR_READ_BUFFER_INVALID_POINTER = 0x0D00,       /*!< When calling HSM_ReadRxBuff, the address of the result value is null */
	HSM_ERR_SEND_DATA_INVALID = 0x0D01,                 /*!< When entering incorrect data as an API input parameter */
	HSM_ERR_SEND_TIMEOUT = 0x0D02,                      /*!< HSM common buffer resource acquisition waiting time exceeded */
	HSM_ERR_WRITE_BUFFER = 0x0D03,                      /*!< Failed to acquire resources of HSM common buffer */

	/* DFlash Check Error Code */
	HSM_ERR_HSM_USING_DFLASH = 0x0E00,                  /*!< Failed to acquire permission to use HSM data flash */
	HSM_ERR_HSM_USING_DFLASH_TIMEOUT = 0x0E01,          /*!< HSM Data flash permission acquisition waiting time exceeded */

} HSM_ERROR_CODE;

/** Type for callback function */
typedef void (*HSM_CallbackFunc)(void);

#endif /* HSM_TYPE_H_ */
