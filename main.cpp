//hacer sleeps y marcar prints
#include "./Headers/tablero.h"
#include "./Headers/celda.h"
#include "./Headers/renderizador.h"
#include <typeinfo>
#include <iostream>
#include <unistd.h>

using namespace std;
typedef Tablero<Celda> Mapa;

void cargarPlaya(Mapa* batallaDigital){
    for(int i = 0; i < batallaDigital->getTamanioX(); i++){
        for(int j = 0; j < batallaDigital->getTamanioY(); j++){
            for(int k = 0; k < batallaDigital->getTamanioZ(); k++){
                batallaDigital->getTData(i, j, k).setTipo(k > (batallaDigital->getTamanioZ() / 2)? CELDA_AIRE : (batallaDigital->getTamanioX() < batallaDigital->getTamanioZ() - 4) ? CELDA_AGUA : CELDA_TIERRA);
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
    cargarPlaya(batallaDigital);
    imprimirAngulo(IZQUIERDA, imgSize, &imagen, *batallaDigital, getMap());
    sleep(1);
    cout << "Angulo 2" << endl;
    imprimirAngulo(DERECHA, imgSize, &imagen, *batallaDigital, getMap());
    imprimirAngulo(ATRAS, imgSize, &imagen, *batallaDigital, getMap());
    imagen.WriteToFile("Partida.bmp");
    //delete batallaDigital;
    return 0;
}