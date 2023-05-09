#include "tablero.h"
#include "celda.h"
#include <typeinfo>
#include <iostream>

using namespace std;
int main(){
    Tablero<Celda*>* batallaDigital = new Tablero<Celda*>(50, 50, 50);
    delete batallaDigital;
    return 0;
}