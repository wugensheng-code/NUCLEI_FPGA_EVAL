/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-22     hqfang       first version
 *
 */

#include <rtthread.h>
#include "board.h"
#include "cpuport.h"
#include <unistd.h>
#include <stdio.h>
#include "al_log.h"

#ifdef RT_USING_SERIAL
    #include <rtdevice.h>
    #include <drv_uart.h>
#endif

/** _end symbol defined in linker script of Nuclei SDK */
extern void *_end;

/** _heap_end symbol defined in linker script of Nuclei SDK */
extern void *_heap_end;
#define HEAP_BEGIN  &_end
#define HEAP_END    &_heap_end

/*
 * - Implemented and defined in Nuclei SDK system_<Device>.c file
 * - Required macro NUCLEI_BANNER set to 0
 */

extern void _init(void);
extern void eclic_msip_handler(void);
extern void eclic_mtip_handler(void);
extern int32_t ECLIC_Register_IRQ(IRQn_Type IRQn, uint8_t shv, ECLIC_TRIGGER_Type trig_mode, uint8_t lvl, uint8_t priority, AL_INTR_HandlerStruct* handler);

/**
 * @brief Setup hardware board for rt-thread
 *
 */
void rt_hw_board_init(void)
{
    /* OS Tick Configuration */
    rt_hw_ticksetup();
    // // initialize software interrupt as vector interrupt
    // AlIntr_RegHandler(SysTimerSW_IRQn, AL_NULL, (AL_INTR_Func *)eclic_msip_handler, AL_NULL);

    // // inital timer interrupt as non-vector interrupt
    // AlIntr_RegHandler(SysTimer_IRQn, &SysTimerAttr, (AL_INTR_Func *)eclic_mtip_handler, AL_NULL);

    // initialize software interrupt as vector interrupt
    // ECLIC_Register_IRQ(SysTimerSW_IRQn, ECLIC_VECTOR_INTERRUPT,
    //                                 ECLIC_LEVEL_TRIGGER, 1, 0, eclic_msip_handler);

    // // inital timer interrupt as non-vector interrupt
    // ECLIC_Register_IRQ(SysTimer_IRQn, ECLIC_NON_VECTOR_INTERRUPT,
    //                                 ECLIC_LEVEL_TRIGGER, 1, 0, eclic_mtip_handler);


    // /* set interrupt handler entry to vector table */
    // ECLIC_SetVector(SysTimerSW_IRQn, (rv_csr_t)eclic_msip_handler);
    
    // /* set interrupt handler entry to vector table */
    // ECLIC_SetVector(SysTimer_IRQn, (rv_csr_t)eclic_mtip_handler);

    /* enable interrupt */
    __enable_irq();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *) HEAP_BEGIN, (void *) HEAP_END);
#endif

    _init(); // __libc_init_array is not used in RT-Thread

    /* UART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_uart_init();
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}


extern ssize_t _write(int fd, const void* ptr, size_t len);

void rt_hw_console_output(const char* str)
{
    rt_size_t size = 0;
    char cr = '\r';

    rt_enter_critical();
    
    size = rt_strlen(str);

    AlLog_Write(str, size);

    AlLog_Write(&cr, 1);

    rt_exit_critical();
}
/******************** end of file *******************/

