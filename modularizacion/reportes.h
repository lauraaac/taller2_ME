#ifndef REPORTES_H

#define REPORTES_H

#include "stdlib.h"
#include <stdio.h>
#include "../sistema_de_colas.h"

void reportes(
        FILE *resultados_resumen,
        float & total_de_esperas,
        float & area_num_entra_cola,
        float & tiempo_simulacion,
        float & area_estado_servidor,
        int & num_clientes_espera,
        int & num_eventos_realizados, 
        int & num_eventos_con_cola,
        int & num_servidores
        );

#endif