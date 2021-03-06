#ifndef __SBS_CONFIGURATION__
#define __SBS_CONFIGURATION__

#include <stdio.h>
#include <rtthread.h>
#include "cpu_usage.h"
#include "simbus.h"
/*Debug levels to be used as the lvl parameter for the macro DEBUG_PRINT*/
#define HEAVY_DEBUG 3
#define MODERATE_DEBUG 2
#define LIGHT_DEBUG 1
#define NO_DEBUG 0 /*Don't use this with the macro DEBUG_PRINT!!!*/

/*Define the global debug level*/
#define DEBUG_LEVEL LIGHT_DEBUG


/*****************CONFIGURATION******************/
#define DEADLINE_TESTING
//#define OVERLOAD_TESTING
#define SIMBUS
#define BENCHMARKING
/*****************END CONFIGURATION**************/

#ifdef SIMBUS
bus_t simbus;
#endif

#define DEBUG_PRINT(string, lvl) \
    if (lvl <= DEBUG_LEVEL) {\
        printf(string);\
    }\

#define TEST_TINY_AES_IV  "0123456789ABCDEF"
#define TEST_TINY_AES_KEY "0123456789ABCDEF0123456789ABCDEF"

#define TIMESTAMP_FILENAME "timestamp.csv"


struct rt_mailbox p8_mailbox, p6_mailbox, p4_mailbox, p3_mailbox, p2_mailbox, p3_mailbox_bis, p7_mailbox;

rt_thread_t process8_thread;

char shared_mem1to3[32 + 1], shared_mem3to2[32 + 1];

struct rt_semaphore sem_lock;

const struct dfs_mount_tbl mount_table[] =
{
    {"sd0", "/", "elm", 0, 0},
    {0}
};

#ifdef DEADLINE_TESTING


uint32_t missed_deadlines_count = 0;

/**
 * Function tools created for online
 * deadline checks.
 * */
#define DEADLINE_MISS 0
#define DEADLINE_OK 1

rt_tick_t deadline_init(rt_tick_t process_deadline)
{
    return rt_tick_get() + process_deadline;
}

uint8_t check_deadline(rt_tick_t next_deadline)
{
    rt_tick_t curr_time = rt_tick_get();

    if (curr_time > next_deadline) {
        missed_deadlines_count++;
        return DEADLINE_MISS;
    }

    return DEADLINE_OK;
}


rt_tick_t get_next_deadline(rt_tick_t curr_deadline, rt_tick_t process_deadline)
{
    return curr_deadline + process_deadline;
}



#endif

rt_tick_t ms2ticks(int milliseconds)
{
    return RT_TICK_PER_SECOND/1000*milliseconds;
}

int ticks2ms(uint64_t ticks)
{
   return ticks * 1000 / RT_TICK_PER_SECOND;
}

#ifdef BENCHMARKING

uint8_t missed_deadlines_count = 0;

void print_benchmarks_results(void)
{

    float cpu_average_load = cpu_load_average();
    cpu_usage_t *infos = cpu_usage_obj();

    printf("\n================================================");
    printf(
            "\nTotal idle time: %d\n"\
            "Average CPU load: %.2f%%\n",\
                                        ticks2ms(infos->idle_stat[0].idle_tick),
                                        cpu_average_load
                                        );
#ifdef DEADLINE_TESTING
    printf("Number of missed deadlines: %u\n", missed_deadlines_count);
#endif
    printf("\n================================================\n");



    return;
}

#endif

#endif
