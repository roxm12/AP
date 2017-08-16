#ifndef __DDT_H__
#define __DDT_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "../pshm/pshm.h"
#include "../sem/sem.h"
#define MAX_CATEGORY_NUM 5
#define MAX_HOST_NUM 64
typedef enum{
 PORN=0,//성인사이트
 ADS,//광고
 DRUGS,//마약
 GAMBLING,//도박
 USER_DEFINED//사용자 정의

}category;
/*
name: deviceDescriptor
details: AP에 연결된 호스트(디바이스)의 정보를 저장
field:
char *ipAddr - IP주소
char *macAddr - MAC 주소
int blockCategoryList[MAX_CATEGORY_NUM] - 호스트에 적용된 차단정책 정보
*/
typedef struct{
	struct in_addr ipAddr;
	char *macAddr;
	int blockCategoryList[MAX_CATEGORY_NUM];
	//list blockCategoryList;

}deviceDescriptor;
/*
name: DDT(DeviceDescriptorTable)
details: AP에 등록된 모든호스트(디바이스)의 정보를 저장
field:
deviceDescriptor* ddsc[MAX_HOST_NUM] - 모든 호스트의 정보들을 참조하는 테이블
int count - 등록된 호스트의 수
*/
typedef struct{

	deviceDescriptor* ddsc[MAX_HOST_NUM];
	int count;//host number
}DDT;//deviceDescriptTable
//pthread_rwlock_t rwlock;
void printDDT();
void refreshDDT(DDT *ddt);
void insertDD(char *hwAddr,char *ipAddr);
int isIpUpdate(char *hwaddr, char *ipAddr);
int isMacInDDT(char *hwAddr);
void initDDT();
void deleteDDT(char *hwAddr);
void regDDT(char *hwAddr, int categoryList[]);
void updateIP(char *hwAddr,char *ipAddr);
int searchWithIP(deviceDescriptor *ves,char *ipAddr);
void updateBL(char *hwAddr ,int categoryList[]);
#endif
