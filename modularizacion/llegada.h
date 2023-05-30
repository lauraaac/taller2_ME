#ifndef LLEGADA_H

#define LLEGADA_H

#include "../sistema_de_colas.h"
#include <stdio.h>
#include "stdlib.h"

void llegada(
    float * tiempo_sig_evento,
    float & tiempo_simulacion,
    float & media_entre_llegadas,
    int & estado_servidor,
    int & num_servidores,
    int & num_entra_cola,
    FILE * resultados_resumen,
    float * tiempo_llegada,
    float & total_de_esperas,
    int & num_clientes_espera,
    float & media_atencion
    );  /* Funcion de llegada */

#endif