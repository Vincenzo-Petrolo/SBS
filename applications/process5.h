#ifndef __PROCESS5__
#define __PROCESS5__


#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include "image_edge.h"

#ifdef SIMBUS
/*For including the global simbus*/
#include "process8.h"
#endif

#define M 500
#define N 400


#define P5_STACK 4096 //4kB
#define P5_PRIORITY 3 //lower than p8 and p6
#define P5_TSLICE 50
#define P5_DEADLINE_MS 10 //ms
#define P5_DEADLINE_TICKS RT_TICK_PER_SECOND/1000*P5_DEADLINE_MS
#define P5_MB_POOL_SIZE 128

#ifdef OVERLOAD_TESTING

int image[M*N] = {0};

#endif

static rt_timer_t timerrpm;
static rt_timer_t timervel;
static rt_timer_t timerhum;
static rt_timer_t timerprox;
msg_t msg;


static void timeoutrpm(void)
{
    msg.rpm = get_rpm(&simbus);
}
static void timeoutvel(void)
{
#ifdef SIMBUS
    /*Get bus speed*/
    msg.speed = get_speed(&simbus);
#endif
}

static void timeouthum(void)
{
    msg.humidity = get_humidity(&simbus);
}

static void timeoutprox(void)
{
    msg.proximity = get_proximity(&simbus);
}

void process5_entry()
{


    rt_err_t result;
#ifdef DEADLINE_TESTING
    /*Initialize deadline*/
    rt_tick_t next_deadline = deadline_init(P5_DEADLINE_TICKS);
    rt_tick_t curr_deadline = 0;

#endif
#ifdef OVERLOAD_TESTING
    rt_tick_t start_news, end_news;
#endif

    DEBUG_PRINT("process5 started\n", HEAVY_DEBUG);

    timerrpm = rt_timer_create("timerrpm", timeoutrpm,
                                 NULL, 50,
                                 RT_TIMER_FLAG_PERIODIC);

    timervel = rt_timer_create("timervel", timeoutvel,
                                NULL, 50,
                                 RT_TIMER_FLAG_PERIODIC);

    timerhum = rt_timer_create("timerhum", timeouthum,
                                NULL, 1000,
                                 RT_TIMER_FLAG_PERIODIC);

    timerprox = rt_timer_create("timerprox", timeoutprox,
                                NULL, 50,
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

#ifdef OVERLOAD_TESTING
        start_news = rt_tick_get();
        free(news(M, N, image));
        end_news = rt_tick_get();
        //rt_kprintf("\n\n TIME ELAPSED %u\n\n", end_news - start_news);
#endif
        rt_mb_send_wait(&p6_mailbox, (rt_uint32_t)&msg,100);
        rt_mb_send_wait(&p8_mailbox, (rt_uint32_t)&msg,100);
        rt_mb_send_wait(&p4_mailbox, (rt_uint32_t)&msg,100);
        rt_mb_send_wait(&p7_mailbox, (rt_uint32_t)&msg,100);

        rt_thread_delay(100);

#ifdef DEADLINE_TESTING
        /*Online deadline testing*/
        if (check_deadline(next_deadline) == DEADLINE_MISS) {
            rt_kprintf("[!!WARNING!!] Process 5 missed the deadline!\n");
        }

        if (rt_tick_get() > curr_deadline) {
            curr_deadline = next_deadline;
            next_deadline = get_next_deadline(next_deadline, P5_DEADLINE_TICKS);
        }
#endif

    }
    return;
}

#endif
