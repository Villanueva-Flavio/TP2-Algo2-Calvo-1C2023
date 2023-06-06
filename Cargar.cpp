#include "Cargar.h"

Cargar::Cargar(){
    this->tipoDeMundo = "";
    this->numeroDeJugadores = 0;
    this->mundoDelJuego = nullptr;
    this->jugadores = nullptr;
    this->nombres = nullptr;
    srand(unsigned(time(NULL)));
}

void cargarPlaya(Tablero<Celda*>* mundoDelJuego) {
    for(int i = 0; i < mundoDelJuego->getTamanioX(); i++){
        for(int j = 0; j < mundoDelJuego->getTamanioY(); j++){
            for(int k = 0; k < mundoDelJuego->getTamanioZ(); k++){
                if(i < k+4 ){
                    mundoDelJuego->getTData(i, j, k)->setTipo(CAPA_ARENA);
                } else if (i >= k+4){
                    mundoDelJuego->getTData(i, j, k)->setTipo(CAPA_AGUA);
                }

                if(k > mundoDelJuego->getTamanioX() / 2){
                    mundoDelJuego->getTData(i, j, k)->setTipo(CAPA_AIRE);
                }
            }
        }
    }
}

void cargarMar(Tablero<Celda*>* mundoDelJuego) {
    for (int i = 0; i < mundoDelJuego->getTamanioX(); i++){
        for (int j = 0; j < mundoDelJuego->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                mundoDelJuego->getTData(i,j,k)->setTipo(CAPA_AGUA);
            }
        }
    }    
}

void cargarTierra(Tablero<Celda*>* mundoDelJuego) {
    for (int i = 0; i < mundoDelJuego->getTamanioX(); i++){
        for (int j = 0; j < mundoDelJuego->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                if (k < CAPA_MAXIMA-1){
                    mundoDelJuego->getTData(i,j,k)->setTipo(CAPA_PASTO);
                }else {
                    mundoDelJuego->getTData(i,j,k)->setTipo(CAPA_TIERRA);
                }                
            }
        }
    }
}

void cargarDesierto(Tablero<Celda*>* mundoDelJuego) {
    for (int i = 0; i < mundoDelJuego->getTamanioX(); i++){
        for (int j = 0; j < mundoDelJuego->getTamanioY(); j++){
            for (int k = 0; k < CAPA_MAXIMA; k++){
                mundoDelJuego->getTData(i,j,k)->setTipo(CAPA_ARENA);
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

void generarMundo(std::string tipoDeMundo, Tablero<Celda*>* mundoDelJuego){
     do{ 
        // if (verificarOpcion(tipoDeMundo) == false){
                //tipoDeMundo = pedirTipoDeMundo();
         // }
        if (tipoDeMundo == "playa"){
            cargarPlaya(mundoDelJuego);
        }else if (tipoDeMundo == "mar") {
            cargarMar(mundoDelJuego);
        }else if (tipoDeMundo == "tierra"){
            cargarTierra(mundoDelJuego);
        }else if (tipoDeMundo == "desierto"){
            cargarDesierto(mundoDelJuego);
        }else if (tipoDeMundo == "lago"){
            cargarLago(mundoDelJuego, mundoDelJuego->getTamanioX());
        }else if (tipoDeMundo == "rio"){
            cargarRio(mundoDelJuego, mundoDelJuego->getTamanioX());
        }
        break; // Sacar el braque al descomentar el if de arriba
    } while (!verificarOpcion(tipoDeMundo));     
}

void cargarNombres(Lista<Jugador*>* jugadores,std::string** nombres) {
    jugadores->resetIter();
    for(int i = 0; i < jugadores->getSize(); i++) { // getSize() == cantidadJugadores?
        (jugadores->getLData(jugadores->getIter()))->setNombre(*nombres[i]);
        jugadores->iterar(SIGUIENTE);
    }
}

void cargarCantidadFichas(Lista<Jugador*>* jugadores){
    jugadores->resetIter();
    for(int i = 0; i < jugadores->getSize(); i++) { // getSize() == cantidadJugadores?
        // 2 tipos distintos de armamentos para un total de 8 armamentos por jugador
        (jugadores->getLData(jugadores->getIter()))->setArmamentos(8);
        // 10 soldados por jugador
        (jugadores->getLData(jugadores->getIter()))->setSoldados(10);
        // 36 minas en total, 2 para cada ficha
        (jugadores->getLData(jugadores->getIter()))->setMinas(36);
        jugadores->iterar(SIGUIENTE);
    }    
}

void cargarTurnos(Lista<Jugador*>* jugadores) {
    jugadores->resetIter();
    (jugadores->getLData(jugadores->getIter()))->setTurno(true);
}

void cargarJugadores(Lista<Jugador*>* jugadores,std::string** nombres) {
    cargarNombres(jugadores,nombres);
    cargarCantidadFichas(jugadores);
    cargarTurnos(jugadores);
}

bool verificarSolapamientos(Tablero<Celda*>* mundoDelJuego, int tipoDeFichaActual, std::string tipoMundo, int x, int y, int z) {
    return ((tipoDeFichaActual == 0 && tipoMundo != "mar" && mundoDelJuego->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 1 && (tipoMundo != "mar" && tipoMundo != "lago") && mundoDelJuego->getTData(x,y,z-1)->getTipo() != CAPA_AGUA && mundoDelJuego->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 2 && (tipoMundo != "tierra" && tipoMundo != "desierto") && (mundoDelJuego->getTData(x,y,z-1)->getTipo() != CAPA_TIERRA && mundoDelJuego->getTData(x,y,z-1)->getTipo() != CAPA_ARENA && mundoDelJuego->getTData(x,y,z-1)->getTipo() != CAPA_PASTO) && mundoDelJuego->getTData(x,y,z)->getFicha()->getTipo() == VACIO) || (tipoDeFichaActual == 3 && mundoDelJuego->getTData(x,y,z)->getFicha()->getTipo() == VACIO && mundoDelJuego->getTData(x,y,z)->getTipo() == CAPA_AIRE) || (tipoDeFichaActual == 4 && (tipoMundo != "tierra" && tipoMundo != "desierto" && tipoMundo != "lago" && tipoMundo != "rio") && mundoDelJuego->getTData(x,y,z)->getFicha()->getTipo() == VACIO && mundoDelJuego->getTData(x,y,z)->getTipo() == CAPA_AGUA)) ? true : false;
}

int cantidadDistintaDeArmamento(int tipoDeFichaActual){
    return (tipoDeFichaActual == 0) ? 1 : 4 ;
}

int obtenerCantidadesDeFichas(Lista<Jugador*>* jugadores, int tipoDeFichaActual, int jugadorActual) {
    return (tipoDeFichaActual < 1) ? jugadores->getLData(jugadorActual)->getSoldados() : jugadores->getLData(jugadorActual)->getArmamentos() ;
}

void cargarFichas(Tablero<Celda*>* mundoDelJuego, Lista<Jugador*>* jugadores, std::string tipoMundo) {
    jugadores->resetIter();
    int x = 0, y = 0, z = 0;
    for(int jugadorActual = 0; jugadorActual < jugadores->getSize(); jugadorActual++){
        jugadores->iterar(SIGUIENTE);
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

void Cargar::cargarJuego(Tablero<Celda*>* mundoRecibido, Lista<Jugador*>* jugadores, std::string** nombres, std::string nombreMundo, int numeroDeJugadores) {
    mundoRecibido = new Tablero<Celda*>(numeroDeJugadores*4, numeroDeJugadores*4, numeroDeJugadores*4);
    this->mundoDelJuego = mundoRecibido;
    generarMundo(this->tipoDeMundo, this->mundoDelJuego);
    cargarJugadores(this->jugadores, this->nombres);
    cargarFichas(this->mundoDelJuego,this->jugadores,this->tipoDeMundo);
}