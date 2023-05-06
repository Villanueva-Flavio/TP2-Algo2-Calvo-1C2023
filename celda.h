#ifndef __CELDA_H__
#define __CELDA_H__

enum TipoCelda {TIERRA, AGUA, AIRE};
enum TipoContenido {SOLDADO, ARMAMENTO, MINA, CARTA, VACIO};

class Celda {
    private:
        TipoCelda tipo;
        TipoContenido contenido;
        bool estado;

    public:

        Celda(TipoCelda tipoCelda);

        TipoCelda getTipo();

        TipoContenido getEntidad();

        void setTipo(TipoCelda tipo);

        void setEntidad(TipoContenido entidad);

        void setEstado(bool estado);

        bool getEstado();
};

Celda::Celda(TipoCelda tipoCelda) {
    this->tipo = tipoCelda;
}

bool Celda::getEstado() {
    return this->estado;
}

void Celda::setEstado(bool estado) {
    this->estado = estado;
}

TipoCelda Celda::getTipo() {
    return this->tipo;
}

TipoContenido Celda::getEntidad() {
    return this->contenido;
}

void Celda::setTipo(TipoCelda tipo) {
    this->tipo = tipo;
}

void Celda::setEntidad(TipoContenido entidad) {
    this->contenido = entidad;
}

#endif