#include "ddt.h"
#include "sem.h"
#include "pshm.h"

void refreshDDT(DDT *ddt){//strdup으로 할당한 M 을 다 해제해주어야 한다.
	int i;
	for(i=0;i<ddt->count;i++){
		free(ddt->ddsc[i].macAddr);
		free(ddt->ddsc[i].ipAddr);
	}
	memset(ddt,0,sizeof(deviceDescriptTable));
}

void printDDT(){

	int i;sem_t *sem;
 	sem=(sem_t*)semaphore_open();
	sem_wait(sem);
	DDT* ddt=(DDT*)shmemory_read();
	for(i=0;i<ddt->count;i++){
		printf("Host[%d] ipAddress:%10s  macAddress:%10s\n"
				,ddt->ddsc[i].id,ddt->ddsc[i].ipAddr,ddt->ddsc[i].macAddr);
	}
	sem_post(sem);
}
/* insert와 getDDT delete등에 대해서 lock unlock이 필요하다.i*/
void insertDD(char * hwAddr,char * ipAddr){

	sem_t *sem;
    sem=(sem_t*)semaphore_open();
    sem_wait(sem);
	DDT* ddt=(DDT*)shmemory_write();
	ddt->ddsc[ddt->count].macAddr=strdup(hwAddr);
	ddt->ddsc[ddt->count].id=ddt->count;
	ddt->ddsc[ddt->count++].ipAddr=strdup(ipAddr);
	if(ddt->count>MAX_HOST_NUM)
		refreshDDT(ddt);
    sem_post(sem);
}
int isMacInDDT(char * hwAddr){

	sem_t *sem;int i;int flag=0;
    sem=(sem_t*)semaphore_open();
    sem_wait(sem);
	DDT* ddt=(DDT*)shmemory_read();
//	memset(ddt,0,sizeof(deviceDescriptTable));
    for(i=0;i<ddt->count;i++){
		if(!strcmp(ddt->ddsc[i].macAddr,hwAddr)){
			flag=1;
			break;
		}
	}
    semaphore_post(sem);
	return flag;
}

void initDDT(){
	shmemory_close();
	semaphore_close();
	if(shmemory_open()== 1)
     printf("shm success\n");
	else printf("shm failed\n");
}
