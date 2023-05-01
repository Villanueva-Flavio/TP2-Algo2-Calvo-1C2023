#include "tablero.h"
#include <typeinfo>
#include <iostream>
using namespace std;

int main(){
    Tablero<char*>* tablero = new Tablero<char*>(20, 20, 20);
    cout << typeid(tablero).name() << endl;
    delete tablero;
    return 0;
}