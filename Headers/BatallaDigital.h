#ifndef __BATALLA_DIGITAL_H__
#define __BATALLA_DIGITAL_H__
#include "Tablero.h"
#include "Celda.h"
#include "Jugador.h"

typedef Tablero<Celda*> Mapa;
typedef Lista<Jugador*> Jugadores;

class BatallaDigital{
    private:
        Mapa* mapa;
        Jugadores* jugadores;
        string tipoMapa;
        int cantidadJugadores;
        int turno;
    public:
        BatallaDigital(int cantidad);
        ~BatallaDigital();
        void cargarJuego();
        void consultarNombres();
        void consultarTipoDeMapa(string tipoMapa);
        void consultarColores();

};
#endif