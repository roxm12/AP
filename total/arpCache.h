#ifndef __ARPCACHE_H__
#define __ARPCACHE_H__


 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/ipc.h>
 #include <sys/shm.h>
 #include <string.h>
 #include "ddt.h"
 #define xstr(s) str(s)
 #define str(s) #s
 #define ARP_CACHE "/proc/net/arp"
 #define ARP_STRING_LEN  1023
 #define ARP_BUFFER_LEN  (ARP_STRING_LEN + 1)
 #define N_INTERFACE "wlan0"
 #define ARP_LINE_FORMAT "%" xstr(ARP_STRING_LEN) "s %*s %*s " \
	                     "%" xstr(ARP_STRING_LEN) "s %*s " \
						 "%" xstr(ARP_STRING_LEN) "s"
//즉 접속해제 되는 애들도 해결해야 한다.
/* Format for fscanf() to read the 1st, 4th, and 6th space-delimited fields */
/*%1024s*/


void setDDT(FILE *);
#endif
