#include <string>

enum TipoContenido {SOLDADO, ARMAMENTO, MINA, CARTA, VACIO};

class Ficha{
    private:
        int jugadorOwner;
        std::string tipo; // revisar los enums y cambiar 
    public:
        Ficha(TipoContenido contenido);
        void setTipo(std::string nombre);
        std::string getTipo();
        int getJugadorOwner();
        void setJugadorOwner(int jugadorOwner);
};

// Constructor y destructor en las siguietes dos lineas
Ficha::Ficha(TipoContenido contenido) {
    this->tipo = "";
    this->jugadorOwner = NULL;
}

int Ficha::getJugadorOwner() {
    return this->jugadorOwner;
}

void Ficha::setJugadorOwner(int jugadorOwner) {
    this->jugadorOwner = jugadorOwner;
}

// Pre: recibe el nombre que va a recibir el nombre de la Ficha, este es un string.
// Post: cambia el contenido del atributo 'tipo'
void Ficha::setTipo(std::string nombre) {
    this->tipo = nombre;
}

// Post: devuelve el contenido del atributo 'tipo'.
std::string Ficha::getTipo() {
    return this->tipo;
}