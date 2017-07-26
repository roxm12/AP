#include <stdio.h>
#define xstr(s) str(s)
#define str(s) #s
#define ARP_CACHE       "/proc/net/arp"
#define ARP_STRING_LEN  1023
#define ARP_BUFFER_LEN  (ARP_STRING_LEN + 1)
#define MAX_HOST_NUM 1024

/* Format for fscanf() to read the 1st, 4th, and 6th space-delimited fields */
/*%1024s*/ 

#define ARP_LINE_FORMAT "%" xstr(ARP_STRING_LEN) "s %*s %*s "\                     
                        "%" xstr(ARP_STRING_LEN) "s %*s " \
                        "%" xstr(ARP_STRING_LEN) "s"
static char *macCache[10];
static int macCacheCount=0;
int main(){

    	
	while(1){
	FILE *arpCache = fopen(ARP_CACHE, "r");
    if (!arpCache) {
        perror("Arp Cache: Failed to open file \"" ARP_CACHE "\"");
        return 1;
    }
    /* Ignore the first line, which contains the header */
    char header[ARP_BUFFER_LEN];
    if (!fgets(header, sizeof(header), arpCache));
    
	//puts(header);

    char ipAddr[ARP_BUFFER_LEN], hwAddr[ARP_BUFFER_LEN], device[ARP_BUFFER_LEN];
    int count = 0;
	int flag=0;
    while (3 == fscanf(arpCache, ARP_LINE_FORMAT, ipAddr, hwAddr, device)) {
		int i;
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
                   
	fclose(arpCache);
	sleep(1);
  }
    
    return 0;
}
