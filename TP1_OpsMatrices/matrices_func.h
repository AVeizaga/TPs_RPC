#ifndef matrices_func_h
#define matrices_func_h

#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"


//Prototipos de funciones
int matriz_cargar(int mat[SIZE][SIZE]);
int matriz_imprimir(int mat[SIZE][SIZE]);
int matriz_suma(int matA[SIZE][SIZE], int matB[SIZE][SIZE], int res[SIZE][SIZE]);
int matriz_transpo(int mat[SIZE][SIZE]);
int matriz_escarlar_multi(int mat[SIZE][SIZE], int scalar);
int matriz_multiplicacion(int matA[SIZE][SIZE], int matB[SIZE][SIZE], int res[SIZE][SIZE]);

#endif