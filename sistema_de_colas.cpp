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

    inicializar();

    /* Corre la simulacion mientras no se llegue al numero de clientes especificaco en el archivo de entrada*/

    while (num_clientes_espera < num_esperas_requerido) {
        /*Reporta para el cliente iesimo*/
        reporte_estado();

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


float expon(float media)  /* Funcion generadora de la exponencias */
{
    /* Retorna una variable aleatoria exponencial con media "media"*/

    return -media * log(lcgrand(1));
}
