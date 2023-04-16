#include "matrix_func.h"

//Devuelve la suma de las matrices matA y matB
Matrix matriz_suma(Matrix matA, Matrix matB){
    Matrix res;
    Coordinate c;
    if((matA.q_row != matB.q_row) || (matA.q_cols != matB.q_cols)){
        fprintf(stderr, "Las matrices tienen dimensiones distintas, no se puede realizar la suma.\n");
        exit(-1);
    }

    res = initialize_matrix(matA.q_row, matA.q_cols);
    
    for(int i = 0; i < res.q_row; i++){
        for(int j = 0; j < res.q_cols; j++){
            c = to_coord(i, j);
            int valA = is_def(matA, c) ? get_element(matA, c) : 0 ;
            int valB = is_def(matB, c) ? get_element(matB, c) : 0 ;
            if((valA + valB) != 0)
                set_element(&res, c, valA + valB);
        }
    }

    return res;
}

//Devuelve la transpuesta de la matriz
Matrix matriz_transpo(Matrix matrix){
    Matrix res = initialize_matrix(matrix.q_cols, matrix.q_row);

    for(int i = 0; i < matrix.q_row; i++){
        for(int j = 0; j < matrix.q_cols; j++){
            if(is_def(matrix, to_coord(i, j))){
                set_element(&res, to_coord(j, i), get_element(matrix, to_coord(i, j)));
            }
        }
    }

    return res;
}
