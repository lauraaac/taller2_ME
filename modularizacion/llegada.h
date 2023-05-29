#ifndef LLEGADA_H

#define LLEGADA_H

#include "../sistema_de_colas.h"
#include <stdio.h>
#include "stdlib.h"

extern FILE *resultados, *resultados_resumen;

extern int estado_servidor,
           num_entra_cola,
           num_clientes_espera,
           num_servidores;
           
extern float tiempo_sig_evento[3], 
             tiempo_simulacion,
             media_entre_llegadas,
             tiempo_llegada[LIMITE_COLA + 1],
             total_de_esperas, media_atencion;

#endif