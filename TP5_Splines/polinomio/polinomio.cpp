#include "polinomio.h"

/// @brief Funcion privada para calcular el error relativo, usada en biseccion
template <class T>
float polinomio<T>::relative_error(float old_x, float new_x){
    return 100*abs((new_x - old_x)/new_x);
}

template <class T>
polinomio<T>::polinomio(unsigned int gra, T *vec){
    if(grado < 0)
        grado = 0;
    else
        grado = gra;
    coefs = new T[grado+1];
    if(coefs == NULL){
        cerr << "No se pudo reservar memoria." << endl;
        exit(-1);
    }
    for(int i = 0; i <= grado; i++){
        coefs[i] = vec[i];
    }
}

template <class T>
polinomio<T>::polinomio(){
    grado = 0;
    coefs = new T[1];
    if(coefs == NULL){
        cerr << "No se pudo reservar memoria." << endl;
        exit(-1);
    }
    coefs[0] = 0;
}

template <class T>
polinomio<T>::polinomio(const polinomio<T> & pol){
    grado = pol.grado;
    coefs = new T[grado+1];
    if(coefs == NULL){
        cerr << "No se pudo reservar memoria." << endl;
        exit(-1);
    }
    for(int i = 0; i <= grado; i++){
        coefs[i] = pol.coefs[i];
    }
}

template <class T>
polinomio<T>::~polinomio(){
    delete[] coefs;
}

template <class T>
const polinomio<T> & polinomio<T>::operator=(const polinomio & pol){
    delete[] coefs;
    grado = pol.grado;
    coefs = new T[grado + 1];
    if(coefs == NULL){
        cerr << "No se pudo reservar memoria." << endl;
        exit(-1);
    }
    for(int i = 0; i <= grado; i++){
        coefs[i] = pol.coefs[i];
    }

    return pol;
}

template <class T>
polinomio<T> polinomio<T>::operator+(const polinomio & pol){
    T *temp;
    int grado_sum, grado_min;

    grado_sum  = (grado > pol.grado) ? grado : pol.grado;
    grado_min = (grado > pol.grado) ? pol.grado : grado;

    temp = new T[grado_sum];
    if(temp == NULL){
        cerr << "No se pudo reservar memoria." << endl;
        exit(-1);
    }

    for(int i = 0; i <= grado_sum; i++){
        if(i <= grado_min)
            temp[i] = coefs[i] + pol.coefs[i];
        else{
            if(grado_sum == grado)
                temp[i] = coefs[i] + 0;
            else
                temp[i] = 0 + pol.coefs[i];
        }
    }

    polinomio<T> suma(grado_sum, temp);

    delete[] temp;
    return suma;
}

template <class T>
polinomio<T> polinomio<T>::operator-(const polinomio & pol){
    T *temp;
    int grado_sum, grado_min;

    grado_sum  = (grado > pol.grado) ? grado : pol.grado;
    grado_min = (grado > pol.grado) ? pol.grado : grado;

    temp = new T[grado_sum];
    if(temp == NULL){
        cerr << "No se pudo reservar memoria." << endl;
        exit(-1);
    }

    for(int i = 0; i <= grado_sum; i++){
        if(i <= grado_min)
            temp[i] = coefs[i] - pol.coefs[i];
        else{
            if(grado_sum == grado)
                temp[i] = coefs[i] - 0;
            else
                temp[i] = 0 - pol.coefs[i];
        }
    }

    polinomio<T> suma(grado_sum, temp);

    delete[] temp;
    return suma;
}

template <class T>
polinomio<T> polinomio<T>::operator*(const polinomio<T> & pol){
    T *temp;
    int max_grado = grado + pol.grado;

    temp = new T[max_grado + 1];
    if(temp == NULL){
        cerr << "No se pudo reservar memoria." << endl;
        exit(-1);
    }

    for(int i = 0; i < max_grado; i++){
        temp[i] = 0;
    }

    for(int i = 0; i <= grado; i++){
        for(int j = 0; j <= pol.grado; j++){
            temp[i+j] += coefs[i]*pol.coefs[j];
        }
    }

    polinomio<T> mult(max_grado, temp);

    delete[] temp;
    return mult;
}

template <class T>
polinomio<T> polinomio<T>::operator/(const polinomio & q){
    polinomio p, res;
    T *cociente;
    int index_cociente;

    p = *this;
    if(p.grado >= q.grado){
        cociente  = new T[p.grado - q.grado + 1];
        if(cociente == NULL){
            cerr << "No se pudo reservar memoria." << endl;
            exit(-1);
        }
        index_cociente = p.grado - q.grado;
        while(index_cociente >= 0){
            if(q.coefs[q.grado] == 0){
                cerr << "Division por cero" <<endl;
                exit(-1);
            }
            cociente[index_cociente] = p.coefs[index_cociente + q.grado]/q.coefs[q.grado];

            for(int i = 0; i <= q.grado; i++){
                p.coefs[index_cociente + i] -= cociente[index_cociente]*q.coefs[i];
            }
            index_cociente--;
        }
        int temp_grado = p.grado;
        while(temp_grado > 0 && p.coefs[temp_grado] == 0)
            temp_grado--;

        polinomio c(p.grado - q.grado, cociente);
        polinomio r(temp_grado, p.coefs);

        delete[] cociente;
        res = c;
    }
    else{
        cerr << "Division invalida." << endl;
        exit(-1);
    }
    return res;
}

template <class T>
polinomio<T> polinomio<T>::resto(const polinomio &q){
    polinomio p, res;
    T *cociente;
    int index_cociente;

    p = *this;
    if(p.grado >= q.grado){
        cociente  = new T[p.grado - q.grado + 1];
        if(cociente == NULL){
            cerr << "No se pudo reservar memoria." << endl;
            exit(-1);
        }
        index_cociente = p.grado - q.grado;
        while(index_cociente >= 0){
            if(q.coefs[q.grado] == 0){
                cerr << "Division por cero" <<endl;
                exit(-1);
            }
            cociente[index_cociente] = p.coefs[index_cociente + q.grado]/q.coefs[q.grado];

            for(int i = 0; i <= q.grado; i++){
                p.coefs[index_cociente + i] -= cociente[index_cociente]*q.coefs[i];
            }
            index_cociente--;
        }
        int temp_grado = p.grado;
        while(temp_grado > 0 && p.coefs[temp_grado] == 0)
            temp_grado--;

        polinomio c(p.grado - q.grado, cociente);
        polinomio r(temp_grado, p.coefs);

        delete[] cociente;
        res = r;
    }
    else{
        cerr << "Division invalida." << endl;
        exit(-1);
    }
    return res;
}

/*
//Division implementada usando las funciones de polinomios, en vez de por manipulacion
//de vectores
template <class T>
polinomio polinomio<T>::operator/(const polinomio & q){
    polinomio division;
    polinomio p = *this;
    polinomio c(p.grado - q.grado);

    if(p.grado >= q.grado){
        float *cociente  = new float[p.grado - q.grado + 1];
        int index_cociente = p.grado - q.grado;
        while(index_cociente >= 0){
            for(int i = 0; i <= q.grado; i++){
                cociente[i] = 0;
            }
            cociente[index_cociente] = p.coefs[index_cociente + q.grado]/q.coefs[q.grado];

            polinomio pol(index_cociente, cociente);
            c = c+pol;

            p = p - pol*q;
            index_cociente--;
        }   
        division = c;
        delete[] cociente;
    }
    return division;
}
*/

template <class T>
float polinomio<T>::operator()(const float val){
    float res = 0;
    for(int i = 0; i <= grado; i++)
        res += coefs[i]*pow(val, i);

    return res;
}

template <class T>
T polinomio<T>::operator[](const int pos){
    return coefs[pos%(grado+1)];
}

template <class Q>
ostream & operator<< (ostream & out, const polinomio<Q> & pol){
    out << pol.grado << " ";

    for(int i = 0; i <= pol.grado; i++){
        if(pol.coefs[i] >= 0){
            if(i != 0)
                out << "+" << pol.coefs[i] << "*x^" << i;
            else
                out << pol.coefs[i];
            }
        else{
            if(i == 0)
                out << pol.coefs[i];
            else
                out << pol.coefs[i] << "*x^" << i;
        }
    }

    return out;
}

template <class Q>
istream & operator>>(istream & in, polinomio<Q> & pol){
    delete[] pol.coefs;
    in >> pol.grado;
    pol.coefs = new Q[pol.grado];
    if(pol.coefs == NULL){
        cerr << "No se pudo reservar memoria." << endl;
        exit(-1);
    }

    in >> pol.coefs[0];
    for(int i = 1; i <= pol.grado; i++){
        char buffer;
        int temp;
        in >> pol.coefs[i];
        
        in >> buffer;
        assert(buffer == '*');
        in >> buffer;
        assert(buffer == 'x');
        in >> buffer;
        assert(buffer == '^');
        in >> temp; //Para descartar el grado
    }
    return in;
}

template <class T>
float polinomio<T>::raiz(const float a, const float b, const float err, const unsigned int max_iters){
    float pos, neg;
    float rel_err;
    float x_new, x_old;
    int iters;

    if( (*this)(a)*(*this)(b) < 0){ //Un valor positivo y negativo
        if( (*this)(a) > 0){    //Se encuentra cual es cada uno
            pos = a;
            neg = b;
        }
        else{
            pos = b;
            neg = a;
        }

        iters = 0;
        x_new = neg;
        rel_err = 100;
        while(iters < max_iters && rel_err > err){
            x_old = x_new;
            x_new = (pos + neg)/2;
            iters++;
            if(x_new != 0)
                rel_err = relative_error(x_old, x_new);
            if( (*this)(pos)*(*this)(x_new) > 0)
                pos = x_new;
            else if((*this)(pos)*(*this)(x_new) < 0)
                neg = x_new;
            else
                rel_err = 0;
        }
    }
    else{
        cerr << "Los valores no corresponden a un intervalo apropiado." << endl;
    }
    return x_new;
}

template <class T>
int polinomio<T>::get_grado(void){
    return grado;
}

//Solo sirve para polinomios de grado 2, falta implementar para grado 3
template <class T>
void polinomio<T>::factorizar(){
    if(grado > 2){
        cerr << "El grado del polinomio es mayor a 2, se necesitan intervalos para poder efectuar la factorizacion." << endl;
    }

    if(grado == 2){
        T a = coefs[0];
        T b = coefs[1];
        T c = coefs[2];

        float sol1 = (-b+sqrt(pow(b, 2)-4*a*c))/(2*a);
        float sol2 = (-b-sqrt(pow(b, 2)-4*a*c))/(2*a);

        T temp[2];
        temp[1] = 1;
        temp[0] = -sol1;
        polinomio<float> res1(1, temp);
        temp[0] = -sol2;
        polinomio<float> res2(1, temp);
        cout << res1 << endl;
        cout << res2 << endl;
    }
}

//La funcion recibe el nombre del archivo e imprime los polinomios de grado 1 que
//conforman al polinomio, la funcion no corrobora si las raices son correctas
//Formato de archivo:
//grado
//error maximo
//cantidad de iteraciones maximas
//int_a1 int_a2
//int_b1 int b2
//etc
//No pude dejar la funcion como quería, por ahora solo imprime los valores
template <class T>
void polinomio<T>::factorizar(string filename){
    ifstream in;
    in.open(filename);

    int cant;
    float err;
    float max_iters;
    float a,b;
    polinomio resto = *this;

    in >> cant;
    in >> err;
    in >> max_iters;
    if(cant > grado){
        cerr << "La cantidad de intervalos es mayor que la cantidad de raices." << endl;
        exit(-1);
    }
    
    for(int i = 0; i < cant; i++){
        in >> a;
        in >> b;
        float raiz = resto.raiz(a, b, err, max_iters);
        float temp[2] = {-raiz, 1};
        polinomio factor(1, temp);
        resto = resto/factor;
        cout << factor << endl;
    }

    cout << resto << endl;
}