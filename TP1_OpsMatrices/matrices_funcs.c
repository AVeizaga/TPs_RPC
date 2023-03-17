#include "matrices_func.h"

//Carga en cada elemento de la matriz i+2j
int matriz_cargar(int mat[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            mat[i][j] = i + j*2;
        }
    }
    return 0;
}

//Imprime la matriz
int matriz_imprimir(int mat[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

//Suma res=matA + matB
int matriz_suma(int matA[SIZE][SIZE], int matB[SIZE][SIZE], int res[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            res[i][j] = matA[i][j] + matB[i][j];
        }
    }
    return 0;
}

//Transpone la matriz mat
int matriz_transpo(int mat[SIZE][SIZE]){
    int temp;

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(i > j){
                temp = mat[i][j];
                mat[i][j] = mat[j][i];
                mat[j][i] = temp;
            }
        }
    }
    return 0;
}

//Multiplicacion por un escalar
int matriz_escarlar_multi(int mat[SIZE][SIZE], int scalar){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            mat[i][j] = scalar * mat[i][j];
        }
    }
    return 0;
}

//Multiplicacion de matrices res=matA*matB
int matriz_multiplicacion(int matA[SIZE][SIZE], int matB[SIZE][SIZE], int res[SIZE][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            res[i][j] = 0;
            for(int k = 0; k < SIZE; k++){
                res[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }

    return 0;
}