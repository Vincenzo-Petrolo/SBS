#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtthread.h>
#include "sbs_configuration.h"
#include "process5.h"
#include "process6.h"
#include "process8.h"

/*Visible to others*/

/*Visible to this file only*/
static uint8_t p8_mb_pool[P8_MB_POOL_SIZE], p6_mb_pool[P6_MB_POOL_SIZE];

int main() {

    rt_err_t result;
    srand(time(NULL));

    result  = rt_mb_init(&p8_mailbox, "p8mb", &p8_mb_pool, P8_MB_POOL_SIZE/4, RT_IPC_FLAG_FIFO);

    if (result != RT_EOK) {
        rt_kprintf("[ERROR] : unable to initialize mailbox P8");

        return 1;
    }

    result  = rt_mb_init(&p6_mailbox, "p6mb", &p6_mb_pool, P6_MB_POOL_SIZE/4, RT_IPC_FLAG_FIFO);

    if (result != RT_EOK) {
        rt_kprintf("[ERROR] : unable to initialize mailbox P6");

        return 1;
    }

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

    rt_thread_t process6_thread = rt_thread_create("process6",
                                                        process6_entry,
                                                        NULL,
                                                        P6_STACK,
                                                        P6_PRIORITY,
                                                        P6_TSLICE);


    if (process6_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process6 failed to create\n");

        return 1;
    }

    rt_thread_t process8_thread = rt_thread_create("process8",
                                                    process8_entry,
                                                    NULL,
                                                    P8_STACK,
                                                    P8_PRIORITY,
                                                    P8_TSLICE);

    if (process8_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process8 failed to create\n");

        return 1;
    }




    rt_err_t p6_startup_error = rt_thread_startup(process6_thread);

    if (p6_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 6 failed to start\n");

        return 1;
    }


    rt_err_t p8_startup_error = rt_thread_startup(process8_thread);

    if (p8_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 8 failed to start\n");

        return 1;
    }

    rt_err_t p5_startup_error = rt_thread_startup(process5_thread);

        if (p5_startup_error == RT_ERROR) {
            rt_kprintf("[ERORR] : process 5 failed to start\n");

            return 1;
        }
    return 0;
}
