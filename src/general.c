#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define pi 3.14159265359

double aleatorio();
double gaussiana(double mu, double sigma);
double norma(double *v, int l);

double aleatorio(){
	return rand()*1.0/RAND_MAX;
}

double gaussiana(double mu, double sigma){
	int n=20;
	double z=0;
	for(int i=0; i<n; i++)
		z+=aleatorio();
	z=sqrt(12)*(z/n-0.5);
	return z*sigma+mu;
}

double gaussiana_centrada_en_cero(double sigma){
	double x=aleatorio();
	double y=aleatorio();
	
	return sqrt(-2*sigma*log(x))*cos(2*pi*y);
	
}

double norma(double *v, int l){
	double norma=0.0;
	for(int i=0; i<l; i++)
		norma+=powl(*(v+i),2);
	return sqrt(norma);
}

double histograma(double *x, double *y, int N, int M){

	for(int i=0; i<M; i++)
		*(y+i)=0;
	int j;
	double a, b, h;
	a=maximo(x,N);
	b=minimo(x,N);
	
	h=(a-b)*1.0/M;
	
	for(int i=0; i<N; i++){
		j=(int)((*(x+i)-b)/h);
		if(j>=M)
			j=M-1;
		*(y+j)+=1.0/N;
	}
	return h;
}

double maximo(double *x, int N){
	double a=*x;

	for(int i=1; i<N; i++){
		if(*(x+i)>a)
			a=*(x+i);
	}
		
	return a;
}

double minimo(double *x, int N){
	double a=*x;

	for(int i=1; i<N; i++){
		if(*(x+i)<a)
			a=*(x+i);
	}
		
	return a;
}
