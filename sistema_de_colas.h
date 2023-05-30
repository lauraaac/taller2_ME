/* Archivo de encabezado para el sistema de colas simple */

#ifndef SISTEMA_COLAS_ERLANG_H
#define SISTEMA_COLAS_ERLANG_H

#define LIMITE_COLA 100  /* Capacidad maxima de la cola */
#define OCUPADO      1    /* Indicador de Servidor Ocupado */
#define LIBRE        0    /* Indicador de Servidor Libre */


void  reporte_estado(void);
float expon(float mean);

#endif /* SISTEMA_COLAS_ERLANG_H */
