CC = gcc

pth_exe : main.o ddt.o pshm_funcs.o sem_funcs.o
	$(CC) -gdbb -o pth_exe  main.o pth_funcs.o ddt.o pshm_funcs.o sem_funcs.o -lpthread -lrt

main.o : main.c
	$(CC) -c -o main.o main.c

pth_funcs.o : ./pth/pth_funcs.c
	$(CC) -c -o pth_funcs.o ./pth/pth_funcs.c

ddt.o : ./ddt/ddt.c
	$(CC) -c -o ddt.o ./ddt/ddt.c

pshm_funcs.o : ./pshm/pshm_funcs.c
	$(CC) -c -o pshm_funcs.o ./pshm/pshm_funcs.c

sem_funcs.o : ./sem/sem_funcs.c
	$(CC) -c -o sem_funcs.o ./sem/sem_funcs.c

clean :
	rm *.o pth_exe
