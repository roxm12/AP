#include "arpCache.h"

int main(void){
   	
	FILE *arpCache = fopen(ARP_CACHE, "r");
	while(1){
    if (!arpCache) {
        perror("Arp Cache: Failed to open file \"" ARP_CACHE "\"");
        return 1;
    }
    /* Ignore the first line, which contains the header */
    char header[ARP_BUFFER_LEN];
    if (!fgets(header, sizeof(header), arpCache));
    char ipAddr[ARP_BUFFER_LEN], hwAddr[ARP_BUFFER_LEN], device[ARP_BUFFER_LEN];
    int count = 0;
	int flag=0;
    while (3 == fscanf(arpCache, ARP_LINE_FORMAT, ipAddr, hwAddr, device)) {
		int i;
		if(!strcmp(device,N_INTERFACE)){
		printf("%03d: Mac Address of [%s] on [%s] is \"%s\"\n",
                ++count, ipAddr, device, hwAddr);
          for(i=0;i<macCacheCount;i++){
		    if(!strcmp(macCache[i],hwAddr)){
			flag=1;
			}
		  }
		  if(flag==0){
          macCache[macCacheCount]=strdup(hwAddr);         
          macCacheCount++;
		}
		}
	else;
   }
    rewind(arpCache);               
	sleep(1);
  }
    
	fclose(arpCache);
    return 0;
}
