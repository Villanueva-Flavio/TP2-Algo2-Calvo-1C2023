#include "Tablero.h"
#include "Celda.h"
#include <string>

#ifndef __INTERACCIONES_H__
#define __INTERACCIONES_H__

//Pre:recibe la celda dell jugador actual y la celda a la que desea trasladarse
//Post: Devuelve un string que inidicara el evento que se debe desencadenar dependiendo del tipo de ficha 
std::string validarContenidoFicha(Celda* celdaJugador, Celda* celdaElegida);

//Pre:Recibe una celda que contiene una ficha del tipo armamento
//Post: Devuelve un string que inidicara el evento que se debe desencadenar dependiendo del tipo de ficha 
std::string validacionArmamento(Celda* celdaJugador, Celda* celdaElegida);

//Pre:Recibe una celda que contiene una ficha del tipo soldado
//Post: Devuelve un string que inidicara el evento que se debe desencadenar dependiendo del tipo de ficha 
std::string validacionSoldado(Celda* celdaJugador, Celda* celdaElegida);

//Pre:recibe el contenido de una ficha
//Post:devuelve true si la ficha es armamento y false de caso contrario 
bool esArmamento(TipoContenido contenidoFicha);

//Pre:recibe como parametro dos celdas 
//Post: evalua si las fichas contenidas pertenecen al mismo jugador, devuelve true en caso de que lo sean, y false en caso contrario
bool esFichaDelJugadorActual(Celda* celdaJugador, Celda* celdaElegida);

//Pre: recibe el estado de la validacion
//Post: devuelve una alarte por consola al ussuario para que solucione el error
void errorEnCeldaElegida(std::string resultado);

#endif