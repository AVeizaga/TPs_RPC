///g++ main.cpp spline.cpp -lginac -lcln
///El ejemplo guarda en salida.txt 100 puntos usando los splines entre 
///-6.8 y 6.8 separado en 39 polinomios.
///Se pueden graficar estos puntos, con el script g_test.py


#include <iostream>
#include <fstream>
#include <string>
#include <ginac/ginac.h>

#include "spline.h"

using namespace std;
using namespace GiNaC;

int main(int argc, char* argv[]){
    //Simbolo y expresion
    symbol x("x");
    ex e = sin(x);

    //Output
    ofstream out;
    out.open("salida.txt");

    //Spline por string
    spline sp(x, "sin(x)");
    sp.set_lims(-6.8, 6.8);
    sp.set_ints(40);

    //Spline por expresion
    spline sp1(x, e, -6.8, 6.8, 40);

    //Guardar datos y comprobar
    sp.save(out, 100);
    cout << sp(2.5) << "\n";
    cout << sp1(2.5) << "\n";
    cout << "sin(2.5) = 0.5984721441039564" << endl;

    out.close();

    return 0;
}