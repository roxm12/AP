

#include "pshm.h"

int main(){

	int fd;
	void *addr;
	fd=shm_open(SHM_NAME,O_RDWR | O_CREAT,0666);
	if(fd == -1)
		perror("shm_open");
	if(ftruncate(fd,MMAP_SIZE) == -1)
		perror("ftruncate");
    
	//shm mapping

	addr=mmap(NULL,MMAP_SIZE,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
	if(addr==MAP_FAILED)
		perror("mmap");

	exit(EXIT_SUCCESS);

}

