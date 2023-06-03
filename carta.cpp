#include "./Headers/carta.h"
#include "./Headers/Tablero.h"
#include "./Headers/Celda.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;


Carta::Carta(TipoCarta carta) {
    
    this->cartaActiva = true;
    this->radioAccion = -1;
    this->cantidadBombas = -1;

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
    
    this->cartaActiva = false;

    switch(this->carta){
        case OMITIR_TURNO:
            //se pasa por parametros jugador continuo
            this->activarAtributosJugador(atributoJugador);
            break;
        case ESCUDO:
            this->activarAtributosJugador(atributoJugador);
            break;
    }
} 

 void Carta::usarCarta(Tablero<Celda*>* tablero, int x, int y, int z){

    this->cartaActiva = false;

    switch(this->carta){
        case AVION_RADAR:
            this->radioAccion = 8;
            this->obtenerReporte(tablero,x,y,z);
            break;
        case ATAQUE_QUIMICO:
            this->radioAccion = 5;
            this->inactivarCeldas(tablero,x,y,z);
            break;
        case BOMBARDEO:
            this->radioAccion = 5;
            this->cantidadBombas = 4;
            this->bombardearCeldas(tablero,x,y,z);
            break;
        case BARCO_MISIL:
            this->lanzarMisil(tablero, x , y, z);
            break;
    }
}

TipoCarta Carta::getTipoCarta() {
    return this->carta;
}

bool Carta::getCartaActiva() {
    return this->cartaActiva;
}

void Carta::inactivarCeldas(Tablero<Celda*>* tablero, int x, int y, int z){

    int radio = this->radioAccion; 
    string reporte = NULL;

    for (int n= x - radio; n < x + radio ; n++){
        for (int m= y - radio; m < y + radio ; m++){
            for (int l = z - radio; l < z + radio ; l++){
                
                if(tablero->inRange(n,m,l)){

                    int turnosInactiva = this->getTurnosInactiva(n,m,l,x,y,z);

                    if(tablero->getTData(n,m,l)->getFicha()->getTipo() == VACIO){
                        tablero->getTData(n,m,l)->setEstado(false); 
                        tablero->getTData(n,m,l)->setTurnosInactiva(turnosInactiva);
                    }else{
                        int owner = tablero->getTData(n,m,l)->getFicha()->getJugadorOwner();
                        string contenido = this->getStringTipoFicha(tablero->getTData(n,m,l)->getFicha()->getTipo());
                        reporte = reporte + "(" + to_string(n) + ","+ to_string(m) + ","+ to_string(l) + ") - " + contenido + " " + to_string(owner) + "/";
                        
                        tablero->getTData(n,m,l)->setEstado(false);
                        tablero->getTData(n,m,l)->setTurnosInactiva(turnosInactiva);
                        tablero->getTData(n,m,l)->getFicha()->setTipo(VACIO);
                    }
                }
            }
        }
    }

    this->imprimirReporte(reporte);
}
void Carta::bombardearCeldas(Tablero<Celda*>* tablero, int x, int y, int z){

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

void Carta::obtenerReporte(Tablero<Celda*>* tablero, int x, int y, int z){
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
  
void Carta::lanzarMisil(Tablero<Celda*>* tablero,  int x, int y, int z){
    
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

string Carta::getStringTipoFicha(TipoContenido tipo){

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

int Carta::getTurnosInactiva(int puntoX, int puntoY, int puntoZ, int centroX, int centroY, int centroZ){

    int radio = this->radioAccion;

    int distanciaX = abs(centroX - puntoX);
    int distanciaY = abs(centroY - puntoY);
    int distanciaZ = abs(centroZ - puntoZ);
    
    if (distanciaX == radio || distanciaY == radio || distanciaZ == radio) {
        return  1; 
    } else if (distanciaX == radio-1 || distanciaY == radio-1 || distanciaZ == radio-1) {
        return  2; 
    } else if (distanciaX == radio-2 || distanciaY == radio-2 || distanciaZ == radio-2) {
        return  4; 
    } else if (distanciaX == radio-3 || distanciaY == radio-3 || distanciaZ == radio-3) {
        return  6; 
    } else if (distanciaX == radio-4 || distanciaY == radio-4 || distanciaZ == radio-4) {
        return  8; 
    } else {
        return 10; 
    }

}