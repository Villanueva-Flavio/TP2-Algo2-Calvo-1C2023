//hacer sleeps y marcar prints
#include "../Headers/tablero.h"
#include "../Headers/celda.h"
#include "../Headers/renderizador.h"
#include <iostream>
using namespace std;

void mostrarJuego(Coordenada imgSize, BMP imagen, Mapa* tablero) {
    imprimirAngulo(imgSize, &imagen, tablero, getMap());
    imagen.WriteToFile("Partida.bmp");
}
1
void cargarPlaya(Mapa* tablero){
    for(int i = 0; i < tablero->getTamanioX(); i++){
        for(int j = 0; j < tablero->getTamanioY(); j++){
            tablero->getTData(i, j, 0)->setTipo(CAPA_TIERRA);
        }
    }
    tablero->getTData(4,4,1)->getFicha().setTipo(SOLDADO); // Cargo por default un soldado
}

string pedirOpcion() {
    string opcion;
    cout << "Escriba el tipo de ficha que desea seleccionar:\n-avion\n-soldado\n-tanque\n-barco\n-submarino\n";
    cin >> opcion;
    return opcion;
}

bool seEncuentraLaFicha(Mapa* tablero, string opcion, int x, int y, int z) {
    bool seEncontro = false;
    if (opcion == "soldado"){
        seEncontro = (tablero->getTData(x,y,z)->getFicha().getTipo() == SOLDADO) ? true : false ;
    }
    else if (opcion == "tanque"){
        seEncontro = (tablero->getTData(x,y,z)->getFicha().getTipo() == TANQUE) ? true : false ;
    }
    else if (opcion == "barco"){
        seEncontro = (tablero->getTData(x,y,z)->getFicha().getTipo() == BARCO) ? true : false ;
    }
    else if (opcion == "avion"){
        seEncontro = (tablero->getTData(x,y,z)->getFicha().getTipo() == AVION) ? true : false ;
    }
    else if (opcion == "submarino"){
        seEncontro = (tablero->getTData(x,y,z)->getFicha().getTipo() == SUBMARINO) ? true : false ;
    }
    return seEncontro;
}

bool buscarFicha(Mapa* tablero){
    string opcion = pedirOpcion();
    bool encontrada = false;
    for (int x = (opcion == "avion") ? 1 : 0; x < tablero->getTamanioX(); x++){
        for(int y = 0; y < tablero->getTamanioY(); y++){
            for(int z = 0; z < tablero->getTamanioZ(); z++){
                // z = (opcion == "soldado" || opcion == "barco" || opcion == "tanque") ? 0 : z ;
                if (seEncuentraLaFicha(tablero, opcion, x, y, z)){
                    encontrada = true;
                    x = tablero->getTamanioX();
                    y = tablero->getTamanioY();
                    z = tablero->getTamanioZ();
                }
                // z = ((!encontrada) && (x == tablero->getTamanioX()-1) && (y == tablero->getTamanioY()-1)) ? tablero->getTamanioZ() : z ;
            }
        }
    }
    if (encontrada){
        cout << "Ficha encontrada\n";
    }else {"Ficha no se encontró\n"}
    return encontrada;
}

int main(){
    int size = 10;
    Coordenada imgSize = {size*100, size*70};
    BMP imagen;
    imagen.SetSize(imgSize.x, imgSize.y);
    Mapa* tablero = new Mapa(size, size, size);
    
    cargarPlaya(tablero);
    bool sas = buscarFicha(tablero);
    mostrarJuego(imgSize, imagen, tablero);

    delete tablero;
    return 0;
}