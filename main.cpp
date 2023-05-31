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
                if(i < k+4 ){
                    batallaDigital->getTData(i, j, k)->setTipo(CAPA_ARENA);
                } else if (i >= k+4){
                    batallaDigital->getTData(i, j, k)->setTipo(CAPA_AGUA);
                }

                if(k > batallaDigital->getTamanioX() / 2){
                    batallaDigital->getTData(i, j, k)->setTipo(CAPA_AIRE);
                }
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
    imprimirBMP(imgSize, &imagen, batallaDigital, getMap());
    imagen.WriteToFile("Partida.bmp");
    delete batallaDigital;
    return 0;
}
