#ifndef __DDT_H__
#define __DDT_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sem.h"
#include "pshm.h"
#define MAX_HOST_NUM 64
typedef struct{
	int id;
	char *ipAddr;
	char *macAddr;
	//list blockCategoryList;

}deviceDescriptor;

typedef struct{

	deviceDescriptor ddsc[MAX_HOST_NUM];
	int count;
}DDT;//deviceDescriptTable
void printDDT();
void refreshDDT(DDT *ddt);
void insertDD(char *hwAddr,char *ipAddr);
int isMacInDDT(char *hwAddr);
void initDDT();

#endif
