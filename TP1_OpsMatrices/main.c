#include "matrices_func.h"

int main(int argc, const char *argv[]){
    int matriz[SIZE][SIZE];
    int matriz2[SIZE][SIZE];
    int res[SIZE][SIZE];

    matriz_cargar(matriz);
    matriz_cargar(matriz2);

    matriz_imprimir(matriz);
    //matriz_imprimir(matriz2);

    matriz_suma(matriz,matriz2,res);
    matriz_imprimir(res);
    matriz_imprimir(matriz);
    matriz_imprimir(matriz2);

    return 0;
}
