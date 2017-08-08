#include <stdio.h>
#include "arpCache.h"
int main(){


	printf("c:create arp g:get ddt info q:quit\n");
	while(1){
		char c;
		char *addr;
		char *str="you are so beautiful";
		printf("input:");
		scanf("%c",&c);
		getchar();
		switch(c){
			case 'c':
				
				break;
			case 'g':
				break;
			case 'q':
				return;

		}
	}
	return ;
}
