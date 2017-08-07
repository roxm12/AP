#ifndef __SHM_H__
#define __SHM_H__
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ddt.h"
#include <sys/mman.h>
#define MMAP_SIZE 1000
#define SHM_NAME "/ddt"

int  shmemory_open();
void shmemory_close();
DDT*  shmemory_write();
DDT*  shmeory_read();
#endif
