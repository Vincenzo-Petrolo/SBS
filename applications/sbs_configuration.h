#ifndef __SBS_CONFIGURATION__
#define __SBS_CONFIGURATION__


/*Debug levels to be used as the lvl parameter for the macro DEBUG_PRINT*/
#define HEAVY_DEBUG 3
#define MODERATE_DEBUG 2
#define LIGHT_DEBUG 1
#define NO_DEBUG 0 /*Don't use this with the macro DEBUG_PRINT!!!*/

/*Define the global debug level*/
#define DEBUG_LEVEL HEAVY_DEBUG

#define DEBUG_PRINT(string, lvl) \
    if (lvl <= DEBUG_LEVEL) {\
        printf(string);\
    }\

#define TEST_TINY_AES_IV  "0123456789ABCDEF"
#define TEST_TINY_AES_KEY "0123456789ABCDEF0123456789ABCDEF"

struct rt_mailbox p8_mailbox, p6_mailbox, p4_mailbox, p3_mailbox, p2_mailbox;

char shared_mem1to3[32 + 1], shared_mem3to2[32 + 1];

struct rt_semaphore sem_lock;

const struct dfs_mount_tbl mount_table[] =
{
    {"sd0", "/", "elm", 0, 0},
    {0}
};

#endif
