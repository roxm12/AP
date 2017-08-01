#include "arpCache.h"


static deviceDescriptTable ddt;
/*
int isModify(){

  return ;
}*/
void refreshDDT(){//strdup으로 할당한 M 을 다 해제해주어야 한다.
	int i;
	for(i=0;i<ddt.count;i++){
		free(ddt.ddsc[i].macAddr);
		free(ddt.ddsc[i].ipAddr);
	}
	memset(getDDT(),0,sizeof(deviceDescriptTable));
}

void printDDT(){
	int i;
	for(i=0;i<ddt.count;i++){
       printf("Host[%d] ipAddress:%10s  macAddress:%10s\n"
	   ,ddt.ddsc[i].id,ddt.ddsc[i].ipAddr,ddt.ddsc[i].macAddr);
			           

	}
}
/* insert와 getDDT delete등에 대해서 lock unlock이 필요하다.i*/
void insertDD(char * hwAddr,char * ipAddr){

	ddt.ddsc[ddt.count].macAddr=strdup(hwAddr);
	ddt.ddsc[ddt.count].id=ddt.count;
	ddt.ddsc[ddt.count++].ipAddr=strdup(ipAddr);
	if(ddt.count>MAX_HOST_NUM)
		refreshDDT();
}

/*Wrapper func of ddt address*/
deviceDescriptTable* getDDT(){

return &ddt;
}
