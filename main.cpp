#include "./Headers/tablero.h"
#include "./Headers/celda.h"
#include <iostream>
using namespace std;

void cargarMapa(Tablero<Celda*>* tablero){
    for(int i = 0; i < tablero->getTamanioX(); i++){
        for(int j = 0; j < tablero->getTamanioY(); j++){
            tablero->getTData(i, j, 0)->setTipo(CAPA_TIERRA);
        }
    }
    tablero->getTData(0,0,0)->getFicha()->setTipo(SOLDADO);
}

string pedirOpcion() {
    string opcion;
    cout << "Escriba el tipo de ficha que desea seleccionar:\n-avion\n-soldado\n-tanque\n-barco\n-submarino\n";
    cin >> opcion;
    return opcion;
}

bool seEncuentraLaFicha(Tablero<Celda*>* tablero, string opcion, int x, int y, int z) {
    bool seEncontro = false;
    if (opcion == "soldado"){
        seEncontro = (tablero->getTData(x,y,z)->getFicha()->getTipo() == SOLDADO) ? true : false ;
    }
    else if (opcion == "tanque"){
        seEncontro = (tablero->getTData(x,y,z)->getFicha()->getTipo() == TANQUE) ? true : false ;
    }
    else if (opcion == "barco"){
        seEncontro = (tablero->getTData(x,y,z)->getFicha()->getTipo() == BARCO) ? true : false ;
    }
    else if (opcion == "avion"){
        seEncontro = (tablero->getTData(x,y,z)->getFicha()->getTipo() == AVION) ? true : false ;
    }
    else if (opcion == "submarino"){
        seEncontro = (tablero->getTData(x,y,z)->getFicha()->getTipo() == SUBMARINO) ? true : false ;
    }
    return seEncontro;
}

bool buscarFicha(Tablero<Celda*>* tablero){
    string opcion = pedirOpcion();
    int nivelX = 1;
    int nivelZ = 1;
    bool encontrada = false;
    for (int x = (opcion == "avion") ? nivelX : 0; x < tablero->getTamanioX(); x++){ // Se inicializa x siempre en el nivel del aire si es que se eligió buscar una cosa de ahí
        for(int y = 0; y < tablero->getTamanioY(); y++){
            for(int z = 0; z < tablero->getTamanioZ(); z++){
                if (seEncuentraLaFicha(tablero,opcion,x,y,z)){
                    encontrada = true;
                    x = tablero->getTamanioX();
                    y = tablero->getTamanioY();
                    z = tablero->getTamanioZ();
                }
                z = (z >= nivelZ) ? tablero->getTamanioZ() : z; // Se corta la iteración de nivel si z vale el nivel límite o por encima de tierra
            }
        }
    }
    return encontrada;
}

int main(){
    int size = 10;
    Tablero<Celda*>* tablero = new Tablero<Celda*>(size, size, size);
    cargarMapa(tablero);
    if (buscarFicha(tablero)){
        cout << "¡Encontrada!\n";
    }
    else {
        cout << "¡Inexistente!\n";
    }
    delete tablero;
    return 0;
}