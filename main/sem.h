#ifndef __SEM_H__
#define __SEM_H__
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SEM_NAME_FOR_DDT  "/sol_smp"

//sem_t* getSem();
sem_t* semaphore_open();
void semaphore_close();
void semaphore_wait(sem_t *sem);//decrease(lock)
void semaphore_post(sem_t *sem);//increase(unlock)

#endif
