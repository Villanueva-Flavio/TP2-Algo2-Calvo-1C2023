#include "../Headers/Tablero.h"
#include "../Headers/Jugador.h"
#include "../Headers/Renderizador.h"
#include "../Headers/BatallaDigital.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

const int CAPA_MAXIMA = 5;

void cargarPlaya(Tablero<Celda*>* tablero) {
    for(int i = 0; i < tablero->getTamanioX(); i++){
        for(int j = 0; j < tablero->getTamanioY(); j++){
            for(int k = 0; k < tablero->getTamanioZ(); k++){
                if(i < k+4 ){
                    tablero->getTData(i, j, k)->setTipo(CAPA_ARENA);
                } else if (i >= k+4){
                    tablero->getTData(i, j, k)->setTipo(CAPA_AGUA);
                }

                if(k > tablero->getTamanioX() / 2){
                    tablero->getTData(i, j, k)->setTipo(CAPA_AIRE);
                }
            }
        }
    }
}

void cargarMar(Tablero<Celda*>* tablero) {
    for (int i = 0; i < tablero->getTamanioX(); i++){
        for (int j = 0; j < tablero->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                tablero->getTData(i,j,k)->setTipo(CAPA_AGUA);
            }
        }
    }    
}

void cargarTierra(Tablero<Celda*>* tablero) {
    for (int i = 0; i < tablero->getTamanioX(); i++){
        for (int j = 0; j < tablero->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                if (k < CAPA_MAXIMA-1){
                    tablero->getTData(i,j,k)->setTipo(CAPA_PASTO);
                }else {
                    tablero->getTData(i,j,k)->setTipo(CAPA_TIERRA);
                }                
            }
        }
    }
}

void cargarDesierto(Tablero<Celda*>* tablero) {
    for (int i = 0; i < tablero->getTamanioX(); i++){
        for (int j = 0; j < tablero->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                tablero->getTData(i,j,k)->setTipo(CAPA_ARENA);
            }
        }
    }
}

bool verificarOpcion(std::string tipoDeMundo){
    bool opcionVerificada = false;
    if (tipoDeMundo == "playa" || tipoDeMundo == "mar" || tipoDeMundo == "tierra" || tipoDeMundo == "desierto" || tipoDeMundo == "rio" || tipoDeMundo == "lago"){
        opcionVerificada = true;
    }
    return opcionVerificada;
}

bool noEsOrillaDelLago(Tablero<Celda*>* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    double radioAjustado = 1+(0.285*(pow(size/4,1/2.5)));
    double radio = pow(x-mapa->getTamanioX()/2, 2) + (pow(y-mapa->getTamanioY()/2, 2)) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio <= pow(size,radioAjustado)){
        orilla = true;
    }
    return orilla;
}

void cargarLago(Tablero<Celda*>* mapa, int size) {
    for(int x = 0; x < mapa->getTamanioX(); x++) {
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < CAPA_MAXIMA; z++) {
                if (noEsOrillaDelLago(mapa,x,y,z,size)){
                    mapa->getTData(x,y,z)->setTipo(CAPA_AGUA);
                } else {
                    if (z < CAPA_MAXIMA) mapa->getTData(x,y,z)->setTipo(CAPA_TIERRA);
                    mapa->getTData(x,y,CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
                }
                mapa->getTData(x,y,0)->setTipo(CAPA_ARENA);
            }
        }
    }
}

bool noEsOrillaDelRio(Tablero<Celda*>* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    double radioAjustado = 1+(0.227*(pow(size/4,1/2.5)));
    double radio = pow(y-mapa->getTamanioY()/2, 2) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio <= pow(size,radioAjustado)){
        orilla = true;
    }
    return orilla;
}

void cargarRio(Tablero<Celda*>* mapa, int size) {
    for(int x = 0; x < mapa->getTamanioX(); x++) {
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < CAPA_MAXIMA; z++) {
                if (noEsOrillaDelRio(mapa,x,y,z,size)){
                    mapa->getTData(x,y,z)->setTipo(CAPA_AGUA);
                } else {
                    if (z < CAPA_MAXIMA) mapa->getTData(x,y,z)->setTipo(CAPA_TIERRA);
                    mapa->getTData(x,y,CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
                }
                mapa->getTData(x,y,0)->setTipo(CAPA_ARENA);
            }
        }
    }
}

void generarMundo(std::string tipoDeMundo, Tablero<Celda*>* tablero){
     do{ 
        // if (verificarOpcion(tipoDeMundo) == false){
                //tipoDeMundo = pedirTipoDeMundo();
         // }
        if (tipoDeMundo == "playa"){
            cargarPlaya(tablero);
        }else if (tipoDeMundo == "mar") {
            cargarMar(tablero);
        }else if (tipoDeMundo == "tierra"){
            cargarTierra(tablero);
        }else if (tipoDeMundo == "desierto"){
            cargarDesierto(tablero);
        }else if (tipoDeMundo == "lago"){
            cargarLago(tablero, tablero->getTamanioX());
        }else if (tipoDeMundo == "rio"){
            cargarRio(tablero, tablero->getTamanioX());
        }
        break; // Sacar el braque al descomentar el if de arriba
    } while (!verificarOpcion(tipoDeMundo));     
}

void cargarNombres(Lista<Jugador*>* jugadores,std::string* nombres) {
    jugadores->resetIter();
    for(int i = 0; i < jugadores->getSize(); i++) { // getSize() == cantidadJugadores?
        (jugadores->getLData(jugadores->getIter()))->setNombre(nombres[i]);
        jugadores->iterar(SIGUIENTE);
    }
}

void cargarCantidadFichas(Lista<Jugador*>* jugadores, int numeroDeJugadores){
    jugadores->resetIter();
    for(int i = 0; i < numeroDeJugadores; i++) {
        Jugador* jugadorActual = jugadores->getLData(jugadores->getIter());             //tira seg fault en este bucle
        // 2 tipos distintos de armamentos para un total de 8 armamentos por jugador
        jugadorActual->setArmamentos(8);
        // 10 soldados por jugador
        jugadorActual->setSoldados(10);
        // 36 minas en total, 2 para cada ficha
        jugadorActual->setMinas(36);
        jugadores->iterar(SIGUIENTE);
    }    
}

void cargarTurnos(Lista<Jugador*>* jugadores) {
    jugadores->resetIter();
    //(jugadores->getLData(jugadores->getIter()))->setTurno(true);
}

void cargarJugadores(Lista<Jugador*>* jugadores,std::string* nombres, int numeroDeJugadores) {

    cargarNombres(jugadores, nombres);
    cargarCantidadFichas(jugadores, numeroDeJugadores);
    cargarTurnos(jugadores);
}

bool verificarSolapamientos(Tablero<Celda*>* tablero, int tipoDeFichaActual, std::string tipoMundo, int x, int y, int z) {
    return ((tipoDeFichaActual == 0 && tipoMundo != "mar" && tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 1 && (tipoMundo != "mar" && tipoMundo != "lago") && tablero->getTData(x,y,z-1)->getTipo() != CAPA_AGUA && tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 2 && (tipoMundo != "tierra" && tipoMundo != "desierto") && (tablero->getTData(x,y,z-1)->getTipo() != CAPA_TIERRA && tablero->getTData(x,y,z-1)->getTipo() != CAPA_ARENA && tablero->getTData(x,y,z-1)->getTipo() != CAPA_PASTO) && tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 3 && tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO && tablero->getTData(x,y,z)->getTipo() == CAPA_AIRE) || (tipoDeFichaActual == 4 && (tipoMundo != "tierra" && tipoMundo != "desierto" && tipoMundo != "lago" && tipoMundo != "rio") && tablero->getTData(x,y,z)->getFicha()->getTipo() == VACIO && tablero->getTData(x,y,z)->getTipo() == CAPA_AGUA)) ? true : false;
}

int cantidadDistintaDeArmamento(int tipoDeFichaActual){
    return (tipoDeFichaActual == 0) ? 1 : 4 ;
}

int obtenerCantidadesDeFichas(Lista<Jugador*>* jugadores, int tipoDeFichaActual, int jugadorActual) {
    return (tipoDeFichaActual < 1) ? jugadores->getLData(jugadorActual)->getSoldados() : jugadores->getLData(jugadorActual)->getArmamentos() ;
}

void cargarFichas(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, std::string tipoMundo) {
    jugadores->resetIter();
    int x = 0, y = 0, z = 0;
    for(int jugadorActual = 0; jugadorActual < jugadores->getSize(); jugadorActual++){
        jugadores->iterar(SIGUIENTE);
        for (int tipoDeFichaActual = 0; tipoDeFichaActual < 5; tipoDeFichaActual++){
            // 0 soldado, 1 tanque, 2 barcos. El resto en cualquier nivel
            x = rand() % tablero->getTamanioX(), y = rand() % tablero->getTamanioY(), z = (tipoDeFichaActual < 3) ? CAPA_MAXIMA : (rand() % tablero->getTamanioZ()) ;
            for(int j = 0; j < obtenerCantidadesDeFichas(jugadores,tipoDeFichaActual,jugadorActual) / cantidadDistintaDeArmamento(tipoDeFichaActual); j++){ 
                if (verificarSolapamientos(tablero,tipoDeFichaActual,tipoMundo,x,y,z)){
                    tablero->getTData(x,y,z)->getFicha()->setJugadorOwner(jugadorActual);
                } else{
                    j--;
                    x = rand() % tablero->getTamanioX();
                    y = rand() % tablero->getTamanioY();
                    z = (tipoDeFichaActual < 3) ? CAPA_MAXIMA : (rand() % tablero->getTamanioZ());
                }
            }
        }
    }
}

void cargarJuego(Tablero<Celda*>* tablero, Lista<Jugador*>* jugadores, std::string* nombres, std::string tipoMundo, int numeroDeJugadores) {
    
    generarMundo(tipoMundo, tablero);
    cargarJugadores(jugadores, nombres, numeroDeJugadores);
    cargarFichas(tablero,jugadores,tipoMundo);
}

void mostrarTerreno(Tablero<Celda*>* tablero, int size) {
    Coordenada imgSize = {size*100, size*70};
    BMP imagen;
    imagen.SetSize(imgSize.x,imgSize.y);
    imprimirAngulo(imgSize,(&imagen),tablero, getMap());
    imagen.WriteToFile("Partida.bmp");
}

EstadoJuego estadoDelJuego(Lista<Jugador*>* listaJugadores, int cantJugadores){     // (acomodar)
    Jugador* ganador = nullptr;
    int contador = 0;

    listaJugadores->resetIter();
    for (int i = 0; i < cantJugadores; i++) {
        Jugador* jugador = listaJugadores->getLData(i);

        for (int j = 0; j < cantJugadores; j++) {
            Jugador* otroJugador = listaJugadores->getLData(j);
            if (jugador != otroJugador && otroJugador->getSoldados() == 0 && otroJugador->getArmamentos() == 0) {
                contador++;
            }
        }

    }
    if (contador == cantJugadores - 1) {
        return FINALIZADO;
    }
    return COMENZADO;
}
