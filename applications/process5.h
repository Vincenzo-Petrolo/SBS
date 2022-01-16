#ifndef __PROCESS5__
#define __PROCESS5__

#include "sbs_configuration.h"
#include <rtthread.h>
#include <time.h>

#define P5_STACK 1024 //1kB
#define P5_PRIORITY 3 //lower than p8 and p6
#define P5_TSLICE 10 //TODO verify if this is ok
#define P5_DEADLINE 10 //ms
#define P5_MB_POOL_SIZE 128

typedef struct {
  uint8_t value;
  uint8_t sensor;
} msg_t;

int rpm_comp();
int vel_comp();
int hum_comp();
int prox_comp();

void process5_entry(void *parameter)
{

    uint8_t rpm; //in rpm 0-400
    uint8_t vel; //in kmh 0-80
    uint8_t hum; //in % 0-100
    uint8_t prox; //in m 0-20
    msg_t msg;
    rt_err_t result;

    DEBUG_PRINT("process5 started\n", HEAVY_DEBUG);

    while (1) {

        rpm = rpm_comp();
        vel = vel_comp();
        hum = hum_comp();
        prox = prox_comp();

        if (rpm != -1) {
            msg.value = rpm;
            msg.sensor = 'R';
            result = rt_mb_send(&p6_mailbox, (rt_uint32_t)&msg);
            DEBUG_PRINT("Process 5 is sending a mail\n", HEAVY_DEBUG);
        }

        if (vel != -1) {
            msg.value = vel;
            msg.sensor = 'V';
            result = rt_mb_send(&p6_mailbox, (rt_uint32_t)&msg);
            result = rt_mb_send(&p8_mailbox, (rt_uint32_t)&msg);
            DEBUG_PRINT("Process 5 is sending a mail\n", HEAVY_DEBUG);
        }

        if (hum != -1) {
            msg.value = hum;
            msg.sensor = 'H';
            result = rt_mb_send(&p8_mailbox, msg);
            DEBUG_PRINT("Process 5 is sending a mail\n", HEAVY_DEBUG);
        }

        if (prox != -1) {
            msg.value = prox;
            msg.sensor = 'P';
            result = rt_mb_send(&p8_mailbox, msg);
            //DEBUG_PRINT("Process 5 is sending a mail\n", HEAVY_DEBUG);
        }


        if (result != RT_EOK) {
            DEBUG_PRINT("Process5 wasn't able to send mail\n",LIGHT_DEBUG);
            /*Continue with next cycle*/
            continue;
        }

    return;
}

    int rpm_comp() {
        int v;

        srand(time(NULL));

        v=rand%10;
        if (v ==0)
            return rand%401;
        else
            return -1;
    }

    int vel_comp() {
        int v;

        srand(time(NULL));

        v=rand%10;
        if (v ==0)
            return rand%81;
        else
            return -1;
    }

    int hum_comp() {
        int v;

        srand(time(NULL));

        v=rand%10;
        if (v ==0)
            return rand%101;
        else
            return -1;
    }

    int prox_comp() {
        int v;

        srand(time(NULL));

        v=rand%10;
        if (v ==0)
            return rand%21;
        else
            return -1;
    }

#endif
