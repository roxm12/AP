#include "sem.h"



sem_t* semaphore_open(){
    sem_t *sem;
	sem=sem_open(SEM_NAME_FOR_DDT,O_CREAT,0666,1); //O_EXCL로 하면 그 프로세스만 접근 가능
	if(sem==SEM_FAILED){
		perror("sem_open");
		return NULL;
	}
	printf("%ld sem_open() succeeded\n",(long)getpid());
	return sem;
}
void semaphore_close(){
   sem_unlink(SEM_NAME_FOR_DDT);
   printf("%ld sem_close() succeeded\n",(long)getpid());
   return;
}


//wait --> decrease -->lock  w1 w2->p1 되야 w2로 critical section에 접근이 가능함.
void semaphore_wait(sem_t* sem){
                                 
	if(sem_wait(sem) == -1){
		perror("sem_wait");
		return;
	}
	printf("%ld sem_wait() succeeded\n",(long)getpid());
	return;
}
//post -- increase --> unlock
void semaphore_post(sem_t *sem){

	if(sem_post(sem) == -1){
		perror("sem_post");
		return;
	}
	printf("%ld sem_post() succeeded\n",(long)getpid());
	return;

}
