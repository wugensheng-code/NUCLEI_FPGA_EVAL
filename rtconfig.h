#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_HOOK_USING_FUNC_PTR
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 2048

/* kservice optimization */

#define RT_DEBUG

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_SMALL_MEM
#define RT_USING_SMALL_MEM_AS_HEAP
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart"
#define RT_VER_NUM 0x40101
#define ARCH_RISCV

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 4096
#define RT_MAIN_THREAD_PRIORITY 30

/* Device Drivers */

#define RT_USING_DEVICE_IPC

/* Using USB */


/* C/C++ and POSIX layer */

#define RT_LIBC_DEFAULT_TIMEZONE 8

/* POSIX (Portable Operating System Interface) layer */


/* Interprocess Communication (IPC) */


/* Socket is in the 'Network' category */


/* Network */


/* Utilities */

#define RT_USING_ULOG
#define ULOG_OUTPUT_LVL_D
#define ULOG_OUTPUT_LVL 7
#define ULOG_USING_ISR_LOG
#define ULOG_ASSERT_ENABLE
#define ULOG_LINE_BUF_SIZE 128
#define ULOG_USING_ASYNC_OUTPUT
#define ULOG_ASYNC_OUTPUT_BUF_SIZE 2048
#define ULOG_ASYNC_OUTPUT_BY_THREAD
#define ULOG_ASYNC_OUTPUT_THREAD_STACK 1024
#define ULOG_ASYNC_OUTPUT_THREAD_PRIORITY 30

/* log format */

#define ULOG_USING_COLOR
#define ULOG_OUTPUT_TIME
#define ULOG_TIME_USING_TIMESTAMP
#define ULOG_OUTPUT_LEVEL
#define ULOG_OUTPUT_TAG
#define ULOG_OUTPUT_THREAD_NAME
#define ULOG_BACKEND_USING_CONSOLE

/* RT-Thread online packages */

/* IoT - internet of things */


/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */


/* IoT Cloud */


/* security packages */


/* language packages */

/* JSON: JavaScript Object Notation, a lightweight data-interchange format */


/* XML: Extensible Markup Language */


/* multimedia packages */

/* LVGL: powerful and easy-to-use embedded GUI library */


/* u8g2: a monochrome graphic library */


/* tools packages */


/* system packages */

/* enhanced kernel services */


/* acceleration: Assembly language or algorithmic acceleration packages */


/* CMSIS: ARM Cortex-M Microcontroller Software Interface Standard */


/* Micrium: Micrium software products porting for RT-Thread */


/* peripheral libraries and drivers */

/* sensors drivers */


/* touch drivers */


/* Kendryte SDK */

#define PKG_USING_NUCLEI_SDK

/* !!!Nuclei SDK only works with Nuclei RISC-V Processor IP!!! */

#define PKG_USING_NUCLEI_SDK_LATEST_VERSION

/* AI packages */


/* Signal Processing and Control Algorithm Packages */


/* miscellaneous packages */

/* project laboratory */

/* samples: kernel and components samples */


/* entertainment: terminal games and other interesting software packages */


/* Arduino libraries */


/* Projects */


/* Sensors */


/* Display */


/* Timing */


/* Data Processing */


/* Data Storage */

/* Communication */


/* Device Control */


/* Other */


/* Signal IO */


/* Uncategorized */

/* Hardware Drivers Config */

#define SOC_HUMMINGBIRD

/* Onboard Peripheral Drivers */


/* On-chip Peripheral Drivers */


/* Board extended module Drivers */

#define SOC_DEMOSOC

#endif
