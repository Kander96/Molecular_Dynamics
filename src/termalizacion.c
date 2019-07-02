#include "general.h"
#include "termalizacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

double termalizacion_verlet(double *x, double L, int N){
	
	double a, lambda=0.0;
	
	a=L*1.0/cbrt(N);
	
	for(int i=0; i<3*N; i++)
		lambda+=cos(2*pi*((*(x+i))-a/2.0)/a)*1.0/(3*N);
	return lambda;
}

double termalizacion_H(double *v, int N){
	
	int M=10;
	double *v_x, *v_y, *v_z, *hist;
	double H_x=0.0, H_y=0.0, H_z=0.0, h;
	
	v_x = (double*)malloc(N*sizeof(double));
	v_y = (double*)malloc(N*sizeof(double));
	v_z = (double*)malloc(N*sizeof(double));
	hist= (double*)malloc(M*sizeof(double));
	
	for(int i=0; i<N; i++){
		*(v_x+i)=*(v+3*i);
		*(v_y+i)=*(v+3*i+1);
		*(v_z+i)=*(v+3*i+2);
	}
	
	h=histograma(v_x,hist,N,M);
	for(int i=0; i<M; i++){
		if(*(hist+i)>0)
			H_x+=*(hist+i)*log(*(hist+i))*h;
	}
	h=histograma(v_y,hist,N,M);
	for(int i=0; i<M; i++){
		if(*(hist+i)>0)
			H_y+=*(hist+i)*log(*(hist+i))*h;
	}
	h=histograma(v_z,hist,N,M);
	for(int i=0; i<M; i++){
		if(*(hist+i)>0)
			H_z+=*(hist+i)*log(*(hist+i))*h;
	}
	
	
	free(v_x);
	free(v_y);
	free(v_z);
	free(hist);
	return (H_x+H_y+H_z)/3.0;
}
