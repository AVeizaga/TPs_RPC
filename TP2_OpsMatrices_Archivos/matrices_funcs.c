#include "matrices_func.h"

//Abre el archivo pasado en modo lectura
FILE *archivo_abrir_lectura(const char *argv){
    FILE *ptr;

    ptr = fopen(argv, "r");
    if(ptr == NULL){
        fprintf(stderr,"No se pudo abrir el archivo. \n");
        exit(-1);
    }

    return ptr;
}

//Abre el archivo pasado en modo escritura
FILE *archivo_abrir_escritura(const char *argv){
    FILE *ptr;

    ptr = fopen(argv, "w");
    if(ptr == NULL){
        fprintf(stderr,"No se pudo abrir el archivo. \n");
        exit(-1);
    }

    return ptr;
}

//Carga a la matriz pasada los contenidos del archivo
void matriz_cargar_archivo(FILE *fptr, Matriz *matriz){
    
    fscanf(fptr, "%d %d", &matriz->cant_fil, &matriz->cant_col);     //Lectura de las filas y columnas 

    *matriz = matriz_inicializar(matriz->cant_fil, matriz->cant_col);

    //Cargar la matriz del archivo
    for(int i = 0; i < matriz->cant_fil; i++){
        for(int j = 0; j < matriz->cant_col; j++){
            if(fscanf(fptr, "%d", &matriz->mat[i][j]) != 1){
                fprintf(stderr,"El archivo no tiene la cantidad de datos correcta.\n");
                exit(-1);
                }
        }
    }
}

//Imprime los contenidos de la matriz
void matriz_imprimir(Matriz matriz){
    for(int i = 0; i < matriz.cant_fil; i++){
        for(int j = 0; j < matriz.cant_col; j++){
            printf("%d\t", matriz.mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Devuelve una matriz de las dimensiones dadas
Matriz matriz_inicializar(int cant_fil, int cant_col){
    Matriz matriz;

    matriz.cant_fil = cant_fil;
    matriz.cant_col = cant_col;
    
    matriz.mat =(int**) calloc(matriz.cant_fil, sizeof(int*));
    if(matriz.mat == NULL){
        fprintf(stderr,"No se pudo reservar memoria para la matriz.\n");
        exit(-1);
    }
    for(int i = 0; i < matriz.cant_fil; i++){
        matriz.mat[i] = (int*) calloc(matriz.cant_col, sizeof(int));
        if(matriz.mat[i] == NULL){
            fprintf(stderr,"No se pudo reservar memoria para la matriz.\n");
            exit(-1);
        }
    }    

    return matriz;
}

//Libera el espacio de memoria que ocupaba la matriz
void matriz_liberar(Matriz matriz){
    for(int i = 0; i < matriz.cant_fil; i++){
        free(matriz.mat[i]);
    }
    free(matriz.mat);
}

//Devuelve la suma de matrices
Matriz matriz_suma(Matriz matA, Matriz matB){
    Matriz res;
    if((matA.cant_fil != matB.cant_fil) || (matA.cant_col != matB.cant_col)){
        fprintf(stderr, "Las matrices tienen dimensiones distintas, no se puede realizar la suma.\n");
        exit(-1);
    }

    res = matriz_inicializar(matA.cant_fil, matA.cant_col);
    
    for(int i = 0; i < res.cant_fil; i++){
        for(int j = 0; j < res.cant_col; j++){
            res.mat[i][j] = matA.mat[i][j] + matB.mat[i][j];
        }
    }

    return res;
}

//Escribe en el archivo los contenidos de la matriz
void matriz_escribir_archivo(FILE *fptr,Matriz matriz){
    fprintf(fptr, "%d \t%d \n", matriz.cant_fil, matriz.cant_col);
    for(int i = 0; i < matriz.cant_fil; i++){
        for(int j = 0; j < matriz.cant_col; j++){
            fprintf(fptr, "%d \t",matriz.mat[i][j]);
        }
        fprintf(fptr, "\n");
    }
}

//Devuelve la transpuesta de la matriz
Matriz matriz_transpo(Matriz matriz){
    Matriz res = matriz_inicializar(matriz.cant_col, matriz.cant_fil);

    for(int i = 0; i < matriz.cant_fil; i++){
        for(int j = 0; j < matriz.cant_col; j++){
            res.mat[j][i] = matriz.mat[i][j];
        }
    }

    return res;
}

//Devuelve la multiplicacion de matriz por escalar
Matriz matriz_multi_escalar(Matriz matriz, int escalar){
    Matriz res = matriz_inicializar(matriz.cant_fil, matriz.cant_col);

    for(int i = 0; i < matriz.cant_fil; i++){
        for(int j = 0; j < matriz.cant_col; j++){
            res.mat[i][j] = escalar * matriz.mat[i][j];
        }
    }

    return res;
}

//Devuelve la multiplicacion por matrices
Matriz matriz_multiplicacion(Matriz matA, Matriz matB){
    Matriz res = matriz_inicializar(matA.cant_fil, matB.cant_col);

    if(matA.cant_col != matB.cant_fil){
        fprintf(stderr, "Las dimensiones de las matrices no son compatibles, no se puede realizar la multiplicacion.\n");
        exit(-1);
    }

    for(int i = 0; i < matA.cant_fil; i++){
        for(int j = 0; j < matB.cant_col; j++){
            res.mat[i][j] = 0;
            for(int k = 0; k < matA.cant_col; k++){
                res.mat[i][j] += matA.mat[i][k] * matB.mat[k][j];
            }
        }
    }

    return res;
}