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
