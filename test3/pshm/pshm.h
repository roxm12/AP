#ifndef __SHM_H__
#define __SHM_H__


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../ddt/ddt.h"
#include <sys/mman.h>
#define MMAP_SIZE 1000
#define SHM_NAME "/ddt"//Shared memory section name

int  shmemory_open();//공유메모리 영역 open
void shmemory_close();//공유메모리 영역 해제
void* shmemory_write();//공유메모리 영역 write
void* shmemory_read();//공유메모리 영역 read


#endif
