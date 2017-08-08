#include "pth.h"


void initFuncTable(){
	funcTable[DDT_MODULE]=ddtModule;
	funcTable[READ]=shmreadModule;
}


void * ddtModule(void *arg){

	setDDT();

}
void * shmreadModule(void *arg){

	printDDT();

}
