#include <iostream>
#include "celda.h"
#include "tablero.h"
using namespace std;

// typedef struct coordenada{
//     int x;
//     int y;
//     int z;
// };

// void cargarFicha(Tablero<Celda*>* juego) {
//     juego->getTData(0,0,0)->getFicha().setTipo(SOLDADO); // El soldado pertenece a la celda que se encuentra en (0,0,0)
// }

// string pedirTipo(){
//     string tipo = (string)NULL;
//     cout << "Qué tipo de ficha busca?\n-";
//     cin >> tipo;
//     return tipo;
// }

// bool esDelTipoFicha(string tipo, Tablero<Celda*>* juego){
//     bool esDelTipo = false;
//     string nombresFichas[] = {"soldado","tanque","avion","barco","submarino"};
//     int longitud = sizeof(nombresFichas) / sizeof(string);
//     for (int i; i < longitud; i++){
//         if(tipo == nombresFichas[i]){

//         }
//     }
//     if (tipo == "soldado"){
//         esDelTipo = true;
//     }
//     else if(tipo == "tanque"){
//         esDelTipo = true;
//     }
//     else if(tipo == "avion"){
//         esDelTipo = true;
//     }
//     else if(tipo == "barco"){
//         esDelTipo = true;
//     }
//     else if(tipo == "submarino"){ // else solo es igual a que todo lo que sea basura es válido
//         esDelTipo = true;
//     }
//     return esDelTipo;
// }

// void obtenerPosicionSoldado(coordenada* posicionSoldado, Tablero<Celda*>* juego) {
//     string tipo;
//     for (int x; x < juego->getTamanioX(); x++){
//         for (int y; y < juego->getTamanioY(); y++){
//             for (int z; z < juego->getTamanioZ(); z++){
//                 *posicionSoldado = {x,y,z};
//             }
//         }
//     }
// }

// void seleccionarFicha(Tablero<Celda*>* juego){
//     string tipo = pedirTipo();
//     coordenada posicionSoldado;
//     if (tipo == "soldado"){
//         obtenerPosicionSoldado(&posicionSoldado, juego);
//     }
// }

void cargarTablero(Tablero<Celda*>* juego){
    Celda* punteroCelda;
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            for (int k = 0; k < 20; k++){
                punteroCelda = juego->getTData(i,j,k);
                punteroCelda->setTipo(TIERRA);
            }
        }
    }
}

int main() {
    Tablero<Celda*>* juego = new Tablero<Celda*>(20, 20, 20);
    //cargarTablero(juego);
    Celda* punteroCelda = juego->getTData(0,0,0);
    Celda* celptr = new Celda;
    juego->setTData(0,0,0, celptr);
    cout << juego->getTData(0,0,0)->getTipo() << endl;
    delete juego;
    return 0;
}







    // cargarFicha(juego);
    // seleccionarFicha(juego);