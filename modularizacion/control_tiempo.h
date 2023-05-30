#ifndef CONTROL_TIEMPO_H

#define CONTROL_TIEMPO_H

#include "stdlib.h"
#include <stdio.h>

void controltiempo(FILE * resultados_resumen,float &tiempo_simulacion, int &sig_tipo_evento, int &num_eventos, float *tiempo_sig_evento);  /* Funcion de control de tiempo */

#endif