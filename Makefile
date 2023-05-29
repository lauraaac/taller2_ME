CC = g++
CFLAGS = -Wall -std=c++11

all: programa.out



programa.out: modularizacion/lcgrand.o sistema_de_colas.o modularizacion/inicializacion.o modularizacion/control_tiempo.o modularizacion/actualizar_estad_prom_tiempo.o modularizacion/reportes.o modularizacion/llegada.o modularizacion/salida.o
	$(CC) $(CFLAGS) -o programa.out modularizacion/lcgrand.o sistema_de_colas.o modularizacion/inicializacion.o modularizacion/control_tiempo.o modularizacion/actualizar_estad_prom_tiempo.o modularizacion/reportes.o modularizacion/llegada.o modularizacion/salida.o

lcgrand.o: modularizacion/lcgrand.cpp modularizacion/lcgrand.h
	$(CC) $(CFLAGS) -c modularizacion/lcgrand.cpp

inicializacion.o: modularizacion/inicializacion.cpp modularizacion/inicializacion.h
	$(CC) $(CFLAGS) -c modularizacion/inicializacion.cpp

control_tiempo.o: modularizacion/control_tiempo.cpp modularizacion/control_tiempo.h
	$(CC) $(CFLAGS) -c modularizacion/control_tiempo.cpp

actualizar_estad_prom_tiempo.o: modularizacion/actualizar_estad_prom_tiempo.cpp modularizacion/actualizar_estad_prom_tiempo.h
	$(CC) $(CFLAGS) -c modularizacion/actualizar_estad_prom_tiempo.cpp

reportes.o: modularizacion/reportes.cpp modularizacion/reportes.h 
	$(CC) $(CFLAGS) -c modularizacion/reportes.cpp

llegada.o: modularizacion/llegada.cpp modularizacion/llegada.h 
	$(CC) $(CFLAGS) -c modularizacion/llegada.cpp

salida.o: modularizacion/salida.cpp modularizacion/salida.h 
	$(CC) $(CFLAGS) -c modularizacion/salida.cpp


clean:
	rm -f programa.out erlang.out *.o

clean-all:
	rm -f programa.out *.o *.txt *.csv