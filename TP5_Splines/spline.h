#ifndef SPLINE_H
#define SPLINE_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ginac/ginac.h>

using namespace std;
using namespace GiNaC;

class spline{
private:
    //Polinomios y datos del intervalo
    vector<ex> sp;  //Polinomios
    unsigned int n; //n cantidad de puntos, n - 1 = cantidad de intervalos
    double lim_inf; //Limite inferior
    double lim_sup; //Limite superior
    
    //Variable, funcion y derivada. Para las evaluaciones
    symbol x;
    ex func;
    ex d_func;

    //Generar los splines
    void generate();
public:
    //Constructores
    spline(const symbol &x, const ex func);
    spline(const symbol &x, const ex func, double lim_inf, double lim_sup, unsigned int n);
    spline(const symbol &x, const string func);
    spline(const symbol &x, const string func, double lim_inf, double lim_sup, unsigned int n);

    ~spline();

    //Modificadores
    void set_lims(const double inf, const double sup);  //Cambiar los limites
    void set_lim_inf(const double lim);                 //Cambiar limite inferior
    void set_lim_sup(const double lim);                 //Cambiar limite superior
    void set_ints(const unsigned int n);                //Cambiar cantidad de intervalos

    ex operator()(const double val);  //Evalua en val con el polinomio apropiado
    ex operator[](const unsigned int pos); //Devuelve el polinomio en pos
    int len();  //Devuelve la cantidad de polinomios, o numero de intervalos

    //Exportar a archivo
    void save(ostream & out, unsigned int cant_p);
};


#endif //SPLINE_H