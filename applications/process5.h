#ifndef __PROCESS5__
#define __PROCESS5__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <time.h>

#define P5_STACK 4096 //1kB
#define P5_PRIORITY 3 //lower than p8 and p6
#define P5_TSLICE 10 
#define P5_DEADLINE 10 //ms
#define P5_MB_POOL_SIZE 128



int rpm_comp();
int vel_comp();
int hum_comp();
int prox_comp();

static rt_timer_t timerrpm;
static rt_timer_t timervel;
static rt_timer_t timerhum;
static rt_timer_t timerprox;

static void timeoutrpm(void *rpm)
{
    int *p;
    p = (int *) rpm;
    *p = rpm_comp();
}
static void timeoutvel(void *vel)
{
    int *p;
    p = (int *) vel;
    *p = vel_comp();
}

static void timeouthum(void *hum)
{
    int *p;
    p = (int *) hum;
    *p = hum_comp();
}

static void timeoutprox(void *prox)
{
    int *p;
    p = (int *) prox;
    *p = prox_comp();
}

void process5_entry()
{

    int rpm; //in rpm 0-400
    int vel; //in kmh 0-80
    int hum; //in % 0-100
    int prox; //in m 0-20
    msg_t msg;
    rt_err_t result;

    DEBUG_PRINT("process5 started\n", HEAVY_DEBUG);

    timerrpm = rt_timer_create("timerrpm", timeoutrpm,
                                 (void *)&rpm, 50,
                                 RT_TIMER_FLAG_PERIODIC);

    timervel = rt_timer_create("timervel", timeoutvel,
                                (void *)&vel, 50,
                                 RT_TIMER_FLAG_PERIODIC);

    timerhum = rt_timer_create("timerhum", timeouthum,
                                (void *)&hum, 1000,
                                 RT_TIMER_FLAG_PERIODIC);

    timerprox = rt_timer_create("timerprox", timeoutprox,
                                (void *)&prox, 10,
                                 RT_TIMER_FLAG_PERIODIC);

    if (timerrpm != RT_NULL)
        rt_timer_start(timerrpm);

    if (timervel != RT_NULL)
        rt_timer_start(timervel);

    if (timerhum != RT_NULL)
        rt_timer_start(timerhum);

    if (timerprox != RT_NULL)
        rt_timer_start(timerprox);

    while (1) {
        /*TODO since we are giving other threads the same pointer
         * to the msg variable, then it might happen that the content
         * of a msg is written during the read from the other thread.
         * Since msg_t type is only 16bits we could send it as a copy.
         *TOOD compact in for loops
         */
        if (rpm != -1) {
            msg.value = rpm;
            msg.sensor = 'R';
            result = rt_mb_send(&p6_mailbox, (rt_uint32_t)&msg);
            result = rt_mb_send(&p8_mailbox, (rt_uint32_t)&msg);
            result = rt_mb_send(&p4_mailbox, (rt_uint32_t)&msg);
            result = rt_mb_send(&p7_mailbox, (rt_uint32_t)&msg);

            DEBUG_PRINT("Process 5 is sending a mail\n", HEAVY_DEBUG);
        }

        if (vel != -1) {
            msg.value = vel;
            msg.sensor = 'V';
            result = rt_mb_send(&p6_mailbox, (rt_uint32_t)&msg);
            result = rt_mb_send(&p8_mailbox, (rt_uint32_t)&msg);
            result = rt_mb_send(&p4_mailbox, (rt_uint32_t)&msg);
            result = rt_mb_send(&p7_mailbox, (rt_uint32_t)&msg);

            DEBUG_PRINT("Process 5 is sending a mail\n", HEAVY_DEBUG);
        }

        if (hum != -1) {
            msg.value = hum;
            msg.sensor = 'H';
            result = rt_mb_send(&p8_mailbox, (rt_uint32_t)&msg);
            result = rt_mb_send(&p4_mailbox, (rt_uint32_t)&msg);
            result = rt_mb_send(&p7_mailbox, (rt_uint32_t)&msg);

            DEBUG_PRINT("Process 5 is sending a mail\n", HEAVY_DEBUG);
        }

        if (prox != -1) {
            msg.value = prox;
            msg.sensor = 'P';
            result = rt_mb_send(&p8_mailbox, (rt_uint32_t)&msg);
            result = rt_mb_send(&p4_mailbox, (rt_uint32_t)&msg);
            result = rt_mb_send(&p7_mailbox, (rt_uint32_t)&msg);

            DEBUG_PRINT("Process 5 is sending a mail\n", HEAVY_DEBUG);
        }

        if (result != RT_EOK) {
            DEBUG_PRINT("Process5 wasn't able to send mail\n",LIGHT_DEBUG);
            /*Continue with next cycle*/
            continue;
        }

        /*Physical delay of polling*/
        rt_thread_delay(100);

    }
    return;
}

    int rpm_comp() {

        return rand()%401;
    }

    int vel_comp() {

        return rand()%81;

    }

    int hum_comp() {

        return rand()%101;

    }

    int prox_comp() {

        return rand()%21;

    }

#endif
