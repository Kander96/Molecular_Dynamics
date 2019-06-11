#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

double aleatorio();
double gaussiana(double mu, double sigma);
double norma(double *v, int l);

double aleatorio(){
	return ((double)rand())/((double)RAND_MAX);
}

double gaussiana(double mu, double sigma){
	int n=10;
	double z=0;
	for(int i=0; i<n; i++)
		z+=aleatorio();
	z=sqrt(12)*(z/n-0.5);
	return z*sigma+mu;
}

double norma(double *v, int l){
	double norma=0.0;
	for(int i=0; i<l; i++)
		norma+=powl(*(v+i),2);
	return sqrt(norma);
}
