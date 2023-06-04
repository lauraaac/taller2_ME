#include "reportes.h"

void reportes(
        FILE *resultados_resumen,
        float & total_de_esperas,
        float & area_num_entra_cola,
        float & tiempo_simulacion,
        float & area_estado_servidor,
        int & num_clientes_espera,
        int & num_eventos_realizados, 
        int & num_eventos_con_cola
        )  /* Funcion generadora de reportes. */
{
    /* Calcula y estima los estimados de las medidas deseadas de desempe�o */  
    fprintf(resultados_resumen, "\nEspera promedio en la cola %11.8f minutos\n",
            total_de_esperas / num_clientes_espera);
    fprintf(resultados_resumen, "Numero promedio en cola %10.8f\n",
            area_num_entra_cola / tiempo_simulacion);
    fprintf(resultados_resumen, "Uso del servidor %15.8f\n",
            area_estado_servidor / tiempo_simulacion);
    fprintf(resultados_resumen, "Tiempo de terminacion de la simulacion %12.8f minutos \n", tiempo_simulacion);
    fprintf(resultados_resumen, "Numero eventos realizados: %14d\n", num_eventos_realizados);
    fprintf(resultados_resumen, "Numero eventos con cola: %14d\n", num_eventos_con_cola);
    fprintf(resultados_resumen, "Promedio eventos con cola: %14.8f\n",  (float) num_eventos_con_cola/ (float)num_eventos_realizados );
}
