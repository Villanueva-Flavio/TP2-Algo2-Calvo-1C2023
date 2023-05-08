#include <string>

class ficha{
    private:
        std::string* tipo;
        bool* activa;
        int* coorX, *coorY, *coorZ;
        int* vida;
    public:
        ficha();
        ~ficha();
        void setCoords(int x, int y, int z);
        void setTipo(std::string nombre);
        void setActiva(bool estado);
        void setVida(int danio);
        int getCoords(char coordenada);
        std::string getTipo();
        bool getActiva();
        int getVida();
};

// Constructor y destructor en las siguietes dos lineas
ficha::ficha() {
    this->tipo = new std::string("");
    this->activa = new bool(true);
    this->coorX = new int(0);
    this->coorY = new int(0);
    this->coorZ = new int(0);
    this->vida = new int(0);
}
ficha::~ficha() {
    delete tipo;
    delete activa;
    delete coorX;
    delete coorY;
    delete coorZ;    
    delete vida;
}

// Pre: recibe un número entero por parámetro, si o si un valor para cada uno. No se puede poner solo un parámetro.
// Post: dcambia los valores de la coordenadas en los atributos. 
void ficha::setCoords(int x, int y, int z) {
    *coorX = x;
    *coorY = y;
    *coorZ = z;
}

// Pre: recibe el nombre que va a recibir el nombre de la ficha, este es un string.
// Post: cambia el contenido del atributo 'tipo'
void ficha::setTipo(std::string nombre) {
    *tipo = nombre;
}

// Pre: recibe un bool sin más.
// Post: cambia el bool del atributo 'activa'.
void ficha::setActiva(bool estado) {
    *activa = estado;
}

// Pre: recibe un valor entero.
// Post: cambia el valor del atributo 'vida' mediante una resta de 'vida' con el valor ingresado en el parámetro.
void ficha::setVida(int danio) {
    *vida -= danio;
}

// Pre: recibe la coordenada que se quiere obtener x,y,z respectivamente como caracteres.
// Post: devuelve la coordenada pedida. 
int ficha::getCoords(char coordenada) {
    if (coordenada == 'x') return *coorX;
    else if (coordenada == 'y') return *coorY;
    else if (coordenada == 'z') return *coorZ;
    return -1;
}

// Post: devuelve el contenido del atributo 'tipo'.
std::string ficha::getTipo() {
    return *tipo;
}

// Post: devuelve el contenido del atributo 'activa'.
bool ficha::getActiva() {
    return *activa;
}

// Post: devuelve el contenido del atributo 'vida'.
int ficha::getVida() {
    return *vida;
}