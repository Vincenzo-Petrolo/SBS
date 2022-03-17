#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtthread.h>
#include <dfs_posix.h>

#include "sbs_configuration.h"
#include "process5.h"
#include "process8.h"


static int fd = -1; //at begininning no file is open

static void hook_of_scheduler(struct rt_thread* from, struct rt_thread* to)
{

    fd = open("timings.csv", O_WRONLY | O_APPEND | O_CREAT);
#if HEAVY_DEBUG
    rt_kprintf("%s -> %s\n", from->name, to->name);
#endif

    if (fd>= 0) {
        write(fd, to->name, rt_strlen(to->name));
        write(fd, "\n", 1);
        close(fd);
    } else {
        rt_kprintf("Can't open the file\n");
    }
}


int main() {


    rt_err_t result;
    srand(time(NULL));


    fd = open("timings.csv",  O_TRUNC);
    close(fd);

    rt_scheduler_sethook(hook_of_scheduler);


    rt_sem_init(&sem_lock, "lock", 1, RT_IPC_FLAG_FIFO);

    /*TOOD use for loops to initialize everything in order to avoid huge file which affects readability*/

    rt_thread_t process5_thread = rt_thread_create("process5",
                                                    process5_entry,
                                                    NULL,
                                                    P5_STACK,
                                                    P5_PRIORITY,
                                                    P5_TSLICE);


    if (process5_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process5 failed to create\n");

        return 1;
    }



    rt_thread_t process8_thread = rt_thread_create("process8",
                                                    process8_entry,
                                                    NULL,
                                                    P8_STACK,
                                                    P8_PRIORITY,
                                                    P8_TSLICE);

    if (process8_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process8 failed to create\n");

        return 1;
    }


    rt_err_t p8_startup_error = rt_thread_startup(process8_thread);

    if (p8_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 8 failed to start\n");

        return 1;
    }


    rt_err_t p5_startup_error = rt_thread_startup(process5_thread);

    if (p5_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 5 failed to start\n");

        return 1;
    }


    return 0;
}
