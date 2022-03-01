#ifndef __PROCESS2__
#define __PROCESS2__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <tiny_aes.h>


#define P2_STACK 2048 //1kB
#define P2_PRIORITY 6 //lower than firm and hard
#define P2_TSLICE 10
#define P2_DEADLINE 25 //ms
#define P2_MB_POOL_SIZE 128

void transmit_data(unsigned char *encrypted_value);

void process2_entry()
{
    uint32_t *pointer;
    rt_err_t result;


    while (1) {

        DEBUG_PRINT("Process 2 is waiting for mail\n", HEAVY_DEBUG);

        result = rt_mb_recv(&p2_mailbox, (rt_ubase_t *)&pointer, RT_WAITING_FOREVER);

        if (result != RT_EOK) {
            DEBUG_PRINT("Process2 wasn't able to receive mail\n",LIGHT_DEBUG);
            /*Continue with next cycle*/
            continue;
        }
        /*Send data over the network*/
        transmit_data((unsigned char *) pointer);

    }
}

void transmit_data(unsigned char *encrypted_value)
{
    //rt_thread_delay(100);

    return;
}
#endif
