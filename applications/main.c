#include <rtthread.h>
#include <stdio.h>

#define THREAD_STACK_SIZE   1024
#define THREAD_PRIORITY     20
#define THREAD_TIMESLICE    10

/* 针对每个线程的计数器 */
volatile rt_uint32_t count[2];

/* 线程 1、2 共用一个入口，但入口参数不同 */
static void thread_entry(void* parameter)
{
    rt_uint32_t value;

    value = (rt_uint32_t)parameter;
    while (1)
    {
        rt_kprintf("thread %d is running\n", value);
        rt_thread_mdelay(500); // 延时一段时间
    }
}

static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;

static void hook_of_scheduler(struct rt_thread* from, struct rt_thread* to)
{
    rt_kprintf("from: %s -->  to: %s \n", from->name , to->name);
}

int scheduler_hook(void)
{
    /* 设置调度器钩子 */
    rt_scheduler_sethook(hook_of_scheduler);

    /* 创建线程 1 */
    tid1 = rt_thread_create("thread1",
                            thread_entry, (void*)1,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    /* 创建线程 2 */
    tid2 = rt_thread_create("thread2",
                            thread_entry, (void*)2,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY,THREAD_TIMESLICE - 5);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);
    return 0;
}

/* 导出到 msh 命令列表中 */
// MSH_CMD_EXPORT(scheduler_hook, scheduler_hook sample);

int main(void)
{
    printf("RT-Thread\n");
    scheduler_hook();
    printf("hello\n");
    while (1)
    {
        // rt_kprintf("main thread is running\n");
        rt_thread_mdelay(500); // 延时一段时间
    }
}