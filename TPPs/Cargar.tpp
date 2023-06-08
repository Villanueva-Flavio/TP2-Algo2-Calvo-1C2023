#ifndef __CARGAR_TPP__
#define __CARGAR_TPP__

//#include "Headers/Cargar.h"

#include "../Headers/Tablero.h"
#include "../Headers/Jugador.h"

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

void generarMundo(std::string tipoDeMundo, Tablero<Celda*>* tablero){
    if (tipoDeMundo == "playa"){
        
        cargarPlaya(tablero);
        std::cout << "\nPlaya cargado\n";
    }else if (tipoDeMundo == "mar") {

        cargarMar(tablero);
        std::cout << "\nMar cargado\n";
    }else if (tipoDeMundo == "tierra"){

        cargarTierra(tablero);
        std::cout << "\nTierra cargado\n";
    }else if (tipoDeMundo == "desierto"){

        cargarDesierto(tablero);
        std::cout << "\nDesierto cargado\n";
    }else if (tipoDeMundo == "lago"){

        cargarLago(tablero, tablero->getTamanioX());
        std::cout << "\nLago cargado\n";
    }else if (tipoDeMundo == "rio"){

        cargarRio(tablero, tablero->getTamanioX());
        std::cout << "\nRio cargado\n";
    }    
}

void cargarNombres(Lista<Jugador*>* jugadores,std::string* nombres) {
    jugadores->resetIter();
    for(int i = 0; i < jugadores->getSize(); i++) { // getSize() == cantidadJugadores?
        (jugadores->getLData(jugadores->getIter()))->setNombre(nombres[i]);
        jugadores->iterar(SIGUIENTE);
    }
}

void cargarCantidadFichas(Lista<Jugador*>* jugadores, int numeroDeJugadores){
    jugadores->resetIter();
    Jugador* jugadorActual = nullptr;
    for(int i = 0; i < jugadores->getSize(); i++) {
        jugadorActual = jugadores->getLData(jugadores->getIter());             //tira seg fault en este bucle
        // 2 tipos distintos de armamentos para un total de 8 armamentos por jugador
        jugadorActual->setArmamentos(8);
        // 10 soldados por jugador
        jugadorActual->setSoldados(10);
        // 36 minas en total, 2 para cada ficha
        jugadorActual->setMinas(36);
        jugadores->iterar(SIGUIENTE);
    }    
}

void cargarJugadores(Lista<Jugador*>* jugadores,std::string* nombres, int numeroDeJugadores) {

    std::cout << "\nCargando nombres.\n";
    cargarNombres(jugadores, nombres);
    std::cout << "\nCarga completada\n";

    std::cout << "\nCargando fichas.\n";
    cargarCantidadFichas(jugadores, numeroDeJugadores);
    std::cout << "\nCarga completada\n";
}

bool verificarSolapamientos(Tablero<Celda*>* tablero, int tipoDeFichaActual, std::string tipoMundo, int x, int y, int z) {
    return ((tipoDeFichaActual == 0 && tipoMundo != "mar" && tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 1 && (tipoMundo != "mar" && tipoMundo != "lago") && tablero->getTData(x,y,z-1)->getTipo() != CAPA_AGUA && tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 2 && (tipoMundo != "tierra" && tipoMundo != "desierto") && (tablero->getTData(x,y,z-1)->getTipo() != CAPA_TIERRA && tablero->getTData(x,y,z-1)->getTipo() != CAPA_ARENA && tablero->getTData(x,y,z-1)->getTipo() != CAPA_PASTO) && tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 3 && tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO && tablero->getTData(x,y,z)->getTipo() == CAPA_AIRE) || (tipoDeFichaActual == 4 && (tipoMundo != "tierra" && tipoMundo != "desierto" && tipoMundo != "lago" && tipoMundo != "rio") && tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO && tablero->getTData(x,y,z)->getTipo() == CAPA_AGUA)) ? true : false;
}

int cantidadDistintaDeArmamento(int tipoDeFichaActual){
    return (tipoDeFichaActual == 0) ? 1 : 4 ;
}

int obtenerCantidadesDeFichas(Lista<Jugador*>* jugadores, int tipoDeFichaActual, int jugadorActual) {
    return (tipoDeFichaActual < 1) ? jugadores->getLData(jugadorActual)->getSoldados() : jugadores->getLData(jugadorActual)->getArmamentos() ;
}

void cargarFichas(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, std::string tipoMundo) {
    jugadores->resetIter();
    int x = 0, y = 0, z = 0;
    for(int jugadorActual = 0; jugadorActual < jugadores->getSize(); jugadorActual++){
        jugadores->iterar(SIGUIENTE);
        for (int tipoDeFichaActual = 0; tipoDeFichaActual < 5; tipoDeFichaActual++){
            // 0 soldado, 1 tanque, 2 barcos. El resto en cualquier nivel
            x = rand() % tablero->getTamanioX(), y = rand() % tablero->getTamanioY(), z = (tipoDeFichaActual < 3) ? CAPA_MAXIMA : (rand() % tablero->getTamanioZ()) ;
            for(int j = 0; j < obtenerCantidadesDeFichas(jugadores,tipoDeFichaActual,jugadorActual) / cantidadDistintaDeArmamento(tipoDeFichaActual); j++){ 
                if (verificarSolapamientos(tablero,tipoDeFichaActual,tipoMundo,x,y,z)){
                    tablero->getTData(x,y,z)->getFicha()->setJugadorOwner(jugadorActual);
                } else{
                    j--;
                    x = rand() % tablero->getTamanioX();
                    y = rand() % tablero->getTamanioY();
                    z = (tipoDeFichaActual < 3) ? CAPA_MAXIMA : (rand() % tablero->getTamanioZ());
                }
            }
        }
    }
}

void cargarJuego(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, std::string* nombres, std::string tipoMundo, int numeroDeJugadores) {
    
    std::cout << "\nGenerando mundo.\n";
    generarMundo(tipoMundo, tablero);
    std::cout << "\nGeneracion de mundo completado\n";

    std::cout << "\nCargando jugadores.\n";
    cargarJugadores(jugadores, nombres, numeroDeJugadores);
    std::cout << "\nCarga de jugadores completado\n";

    std::cout << "\nCarga de fichas.\n";
    cargarFichas(tablero,jugadores,tipoMundo);
    std::cout << "\nCarga de fichas completado\n";
}

#endif