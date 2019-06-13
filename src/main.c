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
	int  N=512, M=2500;
	double *x, *v, *f_old, *f_new, *tabla;
	double h, dt=0.01, lambda, H, E_p;
	double L=8.4646, T=0.728;
	char filename[64];
	char filename_2[64];
	char filename_3[64];
	clock_t t;
	x = (double*)malloc(N*3*sizeof(double));
	v = (double*)malloc(N*3*sizeof(double));
	f_old = (double*)malloc(N*3*sizeof(double));
	f_new = (double*)malloc(N*3*sizeof(double));
	tabla = (double*)malloc(M*4*sizeof(double));
	srand(time(NULL));
	
	t=clock();	
	
	h=tabla_de_fuerzas(tabla,M);
	
	printf("Temperatura inicial que le di: %lf\n", T);
			
	set_box(x,N,L);
	set_v(v,N,T);
	
	T=medir_temperatura(v,N);
	
	printf("Temperatura inicial que midió: %lf\n", T);



/*	
	E_p=medir_energia_potencial(x,tabla,L,h,N);
	
	printf("Energía potencial inical: %lf\n", E_p);
*/	

	calcular_fuerzas(f_old,x,tabla,N,L,h);
	
	FILE *file;
	FILE *f;
	
	sprintf(filename, "datos/Termalizacion_N_%i_T_%.3lf_L_%.3lf.txt", N,T,L);
	sprintf(filename_2, "datos/Video_N_%i_T_%.3lf_L_%.3lf.lammpstrj", N,T,L);
	sprintf(filename_3, "datos/Energia_N_%i_T_%.3lf_L_%.3lf.txt", N,T,L);
	
	
	
	for(int i=0; i<400; i++){
		T=medir_temperatura(v,N);
		E_p=medir_energia_potencial(x,tabla,L,h,N);
		f=fopen(filename_3,"a");
		fprintf(f, "%i\t%lf\t%lf\n", i, T, E_p);
		fclose(f);
		lambda=termalizacion_verlet(x,L,N);
		H=termalizacion_H(v,N);
		file=fopen(filename, "a");
		fprintf(file, "%i\t%lf\t%lf\n", i, lambda, H);
		fclose(file);
		save_lammpstrj(filename_2,x,v,N,L,i);
		ajustar_posicion(x,v,f_old,dt,L,N);
		calcular_fuerzas(f_new,x,tabla,N,L,h);
		ajustar_velocidad(v,f_old,f_new,dt,N);
		for(int j=0; j<3*N; j++)
			*(f_old+j)=*(f_new+j);
	}
	
	
	
	
	T=medir_temperatura(v,N);
	
	printf("Temperatura final que midió: %lf\n", T);
	
	t=clock()-t;
	printf("El programa tardó %f segundos\n", ((float)t/CLOCKS_PER_SEC));	
	
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
