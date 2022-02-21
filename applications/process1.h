#ifndef __PROCESS1__
#define __PROCESS1__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <tiny_aes.h>


#define P1_STACK 4096 //1kB
#define P1_PRIORITY 4 //lower than hard real time tasks
#define P1_TSLICE 10
#define P1_DEADLINE 25 //ms
#define P1_MB_POOL_SIZE 128

void receive_data(unsigned char *encrypted_value);

void process1_entry()
{
    unsigned char encrypted_value[32];

    rt_err_t result;


    while (1) {

        receive_data(encrypted_value);

        /*Send data to p3*/
        result = rt_mb_send(&p3_mailbox, (rt_uint32_t)encrypted_value);

        if (result != RT_EOK) {
            DEBUG_PRINT("P1 can't send mail\n", LIGHT_DEBUG);

            continue;
        }
    }
}

void receive_data(unsigned char *encrypted_value)
{
    unsigned char data_to_encrypt[sizeof(external_state_t)];
    tiny_aes_context ctx;
    uint8_t iv[16 + 1], private_key[32 + 1];
    /*Generate pseudo random values evolving with time*/
    external_state_t val = {
            rt_tick_get()%13,
            rt_tick_get()%54,
            3
    };


    /*Store the values (which are bytes) in an array, in order to perform encryption*/
    data_to_encrypt[0] = val.crossway_proximity;
    data_to_encrypt[1] = val.traffic;
    data_to_encrypt[2] = val.traffic_light_status;

    rt_memcpy(iv, TEST_TINY_AES_IV, rt_strlen(TEST_TINY_AES_IV));
    iv[rt_strlen(iv) - 1] = '\0';
    rt_memcpy(private_key, TEST_TINY_AES_KEY, rt_strlen(TEST_TINY_AES_KEY));
    private_key[sizeof(private_key) - 1] = '\0';
    rt_memset(encrypted_value, 0x0, sizeof(encrypted_value));
    tiny_aes_setkey_enc(&ctx, (uint8_t *) private_key, 256);
    tiny_aes_crypt_cbc(&ctx, AES_ENCRYPT, sizeof(external_state_t), iv, data_to_encrypt,encrypted_value);

    return;
}
#endif
