#ifndef __PROCESS1__
#define __PROCESS1__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <tiny_aes.h>

#define P1_STACK 1024 //1kB
#define P1_PRIORITY 3 //lower than hard real time tasks
#define P1_TSLICE 10 
#define P1_DEADLINE 25 //ms
#define P1_MB_POOL_SIZE 128

void receive_data(unsigned char *encrypted_value);

void process1_entry()
{
    unsigned char value[sizeof(external_state_t)];
    rt_err_t result;
    
    while (1) {

        receive_data(value);

        /*Send data to p3*/
        result = rt_mb_send(&p3_mailbox, (rt_uint32_t)value);

        if (result != RT_EOK) {
            DEBUG_PRINT("P1 can't send mail\n", LIGHT_DEBUG);

            continue;
        }
    }
}

/*emulate, reception of encrypted data*/
void receive_data(unsigned char *encrypted_value)
{
    tiny_aes_context ctx;
    uint8_t iv[16 + 1], private_key[32 + 1];
    unsigned char data_to_encrypt[sizeof(external_state_t)];

    /*Simulate the wait for a new value from the receiver*/
    //rt_thread_delay(100);
    /*Generate pseudo random values evolving with time*/
    external_state_t val = {
            rt_tick_get()%13,
            rt_tick_get()%54,
            3
    };
    rt_kprintf("PROCESS 1 Sending: %u, %u, %u\n", val.crossway_proximity,
                                                                val.traffic,
                                                                val.traffic_light_status);
    /*Store the values (which are bytes) in an array, in order to perform encryption*/
    data_to_encrypt[0] = val.crossway_proximity;
    data_to_encrypt[1] = val.traffic;
    data_to_encrypt[2] = val.traffic_light_status;

    rt_memcpy(iv, TEST_TINY_AES_IV, rt_strlen(TEST_TINY_AES_IV));
    iv[rt_strlen(iv) - 1] = '\0';
    tiny_aes_setkey_enc(&ctx, (uint8_t *) private_key, 256);
    tiny_aes_crypt_cbc(&ctx, AES_ENCRYPT, sizeof(external_state_t), iv, data_to_encrypt,encrypted_value);
}

#endif
