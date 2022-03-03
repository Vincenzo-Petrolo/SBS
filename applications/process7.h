#ifndef __PROCESS7__
#define __PROCESS7__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>

#define P7_STACK 4096 //1kB
#define P7_PRIORITY 3 //highest priority
#define P7_TSLICE 10 //TODO verify if this is ok
#define P7_DEADLINE_MS 15 //ms
#define P7_DEADLINE_TICKS RT_TICK_PER_SECOND/1000*P7_DEADLINE_MS
#define P7_MB_POOL_SIZE 128

static void can_send_msg(msg_t *msg);
static msg_t can_receive_msg(void);

void process7_entry()
{

    rt_err_t result;
    uint32_t *pointer; //declare a pointer to data received
    msg_t *msg;
    msg_t rec;
#ifdef DEADLINE_TESTING
    /*Initialize deadline*/
    rt_tick_t next_deadline = deadline_init(P7_DEADLINE_TICKS);
#endif

    DEBUG_PRINT("process7 started\n", HEAVY_DEBUG);


    while (1) {
        DEBUG_PRINT("Process 7 is waiting for mail\n", HEAVY_DEBUG);

        result = rt_mb_recv(&p7_mailbox, (rt_ubase_t *)&pointer, 1000);

        if (result != RT_EOK) {
            DEBUG_PRINT("Process7 wasn't able to receive mail\n",LIGHT_DEBUG);

            /*Continue with next cycle*/
            continue;
        } else {
            /*After receiving a message from a sensor, send it over can to the network*/
            msg = (msg_t *) pointer;
            can_send_msg(msg);
        }

        /*Receive informations over CAN from system*/
        rec = can_receive_msg();
        /*Forward the received values to process 6 and process 8*/
        rt_mb_send(&p6_mailbox, (rt_uint32_t)&rec);
        rt_mb_send(&p8_mailbox, (rt_uint32_t)&rec);
#ifdef DEADLINE_TESTING
        /*Online deadline testing*/
        if (check_deadline(next_deadline) == DEADLINE_MISS) {
            rt_kprintf("[!!WARNING!!] Process 7 missed the deadline!\n");
        }

        next_deadline = get_next_deadline(next_deadline, P7_DEADLINE_TICKS);
#endif
    }
}

static void can_send_msg(msg_t *msg)
{

    /*Emulate sending over CAN*/
    DEBUG_PRINT("Sending over CAN network\n", HEAVY_DEBUG);
    return;
}

static msg_t can_receive_msg(void)
{
    /*Emulate receive from CAN*/
    /*Initialize to tyre pressure*/
    static char sensor_name = 'T';
    msg_t received_msg;

    received_msg.sensor = sensor_name;
    /*Randomize the value*/
    received_msg.value = ((rand()%rt_tick_get()) & 0xFF00000) >> 20;

    if (sensor_name == 'T') {
        sensor_name = 'W';
    } else if (sensor_name == 'W') {
        sensor_name = 'O';
    } else {
        sensor_name = 'T';
    }

    //rt_thread_delay(500);

    DEBUG_PRINT("Received from CAN network\n", HEAVY_DEBUG);

    return received_msg;
}

#endif
