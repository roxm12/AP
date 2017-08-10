#include "ddt.h"
/*
   refrsehDDT
description:
DDT가 가득찬 경우 접속하지 않은 host들을 제거하기 위해 refresh 한다.
parameter:
갱신해야 하는 DDT의 주소

 */
void refreshDDT(DDT *ddt){//strdup으로 할당한 M 을 다 해제해주어야 한다.
	int i;
	for(i=0;i<ddt->count;i++){
		free(ddt->ddsc[i]->macAddr);
		free(ddt->ddsc[i]->ipAddr);
		free(ddt->ddsc[i]);
	}
	memset(ddt,0,sizeof(DDT));
}
/*
   DDT 내용 전부 출력
 */
void printDDT(){

	int i;sem_t *sem;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_read();
	for(i=0;i<ddt->count;i++){
		printf("Host[%d] ipAddress:%10s  macAddress:%10s\n"
				,i,ddt->ddsc[i]->ipAddr,ddt->ddsc[i]->macAddr);
	}
	semaphore_post(sem);
}
/*
   DeviceDescriptor insert 한다.
 */
void insertDD(char * hwAddr,char * ipAddr){

	sem_t *sem;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_write();
	ddt->ddsc[ddt->count]=(deviceDescriptor*)malloc(sizeof(deviceDescriptor));
	memset(ddt->ddsc[ddt->count]->blockCategoryList,0,
			sizeof(ddt->ddsc[ddt->count]->blockCategoryList));
	ddt->ddsc[ddt->count]->macAddr=strdup(hwAddr);
	ddt->ddsc[ddt->count++]->ipAddr=strdup(ipAddr);
	if(ddt->count>MAX_HOST_NUM)//다른 것을 생각해야 함.
		refreshDDT(ddt);
	semaphore_post(sem);
}
/**
 */
void deleteDDT(char *hwAddr){

	sem_t *sem;int i;int j;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_write();
	for(i=0;i<ddt->count;i++){

		if(!strcmp(ddt->ddsc[i]->macAddr,hwAddr)){
			free(ddt->ddsc[i]->ipAddr);
			free(ddt->ddsc[i]->macAddr);
			free(ddt->ddsc[i]);
			for(j=i+1;j<ddt->count;j++){
				ddt->ddsc[j-1]=ddt->ddsc[j];
			}
			ddt->count--;
		}
	}
	semaphore_post(sem);
}
void updateIP(char *hwAddr, char *ipAddr){

	sem_t *sem;int i;
	sem=(sem_t*)semaphore_open();
	printf("update ..\n");
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_write();
	for(i=0;i<ddt->count;i++){
		if(!strcmp(ddt->ddsc[i]->macAddr,hwAddr)){
			ddt->ddsc[i]->ipAddr=strdup(ipAddr);
			break;
		}
	}
	semaphore_post(sem);
	return;
}
void regDDT(char *hwAddr,int blockList[]){
	sem_t *sem;int i;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_write();
	ddt->ddsc[ddt->count]=(deviceDescriptor*)malloc(sizeof(deviceDescriptor));
	memcpy(ddt->ddsc[ddt->count]->blockCategoryList,
			blockList,sizeof(ddt->ddsc[ddt->count]->blockCategoryList));
	ddt->ddsc[ddt->count]->macAddr=strdup(hwAddr);
	ddt->ddsc[ddt->count++]->ipAddr=strdup("not allowcated");
	semaphore_post(sem);

}
int isIpUpdate(char *hwAddr, char *ipAddr){

	sem_t *sem;int i,flag=0;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_read();
	for(i=0;i<ddt->count;i++){
		if(!strcmp(ddt->ddsc[i]->macAddr,hwAddr)){
			if(!strcmp(ddt->ddsc[i]->ipAddr,ipAddr))
				flag=1;//ip가  update 되어있는 경우는 1을 반환한다.
			else;
			break;
		}
	}
	semaphore_post(sem);
	return flag;
}
/*
   hwAddr(MAC 주소)가 DDT에 있는지 확인

 */
int isMacInDDT(char * hwAddr){

	sem_t *sem;int i;int flag=0;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_read();
	//	memset(ddt,0,sizeof(deviceDescriptTable));
	for(i=0;i<ddt->count;i++){
		if(!strcmp(ddt->ddsc[i]->macAddr,hwAddr)){
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
/*
   해당 사설 ip를 갖는 device 정보를 return 한다.
 */
deviceDescriptor*  searchWithIP(char *ipAddr){

	int i;sem_t *sem;
	deviceDescriptor *ves=NULL;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_read();
	for(i=0;i<ddt->count;i++){
		if(!strcmp(ddt->ddsc[i]->ipAddr,ipAddr)){
			ves=(deviceDescriptor*)malloc(sizeof(deviceDescriptor));
			ves->ipAddr=strdup(ddt->ddsc[i]->ipAddr);
			ves->macAddr=strdup(ddt->ddsc[i]->macAddr);
			memcpy(ves->blockCategoryList,ddt->ddsc[i]->blockCategoryList
					,sizeof(ves->blockCategoryList));
			break;
		}
	}
	semaphore_post(sem);
	return ves;
}
