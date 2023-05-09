#include "tablero.h"
#include "celda.h"
#include <typeinfo>
#include <iostream>

using namespace std;

void cargarPlano(Tablero<Celda*>* batallaDigital){
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 20; y++) {
            batallaDigital->getTData(x,y,0)->setTipo(TIERRA);
        }
    }
}

int main(){
    Tablero<Celda*>* batallaDigital = new Tablero<Celda*>(20, 20, 20);
    cargarPlano(batallaDigital);
    delete batallaDigital;
    return 0;
}