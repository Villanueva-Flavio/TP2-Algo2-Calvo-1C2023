#include "./Headers/tablero.h"
#include "./Headers/celda.h"
#include "./Headers/renderizador.h"
#include <typeinfo>
#include <iostream>

using namespace std;
typedef Tablero<Celda> Mapa;

void cargarPlaya(Mapa* batallaDigital){
    for(int i = 0; i < batallaDigital->getTamanioX(); i++){
        for(int j = 0; j < batallaDigital->getTamanioY(); j++){
            for(int k = 0; k < batallaDigital->getTamanioZ(); k++){
                // batallaDigital->getTData(i, j, k).setTipo(k > (batallaDigital->getTamanioZ() / 2)? AIRE : (batallaDigital->getTamanioX() < batallaDigital->getTamanioZ() - 4) ? AGUA : TIERRA);
            }
        }
    }
}

int main(){
    Mapa* batallaDigital = new Mapa(20, 20, 20);
    cargarPlaya(batallaDigital);
    
    delete batallaDigital;
    return 0;
}