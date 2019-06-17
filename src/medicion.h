#ifndef MEDICION_H
#define MEDICION_H
#include "math.h"

double medir_temperatura(double *v, int N);

double medir_energia_potencial(double *x, double *tabla, double L, double h, int N);

double distribucion_radial(double *x, double *g_r, double L, double dr, int N);

#endif
