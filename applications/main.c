#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtthread.h>
#include "sbs_configuration.h"
#include "process5.h"
#include "process8.h"

/*Visible to others*/
struct rt_mailbox p8_mailbox;
/*Visible to this file only*/
static uint8_t p8_mb_pool[P8_MB_POOL_SIZE];

int main() {

    rt_err_t result;

    srand(time(NULL));

    result  = rt_mb_init(&p8_mailbox, "p8mb", &p8_mb_pool, P8_MB_POOL_SIZE/4, RT_IPC_FLAG_FIFO);

    if (result != RT_EOK) {
        rt_kprintf("[ERROR] : unable to initialize mailbox P8");
    }

    /*All threads creation*/
    rt_thread_t process5_thread = rt_thread_create("process5",
                                                    process5_entry,
                                                    &p8_mailbox,
                                                    P5_STACK,
                                                    P5_PRIORITY,
                                                    P5_TSLICE);


    if (process5_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process5 failed to create\n");

        return 1;
    }

    rt_thread_t process8_thread = rt_thread_create("process8",
                                                    process8_entry,
                                                    &p8_mailbox,
                                                    P8_STACK,
                                                    P8_PRIORITY,
                                                    P8_TSLICE);

    if (process8_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process8 failed to create\n");

        return 1;
    }


    rt_err_t p8_startup_error = rt_thread_startup(process8_thread);

    if (p8_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 8 failed to start\n");

        return 1;
    }

    printf("hello rt-thread\n");

    rt_err_t p5_startup_error = rt_thread_startup(process5_thread);

    if (p5_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 5 failed to start\n");

        return 1;
    }





    return 0;
}

void process8(void *parameter)
{



    return;
}
