/* Archivo de encabezado para el sistema de colas simple */

#ifndef SISTEMA_COLAS_SIMPLE_H
#define SISTEMA_COLAS_SIMPLE_H

#define LIMITE_COLA 100  /* Capacidad maxima de la cola */
#define OCUPADO      1    /* Indicador de Servidor Ocupado */
#define LIBRE        0    /* Indicador de Servidor Libre */

void  inicializar(void);
void  controltiempo(void);
void  llegada(void);
void  salida(void);
void  reportes(void);
void  actualizar_estad_prom_tiempo(void);
float expon(float mean);

#endif /* SISTEMA_COLAS_SIMPLE_H */
