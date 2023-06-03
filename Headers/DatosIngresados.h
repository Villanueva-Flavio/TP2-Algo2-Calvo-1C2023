#ifndef __DATOS_INGRESADOS_H__
#define __DATOS_INGRESADOS_H__

#include <string>

// muestra por pantalla un mensaje el nombre del juego y pide la cantidad de jugadores
void solicitarJugadores(int* cantJugadores);

void pedirDatosIniciales(int cantJugadores, std::string tipoDemapa, std::string* nombreJugadores, int* r, int* g , int* b);

//void realizarMovimiento();

//void colocarMina();

#include "../TPPs/Jugador.tpp"
#endif //__DATOS_INGRESADOS_H__