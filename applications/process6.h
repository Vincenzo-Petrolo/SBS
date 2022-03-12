#ifndef __PROCESS6__
#define __PROCESS6__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>

#ifdef SIMBUS
#include "simbus.h"
#endif

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
    uint8_t update_prio6;
    uint8_t update_prio8;

#ifdef DEADLINE_TESTING
    /*Initialize deadline*/
    rt_tick_t next_deadline = deadline_init(P6_DEADLINE_TICKS);
    rt_tick_t curr_deadline = 0;
#endif

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

            if (current_speed > 10/3.6 && current_rpm == 0 && ABS_state == 0) {
                update_prio6 = 1;
                update_prio8 = 2;
                rt_thread_control(rt_thread_self(), RT_THREAD_CTRL_CHANGE_PRIORITY, &update_prio6);
                rt_thread_control(process8_thread, RT_THREAD_CTRL_CHANGE_PRIORITY, &update_prio8);
                ABS_state = 1;
                rt_kprintf("[ABS ACTIVE]\n");
                set_brake(&simbus, get_brake(&simbus)/2);
                printf("Bus speed: %.1f m/s and proximity is %.2f m, braking at %.1f, time %.3f s\n",   get_speed(&simbus),
                                                                                                    get_proximity(&simbus),
                                                                                                    get_brake(&simbus),
                                                                                                    get_time(&simbus));
            }
            else if (ABS_state == 1){
                update_prio6 = 2;
                update_prio8 = 1;
                rt_thread_control(process8_thread, RT_THREAD_CTRL_CHANGE_PRIORITY, &update_prio8);
                rt_thread_control(rt_thread_self(), RT_THREAD_CTRL_CHANGE_PRIORITY, &update_prio6);
                ABS_state = 0;
                rt_kprintf("[ABS INACTIVE]\n");
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
