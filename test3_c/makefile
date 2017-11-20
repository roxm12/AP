CC = g++

main_exe : main.o pth_funcs.o ddt.o pshm_funcs.o sem_funcs.o com.o sig.o
	$(CC) -W -Wall -o main_exe  main.o pth_funcs.o ddt.o pshm_funcs.o sem_funcs.o com.o sig.o  -lpthread -lrt

main.o : main.cpp
	$(CC) -W -Wall -c -o main.o main.cpp

ddt.o : ./ddt/ddt.cpp
	$(CC) -W -Wall -c -o ddt.o ./ddt/ddt.cpp

pshm_funcs.o : ./pshm/pshm.cpp
	$(CC) -W -Wall -c -o pshm_funcs.o ./pshm/pshm.cpp

sem_funcs.o : ./sem/sem.cpp
	$(CC) -W -Wall -c -o sem_funcs.o ./sem/sem.cpp

sig.o : ./signal/sig.cpp
	$(CC) -W -Wall -c -o sig.o ./signal/sig.cpp

pth_funcs.o : ./pth/pth.cpp
	$(CC) -W -Wall -c -o pth_funcs.o ./pth/pth.cpp

com.o : ./com/com.cpp
	$(CC) -W -Wall -c -o com.o ./com/com.cpp

clean :
	rm *.o main_exe
