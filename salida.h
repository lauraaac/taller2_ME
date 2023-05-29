
#ifndef SALIDA_H

#define SALIDA_H

#include "sistema_de_colas.h"

extern int num_entra_cola, estado_servidor, num_clientes_espera;

extern float tiempo_sig_evento[3], tiempo_simulacion, total_de_esperas, tiempo_llegada[LIMITE_COLA + 1], media_atencion;
#endif