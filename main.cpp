#include "./Headers/Tablero.h"
#include "./Headers/Celda.h"
#include "./Headers/Renderizador.h"
#include <iostream>
#include <map>
using namespace std;

struct Coordenada{int x,y,z;};
struct Niveles{int suelo,mar;};

typedef map<string, Coordenada> MapaCoordenadas;

MapaCoordenadas getMapaCoordenadas(){
    MapaCoordenadas mapa;
    mapa["w"] = {0,0,1};
    mapa["a"] = {-1,0,0};
    mapa["s"] = {0,0,-1};
    mapa["d"] = {1,0,0};
    mapa["W"] = {0,0,1};
    mapa["A"] = {-1,0,0};
    mapa["S"] = {0,0,-1};
    mapa["D"] = {1,0,0};
}

// Carga el terreno de juego
void cargarMapa(Tablero<Celda*>* tablero){
    for(int x = 0; x < tablero->getTamanioX(); x++){
        for(int y = 0; y < tablero->getTamanioY(); y++){
            for(int z = 0; z < 4; z++){
                bool rango = (x < tablero->getTamanioX()/1.5) ? true : false;
                tablero->getTData(x, y, z)->setTipo((rango && z != 3)? CAPA_TIERRA : (rango && z==3)? CAPA_PASTO : CAPA_AGUA);
            }
        }
    }
    tablero->getTData(tablero->getTamanioX()-1,tablero->getTamanioY()-1,2)->getFicha()->setTipo(SUBMARINO);
    tablero->getTData(tablero->getTamanioX()-1,tablero->getTamanioY()-1,2)->getFicha()->setJugadorOwner(5);
    tablero->getTData(tablero->getTamanioX()-1,tablero->getTamanioY()-1,2)->getFicha()->setNumFicha(1);
    tablero->getTData(tablero->getTamanioX()-1,tablero->getTamanioY()-1,2)->setTipo(CAPA_ARENA);

    tablero->getTData(tablero->getTamanioX()-2,tablero->getTamanioY()-2,2)->getFicha()->setTipo(MINA_FICHA);
    tablero->getTData(tablero->getTamanioX()-2,tablero->getTamanioY()-2,2)->getFicha()->setNumFicha(2);
    tablero->getTData(tablero->getTamanioX()-2,tablero->getTamanioY()-2,2)->setTipo(CAPA_MINA);
}

// Pide un tipo de ficha
string pedirOpcion() {
    string opcion;
    cout << "Elegir: Avion Soldado Tanque Barco [Submarino]" << endl;
    cin >> opcion;
    return opcion;
}

// Pide el número de la ficha para distinguirlas del mismo tipo en el resto
int pedirEnumeracion() {
    int opcion;
    cout << "Ingresar numero (1)" << endl;
    cin >> opcion;
    return opcion;
}

// Si la ficha se encuentra en el mundo se retorna verdadero
bool seEncuentraLaFicha(Tablero<Celda*>* tablero, string opcion, int enumeracionFicha, int x, int y, int z) {
    bool seEncontro = false;
    if (opcion == "soldado"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == SOLDADO) 
        && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }else if (opcion == "tanque"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == TANQUE) 
        && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }else if (opcion == "barco"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == BARCO) 
        && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }else if (opcion == "avion"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == AVION) 
        && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }else if (opcion == "submarino"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == SUBMARINO) 
        && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }
    return seEncontro; 
}

// Busca la capa máxima de suelo y mar. Cuidado que solo sirve para esta versión de mapa
Niveles buscarNiveles(Tablero<Celda*>* tablero) {
    Niveles nivel = {1,1};
    for(int z = 0; z < tablero->getTamanioZ(); z++){
        nivel.suelo = (tablero->getTData(0,0,z)->getTipo() == CAPA_TIERRA || tablero->getTData(0,0,z)->getTipo() == CAPA_PASTO) ? z + 1 : nivel.suelo;
        nivel.mar = (tablero->getTData(tablero->getTamanioX() - 1,tablero->getTamanioY() - 1,z)->getTipo() == CAPA_AGUA) ?  z + 1 : nivel.mar;
    }
    return nivel;
}

int nivelMinimoDeBusqueda(string ficha,Niveles nivel) {
    return (ficha == "soldado" || ficha == "tanque") ? nivel.suelo : (ficha == "barco" || ficha == "avion") ? nivel.mar : 0;
}

int nivelMaximoDeBusqueda(string ficha, Niveles nivel, int nivelMaxTablero) {
    return (ficha == "soldado" || ficha == "tanque") ? nivel.suelo : (ficha == "barco" || ficha == "avion" || ficha == "submarino") ? nivel.mar : nivelMaxTablero - 1;
}

// Realiza el barrido del mapa según los valores de 'minimo', 'maximo' más que los otros datos que reciben la función.
void procesarBusqueda(Coordenada* coorFicha, Tablero<Celda*>* tablero, string* ficha, int numeroFicha){
    int minimo, maximo;
    minimo = 0, maximo = tablero->getTamanioZ();
    Niveles nivel;
    nivel = buscarNiveles(tablero);
    minimo = nivelMinimoDeBusqueda(*ficha,nivel), maximo = nivelMaximoDeBusqueda(*ficha,nivel,maximo);
    for (int x = 0; x < tablero->getTamanioX(); x++){
        for(int y = 0; y < tablero->getTamanioY(); y++){
            for(int z = minimo; z <= maximo; z++){
                if (seEncuentraLaFicha(tablero,*ficha,numeroFicha,x,y,z)){
                    *coorFicha = {x,y,z};
                    x = tablero->getTamanioX();
                    y = tablero->getTamanioY();
                    z = tablero->getTamanioZ();
                }
            }
        }
    }
}

// Busca las Coordenada de la celda en donde está parada la ficha
void buscarCoordenadasFicha(Coordenada* coorFicha, Tablero<Celda*>* tablero, string* ficha){
    int nivelAire = 0, nivelMaximo = 0, enumeracionFicha = 0;
    string salir = "";
    do{ 
        *ficha = pedirOpcion();        
        enumeracionFicha = pedirEnumeracion();
        procesarBusqueda(coorFicha,tablero,ficha,enumeracionFicha);
        if (coorFicha->x == -1 && coorFicha->y == -1 && coorFicha->z == -1){
            cout << "\nLa ficha que usted intenta buscar fue eliminada de la jugada o es inexistente, vuelva a intentarlo.\n('t' para salir)\n-";
            cin >> salir;
        }
    } while ((coorFicha->x == -1 && coorFicha->y == -1 && coorFicha->z == -1) && (salir != "t"));
}

// Pide los movimientos longitudinales y horizontales (WASD). No existen movimientos diagonales ni de alturas.
void pedirAccion(char* movimiento){
        system("clear");
    cout << "Ingrese el movimiento:\n-Frontal y tracero: W y S\nLaterales: A y D\n(Puede mandar la letra 't' para salir)\n-";
    cin >> *movimiento;
}

// Revisa que las celdas cercanas sean de un tipo coherente a donde se va a mover la ficha (celda)
bool escanearCeldasPerifericasCompatibles(Tablero<Celda*>* tablero, Coordenada coordFicha, string ficha, char movimiento, Coordenada desplazarPor) {
    bool permitido = false;
    bool estado = tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z + desplazarPor.z)->getEstado();
    Capa tipo = tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z + desplazarPor.z)->getTipo();
    Capa tipoSiguiente = tablero->getTData(coordFicha.x + desplazarPor.x + desplazarPor.x,coordFicha.y + desplazarPor.y + desplazarPor.y,coordFicha.z + desplazarPor.z + desplazarPor.z)->getTipo();
    return ((ficha == "soldado" || ficha == "tanque") || (ficha == "barco" && tipoSiguiente == CAPA_AGUA) || (ficha == "avion" && tipo == CAPA_AIRE) || (ficha == "submarino" && tipo == CAPA_AGUA) && estado) ? true : false;
}

// Segun el movimiento que le ingrese el usuario se modifican los valores del estuct 'desplazar'
void ajustarDesplazamientosPorMovimiento(Coordenada* desplazar, string ficha, char movimiento) {
    if (movimiento == 'w' || movimiento == 's'){
        desplazar->x = (movimiento == 'w') ? 1 : -1;
    }else if (movimiento == 'a' || movimiento == 'd'){
        desplazar->y = (movimiento == 'a') ? 1 : -1;
    }else if((movimiento == 'e'|| movimiento == 'x') && (ficha == "avion" || ficha == "submarino")){
        desplazar->z = (movimiento == 'e') ? 1 : -1;
    }
}

void actualizarCoordenadasDeFicha(Coordenada* coordenadaFichaActual,Coordenada desplazar) {
    coordenadaFichaActual->x += desplazar.x;
    coordenadaFichaActual->y += desplazar.y;
    coordenadaFichaActual->z += desplazar.z;
}

void procesarIntercambioCeldas(Tablero<Celda*>* tablero, Coordenada coordenadaFichaActual, Coordenada desplazar, string ficha) {
    tablero->getTData((coordenadaFichaActual.x + desplazar.x),(coordenadaFichaActual.y + desplazar.y),(coordenadaFichaActual.z + desplazar.z))->setTipo(tablero->getTData((coordenadaFichaActual.x),(coordenadaFichaActual.y),(coordenadaFichaActual.z))->getTipo());
    *tablero->getTData((coordenadaFichaActual.x + desplazar.x),(coordenadaFichaActual.y + desplazar.y),(coordenadaFichaActual.z + desplazar.z))->getFicha() = *tablero->getTData((coordenadaFichaActual.x),(coordenadaFichaActual.y),(coordenadaFichaActual.z))->getFicha();
    tablero->getTData((coordenadaFichaActual.x + desplazar.x),(coordenadaFichaActual.y + desplazar.y),(coordenadaFichaActual.z + desplazar.z))->getFicha()->setTipo(VACIO);
    if (ficha == "soldado" || ficha == "tanque" || ficha == "avion"){
        tablero->getTData((coordenadaFichaActual.x),(coordenadaFichaActual.y),(coordenadaFichaActual.z))->setTipo(CAPA_AIRE);
    } else if(ficha == "submarino"){
        tablero->getTData((coordenadaFichaActual.x),(coordenadaFichaActual.y),(coordenadaFichaActual.z))->setTipo(CAPA_AGUA);
    }
}

// Simula el movimiento de las fichas para evaluar si se sale del mapa o no.
bool revisarLimitesDelMapa(Tablero<Celda*>* tablero, Coordenada coordenadaFichaActual, Coordenada desplazar) {
    return (coordenadaFichaActual.x + desplazar.x >= 0 && coordenadaFichaActual.x + desplazar.x < tablero->getTamanioX() 
        && coordenadaFichaActual.y + desplazar.y >= 0 && coordenadaFichaActual.y + desplazar.y < tablero->getTamanioY() 
        && coordenadaFichaActual.z + desplazar.z >= 0 && coordenadaFichaActual.z + desplazar.z < tablero->getTamanioZ()) ? true : false;
}

//Valida el cambio de celda dependiendo del contenido
void validarCambioDeCelda(Tablero<Celda*>* tablero,  Coordenada* coordenadaFichaActual, Coordenada desplazar, string ficha){
    
    string resultado = validarContenidoFicha(tablero->getTData(coordenadaFichaActual->x,coordenadaFichaActual->y, coordenadaFichaActual->z)
    ,tablero->getTData(coordenadaFichaActual->x + desplazar.x,coordenadaFichaActual->y + desplazar.y, coordenadaFichaActual->z + desplazar.z));
    cout << "entro validarCambioDeCelda"<<endl;
    if(resultado == "inactiva"){
        errorEnCeldaElegida(resultado);
    }else if(resultado == "vacia"){
        cout << "entro vacia"<<endl;
        procesarIntercambioCeldas(tablero,(*coordenadaFichaActual),desplazar,ficha);
        actualizarCoordenadasDeFicha(coordenadaFichaActual,desplazar);

    }else if(resultado == "destruir"){
        cout << "entro destruir"<<endl;
        tablero->getTData(coordenadaFichaActual->x,coordenadaFichaActual->y, coordenadaFichaActual->z)->getFicha()->setTipo(VACIO);
        tablero->getTData(coordenadaFichaActual->x,coordenadaFichaActual->y, coordenadaFichaActual->z)->getFicha()->setJugadorOwner(-1);
        tablero->getTData(coordenadaFichaActual->x + desplazar.x,coordenadaFichaActual->y + desplazar.y, coordenadaFichaActual->z + desplazar.z)->setEstado(false);
    
    }else if(resultado == "fichaJugador"){
        cout << "ficha jugador"<<endl;
        errorEnCeldaElegida(resultado);
    }else{
        tablero->getTData(coordenadaFichaActual->x,coordenadaFichaActual->y, coordenadaFichaActual->z)->getFicha()->setTipo(VACIO);
        tablero->getTData(coordenadaFichaActual->x,coordenadaFichaActual->y, coordenadaFichaActual->z)->getFicha()->setJugadorOwner(-1);

        tablero->getTData(coordenadaFichaActual->x + desplazar.x,coordenadaFichaActual->y + desplazar.y, coordenadaFichaActual->z + desplazar.z)->getFicha()->setTipo(VACIO);
        tablero->getTData(coordenadaFichaActual->x + desplazar.x,coordenadaFichaActual->y + desplazar.y, coordenadaFichaActual->z + desplazar.z)->getFicha()->setJugadorOwner(-1);
            
        //Inactivar Celda
        tablero->getTData(coordenadaFichaActual->x + desplazar.x,coordenadaFichaActual->y + desplazar.y, coordenadaFichaActual->z + desplazar.z)->setEstado(false);
    }
}

// Procesa los cambios de las celdas
void procesarMovimiento(char movimiento, Tablero<Celda*>* tablero, Coordenada* coordenadaFichaActual, string ficha){
    Celda celdaAuxiliar;
    Coordenada desplazar = {0,0,0};
    ajustarDesplazamientosPorMovimiento(&desplazar,ficha,movimiento);
    if (revisarLimitesDelMapa(tablero,(*coordenadaFichaActual),desplazar)){
        if (escanearCeldasPerifericasCompatibles(tablero,(*coordenadaFichaActual),ficha,movimiento,desplazar)){
            validarCambioDeCelda(tablero,coordenadaFichaActual,desplazar,ficha);
        }
    }
}

void colocarMina(Tablero<Celda*>* tablero, Coordenada coordenadaFichaActual, string ficha, char movimiento) {
    if (coordenadaFichaActual.z - 1 >= 0){
        if (ficha == "soldado" || ficha == "tanque"){
            tablero->getTData(coordenadaFichaActual.x,coordenadaFichaActual.y,coordenadaFichaActual.z - 1)->getMina()->setTipoMina(MINA_TERRESTRE);
        }else if (ficha == "barco" || "submarino"){
            tablero->getTData(coordenadaFichaActual.x,coordenadaFichaActual.y,coordenadaFichaActual.z - 1)->getMina()->setTipoMina(MINA_MARITIMA);
            tablero->getTData(coordenadaFichaActual.x,coordenadaFichaActual.y,coordenadaFichaActual.z - 1)->setTipo(CAPA_MINA);
        } else if (ficha == "avion"){
            tablero->getTData(coordenadaFichaActual.x,coordenadaFichaActual.y,coordenadaFichaActual.z - 1)->getMina()->setTipoMina(MINA_AEREA);
            tablero->getTData(coordenadaFichaActual.x,coordenadaFichaActual.y,coordenadaFichaActual.z - 1)->setTipo(CAPA_MINA);
        }
    }
}

void procesarCambiosMapa(Tablero<Celda*>* tablero, int size) {
    Coordenada imgSize = {size*100, size*70};
    BMP imagen;
    imagen.SetSize(imgSize.x,imgSize.y);
    imprimirAngulo(imgSize,(&imagen),tablero, getMap());
    imagen.WriteToFile("Partida.bmp");
}

// Cambia la casilla en la que se encuentra la ficha por la siguiente y viceversa, siempre y cuando se cumplan ciertas restricciones.
void usarFicha(Tablero<Celda*>* tablero, Coordenada* coordenadaFichaActual, string ficha, char* movimiento, int size) {
    // Después declarar movimiento acá. Por ahora no porque se usa para salir del while y limpiar la memoria.
    pedirAccion(movimiento);
    if ((*movimiento) == 'w' || (*movimiento) == 'a' || (*movimiento) == 's' || (*movimiento) == 'd' || (*movimiento) == 'e' || (*movimiento) == 'x'){
        procesarMovimiento((*movimiento),tablero,coordenadaFichaActual,ficha);
    }else if (*movimiento == 'q'){
        colocarMina(tablero,(*coordenadaFichaActual),ficha,(*movimiento));
    }
    procesarCambiosMapa(tablero,size);
}

int main(){
    string cortar = "",ficha = "";
    bool seguir = false;
    int size = 20;
    char movimiento;
    Coordenada coordenadaFichaActual = {-1,-1,-1};
    Tablero<Celda*>* tablero = new Tablero<Celda*>(size, size, size);
    cargarMapa(tablero);
    procesarCambiosMapa(tablero,size);
    while (!seguir){
        buscarCoordenadasFicha((&coordenadaFichaActual),tablero,(&ficha));
        if ((coordenadaFichaActual.x != -1) && (coordenadaFichaActual.y != -1) && (coordenadaFichaActual.z != -1)){
            while (movimiento != 't'){
                usarFicha(tablero,(&coordenadaFichaActual),ficha,(&movimiento),size);
            }
        }
        cout << "\nSeguir?('c' para salir)\n-";
        cin >> cortar;
        seguir = (cortar == "c") ? true : false;
    }
    delete tablero;
    return 0;
}