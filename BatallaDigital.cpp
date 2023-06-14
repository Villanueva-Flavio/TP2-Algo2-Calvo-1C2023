#include <map>
#include <string>
#include <cmath>
#include "Headers/Tablero.h"
#include "Headers/Celda.h"
#include "Headers/Carta.h"
#include "Headers/Renderizador.h"
#include "Headers/BatallaDigital.h"

using namespace std;

#define CAPA_MAXIMA 5

enum Color {PASTO, TIERRA, ARENA, MINA, FUEGO, AGUA, AIRE, SIN_COLOR};
enum TipoMapa {M_PLAYA, M_MAR, M_TIERRA, M_DESIERTO, M_RIO, M_LAGO};

typedef map<string, Coordenada> MapaCoordenadas;
typedef map<Color, RGBApixel> MapaColores;
typedef map<string, TipoMapa> MapaTipos;

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

MapaTipos getMapaTipos(){
    MapaTipos mapa;
    mapa["playa"] = M_PLAYA;
    mapa["mar"] = M_MAR;
    mapa["tierra"] = M_TIERRA;
    mapa["desierto"] = M_DESIERTO;
    mapa["rio"] = M_RIO;
    mapa["lago"] = M_LAGO;
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

// Retorna el tipo de mapa ingresado por el usuario (implementación requerida)
std::string BatallaDigital::consultarTipoDeMapa(){
// Gero
    return this->tipoMapa;
}

void BatallaDigital::cargarTerrenoPlano(int tipo) {
    for(int i = 0; i < this->mapa->getTamanioX(); i ++){
        for(int j = 0; i < this->mapa->getTamanioY(); j ++){
            for(int k = 0; i < this->mapa->getTamanioZ(); k ++){
                this->mapa->getTData(i, j, k)->setTipo((k>5)? CAPA_AIRE : (i<k+4)? CAPA_ARENA : CAPA_AGUA);
            }    
        }    
    }    
}

void BatallaDigital::cargarPlaya(int tipo) {
    for(int i = 0; i < this->mapa->getTamanioX(); i ++){
        for(int j = 0; i < this->mapa->getTamanioY(); j ++){
            for(int k = 0; i < this->mapa->getTamanioZ(); k ++){
                this->mapa->getTData(i, j, k)->setTipo((k>5)? CAPA_AIRE : (i<k+4)? CAPA_ARENA : CAPA_AGUA);
            }    
        }    
    }    
}

bool BatallaDigital::esOrilla(int tipo, Coordenada pos){
    CoordenadaDouble r;
    double p = (tipo == M_LAGO)? 0.285:0.227;
    double radioAjustado = 1+(p*(pow(this->mapa->getTamanioX()/4, 1/2.5)));
    r.x = (tipo == M_LAGO)? pow(pos.x - mapa->getTamanioX()/2, 2) : 0;
    r.y = pow(pos.y - mapa->getTamanioY()/2, 2);
    r.z = pow(pos.y - mapa->getTamanioZ()/2, 2);
    return ((double)(r.x + r.y + r.z) <= pow(this->mapa->getTamanioX(), radioAjustado));
}

void BatallaDigital::cargarRioLago(int tipo){
    for(int x = 0; x < mapa->getTamanioX(); x++){
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < mapa->getTamanioZ(); z++){
                Coordenada pos = {x, y, z};
                (!esOrilla(tipo, pos))? this->mapa->getTData(x, y, z)->setTipo(CAPA_AGUA) : this->mapa->getTData(x, y, CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
            }
            mapa->getTData(x, y, 0)->setTipo(CAPA_ARENA);
        }
    }
}

// Carga el mapa elegido por el jugador
void BatallaDigital::cargarMapas() {
    string tipo = this->consultarTipoDeMapa();
    MapaTipos mapita = getMapaTipos();
    int enumeradorcito = 0;
    while (mapita.count(tipo) == 0) {
        cout << "Tipo inválido, reingrese el tipo.\n";
        tipo = this->consultarTipoDeMapa();
    }
    enumeradorcito = mapita[tipo];
    if (enumeradorcito == M_TIERRA || enumeradorcito == M_DESIERTO || enumeradorcito == M_MAR) {
        this->cargarTerrenoPlano(enumeradorcito);
    } else if (enumeradorcito == M_PLAYA) {
        this->cargarPlaya(enumeradorcito);
    } else if (enumeradorcito == M_RIO || enumeradorcito == M_LAGO) {
        this->cargarRioLago(enumeradorcito);
    }
}

// Carga las cantidades de fichas que contiene cada jugador
void BatallaDigital::cargarCantidadesDeFichasAJugadores(){
    for(int i = 0; i < this->jugadores->getSize(); i++) {
        this->jugadores->getLData(i)->setArmamentos(1), jugadores->getLData(i)->setSoldados(5);
    }    
}

bool BatallaDigital::validarCeldaAInsertarFicha(Coordenada* cordenada, TipoContenido tipoDeFicha) {
    TipoContenido tipo = this->mapa->getTData(cordenada->x,cordenada->y,cordenada->z)->getFicha()->getTipo();
    Capa capa = this->mapa->getTData(cordenada->x,cordenada->y,cordenada->z)->getTipo();

    return (tipo == VACIO 
    && ((tipoDeFicha == BARCO && this->mapa->getTData(cordenada->x,cordenada->y,CAPA_MAXIMA-1)->getTipo() == CAPA_AGUA) 
        || (tipoDeFicha == SUBMARINO && capa == CAPA_AGUA) 
        || (tipoDeFicha == AVION && capa == CAPA_AIRE)  
        || (tipoDeFicha == SOLDADO && capa == CAPA_AIRE))
    );
}

void BatallaDigital::cargarFichaDelTipo(int cantidadDeCarga, TipoContenido tipoDeFicha, int jugadorOwner){
    Coordenada cordenada;
    for (int i = 0; i <= cantidadDeCarga; i++){
        do{
            cordenada.x = std::rand()%(this->mapa->getTamanioX()-1);
            cordenada.y = std::rand()%(this->mapa->getTamanioY()-1);
            cordenada.z = (tipoDeFicha == SOLDADO || tipoDeFicha == TANQUE || tipoDeFicha == BARCO) ? CAPA_MAXIMA : std::rand()%(this->mapa->getTamanioZ()-1);
        } while (validarCeldaAInsertarFicha(&cordenada,tipoDeFicha));
    }
}

void BatallaDigital::cargarFichas(){
    for (int i = 0; i < jugadores->getSize(); i++){
        if (this->tipoMapa != "mar"){
            this->cargarFichaDelTipo(jugadores->getLData(i)->getSoldados(),SOLDADO,i+1);
            this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos(),TANQUE,i+1);
        }
        if (this->tipoMapa != "tierra" && this->tipoMapa != "desierto"){
            this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos(),SUBMARINO,i+1);
            this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos(),BARCO,i+1);

        }
        this->cargarFichaDelTipo(jugadores->getLData(i)->getArmamentos() + 1,AVION,i+1);
    }
}

void BatallaDigital::cargarJuego() {
    this->cargarMapas();
    this->cargarCantidadesDeFichasAJugadores();
    this->cargarFichas();
}