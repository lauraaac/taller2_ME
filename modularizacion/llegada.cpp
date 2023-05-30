#include "llegada.h"

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
    )  /* Funcion de llegada */
{
    float espera;

    /* Programa la siguiente llegada. */

    tiempo_sig_evento[1] = tiempo_simulacion + expon(media_entre_llegadas);

    /* Revisa si el servidor esta OCUPADO. */

    if (estado_servidor == num_servidores) {

        /* Sservidor OCUPADO, aumenta el numero de clientes en cola */

        ++num_entra_cola;

        /* Verifica si hay condici�n de desbordamiento */

        if (num_entra_cola > LIMITE_COLA) {

            /* Se ha desbordado la cola, detiene la simulacion */

            fprintf(resultados_resumen, "\nDesbordamiento del arreglo tiempo_llegada a la hora");
            fprintf(resultados_resumen, "%f", tiempo_simulacion);
            exit(2);
        }

        /* Todavia hay espacio en la cola, se almacena el tiempo de llegada del
        	cliente en el ( nuevo ) fin de tiempo_llegada */

        tiempo_llegada[num_entra_cola] = tiempo_simulacion;
    }

    else {

        /*  El servidor esta LIBRE es decir hay menos servidores libres, por lo tanto el cliente que llega tiene tiempo de eespera=0
           (Las siguientes dos lineas del programa son para claridad, y no afectan
           el reultado de la simulacion ) */

        espera            = 0.0;
        total_de_esperas += espera;

        /* Incrementa el numero de clientes en espera, y pasa el servidor a ocupado */
        ++num_clientes_espera;
        estado_servidor++;

        /* Programa una salida ( servicio terminado ). */     

        tiempo_sig_evento[2] = tiempo_simulacion + expon(media_atencion);
    }
}