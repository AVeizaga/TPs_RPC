#include "matrix_esp.h"

//Devuelve la componente fila de la coordenada
int row(Coordinate c){
    return c.row;
}

//Devuelve la componente columna de la coordenada
int column(Coordinate c){
    return c.col;
}

//Devuelve una coordena con los datos pasados
Coordinate to_coord(int row, int col){
    Coordinate c;
    c.row = row;
    c.col = col;

    return c;
}

//Inicializa la matriz
Matrix initialize_matrix(int q_row, int q_cols){
    Matrix matrix;
    matrix.q_row = q_row;
    matrix.q_cols = q_cols;

    int inic_size = (matrix.q_row*matrix.q_row)*10/100;
    if(inic_size == 0)
        inic_size = 1;

    matrix.mat = (Elem*) calloc(inic_size, sizeof(Elem));
    if(matrix.mat == NULL){
        fprintf(stderr, "No se pudo reservar memoria para la matriz.\n");
        exit(-1);
    }

    matrix.data_size = 0;
    matrix.ph_size = inic_size;

    return matrix;
}

//Devuelve true si la matriz se encuentra vacia
bool is_empty(Matrix matrix){
    return (matrix.data_size == 0);
}

//Devuelve true si el valor ya estaba definido
bool is_def(Matrix matrix, Coordinate c){
    int high, low, mid;

    //Si la coordenada es mayor a las dimensiones de la matriz retorna falso
    if((matrix.q_cols < column(c)) || (matrix.q_row < row(c))){
        fprintf(stderr, "La coordenada se encuentra fuera de la matriz.\n");
        return false;
    }

    if(is_empty(matrix)){
        return false;
    }
    else{
        low = 0;
        high = matrix.data_size - 1;
        while(low <= high){
            mid = (high + low)/2;

            if(row(matrix.mat[mid].coord)*matrix.q_cols+column(matrix.mat[mid].coord) < row(c)*matrix.q_cols+column(c)){
                low = mid + 1;
            }
            else if(row(matrix.mat[mid].coord)*matrix.q_cols+column(matrix.mat[mid].coord) > row(c)*matrix.q_cols+column(c)){
                high = mid - 1;
            }
            else{
                return true;
            }
        }

    }
    return false;
}

//Devuelve el indice donde se encuentra la coordenada, si no está definido devuelve el indice donde colocarlo
//Se debería usar is_def() antes para saber el contexto del resultado
int where_is(Matrix matrix, Coordinate c){
    int high, low, mid;

    if((matrix.q_cols < column(c)) || (matrix.q_row < row(c))){
        fprintf(stderr, "La coordenada se encuentra fuera de la matriz.\n");
        exit(-1);
    }

    if(is_empty(matrix)){
        return (0);
    }
    else{
        low = 0;
        high = matrix.data_size - 1;
        while(low <= high){
            mid = (high + low)/2;

            if(row(matrix.mat[mid].coord)*matrix.q_cols+column(matrix.mat[mid].coord) < row(c)*matrix.q_cols+column(c)){
                low = mid + 1;
            }
            else if(row(matrix.mat[mid].coord)*matrix.q_cols+column(matrix.mat[mid].coord) > row(c)*matrix.q_cols+column(c)){
                high = mid - 1;
            }
            else{
                return mid;
            }
        }

    }
    return low;
}

//Coloca un nuevo elemento en la matriz o lo reemplaza
void set_element(Matrix *matrix, Coordinate c, int val){
    int index;
    if((matrix->q_cols < column(c)) || (matrix->q_row < row(c))){
        fprintf(stderr, "La coordenada se encuentra fuera de la matriz.\n");
        exit(-1);
    }

    //Seteo cuando el elemento ya estaba definido
    if(is_def(*matrix,c)){
        matrix->mat[where_is(*matrix, c)].data = val;
    }
    //Seteo cuando el elemento no estaba definido
    else{
        index = where_is(*matrix, c);
        //Reviso que haya memoria
        if((matrix->data_size + 1) > (matrix->ph_size)){
            //Reviso que no me paso del maximo tamaño
            if((2 * matrix->ph_size) > (matrix->q_row*matrix->q_cols)){
                matrix->mat = (Elem*) realloc(matrix->mat, matrix->q_row*matrix->q_cols*sizeof(Elem));
                matrix->ph_size = matrix->q_row*matrix->q_cols;
            }
            else{
                matrix->mat = (Elem*) realloc(matrix->mat, 2*matrix->ph_size*sizeof(Elem));
                matrix->ph_size = 2*matrix->ph_size;
            }

            for(int i = (matrix->data_size - 1); i >= index; i--){
                matrix->mat[i + 1] = matrix->mat[i];
            }
            matrix->mat[index].data = val;
            matrix->mat[index].coord.row = row(c);
            matrix->mat[index].coord.col = column(c);
            matrix->data_size++;
        }
        else{
            for(int i = (matrix->data_size - 1); i >= index; i--){
                matrix->mat[i + 1] = matrix->mat[i];
            }
            matrix->mat[index].data = val;
            matrix->mat[index].coord.row = row(c);
            matrix->mat[index].coord.col = column(c);
            matrix->data_size++;
        }
    }
}

//Elimina el elemento en la coordenada c
//Si el elemento no estaba definido la funcion no hace nada
void delete_element(Matrix *matrix, Coordinate c){
    int index;
    
    if((matrix->q_cols < column(c)) || (matrix->q_row < row(c))){
        fprintf(stderr, "La coordenada se encuentra fuera de la matriz.\n");
        exit(-1);
    }

    if(is_def(*matrix, c)){
        index = where_is(*matrix, c);
        for(int i  = index; i < (matrix->data_size - 1); i++){
            matrix->mat[i] = matrix->mat[i + 1];
        }
        matrix->data_size--;
    }
    //Si el elemento no estaba definido continua
}

//Devuelve el elemento de la coordenada c. Si el elemento no estaba definido da error.
int get_element(Matrix matrix, Coordinate c){
    int index;
    if((matrix.q_cols < column(c)) || (matrix.q_row < row(c))){
        fprintf(stderr, "La coordenada se encuentra fuera de la matriz.\n");
        exit(-1);
    }

    if(is_def(matrix, c)){
        index = where_is(matrix, c);
        return matrix.mat[index].data;
    }
    else{
        fprintf(stderr,"El elemento no estaba definido, no se puede devolver elemento.\n");
        exit(-1);
    }
}

//Libera la matriz
void free_matrix(Matrix *matrix){
    matrix->data_size = 0;
    matrix->ph_size = 0;
    matrix->q_cols = 0;
    matrix->q_row = 0;
    free(matrix->mat);
}

//Imprime los elementos definidos de la matriz. Finaliza imprimiendo la cantidad de elementos definidos.
void print_matrix(Matrix matrix){
    for(int i = 0; i < matrix.data_size; i++){
        printf("(%d, %d) = %d\n", row(matrix.mat[i].coord), column(matrix.mat[i].coord),matrix.mat[i].data);
    }
    printf("Cant. elems: %d\n",matrix.data_size);
}

//Funcion para pruebas. Hace cant_elem de inserciones en la matriz matrix
Matrix generate_matrix(int cant_elem){
    int dim_col = 10;
    int dim_fil = 10;
    
    Matrix matrix;
    Coordinate c;
    matrix = initialize_matrix(dim_fil, dim_col);
    for(int i = 0; i < cant_elem; i++){
        c.row = rand()%dim_fil;
        c.col = rand()%dim_col;
        int val = rand()%100;
        set_element(&matrix, c, val);
    }
    return matrix;
}