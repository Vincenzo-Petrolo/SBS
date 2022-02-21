#ifndef __PROCESS3__
#define __PROCESS3__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <tiny_aes.h>

#define P3_STACK 4096 //1kB
#define P3_PRIORITY 3 //lower than hard real time tasks
#define P3_TSLICE 10 //TODO verify if this is ok
#define P3_DEADLINE 25 //ms

static external_state_t decrypt(void *encrypted_value);

void process3_entry()
{
    rt_err_t result;
    unsigned char *encrypted_value;
    external_state_t received_external_values;
    rt_kprintf("%d\n", sizeof(external_state_t));

    while (1) {

        DEBUG_PRINT("Process 3 is waiting for mail\n", HEAVY_DEBUG);

        /*Wait for a given amount of time, if no message incoming then
         * continue checking for other messages*/
        result = rt_mb_recv(&p3_mailbox, (rt_ubase_t *)&encrypted_value, 1000);

        if (result != RT_EOK) {
            DEBUG_PRINT("Process 3 wasn't able to receive mail\n",LIGHT_DEBUG);
        } else {
            received_external_values = decrypt(encrypted_value);
        }


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

#endif
