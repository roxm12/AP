#include "pshm.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/////Sharedmemory functions

/*
function: int shemory_open()
arthor:정한솔 20170801
return: 
 1-- 공유메모리 객체 생성 성공
-1-- 공유메모리 객체 생성 실패
parameter:
function details:
공유메모리 객체(for DeciceDescriptTable)를 생성
*/
int shmemory_open(){
	int fd;
	 DDT *addr;
	fd=shm_open(SHM_NAME,O_RDWR | O_CREAT,0666);//초기값으로 매모리 객체의 길이=0
	if(fd == -1){
		perror("shm_open");
		return -1;
	}
	if(ftruncate(fd,MMAP_SIZE) == -1){//mmap 이전에 객체의 크기를 설정하기 위함.
		perror("ftruncate");
		return -1;
	}

    //shm mapping
	addr=(DDT*)mmap(NULL, sizeof(DDT),PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
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
/*
function: void shmemory_close()
arthor:정한솔 20170801
return: 
parameter:
function details:
공유메모리 영역(for DeciceDescriptTable) 해제
*/
void shmemory_close(){

	if(shm_unlink(SHM_NAME) == -1)
		perror("shm_unlink");
	return;
}
/*
function: void* shmemory_write()
arthor:정한솔 20170801
return: void* DDT reference 
parameter:
function details:
공유메모리 영역(for DeciceDescriptTable)에 write하기 위한 설정
*/
void* shmemory_write(){
	int fd;
	size_t len=sizeof(DDT);
	DDT *addr;
	fd=shm_open(SHM_NAME,O_RDWR,0);
	if(fd == -1){
		perror("shm_openW");
		return NULL;
	}
	if(ftruncate(fd,len) == -1){
		perror("ftruncateW");
		return NULL;
	}
	addr=(DDT*)mmap(NULL,len,PROT_READ | PROT_WRITE, MAP_SHARED, fd ,0);
	if(addr==MAP_FAILED){
		perror("mmapW");
		return NULL;
	}
//	printf("Resized to %ld bytes \n",(long)len);
	if(close(fd) == -1){
		perror("close fd");
		return NULL;
	}
	return addr;//DDT의 주소를 반환한다.
}
/*
function: void* shmemory_read()
arthor:정한솔 20170801
return: void* DDT reference 
parameter:
function details:
공유메모리 영역(for DeciceDescriptTable)에 read하기 위한 설정
*/
void* shmemory_read(){
	int fd;
	DDT * addr;
	struct stat sb;
	fd=shm_open(SHM_NAME,O_RDONLY,0);
	if(fd == -1){
		perror("shm_openR");
		return NULL;
	}
	if(fstat(fd,&sb) == -1){
		perror("fstat");
		return NULL;
	}
	addr=(DDT*)mmap(NULL,sb.st_size,PROT_READ,MAP_SHARED,fd,0);
	if(addr == MAP_FAILED){
		perror("mmap");
		return NULL;
	}
	return addr;
}

