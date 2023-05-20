CC = g++
CFLAGS = -Wall -std=c++11

all: programa.out

programa.out: lcgrand.o sistema_de_colas.o
	$(CC) $(CFLAGS) -o programa.out lcgrand.o sistema_de_colas.o

lcgrand.o: lcgrand.cpp lcgrand.h
	$(CC) $(CFLAGS) -c lcgrand.cpp

sistema_de_colas.o: sistema_de_colas.cpp sistema_de_colas.h lcgrand.h
	$(CC) $(CFLAGS) -c sistema_de_colas.cpp

clean:
	rm -f programa.out *.o
