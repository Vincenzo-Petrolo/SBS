#ifndef __PROCESS8__
#define __PROCESS8__

#include "sbs_configuration.h"
#include <rtthread.h>

#define P8_STACK 1024 //1kB
#define P8_PRIORITY 1 //highest priority
#define P8_TSLICE 10 //TODO verify if this is ok
#define P8_DEADLINE 10 //ms
#define P8_MB_POOL_SIZE 128

/*Visible to others*/
struct rt_mailbox p8_mailbox;
/*Visible to this file only*/
static uint8_t p8_mb_pool[P8_MB_POOL_SIZE];

void set_brake(uint8_t value);


void process8_entry(void *parameter)
{

    rt_err_t result;
    uint32_t *pointer; //declare a pointer to data received

    result  = rt_mb_init(&p8_mailbox, "p8mb", &p8_mb_pool, P8_MB_POOL_SIZE/4, RT_IPC_FLAG_FIFO);

    if (result != RT_EOK) {
        rt_kprintf("[ERROR] : P8 unable to initialize its mailbox");
    }


    DEBUG_PRINT("process8 started\n", HEAVY_DEBUG);

    while (1) {

        DEBUG_PRINT("Process 8 is waiting for mail\n", HEAVY_DEBUG);

        result = rt_mb_recv(&p8_mailbox, (uint32_t *)&pointer, 100);

        if (result != RT_EOK) {
            DEBUG_PRINT("Process8 wasn't able to receive mail\n",LIGHT_DEBUG);
            DEBUG_PRINT("Braking for safety reasons\n",LIGHT_DEBUG);
            set_brake(255);

            /*Continue with next cycle*/
            continue;
        }


        /*TODO cast the pointer to a defined type in order to access information.*/
        set_brake(*pointer); //TODO remove, it's here just to see if it works

    }

    result = rt_mb_detach(&p8_mailbox);

    if (result != RT_EOK) {
        rt_kprintf("process8 failed to detach its mailbox\n");
    }

    return;
}

void set_brake(uint8_t value) //between 0 and 255
{
    rt_kprintf("[BRAKING] : %d\n",value);
    return;
}

#endif
