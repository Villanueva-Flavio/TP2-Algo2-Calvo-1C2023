#include "tablero.h"

int main(){
    Tablero<int*>* poronga = new Tablero<int*>(20, 20, 20);
    delete poronga;
    return 0;
}