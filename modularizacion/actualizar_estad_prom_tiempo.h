#ifndef ACTUALIZAR_ESTAD_PROM_TIEMPO_H

#define ACTUALIZAR_ESTAD_PROM_TIEMPO_H

void actualizar_estad_prom_tiempo(
    float &tiempo_simulacion, 
    float &tiempo_ultimo_evento, 
    float & area_num_entra_cola, 
    int & num_entra_cola, 
    float & area_estado_servidor, 
    int & estado_servidor,
    int & num_eventos_realizados,
    int & num_eventos_con_cola);

#endif