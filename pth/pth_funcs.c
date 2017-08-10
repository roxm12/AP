#include "pth.h"


void initFuncTable(){
	funcTable[DDT_MODULE]=ddtModule;
	funcTable[PRINT_MODULE]=printModule;
	funcTable[SEARCH_MODULE]=searchModule;
}


void * ddtModule(void *arg){

	setDDT();
	return NULL;
}
void * printModule(void *arg){
	printDDT();
	return NULL;
}
void * searchModule(void *arg){

	deviceDescriptor *ves;
	char *tempIP="172.24.1.105";
	ves=searchWithIP(tempIP);
	if(ves != NULL){
		printf("host of %10s  is %10s\n",ves->ipAddr,ves->macAddr);
	}
	else{
		printf("ves wrong\n");
	}
	return NULL;
}
