#include "./Headers/Tablero.h"
#include "./Headers/Celda.h"
#include "./Headers/Jugador.h"
#include "./Headers/BatallaDigital.h"
#include "./Headers/DatosIngresados.h"
#include <iostream>
#include <string>
using namespace std;


int main(){
    Lista<Jugador*>* listaJugadores = new Lista<Jugador*>();
    int cantJugadores = 0;
    int turnoDelJugador = 1;
    int r = 0, g = 0, b = 0;
    string tipoDeMapa = "";
    EstadoJuego estadoBatallaDigital = COMENZADO;
    char movimiento;
    coordenadas ubicacionMina;

    solicitarJugadores(&cantJugadores);
    int mapSize = cantJugadores*4;

    Tablero<Celda*>* tablero = new Tablero<Celda*>(mapSize, mapSize, mapSize);
    
    string* nombreJugadores = new string[cantJugadores];
    int* valoresR = new int[cantJugadores];
    int* valoresG = new int[cantJugadores];
    int* valoresB = new int[cantJugadores];


    pedirDatosIniciales(cantJugadores, tipoDeMapa, nombreJugadores, valoresR, valoresG ,valoresB);
    cargarJuego(tablero, listaJugadores, nombreJugadores, tipoDeMapa, cantJugadores);

    while(estadoBatallaDigital != FINALIZADO){
        pedirMovimiento(&movimiento);
        pedirUbicacionMina(&ubicacionMina, mapSize);
        //actualizarJuego(tablero, listaJugadores, turnoDelJugador);
        mostrarTerreno(tablero,mapSize);
        estadoBatallaDigital = estadoDelJuego(listaJugadores, cantJugadores);
        
        if(turnoDelJugador != cantJugadores) {
            turnoDelJugador++;
        } else {
            turnoDelJugador = 1;
        }
    }


    delete[] valoresR;
    delete[] valoresG;
    delete[] valoresB;
    delete[] nombreJugadores;
    delete tablero;
    delete listaJugadores;
    return 0;
}