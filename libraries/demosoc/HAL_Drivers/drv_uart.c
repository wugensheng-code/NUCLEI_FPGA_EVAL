/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-22     hqfang       First version
 */

#include <drv_uart.h>

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be enabled at menuconfig -> 
    Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable UART */
#endif

enum
{
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
};

extern AL_UART_HwConfigStruct AlUart_HwConfig[AL_UART_NUM_INSTANCE];

static AL_UART_DevStruct AL_UART_DevInstance[AL_UART_NUM_INSTANCE];

static struct al9000_uart uart_obj[AL_UART_NUM_INSTANCE] = {0};

static rt_err_t al9000_configure(struct rt_serial_device *serial,
                               struct serial_configure *cfg)
{
    // struct al9000_uart *uart_obj;
    // struct al9000_uart_config *uart_cfg;
    // RT_ASSERT(serial != RT_NULL);
    // RT_ASSERT(cfg != RT_NULL);

    // uart_obj = (struct hbird_uart *) serial->parent.user_data;
    // uart_cfg = uart_obj->config;
    // RT_ASSERT(uart_cfg != RT_NULL);

    // uart_init(uart_cfg->uart, cfg->baud_rate);

    // switch (cfg->stop_bits)
    // {
    // case STOP_BITS_1:
    //     // uart_config_stopbit(uart_cfg->uart, UART_STOP_BIT_1);
    //     break;
    // case STOP_BITS_2:
    //     // uart_config_stopbit(uart_cfg->uart, UART_STOP_BIT_2);
    //     break;
    // default:
    //     // uart_config_stopbit(uart_cfg->uart, UART_STOP_BIT_1);
    //     break;
    // }

    return RT_EOK;
}

static rt_err_t al9000_control(struct rt_serial_device *serial, int cmd,
                             void *arg)
{
    struct al9000_uart *uart_obj;
    struct al9000_uart_config *uart_cfg;

    RT_ASSERT(serial != RT_NULL);
    uart_obj = (struct hbird_uart *) serial->parent.user_data;
    uart_cfg = uart_obj->config;
    RT_ASSERT(uart_cfg != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        // ECLIC_DisableIRQ(uart_cfg->irqn);
        // uart_disable_rxint(uart_cfg->uart);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        // ECLIC_EnableIRQ(uart_cfg->irqn);
        // ECLIC_SetShvIRQ(uart_cfg->irqn, ECLIC_NON_VECTOR_INTERRUPT);
        // ECLIC_SetLevelIRQ(uart_cfg->irqn, 1);
        // uart_enable_rxint(uart_cfg->uart);
        break;
    }

    return RT_EOK;
}

static int al9000_putc(struct rt_serial_device *serial, char ch)
{
    struct al9000_uart *uart_obj;
    struct al9000_uart_config *uart_cfg;
    AL_S32 Ret = AL_OK;

    RT_ASSERT(serial != RT_NULL);
    uart_obj = (struct al9000_uart *) serial->parent.user_data;
    uart_cfg = uart_obj->config;
    RT_ASSERT(uart_cfg != RT_NULL);

    Ret = AlUart_Dev_SendDataPolling(uart_cfg->uart, (AL_U8 *)&ch, 1);
    if (Ret != AL_OK) {
        return Ret;
    }

    return 1;
}

static int al9000_getc(struct rt_serial_device *serial)
{
    int ch;
    uint32_t rxfifo;
    struct al9000_uart *uart_obj;
    struct al9000_uart_config *uart_cfg;
    AL_S32 Ret = AL_OK;

    RT_ASSERT(serial != RT_NULL);
    uart_obj = (struct hbird_uart *) serial->parent.user_data;
    uart_cfg = uart_obj->config;
    RT_ASSERT(uart_cfg != RT_NULL);

    ch = -1;
    Ret = AlUart_Dev_RecvData(uart_cfg->uart, &ch, 1);
    if (Ret != AL_OK) {
        return Ret;
    }
    return ch;

}

static const struct rt_uart_ops al9000_uart_ops = { al9000_configure, al9000_control,
           al9000_putc, al9000_getc,
           RT_NULL
};

// static void gd32_uart_isr(struct rt_serial_device *serial)
// {
//     struct hbird_uart *uart_obj;
//     struct hbird_uart_config *uart_cfg;

//     RT_ASSERT(serial != RT_NULL);
//     uart_obj = (struct hbird_uart *) serial->parent.user_data;
//     uart_cfg = uart_obj->config;
//     RT_ASSERT(uart_cfg != RT_NULL);

//     if (uart_cfg->uart->IP & UART_IP_RXIP_MASK) {
//         rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
//     }
// }

// #ifdef BSP_USING_UART0

// // void eclic_irq19_handler(void)
// // {
// //     rt_interrupt_enter();

// //     gd32_uart_isr(&uart_obj[UART0_INDEX].serial);

// //     rt_interrupt_leave();
// // }

// #endif

// #ifdef BSP_USING_UART1

// void eclic_irq20_handler(void)
// {
//     rt_interrupt_enter();

//     gd32_uart_isr(&uart_obj[UART1_INDEX].serial);

//     rt_interrupt_leave();
// }

// #endif

/* For Nuclei demosoc Uart, when CPU freq is lower than 8M
   The uart read will only work on baudrate <= 57600.
   Nowadays, we usually distribute FPGA bitsteam with CPU Freq 16MHz */
#define DRV_UART_BAUDRATE       BAUD_RATE_115200


static AL_VOID AlUart_Hal_EventHandler(AL_UART_EventStruct UartEvent, AL_VOID *CallbackRef)
{

}

int rt_hw_uart_init(void)
{
    AL_UART_InitStruct UART_InitStruct = {
        .BaudRate     = 115200,
        .Parity       = UART_NO_PARITY,
        .WordLength   = UART_CHAR_8BITS,
        .StopBits     = UART_STOP_1BIT,
    };

    AL_U32 DevId = UART0_INDEX;
    AL_S32 Ret;
    AL_UART_DevStruct *Dev;
    AL_UART_HwConfigStruct *HwConfig;
    rt_size_t obj_num;
    int index;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    obj_num = sizeof(uart_obj) / sizeof(struct al9000_uart);
    config.baud_rate = DRV_UART_BAUDRATE;


    HwConfig = AlUart_Dev_LookupConfig(DevId);
    if (HwConfig != AL_NULL) {
        Dev = &AL_UART_DevInstance[DevId];
    } else {
        return AL_UART_ERR_ILLEGAL_PARAM;
    }

    Ret = AlUart_Dev_Init(Dev, &UART_InitStruct, DevId);
    if (Ret != AL_OK) {
        return Ret;
    }

    Ret = AlUart_Dev_RegisterEventCallBack(Dev, AlUart_Hal_EventHandler, AL_NULL);
    if (Ret != AL_OK) {
        return Ret;
    }

    (AL_VOID)AlIntr_RegHandler(Dev->IrqNum, AL_NULL, AlUart_Dev_IntrHandler, Dev);
    __enable_irq();

    for (index = 0; index < obj_num; index++)
    {
        /* init UART object */
        uart_obj[index].config = &AlUart_HwConfig[index];
        uart_obj[index].serial.ops = &al9000_uart_ops;
        uart_obj[index].serial.config = config;

        /* register UART device */
        Ret = rt_hw_serial_register(&uart_obj[index].serial,
                                       uart_obj[index].config->name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                       &uart_obj[index]);

        (AL_VOID)AlIntr_RegHandler(Dev->IrqNum, AL_NULL, AlUart_Dev_IntrHandler, Dev);

        RT_ASSERT(Ret == RT_EOK);
    }

    return Ret;
}

// void rt_hw_serial_rcvtsk(void *parameter)
// {
//     struct hbird_uart_config *uart_cfg;

//     while (1) {
// #ifdef BSP_USING_UART0
//     uart_cfg = uart_obj[UART0_INDEX].config;
//     if (uart_cfg->uart->IP & UART_IP_RXIP_MASK) {
//         gd32_uart_isr(&uart_obj[UART0_INDEX].serial);
//     }
// #endif
// #ifdef BSP_USING_UART1
//     uart_cfg = uart_obj[UART1_INDEX].config;
//     if (uart_cfg->uart->IP & UART_IP_RXIP_MASK) {
//         gd32_uart_isr(&uart_obj[UART1_INDEX].serial);
//     }
// #endif
//         rt_thread_mdelay(50);
//     }
// }

#endif /* RT_USING_SERIAL */

/******************** end of file *******************/
