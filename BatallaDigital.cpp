#include <map>
#include <string>
#include "Headers/Tablero.h"
#include "Headers/Celda.h"
#include "Headers/Carta.h"
#include "Headers/Renderizador.h"
#include "Headers/BatallaDigital.h"

using namespace std;

enum Color {PASTO, TIERRA, ARENA, MINA, FUEGO, AGUA, AIRE, SIN_COLOR};

typedef map<string, Coordenada> MapaCoordenadas;
typedef map<Color, RGBApixel> MapaColores;

MapaCoordenadas getMapaCoordenadas(){
    MapaCoordenadas mapa;
    mapa["w"] = {0,0,1};
    mapa["a"] = {-1,0,0};
    mapa["s"] = {0,0,-1};
    mapa["d"] = {1,0,0};
    mapa["W"] = {0,0,1};
    mapa["A"] = {-1,0,0};
    mapa["S"] = {0,0,-1};
    mapa["D"] = {1,0,0};
    return mapa;
};

BatallaDigital::BatallaDigital(int cantidad){
    this->mapa = new Mapa(cantidad*4, cantidad*4, cantidad*4);
    this->jugadores = new Jugadores();
    for(int i = 0; i < cantidad; i++){
        Jugador* jugador = new Jugador();
        this->jugadores->add(jugador);
    }
    this->cantidadJugadores = cantidad;
    this->turno = 0;
}

BatallaDigital::~BatallaDigital(){
    delete this->mapa;
    delete this->jugadores;
}

void BatallaDigital::consultarNombres(){
// Gero
}

void BatallaDigital::consultarTipoDeMapa(){
// Gero
}

int jugadoresConFichas(){
    
}

void BatallaDigital::cargarJuego(){
    //Consultar Nombres | SIN PARAMETROS
    //Consultar Colores | SIN PARAMETROS

    //Consultar tipo de mapa | enum tipo
    //Cargar tipo mapa | enum tipo
    //Posicionar fichas  | enum tipo
}

void BatallaDigital::ejecutarTurno(){
    for(int i = 0; i < this->cantidadJugadores; i++){
        
        //Si jugador no tiene fichas -> no juega
        //Si jugador tiene turno omitido -> no juega
        
        //Print Mapa_Jugador_X.bmp

        //Pedir Ficha a mover - Mostrar ficha
        //Pedir movimiento o accion
        //Ejecutar movimiento o accion

        //Soltar mina
        //Comprobar si explota

        //Robar Carta    

    }
}

void BatallaDigital::jugar(){
    while(this->jugadoresConFichas() > 1){
        this->ejecutarTurno();
    }
    //mensajeVictoria(this->jugadores->getJugador(0)->getNombre()); (Podria quedar para main)
}
