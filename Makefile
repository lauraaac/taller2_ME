CC = g++
CFLAGS = -Wall -std=c++11

all: programa.out erlang.out

programa.out: lcgrand.o sistema_de_colas.o
	$(CC) $(CFLAGS) -o programa.out lcgrand.o sistema_de_colas.o

erlang.out: lcgrand.o sistema_de_colas_erlang.o
	$(CC) $(CFLAGS) -o erlang.out lcgrand.o sistema_de_colas_erlang.o

lcgrand.o: lcgrand.cpp lcgrand.h
	$(CC) $(CFLAGS) -c lcgrand.cpp

sistema_de_colas.o: sistema_de_colas.cpp sistema_de_colas.h lcgrand.h
	$(CC) $(CFLAGS) -c sistema_de_colas.cpp

sistema_de_colas_erlang.o: sistema_de_colas_erlang.cpp sistema_de_colas_erlang.h lcgrand.h
	$(CC) $(CFLAGS) -c sistema_de_colas_erlang.cpp

clean:
	rm -f programa.out *.o

clean-all:
	rm -f programa.out *.o *.txt *.csv