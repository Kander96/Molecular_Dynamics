#include "visualizacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Viene con comentarios para que los interesados en entender no me odien
// Este formato es LAMMPS trajectory, que VMD entiende perfectamente

// Guarda un unico frame, dependiendo del numero del frame lo appendea o
// directamente crea un nuevo archivo. Los frame no tiene porque ser
// consecutivos (skipeamos para "acelerar el video"), pero si crecientes
int save_lammpstrj(char *filename, double* x, double* v, int N, double L, int frame){
  FILE *fp;
  if (frame) fp = fopen(filename, "a"); // Si frame==0, es el primero y por lo tanto
  else fp = fopen(filename, "w");       // tiene que crear un nuevo archivo
  // Header que usa lammps
	fprintf(fp, "ITEM: TIMESTEP\n%d\nITEM: NUMBER OF ATOMS\n%d\nITEM: BOX BOUNDS pp pp pp\n", frame, N);
	for(int l = 0; l < 3; l++){
		fprintf(fp, "0 %lf\n", L); // Limites de la caja en x-y-z
	}
	fprintf(fp, "ITEM: ATOMS id x y z vx vy vz \n"); // "Nombre de las columnas"
	for(int i = 0; i < N; i++){
		fprintf(fp, "%d %lf %lf %lf %lf %lf %lf\n", i, x[3*i], x[3*i+1], x[3*i+2], v[3*i], v[3*i+1], v[3*i+2]);
	}
  fclose(fp);
  return 0;
}

// Funcion que carga un unico frame, el siguiente segun fp
// Uso los fscanf(..) para saltear lineas sin informacion (como el header)
int load_frame(void *fp, double* x, double* v, int N, double *L){
  char buffer[255], *eof;
  int id, frame, N_file;
  eof = fgets(buffer, 255, fp);
  if (eof==NULL){ // Si apunta a NULL, es porque ya leí todos los frames
    return -1;
  }
  id = fscanf(fp, "%d\n", &frame);  // Cargo el frame
  eof = fgets(buffer, 255, fp);
  id = fscanf(fp, "%d\n", &N_file); // Cargo el numero de particulas
  if (N_file != N){ // Se confundieron de archivo, este
    return -2;      // tiene distinto numero de particulas
  }
  for(int l = 0; l < 2; l++){
    eof = fgets(buffer, 255, fp);
  }
  id = fscanf(fp, "0 %lf\n", L); // Cargo la dimension de la caja
  for(int l = 0; l < 2; l++){
    eof = fgets(buffer, 255, fp);
  }
  for(int i = 0; i < N; i++){  // Cargo las posiciones y velocidades
    id = fscanf(fp, "%d %lf %lf %lf %lf %lf %lf\n", &id, x+3*i, x+3*i+1, x+3*i+2, v+3*i, v+3*i+1, v+3*i+2);
  }
  return frame;
}

// Carga un frame especifico de un archivo
int load_lammpstrj(char *filename, double* x, double* v, int N, double *L, int frame){
  FILE *fp = fopen(filename, "r");
  int frame_file = load_frame(fp, x, v, N, L);
  while(frame_file < frame && frame_file >= 0){ // A lo bestia, cargo frames
    frame_file = load_frame(fp, x, v, N, L);    // hasta tener el correcto
  }
  fclose(fp);
  if(frame_file == -1) printf("No existe el frame %d en %s\n", frame, filename);
  if(frame_file == -2) printf("Numero de particulas incompatible\n");
  return frame_file;
}
