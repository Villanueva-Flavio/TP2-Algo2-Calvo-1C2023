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

// Dependiendo de la cantidades de fichas se le asignarán al tablero ciertas cantidades de fichas
void cargarFichaDelTipo(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner){
    
    int x, y, z, i = 0; // coordendas, i representa la iteración de la cantidad

    while (i <= cantidadDeCarga){
        x = std::rand()%tablero->getTamanioX()-1;
        y = std::rand()%tablero->getTamanioY()-1;
        z = (tipoDeFicha == SOLDADO || tipoDeFicha == TANQUE || tipoDeFicha == BARCO) ? CAPA_MAXIMA : std::rand()%tablero->getTamanioZ()-1;

        // if (tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO && ((tipoDeFicha == BARCO && tablero->getTData(x,y,CAPA_MAXIMA-1)->getTipo() == CAPA_AGUA) || (tipoDeFicha == SUBMARINO && tablero->getTData(x,y,z)->getTipo() == CAPA_AGUA) || (tipoDeFicha == AVION && tablero->getTData(x,y,z)->getTipo() == CAPA_AIRE) || (tipoDeFicha == SOLDADO && tablero->getTData(x,y,z)->getTipo() == CAPA_AIRE) || (tipoDeFicha == SOLDADO && tablero->getTData(x,y,z)->getTipo() == CAPA_AIRE))){
        if (tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO && tablero->getTData(x,y,z-1)->getTipo() == CAPA_TIERRA){
            tablero->getTData(x,y,z)->getFicha()->setTipo(tipoDeFicha);
            tablero->getTData(x,y,z)->getFicha()->setJugadorOwner(jugadorOwner);
            tablero->getTData(x,y,z)->getFicha()->setNumFicha(i+1);

            std::cout << "Cargado/da en la coordenada (" << x <<", "<< y << ", " << z << ")\n";

            i++; // el incremento está adentro del if porque se necesita que si o si se pueda cargar la ficha en el tablero
        }
    }
}

void cargarFichas(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, std::string tipoMundo) {

    for (int i = 0; i < jugadores->getSize(); i++){

        if (tipoMundo != "mar"){

            std::cout << "\nSoldados del jugador " << i+1 << " \n";
            cargarFichaDelTipo(tablero,jugadores,jugadores->getLData(i)->getSoldados(),SOLDADO,i+1);
            std::cout << "cargados\n";
            
            // std::cout << "\nTanques:";
            // cargarFichaDelTipo(tablero,jugadores,jugadores->getLData(i)->getArmamentos(),TANQUE,0);
            // std::cout << "cargados\n";
        }
        // if (tipoMundo != "tierra" && tipoMundo != "desierto"){

            // std::cout << "\nsubmarinos:";
            // cargarFichaDelTipo(tablero,jugadores,jugadores->getLData(i)->getSoldados(),SUBMARINO,0);
            // std::cout << "cargados\n";

            // std::cout << "\nbarcos:";
            // cargarFichaDelTipo(tablero,jugadores,jugadores->getLData(i)->getSoldados(),BARCO,0);
            // std::cout << "cargados\n";
        // }
        // std::cout << "\nAviones:";
        // cargarFichaDelTipo(tablero,jugadores,jugadores->getLData(i)->getSoldados(),AVION,i);
        // std::cout << "cargados\n";
    }
}

void mostrarDatosDeJugadores(Lista<Jugador*>* jugadores) {
    for (int i = 0; i < jugadores->getSize(); i++){
        std::cout<<"\nEl nombre del jugador "<<i+1<<" es "<<jugadores->getLData(i)->getNombre()<<std::endl;
        std::cout<<"\nTiene "<<jugadores->getLData(i)->getSoldados()<<" soldados"<<std::endl;
        std::cout<<"\nTiene "<<jugadores->getLData(i)->getMinas()<<" minas"<<std::endl;
        std::cout<<"\nTiene "<<jugadores->getLData(i)->getArmamentos()<<" armamentos"<<std::endl;
    }
}

void cargarJuego(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, std::string* nombres, std::string tipoMundo, int numeroDeJugadores) {
    tablero = new Tablero<Celda*>(jugadores->getSize()*6,jugadores->getSize()*6,jugadores->getSize()*6);
    generarMundo(tipoMundo, tablero);

    cargarJugadores(jugadores, nombres);

    // std::cout << "\nFichas:";
    cargarFichas(tablero,jugadores,tipoMundo);
    // std::cout << "cargados\n";


    // std::cout<<"Hay "<<jugadores->getSize()<<" jugadores.\n";
    // std::cin.ignore();
    // 
    // 
    // int a = jugadores->getIter();
    // std::cout<<"El jugador "<< a <<" tiene "<<jugadores->getLData(a)->getSoldados() << " fichas de soldados\n";
    // std::cin.ignore();
    // 
    // 

}