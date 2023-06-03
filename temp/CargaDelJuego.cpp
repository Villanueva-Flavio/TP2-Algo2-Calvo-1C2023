#include "./Headers/Tablero.h"
#include "./Headers/Celda.h"
#include "./Headers/Jugador.h"
#include "./Headers/Renderizador.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

#define CAPA_MAXIMA 5
#define CANTIDAD_FICHAS 10

struct coordenadas{int x,y,z;};
struct Niveles{int suelo,mar;};
struct Desplazar{int x,y,z;};

bool noEsOrillaRio(Mapa* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    double radioAjustado = 1+(0.227*(pow(size/4,1/2.5)));
    double radio = pow(y-mapa->getTamanioY()/2, 2) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio <= pow(size,radioAjustado)){
        orilla = true;
    }
    return orilla;
}

bool esOrillaRio(Mapa* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    double radioAjustado = 1+(0.227*(pow(size/4,1/2.5)));
    double radio = pow(y-mapa->getTamanioY()/2, 2) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio > pow(size,radioAjustado)){
        orilla = true;
    }
    return orilla;
}

void cargarRio(Mapa* mapa, int size) {
    for(int x = 0; x < mapa->getTamanioX(); x++) {
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < CAPA_MAXIMA; z++) {
                if (noEsOrillaRio(mapa,x,y,z,size)){
                    mapa->getTData(x,y,z)->setTipo(CAPA_AGUA);
                }else if (esOrillaRio(mapa,x,y,z,size)){
                    if (z < CAPA_MAXIMA) mapa->getTData(x,y,z)->setTipo(CAPA_TIERRA);
                    mapa->getTData(x,y,CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
                }
                mapa->getTData(x,y,0)->setTipo(CAPA_ARENA);
            }
        }
    }
}

bool noEsOrillaDelLago(Mapa* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    double radioAjustado = 1+(0.285*(pow(size/4,1/2.5)));
    double radio = pow(x-mapa->getTamanioX()/2, 2) + (pow(y-mapa->getTamanioY()/2, 2)) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio <= pow(size,radioAjustado)){
        orilla = true;
    }
    return orilla;
}

bool esOrillaDelLago(Mapa* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    double radioAjustado = 1+(0.285*(pow(size/4,1/2.5)));
    double radio = pow(x-mapa->getTamanioX()/2, 2) + (pow(y-mapa->getTamanioY()/2, 2)) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio > pow(size,radioAjustado)){
        orilla = true;
    }
    return orilla;
}

void cargarLago(Mapa* mapa, int size) {
    for(int x = 0; x < mapa->getTamanioX(); x++) {
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < CAPA_MAXIMA; z++) {
                if (noEsOrillaDelLago(mapa,x,y,z,size)){
                    mapa->getTData(x,y,z)->setTipo(CAPA_AGUA);
                }else if (esOrillaDelLago(mapa,x,y,z,size)){
                    if (z < CAPA_MAXIMA) mapa->getTData(x,y,z)->setTipo(CAPA_TIERRA);
                    mapa->getTData(x,y,CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
                }
                mapa->getTData(x,y,0)->setTipo(CAPA_ARENA);
            }
        }
    }
}

void cargarPlaya(Mapa* playa){
    for(int i = 0; i < playa->getTamanioX(); i++){
        for(int j = 0; j < playa->getTamanioY(); j++){
            for(int k = 0; k < playa->getTamanioZ(); k++){
                if(i < k+4 ){
                    playa->getTData(i, j, k)->setTipo(CAPA_ARENA);
                } else if (i >= k+4){
                    playa->getTData(i, j, k)->setTipo(CAPA_AGUA);
                }

                if(k > playa->getTamanioX() / 2){
                    playa->getTData(i, j, k)->setTipo(CAPA_AIRE);
                }
            }
        }
    }
}

void cargarMar(Mapa* mar) {
    for (int i = 0; i < mar->getTamanioX(); i++){
        for (int j = 0; j < mar->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                mar->getTData(i,j,k)->setTipo(CAPA_AGUA);
            }
        }
    }
}

void cargarTierra(Mapa* tierraConPasto) {
    for (int i = 0; i < tierraConPasto->getTamanioX(); i++){
        for (int j = 0; j < tierraConPasto->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                if (k < CAPA_MAXIMA-1){
                    tierraConPasto->getTData(i,j,k)->setTipo(CAPA_PASTO);
                }else {
                    tierraConPasto->getTData(i,j,k)->setTipo(CAPA_TIERRA);
                }                
            }
        }
    }
}

void cargarDesierto(Mapa* desierto) {
    for (int i = 0; i < desierto->getTamanioX(); i++){
        for (int j = 0; j < desierto->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                desierto->getTData(i,j,k)->setTipo(CAPA_ARENA);
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

void generarMundo(Mapa* mundoGenerado, std::string tipoDeMundo) {
     do{ // if (verificarOpcion(tipoDeMundo) == false){
                //tipoDeMundo = pedirTipoDeMundo();
         // }
        if (tipoDeMundo == "playa"){
            cargarPlaya(mundoGenerado);
        }else if (tipoDeMundo == "mar") {
            cargarMar(mundoGenerado);
        }else if (tipoDeMundo == "tierra"){
            cargarTierra(mundoGenerado);
        }else if (tipoDeMundo == "desierto"){
            cargarDesierto(mundoGenerado);
        }
        break; // Sacar el braque al descomentar el if de arriba
    } while (verificarOpcion(tipoDeMundo) == false);
}

void cargarCantidadesDeFicha(Jugador* jugadores[], int cantidadDeJugadores) {
    for(int i = 0; i < cantidadDeJugadores; i++) {
        jugadores[i]->setSoldados(CANTIDAD_FICHAS);
        jugadores[i]->setSoldados(CANTIDAD_FICHAS);
        // Cada vez que se mueran soldados decrementar cantidades 
    }
}

void cargarJugadores(Jugador* jugadores[], std::string nombres[], int cantidadJugadores) {

}


bool hayUnaFichaDelTipo(Mapa* mundoDelJuego, int coordenadaX, int coordenadaY, int coordenadaZ){
    bool hayDelTipo = true;
    hayDelTipo = (mundoDelJuego->getTData(coordenadaX,coordenadaY,coordenadaZ)->getFicha()->getTipo() == VACIO 
        && mundoDelJuego->getTData(coordenadaX,coordenadaY,coordenadaZ)->getFicha()->getTipo()) ? true : false;
    return hayDelTipo;
}

void cargarSoldados(Mapa* mundoDelJuego, std::string tipoDeMundo, int cantidadJugadores) {
    int a = 0, x = 0, y = 0;
    for(int i = 0; i < cantidadJugadores; i++) {
        while (a < CANTIDAD_FICHAS){
            x = rand() % mundoDelJuego->getTamanioX(),rand() % mundoDelJuego->getTamanioY(),CAPA_MAXIMA + 1;
            y = rand() % mundoDelJuego->getTamanioY(),rand() % mundoDelJuego->getTamanioY(),CAPA_MAXIMA + 1;
            if (hayUnaFichaDelTipo(mundoDelJuego,x,y,CAPA_MAXIMA - 1) && (mundoDelJuego->getTData(x,y,CAPA_MAXIMA)->getTipo() == CAPA_PASTO 
            || mundoDelJuego->getTData(x,y,CAPA_MAXIMA)->getTipo() == CAPA_TIERRA 
            || mundoDelJuego->getTData(x,y,CAPA_MAXIMA)->getTipo() == CAPA_ARENA))
            {
                mundoDelJuego->getTData(x,y,CAPA_MAXIMA + 1)->getFicha()->setTipo(SOLDADO);
                mundoDelJuego->getTData(x,y,CAPA_MAXIMA + 1)->getFicha()->setJugadorOwner(i + 1);
                a++;
            }
        }
        a = 0, x = 0, y = 0;
    }
}

void cargarFichas(Mapa* mundoDelJuego, std::string tipoDeMundo, int cantidadJugadores) {
    cargarSoldados(mundoDelJuego,tipoDeMundo,cantidadJugadores);
}

// Precondiciones: Se espera que se 'mundoDelJuego' inicializado en tipo 'CAPA_AIRE', 'jugadores' debe ser un array de punteros a objetos del tipo 'Jugador' declarados de forma dinámica. ('jugadores' es un array estático)
// Postcondiciones: La función carga todo el juego según lo que pida el usuario.
void cargarJuego(Mapa* mundoDelJuego,Lista<Jugador*> jugadores, int cantidadJugadores, std::string tipoDeMundo, std::string* nombres[]) {
    srand(unsigned(time(NULL)));
    mundoDelJuego = new Mapa(cantidadJugadores*4, cantidadJugadores*4, cantidadJugadores*4);
    generarMundo(mundoDelJuego,tipoDeMundo);
    // inicializar jugadores
    cargarFichas(mundoDelJuego,tipoDeMundo,cantidadJugadores);
}