#include "./Headers/Carta.h"
#include "./Headers/tablero.h"
#include "./Headers/celda.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;


Carta::Carta(TipoCarta carta) {
    
    this->activa = true;
    this->radioAccion = NULL;
    this->cantidadBombas = NULL;

    switch(carta){
        case AVION_RADAR:
            this->carta = AVION_RADAR;
            break;
        case ATAQUE_QUIMICO:
            this->carta = ATAQUE_QUIMICO;
            break;
        case BOMBARDEO:
            this->carta = BOMBARDEO;
            break;
        case BARCO_MISIL:
            this->carta = BARCO_MISIL;
            break;
        case OMITIR_TURNO:
            this->carta = OMITIR_TURNO;
            break;
        case ESCUDO:
            this->carta = ESCUDO;
            break;
    }
}

 void Carta::usarCarta(bool &atributoJugador){
    
    this->activa = false;

    switch(this->carta){
        case OMITIR_TURNO:
            //se pasa por parametros jugador continuo
            activarAtributosJugador(atributoJugador);
            break;
        case ESCUDO:
            activarAtributosJugador(atributoJugador);
            break;
    }
} 
template <class Celda> 
 void Carta::usarCarta(Tablero<Celda> &tablero, int x, int y, int z){

    this->activa = false;

    switch(this->carta){
        case AVION_RADAR:
            this->radioAccion = 8;
            obtenerReporte(tablero,x,y,z);
            break;
        case ATAQUE_QUIMICO:
            this->radioAccion = 5;
            inactivarCeldas(tablero,x,y,z);
            break;
        case BOMBARDEO:
            this->radioAccion = 5;
            this->cantidadBombas = 4;
            bombardearCeldas(tablero,x,y,z);
            break;
        case BARCO_MISIL:
            lanzarMisil(tablero, x , y, z);
            break;
    }
}

TipoCarta Carta::getTipoCarta() {
    return this->carta;
}

bool Carta::getCartaActiva() {
    return this->cartaActiva;
}
template <class Celda> 
void Carta::inactivarCeldas(Tablero<Celda> &tablero, int x, int y, int z){

    // Falta reactivar celdas dependiendo del radio 
    int &radio = this->radioAccion; 
    string reporte = "";

    for (int n= x - radio; n < x + radio ; n++){
        for (int m= y - radio; m < y + radio ; m++){
            for (int l = z - radio; l < z + radio ; l++){

                if(tablero->inRange(n,m,l)){

                    if(tablero->getTData(n,m,l)->getFicha()->getTipo() == VACIO){
                        tablero->getTData(n,m,l)->setEstado(false); 
                    }else{
                        int owner = tablero->getTData(n,m,l)->getFicha()->getJugadorOwner();
                        string contenido = this->getStringTipoFicha(tablero->getTData(n,m,l)->getFicha()->getTipo());
                        reporte = reporte + "(" + to_string(n) + ","+ to_string(m) + ","+ to_string(l) + ") - " + contenido + " " + to_string(owner) + "/";
                        
                        tablero->getTData(n,m,l)->setEstado(false);
                    }
                }
        
            }
        }
    }

    this->imprimirReporte(reporte);
}
template <class Celda> 
void Carta::bombardearCeldas(Tablero<Celda> &tablero, int x, int y, int z){

    int randomX, randomY, randomZ;
    int &radio = this->radioAccion; 
    string reporte = "";

    int limiteSuperiorX = x + radio;
    int limiteSuperiorY = y + radio;
    int limiteSuperiorZ = z + radio;

    int limiteInferiorX = x -radio ;
    int limiteInferiorY = y - radio;
    int limiteInferiorZ = z - radio;

    for(int i= 0; i<this->cantidadBombas; i++){

        randomX = limiteInferiorX + rand() % limiteSuperiorX;
        randomY = limiteInferiorY + rand() % limiteSuperiorY;
        randomZ = limiteInferiorZ + rand() % limiteSuperiorZ;

        if(tablero->inRange(randomX,randomY,randomZ)){

            int owner = tablero->getTData(randomX,randomY,randomZ)->getFicha()->getJugadorOwner();
            string contenido = this->getStringTipoFicha(tablero->getTData(randomX,randomY,randomZ)->getFicha()->getTipo());
            reporte = reporte + "(" + to_string(randomX) + ","+ to_string(randomY) + ","+ to_string(randomZ) + ") - " + contenido + " " + to_string(owner) + "/";
            
            tablero->getTData(randomX,randomY,randomZ)->setEstado(false);
            
        }
    }

    this->imprimirReporte(reporte);
}

template <class Celda> 
void Carta::obtenerReporte(Tablero<Celda> &tablero, int x, int y, int z){
    int &radio = this->radioAccion; 
    string reporte = "";

    for (int n= x - radio; n < x + radio ; n++){
        for (int m= y - radio; m < y + radio ; m++){
            for (int l = z - radio; l < z + radio ; l++){

                if(tablero->inRange(n,m,l)){

                    if(tablero->getTData(n,m,l)->getFicha()->getTipo() != VACIO){
                        int owner = tablero->getTData(n,m,l)->getFicha()->getJugadorOwner();
                        string contenido = this->getStringTipoFicha(tablero->getTData(n,m,l)->getFicha()->getTipo());
                        reporte = reporte + "(" + to_string(n) + ","+ to_string(m) + ","+ to_string(l) + ") - " + contenido + " " + to_string(owner) + "/";
                    }
                }
        
            }
        }
    }
    this->imprimirReporte(reporte);
}

template <class Celda> 
void Carta::lanzarMisil(Tablero<Celda> &tablero,  int x, int y, int z){
    
    if(tablero->inRange(x,y,z)){

        int owner = tablero->getTData(x,y,z)->getFicha()->getJugadorOwner();
        string contenido = this->getStringTipoFicha(tablero->getTData(x,y,z)->getFicha()->getTipo());
        string reporte = "(" + to_string(x) + ","+ to_string(y) + ","+ to_string(z) + ") - " + contenido + " " + to_string(owner) + "/"; 
        tablero->getTData(x,y,z)->setEstado(false);
        this->imprimirReporte(reporte);
    }
    
}

void Carta::activarAtributosJugador(bool &atributoJugador){
    if(!atributoJugador){
        atributoJugador = true;
    }
} 

void Carta::imprimirReporte(string reporte){

    string txtName = "cartaReporte.txt";
    ofstream file;

    file.open(txtName.c_str(), fstream::out);

    for(int i=0; i < reporte.size() ; i++){

        //47-> Codigo ANSI para (/)
        if (reporte[i] != 47) {
            file << reporte[i];
            
        }else{
            file <<"\n";
        }
    }

    file.close();

}

string getStringTipoFicha(TipoContenido tipo){

    string contenido = "";

    switch(tipo){
        case SOLDADO:
            contenido = "Soldado";
            break;
        case TANQUE:
            contenido = "Tanque";
            break;
        case SUBMARINO:
            contenido = "Submarino";
            break;
            case AVION:
            contenido = "Avion";
            break;
        case MINA_FICHA:
            contenido = "Mina";
            break; 
    }

    return contenido;
}