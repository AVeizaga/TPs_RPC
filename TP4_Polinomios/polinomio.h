#ifndef polinomio_h
#define polinomio_h

#include <iostream>
#include <cmath>
#include <cstring>
#include <assert.h>
#include <fstream>
#include <cstdarg>
#include <string>

using namespace std;

//struct pol_division;

template <class T>
class polinomio{
private:
    unsigned int grado;
    T *coefs;

    float relative_error(float old_x, float new_x);
public:
    //Constructores y destructores
    polinomio(unsigned int gra, T *vec);    //Constructor
    polinomio();    //Por defecto, cero
    polinomio(const polinomio & pol);   //Constructor por copia
    ~polinomio();   //Destructor

    //Operaciones basicas
    const polinomio & operator=(const polinomio & pol);  //Igualdad
    polinomio operator+(const polinomio & pol);   //Suma
    polinomio operator-(const polinomio & pol);   //Resta
    polinomio operator*(const polinomio & pol);   //Multiplicacion
    polinomio operator/(const polinomio & q);
    polinomio resto(const polinomio &q);
    
    //Evaluaciones de parametros  
    float operator()(const float val);    //Evaluacion
    T operator[](const int pos);      //Revisar coeficiente

    //Entrada y salida
    template <class Q>
    friend ostream & operator<<(ostream & out, const polinomio<Q> & pol);
    template <class Q>
    friend istream & operator>>(istream & in, polinomio<Q> & pol);

    //Funciones varias
    float raiz(const float a, const float b, const float err, const unsigned int max_iters = 50);
    int get_grado(void);
    void factorizar();
    void factorizar(string filename);
};

//Al final no use la estructura, la division esta separada en
//2 funciones. Tengo que terminar de revisar esto
//template<class Q>
//struct pol_division{
//    class polinomio<Q> resto, cociente;
//};
//
//typedef struct pol_division pol_division;

#include "polinomio.cpp"

#endif  //polinomio_h