/* Definiciones externas para el sistema de colas simple */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "lcgrand.h"
#include "sistema_de_colas.h"
#include "inicializacion.h"
#include "control_tiempo.h"
#include "actualizar_estad_prom_tiempo.h"
#include "reportes.h"
#include "llegada.h"
#include "salida.h"


int sig_tipo_evento,
    num_clientes_espera,
    num_esperas_requerido,
    num_eventos,
    num_entra_cola,
    estado_servidor;

float area_num_entra_cola,
    area_estado_servidor,
    media_entre_llegadas,
    media_atencion,
    tiempo_simulacion,
    tiempo_llegada[LIMITE_COLA + 1],
    tiempo_ultimo_evento,
    tiempo_sig_evento[3],
    total_de_esperas;


FILE  *parametros,
      *resultados;

using namespace std;

int main(void)  /* Funcion Principal */
{
    /* Abre los archivos de entrada y salida */

    parametros  = fopen("param.txt",  "r");

    resultados = fopen("result.txt", "w");

    /* Especifica el numero de eventos para la funcion controltiempo. */

    num_eventos = 2;

    /* Lee los parametros de enrtrada. */

    fscanf(parametros, "%f %f %d", &media_entre_llegadas, &media_atencion,
           &num_esperas_requerido);

    /* Escribe en el archivo de salida los encabezados del reporte y los parametros iniciales */

    fprintf(resultados, "Sistema de Colas Simple\n\n");
    fprintf(resultados, "Tiempo promedio de llegada%11.3f minutos\n\n",
            media_entre_llegadas);
    fprintf(resultados, "Tiempo promedio de atencion%16.3f minutos\n\n", media_atencion);
    fprintf(resultados, "Numero de clientes%14d\n\n", num_esperas_requerido);

    /* iInicializa la simulacion. */

    inicializar();

    /* Corre la simulacion mientras no se llegue al numero de clientes especificaco en el archivo de entrada*/

    while (num_clientes_espera < num_esperas_requerido) {

        /* Determina el siguiente evento */

        controltiempo();

        /* Actualiza los acumuladores estadisticos de tiempo promedio */

        actualizar_estad_prom_tiempo();

        /* Invoca la funcion del evento adecuado. */

        switch (sig_tipo_evento) {
            case 1:
                llegada();
                break;
            case 2:
                salida();
                break;
        }
    }

    /* Invoca el generador de reportes y termina la simulacion. */

    reportes();

    fclose(parametros);
    fclose(resultados);

    return 0;
}

float expon(float media)  /* Funcion generadora de la exponencias */
{
    /* Retorna una variable aleatoria exponencial con media "media"*/

    return -media * log(lcgrand(1));
}
