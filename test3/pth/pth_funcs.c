#include "pth.h"

//Thread functions
 /*
function: void initFuncTable()
arthor:정한솔 20170806
return: 
parameter:
function details:
함수 테이블의 참조 선언
*/
void initFuncTable(){
	funcTable[DDT_MODULE]=ddtModule;
	funcTable[PRINT_MODULE]=printModule;
	funcTable[SEARCH_MODULE]=searchModule;
	funcTable[FILTER_MODULE]=filterModule;
}
void * filterModule(void *arg){
     printf("filter module!\n");  
	return NULL;
}
 /*
function: void * ddtModule(void *arg)
arthor:정한솔 20170806
return: 
parameter:
function details:
 setDDT()을 thread로 실행하기 위한 Wrapper function
*/
void * ddtModule(void *arg){
	setDDT();
	return NULL;
}
 /*
function: void * ddtModule(void *arg)
arthor:정한솔 20170806
return: 
parameter:
function details:
 printDDT()을 thread로 실행하기 위한 Wrapper function
*/
void * printModule(void *arg){
	printDDT();
	return NULL;
} /*
function: void * ddtModule(void *arg)
arthor:정한솔 20170806
return: 
parameter:
function details:
 searchWithIP()을 thread로 실행하기 위한 Wrapper function
아직 임시로 만들어놓은 것임. NFQ에서 arg로 ip주소를 받아야 한다.
 ves alloc 해제해주어야 함.
*/
void * searchModule(void *arg){

	deviceDescriptor *ves;
	char *tempIP="172.24.1.105";
	if(searchWithIP(ves,tempIP)){
		printf("host of %10s  is %10s\n",ves->ipAddr,ves->macAddr);
	}
	else{
		printf("ves wrong\n");
	}
	return NULL;
}
