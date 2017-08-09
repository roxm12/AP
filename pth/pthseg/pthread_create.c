#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static void* threadFunc(void *arg){

	char *s=(char *)arg;
	printf("%s",s);
	return (void*) strlen(s);
}

int main(){


	pthread_t tl;
	void *res;
	int s;
	s=pthread_create(&tl,NULL,threadFunc,"Hello world\n");
	if(s != 0)
		perror("pthread create\n");
	printf("message from main()\n");
	s=pthread_join(tl,&res);
	if( s!= 0)
		perror("pthread join\n");
	printf("Thread returned %ld\n",(long)res);

	return;

}
