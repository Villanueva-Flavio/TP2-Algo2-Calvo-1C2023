//hacer sleeps y marcar prints
#include "./Headers/tablero.h"
#include "./Headers/celda.h"
#include "./Headers/renderizador.h"
#include <typeinfo>
#include <iostream>
#include <unistd.h>

using namespace std;

const char MOV_ARRIBA = 'w';
const char MOV_IZQUIERDA = 'a';
const char MOV_ABAJO = 's';
const char MOV_DERECHA = 'd';

void moverJugador(Mapa* batallaDigital){

    char movimiento = ' ';

    cout << "Ingrese un movimiento: \n";
    cin >> movimiento;

    while(movimiento != MOV_ABAJO && movimiento != MOV_ARRIBA && movimiento != MOV_DERECHA && movimiento != MOV_IZQUIERDA){

        cout << "\nEntra al while";            //BORRAR
        cout << "\nIngresa un movimientos valido (W-A-S-D): ";
        cin >> movimiento;
    }

    cout << "Mov ingresado: " << movimiento;

    batallaDigital->getTData(5,5,2)->getFicha()->setTipo(VACIO);
    batallaDigital->getTData(5,5,2)->getFicha()->setJugadorOwner(-1);     //

    switch(movimiento){
        
        case MOV_ARRIBA:
            batallaDigital->getTData(5,5 +3,2)->getFicha()->setTipo(SOLDADO);
            batallaDigital->getTData(5,5 +3,2)->getFicha()->setJugadorOwner(1);         //
            cout << "\nEntra al switch";                            //BORRAR
            break;

    }
}


void cargarPlaya(Mapa* batallaDigital){
    for(int i = 0; i < batallaDigital->getTamanioX(); i++){
        for(int j = 0; j < batallaDigital->getTamanioY(); j++){
            for(int k = 0; k < batallaDigital->getTamanioZ(); k++){
                if(i == 0 || i == batallaDigital->getTamanioX() - 1 || j == 0 || j == batallaDigital->getTamanioY() - 1){
                    batallaDigital->getTData(i, j, k)->setTipo(CAPA_AGUA);
                    if(batallaDigital->getTData(i, j, k)->getFicha()->getTipo() != VACIO){           // 
                        batallaDigital->getTData(i, j, k)->setTipo(CAPA_ARENA);
                        cout << "\n(if de carg)";
                    }
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
    batallaDigital->getTData(1, 1, 1)->setTipo(CAPA_AGUA);

    cargarPlaya(batallaDigital);

    // Coloco un soldado en la posicion 5,5,2 para posteriormente moverlo
    batallaDigital->getTData(5,5,2)->getFicha()->setJugadorOwner(1);
    batallaDigital->getTData(5,5,2)->getFicha()->setTipo(SOLDADO);

    cout << "\nTIPO: " << batallaDigital->getTData(5,5,2)->getFicha()->getTipo();
    

    imprimirAngulo(imgSize, &imagen, batallaDigital, getMap());
    imagen.WriteToFile("Partida.bmp");

    // Muevo al soldado y actualizo los datos
    moverJugador(batallaDigital);

    // Imprimo el mapa con la nueva posicion del soldado
    imprimirAngulo(imgSize, &imagen, batallaDigital, getMap());
    imagen.WriteToFile("Partida.bmp");

    delete batallaDigital;
    return 0;
}
