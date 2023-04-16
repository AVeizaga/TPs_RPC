#ifndef matrix_esp_h
#define matrix_esp_h

#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int row;
    int col;
}Coordinate;

int row(Coordinate c);
int column(Coordinate c);
Coordinate to_coord(int row, int col);

typedef struct{
    Coordinate coord;
    int data;
}Elem;

typedef struct{
    int q_row;  //Cantidad de filas de la matriz
    int q_cols; //Cantidad de columnas de la matriz
    Elem *mat; //Matriz
    int data_size;  //Cantidad de datos actualmente en la matriz
    int ph_size; //Tamaño fisico de la matriz
}Matrix;

Matrix initialize_matrix(int q_row, int q_cols);
bool is_empty(Matrix matrix);
bool is_def(Matrix matrix, Coordinate c);
void set_element(Matrix *matrix, Coordinate c, int val);
void delete_element(Matrix *matrix, Coordinate c);
int get_element(Matrix matrix, Coordinate c);
void free_matrix(Matrix *matrix);
void print_matrix(Matrix matrix);

//Para pruebas
Matrix generate_matrix(int cant_elem);


#endif