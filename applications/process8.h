#ifndef __PROCESS8__
#define __PROCESS8__

#include "sbs_configuration.h"

#define P8_STACK 1024 //1kB
#define P8_PRIORITY 1 //highest priority
#define P8_TSLICE 10 //TODO verify if this is ok

void process8_entry(void *parameter)
{

    DEBUG_PRINT("process8 started\n", HEAVY_DEBUG);

    /*I should receive data from parameter argument
     *  and perform some if checking*/
    DEBUG_PRINT("BRAKING!!\n",LIGHT_DEBUG); //important to print even in light debugging

    return;
}

#endif
