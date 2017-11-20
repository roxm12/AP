#include "sem.h"

//Semaphore functions
/*
function: sem_t* semaphore_open()
arthor:정한솔 20170730
return: sem_t* semaphore reference
parameter:
function details:
공유메모리 영역 접근을 제어하기 위한
지정된 이름의 세마포 생성 및 이에 대한 참조 반환
 */
sem_t* semaphore_open(){
    sem_t *sem;
    sem=sem_open(SEM_NAME_FOR_DDT,O_CREAT,0666,1); //O_EXCL로 하면 그 프로세스만 접근 가능
    if(sem==SEM_FAILED){
        perror("sem_open");
        return NULL;
    }
    //	printf("%ld sem_open() succeeded\n",(long)syscall(__NR_gettid));
    return sem;
}
/*
function: void semaphore_close()
arthor:정한솔 20170730
return: 
parameter:
function details:
공유메모리 영역 접근을 제어하기 위한
지정된 이름의 세마포의 해제
 */
void semaphore_close(){
    sem_unlink(SEM_NAME_FOR_DDT);
    //  printf("%ld sem_close() succeeded\n",(long)syscall(__NR_gettid));
    return;
}
/*
function: void semaphore_wait(sem_t *sem)
arthor:정한솔 20170730
return: 
parameter:sem_t *sem semaphore reference
function details:
지정된 세마포 lock
 */
void semaphore_wait(sem_t *sem){
    //wait --> decrease -->lock  w1 w2->p1 되야 w2로 critical section에 접근이 가능함.                                 
    if(sem_wait(sem) == -1){
        perror("sem_wait");
        return;
    }
    //	printf("%ld sem_wait() succeeded\n",(long)syscall(__NR_gettid));
    return;
}
/*
function: void semaphore_post(sem_t *sem)
arthor:정한솔 20170730
return: 
parameter:sem_t *sem semaphore reference
function details:
지정된 세마포 unlock
 */
void semaphore_post(sem_t *sem){
    //post -- increase --> unlock
    if(sem_post(sem) == -1){
        perror("sem_post");
        return;
    }
    //	printf("%ld sem_post() succeeded\n",(long)syscall(__NR_gettid));
    return;

}
