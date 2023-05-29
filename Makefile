CC = g++
CFLAGS = -Wall -std=c++11

all: programa.out

programa.out: lcgrand.o sistema_de_colas.o inicializacion.o control_tiempo.o actualizar_estad_prom_tiempo.o reportes.o llegada.o salida.o
	$(CC) $(CFLAGS) -o programa.out lcgrand.o sistema_de_colas.o inicializacion.o control_tiempo.o actualizar_estad_prom_tiempo.o reportes.o llegada.o salida.o

lcgrand.o: lcgrand.cpp lcgrand.h
	$(CC) $(CFLAGS) -c lcgrand.cpp

inicializacion.o: inicializacion.cpp inicializacion.h
	$(CC) $(CFLAGS) -c inicializacion.cpp

control_tiempo.o: control_tiempo.cpp control_tiempo.h
	$(CC) $(CFLAGS) -c control_tiempo.cpp

actualizar_estad_prom_tiempo.o: actualizar_estad_prom_tiempo.cpp actualizar_estad_prom_tiempo.h
	$(CC) $(CFLAGS) -c actualizar_estad_prom_tiempo.cpp

reportes.o: reportes.cpp reportes.h 
	$(CC) $(CFLAGS) -c reportes.cpp

llegada.o: llegada.cpp llegada.h 
	$(CC) $(CFLAGS) -c llegada.cpp

salida.o: salida.cpp salida.h 
	$(CC) $(CFLAGS) -c salida.cpp

clean:
	rm -f programa.out *.o
