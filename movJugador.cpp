#include "movJugador.h"

using namespace std;            //

const char MOV_ARRIBA = 'w';
const char MOV_IZQUIERDA = 'a';
const char MOV_ABAJO = 's';
const char MOV_DERECHA = 'd';

void moverJugador(Mapa* batallaDigital, Coordenada posSoldado){

    char movimiento = ' ';
    int jugadorActual = -1;

    cout << "Ingrese un movimiento: \n";
    cin >> movimiento;

    while(movimiento != MOV_ABAJO && movimiento != MOV_ARRIBA && movimiento != MOV_DERECHA && movimiento != MOV_IZQUIERDA){

        cout << "\nIngresa un movimientos valido (W-A-S-D): ";
        cin >> movimiento;
        //AGREGAR VALIDACION DE MOVIMIENTO
    }

    cout << "Mov ingresado: " << movimiento;

    batallaDigital->getTData(posSoldado.x, posSoldado.y, posSoldado.z)->getFicha()->setTipo(VACIO);
    jugadorActual = batallaDigital->getTData(posSoldado.x, posSoldado.y, posSoldado.z)->getFicha()->getJugadorOwner();
    batallaDigital->getTData(posSoldado.x, posSoldado.y, posSoldado.z)->getFicha()->setJugadorOwner(-1);


    if(movimiento == MOV_ARRIBA){

        batallaDigital->getTData(posSoldado.x, posSoldado.y +1, posSoldado.z)->getFicha()->setTipo(SOLDADO);    //acomodar: el tipo de ficha se tiene q pasar por argumento
        batallaDigital->getTData(posSoldado.x, posSoldado.y +1, posSoldado.z)->getFicha()->setJugadorOwner(jugadorActual);
    }
    else if(movimiento == MOV_ABAJO){

        batallaDigital->getTData(posSoldado.x, posSoldado.y -1, posSoldado.z)->getFicha()->setTipo(SOLDADO);
        batallaDigital->getTData(posSoldado.x, posSoldado.y -1, posSoldado.z)->getFicha()->setJugadorOwner(jugadorActual);
    }
    else if(movimiento == MOV_DERECHA){

        batallaDigital->getTData(posSoldado.x +1, posSoldado.y, posSoldado.z)->getFicha()->setTipo(SOLDADO);
        batallaDigital->getTData(posSoldado.x +1, posSoldado.y, posSoldado.z)->getFicha()->setJugadorOwner(jugadorActual);
    }
    else{

        batallaDigital->getTData(posSoldado.x -1, posSoldado.y, posSoldado.z)->getFicha()->setTipo(SOLDADO);
        batallaDigital->getTData(posSoldado.x -1, posSoldado.y, posSoldado.z)->getFicha()->setJugadorOwner(jugadorActual);
    }

}