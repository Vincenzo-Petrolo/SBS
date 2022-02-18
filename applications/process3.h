#ifndef __PROCESS3__
#define __PROCESS3__

#include "sbs_configuration.h"
#include "custom_types.h"
#include <rtthread.h>
#include <tiny_aes.h>

#define P3_STACK 1024 //1kB
#define P3_PRIORITY 3 //lower than hard real time tasks
#define P3_TSLICE 10 //TODO verify if this is ok
#define P3_DEADLINE 25 //ms
#define P3_MB_POOL_SIZE 128




void process3_entry()
{
    tiny_aes_context ctx;
    uint8_t iv[16 + 1], private_key[32 + 1];

    while (1) {

        rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

        unsigned char data_to_encrypt[32 + 1];
        unsigned char data_to_decrypt[32 + 1];

        rt_memcpy(data_to_encrypt, "ciao\0", 5); //TODO find out if this is working
        /* encrypt */
        rt_memcpy(iv, TEST_TINY_AES_IV, rt_strlen(TEST_TINY_AES_IV));
        iv[sizeof(iv) - 1] = '\0';
        rt_memcpy(private_key, TEST_TINY_AES_KEY, rt_strlen(TEST_TINY_AES_KEY));
        private_key[sizeof(private_key) - 1] = '\0';

        tiny_aes_setkey_enc(&ctx, (uint8_t *) private_key, 256);
        tiny_aes_crypt_cbc(&ctx, AES_ENCRYPT, rt_strlen(data_to_encrypt), iv, data_to_encrypt, shared_mem3to2);

        /* decrypt */
        rt_memcpy(iv, TEST_TINY_AES_IV, rt_strlen(TEST_TINY_AES_IV));
        iv[sizeof(iv) - 1] = '\0';
        rt_memcpy(private_key, TEST_TINY_AES_KEY, rt_strlen(TEST_TINY_AES_KEY));
        private_key[sizeof(private_key) - 1] = '\0';

        tiny_aes_setkey_dec(&ctx, (uint8_t *) private_key, 256);
        tiny_aes_crypt_cbc(&ctx, AES_DECRYPT, rt_strlen(shared_mem1to3), iv, shared_mem1to3, data_to_decrypt); //maybe different strlen

        rt_sem_release(&sem_lock);
    }
}



#endif
