#include "./Headers/tablero.h"
#include "./Headers/celda.h"
#include "./Headers/renderizador.h"
#include <iostream>
using namespace std;

struct coordenadas{int x,y,z;};
struct Niveles{int suelo,mar;};
struct Desplazar{int x,y,z;};

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
    tablero->getTData(9,9,1)->getFicha()->setTipo(SOLDADO);
    tablero->getTData(9,9,1)->getFicha()->setNumFicha(1);
    tablero->getTData(9,9,1)->setTipo(CAPA_ARENA);
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
    }else if (opcion == "tanque"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == TANQUE) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }else if (opcion == "barco"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == BARCO) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }else if (opcion == "avion"){
        seEncontro = ((tablero->getTData(x,y,z)->getFicha()->getTipo() == AVION) && (tablero->getTData(x,y,z)->getFicha()->getNumFicha() == enumeracionFicha)) ? true : false ;
    }else if (opcion == "submarino"){
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
    cout << "Ingrese el movimiento:\n-Frontal y tracero: W y S\nLaterales: A y D\n(Puede mandar la letra 't' para salir)\n-";
    cin >> *movimiento;
}

// Revisa que las celdas cercanas sean de un tipo coherente a donde se va a mover la ficha (celda)
bool permitirPaso(Tablero<Celda*>* tablero, coordenadas coordFicha, string ficha, char movimiento, Desplazar desplazarPor) {
    bool permitido = false; 
    if (ficha == "soldado" || ficha == "tanque" || ficha == "barco"){
        // El condicional ternario que modifica a 'permitido' tiene una condición compleja tal que ( (este || otro ) ... (este || otro) && (este) ) || ( (este) && (otro) ) tienen que ver con revisar las capas periféricas a celda en donde estoy estacionado.
            permitido = ( (((tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z)->getTipo() == CAPA_PASTO) 
            || (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z)->getTipo() == CAPA_TIERRA) 
            || (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z)->getTipo() == CAPA_ARENA)) 
            && (ficha == "soldado" || ficha == "tanque")) 
            || ((tablero->getTData(coordFicha.x + 1,coordFicha.y,coordFicha.z)->getTipo() == CAPA_AGUA) && (ficha == "barco")) ) ? true : false;
    }else if (ficha == "avion" || ficha == "submarino"){
        // El condicional ternario que modifica a 'permitido' tiene una condición compleja tal que ((esto || otro) && (esto || otro)) tienen que ver con revisar las capas periféricas a celda en donde estoy estacionado.
            permitido = ( ((tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z + desplazarPor.z)->getTipo() == CAPA_AIRE) 
            && (ficha == "avion")) 
            || ((tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z + desplazarPor.z)->getTipo() == CAPA_AGUA) && (ficha == "submarino")) ) ? true : false;
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

// Procesa los cambios de las celdas
void procesarMovimiento(char movimiento, Tablero<Celda*>* tablero, coordenadas* fichaActual, string ficha){
    Celda celdaAuxiliar;
    Desplazar desplazar = {0,0,0};
    ajustarDesplazamientosPorMovimiento(&desplazar,ficha,movimiento);
    // Este if () es para evitar que se trate de hacer un intercambio de celdas con celdas inexistentes, evitando una violación de segmento
    if (fichaActual->x + desplazar.x >= 0 && fichaActual->x + desplazar.x < tablero->getTamanioX() && fichaActual->y + desplazar.y >= 0 && fichaActual->y + desplazar.y < tablero->getTamanioY() && fichaActual->z + desplazar.z >= 0 && fichaActual->z + desplazar.z < tablero->getTamanioZ()){
        if (permitirPaso(tablero,*fichaActual,ficha,movimiento, desplazar)){
            // Guardo la siguiente celda próxima, anterior o laterales
                celdaAuxiliar = *tablero->getTData((fichaActual->x + desplazar.x),(fichaActual->y + desplazar.y),(fichaActual->z + desplazar.z));
            // La celda próxima, anterior o laterales son cambiadas por la celda en donde mi ficha está estacionada
                *tablero->getTData((fichaActual->x + desplazar.x),(fichaActual->y + desplazar.y),(fichaActual->z + desplazar.z)) = *tablero->getTData((fichaActual->x),(fichaActual->y),(fichaActual->z)); 
            // La celda en donde estaba parado es cambiada por la celda que estaba en la posicion anterior de la celda que contenía mi ficha.
                *tablero->getTData((fichaActual->x),(fichaActual->y),(fichaActual->z)) = celdaAuxiliar;
            // Actualizo los valores de posición por si quiero seguir moviendo las celdas
                fichaActual->x += desplazar.x;
                fichaActual->y += desplazar.y;
                fichaActual->z += desplazar.z;
        }
    }
}

// Cambia la casilla en la que se encuentra la ficha por la siguiente y viceversa, siempre y cuando se cumplan ciertas restricciones.
void moverFicha(Tablero<Celda*>* tablero, coordenadas* fichaActual, string ficha, char* movimiento) {
    pedirMovimiento(movimiento);
    procesarMovimiento(*movimiento,tablero,fichaActual,ficha);
}

void procesarMapa(Coordenada imgSize, BMP* imagen, Tablero<Celda*>* tablero) {
    imprimirAngulo(imgSize, imagen, tablero, getMap());
    imagen->WriteToFile("Partida.bmp");
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
        buscarCoordenadasFicha(&fichaActual,tablero,&ficha);
        while (movimiento != 't'){
            procesarMapa(imgSize, &imagen, tablero);
            moverFicha(tablero, &fichaActual, ficha, &movimiento);
            procesarMapa(imgSize, &imagen, tablero);
        }
        cout << "\nSeguir?(Puede mandar la letra 'c' para salir)\n-";
        cin >> cortar;
        seguir = (cortar == "c") ? true : false;
    }
    delete tablero;
    return 0;
}