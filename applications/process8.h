#ifndef __PROCESS8__
#define __PROCESS8__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <dfs_posix.h>

#define P8_STACK 4096 //1kB
#define P8_PRIORITY 10 //lower than p6
#define P8_TSLICE 1 //TODO verify if this is ok
#define P8_DEADLINE 10 //ms
#define P8_MB_POOL_SIZE 128

void process8_entry()
{

    int fd = open("pippo.txt", O_CREAT | O_WRONLY);
    int written;
    char buffer[] = "Ciao da claudio\n";

     if (fd > 0) {
         while (1) {
             written = write(fd, buffer,rt_strlen(buffer) );
             rt_kprintf("Written %d bytes\n", written);
         }
     }


}

#endif
