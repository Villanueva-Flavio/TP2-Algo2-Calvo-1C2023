#ifndef __DATOS_INGRESADOS_H__
#define __DATOS_INGRESADOS_H__

#include <string>

struct coordenadas { int x, y, z; };

// Muestra por pantalla un mensaje el nombre del juego y pide la cantidad de jugadores
void solicitarJugadores(int* cantJugadores);

//  Para cada jugador, pide al usuario que ingrese el nombre y los valores RGB para el color del jugador
void pedirDatosIniciales(int cantJugadores, std::string& tipoDemapa, std::string* nombreJugadores, int* r, int* g , int* b);

//
void pedirMovimiento(char* movimiento);

void pedirUbicacionMina(coordenadas* ubicacionMina, int size);

#include "../TPPs/DatosIngresados.tpp"
#endif //__DATOS_INGRESADOS_H__