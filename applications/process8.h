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

void set_brake(uint8_t value); //between 0 and 255

typedef struct {
    uint8_t humidity_threshold;
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
    thresholds_t thresholds;
    uint8_t road_state = 0; //assume it is dry
    uint8_t brakes;
#ifdef DEADLINE_TESTING
    /*Initialize deadline*/
    rt_tick_t next_deadline = deadline_init(P8_DEADLINE_TICKS);
    rt_tick_t curr_deadline = 0;
#endif

    thresholds.humidity_threshold = 70;
    thresholds.proximity_threshold[0] = 15;
    thresholds.proximity_threshold[1] = 30;

    DEBUG_PRINT("process8 started\n", HEAVY_DEBUG);

    while (1) {

        DEBUG_PRINT("Process 8 is waiting for mail\n", HEAVY_DEBUG);

        /**Wait for 3ms at most and then make a decision*/
        result = rt_mb_recv(&p8_mailbox, (rt_ubase_t *)&pointer, ms2ticks(3));

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

        if (current_state.proximity < thresholds.proximity_threshold[road_state]) {
            /*Check if the bus is in motion*/
            if (current_state.speed > 0 && current_state.rpm > 0) {
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

void set_brake(uint8_t value) //between 0 and 255
{
    //rt_kprintf("[BRAKING] : %d\n",value);
    return;
}

#endif
