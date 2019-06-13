#include "inicializar.h"
#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


double set_box(double *X, int N, double L){
	
	int n=cbrt(N), i=0;
	double dL=L/n;
	
	for(int x=0; x<n; x++){
		for(int y=0; y<n; y++){
			for(int z=0; z<n; z++){
				*(X+3*i)=dL*(x+0.5);
				*(X+3*i+1)=dL*(y+0.5);
				*(X+3*i+2)=dL*(z+0.5);
				i++;
			}
		}
	}
	return dL;
}

double set_v(double *v, int N, double T){

	double sigma=sqrt(T);
	
	for(int i=0; i<3*N; i++)
		*(v+i)=gaussiana(0.0,sigma);
		//*(v+i)=gaussiana_centrada_en_cero(sigma);
	
	double vcm[3]={0,0,0};
	
	for(int i=0; i<N; i++){
		for(int k=0; k<3; k++)
			vcm[k]+=v[3*i+k]/N;
	}
	
	for(int i=0; i<N; i++){
		for(int k=0; k<3; k++)
			v[3*i+k]-=vcm[k];
			
	}
	return 0;	
}
