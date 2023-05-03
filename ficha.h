#include <string>

class ficha{
    private:
        std::string tipo;
        bool activa;
        int coorX, coorY, coorZ;
    public:
        ficha();
        void setCoords(int x, int y, int z);
        void setTipo(std::string nombre);
        void setActiva(bool estado);
        int getCoords(char coordenada);
        std::string getTipo();
        bool getActiva();
};

// Constructor y destructor en las siguietes dos lineas
ficha::ficha() {
    this->tipo = "";
    this->activa = true;
    this->coorX = 0;
    this->coorY = 0;
    this->coorZ = 0;
}

// Pre: recibe un número entero por parámetro, si o si un valor para cada uno. No se puede poner solo un parámetro.
// Post: dcambia los valores de la coordenadas en los atributos. 
void ficha::setCoords(int x, int y, int z) {
    this->coorX = x;
    this->coorY = y;
    this->coorZ = z;
}

// Pre: recibe el nombre que va a recibir el nombre de la ficha, este es un string.
// Post: cambia el contenido del atributo 'tipo'
void ficha::setTipo(std::string nombre) {
    this->tipo = nombre;
}

// Pre: recibe un bool sin más.
// Post: cambia el bool del atributo 'activa'.
void ficha::setActiva(bool estado) {
    this->activa = estado;
}

// Pre: recibe la coordenada que se quiere obtener x,y,z respectivamente como caracteres.
// Post: devuelve la coordenada pedida. 
int ficha::getCoords(char coordenada) {
    if (coordenada == 'x') return this->coorX;
    else if (coordenada == 'y') return this->coorY;
    else if (coordenada == 'z') return this->coorZ;
    return -1;
}

// Post: devuelve el contenido del atributo 'tipo'.
std::string ficha::getTipo() {
    return this->tipo;
}

// Post: devuelve el contenido del atributo 'activa'.
bool ficha::getActiva() {
    return this->activa;
}