#include "pshm.h"
#include <string.h>
#include <unistd.h>
int main(){

	int fd;
	char *addr;
	struct stat sb;//현재 shm의 상태를 알기 위함임.
	fd=shm_open(SHM_NAME,O_RDONLY,0);
	if(fd == -1)
		perror("shm_open");
	//fstat read file state from fd
	if(fstat(fd,&sb) == -1)
		perror("fstat");
	addr=mmap(NULL,sb.st_size,PROT_READ,MAP_SHARED,fd,0);
	if(addr == MAP_FAILED) 
		perror("mmap");
	if(close(fd) == -1)
		perror("close");

	write(STDOUT_FILENO,addr,sb.st_size);
	printf("\n");
	exit(EXIT_SUCCESS);


}
