#include "pshm.h"
#include <string.h>

int main(){

	int fd;
	char *addr;
	size_t len;
    char *sampleString="You are so beautiful";
	len=strlen(sampleString)+15;
	fd=shm_open(SHM_NAME,O_RDWR,0);//open exist shm object
	if(fd==-1)
		perror("shm_open");
	if(ftruncate(fd,len)== -1){
	 perror("ftruncate");
	}
	printf("Resized to %ld bytes \n",(long)len);
	addr=mmap(NULL,len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(addr == MAP_FAILED){
	 perror("mmap");
	}
	if(close(fd) == -1)
		perror("close");
	
	sprintf(addr,"%s is to shm\n",sampleString);
	printf("copying %ld bytes\n", strlen(addr));
	exit(EXIT_SUCCESS);

}
