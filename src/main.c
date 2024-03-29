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
	int  N=512, M=2500, item;
	double *x, *v, *f_old, *f_new, *g_r,*tabla;
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
	g_r = (double*)malloc(N*sizeof(double));
	tabla = (double*)malloc(M*4*sizeof(double));
	
	srand(time(NULL));
	
	sscanf(argv[1],"%i",&item);
	
	if(item==1){
		
		sscanf(argv[2],"%i",&N);
		sscanf(argv[3],"%lf",&L);
		sscanf(argv[4],"%lf",&T);
		
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
		
	//	FILE *file;
		FILE *f;
		
	//	sprintf(filename, "datos/Termalizacion_N_%i_T_%.3lf_L_%.3lf.txt", N,T,L);
		//sprintf(filename_2, "datos/Video_N_%i_T_%.3lf_L_%.3lf.lammpstrj", N,T,L);
		sprintf(filename, "datos/Estado_final.txt");
		sprintf(filename_2, "datos/TvsE_p_N_%i_L_%.3lf.txt",N,L);
		sprintf(filename_3, "datos/Energia_N_%i_T_%.3lf_L_%.3lf.txt", N,T,L);
		
		for(int i=0; i<200; i++){
			//lambda=termalizacion_verlet(x,L,N);
			//H=termalizacion_H(v,N);
			//file=fopen(filename, "a");
			//fprintf(file, "%i\t%lf\t%lf\n", i, lambda, H);
			//fclose(file);
			//save_lammpstrj(filename_2,x,v,N,L,i);
			ajustar_posicion(x,v,f_old,dt,L,N);
			calcular_fuerzas(f_new,x,tabla,N,L,h);
			ajustar_velocidad(v,f_old,f_new,dt,N);
			for(int j=0; j<3*N; j++)
				*(f_old+j)=*(f_new+j);
		}
		
		T=medir_temperatura(v,N);
		
		printf("Temperatura inicial:%lf\n",T);
		
		double T_D;
		double E;
		double E_sqr;
		double a;
		double b;
		double c;
		for(T_D=T; T_D<6.0; T_D+=0.05){
		
			for(int i=0; i<100; i++){
				//lambda=termalizacion_verlet(x,L,N);
				//H=termalizacion_H(v,N);
				//file=fopen(filename, "a");
				//fprintf(file, "%i\t%lf\t%lf\n", i, lambda, H);
				//fclose(file);
				//save_lammpstrj(filename_2,x,v,N,L,b*100+i+200);
				ajustar_posicion(x,v,f_old,dt,L,N);
				calcular_fuerzas(f_new,x,tabla,N,L,h);
				ajustar_velocidad(v,f_old,f_new,dt,N);
				for(int j=0; j<3*N; j++)
					*(f_old+j)=*(f_new+j);
			}
			T=0;
			E_p=0;
			E=0;
			E_sqr=0;
			for(int i=0; i<50; i++){
				a=medir_temperatura(v,N)/50.0;
				T+=a;
				b=medir_energia_potencial(x,tabla,L,h,N)/50.0;
				E_p+=b;
				c=3*a/2+b/N;
				E+=c;
				E_sqr+=c*c;
				//lambda=termalizacion_verlet(x,L,N);
				//H=termalizacion_H(v,N);
				//file=fopen(filename, "a");
				//fprintf(file, "%i\t%lf\t%lf\n", i, lambda, H);
				//fclose(file);
				//save_lammpstrj(filename_2,x,v,N,L,i);
				ajustar_posicion(x,v,f_old,dt,L,N);
				calcular_fuerzas(f_new,x,tabla,N,L,h);
				ajustar_velocidad(v,f_old,f_new,dt,N);
				for(int j=0; j<3*N; j++)
					*(f_old+j)=*(f_new+j);
			}
			
			f=fopen(filename_2,"a");
			fprintf(f, "%lf\t%lf\t%lf\t%lf\n", T, E_p,E,E_sqr);
			fclose(f);
			T=medir_temperatura(v,N);
			printf("Temperatura final que midió: %lf\n", T);
			ajustar_temperatura(v,T,T_D,N);
			T=medir_temperatura(v,N);
			
		}
		
		save_lammpstrj(filename,x,v,N,L,0);
		/*
		for(int i=0; i<20; i++){
			distribucion_radial(x,g_r,L,0.1,N);
			ajustar_posicion(x,v,f_old,dt,L,N);
			calcular_fuerzas(f_new,x,tabla,N,L,h);
			ajustar_velocidad(v,f_old,f_new,dt,N);
			for(int j=0; j<3*N; j++)
				*(f_old+j)=*(f_new+j);
		}
		
		FILE *dist;
		dist=fopen("datos/Distribucion_radial.txt", "w");
		
		int k=0;
		for(double r=0.0; r<L; r+=0.1){
			fprintf(dist,"%lf\t%lf\n",r,*(g_r+k)/20.0);
			k++;
		}
		
		fclose(dist);
		*/
		T=medir_temperatura(v,N);
		
		printf("Temperatura final que midió: %lf\n", T);
		
		t=clock()-t;
		printf("El programa tardó %f segundos\n", ((float)t/CLOCKS_PER_SEC));	
	}

	if(item==2){
	
		sscanf(argv[2],"%i",&N);
		sscanf(argv[3],"%lf",&L);
		sscanf(argv[4],"%lf",&T);
		
		t=clock();	
		
		h=tabla_de_fuerzas(tabla,M);
		
		printf("Temperatura inicial que le di: %lf\n", T);
				
		set_box(x,N,L);
		set_v(v,N,T);
		
		T=medir_temperatura(v,N);
		
		printf("Temperatura inicial que midió: %lf\n", T);
		
		calcular_fuerzas(f_old,x,tabla,N,L,h);
		
		FILE *f;
		
		sprintf(filename, "datos/Termalizacion_N_%i_T_%.3lf_L_%.3lf.txt", N,T,L);
		f=fopen(filename, "w");
		
		for(int i=0; i<500; i++){
			lambda=termalizacion_verlet(x,L,N);
			H=termalizacion_H(v,N);
			fprintf(f, "%i\t%lf\t%lf\n", i, lambda, H);
			ajustar_posicion(x,v,f_old,dt,L,N);
			calcular_fuerzas(f_new,x,tabla,N,L,h);
			ajustar_velocidad(v,f_old,f_new,dt,N);
			for(int j=0; j<3*N; j++)
				*(f_old+j)=*(f_new+j);
		}
		
		fclose(f);
		
		T=medir_temperatura(v,N);
		
		printf("Temperatura final:%lf\n",T);	
		
		t=clock()-t;
		printf("El programa tardó %f segundos\n", ((float)t/CLOCKS_PER_SEC));
	}

	if(item==4){
		
		sscanf(argv[2],"%i",&N);
		sscanf(argv[3],"%lf",&L);
		sscanf(argv[4],"%lf",&T);
		
		t=clock();	
		
		h=tabla_de_fuerzas(tabla,M);
		
		printf("Temperatura inicial que le di: %lf\n", T);
				
		set_box(x,N,L);
		set_v(v,N,T);
		
		T=medir_temperatura(v,N);
		
		printf("Temperatura inicial que midió: %lf\n", T);

		calcular_fuerzas(f_old,x,tabla,N,L,h);
		
		FILE *f;
		
		sprintf(filename, "datos/Estado_final.txt");
		sprintf(filename_2, "datos/barrido/Rho_%.2lf/Temp_N_%i.txt",N/(L*L*L),N);
		sprintf(filename_3, "datos/Energia_N_%i_T_%.3lf_L_%.3lf.txt", N,T,L);
		
		for(int i=0; i<200; i++){
			ajustar_posicion(x,v,f_old,dt,L,N);
			calcular_fuerzas(f_new,x,tabla,N,L,h);
			ajustar_velocidad(v,f_old,f_new,dt,N);
			for(int j=0; j<3*N; j++)
				*(f_old+j)=*(f_new+j);
		}
		
		T=medir_temperatura(v,N);
		
		printf("Temperatura inicial:%lf\n",T);
		
		double T_D;
		double E;
		double E_sqr;
		double a;
		double b;
		double c;
		for(T_D=T; T_D<2.0; T_D+=0.05){
		
			for(int i=0; i<100; i++){
				ajustar_posicion(x,v,f_old,dt,L,N);
				calcular_fuerzas(f_new,x,tabla,N,L,h);
				ajustar_velocidad(v,f_old,f_new,dt,N);
				for(int j=0; j<3*N; j++)
					*(f_old+j)=*(f_new+j);
			}
			T=0;
			E_p=0;
			E=0;
			E_sqr=0;
			for(int i=0; i<50; i++){
				a=medir_temperatura(v,N)/50.0;
				T+=a;
				b=medir_energia_potencial(x,tabla,L,h,N)/50.0;
				E_p+=b;
				c=3*a/2+b/N;
				E+=c;
				E_sqr+=c*c;
				ajustar_posicion(x,v,f_old,dt,L,N);
				calcular_fuerzas(f_new,x,tabla,N,L,h);
				ajustar_velocidad(v,f_old,f_new,dt,N);
				for(int j=0; j<3*N; j++)
					*(f_old+j)=*(f_new+j);
			}
			
			f=fopen(filename_2,"a");
			fprintf(f, "%lf\t%lf\t%lf\t%lf\n", T, E_p,E,E_sqr);
			fclose(f);
			T=medir_temperatura(v,N);
			printf("Temperatura final que midió: %lf\n", T);
			ajustar_temperatura(v,T,T_D,N);
			T=medir_temperatura(v,N);
			
		}
		
		save_lammpstrj(filename,x,v,N,L,0);
		
		T=medir_temperatura(v,N);
		
		printf("Temperatura final que midió: %lf\n", T);
		
		t=clock()-t;
		printf("El programa tardó %f segundos\n", ((float)t/CLOCKS_PER_SEC));
	
	}
	
	if(item==5){
		
		sscanf(argv[2],"%i",&N);
		sscanf(argv[3],"%lf",&L);
		sscanf(argv[4],"%lf",&T);
		
		t=clock();	
		
		h=tabla_de_fuerzas(tabla,M);
		
		printf("Temperatura inicial que le di: %lf\n", T);
				
		set_box(x,N,L);
		set_v(v,N,T);
		
		T=medir_temperatura(v,N);
		
		printf("Temperatura inicial que midió: %lf\n", T);

		calcular_fuerzas(f_old,x,tabla,N,L,h);
		
		FILE *f;
		
		sprintf(filename, "datos/Estado_final.txt");
		sprintf(filename_2, "datos/barrido/Rho_%.2lf/Presion_N_%i.txt",N/(L*L*L),N);
		
		for(int i=0; i<200; i++){
			ajustar_posicion(x,v,f_old,dt,L,N);
			calcular_fuerzas(f_new,x,tabla,N,L,h);
			ajustar_velocidad(v,f_old,f_new,dt,N);
			for(int j=0; j<3*N; j++)
				*(f_old+j)=*(f_new+j);
		}
		
		T=medir_temperatura(v,N);
		
		printf("Temperatura inicial:%lf\n",T);
		
		double T_D;
		double P;
		for(T_D=T; T_D<2.0; T_D+=0.05){
		
			for(int i=0; i<100; i++){
				ajustar_posicion(x,v,f_old,dt,L,N);
				calcular_fuerzas(f_new,x,tabla,N,L,h);
				ajustar_velocidad(v,f_old,f_new,dt,N);
				for(int j=0; j<3*N; j++)
					*(f_old+j)=*(f_new+j);
			}
			T=0;
			P=0;
			for(int i=0; i<50; i++){
				T+=medir_temperatura(v,N)/50.0;
				P+=medir_presion(x,tabla,L,N,h)/50.0;
				ajustar_posicion(x,v,f_old,dt,L,N);
				calcular_fuerzas(f_new,x,tabla,N,L,h);
				ajustar_velocidad(v,f_old,f_new,dt,N);
				for(int j=0; j<3*N; j++)
					*(f_old+j)=*(f_new+j);
			}
			
			f=fopen(filename_2,"a");
			fprintf(f, "%lf\t%lf\n", T, P);
			fclose(f);
			T=medir_temperatura(v,N);
			printf("Temperatura final que midió: %lf\n", T);
			ajustar_temperatura(v,T,T_D,N);
			T=medir_temperatura(v,N);
			
		}
		
		save_lammpstrj(filename,x,v,N,L,0);
		
		T=medir_temperatura(v,N);
		
		printf("Temperatura final que midió: %lf\n", T);
		
		t=clock()-t;
		printf("El programa tardó %f segundos\n", ((float)t/CLOCKS_PER_SEC));
	
	}

	free(x);
	free(v);
	free(f_old);
	free(f_new);
	free(tabla);

}
	
/*	
	}

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

