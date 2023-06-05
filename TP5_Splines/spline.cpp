#include "spline.h"


spline::spline(const symbol &x, const ex func){
    this->func = func;
    this->x = x;
    this->d_func = this->func.diff(this->x);
}

spline::~spline(){
}

/// @brief Genera polinomios de grado 3, tipo cubic hermit spline y pasa los puntos a un ostream
/// @param out Salida para los puntos
/// @param lim_inf Limite inferior para la aproximacion
/// @param lim_sup Limite superior para la aproximacion
/// @param n Cantidad de puntos a separar, n-1 intervalos
/// @param cant_p_int Cantidad de puntos para muestrear de los polinomios resultantes
void spline::generate(ostream & out, float lim_inf, float lim_sup, int n, int cant_p_int){
    float x[n];
    float y[n];
    float y_d[n];

    for(int i = 0; i < n; i++){
        x[i] = lim_inf + i*(lim_sup - lim_inf)/(n-1);
        ex f = evalf(this->func.subs(this->x==x[i]));
        ex d_f = evalf(this->d_func.subs(this->x==x[i]));

        if(is_a<numeric>(f))
            y[i] = (float)ex_to<numeric>(f).to_double();
        else
            exit(-1);
        if(is_a<numeric>(d_f))
            y_d[i] = (float)ex_to<numeric>(d_f).to_double();
        else
            exit(-1);
    }

    float res[n - 1][4];

    float a0[1], a1[1], a2[1], a3[1];
    for(int i = 0; i < (n - 1); i++){
        float A = x[i + 1] - x[i];

        a0[0] = y[i];
        a1[0] = y_d[i]*A;
        a2[0] = -3*y[i] + 3*y[i + 1] -2*y_d[i]*A - y_d[i + 1]*A;
        a3[0] = 2*y[i] - 2*y[i + 1] + y_d[i]*A + y_d[i + 1]*A;

        float temp[2] = {-x[i]/A, 1/A};
        polinomio<float> t(1, temp);

        polinomio<float> pol_a0(0, a0), pol_a1(0, a1), pol_a2(0, a2), pol_a3(0, a3);
        
        polinomio<float> final;
        final = pol_a0 + pol_a1*t + pol_a2*t*t + pol_a3*t*t*t;

        //De la implementacion anterior, se queda por ahora
        //res[i][0] = a0 - a1*x[i]/A + a2*pow(x[i], 2)/pow(A, 2) - a3*pow(x[i], 3)/pow(A, 3);
        //res[i][1] = a1/A - 2*a2*x[i]/pow(A, 2) + 3*a3*pow(x[i], 2)/pow(A, 3);

        cout << final <<endl;
        //out << (n-1)*cant_p_int << "\n";
        for(int j = 0; j < cant_p_int; j++){
            float x_pos = x[i] + j*(x[i + 1] - x[i])/cant_p_int;
            out << x_pos << "\n";
            out << final(x_pos) << "\n";
        }
    }
}

