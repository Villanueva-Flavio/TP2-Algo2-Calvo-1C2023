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
    this->carta = carta;
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

 void Carta::usarCarta(Tablero<Celda*>* tablero, coordenadas centro){

    this->cartaActiva = false;

    switch(this->carta){
        case AVION_RADAR:
            this->radioAccion = 8;
            this->obtenerReporte(tablero,centro);
            break;
        case ATAQUE_QUIMICO:
            this->radioAccion = 5;
            this->inactivarCeldas(tablero,centro);
            break;
        case BOMBARDEO:
            this->radioAccion = 3;
            this->cantidadBombas = 4;
            this->bombardearCeldas(tablero,centro);
            break;
        case BARCO_MISIL:
            this->lanzarMisil(tablero,centro);
            break;
    }
}

TipoCarta Carta::getTipoCarta() {
    return this->carta;
}

string Carta::getStringTipoCarta(){
    mapaStringTipoDeCarta mapa = getMapaStringTipoDeCartas();
    return mapa[this->carta];
}

bool Carta::getCartaActiva() {
    return this->cartaActiva;
}

void Carta::inactivarCeldas(Tablero<Celda*>* tablero, coordenadas centro){

    int radio = this->radioAccion; 
    string reporte = "";

    for (int n= centro.x - radio; n < centro.x + radio ; n++){
        for (int m= centro.y - radio; m < centro.y + radio ; m++){
            for (int l = centro.z - radio; l < centro.z + radio ; l++){
                if(tablero->inRange(n,m,l)){
                    coordenadas punto = {n,m,l};
                    int turnosInactiva = this->getTurnosInactiva(centro,punto);

                    if(tablero->getTData(n,m,l)->getFicha()->getTipo() == VACIO){
                        tablero->getTData(n,m,l)->setEstado(false); 
                        tablero->getTData(n,m,l)->setTurnosInactiva(turnosInactiva);
                        this->inactivarCelda(tablero,punto,turnosInactiva);
                    }else{
                        int owner = tablero->getTData(n,m,l)->getFicha()->getJugadorOwner();
                        string contenido = this->getStringTipoFicha(tablero->getTData(n,m,l)->getFicha()->getTipo());
                        reporte = reporte + "Posicion: (" + to_string(n) + ","+ to_string(m) + ","+ to_string(l) + ") - Contenido: " + contenido + " - Jugador: " + to_string(owner) + "/";
                        this->inactivarCelda(tablero,punto,turnosInactiva);
                    }
                }
            }
        }
    }

    this->imprimirReporte(reporte);
}
void Carta::bombardearCeldas(Tablero<Celda*>* tablero, coordenadas centro){

    int &radio = this->radioAccion; 
    string reporte = "";
    coordenadas limiteSuperior = {2*radio,2*radio,2*radio};
    coordenadas limiteInferior = {centro.x -radio, centro.y - radio, centro.z - radio};

    for(int i= 0; i<this->cantidadBombas; i++){
        coordenadas puntoAlAzar = {rand() % limiteSuperior.x + limiteInferior.x, rand() % limiteSuperior.y + limiteInferior.y, rand() % limiteSuperior.z +limiteInferior.z};
        if(tablero->inRange(puntoAlAzar.x,puntoAlAzar.y,puntoAlAzar.z)){
            cout << "entro"<<endl;
            int owner = tablero->getTData(puntoAlAzar.x,puntoAlAzar.y,puntoAlAzar.z)->getFicha()->getJugadorOwner();
            string contenido = this->getStringTipoFicha(tablero->getTData(puntoAlAzar.x,puntoAlAzar.y,puntoAlAzar.z)->getFicha()->getTipo());
            reporte = reporte + "Posicion: (" + to_string(puntoAlAzar.x) + ","+ to_string(puntoAlAzar.y) + ","+ to_string(puntoAlAzar.z) + ") - Contenido: " + contenido + " - Jugador: " + to_string(owner) + "/";
            
            this->inactivarCelda(tablero,puntoAlAzar,4);
        }
    }

    this->imprimirReporte(reporte);
}

void Carta::obtenerReporte(Tablero<Celda*>* tablero,  coordenadas centro){
    int &radio = this->radioAccion; 
    string reporte = "";

    for (int n= centro.x - radio; n < centro.x + radio ; n++){
        for (int m= centro.y - radio; m < centro.y + radio ; m++){
            for (int l = centro.z - radio; l < centro.z + radio ; l++){
                if(tablero->inRange(n,m,l)){

                    if(tablero->getTData(n,m,l)->getFicha()->getTipo() != VACIO){
                        int owner = tablero->getTData(n,m,l)->getFicha()->getJugadorOwner();
                        string contenido = this->getStringTipoFicha(tablero->getTData(n,m,l)->getFicha()->getTipo());
                        reporte = reporte + "Posicion: (" + to_string(n) + ","+ to_string(m) + ","+ to_string(l) + ") - Contenido: " + contenido + " - Jugador: " + to_string(owner) + "/";
                    }
                }
        
            }
        }
    }
    this->imprimirReporte(reporte);
}
  
void Carta::lanzarMisil(Tablero<Celda*>* tablero,  coordenadas centro){
    
    if(tablero->inRange(centro.x,centro.y,centro.z)){

        int owner = tablero->getTData(centro.x,centro.y,centro.z)->getFicha()->getJugadorOwner();
        string contenido = this->getStringTipoFicha(tablero->getTData(centro.x,centro.y,centro.z)->getFicha()->getTipo());
        string reporte = "Posicion: (" + to_string(centro.x) + ","+ to_string(centro.y) + ","+ to_string(centro.z) + ") - Contenido: " + contenido + " - Jugador: " + to_string(owner) + "/"; 
        this->inactivarCelda(tablero,centro,4);
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
    if(reporte!= ""){
        for(int i=0; i < reporte.size() ; i++){

            //47-> Codigo ANSI para (/)
            if (reporte[i] != 47) {
                file << reporte[i];
                
            }else{
                file <<"\n";
            }
        }
    }else{
        file << "No hubieron fichas afectadas por el ataque :("; 
    }
    

    file.close();

}

string Carta::getStringTipoFicha(TipoContenido tipo){
    mapaTiposContenido mapaTiposContenido = this->getMapaTiposContenido();
    return mapaTiposContenido[tipo];
}

int Carta::getTurnosInactiva(coordenadas centro, coordenadas punto){

    int radio = this->radioAccion;

    coordenadas distancia = {abs(centro.x - punto.x), abs(centro.y - punto.y), abs(centro.z - punto.z)};
    
    if (distancia.x == radio || distancia.y == radio || distancia.z == radio) {
        return  1; 
    } else if (distancia.x== radio-1 || distancia.y == radio-1 || distancia.z == radio-1) {
        return  2; 
    } else if (distancia.x == radio-2 || distancia.y == radio-2 || distancia.z == radio-2) {
        return  4; 
    } else if (distancia.x == radio-3 || distancia.y == radio-3 || distancia.z == radio-3) {
        return  6; 
    } else if (distancia.x == radio-4 || distancia.y == radio-4 || distancia.z == radio-4) {
        return  8; 
    } else {
        return 10; 
    }

}

void Carta::inactivarCelda(Tablero<Celda*>* tablero, coordenadas punto, int turnosInactiva){
    tablero->getTData(punto.x,punto.y,punto.z)->setEstado(false);
    tablero->getTData(punto.x,punto.y,punto.z)->setTurnosInactiva(4);
    tablero->getTData(punto.x,punto.y,punto.z)->getFicha()->setTipo(VACIO);
}

mapaTiposDeCartas Carta::getMapaTipoDeCartas(){
    mapaTiposDeCartas mapa;
    mapa[AVION_RADAR]=AVION_RADAR;
    mapa[BARCO_MISIL]=BARCO_MISIL;
    mapa[ATAQUE_QUIMICO]=ATAQUE_QUIMICO;
    mapa[BOMBARDEO]=BOMBARDEO;
    mapa[OMITIR_TURNO]=OMITIR_TURNO;
    mapa[ESCUDO]=ESCUDO;
    return mapa;
}


mapaTiposContenido Carta::getMapaTiposContenido(){
    mapaTiposContenido mapa;
    mapa[SOLDADO]="soldado";
    mapa[TANQUE]="tanque";
    mapa[BARCO]="barco";
    mapa[SUBMARINO]="submarino";
    mapa[AVION]="avion";
    mapa[MINA_FICHA]="mina";
    mapa[VACIO]="vacio";
    return mapa;
}

mapaStringTipoDeCarta Carta::getMapaStringTipoDeCartas(){
    mapaStringTipoDeCarta mapa;
    mapa[AVION_RADAR]="Avion Radar";
    mapa[BARCO_MISIL]="Barco";
    mapa[ATAQUE_QUIMICO]="Ataque Quimico";
    mapa[BOMBARDEO]="Bombardeo";
    mapa[OMITIR_TURNO]="Omitir Turno";
    mapa[ESCUDO]="Escudo";
    return mapa;
}