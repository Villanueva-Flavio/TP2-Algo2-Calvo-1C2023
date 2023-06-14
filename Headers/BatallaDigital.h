#ifndef __BATALLA_DIGITAL_H__
#define __BATALLA_DIGITAL_H__

#include "Tablero.h"
#include "Jugador.h"
#include "Enums.h"


void cargarJuego(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, std::string* nombres, std::string nombreMundo, int numeroDeJugadores);

void mostrarTerreno(Tablero<Celda*>* tablero, int size);

void actualizarJuego(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, int turnoDelJugador);

EstadoJuego estadoDelJuego(Lista<Jugador*>* listaJugadores, int cantJugadores);


#include "../TPPs/BatallaDigital.tpp"

#endif  //__BATALLA_DIGITAL_H__