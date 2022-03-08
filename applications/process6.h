#ifndef __PROCESS6__
#define __PROCESS6__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>

#define P6_STACK 4096 //4kB
#define P6_PRIORITY 2 //highest priority
#define P6_TSLICE 10
#define P6_DEADLINE_MS 15 //ms
#define P6_DEADLINE_TICKS RT_TICK_PER_SECOND/1000*P6_DEADLINE_MS
#define P6_MB_POOL_SIZE 128

void process6_entry()
{

    rt_err_t result;
    uint32_t *pointer; //declare a pointer to data received
    msg_t *msg;
    uint8_t current_rpm = 0;
    uint8_t current_speed = 0;
    uint8_t ABS_state = 0;
#ifdef DEADLINE_TESTING
    /*Initialize deadline*/
    rt_tick_t next_deadline = deadline_init(P6_DEADLINE_TICKS);
    rt_tick_t curr_deadline = 0;
#endif

    DEBUG_PRINT("process6 started\n", HEAVY_DEBUG);

        while (1) {

            DEBUG_PRINT("Process 6 is waiting for mail\n", HEAVY_DEBUG);

            /*Limit the wait time to 5ms at most, then if no data has arrived
             * make a decision*/
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
                //rt_kprintf("[ABS ACTIVE]\n");
            }
            else {
                ABS_state = 0;
            }

#ifdef DEADLINE_TESTING
        /*Online deadline testing*/
        if (check_deadline(next_deadline) == DEADLINE_MISS) {
            rt_kprintf("[!!WARNING!!] Process 6 missed the deadline!\n");
        }

        if (rt_tick_get() > curr_deadline) {
            curr_deadline = next_deadline;
            next_deadline = get_next_deadline(next_deadline, P6_DEADLINE_TICKS);
        }

#endif
        }
}

#endif
