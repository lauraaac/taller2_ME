#include "control_tiempo.h"

void controltiempo(FILE * resultados_resumen,float &tiempo_simulacion, int &sig_tipo_evento, int &num_eventos, float *tiempo_sig_evento) /* Funcion controltiempo */
{
    int i;
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
