#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtthread.h>
#include "sbs_configuration.h"
#include "process8.h"

int main(void)
{
    printf("hello rt-thread\n");

    DEBUG_PRINT("debug print example\n",LIGHT_DEBUG); //example of usage of macro DEBUG_PRINT

    /*All threads creation*/
    rt_thread_t process8_thread = rt_thread_create("process8",
                                                    process8_entry,
                                                    NULL,
                                                    P8_STACK,
                                                    P8_PRIORITY,
                                                    P8_TSLICE);

    if (process8_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process8 failed to create\n");
    }

    rt_err_t p8_startup_error = rt_thread_startup(process8_thread);

    if (p8_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 8 failed to start\n");
    }

    return 0;
}
