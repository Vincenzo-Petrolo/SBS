#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtthread.h>
#include <dfs_posix.h>

#include "sbs_configuration.h"
#include "process5.h"
#include "process6.h"
#include "process8.h"
#include "process4.h"
#include "process3.h"
#include "process1.h"
#include "process2.h"
#include "process7.h"

#ifdef BENCHMARKING
#include "cpu_usage.h"
#endif

/*Visible to this file only*/
static uint8_t p8_mb_pool[P8_MB_POOL_SIZE], p6_mb_pool[P6_MB_POOL_SIZE],p4_mb_pool[P4_MB_POOL_SIZE], p3_mb_pool[2*sizeof(external_state_t)],
p2_mb_pool[P2_MB_POOL_SIZE],p3_mb_pool_bis[P3_MB_POOL_SIZE], p7_mb_pool[P7_MB_POOL_SIZE];

static int fd = -1; //at beginning no file is open

static void hook_of_scheduler(struct rt_thread* from, struct rt_thread* to)
{
    FILE *fp = open("timings.csv", O_WRONLY | O_APPEND | O_CREAT);
#if DEBUG_LEVEL == HEAVY_DEBUG
    rt_kprintf("%s -> %s\n", from->name, to->name);
#endif

    if (fd >= 0) {
        write(fd, to->name, rt_strlen(to->name));
        write(fd, "\n", 1);
        close(fd);
    } else {
        rt_kprintf("Can't open the file\n");
    }
}

static void hook_of_scheduler_light(struct rt_thread* from, struct rt_thread* to)
{
    rt_kprintf("%s -> %s\n", from->name, to->name);
}

int main() {

    rt_err_t result;
    srand(time(NULL));
#ifdef BENCHMARKING
    list_mem();
#endif

#ifndef DEADLINE_TESTING

    fd = open("timings.csv",  O_TRUNC);
    close(fd);
    /*Initialize timestamp filename*/
    fd = open(TIMESTAMP_FILENAME, O_TRUNC);
    close(fd);

    /*If using deadline testing, comment out this otherwise it will
     * use all the bandwidth during the preemption moments and cause
     * all other tasks to miss their deadlines.*/
#if DEBUG_LEVEL != NO_DEBUG
    rt_scheduler_sethook(hook_of_scheduler);
#endif

#endif

#ifdef BENCHMARKING
    list_mem();
    /*Initialize the module*/
    cpu_usage_init();
    /*Let the system run for a given amount of ms, then get benchmarks*/
    rt_timer_t benchamrks_timer = rt_timer_create("benchamrks_timer",
                                                &print_benchmarks_results,
                                                NULL,
                                                ms2ticks(1000* 10),
                                                RT_TIMER_FLAG_ONE_SHOT);
    /*Start the timer*/
    if (benchamrks_timer != NULL)
        rt_timer_start(benchamrks_timer);
#endif

    rt_sem_init(&sem_lock, "lock", 1, RT_IPC_FLAG_FIFO);

    /*MAILBOX INITIALIZATION*/

    result  = rt_mb_init(&p2_mailbox, "p2mb", &p2_mb_pool, P2_MB_POOL_SIZE/4, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK) {
        rt_kprintf("[ERROR] : unable to initialize mailbox P2\n");
        return 1;
    }

    /*The mailbox for process 3, is using only two entries, one for the new value and one for receiving a new value*/
    result  = rt_mb_init(&p3_mailbox, "p3mb", &p3_mb_pool, P3_MB_POOL_SIZE/4, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK) {
        rt_kprintf("[ERROR] : unable to initialize mailbox P3\n");
        return 1;
    }

    result  = rt_mb_init(&p3_mailbox_bis, "p3mbbis", &p3_mb_pool_bis, P3_MB_POOL_SIZE/4, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK) {
        rt_kprintf("[ERROR] : unable to initialize mailbox P3 bis\n");
        return 1;
    }

    result  = rt_mb_init(&p4_mailbox, "p4mb", &p4_mb_pool, P4_MB_POOL_SIZE/4, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK) {
        rt_kprintf("[ERROR] : unable to initialize mailbox P4\n");
        return 1;
    }

    result  = rt_mb_init(&p6_mailbox, "p6mb", &p6_mb_pool, P6_MB_POOL_SIZE/4, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK) {
        rt_kprintf("[ERROR] : unable to initialize mailbox P6\n");
        return 1;
    }

    result  = rt_mb_init(&p7_mailbox, "p7mb", &p7_mb_pool, P7_MB_POOL_SIZE/4, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK) {
        rt_kprintf("[ERROR] : unable to initialize mailbox P7\n");
        return 1;
    }

    result  = rt_mb_init(&p8_mailbox, "p8mb", &p8_mb_pool, P8_MB_POOL_SIZE/4, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK) {
        rt_kprintf("[ERROR] : unable to initialize mailbox P8\n");
        return 1;
    }

    /*THREADS CREATION*/

    rt_thread_t process1_thread = rt_thread_create("process1",
                                                        process1_entry,
                                                        NULL,
                                                        P1_STACK,
                                                        P1_PRIORITY,
                                                        P1_TSLICE);

    if (process1_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process1 failed to create\n");
        return 1;
    }

    rt_thread_t process2_thread = rt_thread_create("process2",
                                                        process2_entry,
                                                        NULL,
                                                        P2_STACK,
                                                        P2_PRIORITY,
                                                        P2_TSLICE);

    if (process2_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process2 failed to create\n");
        return 1;
    }

    rt_thread_t process3_thread = rt_thread_create("process3",
                                                    process3_entry,
                                                    NULL,
                                                    P3_STACK,
                                                    P3_PRIORITY,
                                                    P3_TSLICE);

    if (process3_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process5 failed to create\n");
        return 1;
    }

    rt_thread_t process4_thread = rt_thread_create("process4",
                                                     process4_entry,
                                                     NULL,
                                                     P4_STACK,
                                                     P4_PRIORITY,
                                                     P4_TSLICE);

     if (process4_thread == RT_NULL) {
         rt_kprintf("[ERROR] : process4 failed to create\n");
         return 1;
    }

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

    rt_thread_t process6_thread = rt_thread_create("process6",
                                                        process6_entry,
                                                        NULL,
                                                        P6_STACK,
                                                        P6_PRIORITY,
                                                        P6_TSLICE);

    if (process6_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process6 failed to create\n");
        return 1;
    }

    rt_thread_t process7_thread = rt_thread_create("process7",
                                                            process7_entry,
                                                            NULL,
                                                            P7_STACK,
                                                            P7_PRIORITY,
                                                            P7_TSLICE);

    if (process7_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process7 failed to create\n");
        return 1;
    }

     process8_thread = rt_thread_create("process8",
                                                    process8_entry,
                                                    NULL,
                                                    P8_STACK,
                                                    P8_PRIORITY,
                                                    P8_TSLICE);

    if (process8_thread == RT_NULL) {
        rt_kprintf("[ERROR] : process8 failed to create\n");
        return 1;
    }

    /*THREAD STARTUP*/

    rt_err_t p1_startup_error = rt_thread_startup(process1_thread);

    if (p1_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 1 failed to start\n");
        return 1;
    }

    rt_err_t p2_startup_error = rt_thread_startup(process2_thread);

    if (p2_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 2 failed to start\n");
        return 1;
    }
    rt_err_t p3_startup_error = rt_thread_startup(process3_thread);

    if (p3_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 3 failed to start\n");
        return 1;
    }
    rt_err_t p4_startup_error = rt_thread_startup(process4_thread);

    if (p4_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 4 failed to start\n");
        return 1;
    }

    rt_err_t p5_startup_error = rt_thread_startup(process5_thread);

    if (p5_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 5 failed to start\n");
        return 1;
    }

    rt_err_t p6_startup_error = rt_thread_startup(process6_thread);

    if (p6_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 6 failed to start\n");
        return 1;
    }

    rt_err_t p7_startup_error = rt_thread_startup(process7_thread);

    if (p7_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 7 failed to start\n");
        return 1;
    }

    rt_err_t p8_startup_error = rt_thread_startup(process8_thread);

    if (p8_startup_error == RT_ERROR) {
        rt_kprintf("[ERORR] : process 8 failed to start\n");
        return 1;
    }

    #ifdef BENCHMARKING
        list_mem();
    #endif

    return 0;
}
