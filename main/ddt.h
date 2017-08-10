#ifndef __DDT_H__
#define __DDT_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sem.h"
#include "pshm.h"
#define MAX_CATEGORY_NUM 5
#define MAX_HOST_NUM 64
typedef enum{
 PORN=0,//성인사이트
 ADS,//광고
 DRUGS,//마약
 GAMBLING,//도박
 USER_DEFINED//사용자 정의

}category;
typedef struct{
	int id;
	char *ipAddr;
	char *macAddr;
	int blockCategoryList[MAX_CATEGORY_NUM-1];
	//list blockCategoryList;

}deviceDescriptor;

typedef struct{

	deviceDescriptor ddsc[MAX_HOST_NUM];
	int count;//host number
}DDT;//deviceDescriptTable
void printDDT();
void refreshDDT(DDT *ddt);
void insertDD(char *hwAddr,char *ipAddr);
int isMacInDDT(char *hwAddr);
void initDDT();
deviceDescriptor*  searchWithIP(char *ipAddr);
#endif
