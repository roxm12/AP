
#include "pshm.h"
#include "sem.h"
#include "arpCache.h"
#include "sem.h"
#include <string.h>
#include <unistd.h>
int shmemory_open(){
	int fd;
	char *addr;
	fd=shm_open(SHM_NAME,O_RDWR | O_CREAT,0666);
	if(fd == -1){
		perror("shm_open");
		return -1;
	}
	if(ftruncate(fd,MMAP_SIZE) == -1){
		perror("ftruncate");
		return -1;
	}

	//shm mapping

	addr=mmap(NULL,MMAP_SIZE,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
	if(addr==MAP_FAILED){
		perror("mmap");
		return -1;
	}
	if(close(fd) == -1){
	perror("close");
	return -1;
	}

	return 1;
}

void shmemory_close(){

	if(shm_unlink(SHM_NAME) == -1)
		perror("shm_unlink");
	return;
}
void shmemory_write(char *str){
	sem_t * sem;
	int fd;
	size_t len;
	char *addr;
    sem=semaphore_open();
    semaphore_wait(sem);
	len=strlen(str);
	fd=shm_open(SHM_NAME,O_RDWR,0);
	if(fd == -1){
		perror("shm_openW");
		return;
	}
	if(ftruncate(fd,len) == -1){
		perror("ftruncateW");
		return;
	}
	addr=mmap(NULL,len,PROT_READ | PROT_WRITE, MAP_SHARED, fd ,0);
	if(addr==MAP_FAILED){
		perror("mmapW");
		return;
	}
	printf("Resized to %ld bytes \n",(long)len);
	if(close(fd) == -1)
		perror("close fd");
	sprintf(addr,"%s is to shm\n",str);
	printf("copying %ld bytes\n",strlen(addr));
    semaphore_post(sem);
			return;
}
void shmemory_read(){
	 sem_t *sem;
	 int fd;
	 char *addr;
	 struct stat sb;
	 sem=semaphore_open();
      semaphore_wait(sem);
	 fd=shm_open(SHM_NAME,O_RDONLY,0);
     if(fd == -1){
	  perror("shm_openR");
	  return;
	  }
	 if(fstat(fd,&sb) == -1){
	  perror("fstat");
	  return;
	 }
	 addr=mmap(NULL,sb.st_size,PROT_READ,MAP_SHARED,fd,0);
	 if(addr == MAP_FAILED){
	  perror("mmap");
	  return;
	 }
	 write(STDOUT_FILENO,addr,sb.st_size);
	 printf("\n");
     semaphore_post(sem);
	 return;
}


