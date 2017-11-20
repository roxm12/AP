#ifndef __SHM_H__
#define __SHM_H__
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#define MMAP_SIZE 1000
#define SHM_NAME "/ddt"

int  shmemory_open();
void shmemory_close();
void shmemory_write(char* str);
void shmeory_read();
#endif
