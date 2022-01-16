#ifndef __PROCESS8__
#define __PROCESS8__

#include "sbs_configuration.h"
#include <rtthread.h>
#include <time.h>

#define P5_STACK 1024 //1kB
#define P5_PRIORITY 3 //lower than p8 and p6
#define P5_TSLICE 10 //TODO verify if this is ok
#define P5_DEADLINE 10 //ms
#define P5_MB_POOL_SIZE 128



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



    return;
}


#endif
