#include "general.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

float tabla_de_fuerzas(float *tabla, int N){
	
	float h=2.5/N;
	float r=h;
		
	for(int j=0; j<N; j++){
		*(tabla+j*4)=r;
		*(tabla+j*4+1)=r*r;
		*(tabla+j*4+2)=24*(2*powl(*(tabla+j*4+1),-7)-powl(*(tabla+j*4+1),-4)); //esto es F(r)/r
		*(tabla+j*4+3)=4*(powl(*(tabla+j*4+1),-6)-powl(*(tabla+j*4+1),-3));
		r+=h;
	}
	return h;
}

float ajustar_dx_para_interaccion(float dx, float L){
	
	if(dx<=-L/2)
		dx+=L;
	else if(dx>=L/2)
		dx-=L;
	return dx;
}

float calcular_fuerzas(float *f, float *x, float *tabla, int N, float L, float h){
	
	float dx, dy, dz, DX;
	int indice;
	
	for(int i=0; i<N; i++){
		for(int j=i+1; j<N; j++){
			
			dx=*(x+3*i)-(*(x+3*j));
			dy=*(x+3*i+1)-(*(x+3*j+1));
			dz=*(x+3*i+2)-(*(x+3*j+2));
			dx=ajustar_dx_para_interaccion(dx,L);
			dy=ajustar_dx_para_interaccion(dy,L);
			dz=ajustar_dx_para_interaccion(dz,L);
			DX=sqrt(dx*dx+dy*dy+dz*dz);
			
			if(DX<=2.5){
				indice=(int)(DX/h);
				*(f+N*i+j)+=*(tabla+4*indice+2);
				*(f+N*j+i)+=*(tabla+4*indice+2);
			
			}
		}
	}
	
	
	return 0;
}
