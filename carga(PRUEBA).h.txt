#ifndef __CARGA_H__
#define __CARGA_H__
#include "./Headers/Jugador.h"
#include "./Headers/Tablero.h"
#include <cmath>

void cargarJuego(Tablero<Celda*>* mundoDelJuego,Lista<Jugador*>* jugadores, int cantidadJugadores, std::string tipoDeMundo, std::string* nombres[]);

#endif 