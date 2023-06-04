#include "inicializacion.h"
#include "expon.h"

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
    float & media_entre_llegadas,
    int & num_eventos_realizados, 
    int & num_eventos_con_cola)  /* Funcion de inicializacion. */
{
    /* inicializa valores para calcular promedios de veces que el sistema tuvo cola*/
    num_eventos_realizados = 0;
    num_eventos_con_cola = 0;

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