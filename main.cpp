#include "./Headers/tablero.h"
#include "./Headers/celda.h"
#include "./Headers/renderizador.h"
#include <iostream>
using namespace std;

struct coordenadas{int x; int y; int z;};

void cargarMapa(Tablero<Celda*>* tablero){
    for(int x = 0; x < tablero->getTamanioX(); x++){
        for(int y = 0; y < tablero->getTamanioY(); y++){
            if (x < (tablero->getTamanioX()/1.5)){
                tablero->getTData(x, y, 0)->setTipo(CAPA_TIERRA);
                tablero->getTData(x, y, 1)->setTipo(CAPA_PASTO);
            }else {
                tablero->getTData(x, y, 0)->setTipo(CAPA_AGUA);
                tablero->getTData(x, y, 1)->setTipo(CAPA_AGUA);
            }
        }
    }
    tablero->getTData(2,2,1)->getFicha()->setTipo(SOLDADO);
    tablero->getTData(2,2,1)->getFicha()->setNumFicha(1);
    tablero->getTData(2,2,1)->setTipo(CAPA_ARENA);
}

string pedirOpcion() {
    string opcion;
    cout << "Escriba el tipo de ficha que desea seleccionar:\n-avion\n-soldado\n-tanque\n-barco\n-submarino\n";
    cin >> opcion;
    return opcion;
}

int pedirEnumeracion() {
    int opcion;
    cout << "Ahora por favor elija el número de ficha que quiere buscar, esto para diferenciarla de las otras.\n-";
    cin >> opcion;
    return opcion;
}

bool seEncuentraLaFicha(Tablero<Celda*>* tablero, string opcion, int enumeracionFicha, int x, int y, int z) {
    bool seEncontro = false;
    if (opcion == "soldado"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == SOLDADO) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }
    else if (opcion == "tanque"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == TANQUE) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }
    else if (opcion == "barco"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == BARCO) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }
    else if (opcion == "avion"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == AVION) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }
    else if (opcion == "submarino"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == SUBMARINO) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }
    return seEncontro; 
}
 
// Faltan refinar algunas cosas de busqueda
void buscarCoordenadasFicha(coordenadas* coorFicha, Tablero<Celda*>* tablero){
    string tipoFicha = pedirOpcion();
    int enumeracionFicha = pedirEnumeracion();
    int nivelX = 1;
    int nivelZ = 1;
    for (int x = (tipoFicha == "avion") ? nivelX : 0; x < tablero->getTamanioX(); x++){ // Se inicializa x siempre en el nivel del aire si es que se eligió buscar una cosa de ahí
        for(int y = 0; y < tablero->getTamanioY(); y++){
            for(int z = 0; z < tablero->getTamanioZ(); z++){
                if (seEncuentraLaFicha(tablero,tipoFicha,enumeracionFicha,x,y,z)){
                    *coorFicha = {x,y,z};
                    x = tablero->getTamanioX();
                    y = tablero->getTamanioY();
                    z = tablero->getTamanioZ();
                }
                // z = (z >= nivelZ) ? tablero->getTamanioZ() : z; // Se corta la iteración de nivel si z vale el nivel límite o por encima de tierra
            }
        }
    }
}

void pedirMovimiento(char* movimiento){
    cout << "Ingrese el movimiento:\n-Frontal y tracero: W y S\nLaterales: A y D\n[ ";
    cin >> *movimiento;
}

void moverLongitudinalmente(char movimiento, Tablero<Celda*>* tablero, coordenadas fichaActual){
    Celda auxiliar;
    if (movimiento == 'W'){
        if ((fichaActual.x + 1) < tablero->getTamanioX()){
            system("clear");
            cout << "\n(" << fichaActual.x + 1 << fichaActual.y << fichaActual.z << ")\n";
            auxiliar = *tablero->getTData((fichaActual.x + 1),(fichaActual.y),(fichaActual.z));
            *tablero->getTData((fichaActual.x + 1),(fichaActual.y),(fichaActual.z)) = *tablero->getTData((fichaActual.x),(fichaActual.y),(fichaActual.z)); 
            *tablero->getTData((fichaActual.x),(fichaActual.y),(fichaActual.z)) = auxiliar; 
        }
    }
    else if (movimiento == 'S'){
        if ((fichaActual.x - 1) >= 0){
            system("clear");
            cout << "\n(" << fichaActual.x - 1 << fichaActual.y << fichaActual.z << ")\n";
            auxiliar = *tablero->getTData((fichaActual.x - 1),(fichaActual.y),(fichaActual.z));
            *tablero->getTData((fichaActual.x - 1),(fichaActual.y),(fichaActual.z)) = *tablero->getTData((fichaActual.x),(fichaActual.y),(fichaActual.z)); 
            *tablero->getTData((fichaActual.x),(fichaActual.y),(fichaActual.z)) = auxiliar; 
        }
    }
}

void moverLateralmente(char movimiento, Tablero<Celda*>* tablero, coordenadas fichaActual){
    Celda auxiliar;
    if (movimiento == 'D'){
        if ((fichaActual.y + 1) < tablero->getTamanioY()){
            system("clear");
            cout << "\n(" << fichaActual.x << fichaActual.y + 1 << fichaActual.z << ")\n";
            auxiliar = *tablero->getTData((fichaActual.x),(fichaActual.y + 1),(fichaActual.z)); 
            *tablero->getTData((fichaActual.x),(fichaActual.y + 1),(fichaActual.z)) = *tablero->getTData((fichaActual.x),(fichaActual.y),(fichaActual.z));
            *tablero->getTData((fichaActual.x),(fichaActual.y),(fichaActual.z)) = auxiliar;
        }
    }
    else if (movimiento == 'A'){
        if ((fichaActual.y - 1) >= 0){
            system("clear");
            cout << "\n(" << fichaActual.x << fichaActual.y - 1 << fichaActual.z << ")\n";
            auxiliar = *tablero->getTData((fichaActual.x),(fichaActual.y - 1),(fichaActual.z)); 
            *tablero->getTData((fichaActual.x),(fichaActual.y - 1),(fichaActual.z)) = *tablero->getTData((fichaActual.x),(fichaActual.y),(fichaActual.z));
            *tablero->getTData((fichaActual.x),(fichaActual.y),(fichaActual.z)) = auxiliar;
        }      
    }
}

void moverFicha(Tablero<Celda*>* tablero) {
    char movimiento;
    coordenadas fichaActual;
    buscarCoordenadasFicha(&fichaActual,tablero);
    pedirMovimiento(&movimiento);
    moverLongitudinalmente(movimiento,tablero,fichaActual);
    moverLateralmente(movimiento,tablero,fichaActual);
    fichaActual = fichaActual;
}

int main(){
    bool seguir = false;
    string cortar = "";

    int size = 20;
    Coordenada imgSize = {size*100, size*70};
    BMP imagen;
    imagen.SetSize(imgSize.x, imgSize.y);
    
    Tablero<Celda*>* tablero = new Tablero<Celda*>(size, size, size);
    cargarMapa(tablero);
    while (!seguir){
        imprimirAngulo(imgSize, &imagen, tablero, getMap());
        imagen.WriteToFile("Partida.bmp");
        moverFicha(tablero);
        imprimirAngulo(imgSize, &imagen, tablero, getMap());
        imagen.WriteToFile("Partida.bmp");
        cout << "\nSeguir?\n-";
        cin >> cortar;
        seguir = (cortar == "c") ? true : false;
    }
    delete tablero;
    return 0;
}