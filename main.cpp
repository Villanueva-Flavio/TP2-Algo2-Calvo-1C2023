//hacer sleeps y marcar prints
#include "./Headers/tablero.h"
#include "./Headers/celda.h"
#include "./Headers/renderizador.h"
#include <typeinfo>
#include <iostream>
#include <unistd.h>

using namespace std;

void cargarPlaya(Mapa* batallaDigital){
    for(int i = 0; i < batallaDigital->getTamanioX(); i++){
        for(int j = 0; j < batallaDigital->getTamanioY(); j++){
            for(int k = 0; k < batallaDigital->getTamanioZ(); k++){
                if(i == 0 || i == batallaDigital->getTamanioX() - 1 || j == 0 || j == batallaDigital->getTamanioY() - 1){
                    Celda* celda = new Celda();
                    celda->setTipo(CAPA_ARENA);
                    batallaDigital->setTData(i, j, k, celda);
                }
                //cout << batallaDigital->getTData(0, 0, 0)->getTipo() << " y la capa arena es: " << CAPA_ARENA << endl;
            }
        }
    }
}

void loadCeldas(Mapa* batallaDigital){
    for(int i = 0; i < batallaDigital->getTamanioX(); i++){
        for(int j = 0; j < batallaDigital->getTamanioY(); j++){
            for(int k = 0; k < batallaDigital->getTamanioZ(); k++){
                Celda* celda = new Celda();
                batallaDigital->setTData(i, j, k, celda);
            }
        }
    }
}

void unloadCeldas(Mapa* batallaDigital){
    for(int i = 0; i < batallaDigital->getTamanioX(); i++){
        for(int j = 0; j < batallaDigital->getTamanioY(); j++){
            for(int k = 0; k < batallaDigital->getTamanioZ(); k++){
                delete batallaDigital->getTData(i, j, k);
            }
        }
    }
}

int main(){
    int size = 20;
    Coordenada imgSize = {size*100, size*70};
    Mapa* batallaDigital = new Mapa(size, size, size);
    BMP imagen;
    imagen.SetSize(imgSize.x, imgSize.y);
    
    loadCeldas(batallaDigital);
    cargarPlaya(batallaDigital);
    //batallaDigital->getTData(1, 1, 1)->setTipo(CAPA_ARENA);
    //cout << batallaDigital->getTData(1, 1, 1)->getTipo() << " y la capa arena es: " << CAPA_ARENA << endl;
    unloadCeldas(batallaDigital);
    //imprimirAngulo(imgSize, &imagen, *batallaDigital, getMap());
    //imagen.WriteToFile("Partida.bmp");
    delete batallaDigital;
    return 0;
}