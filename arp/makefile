CC = gcc

arp_exe : main.o arp_funcs.o ddt.o pshm_funcs.o sem_funcs.o
	gcc -o arp_exe main.o arp_funcs.o ddt.o pshm_funcs.o sem_funcs.o -lpthread -lrt

main.o : main.c
	gcc -c -o main.o main.c

arp_funcs.o : arp_funcs.c
	gcc -c -o arp_funcs.o arp_funcs.c

ddt.o : ddt.c
	gcc -c -o ddt.o ddt.c

pshm_funcs.o : pshm_funcs.c
	gcc -c -o pshm_funcs.o pshm_funcs.c

sem_funcs.o : sem_funcs.c
	gcc -c -o sem_funcs.o sem_funcs.c

clean :
	rm *.o arp_exe
