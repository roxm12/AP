#ifndef __PTHREAD_H__
#define __PTHREAD_H__
#define NUM_OF_PTHF 3
#include<pthread.h>
#include"arpCache.h"
typedef void* (*threadFptr)(void *);
typedef enum{
	DDT_MODULE=0,
	READ,
    FILTER,
	UPDATE
}pth_type;

threadFptr funcTable[NUM_OF_PTHF];

void * ddtModule(void *);
void * shmreadModule(void *);
void initFuncTable();


#endif

