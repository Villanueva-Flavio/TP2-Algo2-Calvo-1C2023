#include "tablero.h"
#include <typeinfo>
#include <iostream>
using namespace std;
int main(){
    Tablero<char*>* falo = new Tablero<char*>(50, 50, 50);
    cout << typeid(falo).name() << endl;
    delete falo;
    return 0;
}