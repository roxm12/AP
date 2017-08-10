#include <stdio.h>
#include "pth.h"
int main(){

	printf("c: create arp g:get ddt info p:print ddt  q:quit\n");
	while(1){
		pthread_t ddt_m;
		pthread_t search_m;
		pthread_t print_m;
		char c;
		int s;
		void *res;
		initFuncTable();
		printf("input:");
		scanf("%c",&c);
		getchar();
		switch(c){
			case 'c':
				s=pthread_create(&ddt_m,NULL,funcTable[DDT_MODULE],(void*)NULL);
				if(s != 0)
					perror("pthread create\n");
				break;
			case 'p':
				s=pthread_create(&print_m,NULL,funcTable[PRINT_MODULE],(void*)NULL);
				pthread_join(print_m,res);
				break;
			case 'g':
				s=pthread_create(&search_m,NULL,funcTable[SEARCH_MODULE],(void*)NULL);
				if(s != 0)
					perror("thread create\n");
			//	pthread_detach(read_m);
				pthread_join(search_m,res);
				break;
			case 'q':
				pthread_detach(ddt_m);
				return;

		}
	}
	return ;
}
