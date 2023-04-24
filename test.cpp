#include "tablero.h"
#include <typeinfo>
#include <iostream>
using namespace std;
int main(){
    Tablero<char*>* poronga = new Tablero<char*>(200, 200, 200);
    cout << typeid(poronga).name();
    delete poronga;
    return 0;
}