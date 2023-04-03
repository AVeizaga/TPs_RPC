#include "matrices_func.h"

/*---------------------
El orden de los parametros es por ejemplo ./a.out matriz1.txt matriz2.txt matriz_salida.txt
Multiples resultados se pueden escribir en un mismo archivo de salida
Luego de cada resultado se deberia usar matriz_liberar() para evitar leaks de memoria
---------------------*/


int main(int argc, const char *argv[]){
    Matriz matA, matB, res;

    FILE *fptr_entradaA, *fptr_entradaB, *fptr_salida;   //Punteros a archivos de entrada y salida

    //Revisa si la cantidad de parametros es correcta
    if(argc != 4){
        fprintf(stderr, "Cantidad incorrecta de parametros. \n");
        exit(-1);
    }

    //Apertura de archivos
    fptr_entradaA = archivo_abrir_lectura(argv[1]);
    fptr_entradaB = archivo_abrir_lectura(argv[2]);
    fptr_salida = archivo_abrir_escritura(argv[3]);

    //Cargar las matrices de entrada
    matriz_cargar_archivo(fptr_entradaA, &matA);
    matriz_cargar_archivo(fptr_entradaB, &matB);
    matriz_imprimir(matA);
    matriz_imprimir(matB);

    matriz_diagonalizacion(matA);
    matriz_imprimir(matA);

    printf("%f\n", matriz_determinante(matB));

    //Liberar matrices
    matriz_liberar(matA);
    matriz_liberar(matB);
    //matriz_liberar(res);


    //Cierre de archivos
    fclose(fptr_entradaA);
    fclose(fptr_entradaB);
    fclose(fptr_salida);

    return 0;
}
