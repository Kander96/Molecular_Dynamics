#include "general.h"
#include "inicializar.h"
#include "visualizacion.h"
#include "interaccion.h"
#include "avanzar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int L=4, N=2, M=2500;
	double *x, *v, *f_old, *f_new, *tabla;
	double h, dt=0.01;
	//float T=0.128;
	x = (double*)malloc(N*3*sizeof(double));
	v = (double*)malloc(N*3*sizeof(double));
	f_old = (double*)malloc(N*3*sizeof(double));
	f_new = (double*)malloc(N*3*sizeof(double));
	tabla = (double*)malloc(M*4*sizeof(double));
	
	for(int i=0; i<3*N; i++){
		*(f_old+i)=0.0;
		*(f_new+i)=0.0;
		*(v+i)=0.0;
	}
	/*FILE *file;
	file=fopen("tabla.txt", "w");
	*/
	h=tabla_de_fuerzas(tabla,M);
	/*fprintf(file, "paso=%f\n",h);
	
	for(int i=0; i<M; i++)
		fprintf(file, "%f\t%f\t%f\t%f\n", *(t+4*i),*(t+4*i+1),*(t+4*i+2),*(t+4*i+3));
	fclose(file);
	*/	
	
	
	
	*x=1;
	*(x+1)=2;
	*(x+2)=2;
	*(x+3)=3;
	*(x+4)=2;
	*(x+5)=2;
	
	calcular_fuerzas(f_old,x,tabla,N,L,h);
	
	//printf("las fuerzas calculadas son: f_x_1=%lf, f_y_1=%lf f_z_1=%lf y f_x_2=%lf, f_y_2=%lf, f_z_2=%lf", *f, *(f+1), *(f+2), *(f+3), *(f+4), *(f+5));	

	//set_v(v,N,T);
	
	for(int i=0; i<200; i++){
		save_lammpstrj("archivo.lammpstrj",x,v,N,L,i);
		ajustar_posicion(x,v,f_old,dt,L,N);
		calcular_fuerzas(f_new,x,tabla,N,L,h);
		ajustar_velocidad(v,f_old,f_new,dt,N);
		for(int j=0; j<3*N; j++)
			*(f_old+j)=*(f_new+j);
	}

	






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
	free(v);
	free(f_old);
	free(f_new);
	free(tabla);


}
