#ifndef matrices_func_h
#define matrices_func_h

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int cant_fil, cant_col;
    float **mat;
}Matriz;

//Prototipos de funciones
FILE *archivo_abrir_lectura(const char *argv);
FILE *archivo_abrir_escritura(const char *argv);
void matriz_cargar_archivo(FILE *fptr, Matriz *matriz);
void matriz_imprimir(Matriz matriz);
void matriz_escribir_archivo(FILE *fptr,Matriz matriz);
void matriz_liberar(Matriz matriz);
Matriz matriz_inicializar(int cant_fil, int cant_col);
Matriz matriz_suma(Matriz matA, Matriz matB);
Matriz matriz_transpo(Matriz matriz);
Matriz matriz_multi_escalar(Matriz matriz, int escalar);
Matriz matriz_multiplicacion(Matriz matA, Matriz matB);

float matriz_determinante(Matriz matriz);
void matriz_intercambio_filas(Matriz matriz, int filaA, int filaB);
void matriz_multi_escalar_fila(Matriz matriz, int fila, float escalar);
void matriz_suma_filas_escalar(Matriz matriz, int filaA, int filaB, float escalar);
void matriz_diagonalizacion(Matriz matriz);

#endif