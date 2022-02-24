#ifndef __PROCESS7__
#define __PROCESS7__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>

#define P7_STACK 4096 //1kB
#define P7_PRIORITY 3 //highest priority
#define P7_TSLICE 10 //TODO verify if this is ok
#define P7_DEADLINE 15 //ms
#define P7_MB_POOL_SIZE 128

static void can_send_msg(msg_t *msg);
static msg_t can_receive_msg(void);

void process7_entry()
{

    rt_err_t result;
    uint32_t *pointer; //declare a pointer to data received
    msg_t *msg;
    msg_t rec;

    DEBUG_PRINT("process7 started\n", HEAVY_DEBUG);


    while (1) {

        DEBUG_PRINT("Process 6 is waiting for mail\n", HEAVY_DEBUG);

        result = rt_mb_recv(&p7_mailbox, (rt_ubase_t *)&pointer, RT_WAITING_FOREVER);

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
        /*Spread to other processes depending on the type of information*/
        /*TOOD decide what kind of data we can receive from the system*/
    }
}

static void can_send_msg(msg_t *msg)
{

    /*More on CAN*/

    return;
}

static msg_t can_receive_msg(void)
{
    /*Emulate receive from CAN*/
    msg_t received_msg;

    rt_thread_delay(500);

    return received_msg;
}

#endif
