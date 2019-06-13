#ifndef GENERAL_H
#define GENERAL_H

#include "math.h"

#define pi 3.14159265359

double aleatorio();

double gaussiana(double mu, double sigma);

double gaussiana_centrada_en_cero(double sigma);

double norma(double *v, int l);

double histograma(double *x, double *y, int N, int M);

double maximo(double *x, int N);

double minimo(double *x, int N);

#endif
