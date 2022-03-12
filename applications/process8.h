#ifndef __PROCESS8__
#define __PROCESS8__

#include "sbs_configuration.h"
#include "custom_types.h"

#ifdef SIMBUS
#include "simbus.h"
#endif

#include <rtthread.h>

#define P8_STACK 4096 //1kB
#define P8_PRIORITY 1 //lower than p6
#define P8_TSLICE 100 //TODO verify if this is ok
#define P8_DEADLINE_MS 10 //ms
#define P8_DEADLINE_TICKS RT_TICK_PER_SECOND/1000*P8_DEADLINE_MS
#define P8_MB_POOL_SIZE 128

typedef struct {
    uint8_t humidity_threshold;
    uint8_t critical_proximity_threshold;
    uint8_t proximity_threshold[2];
    uint8_t speed_threshold[2];
    uint8_t rpm_threshdold[2];
} thresholds_t;

void process8_entry()
{

    rt_err_t result;
    uint32_t *pointer; //declare a pointer to data received
    msg_t *msg;
    bus_state_t current_state = {0,0,0,0}; //describe the motion state of the bus
    thresholds_t thresholds[4];
    uint8_t road_state = 0; //assume it is dry
    float brakes = 0;
    uint8_t i = 0;
    float brake_ratio;
#ifdef SIMBUS
    rt_tick_t last_tick,curr_tick;
    /*Initialize bus*/
    bus_init(&simbus);
    last_tick = rt_tick_get();
#endif

#ifdef DEADLINE_TESTING
    /*Initialize deadline*/
    rt_tick_t next_deadline = deadline_init(P8_DEADLINE_TICKS);
    rt_tick_t curr_deadline = 0;
#endif

    thresholds[0].humidity_threshold = 70;
    thresholds[0].proximity_threshold[0] = 36;
    thresholds[0].proximity_threshold[1] = 18;
    thresholds[0].critical_proximity_threshold = 9;

    thresholds[1].humidity_threshold = 70;
    thresholds[1].proximity_threshold[0] = 64;
    thresholds[1].proximity_threshold[1] = 32;
    thresholds[1].critical_proximity_threshold = 16;

    thresholds[2].humidity_threshold = 70;
    thresholds[2].proximity_threshold[0] = 100;
    thresholds[2].proximity_threshold[1] = 50;
    thresholds[2].critical_proximity_threshold = 25;

    thresholds[3].humidity_threshold = 70;
    thresholds[3].proximity_threshold[0] = 144;
    thresholds[3].proximity_threshold[1] = 72;
    thresholds[3].critical_proximity_threshold = 36;

    DEBUG_PRINT("process8 started\n", HEAVY_DEBUG);

    while (1) {

        DEBUG_PRINT("Process 8 is waiting for mail\n", HEAVY_DEBUG);

        result = rt_mb_recv(&p8_mailbox, (rt_ubase_t *)&pointer, ms2ticks(3));

        if (result != RT_EOK) {
            DEBUG_PRINT("Process8 wasn't able to receive mail\n",LIGHT_DEBUG);
            DEBUG_PRINT("Braking for safety reasons\n",LIGHT_DEBUG);
#ifdef SIMBUS
            set_brake(&simbus, brakes);
#endif
            /*Continue with next cycle*/
            continue;
        }

        msg = (msg_t *) pointer;

        switch (msg->sensor) {
            case 'R':
                current_state.rpm = msg->value;
                break;
            case 'V':
                current_state.speed = msg->value;
                break;
            case 'H':
                current_state.humidity = (uint8_t)msg->value;
                break;
            case 'P':
                current_state.proximity = (uint16_t)msg->value;
                break;
            default:
                DEBUG_PRINT("p8 received a value from an unknown sensor\n",LIGHT_DEBUG);
                break;
        }

        if (current_state.humidity > thresholds[0].humidity_threshold) {
            /*road is wet*/
            road_state = 0;
        } else {
            /*road is dry*/
            road_state = 1;
        }

        if (current_state.speed < 20/3.6)
            i = 0;
        else if (current_state.speed < 40/3.6)
            i = 1;
        else if (current_state.speed < 60/3.6)
            i = 2;
        else if (current_state.speed < 80/3.6)
            i = 3;

        if (current_state.speed > 0) {
            if (current_state.proximity <= thresholds[i].critical_proximity_threshold)      //max braking to avoid fatal crashes
                {
                    //3 m/s^2 max
                    brakes = 3.0;
                }

            else if (current_state.proximity < thresholds[i].proximity_threshold[road_state])
            {

                /*brake depending linearly on the proximity and modulated by speed*/
                brake_ratio = ((float)(thresholds[i].proximity_threshold[road_state] - current_state.proximity))/((float)(thresholds[i].proximity_threshold[road_state] - thresholds[i].critical_proximity_threshold));
                brakes = 3*brake_ratio;
            }
            else {
                brakes = 0;
            }
#ifdef SIMBUS
            set_brake(&simbus, brakes);
#endif
        }

        result = rt_mb_send(&p3_mailbox_bis, (rt_uint32_t)&current_state);
#ifdef DEADLINE_TESTING
        /*Online deadline testing*/
        if (check_deadline(next_deadline) == DEADLINE_MISS) {
            rt_kprintf("[!!WARNING!!] Process 8 missed the deadline!\n");
        }

        if (rt_tick_get() > curr_deadline) {
            curr_deadline = next_deadline;
            next_deadline = get_next_deadline(next_deadline, P8_DEADLINE_TICKS);
        }


#endif

#ifdef SIMBUS
        curr_tick = rt_tick_get();
        /*Step the simulation*/
        step_sim(&simbus, (float)ticks2ms((curr_tick-last_tick))/1000);
        last_tick = curr_tick;

        /*Check bus conditions*/
        if (bus_crashed(&simbus) == SIMBUS_CRASHED) {
            rt_kprintf("[EMERGENCY] The bus crashed!!!\n");
        }
        if (bus_is_still(&simbus) == SIMBUS_STILL) {
            rt_kprintf("The bus is still\n");
        }
        printf("Bus speed: %.1f m/s and proximity is %.2f m, braking at %.1f, time %.3f s\n",   get_speed(&simbus),
                                                                                            get_proximity(&simbus),
                                                                                            get_brake(&simbus),
                                                                                            get_time(&simbus));

#endif
    }


}

#endif
