#include "sem.h"

int main(){

	char c;
	sem_t* sem;
	semaphore_close();
	printf("p:post w:wait o:open\n");
	while(1){
		printf("input:");
		scanf("%c",&c);
		getchar();
		switch(c){
			case 'p':			 
				semaphore_post(sem);
				break;
			case 'w':
				semaphore_wait(sem);
				break;
			case 'o':
				sem=semaphore_open();
				break;
			case 'c':
				return;
            defualt:
				break;
		}
	}
	exit(EXIT_SUCCESS);


}
