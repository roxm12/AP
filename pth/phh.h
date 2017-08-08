#ifndef __PTHREAD_H__
#define __PTHREAD_H__
#define NUM_OF_PTHF 3
#include<pthread.h>
typedef void *(threadFptr)(void *);
typedef enum{

	DDT=0,
    FILTER,
	UPDATE
}pth_type;

threadFptr funcTable[NUM_OF_PTHF];



#endif

