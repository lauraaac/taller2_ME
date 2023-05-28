/* Definiciones externas para el sistema de colas simple */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "lcgrand.h"
#include "sistema_de_colas_erlang.h"


int sig_tipo_evento,
    num_clientes_espera,
    num_esperas_requerido,
    num_eventos,
    num_entra_cola,
    estado_servidor, /* Este es ahora el numero de servidores ocupados */
    num_servidores;

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

    fprintf(resultados, "Numero de clientes atendidos;Tiempo de simulacion;Numero de clientes en cola;Estado del servidor;Tiempo de proxima llegada;Tiempo de proxima salida;Total de esperas;Area bajo el numero en cola;Area bajo el indicador de servidor ocupado;Tiempo de ultimo evento;Tiempo desde el ultimo evento;Tiempo promedio de espera\n");

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


void inicializar(void)  /* Funcion de inicializacion. */
{
    /* Inicializa el reloj de la simulacion. */

    tiempo_simulacion = 0.0;

    /* Inicializa las variables de estado */

    estado_servidor   = 0;
    num_entra_cola        = 0;
    tiempo_ultimo_evento = 0.0;

    /* Inicializa los contadores estadisticos. */

    num_clientes_espera  = 0;
    total_de_esperas    = 0.0;
    area_num_entra_cola      = 0.0;
    area_estado_servidor = 0.0;

    /* Inicializa la lista de eventos. Ya que no hay clientes, el evento salida
       (terminacion del servicio) no se tiene en cuenta */

    tiempo_sig_evento[1] = tiempo_simulacion + expon(media_entre_llegadas);
    tiempo_sig_evento[2] = 1.0e+30;
}


void controltiempo(void)  /* Funcion controltiempo */
{
    int   i;
    float min_tiempo_sig_evento = 1.0e+29;

    sig_tipo_evento = 0;

    /*  Determina el tipo de evento del evento que debe ocurrir. */

    for (i = 1; i <= num_eventos; ++i)
        if (tiempo_sig_evento[i] < min_tiempo_sig_evento) 
        {
            min_tiempo_sig_evento = tiempo_sig_evento[i];
            sig_tipo_evento = i;
        }

    /* Revisa si la lista de eventos esta vacia. */

    if (sig_tipo_evento == 0) 
    {

        /* La lista de eventos esta vacia, se detiene la simulacion. */

        fprintf(resultados_resumen, "\nLa lista de eventos esta vacia %f", tiempo_simulacion);
        exit(1);
    }

    /* TLa lista de eventos no esta vacia, adelanta el reloj de la simulacion. */

    tiempo_simulacion = min_tiempo_sig_evento;
}


void llegada(void)  /* Funcion de llegada */
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


void salida(void)  /* Funcion de Salida. */
{
    int   i;
    float espera;

    /* Revisa si la cola esta vacia y si hay clientes en servicio*/

    if (num_entra_cola == 0) 
    {
        /* La cola esta vacia, se disminuyen los clientes en el servidor y
        no considera el evento de salida*/     
        estado_servidor = (estado_servidor > 0) ? estado_servidor-1 : 0;
        tiempo_sig_evento[2] = 1.0e+30;
    }
    else {

        /* La cola no esta vacia, disminuye el numero de clientes en cola SI O SI HAY CUPO EN LOS SERVIDORES PUES ACABA SE SALIR UN CLIENTE  */
        --num_entra_cola;

        /*Calcula la espera del cliente que esta siendo atendido y
        actualiza el acumulador de espera si el servidor está libre */

        espera = tiempo_simulacion - tiempo_llegada[1];
        total_de_esperas += espera;

        /*Incrementa el numero de clientes en espera, y programa la salida. */   
        ++num_clientes_espera;
        tiempo_sig_evento[2] = tiempo_simulacion + expon(media_atencion);

        /* Mueve cada cliente en la cola ( si los hay ) una posicion hacia adelante */
        for (i = 1; i <= num_entra_cola; ++i)
            tiempo_llegada[i] = tiempo_llegada[i + 1];


    }
}


void reportes(void)  /* Funcion generadora de reportes. */
{
    /* Calcula y estima los estimados de las medidas deseadas de desempe�o */  
    fprintf(resultados_resumen, "\nEspera promedio en la cola%11.8f minutos\n",
            total_de_esperas / num_clientes_espera);
    fprintf(resultados_resumen, "Numero promedio en cola%10.8f\n",
            area_num_entra_cola / tiempo_simulacion);
    fprintf(resultados_resumen, "Uso del servidor%15.8f\n",
            area_estado_servidor / tiempo_simulacion);
    fprintf(resultados_resumen, "Tiempo de terminacion de la simulacion%12.8f minutos \n", tiempo_simulacion);
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


void actualizar_estad_prom_tiempo(void)  /* Actualiza los acumuladores de
														area para las estadisticas de tiempo promedio. */
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


float expon(float media)  /* Funcion generadora de la exponencias */
{
    /* Retorna una variable aleatoria exponencial con media "media"*/

    return -media * log(lcgrand(1));
}
