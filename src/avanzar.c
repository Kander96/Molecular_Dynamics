#include "general.h"

double ajustar_posicion(double *x, double *v, double *f, double dt, double L, int N){

	for(int i=0; i<3*N; i++){
			*(x+i)+=*(v+i)*dt+(*(f+i))*dt*dt/2.0;
			if(*(x+i)>L) 
				*(x+i)-=L;
			else if(*(x+i)<0) 
				*(x+i)+=L;
	}
	return 0;
}

double ajustar_velocidad(double *v, double *f_old, double *f_new, double dt, int N){
	
	for(int i=0; i<3*N; i++)
		*(v+i)+=(*(f_old+i)+(*(f_new+i)))*dt/2.0;
	return 0;
}

double ajustar_temperatura(double *v, double T_m, double T_d, int N){
	
	for(int i=0; i<3*N; i++)
		*(v+i)=*(v+i)*sqrt(T_d/T_m);
	return 0;
}
