#include "medicion.h"
#include "interaccion.h"

double medir_temperatura(double *v, int N){
	
	double T, sx=0, sy=0, sz=0;
	
	for(int i=0; i<N; i++){
		sx+=powl(*(v+3*i),2);
		sy+=powl(*(v+3*i+1),2);
		sz+=powl(*(v+3*i+2),2);
	}
	
	T=(sx+sy+sz)/(3.0*N);
	
	return T;
}
/*
double medir_energía_cinética(double *v, int N){

	double E_k=0;


}*/

double medir_energia_potencial(double *x, double *tabla, double L, double h, int N){
	double dx, dy, dz, DX, E_p=0;
	int indice;
	
	for(int i=0; i<N-1; i++){
		for(int j=i+1; j<N; j++){
			dx=*(x+3*i)-(*(x+3*j));
			dy=*(x+3*i+1)-(*(x+3*j+1));
			dz=*(x+3*i+2)-(*(x+3*j+2));
			dx=ajustar_dx_para_interaccion(dx,L);
			dy=ajustar_dx_para_interaccion(dy,L);
			dz=ajustar_dx_para_interaccion(dz,L);
			DX=sqrt(dx*dx+dy*dy+dz*dz);
			
			if(DX<=cut_off){
				indice=(int)(DX/h);
				E_p+=*(tabla+4*indice+3);
			}
		}
	
	}
	return E_p;	
}
