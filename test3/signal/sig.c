#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "../com/com.h"
volatile sig_atomic_t gSigStat=0;
void sigusr1Handler(int signo){
    if(signo ==SIGUSR1){
    printf("sigsur1\n");
   // system("~/AP/test3/com/cmain");
    parse();
    //Parsing routine
//    gSigStat=1; 
    }

}
void sigusr2Handler(int signo){
 if(signo==SIGUSR2){
    printf("sigusr2\n");
 //   gSigStat=1;
 }
}
