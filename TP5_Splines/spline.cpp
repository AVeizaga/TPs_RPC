#include "spline.h"

//Constructor por expresion
spline::spline(const symbol &x, const ex func){
    this->func = func;
    this->x = x;
    this->d_func = this->func.diff(this->x);

    this->n = 2;
    this->lim_inf = 0;
    this->lim_sup = 1;
    this->generate();
}

//Constructor por expresion y datos
spline::spline(const symbol &x, const ex func, double lim_inf, double lim_sup, unsigned int n){
    this->x = x;
    this->func = func;
    this->d_func = this->func.diff(this->x);

    this->lim_inf = lim_inf;
    this->lim_sup = lim_sup;
    this->n = (n < 2) ? 2 : n;
    this->generate();
}

//Constructor por string
spline::spline(const symbol &x, const string func){
    symtab table;
    table["x"] = x;
    this->x = x;

    parser reader(table);
    this->func = reader(func);
    this->d_func = this->func.diff(this->x);

    this->n = 2;
    this->lim_inf = 0;
    this->lim_sup = 1;
    this->generate();
}

//Constructor por string y datos
spline::spline(const symbol &x, const string func, double lim_inf, double lim_sup, unsigned int n){
    symtab table;
    table["x"] = x;
    this->x = x;

    parser reader(table);
    this->func = reader(func);
    this->d_func = this->func.diff(this->x);

    this->lim_inf = lim_inf;
    this->lim_sup = lim_sup;
    this->n = (n < 2) ? 2 : n;
    this->generate();
}

//Destructor
spline::~spline(){
}

//Seteos de datos
//Modificadores
void spline::set_lims(const double inf, const double sup){
    lim_inf = inf;
    lim_sup = sup;
    generate();
}

void spline::set_lim_inf(const double lim){
    lim_inf = lim;
    generate();
}

void spline::set_lim_sup(const double lim){
    lim_sup = lim;
    generate();
}

void spline::set_ints(const unsigned int n){
    this->n = (n < 2) ? 2 : n;
    generate();
}

/// @brief Toma los datos del spline y calcula los polinomios para la aproximacion. Se usan tipo cubic hermit spline.
void spline::generate(){
    //cout << "Lim_Inf: " << this->lim_inf << "\tLim_sup: " << this->lim_sup << "\tPuntos: " << this->n << endl;

    //Comprobar que los limites esten bien
    if(lim_inf >= lim_sup){
        cerr << "Los limites no son apropiados." << endl;
        exit(-1);
    }

    sp.clear(); //Limpiar los valores previos

    //Puntos de x, 'y' y su derivada
    vector<ex> x;
    vector<ex> y;
    vector<ex> y_d;

    //Evaluacion
    for(int i = 0; i < this->n; i++){
        x.push_back(lim_inf + i*(lim_sup - lim_inf)/(n-1));
        y.push_back(evalf(this->func.subs(this->x==x[i])));
        y_d.push_back(evalf(this->d_func.subs(this->x==x[i])));
    }

    //Calculo de splines
    ex a0, a1, a2, a3;
    for(int i = 0; i < (this->n - 1); i++){
        ex A = x[i + 1] - x[i];

        //Coeficientes auxiliares, inversa de la matriz evaluada en 0 y 1, escalado en A
        a0 = y[i];
        a1 = y_d[i]*A;
        a2 = -3*y[i] + 3*y[i + 1] -2*y_d[i]*A - y_d[i + 1]*A;
        a3 = 2*y[i] - 2*y[i + 1] + y_d[i]*A + y_d[i + 1]*A;

        //Escalado de x
        ex t_func = (this->x/A) - x[i]/A;

        //Polinomio
        ex final = a0 + a1*t_func + a2*pow(t_func, 2) + a3*pow(t_func, 3);

        //cout << final <<endl;
        sp.push_back(final);
    }
}

/// @brief Evalua con el polinomio apropiado en val, si se excede del intervalo se usan los polinomios en los limites.
/// @param val Punto donde evaluar
/// @return Devuelve un numeric del punto evaluado
ex spline::operator()(const double val){
    ex res;

    //Elegir el polinomio apropiado
    int index = (int)floor((val - lim_inf)*(n-1)/(lim_sup - lim_inf));
    if(index > (n - 2))
        index = (n - 2);
    else if(index < 0)
        index = 0;

    //Conversion a numeric
    res = evalf(sp[index].subs(this->x == val));
    if(is_a<numeric>(res))
        return res;
    else{
        cerr << "La conversion a numeric en la evaluacion no fue exitosa.\n";
        exit(-1);
    }
}

/// @brief Devuelve el polinomio en la posicion pos. Si se excede el limite se devuelve el modulo de pos.
/// @param pos Posicion del vector
/// @return 
ex spline::operator[](const unsigned int pos){
    return sp[pos%(n - 1)];
}

/// @brief Indica la cantidad de polinomios. Minimo 1.
/// @return n-1
int spline::len(){
    return n-1;
}

/// @brief Almacena en un ostream cant_p de puntos entre los limites inferior y superior.
/// @param out ostream utilizado
/// @param cant_p Cantidad de puntos a guardar
void spline::save(ostream & out, unsigned int cant_p){
    for(int i = 0; i < cant_p; i++){
        out << lim_inf + i*(lim_sup - lim_inf)/cant_p << ", ";
        out << (*this)(lim_inf + i*(lim_sup - lim_inf)/cant_p) << endl;
    }
}