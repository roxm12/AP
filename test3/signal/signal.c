#include <signal.h>
#include <stdio.h>
void sigusr1Handler(int signo){
printf("SIGUSR1\n");
}
void sigusr2Handler(int signo){
printf("SIGUSR2\n");
}
