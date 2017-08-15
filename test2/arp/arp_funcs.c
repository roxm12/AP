#include "arpCache.h"
 /*
function: void setDDT()
arthor:정한솔 20170803
return: 
parameter:
function details:
ARP로부터 AP에 연결된 모든 호스트의 정보를 주기적으로 받고 
이에 맞춰 DDT 정보를 수정 및 갱신한다.
##arp -i wlan0 처럼 옵션을 줄 수 있다면 필요 없는 루틴이 줄어들 것이다.
*/
void setDDT(){

	FILE * arpCache;
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
				if(isMacInDDT(hwAddr)){
					if(isIpUpdate(hwAddr,ipAddr));//mac is in and ip is updatef
					else//means mac is in but ip isn't updated
						updateIP(hwAddr,ipAddr);
				}
				else insertDD(hwAddr,ipAddr);
			}
			else;//wlan0이 아닌 networkinterface는 신경 쓸 필요가 없다.
			//	printDDT(ddt);
			
			sleep(1);
		}

		rewind(arpCache);
	}
	return;
}



