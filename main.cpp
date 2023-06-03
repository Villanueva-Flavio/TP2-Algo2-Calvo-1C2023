#include "./Headers/Tablero.h"
#include "./Headers/Celda.h"
#include "./Headers/Renderizador.h"
#include <iostream>
using namespace std;

                    z = tablero->getTamanioZ();
void cargarPlaya(Mapa* batallaDigital){
    for(int i = 0; i < batallaDigital->getTamanioX(); i++){
        for(int j = 0; j < batallaDigital->getTamanioY(); j++){
            for(int k = 0; k < batallaDigital->getTamanioZ(); k++){
                if(i < k+4 ){
                    batallaDigital->getTData(i, j, k)->setTipo(CAPA_ARENA);
                } else if (i >= k+4){
                    batallaDigital->getTData(i, j, k)->setTipo(CAPA_AGUA);
                }

                if(k > batallaDigital->getTamanioX() / 2){
                    batallaDigital->getTData(i, j, k)->setTipo(CAPA_AIRE);
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
    imagen.SetSize(imgSize.x, imgSize.y);
    cargarPlaya(batallaDigital);
    imprimirBMP(imgSize, &imagen, batallaDigital, getMap());
    imagen.WriteToFile("Partida.bmp");
}

// Cambia la casilla en la que se encuentra la ficha por la siguiente y viceversa, siempre y cuando se cumplan ciertas restricciones.
void usarFicha(Tablero<Celda*>* tablero, coordenadas* coordenadaFichaActual, string ficha, char* movimiento, int size) {
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
    coordenadas coordenadaFichaActual = {-1,-1,-1};
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
        cout << "\nSeguir?(Puede mandar la letra 'c' para salir)\n-";
        cin >> cortar;
        seguir = (cortar == "c") ? true : false;
    }
    delete tablero;
    return 0;
}