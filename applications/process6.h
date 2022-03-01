#ifndef __PROCESS6__
#define __PROCESS6__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>

#define P6_STACK 2048 //1kB
#define P6_PRIORITY 1 //highest priority
#define P6_TSLICE 10 //TODO verify if this is ok
#define P6_DEADLINE 15 //ms
#define P6_MB_POOL_SIZE 128


void process6_entry()
{

    rt_err_t result;
    uint32_t *pointer; //declare a pointer to data received
    msg_t *msg;
    uint8_t current_rpm = 0;
    uint8_t current_speed = 0;
    uint8_t ABS_state = 0;

    DEBUG_PRINT("process6 started\n", HEAVY_DEBUG);

        while (1) {

            DEBUG_PRINT("Process 6 is waiting for mail\n", HEAVY_DEBUG);

            result = rt_mb_recv(&p6_mailbox, (rt_ubase_t *)&pointer, RT_WAITING_FOREVER);

            if (result != RT_EOK) {
                DEBUG_PRINT("Process6 wasn't able to receive mail\n",LIGHT_DEBUG);
                /*Continue with next cycle*/
                continue;
            }

            msg = (msg_t *) pointer;

            switch (msg->sensor) {
                case 'R':
                    current_rpm = msg->value;
                    break;
                case 'V':
                    current_speed = msg->value;
                    break;
                default:
                    DEBUG_PRINT("p6 received a value from an unknown sensor\n",LIGHT_DEBUG);
                    break;
            }

            if (current_speed > 10 && current_rpm == 0) {
                ABS_state = 1;
                rt_kprintf("[ABS ACTIVE]\n");
            }
            else {
                ABS_state = 0;
            }
        }
}

#endif
