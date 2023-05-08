#ifndef __CELDA_H__
#define __CELDA_H__

enum TipoCelda {TIERRA, AGUA, AIRE};
enum TipoContenido {SOLDADO, ARMAMENTO, MINA, CARTA, VACIO};

class Celda {
    private:
        TipoCelda tipo;
        TipoContenido contenido;
        int jugadorOwner;
    
    public:

        Celda();

        TipoCelda getTipo();

        TipoContenido getEntidad();

        int getJugadorOwner();

        void setTipo(TipoCelda tipo);

        void setEntidad(TipoContenido entidad);

        void setJugadorOwner(int jugadorOwner);
};

Celda::Celda() {
    this->tipo = AIRE;
    this->contenido = VACIO;
    this->jugadorOwner = -1;
}

TipoCelda Celda::getTipo() {
    return this->tipo;
}

TipoContenido Celda::getEntidad() {
    return this->contenido;
}

int Celda::getJugadorOwner() {
    return this->jugadorOwner;
}

void Celda::setTipo(TipoCelda tipo) {
    this->tipo = tipo;
}

void Celda::setEntidad(TipoContenido entidad) {
    this->contenido = entidad;
}

void Celda::setJugadorOwner(int jugadorOwner) {
    this->jugadorOwner = jugadorOwner;
}

#endif