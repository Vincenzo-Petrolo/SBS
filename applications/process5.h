#ifndef __PROCESS5__
#define __PROCESS5__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <time.h>

#define P5_STACK 4096 //1kB
#define P5_PRIORITY 10 //lower than p8 and p6
#define P5_TSLICE 1
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

    while (1) {
        rt_kprintf("Doing stuff\n");
        int a = 1+1;
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
