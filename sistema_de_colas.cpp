/* Definiciones externas para el sistema de colas simple */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "modularizacion/lcgrand.h"
#include "sistema_de_colas.h"
#include "modularizacion/inicializacion.h"
#include "modularizacion/control_tiempo.h"
#include "modularizacion/actualizar_estad_prom_tiempo.h"
#include "modularizacion/reportes.h"
#include "modularizacion/llegada.h"
#include "modularizacion/salida.h"
#include "modularizacion/expon.h"


int sig_tipo_evento,
    num_clientes_espera,
    num_esperas_requerido,
    num_eventos,
    num_entra_cola,
    estado_servidor, /* Este es ahora el numero de servidores ocupados */
    num_servidores,
    num_eventos_realizados,
    num_eventos_con_cola;

float area_num_entra_cola,
    area_estado_servidor,
    media_entre_llegadas,
    media_atencion,
    tiempo_simulacion,
    tiempo_llegada[LIMITE_COLA + 1],
    tiempo_ultimo_evento,
    tiempo_sig_evento[3],
    total_de_esperas;


FILE *resultados_resumen, *resultados;

using namespace std;

int main(int argc, char* argv[])  /* Funcion Principal */
{
    /* Abre los archivos de entrada y salida */

    resultados_resumen = fopen("result.txt", "a");
    resultados = fopen("result.csv", "a");

    /* Especifica el numero de eventos para la funcion controltiempo. */

    num_eventos = 2;

    /* Lee los parametros de enrtrada. */

    media_entre_llegadas = atof(argv[1]);
    media_atencion = atof(argv[2]);
    num_esperas_requerido = atoi(argv[3]);
    num_servidores = atoi(argv[4]);

    /* Escribe en el archivo de salida los encabezados del reporte y los parametros iniciales */
    fprintf(resultados_resumen, "------------\n");
    fprintf(resultados_resumen, "Sistema de Colas Simple\n");
    fprintf(resultados_resumen, "Tiempo promedio de llegada%11.8f minutos\n", media_entre_llegadas);
    fprintf(resultados_resumen, "Tiempo promedio de atencion%16.8f minutos\n", media_atencion);
    fprintf(resultados_resumen, "Numero de clientes%14d\n", num_esperas_requerido);

    /* Escribe encabezado para salida tipo csv */

    fprintf(resultados, "Numero de clientes atendidos;Tiempo de simulacion;Numero de clientes en cola;Estado del servidor o num clientes en servidores;Tiempo de proxima llegada;Tiempo de proxima salida;Total de esperas;Area bajo el numero en cola;Area bajo el indicador de servidor ocupado;Tiempo de ultimo evento;Tiempo desde el ultimo evento;Tiempo promedio de espera\n");

    /* iInicializa la simulacion. */

    inicializar(tiempo_simulacion, estado_servidor, num_entra_cola, tiempo_ultimo_evento, num_clientes_espera, total_de_esperas, area_num_entra_cola, area_estado_servidor, tiempo_sig_evento, media_entre_llegadas, num_eventos_realizados, num_eventos_con_cola);

    /* Corre la simulacion mientras no se llegue al numero de clientes especificaco en el archivo de entrada*/

    while (num_clientes_espera < num_esperas_requerido) {
        /*Reporta para el cliente iesimo*/
        reporte_estado();

        /* Determina el siguiente evento */

        controltiempo(resultados_resumen, tiempo_simulacion, sig_tipo_evento, num_eventos, tiempo_sig_evento);

        /* Actualiza los acumuladores estadisticos de tiempo promedio */

        actualizar_estad_prom_tiempo(tiempo_simulacion, tiempo_ultimo_evento, area_num_entra_cola, num_entra_cola, area_estado_servidor, estado_servidor, num_eventos_realizados, num_eventos_con_cola);

        /* Invoca la funcion del evento adecuado. */

        switch (sig_tipo_evento) {
            case 1:
                llegada(tiempo_sig_evento, tiempo_simulacion, media_entre_llegadas, estado_servidor, num_servidores, num_entra_cola, resultados_resumen, tiempo_llegada, total_de_esperas, num_clientes_espera, media_atencion);
                break;
            case 2:
                salida(tiempo_sig_evento, tiempo_simulacion, media_atencion, num_entra_cola, num_clientes_espera, total_de_esperas, estado_servidor, tiempo_llegada);
                break;
        }

    }

    /* Invoca el generador de reportes y termina la simulacion. */

    reportes(resultados_resumen, total_de_esperas, area_num_entra_cola, tiempo_simulacion, area_estado_servidor, num_clientes_espera, num_eventos_realizados, num_eventos_con_cola, num_servidores);

    fclose(resultados);
    fclose(resultados_resumen);

    return 0;
}

void reporte_estado(void) /* Reporte de cada estado. */
{

    fprintf(resultados, "%7d;%f;%11d;%16d;%12.8f;%13.8f;%18.8f;%10.8f;%5.8f;%14.8f;%11.8f;%14.8f\n", 
        num_clientes_espera,
        tiempo_simulacion,
        num_entra_cola,
        estado_servidor,
        tiempo_sig_evento[1],
        tiempo_sig_evento[2],
        total_de_esperas,
        area_num_entra_cola,
        area_estado_servidor,
        tiempo_ultimo_evento,
        tiempo_simulacion - tiempo_ultimo_evento,
        total_de_esperas / num_clientes_espera);

}
