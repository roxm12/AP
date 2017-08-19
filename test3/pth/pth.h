#ifndef __PTHREAD_H__
#define __PTHREAD_H__
#define NUM_OF_PTHF 8
#include<pthread.h>
#include"../ddt/ddt.h"
typedef void* (*threadFptr)(void *);
typedef enum{
	DDT_MODULE=0,//DDT module
	DDT_PRINT_MODULE,// ddt print module
	DDT_SEARCH_MODULE,// ddt searh module
    FILTER_MODULE,// filter module
	FILTER_SEARCH_MODULE,
	FILTER_UPDATE_MODULE,
	COM_MODULE,// module handing with  communication to mobile application
	UPDATE_MODULE// DB update module
}pth_type;//function Table의 각 index에 따른 함수들의 기능 정의

threadFptr funcTable[NUM_OF_PTHF];
//thread function table

void * filterModule(void *);
void * ddtModule(void *);
void * ddt_printModule(void *);
void * ddt_searchModule(void *);
void * filter_searchModule(void *);
void * filter_updateModule(void *);
void * comModule(void *);
void initFuncTable();


#endif

