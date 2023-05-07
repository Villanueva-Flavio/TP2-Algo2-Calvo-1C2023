#include "tablero.h"
#include "celda.h"
#include <typeinfo>
#include <iostream>

using namespace std;

int main(){
    Tablero<Celda*>* batallaDigital = new Tablero<Celda*>(20, 20, 20);
    delete batallaDigital;
    return 0;
}