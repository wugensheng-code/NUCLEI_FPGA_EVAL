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
/**
 * @brief Setup hardware board for rt-thread
 *
 */
void rt_hw_board_init(void)
{
    /* OS Tick Configuration */
    rt_hw_ticksetup();

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
    // rt_size_t size = 0;
    // rt_int32_t ret = RT_EOK;
    // char cr = '\r';

    // rt_enter_critical();
    
    // size = rt_strlen(str);

    // ret = AlLog_Write(str, size);
    // if(ret != RT_EOK)
    // {
    //     while (1)
    //     {
    //         /* code */
    //     }
        
    // }

    // ret = AlLog_Write(&cr, 1);
    // if(ret != RT_EOK)
    // {
    //     while (1)
    //     {
    //         /* code */
    //     }
                
    // }
    
    // rt_exit_critical();
}
/******************** end of file *******************/

