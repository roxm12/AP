#ifndef __PTHREAD_H__
#define __PTHREAD_H__
#define NUM_OF_PTHF 3
#include<pthread.h>
#include"../arp/arpCache.h"
typedef void* (*threadFptr)(void *);
typedef enum{
	DDT_MODULE=0,
	PRINT_MODULE,
	SEARCH_MODULE,
    FILTER,
	UPDATE
}pth_type;//function Table의 각 index에 따른 함수들의 기능 정의

threadFptr funcTable[NUM_OF_PTHF];
//thread function table

void * ddtModule(void *);
void * printModule(void *);
void * searchModule(void *);
void initFuncTable();


#endif

