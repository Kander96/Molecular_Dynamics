#include "medicion.h"
#include "general.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define pi 3.14159265359

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

double medir_presion(double *x, double *tabla, double L, int N, double h){

	double P=0;
	double dx, dy, dz, DX;
	int indice, b=0;
	
	for(int i=0; i<N-1; i++){
		for(int j=i+1; j<N; j++){
			b++;
			dx=*(x+3*i)-(*(x+3*j));
			dy=*(x+3*i+1)-(*(x+3*j+1));
			dz=*(x+3*i+2)-(*(x+3*j+2));
			dx=ajustar_dx_para_interaccion(dx,L);
			dy=ajustar_dx_para_interaccion(dy,L);
			dz=ajustar_dx_para_interaccion(dz,L);
			DX=sqrt(dx*dx+dy*dy+dz*dz);
			
			if(DX<=cut_off){
				indice=(int)(DX/h);
				P+=*(tabla+4*indice+2)*dx*dx;
				P+=*(tabla+4*indice+2)*dy*dy;
				P+=*(tabla+4*indice+2)*dz*dz;
			}
		}
	}
	
	return P*1.0/b;
}

double distribucion_radial(double *x, double *g_r, double L, double dr, int N){
	
	double rho=N/(L*L*L), r, R, dx, dy, dz;
	int dn, k=0;

		
	for(r=0.0; r<L+dr; r+=dr){
		dn=0;
		for(int i=0; i<N-1; i++){
			for(int j=i; j<N; j++){
				dx=*(x+3*i)-(*(x+3*j));
				dy=*(x+3*i+1)-(*(x+3*j+1));
				dz=*(x+3*i+2)-(*(x+3*j+2));
				dx=ajustar_dx_para_interaccion(dx,L);
				dy=ajustar_dx_para_interaccion(dy,L);
				dz=ajustar_dx_para_interaccion(dz,L);
				R=dx*dx+dy*dy+dz*dz;
				if(R>r*r && R<((r+dr)*(r+dr)))
					dn++;
			}
		}
		dn=2*dn*1.0/N;
		*(g_r+k)+=dn/(4*pi*r*r*dr*rho);
		k++;
	}
			
	return 0;
}
