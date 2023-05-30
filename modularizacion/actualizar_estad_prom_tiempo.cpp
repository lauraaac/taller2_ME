#include "actualizar_estad_prom_tiempo.h"

void actualizar_estad_prom_tiempo(
    float &tiempo_simulacion, 
    float &tiempo_ultimo_evento, 
    float & area_num_entra_cola, 
    int & num_entra_cola, 
    float & area_estado_servidor, 
    int & estado_servidor)  /* Actualiza los acumuladores de area para las estadisticas de tiempo promedio. */
{
    float time_since_last_event;

    /* Calcula el tiempo desde el ultimo evento, y actualiza el marcador
    	del ultimo evento */

    time_since_last_event = tiempo_simulacion - tiempo_ultimo_evento;
    tiempo_ultimo_evento = tiempo_simulacion;

    /* Actualiza el area bajo la funcion de numero_en_cola */
    area_num_entra_cola += num_entra_cola * time_since_last_event;

    /*Actualiza el area bajo la funcion indicadora de servidor ocupado*/
    area_estado_servidor += estado_servidor * time_since_last_event;
}