#include "general.h"
#include "inicializar.h"
#include "visualizacion.h"
#include "interaccion.h"
#include "avanzar.h"
#include "medicion.h"
#include "termalizacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int L=4, N=64, M=2500;
	double *x, *v, *f_old, *f_new, *tabla;
	double h, dt=0.01, lambda;
	double T=1;
	x = (double*)malloc(N*3*sizeof(double));
	v = (double*)malloc(N*3*sizeof(double));
	f_old = (double*)malloc(N*3*sizeof(double));
	f_new = (double*)malloc(N*3*sizeof(double));
	tabla = (double*)malloc(M*4*sizeof(double));
	srand(time(NULL));

	h=tabla_de_fuerzas(tabla,M);
	
//	printf("Temperatura inicial que le di: %lf\n", T);
		
		
	set_box(x,N,L);
	set_v(v,N,T);
	
/*	T=medir_temperatura(v,N);
	
	printf("Temperatura inicial que midió: %lf\n", T);
	
	E_p=medir_energia_potencial(x,tabla,L,h,N);
	
	printf("Energía potencial inical: %lf\n", E_p);
*/	

	calcular_fuerzas(f_old,x,tabla,N,L,h);
	
	
	FILE *file;
	file=fopen("datos/Termalizacion_H.txt", "w");
	
	
	for(int i=0; i<400; i++){
		//T=medir_temperatura(v,N);
		//E_p=medir_energia_potencial(x,tabla,L,h,N);
		lambda=termalizacion_H(v,N);
		fprintf(file, "%i\t%lf\n", i, lambda);
		save_lammpstrj("datos/archivo.lammpstrj",x,v,N,L,i);
		ajustar_posicion(x,v,f_old,dt,L,N);
		calcular_fuerzas(f_new,x,tabla,N,L,h);
		ajustar_velocidad(v,f_old,f_new,dt,N);
		for(int j=0; j<3*N; j++)
			*(f_old+j)=*(f_new+j);
	}
	
	fclose(file);
	
	T=medir_temperatura(v,N);
	
	printf("Temperatura final que midió: %lf\n", T);
/*	
	E_p=medir_energia_potencial(x,tabla,L,h,N);

	printf("Energía potencial final: %lf\n", E_p);




	clock_t t;
	
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
