#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

float random();
float gaussiana(float mu, float sigma);
float norma(float *v, int l);

float random(){
	return ((float)rand)/((float)rand_max);
}

float gaussiana(float mu, float sigma){
	int n=10;
	float z=0;
	for(i=0; i<n; i++)
		z=random();
	z=sqrt(12)*(z/n-0.5);
	return z*sigma+mu;
}

float norma(float *v){
	float norma=0.0;
	for(i=0; i<l; i++)
		norma+=powl(*(v+i),2);
	return sqrt(norma);
}
