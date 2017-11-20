#include <stdio.h>
#include "./ddt/ddt.h"
#include "./com/com.h"
#include "./signal/sig.h"
#include "./pth/pth.h"
#include <pthread.h>
extern threadFptr funcTable[NUM_OF_PTHF];

int main(){
    /*
    struct sigaction sigact;
    sigact.sa_handler=sigusr1Handler;
    sigfillset(&sigact.sa_mask);
    sigact.sa_flags=SA_RESTART;
    sigaction(SIGUSR1,&sigact,NULL);
    while(1);*/
    int s;
    pthread_t com_m;
    initFuncTable();
    s=pthread_create(&com_m,NULL,funcTable[COM_MODULE],(void*)NULL);
    if(s != 0)
        perror("pthread create\n");
    pthread_detach(com_m);
    // parse();
    initDDT();
    setDDT();
    return 0;
}
