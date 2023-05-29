#ifndef REPORTES_H

#define REPORTES_H

#include "stdlib.h"
#include <stdio.h>
#include "../sistema_de_colas.h"

extern FILE *resultados, *resultados_resumen;
extern float total_de_esperas, area_num_entra_cola, tiempo_simulacion, area_estado_servidor;
extern int num_clientes_espera;

#endif