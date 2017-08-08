#include <stdio.h>
#include "pth.h"
int main(){

	printf("c:create arp g:get ddt info q:quit\n");
	while(1){
		pthread_t ddt_m;
		pthread_t read_m;
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
			case 'g':
				s=pthread_create(&read_m,NULL,funcTable[READ],(void*)NULL);
				if(s != 0)
					perror("thread create\n");
			//	pthread_detach(read_m);
				pthread_join(read_m,res);
				printf("Thread retunred\n");
				break;
			case 'q':
				pthread_detach(ddt_m);
				return;

		}
	}
	return ;
}
