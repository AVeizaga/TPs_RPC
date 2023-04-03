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
            if(fscanf(fptr, "%f", &matriz->mat[i][j]) != 1){
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
            printf("%f\t", matriz.mat[i][j]);
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
    
    matriz.mat =(float**) calloc(matriz.cant_fil, sizeof(float*));
    if(matriz.mat == NULL){
        fprintf(stderr,"No se pudo reservar memoria para la matriz.\n");
        exit(-1);
    }
    for(int i = 0; i < matriz.cant_fil; i++){
        matriz.mat[i] = (float*) calloc(matriz.cant_col, sizeof(float));
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
            fprintf(fptr, "%f \t",matriz.mat[i][j]);
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

float matriz_determinante(Matriz matriz){
    float det = 1;

    if(matriz.cant_fil != matriz.cant_col){
        fprintf(stderr, "La matriz no es cuadrada, no se puede calcular el determinante.\n");
        exit(-1);
    }

    for(int i = 0; i < matriz.cant_fil; i++){
        if(i == 0){
            int count = 0;
            float pivot = matriz.mat[count][i];
            while(pivot == 0 && count < matriz.cant_fil-1){
                count++;
                pivot = matriz.mat[count][i];
            }
            
            if(i != count){
                matriz_intercambio_filas(matriz, i, count);
                det *= -1;
            }
        }

        if(matriz.mat[i][i] != 0){
            for(int j = 0; j < matriz.cant_fil; j++){
                if(j != i){
                    matriz_suma_filas_escalar(matriz, j, i, -1*matriz.mat[j][i]/matriz.mat[i][i]);
                }
            }
        }
        else
            return 0;
        
        det *= matriz.mat[i][i];
    }
    return det;
}

void matriz_intercambio_filas(Matriz matriz, int filaA, int filaB){
    float *temp;
    
    temp = matriz.mat[filaA];
    matriz.mat[filaA] = matriz.mat[filaB];
    matriz.mat[filaB] = temp;
}

void matriz_multi_escalar_fila(Matriz matriz, int fila, float escalar){
    for(int j = 0; j < matriz.cant_col; j++){
        matriz.mat[fila][j] = escalar * matriz.mat[fila][j];
    }
}

void matriz_suma_filas_escalar(Matriz matriz, int filaA, int filaB, float escalar){
    for(int j = 0; j < matriz.cant_col; j++){
        matriz.mat[filaA][j] += escalar * matriz.mat[filaB][j];
    }
}

void matriz_diagonalizacion(Matriz matriz){
    int dig;
    if(matriz.cant_fil < matriz.cant_col)
        dig = matriz.cant_fil;
    else
        dig = matriz.cant_col;

    for(int i = 0; i < dig; i++){
        if(i == 0){
            int count = 0;
            float pivot = matriz.mat[count][i];
            while(pivot == 0 && count < matriz.cant_fil-1){
                count++;
                pivot = matriz.mat[count][i];
            }
            
            matriz_intercambio_filas(matriz, i, count);
        }

        if(matriz.mat[i][i] != 0){
            for(int j = 0; j < matriz.cant_fil; j++){
                if(j != i){
                    matriz_suma_filas_escalar(matriz, j, i, -1*matriz.mat[j][i]/matriz.mat[i][i]);
                }
            }
        }

    }

}