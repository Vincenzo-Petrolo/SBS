#ifndef __PROCESS2__
#define __PROCESS2__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <tiny_aes.h>


#define P2_STACK 4096 //4kB
#define P2_PRIORITY 6 //lower than firm and hard
#define P2_TSLICE 10
#define P2_DEADLINE_MS 25
#define P2_DEADLINE_TICKS RT_TICK_PER_SECOND/1000*P2_DEADLINE_MS
#define P2_MB_POOL_SIZE 128

void transmit_data(unsigned char *encrypted_value);

void process2_entry()
{
    uint32_t *pointer;
    rt_err_t result;
#ifdef DEADLINE_TESTING
    /*Initialize deadline*/
    rt_tick_t next_deadline = deadline_init(P2_DEADLINE_TICKS);
    rt_tick_t curr_deadline = 0;
#endif

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
#ifdef DEADLINE_TESTING
        /*Online deadline testing*/
        if (check_deadline(next_deadline) == DEADLINE_MISS) {
            rt_kprintf("[!!WARNING!!] Process 2 missed the deadline!\n");
        }

        if (rt_tick_get() > curr_deadline) {
            curr_deadline = next_deadline;
            next_deadline = get_next_deadline(next_deadline, P2_DEADLINE_TICKS);
        }
#endif
}

void transmit_data(unsigned char *encrypted_value)
{
    return;
}
#endif
