#include "sig.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
extern volatile sig_atomic_t gSigStat;
int main(){


    struct sigaction sigact;
    sigact.sa_handler=sigusr1Handler;
    sigfillset(&sigact.sa_mask);
    sigact.sa_flags=SA_RESTART;
    sigaction(SIGUSR2,&sigact,NULL);
    sigaction(SIGUSR1,&sigact,NULL);
    while(!gSigStat)
        continue;

    return 0;



}
