#include "ddt.h"
#include "arpCache.h"
//DeviceDescriptTable functions
//각 함수들의 루틴들이 중복되는 작업이 많으므로 성능 향상을 위해서 이를 줄인다.(20170810)


/*
function: void setDDT()
arthor:정한솔 20170803
return: 
parameter:
function details:
ARP로부터 AP에 연결된 모든 호스트의 정보를 주기적으로 받고 
이에 맞춰 DDT 정보를 수정 및 갱신한다.
##arp -i wlan0 처럼 옵션을 줄 수 있다면 필요 없는 루틴이 줄어들 것이다.
 */
void setDDT(){

	FILE * arpCache;
	arpCache=fopen(ARP_CACHE,"r");
	if(arpCache == NULL){
		perror("Arp Cache: Failed to open file \"" ARP_CACHE "\"");
		return;
	}
	//	initDDT();
	while(1){
		char header[ARP_BUFFER_LEN];
		if(!fgets(header,sizeof(header),arpCache));
		//arp 프로그램의  출력 중에  header는 제거.
		// hwAddr-->MAC device --> network interface
		char ipAddr[ARP_BUFFER_LEN], hwAddr[ARP_BUFFER_LEN], device[ARP_BUFFER_LEN];
		int count=0;
		int flag=0;
		while(3 == fscanf(arpCache, ARP_LINE_FORMAT, ipAddr, hwAddr, device)){

			if(!strcmp(device,N_INTERFACE)){//wlan0인 경우에만 DDT에 저장한다.
				if(isMacInDDT(hwAddr)){
					if(isIpUpdate(hwAddr,ipAddr));//mac is in and ip is updatef
					else{//means mac is in but ip isn't updated
						updateIP(hwAddr,ipAddr);
					}
				}
				else {
					insertDD(hwAddr,ipAddr);
				}
			}
			else;//wlan0이 아닌 networkinterface는 신경 쓸 필요가 없다.
			//	printDDT(ddt);

			sleep(1);
		}

		rewind(arpCache);
	}
	return;
}

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

	pthread_rwlock_rdlock(&rwlock);
	int i;
	DDT *ddt=(DDT*)shmemory_read();
	for(i=0;i<ddt->count;i++){
		printf("Host[%d] ipAddress:%10s  macAddress:%10s\n"
				,i,inet_ntoa(ddt->ddsc[i]->ipAddr),ddt->ddsc[i]->macAddr);
	}
	pthread_rwlock_unlock(&rwlock);
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

	pthread_rwlock_wrlock(&rwlock);
	DDT *ddt=(DDT*)shmemory_write();
	ddt->ddsc[ddt->count]=(deviceDescriptor*)malloc(sizeof(deviceDescriptor));
	memset(ddt->ddsc[ddt->count]->blockCategoryList,0,
			sizeof(ddt->ddsc[ddt->count]->blockCategoryList));
	inet_aton(ipAddr, &(ddt->ddsc[ddt->count]->ipAddr));

	ddt->ddsc[ddt->count++]->macAddr=strdup(hwAddr);
	if(ddt->count>MAX_HOST_NUM)//다른 것을 생각해야 함.
		refreshDDT(ddt);

	pthread_rwlock_unlock(&rwlock);
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

	int i;int j;
	pthread_rwlock_wrlock(&rwlock);
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
	pthread_rwlock_unlock(&rwlock);
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

	int i;
	printf("update ..\n");
	pthread_rwlock_wrlock(&rwlock);
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
	pthread_rwlock_unlock(&rwlock);
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
	int i;
	pthread_rwlock_wrlock(&rwlock);
	DDT *ddt=(DDT*)shmemory_write();
	for(i=0;i<ddt->count;i++){
		if(!strcmp(ddt->ddsc[i]->macAddr,hwAddr))
			memcpy(ddt->ddsc[i]->blockCategoryList,
					blockList,sizeof(ddt->ddsc[i]->blockCategoryList));
	}
	pthread_rwlock_unlock(&rwlock);
}
void regDDT(char *hwAddr,int blockList[]){
	pthread_rwlock_wrlock(&rwlock);
	DDT *ddt=(DDT*)shmemory_write();
	if(ddt->count>MAX_HOST_NUM){
		perror("max host number\n");
		return;
	}
	ddt->ddsc[ddt->count]=(deviceDescriptor*)malloc(sizeof(deviceDescriptor));
	memcpy(ddt->ddsc[ddt->count]->blockCategoryList,
			blockList,sizeof(ddt->ddsc[ddt->count]->blockCategoryList));
	inet_aton("0.0.0.0",&(ddt->ddsc[ddt->count]->ipAddr));
	ddt->ddsc[ddt->count++]->macAddr=strdup(hwAddr);
	pthread_rwlock_unlock(&rwlock);
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
	int i,flag=0;
	pthread_rwlock_rdlock(&rwlock);
	DDT *ddt=(DDT*)shmemory_read();
	for(i=0;i<ddt->count;i++){
		if(!strcmp(ddt->ddsc[i]->macAddr,hwAddr)){
			if(!strcmp(inet_ntoa(ddt->ddsc[i]->ipAddr),ipAddr))
				flag=1;//ip가  update 되어있는 경우는 1을 반환한다.
			else;
			break;
		}
	}
	pthread_rwlock_unlock(&rwlock);
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

	int i;int flag=0;
	pthread_rwlock_rdlock(&rwlock);
	DDT *ddt=(DDT*)shmemory_read();
	//	memset(ddt,0,sizeof(deviceDescriptTable));
	for(i=0;i<ddt->count;i++){
		if(!strcmp(ddt->ddsc[i]->macAddr,hwAddr)){
			flag=1;
			break;
		}
	}
	pthread_rwlock_unlock(&rwlock);
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
	if(pthread_rwlock_init(&rwlock,NULL)!=0){
		perror("rwlock_init error");
	}
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
int searchWithIP(deviceDescriptor *ves, char *ipAddr){

	int i;int flag=0;
	pthread_rwlock_rdlock(&rwlock);
	DDT *ddt=(DDT*)shmemory_read();
	struct in_addr tempIp;
	ves=NULL;
	inet_aton(ipAddr,&tempIp);
	for(i=0;i<ddt->count;i++){
		if(ddt->ddsc[i]->ipAddr.s_addr == tempIp.s_addr){//ip가 있다면 DD 반환
			ves=(deviceDescriptor*)malloc(sizeof(deviceDescriptor));
			ves->ipAddr=ddt->ddsc[i]->ipAddr;
			ves->macAddr=strdup(ddt->ddsc[i]->macAddr);
			memcpy(ves->blockCategoryList,ddt->ddsc[i]->blockCategoryList
					,sizeof(ves->blockCategoryList));
			flag=1;
			break;
		}
	}
	pthread_rwlock_unlock(&rwlock);
	return flag;
}
