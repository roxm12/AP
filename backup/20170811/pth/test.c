#include <stdio.h>
#include "pth.h"
int main(){

	printf("c:create arp g:get ddt info q:quit\n");
	while(1){
		char c;
		int s;
		char *tempIp="172.24.1.146";
		deviceDescriptor *ves;
		int result;
		initFuncTable();
		printf("input:");
		scanf("%c",&c);
		getchar();
		switch(c){
			case 'c':
				setDDT();
				break;
			case 'p':
                 printDDT();
            case 'g':
				 result=searchWithIP(ves,tempIp);
				 printf("%d result\n",result);
				break;
			case 'q':
				return;

		}
	}
	return ;
}
