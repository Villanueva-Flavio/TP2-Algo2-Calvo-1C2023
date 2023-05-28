#include "./Headers/tablero.h"
#include "./Headers/celda.h"
#include "./Headers/renderizador.h"
#include <iostream>
using namespace std;

struct coordenadas{int x; int y; int z;};
struct Niveles{int suelo;int mar;};

// Carga el terreno de juego
void cargarMapa(Tablero<Celda*>* tablero){
    for(int x = 0; x < tablero->getTamanioX(); x++){
        for(int y = 0; y < tablero->getTamanioY(); y++){
            if (x < (tablero->getTamanioX()/1.5)){
                tablero->getTData(x, y, 0)->setTipo(CAPA_TIERRA);
                tablero->getTData(x, y, 1)->setTipo(CAPA_PASTO);
            }else {
                tablero->getTData(x, y, 0)->setTipo(CAPA_AGUA);
                tablero->getTData(x, y, 1)->setTipo(CAPA_AGUA);
            }
        }
    }
    tablero->getTData(2,2,1)->getFicha()->setTipo(SOLDADO);
    tablero->getTData(2,2,1)->getFicha()->setNumFicha(1);
    tablero->getTData(2,2,1)->setTipo(CAPA_MINA);
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
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == SOLDADO) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }
    else if (opcion == "tanque"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == TANQUE) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }
    else if (opcion == "barco"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == BARCO) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }
    else if (opcion == "avion"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == AVION) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }
    else if (opcion == "submarino"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == SUBMARINO) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }
    return seEncontro; 
}

// Busca la capa máxima de suelo y mar. Cuidado que solo sirve para esta versión de mapa
Niveles buscarNiveles(Tablero<Celda*>* tablero) {
    Niveles nivel;
    nivel.suelo = 0;
    nivel.mar = 0;
    for(int z = 0; z < tablero->getTamanioZ(); z++){
        nivel.suelo = (tablero->getTData(0,0,z)->getTipo() == CAPA_TIERRA || tablero->getTData(0,0,z)->getTipo() == CAPA_PASTO) ? z + 1 : nivel.suelo;
        nivel.mar = (tablero->getTData(tablero->getTamanioX() - 1,tablero->getTamanioY() - 1,z)->getTipo() == CAPA_AGUA) ?  z + 1 : nivel.mar;
    }
    return nivel;
}

// Devuelve el máximo valor de iteración de z según la ficha que eligió el usuario
int nivelMaximoDeBusqueda(string ficha, Niveles nivel, int nivelMaximo){
    int capa = nivelMaximo;
    if (ficha == "soldado" || ficha == "tanque" || ficha == "submarino"){
        capa = (ficha == "soldado" || ficha == "tanque") ? nivel.suelo : capa;
        capa = (ficha == "submarino") ? nivel.mar : capa;
    }
    return capa;
}

// Realiza el barrido del mapa según los valores de 'minimo', 'maximo' más que los otros datos que reciben la función.
void procesarBusqueda(coordenadas* coorFicha, Tablero<Celda*>* tablero, string* ficha, int minimo, int maximo, int numeroFicha){
    for (int x = 0; x < tablero->getTamanioX(); x++){
        for(int y = 0; y < tablero->getTamanioY(); y++){
            for(int z = (*ficha == "avion") ? minimo : 0; z < maximo; z++){
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
    Niveles nivel;
    int nivelAire = 0; 
    int nivelMaximo = 0;
    int enumeracionFicha = 0;
    do{ nivel = buscarNiveles(tablero);
        *ficha = pedirOpcion();
        nivelMaximo = nivelMaximoDeBusqueda(*ficha,nivel,tablero->getTamanioZ());
        nivelAire = (nivel.suelo >= nivel.mar) ? nivel.suelo : nivel.mar;
        enumeracionFicha = pedirEnumeracion();
        procesarBusqueda(coorFicha,tablero,ficha,nivelAire,nivelMaximo,enumeracionFicha);
        if (coorFicha->x == -1 && coorFicha->y == -1 && coorFicha->z == -1){
            cout << "\nLa ficha que usted intenta buscar fue eliminada de la jugada o es inexistente, vuelva a intentarlo.\n";
        }
    } while (coorFicha->x == -1 && coorFicha->y == -1 && coorFicha->z == -1);
}

// Pide los movimientos longitudinales y horizontales (WASD). No existen movimientos diagonales ni de alturas.
void pedirMovimiento(char* movimiento){
        system("clear");
    cout << "Ingrese el movimiento:\n-Frontal y tracero: W y S\nLaterales: A y D\n(Puede mandar la letra 'f' para salir)\n-";
    cin >> *movimiento;
}
// Usando la lógica de 'moverLongitudinalmente( )' lo hace pero con casillas que se encuentren a los laterales en donde se encuentra la ficha a desplazar.
void moverLongitudinalmente(char movimiento, Tablero<Celda*>* tablero, coordenadas* fichaActual, string ficha){
    Celda auxiliar;
    if (movimiento == 'W'){
        if ((fichaActual->x + 1) < tablero->getTamanioX()){
                system("clear");
                cout << "\n(" << fichaActual->x + 1 << fichaActual->y << fichaActual->z << ")\n";
            auxiliar = *tablero->getTData((fichaActual->x + 1),(fichaActual->y),(fichaActual->z));
            *tablero->getTData((fichaActual->x + 1),(fichaActual->y),(fichaActual->z)) = *tablero->getTData((fichaActual->x),(fichaActual->y),(fichaActual->z)); 
            *tablero->getTData((fichaActual->x),(fichaActual->y),(fichaActual->z)) = auxiliar;
            fichaActual->x++;           
        }
    }
    else if (movimiento == 'S'){
        if ((fichaActual->x - 1) >= 0){
                system("clear");
                cout << "\n(" << fichaActual->x - 1 << fichaActual->y << fichaActual->z << ")\n";
            auxiliar = *tablero->getTData((fichaActual->x - 1),(fichaActual->y),(fichaActual->z));
            *tablero->getTData((fichaActual->x - 1),(fichaActual->y),(fichaActual->z)) = *tablero->getTData((fichaActual->x),(fichaActual->y),(fichaActual->z)); 
            *tablero->getTData((fichaActual->x),(fichaActual->y),(fichaActual->z)) = auxiliar;
            fichaActual--;
        }
    }
}

// Usando la lógica de 'moverLongitudinalmente( )' lo hace pero con casillas que se encuentren a los laterales en donde se encuentra la ficha a desplazar.
void moverLateralmente(char movimiento, Tablero<Celda*>* tablero, coordenadas* fichaActual, string ficha){
    Celda auxiliar;
    if (movimiento == 'A'){
        if ((fichaActual->y + 1) < tablero->getTamanioY()){
                system("clear");
                cout << "\n(" << fichaActual->x << fichaActual->y + 1 << fichaActual->z << ")\n";
            auxiliar = *tablero->getTData((fichaActual->x),(fichaActual->y + 1),(fichaActual->z)); 
            *tablero->getTData((fichaActual->x),(fichaActual->y + 1),(fichaActual->z)) = *tablero->getTData((fichaActual->x),(fichaActual->y),(fichaActual->z));
            *tablero->getTData((fichaActual->x),(fichaActual->y),(fichaActual->z)) = auxiliar;
            fichaActual->y++;
        }
    }
    else if (movimiento == 'D'){
        if ((fichaActual->y - 1) >= 0){
                system("clear");
                cout << "\n(" << fichaActual->x << fichaActual->y - 1 << fichaActual->z << ")\n";
            auxiliar = *tablero->getTData((fichaActual->x),(fichaActual->y - 1),(fichaActual->z)); 
            *tablero->getTData((fichaActual->x),(fichaActual->y - 1),(fichaActual->z)) = *tablero->getTData((fichaActual->x),(fichaActual->y),(fichaActual->z));
            *tablero->getTData((fichaActual->x),(fichaActual->y),(fichaActual->z)) = auxiliar;
            fichaActual->y--;
        }      
    }
}

// Cambia la casilla en la que se encuentra la ficha por la siguiente y viceversa, siempre y cuando se cumplan ciertas restricciones.
void moverFicha(Tablero<Celda*>* tablero, coordenadas* fichaActual, string ficha, char* movimiento) {
    pedirMovimiento(movimiento);
    moverLongitudinalmente(*movimiento,tablero,fichaActual,ficha);
    moverLateralmente(*movimiento,tablero,fichaActual,ficha);
    fichaActual = fichaActual;
}

int main(){
    bool seguir = false;
    string cortar = "";
    int size = 20;
    string ficha;
    char movimiento;
    
    coordenadas fichaActual = {-1,-1,-1};

    Coordenada imgSize = {size*100, size*70};
    BMP imagen;
    imagen.SetSize(imgSize.x, imgSize.y);
    
    Tablero<Celda*>* tablero = new Tablero<Celda*>(size, size, size);
    cargarMapa(tablero);
    while (!seguir){

        imprimirAngulo(imgSize, &imagen, tablero, getMap());
        imagen.WriteToFile("Partida.bmp");

        buscarCoordenadasFicha(&fichaActual,tablero,&ficha);
        while (movimiento != 't'){
            moverFicha(tablero, &fichaActual, ficha, &movimiento);
            imprimirAngulo(imgSize, &imagen, tablero, getMap());
            imagen.WriteToFile("Partida.bmp");
        }
        cout << "\nSeguir?(Puede mandar la letra 'c' para salir)\n-";
        cin >> cortar;
        seguir = (cortar == "c") ? true : false;
    }
    delete tablero;
    return 0;
}