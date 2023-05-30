
#ifndef SALIDA_H

#define SALIDA_H

#include "../sistema_de_colas.h"

void salida(
    float * tiempo_sig_evento,
    float & tiempo_simulacion,
    float & media_atencion,
    int & num_entra_cola,
    int & num_clientes_espera,
    float & total_de_esperas,
    int & estado_servidor,
    float * tiempo_llegada
);  /* Funcion de Salida. */

#endif