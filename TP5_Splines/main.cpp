#include <iostream>
#include <fstream>
#include <string>
#include <ginac/ginac.h>

#include "spline.h"

using namespace std;
using namespace GiNaC;

int main(int argc, char* argv[]){
    symbol x("x");
    ex e = sin(x);

    ofstream out;
    out.open("salida.txt");

    spline sp(x, e, -4, 4, 10);

    sp.set_lims(-10, 10);
    sp.set_ints(40);

    sp.save(out, 100);

    return 0;
}