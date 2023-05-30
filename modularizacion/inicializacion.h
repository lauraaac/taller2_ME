#ifndef INICIALIZACION_H

#define INICIALIZACION_H


void inicializar(
    float & tiempo_simulacion, 
    int & estado_servidor, 
    int & num_entra_cola, 
    float & tiempo_ultimo_evento,
    int & num_clientes_espera,
    float & total_de_esperas,
    float & area_num_entra_cola,
    float & area_estado_servidor,
    float * tiempo_sig_evento,
    float & media_entre_llegadas);

#endif 