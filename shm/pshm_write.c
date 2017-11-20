#include "pshm.h"
#include <string.h>

int main(){

	int fd;int i;
	char *addr;
	size_t len; size_t tempLen;
    char *sampleString="You are so beautiful\n";
	len=strlen(sampleString)+1;
	tempLen=strlen(sampleString);
	fd=shm_open(SHM_NAME,O_RDWR,0);//open exist shm object
    i=0;
	if(fd==-1)
	 perror("shm_open");
	while(i<10){
	if(ftruncate(fd,len) == -1)
		perror("ftruncate");
	addr=mmap(NULL,len,PROT_READ | PROT_WRITE, MAP_SHARED, fd,0);
	if(addr == MAP_FAILED)
		perror("mmap");
	sprintf(addr+tempLen*i,"%s",sampleString);
	len += tempLen;
	i++;
	}

	/*
	while(i<10){
	if(ftruncate(fd,len)== -1){
	 perror("ftruncate");
	}
	printf("Resized to %ld bytes \n",(long)len);
	addr=mmap(NULL,len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(addr == MAP_FAILED){
	 perror("mmap");
	 printf("mmap");
	}	
	sprintf(addr+len*i-1,"%s",sampleString);
	printf("copying %ld bytes\n", strlen(addr));
	printf("len is %d\n",len);
	len += tempLen*(++i);
	}
	*/
	if(close(fd) == -1)
		perror("close");
	exit(EXIT_SUCCESS);

}
