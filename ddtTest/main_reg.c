#include <stdio.h>
#include "pth.h"
int main(){
    char *tempMac="24:2f:6a:e9:35:89";
	char *tempIP="172.24.1.105";
	int blocklist[MAX_CATEGORY_NUM]={0,0,0,0,0};
	initDDT();
	regDDT(tempMac,blocklist);
//	updateIP(tempIP,tempMac);
//	printDDT();
//	printf("deleteing..\n");
//	deleteDDT(tempMac);
//	printDDT();
	return 0;
}
