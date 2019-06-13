#ifndef AVANZAR_H
#define AVANZAR_H
#include "math.h"

double ajustar_posicion(double *x, double *v, double *f, double dt, double L, int N);

double ajustar_velocidad(double *v, double *f_old, double *f_new, double dt, int N);

double ajustar_temperatura(double *v, double T_m, double T_d, int N);

#endif
