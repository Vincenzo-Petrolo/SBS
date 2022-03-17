#ifndef __PROCESS3__
#define __PROCESS3__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <tiny_aes.h>

#define P3_STACK 4096 //4kB
#define P3_PRIORITY 3 //lower than hard real time tasks
#define P3_TSLICE 10
#define P3_DEADLINE_MS 25 //ms
#define P3_DEADLINE_TICKS RT_TICK_PER_SECOND/1000*P3_DEADLINE_MS
#define P3_MB_POOL_SIZE 128

static external_state_t decrypt(void *encrypted_value);
static void encrypt(void *plaintext_value, unsigned char *ptr);

void process3_entry()
{
    rt_err_t result;
    unsigned char *encrypted_value;
    unsigned char encrypted_data_to_send[32];
    external_state_t received_external_values;
    bus_state_t internal_bus_status; //receive this from p5
#ifdef DEADLINE_TESTING
    /*Initialize deadline*/
    rt_tick_t next_deadline = deadline_init(P3_DEADLINE_TICKS);
    rt_tick_t curr_deadline = 0;
#endif
    while (1) {

        DEBUG_PRINT("Process 3 is waiting for mail\n", HEAVY_DEBUG);

        /*Wait for a given amount of time, if no message incoming then
         * continue checking for other messages*/
        result = rt_mb_recv(&p3_mailbox, (rt_ubase_t *)&encrypted_value, 25);

        if (result != RT_EOK) {
            DEBUG_PRINT("Process 3 wasn't able to receive mail\n",LIGHT_DEBUG);
        } else {
            received_external_values = decrypt(encrypted_value);
        }

        result = rt_mb_recv(&p3_mailbox_bis, (rt_ubase_t *)&internal_bus_status, 25);

        if (result != RT_EOK) {
            DEBUG_PRINT("Process 3 wasn't able to receive mail from process 5\n",LIGHT_DEBUG);
        } else {
            encrypt(&internal_bus_status, encrypted_data_to_send);
            /*After it is encrypted, send it to p2*/
            result = rt_mb_send(&p2_mailbox, (rt_uint32_t)encrypted_data_to_send);
        }
#ifdef DEADLINE_TESTING
        /*Online deadline testing*/
        if (check_deadline(next_deadline) == DEADLINE_MISS) {
            rt_kprintf("[!!WARNING!!] Process 3 missed the deadline!\n");
#ifdef BENCHMARKING
            missed_deadlines_count++;
#endif
        }

        if (rt_tick_get() > curr_deadline) {
            curr_deadline = next_deadline;
            next_deadline = get_next_deadline(next_deadline, P3_DEADLINE_TICKS);
        }
#endif
    }
}

static external_state_t decrypt(void *encrypted_value)
{
    unsigned char decrypted_value[32];
    external_state_t value;
    tiny_aes_context ctx;

    uint8_t iv[16 + 1];
    uint8_t private_key[32 + 1];


    /* decrypt */
    rt_memcpy(iv, TEST_TINY_AES_IV, rt_strlen(TEST_TINY_AES_IV));
    iv[sizeof(iv) - 1] = '\0';
    rt_memcpy(private_key, TEST_TINY_AES_KEY, rt_strlen(TEST_TINY_AES_KEY));
    private_key[sizeof(private_key) - 1] = '\0';

    rt_memset(decrypted_value, 0x0, sizeof(decrypted_value));
    tiny_aes_setkey_dec(&ctx, (uint8_t *) private_key, 256);
    tiny_aes_crypt_cbc(&ctx, AES_DECRYPT, sizeof(external_state_t), iv, encrypted_value, decrypted_value);

    /*Recreate the struct from encrypted bytes*/
    value.crossway_proximity = decrypted_value[0];
    value.traffic = decrypted_value[1];
    value.traffic_light_status = decrypted_value[2];

    return value;
}

static void encrypt(void *plaintext_value, unsigned char *ptr)
{
    external_state_t value;
    tiny_aes_context ctx;

    uint8_t iv[16 + 1];
    uint8_t private_key[32 + 1];


    /* encrypt */
    rt_memcpy(iv, TEST_TINY_AES_IV, rt_strlen(TEST_TINY_AES_IV));
    iv[sizeof(iv) - 1] = '\0';
    rt_memcpy(private_key, TEST_TINY_AES_KEY, rt_strlen(TEST_TINY_AES_KEY));
    private_key[sizeof(private_key) - 1] = '\0';

    rt_memset(ptr, 0x0, sizeof(ptr));
    tiny_aes_setkey_enc(&ctx, (uint8_t *) private_key, 256);
    tiny_aes_crypt_cbc(&ctx, AES_ENCRYPT, sizeof(bus_state_t), iv, plaintext_value, ptr);

    return;
}

#endif
