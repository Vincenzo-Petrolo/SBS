#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtthread.h>
#include "sbs_configuration.h"
#include "process5.h"

int main(void)
{
    printf("hello rt-thread\n");

    DEBUG_PRINT("debug print example\n",LIGHT_DEBUG); //example of usage of macro DEBUG_PRINT

    /*All threads creation*/
    rt_thread_t process5_thread = rt_thread_create("process5",
                                                    process5_entry,
                                                    NULL,
                                                    P5_STACK,
                                                    P5_PRIORITY,
                                                    P5_TSLICE);

    if (process5_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process5 failed to create\n");

        return 1;
    }

    rt_err_t p5_startup_error = rt_thread_startup(process5_thread);

    if (p5_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 5 failed to start\n");

        return 1;
    }


    return 0;
}
