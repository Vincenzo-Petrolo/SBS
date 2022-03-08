#ifndef __PROCESS8__
#define __PROCESS8__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>

#define P8_STACK 4096 //1kB
#define P8_PRIORITY 1 //lower than p6
#define P8_TSLICE 100 //TODO verify if this is ok
#define P8_DEADLINE_MS 10 //ms
#define P8_DEADLINE_TICKS RT_TICK_PER_SECOND/1000*P8_DEADLINE_MS
#define P8_MB_POOL_SIZE 128

void set_brake(uint8_t value); //between 0 and 10 m/s^2

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
    thresholds_t thresholds[7];
    uint8_t road_state = 0; //assume it is dry
    uint8_t brakes;
    uint8_t i;
#ifdef DEADLINE_TESTING
    /*Initialize deadline*/
    rt_tick_t next_deadline = deadline_init(P8_DEADLINE_TICKS);
    rt_tick_t curr_deadline = 0;
#endif

    thresholds[0].humidity_threshold = 70;
    thresholds[0].proximity_threshold[0] = 4;
    thresholds[0].proximity_threshold[1] = 2;
    thresholds[0].critical_proximity_threshold = 1;

    thresholds[1].humidity_threshold = 70;
    thresholds[1].proximity_threshold[0] = 16;
    thresholds[1].proximity_threshold[1] = 8;
    thresholds[1].critical_proximity_threshold = 4;

    thresholds[2].humidity_threshold = 70;
    thresholds[2].proximity_threshold[0] = 36;
    thresholds[2].proximity_threshold[1] = 18;
    thresholds[2].critical_proximity_threshold = 9;

    thresholds[3].humidity_threshold = 70;
    thresholds[3].proximity_threshold[0] = 64;
    thresholds[3].proximity_threshold[1] = 32;
    thresholds[3].critical_proximity_threshold = 16;

    thresholds[4].humidity_threshold = 70;
    thresholds[4].proximity_threshold[0] = 100;
    thresholds[4].proximity_threshold[1] = 50;
    thresholds[4].critical_proximity_threshold = 25;

    thresholds[5].humidity_threshold = 70;
    thresholds[5].proximity_threshold[0] = 144;
    thresholds[5].proximity_threshold[1] = 72;
    thresholds[5].critical_proximity_threshold = 36;

    thresholds[6].humidity_threshold = 70;
    thresholds[6].proximity_threshold[0] = 196;
    thresholds[6].proximity_threshold[1] = 98;
    thresholds[6].critical_proximity_threshold = 49;

    DEBUG_PRINT("process8 started\n", HEAVY_DEBUG);

    while (1) {

        DEBUG_PRINT("Process 8 is waiting for mail\n", HEAVY_DEBUG);

        /**Wait for 3ms at most and then make a decision*/
        result = rt_mb_recv(&p8_mailbox, (rt_ubase_t *)&pointer, RT_WAITING_FOREVER);

        if (result != RT_EOK) {
            DEBUG_PRINT("Process8 wasn't able to receive mail\n",LIGHT_DEBUG);
            DEBUG_PRINT("Braking for safety reasons\n",LIGHT_DEBUG);
            set_brake(255);

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
                current_state.humidity = msg->value;
                break;
            case 'P':
                current_state.proximity = msg->value;
                break;
            default:
                DEBUG_PRINT("p8 received a value from an unknown sensor\n",LIGHT_DEBUG);
                break;
        }

        //TODO this can be avoided if we haven't updated the humidity value this cycle
        if (current_state.humidity > thresholds.humidity_threshold) {
            /*road is dry*/
            road_state = 0;
        } else {
            /*road is wet*/
            road_state = 1;
        }

        if (current_state.speed < 20)
            i = 0;
        else if (current_state.speed < 40)
            i = 1;
        else if (current_state.speed < 60)
            i = 2;
        else if (current_state.speed < 80)
            i = 3;
        else if (current_state.speed < 100)
            i = 4;
        else if (current_state.speed < 120)
            i = 5;
        else
            i = 6;

        if (current_state.speed > 0 && current_state.rpm > 0) {
            if (current_state.proximity <= thresholds[i].critical_proximity_threshold)      //max braking to avoid fatal crashes
                        {
                            //10 m/s^2 max
                            brakes = 10;
                        }

            else if (current_state.proximity < thresholds[i].proximity_threshold[road_state]) {

                /*brake depending linearly on the proximity and modulated by speed*/
                brakes = (255-current_state.proximity)*((float)current_state.speed/255);
                set_brake(brakes);
                }

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
    }


}

void set_brake(uint8_t value) //between 0 and 10 m/s^2
{

    //rt_kprintf("[BRAKING] : %d\n",value);
    return;
}

#endif
