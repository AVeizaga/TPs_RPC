#ifndef SPLINE_H
#define SPLINE_H

#include <iostream>
#include <ginac/ginac.h>
#include "polinomio/polinomio.h"

using namespace std;
using namespace GiNaC;

class spline{
private:
    ex func;
    ex d_func;
    symbol x;
public:
    spline(const symbol &x, const ex func);
    ~spline();

    void generate(ostream & out, float lim_inf, float lim_sup, int n, int cant_p_int);
};


#endif //SPLINE_H