//#include "Headers/Cargar.h"
#include "./Headers/Tablero.h"
#include "./Headers/Jugador.h"

#include <cstdlib>
#include <ctime>

#include <cmath>
#include <string>


const int CAPA_MAXIMA = 5;

void cargarPlaya(Tablero<Celda*>* tablero) {
    for(int i = 0; i < tablero->getTamanioX(); i++){
        for(int j = 0; j < tablero->getTamanioY(); j++){
            for(int k = 0; k < tablero->getTamanioZ(); k++){
                if(i < k+4 ){
                    tablero->getTData(i, j, k)->setTipo(CAPA_ARENA);
                } else if (i >= k+4){
                    tablero->getTData(i, j, k)->setTipo(CAPA_AGUA);
                }

                if(k > tablero->getTamanioX() / 2){
                    tablero->getTData(i, j, k)->setTipo(CAPA_AIRE);
                }
            }
        }
    }
}

void cargarMar(Tablero<Celda*>* tablero) {
    for (int i = 0; i < tablero->getTamanioX(); i++){
        for (int j = 0; j < tablero->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                tablero->getTData(i,j,k)->setTipo(CAPA_AGUA);
            }
        }
    }    
}

void cargarTierra(Tablero<Celda*>* tablero) {
    for (int i = 0; i < tablero->getTamanioX(); i++){
        for (int j = 0; j < tablero->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                if (k < CAPA_MAXIMA-1){
                    tablero->getTData(i,j,k)->setTipo(CAPA_PASTO);
                }else {
                    tablero->getTData(i,j,k)->setTipo(CAPA_TIERRA);
                }                
            }
        }
    }
}

void cargarDesierto(Tablero<Celda*>* tablero) {
    for (int i = 0; i < tablero->getTamanioX(); i++){
        for (int j = 0; j < tablero->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                tablero->getTData(i,j,k)->setTipo(CAPA_ARENA);
            }
        }
    }
}

bool verificarOpcion(std::string tipoDeMundo){
    bool opcionVerificada = false;
    if (tipoDeMundo == "playa" || tipoDeMundo == "mar" || tipoDeMundo == "tierra" || tipoDeMundo == "desierto" || tipoDeMundo == "rio" || tipoDeMundo == "lago"){
        opcionVerificada = true;
    }
    return opcionVerificada;
}

bool noEsOrillaDelLago(Tablero<Celda*>* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    double radioAjustado = 1+(0.285*(pow(size/4,1/2.5)));
    double radio = pow(x-mapa->getTamanioX()/2, 2) + (pow(y-mapa->getTamanioY()/2, 2)) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio <= pow(size,radioAjustado)){
        orilla = true;
    }
    return orilla;
}

void cargarLago(Tablero<Celda*>* mapa, int size) {
    for(int x = 0; x < mapa->getTamanioX(); x++) {
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < CAPA_MAXIMA; z++) {
                if (noEsOrillaDelLago(mapa,x,y,z,size)){
                    mapa->getTData(x,y,z)->setTipo(CAPA_AGUA);
                } else {
                    if (z < CAPA_MAXIMA) mapa->getTData(x,y,z)->setTipo(CAPA_TIERRA);
                    mapa->getTData(x,y,CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
                }
                mapa->getTData(x,y,0)->setTipo(CAPA_ARENA);
            }
        }
    }
}

bool noEsOrillaDelRio(Tablero<Celda*>* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    double radioAjustado = 1+(0.227*(pow(size/4,1/2.5)));
    double radio = pow(y-mapa->getTamanioY()/2, 2) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio <= pow(size,radioAjustado)){
        orilla = true;
    }
    return orilla;
}

void cargarRio(Tablero<Celda*>* mapa, int size) {
    for(int x = 0; x < mapa->getTamanioX(); x++) {
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < CAPA_MAXIMA; z++) {
                if (noEsOrillaDelRio(mapa,x,y,z,size)){
                    mapa->getTData(x,y,z)->setTipo(CAPA_AGUA);
                } else {
                    if (z < CAPA_MAXIMA) mapa->getTData(x,y,z)->setTipo(CAPA_TIERRA);
                    mapa->getTData(x,y,CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
                }
                mapa->getTData(x,y,0)->setTipo(CAPA_ARENA);
            }
        }
    }
}
s
void generarMundo(std::string tipoDeMundo, Tablero<Celda*>* tablero){
    (tipoDeMundo == "playa" && tipoDeMundo != "mar") ? : ;
    () ? : ;
    () ? : ;
    () ? : ;
    if (tipoDeMundo == "playa"){
        cargarPlaya(tablero);
    }else if (tipoDeMundo == "mar") {
        cargarMar(tablero);
    }else if (tipoDeMundo == "tierra"){
        cargarTierra(tablero);
    }else if (tipoDeMundo == "desierto"){
        cargarDesierto(tablero);
    }else if (tipoDeMundo == "lago"){
        cargarLago(tablero, tablero->getTamanioX());
    }else if (tipoDeMundo == "rio"){
        cargarRio(tablero, tablero->getTamanioX());
    }    
}

void cargarNombres(Lista<Jugador*>* jugadores,std::string* nombres) {
    for(int i = 0; i < jugadores->getSize(); i++) {
        jugadores->getLData(i)->setNombre(nombres[i]);
    }
}

void cargarCantidadFichas(Lista<Jugador*>* jugadores){
    Jugador* jugadorActual = nullptr;
    for(int i = 0; i < jugadores->getSize(); i++) {
        jugadorActual = jugadores->getLData(i);          
        jugadorActual->setArmamentos(2);
        jugadorActual->setSoldados(5);
        jugadorActual->setMinas(30);
    }    
}

void cargarJugadores(Lista<Jugador*>* jugadores,std::string* nombres) {
    cargarNombres(jugadores, nombres);
    cargarCantidadFichas(jugadores);
}

void cargarFichaDelTipo(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner){
    int x, y, z, i = 0, a = 0;

    while (i <= cantidadDeCarga){
        x = std::rand()%(tablero->getTamanioX()-1);
        y = std::rand()%(tablero->getTamanioY()-1);
        z = (tipoDeFicha == SOLDADO || tipoDeFicha == TANQUE || tipoDeFicha == BARCO) ? CAPA_MAXIMA : std::rand()%(tablero->getTamanioZ()-1);
        a = (tipoDeFicha == SOLDADO || tipoDeFicha == TANQUE || tipoDeFicha == BARCO) ? -1 : 0;

        if (tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO && ((tipoDeFicha == BARCO && tablero->getTData(x,y,CAPA_MAXIMA-1)->getTipo() == CAPA_AGUA) || (tipoDeFicha == SUBMARINO && tablero->getTData(x,y,z)->getTipo() == CAPA_AGUA) || (tipoDeFicha == AVION && tablero->getTData(x,y,z)->getTipo() == CAPA_AIRE) || (tipoDeFicha == SOLDADO && tablero->getTData(x,y,z)->getTipo() == CAPA_AIRE) || (tipoDeFicha == SOLDADO && tablero->getTData(x,y,z)->getTipo() == CAPA_AIRE))){
            tablero->getTData(x,y,z)->getFicha()->setTipo(tipoDeFicha);
            tablero->getTData(x,y,z)->getFicha()->setJugadorOwner(jugadorOwner);
            tablero->getTData(x,y,z)->getFicha()->setNumFicha(i+1);
            i++;
        }
    }
}

void cargarFichas(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, std::string tipoMundo) {

    for (int i = 0; i < jugadores->getSize(); i++){
        if (tipoMundo != "mar" && i < jugadores->getSize()){
            cargarFichaDelTipo(tablero,jugadores,jugadores->getLData(i)->getSoldados(),SOLDADO,i+1);
            cargarFichaDelTipo(tablero,jugadores,jugadores->getLData(i)->getArmamentos(),TANQUE,i+1);
        }
        if (tipoMundo != "tierra" && tipoMundo != "desierto"){
            cargarFichaDelTipo(tablero,jugadores,jugadores->getLData(i)->getSoldados(),SUBMARINO,i+1);
            cargarFichaDelTipo(tablero,jugadores,jugadores->getLData(i)->getSoldados(),BARCO,i+1);

        }
        cargarFichaDelTipo(tablero,jugadores,jugadores->getLData(i)->getSoldados(),AVION,i+1);
    }
}

void cargarJuego(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, std::string* nombres, std::string tipoMundo, int numeroDeJugadores) {
    tablero = new Tablero<Celda*>(jugadores->getSize()*6,jugadores->getSize()*6,jugadores->getSize()*6);
    generarMundo(tipoMundo, tablero);
    cargarJugadores(jugadores, nombres);
    cargarFichas(tablero,jugadores,tipoMundo);
}