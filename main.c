#include "general.h"
#include "inicializar.h"
#include "visualizacion.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int L=4, N=2, M=2500;
	float *x, *f, *t;
	float h;
	//float T=0.728;
	x = (float*)malloc(N*3*sizeof(float));
	f = (float*)malloc(N*N*sizeof(float));
	t = (float*)malloc(M*4*sizeof(float));
	FILE *file;
	file=fopen("tabla.txt", "w");
	
	h=tabla_de_fuerzas(t,M);
	fprintf(file, "paso=%f\n",h);
	
	for(int i=0; i<M; i++)
		fprintf(file, "%f\t%f\t%f\t%f\n", *(t+4*i),*(t+4*i+1),*(t+4*i+2),*(t+4*i+3));
	
	fclose(file);
	*x=1;
	*(x+1)=2;
	*(x+2)=2;
	*(x+3)=3;
	*(x+4)=2;
	*(x+5)=2;
	
	calcular_fuerzas(f,x,t,N,L,h);
	
	printf("las fuerzas calculadas son: %f y %f", *(f+N*1+0), *(f+N*0+1));	
/*	clock_t t;
	
	t=clock();
	set_box(x,N,L);
	set_v(v,N,T);
	
	for(int i=0; i<200; i++){
		save_lammpstrj("archivo.lammpstrj",x,v,N,L,i);
		for(int j=0; j<3*N; j++){
			*(x+j)=*(x+j)+(*(v+j));
			if(*(x+j)>L) 
				*(x+j)=*(x+j)-L;
			else if(*(x+j)<0) 
				*(x+j)=*(x+j)+L;
		}
	}
	t=clock()-t;
	printf("El programa tardó %f segundos", ((float)t/CLOCKS_PER_SEC));*/
	free(x);
	free(f);
	free(t);


}
