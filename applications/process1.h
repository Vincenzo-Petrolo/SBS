#ifndef __PROCESS1__
#define __PROCESS1__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <tiny_aes.h>


#define P1_STACK 4096 //4kB
#define P1_PRIORITY 3 //lower than hard real time tasks
#define P1_TSLICE 10
#define P1_DEADLINE_MS 25
#define P1_DEADLINE_TICKS RT_TICK_PER_SECOND/1000*P1_DEADLINE_MS
#define P1_MB_POOL_SIZE 128

void receive_data(unsigned char *encrypted_value);

void process1_entry()
{
    unsigned char encrypted_value[32];
#ifdef DEADLINE_TESTING
    /*Initialize deadline*/
    rt_tick_t next_deadline = deadline_init(P1_DEADLINE_TICKS);
    rt_tick_t curr_deadline = 0;
#endif

    rt_err_t result;


    while (1) {

        receive_data(encrypted_value);

        /*Send data to p3 waiting for it to empty if it is full*/
        result = rt_mb_send_wait(&p3_mailbox, (rt_uint32_t)encrypted_value, 25);
        /*If timeout is reached or error encountered then receive new data, because this is a firm realtime task*/
        if (result == -RT_ETIMEOUT) {
            DEBUG_PRINT("P1 reached timeout waiting for p3 to empty", LIGHT_DEBUG);

            continue;
        } else if (result == -RT_ERROR) {
            DEBUG_PRINT("P1 error when sending mail\n", LIGHT_DEBUG);

            continue;
        }
#ifdef DEADLINE_TESTING
        /*Online deadline testing*/
        if (check_deadline(next_deadline) == DEADLINE_MISS) {
            rt_kprintf("[!!WARNING!!] Process 1 missed the deadline!\n");
        }

        if (rt_tick_get() > curr_deadline) {
            curr_deadline = next_deadline;
            next_deadline = get_next_deadline(next_deadline, P1_DEADLINE_TICKS);
        }
#endif
    }
}

void receive_data(unsigned char *encrypted_value)
{
    uint8_t data_to_encrypt[32];
    tiny_aes_context ctx;
    uint8_t iv[16 + 1], private_key[32 + 1];


    /*Generate pseudo random values evolving with time*/
    external_state_t val = {
        rt_tick_get()%13,
        rt_tick_get()%54,
        3
    };

    /*Store the values (which are bytes) in an array, in order to perform encryption*/
    rt_memcpy(data_to_encrypt, &val, sizeof(val.crossway_proximity));
    rt_memcpy(data_to_encrypt + sizeof val.crossway_proximity, &val, sizeof(val.traffic));
    rt_memcpy(data_to_encrypt + sizeof val.crossway_proximity + sizeof val.traffic, &val, sizeof(val.traffic_light_status));

    rt_memcpy(iv, TEST_TINY_AES_IV, rt_strlen(TEST_TINY_AES_IV));
    iv[rt_strlen((const char *)iv) - 1] = '\0';
    rt_memcpy(private_key, TEST_TINY_AES_KEY, rt_strlen(TEST_TINY_AES_KEY));
    private_key[sizeof(private_key) - 1] = '\0';
    rt_memset(encrypted_value, 0x0, sizeof(encrypted_value));
    tiny_aes_setkey_enc(&ctx, (uint8_t *) private_key, 256);
    tiny_aes_crypt_cbc(&ctx, AES_ENCRYPT, sizeof(external_state_t), iv, data_to_encrypt,encrypted_value);

    return;
}
#endif
