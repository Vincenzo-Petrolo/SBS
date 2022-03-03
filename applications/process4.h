#ifndef __PROCESS4__
#define __PROCESS4__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <time.h>

#define P4_STACK 4096 //4kB
#define P4_PRIORITY 6
#define P4_TSLICE 1
#define P4_DEADLINE_MS 200 //ms
#define P4_DEADLINE_TICKS RT_TICK_PER_SECOND/1000*P4_DEADLINE_MS
#define P4_MB_POOL_SIZE 128

static void send_json(uint8_t rpm, uint8_t speed, uint8_t proximity, uint8_t humidity);

/*To be used only by this process*/
/*Use the other uart peripheral of the board, to send data*/
#define DEVICE_NAME "uart1"
static rt_device_t serial_monitor;

/*This process is in charge of creating JSON packages sent through UART
 * connection to the monitor.*/
void process4_entry(void *param)
{
    uint32_t *pointer;
    msg_t *msg;
    uint8_t last_rpm,last_speed,last_hum,last_prox;
    rt_err_t result;
#ifdef DEADLINE_TESTING
    /*Initialize deadline*/
    rt_tick_t next_deadline = deadline_init(P4_DEADLINE_TICKS);
#endif
    DEBUG_PRINT("process4 started\n", HEAVY_DEBUG);
    serial_monitor = rt_device_find(DEVICE_NAME);

    if (serial_monitor == RT_NULL) {
        rt_kprintf("PROCESS4 serial monitor not found, exiting\n");

        return;
    }

    while (rt_device_open(serial_monitor, RT_DEVICE_FLAG_STREAM) != RT_EOK);
    DEBUG_PRINT("Process 4 created serial device\n", HEAVY_DEBUG);

    while (1) {

        DEBUG_PRINT("Process 4 is waiting for mail\n", HEAVY_DEBUG);

        result = rt_mb_recv(&p4_mailbox, (rt_ubase_t *)&pointer, RT_WAITING_FOREVER);

        if (result != RT_EOK) {
            DEBUG_PRINT("Process 4 wasn't able to receive mail\n",LIGHT_DEBUG);
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
#ifdef DEADLINE_TESTING
        /*Online deadline testing*/
        if (check_deadline(next_deadline) == DEADLINE_MISS) {
            rt_kprintf("[!!WARNING!!] Process 4 missed the deadline!\n");
        }

        next_deadline = get_next_deadline(next_deadline, P4_DEADLINE_TICKS);
#endif
    }
    return;
}


static void send_json(uint8_t rpm, uint8_t speed, uint8_t proximity, uint8_t humidity)
{
    /*Send json packets over UART to a serial monitor*/
    char string[256];

    sprintf(string, "RPM: %d\n"\
                    "SPEED: %d\n"\
                    "PROXIMITY: %d\n"\
                    "HUMIDITY: %d\n",rpm,speed,proximity,humidity);
    rt_device_write(serial_monitor, 0, string, (sizeof(string) - 1));
    return;
}

#endif
