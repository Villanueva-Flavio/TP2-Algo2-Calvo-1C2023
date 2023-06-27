#include "Carta.h"
#include "Tablero.h"
#include "Celda.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sstream>


using namespace std;

Carta::Carta(TipoCarta carta) {
    this->cartaActiva = true;
    this->radioAccion = -1;
    this->cantidadBombas = -1;
    this->carta = carta;
}

 void Carta::usarCarta(Tablero<Celda*>* tablero, Coordenada centro){

    this->cartaActiva = false;

    switch(this->carta){
        case AVION_RADAR:
            this->radioAccion = 4;
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
    string tipoDeCarta = "";

    switch (this->carta)
    {
    case AVION_RADAR:
        tipoDeCarta = "Avion Radar";
        break;
    case BARCO_MISIL:
        tipoDeCarta = "Barco";
        break;
    case ATAQUE_QUIMICO:
        tipoDeCarta = "Ataque Quimico";
        break;
    case BOMBARDEO:
        tipoDeCarta = "Bombardeo";
        break;
    case OMITIR_TURNO:
        tipoDeCarta = "Omitir Turno";
        break;
    default:
        tipoDeCarta = "Escudo";
        break;
    }
    return tipoDeCarta;
}

bool Carta::getCartaActiva() {
    return this->cartaActiva;
}

void Carta::inactivarCeldas(Tablero<Celda*>* tablero, Coordenada centro){

    int radio = this->radioAccion; 
    string reporte = "";

    for (int n= centro.getCoordenadaX() - radio; n < centro.getCoordenadaX() + radio ; n++){
        for (int m= centro.getCoordenadaY() - radio; m < centro.getCoordenadaY() + radio ; m++){
            for (int l = centro.getCoordenadaZ() - radio; l < centro.getCoordenadaZ() + radio ; l++){
                if(tablero->inRange(n,m,l)){
                    Coordenada punto;
                    punto.setCoordenadaX(n);
                    punto.setCoordenadaY(m);
                    punto.setCoordenadaZ(l);
                    int turnosInactiva = this->getTurnosInactiva(centro,punto);

                    if(tablero->getTData(n,m,l)->getFicha()->getTipo() == VACIO){
                        tablero->getTData(n,m,l)->setEstado(false); 
                        tablero->getTData(n,m,l)->setTurnosInactiva(turnosInactiva);
                        this->inactivarCelda(tablero,punto,turnosInactiva);
                    }else{
                        int owner = tablero->getTData(n,m,l)->getFicha()->getJugadorOwner();
                        string contenido = this->getStringTipoFicha(tablero->getTData(n,m,l)->getFicha()->getTipo());
                        stringstream ss;
                        ss << "Posicion: (" << n << "," << m << "," << l << ") - Contenido: " << contenido << " - Jugador: " << owner << "/";
                        reporte += ss.str();
                        this->inactivarCelda(tablero,punto,turnosInactiva);
                    }
                }
            }
        }
    }

    this->imprimirReporte(reporte);
}
void Carta::bombardearCeldas(Tablero<Celda*>* tablero, Coordenada centro){

    int &radio = this->radioAccion; 
    string reporte = "";
    Coordenada limiteSuperior;
    limiteSuperior.setCoordenadaX(2*radio);
    limiteSuperior.setCoordenadaY(2*radio);
    limiteSuperior.setCoordenadaZ(2*radio);

    Coordenada limiteInferior;
    limiteInferior.setCoordenadaX(centro.getCoordenadaX() -radio);
    limiteInferior.setCoordenadaX(centro.getCoordenadaY() -radio);
    limiteInferior.setCoordenadaX(centro.getCoordenadaZ() -radio);

    for(int i= 0; i<this->cantidadBombas; i++){
        Coordenada puntoAlAzar;
        puntoAlAzar.setCoordenadaX(rand() % limiteSuperior.getCoordenadaX() + limiteInferior.getCoordenadaX());
        puntoAlAzar.setCoordenadaY(rand() % limiteSuperior.getCoordenadaY() + limiteInferior.getCoordenadaY());
        puntoAlAzar.setCoordenadaZ(rand() % limiteSuperior.getCoordenadaZ() +limiteInferior.getCoordenadaZ());
        if(tablero->inRange(puntoAlAzar.getCoordenadaX(),puntoAlAzar.getCoordenadaY(),puntoAlAzar.getCoordenadaZ())){
            int owner = tablero->getTData(puntoAlAzar.getCoordenadaX(),puntoAlAzar.getCoordenadaY(),puntoAlAzar.getCoordenadaZ())->getFicha()->getJugadorOwner();
            string contenido = this->getStringTipoFicha(tablero->getTData(puntoAlAzar.getCoordenadaX(),puntoAlAzar.getCoordenadaY(),puntoAlAzar.getCoordenadaZ())->getFicha()->getTipo());
            stringstream ss;
            ss << "Posicion: (" << puntoAlAzar.getCoordenadaX() << "," << puntoAlAzar.getCoordenadaY() << "," << puntoAlAzar.getCoordenadaZ() << ") - Contenido: " << contenido << " - Jugador: " << owner << "/";
            reporte += ss.str();
            this->inactivarCelda(tablero,puntoAlAzar,4);
        }
    }

    this->imprimirReporte(reporte);
}

void Carta::obtenerReporte(Tablero<Celda*>* tablero,  Coordenada centro){
    int &radio = this->radioAccion; 
    string reporte = "";

    for (int n= centro.getCoordenadaX() - radio; n < centro.getCoordenadaX() + radio ; n++){
        for (int m= centro.getCoordenadaY() - radio; m < centro.getCoordenadaY() + radio ; m++){
            for (int l = centro.getCoordenadaZ() - radio; l < centro.getCoordenadaZ() + radio ; l++){
                if(tablero->inRange(n,m,l)){

                    if(tablero->getTData(n,m,l)->getFicha()->getTipo() != VACIO){
                        int owner = tablero->getTData(n,m,l)->getFicha()->getJugadorOwner();
                        string contenido = this->getStringTipoFicha(tablero->getTData(n,m,l)->getFicha()->getTipo());
                        stringstream ss;
                        ss << "Posicion: (" << n << "," << m << "," << l << ") - Contenido: " << contenido << " - Jugador: " << owner << "/";
                        reporte += ss.str();
                    }
                }
        
            }
        }
    }
    this->imprimirReporte(reporte);
}
  
void Carta::lanzarMisil(Tablero<Celda*>* tablero,  Coordenada centro){
    
    if(tablero->inRange(centro.getCoordenadaX(),centro.getCoordenadaY(),centro.getCoordenadaZ())){

        int owner = tablero->getTData(centro.getCoordenadaX(),centro.getCoordenadaY(),centro.getCoordenadaZ())->getFicha()->getJugadorOwner();
        string contenido = this->getStringTipoFicha(tablero->getTData(centro.getCoordenadaX(),centro.getCoordenadaY(),centro.getCoordenadaZ())->getFicha()->getTipo());
        stringstream ss4;
        ss4 << "Posicion: (" << centro.getCoordenadaX() << "," << centro.getCoordenadaY() << "," << centro.getCoordenadaZ() << ") - Contenido: " << contenido << " - Jugador: " << owner << "/";
        string reporte = ss4.str();
        this->inactivarCelda(tablero,centro,4);
        this->imprimirReporte(reporte);
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
    string tipoDeCarta= "";

    switch (tipo)
    {
    case SOLDADO:
        tipoDeCarta= "soldado";
        break;
    case TANQUE:
        tipoDeCarta= "tanque";
        break;
    case BARCO:
        tipoDeCarta= "barco";
        break;
    case SUBMARINO:
        tipoDeCarta= "submarino";
        break;
    case AVION:
        tipoDeCarta= "avion";
        break;
    case MINA_FICHA:
        tipoDeCarta= "mina";
        break;
    default:
        tipoDeCarta= "vacio";
        break;
    }
    return tipoDeCarta;
}

int Carta::getTurnosInactiva(Coordenada centro, Coordenada punto){

    int radio = this->radioAccion;

    Coordenada distancia;
    distancia.setCoordenadaX(abs(centro.getCoordenadaX() - punto.getCoordenadaX()));
    distancia.setCoordenadaY(abs(centro.getCoordenadaY() - punto.getCoordenadaY()));
    distancia.setCoordenadaZ(abs(centro.getCoordenadaZ() - punto.getCoordenadaZ()));
    
    if (distancia.getCoordenadaX() == radio || distancia.getCoordenadaY() == radio || distancia.getCoordenadaZ() == radio) {
        return  1; 
    } else if (distancia.getCoordenadaX()== radio-1 || distancia.getCoordenadaY() == radio-1 || distancia.getCoordenadaZ() == radio-1) {
        return  2; 
    } else if (distancia.getCoordenadaX() == radio-2 || distancia.getCoordenadaY() == radio-2 || distancia.getCoordenadaZ() == radio-2) {
        return  4; 
    } else if (distancia.getCoordenadaX() == radio-3 || distancia.getCoordenadaY() == radio-3 || distancia.getCoordenadaZ() == radio-3) {
        return  6; 
    } else if (distancia.getCoordenadaX() == radio-4 || distancia.getCoordenadaY() == radio-4 || distancia.getCoordenadaZ() == radio-4) {
        return  8; 
    } else {
        return 10; 
    }

}

void Carta::inactivarCelda(Tablero<Celda*>* tablero, Coordenada punto, int turnosInactiva){
    tablero->getTData(punto.getCoordenadaX(),punto.getCoordenadaY(),punto.getCoordenadaZ())->setEstado(false);
    tablero->getTData(punto.getCoordenadaX(),punto.getCoordenadaY(),punto.getCoordenadaZ())->setTurnosInactiva(4);
    tablero->getTData(punto.getCoordenadaX(),punto.getCoordenadaY(),punto.getCoordenadaZ())->getFicha()->setTipo(VACIO);
}

