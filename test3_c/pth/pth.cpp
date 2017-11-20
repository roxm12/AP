#include "pth.h"
#include "../com/com.h"
#include "../signal/sig.h"
#include <stdio.h>
//Thread functions
/*
function: void initFuncTable()
arthor:정한솔 20170806
return: 
parameter:
function details:
함수 테이블의 참조 선언
 */
threadFptr funcTable[NUM_OF_PTHF];
void initFuncTable(){
    funcTable[DDT_MODULE]=ddtModule;
    funcTable[COM_MODULE]=comModule;
    funcTable[UPDATE_MODULE]=updateModule;
}
void * comModule(void *arg){
    printf("comModule\n");
    struct sigaction sigact;
    sigact.sa_handler=sigusr1Handler;
    sigfillset(&sigact.sa_mask);
    sigact.sa_flags=SA_RESTART;
    sigaction(SIGUSR1,&sigact,NULL);
    while(1);
    return NULL;
}
void * updateModule(void *arg){
    printf("updateModule\n");
    return NULL;
}
/*
function: void * ddtModule(void *arg)
arthor:정한솔 20170806
return: 
parameter:
function details:
setDDT()을 thread로 실행하기 위한 Wrapper function
 */
void * ddtModule(void *arg){
    printf("ddtModule\n");
    return NULL;
}

