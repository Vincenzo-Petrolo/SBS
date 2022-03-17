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



void process5_entry()
{
    int a;

    while (1) {
        rt_kprintf("Doing stuff\n");
        a = 1+1;
        rt_thread_delay(10);
    }
    return;
}

#endif
