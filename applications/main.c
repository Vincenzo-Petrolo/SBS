#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "sbs_configuration.h"

int main(void)
{
    printf("hello rt-thread\n");
    printf("saluti viandante\n");

    DEBUG_PRINT("Ciao da claudio\n",LIGHT_DEBUG); //example of usage of macro DEBUG_PRINT
    return 0;
}
