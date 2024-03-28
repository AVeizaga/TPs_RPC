#include <iostream>
#include <fstream>
#include "polinomio.h"
#include <cmath>


int main(){
    polinomio<float> a, b, c, d, e, f, result;

    ifstream pols;
    pols.open("poli.txt");
    ofstream res;
    res.open("res.txt");

    pols >> a;
    pols >> b;
    pols >> c;
    pols >> d;
    pols >> e;
    pols >> f;

    res << a <<endl;
    res << b <<endl;
    res << c <<endl;
    res << d <<endl;
    res << e <<endl;
    res << f <<endl;

    //float ff[3] = {1.0, 1.0, 1.0};
    //polinomio<float> temp(2, ff);
    //temp = a;

    //Suma
    //1-x+10*x^2-5*x^3
    result = a + b;
    res << result <<endl;

    //Resta
    //1-5x-30x^2+5x^3
    result = a - b;
    res << result <<endl;

    //Multiplicacion
    //0.736-1.203*x-210.475*x^2+640.85*x^3+1849.65*x^4-607.35*x^5+295.5*x^6+1000*x^7
    result = a * c;
    res << result <<endl;

    //Division - cociente
    //5+x
    result = d / e;
    res << result <<endl;

    //Division - resto
    //0
    result = d.resto(e);
    res << result << endl;

    //Evaluacion
    //-3
    cout << "Coeficiente 1 de a: ";
    cout << a[1] << endl;
    //-4180.8
    cout << "a evaluado en 20.3: ";
    cout << a(20.3) << endl;

    //Factorizacion
    //Raices en 0.7, -5, 10 y -8
    f.factorizar("factor.txt");

    pols.close();
    res.close();

    return 0;
}
