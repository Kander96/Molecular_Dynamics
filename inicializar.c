#include "inicializar.h"
#include "general.h"

float set_box(float *X, int N, float L){
	
	int n=cbrt(N), i=0;
	float dL=L/n;
	
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

float set_v(float *v, int N, float T){

	float sigma=sqrt(T);
	
	for(int i=0; i<3*N; i++)
		v[i]=gaussiana(0.0,sigma);
	
	float vcm[3]={0,0,0};
	
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
