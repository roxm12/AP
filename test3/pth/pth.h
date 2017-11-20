#ifndef __PTHREAD_H__
#define __PTHREAD_H__
#define NUM_OF_PTHF 3

typedef void* (*threadFptr)(void *);
typedef enum{
	DDT_MODULE=0,//DDT module
	COM_MODULE,// module handing with  communication to mobile application
	UPDATE_MODULE// DB update module
}pth_type;//function Table의 각 index에 따른 함수들의 기능 정의

//thread function table

void * ddtModule(void *);
void * updateModule(void *);
void * comModule(void *);
void initFuncTable();


#endif

