#ifndef __PROCESS8__
#define __PROCESS8__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>

#define P8_STACK 1024 //1kB
#define P8_PRIORITY 1 //highest priority
#define P8_TSLICE 10 //TODO verify if this is ok
#define P8_DEADLINE 10 //ms
#define P8_MB_POOL_SIZE 128



void set_brake(uint8_t value); //between 0 and 255


void process8_entry(void *p8_mailboxp)
{

    rt_err_t result;
    uint32_t *pointer; //declare a pointer to data received
    msg_t *msg;

    DEBUG_PRINT("process8 started\n", HEAVY_DEBUG);

    while (1) {

        DEBUG_PRINT("Process 8 is waiting for mail\n", HEAVY_DEBUG);

        result = rt_mb_recv(p8_mailboxp, (rt_ubase_t *)&pointer, 100);

        if (result != RT_EOK) {
            DEBUG_PRINT("Process8 wasn't able to receive mail\n",LIGHT_DEBUG);
            DEBUG_PRINT("Braking for safety reasons\n",LIGHT_DEBUG);
            set_brake(255);

            /*Continue with next cycle*/
            continue;
        }

        msg = (msg_t *) pointer;

        if (msg -> sensor == 'V') {
            set_brake((uint8_t) msg -> value);

        }
    }


}

void set_brake(uint8_t value) //between 0 and 255
{
    rt_kprintf("[BRAKING] : %d\n",value);
    return;
}

#endif
