#include "sem.h"

int main(){



	semaphore_open();
    semaphore_wait();
	printf("%ld sem_wait() succeeded \n",(long)getpid());
	exit(EXIT_SUCCESS);


}
