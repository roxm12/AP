#include "sem.h"


int main(){
    sem_t *sem;
	sem=sem_open(SEM_NAME,O_CREAT,0666,1);
	if(sem==SEM_FAILED)
		perror("sem_open");
	exit(EXIT_SUCCESS);


}
