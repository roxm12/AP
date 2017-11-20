#include "arpCache.h"

void setDDT(){


	DDT *ddt;
	FILE * arpCache;
		initDDT();
	arpCache=fopen(ARP_CACHE,"r");
	if(arpCache == NULL){
		perror("Arp Cache: Failed to open file \"" ARP_CACHE "\"");
		return;
	}
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
				flag=isMacInDDT(hwAddr);
				if(flag ==0)
					insertDD(hwAddr,ipAddr);
			}
			else;//wlan0이 아닌 networkinterface는 신경 쓸 필요가 없다.
		}
	//	printDDT(ddt);
		rewind(arpCache);
		sleep(1);
	}
	return;
}

