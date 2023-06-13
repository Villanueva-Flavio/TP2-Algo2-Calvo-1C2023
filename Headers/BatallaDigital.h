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
        int cantidadJugadores;
        int turno;
        string tipoMapa;
    public:
        BatallaDigital(int cantidad);
        ~BatallaDigital();
        void cargarMapas();
    private:
        // Carga del mapa
        void cargarTerrenoPlano(TipoMapa tipo);
        void cargarPlaya(TipoMapa tipo);
        void cargarRioLago(TipoMapa tipo);
        bool esOrilla(TipoMapa tipo);
        // Carga de jugadores
        
};
#endif