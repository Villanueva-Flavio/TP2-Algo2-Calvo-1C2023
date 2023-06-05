#include "./Headers/Tablero.h"
#include "./Headers/Celda.h"
#include "./Headers/Jugador.h"
#include "./Headers/Renderizador.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

#define CAPA_MAXIMA 5
#define CANTIDAD_FICHAS 10

struct coordenadas{int x,y,z;};
struct Niveles{int suelo,mar;};
struct Desplazar{int x,y,z;};

bool noEsOrillaRio(Mapa* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    double radioAjustado = 1+(0.227*(pow(size/4,1/2.5)));
    double radio = pow(y-mapa->getTamanioY()/2, 2) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio <= pow(size,radioAjustado)){
        orilla = true;
    }
    return orilla;
}

void cargarRio(Mapa* mapa, int size) {
    for(int x = 0; x < mapa->getTamanioX(); x++) {
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < CAPA_MAXIMA; z++) {
                if (noEsOrillaRio(mapa,x,y,z,size)){
                    mapa->getTData(x,y,z)->setTipo(CAPA_AGUA);
                }else if (noEsOrillaRio(mapa,x,y,z,size)){
                    if (z < CAPA_MAXIMA) mapa->getTData(x,y,z)->setTipo(CAPA_TIERRA);
                    mapa->getTData(x,y,CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
                }
                mapa->getTData(x,y,0)->setTipo(CAPA_ARENA);
            }
        }
    }
}

bool noEsOrillaDelLago(Mapa* mapa, int x, int y, int z, int size) {
    bool orilla = false;
    double radioAjustado = 1+(0.285*(pow(size/4,1/2.5)));
    double radio = pow(x-mapa->getTamanioX()/2, 2) + (pow(y-mapa->getTamanioY()/2, 2)) + pow(z-mapa->getTamanioZ()/2, 2);
    if (radio <= pow(size,radioAjustado)){
        orilla = true;
    }
    return orilla;
}

void cargarLago(Mapa* mapa, int size) {
    for(int x = 0; x < mapa->getTamanioX(); x++) {
        for(int y = 0; y < mapa->getTamanioY(); y++){
            for(int z = 0; z < CAPA_MAXIMA; z++) {
                if (noEsOrillaDelLago(mapa,x,y,z,size)){
                    mapa->getTData(x,y,z)->setTipo(CAPA_AGUA);
                }else if (noEsOrillaDelLago(mapa,x,y,z,size)){
                    if (z < CAPA_MAXIMA) mapa->getTData(x,y,z)->setTipo(CAPA_TIERRA);
                    mapa->getTData(x,y,CAPA_MAXIMA-1)->setTipo(CAPA_PASTO);
                }
                mapa->getTData(x,y,0)->setTipo(CAPA_ARENA);
            }
        }
    }
}

void cargarPlaya(Mapa* playa){
    for(int i = 0; i < playa->getTamanioX(); i++){
        for(int j = 0; j < playa->getTamanioY(); j++){
            for(int k = 0; k < playa->getTamanioZ(); k++){
                if(i < k+4 ){
                    playa->getTData(i, j, k)->setTipo(CAPA_ARENA);
                } else if (i >= k+4){
                    playa->getTData(i, j, k)->setTipo(CAPA_AGUA);
                }

                if(k > playa->getTamanioX() / 2){
                    playa->getTData(i, j, k)->setTipo(CAPA_AIRE);
                }
            }
        }
    }
}

void cargarMar(Mapa* mar) {
    for (int i = 0; i < mar->getTamanioX(); i++){
        for (int j = 0; j < mar->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                mar->getTData(i,j,k)->setTipo(CAPA_AGUA);
            }
        }
    }
}

void cargarTierra(Mapa* tierraConPasto) {
    for (int i = 0; i < tierraConPasto->getTamanioX(); i++){
        for (int j = 0; j < tierraConPasto->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                if (k < CAPA_MAXIMA-1){
                    tierraConPasto->getTData(i,j,k)->setTipo(CAPA_PASTO);
                }else {
                    tierraConPasto->getTData(i,j,k)->setTipo(CAPA_TIERRA);
                }                
            }
        }
    }
}

void cargarDesierto(Mapa* desierto) {
    for (int i = 0; i < desierto->getTamanioX(); i++){
        for (int j = 0; j < desierto->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                desierto->getTData(i,j,k)->setTipo(CAPA_ARENA);
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

void generarMundo(Mapa* mundoGenerado, std::string tipoDeMundo) {
     do{ // if (verificarOpcion(tipoDeMundo) == false){
                //tipoDeMundo = pedirTipoDeMundo();
         // }
        if (tipoDeMundo == "playa"){
            cargarPlaya(mundoGenerado);
        }else if (tipoDeMundo == "mar") {
            cargarMar(mundoGenerado);
        }else if (tipoDeMundo == "tierra"){
            cargarTierra(mundoGenerado);
        }else if (tipoDeMundo == "desierto"){
            cargarDesierto(mundoGenerado);
        }
        break; // Sacar el braque al descomentar el if de arriba
    } while (verificarOpcion(tipoDeMundo) == false);
}

void cargarCantidadesDeFicha(Jugador* jugadores[], int cantidadDeJugadores) {
    for(int i = 0; i < cantidadDeJugadores; i++) {
        jugadores[i]->setSoldados(CANTIDAD_FICHAS);
        jugadores[i]->setSoldados(CANTIDAD_FICHAS);
        // Cada vez que se mueran soldados decrementar cantidades 
    }
}

bool hayUnaFichaDelTipo(Mapa* mundoDelJuego, int coordenadaX, int coordenadaY, int coordenadaZ){
    bool hayDelTipo = true;
    hayDelTipo = (mundoDelJuego->getTData(coordenadaX,coordenadaY,coordenadaZ)->getFicha()->getTipo() == VACIO 
        && mundoDelJuego->getTData(coordenadaX,coordenadaY,coordenadaZ)->getFicha()->getTipo()) ? true : false;
    return hayDelTipo;
}

// Carga los soldados en cualquier mapa menos en el del mar
void cargarSoldados(Mapa* mundoDelJuego, Lista<Jugador*> jugadores, std::string tipoMundo) {
    // No puede haber soldados en el mapa de mar
    if (tipoMundo != "mar"){
        jugadores.resetIter(); // Para evitar errores restauro el iterador
        // Me guardo previamente las coordenadas de la celda a donde quiero ejectuar el cambio
        int x = rand() % mundoDelJuego->getTamanioX(), y = rand() % mundoDelJuego->getTamanioY(), z = CAPA_MAXIMA; 
        // Este iterador se usa para iterar tantas veces las asignaciones en el mapa como jugadores halla.
        for(int i = 0; i < jugadores.getSize(); i++){
            jugadores.iterar(SIGUIENTE);
            // Este iterador siver para asignar tantas fichas como en el jugador actual en cantidades se halla.
            for(int j = 0; j < jugadores.getLData(i)->getSoldados(); j++){
                // Si hay una ficha sin tipado se puede asignar una en la celda revisada, esto para no solapar fichas.
                if (mundoDelJuego->getTData(x,y,z)->getFicha()->getTipo() == VACIO){
                    mundoDelJuego->getTData(x,y,z)->getFicha()->setJugadorOwner(i);
                } else{ // Repetir paso con otra celda
                    j--;
                    x = rand() % mundoDelJuego->getTamanioX();
                    y = rand() % mundoDelJuego->getTamanioY();
                }
            }
        }
    }
}

// Verifica que no se esten superponiendo las fichas una encima de la otra y si es en un terreno válido
bool verificarSolapamientos(Mapa* mundoDelJuego, int tipoDeFichaActual, std::string tipoMundo, int x, int y, int z) {
    return ((tipoDeFichaActual == 0 && tipoMundo != "mar" && mundoDelJuego->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 1 && (tipoMundo != "mar" && tipoMundo != "lago") && mundoDelJuego->getTData(x,y,z-1)->getTipo() != CAPA_AGUA && mundoDelJuego->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 2 && (tipoMundo != "tierra" && tipoMundo != "desierto") && (mundoDelJuego->getTData(x,y,z-1)->getTipo() != CAPA_TIERRA && mundoDelJuego->getTData(x,y,z-1)->getTipo() != CAPA_ARENA && mundoDelJuego->getTData(x,y,z-1)->getTipo() != CAPA_PASTO) && mundoDelJuego->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 3 && mundoDelJuego->getTData(x,y,z)->getFicha()->getTipo() == VACIO && mundoDelJuego->getTData(x,y,z)->getTipo() == CAPA_AIRE) || (tipoDeFichaActual == 4 && (tipoMundo != "tierra" && tipoMundo != "desierto" && tipoMundo != "lago" && tipoMundo != "rio") && mundoDelJuego->getTData(x,y,z)->getFicha()->getTipo() == VACIO && mundoDelJuego->getTData(x,y,z)->getTipo() == CAPA_AGUA)) ? true : false;
}

// Segun en el estado en que se encuentr 'tipoDeFichaActual' se distribuye dos tipos de denominadores, uno para la cantidad de fichas y 4 para la cantidad de armamento.
int cantidadDistintaDeArmamento(int tipoDeFichaActual){
    return (tipoDeFichaActual == 0) ? 1 : 4 ;
}

int obtenerCantidadesDeFichas(Lista<Jugador*> jugadores, int tipoDeFichaActual, int jugadorActual) {
    return (tipoDeFichaActual < 1) ? jugadores.getLData(jugadorActual)->getSoldados() : jugadores.getLData(jugadorActual)->getArmamentos() ;
}

void cargarFichas(Mapa* mundoDelJuego, Lista<Jugador*> jugadores, std::string tipoMundo) {
    jugadores.resetIter();
    int x = 0, y = 0, z = 0;
    for(int jugadorActual = 0; jugadorActual < jugadores.getSize(); jugadorActual++){
        jugadores.iterar(SIGUIENTE);
        for (int tipoDeFichaActual = 0; tipoDeFichaActual < 5; tipoDeFichaActual++){
            // 0 soldado, 1 tanque, 2 barcos. El resto en cualquier nivel
            x = rand() % mundoDelJuego->getTamanioX(), y = rand() % mundoDelJuego->getTamanioY(), z = (tipoDeFichaActual < 3) ? CAPA_MAXIMA : (rand() % mundoDelJuego->getTamanioZ()) ;
            for(int j = 0; j < obtenerCantidadesDeFichas(jugadores,tipoDeFichaActual,jugadorActual) / cantidadDistintaDeArmamento(tipoDeFichaActual); j++){ 
                if (verificarSolapamientos(mundoDelJuego,tipoDeFichaActual,tipoMundo,x,y,z)){
                    mundoDelJuego->getTData(x,y,z)->getFicha()->setJugadorOwner(jugadorActual);
                } else{
                    j--;
                    x = rand() % mundoDelJuego->getTamanioX();
                    y = rand() % mundoDelJuego->getTamanioY();
                    z = (tipoDeFichaActual < 3) ? CAPA_MAXIMA : (rand() % mundoDelJuego->getTamanioZ());
                }
            }
        }
    }
}

// Carga a cada número de jugador de la lista un nombre
void cargarNombres(Lista<Jugador*> jugadores,std::string* nombres[]) {
    jugadores.resetIter();
    for(int i = 0; i < jugadores.getSize(); i++) { // getSize() == cantidadJugadores?
        (jugadores.getLData(jugadores.getIter()))->setNombre(*nombres[i]);
        jugadores.iterar(SIGUIENTE);
    }
}

// Carga cantidades no definidas e iguales a los jugadores de fichas
void cargarCantidadFichas(Lista<Jugador*> jugadores){
    jugadores.resetIter();
    for(int i = 0; i < jugadores.getSize(); i++) { // getSize() == cantidadJugadores?
        // 2 tipos distintos de armamentos para un total de 8 armamentos por jugador
        (jugadores.getLData(jugadores.getIter()))->setArmamentos(8);
        // 10 soldados por jugador
        (jugadores.getLData(jugadores.getIter()))->setSoldados(10);
        // 36 minas en total, 2 para cada ficha
        (jugadores.getLData(jugadores.getIter()))->setMinas(36);
        jugadores.iterar(SIGUIENTE);
    }    
}

// Carga el turno del primer jugador en true
void cargarTurnos(Lista<Jugador*> jugadores) {
    jugadores.resetIter();
    (jugadores.getLData(jugadores.getIter()))->setTurno(true);
}

// Carga la información de los jugadores
void cargarJugadores(Lista<Jugador*> jugadores,std::string* nombres[]) {
    cargarNombres(jugadores,nombres);
    cargarCantidadFichas(jugadores);
    cargarTurnos(jugadores);
}

// Pre: Se debe recibir 'mundoDelJuego' que es un puntero a 'Tablero<Celda*>' definido 'Mapa', luego se debe recibir 'jugadores' que es una lista de jugadores previamente agregados, además se debe recibir un array de string dinámico con los nombres de los jugadores, un string del mundo que va a elegir el jugador y el dato de la cantidad de jugadores.
void cargarJuego(Mapa* mundoDelJuego,Lista<Jugador*> jugadores, int cantidadJugadores, std::string tipoDeMundo, std::string* nombres[]) {
    srand(unsigned(time(NULL)));
    mundoDelJuego = new Mapa(jugadores.getSize() * 4, jugadores.getSize() * 4, jugadores.getSize() * 4);
    generarMundo(mundoDelJuego,tipoDeMundo);
    cargarJugadores(jugadores,nombres);
    cargarFichas(mundoDelJuego,jugadores,tipoDeMundo);
}
