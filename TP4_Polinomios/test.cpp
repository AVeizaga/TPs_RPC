#include <iostream>
#include <fstream>
#include <cstring>
#include <assert.h>

using namespace std;

int main(){
    fstream myfile;
    myfile.open ("poli.txt");
    
    char buffer[2];
    int vals[5];

    myfile >> vals[0];
    myfile >> vals[1];
    myfile >> vals[2];
    myfile >> buffer;
    //assert(strcmp(buffer, "+") || strcmp(buffer, "-"));

    cout << vals[2];
    cout << buffer;

    return 0;
}
