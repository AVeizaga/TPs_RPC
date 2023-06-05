#include <iostream>
#include <ginac/ginac.h>
#include <fstream>
#include "spline.h"
using namespace std;
using namespace GiNaC;

/*
void spline_test(){
    int len = 3;
    float x[len] = {-2, 1.5, 5};
    float y[len] = {9.13533528,  2.10668907, 24.4131591};
    float y_d[len] = {-11.86466472, -2.26831093, 73.4131591};

    float res[len - 1][4];

    float a0[1], a1[1], a2[1], a3[1];
    for(int i = 0; i < (len - 1); i++){
        a0[0] = y[i];
        a1[0] = y_d[i];
        a2[0] = -3*y[i] + 3*y[i + 1] -2*y_d[i] - y_d[i + 1];
        a3[0] = 2*y[i] - 2*y[i + 1] + y_d[i] + y_d[i + 1];

        float A = x[i + 1] - x[i];

        float temp[2] = {-x[i]/A, 1/A};
        polinomio<float> t(1, temp);

        polinomio<float> pol_a0(0, a0), pol_a1(0, a1), pol_a2(0, a2), pol_a3(0, a3);
        
        polinomio<float> final;
        final = pol_a0 + pol_a1*t + pol_a2*t*t + pol_a3*t*t*t;

        //res[i][0] = a0 - a1*x[i]/A + a2*pow(x[i], 2)/pow(A, 2) - a3*pow(x[i], 3)/pow(A, 3);
        //res[i][1] = a1/A - 2*a2*x[i]/pow(A, 2) + 3*a3*pow(x[i], 2)/pow(A, 3);

        cout << final <<endl;
    }
}
*/

template <class Q>
void spline_test(){
    int len = 3;
    Q x[len] = {-2, 1.5, 5};
    Q y[len] = {9.13533528,  2.10668907, 24.4131591};
    Q y_d[len] = {-11.86466472, -2.26831093, 73.4131591};

    Q res[len - 1][4];

    Q a0[1], a1[1], a2[1], a3[1];
    for(int i = 0; i < (len - 1); i++){
        Q A = x[i + 1] - x[i];

        a0[0] = y[i];
        a1[0] = y_d[i]*A;
        a2[0] = -3*y[i] + 3*y[i + 1] -2*y_d[i]*A - y_d[i + 1]*A;
        a3[0] = 2*y[i] - 2*y[i + 1] + y_d[i]*A + y_d[i + 1]*A;

        Q temp[2] = {-x[i]/A, 1/A};
        polinomio<Q> t(1, temp);

        polinomio<Q> pol_a0(0, a0), pol_a1(0, a1), pol_a2(0, a2), pol_a3(0, a3);
        cout << pol_a0 <<endl;
        cout << pol_a1 <<endl;
        cout << pol_a2 <<endl;
        cout << pol_a3 <<endl;
        
        polinomio<Q> final, aux;
        aux = pol_a3*t*t;
        aux = aux*t;
        cout << "ok" << endl;
        final = pol_a0 + pol_a1*t + pol_a2*t*t;
        final = final + aux;

        //res[i][0] = a0 - a1*x[i]/A + a2*pow(x[i], 2)/pow(A, 2) - a3*pow(x[i], 3)/pow(A, 3);
        //res[i][1] = a1/A - 2*a2*x[i]/pow(A, 2) + 3*a3*pow(x[i], 2)/pow(A, 3);

        cout << final <<endl;
    }
}

int main(){
    symbol x("x");

    ex func = 1+exp(x)-pow(x, 3);
    spline sp(x, func);
    

    ofstream out;
    out.open("salida.txt");

    sp.generate(out, -2, 5, 6, 10);

    //spline_test<float>();

    return 0;
}