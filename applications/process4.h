#ifndef __PROCESS4__
#define __PROCESS4__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <time.h>

#define P4_STACK 4096 //4kB
#define P4_PRIORITY 30 //lower than all the other threads
#define P4_TSLICE 10 //TODO verify if this is ok
#define P4_DEADLINE 200 //ms
#define P4_MB_POOL_SIZE 128

static void send_json(uint8_t rpm, uint8_t speed, uint8_t proximity, uint8_t humidity);


/*This process is in charge of creating JSON packages sent through UART
 * connection to the monitor.*/
void process4_entry(void *param)
{
    uint32_t *pointer;
    msg_t *msg;
    uint8_t last_rpm,last_speed,last_hum,last_prox;
    rt_err_t result;

    DEBUG_PRINT("process4 started\n", HEAVY_DEBUG);

    while (1) {
        DEBUG_PRINT("Process 4 is waiting for mail\n", HEAVY_DEBUG);

        result = rt_mb_recv(&p4_mailbox, (rt_ubase_t *)&pointer, 100);

        if (result != RT_EOK) {
            DEBUG_PRINT("Process4 wasn't able to receive mail\n",LIGHT_DEBUG);

            /*Continue with next cycle*/
            continue;
        }

        /*Care must be taken on mailbox messages because they are
         * shared pointer and data can change.*/
        msg = (msg_t *) pointer;

        switch (msg->sensor) {
        case 'V':
            last_speed = msg->value; //copy the value into a local variable
            break;
        case 'R':
            last_rpm = msg->value;
            break;
        case 'H':
            last_hum = msg->value;
            break;
        case 'P':
            last_prox = msg->value;
            break;

        default:
            DEBUG_PRINT("p4 received an unknown sensor",HEAVY_DEBUG);
            break;
        }

        send_json(last_rpm, last_speed, last_prox, last_hum);

    }
    return;
}


static void send_json(uint8_t rpm, uint8_t speed, uint8_t proximity, uint8_t humidity)
{
    /*Send json packets over UART*/
    /*use the uart port over tty to send the JSON values*/
    return;
}

#endif
