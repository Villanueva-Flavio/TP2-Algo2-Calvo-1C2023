#ifndef __CARGAR_H__
#define __CARGAR_H__

#include "Tablero.h"
#include "Jugador.h"
/*
#include <cstdlib>
#include <ctime>
#include <cmath>*/

void cargarJuego(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, std::string* nombres, std::string nombreMundo, int numeroDeJugadores);

#include "../TPPs/Cargar.tpp"

#endif
