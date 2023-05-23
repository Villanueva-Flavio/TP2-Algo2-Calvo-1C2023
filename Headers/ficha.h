#ifndef __FICHA_H__
#define __FICHA_H__

enum TipoContenido {SOLDADO, TANQUE, BARCO, SUBMARINO, AVION, MINA_FICHA, CARTA, VACIO};

class Ficha{
    private:
        int jugadorOwner;
        int enumerador;
        TipoContenido tipo; 
    public:
        Ficha();
        void setTipo(TipoContenido tipo);
        TipoContenido getTipo();
        int getJugadorOwner();
        void setJugadorOwner(int jugadorOwner);
        int getNumFicha();
        void setNumFicha();
};
#endif