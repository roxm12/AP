#include "pshm.h"
int main(){

	if(shm_unlink(SHM_NAME) == -1)
		perror("shm_unlink");

	exit(EXIT_SUCCESS);
}






