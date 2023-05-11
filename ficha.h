#include <string>
class ficha{
    private:
        int jugadorOwner;
        std::string tipo; // revisar los enums y cambiar 
    public:
        ficha();
        void setTipo(std::string nombre);
        std::string getTipo();
        int getJugadorOwner();
        void setJugadorOwner(int jugadorOwner);
};

// Constructor y destructor en las siguietes dos lineas
ficha::ficha() {
    this->tipo = "";
    this->jugadorOwner = NULL;
}

int ficha::getJugadorOwner() {
    return this->jugadorOwner;
}

void ficha::setJugadorOwner(int jugadorOwner) {
    this->jugadorOwner = jugadorOwner;
}

// Pre: recibe el nombre que va a recibir el nombre de la ficha, este es un string.
// Post: cambia el contenido del atributo 'tipo'
void ficha::setTipo(std::string nombre) {
    this->tipo = nombre;
}

// Post: devuelve el contenido del atributo 'tipo'.
std::string ficha::getTipo() {
    return this->tipo;
}