#include "pth.h"


void initFuncTable(){
	funcTable[DDT_MODULE]=ddtModule;
	funcTable[READ]=shmreadModule;
	funcTable[FIND_DD]=findDDModule;
}


void * ddtModule(void *arg){

	setDDT();
	return (void*) NULL;

}
void * shmreadModule(void *arg){

	printDDT();
	return (void*) NULL;

}
void * findDDModule(void *ipAddr){
          
	deviceDescriptor *ves;
        if(searchWithIP(ves,(char*)ipAddr) == 0){
			printf("No such ip address\n");
			return (void*) 0;
		}
		else {
			printf("Host[%d] of ipAddress:%10s macAddress:%10s\n",
					ves->id,ves->ipAddr,ves->macAddr);
			free(ves->ipAddr);
			free(ves->macAddr);
			free(ves);
			return (void*) 1;
		}
}
