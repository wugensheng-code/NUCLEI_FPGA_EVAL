#include <rtthread.h>












int backtrace_init(void) {
    static rt_bool_t is_init = RT_FALSE;

    if (is_init)
    {
        return 0;
    }

    cm_backtrace_init("rtthread","1.0","1.0");
    
    rt_hw_exception_install(exception_hook);

    rt_assert_set_hook(assert_hook);
    
    is_init = RT_TRUE;
    return 0;
}
INIT_DEVICE_EXPORT(rt_cm_backtrace_init);