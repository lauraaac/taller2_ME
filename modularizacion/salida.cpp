
#include "salida.h"
#include "expon.h"

void salida(
    float * tiempo_sig_evento,
    float & tiempo_simulacion,
    float & media_atencion,
    int & num_entra_cola,
    int & num_clientes_espera,
    float & total_de_esperas,
    int & estado_servidor,
    float * tiempo_llegada,
    int & num_servidores
)  /* Funcion de Salida. */
{
    int   i;
    float espera;

    /* Revisa si la cola esta vacia y si hay clientes en servicio*/

    if (num_entra_cola == 0 && estado_servidor == 0) 
    {
        /* La cola esta vacia, se disminuyen los clientes en el servidor y
        no considera el evento de salida*/     
        tiempo_sig_evento[2] = 1.0e+30;
    }
    else if (num_entra_cola > 0 || estado_servidor > 0){
        estado_servidor--;
        /* La cola no esta vacia, disminuye el numero de clientes en cola SI O SI HAY CUPO EN LOS SERVIDORES PUES ACABA SE SALIR UN CLIENTE  */
        num_entra_cola = (num_entra_cola > 0) ? num_entra_cola - 1 : 0;
        estado_servidor = (num_entra_cola > 0) ? estado_servidor + 1 : estado_servidor;

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