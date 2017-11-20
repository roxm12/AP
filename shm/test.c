#include <stdio.h>
#include "sem.h"
#include "pshm.h"
int main(){


	printf("c:create u:unlink w:write r:read q:quit\n");
	while(1){
		char c;
		char *addr;
		char *str="you are so beautiful";
		printf("input:");
		scanf("%c",&c);
		getchar();
		switch(c){
			case 'c':
				shmemory_open(addr);
				break;
			case 'u':
				shmemory_close();
				break;
			case 'w':
				shmemory_write(str);
				break;
			case 'r':
				shmemory_read();
				break;
			case 'q':
				return;

		}
	}
	return ;
}
