#include "./Headers/Tablero.h"
#include "./Headers/Celda.h"
#include "./Headers/Renderizador.h"
#include <cmath>
#include <iostream>
using namespace std;

struct coordenadas{int x,y,z;};
struct Niveles{int suelo,mar;};
struct Desplazar{int x,y,z;};

bool noEsOrillaDelLago(Mapa* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    int radio = pow(x-mapa->getTamanioX()/2, 2) + (pow(y-mapa->getTamanioY()/2, 2)) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio < pow(size,1/0.80)){
        orilla = true;
    }
    return orilla;
}

bool esOrillaDelLago(Mapa* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    int radio = pow(x-mapa->getTamanioX()/2, 2) + (pow(y-mapa->getTamanioY()/2, 2)) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio > pow(size,1/0.80)){
        orilla = true;
    }
    return orilla;
}

bool esSegmentoLago(Mapa* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    int radio = pow(x-mapa->getTamanioX()/2, 2) + (pow(y-mapa->getTamanioY()/2, 2)) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio == pow(size,1/0.80)){
        orilla = true;
    }
    return orilla;
}

// Carga el terreno de juego
void dibujarEsfera(Mapa* mapa, int size) {
    for(int x = 0; x < mapa->getTamanioX(); x++) {
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < mapa->getTamanioZ()/2; z++) {
                if (noEsOrillaDelLago(mapa,x,y,z,size)){
                    mapa->getTData(x,y,z)->setTipo(CAPA_AGUA);
                }else if (esOrillaDelLago(mapa,x,y,z,size)){
                    if (z < mapa->getTamanioZ()/2) mapa->getTData(x,y,z)->setTipo(CAPA_TIERRA);
                    mapa->getTData(x,y,mapa->getTamanioZ()/2-1)->setTipo(CAPA_PASTO);
                }
                if (esSegmentoLago(mapa,x,y,z,size)){
                    mapa->getTData(x,y,mapa->getTamanioZ()/2-1)->setTipo(CAPA_ARENA);
                }
            }
        }
    }
}

// Pide un tipo de ficha
string pedirOpcion() {
    string opcion;
    cout << "Escriba el tipo de ficha que desea seleccionar:\n-avion\n-soldado\n-tanque\n-barco\n-submarino\n";
    cin >> opcion;
    return opcion;
}

// Pide el número de la ficha para distinguirlas del mismo tipo en el resto
int pedirEnumeracion() {
    int opcion;
    cout << "Ahora por favor elija el número de ficha que quiere buscar, esto para diferenciarla de las otras.\n-";
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
    int nivelMinimo = 0;
    if (ficha == "soldado" || ficha == "tanque"){
        nivelMinimo = nivel.suelo;
    } else if (ficha == "barco"){
        nivelMinimo = nivel.mar;
    } else if (ficha == "avion"){
        nivelMinimo = nivel.mar;
    } // Submarino no aparece porque el agua llega hasta abajo del mapa
    return nivelMinimo;
}

int nivelMaximoDeBusqueda(string ficha, Niveles nivel, int nivelMaxTablero) {
    int nivelMaximo = nivelMaxTablero - 1;
    if (ficha == "soldado" || ficha == "tanque"){
        nivelMaximo = nivel.suelo;
    } else if (ficha == "barco"){
        nivelMaximo = nivel.mar;
    } else if (ficha == "avion"){
        nivelMaximo = nivelMaxTablero - 1;
    } else if (ficha ==  "submarino"){
        nivelMaximo = nivel.mar;
    }
    return nivelMaximo;
}

// Realiza el barrido del mapa según los valores de 'minimo', 'maximo' más que los otros datos que reciben la función.
void procesarBusqueda(coordenadas* coorFicha, Tablero<Celda*>* tablero, string* ficha, int numeroFicha){
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

// Busca las coordenadas de la celda en donde está parada la ficha
void buscarCoordenadasFicha(coordenadas* coorFicha, Tablero<Celda*>* tablero, string* ficha){
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
bool escanearCeldasPerifericasCompatibles(Tablero<Celda*>* tablero, coordenadas coordFicha, string ficha, char movimiento, Desplazar desplazarPor) {
    bool permitido = false;
    if (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z + desplazarPor.z)->getEstado() == true){
        if (ficha == "soldado" || ficha == "tanque"){
            permitido = true;
        }
        else if (ficha == "barco"){
            if (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z - 1)->getTipo() == CAPA_AGUA){
                permitido = true;
            }
        }
        else if (ficha == "avion" || ficha == "submarino"){
            if (ficha == "avion"){  
                if (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z + desplazarPor.z)->getTipo() == CAPA_AIRE){
                    permitido = true;
                }
            }
            else if (ficha == "submarino"){
                if (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z + desplazarPor.z)->getTipo() == CAPA_AGUA){
                    permitido = true;
                }
            }
        }
    }
    return permitido;
}

// Segun el movimiento que le ingrese el usuario se modifican los valores del estuct 'desplazar'
void ajustarDesplazamientosPorMovimiento(Desplazar* desplazar, string ficha, char movimiento) {
    if (movimiento == 'w' || movimiento == 's'){
        desplazar->x = (movimiento == 'w') ? 1 : -1;
    }else if (movimiento == 'a' || movimiento == 'd'){
        desplazar->y = (movimiento == 'a') ? 1 : -1;
    }else if((movimiento == 'e'|| movimiento == 'x') && (ficha == "avion" || ficha == "submarino")){
        desplazar->z = (movimiento == 'e') ? 1 : -1;
    }
}

void actualizarCoordenadasDeFicha(coordenadas* coordenadaFichaActual,Desplazar desplazar) {
    coordenadaFichaActual->x += desplazar.x;
    coordenadaFichaActual->y += desplazar.y;
    coordenadaFichaActual->z += desplazar.z;
}

void procesarIntercambioCeldas(Tablero<Celda*>* tablero, coordenadas coordenadaFichaActual, Desplazar desplazar, string ficha) {
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
bool revisarLimitesDelMapa(Tablero<Celda*>* tablero, coordenadas coordenadaFichaActual, Desplazar desplazar) {
    bool rangoValido = false;
    Coordenada desplazamientoHipotetico = {coordenadaFichaActual.x + desplazar.x,coordenadaFichaActual.y + desplazar.y,coordenadaFichaActual.z + desplazar.z};
    int topeMaximoX = tablero->getTamanioX(), topeMaximoY = tablero->getTamanioY(), topeMaximoZ = tablero->getTamanioZ();

    if (desplazamientoHipotetico.x >= 0 && desplazamientoHipotetico.x < topeMaximoX
        && desplazamientoHipotetico.y >= 0 && desplazamientoHipotetico.y < topeMaximoY
        && desplazamientoHipotetico.z >= 0 && desplazamientoHipotetico.z < topeMaximoZ){
        rangoValido = true;
    }
    return rangoValido;
}

// Procesa los cambios de las celdas
void procesarMovimiento(char movimiento, Tablero<Celda*>* tablero, coordenadas* coordenadaFichaActual, string ficha){
    Celda celdaAuxiliar;
    Desplazar desplazar = {0,0,0};
    ajustarDesplazamientosPorMovimiento(&desplazar,ficha,movimiento);
    if (revisarLimitesDelMapa(tablero,(*coordenadaFichaActual),desplazar)){
        if (escanearCeldasPerifericasCompatibles(tablero,(*coordenadaFichaActual),ficha,movimiento,desplazar)){
            procesarIntercambioCeldas(tablero,(*coordenadaFichaActual),desplazar,ficha);
            actualizarCoordenadasDeFicha(coordenadaFichaActual,desplazar);
        }
    }
}

void colocarMina(Tablero<Celda*>* tablero, coordenadas coordenadaFichaActual, string ficha, char movimiento) {
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
void moverFichas(Tablero<Celda*>* tablero, int size) {
    string cortar = "",ficha = "";
    coordenadas coordenadaFichaActual = {-1,-1,-1};
    bool seguir = false;
    char movimiento;
    while (!seguir){
        buscarCoordenadasFicha((&coordenadaFichaActual),tablero,(&ficha));
        if ((coordenadaFichaActual.x != -1) && (coordenadaFichaActual.y != -1) && (coordenadaFichaActual.z != -1)){
            while (movimiento != 't'){
                pedirAccion(&movimiento);
                if ((movimiento) == 'w' || (movimiento) == 'a' || (movimiento) == 's' || (movimiento) == 'd' || (movimiento) == 'e' || (movimiento) == 'x'){
                    procesarMovimiento((movimiento),tablero,&coordenadaFichaActual,ficha);
                }else if (movimiento == 'q'){
                    colocarMina(tablero,(coordenadaFichaActual),ficha,(movimiento));
                }
                procesarCambiosMapa(tablero,size);
            }
        }
        cout << "\nSeguir?(Puede mandar la letra 'c' para salir)\n-";
        cin >> cortar;
        seguir = (cortar == "c") ? true : false;
    }
}

int main(){
    int size = 8;
    Tablero<Celda*>* tablero = new Tablero<Celda*>(size, size, size);
    dibujarEsfera(tablero,size);
    // procesarCambiosMapa(tablero,size);
    // moverFichas(tablero,size);
    procesarCambiosMapa(tablero,size);
    delete tablero;
    return 0;
}