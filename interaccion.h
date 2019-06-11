#ifndef INTERACCION_H
#define INTERACCION_H

#include "math.h"

float tabla_de_fuerzas(float *tabla, int N);

float ajustar_dx_para_interaccion(float dx, float L);

float calcular_fuerzas(float *f, float *x, float *tabla, int N, float L, float h);

#endif
