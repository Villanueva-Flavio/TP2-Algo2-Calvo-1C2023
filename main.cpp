#include "./Headers/Tablero.h"
#include "./Headers/Celda.h"
#include "./Headers/Renderizador.h"
#include "./Headers/Jugador.h"                 //???
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
                tablero->getTData(x, y, 1)->setTipo(CAPA_TIERRA);
                tablero->getTData(x, y, 2)->setTipo(CAPA_TIERRA);
                tablero->getTData(x, y, 3)->setTipo(CAPA_PASTO);
            }else {
                tablero->getTData(x, y, 0)->setTipo(CAPA_AGUA);
                tablero->getTData(x, y, 1)->setTipo(CAPA_AGUA);
                tablero->getTData(x, y, 2)->setTipo(CAPA_AGUA);
                tablero->getTData(x, y, 3)->setTipo(CAPA_AGUA);
            }
        }
    }
    tablero->getTData(16,16,5)->getFicha()->setTipo(AVION);
    tablero->getTData(16,16,5)->getFicha()->setNumFicha(1);
    tablero->getTData(16,16,5)->setTipo(CAPA_ARENA);
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
        cout << "\n" << x << y << z << "\n";
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
    if (ficha == "soldado" || ficha == "tanque"){
            if (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z - 1)->getEstado() == true){
                if (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z - 1)->getTipo() == CAPA_PASTO
                || tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z - 1)->getTipo() == CAPA_TIERRA
                || tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z - 1)->getTipo() == CAPA_ARENA){
                permitido = true;
            }
        }
    } else if (ficha == "barco"){
        if (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z - 1)->getEstado() == true){
            if (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z - 1)->getTipo() == CAPA_AGUA){
                permitido = true;
            }
        }
    }else if (ficha == "avion" || ficha == "submarino"){
        if (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z + desplazarPor.z)->getEstado() == true){
            if (((ficha == "avion") 
                && (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z + desplazarPor.z)->getTipo() == CAPA_AIRE)) 
                || ((ficha == "submarino") == CAPA_AGUA) && (tablero->getTData(coordFicha.x + desplazarPor.x,coordFicha.y + desplazarPor.y,coordFicha.z + desplazarPor.z)->getTipo())){
                permitido = true;
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

void procesarIntercambioCeldas(Tablero<Celda*>* tablero, coordenadas coordenadaFichaActual, Desplazar desplazar) {
    Celda celdaAuxiliar;
    // Guardo la siguiente celda próxima, anterior o laterales
        celdaAuxiliar = *tablero->getTData((coordenadaFichaActual.x + desplazar.x),(coordenadaFichaActual.y + desplazar.y),(coordenadaFichaActual.z + desplazar.z));
    // La celda próxima, anterior o laterales son cambiadas por la celda en donde mi ficha está estacionada
        *tablero->getTData((coordenadaFichaActual.x + desplazar.x),(coordenadaFichaActual.y + desplazar.y),(coordenadaFichaActual.z + desplazar.z)) 
        = *tablero->getTData((coordenadaFichaActual.x),(coordenadaFichaActual.y),(coordenadaFichaActual.z)); 
    // La celda en donde estaba parado es cambiada por la celda que estaba en la posicion anterior de la celda que contenía mi ficha.
        *tablero->getTData((coordenadaFichaActual.x),(coordenadaFichaActual.y),(coordenadaFichaActual.z)) = celdaAuxiliar;
}

// Simula el movimiento de las fichas para evaluar si se sale del mapa o no.
bool revisarLimitesDelMapa(Tablero<Celda*>* tablero, coordenadas coordenadaFichaActual, Desplazar desplazar) {
    return (coordenadaFichaActual.x + desplazar.x >= 0 && coordenadaFichaActual.x + desplazar.x < tablero->getTamanioX() 
        && coordenadaFichaActual.y + desplazar.y >= 0 && coordenadaFichaActual.y + desplazar.y < tablero->getTamanioY() 
        && coordenadaFichaActual.z + desplazar.z >= 0 && coordenadaFichaActual.z + desplazar.z < tablero->getTamanioZ()) ? true : false;
}

// Procesa los cambios de las celdas
void procesarMovimiento(char movimiento, Tablero<Celda*>* tablero, coordenadas* coordenadaFichaActual, string ficha){
    Celda celdaAuxiliar;
    Desplazar desplazar = {0,0,0};
    ajustarDesplazamientosPorMovimiento(&desplazar,ficha,movimiento);
    if (revisarLimitesDelMapa(tablero,(*coordenadaFichaActual),desplazar)){
        if (escanearCeldasPerifericasCompatibles(tablero,(*coordenadaFichaActual),ficha,movimiento, desplazar)){
            procesarIntercambioCeldas(tablero,(*coordenadaFichaActual),desplazar);
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

// Cambia la casilla en la que se encuentra la ficha por la siguiente y viceversa, siempre y cuando se cumplan ciertas restricciones.
void usarFicha(Tablero<Celda*>* tablero, coordenadas* coordenadaFichaActual, string ficha, char* movimiento) {
    // Después declarar movimiento acá. Por ahora no porque se usa para salir del while y limpiar la memoria.
    pedirAccion(movimiento);
    if ((*movimiento) == 'w' || (*movimiento) == 'a' || (*movimiento) == 's' || (*movimiento) == 'd'){
        procesarMovimiento((*movimiento),tablero,coordenadaFichaActual,ficha);
    }else if (*movimiento == 'q'){
        colocarMina(tablero,(*coordenadaFichaActual),ficha,(*movimiento));
    }
}

void procesarMapa(Tablero<Celda*>* tablero, int size) {
    Coordenada imgSize = {size*100, size*70};
    BMP imagen;
    imagen.SetSize(imgSize.x,imgSize.y);
    imprimirAngulo(imgSize,(&imagen),tablero, getMap());
    imagen.WriteToFile("Partida.bmp");
}

void inicializarJuego(Tablero<Celda*>* tablero, Lista<Jugador*>* listaJugadores){

    int numJugadores = 0;
    string nombreJugador = " ", mapaElegido = " ";

    cout << "---BATALLA DIGITAL---\n";
    
    cout << "---Ingrese el numero de jugadores: ";
    cin >> numJugadores;

    while (numJugadores <= 0 || numJugadores >= 100){       //definir    
        cout << "Ingresa una cantidad valida de jugadores. Numero de jugadores: \n";
        cin >> numJugadores;
    }
    
    for(int i=0; i<numJugadores; i++){
        cout << "Ingresa el nombre del jugador " << i+1 << ": ";
        cin >> nombreJugador;

        Jugador* jugador = new Jugador();
        listaJugadores->add(jugador);
        listaJugadores->getLData(i)->setNombre(nombreJugador);
    }

    //para probar
    for(int j=0; j<numJugadores; j++){
        cout << "Nombre de jugador " << j << " es: " << listaJugadores->getLData(j)->getNombre() << "\n";
    }

    /*
    cout << "Seleccione un mapa\n- playa - agua - ...\n";
    cin >> mapaElegido;

    if(mapaElegido == "playa"){

    }
    */
}

int main(){
    string cortar = "",ficha = "";
    bool seguir = false;
    int size = 20;
    char movimiento;
    coordenadas coordenadaFichaActual = {-1,-1,-1};
    Tablero<Celda*>* tablero = new Tablero<Celda*>(size, size, size);
    cargarMapa(tablero);
    Lista<Jugador*>* listaJugadores = new Lista<Jugador*>() ;        //agregado

    inicializarJuego(tablero, listaJugadores);

    while (!seguir){

        buscarCoordenadasFicha((&coordenadaFichaActual),tablero,(&ficha));
        if ((coordenadaFichaActual.x != -1) && (coordenadaFichaActual.y != -1) && (coordenadaFichaActual.z != -1)){

            while (movimiento != 't'){
                
                //procesarMapa(tablero,size);
                usarFicha(tablero,(&coordenadaFichaActual),ficha,(&movimiento));
                procesarMapa(tablero,size);
            }
        }
        cout << "\nSeguir?(Puede mandar la letra 'c' para salir)\n-";
        cin >> cortar;
        seguir = (cortar == "c") ? true : false;
    }
    delete tablero;
    return 0;
}