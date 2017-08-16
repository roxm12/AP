#include "ddt.h"
//DeviceDescriptTable functions
//각 함수들의 루틴들이 중복되는 작업이 많으므로 성능 향상을 위해서 이를 줄인다.(20170810)
/*
function: void refreshDDT(DDT *ddt)
arthor:정한솔 20170803
return: 
parameter: DDT* ddt DDT reference to refresh
function details:
DDT가 가득찬 경우 접속하지 않은 host들을 제거하기 위해 refresh 한다.
 */
void refreshDDT(DDT *ddt){//strdup으로 할당한 M 을 다 해제해주어야 한다.
	int i;
	for(i=0;i<ddt->count;i++){
		free(ddt->ddsc[i]->macAddr);
		free(ddt->ddsc[i]);
	}
	memset(ddt,0,sizeof(DDT));
}
/*
function: void printDDT()
arthor:정한솔 20170803
return: 
parameter: 
function details:
print all contentsof DDT
 */
void printDDT(){

	int i;sem_t *sem;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_read();
	for(i=0;i<ddt->count;i++){
		printf("Host[%d] ipAddress:%10s  macAddress:%10s\n"
				,i,inet_ntoa(ddt->ddsc[i]->ipAddr),ddt->ddsc[i]->macAddr);
	}
	semaphore_post(sem);
}
/*
function: void insertDD(char * hwAddr,char * ipAddr)
arthor:정한솔 20170803
return: 
parameter: char *hwAddr MAC 주소 /char* ipAddr IP 주소
function details:
DDT에 해당 MAC 주소, IP 주소의 호스트 정보 삽입
 */
void insertDD(char * hwAddr,char * ipAddr){

	sem_t *sem;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_write();
	ddt->ddsc[ddt->count]=(deviceDescriptor*)malloc(sizeof(deviceDescriptor));
	memset(ddt->ddsc[ddt->count]->blockCategoryList,0,
			sizeof(ddt->ddsc[ddt->count]->blockCategoryList));
	inet_aton(ipAddr, &(ddt->ddsc[ddt->count]->ipAddr));

	ddt->ddsc[ddt->count++]->macAddr=strdup(hwAddr);
	if(ddt->count>MAX_HOST_NUM)//다른 것을 생각해야 함.
		refreshDDT(ddt);

semaphore_post(sem);
}
/*
function: void deleteDDT(char *hwAddr)
arthor:정한솔 20170803
return: 
parameter: char *hwAddr MAC 주소
function details:
DDT에 해당 MAC 주소의 호스트 정보 삭제
 */
void deleteDDT(char *hwAddr){

	sem_t *sem;int i;int j;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_write();
	for(i=0;i<ddt->count;i++){

		if(!strcmp(ddt->ddsc[i]->macAddr,hwAddr)){
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
/*
function: void insertDD(char * hwAddr,char * ipAddr)
arthor:정한솔 20170803
return: 
parameter: char *hwAddr MAC 주소 /char* ipAddr 갱신해야 할 IP 주소
function details:
DDT에 해당 MAC 주소를 갖는 호스트의 IP주소를 새로 할당된 새로운 IP 주소로 갱신
 */
void updateIP(char *hwAddr, char *ipAddr){

	sem_t *sem;int i;
	sem=(sem_t*)semaphore_open();
	printf("update ..\n");
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_write();
	for(i=0;i<ddt->count;i++){
		if(!strcmp(ddt->ddsc[i]->macAddr,hwAddr)){
			/*
			   if(!inet_aton(ipAddr,&(ddt->ddssc[i]->ipAddr))){
			   perror("wrong ip address format\n");
			   break;
			   }else break;*/
			inet_aton(ipAddr,&(ddt->ddsc[i]->ipAddr));
		}
	}
	semaphore_post(sem);
	return;
}
/*
function: void regDDT(char *hwAddr,int blockList[])
arthor:정한솔 20170804
return: 
parameter: char *hwAddr MAC 주소 int blockList[] 차단카테고리리스트
function details:
DDT에 새로운 호스트의 MAC 주소와 차단카테고리리스트 정보 등록
 */
void updateBL(char *hwAddr, int blockList[]){
	sem_t *sem;int i;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_write();
	for(i=0;i<ddt->count;i++){
		if(!strcmp(ddt->ddsc[i]->macAddr,hwAddr))
	memcpy(ddt->ddsc[i]->blockCategoryList,
			blockList,sizeof(ddt->ddsc[i]->blockCategoryList));
	}
	semaphore_post(sem);
}
void regDDT(char *hwAddr,int blockList[]){
	sem_t *sem;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_write();
	ddt->ddsc[ddt->count]=(deviceDescriptor*)malloc(sizeof(deviceDescriptor));
	memcpy(ddt->ddsc[ddt->count]->blockCategoryList,
			blockList,sizeof(ddt->ddsc[ddt->count]->blockCategoryList));
	inet_aton("0.0.0.0",&(ddt->ddsc[ddt->count]->ipAddr));
	ddt->ddsc[ddt->count++]->macAddr=strdup(hwAddr);
	semaphore_post(sem);
}
/*
function: isIpUpdate(char *hwAddr, char *ipAddr)
arthor:정한솔 20170804
return: 
parameter: char *hwAddr MAC 주소 char *ipAddr IP 주소
function details:
해당 호스트에 DHCP가 할당한 IP가 변경되었는지 확인.
 */
int isIpUpdate(char *hwAddr, char *ipAddr){
	sem_t *sem;int i,flag=0;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_read();
	for(i=0;i<ddt->count;i++){
		if(!strcmp(ddt->ddsc[i]->macAddr,hwAddr)){
			if(!strcmp(inet_ntoa(ddt->ddsc[i]->ipAddr),ipAddr))
				flag=1;//ip가  update 되어있는 경우는 1을 반환한다.
			else;
			break;
		}
	}
	semaphore_post(sem);
	return flag;
}
/*
function: isMacInDDT(char * hwAddr)
arthor:정한솔 20170804
return: 
parameter: char *hwAddr MAC 주소
function details:
해당 MAC 주소의 host가 DDT 내에 있는지 확인
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
/*
function: void initDDT()
arthor:정한솔 20170803
return: 
parameter: 
function details:
DDT(공유메모리 객체 생성)
 */
void initDDT(){
	shmemory_close();
	semaphore_close();
	if(shmemory_open()== 1)
		printf("shm success\n");
	else printf("shm failed\n");
}

/*
function: deviceDescriptor*  searchWithIP(char *ipAddr)
arthor:정한솔 20170804
return: deviceDescriptor* 호스트(device)의 정보(ip,MAC,blocklist)반환한다.
parameter: char *ipAddr IP 주소
function details:
해당 사설 IP를 갖는 호스트의 정보를 반환
 */
deviceDescriptor*  searchWithIP(char *ipAddr){

	int i;sem_t *sem;
	deviceDescriptor *ves=NULL;
	sem=(sem_t*)semaphore_open();
	semaphore_wait(sem);
	DDT *ddt=(DDT*)shmemory_read();
	for(i=0;i<ddt->count;i++){
		if(!strcmp(inet_ntoa(ddt->ddsc[i]->ipAddr),ipAddr)){
			ves=(deviceDescriptor*)malloc(sizeof(deviceDescriptor));
			ves->ipAddr=ddt->ddsc[i]->ipAddr;
			ves->macAddr=strdup(ddt->ddsc[i]->macAddr);
			memcpy(ves->blockCategoryList,ddt->ddsc[i]->blockCategoryList
					,sizeof(ves->blockCategoryList));
			break;
		}
	}
	semaphore_post(sem);
	return ves;
}
