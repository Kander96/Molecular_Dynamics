#ifndef INTERACCION_H
#define INTERACCION_H

#define cut_off 2.5

#include "math.h"

double tabla_de_fuerzas(double *tabla, int N);

double ajustar_dx_para_interaccion(double dx, double L);

double calcular_fuerzas(double *f, double *x, double *tabla, int N, double L, double h);

#endif
