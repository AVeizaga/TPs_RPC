#ifndef SPLINE_H
#define SPLINE_H

#include <iostream>
#include <ginac/ginac.h>
#include "polinomio/polinomio.h"
#include <vector>

using namespace std;
using namespace GiNaC;

class spline{
private:
    //Polinomios y datos del intervalo
    vector<ex> sp;  //Polinomios
    unsigned int n; //n-1 = cantidad de intervalos
    double lim_inf; //Limite inferior
    double lim_sup; //Limite superior
    
    //Variable, funcion y derivada. Para las evaluaciones
    symbol x;
    ex func;
    ex d_func;
public:
    spline(const symbol &x, const ex func);
    spline(const symbol &x, const ex func, double lim_inf, double lim_sup, unsigned int n);
    ~spline();

    //Modificadores
    void set_lims();
    void set_lim_inf();
    void set_lim_sup();
    void set_ints();


    void generate(ostream & out, double lim_inf, double lim_sup, int n, int cant_p_int);

    ex operator()(double val);  //Evalua en val con el polinomio apropiado
    ex operator[](int pos); //Devuelve el polinomio en pos
    int len();  //Devuelve la cantidad de polinomios, o numero de intervalos+1
};


#endif //SPLINE_H