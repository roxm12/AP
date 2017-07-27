#include "arpCache.h"

/*
   Wrapper print function for static var ddt
 */
void printDDT(){
	int i;
	for(i=0;i<ddt.count;i++){
       printf("Host[%d] ipAddress:%10s  macAddress:%10s\n"
	   ,ddt.ddsc[i].id,ddt.ddsc[i].ipAddr,ddt.ddsc[i].macAddr);
			           

	}
}
