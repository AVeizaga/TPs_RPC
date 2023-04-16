#include "matrix_esp.h"
#include "matrix_func.h"

int main(int argc, const char *argv[]){
    srand(time(NULL));

    Matrix matrix, matrix2, res;
    matrix = generate_matrix(20);
    matrix2 = generate_matrix(20);

    print_matrix(matrix);
    print_matrix(matrix2);

    res =  matriz_transpo(matrix);
    print_matrix(res);
    free_matrix(&res);
    res = matriz_suma(matrix, matrix2);
    print_matrix(res);

    free_matrix(&matrix);
    free_matrix(&matrix2);
    free_matrix(&res);

    return 0;
}
