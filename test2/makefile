CC = gcc

pth_exe : main.o arp_funcs.o ddt.o pshm_funcs.o sem_funcs.o
	gcc -gdbb -o pth_exe  main.o pth_funcs.o arp_funcs.o ddt.o pshm_funcs.o sem_funcs.o -lpthread -lrt

main.o : main.c
	gcc -c -o main.o main.c

arp_funcs.o : ./arp/arp_funcs.c
	gcc -c -o arp_funcs.o ./arp/arp_funcs.c

pth_funcs.o : ./pth/pth_funcs.c
	gcc -c -o pth_funcs.o ./pth/pth_funcs.c

ddt.o : ./ddt/ddt.c
	gcc -c -o ddt.o ./ddt/ddt.c

pshm_funcs.o : ./pshm/pshm_funcs.c
	gcc -c -o pshm_funcs.o ./pshm/pshm_funcs.c

sem_funcs.o : ./sem/sem_funcs.c
	gcc -c -o sem_funcs.o ./sem/sem_funcs.c

clean :
	rm *.o pth_exe
